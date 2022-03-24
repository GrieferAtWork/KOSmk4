/* HASH CRC-32:0xd8efc10c */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Cygwin (/newlib/libc/include/ssp/string.h) */
/* (#) Portability: NetBSD (/include/ssp/string.h) */
/* (#) Portability: Newlib (/newlib/libc/include/ssp/string.h) */
#ifndef _SSP_STRING_H
#define _SSP_STRING_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <hybrid/typecore.h>

#include <ssp/ssp.h>
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/ssp.string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */

__SYSDECL_BEGIN

#ifdef __CC__

#ifdef __fast___memcpy_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__memcpy_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __memcpy_chk)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memcpy_chk))(__dst, __src, __n_bytes, __dst_objsize); })
#elif defined(__CRT_HAVE___memcpy_chk)
__CDECLARE_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__memcpy_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_bytes,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__memcpy_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__memcpy_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __memcpy_chk)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memcpy_chk))(__dst, __src, __n_bytes, __dst_objsize); })
#endif /* !... */
#ifdef __fast___memmove_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__memmove_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __memmove_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmove_chk))(__dst, __src, __n_bytes, __dst_objsize); })
#elif defined(__CRT_HAVE___memmove_chk)
__CDECLARE_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__memmove_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_bytes,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__memmove_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__memmove_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __memmove_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmove_chk))(__dst, __src, __n_bytes, __dst_objsize); })
#endif /* !... */
#ifdef __fast___memset_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__memset_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL __memset_chk)(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memset_chk))(__dst, __byte, __n_bytes, __dst_objsize); })
#elif defined(__CRT_HAVE___memset_chk)
__CDECLARE_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__memset_chk,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize),(__dst,__byte,__n_bytes,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__memset_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__memset_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL __memset_chk)(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memset_chk))(__dst, __byte, __n_bytes, __dst_objsize); })
#endif /* !... */
#ifdef __fast___strcat_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__strcat_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL __strcat_chk)(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__strcat_chk))(__dst, __src, __dst_objsize); })
#elif defined(__CRT_HAVE___strcat_chk)
__CDECLARE_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__strcat_chk,(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__strcat_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__strcat_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL __strcat_chk)(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__strcat_chk))(__dst, __src, __dst_objsize); })
#endif /* !... */
#ifdef __fast___strcpy_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__strcpy_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL __strcpy_chk)(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__strcpy_chk))(__dst, __src, __dst_objsize); })
#elif defined(__CRT_HAVE___strcpy_chk)
__CDECLARE_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__strcpy_chk,(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__strcpy_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__strcpy_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL __strcpy_chk)(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__strcpy_chk))(__dst, __src, __dst_objsize); })
#endif /* !... */
#ifdef __fast___strncat_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__strncat_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL __strncat_chk)(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __buflen, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__strncat_chk))(__dst, __src, __buflen, __dst_objsize); })
#elif defined(__CRT_HAVE___strncat_chk)
__CDECLARE_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__strncat_chk,(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __buflen, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__buflen,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__strncat_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__strncat_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL __strncat_chk)(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __buflen, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__strncat_chk))(__dst, __src, __buflen, __dst_objsize); })
#endif /* !... */
#ifdef __fast___strncpy_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__strncpy_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL __strncpy_chk)(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __buflen, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__strncpy_chk))(__dst, __src, __buflen, __dst_objsize); })
#elif defined(__CRT_HAVE___strncpy_chk)
__CDECLARE_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__strncpy_chk,(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __buflen, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__buflen,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__strncpy_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__strncpy_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL __strncpy_chk)(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __buflen, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__strncpy_chk))(__dst, __src, __buflen, __dst_objsize); })
#endif /* !... */

#ifdef __USE_GNU
#ifdef __fast___mempcpy_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__mempcpy_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __mempcpy_chk)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempcpy_chk))(__dst, __src, __n_bytes, __dst_objsize); })
#elif defined(__CRT_HAVE___mempcpy_chk)
__CDECLARE_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__mempcpy_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_bytes,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__mempcpy_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__mempcpy_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __mempcpy_chk)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempcpy_chk))(__dst, __src, __n_bytes, __dst_objsize); })
#endif /* !... */
#endif /* __USE_GNU */

#ifdef __USE_XOPEN2K8
#ifdef __fast___stpcpy_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__stpcpy_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL __stpcpy_chk)(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__stpcpy_chk))(__dst, __src, __dst_objsize); })
#elif defined(__CRT_HAVE___stpcpy_chk)
__CDECLARE_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__stpcpy_chk,(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__stpcpy_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__stpcpy_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL __stpcpy_chk)(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__stpcpy_chk))(__dst, __src, __dst_objsize); })
#endif /* !... */
#ifdef __fast___stpncpy_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__stpncpy_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL __stpncpy_chk)(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __buflen, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__stpncpy_chk))(__dst, __src, __buflen, __dst_objsize); })
#elif defined(__CRT_HAVE___stpncpy_chk)
__CDECLARE_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__stpncpy_chk,(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __buflen, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__buflen,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__stpncpy_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__stpncpy_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL __stpncpy_chk)(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __buflen, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__stpncpy_chk))(__dst, __src, __buflen, __dst_objsize); })
#endif /* !... */
#endif /* __USE_XOPEN2K8 */

