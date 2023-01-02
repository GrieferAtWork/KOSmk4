/* HASH CRC-32:0x1d7fa6f0 */
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
#ifndef __local_group_member_defined
#define __local_group_member_defined
#include <__crt.h>
#include <hybrid/__alloca.h>
#include <libc/errno.h>
#if (defined(__CRT_HAVE_getgroups) || defined(__CRT_HAVE___getgroups) || defined(__CRT_HAVE___libc_getgroups)) && defined(__hybrid_alloca) && defined(__libc_geterrno) && defined(__EINVAL)
#include <bits/types.h>
#include <asm/os/limits.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__group_member_impl) __ATTR_NOINLINE int
(__LIBCCALL __group_member_impl)(__gid_t __gid, unsigned int __bufsize) {
	unsigned int __i;
	__gid_t *__groups = (__gid_t *)__hybrid_alloca(__bufsize * sizeof(*__groups));
	int __n         = __getgroups((int)__bufsize, __groups);
	if __unlikely(__n < 0)
		return __n;
	for (__i = 0; __i < (unsigned int)__n; ++__i) {
		if (__groups[__i] == __gid)
			return 1;
	}
	return 0;
}
__NAMESPACE_LOCAL_END
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(group_member) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(group_member))(__gid_t __gid) {
	int __result;
#if !defined(__NGROUPS_MAX) || __NGROUPS_MAX <= 0 || __NGROUPS_MAX >= 32
	unsigned int __size = 32;
#else /* !__NGROUPS_MAX || __NGROUPS_MAX <= 0 || __NGROUPS_MAX >= 32 */
	unsigned int __size = __NGROUPS_MAX;
#endif /* __NGROUPS_MAX && __NGROUPS_MAX > 0 && __NGROUPS_MAX < 32 */
	for (;;) {
		__result = (__NAMESPACE_LOCAL_SYM __group_member_impl)(__gid, __size);
		if (__result >= 0)
			break;
		if (__libc_geterrno() != __EINVAL)
			break;
		/* Try again with a larger buffer. */
		__size *= 2;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_group_member_defined
#define __local___localdep_group_member_defined
#define __localdep_group_member __LIBC_LOCAL_NAME(group_member)
#endif /* !__local___localdep_group_member_defined */
#else /* (__CRT_HAVE_getgroups || __CRT_HAVE___getgroups || __CRT_HAVE___libc_getgroups) && __hybrid_alloca && __libc_geterrno && __EINVAL */
#undef __local_group_member_defined
#endif /* (!__CRT_HAVE_getgroups && !__CRT_HAVE___getgroups && !__CRT_HAVE___libc_getgroups) || !__hybrid_alloca || !__libc_geterrno || !__EINVAL */
#endif /* !__local_group_member_defined */
