// document https://github.com/iotaledger/kerl/blob/master/IOTA-Kerl-spec.md
#include <stdio.h>

#include "crypto/kerl/converter.h"
#include "crypto/kerl/kerl.h"

int kerl_init(Keccak_HashInstance* const kerl) {
  // keccak_384 rate: 832, capacity: 768, hashbitlen: 384, delimitedSuffix: 0x01 (SOH)
  if (Keccak_HashInitialize(kerl, KECCAK_384_RATE, KECCAK_384_CAPACITY, KECCAK_384_HASHBITLEN,
                            KECCAK_384_DELIMITED_SUFFIX) == KECCAK_SUCCESS) {
    return 0;
  }
  return -1;
}

int kerl_reset(Keccak_HashInstance* const kerl) { return kerl_init(kerl); }

// void dump_hex(uint8_t data[], size_t len){
//   for(int i = 0; i < len; i++){
//     printf("0x%x ", data[i]);
//   }
//   printf("\n");
// }

void kerl_absorb(Keccak_HashInstance* const kerl, trit_t trits[], size_t length) {
  uint8_t bytes[NUM_KERL_HASH_BYTES];
  trit_t const* const end = &trits[length - 1];

  for (; trits < end;) {
    kerl_trits_to_bytes(trits, bytes);
    Keccak_HashUpdate(kerl, bytes, KECCAK_384_HASHBITLEN);
    trits = &trits[NUM_KERL_HASH_TRITS];
  }
}

void kerl_squeeze(Keccak_HashInstance* const kerl, trit_t trits[], size_t length) {
  size_t i;
  uint8_t bytes[NUM_KERL_HASH_BYTES], tmp[NUM_KERL_HASH_BYTES];
  uint32_t* ptr = (uint32_t*)bytes;
  trit_t const* const end = &trits[length - 1];

  for (; trits < end;) {
    Keccak_HashSqueeze(kerl, bytes, KECCAK_384_HASHBITLEN);

    memcpy(tmp, bytes, NUM_KERL_HASH_BYTES * sizeof(uint8_t));
    kerl_bytes_to_trits(tmp, trits);

    for (i = 0; i < BIGINT_LENGTH; i++) {
      ptr[i] = ptr[i] ^ 0xFFFFFFFF;
    }

    kerl_init(kerl);
    Keccak_HashUpdate(kerl, bytes, KECCAK_384_HASHBITLEN);
    trits = &trits[NUM_KERL_HASH_TRITS];
  }
}

#define HASH_TRYTE_VAL(hash, i)                                                    \
  (hash[i * TERNARY_TRITS_PER_TRYTE] + hash[i * TERNARY_TRITS_PER_TRYTE + 1] * 3 + \
   hash[i * TERNARY_TRITS_PER_TRYTE + 2] * 9)

int kerl_signature(Keccak_HashInstance* const kerl, trit_t bundle_hash[], trit_t key[], size_t key_len, trit_t sig[]) {
  trit_t* se = &sig[key_len];

  if (sig != key) {
    memcpy(sig, key, key_len * sizeof(trit_t));
  }

  for (size_t i = 0; sig < se; i++, sig = &sig[NUM_KERL_HASH_TRITS]) {
    for (size_t j = 0; j < (size_t)(TERNARY_TRYTE_MAX - HASH_TRYTE_VAL(bundle_hash, i)); j++) {
      kerl_absorb(kerl, sig, NUM_KERL_HASH_TRITS);
      kerl_squeeze(kerl, sig, NUM_KERL_HASH_TRITS);
      kerl_reset(kerl);
    }
  }

  return 0;
}