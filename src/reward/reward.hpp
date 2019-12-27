#pragma once

#include <ion/ion.hpp>
#include <ion/singleton.hpp>

#include "gmsp_reward_data.hpp"
#include "../../core/contract.hpp"

//--------------------------------------------------------------------------------
// GMSP - it`s example, сhoice your project name or short name token 

class [[ion::contract]] gmsp_reward : public plasma::contractBase
{
public:
    gmsp_reward(ion::name receiver, ion::name code, ion::datastream<const char*> ds);
    virtual ~gmsp_reward() {}

    [[ion::action]]
    void regowner(ion::name owner);

    [[ion::action]]
    void showowners();

    [[ion::action]]
    void clearowners();

    [[ion::action]]
    void collect(ion::symbol_code code);

    [[ion::action]]
    void showcollect();

    [[ion::action]]
    void clearcollect();

    [[ion::action]]
    void reward(ion::name owner, ion::symbol_code code);

    [[ion::action]]
    void updatelimits(uint32_t interval_seconds, uint32_t epsilon_seconds);

    [[ion::action]]
    void showlimits();

    [[ion::action]]
    void version();

private:
    TABLE gmsp_owner_data : public gmsp::gmsp_owner {};
    using TableGmspOwner_t = ion::multi_index<"gmsp.owner"_n, gmsp_owner_data>;
    TableGmspOwner_t gmsp_owner_t;

    TABLE gmsp_payout_data : public gmsp::gmsp_payout {};
    using TableGmspPayout_t = ion::multi_index<"gmsp.payout"_n, gmsp_payout_data>;
    TableGmspPayout_t gmsp_payout_t;

    TABLE gmsp_receipt_data : public gmsp::gmsp_receipt {};
    using TableGmspReceipt_t = ion::multi_index<"gmsp.receipt"_n, gmsp_receipt_data>;
    TableGmspReceipt_t gmsp_receipt_t;

    using gmsp_limits_data = ion::singleton< "gmsp.limits"_n, gmsp::gmsp_limits>;
    gmsp_limits_data gmsp_limits_t;
};

//--------------------------------------------------------------------------------
