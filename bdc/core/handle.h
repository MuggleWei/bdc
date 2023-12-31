/******************************************************************************
 *  @file         handle.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2023-12-24
 *  @license      LGPL-v3
 *  @brief        bdc macro
 *****************************************************************************/

#ifndef BDC_CORE_HANDLE_H_
#define BDC_CORE_HANDLE_H_

#include "bdc/core/macro.h"

BDC_EXTERN_C_BEGIN

BDC_EXPORT
int bdc_cli_run(int argc, char **argv);

BDC_EXTERN_C_END

#endif // !BDC_CORE_HANDLE_H_
