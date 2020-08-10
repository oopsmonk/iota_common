#ifndef __MODELS_PAYLOADS_UNSIGNED_DATA_H__
#define __MODELS_PAYLOADS_UNSIGNED_DATA_H__

#include <stdint.h>

#include "models/types.h"

typedef struct {
  payload_t type;  // Must be set to 2
  byte_t *data;    // The data we are attaching
} unsigned_data_t;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif
