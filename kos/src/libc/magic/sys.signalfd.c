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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/signalfd.h) */
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/sys/signalfd.h) */
/* (#) Portability: diet libc     (/include/sys/signalfd.h) */
/* (#) Portability: musl libc     (/include/sys/signalfd.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.sched.signalfd")]

%[define_decl_include_implication("<bits/os/sigset.h>" => ["<hybrid/typecore.h>"])]
%[define_decl_include("<bits/os/sigset.h>": ["struct __sigset_struct"])]

%[define_decl_include_implication("<bits/os/sigset.h>" => ["<hybrid/typecore.h>"])]
%[define_decl_include("<bits/os/sigset.h>": ["struct __sigset_struct"])]
%[define_replacement(sigset_t = "struct __sigset_struct")]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <asm/os/signalfd.h>          /* __SFD_*/
)]%[insert:prefix(
#include <bits/os/signalfd_siginfo.h> /* struct signalfd_siginfo */
)]%[insert:prefix(
#include <bits/os/sigset.h>           /* struct __sigset_struct */
)]%[insert:prefix(
#include <bits/types.h>               /* __fd_t */
)]%{

#ifdef __USE_GLIBC
#include <stdint.h>
#endif /* __USE_GLIBC */



/* Flags for signalfd. */
#if (defined(__SFD_NONBLOCK) || defined(__SFD_CLOEXEC) || \
     defined(__SFD_CLOFORK))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __SFD_NONBLOCK
	SFD_NONBLOCK = __SFD_NONBLOCK, /* Do not block when trying to read data that hasn't been written, yet. */
#endif /* __SFD_NONBLOCK */
#ifdef __SFD_CLOEXEC
	SFD_CLOEXEC  = __SFD_CLOEXEC,  /* Close the file during exec() */
#endif /* __SFD_CLOEXEC */
#ifdef __SFD_CLOFORK
	SFD_CLOFORK  = __SFD_CLOFORK,  /* Close the handle when the file descriptors are unshared (s.a. `CLONE_FILES') */
#endif /* __SFD_CLOFORK */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __SFD_NONBLOCK
#define SFD_NONBLOCK SFD_NONBLOCK /* Do not block when trying to read data that hasn't been written, yet. */
#endif /* __SFD_NONBLOCK */
#ifdef __SFD_CLOEXEC
#define SFD_CLOEXEC  SFD_CLOEXEC  /* Close the file during exec() */
#endif /* __SFD_CLOEXEC */
#ifdef __SFD_CLOFORK
#define SFD_CLOFORK  SFD_CLOFORK  /* Close the handle when the file descriptors are unshared (s.a. `CLONE_FILES') */
#endif /* __SFD_CLOFORK */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __SFD_NONBLOCK
#define SFD_NONBLOCK __SFD_NONBLOCK /* Do not block when trying to read data that hasn't been written, yet. */
#endif /* __SFD_NONBLOCK */
#ifdef __SFD_CLOEXEC
#define SFD_CLOEXEC  __SFD_CLOEXEC  /* Close the file during exec() */
#endif /* __SFD_CLOEXEC */
#ifdef __SFD_CLOFORK
#define SFD_CLOFORK  __SFD_CLOFORK  /* Close the handle when the file descriptors are unshared (s.a. `CLONE_FILES') */
#endif /* __SFD_CLOFORK */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __SFD_NONBLOCK || __SFD_CLOEXEC || __SFD_CLOFORK */


#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __sigset_t_defined
#define __sigset_t_defined
typedef struct __sigset_struct sigset_t;
#endif /* !__sigset_t_defined */

}

@@>> signalfd(2)
@@Create or update a poll(2)-able file descriptor which can be used to
@@wait for the delivery of signals masked by `sigmask' to the  waiting
@@thread/process.
@@@param: fd:    When `-1', create a new signalfd object; Otherwise,
@@               the FD number of  the signalfd object who's  signal
@@               mask should be updated to `sigmask'.
@@@param: flags: Set of `0 | SFD_NONBLOCK | SFD_CLOEXEC | SFD_CLOFORK'
@@               Meaningless,  but  still  validated  when  `fd != -1'
[[wunused, decl_include("<features.h>", "<bits/os/sigset.h>", "<bits/types.h>")]]
$fd_t signalfd($fd_t fd, [[in]] sigset_t const *sigmask,
               __STDC_INT_AS_UINT_T flags);

%{

__SYSDECL_END
#endif /* __CC__ */

}
