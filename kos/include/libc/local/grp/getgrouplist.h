/* HASH CRC-32:0x13339db9 */
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
#ifndef __local_getgrouplist_defined
#define __local_getgrouplist_defined
#include <__crt.h>
#if defined(__CRT_HAVE_setgrent) && defined(__CRT_HAVE_getgrent)
#include <features.h>
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
#ifndef __local___localdep_strcmp_defined
#define __local___localdep_strcmp_defined
#if __has_builtin(__builtin_strcmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,{ return __builtin_strcmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,(__s1,__s2))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strcmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strcmp __LIBC_LOCAL_NAME(strcmp)
#endif /* !... */
#endif /* !__local___localdep_strcmp_defined */
__LOCAL_LIBC(getgrouplist) __ATTR_NONNULL((1, 3, 4)) __STDC_INT_AS_SSIZE_T
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(getgrouplist))(char const *__user, __gid_t __group, __gid_t *__groups, __STDC_INT_AS_SIZE_T *__ngroups) {
	__STDC_INT_AS_SIZE_T __count = 0;
	__STDC_INT_AS_SIZE_T __buflen = *__ngroups;
	struct group *__ent;
	(__NAMESPACE_LOCAL_SYM __localdep_setgrent)();
	while ((__ent = (__NAMESPACE_LOCAL_SYM __localdep_getgrent)()) != __NULLPTR) {
		__SIZE_TYPE__ __i;
		if (__ent->gr_gid == __group)
			goto __nextgroup; /* Skip! (always added manually) */

		/* Check if `user' is in this group's member list. */
		for (__i = 0;; ++__i) {
			char *__member = __ent->gr_mem[__i];
			if (!__member)
				goto __nextgroup;
			if ((__NAMESPACE_LOCAL_SYM __localdep_strcmp)(__member, __user) == 0)
				break; /* Yup! User is apart of this group! */
		}

		/* Add this group's GID to the result list. */
		if (__count < __buflen)
			*__groups++ = __ent->gr_gid;
		++__count;
__nextgroup:
		;
	}

	/* Append `group', so it's always apart of the list.
	 *
	 * The fact  that in  our  implementation it's  always  the
	 * last member is an implementation detail we intentionally
	 * neglect to document! */
	if (__count < __buflen)
		*__groups++ = __group;
	++__count;

	/* Write-back the required buffer size. */
	*__ngroups = (__STDC_INT_AS_SIZE_T)__count;
	if ((__SIZE_TYPE__)__count > (__SIZE_TYPE__)__buflen)
		return (__STDC_INT_AS_SSIZE_T)-1; /* Buffer too small. */
	return (__STDC_INT_AS_SSIZE_T)__count;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getgrouplist_defined
#define __local___localdep_getgrouplist_defined
#define __localdep_getgrouplist __LIBC_LOCAL_NAME(getgrouplist)
#endif /* !__local___localdep_getgrouplist_defined */
#else /* __CRT_HAVE_setgrent && __CRT_HAVE_getgrent */
#undef __local_getgrouplist_defined
#endif /* !__CRT_HAVE_setgrent || !__CRT_HAVE_getgrent */
#endif /* !__local_getgrouplist_defined */
