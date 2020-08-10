#ifndef __MODELS_PAYLOADS_INDEXATION_H__
#define __MODELS_PAYLOADS_INDEXATION_H__

#include <stdint.h>

#include "models/types.h"

typedef struct {
  payload_t type;  // Must be set to 4
  byte_t tag[16];  // The tag which is used to index the Signed Transaction's hash.
} unsigned_data_t;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif
