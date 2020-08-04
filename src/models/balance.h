#ifndef __MODELS_BALANCE_H__
#define __MODELS_BALANCE_H__

#include <stdbool.h>
#include <stdint.h>

#include "models/types.h"

// Color represents a marker that is associated to a token balance and that gives it a certain "meaning". The zero value
// represents "vanilla" IOTA tokens but it is also possible to define tokens that represent i.e. real world assets.

#define BALANCE_COLOR_LEN 32

// Balance represents a balance in the IOTA ledger. It consists out of a numeric value and a color.
typedef struct {
  int64_t value;
  byte_t color[BALANCE_COLOR_LEN];
} balance_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Inits a balance object by given value and color.
 *
 * @param[out] balance The balance object
 * @param[in] color The color is optional, NULL for a default value.
 * @param[in] value The value
 */
void balance_init(balance_t* balance, byte_t color[], int64_t value);

/**
 * @brief Inits a balance object from the given bytes.
 *
 * @param[out] balance The balance object
 * @param[in] balance_bytes The balance bytes for serializing to the balance object
 */
void balance_from_bytes(balance_t* balance, byte_t balance_bytes[]);

/**
 * @brief Serialize balance object to bytes
 *
 * @param[out] balance_bytes A buffer holds bytes data
 * @param[in] balance The balance object to be serialized
 */
void balance_2_bytes(byte_t balance_bytes[], balance_t* balance);

/**
 * @brief Sets color to a balance object.
 *
 * @param[out] balance the balance object
 * @param[in] color The color bytes to be set
 */
void balance_set_color(balance_t* balance, byte_t color[]);

/**
 * @brief print out a balance object
 *
 * @param[in] balance A balance object.
 */
void print_balance(balance_t* balance);

#ifdef __cplusplus
}
#endif

#endif