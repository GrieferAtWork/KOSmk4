/* HASH CRC-32:0x28486ac2 */
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
#ifndef __local_atof_defined
#define __local_atof_defined 1
/* Dependency: "strtod" from "stdlib" */
#ifndef ____localdep_strtod_defined
#define ____localdep_strtod_defined 1
#if defined(__CRT_HAVE_strtod)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),double,__NOTHROW_NCX,__localdep_strtod,(char const *__restrict __nptr, char **__endptr),strtod,(__nptr,__endptr))
#elif defined(__CRT_HAVE_strtold) && (__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),double,__NOTHROW_NCX,__localdep_strtod,(char const *__restrict __nptr, char **__endptr),strtold,(__nptr,__endptr))
#else /* LIBC: strtod */
#include <local/stdlib/strtod.h>
#define __localdep_strtod (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtod))
#endif /* strtod... */
#endif /* !____localdep_strtod_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(atof) __ATTR_LEAF __ATTR_WUNUSED __ATTR_NONNULL((1)) double
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(atof))(char const *__restrict __nptr) {
#line 818 "kos/src/libc/magic/stdlib.c"
	return __localdep_strtod(__nptr, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_atof_defined */
