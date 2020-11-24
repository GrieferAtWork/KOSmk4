/* HASH CRC-32:0x44dfc370 */
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

#if defined(__CRT_HAVE_wmemcpy) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16memcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, size_t __num_chars),wmemcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmemcpy)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16memcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, size_t __num_chars),wmemcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memcpyw) && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16memcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, size_t __num_chars),memcpyw,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$memcpyw)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16memcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, size_t __num_chars),memcpyw,(__dst,__src,__num_chars))
#else /* ... */
#include <libc/local/string/memcpyw.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16memcpy)(char16_t *__restrict __dst, char16_t const *__restrict __src, size_t __num_chars) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyw))((void *)__dst, (void const *)__src, (__SIZE_TYPE__)__num_chars); }
#endif /* !... */
#if defined(__CRT_HAVE_wmemcpy) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32memcpy,(char32_t *__restrict __dst, char32_t const *__restrict __src, size_t __num_chars),wmemcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_KOS$wmemcpy)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32memcpy,(char32_t *__restrict __dst, char32_t const *__restrict __src, size_t __num_chars),wmemcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memcpyl) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32memcpy,(char32_t *__restrict __dst, char32_t const *__restrict __src, size_t __num_chars),memcpyl,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_KOS$memcpyl)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32memcpy,(char32_t *__restrict __dst, char32_t const *__restrict __src, size_t __num_chars),memcpyl,(__dst,__src,__num_chars))
#else /* ... */
#include <libc/local/string/memcpyl.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32memcpy)(char32_t *__restrict __dst, char32_t const *__restrict __src, size_t __num_chars) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyl))((void *)__dst, (void const *)__src, (__SIZE_TYPE__)__num_chars); }
#endif /* !... */
#if defined(__CRT_HAVE_wmemmove) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16memmove,(char16_t *__dst, char16_t const *__src, size_t __num_chars),wmemmove,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmemmove)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16memmove,(char16_t *__dst, char16_t const *__src, size_t __num_chars),wmemmove,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memmovew) && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16memmove,(char16_t *__dst, char16_t const *__src, size_t __num_chars),memmovew,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$memmovew)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16memmove,(char16_t *__dst, char16_t const *__src, size_t __num_chars),memmovew,(__dst,__src,__num_chars))
#else /* ... */
#include <libc/local/string/memmovew.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16memmove)(char16_t *__dst, char16_t const *__src, size_t __num_chars) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovew))((void *)__dst, (void const *)__src, (__SIZE_TYPE__)__num_chars); }
#endif /* !... */
#if defined(__CRT_HAVE_wmemmove) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32memmove,(char32_t *__dst, char32_t const *__src, size_t __num_chars),wmemmove,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_KOS$wmemmove)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32memmove,(char32_t *__dst, char32_t const *__src, size_t __num_chars),wmemmove,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memmovel) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32memmove,(char32_t *__dst, char32_t const *__src, size_t __num_chars),memmovel,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_KOS$memmovel)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32memmove,(char32_t *__dst, char32_t const *__src, size_t __num_chars),memmovel,(__dst,__src,__num_chars))
#else /* ... */
#include <libc/local/string/memmovel.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32memmove)(char32_t *__dst, char32_t const *__src, size_t __num_chars) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovel))((void *)__dst, (void const *)__src, (__SIZE_TYPE__)__num_chars); }
#endif /* !... */
#if defined(__CRT_HAVE_wmemset) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16memset,(char16_t *__dst, char16_t __filler, size_t __num_chars),wmemset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmemset)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16memset,(char16_t *__dst, char16_t __filler, size_t __num_chars),wmemset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_memsetw) && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16memset,(char16_t *__dst, char16_t __filler, size_t __num_chars),memsetw,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_DOS$memsetw)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16memset,(char16_t *__dst, char16_t __filler, size_t __num_chars),memsetw,(__dst,__filler,__num_chars))
#else /* ... */
#include <libc/local/string/memsetw.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16memset)(char16_t *__dst, char16_t __filler, size_t __num_chars) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memsetw))((void *)__dst, (__UINT16_TYPE__)__filler, (__SIZE_TYPE__)__num_chars); }
#endif /* !... */
#if defined(__CRT_HAVE_wmemset) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32memset,(char32_t *__dst, char32_t __filler, size_t __num_chars),wmemset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_KOS$wmemset)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32memset,(char32_t *__dst, char32_t __filler, size_t __num_chars),wmemset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_memsetl) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32memset,(char32_t *__dst, char32_t __filler, size_t __num_chars),memsetl,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_KOS$memsetl)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32memset,(char32_t *__dst, char32_t __filler, size_t __num_chars),memsetl,(__dst,__filler,__num_chars))
#else /* ... */
#include <libc/local/string/memsetl.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32memset)(char32_t *__dst, char32_t __filler, size_t __num_chars) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memsetl))((void *)__dst, (__UINT32_TYPE__)__filler, (__SIZE_TYPE__)__num_chars); }
#endif /* !... */
#if defined(__CRT_HAVE_wmempcpy) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16mempcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, __SIZE_TYPE__ __num_chars),wmempcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmempcpy)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16mempcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, __SIZE_TYPE__ __num_chars),wmempcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_mempcpyw) && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16mempcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, __SIZE_TYPE__ __num_chars),mempcpyw,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$mempcpyw)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16mempcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, __SIZE_TYPE__ __num_chars),mempcpyw,(__dst,__src,__num_chars))
#else /* ... */
#include <libc/local/string/mempcpyw.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16mempcpy)(char16_t *__restrict __dst, char16_t const *__restrict __src, __SIZE_TYPE__ __num_chars) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyw))((void *)__dst, (void const *)__src, __num_chars); }
#endif /* !... */
#if defined(__CRT_HAVE_wmempcpy) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32mempcpy,(char32_t *__restrict __dst, char32_t const *__restrict __src, __SIZE_TYPE__ __num_chars),wmempcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_KOS$wmempcpy)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32mempcpy,(char32_t *__restrict __dst, char32_t const *__restrict __src, __SIZE_TYPE__ __num_chars),wmempcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_mempcpyl) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32mempcpy,(char32_t *__restrict __dst, char32_t const *__restrict __src, __SIZE_TYPE__ __num_chars),mempcpyl,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_KOS$mempcpyl)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32mempcpy,(char32_t *__restrict __dst, char32_t const *__restrict __src, __SIZE_TYPE__ __num_chars),mempcpyl,(__dst,__src,__num_chars))
#else /* ... */
#include <libc/local/string/mempcpyl.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32mempcpy)(char32_t *__restrict __dst, char32_t const *__restrict __src, __SIZE_TYPE__ __num_chars) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyl))((void *)__dst, (void const *)__src, __num_chars); }
#endif /* !... */
#if defined(__CRT_HAVE_wmempmove) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16mempmove,(char16_t *__dst, char16_t const *__src, __SIZE_TYPE__ __num_chars),wmempmove,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmempmove)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16mempmove,(char16_t *__dst, char16_t const *__src, __SIZE_TYPE__ __num_chars),wmempmove,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_mempmovew) && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16mempmove,(char16_t *__dst, char16_t const *__src, __SIZE_TYPE__ __num_chars),mempmovew,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$mempmovew)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16mempmove,(char16_t *__dst, char16_t const *__src, __SIZE_TYPE__ __num_chars),mempmovew,(__dst,__src,__num_chars))
#else /* ... */
#include <libc/local/string/mempmovew.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16mempmove)(char16_t *__dst, char16_t const *__src, __SIZE_TYPE__ __num_chars) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovew))((void *)__dst, (void const *)__src, __num_chars); }
#endif /* !... */
#if defined(__CRT_HAVE_wmempmove) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32mempmove,(char32_t *__dst, char32_t const *__src, __SIZE_TYPE__ __num_chars),wmempmove,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_KOS$wmempmove)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32mempmove,(char32_t *__dst, char32_t const *__src, __SIZE_TYPE__ __num_chars),wmempmove,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_mempmovel) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32mempmove,(char32_t *__dst, char32_t const *__src, __SIZE_TYPE__ __num_chars),mempmovel,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_KOS$mempmovel)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32mempmove,(char32_t *__dst, char32_t const *__src, __SIZE_TYPE__ __num_chars),mempmovel,(__dst,__src,__num_chars))
#else /* ... */
#include <libc/local/string/mempmovel.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32mempmove)(char32_t *__dst, char32_t const *__src, __SIZE_TYPE__ __num_chars) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovel))((void *)__dst, (void const *)__src, __num_chars); }
#endif /* !... */
#if defined(__CRT_HAVE_wmempset) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as wmemset, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16mempset,(char16_t *__dst, char16_t __filler, __SIZE_TYPE__ __num_chars),wmempset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmempset)
/* Same as wmemset, but return a pointer after the last written character */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16mempset,(char16_t *__dst, char16_t __filler, __SIZE_TYPE__ __num_chars),wmempset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_mempsetw) && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as wmemset, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16mempset,(char16_t *__dst, char16_t __filler, __SIZE_TYPE__ __num_chars),mempsetw,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_DOS$mempsetw)
/* Same as wmemset, but return a pointer after the last written character */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16mempset,(char16_t *__dst, char16_t __filler, __SIZE_TYPE__ __num_chars),mempsetw,(__dst,__filler,__num_chars))
#else /* ... */
#include <libc/local/string/mempsetw.h>
/* Same as wmemset, but return a pointer after the last written character */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16mempset)(char16_t *__dst, char16_t __filler, __SIZE_TYPE__ __num_chars) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempsetw))((void *)__dst, (__UINT16_TYPE__)__filler, __num_chars); }
#endif /* !... */
#if defined(__CRT_HAVE_wmempset) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as wmemset, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32mempset,(char32_t *__dst, char32_t __filler, __SIZE_TYPE__ __num_chars),wmempset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_KOS$wmempset)
/* Same as wmemset, but return a pointer after the last written character */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32mempset,(char32_t *__dst, char32_t __filler, __SIZE_TYPE__ __num_chars),wmempset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_mempsetl) && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as wmemset, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32mempset,(char32_t *__dst, char32_t __filler, __SIZE_TYPE__ __num_chars),mempsetl,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_KOS$mempsetl)
/* Same as wmemset, but return a pointer after the last written character */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32mempset,(char32_t *__dst, char32_t __filler, __SIZE_TYPE__ __num_chars),mempsetl,(__dst,__filler,__num_chars))
#else /* ... */
#include <libc/local/string/mempsetl.h>
/* Same as wmemset, but return a pointer after the last written character */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32mempset)(char32_t *__dst, char32_t __filler, __SIZE_TYPE__ __num_chars) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempsetl))((void *)__dst, (__UINT32_TYPE__)__filler, __num_chars); }
#endif /* !... */
#if defined(__CRT_HAVE_wcsend) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcslen(STR)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16send,(char16_t *__restrict __string),wcsend,(__string))
/* Same as `STR+wcslen(STR)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16send,(char16_t const *__restrict __string),wcsend,(__string))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcslen(STR)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16send,(char16_t const *__restrict __string),wcsend,(__string))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsend)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcslen(STR)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16send,(char16_t *__restrict __string),wcsend,(__string))
/* Same as `STR+wcslen(STR)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16send,(char16_t const *__restrict __string),wcsend,(__string))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcslen(STR)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16send,(char16_t const *__restrict __string),wcsend,(__string))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcslen(STR)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16send)(char16_t *__restrict __string) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))((__WCHAR_TYPE__ const *)__string); }
/* Same as `STR+wcslen(STR)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16send)(char16_t const *__restrict __string) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))((__WCHAR_TYPE__ const *)__string); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcslen(STR)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16send)(char16_t const *__restrict __string) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))((__WCHAR_TYPE__ const *)__string); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c16send.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcslen(STR)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16send)(char16_t *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16send))(__string); }
/* Same as `STR+wcslen(STR)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16send)(char16_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16send))(__string); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcslen(STR)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16send, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16send)(char16_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16send))(__string); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsend) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcslen(STR)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32send,(char32_t *__restrict __string),wcsend,(__string))
/* Same as `STR+wcslen(STR)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32send,(char32_t const *__restrict __string),wcsend,(__string))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcslen(STR)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32send,(char32_t const *__restrict __string),wcsend,(__string))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_KOS$wcsend)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcslen(STR)' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32send,(char32_t *__restrict __string),wcsend,(__string))
/* Same as `STR+wcslen(STR)' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32send,(char32_t const *__restrict __string),wcsend,(__string))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcslen(STR)' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32send,(char32_t const *__restrict __string),wcsend,(__string))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcslen(STR)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32send)(char32_t *__restrict __string) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))((__WCHAR_TYPE__ const *)__string); }
/* Same as `STR+wcslen(STR)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32send)(char32_t const *__restrict __string) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))((__WCHAR_TYPE__ const *)__string); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcslen(STR)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32send)(char32_t const *__restrict __string) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))((__WCHAR_TYPE__ const *)__string); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c32send.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcslen(STR)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32send)(char32_t *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32send))(__string); }
/* Same as `STR+wcslen(STR)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32send)(char32_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32send))(__string); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcslen(STR)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32send, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32send)(char32_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32send))(__string); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsnend) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16snend,(char16_t *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16snend,(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16snend,(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsnend)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16snend,(char16_t *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16snend,(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16snend,(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsnend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16snend)(char16_t *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))((__WCHAR_TYPE__ const *)__string, __maxlen); }
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16snend)(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))((__WCHAR_TYPE__ const *)__string, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16snend)(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))((__WCHAR_TYPE__ const *)__string, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c16snend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16snend)(char16_t *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16snend))(__string, __maxlen); }
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16snend)(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16snend))(__string, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16snend, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16snend)(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16snend))(__string, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsnend) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32snend,(char32_t *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32snend,(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32snend,(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_KOS$wcsnend)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32snend,(char32_t *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32snend,(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32snend,(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsnend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32snend)(char32_t *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))((__WCHAR_TYPE__ const *)__string, __maxlen); }
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32snend)(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))((__WCHAR_TYPE__ const *)__string, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32snend)(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))((__WCHAR_TYPE__ const *)__string, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c32snend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32snend)(char32_t *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32snend))(__string, __maxlen); }
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32snend)(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32snend))(__string, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32snend, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32snend)(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32snend))(__string, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcslen) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,c16slen,(char16_t const *__restrict __string),wcslen,(__string))
#elif defined(__CRT_HAVE_DOS$wcslen)
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,c16slen,(char16_t const *__restrict __string),wcslen,(__string))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcslen.h>
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBDCALL c16slen)(char16_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslen))((__WCHAR_TYPE__ const *)__string); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16slen.h>
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16slen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBDCALL c16slen)(char16_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16slen))(__string); })
#endif /* !... */
#if defined(__CRT_HAVE_wcslen) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,c32slen,(char32_t const *__restrict __string),wcslen,(__string))
#elif defined(__CRT_HAVE_KOS$wcslen)
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,c32slen,(char32_t const *__restrict __string),wcslen,(__string))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcslen.h>
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBKCALL c32slen)(char32_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslen))((__WCHAR_TYPE__ const *)__string); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32slen.h>
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32slen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBKCALL c32slen)(char32_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32slen))(__string); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnlen) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16snlen,(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnlen)
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16snlen,(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsnlen.h>
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16snlen)(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlen))((__WCHAR_TYPE__ const *)__string, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16snlen.h>
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16snlen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16snlen)(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16snlen))(__string, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnlen) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c32snlen,(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsnlen)
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c32snlen,(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsnlen.h>
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32snlen)(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlen))((__WCHAR_TYPE__ const *)__string, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32snlen.h>
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32snlen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32snlen)(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32snlen))(__string, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scmp,(char16_t const *__s1, char16_t const *__s2),wcscmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscmp)
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scmp,(char16_t const *__s1, char16_t const *__s2),wcscmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcscmp.h>
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16scmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16scmp.h>
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16scmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16scmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16scmp))(__s1, __s2); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scmp,(char32_t const *__s1, char32_t const *__s2),wcscmp,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$wcscmp)
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scmp,(char32_t const *__s1, char32_t const *__s2),wcscmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcscmp.h>
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32scmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32scmp.h>
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32scmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32scmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32scmp))(__s1, __s2); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `MAXLEN' characters from either string */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncmp,(char16_t const *__s1, char16_t const *__s2, size_t __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsncmp)
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `MAXLEN' characters from either string */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncmp,(char16_t const *__s1, char16_t const *__s2, size_t __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsncmp.h>
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `MAXLEN' characters from either string */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16sncmp)(char16_t const *__s1, char16_t const *__s2, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16sncmp.h>
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `MAXLEN' characters from either string */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sncmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16sncmp)(char16_t const *__s1, char16_t const *__s2, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sncmp))(__s1, __s2, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `MAXLEN' characters from either string */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncmp,(char32_t const *__s1, char32_t const *__s2, size_t __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsncmp)
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `MAXLEN' characters from either string */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncmp,(char32_t const *__s1, char32_t const *__s2, size_t __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsncmp.h>
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `MAXLEN' characters from either string */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32sncmp)(char32_t const *__s1, char32_t const *__s2, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32sncmp.h>
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `MAXLEN' characters from either string */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sncmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32sncmp)(char32_t const *__s1, char32_t const *__s2, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sncmp))(__s1, __s2, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcschr) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strchr(3)
 * Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16schr,(char16_t *__restrict __haystack, char16_t __needle),wcschr,(__haystack,__needle))
/* >> strchr(3)
 * Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16schr,(char16_t const *__restrict __haystack, char16_t __needle),wcschr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strchr(3)
 * Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16schr,(char16_t const *__restrict __haystack, char16_t __needle),wcschr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcschr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strchr(3)
 * Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16schr,(char16_t *__restrict __haystack, char16_t __needle),wcschr,(__haystack,__needle))
/* >> strchr(3)
 * Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16schr,(char16_t const *__restrict __haystack, char16_t __needle),wcschr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strchr(3)
 * Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16schr,(char16_t const *__restrict __haystack, char16_t __needle),wcschr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcschr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strchr(3)
 * Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16schr)(char16_t *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* >> strchr(3)
 * Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16schr)(char16_t const *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strchr(3)
 * Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16schr)(char16_t const *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c16schr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strchr(3)
 * Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16schr)(char16_t *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16schr))(__haystack, __needle); }
/* >> strchr(3)
 * Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16schr)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16schr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strchr(3)
 * Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16schr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16schr)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16schr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcschr) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strchr(3)
 * Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32schr,(char32_t *__restrict __haystack, char32_t __needle),wcschr,(__haystack,__needle))
/* >> strchr(3)
 * Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32schr,(char32_t const *__restrict __haystack, char32_t __needle),wcschr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strchr(3)
 * Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32schr,(char32_t const *__restrict __haystack, char32_t __needle),wcschr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_KOS$wcschr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strchr(3)
 * Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32schr,(char32_t *__restrict __haystack, char32_t __needle),wcschr,(__haystack,__needle))
/* >> strchr(3)
 * Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32schr,(char32_t const *__restrict __haystack, char32_t __needle),wcschr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strchr(3)
 * Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32schr,(char32_t const *__restrict __haystack, char32_t __needle),wcschr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcschr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strchr(3)
 * Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32schr)(char32_t *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* >> strchr(3)
 * Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32schr)(char32_t const *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strchr(3)
 * Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32schr)(char32_t const *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c32schr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strchr(3)
 * Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32schr)(char32_t *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32schr))(__haystack, __needle); }
/* >> strchr(3)
 * Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32schr)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32schr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strchr(3)
 * Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32schr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32schr)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32schr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsrchr) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strrchr(3)
 * Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16srchr,(char16_t *__restrict __haystack, char16_t __needle),wcsrchr,(__haystack,__needle))
/* >> strrchr(3)
 * Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16srchr,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strrchr(3)
 * Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16srchr,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsrchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strrchr(3)
 * Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16srchr,(char16_t *__restrict __haystack, char16_t __needle),wcsrchr,(__haystack,__needle))
/* >> strrchr(3)
 * Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16srchr,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strrchr(3)
 * Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16srchr,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strrchr(3)
 * Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16srchr)(char16_t *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* >> strrchr(3)
 * Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16srchr)(char16_t const *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strrchr(3)
 * Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16srchr)(char16_t const *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c16srchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strrchr(3)
 * Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16srchr)(char16_t *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16srchr))(__haystack, __needle); }
/* >> strrchr(3)
 * Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16srchr)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16srchr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strrchr(3)
 * Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16srchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16srchr)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16srchr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsrchr) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strrchr(3)
 * Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32srchr,(char32_t *__restrict __haystack, char32_t __needle),wcsrchr,(__haystack,__needle))
/* >> strrchr(3)
 * Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32srchr,(char32_t const *__restrict __haystack, char32_t __needle),wcsrchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strrchr(3)
 * Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32srchr,(char32_t const *__restrict __haystack, char32_t __needle),wcsrchr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_KOS$wcsrchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strrchr(3)
 * Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32srchr,(char32_t *__restrict __haystack, char32_t __needle),wcsrchr,(__haystack,__needle))
/* >> strrchr(3)
 * Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32srchr,(char32_t const *__restrict __haystack, char32_t __needle),wcsrchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strrchr(3)
 * Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32srchr,(char32_t const *__restrict __haystack, char32_t __needle),wcsrchr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strrchr(3)
 * Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32srchr)(char32_t *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* >> strrchr(3)
 * Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32srchr)(char32_t const *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strrchr(3)
 * Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32srchr)(char32_t const *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c32srchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strrchr(3)
 * Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32srchr)(char32_t *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32srchr))(__haystack, __needle); }
/* >> strrchr(3)
 * Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32srchr)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32srchr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strrchr(3)
 * Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32srchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32srchr)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32srchr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsnchr) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16snchr,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16snchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16snchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsnchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16snchr,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16snchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16snchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsnchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16snchr)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16snchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16snchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c16snchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16snchr)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16snchr))(__haystack, __needle, __maxlen); }
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16snchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16snchr))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16snchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16snchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16snchr))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsnchr) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32snchr,(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32snchr,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32snchr,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_KOS$wcsnchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32snchr,(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32snchr,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32snchr,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsnchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32snchr)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32snchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32snchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c32snchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32snchr)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32snchr))(__haystack, __needle, __maxlen); }
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32snchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32snchr))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32snchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32snchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32snchr))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsnrchr) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16snrchr,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16snrchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16snrchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsnrchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16snrchr,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16snrchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16snrchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsnrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16snrchr)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16snrchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16snrchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c16snrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16snrchr)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16snrchr))(__haystack, __needle, __maxlen); }
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16snrchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16snrchr))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16snrchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16snrchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16snrchr))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsnrchr) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32snrchr,(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32snrchr,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32snrchr,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_KOS$wcsnrchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32snrchr,(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32snrchr,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32snrchr,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsnrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32snrchr)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32snrchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32snrchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c32snrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32snrchr)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32snrchr))(__haystack, __needle, __maxlen); }
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32snrchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32snrchr))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32snrchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32snrchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32snrchr))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcschrnul) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16schrnul,(char16_t *__restrict __haystack, char16_t __needle),wcschrnul,(__haystack,__needle))
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16schrnul,(char16_t const *__restrict __haystack, char16_t __needle),wcschrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16schrnul,(char16_t const *__haystack, char16_t __needle),wcschrnul,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcschrnul)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16schrnul,(char16_t *__restrict __haystack, char16_t __needle),wcschrnul,(__haystack,__needle))
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16schrnul,(char16_t const *__restrict __haystack, char16_t __needle),wcschrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16schrnul,(char16_t const *__haystack, char16_t __needle),wcschrnul,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcschrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16schrnul)(char16_t *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16schrnul)(char16_t const *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16schrnul)(char16_t const *__haystack, char16_t __needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c16schrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16schrnul)(char16_t *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16schrnul))(__haystack, __needle); }
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16schrnul)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16schrnul))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16schrnul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16schrnul)(char16_t const *__haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16schrnul))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcschrnul) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32schrnul,(char32_t *__restrict __haystack, char32_t __needle),wcschrnul,(__haystack,__needle))
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32schrnul,(char32_t const *__restrict __haystack, char32_t __needle),wcschrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32schrnul,(char32_t const *__haystack, char32_t __needle),wcschrnul,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_KOS$wcschrnul)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32schrnul,(char32_t *__restrict __haystack, char32_t __needle),wcschrnul,(__haystack,__needle))
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32schrnul,(char32_t const *__restrict __haystack, char32_t __needle),wcschrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32schrnul,(char32_t const *__haystack, char32_t __needle),wcschrnul,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcschrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32schrnul)(char32_t *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32schrnul)(char32_t const *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32schrnul)(char32_t const *__haystack, char32_t __needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c32schrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32schrnul)(char32_t *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32schrnul))(__haystack, __needle); }
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32schrnul)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32schrnul))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32schrnul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32schrnul)(char32_t const *__haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32schrnul))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsrchrnul) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16srchrnul,(char16_t *__restrict __haystack, char16_t __needle),wcsrchrnul,(__haystack,__needle))
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16srchrnul,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16srchrnul,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchrnul,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsrchrnul)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16srchrnul,(char16_t *__restrict __haystack, char16_t __needle),wcsrchrnul,(__haystack,__needle))
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16srchrnul,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16srchrnul,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchrnul,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsrchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16srchrnul)(char16_t *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16srchrnul)(char16_t const *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16srchrnul)(char16_t const *__restrict __haystack, char16_t __needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c16srchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16srchrnul)(char16_t *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16srchrnul))(__haystack, __needle); }
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16srchrnul)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16srchrnul))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16srchrnul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16srchrnul)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16srchrnul))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsrchrnul) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32srchrnul,(char32_t *__restrict __haystack, char32_t __needle),wcsrchrnul,(__haystack,__needle))
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32srchrnul,(char32_t const *__restrict __haystack, char32_t __needle),wcsrchrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32srchrnul,(char32_t const *__restrict __haystack, char32_t __needle),wcsrchrnul,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_KOS$wcsrchrnul)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32srchrnul,(char32_t *__restrict __haystack, char32_t __needle),wcsrchrnul,(__haystack,__needle))
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32srchrnul,(char32_t const *__restrict __haystack, char32_t __needle),wcsrchrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32srchrnul,(char32_t const *__restrict __haystack, char32_t __needle),wcsrchrnul,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsrchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32srchrnul)(char32_t *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32srchrnul)(char32_t const *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32srchrnul)(char32_t const *__restrict __haystack, char32_t __needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c32srchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32srchrnul)(char32_t *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32srchrnul))(__haystack, __needle); }
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32srchrnul)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32srchrnul))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32srchrnul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32srchrnul)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32srchrnul))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsnchrnul) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16snchrnul,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16snchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16snchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsnchrnul)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16snchrnul,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16snchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16snchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsnchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16snchrnul)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16snchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16snchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c16snchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16snchrnul)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16snchrnul))(__haystack, __needle, __maxlen); }
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16snchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16snchrnul))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16snchrnul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16snchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16snchrnul))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsnchrnul) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32snchrnul,(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32snchrnul,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32snchrnul,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_KOS$wcsnchrnul)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32snchrnul,(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32snchrnul,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32snchrnul,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsnchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32snchrnul)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32snchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32snchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c32snchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32snchrnul)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32snchrnul))(__haystack, __needle, __maxlen); }
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32snchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32snchrnul))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32snchrnul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32snchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32snchrnul))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsnrchrnul) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16snrchrnul,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16snrchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16snrchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsnrchrnul)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16snrchrnul,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16snrchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16snrchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsnrchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16snrchrnul)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16snrchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16snrchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c16snrchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16snrchrnul)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16snrchrnul))(__haystack, __needle, __maxlen); }
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16snrchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16snrchrnul))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16snrchrnul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16snrchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16snrchrnul))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsnrchrnul) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32snrchrnul,(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32snrchrnul,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32snrchrnul,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_KOS$wcsnrchrnul)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32snrchrnul,(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32snrchrnul,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32snrchrnul,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsnrchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32snrchrnul)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32snrchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32snrchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c32snrchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32snrchrnul)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32snrchrnul))(__haystack, __needle, __maxlen); }
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32snrchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32snrchrnul))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32snrchrnul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32snrchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32snrchrnul))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsoff) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as `wcschrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16soff,(char16_t const *__restrict __haystack, char16_t __needle),wcsoff,(__haystack,__needle))
#elif defined(__CRT_HAVE_DOS$wcsoff)
/* Same as `wcschrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16soff,(char16_t const *__restrict __haystack, char16_t __needle),wcsoff,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsoff.h>
/* Same as `wcschrnul', but return the offset from `STR', rather than the actual address */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16soff)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsoff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16soff.h>
/* Same as `wcschrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16soff, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16soff)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16soff))(__haystack, __needle); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsoff) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as `wcschrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c32soff,(char32_t const *__restrict __haystack, char32_t __needle),wcsoff,(__haystack,__needle))
#elif defined(__CRT_HAVE_KOS$wcsoff)
/* Same as `wcschrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c32soff,(char32_t const *__restrict __haystack, char32_t __needle),wcsoff,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsoff.h>
/* Same as `wcschrnul', but return the offset from `STR', rather than the actual address */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32soff)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsoff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32soff.h>
/* Same as `wcschrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32soff, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32soff)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32soff))(__haystack, __needle); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsroff) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16sroff,(char16_t const *__restrict __haystack, char16_t __needle),wcsroff,(__haystack,__needle))
#elif defined(__CRT_HAVE_DOS$wcsroff)
/* Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16sroff,(char16_t const *__restrict __haystack, char16_t __needle),wcsroff,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsroff.h>
/* Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16sroff)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsroff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16sroff.h>
/* Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sroff, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16sroff)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sroff))(__haystack, __needle); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsroff) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c32sroff,(char32_t const *__restrict __haystack, char32_t __needle),wcsroff,(__haystack,__needle))
#elif defined(__CRT_HAVE_KOS$wcsroff)
/* Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c32sroff,(char32_t const *__restrict __haystack, char32_t __needle),wcsroff,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsroff.h>
/* Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32sroff)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsroff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32sroff.h>
/* Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sroff, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32sroff)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sroff))(__haystack, __needle); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnoff) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as `wcsnchrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16snoff,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnoff,(__haystack,__needle,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnoff)
/* Same as `wcsnchrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16snoff,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnoff,(__haystack,__needle,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsnoff.h>
/* Same as `wcsnchrnul', but return the offset from `STR', rather than the actual address */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16snoff)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnoff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16snoff.h>
/* Same as `wcsnchrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16snoff, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16snoff)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16snoff))(__haystack, __needle, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnoff) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as `wcsnchrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c32snoff,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnoff,(__haystack,__needle,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsnoff)
/* Same as `wcsnchrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c32snoff,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnoff,(__haystack,__needle,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsnoff.h>
/* Same as `wcsnchrnul', but return the offset from `STR', rather than the actual address */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32snoff)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnoff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32snoff.h>
/* Same as `wcsnchrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32snoff, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32snoff)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32snoff))(__haystack, __needle, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnroff) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as `wcsnrchrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16snroff,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnroff,(__haystack,__needle,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnroff)
/* Same as `wcsnrchrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16snroff,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnroff,(__haystack,__needle,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsnroff.h>
/* Same as `wcsnrchrnul', but return the offset from `STR', rather than the actual address */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16snroff)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnroff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16snroff.h>
/* Same as `wcsnrchrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16snroff, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16snroff)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16snroff))(__haystack, __needle, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnroff) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as `wcsnrchrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c32snroff,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnroff,(__haystack,__needle,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsnroff)
/* Same as `wcsnrchrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c32snroff,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnroff,(__haystack,__needle,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsnroff.h>
/* Same as `wcsnrchrnul', but return the offset from `STR', rather than the actual address */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32snroff)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnroff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32snroff.h>
/* Same as `wcsnrchrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32snroff, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32snroff)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32snroff))(__haystack, __needle, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsstr) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16sstr,(char16_t *__haystack, char16_t *__needle),wcsstr,(__haystack,__needle))
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16sstr,(char16_t const *__haystack, char16_t const *__needle),wcsstr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16sstr,(char16_t const *__haystack, char16_t const *__needle),wcsstr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcsstr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16sstr,(char16_t *__haystack, char16_t *__needle),wcsstr,(__haystack,__needle))
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16sstr,(char16_t const *__haystack, char16_t const *__needle),wcsstr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16sstr,(char16_t const *__haystack, char16_t const *__needle),wcsstr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_wcswcs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16sstr,(char16_t *__haystack, char16_t *__needle),wcswcs,(__haystack,__needle))
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16sstr,(char16_t const *__haystack, char16_t const *__needle),wcswcs,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16sstr,(char16_t const *__haystack, char16_t const *__needle),wcswcs,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcswcs)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16sstr,(char16_t *__haystack, char16_t *__needle),wcswcs,(__haystack,__needle))
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16sstr,(char16_t const *__haystack, char16_t const *__needle),wcswcs,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16sstr,(char16_t const *__haystack, char16_t const *__needle),wcswcs,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsstr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16sstr)(char16_t *__haystack, char16_t *__needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16sstr)(char16_t const *__haystack, char16_t const *__needle) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16sstr)(char16_t const *__haystack, char16_t const *__needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c16sstr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16sstr)(char16_t *__haystack, char16_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sstr))(__haystack, __needle); }
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16sstr)(char16_t const *__haystack, char16_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sstr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sstr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16sstr)(char16_t const *__haystack, char16_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sstr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcsstr) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32sstr,(char32_t *__haystack, char32_t *__needle),wcsstr,(__haystack,__needle))
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,c32sstr,(char32_t const *__haystack, char32_t const *__needle),wcsstr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32sstr,(char32_t const *__haystack, char32_t const *__needle),wcsstr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_KOS$wcsstr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32sstr,(char32_t *__haystack, char32_t *__needle),wcsstr,(__haystack,__needle))
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,c32sstr,(char32_t const *__haystack, char32_t const *__needle),wcsstr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32sstr,(char32_t const *__haystack, char32_t const *__needle),wcsstr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_wcswcs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32sstr,(char32_t *__haystack, char32_t *__needle),wcswcs,(__haystack,__needle))
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,c32sstr,(char32_t const *__haystack, char32_t const *__needle),wcswcs,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32sstr,(char32_t const *__haystack, char32_t const *__needle),wcswcs,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_KOS$wcswcs)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32sstr,(char32_t *__haystack, char32_t *__needle),wcswcs,(__haystack,__needle))
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,c32sstr,(char32_t const *__haystack, char32_t const *__needle),wcswcs,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32sstr,(char32_t const *__haystack, char32_t const *__needle),wcswcs,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsstr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32sstr)(char32_t *__haystack, char32_t *__needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32sstr)(char32_t const *__haystack, char32_t const *__needle) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32sstr)(char32_t const *__haystack, char32_t const *__needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c32sstr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32sstr)(char32_t *__haystack, char32_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sstr))(__haystack, __needle); }
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32sstr)(char32_t const *__haystack, char32_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sstr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strstr(3)
 * Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sstr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32sstr)(char32_t const *__haystack, char32_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sstr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcscasestr) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `strstr', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16scasestr,(char16_t *__haystack, char16_t *__needle),wcscasestr,(__haystack,__needle))
/* Same as `strstr', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16scasestr,(char16_t const *__haystack, char16_t const *__needle),wcscasestr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `strstr', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16scasestr,(char16_t const *__haystack, char16_t const *__needle),wcscasestr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcscasestr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `strstr', but ignore casing */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16scasestr,(char16_t *__haystack, char16_t *__needle),wcscasestr,(__haystack,__needle))
/* Same as `strstr', but ignore casing */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16scasestr,(char16_t const *__haystack, char16_t const *__needle),wcscasestr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `strstr', but ignore casing */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16scasestr,(char16_t const *__haystack, char16_t const *__needle),wcscasestr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcscasestr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16scasestr)(char16_t *__haystack, char16_t *__needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
/* Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16scasestr)(char16_t const *__haystack, char16_t const *__needle) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16scasestr)(char16_t const *__haystack, char16_t const *__needle) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c16scasestr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16scasestr)(char16_t *__haystack, char16_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16scasestr))(__haystack, __needle); }
/* Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16scasestr)(char16_t const *__haystack, char16_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16scasestr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `strstr', but ignore casing */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16scasestr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16scasestr)(char16_t const *__haystack, char16_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16scasestr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcscasestr) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `strstr', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32scasestr,(char32_t *__haystack, char32_t *__needle),wcscasestr,(__haystack,__needle))
/* Same as `strstr', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,c32scasestr,(char32_t const *__haystack, char32_t const *__needle),wcscasestr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `strstr', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32scasestr,(char32_t const *__haystack, char32_t const *__needle),wcscasestr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_KOS$wcscasestr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `strstr', but ignore casing */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32scasestr,(char32_t *__haystack, char32_t *__needle),wcscasestr,(__haystack,__needle))
/* Same as `strstr', but ignore casing */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,c32scasestr,(char32_t const *__haystack, char32_t const *__needle),wcscasestr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `strstr', but ignore casing */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32scasestr,(char32_t const *__haystack, char32_t const *__needle),wcscasestr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcscasestr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32scasestr)(char32_t *__haystack, char32_t *__needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
/* Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32scasestr)(char32_t const *__haystack, char32_t const *__needle) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32scasestr)(char32_t const *__haystack, char32_t const *__needle) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c32scasestr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32scasestr)(char32_t *__haystack, char32_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32scasestr))(__haystack, __needle); }
/* Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32scasestr)(char32_t const *__haystack, char32_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32scasestr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `strstr', but ignore casing */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32scasestr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32scasestr)(char32_t const *__haystack, char32_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32scasestr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcscpy) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16scpy,(char16_t *__restrict __buf, char16_t const *__restrict __src),wcscpy,(__buf,__src))
#elif defined(__CRT_HAVE_DOS$wcscpy)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16scpy,(char16_t *__restrict __buf, char16_t const *__restrict __src),wcscpy,(__buf,__src))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcscpy.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16scpy)(char16_t *__restrict __buf, char16_t const *__restrict __src) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16scpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16scpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16scpy)(char16_t *__restrict __buf, char16_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16scpy))(__buf, __src); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscpy) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32scpy,(char32_t *__restrict __buf, char32_t const *__restrict __src),wcscpy,(__buf,__src))
#elif defined(__CRT_HAVE_KOS$wcscpy)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32scpy,(char32_t *__restrict __buf, char32_t const *__restrict __src),wcscpy,(__buf,__src))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcscpy.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32scpy)(char32_t *__restrict __buf, char32_t const *__restrict __src) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32scpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32scpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32scpy)(char32_t *__restrict __buf, char32_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32scpy))(__buf, __src); })
#endif /* !... */
#if defined(__CRT_HAVE_wcspcpy) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as wcscpy, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16spcpy,(char16_t *__restrict __buf, char16_t const *__restrict __src),wcspcpy,(__buf,__src))
#elif defined(__CRT_HAVE_DOS$wcspcpy)
/* Same as wcscpy, but return a pointer after the last written character */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16spcpy,(char16_t *__restrict __buf, char16_t const *__restrict __src),wcspcpy,(__buf,__src))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcspcpy.h>
/* Same as wcscpy, but return a pointer after the last written character */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16spcpy)(char16_t *__restrict __buf, char16_t const *__restrict __src) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspcpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16spcpy.h>
/* Same as wcscpy, but return a pointer after the last written character */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16spcpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16spcpy)(char16_t *__restrict __buf, char16_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16spcpy))(__buf, __src); })
#endif /* !... */
#if defined(__CRT_HAVE_wcspcpy) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as wcscpy, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32spcpy,(char32_t *__restrict __buf, char32_t const *__restrict __src),wcspcpy,(__buf,__src))
#elif defined(__CRT_HAVE_KOS$wcspcpy)
/* Same as wcscpy, but return a pointer after the last written character */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32spcpy,(char32_t *__restrict __buf, char32_t const *__restrict __src),wcspcpy,(__buf,__src))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcspcpy.h>
/* Same as wcscpy, but return a pointer after the last written character */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32spcpy)(char32_t *__restrict __buf, char32_t const *__restrict __src) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspcpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32spcpy.h>
/* Same as wcscpy, but return a pointer after the last written character */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32spcpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32spcpy)(char32_t *__restrict __buf, char32_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32spcpy))(__buf, __src); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncpy) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16sncpy,(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcsncpy,(__buf,__src,__buflen))
#elif defined(__CRT_HAVE_DOS$wcsncpy)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16sncpy,(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcsncpy,(__buf,__src,__buflen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsncpy.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16sncpy)(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src, __buflen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16sncpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sncpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16sncpy)(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sncpy))(__buf, __src, __buflen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncpy) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32sncpy,(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcsncpy,(__buf,__src,__buflen))
#elif defined(__CRT_HAVE_KOS$wcsncpy)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32sncpy,(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcsncpy,(__buf,__src,__buflen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsncpy.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32sncpy)(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src, __buflen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32sncpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sncpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32sncpy)(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sncpy))(__buf, __src, __buflen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcspncpy) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as wcsncpy, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16spncpy,(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcspncpy,(__buf,__src,__buflen))
#elif defined(__CRT_HAVE_DOS$wcspncpy)
/* Same as wcsncpy, but return a pointer after the last written character */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16spncpy,(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcspncpy,(__buf,__src,__buflen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcspncpy.h>
/* Same as wcsncpy, but return a pointer after the last written character */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16spncpy)(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspncpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src, __buflen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16spncpy.h>
/* Same as wcsncpy, but return a pointer after the last written character */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16spncpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16spncpy)(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16spncpy))(__buf, __src, __buflen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcspncpy) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as wcsncpy, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32spncpy,(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcspncpy,(__buf,__src,__buflen))
#elif defined(__CRT_HAVE_KOS$wcspncpy)
/* Same as wcsncpy, but return a pointer after the last written character */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32spncpy,(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcspncpy,(__buf,__src,__buflen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcspncpy.h>
/* Same as wcsncpy, but return a pointer after the last written character */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32spncpy)(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspncpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src, __buflen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32spncpy.h>
/* Same as wcsncpy, but return a pointer after the last written character */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32spncpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32spncpy)(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32spncpy))(__buf, __src, __buflen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16scat,(char16_t *__restrict __buf, char16_t const *__restrict __src),wcscat,(__buf,__src))
#elif defined(__CRT_HAVE_DOS$wcscat)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16scat,(char16_t *__restrict __buf, char16_t const *__restrict __src),wcscat,(__buf,__src))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcscat.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16scat)(char16_t *__restrict __buf, char16_t const *__restrict __src) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscat))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16scat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16scat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16scat)(char16_t *__restrict __buf, char16_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16scat))(__buf, __src); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32scat,(char32_t *__restrict __buf, char32_t const *__restrict __src),wcscat,(__buf,__src))
#elif defined(__CRT_HAVE_KOS$wcscat)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32scat,(char32_t *__restrict __buf, char32_t const *__restrict __src),wcscat,(__buf,__src))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcscat.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32scat)(char32_t *__restrict __buf, char32_t const *__restrict __src) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscat))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32scat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32scat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32scat)(char32_t *__restrict __buf, char32_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32scat))(__buf, __src); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16sncat,(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcsncat,(__buf,__src,__buflen))
#elif defined(__CRT_HAVE_DOS$wcsncat)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16sncat,(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcsncat,(__buf,__src,__buflen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsncat.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16sncat)(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncat))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src, __buflen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16sncat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sncat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16sncat)(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sncat))(__buf, __src, __buflen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32sncat,(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcsncat,(__buf,__src,__buflen))
#elif defined(__CRT_HAVE_KOS$wcsncat)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32sncat,(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcsncat,(__buf,__src,__buflen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsncat.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32sncat)(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncat))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src, __buflen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32sncat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sncat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32sncat)(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sncat))(__buf, __src, __buflen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsspn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> strspn(3)
 * Return the offset from `haystack' to the first
 * character for which `strchr(reject, CH) == NULL'.
 * If no such character exists, return `strlen(haystack)' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,c16sspn,(char16_t const *__haystack, char16_t const *__accept),wcsspn,(__haystack,__accept))
#elif defined(__CRT_HAVE_DOS$wcsspn)
/* >> strspn(3)
 * Return the offset from `haystack' to the first
 * character for which `strchr(reject, CH) == NULL'.
 * If no such character exists, return `strlen(haystack)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,c16sspn,(char16_t const *__haystack, char16_t const *__accept),wcsspn,(__haystack,__accept))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsspn.h>
