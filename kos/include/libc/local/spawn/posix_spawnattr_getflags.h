/* HASH CRC-32:0x9b3fdd58 */
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
#ifndef __local_posix_spawnattr_getflags_defined
#define __local_posix_spawnattr_getflags_defined
#include <__crt.h>
#include <asm/crt/posix_spawn.h>
#ifdef __POSIX_SPAWN_USE_KOS
#include <bits/crt/posix_spawn.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(posix_spawnattr_getflags) __ATTR_IN(1) __ATTR_OUT(2) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(posix_spawnattr_getflags))(struct __posix_spawnattr const *__restrict __attr, short int *__restrict __pflags) {
	*__pflags = (short int)(unsigned short int)__attr->__flags;
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_posix_spawnattr_getflags_defined
#define __local___localdep_posix_spawnattr_getflags_defined
#define __localdep_posix_spawnattr_getflags __LIBC_LOCAL_NAME(posix_spawnattr_getflags)
#endif /* !__local___localdep_posix_spawnattr_getflags_defined */
#else /* __POSIX_SPAWN_USE_KOS */
#undef __local_posix_spawnattr_getflags_defined
#endif /* !__POSIX_SPAWN_USE_KOS */
#endif /* !__local_posix_spawnattr_getflags_defined */
