/* HASH CRC-32:0xf4d54488 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _PARTS_UCHAR_STRING_H
#define _PARTS_UCHAR_STRING_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#ifndef _STRING_H
#include <string.h>
#endif /* !_STRING_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */

#include <parts/malloca.h>

#ifdef __CC__
__SYSDECL_BEGIN

#if defined(__CRT_HAVE_wmemcpy) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wmemcpy(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char16_t *,__NOTHROW_NCX,c16memcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, size_t __num_chars),wmemcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmemcpy)
/* >> wmemcpy(3) */
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char16_t *,__NOTHROW_NCX,c16memcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, size_t __num_chars),wmemcpy,(__dst,__src,__num_chars))
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE_memcpyw) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wmemcpy(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char16_t *,__NOTHROW_NCX,c16memcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, size_t __num_chars),memcpyw,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$memcpyw)
/* >> wmemcpy(3) */
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char16_t *,__NOTHROW_NCX,c16memcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, size_t __num_chars),memcpyw,(__dst,__src,__num_chars))
#else /* ... */
#include <libc/local/string/memcpyw.h>
/* >> wmemcpy(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) char16_t *__NOTHROW_NCX(__LIBDCALL c16memcpy)(char16_t *__restrict __dst, char16_t const *__restrict __src, size_t __num_chars) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyw))((void *)__dst, (void const *)__src, (__SIZE_TYPE__)__num_chars); }
#endif /* !... */
#endif /* !... */
#if defined(__CRT_HAVE_wmemcpy) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wmemcpy(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char32_t *,__NOTHROW_NCX,c32memcpy,(char32_t *__restrict __dst, char32_t const *__restrict __src, size_t __num_chars),wmemcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_KOS$wmemcpy)
/* >> wmemcpy(3) */
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char32_t *,__NOTHROW_NCX,c32memcpy,(char32_t *__restrict __dst, char32_t const *__restrict __src, size_t __num_chars),wmemcpy,(__dst,__src,__num_chars))
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE_memcpyl) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wmemcpy(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char32_t *,__NOTHROW_NCX,c32memcpy,(char32_t *__restrict __dst, char32_t const *__restrict __src, size_t __num_chars),memcpyl,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_KOS$memcpyl)
/* >> wmemcpy(3) */
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char32_t *,__NOTHROW_NCX,c32memcpy,(char32_t *__restrict __dst, char32_t const *__restrict __src, size_t __num_chars),memcpyl,(__dst,__src,__num_chars))
#else /* ... */
#include <libc/local/string/memcpyl.h>
/* >> wmemcpy(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) char32_t *__NOTHROW_NCX(__LIBKCALL c32memcpy)(char32_t *__restrict __dst, char32_t const *__restrict __src, size_t __num_chars) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyl))((void *)__dst, (void const *)__src, (__SIZE_TYPE__)__num_chars); }
#endif /* !... */
#endif /* !... */
#if defined(__CRT_HAVE_wmemcmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wmemcmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16memcmp,(char16_t const *__s1, char16_t const *__s2, size_t __num_chars),wmemcmp,(__s1,__s2,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmemcmp)
/* >> wmemcmp(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16memcmp,(char16_t const *__s1, char16_t const *__s2, size_t __num_chars),wmemcmp,(__s1,__s2,__num_chars))
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE_memcmpw) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wmemcmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16memcmp,(char16_t const *__s1, char16_t const *__s2, size_t __num_chars),memcmpw,(__s1,__s2,__num_chars))
#elif defined(__CRT_HAVE_DOS$memcmpw)
/* >> wmemcmp(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16memcmp,(char16_t const *__s1, char16_t const *__s2, size_t __num_chars),memcmpw,(__s1,__s2,__num_chars))
#else /* ... */
#include <libc/local/string/memcmpw.h>
/* >> wmemcmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16memcmp)(char16_t const *__s1, char16_t const *__s2, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpw))((void const *)__s1, (void const *)__s2, (__SIZE_TYPE__)__num_chars); }
#endif /* !... */
#endif /* !... */
#if defined(__CRT_HAVE_wmemcmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wmemcmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32memcmp,(char32_t const *__s1, char32_t const *__s2, size_t __num_chars),wmemcmp,(__s1,__s2,__num_chars))
#elif defined(__CRT_HAVE_KOS$wmemcmp)
/* >> wmemcmp(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32memcmp,(char32_t const *__s1, char32_t const *__s2, size_t __num_chars),wmemcmp,(__s1,__s2,__num_chars))
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE_memcmpl) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wmemcmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32memcmp,(char32_t const *__s1, char32_t const *__s2, size_t __num_chars),memcmpl,(__s1,__s2,__num_chars))
#elif defined(__CRT_HAVE_KOS$memcmpl)
/* >> wmemcmp(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32memcmp,(char32_t const *__s1, char32_t const *__s2, size_t __num_chars),memcmpl,(__s1,__s2,__num_chars))
#else /* ... */
#include <libc/local/string/memcmpl.h>
/* >> wmemcmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32memcmp)(char32_t const *__s1, char32_t const *__s2, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpl))((void const *)__s1, (void const *)__s2, (__SIZE_TYPE__)__num_chars); }
#endif /* !... */
#endif /* !... */
#if defined(__CRT_HAVE_wmemmove) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wmemmove(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char16_t *,__NOTHROW_NCX,c16memmove,(char16_t *__dst, char16_t const *__src, size_t __num_chars),wmemmove,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmemmove)
/* >> wmemmove(3) */
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char16_t *,__NOTHROW_NCX,c16memmove,(char16_t *__dst, char16_t const *__src, size_t __num_chars),wmemmove,(__dst,__src,__num_chars))
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE_memmovew) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wmemmove(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char16_t *,__NOTHROW_NCX,c16memmove,(char16_t *__dst, char16_t const *__src, size_t __num_chars),memmovew,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$memmovew)
/* >> wmemmove(3) */
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char16_t *,__NOTHROW_NCX,c16memmove,(char16_t *__dst, char16_t const *__src, size_t __num_chars),memmovew,(__dst,__src,__num_chars))
#else /* ... */
#include <libc/local/string/memmovew.h>
/* >> wmemmove(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) char16_t *__NOTHROW_NCX(__LIBDCALL c16memmove)(char16_t *__dst, char16_t const *__src, size_t __num_chars) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovew))((void *)__dst, (void const *)__src, (__SIZE_TYPE__)__num_chars); }
#endif /* !... */
#endif /* !... */
#if defined(__CRT_HAVE_wmemmove) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wmemmove(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char32_t *,__NOTHROW_NCX,c32memmove,(char32_t *__dst, char32_t const *__src, size_t __num_chars),wmemmove,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_KOS$wmemmove)
/* >> wmemmove(3) */
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char32_t *,__NOTHROW_NCX,c32memmove,(char32_t *__dst, char32_t const *__src, size_t __num_chars),wmemmove,(__dst,__src,__num_chars))
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE_memmovel) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wmemmove(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char32_t *,__NOTHROW_NCX,c32memmove,(char32_t *__dst, char32_t const *__src, size_t __num_chars),memmovel,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_KOS$memmovel)
/* >> wmemmove(3) */
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char32_t *,__NOTHROW_NCX,c32memmove,(char32_t *__dst, char32_t const *__src, size_t __num_chars),memmovel,(__dst,__src,__num_chars))
#else /* ... */
#include <libc/local/string/memmovel.h>
/* >> wmemmove(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) char32_t *__NOTHROW_NCX(__LIBKCALL c32memmove)(char32_t *__dst, char32_t const *__src, size_t __num_chars) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovel))((void *)__dst, (void const *)__src, (__SIZE_TYPE__)__num_chars); }
#endif /* !... */
#endif /* !... */
#if defined(__CRT_HAVE_wmemset) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wmemset(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_OUTS(1, 3),char16_t *,__NOTHROW_NCX,c16memset,(char16_t *__dst, char16_t __filler, size_t __num_chars),wmemset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmemset)
/* >> wmemset(3) */
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_OUTS(1, 3),char16_t *,__NOTHROW_NCX,c16memset,(char16_t *__dst, char16_t __filler, size_t __num_chars),wmemset,(__dst,__filler,__num_chars))
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE_memsetw) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wmemset(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_OUTS(1, 3),char16_t *,__NOTHROW_NCX,c16memset,(char16_t *__dst, char16_t __filler, size_t __num_chars),memsetw,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_DOS$memsetw)
/* >> wmemset(3) */
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_OUTS(1, 3),char16_t *,__NOTHROW_NCX,c16memset,(char16_t *__dst, char16_t __filler, size_t __num_chars),memsetw,(__dst,__filler,__num_chars))
#else /* ... */
#include <libc/local/string/memsetw.h>
/* >> wmemset(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_OUTS(1, 3) char16_t *__NOTHROW_NCX(__LIBDCALL c16memset)(char16_t *__dst, char16_t __filler, size_t __num_chars) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memsetw))((void *)__dst, (__UINT16_TYPE__)__filler, (__SIZE_TYPE__)__num_chars); }
#endif /* !... */
#endif /* !... */
#if defined(__CRT_HAVE_wmemset) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wmemset(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_OUTS(1, 3),char32_t *,__NOTHROW_NCX,c32memset,(char32_t *__dst, char32_t __filler, size_t __num_chars),wmemset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_KOS$wmemset)
/* >> wmemset(3) */
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_OUTS(1, 3),char32_t *,__NOTHROW_NCX,c32memset,(char32_t *__dst, char32_t __filler, size_t __num_chars),wmemset,(__dst,__filler,__num_chars))
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE_memsetl) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wmemset(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_OUTS(1, 3),char32_t *,__NOTHROW_NCX,c32memset,(char32_t *__dst, char32_t __filler, size_t __num_chars),memsetl,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_KOS$memsetl)
/* >> wmemset(3) */
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_OUTS(1, 3),char32_t *,__NOTHROW_NCX,c32memset,(char32_t *__dst, char32_t __filler, size_t __num_chars),memsetl,(__dst,__filler,__num_chars))
#else /* ... */
#include <libc/local/string/memsetl.h>
/* >> wmemset(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_OUTS(1, 3) char32_t *__NOTHROW_NCX(__LIBKCALL c32memset)(char32_t *__dst, char32_t __filler, size_t __num_chars) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memsetl))((void *)__dst, (__UINT32_TYPE__)__filler, (__SIZE_TYPE__)__num_chars); }
#endif /* !... */
#endif /* !... */
#if defined(__CRT_HAVE_wmempcpy) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wmempcpy(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char16_t *,__NOTHROW_NCX,c16mempcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, __SIZE_TYPE__ __num_chars),wmempcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmempcpy)
/* >> wmempcpy(3) */
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char16_t *,__NOTHROW_NCX,c16mempcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, __SIZE_TYPE__ __num_chars),wmempcpy,(__dst,__src,__num_chars))
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE_mempcpyw) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wmempcpy(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char16_t *,__NOTHROW_NCX,c16mempcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, __SIZE_TYPE__ __num_chars),mempcpyw,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$mempcpyw)
/* >> wmempcpy(3) */
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char16_t *,__NOTHROW_NCX,c16mempcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, __SIZE_TYPE__ __num_chars),mempcpyw,(__dst,__src,__num_chars))
#else /* ... */
#include <libc/local/string/mempcpyw.h>
/* >> wmempcpy(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) char16_t *__NOTHROW_NCX(__LIBDCALL c16mempcpy)(char16_t *__restrict __dst, char16_t const *__restrict __src, __SIZE_TYPE__ __num_chars) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyw))((void *)__dst, (void const *)__src, __num_chars); }
#endif /* !... */
#endif /* !... */
#if defined(__CRT_HAVE_wmempcpy) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wmempcpy(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char32_t *,__NOTHROW_NCX,c32mempcpy,(char32_t *__restrict __dst, char32_t const *__restrict __src, __SIZE_TYPE__ __num_chars),wmempcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_KOS$wmempcpy)
/* >> wmempcpy(3) */
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char32_t *,__NOTHROW_NCX,c32mempcpy,(char32_t *__restrict __dst, char32_t const *__restrict __src, __SIZE_TYPE__ __num_chars),wmempcpy,(__dst,__src,__num_chars))
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE_mempcpyl) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wmempcpy(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char32_t *,__NOTHROW_NCX,c32mempcpy,(char32_t *__restrict __dst, char32_t const *__restrict __src, __SIZE_TYPE__ __num_chars),mempcpyl,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_KOS$mempcpyl)
/* >> wmempcpy(3) */
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char32_t *,__NOTHROW_NCX,c32mempcpy,(char32_t *__restrict __dst, char32_t const *__restrict __src, __SIZE_TYPE__ __num_chars),mempcpyl,(__dst,__src,__num_chars))
#else /* ... */
#include <libc/local/string/mempcpyl.h>
/* >> wmempcpy(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) char32_t *__NOTHROW_NCX(__LIBKCALL c32mempcpy)(char32_t *__restrict __dst, char32_t const *__restrict __src, __SIZE_TYPE__ __num_chars) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyl))((void *)__dst, (void const *)__src, __num_chars); }
#endif /* !... */
#endif /* !... */
#if defined(__CRT_HAVE_wmempmove) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wmempmove(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char16_t *,__NOTHROW_NCX,c16mempmove,(char16_t *__dst, char16_t const *__src, __SIZE_TYPE__ __num_chars),wmempmove,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmempmove)
/* >> wmempmove(3) */
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char16_t *,__NOTHROW_NCX,c16mempmove,(char16_t *__dst, char16_t const *__src, __SIZE_TYPE__ __num_chars),wmempmove,(__dst,__src,__num_chars))
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE_mempmovew) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wmempmove(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char16_t *,__NOTHROW_NCX,c16mempmove,(char16_t *__dst, char16_t const *__src, __SIZE_TYPE__ __num_chars),mempmovew,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$mempmovew)
/* >> wmempmove(3) */
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char16_t *,__NOTHROW_NCX,c16mempmove,(char16_t *__dst, char16_t const *__src, __SIZE_TYPE__ __num_chars),mempmovew,(__dst,__src,__num_chars))
#else /* ... */
#include <libc/local/string/mempmovew.h>
/* >> wmempmove(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) char16_t *__NOTHROW_NCX(__LIBDCALL c16mempmove)(char16_t *__dst, char16_t const *__src, __SIZE_TYPE__ __num_chars) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovew))((void *)__dst, (void const *)__src, __num_chars); }
#endif /* !... */
#endif /* !... */
#if defined(__CRT_HAVE_wmempmove) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wmempmove(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char32_t *,__NOTHROW_NCX,c32mempmove,(char32_t *__dst, char32_t const *__src, __SIZE_TYPE__ __num_chars),wmempmove,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_KOS$wmempmove)
/* >> wmempmove(3) */
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char32_t *,__NOTHROW_NCX,c32mempmove,(char32_t *__dst, char32_t const *__src, __SIZE_TYPE__ __num_chars),wmempmove,(__dst,__src,__num_chars))
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE_mempmovel) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wmempmove(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char32_t *,__NOTHROW_NCX,c32mempmove,(char32_t *__dst, char32_t const *__src, __SIZE_TYPE__ __num_chars),mempmovel,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_KOS$mempmovel)
/* >> wmempmove(3) */
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char32_t *,__NOTHROW_NCX,c32mempmove,(char32_t *__dst, char32_t const *__src, __SIZE_TYPE__ __num_chars),mempmovel,(__dst,__src,__num_chars))
#else /* ... */
#include <libc/local/string/mempmovel.h>
/* >> wmempmove(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) char32_t *__NOTHROW_NCX(__LIBKCALL c32mempmove)(char32_t *__dst, char32_t const *__src, __SIZE_TYPE__ __num_chars) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovel))((void *)__dst, (void const *)__src, __num_chars); }
#endif /* !... */
#endif /* !... */
#if defined(__CRT_HAVE_wmempset) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wmempset(3)
 * Same as wmemset, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16mempset,(char16_t *__dst, char16_t __filler, __SIZE_TYPE__ __num_chars),wmempset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmempset)
/* >> wmempset(3)
 * Same as wmemset, but return a pointer after the last written character */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16mempset,(char16_t *__dst, char16_t __filler, __SIZE_TYPE__ __num_chars),wmempset,(__dst,__filler,__num_chars))
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE_mempsetw) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wmempset(3)
 * Same as wmemset, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16mempset,(char16_t *__dst, char16_t __filler, __SIZE_TYPE__ __num_chars),mempsetw,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_DOS$mempsetw)
/* >> wmempset(3)
 * Same as wmemset, but return a pointer after the last written character */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16mempset,(char16_t *__dst, char16_t __filler, __SIZE_TYPE__ __num_chars),mempsetw,(__dst,__filler,__num_chars))
#else /* ... */
#include <libc/local/string/mempsetw.h>
/* >> wmempset(3)
 * Same as wmemset, but return a pointer after the last written character */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16mempset)(char16_t *__dst, char16_t __filler, __SIZE_TYPE__ __num_chars) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempsetw))((void *)__dst, (__UINT16_TYPE__)__filler, __num_chars); }
#endif /* !... */
#endif /* !... */
#if defined(__CRT_HAVE_wmempset) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wmempset(3)
 * Same as wmemset, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32mempset,(char32_t *__dst, char32_t __filler, __SIZE_TYPE__ __num_chars),wmempset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_KOS$wmempset)
/* >> wmempset(3)
 * Same as wmemset, but return a pointer after the last written character */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32mempset,(char32_t *__dst, char32_t __filler, __SIZE_TYPE__ __num_chars),wmempset,(__dst,__filler,__num_chars))
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE_mempsetl) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wmempset(3)
 * Same as wmemset, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32mempset,(char32_t *__dst, char32_t __filler, __SIZE_TYPE__ __num_chars),mempsetl,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_KOS$mempsetl)
/* >> wmempset(3)
 * Same as wmemset, but return a pointer after the last written character */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32mempset,(char32_t *__dst, char32_t __filler, __SIZE_TYPE__ __num_chars),mempsetl,(__dst,__filler,__num_chars))
#else /* ... */
#include <libc/local/string/mempsetl.h>
/* >> wmempset(3)
 * Same as wmemset, but return a pointer after the last written character */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32mempset)(char32_t *__dst, char32_t __filler, __SIZE_TYPE__ __num_chars) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempsetl))((void *)__dst, (__UINT32_TYPE__)__filler, __num_chars); }
