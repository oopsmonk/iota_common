
#ifndef __COMMON_TERNARY_H__
#define __COMMON_TERNARY_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t byte_t;
typedef int8_t trit_t;
typedef int8_t tryte_t;

#define TERNARY_BASE 3
#define TERNARY_TRITS_PER_TRYTE 3
#define TERNARY_NULL_TRYTE_CHAR '9'
// 3^3, 9ABCDEFGHIJKLMNOPQRSTUVWXYZ
#define TERNARY_TABLE_SIZE 27

#define TERNARY_TRIT_MIN (-1)
#define TERNARY_TRIT_MAX 1

#define TERNARY_TRYTE_MIN (-13)
#define TERNARY_TRYTE_MAX 13

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Checks if the given trits are valid.
 *
 * @param[in] trits A trits array.
 * @param[in] len The length of trits array.
 * @return true
 * @return false
 */
bool valid_trits(trit_t const trits[], size_t len);

/**
 * @brief Checks if given trytes are valid.
 *
 * @param[in] trytes A tryte array.
 * @param[in] len The length of the tryte array.
 * @return true
 * @return false
 */
bool valid_trytes(tryte_t const trytes[], size_t len);

/**
 * @brief Checks if given trytes are all empty characters ('9's)
 *
 * @param[in] trytes A tryte array
 * @param[in] len The length of the tryte array
 * @return true
 * @return false
 */
bool is_empty_trytes(tryte_t const trytes[], size_t len);

/**
 * @brief the number of trits needed to encode of a given value
 *
 * @param[in] value signed integer to convert
 * @return size_t a number of trits
 */
size_t min_trits(int64_t value);

/**
 * @brief Converts an array of trits to an integer value
 *
 * @param[in] trits an array of trits
 * @param[in] num_trits size of the trits array
 * @return int64_t
 */
int64_t trits_to_int(trit_t const trits[], size_t num_trits);

/**
 * @brief Adds an intger to trits
 *
 * @param[out] trits A trit array
 * @param[in] trit_len the size of trit array
 * @param[in] value The value adds to the given trit array.
 */
void trits_add_int(trit_t trits[], size_t trit_len, int64_t value);

/**
 * @brief Converts trits to trytes
 *
 * @param[in] trits input trits
 * @param[in] trits_len the length of input trits
 * @param[out] trytes output trytes
 * @return int 0 on success
 */
int trits_to_trytes(trit_t trits[], size_t trits_len, tryte_t trytes[]);

/**
 * @brief Converts trytes to trits
 *
 * @param[in] trytes input trytes
 * @param[in] tryte_len the length of input trytes
 * @param[out] trits output trits
 * @return int 0 on success
 */
int trytes_to_trits(tryte_t trytes[], size_t tryte_len, trit_t trits[]);

/**
 * @brief Converts trits to int64
 *
 * @param[in] trits A trits array
 * @param[in] num_trits The length of the trits array
 * @return int64_t
 */
int64_t trits_to_int64(trit_t trits[], size_t num_trits);

/**
 * @brief Converts int64 to a trits array
 *
 * @param[in] value A 64-bit integer
 * @param[out] trits A trits array
 */
void int64_to_trits(int64_t value, trit_t trits[]);

#ifdef __cplusplus
}
#endif

#endif