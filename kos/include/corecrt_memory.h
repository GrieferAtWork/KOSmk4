/* HASH CRC-32:0x5783f4cf */
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
/* (#) Portability: Windows Kits (/ucrt/corecrt_memory.h) */
#ifndef _CORECRT_MEMORY_H
#define _CORECRT_MEMORY_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <hybrid/typecore.h>
#include <bits/types.h>
#include <vcruntime_string.h>
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __memcpy_defined
#define __memcpy_defined
#ifdef __std_memcpy_defined
/* >> memcpy(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__NAMESPACE_STD_USING(memcpy)
#elif defined(__fast_memcpy_defined) && defined(__CRT_HAVE_memcpy)
/* >> memcpy(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CEIDECLARE_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memcpy,(void *__restrict __dst, void const *__restrict __src, size_t __n_bytes),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpy))(__dst, __src, __n_bytes); })
#elif defined(__fast_memcpy_defined)
/* >> memcpy(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memcpy)(void *__restrict __dst, void const *__restrict __src, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpy))(__dst, __src, __n_bytes); }
#elif defined(__CRT_HAVE_memcpy)
/* >> memcpy(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CDECLARE_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memcpy,(void *__restrict __dst, void const *__restrict __src, size_t __n_bytes),(__dst,__src,__n_bytes))
#else /* ... */
#include <libc/local/string/memcpy.h>
/* >> memcpy(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memcpy)(void *__restrict __dst, void const *__restrict __src, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpy))(__dst, __src, __n_bytes); })
#endif /* !... */
#endif /* !__memcpy_defined */
#ifndef __memcpy_s_defined
#define __memcpy_s_defined
#ifdef __CRT_HAVE_memcpy_s
__CDECLARE(__ATTR_NONNULL((1, 3)),__errno_t,__NOTHROW_NCX,memcpy_s,(void *__dst, rsize_t __dstlength, void const *__src, rsize_t __srclength),(__dst,__dstlength,__src,__srclength))
#else /* __CRT_HAVE_memcpy_s */
#include <libc/local/string/memcpy_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memcpy_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) __errno_t __NOTHROW_NCX(__LIBCCALL memcpy_s)(void *__dst, rsize_t __dstlength, void const *__src, rsize_t __srclength) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpy_s))(__dst, __dstlength, __src, __srclength); })
#endif /* !__CRT_HAVE_memcpy_s */
#endif /* !__memcpy_s_defined */
#ifndef __memmove_s_defined
#define __memmove_s_defined
#ifdef __CRT_HAVE_memmove_s
__CDECLARE(__ATTR_NONNULL((1, 3)),__errno_t,__NOTHROW_NCX,memmove_s,(void *__dst, rsize_t __dstlength, void const *__src, rsize_t __srclength),(__dst,__dstlength,__src,__srclength))
#else /* __CRT_HAVE_memmove_s */
#include <libc/local/string/memmove_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memmove_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) __errno_t __NOTHROW_NCX(__LIBCCALL memmove_s)(void *__dst, rsize_t __dstlength, void const *__src, rsize_t __srclength) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmove_s))(__dst, __dstlength, __src, __srclength); })
#endif /* !__CRT_HAVE_memmove_s */
#endif /* !__memmove_s_defined */
#ifndef __memccpy_defined
#define __memccpy_defined
#ifdef __CRT_HAVE_memccpy
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memccpy,(void *__restrict __dst, void const *__restrict __src, int __needle, __SIZE_TYPE__ __num_bytes),(__dst,__src,__needle,__num_bytes))
#elif defined(__CRT_HAVE__memccpy)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memccpy,(void *__restrict __dst, void const *__restrict __src, int __needle, __SIZE_TYPE__ __num_bytes),_memccpy,(__dst,__src,__needle,__num_bytes))
#elif defined(__CRT_HAVE___memccpy)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memccpy,(void *__restrict __dst, void const *__restrict __src, int __needle, __SIZE_TYPE__ __num_bytes),__memccpy,(__dst,__src,__needle,__num_bytes))
#else /* ... */
#include <libc/local/string/memccpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memccpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memccpy)(void *__restrict __dst, void const *__restrict __src, int __needle, __SIZE_TYPE__ __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memccpy))(__dst, __src, __needle, __num_bytes); })
#endif /* !... */
#endif /* !__memccpy_defined */
#ifndef ___memccpy_defined
#define ___memccpy_defined
#ifdef __CRT_HAVE_memccpy
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,_memccpy,(void *__restrict __dst, void const *__restrict __src, int __needle, __SIZE_TYPE__ __num_bytes),memccpy,(__dst,__src,__needle,__num_bytes))
#elif defined(__CRT_HAVE__memccpy)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,_memccpy,(void *__restrict __dst, void const *__restrict __src, int __needle, __SIZE_TYPE__ __num_bytes),(__dst,__src,__needle,__num_bytes))
#elif defined(__CRT_HAVE___memccpy)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,_memccpy,(void *__restrict __dst, void const *__restrict __src, int __needle, __SIZE_TYPE__ __num_bytes),__memccpy,(__dst,__src,__needle,__num_bytes))
#else /* ... */
#include <libc/local/string/memccpy.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL _memccpy)(void *__restrict __dst, void const *__restrict __src, int __needle, __SIZE_TYPE__ __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memccpy))(__dst, __src, __needle, __num_bytes); }
#endif /* !... */
#endif /* !___memccpy_defined */
#ifndef ___memicmp_defined
#define ___memicmp_defined
#ifdef __CRT_HAVE_memcasecmp
/* >> memcasecmp(3), memcasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_memicmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcasecmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_memicmp)
/* >> memcasecmp(3), memcasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_memicmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memicmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE__memicmp)
/* >> memcasecmp(3), memcasecmp_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_memicmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),(__s1,__s2,__n_bytes))
#else /* ... */
#include <libc/local/string/memcasecmp.h>
/* >> memcasecmp(3), memcasecmp_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _memicmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasecmp))(__s1, __s2, __n_bytes); }
#endif /* !... */
#endif /* !___memicmp_defined */
#ifndef ___memicmp_l_defined
#define ___memicmp_l_defined
#ifdef __CRT_HAVE_memcasecmp_l
/* >> memcasecmp(3), memcasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_memicmp_l,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes, __locale_t __locale),memcasecmp_l,(__s1,__s2,__n_bytes,__locale))
#elif defined(__CRT_HAVE__memicmp_l)
/* >> memcasecmp(3), memcasecmp_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_memicmp_l,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes, __locale_t __locale),(__s1,__s2,__n_bytes,__locale))
#else /* ... */
#include <libc/local/string/memcasecmp_l.h>
/* >> memcasecmp(3), memcasecmp_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _memicmp_l)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasecmp_l))(__s1, __s2, __n_bytes, __locale); }
#endif /* !... */
#endif /* !___memicmp_l_defined */
#ifndef __memicmp_defined
#define __memicmp_defined
#ifdef __CRT_HAVE_memcasecmp
/* >> memcasecmp(3), memcasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memicmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcasecmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_memicmp)
/* >> memcasecmp(3), memcasecmp_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memicmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE__memicmp)
/* >> memcasecmp(3), memcasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memicmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),_memicmp,(__s1,__s2,__n_bytes))
#else /* ... */
#include <libc/local/string/memcasecmp.h>
/* >> memcasecmp(3), memcasecmp_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL memicmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasecmp))(__s1, __s2, __n_bytes); }
#endif /* !... */
#endif /* !__memicmp_defined */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_CORECRT_MEMORY_H */
