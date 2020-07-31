#include <string.h>

#include "ternary/ternary.h"

#define INDEX_OF_TRYTE(tryte) ((tryte) == '9' ? 0 : ((tryte) - 'A' + 1))

// trit tryte convertion
#define TERNARY_TRYTE_ALPHABET "9ABCDEFGHIJKLMNOPQRSTUVWXYZ"
// lookup table to convert a single tryte into the corresponding three trits
static const trit_t TRYTES_TRITS_LUT[TERNARY_TABLE_SIZE][TERNARY_TRITS_PER_TRYTE] = {
    {0, 0, 0},  {1, 0, 0},  {-1, 1, 0},  {0, 1, 0},  {1, 1, 0},  {-1, -1, 1},  {0, -1, 1},  {1, -1, 1},  {-1, 0, 1},
    {0, 0, 1},  {1, 0, 1},  {-1, 1, 1},  {0, 1, 1},  {1, 1, 1},  {-1, -1, -1}, {0, -1, -1}, {1, -1, -1}, {-1, 0, -1},
    {0, 0, -1}, {1, 0, -1}, {-1, 1, -1}, {0, 1, -1}, {1, 1, -1}, {-1, -1, 0},  {0, -1, 0},  {1, -1, 0},  {-1, 0, 0}};

bool valid_trits(trit_t const trits[], size_t len) {
  for (size_t i = 0; i < len; i++) {
    if (trits[i] < -1 || trits[i] > 1) {
      return false;
    }
  }
  return true;
}

bool valid_trytes(tryte_t const trytes[], size_t len) {
  for (size_t i = 0; i < len; i++) {
    if (trytes[i] != '9' && (trytes[i] < 'A' || trytes[i] > 'Z')) {
      return false;
    }
  }
  return true;
}

bool is_empty_trytes(tryte_t const trytes[], size_t len) {
  for (size_t i = 0; i < len; i++) {
    if (trytes[i] != TERNARY_NULL_TRYTE_CHAR) {
      return false;
    }
  }
  return true;
}

size_t min_trits(int64_t value) {
  size_t num = 1;
  uint64_t vp = 1;
  uint64_t v_abs;

  // nothing for zero value
  if (value == 0) {
    return 1;
  }

  bool is_negative = value < 0;
  // Edge case where value == INT64_MIN. In this case,
  // llabs cannot return a value greater than INT64_MAX
  // so we "force" the (unsigned) value explicitly
  if (value == INT64_MIN) {
    v_abs = INT64_MAX + 1ULL;
  } else if (is_negative) {
    v_abs = -value;
  } else {
    v_abs = value;
  }

  while (v_abs > vp) {
    vp = vp * TERNARY_BASE + 1;
    num++;
  }
  return num;
}

int64_t trits_to_int(trit_t const trits[], size_t num_trits) {
  int64_t accum = 0;
  size_t end = num_trits;
  while (end-- > 0) {
    accum = accum * TERNARY_BASE + trits[end];
  }

  return accum;
}

// ========== trits addition =============
typedef struct ha_o {
  trit_t s;  // sum
  trit_t c;  // carry
} ha_o_t;

static trit_t trit_cons(trit_t a, trit_t b) { return a == b ? a : 0; }

static trit_t trit_sum(trit_t a, trit_t b) {
  trit_t s = a + b;
  switch (s) {
    case 2:
      return -1;
    case -2:
      return 1;
    default:
      return s;
  }
}

/// Adds values `a` with `b` with a carry `c`, and returns (sum, carry)
static ha_o_t trit_full_add(trit_t a, trit_t b, trit_t c) {
  trit_t s_ab = trit_sum(a, b);

  trit_t x = trit_cons(a, b) + trit_cons(s_ab, c);
  return (ha_o_t){trit_sum(s_ab, c), (x > 0) - (x < 0)};
}

static int add_internal(trit_t t[], size_t s, int8_t negative, int64_t v, ha_o_t r) {
  trit_t trit;

  if (!v && !r.c) return 0;
  if (s == 0) return 1;

  trit = ((v + 1) % 3) - 1;
  if (negative) {
    trit = -trit;
  }

  r = trit_full_add(*t, trit, r.c);
  *t = r.s;
  return add_internal(&t[1], s - 1, negative, (v + 1) / 3, r);
}

void trits_add_int(trit_t trits[], size_t trits_len, int64_t value) {
  add_internal(trits, trits_len, value < 0, value, (ha_o_t){0, 0});
}

void trits_add_trits(trit_t const *const lh, trit_t *const rh, size_t const len) {
  ha_o_t r = {0, 0};
  size_t i = 0;
  for (; i < len; i++) {
    r = trit_full_add(lh[i], rh[i], r.c);
    rh[i] = r.s;
  }
}

// ========== trits trytes convertion =============

int trits_to_trytes(trit_t trits[], size_t trits_len, tryte_t trytes[]) {
  if (trits_len == 0) {
    return -1;
  }

  int k = 0;

  for (size_t i = 0, j = 0; i < trits_len; i += TERNARY_BASE, j++) {
    k = 0;
    for (size_t l = trits_len - i < TERNARY_TRITS_PER_TRYTE ? trits_len - i : TERNARY_TRITS_PER_TRYTE; l-- > 0;) {
      k *= TERNARY_BASE;
      k += trits[i + l];
    }
    if (k < 0) {
      k += TERNARY_TABLE_SIZE;
    }
    trytes[j] = TERNARY_TRYTE_ALPHABET[k];
  }
  return 0;
}

int trytes_to_trits(tryte_t trytes[], size_t trytes_len, trit_t trits[]) {
  if (trytes_len == 0) {
    return -1;
  }

  for (size_t i = 0, j = 0; i < trytes_len; i++, j += TERNARY_BASE) {
    memcpy(trits + j, TRYTES_TRITS_LUT[INDEX_OF_TRYTE(trytes[i])], TERNARY_TRITS_PER_TRYTE);
  }
  return 0;
}

// int64 trits

int64_t trits_to_int64(trit_t trits[], size_t num_trits) {
  if (num_trits == 0) {
    return 0;
  }
  int64_t accum = 0;
  size_t end = num_trits;
  while (end-- > 0) {
    accum = accum * TERNARY_BASE + trits[end];
  }
  return accum;
}

void int64_to_trits(int64_t value, trit_t trits[]) {
  trit_t trit;
  size_t i;
  uint64_t v_abs;

  bool negative = value < 0;
  // Edge case where value == INT64_MIN. In this case,
  // llabs cannot return a value greater than INT64_MAX
  // so we "force" the (unsigned) value explicitly
  if (value == INT64_MIN) {
    v_abs = INT64_MAX + 1ULL;
  } else if (negative) {
    v_abs = -value;
  } else {
    v_abs = value;
  }
  // } else {
  //   v_abs = llabs(value);
  // }

  memset(trits, 0, TERNARY_BASE);
  for (i = 0; i < min_trits(value); i++) {
    if (v_abs == 0) {
      break;
    }
    trit = (v_abs + 1) % (TERNARY_BASE)-1;
    if (negative) {
      trit = -trit;
    }
    trits[i] = trit;
    v_abs++;
    v_abs /= TERNARY_BASE;
  }
}

// ========== ASCII =============
/*
How the conversion works:
  2 Trytes === 1 Byte
  There are a total of 27 different tryte values: 9ABCDEFGHIJKLMNOPQRSTUVWXYZ

  1. We get the decimal value of an individual ASCII character
  2. From the decimal value, we then derive the two tryte values by basically calculating the tryte equivalent
    (e.g. 100 === 19 + 3 * 27)
    a. The first tryte value is the decimal value modulo 27 (27 trytes)
    b. The second value is the remainder (decimal value - first value), divided by 27
  3. The two values returned from Step 2. are then input as indices into the available values list
    ('9ABCDEFGHIJKLMNOPQRSTUVWXYZ') to get the correct tryte value

EXAMPLES
  Lets say we want to convert the ASCII character "Z".
    1. 'Z' has a decimal value of 90.
    2. 90 can be represented as 9 + 3 * 27. To make it simpler:
      a. First value: 90 modulo 27 is 9. This is now our first value
      b. Second value: (90 - 9) / 27 is 3. This is our second value.
    3. Our two values are now 9 and 3. To get the tryte value now
      we simply insert it as indices into '9ABCDEFGHIJKLMNOPQRSTUVWXYZ'
      a. The first tryte value is '9ABCDEFGHIJKLMNOPQRSTUVWXYZ'[9] === "I"
      b. The second tryte value is '9ABCDEFGHIJKLMNOPQRSTUVWXYZ'[3] === "C"
    Our tryte pair is "IC"

RESULT:
  The ASCII char "Z" is represented as "IC" in trytes
*/

void ascii_to_trytes(char const str[], tryte_t trytes[]) {
  tryte_t first_tryte = 0, second_tryte = 0;
  uint8_t ascii_value = 0;
  size_t tryte_index = 0;

  for (size_t i = 0; i < strlen(str); i++) {
    ascii_value = str[i];
    first_tryte = ascii_value % 27;
    second_tryte = (ascii_value - first_tryte) / 27;
    trytes[tryte_index++] = TERNARY_TRYTE_ALPHABET[first_tryte];
    trytes[tryte_index++] = TERNARY_TRYTE_ALPHABET[second_tryte];
  }
}

void trytes_to_ascii(tryte_t const trytes[], size_t trytes_len, char out_str[]) {
  for (size_t i = 0; i < trytes_len; i += 2) {
    out_str[i / 2] = INDEX_OF_TRYTE(trytes[i]) + INDEX_OF_TRYTE(trytes[i + 1]) * 27;
  }
}
