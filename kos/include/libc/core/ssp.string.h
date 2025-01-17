/* HASH CRC-32:0x5b39c3e3 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
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

#ifndef ____libc_core___memcpy_chk_defined
#define ____libc_core___memcpy_chk_defined
#ifdef __CRT_HAVE___memcpy_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___memcpy_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize),__memcpy_chk,(__dst,__src,__n_bytes,__dst_objsize))
#else /* __CRT_HAVE___memcpy_chk */
#include <libc/local/ssp.string/__memcpy_chk.h>
#define __libc_core___memcpy_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memcpy_chk)
#endif /* !__CRT_HAVE___memcpy_chk */
#endif /* !____libc_core___memcpy_chk_defined */
#ifndef ____libc_core___memmove_chk_defined
#define ____libc_core___memmove_chk_defined
#ifdef __CRT_HAVE___memmove_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___memmove_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize),__memmove_chk,(__dst,__src,__n_bytes,__dst_objsize))
#else /* __CRT_HAVE___memmove_chk */
#include <libc/local/ssp.string/__memmove_chk.h>
#define __libc_core___memmove_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmove_chk)
#endif /* !__CRT_HAVE___memmove_chk */
#endif /* !____libc_core___memmove_chk_defined */
#ifndef ____libc_core___memset_chk_defined
#define ____libc_core___memset_chk_defined
#ifdef __CRT_HAVE___memset_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__libc_core___memset_chk,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize),__memset_chk,(__dst,__byte,__n_bytes,__dst_objsize))
#else /* __CRT_HAVE___memset_chk */
#include <libc/local/ssp.string/__memset_chk.h>
#define __libc_core___memset_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memset_chk)
#endif /* !__CRT_HAVE___memset_chk */
#endif /* !____libc_core___memset_chk_defined */
#ifndef ____libc_core___strcat_chk_defined
#define ____libc_core___strcat_chk_defined
#ifdef __CRT_HAVE___strcat_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__libc_core___strcat_chk,(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __dst_objsize),__strcat_chk,(__dst,__src,__dst_objsize))
#else /* __CRT_HAVE___strcat_chk */
#include <libc/local/ssp.string/__strcat_chk.h>
#define __libc_core___strcat_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__strcat_chk)
#endif /* !__CRT_HAVE___strcat_chk */
#endif /* !____libc_core___strcat_chk_defined */
#ifndef ____libc_core___strcpy_chk_defined
#define ____libc_core___strcpy_chk_defined
#ifdef __CRT_HAVE___strcpy_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__libc_core___strcpy_chk,(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __dst_objsize),__strcpy_chk,(__dst,__src,__dst_objsize))
#else /* __CRT_HAVE___strcpy_chk */
#include <libc/local/ssp.string/__strcpy_chk.h>
#define __libc_core___strcpy_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__strcpy_chk)
#endif /* !__CRT_HAVE___strcpy_chk */
#endif /* !____libc_core___strcpy_chk_defined */
#ifndef ____libc_core___strncat_chk_defined
#define ____libc_core___strncat_chk_defined
#ifdef __CRT_HAVE___strncat_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__libc_core___strncat_chk,(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __buflen, __SIZE_TYPE__ __dst_objsize),__strncat_chk,(__dst,__src,__buflen,__dst_objsize))
#else /* __CRT_HAVE___strncat_chk */
#include <libc/local/ssp.string/__strncat_chk.h>
#define __libc_core___strncat_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__strncat_chk)
#endif /* !__CRT_HAVE___strncat_chk */
#endif /* !____libc_core___strncat_chk_defined */
#ifndef ____libc_core___strncpy_chk_defined
#define ____libc_core___strncpy_chk_defined
#ifdef __CRT_HAVE___strncpy_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__libc_core___strncpy_chk,(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __buflen, __SIZE_TYPE__ __dst_objsize),__strncpy_chk,(__dst,__src,__buflen,__dst_objsize))
#else /* __CRT_HAVE___strncpy_chk */
#include <libc/local/ssp.string/__strncpy_chk.h>
#define __libc_core___strncpy_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__strncpy_chk)
#endif /* !__CRT_HAVE___strncpy_chk */
#endif /* !____libc_core___strncpy_chk_defined */
#ifndef ____libc_core___mempcpy_chk_defined
#define ____libc_core___mempcpy_chk_defined
#ifdef __CRT_HAVE___mempcpy_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___mempcpy_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize),__mempcpy_chk,(__dst,__src,__n_bytes,__dst_objsize))
#else /* __CRT_HAVE___mempcpy_chk */
#include <libc/local/ssp.string/__mempcpy_chk.h>
#define __libc_core___mempcpy_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempcpy_chk)
#endif /* !__CRT_HAVE___mempcpy_chk */
#endif /* !____libc_core___mempcpy_chk_defined */
#ifndef ____libc_core___stpcpy_chk_defined
#define ____libc_core___stpcpy_chk_defined
#ifdef __CRT_HAVE___stpcpy_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__libc_core___stpcpy_chk,(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __dst_objsize),__stpcpy_chk,(__dst,__src,__dst_objsize))
#else /* __CRT_HAVE___stpcpy_chk */
#include <libc/local/ssp.string/__stpcpy_chk.h>
#define __libc_core___stpcpy_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__stpcpy_chk)
#endif /* !__CRT_HAVE___stpcpy_chk */
#endif /* !____libc_core___stpcpy_chk_defined */
#ifndef ____libc_core___stpncpy_chk_defined
#define ____libc_core___stpncpy_chk_defined
#ifdef __CRT_HAVE___stpncpy_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__libc_core___stpncpy_chk,(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __buflen, __SIZE_TYPE__ __dst_objsize),__stpncpy_chk,(__dst,__src,__buflen,__dst_objsize))
#else /* __CRT_HAVE___stpncpy_chk */
#include <libc/local/ssp.string/__stpncpy_chk.h>
#define __libc_core___stpncpy_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__stpncpy_chk)
#endif /* !__CRT_HAVE___stpncpy_chk */
#endif /* !____libc_core___stpncpy_chk_defined */
#ifndef ____libc_core___mempmove_chk_defined
#define ____libc_core___mempmove_chk_defined
#ifdef __CRT_HAVE___mempmove_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___mempmove_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize),__mempmove_chk,(__dst,__src,__n_bytes,__dst_objsize))
#else /* __CRT_HAVE___mempmove_chk */
#include <libc/local/ssp.string/__mempmove_chk.h>
#define __libc_core___mempmove_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmove_chk)
#endif /* !__CRT_HAVE___mempmove_chk */
#endif /* !____libc_core___mempmove_chk_defined */
#ifndef ____libc_core___mempset_chk_defined
#define ____libc_core___mempset_chk_defined
#ifdef __CRT_HAVE___mempset_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__libc_core___mempset_chk,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize),__mempset_chk,(__dst,__byte,__n_bytes,__dst_objsize))
#else /* __CRT_HAVE___mempset_chk */
#include <libc/local/ssp.string/__mempset_chk.h>
#define __libc_core___mempset_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempset_chk)
#endif /* !__CRT_HAVE___mempset_chk */
#endif /* !____libc_core___mempset_chk_defined */
#ifndef ____libc_core___memmoveup_chk_defined
#define ____libc_core___memmoveup_chk_defined
#ifdef __CRT_HAVE___memmoveup_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___memmoveup_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize),__memmoveup_chk,(__dst,__src,__n_bytes,__dst_objsize))
#else /* __CRT_HAVE___memmoveup_chk */
#include <libc/local/ssp.string/__memmoveup_chk.h>
#define __libc_core___memmoveup_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmoveup_chk)
#endif /* !__CRT_HAVE___memmoveup_chk */
#endif /* !____libc_core___memmoveup_chk_defined */
#ifndef ____libc_core___memmovedown_chk_defined
#define ____libc_core___memmovedown_chk_defined
#ifdef __CRT_HAVE___memmovedown_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___memmovedown_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize),__memmovedown_chk,(__dst,__src,__n_bytes,__dst_objsize))
#else /* __CRT_HAVE___memmovedown_chk */
#include <libc/local/ssp.string/__memmovedown_chk.h>
#define __libc_core___memmovedown_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmovedown_chk)
#endif /* !__CRT_HAVE___memmovedown_chk */
#endif /* !____libc_core___memmovedown_chk_defined */
#ifndef ____libc_core___mempmoveup_chk_defined
#define ____libc_core___mempmoveup_chk_defined
#ifdef __CRT_HAVE___mempmoveup_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___mempmoveup_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize),__mempmoveup_chk,(__dst,__src,__n_bytes,__dst_objsize))
#else /* __CRT_HAVE___mempmoveup_chk */
#include <libc/local/ssp.string/__mempmoveup_chk.h>
#define __libc_core___mempmoveup_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmoveup_chk)
#endif /* !__CRT_HAVE___mempmoveup_chk */
#endif /* !____libc_core___mempmoveup_chk_defined */
#ifndef ____libc_core___mempmovedown_chk_defined
#define ____libc_core___mempmovedown_chk_defined
#ifdef __CRT_HAVE___mempmovedown_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___mempmovedown_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize),__mempmovedown_chk,(__dst,__src,__n_bytes,__dst_objsize))
#else /* __CRT_HAVE___mempmovedown_chk */
#include <libc/local/ssp.string/__mempmovedown_chk.h>
#define __libc_core___mempmovedown_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmovedown_chk)
#endif /* !__CRT_HAVE___mempmovedown_chk */
#endif /* !____libc_core___mempmovedown_chk_defined */
#ifndef ____libc_core___memcpyc_chk_defined
#define ____libc_core___memcpyc_chk_defined
#ifdef __CRT_HAVE___memcpyc_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___memcpyc_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize),__memcpyc_chk,(__dst,__src,__elem_count,__elem_size,__dst_objsize))
#else /* __CRT_HAVE___memcpyc_chk */
#include <libc/local/ssp.string/__memcpyc_chk.h>
#define __libc_core___memcpyc_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memcpyc_chk)
#endif /* !__CRT_HAVE___memcpyc_chk */
#endif /* !____libc_core___memcpyc_chk_defined */
#ifndef ____libc_core___memmovec_chk_defined
#define ____libc_core___memmovec_chk_defined
#ifdef __CRT_HAVE___memmovec_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___memmovec_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize),__memmovec_chk,(__dst,__src,__elem_count,__elem_size,__dst_objsize))
#else /* __CRT_HAVE___memmovec_chk */
#include <libc/local/ssp.string/__memmovec_chk.h>
#define __libc_core___memmovec_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmovec_chk)
#endif /* !__CRT_HAVE___memmovec_chk */
#endif /* !____libc_core___memmovec_chk_defined */
#ifndef ____libc_core___mempcpyc_chk_defined
#define ____libc_core___mempcpyc_chk_defined
#ifdef __CRT_HAVE___mempcpyc_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___mempcpyc_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize),__mempcpyc_chk,(__dst,__src,__elem_count,__elem_size,__dst_objsize))
#else /* __CRT_HAVE___mempcpyc_chk */
#include <libc/local/ssp.string/__mempcpyc_chk.h>
#define __libc_core___mempcpyc_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempcpyc_chk)
#endif /* !__CRT_HAVE___mempcpyc_chk */
#endif /* !____libc_core___mempcpyc_chk_defined */
#ifndef ____libc_core___mempmovec_chk_defined
#define ____libc_core___mempmovec_chk_defined
#ifdef __CRT_HAVE___mempmovec_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___mempmovec_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize),__mempmovec_chk,(__dst,__src,__elem_count,__elem_size,__dst_objsize))
#else /* __CRT_HAVE___mempmovec_chk */
#include <libc/local/ssp.string/__mempmovec_chk.h>
#define __libc_core___mempmovec_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmovec_chk)
#endif /* !__CRT_HAVE___mempmovec_chk */
#endif /* !____libc_core___mempmovec_chk_defined */
#ifndef ____libc_core___memmoveupc_chk_defined
#define ____libc_core___memmoveupc_chk_defined
#ifdef __CRT_HAVE___memmoveupc_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___memmoveupc_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize),__memmoveupc_chk,(__dst,__src,__elem_count,__elem_size,__dst_objsize))
#else /* __CRT_HAVE___memmoveupc_chk */
#include <libc/local/ssp.string/__memmoveupc_chk.h>
#define __libc_core___memmoveupc_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmoveupc_chk)
#endif /* !__CRT_HAVE___memmoveupc_chk */
#endif /* !____libc_core___memmoveupc_chk_defined */
#ifndef ____libc_core___memmovedownc_chk_defined
#define ____libc_core___memmovedownc_chk_defined
#ifdef __CRT_HAVE___memmovedownc_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___memmovedownc_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize),__memmovedownc_chk,(__dst,__src,__elem_count,__elem_size,__dst_objsize))
#else /* __CRT_HAVE___memmovedownc_chk */
#include <libc/local/ssp.string/__memmovedownc_chk.h>
#define __libc_core___memmovedownc_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmovedownc_chk)
#endif /* !__CRT_HAVE___memmovedownc_chk */
#endif /* !____libc_core___memmovedownc_chk_defined */
#ifndef ____libc_core___mempmoveupc_chk_defined
#define ____libc_core___mempmoveupc_chk_defined
#ifdef __CRT_HAVE___mempmoveupc_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___mempmoveupc_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize),__mempmoveupc_chk,(__dst,__src,__elem_count,__elem_size,__dst_objsize))
#else /* __CRT_HAVE___mempmoveupc_chk */
#include <libc/local/ssp.string/__mempmoveupc_chk.h>
#define __libc_core___mempmoveupc_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmoveupc_chk)
#endif /* !__CRT_HAVE___mempmoveupc_chk */
#endif /* !____libc_core___mempmoveupc_chk_defined */
#ifndef ____libc_core___mempmovedownc_chk_defined
#define ____libc_core___mempmovedownc_chk_defined
#ifdef __CRT_HAVE___mempmovedownc_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core___mempmovedownc_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize),__mempmovedownc_chk,(__dst,__src,__elem_count,__elem_size,__dst_objsize))
#else /* __CRT_HAVE___mempmovedownc_chk */
#include <libc/local/ssp.string/__mempmovedownc_chk.h>
#define __libc_core___mempmovedownc_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmovedownc_chk)
#endif /* !__CRT_HAVE___mempmovedownc_chk */
#endif /* !____libc_core___mempmovedownc_chk_defined */
#ifndef ____libc_core___memcpyw_chk_defined
#define ____libc_core___memcpyw_chk_defined
#ifdef __CRT_HAVE___memcpyw_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___memcpyw_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__memcpyw_chk,(__dst,__src,__n_words,__dst_objsize))
#elif defined(__CRT_HAVE___wmemcpy_chk) && __SIZEOF_WCHAR_T__ == 2
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___memcpyw_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__wmemcpy_chk,(__dst,__src,__n_words,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__memcpyw_chk.h>
#define __libc_core___memcpyw_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memcpyw_chk)
#endif /* !... */
#endif /* !____libc_core___memcpyw_chk_defined */
#ifndef ____libc_core___mempcpyw_chk_defined
#define ____libc_core___mempcpyw_chk_defined
#ifdef __CRT_HAVE___mempcpyw_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___mempcpyw_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__mempcpyw_chk,(__dst,__src,__n_words,__dst_objsize))
#elif defined(__CRT_HAVE___wmempcpy_chk) && __SIZEOF_WCHAR_T__ == 2
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___mempcpyw_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__wmempcpy_chk,(__dst,__src,__n_words,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__mempcpyw_chk.h>
#define __libc_core___mempcpyw_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempcpyw_chk)
#endif /* !... */
#endif /* !____libc_core___mempcpyw_chk_defined */
#ifndef ____libc_core___memmovew_chk_defined
#define ____libc_core___memmovew_chk_defined
#ifdef __CRT_HAVE___memmovew_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___memmovew_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__memmovew_chk,(__dst,__src,__n_words,__dst_objsize))
#elif defined(__CRT_HAVE___wmemmove_chk) && __SIZEOF_WCHAR_T__ == 2
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___memmovew_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__wmemmove_chk,(__dst,__src,__n_words,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__memmovew_chk.h>
#define __libc_core___memmovew_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmovew_chk)
#endif /* !... */
#endif /* !____libc_core___memmovew_chk_defined */
#ifndef ____libc_core___memcpyl_chk_defined
#define ____libc_core___memcpyl_chk_defined
#ifdef __CRT_HAVE___memcpyl_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___memcpyl_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__memcpyl_chk,(__dst,__src,__n_dwords,__dst_objsize))
#elif defined(__CRT_HAVE___wmemcpy_chk) && __SIZEOF_WCHAR_T__ == 4
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___memcpyl_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__wmemcpy_chk,(__dst,__src,__n_dwords,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__memcpyl_chk.h>
#define __libc_core___memcpyl_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memcpyl_chk)
#endif /* !... */
#endif /* !____libc_core___memcpyl_chk_defined */
#ifndef ____libc_core___mempcpyl_chk_defined
#define ____libc_core___mempcpyl_chk_defined
#ifdef __CRT_HAVE___mempcpyl_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___mempcpyl_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__mempcpyl_chk,(__dst,__src,__n_dwords,__dst_objsize))
#elif defined(__CRT_HAVE___wmempcpy_chk) && __SIZEOF_WCHAR_T__ == 4
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___mempcpyl_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__wmempcpy_chk,(__dst,__src,__n_dwords,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__mempcpyl_chk.h>
#define __libc_core___mempcpyl_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempcpyl_chk)
#endif /* !... */
#endif /* !____libc_core___mempcpyl_chk_defined */
#ifndef ____libc_core___memmovel_chk_defined
#define ____libc_core___memmovel_chk_defined
#ifdef __CRT_HAVE___memmovel_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___memmovel_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__memmovel_chk,(__dst,__src,__n_dwords,__dst_objsize))
#elif defined(__CRT_HAVE___wmemmove_chk) && __SIZEOF_WCHAR_T__ == 4
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___memmovel_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__wmemmove_chk,(__dst,__src,__n_dwords,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__memmovel_chk.h>
#define __libc_core___memmovel_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmovel_chk)
#endif /* !... */
#endif /* !____libc_core___memmovel_chk_defined */
#ifndef ____libc_core___mempmovew_chk_defined
#define ____libc_core___mempmovew_chk_defined
#ifdef __CRT_HAVE___mempmovew_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___mempmovew_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__mempmovew_chk,(__dst,__src,__n_words,__dst_objsize))
#else /* __CRT_HAVE___mempmovew_chk */
#include <libc/local/ssp.string/__mempmovew_chk.h>
#define __libc_core___mempmovew_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmovew_chk)
#endif /* !__CRT_HAVE___mempmovew_chk */
#endif /* !____libc_core___mempmovew_chk_defined */
#ifndef ____libc_core___mempmovel_chk_defined
#define ____libc_core___mempmovel_chk_defined
#ifdef __CRT_HAVE___mempmovel_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___mempmovel_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__mempmovel_chk,(__dst,__src,__n_dwords,__dst_objsize))
#else /* __CRT_HAVE___mempmovel_chk */
#include <libc/local/ssp.string/__mempmovel_chk.h>
#define __libc_core___mempmovel_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmovel_chk)
#endif /* !__CRT_HAVE___mempmovel_chk */
#endif /* !____libc_core___mempmovel_chk_defined */
#ifndef ____libc_core___memsetw_chk_defined
#define ____libc_core___memsetw_chk_defined
#ifdef __CRT_HAVE___memsetw_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___memsetw_chk,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__memsetw_chk,(__dst,__word,__n_words,__dst_objsize))
#else /* __CRT_HAVE___memsetw_chk */
#include <libc/local/ssp.string/__memsetw_chk.h>
#define __libc_core___memsetw_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memsetw_chk)
#endif /* !__CRT_HAVE___memsetw_chk */
#endif /* !____libc_core___memsetw_chk_defined */
#ifndef ____libc_core___mempsetw_chk_defined
#define ____libc_core___mempsetw_chk_defined
#ifdef __CRT_HAVE___mempsetw_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___mempsetw_chk,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__mempsetw_chk,(__dst,__word,__n_words,__dst_objsize))
#else /* __CRT_HAVE___mempsetw_chk */
#include <libc/local/ssp.string/__mempsetw_chk.h>
#define __libc_core___mempsetw_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempsetw_chk)
#endif /* !__CRT_HAVE___mempsetw_chk */
#endif /* !____libc_core___mempsetw_chk_defined */
#ifndef ____libc_core___memsetl_chk_defined
#define ____libc_core___memsetl_chk_defined
#ifdef __CRT_HAVE___memsetl_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___memsetl_chk,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__memsetl_chk,(__dst,__dword,__n_dwords,__dst_objsize))
#else /* __CRT_HAVE___memsetl_chk */
#include <libc/local/ssp.string/__memsetl_chk.h>
#define __libc_core___memsetl_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memsetl_chk)
#endif /* !__CRT_HAVE___memsetl_chk */
#endif /* !____libc_core___memsetl_chk_defined */
#ifndef ____libc_core___mempsetl_chk_defined
#define ____libc_core___mempsetl_chk_defined
#ifdef __CRT_HAVE___mempsetl_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___mempsetl_chk,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__mempsetl_chk,(__dst,__dword,__n_dwords,__dst_objsize))
#else /* __CRT_HAVE___mempsetl_chk */
#include <libc/local/ssp.string/__mempsetl_chk.h>
#define __libc_core___mempsetl_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempsetl_chk)
#endif /* !__CRT_HAVE___mempsetl_chk */
#endif /* !____libc_core___mempsetl_chk_defined */
#ifndef ____libc_core___memmoveupw_chk_defined
#define ____libc_core___memmoveupw_chk_defined
#ifdef __CRT_HAVE___memmoveupw_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___memmoveupw_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__memmoveupw_chk,(__dst,__src,__n_words,__dst_objsize))
#elif defined(__CRT_HAVE___memmovew_chk)
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___memmoveupw_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__memmovew_chk,(__dst,__src,__n_words,__dst_objsize))
#elif defined(__CRT_HAVE___wmemmove_chk) && __SIZEOF_WCHAR_T__ == 2
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___memmoveupw_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__wmemmove_chk,(__dst,__src,__n_words,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__memmoveupw_chk.h>
#define __libc_core___memmoveupw_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmoveupw_chk)
#endif /* !... */
#endif /* !____libc_core___memmoveupw_chk_defined */
#ifndef ____libc_core___memmovedownw_chk_defined
#define ____libc_core___memmovedownw_chk_defined
#ifdef __CRT_HAVE___memmovedownw_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___memmovedownw_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__memmovedownw_chk,(__dst,__src,__n_words,__dst_objsize))
#elif defined(__CRT_HAVE___memmovew_chk)
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___memmovedownw_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__memmovew_chk,(__dst,__src,__n_words,__dst_objsize))
#elif defined(__CRT_HAVE___wmemmove_chk) && __SIZEOF_WCHAR_T__ == 2
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___memmovedownw_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__wmemmove_chk,(__dst,__src,__n_words,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__memmovedownw_chk.h>
#define __libc_core___memmovedownw_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmovedownw_chk)
#endif /* !... */
#endif /* !____libc_core___memmovedownw_chk_defined */
#ifndef ____libc_core___memmoveupl_chk_defined
#define ____libc_core___memmoveupl_chk_defined
#ifdef __CRT_HAVE___memmoveupl_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___memmoveupl_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__memmoveupl_chk,(__dst,__src,__n_dwords,__dst_objsize))
#elif defined(__CRT_HAVE___memmovel_chk)
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___memmoveupl_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__memmovel_chk,(__dst,__src,__n_dwords,__dst_objsize))
#elif defined(__CRT_HAVE___wmemmove_chk) && __SIZEOF_WCHAR_T__ == 4
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___memmoveupl_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__wmemmove_chk,(__dst,__src,__n_dwords,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__memmoveupl_chk.h>
#define __libc_core___memmoveupl_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmoveupl_chk)
#endif /* !... */
#endif /* !____libc_core___memmoveupl_chk_defined */
#ifndef ____libc_core___memmovedownl_chk_defined
#define ____libc_core___memmovedownl_chk_defined
#ifdef __CRT_HAVE___memmovedownl_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___memmovedownl_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__memmovedownl_chk,(__dst,__src,__n_dwords,__dst_objsize))
#elif defined(__CRT_HAVE___memmovel_chk)
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___memmovedownl_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__memmovel_chk,(__dst,__src,__n_dwords,__dst_objsize))
#elif defined(__CRT_HAVE___wmemmove_chk) && __SIZEOF_WCHAR_T__ == 4
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___memmovedownl_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__wmemmove_chk,(__dst,__src,__n_dwords,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__memmovedownl_chk.h>
#define __libc_core___memmovedownl_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmovedownl_chk)
#endif /* !... */
#endif /* !____libc_core___memmovedownl_chk_defined */
#ifndef ____libc_core___mempmoveupw_chk_defined
#define ____libc_core___mempmoveupw_chk_defined
#ifdef __CRT_HAVE___mempmoveupw_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___mempmoveupw_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__mempmoveupw_chk,(__dst,__src,__n_words,__dst_objsize))
#elif defined(__CRT_HAVE___mempmovew_chk)
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___mempmoveupw_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__mempmovew_chk,(__dst,__src,__n_words,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__mempmoveupw_chk.h>
#define __libc_core___mempmoveupw_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmoveupw_chk)
#endif /* !... */
#endif /* !____libc_core___mempmoveupw_chk_defined */
#ifndef ____libc_core___mempmovedownw_chk_defined
#define ____libc_core___mempmovedownw_chk_defined
#ifdef __CRT_HAVE___mempmovedownw_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___mempmovedownw_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__mempmovedownw_chk,(__dst,__src,__n_words,__dst_objsize))
#elif defined(__CRT_HAVE___mempmovew_chk)
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core___mempmovedownw_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__mempmovew_chk,(__dst,__src,__n_words,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__mempmovedownw_chk.h>
#define __libc_core___mempmovedownw_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmovedownw_chk)
#endif /* !... */
#endif /* !____libc_core___mempmovedownw_chk_defined */
#ifndef ____libc_core___mempmoveupl_chk_defined
#define ____libc_core___mempmoveupl_chk_defined
#ifdef __CRT_HAVE___mempmoveupl_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___mempmoveupl_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__mempmoveupl_chk,(__dst,__src,__n_dwords,__dst_objsize))
#elif defined(__CRT_HAVE___mempmovel_chk)
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___mempmoveupl_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__mempmovel_chk,(__dst,__src,__n_dwords,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__mempmoveupl_chk.h>
#define __libc_core___mempmoveupl_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmoveupl_chk)
#endif /* !... */
#endif /* !____libc_core___mempmoveupl_chk_defined */
#ifndef ____libc_core___mempmovedownl_chk_defined
#define ____libc_core___mempmovedownl_chk_defined
#ifdef __CRT_HAVE___mempmovedownl_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___mempmovedownl_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__mempmovedownl_chk,(__dst,__src,__n_dwords,__dst_objsize))
#elif defined(__CRT_HAVE___mempmovel_chk)
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core___mempmovedownl_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__mempmovel_chk,(__dst,__src,__n_dwords,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__mempmovedownl_chk.h>
#define __libc_core___mempmovedownl_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmovedownl_chk)
#endif /* !... */
#endif /* !____libc_core___mempmovedownl_chk_defined */
#ifndef ____libc_core___memcpyq_chk_defined
#define ____libc_core___memcpyq_chk_defined
#ifdef __CRT_HAVE___memcpyq_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core___memcpyq_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__memcpyq_chk,(__dst,__src,__n_qwords,__dst_objsize))
#else /* __CRT_HAVE___memcpyq_chk */
#include <libc/local/ssp.string/__memcpyq_chk.h>
#define __libc_core___memcpyq_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memcpyq_chk)
#endif /* !__CRT_HAVE___memcpyq_chk */
#endif /* !____libc_core___memcpyq_chk_defined */
#ifndef ____libc_core___mempcpyq_chk_defined
#define ____libc_core___mempcpyq_chk_defined
#ifdef __CRT_HAVE___mempcpyq_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core___mempcpyq_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__mempcpyq_chk,(__dst,__src,__n_qwords,__dst_objsize))
#else /* __CRT_HAVE___mempcpyq_chk */
#include <libc/local/ssp.string/__mempcpyq_chk.h>
#define __libc_core___mempcpyq_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempcpyq_chk)
#endif /* !__CRT_HAVE___mempcpyq_chk */
#endif /* !____libc_core___mempcpyq_chk_defined */
#ifndef ____libc_core___memmoveq_chk_defined
#define ____libc_core___memmoveq_chk_defined
#ifdef __CRT_HAVE___memmoveq_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core___memmoveq_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__memmoveq_chk,(__dst,__src,__n_qwords,__dst_objsize))
#else /* __CRT_HAVE___memmoveq_chk */
#include <libc/local/ssp.string/__memmoveq_chk.h>
#define __libc_core___memmoveq_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmoveq_chk)
#endif /* !__CRT_HAVE___memmoveq_chk */
#endif /* !____libc_core___memmoveq_chk_defined */
#ifndef ____libc_core___mempmoveq_chk_defined
#define ____libc_core___mempmoveq_chk_defined
#ifdef __CRT_HAVE___mempmoveq_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core___mempmoveq_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__mempmoveq_chk,(__dst,__src,__n_qwords,__dst_objsize))
#else /* __CRT_HAVE___mempmoveq_chk */
#include <libc/local/ssp.string/__mempmoveq_chk.h>
#define __libc_core___mempmoveq_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmoveq_chk)
#endif /* !__CRT_HAVE___mempmoveq_chk */
#endif /* !____libc_core___mempmoveq_chk_defined */
#ifndef ____libc_core___memsetq_chk_defined
#define ____libc_core___memsetq_chk_defined
#ifdef __CRT_HAVE___memsetq_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core___memsetq_chk,(void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__memsetq_chk,(__dst,__qword,__n_qwords,__dst_objsize))
#else /* __CRT_HAVE___memsetq_chk */
#include <libc/local/ssp.string/__memsetq_chk.h>
#define __libc_core___memsetq_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memsetq_chk)
#endif /* !__CRT_HAVE___memsetq_chk */
#endif /* !____libc_core___memsetq_chk_defined */
#ifndef ____libc_core___mempsetq_chk_defined
#define ____libc_core___mempsetq_chk_defined
#ifdef __CRT_HAVE___mempsetq_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core___mempsetq_chk,(void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__mempsetq_chk,(__dst,__qword,__n_qwords,__dst_objsize))
#else /* __CRT_HAVE___mempsetq_chk */
#include <libc/local/ssp.string/__mempsetq_chk.h>
#define __libc_core___mempsetq_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempsetq_chk)
#endif /* !__CRT_HAVE___mempsetq_chk */
#endif /* !____libc_core___mempsetq_chk_defined */
#ifndef ____libc_core___memmoveupq_chk_defined
#define ____libc_core___memmoveupq_chk_defined
#ifdef __CRT_HAVE___memmoveupq_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core___memmoveupq_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__memmoveupq_chk,(__dst,__src,__n_qwords,__dst_objsize))
#elif defined(__CRT_HAVE___memmoveq_chk)
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core___memmoveupq_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__memmoveq_chk,(__dst,__src,__n_qwords,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__memmoveupq_chk.h>
#define __libc_core___memmoveupq_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmoveupq_chk)
#endif /* !... */
#endif /* !____libc_core___memmoveupq_chk_defined */
#ifndef ____libc_core___memmovedownq_chk_defined
#define ____libc_core___memmovedownq_chk_defined
#ifdef __CRT_HAVE___memmovedownq_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core___memmovedownq_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__memmovedownq_chk,(__dst,__src,__n_qwords,__dst_objsize))
#elif defined(__CRT_HAVE___memmoveq_chk)
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core___memmovedownq_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__memmoveq_chk,(__dst,__src,__n_qwords,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__memmovedownq_chk.h>
#define __libc_core___memmovedownq_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmovedownq_chk)
#endif /* !... */
#endif /* !____libc_core___memmovedownq_chk_defined */
#ifndef ____libc_core___mempmoveupq_chk_defined
#define ____libc_core___mempmoveupq_chk_defined
#ifdef __CRT_HAVE___mempmoveupq_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core___mempmoveupq_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__mempmoveupq_chk,(__dst,__src,__n_qwords,__dst_objsize))
#elif defined(__CRT_HAVE___mempmoveq_chk)
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core___mempmoveupq_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__mempmoveq_chk,(__dst,__src,__n_qwords,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__mempmoveupq_chk.h>
#define __libc_core___mempmoveupq_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmoveupq_chk)
#endif /* !... */
#endif /* !____libc_core___mempmoveupq_chk_defined */
#ifndef ____libc_core___mempmovedownq_chk_defined
#define ____libc_core___mempmovedownq_chk_defined
#ifdef __CRT_HAVE___mempmovedownq_chk
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core___mempmovedownq_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__mempmovedownq_chk,(__dst,__src,__n_qwords,__dst_objsize))
#elif defined(__CRT_HAVE___mempmoveq_chk)
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core___mempmovedownq_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__mempmoveq_chk,(__dst,__src,__n_qwords,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__mempmovedownq_chk.h>
#define __libc_core___mempmovedownq_chk __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmovedownq_chk)
#endif /* !... */
#endif /* !____libc_core___mempmovedownq_chk_defined */

__SYSDECL_END

#endif /* __CC__ */

#endif /* !_LIBC_CORE_SSP_STRING_H */
