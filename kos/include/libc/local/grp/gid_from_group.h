/* HASH CRC-32:0xe96d3987 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_gid_from_group_defined
#define __local_gid_from_group_defined
#include <__crt.h>
#if defined(__CRT_HAVE_getgrnam) || (defined(__CRT_HAVE_setgrent) && defined(__CRT_HAVE_getgrent))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getgrnam_defined
#define __local___localdep_getgrnam_defined
#ifdef __CRT_HAVE_getgrnam
__NAMESPACE_LOCAL_END
#include <bits/crt/db/group.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),struct group *,__NOTHROW_RPC,__localdep_getgrnam,(char const *__restrict __name),getgrnam,(__name))
#elif defined(__CRT_HAVE_setgrent) && defined(__CRT_HAVE_getgrent)
__NAMESPACE_LOCAL_END
#include <libc/local/grp/getgrnam.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_getgrnam __LIBC_LOCAL_NAME(getgrnam)
#else /* ... */
#undef __local___localdep_getgrnam_defined
#endif /* !... */
#endif /* !__local___localdep_getgrnam_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/db/group.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(gid_from_group) __ATTR_IN(1) __ATTR_OUT(2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(gid_from_group))(char const *__name, __gid_t *__p_gid) {
	struct group *__ent = (__NAMESPACE_LOCAL_SYM __localdep_getgrnam)(__name);
	if (__ent) {
		*__p_gid = __ent->gr_gid;
		return 0;
	}
	return -1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_gid_from_group_defined
#define __local___localdep_gid_from_group_defined
#define __localdep_gid_from_group __LIBC_LOCAL_NAME(gid_from_group)
#endif /* !__local___localdep_gid_from_group_defined */
#else /* __CRT_HAVE_getgrnam || (__CRT_HAVE_setgrent && __CRT_HAVE_getgrent) */
#undef __local_gid_from_group_defined
#endif /* !__CRT_HAVE_getgrnam && (!__CRT_HAVE_setgrent || !__CRT_HAVE_getgrent) */
#endif /* !__local_gid_from_group_defined */