#ifdef __USE_KOS
#ifdef __fast___mempmove_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__mempmove_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __mempmove_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmove_chk))(__dst, __src, __n_bytes, __dst_objsize); })
#elif defined(__CRT_HAVE___mempmove_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__mempmove_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_bytes,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__mempmove_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__mempmove_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __mempmove_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmove_chk))(__dst, __src, __n_bytes, __dst_objsize); })
#endif /* !... */
#ifdef __fast___mempset_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__mempset_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL __mempset_chk)(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempset_chk))(__dst, __byte, __n_bytes, __dst_objsize); })
#elif defined(__CRT_HAVE___mempset_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__mempset_chk,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize),(__dst,__byte,__n_bytes,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__mempset_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__mempset_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL __mempset_chk)(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempset_chk))(__dst, __byte, __n_bytes, __dst_objsize); })
#endif /* !... */
#ifdef __fast___memmoveup_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__memmoveup_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __memmoveup_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmoveup_chk))(__dst, __src, __n_bytes, __dst_objsize); })
#elif defined(__CRT_HAVE___memmoveup_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__memmoveup_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_bytes,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__memmoveup_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__memmoveup_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __memmoveup_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmoveup_chk))(__dst, __src, __n_bytes, __dst_objsize); })
#endif /* !... */
#ifdef __fast___memmovedown_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__memmovedown_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __memmovedown_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmovedown_chk))(__dst, __src, __n_bytes, __dst_objsize); })
#elif defined(__CRT_HAVE___memmovedown_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__memmovedown_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_bytes,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__memmovedown_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__memmovedown_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __memmovedown_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmovedown_chk))(__dst, __src, __n_bytes, __dst_objsize); })
#endif /* !... */
#ifdef __fast___mempmoveup_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__mempmoveup_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __mempmoveup_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmoveup_chk))(__dst, __src, __n_bytes, __dst_objsize); })
#elif defined(__CRT_HAVE___mempmoveup_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__mempmoveup_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_bytes,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__mempmoveup_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__mempmoveup_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __mempmoveup_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmoveup_chk))(__dst, __src, __n_bytes, __dst_objsize); })
#endif /* !... */
#ifdef __fast___mempmovedown_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__mempmovedown_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __mempmovedown_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmovedown_chk))(__dst, __src, __n_bytes, __dst_objsize); })
#elif defined(__CRT_HAVE___mempmovedown_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__mempmovedown_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_bytes,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__mempmovedown_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__mempmovedown_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __mempmovedown_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmovedown_chk))(__dst, __src, __n_bytes, __dst_objsize); })
#endif /* !... */
#ifdef __fast___memcpyc_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__memcpyc_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __memcpyc_chk)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memcpyc_chk))(__dst, __src, __elem_count, __elem_size, __dst_objsize); })
#elif defined(__CRT_HAVE___memcpyc_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__memcpyc_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__elem_count,__elem_size,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__memcpyc_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__memcpyc_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __memcpyc_chk)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memcpyc_chk))(__dst, __src, __elem_count, __elem_size, __dst_objsize); })
#endif /* !... */
#ifdef __fast___memmovec_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__memmovec_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __memmovec_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmovec_chk))(__dst, __src, __elem_count, __elem_size, __dst_objsize); })
#elif defined(__CRT_HAVE___memmovec_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__memmovec_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__elem_count,__elem_size,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__memmovec_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__memmovec_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __memmovec_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmovec_chk))(__dst, __src, __elem_count, __elem_size, __dst_objsize); })
#endif /* !... */
#ifdef __fast___mempcpyc_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__mempcpyc_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __mempcpyc_chk)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempcpyc_chk))(__dst, __src, __elem_count, __elem_size, __dst_objsize); })
#elif defined(__CRT_HAVE___mempcpyc_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__mempcpyc_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__elem_count,__elem_size,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__mempcpyc_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__mempcpyc_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __mempcpyc_chk)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempcpyc_chk))(__dst, __src, __elem_count, __elem_size, __dst_objsize); })
#endif /* !... */
#ifdef __fast___mempmovec_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__mempmovec_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __mempmovec_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmovec_chk))(__dst, __src, __elem_count, __elem_size, __dst_objsize); })
#elif defined(__CRT_HAVE___mempmovec_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__mempmovec_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__elem_count,__elem_size,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__mempmovec_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__mempmovec_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __mempmovec_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmovec_chk))(__dst, __src, __elem_count, __elem_size, __dst_objsize); })
#endif /* !... */
#ifdef __fast___memmoveupc_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__memmoveupc_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __memmoveupc_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmoveupc_chk))(__dst, __src, __elem_count, __elem_size, __dst_objsize); })
#elif defined(__CRT_HAVE___memmoveupc_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__memmoveupc_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__elem_count,__elem_size,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__memmoveupc_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__memmoveupc_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __memmoveupc_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmoveupc_chk))(__dst, __src, __elem_count, __elem_size, __dst_objsize); })
#endif /* !... */
#ifdef __fast___memmovedownc_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__memmovedownc_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __memmovedownc_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmovedownc_chk))(__dst, __src, __elem_count, __elem_size, __dst_objsize); })
#elif defined(__CRT_HAVE___memmovedownc_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__memmovedownc_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__elem_count,__elem_size,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__memmovedownc_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__memmovedownc_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __memmovedownc_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmovedownc_chk))(__dst, __src, __elem_count, __elem_size, __dst_objsize); })
#endif /* !... */
#ifdef __fast___mempmoveupc_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__mempmoveupc_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __mempmoveupc_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmoveupc_chk))(__dst, __src, __elem_count, __elem_size, __dst_objsize); })
#elif defined(__CRT_HAVE___mempmoveupc_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__mempmoveupc_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__elem_count,__elem_size,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__mempmoveupc_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__mempmoveupc_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __mempmoveupc_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmoveupc_chk))(__dst, __src, __elem_count, __elem_size, __dst_objsize); })
#endif /* !... */
#ifdef __fast___mempmovedownc_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__mempmovedownc_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __mempmovedownc_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmovedownc_chk))(__dst, __src, __elem_count, __elem_size, __dst_objsize); })
#elif defined(__CRT_HAVE___mempmovedownc_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__mempmovedownc_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__elem_count,__elem_size,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__mempmovedownc_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__mempmovedownc_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __mempmovedownc_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmovedownc_chk))(__dst, __src, __elem_count, __elem_size, __dst_objsize); })
#endif /* !... */
#endif /* __USE_KOS */
#ifdef __USE_STRING_BWLQ
#ifdef __fast___memcpyw_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__memcpyw_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL __memcpyw_chk)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memcpyw_chk))(__dst, __src, __n_words, __dst_objsize); })
#elif defined(__CRT_HAVE___memcpyw_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__memcpyw_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_words,__dst_objsize))
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE___wmemcpy_chk) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__memcpyw_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__wmemcpy_chk,(__dst,__src,__n_words,__dst_objsize))
#else /* __CRT_HAVE___wmemcpy_chk && __SIZEOF_WCHAR_T__ == 2 */
#include <libc/local/ssp.string/__memcpyw_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__memcpyw_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL __memcpyw_chk)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memcpyw_chk))(__dst, __src, __n_words, __dst_objsize); })
#endif /* !__CRT_HAVE___wmemcpy_chk || __SIZEOF_WCHAR_T__ != 2 */
#endif /* !... */
#ifdef __fast___mempcpyw_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__mempcpyw_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL __mempcpyw_chk)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempcpyw_chk))(__dst, __src, __n_words, __dst_objsize); })
#elif defined(__CRT_HAVE___mempcpyw_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__mempcpyw_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_words,__dst_objsize))
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE___wmempcpy_chk) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__mempcpyw_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__wmempcpy_chk,(__dst,__src,__n_words,__dst_objsize))
#else /* __CRT_HAVE___wmempcpy_chk && __SIZEOF_WCHAR_T__ == 2 */
#include <libc/local/ssp.string/__mempcpyw_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__mempcpyw_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL __mempcpyw_chk)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempcpyw_chk))(__dst, __src, __n_words, __dst_objsize); })
#endif /* !__CRT_HAVE___wmempcpy_chk || __SIZEOF_WCHAR_T__ != 2 */
#endif /* !... */
#ifdef __fast___memmovew_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__memmovew_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL __memmovew_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmovew_chk))(__dst, __src, __n_words, __dst_objsize); })
#elif defined(__CRT_HAVE___memmovew_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__memmovew_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_words,__dst_objsize))
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE___wmemmove_chk) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__memmovew_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__wmemmove_chk,(__dst,__src,__n_words,__dst_objsize))
#else /* __CRT_HAVE___wmemmove_chk && __SIZEOF_WCHAR_T__ == 2 */
#include <libc/local/ssp.string/__memmovew_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__memmovew_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL __memmovew_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmovew_chk))(__dst, __src, __n_words, __dst_objsize); })
#endif /* !__CRT_HAVE___wmemmove_chk || __SIZEOF_WCHAR_T__ != 2 */
#endif /* !... */
#ifdef __fast___memcpyl_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__memcpyl_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL __memcpyl_chk)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memcpyl_chk))(__dst, __src, __n_dwords, __dst_objsize); })
#elif defined(__CRT_HAVE___memcpyl_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__memcpyl_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_dwords,__dst_objsize))
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE___wmemcpy_chk) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__memcpyl_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__wmemcpy_chk,(__dst,__src,__n_dwords,__dst_objsize))
#else /* __CRT_HAVE___wmemcpy_chk && __SIZEOF_WCHAR_T__ == 4 */
#include <libc/local/ssp.string/__memcpyl_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__memcpyl_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL __memcpyl_chk)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memcpyl_chk))(__dst, __src, __n_dwords, __dst_objsize); })
#endif /* !__CRT_HAVE___wmemcpy_chk || __SIZEOF_WCHAR_T__ != 4 */
#endif /* !... */
#ifdef __fast___mempcpyl_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__mempcpyl_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL __mempcpyl_chk)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempcpyl_chk))(__dst, __src, __n_dwords, __dst_objsize); })
#elif defined(__CRT_HAVE___mempcpyl_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__mempcpyl_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_dwords,__dst_objsize))
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE___wmempcpy_chk) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__mempcpyl_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__wmempcpy_chk,(__dst,__src,__n_dwords,__dst_objsize))
#else /* __CRT_HAVE___wmempcpy_chk && __SIZEOF_WCHAR_T__ == 4 */
#include <libc/local/ssp.string/__mempcpyl_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__mempcpyl_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL __mempcpyl_chk)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempcpyl_chk))(__dst, __src, __n_dwords, __dst_objsize); })
#endif /* !__CRT_HAVE___wmempcpy_chk || __SIZEOF_WCHAR_T__ != 4 */
#endif /* !... */
#ifdef __fast___memmovel_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__memmovel_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL __memmovel_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmovel_chk))(__dst, __src, __n_dwords, __dst_objsize); })
#elif defined(__CRT_HAVE___memmovel_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__memmovel_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_dwords,__dst_objsize))
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE___wmemmove_chk) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__memmovel_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__wmemmove_chk,(__dst,__src,__n_dwords,__dst_objsize))
#else /* __CRT_HAVE___wmemmove_chk && __SIZEOF_WCHAR_T__ == 4 */
#include <libc/local/ssp.string/__memmovel_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__memmovel_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL __memmovel_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmovel_chk))(__dst, __src, __n_dwords, __dst_objsize); })
#endif /* !__CRT_HAVE___wmemmove_chk || __SIZEOF_WCHAR_T__ != 4 */
#endif /* !... */
#ifdef __fast___mempmovew_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__mempmovew_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL __mempmovew_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmovew_chk))(__dst, __src, __n_words, __dst_objsize); })
#elif defined(__CRT_HAVE___mempmovew_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__mempmovew_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_words,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__mempmovew_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__mempmovew_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL __mempmovew_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmovew_chk))(__dst, __src, __n_words, __dst_objsize); })
#endif /* !... */
#ifdef __fast___mempmovel_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__mempmovel_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL __mempmovel_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmovel_chk))(__dst, __src, __n_dwords, __dst_objsize); })
#elif defined(__CRT_HAVE___mempmovel_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__mempmovel_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_dwords,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__mempmovel_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__mempmovel_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL __mempmovel_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmovel_chk))(__dst, __src, __n_dwords, __dst_objsize); })
#endif /* !... */
#ifdef __fast___memsetw_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__memsetw_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL __memsetw_chk)(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memsetw_chk))(__dst, __word, __n_words, __dst_objsize); })
#elif defined(__CRT_HAVE___memsetw_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__memsetw_chk,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),(__dst,__word,__n_words,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__memsetw_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__memsetw_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL __memsetw_chk)(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memsetw_chk))(__dst, __word, __n_words, __dst_objsize); })
#endif /* !... */
#ifdef __fast___mempsetw_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__mempsetw_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL __mempsetw_chk)(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempsetw_chk))(__dst, __word, __n_words, __dst_objsize); })
#elif defined(__CRT_HAVE___mempsetw_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__mempsetw_chk,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),(__dst,__word,__n_words,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__mempsetw_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__mempsetw_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL __mempsetw_chk)(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempsetw_chk))(__dst, __word, __n_words, __dst_objsize); })
#endif /* !... */
#ifdef __fast___memsetl_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__memsetl_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL __memsetl_chk)(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memsetl_chk))(__dst, __dword, __n_dwords, __dst_objsize); })
#elif defined(__CRT_HAVE___memsetl_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__memsetl_chk,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),(__dst,__dword,__n_dwords,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__memsetl_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__memsetl_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL __memsetl_chk)(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memsetl_chk))(__dst, __dword, __n_dwords, __dst_objsize); })
#endif /* !... */
#ifdef __fast___mempsetl_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__mempsetl_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL __mempsetl_chk)(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempsetl_chk))(__dst, __dword, __n_dwords, __dst_objsize); })
#elif defined(__CRT_HAVE___mempsetl_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__mempsetl_chk,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),(__dst,__dword,__n_dwords,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__mempsetl_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__mempsetl_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL __mempsetl_chk)(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempsetl_chk))(__dst, __dword, __n_dwords, __dst_objsize); })
#endif /* !... */
#ifdef __USE_KOS
#ifdef __fast___memmoveupw_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__memmoveupw_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL __memmoveupw_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmoveupw_chk))(__dst, __src, __n_words, __dst_objsize); })
#elif defined(__CRT_HAVE___memmoveupw_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__memmoveupw_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_words,__dst_objsize))
#elif defined(__CRT_HAVE___memmovew_chk)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__memmoveupw_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__memmovew_chk,(__dst,__src,__n_words,__dst_objsize))
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE___wmemmove_chk) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__memmoveupw_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__wmemmove_chk,(__dst,__src,__n_words,__dst_objsize))
#else /* __CRT_HAVE___wmemmove_chk && __SIZEOF_WCHAR_T__ == 2 */
#include <libc/local/ssp.string/__memmoveupw_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__memmoveupw_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL __memmoveupw_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmoveupw_chk))(__dst, __src, __n_words, __dst_objsize); })
#endif /* !__CRT_HAVE___wmemmove_chk || __SIZEOF_WCHAR_T__ != 2 */
#endif /* !... */
#ifdef __fast___memmovedownw_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__memmovedownw_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL __memmovedownw_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmovedownw_chk))(__dst, __src, __n_words, __dst_objsize); })
#elif defined(__CRT_HAVE___memmovedownw_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__memmovedownw_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_words,__dst_objsize))
#elif defined(__CRT_HAVE___memmovew_chk)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__memmovedownw_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__memmovew_chk,(__dst,__src,__n_words,__dst_objsize))
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE___wmemmove_chk) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__memmovedownw_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__wmemmove_chk,(__dst,__src,__n_words,__dst_objsize))
#else /* __CRT_HAVE___wmemmove_chk && __SIZEOF_WCHAR_T__ == 2 */
#include <libc/local/ssp.string/__memmovedownw_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__memmovedownw_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL __memmovedownw_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmovedownw_chk))(__dst, __src, __n_words, __dst_objsize); })
#endif /* !__CRT_HAVE___wmemmove_chk || __SIZEOF_WCHAR_T__ != 2 */
#endif /* !... */
#ifdef __fast___memmoveupl_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__memmoveupl_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL __memmoveupl_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmoveupl_chk))(__dst, __src, __n_dwords, __dst_objsize); })
#elif defined(__CRT_HAVE___memmoveupl_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__memmoveupl_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_dwords,__dst_objsize))
#elif defined(__CRT_HAVE___memmovel_chk)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__memmoveupl_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__memmovel_chk,(__dst,__src,__n_dwords,__dst_objsize))
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE___wmemmove_chk) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__memmoveupl_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__wmemmove_chk,(__dst,__src,__n_dwords,__dst_objsize))
#else /* __CRT_HAVE___wmemmove_chk && __SIZEOF_WCHAR_T__ == 4 */
#include <libc/local/ssp.string/__memmoveupl_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__memmoveupl_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL __memmoveupl_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmoveupl_chk))(__dst, __src, __n_dwords, __dst_objsize); })
#endif /* !__CRT_HAVE___wmemmove_chk || __SIZEOF_WCHAR_T__ != 4 */
#endif /* !... */
#ifdef __fast___memmovedownl_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__memmovedownl_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL __memmovedownl_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmovedownl_chk))(__dst, __src, __n_dwords, __dst_objsize); })
#elif defined(__CRT_HAVE___memmovedownl_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__memmovedownl_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_dwords,__dst_objsize))
#elif defined(__CRT_HAVE___memmovel_chk)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__memmovedownl_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__memmovel_chk,(__dst,__src,__n_dwords,__dst_objsize))
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE___wmemmove_chk) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__memmovedownl_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__wmemmove_chk,(__dst,__src,__n_dwords,__dst_objsize))
#else /* __CRT_HAVE___wmemmove_chk && __SIZEOF_WCHAR_T__ == 4 */
#include <libc/local/ssp.string/__memmovedownl_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__memmovedownl_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL __memmovedownl_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmovedownl_chk))(__dst, __src, __n_dwords, __dst_objsize); })
#endif /* !__CRT_HAVE___wmemmove_chk || __SIZEOF_WCHAR_T__ != 4 */
#endif /* !... */
#ifdef __fast___mempmoveupw_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__mempmoveupw_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL __mempmoveupw_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmoveupw_chk))(__dst, __src, __n_words, __dst_objsize); })
#elif defined(__CRT_HAVE___mempmoveupw_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__mempmoveupw_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_words,__dst_objsize))
#elif defined(__CRT_HAVE___mempmovew_chk)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__mempmoveupw_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__mempmovew_chk,(__dst,__src,__n_words,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__mempmoveupw_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__mempmoveupw_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL __mempmoveupw_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmoveupw_chk))(__dst, __src, __n_words, __dst_objsize); })
#endif /* !... */
#ifdef __fast___mempmovedownw_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__mempmovedownw_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL __mempmovedownw_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmovedownw_chk))(__dst, __src, __n_words, __dst_objsize); })
#elif defined(__CRT_HAVE___mempmovedownw_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__mempmovedownw_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_words,__dst_objsize))
#elif defined(__CRT_HAVE___mempmovew_chk)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__mempmovedownw_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize),__mempmovew_chk,(__dst,__src,__n_words,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__mempmovedownw_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__mempmovedownw_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL __mempmovedownw_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmovedownw_chk))(__dst, __src, __n_words, __dst_objsize); })
#endif /* !... */
#ifdef __fast___mempmoveupl_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__mempmoveupl_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL __mempmoveupl_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmoveupl_chk))(__dst, __src, __n_dwords, __dst_objsize); })
#elif defined(__CRT_HAVE___mempmoveupl_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__mempmoveupl_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_dwords,__dst_objsize))
#elif defined(__CRT_HAVE___mempmovel_chk)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__mempmoveupl_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__mempmovel_chk,(__dst,__src,__n_dwords,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__mempmoveupl_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__mempmoveupl_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL __mempmoveupl_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmoveupl_chk))(__dst, __src, __n_dwords, __dst_objsize); })
#endif /* !... */
#ifdef __fast___mempmovedownl_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__mempmovedownl_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL __mempmovedownl_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmovedownl_chk))(__dst, __src, __n_dwords, __dst_objsize); })
#elif defined(__CRT_HAVE___mempmovedownl_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__mempmovedownl_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_dwords,__dst_objsize))
#elif defined(__CRT_HAVE___mempmovel_chk)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__mempmovedownl_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize),__mempmovel_chk,(__dst,__src,__n_dwords,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__mempmovedownl_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__mempmovedownl_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL __mempmovedownl_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmovedownl_chk))(__dst, __src, __n_dwords, __dst_objsize); })
#endif /* !... */
#endif /* __USE_KOS */
#ifdef __UINT64_TYPE__
#ifdef __fast___memcpyq_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__memcpyq_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL __memcpyq_chk)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memcpyq_chk))(__dst, __src, __n_qwords, __dst_objsize); })
#elif defined(__CRT_HAVE___memcpyq_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__memcpyq_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_qwords,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__memcpyq_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__memcpyq_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL __memcpyq_chk)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memcpyq_chk))(__dst, __src, __n_qwords, __dst_objsize); })
#endif /* !... */
#ifdef __fast___mempcpyq_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__mempcpyq_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL __mempcpyq_chk)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempcpyq_chk))(__dst, __src, __n_qwords, __dst_objsize); })
#elif defined(__CRT_HAVE___mempcpyq_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__mempcpyq_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_qwords,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__mempcpyq_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__mempcpyq_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL __mempcpyq_chk)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempcpyq_chk))(__dst, __src, __n_qwords, __dst_objsize); })
#endif /* !... */
#ifdef __fast___memmoveq_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__memmoveq_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL __memmoveq_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmoveq_chk))(__dst, __src, __n_qwords, __dst_objsize); })
#elif defined(__CRT_HAVE___memmoveq_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__memmoveq_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_qwords,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__memmoveq_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__memmoveq_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL __memmoveq_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmoveq_chk))(__dst, __src, __n_qwords, __dst_objsize); })
#endif /* !... */
#ifdef __fast___mempmoveq_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__mempmoveq_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL __mempmoveq_chk)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmoveq_chk))(__dst, __src, __n_qwords, __dst_objsize); })
#elif defined(__CRT_HAVE___mempmoveq_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__mempmoveq_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_qwords,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__mempmoveq_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__mempmoveq_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL __mempmoveq_chk)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmoveq_chk))(__dst, __src, __n_qwords, __dst_objsize); })
#endif /* !... */
#ifdef __fast___memsetq_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__memsetq_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL __memsetq_chk)(void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memsetq_chk))(__dst, __qword, __n_qwords, __dst_objsize); })
#elif defined(__CRT_HAVE___memsetq_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,__memsetq_chk,(void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),(__dst,__qword,__n_qwords,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__memsetq_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__memsetq_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL __memsetq_chk)(void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memsetq_chk))(__dst, __qword, __n_qwords, __dst_objsize); })
#endif /* !... */
#ifdef __fast___mempsetq_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__mempsetq_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL __mempsetq_chk)(void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempsetq_chk))(__dst, __qword, __n_qwords, __dst_objsize); })
#elif defined(__CRT_HAVE___mempsetq_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,__mempsetq_chk,(void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),(__dst,__qword,__n_qwords,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__mempsetq_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__mempsetq_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL __mempsetq_chk)(void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempsetq_chk))(__dst, __qword, __n_qwords, __dst_objsize); })
#endif /* !... */
#ifdef __USE_KOS
#ifdef __fast___memmoveupq_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__memmoveupq_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL __memmoveupq_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmoveupq_chk))(__dst, __src, __n_qwords, __dst_objsize); })
#elif defined(__CRT_HAVE___memmoveupq_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__memmoveupq_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_qwords,__dst_objsize))
#elif defined(__CRT_HAVE___memmoveq_chk)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__memmoveupq_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__memmoveq_chk,(__dst,__src,__n_qwords,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__memmoveupq_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__memmoveupq_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL __memmoveupq_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmoveupq_chk))(__dst, __src, __n_qwords, __dst_objsize); })
#endif /* !... */
#ifdef __fast___memmovedownq_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__memmovedownq_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL __memmovedownq_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__memmovedownq_chk))(__dst, __src, __n_qwords, __dst_objsize); })
#elif defined(__CRT_HAVE___memmovedownq_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__memmovedownq_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_qwords,__dst_objsize))
#elif defined(__CRT_HAVE___memmoveq_chk)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__memmovedownq_chk,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__memmoveq_chk,(__dst,__src,__n_qwords,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__memmovedownq_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__memmovedownq_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL __memmovedownq_chk)(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmovedownq_chk))(__dst, __src, __n_qwords, __dst_objsize); })
#endif /* !... */
#ifdef __fast___mempmoveupq_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__mempmoveupq_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL __mempmoveupq_chk)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmoveupq_chk))(__dst, __src, __n_qwords, __dst_objsize); })
#elif defined(__CRT_HAVE___mempmoveupq_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__mempmoveupq_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_qwords,__dst_objsize))
#elif defined(__CRT_HAVE___mempmoveq_chk)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__mempmoveupq_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__mempmoveq_chk,(__dst,__src,__n_qwords,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__mempmoveupq_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__mempmoveupq_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL __mempmoveupq_chk)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmoveupq_chk))(__dst, __src, __n_qwords, __dst_objsize); })
#endif /* !... */
#ifdef __fast___mempmovedownq_chk_defined
__NAMESPACE_FAST_USING_OR_IMPL(__mempmovedownq_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL __mempmovedownq_chk)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(__mempmovedownq_chk))(__dst, __src, __n_qwords, __dst_objsize); })
#elif defined(__CRT_HAVE___mempmovedownq_chk)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__mempmovedownq_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),(__dst,__src,__n_qwords,__dst_objsize))
#elif defined(__CRT_HAVE___mempmoveq_chk)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__mempmovedownq_chk,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize),__mempmoveq_chk,(__dst,__src,__n_qwords,__dst_objsize))
#else /* ... */
#include <libc/local/ssp.string/__mempmovedownq_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__mempmovedownq_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL __mempmovedownq_chk)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempmovedownq_chk))(__dst, __src, __n_qwords, __dst_objsize); })
#endif /* !... */
#endif /* __USE_KOS */
#endif /* __UINT64_TYPE__ */
#endif /* __USE_STRING_BWLQ */



