/* HASH CRC-32:0x72e3fe3d */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
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

#if defined(__CRT_HAVE_wmemcpy) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16memcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, size_t __num_chars),wmemcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memcpyw)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16memcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, size_t __num_chars),memcpyw,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmemcpy)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16memcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, size_t __num_chars),wmemcpy,(__dst,__src,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wmemcpy.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16memcpy)(char16_t *__restrict __dst, char16_t const *__restrict __src, size_t __num_chars) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemcpy))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __num_chars); }
#else /* LIBC: c16memcpy */
#include <local/wchar/c16memcpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16memcpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16memcpy)(char16_t *__restrict __dst, char16_t const *__restrict __src, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16memcpy))(__dst, __src, __num_chars); })
#endif /* c16memcpy... */
#if defined(__CRT_HAVE_wmemcpy) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32memcpy,(char32_t *__restrict __dst, char32_t const *__restrict __src, size_t __num_chars),wmemcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memcpyl)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32memcpy,(char32_t *__restrict __dst, char32_t const *__restrict __src, size_t __num_chars),memcpyl,(__dst,__src,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wmemcpy.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32memcpy)(char32_t *__restrict __dst, char32_t const *__restrict __src, size_t __num_chars) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemcpy))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __num_chars); }
#else /* LIBC: c32memcpy */
#include <local/wchar/c32memcpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32memcpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32memcpy)(char32_t *__restrict __dst, char32_t const *__restrict __src, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32memcpy))(__dst, __src, __num_chars); })
#endif /* c32memcpy... */
#if defined(__CRT_HAVE_wmemmove) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16memmove,(char16_t *__dst, char16_t const *__src, size_t __num_chars),wmemmove,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memmovew)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16memmove,(char16_t *__dst, char16_t const *__src, size_t __num_chars),memmovew,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmemmove)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16memmove,(char16_t *__dst, char16_t const *__src, size_t __num_chars),wmemmove,(__dst,__src,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wmemmove.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16memmove)(char16_t *__dst, char16_t const *__src, size_t __num_chars) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemmove))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __num_chars); }
#else /* LIBC: c16memmove */
#include <local/wchar/c16memmove.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16memmove, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16memmove)(char16_t *__dst, char16_t const *__src, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16memmove))(__dst, __src, __num_chars); })
#endif /* c16memmove... */
#if defined(__CRT_HAVE_wmemmove) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32memmove,(char32_t *__dst, char32_t const *__src, size_t __num_chars),wmemmove,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memmovel)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32memmove,(char32_t *__dst, char32_t const *__src, size_t __num_chars),memmovel,(__dst,__src,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wmemmove.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32memmove)(char32_t *__dst, char32_t const *__src, size_t __num_chars) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemmove))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __num_chars); }
#else /* LIBC: c32memmove */
#include <local/wchar/c32memmove.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32memmove, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32memmove)(char32_t *__dst, char32_t const *__src, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32memmove))(__dst, __src, __num_chars); })
#endif /* c32memmove... */
#if defined(__CRT_HAVE_wmemset) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16memset,(char16_t *__dst, char16_t __filler, size_t __num_chars),wmemset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_memsetw)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16memset,(char16_t *__dst, char16_t __filler, size_t __num_chars),memsetw,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmemset)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16memset,(char16_t *__dst, char16_t __filler, size_t __num_chars),wmemset,(__dst,__filler,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wmemset.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16memset)(char16_t *__dst, char16_t __filler, size_t __num_chars) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemset))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__)__filler, __num_chars); }
#else /* LIBC: c16memset */
#include <local/wchar/c16memset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16memset, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16memset)(char16_t *__dst, char16_t __filler, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16memset))(__dst, __filler, __num_chars); })
#endif /* c16memset... */
#if defined(__CRT_HAVE_wmemset) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32memset,(char32_t *__dst, char32_t __filler, size_t __num_chars),wmemset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_memsetl)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32memset,(char32_t *__dst, char32_t __filler, size_t __num_chars),memsetl,(__dst,__filler,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wmemset.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32memset)(char32_t *__dst, char32_t __filler, size_t __num_chars) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemset))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__)__filler, __num_chars); }
#else /* LIBC: c32memset */
#include <local/wchar/c32memset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32memset, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32memset)(char32_t *__dst, char32_t __filler, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32memset))(__dst, __filler, __num_chars); })
#endif /* c32memset... */
#if defined(__CRT_HAVE_wmempcpy) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16mempcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, __SIZE_TYPE__ __num_chars),wmempcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_mempcpyw)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16mempcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, __SIZE_TYPE__ __num_chars),mempcpyw,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmempcpy)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16mempcpy,(char16_t *__restrict __dst, char16_t const *__restrict __src, __SIZE_TYPE__ __num_chars),wmempcpy,(__dst,__src,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wmempcpy.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16mempcpy)(char16_t *__restrict __dst, char16_t const *__restrict __src, __SIZE_TYPE__ __num_chars) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmempcpy))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __num_chars); }
#else /* LIBC: c16mempcpy */
#include <local/wchar/c16mempcpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16mempcpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16mempcpy)(char16_t *__restrict __dst, char16_t const *__restrict __src, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16mempcpy))(__dst, __src, __num_chars); })
#endif /* c16mempcpy... */
#if defined(__CRT_HAVE_wmempcpy) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32mempcpy,(char32_t *__restrict __dst, char32_t const *__restrict __src, __SIZE_TYPE__ __num_chars),wmempcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_mempcpyl)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32mempcpy,(char32_t *__restrict __dst, char32_t const *__restrict __src, __SIZE_TYPE__ __num_chars),mempcpyl,(__dst,__src,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wmempcpy.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32mempcpy)(char32_t *__restrict __dst, char32_t const *__restrict __src, __SIZE_TYPE__ __num_chars) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmempcpy))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __num_chars); }
#else /* LIBC: c32mempcpy */
#include <local/wchar/c32mempcpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32mempcpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32mempcpy)(char32_t *__restrict __dst, char32_t const *__restrict __src, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32mempcpy))(__dst, __src, __num_chars); })
#endif /* c32mempcpy... */
#if defined(__CRT_HAVE_wmempmove) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16mempmove,(char16_t *__dst, char16_t const *__src, __SIZE_TYPE__ __num_chars),wmempmove,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_mempmovew)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16mempmove,(char16_t *__dst, char16_t const *__src, __SIZE_TYPE__ __num_chars),mempmovew,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmempmove)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16mempmove,(char16_t *__dst, char16_t const *__src, __SIZE_TYPE__ __num_chars),wmempmove,(__dst,__src,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wmempmove.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16mempmove)(char16_t *__dst, char16_t const *__src, __SIZE_TYPE__ __num_chars) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmempmove))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __num_chars); }
#else /* LIBC: c16mempmove */
#include <local/wchar/c16mempmove.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16mempmove, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16mempmove)(char16_t *__dst, char16_t const *__src, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16mempmove))(__dst, __src, __num_chars); })
#endif /* c16mempmove... */
#if defined(__CRT_HAVE_wmempmove) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32mempmove,(char32_t *__dst, char32_t const *__src, __SIZE_TYPE__ __num_chars),wmempmove,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_mempmovel)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32mempmove,(char32_t *__dst, char32_t const *__src, __SIZE_TYPE__ __num_chars),mempmovel,(__dst,__src,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wmempmove.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32mempmove)(char32_t *__dst, char32_t const *__src, __SIZE_TYPE__ __num_chars) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmempmove))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __num_chars); }
#else /* LIBC: c32mempmove */
#include <local/wchar/c32mempmove.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32mempmove, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32mempmove)(char32_t *__dst, char32_t const *__src, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32mempmove))(__dst, __src, __num_chars); })
#endif /* c32mempmove... */
#if defined(__CRT_HAVE_wmempset) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as wmemset, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16mempset,(char16_t *__dst, char16_t __filler, __SIZE_TYPE__ __num_chars),wmempset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_mempsetw)
/* Same as wmemset, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16mempset,(char16_t *__dst, char16_t __filler, __SIZE_TYPE__ __num_chars),mempsetw,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmempset)
/* Same as wmemset, but return a pointer after the last written character */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16mempset,(char16_t *__dst, char16_t __filler, __SIZE_TYPE__ __num_chars),wmempset,(__dst,__filler,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wmempset.h>
/* Same as wmemset, but return a pointer after the last written character */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16mempset)(char16_t *__dst, char16_t __filler, __SIZE_TYPE__ __num_chars) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmempset))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__)__filler, __num_chars); }
#else /* LIBC: c16mempset */
#include <local/wchar/c16mempset.h>
/* Same as wmemset, but return a pointer after the last written character */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16mempset, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16mempset)(char16_t *__dst, char16_t __filler, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16mempset))(__dst, __filler, __num_chars); })
#endif /* c16mempset... */
#if defined(__CRT_HAVE_wmempset) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as wmemset, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32mempset,(char32_t *__dst, char32_t __filler, __SIZE_TYPE__ __num_chars),wmempset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_mempsetl)
/* Same as wmemset, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32mempset,(char32_t *__dst, char32_t __filler, __SIZE_TYPE__ __num_chars),mempsetl,(__dst,__filler,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wmempset.h>
/* Same as wmemset, but return a pointer after the last written character */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32mempset)(char32_t *__dst, char32_t __filler, __SIZE_TYPE__ __num_chars) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmempset))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__)__filler, __num_chars); }
#else /* LIBC: c32mempset */
#include <local/wchar/c32mempset.h>
/* Same as wmemset, but return a pointer after the last written character */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32mempset, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32mempset)(char32_t *__dst, char32_t __filler, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32mempset))(__dst, __filler, __num_chars); })
#endif /* c32mempset... */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO)
#if defined(__CRT_HAVE_wcsend) && (__SIZEOF_WCHAR_T__ == 2)
extern "C++" {
/* Same as `STR+c16len(STR)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16end,(char16_t *__restrict __string),wcsend,(__string))
/* Same as `STR+c16len(STR)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16end,(char16_t const *__restrict __string),wcsend,(__string))
}
#elif defined(__CRT_HAVE_DOS$wcsend)
extern "C++" {
/* Same as `STR+c16len(STR)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16end,(char16_t *__restrict __string),wcsend,(__string))
/* Same as `STR+c16len(STR)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16end,(char16_t const *__restrict __string),wcsend,(__string))
}
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsend.h>
extern "C++" {
/* Same as `STR+c16len(STR)' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16end)(char16_t *__restrict __string) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))((__WCHAR_TYPE__ const *)__string); }
/* Same as `STR+c16len(STR)' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBCCALL c16end)(char16_t const *__restrict __string) { return (char16_t const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))((__WCHAR_TYPE__ const *)__string); }
}
#else /* LIBC: c16end */
#include <local/wchar/c16end.h>
extern "C++" {
/* Same as `STR+c16len(STR)' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16end)(char16_t *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16end))(__string); }
/* Same as `STR+c16len(STR)' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBCCALL c16end)(char16_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16end))(__string); }
}
#endif /* c16end... */
#else /* __cplusplus && __CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcsend) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `STR+c16len(STR)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16end,(char16_t const *__restrict __string),wcsend,(__string))
#elif defined(__CRT_HAVE_DOS$wcsend)
/* Same as `STR+c16len(STR)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16end,(char16_t const *__restrict __string),wcsend,(__string))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsend.h>
/* Same as `STR+c16len(STR)' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16end)(char16_t const *__restrict __string) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))((__WCHAR_TYPE__ const *)__string); }
#else /* LIBC: c16end */
#include <local/wchar/c16end.h>
/* Same as `STR+c16len(STR)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16end, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16end)(char16_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16end))(__string); })
#endif /* c16end... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO)
#if defined(__CRT_HAVE_wcsend) && (__SIZEOF_WCHAR_T__ == 4)
extern "C++" {
/* Same as `STR+c32len(STR)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32end,(char32_t *__restrict __string),wcsend,(__string))
/* Same as `STR+c32len(STR)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32end,(char32_t const *__restrict __string),wcsend,(__string))
}
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsend.h>
extern "C++" {
/* Same as `STR+c32len(STR)' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32end)(char32_t *__restrict __string) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))((__WCHAR_TYPE__ const *)__string); }
/* Same as `STR+c32len(STR)' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBCCALL c32end)(char32_t const *__restrict __string) { return (char32_t const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))((__WCHAR_TYPE__ const *)__string); }
}
#else /* LIBC: c32end */
#include <local/wchar/c32end.h>
extern "C++" {
/* Same as `STR+c32len(STR)' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32end)(char32_t *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32end))(__string); }
/* Same as `STR+c32len(STR)' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBCCALL c32end)(char32_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32end))(__string); }
}
#endif /* c32end... */
#else /* __cplusplus && __CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcsend) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `STR+c32len(STR)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32end,(char32_t const *__restrict __string),wcsend,(__string))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsend.h>
/* Same as `STR+c32len(STR)' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32end)(char32_t const *__restrict __string) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))((__WCHAR_TYPE__ const *)__string); }
#else /* LIBC: c32end */
#include <local/wchar/c32end.h>
/* Same as `STR+c32len(STR)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32end, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32end)(char32_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32end))(__string); })
#endif /* c32end... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO)
#if defined(__CRT_HAVE_wcsnend) && (__SIZEOF_WCHAR_T__ == 2)
extern "C++" {
/* Same as `STR+c16nlen(STR, MAX_CHARS)' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nend,(char16_t *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string, __maxlen))
/* Same as `STR+c16nlen(STR, MAX_CHARS)' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16nend,(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string, __maxlen))
}
#elif defined(__CRT_HAVE_DOS$wcsnend)
extern "C++" {
/* Same as `STR+c16nlen(STR, MAX_CHARS)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nend,(char16_t *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string, __maxlen))
/* Same as `STR+c16nlen(STR, MAX_CHARS)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16nend,(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string, __maxlen))
}
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsnend.h>
extern "C++" {
/* Same as `STR+c16nlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16nend)(char16_t *__restrict __string, __SIZE_TYPE__ __maxlen) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))((__WCHAR_TYPE__ const *)__string, __maxlen); }
/* Same as `STR+c16nlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBCCALL c16nend)(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (char16_t const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))((__WCHAR_TYPE__ const *)__string, __maxlen); }
}
#else /* LIBC: c16nend */
#include <local/wchar/c16nend.h>
extern "C++" {
/* Same as `STR+c16nlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16nend)(char16_t *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nend))(__string, __maxlen); }
/* Same as `STR+c16nlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBCCALL c16nend)(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nend))(__string, __maxlen); }
}
#endif /* c16nend... */
#else /* __cplusplus && __CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcsnend) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `STR+c16nlen(STR, MAX_CHARS)' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nend,(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnend)
/* Same as `STR+c16nlen(STR, MAX_CHARS)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nend,(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsnend.h>
/* Same as `STR+c16nlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16nend)(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))((__WCHAR_TYPE__ const *)__string, __maxlen); }
#else /* LIBC: c16nend */
#include <local/wchar/c16nend.h>
/* Same as `STR+c16nlen(STR, MAX_CHARS)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16nend, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16nend)(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nend))(__string, __maxlen); })
#endif /* c16nend... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO)
#if defined(__CRT_HAVE_wcsnend) && (__SIZEOF_WCHAR_T__ == 4)
extern "C++" {
/* Same as `STR+c32nlen(STR, MAX_CHARS)' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nend,(char32_t *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string, __maxlen))
/* Same as `STR+c32nlen(STR, MAX_CHARS)' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32nend,(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string, __maxlen))
}
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsnend.h>
extern "C++" {
/* Same as `STR+c32nlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32nend)(char32_t *__restrict __string, __SIZE_TYPE__ __maxlen) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))((__WCHAR_TYPE__ const *)__string, __maxlen); }
/* Same as `STR+c32nlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBCCALL c32nend)(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (char32_t const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))((__WCHAR_TYPE__ const *)__string, __maxlen); }
}
#else /* LIBC: c32nend */
#include <local/wchar/c32nend.h>
extern "C++" {
/* Same as `STR+c32nlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32nend)(char32_t *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nend))(__string, __maxlen); }
/* Same as `STR+c32nlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBCCALL c32nend)(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nend))(__string, __maxlen); }
}
#endif /* c32nend... */
#else /* __cplusplus && __CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcsnend) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `STR+c32nlen(STR, MAX_CHARS)' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nend,(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsnend.h>
/* Same as `STR+c32nlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32nend)(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))((__WCHAR_TYPE__ const *)__string, __maxlen); }
#else /* LIBC: c32nend */
#include <local/wchar/c32nend.h>
/* Same as `STR+c32nlen(STR, MAX_CHARS)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32nend, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32nend)(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nend))(__string, __maxlen); })
#endif /* c32nend... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcslen) && (__SIZEOF_WCHAR_T__ == 2)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16len,(char16_t const *__restrict __string),wcslen,(__string))
#elif defined(__CRT_HAVE_DOS$wcslen)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16len,(char16_t const *__restrict __string),wcslen,(__string))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcslen.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c16len)(char16_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslen))((__WCHAR_TYPE__ const *)__string); }
#else /* LIBC: c16len */
#include <local/wchar/c16len.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16len, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c16len)(char16_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16len))(__string); })
#endif /* c16len... */
#if defined(__CRT_HAVE_wcslen) && (__SIZEOF_WCHAR_T__ == 4)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c32len,(char32_t const *__restrict __string),wcslen,(__string))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcslen.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c32len)(char32_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslen))((__WCHAR_TYPE__ const *)__string); }
#else /* LIBC: c32len */
#include <local/wchar/c32len.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32len, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c32len)(char32_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32len))(__string); })
#endif /* c32len... */
#if defined(__CRT_HAVE_wcsnlen) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `c16len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16nlen,(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnlen)
/* Same as `c16len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16nlen,(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsnlen.h>
/* Same as `c16len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c16nlen)(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlen))((__WCHAR_TYPE__ const *)__string, __maxlen); }
#else /* LIBC: c16nlen */
#include <local/wchar/c16nlen.h>
/* Same as `c16len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16nlen, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c16nlen)(char16_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nlen))(__string, __maxlen); })
#endif /* c16nlen... */
#if defined(__CRT_HAVE_wcsnlen) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `c32len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c32nlen,(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsnlen.h>
/* Same as `c32len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c32nlen)(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlen))((__WCHAR_TYPE__ const *)__string, __maxlen); }
#else /* LIBC: c32nlen */
#include <local/wchar/c32nlen.h>
/* Same as `c32len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32nlen, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c32nlen)(char32_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nlen))(__string, __maxlen); })
#endif /* c32nlen... */
#if defined(__CRT_HAVE_wcscmp) && (__SIZEOF_WCHAR_T__ == 2)
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16cmp,(char16_t const *__s1, char16_t const *__s2),wcscmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscmp)
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16cmp,(char16_t const *__s1, char16_t const *__s2),wcscmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcscmp.h>
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c16cmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* LIBC: c16cmp */
#include <local/wchar/c16cmp.h>
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16cmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c16cmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16cmp))(__s1, __s2); })
#endif /* c16cmp... */
#if defined(__CRT_HAVE_wcscmp) && (__SIZEOF_WCHAR_T__ == 4)
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32cmp,(char32_t const *__s1, char32_t const *__s2),wcscmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcscmp.h>
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c32cmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* LIBC: c32cmp */
#include <local/wchar/c32cmp.h>
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32cmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c32cmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32cmp))(__s1, __s2); })
#endif /* c32cmp... */
#if defined(__CRT_HAVE_wcsncmp) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `c16cmp', but compare at most `MAXLEN' characters from either string */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncmp,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsncmp)
/* Same as `c16cmp', but compare at most `MAXLEN' characters from either string */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncmp,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsncmp.h>
/* Same as `c16cmp', but compare at most `MAXLEN' characters from either string */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c16ncmp)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* LIBC: c16ncmp */
#include <local/wchar/c16ncmp.h>
/* Same as `c16cmp', but compare at most `MAXLEN' characters from either string */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ncmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c16ncmp)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ncmp))(__s1, __s2, __maxlen); })
#endif /* c16ncmp... */
#if defined(__CRT_HAVE_wcsncmp) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `c32cmp', but compare at most `MAXLEN' characters from either string */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncmp,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsncmp.h>
/* Same as `c32cmp', but compare at most `MAXLEN' characters from either string */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c32ncmp)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* LIBC: c32ncmp */
#include <local/wchar/c32ncmp.h>
/* Same as `c32cmp', but compare at most `MAXLEN' characters from either string */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ncmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c32ncmp)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ncmp))(__s1, __s2, __maxlen); })
#endif /* c32ncmp... */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO)
#if defined(__CRT_HAVE_wcschr) && (__SIZEOF_WCHAR_T__ == 2)
extern "C++" {
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16chr,(char16_t *__restrict __haystack, char16_t __needle),wcschr,(__haystack, __needle))
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16chr,(char16_t const *__restrict __haystack, char16_t __needle),wcschr,(__haystack, __needle))
}
#elif defined(__CRT_HAVE_DOS$wcschr)
extern "C++" {
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16chr,(char16_t *__restrict __haystack, char16_t __needle),wcschr,(__haystack, __needle))
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16chr,(char16_t const *__restrict __haystack, char16_t __needle),wcschr,(__haystack, __needle))
}
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcschr.h>
extern "C++" {
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16chr)(char16_t *__restrict __haystack, char16_t __needle) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBCCALL c16chr)(char16_t const *__restrict __haystack, char16_t __needle) { return (char16_t const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
}
#else /* LIBC: c16chr */
#include <local/wchar/c16chr.h>
extern "C++" {
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16chr)(char16_t *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16chr))(__haystack, __needle); }
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBCCALL c16chr)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16chr))(__haystack, __needle); }
}
#endif /* c16chr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcschr) && (__SIZEOF_WCHAR_T__ == 2)
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16chr,(char16_t const *__restrict __haystack, char16_t __needle),wcschr,(__haystack,__needle))
#elif defined(__CRT_HAVE_DOS$wcschr)
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16chr,(char16_t const *__restrict __haystack, char16_t __needle),wcschr,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcschr.h>
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16chr)(char16_t const *__restrict __haystack, char16_t __needle) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#else /* LIBC: c16chr */
#include <local/wchar/c16chr.h>
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16chr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16chr)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16chr))(__haystack, __needle); })
#endif /* c16chr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO)
#if defined(__CRT_HAVE_wcschr) && (__SIZEOF_WCHAR_T__ == 4)
extern "C++" {
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32chr,(char32_t *__restrict __haystack, char32_t __needle),wcschr,(__haystack, __needle))
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32chr,(char32_t const *__restrict __haystack, char32_t __needle),wcschr,(__haystack, __needle))
}
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcschr.h>
extern "C++" {
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32chr)(char32_t *__restrict __haystack, char32_t __needle) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBCCALL c32chr)(char32_t const *__restrict __haystack, char32_t __needle) { return (char32_t const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
}
#else /* LIBC: c32chr */
#include <local/wchar/c32chr.h>
extern "C++" {
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32chr)(char32_t *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32chr))(__haystack, __needle); }
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBCCALL c32chr)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32chr))(__haystack, __needle); }
}
#endif /* c32chr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcschr) && (__SIZEOF_WCHAR_T__ == 4)
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32chr,(char32_t const *__restrict __haystack, char32_t __needle),wcschr,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcschr.h>
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32chr)(char32_t const *__restrict __haystack, char32_t __needle) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#else /* LIBC: c32chr */
#include <local/wchar/c32chr.h>
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32chr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32chr)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32chr))(__haystack, __needle); })
#endif /* c32chr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO)
#if defined(__CRT_HAVE_wcsrchr) && (__SIZEOF_WCHAR_T__ == 2)
extern "C++" {
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16rchr,(char16_t *__restrict __haystack, char16_t __needle),wcsrchr,(__haystack, __needle))
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16rchr,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchr,(__haystack, __needle))
}
#elif defined(__CRT_HAVE_DOS$wcsrchr)
extern "C++" {
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16rchr,(char16_t *__restrict __haystack, char16_t __needle),wcsrchr,(__haystack, __needle))
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16rchr,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchr,(__haystack, __needle))
}
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsrchr.h>
extern "C++" {
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16rchr)(char16_t *__restrict __haystack, char16_t __needle) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBCCALL c16rchr)(char16_t const *__restrict __haystack, char16_t __needle) { return (char16_t const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
}
#else /* LIBC: c16rchr */
#include <local/wchar/c16rchr.h>
extern "C++" {
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16rchr)(char16_t *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rchr))(__haystack, __needle); }
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBCCALL c16rchr)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rchr))(__haystack, __needle); }
}
#endif /* c16rchr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcsrchr) && (__SIZEOF_WCHAR_T__ == 2)
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16rchr,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchr,(__haystack,__needle))
#elif defined(__CRT_HAVE_DOS$wcsrchr)
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16rchr,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchr,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsrchr.h>
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16rchr)(char16_t const *__restrict __haystack, char16_t __needle) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#else /* LIBC: c16rchr */
#include <local/wchar/c16rchr.h>
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16rchr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16rchr)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rchr))(__haystack, __needle); })
#endif /* c16rchr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO)
#if defined(__CRT_HAVE_wcsrchr) && (__SIZEOF_WCHAR_T__ == 4)
extern "C++" {
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32rchr,(char32_t *__restrict __haystack, char32_t __needle),wcsrchr,(__haystack, __needle))
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32rchr,(char32_t const *__restrict __haystack, char32_t __needle),wcsrchr,(__haystack, __needle))
}
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsrchr.h>
extern "C++" {
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32rchr)(char32_t *__restrict __haystack, char32_t __needle) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBCCALL c32rchr)(char32_t const *__restrict __haystack, char32_t __needle) { return (char32_t const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
}
#else /* LIBC: c32rchr */
#include <local/wchar/c32rchr.h>
extern "C++" {
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32rchr)(char32_t *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32rchr))(__haystack, __needle); }
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBCCALL c32rchr)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32rchr))(__haystack, __needle); }
}
#endif /* c32rchr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcsrchr) && (__SIZEOF_WCHAR_T__ == 4)
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32rchr,(char32_t const *__restrict __haystack, char32_t __needle),wcsrchr,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsrchr.h>
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32rchr)(char32_t const *__restrict __haystack, char32_t __needle) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#else /* LIBC: c32rchr */
#include <local/wchar/c32rchr.h>
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32rchr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32rchr)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32rchr))(__haystack, __needle); })
#endif /* c32rchr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO)
#if defined(__CRT_HAVE_wcsnchr) && (__SIZEOF_WCHAR_T__ == 2)
extern "C++" {
/* Same as `c16chr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nchr,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack, __needle, __maxlen))
/* Same as `c16chr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16nchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack, __needle, __maxlen))
}
#elif defined(__CRT_HAVE_DOS$wcsnchr)
extern "C++" {
/* Same as `c16chr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nchr,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack, __needle, __maxlen))
/* Same as `c16chr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16nchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack, __needle, __maxlen))
}
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsnchr.h>
extern "C++" {
/* Same as `c16chr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16nchr)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* Same as `c16chr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBCCALL c16nchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (char16_t const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
}
#else /* LIBC: c16nchr */
#include <local/wchar/c16nchr.h>
extern "C++" {
/* Same as `c16chr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16nchr)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nchr))(__haystack, __needle, __maxlen); }
/* Same as `c16chr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBCCALL c16nchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nchr))(__haystack, __needle, __maxlen); }
}
#endif /* c16nchr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcsnchr) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `c16chr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnchr)
/* Same as `c16chr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsnchr.h>
/* Same as `c16chr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16nchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#else /* LIBC: c16nchr */
#include <local/wchar/c16nchr.h>
/* Same as `c16chr', but don't exceed `MAX_CHARS' characters. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16nchr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16nchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nchr))(__haystack, __needle, __maxlen); })
#endif /* c16nchr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO)
#if defined(__CRT_HAVE_wcsnchr) && (__SIZEOF_WCHAR_T__ == 4)
extern "C++" {
/* Same as `c32chr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nchr,(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack, __needle, __maxlen))
/* Same as `c32chr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32nchr,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack, __needle, __maxlen))
}
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsnchr.h>
extern "C++" {
/* Same as `c32chr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32nchr)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* Same as `c32chr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBCCALL c32nchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (char32_t const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
}
#else /* LIBC: c32nchr */
#include <local/wchar/c32nchr.h>
extern "C++" {
/* Same as `c32chr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32nchr)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nchr))(__haystack, __needle, __maxlen); }
/* Same as `c32chr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBCCALL c32nchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nchr))(__haystack, __needle, __maxlen); }
}
#endif /* c32nchr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcsnchr) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `c32chr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nchr,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsnchr.h>
/* Same as `c32chr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32nchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#else /* LIBC: c32nchr */
#include <local/wchar/c32nchr.h>
/* Same as `c32chr', but don't exceed `MAX_CHARS' characters. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32nchr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32nchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nchr))(__haystack, __needle, __maxlen); })
#endif /* c32nchr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO)
#if defined(__CRT_HAVE_wcsnrchr) && (__SIZEOF_WCHAR_T__ == 2)
extern "C++" {
/* Same as `c16rchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nrchr,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack, __needle, __maxlen))
/* Same as `c16rchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16nrchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack, __needle, __maxlen))
}
#elif defined(__CRT_HAVE_DOS$wcsnrchr)
extern "C++" {
/* Same as `c16rchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nrchr,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack, __needle, __maxlen))
/* Same as `c16rchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16nrchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack, __needle, __maxlen))
}
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsnrchr.h>
extern "C++" {
/* Same as `c16rchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16nrchr)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* Same as `c16rchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBCCALL c16nrchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (char16_t const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
}
#else /* LIBC: c16nrchr */
#include <local/wchar/c16nrchr.h>
extern "C++" {
/* Same as `c16rchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16nrchr)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nrchr))(__haystack, __needle, __maxlen); }
/* Same as `c16rchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBCCALL c16nrchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nrchr))(__haystack, __needle, __maxlen); }
}
#endif /* c16nrchr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcsnrchr) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `c16rchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nrchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnrchr)
/* Same as `c16rchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nrchr,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsnrchr.h>
/* Same as `c16rchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16nrchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#else /* LIBC: c16nrchr */
#include <local/wchar/c16nrchr.h>
/* Same as `c16rchr', but don't exceed `MAX_CHARS' characters. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16nrchr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16nrchr)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nrchr))(__haystack, __needle, __maxlen); })
#endif /* c16nrchr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO)
#if defined(__CRT_HAVE_wcsnrchr) && (__SIZEOF_WCHAR_T__ == 4)
extern "C++" {
/* Same as `c32rchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nrchr,(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack, __needle, __maxlen))
/* Same as `c32rchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32nrchr,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack, __needle, __maxlen))
}
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsnrchr.h>
extern "C++" {
/* Same as `c32rchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32nrchr)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* Same as `c32rchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBCCALL c32nrchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (char32_t const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
}
#else /* LIBC: c32nrchr */
#include <local/wchar/c32nrchr.h>
extern "C++" {
/* Same as `c32rchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32nrchr)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nrchr))(__haystack, __needle, __maxlen); }
/* Same as `c32rchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBCCALL c32nrchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nrchr))(__haystack, __needle, __maxlen); }
}
#endif /* c32nrchr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcsnrchr) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `c32rchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nrchr,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsnrchr.h>
/* Same as `c32rchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32nrchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#else /* LIBC: c32nrchr */
#include <local/wchar/c32nrchr.h>
/* Same as `c32rchr', but don't exceed `MAX_CHARS' characters. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32nrchr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32nrchr)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nrchr))(__haystack, __needle, __maxlen); })
#endif /* c32nrchr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO)
#if defined(__CRT_HAVE_wcschrnul) && (__SIZEOF_WCHAR_T__ == 2)
extern "C++" {
/* Same as `c16chr', but return `c16end(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16chrnul,(char16_t *__restrict __haystack, char16_t __needle),wcschrnul,(__haystack, __needle))
/* Same as `c16chr', but return `c16end(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16chrnul,(char16_t const *__restrict __haystack, char16_t __needle),wcschrnul,(__haystack, __needle))
}
#elif defined(__CRT_HAVE_DOS$wcschrnul)
extern "C++" {
/* Same as `c16chr', but return `c16end(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16chrnul,(char16_t *__restrict __haystack, char16_t __needle),wcschrnul,(__haystack, __needle))
/* Same as `c16chr', but return `c16end(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16chrnul,(char16_t const *__restrict __haystack, char16_t __needle),wcschrnul,(__haystack, __needle))
}
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcschrnul.h>
extern "C++" {
/* Same as `c16chr', but return `c16end(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16chrnul)(char16_t *__restrict __haystack, char16_t __needle) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* Same as `c16chr', but return `c16end(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBCCALL c16chrnul)(char16_t const *__restrict __haystack, char16_t __needle) { return (char16_t const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
}
#else /* LIBC: c16chrnul */
#include <local/wchar/c16chrnul.h>
extern "C++" {
/* Same as `c16chr', but return `c16end(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16chrnul)(char16_t *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16chrnul))((__CHAR16_TYPE__ const *)__haystack, __needle); }
/* Same as `c16chr', but return `c16end(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBCCALL c16chrnul)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16chrnul))((__CHAR16_TYPE__ const *)__haystack, __needle); }
}
#endif /* c16chrnul... */
#else /* __cplusplus && __CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcschrnul) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `c16chr', but return `c16end(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16chrnul,(char16_t const *__haystack, char16_t __needle),wcschrnul,(__haystack,__needle))
#elif defined(__CRT_HAVE_DOS$wcschrnul)
/* Same as `c16chr', but return `c16end(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16chrnul,(char16_t const *__haystack, char16_t __needle),wcschrnul,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcschrnul.h>
/* Same as `c16chr', but return `c16end(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16chrnul)(char16_t const *__haystack, char16_t __needle) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#else /* LIBC: c16chrnul */
#include <local/wchar/c16chrnul.h>
/* Same as `c16chr', but return `c16end(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16chrnul, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16chrnul)(char16_t const *__haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16chrnul))(__haystack, __needle); })
#endif /* c16chrnul... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO)
#if defined(__CRT_HAVE_wcschrnul) && (__SIZEOF_WCHAR_T__ == 4)
extern "C++" {
/* Same as `c32chr', but return `c32end(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32chrnul,(char32_t *__restrict __haystack, char32_t __needle),wcschrnul,(__haystack, __needle))
/* Same as `c32chr', but return `c32end(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32chrnul,(char32_t const *__restrict __haystack, char32_t __needle),wcschrnul,(__haystack, __needle))
}
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcschrnul.h>
extern "C++" {
/* Same as `c32chr', but return `c32end(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32chrnul)(char32_t *__restrict __haystack, char32_t __needle) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* Same as `c32chr', but return `c32end(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBCCALL c32chrnul)(char32_t const *__restrict __haystack, char32_t __needle) { return (char32_t const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
}
#else /* LIBC: c32chrnul */
#include <local/wchar/c32chrnul.h>
extern "C++" {
/* Same as `c32chr', but return `c32end(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32chrnul)(char32_t *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32chrnul))((__CHAR32_TYPE__ const *)__haystack, __needle); }
/* Same as `c32chr', but return `c32end(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBCCALL c32chrnul)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32chrnul))((__CHAR32_TYPE__ const *)__haystack, __needle); }
}
#endif /* c32chrnul... */
#else /* __cplusplus && __CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcschrnul) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `c32chr', but return `c32end(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32chrnul,(char32_t const *__haystack, char32_t __needle),wcschrnul,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcschrnul.h>
/* Same as `c32chr', but return `c32end(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32chrnul)(char32_t const *__haystack, char32_t __needle) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#else /* LIBC: c32chrnul */
#include <local/wchar/c32chrnul.h>
/* Same as `c32chr', but return `c32end(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32chrnul, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32chrnul)(char32_t const *__haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32chrnul))(__haystack, __needle); })
#endif /* c32chrnul... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO)
#if defined(__CRT_HAVE_wcsrchrnul) && (__SIZEOF_WCHAR_T__ == 2)
extern "C++" {
/* Same as `c16rchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16rchrnul,(char16_t *__restrict __haystack, char16_t __needle),wcsrchrnul,(__haystack, __needle))
/* Same as `c16rchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16rchrnul,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchrnul,(__haystack, __needle))
}
#elif defined(__CRT_HAVE_DOS$wcsrchrnul)
extern "C++" {
/* Same as `c16rchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16rchrnul,(char16_t *__restrict __haystack, char16_t __needle),wcsrchrnul,(__haystack, __needle))
/* Same as `c16rchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16rchrnul,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchrnul,(__haystack, __needle))
}
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsrchrnul.h>
extern "C++" {
/* Same as `c16rchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16rchrnul)(char16_t *__restrict __haystack, char16_t __needle) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* Same as `c16rchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBCCALL c16rchrnul)(char16_t const *__restrict __haystack, char16_t __needle) { return (char16_t const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
}
#else /* LIBC: c16rchrnul */
#include <local/wchar/c16rchrnul.h>
extern "C++" {
/* Same as `c16rchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16rchrnul)(char16_t *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rchrnul))(__haystack, __needle); }
/* Same as `c16rchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBCCALL c16rchrnul)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rchrnul))(__haystack, __needle); }
}
#endif /* c16rchrnul... */
#else /* __cplusplus && __CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcsrchrnul) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `c16rchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16rchrnul,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchrnul,(__haystack,__needle))
#elif defined(__CRT_HAVE_DOS$wcsrchrnul)
/* Same as `c16rchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16rchrnul,(char16_t const *__restrict __haystack, char16_t __needle),wcsrchrnul,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsrchrnul.h>
/* Same as `c16rchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16rchrnul)(char16_t const *__restrict __haystack, char16_t __needle) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#else /* LIBC: c16rchrnul */
#include <local/wchar/c16rchrnul.h>
/* Same as `c16rchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16rchrnul, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16rchrnul)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rchrnul))(__haystack, __needle); })
#endif /* c16rchrnul... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO)
#if defined(__CRT_HAVE_wcsrchrnul) && (__SIZEOF_WCHAR_T__ == 4)
extern "C++" {
/* Same as `c32rchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32rchrnul,(char32_t *__restrict __haystack, char32_t __needle),wcsrchrnul,(__haystack, __needle))
/* Same as `c32rchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32rchrnul,(char32_t const *__restrict __haystack, char32_t __needle),wcsrchrnul,(__haystack, __needle))
}
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsrchrnul.h>
extern "C++" {
/* Same as `c32rchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32rchrnul)(char32_t *__restrict __haystack, char32_t __needle) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
/* Same as `c32rchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBCCALL c32rchrnul)(char32_t const *__restrict __haystack, char32_t __needle) { return (char32_t const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
}
#else /* LIBC: c32rchrnul */
#include <local/wchar/c32rchrnul.h>
extern "C++" {
/* Same as `c32rchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32rchrnul)(char32_t *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32rchrnul))(__haystack, __needle); }
/* Same as `c32rchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBCCALL c32rchrnul)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32rchrnul))(__haystack, __needle); }
}
#endif /* c32rchrnul... */
#else /* __cplusplus && __CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcsrchrnul) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `c32rchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32rchrnul,(char32_t const *__restrict __haystack, char32_t __needle),wcsrchrnul,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsrchrnul.h>
/* Same as `c32rchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32rchrnul)(char32_t const *__restrict __haystack, char32_t __needle) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#else /* LIBC: c32rchrnul */
#include <local/wchar/c32rchrnul.h>
/* Same as `c32rchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32rchrnul, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32rchrnul)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32rchrnul))(__haystack, __needle); })
#endif /* c32rchrnul... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO)
#if defined(__CRT_HAVE_wcsnchrnul) && (__SIZEOF_WCHAR_T__ == 2)
extern "C++" {
/* Same as `c16nchr', but return `c16nend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nchrnul,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack, __needle, __maxlen))
/* Same as `c16nchr', but return `c16nend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16nchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack, __needle, __maxlen))
}
#elif defined(__CRT_HAVE_DOS$wcsnchrnul)
extern "C++" {
/* Same as `c16nchr', but return `c16nend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nchrnul,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack, __needle, __maxlen))
/* Same as `c16nchr', but return `c16nend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16nchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack, __needle, __maxlen))
}
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsnchrnul.h>
extern "C++" {
/* Same as `c16nchr', but return `c16nend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16nchrnul)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* Same as `c16nchr', but return `c16nend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBCCALL c16nchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (char16_t const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
}
#else /* LIBC: c16nchrnul */
#include <local/wchar/c16nchrnul.h>
extern "C++" {
/* Same as `c16nchr', but return `c16nend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16nchrnul)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nchrnul))(__haystack, __needle, __maxlen); }
/* Same as `c16nchr', but return `c16nend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBCCALL c16nchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nchrnul))(__haystack, __needle, __maxlen); }
}
#endif /* c16nchrnul... */
#else /* __cplusplus && __CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcsnchrnul) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `c16nchr', but return `c16nend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnchrnul)
/* Same as `c16nchr', but return `c16nend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsnchrnul.h>
/* Same as `c16nchr', but return `c16nend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16nchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#else /* LIBC: c16nchrnul */
#include <local/wchar/c16nchrnul.h>
/* Same as `c16nchr', but return `c16nend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16nchrnul, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16nchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nchrnul))(__haystack, __needle, __maxlen); })
#endif /* c16nchrnul... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO)
#if defined(__CRT_HAVE_wcsnchrnul) && (__SIZEOF_WCHAR_T__ == 4)
extern "C++" {
/* Same as `c32nchr', but return `c32nend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nchrnul,(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack, __needle, __maxlen))
/* Same as `c32nchr', but return `c32nend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32nchrnul,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack, __needle, __maxlen))
}
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsnchrnul.h>
extern "C++" {
/* Same as `c32nchr', but return `c32nend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32nchrnul)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* Same as `c32nchr', but return `c32nend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBCCALL c32nchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (char32_t const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
}
#else /* LIBC: c32nchrnul */
#include <local/wchar/c32nchrnul.h>
extern "C++" {
/* Same as `c32nchr', but return `c32nend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32nchrnul)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nchrnul))(__haystack, __needle, __maxlen); }
/* Same as `c32nchr', but return `c32nend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBCCALL c32nchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nchrnul))(__haystack, __needle, __maxlen); }
}
#endif /* c32nchrnul... */
#else /* __cplusplus && __CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcsnchrnul) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `c32nchr', but return `c32nend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nchrnul,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsnchrnul.h>
/* Same as `c32nchr', but return `c32nend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32nchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#else /* LIBC: c32nchrnul */
#include <local/wchar/c32nchrnul.h>
/* Same as `c32nchr', but return `c32nend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32nchrnul, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32nchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nchrnul))(__haystack, __needle, __maxlen); })
#endif /* c32nchrnul... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO)
#if defined(__CRT_HAVE_wcsnrchrnul) && (__SIZEOF_WCHAR_T__ == 2)
extern "C++" {
/* Same as `c16nrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nrchrnul,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack, __needle, __maxlen))
/* Same as `c16nrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16nrchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack, __needle, __maxlen))
}
#elif defined(__CRT_HAVE_DOS$wcsnrchrnul)
extern "C++" {
/* Same as `c16nrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nrchrnul,(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack, __needle, __maxlen))
/* Same as `c16nrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t const *,__NOTHROW_NCX,c16nrchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack, __needle, __maxlen))
}
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsnrchrnul.h>
extern "C++" {
/* Same as `c16nrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16nrchrnul)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* Same as `c16nrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBCCALL c16nrchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (char16_t const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
}
#else /* LIBC: c16nrchrnul */
#include <local/wchar/c16nrchrnul.h>
extern "C++" {
/* Same as `c16nrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16nrchrnul)(char16_t *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nrchrnul))(__haystack, __needle, __maxlen); }
/* Same as `c16nrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t const *__NOTHROW_NCX(__LIBCCALL c16nrchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nrchrnul))(__haystack, __needle, __maxlen); }
}
#endif /* c16nrchrnul... */
#else /* __cplusplus && __CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcsnrchrnul) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `c16nrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nrchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnrchrnul)
/* Same as `c16nrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nrchrnul,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsnrchrnul.h>
/* Same as `c16nrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16nrchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#else /* LIBC: c16nrchrnul */
#include <local/wchar/c16nrchrnul.h>
/* Same as `c16nrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16nrchrnul, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16nrchrnul)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nrchrnul))(__haystack, __needle, __maxlen); })
#endif /* c16nrchrnul... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO)
#if defined(__CRT_HAVE_wcsnrchrnul) && (__SIZEOF_WCHAR_T__ == 4)
extern "C++" {
/* Same as `c32nrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nrchrnul,(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack, __needle, __maxlen))
/* Same as `c32nrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t const *,__NOTHROW_NCX,c32nrchrnul,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack, __needle, __maxlen))
}
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsnrchrnul.h>
extern "C++" {
/* Same as `c32nrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32nrchrnul)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
/* Same as `c32nrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBCCALL c32nrchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (char32_t const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
}
#else /* LIBC: c32nrchrnul */
#include <local/wchar/c32nrchrnul.h>
extern "C++" {
/* Same as `c32nrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32nrchrnul)(char32_t *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nrchrnul))(__haystack, __needle, __maxlen); }
/* Same as `c32nrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t const *__NOTHROW_NCX(__LIBCCALL c32nrchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nrchrnul))(__haystack, __needle, __maxlen); }
}
#endif /* c32nrchrnul... */
#else /* __cplusplus && __CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcsnrchrnul) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `c32nrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nrchrnul,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsnrchrnul.h>
/* Same as `c32nrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32nrchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#else /* LIBC: c32nrchrnul */
#include <local/wchar/c32nrchrnul.h>
/* Same as `c32nrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32nrchrnul, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32nrchrnul)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nrchrnul))(__haystack, __needle, __maxlen); })
#endif /* c32nrchrnul... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcsoff) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `c16chrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16off,(char16_t const *__restrict __haystack, char16_t __needle),wcsoff,(__haystack,__needle))
#elif defined(__CRT_HAVE_DOS$wcsoff)
/* Same as `c16chrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16off,(char16_t const *__restrict __haystack, char16_t __needle),wcsoff,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsoff.h>
/* Same as `c16chrnul', but return the offset from `STR', rather than the actual address */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c16off)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsoff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#else /* LIBC: c16off */
#include <local/wchar/c16off.h>
/* Same as `c16chrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16off, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c16off)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16off))(__haystack, __needle); })
#endif /* c16off... */
#if defined(__CRT_HAVE_wcsoff) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `c32chrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c32off,(char32_t const *__restrict __haystack, char32_t __needle),wcsoff,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsoff.h>
/* Same as `c32chrnul', but return the offset from `STR', rather than the actual address */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c32off)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsoff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#else /* LIBC: c32off */
#include <local/wchar/c32off.h>
/* Same as `c32chrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32off, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c32off)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32off))(__haystack, __needle); })
#endif /* c32off... */
#if defined(__CRT_HAVE_wcsroff) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `c16rchrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16roff,(char16_t const *__restrict __haystack, char16_t __needle),wcsroff,(__haystack,__needle))
#elif defined(__CRT_HAVE_DOS$wcsroff)
/* Same as `c16rchrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16roff,(char16_t const *__restrict __haystack, char16_t __needle),wcsroff,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsroff.h>
/* Same as `c16rchrnul', but return the offset from `STR', rather than the actual address */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c16roff)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsroff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#else /* LIBC: c16roff */
#include <local/wchar/c16roff.h>
/* Same as `c16rchrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16roff, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c16roff)(char16_t const *__restrict __haystack, char16_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16roff))(__haystack, __needle); })
#endif /* c16roff... */
#if defined(__CRT_HAVE_wcsroff) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `c32rchrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c32roff,(char32_t const *__restrict __haystack, char32_t __needle),wcsroff,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsroff.h>
/* Same as `c32rchrnul', but return the offset from `STR', rather than the actual address */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c32roff)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsroff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle); }
#else /* LIBC: c32roff */
#include <local/wchar/c32roff.h>
/* Same as `c32rchrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32roff, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c32roff)(char32_t const *__restrict __haystack, char32_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32roff))(__haystack, __needle); })
#endif /* c32roff... */
#if defined(__CRT_HAVE_wcsnoff) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `c16nchrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16noff,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnoff,(__haystack,__needle,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnoff)
/* Same as `c16nchrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16noff,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnoff,(__haystack,__needle,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsnoff.h>
/* Same as `c16nchrnul', but return the offset from `STR', rather than the actual address */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c16noff)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnoff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#else /* LIBC: c16noff */
#include <local/wchar/c16noff.h>
/* Same as `c16nchrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16noff, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c16noff)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16noff))(__haystack, __needle, __maxlen); })
#endif /* c16noff... */
#if defined(__CRT_HAVE_wcsnoff) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `c32nchrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c32noff,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnoff,(__haystack,__needle,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsnoff.h>
/* Same as `c32nchrnul', but return the offset from `STR', rather than the actual address */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c32noff)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnoff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#else /* LIBC: c32noff */
#include <local/wchar/c32noff.h>
/* Same as `c32nchrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32noff, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c32noff)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32noff))(__haystack, __needle, __maxlen); })
#endif /* c32noff... */
#if defined(__CRT_HAVE_wcsnroff) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `c16nrchrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16nroff,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnroff,(__haystack,__needle,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnroff)
/* Same as `c16nrchrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c16nroff,(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen),wcsnroff,(__haystack,__needle,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsnroff.h>
/* Same as `c16nrchrnul', but return the offset from `STR', rather than the actual address */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c16nroff)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnroff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#else /* LIBC: c16nroff */
#include <local/wchar/c16nroff.h>
/* Same as `c16nrchrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16nroff, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c16nroff)(char16_t const *__restrict __haystack, char16_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nroff))(__haystack, __needle, __maxlen); })
#endif /* c16nroff... */
#if defined(__CRT_HAVE_wcsnroff) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `c32nrchrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,c32nroff,(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen),wcsnroff,(__haystack,__needle,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsnroff.h>
/* Same as `c32nrchrnul', but return the offset from `STR', rather than the actual address */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c32nroff)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnroff))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__)__needle, __maxlen); }
#else /* LIBC: c32nroff */
#include <local/wchar/c32nroff.h>
/* Same as `c32nrchrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32nroff, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c32nroff)(char32_t const *__restrict __haystack, char32_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nroff))(__haystack, __needle, __maxlen); })
#endif /* c32nroff... */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO)
#if defined(__CRT_HAVE_wcsstr) && (__SIZEOF_WCHAR_T__ == 2)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16str,(char16_t *__haystack, char16_t *__needle),wcsstr,(__haystack, __needle))
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16str,(char16_t const *__haystack, char16_t const *__needle),wcsstr,(__haystack, __needle))
}
#elif defined(__CRT_HAVE_wcswcs) && (__SIZEOF_WCHAR_T__ == 2)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16str,(char16_t *__haystack, char16_t *__needle),wcswcs,(__haystack, __needle))
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16str,(char16_t const *__haystack, char16_t const *__needle),wcswcs,(__haystack, __needle))
}
#elif defined(__CRT_HAVE_DOS$wcswcs)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16str,(char16_t *__haystack, char16_t *__needle),wcswcs,(__haystack, __needle))
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16str,(char16_t const *__haystack, char16_t const *__needle),wcswcs,(__haystack, __needle))
}
#elif defined(__CRT_HAVE_DOS$wcsstr)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16str,(char16_t *__haystack, char16_t *__needle),wcsstr,(__haystack, __needle))
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16str,(char16_t const *__haystack, char16_t const *__needle),wcsstr,(__haystack, __needle))
}
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsstr.h>
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16str)(char16_t *__haystack, char16_t *__needle) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t const *__NOTHROW_NCX(__LIBCCALL c16str)(char16_t const *__haystack, char16_t const *__needle) { return (char16_t const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
}
#else /* LIBC: c16str */
#include <local/wchar/c16str.h>
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16str)(char16_t *__haystack, char16_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16str))(__haystack, __needle); }
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t const *__NOTHROW_NCX(__LIBCCALL c16str)(char16_t const *__haystack, char16_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16str))(__haystack, __needle); }
}
#endif /* c16str... */
#else /* __cplusplus && __CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcsstr) && (__SIZEOF_WCHAR_T__ == 2)
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16str,(char16_t const *__haystack, char16_t const *__needle),wcsstr,(__haystack,__needle))
#elif defined(__CRT_HAVE_wcswcs) && (__SIZEOF_WCHAR_T__ == 2)
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16str,(char16_t const *__haystack, char16_t const *__needle),wcswcs,(__haystack,__needle))
#elif defined(__CRT_HAVE_DOS$wcswcs)
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16str,(char16_t const *__haystack, char16_t const *__needle),wcswcs,(__haystack,__needle))
#elif defined(__CRT_HAVE_DOS$wcsstr)
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16str,(char16_t const *__haystack, char16_t const *__needle),wcsstr,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsstr.h>
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16str)(char16_t const *__haystack, char16_t const *__needle) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
#else /* LIBC: c16str */
#include <local/wchar/c16str.h>
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16str, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16str)(char16_t const *__haystack, char16_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16str))(__haystack, __needle); })
#endif /* c16str... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO)
#if defined(__CRT_HAVE_wcsstr) && (__SIZEOF_WCHAR_T__ == 4)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32str,(char32_t *__haystack, char32_t *__needle),wcsstr,(__haystack, __needle))
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,c32str,(char32_t const *__haystack, char32_t const *__needle),wcsstr,(__haystack, __needle))
}
#elif defined(__CRT_HAVE_wcswcs) && (__SIZEOF_WCHAR_T__ == 4)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32str,(char32_t *__haystack, char32_t *__needle),wcswcs,(__haystack, __needle))
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,c32str,(char32_t const *__haystack, char32_t const *__needle),wcswcs,(__haystack, __needle))
}
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsstr.h>
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32str)(char32_t *__haystack, char32_t *__needle) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t const *__NOTHROW_NCX(__LIBCCALL c32str)(char32_t const *__haystack, char32_t const *__needle) { return (char32_t const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
}
#else /* LIBC: c32str */
#include <local/wchar/c32str.h>
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32str)(char32_t *__haystack, char32_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32str))(__haystack, __needle); }
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t const *__NOTHROW_NCX(__LIBCCALL c32str)(char32_t const *__haystack, char32_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32str))(__haystack, __needle); }
}
#endif /* c32str... */
#else /* __cplusplus && __CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcsstr) && (__SIZEOF_WCHAR_T__ == 4)
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32str,(char32_t const *__haystack, char32_t const *__needle),wcsstr,(__haystack,__needle))
#elif defined(__CRT_HAVE_wcswcs) && (__SIZEOF_WCHAR_T__ == 4)
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32str,(char32_t const *__haystack, char32_t const *__needle),wcswcs,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsstr.h>
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32str)(char32_t const *__haystack, char32_t const *__needle) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
#else /* LIBC: c32str */
#include <local/wchar/c32str.h>
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32str, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32str)(char32_t const *__haystack, char32_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32str))(__haystack, __needle); })
#endif /* c32str... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO)
#if defined(__CRT_HAVE_wcscasestr) && (__SIZEOF_WCHAR_T__ == 2)
extern "C++" {
/* Same as `c16str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr,(char16_t *__haystack, char16_t *__needle),wcscasestr,(__haystack, __needle))
/* Same as `c16str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16casestr,(char16_t const *__haystack, char16_t const *__needle),wcscasestr,(__haystack, __needle))
}
#elif defined(__CRT_HAVE_wcsistr) && (__SIZEOF_WCHAR_T__ == 2)
extern "C++" {
/* Same as `c16str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr,(char16_t *__haystack, char16_t *__needle),wcsistr,(__haystack, __needle))
/* Same as `c16str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16casestr,(char16_t const *__haystack, char16_t const *__needle),wcsistr,(__haystack, __needle))
}
#elif defined(__CRT_HAVE__wcsistr) && (__SIZEOF_WCHAR_T__ == 2)
extern "C++" {
/* Same as `c16str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr,(char16_t *__haystack, char16_t *__needle),_wcsistr,(__haystack, __needle))
/* Same as `c16str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16casestr,(char16_t const *__haystack, char16_t const *__needle),_wcsistr,(__haystack, __needle))
}
#elif defined(__CRT_HAVE_wcscasewcs) && (__SIZEOF_WCHAR_T__ == 2)
extern "C++" {
/* Same as `c16str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr,(char16_t *__haystack, char16_t *__needle),wcscasewcs,(__haystack, __needle))
/* Same as `c16str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16casestr,(char16_t const *__haystack, char16_t const *__needle),wcscasewcs,(__haystack, __needle))
}
#elif defined(__CRT_HAVE_wcsiwcs) && (__SIZEOF_WCHAR_T__ == 2)
extern "C++" {
/* Same as `c16str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr,(char16_t *__haystack, char16_t *__needle),wcsiwcs,(__haystack, __needle))
/* Same as `c16str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16casestr,(char16_t const *__haystack, char16_t const *__needle),wcsiwcs,(__haystack, __needle))
}
#elif defined(__CRT_HAVE__wcsiwcs) && (__SIZEOF_WCHAR_T__ == 2)
extern "C++" {
/* Same as `c16str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr,(char16_t *__haystack, char16_t *__needle),_wcsiwcs,(__haystack, __needle))
/* Same as `c16str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16casestr,(char16_t const *__haystack, char16_t const *__needle),_wcsiwcs,(__haystack, __needle))
}
#elif defined(__CRT_HAVE_DOS$wcsistr)
extern "C++" {
/* Same as `c16str', but ignore casing */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr,(char16_t *__haystack, char16_t *__needle),wcsistr,(__haystack, __needle))
/* Same as `c16str', but ignore casing */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16casestr,(char16_t const *__haystack, char16_t const *__needle),wcsistr,(__haystack, __needle))
}
#elif defined(__CRT_HAVE_DOS$wcsiwcs)
extern "C++" {
/* Same as `c16str', but ignore casing */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr,(char16_t *__haystack, char16_t *__needle),wcsiwcs,(__haystack, __needle))
/* Same as `c16str', but ignore casing */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16casestr,(char16_t const *__haystack, char16_t const *__needle),wcsiwcs,(__haystack, __needle))
}
#elif defined(__CRT_HAVE_DOS$_wcsistr)
extern "C++" {
/* Same as `c16str', but ignore casing */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr,(char16_t *__haystack, char16_t *__needle),_wcsistr,(__haystack, __needle))
/* Same as `c16str', but ignore casing */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16casestr,(char16_t const *__haystack, char16_t const *__needle),_wcsistr,(__haystack, __needle))
}
#elif defined(__CRT_HAVE_DOS$_wcsiwcs)
extern "C++" {
/* Same as `c16str', but ignore casing */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr,(char16_t *__haystack, char16_t *__needle),_wcsiwcs,(__haystack, __needle))
/* Same as `c16str', but ignore casing */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16casestr,(char16_t const *__haystack, char16_t const *__needle),_wcsiwcs,(__haystack, __needle))
}
#elif defined(__CRT_HAVE_DOS$wcscasestr)
extern "C++" {
/* Same as `c16str', but ignore casing */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr,(char16_t *__haystack, char16_t *__needle),wcscasestr,(__haystack, __needle))
/* Same as `c16str', but ignore casing */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16casestr,(char16_t const *__haystack, char16_t const *__needle),wcscasestr,(__haystack, __needle))
}
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcscasestr.h>
extern "C++" {
/* Same as `c16str', but ignore casing */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16casestr)(char16_t *__haystack, char16_t *__needle) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
/* Same as `c16str', but ignore casing */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t const *__NOTHROW_NCX(__LIBCCALL c16casestr)(char16_t const *__haystack, char16_t const *__needle) { return (char16_t const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
}
#else /* LIBC: c16casestr */
#include <local/wchar/c16casestr.h>
extern "C++" {
/* Same as `c16str', but ignore casing */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16casestr)(char16_t *__haystack, char16_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16casestr))(__haystack, __needle); }
/* Same as `c16str', but ignore casing */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t const *__NOTHROW_NCX(__LIBCCALL c16casestr)(char16_t const *__haystack, char16_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16casestr))(__haystack, __needle); }
}
#endif /* c16casestr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcscasestr) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `c16str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr,(char16_t const *__haystack, char16_t const *__needle),wcscasestr,(__haystack,__needle))
#elif defined(__CRT_HAVE_wcsistr) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `c16str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr,(char16_t const *__haystack, char16_t const *__needle),wcsistr,(__haystack,__needle))
#elif defined(__CRT_HAVE__wcsistr) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `c16str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr,(char16_t const *__haystack, char16_t const *__needle),_wcsistr,(__haystack,__needle))
#elif defined(__CRT_HAVE_wcscasewcs) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `c16str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr,(char16_t const *__haystack, char16_t const *__needle),wcscasewcs,(__haystack,__needle))
#elif defined(__CRT_HAVE_wcsiwcs) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `c16str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr,(char16_t const *__haystack, char16_t const *__needle),wcsiwcs,(__haystack,__needle))
#elif defined(__CRT_HAVE__wcsiwcs) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `c16str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr,(char16_t const *__haystack, char16_t const *__needle),_wcsiwcs,(__haystack,__needle))
#elif defined(__CRT_HAVE_DOS$wcsistr)
/* Same as `c16str', but ignore casing */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr,(char16_t const *__haystack, char16_t const *__needle),wcsistr,(__haystack,__needle))
#elif defined(__CRT_HAVE_DOS$wcsiwcs)
/* Same as `c16str', but ignore casing */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr,(char16_t const *__haystack, char16_t const *__needle),wcsiwcs,(__haystack,__needle))
#elif defined(__CRT_HAVE_DOS$_wcsistr)
/* Same as `c16str', but ignore casing */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr,(char16_t const *__haystack, char16_t const *__needle),_wcsistr,(__haystack,__needle))
#elif defined(__CRT_HAVE_DOS$_wcsiwcs)
/* Same as `c16str', but ignore casing */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr,(char16_t const *__haystack, char16_t const *__needle),_wcsiwcs,(__haystack,__needle))
#elif defined(__CRT_HAVE_DOS$wcscasestr)
/* Same as `c16str', but ignore casing */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr,(char16_t const *__haystack, char16_t const *__needle),wcscasestr,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcscasestr.h>
/* Same as `c16str', but ignore casing */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16casestr)(char16_t const *__haystack, char16_t const *__needle) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
#else /* LIBC: c16casestr */
#include <local/wchar/c16casestr.h>
/* Same as `c16str', but ignore casing */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16casestr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16casestr)(char16_t const *__haystack, char16_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16casestr))(__haystack, __needle); })
#endif /* c16casestr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO)
#if defined(__CRT_HAVE_wcscasestr) && (__SIZEOF_WCHAR_T__ == 4)
extern "C++" {
/* Same as `c32str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32casestr,(char32_t *__haystack, char32_t *__needle),wcscasestr,(__haystack, __needle))
/* Same as `c32str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,c32casestr,(char32_t const *__haystack, char32_t const *__needle),wcscasestr,(__haystack, __needle))
}
#elif defined(__CRT_HAVE_wcsistr) && (__SIZEOF_WCHAR_T__ == 4)
extern "C++" {
/* Same as `c32str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32casestr,(char32_t *__haystack, char32_t *__needle),wcsistr,(__haystack, __needle))
/* Same as `c32str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,c32casestr,(char32_t const *__haystack, char32_t const *__needle),wcsistr,(__haystack, __needle))
}
#elif defined(__CRT_HAVE__wcsistr) && (__SIZEOF_WCHAR_T__ == 4)
extern "C++" {
/* Same as `c32str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32casestr,(char32_t *__haystack, char32_t *__needle),_wcsistr,(__haystack, __needle))
/* Same as `c32str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,c32casestr,(char32_t const *__haystack, char32_t const *__needle),_wcsistr,(__haystack, __needle))
}
#elif defined(__CRT_HAVE_wcscasewcs) && (__SIZEOF_WCHAR_T__ == 4)
extern "C++" {
/* Same as `c32str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32casestr,(char32_t *__haystack, char32_t *__needle),wcscasewcs,(__haystack, __needle))
/* Same as `c32str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,c32casestr,(char32_t const *__haystack, char32_t const *__needle),wcscasewcs,(__haystack, __needle))
}
#elif defined(__CRT_HAVE_wcsiwcs) && (__SIZEOF_WCHAR_T__ == 4)
extern "C++" {
/* Same as `c32str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32casestr,(char32_t *__haystack, char32_t *__needle),wcsiwcs,(__haystack, __needle))
/* Same as `c32str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,c32casestr,(char32_t const *__haystack, char32_t const *__needle),wcsiwcs,(__haystack, __needle))
}
#elif defined(__CRT_HAVE__wcsiwcs) && (__SIZEOF_WCHAR_T__ == 4)
extern "C++" {
/* Same as `c32str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32casestr,(char32_t *__haystack, char32_t *__needle),_wcsiwcs,(__haystack, __needle))
/* Same as `c32str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,c32casestr,(char32_t const *__haystack, char32_t const *__needle),_wcsiwcs,(__haystack, __needle))
}
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcscasestr.h>
extern "C++" {
/* Same as `c32str', but ignore casing */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32casestr)(char32_t *__haystack, char32_t *__needle) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
/* Same as `c32str', but ignore casing */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t const *__NOTHROW_NCX(__LIBCCALL c32casestr)(char32_t const *__haystack, char32_t const *__needle) { return (char32_t const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
}
#else /* LIBC: c32casestr */
#include <local/wchar/c32casestr.h>
extern "C++" {
/* Same as `c32str', but ignore casing */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32casestr)(char32_t *__haystack, char32_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32casestr))(__haystack, __needle); }
/* Same as `c32str', but ignore casing */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t const *__NOTHROW_NCX(__LIBCCALL c32casestr)(char32_t const *__haystack, char32_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32casestr))(__haystack, __needle); }
}
#endif /* c32casestr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcscasestr) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `c32str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32casestr,(char32_t const *__haystack, char32_t const *__needle),wcscasestr,(__haystack,__needle))
#elif defined(__CRT_HAVE_wcsistr) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `c32str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32casestr,(char32_t const *__haystack, char32_t const *__needle),wcsistr,(__haystack,__needle))
#elif defined(__CRT_HAVE__wcsistr) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `c32str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32casestr,(char32_t const *__haystack, char32_t const *__needle),_wcsistr,(__haystack,__needle))
#elif defined(__CRT_HAVE_wcscasewcs) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `c32str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32casestr,(char32_t const *__haystack, char32_t const *__needle),wcscasewcs,(__haystack,__needle))
#elif defined(__CRT_HAVE_wcsiwcs) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `c32str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32casestr,(char32_t const *__haystack, char32_t const *__needle),wcsiwcs,(__haystack,__needle))
#elif defined(__CRT_HAVE__wcsiwcs) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `c32str', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32casestr,(char32_t const *__haystack, char32_t const *__needle),_wcsiwcs,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcscasestr.h>
/* Same as `c32str', but ignore casing */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32casestr)(char32_t const *__haystack, char32_t const *__needle) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle); }
#else /* LIBC: c32casestr */
#include <local/wchar/c32casestr.h>
/* Same as `c32str', but ignore casing */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32casestr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32casestr)(char32_t const *__haystack, char32_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32casestr))(__haystack, __needle); })
#endif /* c32casestr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcscpy) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16cpy,(char16_t *__restrict __buf, char16_t const *__restrict __src),wcscpy,(__buf,__src))
#elif defined(__CRT_HAVE_DOS$wcscpy)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16cpy,(char16_t *__restrict __buf, char16_t const *__restrict __src),wcscpy,(__buf,__src))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcscpy.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16cpy)(char16_t *__restrict __buf, char16_t const *__restrict __src) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src); }
#else /* LIBC: c16cpy */
#include <local/wchar/c16cpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16cpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16cpy)(char16_t *__restrict __buf, char16_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16cpy))(__buf, __src); })
#endif /* c16cpy... */
#if defined(__CRT_HAVE_wcscpy) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32cpy,(char32_t *__restrict __buf, char32_t const *__restrict __src),wcscpy,(__buf,__src))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcscpy.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32cpy)(char32_t *__restrict __buf, char32_t const *__restrict __src) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src); }
#else /* LIBC: c32cpy */
#include <local/wchar/c32cpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32cpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32cpy)(char32_t *__restrict __buf, char32_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32cpy))(__buf, __src); })
#endif /* c32cpy... */
#if defined(__CRT_HAVE_wcspcpy) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as wcscpy, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16pcpy,(char16_t *__restrict __buf, char16_t const *__restrict __src),wcspcpy,(__buf,__src))
#elif defined(__CRT_HAVE_DOS$wcspcpy)
/* Same as wcscpy, but return a pointer after the last written character */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16pcpy,(char16_t *__restrict __buf, char16_t const *__restrict __src),wcspcpy,(__buf,__src))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcspcpy.h>
/* Same as wcscpy, but return a pointer after the last written character */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16pcpy)(char16_t *__restrict __buf, char16_t const *__restrict __src) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspcpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src); }
#else /* LIBC: c16pcpy */
#include <local/wchar/c16pcpy.h>
/* Same as wcscpy, but return a pointer after the last written character */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16pcpy, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16pcpy)(char16_t *__restrict __buf, char16_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16pcpy))(__buf, __src); })
#endif /* c16pcpy... */
#if defined(__CRT_HAVE_wcspcpy) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as wcscpy, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32pcpy,(char32_t *__restrict __buf, char32_t const *__restrict __src),wcspcpy,(__buf,__src))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcspcpy.h>
/* Same as wcscpy, but return a pointer after the last written character */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32pcpy)(char32_t *__restrict __buf, char32_t const *__restrict __src) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspcpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src); }
#else /* LIBC: c32pcpy */
#include <local/wchar/c32pcpy.h>
/* Same as wcscpy, but return a pointer after the last written character */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32pcpy, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32pcpy)(char32_t *__restrict __buf, char32_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32pcpy))(__buf, __src); })
#endif /* c32pcpy... */
#if defined(__CRT_HAVE_wcsncpy) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16ncpy,(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcsncpy,(__buf,__src,__buflen))
#elif defined(__CRT_HAVE_DOS$wcsncpy)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16ncpy,(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcsncpy,(__buf,__src,__buflen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsncpy.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16ncpy)(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src, __buflen); }
#else /* LIBC: c16ncpy */
#include <local/wchar/c16ncpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ncpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16ncpy)(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ncpy))(__buf, __src, __buflen); })
#endif /* c16ncpy... */
#if defined(__CRT_HAVE_wcsncpy) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32ncpy,(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcsncpy,(__buf,__src,__buflen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsncpy.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32ncpy)(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src, __buflen); }
#else /* LIBC: c32ncpy */
#include <local/wchar/c32ncpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ncpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32ncpy)(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ncpy))(__buf, __src, __buflen); })
#endif /* c32ncpy... */
#if defined(__CRT_HAVE_wcspncpy) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as wcsncpy, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16pncpy,(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcspncpy,(__buf,__src,__buflen))
#elif defined(__CRT_HAVE_DOS$wcspncpy)
/* Same as wcsncpy, but return a pointer after the last written character */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16pncpy,(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcspncpy,(__buf,__src,__buflen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcspncpy.h>
/* Same as wcsncpy, but return a pointer after the last written character */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16pncpy)(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspncpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src, __buflen); }
#else /* LIBC: c16pncpy */
#include <local/wchar/c16pncpy.h>
/* Same as wcsncpy, but return a pointer after the last written character */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16pncpy, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16pncpy)(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16pncpy))(__buf, __src, __buflen); })
#endif /* c16pncpy... */
#if defined(__CRT_HAVE_wcspncpy) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as wcsncpy, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32pncpy,(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcspncpy,(__buf,__src,__buflen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcspncpy.h>
/* Same as wcsncpy, but return a pointer after the last written character */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32pncpy)(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspncpy))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src, __buflen); }
#else /* LIBC: c32pncpy */
#include <local/wchar/c32pncpy.h>
/* Same as wcsncpy, but return a pointer after the last written character */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32pncpy, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32pncpy)(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32pncpy))(__buf, __src, __buflen); })
#endif /* c32pncpy... */
#if defined(__CRT_HAVE_wcscat) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16cat,(char16_t *__restrict __buf, char16_t const *__restrict __src),wcscat,(__buf,__src))
#elif defined(__CRT_HAVE_DOS$wcscat)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16cat,(char16_t *__restrict __buf, char16_t const *__restrict __src),wcscat,(__buf,__src))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcscat.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16cat)(char16_t *__restrict __buf, char16_t const *__restrict __src) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscat))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src); }
#else /* LIBC: c16cat */
#include <local/wchar/c16cat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16cat, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16cat)(char16_t *__restrict __buf, char16_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16cat))(__buf, __src); })
#endif /* c16cat... */
#if defined(__CRT_HAVE_wcscat) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32cat,(char32_t *__restrict __buf, char32_t const *__restrict __src),wcscat,(__buf,__src))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcscat.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32cat)(char32_t *__restrict __buf, char32_t const *__restrict __src) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscat))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src); }
#else /* LIBC: c32cat */
#include <local/wchar/c32cat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32cat, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32cat)(char32_t *__restrict __buf, char32_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32cat))(__buf, __src); })
#endif /* c32cat... */
#if defined(__CRT_HAVE_wcsncat) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16ncat,(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcsncat,(__buf,__src,__buflen))
#elif defined(__CRT_HAVE_DOS$wcsncat)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16ncat,(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcsncat,(__buf,__src,__buflen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsncat.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16ncat)(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncat))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src, __buflen); }
#else /* LIBC: c16ncat */
#include <local/wchar/c16ncat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ncat, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16ncat)(char16_t *__restrict __buf, char16_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ncat))(__buf, __src, __buflen); })
#endif /* c16ncat... */
#if defined(__CRT_HAVE_wcsncat) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32ncat,(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen),wcsncat,(__buf,__src,__buflen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsncat.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32ncat)(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncat))((__WCHAR_TYPE__ *)__buf, (__WCHAR_TYPE__ const *)__src, __buflen); }
#else /* LIBC: c32ncat */
#include <local/wchar/c32ncat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ncat, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32ncat)(char32_t *__restrict __buf, char32_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ncat))(__buf, __src, __buflen); })
#endif /* c32ncat... */
#if defined(__CRT_HAVE_wcsspn) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,c16spn,(char16_t const *__haystack, char16_t const *__accept),wcsspn,(__haystack,__accept))
#elif defined(__CRT_HAVE_DOS$wcsspn)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,c16spn,(char16_t const *__haystack, char16_t const *__accept),wcsspn,(__haystack,__accept))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsspn.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c16spn)(char16_t const *__haystack, char16_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsspn))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
#else /* LIBC: c16spn */
#include <local/wchar/c16spn.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16spn, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c16spn)(char16_t const *__haystack, char16_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16spn))(__haystack, __accept); })
#endif /* c16spn... */
#if defined(__CRT_HAVE_wcsspn) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,c32spn,(char32_t const *__haystack, char32_t const *__accept),wcsspn,(__haystack,__accept))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsspn.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c32spn)(char32_t const *__haystack, char32_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsspn))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
#else /* LIBC: c32spn */
#include <local/wchar/c32spn.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32spn, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c32spn)(char32_t const *__haystack, char32_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32spn))(__haystack, __accept); })
#endif /* c32spn... */
#if defined(__CRT_HAVE_wcscspn) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,c16cspn,(char16_t const *__haystack, char16_t const *__reject),wcscspn,(__haystack,__reject))
#elif defined(__CRT_HAVE_DOS$wcscspn)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,c16cspn,(char16_t const *__haystack, char16_t const *__reject),wcscspn,(__haystack,__reject))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcscspn.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c16cspn)(char16_t const *__haystack, char16_t const *__reject) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscspn))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__reject); }
#else /* LIBC: c16cspn */
#include <local/wchar/c16cspn.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16cspn, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c16cspn)(char16_t const *__haystack, char16_t const *__reject) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16cspn))(__haystack, __reject); })
#endif /* c16cspn... */
#if defined(__CRT_HAVE_wcscspn) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,c32cspn,(char32_t const *__haystack, char32_t const *__reject),wcscspn,(__haystack,__reject))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcscspn.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c32cspn)(char32_t const *__haystack, char32_t const *__reject) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscspn))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__reject); }
#else /* LIBC: c32cspn */
#include <local/wchar/c32cspn.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32cspn, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c32cspn)(char32_t const *__haystack, char32_t const *__reject) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32cspn))(__haystack, __reject); })
#endif /* c32cspn... */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO)
#if defined(__CRT_HAVE_wcspbrk) && (__SIZEOF_WCHAR_T__ == 2)
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16pbrk,(char16_t *__haystack, char16_t const *__accept),wcspbrk,(__haystack, __accept))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16pbrk,(char16_t const *__haystack, char16_t const *__accept),wcspbrk,(__haystack, __accept))
}
#elif defined(__CRT_HAVE_DOS$wcspbrk)
extern "C++" {
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16pbrk,(char16_t *__haystack, char16_t const *__accept),wcspbrk,(__haystack, __accept))
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16pbrk,(char16_t const *__haystack, char16_t const *__accept),wcspbrk,(__haystack, __accept))
}
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcspbrk.h>
extern "C++" {
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16pbrk)(char16_t *__haystack, char16_t const *__accept) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t const *__NOTHROW_NCX(__LIBCCALL c16pbrk)(char16_t const *__haystack, char16_t const *__accept) { return (char16_t const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
}
#else /* LIBC: c16pbrk */
#include <local/wchar/c16pbrk.h>
extern "C++" {
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16pbrk)(char16_t *__haystack, char16_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16pbrk))(__haystack, __accept); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t const *__NOTHROW_NCX(__LIBCCALL c16pbrk)(char16_t const *__haystack, char16_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16pbrk))(__haystack, __accept); }
}
#endif /* c16pbrk... */
#else /* __cplusplus && __CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcspbrk) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16pbrk,(char16_t const *__haystack, char16_t const *__accept),wcspbrk,(__haystack,__accept))
#elif defined(__CRT_HAVE_DOS$wcspbrk)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16pbrk,(char16_t const *__haystack, char16_t const *__accept),wcspbrk,(__haystack,__accept))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcspbrk.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16pbrk)(char16_t const *__haystack, char16_t const *__accept) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
#else /* LIBC: c16pbrk */
#include <local/wchar/c16pbrk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16pbrk, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16pbrk)(char16_t const *__haystack, char16_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16pbrk))(__haystack, __accept); })
#endif /* c16pbrk... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO)
#if defined(__CRT_HAVE_wcspbrk) && (__SIZEOF_WCHAR_T__ == 4)
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32pbrk,(char32_t *__haystack, char32_t const *__accept),wcspbrk,(__haystack, __accept))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,c32pbrk,(char32_t const *__haystack, char32_t const *__accept),wcspbrk,(__haystack, __accept))
}
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcspbrk.h>
extern "C++" {
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32pbrk)(char32_t *__haystack, char32_t const *__accept) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t const *__NOTHROW_NCX(__LIBCCALL c32pbrk)(char32_t const *__haystack, char32_t const *__accept) { return (char32_t const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
}
#else /* LIBC: c32pbrk */
#include <local/wchar/c32pbrk.h>
extern "C++" {
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32pbrk)(char32_t *__haystack, char32_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32pbrk))(__haystack, __accept); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t const *__NOTHROW_NCX(__LIBCCALL c32pbrk)(char32_t const *__haystack, char32_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32pbrk))(__haystack, __accept); }
}
#endif /* c32pbrk... */
#else /* __cplusplus && __CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcspbrk) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32pbrk,(char32_t const *__haystack, char32_t const *__accept),wcspbrk,(__haystack,__accept))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcspbrk.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32pbrk)(char32_t const *__haystack, char32_t const *__accept) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__accept); }
#else /* LIBC: c32pbrk */
#include <local/wchar/c32pbrk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32pbrk, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32pbrk)(char32_t const *__haystack, char32_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32pbrk))(__haystack, __accept); })
#endif /* c32pbrk... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#ifndef __c16tok_defined
#define __c16tok_defined 1
#if defined(__CRT_HAVE_wcstok) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2, 3)),char16_t *,__NOTHROW_NCX,c16tok,(char16_t *__string, char16_t const *__restrict __delim, char16_t **__restrict __save_ptr),wcstok,(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE_DOS$wcstok)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)),char16_t *,__NOTHROW_NCX,c16tok,(char16_t *__string, char16_t const *__restrict __delim, char16_t **__restrict __save_ptr),wcstok,(__string,__delim,__save_ptr))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcstok.h>
__FORCELOCAL __ATTR_NONNULL((2, 3)) char16_t *__NOTHROW_NCX(__LIBCCALL c16tok)(char16_t *__string, char16_t const *__restrict __delim, char16_t **__restrict __save_ptr) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstok))((__WCHAR_TYPE__ *)__string, (__WCHAR_TYPE__ const *)__delim, (__WCHAR_TYPE__ **)__save_ptr); }
#else /* LIBC: c16tok */
#include <local/wchar/c16tok.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16tok, __FORCELOCAL __ATTR_NONNULL((2, 3)) char16_t *__NOTHROW_NCX(__LIBCCALL c16tok)(char16_t *__string, char16_t const *__restrict __delim, char16_t **__restrict __save_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16tok))(__string, __delim, __save_ptr); })
#endif /* c16tok... */
#endif /* !__c16tok_defined */
#ifndef __c32tok_defined
#define __c32tok_defined 1
#if defined(__CRT_HAVE_wcstok) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2, 3)),char32_t *,__NOTHROW_NCX,c32tok,(char32_t *__string, char32_t const *__restrict __delim, char32_t **__restrict __save_ptr),wcstok,(__string,__delim,__save_ptr))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcstok.h>
__FORCELOCAL __ATTR_NONNULL((2, 3)) char32_t *__NOTHROW_NCX(__LIBCCALL c32tok)(char32_t *__string, char32_t const *__restrict __delim, char32_t **__restrict __save_ptr) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstok))((__WCHAR_TYPE__ *)__string, (__WCHAR_TYPE__ const *)__delim, (__WCHAR_TYPE__ **)__save_ptr); }
#else /* LIBC: c32tok */
#include <local/wchar/c32tok.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32tok, __FORCELOCAL __ATTR_NONNULL((2, 3)) char32_t *__NOTHROW_NCX(__LIBCCALL c32tok)(char32_t *__string, char32_t const *__restrict __delim, char32_t **__restrict __save_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32tok))(__string, __delim, __save_ptr); })
#endif /* c32tok... */
#endif /* !__c32tok_defined */
#if defined(__CRT_HAVE_wcssep) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16sep,(char16_t **__restrict __stringp, char16_t const *__restrict __delim),wcssep,(__stringp,__delim))
#elif defined(__CRT_HAVE_DOS$wcssep)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16sep,(char16_t **__restrict __stringp, char16_t const *__restrict __delim),wcssep,(__stringp,__delim))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcssep.h>
__FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16sep)(char16_t **__restrict __stringp, char16_t const *__restrict __delim) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcssep))((__WCHAR_TYPE__ **)__stringp, (__WCHAR_TYPE__ const *)__delim); }
#else /* LIBC: c16sep */
#include <local/wchar/c16sep.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sep, __FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16sep)(char16_t **__restrict __stringp, char16_t const *__restrict __delim) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sep))(__stringp, __delim); })
#endif /* c16sep... */
#if defined(__CRT_HAVE_wcssep) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32sep,(char32_t **__restrict __stringp, char32_t const *__restrict __delim),wcssep,(__stringp,__delim))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcssep.h>
__FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32sep)(char32_t **__restrict __stringp, char32_t const *__restrict __delim) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcssep))((__WCHAR_TYPE__ **)__stringp, (__WCHAR_TYPE__ const *)__delim); }
#else /* LIBC: c32sep */
#include <local/wchar/c32sep.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sep, __FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32sep)(char32_t **__restrict __stringp, char32_t const *__restrict __delim) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sep))(__stringp, __delim); })
#endif /* c32sep... */
#if defined(__CRT_HAVE_wcsdup) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16dup,(char16_t const *__restrict __string),wcsdup,(__string))
#elif defined(__CRT_HAVE__wcsdup) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16dup,(char16_t const *__restrict __string),_wcsdup,(__string))
#elif defined(__CRT_HAVE_DOS$_wcsdup)
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16dup,(char16_t const *__restrict __string),_wcsdup,(__string))
#elif defined(__CRT_HAVE_DOS$_wcsdup)
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16dup,(char16_t const *__restrict __string),_wcsdup,(__string))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsdup.h>
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16dup)(char16_t const *__restrict __string) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsdup))((__WCHAR_TYPE__ const *)__string); }
#else /* LIBC: c16dup */
#include <local/wchar/c16dup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16dup, __FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16dup)(char16_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16dup))(__string); })
#endif /* LIBC: c16dup */
#endif /* c16dup... */
#if defined(__CRT_HAVE_wcsdup) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32dup,(char32_t const *__restrict __string),wcsdup,(__string))
#elif defined(__CRT_HAVE__wcsdup) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32dup,(char32_t const *__restrict __string),_wcsdup,(__string))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsdup.h>
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32dup)(char32_t const *__restrict __string) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsdup))((__WCHAR_TYPE__ const *)__string); }
#else /* LIBC: c32dup */
#include <local/wchar/c32dup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32dup, __FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32dup)(char32_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32dup))(__string); })
#endif /* LIBC: c32dup */
#endif /* c32dup... */
#if defined(__CRT_HAVE_wcsndup) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16ndup,(char16_t const *__restrict __string, __SIZE_TYPE__ __max_chars),wcsndup,(__string,__max_chars))
#elif defined(__CRT_HAVE_DOS$wcsndup)
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16ndup,(char16_t const *__restrict __string, __SIZE_TYPE__ __max_chars),wcsndup,(__string,__max_chars))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsndup.h>
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16ndup)(char16_t const *__restrict __string, __SIZE_TYPE__ __max_chars) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsndup))((__WCHAR_TYPE__ const *)__string, __max_chars); }
#else /* LIBC: c16ndup */
#include <local/wchar/c16ndup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ndup, __FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16ndup)(char16_t const *__restrict __string, __SIZE_TYPE__ __max_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ndup))(__string, __max_chars); })
#endif /* LIBC: c16ndup */
#endif /* c16ndup... */
#if defined(__CRT_HAVE_wcsndup) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32ndup,(char32_t const *__restrict __string, __SIZE_TYPE__ __max_chars),wcsndup,(__string,__max_chars))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsndup.h>
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32ndup)(char32_t const *__restrict __string, __SIZE_TYPE__ __max_chars) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsndup))((__WCHAR_TYPE__ const *)__string, __max_chars); }
#else /* LIBC: c32ndup */
#include <local/wchar/c32ndup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ndup, __FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32ndup)(char32_t const *__restrict __string, __SIZE_TYPE__ __max_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ndup))(__string, __max_chars); })
#endif /* LIBC: c32ndup */
#endif /* c32ndup... */
#if defined(__CRT_HAVE_wcsfry) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16fry,(char16_t *__restrict __string),wcsfry,(__string))
#elif defined(__CRT_HAVE_DOS$wcsfry)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16fry,(char16_t *__restrict __string),wcsfry,(__string))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsfry.h>
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16fry)(char16_t *__restrict __string) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsfry))((__WCHAR_TYPE__ *)__string); }
#else /* LIBC: c16fry */
#include <local/wchar/c16fry.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16fry, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16fry)(char16_t *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16fry))(__string); })
#endif /* c16fry... */
#if defined(__CRT_HAVE_wcsfry) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32fry,(char32_t *__restrict __string),wcsfry,(__string))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsfry.h>
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32fry)(char32_t *__restrict __string) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsfry))((__WCHAR_TYPE__ *)__string); }
#else /* LIBC: c32fry */
#include <local/wchar/c32fry.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32fry, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32fry)(char32_t *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32fry))(__string); })
#endif /* c32fry... */
#if defined(__CRT_HAVE_wcscasecmp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecmp,(char16_t const *__s1, char16_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecmp,(char16_t const *__s1, char16_t const *__s2),wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecmp,(char16_t const *__s1, char16_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcsicmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecmp,(char16_t const *__s1, char16_t const *__s2),wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$_wcsicmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecmp,(char16_t const *__s1, char16_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscasecmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecmp,(char16_t const *__s1, char16_t const *__s2),wcscasecmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcscasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c16casecmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* LIBC: c16casecmp */
#include <local/wchar/c16casecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16casecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c16casecmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16casecmp))(__s1, __s2); })
#endif /* c16casecmp... */
#if defined(__CRT_HAVE_wcscasecmp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecmp,(char32_t const *__s1, char32_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecmp,(char32_t const *__s1, char32_t const *__s2),wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecmp,(char32_t const *__s1, char32_t const *__s2),_wcsicmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcscasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c32casecmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* LIBC: c32casecmp */
#include <local/wchar/c32casecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32casecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c32casecmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32casecmp))(__s1, __s2); })
#endif /* c32casecmp... */
#if defined(__CRT_HAVE_wcsncasecmp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecmp,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecmp,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecmp,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnicmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecmp,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$_wcsnicmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecmp,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsncasecmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecmp,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsncasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c16ncasecmp)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* LIBC: c16ncasecmp */
#include <local/wchar/c16ncasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ncasecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c16ncasecmp)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ncasecmp))(__s1, __s2, __maxlen); })
#endif /* c16ncasecmp... */
#if defined(__CRT_HAVE_wcsncasecmp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecmp,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecmp,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecmp,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsncasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c32ncasecmp)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* LIBC: c32ncasecmp */
#include <local/wchar/c32ncasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ncasecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c32ncasecmp)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ncasecmp))(__s1, __s2, __maxlen); })
#endif /* c32ncasecmp... */
#if defined(__CRT_HAVE_wcsxfrm) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,c16xfrm,(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen),wcsxfrm,(__dst,__src,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsxfrm)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,c16xfrm,(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen),wcsxfrm,(__dst,__src,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsxfrm.h>
__FORCELOCAL __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c16xfrm)(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __maxlen); }
#else /* LIBC: c16xfrm */
#include <local/wchar/c16xfrm.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16xfrm, __FORCELOCAL __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c16xfrm)(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16xfrm))(__dst, __src, __maxlen); })
#endif /* c16xfrm... */
#if defined(__CRT_HAVE_wcsxfrm) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,c32xfrm,(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __maxlen),wcsxfrm,(__dst,__src,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsxfrm.h>
__FORCELOCAL __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c32xfrm)(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __maxlen); }
#else /* LIBC: c32xfrm */
#include <local/wchar/c32xfrm.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32xfrm, __FORCELOCAL __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c32xfrm)(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32xfrm))(__dst, __src, __maxlen); })
#endif /* c32xfrm... */
#if defined(__CRT_HAVE_wcscoll) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16coll,(char16_t const *__s1, char16_t const *__s2),wcscoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcscmp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16coll,(char16_t const *__s1, char16_t const *__s2),wcscmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16coll,(char16_t const *__s1, char16_t const *__s2),wcscmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscoll)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16coll,(char16_t const *__s1, char16_t const *__s2),wcscoll,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcscoll.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c16coll)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* LIBC: c16coll */
#include <local/wchar/c16coll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16coll, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c16coll)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16coll))(__s1, __s2); })
#endif /* c16coll... */
#if defined(__CRT_HAVE_wcscoll) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32coll,(char32_t const *__s1, char32_t const *__s2),wcscoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcscmp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32coll,(char32_t const *__s1, char32_t const *__s2),wcscmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcscoll.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c32coll)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* LIBC: c32coll */
#include <local/wchar/c32coll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32coll, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c32coll)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32coll))(__s1, __s2); })
#endif /* c32coll... */
#if defined(__CRT_HAVE_wcsncoll) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsncmp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsncmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsncoll)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncoll,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsncoll.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c16ncoll)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* LIBC: c16ncoll */
#include <local/wchar/c16ncoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ncoll, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c16ncoll)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ncoll))(__s1, __s2, __maxlen); })
#endif /* c16ncoll... */
#if defined(__CRT_HAVE_wcsncoll) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsncmp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsncoll.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c32ncoll)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* LIBC: c32ncoll */
#include <local/wchar/c32ncoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ncoll, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c32ncoll)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ncoll))(__s1, __s2, __maxlen); })
#endif /* c32ncoll... */
#if defined(__CRT_HAVE_wcscasecoll) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll,(char16_t const *__s1, char16_t const *__s2),wcscasecoll,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicoll) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll,(char16_t const *__s1, char16_t const *__s2),_wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicoll) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll,(char16_t const *__s1, char16_t const *__s2),wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcscasecmp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll,(char16_t const *__s1, char16_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll,(char16_t const *__s1, char16_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll,(char16_t const *__s1, char16_t const *__s2),wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$_wcsicoll)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll,(char16_t const *__s1, char16_t const *__s2),_wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcsicoll)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll,(char16_t const *__s1, char16_t const *__s2),wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$_wcsicmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll,(char16_t const *__s1, char16_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcsicmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll,(char16_t const *__s1, char16_t const *__s2),wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscasecoll)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll,(char16_t const *__s1, char16_t const *__s2),wcscasecoll,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcscasecoll.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c16casecoll)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* LIBC: c16casecoll */
#include <local/wchar/c16casecoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16casecoll, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c16casecoll)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16casecoll))(__s1, __s2); })
#endif /* c16casecoll... */
#if defined(__CRT_HAVE_wcscasecoll) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecoll,(char32_t const *__s1, char32_t const *__s2),wcscasecoll,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicoll) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecoll,(char32_t const *__s1, char32_t const *__s2),_wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicoll) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecoll,(char32_t const *__s1, char32_t const *__s2),wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcscasecmp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecoll,(char32_t const *__s1, char32_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecoll,(char32_t const *__s1, char32_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecoll,(char32_t const *__s1, char32_t const *__s2),wcsicmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcscasecoll.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c32casecoll)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* LIBC: c32casecoll */
#include <local/wchar/c32casecoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32casecoll, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c32casecoll)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32casecoll))(__s1, __s2); })
#endif /* c32casecoll... */
#if defined(__CRT_HAVE_wcsncasecoll) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicoll) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsncasecmp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$_wcsnicoll)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$_wcsnicmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnicmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsncasecoll)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecoll,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsncasecoll.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c16ncasecoll)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* LIBC: c16ncasecoll */
#include <local/wchar/c16ncasecoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ncasecoll, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c16ncasecoll)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ncasecoll))(__s1, __s2, __maxlen); })
#endif /* c16ncasecoll... */
#if defined(__CRT_HAVE_wcsncasecoll) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicoll) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsncasecmp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsncasecoll.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c32ncasecoll)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen); }
#else /* LIBC: c32ncasecoll */
#include <local/wchar/c32ncasecoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ncasecoll, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c32ncasecoll)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ncasecoll))(__s1, __s2, __maxlen); })
#endif /* c32ncasecoll... */
#if defined(__CRT_HAVE_wcslwr) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16lwr,(char16_t *__restrict __str),wcslwr,(__str))
#elif defined(__CRT_HAVE__wcslwr) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16lwr,(char16_t *__restrict __str),_wcslwr,(__str))
#elif defined(__CRT_HAVE_DOS$_wcslwr)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16lwr,(char16_t *__restrict __str),_wcslwr,(__str))
#elif defined(__CRT_HAVE_DOS$wcslwr)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16lwr,(char16_t *__restrict __str),wcslwr,(__str))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcslwr.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16lwr)(char16_t *__restrict __str) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr))((__WCHAR_TYPE__ *)__str); }
#else /* LIBC: c16lwr */
#include <local/wchar/c16lwr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16lwr, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16lwr)(char16_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16lwr))(__str); })
#endif /* c16lwr... */
#if defined(__CRT_HAVE_wcslwr) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32lwr,(char32_t *__restrict __str),wcslwr,(__str))
#elif defined(__CRT_HAVE__wcslwr) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32lwr,(char32_t *__restrict __str),_wcslwr,(__str))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcslwr.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32lwr)(char32_t *__restrict __str) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr))((__WCHAR_TYPE__ *)__str); }
#else /* LIBC: c32lwr */
#include <local/wchar/c32lwr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32lwr, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32lwr)(char32_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32lwr))(__str); })
#endif /* c32lwr... */
#if defined(__CRT_HAVE_wcsupr) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16upr,(char16_t *__restrict __str),wcsupr,(__str))
#elif defined(__CRT_HAVE__wcsupr) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16upr,(char16_t *__restrict __str),_wcsupr,(__str))
#elif defined(__CRT_HAVE_DOS$_wcsupr)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16upr,(char16_t *__restrict __str),_wcsupr,(__str))
#elif defined(__CRT_HAVE_DOS$wcsupr)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16upr,(char16_t *__restrict __str),wcsupr,(__str))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsupr.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16upr)(char16_t *__restrict __str) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr))((__WCHAR_TYPE__ *)__str); }
#else /* LIBC: c16upr */
#include <local/wchar/c16upr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16upr, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16upr)(char16_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16upr))(__str); })
#endif /* c16upr... */
#if defined(__CRT_HAVE_wcsupr) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32upr,(char32_t *__restrict __str),wcsupr,(__str))
#elif defined(__CRT_HAVE__wcsupr) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32upr,(char32_t *__restrict __str),_wcsupr,(__str))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsupr.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32upr)(char32_t *__restrict __str) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr))((__WCHAR_TYPE__ *)__str); }
#else /* LIBC: c32upr */
#include <local/wchar/c32upr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32upr, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32upr)(char32_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32upr))(__str); })
#endif /* c32upr... */
#if defined(__CRT_HAVE_wcsrev) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16rev,(char16_t *__restrict __str),wcsrev,(__str))
#elif defined(__CRT_HAVE__wcsrev) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16rev,(char16_t *__restrict __str),_wcsrev,(__str))
#elif defined(__CRT_HAVE_DOS$_wcsrev)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16rev,(char16_t *__restrict __str),_wcsrev,(__str))
#elif defined(__CRT_HAVE_DOS$wcsrev)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16rev,(char16_t *__restrict __str),wcsrev,(__str))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsrev.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16rev)(char16_t *__restrict __str) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrev))((__WCHAR_TYPE__ *)__str); }
#else /* LIBC: c16rev */
#include <local/wchar/c16rev.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16rev, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16rev)(char16_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rev))(__str); })
#endif /* c16rev... */
#if defined(__CRT_HAVE_wcsrev) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32rev,(char32_t *__restrict __str),wcsrev,(__str))
#elif defined(__CRT_HAVE__wcsrev) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32rev,(char32_t *__restrict __str),_wcsrev,(__str))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsrev.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32rev)(char32_t *__restrict __str) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrev))((__WCHAR_TYPE__ *)__str); }
#else /* LIBC: c32rev */
#include <local/wchar/c32rev.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32rev, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32rev)(char32_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32rev))(__str); })
#endif /* c32rev... */
#if defined(__CRT_HAVE_wcsnrev) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nrev,(char16_t *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnrev,(__str,__maxlen))
#elif defined(__CRT_HAVE__wcsnrev) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nrev,(char16_t *__restrict __str, __SIZE_TYPE__ __maxlen),_wcsnrev,(__str,__maxlen))
#elif defined(__CRT_HAVE_DOS$_wcsnrev)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nrev,(char16_t *__restrict __str, __SIZE_TYPE__ __maxlen),_wcsnrev,(__str,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnrev)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nrev,(char16_t *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnrev,(__str,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsnrev.h>
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16nrev)(char16_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrev))((__WCHAR_TYPE__ *)__str, __maxlen); }
#else /* LIBC: c16nrev */
#include <local/wchar/c16nrev.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16nrev, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16nrev)(char16_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nrev))(__str, __maxlen); })
#endif /* c16nrev... */
#if defined(__CRT_HAVE_wcsnrev) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nrev,(char32_t *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnrev,(__str,__maxlen))
#elif defined(__CRT_HAVE__wcsnrev) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nrev,(char32_t *__restrict __str, __SIZE_TYPE__ __maxlen),_wcsnrev,(__str,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsnrev.h>
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32nrev)(char32_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrev))((__WCHAR_TYPE__ *)__str, __maxlen); }
#else /* LIBC: c32nrev */
#include <local/wchar/c32nrev.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32nrev, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32nrev)(char32_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nrev))(__str, __maxlen); })
#endif /* c32nrev... */
#if defined(__CRT_HAVE_wcsset) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16set,(char16_t *__restrict __str, char16_t __ch),wcsset,(__str,__ch))
#elif defined(__CRT_HAVE__wcsset) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16set,(char16_t *__restrict __str, char16_t __ch),_wcsset,(__str,__ch))
#elif defined(__CRT_HAVE_DOS$_wcsset)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16set,(char16_t *__restrict __str, char16_t __ch),_wcsset,(__str,__ch))
#elif defined(__CRT_HAVE_DOS$wcsset)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16set,(char16_t *__restrict __str, char16_t __ch),wcsset,(__str,__ch))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsset.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16set)(char16_t *__restrict __str, char16_t __ch) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsset))((__WCHAR_TYPE__ *)__str, (__WCHAR_TYPE__)__ch); }
#else /* LIBC: c16set */
#include <local/wchar/c16set.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16set, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16set)(char16_t *__restrict __str, char16_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16set))(__str, __ch); })
#endif /* c16set... */
#if defined(__CRT_HAVE_wcsset) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32set,(char32_t *__restrict __str, char32_t __ch),wcsset,(__str,__ch))
#elif defined(__CRT_HAVE__wcsset) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32set,(char32_t *__restrict __str, char32_t __ch),_wcsset,(__str,__ch))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsset.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32set)(char32_t *__restrict __str, char32_t __ch) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsset))((__WCHAR_TYPE__ *)__str, (__WCHAR_TYPE__)__ch); }
#else /* LIBC: c32set */
#include <local/wchar/c32set.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32set, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32set)(char32_t *__restrict __str, char32_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32set))(__str, __ch); })
#endif /* c32set... */
#if defined(__CRT_HAVE_wcsnset) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nset,(char16_t *__restrict __str, char16_t __ch, __SIZE_TYPE__ __maxlen),wcsnset,(__str,__ch,__maxlen))
#elif defined(__CRT_HAVE__wcsnset) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nset,(char16_t *__restrict __str, char16_t __ch, __SIZE_TYPE__ __maxlen),_wcsnset,(__str,__ch,__maxlen))
#elif defined(__CRT_HAVE_DOS$_wcsnset)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nset,(char16_t *__restrict __str, char16_t __ch, __SIZE_TYPE__ __maxlen),_wcsnset,(__str,__ch,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnset)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16nset,(char16_t *__restrict __str, char16_t __ch, __SIZE_TYPE__ __maxlen),wcsnset,(__str,__ch,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsnset.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16nset)(char16_t *__restrict __str, char16_t __ch, __SIZE_TYPE__ __maxlen) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnset))((__WCHAR_TYPE__ *)__str, (__WCHAR_TYPE__)__ch, __maxlen); }
#else /* LIBC: c16nset */
#include <local/wchar/c16nset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16nset, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16nset)(char16_t *__restrict __str, char16_t __ch, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nset))(__str, __ch, __maxlen); })
#endif /* c16nset... */
#if defined(__CRT_HAVE_wcsnset) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nset,(char32_t *__restrict __str, char32_t __ch, __SIZE_TYPE__ __maxlen),wcsnset,(__str,__ch,__maxlen))
#elif defined(__CRT_HAVE__wcsnset) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32nset,(char32_t *__restrict __str, char32_t __ch, __SIZE_TYPE__ __maxlen),_wcsnset,(__str,__ch,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsnset.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32nset)(char32_t *__restrict __str, char32_t __ch, __SIZE_TYPE__ __maxlen) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnset))((__WCHAR_TYPE__ *)__str, (__WCHAR_TYPE__)__ch, __maxlen); }
#else /* LIBC: c32nset */
#include <local/wchar/c32nset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32nset, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32nset)(char32_t *__restrict __str, char32_t __ch, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nset))(__str, __ch, __maxlen); })
#endif /* c32nset... */
#if defined(__CRT_HAVE_fuzzy_wmemcmp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16memcmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_chars, char16_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_wmemcmp,(__s1,__s1_chars,__s2,__s2_chars))
#elif defined(__CRT_HAVE_DOS$fuzzy_wmemcmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16memcmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_chars, char16_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_wmemcmp,(__s1,__s1_chars,__s2,__s2_chars))
#elif !defined(__NO_MALLOCA)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/fuzzy_wmemcmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c16memcmp)(char16_t const *__s1, __SIZE_TYPE__ __s1_chars, char16_t const *__s2, __SIZE_TYPE__ __s2_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcmp))((__WCHAR_TYPE__ const *)__s1, __s1_chars, (__WCHAR_TYPE__ const *)__s2, __s2_chars); }
#else /* LIBC: fuzzy_c16memcmp */
#include <local/wchar/fuzzy_c16memcmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16memcmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c16memcmp)(char16_t const *__s1, __SIZE_TYPE__ __s1_chars, char16_t const *__s2, __SIZE_TYPE__ __s2_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16memcmp))(__s1, __s1_chars, __s2, __s2_chars); })
#endif /* LIBC: fuzzy_c16memcmp */
#endif /* fuzzy_c16memcmp... */
#if defined(__CRT_HAVE_fuzzy_wmemcmp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32memcmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_chars, char32_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_wmemcmp,(__s1,__s1_chars,__s2,__s2_chars))
#elif !defined(__NO_MALLOCA)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/fuzzy_wmemcmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c32memcmp)(char32_t const *__s1, __SIZE_TYPE__ __s1_chars, char32_t const *__s2, __SIZE_TYPE__ __s2_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcmp))((__WCHAR_TYPE__ const *)__s1, __s1_chars, (__WCHAR_TYPE__ const *)__s2, __s2_chars); }
#else /* LIBC: fuzzy_c32memcmp */
#include <local/wchar/fuzzy_c32memcmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32memcmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c32memcmp)(char32_t const *__s1, __SIZE_TYPE__ __s1_chars, char32_t const *__s2, __SIZE_TYPE__ __s2_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32memcmp))(__s1, __s1_chars, __s2, __s2_chars); })
#endif /* LIBC: fuzzy_c32memcmp */
#endif /* fuzzy_c32memcmp... */
#if defined(__CRT_HAVE_fuzzy_wmemcasecmp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16memcasecmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes),fuzzy_wmemcasecmp,(__s1,__s1_bytes,__s2,__s2_bytes))
#elif defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16memcasecmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes),fuzzy_wmemcasecmp,(__s1,__s1_bytes,__s2,__s2_bytes))
#elif !defined(__NO_MALLOCA)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/fuzzy_wmemcasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c16memcasecmp)(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcasecmp))((__WCHAR_TYPE__ const *)__s1, __s1_bytes, (__WCHAR_TYPE__ const *)__s2, __s2_bytes); }
#else /* LIBC: fuzzy_c16memcasecmp */
#include <local/wchar/fuzzy_c16memcasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16memcasecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c16memcasecmp)(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16memcasecmp))(__s1, __s1_bytes, __s2, __s2_bytes); })
#endif /* LIBC: fuzzy_c16memcasecmp */
#endif /* fuzzy_c16memcasecmp... */
#if defined(__CRT_HAVE_fuzzy_wmemcasecmp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32memcasecmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_bytes, char32_t const *__s2, __SIZE_TYPE__ __s2_bytes),fuzzy_wmemcasecmp,(__s1,__s1_bytes,__s2,__s2_bytes))
#elif !defined(__NO_MALLOCA)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/fuzzy_wmemcasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c32memcasecmp)(char32_t const *__s1, __SIZE_TYPE__ __s1_bytes, char32_t const *__s2, __SIZE_TYPE__ __s2_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcasecmp))((__WCHAR_TYPE__ const *)__s1, __s1_bytes, (__WCHAR_TYPE__ const *)__s2, __s2_bytes); }
#else /* LIBC: fuzzy_c32memcasecmp */
#include <local/wchar/fuzzy_c32memcasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32memcasecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c32memcasecmp)(char32_t const *__s1, __SIZE_TYPE__ __s1_bytes, char32_t const *__s2, __SIZE_TYPE__ __s2_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32memcasecmp))(__s1, __s1_bytes, __s2, __s2_bytes); })
#endif /* LIBC: fuzzy_c32memcasecmp */
#endif /* fuzzy_c32memcasecmp... */
#if defined(__CRT_HAVE_fuzzy_wcscmp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16cmp,(char16_t const *__s1, char16_t const *__s2),fuzzy_wcscmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$fuzzy_wcscmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16cmp,(char16_t const *__s1, char16_t const *__s2),fuzzy_wcscmp,(__s1,__s2))
#elif !defined(__NO_MALLOCA) || defined(__CRT_HAVE_fuzzy_wmemcmp)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/fuzzy_wcscmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c16cmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* LIBC: fuzzy_c16cmp */
#include <local/wchar/fuzzy_c16cmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16cmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c16cmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16cmp))(__s1, __s2); })
#endif /* LIBC: fuzzy_c16cmp */
#endif /* fuzzy_c16cmp... */
#if defined(__CRT_HAVE_fuzzy_wcscmp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32cmp,(char32_t const *__s1, char32_t const *__s2),fuzzy_wcscmp,(__s1,__s2))
#elif !defined(__NO_MALLOCA) || defined(__CRT_HAVE_fuzzy_wmemcmp)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/fuzzy_wcscmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c32cmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* LIBC: fuzzy_c32cmp */
#include <local/wchar/fuzzy_c32cmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32cmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c32cmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32cmp))(__s1, __s2); })
#endif /* LIBC: fuzzy_c32cmp */
#endif /* fuzzy_c32cmp... */
#if defined(__CRT_HAVE_fuzzy_wcsncmp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16ncmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen),fuzzy_wcsncmp,(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif defined(__CRT_HAVE_DOS$fuzzy_wcsncmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16ncmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen),fuzzy_wcsncmp,(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif !defined(__NO_MALLOCA) || defined(__CRT_HAVE_fuzzy_wmemcmp)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/fuzzy_wcsncmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c16ncmp)(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncmp))((__WCHAR_TYPE__ const *)__s1, __s1_maxlen, (__WCHAR_TYPE__ const *)__s2, __s2_maxlen); }
#else /* LIBC: fuzzy_c16ncmp */
#include <local/wchar/fuzzy_c16ncmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16ncmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c16ncmp)(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16ncmp))(__s1, __s1_maxlen, __s2, __s2_maxlen); })
#endif /* LIBC: fuzzy_c16ncmp */
#endif /* fuzzy_c16ncmp... */
#if defined(__CRT_HAVE_fuzzy_wcsncmp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32ncmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen),fuzzy_wcsncmp,(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif !defined(__NO_MALLOCA) || defined(__CRT_HAVE_fuzzy_wmemcmp)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/fuzzy_wcsncmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c32ncmp)(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncmp))((__WCHAR_TYPE__ const *)__s1, __s1_maxlen, (__WCHAR_TYPE__ const *)__s2, __s2_maxlen); }
#else /* LIBC: fuzzy_c32ncmp */
#include <local/wchar/fuzzy_c32ncmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32ncmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c32ncmp)(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32ncmp))(__s1, __s1_maxlen, __s2, __s2_maxlen); })
#endif /* LIBC: fuzzy_c32ncmp */
#endif /* fuzzy_c32ncmp... */
#if defined(__CRT_HAVE_fuzzy_wcscasecmp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16casecmp,(char16_t const *__s1, char16_t const *__s2),fuzzy_wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$fuzzy_wcscasecmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16casecmp,(char16_t const *__s1, char16_t const *__s2),fuzzy_wcscasecmp,(__s1,__s2))
#elif !defined(__NO_MALLOCA) || defined(__CRT_HAVE_fuzzy_wmemcasecmp)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/fuzzy_wcscasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c16casecmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscasecmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* LIBC: fuzzy_c16casecmp */
#include <local/wchar/fuzzy_c16casecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16casecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c16casecmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16casecmp))(__s1, __s2); })
#endif /* LIBC: fuzzy_c16casecmp */
#endif /* fuzzy_c16casecmp... */
#if defined(__CRT_HAVE_fuzzy_wcscasecmp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32casecmp,(char32_t const *__s1, char32_t const *__s2),fuzzy_wcscasecmp,(__s1,__s2))
#elif !defined(__NO_MALLOCA) || defined(__CRT_HAVE_fuzzy_wmemcasecmp)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/fuzzy_wcscasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c32casecmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscasecmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* LIBC: fuzzy_c32casecmp */
#include <local/wchar/fuzzy_c32casecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32casecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c32casecmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32casecmp))(__s1, __s2); })
#endif /* LIBC: fuzzy_c32casecmp */
#endif /* fuzzy_c32casecmp... */
#if defined(__CRT_HAVE_fuzzy_wcsncasecmp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16ncasecmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen),fuzzy_wcsncasecmp,(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif defined(__CRT_HAVE_DOS$fuzzy_wcsncasecmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16ncasecmp,(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen),fuzzy_wcsncasecmp,(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif !defined(__NO_MALLOCA) || defined(__CRT_HAVE_fuzzy_wmemcasecmp)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/fuzzy_wcsncasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c16ncasecmp)(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncasecmp))((__WCHAR_TYPE__ const *)__s1, __s1_maxlen, (__WCHAR_TYPE__ const *)__s2, __s2_maxlen); }
#else /* LIBC: fuzzy_c16ncasecmp */
#include <local/wchar/fuzzy_c16ncasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16ncasecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c16ncasecmp)(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16ncasecmp))(__s1, __s1_maxlen, __s2, __s2_maxlen); })
#endif /* LIBC: fuzzy_c16ncasecmp */
#endif /* fuzzy_c16ncasecmp... */
#if defined(__CRT_HAVE_fuzzy_wcsncasecmp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32ncasecmp,(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen),fuzzy_wcsncasecmp,(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif !defined(__NO_MALLOCA) || defined(__CRT_HAVE_fuzzy_wmemcasecmp)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/fuzzy_wcsncasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c32ncasecmp)(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncasecmp))((__WCHAR_TYPE__ const *)__s1, __s1_maxlen, (__WCHAR_TYPE__ const *)__s2, __s2_maxlen); }
#else /* LIBC: fuzzy_c32ncasecmp */
#include <local/wchar/fuzzy_c32ncasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32ncasecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c32ncasecmp)(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32ncasecmp))(__s1, __s1_maxlen, __s2, __s2_maxlen); })
#endif /* LIBC: fuzzy_c32ncasecmp */
#endif /* fuzzy_c32ncasecmp... */
#if defined(__CRT_HAVE_wildwcscmp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildc16cmp,(char16_t const *__pattern, char16_t const *__string),wildwcscmp,(__pattern,__string))
#elif defined(__CRT_HAVE_DOS$wildwcscmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildc16cmp,(char16_t const *__pattern, char16_t const *__string),wildwcscmp,(__pattern,__string))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wildwcscmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wildc16cmp)(char16_t const *__pattern, char16_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscmp))((__WCHAR_TYPE__ const *)__pattern, (__WCHAR_TYPE__ const *)__string); }
#else /* LIBC: wildc16cmp */
#include <local/wchar/wildc16cmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildc16cmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wildc16cmp)(char16_t const *__pattern, char16_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildc16cmp))(__pattern, __string); })
#endif /* wildc16cmp... */
#if defined(__CRT_HAVE_wildwcscmp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildc32cmp,(char32_t const *__pattern, char32_t const *__string),wildwcscmp,(__pattern,__string))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wildwcscmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wildc32cmp)(char32_t const *__pattern, char32_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscmp))((__WCHAR_TYPE__ const *)__pattern, (__WCHAR_TYPE__ const *)__string); }
#else /* LIBC: wildc32cmp */
#include <local/wchar/wildc32cmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildc32cmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wildc32cmp)(char32_t const *__pattern, char32_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildc32cmp))(__pattern, __string); })
#endif /* wildc32cmp... */
#if defined(__CRT_HAVE_wildwcscasecmp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildc16casecmp,(char16_t const *__pattern, char16_t const *__string),wildwcscasecmp,(__pattern,__string))
#elif defined(__CRT_HAVE_DOS$wildwcscasecmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildc16casecmp,(char16_t const *__pattern, char16_t const *__string),wildwcscasecmp,(__pattern,__string))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wildwcscasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wildc16casecmp)(char16_t const *__pattern, char16_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscasecmp))((__WCHAR_TYPE__ const *)__pattern, (__WCHAR_TYPE__ const *)__string); }
#else /* LIBC: wildc16casecmp */
#include <local/wchar/wildc16casecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildc16casecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wildc16casecmp)(char16_t const *__pattern, char16_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildc16casecmp))(__pattern, __string); })
#endif /* wildc16casecmp... */
#if defined(__CRT_HAVE_wildwcscasecmp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildc32casecmp,(char32_t const *__pattern, char32_t const *__string),wildwcscasecmp,(__pattern,__string))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wildwcscasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wildc32casecmp)(char32_t const *__pattern, char32_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscasecmp))((__WCHAR_TYPE__ const *)__pattern, (__WCHAR_TYPE__ const *)__string); }
#else /* LIBC: wildc32casecmp */
#include <local/wchar/wildc32casecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildc32casecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wildc32casecmp)(char32_t const *__pattern, char32_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildc32casecmp))(__pattern, __string); })
#endif /* wildc32casecmp... */
#if defined(__CRT_HAVE_wcsverscmp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16verscmp,(char16_t const *__s1, char16_t const *__s2),wcsverscmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcsverscmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16verscmp,(char16_t const *__s1, char16_t const *__s2),wcsverscmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsverscmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c16verscmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsverscmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* LIBC: c16verscmp */
#include <local/wchar/c16verscmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16verscmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c16verscmp)(char16_t const *__s1, char16_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16verscmp))(__s1, __s2); })
#endif /* c16verscmp... */
#if defined(__CRT_HAVE_wcsverscmp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32verscmp,(char32_t const *__s1, char32_t const *__s2),wcsverscmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsverscmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c32verscmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsverscmp))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2); }
#else /* LIBC: c32verscmp */
#include <local/wchar/c32verscmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32verscmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c32verscmp)(char32_t const *__s1, char32_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32verscmp))(__s1, __s2); })
#endif /* c32verscmp... */
#ifdef __USE_XOPEN2K8
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO)
#if defined(__CRT_HAVE_wcscasestr_l) && (__SIZEOF_WCHAR_T__ == 2)
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr_l,(char16_t *__haystack, char16_t *__needle, __locale_t __locale),wcscasestr_l,(__haystack, __needle, __locale))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16casestr_l,(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale),wcscasestr_l,(__haystack, __needle, __locale))
}
#elif defined(__CRT_HAVE_wcsistr_l) && (__SIZEOF_WCHAR_T__ == 2)
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr_l,(char16_t *__haystack, char16_t *__needle, __locale_t __locale),wcsistr_l,(__haystack, __needle, __locale))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16casestr_l,(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale),wcsistr_l,(__haystack, __needle, __locale))
}
#elif defined(__CRT_HAVE__wcsistr_l) && (__SIZEOF_WCHAR_T__ == 2)
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr_l,(char16_t *__haystack, char16_t *__needle, __locale_t __locale),_wcsistr_l,(__haystack, __needle, __locale))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16casestr_l,(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale),_wcsistr_l,(__haystack, __needle, __locale))
}
#elif defined(__CRT_HAVE_wcscasewcs_l) && (__SIZEOF_WCHAR_T__ == 2)
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr_l,(char16_t *__haystack, char16_t *__needle, __locale_t __locale),wcscasewcs_l,(__haystack, __needle, __locale))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16casestr_l,(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale),wcscasewcs_l,(__haystack, __needle, __locale))
}
#elif defined(__CRT_HAVE_wcsiwcs_l) && (__SIZEOF_WCHAR_T__ == 2)
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr_l,(char16_t *__haystack, char16_t *__needle, __locale_t __locale),wcsiwcs_l,(__haystack, __needle, __locale))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16casestr_l,(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale),wcsiwcs_l,(__haystack, __needle, __locale))
}
#elif defined(__CRT_HAVE__wcsiwcs_l) && (__SIZEOF_WCHAR_T__ == 2)
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr_l,(char16_t *__haystack, char16_t *__needle, __locale_t __locale),_wcsiwcs_l,(__haystack, __needle, __locale))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16casestr_l,(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale),_wcsiwcs_l,(__haystack, __needle, __locale))
}
#elif defined(__CRT_HAVE_DOS$wcsistr_l)
extern "C++" {
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr_l,(char16_t *__haystack, char16_t *__needle, __locale_t __locale),wcsistr_l,(__haystack, __needle, __locale))
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16casestr_l,(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale),wcsistr_l,(__haystack, __needle, __locale))
}
#elif defined(__CRT_HAVE_DOS$wcsiwcs_l)
extern "C++" {
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr_l,(char16_t *__haystack, char16_t *__needle, __locale_t __locale),wcsiwcs_l,(__haystack, __needle, __locale))
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16casestr_l,(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale),wcsiwcs_l,(__haystack, __needle, __locale))
}
#elif defined(__CRT_HAVE_DOS$_wcsistr_l)
extern "C++" {
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr_l,(char16_t *__haystack, char16_t *__needle, __locale_t __locale),_wcsistr_l,(__haystack, __needle, __locale))
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16casestr_l,(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale),_wcsistr_l,(__haystack, __needle, __locale))
}
#elif defined(__CRT_HAVE_DOS$_wcsiwcs_l)
extern "C++" {
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr_l,(char16_t *__haystack, char16_t *__needle, __locale_t __locale),_wcsiwcs_l,(__haystack, __needle, __locale))
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16casestr_l,(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale),_wcsiwcs_l,(__haystack, __needle, __locale))
}
#elif defined(__CRT_HAVE_DOS$wcscasestr_l)
extern "C++" {
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr_l,(char16_t *__haystack, char16_t *__needle, __locale_t __locale),wcscasestr_l,(__haystack, __needle, __locale))
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t const *,__NOTHROW_NCX,c16casestr_l,(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale),wcscasestr_l,(__haystack, __needle, __locale))
}
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcscasestr_l.h>
extern "C++" {
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16casestr_l)(char16_t *__haystack, char16_t *__needle, __locale_t __locale) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr_l))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle, __locale); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t const *__NOTHROW_NCX(__LIBCCALL c16casestr_l)(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale) { return (char16_t const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr_l))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle, __locale); }
}
#else /* LIBC: c16casestr_l */
#include <local/wchar/c16casestr_l.h>
extern "C++" {
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16casestr_l)(char16_t *__haystack, char16_t *__needle, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16casestr_l))(__haystack, __needle, __locale); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t const *__NOTHROW_NCX(__LIBCCALL c16casestr_l)(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16casestr_l))(__haystack, __needle, __locale); }
}
#endif /* c16casestr_l... */
#else /* __cplusplus && __CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcscasestr_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr_l,(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale),wcscasestr_l,(__haystack,__needle,__locale))
#elif defined(__CRT_HAVE_wcsistr_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr_l,(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale),wcsistr_l,(__haystack,__needle,__locale))
#elif defined(__CRT_HAVE__wcsistr_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr_l,(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale),_wcsistr_l,(__haystack,__needle,__locale))
#elif defined(__CRT_HAVE_wcscasewcs_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr_l,(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale),wcscasewcs_l,(__haystack,__needle,__locale))
#elif defined(__CRT_HAVE_wcsiwcs_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr_l,(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale),wcsiwcs_l,(__haystack,__needle,__locale))
#elif defined(__CRT_HAVE__wcsiwcs_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr_l,(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale),_wcsiwcs_l,(__haystack,__needle,__locale))
#elif defined(__CRT_HAVE_DOS$wcsistr_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr_l,(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale),wcsistr_l,(__haystack,__needle,__locale))
#elif defined(__CRT_HAVE_DOS$wcsiwcs_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr_l,(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale),wcsiwcs_l,(__haystack,__needle,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsistr_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr_l,(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale),_wcsistr_l,(__haystack,__needle,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsiwcs_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr_l,(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale),_wcsiwcs_l,(__haystack,__needle,__locale))
#elif defined(__CRT_HAVE_DOS$wcscasestr_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char16_t *,__NOTHROW_NCX,c16casestr_l,(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale),wcscasestr_l,(__haystack,__needle,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcscasestr_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16casestr_l)(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr_l))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle, __locale); }
#else /* LIBC: c16casestr_l */
#include <local/wchar/c16casestr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16casestr_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char16_t *__NOTHROW_NCX(__LIBCCALL c16casestr_l)(char16_t const *__haystack, char16_t const *__needle, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16casestr_l))(__haystack, __needle, __locale); })
#endif /* c16casestr_l... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO)
#if defined(__CRT_HAVE_wcscasestr_l) && (__SIZEOF_WCHAR_T__ == 4)
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32casestr_l,(char32_t *__haystack, char32_t *__needle, __locale_t __locale),wcscasestr_l,(__haystack, __needle, __locale))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,c32casestr_l,(char32_t const *__haystack, char32_t const *__needle, __locale_t __locale),wcscasestr_l,(__haystack, __needle, __locale))
}
#elif defined(__CRT_HAVE_wcsistr_l) && (__SIZEOF_WCHAR_T__ == 4)
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32casestr_l,(char32_t *__haystack, char32_t *__needle, __locale_t __locale),wcsistr_l,(__haystack, __needle, __locale))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,c32casestr_l,(char32_t const *__haystack, char32_t const *__needle, __locale_t __locale),wcsistr_l,(__haystack, __needle, __locale))
}
#elif defined(__CRT_HAVE__wcsistr_l) && (__SIZEOF_WCHAR_T__ == 4)
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32casestr_l,(char32_t *__haystack, char32_t *__needle, __locale_t __locale),_wcsistr_l,(__haystack, __needle, __locale))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,c32casestr_l,(char32_t const *__haystack, char32_t const *__needle, __locale_t __locale),_wcsistr_l,(__haystack, __needle, __locale))
}
#elif defined(__CRT_HAVE_wcscasewcs_l) && (__SIZEOF_WCHAR_T__ == 4)
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32casestr_l,(char32_t *__haystack, char32_t *__needle, __locale_t __locale),wcscasewcs_l,(__haystack, __needle, __locale))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,c32casestr_l,(char32_t const *__haystack, char32_t const *__needle, __locale_t __locale),wcscasewcs_l,(__haystack, __needle, __locale))
}
#elif defined(__CRT_HAVE_wcsiwcs_l) && (__SIZEOF_WCHAR_T__ == 4)
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32casestr_l,(char32_t *__haystack, char32_t *__needle, __locale_t __locale),wcsiwcs_l,(__haystack, __needle, __locale))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,c32casestr_l,(char32_t const *__haystack, char32_t const *__needle, __locale_t __locale),wcsiwcs_l,(__haystack, __needle, __locale))
}
#elif defined(__CRT_HAVE__wcsiwcs_l) && (__SIZEOF_WCHAR_T__ == 4)
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32casestr_l,(char32_t *__haystack, char32_t *__needle, __locale_t __locale),_wcsiwcs_l,(__haystack, __needle, __locale))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t const *,__NOTHROW_NCX,c32casestr_l,(char32_t const *__haystack, char32_t const *__needle, __locale_t __locale),_wcsiwcs_l,(__haystack, __needle, __locale))
}
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcscasestr_l.h>
extern "C++" {
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32casestr_l)(char32_t *__haystack, char32_t *__needle, __locale_t __locale) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr_l))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle, __locale); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t const *__NOTHROW_NCX(__LIBCCALL c32casestr_l)(char32_t const *__haystack, char32_t const *__needle, __locale_t __locale) { return (char32_t const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr_l))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle, __locale); }
}
#else /* LIBC: c32casestr_l */
#include <local/wchar/c32casestr_l.h>
extern "C++" {
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32casestr_l)(char32_t *__haystack, char32_t *__needle, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32casestr_l))(__haystack, __needle, __locale); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t const *__NOTHROW_NCX(__LIBCCALL c32casestr_l)(char32_t const *__haystack, char32_t const *__needle, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32casestr_l))(__haystack, __needle, __locale); }
}
#endif /* c32casestr_l... */
#else /* __cplusplus && __CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcscasestr_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32casestr_l,(char32_t const *__haystack, char32_t const *__needle, __locale_t __locale),wcscasestr_l,(__haystack,__needle,__locale))
#elif defined(__CRT_HAVE_wcsistr_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32casestr_l,(char32_t const *__haystack, char32_t const *__needle, __locale_t __locale),wcsistr_l,(__haystack,__needle,__locale))
#elif defined(__CRT_HAVE__wcsistr_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32casestr_l,(char32_t const *__haystack, char32_t const *__needle, __locale_t __locale),_wcsistr_l,(__haystack,__needle,__locale))
#elif defined(__CRT_HAVE_wcscasewcs_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32casestr_l,(char32_t const *__haystack, char32_t const *__needle, __locale_t __locale),wcscasewcs_l,(__haystack,__needle,__locale))
#elif defined(__CRT_HAVE_wcsiwcs_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32casestr_l,(char32_t const *__haystack, char32_t const *__needle, __locale_t __locale),wcsiwcs_l,(__haystack,__needle,__locale))
#elif defined(__CRT_HAVE__wcsiwcs_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char32_t *,__NOTHROW_NCX,c32casestr_l,(char32_t const *__haystack, char32_t const *__needle, __locale_t __locale),_wcsiwcs_l,(__haystack,__needle,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcscasestr_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32casestr_l)(char32_t const *__haystack, char32_t const *__needle, __locale_t __locale) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr_l))((__WCHAR_TYPE__ const *)__haystack, (__WCHAR_TYPE__ const *)__needle, __locale); }
#else /* LIBC: c32casestr_l */
#include <local/wchar/c32casestr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32casestr_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char32_t *__NOTHROW_NCX(__LIBCCALL c32casestr_l)(char32_t const *__haystack, char32_t const *__needle, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32casestr_l))(__haystack, __needle, __locale); })
#endif /* c32casestr_l... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_PARTS_UCHAR_STRING_H_PROTO */
#if defined(__CRT_HAVE_wcscasecmp_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcsicmp_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$wcsicmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsicmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$wcscasecmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$__wcscasecmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),__wcscasecmp_l,(__s1,__s2,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcscasecmp_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c16casecmp_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#else /* LIBC: c16casecmp_l */
#include <local/wchar/c16casecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16casecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c16casecmp_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16casecmp_l))(__s1, __s2, __locale); })
#endif /* c16casecmp_l... */
#if defined(__CRT_HAVE_wcscasecmp_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcsicmp_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcscasecmp_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c32casecmp_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#else /* LIBC: c32casecmp_l */
#include <local/wchar/c32casecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32casecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c32casecmp_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32casecmp_l))(__s1, __s2, __locale); })
#endif /* c32casecmp_l... */
#if defined(__CRT_HAVE_wcsncasecmp_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecmp_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_wcsnicmp_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecmp_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicmp_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecmp_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$wcsnicmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecmp_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsnicmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecmp_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$wcsncasecmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecmp_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$__wcsncasecmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecmp_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsncasecmp_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c16ncasecmp_l)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen, __locale); }
#else /* LIBC: c16ncasecmp_l */
#include <local/wchar/c16ncasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ncasecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c16ncasecmp_l)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ncasecmp_l))(__s1, __s2, __maxlen, __locale); })
#endif /* c16ncasecmp_l... */
#if defined(__CRT_HAVE_wcsncasecmp_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecmp_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_wcsnicmp_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecmp_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicmp_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecmp_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsncasecmp_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c32ncasecmp_l)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen, __locale); }
#else /* LIBC: c32ncasecmp_l */
#include <local/wchar/c32ncasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ncasecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c32ncasecmp_l)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ncasecmp_l))(__s1, __s2, __maxlen, __locale); })
#endif /* c32ncasecmp_l... */
#if defined(__CRT_HAVE_wcsxfrm_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,c16xfrm_l,(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsxfrm_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,c16xfrm_l,(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsxfrm_l)
__CREDIRECT_DOS(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,c16xfrm_l,(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$wcsxfrm_l)
__CREDIRECT_DOS(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,c16xfrm_l,(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$__wcsxfrm_l)
__CREDIRECT_DOS(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,c16xfrm_l,(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsxfrm_l.h>
__FORCELOCAL __ATTR_NONNULL((2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c16xfrm_l)(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm_l))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __maxlen, __locale); }
#else /* LIBC: c16xfrm_l */
#include <local/wchar/c16xfrm_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16xfrm_l, __FORCELOCAL __ATTR_NONNULL((2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c16xfrm_l)(char16_t *__dst, char16_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16xfrm_l))(__dst, __src, __maxlen, __locale); })
#endif /* c16xfrm_l... */
#if defined(__CRT_HAVE_wcsxfrm_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,c32xfrm_l,(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsxfrm_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,c32xfrm_l,(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsxfrm_l.h>
__FORCELOCAL __ATTR_NONNULL((2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c32xfrm_l)(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm_l))((__WCHAR_TYPE__ *)__dst, (__WCHAR_TYPE__ const *)__src, __maxlen, __locale); }
#else /* LIBC: c32xfrm_l */
#include <local/wchar/c32xfrm_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32xfrm_l, __FORCELOCAL __ATTR_NONNULL((2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL c32xfrm_l)(char32_t *__dst, char32_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32xfrm_l))(__dst, __src, __maxlen, __locale); })
#endif /* c32xfrm_l... */
#if defined(__CRT_HAVE_wcscoll_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16coll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcscoll_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16coll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcscmp_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16coll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcscmp_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16coll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcscmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$_wcscoll_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16coll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$_wcscmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16coll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcscmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$wcscoll_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16coll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$__wcscoll_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16coll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),__wcscoll_l,(__s1,__s2,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcscoll_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c16coll_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#else /* LIBC: c16coll_l */
#include <local/wchar/c16coll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16coll_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c16coll_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16coll_l))(__s1, __s2, __locale); })
#endif /* c16coll_l... */
#if defined(__CRT_HAVE_wcscoll_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32coll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcscoll_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32coll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),_wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcscmp_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32coll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcscmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcscmp_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32coll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),_wcscmp_l,(__s1,__s2,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcscoll_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c32coll_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#else /* LIBC: c32coll_l */
#include <local/wchar/c32coll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32coll_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c32coll_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32coll_l))(__s1, __s2, __locale); })
#endif /* c32coll_l... */
#if defined(__CRT_HAVE_wcsncoll_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsncoll_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_wcsncmp_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsncmp_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsncmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsncmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsncmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$wcsncoll_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsncoll_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c16ncoll_l)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen, __locale); }
#else /* LIBC: c16ncoll_l */
#include <local/wchar/c16ncoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ncoll_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c16ncoll_l)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ncoll_l))(__s1, __s2, __maxlen, __locale); })
#endif /* c16ncoll_l... */
#if defined(__CRT_HAVE_wcsncoll_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsncmp_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsncmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_wcsncmp_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncmp_l,(__s1,__s2,__maxlen,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsncoll_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c32ncoll_l)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen, __locale); }
#else /* LIBC: c32ncoll_l */
#include <local/wchar/c32ncoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ncoll_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c32ncoll_l)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ncoll_l))(__s1, __s2, __maxlen, __locale); })
#endif /* c32ncoll_l... */
#if defined(__CRT_HAVE_wcscasecoll_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscasecoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicoll_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcsicoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcsicoll_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcsicoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcscasecmp_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcsicmp_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsicoll_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcsicoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$wcsicoll_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcsicoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsicmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$wcsicmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$wcscasecoll_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16casecoll_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),wcscasecoll_l,(__s1,__s2,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcscasecoll_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c16casecoll_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#else /* LIBC: c16casecoll_l */
#include <local/wchar/c16casecoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16casecoll_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c16casecoll_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16casecoll_l))(__s1, __s2, __locale); })
#endif /* c16casecoll_l... */
#if defined(__CRT_HAVE_wcscasecoll_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcscasecoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicoll_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),_wcsicoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcsicoll_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcsicoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcscasecmp_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcsicmp_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32casecoll_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),wcsicmp_l,(__s1,__s2,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcscasecoll_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c32casecoll_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#else /* LIBC: c32casecoll_l */
#include <local/wchar/c32casecoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32casecoll_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c32casecoll_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32casecoll_l))(__s1, __s2, __locale); })
#endif /* c32casecoll_l... */
#if defined(__CRT_HAVE_wcsncasecoll_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicoll_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_wcsncasecmp_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicmp_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_wcsnicmp_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsnicoll_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsnicmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$wcsnicmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$wcsncasecoll_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c16ncasecoll_l,(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecoll_l,(__s1,__s2,__maxlen,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsncasecoll_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c16ncasecoll_l)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen, __locale); }
#else /* LIBC: c16ncasecoll_l */
#include <local/wchar/c16ncasecoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ncasecoll_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c16ncasecoll_l)(char16_t const *__s1, char16_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ncasecoll_l))(__s1, __s2, __maxlen, __locale); })
#endif /* c16ncasecoll_l... */
#if defined(__CRT_HAVE_wcsncasecoll_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicoll_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_wcsncasecmp_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicmp_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_wcsnicmp_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,c32ncasecoll_l,(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsncasecoll_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c32ncasecoll_l)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __maxlen, __locale); }
#else /* LIBC: c32ncasecoll_l */
#include <local/wchar/c32ncasecoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ncasecoll_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL c32ncasecoll_l)(char32_t const *__s1, char32_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ncasecoll_l))(__s1, __s2, __maxlen, __locale); })
#endif /* c32ncasecoll_l... */
#if defined(__CRT_HAVE_wcslwr_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16lwr_l,(char16_t *__restrict __str, __locale_t __locale),wcslwr_l,(__str,__locale))
#elif defined(__CRT_HAVE__wcslwr_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16lwr_l,(char16_t *__restrict __str, __locale_t __locale),_wcslwr_l,(__str,__locale))
#elif defined(__CRT_HAVE_DOS$_wcslwr_l)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16lwr_l,(char16_t *__restrict __str, __locale_t __locale),_wcslwr_l,(__str,__locale))
#elif defined(__CRT_HAVE_DOS$wcslwr_l)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16lwr_l,(char16_t *__restrict __str, __locale_t __locale),wcslwr_l,(__str,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcslwr_l.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16lwr_l)(char16_t *__restrict __str, __locale_t __locale) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr_l))((__WCHAR_TYPE__ *)__str, __locale); }
#else /* LIBC: c16lwr_l */
#include <local/wchar/c16lwr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16lwr_l, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16lwr_l)(char16_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16lwr_l))(__str, __locale); })
#endif /* c16lwr_l... */
#if defined(__CRT_HAVE_wcslwr_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32lwr_l,(char32_t *__restrict __str, __locale_t __locale),wcslwr_l,(__str,__locale))
#elif defined(__CRT_HAVE__wcslwr_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32lwr_l,(char32_t *__restrict __str, __locale_t __locale),_wcslwr_l,(__str,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcslwr_l.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32lwr_l)(char32_t *__restrict __str, __locale_t __locale) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr_l))((__WCHAR_TYPE__ *)__str, __locale); }
#else /* LIBC: c32lwr_l */
#include <local/wchar/c32lwr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32lwr_l, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32lwr_l)(char32_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32lwr_l))(__str, __locale); })
#endif /* c32lwr_l... */
#if defined(__CRT_HAVE_wcsupr_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16upr_l,(char16_t *__restrict __str, __locale_t __locale),wcsupr_l,(__str,__locale))
#elif defined(__CRT_HAVE__wcsupr_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16upr_l,(char16_t *__restrict __str, __locale_t __locale),_wcsupr_l,(__str,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsupr_l)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16upr_l,(char16_t *__restrict __str, __locale_t __locale),_wcsupr_l,(__str,__locale))
#elif defined(__CRT_HAVE_DOS$wcsupr_l)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char16_t *,__NOTHROW_NCX,c16upr_l,(char16_t *__restrict __str, __locale_t __locale),wcsupr_l,(__str,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsupr_l.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16upr_l)(char16_t *__restrict __str, __locale_t __locale) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr_l))((__WCHAR_TYPE__ *)__str, __locale); }
#else /* LIBC: c16upr_l */
#include <local/wchar/c16upr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16upr_l, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char16_t *__NOTHROW_NCX(__LIBCCALL c16upr_l)(char16_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16upr_l))(__str, __locale); })
#endif /* c16upr_l... */
#if defined(__CRT_HAVE_wcsupr_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32upr_l,(char32_t *__restrict __str, __locale_t __locale),wcsupr_l,(__str,__locale))
#elif defined(__CRT_HAVE__wcsupr_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char32_t *,__NOTHROW_NCX,c32upr_l,(char32_t *__restrict __str, __locale_t __locale),_wcsupr_l,(__str,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsupr_l.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32upr_l)(char32_t *__restrict __str, __locale_t __locale) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr_l))((__WCHAR_TYPE__ *)__str, __locale); }
#else /* LIBC: c32upr_l */
#include <local/wchar/c32upr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32upr_l, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char32_t *__NOTHROW_NCX(__LIBCCALL c32upr_l)(char32_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32upr_l))(__str, __locale); })
#endif /* c32upr_l... */
#if defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16memcasecmp_l,(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale),fuzzy_wmemcasecmp_l,(__s1,__s1_bytes,__s2,__s2_bytes,__locale))
#elif defined(__CRT_HAVE_DOS$fuzzy_wmemcasecmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16memcasecmp_l,(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale),fuzzy_wmemcasecmp_l,(__s1,__s1_bytes,__s2,__s2_bytes,__locale))
#elif !defined(__NO_MALLOCA)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/fuzzy_wmemcasecmp_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c16memcasecmp_l)(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcasecmp_l))((__WCHAR_TYPE__ const *)__s1, __s1_bytes, (__WCHAR_TYPE__ const *)__s2, __s2_bytes, __locale); }
#else /* LIBC: fuzzy_c16memcasecmp_l */
#include <local/wchar/fuzzy_c16memcasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16memcasecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c16memcasecmp_l)(char16_t const *__s1, __SIZE_TYPE__ __s1_bytes, char16_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16memcasecmp_l))(__s1, __s1_bytes, __s2, __s2_bytes, __locale); })
#endif /* LIBC: fuzzy_c16memcasecmp_l */
#endif /* fuzzy_c16memcasecmp_l... */
#if defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32memcasecmp_l,(char32_t const *__s1, __SIZE_TYPE__ __s1_bytes, char32_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale),fuzzy_wmemcasecmp_l,(__s1,__s1_bytes,__s2,__s2_bytes,__locale))
#elif !defined(__NO_MALLOCA)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/fuzzy_wmemcasecmp_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c32memcasecmp_l)(char32_t const *__s1, __SIZE_TYPE__ __s1_bytes, char32_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcasecmp_l))((__WCHAR_TYPE__ const *)__s1, __s1_bytes, (__WCHAR_TYPE__ const *)__s2, __s2_bytes, __locale); }
#else /* LIBC: fuzzy_c32memcasecmp_l */
#include <local/wchar/fuzzy_c32memcasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32memcasecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c32memcasecmp_l)(char32_t const *__s1, __SIZE_TYPE__ __s1_bytes, char32_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32memcasecmp_l))(__s1, __s1_bytes, __s2, __s2_bytes, __locale); })
#endif /* LIBC: fuzzy_c32memcasecmp_l */
#endif /* fuzzy_c32memcasecmp_l... */
#if defined(__CRT_HAVE_fuzzy_wcscasecmp_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16casecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),fuzzy_wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$fuzzy_wcscasecmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16casecmp_l,(char16_t const *__s1, char16_t const *__s2, __locale_t __locale),fuzzy_wcscasecmp_l,(__s1,__s2,__locale))
#elif !defined(__NO_MALLOCA) || defined(__CRT_HAVE_fuzzy_wmemcasecmp_l)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/fuzzy_wcscasecmp_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c16casecmp_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscasecmp_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#else /* LIBC: fuzzy_c16casecmp_l */
#include <local/wchar/fuzzy_c16casecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16casecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c16casecmp_l)(char16_t const *__s1, char16_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16casecmp_l))(__s1, __s2, __locale); })
#endif /* LIBC: fuzzy_c16casecmp_l */
#endif /* fuzzy_c16casecmp_l... */
#if defined(__CRT_HAVE_fuzzy_wcscasecmp_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32casecmp_l,(char32_t const *__s1, char32_t const *__s2, __locale_t __locale),fuzzy_wcscasecmp_l,(__s1,__s2,__locale))
#elif !defined(__NO_MALLOCA) || defined(__CRT_HAVE_fuzzy_wmemcasecmp_l)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/fuzzy_wcscasecmp_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c32casecmp_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscasecmp_l))((__WCHAR_TYPE__ const *)__s1, (__WCHAR_TYPE__ const *)__s2, __locale); }
#else /* LIBC: fuzzy_c32casecmp_l */
#include <local/wchar/fuzzy_c32casecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32casecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c32casecmp_l)(char32_t const *__s1, char32_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32casecmp_l))(__s1, __s2, __locale); })
#endif /* LIBC: fuzzy_c32casecmp_l */
#endif /* fuzzy_c32casecmp_l... */
#if defined(__CRT_HAVE_fuzzy_wcsncasecmp_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16ncasecmp_l,(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale),fuzzy_wcsncasecmp_l,(__s1,__s1_maxlen,__s2,__s2_maxlen,__locale))
#elif defined(__CRT_HAVE_DOS$fuzzy_wcsncasecmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c16ncasecmp_l,(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale),fuzzy_wcsncasecmp_l,(__s1,__s1_maxlen,__s2,__s2_maxlen,__locale))
#elif !defined(__NO_MALLOCA) || defined(__CRT_HAVE_fuzzy_wmemcasecmp_l)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/fuzzy_wcsncasecmp_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c16ncasecmp_l)(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncasecmp_l))((__WCHAR_TYPE__ const *)__s1, __s1_maxlen, (__WCHAR_TYPE__ const *)__s2, __s2_maxlen, __locale); }
#else /* LIBC: fuzzy_c16ncasecmp_l */
#include <local/wchar/fuzzy_c16ncasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c16ncasecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c16ncasecmp_l)(char16_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char16_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c16ncasecmp_l))(__s1, __s1_maxlen, __s2, __s2_maxlen, __locale); })
#endif /* LIBC: fuzzy_c16ncasecmp_l */
#endif /* fuzzy_c16ncasecmp_l... */
#if defined(__CRT_HAVE_fuzzy_wcsncasecmp_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_c32ncasecmp_l,(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale),fuzzy_wcsncasecmp_l,(__s1,__s1_maxlen,__s2,__s2_maxlen,__locale))
#elif !defined(__NO_MALLOCA) || defined(__CRT_HAVE_fuzzy_wmemcasecmp_l)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/fuzzy_wcsncasecmp_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c32ncasecmp_l)(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncasecmp_l))((__WCHAR_TYPE__ const *)__s1, __s1_maxlen, (__WCHAR_TYPE__ const *)__s2, __s2_maxlen, __locale); }
#else /* LIBC: fuzzy_c32ncasecmp_l */
#include <local/wchar/fuzzy_c32ncasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_c32ncasecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_c32ncasecmp_l)(char32_t const *__s1, __SIZE_TYPE__ __s1_maxlen, char32_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32ncasecmp_l))(__s1, __s1_maxlen, __s2, __s2_maxlen, __locale); })
#endif /* LIBC: fuzzy_c32ncasecmp_l */
#endif /* fuzzy_c32ncasecmp_l... */
#if defined(__CRT_HAVE_wildwcscasecmp_l) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildc16casecmp_l,(char16_t const *__pattern, char16_t const *__string, __locale_t __locale),wildwcscasecmp_l,(__pattern,__string,__locale))
#elif defined(__CRT_HAVE_DOS$wildwcscasecmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildc16casecmp_l,(char16_t const *__pattern, char16_t const *__string, __locale_t __locale),wildwcscasecmp_l,(__pattern,__string,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wildwcscasecmp_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wildc16casecmp_l)(char16_t const *__pattern, char16_t const *__string, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscasecmp_l))((__WCHAR_TYPE__ const *)__pattern, (__WCHAR_TYPE__ const *)__string, __locale); }
#else /* LIBC: wildc16casecmp_l */
#include <local/wchar/wildc16casecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildc16casecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wildc16casecmp_l)(char16_t const *__pattern, char16_t const *__string, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildc16casecmp_l))(__pattern, __string, __locale); })
#endif /* wildc16casecmp_l... */
#if defined(__CRT_HAVE_wildwcscasecmp_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildc32casecmp_l,(char32_t const *__pattern, char32_t const *__string, __locale_t __locale),wildwcscasecmp_l,(__pattern,__string,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wildwcscasecmp_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wildc32casecmp_l)(char32_t const *__pattern, char32_t const *__string, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscasecmp_l))((__WCHAR_TYPE__ const *)__pattern, (__WCHAR_TYPE__ const *)__string, __locale); }
#else /* LIBC: wildc32casecmp_l */
#include <local/wchar/wildc32casecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildc32casecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wildc32casecmp_l)(char32_t const *__pattern, char32_t const *__string, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildc32casecmp_l))(__pattern, __string, __locale); })
#endif /* wildc32casecmp_l... */
#endif /* __USE_XOPEN2K8 */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_PARTS_UCHAR_STRING_H */
