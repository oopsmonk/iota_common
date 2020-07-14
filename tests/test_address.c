#include <stdio.h>
#include <unity/unity.h>

#include "model/address.h"
#include "model/transaction.h"

void test_address_gen_trytes() {
  tryte_t const* const SEED =
      (tryte_t*)"ABCDEFGHIJKLMNOPQRSTUVWXYZ9ABCDEFGHIJKLMNOPQRSTUVWXYZ9ABCDEFGHIJKLMNOPQRSTUVWXYZ9";
  tryte_t const* const EX_ADD_0_1 =
      (tryte_t*)"CFOYUCXLHLSUBAEYOTAWUNRPJFA9TSJNLBFLMZQASPTVCMTFBOQQRGGQ9MRZCJWYGBORJZQWVSBLVKBVW";
  tryte_t const* const EX_ADD_2_2 =
      (tryte_t*)"TZZUOMKXUUIIAJEQJJRIJQKWQVYK9YPFNWWUUHDQWVVWIBWHC9J9FJJEFZKOZZAIMUDDGHOIWTIWCOHGD";
  tryte_t const* const EX_ADD_2_3 =
      (tryte_t*)"MLAUELWJHZ9QBPCIYLOXAWCVSZTK9XUEIWQSRLFDWEORDOLVOMOF9RUMFXSAMYWCGXDAVXZMRWQOJH9RY";

  tryte_t addr[NUM_TRYTES_ADDRESS];

  if (generate_address_trytes((tryte_t*)SEED, 0, ADDR_SECURITY_LOW, addr)) {
    printf("gen address failed\n");
  } else {
    printf("address low: %.*s\n", NUM_TRYTES_ADDRESS, addr);
    TEST_ASSERT_EQUAL_MEMORY(addr, EX_ADD_0_1, NUM_TRYTES_ADDRESS);
  }

  if (generate_address_trytes((tryte_t*)SEED, 2, ADDR_SECURITY_MEDIUM, addr)) {
    printf("gen address failed\n");
  } else {
    printf("address medium: %.*s\n", NUM_TRYTES_ADDRESS, addr);
    TEST_ASSERT_EQUAL_MEMORY(addr, EX_ADD_2_2, NUM_TRYTES_ADDRESS);
  }
  if (generate_address_trytes((tryte_t*)SEED, 2, ADDR_SECURITY_HIGH, addr)) {
    printf("gen address failed\n");
  } else {
    printf("address high: %.*s\n", NUM_TRYTES_ADDRESS, addr);
    TEST_ASSERT_EQUAL_MEMORY(addr, EX_ADD_2_3, NUM_TRYTES_ADDRESS);
  }
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_address_gen_trytes);

  return UNITY_END();
}
