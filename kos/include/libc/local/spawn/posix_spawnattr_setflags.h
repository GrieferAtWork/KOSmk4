/* HASH CRC-32:0xfd6b6922 */
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
#ifndef __local_posix_spawnattr_setflags_defined
#define __local_posix_spawnattr_setflags_defined
#include <__crt.h>
#include <asm/crt/posix_spawn.h>
#ifdef __POSIX_SPAWN_USE_KOS
#include <bits/crt/posix_spawn.h>
#include <asm/os/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(posix_spawnattr_setflags) __ATTR_INOUT(1) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(posix_spawnattr_setflags))(struct __posix_spawnattr *__restrict __attr, short int __flags) {
	enum {
		__ALL_FLAGS = 0
#ifdef __POSIX_SPAWN_RESETIDS
		| __POSIX_SPAWN_RESETIDS
#endif /* __POSIX_SPAWN_RESETIDS */
#ifdef __POSIX_SPAWN_SETPGROUP
		| __POSIX_SPAWN_SETPGROUP
#endif /* __POSIX_SPAWN_SETPGROUP */
#ifdef __POSIX_SPAWN_SETSIGDEF
		| __POSIX_SPAWN_SETSIGDEF
#endif /* __POSIX_SPAWN_SETSIGDEF */
#ifdef __POSIX_SPAWN_SETSIGMASK
		| __POSIX_SPAWN_SETSIGMASK
#endif /* __POSIX_SPAWN_SETSIGMASK */
#ifdef __POSIX_SPAWN_SETSCHEDPARAM
		| __POSIX_SPAWN_SETSCHEDPARAM
#endif /* __POSIX_SPAWN_SETSCHEDPARAM */
#ifdef __POSIX_SPAWN_SETSCHEDULER
		| __POSIX_SPAWN_SETSCHEDULER
#endif /* __POSIX_SPAWN_SETSCHEDULER */
#ifdef __POSIX_SPAWN_USEVFORK
		| __POSIX_SPAWN_USEVFORK
#endif /* __POSIX_SPAWN_USEVFORK */
#ifdef __POSIX_SPAWN_SETSID
		| __POSIX_SPAWN_SETSID
#endif /* __POSIX_SPAWN_SETSID */
#ifdef __POSIX_SPAWN_SETCGROUP
		| __POSIX_SPAWN_SETCGROUP
#endif /* __POSIX_SPAWN_SETCGROUP */
#ifdef __POSIX_SPAWN_NOEXECERR
		| __POSIX_SPAWN_NOEXECERR
#endif /* __POSIX_SPAWN_NOEXECERR */
	};
	if __unlikely((unsigned short int)__flags & ~(unsigned short int)__ALL_FLAGS) {
#ifdef __EINVAL
		return __EINVAL;
#else /* __EINVAL */
		return 1;
#endif /* !__EINVAL */
	}
	__attr->__flags = (__UINT16_TYPE__)(unsigned short int)__flags;
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_posix_spawnattr_setflags_defined
#define __local___localdep_posix_spawnattr_setflags_defined
#define __localdep_posix_spawnattr_setflags __LIBC_LOCAL_NAME(posix_spawnattr_setflags)
#endif /* !__local___localdep_posix_spawnattr_setflags_defined */
#else /* __POSIX_SPAWN_USE_KOS */
#undef __local_posix_spawnattr_setflags_defined
#endif /* !__POSIX_SPAWN_USE_KOS */
#endif /* !__local_posix_spawnattr_setflags_defined */
