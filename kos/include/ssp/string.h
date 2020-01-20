/* HASH CRC-32:0xe6ad5214 */
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
#ifndef _SSP_STRING_H
#define _SSP_STRING_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifdef __CRT_HAVE___memcpy_chk
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__memcpy_chk,(void *__restrict __dst, void const *__restrict __src, size_t __num_bytes, size_t __dst_bufsize),(__dst,__src,__num_bytes,__dst_bufsize))
#else /* LIBC: __memcpy_chk */
#include <local/ssp.string/__memcpy_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__memcpy_chk, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __memcpy_chk)(void *__restrict __dst, void const *__restrict __src, size_t __num_bytes, size_t __dst_bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memcpy_chk))(__dst, __src, __num_bytes, __dst_bufsize); })
#endif /* __memcpy_chk... */
#ifdef __CRT_HAVE___memmove_chk
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__memmove_chk,(void *__dst, void const *__src, size_t __num_bytes, size_t __dst_bufsize),(__dst,__src,__num_bytes,__dst_bufsize))
#else /* LIBC: __memmove_chk */
#include <local/ssp.string/__memmove_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__memmove_chk, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __memmove_chk)(void *__dst, void const *__src, size_t __num_bytes, size_t __dst_bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memmove_chk))(__dst, __src, __num_bytes, __dst_bufsize); })
#endif /* __memmove_chk... */
#ifdef __CRT_HAVE___mempcpy_chk
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__mempcpy_chk,(void *__restrict __dst, void const *__restrict __src, size_t __num_bytes, size_t __dst_bufsize),(__dst,__src,__num_bytes,__dst_bufsize))
#else /* LIBC: __mempcpy_chk */
#include <local/ssp.string/__mempcpy_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__mempcpy_chk, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __mempcpy_chk)(void *__restrict __dst, void const *__restrict __src, size_t __num_bytes, size_t __dst_bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mempcpy_chk))(__dst, __src, __num_bytes, __dst_bufsize); })
#endif /* __mempcpy_chk... */
#ifdef __CRT_HAVE___memset_chk
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__memset_chk,(void *__restrict __dst, int __byte, size_t __num_bytes, size_t __dst_bufsize),(__dst,__byte,__num_bytes,__dst_bufsize))
#else /* LIBC: __memset_chk */
#include <local/ssp.string/__memset_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__memset_chk, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL __memset_chk)(void *__restrict __dst, int __byte, size_t __num_bytes, size_t __dst_bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__memset_chk))(__dst, __byte, __num_bytes, __dst_bufsize); })
#endif /* __memset_chk... */
#ifdef __CRT_HAVE___stpcpy_chk
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__stpcpy_chk,(char *__restrict __dst, char const *__restrict __src, size_t __dst_bufsize),(__dst,__src,__dst_bufsize))
#else /* LIBC: __stpcpy_chk */
#include <local/ssp.string/__stpcpy_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__stpcpy_chk, __FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL __stpcpy_chk)(char *__restrict __dst, char const *__restrict __src, size_t __dst_bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__stpcpy_chk))(__dst, __src, __dst_bufsize); })
#endif /* __stpcpy_chk... */
#ifdef __CRT_HAVE___strcat_chk
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__strcat_chk,(char *__restrict __dst, char const *__restrict __src, size_t __dst_bufsize),(__dst,__src,__dst_bufsize))
#else /* LIBC: __strcat_chk */
#include <local/ssp.string/__strcat_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__strcat_chk, __FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL __strcat_chk)(char *__restrict __dst, char const *__restrict __src, size_t __dst_bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__strcat_chk))(__dst, __src, __dst_bufsize); })
#endif /* __strcat_chk... */
#ifdef __CRT_HAVE___strcpy_chk
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__strcpy_chk,(char *__restrict __dst, char const *__restrict __src, size_t __dst_bufsize),(__dst,__src,__dst_bufsize))
#else /* LIBC: __strcpy_chk */
#include <local/ssp.string/__strcpy_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__strcpy_chk, __FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL __strcpy_chk)(char *__restrict __dst, char const *__restrict __src, size_t __dst_bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__strcpy_chk))(__dst, __src, __dst_bufsize); })
#endif /* __strcpy_chk... */
#ifdef __CRT_HAVE___strncat_chk
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__strncat_chk,(char *__restrict __dst, char const *__restrict __src, size_t __buflen, size_t __dst_bufsize),(__dst,__src,__buflen,__dst_bufsize))
#else /* LIBC: __strncat_chk */
#include <local/ssp.string/__strncat_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__strncat_chk, __FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL __strncat_chk)(char *__restrict __dst, char const *__restrict __src, size_t __buflen, size_t __dst_bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__strncat_chk))(__dst, __src, __buflen, __dst_bufsize); })
#endif /* __strncat_chk... */
#ifdef __CRT_HAVE___strncpy_chk
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__strncpy_chk,(char *__restrict __dst, char const *__restrict __src, size_t __buflen, size_t __dst_bufsize),(__dst,__src,__buflen,__dst_bufsize))
#else /* LIBC: __strncpy_chk */
#include <local/ssp.string/__strncpy_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__strncpy_chk, __FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL __strncpy_chk)(char *__restrict __dst, char const *__restrict __src, size_t __buflen, size_t __dst_bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__strncpy_chk))(__dst, __src, __buflen, __dst_bufsize); })
#endif /* __strncpy_chk... */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SSP_STRING_H */
