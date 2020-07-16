#ifndef __COMMON_CRYPTO_SIGNING_H__
#define __COMMON_CRYPTO_SIGNING_H__

#include "crypto/kerl/kerl.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Gets subseed from given a seed and a key index(address index).
 *
 * @param[in] kerl A keccak instance
 * @param[in] seed The seed for the sponge function
 * @param[in] key_idx A key index
 * @param[out] subseed_out A buffer holds the output subseed
 * @return int 0 on success
 */
int kerl_subseed(Keccak_HashInstance* kerl, trit_t const seed[], uint64_t key_idx, trit_t subseed_out[]);

/**
 * @brief Generats private key
 *
 * @param[in] kerl A keccake instance
 * @param[in] subseed The subseed from kerl_subseed()
 * @param[in, out] key A buffer holds the private key
 * @param[in] key_length The length of private key
 * @return int 0 on success
 */
int kerl_key(Keccak_HashInstance* kerl, trit_t subseed[], trit_t key[], size_t key_length);

/**
 * @brief Digests hashes each segment of each key fragment 26 times and returns them.
 *
 * @param[in] kerl A keccak instance
 * @param[in] key A private key
 * @param[in] key_length The length of private key
 * @param[out] digest A buffer holds the output digest
 * @return int 0 on success
 */
int kerl_key_digest(Keccak_HashInstance* kerl, trit_t key[], size_t key_length, trit_t digest[]);

/**
 * @brief Generates the address trits from the given digests.
 *
 * @param[in] kerl A keccak instance
 * @param[in] digest A digest trits
 * @param[in] digest_len The length of digest trits
 * @param[out] address_out A buffer holds the output address
 * @return int 0 on success
 */
int kerl_address(Keccak_HashInstance* kerl, trit_t digest[], size_t digest_len, trit_t address_out[]);

/**
 * @brief Signs a 243-trit address, according to the given seed, index and security level.
 *
 * @param[in] seed A seed
 * @param[in] index A key index
 * @param[in] security A security level
 * @param[out] address_out A buffer holds address
 * @return int 0 on success
 */
int sign_address_gen_trits(trit_t seed[], uint64_t index, uint8_t security, trit_t address_out[]);

/**
 * @brief Gets the signature in trits
 *
 * @param[in] seed A seed
 * @param[in] index A key index
 * @param[in] security A security level
 * @param[in] bundle_hash A bundle hash
 * @param[out] out_signature A buffer holds signature
 * @return int 0 on success
 */
int sign_signature_gen_trits(trit_t seed[], size_t index, uint8_t security, trit_t bundle_hash[],
                             trit_t out_signature[]);

/**
 * @brief Get the signature in trytes
 *
 * @param[in] seed A seed
 * @param[in] index A key index
 * @param[in] security A security level
 * @param[in] bundle_hash A bundle hash
 * @param[out] out_signature A buffer holds signature
 * @return int 0 on success
 */
int sign_signature_gen_trytes(tryte_t seed[], size_t index, uint8_t security, tryte_t bundle_hash[],
                              tryte_t out_signature[]);

#ifdef __cplusplus
}
#endif

#endif