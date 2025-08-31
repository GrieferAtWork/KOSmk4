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
#ifndef GUARD_LIBC_USER_SPAWN_C
#define GUARD_LIBC_USER_SPAWN_C 1

#include "../api.h"
/**/

#include "spawn.h"

DECL_BEGIN

/*[[[head:libc_pidfd_spawn_impl,hash:CRC-32=0xceef6ea0]]]*/
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") ATTR_IN(6) ATTR_IN(7) ATTR_IN_OPT(4) ATTR_IN_OPT(5) ATTR_OUT(1) errno_t
NOTHROW_RPC(LIBCCALL libc_pidfd_spawn_impl)(fd_t *__restrict pidfd,
                                            unsigned int exec_type,
                                            void *exec_arg,
                                            posix_spawn_file_actions_t const *file_actions,
                                            posix_spawnattr_t const *attrp,
                                            __TARGV,
                                            __TENVP)
/*[[[body:libc_pidfd_spawn_impl]]]*/
/*AUTO*/{
	(void)pidfd;
	(void)exec_type;
	(void)exec_arg;
	(void)file_actions;
	(void)attrp;
	(void)___argv;
	(void)___envp;
	CRT_UNIMPLEMENTEDF("pidfd_spawn_impl(pidfd: %p, exec_type: %x, exec_arg: %p, file_actions: %p, attrp: %p, ___argv: %p, ___envp: %p)", pidfd, exec_type, exec_arg, file_actions, attrp, ___argv, ___envp); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pidfd_spawn_impl]]]*/

/*[[[start:exports,hash:CRC-32=0x0]]]*/
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SPAWN_C */
