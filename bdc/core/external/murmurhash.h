/******************************************************************************
 *  @file         murmurhash.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2024-01-08
 *  @license      LGPL-v3
 *  @brief        bdc external murmurhash
 *  @NOTE
 *    This file extract from:
 *    https://github.com/aappleby/smhasher/blob/master/src/MurmurHash3.cpp
 *****************************************************************************/

#ifndef BDC_CORE_EXTERNAL_MURMURHASH_H_
#define BDC_CORE_EXTERNAL_MURMURHASH_H_

#include "bdc/core/macro.h"
#include <stdint.h>

BDC_EXTERN_C_BEGIN

void MurmurHash3_x86_32(const void *key, int len, uint32_t seed, void *out);

BDC_EXTERN_C_END

#endif // !BDC_CORE_EXTERNAL_MURMURHASH_H_
