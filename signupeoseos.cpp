#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>
//#include <eosiolib/types.hpp>
#include <eosio/action.hpp>
#include <eosio/symbol.hpp>
#include <eosio/crypto.hpp>
#include <cstring>
using namespace eosio;
using namespace std;

typedef int64_t weight_type;
#define CORE_SYMBOL symbol("WAX",8)

CONTRACT signupeoseos: public contract {
public:

signupeoseos(name receiver, name code, datastream<const char*> ds): contract(receiver, code, ds){};


ACTION transfer(name from, name to, asset quantity, string memo);
private:
struct signup_public_key {
    uint8_t        type;
    array<unsigned char,33> data;
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


// Copied from https://github.com/bitcoin/bitcoin

/** All alphanumeric characters except for "0", "I", "O", and "l" */
static const char* pszBase58 = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
static const int8_t mapBase58[256] = {
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1, 0, 1, 2, 3, 4, 5, 6,  7, 8,-1,-1,-1,-1,-1,-1,
        -1, 9,10,11,12,13,14,15, 16,-1,17,18,19,20,21,-1,
        22,23,24,25,26,27,28,29, 30,31,32,-1,-1,-1,-1,-1,
        -1,33,34,35,36,37,38,39, 40,41,42,43,-1,44,45,46,
        47,48,49,50,51,52,53,54, 55,56,57,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
};

bool DecodeBase58(const char* psz, std::vector<unsigned char>& vch)
{
    // Skip leading spaces.
    while (*psz && isspace(*psz))
        psz++;
    // Skip and count leading '1's.
    int zeroes = 0;
    int length = 0;
    while (*psz == '1') {
        zeroes++;
        psz++;
    }
    // Allocate enough space in big-endian base256 representation.
    int size = strlen(psz) * 733 /1000 + 1; // log(58) / log(256), rounded up.
    std::vector<unsigned char> b256(size);
    // Process the characters.
    static_assert(sizeof(mapBase58)/sizeof(mapBase58[0]) == 256, "mapBase58.size() should be 256"); // guarantee not out of range
    while (*psz && !isspace(*psz)) {
        // Decode base58 character
        int carry = mapBase58[(uint8_t)*psz];
        if (carry == -1)  // Invalid b58 character
            return false;
        int i = 0;
        for (std::vector<unsigned char>::reverse_iterator it = b256.rbegin(); (carry != 0 || i < length) && (it != b256.rend()); ++it, ++i) {
            carry += 58 * (*it);
            *it = carry % 256;
            carry /= 256;
        }
        assert(carry == 0);
        length = i;
        psz++;
    }
    // Skip trailing spaces.
    while (isspace(*psz))
        psz++;
    if (*psz != 0)
        return false;
    // Skip leading zeroes in b256.
    std::vector<unsigned char>::iterator it = b256.begin() + (size - length);
    while (it != b256.end() && *it == 0)
        it++;
    // Copy result into output vector.
    vch.reserve(zeroes + (b256.end() - it));
    vch.assign(zeroes, 0x00);
    while (it != b256.end())
        vch.push_back(*(it++));
    return true;
}

bool decode_base58(const string& str, vector<unsigned char>& vch) {
    return DecodeBase58(str.c_str(), vch);
}


ACTION signupeoseos::transfer(name from, name to, asset quantity, string memo) {
    if (from == _self || to != _self) {
        return;
    }
    check(quantity.symbol == CORE_SYMBOL, "signupeoseos only accepts CORE for signup eos account");
    check(quantity.is_valid(), "Invalid token transfer");
    check(quantity.amount > 0, "Quantity must be positive");

    memo.erase(memo.begin(), find_if(memo.begin(), memo.end(), [](int ch) {
        return !isspace(ch);
    }));
    memo.erase(find_if(memo.rbegin(), memo.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), memo.end());

    auto separator_pos = memo.find(' ');
    if (separator_pos == string::npos) {
        separator_pos = memo.find('-');
    }
    check(separator_pos != string::npos, "Account name and other command must be separated with space or minuses");

    string account_name_str = memo.substr(0, separator_pos);
    check(account_name_str.length() == 12, "Length of account name should be 12");
    name new_account_name = name(account_name_str.c_str());

    string public_key_str = memo.substr(separator_pos + 1);
    check(public_key_str.length() == 53, "Length of publik key should be 53");

    string pubkey_prefix("EOS");
    auto result = mismatch(pubkey_prefix.begin(), pubkey_prefix.end(), public_key_str.begin());
    check(result.first == pubkey_prefix.end(), "Public key should be prefix with EOS");
    auto base58substr = public_key_str.substr(pubkey_prefix.length());

    vector<unsigned char> vch;
    check(decode_base58(base58substr, vch), "Decode pubkey failed");
    check(vch.size() == 37, "Invalid public key");

    array<unsigned char,33> pubkey_data;
    copy_n(vch.begin(), 33, pubkey_data.begin());

    checksum160 check_pubkey;
    check_pubkey = ripemd160(reinterpret_cast<char *>(pubkey_data.data()), 33);
    check(memcmp(&check_pubkey, &vch.end()[-4], 4) == 0, "invalid public key");

    asset stake_net(1000, CORE_SYMBOL);
    asset stake_cpu(1000, CORE_SYMBOL);
    asset buy_ram = quantity - stake_net - stake_cpu;
    check(buy_ram.amount > 0, "Not enough balance to buy ram");

    signup_public_key pubkey = {
        .type = 0,
        .data = pubkey_data,
    };
    key_weight pubkey_weight = {
        .key = pubkey,
        .weight = 1,
    };
    authority owner = authority{
        .threshold = 1,
        .keys = {pubkey_weight},
        .accounts = {},
        .waits = {}
    };
    authority active = authority{
        .threshold = 1,
        .keys = {pubkey_weight},
        .accounts = {},
        .waits = {}
    };
    newaccount new_account = newaccount{
        .creator = _self,
        .name = new_account_name,
        .owner = owner,
        .active = active
    };

    action(
            permission_level{ _self, name("active") },
            name("eosio"),
            name("newaccount"),
            new_account
    ).send();

    action(
            permission_level{ _self, name("active")},
            name("eosio"),
            name("buyram"),
            make_tuple(_self, new_account_name, buy_ram)
    ).send();

    action(
            permission_level{ _self, name("active")},
            name("eosio"),
            name("delegatebw"),
            make_tuple(_self, new_account_name, stake_net, stake_cpu, true)
    ).send();
}