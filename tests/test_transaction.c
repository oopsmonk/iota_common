
#include <stdio.h>
#include <string.h>
#include <unity/unity.h>

#include "model/transaction.h"

void test_tx() {
  iota_transaction_t tx;
  transaction_reset(&tx);
  TEST_ASSERT_EQUAL_INT64(0, tx.value);
  TEST_ASSERT_EQUAL_UINT64(0, tx.timestamp);
  TEST_ASSERT_EQUAL_UINT64(0, tx.current_index);
  TEST_ASSERT_EQUAL_UINT64(0, tx.last_index);
  TEST_ASSERT_EQUAL_UINT64(0, tx.attachment_timestamp);
  TEST_ASSERT_EQUAL_UINT64(0, tx.attachment_timestamp_lower);
  TEST_ASSERT_EQUAL_UINT64(0, tx.attachment_timestamp_upper);
  TEST_ASSERT_TRUE(is_empty_trytes(tx.hash, NUM_TRYTES_HASH));
  TEST_ASSERT_TRUE(is_empty_trytes(tx.sig_msg_fragment, NUM_TRYTES_SIG_MSG));
  TEST_ASSERT_TRUE(is_empty_trytes(tx.address, NUM_TRYTES_ADDRESS));
  TEST_ASSERT_TRUE(is_empty_trytes(tx.obsolete_tag, NUM_TRYTES_OBSOLETE_TAG));
  TEST_ASSERT_TRUE(is_empty_trytes(tx.bundle, NUM_TRYTES_BUNDLE));
  TEST_ASSERT_TRUE(is_empty_trytes(tx.trunk, NUM_TRYTES_TRUNK));
  TEST_ASSERT_TRUE(is_empty_trytes(tx.branch, NUM_TRYTES_BRANCH));
  TEST_ASSERT_TRUE(is_empty_trytes(tx.tag, NUM_TRYTES_TAG));
  TEST_ASSERT_TRUE(is_empty_trytes(tx.nonce, NUM_TRYTES_NONCE));
}

void test_tx_array() {
  iota_transaction_t *tx = NULL;
  tx = (iota_transaction_t *)malloc(sizeof(iota_transaction_t));
  transaction_reset(tx);

  transaction_array_t *tx_list = transaction_array_new();
  for (size_t i = 0; i < 10; i++) {
    tx->value = (int64_t)i;
    transaction_array_push(tx_list, tx);
  }
  free(tx);

  iota_transaction_t *tmp_tx = NULL;
  for (int64_t i = 0; i < 10; i++) {
    tmp_tx = transaction_array_at(tx_list, i);
    TEST_ASSERT_EQUAL_INT64(i, tmp_tx->value);
  }

  transaction_array_free(tx_list);
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_tx);
  RUN_TEST(test_tx_array);

  return UNITY_END();
}