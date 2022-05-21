/* HASH CRC-32:0xd445b569 */
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
#ifndef __local_posix_spawn_file_actions_addchdir_np_defined
#define __local_posix_spawn_file_actions_addchdir_np_defined
#include <__crt.h>
#include <asm/crt/posix_spawn.h>
#if defined(__POSIX_SPAWN_USE_KOS) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <bits/crt/posix_spawn.h>
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
#ifndef __local___localdep_posix_spawn_file_actions_alloc_defined
#define __local___localdep_posix_spawn_file_actions_alloc_defined
__NAMESPACE_LOCAL_END
#include <libc/local/spawn/posix_spawn_file_actions_alloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_posix_spawn_file_actions_alloc __LIBC_LOCAL_NAME(posix_spawn_file_actions_alloc)
#endif /* !__local___localdep_posix_spawn_file_actions_alloc_defined */
#ifndef __local___localdep_strdup_defined
#define __local___localdep_strdup_defined
#if __has_builtin(__builtin_strdup) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strdup)
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ACCESS_RO(1),char *,__NOTHROW_NCX,__localdep_strdup,(char const *__restrict __string),strdup,{ return __builtin_strdup(__string); })
#elif defined(__CRT_HAVE_strdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ACCESS_RO(1),char *,__NOTHROW_NCX,__localdep_strdup,(char const *__restrict __string),strdup,(__string))
#elif defined(__CRT_HAVE__strdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ACCESS_RO(1),char *,__NOTHROW_NCX,__localdep_strdup,(char const *__restrict __string),_strdup,(__string))
#elif defined(__CRT_HAVE__mbsdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ACCESS_RO(1),char *,__NOTHROW_NCX,__localdep_strdup,(char const *__restrict __string),_mbsdup,(__string))
#elif defined(__CRT_HAVE___strdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ACCESS_RO(1),char *,__NOTHROW_NCX,__localdep_strdup,(char const *__restrict __string),__strdup,(__string))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strdup.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strdup __LIBC_LOCAL_NAME(strdup)
#endif /* !... */
#endif /* !__local___localdep_strdup_defined */
__LOCAL_LIBC(posix_spawn_file_actions_addchdir_np) __ATTR_NONNULL((1, 2)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(posix_spawn_file_actions_addchdir_np))(struct __posix_spawn_file_actions *__restrict __file_actions, const char *__restrict __path) {
	struct __spawn_action *__action;
	if __unlikely((__path = (__NAMESPACE_LOCAL_SYM __localdep_strdup)(__path)) == __NULLPTR)
		goto __err;
	__action = (__NAMESPACE_LOCAL_SYM __localdep_posix_spawn_file_actions_alloc)(__file_actions);
	if __unlikely(!__action)
		goto __err_path;
	/* Fill in the new mode. */
	__action->__sa_tag = __POSIX_SPAWN_ACTION_CHDIR;
	__action->__sa_action.__sa_chdir_action.__sa_path = (char *)__path;
	return 0;
__err_path:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)((char *)__path);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
__err:
#ifdef __ENOMEM
	return __ENOMEM;
#else /* __ENOMEM */
	return 1;
#endif /* !__ENOMEM */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_posix_spawn_file_actions_addchdir_np_defined
#define __local___localdep_posix_spawn_file_actions_addchdir_np_defined
#define __localdep_posix_spawn_file_actions_addchdir_np __LIBC_LOCAL_NAME(posix_spawn_file_actions_addchdir_np)
#endif /* !__local___localdep_posix_spawn_file_actions_addchdir_np_defined */
#else /* __POSIX_SPAWN_USE_KOS && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) */
#undef __local_posix_spawn_file_actions_addchdir_np_defined
#endif /* !__POSIX_SPAWN_USE_KOS || (!__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) */
#endif /* !__local_posix_spawn_file_actions_addchdir_np_defined */