#endif /* !... */
#endif /* !... */
#if defined(__CRT_HAVE_wcsend) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16end,(char16_t *__restrict __str),wcsend,(__str))
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char16_t const *,__NOTHROW_NCX,c16end,(char16_t const *__restrict __str),wcsend,(__str))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16end,(char16_t const *__restrict __str),wcsend,(__str))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsend)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16end,(char16_t *__restrict __str),wcsend,(__str))
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char16_t const *,__NOTHROW_NCX,c16end,(char16_t const *__restrict __str),wcsend,(__str))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16end,(char16_t const *__restrict __str),wcsend,(__str))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16end)(char16_t *__restrict __str) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))((__WCHAR_TYPE__ const *)__str); }
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char16_t const *__NOTHROW_NCX(__LIBDCALL c16end)(char16_t const *__restrict __str) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))((__WCHAR_TYPE__ const *)__str); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16end)(char16_t const *__restrict __str) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))((__WCHAR_TYPE__ const *)__str); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c16end.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16end)(char16_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16end))(__str); }
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char16_t const *__NOTHROW_NCX(__LIBDCALL c16end)(char16_t const *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16end))(__str); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16end, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16end)(char16_t const *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16end))(__str); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsend) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32end,(char32_t *__restrict __str),wcsend,(__str))
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char32_t const *,__NOTHROW_NCX,c32end,(char32_t const *__restrict __str),wcsend,(__str))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32end,(char32_t const *__restrict __str),wcsend,(__str))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_KOS$wcsend)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32end,(char32_t *__restrict __str),wcsend,(__str))
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char32_t const *,__NOTHROW_NCX,c32end,(char32_t const *__restrict __str),wcsend,(__str))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32end,(char32_t const *__restrict __str),wcsend,(__str))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32end)(char32_t *__restrict __str) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))((__WCHAR_TYPE__ const *)__str); }
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char32_t const *__NOTHROW_NCX(__LIBKCALL c32end)(char32_t const *__restrict __str) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))((__WCHAR_TYPE__ const *)__str); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32end)(char32_t const *__restrict __str) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))((__WCHAR_TYPE__ const *)__str); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c32end.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32end)(char32_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32end))(__str); }
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char32_t const *__NOTHROW_NCX(__LIBKCALL c32end)(char32_t const *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32end))(__str); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32end, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32end)(char32_t const *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32end))(__str); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsnend) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nend,(char16_t *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnend,(__str,__maxlen))
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16nend,(char16_t const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnend,(__str,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nend,(char16_t const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnend,(__str,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsnend)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nend,(char16_t *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnend,(__str,__maxlen))
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16nend,(char16_t const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnend,(__str,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nend,(char16_t const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnend,(__str,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsnend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nend)(char16_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))((__WCHAR_TYPE__ const *)__str, __maxlen); }
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16nend)(char16_t const *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))((__WCHAR_TYPE__ const *)__str, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nend)(char16_t const *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))((__WCHAR_TYPE__ const *)__str, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c16nend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nend)(char16_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nend))(__str, __maxlen); }
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16nend)(char16_t const *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nend))(__str, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16nend, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nend)(char16_t const *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nend))(__str, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsnend) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nend,(char32_t *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnend,(__str,__maxlen))
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32nend,(char32_t const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnend,(__str,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nend,(char32_t const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnend,(__str,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_KOS$wcsnend)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nend,(char32_t *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnend,(__str,__maxlen))
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32nend,(char32_t const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnend,(__str,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nend,(char32_t const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnend,(__str,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsnend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nend)(char32_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))((__WCHAR_TYPE__ const *)__str, __maxlen); }
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32nend)(char32_t const *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))((__WCHAR_TYPE__ const *)__str, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nend)(char32_t const *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))((__WCHAR_TYPE__ const *)__str, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c32nend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nend)(char32_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nend))(__str, __maxlen); }
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32nend)(char32_t const *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nend))(__str, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32nend, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nend)(char32_t const *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nend))(__str, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcslen) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcslen(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),size_t,__NOTHROW_NCX,c16len,(char16_t const *__restrict __str),wcslen,(__str))
#elif defined(__CRT_HAVE_DOS$wcslen)
/* >> wcslen(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),size_t,__NOTHROW_NCX,c16len,(char16_t const *__restrict __str),wcslen,(__str))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcslen.h>
/* >> wcslen(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) size_t __NOTHROW_NCX(__LIBDCALL c16len)(char16_t const *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslen))((__WCHAR_TYPE__ const *)__str); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16len.h>
/* >> wcslen(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16len, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) size_t __NOTHROW_NCX(__LIBDCALL c16len)(char16_t const *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16len))(__str); })
#endif /* !... */
#if defined(__CRT_HAVE_wcslen) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcslen(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),size_t,__NOTHROW_NCX,c32len,(char32_t const *__restrict __str),wcslen,(__str))
#elif defined(__CRT_HAVE_KOS$wcslen)
/* >> wcslen(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),size_t,__NOTHROW_NCX,c32len,(char32_t const *__restrict __str),wcslen,(__str))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcslen.h>
/* >> wcslen(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) size_t __NOTHROW_NCX(__LIBKCALL c32len)(char32_t const *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslen))((__WCHAR_TYPE__ const *)__str); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32len.h>
/* >> wcslen(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32len, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) size_t __NOTHROW_NCX(__LIBKCALL c32len)(char32_t const *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32len))(__str); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnlen) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsnlen(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16nlen,(char16_t const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnlen,(__str,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnlen)
/* >> wcsnlen(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16nlen,(char16_t const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnlen,(__str,__maxlen))
#elif defined(__CRT_HAVE___wcsncnt) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsnlen(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16nlen,(char16_t const *__restrict __str, __SIZE_TYPE__ __maxlen),__wcsncnt,(__str,__maxlen))
#elif defined(__CRT_HAVE_DOS$__wcsncnt)
/* >> wcsnlen(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16nlen,(char16_t const *__restrict __str, __SIZE_TYPE__ __maxlen),__wcsncnt,(__str,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsnlen.h>
/* >> wcsnlen(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16nlen)(char16_t const *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlen))((__WCHAR_TYPE__ const *)__str, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16nlen.h>
/* >> wcsnlen(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16nlen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16nlen)(char16_t const *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nlen))(__str, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnlen) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsnlen(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c32nlen,(char32_t const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnlen,(__str,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsnlen)
/* >> wcsnlen(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c32nlen,(char32_t const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnlen,(__str,__maxlen))
#elif defined(__CRT_HAVE___wcsncnt) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsnlen(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c32nlen,(char32_t const *__restrict __str, __SIZE_TYPE__ __maxlen),__wcsncnt,(__str,__maxlen))
#elif defined(__CRT_HAVE_KOS$__wcsncnt)
/* >> wcsnlen(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c32nlen,(char32_t const *__restrict __str, __SIZE_TYPE__ __maxlen),__wcsncnt,(__str,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsnlen.h>
/* >> wcsnlen(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32nlen)(char32_t const *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlen))((__WCHAR_TYPE__ const *)__str, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32nlen.h>
/* >> wcsnlen(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32nlen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32nlen)(char32_t const *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nlen))(__str, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcscmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16cmp,(char16_t const *__s1, char16_t const *__s2),wcscmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscmp)
/* >> wcscmp(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16cmp,(char16_t const *__s1, char16_t const *__s2),wcscmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcscmp.h>
/* >> wcscmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBDCALL c16cmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16cmp.h>
/* >> wcscmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16cmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBDCALL c16cmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16cmp))(__s1, __s2); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcscmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32cmp,(char32_t const *__s1, char32_t const *__s2),wcscmp,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$wcscmp)
/* >> wcscmp(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32cmp,(char32_t const *__s1, char32_t const *__s2),wcscmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcscmp.h>
/* >> wcscmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBKCALL c32cmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32cmp.h>
/* >> wcscmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32cmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBKCALL c32cmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32cmp))(__s1, __s2); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsncmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncmp,(char16_t const *__s1, char16_t const *__s2, size_t __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsncmp)
/* >> wcsncmp(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncmp,(char16_t const *__s1, char16_t const *__s2, size_t __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsncmp.h>
/* >> wcsncmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16ncmp)(char16_t const *__s1, char16_t const *__s2, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16ncmp.h>
/* >> wcsncmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ncmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16ncmp)(char16_t const *__s1, char16_t const *__s2, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ncmp))(__s1, __s2, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsncmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncmp,(char32_t const *__s1, char32_t const *__s2, size_t __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsncmp)
/* >> wcsncmp(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncmp,(char32_t const *__s1, char32_t const *__s2, size_t __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsncmp.h>
/* >> wcsncmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32ncmp)(char32_t const *__s1, char32_t const *__s2, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32ncmp.h>
/* >> wcsncmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ncmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32ncmp)(char32_t const *__s1, char32_t const *__s2, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ncmp))(__s1, __s2, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcschr) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcschr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16chr,(char16_t *__restrict __haystack, char16_t __needle),wcschr,(__haystack,__needle))
/* >> wcschr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char16_t const *,__NOTHROW_NCX,c16chr,(char16_t const *__restrict __haystack, char16_t __needle),wcschr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcschr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16chr,(char16_t const *__restrict __haystack, char16_t __needle),wcschr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcschr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcschr(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16chr,(char16_t *__restrict __haystack, char16_t __needle),wcschr,(__haystack,__needle))
/* >> wcschr(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char16_t const *,__NOTHROW_NCX,c16chr,(char16_t const *__restrict __haystack, char16_t __needle),wcschr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcschr(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16chr,(char16_t const *__restrict __haystack, char16_t __needle),wcschr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcschr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcschr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16chr)(char16_t *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* >> wcschr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char16_t const *__NOTHROW_NCX(__LIBDCALL c16chr)(char16_t const *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcschr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16chr)(char16_t const *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c16chr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcschr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16chr)(char16_t *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16chr))(__haystack, __needle); }
/* >> wcschr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char16_t const *__NOTHROW_NCX(__LIBDCALL c16chr)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16chr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcschr(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16chr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16chr)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16chr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcschr) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcschr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32chr,(char32_t *__restrict __haystack, char32_t __needle),wcschr,(__haystack,__needle))
/* >> wcschr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char32_t const *,__NOTHROW_NCX,c32chr,(char32_t const *__restrict __haystack, char32_t __needle),wcschr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcschr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32chr,(char32_t const *__restrict __haystack, char32_t __needle),wcschr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_KOS$wcschr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcschr(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32chr,(char32_t *__restrict __haystack, char32_t __needle),wcschr,(__haystack,__needle))
/* >> wcschr(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char32_t const *,__NOTHROW_NCX,c32chr,(char32_t const *__restrict __haystack, char32_t __needle),wcschr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcschr(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32chr,(char32_t const *__restrict __haystack, char32_t __needle),wcschr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcschr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcschr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32chr)(char32_t *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* >> wcschr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char32_t const *__NOTHROW_NCX(__LIBKCALL c32chr)(char32_t const *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcschr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32chr)(char32_t const *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c32chr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcschr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32chr)(char32_t *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32chr))(__haystack, __needle); }
/* >> wcschr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char32_t const *__NOTHROW_NCX(__LIBKCALL c32chr)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32chr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcschr(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32chr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32chr)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32chr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsrchr) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsrchr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16rchr,(char16_t *__restrict __haystack, char16_t __needle),wcsrchr,(__haystack,__needle))
/* >> wcsrchr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char16_t const *,__NOTHROW_NCX,c16rchr,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsrchr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16rchr,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsrchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsrchr(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16rchr,(char16_t *__restrict __haystack, char16_t __needle),wcsrchr,(__haystack,__needle))
/* >> wcsrchr(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char16_t const *,__NOTHROW_NCX,c16rchr,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsrchr(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16rchr,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsrchr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16rchr)(char16_t *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* >> wcsrchr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char16_t const *__NOTHROW_NCX(__LIBDCALL c16rchr)(char16_t const *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsrchr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16rchr)(char16_t const *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c16rchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsrchr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16rchr)(char16_t *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rchr))(__haystack, __needle); }
/* >> wcsrchr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char16_t const *__NOTHROW_NCX(__LIBDCALL c16rchr)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rchr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsrchr(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16rchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16rchr)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rchr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsrchr) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsrchr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32rchr,(char32_t *__restrict __haystack, char32_t __needle),wcsrchr,(__haystack,__needle))
/* >> wcsrchr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char32_t const *,__NOTHROW_NCX,c32rchr,(char32_t const *__restrict __haystack, char32_t __needle),wcsrchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsrchr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32rchr,(char32_t const *__restrict __haystack, char32_t __needle),wcsrchr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_KOS$wcsrchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsrchr(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32rchr,(char32_t *__restrict __haystack, char32_t __needle),wcsrchr,(__haystack,__needle))
/* >> wcsrchr(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char32_t const *,__NOTHROW_NCX,c32rchr,(char32_t const *__restrict __haystack, char32_t __needle),wcsrchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsrchr(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32rchr,(char32_t const *__restrict __haystack, char32_t __needle),wcsrchr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsrchr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32rchr)(char32_t *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* >> wcsrchr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char32_t const *__NOTHROW_NCX(__LIBKCALL c32rchr)(char32_t const *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsrchr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32rchr)(char32_t const *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c32rchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsrchr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32rchr)(char32_t *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32rchr))(__haystack, __needle); }
/* >> wcsrchr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char32_t const *__NOTHROW_NCX(__LIBKCALL c32rchr)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32rchr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsrchr(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32rchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32rchr)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32rchr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsnchr) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nchr,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16nchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsnchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nchr,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16nchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsnchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nchr)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16nchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c16nchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nchr)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nchr))(__haystack, __needle, __maxlen); }
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16nchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nchr))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16nchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nchr))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsnchr) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nchr,(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32nchr,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nchr,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_KOS$wcsnchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nchr,(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32nchr,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nchr,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsnchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nchr)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32nchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c32nchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nchr)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nchr))(__haystack, __needle, __maxlen); }
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32nchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nchr))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32nchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nchr))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsnrchr) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nrchr,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16nrchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nrchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsnrchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nrchr,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16nrchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nrchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsnrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nrchr)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16nrchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nrchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c16nrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nrchr)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nrchr))(__haystack, __needle, __maxlen); }
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16nrchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nrchr))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16nrchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nrchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nrchr))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsnrchr) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nrchr,(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32nrchr,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nrchr,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_KOS$wcsnrchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nrchr,(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32nrchr,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nrchr,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsnrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nrchr)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32nrchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nrchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c32nrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nrchr)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nrchr))(__haystack, __needle, __maxlen); }
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32nrchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nrchr))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32nrchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nrchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nrchr))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcschrnul) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16chrnul,(char16_t *__restrict __haystack, char16_t __needle),wcschrnul,(__haystack,__needle))
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char16_t const *,__NOTHROW_NCX,c16chrnul,(char16_t const *__restrict __haystack, char16_t __needle),wcschrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16chrnul,(char16_t const *__haystack, char16_t __needle),wcschrnul,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcschrnul)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16chrnul,(char16_t *__restrict __haystack, char16_t __needle),wcschrnul,(__haystack,__needle))
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char16_t const *,__NOTHROW_NCX,c16chrnul,(char16_t const *__restrict __haystack, char16_t __needle),wcschrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16chrnul,(char16_t const *__haystack, char16_t __needle),wcschrnul,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcschrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16chrnul)(char16_t *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char16_t const *__NOTHROW_NCX(__LIBDCALL c16chrnul)(char16_t const *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16chrnul)(char16_t const *__haystack, char16_t __needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c16chrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16chrnul)(char16_t *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16chrnul))(__haystack, __needle); }
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char16_t const *__NOTHROW_NCX(__LIBDCALL c16chrnul)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16chrnul))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16chrnul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16chrnul)(char16_t const *__haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16chrnul))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcschrnul) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32chrnul,(char32_t *__restrict __haystack, char32_t __needle),wcschrnul,(__haystack,__needle))
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char32_t const *,__NOTHROW_NCX,c32chrnul,(char32_t const *__restrict __haystack, char32_t __needle),wcschrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32chrnul,(char32_t const *__haystack, char32_t __needle),wcschrnul,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_KOS$wcschrnul)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32chrnul,(char32_t *__restrict __haystack, char32_t __needle),wcschrnul,(__haystack,__needle))
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char32_t const *,__NOTHROW_NCX,c32chrnul,(char32_t const *__restrict __haystack, char32_t __needle),wcschrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32chrnul,(char32_t const *__haystack, char32_t __needle),wcschrnul,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcschrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32chrnul)(char32_t *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char32_t const *__NOTHROW_NCX(__LIBKCALL c32chrnul)(char32_t const *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32chrnul)(char32_t const *__haystack, char32_t __needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c32chrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32chrnul)(char32_t *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32chrnul))(__haystack, __needle); }
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char32_t const *__NOTHROW_NCX(__LIBKCALL c32chrnul)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32chrnul))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32chrnul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32chrnul)(char32_t const *__haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32chrnul))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsrchrnul) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16rchrnul,(char16_t *__restrict __haystack, char16_t __needle),wcsrchrnul,(__haystack,__needle))
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char16_t const *,__NOTHROW_NCX,c16rchrnul,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16rchrnul,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchrnul,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsrchrnul)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16rchrnul,(char16_t *__restrict __haystack, char16_t __needle),wcsrchrnul,(__haystack,__needle))
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char16_t const *,__NOTHROW_NCX,c16rchrnul,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16rchrnul,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchrnul,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsrchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16rchrnul)(char16_t *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char16_t const *__NOTHROW_NCX(__LIBDCALL c16rchrnul)(char16_t const *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16rchrnul)(char16_t const *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c16rchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16rchrnul)(char16_t *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rchrnul))(__haystack, __needle); }
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char16_t const *__NOTHROW_NCX(__LIBDCALL c16rchrnul)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rchrnul))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16rchrnul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16rchrnul)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rchrnul))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsrchrnul) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32rchrnul,(char32_t *__restrict __haystack, char32_t __needle),wcsrchrnul,(__haystack,__needle))
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char32_t const *,__NOTHROW_NCX,c32rchrnul,(char32_t const *__restrict __haystack, char32_t __needle),wcsrchrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32rchrnul,(char32_t const *__restrict __haystack, char32_t __needle),wcsrchrnul,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_KOS$wcsrchrnul)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32rchrnul,(char32_t *__restrict __haystack, char32_t __needle),wcsrchrnul,(__haystack,__needle))
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char32_t const *,__NOTHROW_NCX,c32rchrnul,(char32_t const *__restrict __haystack, char32_t __needle),wcsrchrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32rchrnul,(char32_t const *__restrict __haystack, char32_t __needle),wcsrchrnul,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsrchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32rchrnul)(char32_t *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char32_t const *__NOTHROW_NCX(__LIBKCALL c32rchrnul)(char32_t const *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32rchrnul)(char32_t const *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c32rchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32rchrnul)(char32_t *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32rchrnul))(__haystack, __needle); }
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char32_t const *__NOTHROW_NCX(__LIBKCALL c32rchrnul)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32rchrnul))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32rchrnul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32rchrnul)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32rchrnul))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsnchrnul) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nchrnul,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16nchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsnchrnul)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nchrnul,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16nchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsnchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nchrnul)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16nchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c16nchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nchrnul)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nchrnul))(__haystack, __needle, __maxlen); }
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16nchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nchrnul))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16nchrnul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nchrnul))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsnchrnul) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nchrnul,(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32nchrnul,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nchrnul,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_KOS$wcsnchrnul)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nchrnul,(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32nchrnul,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nchrnul,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsnchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nchrnul)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32nchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c32nchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nchrnul)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nchrnul))(__haystack, __needle, __maxlen); }
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32nchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nchrnul))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32nchrnul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nchrnul))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsnrchrnul) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nrchrnul,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16nrchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nrchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsnrchrnul)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nrchrnul,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16nrchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nrchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsnrchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nrchrnul)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16nrchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nrchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c16nrchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nrchrnul)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nrchrnul))(__haystack, __needle, __maxlen); }
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16nrchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nrchrnul))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16nrchrnul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nrchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nrchrnul))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsnrchrnul) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nrchrnul,(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32nrchrnul,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nrchrnul,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_KOS$wcsnrchrnul)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nrchrnul,(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32nrchrnul,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nrchrnul,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsnrchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nrchrnul)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32nrchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nrchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c32nrchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nrchrnul)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nrchrnul))(__haystack, __needle, __maxlen); }
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32nrchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nrchrnul))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32nrchrnul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nrchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nrchrnul))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsoff) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsoff(3)
 * Same as `wcschrnul', but return the offset from `str', rather than the actual address */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,c16off,(char16_t const *__restrict __haystack, char16_t __needle),wcsoff,(__haystack,__needle))
