/* HASH CRC-32:0xcc68ee97 */
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
#ifndef __local__printf_s_l_defined
#if defined(__CRT_HAVE__vprintf_s_l) || defined(__CRT_HAVE__vprintf_l) || (!defined(__NO_STDSTREAMS) && ((defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked))) || defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vprintf_s) || defined(__CRT_HAVE_vprintf_unlocked)
#define __local__printf_s_l_defined 1
#include <__crt.h>
#include <kos/anno.h>
/* Dependency: "_vprintf_s_l" from "stdio" */
#ifndef ____localdep__vprintf_s_l_defined
#define ____localdep__vprintf_s_l_defined 1
#ifdef __CRT_HAVE__vprintf_s_l
__CREDIRECT(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,,__localdep__vprintf_s_l,(char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),_vprintf_s_l,(__format,__locale,__args)) __THROWS(...)
#elif defined(__CRT_HAVE__vprintf_l)
__CREDIRECT(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,,__localdep__vprintf_s_l,(char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),_vprintf_l,(__format,__locale,__args)) __THROWS(...)
#elif (!defined(__NO_STDSTREAMS) && ((defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked))) || defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vprintf_s) || defined(__CRT_HAVE_vprintf_unlocked)
#include <local/stdio/_vprintf_l.h>
#define __localdep__vprintf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vprintf_l))
#else /* CUSTOM: _vprintf_l */
#undef ____localdep__vprintf_s_l_defined
#endif /* _vprintf_s_l... */
#endif /* !____localdep__vprintf_s_l_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_printf_s_l) __ATTR_LIBC_PRINTF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T
(__VLIBCCALL __LIBC_LOCAL_NAME(_printf_s_l))(char const *__restrict __format,
                                             __locale_t __locale,
                                             ...) __THROWS(...) {
#line 2561 "kos/src/libc/magic/stdio.c"
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __locale);
	__result = __localdep__vprintf_s_l(__format, __locale, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE__vprintf_s_l || __CRT_HAVE__vprintf_l || (!__NO_STDSTREAMS && ((__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked)) || __CRT_HAVE_vprintf || __CRT_HAVE_vprintf_s || __CRT_HAVE_vprintf_unlocked */
#endif /* !__local__printf_s_l_defined */
