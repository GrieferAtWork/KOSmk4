/* HASH CRC-32:0x316e4e43 */
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
#ifndef _UCHAR_H
#define _UCHAR_H 1

#ifdef _CXX_STDONLY_CUCHAR
#ifdef __CXX_SYSTEM_HEADER
#undef _UCHAR_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "uchar.h" after "cuchar" */
#ifndef __mbstate_t_defined
#define __mbstate_t_defined 1
__NAMESPACE_STD_USING(mbstate_t)
#endif /* !__mbstate_t_defined */
#ifndef __size_t_defined
#define __size_t_defined 1
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
#include <bits/mbstate.h>

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __std_mbstate_t_defined
#define __std_mbstate_t_defined 1
__NAMESPACE_STD_BEGIN
typedef __mbstate_t mbstate_t;
__NAMESPACE_STD_END
#endif /* !__std_mbstate_t_defined */

#ifndef __CXX_SYSTEM_HEADER
#ifndef __mbstate_t_defined
#define __mbstate_t_defined 1
__NAMESPACE_STD_USING(mbstate_t)
#endif /* !__mbstate_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */


/* Define `size_t' */
#ifndef __std_size_t_defined
#define __std_size_t_defined 1
__NAMESPACE_STD_BEGIN
typedef __SIZE_TYPE__ size_t;
__NAMESPACE_STD_END
#endif /* !__std_size_t_defined */
#ifndef __CXX_SYSTEM_HEADER
#ifndef __size_t_defined
#define __size_t_defined 1
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */

#ifndef __char16_t_defined
#define __char16_t_defined 1
typedef __CHAR16_TYPE__ char16_t;
typedef __CHAR32_TYPE__ char32_t;
#endif /* !__char16_t_defined */

/* Libc uses utf16/utf32 to encode/decode char16_t and char32_t */
#define __STD_UTF_16__ 1
#define __STD_UTF_32__ 1

