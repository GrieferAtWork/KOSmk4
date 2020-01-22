/* HASH CRC-32:0xfc15ed75 */
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
#ifndef _LIBC_CORE_SSP_STRING_H
#define _LIBC_CORE_SSP_STRING_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

#ifdef __CRT_HAVE___memcpy_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___memcpy_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize),__memcpy_chk,(__dst,__src,__n_bytes,__dst_objsize))
#else /* LIBC: __memcpy_chk */
#include <local/ssp.string/__memcpy_chk.h>
#define __libc_core___memcpy_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memcpy_chk))
#endif /* __memcpy_chk... */
#ifdef __CRT_HAVE___memmove_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___memmove_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize),__memmove_chk,(__dst,__src,__n_bytes,__dst_objsize))
#else /* LIBC: __memmove_chk */
#include <local/ssp.string/__memmove_chk.h>
#define __libc_core___memmove_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmove_chk))
#endif /* __memmove_chk... */
#ifdef __CRT_HAVE___memset_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__libc_core___memset_chk,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize),__memset_chk,(__dst,__byte,__n_bytes,__dst_objsize))
#else /* LIBC: __memset_chk */
#include <local/ssp.string/__memset_chk.h>
#define __libc_core___memset_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memset_chk))
#endif /* __memset_chk... */
#ifdef __CRT_HAVE___strcat_chk
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__libc_core___strcat_chk,(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __dst_objsize),__strcat_chk,(__dst,__src,__dst_objsize))
#else /* LIBC: __strcat_chk */
#include <local/ssp.string/__strcat_chk.h>
#define __libc_core___strcat_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__strcat_chk))
#endif /* __strcat_chk... */
#ifdef __CRT_HAVE___strcpy_chk
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__libc_core___strcpy_chk,(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __dst_objsize),__strcpy_chk,(__dst,__src,__dst_objsize))
#else /* LIBC: __strcpy_chk */
#include <local/ssp.string/__strcpy_chk.h>
#define __libc_core___strcpy_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__strcpy_chk))
#endif /* __strcpy_chk... */
#ifdef __CRT_HAVE___strncat_chk
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__libc_core___strncat_chk,(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __buflen, __SIZE_TYPE__ __dst_objsize),__strncat_chk,(__dst,__src,__buflen,__dst_objsize))
#else /* LIBC: __strncat_chk */
#include <local/ssp.string/__strncat_chk.h>
#define __libc_core___strncat_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__strncat_chk))
#endif /* __strncat_chk... */
#ifdef __CRT_HAVE___strncpy_chk
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__libc_core___strncpy_chk,(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __buflen, __SIZE_TYPE__ __dst_objsize),__strncpy_chk,(__dst,__src,__buflen,__dst_objsize))
#else /* LIBC: __strncpy_chk */
#include <local/ssp.string/__strncpy_chk.h>
#define __libc_core___strncpy_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__strncpy_chk))
#endif /* __strncpy_chk... */
#ifdef __CRT_HAVE___mempcpy_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___mempcpy_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize),__mempcpy_chk,(__dst,__src,__n_bytes,__dst_objsize))
#else /* LIBC: __mempcpy_chk */
#include <local/ssp.string/__mempcpy_chk.h>
#define __libc_core___mempcpy_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempcpy_chk))
#endif /* __mempcpy_chk... */
#ifdef __CRT_HAVE___stpcpy_chk
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__libc_core___stpcpy_chk,(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __dst_objsize),__stpcpy_chk,(__dst,__src,__dst_objsize))
#else /* LIBC: __stpcpy_chk */
#include <local/ssp.string/__stpcpy_chk.h>
#define __libc_core___stpcpy_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__stpcpy_chk))
#endif /* __stpcpy_chk... */
#ifdef __CRT_HAVE___stpncpy_chk
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__libc_core___stpncpy_chk,(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __buflen, __SIZE_TYPE__ __dst_objsize),__stpncpy_chk,(__dst,__src,__buflen,__dst_objsize))
#else /* LIBC: __stpncpy_chk */
#include <local/ssp.string/__stpncpy_chk.h>
#define __libc_core___stpncpy_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__stpncpy_chk))
#endif /* __stpncpy_chk... */
#ifdef __CRT_HAVE___mempmove_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___mempmove_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize),__mempmove_chk,(__dst,__src,__n_bytes,__dst_objsize))
#else /* LIBC: __mempmove_chk */
#include <local/ssp.string/__mempmove_chk.h>
#define __libc_core___mempmove_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmove_chk))
#endif /* __mempmove_chk... */
#ifdef __CRT_HAVE___mempset_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__libc_core___mempset_chk,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize),__mempset_chk,(__dst,__byte,__n_bytes,__dst_objsize))
#else /* LIBC: __mempset_chk */
#include <local/ssp.string/__mempset_chk.h>
#define __libc_core___mempset_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempset_chk))
#endif /* __mempset_chk... */
#ifdef __CRT_HAVE___memmoveup_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___memmoveup_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize),__memmoveup_chk,(__dst,__src,__n_bytes,__dst_objsize))
#else /* LIBC: __memmoveup_chk */
#include <local/ssp.string/__memmoveup_chk.h>
#define __libc_core___memmoveup_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmoveup_chk))
#endif /* __memmoveup_chk... */
#ifdef __CRT_HAVE___memmovedown_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___memmovedown_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize),__memmovedown_chk,(__dst,__src,__n_bytes,__dst_objsize))
#else /* LIBC: __memmovedown_chk */
#include <local/ssp.string/__memmovedown_chk.h>
#define __libc_core___memmovedown_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmovedown_chk))
#endif /* __memmovedown_chk... */
#ifdef __CRT_HAVE___mempmoveup_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___mempmoveup_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize),__mempmoveup_chk,(__dst,__src,__n_bytes,__dst_objsize))
#else /* LIBC: __mempmoveup_chk */
#include <local/ssp.string/__mempmoveup_chk.h>
#define __libc_core___mempmoveup_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmoveup_chk))
#endif /* __mempmoveup_chk... */
#ifdef __CRT_HAVE___mempmovedown_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___mempmovedown_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize),__mempmovedown_chk,(__dst,__src,__n_bytes,__dst_objsize))
#else /* LIBC: __mempmovedown_chk */
#include <local/ssp.string/__mempmovedown_chk.h>
#define __libc_core___mempmovedown_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmovedown_chk))
#endif /* __mempmovedown_chk... */
#ifdef __CRT_HAVE___memcpyc_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___memcpyc_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize),__memcpyc_chk,(__dst,__src,__elem_count,__elem_size,__dst_objsize))
#else /* LIBC: __memcpyc_chk */
#include <local/ssp.string/__memcpyc_chk.h>
#define __libc_core___memcpyc_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memcpyc_chk))
#endif /* __memcpyc_chk... */
#ifdef __CRT_HAVE___memmovec_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___memmovec_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize),__memmovec_chk,(__dst,__src,__elem_count,__elem_size,__dst_objsize))
#else /* LIBC: __memmovec_chk */
#include <local/ssp.string/__memmovec_chk.h>
#define __libc_core___memmovec_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmovec_chk))
#endif /* __memmovec_chk... */
#ifdef __CRT_HAVE___mempcpyc_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___mempcpyc_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize),__mempcpyc_chk,(__dst,__src,__elem_count,__elem_size,__dst_objsize))
#else /* LIBC: __mempcpyc_chk */
#include <local/ssp.string/__mempcpyc_chk.h>
#define __libc_core___mempcpyc_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempcpyc_chk))
#endif /* __mempcpyc_chk... */
#ifdef __CRT_HAVE___mempmovec_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___mempmovec_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize),__mempmovec_chk,(__dst,__src,__elem_count,__elem_size,__dst_objsize))
#else /* LIBC: __mempmovec_chk */
#include <local/ssp.string/__mempmovec_chk.h>
#define __libc_core___mempmovec_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmovec_chk))
#endif /* __mempmovec_chk... */
#ifdef __CRT_HAVE___memmoveupc_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___memmoveupc_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize),__memmoveupc_chk,(__dst,__src,__elem_count,__elem_size,__dst_objsize))
#else /* LIBC: __memmoveupc_chk */
#include <local/ssp.string/__memmoveupc_chk.h>
#define __libc_core___memmoveupc_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmoveupc_chk))
#endif /* __memmoveupc_chk... */
#ifdef __CRT_HAVE___memmovedownc_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___memmovedownc_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize),__memmovedownc_chk,(__dst,__src,__elem_count,__elem_size,__dst_objsize))
#else /* LIBC: __memmovedownc_chk */
#include <local/ssp.string/__memmovedownc_chk.h>
#define __libc_core___memmovedownc_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmovedownc_chk))
#endif /* __memmovedownc_chk... */
#ifdef __CRT_HAVE___mempmoveupc_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___mempmoveupc_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize),__mempmoveupc_chk,(__dst,__src,__elem_count,__elem_size,__dst_objsize))
#else /* LIBC: __mempmoveupc_chk */
#include <local/ssp.string/__mempmoveupc_chk.h>
#define __libc_core___mempmoveupc_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmoveupc_chk))
#endif /* __mempmoveupc_chk... */
#ifdef __CRT_HAVE___mempmovedownc_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___mempmovedownc_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize),__mempmovedownc_chk,(__dst,__src,__elem_count,__elem_size,__dst_objsize))
#else /* LIBC: __mempmovedownc_chk */
#include <local/ssp.string/__mempmovedownc_chk.h>
#define __libc_core___mempmovedownc_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmovedownc_chk))
#endif /* __mempmovedownc_chk... */
#ifdef __CRT_HAVE___memcpyw_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___memcpyw_chk,(/*aligned(2)*/ void *__restrict __dst, /*aligned(2)*/ void const *__restrict __src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__memcpyw_chk,(__dst,__src,__n_words,__dst_objsize))
#elif defined(__CRT_HAVE___wmemcpy_chk) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___memcpyw_chk,(/*aligned(2)*/ void *__restrict __dst, /*aligned(2)*/ void const *__restrict __src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__wmemcpy_chk,(__dst,__src,__n_words,__dst_objsize))
#else /* LIBC: __memcpyw_chk */
#include <local/ssp.string/__memcpyw_chk.h>
#define __libc_core___memcpyw_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memcpyw_chk))
#endif /* __memcpyw_chk... */
#ifdef __CRT_HAVE___mempcpyw_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___mempcpyw_chk,(/*aligned(2)*/ void *__restrict __dst, /*aligned(2)*/ void const *__restrict __src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__mempcpyw_chk,(__dst,__src,__n_words,__dst_objsize))
#elif defined(__CRT_HAVE___wmempcpy_chk) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___mempcpyw_chk,(/*aligned(2)*/ void *__restrict __dst, /*aligned(2)*/ void const *__restrict __src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__wmempcpy_chk,(__dst,__src,__n_words,__dst_objsize))
#else /* LIBC: __mempcpyw_chk */
#include <local/ssp.string/__mempcpyw_chk.h>
#define __libc_core___mempcpyw_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempcpyw_chk))
#endif /* __mempcpyw_chk... */
#ifdef __CRT_HAVE___memmovew_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___memmovew_chk,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__memmovew_chk,(__dst,__src,__n_words,__dst_objsize))
#elif defined(__CRT_HAVE___wmemmove_chk) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___memmovew_chk,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__wmemmove_chk,(__dst,__src,__n_words,__dst_objsize))
#else /* LIBC: __memmovew_chk */
#include <local/ssp.string/__memmovew_chk.h>
#define __libc_core___memmovew_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmovew_chk))
#endif /* __memmovew_chk... */
#ifdef __CRT_HAVE___memcpyl_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___memcpyl_chk,(/*aligned(4)*/ void *__restrict __dst, /*aligned(4)*/ void const *__restrict __src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__memcpyl_chk,(__dst,__src,__n_dwords,__dst_objsize))
#elif defined(__CRT_HAVE___wmemcpy_chk) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___memcpyl_chk,(/*aligned(4)*/ void *__restrict __dst, /*aligned(4)*/ void const *__restrict __src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__wmemcpy_chk,(__dst,__src,__n_dwords,__dst_objsize))
#else /* LIBC: __memcpyl_chk */
#include <local/ssp.string/__memcpyl_chk.h>
#define __libc_core___memcpyl_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memcpyl_chk))
#endif /* __memcpyl_chk... */
#ifdef __CRT_HAVE___mempcpyl_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___mempcpyl_chk,(/*aligned(4)*/ void *__restrict __dst, /*aligned(4)*/ void const *__restrict __src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__mempcpyl_chk,(__dst,__src,__n_dwords,__dst_objsize))
#elif defined(__CRT_HAVE___wmempcpy_chk) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___mempcpyl_chk,(/*aligned(4)*/ void *__restrict __dst, /*aligned(4)*/ void const *__restrict __src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__wmempcpy_chk,(__dst,__src,__n_dwords,__dst_objsize))
#else /* LIBC: __mempcpyl_chk */
#include <local/ssp.string/__mempcpyl_chk.h>
#define __libc_core___mempcpyl_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempcpyl_chk))
#endif /* __mempcpyl_chk... */
#ifdef __CRT_HAVE___memmovel_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___memmovel_chk,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__memmovel_chk,(__dst,__src,__n_dwords,__dst_objsize))
#elif defined(__CRT_HAVE___wmemmove_chk) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___memmovel_chk,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__wmemmove_chk,(__dst,__src,__n_dwords,__dst_objsize))
#else /* LIBC: __memmovel_chk */
#include <local/ssp.string/__memmovel_chk.h>
#define __libc_core___memmovel_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmovel_chk))
#endif /* __memmovel_chk... */
#ifdef __CRT_HAVE___mempmovew_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___mempmovew_chk,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__mempmovew_chk,(__dst,__src,__n_words,__dst_objsize))
#else /* LIBC: __mempmovew_chk */
#include <local/ssp.string/__mempmovew_chk.h>
#define __libc_core___mempmovew_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmovew_chk))
#endif /* __mempmovew_chk... */
#ifdef __CRT_HAVE___mempmovel_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___mempmovel_chk,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__mempmovel_chk,(__dst,__src,__n_dwords,__dst_objsize))
#else /* LIBC: __mempmovel_chk */
#include <local/ssp.string/__mempmovel_chk.h>
#define __libc_core___mempmovel_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmovel_chk))
#endif /* __mempmovel_chk... */
#ifdef __CRT_HAVE___memsetw_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___memsetw_chk,(/*aligned(2)*/ void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__memsetw_chk,(__dst,__word,__n_words,__dst_objsize))
#else /* LIBC: __memsetw_chk */
#include <local/ssp.string/__memsetw_chk.h>
#define __libc_core___memsetw_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memsetw_chk))
#endif /* __memsetw_chk... */
#ifdef __CRT_HAVE___mempsetw_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___mempsetw_chk,(/*aligned(2)*/ void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__mempsetw_chk,(__dst,__word,__n_words,__dst_objsize))
#else /* LIBC: __mempsetw_chk */
#include <local/ssp.string/__mempsetw_chk.h>
#define __libc_core___mempsetw_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempsetw_chk))
#endif /* __mempsetw_chk... */
#ifdef __CRT_HAVE___memsetl_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___memsetl_chk,(/*aligned(4)*/ void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__memsetl_chk,(__dst,__dword,__n_dwords,__dst_objsize))
#else /* LIBC: __memsetl_chk */
#include <local/ssp.string/__memsetl_chk.h>
#define __libc_core___memsetl_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memsetl_chk))
#endif /* __memsetl_chk... */
#ifdef __CRT_HAVE___mempsetl_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___mempsetl_chk,(/*aligned(4)*/ void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__mempsetl_chk,(__dst,__dword,__n_dwords,__dst_objsize))
#else /* LIBC: __mempsetl_chk */
#include <local/ssp.string/__mempsetl_chk.h>
#define __libc_core___mempsetl_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempsetl_chk))
#endif /* __mempsetl_chk... */
#ifdef __CRT_HAVE___memmoveupw_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___memmoveupw_chk,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__memmoveupw_chk,(__dst,__src,__n_words,__dst_objsize))
#elif defined(__CRT_HAVE___memmovew_chk)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___memmoveupw_chk,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__memmovew_chk,(__dst,__src,__n_words,__dst_objsize))
#elif defined(__CRT_HAVE___wmemmove_chk) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___memmoveupw_chk,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__wmemmove_chk,(__dst,__src,__n_words,__dst_objsize))
#else /* LIBC: __memmoveupw_chk */
#include <local/ssp.string/__memmoveupw_chk.h>
#define __libc_core___memmoveupw_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmoveupw_chk))
#endif /* __memmoveupw_chk... */
#ifdef __CRT_HAVE___memmovedownw_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___memmovedownw_chk,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__memmovedownw_chk,(__dst,__src,__n_words,__dst_objsize))
#elif defined(__CRT_HAVE___memmovew_chk)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___memmovedownw_chk,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__memmovew_chk,(__dst,__src,__n_words,__dst_objsize))
#elif defined(__CRT_HAVE___wmemmove_chk) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___memmovedownw_chk,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__wmemmove_chk,(__dst,__src,__n_words,__dst_objsize))
#else /* LIBC: __memmovedownw_chk */
#include <local/ssp.string/__memmovedownw_chk.h>
#define __libc_core___memmovedownw_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmovedownw_chk))
#endif /* __memmovedownw_chk... */
#ifdef __CRT_HAVE___memmoveupl_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___memmoveupl_chk,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__memmoveupl_chk,(__dst,__src,__n_dwords,__dst_objsize))
#elif defined(__CRT_HAVE___memmovel_chk)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___memmoveupl_chk,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__memmovel_chk,(__dst,__src,__n_dwords,__dst_objsize))
#elif defined(__CRT_HAVE___wmemmove_chk) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___memmoveupl_chk,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__wmemmove_chk,(__dst,__src,__n_dwords,__dst_objsize))
#else /* LIBC: __memmoveupl_chk */
#include <local/ssp.string/__memmoveupl_chk.h>
#define __libc_core___memmoveupl_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmoveupl_chk))
#endif /* __memmoveupl_chk... */
#ifdef __CRT_HAVE___memmovedownl_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___memmovedownl_chk,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__memmovedownl_chk,(__dst,__src,__n_dwords,__dst_objsize))
#elif defined(__CRT_HAVE___memmovel_chk)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___memmovedownl_chk,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__memmovel_chk,(__dst,__src,__n_dwords,__dst_objsize))
#elif defined(__CRT_HAVE___wmemmove_chk) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___memmovedownl_chk,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__wmemmove_chk,(__dst,__src,__n_dwords,__dst_objsize))
#else /* LIBC: __memmovedownl_chk */
#include <local/ssp.string/__memmovedownl_chk.h>
#define __libc_core___memmovedownl_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmovedownl_chk))
#endif /* __memmovedownl_chk... */
#ifdef __CRT_HAVE___mempmoveupw_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___mempmoveupw_chk,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__mempmoveupw_chk,(__dst,__src,__n_words,__dst_objsize))
#elif defined(__CRT_HAVE___mempmovew_chk)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___mempmoveupw_chk,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__mempmovew_chk,(__dst,__src,__n_words,__dst_objsize))
#else /* LIBC: __mempmoveupw_chk */
#include <local/ssp.string/__mempmoveupw_chk.h>
#define __libc_core___mempmoveupw_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmoveupw_chk))
#endif /* __mempmoveupw_chk... */
#ifdef __CRT_HAVE___mempmovedownw_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___mempmovedownw_chk,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__mempmovedownw_chk,(__dst,__src,__n_words,__dst_objsize))
#elif defined(__CRT_HAVE___mempmovew_chk)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___mempmovedownw_chk,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__mempmovew_chk,(__dst,__src,__n_words,__dst_objsize))
#else /* LIBC: __mempmovedownw_chk */
#include <local/ssp.string/__mempmovedownw_chk.h>
#define __libc_core___mempmovedownw_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmovedownw_chk))
#endif /* __mempmovedownw_chk... */
#ifdef __CRT_HAVE___mempmoveupl_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___mempmoveupl_chk,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__mempmoveupl_chk,(__dst,__src,__n_dwords,__dst_objsize))
#elif defined(__CRT_HAVE___mempmovel_chk)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___mempmoveupl_chk,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__mempmovel_chk,(__dst,__src,__n_dwords,__dst_objsize))
#else /* LIBC: __mempmoveupl_chk */
#include <local/ssp.string/__mempmoveupl_chk.h>
#define __libc_core___mempmoveupl_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmoveupl_chk))
#endif /* __mempmoveupl_chk... */
#ifdef __CRT_HAVE___mempmovedownl_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___mempmovedownl_chk,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__mempmovedownl_chk,(__dst,__src,__n_dwords,__dst_objsize))
#elif defined(__CRT_HAVE___mempmovel_chk)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___mempmovedownl_chk,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__mempmovel_chk,(__dst,__src,__n_dwords,__dst_objsize))
#else /* LIBC: __mempmovedownl_chk */
#include <local/ssp.string/__mempmovedownl_chk.h>
#define __libc_core___mempmovedownl_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmovedownl_chk))
#endif /* __mempmovedownl_chk... */
#ifdef __CRT_HAVE___memcpyq_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core___memcpyq_chk,(/*aligned(8)*/ void *__restrict __dst, /*aligned(8)*/ void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__memcpyq_chk,(__dst,__src,__n_qwords,__dst_objsize))
#else /* LIBC: __memcpyq_chk */
#include <local/ssp.string/__memcpyq_chk.h>
#define __libc_core___memcpyq_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memcpyq_chk))
#endif /* __memcpyq_chk... */
#ifdef __CRT_HAVE___mempcpyq_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core___mempcpyq_chk,(/*aligned(8)*/ void *__restrict __dst, /*aligned(8)*/ void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__mempcpyq_chk,(__dst,__src,__n_qwords,__dst_objsize))
#else /* LIBC: __mempcpyq_chk */
#include <local/ssp.string/__mempcpyq_chk.h>
#define __libc_core___mempcpyq_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempcpyq_chk))
#endif /* __mempcpyq_chk... */
#ifdef __CRT_HAVE___memmoveq_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core___memmoveq_chk,(/*aligned(8)*/ void *__dst, /*aligned(8)*/ void const *__src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__memmoveq_chk,(__dst,__src,__n_qwords,__dst_objsize))
#else /* LIBC: __memmoveq_chk */
#include <local/ssp.string/__memmoveq_chk.h>
#define __libc_core___memmoveq_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmoveq_chk))
#endif /* __memmoveq_chk... */
#ifdef __CRT_HAVE___mempmoveq_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core___mempmoveq_chk,(/*aligned(8)*/ void *__restrict __dst, /*aligned(8)*/ void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__mempmoveq_chk,(__dst,__src,__n_qwords,__dst_objsize))
#else /* LIBC: __mempmoveq_chk */
#include <local/ssp.string/__mempmoveq_chk.h>
#define __libc_core___mempmoveq_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmoveq_chk))
#endif /* __mempmoveq_chk... */
#ifdef __CRT_HAVE___memsetq_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core___memsetq_chk,(/*aligned(8)*/ void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__memsetq_chk,(__dst,__qword,__n_qwords,__dst_objsize))
#else /* LIBC: __memsetq_chk */
#include <local/ssp.string/__memsetq_chk.h>
#define __libc_core___memsetq_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memsetq_chk))
#endif /* __memsetq_chk... */
#ifdef __CRT_HAVE___mempsetq_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core___mempsetq_chk,(/*aligned(8)*/ void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__mempsetq_chk,(__dst,__qword,__n_qwords,__dst_objsize))
#else /* LIBC: __mempsetq_chk */
#include <local/ssp.string/__mempsetq_chk.h>
#define __libc_core___mempsetq_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempsetq_chk))
#endif /* __mempsetq_chk... */
#ifdef __CRT_HAVE___memmoveupq_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core___memmoveupq_chk,(/*aligned(8)*/ void *__dst, /*aligned(8)*/ void const *__src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__memmoveupq_chk,(__dst,__src,__n_qwords,__dst_objsize))
#elif defined(__CRT_HAVE___memmoveq_chk)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core___memmoveupq_chk,(/*aligned(8)*/ void *__dst, /*aligned(8)*/ void const *__src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__memmoveq_chk,(__dst,__src,__n_qwords,__dst_objsize))
#else /* LIBC: __memmoveupq_chk */
#include <local/ssp.string/__memmoveupq_chk.h>
#define __libc_core___memmoveupq_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmoveupq_chk))
#endif /* __memmoveupq_chk... */
#ifdef __CRT_HAVE___memmovedownq_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core___memmovedownq_chk,(/*aligned(8)*/ void *__dst, /*aligned(8)*/ void const *__src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__memmovedownq_chk,(__dst,__src,__n_qwords,__dst_objsize))
#elif defined(__CRT_HAVE___memmoveq_chk)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core___memmovedownq_chk,(/*aligned(8)*/ void *__dst, /*aligned(8)*/ void const *__src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__memmoveq_chk,(__dst,__src,__n_qwords,__dst_objsize))
#else /* LIBC: __memmovedownq_chk */
#include <local/ssp.string/__memmovedownq_chk.h>
#define __libc_core___memmovedownq_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmovedownq_chk))
#endif /* __memmovedownq_chk... */
#ifdef __CRT_HAVE___mempmoveupq_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core___mempmoveupq_chk,(/*aligned(8)*/ void *__restrict __dst, /*aligned(8)*/ void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__mempmoveupq_chk,(__dst,__src,__n_qwords,__dst_objsize))
#elif defined(__CRT_HAVE___mempmoveq_chk)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core___mempmoveupq_chk,(/*aligned(8)*/ void *__restrict __dst, /*aligned(8)*/ void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__mempmoveq_chk,(__dst,__src,__n_qwords,__dst_objsize))
#else /* LIBC: __mempmoveupq_chk */
#include <local/ssp.string/__mempmoveupq_chk.h>
#define __libc_core___mempmoveupq_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmoveupq_chk))
#endif /* __mempmoveupq_chk... */
#ifdef __CRT_HAVE___mempmovedownq_chk
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core___mempmovedownq_chk,(/*aligned(8)*/ void *__restrict __dst, /*aligned(8)*/ void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__mempmovedownq_chk,(__dst,__src,__n_qwords,__dst_objsize))
#elif defined(__CRT_HAVE___mempmoveq_chk)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core___mempmovedownq_chk,(/*aligned(8)*/ void *__restrict __dst, /*aligned(8)*/ void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__mempmoveq_chk,(__dst,__src,__n_qwords,__dst_objsize))
#else /* LIBC: __mempmovedownq_chk */
#include <local/ssp.string/__mempmovedownq_chk.h>
#define __libc_core___mempmovedownq_chk (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmovedownq_chk))
#endif /* __mempmovedownq_chk... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_LIBC_CORE_SSP_STRING_H */
