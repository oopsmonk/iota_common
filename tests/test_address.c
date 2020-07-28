#include <stdio.h>
#include <unity/unity.h>

#include "models/address.h"

void test_address_gen() {
  uint8_t iota_seed[IOTA_SEED_BYTES];
  uint8_t ed25519_addr[IOTA_ADDRESS_BYTES] = {0};
  char ed25519_addr_str[IOTA_ADDRESS_STR_LEN] = {0};
  // random_seed(iota_seed);
  seed_from_string(iota_seed, "7rxy9mMdYKjcqh4V1xHRvFK2FRMieRgzzt4txA2m8Hqq");
  size_t len = IOTA_ADDRESS_STR_LEN;
  seed_2_string(ed25519_addr_str, &len, iota_seed);
  printf("seed: %s\n", ed25519_addr_str);

  get_address(ed25519_addr, iota_seed, 0, ADDRESS_VER_ED25519);
  address_2_string(ed25519_addr_str, ed25519_addr);
  printf("addr: %s\n", ed25519_addr_str);

  uint32_t data_len = 4;
  uint8_t signature[ED_SIGNATURE_BYTES + data_len];
  uint8_t data[4] = {1, 3, 3, 8};
  sign_signature(signature, iota_seed, 7, data, data_len);
  // printf("sign: ");
  // dump_hex(signature, ED_SIGNATURE_BYTES+data_len);

  printf("verify: %d\n", sign_verify_signature(iota_seed, 7, signature, data, data_len));
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_address_gen);

  return UNITY_END();
}
