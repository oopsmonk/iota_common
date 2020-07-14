#include <unity/unity.h>

#include "crypto/kerl/converter.h"
#include "crypto/kerl/kerl.h"
#include "ternary/ternary.h"

void test_identity(tryte_t trytes[]) {
  trit_t trits_in[KERL_HASH_TRITS_CHUNK] = {0};
  trit_t trits_out[KERL_HASH_TRITS_CHUNK] = {0};
  uint8_t bytes[NUM_KERL_HASH_BYTES] = {0};

  trytes_to_trits(trytes, KERL_HASH_TRYTES_CHUNK, trits_in);
  trits_in[KERL_HASH_TRITS_CHUNK - 1] = 0;

  kerl_trits_to_bytes(trits_in, bytes);
  kerl_bytes_to_trits(bytes, trits_out);

  TEST_ASSERT_EQUAL_MEMORY(trits_in, trits_out, KERL_HASH_TRITS_CHUNK * sizeof(trit_t));
}

void bt(uint8_t bytes_in[], tryte_t expected[]) {
  uint8_t bytes[NUM_KERL_HASH_BYTES] = {0};
  trit_t trits[KERL_HASH_TRITS_CHUNK] = {0};
  tryte_t trytes[KERL_HASH_TRYTES_CHUNK] = {0};

  memcpy(bytes, bytes_in, NUM_KERL_HASH_BYTES);
  kerl_bytes_to_trits(bytes, trits);
  trits_to_trytes(trits, KERL_HASH_TRITS_CHUNK, trytes);

  TEST_ASSERT_EQUAL_MEMORY(trytes, expected, KERL_HASH_TRYTES_CHUNK * sizeof(tryte_t));
}

void test_trits_all_bytes(void) {
  uint32_t i = 0;
  uint8_t bytes[NUM_KERL_HASH_BYTES] = {0};
  trit_t trits[KERL_HASH_TRITS_CHUNK] = {0};
  trit_t norm_trits[KERL_HASH_TRITS_CHUNK] = {0};
  tryte_t trytes[KERL_HASH_TRYTES_CHUNK] = {0};

  for (i = 0; i < 0xff; i++) {
    memset(bytes, i, NUM_KERL_HASH_BYTES);
    kerl_bytes_to_trits(bytes, trits);
    trits_to_trytes(trits, KERL_HASH_TRITS_CHUNK, trytes);
    kerl_trits_to_bytes(trits, bytes);
    kerl_bytes_to_trits(bytes, norm_trits);
    trits_to_trytes(norm_trits, KERL_HASH_TRITS_CHUNK, trytes);

    TEST_ASSERT_EQUAL_MEMORY(trits, norm_trits, KERL_HASH_TRITS_CHUNK * sizeof(trit_t));
  }
}

void test_trits_bytes_trits(void) {
  test_identity((tryte_t*)"999999999999999999999999999999999999999999999999999999999999999999999999999999999");
  test_identity((tryte_t*)"ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ");
  test_identity((tryte_t*)"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
  test_identity((tryte_t*)"MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
  test_identity((tryte_t*)"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN");
  test_identity((tryte_t*)"SCYLJDWIM9LIXCSLETSHLQOOFDKYOVFZLAHQYCCNMYHRTNIKBZRIRACFYPOWYNSOWDNXFZUG9OEOZPOTD");
}

void test_bytes_trits(void) {
  uint8_t bytes[NUM_KERL_HASH_BYTES];

  memset(bytes, 0, NUM_KERL_HASH_BYTES);
  bt(bytes, (tryte_t*)"999999999999999999999999999999999999999999999999999999999999999999999999999999999");

  memset(bytes, 32, NUM_KERL_HASH_BYTES);
  bt(bytes, (tryte_t*)"FKMPGCDVPEYWPGTBVRFDVVRURXFHVDPGHBTEWHEBDCKOL9AVTISEFCWMDHTUBWBOFPSQERRDQ9MFGFINB");

  memset(bytes, 127, NUM_KERL_HASH_BYTES);
  bt(bytes, (tryte_t*)"LWWOYBGUIARWDZWMLWORYDNDMTEXKSWLW9HPHYPZW9GABECSCPBFOTVTBRUUNVPBVXYNGAVMKONVGABBX");

  memset(bytes, 128, NUM_KERL_HASH_BYTES);
  bt(bytes, (tryte_t*)"NDDLBYTFRZIDWADNODLIBWMWNGVCPHDOD9SKSBKAD9TZYVXHXKYULGEGYIFFMEKYECBMTZENPLMETZYYC");

  memset(bytes, 220, NUM_KERL_HASH_BYTES);
  bt(bytes, (tryte_t*)"KEBSORVSJYXMUTVPUAYYBY9LXXSTMHTDQXFNSAFUPMKSRJWNUPXKSQH9ABNIRHWYUWVNNKYRAXGGGCUIY");

  memset(bytes, 255, NUM_KERL_HASH_BYTES);
  bt(bytes, (tryte_t*)"Z99999999999999999999999999999999999999999999999999999999999999999999999999999999");
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_trits_all_bytes);
  RUN_TEST(test_trits_bytes_trits);
  RUN_TEST(test_bytes_trits);

  return UNITY_END();
}
