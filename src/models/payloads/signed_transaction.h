#ifndef __MODELS_PAYLOADS_SIGNED_TX_H__
#define __MODELS_PAYLOADS_SIGNED_TX_H__

#include <stdint.h>
#include <stdlib.h>

#include "models/types.h"

typedef struct {
  transaction_t type;    // Set to value 0 to denote an Unsigned Transaction.
  size_t inputs_count;   // The amount of inputs proceeding.
  void *inputs;          // a list of inputs, any of utxo_input
  size_t outputs_count;  // The amount of outputs proceeding.
  void *outputs;         // a list of outputs, any of sig_unlocked_single_deposit_t
  size_t payload_len;    // The length in bytes of the optional payload.
  void *payload;         // optional one of unsigned data, signed data, indexation playloads.
} unsigned_tx_t;

typedef struct {
  signature_t type;      // Set to value 0 to denote an Ed25519 Signature
  byte_t pub_key[32];    // The public key of the Ed25519 keypair which is used to verify the signature.
  byte_t signature[64];  // The signature signing the serialized Unsigned Transaction.
} ed25519_signature_t;

typedef struct {
  unlock_block_t type;            // Set to value 0 to denote a Signature Unlock Block.
  ed25519_signature_t signature;  // Ed25519 signature
} signature_unlock_block_t;

typedef struct {
  unlock_block_t type;  // Set to value 1 to denote a Reference Unlock Block.
  size_t reference;     // Represents the index of a previous unlock block.
} reference_unlock_block_t;

typedef struct {
  payload_t type;                // Set to value 0 to denote a Signed Transaction payload.
  void *tx;                      // One of transaction type, ex: unsigned_tx_t
  uint64_t unlock_blocks_count;  // The count of unlock blocks proceeding. Must match count of inputs specified.
  void *unlock_blocks;           // a list of unlock blocks, any of signature unlock block or reference unlock block
} signed_tx_payload_t;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif
