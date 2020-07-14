#ifndef __COMMON_CRYPTO_KERL_H__
#define __COMMON_CRYPTO_KERL_H__

#include <stdint.h>

#include "KeccakHash.h"
#include "ternary/ternary.h"

#define KECCAK_384_RATE 832
#define KECCAK_384_CAPACITY 768
#define KECCAK_384_HASHBITLEN 384
#define KECCAK_384_DELIMITED_SUFFIX 0x01

#define KERL_HASH_TRITS_CHUNK 243
#define KERL_HASH_TRYTES_CHUNK (KERL_HASH_TRITS_CHUNK / TERNARY_TRITS_PER_TRYTE)
#define NUM_HASH_CHUNK_BYTE (KECCAK_384_HASHBITLEN / 8)
#define KERL_HASH_FRAGMENTS 27
#define KERL_KEY_FRAGMENTS (KERL_HASH_TRITS_CHUNK * KERL_HASH_FRAGMENTS)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief initializes the Kerl instance
 *
 * @param[in] kerl a kerl instance
 * @return int 0 on success
 */
int kerl_init(Keccak_HashInstance* const kerl);

/**
 * @brief resets Kerl’s internal state.
 *
 * @param[in] kerl a kerl instance
 * @return int 0 on success
 */
int kerl_reset(Keccak_HashInstance* const kerl);

/**
 * @brief Absorbs a trit array.
 * last trit is zeroed-out, then converted to 384-bits and absorbed by keccak.
 *
 * @param[in] kerl a kerl instance
 * @param[in, out] trit array of trits to be absorbed
 * @param[in] length the size of trit array
 */
void kerl_absorb(Keccak_HashInstance* const kerl, trit_t trits[], size_t length);

/**
 * @brief Squeezes a trit array.
 * Squeeze is done by receiving a 384-bit digest() from keccak.
 *
 * @param[in] kerl a kerl instance
 * @param[in, out] trits array of trits to be squeezed
 */
void kerl_squeeze(Keccak_HashInstance* const kerl, trit_t trits[], size_t length);

#ifdef __cplusplus
}
#endif

#endif
