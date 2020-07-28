#ifndef __MODELS_ADDRESS_H__
#define __MODELS_ADDRESS_H__

#include <stdbool.h>

#include "models/types.h"
#include "sodium.h"

// the length of an address (digest length = 32 + version byte length = 1).
#define IOTA_ADDRESS_BYTES 33
#define IOTA_ADDRESS_STR_LEN 48
#define IOTA_SEED_BYTES crypto_sign_ed25519_SEEDBYTES

#define ED_PUBLIC_KEY_BYTES crypto_sign_ed25519_PUBLICKEYBYTES
#define ED_PRIVATE_KEY_BYTES crypto_sign_ed25519_SECRETKEYBYTES
#define ED_SIGNATURE_BYTES crypto_sign_ed25519_BYTES
#define ED_DIGEST_BYTES 32

// address signature version
typedef enum { ADDRESS_VER_WOTS = 0, ADDRESS_VER_ED25519 = 1 } address_version_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Gets a random seed.
 *
 * @param[out] seed An output seed
 */
void random_seed(uint8_t seed[]);

/**
 * @brief Gets a human readable version of the Seed (base58 encoded).
 *
 * @param[out] str_buf The seed string
 * @param[in, out] buf_len The len of string
 * @param[in] seed The seed in bytes
 * @return true
 * @return false
 */
bool seed_2_string(char str_buf[], size_t *buf_len, uint8_t seed[]);

/**
 * @brief Gets seed bytes from a human readable seed string.
 *
 * @param[out] out_seed seed in bytes array
 * @param[in] str the seed string
 * @return true
 * @return false
 */
bool seed_from_string(uint8_t out_seed[], const char *str);

/**
 * @brief Gets the address from corresponding seed and index
 *
 * @param[out] addr_out An address
 * @param[in] seed The seed for genrate address
 * @param[in] index The index of address
 * @param[in] version The address signature version
 */
void get_address(uint8_t addr_out[], uint8_t seed[], uint64_t index, address_version_t version);

/**
 * @brief Gets a human readable version of the address (base58 encoded).
 *
 * @param[out] str_buf A buffer holds string address
 * @param[in] address An address in bytes
 * @return true
 * @return false
 */
bool address_2_string(char str_buf[], uint8_t address[]);

/**
 * @brief signs data/message and returns the signature.
 *
 * @param[out] signature The signed signature.
 * @param[in] seed The seed
 * @param[in] index The index of address
 * @param[in] data The message or data
 * @param[in] data_len The length of data
 */
void sign_signature(uint8_t signature[], uint8_t seed[], uint64_t index, uint8_t data[], uint64_t data_len);

bool sign_verify_signature(uint8_t seed[], uint64_t index, uint8_t signature[], uint8_t data[], size_t data_len);

void dump_hex(uint8_t data[], size_t len);

#ifdef __cplusplus
}
#endif

#endif