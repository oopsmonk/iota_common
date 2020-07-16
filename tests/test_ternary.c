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

#define LONG_EXP 565253
#define TRITS_IN -1, 0, 1, 1, 0, 1, 1, 0, -1, -1, 1, 0, 1
#define TRITS_IN_ENC 1, 0, -1, -1, 0, -1, 1, 0, -1, 1, -1, 0, 1, 0, 0, -1, 1, 1, 0
#define TRITS_IN_ENC_LEN 19

#define MAX_TRITS_IN                                                                                                   \
  1, -1, 0, 1, -1, 0, -1, 1, 1, 0, -1, 0, -1, 0, 1, 0, 1, 0, -1, 1, 1, -1, -1, 1, 0, 1, -1, 0, 0, 1, 1, 1, 0, 0, 1, 1, \
      1, -1, 1, -1, 1
#define MAX_TRITS_IN_LEN 41

#define MIN_TRITS_IN                                                                                                \
  1, 0, 0, -1, 1, 0, 1, -1, -1, 0, 1, 0, 1, 0, -1, 0, -1, 0, 1, -1, -1, 1, 1, -1, 0, -1, 1, 0, 0, -1, -1, -1, 0, 0, \
      -1, -1, -1, 1, -1, 1, -1
#define MIN_TRITS_IN_LEN 41

void test_min_trits(void) {
  trit_t trits[] = {TRITS_IN};
  size_t trits_size = sizeof(trits) / sizeof(trit_t);

  TEST_ASSERT_EQUAL_INT(trits_size, min_trits(LONG_EXP));
  TEST_ASSERT_EQUAL_INT(MAX_TRITS_IN_LEN, min_trits(INT64_MAX));
  TEST_ASSERT_EQUAL_INT(MIN_TRITS_IN_LEN, min_trits(INT64_MIN));
}

void test_trit_to_int64(void) {
  trit_t trits[] = {TRITS_IN};
  size_t trits_size = sizeof(trits) / sizeof(trit_t);
  int64_t val = trits_to_int64(trits, trits_size);

  TEST_ASSERT_EQUAL_INT64(LONG_EXP, val);
}

void test_trit_to_int64_max(void) {
  trit_t trits[] = {MAX_TRITS_IN};
  size_t trits_size = sizeof(trits) / sizeof(trit_t);
  int64_t val = trits_to_int64(trits, trits_size);

  TEST_ASSERT_EQUAL_INT64(INT64_MAX, val);
}

void test_trit_to_int64_min(void) {
  trit_t trits[] = {MIN_TRITS_IN};
  size_t trits_size = sizeof(trits) / sizeof(trit_t);
  int64_t val = trits_to_int64(trits, trits_size);

  TEST_ASSERT_EQUAL_INT64(INT64_MIN, val);
}

void test_int64_max_to_trits(void) {
  size_t trits_len_exp = min_trits(INT64_MAX);
  TEST_ASSERT_EQUAL_INT(MAX_TRITS_IN_LEN, trits_len_exp);

  trit_t trits[trits_len_exp];
  trit_t exp[] = {MAX_TRITS_IN};
  int64_to_trits(INT64_MAX, trits);

  TEST_ASSERT_EQUAL_MEMORY(exp, trits, sizeof(trits));
}

void test_int64_min_to_trits(void) {
  size_t trits_len_exp = min_trits(INT64_MIN);
  TEST_ASSERT_EQUAL_INT(MIN_TRITS_IN_LEN, trits_len_exp);

  trit_t trits[trits_len_exp];
  trit_t exp[] = {MIN_TRITS_IN};
  int64_to_trits(INT64_MIN, trits);

  TEST_ASSERT_EQUAL_MEMORY(exp, trits, sizeof(trits));
}

void test_from_int64(void) {
  size_t trits_len_exp = min_trits(LONG_EXP);
  trit_t trits[trits_len_exp];
  trit_t exp[] = {TRITS_IN};
  int64_to_trits(LONG_EXP, trits);

  TEST_ASSERT_EQUAL_MEMORY(exp, trits, sizeof(trits));
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_trits_to_trytes);
  RUN_TEST(test_trytes_to_trits);

  RUN_TEST(test_valid_trytes);

  RUN_TEST(test_min_trits);
  RUN_TEST(test_trit_to_int64);
  RUN_TEST(test_trit_to_int64_max);
  RUN_TEST(test_trit_to_int64_min);
  RUN_TEST(test_from_int64);
  RUN_TEST(test_int64_max_to_trits);
  RUN_TEST(test_int64_min_to_trits);

  return UNITY_END();
}
