/**
 *  @file
 *  @copyright defined in plasma/LICENSE.txt
 */

#include <ion.token/ion.token.hpp>

namespace ion {

// token creation - account plus the maximum number of coins
void token::create( name   issuer,
                    asset  maximum_supply )
{
   // authentication
    require_auth( _self );

   // validation and validation of data entry
    auto sym = maximum_supply.symbol;
    check( sym.is_valid(), "invalid symbol name" );
    check( maximum_supply.is_valid(), "invalid supply");
    check( maximum_supply.amount > 0, "max-supply must be positive");

   // search for a similar token in the table, if found - return and execution error
    stats statstable( _self, sym.code().raw() );
    auto existing = statstable.find( sym.code().raw() );
    check( existing == statstable.end(), "token with symbol already exists" );

   // add a freshly created token to the general token table
    statstable.emplace( _self, [&]( auto& s ) {
       s.supply.symbol = maximum_supply.symbol;
       s.max_supply    = maximum_supply;
       s.issuer        = issuer;
    });
}

// issue a token on the platform, in the name of a specific account, the right amount
void token::issue( name to, asset quantity, string memo )
{
   // check for input validity
    auto sym = quantity.symbol;
    check( sym.is_valid(), "invalid symbol name" );
    check( memo.size() <= 256, "memo has more than 256 bytes" );

   // token search among existing tokens, general table, if not found - error and return
    stats statstable( _self, sym.code().raw() );
    auto existing = statstable.find( sym.code().raw() );
    check( existing != statstable.end(), "token with symbol does not exist, create token before issue" );
    const auto& st = *existing;

   // authentication 
    require_auth( st.issuer );

    // check the number of coins
    check( quantity.is_valid(), "invalid quantity" );
    check( quantity.amount > 0, "must issue positive quantity" );

   // check the symbol code of the coin
    check( quantity.symbol == st.supply.symbol, "symbol precision mismatch" );
    check( quantity.amount <= st.max_supply.amount - st.supply.amount, "quantity exceeds available supply");

   // modification of the table entry describing the current token
    // increase the supply parameter - the total number of coins on the platform
    statstable.modify( st, same_payer, [&]( auto& s ) {
       s.supply += quantity;
    });

   // call the function to add balance for the user, for the number of coins - specified in the quantity parameter
    add_balance( st.issuer, quantity, st.issuer );

    if( to != st.issuer ) {
   // call the token sending function to the user
      transfer_(st.issuer, to, quantity, memo);
    }
}

// mashing (burning) of the token, reducing the number of coins on the platform
void token::retire( asset quantity, string memo )
{
   // check the validity of the token character code
    auto sym = quantity.symbol;
    check( sym.is_valid(), "invalid symbol name" );
    check( memo.size() <= 256, "memo has more than 256 bytes" );

   // search for a token among existing ones, general table, error and return - if not found
    stats statstable( _self, sym.code().raw() );
    auto existing = statstable.find( sym.code().raw() );
    check( existing != statstable.end(), "token with symbol does not exist" );
    const auto& st = *existing;

   // transaction authentication - on behalf of the token creator
    require_auth( st.issuer );

    // check on the validity of the number of coins for burning - input parameter
    check( quantity.is_valid(), "invalid quantity" );
    check( quantity.amount > 0, "must retire positive quantity" );

   // check the accuracy of the token character code
    check( quantity.symbol == st.supply.symbol, "symbol precision mismatch" );

   // modification of the table entry describing the current token
    // reduce the supply parameter - the total number of coins on the platform
    statstable.modify( st, same_payer, [&]( auto& s ) {
       s.supply -= quantity;
    });

  // call the function to reduce the balance for the user, by the number of coins - specified in the quantity parameter
    sub_balance( st.issuer, quantity );
}

// forward the token from one account to another, a certain amount
void token::transfer( name    from,
                      name    to,
                      asset   quantity,
                      string  memo )
{
   // authentication on behalf of the sending user
    require_auth( _self );

   // call the internal function to transfer tokens from one account to another
    transfer_(from, to, quantity, memo);
}

// decrease the balance by a certain value
void token::sub_balance( name owner, asset value ) {

   // formation of an account key for search
   accounts from_acnts( _self, owner.value );

   // Search for an account in a table containing all the values and additional validation
   const auto& from = from_acnts.get( value.symbol.code().raw(), "no balance object found" );
   check( from.balance.amount >= value.amount, "overdrawn balance" );

   // balance change - decrease by input parameter value
   from_acnts.modify( from, same_payer, [&]( auto& a ) {
         a.balance -= value;
      });
}

// adding balance
void token::add_balance( name owner, asset value, name ram_payer )
{
   //search for an account in a table containing all the values plus additional validation
   accounts to_acnts( _self, owner.value );
   auto to = to_acnts.find( value.symbol.code().raw() );

   // if not found - add again
   if( to == to_acnts.end() ) {
      to_acnts.emplace( _self, [&]( auto& a ){
        a.balance = value;
      });
   } else { // otherwise - modification of the current record by the value of the input parameter value
      to_acnts.modify( to, same_payer, [&]( auto& a ) {
        a.balance += value;
      });
   }
}

// creating an account for the user on which he can contain a token of a certain format
void token::open( name owner, const symbol& symbol, name ram_payer )
{
   // authentication
   require_auth( _self );

   auto sym_code_raw = symbol.code().raw();

   // search for the character code in the table and checking for correctness
   stats statstable( _self, sym_code_raw );
   const auto& st = statstable.get( sym_code_raw, "symbol does not exist" );
   check( st.supply.symbol == symbol, "symbol precision mismatch" );

  // search for an account among existing ones
    // if an account is found, just exit the function
    // if not, add a record to the table
   accounts acnts( _self, owner.value );
   auto it = acnts.find( sym_code_raw );
   if( it == acnts.end() ) {
      acnts.emplace( _self, [&]( auto& a ){
        a.balance = asset{0, symbol};
      });
   }
}

// closing for the user an account on which he could hold a token of a certain format
void token::close( name owner, const symbol& symbol )
{
   require_auth( _self );

// search for an account among existing ones
   accounts acnts( _self, owner.value );
   auto it = acnts.find( symbol.code().raw() );

// if the account is not found, we generate an error
   check( it != acnts.end(), "Balance row already deleted or never existed. Action won't have any effect." );

   // if an account is found - check its balance
    // if the balance is zero - feel free to delete the account, otherwise we generate an error
   check( it->balance.amount == 0, "Cannot close because the balance is not zero." );
   acnts.erase( it );
}

// decrease the balance by a certain value
void token::subbalance( asset quantity)
{
  // function call - overwriting (burning) the token, reducing the number of coins on the platform
   retire(std::move(quantity), "retire");
}

// service function to transfer the token from one user to another
void token::transfer_(name from, name to, const asset& quantity, const string& memo)
{
   // check for the ability to send tokens to oneself
   check( from != to, "cannot transfer to self" );

// check for the existence of an account inside the blockchain
   check( is_account( to ), "to account does not exist");

  // generate and search for the symbolic code of the coin
   const auto& sym = quantity.symbol.code();
   stats statstable( _self, sym.raw() );
   const auto& st = statstable.get( sym.raw() );

// notification of required accounts
   require_recipient( from );
   require_recipient( to );

 // validation check - the number of coins to send
   check( quantity.is_valid(), "invalid quantity" );
   check( quantity.amount > 0, "must transfer positive quantity" );

   // validation check - accuracy
   check( quantity.symbol == st.supply.symbol, "symbol precision mismatch" );

   // check the validity of the memo field
   check( memo.size() <= 256, "memo has more than 256 bytes" );

// payer for creating / creating a record in the table
   auto payer = has_auth( to ) ? to : from;

// server function call - reducing user balance
   sub_balance( from, quantity );

   // server function call - increase user balance
   add_balance( to, quantity, payer );
}

} /// namespace ion

ION_DISPATCH( ion::token, (create)(issue)(transfer)(open)(close)(retire)(subbalance) )
