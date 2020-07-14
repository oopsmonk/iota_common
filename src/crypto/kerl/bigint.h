
#ifndef __COMMON_CRYPTO_KERL_BIGINT_H_
#define __COMMON_CRYPTO_KERL_BIGINT_H_

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief NOT operator
 *
 * @param[in, out] bigint A bigint array
 * @param[in] len the length of bigint
 */
void bigint_not(uint32_t bigint[], size_t len);

size_t bigint_add_small(uint32_t biging[], uint32_t value);
void bigint_add(uint32_t base[], uint32_t const rh[], size_t len);
void bigint_sub(uint32_t base[], uint32_t const rh[], size_t len);
int8_t bigint_cmp(uint32_t const lh[], uint32_t const rh[], size_t len);

#ifdef __cplusplus
}
#endif

#endif