/* Bind SSP function variants if necessary */
#ifdef __SSP_FORTIFY_LEVEL
#if (defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_memset) && \
     defined(__CRT_HAVE___memset_chk) && __has_builtin(__builtin___memset_chk))
#undef __PRIVATE_memset_3
#define __PRIVATE_memset_3(dst, byte, n_bytes)                                                          \
	(__ssp_bos0(dst) != (__SIZE_TYPE__)-1 ? __builtin___memset_chk(dst, byte, n_bytes, __ssp_bos0(dst)) \
	                                      : __memset_chk(dst, byte, n_bytes, __ssp_bos0(dst)))
#else /* ... */
#undef __PRIVATE_memset_3
#define __PRIVATE_memset_3(dst, byte, n_bytes) __memset_chk(dst, byte, n_bytes, __ssp_bos0(dst))
#endif /* !... */
#if (defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_memcpy) && \
     defined(__CRT_HAVE___memcpy_chk) && __has_builtin(__builtin___memcpy_chk))
#undef __PRIVATE_memcpy_3
#define __PRIVATE_memcpy_3(dst, src, n_bytes)                                                          \
	(__ssp_bos0(dst) != (__SIZE_TYPE__)-1 ? __builtin___memcpy_chk(dst, src, n_bytes, __ssp_bos0(dst)) \
	                                      : __memcpy_chk(dst, src, n_bytes, __ssp_bos0(dst)))
