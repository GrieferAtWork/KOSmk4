/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
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

/*[[[head:libc_posix_spawn,hash:CRC-32=0x29a71edd]]]*/
/* Spawn a new process executing PATH with the attributes describes in *ATTRP.
 * Before running the process perform the actions described in FILE-ACTIONS.
 * This function is a possible cancellation point and therefore not marked with __THROW */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") NONNULL((1, 2, 5, 6)) int
NOTHROW_RPC(LIBCCALL libc_posix_spawn)(pid_t *__restrict pid,
                                       char const *__restrict path,
                                       posix_spawn_file_actions_t const *file_actions,
                                       posix_spawnattr_t const *attrp,
                                       __TARGV,
                                       __TENVP)
/*[[[body:libc_posix_spawn]]]*/
/*AUTO*/{
	(void)pid;
	(void)path;
	(void)file_actions;
	(void)attrp;
	(void)___argv;
	(void)___envp;
	CRT_UNIMPLEMENTED("posix_spawn"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_posix_spawn]]]*/

/*[[[head:libc_posix_spawnp,hash:CRC-32=0xcd5fbcd2]]]*/
/* Similar to `posix_spawn' but search for FILE in the PATH.
 * This function is a possible cancellation point and therefore not marked with __THROW */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") NONNULL((1, 2, 5, 6)) int
NOTHROW_RPC(LIBCCALL libc_posix_spawnp)(pid_t *__restrict pid,
                                        const char *__restrict file,
                                        posix_spawn_file_actions_t const *file_actions,
                                        posix_spawnattr_t const *attrp,
                                        __TARGV,
                                        __TENVP)
/*[[[body:libc_posix_spawnp]]]*/
/*AUTO*/{
	(void)pid;
	(void)file;
	(void)file_actions;
	(void)attrp;
	(void)___argv;
	(void)___envp;
	CRT_UNIMPLEMENTED("posix_spawnp"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_posix_spawnp]]]*/

/*[[[head:libc_posix_spawnattr_init,hash:CRC-32=0xabb7b0a3]]]*/
/* Initialize data structure with attributes for `spawn' to default values */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_init)(posix_spawnattr_t *__restrict attr)
/*[[[body:libc_posix_spawnattr_init]]]*/
/*AUTO*/{
	(void)attr;
	CRT_UNIMPLEMENTED("posix_spawnattr_init"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_posix_spawnattr_init]]]*/

/*[[[head:libc_posix_spawnattr_destroy,hash:CRC-32=0x9bc94dc6]]]*/
/* Free resources associated with ATTR */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_destroy)(posix_spawnattr_t *__restrict attr)
/*[[[body:libc_posix_spawnattr_destroy]]]*/
/*AUTO*/{
	(void)attr;
	CRT_UNIMPLEMENTED("posix_spawnattr_destroy"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_posix_spawnattr_destroy]]]*/

/*[[[head:libc_posix_spawnattr_getsigdefault,hash:CRC-32=0x3753a695]]]*/
/* Store signal mask for signals with default handling from ATTR in SIGDEFAULT */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_getsigdefault)(posix_spawnattr_t const *__restrict attr,
                                                         sigset_t *__restrict sigdefault)
/*[[[body:libc_posix_spawnattr_getsigdefault]]]*/
/*AUTO*/{
	(void)attr;
	(void)sigdefault;
	CRT_UNIMPLEMENTED("posix_spawnattr_getsigdefault"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_posix_spawnattr_getsigdefault]]]*/

/*[[[head:libc_posix_spawnattr_setsigdefault,hash:CRC-32=0xe3cfa293]]]*/
/* Set signal mask for signals with default handling in ATTR to SIGDEFAULT */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_setsigdefault)(posix_spawnattr_t *__restrict attr,
                                                         sigset_t const *__restrict sigdefault)
/*[[[body:libc_posix_spawnattr_setsigdefault]]]*/
/*AUTO*/{
	(void)attr;
	(void)sigdefault;
	CRT_UNIMPLEMENTED("posix_spawnattr_setsigdefault"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_posix_spawnattr_setsigdefault]]]*/

/*[[[head:libc_posix_spawnattr_getsigmask,hash:CRC-32=0xf5954b71]]]*/
/* Store signal mask for the new process from ATTR in SIGMASK */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_getsigmask)(posix_spawnattr_t const *__restrict attr,
                                                      sigset_t *__restrict sigmask)
/*[[[body:libc_posix_spawnattr_getsigmask]]]*/
/*AUTO*/{
	(void)attr;
	(void)sigmask;
	CRT_UNIMPLEMENTED("posix_spawnattr_getsigmask"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_posix_spawnattr_getsigmask]]]*/

/*[[[head:libc_posix_spawnattr_setsigmask,hash:CRC-32=0x917b3e07]]]*/
/* Set signal mask for the new process in ATTR to SIGMASK */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_setsigmask)(posix_spawnattr_t *__restrict attr,
                                                      sigset_t const *__restrict sigmask)
/*[[[body:libc_posix_spawnattr_setsigmask]]]*/
/*AUTO*/{
	(void)attr;
	(void)sigmask;
	CRT_UNIMPLEMENTED("posix_spawnattr_setsigmask"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_posix_spawnattr_setsigmask]]]*/

/*[[[head:libc_posix_spawnattr_getflags,hash:CRC-32=0x4ed567d4]]]*/
/* Get flag word from the attribute structure */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_getflags)(posix_spawnattr_t const *__restrict attr,
                                                    int16_t *__restrict flags)
/*[[[body:libc_posix_spawnattr_getflags]]]*/
/*AUTO*/{
	(void)attr;
	(void)flags;
	CRT_UNIMPLEMENTED("posix_spawnattr_getflags"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_posix_spawnattr_getflags]]]*/

/*[[[head:libc_posix_spawnattr_setflags,hash:CRC-32=0xf6c54eab]]]*/
/* Store flags in the attribute structure */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_setflags)(posix_spawnattr_t *__restrict attr,
                                                    short int flags)
/*[[[body:libc_posix_spawnattr_setflags]]]*/
/*AUTO*/{
	(void)attr;
	(void)flags;
	CRT_UNIMPLEMENTED("posix_spawnattr_setflags"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_posix_spawnattr_setflags]]]*/

/*[[[head:libc_posix_spawnattr_getpgroup,hash:CRC-32=0x5828c9f1]]]*/
/* Get process group ID from the attribute structure */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_getpgroup)(posix_spawnattr_t const *__restrict attr,
                                                     pid_t *__restrict pgroup)
/*[[[body:libc_posix_spawnattr_getpgroup]]]*/
/*AUTO*/{
	(void)attr;
	(void)pgroup;
	CRT_UNIMPLEMENTED("posix_spawnattr_getpgroup"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_posix_spawnattr_getpgroup]]]*/

/*[[[head:libc_posix_spawnattr_setpgroup,hash:CRC-32=0x1d57ff21]]]*/
/* Store rocess group ID in the attribute structure */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_setpgroup)(posix_spawnattr_t *__restrict attr,
                                                     pid_t pgroup)
/*[[[body:libc_posix_spawnattr_setpgroup]]]*/
/*AUTO*/{
	(void)attr;
	(void)pgroup;
	CRT_UNIMPLEMENTED("posix_spawnattr_setpgroup"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_posix_spawnattr_setpgroup]]]*/

/*[[[head:libc_posix_spawnattr_getschedpolicy,hash:CRC-32=0xbfd5060b]]]*/
/* Get scheduling policy from the attribute structure */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_getschedpolicy)(posix_spawnattr_t const *__restrict attr,
                                                          int *__restrict schedpolicy)
/*[[[body:libc_posix_spawnattr_getschedpolicy]]]*/
/*AUTO*/{
	(void)attr;
	(void)schedpolicy;
	CRT_UNIMPLEMENTED("posix_spawnattr_getschedpolicy"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_posix_spawnattr_getschedpolicy]]]*/

/*[[[head:libc_posix_spawnattr_setschedpolicy,hash:CRC-32=0xdbc5dceb]]]*/
/* Store scheduling policy in the attribute structure */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_setschedpolicy)(posix_spawnattr_t *__restrict attr,
                                                          int schedpolicy)
/*[[[body:libc_posix_spawnattr_setschedpolicy]]]*/
/*AUTO*/{
	(void)attr;
	(void)schedpolicy;
	CRT_UNIMPLEMENTED("posix_spawnattr_setschedpolicy"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_posix_spawnattr_setschedpolicy]]]*/

/*[[[head:libc_posix_spawnattr_getschedparam,hash:CRC-32=0x85459291]]]*/
/* Get scheduling parameters from the attribute structure */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_getschedparam)(posix_spawnattr_t const *__restrict attr,
                                                         struct sched_param *__restrict schedparam)
/*[[[body:libc_posix_spawnattr_getschedparam]]]*/
/*AUTO*/{
	(void)attr;
	(void)schedparam;
	CRT_UNIMPLEMENTED("posix_spawnattr_getschedparam"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_posix_spawnattr_getschedparam]]]*/

/*[[[head:libc_posix_spawnattr_setschedparam,hash:CRC-32=0xc049bcd4]]]*/
/* Store scheduling parameters in the attribute structure */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_setschedparam)(posix_spawnattr_t *__restrict attr,
                                                         struct sched_param const *__restrict schedparam)
/*[[[body:libc_posix_spawnattr_setschedparam]]]*/
/*AUTO*/{
	(void)attr;
	(void)schedparam;
	CRT_UNIMPLEMENTED("posix_spawnattr_setschedparam"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_posix_spawnattr_setschedparam]]]*/

/*[[[head:libc_posix_spawn_file_actions_init,hash:CRC-32=0x4ea59a5d]]]*/
/* Initialize data structure for file attribute for `spawn' call */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_init)(posix_spawn_file_actions_t *__restrict file_actions)
/*[[[body:libc_posix_spawn_file_actions_init]]]*/
/*AUTO*/{
	(void)file_actions;
	CRT_UNIMPLEMENTED("posix_spawn_file_actions_init"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_posix_spawn_file_actions_init]]]*/

/*[[[head:libc_posix_spawn_file_actions_destroy,hash:CRC-32=0x85ca4971]]]*/
/* Free resources associated with FILE-ACTIONS */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_destroy)(posix_spawn_file_actions_t *__restrict file_actions)
/*[[[body:libc_posix_spawn_file_actions_destroy]]]*/
/*AUTO*/{
	(void)file_actions;
	CRT_UNIMPLEMENTED("posix_spawn_file_actions_destroy"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_posix_spawn_file_actions_destroy]]]*/

/*[[[head:libc_posix_spawn_file_actions_addopen,hash:CRC-32=0x2d851093]]]*/
/* Add an action to FILE-ACTIONS which tells the implementation
 * to call `open' for the given file during the `spawn' call */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") NONNULL((1, 3)) int
NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_addopen)(posix_spawn_file_actions_t *__restrict file_actions,
                                                            fd_t fd,
                                                            char const *__restrict path,
                                                            oflag_t oflags,
                                                            mode_t mode)
/*[[[body:libc_posix_spawn_file_actions_addopen]]]*/
/*AUTO*/{
	(void)file_actions;
	(void)fd;
	(void)path;
	(void)oflags;
	(void)mode;
	CRT_UNIMPLEMENTED("posix_spawn_file_actions_addopen"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_posix_spawn_file_actions_addopen]]]*/

/*[[[head:libc_posix_spawn_file_actions_addclose,hash:CRC-32=0xd0a2ac0]]]*/
/* Add an action to FILE-ACTIONS which tells the implementation to
 * call `close' for the given file descriptor during the `spawn' call */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_addclose)(posix_spawn_file_actions_t *__restrict file_actions,
                                                             fd_t fd)
/*[[[body:libc_posix_spawn_file_actions_addclose]]]*/
/*AUTO*/{
	(void)file_actions;
	(void)fd;
	CRT_UNIMPLEMENTED("posix_spawn_file_actions_addclose"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_posix_spawn_file_actions_addclose]]]*/

/*[[[head:libc_posix_spawn_file_actions_adddup2,hash:CRC-32=0xb2eede1c]]]*/
/* Add an action to FILE-ACTIONS which tells the implementation to
 * call `dup2' for the given file descriptors during the `spawn' call */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_adddup2)(posix_spawn_file_actions_t *__restrict file_actions,
                                                            fd_t fd,
                                                            fd_t newfd)
/*[[[body:libc_posix_spawn_file_actions_adddup2]]]*/
/*AUTO*/{
	(void)file_actions;
	(void)fd;
	(void)newfd;
	CRT_UNIMPLEMENTED("posix_spawn_file_actions_adddup2"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_posix_spawn_file_actions_adddup2]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x5c4c3f63]]]*/
DEFINE_PUBLIC_ALIAS(posix_spawn, libc_posix_spawn);
DEFINE_PUBLIC_ALIAS(posix_spawnp, libc_posix_spawnp);
DEFINE_PUBLIC_ALIAS(posix_spawnattr_init, libc_posix_spawnattr_init);
DEFINE_PUBLIC_ALIAS(posix_spawnattr_destroy, libc_posix_spawnattr_destroy);
DEFINE_PUBLIC_ALIAS(posix_spawnattr_getsigdefault, libc_posix_spawnattr_getsigdefault);
DEFINE_PUBLIC_ALIAS(posix_spawnattr_setsigdefault, libc_posix_spawnattr_setsigdefault);
DEFINE_PUBLIC_ALIAS(posix_spawnattr_getsigmask, libc_posix_spawnattr_getsigmask);
DEFINE_PUBLIC_ALIAS(posix_spawnattr_setsigmask, libc_posix_spawnattr_setsigmask);
DEFINE_PUBLIC_ALIAS(posix_spawnattr_getflags, libc_posix_spawnattr_getflags);
DEFINE_PUBLIC_ALIAS(posix_spawnattr_setflags, libc_posix_spawnattr_setflags);
DEFINE_PUBLIC_ALIAS(posix_spawnattr_getpgroup, libc_posix_spawnattr_getpgroup);
DEFINE_PUBLIC_ALIAS(posix_spawnattr_setpgroup, libc_posix_spawnattr_setpgroup);
DEFINE_PUBLIC_ALIAS(posix_spawnattr_getschedpolicy, libc_posix_spawnattr_getschedpolicy);
DEFINE_PUBLIC_ALIAS(posix_spawnattr_setschedpolicy, libc_posix_spawnattr_setschedpolicy);
DEFINE_PUBLIC_ALIAS(posix_spawnattr_getschedparam, libc_posix_spawnattr_getschedparam);
DEFINE_PUBLIC_ALIAS(posix_spawnattr_setschedparam, libc_posix_spawnattr_setschedparam);
DEFINE_PUBLIC_ALIAS(posix_spawn_file_actions_init, libc_posix_spawn_file_actions_init);
DEFINE_PUBLIC_ALIAS(posix_spawn_file_actions_destroy, libc_posix_spawn_file_actions_destroy);
DEFINE_PUBLIC_ALIAS(posix_spawn_file_actions_addopen, libc_posix_spawn_file_actions_addopen);
DEFINE_PUBLIC_ALIAS(posix_spawn_file_actions_addclose, libc_posix_spawn_file_actions_addclose);
DEFINE_PUBLIC_ALIAS(posix_spawn_file_actions_adddup2, libc_posix_spawn_file_actions_adddup2);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SPAWN_C */
