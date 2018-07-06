//
// Created by Hongbo Tang on 2018/7/5.
//

#include "signupeoseos.hpp"
using namespace std;
using namespace eosio::chain;

void signupeoseos::transfer(account_name from, account_name to, asset quantity, string memo) {
    if (from == _self || to != _self) {
        return;
    }
    print("from: ", from, " to: ", to, " quantity: ", quantity, " memo: ", memo, "\n");
    eosio_assert(quantity.symbol == string_to_symbol(4, "EOS"), "EosRAMBettor only accepts EOS for deposits");
    eosio_assert(quantity.is_valid(), "Invalid token transfer");
    eosio_assert(quantity.amount > 0, "Quantity must be positive");

    asset stake_net(0.001, S(4, EOS));
    asset stake_cpu(0.001, S(4, EOS));
    asset buy_ram = quantity - stake_net - stake_cpu;
    eosio_assert(buy_ram.amount > 0, "Not enough eos to buy ram");

    // todo: trim string
    auto space_pos = memo.find(' ');
    eosio_assert(space_pos != string::npos, "Public key and account name must be separated with space");

    auto public_key_str = memo.substr(0, space_pos);
    auto account_name_str = memo.substr(space_pos + 1);

    account_name new_account_name = string_to_name(account_name_str.c_str());

    authority owner = authority{
        .threshold = 1,
        .keys = {{public_key_type(public_key_str), 1}},
        .accounts = {},
        .waits = {}
    };
    newaccount new_account = newaccount{
        .creator = _self,
        .name = new_account_name,
        .owner = owner,
        .active = owner
    };
    action(
            permission_level{ _self, N(active) },
            N(eosio),
            N(newaccount),
            new_account
    ).send();

    action(
            permission_level{ _self, N(active)},
            N(eosio),
            N(buyram),
            std::make_tuple(_self, new_account_name, buy_ram)
    ).send();

    action(
            permission_level{ _self, N(active)},
            N(eosio),
            N(delegatebw),
            std::make_tuple(_self, new_account_name, stake_net, stake_cpu, true)
    ).send();
}
