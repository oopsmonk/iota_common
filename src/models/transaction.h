#ifndef __MODELS_TRANSACTION_H__
#define __MODELS_TRANSACTION_H__

#include <stdint.h>

#include "models/address.h"
#include "models/balance.h"
#include "models/types.h"
#include "utarray.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TRANSACTION_ID_BYTES 32
#define OUTPUT_ID_BYTES (IOTA_ADDRESS_BYTES + TRANSACTION_ID_BYTES)

// input is a list of addresses
typedef UT_array inputs_t;
static UT_icd const ut_inputs_icd = {sizeof(byte_t) * IOTA_ADDRESS_BYTES, NULL, NULL, NULL};
static inline inputs_t *transaction_inputs_new() {
  inputs_t *tx_inputs = NULL;
  utarray_new(tx_inputs, &ut_inputs_icd);
  return tx_inputs;
}
static inline void transaction_inputs_push(inputs_t *tx_in, byte_t address[]) { utarray_push_back(tx_in, address); }
static inline size_t transaction_inputs_len(inputs_t *tx_in) { return utarray_len(tx_in); }
static inline void transaction_inputs_free(inputs_t *tx_in) { utarray_free(tx_in); }
static inline byte_t *transaction_inputs_at(inputs_t *tx_in, size_t index) {
  // return NULL if not found.
  return (byte_t *)utarray_eltptr(tx_in, index);
}

#define TX_INPUTS_FOREACH(tx_in, addr) \
  for (addr = (byte_t *)utarray_front(tx_in); addr != NULL; addr = (byte_t *)utarray_next(tx_in, addr))

typedef struct {
  byte_t address[IOTA_ADDRESS_BYTES];
  balance_t balance;
} output_t;

typedef UT_array outputs_t;
static UT_icd const ut_outputs_icd = {sizeof(output_t), NULL, NULL, NULL};
static inline outputs_t *transaction_outputs_new() {
  inputs_t *tx_outputs = NULL;
  utarray_new(tx_outputs, &ut_outputs_icd);
  return tx_outputs;
}
static inline void transaction_outputs_push(outputs_t *tx_out, output_t const *const output) {
  utarray_push_back(tx_out, output);
}
static inline size_t transaction_outputs_len(outputs_t *tx_out) { return utarray_len(tx_out); }
static inline void transaction_outputs_free(outputs_t *tx_out) { utarray_free(tx_out); }
static inline output_t *transaction_outputs_at(outputs_t *tx_out, size_t index) {
  // return NULL if not found.
  return (output_t *)utarray_eltptr(tx_out, index);
}

#define TX_OUTPUTS_FOREACH(tx_out, o) \
  for (o = (output_t *)utarray_front(tx_out); o != NULL; o = (output_t *)utarray_next(tx_out, o))

// typedef struct {
//   byte_t address[IOTA_ADDRESS_BYTES];
//   byte_t keypair[32];
//   byte_t signature[ED_SIGNATURE_BYTES];
// } signature_t;
//
// typedef struct {
//   byte_t id[32];
//   byte_t essence[1];    // len?
//   byte_t signature[1];  // len?
//   inputs_t* inputs;
//   outputs_t* outputs;
//   signature_t* signatures;
//   byte_t* datapayload;  // optional
//
// } transaction_ctx_t;

#ifdef __cplusplus
}
#endif

#endif