//
// Created by Hongbo Tang on 2018/7/5.
//

#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/types.hpp>
#include <eosio.system/native.hpp>
//#include <eosio/chain/types.hpp>
//#include <eosio/chain/authority.hpp>
//#include <eosio/chain/contract_types.hpp>

using namespace eosio;

class signup_public_key {
public:
    uint32_t        type;
    std::array<char,33> data;

    explicit signup_public_key(const std::string& base58str) {

    }
};

class signupeoseos: public contract {
public:
    signupeoseos(account_name self): contract(self){};
    void transfer(account_name from, account_name to, asset quantity, std::string memo);
private:
//    struct key_weight {
//        public_key key;
//        uint16_t weight;
//    };
//    struct wait_weight {
//        uint32_t wait_sec;
//        uint16_t weight;
//    };
//    struct authority {
//        uint32_t threshold;
//        std::vector<eosiosystem::key_weight> keys;
//        std::vector<eosiosystem::permission_level_weight> accounts;
//        std::vector<wait_weight> waits;
//    };
//    struct newaccount {
//        account_name creator;
//        account_name name;
//        authority owner;
//        authority active;
//    };
};

#define EOSIO_ABI_EX( TYPE, MEMBERS ) \
extern "C" { \
    void apply( uint64_t receiver, uint64_t code, uint64_t action ) { \
        auto self = receiver; \
        if( action == N(onerror)) { \
            /* onerror is only valid if it is for the "eosio" code account and authorized by "eosio"'s "active permission */ \
            eosio_assert(code == N(eosio), "onerror action's are only valid from the \"eosio\" system account"); \
        } \
        if( (code == self || action == N(onerror)) || (code == N(eosio.token) && action == N(transfer)) ) { \
            TYPE thiscontract( self ); \
            switch( action ) { \
                EOSIO_API( TYPE, MEMBERS ) \
            } \
         /* does not allow destructor of thiscontract to run: eosio_exit(0); */ \
        } \
    } \
} \

EOSIO_ABI_EX(signupeoseos, (transfer))