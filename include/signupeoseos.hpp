//
// Created by Hongbo Tang on 2018/7/5.
//

#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>
#include <eosio/action.hpp>
#include <eosio/symbol.hpp>
#include <eosio/crypto.hpp>
#include <cstring>
using namespace eosio;
using namespace std;

typedef eosio::name name;
typedef uint16_t weight_type;
#define CORE_SYMBOL eosio::symbol("WAX",8)


class [[eosio::contract("signupeoseos")]] signupeoseos: public contract {
public:
    signupeoseos(name s, name code, datastream<const char*> ds): eosio::contract(s, code, ds) {};

     [[eosio::action]]
    void hi( name hi );

    [[eosio::on_notify("eosio.token::transfer")]]
    void transfer(name from, name to, asset quantity, string memo);
private:
    struct signup_public_key {
        uint8_t        type;
        array<char,33> data;
    };
    struct permission_level_weight {
        permission_level permission;
        weight_type weight;
    };
    struct key_weight {
        signup_public_key key;
        weight_type weight;
    };
    struct wait_weight {
        uint32_t wait_sec;
        weight_type weight;
    };
    struct authority {
        uint32_t threshold;
        vector<key_weight> keys;
        vector<permission_level_weight> accounts;
        vector<wait_weight> waits;
    };
    struct newaccount {
        name creator;
        name name;
        authority owner;
        authority active;
    };
};

#define N(act)  eosio::name(act).value
