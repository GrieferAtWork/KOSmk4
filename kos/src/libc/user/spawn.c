/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SPAWN_C
#define GUARD_LIBC_USER_SPAWN_C 1

#include "../api.h"
#include "spawn.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:posix_spawn,hash:CRC-32=0x81a8337b]]]*/
/* Spawn a new process executing PATH with the attributes describes in *ATTRP.
 * Before running the process perform the actions described in FILE-ACTIONS.
 * This function is a possible cancellation point and therefore not marked with __THROW */
INTERN NONNULL((1, 2, 5, 6))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.exec.posix_spawn.posix_spawn") int
NOTHROW_RPC(LIBCCALL libc_posix_spawn)(pid_t *__restrict pid,
                                       char const *__restrict path,
                                       posix_spawn_file_actions_t const *file_actions,
                                       posix_spawnattr_t const *attrp,
                                       __TARGV,
                                       __TENVP)
/*[[[body:posix_spawn]]]*/
{
	CRT_UNIMPLEMENTED("posix_spawn"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:posix_spawn]]]*/

/*[[[head:posix_spawnp,hash:CRC-32=0xe1977aad]]]*/
/* Similar to `posix_spawn' but search for FILE in the PATH.
 * This function is a possible cancellation point and therefore not marked with __THROW */
INTERN NONNULL((1, 2, 5, 6))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.exec.posix_spawn.posix_spawnp") int
NOTHROW_RPC(LIBCCALL libc_posix_spawnp)(pid_t *__restrict pid,
                                        const char *__restrict file,
                                        posix_spawn_file_actions_t const *file_actions,
                                        posix_spawnattr_t const *attrp,
                                        __TARGV,
                                        __TENVP)
/*[[[body:posix_spawnp]]]*/
{
	CRT_UNIMPLEMENTED("posix_spawnp"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:posix_spawnp]]]*/

/*[[[head:posix_spawnattr_init,hash:CRC-32=0x508e57d1]]]*/
/* Initialize data structure with attributes for `spawn' to default values */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.exec.posix_spawn.posix_spawnattr_init") int
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_init)(posix_spawnattr_t *__restrict attr)
/*[[[body:posix_spawnattr_init]]]*/
{
	CRT_UNIMPLEMENTED("posix_spawnattr_init"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:posix_spawnattr_init]]]*/

/*[[[head:posix_spawnattr_destroy,hash:CRC-32=0xb08f450d]]]*/
/* Free resources associated with ATTR */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.exec.posix_spawn.posix_spawnattr_destroy") int
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_destroy)(posix_spawnattr_t *__restrict attr)
/*[[[body:posix_spawnattr_destroy]]]*/
{
	CRT_UNIMPLEMENTED("posix_spawnattr_destroy"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:posix_spawnattr_destroy]]]*/

/*[[[head:posix_spawnattr_getsigdefault,hash:CRC-32=0x3802aee6]]]*/
/* Store signal mask for signals with default handling from ATTR in SIGDEFAULT */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.exec.posix_spawn.posix_spawnattr_getsigdefault") int
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_getsigdefault)(posix_spawnattr_t const * __restrict attr,
                                                         sigset_t *__restrict sigdefault)
/*[[[body:posix_spawnattr_getsigdefault]]]*/
{
	CRT_UNIMPLEMENTED("posix_spawnattr_getsigdefault"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:posix_spawnattr_getsigdefault]]]*/

/*[[[head:posix_spawnattr_setsigdefault,hash:CRC-32=0xe37f9242]]]*/
/* Set signal mask for signals with default handling in ATTR to SIGDEFAULT */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.exec.posix_spawn.posix_spawnattr_setsigdefault") int
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_setsigdefault)(posix_spawnattr_t *__restrict attr,
                                                         sigset_t const *__restrict sigdefault)
/*[[[body:posix_spawnattr_setsigdefault]]]*/
{
	CRT_UNIMPLEMENTED("posix_spawnattr_setsigdefault"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:posix_spawnattr_setsigdefault]]]*/

