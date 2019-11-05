/* HASH CRC-32:0x982dc20c */
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
#ifndef __local_wcstombs_s_defined
#define __local_wcstombs_s_defined 1
#include <parts/errno.h>
/* Dependency: "wcstombs" from "stdlib" */
#ifndef ____localdep_wcstombs_defined
#define ____localdep_wcstombs_defined 1
#ifdef __CRT_HAVE_wcstombs
__CREDIRECT(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcstombs,(char *__restrict __s, __WCHAR_TYPE__ const *__restrict __pwcs, __SIZE_TYPE__ __n),wcstombs,(__s,__pwcs,__n))
#else /* LIBC: wcstombs */
#include <local/stdlib/wcstombs.h>
#define __localdep_wcstombs (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstombs))
#endif /* wcstombs... */
#endif /* !____localdep_wcstombs_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wcstombs_s) __ATTR_NONNULL((1, 2, 4)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcstombs_s))(__SIZE_TYPE__ *__presult,
                                                        char *__buf,
                                                        __SIZE_TYPE__ __buflen,
                                                        __WCHAR_TYPE__ const *__src,
                                                        __SIZE_TYPE__ __maxlen) {
#line 2397 "kos/src/libc/magic/stdlib.c"
	if (!__presult || !__buf || !__src)
		return __EINVAL;
	if (__buflen < __localdep_wcstombs(__NULLPTR, __src, __maxlen))
		return __ERANGE;
	*__presult = __localdep_wcstombs(__buf, __src, __maxlen);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wcstombs_s_defined */
