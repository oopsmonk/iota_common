#include <string.h>
#include <unity/unity.h>

#include "libbase58.h"

/**
 * @brief hexadecimal text to a string, ex: "48656c6c6f" -> "Hello"
 *
 * @param str the hex text,
 * @param array output string
 */
void hex_decode_string(const char str[], uint8_t array[]) {
  size_t len = strlen(str) / 2;
  for (size_t i = 0; i < len; i++) {
    uint8_t c = 0;
    if (str[i * 2] >= '0' && str[i * 2] <= '9') {
      c += (str[i * 2] - '0') << 4;
    }
    if ((str[i * 2] & ~0x20) >= 'A' && (str[i * 2] & ~0x20) <= 'F') {
      c += (10 + (str[i * 2] & ~0x20) - 'A') << 4;
    }
    if (str[i * 2 + 1] >= '0' && str[i * 2 + 1] <= '9') {
      c += (str[i * 2 + 1] - '0');
    }
    if ((str[i * 2 + 1] & ~0x20) >= 'A' && (str[i * 2 + 1] & ~0x20) <= 'F') {
      c += (10 + (str[i * 2 + 1] & ~0x20) - 'A');
    }
    array[i] = c;
  }
}

void test_base58_encode() {
  char *en_src = "48656c6c6f20494f544121";
  size_t en_src_len = strlen(en_src);
  uint8_t en_byte[en_src_len / 2];
  hex_decode_string(en_src, en_byte);
  printf("%.*s\n", (int)(en_src_len / 2), en_byte);
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_base58_encode);

  return UNITY_END();
}
