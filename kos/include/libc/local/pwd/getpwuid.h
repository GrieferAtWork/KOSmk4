/* HASH CRC-32:0x54a0d7ee */
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
#ifndef __local_getpwuid_defined
#define __local_getpwuid_defined
#include <__crt.h>
#if defined(__CRT_HAVE_setpwent) && defined(__CRT_HAVE_getpwent)
#include <bits/crt/db/passwd.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getpwent_defined
#define __local___localdep_getpwent_defined
__CREDIRECT(,struct passwd *,__NOTHROW_RPC,__localdep_getpwent,(void),getpwent,())
#endif /* !__local___localdep_getpwent_defined */
#ifndef __local___localdep_setpwent_defined
#define __local___localdep_setpwent_defined
__CREDIRECT_VOID(,__NOTHROW_RPC,__localdep_setpwent,(void),setpwent,())
#endif /* !__local___localdep_setpwent_defined */
__LOCAL_LIBC(getpwuid) __ATTR_WUNUSED struct passwd *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(getpwuid))(__uid_t __uid) {
	struct passwd *__result;
	(__NAMESPACE_LOCAL_SYM __localdep_setpwent)();
	while ((__result = (__NAMESPACE_LOCAL_SYM __localdep_getpwent)()) != __NULLPTR) {
		if (__result->pw_uid == __uid)
			break;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getpwuid_defined
#define __local___localdep_getpwuid_defined
#define __localdep_getpwuid __LIBC_LOCAL_NAME(getpwuid)
#endif /* !__local___localdep_getpwuid_defined */
#else /* __CRT_HAVE_setpwent && __CRT_HAVE_getpwent */
#undef __local_getpwuid_defined
#endif /* !__CRT_HAVE_setpwent || !__CRT_HAVE_getpwent */
#endif /* !__local_getpwuid_defined */
