/******************************************************************************
 *  @file         main.c
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2023-12-24
 *  @license      LGPL-v3
 *  @brief        bdc client main
 *****************************************************************************/

#include "bdc/core/core.h"

int main(int argc, char *argv[])
{
	return bdc_cli_run(argc, argv);
}
