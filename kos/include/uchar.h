/* HASH CRC-32:0xcc3a784 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
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
__CDECLARE(,size_t,__NOTHROW_NCX,mbrtoc16,(char16_t *__restrict __pc16, char const *__restrict __s, size_t __n, __mbstate_t *__restrict __mbs),(__pc16,__s,__n,__mbs))
#else /* LIBC: mbrtoc16 */
__NAMESPACE_STD_END
#include <local/uchar/mbrtoc16.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(mbrtoc16, __FORCELOCAL size_t __NOTHROW_NCX(__LIBCCALL mbrtoc16)(char16_t *__restrict __pc16, char const *__restrict __s, size_t __n, __mbstate_t *__restrict __mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbrtoc16))(__pc16, __s, __n, __mbs); })
#endif /* mbrtoc16... */
#ifdef __CRT_HAVE_mbrtoc32
__CDECLARE(,size_t,__NOTHROW_NCX,mbrtoc32,(char32_t *__restrict __pc32, char const *__restrict __s, size_t __n, __mbstate_t *__restrict __mbs),(__pc32,__s,__n,__mbs))
#else /* LIBC: mbrtoc32 */
__NAMESPACE_STD_END
#include <local/uchar/mbrtoc32.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(mbrtoc32, __FORCELOCAL size_t __NOTHROW_NCX(__LIBCCALL mbrtoc32)(char32_t *__restrict __pc32, char const *__restrict __s, size_t __n, __mbstate_t *__restrict __mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbrtoc32))(__pc32, __s, __n, __mbs); })
#endif /* mbrtoc32... */
#ifdef __CRT_HAVE_c16rtomb
__CDECLARE(,size_t,__NOTHROW_NCX,c16rtomb,(char *__restrict __s, char16_t __c16, __mbstate_t *__restrict __mbs),(__s,__c16,__mbs))
#else /* LIBC: c16rtomb */
__NAMESPACE_STD_END
#include <local/uchar/c16rtomb.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(c16rtomb, __FORCELOCAL size_t __NOTHROW_NCX(__LIBCCALL c16rtomb)(char *__restrict __s, char16_t __c16, __mbstate_t *__restrict __mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rtomb))(__s, __c16, __mbs); })
#endif /* c16rtomb... */
#ifdef __CRT_HAVE_c32rtomb
__CDECLARE(,size_t,__NOTHROW_NCX,c32rtomb,(char *__restrict __s, char32_t __c32, __mbstate_t *__restrict __mbs),(__s,__c32,__mbs))
#else /* LIBC: c32rtomb */
__NAMESPACE_STD_END
#include <local/uchar/c32rtomb.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(c32rtomb, __FORCELOCAL size_t __NOTHROW_NCX(__LIBCCALL c32rtomb)(char *__restrict __s, char32_t __c32, __mbstate_t *__restrict __mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32rtomb))(__s, __c32, __mbs); })
#endif /* c32rtomb... */
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
#endif

#if defined(_PROCESS_H) && !defined(_PARTS_UCHAR_PROCESS_H)
#include <parts/uchar/process.h>
#endif

#if defined(_STDLIB_H) && !defined(_PARTS_UCHAR_STDLIB_H)
#include <parts/uchar/stdlib.h>
#endif

#if defined(_FCNTL_H) && !defined(_PARTS_UCHAR_FCNTL_H)
#include <parts/uchar/fcntl.h>
#endif

#if defined(_UNISTD_H) && !defined(_PARTS_UCHAR_UNISTD_H)
#include <parts/uchar/unistd.h>
#endif

#if defined(_UTIME_H) && !defined(_PARTS_UCHAR_UTIME_H)
#include <parts/uchar/utime.h>
#endif

#if defined(_FORMAT_PRINTER_H) && !defined(_PARTS_UCHAR_FORMATPRINTER_H)
#include <parts/uchar/format-printer.h>
#endif

#if defined(_IO_H) && !defined(_PARTS_UCHAR_IO_H)
#include <parts/uchar/io.h>
#endif

#if defined(_STDIO_H) && !defined(_PARTS_UCHAR_STDIO_H)
#include <parts/uchar/stdio.h>
#endif

#if defined(_TIME_H) && !defined(_PARTS_UCHAR_TIME_H)
#include <parts/uchar/time.h>
#endif

#if defined(_SYS_STAT_H) && !defined(_PARTS_UCHAR_SYS_STAT_H)
#include <parts/uchar/sys/stat.h>
#endif

#if defined(_SYS_MMAN_H) && !defined(_PARTS_UCHAR_SYS_MMAN_H)
#include <parts/uchar/sys/mman.h>
#endif

#if defined(_INTTYPES_H) && !defined(_PARTS_UCHAR_INTTYPES_H)
#include <parts/uchar/inttypes.h>
#endif

#endif /* __USE_UTF */

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CUCHAR 1
#undef _UCHAR_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CUCHAR */
#endif /* !_UCHAR_H */
