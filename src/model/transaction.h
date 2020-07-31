
#ifndef __COMMON_MODEL_TRANSACTION_H__
#define __COMMON_MODEL_TRANSACTION_H__

#include "ternary/ternary.h"
#include "utarray.h"

#define NUM_TRYTES_SERIALIZED_TRANSACTION 2673
#define NUM_TRYTES_SIG_MSG 2187
#define NUM_TRYTES_ADDRESS 81
#define NUM_TRYTES_VALUE 27
#define NUM_TRYTES_OBSOLETE_TAG 27
#define NUM_TRYTES_TIMESTAMP 9
#define NUM_TRYTES_CURRENT_INDEX 9
#define NUM_TRYTES_LAST_INDEX 9
#define NUM_TRYTES_BUNDLE 81
#define NUM_TRYTES_TRUNK 81
#define NUM_TRYTES_BRANCH 81
#define NUM_TRYTES_TAG 27
#define NUM_TRYTES_ATTACHMENT_TIMESTAMP 9
#define NUM_TRYTES_ATTACHMENT_TIMESTAMP_LOWER 9
#define NUM_TRYTES_ATTACHMENT_TIMESTAMP_UPPER 9
#define NUM_TRYTES_NONCE 27
#define NUM_TRYTES_HASH 81
#define NUM_TRYTES_CHECKSUM 9

#define NUM_TRITS_SERIALIZED_TRANSACTION (NUM_TRYTES_SERIALIZED_TRANSACTION * TERNARY_TRITS_PER_TRYTE)
#define NUM_TRITS_SIG_MSG (NUM_TRYTES_SIGNATURE * TERNARY_TRITS_PER_TRYTE)
#define NUM_TRITS_ADDRESS (NUM_TRYTES_ADDRESS * TERNARY_TRITS_PER_TRYTE)
#define NUM_TRITS_VALUE (NUM_TRYTES_VALUE * TERNARY_TRITS_PER_TRYTE)
#define NUM_TRITS_OBSOLETE_TAG (NUM_TRYTES_OBSOLETE_TAG * TERNARY_TRITS_PER_TRYTE)
#define NUM_TRITS_TIMESTAMP (NUM_TRYTES_TIMESTAMP * TERNARY_TRITS_PER_TRYTE)
#define NUM_TRITS_CURRENT_INDEX (NUM_TRYTES_CURRENT_INDEX * TERNARY_TRITS_PER_TRYTE)
#define NUM_TRITS_LAST_INDEX (NUM_TRYTES_LAST_INDEX * TERNARY_TRITS_PER_TRYTE)
#define NUM_TRITS_BUNDLE (NUM_TRYTES_BUNDLE * TERNARY_TRITS_PER_TRYTE)
#define NUM_TRITS_TRUNK (NUM_TRYTES_TRUNK * TERNARY_TRITS_PER_TRYTE)
#define NUM_TRITS_BRANCH (NUM_TRYTES_BRANCH * TERNARY_TRITS_PER_TRYTE)
#define NUM_TRITS_TAG (NUM_TRYTES_TAG * TERNARY_TRITS_PER_TRYTE)
#define NUM_TRITS_ATTACHMENT_TIMESTAMP (NUM_TRYTES_ATTACHMENT_TIMESTAMP * TERNARY_TRITS_PER_TRYTE)
#define NUM_TRITS_ATTACHMENT_TIMESTAMP_LOWER (NUM_TRYTES_ATTACHMENT_TIMESTAMP_LOWER * TERNARY_TRITS_PER_TRYTE)
#define NUM_TRITS_ATTACHMENT_TIMESTAMP_UPPER (NUM_TRYTES_ATTACHMENT_TIMESTAMP_UPPER * TERNARY_TRITS_PER_TRYTE)
#define NUM_TRITS_NONCE (NUM_TRYTES_NONCE * TERNARY_TRITS_PER_TRYTE)
#define NUM_TRITS_HASH (NUM_TRYTES_HASH * TERNARY_TRITS_PER_TRYTE)
#define NUM_TRITS_CHECKSUM (NUM_TRYTES_CHECKSUM * TERNARY_TRITS_PER_TRYTE)

/**
 * @brief Transaction object
 *
 */
