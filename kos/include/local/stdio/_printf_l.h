/* HASH CRC-32:0xd490df51 */
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
#ifndef __local__printf_l_defined
#if ((!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)|| defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked))) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || (__has_builtin(__builtin_vfprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vfprintf)) || (defined(__CRT_HAVE_vfprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s)) || (__has_builtin(__builtin_vprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vprintf)) || (defined(__CRT_HAVE_vprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vprintf_s)) || defined(__CRT_HAVE__vprintf_l) || defined(__CRT_HAVE__vprintf_s_l))
#define __local__printf_l_defined 1
#include <kos/anno.h>
/* Dependency: "_vprintf_l" from "stdio" */
#ifndef ____localdep__vprintf_l_defined
#define ____localdep__vprintf_l_defined 1
#if defined(__CRT_HAVE__vprintf_l)
__CREDIRECT(__ATTR_NONNULL((1)) __ATTR_LIBC_PRINTF(1, 0),__STDC_INT_AS_SIZE_T,,__localdep__vprintf_l,(char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),_vprintf_l,(__format,__locale,__args)) __THROWS(...)
#elif defined(__CRT_HAVE__vprintf_s_l)
__CREDIRECT(__ATTR_NONNULL((1)) __ATTR_LIBC_PRINTF(1, 0),__STDC_INT_AS_SIZE_T,,__localdep__vprintf_l,(char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),_vprintf_s_l,(__format,__locale,__args)) __THROWS(...)
#elif (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)|| defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked))) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || (__has_builtin(__builtin_vfprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vfprintf)) || (defined(__CRT_HAVE_vfprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s)) || (__has_builtin(__builtin_vprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vprintf)) || (defined(__CRT_HAVE_vprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vprintf_s))
#include <local/stdio/_vprintf_l.h>
#define __localdep__vprintf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vprintf_l))
#else /* CUSTOM: _vprintf_l */
#undef ____localdep__vprintf_l_defined
#endif /* _vprintf_l... */
#endif /* !____localdep__vprintf_l_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_printf_l) __ATTR_NONNULL((1)) __ATTR_LIBC_PRINTF(1, 3) __STDC_INT_AS_SIZE_T
(__VLIBCCALL __LIBC_LOCAL_NAME(_printf_l))(char const *__restrict __format,
                                           __locale_t __locale,
                                           ...) __THROWS(...) {
#line 2470 "kos/src/libc/magic/stdio.c"
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __locale);
	__result = __localdep__vprintf_l(__format, __locale, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* ((!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)|| defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked))) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || (__has_builtin(__builtin_vfprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vfprintf)) || (defined(__CRT_HAVE_vfprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s)) || (__has_builtin(__builtin_vprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vprintf)) || (defined(__CRT_HAVE_vprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vprintf_s)) || defined(__CRT_HAVE__vprintf_l) || defined(__CRT_HAVE__vprintf_s_l)) */
#endif /* !__local__printf_l_defined */
