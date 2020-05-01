/* HASH CRC-32:0x80e9c60d */
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
#ifndef __local_fputc16s_unlocked_defined
#if defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter)
#define __local_fputc16s_unlocked_defined 1
#include <__crt.h>
#include <kos/anno.h>
/* Dependency: "file_wprinter_unlocked" from "wchar" */
#ifndef ____localdep_file_c16printer_unlocked_defined
#define ____localdep_file_c16printer_unlocked_defined 1
#if defined(__CRT_HAVE_file_wprinter_unlocked) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `file_c16printer()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_file_c16printer_unlocked,(void *__arg, __CHAR16_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_wprinter) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `file_c16printer()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_file_c16printer_unlocked,(void *__arg, __CHAR16_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$file_wprinter)
/* Same as `file_c16printer()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_file_c16printer_unlocked,(void *__arg, __CHAR16_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$file_wprinter_unlocked)
/* Same as `file_c16printer()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_file_c16printer_unlocked,(void *__arg, __CHAR16_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/file_wprinter_unlocked.h>
/* Same as `file_c16printer()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
#define __localdep_file_c16printer_unlocked (*(__SSIZE_TYPE__(__LIBCCALL*)(void *, __CHAR16_TYPE__ const *__restrict, __SIZE_TYPE__))&(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_wprinter_unlocked)))
#else /* LIBC: file_c16printer_unlocked */
#include <local/wchar/file_c16printer_unlocked.h>
/* Same as `file_c16printer()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
#define __localdep_file_c16printer_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_c16printer_unlocked))
#endif /* LIBC: file_c16printer_unlocked */
#else /* CUSTOM: file_wprinter_unlocked */
#undef ____localdep_file_c16printer_unlocked_defined
#endif /* file_c16printer_unlocked... */
#endif /* !____localdep_file_c16printer_unlocked_defined */

/* Dependency: "wcslen" from "wchar" */
#ifndef ____localdep_c16len_defined
#define ____localdep_c16len_defined 1
#if defined(__CRT_HAVE_wcslen) && (__SIZEOF_WCHAR_T__ == 2)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16len,(__CHAR16_TYPE__ const *__restrict __string),wcslen,(__string))
#elif defined(__CRT_HAVE_DOS$wcslen)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16len,(__CHAR16_TYPE__ const *__restrict __string),wcslen,(__string))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcslen.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_c16len (*(__SIZE_TYPE__(__LIBCCALL*)(__CHAR16_TYPE__ const *__restrict))&(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslen)))
#else /* LIBC: c16len */
#include <local/wchar/c16len.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_c16len (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16len))
#endif /* c16len... */
#endif /* !____localdep_c16len_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fputc16s_unlocked) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(__LIBDCALL __LIBC_LOCAL_NAME(fputc16s_unlocked))(__CHAR16_TYPE__ const *__restrict __string,
                                                  __FILE *__restrict __stream) __THROWS(...) {
#line 1140 "kos/src/libc/magic/wchar.c"
	__STDC_INT_AS_SIZE_T __result;
	__result = __localdep_file_c16printer_unlocked(__stream, __string, __localdep_c16len(__string));
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_fputwc_unlocked || __CRT_HAVE__fputwc_nolock || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_file_wprinter */
#endif /* !__local_fputc16s_unlocked_defined */
