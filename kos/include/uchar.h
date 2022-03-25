/* HASH CRC-32:0x1148d038 */
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
/* (>) Standard: ISO C11 (ISO/IEC 9899:2011) */
/* (#) Portability: FreeBSD       (/include/uchar.h) */
/* (#) Portability: GNU C Library (/wcsmbs/uchar.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/uchar.h) */
/* (#) Portability: Windows Kits  (/ucrt/uchar.h) */
/* (#) Portability: libc6         (/include/uchar.h) */
/* (#) Portability: musl libc     (/include/uchar.h) */
/* (#) Portability: uClibc        (/include/uchar.h) */
#ifndef _UCHAR_H
#define _UCHAR_H 1

#ifdef _CXX_STDONLY_CUCHAR
#ifdef __CXX_SYSTEM_HEADER
#undef _UCHAR_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "uchar.h" after "cuchar" */
#ifndef __mbstate_t_defined
#define __mbstate_t_defined
__NAMESPACE_STD_USING(mbstate_t)
#endif /* !__mbstate_t_defined */
#ifndef __size_t_defined
#define __size_t_defined
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
__NAMESPACE_STD_USING(mbrtoc16)
__NAMESPACE_STD_USING(mbrtoc32)
__NAMESPACE_STD_USING(c16rtomb)
__NAMESPACE_STD_USING(c32rtomb)
#undef _CXX_STDONLY_CUCHAR
#endif /* !__CXX_SYSTEM_HEADER */
#else /* _CXX_STDONLY_CUCHAR */
#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <hybrid/typecore.h>
#include <bits/crt/mbstate.h>


#ifdef __USE_KOS
/* Static initializer for `mbstate_t':
 * >> mbstate_t mbs = MBSTATE_INIT; */
#if !defined(MBSTATE_INIT) && defined(__MBSTATE_INIT)
#define MBSTATE_INIT __MBSTATE_INIT
#endif /* !MBSTATE_INIT && __MBSTATE_INIT */

/* Dynamic initializer for `mbstate_t':
 * >> mbstate_t mbs;
 * >> mbstate_init(&mbs); */
#if !defined(mbstate_init) && defined(__mbstate_init)
#define mbstate_init __mbstate_init
#endif /* !mbstate_init && __mbstate_init */

/* Check if the given mbstate_t is in its zero-shift state:
 * >> if (mbstate_isempty(&mbs)) { ... } */
#if !defined(mbstate_isempty) && defined(__mbstate_isempty)
#define mbstate_isempty __mbstate_isempty
#endif /* !mbstate_isempty && __mbstate_isempty */
#endif /* __USE_KOS */


#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __std_mbstate_t_defined
#define __std_mbstate_t_defined
__NAMESPACE_STD_BEGIN
typedef struct __mbstate mbstate_t;
__NAMESPACE_STD_END
#endif /* !__std_mbstate_t_defined */

#ifndef __CXX_SYSTEM_HEADER
#ifndef __mbstate_t_defined
#define __mbstate_t_defined
__NAMESPACE_STD_USING(mbstate_t)
#endif /* !__mbstate_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */


/* Define `size_t' */
#ifndef __std_size_t_defined
#define __std_size_t_defined
__NAMESPACE_STD_BEGIN
typedef __SIZE_TYPE__ size_t;
__NAMESPACE_STD_END
#endif /* !__std_size_t_defined */
#ifndef __CXX_SYSTEM_HEADER
#ifndef __size_t_defined
#define __size_t_defined
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */

#ifndef __char16_t_defined
#define __char16_t_defined
typedef __CHAR16_TYPE__ char16_t;
typedef __CHAR32_TYPE__ char32_t;
#endif /* !__char16_t_defined */

/* Libc uses utf16/utf32 to encode/decode char16_t and char32_t */
#define __STD_UTF_16__ 1
#define __STD_UTF_32__ 1

