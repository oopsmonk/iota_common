#ifndef __COMMON_CRYPTO_SIGNING_H__
#define __COMMON_CRYPTO_SIGNING_H__

#include "crypto/kerl/kerl.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Gets subseed from given a seed and a key index(address index).
 *
 * @param[in] kerl a keccak instance
 * @param[in] seed the seed for the sponge function
 * @param[in] key_idx the key index
 * @param[out] subseed_out a subseed from sponge function
 * @return int 0 on success
 */
int kerl_subseed(Keccak_HashInstance* kerl, trit_t const seed[], uint64_t key_idx, trit_t subseed_out[]);

/**
 * @brief Generats private key
 *
 * @param[in] kerl a keccake instance
 * @param[in] subseed the subseed from kerl_subseed()
 * @param[in, out] key a buffer holds private key
 * @param[in] key_length the length of private key
 * @return int 0 on success
 */
int kerl_key(Keccak_HashInstance* kerl, trit_t subseed[], trit_t key[], size_t key_length);

/**
 * @brief Digests hashes each segment of each key fragment 26 times and returns them.
 *
 * @param[in] kerl a keccak instance
 * @param[in] key the private key
 * @param[in] key_length the length of private key
 * @param[out] digest output digest from sponge
 * @return int 0 on success
 */
int kerl_key_digest(Keccak_HashInstance* kerl, trit_t key[], size_t key_length, trit_t digest[]);

/**
 * @brief Generates the address trits from the given digests.
 *
 * @param[in] kerl a keccak instance
 * @param[in] digest the digest trits
 * @param[in] digest_len length of digest trits
 * @param[out] address_out output address from sponge
 * @return int 0 on success
 */
int kerl_address(Keccak_HashInstance* kerl, trit_t digest[], size_t digest_len, trit_t address_out[]);

#ifdef __cplusplus
}
#endif

#endif