#include "gmsp_reward.hpp"

#include <ion/print.hpp>
#include <ion/system.hpp>

#include "../../core/accounts.hpp"
#include "../../core/token_utils.hpp"

//--------------------------------------------------------------------------------
// GMSP - it`s example, сhoice your project name or short name token 

gmsp_reward::gmsp_reward(ion::name receiver, ion::name code, ion::datastream<const char*> ds)
  : contractBase(receiver, code, ds),
    gmsp_owner_t(receiver, code.value),
    gmsp_payout_t(receiver, code.value),
    gmsp_receipt_t(receiver, code.value),
    gmsp_limits_t(receiver, code.value)
{
}

//--------------------------------------------------------------------------------

void gmsp_reward::regowner(ion::name owner)
{
    require_auth(get_self());

    plasma::big_asset balance = plasma::tokenTypes::getBalanceEx(owner, plasma::gmsp_code);
    ion::check(balance.get_amount(), "no balance object found");

    auto it = gmsp_owner_t.find(owner.value);
    if (it == gmsp_owner_t.end()) {
        gmsp_owner_t.emplace(get_self(), [&](auto& new_data) { new_data.owner = owner; });
    }
    else {
        ion::print("Register gmsp owner - user already exists in DB.\n");
    }
}

//--------------------------------------------------------------------------------

void gmsp_reward::showowners()
{
    require_auth(get_self());

    for (const auto& item : gmsp_owner_t) {
        ion::print(item.owner, "\n");
    }
}

//--------------------------------------------------------------------------------

void gmsp_reward::clearowners()
{
    require_auth(get_self());
    
    auto it = gmsp_owner_t.begin();
    while (it != gmsp_owner_t.end()) {
        it = gmsp_owner_t.erase(it);
    }
}

//--------------------------------------------------------------------------------

void gmsp_reward::collect(ion::symbol_code code)
{
    require_auth(get_self());
    ion::check(code != plasma::gmsp_code, "symbol code == GMSP");

    plasma::big_asset balance = plasma::tokenTypes::getBalanceEx(plasma::accountGmspBank, code);
    ion::check(balance.get_amount(), "no balance object found");

    plasma::big_asset supply = plasma::tokenTypes::getSupplyEx(plasma::gmsp_code);
    ion::check(supply.get_amount(), "no supplied balance object found");

    plasma::big_asset payout = plasma::big_asset(
        std::pow(10, supply.symbol.precision()) * (balance.get_amount() / supply.get_amount()), balance.symbol);

    ion::check(payout.get_amount(), "too small payout - not enough precision");
    ion::print("[balance = ", balance, ", supply = ", supply, ", payout per 1 ", plasma::gmsp_code, " = ", payout, "]\n");

    uint32_t block_time = ion::current_time_point().sec_since_epoch();
    auto it = gmsp_payout_t.find(code.raw());

    if (it == gmsp_payout_t.end()) {
        gmsp_payout_t.emplace(get_self(), [&](auto& new_data) { 
            new_data.payout_time = block_time;
            new_data.payout_per_one = payout;
        });
    }
    else {
        uint32_t old_time = it->payout_time;
        uint32_t diff_time = block_time - old_time;

        gmsp::gmsp_limits tmp = gmsp_limits_t.get_or_default();

        ion::check(block_time - it->payout_time > tmp.interval_seconds, "less than 24 hours passed after previous payouts");
        ion::print("[block_seconds = ", block_time, ", payout_seconds = ", old_time, ", interval_seconds = ", diff_time, "]\n");

        gmsp_payout_t.modify(it, get_self(), [&](auto& old_data)
        {
            old_data.payout_time = block_time;
            old_data.payout_per_one = payout;
        });
    }
}

//--------------------------------------------------------------------------------

void gmsp_reward::clearcollect()
{
    require_auth(get_self());
    
    auto it = gmsp_payout_t.begin();
    while (it != gmsp_payout_t.end()) {
        it = gmsp_payout_t.erase(it);
    }
}

