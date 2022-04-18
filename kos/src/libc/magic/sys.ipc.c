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
%(c_prefix){
/* (>) Standard: POSIX.1b (Issue 2, IEEE Std 1003.1b-1993) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/ipc.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/ipc.h) */
/* (#) Portability: FreeBSD       (/sys/sys/ipc.h) */
/* (#) Portability: GNU C Library (/sysvipc/sys/ipc.h) */
/* (#) Portability: NetBSD        (/sys/sys/ipc.h) */
/* (#) Portability: OpenBSD       (/sys/sys/ipc.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/ipc.h) */
/* (#) Portability: diet libc     (/include/sys/ipc.h) */
/* (#) Portability: libc4/5       (/include/sys/ipc.h) */
/* (#) Portability: mintlib       (/include/sys/ipc.h) */
/* (#) Portability: musl libc     (/include/sys/ipc.h) */
/* (#) Portability: uClibc        (/include/sys/ipc.h) */
}

%[define_replacement(uid_t = __uid_t)]
%[define_replacement(gid_t = __gid_t)]
%[define_replacement(mode_t = __mode_t)]
%[define_replacement(key_t = __key_t)]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <asm/os/ipc.h>
)]%[insert:prefix(
#include <bits/os/ipc.h>
)]%{


/* Mode flags for `msgget()', `semget()', and `shmget()'. */
#if !defined(IPC_CREAT) && defined(__IPC_CREAT)
#define IPC_CREAT  __IPC_CREAT  /* ??? */
#endif /* !IPC_CREAT && __IPC_CREAT */
#if !defined(IPC_EXCL) && defined(__IPC_EXCL)
#define IPC_EXCL   __IPC_EXCL   /* ??? */
#endif /* !IPC_EXCL && __IPC_EXCL */
#if !defined(IPC_NOWAIT) && defined(__IPC_NOWAIT)
#define IPC_NOWAIT __IPC_NOWAIT /* ??? */
#endif /* !IPC_NOWAIT && __IPC_NOWAIT */

/* Control commands for `msgctl', `semctl', and `shmctl'. */
#if !defined(IPC_RMID) && defined(__IPC_RMID)
#define IPC_RMID __IPC_RMID /* ??? */
#endif /* !IPC_RMID && __IPC_RMID */
#if !defined(IPC_SET) && defined(__IPC_SET)
#define IPC_SET  __IPC_SET  /* ??? */
#endif /* !IPC_SET && __IPC_SET */
#if !defined(IPC_STAT) && defined(__IPC_STAT)
#define IPC_STAT __IPC_STAT /* ??? */
#endif /* !IPC_STAT && __IPC_STAT */
#ifdef __USE_GNU
#if !defined(IPC_INFO) && defined(__IPC_INFO)
#define IPC_INFO __IPC_INFO /* ??? */
#endif /* !IPC_INFO && __IPC_INFO */
#endif /* __USE_GNU */

/* Special key values. */
#if !defined(IPC_PRIVATE) && defined(__IPC_PRIVATE)
#define IPC_PRIVATE (__CCAST(__key_t)__IPC_PRIVATE) /* ???. */
#endif /* !IPC_PRIVATE && __IPC_PRIVATE */


#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __uid_t_defined
#define __uid_t_defined
typedef __uid_t uid_t;
#endif /* !__uid_t_defined */

#ifndef __gid_t_defined
#define __gid_t_defined
typedef __gid_t gid_t;
#endif /* !__gid_t_defined */

#ifndef __mode_t_defined
#define __mode_t_defined
typedef __mode_t mode_t; /* INode type (Set of `S_*' from `<fcntl.h>' or `<sys/stat.h>') */
#endif /* !__mode_t_defined */

#ifndef __key_t_defined
#define __key_t_defined
typedef __key_t key_t;
#endif /* !__key_t_defined */

}

[[cp, decl_include("<features.h>")]]
key_t ftok([[nonnull]] char const *pathname,
           __STDC_INT_AS_UINT_T proj_id);

%{

__SYSDECL_END
#endif /* __CC__ */

}
