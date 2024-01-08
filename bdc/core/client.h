/******************************************************************************
 *  @file         client.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2023-12-24
 *  @license      LGPL-v3
 *  @brief        bdc client
 *****************************************************************************/

#ifndef BDC_CORE_CLIENT_H_
#define BDC_CORE_CLIENT_H_

#include "bdc/core/macro.h"

BDC_EXTERN_C_BEGIN

/**
 * @brief bdc cli run
 *
 * @param argc  input argc
 * @param argv  input argv
 *
 * @return
 *     - on succes, return 0
 *     - otherwise, failed
 */
BDC_EXPORT
int bdc_cli_run(int argc, char **argv);

BDC_EXTERN_C_END

#endif // !BDC_CORE_CLIENT_H_