#else /* ... */
#undef __PRIVATE_memcpy_3
#define __PRIVATE_memcpy_3(dst, src, n_bytes) __memcpy_chk(dst, src, n_bytes, __ssp_bos0(dst))
#endif /* !... */
#if (defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_memmove) && \
     defined(__CRT_HAVE___memmove_chk) && __has_builtin(__builtin___memmove_chk))
#undef __PRIVATE_memmove_3
#define __PRIVATE_memmove_3(dst, src, n_bytes)                                                          \
	(__ssp_bos0(dst) != (__SIZE_TYPE__)-1 ? __builtin___memmove_chk(dst, src, n_bytes, __ssp_bos0(dst)) \
	                                      : __memmove_chk(dst, src, n_bytes, __ssp_bos0(dst)))
#else /* ... */
#undef __PRIVATE_memmove_3
#define __PRIVATE_memmove_3(dst, src, n_bytes) __memmove_chk(dst, src, n_bytes, __ssp_bos0(dst))
#endif /* !... */

#ifdef __USE_STRING_OVERLOADS
#undef __PRIVATE_memcpy_4
#define __PRIVATE_memcpy_4(dst, src, elem_count, elem_size) __memcpyc_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))
#undef __PRIVATE_memmove_4
#define __PRIVATE_memmove_4(dst, src, elem_count, elem_size) __memmovec_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))
#endif /* __USE_STRING_OVERLOADS */