__NAMESPACE_STD_BEGIN
#ifdef __CRT_HAVE_mbrtoc16
/* >> mbrtoc16(3) */
__CDECLARE(,size_t,__NOTHROW_NCX,mbrtoc16,(char16_t *__pc16, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs),(__pc16,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_mbrtowc) && __SIZEOF_WCHAR_T__ == 2
/* >> mbrtoc16(3) */
__CREDIRECT(,size_t,__NOTHROW_NCX,mbrtoc16,(char16_t *__pc16, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs),mbrtowc,(__pc16,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE___mbrtowc) && __SIZEOF_WCHAR_T__ == 2
/* >> mbrtoc16(3) */
__CREDIRECT(,size_t,__NOTHROW_NCX,mbrtoc16,(char16_t *__pc16, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs),__mbrtowc,(__pc16,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_DOS$mbrtowc) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> mbrtoc16(3) */
__COMPILER_CREDIRECT(__LIBC,,size_t,__NOTHROW_NCX,__LIBCCALL,mbrtoc16,(char16_t *__pc16, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs),DOS$mbrtowc,(__pc16,__str,__maxlen,__mbs))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_STD_END
#include <libc/local/wchar/mbrtowc.h>
__NAMESPACE_STD_BEGIN
/* >> mbrtoc16(3) */
__FORCELOCAL __ATTR_ARTIFICIAL size_t __NOTHROW_NCX(__LIBCCALL mbrtoc16)(char16_t *__pc16, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbrtowc))((__WCHAR_TYPE__ *)__pc16, __str, __maxlen, __mbs); }
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/uchar/uchar_mbrtoc16.h>
__NAMESPACE_STD_BEGIN
/* >> mbrtoc16(3) */
__FORCELOCAL __ATTR_ARTIFICIAL size_t __NOTHROW_NCX(__LIBCCALL mbrtoc16)(char16_t *__pc16, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(uchar_mbrtoc16))(__pc16, __str, __maxlen, __mbs); }
#endif /* !... */
#ifdef __CRT_HAVE_mbrtoc32
/* >> mbrtoc32(3) */
__CDECLARE(,size_t,__NOTHROW_NCX,mbrtoc32,(char32_t *__pc32, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs),(__pc32,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_mbrtowc) && __SIZEOF_WCHAR_T__ == 4
/* >> mbrtoc32(3) */
__CREDIRECT(,size_t,__NOTHROW_NCX,mbrtoc32,(char32_t *__pc32, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs),mbrtowc,(__pc32,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE___mbrtowc) && __SIZEOF_WCHAR_T__ == 4
/* >> mbrtoc32(3) */
__CREDIRECT(,size_t,__NOTHROW_NCX,mbrtoc32,(char32_t *__pc32, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs),__mbrtowc,(__pc32,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_KOS$mbrtowc) && defined(__PE__) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> mbrtoc32(3) */
__COMPILER_CREDIRECT(__LIBC,,size_t,__NOTHROW_NCX,__LIBCCALL,mbrtoc32,(char32_t *__pc32, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs),KOS$mbrtowc,(__pc32,__str,__maxlen,__mbs))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_STD_END
#include <libc/local/wchar/mbrtowc.h>
__NAMESPACE_STD_BEGIN
/* >> mbrtoc32(3) */
__FORCELOCAL __ATTR_ARTIFICIAL size_t __NOTHROW_NCX(__LIBCCALL mbrtoc32)(char32_t *__pc32, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbrtowc))((__WCHAR_TYPE__ *)__pc32, __str, __maxlen, __mbs); }
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/uchar/uchar_mbrtoc32.h>
__NAMESPACE_STD_BEGIN
/* >> mbrtoc32(3) */
__FORCELOCAL __ATTR_ARTIFICIAL size_t __NOTHROW_NCX(__LIBCCALL mbrtoc32)(char32_t *__pc32, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(uchar_mbrtoc32))(__pc32, __str, __maxlen, __mbs); }
#endif /* !... */
#ifdef __CRT_HAVE_c16rtomb
/* >> c16rtomb(3) */
__CDECLARE(,size_t,__NOTHROW_NCX,c16rtomb,(char *__restrict __str, char16_t __c16, mbstate_t *__mbs),(__str,__c16,__mbs))
#elif defined(__CRT_HAVE_wcrtomb) && __SIZEOF_WCHAR_T__ == 2
/* >> c16rtomb(3) */
__CREDIRECT(,size_t,__NOTHROW_NCX,c16rtomb,(char *__restrict __str, char16_t __c16, mbstate_t *__mbs),wcrtomb,(__str,__c16,__mbs))
#elif defined(__CRT_HAVE_DOS$wcrtomb) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> c16rtomb(3) */
__COMPILER_CREDIRECT(__LIBC,,size_t,__NOTHROW_NCX,__LIBCCALL,c16rtomb,(char *__restrict __str, char16_t __c16, mbstate_t *__mbs),DOS$wcrtomb,(__str,__c16,__mbs))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_STD_END
#include <libc/local/wchar/wcrtomb.h>
__NAMESPACE_STD_BEGIN
/* >> c16rtomb(3) */
__FORCELOCAL __ATTR_ARTIFICIAL size_t __NOTHROW_NCX(__LIBCCALL c16rtomb)(char *__restrict __str, char16_t __c16, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcrtomb))(__str, (__WCHAR_TYPE__)__c16, __mbs); }
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/uchar/uchar_c16rtomb.h>
__NAMESPACE_STD_BEGIN
/* >> c16rtomb(3) */
__FORCELOCAL __ATTR_ARTIFICIAL size_t __NOTHROW_NCX(__LIBCCALL c16rtomb)(char *__restrict __str, char16_t __c16, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(uchar_c16rtomb))(__str, __c16, __mbs); }
#endif /* !... */
#ifdef __CRT_HAVE_c32rtomb
/* >> c32rtomb(3) */
__CDECLARE(,size_t,__NOTHROW_NCX,c32rtomb,(char *__restrict __str, char32_t __c32, mbstate_t *__mbs),(__str,__c32,__mbs))
#elif defined(__CRT_HAVE_wcrtomb) && __SIZEOF_WCHAR_T__ == 4
/* >> c32rtomb(3) */
__CREDIRECT(,size_t,__NOTHROW_NCX,c32rtomb,(char *__restrict __str, char32_t __c32, mbstate_t *__mbs),wcrtomb,(__str,__c32,__mbs))
#elif defined(__CRT_HAVE_KOS$wcrtomb) && defined(__PE__) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> c32rtomb(3) */
__COMPILER_CREDIRECT(__LIBC,,size_t,__NOTHROW_NCX,__LIBCCALL,c32rtomb,(char *__restrict __str, char32_t __c32, mbstate_t *__mbs),KOS$wcrtomb,(__str,__c32,__mbs))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_STD_END
#include <libc/local/wchar/wcrtomb.h>
__NAMESPACE_STD_BEGIN
/* >> c32rtomb(3) */
__FORCELOCAL __ATTR_ARTIFICIAL size_t __NOTHROW_NCX(__LIBCCALL c32rtomb)(char *__restrict __str, char32_t __c32, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcrtomb))(__str, (__WCHAR_TYPE__)__c32, __mbs); }
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/uchar/uchar_c32rtomb.h>
__NAMESPACE_STD_BEGIN
/* >> c32rtomb(3) */
__FORCELOCAL __ATTR_ARTIFICIAL size_t __NOTHROW_NCX(__LIBCCALL c32rtomb)(char *__restrict __str, char32_t __c32, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(uchar_c32rtomb))(__str, __c32, __mbs); }
#endif /* !... */
__NAMESPACE_STD_END
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(mbrtoc16)
__NAMESPACE_STD_USING(mbrtoc32)
__NAMESPACE_STD_USING(c16rtomb)
__NAMESPACE_STD_USING(c32rtomb)
#endif /* !__CXX_SYSTEM_HEADER */


