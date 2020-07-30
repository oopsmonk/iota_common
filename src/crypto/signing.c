#include "crypto/signing.h"
#include "utils/memset_safe.h"

#define SECURITY_LEVEL_MAX 3

// we reserve biggest key buffer for all security level..
// not thread-safe, used by address and signature sining.
// private key buffer = max_security * hash_size * fragments
#define MAX_PKEY_LEN (SECURITY_LEVEL_MAX * (KERL_HASH_TRITS_CHUNK * KERL_HASH_FRAGMENTS))
trit_t g_pkey[MAX_PKEY_LEN];

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

int sign_address_gen_trits(trit_t seed[], uint64_t index, uint8_t security, trit_t address_out[]) {
  Keccak_HashInstance kerl;
  trit_t subseed[KERL_HASH_TRITS_CHUNK];
  size_t key_length = security * (KERL_HASH_TRITS_CHUNK * KERL_HASH_FRAGMENTS);
  if (seed == NULL || address_out == NULL) {
    return -1;
  }

  kerl_init(&kerl);
  // computing subseed
  kerl_subseed(&kerl, seed, index, subseed);
  // computing private key
  kerl_key(&kerl, subseed, g_pkey, key_length);
  // computing digest
  kerl_key_digest(&kerl, g_pkey, key_length, g_pkey);
  // computing address
  kerl_address(&kerl, g_pkey, security * KERL_HASH_TRITS_CHUNK, address_out);
  // for security
  memset_safe(g_pkey, MAX_PKEY_LEN, 0, MAX_PKEY_LEN);
  return 0;
}

void normalize_hash(trit_t hash[], trit_t normalized_hash[]) {
  for (int i = 0; i < SECURITY_LEVEL_MAX; i++) {
    int sum = 0;
    for (int j = i * KERL_HASH_FRAGMENTS; j < (i + 1) * KERL_HASH_FRAGMENTS; j++) {
      normalized_hash[j] = (hash[j * TERNARY_TRITS_PER_TRYTE] + hash[j * TERNARY_TRITS_PER_TRYTE + 1] * 3 +
                            hash[j * TERNARY_TRITS_PER_TRYTE + 2] * 9);
      sum += normalized_hash[j];
    }
    if (sum > 0) {
      while (sum-- > 0) {
        for (int j = i * KERL_HASH_FRAGMENTS; j < (i + 1) * KERL_HASH_FRAGMENTS; j++) {
          if (normalized_hash[j] > TERNARY_TRYTE_MIN) {
            normalized_hash[j]--;
            break;
          }
        }
      }
    } else {
      while (sum++ < 0) {
        for (int j = i * KERL_HASH_FRAGMENTS; j < (i + 1) * KERL_HASH_FRAGMENTS; j++) {
          if (normalized_hash[j] < TERNARY_TRYTE_MAX) {
            normalized_hash[j]++;
            break;
          }
        }
      }
    }
  }
}

static void normalize_hash_to_trits(trit_t hash[], trit_t normalized_hash[]) {
  trit_t normalized_bundle_bytes[KERL_HASH_TRYTES_CHUNK];

  normalize_hash(hash, normalized_bundle_bytes);
  for (int c = 0; c < KERL_HASH_TRYTES_CHUNK; ++c) {
    int64_to_trits(normalized_bundle_bytes[c], &normalized_hash[c * TERNARY_BASE]);
  }
}

int sign_signature_gen_trits(trit_t seed[], size_t index, uint8_t security, trit_t bundle_hash[],
                             trit_t out_signature[]) {
  Keccak_HashInstance kerl;
  trit_t subseed[KERL_HASH_TRITS_CHUNK];
  trit_t normalized_bundle_hash[KERL_HASH_TRITS_CHUNK];
  size_t key_length = security * (KERL_HASH_TRITS_CHUNK * KERL_HASH_FRAGMENTS);

  if (seed == NULL || !(security > 0 && security <= 3) || bundle_hash == NULL) {
    return -1;
  }

  kerl_init(&kerl);
  kerl_subseed(&kerl, seed, index, subseed);
  kerl_key(&kerl, subseed, g_pkey, key_length);
  normalize_hash_to_trits(bundle_hash, normalized_bundle_hash);
  kerl_signature(&kerl, normalized_bundle_hash, g_pkey, key_length, out_signature);
  kerl_reset(&kerl);
  memset_safe(subseed, KERL_HASH_TRITS_CHUNK, 0, KERL_HASH_TRITS_CHUNK);
  memset_safe(g_pkey, MAX_PKEY_LEN, 0, MAX_PKEY_LEN);
  return 0;
}

int sign_signature_gen_trytes(tryte_t seed[], size_t index, uint8_t security, tryte_t bundle_hash[],
                              tryte_t out_signature[]) {
  int ret = 0;
  trit_t seed_trits[KERL_HASH_TRITS_CHUNK];
  trit_t bundle_hash_trits[KERL_HASH_TRITS_CHUNK];
  size_t sig_trits_len = security * (KERL_HASH_TRITS_CHUNK * KERL_HASH_FRAGMENTS);
  trit_t sig_trits[sig_trits_len];

  if (seed == NULL || !(security > 0 && security <= 3) || bundle_hash == NULL) {
    return -1;
  }

  trytes_to_trits(seed, KERL_HASH_TRYTES_CHUNK, seed_trits);
  trytes_to_trits(bundle_hash, KERL_HASH_TRYTES_CHUNK, bundle_hash_trits);

  ret = sign_signature_gen_trits(seed_trits, index, security, bundle_hash_trits, sig_trits);
  memset_safe(seed_trits, KERL_HASH_TRITS_CHUNK, 0, KERL_HASH_TRITS_CHUNK);
  trits_to_trytes(sig_trits, sig_trits_len, out_signature);

  return ret;
}