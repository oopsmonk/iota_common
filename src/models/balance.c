#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "libbase58.h"
#include "models/balance.h"

bool has_color(balance_t* balance) {
  for (int i = 0; i < BALANCE_COLOR_LEN; i++) {
    if (balance->color[i] != 0) {
      return true;
    }
  }
  return false;
}

bool color_2_string(char color_str[], byte_t color[]) {
  size_t buf_len = 48;
  bool ret = b58enc(color_str, &buf_len, (const void*)color, BALANCE_COLOR_LEN);
  // printf("len %zu, %d\n", buf_len, ret);
  return ret;
}

void balance_init(balance_t* balance, byte_t color[], int64_t value) {
  balance->value = value;
  memset(balance->color, 0, BALANCE_COLOR_LEN);
  if (color) {
    balance_set_color(balance, color);
  }
}

void balance_from_bytes(balance_t* balance, byte_t balance_bytes[]) {
  memcpy(&balance->value, balance_bytes, sizeof(balance->value));
  memcpy(balance->color, balance_bytes + sizeof(balance->value), sizeof(balance->color));
}

void balance_set_color(balance_t* balance, byte_t color[]) { memcpy(balance->color, color, BALANCE_COLOR_LEN); }

void balance_2_bytes(byte_t balance_bytes[], balance_t* balance) {
  // value offset
  int offset = sizeof(balance->value);
  memcpy(balance_bytes, &balance->value, offset);
  memcpy(balance_bytes + offset, balance->color, sizeof(balance->color));
}

void print_balance(balance_t* balance) {
  if (has_color(balance)) {
    char color_str[48];
    color_2_string(color_str, balance->color);
    printf("balance[%" PRId64 ", %s]\n", balance->value, color_str);
  } else {
    printf("balance[%" PRId64 ", IOTA]\n", balance->value);
  }
}