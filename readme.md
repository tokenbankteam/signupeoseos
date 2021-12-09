# signupeoseos

### Install

```
cleos create account eosio signupeoseo your_public_key
make build_and_deploy
```

### Usage

```
cleos transfer eosio signupeoseos "5.00000000 WAX" "your_account_name-your_public_key"
```


```
~# cleos -u https://testnet.waxsweden.org transfer  clement33333 clement12345 "1.00000000 WAX" "clement55555-EOS8JVnjJHLv8kQ8ix8ALSmRqkXXckBcfqwdCtuHkRq3gtQPVSvsJ"
executed transaction: 47e47fad21242f066132d57ac9d94e597903e3e293b936cb058d978113a63341  192 bytes  1233 us
#   eosio.token <= eosio.token::transfer        {"from":"clement33333","to":"clement12345","quantity":"1.00000000 WAX","memo":"clement55555-EOS8JVnj...
#  clement33333 <= eosio.token::transfer        {"from":"clement33333","to":"clement12345","quantity":"1.00000000 WAX","memo":"clement55555-EOS8JVnj...
#  clement12345 <= eosio.token::transfer        {"from":"clement33333","to":"clement12345","quantity":"1.00000000 WAX","memo":"clement55555-EOS8JVnj...
#         eosio <= eosio::newaccount            {"creator":"clement12345","name":"clement55555","owner":{"threshold":1,"keys":[{"key":"EOS8JVnjJHLv8...
#         eosio <= eosio::buyram                {"payer":"clement12345","receiver":"clement55555","quant":"0.99998000 WAX"}
#         eosio <= eosio::delegatebw            {"from":"clement12345","receiver":"clement55555","stake_net_quantity":"0.00001000 WAX","stake_cpu_qu...
#   eosio.token <= eosio.token::transfer        {"from":"clement12345","to":"eosio.ram","quantity":"0.99498010 WAX","memo":"buy ram"}
#   eosio.token <= eosio.token::transfer        {"from":"clement12345","to":"eosio.ramfee","quantity":"0.00499990 WAX","memo":"ram fee"}
#  clement12345 <= eosio.token::transfer        {"from":"clement12345","to":"eosio.ram","quantity":"0.99498010 WAX","memo":"buy ram"}
#     eosio.ram <= eosio.token::transfer        {"from":"clement12345","to":"eosio.ram","quantity":"0.99498010 WAX","memo":"buy ram"}
#  clement12345 <= eosio.token::transfer        {"from":"clement12345","to":"eosio.ramfee","quantity":"0.00499990 WAX","memo":"ram fee"}
#  eosio.ramfee <= eosio.token::transfer        {"from":"clement12345","to":"eosio.ramfee","quantity":"0.00499990 WAX","memo":"ram fee"}
#   eosio.token <= eosio.token::transfer        {"from":"clement12345","to":"eosio.stake","quantity":"0.00002000 WAX","memo":"stake bandwidth"}
#  clement12345 <= eosio.token::transfer        {"from":"clement12345","to":"eosio.stake","quantity":"0.00002000 WAX","memo":"stake bandwidth"}
#   eosio.stake <= eosio.token::transfer        {"from":"clement12345","to":"eosio.stake","quantity":"0.00002000 WAX","memo":"stake bandwidth"}

```