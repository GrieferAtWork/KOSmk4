/* HASH CRC-32:0xef4d3b10 */
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
#ifndef __local__vfprintf_p_defined
#if (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked)
#define __local__vfprintf_p_defined 1
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_vfprintf_p) __ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF_P(2, 0) __STDC_INT_AS_SIZE_T
(__LIBCCALL __LIBC_LOCAL_NAME(_vfprintf_p))(__FILE *__restrict __stream,
                                            char const *__restrict __format,
                                            __builtin_va_list __args) __THROWS(...) {
#line 2591 "kos/src/libc/magic/stdio.c"
	(void)__stream;
	(void)__format;
	(void)__args;
	/* TODO */
	__COMPILER_IMPURE();
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) */
#endif /* !__local__vfprintf_p_defined */
