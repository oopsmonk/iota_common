#include <stdio.h>

#include "crypto/signing.h"
#include "model/address.h"
#include "model/transaction.h"

int generate_address_trits(trit_t seed[], uint64_t index, addr_security_t security, trit_t address_out[]) {
  Keccak_HashInstance kerl;
  trit_t subseed[KERL_HASH_TRITS_CHUNK];
  size_t key_length = (size_t)security * (KERL_HASH_TRITS_CHUNK * KERL_HASH_FRAGMENTS);
  // we reserve biggest key size for all security level.
  trit_t key[ADDR_SECURITY_HIGH * (KERL_HASH_TRITS_CHUNK * KERL_HASH_FRAGMENTS)];
  memset(key, 0, ADDR_SECURITY_HIGH * (KERL_HASH_TRITS_CHUNK * KERL_HASH_FRAGMENTS));

  if (seed == NULL || address_out == NULL) {
    return -1;
  }

  kerl_init(&kerl);
  // computing subseed
  kerl_subseed(&kerl, seed, index, subseed);
  // computing private key
  kerl_key(&kerl, subseed, key, key_length);
  // computing digest
  kerl_key_digest(&kerl, key, key_length, key);
  // computing address
  kerl_address(&kerl, key, security * KERL_HASH_TRITS_CHUNK, address_out);
  return 0;
}

int generate_address_trytes(tryte_t seed[], uint64_t index, addr_security_t security, tryte_t address_out[]) {
  trit_t seed_trits[NUM_TRITS_HASH];
  trit_t address_trits[NUM_TRITS_ADDRESS];
  if (seed == NULL || address_out == NULL) {
    return -1;
  }

  trytes_to_trits(seed, NUM_TRYTES_HASH, seed_trits);
  generate_address_trits(seed_trits, index, security, address_trits);
  trits_to_trytes(address_trits, NUM_TRITS_HASH, address_out);

  return 0;
}