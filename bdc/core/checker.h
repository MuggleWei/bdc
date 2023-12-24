/******************************************************************************
 *  @file         checker.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2023-12-24
 *  @license      LGPL-v3
 *  @brief        bdc checker
 *****************************************************************************/

#ifndef BDC_CORE_CHECKER_H_
#define BDC_CORE_CHECKER_H_

#include "bdc/core/macro.h"
#include <stdbool.h>

BDC_EXTERN_C_BEGIN

typedef struct bdc_checker {
} bdc_checker_t;

BDC_EXPORT
bool bdc_checker_init(bdc_checker_t *checker);

/**
 * @brief generate bdc meta infos
 *
 * @param checker  bdc checker
 * @param dirpath  directory path
 *
 * @return boolean
 */
BDC_EXPORT
bool bdc_checker_gen(bdc_checker_t *checker, const char *dirpath);

BDC_EXTERN_C_END

#endif // !BDC_CORE_CHECKER_H_
