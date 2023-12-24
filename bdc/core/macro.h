/******************************************************************************
 *  @file         macro.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2023-12-24
 *  @license      LGPL-v3
 *  @brief        bdc macro
 *****************************************************************************/

#ifndef BDC_CORE_MACRO_H_
#define BDC_CORE_MACRO_H_

#include "bdc/config.h"

// lib and dll
#if MUGGLE_PLATFORM_WINDOWS && defined(BDC_USE_DLL)
	#ifdef BDC_EXPORTS
		#define BDC_EXPORT __declspec(dllexport)
	#else
		#define BDC_EXPORT __declspec(dllimport)
	#endif
#else
	#define BDC_EXPORT
#endif

// extern c
#ifdef __cplusplus
	#ifndef BDC_EXTERN_C_BEGIN
		#define BDC_EXTERN_C_BEGIN extern "C" {
	#endif
	#ifndef BDC_EXTERN_C_END
		#define BDC_EXTERN_C_END   }
	#endif
#else
	#ifndef BDC_EXTERN_C_BEGIN
		#define BDC_EXTERN_C_BEGIN
	#endif
	#ifndef BDC_EXTERN_C_END
		#define BDC_EXTERN_C_END
	#endif
#endif

#endif // !BDC_CORE_MACRO_H_
