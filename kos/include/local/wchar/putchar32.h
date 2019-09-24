/* HASH CRC-32:0x4ddae6f2 */
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
#ifndef __local_putchar32_defined
#include <features.h>
#if !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc))
#define __local_putchar32_defined 1
#include <kos/anno.h>
#include <local/stdstreams.h>
/* Dependency: "fputwc" */
#ifndef ____localdep_fputc32_defined
#define ____localdep_fputc32_defined 1
#if defined(__CRT_HAVE_fputwc) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_fputc32,(__CHAR32_TYPE__ __wc, __FILE *__stream),fputwc,(__wc,__stream))
#elif defined(__CRT_HAVE_putwc) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_fputc32,(__CHAR32_TYPE__ __wc, __FILE *__stream),putwc,(__wc,__stream))
#else /* LIBC: fputc32 */
#undef ____localdep_fputc32_defined
#endif /* fputc32... */
#endif /* !____localdep_fputc32_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(putchar32) __WINT_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(putchar32))(__CHAR32_TYPE__ __wc) __THROWS(...) {
#line 381 "kos/src/libc/magic/wchar.c"
	return __localdep_fputc32(__wc, __LOCAL_stdout);
}
__NAMESPACE_LOCAL_END
#endif /* !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) */
#endif /* !__local_putchar32_defined */
