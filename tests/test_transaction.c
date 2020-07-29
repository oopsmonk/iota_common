#include <stdio.h>

#include "models/address.h"
#include "models/balance.h"
#include "models/transaction.h"
#include "unity/unity.h"

void test_inputs() {
  byte_t seed[IOTA_SEED_BYTES];
  byte_t addr_tmp[IOTA_ADDRESS_BYTES];
  // new seed
  random_seed(seed);

  // transaction inputs
  inputs_t *in = transaction_inputs_new();
  get_address(addr_tmp, seed, 0, ADDRESS_VER_ED25519);
  transaction_inputs_push(in, addr_tmp);

  get_address(addr_tmp, seed, 1, ADDRESS_VER_ED25519);
  transaction_inputs_push(in, addr_tmp);

  get_address(addr_tmp, seed, 2, ADDRESS_VER_ED25519);
  transaction_inputs_push(in, addr_tmp);

  TEST_ASSERT_EQUAL_UINT32(3, transaction_inputs_len(in));
  TEST_ASSERT_EQUAL_MEMORY(addr_tmp, transaction_inputs_at(in, 2), IOTA_ADDRESS_BYTES);
  get_address(addr_tmp, seed, 0, ADDRESS_VER_ED25519);
  TEST_ASSERT_EQUAL_MEMORY(addr_tmp, transaction_inputs_at(in, 0), IOTA_ADDRESS_BYTES);

  transaction_inputs_free(in);
}

void test_outputs() {
  byte_t seed[IOTA_SEED_BYTES];
  // byte_t addr_tmp[IOTA_ADDRESS_BYTES];
  output_t tmp_out;
  // new seed
  random_seed(seed);

  outputs_t *tx_outs = transaction_outputs_new();
  // init and add output object to output list
  get_address(tmp_out.address, seed, 0, ADDRESS_VER_ED25519);
  balance_init(&(tmp_out.balance), NULL, 100);
  transaction_outputs_push(tx_outs, &tmp_out);

  get_address(tmp_out.address, seed, 1, ADDRESS_VER_ED25519);
  balance_init(&(tmp_out.balance), NULL, 200);
  transaction_outputs_push(tx_outs, &tmp_out);

  TEST_ASSERT_EQUAL_UINT32(2, transaction_outputs_len(tx_outs));
  output_t *o = transaction_outputs_at(tx_outs, 5);
  TEST_ASSERT_NULL(o);
  o = transaction_outputs_at(tx_outs, 1);
  TEST_ASSERT_EQUAL_INT64(tmp_out.balance.value, o->balance.value);
  TEST_ASSERT_EQUAL_MEMORY(tmp_out.balance.color, o->balance.color, BALANCE_COLOR_LEN);
  TEST_ASSERT_EQUAL_MEMORY(tmp_out.address, o->address, IOTA_ADDRESS_BYTES);

  transaction_outputs_free(tx_outs);
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_inputs);
  RUN_TEST(test_outputs);

  return UNITY_END();
}