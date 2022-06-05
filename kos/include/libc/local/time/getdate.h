/* HASH CRC-32:0xe37fa3e6 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_getdate_defined
#define __local_getdate_defined
#include <__crt.h>
#include <libc/template/getdate_err.h>
#ifdef __LOCAL_getdate_err
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getdate_r_defined
#define __local___localdep_getdate_r_defined
#ifdef __CRT_HAVE_getdate_r
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_getdate_r,(char const *__restrict __string, struct __NAMESPACE_STD_SYM tm *__restrict __resbufp),getdate_r,(__string,__resbufp))
#else /* __CRT_HAVE_getdate_r */
__NAMESPACE_LOCAL_END
#include <libc/local/time/getdate_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_getdate_r __LIBC_LOCAL_NAME(getdate_r)
#endif /* !__CRT_HAVE_getdate_r */
#endif /* !__local___localdep_getdate_r_defined */
__LOCAL_LIBC(getdate) __ATTR_IN(1) struct __NAMESPACE_STD_SYM tm *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(getdate))(const char *__string) {
	static struct __NAMESPACE_STD_SYM tm __result;
	int __error = (__NAMESPACE_LOCAL_SYM __localdep_getdate_r)(__string, &__result);
	if (__error == 0)
		return &__result;
	__LOCAL_getdate_err = __error;
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getdate_defined
#define __local___localdep_getdate_defined
#define __localdep_getdate __LIBC_LOCAL_NAME(getdate)
#endif /* !__local___localdep_getdate_defined */
#else /* __LOCAL_getdate_err */
#undef __local_getdate_defined
#endif /* !__LOCAL_getdate_err */
#endif /* !__local_getdate_defined */
