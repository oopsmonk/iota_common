#ifndef __MODELS_PAYLOADS_SIGNED_DATA_H__
#define __MODELS_PAYLOADS_SIGNED_DATA_H__

#include <stdint.h>

#include "models/address.h"
#include "models/types.h"

typedef struct {
  payload_t type;                        // Must be set to 3
  byte_t *data;                          // The data we are attaching
  byte_t pub_key[ED_PUBLIC_KEY_BYTES];   // The Ed25519 public key used to verify the signature.
  byte_t signature[ED_SIGNATURE_BYTES];  // The signature signing the data.
} signed_data_t;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif