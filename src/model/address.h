#ifndef __COMMON_MODEL_ADDRESS_H__
#define __COMMON_MODEL_ADDRESS_H__

#include <stdint.h>

#include "ternary/ternary.h"

typedef enum { ADDR_SECURITY_LOW = 1, ADDR_SECURITY_MEDIUM = 2, ADDR_SECURITY_HIGH = 3 } addr_security_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get a 243-trit address from seed, index and security level.
 *
 * @param[in] seed the seed
 * @param[in] index a key index
 * @param[in] security a security level
 * @param[out] address_out a buffer holds address
 * @return int 0 on success
 */
int generate_address_trits(trit_t seed[], uint64_t index, addr_security_t security, trit_t address_out[]);

/**
 * @brief Get a 81-tryte address from seed, index and security level.
 *
 * @param[in] seed the seed
 * @param[in] index a key index
 * @param[in] security a security level
 * @param[out] address_out a buffer holds address
 * @return int 0 on success
 */
int generate_address_trytes(tryte_t seed[], uint64_t index, addr_security_t security, tryte_t address_out[]);

#ifdef __cplusplus
}
#endif

#endif