#elif defined(__CRT_HAVE_DOS$wcsoff)
/* >> wcsoff(3)
 * Same as `wcschrnul', but return the offset from `str', rather than the actual address */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,c16off,(char16_t const *__restrict __haystack, char16_t __needle),wcsoff,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsoff.h>
/* >> wcsoff(3)
 * Same as `wcschrnul', but return the offset from `str', rather than the actual address */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16off)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsoff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16off.h>
/* >> wcsoff(3)
 * Same as `wcschrnul', but return the offset from `str', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16off, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16off)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16off))(__haystack, __needle); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsoff) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsoff(3)
 * Same as `wcschrnul', but return the offset from `str', rather than the actual address */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,c32off,(char32_t const *__restrict __haystack, char32_t __needle),wcsoff,(__haystack,__needle))
#elif defined(__CRT_HAVE_KOS$wcsoff)
/* >> wcsoff(3)
 * Same as `wcschrnul', but return the offset from `str', rather than the actual address */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,c32off,(char32_t const *__restrict __haystack, char32_t __needle),wcsoff,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsoff.h>
/* >> wcsoff(3)
 * Same as `wcschrnul', but return the offset from `str', rather than the actual address */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32off)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsoff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32off.h>
/* >> wcsoff(3)
 * Same as `wcschrnul', but return the offset from `str', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32off, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32off)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32off))(__haystack, __needle); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsroff) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsroff(3)
 * Same as `wcsrchrnul', but return the offset from `str', rather than the actual address */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,c16roff,(char16_t const *__restrict __haystack, char16_t __needle),wcsroff,(__haystack,__needle))
#elif defined(__CRT_HAVE_DOS$wcsroff)
/* >> wcsroff(3)
 * Same as `wcsrchrnul', but return the offset from `str', rather than the actual address */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,c16roff,(char16_t const *__restrict __haystack, char16_t __needle),wcsroff,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsroff.h>
/* >> wcsroff(3)
 * Same as `wcsrchrnul', but return the offset from `str', rather than the actual address */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16roff)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsroff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16roff.h>
/* >> wcsroff(3)
 * Same as `wcsrchrnul', but return the offset from `str', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16roff, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16roff)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16roff))(__haystack, __needle); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsroff) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsroff(3)
 * Same as `wcsrchrnul', but return the offset from `str', rather than the actual address */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,c32roff,(char32_t const *__restrict __haystack, char32_t __needle),wcsroff,(__haystack,__needle))
#elif defined(__CRT_HAVE_KOS$wcsroff)
/* >> wcsroff(3)
 * Same as `wcsrchrnul', but return the offset from `str', rather than the actual address */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,c32roff,(char32_t const *__restrict __haystack, char32_t __needle),wcsroff,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsroff.h>
/* >> wcsroff(3)
 * Same as `wcsrchrnul', but return the offset from `str', rather than the actual address */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32roff)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsroff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32roff.h>
/* >> wcsroff(3)
 * Same as `wcsrchrnul', but return the offset from `str', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32roff, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32roff)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32roff))(__haystack, __needle); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnoff) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsnoff(3)
 * Same as `wcsnchrnul', but return the offset from `str', rather than the actual address */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,c16noff,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnoff,(__haystack,__needle,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnoff)
/* >> wcsnoff(3)
 * Same as `wcsnchrnul', but return the offset from `str', rather than the actual address */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,c16noff,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnoff,(__haystack,__needle,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsnoff.h>
/* >> wcsnoff(3)
 * Same as `wcsnchrnul', but return the offset from `str', rather than the actual address */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16noff)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnoff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16noff.h>
/* >> wcsnoff(3)
 * Same as `wcsnchrnul', but return the offset from `str', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16noff, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16noff)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16noff))(__haystack, __needle, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnoff) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsnoff(3)
 * Same as `wcsnchrnul', but return the offset from `str', rather than the actual address */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,c32noff,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnoff,(__haystack,__needle,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsnoff)
/* >> wcsnoff(3)
 * Same as `wcsnchrnul', but return the offset from `str', rather than the actual address */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,c32noff,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnoff,(__haystack,__needle,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsnoff.h>
/* >> wcsnoff(3)
 * Same as `wcsnchrnul', but return the offset from `str', rather than the actual address */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32noff)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnoff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32noff.h>
/* >> wcsnoff(3)
 * Same as `wcsnchrnul', but return the offset from `str', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32noff, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32noff)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32noff))(__haystack, __needle, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnroff) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsnroff(3)
 * Same as `wcsnrchrnul', but return the offset from `str', rather than the actual address */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,c16nroff,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnroff,(__haystack,__needle,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnroff)
/* >> wcsnroff(3)
 * Same as `wcsnrchrnul', but return the offset from `str', rather than the actual address */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,c16nroff,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnroff,(__haystack,__needle,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsnroff.h>
/* >> wcsnroff(3)
 * Same as `wcsnrchrnul', but return the offset from `str', rather than the actual address */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16nroff)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnroff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16nroff.h>
/* >> wcsnroff(3)
 * Same as `wcsnrchrnul', but return the offset from `str', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16nroff, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16nroff)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nroff))(__haystack, __needle, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnroff) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsnroff(3)
 * Same as `wcsnrchrnul', but return the offset from `str', rather than the actual address */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,c32nroff,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnroff,(__haystack,__needle,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsnroff)
/* >> wcsnroff(3)
 * Same as `wcsnrchrnul', but return the offset from `str', rather than the actual address */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,c32nroff,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnroff,(__haystack,__needle,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsnroff.h>
/* >> wcsnroff(3)
 * Same as `wcsnrchrnul', but return the offset from `str', rather than the actual address */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32nroff)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnroff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32nroff.h>
/* >> wcsnroff(3)
 * Same as `wcsnrchrnul', but return the offset from `str', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32nroff, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32nroff)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nroff))(__haystack, __needle, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsstr) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char16_t *,__NOTHROW_NCX,c16str,(char16_t *__haystack, char16_t *__needle),wcsstr,(__haystack,__needle))
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char16_t const *,__NOTHROW_NCX,c16str,(char16_t const *__haystack, char16_t const *__needle),wcsstr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char16_t *,__NOTHROW_NCX,c16str,(char16_t const *__haystack, char16_t const *__needle),wcsstr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsstr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsstr(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char16_t *,__NOTHROW_NCX,c16str,(char16_t *__haystack, char16_t *__needle),wcsstr,(__haystack,__needle))
/* >> wcsstr(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char16_t const *,__NOTHROW_NCX,c16str,(char16_t const *__haystack, char16_t const *__needle),wcsstr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsstr(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char16_t *,__NOTHROW_NCX,c16str,(char16_t const *__haystack, char16_t const *__needle),wcsstr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_wcswcs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char16_t *,__NOTHROW_NCX,c16str,(char16_t *__haystack, char16_t *__needle),wcswcs,(__haystack,__needle))
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char16_t const *,__NOTHROW_NCX,c16str,(char16_t const *__haystack, char16_t const *__needle),wcswcs,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char16_t *,__NOTHROW_NCX,c16str,(char16_t const *__haystack, char16_t const *__needle),wcswcs,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcswcs)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsstr(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char16_t *,__NOTHROW_NCX,c16str,(char16_t *__haystack, char16_t *__needle),wcswcs,(__haystack,__needle))
/* >> wcsstr(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char16_t const *,__NOTHROW_NCX,c16str,(char16_t const *__haystack, char16_t const *__needle),wcswcs,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsstr(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char16_t *,__NOTHROW_NCX,c16str,(char16_t const *__haystack, char16_t const *__needle),wcswcs,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsstr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsstr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char16_t *__NOTHROW_NCX(__LIBDCALL c16str)(char16_t *__haystack, char16_t *__needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
/* >> wcsstr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char16_t const *__NOTHROW_NCX(__LIBDCALL c16str)(char16_t const *__haystack, char16_t const *__needle) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsstr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char16_t *__NOTHROW_NCX(__LIBDCALL c16str)(char16_t const *__haystack, char16_t const *__needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c16str.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsstr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char16_t *__NOTHROW_NCX(__LIBDCALL c16str)(char16_t *__haystack, char16_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16str))(__haystack, __needle); }
/* >> wcsstr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char16_t const *__NOTHROW_NCX(__LIBDCALL c16str)(char16_t const *__haystack, char16_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16str))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsstr(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16str, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char16_t *__NOTHROW_NCX(__LIBDCALL c16str)(char16_t const *__haystack, char16_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16str))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsstr) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char32_t *,__NOTHROW_NCX,c32str,(char32_t *__haystack, char32_t *__needle),wcsstr,(__haystack,__needle))
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char32_t const *,__NOTHROW_NCX,c32str,(char32_t const *__haystack, char32_t const *__needle),wcsstr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char32_t *,__NOTHROW_NCX,c32str,(char32_t const *__haystack, char32_t const *__needle),wcsstr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_KOS$wcsstr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsstr(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char32_t *,__NOTHROW_NCX,c32str,(char32_t *__haystack, char32_t *__needle),wcsstr,(__haystack,__needle))
/* >> wcsstr(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char32_t const *,__NOTHROW_NCX,c32str,(char32_t const *__haystack, char32_t const *__needle),wcsstr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsstr(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char32_t *,__NOTHROW_NCX,c32str,(char32_t const *__haystack, char32_t const *__needle),wcsstr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_wcswcs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char32_t *,__NOTHROW_NCX,c32str,(char32_t *__haystack, char32_t *__needle),wcswcs,(__haystack,__needle))
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char32_t const *,__NOTHROW_NCX,c32str,(char32_t const *__haystack, char32_t const *__needle),wcswcs,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char32_t *,__NOTHROW_NCX,c32str,(char32_t const *__haystack, char32_t const *__needle),wcswcs,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_KOS$wcswcs)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsstr(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char32_t *,__NOTHROW_NCX,c32str,(char32_t *__haystack, char32_t *__needle),wcswcs,(__haystack,__needle))
/* >> wcsstr(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char32_t const *,__NOTHROW_NCX,c32str,(char32_t const *__haystack, char32_t const *__needle),wcswcs,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsstr(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char32_t *,__NOTHROW_NCX,c32str,(char32_t const *__haystack, char32_t const *__needle),wcswcs,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsstr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsstr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char32_t *__NOTHROW_NCX(__LIBKCALL c32str)(char32_t *__haystack, char32_t *__needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
/* >> wcsstr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char32_t const *__NOTHROW_NCX(__LIBKCALL c32str)(char32_t const *__haystack, char32_t const *__needle) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsstr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char32_t *__NOTHROW_NCX(__LIBKCALL c32str)(char32_t const *__haystack, char32_t const *__needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c32str.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsstr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char32_t *__NOTHROW_NCX(__LIBKCALL c32str)(char32_t *__haystack, char32_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32str))(__haystack, __needle); }
/* >> wcsstr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char32_t const *__NOTHROW_NCX(__LIBKCALL c32str)(char32_t const *__haystack, char32_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32str))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsstr(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32str, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char32_t *__NOTHROW_NCX(__LIBKCALL c32str)(char32_t const *__haystack, char32_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32str))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcscasestr) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcscasestr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char16_t *,__NOTHROW_NCX,c16casestr,(char16_t *__haystack, char16_t *__needle),wcscasestr,(__haystack,__needle))
/* >> wcscasestr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char16_t const *,__NOTHROW_NCX,c16casestr,(char16_t const *__haystack, char16_t const *__needle),wcscasestr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcscasestr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16casestr,(char16_t const *__haystack, char16_t const *__needle),wcscasestr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcscasestr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcscasestr(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char16_t *,__NOTHROW_NCX,c16casestr,(char16_t *__haystack, char16_t *__needle),wcscasestr,(__haystack,__needle))
/* >> wcscasestr(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char16_t const *,__NOTHROW_NCX,c16casestr,(char16_t const *__haystack, char16_t const *__needle),wcscasestr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcscasestr(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16casestr,(char16_t const *__haystack, char16_t const *__needle),wcscasestr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcscasestr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcscasestr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char16_t *__NOTHROW_NCX(__LIBDCALL c16casestr)(char16_t *__haystack, char16_t *__needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
/* >> wcscasestr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char16_t const *__NOTHROW_NCX(__LIBDCALL c16casestr)(char16_t const *__haystack, char16_t const *__needle) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcscasestr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16casestr)(char16_t const *__haystack, char16_t const *__needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c16casestr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcscasestr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char16_t *__NOTHROW_NCX(__LIBDCALL c16casestr)(char16_t *__haystack, char16_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16casestr))(__haystack, __needle); }
/* >> wcscasestr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char16_t const *__NOTHROW_NCX(__LIBDCALL c16casestr)(char16_t const *__haystack, char16_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16casestr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcscasestr(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16casestr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16casestr)(char16_t const *__haystack, char16_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16casestr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcscasestr) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcscasestr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char32_t *,__NOTHROW_NCX,c32casestr,(char32_t *__haystack, char32_t *__needle),wcscasestr,(__haystack,__needle))
/* >> wcscasestr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char32_t const *,__NOTHROW_NCX,c32casestr,(char32_t const *__haystack, char32_t const *__needle),wcscasestr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcscasestr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32casestr,(char32_t const *__haystack, char32_t const *__needle),wcscasestr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_KOS$wcscasestr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcscasestr(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char32_t *,__NOTHROW_NCX,c32casestr,(char32_t *__haystack, char32_t *__needle),wcscasestr,(__haystack,__needle))
/* >> wcscasestr(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char32_t const *,__NOTHROW_NCX,c32casestr,(char32_t const *__haystack, char32_t const *__needle),wcscasestr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcscasestr(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32casestr,(char32_t const *__haystack, char32_t const *__needle),wcscasestr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcscasestr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcscasestr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char32_t *__NOTHROW_NCX(__LIBKCALL c32casestr)(char32_t *__haystack, char32_t *__needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
/* >> wcscasestr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char32_t const *__NOTHROW_NCX(__LIBKCALL c32casestr)(char32_t const *__haystack, char32_t const *__needle) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcscasestr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32casestr)(char32_t const *__haystack, char32_t const *__needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c32casestr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcscasestr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char32_t *__NOTHROW_NCX(__LIBKCALL c32casestr)(char32_t *__haystack, char32_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32casestr))(__haystack, __needle); }
/* >> wcscasestr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char32_t const *__NOTHROW_NCX(__LIBKCALL c32casestr)(char32_t const *__haystack, char32_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32casestr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcscasestr(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32casestr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32casestr)(char32_t const *__haystack, char32_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32casestr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcscpy) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcscpy(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1),char16_t *,__NOTHROW_NCX,c16cpy,(char16_t *__restrict __buf, char16_t const *__restrict __src),wcscpy,(__buf,__src))
#elif defined(__CRT_HAVE_DOS$wcscpy)
/* >> wcscpy(3) */
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1),char16_t *,__NOTHROW_NCX,c16cpy,(char16_t *__restrict __buf, char16_t const *__restrict __src),wcscpy,(__buf,__src))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcscpy.h>
/* >> wcscpy(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16cpy)(char16_t *__restrict __buf, char16_t const *__restrict __src) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16cpy.h>
/* >> wcscpy(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16cpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16cpy)(char16_t *__restrict __buf, char16_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16cpy))(__buf, __src); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscpy) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcscpy(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1),char32_t *,__NOTHROW_NCX,c32cpy,(char32_t *__restrict __buf, char32_t const *__restrict __src),wcscpy,(__buf,__src))
#elif defined(__CRT_HAVE_KOS$wcscpy)
/* >> wcscpy(3) */
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1),char32_t *,__NOTHROW_NCX,c32cpy,(char32_t *__restrict __buf, char32_t const *__restrict __src),wcscpy,(__buf,__src))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcscpy.h>
/* >> wcscpy(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32cpy)(char32_t *__restrict __buf, char32_t const *__restrict __src) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32cpy.h>
/* >> wcscpy(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32cpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32cpy)(char32_t *__restrict __buf, char32_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32cpy))(__buf, __src); })
#endif /* !... */
#if defined(__CRT_HAVE_wcspcpy) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcspcpy(3)
 * Same as wcscpy, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1),char16_t *,__NOTHROW_NCX,c16pcpy,(char16_t *__restrict __buf, char16_t const *__restrict __src),wcspcpy,(__buf,__src))
#elif defined(__CRT_HAVE_DOS$wcspcpy)
/* >> wcspcpy(3)
 * Same as wcscpy, but return a pointer after the last written character */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1),char16_t *,__NOTHROW_NCX,c16pcpy,(char16_t *__restrict __buf, char16_t const *__restrict __src),wcspcpy,(__buf,__src))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcspcpy.h>
/* >> wcspcpy(3)
 * Same as wcscpy, but return a pointer after the last written character */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16pcpy)(char16_t *__restrict __buf, char16_t const *__restrict __src) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspcpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16pcpy.h>
/* >> wcspcpy(3)
 * Same as wcscpy, but return a pointer after the last written character */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16pcpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16pcpy)(char16_t *__restrict __buf, char16_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16pcpy))(__buf, __src); })
#endif /* !... */
#if defined(__CRT_HAVE_wcspcpy) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcspcpy(3)
 * Same as wcscpy, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1),char32_t *,__NOTHROW_NCX,c32pcpy,(char32_t *__restrict __buf, char32_t const *__restrict __src),wcspcpy,(__buf,__src))
#elif defined(__CRT_HAVE_KOS$wcspcpy)
/* >> wcspcpy(3)
 * Same as wcscpy, but return a pointer after the last written character */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1),char32_t *,__NOTHROW_NCX,c32pcpy,(char32_t *__restrict __buf, char32_t const *__restrict __src),wcspcpy,(__buf,__src))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcspcpy.h>
/* >> wcspcpy(3)
 * Same as wcscpy, but return a pointer after the last written character */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32pcpy)(char32_t *__restrict __buf, char32_t const *__restrict __src) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspcpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32pcpy.h>