#ifdef __USE_KOS
/* Simple functions to convert between single-byte and multi-byte  formats,
 * without having to worry about buffers (since all of these functions will
 * automatically allocate buffers on the heap) */

#ifdef __CRT_HAVE_convert_freev
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UCHAR_H_PROTO)
extern "C++" {
__CREDIRECT_VOID(,__NOTHROW_NCX,convert_freev,(char **__vector),convert_freev,(__vector))
__CREDIRECT_VOID(,__NOTHROW_NCX,convert_freev,(char16_t **__vector),convert_freev,(__vector))
__CREDIRECT_VOID(,__NOTHROW_NCX,convert_freev,(char32_t **__vector),convert_freev,(__vector))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UCHAR_H_PROTO */
__CDECLARE_VOID(,__NOTHROW_NCX,convert_freev,(void *__vector),(__vector))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UCHAR_H_PROTO */
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
#include <libc/local/uchar/convert_freev.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UCHAR_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL convert_freev)(char **__vector) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_freev))((void *)__vector); }
__FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL convert_freev)(char16_t **__vector) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_freev))((void *)__vector); }
__FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL convert_freev)(char32_t **__vector) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_freev))((void *)__vector); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UCHAR_H_PROTO */
__NAMESPACE_LOCAL_USING_OR_IMPL(convert_freev, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL convert_freev)(void *__vector) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_freev))(__vector); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UCHAR_H_PROTO */
#endif /* ... */
#ifdef __CRT_HAVE_convert_freevn
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UCHAR_H_PROTO)
extern "C++" {
__CREDIRECT_VOID(,__NOTHROW_NCX,convert_freevn,(char **__vector, __SIZE_TYPE__ __count),convert_freevn,(__vector,__count))
__CREDIRECT_VOID(,__NOTHROW_NCX,convert_freevn,(char16_t **__vector, __SIZE_TYPE__ __count),convert_freevn,(__vector,__count))
__CREDIRECT_VOID(,__NOTHROW_NCX,convert_freevn,(char32_t **__vector, __SIZE_TYPE__ __count),convert_freevn,(__vector,__count))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UCHAR_H_PROTO */
__CDECLARE_VOID(,__NOTHROW_NCX,convert_freevn,(void *__vector, __SIZE_TYPE__ __count),(__vector,__count))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UCHAR_H_PROTO */
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
#include <libc/local/uchar/convert_freevn.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UCHAR_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL convert_freevn)(char **__vector, __SIZE_TYPE__ __count) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_freevn))((void *)__vector, __count); }
__FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL convert_freevn)(char16_t **__vector, __SIZE_TYPE__ __count) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_freevn))((void *)__vector, __count); }
__FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL convert_freevn)(char32_t **__vector, __SIZE_TYPE__ __count) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_freevn))((void *)__vector, __count); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UCHAR_H_PROTO */
__NAMESPACE_LOCAL_USING_OR_IMPL(convert_freevn, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL convert_freevn)(void *__vector, __SIZE_TYPE__ __count) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_freevn))(__vector, __count); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UCHAR_H_PROTO */
#endif /* ... */
#ifdef __CRT_HAVE_convert_wcstombs
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,convert_wcstombs,(__WCHAR_TYPE__ const *__str),(__str))
#elif defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <libc/local/uchar/convert_wcstombs.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(convert_wcstombs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL convert_wcstombs)(__WCHAR_TYPE__ const *__str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_wcstombs))(__str); })
#endif /* ... */
#ifdef __CRT_HAVE_convert_wcstombsn
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,convert_wcstombsn,(__WCHAR_TYPE__ const *__restrict __str, __SIZE_TYPE__ __len, __SIZE_TYPE__ *__preslen),(__str,__len,__preslen))
#elif defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <libc/local/uchar/convert_wcstombsn.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(convert_wcstombsn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL convert_wcstombsn)(__WCHAR_TYPE__ const *__restrict __str, __SIZE_TYPE__ __len, __SIZE_TYPE__ *__preslen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_wcstombsn))(__str, __len, __preslen); })
#endif /* ... */
#ifdef __CRT_HAVE_convert_wcstombsv
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED,char **,__NOTHROW_NCX,convert_wcstombsv,(__WCHAR_TYPE__ const *const *__restrict __vector),(__vector))
#elif defined(__CRT_HAVE_convert_wcstombsvn) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/uchar/convert_wcstombsv.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(convert_wcstombsv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED char **__NOTHROW_NCX(__LIBCCALL convert_wcstombsv)(__WCHAR_TYPE__ const *const *__restrict __vector) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_wcstombsv))(__vector); })
#endif /* ... */
#ifdef __CRT_HAVE_convert_wcstombsvn
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED,char **,__NOTHROW_NCX,convert_wcstombsvn,(__WCHAR_TYPE__ const *const *__restrict __vector, size_t __count),(__vector,__count))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/uchar/convert_wcstombsvn.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(convert_wcstombsvn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED char **__NOTHROW_NCX(__LIBCCALL convert_wcstombsvn)(__WCHAR_TYPE__ const *const *__restrict __vector, size_t __count) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_wcstombsvn))(__vector, __count); })
#endif /* ... */
#ifdef __CRT_HAVE_convert_mbstowcs
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED,__WCHAR_TYPE__ *,__NOTHROW_NCX,convert_mbstowcs,(char const *__restrict __str),(__str))
#elif defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/uchar/convert_mbstowcs.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(convert_mbstowcs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __WCHAR_TYPE__ *__NOTHROW_NCX(__LIBCCALL convert_mbstowcs)(char const *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_mbstowcs))(__str); })
#endif /* ... */
#ifdef __CRT_HAVE_convert_mbstowcsn
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED,__WCHAR_TYPE__ *,__NOTHROW_NCX,convert_mbstowcsn,(char const *__restrict __str, size_t __len, size_t *__preslen),(__str,__len,__preslen))
#elif (defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/uchar/convert_mbstowcsn.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(convert_mbstowcsn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __WCHAR_TYPE__ *__NOTHROW_NCX(__LIBCCALL convert_mbstowcsn)(char const *__restrict __str, size_t __len, size_t *__preslen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_mbstowcsn))(__str, __len, __preslen); })
#endif /* ... */
#ifdef __CRT_HAVE_convert_mbstowcsv
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED,__WCHAR_TYPE__ **,__NOTHROW_NCX,convert_mbstowcsv,(char const *const *__restrict __vector),(__vector))
#elif defined(__CRT_HAVE_convert_mbstowcsvn) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))))
#include <libc/local/uchar/convert_mbstowcsv.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(convert_mbstowcsv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __WCHAR_TYPE__ **__NOTHROW_NCX(__LIBCCALL convert_mbstowcsv)(char const *const *__restrict __vector) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_mbstowcsv))(__vector); })
#endif /* ... */
#ifdef __CRT_HAVE_convert_mbstowcsvn
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED,__WCHAR_TYPE__ **,__NOTHROW_NCX,convert_mbstowcsvn,(char const *const *__restrict __vector, size_t __count),(__vector,__count))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
#include <libc/local/uchar/convert_mbstowcsvn.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(convert_mbstowcsvn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __WCHAR_TYPE__ **__NOTHROW_NCX(__LIBCCALL convert_mbstowcsvn)(char const *const *__restrict __vector, size_t __count) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_mbstowcsvn))(__vector, __count); })
#endif /* ... */
#if defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,convert_c16tombs,(__CHAR16_TYPE__ const *__str),convert_wcstombs,(__str))
#elif defined(__CRT_HAVE_DOS$convert_wcstombs)
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,convert_c16tombs,(__CHAR16_TYPE__ const *__str),convert_wcstombs,(__str))
#elif (defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/uchar/convert_wcstombs.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBDCALL convert_c16tombs)(__CHAR16_TYPE__ const *__str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_wcstombs))((__WCHAR_TYPE__ const *)__str); }
#elif (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <libc/local/uchar/convert_c16tombs.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(convert_c16tombs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBDCALL convert_c16tombs)(__CHAR16_TYPE__ const *__str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_c16tombs))(__str); })
#endif /* ... */
#if defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,convert_c32tombs,(__CHAR32_TYPE__ const *__str),convert_wcstombs,(__str))
#elif defined(__CRT_HAVE_KOS$convert_wcstombs)
__CREDIRECT_KOS(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,convert_c32tombs,(__CHAR32_TYPE__ const *__str),convert_wcstombs,(__str))
#elif (defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/uchar/convert_wcstombs.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBKCALL convert_c32tombs)(__CHAR32_TYPE__ const *__str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_wcstombs))((__WCHAR_TYPE__ const *)__str); }
#elif (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <libc/local/uchar/convert_c32tombs.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(convert_c32tombs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBKCALL convert_c32tombs)(__CHAR32_TYPE__ const *__str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_c32tombs))(__str); })
#endif /* ... */
#if defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,convert_c16tombsn,(__CHAR16_TYPE__ const *__restrict __str, __SIZE_TYPE__ __len, __SIZE_TYPE__ *__preslen),convert_wcstombsn,(__str,__len,__preslen))
#elif defined(__CRT_HAVE_DOS$convert_wcstombsn)
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,convert_c16tombsn,(__CHAR16_TYPE__ const *__restrict __str, __SIZE_TYPE__ __len, __SIZE_TYPE__ *__preslen),convert_wcstombsn,(__str,__len,__preslen))
#elif (defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/uchar/convert_wcstombsn.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBDCALL convert_c16tombsn)(__CHAR16_TYPE__ const *__restrict __str, __SIZE_TYPE__ __len, __SIZE_TYPE__ *__preslen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_wcstombsn))((__WCHAR_TYPE__ const *)__str, __len, __preslen); }
#elif defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <libc/local/uchar/convert_c16tombsn.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(convert_c16tombsn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBDCALL convert_c16tombsn)(__CHAR16_TYPE__ const *__restrict __str, __SIZE_TYPE__ __len, __SIZE_TYPE__ *__preslen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_c16tombsn))(__str, __len, __preslen); })
#endif /* ... */
#if defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,convert_c32tombsn,(__CHAR32_TYPE__ const *__restrict __str, __SIZE_TYPE__ __len, __SIZE_TYPE__ *__preslen),convert_wcstombsn,(__str,__len,__preslen))
#elif defined(__CRT_HAVE_KOS$convert_wcstombsn)
__CREDIRECT_KOS(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,convert_c32tombsn,(__CHAR32_TYPE__ const *__restrict __str, __SIZE_TYPE__ __len, __SIZE_TYPE__ *__preslen),convert_wcstombsn,(__str,__len,__preslen))
#elif (defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/uchar/convert_wcstombsn.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBKCALL convert_c32tombsn)(__CHAR32_TYPE__ const *__restrict __str, __SIZE_TYPE__ __len, __SIZE_TYPE__ *__preslen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_wcstombsn))((__WCHAR_TYPE__ const *)__str, __len, __preslen); }
#elif defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <libc/local/uchar/convert_c32tombsn.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(convert_c32tombsn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBKCALL convert_c32tombsn)(__CHAR32_TYPE__ const *__restrict __str, __SIZE_TYPE__ __len, __SIZE_TYPE__ *__preslen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_c32tombsn))(__str, __len, __preslen); })
#endif /* ... */
#if defined(__CRT_HAVE_convert_wcstombsv) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,char **,__NOTHROW_NCX,convert_c16tombsv,(__CHAR16_TYPE__ const *const *__restrict __vector),convert_wcstombsv,(__vector))
#elif defined(__CRT_HAVE_DOS$convert_wcstombsv)
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_WUNUSED,char **,__NOTHROW_NCX,convert_c16tombsv,(__CHAR16_TYPE__ const *const *__restrict __vector),convert_wcstombsv,(__vector))
#elif (defined(__CRT_HAVE_convert_wcstombsvn) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/uchar/convert_wcstombsv.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED char **__NOTHROW_NCX(__LIBDCALL convert_c16tombsv)(__CHAR16_TYPE__ const *const *__restrict __vector) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_wcstombsv))((__WCHAR_TYPE__ const *const *)__vector); }
#elif (defined(__CRT_HAVE_convert_wcstombsvn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombsvn) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/uchar/convert_c16tombsv.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(convert_c16tombsv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED char **__NOTHROW_NCX(__LIBDCALL convert_c16tombsv)(__CHAR16_TYPE__ const *const *__restrict __vector) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_c16tombsv))(__vector); })
#endif /* ... */
#if defined(__CRT_HAVE_convert_wcstombsv) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,char **,__NOTHROW_NCX,convert_c32tombsv,(__CHAR32_TYPE__ const *const *__restrict __vector),convert_wcstombsv,(__vector))
#elif defined(__CRT_HAVE_KOS$convert_wcstombsv)
__CREDIRECT_KOS(__ATTR_MALLOC __ATTR_WUNUSED,char **,__NOTHROW_NCX,convert_c32tombsv,(__CHAR32_TYPE__ const *const *__restrict __vector),convert_wcstombsv,(__vector))
#elif (defined(__CRT_HAVE_convert_wcstombsvn) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/uchar/convert_wcstombsv.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED char **__NOTHROW_NCX(__LIBKCALL convert_c32tombsv)(__CHAR32_TYPE__ const *const *__restrict __vector) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_wcstombsv))((__WCHAR_TYPE__ const *const *)__vector); }
#elif (defined(__CRT_HAVE_convert_wcstombsvn) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_wcstombsvn) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 4) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/uchar/convert_c32tombsv.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(convert_c32tombsv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED char **__NOTHROW_NCX(__LIBKCALL convert_c32tombsv)(__CHAR32_TYPE__ const *const *__restrict __vector) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_c32tombsv))(__vector); })
#endif /* ... */
#if defined(__CRT_HAVE_convert_wcstombsvn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,char **,__NOTHROW_NCX,convert_c16tombsvn,(__CHAR16_TYPE__ const *const *__restrict __vector, size_t __count),convert_wcstombsvn,(__vector,__count))
#elif defined(__CRT_HAVE_DOS$convert_wcstombsvn)
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_WUNUSED,char **,__NOTHROW_NCX,convert_c16tombsvn,(__CHAR16_TYPE__ const *const *__restrict __vector, size_t __count),convert_wcstombsvn,(__vector,__count))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/uchar/convert_wcstombsvn.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED char **__NOTHROW_NCX(__LIBDCALL convert_c16tombsvn)(__CHAR16_TYPE__ const *const *__restrict __vector, size_t __count) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_wcstombsvn))((__WCHAR_TYPE__ const *const *)__vector, __count); }
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/uchar/convert_c16tombsvn.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(convert_c16tombsvn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED char **__NOTHROW_NCX(__LIBDCALL convert_c16tombsvn)(__CHAR16_TYPE__ const *const *__restrict __vector, size_t __count) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_c16tombsvn))(__vector, __count); })
#endif /* ... */
#if defined(__CRT_HAVE_convert_wcstombsvn) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,char **,__NOTHROW_NCX,convert_c32tombsvn,(__CHAR32_TYPE__ const *const *__restrict __vector, size_t __count),convert_wcstombsvn,(__vector,__count))
#elif defined(__CRT_HAVE_KOS$convert_wcstombsvn)
__CREDIRECT_KOS(__ATTR_MALLOC __ATTR_WUNUSED,char **,__NOTHROW_NCX,convert_c32tombsvn,(__CHAR32_TYPE__ const *const *__restrict __vector, size_t __count),convert_wcstombsvn,(__vector,__count))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/uchar/convert_wcstombsvn.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED char **__NOTHROW_NCX(__LIBKCALL convert_c32tombsvn)(__CHAR32_TYPE__ const *const *__restrict __vector, size_t __count) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_wcstombsvn))((__WCHAR_TYPE__ const *const *)__vector, __count); }
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/uchar/convert_c32tombsvn.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(convert_c32tombsvn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED char **__NOTHROW_NCX(__LIBKCALL convert_c32tombsvn)(__CHAR32_TYPE__ const *const *__restrict __vector, size_t __count) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_c32tombsvn))(__vector, __count); })
#endif /* ... */
#if defined(__CRT_HAVE_convert_mbstowcs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,__CHAR16_TYPE__ *,__NOTHROW_NCX,convert_mbstoc16,(char const *__restrict __str),convert_mbstowcs,(__str))
#elif defined(__CRT_HAVE_DOS$convert_mbstowcs)
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_WUNUSED,__CHAR16_TYPE__ *,__NOTHROW_NCX,convert_mbstoc16,(char const *__restrict __str),convert_mbstowcs,(__str))
#elif (defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/uchar/convert_mbstowcs.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __CHAR16_TYPE__ *__NOTHROW_NCX(__LIBDCALL convert_mbstoc16)(char const *__restrict __str) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_mbstowcs))(__str); }
#elif (defined(__CRT_HAVE_convert_mbstowcsn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2) || (((defined(__CRT_HAVE_format_waprintf_printer) && __SIZEOF_WCHAR_T__ == 2 && defined(__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)) || defined(__CRT_HAVE_DOS$format_waprintf_printer) || (defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_format_waprintf_pack) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/uchar/convert_mbstoc16.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(convert_mbstoc16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __CHAR16_TYPE__ *__NOTHROW_NCX(__LIBDCALL convert_mbstoc16)(char const *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_mbstoc16))(__str); })
#endif /* ... */
#if defined(__CRT_HAVE_convert_mbstowcs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,__CHAR32_TYPE__ *,__NOTHROW_NCX,convert_mbstoc32,(char const *__restrict __str),convert_mbstowcs,(__str))
#elif defined(__CRT_HAVE_KOS$convert_mbstowcs)
__CREDIRECT_KOS(__ATTR_MALLOC __ATTR_WUNUSED,__CHAR32_TYPE__ *,__NOTHROW_NCX,convert_mbstoc32,(char const *__restrict __str),convert_mbstowcs,(__str))
#elif (defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/uchar/convert_mbstowcs.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __CHAR32_TYPE__ *__NOTHROW_NCX(__LIBKCALL convert_mbstoc32)(char const *__restrict __str) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_mbstowcs))(__str); }
#elif (defined(__CRT_HAVE_convert_mbstowcsn) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 4) || (((defined(__CRT_HAVE_format_waprintf_printer) && __SIZEOF_WCHAR_T__ == 4 && defined(__C32FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)) || defined(__CRT_HAVE_KOS$format_waprintf_printer) || (defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_format_waprintf_pack) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/uchar/convert_mbstoc32.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(convert_mbstoc32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __CHAR32_TYPE__ *__NOTHROW_NCX(__LIBKCALL convert_mbstoc32)(char const *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_mbstoc32))(__str); })
#endif /* ... */
#if defined(__CRT_HAVE_convert_mbstowcsn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,__CHAR16_TYPE__ *,__NOTHROW_NCX,convert_mbstoc16n,(char const *__restrict __str, size_t __len, size_t *__preslen),convert_mbstowcsn,(__str,__len,__preslen))
#elif defined(__CRT_HAVE_DOS$convert_mbstowcsn)
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_WUNUSED,__CHAR16_TYPE__ *,__NOTHROW_NCX,convert_mbstoc16n,(char const *__restrict __str, size_t __len, size_t *__preslen),convert_mbstowcsn,(__str,__len,__preslen))
#elif (defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/uchar/convert_mbstowcsn.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __CHAR16_TYPE__ *__NOTHROW_NCX(__LIBDCALL convert_mbstoc16n)(char const *__restrict __str, size_t __len, size_t *__preslen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_mbstowcsn))(__str, __len, __preslen); }
#elif ((defined(__CRT_HAVE_format_waprintf_printer) && __SIZEOF_WCHAR_T__ == 2 && defined(__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)) || defined(__CRT_HAVE_DOS$format_waprintf_printer) || (defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_format_waprintf_pack) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/uchar/convert_mbstoc16n.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(convert_mbstoc16n, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __CHAR16_TYPE__ *__NOTHROW_NCX(__LIBDCALL convert_mbstoc16n)(char const *__restrict __str, size_t __len, size_t *__preslen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_mbstoc16n))(__str, __len, __preslen); })
#endif /* ... */
#if defined(__CRT_HAVE_convert_mbstowcsn) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,__CHAR32_TYPE__ *,__NOTHROW_NCX,convert_mbstoc32n,(char const *__restrict __str, size_t __len, size_t *__preslen),convert_mbstowcsn,(__str,__len,__preslen))
#elif defined(__CRT_HAVE_KOS$convert_mbstowcsn)
__CREDIRECT_KOS(__ATTR_MALLOC __ATTR_WUNUSED,__CHAR32_TYPE__ *,__NOTHROW_NCX,convert_mbstoc32n,(char const *__restrict __str, size_t __len, size_t *__preslen),convert_mbstowcsn,(__str,__len,__preslen))
#elif (defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/uchar/convert_mbstowcsn.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __CHAR32_TYPE__ *__NOTHROW_NCX(__LIBKCALL convert_mbstoc32n)(char const *__restrict __str, size_t __len, size_t *__preslen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_mbstowcsn))(__str, __len, __preslen); }
#elif ((defined(__CRT_HAVE_format_waprintf_printer) && __SIZEOF_WCHAR_T__ == 4 && defined(__C32FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)) || defined(__CRT_HAVE_KOS$format_waprintf_printer) || (defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_format_waprintf_pack) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/uchar/convert_mbstoc32n.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(convert_mbstoc32n, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __CHAR32_TYPE__ *__NOTHROW_NCX(__LIBKCALL convert_mbstoc32n)(char const *__restrict __str, size_t __len, size_t *__preslen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_mbstoc32n))(__str, __len, __preslen); })
#endif /* ... */
#if defined(__CRT_HAVE_convert_mbstowcsv) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,__CHAR16_TYPE__ **,__NOTHROW_NCX,convert_mbstoc16v,(char const *const *__restrict __vector),convert_mbstowcsv,(__vector))
#elif defined(__CRT_HAVE_DOS$convert_mbstowcsv)
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_WUNUSED,__CHAR16_TYPE__ **,__NOTHROW_NCX,convert_mbstoc16v,(char const *const *__restrict __vector),convert_mbstowcsv,(__vector))
#elif (defined(__CRT_HAVE_convert_mbstowcsvn) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))))) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/uchar/convert_mbstowcsv.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __CHAR16_TYPE__ **__NOTHROW_NCX(__LIBDCALL convert_mbstoc16v)(char const *const *__restrict __vector) { return (__CHAR16_TYPE__ **)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_mbstowcsv))(__vector); }
#elif (defined(__CRT_HAVE_convert_mbstowcsvn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcsvn) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 2) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && ((defined(__CRT_HAVE_convert_mbstowcs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcs) || ((defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_convert_mbstowcsn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2) || (((defined(__CRT_HAVE_format_waprintf_printer) && __SIZEOF_WCHAR_T__ == 2 && defined(__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)) || defined(__CRT_HAVE_DOS$format_waprintf_printer) || (defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_format_waprintf_pack) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))))
#include <libc/local/uchar/convert_mbstoc16v.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(convert_mbstoc16v, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __CHAR16_TYPE__ **__NOTHROW_NCX(__LIBDCALL convert_mbstoc16v)(char const *const *__restrict __vector) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_mbstoc16v))(__vector); })
#endif /* ... */
#if defined(__CRT_HAVE_convert_mbstowcsv) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,__CHAR32_TYPE__ **,__NOTHROW_NCX,convert_mbstoc32v,(char const *const *__restrict __vector),convert_mbstowcsv,(__vector))
#elif defined(__CRT_HAVE_KOS$convert_mbstowcsv)
__CREDIRECT_KOS(__ATTR_MALLOC __ATTR_WUNUSED,__CHAR32_TYPE__ **,__NOTHROW_NCX,convert_mbstoc32v,(char const *const *__restrict __vector),convert_mbstowcsv,(__vector))
#elif (defined(__CRT_HAVE_convert_mbstowcsvn) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))))) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/uchar/convert_mbstowcsv.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __CHAR32_TYPE__ **__NOTHROW_NCX(__LIBKCALL convert_mbstoc32v)(char const *const *__restrict __vector) { return (__CHAR32_TYPE__ **)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_mbstowcsv))(__vector); }
#elif (defined(__CRT_HAVE_convert_mbstowcsvn) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_mbstowcsvn) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 4) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && ((defined(__CRT_HAVE_convert_mbstowcs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_mbstowcs) || ((defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_convert_mbstowcsn) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 4) || (((defined(__CRT_HAVE_format_waprintf_printer) && __SIZEOF_WCHAR_T__ == 4 && defined(__C32FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)) || defined(__CRT_HAVE_KOS$format_waprintf_printer) || (defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_format_waprintf_pack) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))))
#include <libc/local/uchar/convert_mbstoc32v.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(convert_mbstoc32v, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __CHAR32_TYPE__ **__NOTHROW_NCX(__LIBKCALL convert_mbstoc32v)(char const *const *__restrict __vector) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_mbstoc32v))(__vector); })
#endif /* ... */
#if defined(__CRT_HAVE_convert_mbstowcsvn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,__CHAR16_TYPE__ **,__NOTHROW_NCX,convert_mbstoc16vn,(char const *const *__restrict __vector, size_t __count),convert_mbstowcsvn,(__vector,__count))
#elif defined(__CRT_HAVE_DOS$convert_mbstowcsvn)
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_WUNUSED,__CHAR16_TYPE__ **,__NOTHROW_NCX,convert_mbstoc16vn,(char const *const *__restrict __vector, size_t __count),convert_mbstowcsvn,(__vector,__count))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/uchar/convert_mbstowcsvn.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __CHAR16_TYPE__ **__NOTHROW_NCX(__LIBDCALL convert_mbstoc16vn)(char const *const *__restrict __vector, size_t __count) { return (__CHAR16_TYPE__ **)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_mbstowcsvn))(__vector, __count); }
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && ((defined(__CRT_HAVE_convert_mbstowcs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcs) || ((defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_convert_mbstowcsn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2) || (((defined(__CRT_HAVE_format_waprintf_printer) && __SIZEOF_WCHAR_T__ == 2 && defined(__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)) || defined(__CRT_HAVE_DOS$format_waprintf_printer) || (defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_format_waprintf_pack) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
#include <libc/local/uchar/convert_mbstoc16vn.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(convert_mbstoc16vn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __CHAR16_TYPE__ **__NOTHROW_NCX(__LIBDCALL convert_mbstoc16vn)(char const *const *__restrict __vector, size_t __count) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_mbstoc16vn))(__vector, __count); })
#endif /* ... */
#if defined(__CRT_HAVE_convert_mbstowcsvn) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,__CHAR32_TYPE__ **,__NOTHROW_NCX,convert_mbstoc32vn,(char const *const *__restrict __vector, size_t __count),convert_mbstowcsvn,(__vector,__count))
#elif defined(__CRT_HAVE_KOS$convert_mbstowcsvn)
__CREDIRECT_KOS(__ATTR_MALLOC __ATTR_WUNUSED,__CHAR32_TYPE__ **,__NOTHROW_NCX,convert_mbstoc32vn,(char const *const *__restrict __vector, size_t __count),convert_mbstowcsvn,(__vector,__count))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/uchar/convert_mbstowcsvn.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __CHAR32_TYPE__ **__NOTHROW_NCX(__LIBKCALL convert_mbstoc32vn)(char const *const *__restrict __vector, size_t __count) { return (__CHAR32_TYPE__ **)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_mbstowcsvn))(__vector, __count); }
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && ((defined(__CRT_HAVE_convert_mbstowcs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_mbstowcs) || ((defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_convert_mbstowcsn) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 4) || (((defined(__CRT_HAVE_format_waprintf_printer) && __SIZEOF_WCHAR_T__ == 4 && defined(__C32FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)) || defined(__CRT_HAVE_KOS$format_waprintf_printer) || (defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_format_waprintf_pack) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
#include <libc/local/uchar/convert_mbstoc32vn.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(convert_mbstoc32vn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __CHAR32_TYPE__ **__NOTHROW_NCX(__LIBKCALL convert_mbstoc32vn)(char const *const *__restrict __vector, size_t __count) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(convert_mbstoc32vn))(__vector, __count); })
#endif /* ... */
#endif /* __USE_KOS */

__SYSDECL_END
#endif /* __CC__ */


/* When  `#define _UTF_SOURCE' is  given, all  of KOS's  uchar variants are
 * exposed when both <uchar.h> and the header of origin have been included.
 *
 * For example:
 * >> #define _UTF_SOURCE
 * >> #include <string.h>  // Order of #includes doesn't matter; <string.h>
 * >> #include <uchar.h>   // also has a check if uchar was already included
 * >> // At this point, symbols `size_t c16slen(char16_t const *str)'
 * >> // have been defined (but be aware that calling conventions may
 * >> // not be identical between char16_t and char32_t variants of
 * >> // libc functions, and that utf-16 filesystem functions take
 * >> // DOS paths, rather than unix paths!)
 */
#ifdef __USE_UTF

#if defined(_CORECRT_WDIRECT_H) && !defined(_PARTS_UCHAR_DIRECT_H)
#include <parts/uchar/direct.h>
#endif /* _CORECRT_WDIRECT_H && !_PARTS_UCHAR_DIRECT_H */

#if defined(_FCNTL_H) && !defined(_PARTS_UCHAR_FCNTL_H)
#include <parts/uchar/fcntl.h>
#endif /* _FCNTL_H && !_PARTS_UCHAR_FCNTL_H */

#if defined(_FORMAT_PRINTER_H) && !defined(_PARTS_UCHAR_FORMATPRINTER_H)
#include <parts/uchar/format-printer.h>
#endif /* _FORMAT_PRINTER_H && !_PARTS_UCHAR_FORMATPRINTER_H */

#if defined(_INTTYPES_H) && !defined(_PARTS_UCHAR_INTTYPES_H)
#include <parts/uchar/inttypes.h>
#endif /* _INTTYPES_H && !_PARTS_UCHAR_INTTYPES_H */

#if defined(_IO_H) && !defined(_PARTS_UCHAR_IO_H)
#include <parts/uchar/io.h>
#endif /* _IO_H && !_PARTS_UCHAR_IO_H */

#if defined(_PROCESS_H) && !defined(_PARTS_UCHAR_PROCESS_H)
#include <parts/uchar/process.h>
#endif /* _PROCESS_H && !_PARTS_UCHAR_PROCESS_H */

#if defined(_STDIO_H) && !defined(_PARTS_UCHAR_STDIO_H)
#include <parts/uchar/stdio.h>
#endif /* _STDIO_H && !_PARTS_UCHAR_STDIO_H */

#if defined(_STDLIB_H) && !defined(_PARTS_UCHAR_STDLIB_H)
#include <parts/uchar/stdlib.h>
#endif /* _STDLIB_H && !_PARTS_UCHAR_STDLIB_H */

#if defined(_STRING_H) && !defined(_PARTS_UCHAR_STRING_H)
#include <parts/uchar/string.h>
#endif /* _STRING_H && !_PARTS_UCHAR_STRING_H */

#if defined(_SYS_MMAN_H) && !defined(_PARTS_UCHAR_SYS_MMAN_H)
#include <parts/uchar/sys/mman.h>
#endif /* _SYS_MMAN_H && !_PARTS_UCHAR_SYS_MMAN_H */

#if defined(_SYS_STAT_H) && !defined(_PARTS_UCHAR_SYS_STAT_H)
#include <parts/uchar/sys/stat.h>
#endif /* _SYS_STAT_H && !_PARTS_UCHAR_SYS_STAT_H */

#if defined(_TIME_H) && !defined(_PARTS_UCHAR_TIME_H)
#include <parts/uchar/time.h>
#endif /* _TIME_H && !_PARTS_UCHAR_TIME_H */

#if defined(_UNISTD_H) && !defined(_PARTS_UCHAR_UNISTD_H)
#include <parts/uchar/unistd.h>
#endif /* _UNISTD_H && !_PARTS_UCHAR_UNISTD_H */

#if defined(_UTIME_H) && !defined(_PARTS_UCHAR_UTIME_H)
#include <parts/uchar/utime.h>
#endif /* _UTIME_H && !_PARTS_UCHAR_UTIME_H */

#if defined(_WCHAR_H) && !defined(_PARTS_UCHAR_WCHAR_H)
#include <parts/uchar/wchar.h>
#endif /* _WCHAR_H && !_PARTS_UCHAR_WCHAR_H */

#if defined(_WCTYPE_H) && !defined(_PARTS_UCHAR_WCTYPE_H)
#include <parts/uchar/wctype.h>
#endif /* _WCTYPE_H && !_PARTS_UCHAR_WCTYPE_H */

#endif /* __USE_UTF */

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CUCHAR
#undef _UCHAR_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CUCHAR */
#endif /* !_UCHAR_H */
