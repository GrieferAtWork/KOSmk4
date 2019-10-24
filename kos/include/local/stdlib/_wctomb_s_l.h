/* HASH CRC-32:0xe240be39 */
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
#ifndef __local__wctomb_s_l_defined
#define __local__wctomb_s_l_defined 1
#include <parts/errno.h>
/* Dependency: "wctomb_s" from "stdlib" */
#ifndef ____localdep_wctomb_s_defined
#define ____localdep_wctomb_s_defined 1
#if defined(__CRT_HAVE_wctomb_s)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,__localdep_wctomb_s,(int *__presult, char *__buf, __SIZE_TYPE__ __buflen, __WCHAR_TYPE__ __wc),wctomb_s,(__presult,__buf,__buflen,__wc))
#else /* LIBC: wctomb_s */
#include <local/stdlib/wctomb_s.h>
#define __localdep_wctomb_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wctomb_s))
#endif /* wctomb_s... */
#endif /* !____localdep_wctomb_s_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_wctomb_s_l) __ATTR_NONNULL((1, 2)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_wctomb_s_l))(int *__presult,
                                                         char *__buf,
                                                         __SIZE_TYPE__ __buflen,
                                                         __WCHAR_TYPE__ __wc,
                                                         __locale_t __locale) {
#line 2235 "kos/src/libc/magic/stdlib.c"
	(void)__locale;
	return __localdep_wctomb_s(__presult, __buf, __buflen, __wc);
}
__NAMESPACE_LOCAL_END
#endif /* !__local__wctomb_s_l_defined */
