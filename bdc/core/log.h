/******************************************************************************
 *  @file         log.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2023-12-24
 *  @license      LGPL-v3
 *  @brief        bdc log
 *****************************************************************************/

#ifndef BDC_CORE_LOG_H_
#define BDC_CORE_LOG_H_

#include "bdc/core/macro.h"

BDC_EXTERN_C_BEGIN

/**
 * @brief initialize log
 *
 * @param level_console  level of console
 * @param level_file     level of file
 * @param log_path       output log path
 * @param use_rotate     is use rotate
 *
 * @return
 *     - on success, return 0
 *     - otherwise, failed
 */
BDC_EXPORT
int bdc_log_init(int level_console, int level_file, const char *log_path,
				 int use_rotate);

BDC_EXTERN_C_END

#endif // !BDC_CORE_LOG_H_
