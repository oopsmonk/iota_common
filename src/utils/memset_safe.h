#ifndef __UTILS_MEMSET_SAFE_H__
#define __UTILS_MEMSET_SAFE_H__

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief instead of memset, use for zero out a sensitive memory block.
 *
 * @param[in] dest The pointer to the object to fill
 * @param[in] destsz The size of the destination array
 * @param[in] ch The fill byte
 * @param[in] count Number of bytes to fill
 * @return int
 */
int memset_safe(void *dest, size_t destsz, int ch, size_t count);

#ifdef __cplusplus
}
#endif

#endif  // __UTILS_MEMSET_SAFE_H__
