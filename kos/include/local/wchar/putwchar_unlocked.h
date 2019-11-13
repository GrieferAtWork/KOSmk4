/* HASH CRC-32:0xec17b2c2 */
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
#ifndef __local_putwchar_unlocked_defined
#if (defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && !defined(__NO_STDSTREAMS)
#define __local_putwchar_unlocked_defined 1
#include <kos/anno.h>
/* Dependency: "fputwc_unlocked" */
#ifndef ____localdep_fputwc_unlocked_defined
#define ____localdep_fputwc_unlocked_defined 1
#ifdef __CRT_HAVE_fputwc_unlocked
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,,__localdep_fputwc_unlocked,(__WCHAR_TYPE__ __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__fputwc_nolock)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,,__localdep_fputwc_unlocked,(__WCHAR_TYPE__ __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream)) __THROWS(...)
#else /* LIBC: fputwc_unlocked */
#undef ____localdep_fputwc_unlocked_defined
#endif /* fputwc_unlocked... */
#endif /* !____localdep_fputwc_unlocked_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(putwchar_unlocked) __WINT_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(putwchar_unlocked))(__WCHAR_TYPE__ __wc) __THROWS(...) {
#line 1018 "kos/src/libc/magic/wchar.c"
	return __localdep_fputwc_unlocked(__wc, __LOCAL_stdin);
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && !defined(__NO_STDSTREAMS) */
#endif /* !__local_putwchar_unlocked_defined */
