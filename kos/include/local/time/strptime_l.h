/* HASH CRC-32:0x1d08db5 */
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
#ifndef __local_strptime_l_defined
#define __local_strptime_l_defined 1
/* Dependency: "strptime" from "time" */
#ifndef ____localdep_strptime_defined
#define ____localdep_strptime_defined 1
#if defined(__CRT_HAVE_strptime)
/* Parse S according to FORMAT and store binary time information in TP.
 * The return value is a pointer to the first unparsed character in S */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),char *,__NOTHROW_NCX,__localdep_strptime,(char const *__restrict __s, char const *__restrict __format, struct tm *__restrict __tp),strptime,(__s,__format,__tp))
#else /* LIBC: strptime */
#include <local/time/strptime.h>
/* Parse S according to FORMAT and store binary time information in TP.
 * The return value is a pointer to the first unparsed character in S */
#define __localdep_strptime (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strptime))
#endif /* strptime... */
#endif /* !____localdep_strptime_defined */

__NAMESPACE_LOCAL_BEGIN
/* Similar to `strptime' but take the information from
 * the provided locale and not the global locale */
__LOCAL_LIBC(strptime_l) __ATTR_NONNULL((1, 2, 3)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strptime_l))(char const *__restrict __s,
                                                        char const *__restrict __format,
                                                        struct tm *__restrict __tp,
                                                        __locale_t __locale) {
#line 1522 "kos/src/libc/magic/time.c"
	(void)__locale;
	return __localdep_strptime(__s, __format, __tp);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_strptime_l_defined */
