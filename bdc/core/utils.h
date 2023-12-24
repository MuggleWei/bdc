/******************************************************************************
 *  @file         utils.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2023-12-24
 *  @license      LGPL-v3
 *  @brief        bdc utils
 *****************************************************************************/

#ifndef BDC_CORE_UTILS_H_
#define BDC_CORE_UTILS_H_

#include "bdc/core/macro.h"

BDC_EXTERN_C_BEGIN

/**
 * @brief get home dir
 *
 * @param buf     buffer store the result
 * @param bufsize sizeof buf
 *
 * @return
 *     - on success, return homedir string
 *     - on failed, return NULL
 */
BDC_EXPORT
const char *bdc_homedir(char *buf, unsigned int bufsize);

BDC_EXTERN_C_END

#endif // !BDC_CORE_UTILS_H_
