/**
 *  @file
 *  @copyright defined in plasma/LICENSE.txt
 */
#pragma once

#include <ionlib/asset.hpp>
#include <ionlib/ion.hpp>

#include <string>

namespace ion {

   using std::string;

   class [[ion::contract("ion.token")]] token : public contract {
      public:
         using contract::contract;

        // create current - account plus the number of coins available
         [[ion::action]]
         void create( name   issuer,
                      asset  maximum_supply);

         // issue a token on the platform, in the name of a specific account, the right amount
         [[ion::action]]
         void issue( name to, asset quantity, string memo );

        // overwriting (burning) the token, reducing the number of coins on the platform
         [[ion::action]]
         void retire( asset quantity, string memo );

         // forward the token from one account to another, a certain amount
         [[ion::action]]
         void transfer( name    from,
                        name    to,
                        asset   quantity,
                        string  memo );

         // create an account for the user on which he can contain a token of a certain format
         [[ion::action]]
         void open( name owner, const symbol& symbol, name ram_payer );

         // closing for the user an account on which he could hold a token of a certain format
         [[ion::action]]
         void close( name owner, const symbol& symbol );

         // decrease the balance by a certain value
         [[ion::action]]
         void subbalance(asset quantity);

         // get the total balance of the token with a specific code
         static asset get_supply( name token_contract_account, symbol_code sym_code )
         {
            stats statstable( token_contract_account, sym_code.raw() );
            const auto& st = statstable.get( sym_code.raw() );
            return st.supply;
         }

         // get the balance of a certain token
         static asset get_balance( name token_contract_account, name owner, symbol_code sym_code )
         {
            accounts accountstable( token_contract_account, owner.value );
            const auto& ac = accountstable.get( sym_code.raw() );
            return ac.balance;
         }

         using create_action = ion::action_wrapper<"create"_n, &token::create>;
         using issue_action = ion::action_wrapper<"issue"_n, &token::issue>;
         using retire_action = ion::action_wrapper<"retire"_n, &token::retire>;
         using transfer_action = ion::action_wrapper<"transfer"_n, &token::transfer>;
         using open_action = ion::action_wrapper<"open"_n, &token::open>;
         using close_action = ion::action_wrapper<"close"_n, &token::close>;

         
      private:

         // structure describing the balance of a token of a certain type
         struct [[ion::table]] account {
            asset    balance;       // character + quantity
            uint64_t primary_key()const { return balance.symbol.code().raw(); }
         };

         // structure describing the status of a specific token on the platform
         struct [[ion::table]] currency_stats {
            asset    supply;           // currently released
            asset    max_supply;       // total can be released, the maximum number
            name     issuer;           // owner - token account

            uint64_t primary_key()const { return supply.symbol.code().raw(); }
         };

         typedef ion::multi_index< "accounts"_n, account > accounts;
         typedef ion::multi_index< "stat"_n, currency_stats > stats;

         // service functions for adding / decreasing user balance
         void sub_balance( name owner, asset value );
         void add_balance( name owner, asset value, name ram_payer );

         // service function to transfer the token from one user to another
         void transfer_(name from, name to, const asset& quantity, const string& memo);
   };

} /// namespace ion