/*[[[head:posix_spawnattr_getsigmask,hash:CRC-32=0x9da6267e]]]*/
/* Store signal mask for the new process from ATTR in SIGMASK */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.exec.posix_spawn.posix_spawnattr_getsigmask") int
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_getsigmask)(posix_spawnattr_t const *__restrict attr,
                                                      sigset_t *__restrict sigmask)
/*[[[body:posix_spawnattr_getsigmask]]]*/
{
	CRT_UNIMPLEMENTED("posix_spawnattr_getsigmask"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:posix_spawnattr_getsigmask]]]*/

/*[[[head:posix_spawnattr_setsigmask,hash:CRC-32=0x23d65c01]]]*/
/* Set signal mask for the new process in ATTR to SIGMASK */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.exec.posix_spawn.posix_spawnattr_setsigmask") int
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_setsigmask)(posix_spawnattr_t *__restrict attr,
                                                      sigset_t const *__restrict sigmask)
/*[[[body:posix_spawnattr_setsigmask]]]*/
{
	CRT_UNIMPLEMENTED("posix_spawnattr_setsigmask"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:posix_spawnattr_setsigmask]]]*/

/*[[[head:posix_spawnattr_getflags,hash:CRC-32=0xaa5c97c6]]]*/
/* Get flag word from the attribute structure */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.exec.posix_spawn.posix_spawnattr_getflags") int
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_getflags)(posix_spawnattr_t const *__restrict attr,
                                                    int16_t *__restrict flags)
/*[[[body:posix_spawnattr_getflags]]]*/
{
	CRT_UNIMPLEMENTED("posix_spawnattr_getflags"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:posix_spawnattr_getflags]]]*/

/*[[[head:posix_spawnattr_setflags,hash:CRC-32=0x68d81a6f]]]*/
/* Store flags in the attribute structure */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.exec.posix_spawn.posix_spawnattr_setflags") int
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_setflags)(posix_spawnattr_t *__restrict attr,
                                                    short int flags)
/*[[[body:posix_spawnattr_setflags]]]*/
{
	CRT_UNIMPLEMENTED("posix_spawnattr_setflags"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:posix_spawnattr_setflags]]]*/

/*[[[head:posix_spawnattr_getpgroup,hash:CRC-32=0x6303e437]]]*/
/* Get process group ID from the attribute structure */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.exec.posix_spawn.posix_spawnattr_getpgroup") int
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_getpgroup)(posix_spawnattr_t const *__restrict attr,
                                                     pid_t *__restrict pgroup)
/*[[[body:posix_spawnattr_getpgroup]]]*/
{
	CRT_UNIMPLEMENTED("posix_spawnattr_getpgroup"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:posix_spawnattr_getpgroup]]]*/

/*[[[head:posix_spawnattr_setpgroup,hash:CRC-32=0x88a69712]]]*/
/* Store process group ID in the attribute structure */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.exec.posix_spawn.posix_spawnattr_setpgroup") int
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_setpgroup)(posix_spawnattr_t *__restrict attr,
                                                     pid_t pgroup)
/*[[[body:posix_spawnattr_setpgroup]]]*/
{
	CRT_UNIMPLEMENTED("posix_spawnattr_setpgroup"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:posix_spawnattr_setpgroup]]]*/

/*[[[head:posix_spawnattr_getschedpolicy,hash:CRC-32=0x38109bda]]]*/
/* Get scheduling policy from the attribute structure */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.exec.posix_spawn.posix_spawnattr_getschedpolicy") int
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_getschedpolicy)(posix_spawnattr_t const *__restrict attr,
                                                          int *__restrict schedpolicy)
/*[[[body:posix_spawnattr_getschedpolicy]]]*/
{
	CRT_UNIMPLEMENTED("posix_spawnattr_getschedpolicy"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:posix_spawnattr_getschedpolicy]]]*/

/*[[[head:posix_spawnattr_setschedpolicy,hash:CRC-32=0x72b8ab8f]]]*/
/* Store scheduling policy in the attribute structure */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.exec.posix_spawn.posix_spawnattr_setschedpolicy") int
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_setschedpolicy)(posix_spawnattr_t *__restrict attr,
                                                          int schedpolicy)
/*[[[body:posix_spawnattr_setschedpolicy]]]*/
{
	CRT_UNIMPLEMENTED("posix_spawnattr_setschedpolicy"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:posix_spawnattr_setschedpolicy]]]*/

/*[[[head:posix_spawnattr_getschedparam,hash:CRC-32=0x6ace26d5]]]*/
/* Get scheduling parameters from the attribute structure */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.exec.posix_spawn.posix_spawnattr_getschedparam") int
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_getschedparam)(posix_spawnattr_t const *__restrict attr,
                                                         struct sched_param *__restrict schedparam)
/*[[[body:posix_spawnattr_getschedparam]]]*/
{
	CRT_UNIMPLEMENTED("posix_spawnattr_getschedparam"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:posix_spawnattr_getschedparam]]]*/

/*[[[head:posix_spawnattr_setschedparam,hash:CRC-32=0x60d6be18]]]*/
/* Store scheduling parameters in the attribute structure */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.exec.posix_spawn.posix_spawnattr_setschedparam") int
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_setschedparam)(posix_spawnattr_t *__restrict attr,
                                                         struct sched_param const *__restrict schedparam)
/*[[[body:posix_spawnattr_setschedparam]]]*/
{
	CRT_UNIMPLEMENTED("posix_spawnattr_setschedparam"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:posix_spawnattr_setschedparam]]]*/

/*[[[head:posix_spawn_file_actions_init,hash:CRC-32=0x50551f02]]]*/
/* Initialize data structure for file attribute for `spawn' call */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.exec.posix_spawn.posix_spawn_file_actions_init") int
NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_init)(posix_spawn_file_actions_t *__restrict file_actions)
/*[[[body:posix_spawn_file_actions_init]]]*/
{
	CRT_UNIMPLEMENTED("posix_spawn_file_actions_init"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:posix_spawn_file_actions_init]]]*/

/*[[[head:posix_spawn_file_actions_destroy,hash:CRC-32=0x72454da7]]]*/
/* Free resources associated with FILE-ACTIONS */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.exec.posix_spawn.posix_spawn_file_actions_destroy") int
NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_destroy)(posix_spawn_file_actions_t *__restrict file_actions)
/*[[[body:posix_spawn_file_actions_destroy]]]*/
{
	CRT_UNIMPLEMENTED("posix_spawn_file_actions_destroy"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:posix_spawn_file_actions_destroy]]]*/

/*[[[head:posix_spawn_file_actions_addopen,hash:CRC-32=0x78758c3a]]]*/
/* Add an action to FILE-ACTIONS which tells the implementation
 * to call `open' for the given file during the `spawn' call */
INTERN NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.exec.posix_spawn.posix_spawn_file_actions_addopen") int
NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_addopen)(posix_spawn_file_actions_t *__restrict file_actions,
                                                            fd_t fd,
                                                            char const *__restrict path,
                                                            oflag_t oflags,
                                                            mode_t mode)
/*[[[body:posix_spawn_file_actions_addopen]]]*/
{
	CRT_UNIMPLEMENTED("posix_spawn_file_actions_addopen"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:posix_spawn_file_actions_addopen]]]*/

/*[[[head:posix_spawn_file_actions_addclose,hash:CRC-32=0xfea4c696]]]*/
/* Add an action to FILE-ACTIONS which tells the implementation to
 * call `close' for the given file descriptor during the `spawn' call */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.exec.posix_spawn.posix_spawn_file_actions_addclose") int
NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_addclose)(posix_spawn_file_actions_t *__restrict file_actions,
                                                             fd_t fd)