#ifdef __USE_GNU
#if (defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_mempcpy) && \
     defined(__CRT_HAVE___mempcpy_chk) && __has_builtin(__builtin___mempcpy_chk))
#undef __PRIVATE_mempcpy_3
#define __PRIVATE_mempcpy_3(dst, src, n_bytes)                                                          \
	(__ssp_bos0(dst) != (__SIZE_TYPE__)-1 ? __builtin___mempcpy_chk(dst, src, n_bytes, __ssp_bos0(dst)) \
	                                      : __mempcpy_chk(dst, src, n_bytes, __ssp_bos0(dst)))
#else /* ... */
#undef __PRIVATE_mempcpy_3
#define __PRIVATE_mempcpy_3(dst, src, n_bytes) __mempcpy_chk(dst, src, n_bytes, __ssp_bos0(dst))
#endif /* !... */
#ifdef __USE_STRING_OVERLOADS
#undef __PRIVATE_mempcpy_4
#define __PRIVATE_mempcpy_4(dst, src, elem_count, elem_size) __mempcpyc_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))
#endif /* __USE_STRING_OVERLOADS */
#endif /* __USE_GNU */

#ifdef __USE_KOS
#undef memcpyc
#define memcpyc(dst, src, elem_count, elem_size) __memcpyc_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))
#undef memmovec
#define memmovec(dst, src, elem_count, elem_size) __memmovec_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))
#undef mempcpyc
#define mempcpyc(dst, src, elem_count, elem_size) __mempcpyc_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))
#undef mempmovec
#define mempmovec(dst, src, elem_count, elem_size) __mempmovec_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))
#undef memmoveupc
#define memmoveupc(dst, src, elem_count, elem_size) __memmoveupc_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))
#undef mempmoveupc
#define mempmoveupc(dst, src, elem_count, elem_size) __mempmoveupc_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))
#undef memmovedownc
#define memmovedownc(dst, src, elem_count, elem_size) __memmovedownc_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))
#undef mempmovedownc
#define mempmovedownc(dst, src, elem_count, elem_size) __mempmovedownc_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))
#undef __PRIVATE_mempset_3
#define __PRIVATE_mempset_3(dst, byte, n_bytes) __mempset_chk(dst, byte, n_bytes, __ssp_bos0(dst))
#undef __PRIVATE_mempmove_3
#define __PRIVATE_mempmove_3(dst, src, n_bytes) __mempmove_chk(dst, src, n_bytes, __ssp_bos0(dst))
#undef __PRIVATE_memmoveup_3
#define __PRIVATE_memmoveup_3(dst, src, n_bytes) __memmoveup_chk(dst, src, n_bytes, __ssp_bos0(dst))
#undef __PRIVATE_mempmoveup_3
#define __PRIVATE_mempmoveup_3(dst, src, n_bytes) __mempmoveup_chk(dst, src, n_bytes, __ssp_bos0(dst))
#undef __PRIVATE_memmovedown_3
#define __PRIVATE_memmovedown_3(dst, src, n_bytes) __memmovedown_chk(dst, src, n_bytes, __ssp_bos0(dst))
#undef __PRIVATE_mempmovedown_3
#define __PRIVATE_mempmovedown_3(dst, src, n_bytes) __mempmovedown_chk(dst, src, n_bytes, __ssp_bos0(dst))
#ifdef __USE_STRING_OVERLOADS
#undef __PRIVATE_mempmove_4
#define __PRIVATE_mempmove_4(dst, src, elem_count, elem_size) __mempmovec_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))
#undef __PRIVATE_memmoveup_4
#define __PRIVATE_memmoveup_4(dst, src, elem_count, elem_size) __memmoveupc_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))
#undef __PRIVATE_mempmoveup_4
#define __PRIVATE_mempmoveup_4(dst, src, elem_count, elem_size) __mempmoveupc_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))
#undef __PRIVATE_memmovedown_4
#define __PRIVATE_memmovedown_4(dst, src, elem_count, elem_size) __memmovedownc_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))
#undef __PRIVATE_mempmovedown_4
#define __PRIVATE_mempmovedown_4(dst, src, elem_count, elem_size) __mempmovedownc_chk(dst, src, elem_count, elem_size, __ssp_bos0(dst))
#endif /* __USE_STRING_OVERLOADS */
#endif /* __USE_KOS */
#ifdef __USE_STRING_BWLQ
#undef memcpyw
#define memcpyw(dst, src, n_words) __memcpyw_chk(dst, src, n_words, __ssp_bos0(dst))
#undef mempcpyw
#define mempcpyw(dst, src, n_words) __mempcpyw_chk(dst, src, n_words, __ssp_bos0(dst))
#undef memmovew
#define memmovew(dst, src, n_words) __memmovew_chk(dst, src, n_words, __ssp_bos0(dst))
#undef memcpyl
#define memcpyl(dst, src, n_dwords) __memcpyl_chk(dst, src, n_dwords, __ssp_bos0(dst))
#undef mempcpyl
#define mempcpyl(dst, src, n_dwords) __mempcpyl_chk(dst, src, n_dwords, __ssp_bos0(dst))
#undef memmovel
#define memmovel(dst, src, n_dwords) __memmovel_chk(dst, src, n_dwords, __ssp_bos0(dst))
#undef mempmovew
#define mempmovew(dst, src, n_words) __mempmovew_chk(dst, src, n_words, __ssp_bos0(dst))
#undef mempmovel
#define mempmovel(dst, src, n_dwords) __mempmovel_chk(dst, src, n_dwords, __ssp_bos0(dst))
#undef memsetw
#define memsetw(dst, word, n_words) __memsetw_chk(dst, word, n_words, __ssp_bos0(dst))
#undef mempsetw
#define mempsetw(dst, word, n_words) __mempsetw_chk(dst, word, n_words, __ssp_bos0(dst))
#undef memsetl
#define memsetl(dst, dword, n_dwords) __memsetl_chk(dst, dword, n_dwords, __ssp_bos0(dst))
#undef mempsetl
#define mempsetl(dst, dword, n_dwords) __mempsetl_chk(dst, dword, n_dwords, __ssp_bos0(dst))
#ifdef __USE_KOS
#undef memmoveupw
#define memmoveupw(dst, src, n_words) __memmoveupw_chk(dst, src, n_words, __ssp_bos0(dst))
#undef memmovedownw
#define memmovedownw(dst, src, n_words) __memmovedownw_chk(dst, src, n_words, __ssp_bos0(dst))
#undef memmoveupl
#define memmoveupl(dst, src, n_dwords) __memmoveupl_chk(dst, src, n_dwords, __ssp_bos0(dst))
#undef memmovedownl
#define memmovedownl(dst, src, n_dwords) __memmovedownl_chk(dst, src, n_dwords, __ssp_bos0(dst))
#undef mempmoveupw
#define mempmoveupw(dst, src, n_words) __mempmoveupw_chk(dst, src, n_words, __ssp_bos0(dst))
#undef mempmovedownw
#define mempmovedownw(dst, src, n_words) __mempmovedownw_chk(dst, src, n_words, __ssp_bos0(dst))
#undef mempmoveupl
#define mempmoveupl(dst, src, n_dwords) __mempmoveupl_chk(dst, src, n_dwords, __ssp_bos0(dst))
#undef mempmovedownl
#define mempmovedownl(dst, src, n_dwords) __mempmovedownl_chk(dst, src, n_dwords, __ssp_bos0(dst))
#endif /* __USE_KOS */
#ifdef __UINT64_TYPE__
#undef memcpyq
#define memcpyq(dst, src, n_qwords) __memcpyq_chk(dst, src, n_qwords, __ssp_bos0(dst))
#undef mempcpyq
#define mempcpyq(dst, src, n_qwords) __mempcpyq_chk(dst, src, n_qwords, __ssp_bos0(dst))
#undef memmoveq
#define memmoveq(dst, src, n_qwords) __memmoveq_chk(dst, src, n_qwords, __ssp_bos0(dst))
#undef mempmoveq
#define mempmoveq(dst, src, n_qwords) __mempmoveq_chk(dst, src, n_qwords, __ssp_bos0(dst))
#undef memsetq
#define memsetq(dst, qword, n_qwords) __memsetq_chk(dst, qword, n_qwords, __ssp_bos0(dst))
#undef mempsetq
#define mempsetq(dst, qword, n_qwords) __mempsetq_chk(dst, qword, n_qwords, __ssp_bos0(dst))
#ifdef __USE_KOS
#undef memmoveupq
#define memmoveupq(dst, src, n_qwords) __memmoveupq_chk(dst, src, n_qwords, __ssp_bos0(dst))
#undef memmovedownq
#define memmovedownq(dst, src, n_qwords) __memmovedownq_chk(dst, src, n_qwords, __ssp_bos0(dst))
#undef mempmoveupq
#define mempmoveupq(dst, src, n_qwords) __mempmoveupq_chk(dst, src, n_qwords, __ssp_bos0(dst))
#undef mempmovedownq
#define mempmovedownq(dst, src, n_qwords) __mempmovedownq_chk(dst, src, n_qwords, __ssp_bos0(dst))
#endif /* __USE_KOS */
#endif /* __UINT64_TYPE__ */
#endif /* __USE_STRING_BWLQ */