//--------------------------------------------------------------------------------

void gmsp_reward::showcollect()
{
    require_auth(get_self());
    
    for (const auto& item : gmsp_payout_t) {
        ion::print("[payout per 1 ", plasma::gmsp_code, " = ", item.payout_per_one);
        ion::print(", timestamp = ", item.payout_time, " seconds]\n");
    }
}

//--------------------------------------------------------------------------------

void gmsp_reward::reward(ion::name owner, ion::symbol_code code)
{
    require_auth(get_self());
    ion::check(code != plasma::gmsp_code, "symbol code == GMSP");

    auto it_payout = gmsp_payout_t.find(code.raw());
    ion::check(it_payout != gmsp_payout_t.end(), "no collected payout information found");

    gmsp::gmsp_limits tmp = gmsp_limits_t.get_or_default();
    uint32_t final_interval = tmp.interval_seconds - tmp.epsilon_seconds;

    uint32_t block_time = ion::current_time_point().sec_since_epoch();
    ion::check(block_time - it_payout->payout_time < tmp.interval_seconds, "more than 24 hours passed after previous collect");

    plasma::big_asset balance = plasma::tokenTypes::getBalanceEx(owner, plasma::gmsp_code);
    ion::check(balance.get_amount(), "no balance object found");

    auto it_receipt = gmsp_receipt_t.find(owner.value);
    if (it_receipt != gmsp_receipt_t.end())
    {
        auto it_code = it_receipt->symbols.find(code.to_string());
        if (it_code != it_receipt->symbols.end()) {
            ion::check(block_time - it_code->second > final_interval, "less than 24 hours passed after previous payout");
        }

        gmsp_receipt_t.modify(it_receipt, get_self(), [&](auto& old_data) { 
            old_data.symbols[code.to_string()] = block_time;
        });
    }
    else
    {
        gmsp_receipt_t.emplace(get_self(), [&](auto& new_data) { 
            new_data.owner = owner;
            new_data.symbols[code.to_string()] = block_time;
        });
    }

    plasma::big_asset payout = plasma::big_asset(
        balance.get_amount() * it_payout->payout_per_one.get_amount() / 
        std::pow(10, balance.symbol.precision()), plasma::tokenTypes::getSymbolEx(code));

    ion::print("[payout per 1 ", plasma::gmsp_code, " = ", it_payout->payout_per_one);
    ion::print(", balance = ", balance, ", payout = ", payout, "]\n");

    std::string memo_payout = "gmsp reward for owner " + owner.to_string();
    plasma::token::transfer(plasma::accountGmspBank, owner, payout, memo_payout);
}

//--------------------------------------------------------------------------------

void gmsp_reward::showlimits()
{
    require_auth(get_self());

    gmsp::gmsp_limits tmp = gmsp_limits_t.get_or_default();
    ion::print("[interval_seconds = ", tmp.interval_seconds, ", epsilon_seconds = ", tmp.epsilon_seconds, "]\n");
}

//--------------------------------------------------------------------------------

void gmsp_reward::updatelimits(uint32_t interval_seconds, uint32_t epsilon_seconds)
{
    require_auth(get_self());

    ion::check(interval_seconds > 0, "invalid zero interval_seconds");
    ion::check(interval_seconds > epsilon_seconds, "incorrect interval_seconds > epsilon_second");
    
    gmsp::gmsp_limits tmp = gmsp_limits_t.get_or_default();

    tmp.epsilon_seconds = epsilon_seconds;
    tmp.interval_seconds = interval_seconds;

    gmsp_limits_t.set(tmp, get_self());
}

//--------------------------------------------------------------------------------

void gmsp_reward::version()
{
    printVersion("0.1");
}

//--------------------------------------------------------------------------------

ION_DISPATCH(gmsp_reward, (regowner)(showowners)(clearowners)(collect)(clearcollect)(showcollect)(reward)(showlimits)(updatelimits)(version))
