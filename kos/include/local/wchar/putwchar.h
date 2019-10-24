/* HASH CRC-32:0xebd5188e */
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
#ifndef __local_putwchar_defined
#include <__crt.h>
#if !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc))
#define __local_putwchar_defined 1
#include <kos/anno.h>
#include <local/stdstreams.h>
/* Dependency: "fputwc" */
#ifndef ____localdep_fputwc_defined
#define ____localdep_fputwc_defined 1
#ifdef __std___localdep_fputwc_defined
__NAMESPACE_STD_USING(__localdep_fputwc)
#elif defined(__CRT_HAVE_fputwc)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,,__localdep_fputwc,(__WCHAR_TYPE__ __wc, __FILE *__stream),fputwc,(__wc,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_putwc)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,,__localdep_fputwc,(__WCHAR_TYPE__ __wc, __FILE *__stream),putwc,(__wc,__stream)) __THROWS(...)
#else /* LIBC: fputwc */
#undef ____localdep_fputwc_defined
#endif /* fputwc... */
#endif /* !____localdep_fputwc_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(putwchar) __WINT_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(putwchar))(__WCHAR_TYPE__ __wc) __THROWS(...) {
#line 386 "kos/src/libc/magic/wchar.c"
	return __localdep_fputwc(__wc, __LOCAL_stdout);
}
__NAMESPACE_LOCAL_END
#endif /* !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) */
#endif /* !__local_putwchar_defined */
