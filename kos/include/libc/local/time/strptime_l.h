/* HASH CRC-32:0x7906c855 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_strptime_l_defined
#define __local_strptime_l_defined
#include <__crt.h>
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strptime_defined
#define __local___localdep_strptime_defined
#ifdef __CRT_HAVE_strptime
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_OUT(3),char *,__NOTHROW_NCX,__localdep_strptime,(char const *__restrict __s, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm *__restrict __tp),strptime,(__s,__format,__tp))
#else /* __CRT_HAVE_strptime */
__NAMESPACE_LOCAL_END
#include <libc/local/time/strptime.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strptime __LIBC_LOCAL_NAME(strptime)
#endif /* !__CRT_HAVE_strptime */
#endif /* !__local___localdep_strptime_defined */
__LOCAL_LIBC(strptime_l) __ATTR_IN(1) __ATTR_IN(2) __ATTR_OUT(3) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strptime_l))(char const *__restrict __s, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm *__restrict __tp, __locale_t __locale) {
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep_strptime)(__s, __format, __tp);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strptime_l_defined
#define __local___localdep_strptime_l_defined
#define __localdep_strptime_l __LIBC_LOCAL_NAME(strptime_l)
#endif /* !__local___localdep_strptime_l_defined */
#endif /* !__local_strptime_l_defined */
