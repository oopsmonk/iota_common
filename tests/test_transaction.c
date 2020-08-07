#include <stdint.h>
#include <stdio.h>

#include "libbase58.h"
#include "models/address.h"
#include "models/balance.h"
#include "models/transaction.h"
#include "unity/unity.h"

void test_transaction_id() {
  byte_t id[TRANSACTION_ID_BYTES];
  char id_str[TRANSACTION_ID_BASE58_LEN];
  size_t str_len = TRANSACTION_ID_BASE58_LEN;
  tx_id_random(id);
  TEST_ASSERT(tx_id_2_base58(id_str, &str_len, id));
  // printf("id: %s\n", id_str);

  byte_t exp_id[TRANSACTION_ID_BYTES];
  size_t id_len = TRANSACTION_ID_BYTES;
  TEST_ASSERT(b58tobin((void *)exp_id, &id_len, id_str, strlen(id_str)));
  TEST_ASSERT_EQUAL_MEMORY(exp_id, id, TRANSACTION_ID_BYTES);
}

void test_inputs() {
  byte_t seed[IOTA_SEED_BYTES];
  byte_t addr_tmp[IOTA_ADDRESS_BYTES];
  byte_t tmp_output_id[OUTPUT_ID_BYTES];
  // new seed
  random_seed(seed);

  // transaction inputs
  tx_inputs_t *in = tx_inputs_new();
  get_address(addr_tmp, seed, 0, ADDRESS_VER_ED25519);
  // set output id
  memcpy(tmp_output_id, addr_tmp, IOTA_ADDRESS_BYTES);
  randombytes_buf((void *const)tmp_output_id + IOTA_ADDRESS_BYTES, TRANSACTION_ID_BYTES);
  tx_inputs_push(in, tmp_output_id);

  get_address(addr_tmp, seed, 1, ADDRESS_VER_ED25519);
  // set output id
  memcpy(tmp_output_id, addr_tmp, IOTA_ADDRESS_BYTES);
  randombytes_buf((void *const)tmp_output_id + IOTA_ADDRESS_BYTES, TRANSACTION_ID_BYTES);
  tx_inputs_push(in, tmp_output_id);

  get_address(addr_tmp, seed, 2, ADDRESS_VER_ED25519);
  // set output id
  memcpy(tmp_output_id, addr_tmp, IOTA_ADDRESS_BYTES);
  randombytes_buf((void *const)tmp_output_id + IOTA_ADDRESS_BYTES, TRANSACTION_ID_BYTES);
  tx_inputs_push(in, tmp_output_id);

  TEST_ASSERT_EQUAL_UINT32(3, tx_inputs_len(in));
  TEST_ASSERT_EQUAL_MEMORY(tmp_output_id, tx_inputs_at(in, 2), OUTPUT_ID_BYTES);
  get_address(addr_tmp, seed, 0, ADDRESS_VER_ED25519);
  TEST_ASSERT_EQUAL_MEMORY(addr_tmp, tx_inputs_at(in, 0), IOTA_ADDRESS_BYTES);

  tx_inputs_print(in);

  tx_inputs_free(in);
}

void test_outputs() {
  byte_t seed[IOTA_SEED_BYTES];
  byte_t color[BALANCE_COLOR_BYTES];
  tx_output_t tmp_out;
  // new seed
  random_seed(seed);

  tx_outputs_t *tx_outs = tx_outputs_new();
  // init and add output object to output list
  get_address(tmp_out.address, seed, 0, ADDRESS_VER_ED25519);
  balance_init(&(tmp_out.balance), NULL, 100);
  tx_outputs_push(tx_outs, &tmp_out);

  get_address(tmp_out.address, seed, 1, ADDRESS_VER_ED25519);
  balance_init(&(tmp_out.balance), NULL, 200);
  tx_outputs_push(tx_outs, &tmp_out);

  get_address(tmp_out.address, seed, 2, ADDRESS_VER_ED25519);
  randombytes_buf((void *const)color, BALANCE_COLOR_BYTES);
  balance_init(&(tmp_out.balance), color, 300);
  tx_outputs_push(tx_outs, &tmp_out);

  TEST_ASSERT_EQUAL_UINT32(3, tx_outputs_len(tx_outs));
  tx_output_t *o = tx_outputs_at(tx_outs, 5);
  TEST_ASSERT_NULL(o);
  o = tx_outputs_at(tx_outs, 2);
  TEST_ASSERT_EQUAL_INT64(tmp_out.balance.value, o->balance.value);
  TEST_ASSERT_EQUAL_MEMORY(tmp_out.balance.color, o->balance.color, BALANCE_COLOR_BYTES);
  TEST_ASSERT_EQUAL_MEMORY(tmp_out.address, o->address, IOTA_ADDRESS_BYTES);

  tx_outputs_print(tx_outs);

  tx_outputs_free(tx_outs);
}

void test_transaction() {
  // get seed
  byte_t seed[IOTA_SEED_BYTES];
  random_seed(seed);

  // get an address

  // output id

  // inputs from output id

  // balance

  // create outputs
  tx_outputs_t *tx_outs = tx_outputs_new();

  // create transaction

  // clean up
  tx_outputs_free(tx_outs);
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_transaction_id);
  RUN_TEST(test_inputs);
  RUN_TEST(test_outputs);
  // RUN_TEST(test_transaction);

  return UNITY_END();
}