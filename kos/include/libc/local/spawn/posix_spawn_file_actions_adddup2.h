/* HASH CRC-32:0xa9550575 */
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
#ifndef __local_posix_spawn_file_actions_adddup2_defined
#define __local_posix_spawn_file_actions_adddup2_defined 1
#include <__crt.h>
#include <asm/crt/posix_spawn.h>
#if defined(__POSIX_SPAWN_USE_KOS) && defined(__CRT_HAVE_realloc)
#include <bits/crt/posix_spawn.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_posix_spawn_file_actions_alloc_defined
#define __local___localdep_posix_spawn_file_actions_alloc_defined 1
__NAMESPACE_LOCAL_END
#include <libc/local/spawn/posix_spawn_file_actions_alloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_posix_spawn_file_actions_alloc __LIBC_LOCAL_NAME(posix_spawn_file_actions_alloc)
#endif /* !__local___localdep_posix_spawn_file_actions_alloc_defined */
__LOCAL_LIBC(posix_spawn_file_actions_adddup2) __ATTR_NONNULL((1)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(posix_spawn_file_actions_adddup2))(struct __posix_spawn_file_actions *__restrict __file_actions, __fd_t __oldfd, __fd_t __newfd) {
	struct __spawn_action *__action;
	__action = __localdep_posix_spawn_file_actions_alloc(__file_actions);
	if __unlikely(!__action)
		goto __err;
	/* Fill in the new mode. */
	__action->__sa_tag = __POSIX_SPAWN_ACTION_DUP2;
	__action->__sa_action.__sa_dup2_action.__sa_oldfd = __oldfd;
	__action->__sa_action.__sa_dup2_action.__sa_newfd = __newfd;
	return 0;
__err:
#ifdef __ENOMEM
	return __ENOMEM;
#else /* __ENOMEM */
	return 1;
#endif /* !__ENOMEM */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_posix_spawn_file_actions_adddup2_defined
#define __local___localdep_posix_spawn_file_actions_adddup2_defined 1
#define __localdep_posix_spawn_file_actions_adddup2 __LIBC_LOCAL_NAME(posix_spawn_file_actions_adddup2)
#endif /* !__local___localdep_posix_spawn_file_actions_adddup2_defined */
#else /* __POSIX_SPAWN_USE_KOS && __CRT_HAVE_realloc */
#undef __local_posix_spawn_file_actions_adddup2_defined
#endif /* !__POSIX_SPAWN_USE_KOS || !__CRT_HAVE_realloc */
#endif /* !__local_posix_spawn_file_actions_adddup2_defined */
