/* HASH CRC-32:0x88968743 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBC_SSP_STRING_H
#define _LIBC_SSP_STRING_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/ssp.string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include "core/ssp.string.h"

#ifndef ____libc___memcpy_chk_defined
#ifdef __fast___memcpy_chk_defined
#define ____libc___memcpy_chk_defined
#define __libc___memcpy_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memcpy_chk))
#elif defined(____libc_core___memcpy_chk_defined)
#define ____libc___memcpy_chk_defined
#define __libc___memcpy_chk __libc_core___memcpy_chk
#endif /* ... */
#endif /* !____libc___memcpy_chk_defined */
#ifndef ____libc___memmove_chk_defined
#ifdef __fast___memmove_chk_defined
#define ____libc___memmove_chk_defined
#define __libc___memmove_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmove_chk))
#elif defined(____libc_core___memmove_chk_defined)
#define ____libc___memmove_chk_defined
#define __libc___memmove_chk __libc_core___memmove_chk
#endif /* ... */
#endif /* !____libc___memmove_chk_defined */
#ifndef ____libc___memset_chk_defined
#ifdef __fast___memset_chk_defined
#define ____libc___memset_chk_defined
#define __libc___memset_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memset_chk))
#elif defined(____libc_core___memset_chk_defined)
#define ____libc___memset_chk_defined
#define __libc___memset_chk __libc_core___memset_chk
#endif /* ... */
#endif /* !____libc___memset_chk_defined */
#ifndef ____libc___strcat_chk_defined
#ifdef __fast___strcat_chk_defined
#define ____libc___strcat_chk_defined
#define __libc___strcat_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__strcat_chk))
#elif defined(____libc_core___strcat_chk_defined)
#define ____libc___strcat_chk_defined
#define __libc___strcat_chk __libc_core___strcat_chk
#endif /* ... */
#endif /* !____libc___strcat_chk_defined */
#ifndef ____libc___strcpy_chk_defined
#ifdef __fast___strcpy_chk_defined
#define ____libc___strcpy_chk_defined
#define __libc___strcpy_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__strcpy_chk))
#elif defined(____libc_core___strcpy_chk_defined)
#define ____libc___strcpy_chk_defined
#define __libc___strcpy_chk __libc_core___strcpy_chk
#endif /* ... */
#endif /* !____libc___strcpy_chk_defined */
#ifndef ____libc___strncat_chk_defined
#ifdef __fast___strncat_chk_defined
#define ____libc___strncat_chk_defined
#define __libc___strncat_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__strncat_chk))
#elif defined(____libc_core___strncat_chk_defined)
#define ____libc___strncat_chk_defined
#define __libc___strncat_chk __libc_core___strncat_chk
#endif /* ... */
#endif /* !____libc___strncat_chk_defined */
#ifndef ____libc___strncpy_chk_defined
#ifdef __fast___strncpy_chk_defined
#define ____libc___strncpy_chk_defined
#define __libc___strncpy_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__strncpy_chk))
#elif defined(____libc_core___strncpy_chk_defined)
#define ____libc___strncpy_chk_defined
#define __libc___strncpy_chk __libc_core___strncpy_chk
#endif /* ... */
#endif /* !____libc___strncpy_chk_defined */
#ifndef ____libc___mempcpy_chk_defined
#ifdef __fast___mempcpy_chk_defined
#define ____libc___mempcpy_chk_defined
#define __libc___mempcpy_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempcpy_chk))
#elif defined(____libc_core___mempcpy_chk_defined)
#define ____libc___mempcpy_chk_defined
#define __libc___mempcpy_chk __libc_core___mempcpy_chk
#endif /* ... */
#endif /* !____libc___mempcpy_chk_defined */
#ifndef ____libc___stpcpy_chk_defined
#ifdef __fast___stpcpy_chk_defined
#define ____libc___stpcpy_chk_defined
#define __libc___stpcpy_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__stpcpy_chk))
#elif defined(____libc_core___stpcpy_chk_defined)
#define ____libc___stpcpy_chk_defined
#define __libc___stpcpy_chk __libc_core___stpcpy_chk
#endif /* ... */
#endif /* !____libc___stpcpy_chk_defined */
#ifndef ____libc___stpncpy_chk_defined
#ifdef __fast___stpncpy_chk_defined
#define ____libc___stpncpy_chk_defined
#define __libc___stpncpy_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__stpncpy_chk))
#elif defined(____libc_core___stpncpy_chk_defined)
#define ____libc___stpncpy_chk_defined
#define __libc___stpncpy_chk __libc_core___stpncpy_chk
#endif /* ... */
#endif /* !____libc___stpncpy_chk_defined */
#ifndef ____libc___mempmove_chk_defined
#ifdef __fast___mempmove_chk_defined
#define ____libc___mempmove_chk_defined
#define __libc___mempmove_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmove_chk))
#elif defined(____libc_core___mempmove_chk_defined)
#define ____libc___mempmove_chk_defined
#define __libc___mempmove_chk __libc_core___mempmove_chk
#endif /* ... */
#endif /* !____libc___mempmove_chk_defined */
#ifndef ____libc___mempset_chk_defined
#ifdef __fast___mempset_chk_defined
#define ____libc___mempset_chk_defined
#define __libc___mempset_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempset_chk))
#elif defined(____libc_core___mempset_chk_defined)
#define ____libc___mempset_chk_defined
#define __libc___mempset_chk __libc_core___mempset_chk
#endif /* ... */
#endif /* !____libc___mempset_chk_defined */
#ifndef ____libc___memmoveup_chk_defined
#ifdef __fast___memmoveup_chk_defined
#define ____libc___memmoveup_chk_defined
#define __libc___memmoveup_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmoveup_chk))
#elif defined(____libc_core___memmoveup_chk_defined)
#define ____libc___memmoveup_chk_defined
#define __libc___memmoveup_chk __libc_core___memmoveup_chk
#endif /* ... */
#endif /* !____libc___memmoveup_chk_defined */
#ifndef ____libc___memmovedown_chk_defined
#ifdef __fast___memmovedown_chk_defined
#define ____libc___memmovedown_chk_defined
#define __libc___memmovedown_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmovedown_chk))
#elif defined(____libc_core___memmovedown_chk_defined)
#define ____libc___memmovedown_chk_defined
#define __libc___memmovedown_chk __libc_core___memmovedown_chk
#endif /* ... */
#endif /* !____libc___memmovedown_chk_defined */
#ifndef ____libc___mempmoveup_chk_defined
#ifdef __fast___mempmoveup_chk_defined
#define ____libc___mempmoveup_chk_defined
#define __libc___mempmoveup_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmoveup_chk))
#elif defined(____libc_core___mempmoveup_chk_defined)
#define ____libc___mempmoveup_chk_defined
#define __libc___mempmoveup_chk __libc_core___mempmoveup_chk
#endif /* ... */
#endif /* !____libc___mempmoveup_chk_defined */
#ifndef ____libc___mempmovedown_chk_defined
#ifdef __fast___mempmovedown_chk_defined
#define ____libc___mempmovedown_chk_defined
#define __libc___mempmovedown_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmovedown_chk))
#elif defined(____libc_core___mempmovedown_chk_defined)
#define ____libc___mempmovedown_chk_defined
#define __libc___mempmovedown_chk __libc_core___mempmovedown_chk
#endif /* ... */
#endif /* !____libc___mempmovedown_chk_defined */
#ifndef ____libc___memcpyc_chk_defined
#ifdef __fast___memcpyc_chk_defined
#define ____libc___memcpyc_chk_defined
#define __libc___memcpyc_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memcpyc_chk))
#elif defined(____libc_core___memcpyc_chk_defined)
#define ____libc___memcpyc_chk_defined
#define __libc___memcpyc_chk __libc_core___memcpyc_chk
#endif /* ... */
#endif /* !____libc___memcpyc_chk_defined */
#ifndef ____libc___memmovec_chk_defined
#ifdef __fast___memmovec_chk_defined
#define ____libc___memmovec_chk_defined
#define __libc___memmovec_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmovec_chk))
#elif defined(____libc_core___memmovec_chk_defined)
#define ____libc___memmovec_chk_defined
#define __libc___memmovec_chk __libc_core___memmovec_chk
#endif /* ... */
#endif /* !____libc___memmovec_chk_defined */
#ifndef ____libc___mempcpyc_chk_defined
#ifdef __fast___mempcpyc_chk_defined
#define ____libc___mempcpyc_chk_defined
#define __libc___mempcpyc_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempcpyc_chk))
#elif defined(____libc_core___mempcpyc_chk_defined)
#define ____libc___mempcpyc_chk_defined
#define __libc___mempcpyc_chk __libc_core___mempcpyc_chk
#endif /* ... */
#endif /* !____libc___mempcpyc_chk_defined */
#ifndef ____libc___mempmovec_chk_defined
#ifdef __fast___mempmovec_chk_defined
#define ____libc___mempmovec_chk_defined
#define __libc___mempmovec_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmovec_chk))
#elif defined(____libc_core___mempmovec_chk_defined)
#define ____libc___mempmovec_chk_defined
#define __libc___mempmovec_chk __libc_core___mempmovec_chk
#endif /* ... */
#endif /* !____libc___mempmovec_chk_defined */
#ifndef ____libc___memmoveupc_chk_defined
#ifdef __fast___memmoveupc_chk_defined
#define ____libc___memmoveupc_chk_defined
#define __libc___memmoveupc_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmoveupc_chk))
#elif defined(____libc_core___memmoveupc_chk_defined)
#define ____libc___memmoveupc_chk_defined
#define __libc___memmoveupc_chk __libc_core___memmoveupc_chk
#endif /* ... */
#endif /* !____libc___memmoveupc_chk_defined */
#ifndef ____libc___memmovedownc_chk_defined
#ifdef __fast___memmovedownc_chk_defined
#define ____libc___memmovedownc_chk_defined
#define __libc___memmovedownc_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmovedownc_chk))
#elif defined(____libc_core___memmovedownc_chk_defined)
#define ____libc___memmovedownc_chk_defined
#define __libc___memmovedownc_chk __libc_core___memmovedownc_chk
#endif /* ... */
#endif /* !____libc___memmovedownc_chk_defined */
#ifndef ____libc___mempmoveupc_chk_defined
#ifdef __fast___mempmoveupc_chk_defined
#define ____libc___mempmoveupc_chk_defined
#define __libc___mempmoveupc_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmoveupc_chk))
#elif defined(____libc_core___mempmoveupc_chk_defined)
#define ____libc___mempmoveupc_chk_defined
#define __libc___mempmoveupc_chk __libc_core___mempmoveupc_chk
#endif /* ... */
#endif /* !____libc___mempmoveupc_chk_defined */
#ifndef ____libc___mempmovedownc_chk_defined
#ifdef __fast___mempmovedownc_chk_defined
#define ____libc___mempmovedownc_chk_defined
#define __libc___mempmovedownc_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmovedownc_chk))
#elif defined(____libc_core___mempmovedownc_chk_defined)
#define ____libc___mempmovedownc_chk_defined
#define __libc___mempmovedownc_chk __libc_core___mempmovedownc_chk
#endif /* ... */
#endif /* !____libc___mempmovedownc_chk_defined */
#ifndef ____libc___memcpyw_chk_defined
#ifdef __fast___memcpyw_chk_defined
#define ____libc___memcpyw_chk_defined
#define __libc___memcpyw_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memcpyw_chk))
#elif defined(____libc_core___memcpyw_chk_defined)
#define ____libc___memcpyw_chk_defined
#define __libc___memcpyw_chk __libc_core___memcpyw_chk
#endif /* ... */
#endif /* !____libc___memcpyw_chk_defined */
#ifndef ____libc___mempcpyw_chk_defined
#ifdef __fast___mempcpyw_chk_defined
#define ____libc___mempcpyw_chk_defined
#define __libc___mempcpyw_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempcpyw_chk))
#elif defined(____libc_core___mempcpyw_chk_defined)
#define ____libc___mempcpyw_chk_defined
#define __libc___mempcpyw_chk __libc_core___mempcpyw_chk
#endif /* ... */
#endif /* !____libc___mempcpyw_chk_defined */
#ifndef ____libc___memmovew_chk_defined
#ifdef __fast___memmovew_chk_defined
#define ____libc___memmovew_chk_defined
#define __libc___memmovew_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmovew_chk))
#elif defined(____libc_core___memmovew_chk_defined)
#define ____libc___memmovew_chk_defined
#define __libc___memmovew_chk __libc_core___memmovew_chk
#endif /* ... */
#endif /* !____libc___memmovew_chk_defined */
#ifndef ____libc___memcpyl_chk_defined
#ifdef __fast___memcpyl_chk_defined
#define ____libc___memcpyl_chk_defined
#define __libc___memcpyl_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memcpyl_chk))
#elif defined(____libc_core___memcpyl_chk_defined)
#define ____libc___memcpyl_chk_defined
#define __libc___memcpyl_chk __libc_core___memcpyl_chk
#endif /* ... */
#endif /* !____libc___memcpyl_chk_defined */
#ifndef ____libc___mempcpyl_chk_defined
#ifdef __fast___mempcpyl_chk_defined
#define ____libc___mempcpyl_chk_defined
#define __libc___mempcpyl_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempcpyl_chk))
#elif defined(____libc_core___mempcpyl_chk_defined)
#define ____libc___mempcpyl_chk_defined
#define __libc___mempcpyl_chk __libc_core___mempcpyl_chk
#endif /* ... */
#endif /* !____libc___mempcpyl_chk_defined */
#ifndef ____libc___memmovel_chk_defined
#ifdef __fast___memmovel_chk_defined
#define ____libc___memmovel_chk_defined
#define __libc___memmovel_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmovel_chk))
#elif defined(____libc_core___memmovel_chk_defined)
#define ____libc___memmovel_chk_defined
#define __libc___memmovel_chk __libc_core___memmovel_chk
#endif /* ... */
#endif /* !____libc___memmovel_chk_defined */
#ifndef ____libc___mempmovew_chk_defined
#ifdef __fast___mempmovew_chk_defined
#define ____libc___mempmovew_chk_defined
#define __libc___mempmovew_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmovew_chk))
#elif defined(____libc_core___mempmovew_chk_defined)
#define ____libc___mempmovew_chk_defined
#define __libc___mempmovew_chk __libc_core___mempmovew_chk
#endif /* ... */
#endif /* !____libc___mempmovew_chk_defined */
#ifndef ____libc___mempmovel_chk_defined
#ifdef __fast___mempmovel_chk_defined
#define ____libc___mempmovel_chk_defined
#define __libc___mempmovel_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmovel_chk))
#elif defined(____libc_core___mempmovel_chk_defined)
#define ____libc___mempmovel_chk_defined
#define __libc___mempmovel_chk __libc_core___mempmovel_chk
#endif /* ... */
#endif /* !____libc___mempmovel_chk_defined */
#ifndef ____libc___memsetw_chk_defined
#ifdef __fast___memsetw_chk_defined
#define ____libc___memsetw_chk_defined
#define __libc___memsetw_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memsetw_chk))
#elif defined(____libc_core___memsetw_chk_defined)
#define ____libc___memsetw_chk_defined
#define __libc___memsetw_chk __libc_core___memsetw_chk
#endif /* ... */
#endif /* !____libc___memsetw_chk_defined */
#ifndef ____libc___mempsetw_chk_defined
#ifdef __fast___mempsetw_chk_defined
#define ____libc___mempsetw_chk_defined
#define __libc___mempsetw_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempsetw_chk))
#elif defined(____libc_core___mempsetw_chk_defined)
#define ____libc___mempsetw_chk_defined
#define __libc___mempsetw_chk __libc_core___mempsetw_chk
#endif /* ... */
#endif /* !____libc___mempsetw_chk_defined */
#ifndef ____libc___memsetl_chk_defined
#ifdef __fast___memsetl_chk_defined
#define ____libc___memsetl_chk_defined
#define __libc___memsetl_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memsetl_chk))
#elif defined(____libc_core___memsetl_chk_defined)
#define ____libc___memsetl_chk_defined
#define __libc___memsetl_chk __libc_core___memsetl_chk
#endif /* ... */
#endif /* !____libc___memsetl_chk_defined */
#ifndef ____libc___mempsetl_chk_defined
#ifdef __fast___mempsetl_chk_defined
#define ____libc___mempsetl_chk_defined
#define __libc___mempsetl_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempsetl_chk))
#elif defined(____libc_core___mempsetl_chk_defined)
#define ____libc___mempsetl_chk_defined
#define __libc___mempsetl_chk __libc_core___mempsetl_chk
#endif /* ... */
#endif /* !____libc___mempsetl_chk_defined */
#ifndef ____libc___memmoveupw_chk_defined
#ifdef __fast___memmoveupw_chk_defined
#define ____libc___memmoveupw_chk_defined
#define __libc___memmoveupw_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmoveupw_chk))
#elif defined(____libc_core___memmoveupw_chk_defined)
#define ____libc___memmoveupw_chk_defined
#define __libc___memmoveupw_chk __libc_core___memmoveupw_chk
#endif /* ... */
#endif /* !____libc___memmoveupw_chk_defined */
#ifndef ____libc___memmovedownw_chk_defined
#ifdef __fast___memmovedownw_chk_defined
#define ____libc___memmovedownw_chk_defined
#define __libc___memmovedownw_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmovedownw_chk))
#elif defined(____libc_core___memmovedownw_chk_defined)
#define ____libc___memmovedownw_chk_defined
#define __libc___memmovedownw_chk __libc_core___memmovedownw_chk
#endif /* ... */
#endif /* !____libc___memmovedownw_chk_defined */
#ifndef ____libc___memmoveupl_chk_defined
#ifdef __fast___memmoveupl_chk_defined
#define ____libc___memmoveupl_chk_defined
#define __libc___memmoveupl_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmoveupl_chk))
#elif defined(____libc_core___memmoveupl_chk_defined)
#define ____libc___memmoveupl_chk_defined
#define __libc___memmoveupl_chk __libc_core___memmoveupl_chk
#endif /* ... */
#endif /* !____libc___memmoveupl_chk_defined */
#ifndef ____libc___memmovedownl_chk_defined
#ifdef __fast___memmovedownl_chk_defined
#define ____libc___memmovedownl_chk_defined
#define __libc___memmovedownl_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmovedownl_chk))
#elif defined(____libc_core___memmovedownl_chk_defined)
#define ____libc___memmovedownl_chk_defined
#define __libc___memmovedownl_chk __libc_core___memmovedownl_chk
#endif /* ... */
#endif /* !____libc___memmovedownl_chk_defined */
#ifndef ____libc___mempmoveupw_chk_defined
#ifdef __fast___mempmoveupw_chk_defined
#define ____libc___mempmoveupw_chk_defined
#define __libc___mempmoveupw_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmoveupw_chk))
#elif defined(____libc_core___mempmoveupw_chk_defined)
#define ____libc___mempmoveupw_chk_defined
#define __libc___mempmoveupw_chk __libc_core___mempmoveupw_chk
#endif /* ... */
#endif /* !____libc___mempmoveupw_chk_defined */
#ifndef ____libc___mempmovedownw_chk_defined
#ifdef __fast___mempmovedownw_chk_defined
#define ____libc___mempmovedownw_chk_defined
#define __libc___mempmovedownw_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmovedownw_chk))
#elif defined(____libc_core___mempmovedownw_chk_defined)
#define ____libc___mempmovedownw_chk_defined
#define __libc___mempmovedownw_chk __libc_core___mempmovedownw_chk
#endif /* ... */
#endif /* !____libc___mempmovedownw_chk_defined */
#ifndef ____libc___mempmoveupl_chk_defined
#ifdef __fast___mempmoveupl_chk_defined
#define ____libc___mempmoveupl_chk_defined
#define __libc___mempmoveupl_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmoveupl_chk))
#elif defined(____libc_core___mempmoveupl_chk_defined)
#define ____libc___mempmoveupl_chk_defined
#define __libc___mempmoveupl_chk __libc_core___mempmoveupl_chk
#endif /* ... */
#endif /* !____libc___mempmoveupl_chk_defined */
#ifndef ____libc___mempmovedownl_chk_defined
#ifdef __fast___mempmovedownl_chk_defined
#define ____libc___mempmovedownl_chk_defined
#define __libc___mempmovedownl_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmovedownl_chk))
#elif defined(____libc_core___mempmovedownl_chk_defined)
#define ____libc___mempmovedownl_chk_defined
#define __libc___mempmovedownl_chk __libc_core___mempmovedownl_chk
#endif /* ... */
#endif /* !____libc___mempmovedownl_chk_defined */
#ifndef ____libc___memcpyq_chk_defined
#ifdef __fast___memcpyq_chk_defined
#define ____libc___memcpyq_chk_defined
#define __libc___memcpyq_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memcpyq_chk))
#elif defined(____libc_core___memcpyq_chk_defined)
#define ____libc___memcpyq_chk_defined
#define __libc___memcpyq_chk __libc_core___memcpyq_chk
#endif /* ... */
#endif /* !____libc___memcpyq_chk_defined */
#ifndef ____libc___mempcpyq_chk_defined
#ifdef __fast___mempcpyq_chk_defined
#define ____libc___mempcpyq_chk_defined
#define __libc___mempcpyq_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempcpyq_chk))
#elif defined(____libc_core___mempcpyq_chk_defined)
#define ____libc___mempcpyq_chk_defined
#define __libc___mempcpyq_chk __libc_core___mempcpyq_chk
#endif /* ... */
#endif /* !____libc___mempcpyq_chk_defined */
#ifndef ____libc___memmoveq_chk_defined
#ifdef __fast___memmoveq_chk_defined
#define ____libc___memmoveq_chk_defined
#define __libc___memmoveq_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmoveq_chk))
#elif defined(____libc_core___memmoveq_chk_defined)
#define ____libc___memmoveq_chk_defined
#define __libc___memmoveq_chk __libc_core___memmoveq_chk
#endif /* ... */
#endif /* !____libc___memmoveq_chk_defined */
#ifndef ____libc___mempmoveq_chk_defined
#ifdef __fast___mempmoveq_chk_defined
#define ____libc___mempmoveq_chk_defined
#define __libc___mempmoveq_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmoveq_chk))
#elif defined(____libc_core___mempmoveq_chk_defined)
#define ____libc___mempmoveq_chk_defined
#define __libc___mempmoveq_chk __libc_core___mempmoveq_chk
#endif /* ... */
#endif /* !____libc___mempmoveq_chk_defined */
#ifndef ____libc___memsetq_chk_defined
#ifdef __fast___memsetq_chk_defined
#define ____libc___memsetq_chk_defined
#define __libc___memsetq_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memsetq_chk))
#elif defined(____libc_core___memsetq_chk_defined)
#define ____libc___memsetq_chk_defined
#define __libc___memsetq_chk __libc_core___memsetq_chk
#endif /* ... */
#endif /* !____libc___memsetq_chk_defined */
#ifndef ____libc___mempsetq_chk_defined
#ifdef __fast___mempsetq_chk_defined
#define ____libc___mempsetq_chk_defined
#define __libc___mempsetq_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempsetq_chk))
#elif defined(____libc_core___mempsetq_chk_defined)
#define ____libc___mempsetq_chk_defined
#define __libc___mempsetq_chk __libc_core___mempsetq_chk
#endif /* ... */
#endif /* !____libc___mempsetq_chk_defined */
#ifndef ____libc___memmoveupq_chk_defined
#ifdef __fast___memmoveupq_chk_defined
#define ____libc___memmoveupq_chk_defined
#define __libc___memmoveupq_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmoveupq_chk))
#elif defined(____libc_core___memmoveupq_chk_defined)
#define ____libc___memmoveupq_chk_defined
#define __libc___memmoveupq_chk __libc_core___memmoveupq_chk
#endif /* ... */
#endif /* !____libc___memmoveupq_chk_defined */
#ifndef ____libc___memmovedownq_chk_defined
#ifdef __fast___memmovedownq_chk_defined
#define ____libc___memmovedownq_chk_defined
#define __libc___memmovedownq_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmovedownq_chk))
#elif defined(____libc_core___memmovedownq_chk_defined)
#define ____libc___memmovedownq_chk_defined
#define __libc___memmovedownq_chk __libc_core___memmovedownq_chk
#endif /* ... */
#endif /* !____libc___memmovedownq_chk_defined */
#ifndef ____libc___mempmoveupq_chk_defined
#ifdef __fast___mempmoveupq_chk_defined
#define ____libc___mempmoveupq_chk_defined
#define __libc___mempmoveupq_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmoveupq_chk))
#elif defined(____libc_core___mempmoveupq_chk_defined)
#define ____libc___mempmoveupq_chk_defined
#define __libc___mempmoveupq_chk __libc_core___mempmoveupq_chk
#endif /* ... */
#endif /* !____libc___mempmoveupq_chk_defined */
#ifndef ____libc___mempmovedownq_chk_defined
#ifdef __fast___mempmovedownq_chk_defined
#define ____libc___mempmovedownq_chk_defined
#define __libc___mempmovedownq_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmovedownq_chk))
#elif defined(____libc_core___mempmovedownq_chk_defined)
#define ____libc___mempmovedownq_chk_defined
#define __libc___mempmovedownq_chk __libc_core___mempmovedownq_chk
#endif /* ... */
#endif /* !____libc___mempmovedownq_chk_defined */

#endif /* __CC__ */

#endif /* !_LIBC_SSP_STRING_H */
