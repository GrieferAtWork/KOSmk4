/* HASH CRC-32:0x764348a4 */
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
#ifndef __local_envz_merge_defined
#define __local_envz_merge_defined
#include <__crt.h>
#if defined(__CRT_HAVE_argz_append) || defined(__CRT_HAVE___argz_create_sep) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_argz_append_defined
#define __local___localdep_argz_append_defined
#ifdef __CRT_HAVE_argz_append
__CREDIRECT(__ATTR_ACCESS_ROS(3, 4) __ATTR_ACCESS_RW(1) __ATTR_ACCESS_RW(2),__errno_t,__NOTHROW_NCX,__localdep_argz_append,(char **__restrict __pargz, __SIZE_TYPE__ *__restrict __pargz_len, char const *__restrict __buf, __SIZE_TYPE__ __buf_len),argz_append,(__pargz,__pargz_len,__buf,__buf_len))
#elif defined(__CRT_HAVE___argz_create_sep)
__CREDIRECT(__ATTR_ACCESS_ROS(3, 4) __ATTR_ACCESS_RW(1) __ATTR_ACCESS_RW(2),__errno_t,__NOTHROW_NCX,__localdep_argz_append,(char **__restrict __pargz, __SIZE_TYPE__ *__restrict __pargz_len, char const *__restrict __buf, __SIZE_TYPE__ __buf_len),__argz_create_sep,(__pargz,__pargz_len,__buf,__buf_len))
#elif defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
__NAMESPACE_LOCAL_END
#include <libc/local/argz/argz_append.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_argz_append __LIBC_LOCAL_NAME(argz_append)
#else /* ... */
#undef __local___localdep_argz_append_defined
#endif /* !... */
#endif /* !__local___localdep_argz_append_defined */
#ifndef __local___localdep_argz_delete_defined
#define __local___localdep_argz_delete_defined
#ifdef __CRT_HAVE_argz_delete
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_ACCESS_RO_OPT(3) __ATTR_ACCESS_RW(1) __ATTR_ACCESS_RW(2),__NOTHROW_NCX,__localdep_argz_delete,(char **__restrict __pargz, __SIZE_TYPE__ *__restrict __pargz_len, char *__entry),argz_delete,(__pargz,__pargz_len,__entry))
#elif defined(__CRT_HAVE___argz_add_sep)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_ACCESS_RO_OPT(3) __ATTR_ACCESS_RW(1) __ATTR_ACCESS_RW(2),__NOTHROW_NCX,__localdep_argz_delete,(char **__restrict __pargz, __SIZE_TYPE__ *__restrict __pargz_len, char *__entry),__argz_add_sep,(__pargz,__pargz_len,__entry))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/argz/argz_delete.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_argz_delete __LIBC_LOCAL_NAME(argz_delete)
#endif /* !... */
#endif /* !__local___localdep_argz_delete_defined */
#ifndef __local___localdep_envz_entry_defined
#define __local___localdep_envz_entry_defined
#ifdef __CRT_HAVE_envz_entry
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(3) __ATTR_ACCESS_ROS(1, 2) __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_envz_entry,(char const *__restrict __envz, __SIZE_TYPE__ __envz_len, char const *__restrict __name),envz_entry,(__envz,__envz_len,__name))
#else /* __CRT_HAVE_envz_entry */
__NAMESPACE_LOCAL_END
#include <libc/local/envz/envz_entry.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_envz_entry __LIBC_LOCAL_NAME(envz_entry)
#endif /* !__CRT_HAVE_envz_entry */
#endif /* !__local___localdep_envz_entry_defined */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined
#ifdef __CRT_HAVE_strlen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
__LOCAL_LIBC(envz_merge) __ATTR_ACCESS_ROS(3, 4) __ATTR_ACCESS_RW(1) __ATTR_ACCESS_RW(2) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(envz_merge))(char **__restrict __penvz, __SIZE_TYPE__ *__restrict __penvz_len, char const *__restrict __envz2, __SIZE_TYPE__ __envz2_len, int __override_) {
	__errno_t __result = 0;
	while (__envz2_len && __result == 0) {
		char *__existing = (__NAMESPACE_LOCAL_SYM __localdep_envz_entry)(*__penvz, *__penvz_len, __envz2);
		__SIZE_TYPE__ __newlen  = (__NAMESPACE_LOCAL_SYM __localdep_strlen)(__envz2) + 1;
		if (!__existing)
			__result = (__NAMESPACE_LOCAL_SYM __localdep_argz_append)(__penvz, __penvz_len, __envz2, __newlen);
		else if (__override_) {
			(__NAMESPACE_LOCAL_SYM __localdep_argz_delete)(__penvz, __penvz_len, __existing);
			__result = (__NAMESPACE_LOCAL_SYM __localdep_argz_append)(__penvz, __penvz_len, __envz2, __newlen);
		}
		__envz2     += __newlen;
		__envz2_len -= __newlen;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_envz_merge_defined
#define __local___localdep_envz_merge_defined
#define __localdep_envz_merge __LIBC_LOCAL_NAME(envz_merge)
#endif /* !__local___localdep_envz_merge_defined */
#else /* __CRT_HAVE_argz_append || __CRT_HAVE___argz_create_sep || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc */
#undef __local_envz_merge_defined
#endif /* !__CRT_HAVE_argz_append && !__CRT_HAVE___argz_create_sep && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc */
#endif /* !__local_envz_merge_defined */