/* >> strspn(3)
 * Return the offset from `haystack' to the first
 * character for which `strchr(reject, CH) == NULL'.
 * If no such character exists, return `strlen(haystack)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBDCALL c16sspn)(char16_t const *__haystack, char16_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsspn))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16sspn.h>
/* >> strspn(3)
 * Return the offset from `haystack' to the first
 * character for which `strchr(reject, CH) == NULL'.
 * If no such character exists, return `strlen(haystack)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sspn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBDCALL c16sspn)(char16_t const *__haystack, char16_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sspn))(__haystack, __accept); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsspn) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> strspn(3)
 * Return the offset from `haystack' to the first
 * character for which `strchr(reject, CH) == NULL'.
 * If no such character exists, return `strlen(haystack)' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,c32sspn,(char32_t const *__haystack, char32_t const *__accept),wcsspn,(__haystack,__accept))
#elif defined(__CRT_HAVE_KOS$wcsspn)
/* >> strspn(3)
 * Return the offset from `haystack' to the first
 * character for which `strchr(reject, CH) == NULL'.
 * If no such character exists, return `strlen(haystack)' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,c32sspn,(char32_t const *__haystack, char32_t const *__accept),wcsspn,(__haystack,__accept))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsspn.h>
/* >> strspn(3)
 * Return the offset from `haystack' to the first
 * character for which `strchr(reject, CH) == NULL'.
 * If no such character exists, return `strlen(haystack)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBKCALL c32sspn)(char32_t const *__haystack, char32_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsspn))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32sspn.h>
/* >> strspn(3)
 * Return the offset from `haystack' to the first
 * character for which `strchr(reject, CH) == NULL'.
 * If no such character exists, return `strlen(haystack)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sspn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBKCALL c32sspn)(char32_t const *__haystack, char32_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sspn))(__haystack, __accept); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscspn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> strcspn(3)
 * Return the offset from `haystack' to the first
 * character for which `strchr(reject, CH) != NULL'.
 * If no such character exists, return `strlen(haystack)' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,c16scspn,(char16_t const *__haystack, char16_t const *__reject),wcscspn,(__haystack,__reject))
#elif defined(__CRT_HAVE_DOS$wcscspn)
/* >> strcspn(3)
 * Return the offset from `haystack' to the first
 * character for which `strchr(reject, CH) != NULL'.
 * If no such character exists, return `strlen(haystack)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,c16scspn,(char16_t const *__haystack, char16_t const *__reject),wcscspn,(__haystack,__reject))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcscspn.h>
/* >> strcspn(3)
 * Return the offset from `haystack' to the first
 * character for which `strchr(reject, CH) != NULL'.
 * If no such character exists, return `strlen(haystack)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBDCALL c16scspn)(char16_t const *__haystack, char16_t const *__reject) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscspn))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__reject); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16scspn.h>
/* >> strcspn(3)
 * Return the offset from `haystack' to the first
 * character for which `strchr(reject, CH) != NULL'.
 * If no such character exists, return `strlen(haystack)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16scspn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBDCALL c16scspn)(char16_t const *__haystack, char16_t const *__reject) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16scspn))(__haystack, __reject); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscspn) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> strcspn(3)
 * Return the offset from `haystack' to the first
 * character for which `strchr(reject, CH) != NULL'.
 * If no such character exists, return `strlen(haystack)' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,c32scspn,(char32_t const *__haystack, char32_t const *__reject),wcscspn,(__haystack,__reject))
#elif defined(__CRT_HAVE_KOS$wcscspn)
/* >> strcspn(3)
 * Return the offset from `haystack' to the first
 * character for which `strchr(reject, CH) != NULL'.
 * If no such character exists, return `strlen(haystack)' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,c32scspn,(char32_t const *__haystack, char32_t const *__reject),wcscspn,(__haystack,__reject))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcscspn.h>
/* >> strcspn(3)
 * Return the offset from `haystack' to the first
 * character for which `strchr(reject, CH) != NULL'.
 * If no such character exists, return `strlen(haystack)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBKCALL c32scspn)(char32_t const *__haystack, char32_t const *__reject) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscspn))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__reject); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32scspn.h>
/* >> strcspn(3)
 * Return the offset from `haystack' to the first
 * character for which `strchr(reject, CH) != NULL'.
 * If no such character exists, return `strlen(haystack)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32scspn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBKCALL c32scspn)(char32_t const *__haystack, char32_t const *__reject) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32scspn))(__haystack, __reject); })
#endif /* !... */
#if defined(__CRT_HAVE_wcspbrk) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16spbrk,(char16_t *__haystack, char16_t const *__accept),wcspbrk,(__haystack,__accept))
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16spbrk,(char16_t const *__haystack, char16_t const *__accept),wcspbrk,(__haystack,__accept))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16spbrk,(char16_t const *__haystack, char16_t const *__accept),wcspbrk,(__haystack,__accept))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wcspbrk)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16spbrk,(char16_t *__haystack, char16_t const *__accept),wcspbrk,(__haystack,__accept))
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16spbrk,(char16_t const *__haystack, char16_t const *__accept),wcspbrk,(__haystack,__accept))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16spbrk,(char16_t const *__haystack, char16_t const *__accept),wcspbrk,(__haystack,__accept))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcspbrk.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16spbrk)(char16_t *__haystack, char16_t const *__accept) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16spbrk)(char16_t const *__haystack, char16_t const *__accept) { return (__CHAR16_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16spbrk)(char16_t const *__haystack, char16_t const *__accept) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c16spbrk.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16spbrk)(char16_t *__haystack, char16_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16spbrk))(__haystack, __accept); }
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t const *__NOTHROW_NCX(__LIBDCALL c16spbrk)(char16_t const *__haystack, char16_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16spbrk))(__haystack, __accept); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16spbrk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16spbrk)(char16_t const *__haystack, char16_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16spbrk))(__haystack, __accept); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_wcspbrk) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32spbrk,(char32_t *__haystack, char32_t const *__accept),wcspbrk,(__haystack,__accept))
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,c32spbrk,(char32_t const *__haystack, char32_t const *__accept),wcspbrk,(__haystack,__accept))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32spbrk,(char32_t const *__haystack, char32_t const *__accept),wcspbrk,(__haystack,__accept))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_KOS$wcspbrk)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32spbrk,(char32_t *__haystack, char32_t const *__accept),wcspbrk,(__haystack,__accept))
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,c32spbrk,(char32_t const *__haystack, char32_t const *__accept),wcspbrk,(__haystack,__accept))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32spbrk,(char32_t const *__haystack, char32_t const *__accept),wcspbrk,(__haystack,__accept))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcspbrk.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32spbrk)(char32_t *__haystack, char32_t const *__accept) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32spbrk)(char32_t const *__haystack, char32_t const *__accept) { return (__CHAR32_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32spbrk)(char32_t const *__haystack, char32_t const *__accept) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/parts.uchar.string/c32spbrk.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32spbrk)(char32_t *__haystack, char32_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32spbrk))(__haystack, __accept); }
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t const *__NOTHROW_NCX(__LIBKCALL c32spbrk)(char32_t const *__haystack, char32_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32spbrk))(__haystack, __accept); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32spbrk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32spbrk)(char32_t const *__haystack, char32_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32spbrk))(__haystack, __accept); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#ifndef __c16stok_defined
#define __c16stok_defined 1
#if defined(__CRT_HAVE_wcstok) && !defined(__CRT_DOS_PRIMARY) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((2, 3)),char16_t *,__NOTHROW_NCX,c16stok,(char16_t *__string, char16_t const *__restrict __delim, char16_t **__restrict __save_ptr),wcstok,(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE_DOS$wcstok) && !defined(__CRT_DOS_PRIMARY)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)),char16_t *,__NOTHROW_NCX,c16stok,(char16_t *__string, char16_t const *__restrict __delim, char16_t **__restrict __save_ptr),wcstok,(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE_wcstok_s) && defined(__CRT_DOS_PRIMARY) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((2, 3)),char16_t *,__NOTHROW_NCX,c16stok,(char16_t *__string, char16_t const *__restrict __delim, char16_t **__restrict __save_ptr),wcstok_s,(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE_DOS$wcstok_s) && defined(__CRT_DOS_PRIMARY)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)),char16_t *,__NOTHROW_NCX,c16stok,(char16_t *__string, char16_t const *__restrict __delim, char16_t **__restrict __save_ptr),wcstok_s,(__string,__delim,__save_ptr))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstok.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2, 3)) char16_t *__NOTHROW_NCX(__LIBDCALL c16stok)(char16_t *__string, char16_t const *__restrict __delim, char16_t **__restrict __save_ptr) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstok))((__WCHAR_TYPE__ *)__string, (__WCHAR_TYPE__ const *)__delim, (__WCHAR_TYPE__ **)__save_ptr); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16stok.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stok, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2, 3)) char16_t *__NOTHROW_NCX(__LIBDCALL c16stok)(char16_t *__string, char16_t const *__restrict __delim, char16_t **__restrict __save_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stok))(__string, __delim, __save_ptr); })
#endif /* !... */
#endif /* !__c16stok_defined */
#ifndef __c32stok_defined
#define __c32stok_defined 1
#if defined(__CRT_HAVE_wcstok) && !defined(__CRT_DOS_PRIMARY) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((2, 3)),char32_t *,__NOTHROW_NCX,c32stok,(char32_t *__string, char32_t const *__restrict __delim, char32_t **__restrict __save_ptr),wcstok,(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE_KOS$wcstok) && !defined(__CRT_DOS_PRIMARY)
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3)),char32_t *,__NOTHROW_NCX,c32stok,(char32_t *__string, char32_t const *__restrict __delim, char32_t **__restrict __save_ptr),wcstok,(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE_wcstok_s) && defined(__CRT_DOS_PRIMARY) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((2, 3)),char32_t *,__NOTHROW_NCX,c32stok,(char32_t *__string, char32_t const *__restrict __delim, char32_t **__restrict __save_ptr),wcstok_s,(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE_KOS$wcstok_s) && defined(__CRT_DOS_PRIMARY)
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3)),char32_t *,__NOTHROW_NCX,c32stok,(char32_t *__string, char32_t const *__restrict __delim, char32_t **__restrict __save_ptr),wcstok_s,(__string,__delim,__save_ptr))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstok.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2, 3)) char32_t *__NOTHROW_NCX(__LIBKCALL c32stok)(char32_t *__string, char32_t const *__restrict __delim, char32_t **__restrict __save_ptr) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstok))((__WCHAR_TYPE__ *)__string, (__WCHAR_TYPE__ const *)__delim, (__WCHAR_TYPE__ **)__save_ptr); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32stok.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stok, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2, 3)) char32_t *__NOTHROW_NCX(__LIBKCALL c32stok)(char32_t *__string, char32_t const *__restrict __delim, char32_t **__restrict __save_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stok))(__string, __delim, __save_ptr); })
#endif /* !... */
#endif /* !__c32stok_defined */
#if defined(__CRT_HAVE_wcssep) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16ssep,(char16_t **__restrict __stringp, char16_t const *__restrict __delim),wcssep,(__stringp,__delim))
#elif defined(__CRT_HAVE_DOS$wcssep)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16ssep,(char16_t **__restrict __stringp, char16_t const *__restrict __delim),wcssep,(__stringp,__delim))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcssep.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16ssep)(char16_t **__restrict __stringp, char16_t const *__restrict __delim) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcssep))((__WCHAR_TYPE__ **)__stringp, (__WCHAR_TYPE__ const *)__delim); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16ssep.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ssep, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16ssep)(char16_t **__restrict __stringp, char16_t const *__restrict __delim) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ssep))(__stringp, __delim); })
#endif /* !... */
#if defined(__CRT_HAVE_wcssep) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32ssep,(char32_t **__restrict __stringp, char32_t const *__restrict __delim),wcssep,(__stringp,__delim))
#elif defined(__CRT_HAVE_KOS$wcssep)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32ssep,(char32_t **__restrict __stringp, char32_t const *__restrict __delim),wcssep,(__stringp,__delim))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcssep.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32ssep)(char32_t **__restrict __stringp, char32_t const *__restrict __delim) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcssep))((__WCHAR_TYPE__ **)__stringp, (__WCHAR_TYPE__ const *)__delim); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32ssep.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ssep, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32ssep)(char32_t **__restrict __stringp, char32_t const *__restrict __delim) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ssep))(__stringp, __delim); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsdup) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16sdup,(char16_t const *__restrict __string),wcsdup,(__string))
#elif defined(__CRT_HAVE_DOS$wcsdup)
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16sdup,(char16_t const *__restrict __string),wcsdup,(__string))
#elif defined(__CRT_HAVE__wcsdup) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16sdup,(char16_t const *__restrict __string),_wcsdup,(__string))
#elif defined(__CRT_HAVE_DOS$_wcsdup)
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16sdup,(char16_t const *__restrict __string),_wcsdup,(__string))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsdup.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16sdup)(char16_t const *__restrict __string) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsdup))((__WCHAR_TYPE__ const *)__string); }
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/parts.uchar.string/c16sdup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sdup, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16sdup)(char16_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sdup))(__string); })
#endif /* ... */
#if defined(__CRT_HAVE_wcsdup) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32sdup,(char32_t const *__restrict __string),wcsdup,(__string))
#elif defined(__CRT_HAVE_KOS$wcsdup)
__CREDIRECT_KOS(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32sdup,(char32_t const *__restrict __string),wcsdup,(__string))
#elif defined(__CRT_HAVE__wcsdup) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32sdup,(char32_t const *__restrict __string),_wcsdup,(__string))
#elif defined(__CRT_HAVE_KOS$_wcsdup)
__CREDIRECT_KOS(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32sdup,(char32_t const *__restrict __string),_wcsdup,(__string))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsdup.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32sdup)(char32_t const *__restrict __string) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsdup))((__WCHAR_TYPE__ const *)__string); }
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/parts.uchar.string/c32sdup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sdup, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32sdup)(char32_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sdup))(__string); })
#endif /* ... */
#if defined(__CRT_HAVE_wcsndup) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16sndup,(char16_t const *__restrict __string, __SIZE_TYPE__ __max_chars),wcsndup,(__string,__max_chars))
#elif defined(__CRT_HAVE_DOS$wcsndup)
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16sndup,(char16_t const *__restrict __string, __SIZE_TYPE__ __max_chars),wcsndup,(__string,__max_chars))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsndup.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16sndup)(char16_t const *__restrict __string, __SIZE_TYPE__ __max_chars) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsndup))((__WCHAR_TYPE__ const *)__string, __max_chars); }
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/parts.uchar.string/c16sndup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sndup, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16sndup)(char16_t const *__restrict __string, __SIZE_TYPE__ __max_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sndup))(__string, __max_chars); })
#endif /* ... */
#if defined(__CRT_HAVE_wcsndup) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32sndup,(char32_t const *__restrict __string, __SIZE_TYPE__ __max_chars),wcsndup,(__string,__max_chars))
#elif defined(__CRT_HAVE_KOS$wcsndup)
__CREDIRECT_KOS(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32sndup,(char32_t const *__restrict __string, __SIZE_TYPE__ __max_chars),wcsndup,(__string,__max_chars))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsndup.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32sndup)(char32_t const *__restrict __string, __SIZE_TYPE__ __max_chars) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsndup))((__WCHAR_TYPE__ const *)__string, __max_chars); }
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/parts.uchar.string/c32sndup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sndup, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32sndup)(char32_t const *__restrict __string, __SIZE_TYPE__ __max_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sndup))(__string, __max_chars); })
#endif /* ... */
#if defined(__CRT_HAVE_wcsfry) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16sfry,(char16_t *__restrict __string),wcsfry,(__string))
#elif defined(__CRT_HAVE_DOS$wcsfry)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16sfry,(char16_t *__restrict __string),wcsfry,(__string))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsfry.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16sfry)(char16_t *__restrict __string) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsfry))((__WCHAR_TYPE__ *)__string); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16sfry.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sfry, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16sfry)(char16_t *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sfry))(__string); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsfry) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32sfry,(char32_t *__restrict __string),wcsfry,(__string))
#elif defined(__CRT_HAVE_KOS$wcsfry)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32sfry,(char32_t *__restrict __string),wcsfry,(__string))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsfry.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32sfry)(char32_t *__restrict __string) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsfry))((__WCHAR_TYPE__ *)__string); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32sfry.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sfry, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32sfry)(char32_t *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sfry))(__string); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscasecmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scasecmp,(char16_t const *__s1, char16_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscasecmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scasecmp,(char16_t const *__s1, char16_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scasecmp,(char16_t const *__s1, char16_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$_wcsicmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scasecmp,(char16_t const *__s1, char16_t const *__s2),_wcsicmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcscasecmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16scasecmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16scasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16scasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16scasecmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16scasecmp))(__s1, __s2); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscasecmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scasecmp,(char32_t const *__s1, char32_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$wcscasecmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scasecmp,(char32_t const *__s1, char32_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scasecmp,(char32_t const *__s1, char32_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$_wcsicmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scasecmp,(char32_t const *__s1, char32_t const *__s2),_wcsicmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcscasecmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32scasecmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32scasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32scasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32scasecmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32scasecmp))(__s1, __s2); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncasecmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncasecmp,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsncasecmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncasecmp,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncasecmp,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$_wcsnicmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncasecmp,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsncasecmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16sncasecmp)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16sncasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sncasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16sncasecmp)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sncasecmp))(__s1, __s2, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncasecmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncasecmp,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsncasecmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncasecmp,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncasecmp,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_KOS$_wcsnicmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncasecmp,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsncasecmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32sncasecmp)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32sncasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sncasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32sncasecmp)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sncasecmp))(__s1, __s2, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsxfrm) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((2)),size_t,__NOTHROW_NCX,c16sxfrm,(char16_t *__dst, char16_t const *__restrict __src, size_t __maxlen),wcsxfrm,(__dst,__src,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsxfrm)
__CREDIRECT_DOS(__ATTR_NONNULL((2)),size_t,__NOTHROW_NCX,c16sxfrm,(char16_t *__dst, char16_t const *__restrict __src, size_t __maxlen),wcsxfrm,(__dst,__src,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsxfrm.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) size_t __NOTHROW_NCX(__LIBDCALL c16sxfrm)(char16_t *__dst, char16_t const *__restrict __src, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16sxfrm.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sxfrm, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) size_t __NOTHROW_NCX(__LIBDCALL c16sxfrm)(char16_t *__dst, char16_t const *__restrict __src, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sxfrm))(__dst, __src, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsxfrm) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((2)),size_t,__NOTHROW_NCX,c32sxfrm,(char32_t *__dst, char32_t const *__restrict __src, size_t __maxlen),wcsxfrm,(__dst,__src,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsxfrm)
__CREDIRECT_KOS(__ATTR_NONNULL((2)),size_t,__NOTHROW_NCX,c32sxfrm,(char32_t *__dst, char32_t const *__restrict __src, size_t __maxlen),wcsxfrm,(__dst,__src,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsxfrm.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) size_t __NOTHROW_NCX(__LIBKCALL c32sxfrm)(char32_t *__dst, char32_t const *__restrict __src, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32sxfrm.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sxfrm, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) size_t __NOTHROW_NCX(__LIBKCALL c32sxfrm)(char32_t *__dst, char32_t const *__restrict __src, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sxfrm))(__dst, __src, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscoll) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scoll,(char16_t const *__s1, char16_t const *__s2),wcscoll,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscoll)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scoll,(char16_t const *__s1, char16_t const *__s2),wcscoll,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcscoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16scoll)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16scoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16scoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16scoll)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16scoll))(__s1, __s2); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscoll) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scoll,(char32_t const *__s1, char32_t const *__s2),wcscoll,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$wcscoll)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scoll,(char32_t const *__s1, char32_t const *__s2),wcscoll,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcscoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32scoll)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32scoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32scoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32scoll)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32scoll))(__s1, __s2); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncoll) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsncoll)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsncoll) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsncoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$_wcsncoll)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsncoll,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsncoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16sncoll)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16sncoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sncoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16sncoll)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sncoll))(__s1, __s2, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncoll) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsncoll)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsncoll) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsncoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_KOS$_wcsncoll)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsncoll,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsncoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32sncoll)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32sncoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sncoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32sncoll)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sncoll))(__s1, __s2, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscasecoll) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scasecoll,(char16_t const *__s1, char16_t const *__s2),wcscasecoll,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscasecoll)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scasecoll,(char16_t const *__s1, char16_t const *__s2),wcscasecoll,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicoll) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scasecoll,(char16_t const *__s1, char16_t const *__s2),_wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$_wcsicoll)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scasecoll,(char16_t const *__s1, char16_t const *__s2),_wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicoll) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scasecoll,(char16_t const *__s1, char16_t const *__s2),wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcsicoll)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scasecoll,(char16_t const *__s1, char16_t const *__s2),wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcscasecmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scasecoll,(char16_t const *__s1, char16_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscasecmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scasecoll,(char16_t const *__s1, char16_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scasecoll,(char16_t const *__s1, char16_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$_wcsicmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scasecoll,(char16_t const *__s1, char16_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scasecoll,(char16_t const *__s1, char16_t const *__s2),wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcsicmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scasecoll,(char16_t const *__s1, char16_t const *__s2),wcsicmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcscasecoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16scasecoll)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16scasecoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16scasecoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16scasecoll)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16scasecoll))(__s1, __s2); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscasecoll) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scasecoll,(char32_t const *__s1, char32_t const *__s2),wcscasecoll,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$wcscasecoll)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scasecoll,(char32_t const *__s1, char32_t const *__s2),wcscasecoll,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicoll) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scasecoll,(char32_t const *__s1, char32_t const *__s2),_wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$_wcsicoll)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scasecoll,(char32_t const *__s1, char32_t const *__s2),_wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicoll) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scasecoll,(char32_t const *__s1, char32_t const *__s2),wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$wcsicoll)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scasecoll,(char32_t const *__s1, char32_t const *__s2),wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcscasecmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scasecoll,(char32_t const *__s1, char32_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$wcscasecmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scasecoll,(char32_t const *__s1, char32_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scasecoll,(char32_t const *__s1, char32_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$_wcsicmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scasecoll,(char32_t const *__s1, char32_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scasecoll,(char32_t const *__s1, char32_t const *__s2),wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$wcsicmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scasecoll,(char32_t const *__s1, char32_t const *__s2),wcsicmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcscasecoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32scasecoll)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32scasecoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32scasecoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32scasecoll)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32scasecoll))(__s1, __s2); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncasecoll) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsncasecoll)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicoll) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$_wcsnicoll)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicoll) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnicoll)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsncasecmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsncasecmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$_wcsnicmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnicmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsncasecoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16sncasecoll)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16sncasecoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sncasecoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16sncasecoll)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sncasecoll))(__s1, __s2, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncasecoll) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsncasecoll)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicoll) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_KOS$_wcsnicoll)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicoll) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsnicoll)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsncasecmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsncasecmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_KOS$_wcsnicmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsnicmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsncasecoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32sncasecoll)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32sncasecoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sncasecoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32sncasecoll)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sncasecoll))(__s1, __s2, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcslwr) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16slwr,(char16_t *__restrict __str),wcslwr,(__str))
#elif defined(__CRT_HAVE_DOS$wcslwr)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16slwr,(char16_t *__restrict __str),wcslwr,(__str))
#elif defined(__CRT_HAVE__wcslwr) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16slwr,(char16_t *__restrict __str),_wcslwr,(__str))
#elif defined(__CRT_HAVE_DOS$_wcslwr)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16slwr,(char16_t *__restrict __str),_wcslwr,(__str))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcslwr.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16slwr)(char16_t *__restrict __str) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr))((__WCHAR_TYPE__ *)__str); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16slwr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16slwr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16slwr)(char16_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16slwr))(__str); })
#endif /* !... */
#if defined(__CRT_HAVE_wcslwr) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32slwr,(char32_t *__restrict __str),wcslwr,(__str))
#elif defined(__CRT_HAVE_KOS$wcslwr)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32slwr,(char32_t *__restrict __str),wcslwr,(__str))
#elif defined(__CRT_HAVE__wcslwr) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32slwr,(char32_t *__restrict __str),_wcslwr,(__str))
#elif defined(__CRT_HAVE_KOS$_wcslwr)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32slwr,(char32_t *__restrict __str),_wcslwr,(__str))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcslwr.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32slwr)(char32_t *__restrict __str) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr))((__WCHAR_TYPE__ *)__str); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32slwr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32slwr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32slwr)(char32_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32slwr))(__str); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsupr) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16supr,(char16_t *__restrict __str),wcsupr,(__str))
#elif defined(__CRT_HAVE_DOS$wcsupr)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16supr,(char16_t *__restrict __str),wcsupr,(__str))
#elif defined(__CRT_HAVE__wcsupr) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16supr,(char16_t *__restrict __str),_wcsupr,(__str))
#elif defined(__CRT_HAVE_DOS$_wcsupr)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16supr,(char16_t *__restrict __str),_wcsupr,(__str))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsupr.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16supr)(char16_t *__restrict __str) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr))((__WCHAR_TYPE__ *)__str); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16supr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16supr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16supr)(char16_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16supr))(__str); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsupr) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32supr,(char32_t *__restrict __str),wcsupr,(__str))
#elif defined(__CRT_HAVE_KOS$wcsupr)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32supr,(char32_t *__restrict __str),wcsupr,(__str))
#elif defined(__CRT_HAVE__wcsupr) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32supr,(char32_t *__restrict __str),_wcsupr,(__str))
#elif defined(__CRT_HAVE_KOS$_wcsupr)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32supr,(char32_t *__restrict __str),_wcsupr,(__str))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsupr.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32supr)(char32_t *__restrict __str) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr))((__WCHAR_TYPE__ *)__str); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32supr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32supr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32supr)(char32_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32supr))(__str); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsrev) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16srev,(char16_t *__restrict __str),wcsrev,(__str))
#elif defined(__CRT_HAVE_DOS$wcsrev)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16srev,(char16_t *__restrict __str),wcsrev,(__str))
#elif defined(__CRT_HAVE__wcsrev) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16srev,(char16_t *__restrict __str),_wcsrev,(__str))
#elif defined(__CRT_HAVE_DOS$_wcsrev)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16srev,(char16_t *__restrict __str),_wcsrev,(__str))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsrev.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16srev)(char16_t *__restrict __str) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrev))((__WCHAR_TYPE__ *)__str); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16srev.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16srev, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16srev)(char16_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16srev))(__str); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsrev) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32srev,(char32_t *__restrict __str),wcsrev,(__str))
#elif defined(__CRT_HAVE_KOS$wcsrev)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32srev,(char32_t *__restrict __str),wcsrev,(__str))
#elif defined(__CRT_HAVE__wcsrev) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32srev,(char32_t *__restrict __str),_wcsrev,(__str))
#elif defined(__CRT_HAVE_KOS$_wcsrev)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32srev,(char32_t *__restrict __str),_wcsrev,(__str))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsrev.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32srev)(char32_t *__restrict __str) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrev))((__WCHAR_TYPE__ *)__str); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32srev.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32srev, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32srev)(char32_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32srev))(__str); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnrev) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16snrev,(char16_t *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnrev,(__str,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnrev)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16snrev,(char16_t *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnrev,(__str,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsnrev.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16snrev)(char16_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrev))((__WCHAR_TYPE__ *)__str, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16snrev.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16snrev, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16snrev)(char16_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16snrev))(__str, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnrev) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32snrev,(char32_t *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnrev,(__str,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsnrev)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32snrev,(char32_t *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnrev,(__str,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsnrev.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32snrev)(char32_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrev))((__WCHAR_TYPE__ *)__str, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32snrev.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32snrev, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32snrev)(char32_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32snrev))(__str, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsset) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16sset,(char16_t *__restrict __str, int __ch),wcsset,(__str,__ch))
#elif defined(__CRT_HAVE_DOS$wcsset)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16sset,(char16_t *__restrict __str, int __ch),wcsset,(__str,__ch))
#elif defined(__CRT_HAVE__wcsset) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16sset,(char16_t *__restrict __str, int __ch),_wcsset,(__str,__ch))
#elif defined(__CRT_HAVE_DOS$_wcsset)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16sset,(char16_t *__restrict __str, int __ch),_wcsset,(__str,__ch))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsset.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16sset)(char16_t *__restrict __str, int __ch) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsset))((__WCHAR_TYPE__ *)__str, __ch); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16sset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16sset)(char16_t *__restrict __str, int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sset))(__str, __ch); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsset) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32sset,(char32_t *__restrict __str, int __ch),wcsset,(__str,__ch))
#elif defined(__CRT_HAVE_KOS$wcsset)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32sset,(char32_t *__restrict __str, int __ch),wcsset,(__str,__ch))
#elif defined(__CRT_HAVE__wcsset) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32sset,(char32_t *__restrict __str, int __ch),_wcsset,(__str,__ch))
#elif defined(__CRT_HAVE_KOS$_wcsset)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32sset,(char32_t *__restrict __str, int __ch),_wcsset,(__str,__ch))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsset.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32sset)(char32_t *__restrict __str, int __ch) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsset))((__WCHAR_TYPE__ *)__str, __ch); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32sset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32sset)(char32_t *__restrict __str, int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sset))(__str, __ch); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnset) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16snset,(char16_t *__restrict __str, char16_t __ch, __SIZE_TYPE__ __maxlen),wcsnset,(__str,__ch,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnset)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16snset,(char16_t *__restrict __str, char16_t __ch, __SIZE_TYPE__ __maxlen),wcsnset,(__str,__ch,__maxlen))
#elif defined(__CRT_HAVE__wcsnset) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16snset,(char16_t *__restrict __str, char16_t __ch, __SIZE_TYPE__ __maxlen),_wcsnset,(__str,__ch,__maxlen))
#elif defined(__CRT_HAVE_DOS$_wcsnset)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16snset,(char16_t *__restrict __str, char16_t __ch, __SIZE_TYPE__ __maxlen),_wcsnset,(__str,__ch,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsnset.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16snset)(char16_t *__restrict __str, char16_t __ch, __SIZE_TYPE__ __maxlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnset))((__WCHAR_TYPE__ *)__str, (__WCHAR_TYPE__)__ch, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16snset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16snset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16snset)(char16_t *__restrict __str, char16_t __ch, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16snset))(__str, __ch, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsnset) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32snset,(char32_t *__restrict __str, char32_t __ch, __SIZE_TYPE__ __maxlen),wcsnset,(__str,__ch,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsnset)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32snset,(char32_t *__restrict __str, char32_t __ch, __SIZE_TYPE__ __maxlen),wcsnset,(__str,__ch,__maxlen))
#elif defined(__CRT_HAVE__wcsnset) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32snset,(char32_t *__restrict __str, char32_t __ch, __SIZE_TYPE__ __maxlen),_wcsnset,(__str,__ch,__maxlen))
#elif defined(__CRT_HAVE_KOS$_wcsnset)
__CREDIRECT_KOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32snset,(char32_t *__restrict __str, char32_t __ch, __SIZE_TYPE__ __maxlen),_wcsnset,(__str,__ch,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsnset.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32snset)(char32_t *__restrict __str, char32_t __ch, __SIZE_TYPE__ __maxlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnset))((__WCHAR_TYPE__ *)__str, (__WCHAR_TYPE__)__ch, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32snset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32snset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32snset)(char32_t *__restrict __str, char32_t __ch, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32snset))(__str, __ch, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wmemcmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16memcmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_chars, char16_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_wmemcmp,(__s1,__s1_chars,__s2,__s2_chars))
#elif defined(__CRT_HAVE_DOS$fuzzy_wmemcmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16memcmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_chars, char16_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_wmemcmp,(__s1,__s1_chars,__s2,__s2_chars))
#elif defined(__CRT_HAVE_fuzzy_memcmpw) && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16memcmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_chars, char16_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_memcmpw,(__s1,__s1_chars,__s2,__s2_chars))
#elif defined(__CRT_HAVE_DOS$fuzzy_memcmpw)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16memcmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_chars, char16_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_memcmpw,(__s1,__s1_chars,__s2,__s2_chars))
#else /* ... */
#include <libc/local/string/fuzzy_memcmpw.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16memcmp)(char16_t const *__s1, __SIZE_TYPE__ __s1_chars, char16_t const *__s2, __SIZE_TYPE__ __s2_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcmpw))((void const *)__s1, __s1_chars, (void const *)__s2, __s2_chars); }
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wmemcmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32memcmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_chars, char32_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_wmemcmp,(__s1,__s1_chars,__s2,__s2_chars))
#elif defined(__CRT_HAVE_KOS$fuzzy_wmemcmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32memcmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_chars, char32_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_wmemcmp,(__s1,__s1_chars,__s2,__s2_chars))
#elif defined(__CRT_HAVE_fuzzy_memcmpl) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32memcmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_chars, char32_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_memcmpl,(__s1,__s1_chars,__s2,__s2_chars))
#elif defined(__CRT_HAVE_KOS$fuzzy_memcmpl)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32memcmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_chars, char32_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_memcmpl,(__s1,__s1_chars,__s2,__s2_chars))
#else /* ... */
#include <libc/local/string/fuzzy_memcmpl.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32memcmp)(char32_t const *__s1, __SIZE_TYPE__ __s1_chars, char32_t const *__s2, __SIZE_TYPE__ __s2_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcmpl))((void const *)__s1, __s1_chars, (void const *)__s2, __s2_chars); }
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wmemcasecmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16memcasecmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes),fuzzy_wmemcasecmp,(__s1,__s1_bytes,__s2,__s2_bytes))
#elif defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16memcasecmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes),fuzzy_wmemcasecmp,(__s1,__s1_bytes,__s2,__s2_bytes))
#else /* ... */
#include <parts/malloca.h>
#if !defined(__NO_MALLOCA) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/fuzzy_wmemcasecmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16memcasecmp)(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcasecmp))((__WCHAR_TYPE__ const *)__s1, __s1_bytes, (__WCHAR_TYPE__ const *)__s2, __s2_bytes); }
#elif !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c16memcasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16memcasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16memcasecmp)(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16memcasecmp))(__s1, __s1_bytes, __s2, __s2_bytes); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wmemcasecmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32memcasecmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_bytes, char32_t const *__s2, __SIZE_TYPE__ __s2_bytes),fuzzy_wmemcasecmp,(__s1,__s1_bytes,__s2,__s2_bytes))
#elif defined(__CRT_HAVE_KOS$fuzzy_wmemcasecmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32memcasecmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_bytes, char32_t const *__s2, __SIZE_TYPE__ __s2_bytes),fuzzy_wmemcasecmp,(__s1,__s1_bytes,__s2,__s2_bytes))
#else /* ... */
#include <parts/malloca.h>
#if !defined(__NO_MALLOCA) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/fuzzy_wmemcasecmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32memcasecmp)(char32_t const *__s1, __SIZE_TYPE__ __s1_bytes, char32_t const *__s2, __SIZE_TYPE__ __s2_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcasecmp))((__WCHAR_TYPE__ const *)__s1, __s1_bytes, (__WCHAR_TYPE__ const *)__s2, __s2_bytes); }
#elif !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c32memcasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32memcasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32memcasecmp)(char32_t const *__s1, __SIZE_TYPE__ __s1_bytes, char32_t const *__s2, __SIZE_TYPE__ __s2_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32memcasecmp))(__s1, __s1_bytes, __s2, __s2_bytes); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wcscmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16scmp,(char16_t const *__s1, char16_t const *__s2),fuzzy_wcscmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$fuzzy_wcscmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16scmp,(char16_t const *__s1, char16_t const *__s2),fuzzy_wcscmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/fuzzy_wcscmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16scmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <parts/malloca.h>
#if defined(__CRT_HAVE_fuzzy_memcmpw) || (defined(__CRT_HAVE_DOS$fuzzy_wmemcmp) && defined(__LIBCCALL_IS_LIBDCALL)) || !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c16scmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16scmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16scmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16scmp))(__s1, __s2); })
#endif /* __CRT_HAVE_fuzzy_memcmpw || (__CRT_HAVE_DOS$fuzzy_wmemcmp && __LIBCCALL_IS_LIBDCALL) || !__NO_MALLOCA */
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wcscmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32scmp,(char32_t const *__s1, char32_t const *__s2),fuzzy_wcscmp,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$fuzzy_wcscmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32scmp,(char32_t const *__s1, char32_t const *__s2),fuzzy_wcscmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/fuzzy_wcscmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32scmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <parts/malloca.h>
#if defined(__CRT_HAVE_fuzzy_memcmpl) || (defined(__CRT_HAVE_KOS$fuzzy_wmemcmp) && defined(__LIBCCALL_IS_LIBKCALL)) || !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c32scmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32scmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32scmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32scmp))(__s1, __s2); })
#endif /* __CRT_HAVE_fuzzy_memcmpl || (__CRT_HAVE_KOS$fuzzy_wmemcmp && __LIBCCALL_IS_LIBKCALL) || !__NO_MALLOCA */
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wcsncmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16sncmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen),fuzzy_wcsncmp,(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif defined(__CRT_HAVE_DOS$fuzzy_wcsncmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16sncmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen),fuzzy_wcsncmp,(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/fuzzy_wcsncmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16sncmp)(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncmp))((__WCHAR_TYPE__ const *)__s1, __s1_maxlen, (__WCHAR_TYPE__ const *)__s2, __s2_maxlen); }
#else /* ... */
#include <parts/malloca.h>
#if defined(__CRT_HAVE_fuzzy_memcmpw) || (defined(__CRT_HAVE_DOS$fuzzy_wmemcmp) && defined(__LIBCCALL_IS_LIBDCALL)) || !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c16sncmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16sncmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16sncmp)(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16sncmp))(__s1, __s1_maxlen, __s2, __s2_maxlen); })
#endif /* __CRT_HAVE_fuzzy_memcmpw || (__CRT_HAVE_DOS$fuzzy_wmemcmp && __LIBCCALL_IS_LIBDCALL) || !__NO_MALLOCA */
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wcsncmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32sncmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen),fuzzy_wcsncmp,(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif defined(__CRT_HAVE_KOS$fuzzy_wcsncmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32sncmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen),fuzzy_wcsncmp,(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/fuzzy_wcsncmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32sncmp)(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncmp))((__WCHAR_TYPE__ const *)__s1, __s1_maxlen, (__WCHAR_TYPE__ const *)__s2, __s2_maxlen); }
#else /* ... */
#include <parts/malloca.h>
#if defined(__CRT_HAVE_fuzzy_memcmpl) || (defined(__CRT_HAVE_KOS$fuzzy_wmemcmp) && defined(__LIBCCALL_IS_LIBKCALL)) || !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c32sncmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32sncmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32sncmp)(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32sncmp))(__s1, __s1_maxlen, __s2, __s2_maxlen); })
#endif /* __CRT_HAVE_fuzzy_memcmpl || (__CRT_HAVE_KOS$fuzzy_wmemcmp && __LIBCCALL_IS_LIBKCALL) || !__NO_MALLOCA */
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wcscasecmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16scasecmp,(char16_t const *__s1, char16_t const *__s2),fuzzy_wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$fuzzy_wcscasecmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16scasecmp,(char16_t const *__s1, char16_t const *__s2),fuzzy_wcscasecmp,(__s1,__s2))
#else /* ... */
#include <parts/malloca.h>
#if (defined(__CRT_HAVE_fuzzy_wmemcasecmp) || !defined(__NO_MALLOCA)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/fuzzy_wcscasecmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16scasecmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscasecmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp) || !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c16scasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16scasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16scasecmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16scasecmp))(__s1, __s2); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wcscasecmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32scasecmp,(char32_t const *__s1, char32_t const *__s2),fuzzy_wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$fuzzy_wcscasecmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32scasecmp,(char32_t const *__s1, char32_t const *__s2),fuzzy_wcscasecmp,(__s1,__s2))
#else /* ... */
#include <parts/malloca.h>
#if (defined(__CRT_HAVE_fuzzy_wmemcasecmp) || !defined(__NO_MALLOCA)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/fuzzy_wcscasecmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32scasecmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscasecmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fuzzy_wmemcasecmp) || !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c32scasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32scasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32scasecmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32scasecmp))(__s1, __s2); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wcsncasecmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16sncasecmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen),fuzzy_wcsncasecmp,(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif defined(__CRT_HAVE_DOS$fuzzy_wcsncasecmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16sncasecmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen),fuzzy_wcsncasecmp,(__s1,__s1_maxlen,__s2,__s2_maxlen))
#else /* ... */
#include <parts/malloca.h>
#if (defined(__CRT_HAVE_fuzzy_wmemcasecmp) || !defined(__NO_MALLOCA)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/fuzzy_wcsncasecmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16sncasecmp)(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncasecmp))((__WCHAR_TYPE__ const *)__s1, __s1_maxlen, (__WCHAR_TYPE__ const *)__s2, __s2_maxlen); }
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp) || !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c16sncasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16sncasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16sncasecmp)(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16sncasecmp))(__s1, __s1_maxlen, __s2, __s2_maxlen); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wcsncasecmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32sncasecmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen),fuzzy_wcsncasecmp,(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif defined(__CRT_HAVE_KOS$fuzzy_wcsncasecmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32sncasecmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen),fuzzy_wcsncasecmp,(__s1,__s1_maxlen,__s2,__s2_maxlen))
#else /* ... */
#include <parts/malloca.h>
#if (defined(__CRT_HAVE_fuzzy_wmemcasecmp) || !defined(__NO_MALLOCA)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/fuzzy_wcsncasecmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32sncasecmp)(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncasecmp))((__WCHAR_TYPE__ const *)__s1, __s1_maxlen, (__WCHAR_TYPE__ const *)__s2, __s2_maxlen); }
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fuzzy_wmemcasecmp) || !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c32sncasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32sncasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32sncasecmp)(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32sncasecmp))(__s1, __s1_maxlen, __s2, __s2_maxlen); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_wildwcscmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildc16scmp,(char16_t const *__pattern, char16_t const *__string),wildwcscmp,(__pattern,__string))
#elif defined(__CRT_HAVE_DOS$wildwcscmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildc16scmp,(char16_t const *__pattern, char16_t const *__string),wildwcscmp,(__pattern,__string))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wildwcscmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL wildc16scmp)(char16_t const *__pattern, char16_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscmp))((__WCHAR_TYPE__ const *)__pattern, (__WCHAR_TYPE__ const *)__string); }
#else /* ... */
#include <libc/local/parts.uchar.string/wildc16scmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildc16scmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL wildc16scmp)(char16_t const *__pattern, char16_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildc16scmp))(__pattern, __string); })
#endif /* !... */
#if defined(__CRT_HAVE_wildwcscmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildc32scmp,(char32_t const *__pattern, char32_t const *__string),wildwcscmp,(__pattern,__string))
#elif defined(__CRT_HAVE_KOS$wildwcscmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildc32scmp,(char32_t const *__pattern, char32_t const *__string),wildwcscmp,(__pattern,__string))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wildwcscmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL wildc32scmp)(char32_t const *__pattern, char32_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscmp))((__WCHAR_TYPE__ const *)__pattern, (__WCHAR_TYPE__ const *)__string); }
#else /* ... */
#include <libc/local/parts.uchar.string/wildc32scmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildc32scmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL wildc32scmp)(char32_t const *__pattern, char32_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildc32scmp))(__pattern, __string); })
#endif /* !... */
#if defined(__CRT_HAVE_wildwcscasecmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildc16scasecmp,(char16_t const *__pattern, char16_t const *__string),wildwcscasecmp,(__pattern,__string))
#elif defined(__CRT_HAVE_DOS$wildwcscasecmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildc16scasecmp,(char16_t const *__pattern, char16_t const *__string),wildwcscasecmp,(__pattern,__string))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wildwcscasecmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL wildc16scasecmp)(char16_t const *__pattern, char16_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscasecmp))((__WCHAR_TYPE__ const *)__pattern, (__WCHAR_TYPE__ const *)__string); }
#else /* ... */
#include <libc/local/parts.uchar.string/wildc16scasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildc16scasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL wildc16scasecmp)(char16_t const *__pattern, char16_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildc16scasecmp))(__pattern, __string); })
#endif /* !... */
#if defined(__CRT_HAVE_wildwcscasecmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildc32scasecmp,(char32_t const *__pattern, char32_t const *__string),wildwcscasecmp,(__pattern,__string))
#elif defined(__CRT_HAVE_KOS$wildwcscasecmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildc32scasecmp,(char32_t const *__pattern, char32_t const *__string),wildwcscasecmp,(__pattern,__string))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wildwcscasecmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL wildc32scasecmp)(char32_t const *__pattern, char32_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscasecmp))((__WCHAR_TYPE__ const *)__pattern, (__WCHAR_TYPE__ const *)__string); }
#else /* ... */
#include <libc/local/parts.uchar.string/wildc32scasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildc32scasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL wildc32scasecmp)(char32_t const *__pattern, char32_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildc32scasecmp))(__pattern, __string); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsverscmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sverscmp,(char16_t const *__s1, char16_t const *__s2),wcsverscmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcsverscmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sverscmp,(char16_t const *__s1, char16_t const *__s2),wcsverscmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsverscmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16sverscmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsverscmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16sverscmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sverscmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16sverscmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sverscmp))(__s1, __s2); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsverscmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sverscmp,(char32_t const *__s1, char32_t const *__s2),wcsverscmp,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$wcsverscmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sverscmp,(char32_t const *__s1, char32_t const *__s2),wcsverscmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsverscmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32sverscmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsverscmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32sverscmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sverscmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32sverscmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sverscmp))(__s1, __s2); })
#endif /* !... */
#ifdef __USE_XOPEN2K8
#if defined(__CRT_HAVE_wcscasestr_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16scasestr_l,(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale),wcscasestr_l,(__haystack,__needle,__locale))
#elif defined(__CRT_HAVE_DOS$wcscasestr_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16scasestr_l,(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale),wcscasestr_l,(__haystack,__needle,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcscasestr_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16scasestr_l)(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr_l))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16scasestr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16scasestr_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBDCALL c16scasestr_l)(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16scasestr_l))(__haystack, __needle, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscasestr_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32scasestr_l,(char32_t const *__haystack, char32_t const *__needle, __locale_t __locale),wcscasestr_l,(__haystack,__needle,__locale))
#elif defined(__CRT_HAVE_KOS$wcscasestr_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32scasestr_l,(char32_t const *__haystack, char32_t const *__needle, __locale_t __locale),wcscasestr_l,(__haystack,__needle,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcscasestr_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32scasestr_l)(char32_t const *__haystack, char32_t const *__needle, __locale_t __locale) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr_l))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32scasestr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32scasestr_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBKCALL c32scasestr_l)(char32_t const *__haystack, char32_t const *__needle, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32scasestr_l))(__haystack, __needle, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscasecmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scasecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$wcscasecmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scasecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scasecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsicmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scasecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___wcscasecmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scasecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),__wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$__wcscasecmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scasecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),__wcscasecmp_l,(__s1,__s2,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcscasecmp_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16scasecmp_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16scasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16scasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16scasecmp_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16scasecmp_l))(__s1, __s2, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscasecmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scasecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_KOS$wcscasecmp_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scasecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scasecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_KOS$_wcsicmp_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scasecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___wcscasecmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scasecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),__wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_KOS$__wcscasecmp_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scasecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),__wcscasecmp_l,(__s1,__s2,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcscasecmp_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32scasecmp_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32scasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32scasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32scasecmp_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32scasecmp_l))(__s1, __s2, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncasecmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncasecmp_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$wcsncasecmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncasecmp_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncasecmp_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsnicmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncasecmp_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE___wcsncasecmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncasecmp_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$__wcsncasecmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncasecmp_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsncasecmp_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16sncasecmp_l)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16sncasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sncasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16sncasecmp_l)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sncasecmp_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncasecmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncasecmp_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_KOS$wcsncasecmp_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncasecmp_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncasecmp_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_KOS$_wcsnicmp_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncasecmp_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE___wcsncasecmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncasecmp_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_KOS$__wcsncasecmp_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncasecmp_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsncasecmp_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32sncasecmp_l)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32sncasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sncasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32sncasecmp_l)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sncasecmp_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsxfrm_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,c16sxfrm_l,(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$wcsxfrm_l)
__CREDIRECT_DOS(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,c16sxfrm_l,(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsxfrm_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,c16sxfrm_l,(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsxfrm_l)
__CREDIRECT_DOS(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,c16sxfrm_l,(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE___wcsxfrm_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,c16sxfrm_l,(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$__wcsxfrm_l)
__CREDIRECT_DOS(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,c16sxfrm_l,(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsxfrm_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16sxfrm_l)(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm_l))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __maxlen, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16sxfrm_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sxfrm_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16sxfrm_l)(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sxfrm_l))(__dst, __src, __maxlen, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsxfrm_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,c32sxfrm_l,(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE_KOS$wcsxfrm_l)
__CREDIRECT_KOS(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,c32sxfrm_l,(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsxfrm_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,c32sxfrm_l,(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE_KOS$_wcsxfrm_l)
__CREDIRECT_KOS(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,c32sxfrm_l,(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE___wcsxfrm_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,c32sxfrm_l,(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE_KOS$__wcsxfrm_l)
__CREDIRECT_KOS(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,c32sxfrm_l,(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsxfrm_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32sxfrm_l)(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm_l))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __maxlen, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32sxfrm_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sxfrm_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32sxfrm_l)(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sxfrm_l))(__dst, __src, __maxlen, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscoll_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$wcscoll_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcscoll_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$_wcscoll_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___wcscoll_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),__wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$__wcscoll_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),__wcscoll_l,(__s1,__s2,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcscoll_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16scoll_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16scoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16scoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16scoll_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16scoll_l))(__s1, __s2, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscoll_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_KOS$wcscoll_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcscoll_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),_wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_KOS$_wcscoll_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),_wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___wcscoll_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),__wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_KOS$__wcscoll_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),__wcscoll_l,(__s1,__s2,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcscoll_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32scoll_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32scoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32scoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32scoll_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32scoll_l))(__s1, __s2, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncoll_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$wcsncoll_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsncoll_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsncoll_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsncoll_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16sncoll_l)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16sncoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sncoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16sncoll_l)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sncoll_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncoll_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_KOS$wcsncoll_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsncoll_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_KOS$_wcsncoll_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsncoll_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32sncoll_l)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32sncoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sncoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32sncoll_l)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sncoll_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscasecoll_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scasecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscasecoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$wcscasecoll_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scasecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscasecoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicoll_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scasecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcsicoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsicoll_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scasecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcsicoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcscasecmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scasecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$wcscasecmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scasecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scasecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsicmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16scasecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcscasecoll_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16scasecoll_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16scasecoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16scasecoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16scasecoll_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16scasecoll_l))(__s1, __s2, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcscasecoll_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scasecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcscasecoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_KOS$wcscasecoll_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scasecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcscasecoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicoll_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scasecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),_wcsicoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_KOS$_wcsicoll_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scasecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),_wcsicoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcscasecmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scasecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_KOS$wcscasecmp_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scasecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scasecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_KOS$_wcsicmp_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32scasecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcscasecoll_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32scasecoll_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32scasecoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32scasecoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32scasecoll_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32scasecoll_l))(__s1, __s2, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncasecoll_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$wcsncasecoll_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicoll_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsnicoll_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_wcsncasecmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$wcsncasecmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsnicmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16sncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsncasecoll_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16sncasecoll_l)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16sncasecoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sncasecoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL c16sncasecoll_l)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sncasecoll_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsncasecoll_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncasecoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_KOS$wcsncasecoll_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncasecoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicoll_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncasecoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_KOS$_wcsnicoll_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncasecoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_wcsncasecmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncasecoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_KOS$wcsncasecmp_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncasecoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncasecoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_KOS$_wcsnicmp_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32sncasecoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsncasecoll_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32sncasecoll_l)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32sncasecoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sncasecoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL c32sncasecoll_l)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sncasecoll_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcslwr_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16slwr_l,(char16_t *__restrict __str, __locale_t __locale),wcslwr_l,(__str,__locale))
#elif defined(__CRT_HAVE_DOS$wcslwr_l)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16slwr_l,(char16_t *__restrict __str, __locale_t __locale),wcslwr_l,(__str,__locale))
#elif defined(__CRT_HAVE__wcslwr_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16slwr_l,(char16_t *__restrict __str, __locale_t __locale),_wcslwr_l,(__str,__locale))
#elif defined(__CRT_HAVE_DOS$_wcslwr_l)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16slwr_l,(char16_t *__restrict __str, __locale_t __locale),_wcslwr_l,(__str,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcslwr_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16slwr_l)(char16_t *__restrict __str, __locale_t __locale) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr_l))((__WCHAR_TYPE__ *)__str, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16slwr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16slwr_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16slwr_l)(char16_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16slwr_l))(__str, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcslwr_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32slwr_l,(char32_t *__restrict __str, __locale_t __locale),wcslwr_l,(__str,__locale))
#elif defined(__CRT_HAVE_KOS$wcslwr_l)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32slwr_l,(char32_t *__restrict __str, __locale_t __locale),wcslwr_l,(__str,__locale))
#elif defined(__CRT_HAVE__wcslwr_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32slwr_l,(char32_t *__restrict __str, __locale_t __locale),_wcslwr_l,(__str,__locale))
#elif defined(__CRT_HAVE_KOS$_wcslwr_l)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32slwr_l,(char32_t *__restrict __str, __locale_t __locale),_wcslwr_l,(__str,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcslwr_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32slwr_l)(char32_t *__restrict __str, __locale_t __locale) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr_l))((__WCHAR_TYPE__ *)__str, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32slwr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32slwr_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32slwr_l)(char32_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32slwr_l))(__str, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsupr_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16supr_l,(char16_t *__restrict __str, __locale_t __locale),wcsupr_l,(__str,__locale))
#elif defined(__CRT_HAVE_DOS$wcsupr_l)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16supr_l,(char16_t *__restrict __str, __locale_t __locale),wcsupr_l,(__str,__locale))
#elif defined(__CRT_HAVE__wcsupr_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16supr_l,(char16_t *__restrict __str, __locale_t __locale),_wcsupr_l,(__str,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsupr_l)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16supr_l,(char16_t *__restrict __str, __locale_t __locale),_wcsupr_l,(__str,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsupr_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16supr_l)(char16_t *__restrict __str, __locale_t __locale) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr_l))((__WCHAR_TYPE__ *)__str, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c16supr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16supr_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBDCALL c16supr_l)(char16_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16supr_l))(__str, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsupr_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32supr_l,(char32_t *__restrict __str, __locale_t __locale),wcsupr_l,(__str,__locale))
#elif defined(__CRT_HAVE_KOS$wcsupr_l)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32supr_l,(char32_t *__restrict __str, __locale_t __locale),wcsupr_l,(__str,__locale))
#elif defined(__CRT_HAVE__wcsupr_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32supr_l,(char32_t *__restrict __str, __locale_t __locale),_wcsupr_l,(__str,__locale))
#elif defined(__CRT_HAVE_KOS$_wcsupr_l)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32supr_l,(char32_t *__restrict __str, __locale_t __locale),_wcsupr_l,(__str,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsupr_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32supr_l)(char32_t *__restrict __str, __locale_t __locale) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr_l))((__WCHAR_TYPE__ *)__str, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/c32supr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32supr_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBKCALL c32supr_l)(char32_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32supr_l))(__str, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16memcasecmp_l,(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale),fuzzy_wmemcasecmp_l,(__s1,__s1_bytes,__s2,__s2_bytes,__locale))
#elif defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16memcasecmp_l,(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale),fuzzy_wmemcasecmp_l,(__s1,__s1_bytes,__s2,__s2_bytes,__locale))
#else /* ... */
#include <parts/malloca.h>
#if !defined(__NO_MALLOCA) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/fuzzy_wmemcasecmp_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16memcasecmp_l)(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcasecmp_l))((__WCHAR_TYPE__ const *)__s1, __s1_bytes, (__WCHAR_TYPE__ const *)__s2, __s2_bytes, __locale); }
#elif !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c16memcasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16memcasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16memcasecmp_l)(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16memcasecmp_l))(__s1, __s1_bytes, __s2, __s2_bytes, __locale); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32memcasecmp_l,(char32_t const *__s1, __SIZE_TYPE__ __s1_bytes, char32_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale),fuzzy_wmemcasecmp_l,(__s1,__s1_bytes,__s2,__s2_bytes,__locale))
#elif defined(__CRT_HAVE_KOS$fuzzy_wmemcasecmp_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32memcasecmp_l,(char32_t const *__s1, __SIZE_TYPE__ __s1_bytes, char32_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale),fuzzy_wmemcasecmp_l,(__s1,__s1_bytes,__s2,__s2_bytes,__locale))
#else /* ... */
#include <parts/malloca.h>
#if !defined(__NO_MALLOCA) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/fuzzy_wmemcasecmp_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32memcasecmp_l)(char32_t const *__s1, __SIZE_TYPE__ __s1_bytes, char32_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcasecmp_l))((__WCHAR_TYPE__ const *)__s1, __s1_bytes, (__WCHAR_TYPE__ const *)__s2, __s2_bytes, __locale); }
#elif !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c32memcasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32memcasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32memcasecmp_l)(char32_t const *__s1, __SIZE_TYPE__ __s1_bytes, char32_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32memcasecmp_l))(__s1, __s1_bytes, __s2, __s2_bytes, __locale); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wcscasecmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16scasecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),fuzzy_wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$fuzzy_wcscasecmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16scasecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),fuzzy_wcscasecmp_l,(__s1,__s2,__locale))
#else /* ... */
#include <parts/malloca.h>
#if (defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) || !defined(__NO_MALLOCA)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/fuzzy_wcscasecmp_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16scasecmp_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscasecmp_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp_l) || !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c16scasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16scasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16scasecmp_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16scasecmp_l))(__s1, __s2, __locale); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wcscasecmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32scasecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),fuzzy_wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_KOS$fuzzy_wcscasecmp_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32scasecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),fuzzy_wcscasecmp_l,(__s1,__s2,__locale))
#else /* ... */
#include <parts/malloca.h>
#if (defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) || !defined(__NO_MALLOCA)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/fuzzy_wcscasecmp_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32scasecmp_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscasecmp_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fuzzy_wmemcasecmp_l) || !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c32scasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32scasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32scasecmp_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32scasecmp_l))(__s1, __s2, __locale); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wcsncasecmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16sncasecmp_l,(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale),fuzzy_wcsncasecmp_l,(__s1,__s1_maxlen,__s2,__s2_maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$fuzzy_wcsncasecmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16sncasecmp_l,(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale),fuzzy_wcsncasecmp_l,(__s1,__s1_maxlen,__s2,__s2_maxlen,__locale))
#else /* ... */
#include <parts/malloca.h>
#if (defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) || !defined(__NO_MALLOCA)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/fuzzy_wcsncasecmp_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16sncasecmp_l)(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncasecmp_l))((__WCHAR_TYPE__ const *)__s1, __s1_maxlen, (__WCHAR_TYPE__ const *)__s2, __s2_maxlen, __locale); }
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp_l) || !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c16sncasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16sncasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL fuzzy_c16sncasecmp_l)(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16sncasecmp_l))(__s1, __s1_maxlen, __s2, __s2_maxlen, __locale); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_fuzzy_wcsncasecmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32sncasecmp_l,(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale),fuzzy_wcsncasecmp_l,(__s1,__s1_maxlen,__s2,__s2_maxlen,__locale))
#elif defined(__CRT_HAVE_KOS$fuzzy_wcsncasecmp_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32sncasecmp_l,(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale),fuzzy_wcsncasecmp_l,(__s1,__s1_maxlen,__s2,__s2_maxlen,__locale))
#else /* ... */
#include <parts/malloca.h>
#if (defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) || !defined(__NO_MALLOCA)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/fuzzy_wcsncasecmp_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32sncasecmp_l)(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncasecmp_l))((__WCHAR_TYPE__ const *)__s1, __s1_maxlen, (__WCHAR_TYPE__ const *)__s2, __s2_maxlen, __locale); }
#elif (defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fuzzy_wmemcasecmp_l) || !defined(__NO_MALLOCA)
#include <libc/local/parts.uchar.string/fuzzy_c32sncasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32sncasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL fuzzy_c32sncasecmp_l)(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32sncasecmp_l))(__s1, __s1_maxlen, __s2, __s2_maxlen, __locale); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_wildwcscasecmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildc16scasecmp_l,(char16_t const *__pattern, char16_t const *__string, __locale_t __locale),wildwcscasecmp_l,(__pattern,__string,__locale))
#elif defined(__CRT_HAVE_DOS$wildwcscasecmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildc16scasecmp_l,(char16_t const *__pattern, char16_t const *__string, __locale_t __locale),wildwcscasecmp_l,(__pattern,__string,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wildwcscasecmp_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL wildc16scasecmp_l)(char16_t const *__pattern, char16_t const *__string, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscasecmp_l))((__WCHAR_TYPE__ const *)__pattern, (__WCHAR_TYPE__ const *)__string, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/wildc16scasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildc16scasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBDCALL wildc16scasecmp_l)(char16_t const *__pattern, char16_t const *__string, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildc16scasecmp_l))(__pattern, __string, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wildwcscasecmp_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildc32scasecmp_l,(char32_t const *__pattern, char32_t const *__string, __locale_t __locale),wildwcscasecmp_l,(__pattern,__string,__locale))
#elif defined(__CRT_HAVE_KOS$wildwcscasecmp_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildc32scasecmp_l,(char32_t const *__pattern, char32_t const *__string, __locale_t __locale),wildwcscasecmp_l,(__pattern,__string,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wildwcscasecmp_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL wildc32scasecmp_l)(char32_t const *__pattern, char32_t const *__string, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscasecmp_l))((__WCHAR_TYPE__ const *)__pattern, (__WCHAR_TYPE__ const *)__string, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.string/wildc32scasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildc32scasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBKCALL wildc32scasecmp_l)(char32_t const *__pattern, char32_t const *__string, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildc32scasecmp_l))(__pattern, __string, __locale); })
#endif /* !... */
#endif /* __USE_XOPEN2K8 */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_PARTS_UCHAR_STRING_H */
