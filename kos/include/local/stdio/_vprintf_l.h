/* HASH CRC-32:0x99eaab49 */
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
#ifndef __local__vprintf_l_defined
#if (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)|| defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked))) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || (__has_builtin(__builtin_vfprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vfprintf)) || (defined(__CRT_HAVE_vfprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s)) || (__has_builtin(__builtin_vprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vprintf)) || (defined(__CRT_HAVE_vprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vprintf_s))
#define __local__vprintf_l_defined 1
#include <kos/anno.h>
/* Dependency: "vprintf" from "stdio" */
#ifndef ____localdep_vprintf_defined
#define ____localdep_vprintf_defined 1
#if __has_builtin(__builtin_vprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vprintf)
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__FORCELOCAL __ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__LIBCCALL __localdep_vprintf)(char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return __builtin_vprintf(__format, __args); }
#elif defined(__CRT_HAVE_vprintf_unlocked) && (defined(__USE_STDIO_UNLOCKED))
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,,__localdep_vprintf,(char const *__restrict __format, __builtin_va_list __args),vprintf_unlocked,(__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_vprintf)
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,,__localdep_vprintf,(char const *__restrict __format, __builtin_va_list __args),vprintf,(__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_vprintf_s)
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,,__localdep_vprintf,(char const *__restrict __format, __builtin_va_list __args),vprintf_s,(__format,__args)) __THROWS(...)
#elif !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)|| defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked))) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || (__has_builtin(__builtin_vfprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vfprintf)) || (defined(__CRT_HAVE_vfprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s))
#include <local/stdio/vprintf.h>
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
#define __localdep_vprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vprintf))
#else /* CUSTOM: vprintf */
#undef ____localdep_vprintf_defined
#endif /* vprintf... */
#endif /* !____localdep_vprintf_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_vprintf_l) __ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T
(__LIBCCALL __LIBC_LOCAL_NAME(_vprintf_l))(char const *__restrict __format,
                                           __locale_t __locale,
                                           __builtin_va_list __args) __THROWS(...) {
#line 2333 "kos/src/libc/magic/stdio.c"
	(void)__locale;
	return __localdep_vprintf(__format, __args);
}
__NAMESPACE_LOCAL_END
#endif /* (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)|| defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked))) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || (__has_builtin(__builtin_vfprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vfprintf)) || (defined(__CRT_HAVE_vfprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s)) || (__has_builtin(__builtin_vprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vprintf)) || (defined(__CRT_HAVE_vprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vprintf_s)) */
#endif /* !__local__vprintf_l_defined */
