#ifndef __MODELS_OUTPUTS_SIG_UNLOCK_H__
#define __MODELS_OUTPUTS_SIG_UNLOCK_H__

#include <stdint.h>

#include "models/address.h"
#include "models/types.h"

typedef struct {
  output_t type;                    // Set to value 0 to denote a SigLockedSingleDeposit.
  byte_t addr[IOTA_ADDRESS_BYTES];  // Ed25519 address
  uint64_t amount;                  // The amount of tokens to deposit with this SigLockedSingleDeposit output.
} sig_unlocked_single_deposit_t;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif