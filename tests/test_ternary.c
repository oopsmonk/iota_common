#include <stdio.h>
#include <unity/unity.h>

#include "ternary/ternary.h"

#define TRYTES_IN "AZN9AZN9AZN9AZN9AZN9"
#define EXP                                                                                                            \
  1, 0, 0, -1, 0, 0, -1, -1, -1, 0, 0, 0, 1, 0, 0, -1, 0, 0, -1, -1, -1, 0, 0, 0, 1, 0, 0, -1, 0, 0, -1, -1, -1, 0, 0, \
      0, 1, 0, 0, -1, 0, 0, -1, -1, -1, 0, 0, 0, 1, 0, 0, -1, 0, 0, -1, -1, -1, 0, 0, 0

void test_trits_to_trytes() {
  trit_t trits[] = {EXP};
  tryte_t trytes[20];
  tryte_t exp[] = {TRYTES_IN};
  trits_to_trytes(trits, 60, trytes);
  TEST_ASSERT_EQUAL_MEMORY(exp, trytes, 20);
}

void test_trytes_to_trits() {
  tryte_t trytes[] = {TRYTES_IN};
  trit_t trits[60];
  trit_t exp[] = {EXP};
  trytes_to_trits(trytes, 20, trits);
  TEST_ASSERT_EQUAL_MEMORY(exp, trits, 60);
}

void test_valid_trytes() {
  tryte_t *hash0 = (tryte_t *)"XUERGHWTYRTFUYKFKXURKHMFEVLOIFTTCNTXOGLDPCZ9CJLKHROOPGNAQYFJEPGK9OKUQROUECBAVNXRX";
  TEST_ASSERT(valid_trytes(hash0, 81) == true);

  // hash with lowercases
  tryte_t *hash1 = (tryte_t *)"XUERGHWTYRTFUYKFKXURKHMFEVLOIFTTCNTXOGLDPCZ9cjlkhroopgnaqyfjepgk9okuqrouecbavnxrx";
  TEST_ASSERT(valid_trytes(hash1, 81) == false);

  // hash with invalid tryte
  tryte_t *hash2 = (tryte_t *)"XUERGH3TYRTFUYKFKXURKHMF5VLOIFTTCNTXOGLDPCZ9CJLKHR0OPGNAQYFJEPGK9OKUQROUECBAVNXRX";
  TEST_ASSERT(valid_trytes(hash2, 81) == false);
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_trits_to_trytes);
  RUN_TEST(test_trytes_to_trits);

  RUN_TEST(test_valid_trytes);

  return UNITY_END();
}
