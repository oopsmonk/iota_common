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

void balance_init(balance_t* balance, byte_t color[], int64_t value);
void balance_from_bytes(balance_t* balance, byte_t balance_bytes[]);
void balance_2_bytes(byte_t balance_bytes[], balance_t* balance);

void balance_set_color(balance_t* balance, byte_t color[]);

void print_balance(balance_t* balance);

#ifdef __cplusplus
}
#endif

#endif
