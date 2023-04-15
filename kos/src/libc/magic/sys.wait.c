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
%(c_prefix){
/* (>) Standard: POSIX.1c (Issue 3, IEEE Std 1003.1c-1995) */
/* (#) Portability: Cygwin        (/newlib/libc/include/sys/wait.h) */
/* (#) Portability: DJGPP         (/include/sys/wait.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/wait.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/wait.h) */
/* (#) Portability: FreeBSD       (/sys/sys/wait.h) */
/* (#) Portability: GNU C Library (/posix/sys/wait.h) */
/* (#) Portability: NetBSD        (/sys/sys/wait.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/sys/wait.h) */
/* (#) Portability: OpenBSD       (/sys/sys/wait.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/wait.h) */
/* (#) Portability: diet libc     (/include/sys/wait.h) */
/* (#) Portability: libc4/5       (/include/sys/wait.h) */
/* (#) Portability: mintlib       (/include/sys/wait.h) */
/* (#) Portability: musl libc     (/include/sys/wait.h) */
/* (#) Portability: uClibc        (/include/sys/wait.h) */
}

%[define_decl_include_implication("<bits/os/siginfo.h>" => ["<hybrid/typecore.h>"])]
%[define_decl_include("<bits/os/siginfo.h>": ["struct __siginfo_struct"])]

%[define_decl_include("<bits/os/rusage.h>": ["struct rusage", "struct rusage64"])]

%[define_replacement(pid_t = __pid_t)]
%[define_replacement(rusage32 = __rusage32)]
%[define_replacement(rusage64 = __rusage64)]
%[define_replacement(idtype_t = int)]
%[default:section(".text.crt{|.dos}.sched.wait")]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <asm/os/wait.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <parts/waitmacros.h>
)]%{

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#include <bits/os/siginfo.h> /* `struct __siginfo_struct' */
#endif /* __USE_XOPEN || __USE_XOPEN2K8 */


/* Macros for constructing wait status values. */
#ifdef __USE_MISC
#if !defined(WCOREFLAG) && defined(__WCOREFLAG)
#define WCOREFLAG __WCOREFLAG
#endif /* !WCOREFLAG && __WCOREFLAG */
#if !defined(WCOREDUMP) && defined(__WCOREDUMP)
#define WCOREDUMP(status) __WCOREDUMP(__WAIT_INT(status))
#endif /* !WCOREDUMP && __WCOREDUMP */
#if !defined(W_EXITCODE) && defined(__W_EXITCODE)
#define W_EXITCODE(ret, sig) __W_EXITCODE(ret, sig)
#endif /* !W_EXITCODE && __W_EXITCODE */
#if !defined(W_STOPCODE) && defined(__W_STOPCODE)
#define W_STOPCODE(sig) __W_STOPCODE(sig)
#endif /* !W_STOPCODE && __W_STOPCODE */

#if !defined(WAIT_ANY) && defined(__WAIT_ANY)
#define WAIT_ANY __WAIT_ANY /* Any process. */
#endif /* !WAIT_ANY && __WAIT_ANY */
#if !defined(WAIT_MYPGRP) && defined(__WAIT_MYPGRP)
#define WAIT_MYPGRP __WAIT_MYPGRP /* Any process in my process group. */
#endif /* !WAIT_MYPGRP && __WAIT_MYPGRP */
#endif /* __USE_MISC */


#ifdef __CC__
__SYSDECL_BEGIN

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#ifndef __siginfo_t_defined
#define __siginfo_t_defined
typedef struct __siginfo_struct siginfo_t;
#endif /* !__siginfo_t_defined */
#endif /* __USE_XOPEN || __USE_XOPEN2K8 */

}


@@>> wait(2)
@@Wait for any child process (same as `waitpid(-1, STAT_LOC, 0);')
[[cp, export_alias("__wait"), decl_include("<bits/types.h>", "<parts/waitmacros.h>")]]
$pid_t wait(/*[[out_opt]]*/ __WAIT_STATUS stat_loc);

@@>> waitpid(2)
@@Wait for a child process:
@@ - `pid < -1':  Wait for any child process whose process group ID is `-PID'
@@ - `pid == -1': Wait for any child process
@@ - `pid == 0':  Wait for any child process whose process group ID is that of the caller
@@ - `pid > 0':   Wait for the child whose process ID is equal to `PID'
@@@param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted)
[[decl_include("<bits/types.h>", "<features.h>", "<parts/waitmacros.h>")]]
[[cp, export_alias("__waitpid")]]
$pid_t waitpid($pid_t pid, /*[[out_opt]]*/ __WAIT_STATUS stat_loc,
               __STDC_INT_AS_UINT_T options);