#if defined(__cplusplus) || !defined(__USE_STRING_OVERLOADS)
#ifdef __cplusplus
__NAMESPACE_STD_BEGIN
typedef void *__forward_voidp;
__NAMESPACE_STD_END
__NAMESPACE_STD_USING(__forward_voidp)
#endif /* __cplusplus */
#undef memset
#undef memcpy
#undef memmove
#ifdef __USE_STRING_OVERLOADS
#ifdef __cplusplus
#define memset(...)  __forward_voidp(__HYBRID_PP_VA_OVERLOAD(__PRIVATE_memset_, (__VA_ARGS__))(__VA_ARGS__))
#define memcpy(...)  __forward_voidp(__HYBRID_PP_VA_OVERLOAD(__PRIVATE_memcpy_, (__VA_ARGS__))(__VA_ARGS__))
#define memmove(...) __forward_voidp(__HYBRID_PP_VA_OVERLOAD(__PRIVATE_memmove_, (__VA_ARGS__))(__VA_ARGS__))
#else /* __cplusplus */
#define memset(...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memset_, (__VA_ARGS__))(__VA_ARGS__)
#define memcpy(...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memcpy_, (__VA_ARGS__))(__VA_ARGS__)
#define memmove(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memmove_, (__VA_ARGS__))(__VA_ARGS__)
#endif /* !__cplusplus */
#ifdef __USE_GNU
#undef mempcpy
#define mempcpy(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempcpy_, (__VA_ARGS__))(__VA_ARGS__)
#endif /* __USE_GNU */
#ifdef __USE_KOS
#undef mempset
#undef mempmove
#undef mempmoveup
#undef mempmovedown
#undef memmoveup
#undef memmovedown
#define mempset(...)      __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempset_, (__VA_ARGS__))(__VA_ARGS__)
#define mempmove(...)     __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempmove_, (__VA_ARGS__))(__VA_ARGS__)
#define mempmoveup(...)   __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempmoveup_, (__VA_ARGS__))(__VA_ARGS__)
#define mempmovedown(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempmovedown_, (__VA_ARGS__))(__VA_ARGS__)
#define memmoveup(...)    __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memmoveup_, (__VA_ARGS__))(__VA_ARGS__)
#define memmovedown(...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memmovedown_, (__VA_ARGS__))(__VA_ARGS__)
#endif /* __USE_KOS */
#else /* __USE_STRING_OVERLOADS */
#define memset(dst, src, n_bytes)  __forward_voidp(__PRIVATE_memset_3(dst, src, n_bytes))
#define memcpy(dst, src, n_bytes)  __forward_voidp(__PRIVATE_memcpy_3(dst, src, n_bytes))
#define memmove(dst, src, n_bytes) __forward_voidp(__PRIVATE_memmove_3(dst, src, n_bytes))
#ifdef __USE_GNU
#undef mempcpy
#define mempcpy(dst, src, n_bytes) __PRIVATE_mempcpy_3(dst, src, n_bytes)
#endif /* __USE_GNU */
#ifdef __USE_KOS
#undef mempset
#undef mempmove
#undef mempmoveup
#undef mempmovedown
#undef memmoveup
#undef memmovedown
#define mempset(dst, src, n_bytes)      __PRIVATE_mempset_3(dst, src, n_bytes)
#define mempmove(dst, src, n_bytes)     __PRIVATE_mempmove_3(dst, src, n_bytes)
#define mempmoveup(dst, src, n_bytes)   __PRIVATE_mempmoveup_3(dst, src, n_bytes)
#define mempmovedown(dst, src, n_bytes) __PRIVATE_mempmovedown_3(dst, src, n_bytes)
#define memmoveup(dst, src, n_bytes)    __PRIVATE_memmoveup_3(dst, src, n_bytes)
#define memmovedown(dst, src, n_bytes)  __PRIVATE_memmovedown_3(dst, src, n_bytes)
#endif /* __USE_KOS */
#endif /* !__USE_STRING_OVERLOADS */
#endif /* __cplusplus || !__USE_STRING_OVERLOADS */


