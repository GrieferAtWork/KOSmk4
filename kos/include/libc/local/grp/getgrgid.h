/* HASH CRC-32:0x978d8c4a */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_getgrgid_defined
#define __local_getgrgid_defined
#include <__crt.h>
#if defined(__CRT_HAVE_setgrent) && defined(__CRT_HAVE_getgrent)
#include <bits/crt/db/group.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getgrent_defined
#define __local___localdep_getgrent_defined
__CREDIRECT(__ATTR_WUNUSED,struct group *,__NOTHROW_RPC,__localdep_getgrent,(void),getgrent,())
#endif /* !__local___localdep_getgrent_defined */
#ifndef __local___localdep_setgrent_defined
#define __local___localdep_setgrent_defined
__CREDIRECT_VOID(,__NOTHROW_RPC,__localdep_setgrent,(void),setgrent,())
#endif /* !__local___localdep_setgrent_defined */
__LOCAL_LIBC(getgrgid) __ATTR_WUNUSED struct group *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(getgrgid))(__gid_t __gid) {
	struct group *__result;
	(__NAMESPACE_LOCAL_SYM __localdep_setgrent)();
	while ((__result = (__NAMESPACE_LOCAL_SYM __localdep_getgrent)()) != __NULLPTR) {
		if (__result->gr_gid == __gid)
			break;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getgrgid_defined
#define __local___localdep_getgrgid_defined
#define __localdep_getgrgid __LIBC_LOCAL_NAME(getgrgid)
#endif /* !__local___localdep_getgrgid_defined */
#else /* __CRT_HAVE_setgrent && __CRT_HAVE_getgrent */
#undef __local_getgrgid_defined
#endif /* !__CRT_HAVE_setgrent || !__CRT_HAVE_getgrent */
#endif /* !__local_getgrgid_defined */
