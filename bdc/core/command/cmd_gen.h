/******************************************************************************
 *  @file         cmd_gen.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2023-12-24
 *  @license      LGPL-v3
 *  @brief        bdc command - gen
 *****************************************************************************/

#ifndef BDC_CORE_COMMAND_CMD_GEN_H_
#define BDC_CORE_COMMAND_CMD_GEN_H_

#include "bdc/core/macro.h"

BDC_EXTERN_C_BEGIN

/**
 * @brief bdc cli run command: gen
 *
 * @param argc  input argc
 * @param argv  input argv
 *
 * @return
 *     - on succes, return 0
 *     - otherwise, failed
 */
BDC_EXPORT
int bdc_cli_run_cmd_gen(int argc, char **argv);

BDC_EXTERN_C_END

#endif // !BDC_CORE_COMMAND_CMD_GEN_H_
