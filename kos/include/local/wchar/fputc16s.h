/* HASH CRC-32:0x1e57e009 */
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
#ifndef __local_fputc16s_defined
#if defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked)
#define __local_fputc16s_defined 1
#include <kos/anno.h>
/* Dependency: "file_wprinter" from "wchar" */
#ifndef ____localdep_file_c16printer_defined
#define ____localdep_file_c16printer_defined 1
#if defined(__CRT_HAVE_file_wprinter) && (__SIZEOF_WCHAR_T__ == 2)
/* For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_file_c16printer,(void *__arg, __CHAR16_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_wprinter_unlocked) && defined(__USE_STDIO_UNLOCKED) && (__SIZEOF_WCHAR_T__ == 2)
/* For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_file_c16printer,(void *__arg, __CHAR16_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$file_wprinter_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_file_c16printer,(void *__arg, __CHAR16_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_wprinter_unlocked) && (__SIZEOF_WCHAR_T__ == 2)
/* For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_file_c16printer,(void *__arg, __CHAR16_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$file_wprinter_unlocked)
/* For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_file_c16printer,(void *__arg, __CHAR16_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$file_wprinter)
/* For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_file_c16printer,(void *__arg, __CHAR16_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/file_wprinter.h>
/* For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
#define __localdep_file_c16printer(arg, data, datalen) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_wprinter))(arg, (__WCHAR_TYPE__ const *)(data), datalen)
#else /* LIBC: file_c16printer */
#include <local/wchar/file_c16printer.h>
/* For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
#define __localdep_file_c16printer (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_c16printer))
#endif /* LIBC: file_c16printer */
#else /* CUSTOM: file_wprinter */
#undef ____localdep_file_c16printer_defined
#endif /* file_c16printer... */
#endif /* !____localdep_file_c16printer_defined */

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
#define __localdep_c16len(string) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslen))((__WCHAR_TYPE__ const *)(string))
#else /* LIBC: c16len */
#include <local/wchar/c16len.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_c16len (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16len))
#endif /* c16len... */
#endif /* !____localdep_c16len_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fputc16s) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(__LIBDCALL __LIBC_LOCAL_NAME(fputc16s))(__CHAR16_TYPE__ const *__restrict __string,
                                         __FILE *__restrict __stream) __THROWS(...) {
#line 544 "kos/src/libc/magic/wchar.c"
	__STDC_INT_AS_SIZE_T __result;
	__result = __localdep_file_c16printer(__stream, __string, __localdep_c16len(__string));
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_fputwc || __CRT_HAVE_putwc || __CRT_HAVE_file_wprinter || __CRT_HAVE_file_wprinter_unlocked */
#endif /* !__local_fputc16s_defined */
