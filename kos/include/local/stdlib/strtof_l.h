/* HASH CRC-32:0xd6fcd884 */
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
#ifndef __local_strtof_l_defined
#define __local_strtof_l_defined 1
/* Dependency: "strtof" from "stdlib" */
#ifndef ____localdep_strtof_defined
#define ____localdep_strtof_defined 1
#ifdef __std___localdep_strtof_defined
__NAMESPACE_STD_USING(__localdep_strtof)
#elif defined(__CRT_HAVE_strtof)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),float,__NOTHROW_NCX,__localdep_strtof,(char const *__restrict __nptr, char **__endptr),strtof,(__nptr,__endptr))
#else /* LIBC: strtof */
#include <local/stdlib/strtof.h>
#define __localdep_strtof (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtof))
#endif /* strtof... */
#endif /* !____localdep_strtof_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strtof_l) __ATTR_NONNULL((1)) float
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtof_l))(char const *__restrict __nptr,
                                                      char **__endptr,
                                                      __locale_t __locale) {
#line 1671 "kos/src/libc/magic/stdlib.c"
	(void)__locale;
	return __localdep_strtof(__nptr, __endptr);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_strtof_l_defined */