#if (defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcpy) && \
     defined(__CRT_HAVE___strcpy_chk) && __has_builtin(__builtin___strcpy_chk))
#undef strcpy
#define strcpy(buf, src)                                                                      \
	(__ssp_bos0(buf) != (__SIZE_TYPE__)-1 ? __builtin___strcpy_chk(buf, src, __ssp_bos0(buf)) \
	                                      : __strcpy_chk(buf, src, __ssp_bos0(buf)))
#else /* ... */
#undef strcpy
#define strcpy(buf, src) __strcpy_chk(buf, src, __ssp_bos0(buf))
#endif /* !... */
#if (defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcat) && \
     defined(__CRT_HAVE___strcat_chk) && __has_builtin(__builtin___strcat_chk))
#undef strcat
#define strcat(buf, src)                                                                      \
	(__ssp_bos0(buf) != (__SIZE_TYPE__)-1 ? __builtin___strcat_chk(buf, src, __ssp_bos0(buf)) \
	                                      : __strcat_chk(buf, src, __ssp_bos0(buf)))
#else /* ... */
#undef strcat
#define strcat(buf, src) __strcat_chk(buf, src, __ssp_bos0(buf))
#endif /* !... */
#if (defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncpy) && \
     defined(__CRT_HAVE___strncpy_chk) && __has_builtin(__builtin___strncpy_chk))
