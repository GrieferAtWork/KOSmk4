/* HASH CRC-32:0xdd48aba9 */
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

__SYSDECL_BEGIN

#ifdef __CC__

#if defined(__CRT_HAVE_wmemcpy) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16memcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, size_t __num_chars),wmemcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmemcpy)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16memcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, size_t __num_chars),wmemcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memcpyw) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16memcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, size_t __num_chars),memcpyw,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$memcpyw)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16memcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, size_t __num_chars),memcpyw,(__dst,__src,__num_chars))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wmemcpy.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16memcpy)(char16_t *__restrict __dst, char16_t const *__restrict __src, size_t __num_chars) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemcpy))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __num_chars); }
#else /* ... */
#include <local/parts.uchar.string/c16memcpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16memcpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16memcpy)(char16_t *__restrict __dst, char16_t const *__restrict __src, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16memcpy))(__dst, __src, __num_chars); })
#endif /* !... */
#if defined(__CRT_HAVE_wmemcpy) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32memcpy,(char32_t *__restrict __dst, char32_t const *__restrict __src, size_t __num_chars),wmemcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmemcpy)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32memcpy,(char32_t *__restrict __dst, char32_t const *__restrict __src, size_t __num_chars),wmemcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memcpyl) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32memcpy,(char32_t *__restrict __dst, char32_t const *__restrict __src, size_t __num_chars),memcpyl,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$memcpyl)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32memcpy,(char32_t *__restrict __dst, char32_t const *__restrict __src, size_t __num_chars),memcpyl,(__dst,__src,__num_chars))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wmemcpy.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32memcpy)(char32_t *__restrict __dst, char32_t const *__restrict __src, size_t __num_chars) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemcpy))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __num_chars); }
#else /* ... */
#include <local/parts.uchar.string/c32memcpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32memcpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32memcpy)(char32_t *__restrict __dst, char32_t const *__restrict __src, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32memcpy))(__dst, __src, __num_chars); })
#endif /* !... */
#if defined(__CRT_HAVE_wmemmove) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16memmove,(char16_t *__dst, char16_t const *__src, size_t __num_chars),wmemmove,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmemmove)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16memmove,(char16_t *__dst, char16_t const *__src, size_t __num_chars),wmemmove,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memmovew) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16memmove,(char16_t *__dst, char16_t const *__src, size_t __num_chars),memmovew,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$memmovew)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16memmove,(char16_t *__dst, char16_t const *__src, size_t __num_chars),memmovew,(__dst,__src,__num_chars))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wmemmove.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16memmove)(char16_t *__dst, char16_t const *__src, size_t __num_chars) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemmove))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __num_chars); }
#else /* ... */
#include <local/parts.uchar.string/c16memmove.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16memmove, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16memmove)(char16_t *__dst, char16_t const *__src, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16memmove))(__dst, __src, __num_chars); })
#endif /* !... */
#if defined(__CRT_HAVE_wmemmove) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32memmove,(char32_t *__dst, char32_t const *__src, size_t __num_chars),wmemmove,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmemmove)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32memmove,(char32_t *__dst, char32_t const *__src, size_t __num_chars),wmemmove,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memmovel) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32memmove,(char32_t *__dst, char32_t const *__src, size_t __num_chars),memmovel,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$memmovel)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32memmove,(char32_t *__dst, char32_t const *__src, size_t __num_chars),memmovel,(__dst,__src,__num_chars))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wmemmove.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32memmove)(char32_t *__dst, char32_t const *__src, size_t __num_chars) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemmove))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __num_chars); }
#else /* ... */
#include <local/parts.uchar.string/c32memmove.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32memmove, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32memmove)(char32_t *__dst, char32_t const *__src, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32memmove))(__dst, __src, __num_chars); })
#endif /* !... */
#if defined(__CRT_HAVE_wmemset) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16memset,(char16_t *__dst, char16_t __filler, size_t __num_chars),wmemset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmemset)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16memset,(char16_t *__dst, char16_t __filler, size_t __num_chars),wmemset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_memsetw) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16memset,(char16_t *__dst, char16_t __filler, size_t __num_chars),memsetw,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_DOS$memsetw)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16memset,(char16_t *__dst, char16_t __filler, size_t __num_chars),memsetw,(__dst,__filler,__num_chars))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wmemset.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16memset)(char16_t *__dst, char16_t __filler, size_t __num_chars) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemset))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__)__filler, __num_chars); }
#else /* ... */
#include <local/parts.uchar.string/c16memset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16memset, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16memset)(char16_t *__dst, char16_t __filler, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16memset))(__dst, __filler, __num_chars); })
#endif /* !... */
#if defined(__CRT_HAVE_wmemset) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32memset,(char32_t *__dst, char32_t __filler, size_t __num_chars),wmemset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmemset)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32memset,(char32_t *__dst, char32_t __filler, size_t __num_chars),wmemset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_memsetl) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32memset,(char32_t *__dst, char32_t __filler, size_t __num_chars),memsetl,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_DOS$memsetl)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32memset,(char32_t *__dst, char32_t __filler, size_t __num_chars),memsetl,(__dst,__filler,__num_chars))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wmemset.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32memset)(char32_t *__dst, char32_t __filler, size_t __num_chars) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemset))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__)__filler, __num_chars); }
#else /* ... */
#include <local/parts.uchar.string/c32memset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32memset, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32memset)(char32_t *__dst, char32_t __filler, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32memset))(__dst, __filler, __num_chars); })
#endif /* !... */
#if defined(__CRT_HAVE_wmempcpy) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16mempcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, __SIZE_TYPE__ __num_chars),wmempcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmempcpy)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16mempcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, __SIZE_TYPE__ __num_chars),wmempcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_mempcpyw) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16mempcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, __SIZE_TYPE__ __num_chars),mempcpyw,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$mempcpyw)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16mempcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, __SIZE_TYPE__ __num_chars),mempcpyw,(__dst,__src,__num_chars))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wmempcpy.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16mempcpy)(char16_t *__restrict __dst, char16_t const *__restrict __src, __SIZE_TYPE__ __num_chars) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmempcpy))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __num_chars); }
#else /* ... */
#include <local/parts.uchar.string/c16mempcpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16mempcpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16mempcpy)(char16_t *__restrict __dst, char16_t const *__restrict __src, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16mempcpy))(__dst, __src, __num_chars); })
#endif /* !... */
#if defined(__CRT_HAVE_wmempcpy) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32mempcpy,(char32_t *__restrict __dst, char32_t const *__restrict __src, __SIZE_TYPE__ __num_chars),wmempcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmempcpy)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32mempcpy,(char32_t *__restrict __dst, char32_t const *__restrict __src, __SIZE_TYPE__ __num_chars),wmempcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_mempcpyl) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32mempcpy,(char32_t *__restrict __dst, char32_t const *__restrict __src, __SIZE_TYPE__ __num_chars),mempcpyl,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$mempcpyl)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32mempcpy,(char32_t *__restrict __dst, char32_t const *__restrict __src, __SIZE_TYPE__ __num_chars),mempcpyl,(__dst,__src,__num_chars))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wmempcpy.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32mempcpy)(char32_t *__restrict __dst, char32_t const *__restrict __src, __SIZE_TYPE__ __num_chars) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmempcpy))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __num_chars); }
#else /* ... */
#include <local/parts.uchar.string/c32mempcpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32mempcpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32mempcpy)(char32_t *__restrict __dst, char32_t const *__restrict __src, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32mempcpy))(__dst, __src, __num_chars); })
#endif /* !... */
#if defined(__CRT_HAVE_wmempmove) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16mempmove,(char16_t *__dst, char16_t const *__src, __SIZE_TYPE__ __num_chars),wmempmove,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmempmove)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16mempmove,(char16_t *__dst, char16_t const *__src, __SIZE_TYPE__ __num_chars),wmempmove,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_mempmovew) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16mempmove,(char16_t *__dst, char16_t const *__src, __SIZE_TYPE__ __num_chars),mempmovew,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$mempmovew)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16mempmove,(char16_t *__dst, char16_t const *__src, __SIZE_TYPE__ __num_chars),mempmovew,(__dst,__src,__num_chars))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wmempmove.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16mempmove)(char16_t *__dst, char16_t const *__src, __SIZE_TYPE__ __num_chars) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmempmove))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __num_chars); }
#else /* ... */
#include <local/parts.uchar.string/c16mempmove.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16mempmove, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16mempmove)(char16_t *__dst, char16_t const *__src, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16mempmove))(__dst, __src, __num_chars); })
#endif /* !... */
#if defined(__CRT_HAVE_wmempmove) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32mempmove,(char32_t *__dst, char32_t const *__src, __SIZE_TYPE__ __num_chars),wmempmove,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmempmove)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32mempmove,(char32_t *__dst, char32_t const *__src, __SIZE_TYPE__ __num_chars),wmempmove,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_mempmovel) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32mempmove,(char32_t *__dst, char32_t const *__src, __SIZE_TYPE__ __num_chars),mempmovel,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$mempmovel)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32mempmove,(char32_t *__dst, char32_t const *__src, __SIZE_TYPE__ __num_chars),mempmovel,(__dst,__src,__num_chars))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wmempmove.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32mempmove)(char32_t *__dst, char32_t const *__src, __SIZE_TYPE__ __num_chars) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmempmove))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __num_chars); }
#else /* ... */
#include <local/parts.uchar.string/c32mempmove.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32mempmove, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32mempmove)(char32_t *__dst, char32_t const *__src, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32mempmove))(__dst, __src, __num_chars); })
#endif /* !... */
#if defined(__CRT_HAVE_wmempset) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as wmemset, but return a pointer after the last written character */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16mempset,(char16_t *__dst, char16_t __filler, __SIZE_TYPE__ __num_chars),wmempset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmempset)
/* Same as wmemset, but return a pointer after the last written character */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16mempset,(char16_t *__dst, char16_t __filler, __SIZE_TYPE__ __num_chars),wmempset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_mempsetw) && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as wmemset, but return a pointer after the last written character */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16mempset,(char16_t *__dst, char16_t __filler, __SIZE_TYPE__ __num_chars),mempsetw,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_DOS$mempsetw)
/* Same as wmemset, but return a pointer after the last written character */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16mempset,(char16_t *__dst, char16_t __filler, __SIZE_TYPE__ __num_chars),mempsetw,(__dst,__filler,__num_chars))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wmempset.h>
/* Same as wmemset, but return a pointer after the last written character */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16mempset)(char16_t *__dst, char16_t __filler, __SIZE_TYPE__ __num_chars) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmempset))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__)__filler, __num_chars); }
#else /* ... */
#include <local/parts.uchar.string/c16mempset.h>
/* Same as wmemset, but return a pointer after the last written character */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16mempset, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16mempset)(char16_t *__dst, char16_t __filler, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16mempset))(__dst, __filler, __num_chars); })
#endif /* !... */
#if defined(__CRT_HAVE_wmempset) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as wmemset, but return a pointer after the last written character */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32mempset,(char32_t *__dst, char32_t __filler, __SIZE_TYPE__ __num_chars),wmempset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmempset)
/* Same as wmemset, but return a pointer after the last written character */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32mempset,(char32_t *__dst, char32_t __filler, __SIZE_TYPE__ __num_chars),wmempset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_mempsetl) && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as wmemset, but return a pointer after the last written character */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32mempset,(char32_t *__dst, char32_t __filler, __SIZE_TYPE__ __num_chars),mempsetl,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_DOS$mempsetl)
/* Same as wmemset, but return a pointer after the last written character */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32mempset,(char32_t *__dst, char32_t __filler, __SIZE_TYPE__ __num_chars),mempsetl,(__dst,__filler,__num_chars))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wmempset.h>
/* Same as wmemset, but return a pointer after the last written character */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32mempset)(char32_t *__dst, char32_t __filler, __SIZE_TYPE__ __num_chars) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmempset))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__)__filler, __num_chars); }
#else /* ... */
#include <local/parts.uchar.string/c32mempset.h>
/* Same as wmemset, but return a pointer after the last written character */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32mempset, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32mempset)(char32_t *__dst, char32_t __filler, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32mempset))(__dst, __filler, __num_chars); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsend) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcslen(STR)' */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16end,(char16_t *__restrict __string),wcsend,(__string))
/* Same as `STR+wcslen(STR)' */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,__LIBDCALL,c16end,(char16_t const *__restrict __string),wcsend,(__string))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcslen(STR)' */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16end,(char16_t const *__restrict __string),wcsend,(__string))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsend)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcslen(STR)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16end,(char16_t *__restrict __string),wcsend,(__string))
/* Same as `STR+wcslen(STR)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16end,(char16_t const *__restrict __string),wcsend,(__string))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcslen(STR)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16end,(char16_t const *__restrict __string),wcsend,(__string))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcslen(STR)' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16end)(char16_t *__restrict __string) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))((__WCHAR_TYPE__ const *)__string); }
/* Same as `STR+wcslen(STR)' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16end)(char16_t const *__restrict __string) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))((__WCHAR_TYPE__ const *)__string); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcslen(STR)' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16end)(char16_t const *__restrict __string) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))((__WCHAR_TYPE__ const *)__string); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/parts.uchar.string/c16end.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcslen(STR)' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16end)(char16_t *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16end))(__string); }
/* Same as `STR+wcslen(STR)' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16end)(char16_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16end))(__string); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcslen(STR)' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16end)(char16_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16end))(__string); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsend) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcslen(STR)' */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32end,(char32_t *__restrict __string),wcsend,(__string))
/* Same as `STR+wcslen(STR)' */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,__LIBKCALL,c32end,(char32_t const *__restrict __string),wcsend,(__string))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcslen(STR)' */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32end,(char32_t const *__restrict __string),wcsend,(__string))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsend)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcslen(STR)' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32end,(char32_t *__restrict __string),wcsend,(__string))
/* Same as `STR+wcslen(STR)' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32end,(char32_t const *__restrict __string),wcsend,(__string))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcslen(STR)' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32end,(char32_t const *__restrict __string),wcsend,(__string))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcslen(STR)' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32end)(char32_t *__restrict __string) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))((__WCHAR_TYPE__ const *)__string); }
/* Same as `STR+wcslen(STR)' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32end)(char32_t const *__restrict __string) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))((__WCHAR_TYPE__ const *)__string); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcslen(STR)' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32end)(char32_t const *__restrict __string) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))((__WCHAR_TYPE__ const *)__string); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/parts.uchar.string/c32end.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcslen(STR)' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32end)(char32_t *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32end))(__string); }
/* Same as `STR+wcslen(STR)' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32end)(char32_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32end))(__string); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcslen(STR)' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32end)(char32_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32end))(__string); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsnend) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16nend,(char16_t *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,__LIBDCALL,c16nend,(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16nend,(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsnend)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nend,(char16_t *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16nend,(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nend,(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsnend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nend)(char16_t *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))((__WCHAR_TYPE__ const *)__string, __maxlen); }
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16nend)(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))((__WCHAR_TYPE__ const *)__string, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nend)(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))((__WCHAR_TYPE__ const *)__string, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/parts.uchar.string/c16nend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nend)(char16_t *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nend))(__string, __maxlen); }
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16nend)(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nend))(__string, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nend)(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nend))(__string, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsnend) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32nend,(char32_t *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,__LIBKCALL,c32nend,(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32nend,(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsnend)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nend,(char32_t *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32nend,(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nend,(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsnend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nend)(char32_t *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))((__WCHAR_TYPE__ const *)__string, __maxlen); }
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32nend)(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))((__WCHAR_TYPE__ const *)__string, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nend)(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))((__WCHAR_TYPE__ const *)__string, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/parts.uchar.string/c32nend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nend)(char32_t *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nend))(__string, __maxlen); }
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32nend)(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nend))(__string, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nend)(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nend))(__string, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcslen) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBDCALL,c16len,(char16_t const *__restrict __string),wcslen,(__string))
#elif defined(__CRT_HAVE_DOS$wcslen)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16len,(char16_t const *__restrict __string),wcslen,(__string))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcslen.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16len)(char16_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslen))((__WCHAR_TYPE__ const *)__string); }
#else /* ... */
#include <local/parts.uchar.string/c16len.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16len, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16len)(char16_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16len))(__string); })
#endif /* !... */
#if defined(__CRT_HAVE_wcslen) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBKCALL,c32len,(char32_t const *__restrict __string),wcslen,(__string))
#elif defined(__CRT_HAVE_DOS$wcslen)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c32len,(char32_t const *__restrict __string),wcslen,(__string))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcslen.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32len)(char32_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslen))((__WCHAR_TYPE__ const *)__string); }
#else /* ... */
#include <local/parts.uchar.string/c32len.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32len, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32len)(char32_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32len))(__string); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnlen) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBDCALL,c16nlen,(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnlen)
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16nlen,(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsnlen.h>
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16nlen)(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlen))((__WCHAR_TYPE__ const *)__string, __maxlen); }
#else /* ... */
#include <local/parts.uchar.string/c16nlen.h>
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16nlen, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16nlen)(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nlen))(__string, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnlen) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBKCALL,c32nlen,(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnlen)
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c32nlen,(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsnlen.h>
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32nlen)(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlen))((__WCHAR_TYPE__ const *)__string, __maxlen); }
#else /* ... */
#include <local/parts.uchar.string/c32nlen.h>
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32nlen, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32nlen)(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nlen))(__string, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscmp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16cmp,(char16_t const *__s1, char16_t const *__s2),wcscmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscmp)
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16cmp,(char16_t const *__s1, char16_t const *__s2),wcscmp,(__s1,__s2))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcscmp.h>
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16cmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <local/parts.uchar.string/c16cmp.h>
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16cmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16cmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16cmp))(__s1, __s2); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscmp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32cmp,(char32_t const *__s1, char32_t const *__s2),wcscmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscmp)
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32cmp,(char32_t const *__s1, char32_t const *__s2),wcscmp,(__s1,__s2))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcscmp.h>
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32cmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <local/parts.uchar.string/c32cmp.h>
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32cmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32cmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32cmp))(__s1, __s2); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncmp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as `strcmp', but compare at most `MAXLEN' characters from either string */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16ncmp,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsncmp)
/* Same as `strcmp', but compare at most `MAXLEN' characters from either string */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncmp,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsncmp.h>
/* Same as `strcmp', but compare at most `MAXLEN' characters from either string */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16ncmp)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* ... */
#include <local/parts.uchar.string/c16ncmp.h>
/* Same as `strcmp', but compare at most `MAXLEN' characters from either string */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ncmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16ncmp)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ncmp))(__s1, __s2, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncmp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as `strcmp', but compare at most `MAXLEN' characters from either string */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32ncmp,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsncmp)
/* Same as `strcmp', but compare at most `MAXLEN' characters from either string */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncmp,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsncmp.h>
/* Same as `strcmp', but compare at most `MAXLEN' characters from either string */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32ncmp)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* ... */
#include <local/parts.uchar.string/c32ncmp.h>
/* Same as `strcmp', but compare at most `MAXLEN' characters from either string */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ncmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32ncmp)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ncmp))(__s1, __s2, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcschr) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16chr,(char16_t *__restrict __haystack, char16_t __needle),wcschr,(__haystack,__needle))
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,__LIBDCALL,c16chr,(char16_t const *__restrict __haystack, char16_t __needle),wcschr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16chr,(char16_t const *__restrict __haystack, char16_t __needle),wcschr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcschr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16chr,(char16_t *__restrict __haystack, char16_t __needle),wcschr,(__haystack,__needle))
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16chr,(char16_t const *__restrict __haystack, char16_t __needle),wcschr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16chr,(char16_t const *__restrict __haystack, char16_t __needle),wcschr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcschr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16chr)(char16_t *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16chr)(char16_t const *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16chr)(char16_t const *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/parts.uchar.string/c16chr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16chr)(char16_t *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16chr))(__haystack, __needle); }
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16chr)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16chr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16chr)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16chr))(__haystack, __needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcschr) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32chr,(char32_t *__restrict __haystack, char32_t __needle),wcschr,(__haystack,__needle))
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,__LIBKCALL,c32chr,(char32_t const *__restrict __haystack, char32_t __needle),wcschr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32chr,(char32_t const *__restrict __haystack, char32_t __needle),wcschr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcschr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32chr,(char32_t *__restrict __haystack, char32_t __needle),wcschr,(__haystack,__needle))
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32chr,(char32_t const *__restrict __haystack, char32_t __needle),wcschr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32chr,(char32_t const *__restrict __haystack, char32_t __needle),wcschr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcschr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32chr)(char32_t *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32chr)(char32_t const *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32chr)(char32_t const *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/parts.uchar.string/c32chr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32chr)(char32_t *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32chr))(__haystack, __needle); }
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32chr)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32chr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32chr)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32chr))(__haystack, __needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsrchr) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16rchr,(char16_t *__restrict __haystack, char16_t __needle),wcsrchr,(__haystack,__needle))
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,__LIBDCALL,c16rchr,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16rchr,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsrchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16rchr,(char16_t *__restrict __haystack, char16_t __needle),wcsrchr,(__haystack,__needle))
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16rchr,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16rchr,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16rchr)(char16_t *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16rchr)(char16_t const *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16rchr)(char16_t const *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/parts.uchar.string/c16rchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16rchr)(char16_t *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rchr))(__haystack, __needle); }
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16rchr)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rchr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16rchr)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rchr))(__haystack, __needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsrchr) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32rchr,(char32_t *__restrict __haystack, char32_t __needle),wcsrchr,(__haystack,__needle))
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,__LIBKCALL,c32rchr,(char32_t const *__restrict __haystack, char32_t __needle),wcsrchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32rchr,(char32_t const *__restrict __haystack, char32_t __needle),wcsrchr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsrchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32rchr,(char32_t *__restrict __haystack, char32_t __needle),wcsrchr,(__haystack,__needle))
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32rchr,(char32_t const *__restrict __haystack, char32_t __needle),wcsrchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32rchr,(char32_t const *__restrict __haystack, char32_t __needle),wcsrchr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32rchr)(char32_t *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32rchr)(char32_t const *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32rchr)(char32_t const *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/parts.uchar.string/c32rchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32rchr)(char32_t *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32rchr))(__haystack, __needle); }
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32rchr)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32rchr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32rchr)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32rchr))(__haystack, __needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsnchr) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16nchr,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,__LIBDCALL,c16nchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16nchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsnchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nchr,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16nchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsnchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nchr)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16nchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/parts.uchar.string/c16nchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nchr)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nchr))(__haystack, __needle, __maxlen); }
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16nchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nchr))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nchr))(__haystack, __needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsnchr) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32nchr,(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,__LIBKCALL,c32nchr,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32nchr,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsnchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nchr,(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32nchr,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nchr,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsnchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nchr)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32nchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/parts.uchar.string/c32nchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nchr)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nchr))(__haystack, __needle, __maxlen); }
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32nchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nchr))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nchr))(__haystack, __needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsnrchr) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16nrchr,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,__LIBDCALL,c16nrchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16nrchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsnrchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nrchr,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16nrchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nrchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsnrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nrchr)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16nrchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nrchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/parts.uchar.string/c16nrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nrchr)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nrchr))(__haystack, __needle, __maxlen); }
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16nrchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nrchr))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nrchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nrchr))(__haystack, __needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsnrchr) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32nrchr,(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,__LIBKCALL,c32nrchr,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32nrchr,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsnrchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nrchr,(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32nrchr,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nrchr,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsnrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nrchr)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32nrchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nrchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/parts.uchar.string/c32nrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nrchr)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nrchr))(__haystack, __needle, __maxlen); }
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32nrchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nrchr))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nrchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nrchr))(__haystack, __needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcschrnul) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16chrnul,(char16_t *__restrict __haystack, char16_t __needle),wcschrnul,(__haystack,__needle))
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,__LIBDCALL,c16chrnul,(char16_t const *__restrict __haystack, char16_t __needle),wcschrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16chrnul,(char16_t const *__haystack, char16_t __needle),wcschrnul,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcschrnul)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16chrnul,(char16_t *__restrict __haystack, char16_t __needle),wcschrnul,(__haystack,__needle))
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16chrnul,(char16_t const *__restrict __haystack, char16_t __needle),wcschrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16chrnul,(char16_t const *__haystack, char16_t __needle),wcschrnul,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcschrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16chrnul)(char16_t *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16chrnul)(char16_t const *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16chrnul)(char16_t const *__haystack, char16_t __needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/parts.uchar.string/c16chrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16chrnul)(char16_t *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16chrnul))(__haystack, __needle); }
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16chrnul)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16chrnul))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16chrnul)(char16_t const *__haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16chrnul))(__haystack, __needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcschrnul) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32chrnul,(char32_t *__restrict __haystack, char32_t __needle),wcschrnul,(__haystack,__needle))
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,__LIBKCALL,c32chrnul,(char32_t const *__restrict __haystack, char32_t __needle),wcschrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32chrnul,(char32_t const *__haystack, char32_t __needle),wcschrnul,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcschrnul)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32chrnul,(char32_t *__restrict __haystack, char32_t __needle),wcschrnul,(__haystack,__needle))
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32chrnul,(char32_t const *__restrict __haystack, char32_t __needle),wcschrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32chrnul,(char32_t const *__haystack, char32_t __needle),wcschrnul,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcschrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32chrnul)(char32_t *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32chrnul)(char32_t const *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32chrnul)(char32_t const *__haystack, char32_t __needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/parts.uchar.string/c32chrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32chrnul)(char32_t *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32chrnul))(__haystack, __needle); }
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32chrnul)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32chrnul))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32chrnul)(char32_t const *__haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32chrnul))(__haystack, __needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsrchrnul) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16rchrnul,(char16_t *__restrict __haystack, char16_t __needle),wcsrchrnul,(__haystack,__needle))
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,__LIBDCALL,c16rchrnul,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16rchrnul,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchrnul,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsrchrnul)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16rchrnul,(char16_t *__restrict __haystack, char16_t __needle),wcsrchrnul,(__haystack,__needle))
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16rchrnul,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16rchrnul,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchrnul,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsrchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16rchrnul)(char16_t *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16rchrnul)(char16_t const *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16rchrnul)(char16_t const *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/parts.uchar.string/c16rchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16rchrnul)(char16_t *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rchrnul))(__haystack, __needle); }
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16rchrnul)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rchrnul))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16rchrnul)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rchrnul))(__haystack, __needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsrchrnul) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32rchrnul,(char32_t *__restrict __haystack, char32_t __needle),wcsrchrnul,(__haystack,__needle))
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,__LIBKCALL,c32rchrnul,(char32_t const *__restrict __haystack, char32_t __needle),wcsrchrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32rchrnul,(char32_t const *__restrict __haystack, char32_t __needle),wcsrchrnul,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsrchrnul)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32rchrnul,(char32_t *__restrict __haystack, char32_t __needle),wcsrchrnul,(__haystack,__needle))
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32rchrnul,(char32_t const *__restrict __haystack, char32_t __needle),wcsrchrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32rchrnul,(char32_t const *__restrict __haystack, char32_t __needle),wcsrchrnul,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsrchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32rchrnul)(char32_t *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32rchrnul)(char32_t const *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32rchrnul)(char32_t const *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/parts.uchar.string/c32rchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32rchrnul)(char32_t *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32rchrnul))(__haystack, __needle); }
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32rchrnul)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32rchrnul))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32rchrnul)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32rchrnul))(__haystack, __needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsnchrnul) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16nchrnul,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,__LIBDCALL,c16nchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16nchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsnchrnul)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nchrnul,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16nchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsnchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nchrnul)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16nchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/parts.uchar.string/c16nchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nchrnul)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nchrnul))(__haystack, __needle, __maxlen); }
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16nchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nchrnul))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nchrnul))(__haystack, __needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsnchrnul) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32nchrnul,(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,__LIBKCALL,c32nchrnul,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32nchrnul,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsnchrnul)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nchrnul,(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32nchrnul,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nchrnul,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsnchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nchrnul)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32nchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/parts.uchar.string/c32nchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nchrnul)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nchrnul))(__haystack, __needle, __maxlen); }
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32nchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nchrnul))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nchrnul))(__haystack, __needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsnrchrnul) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16nrchrnul,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,__LIBDCALL,c16nrchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16nrchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsnrchrnul)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nrchrnul,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16nrchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nrchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsnrchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nrchrnul)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16nrchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nrchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/parts.uchar.string/c16nrchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nrchrnul)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nrchrnul))(__haystack, __needle, __maxlen); }
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16nrchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nrchrnul))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nrchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nrchrnul))(__haystack, __needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsnrchrnul) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32nrchrnul,(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,__LIBKCALL,c32nrchrnul,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32nrchrnul,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsnrchrnul)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nrchrnul,(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32nrchrnul,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nrchrnul,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsnrchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nrchrnul)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32nrchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nrchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/parts.uchar.string/c32nrchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nrchrnul)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nrchrnul))(__haystack, __needle, __maxlen); }
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32nrchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nrchrnul))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nrchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nrchrnul))(__haystack, __needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsoff) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as `wcschrnul', but return the offset from `STR', rather than the actual address */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBDCALL,c16off,(char16_t const *__restrict __haystack, char16_t __needle),wcsoff,(__haystack,__needle))
#elif defined(__CRT_HAVE_DOS$wcsoff)
/* Same as `wcschrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16off,(char16_t const *__restrict __haystack, char16_t __needle),wcsoff,(__haystack,__needle))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsoff.h>
/* Same as `wcschrnul', but return the offset from `STR', rather than the actual address */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16off)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsoff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#else /* ... */
#include <local/parts.uchar.string/c16off.h>
/* Same as `wcschrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16off, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16off)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16off))(__haystack, __needle); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsoff) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as `wcschrnul', but return the offset from `STR', rather than the actual address */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBKCALL,c32off,(char32_t const *__restrict __haystack, char32_t __needle),wcsoff,(__haystack,__needle))
#elif defined(__CRT_HAVE_DOS$wcsoff)
/* Same as `wcschrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c32off,(char32_t const *__restrict __haystack, char32_t __needle),wcsoff,(__haystack,__needle))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsoff.h>
/* Same as `wcschrnul', but return the offset from `STR', rather than the actual address */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32off)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsoff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#else /* ... */
#include <local/parts.uchar.string/c32off.h>
/* Same as `wcschrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32off, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32off)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32off))(__haystack, __needle); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsroff) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBDCALL,c16roff,(char16_t const *__restrict __haystack, char16_t __needle),wcsroff,(__haystack,__needle))
#elif defined(__CRT_HAVE_DOS$wcsroff)
/* Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16roff,(char16_t const *__restrict __haystack, char16_t __needle),wcsroff,(__haystack,__needle))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsroff.h>
/* Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16roff)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsroff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#else /* ... */
#include <local/parts.uchar.string/c16roff.h>
/* Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16roff, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16roff)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16roff))(__haystack, __needle); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsroff) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBKCALL,c32roff,(char32_t const *__restrict __haystack, char32_t __needle),wcsroff,(__haystack,__needle))
#elif defined(__CRT_HAVE_DOS$wcsroff)
/* Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c32roff,(char32_t const *__restrict __haystack, char32_t __needle),wcsroff,(__haystack,__needle))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsroff.h>
/* Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32roff)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsroff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#else /* ... */
#include <local/parts.uchar.string/c32roff.h>
/* Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32roff, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32roff)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32roff))(__haystack, __needle); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnoff) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as `wcsnchrnul', but return the offset from `STR', rather than the actual address */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBDCALL,c16noff,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnoff,(__haystack,__needle,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnoff)
/* Same as `wcsnchrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16noff,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnoff,(__haystack,__needle,__maxlen))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsnoff.h>
/* Same as `wcsnchrnul', but return the offset from `STR', rather than the actual address */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16noff)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnoff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#else /* ... */
#include <local/parts.uchar.string/c16noff.h>
/* Same as `wcsnchrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16noff, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16noff)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16noff))(__haystack, __needle, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnoff) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as `wcsnchrnul', but return the offset from `STR', rather than the actual address */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBKCALL,c32noff,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnoff,(__haystack,__needle,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnoff)
/* Same as `wcsnchrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c32noff,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnoff,(__haystack,__needle,__maxlen))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsnoff.h>
/* Same as `wcsnchrnul', but return the offset from `STR', rather than the actual address */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32noff)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnoff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#else /* ... */
#include <local/parts.uchar.string/c32noff.h>
/* Same as `wcsnchrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32noff, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32noff)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32noff))(__haystack, __needle, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnroff) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as `wcsnrchrnul', but return the offset from `STR', rather than the actual address */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBDCALL,c16nroff,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnroff,(__haystack,__needle,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnroff)
/* Same as `wcsnrchrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16nroff,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnroff,(__haystack,__needle,__maxlen))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsnroff.h>
/* Same as `wcsnrchrnul', but return the offset from `STR', rather than the actual address */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16nroff)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnroff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#else /* ... */
#include <local/parts.uchar.string/c16nroff.h>
/* Same as `wcsnrchrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16nroff, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16nroff)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nroff))(__haystack, __needle, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnroff) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as `wcsnrchrnul', but return the offset from `STR', rather than the actual address */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBKCALL,c32nroff,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnroff,(__haystack,__needle,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnroff)
/* Same as `wcsnrchrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c32nroff,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnroff,(__haystack,__needle,__maxlen))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsnroff.h>
/* Same as `wcsnrchrnul', but return the offset from `STR', rather than the actual address */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32nroff)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnroff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#else /* ... */
#include <local/parts.uchar.string/c32nroff.h>
/* Same as `wcsnrchrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32nroff, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32nroff)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nroff))(__haystack, __needle, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsstr) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16str,(char16_t *__haystack, char16_t *__needle),wcsstr,(__haystack,__needle))
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,__LIBDCALL,c16str,(char16_t const *__haystack, char16_t const *__needle),wcsstr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16str,(char16_t const *__haystack, char16_t const *__needle),wcsstr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsstr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16str,(char16_t *__haystack, char16_t *__needle),wcsstr,(__haystack,__needle))
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16str,(char16_t const *__haystack, char16_t const *__needle),wcsstr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16str,(char16_t const *__haystack, char16_t const *__needle),wcsstr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_wcswcs) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16str,(char16_t *__haystack, char16_t *__needle),wcswcs,(__haystack,__needle))
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,__LIBDCALL,c16str,(char16_t const *__haystack, char16_t const *__needle),wcswcs,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16str,(char16_t const *__haystack, char16_t const *__needle),wcswcs,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcswcs)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16str,(char16_t *__haystack, char16_t *__needle),wcswcs,(__haystack,__needle))
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16str,(char16_t const *__haystack, char16_t const *__needle),wcswcs,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16str,(char16_t const *__haystack, char16_t const *__needle),wcswcs,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsstr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16str)(char16_t *__haystack, char16_t *__needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16str)(char16_t const *__haystack, char16_t const *__needle) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16str)(char16_t const *__haystack, char16_t const *__needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/parts.uchar.string/c16str.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16str)(char16_t *__haystack, char16_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16str))(__haystack, __needle); }
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16str)(char16_t const *__haystack, char16_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16str))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16str)(char16_t const *__haystack, char16_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16str))(__haystack, __needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsstr) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32str,(char32_t *__haystack, char32_t *__needle),wcsstr,(__haystack,__needle))
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,__LIBKCALL,c32str,(char32_t const *__haystack, char32_t const *__needle),wcsstr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32str,(char32_t const *__haystack, char32_t const *__needle),wcsstr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsstr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32str,(char32_t *__haystack, char32_t *__needle),wcsstr,(__haystack,__needle))
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,c32str,(char32_t const *__haystack, char32_t const *__needle),wcsstr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32str,(char32_t const *__haystack, char32_t const *__needle),wcsstr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_wcswcs) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32str,(char32_t *__haystack, char32_t *__needle),wcswcs,(__haystack,__needle))
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,__LIBKCALL,c32str,(char32_t const *__haystack, char32_t const *__needle),wcswcs,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32str,(char32_t const *__haystack, char32_t const *__needle),wcswcs,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcswcs)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32str,(char32_t *__haystack, char32_t *__needle),wcswcs,(__haystack,__needle))
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,c32str,(char32_t const *__haystack, char32_t const *__needle),wcswcs,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32str,(char32_t const *__haystack, char32_t const *__needle),wcswcs,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsstr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32str)(char32_t *__haystack, char32_t *__needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32str)(char32_t const *__haystack, char32_t const *__needle) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32str)(char32_t const *__haystack, char32_t const *__needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/parts.uchar.string/c32str.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32str)(char32_t *__haystack, char32_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32str))(__haystack, __needle); }
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32str)(char32_t const *__haystack, char32_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32str))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32str)(char32_t const *__haystack, char32_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32str))(__haystack, __needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcscasestr) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `strstr', but ignore casing */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16casestr,(char16_t *__haystack, char16_t *__needle),wcscasestr,(__haystack,__needle))
/* Same as `strstr', but ignore casing */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,__LIBDCALL,c16casestr,(char16_t const *__haystack, char16_t const *__needle),wcscasestr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `strstr', but ignore casing */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16casestr,(char16_t const *__haystack, char16_t const *__needle),wcscasestr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcscasestr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `strstr', but ignore casing */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr,(char16_t *__haystack, char16_t *__needle),wcscasestr,(__haystack,__needle))
/* Same as `strstr', but ignore casing */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16casestr,(char16_t const *__haystack, char16_t const *__needle),wcscasestr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `strstr', but ignore casing */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr,(char16_t const *__haystack, char16_t const *__needle),wcscasestr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcscasestr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16casestr)(char16_t *__haystack, char16_t *__needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
/* Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16casestr)(char16_t const *__haystack, char16_t const *__needle) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16casestr)(char16_t const *__haystack, char16_t const *__needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/parts.uchar.string/c16casestr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16casestr)(char16_t *__haystack, char16_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16casestr))(__haystack, __needle); }
/* Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16casestr)(char16_t const *__haystack, char16_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16casestr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16casestr)(char16_t const *__haystack, char16_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16casestr))(__haystack, __needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcscasestr) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `strstr', but ignore casing */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32casestr,(char32_t *__haystack, char32_t *__needle),wcscasestr,(__haystack,__needle))
/* Same as `strstr', but ignore casing */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,__LIBKCALL,c32casestr,(char32_t const *__haystack, char32_t const *__needle),wcscasestr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `strstr', but ignore casing */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32casestr,(char32_t const *__haystack, char32_t const *__needle),wcscasestr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcscasestr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `strstr', but ignore casing */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32casestr,(char32_t *__haystack, char32_t *__needle),wcscasestr,(__haystack,__needle))
/* Same as `strstr', but ignore casing */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,c32casestr,(char32_t const *__haystack, char32_t const *__needle),wcscasestr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `strstr', but ignore casing */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32casestr,(char32_t const *__haystack, char32_t const *__needle),wcscasestr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcscasestr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32casestr)(char32_t *__haystack, char32_t *__needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
/* Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32casestr)(char32_t const *__haystack, char32_t const *__needle) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32casestr)(char32_t const *__haystack, char32_t const *__needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/parts.uchar.string/c32casestr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32casestr)(char32_t *__haystack, char32_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32casestr))(__haystack, __needle); }
/* Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32casestr)(char32_t const *__haystack, char32_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32casestr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32casestr)(char32_t const *__haystack, char32_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32casestr))(__haystack, __needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcscpy) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16cpy,(char16_t *__restrict __buf, char16_t const *__restrict __src),wcscpy,(__buf,__src))
#elif defined(__CRT_HAVE_DOS$wcscpy)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16cpy,(char16_t *__restrict __buf, char16_t const *__restrict __src),wcscpy,(__buf,__src))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcscpy.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16cpy)(char16_t *__restrict __buf, char16_t const *__restrict __src) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src); }
#else /* ... */
#include <local/parts.uchar.string/c16cpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16cpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16cpy)(char16_t *__restrict __buf, char16_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16cpy))(__buf, __src); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscpy) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32cpy,(char32_t *__restrict __buf, char32_t const *__restrict __src),wcscpy,(__buf,__src))
#elif defined(__CRT_HAVE_DOS$wcscpy)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32cpy,(char32_t *__restrict __buf, char32_t const *__restrict __src),wcscpy,(__buf,__src))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcscpy.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32cpy)(char32_t *__restrict __buf, char32_t const *__restrict __src) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src); }
#else /* ... */
#include <local/parts.uchar.string/c32cpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32cpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32cpy)(char32_t *__restrict __buf, char32_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32cpy))(__buf, __src); })
#endif /* !... */
#if defined(__CRT_HAVE_wcspcpy) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as wcscpy, but return a pointer after the last written character */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16pcpy,(char16_t *__restrict __buf, char16_t const *__restrict __src),wcspcpy,(__buf,__src))
#elif defined(__CRT_HAVE_DOS$wcspcpy)
/* Same as wcscpy, but return a pointer after the last written character */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16pcpy,(char16_t *__restrict __buf, char16_t const *__restrict __src),wcspcpy,(__buf,__src))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcspcpy.h>
/* Same as wcscpy, but return a pointer after the last written character */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16pcpy)(char16_t *__restrict __buf, char16_t const *__restrict __src) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspcpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src); }
#else /* ... */
#include <local/parts.uchar.string/c16pcpy.h>
/* Same as wcscpy, but return a pointer after the last written character */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16pcpy, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16pcpy)(char16_t *__restrict __buf, char16_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16pcpy))(__buf, __src); })
#endif /* !... */
#if defined(__CRT_HAVE_wcspcpy) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as wcscpy, but return a pointer after the last written character */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32pcpy,(char32_t *__restrict __buf, char32_t const *__restrict __src),wcspcpy,(__buf,__src))
#elif defined(__CRT_HAVE_DOS$wcspcpy)
/* Same as wcscpy, but return a pointer after the last written character */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32pcpy,(char32_t *__restrict __buf, char32_t const *__restrict __src),wcspcpy,(__buf,__src))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcspcpy.h>
/* Same as wcscpy, but return a pointer after the last written character */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32pcpy)(char32_t *__restrict __buf, char32_t const *__restrict __src) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspcpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src); }
#else /* ... */
#include <local/parts.uchar.string/c32pcpy.h>
/* Same as wcscpy, but return a pointer after the last written character */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32pcpy, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32pcpy)(char32_t *__restrict __buf, char32_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32pcpy))(__buf, __src); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncpy) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16ncpy,(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcsncpy,(__buf,__src,__buflen))
#elif defined(__CRT_HAVE_DOS$wcsncpy)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16ncpy,(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcsncpy,(__buf,__src,__buflen))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsncpy.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16ncpy)(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src, __buflen); }
#else /* ... */
#include <local/parts.uchar.string/c16ncpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ncpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16ncpy)(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ncpy))(__buf, __src, __buflen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncpy) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32ncpy,(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcsncpy,(__buf,__src,__buflen))
#elif defined(__CRT_HAVE_DOS$wcsncpy)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32ncpy,(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcsncpy,(__buf,__src,__buflen))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsncpy.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32ncpy)(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src, __buflen); }
#else /* ... */
#include <local/parts.uchar.string/c32ncpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ncpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32ncpy)(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ncpy))(__buf, __src, __buflen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcspncpy) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as wcsncpy, but return a pointer after the last written character */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16pncpy,(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcspncpy,(__buf,__src,__buflen))
#elif defined(__CRT_HAVE_DOS$wcspncpy)
/* Same as wcsncpy, but return a pointer after the last written character */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16pncpy,(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcspncpy,(__buf,__src,__buflen))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcspncpy.h>
/* Same as wcsncpy, but return a pointer after the last written character */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16pncpy)(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspncpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src, __buflen); }
#else /* ... */
#include <local/parts.uchar.string/c16pncpy.h>
/* Same as wcsncpy, but return a pointer after the last written character */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16pncpy, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16pncpy)(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16pncpy))(__buf, __src, __buflen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcspncpy) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as wcsncpy, but return a pointer after the last written character */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32pncpy,(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcspncpy,(__buf,__src,__buflen))
#elif defined(__CRT_HAVE_DOS$wcspncpy)
/* Same as wcsncpy, but return a pointer after the last written character */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32pncpy,(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcspncpy,(__buf,__src,__buflen))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcspncpy.h>
/* Same as wcsncpy, but return a pointer after the last written character */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32pncpy)(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspncpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src, __buflen); }
#else /* ... */
#include <local/parts.uchar.string/c32pncpy.h>
/* Same as wcsncpy, but return a pointer after the last written character */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32pncpy, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32pncpy)(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32pncpy))(__buf, __src, __buflen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscat) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16cat,(char16_t *__restrict __buf, char16_t const *__restrict __src),wcscat,(__buf,__src))
#elif defined(__CRT_HAVE_DOS$wcscat)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16cat,(char16_t *__restrict __buf, char16_t const *__restrict __src),wcscat,(__buf,__src))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcscat.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16cat)(char16_t *__restrict __buf, char16_t const *__restrict __src) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscat))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src); }
#else /* ... */
#include <local/parts.uchar.string/c16cat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16cat, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16cat)(char16_t *__restrict __buf, char16_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16cat))(__buf, __src); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscat) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32cat,(char32_t *__restrict __buf, char32_t const *__restrict __src),wcscat,(__buf,__src))
#elif defined(__CRT_HAVE_DOS$wcscat)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32cat,(char32_t *__restrict __buf, char32_t const *__restrict __src),wcscat,(__buf,__src))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcscat.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32cat)(char32_t *__restrict __buf, char32_t const *__restrict __src) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscat))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src); }
#else /* ... */
#include <local/parts.uchar.string/c32cat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32cat, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32cat)(char32_t *__restrict __buf, char32_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32cat))(__buf, __src); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncat) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16ncat,(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcsncat,(__buf,__src,__buflen))
#elif defined(__CRT_HAVE_DOS$wcsncat)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16ncat,(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcsncat,(__buf,__src,__buflen))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsncat.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16ncat)(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncat))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src, __buflen); }
#else /* ... */
#include <local/parts.uchar.string/c16ncat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ncat, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16ncat)(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ncat))(__buf, __src, __buflen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncat) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32ncat,(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcsncat,(__buf,__src,__buflen))
#elif defined(__CRT_HAVE_DOS$wcsncat)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32ncat,(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcsncat,(__buf,__src,__buflen))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsncat.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32ncat)(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncat))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src, __buflen); }
#else /* ... */
#include <local/parts.uchar.string/c32ncat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ncat, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32ncat)(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ncat))(__buf, __src, __buflen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsspn) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBDCALL,c16spn,(char16_t const *__haystack, char16_t const *__accept),wcsspn,(__haystack,__accept))
#elif defined(__CRT_HAVE_DOS$wcsspn)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,c16spn,(char16_t const *__haystack, char16_t const *__accept),wcsspn,(__haystack,__accept))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsspn.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16spn)(char16_t const *__haystack, char16_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsspn))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
#else /* ... */
#include <local/parts.uchar.string/c16spn.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16spn, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16spn)(char16_t const *__haystack, char16_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16spn))(__haystack, __accept); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsspn) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBKCALL,c32spn,(char32_t const *__haystack, char32_t const *__accept),wcsspn,(__haystack,__accept))
#elif defined(__CRT_HAVE_DOS$wcsspn)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,c32spn,(char32_t const *__haystack, char32_t const *__accept),wcsspn,(__haystack,__accept))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsspn.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32spn)(char32_t const *__haystack, char32_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsspn))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
#else /* ... */
#include <local/parts.uchar.string/c32spn.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32spn, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32spn)(char32_t const *__haystack, char32_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32spn))(__haystack, __accept); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscspn) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBDCALL,c16cspn,(char16_t const *__haystack, char16_t const *__reject),wcscspn,(__haystack,__reject))
#elif defined(__CRT_HAVE_DOS$wcscspn)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,c16cspn,(char16_t const *__haystack, char16_t const *__reject),wcscspn,(__haystack,__reject))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcscspn.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16cspn)(char16_t const *__haystack, char16_t const *__reject) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscspn))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__reject); }
#else /* ... */
#include <local/parts.uchar.string/c16cspn.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16cspn, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16cspn)(char16_t const *__haystack, char16_t const *__reject) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16cspn))(__haystack, __reject); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscspn) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBKCALL,c32cspn,(char32_t const *__haystack, char32_t const *__reject),wcscspn,(__haystack,__reject))
#elif defined(__CRT_HAVE_DOS$wcscspn)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,c32cspn,(char32_t const *__haystack, char32_t const *__reject),wcscspn,(__haystack,__reject))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcscspn.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32cspn)(char32_t const *__haystack, char32_t const *__reject) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscspn))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__reject); }
#else /* ... */
#include <local/parts.uchar.string/c32cspn.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32cspn, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32cspn)(char32_t const *__haystack, char32_t const *__reject) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32cspn))(__haystack, __reject); })
#endif /* !... */
#if defined(__CRT_HAVE_wcspbrk) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16pbrk,(char16_t *__haystack, char16_t const *__accept),wcspbrk,(__haystack,__accept))
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,__LIBDCALL,c16pbrk,(char16_t const *__haystack, char16_t const *__accept),wcspbrk,(__haystack,__accept))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16pbrk,(char16_t const *__haystack, char16_t const *__accept),wcspbrk,(__haystack,__accept))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcspbrk)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16pbrk,(char16_t *__haystack, char16_t const *__accept),wcspbrk,(__haystack,__accept))
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16pbrk,(char16_t const *__haystack, char16_t const *__accept),wcspbrk,(__haystack,__accept))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16pbrk,(char16_t const *__haystack, char16_t const *__accept),wcspbrk,(__haystack,__accept))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcspbrk.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16pbrk)(char16_t *__haystack, char16_t const *__accept) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16pbrk)(char16_t const *__haystack, char16_t const *__accept) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16pbrk)(char16_t const *__haystack, char16_t const *__accept) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/parts.uchar.string/c16pbrk.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16pbrk)(char16_t *__haystack, char16_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16pbrk))(__haystack, __accept); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16pbrk)(char16_t const *__haystack, char16_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16pbrk))(__haystack, __accept); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16pbrk)(char16_t const *__haystack, char16_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16pbrk))(__haystack, __accept); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcspbrk) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32pbrk,(char32_t *__haystack, char32_t const *__accept),wcspbrk,(__haystack,__accept))
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,__LIBKCALL,c32pbrk,(char32_t const *__haystack, char32_t const *__accept),wcspbrk,(__haystack,__accept))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32pbrk,(char32_t const *__haystack, char32_t const *__accept),wcspbrk,(__haystack,__accept))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcspbrk)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32pbrk,(char32_t *__haystack, char32_t const *__accept),wcspbrk,(__haystack,__accept))
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,c32pbrk,(char32_t const *__haystack, char32_t const *__accept),wcspbrk,(__haystack,__accept))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32pbrk,(char32_t const *__haystack, char32_t const *__accept),wcspbrk,(__haystack,__accept))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcspbrk.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32pbrk)(char32_t *__haystack, char32_t const *__accept) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32pbrk)(char32_t const *__haystack, char32_t const *__accept) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32pbrk)(char32_t const *__haystack, char32_t const *__accept) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/parts.uchar.string/c32pbrk.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32pbrk)(char32_t *__haystack, char32_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32pbrk))(__haystack, __accept); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32pbrk)(char32_t const *__haystack, char32_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32pbrk))(__haystack, __accept); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32pbrk)(char32_t const *__haystack, char32_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32pbrk))(__haystack, __accept); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#ifndef __c16tok_defined
#define __c16tok_defined 1
#if defined(__CRT_HAVE_wcstok) && !defined(__CRT_DOS_PRIMARY) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2, 3)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16tok,(char16_t *__string, char16_t const *__restrict __delim, char16_t **__restrict __save_ptr),wcstok,(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE_DOS$wcstok) && !defined(__CRT_DOS_PRIMARY)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)),char16_t *,__NOTHROW_NCX,c16tok,(char16_t *__string, char16_t const *__restrict __delim, char16_t **__restrict __save_ptr),wcstok,(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE_wcstok_s) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2, 3)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16tok,(char16_t *__string, char16_t const *__restrict __delim, char16_t **__restrict __save_ptr),wcstok_s,(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE_DOS$wcstok_s)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)),char16_t *,__NOTHROW_NCX,c16tok,(char16_t *__string, char16_t const *__restrict __delim, char16_t **__restrict __save_ptr),wcstok_s,(__string,__delim,__save_ptr))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcstok.h>
__FORCELOCAL __ATTR_NONNULL((2, 3)) char16_t *__NOTHROW_NCX(__LIBDCALL c16tok)(char16_t *__string, char16_t const *__restrict __delim, char16_t **__restrict __save_ptr) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstok))((__WCHAR_TYPE__ *)__string, (__WCHAR_TYPE__ const *)__delim, (__WCHAR_TYPE__ **)__save_ptr); }
#else /* ... */
#include <local/parts.uchar.string/c16tok.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16tok, __FORCELOCAL __ATTR_NONNULL((2, 3)) char16_t *__NOTHROW_NCX(__LIBDCALL c16tok)(char16_t *__string, char16_t const *__restrict __delim, char16_t **__restrict __save_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16tok))(__string, __delim, __save_ptr); })
#endif /* !... */
#endif /* !__c16tok_defined */
#ifndef __c32tok_defined
#define __c32tok_defined 1
#if defined(__CRT_HAVE_wcstok) && !defined(__CRT_DOS_PRIMARY) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2, 3)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32tok,(char32_t *__string, char32_t const *__restrict __delim, char32_t **__restrict __save_ptr),wcstok,(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE_DOS$wcstok) && !defined(__CRT_DOS_PRIMARY)
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3)),char32_t *,__NOTHROW_NCX,c32tok,(char32_t *__string, char32_t const *__restrict __delim, char32_t **__restrict __save_ptr),wcstok,(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE_wcstok_s) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2, 3)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32tok,(char32_t *__string, char32_t const *__restrict __delim, char32_t **__restrict __save_ptr),wcstok_s,(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE_DOS$wcstok_s)
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3)),char32_t *,__NOTHROW_NCX,c32tok,(char32_t *__string, char32_t const *__restrict __delim, char32_t **__restrict __save_ptr),wcstok_s,(__string,__delim,__save_ptr))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcstok.h>
__FORCELOCAL __ATTR_NONNULL((2, 3)) char32_t *__NOTHROW_NCX(__LIBKCALL c32tok)(char32_t *__string, char32_t const *__restrict __delim, char32_t **__restrict __save_ptr) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstok))((__WCHAR_TYPE__ *)__string, (__WCHAR_TYPE__ const *)__delim, (__WCHAR_TYPE__ **)__save_ptr); }
#else /* ... */
#include <local/parts.uchar.string/c32tok.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32tok, __FORCELOCAL __ATTR_NONNULL((2, 3)) char32_t *__NOTHROW_NCX(__LIBKCALL c32tok)(char32_t *__string, char32_t const *__restrict __delim, char32_t **__restrict __save_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32tok))(__string, __delim, __save_ptr); })
#endif /* !... */
#endif /* !__c32tok_defined */
#if defined(__CRT_HAVE_wcssep) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16sep,(char16_t **__restrict __stringp, char16_t const *__restrict __delim),wcssep,(__stringp,__delim))
#elif defined(__CRT_HAVE_DOS$wcssep)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16sep,(char16_t **__restrict __stringp, char16_t const *__restrict __delim),wcssep,(__stringp,__delim))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcssep.h>
__FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16sep)(char16_t **__restrict __stringp, char16_t const *__restrict __delim) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcssep))((__WCHAR_TYPE__ **)__stringp, (__WCHAR_TYPE__ const *)__delim); }
#else /* ... */
#include <local/parts.uchar.string/c16sep.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sep, __FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16sep)(char16_t **__restrict __stringp, char16_t const *__restrict __delim) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sep))(__stringp, __delim); })
#endif /* !... */
#if defined(__CRT_HAVE_wcssep) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32sep,(char32_t **__restrict __stringp, char32_t const *__restrict __delim),wcssep,(__stringp,__delim))
#elif defined(__CRT_HAVE_DOS$wcssep)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32sep,(char32_t **__restrict __stringp, char32_t const *__restrict __delim),wcssep,(__stringp,__delim))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcssep.h>
__FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32sep)(char32_t **__restrict __stringp, char32_t const *__restrict __delim) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcssep))((__WCHAR_TYPE__ **)__stringp, (__WCHAR_TYPE__ const *)__delim); }
#else /* ... */
#include <local/parts.uchar.string/c32sep.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sep, __FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32sep)(char32_t **__restrict __stringp, char32_t const *__restrict __delim) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sep))(__stringp, __delim); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsdup) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16dup,(char16_t const *__restrict __string),wcsdup,(__string))
#elif defined(__CRT_HAVE_DOS$_wcsdup)
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16dup,(char16_t const *__restrict __string),_wcsdup,(__string))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsdup.h>
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16dup)(char16_t const *__restrict __string) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsdup))((__WCHAR_TYPE__ const *)__string); }
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <local/parts.uchar.string/c16dup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16dup, __FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16dup)(char16_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16dup))(__string); })
#endif /* ... */
#if defined(__CRT_HAVE_wcsdup) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32dup,(char32_t const *__restrict __string),wcsdup,(__string))
#elif defined(__CRT_HAVE_DOS$wcsdup)
__CREDIRECT_KOS(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32dup,(char32_t const *__restrict __string),wcsdup,(__string))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsdup.h>
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32dup)(char32_t const *__restrict __string) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsdup))((__WCHAR_TYPE__ const *)__string); }
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <local/parts.uchar.string/c32dup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32dup, __FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32dup)(char32_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32dup))(__string); })
#endif /* ... */
#if defined(__CRT_HAVE_wcsndup) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16ndup,(char16_t const *__restrict __string, __SIZE_TYPE__ __max_chars),wcsndup,(__string,__max_chars))
#elif defined(__CRT_HAVE_DOS$wcsndup)
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16ndup,(char16_t const *__restrict __string, __SIZE_TYPE__ __max_chars),wcsndup,(__string,__max_chars))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsndup.h>
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16ndup)(char16_t const *__restrict __string, __SIZE_TYPE__ __max_chars) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsndup))((__WCHAR_TYPE__ const *)__string, __max_chars); }
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <local/parts.uchar.string/c16ndup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ndup, __FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16ndup)(char16_t const *__restrict __string, __SIZE_TYPE__ __max_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ndup))(__string, __max_chars); })
#endif /* ... */
#if defined(__CRT_HAVE_wcsndup) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32ndup,(char32_t const *__restrict __string, __SIZE_TYPE__ __max_chars),wcsndup,(__string,__max_chars))
#elif defined(__CRT_HAVE_DOS$wcsndup)
__CREDIRECT_KOS(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32ndup,(char32_t const *__restrict __string, __SIZE_TYPE__ __max_chars),wcsndup,(__string,__max_chars))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsndup.h>
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32ndup)(char32_t const *__restrict __string, __SIZE_TYPE__ __max_chars) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsndup))((__WCHAR_TYPE__ const *)__string, __max_chars); }
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <local/parts.uchar.string/c32ndup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ndup, __FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32ndup)(char32_t const *__restrict __string, __SIZE_TYPE__ __max_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ndup))(__string, __max_chars); })
#endif /* ... */
#if defined(__CRT_HAVE_wcsfry) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16fry,(char16_t *__restrict __string),wcsfry,(__string))
#elif defined(__CRT_HAVE_DOS$wcsfry)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16fry,(char16_t *__restrict __string),wcsfry,(__string))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsfry.h>
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16fry)(char16_t *__restrict __string) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsfry))((__WCHAR_TYPE__ *)__string); }
#else /* ... */
#include <local/parts.uchar.string/c16fry.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16fry, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16fry)(char16_t *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16fry))(__string); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsfry) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32fry,(char32_t *__restrict __string),wcsfry,(__string))
#elif defined(__CRT_HAVE_DOS$wcsfry)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32fry,(char32_t *__restrict __string),wcsfry,(__string))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsfry.h>
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32fry)(char32_t *__restrict __string) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsfry))((__WCHAR_TYPE__ *)__string); }
#else /* ... */
#include <local/parts.uchar.string/c32fry.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32fry, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32fry)(char32_t *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32fry))(__string); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscasecmp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16casecmp,(char16_t const *__s1, char16_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscasecmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecmp,(char16_t const *__s1, char16_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16casecmp,(char16_t const *__s1, char16_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$_wcsicmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecmp,(char16_t const *__s1, char16_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16casecmp,(char16_t const *__s1, char16_t const *__s2),wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcsicmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecmp,(char16_t const *__s1, char16_t const *__s2),wcsicmp,(__s1,__s2))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcscasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16casecmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <local/parts.uchar.string/c16casecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16casecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16casecmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16casecmp))(__s1, __s2); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscasecmp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32casecmp,(char32_t const *__s1, char32_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscasecmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecmp,(char32_t const *__s1, char32_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32casecmp,(char32_t const *__s1, char32_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$_wcsicmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecmp,(char32_t const *__s1, char32_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32casecmp,(char32_t const *__s1, char32_t const *__s2),wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcsicmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecmp,(char32_t const *__s1, char32_t const *__s2),wcsicmp,(__s1,__s2))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcscasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32casecmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <local/parts.uchar.string/c32casecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32casecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32casecmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32casecmp))(__s1, __s2); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncasecmp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16ncasecmp,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsncasecmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecmp,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16ncasecmp,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$_wcsnicmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecmp,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16ncasecmp,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnicmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecmp,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsncasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16ncasecmp)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* ... */
#include <local/parts.uchar.string/c16ncasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ncasecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16ncasecmp)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ncasecmp))(__s1, __s2, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncasecmp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32ncasecmp,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsncasecmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecmp,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32ncasecmp,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$_wcsnicmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecmp,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32ncasecmp,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnicmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecmp,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsncasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32ncasecmp)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* ... */
#include <local/parts.uchar.string/c32ncasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ncasecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32ncasecmp)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ncasecmp))(__s1, __s2, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsxfrm) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBDCALL,c16xfrm,(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen),wcsxfrm,(__dst,__src,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsxfrm)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,c16xfrm,(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen),wcsxfrm,(__dst,__src,__maxlen))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsxfrm.h>
__FORCELOCAL __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16xfrm)(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __maxlen); }
#else /* ... */
#include <local/parts.uchar.string/c16xfrm.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16xfrm, __FORCELOCAL __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16xfrm)(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16xfrm))(__dst, __src, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsxfrm) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBKCALL,c32xfrm,(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __maxlen),wcsxfrm,(__dst,__src,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsxfrm)
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,c32xfrm,(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __maxlen),wcsxfrm,(__dst,__src,__maxlen))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsxfrm.h>
__FORCELOCAL __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32xfrm)(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __maxlen); }
#else /* ... */
#include <local/parts.uchar.string/c32xfrm.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32xfrm, __FORCELOCAL __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32xfrm)(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32xfrm))(__dst, __src, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscoll) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16coll,(char16_t const *__s1, char16_t const *__s2),wcscoll,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscoll)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16coll,(char16_t const *__s1, char16_t const *__s2),wcscoll,(__s1,__s2))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcscoll.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16coll)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <local/parts.uchar.string/c16coll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16coll, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16coll)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16coll))(__s1, __s2); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscoll) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32coll,(char32_t const *__s1, char32_t const *__s2),wcscoll,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscoll)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32coll,(char32_t const *__s1, char32_t const *__s2),wcscoll,(__s1,__s2))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcscoll.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32coll)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <local/parts.uchar.string/c32coll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32coll, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32coll)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32coll))(__s1, __s2); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncoll) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16ncoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$_wcsncoll)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsncoll,(__s1,__s2,__maxlen))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsncoll.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16ncoll)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* ... */
#include <local/parts.uchar.string/c16ncoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ncoll, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16ncoll)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ncoll))(__s1, __s2, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncoll) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32ncoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsncoll)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncoll,(__s1,__s2,__maxlen))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsncoll.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32ncoll)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* ... */
#include <local/parts.uchar.string/c32ncoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ncoll, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32ncoll)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ncoll))(__s1, __s2, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscasecoll) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16casecoll,(char16_t const *__s1, char16_t const *__s2),wcscasecoll,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$_wcsicoll)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll,(char16_t const *__s1, char16_t const *__s2),_wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicoll) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16casecoll,(char16_t const *__s1, char16_t const *__s2),wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcsicoll)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll,(char16_t const *__s1, char16_t const *__s2),wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcscasecmp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16casecoll,(char16_t const *__s1, char16_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscasecmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll,(char16_t const *__s1, char16_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16casecoll,(char16_t const *__s1, char16_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$_wcsicmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll,(char16_t const *__s1, char16_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16casecoll,(char16_t const *__s1, char16_t const *__s2),wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcsicmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll,(char16_t const *__s1, char16_t const *__s2),wcsicmp,(__s1,__s2))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcscasecoll.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16casecoll)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <local/parts.uchar.string/c16casecoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16casecoll, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16casecoll)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16casecoll))(__s1, __s2); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscasecoll) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32casecoll,(char32_t const *__s1, char32_t const *__s2),wcscasecoll,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscasecoll)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecoll,(char32_t const *__s1, char32_t const *__s2),wcscasecoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicoll) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32casecoll,(char32_t const *__s1, char32_t const *__s2),wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcsicoll)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecoll,(char32_t const *__s1, char32_t const *__s2),wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcscasecmp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32casecoll,(char32_t const *__s1, char32_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscasecmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecoll,(char32_t const *__s1, char32_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32casecoll,(char32_t const *__s1, char32_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$_wcsicmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecoll,(char32_t const *__s1, char32_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32casecoll,(char32_t const *__s1, char32_t const *__s2),wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcsicmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecoll,(char32_t const *__s1, char32_t const *__s2),wcsicmp,(__s1,__s2))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcscasecoll.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32casecoll)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <local/parts.uchar.string/c32casecoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32casecoll, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32casecoll)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32casecoll))(__s1, __s2); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncasecoll) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16ncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$_wcsnicoll)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsncasecmp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16ncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsncasecmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16ncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$_wcsnicmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16ncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnicmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsncasecoll.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16ncasecoll)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* ... */
#include <local/parts.uchar.string/c16ncasecoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ncasecoll, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16ncasecoll)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ncasecoll))(__s1, __s2, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncasecoll) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32ncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsncasecoll)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsncasecmp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32ncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsncasecmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32ncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$_wcsnicmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32ncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnicmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsncasecoll.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32ncasecoll)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* ... */
#include <local/parts.uchar.string/c32ncasecoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ncasecoll, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32ncasecoll)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ncasecoll))(__s1, __s2, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcslwr) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16lwr,(char16_t *__restrict __str),wcslwr,(__str))
#elif defined(__CRT_HAVE_DOS$_wcslwr) && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16lwr,(char16_t *__restrict __str),_wcslwr,(__str))
#elif defined(__CRT_HAVE_DOS$DOS$_wcslwr)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16lwr,(char16_t *__restrict __str),DOS$_wcslwr,(__str))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcslwr.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16lwr)(char16_t *__restrict __str) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr))((__WCHAR_TYPE__ *)__str); }
#else /* ... */
#include <local/parts.uchar.string/c16lwr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16lwr, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16lwr)(char16_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16lwr))(__str); })
#endif /* !... */
#if defined(__CRT_HAVE_wcslwr) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32lwr,(char32_t *__restrict __str),wcslwr,(__str))
#elif defined(__CRT_HAVE_DOS$wcslwr) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32lwr,(char32_t *__restrict __str),wcslwr,(__str))
#elif defined(__CRT_HAVE_DOS$KOS$wcslwr)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32lwr,(char32_t *__restrict __str),KOS$wcslwr,(__str))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcslwr.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32lwr)(char32_t *__restrict __str) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr))((__WCHAR_TYPE__ *)__str); }
#else /* ... */
#include <local/parts.uchar.string/c32lwr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32lwr, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32lwr)(char32_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32lwr))(__str); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsupr) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16upr,(char16_t *__restrict __str),wcsupr,(__str))
#elif defined(__CRT_HAVE_DOS$_wcsupr) && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16upr,(char16_t *__restrict __str),_wcsupr,(__str))
#elif defined(__CRT_HAVE_DOS$DOS$_wcsupr)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16upr,(char16_t *__restrict __str),DOS$_wcsupr,(__str))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsupr.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16upr)(char16_t *__restrict __str) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr))((__WCHAR_TYPE__ *)__str); }
#else /* ... */
#include <local/parts.uchar.string/c16upr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16upr, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16upr)(char16_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16upr))(__str); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsupr) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32upr,(char32_t *__restrict __str),wcsupr,(__str))
#elif defined(__CRT_HAVE_DOS$wcsupr) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32upr,(char32_t *__restrict __str),wcsupr,(__str))
#elif defined(__CRT_HAVE_DOS$KOS$wcsupr)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32upr,(char32_t *__restrict __str),KOS$wcsupr,(__str))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsupr.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32upr)(char32_t *__restrict __str) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr))((__WCHAR_TYPE__ *)__str); }
#else /* ... */
#include <local/parts.uchar.string/c32upr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32upr, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32upr)(char32_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32upr))(__str); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsrev) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16rev,(char16_t *__restrict __str),wcsrev,(__str))
#elif defined(__CRT_HAVE_DOS$_wcsrev)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16rev,(char16_t *__restrict __str),_wcsrev,(__str))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsrev.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16rev)(char16_t *__restrict __str) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrev))((__WCHAR_TYPE__ *)__str); }
#else /* ... */
#include <local/parts.uchar.string/c16rev.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16rev, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16rev)(char16_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rev))(__str); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsrev) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32rev,(char32_t *__restrict __str),wcsrev,(__str))
#elif defined(__CRT_HAVE_DOS$wcsrev)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32rev,(char32_t *__restrict __str),wcsrev,(__str))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsrev.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32rev)(char32_t *__restrict __str) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrev))((__WCHAR_TYPE__ *)__str); }
#else /* ... */
#include <local/parts.uchar.string/c32rev.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32rev, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32rev)(char32_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32rev))(__str); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnrev) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16nrev,(char16_t *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnrev,(__str,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnrev)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nrev,(char16_t *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnrev,(__str,__maxlen))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsnrev.h>
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nrev)(char16_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrev))((__WCHAR_TYPE__ *)__str, __maxlen); }
#else /* ... */
#include <local/parts.uchar.string/c16nrev.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16nrev, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nrev)(char16_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nrev))(__str, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnrev) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32nrev,(char32_t *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnrev,(__str,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnrev)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nrev,(char32_t *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnrev,(__str,__maxlen))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsnrev.h>
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nrev)(char32_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrev))((__WCHAR_TYPE__ *)__str, __maxlen); }
#else /* ... */
#include <local/parts.uchar.string/c32nrev.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32nrev, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nrev)(char32_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nrev))(__str, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsset) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16set,(char16_t *__restrict __str, int __ch),wcsset,(__str,__ch))
#elif defined(__CRT_HAVE_DOS$_wcsset) && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16set,(char16_t *__restrict __str, int __ch),_wcsset,(__str,__ch))
#elif defined(__CRT_HAVE_DOS$DOS$_wcsset)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16set,(char16_t *__restrict __str, int __ch),DOS$_wcsset,(__str,__ch))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsset.h>
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16set)(char16_t *__restrict __str, int __ch) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsset))((__WCHAR_TYPE__ *)__str, __ch); }
#else /* ... */
#include <local/parts.uchar.string/c16set.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16set, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16set)(char16_t *__restrict __str, int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16set))(__str, __ch); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsset) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32set,(char32_t *__restrict __str, int __ch),wcsset,(__str,__ch))
#elif defined(__CRT_HAVE_DOS$wcsset) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32set,(char32_t *__restrict __str, int __ch),wcsset,(__str,__ch))
#elif defined(__CRT_HAVE_DOS$KOS$wcsset)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32set,(char32_t *__restrict __str, int __ch),KOS$wcsset,(__str,__ch))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsset.h>
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32set)(char32_t *__restrict __str, int __ch) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsset))((__WCHAR_TYPE__ *)__str, __ch); }
#else /* ... */
#include <local/parts.uchar.string/c32set.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32set, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32set)(char32_t *__restrict __str, int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32set))(__str, __ch); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnset) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16nset,(char16_t *__restrict __str, char16_t __ch, __SIZE_TYPE__ __maxlen),wcsnset,(__str,__ch,__maxlen))
#elif defined(__CRT_HAVE_DOS$_wcsnset)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nset,(char16_t *__restrict __str, char16_t __ch, __SIZE_TYPE__ __maxlen),_wcsnset,(__str,__ch,__maxlen))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsnset.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nset)(char16_t *__restrict __str, char16_t __ch, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnset))((__WCHAR_TYPE__ *)__str, (__WCHAR_TYPE__)__ch, __maxlen); }
#else /* ... */
#include <local/parts.uchar.string/c16nset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16nset, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16nset)(char16_t *__restrict __str, char16_t __ch, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nset))(__str, __ch, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnset) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32nset,(char32_t *__restrict __str, char32_t __ch, __SIZE_TYPE__ __maxlen),wcsnset,(__str,__ch,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnset)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nset,(char32_t *__restrict __str, char32_t __ch, __SIZE_TYPE__ __maxlen),wcsnset,(__str,__ch,__maxlen))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsnset.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nset)(char32_t *__restrict __str, char32_t __ch, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnset))((__WCHAR_TYPE__ *)__str, (__WCHAR_TYPE__)__ch, __maxlen); }
#else /* ... */
#include <local/parts.uchar.string/c32nset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32nset, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32nset)(char32_t *__restrict __str, char32_t __ch, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nset))(__str, __ch, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wmemcmp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBDCALL,fuzzy_c16memcmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_chars, char16_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_wmemcmp,(__s1,__s1_chars,__s2,__s2_chars))
#elif defined(__CRT_HAVE_DOS$fuzzy_wmemcmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16memcmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_chars, char16_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_wmemcmp,(__s1,__s1_chars,__s2,__s2_chars))
#elif defined(__CRT_HAVE_fuzzy_memcmpw) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBDCALL,fuzzy_c16memcmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_chars, char16_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_memcmpw,(__s1,__s1_chars,__s2,__s2_chars))
#elif defined(__CRT_HAVE_DOS$fuzzy_memcmpw)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16memcmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_chars, char16_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_memcmpw,(__s1,__s1_chars,__s2,__s2_chars))
#else /* ... */
#include <parts/malloca.h>
#if !defined(__NO_MALLOCA) && (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/fuzzy_wmemcmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16memcmp)(char16_t const *__s1, __SIZE_TYPE__ __s1_chars, char16_t const *__s2, __SIZE_TYPE__ __s2_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcmp))((__WCHAR_TYPE__ const *)__s1, __s1_chars, (__WCHAR_TYPE__ const *)__s2, __s2_chars); }
#else /* !__NO_MALLOCA && (__SIZEOF_WCHAR_T__ == 2) */
#include <parts/malloca.h>
#ifndef __NO_MALLOCA
#include <local/parts.uchar.string/fuzzy_c16memcmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16memcmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16memcmp)(char16_t const *__s1, __SIZE_TYPE__ __s1_chars, char16_t const *__s2, __SIZE_TYPE__ __s2_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16memcmp))(__s1, __s1_chars, __s2, __s2_chars); })
#endif /* !__NO_MALLOCA */
#endif /* __NO_MALLOCA || !(__SIZEOF_WCHAR_T__ == 2) */
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wmemcmp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBKCALL,fuzzy_c32memcmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_chars, char32_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_wmemcmp,(__s1,__s1_chars,__s2,__s2_chars))
#elif defined(__CRT_HAVE_DOS$fuzzy_wmemcmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32memcmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_chars, char32_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_wmemcmp,(__s1,__s1_chars,__s2,__s2_chars))
#elif defined(__CRT_HAVE_fuzzy_memcmpl) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBKCALL,fuzzy_c32memcmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_chars, char32_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_memcmpl,(__s1,__s1_chars,__s2,__s2_chars))
#elif defined(__CRT_HAVE_DOS$fuzzy_memcmpl)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32memcmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_chars, char32_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_memcmpl,(__s1,__s1_chars,__s2,__s2_chars))
#else /* ... */
#include <parts/malloca.h>
#if !defined(__NO_MALLOCA) && (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/fuzzy_wmemcmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32memcmp)(char32_t const *__s1, __SIZE_TYPE__ __s1_chars, char32_t const *__s2, __SIZE_TYPE__ __s2_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcmp))((__WCHAR_TYPE__ const *)__s1, __s1_chars, (__WCHAR_TYPE__ const *)__s2, __s2_chars); }
#else /* !__NO_MALLOCA && (__SIZEOF_WCHAR_T__ == 4) */
#include <parts/malloca.h>
#ifndef __NO_MALLOCA
#include <local/parts.uchar.string/fuzzy_c32memcmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32memcmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32memcmp)(char32_t const *__s1, __SIZE_TYPE__ __s1_chars, char32_t const *__s2, __SIZE_TYPE__ __s2_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32memcmp))(__s1, __s1_chars, __s2, __s2_chars); })
#endif /* !__NO_MALLOCA */
#endif /* __NO_MALLOCA || !(__SIZEOF_WCHAR_T__ == 4) */
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wmemcasecmp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBDCALL,fuzzy_c16memcasecmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes),fuzzy_wmemcasecmp,(__s1,__s1_bytes,__s2,__s2_bytes))
#elif defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16memcasecmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes),fuzzy_wmemcasecmp,(__s1,__s1_bytes,__s2,__s2_bytes))
#else /* ... */
#include <parts/malloca.h>
#if !defined(__NO_MALLOCA) && (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/fuzzy_wmemcasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16memcasecmp)(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcasecmp))((__WCHAR_TYPE__ const *)__s1, __s1_bytes, (__WCHAR_TYPE__ const *)__s2, __s2_bytes); }
#else /* !__NO_MALLOCA && (__SIZEOF_WCHAR_T__ == 2) */
#include <parts/malloca.h>
#ifndef __NO_MALLOCA
#include <local/parts.uchar.string/fuzzy_c16memcasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16memcasecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16memcasecmp)(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16memcasecmp))(__s1, __s1_bytes, __s2, __s2_bytes); })
#endif /* !__NO_MALLOCA */
#endif /* __NO_MALLOCA || !(__SIZEOF_WCHAR_T__ == 2) */
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wmemcasecmp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBKCALL,fuzzy_c32memcasecmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_bytes, char32_t const *__s2, __SIZE_TYPE__ __s2_bytes),fuzzy_wmemcasecmp,(__s1,__s1_bytes,__s2,__s2_bytes))
#elif defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32memcasecmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_bytes, char32_t const *__s2, __SIZE_TYPE__ __s2_bytes),fuzzy_wmemcasecmp,(__s1,__s1_bytes,__s2,__s2_bytes))
#else /* ... */
#include <parts/malloca.h>
#if !defined(__NO_MALLOCA) && (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/fuzzy_wmemcasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32memcasecmp)(char32_t const *__s1, __SIZE_TYPE__ __s1_bytes, char32_t const *__s2, __SIZE_TYPE__ __s2_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcasecmp))((__WCHAR_TYPE__ const *)__s1, __s1_bytes, (__WCHAR_TYPE__ const *)__s2, __s2_bytes); }
#else /* !__NO_MALLOCA && (__SIZEOF_WCHAR_T__ == 4) */
#include <parts/malloca.h>
#ifndef __NO_MALLOCA
#include <local/parts.uchar.string/fuzzy_c32memcasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32memcasecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32memcasecmp)(char32_t const *__s1, __SIZE_TYPE__ __s1_bytes, char32_t const *__s2, __SIZE_TYPE__ __s2_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32memcasecmp))(__s1, __s1_bytes, __s2, __s2_bytes); })
#endif /* !__NO_MALLOCA */
#endif /* __NO_MALLOCA || !(__SIZEOF_WCHAR_T__ == 4) */
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wcscmp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBDCALL,fuzzy_c16cmp,(char16_t const *__s1, char16_t const *__s2),fuzzy_wcscmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$fuzzy_wcscmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16cmp,(char16_t const *__s1, char16_t const *__s2),fuzzy_wcscmp,(__s1,__s2))
#elif (defined(__CRT_HAVE_fuzzy_wmemcmp) || (defined(__CRT_HAVE_DOS$fuzzy_wmemcmp) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$fuzzy_wmemcmp) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_fuzzy_memcmpw) && (__SIZEOF_WCHAR_T__ == 2)) || (defined(__CRT_HAVE_fuzzy_memcmpl) && (__SIZEOF_WCHAR_T__ == 4)) || !defined(__NO_MALLOCA)) && (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/fuzzy_wcscmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16cmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#elif (defined(__CRT_HAVE_fuzzy_wmemcmp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fuzzy_wmemcmp) || (defined(__CRT_HAVE_fuzzy_memcmpw) && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fuzzy_memcmpw) || !defined(__NO_MALLOCA)
#include <local/parts.uchar.string/fuzzy_c16cmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16cmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16cmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16cmp))(__s1, __s2); })
#endif /* ... */
#if defined(__CRT_HAVE_fuzzy_wcscmp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBKCALL,fuzzy_c32cmp,(char32_t const *__s1, char32_t const *__s2),fuzzy_wcscmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$fuzzy_wcscmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32cmp,(char32_t const *__s1, char32_t const *__s2),fuzzy_wcscmp,(__s1,__s2))
#elif (defined(__CRT_HAVE_fuzzy_wmemcmp) || (defined(__CRT_HAVE_DOS$fuzzy_wmemcmp) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$fuzzy_wmemcmp) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_fuzzy_memcmpw) && (__SIZEOF_WCHAR_T__ == 2)) || (defined(__CRT_HAVE_fuzzy_memcmpl) && (__SIZEOF_WCHAR_T__ == 4)) || !defined(__NO_MALLOCA)) && (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/fuzzy_wcscmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32cmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#elif (defined(__CRT_HAVE_fuzzy_wmemcmp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_DOS$fuzzy_wmemcmp) || (defined(__CRT_HAVE_fuzzy_memcmpl) && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_DOS$fuzzy_memcmpl) || !defined(__NO_MALLOCA)
#include <local/parts.uchar.string/fuzzy_c32cmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32cmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32cmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32cmp))(__s1, __s2); })
#endif /* ... */
#if defined(__CRT_HAVE_fuzzy_wcsncmp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBDCALL,fuzzy_c16ncmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen),fuzzy_wcsncmp,(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif defined(__CRT_HAVE_DOS$fuzzy_wcsncmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16ncmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen),fuzzy_wcsncmp,(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif (defined(__CRT_HAVE_fuzzy_wmemcmp) || (defined(__CRT_HAVE_DOS$fuzzy_wmemcmp) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$fuzzy_wmemcmp) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_fuzzy_memcmpw) && (__SIZEOF_WCHAR_T__ == 2)) || (defined(__CRT_HAVE_fuzzy_memcmpl) && (__SIZEOF_WCHAR_T__ == 4)) || !defined(__NO_MALLOCA)) && (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/fuzzy_wcsncmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16ncmp)(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncmp))((__WCHAR_TYPE__ const *)__s1, __s1_maxlen, (__WCHAR_TYPE__ const *)__s2, __s2_maxlen); }
#elif (defined(__CRT_HAVE_fuzzy_wmemcmp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fuzzy_wmemcmp) || (defined(__CRT_HAVE_fuzzy_memcmpw) && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fuzzy_memcmpw) || !defined(__NO_MALLOCA)
#include <local/parts.uchar.string/fuzzy_c16ncmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16ncmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16ncmp)(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16ncmp))(__s1, __s1_maxlen, __s2, __s2_maxlen); })
#endif /* ... */
#if defined(__CRT_HAVE_fuzzy_wcsncmp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBKCALL,fuzzy_c32ncmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen),fuzzy_wcsncmp,(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif defined(__CRT_HAVE_DOS$fuzzy_wcsncmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32ncmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen),fuzzy_wcsncmp,(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif (defined(__CRT_HAVE_fuzzy_wmemcmp) || (defined(__CRT_HAVE_DOS$fuzzy_wmemcmp) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$fuzzy_wmemcmp) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_fuzzy_memcmpw) && (__SIZEOF_WCHAR_T__ == 2)) || (defined(__CRT_HAVE_fuzzy_memcmpl) && (__SIZEOF_WCHAR_T__ == 4)) || !defined(__NO_MALLOCA)) && (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/fuzzy_wcsncmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32ncmp)(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncmp))((__WCHAR_TYPE__ const *)__s1, __s1_maxlen, (__WCHAR_TYPE__ const *)__s2, __s2_maxlen); }
#elif (defined(__CRT_HAVE_fuzzy_wmemcmp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_DOS$fuzzy_wmemcmp) || (defined(__CRT_HAVE_fuzzy_memcmpl) && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_DOS$fuzzy_memcmpl) || !defined(__NO_MALLOCA)
#include <local/parts.uchar.string/fuzzy_c32ncmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32ncmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32ncmp)(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32ncmp))(__s1, __s1_maxlen, __s2, __s2_maxlen); })
#endif /* ... */
#if defined(__CRT_HAVE_fuzzy_wcscasecmp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBDCALL,fuzzy_c16casecmp,(char16_t const *__s1, char16_t const *__s2),fuzzy_wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$fuzzy_wcscasecmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16casecmp,(char16_t const *__s1, char16_t const *__s2),fuzzy_wcscasecmp,(__s1,__s2))
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp) || (defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp) && __SIZEOF_WCHAR_T__ == 2) || !defined(__NO_MALLOCA)) && (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/fuzzy_wcscasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16casecmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscasecmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp) || !defined(__NO_MALLOCA)
#include <local/parts.uchar.string/fuzzy_c16casecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16casecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16casecmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16casecmp))(__s1, __s2); })
#endif /* ... */
#if defined(__CRT_HAVE_fuzzy_wcscasecmp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBKCALL,fuzzy_c32casecmp,(char32_t const *__s1, char32_t const *__s2),fuzzy_wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$fuzzy_wcscasecmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32casecmp,(char32_t const *__s1, char32_t const *__s2),fuzzy_wcscasecmp,(__s1,__s2))
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp) || (defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp) && __SIZEOF_WCHAR_T__ == 2) || !defined(__NO_MALLOCA)) && (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/fuzzy_wcscasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32casecmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscasecmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp) || !defined(__NO_MALLOCA)
#include <local/parts.uchar.string/fuzzy_c32casecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32casecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32casecmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32casecmp))(__s1, __s2); })
#endif /* ... */
#if defined(__CRT_HAVE_fuzzy_wcsncasecmp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBDCALL,fuzzy_c16ncasecmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen),fuzzy_wcsncasecmp,(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif defined(__CRT_HAVE_DOS$fuzzy_wcsncasecmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16ncasecmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen),fuzzy_wcsncasecmp,(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp) || (defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp) && __SIZEOF_WCHAR_T__ == 2) || !defined(__NO_MALLOCA)) && (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/fuzzy_wcsncasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16ncasecmp)(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncasecmp))((__WCHAR_TYPE__ const *)__s1, __s1_maxlen, (__WCHAR_TYPE__ const *)__s2, __s2_maxlen); }
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp) || !defined(__NO_MALLOCA)
#include <local/parts.uchar.string/fuzzy_c16ncasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16ncasecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16ncasecmp)(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16ncasecmp))(__s1, __s1_maxlen, __s2, __s2_maxlen); })
#endif /* ... */
#if defined(__CRT_HAVE_fuzzy_wcsncasecmp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBKCALL,fuzzy_c32ncasecmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen),fuzzy_wcsncasecmp,(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif defined(__CRT_HAVE_DOS$fuzzy_wcsncasecmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32ncasecmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen),fuzzy_wcsncasecmp,(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp) || (defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp) && __SIZEOF_WCHAR_T__ == 2) || !defined(__NO_MALLOCA)) && (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/fuzzy_wcsncasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32ncasecmp)(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncasecmp))((__WCHAR_TYPE__ const *)__s1, __s1_maxlen, (__WCHAR_TYPE__ const *)__s2, __s2_maxlen); }
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp) || !defined(__NO_MALLOCA)
#include <local/parts.uchar.string/fuzzy_c32ncasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32ncasecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32ncasecmp)(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32ncasecmp))(__s1, __s1_maxlen, __s2, __s2_maxlen); })
#endif /* ... */
#if defined(__CRT_HAVE_wildwcscmp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,wildc16cmp,(char16_t const *__pattern, char16_t const *__string),wildwcscmp,(__pattern,__string))
#elif defined(__CRT_HAVE_DOS$wildwcscmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildc16cmp,(char16_t const *__pattern, char16_t const *__string),wildwcscmp,(__pattern,__string))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wildwcscmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL wildc16cmp)(char16_t const *__pattern, char16_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscmp))((__WCHAR_TYPE__ const *)__pattern, (__WCHAR_TYPE__ const *)__string); }
#else /* ... */
#include <local/parts.uchar.string/wildc16cmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildc16cmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL wildc16cmp)(char16_t const *__pattern, char16_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildc16cmp))(__pattern, __string); })
#endif /* !... */
#if defined(__CRT_HAVE_wildwcscmp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,wildc32cmp,(char32_t const *__pattern, char32_t const *__string),wildwcscmp,(__pattern,__string))
#elif defined(__CRT_HAVE_DOS$wildwcscmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildc32cmp,(char32_t const *__pattern, char32_t const *__string),wildwcscmp,(__pattern,__string))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wildwcscmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL wildc32cmp)(char32_t const *__pattern, char32_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscmp))((__WCHAR_TYPE__ const *)__pattern, (__WCHAR_TYPE__ const *)__string); }
#else /* ... */
#include <local/parts.uchar.string/wildc32cmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildc32cmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL wildc32cmp)(char32_t const *__pattern, char32_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildc32cmp))(__pattern, __string); })
#endif /* !... */
#if defined(__CRT_HAVE_wildwcscasecmp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,wildc16casecmp,(char16_t const *__pattern, char16_t const *__string),wildwcscasecmp,(__pattern,__string))
#elif defined(__CRT_HAVE_DOS$wildwcscasecmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildc16casecmp,(char16_t const *__pattern, char16_t const *__string),wildwcscasecmp,(__pattern,__string))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wildwcscasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL wildc16casecmp)(char16_t const *__pattern, char16_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscasecmp))((__WCHAR_TYPE__ const *)__pattern, (__WCHAR_TYPE__ const *)__string); }
#else /* ... */
#include <local/parts.uchar.string/wildc16casecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildc16casecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL wildc16casecmp)(char16_t const *__pattern, char16_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildc16casecmp))(__pattern, __string); })
#endif /* !... */
#if defined(__CRT_HAVE_wildwcscasecmp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,wildc32casecmp,(char32_t const *__pattern, char32_t const *__string),wildwcscasecmp,(__pattern,__string))
#elif defined(__CRT_HAVE_DOS$wildwcscasecmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildc32casecmp,(char32_t const *__pattern, char32_t const *__string),wildwcscasecmp,(__pattern,__string))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wildwcscasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL wildc32casecmp)(char32_t const *__pattern, char32_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscasecmp))((__WCHAR_TYPE__ const *)__pattern, (__WCHAR_TYPE__ const *)__string); }
#else /* ... */
#include <local/parts.uchar.string/wildc32casecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildc32casecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL wildc32casecmp)(char32_t const *__pattern, char32_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildc32casecmp))(__pattern, __string); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsverscmp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16verscmp,(char16_t const *__s1, char16_t const *__s2),wcsverscmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcsverscmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16verscmp,(char16_t const *__s1, char16_t const *__s2),wcsverscmp,(__s1,__s2))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsverscmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16verscmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsverscmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <local/parts.uchar.string/c16verscmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16verscmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16verscmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16verscmp))(__s1, __s2); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsverscmp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32verscmp,(char32_t const *__s1, char32_t const *__s2),wcsverscmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcsverscmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32verscmp,(char32_t const *__s1, char32_t const *__s2),wcsverscmp,(__s1,__s2))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsverscmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32verscmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsverscmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <local/parts.uchar.string/c32verscmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32verscmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32verscmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32verscmp))(__s1, __s2); })
#endif /* !... */
#ifdef __USE_XOPEN2K8
#if defined(__CRT_HAVE_wcscasestr_l) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16casestr_l,(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale),wcscasestr_l,(__haystack,__needle,__locale))
#elif defined(__CRT_HAVE_DOS$wcscasestr_l) && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr_l,(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale),wcscasestr_l,(__haystack,__needle,__locale))
#elif defined(__CRT_HAVE_DOS$DOS$wcscasestr_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr_l,(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale),DOS$wcscasestr_l,(__haystack,__needle,__locale))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcscasestr_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16casestr_l)(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr_l))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle, __locale); }
#else /* ... */
#include <local/parts.uchar.string/c16casestr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16casestr_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16casestr_l)(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16casestr_l))(__haystack, __needle, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscasestr_l) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32casestr_l,(char32_t const *__haystack, char32_t const *__needle, __locale_t __locale),wcscasestr_l,(__haystack,__needle,__locale))
#elif defined(__CRT_HAVE_DOS$wcscasestr_l) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32casestr_l,(char32_t const *__haystack, char32_t const *__needle, __locale_t __locale),wcscasestr_l,(__haystack,__needle,__locale))
#elif defined(__CRT_HAVE_DOS$KOS$wcscasestr_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32casestr_l,(char32_t const *__haystack, char32_t const *__needle, __locale_t __locale),KOS$wcscasestr_l,(__haystack,__needle,__locale))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcscasestr_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32casestr_l)(char32_t const *__haystack, char32_t const *__needle, __locale_t __locale) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr_l))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle, __locale); }
#else /* ... */
#include <local/parts.uchar.string/c32casestr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32casestr_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32casestr_l)(char32_t const *__haystack, char32_t const *__needle, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32casestr_l))(__haystack, __needle, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscasecmp_l) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16casecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$wcscasecmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16casecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsicmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcsicmp_l) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16casecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$wcsicmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___wcscasecmp_l) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16casecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),__wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$__wcscasecmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),__wcscasecmp_l,(__s1,__s2,__locale))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcscasecmp_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16casecmp_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#else /* ... */
#include <local/parts.uchar.string/c16casecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16casecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16casecmp_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16casecmp_l))(__s1, __s2, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscasecmp_l) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32casecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$wcscasecmp_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32casecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsicmp_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcsicmp_l) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32casecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$wcsicmp_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___wcscasecmp_l) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32casecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),__wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$__wcscasecmp_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),__wcscasecmp_l,(__s1,__s2,__locale))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcscasecmp_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32casecmp_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#else /* ... */
#include <local/parts.uchar.string/c32casecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32casecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32casecmp_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32casecmp_l))(__s1, __s2, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncasecmp_l) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16ncasecmp_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$wcsncasecmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecmp_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicmp_l) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16ncasecmp_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsnicmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecmp_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_wcsnicmp_l) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16ncasecmp_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$wcsnicmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecmp_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE___wcsncasecmp_l) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16ncasecmp_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$__wcsncasecmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecmp_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsncasecmp_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16ncasecmp_l)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen, __locale); }
#else /* ... */
#include <local/parts.uchar.string/c16ncasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ncasecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16ncasecmp_l)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ncasecmp_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncasecmp_l) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32ncasecmp_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$wcsncasecmp_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecmp_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicmp_l) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32ncasecmp_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsnicmp_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecmp_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_wcsnicmp_l) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32ncasecmp_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$wcsnicmp_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecmp_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE___wcsncasecmp_l) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32ncasecmp_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$__wcsncasecmp_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecmp_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsncasecmp_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32ncasecmp_l)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen, __locale); }
#else /* ... */
#include <local/parts.uchar.string/c32ncasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ncasecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32ncasecmp_l)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ncasecmp_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsxfrm_l) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBDCALL,c16xfrm_l,(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$wcsxfrm_l)
__CREDIRECT_DOS(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,c16xfrm_l,(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsxfrm_l) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBDCALL,c16xfrm_l,(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsxfrm_l)
__CREDIRECT_DOS(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,c16xfrm_l,(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE___wcsxfrm_l) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBDCALL,c16xfrm_l,(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$__wcsxfrm_l)
__CREDIRECT_DOS(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,c16xfrm_l,(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsxfrm_l.h>
__FORCELOCAL __ATTR_NONNULL((2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16xfrm_l)(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm_l))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __maxlen, __locale); }
#else /* ... */
#include <local/parts.uchar.string/c16xfrm_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16xfrm_l, __FORCELOCAL __ATTR_NONNULL((2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16xfrm_l)(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16xfrm_l))(__dst, __src, __maxlen, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsxfrm_l) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBKCALL,c32xfrm_l,(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$wcsxfrm_l)
__CREDIRECT_KOS(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,c32xfrm_l,(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsxfrm_l) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBKCALL,c32xfrm_l,(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsxfrm_l)
__CREDIRECT_KOS(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,c32xfrm_l,(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE___wcsxfrm_l) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBKCALL,c32xfrm_l,(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$__wcsxfrm_l)
__CREDIRECT_KOS(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,c32xfrm_l,(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsxfrm_l.h>
__FORCELOCAL __ATTR_NONNULL((2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32xfrm_l)(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm_l))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __maxlen, __locale); }
#else /* ... */
#include <local/parts.uchar.string/c32xfrm_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32xfrm_l, __FORCELOCAL __ATTR_NONNULL((2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32xfrm_l)(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32xfrm_l))(__dst, __src, __maxlen, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscoll_l) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16coll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$wcscoll_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16coll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcscoll_l) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16coll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$_wcscoll_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16coll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___wcscoll_l) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16coll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),__wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$__wcscoll_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16coll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),__wcscoll_l,(__s1,__s2,__locale))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcscoll_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16coll_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#else /* ... */
#include <local/parts.uchar.string/c16coll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16coll_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16coll_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16coll_l))(__s1, __s2, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscoll_l) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32coll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$wcscoll_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32coll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcscoll_l) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32coll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),_wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$_wcscoll_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32coll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),_wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___wcscoll_l) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32coll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),__wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$__wcscoll_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32coll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),__wcscoll_l,(__s1,__s2,__locale))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcscoll_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32coll_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#else /* ... */
#include <local/parts.uchar.string/c32coll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32coll_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32coll_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32coll_l))(__s1, __s2, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncoll_l) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16ncoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsncoll_l) && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$DOS$_wcsncoll_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),DOS$_wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsncoll_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16ncoll_l)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen, __locale); }
#else /* ... */
#include <local/parts.uchar.string/c16ncoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ncoll_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16ncoll_l)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ncoll_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncoll_l) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32ncoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$wcsncoll_l) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$KOS$wcsncoll_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),KOS$wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsncoll_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32ncoll_l)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen, __locale); }
#else /* ... */
#include <local/parts.uchar.string/c32ncoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ncoll_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32ncoll_l)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ncoll_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscasecoll_l) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16casecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscasecoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsicoll_l) && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcsicoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$DOS$_wcsicoll_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),DOS$_wcsicoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcscasecmp_l) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16casecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$wcscasecmp_l) && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$DOS$wcscasecmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),DOS$wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16casecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsicmp_l) && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$DOS$_wcsicmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),DOS$_wcsicmp_l,(__s1,__s2,__locale))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcscasecoll_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16casecoll_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#else /* ... */
#include <local/parts.uchar.string/c16casecoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16casecoll_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16casecoll_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16casecoll_l))(__s1, __s2, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscasecoll_l) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32casecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcscasecoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$wcscasecoll_l) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcscasecoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$KOS$wcscasecoll_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),KOS$wcscasecoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcscasecmp_l) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32casecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$wcscasecmp_l) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$KOS$wcscasecmp_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),KOS$wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32casecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsicmp_l) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$KOS$_wcsicmp_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),KOS$_wcsicmp_l,(__s1,__s2,__locale))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcscasecoll_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32casecoll_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#else /* ... */
#include <local/parts.uchar.string/c32casecoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32casecoll_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32casecoll_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32casecoll_l))(__s1, __s2, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncasecoll_l) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16ncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsnicoll_l) && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$DOS$_wcsnicoll_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),DOS$_wcsnicoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_wcsncasecmp_l) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16ncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$wcsncasecmp_l) && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$DOS$wcsncasecmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),DOS$wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicmp_l) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,c16ncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsnicmp_l) && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$DOS$_wcsnicmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),DOS$_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsncasecoll_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16ncasecoll_l)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen, __locale); }
#else /* ... */
#include <local/parts.uchar.string/c16ncasecoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ncasecoll_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16ncasecoll_l)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ncasecoll_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncasecoll_l) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32ncasecoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$wcsncasecoll_l) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$KOS$wcsncasecoll_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),KOS$wcsncasecoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_wcsncasecmp_l) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32ncasecoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$wcsncasecmp_l) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$KOS$wcsncasecmp_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),KOS$wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicmp_l) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,c32ncasecoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsnicmp_l) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$KOS$_wcsnicmp_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),KOS$_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsncasecoll_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32ncasecoll_l)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen, __locale); }
#else /* ... */
#include <local/parts.uchar.string/c32ncasecoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ncasecoll_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32ncasecoll_l)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ncasecoll_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcslwr_l) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16lwr_l,(char16_t *__restrict __str, __locale_t __locale),wcslwr_l,(__str,__locale))
#elif defined(__CRT_HAVE_DOS$_wcslwr_l) && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16lwr_l,(char16_t *__restrict __str, __locale_t __locale),_wcslwr_l,(__str,__locale))
#elif defined(__CRT_HAVE_DOS$DOS$_wcslwr_l)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16lwr_l,(char16_t *__restrict __str, __locale_t __locale),DOS$_wcslwr_l,(__str,__locale))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcslwr_l.h>
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16lwr_l)(char16_t *__restrict __str, __locale_t __locale) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr_l))((__WCHAR_TYPE__ *)__str, __locale); }
#else /* ... */
#include <local/parts.uchar.string/c16lwr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16lwr_l, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16lwr_l)(char16_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16lwr_l))(__str, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcslwr_l) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32lwr_l,(char32_t *__restrict __str, __locale_t __locale),wcslwr_l,(__str,__locale))
#elif defined(__CRT_HAVE_DOS$wcslwr_l) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32lwr_l,(char32_t *__restrict __str, __locale_t __locale),wcslwr_l,(__str,__locale))
#elif defined(__CRT_HAVE_DOS$KOS$wcslwr_l)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32lwr_l,(char32_t *__restrict __str, __locale_t __locale),KOS$wcslwr_l,(__str,__locale))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcslwr_l.h>
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32lwr_l)(char32_t *__restrict __str, __locale_t __locale) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr_l))((__WCHAR_TYPE__ *)__str, __locale); }
#else /* ... */
#include <local/parts.uchar.string/c32lwr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32lwr_l, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32lwr_l)(char32_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32lwr_l))(__str, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsupr_l) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,__LIBDCALL,c16upr_l,(char16_t *__restrict __str, __locale_t __locale),wcsupr_l,(__str,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsupr_l) && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16upr_l,(char16_t *__restrict __str, __locale_t __locale),_wcsupr_l,(__str,__locale))
#elif defined(__CRT_HAVE_DOS$DOS$_wcsupr_l)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16upr_l,(char16_t *__restrict __str, __locale_t __locale),DOS$_wcsupr_l,(__str,__locale))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wcsupr_l.h>
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16upr_l)(char16_t *__restrict __str, __locale_t __locale) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr_l))((__WCHAR_TYPE__ *)__str, __locale); }
#else /* ... */
#include <local/parts.uchar.string/c16upr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16upr_l, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16upr_l)(char16_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16upr_l))(__str, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsupr_l) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,__LIBKCALL,c32upr_l,(char32_t *__restrict __str, __locale_t __locale),wcsupr_l,(__str,__locale))
#elif defined(__CRT_HAVE_DOS$wcsupr_l) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32upr_l,(char32_t *__restrict __str, __locale_t __locale),wcsupr_l,(__str,__locale))
#elif defined(__CRT_HAVE_DOS$KOS$wcsupr_l)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32upr_l,(char32_t *__restrict __str, __locale_t __locale),KOS$wcsupr_l,(__str,__locale))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wcsupr_l.h>
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32upr_l)(char32_t *__restrict __str, __locale_t __locale) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr_l))((__WCHAR_TYPE__ *)__str, __locale); }
#else /* ... */
#include <local/parts.uchar.string/c32upr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32upr_l, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32upr_l)(char32_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32upr_l))(__str, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,,__SIZE_TYPE__,__NOTHROW_NCX,__LIBDCALL,fuzzy_c16memcasecmp_l,(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale),fuzzy_wmemcasecmp_l,(__s1,__s1_bytes,__s2,__s2_bytes,__locale))
#elif defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp_l)
__CREDIRECT_DOS(,__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16memcasecmp_l,(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale),fuzzy_wmemcasecmp_l,(__s1,__s1_bytes,__s2,__s2_bytes,__locale))
#else /* ... */
#include <parts/malloca.h>
#if !defined(__NO_MALLOCA) && (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/fuzzy_wmemcasecmp_l.h>
__FORCELOCAL __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16memcasecmp_l)(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcasecmp_l))((__WCHAR_TYPE__ const *)__s1, __s1_bytes, (__WCHAR_TYPE__ const *)__s2, __s2_bytes, __locale); }
#else /* !__NO_MALLOCA && (__SIZEOF_WCHAR_T__ == 2) */
#include <parts/malloca.h>
#ifndef __NO_MALLOCA
#include <local/parts.uchar.string/fuzzy_c16memcasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16memcasecmp_l, __FORCELOCAL __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16memcasecmp_l)(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16memcasecmp_l))(__s1, __s1_bytes, __s2, __s2_bytes, __locale); })
#endif /* !__NO_MALLOCA */
#endif /* __NO_MALLOCA || !(__SIZEOF_WCHAR_T__ == 2) */
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,,__SIZE_TYPE__,__NOTHROW_NCX,__LIBKCALL,fuzzy_c32memcasecmp_l,(char32_t const *__s1, __SIZE_TYPE__ __s1_bytes, char32_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale),fuzzy_wmemcasecmp_l,(__s1,__s1_bytes,__s2,__s2_bytes,__locale))
#elif defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp_l)
__CREDIRECT_KOS(,__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32memcasecmp_l,(char32_t const *__s1, __SIZE_TYPE__ __s1_bytes, char32_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale),fuzzy_wmemcasecmp_l,(__s1,__s1_bytes,__s2,__s2_bytes,__locale))
#else /* ... */
#include <parts/malloca.h>
#if !defined(__NO_MALLOCA) && (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/fuzzy_wmemcasecmp_l.h>
__FORCELOCAL __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32memcasecmp_l)(char32_t const *__s1, __SIZE_TYPE__ __s1_bytes, char32_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcasecmp_l))((__WCHAR_TYPE__ const *)__s1, __s1_bytes, (__WCHAR_TYPE__ const *)__s2, __s2_bytes, __locale); }
#else /* !__NO_MALLOCA && (__SIZEOF_WCHAR_T__ == 4) */
#include <parts/malloca.h>
#ifndef __NO_MALLOCA
#include <local/parts.uchar.string/fuzzy_c32memcasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32memcasecmp_l, __FORCELOCAL __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32memcasecmp_l)(char32_t const *__s1, __SIZE_TYPE__ __s1_bytes, char32_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32memcasecmp_l))(__s1, __s1_bytes, __s2, __s2_bytes, __locale); })
#endif /* !__NO_MALLOCA */
#endif /* __NO_MALLOCA || !(__SIZEOF_WCHAR_T__ == 4) */
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wcscasecmp_l) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBDCALL,fuzzy_c16casecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),fuzzy_wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$fuzzy_wcscasecmp_l) && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16casecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),fuzzy_wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$DOS$fuzzy_wcscasecmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16casecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),DOS$fuzzy_wcscasecmp_l,(__s1,__s2,__locale))
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) || (defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp_l) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp_l) && __SIZEOF_WCHAR_T__ == 2) || !defined(__NO_MALLOCA)) && (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/fuzzy_wcscasecmp_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16casecmp_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscasecmp_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp_l) || !defined(__NO_MALLOCA)
#include <local/parts.uchar.string/fuzzy_c16casecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16casecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16casecmp_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16casecmp_l))(__s1, __s2, __locale); })
#endif /* ... */
#if defined(__CRT_HAVE_fuzzy_wcscasecmp_l) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBKCALL,fuzzy_c32casecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),fuzzy_wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$fuzzy_wcscasecmp_l) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32casecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),fuzzy_wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$KOS$fuzzy_wcscasecmp_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32casecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),KOS$fuzzy_wcscasecmp_l,(__s1,__s2,__locale))
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) || (defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp_l) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp_l) && __SIZEOF_WCHAR_T__ == 2) || !defined(__NO_MALLOCA)) && (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/fuzzy_wcscasecmp_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32casecmp_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscasecmp_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp_l) || !defined(__NO_MALLOCA)
#include <local/parts.uchar.string/fuzzy_c32casecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32casecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32casecmp_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32casecmp_l))(__s1, __s2, __locale); })
#endif /* ... */
#if defined(__CRT_HAVE_fuzzy_wcsncasecmp_l) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBDCALL,fuzzy_c16ncasecmp_l,(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale),fuzzy_wcsncasecmp_l,(__s1,__s1_maxlen,__s2,__s2_maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$fuzzy_wcsncasecmp_l) && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16ncasecmp_l,(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale),fuzzy_wcsncasecmp_l,(__s1,__s1_maxlen,__s2,__s2_maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$DOS$fuzzy_wcsncasecmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16ncasecmp_l,(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale),DOS$fuzzy_wcsncasecmp_l,(__s1,__s1_maxlen,__s2,__s2_maxlen,__locale))
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) || (defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp_l) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp_l) && __SIZEOF_WCHAR_T__ == 2) || !defined(__NO_MALLOCA)) && (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/fuzzy_wcsncasecmp_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16ncasecmp_l)(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncasecmp_l))((__WCHAR_TYPE__ const *)__s1, __s1_maxlen, (__WCHAR_TYPE__ const *)__s2, __s2_maxlen, __locale); }
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp_l) || !defined(__NO_MALLOCA)
#include <local/parts.uchar.string/fuzzy_c16ncasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16ncasecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16ncasecmp_l)(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16ncasecmp_l))(__s1, __s1_maxlen, __s2, __s2_maxlen, __locale); })
#endif /* ... */
#if defined(__CRT_HAVE_fuzzy_wcsncasecmp_l) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBKCALL,fuzzy_c32ncasecmp_l,(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale),fuzzy_wcsncasecmp_l,(__s1,__s1_maxlen,__s2,__s2_maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$fuzzy_wcsncasecmp_l) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32ncasecmp_l,(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale),fuzzy_wcsncasecmp_l,(__s1,__s1_maxlen,__s2,__s2_maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$KOS$fuzzy_wcsncasecmp_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32ncasecmp_l,(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale),KOS$fuzzy_wcsncasecmp_l,(__s1,__s1_maxlen,__s2,__s2_maxlen,__locale))
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) || (defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp_l) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp_l) && __SIZEOF_WCHAR_T__ == 2) || !defined(__NO_MALLOCA)) && (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/fuzzy_wcsncasecmp_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32ncasecmp_l)(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncasecmp_l))((__WCHAR_TYPE__ const *)__s1, __s1_maxlen, (__WCHAR_TYPE__ const *)__s2, __s2_maxlen, __locale); }
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp_l) || !defined(__NO_MALLOCA)
#include <local/parts.uchar.string/fuzzy_c32ncasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32ncasecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32ncasecmp_l)(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32ncasecmp_l))(__s1, __s1_maxlen, __s2, __s2_maxlen, __locale); })
#endif /* ... */
#if defined(__CRT_HAVE_wildwcscasecmp_l) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,wildc16casecmp_l,(char16_t const *__pattern, char16_t const *__string, __locale_t __locale),wildwcscasecmp_l,(__pattern,__string,__locale))
#elif defined(__CRT_HAVE_DOS$wildwcscasecmp_l) && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildc16casecmp_l,(char16_t const *__pattern, char16_t const *__string, __locale_t __locale),wildwcscasecmp_l,(__pattern,__string,__locale))
#elif defined(__CRT_HAVE_DOS$DOS$wildwcscasecmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildc16casecmp_l,(char16_t const *__pattern, char16_t const *__string, __locale_t __locale),DOS$wildwcscasecmp_l,(__pattern,__string,__locale))
#elif (__SIZEOF_WCHAR_T__ == 2)
#include <local/wchar/wildwcscasecmp_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL wildc16casecmp_l)(char16_t const *__pattern, char16_t const *__string, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscasecmp_l))((__WCHAR_TYPE__ const *)__pattern, (__WCHAR_TYPE__ const *)__string, __locale); }
#else /* ... */
#include <local/parts.uchar.string/wildc16casecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildc16casecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL wildc16casecmp_l)(char16_t const *__pattern, char16_t const *__string, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildc16casecmp_l))(__pattern, __string, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wildwcscasecmp_l) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBKCALL,wildc32casecmp_l,(char32_t const *__pattern, char32_t const *__string, __locale_t __locale),wildwcscasecmp_l,(__pattern,__string,__locale))
#elif defined(__CRT_HAVE_DOS$wildwcscasecmp_l) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildc32casecmp_l,(char32_t const *__pattern, char32_t const *__string, __locale_t __locale),wildwcscasecmp_l,(__pattern,__string,__locale))
#elif defined(__CRT_HAVE_DOS$KOS$wildwcscasecmp_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildc32casecmp_l,(char32_t const *__pattern, char32_t const *__string, __locale_t __locale),KOS$wildwcscasecmp_l,(__pattern,__string,__locale))
#elif (__SIZEOF_WCHAR_T__ == 4)
#include <local/wchar/wildwcscasecmp_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL wildc32casecmp_l)(char32_t const *__pattern, char32_t const *__string, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscasecmp_l))((__WCHAR_TYPE__ const *)__pattern, (__WCHAR_TYPE__ const *)__string, __locale); }
#else /* ... */
#include <local/parts.uchar.string/wildc32casecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildc32casecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL wildc32casecmp_l)(char32_t const *__pattern, char32_t const *__string, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildc32casecmp_l))(__pattern, __string, __locale); })
#endif /* !... */
#endif /* __USE_XOPEN2K8 */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_PARTS_UCHAR_STRING_H */
