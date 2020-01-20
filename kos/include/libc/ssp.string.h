/* HASH CRC-32:0x11236b8c */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
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
#include "slow/ssp.string.h"

#ifdef __fast___memcpy_chk_defined
#define __libc___memcpy_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memcpy_chk))
#else /* __fast___memcpy_chk_defined */
#define __libc___memcpy_chk __libc_slow___memcpy_chk
#endif /* !__fast___memcpy_chk_defined */
#ifdef __fast___memmove_chk_defined
#define __libc___memmove_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmove_chk))
#else /* __fast___memmove_chk_defined */
#define __libc___memmove_chk __libc_slow___memmove_chk
#endif /* !__fast___memmove_chk_defined */
#ifdef __fast___memset_chk_defined
#define __libc___memset_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memset_chk))
#else /* __fast___memset_chk_defined */
#define __libc___memset_chk __libc_slow___memset_chk
#endif /* !__fast___memset_chk_defined */
#ifdef __fast___strcat_chk_defined
#define __libc___strcat_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__strcat_chk))
#else /* __fast___strcat_chk_defined */
#define __libc___strcat_chk __libc_slow___strcat_chk
#endif /* !__fast___strcat_chk_defined */
#ifdef __fast___strcpy_chk_defined
#define __libc___strcpy_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__strcpy_chk))
#else /* __fast___strcpy_chk_defined */
#define __libc___strcpy_chk __libc_slow___strcpy_chk
#endif /* !__fast___strcpy_chk_defined */
#ifdef __fast___strncat_chk_defined
#define __libc___strncat_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__strncat_chk))
#else /* __fast___strncat_chk_defined */
#define __libc___strncat_chk __libc_slow___strncat_chk
#endif /* !__fast___strncat_chk_defined */
#ifdef __fast___strncpy_chk_defined
#define __libc___strncpy_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__strncpy_chk))
#else /* __fast___strncpy_chk_defined */
#define __libc___strncpy_chk __libc_slow___strncpy_chk
#endif /* !__fast___strncpy_chk_defined */
#ifdef __fast___mempcpy_chk_defined
#define __libc___mempcpy_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempcpy_chk))
#else /* __fast___mempcpy_chk_defined */
#define __libc___mempcpy_chk __libc_slow___mempcpy_chk
#endif /* !__fast___mempcpy_chk_defined */
#ifdef __fast___stpcpy_chk_defined
#define __libc___stpcpy_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__stpcpy_chk))
#else /* __fast___stpcpy_chk_defined */
#define __libc___stpcpy_chk __libc_slow___stpcpy_chk
#endif /* !__fast___stpcpy_chk_defined */
#ifdef __fast___stpncpy_chk_defined
#define __libc___stpncpy_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__stpncpy_chk))
#else /* __fast___stpncpy_chk_defined */
#define __libc___stpncpy_chk __libc_slow___stpncpy_chk
#endif /* !__fast___stpncpy_chk_defined */
#ifdef __fast___mempmove_chk_defined
#define __libc___mempmove_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmove_chk))
#else /* __fast___mempmove_chk_defined */
#define __libc___mempmove_chk __libc_slow___mempmove_chk
#endif /* !__fast___mempmove_chk_defined */
#ifdef __fast___mempset_chk_defined
#define __libc___mempset_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempset_chk))
#else /* __fast___mempset_chk_defined */
#define __libc___mempset_chk __libc_slow___mempset_chk
#endif /* !__fast___mempset_chk_defined */
#ifdef __fast___memmoveup_chk_defined
#define __libc___memmoveup_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmoveup_chk))
#else /* __fast___memmoveup_chk_defined */
#define __libc___memmoveup_chk __libc_slow___memmoveup_chk
#endif /* !__fast___memmoveup_chk_defined */
#ifdef __fast___memmovedown_chk_defined
#define __libc___memmovedown_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmovedown_chk))
#else /* __fast___memmovedown_chk_defined */
#define __libc___memmovedown_chk __libc_slow___memmovedown_chk
#endif /* !__fast___memmovedown_chk_defined */
#ifdef __fast___mempmoveup_chk_defined
#define __libc___mempmoveup_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmoveup_chk))
#else /* __fast___mempmoveup_chk_defined */
#define __libc___mempmoveup_chk __libc_slow___mempmoveup_chk
#endif /* !__fast___mempmoveup_chk_defined */
#ifdef __fast___mempmovedown_chk_defined
#define __libc___mempmovedown_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmovedown_chk))
#else /* __fast___mempmovedown_chk_defined */
#define __libc___mempmovedown_chk __libc_slow___mempmovedown_chk
#endif /* !__fast___mempmovedown_chk_defined */
#ifdef __fast___memcpyc_chk_defined
#define __libc___memcpyc_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memcpyc_chk))
#else /* __fast___memcpyc_chk_defined */
#define __libc___memcpyc_chk __libc_slow___memcpyc_chk
#endif /* !__fast___memcpyc_chk_defined */
#ifdef __fast___memmovec_chk_defined
#define __libc___memmovec_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmovec_chk))
#else /* __fast___memmovec_chk_defined */
#define __libc___memmovec_chk __libc_slow___memmovec_chk
#endif /* !__fast___memmovec_chk_defined */
#ifdef __fast___mempcpyc_chk_defined
#define __libc___mempcpyc_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempcpyc_chk))
#else /* __fast___mempcpyc_chk_defined */
#define __libc___mempcpyc_chk __libc_slow___mempcpyc_chk
#endif /* !__fast___mempcpyc_chk_defined */
#ifdef __fast___mempmovec_chk_defined
#define __libc___mempmovec_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmovec_chk))
#else /* __fast___mempmovec_chk_defined */
#define __libc___mempmovec_chk __libc_slow___mempmovec_chk
#endif /* !__fast___mempmovec_chk_defined */
#ifdef __fast___memmoveupc_chk_defined
#define __libc___memmoveupc_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmoveupc_chk))
#else /* __fast___memmoveupc_chk_defined */
#define __libc___memmoveupc_chk __libc_slow___memmoveupc_chk
#endif /* !__fast___memmoveupc_chk_defined */
#ifdef __fast___memmovedownc_chk_defined
#define __libc___memmovedownc_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmovedownc_chk))
#else /* __fast___memmovedownc_chk_defined */
#define __libc___memmovedownc_chk __libc_slow___memmovedownc_chk
#endif /* !__fast___memmovedownc_chk_defined */
#ifdef __fast___mempmoveupc_chk_defined
#define __libc___mempmoveupc_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmoveupc_chk))
#else /* __fast___mempmoveupc_chk_defined */
#define __libc___mempmoveupc_chk __libc_slow___mempmoveupc_chk
#endif /* !__fast___mempmoveupc_chk_defined */
#ifdef __fast___mempmovedownc_chk_defined
#define __libc___mempmovedownc_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmovedownc_chk))
#else /* __fast___mempmovedownc_chk_defined */
#define __libc___mempmovedownc_chk __libc_slow___mempmovedownc_chk
#endif /* !__fast___mempmovedownc_chk_defined */
#ifdef __fast___memcpyw_chk_defined
#define __libc___memcpyw_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memcpyw_chk))
#else /* __fast___memcpyw_chk_defined */
#define __libc___memcpyw_chk __libc_slow___memcpyw_chk
#endif /* !__fast___memcpyw_chk_defined */
#ifdef __fast___mempcpyw_chk_defined
#define __libc___mempcpyw_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempcpyw_chk))
#else /* __fast___mempcpyw_chk_defined */
#define __libc___mempcpyw_chk __libc_slow___mempcpyw_chk
#endif /* !__fast___mempcpyw_chk_defined */
#ifdef __fast___memmovew_chk_defined
#define __libc___memmovew_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmovew_chk))
#else /* __fast___memmovew_chk_defined */
#define __libc___memmovew_chk __libc_slow___memmovew_chk
#endif /* !__fast___memmovew_chk_defined */
#ifdef __fast___memcpyl_chk_defined
#define __libc___memcpyl_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memcpyl_chk))
#else /* __fast___memcpyl_chk_defined */
#define __libc___memcpyl_chk __libc_slow___memcpyl_chk
#endif /* !__fast___memcpyl_chk_defined */
#ifdef __fast___mempcpyl_chk_defined
#define __libc___mempcpyl_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempcpyl_chk))
#else /* __fast___mempcpyl_chk_defined */
#define __libc___mempcpyl_chk __libc_slow___mempcpyl_chk
#endif /* !__fast___mempcpyl_chk_defined */
#ifdef __fast___memmovel_chk_defined
#define __libc___memmovel_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmovel_chk))
#else /* __fast___memmovel_chk_defined */
#define __libc___memmovel_chk __libc_slow___memmovel_chk
#endif /* !__fast___memmovel_chk_defined */
#ifdef __fast___mempmovew_chk_defined
#define __libc___mempmovew_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmovew_chk))
#else /* __fast___mempmovew_chk_defined */
#define __libc___mempmovew_chk __libc_slow___mempmovew_chk
#endif /* !__fast___mempmovew_chk_defined */
#ifdef __fast___mempmovel_chk_defined
#define __libc___mempmovel_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmovel_chk))
#else /* __fast___mempmovel_chk_defined */
#define __libc___mempmovel_chk __libc_slow___mempmovel_chk
#endif /* !__fast___mempmovel_chk_defined */
#ifdef __fast___memsetw_chk_defined
#define __libc___memsetw_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memsetw_chk))
#else /* __fast___memsetw_chk_defined */
#define __libc___memsetw_chk __libc_slow___memsetw_chk
#endif /* !__fast___memsetw_chk_defined */
#ifdef __fast___mempsetw_chk_defined
#define __libc___mempsetw_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempsetw_chk))
#else /* __fast___mempsetw_chk_defined */
#define __libc___mempsetw_chk __libc_slow___mempsetw_chk
#endif /* !__fast___mempsetw_chk_defined */
#ifdef __fast___memsetl_chk_defined
#define __libc___memsetl_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memsetl_chk))
#else /* __fast___memsetl_chk_defined */
#define __libc___memsetl_chk __libc_slow___memsetl_chk
#endif /* !__fast___memsetl_chk_defined */
#ifdef __fast___mempsetl_chk_defined
#define __libc___mempsetl_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempsetl_chk))
#else /* __fast___mempsetl_chk_defined */
#define __libc___mempsetl_chk __libc_slow___mempsetl_chk
#endif /* !__fast___mempsetl_chk_defined */
#ifdef __fast___memmoveupw_chk_defined
#define __libc___memmoveupw_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmoveupw_chk))
#else /* __fast___memmoveupw_chk_defined */
#define __libc___memmoveupw_chk __libc_slow___memmoveupw_chk
#endif /* !__fast___memmoveupw_chk_defined */
#ifdef __fast___memmovedownw_chk_defined
#define __libc___memmovedownw_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmovedownw_chk))
#else /* __fast___memmovedownw_chk_defined */
#define __libc___memmovedownw_chk __libc_slow___memmovedownw_chk
#endif /* !__fast___memmovedownw_chk_defined */
#ifdef __fast___memmoveupl_chk_defined
#define __libc___memmoveupl_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmoveupl_chk))
#else /* __fast___memmoveupl_chk_defined */
#define __libc___memmoveupl_chk __libc_slow___memmoveupl_chk
#endif /* !__fast___memmoveupl_chk_defined */
#ifdef __fast___memmovedownl_chk_defined
#define __libc___memmovedownl_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmovedownl_chk))
#else /* __fast___memmovedownl_chk_defined */
#define __libc___memmovedownl_chk __libc_slow___memmovedownl_chk
#endif /* !__fast___memmovedownl_chk_defined */
#ifdef __fast___mempmoveupw_chk_defined
#define __libc___mempmoveupw_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmoveupw_chk))
#else /* __fast___mempmoveupw_chk_defined */
#define __libc___mempmoveupw_chk __libc_slow___mempmoveupw_chk
#endif /* !__fast___mempmoveupw_chk_defined */
#ifdef __fast___mempmovedownw_chk_defined
#define __libc___mempmovedownw_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmovedownw_chk))
#else /* __fast___mempmovedownw_chk_defined */
#define __libc___mempmovedownw_chk __libc_slow___mempmovedownw_chk
#endif /* !__fast___mempmovedownw_chk_defined */
#ifdef __fast___mempmoveupl_chk_defined
#define __libc___mempmoveupl_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmoveupl_chk))
#else /* __fast___mempmoveupl_chk_defined */
#define __libc___mempmoveupl_chk __libc_slow___mempmoveupl_chk
#endif /* !__fast___mempmoveupl_chk_defined */
#ifdef __fast___mempmovedownl_chk_defined
#define __libc___mempmovedownl_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmovedownl_chk))
#else /* __fast___mempmovedownl_chk_defined */
#define __libc___mempmovedownl_chk __libc_slow___mempmovedownl_chk
#endif /* !__fast___mempmovedownl_chk_defined */
#ifdef __fast___memcpyq_chk_defined
#define __libc___memcpyq_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memcpyq_chk))
#else /* __fast___memcpyq_chk_defined */
#define __libc___memcpyq_chk __libc_slow___memcpyq_chk
#endif /* !__fast___memcpyq_chk_defined */
#ifdef __fast___mempcpyq_chk_defined
#define __libc___mempcpyq_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempcpyq_chk))
#else /* __fast___mempcpyq_chk_defined */
#define __libc___mempcpyq_chk __libc_slow___mempcpyq_chk
#endif /* !__fast___mempcpyq_chk_defined */
#ifdef __fast___memmoveq_chk_defined
#define __libc___memmoveq_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmoveq_chk))
#else /* __fast___memmoveq_chk_defined */
#define __libc___memmoveq_chk __libc_slow___memmoveq_chk
#endif /* !__fast___memmoveq_chk_defined */
#ifdef __fast___mempmoveq_chk_defined
#define __libc___mempmoveq_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmoveq_chk))
#else /* __fast___mempmoveq_chk_defined */
#define __libc___mempmoveq_chk __libc_slow___mempmoveq_chk
#endif /* !__fast___mempmoveq_chk_defined */
#ifdef __fast___memsetq_chk_defined
#define __libc___memsetq_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memsetq_chk))
#else /* __fast___memsetq_chk_defined */
#define __libc___memsetq_chk __libc_slow___memsetq_chk
#endif /* !__fast___memsetq_chk_defined */
#ifdef __fast___mempsetq_chk_defined
#define __libc___mempsetq_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempsetq_chk))
#else /* __fast___mempsetq_chk_defined */
#define __libc___mempsetq_chk __libc_slow___mempsetq_chk
#endif /* !__fast___mempsetq_chk_defined */
#ifdef __fast___memmoveupq_chk_defined
#define __libc___memmoveupq_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmoveupq_chk))
#else /* __fast___memmoveupq_chk_defined */
#define __libc___memmoveupq_chk __libc_slow___memmoveupq_chk
#endif /* !__fast___memmoveupq_chk_defined */
#ifdef __fast___memmovedownq_chk_defined
#define __libc___memmovedownq_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmovedownq_chk))
#else /* __fast___memmovedownq_chk_defined */
#define __libc___memmovedownq_chk __libc_slow___memmovedownq_chk
#endif /* !__fast___memmovedownq_chk_defined */
#ifdef __fast___mempmoveupq_chk_defined
#define __libc___mempmoveupq_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmoveupq_chk))
#else /* __fast___mempmoveupq_chk_defined */
#define __libc___mempmoveupq_chk __libc_slow___mempmoveupq_chk
#endif /* !__fast___mempmoveupq_chk_defined */
#ifdef __fast___mempmovedownq_chk_defined
#define __libc___mempmovedownq_chk (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmovedownq_chk))
#else /* __fast___mempmovedownq_chk_defined */
#define __libc___mempmovedownq_chk __libc_slow___mempmovedownq_chk
#endif /* !__fast___mempmovedownq_chk_defined */

#endif /* __CC__ */

#endif /* !_LIBC_SSP_STRING_H */
