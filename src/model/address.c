#include <stdio.h>

#include "crypto/signing.h"
#include "model/address.h"
#include "model/transaction.h"

int generate_address_trits(trit_t seed[], uint64_t index, addr_security_t security, trit_t address_out[]) {
  return sign_address_gen_trits(seed, index, security, address_out);
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