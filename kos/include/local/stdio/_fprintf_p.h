/* HASH CRC-32:0x77097be2 */
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
#ifndef __local__fprintf_p_defined
#if defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked))) || defined(__CRT_HAVE__vfprintf_p)
#define __local__fprintf_p_defined 1
#include <kos/anno.h>
/* Dependency: "_vfprintf_p" from "stdio" */
#ifndef ____localdep__vfprintf_p_defined
#define ____localdep__vfprintf_p_defined 1
#ifdef __CRT_HAVE__vfprintf_p
__CREDIRECT(__ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF_P(2, 0),__STDC_INT_AS_SIZE_T,,__localdep__vfprintf_p,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),_vfprintf_p,(__stream,__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked)))
#include <local/stdio/_vfprintf_p.h>
#define __localdep__vfprintf_p (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vfprintf_p))
#else /* CUSTOM: _vfprintf_p */
#undef ____localdep__vfprintf_p_defined
#endif /* _vfprintf_p... */
#endif /* !____localdep__vfprintf_p_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_fprintf_p) __ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF_P(2, 3) __STDC_INT_AS_SIZE_T
(__VLIBCCALL __LIBC_LOCAL_NAME(_fprintf_p))(__FILE *__restrict __stream,
                                            char const *__restrict __format,
                                            ...) __THROWS(...) {
#line 2534 "kos/src/libc/magic/stdio.c"
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep__vfprintf_p(__stream, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked))) || defined(__CRT_HAVE__vfprintf_p) */
#endif /* !__local__fprintf_p_defined */
