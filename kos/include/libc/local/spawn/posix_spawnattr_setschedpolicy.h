/* HASH CRC-32:0xd058bea */
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
#ifndef __local_posix_spawnattr_setschedpolicy_defined
#define __local_posix_spawnattr_setschedpolicy_defined
#include <__crt.h>
#include <asm/crt/posix_spawn.h>
#ifdef __POSIX_SPAWN_USE_KOS
#include <bits/crt/posix_spawn.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(posix_spawnattr_setschedpolicy) __ATTR_INOUT(1) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(posix_spawnattr_setschedpolicy))(struct __posix_spawnattr *__restrict __attr, int __schedpolicy) {
	__attr->__policy = __schedpolicy;
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_posix_spawnattr_setschedpolicy_defined
#define __local___localdep_posix_spawnattr_setschedpolicy_defined
#define __localdep_posix_spawnattr_setschedpolicy __LIBC_LOCAL_NAME(posix_spawnattr_setschedpolicy)
#endif /* !__local___localdep_posix_spawnattr_setschedpolicy_defined */
#else /* __POSIX_SPAWN_USE_KOS */
#undef __local_posix_spawnattr_setschedpolicy_defined
#endif /* !__POSIX_SPAWN_USE_KOS */
#endif /* !__local_posix_spawnattr_setschedpolicy_defined */
