#include "crypto/signing.h"

int kerl_subseed(Keccak_HashInstance* kerl, trit_t const seed[], uint64_t key_idx, trit_t subseed_out[]) {
  if (kerl == NULL || seed == NULL || subseed_out == NULL) {
    return -1;
  }

  memcpy(subseed_out, seed, KERL_HASH_TRITS_CHUNK * sizeof(trit_t));
  // subseed = seed + index
  trits_add_int(subseed_out, KERL_HASH_TRITS_CHUNK, key_idx);
  kerl_absorb(kerl, subseed_out, KERL_HASH_TRITS_CHUNK);
  kerl_squeeze(kerl, subseed_out, KERL_HASH_TRITS_CHUNK);
  kerl_reset(kerl);
  return 0;
}

int kerl_key(Keccak_HashInstance* kerl, trit_t subseed[], trit_t key[], size_t key_length) {
  if (kerl == NULL || subseed == NULL || key == NULL) {
    return -1;
  }

  if (key_length % KERL_HASH_TRITS_CHUNK) {
    return -1;
  }

  trit_t const* const end = &key[key_length - 1];
  kerl_absorb(kerl, subseed, KERL_HASH_TRITS_CHUNK);

  for (; key < end; key = &key[KERL_HASH_TRITS_CHUNK]) {
    kerl_squeeze(kerl, key, KERL_HASH_TRITS_CHUNK);
  }

  kerl_reset(kerl);
  return 0;
}

int kerl_key_digest(Keccak_HashInstance* kerl, trit_t key[], size_t key_length, trit_t digest[]) {
  if (kerl == NULL || key == NULL || digest == NULL) {
    return -1;
  }

  if (key_length % KERL_HASH_TRITS_CHUNK) {
    return -1;
  }

  size_t i;
  trit_t* const k_start = key;
  trit_t* const k_end = &key[key_length - 1];
  trit_t* const d_end = &digest[KERL_HASH_TRITS_CHUNK * (key_length / KERL_KEY_FRAGMENTS)];

  for (; key < k_end; key = &key[KERL_HASH_TRITS_CHUNK]) {
    for (i = 0; i < 26; i++) {
      kerl_absorb(kerl, key, KERL_HASH_TRITS_CHUNK);
      kerl_squeeze(kerl, key, KERL_HASH_TRITS_CHUNK);
      kerl_reset(kerl);
    }
  }

  key = k_start;

  for (; digest < d_end; digest = &digest[KERL_HASH_TRITS_CHUNK]) {
    kerl_absorb(kerl, key, KERL_KEY_FRAGMENTS);
    kerl_squeeze(kerl, digest, KERL_HASH_TRITS_CHUNK);
    kerl_reset(kerl);

    key = &key[KERL_KEY_FRAGMENTS];
  }

  return 0;
}

int kerl_address(Keccak_HashInstance* kerl, trit_t digest[], size_t digest_len, trit_t address_out[]) {
  kerl_absorb(kerl, digest, digest_len);
  kerl_squeeze(kerl, address_out, KERL_HASH_TRITS_CHUNK);
  kerl_reset(kerl);
  return 0;
}
