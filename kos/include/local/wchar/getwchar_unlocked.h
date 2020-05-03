/* HASH CRC-32:0x241a1d19 */
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
#ifndef __local_getwchar_unlocked_defined
#if (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE__fgetwc_nolock)) && !defined(__NO_STDSTREAMS)
#define __local_getwchar_unlocked_defined 1
#include <__crt.h>
#include <kos/anno.h>
/* Dependency: "fgetwc_unlocked" */
#ifndef ____localdep_fgetwc_unlocked_defined
#define ____localdep_fgetwc_unlocked_defined 1
#ifdef __CRT_HAVE_fgetwc_unlocked
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,,__localdep_fgetwc_unlocked,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__fgetwc_nolock)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,,__localdep_fgetwc_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream)) __THROWS(...)
#else /* LIBC: fgetwc_unlocked */
#undef ____localdep_fgetwc_unlocked_defined
#endif /* fgetwc_unlocked... */
#endif /* !____localdep_fgetwc_unlocked_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(getwchar_unlocked) __WINT_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(getwchar_unlocked))(void) __THROWS(...) {
#line 1051 "kos/src/libc/magic/wchar.c"
	return __localdep_fgetwc_unlocked(__LOCAL_stdin);
}
__NAMESPACE_LOCAL_END
#endif /* (__CRT_HAVE_fgetwc_unlocked || __CRT_HAVE__fgetwc_nolock) && !__NO_STDSTREAMS */
#endif /* !__local_getwchar_unlocked_defined */
