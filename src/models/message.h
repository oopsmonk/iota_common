#ifndef __MODELS_MESSAGE_H__
#define __MODELS_MESSAGE_H__

#include <stdint.h>
#include <stdlib.h>

#include "models/types.h"

#define IOTA_MESSAGE_ID_BYTES 32
typedef struct {
  uint8_t version;                       // The message version. The schema specified in this RFC is for version 1 only.
  byte_t trunk[IOTA_MESSAGE_ID_BYTES];   // The Message ID of the first Message we reference.
  byte_t branch[IOTA_MESSAGE_ID_BYTES];  // The Message ID of the second Message we reference.
  size_t payload_length;                 // The length of the Payload.
  void *payload;                         // One of payload type
  uint64_t nonce;                        // The nonce which lets this message fulfill the Proof-of-Work requirement.
} message_t;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif
