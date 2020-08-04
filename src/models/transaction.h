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

// The input is a list of addresses in a transaction.
typedef UT_array tx_inputs_t;
static UT_icd const ut_inputs_icd = {sizeof(byte_t) * IOTA_ADDRESS_BYTES, NULL, NULL, NULL};

/**
 * @brief Allocates a transaction input list object.
 *
 * @return tx_inputs_t* a pointer to tx_inputs_t object
 */
static inline tx_inputs_t *transaction_inputs_new() {
  tx_inputs_t *tx_inputs = NULL;
  utarray_new(tx_inputs, &ut_inputs_icd);
  return tx_inputs;
}

/**
 * @brief Appends an input object to the list.
 *
 * @param[in] tx_in The list object
 * @param[in] address An address to be appended to the list.
 */
static inline void transaction_inputs_push(tx_inputs_t *tx_in, byte_t address[]) { utarray_push_back(tx_in, address); }

/**
 * @brief Gets list size
 *
 * @param[in] tx_in A list object
 * @return size_t
 */
static inline size_t transaction_inputs_len(tx_inputs_t *tx_in) { return utarray_len(tx_in); }

/**
 * @brief Frees a transaction input list.
 *
 * @param[in] tx_in A transaction input object.
 */
static inline void transaction_inputs_free(tx_inputs_t *tx_in) { utarray_free(tx_in); }

/**
 * @brief Gets address by index from a transaction list.
 *
 * @param[in] tx_in The transaction input object
 * @param[in] index The index of address
 * @return byte_t* A pointer to the address, NULL if not found.
 */
static inline byte_t *transaction_inputs_at(tx_inputs_t *tx_in, size_t index) {
  // return NULL if not found.
  return (byte_t *)utarray_eltptr(tx_in, index);
}

/**
 * @brief loops transaction input list
 *
 */
#define TX_INPUTS_FOREACH(tx_in, addr) \
  for (addr = (byte_t *)utarray_front(tx_in); addr != NULL; addr = (byte_t *)utarray_next(tx_in, addr))

/**
 * @brief A transaction output object
 *
 */
typedef struct {
  byte_t address[IOTA_ADDRESS_BYTES];
  balance_t balance;
} tx_output_t;

typedef UT_array tx_outputs_t;
static UT_icd const ut_outputs_icd = {sizeof(tx_output_t), NULL, NULL, NULL};

/**
 * @brief Allocates transaction outputs object
 *
 * @return tx_outputs_t* A pointer to the object.
 */
static inline tx_outputs_t *transaction_outputs_new() {
  tx_inputs_t *tx_outputs = NULL;
  utarray_new(tx_outputs, &ut_outputs_icd);
  return tx_outputs;
}

/**
 * @brief Appends an output object to list.
 *
 * @param[in] tx_out The output list object.
 * @param[in] output An output object.
 */
static inline void transaction_outputs_push(tx_outputs_t *tx_out, tx_output_t const *const output) {
  utarray_push_back(tx_out, output);
}

/**
 * @brief Gets length of transaction output list.
 *
 * @param[in] tx_out A transaction output list object.
 * @return size_t
 */
static inline size_t transaction_outputs_len(tx_outputs_t *tx_out) { return utarray_len(tx_out); }

/**
 * @brief Frees a transaction output list
 *
 * @param[in] tx_out
 */
static inline void transaction_outputs_free(tx_outputs_t *tx_out) { utarray_free(tx_out); }

/**
 * @brief Gets an output object from list by given index.
 *
 * @param[in] tx_out A transaction output list object
 * @param[in] index The index of an output object
 * @return tx_output_t*
 */
static inline tx_output_t *transaction_outputs_at(tx_outputs_t *tx_out, size_t index) {
  // return NULL if not found.
  return (tx_output_t *)utarray_eltptr(tx_out, index);
}

/**
 * @brief loops a transaction output list
 *
 */
#define TX_OUTPUTS_FOREACH(tx_out, o) \
  for (o = (tx_output_t *)utarray_front(tx_out); o != NULL; o = (tx_output_t *)utarray_next(tx_out, o))

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
//   tx_inputs_t* inputs;
//   tx_outputs_t* outputs;
//   signature_t* signatures;
//   byte_t* datapayload;  // optional
//
// } transaction_ctx_t;

#ifdef __cplusplus
}
#endif

#endif