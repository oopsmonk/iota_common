#ifndef __COMMON_KERL_CONVERTER_H__
#define __COMMON_KERL_CONVERTER_H__

#include "ternary/ternary.h"

#define UINT32_WIDTH 32
// numer of u32 elements in one bigint array
#define BIGINT_LENGTH 12
// kerl hash in trytes
#define NUM_KERL_HASH_TRYTES 81
#define NUM_KERL_HASH_TRITS (NUM_KERL_HASH_TRYTES * TERNARY_TRITS_PER_TRYTE)
// Kerl hash in bytes, KECCAK_384_HASHBITLEN/8
#define NUM_KERL_HASH_BYTES 48

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Converts a balanced ternary number into a big-endian binary integer.
 *  The input must consist of exactly one 243-trit chunk and is converted into one big-endian 48-byte(384-bit) integer.
 *
 * @param[in] trits a 243-trit array
 * @param[out] bytes a 48-byte int array
 */
void kerl_trits_to_bytes(trit_t trits[], uint8_t bytes[]);

/**
 * @brief Converts a 48-byte integer into a 243-trit number.
 *  The input must consist of exactly one 48-byte integer and is converted into one 243-trit integer.
 *
 * @param[in, out] bytes a 48-byte intger
 * @param[in, out] trits a 243-trit integer
 */
void kerl_bytes_to_trits(uint8_t bytes[], trit_t trits[]);

#ifdef __cplusplus
}
#endif

#endif