typedef struct {
  int64_t value;
  uint64_t timestamp;
  uint64_t current_index;
  uint64_t last_index;
  uint64_t attachment_timestamp;
  uint64_t attachment_timestamp_lower;
  uint64_t attachment_timestamp_upper;
  tryte_t hash[NUM_TRYTES_HASH];                /**< hash iota_transaction_t#hash. */
  tryte_t sig_msg_fragment[NUM_TRYTES_SIG_MSG]; /**< signature and message fragment
                                                     iota_transaction_t#sig_msg_fragment. */
  tryte_t address[NUM_TRYTES_ADDRESS];          /**< address iota_transaction_t#address. */
  tryte_t obsolete_tag[NUM_TRYTES_OBSOLETE_TAG];
  tryte_t bundle[NUM_TRYTES_BUNDLE];
  tryte_t trunk[NUM_TRYTES_TRUNK];
  tryte_t branch[NUM_TRYTES_BRANCH];
  tryte_t tag[NUM_TRYTES_TAG];
  tryte_t nonce[NUM_TRYTES_NONCE];
} iota_transaction_t;

typedef enum {
  TX_FIELD_HASH,
  TX_FIELD_SIG_MSG,
  TX_FIELD_ADDRESS,
  TX_FIELD_VALUE,
  TX_FIELD_OBSOLETE_TAG,
  TX_FIELD_TIMESTAMP,
  TX_FIELD_CURR_INDEX,
  TX_FIELD_LAST_INDEX,
  TX_FIELD_BUNDLE,
  TX_FIELD_TRUNK,
  TX_FIELD_BRANCH,
  TX_FIELD_TAG,
  TX_FIELD_ATT_TIMESTAMP,
  TX_FIELD_ATT_TIME_LOWER,
  TX_FIELD_ATT_TIME_UPPER,
  TX_FIELD_NONCE
} transaction_field;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Gets A trytes field from a transaction object
 *
 * @param[in] tx a transaction object
 * @param[in] tx_field transaction field
 * @return tryte_t* a pointer to the filed
 */
tryte_t const *transaction_get_trytes(iota_transaction_t const *const tx, transaction_field tx_field);

/**
 * @brief Sets a transaction trytes field
 *
 * @param[in] tx a transaction object
 * @param[in] tx_field transaction field
 * @param[in] trytes tryte buffer
 * @return int 0 on success
 */
int transaction_set_trytes(iota_transaction_t *const tx, transaction_field tx_field, tryte_t trytes[]);

/**
 * @brief Sets all transaction trytes fields to '9's and number fields to zero.
 *
 * @param[in] tx a transaction object
 */
void transaction_reset(iota_transaction_t *const tx);

/**
 * @brief print out transaction object
 *
 * @param[in] tx a transaction object
 */
void transaction_printf(iota_transaction_t *const tx);

typedef UT_array transaction_array_t;
static UT_icd const ut_transactions_icd = {sizeof(iota_transaction_t), NULL, NULL, NULL};

/**
 * @brief allocats a transaction list
 *
 * @return transaction_array_t*
 */
static inline transaction_array_t *transaction_array_new() {
  transaction_array_t *txs = NULL;
  utarray_new(txs, &ut_transactions_icd);
  return txs;
}

/**
 * @brief Appends a transaction to the transaction list
 *
 * @param[in] txs A transaction list object
 * @param[in] tx A transaction object
 */
static inline void transaction_array_push(transaction_array_t *txs, iota_transaction_t const *const tx) {
  utarray_push_back(txs, tx);
}

/**
 * @brief Gets the size of list
 *
 * @param[in] txs A transaction list object
 * @return size_t
 */
static inline size_t transaction_array_len(transaction_array_t *txs) { return utarray_len(txs); }

/**
 * @brief Free a transaction list
 *
 * @param[in] txs A transaction list object
 */
static inline void transaction_array_free(transaction_array_t *txs) { utarray_free(txs); }

/**
 * @brief Gets a transaction by index, return NULL if index > transaction_array_len
 *
 * @param[in] txs A transaction list object
 * @param[in] index transaction index
 * @return iota_transaction_t*
 */
static inline iota_transaction_t *transaction_array_at(transaction_array_t *txs, size_t index) {
  // return NULL if not found.
  return (iota_transaction_t *)utarray_eltptr(txs, index);
}

#define TX_OBJS_FOREACH(txs, tx) \
  for (tx = (iota_transaction_t *)utarray_front(txs); tx != NULL; tx = (iota_transaction_t *)utarray_next(txs, tx))

#ifdef __cplusplus
}
#endif

#endif