/*[[[body:posix_spawn_file_actions_addclose]]]*/
{
	CRT_UNIMPLEMENTED("posix_spawn_file_actions_addclose"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:posix_spawn_file_actions_addclose]]]*/

/*[[[head:posix_spawn_file_actions_adddup2,hash:CRC-32=0x4d327012]]]*/
/* Add an action to FILE-ACTIONS which tells the implementation to
 * call `dup2' for the given file descriptors during the `spawn' call */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.exec.posix_spawn.posix_spawn_file_actions_adddup2") int
NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_adddup2)(posix_spawn_file_actions_t *__restrict file_actions,
                                                            fd_t fd,
                                                            fd_t newfd)
/*[[[body:posix_spawn_file_actions_adddup2]]]*/
{
	CRT_UNIMPLEMENTED("posix_spawn_file_actions_adddup2"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:posix_spawn_file_actions_adddup2]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x1adba2e2]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(posix_spawn, libc_posix_spawn);
DEFINE_PUBLIC_WEAK_ALIAS(posix_spawnp, libc_posix_spawnp);
DEFINE_PUBLIC_WEAK_ALIAS(posix_spawnattr_init, libc_posix_spawnattr_init);
DEFINE_PUBLIC_WEAK_ALIAS(posix_spawnattr_destroy, libc_posix_spawnattr_destroy);
DEFINE_PUBLIC_WEAK_ALIAS(posix_spawnattr_getsigdefault, libc_posix_spawnattr_getsigdefault);
DEFINE_PUBLIC_WEAK_ALIAS(posix_spawnattr_setsigdefault, libc_posix_spawnattr_setsigdefault);
DEFINE_PUBLIC_WEAK_ALIAS(posix_spawnattr_getsigmask, libc_posix_spawnattr_getsigmask);
DEFINE_PUBLIC_WEAK_ALIAS(posix_spawnattr_setsigmask, libc_posix_spawnattr_setsigmask);
DEFINE_PUBLIC_WEAK_ALIAS(posix_spawnattr_getflags, libc_posix_spawnattr_getflags);
DEFINE_PUBLIC_WEAK_ALIAS(posix_spawnattr_setflags, libc_posix_spawnattr_setflags);
DEFINE_PUBLIC_WEAK_ALIAS(posix_spawnattr_getpgroup, libc_posix_spawnattr_getpgroup);
DEFINE_PUBLIC_WEAK_ALIAS(posix_spawnattr_setpgroup, libc_posix_spawnattr_setpgroup);
DEFINE_PUBLIC_WEAK_ALIAS(posix_spawnattr_getschedpolicy, libc_posix_spawnattr_getschedpolicy);
DEFINE_PUBLIC_WEAK_ALIAS(posix_spawnattr_setschedpolicy, libc_posix_spawnattr_setschedpolicy);
DEFINE_PUBLIC_WEAK_ALIAS(posix_spawnattr_getschedparam, libc_posix_spawnattr_getschedparam);
DEFINE_PUBLIC_WEAK_ALIAS(posix_spawnattr_setschedparam, libc_posix_spawnattr_setschedparam);
DEFINE_PUBLIC_WEAK_ALIAS(posix_spawn_file_actions_init, libc_posix_spawn_file_actions_init);
DEFINE_PUBLIC_WEAK_ALIAS(posix_spawn_file_actions_destroy, libc_posix_spawn_file_actions_destroy);
DEFINE_PUBLIC_WEAK_ALIAS(posix_spawn_file_actions_addopen, libc_posix_spawn_file_actions_addopen);
DEFINE_PUBLIC_WEAK_ALIAS(posix_spawn_file_actions_addclose, libc_posix_spawn_file_actions_addclose);
DEFINE_PUBLIC_WEAK_ALIAS(posix_spawn_file_actions_adddup2, libc_posix_spawn_file_actions_adddup2);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SPAWN_C */
