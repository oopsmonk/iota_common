#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "model/transaction.h"
#include "ternary/ternary.h"

tryte_t const* transaction_get_trytes(iota_transaction_t const* const tx, transaction_field tx_field) {
  tryte_t const* p = NULL;
  switch (tx_field) {
    case TX_FIELD_HASH:
      p = tx->hash;
      break;
    case TX_FIELD_SIG_MSG:
      p = tx->hash;
      break;
    case TX_FIELD_ADDRESS:
      p = tx->hash;
      break;
    case TX_FIELD_VALUE:
      break;
    case TX_FIELD_OBSOLETE_TAG:
      p = tx->obsolete_tag;
      break;
    case TX_FIELD_TIMESTAMP:
    case TX_FIELD_CURR_INDEX:
    case TX_FIELD_LAST_INDEX:
      break;
    case TX_FIELD_BUNDLE:
      p = tx->bundle;
      break;
    case TX_FIELD_TRUNK:
      p = tx->trunk;
      break;
    case TX_FIELD_BRANCH:
      p = tx->branch;
      break;
    case TX_FIELD_TAG:
      p = tx->tag;
      break;
    case TX_FIELD_ATT_TIMESTAMP:
    case TX_FIELD_ATT_TIME_LOWER:
    case TX_FIELD_ATT_TIME_UPPER:
      break;
    case TX_FIELD_NONCE:
      p = tx->nonce;
      break;
    default:
      break;
  }
  return p;
}

int transaction_set_trytes(iota_transaction_t* const tx, transaction_field tx_field, tryte_t trytes[]) {
  // invalid trytes
  int err = -1;
  switch (tx_field) {
    case TX_FIELD_HASH:
      if (valid_trytes(trytes, NUM_TRYTES_HASH)) {
        memcpy(tx->hash, trytes, NUM_TRYTES_HASH);
        err = 0;
      }
      break;
    case TX_FIELD_SIG_MSG:
      if (valid_trytes(trytes, NUM_TRYTES_SIG_MSG)) {
        memcpy(tx->sig_msg_fragment, trytes, NUM_TRYTES_SIG_MSG);
        err = 0;
      }
      break;
    case TX_FIELD_ADDRESS:
      if (valid_trytes(trytes, NUM_TRYTES_ADDRESS)) {
        memcpy(tx->address, trytes, NUM_TRYTES_ADDRESS);
        err = 0;
      }
      break;
    case TX_FIELD_VALUE:
      // it's not trytes
      err = -2;
      break;
    case TX_FIELD_OBSOLETE_TAG:
      if (valid_trytes(trytes, NUM_TRYTES_OBSOLETE_TAG)) {
        memcpy(tx->obsolete_tag, trytes, NUM_TRYTES_OBSOLETE_TAG);
        err = 0;
      }
      break;
    case TX_FIELD_TIMESTAMP:
    case TX_FIELD_CURR_INDEX:
    case TX_FIELD_LAST_INDEX:
      // it's not trytes
      err = -2;
      break;
    case TX_FIELD_BUNDLE:
      if (valid_trytes(trytes, NUM_TRYTES_BUNDLE)) {
        memcpy(tx->bundle, trytes, NUM_TRYTES_BUNDLE);
        err = 0;
      }
      break;
    case TX_FIELD_TRUNK:
      if (valid_trytes(trytes, NUM_TRYTES_TRUNK)) {
        memcpy(tx->trunk, trytes, NUM_TRYTES_TRUNK);
        err = 0;
      }
      break;
    case TX_FIELD_BRANCH:
      if (valid_trytes(trytes, NUM_TRYTES_BRANCH)) {
        memcpy(tx->branch, trytes, NUM_TRYTES_BRANCH);
        err = 0;
      }
      break;
    case TX_FIELD_TAG:
      if (valid_trytes(trytes, NUM_TRYTES_TAG)) {
        memcpy(tx->tag, trytes, NUM_TRYTES_TAG);
        err = 0;
      }
      break;
    case TX_FIELD_ATT_TIMESTAMP:
    case TX_FIELD_ATT_TIME_LOWER:
    case TX_FIELD_ATT_TIME_UPPER:
      // it's not trytes
      err = -2;
      break;
    case TX_FIELD_NONCE:
      if (valid_trytes(trytes, NUM_TRYTES_NONCE)) {
        memcpy(tx->nonce, trytes, NUM_TRYTES_NONCE);
        err = 0;
      }
      break;
    default:
      break;
  }
  return err;
}

void transaction_reset(iota_transaction_t* const tx) {
  memset(tx, 0, sizeof(iota_transaction_t));
  memset(tx->hash, TERNARY_NULL_TRYTE_CHAR, NUM_TRYTES_HASH);
  memset(tx->sig_msg_fragment, TERNARY_NULL_TRYTE_CHAR, NUM_TRYTES_SIG_MSG);
  memset(tx->address, TERNARY_NULL_TRYTE_CHAR, NUM_TRYTES_ADDRESS);
  memset(tx->obsolete_tag, TERNARY_NULL_TRYTE_CHAR, NUM_TRYTES_OBSOLETE_TAG);
  memset(tx->bundle, TERNARY_NULL_TRYTE_CHAR, NUM_TRYTES_BUNDLE);
  memset(tx->trunk, TERNARY_NULL_TRYTE_CHAR, NUM_TRYTES_TRUNK);
  memset(tx->branch, TERNARY_NULL_TRYTE_CHAR, NUM_TRYTES_BRANCH);
  memset(tx->tag, TERNARY_NULL_TRYTE_CHAR, NUM_TRYTES_TAG);
  memset(tx->nonce, TERNARY_NULL_TRYTE_CHAR, NUM_TRYTES_NONCE);
}

void transaction_printf(iota_transaction_t* const tx) {
  printf("===Transaction===\n");
  printf("address: %.*s\n", NUM_TRYTES_ADDRESS, tx->address);
  printf("value: %" PRId64 "\n", tx->value);
  printf("obsolete tag: %.*s\n", NUM_TRYTES_OBSOLETE_TAG, tx->obsolete_tag);

  printf("timestamp: %" PRId64 "\n", tx->timestamp);
  printf("curr index: %" PRId64 " \nlast index: %" PRId64 "\n", tx->current_index, tx->last_index);

  printf("bundle: %.*s\n", NUM_TRYTES_BUNDLE, tx->bundle);
  printf("trunk: %.*s\n", NUM_TRYTES_TRUNK, tx->trunk);
  printf("branch: %.*s\n", NUM_TRYTES_BRANCH, tx->branch);
  printf("tag: %.*s\n", NUM_TRYTES_TAG, tx->tag);
  printf("attachment_timestamp: %" PRId64 "\n", tx->attachment_timestamp);
  printf("attachment_timestamp_lower: %" PRId64 "\n", tx->attachment_timestamp_lower);
  printf("attachment_timestamp_upper: %" PRId64 "\n", tx->attachment_timestamp_upper);

  printf("nonce: %.*s\n", NUM_TRYTES_NONCE, tx->nonce);
  printf("hash: %.*s\n", NUM_TRYTES_HASH, tx->hash);
  printf("signature and message:\n%.*s\n", NUM_TRYTES_SIG_MSG, tx->sig_msg_fragment);
  printf("=================\n");
}