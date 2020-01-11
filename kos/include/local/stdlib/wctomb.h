/* HASH CRC-32:0xa365d5d9 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_wctomb_defined
#define __local_wctomb_defined 1
/* Dependency: "wcrtomb" from "wchar" */
#ifndef ____localdep_wcrtomb_defined
#define ____localdep_wcrtomb_defined 1
#ifdef __CRT_HAVE_wcrtomb
__CREDIRECT(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcrtomb,(char *__restrict __str, __WCHAR_TYPE__ __wc, __mbstate_t *__ps),wcrtomb,(__str,__wc,__ps))
#else /* LIBC: wcrtomb */
#include <local/wchar/wcrtomb.h>
#define __localdep_wcrtomb (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcrtomb))
#endif /* wcrtomb... */
#endif /* !____localdep_wcrtomb_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wctomb) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wctomb))(char *__str,
                                                    __WCHAR_TYPE__ __wc) {
#line 702 "kos/src/libc/magic/stdlib.c"
	return __localdep_wcrtomb(__str, __wc, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wctomb_defined */