__NAMESPACE_STD_BEGIN
#ifdef __CRT_HAVE_mbrtoc16
__CDECLARE(,size_t,__NOTHROW_NCX,mbrtoc16,(char16_t *__pc16, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs),(__pc16,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_mbrtowc) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(,size_t,__NOTHROW_NCX,mbrtoc16,(char16_t *__pc16, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs),mbrtowc,(__pc16,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE___mbrtowc) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(,size_t,__NOTHROW_NCX,mbrtoc16,(char16_t *__pc16, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs),__mbrtowc,(__pc16,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_DOS$mbrtowc) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,,size_t,__NOTHROW_NCX,__LIBCCALL,mbrtoc16,(char16_t *__pc16, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs),DOS$mbrtowc,(__pc16,__str,__maxlen,__mbs))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_STD_END
#include <local/wchar/mbrtowc.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL size_t __NOTHROW_NCX(__LIBCCALL mbrtoc16)(char16_t *__pc16, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbrtowc))((__WCHAR_TYPE__ *)__pc16, __str, __maxlen, __mbs); }
#else /* ... */
__NAMESPACE_STD_END
#include <local/uchar/uchar_mbrtoc16.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL size_t __NOTHROW_NCX(__LIBCCALL mbrtoc16)(char16_t *__pc16, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(uchar_mbrtoc16))(__pc16, __str, __maxlen, __mbs); }
#endif /* !... */
#ifdef __CRT_HAVE_mbrtoc32
__CDECLARE(,size_t,__NOTHROW_NCX,mbrtoc32,(char32_t *__pc32, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs),(__pc32,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_mbrtowc) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(,size_t,__NOTHROW_NCX,mbrtoc32,(char32_t *__pc32, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs),mbrtowc,(__pc32,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE___mbrtowc) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(,size_t,__NOTHROW_NCX,mbrtoc32,(char32_t *__pc32, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs),__mbrtowc,(__pc32,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_DOS$mbrtowc) && defined(__PE__) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,,size_t,__NOTHROW_NCX,__LIBCCALL,mbrtoc32,(char32_t *__pc32, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs),KOS$mbrtowc,(__pc32,__str,__maxlen,__mbs))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_STD_END
#include <local/wchar/mbrtowc.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL size_t __NOTHROW_NCX(__LIBCCALL mbrtoc32)(char32_t *__pc32, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbrtowc))((__WCHAR_TYPE__ *)__pc32, __str, __maxlen, __mbs); }
#else /* ... */
__NAMESPACE_STD_END
#include <local/uchar/uchar_mbrtoc32.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL size_t __NOTHROW_NCX(__LIBCCALL mbrtoc32)(char32_t *__pc32, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(uchar_mbrtoc32))(__pc32, __str, __maxlen, __mbs); }
#endif /* !... */
#ifdef __CRT_HAVE_c16rtomb
__CDECLARE(,size_t,__NOTHROW_NCX,c16rtomb,(char *__restrict __str, char16_t __c16, mbstate_t *__mbs),(__str,__c16,__mbs))
#elif defined(__CRT_HAVE_wcrtomb) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(,size_t,__NOTHROW_NCX,c16rtomb,(char *__restrict __str, char16_t __c16, mbstate_t *__mbs),wcrtomb,(__str,__c16,__mbs))
#elif defined(__CRT_HAVE_DOS$wcrtomb) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,,size_t,__NOTHROW_NCX,__LIBCCALL,c16rtomb,(char *__restrict __str, char16_t __c16, mbstate_t *__mbs),DOS$wcrtomb,(__str,__c16,__mbs))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_STD_END
#include <local/wchar/wcrtomb.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL size_t __NOTHROW_NCX(__LIBCCALL c16rtomb)(char *__restrict __str, char16_t __c16, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcrtomb))(__str, (__WCHAR_TYPE__)__c16, __mbs); }
#else /* ... */
__NAMESPACE_STD_END
#include <local/uchar/uchar_c16rtomb.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL size_t __NOTHROW_NCX(__LIBCCALL c16rtomb)(char *__restrict __str, char16_t __c16, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(uchar_c16rtomb))(__str, __c16, __mbs); }
#endif /* !... */
#ifdef __CRT_HAVE_c32rtomb
__CDECLARE(,size_t,__NOTHROW_NCX,c32rtomb,(char *__restrict __str, char32_t __c32, mbstate_t *__mbs),(__str,__c32,__mbs))
#elif defined(__CRT_HAVE_wcrtomb) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(,size_t,__NOTHROW_NCX,c32rtomb,(char *__restrict __str, char32_t __c32, mbstate_t *__mbs),wcrtomb,(__str,__c32,__mbs))
#elif defined(__CRT_HAVE_DOS$wcrtomb) && defined(__PE__) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,,size_t,__NOTHROW_NCX,__LIBCCALL,c32rtomb,(char *__restrict __str, char32_t __c32, mbstate_t *__mbs),KOS$wcrtomb,(__str,__c32,__mbs))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_STD_END
#include <local/wchar/wcrtomb.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL size_t __NOTHROW_NCX(__LIBCCALL c32rtomb)(char *__restrict __str, char32_t __c32, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcrtomb))(__str, (__WCHAR_TYPE__)__c32, __mbs); }
#else /* ... */
__NAMESPACE_STD_END
#include <local/uchar/uchar_c32rtomb.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL size_t __NOTHROW_NCX(__LIBCCALL c32rtomb)(char *__restrict __str, char32_t __c32, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(uchar_c32rtomb))(__str, __c32, __mbs); }
#endif /* !... */
__NAMESPACE_STD_END
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(mbrtoc16)
__NAMESPACE_STD_USING(mbrtoc32)
__NAMESPACE_STD_USING(c16rtomb)
__NAMESPACE_STD_USING(c32rtomb)
#endif /* !__CXX_SYSTEM_HEADER */

#endif /* __CC__ */

__SYSDECL_END

#ifdef __USE_UTF
#if defined(_STRING_H) && !defined(_PARTS_UCHAR_STRING_H)
#include <parts/uchar/string.h>
#endif /* _STRING_H && !_PARTS_UCHAR_STRING_H */

#if defined(_PROCESS_H) && !defined(_PARTS_UCHAR_PROCESS_H)
#include <parts/uchar/process.h>
#endif /* _PROCESS_H && !_PARTS_UCHAR_PROCESS_H */

#if defined(_STDLIB_H) && !defined(_PARTS_UCHAR_STDLIB_H)
#include <parts/uchar/stdlib.h>
#endif /* _STDLIB_H && !_PARTS_UCHAR_STDLIB_H */

#if defined(_FCNTL_H) && !defined(_PARTS_UCHAR_FCNTL_H)
#include <parts/uchar/fcntl.h>
#endif /* _FCNTL_H && !_PARTS_UCHAR_FCNTL_H */

#if defined(_UNISTD_H) && !defined(_PARTS_UCHAR_UNISTD_H)
#include <parts/uchar/unistd.h>
#endif /* _UNISTD_H && !_PARTS_UCHAR_UNISTD_H */

#if defined(_UTIME_H) && !defined(_PARTS_UCHAR_UTIME_H)
#include <parts/uchar/utime.h>
#endif /* _UTIME_H && !_PARTS_UCHAR_UTIME_H */

#if defined(_FORMAT_PRINTER_H) && !defined(_PARTS_UCHAR_FORMATPRINTER_H)
#include <parts/uchar/format-printer.h>
#endif /* _FORMAT_PRINTER_H && !_PARTS_UCHAR_FORMATPRINTER_H */

#if defined(_IO_H) && !defined(_PARTS_UCHAR_IO_H)
#include <parts/uchar/io.h>
#endif /* _IO_H && !_PARTS_UCHAR_IO_H */

#if defined(_STDIO_H) && !defined(_PARTS_UCHAR_STDIO_H)
#include <parts/uchar/stdio.h>
#endif /* _STDIO_H && !_PARTS_UCHAR_STDIO_H */

#if defined(_TIME_H) && !defined(_PARTS_UCHAR_TIME_H)
#include <parts/uchar/time.h>
#endif /* _TIME_H && !_PARTS_UCHAR_TIME_H */

#if defined(_SYS_STAT_H) && !defined(_PARTS_UCHAR_SYS_STAT_H)
#include <parts/uchar/sys/stat.h>
#endif /* _SYS_STAT_H && !_PARTS_UCHAR_SYS_STAT_H */

#if defined(_SYS_MMAN_H) && !defined(_PARTS_UCHAR_SYS_MMAN_H)
#include <parts/uchar/sys/mman.h>
#endif /* _SYS_MMAN_H && !_PARTS_UCHAR_SYS_MMAN_H */

#if defined(_INTTYPES_H) && !defined(_PARTS_UCHAR_INTTYPES_H)
#include <parts/uchar/inttypes.h>
#endif /* _INTTYPES_H && !_PARTS_UCHAR_INTTYPES_H */

#if defined(_WCHAR_H) && !defined(_PARTS_UCHAR_WCHAR_H)
#include <parts/uchar/wchar.h>
#endif /* _WCHAR_H && !_PARTS_UCHAR_WCHAR_H */
#endif /* __USE_UTF */

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CUCHAR 1
#undef _UCHAR_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CUCHAR */
#endif /* !_UCHAR_H */
