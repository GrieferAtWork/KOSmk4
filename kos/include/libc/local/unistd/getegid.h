/* HASH CRC-32:0x6c2bb210 */
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
#ifndef __local_getegid_defined
#define __local_getegid_defined
#include <__crt.h>
#ifdef __CRT_HAVE_getresgid
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getresgid_defined
#define __local___localdep_getresgid_defined
__CREDIRECT(__ATTR_OUT_OPT(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_getresgid,(__gid_t *__rgid, __gid_t *__egid, __gid_t *__sgid),getresgid,(__rgid,__egid,__sgid))
#endif /* !__local___localdep_getresgid_defined */
__LOCAL_LIBC(getegid) __ATTR_WUNUSED __gid_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(getegid))(void) {
	__gid_t __result;
	if ((__NAMESPACE_LOCAL_SYM __localdep_getresgid)(__NULLPTR, &__result, __NULLPTR))
		__result = (__gid_t)-1;
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getegid_defined
#define __local___localdep_getegid_defined
#define __localdep_getegid __LIBC_LOCAL_NAME(getegid)
#endif /* !__local___localdep_getegid_defined */
#else /* __CRT_HAVE_getresgid */
#undef __local_getegid_defined
#endif /* !__CRT_HAVE_getresgid */
#endif /* !__local_getegid_defined */
