/* HASH CRC-32:0x385f6919 */
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
#ifndef __local_initgroups_defined
#define __local_initgroups_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_getgrouplist) || (defined(__CRT_HAVE_setgrent) && defined(__CRT_HAVE_getgrent))) && (defined(__CRT_HAVE_setgroups) || defined(__CRT_HAVE___setgroups) || defined(__CRT_HAVE___libc_setgroups)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <bits/crt/db/group.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#elif defined(__CRT_HAVE___libc_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),__libc_free,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
#ifndef __local___localdep_getgrouplist_defined
#define __local___localdep_getgrouplist_defined
#ifdef __CRT_HAVE_getgrouplist
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RW(4) __ATTR_ACCESS_WR(3),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_getgrouplist,(char const *__user, __gid_t __group, __gid_t *__groups, __STDC_INT_AS_SIZE_T *__ngroups),getgrouplist,(__user,__group,__groups,__ngroups))
#elif defined(__CRT_HAVE_setgrent) && defined(__CRT_HAVE_getgrent)
__NAMESPACE_LOCAL_END
#include <libc/local/grp/getgrouplist.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_getgrouplist __LIBC_LOCAL_NAME(getgrouplist)
#else /* ... */
#undef __local___localdep_getgrouplist_defined
#endif /* !... */
#endif /* !__local___localdep_getgrouplist_defined */
#ifndef __local___localdep_realloc_defined
#define __local___localdep_realloc_defined
#if __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,{ return __builtin_realloc(__mallptr, __num_bytes); })
#elif defined(__CRT_HAVE_realloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,(__mallptr,__num_bytes))
#elif defined(__CRT_HAVE___libc_realloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),__libc_realloc,(__mallptr,__num_bytes))
#else /* ... */
#undef __local___localdep_realloc_defined
#endif /* !... */
#endif /* !__local___localdep_realloc_defined */
#ifndef __local___localdep_setgroups_defined
#define __local___localdep_setgroups_defined
#ifdef __CRT_HAVE_setgroups
__CREDIRECT(__ATTR_ACCESS_ROS(2, 1),int,__NOTHROW_RPC,__localdep_setgroups,(__SIZE_TYPE__ __count, __gid_t const *__groups),setgroups,(__count,__groups))
#elif defined(__CRT_HAVE___setgroups)
__CREDIRECT(__ATTR_ACCESS_ROS(2, 1),int,__NOTHROW_RPC,__localdep_setgroups,(__SIZE_TYPE__ __count, __gid_t const *__groups),__setgroups,(__count,__groups))
#elif defined(__CRT_HAVE___libc_setgroups)
__CREDIRECT(__ATTR_ACCESS_ROS(2, 1),int,__NOTHROW_RPC,__localdep_setgroups,(__SIZE_TYPE__ __count, __gid_t const *__groups),__libc_setgroups,(__count,__groups))
#else /* ... */
#undef __local___localdep_setgroups_defined
#endif /* !... */
#endif /* !__local___localdep_setgroups_defined */
__LOCAL_LIBC(initgroups) __ATTR_ACCESS_RO(1) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(initgroups))(char const *__user, __gid_t __group) {
	int __result = 0;
	__gid_t __initbuf[32], *__buf = __initbuf;
	__STDC_INT_AS_SIZE_T __buflen = __COMPILER_LENOF(__initbuf);
	__STDC_INT_AS_SIZE_T __ngroups;
	for (;;) {
		__gid_t *__newbuf;
		__ngroups = __buflen;
		if ((__NAMESPACE_LOCAL_SYM __localdep_getgrouplist)(__user, __group, __buf, &__ngroups) != -1)
			break;
		/* Allocate more space. */
		if (__buf == __initbuf)
			__buf = __NULLPTR;
		__newbuf = (__gid_t *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__buf, __ngroups * sizeof(__gid_t));
		if __unlikely(!__newbuf) {
			__result = -1;
			goto __done;
		}
		__buf = __newbuf;
	}

	/* Apply the loaded list of groups. */
	__result = (__NAMESPACE_LOCAL_SYM __localdep_setgroups)((__SIZE_TYPE__)__ngroups, __buf);
__done:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	if (__buf != __initbuf)
		(__NAMESPACE_LOCAL_SYM __localdep_free)(__buf);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_initgroups_defined
#define __local___localdep_initgroups_defined
#define __localdep_initgroups __LIBC_LOCAL_NAME(initgroups)
#endif /* !__local___localdep_initgroups_defined */
#else /* (__CRT_HAVE_getgrouplist || (__CRT_HAVE_setgrent && __CRT_HAVE_getgrent)) && (__CRT_HAVE_setgroups || __CRT_HAVE___setgroups || __CRT_HAVE___libc_setgroups) && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) */
#undef __local_initgroups_defined
#endif /* (!__CRT_HAVE_getgrouplist && (!__CRT_HAVE_setgrent || !__CRT_HAVE_getgrent)) || (!__CRT_HAVE_setgroups && !__CRT_HAVE___setgroups && !__CRT_HAVE___libc_setgroups) || (!__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) */
#endif /* !__local_initgroups_defined */
