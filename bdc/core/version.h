/******************************************************************************
 *  @file         version.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2023-12-24
 *  @license      LGPL-v3
 *  @brief        bdc version
 *****************************************************************************/

#ifndef BDC_CORE_VERSION_H_
#define BDC_CORE_VERSION_H_

#include "bdc/core/macro.h"

BDC_EXTERN_C_BEGIN

/**
 * @brief get bdc version
 *
 * @return bdc version
 */
BDC_EXPORT
const char *bdc_version();

/**
 * @brief get bdc compile datetime
 *
 * @return bdc compile datetime
 */
BDC_EXPORT
const char *bdc_compile_datetime();

/**
 * @brief get bdc compile datetime in iso8601 format
 *
 * @return bdc compile datetime in iso8601 format
 */
BDC_EXPORT
const char *bdc_compile_datetime_iso8601();

BDC_EXTERN_C_END

#endif // !BDC_CORE_VERSION_H_