#undef strncpy
#define strncpy(buf, src, buflen)                                                                      \
	(__ssp_bos0(buf) != (__SIZE_TYPE__)-1 ? __builtin___strncpy_chk(buf, src, buflen, __ssp_bos0(buf)) \
	                                      : __strncpy_chk(buf, src, buflen, __ssp_bos0(buf)))
#else /* ... */
#undef strncpy
#define strncpy(buf, src, buflen) __strncpy_chk(buf, src, buflen, __ssp_bos0(buf))
#endif /* !... */
#if (defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncat) && \
     defined(__CRT_HAVE___strncat_chk) && __has_builtin(__builtin___strncat_chk))
#undef strncat
#define strncat(buf, src, buflen)                                                                      \
	(__ssp_bos0(buf) != (__SIZE_TYPE__)-1 ? __builtin___strncat_chk(buf, src, buflen, __ssp_bos0(buf)) \
	                                      : __strncat_chk(buf, src, buflen, __ssp_bos0(buf)))
#else /* ... */
#undef strncat
#define strncat(buf, src, buflen) __strncat_chk(buf, src, buflen, __ssp_bos0(buf))
#endif /* !... */
#ifdef __USE_XOPEN2K8
#if (defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_stpcpy) && \
     defined(__CRT_HAVE___stpcpy_chk) && __has_builtin(__builtin___stpcpy_chk))
#undef stpcpy
#define stpcpy(buf, src)                                                                      \
	(__ssp_bos0(buf) != (__SIZE_TYPE__)-1 ? __builtin___stpcpy_chk(buf, src, __ssp_bos0(buf)) \
	                                      : __stpcpy_chk(buf, src, __ssp_bos0(buf)))
#else /* ... */
#undef stpcpy
#define stpcpy(buf, src) __stpcpy_chk(buf, src, __ssp_bos0(buf))
#endif /* !... */
#if (defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_stpncpy) && \
     defined(__CRT_HAVE___stpncpy_chk) && __has_builtin(__builtin___stpncpy_chk))
#undef stpncpy
#define stpncpy(buf, src, buflen)                                                                      \
	(__ssp_bos0(buf) != (__SIZE_TYPE__)-1 ? __builtin___stpncpy_chk(buf, src, buflen, __ssp_bos0(buf)) \
	                                      : __stpncpy_chk(buf, src, buflen, __ssp_bos0(buf)))
#else /* ... */
#undef stpncpy
#define stpncpy(buf, src, buflen) __stpncpy_chk(buf, src, buflen, __ssp_bos0(buf))
#endif /* !... */
#endif /* __USE_XOPEN2K8 */

#endif /* __SSP_FORTIFY_LEVEL */


#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SSP_STRING_H */