/* >> wcspcpy(3)
 * Same as wcscpy, but return a pointer after the last written character */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32pcpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32pcpy)(char32_t *__restrict __buf, char32_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32pcpy))(__buf, __src); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncpy) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsncpy(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char16_t *,__NOTHROW_NCX,c16ncpy,(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcsncpy,(__buf,__src,__buflen))
#elif defined(__CRT_HAVE_DOS$wcsncpy)
/* >> wcsncpy(3) */
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char16_t *,__NOTHROW_NCX,c16ncpy,(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcsncpy,(__buf,__src,__buflen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsncpy.h>
/* >> wcsncpy(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) char16_t *__NOTHROW_NCX(__LIBDCALL c16ncpy)(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src, __buflen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16ncpy.h>
/* >> wcsncpy(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ncpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) char16_t *__NOTHROW_NCX(__LIBDCALL c16ncpy)(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ncpy))(__buf, __src, __buflen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncpy) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsncpy(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char32_t *,__NOTHROW_NCX,c32ncpy,(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcsncpy,(__buf,__src,__buflen))
#elif defined(__CRT_HAVE_KOS$wcsncpy)
/* >> wcsncpy(3) */
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),char32_t *,__NOTHROW_NCX,c32ncpy,(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcsncpy,(__buf,__src,__buflen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsncpy.h>
/* >> wcsncpy(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) char32_t *__NOTHROW_NCX(__LIBKCALL c32ncpy)(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src, __buflen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32ncpy.h>
/* >> wcsncpy(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ncpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) char32_t *__NOTHROW_NCX(__LIBKCALL c32ncpy)(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ncpy))(__buf, __src, __buflen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcspncpy) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcspncpy(3)
 * Same as wcsncpy, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16pncpy,(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcspncpy,(__buf,__src,__buflen))
#elif defined(__CRT_HAVE_DOS$wcspncpy)
/* >> wcspncpy(3)
 * Same as wcsncpy, but return a pointer after the last written character */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16pncpy,(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcspncpy,(__buf,__src,__buflen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcspncpy.h>
/* >> wcspncpy(3)
 * Same as wcsncpy, but return a pointer after the last written character */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16pncpy)(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspncpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src, __buflen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16pncpy.h>
/* >> wcspncpy(3)
 * Same as wcsncpy, but return a pointer after the last written character */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16pncpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16pncpy)(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16pncpy))(__buf, __src, __buflen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcspncpy) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcspncpy(3)
 * Same as wcsncpy, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32pncpy,(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcspncpy,(__buf,__src,__buflen))
#elif defined(__CRT_HAVE_KOS$wcspncpy)
/* >> wcspncpy(3)
 * Same as wcsncpy, but return a pointer after the last written character */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32pncpy,(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcspncpy,(__buf,__src,__buflen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcspncpy.h>
/* >> wcspncpy(3)
 * Same as wcsncpy, but return a pointer after the last written character */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32pncpy)(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspncpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src, __buflen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32pncpy.h>
/* >> wcspncpy(3)
 * Same as wcsncpy, but return a pointer after the last written character */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32pncpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32pncpy)(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32pncpy))(__buf, __src, __buflen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcscat(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_IN(2) __ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,c16cat,(char16_t *__restrict __buf, char16_t const *__restrict __src),wcscat,(__buf,__src))
#elif defined(__CRT_HAVE_DOS$wcscat)
/* >> wcscat(3) */
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_IN(2) __ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,c16cat,(char16_t *__restrict __buf, char16_t const *__restrict __src),wcscat,(__buf,__src))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcscat.h>
/* >> wcscat(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_INOUT(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16cat)(char16_t *__restrict __buf, char16_t const *__restrict __src) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscat))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16cat.h>
/* >> wcscat(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16cat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_INOUT(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16cat)(char16_t *__restrict __buf, char16_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16cat))(__buf, __src); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcscat(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_IN(2) __ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,c32cat,(char32_t *__restrict __buf, char32_t const *__restrict __src),wcscat,(__buf,__src))
#elif defined(__CRT_HAVE_KOS$wcscat)
/* >> wcscat(3) */
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_IN(2) __ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,c32cat,(char32_t *__restrict __buf, char32_t const *__restrict __src),wcscat,(__buf,__src))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcscat.h>
/* >> wcscat(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_INOUT(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32cat)(char32_t *__restrict __buf, char32_t const *__restrict __src) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscat))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32cat.h>
/* >> wcscat(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32cat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_INOUT(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32cat)(char32_t *__restrict __buf, char32_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32cat))(__buf, __src); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsncat(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INOUTS(1, 3) __ATTR_INS(2, 3),char16_t *,__NOTHROW_NCX,c16ncat,(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcsncat,(__buf,__src,__buflen))
#elif defined(__CRT_HAVE_DOS$wcsncat)
/* >> wcsncat(3) */
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_INOUTS(1, 3) __ATTR_INS(2, 3),char16_t *,__NOTHROW_NCX,c16ncat,(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcsncat,(__buf,__src,__buflen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsncat.h>
/* >> wcsncat(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INOUTS(1, 3) __ATTR_INS(2, 3) char16_t *__NOTHROW_NCX(__LIBDCALL c16ncat)(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncat))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src, __buflen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16ncat.h>
/* >> wcsncat(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ncat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INOUTS(1, 3) __ATTR_INS(2, 3) char16_t *__NOTHROW_NCX(__LIBDCALL c16ncat)(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ncat))(__buf, __src, __buflen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsncat(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INOUTS(1, 3) __ATTR_INS(2, 3),char32_t *,__NOTHROW_NCX,c32ncat,(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcsncat,(__buf,__src,__buflen))
#elif defined(__CRT_HAVE_KOS$wcsncat)
/* >> wcsncat(3) */
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_INOUTS(1, 3) __ATTR_INS(2, 3),char32_t *,__NOTHROW_NCX,c32ncat,(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcsncat,(__buf,__src,__buflen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsncat.h>
/* >> wcsncat(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INOUTS(1, 3) __ATTR_INS(2, 3) char32_t *__NOTHROW_NCX(__LIBKCALL c32ncat)(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncat))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src, __buflen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32ncat.h>
/* >> wcsncat(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ncat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INOUTS(1, 3) __ATTR_INS(2, 3) char32_t *__NOTHROW_NCX(__LIBKCALL c32ncat)(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ncat))(__buf, __src, __buflen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsspn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsspn(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),size_t,__NOTHROW_NCX,c16spn,(char16_t const *__haystack, char16_t const *__accept),wcsspn,(__haystack,__accept))
#elif defined(__CRT_HAVE_DOS$wcsspn)
/* >> wcsspn(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),size_t,__NOTHROW_NCX,c16spn,(char16_t const *__haystack, char16_t const *__accept),wcsspn,(__haystack,__accept))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsspn.h>
/* >> wcsspn(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) size_t __NOTHROW_NCX(__LIBDCALL c16spn)(char16_t const *__haystack, char16_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsspn))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16spn.h>
/* >> wcsspn(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16spn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) size_t __NOTHROW_NCX(__LIBDCALL c16spn)(char16_t const *__haystack, char16_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16spn))(__haystack, __accept); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsspn) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsspn(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),size_t,__NOTHROW_NCX,c32spn,(char32_t const *__haystack, char32_t const *__accept),wcsspn,(__haystack,__accept))
#elif defined(__CRT_HAVE_KOS$wcsspn)
/* >> wcsspn(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),size_t,__NOTHROW_NCX,c32spn,(char32_t const *__haystack, char32_t const *__accept),wcsspn,(__haystack,__accept))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsspn.h>
/* >> wcsspn(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) size_t __NOTHROW_NCX(__LIBKCALL c32spn)(char32_t const *__haystack, char32_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsspn))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32spn.h>
/* >> wcsspn(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32spn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) size_t __NOTHROW_NCX(__LIBKCALL c32spn)(char32_t const *__haystack, char32_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32spn))(__haystack, __accept); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscspn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcscspn(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),size_t,__NOTHROW_NCX,c16cspn,(char16_t const *__haystack, char16_t const *__reject),wcscspn,(__haystack,__reject))
#elif defined(__CRT_HAVE_DOS$wcscspn)
/* >> wcscspn(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),size_t,__NOTHROW_NCX,c16cspn,(char16_t const *__haystack, char16_t const *__reject),wcscspn,(__haystack,__reject))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcscspn.h>
/* >> wcscspn(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) size_t __NOTHROW_NCX(__LIBDCALL c16cspn)(char16_t const *__haystack, char16_t const *__reject) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscspn))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__reject); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16cspn.h>
/* >> wcscspn(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16cspn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) size_t __NOTHROW_NCX(__LIBDCALL c16cspn)(char16_t const *__haystack, char16_t const *__reject) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16cspn))(__haystack, __reject); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscspn) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcscspn(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),size_t,__NOTHROW_NCX,c32cspn,(char32_t const *__haystack, char32_t const *__reject),wcscspn,(__haystack,__reject))
#elif defined(__CRT_HAVE_KOS$wcscspn)
/* >> wcscspn(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),size_t,__NOTHROW_NCX,c32cspn,(char32_t const *__haystack, char32_t const *__reject),wcscspn,(__haystack,__reject))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcscspn.h>
/* >> wcscspn(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) size_t __NOTHROW_NCX(__LIBKCALL c32cspn)(char32_t const *__haystack, char32_t const *__reject) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscspn))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__reject); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32cspn.h>
/* >> wcscspn(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32cspn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) size_t __NOTHROW_NCX(__LIBKCALL c32cspn)(char32_t const *__haystack, char32_t const *__reject) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32cspn))(__haystack, __reject); })
#endif /* !... */
#if defined(__CRT_HAVE_wcspbrk) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcspbrk(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char16_t *,__NOTHROW_NCX,c16pbrk,(char16_t *__haystack, char16_t const *__accept),wcspbrk,(__haystack,__accept))
/* >> wcspbrk(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char16_t const *,__NOTHROW_NCX,c16pbrk,(char16_t const *__haystack, char16_t const *__accept),wcspbrk,(__haystack,__accept))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcspbrk(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char16_t *,__NOTHROW_NCX,c16pbrk,(char16_t const *__haystack, char16_t const *__accept),wcspbrk,(__haystack,__accept))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcspbrk)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcspbrk(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char16_t *,__NOTHROW_NCX,c16pbrk,(char16_t *__haystack, char16_t const *__accept),wcspbrk,(__haystack,__accept))
/* >> wcspbrk(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char16_t const *,__NOTHROW_NCX,c16pbrk,(char16_t const *__haystack, char16_t const *__accept),wcspbrk,(__haystack,__accept))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcspbrk(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char16_t *,__NOTHROW_NCX,c16pbrk,(char16_t const *__haystack, char16_t const *__accept),wcspbrk,(__haystack,__accept))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcspbrk.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcspbrk(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char16_t *__NOTHROW_NCX(__LIBDCALL c16pbrk)(char16_t *__haystack, char16_t const *__accept) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
/* >> wcspbrk(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char16_t const *__NOTHROW_NCX(__LIBDCALL c16pbrk)(char16_t const *__haystack, char16_t const *__accept) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcspbrk(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char16_t *__NOTHROW_NCX(__LIBDCALL c16pbrk)(char16_t const *__haystack, char16_t const *__accept) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c16pbrk.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcspbrk(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char16_t *__NOTHROW_NCX(__LIBDCALL c16pbrk)(char16_t *__haystack, char16_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16pbrk))(__haystack, __accept); }
/* >> wcspbrk(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char16_t const *__NOTHROW_NCX(__LIBDCALL c16pbrk)(char16_t const *__haystack, char16_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16pbrk))(__haystack, __accept); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcspbrk(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16pbrk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char16_t *__NOTHROW_NCX(__LIBDCALL c16pbrk)(char16_t const *__haystack, char16_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16pbrk))(__haystack, __accept); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcspbrk) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcspbrk(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char32_t *,__NOTHROW_NCX,c32pbrk,(char32_t *__haystack, char32_t const *__accept),wcspbrk,(__haystack,__accept))
/* >> wcspbrk(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char32_t const *,__NOTHROW_NCX,c32pbrk,(char32_t const *__haystack, char32_t const *__accept),wcspbrk,(__haystack,__accept))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcspbrk(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char32_t *,__NOTHROW_NCX,c32pbrk,(char32_t const *__haystack, char32_t const *__accept),wcspbrk,(__haystack,__accept))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_KOS$wcspbrk)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcspbrk(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char32_t *,__NOTHROW_NCX,c32pbrk,(char32_t *__haystack, char32_t const *__accept),wcspbrk,(__haystack,__accept))
/* >> wcspbrk(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char32_t const *,__NOTHROW_NCX,c32pbrk,(char32_t const *__haystack, char32_t const *__accept),wcspbrk,(__haystack,__accept))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcspbrk(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char32_t *,__NOTHROW_NCX,c32pbrk,(char32_t const *__haystack, char32_t const *__accept),wcspbrk,(__haystack,__accept))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcspbrk.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcspbrk(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char32_t *__NOTHROW_NCX(__LIBKCALL c32pbrk)(char32_t *__haystack, char32_t const *__accept) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
/* >> wcspbrk(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char32_t const *__NOTHROW_NCX(__LIBKCALL c32pbrk)(char32_t const *__haystack, char32_t const *__accept) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcspbrk(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char32_t *__NOTHROW_NCX(__LIBKCALL c32pbrk)(char32_t const *__haystack, char32_t const *__accept) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c32pbrk.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcspbrk(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char32_t *__NOTHROW_NCX(__LIBKCALL c32pbrk)(char32_t *__haystack, char32_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32pbrk))(__haystack, __accept); }
/* >> wcspbrk(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char32_t const *__NOTHROW_NCX(__LIBKCALL c32pbrk)(char32_t const *__haystack, char32_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32pbrk))(__haystack, __accept); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcspbrk(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32pbrk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char32_t *__NOTHROW_NCX(__LIBKCALL c32pbrk)(char32_t const *__haystack, char32_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32pbrk))(__haystack, __accept); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#ifndef __c16tok_defined
#define __c16tok_defined
#if defined(__CRT_HAVE_wcstok) && !defined(__CRT_DOS_PRIMARY) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstok(3) */
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1),char16_t *,__NOTHROW_NCX,c16tok,(char16_t *__str, char16_t const *__restrict __delim, char16_t **__restrict __save_ptr),wcstok,(__str,__delim,__save_ptr))
#elif defined(__CRT_HAVE_DOS$wcstok) && !defined(__CRT_DOS_PRIMARY)
/* >> wcstok(3) */
__CREDIRECT_DOS(__ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1),char16_t *,__NOTHROW_NCX,c16tok,(char16_t *__str, char16_t const *__restrict __delim, char16_t **__restrict __save_ptr),wcstok,(__str,__delim,__save_ptr))
#elif defined(__CRT_HAVE_wcstok_s) && defined(__CRT_DOS_PRIMARY) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstok(3) */
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1),char16_t *,__NOTHROW_NCX,c16tok,(char16_t *__str, char16_t const *__restrict __delim, char16_t **__restrict __save_ptr),wcstok_s,(__str,__delim,__save_ptr))
#elif defined(__CRT_HAVE_DOS$wcstok_s) && defined(__CRT_DOS_PRIMARY)
/* >> wcstok(3) */
__CREDIRECT_DOS(__ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1),char16_t *,__NOTHROW_NCX,c16tok,(char16_t *__str, char16_t const *__restrict __delim, char16_t **__restrict __save_ptr),wcstok_s,(__str,__delim,__save_ptr))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstok.h>
/* >> wcstok(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16tok)(char16_t *__str, char16_t const *__restrict __delim, char16_t **__restrict __save_ptr) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstok))((__WCHAR_TYPE__ *)__str, (__WCHAR_TYPE__ const *)__delim, (__WCHAR_TYPE__ **)__save_ptr); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16tok.h>
/* >> wcstok(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16tok, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16tok)(char16_t *__str, char16_t const *__restrict __delim, char16_t **__restrict __save_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16tok))(__str, __delim, __save_ptr); })
#endif /* !... */
#endif /* !__c16tok_defined */
#ifndef __c32tok_defined
#define __c32tok_defined
#if defined(__CRT_HAVE_wcstok) && !defined(__CRT_DOS_PRIMARY) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstok(3) */
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1),char32_t *,__NOTHROW_NCX,c32tok,(char32_t *__str, char32_t const *__restrict __delim, char32_t **__restrict __save_ptr),wcstok,(__str,__delim,__save_ptr))
#elif defined(__CRT_HAVE_KOS$wcstok) && !defined(__CRT_DOS_PRIMARY)
/* >> wcstok(3) */
__CREDIRECT_KOS(__ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1),char32_t *,__NOTHROW_NCX,c32tok,(char32_t *__str, char32_t const *__restrict __delim, char32_t **__restrict __save_ptr),wcstok,(__str,__delim,__save_ptr))
#elif defined(__CRT_HAVE_wcstok_s) && defined(__CRT_DOS_PRIMARY) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstok(3) */
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1),char32_t *,__NOTHROW_NCX,c32tok,(char32_t *__str, char32_t const *__restrict __delim, char32_t **__restrict __save_ptr),wcstok_s,(__str,__delim,__save_ptr))
#elif defined(__CRT_HAVE_KOS$wcstok_s) && defined(__CRT_DOS_PRIMARY)
/* >> wcstok(3) */
__CREDIRECT_KOS(__ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1),char32_t *,__NOTHROW_NCX,c32tok,(char32_t *__str, char32_t const *__restrict __delim, char32_t **__restrict __save_ptr),wcstok_s,(__str,__delim,__save_ptr))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstok.h>
/* >> wcstok(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32tok)(char32_t *__str, char32_t const *__restrict __delim, char32_t **__restrict __save_ptr) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstok))((__WCHAR_TYPE__ *)__str, (__WCHAR_TYPE__ const *)__delim, (__WCHAR_TYPE__ **)__save_ptr); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32tok.h>
/* >> wcstok(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32tok, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32tok)(char32_t *__str, char32_t const *__restrict __delim, char32_t **__restrict __save_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32tok))(__str, __delim, __save_ptr); })
#endif /* !... */
#endif /* !__c32tok_defined */
#if defined(__CRT_HAVE_wcssep) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcssep(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,c16sep,(char16_t **__restrict __stringp, char16_t const *__restrict __delim),wcssep,(__stringp,__delim))
#elif defined(__CRT_HAVE_DOS$wcssep)
/* >> wcssep(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(2) __ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,c16sep,(char16_t **__restrict __stringp, char16_t const *__restrict __delim),wcssep,(__stringp,__delim))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcssep.h>
/* >> wcssep(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_INOUT(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16sep)(char16_t **__restrict __stringp, char16_t const *__restrict __delim) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcssep))((__WCHAR_TYPE__ **)__stringp, (__WCHAR_TYPE__ const *)__delim); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16sep.h>
/* >> wcssep(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sep, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_INOUT(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16sep)(char16_t **__restrict __stringp, char16_t const *__restrict __delim) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sep))(__stringp, __delim); })
#endif /* !... */
#if defined(__CRT_HAVE_wcssep) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcssep(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,c32sep,(char32_t **__restrict __stringp, char32_t const *__restrict __delim),wcssep,(__stringp,__delim))
#elif defined(__CRT_HAVE_KOS$wcssep)
/* >> wcssep(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(2) __ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,c32sep,(char32_t **__restrict __stringp, char32_t const *__restrict __delim),wcssep,(__stringp,__delim))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcssep.h>
/* >> wcssep(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_INOUT(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32sep)(char32_t **__restrict __stringp, char32_t const *__restrict __delim) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcssep))((__WCHAR_TYPE__ **)__stringp, (__WCHAR_TYPE__ const *)__delim); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32sep.h>
/* >> wcssep(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sep, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_INOUT(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32sep)(char32_t **__restrict __stringp, char32_t const *__restrict __delim) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sep))(__stringp, __delim); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsdup) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsdup(3) */
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16dup,(char16_t const *__restrict __string),wcsdup,(__string))
#elif defined(__CRT_HAVE_DOS$wcsdup)
/* >> wcsdup(3) */
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16dup,(char16_t const *__restrict __string),wcsdup,(__string))
#elif defined(__CRT_HAVE__wcsdup) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsdup(3) */
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16dup,(char16_t const *__restrict __string),_wcsdup,(__string))
#elif defined(__CRT_HAVE_DOS$_wcsdup)
/* >> wcsdup(3) */
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16dup,(char16_t const *__restrict __string),_wcsdup,(__string))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsdup.h>
/* >> wcsdup(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16dup)(char16_t const *__restrict __string) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsdup))((__WCHAR_TYPE__ const *)__string); }
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/parts.uchar.string/c16dup.h>
/* >> wcsdup(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16dup, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16dup)(char16_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16dup))(__string); })
#endif /* ... */
#if defined(__CRT_HAVE_wcsdup) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsdup(3) */
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32dup,(char32_t const *__restrict __string),wcsdup,(__string))
#elif defined(__CRT_HAVE_KOS$wcsdup)
/* >> wcsdup(3) */
__CREDIRECT_KOS(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32dup,(char32_t const *__restrict __string),wcsdup,(__string))
#elif defined(__CRT_HAVE__wcsdup) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsdup(3) */
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32dup,(char32_t const *__restrict __string),_wcsdup,(__string))
#elif defined(__CRT_HAVE_KOS$_wcsdup)
/* >> wcsdup(3) */
__CREDIRECT_KOS(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32dup,(char32_t const *__restrict __string),_wcsdup,(__string))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsdup.h>
/* >> wcsdup(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32dup)(char32_t const *__restrict __string) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsdup))((__WCHAR_TYPE__ const *)__string); }
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/parts.uchar.string/c32dup.h>
/* >> wcsdup(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32dup, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32dup)(char32_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32dup))(__string); })
#endif /* ... */
#if defined(__CRT_HAVE_wcsndup) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsndup(3) */
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INS(1, 2),char16_t *,__NOTHROW_NCX,c16ndup,(char16_t const *__restrict __str, __SIZE_TYPE__ __max_chars),wcsndup,(__str,__max_chars))
#elif defined(__CRT_HAVE_DOS$wcsndup)
/* >> wcsndup(3) */
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INS(1, 2),char16_t *,__NOTHROW_NCX,c16ndup,(char16_t const *__restrict __str, __SIZE_TYPE__ __max_chars),wcsndup,(__str,__max_chars))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsndup.h>
/* >> wcsndup(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INS(1, 2) char16_t *__NOTHROW_NCX(__LIBDCALL c16ndup)(char16_t const *__restrict __str, __SIZE_TYPE__ __max_chars) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsndup))((__WCHAR_TYPE__ const *)__str, __max_chars); }
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/parts.uchar.string/c16ndup.h>
/* >> wcsndup(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ndup, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INS(1, 2) char16_t *__NOTHROW_NCX(__LIBDCALL c16ndup)(char16_t const *__restrict __str, __SIZE_TYPE__ __max_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ndup))(__str, __max_chars); })
#endif /* ... */
#if defined(__CRT_HAVE_wcsndup) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsndup(3) */
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INS(1, 2),char32_t *,__NOTHROW_NCX,c32ndup,(char32_t const *__restrict __str, __SIZE_TYPE__ __max_chars),wcsndup,(__str,__max_chars))
#elif defined(__CRT_HAVE_KOS$wcsndup)
/* >> wcsndup(3) */
__CREDIRECT_KOS(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INS(1, 2),char32_t *,__NOTHROW_NCX,c32ndup,(char32_t const *__restrict __str, __SIZE_TYPE__ __max_chars),wcsndup,(__str,__max_chars))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsndup.h>
/* >> wcsndup(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INS(1, 2) char32_t *__NOTHROW_NCX(__LIBKCALL c32ndup)(char32_t const *__restrict __str, __SIZE_TYPE__ __max_chars) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsndup))((__WCHAR_TYPE__ const *)__str, __max_chars); }
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/parts.uchar.string/c32ndup.h>
/* >> wcsndup(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ndup, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INS(1, 2) char32_t *__NOTHROW_NCX(__LIBKCALL c32ndup)(char32_t const *__restrict __str, __SIZE_TYPE__ __max_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ndup))(__str, __max_chars); })
#endif /* ... */
#if defined(__CRT_HAVE_wcsfry) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsfry(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,c16fry,(char16_t *__restrict __str),wcsfry,(__str))
#elif defined(__CRT_HAVE_DOS$wcsfry)
/* >> wcsfry(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,c16fry,(char16_t *__restrict __str),wcsfry,(__str))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsfry.h>
/* >> wcsfry(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INOUT(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16fry)(char16_t *__restrict __str) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsfry))((__WCHAR_TYPE__ *)__str); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16fry.h>
/* >> wcsfry(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16fry, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INOUT(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16fry)(char16_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16fry))(__str); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsfry) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsfry(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,c32fry,(char32_t *__restrict __str),wcsfry,(__str))
#elif defined(__CRT_HAVE_KOS$wcsfry)
/* >> wcsfry(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,c32fry,(char32_t *__restrict __str),wcsfry,(__str))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsfry.h>
/* >> wcsfry(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INOUT(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32fry)(char32_t *__restrict __str) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsfry))((__WCHAR_TYPE__ *)__str); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32fry.h>
/* >> wcsfry(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32fry, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INOUT(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32fry)(char32_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32fry))(__str); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscasecmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcscasecmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16casecmp,(char16_t const *__s1, char16_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscasecmp)
/* >> wcscasecmp(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16casecmp,(char16_t const *__s1, char16_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcscasecmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16casecmp,(char16_t const *__s1, char16_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$_wcsicmp)
/* >> wcscasecmp(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16casecmp,(char16_t const *__s1, char16_t const *__s2),_wcsicmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcscasecmp.h>
/* >> wcscasecmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBDCALL c16casecmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16casecmp.h>
/* >> wcscasecmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16casecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBDCALL c16casecmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16casecmp))(__s1, __s2); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscasecmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcscasecmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32casecmp,(char32_t const *__s1, char32_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$wcscasecmp)
/* >> wcscasecmp(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32casecmp,(char32_t const *__s1, char32_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcscasecmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32casecmp,(char32_t const *__s1, char32_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$_wcsicmp)
/* >> wcscasecmp(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32casecmp,(char32_t const *__s1, char32_t const *__s2),_wcsicmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcscasecmp.h>
/* >> wcscasecmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBKCALL c32casecmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32casecmp.h>
/* >> wcscasecmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32casecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBKCALL c32casecmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32casecmp))(__s1, __s2); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncasecmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsncasecmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecmp,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsncasecmp)
/* >> wcsncasecmp(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecmp,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsncasecmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecmp,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$_wcsnicmp)
/* >> wcsncasecmp(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecmp,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsncasecmp.h>
/* >> wcsncasecmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16ncasecmp)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16ncasecmp.h>
/* >> wcsncasecmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ncasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16ncasecmp)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ncasecmp))(__s1, __s2, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncasecmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsncasecmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecmp,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsncasecmp)
/* >> wcsncasecmp(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecmp,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsncasecmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecmp,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_KOS$_wcsnicmp)
/* >> wcsncasecmp(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecmp,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsncasecmp.h>
/* >> wcsncasecmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32ncasecmp)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32ncasecmp.h>
/* >> wcsncasecmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ncasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32ncasecmp)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ncasecmp))(__s1, __s2, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsxfrm) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsxfrm(3) */
__CREDIRECT(__ATTR_INS(2, 3) __ATTR_OUTS(1, 3),size_t,__NOTHROW_NCX,c16xfrm,(char16_t *__dst, char16_t const *__restrict __src, size_t __buflen),wcsxfrm,(__dst,__src,__buflen))
#elif defined(__CRT_HAVE_DOS$wcsxfrm)
/* >> wcsxfrm(3) */
__CREDIRECT_DOS(__ATTR_INS(2, 3) __ATTR_OUTS(1, 3),size_t,__NOTHROW_NCX,c16xfrm,(char16_t *__dst, char16_t const *__restrict __src, size_t __buflen),wcsxfrm,(__dst,__src,__buflen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsxfrm.h>
/* >> wcsxfrm(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) size_t __NOTHROW_NCX(__LIBDCALL c16xfrm)(char16_t *__dst, char16_t const *__restrict __src, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __buflen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16xfrm.h>
/* >> wcsxfrm(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16xfrm, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) size_t __NOTHROW_NCX(__LIBDCALL c16xfrm)(char16_t *__dst, char16_t const *__restrict __src, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16xfrm))(__dst, __src, __buflen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsxfrm) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsxfrm(3) */
__CREDIRECT(__ATTR_INS(2, 3) __ATTR_OUTS(1, 3),size_t,__NOTHROW_NCX,c32xfrm,(char32_t *__dst, char32_t const *__restrict __src, size_t __buflen),wcsxfrm,(__dst,__src,__buflen))
#elif defined(__CRT_HAVE_KOS$wcsxfrm)
/* >> wcsxfrm(3) */
__CREDIRECT_KOS(__ATTR_INS(2, 3) __ATTR_OUTS(1, 3),size_t,__NOTHROW_NCX,c32xfrm,(char32_t *__dst, char32_t const *__restrict __src, size_t __buflen),wcsxfrm,(__dst,__src,__buflen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsxfrm.h>
/* >> wcsxfrm(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) size_t __NOTHROW_NCX(__LIBKCALL c32xfrm)(char32_t *__dst, char32_t const *__restrict __src, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __buflen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32xfrm.h>
/* >> wcsxfrm(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32xfrm, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) size_t __NOTHROW_NCX(__LIBKCALL c32xfrm)(char32_t *__dst, char32_t const *__restrict __src, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32xfrm))(__dst, __src, __buflen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscoll) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcscoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16coll,(char16_t const *__s1, char16_t const *__s2),wcscoll,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscoll)
/* >> wcscoll(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16coll,(char16_t const *__s1, char16_t const *__s2),wcscoll,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcscoll.h>
/* >> wcscoll(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBDCALL c16coll)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16coll.h>
/* >> wcscoll(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16coll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBDCALL c16coll)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16coll))(__s1, __s2); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscoll) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcscoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32coll,(char32_t const *__s1, char32_t const *__s2),wcscoll,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$wcscoll)
/* >> wcscoll(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32coll,(char32_t const *__s1, char32_t const *__s2),wcscoll,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcscoll.h>
/* >> wcscoll(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBKCALL c32coll)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32coll.h>
/* >> wcscoll(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32coll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBKCALL c32coll)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32coll))(__s1, __s2); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncoll) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsncoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsncoll)
/* >> wcsncoll(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsncoll) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsncoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsncoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$_wcsncoll)
/* >> wcsncoll(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsncoll,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsncoll.h>
/* >> wcsncoll(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16ncoll)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16ncoll.h>
/* >> wcsncoll(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ncoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16ncoll)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ncoll))(__s1, __s2, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncoll) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsncoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsncoll)
/* >> wcsncoll(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsncoll) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsncoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsncoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_KOS$_wcsncoll)
/* >> wcsncoll(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsncoll,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsncoll.h>
/* >> wcsncoll(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32ncoll)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32ncoll.h>
/* >> wcsncoll(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ncoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32ncoll)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ncoll))(__s1, __s2, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscasecoll) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcscasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16casecoll,(char16_t const *__s1, char16_t const *__s2),wcscasecoll,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscasecoll)
/* >> wcscasecoll(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16casecoll,(char16_t const *__s1, char16_t const *__s2),wcscasecoll,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicoll) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcscasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16casecoll,(char16_t const *__s1, char16_t const *__s2),_wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$_wcsicoll)
/* >> wcscasecoll(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16casecoll,(char16_t const *__s1, char16_t const *__s2),_wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicoll) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcscasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16casecoll,(char16_t const *__s1, char16_t const *__s2),wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcsicoll)
/* >> wcscasecoll(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16casecoll,(char16_t const *__s1, char16_t const *__s2),wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcscasecmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcscasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16casecoll,(char16_t const *__s1, char16_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscasecmp)
/* >> wcscasecoll(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16casecoll,(char16_t const *__s1, char16_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcscasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16casecoll,(char16_t const *__s1, char16_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$_wcsicmp)
/* >> wcscasecoll(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16casecoll,(char16_t const *__s1, char16_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcscasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16casecoll,(char16_t const *__s1, char16_t const *__s2),wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcsicmp)
/* >> wcscasecoll(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16casecoll,(char16_t const *__s1, char16_t const *__s2),wcsicmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcscasecoll.h>
/* >> wcscasecoll(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBDCALL c16casecoll)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16casecoll.h>
/* >> wcscasecoll(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16casecoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBDCALL c16casecoll)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16casecoll))(__s1, __s2); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscasecoll) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcscasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32casecoll,(char32_t const *__s1, char32_t const *__s2),wcscasecoll,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$wcscasecoll)
/* >> wcscasecoll(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32casecoll,(char32_t const *__s1, char32_t const *__s2),wcscasecoll,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicoll) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcscasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32casecoll,(char32_t const *__s1, char32_t const *__s2),_wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$_wcsicoll)
/* >> wcscasecoll(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32casecoll,(char32_t const *__s1, char32_t const *__s2),_wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicoll) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcscasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32casecoll,(char32_t const *__s1, char32_t const *__s2),wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$wcsicoll)
/* >> wcscasecoll(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32casecoll,(char32_t const *__s1, char32_t const *__s2),wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcscasecmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcscasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32casecoll,(char32_t const *__s1, char32_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$wcscasecmp)
/* >> wcscasecoll(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32casecoll,(char32_t const *__s1, char32_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcscasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32casecoll,(char32_t const *__s1, char32_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$_wcsicmp)
/* >> wcscasecoll(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32casecoll,(char32_t const *__s1, char32_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcscasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32casecoll,(char32_t const *__s1, char32_t const *__s2),wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$wcsicmp)
/* >> wcscasecoll(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32casecoll,(char32_t const *__s1, char32_t const *__s2),wcsicmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcscasecoll.h>
/* >> wcscasecoll(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBKCALL c32casecoll)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32casecoll.h>
/* >> wcscasecoll(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32casecoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBKCALL c32casecoll)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32casecoll))(__s1, __s2); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncasecoll) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsncasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsncasecoll)
/* >> wcsncasecoll(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicoll) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsncasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$_wcsnicoll)
/* >> wcsncasecoll(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicoll) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsncasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnicoll)
/* >> wcsncasecoll(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsncasecmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsncasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsncasecmp)
/* >> wcsncasecoll(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsncasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$_wcsnicmp)
/* >> wcsncasecoll(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsncasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnicmp)
/* >> wcsncasecoll(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsncasecoll.h>
/* >> wcsncasecoll(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16ncasecoll)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16ncasecoll.h>
/* >> wcsncasecoll(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ncasecoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16ncasecoll)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ncasecoll))(__s1, __s2, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncasecoll) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsncasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsncasecoll)
/* >> wcsncasecoll(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicoll) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsncasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_KOS$_wcsnicoll)
/* >> wcsncasecoll(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicoll) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsncasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsnicoll)
/* >> wcsncasecoll(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsncasecmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsncasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsncasecmp)
/* >> wcsncasecoll(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsncasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_KOS$_wcsnicmp)
/* >> wcsncasecoll(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsncasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsnicmp)
/* >> wcsncasecoll(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsncasecoll.h>
/* >> wcsncasecoll(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32ncasecoll)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32ncasecoll.h>
/* >> wcsncasecoll(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ncasecoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32ncasecoll)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ncasecoll))(__s1, __s2, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcslwr) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcslwr(3) */
__CREDIRECT(__ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,c16lwr,(char16_t *__restrict __str),wcslwr,(__str))
#elif defined(__CRT_HAVE_DOS$wcslwr)
/* >> wcslwr(3) */
__CREDIRECT_DOS(__ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,c16lwr,(char16_t *__restrict __str),wcslwr,(__str))
#elif defined(__CRT_HAVE__wcslwr) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcslwr(3) */
__CREDIRECT(__ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,c16lwr,(char16_t *__restrict __str),_wcslwr,(__str))
#elif defined(__CRT_HAVE_DOS$_wcslwr)
/* >> wcslwr(3) */
__CREDIRECT_DOS(__ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,c16lwr,(char16_t *__restrict __str),_wcslwr,(__str))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcslwr.h>
/* >> wcslwr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16lwr)(char16_t *__restrict __str) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr))((__WCHAR_TYPE__ *)__str); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16lwr.h>
/* >> wcslwr(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16lwr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16lwr)(char16_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16lwr))(__str); })
#endif /* !... */
#if defined(__CRT_HAVE_wcslwr) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcslwr(3) */
__CREDIRECT(__ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,c32lwr,(char32_t *__restrict __str),wcslwr,(__str))
#elif defined(__CRT_HAVE_KOS$wcslwr)
/* >> wcslwr(3) */
__CREDIRECT_KOS(__ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,c32lwr,(char32_t *__restrict __str),wcslwr,(__str))
#elif defined(__CRT_HAVE__wcslwr) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcslwr(3) */
__CREDIRECT(__ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,c32lwr,(char32_t *__restrict __str),_wcslwr,(__str))
#elif defined(__CRT_HAVE_KOS$_wcslwr)
/* >> wcslwr(3) */
__CREDIRECT_KOS(__ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,c32lwr,(char32_t *__restrict __str),_wcslwr,(__str))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcslwr.h>
/* >> wcslwr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32lwr)(char32_t *__restrict __str) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr))((__WCHAR_TYPE__ *)__str); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32lwr.h>
/* >> wcslwr(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32lwr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32lwr)(char32_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32lwr))(__str); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsupr) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsupr(3) */
__CREDIRECT(__ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,c16upr,(char16_t *__restrict __str),wcsupr,(__str))
#elif defined(__CRT_HAVE_DOS$wcsupr)
/* >> wcsupr(3) */
__CREDIRECT_DOS(__ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,c16upr,(char16_t *__restrict __str),wcsupr,(__str))
#elif defined(__CRT_HAVE__wcsupr) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsupr(3) */
__CREDIRECT(__ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,c16upr,(char16_t *__restrict __str),_wcsupr,(__str))
#elif defined(__CRT_HAVE_DOS$_wcsupr)
/* >> wcsupr(3) */
__CREDIRECT_DOS(__ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,c16upr,(char16_t *__restrict __str),_wcsupr,(__str))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsupr.h>
/* >> wcsupr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16upr)(char16_t *__restrict __str) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr))((__WCHAR_TYPE__ *)__str); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16upr.h>
/* >> wcsupr(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16upr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16upr)(char16_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16upr))(__str); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsupr) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsupr(3) */
__CREDIRECT(__ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,c32upr,(char32_t *__restrict __str),wcsupr,(__str))
#elif defined(__CRT_HAVE_KOS$wcsupr)
/* >> wcsupr(3) */
__CREDIRECT_KOS(__ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,c32upr,(char32_t *__restrict __str),wcsupr,(__str))
#elif defined(__CRT_HAVE__wcsupr) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsupr(3) */
__CREDIRECT(__ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,c32upr,(char32_t *__restrict __str),_wcsupr,(__str))
#elif defined(__CRT_HAVE_KOS$_wcsupr)
/* >> wcsupr(3) */
__CREDIRECT_KOS(__ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,c32upr,(char32_t *__restrict __str),_wcsupr,(__str))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsupr.h>
/* >> wcsupr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32upr)(char32_t *__restrict __str) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr))((__WCHAR_TYPE__ *)__str); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32upr.h>
/* >> wcsupr(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32upr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32upr)(char32_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32upr))(__str); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsrev) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsrev(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,c16rev,(char16_t *__restrict __str),wcsrev,(__str))
#elif defined(__CRT_HAVE_DOS$wcsrev)
/* >> wcsrev(3) */
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,c16rev,(char16_t *__restrict __str),wcsrev,(__str))
#elif defined(__CRT_HAVE__wcsrev) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsrev(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,c16rev,(char16_t *__restrict __str),_wcsrev,(__str))
#elif defined(__CRT_HAVE_DOS$_wcsrev)
/* >> wcsrev(3) */
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,c16rev,(char16_t *__restrict __str),_wcsrev,(__str))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsrev.h>
/* >> wcsrev(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INOUT(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16rev)(char16_t *__restrict __str) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrev))((__WCHAR_TYPE__ *)__str); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16rev.h>
/* >> wcsrev(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16rev, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INOUT(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16rev)(char16_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rev))(__str); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsrev) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsrev(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,c32rev,(char32_t *__restrict __str),wcsrev,(__str))
#elif defined(__CRT_HAVE_KOS$wcsrev)
/* >> wcsrev(3) */
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,c32rev,(char32_t *__restrict __str),wcsrev,(__str))
#elif defined(__CRT_HAVE__wcsrev) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsrev(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,c32rev,(char32_t *__restrict __str),_wcsrev,(__str))
#elif defined(__CRT_HAVE_KOS$_wcsrev)
/* >> wcsrev(3) */
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,c32rev,(char32_t *__restrict __str),_wcsrev,(__str))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsrev.h>
/* >> wcsrev(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INOUT(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32rev)(char32_t *__restrict __str) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrev))((__WCHAR_TYPE__ *)__str); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32rev.h>
/* >> wcsrev(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32rev, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INOUT(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32rev)(char32_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32rev))(__str); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnrev) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsnrev(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nrev,(char16_t *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnrev,(__str,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnrev)
/* >> wcsnrev(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nrev,(char16_t *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnrev,(__str,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsnrev.h>
/* >> wcsnrev(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nrev)(char16_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrev))((__WCHAR_TYPE__ *)__str, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16nrev.h>
/* >> wcsnrev(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16nrev, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nrev)(char16_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nrev))(__str, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnrev) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsnrev(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nrev,(char32_t *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnrev,(__str,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsnrev)
/* >> wcsnrev(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nrev,(char32_t *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnrev,(__str,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsnrev.h>
/* >> wcsnrev(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nrev)(char32_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrev))((__WCHAR_TYPE__ *)__str, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32nrev.h>
/* >> wcsnrev(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32nrev, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nrev)(char32_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nrev))(__str, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsset) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsset(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,c16set,(char16_t *__restrict __str, int __ch),wcsset,(__str,__ch))
#elif defined(__CRT_HAVE_DOS$wcsset)
/* >> wcsset(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,c16set,(char16_t *__restrict __str, int __ch),wcsset,(__str,__ch))
#elif defined(__CRT_HAVE__wcsset) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsset(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,c16set,(char16_t *__restrict __str, int __ch),_wcsset,(__str,__ch))
#elif defined(__CRT_HAVE_DOS$_wcsset)
/* >> wcsset(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,c16set,(char16_t *__restrict __str, int __ch),_wcsset,(__str,__ch))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsset.h>
/* >> wcsset(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INOUT(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16set)(char16_t *__restrict __str, int __ch) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsset))((__WCHAR_TYPE__ *)__str, __ch); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16set.h>
/* >> wcsset(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16set, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INOUT(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16set)(char16_t *__restrict __str, int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16set))(__str, __ch); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsset) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsset(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,c32set,(char32_t *__restrict __str, int __ch),wcsset,(__str,__ch))
#elif defined(__CRT_HAVE_KOS$wcsset)
/* >> wcsset(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,c32set,(char32_t *__restrict __str, int __ch),wcsset,(__str,__ch))
#elif defined(__CRT_HAVE__wcsset) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsset(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,c32set,(char32_t *__restrict __str, int __ch),_wcsset,(__str,__ch))
#elif defined(__CRT_HAVE_KOS$_wcsset)
/* >> wcsset(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,c32set,(char32_t *__restrict __str, int __ch),_wcsset,(__str,__ch))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsset.h>
/* >> wcsset(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INOUT(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32set)(char32_t *__restrict __str, int __ch) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsset))((__WCHAR_TYPE__ *)__str, __ch); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32set.h>
/* >> wcsset(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32set, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INOUT(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32set)(char32_t *__restrict __str, int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32set))(__str, __ch); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnset) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsnset(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INOUTS(1, 3),char16_t *,__NOTHROW_NCX,c16nset,(char16_t *__restrict __str, char16_t __ch, __SIZE_TYPE__ __maxlen),wcsnset,(__str,__ch,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnset)
/* >> wcsnset(3) */
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_INOUTS(1, 3),char16_t *,__NOTHROW_NCX,c16nset,(char16_t *__restrict __str, char16_t __ch, __SIZE_TYPE__ __maxlen),wcsnset,(__str,__ch,__maxlen))
#elif defined(__CRT_HAVE__wcsnset) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsnset(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INOUTS(1, 3),char16_t *,__NOTHROW_NCX,c16nset,(char16_t *__restrict __str, char16_t __ch, __SIZE_TYPE__ __maxlen),_wcsnset,(__str,__ch,__maxlen))
#elif defined(__CRT_HAVE_DOS$_wcsnset)
/* >> wcsnset(3) */
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_INOUTS(1, 3),char16_t *,__NOTHROW_NCX,c16nset,(char16_t *__restrict __str, char16_t __ch, __SIZE_TYPE__ __maxlen),_wcsnset,(__str,__ch,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsnset.h>
/* >> wcsnset(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INOUTS(1, 3) char16_t *__NOTHROW_NCX(__LIBDCALL c16nset)(char16_t *__restrict __str, char16_t __ch, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnset))((__WCHAR_TYPE__ *)__str, (__WCHAR_TYPE__)__ch, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16nset.h>
/* >> wcsnset(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16nset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INOUTS(1, 3) char16_t *__NOTHROW_NCX(__LIBDCALL c16nset)(char16_t *__restrict __str, char16_t __ch, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nset))(__str, __ch, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnset) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsnset(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INOUTS(1, 3),char32_t *,__NOTHROW_NCX,c32nset,(char32_t *__restrict __str, char32_t __ch, __SIZE_TYPE__ __maxlen),wcsnset,(__str,__ch,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsnset)
/* >> wcsnset(3) */
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_INOUTS(1, 3),char32_t *,__NOTHROW_NCX,c32nset,(char32_t *__restrict __str, char32_t __ch, __SIZE_TYPE__ __maxlen),wcsnset,(__str,__ch,__maxlen))
#elif defined(__CRT_HAVE__wcsnset) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsnset(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INOUTS(1, 3),char32_t *,__NOTHROW_NCX,c32nset,(char32_t *__restrict __str, char32_t __ch, __SIZE_TYPE__ __maxlen),_wcsnset,(__str,__ch,__maxlen))
#elif defined(__CRT_HAVE_KOS$_wcsnset)
/* >> wcsnset(3) */
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_INOUTS(1, 3),char32_t *,__NOTHROW_NCX,c32nset,(char32_t *__restrict __str, char32_t __ch, __SIZE_TYPE__ __maxlen),_wcsnset,(__str,__ch,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsnset.h>
/* >> wcsnset(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INOUTS(1, 3) char32_t *__NOTHROW_NCX(__LIBKCALL c32nset)(char32_t *__restrict __str, char32_t __ch, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnset))((__WCHAR_TYPE__ *)__str, (__WCHAR_TYPE__)__ch, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32nset.h>
/* >> wcsnset(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32nset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INOUTS(1, 3) char32_t *__NOTHROW_NCX(__LIBKCALL c32nset)(char32_t *__restrict __str, char32_t __ch, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nset))(__str, __ch, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wmemcmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fuzzy_wmemcmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16memcmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_chars, char16_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_wmemcmp,(__s1,__s1_chars,__s2,__s2_chars))
#elif defined(__CRT_HAVE_DOS$fuzzy_wmemcmp)
/* >> fuzzy_wmemcmp(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16memcmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_chars, char16_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_wmemcmp,(__s1,__s1_chars,__s2,__s2_chars))
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE_fuzzy_memcmpw) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fuzzy_wmemcmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16memcmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_chars, char16_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_memcmpw,(__s1,__s1_chars,__s2,__s2_chars))
#elif defined(__CRT_HAVE_DOS$fuzzy_memcmpw)
/* >> fuzzy_wmemcmp(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16memcmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_chars, char16_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_memcmpw,(__s1,__s1_chars,__s2,__s2_chars))
#else /* ... */
#include <libc/local/string/fuzzy_memcmpw.h>
/* >> fuzzy_wmemcmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16memcmp)(char16_t const *__s1, __SIZE_TYPE__ __s1_chars, char16_t const *__s2, __SIZE_TYPE__ __s2_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcmpw))((void const *)__s1, __s1_chars, (void const *)__s2, __s2_chars); }
#endif /* !... */
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wmemcmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fuzzy_wmemcmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32memcmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_chars, char32_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_wmemcmp,(__s1,__s1_chars,__s2,__s2_chars))
#elif defined(__CRT_HAVE_KOS$fuzzy_wmemcmp)
/* >> fuzzy_wmemcmp(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32memcmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_chars, char32_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_wmemcmp,(__s1,__s1_chars,__s2,__s2_chars))
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE_fuzzy_memcmpl) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fuzzy_wmemcmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32memcmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_chars, char32_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_memcmpl,(__s1,__s1_chars,__s2,__s2_chars))
#elif defined(__CRT_HAVE_KOS$fuzzy_memcmpl)
/* >> fuzzy_wmemcmp(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32memcmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_chars, char32_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_memcmpl,(__s1,__s1_chars,__s2,__s2_chars))
#else /* ... */
#include <libc/local/string/fuzzy_memcmpl.h>
/* >> fuzzy_wmemcmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32memcmp)(char32_t const *__s1, __SIZE_TYPE__ __s1_chars, char32_t const *__s2, __SIZE_TYPE__ __s2_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcmpl))((void const *)__s1, __s1_chars, (void const *)__s2, __s2_chars); }
#endif /* !... */
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wmemcasecmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fuzzy_wmemcasecmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16memcasecmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes),fuzzy_wmemcasecmp,(__s1,__s1_bytes,__s2,__s2_bytes))
#elif defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp)
/* >> fuzzy_wmemcasecmp(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16memcasecmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes),fuzzy_wmemcasecmp,(__s1,__s1_bytes,__s2,__s2_bytes))
#elif !defined(__NO_MALLOCA) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/fuzzy_wmemcasecmp.h>
/* >> fuzzy_wmemcasecmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16memcasecmp)(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcasecmp))((__WCHAR_TYPE__ const *)__s1, __s1_bytes, (__WCHAR_TYPE__ const *)__s2, __s2_bytes); }
#elif !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c16memcasecmp.h>
/* >> fuzzy_wmemcasecmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16memcasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16memcasecmp)(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16memcasecmp))(__s1, __s1_bytes, __s2, __s2_bytes); })
#endif /* ... */
#if defined(__CRT_HAVE_fuzzy_wmemcasecmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fuzzy_wmemcasecmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32memcasecmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_bytes, char32_t const *__s2, __SIZE_TYPE__ __s2_bytes),fuzzy_wmemcasecmp,(__s1,__s1_bytes,__s2,__s2_bytes))
#elif defined(__CRT_HAVE_KOS$fuzzy_wmemcasecmp)
/* >> fuzzy_wmemcasecmp(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32memcasecmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_bytes, char32_t const *__s2, __SIZE_TYPE__ __s2_bytes),fuzzy_wmemcasecmp,(__s1,__s1_bytes,__s2,__s2_bytes))
#elif !defined(__NO_MALLOCA) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/fuzzy_wmemcasecmp.h>
/* >> fuzzy_wmemcasecmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32memcasecmp)(char32_t const *__s1, __SIZE_TYPE__ __s1_bytes, char32_t const *__s2, __SIZE_TYPE__ __s2_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcasecmp))((__WCHAR_TYPE__ const *)__s1, __s1_bytes, (__WCHAR_TYPE__ const *)__s2, __s2_bytes); }
#elif !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c32memcasecmp.h>
/* >> fuzzy_wmemcasecmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32memcasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32memcasecmp)(char32_t const *__s1, __SIZE_TYPE__ __s1_bytes, char32_t const *__s2, __SIZE_TYPE__ __s2_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32memcasecmp))(__s1, __s1_bytes, __s2, __s2_bytes); })
#endif /* ... */
#if defined(__CRT_HAVE_fuzzy_wcscmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fuzzy_wcscmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16scmp,(char16_t const *__s1, char16_t const *__s2),fuzzy_wcscmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$fuzzy_wcscmp)
/* >> fuzzy_wcscmp(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16scmp,(char16_t const *__s1, char16_t const *__s2),fuzzy_wcscmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/fuzzy_wcscmp.h>
/* >> fuzzy_wcscmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16scmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE_fuzzy_memcmpw) || (defined(__CRT_HAVE_DOS$fuzzy_wmemcmp) && defined(__LIBCCALL_IS_LIBDCALL)) || !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c16scmp.h>
/* >> fuzzy_wcscmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16scmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16scmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16scmp))(__s1, __s2); })
#endif /* __CRT_HAVE_fuzzy_memcmpw || (__CRT_HAVE_DOS$fuzzy_wmemcmp && __LIBCCALL_IS_LIBDCALL) || !__NO_MALLOCA */
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wcscmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fuzzy_wcscmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32scmp,(char32_t const *__s1, char32_t const *__s2),fuzzy_wcscmp,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$fuzzy_wcscmp)
/* >> fuzzy_wcscmp(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32scmp,(char32_t const *__s1, char32_t const *__s2),fuzzy_wcscmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/fuzzy_wcscmp.h>
/* >> fuzzy_wcscmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32scmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE_fuzzy_memcmpl) || (defined(__CRT_HAVE_KOS$fuzzy_wmemcmp) && defined(__LIBCCALL_IS_LIBKCALL)) || !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c32scmp.h>
/* >> fuzzy_wcscmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32scmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32scmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32scmp))(__s1, __s2); })
#endif /* __CRT_HAVE_fuzzy_memcmpl || (__CRT_HAVE_KOS$fuzzy_wmemcmp && __LIBCCALL_IS_LIBKCALL) || !__NO_MALLOCA */
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wcsncmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fuzzy_wcsncmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16sncmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen),fuzzy_wcsncmp,(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif defined(__CRT_HAVE_DOS$fuzzy_wcsncmp)
/* >> fuzzy_wcsncmp(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16sncmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen),fuzzy_wcsncmp,(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/fuzzy_wcsncmp.h>
/* >> fuzzy_wcsncmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16sncmp)(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncmp))((__WCHAR_TYPE__ const *)__s1, __s1_maxlen, (__WCHAR_TYPE__ const *)__s2, __s2_maxlen); }
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE_fuzzy_memcmpw) || (defined(__CRT_HAVE_DOS$fuzzy_wmemcmp) && defined(__LIBCCALL_IS_LIBDCALL)) || !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c16sncmp.h>
/* >> fuzzy_wcsncmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16sncmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16sncmp)(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16sncmp))(__s1, __s1_maxlen, __s2, __s2_maxlen); })
#endif /* __CRT_HAVE_fuzzy_memcmpw || (__CRT_HAVE_DOS$fuzzy_wmemcmp && __LIBCCALL_IS_LIBDCALL) || !__NO_MALLOCA */
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wcsncmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fuzzy_wcsncmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32sncmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen),fuzzy_wcsncmp,(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif defined(__CRT_HAVE_KOS$fuzzy_wcsncmp)
/* >> fuzzy_wcsncmp(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32sncmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen),fuzzy_wcsncmp,(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/fuzzy_wcsncmp.h>
/* >> fuzzy_wcsncmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32sncmp)(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncmp))((__WCHAR_TYPE__ const *)__s1, __s1_maxlen, (__WCHAR_TYPE__ const *)__s2, __s2_maxlen); }
#else /* ... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE_fuzzy_memcmpl) || (defined(__CRT_HAVE_KOS$fuzzy_wmemcmp) && defined(__LIBCCALL_IS_LIBKCALL)) || !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c32sncmp.h>
/* >> fuzzy_wcsncmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32sncmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32sncmp)(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32sncmp))(__s1, __s1_maxlen, __s2, __s2_maxlen); })
#endif /* __CRT_HAVE_fuzzy_memcmpl || (__CRT_HAVE_KOS$fuzzy_wmemcmp && __LIBCCALL_IS_LIBKCALL) || !__NO_MALLOCA */
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wcscasecmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fuzzy_wcscasecmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16scasecmp,(char16_t const *__s1, char16_t const *__s2),fuzzy_wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$fuzzy_wcscasecmp)
/* >> fuzzy_wcscasecmp(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16scasecmp,(char16_t const *__s1, char16_t const *__s2),fuzzy_wcscasecmp,(__s1,__s2))
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp) || !defined(__NO_MALLOCA)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/fuzzy_wcscasecmp.h>
/* >> fuzzy_wcscasecmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16scasecmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscasecmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp) || !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c16scasecmp.h>
/* >> fuzzy_wcscasecmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16scasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16scasecmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16scasecmp))(__s1, __s2); })
#endif /* ... */
#if defined(__CRT_HAVE_fuzzy_wcscasecmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fuzzy_wcscasecmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32scasecmp,(char32_t const *__s1, char32_t const *__s2),fuzzy_wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$fuzzy_wcscasecmp)
/* >> fuzzy_wcscasecmp(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32scasecmp,(char32_t const *__s1, char32_t const *__s2),fuzzy_wcscasecmp,(__s1,__s2))
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp) || !defined(__NO_MALLOCA)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/fuzzy_wcscasecmp.h>
/* >> fuzzy_wcscasecmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32scasecmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscasecmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fuzzy_wmemcasecmp) || !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c32scasecmp.h>
/* >> fuzzy_wcscasecmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32scasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32scasecmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32scasecmp))(__s1, __s2); })
#endif /* ... */
#if defined(__CRT_HAVE_fuzzy_wcsncasecmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fuzzy_wcsncasecmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16sncasecmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen),fuzzy_wcsncasecmp,(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif defined(__CRT_HAVE_DOS$fuzzy_wcsncasecmp)
/* >> fuzzy_wcsncasecmp(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16sncasecmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen),fuzzy_wcsncasecmp,(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp) || !defined(__NO_MALLOCA)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/fuzzy_wcsncasecmp.h>
/* >> fuzzy_wcsncasecmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16sncasecmp)(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncasecmp))((__WCHAR_TYPE__ const *)__s1, __s1_maxlen, (__WCHAR_TYPE__ const *)__s2, __s2_maxlen); }
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp) || !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c16sncasecmp.h>
/* >> fuzzy_wcsncasecmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16sncasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16sncasecmp)(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16sncasecmp))(__s1, __s1_maxlen, __s2, __s2_maxlen); })
#endif /* ... */
#if defined(__CRT_HAVE_fuzzy_wcsncasecmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fuzzy_wcsncasecmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32sncasecmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen),fuzzy_wcsncasecmp,(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif defined(__CRT_HAVE_KOS$fuzzy_wcsncasecmp)
/* >> fuzzy_wcsncasecmp(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32sncasecmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen),fuzzy_wcsncasecmp,(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp) || !defined(__NO_MALLOCA)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/fuzzy_wcsncasecmp.h>
/* >> fuzzy_wcsncasecmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32sncasecmp)(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncasecmp))((__WCHAR_TYPE__ const *)__s1, __s1_maxlen, (__WCHAR_TYPE__ const *)__s2, __s2_maxlen); }
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fuzzy_wmemcasecmp) || !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c32sncasecmp.h>
/* >> fuzzy_wcsncasecmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32sncasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32sncasecmp)(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32sncasecmp))(__s1, __s1_maxlen, __s2, __s2_maxlen); })
#endif /* ... */
#if defined(__CRT_HAVE_wildwcscmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wildwcscmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wildc16cmp,(char16_t const *__pattern, char16_t const *__string),wildwcscmp,(__pattern,__string))
#elif defined(__CRT_HAVE_DOS$wildwcscmp)
/* >> wildwcscmp(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wildc16cmp,(char16_t const *__pattern, char16_t const *__string),wildwcscmp,(__pattern,__string))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wildwcscmp.h>
/* >> wildwcscmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBDCALL wildc16cmp)(char16_t const *__pattern, char16_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscmp))((__WCHAR_TYPE__ const *)__pattern, (__WCHAR_TYPE__ const *)__string); }
#else /* ... */
#include <libc/local/parts.uchar.string/wildc16cmp.h>
/* >> wildwcscmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wildc16cmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBDCALL wildc16cmp)(char16_t const *__pattern, char16_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildc16cmp))(__pattern, __string); })
#endif /* !... */
#if defined(__CRT_HAVE_wildwcscmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wildwcscmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wildc32cmp,(char32_t const *__pattern, char32_t const *__string),wildwcscmp,(__pattern,__string))
#elif defined(__CRT_HAVE_KOS$wildwcscmp)
/* >> wildwcscmp(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wildc32cmp,(char32_t const *__pattern, char32_t const *__string),wildwcscmp,(__pattern,__string))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wildwcscmp.h>
/* >> wildwcscmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBKCALL wildc32cmp)(char32_t const *__pattern, char32_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscmp))((__WCHAR_TYPE__ const *)__pattern, (__WCHAR_TYPE__ const *)__string); }
#else /* ... */
#include <libc/local/parts.uchar.string/wildc32cmp.h>
/* >> wildwcscmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wildc32cmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBKCALL wildc32cmp)(char32_t const *__pattern, char32_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildc32cmp))(__pattern, __string); })
#endif /* !... */
#if defined(__CRT_HAVE_wildwcscasecmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wildwcscasecmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wildc16casecmp,(char16_t const *__pattern, char16_t const *__string),wildwcscasecmp,(__pattern,__string))
#elif defined(__CRT_HAVE_DOS$wildwcscasecmp)
/* >> wildwcscasecmp(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wildc16casecmp,(char16_t const *__pattern, char16_t const *__string),wildwcscasecmp,(__pattern,__string))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wildwcscasecmp.h>
/* >> wildwcscasecmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBDCALL wildc16casecmp)(char16_t const *__pattern, char16_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscasecmp))((__WCHAR_TYPE__ const *)__pattern, (__WCHAR_TYPE__ const *)__string); }
#else /* ... */
#include <libc/local/parts.uchar.string/wildc16casecmp.h>
/* >> wildwcscasecmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wildc16casecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBDCALL wildc16casecmp)(char16_t const *__pattern, char16_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildc16casecmp))(__pattern, __string); })
#endif /* !... */
#if defined(__CRT_HAVE_wildwcscasecmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wildwcscasecmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wildc32casecmp,(char32_t const *__pattern, char32_t const *__string),wildwcscasecmp,(__pattern,__string))
#elif defined(__CRT_HAVE_KOS$wildwcscasecmp)
/* >> wildwcscasecmp(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wildc32casecmp,(char32_t const *__pattern, char32_t const *__string),wildwcscasecmp,(__pattern,__string))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wildwcscasecmp.h>
/* >> wildwcscasecmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBKCALL wildc32casecmp)(char32_t const *__pattern, char32_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscasecmp))((__WCHAR_TYPE__ const *)__pattern, (__WCHAR_TYPE__ const *)__string); }
#else /* ... */
#include <libc/local/parts.uchar.string/wildc32casecmp.h>
/* >> wildwcscasecmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wildc32casecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBKCALL wildc32casecmp)(char32_t const *__pattern, char32_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildc32casecmp))(__pattern, __string); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsverscmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsverscmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16verscmp,(char16_t const *__s1, char16_t const *__s2),wcsverscmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcsverscmp)
/* >> wcsverscmp(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16verscmp,(char16_t const *__s1, char16_t const *__s2),wcsverscmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsverscmp.h>
/* >> wcsverscmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBDCALL c16verscmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsverscmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16verscmp.h>
/* >> wcsverscmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16verscmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBDCALL c16verscmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16verscmp))(__s1, __s2); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsverscmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsverscmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32verscmp,(char32_t const *__s1, char32_t const *__s2),wcsverscmp,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$wcsverscmp)
/* >> wcsverscmp(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32verscmp,(char32_t const *__s1, char32_t const *__s2),wcsverscmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsverscmp.h>
/* >> wcsverscmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBKCALL c32verscmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsverscmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32verscmp.h>
/* >> wcsverscmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32verscmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBKCALL c32verscmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32verscmp))(__s1, __s2); })
#endif /* !... */
#if defined(__CRT_HAVE_wcslstrip) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcslstrip(3) */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16lstrip,(char16_t const *__str),wcslstrip,(__str))
#elif defined(__CRT_HAVE_DOS$wcslstrip)
/* >> wcslstrip(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16lstrip,(char16_t const *__str),wcslstrip,(__str))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcslstrip.h>
/* >> wcslstrip(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16lstrip)(char16_t const *__str) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslstrip))((__WCHAR_TYPE__ const *)__str); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16lstrip.h>
/* >> wcslstrip(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16lstrip, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16lstrip)(char16_t const *__str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16lstrip))(__str); })
#endif /* !... */
#if defined(__CRT_HAVE_wcslstrip) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcslstrip(3) */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32lstrip,(char32_t const *__str),wcslstrip,(__str))
#elif defined(__CRT_HAVE_KOS$wcslstrip)
/* >> wcslstrip(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32lstrip,(char32_t const *__str),wcslstrip,(__str))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcslstrip.h>
/* >> wcslstrip(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32lstrip)(char32_t const *__str) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslstrip))((__WCHAR_TYPE__ const *)__str); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32lstrip.h>
/* >> wcslstrip(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32lstrip, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32lstrip)(char32_t const *__str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32lstrip))(__str); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsrstrip) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsrstrip(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16rstrip,(char16_t *__str),wcsrstrip,(__str))
#elif defined(__CRT_HAVE_DOS$wcsrstrip)
/* >> wcsrstrip(3) */
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16rstrip,(char16_t *__str),wcsrstrip,(__str))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsrstrip.h>
/* >> wcsrstrip(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16rstrip)(char16_t *__str) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrstrip))((__WCHAR_TYPE__ *)__str); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16rstrip.h>
/* >> wcsrstrip(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16rstrip, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16rstrip)(char16_t *__str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rstrip))(__str); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsrstrip) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsrstrip(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32rstrip,(char32_t *__str),wcsrstrip,(__str))
#elif defined(__CRT_HAVE_KOS$wcsrstrip)
/* >> wcsrstrip(3) */
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32rstrip,(char32_t *__str),wcsrstrip,(__str))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsrstrip.h>
/* >> wcsrstrip(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32rstrip)(char32_t *__str) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrstrip))((__WCHAR_TYPE__ *)__str); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32rstrip.h>
/* >> wcsrstrip(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32rstrip, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32rstrip)(char32_t *__str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32rstrip))(__str); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsstrip) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsstrip(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16strip,(char16_t *__str),wcsstrip,(__str))
#elif defined(__CRT_HAVE_DOS$wcsstrip)
/* >> wcsstrip(3) */
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char16_t *,__NOTHROW_NCX,c16strip,(char16_t *__str),wcsstrip,(__str))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsstrip.h>
/* >> wcsstrip(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16strip)(char16_t *__str) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstrip))((__WCHAR_TYPE__ *)__str); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16strip.h>
/* >> wcsstrip(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16strip, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16strip)(char16_t *__str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16strip))(__str); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsstrip) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsstrip(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32strip,(char32_t *__str),wcsstrip,(__str))
#elif defined(__CRT_HAVE_KOS$wcsstrip)
/* >> wcsstrip(3) */
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char32_t *,__NOTHROW_NCX,c32strip,(char32_t *__str),wcsstrip,(__str))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsstrip.h>
/* >> wcsstrip(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32strip)(char32_t *__str) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstrip))((__WCHAR_TYPE__ *)__str); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32strip.h>
/* >> wcsstrip(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32strip, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32strip)(char32_t *__str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32strip))(__str); })
#endif /* !... */
#if defined(__CRT_HAVE_wmemcasecmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wmemcasecmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16memcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars),wmemcasecmp,(__s1,__s2,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmemcasecmp)
/* >> wmemcasecmp(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16memcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars),wmemcasecmp,(__s1,__s2,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wmemcasecmp.h>
/* >> wmemcasecmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16memcasecmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemcasecmp))(__s1, __s2, __num_chars); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16memcasecmp.h>
/* >> wmemcasecmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16memcasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16memcasecmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16memcasecmp))(__s1, __s2, __num_chars); })
#endif /* !... */
#if defined(__CRT_HAVE_wmemcasecmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wmemcasecmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32memcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars),wmemcasecmp,(__s1,__s2,__num_chars))
#elif defined(__CRT_HAVE_KOS$wmemcasecmp)
/* >> wmemcasecmp(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32memcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars),wmemcasecmp,(__s1,__s2,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wmemcasecmp.h>
/* >> wmemcasecmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32memcasecmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemcasecmp))(__s1, __s2, __num_chars); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32memcasecmp.h>
/* >> wmemcasecmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32memcasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32memcasecmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32memcasecmp))(__s1, __s2, __num_chars); })
#endif /* !... */
#ifdef __USE_XOPEN2K8
#if defined(__CRT_HAVE_wmemcasecmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wmemcasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16memcasecmp_l,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars, __locale_t __locale),wmemcasecmp_l,(__s1,__s2,__num_chars,__locale))
#elif defined(__CRT_HAVE_DOS$wmemcasecmp_l)
/* >> wmemcasecmp_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16memcasecmp_l,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars, __locale_t __locale),wmemcasecmp_l,(__s1,__s2,__num_chars,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wmemcasecmp_l.h>
/* >> wmemcasecmp_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16memcasecmp_l)(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemcasecmp_l))(__s1, __s2, __num_chars, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16memcasecmp_l.h>
/* >> wmemcasecmp_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16memcasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16memcasecmp_l)(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16memcasecmp_l))(__s1, __s2, __num_chars, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wmemcasecmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wmemcasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32memcasecmp_l,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars, __locale_t __locale),wmemcasecmp_l,(__s1,__s2,__num_chars,__locale))
#elif defined(__CRT_HAVE_KOS$wmemcasecmp_l)
/* >> wmemcasecmp_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32memcasecmp_l,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars, __locale_t __locale),wmemcasecmp_l,(__s1,__s2,__num_chars,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wmemcasecmp_l.h>
/* >> wmemcasecmp_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32memcasecmp_l)(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemcasecmp_l))(__s1, __s2, __num_chars, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32memcasecmp_l.h>
/* >> wmemcasecmp_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32memcasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32memcasecmp_l)(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32memcasecmp_l))(__s1, __s2, __num_chars, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscasestr_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcscasestr_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char16_t *,__NOTHROW_NCX,c16casestr_l,(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale),wcscasestr_l,(__haystack,__needle,__locale))
#elif defined(__CRT_HAVE_DOS$wcscasestr_l)
/* >> wcscasestr_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char16_t *,__NOTHROW_NCX,c16casestr_l,(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale),wcscasestr_l,(__haystack,__needle,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcscasestr_l.h>
/* >> wcscasestr_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char16_t *__NOTHROW_NCX(__LIBDCALL c16casestr_l)(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr_l))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16casestr_l.h>
/* >> wcscasestr_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16casestr_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char16_t *__NOTHROW_NCX(__LIBDCALL c16casestr_l)(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16casestr_l))(__haystack, __needle, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscasestr_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcscasestr_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char32_t *,__NOTHROW_NCX,c32casestr_l,(char32_t const *__haystack, char32_t const *__needle, __locale_t __locale),wcscasestr_l,(__haystack,__needle,__locale))
#elif defined(__CRT_HAVE_KOS$wcscasestr_l)
/* >> wcscasestr_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char32_t *,__NOTHROW_NCX,c32casestr_l,(char32_t const *__haystack, char32_t const *__needle, __locale_t __locale),wcscasestr_l,(__haystack,__needle,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcscasestr_l.h>
/* >> wcscasestr_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char32_t *__NOTHROW_NCX(__LIBKCALL c32casestr_l)(char32_t const *__haystack, char32_t const *__needle, __locale_t __locale) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr_l))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32casestr_l.h>
/* >> wcscasestr_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32casestr_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char32_t *__NOTHROW_NCX(__LIBKCALL c32casestr_l)(char32_t const *__haystack, char32_t const *__needle, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32casestr_l))(__haystack, __needle, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscasecmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcscasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16casecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$wcscasecmp_l)
/* >> wcscasecmp_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16casecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcscasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16casecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsicmp_l)
/* >> wcscasecmp_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16casecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___wcscasecmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcscasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16casecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),__wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$__wcscasecmp_l)
/* >> wcscasecmp_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16casecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),__wcscasecmp_l,(__s1,__s2,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcscasecmp_l.h>
/* >> wcscasecmp_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBDCALL c16casecmp_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16casecmp_l.h>
/* >> wcscasecmp_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16casecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBDCALL c16casecmp_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16casecmp_l))(__s1, __s2, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscasecmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcscasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32casecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_KOS$wcscasecmp_l)
/* >> wcscasecmp_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32casecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcscasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32casecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_KOS$_wcsicmp_l)
/* >> wcscasecmp_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32casecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___wcscasecmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcscasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32casecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),__wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_KOS$__wcscasecmp_l)
/* >> wcscasecmp_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32casecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),__wcscasecmp_l,(__s1,__s2,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcscasecmp_l.h>
/* >> wcscasecmp_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBKCALL c32casecmp_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32casecmp_l.h>
/* >> wcscasecmp_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32casecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBKCALL c32casecmp_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32casecmp_l))(__s1, __s2, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncasecmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsncasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16ncasecmp_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$wcsncasecmp_l)
/* >> wcsncasecmp_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16ncasecmp_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsncasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16ncasecmp_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsnicmp_l)
/* >> wcsncasecmp_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16ncasecmp_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE___wcsncasecmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsncasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16ncasecmp_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$__wcsncasecmp_l)
/* >> wcsncasecmp_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16ncasecmp_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsncasecmp_l.h>
/* >> wcsncasecmp_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBDCALL c16ncasecmp_l)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16ncasecmp_l.h>
/* >> wcsncasecmp_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ncasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBDCALL c16ncasecmp_l)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ncasecmp_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncasecmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsncasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32ncasecmp_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_KOS$wcsncasecmp_l)
/* >> wcsncasecmp_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32ncasecmp_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsncasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32ncasecmp_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_KOS$_wcsnicmp_l)
/* >> wcsncasecmp_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32ncasecmp_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE___wcsncasecmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsncasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32ncasecmp_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_KOS$__wcsncasecmp_l)
/* >> wcsncasecmp_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32ncasecmp_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsncasecmp_l.h>
/* >> wcsncasecmp_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBKCALL c32ncasecmp_l)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32ncasecmp_l.h>
/* >> wcsncasecmp_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ncasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBKCALL c32ncasecmp_l)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ncasecmp_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsxfrm_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsxfrm_l(3) */
__CREDIRECT(__ATTR_INS(2, 3) __ATTR_OUTS(1, 3),__SIZE_TYPE__,__NOTHROW_NCX,c16xfrm_l,(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen, __locale_t __locale),wcsxfrm_l,(__dst,__src,__buflen,__locale))
#elif defined(__CRT_HAVE_DOS$wcsxfrm_l)
/* >> wcsxfrm_l(3) */
__CREDIRECT_DOS(__ATTR_INS(2, 3) __ATTR_OUTS(1, 3),__SIZE_TYPE__,__NOTHROW_NCX,c16xfrm_l,(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen, __locale_t __locale),wcsxfrm_l,(__dst,__src,__buflen,__locale))
#elif defined(__CRT_HAVE__wcsxfrm_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsxfrm_l(3) */
__CREDIRECT(__ATTR_INS(2, 3) __ATTR_OUTS(1, 3),__SIZE_TYPE__,__NOTHROW_NCX,c16xfrm_l,(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen, __locale_t __locale),_wcsxfrm_l,(__dst,__src,__buflen,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsxfrm_l)
/* >> wcsxfrm_l(3) */
__CREDIRECT_DOS(__ATTR_INS(2, 3) __ATTR_OUTS(1, 3),__SIZE_TYPE__,__NOTHROW_NCX,c16xfrm_l,(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen, __locale_t __locale),_wcsxfrm_l,(__dst,__src,__buflen,__locale))
#elif defined(__CRT_HAVE___wcsxfrm_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsxfrm_l(3) */
__CREDIRECT(__ATTR_INS(2, 3) __ATTR_OUTS(1, 3),__SIZE_TYPE__,__NOTHROW_NCX,c16xfrm_l,(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen, __locale_t __locale),__wcsxfrm_l,(__dst,__src,__buflen,__locale))
#elif defined(__CRT_HAVE_DOS$__wcsxfrm_l)
/* >> wcsxfrm_l(3) */
__CREDIRECT_DOS(__ATTR_INS(2, 3) __ATTR_OUTS(1, 3),__SIZE_TYPE__,__NOTHROW_NCX,c16xfrm_l,(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen, __locale_t __locale),__wcsxfrm_l,(__dst,__src,__buflen,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsxfrm_l.h>
/* >> wcsxfrm_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16xfrm_l)(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm_l))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __buflen, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16xfrm_l.h>
/* >> wcsxfrm_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16xfrm_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16xfrm_l)(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16xfrm_l))(__dst, __src, __buflen, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsxfrm_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsxfrm_l(3) */
__CREDIRECT(__ATTR_INS(2, 3) __ATTR_OUTS(1, 3),__SIZE_TYPE__,__NOTHROW_NCX,c32xfrm_l,(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen, __locale_t __locale),wcsxfrm_l,(__dst,__src,__buflen,__locale))
#elif defined(__CRT_HAVE_KOS$wcsxfrm_l)
/* >> wcsxfrm_l(3) */
__CREDIRECT_KOS(__ATTR_INS(2, 3) __ATTR_OUTS(1, 3),__SIZE_TYPE__,__NOTHROW_NCX,c32xfrm_l,(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen, __locale_t __locale),wcsxfrm_l,(__dst,__src,__buflen,__locale))
#elif defined(__CRT_HAVE__wcsxfrm_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsxfrm_l(3) */
__CREDIRECT(__ATTR_INS(2, 3) __ATTR_OUTS(1, 3),__SIZE_TYPE__,__NOTHROW_NCX,c32xfrm_l,(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen, __locale_t __locale),_wcsxfrm_l,(__dst,__src,__buflen,__locale))
#elif defined(__CRT_HAVE_KOS$_wcsxfrm_l)
/* >> wcsxfrm_l(3) */
__CREDIRECT_KOS(__ATTR_INS(2, 3) __ATTR_OUTS(1, 3),__SIZE_TYPE__,__NOTHROW_NCX,c32xfrm_l,(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen, __locale_t __locale),_wcsxfrm_l,(__dst,__src,__buflen,__locale))
#elif defined(__CRT_HAVE___wcsxfrm_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsxfrm_l(3) */
__CREDIRECT(__ATTR_INS(2, 3) __ATTR_OUTS(1, 3),__SIZE_TYPE__,__NOTHROW_NCX,c32xfrm_l,(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen, __locale_t __locale),__wcsxfrm_l,(__dst,__src,__buflen,__locale))
#elif defined(__CRT_HAVE_KOS$__wcsxfrm_l)
/* >> wcsxfrm_l(3) */
__CREDIRECT_KOS(__ATTR_INS(2, 3) __ATTR_OUTS(1, 3),__SIZE_TYPE__,__NOTHROW_NCX,c32xfrm_l,(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen, __locale_t __locale),__wcsxfrm_l,(__dst,__src,__buflen,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsxfrm_l.h>
/* >> wcsxfrm_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32xfrm_l)(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm_l))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __buflen, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32xfrm_l.h>
/* >> wcsxfrm_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32xfrm_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32xfrm_l)(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32xfrm_l))(__dst, __src, __buflen, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscoll_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcscoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16coll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$wcscoll_l)
/* >> wcscoll_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16coll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcscoll_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcscoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16coll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$_wcscoll_l)
/* >> wcscoll_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16coll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___wcscoll_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcscoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16coll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),__wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$__wcscoll_l)
/* >> wcscoll_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16coll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),__wcscoll_l,(__s1,__s2,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcscoll_l.h>
/* >> wcscoll_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBDCALL c16coll_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16coll_l.h>
/* >> wcscoll_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16coll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBDCALL c16coll_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16coll_l))(__s1, __s2, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscoll_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcscoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32coll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_KOS$wcscoll_l)
/* >> wcscoll_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32coll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcscoll_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcscoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32coll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),_wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_KOS$_wcscoll_l)
/* >> wcscoll_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32coll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),_wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___wcscoll_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcscoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32coll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),__wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_KOS$__wcscoll_l)
/* >> wcscoll_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32coll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),__wcscoll_l,(__s1,__s2,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcscoll_l.h>
/* >> wcscoll_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBKCALL c32coll_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32coll_l.h>
/* >> wcscoll_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32coll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBKCALL c32coll_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32coll_l))(__s1, __s2, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncoll_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsncoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$wcsncoll_l)
/* >> wcsncoll_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsncoll_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsncoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsncoll_l)
/* >> wcsncoll_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsncoll_l.h>
/* >> wcsncoll_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16ncoll_l)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16ncoll_l.h>
/* >> wcsncoll_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ncoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16ncoll_l)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ncoll_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncoll_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsncoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_KOS$wcsncoll_l)
/* >> wcsncoll_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsncoll_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsncoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_KOS$_wcsncoll_l)
/* >> wcsncoll_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsncoll_l.h>
/* >> wcsncoll_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32ncoll_l)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32ncoll_l.h>
/* >> wcsncoll_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ncoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32ncoll_l)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ncoll_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscasecoll_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcscasecoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16casecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscasecoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$wcscasecoll_l)
/* >> wcscasecoll_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16casecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscasecoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicoll_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcscasecoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16casecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcsicoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsicoll_l)
/* >> wcscasecoll_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16casecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcsicoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcscasecmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcscasecoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16casecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$wcscasecmp_l)
/* >> wcscasecoll_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16casecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcscasecoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16casecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsicmp_l)
/* >> wcscasecoll_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c16casecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcscasecoll_l.h>
/* >> wcscasecoll_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBDCALL c16casecoll_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16casecoll_l.h>
/* >> wcscasecoll_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16casecoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBDCALL c16casecoll_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16casecoll_l))(__s1, __s2, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscasecoll_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcscasecoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32casecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcscasecoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_KOS$wcscasecoll_l)
/* >> wcscasecoll_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32casecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcscasecoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicoll_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcscasecoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32casecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),_wcsicoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_KOS$_wcsicoll_l)
/* >> wcscasecoll_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32casecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),_wcsicoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcscasecmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcscasecoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32casecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_KOS$wcscasecmp_l)
/* >> wcscasecoll_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32casecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcscasecoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32casecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_KOS$_wcsicmp_l)
/* >> wcscasecoll_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,c32casecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcscasecoll_l.h>
/* >> wcscasecoll_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBKCALL c32casecoll_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32casecoll_l.h>
/* >> wcscasecoll_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32casecoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBKCALL c32casecoll_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32casecoll_l))(__s1, __s2, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncasecoll_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsncasecoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$wcsncasecoll_l)
/* >> wcsncasecoll_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicoll_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsncasecoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsnicoll_l)
/* >> wcsncasecoll_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_wcsncasecmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsncasecoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$wcsncasecmp_l)
/* >> wcsncasecoll_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsncasecoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsnicmp_l)
/* >> wcsncasecoll_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsncasecoll_l.h>
/* >> wcsncasecoll_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16ncasecoll_l)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16ncasecoll_l.h>
/* >> wcsncasecoll_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ncasecoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16ncasecoll_l)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ncasecoll_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncasecoll_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsncasecoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_KOS$wcsncasecoll_l)
/* >> wcsncasecoll_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicoll_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsncasecoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_KOS$_wcsnicoll_l)
/* >> wcsncasecoll_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_wcsncasecmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsncasecoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_KOS$wcsncasecmp_l)
/* >> wcsncasecoll_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsncasecoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_KOS$_wcsnicmp_l)
/* >> wcsncasecoll_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsncasecoll_l.h>
/* >> wcsncasecoll_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32ncasecoll_l)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32ncasecoll_l.h>
/* >> wcsncasecoll_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ncasecoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32ncasecoll_l)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ncasecoll_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcslwr_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcslwr_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,c16lwr_l,(char16_t *__restrict __str, __locale_t __locale),wcslwr_l,(__str,__locale))
#elif defined(__CRT_HAVE_DOS$wcslwr_l)
/* >> wcslwr_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,c16lwr_l,(char16_t *__restrict __str, __locale_t __locale),wcslwr_l,(__str,__locale))
#elif defined(__CRT_HAVE__wcslwr_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcslwr_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,c16lwr_l,(char16_t *__restrict __str, __locale_t __locale),_wcslwr_l,(__str,__locale))
#elif defined(__CRT_HAVE_DOS$_wcslwr_l)
/* >> wcslwr_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,c16lwr_l,(char16_t *__restrict __str, __locale_t __locale),_wcslwr_l,(__str,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcslwr_l.h>
/* >> wcslwr_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INOUT(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16lwr_l)(char16_t *__restrict __str, __locale_t __locale) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr_l))((__WCHAR_TYPE__ *)__str, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16lwr_l.h>
/* >> wcslwr_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16lwr_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INOUT(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16lwr_l)(char16_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16lwr_l))(__str, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcslwr_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcslwr_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,c32lwr_l,(char32_t *__restrict __str, __locale_t __locale),wcslwr_l,(__str,__locale))
#elif defined(__CRT_HAVE_KOS$wcslwr_l)
/* >> wcslwr_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,c32lwr_l,(char32_t *__restrict __str, __locale_t __locale),wcslwr_l,(__str,__locale))
#elif defined(__CRT_HAVE__wcslwr_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcslwr_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,c32lwr_l,(char32_t *__restrict __str, __locale_t __locale),_wcslwr_l,(__str,__locale))
#elif defined(__CRT_HAVE_KOS$_wcslwr_l)
/* >> wcslwr_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,c32lwr_l,(char32_t *__restrict __str, __locale_t __locale),_wcslwr_l,(__str,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcslwr_l.h>
/* >> wcslwr_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INOUT(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32lwr_l)(char32_t *__restrict __str, __locale_t __locale) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr_l))((__WCHAR_TYPE__ *)__str, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32lwr_l.h>
/* >> wcslwr_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32lwr_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INOUT(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32lwr_l)(char32_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32lwr_l))(__str, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsupr_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsupr_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,c16upr_l,(char16_t *__restrict __str, __locale_t __locale),wcsupr_l,(__str,__locale))
#elif defined(__CRT_HAVE_DOS$wcsupr_l)
/* >> wcsupr_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,c16upr_l,(char16_t *__restrict __str, __locale_t __locale),wcsupr_l,(__str,__locale))
#elif defined(__CRT_HAVE__wcsupr_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsupr_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,c16upr_l,(char16_t *__restrict __str, __locale_t __locale),_wcsupr_l,(__str,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsupr_l)
/* >> wcsupr_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,c16upr_l,(char16_t *__restrict __str, __locale_t __locale),_wcsupr_l,(__str,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsupr_l.h>
/* >> wcsupr_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INOUT(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16upr_l)(char16_t *__restrict __str, __locale_t __locale) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr_l))((__WCHAR_TYPE__ *)__str, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16upr_l.h>
/* >> wcsupr_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16upr_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INOUT(1) char16_t *__NOTHROW_NCX(__LIBDCALL c16upr_l)(char16_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16upr_l))(__str, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsupr_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsupr_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,c32upr_l,(char32_t *__restrict __str, __locale_t __locale),wcsupr_l,(__str,__locale))
#elif defined(__CRT_HAVE_KOS$wcsupr_l)
/* >> wcsupr_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,c32upr_l,(char32_t *__restrict __str, __locale_t __locale),wcsupr_l,(__str,__locale))
#elif defined(__CRT_HAVE__wcsupr_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsupr_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,c32upr_l,(char32_t *__restrict __str, __locale_t __locale),_wcsupr_l,(__str,__locale))
#elif defined(__CRT_HAVE_KOS$_wcsupr_l)
/* >> wcsupr_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,c32upr_l,(char32_t *__restrict __str, __locale_t __locale),_wcsupr_l,(__str,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsupr_l.h>
/* >> wcsupr_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INOUT(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32upr_l)(char32_t *__restrict __str, __locale_t __locale) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr_l))((__WCHAR_TYPE__ *)__str, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32upr_l.h>
/* >> wcsupr_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32upr_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INOUT(1) char32_t *__NOTHROW_NCX(__LIBKCALL c32upr_l)(char32_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32upr_l))(__str, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fuzzy_wmemcasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16memcasecmp_l,(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale),fuzzy_wmemcasecmp_l,(__s1,__s1_bytes,__s2,__s2_bytes,__locale))
#elif defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp_l)
/* >> fuzzy_wmemcasecmp_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16memcasecmp_l,(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale),fuzzy_wmemcasecmp_l,(__s1,__s1_bytes,__s2,__s2_bytes,__locale))
#elif !defined(__NO_MALLOCA) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/fuzzy_wmemcasecmp_l.h>
/* >> fuzzy_wmemcasecmp_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16memcasecmp_l)(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcasecmp_l))((__WCHAR_TYPE__ const *)__s1, __s1_bytes, (__WCHAR_TYPE__ const *)__s2, __s2_bytes, __locale); }
#elif !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c16memcasecmp_l.h>
/* >> fuzzy_wmemcasecmp_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16memcasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16memcasecmp_l)(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16memcasecmp_l))(__s1, __s1_bytes, __s2, __s2_bytes, __locale); })
#endif /* ... */
#if defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fuzzy_wmemcasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32memcasecmp_l,(char32_t const *__s1, __SIZE_TYPE__ __s1_bytes, char32_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale),fuzzy_wmemcasecmp_l,(__s1,__s1_bytes,__s2,__s2_bytes,__locale))
#elif defined(__CRT_HAVE_KOS$fuzzy_wmemcasecmp_l)
/* >> fuzzy_wmemcasecmp_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32memcasecmp_l,(char32_t const *__s1, __SIZE_TYPE__ __s1_bytes, char32_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale),fuzzy_wmemcasecmp_l,(__s1,__s1_bytes,__s2,__s2_bytes,__locale))
#elif !defined(__NO_MALLOCA) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/fuzzy_wmemcasecmp_l.h>
/* >> fuzzy_wmemcasecmp_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32memcasecmp_l)(char32_t const *__s1, __SIZE_TYPE__ __s1_bytes, char32_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcasecmp_l))((__WCHAR_TYPE__ const *)__s1, __s1_bytes, (__WCHAR_TYPE__ const *)__s2, __s2_bytes, __locale); }
#elif !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c32memcasecmp_l.h>
/* >> fuzzy_wmemcasecmp_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32memcasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32memcasecmp_l)(char32_t const *__s1, __SIZE_TYPE__ __s1_bytes, char32_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32memcasecmp_l))(__s1, __s1_bytes, __s2, __s2_bytes, __locale); })
#endif /* ... */
#if defined(__CRT_HAVE_fuzzy_wcscasecmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fuzzy_wcscasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16casecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),fuzzy_wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$fuzzy_wcscasecmp_l)
/* >> fuzzy_wcscasecmp_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16casecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),fuzzy_wcscasecmp_l,(__s1,__s2,__locale))
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) || !defined(__NO_MALLOCA)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/fuzzy_wcscasecmp_l.h>
/* >> fuzzy_wcscasecmp_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16casecmp_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscasecmp_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp_l) || !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c16casecmp_l.h>
/* >> fuzzy_wcscasecmp_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16casecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16casecmp_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16casecmp_l))(__s1, __s2, __locale); })
#endif /* ... */
#if defined(__CRT_HAVE_fuzzy_wcscasecmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fuzzy_wcscasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32casecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),fuzzy_wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_KOS$fuzzy_wcscasecmp_l)
/* >> fuzzy_wcscasecmp_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32casecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),fuzzy_wcscasecmp_l,(__s1,__s2,__locale))
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) || !defined(__NO_MALLOCA)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/fuzzy_wcscasecmp_l.h>
/* >> fuzzy_wcscasecmp_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32casecmp_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscasecmp_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fuzzy_wmemcasecmp_l) || !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c32casecmp_l.h>
/* >> fuzzy_wcscasecmp_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32casecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32casecmp_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32casecmp_l))(__s1, __s2, __locale); })
#endif /* ... */
#if defined(__CRT_HAVE_fuzzy_wcsncasecmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fuzzy_wcsncasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16ncasecmp_l,(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale),fuzzy_wcsncasecmp_l,(__s1,__s1_maxlen,__s2,__s2_maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$fuzzy_wcsncasecmp_l)
/* >> fuzzy_wcsncasecmp_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16ncasecmp_l,(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale),fuzzy_wcsncasecmp_l,(__s1,__s1_maxlen,__s2,__s2_maxlen,__locale))
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) || !defined(__NO_MALLOCA)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/fuzzy_wcsncasecmp_l.h>
/* >> fuzzy_wcsncasecmp_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16ncasecmp_l)(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncasecmp_l))((__WCHAR_TYPE__ const *)__s1, __s1_maxlen, (__WCHAR_TYPE__ const *)__s2, __s2_maxlen, __locale); }
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp_l) || !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c16ncasecmp_l.h>
/* >> fuzzy_wcsncasecmp_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16ncasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16ncasecmp_l)(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16ncasecmp_l))(__s1, __s1_maxlen, __s2, __s2_maxlen, __locale); })
#endif /* ... */
#if defined(__CRT_HAVE_fuzzy_wcsncasecmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fuzzy_wcsncasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32ncasecmp_l,(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale),fuzzy_wcsncasecmp_l,(__s1,__s1_maxlen,__s2,__s2_maxlen,__locale))
#elif defined(__CRT_HAVE_KOS$fuzzy_wcsncasecmp_l)
/* >> fuzzy_wcsncasecmp_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32ncasecmp_l,(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale),fuzzy_wcsncasecmp_l,(__s1,__s1_maxlen,__s2,__s2_maxlen,__locale))
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) || !defined(__NO_MALLOCA)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/fuzzy_wcsncasecmp_l.h>
/* >> fuzzy_wcsncasecmp_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32ncasecmp_l)(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncasecmp_l))((__WCHAR_TYPE__ const *)__s1, __s1_maxlen, (__WCHAR_TYPE__ const *)__s2, __s2_maxlen, __locale); }
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fuzzy_wmemcasecmp_l) || !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c32ncasecmp_l.h>
/* >> fuzzy_wcsncasecmp_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32ncasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32ncasecmp_l)(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32ncasecmp_l))(__s1, __s1_maxlen, __s2, __s2_maxlen, __locale); })
#endif /* ... */
#if defined(__CRT_HAVE_wildwcscasecmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wildwcscasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wildc16casecmp_l,(char16_t const *__pattern, char16_t const *__string, __locale_t __locale),wildwcscasecmp_l,(__pattern,__string,__locale))
#elif defined(__CRT_HAVE_DOS$wildwcscasecmp_l)
/* >> wildwcscasecmp_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wildc16casecmp_l,(char16_t const *__pattern, char16_t const *__string, __locale_t __locale),wildwcscasecmp_l,(__pattern,__string,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wildwcscasecmp_l.h>
/* >> wildwcscasecmp_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBDCALL wildc16casecmp_l)(char16_t const *__pattern, char16_t const *__string, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscasecmp_l))((__WCHAR_TYPE__ const *)__pattern, (__WCHAR_TYPE__ const *)__string, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/wildc16casecmp_l.h>
/* >> wildwcscasecmp_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wildc16casecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBDCALL wildc16casecmp_l)(char16_t const *__pattern, char16_t const *__string, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildc16casecmp_l))(__pattern, __string, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wildwcscasecmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wildwcscasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wildc32casecmp_l,(char32_t const *__pattern, char32_t const *__string, __locale_t __locale),wildwcscasecmp_l,(__pattern,__string,__locale))
#elif defined(__CRT_HAVE_KOS$wildwcscasecmp_l)
/* >> wildwcscasecmp_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wildc32casecmp_l,(char32_t const *__pattern, char32_t const *__string, __locale_t __locale),wildwcscasecmp_l,(__pattern,__string,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wildwcscasecmp_l.h>
/* >> wildwcscasecmp_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBKCALL wildc32casecmp_l)(char32_t const *__pattern, char32_t const *__string, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscasecmp_l))((__WCHAR_TYPE__ const *)__pattern, (__WCHAR_TYPE__ const *)__string, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/wildc32casecmp_l.h>
/* >> wildwcscasecmp_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wildc32casecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBKCALL wildc32casecmp_l)(char32_t const *__pattern, char32_t const *__string, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildc32casecmp_l))(__pattern, __string, __locale); })
#endif /* !... */
#endif /* __USE_XOPEN2K8 */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_PARTS_UCHAR_STRING_H */
