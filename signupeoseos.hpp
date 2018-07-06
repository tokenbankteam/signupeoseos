//
// Created by Hongbo Tang on 2018/7/5.
//

#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/types.hpp>
#include <eosio/chain/types.hpp>
#include <eosio/chain/authority.hpp>
#include <eosio/chain/contract_types.hpp>

using namespace eosio;

class signupeoseos: public contract {
public:
    signupeoseos(account_name self): contract(self){};
    void transfer(account_name from, account_name to, asset quantity, std::string memo);
private:
//    struct key_weight {
//        std::string key;
//        uint16_t weight;
//    };
//    struct authority {
//        uint32_t threshold;
//        std::vector<key_weight> keys;
//        std::vector<uint64_t> accounts;
//        std::vector<uint64_t> waits;
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