%
%#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
%{
#ifndef __id_t_defined
#define __id_t_defined
typedef __id_t id_t;
#endif /* !__id_t_defined */
}

@@>> waitid(2)
@@@param: idtype:  One of `P_ALL', `P_PID', `P_PGID'
@@@param: options: At least one of `WEXITED', `WSTOPPED', `WCONTINUED',
@@                 optionally     or'd     with     `WNOHANG | WNOWAIT'
[[cp, decl_include("<features.h>", "<bits/os/siginfo.h>", "<bits/types.h>")]]
int waitid(idtype_t idtype, id_t id,
           [[out_opt]] siginfo_t *infop,
           __STDC_INT_AS_UINT_T options);
%#endif /* __USE_XOPEN || __USE_XOPEN2K8 */

%
%#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
%struct rusage;

[[decl_include("<bits/types.h>", "<features.h>")]]
[[decl_include("<bits/os/rusage.h>", "<parts/waitmacros.h>")]]
[[cp, doc_alias("wait3"), ignore, nocrt, alias("wait3", "__wait3")]]
$pid_t wait3_32(/*[[out_opt]]*/ __WAIT_STATUS stat_loc,
                __STDC_INT_AS_UINT_T options,
                [[out_opt]] struct $rusage32 *usage);

@@>> wait3(2), wait3_64(2)
@@Same as `waitpid(-1, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
@@@param options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted)
[[cp, no_crt_self_import, export_as("__wait3")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("wait3", "__wait3")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("wait3_64")]]
[[userimpl, requires($has_function(wait3_32) || $has_function(wait3_64))]]
[[decl_include("<bits/types.h>", "<features.h>")]]
[[decl_include("<bits/os/rusage.h>", "<parts/waitmacros.h>")]]
[[impl_include("<bits/os/rusage-convert.h>")]]
$pid_t wait3(/*[[out_opt]]*/ __WAIT_STATUS stat_loc,
             __STDC_INT_AS_UINT_T options,
             [[out_opt]] struct rusage *usage) {
	pid_t result;
@@pp_if $has_function(wait3_32)@@
	struct rusage32 ru32;
	result = wait3_32(stat_loc, options, usage ? &ru32 : NULL);
	if (result >= 0 && usage)
		@rusage32_to_rusage@(&ru32, usage);
@@pp_else@@
	struct __rusage64 ru64;
	result = wait3_64(stat_loc, options, usage ? &ru64 : NULL);
	if (result >= 0 && usage)
		@rusage64_to_rusage@(&ru64, usage);
@@pp_endif@@
	return result;
}

%#ifdef __USE_TIME64
%struct rusage64;
[[decl_include("<features.h>", "<bits/types.h>", "<bits/os/rusage.h>", "<parts/waitmacros.h>")]]
[[impl_include("<bits/os/rusage.h>", "<bits/os/rusage-convert.h>", "<parts/waitmacros.h>")]]
[[preferred_time64_variant_of(wait3), doc_alias("wait3")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), preferred_alias("__wait3")]]
[[userimpl, requires_function(wait3_32)]]
$pid_t wait3_64(/*[[out_opt]]*/ __WAIT_STATUS stat_loc,
                __STDC_INT_AS_UINT_T options,
                [[out_opt]] struct rusage64 *usage) {
	pid_t result;
	struct rusage32 ru32;
	result = wait3_32(stat_loc, options, usage ? &ru32 : NULL);
	if (result >= 0 && usage)
		@rusage32_to_rusage64@(&ru32, usage);
	return result;
}
%#endif /* __USE_TIME64 */
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

%
%#ifdef __USE_MISC

[[decl_include("<bits/types.h>", "<features.h>")]]
[[decl_include("<bits/os/rusage.h>", "<parts/waitmacros.h>")]]
[[cp, doc_alias("wait4"), ignore, nocrt, alias("wait4", "__wait4", "__libc_wait4")]]
$pid_t wait4_32($pid_t pid, /*[[out_opt]]*/ __WAIT_STATUS stat_loc,
                __STDC_INT_AS_UINT_T options,
                [[out_opt]] struct $rusage32 *usage);

@@>> wait4(2), wait4_64(2)
@@Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
@@@param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted)
[[cp, decl_prefix(struct rusage;), no_crt_self_import, export_as("__wait4", "__libc_wait4")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("wait4", "__wait4", "__libc_wait4")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("wait4_64")]]
[[decl_include("<bits/types.h>", "<features.h>")]]
[[decl_include("<bits/os/rusage.h>", "<parts/waitmacros.h>")]]
[[impl_include("<bits/os/rusage-convert.h>")]]
[[userimpl, requires($has_function(wait4_32) || $has_function(wait4_64))]]
$pid_t wait4($pid_t pid, /*[[out_opt]]*/ __WAIT_STATUS stat_loc,
             __STDC_INT_AS_UINT_T options,
             [[out_opt]] struct rusage *usage) {
	pid_t result;
@@pp_if $has_function(wait4_32)@@
	struct rusage32 ru32;
	result = wait4_32(pid, stat_loc, options, usage ? &ru32 : NULL);
	if (result >= 0 && usage)
		@rusage32_to_rusage@(&ru32, usage);
@@pp_else@@
	struct __rusage64 ru64;
	result = wait4_64(pid, stat_loc, options, usage ? &ru64 : NULL);
	if (result >= 0 && usage)
		@rusage64_to_rusage@(&ru64, usage);
@@pp_endif@@
	return result;
}

%#ifdef __USE_TIME64
%struct rusage64;
[[preferred_time64_variant_of(wait4), doc_alias("wait4")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), preferred_alias("__wait4", "__libc_wait4")]]
[[decl_prefix(struct rusage64;)]]
[[decl_include("<bits/types.h>", "<features.h>")]]
[[decl_include("<bits/os/rusage.h>", "<parts/waitmacros.h>")]]
[[impl_include("<bits/os/rusage-convert.h>")]]
[[userimpl, requires_function(wait4_32)]]
$pid_t wait4_64($pid_t pid, /*[[out_opt]]*/ __WAIT_STATUS stat_loc,
                __STDC_INT_AS_UINT_T options,
                [[out_opt]] struct rusage64 *usage) {
	pid_t result;
	struct rusage32 ru32;
	result = wait4_32(pid, stat_loc, options, usage ? &ru32 : NULL);
	if (result >= 0 && usage)
		@rusage32_to_rusage64@(&ru32, usage);
	return result;
}
%#endif /* __USE_TIME64 */
%#endif /* __USE_MISC */

%
%#ifdef __USE_KOS
@@>> detach(2)
@@Detach the descriptor of `PID' from the thread that
@@would have received a signal when it changes state,
@@as well as prevent the  thread from turning into  a
@@zombie once it dies.
@@For simplicity, think of it like this:
@@  - pthread_create()  -->  clone()
@@  - pthread_join()    -->  wait()
@@  - pthread_detach()  -->  detach()  // Linux's missing link, now implemented
@@A total of 4 special cases exists to alter the behavior of this function:
@@  - PID == 0 || PID == gettid():
@@    Detach the calling  thread from  the set of  running children  within
@@    its own process.  Note however  that when this  is done  by the  main
@@    thread of the process, gettid() will equal getpid(), and the behavior
@@    will be different.
@@  - PID == getpid():
@@    Detach the calling process from its parent, essentially daemonizing
@@    the  calling   process   the   same  way   a   double-fork   would:
@@    >> if (fork() == 0) {
@@    >> 	if (fork() == 0) {
@@    >> 		// This is a daemonized process
@@    >> 		// aka. the parent process no longer knows
@@    >> 		// about us, and also can't wait(2) on us.
@@    >> 		...
@@    >> 	}
@@    >> 	exit(0);
@@    >> }
@@    Same as:
@@    >> if (fork() == 0) {
@@    >> 	detach(0); // or `detach(getpid())', since 0 --> gettid() and gettid() == getpid()
@@    >> 	// This is a daemonized process
@@    >> 	// aka. the parent process no longer knows
@@    >> 	// about us, and also can't wait(2) on us.
@@    >> 	...
@@    >> }
@@  - PID == -1:
@@    Detach all child processes/threads  of the calling process,  essentially
@@    turning its chain of children into a clean slate that no longer contains
@@    any wait(2)able child threads or processes.
@@    If no waitable children existed, `ECHILD' is set; else `0' is returned.
@@The given `pid' must be:
@@  - A thread without the caller's process
@@  - A child process of the caller's process
@@NOTE: If a thread is created using clone() with `CLONE_DETACHED' set,
@@      it will behave effectively as though this function had  already
@@      be called.
@@@return: -ECHILD:         `PID' was equal to `-1', but no waitable children existed
@@@throw: E_PROCESS_EXITED: No such  thread/process exists,  or  the thread  isn't  isn't
@@                          a thread in your process, or a child process of your process.
[[decl_include("<bits/types.h>")]]
int detach($pid_t pid);
%#endif /* __USE_KOS */

%{

__SYSDECL_END
#endif /* __CC__ */

}
