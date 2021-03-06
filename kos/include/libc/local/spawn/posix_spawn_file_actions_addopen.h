/* HASH CRC-32:0x1d0ad52c */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_posix_spawn_file_actions_addopen_defined
#define __local_posix_spawn_file_actions_addopen_defined 1
#include <__crt.h>
#include <asm/crt/posix_spawn.h>
#if defined(__POSIX_SPAWN_USE_KOS) && defined(__CRT_HAVE_realloc)
#include <bits/crt/posix_spawn.h>
#include <bits/types.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: free from stdlib */
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined 1
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ return __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
/* Dependency: posix_spawn_file_actions_alloc from spawn */
#ifndef __local___localdep_posix_spawn_file_actions_alloc_defined
#define __local___localdep_posix_spawn_file_actions_alloc_defined 1
__NAMESPACE_LOCAL_END
#include <libc/local/spawn/posix_spawn_file_actions_alloc.h>
__NAMESPACE_LOCAL_BEGIN
/* Helper functions for allocating an a new file-spawn action entry */
#define __localdep_posix_spawn_file_actions_alloc __LIBC_LOCAL_NAME(posix_spawn_file_actions_alloc)
#endif /* !__local___localdep_posix_spawn_file_actions_alloc_defined */
/* Dependency: strdup from string */
#ifndef __local___localdep_strdup_defined
#define __local___localdep_strdup_defined 1
#if __has_builtin(__builtin_strdup) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strdup)
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strdup,(char const *__restrict __string),strdup,{ return __builtin_strdup(__string); })
#elif defined(__CRT_HAVE_strdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strdup,(char const *__restrict __string),strdup,(__string))
#elif defined(__CRT_HAVE__strdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strdup,(char const *__restrict __string),_strdup,(__string))
#elif defined(__CRT_HAVE___strdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strdup,(char const *__restrict __string),__strdup,(__string))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strdup.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strdup __LIBC_LOCAL_NAME(strdup)
#endif /* !... */
#endif /* !__local___localdep_strdup_defined */
/* >> posix_spawn_file_actions_addopen(3)
 * Enqueue a call `dup2(open(path, oflags, mode), fd)' to be performed by the child process
 * Note though that the intermediate file returned by `open()' will not remain open!
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
__LOCAL_LIBC(posix_spawn_file_actions_addopen) __ATTR_NONNULL((1, 3)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(posix_spawn_file_actions_addopen))(struct __posix_spawn_file_actions *__restrict __file_actions, __fd_t __fd, char const *__restrict __path, __oflag_t __oflags, __mode_t __mode) {
	struct __spawn_action *__action;
	/* Posix says:
	 * """
	 * The string described by path shall be copied  by
	 * the posix_spawn_file_actions_addopen() function.
	 * """
	 * iow: We need to strdup(path) here! */
	if __unlikely((__path = __localdep_strdup(__path)) == __NULLPTR)
		goto __err;
	__action = __localdep_posix_spawn_file_actions_alloc(__file_actions);
	if __unlikely(!__action)
		goto __err_path;
	/* Fill in the new mode. */
	__action->__sa_tag = __POSIX_SPAWN_ACTION_OPEN;
	__action->__sa_action.__sa_open_action.__sa_fd    = __fd;
	__action->__sa_action.__sa_open_action.__sa_path  = (char *)__path;
	__action->__sa_action.__sa_open_action.__sa_oflag = __oflags;
	__action->__sa_action.__sa_open_action.__sa_mode  = __mode;
	return 0;
__err_path:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
	__localdep_free((char *)__path);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree */
__err:
#ifdef __ENOMEM
	return __ENOMEM;
#else /* __ENOMEM */
	return 1;
#endif /* !__ENOMEM */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_posix_spawn_file_actions_addopen_defined
#define __local___localdep_posix_spawn_file_actions_addopen_defined 1
#define __localdep_posix_spawn_file_actions_addopen __LIBC_LOCAL_NAME(posix_spawn_file_actions_addopen)
#endif /* !__local___localdep_posix_spawn_file_actions_addopen_defined */
#else /* __POSIX_SPAWN_USE_KOS && __CRT_HAVE_realloc */
#undef __local_posix_spawn_file_actions_addopen_defined
#endif /* !__POSIX_SPAWN_USE_KOS || !__CRT_HAVE_realloc */
#endif /* !__local_posix_spawn_file_actions_addopen_defined */
