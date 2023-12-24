/******************************************************************************
 *  @file         config.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2023-12-24
 *  @license      LGPL-v3
 *  @brief        bdc config
 *****************************************************************************/

#ifndef BDC_CORE_CONFIG_H_
#define BDC_CORE_CONFIG_H_

#include "bdc/core/macro.h"

BDC_EXTERN_C_BEGIN

/**
 * @brief get bdc default config path
 *
 * @return bdc default config path
 *
 * @NOTE: search order
 *     * ${USER_HOME}/.local/bdc/config.xml
 *     * ${USER_HOME}/.bdc/config.xml
 *     * ${BDC_BIN_PATH}/../etc/config.xml
 */
BDC_EXPORT
const char *bdc_default_config_path();

BDC_EXTERN_C_END

#endif // !BDC_CORE_CONFIG_H_
