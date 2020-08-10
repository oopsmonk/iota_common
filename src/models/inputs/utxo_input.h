#ifndef __MODELS_INPUTS_UTXO_INPUT_H__
#define __MODELS_INPUTS_UTXO_INPUT_H__

#include <stdint.h>

#include "models/types.h"

typedef struct {
  input_t type;              // Set to value 0 to denote a UTXO Input.
  byte_t tx_id[64];          // The transaction reference from which the UTXO comes from.
  uint64_t tx_output_index;  // The index of the output on the referenced transaction to consume.
} utxo_input_t;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif