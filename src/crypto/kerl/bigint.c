// a 384-bit big unsigned integer
// A Bigint is an unsigned integer x of the form
//   x = x[n-1]*B^(n-1) + x[n-2]*B^(n-2) + ... + x[1]*B + x[0]
// with 0 <= x[i] < B and 0 <= i < n is stored in a slice of length n, with the digits x[i] as the slice elements.
// The length of the slice never changes and operations are only well-defined for operands of the same length.

#include <inttypes.h>

#include "crypto/kerl/bigint.h"

typedef struct {
  uint8_t carry;
  uint32_t v;
} full_add_s;

static void full_add(full_add_s *const fa, uint64_t lh, uint64_t rh) {
  uint8_t carry1;
  uint32_t hi;
  uint64_t v;

  v = lh + rh;
  hi = (uint32_t)(v >> 32uLL);
  fa->v = v & 0xFFFFFFFF;

  carry1 = hi != 0;
  if (fa->carry) {
    v = fa->v + 1uLL;
    hi = (uint32_t)(v >> 32uLL);
    fa->v = v & 0xFFFFFFFF;
    fa->carry = carry1 || (hi != 0);
  } else {
    fa->carry = carry1;
  }
}

void bigint_not(uint32_t base[], size_t len) {
  for (size_t i = len; i--;) {
    base[i] = ~base[i];
  }
}

size_t bigint_add_small(uint32_t base[], uint32_t other) {
  // Note that this method doesn't do any bounds checks!
  size_t i = 1;
  full_add_s fa = {0, 0};
  full_add(&fa, base[0], other);

  base[0] = fa.v;

  while (fa.carry) {
    full_add(&fa, base[i], 0);
    base[i] = fa.v;
    i++;
  }

  return i;
}

void bigint_add(uint32_t base[], uint32_t const rh[], size_t len) {
  full_add_s fa = {0, 0};
  size_t i = 0;

  for (; i < len; i++) {
    full_add(&fa, base[i], rh[i]);
    base[i] = fa.v;
  }
}

void bigint_sub(uint32_t base[], uint32_t const rh[], size_t len) {
  full_add_s fa = {1, 0};
  size_t i = 0;

  for (; i < len; i++) {
    full_add(&fa, base[i], ~rh[i]);
    base[i] = fa.v;
  }
}

int8_t bigint_cmp(uint32_t const lh[], uint32_t const rh[], size_t len) {
  size_t i = len;

  for (; i-- > 0;) {
    if (lh[i] < rh[i]) {
      return -1;
    } else if (lh[i] > rh[i]) {
      return 1;
    }
  }
  return 0;
}
