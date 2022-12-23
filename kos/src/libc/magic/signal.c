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
/* (>) Standard: ISO C89 (ANSI X3.159-1989) */
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/signal.h) */
/* (#) Portability: DJGPP         (/include/signal.h) */
/* (#) Portability: DragonFly BSD (/include/signal.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/signal.h) */
/* (#) Portability: FreeBSD       (/include/signal.h) */
/* (#) Portability: GNU C Library (/signal/signal.h) */
/* (#) Portability: MSVC          (/include/signal.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/signal.h) */
/* (#) Portability: NetBSD        (/include/signal.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/signal.h) */
/* (#) Portability: OpenBSD       (/include/signal.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/signal.h) */
/* (#) Portability: Windows Kits  (/ucrt/signal.h) */
/* (#) Portability: avr-libc      (/include/signal.h) */
/* (#) Portability: diet libc     (/include/signal.h) */
/* (#) Portability: libc4/5       (/include/signal.h) */
/* (#) Portability: libc6         (/include/signal.h) */
/* (#) Portability: mintlib       (/include/signal.h) */
/* (#) Portability: musl libc     (/include/signal.h) */
/* (#) Portability: uClibc        (/include/signal.h) */
}

%[define_decl_include_implication("<bits/os/sigevent.h>" => ["<hybrid/typecore.h>"])]
%[define_decl_include("<bits/os/sigevent.h>": ["struct sigevent"])]

%[define_decl_include_implication("<bits/os/sigval.h>" => ["<hybrid/typecore.h>"])]
%[define_decl_include("<bits/os/sigval.h>": ["union sigval"])]

%[define_decl_include_implication("<bits/os/siginfo.h>" => ["<hybrid/typecore.h>"])]
%[define_decl_include("<bits/os/siginfo.h>": ["struct __siginfo_struct"])]

%[define_decl_include_implication("<bits/os/sigset.h>" => ["<hybrid/typecore.h>"])]
%[define_decl_include("<bits/os/sigset.h>": ["struct __sigset_struct"])]

%[define_ccompat_header("csignal")]
%[define_replacement(longptr_t    = __LONGPTR_TYPE__)]
%[define_replacement(ulongptr_t   = __ULONGPTR_TYPE__)]
%[define_replacement(sighandler_t = __sighandler_t)]
%[define_replacement(siginfo_t    = "struct __siginfo_struct")]
%[define_replacement(sigset_t     = "struct __sigset_struct")]
%[define_replacement(sigval_t     = "union sigval")]
%[define_replacement(sigevent_t   = "struct sigevent")]
%[define_replacement(pid_t        = __pid_t)]
%[define_replacement(timespec32   = __timespec32)]
%[define_replacement(sig_atomic_t = __SIG_ATOMIC_TYPE__)]
%[define_replacement(sig_t        = __sighandler_t)]
%[define_replacement(timespec64   = __timespec64)]
%[define_replacement(NSIG         = __NSIG)]
%[define_replacement(_NSIG        = __NSIG)]
%[define_type_class(__sighandler_t = "TP")]
%[default:section(".text.crt{|.dos}.sched.signal")]

%[assume_defined_in_kos(SIG_ERR, __SIG_ERR)]
%[assume_defined_in_kos(SIG_DFL, __SIG_DFL)]
%[assume_defined_in_kos(SIG_IGN, __SIG_IGN)]
%[assume_defined_in_kos(SIG_GET, __SIG_GET)]
%[assume_defined_in_kos(SIG_HOLD, __SIG_HOLD)]
%[assume_defined_in_kos(SIG_TERM, __SIG_TERM)]
%[assume_defined_in_kos(SIG_EXIT, __SIG_EXIT)]
%[assume_defined_in_kos(SIG_CONT, __SIG_CONT)]
%[assume_defined_in_kos(SIG_STOP, __SIG_STOP)]
%[assume_defined_in_kos(SIG_CORE, __SIG_CORE)]
%[assume_defined_in_kos(SIGHUP, __SIGHUP)]
%[assume_defined_in_kos(SIGINT, __SIGINT)]
%[assume_defined_in_kos(SIGQUIT, __SIGQUIT)]
%[assume_defined_in_kos(SIGILL, __SIGILL)]
%[assume_defined_in_kos(SIGTRAP, __SIGTRAP)]
%[assume_defined_in_kos(SIGABRT, __SIGABRT)]
%[assume_defined_in_kos(SIGIOT, __SIGIOT)]
%[assume_defined_in_kos(SIGBUS, __SIGBUS)]
%[assume_defined_in_kos(SIGFPE, __SIGFPE)]
%[assume_defined_in_kos(SIGKILL, __SIGKILL)]
%[assume_defined_in_kos(SIGUSR1, __SIGUSR1)]
%[assume_defined_in_kos(SIGSEGV, __SIGSEGV)]
%[assume_defined_in_kos(SIGUSR2, __SIGUSR2)]
%[assume_defined_in_kos(SIGPIPE, __SIGPIPE)]
%[assume_defined_in_kos(SIGALRM, __SIGALRM)]
%[assume_defined_in_kos(SIGTERM, __SIGTERM)]
%[assume_defined_in_kos(SIGSTKFLT, __SIGSTKFLT)]
%[assume_defined_in_kos(SIGCHLD, __SIGCHLD)]
%[assume_defined_in_kos(SIGCONT, __SIGCONT)]
%[assume_defined_in_kos(SIGSTOP, __SIGSTOP)]
%[assume_defined_in_kos(SIGTSTP, __SIGTSTP)]
%[assume_defined_in_kos(SIGTTIN, __SIGTTIN)]
%[assume_defined_in_kos(SIGTTOU, __SIGTTOU)]
%[assume_defined_in_kos(SIGURG, __SIGURG)]
%[assume_defined_in_kos(SIGXCPU, __SIGXCPU)]
%[assume_defined_in_kos(SIGXFSZ, __SIGXFSZ)]
%[assume_defined_in_kos(SIGVTALRM, __SIGVTALRM)]
%[assume_defined_in_kos(SIGPROF, __SIGPROF)]
%[assume_defined_in_kos(SIGWINCH, __SIGWINCH)]
%[assume_defined_in_kos(SIGIO, __SIGIO)]
%[assume_defined_in_kos(SIGPOLL, __SIGPOLL)]
%[assume_defined_in_kos(SIGPWR, __SIGPWR)]
%[assume_defined_in_kos(SIGSYS, __SIGSYS)]
%[assume_defined_in_kos(SIGCLD, __SIGCHLD)]
%[assume_defined_in_kos(SIGRPC, __SIGRPC)]
%[assume_defined_in_kos(_NSIG, __NSIG)]
%[assume_defined_in_kos(SIGRTMIN, __SIGRTMIN)]
%[assume_defined_in_kos(SIGRTMAX, __SIGRTMAX)]
%[assume_defined_in_kos(SIGABRT_COMPAT, __SIGABRT)]
%[assume_defined_in_kos(SA_NOCLDSTOP, __SA_NOCLDSTOP)]
%[assume_defined_in_kos(SA_NOCLDWAIT, __SA_NOCLDWAIT)]
%[assume_defined_in_kos(SA_SIGINFO, __SA_SIGINFO)]
%[assume_defined_in_kos(SA_RESTORER, __SA_RESTORER)]
%[assume_defined_in_kos(SA_ONSTACK, __SA_ONSTACK)]
%[assume_defined_in_kos(SA_RESTART, __SA_RESTART)]
%[assume_defined_in_kos(SA_NODEFER, __SA_NODEFER)]
%[assume_defined_in_kos(SA_RESETHAND, __SA_RESETHAND)]
%[assume_defined_in_kos(SA_INTERRUPT, __SA_INTERRUPT)]
%[assume_defined_in_kos(SA_NOMASK, __SA_NODEFER)]
%[assume_defined_in_kos(SA_ONESHOT, __SA_RESETHAND)]
%[assume_defined_in_kos(SA_STACK, __SA_ONSTACK)]
%[assume_defined_in_kos(SIG_BLOCK, __SIG_BLOCK)]
%[assume_defined_in_kos(SIG_UNBLOCK, __SIG_UNBLOCK)]
%[assume_defined_in_kos(SIG_SETMASK, __SIG_SETMASK)]
%[assume_defined_in_kos(SIGEV_SIGNAL, __SIGEV_SIGNAL)]
%[assume_defined_in_kos(SIGEV_NONE, __SIGEV_NONE)]
%[assume_defined_in_kos(SIGEV_THREAD, __SIGEV_THREAD)]
%[assume_defined_in_kos(SIGEV_THREAD_ID, __SIGEV_THREAD_ID)]
%[assume_defined_in_kos(SIGEV_INLINE_THREAD, __SIGEV_INLINE_THREAD)]
%[assume_defined_in_kos(SI_ASYNCNL, __SI_ASYNCNL)]
%[assume_defined_in_kos(SI_TKILL, __SI_TKILL)]
%[assume_defined_in_kos(SI_SIGIO, __SI_SIGIO)]
%[assume_defined_in_kos(SI_ASYNCIO, __SI_ASYNCIO)]
%[assume_defined_in_kos(SI_MESGQ, __SI_MESGQ)]
%[assume_defined_in_kos(SI_TIMER, __SI_TIMER)]
%[assume_defined_in_kos(SI_QUEUE, __SI_QUEUE)]
%[assume_defined_in_kos(SI_USER, __SI_USER)]
%[assume_defined_in_kos(SI_KERNEL, __SI_KERNEL)]
%[assume_defined_in_kos(ILL_ILLOPC, __ILL_ILLOPC)]
%[assume_defined_in_kos(ILL_ILLOPN, __ILL_ILLOPN)]
%[assume_defined_in_kos(ILL_ILLADR, __ILL_ILLADR)]
%[assume_defined_in_kos(ILL_ILLTRP, __ILL_ILLTRP)]
%[assume_defined_in_kos(ILL_PRVOPC, __ILL_PRVOPC)]
%[assume_defined_in_kos(ILL_PRVREG, __ILL_PRVREG)]
%[assume_defined_in_kos(ILL_COPROC, __ILL_COPROC)]
%[assume_defined_in_kos(ILL_BADSTK, __ILL_BADSTK)]
%[assume_defined_in_kos(FPE_INTDIV, __FPE_INTDIV)]
%[assume_defined_in_kos(FPE_INTOVF, __FPE_INTOVF)]
%[assume_defined_in_kos(FPE_FLTDIV, __FPE_FLTDIV)]
%[assume_defined_in_kos(FPE_FLTOVF, __FPE_FLTOVF)]
%[assume_defined_in_kos(FPE_FLTUND, __FPE_FLTUND)]
%[assume_defined_in_kos(FPE_FLTRES, __FPE_FLTRES)]
%[assume_defined_in_kos(FPE_FLTINV, __FPE_FLTINV)]
%[assume_defined_in_kos(FPE_FLTSUB, __FPE_FLTSUB)]
%[assume_defined_in_kos(SEGV_MAPERR, __SEGV_MAPERR)]
%[assume_defined_in_kos(SEGV_ACCERR, __SEGV_ACCERR)]
%[assume_defined_in_kos(BUS_ADRALN, __BUS_ADRALN)]
%[assume_defined_in_kos(BUS_ADRERR, __BUS_ADRERR)]
%[assume_defined_in_kos(BUS_OBJERR, __BUS_OBJERR)]
%[assume_defined_in_kos(BUS_MCEERR_AR, __BUS_MCEERR_AR)]
%[assume_defined_in_kos(BUS_MCEERR_AO, __BUS_MCEERR_AO)]
%[assume_defined_in_kos(TRAP_BRKPT, __TRAP_BRKPT)]
%[assume_defined_in_kos(TRAP_TRACE, __TRAP_TRACE)]
%[assume_defined_in_kos(CLD_EXITED, __CLD_EXITED)]
%[assume_defined_in_kos(CLD_KILLED, __CLD_KILLED)]
%[assume_defined_in_kos(CLD_DUMPED, __CLD_DUMPED)]
%[assume_defined_in_kos(CLD_TRAPPED, __CLD_TRAPPED)]
%[assume_defined_in_kos(CLD_STOPPED, __CLD_STOPPED)]
%[assume_defined_in_kos(CLD_CONTINUED, __CLD_CONTINUED)]
%[assume_defined_in_kos(POLL_IN, __POLL_IN)]
%[assume_defined_in_kos(POLL_OUT, __POLL_OUT)]
%[assume_defined_in_kos(POLL_MSG, __POLL_MSG)]
%[assume_defined_in_kos(POLL_ERR, __POLL_ERR)]
%[assume_defined_in_kos(POLL_PRI, __POLL_PRI)]
%[assume_defined_in_kos(POLL_HUP, __POLL_HUP)]
%[assume_defined_in_kos(SS_ONSTACK, __SS_ONSTACK)]
%[assume_defined_in_kos(SS_DISABLE, __SS_DISABLE)]
%[assume_defined_in_kos(SS_AUTODISARM, __SS_AUTODISARM)]
%[assume_defined_in_kos(MINSIGSTKSZ, __MINSIGSTKSZ)]
%[assume_defined_in_kos(SIGSTKSZ, __SIGSTKSZ)]

%(auto_header){
#include <pthread.h>
}

%(auto_source){
#include "../libc/globals.h"
}

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <asm/os/signal.h>
)]%[insert:prefix(
#include <bits/os/sigset.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <libc/errno.h>
)]%{

#ifdef __USE_POSIX199309
#include <bits/os/timespec.h>
#endif /* __USE_POSIX199309 */

#ifdef __USE_MISC
#include <bits/os/sigcontext.h>
#endif /* __USE_MISC */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
#include <asm/os/sigstack.h>
#include <bits/os/sigstack.h> /* `struct sigstack', `struct sigaltstack' */
#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#include <sys/ucontext.h>
#endif /* __USE_XOPEN || __USE_XOPEN2K8 */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

#if defined(__USE_POSIX199506) || defined(__USE_UNIX98)
#include <bits/crt/pthreadtypes.h>
#include <bits/os/sigval.h> /* union sigval */
#endif /* __USE_POSIX199506 || __USE_UNIX98 */

#ifdef __USE_POSIX
#include <bits/os/sigaction.h>
#endif /* __USE_POSIX */

#if defined(__USE_KOS) && defined(__KOS__)
#include <kos/bits/userprocmask.h>
#endif /* __USE_KOS && __KOS__ */

#if (defined(__USE_POSIX199309) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_KOS))
#include <asm/os/sigevent.h>
#include <asm/os/siginfo.h>
#include <bits/os/sigevent.h> /* struct sigevent */
#include <bits/os/siginfo.h>  /* struct __siginfo_struct */
#include <bits/os/sigval.h>   /* union sigval */
#endif /* __USE_POSIX199309 || __USE_XOPEN_EXTENDED || __USE_KOS */

__SYSDECL_BEGIN

/* Fake signal functions. */
#if !defined(SIG_ERR) && defined(__SIG_ERR)
#define SIG_ERR (__CCAST(__sighandler_t)__SIG_ERR) /* Error return. */
#endif /* !SIG_ERR && __SIG_ERR */
#if !defined(SIG_DFL) && defined(__SIG_DFL)
#define SIG_DFL (__CCAST(__sighandler_t)__SIG_DFL) /* Default action. */
#endif /* !SIG_DFL && __SIG_DFL */
#if !defined(SIG_IGN) && defined(__SIG_IGN)
#define SIG_IGN (__CCAST(__sighandler_t)__SIG_IGN) /* Ignore signal. */
#endif /* !SIG_IGN && __SIG_IGN */

#ifdef __USE_DOS
#if !defined(SIG_GET) && defined(__SIG_GET)
#define SIG_GET (__CCAST(__sighandler_t)__SIG_GET) /* Only get the current handler (accepted by `signal(2)') */
#endif /* !SIG_GET && __SIG_GET */
#if !defined(SIG_SGE) && defined(__SIG_SGE)
#define SIG_SGE (__CCAST(__sighandler_t)__SIG_SGE) /* Signal gets error. */
#endif /* !SIG_SGE && __SIG_SGE */
#if !defined(SIG_ACK) && defined(__SIG_ACK)
#define SIG_ACK (__CCAST(__sighandler_t)__SIG_ACK) /* Acknowledge. */
#endif /* !SIG_ACK && __SIG_ACK */
#endif /* __USE_DOS */

#ifdef __USE_UNIX98
#if !defined(SIG_HOLD) && defined(__SIG_HOLD)
#define SIG_HOLD (__CCAST(__sighandler_t)__SIG_HOLD) /* Add signal to hold mask. */
#endif /* !SIG_HOLD && __SIG_HOLD */
#endif /* __USE_UNIX98 */

#ifdef __USE_KOS
#if !defined(SIG_TERM) && defined(__SIG_TERM)
#define SIG_TERM (__CCAST(__sighandler_t)__SIG_TERM) /* Terminate the receiving process. */
#endif /* !SIG_TERM && __SIG_TERM */
#if !defined(SIG_EXIT) && defined(__SIG_EXIT)
#define SIG_EXIT (__CCAST(__sighandler_t)__SIG_EXIT) /* Terminate the receiving thread. */
#endif /* !SIG_EXIT && __SIG_EXIT */
#if !defined(SIG_CONT) && defined(__SIG_CONT)
#define SIG_CONT (__CCAST(__sighandler_t)__SIG_CONT) /* Continue execution. */
#endif /* !SIG_CONT && __SIG_CONT */
#if !defined(SIG_STOP) && defined(__SIG_STOP)
#define SIG_STOP (__CCAST(__sighandler_t)__SIG_STOP) /* Suspend execution. */
#endif /* !SIG_STOP && __SIG_STOP */
#if !defined(SIG_CORE) && defined(__SIG_CORE)
#define SIG_CORE (__CCAST(__sighandler_t)__SIG_CORE) /* Create a coredump and terminate. */
#endif /* !SIG_CORE && __SIG_CORE */
#if !defined(SIG_GET) && defined(__SIG_GET)
#define SIG_GET  (__CCAST(__sighandler_t)__SIG_GET)  /* Only get the current handler (accepted by `signal(2)') */
#endif /* !SIG_GET && __SIG_GET */
#endif /* __USE_KOS */


/* Signals numbers. */
#if !defined(SIGHUP) && defined(__SIGHUP)
#define SIGHUP    __SIGHUP     /* Hangup (POSIX). */
#endif /* !SIGHUP && __SIGHUP */
#if !defined(SIGINT) && defined(__SIGINT)
#define SIGINT    __SIGINT     /* Interrupt (ANSI). */
#endif /* !SIGINT && __SIGINT */
#if !defined(SIGQUIT) && defined(__SIGQUIT)
#define SIGQUIT   __SIGQUIT    /* Quit (POSIX). */
#endif /* !SIGQUIT && __SIGQUIT */
#if !defined(SIGILL) && defined(__SIGILL)
#define SIGILL    __SIGILL     /* Illegal instruction (ANSI). */
#endif /* !SIGILL && __SIGILL */
#if !defined(SIGTRAP) && defined(__SIGTRAP)
#define SIGTRAP   __SIGTRAP    /* Trace trap (POSIX). */
#endif /* !SIGTRAP && __SIGTRAP */
#if !defined(SIGABRT) && defined(__SIGABRT)
#define SIGABRT   __SIGABRT    /* Abort (ANSI). */
#endif /* !SIGABRT && __SIGABRT */
#if !defined(SIGIOT) && defined(__SIGIOT)
#define SIGIOT    __SIGIOT     /* IOT trap (4.2 BSD). */
#endif /* !SIGIOT && __SIGIOT */
#if !defined(SIGBUS) && defined(__SIGBUS)
#define SIGBUS    __SIGBUS     /* BUS error (4.2 BSD). */
#endif /* !SIGBUS && __SIGBUS */
#if !defined(SIGFPE) && defined(__SIGFPE)
#define SIGFPE    __SIGFPE     /* Floating-point exception (ANSI). */
#endif /* !SIGFPE && __SIGFPE */
#if !defined(SIGKILL) && defined(__SIGKILL)
#define SIGKILL   __SIGKILL    /* Kill, unblockable (POSIX). */
#endif /* !SIGKILL && __SIGKILL */
#if !defined(SIGUSR1) && defined(__SIGUSR1)
#define SIGUSR1   __SIGUSR1    /* User-defined signal 1 (POSIX). */
#endif /* !SIGUSR1 && __SIGUSR1 */
#if !defined(SIGSEGV) && defined(__SIGSEGV)
#define SIGSEGV   __SIGSEGV    /* Segmentation violation (ANSI). */
#endif /* !SIGSEGV && __SIGSEGV */
#if !defined(SIGUSR2) && defined(__SIGUSR2)
#define SIGUSR2   __SIGUSR2    /* User-defined signal 2 (POSIX). */
#endif /* !SIGUSR2 && __SIGUSR2 */
#if !defined(SIGPIPE) && defined(__SIGPIPE)
#define SIGPIPE   __SIGPIPE    /* Broken pipe (POSIX). */
#endif /* !SIGPIPE && __SIGPIPE */
#if !defined(SIGALRM) && defined(__SIGALRM)
#define SIGALRM   __SIGALRM    /* Alarm clock (POSIX). */
#endif /* !SIGALRM && __SIGALRM */
#if !defined(SIGTERM) && defined(__SIGTERM)
#define SIGTERM   __SIGTERM    /* Termination (ANSI). */
#endif /* !SIGTERM && __SIGTERM */
#if !defined(SIGSTKFLT) && defined(__SIGSTKFLT)
#define SIGSTKFLT __SIGSTKFLT  /* Stack fault. */
#endif /* !SIGSTKFLT && __SIGSTKFLT */
#if !defined(SIGCHLD) && defined(__SIGCHLD)
#define SIGCHLD   __SIGCHLD    /* Child status has changed (POSIX). */
#endif /* !SIGCHLD && __SIGCHLD */
#if !defined(SIGCONT) && defined(__SIGCONT)
#define SIGCONT   __SIGCONT    /* Continue (POSIX). */
#endif /* !SIGCONT && __SIGCONT */
#if !defined(SIGSTOP) && defined(__SIGSTOP)
#define SIGSTOP   __SIGSTOP    /* Stop, unblockable (POSIX). */
#endif /* !SIGSTOP && __SIGSTOP */
#if !defined(SIGTSTP) && defined(__SIGTSTP)
#define SIGTSTP   __SIGTSTP    /* Keyboard stop (POSIX). */
#endif /* !SIGTSTP && __SIGTSTP */
#if !defined(SIGTTIN) && defined(__SIGTTIN)
#define SIGTTIN   __SIGTTIN    /* Background read from tty (POSIX). */
#endif /* !SIGTTIN && __SIGTTIN */
#if !defined(SIGTTOU) && defined(__SIGTTOU)
#define SIGTTOU   __SIGTTOU    /* Background write to tty (POSIX). */
#endif /* !SIGTTOU && __SIGTTOU */
#if !defined(SIGURG) && defined(__SIGURG)
#define SIGURG    __SIGURG     /* Urgent condition on socket (4.2 BSD). */
#endif /* !SIGURG && __SIGURG */
#if !defined(SIGXCPU) && defined(__SIGXCPU)
#define SIGXCPU   __SIGXCPU    /* CPU limit exceeded (4.2 BSD). */
#endif /* !SIGXCPU && __SIGXCPU */
#if !defined(SIGXFSZ) && defined(__SIGXFSZ)
#define SIGXFSZ   __SIGXFSZ    /* File size limit exceeded (4.2 BSD). */
#endif /* !SIGXFSZ && __SIGXFSZ */
#if !defined(SIGVTALRM) && defined(__SIGVTALRM)
#define SIGVTALRM __SIGVTALRM  /* Virtual alarm clock (4.2 BSD). */
#endif /* !SIGVTALRM && __SIGVTALRM */
#if !defined(SIGPROF) && defined(__SIGPROF)
#define SIGPROF   __SIGPROF    /* Profiling alarm clock (4.2 BSD). */
#endif /* !SIGPROF && __SIGPROF */
#if !defined(SIGWINCH) && defined(__SIGWINCH)
#define SIGWINCH  __SIGWINCH   /* Window size change (4.3 BSD, Sun). */
#endif /* !SIGWINCH && __SIGWINCH */
#if !defined(SIGIO) && defined(__SIGIO)
#define SIGIO     __SIGIO      /* I/O now possible (4.2 BSD). */
#endif /* !SIGIO && __SIGIO */
#if !defined(SIGPOLL) && defined(__SIGPOLL)
#define SIGPOLL   __SIGPOLL    /* Pollable event occurred (System V). */
#endif /* !SIGPOLL && __SIGPOLL */
#if !defined(SIGPWR) && defined(__SIGPWR)
#define SIGPWR    __SIGPWR     /* Power failure restart (System V). */
#endif /* !SIGPWR && __SIGPWR */
#if !defined(SIGSYS) && defined(__SIGSYS)
#define SIGSYS    __SIGSYS     /* Bad system call. */
#endif /* !SIGSYS && __SIGSYS */
#if !defined(SIGCLD) && defined(__SIGCHLD)
#define SIGCLD    __SIGCHLD    /* Same as SIGCHLD (System V). */
#endif /* !SIGCLD && __SIGCHLD */
#if defined(__USE_KOS) && !defined(SIGRPC) && defined(__SIGRPC)
#define SIGRPC    __SIGRPC     /* Default signal number used for <kos/rpc.h> */
#endif /* __USE_KOS && !SIGRPC && __SIGRPC */
#ifndef SIGUNUSED
#ifdef __SIGUNUSED
#define SIGUNUSED __SIGUNUSED
#elif defined(__SIGSYS)
#define SIGUNUSED __SIGSYS
#endif /* ... */
#endif /* !SIGUNUSED */

#if !defined(_NSIG) && defined(__NSIG)
#define _NSIG __NSIG /* Biggest signal number + 1 (including real-time signals). */
#endif /* !_NSIG && __NSIG */

/* These are the hard limits of the kernel.
 * These values should not be used directly at user level. */
#ifndef SIGRTMIN
#if defined(__SIGRTMIN) && (!defined(__CRT_HAVE___libc_current_sigrtmin) || !defined(__CC__))
#define SIGRTMIN __SIGRTMIN
#else /* __SIGRTMIN && (!__CRT_HAVE___libc_current_sigrtmin || !__CC__) */
#define SIGRTMIN __libc_current_sigrtmin()
#endif /* !__SIGRTMIN || (__CRT_HAVE___libc_current_sigrtmin && __CC__) */
#endif /* !SIGRTMIN */
#ifndef SIGRTMAX
#if defined(__SIGRTMAX) && (!defined(__CRT_HAVE___libc_current_sigrtmax) || !defined(__CC__))
#define SIGRTMAX __SIGRTMAX
#else /* __SIGRTMAX && (!__CRT_HAVE___libc_current_sigrtmax || !__CC__) */
#define SIGRTMAX __libc_current_sigrtmax()
#endif /* !__SIGRTMAX || (__CRT_HAVE___libc_current_sigrtmax && __CC__) */
#endif /* !SIGRTMAX */

#ifdef __USE_DOS
/* Define DOS's signal name aliases. */
#if !defined(SIGBREAK) && defined(__SIGBREAK)
#define SIGBREAK __SIGBREAK /* Background read from tty (POSIX). */
#endif /* !SIGBREAK && __SIGBREAK */
#ifndef SIGABRT_COMPAT
#ifdef __SIGABRT_COMPAT
#define SIGABRT_COMPAT __SIGABRT_COMPAT /* Abort (ANSI). */
#elif defined(__SIGABRT)
#define SIGABRT_COMPAT __SIGABRT        /* Abort (ANSI). */
#endif /* ... */
#endif /* !SIGABRT_COMPAT */
#endif /* __USE_DOS */




#ifdef __USE_POSIX
/* Bits in `sa_flags'. */
#if !defined(SA_NOCLDSTOP) && defined(__SA_NOCLDSTOP)
#define SA_NOCLDSTOP __SA_NOCLDSTOP /* Don't send SIGCHLD when children stop (Ignored for anything other than SIGCLD). */
#endif /* !SA_NOCLDSTOP && __SA_NOCLDSTOP */
#if !defined(SA_NOCLDWAIT) && defined(__SA_NOCLDWAIT)
#define SA_NOCLDWAIT __SA_NOCLDWAIT /* Don't create zombie on child death (Ignored for anything other than SIGCLD). */
#endif /* !SA_NOCLDWAIT && __SA_NOCLDWAIT */
#if !defined(SA_SIGINFO) && defined(__SA_SIGINFO)
#define SA_SIGINFO __SA_SIGINFO /* Invoke signal-catching function with three arguments instead of one. */
#endif /* !SA_SIGINFO && __SA_SIGINFO */

#ifdef __USE_KOS_KERNEL
#if !defined(SA_RESTORER) && defined(__SA_RESTORER)
#define SA_RESTORER __SA_RESTORER /* A custom  signal restore  function (`sa_restorer')  was given.  This
                                   * flag is set by libc, after having filled in the `sa_restorer' field. */
#endif /* !SA_RESTORER && __SA_RESTORER */
#endif /* __USE_KOS_KERNEL */

#if defined(__USE_UNIX98) || defined(__USE_MISC)
#if !defined(SA_ONSTACK) && defined(__SA_ONSTACK)
#define SA_ONSTACK __SA_ONSTACK /* Execute the handler on sigaltstack. */
#endif /* !SA_ONSTACK && __SA_ONSTACK */
#endif /* __USE_UNIX98 || __USE_MISC */

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
#if !defined(SA_RESTART) && defined(__SA_RESTART)
#define SA_RESTART __SA_RESTART /* Restart restartable syscall on signal return. */
#endif /* !SA_RESTART && __SA_RESTART */
#if !defined(SA_NODEFER) && defined(__SA_NODEFER)
#define SA_NODEFER __SA_NODEFER /* Don't automatically block the signal when its handler is being executed. */
#endif /* !SA_NODEFER && __SA_NODEFER */
#if !defined(SA_RESETHAND) && defined(__SA_RESETHAND)
#define SA_RESETHAND __SA_RESETHAND /* Reset to SIG_DFL on entry to handler. */
#endif /* !SA_RESETHAND && __SA_RESETHAND */
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */

#ifdef __USE_MISC
#if !defined(SA_INTERRUPT) && defined(__SA_INTERRUPT)
#define SA_INTERRUPT __SA_INTERRUPT /* Historical no-op. */
#endif /* !SA_INTERRUPT && __SA_INTERRUPT */
/* Some aliases for the SA_ constants. */
#if !defined(SA_NOMASK) && defined(__SA_NODEFER)
#define SA_NOMASK __SA_NODEFER
#endif /* !SA_NOMASK && __SA_NODEFER */
#if !defined(SA_ONESHOT) && defined(__SA_RESETHAND)
#define SA_ONESHOT __SA_RESETHAND
#endif /* !SA_ONESHOT && __SA_RESETHAND */
#if !defined(SA_STACK) && defined(__SA_ONSTACK)
#define SA_STACK __SA_ONSTACK
#endif /* !SA_STACK && __SA_ONSTACK */
#endif /* __USE_MISC */

/* Values for the HOW argument to `sigprocmask'. */
#if !defined(SIG_BLOCK) && defined(__SIG_BLOCK)
#define SIG_BLOCK __SIG_BLOCK /* Block signals. */
#endif /* !SIG_BLOCK && __SIG_BLOCK */
#if !defined(SIG_UNBLOCK) && defined(__SIG_UNBLOCK)
#define SIG_UNBLOCK __SIG_UNBLOCK /* Unblock signals. */
#endif /* !SIG_UNBLOCK && __SIG_UNBLOCK */
#if !defined(SIG_SETMASK) && defined(__SIG_SETMASK)
#define SIG_SETMASK __SIG_SETMASK /* Set the set of blocked signals. */
#endif /* !SIG_SETMASK && __SIG_SETMASK */
#endif /* __USE_POSIX */

#if (defined(__USE_POSIX199309) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_KOS))

/* `sigev_notify' values. */
#if (defined(__SIGEV_SIGNAL) || defined(__SIGEV_NONE) ||      \
     defined(__SIGEV_THREAD) || defined(__SIGEV_THREAD_ID) || \
     defined(__SIGEV_INLINE_THREAD))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __SIGEV_SIGNAL
	SIGEV_SIGNAL    = __SIGEV_SIGNAL, /* Notify via signal. */
#endif /* __SIGEV_SIGNAL */
#ifdef __SIGEV_NONE
	SIGEV_NONE      = __SIGEV_NONE, /* Other notification: meaningless. */
#endif /* __SIGEV_NONE */
#ifdef __SIGEV_THREAD
	SIGEV_THREAD    = __SIGEV_THREAD, /* Deliver via thread creation. */
#endif /* __SIGEV_THREAD */
#ifdef __SIGEV_THREAD_ID
	SIGEV_THREAD_ID = __SIGEV_THREAD_ID, /* Send signal to specific thread. */
#endif /* __SIGEV_THREAD_ID */
#ifdef __SIGEV_INLINE_THREAD
	SIGEV_INLINE_THREAD = __SIGEV_INLINE_THREAD, /* KOS-only: Same as `SIGEV_THREAD', but try not to actually spawn a thread, though
	                                              * this event kind  is allowed to  be implemented as  an alias for  `SIGEV_THREAD'.
	                                              * Semantically, the following rules have to be followed by  `SIGEV_INLINE_THREAD':
	                                              *   - You mustn't call `pthread_exit(3)'
	                                              * In the context of AIO completion events (s.a. <aio.h>), the following applies:
	                                              *   - If triggered as a result of `aio_cancel(3)', the call to `aio_cancel()' may
	                                              *     not return until your callback has also returned (because your callback may
	                                              *     have hi-jacked that thread)
	                                              * NOTE: You are allowed to make modifications to `errno', so don't worry about it.
	                                              * NOTE: Depending on context, this may be identical to `SIGEV_THREAD'!
	                                              *
	                                              * Generally speaking,  you should  act like  your callback  is invoked  as though  it
	                                              * were a signal handler (note that it may actually be invoked from a signal handler),
	                                              * meaning that you should only call NOBLOCK and re-entrance-safe functions. */
#endif /* __SIGEV_INLINE_THREAD */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __SIGEV_SIGNAL
#define SIGEV_SIGNAL        SIGEV_SIGNAL        /* Notify via signal. */
#endif /* __SIGEV_SIGNAL */
#ifdef __SIGEV_NONE
#define SIGEV_NONE          SIGEV_NONE          /* Other notification: meaningless. */
#endif /* __SIGEV_NONE */
#ifdef __SIGEV_THREAD
#define SIGEV_THREAD        SIGEV_THREAD        /* Deliver via thread creation. */
#endif /* __SIGEV_THREAD */
#ifdef __SIGEV_THREAD_ID
#define SIGEV_THREAD_ID     SIGEV_THREAD_ID     /* Send signal to specific thread. */
#endif /* __SIGEV_THREAD_ID */
#ifdef __SIGEV_INLINE_THREAD
#define SIGEV_INLINE_THREAD SIGEV_INLINE_THREAD /* KOS-only: Same as `SIGEV_THREAD', but try not to actually spawn a thread, though
                                                 * this event kind  is allowed to  be implemented as  an alias for  `SIGEV_THREAD'.
                                                 * Semantically, the following rules have to be followed by  `SIGEV_INLINE_THREAD':
                                                 *   - You mustn't call `pthread_exit(3)'
                                                 * In the context of AIO completion events (s.a. <aio.h>), the following applies:
                                                 *   - If triggered as a result of `aio_cancel(3)', the call to `aio_cancel()' may
                                                 *     not return until your callback has also returned (because your callback may
                                                 *     have hi-jacked that thread)
                                                 * NOTE: You are allowed to make modifications to `errno', so don't worry about it.
                                                 * NOTE: Depending on context, this may be identical to `SIGEV_THREAD'!
                                                 *
                                                 * Generally speaking,  you should  act like  your callback  is invoked  as though  it
                                                 * were a signal handler (note that it may actually be invoked from a signal handler),
                                                 * meaning that you should only call NOBLOCK and re-entrance-safe functions. */
#endif /* __SIGEV_INLINE_THREAD */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __SIGEV_SIGNAL
#define SIGEV_SIGNAL        __SIGEV_SIGNAL        /* Notify via signal. */
#endif /* __SIGEV_SIGNAL */
#ifdef __SIGEV_NONE
#define SIGEV_NONE          __SIGEV_NONE          /* Other notification: meaningless. */
#endif /* __SIGEV_NONE */
#ifdef __SIGEV_THREAD
#define SIGEV_THREAD        __SIGEV_THREAD        /* Deliver via thread creation. */
#endif /* __SIGEV_THREAD */
#ifdef __SIGEV_THREAD_ID
#define SIGEV_THREAD_ID     __SIGEV_THREAD_ID     /* Send signal to specific thread. */
#endif /* __SIGEV_THREAD_ID */
#ifdef __SIGEV_INLINE_THREAD
#define SIGEV_INLINE_THREAD __SIGEV_INLINE_THREAD /* KOS-only: Same as `SIGEV_THREAD', but try not to actually spawn a thread, though
                                                   * this event kind  is allowed to  be implemented as  an alias for  `SIGEV_THREAD'.
                                                   * Semantically, the following rules have to be followed by  `SIGEV_INLINE_THREAD':
                                                   *   - You mustn't call `pthread_exit(3)'
                                                   * In the context of AIO completion events (s.a. <aio.h>), the following applies:
                                                   *   - If triggered as a result of `aio_cancel(3)', the call to `aio_cancel()' may
                                                   *     not return until your callback has also returned (because your callback may
                                                   *     have hi-jacked that thread)
                                                   * NOTE: You are allowed to make modifications to `errno', so don't worry about it.
                                                   * NOTE: Depending on context, this may be identical to `SIGEV_THREAD'!
                                                   *
                                                   * Generally speaking,  you should  act like  your callback  is invoked  as though  it
                                                   * were a signal handler (note that it may actually be invoked from a signal handler),
                                                   * meaning that you should only call NOBLOCK and re-entrance-safe functions. */
#endif /* __SIGEV_INLINE_THREAD */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __SIGEV_SIGNAL || __SIGEV_NONE || __SIGEV_THREAD || __SIGEV_THREAD_ID */


/* Values for `si_code'. Positive values are reserved for kernel-generated signals. */
#if (defined(__SI_ASYNCNL) || defined(__SI_TKILL) || defined(__SI_SIGIO) || \
     defined(__SI_ASYNCIO) || defined(__SI_MESGQ) || defined(__SI_TIMER) || \
     defined(__SI_QUEUE) || defined(__SI_USER) || defined(__SI_KERNEL))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __SI_ASYNCNL
	SI_ASYNCNL = __SI_ASYNCNL, /* Sent by asynch name lookup completion. */
#endif /* __SI_ASYNCNL */
#ifdef __SI_TKILL
	SI_TKILL = __SI_TKILL,     /* Sent by tkill. */
#endif /* __SI_TKILL */
#ifdef __SI_SIGIO
	SI_SIGIO = __SI_SIGIO,     /* Sent by queued SIGIO. */
#endif /* __SI_SIGIO */
#ifdef __SI_ASYNCIO
	SI_ASYNCIO = __SI_ASYNCIO, /* Sent by AIO completion. */
#endif /* __SI_ASYNCIO */
#ifdef __SI_MESGQ
	SI_MESGQ = __SI_MESGQ,     /* Sent by real time mesq state change. */
#endif /* __SI_MESGQ */
#ifdef __SI_TIMER
	SI_TIMER = __SI_TIMER,     /* Sent by timer expiration. */
#endif /* __SI_TIMER */
#ifdef __SI_QUEUE
	SI_QUEUE = __SI_QUEUE,     /* Sent by sigqueue. */
#endif /* __SI_QUEUE */
#ifdef __SI_USER
	SI_USER = __SI_USER,       /* Sent by kill, sigsend. */
#endif /* __SI_USER */
#ifdef __SI_KERNEL
	SI_KERNEL = __SI_KERNEL,   /* Send by kernel. */
#endif /* __SI_KERNEL */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __SI_ASYNCNL
#define SI_ASYNCNL SI_ASYNCNL /* Sent by asynch name lookup completion. */
#endif /* __SI_ASYNCNL */
#ifdef __SI_TKILL
#define SI_TKILL   SI_TKILL   /* Sent by tkill. */
#endif /* __SI_TKILL */
#ifdef __SI_SIGIO
#define SI_SIGIO   SI_SIGIO   /* Sent by queued SIGIO. */
#endif /* __SI_SIGIO */
#ifdef __SI_ASYNCIO
#define SI_ASYNCIO SI_ASYNCIO /* Sent by AIO completion. */
#endif /* __SI_ASYNCIO */
#ifdef __SI_MESGQ
#define SI_MESGQ   SI_MESGQ   /* Sent by real time mesq state change. */
#endif /* __SI_MESGQ */
#ifdef __SI_TIMER
#define SI_TIMER   SI_TIMER   /* Sent by timer expiration. */
#endif /* __SI_TIMER */
#ifdef __SI_QUEUE
#define SI_QUEUE   SI_QUEUE   /* Sent by sigqueue. */
#endif /* __SI_QUEUE */
#ifdef __SI_USER
#define SI_USER    SI_USER    /* Sent by kill, sigsend. */
#endif /* __SI_USER */
#ifdef __SI_KERNEL
#define SI_KERNEL  SI_KERNEL  /* Send by kernel. */
#endif /* __SI_KERNEL */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __SI_ASYNCNL
#define SI_ASYNCNL __SI_ASYNCNL /* Sent by asynch name lookup completion. */
#endif /* __SI_ASYNCNL */
#ifdef __SI_TKILL
#define SI_TKILL   __SI_TKILL   /* Sent by tkill. */
#endif /* __SI_TKILL */
#ifdef __SI_SIGIO
#define SI_SIGIO   __SI_SIGIO   /* Sent by queued SIGIO. */
#endif /* __SI_SIGIO */
#ifdef __SI_ASYNCIO
#define SI_ASYNCIO __SI_ASYNCIO /* Sent by AIO completion. */
#endif /* __SI_ASYNCIO */
#ifdef __SI_MESGQ
#define SI_MESGQ   __SI_MESGQ   /* Sent by real time mesq state change. */
#endif /* __SI_MESGQ */
#ifdef __SI_TIMER
#define SI_TIMER   __SI_TIMER   /* Sent by timer expiration. */
#endif /* __SI_TIMER */
#ifdef __SI_QUEUE
#define SI_QUEUE   __SI_QUEUE   /* Sent by sigqueue. */
#endif /* __SI_QUEUE */
#ifdef __SI_USER
#define SI_USER    __SI_USER    /* Sent by kill, sigsend. */
#endif /* __SI_USER */
#ifdef __SI_KERNEL
#define SI_KERNEL  __SI_KERNEL  /* Send by kernel. */
#endif /* __SI_KERNEL */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __SI_... */



#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)

/* `si_code' values for SIGILL signal. */
#if (defined(__ILL_ILLOPC) || defined(__ILL_ILLOPN) || defined(__ILL_ILLADR) || \
     defined(__ILL_ILLTRP) || defined(__ILL_PRVOPC) || defined(__ILL_PRVREG) || \
     defined(__ILL_COPROC) || defined(__ILL_BADSTK))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __ILL_ILLOPC
	ILL_ILLOPC = __ILL_ILLOPC, /* Illegal opcode. */
#endif /* __ILL_ILLOPC */
#ifdef __ILL_ILLOPN
	ILL_ILLOPN = __ILL_ILLOPN, /* Illegal operand. */
#endif /* __ILL_ILLOPN */
#ifdef __ILL_ILLADR
	ILL_ILLADR = __ILL_ILLADR, /* Illegal addressing mode. */
#endif /* __ILL_ILLADR */
#ifdef __ILL_ILLTRP
	ILL_ILLTRP = __ILL_ILLTRP, /* Illegal trap. */
#endif /* __ILL_ILLTRP */
#ifdef __ILL_PRVOPC
	ILL_PRVOPC = __ILL_PRVOPC, /* Privileged opcode. */
#endif /* __ILL_PRVOPC */
#ifdef __ILL_PRVREG
	ILL_PRVREG = __ILL_PRVREG, /* Privileged register. */
#endif /* __ILL_PRVREG */
#ifdef __ILL_COPROC
	ILL_COPROC = __ILL_COPROC, /* Coprocessor error. */
#endif /* __ILL_COPROC */
#ifdef __ILL_BADSTK
	ILL_BADSTK = __ILL_BADSTK  /* Internal stack error. */
#endif /* __ILL_BADSTK */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __ILL_ILLOPC
#define ILL_ILLOPC ILL_ILLOPC /* Illegal opcode. */
#endif /* __ILL_ILLOPC */
#ifdef __ILL_ILLOPN
#define ILL_ILLOPN ILL_ILLOPN /* Illegal operand. */
#endif /* __ILL_ILLOPN */
#ifdef __ILL_ILLADR
#define ILL_ILLADR ILL_ILLADR /* Illegal addressing mode. */
#endif /* __ILL_ILLADR */
#ifdef __ILL_ILLTRP
#define ILL_ILLTRP ILL_ILLTRP /* Illegal trap. */
#endif /* __ILL_ILLTRP */
#ifdef __ILL_PRVOPC
#define ILL_PRVOPC ILL_PRVOPC /* Privileged opcode. */
#endif /* __ILL_PRVOPC */
#ifdef __ILL_PRVREG
#define ILL_PRVREG ILL_PRVREG /* Privileged register. */
#endif /* __ILL_PRVREG */
#ifdef __ILL_COPROC
#define ILL_COPROC ILL_COPROC /* Coprocessor error. */
#endif /* __ILL_COPROC */
#ifdef __ILL_BADSTK
#define ILL_BADSTK ILL_BADSTK /* Internal stack error. */
#endif /* __ILL_BADSTK */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __ILL_ILLOPC
#define ILL_ILLOPC __ILL_ILLOPC /* Illegal opcode. */
#endif /* __ILL_ILLOPC */
#ifdef __ILL_ILLOPN
#define ILL_ILLOPN __ILL_ILLOPN /* Illegal operand. */
#endif /* __ILL_ILLOPN */
#ifdef __ILL_ILLADR
#define ILL_ILLADR __ILL_ILLADR /* Illegal addressing mode. */
#endif /* __ILL_ILLADR */
#ifdef __ILL_ILLTRP
#define ILL_ILLTRP __ILL_ILLTRP /* Illegal trap. */
#endif /* __ILL_ILLTRP */
#ifdef __ILL_PRVOPC
#define ILL_PRVOPC __ILL_PRVOPC /* Privileged opcode. */
#endif /* __ILL_PRVOPC */
#ifdef __ILL_PRVREG
#define ILL_PRVREG __ILL_PRVREG /* Privileged register. */
#endif /* __ILL_PRVREG */
#ifdef __ILL_COPROC
#define ILL_COPROC __ILL_COPROC /* Coprocessor error. */
#endif /* __ILL_COPROC */
#ifdef __ILL_BADSTK
#define ILL_BADSTK __ILL_BADSTK /* Internal stack error. */
#endif /* __ILL_BADSTK */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __ILL_... */



/* `si_code' values for SIGFPE signal. */
#if (defined(__FPE_INTDIV) || defined(__FPE_INTOVF) || defined(__FPE_FLTDIV) || \
     defined(__FPE_FLTOVF) || defined(__FPE_FLTUND) || defined(__FPE_FLTRES) || \
     defined(__FPE_FLTINV) || defined(__FPE_FLTSUB))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __FPE_INTDIV
	FPE_INTDIV = __FPE_INTDIV, /* Integer divide by zero. */
#endif /* __FPE_INTDIV */
#ifdef __FPE_INTOVF
	FPE_INTOVF = __FPE_INTOVF, /* Integer overflow. */
#endif /* __FPE_INTOVF */
#ifdef __FPE_FLTDIV
	FPE_FLTDIV = __FPE_FLTDIV, /* Floating point divide by zero. */
#endif /* __FPE_FLTDIV */
#ifdef __FPE_FLTOVF
	FPE_FLTOVF = __FPE_FLTOVF, /* Floating point overflow. */
#endif /* __FPE_FLTOVF */
#ifdef __FPE_FLTUND
	FPE_FLTUND = __FPE_FLTUND, /* Floating point underflow. */
#endif /* __FPE_FLTUND */
#ifdef __FPE_FLTRES
	FPE_FLTRES = __FPE_FLTRES, /* Floating point inexact result. */
#endif /* __FPE_FLTRES */
#ifdef __FPE_FLTINV
	FPE_FLTINV = __FPE_FLTINV, /* Floating point invalid operation. */
#endif /* __FPE_FLTINV */
#ifdef __FPE_FLTSUB
	FPE_FLTSUB = __FPE_FLTSUB  /* Subscript out of range. */
#endif /* __FPE_FLTSUB */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __FPE_INTDIV
#define FPE_INTDIV FPE_INTDIV /* Integer divide by zero. */
#endif /* __FPE_INTDIV */
#ifdef __FPE_INTOVF
#define FPE_INTOVF FPE_INTOVF /* Integer overflow. */
#endif /* __FPE_INTOVF */
#ifdef __FPE_FLTDIV
#define FPE_FLTDIV FPE_FLTDIV /* Floating point divide by zero. */
#endif /* __FPE_FLTDIV */
#ifdef __FPE_FLTOVF
#define FPE_FLTOVF FPE_FLTOVF /* Floating point overflow. */
#endif /* __FPE_FLTOVF */
#ifdef __FPE_FLTUND
#define FPE_FLTUND FPE_FLTUND /* Floating point underflow. */
#endif /* __FPE_FLTUND */
#ifdef __FPE_FLTRES
#define FPE_FLTRES FPE_FLTRES /* Floating point inexact result. */
#endif /* __FPE_FLTRES */
#ifdef __FPE_FLTINV
#define FPE_FLTINV FPE_FLTINV /* Floating point invalid operation. */
#endif /* __FPE_FLTINV */
#ifdef __FPE_FLTSUB
#define FPE_FLTSUB FPE_FLTSUB /* Subscript out of range. */
#endif /* __FPE_FLTSUB */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __FPE_INTDIV
#define FPE_INTDIV __FPE_INTDIV /* Integer divide by zero. */
#endif /* __FPE_INTDIV */
#ifdef __FPE_INTOVF
#define FPE_INTOVF __FPE_INTOVF /* Integer overflow. */
#endif /* __FPE_INTOVF */
#ifdef __FPE_FLTDIV
#define FPE_FLTDIV __FPE_FLTDIV /* Floating point divide by zero. */
#endif /* __FPE_FLTDIV */
#ifdef __FPE_FLTOVF
#define FPE_FLTOVF __FPE_FLTOVF /* Floating point overflow. */
#endif /* __FPE_FLTOVF */
#ifdef __FPE_FLTUND
#define FPE_FLTUND __FPE_FLTUND /* Floating point underflow. */
#endif /* __FPE_FLTUND */
#ifdef __FPE_FLTRES
#define FPE_FLTRES __FPE_FLTRES /* Floating point inexact result. */
#endif /* __FPE_FLTRES */
#ifdef __FPE_FLTINV
#define FPE_FLTINV __FPE_FLTINV /* Floating point invalid operation. */
#endif /* __FPE_FLTINV */
#ifdef __FPE_FLTSUB
#define FPE_FLTSUB __FPE_FLTSUB /* Subscript out of range. */
#endif /* __FPE_FLTSUB */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __FPE_... */



/* `si_code' values for SIGSEGV signal. */
#if defined(__SEGV_MAPERR) || defined(__SEGV_ACCERR)
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __SEGV_MAPERR
	SEGV_MAPERR = __SEGV_MAPERR, /* Address not mapped to object. */
#endif /* __SEGV_MAPERR */
#ifdef __SEGV_ACCERR
	SEGV_ACCERR = __SEGV_ACCERR  /* Invalid permissions for mapped object. */
#endif /* __SEGV_ACCERR */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __SEGV_MAPERR
#define SEGV_MAPERR SEGV_MAPERR /* Address not mapped to object. */
#endif /* __SEGV_MAPERR */
#ifdef __SEGV_ACCERR
#define SEGV_ACCERR SEGV_ACCERR /* Invalid permissions for mapped object. */
#endif /* __SEGV_ACCERR */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __SEGV_MAPERR
#define SEGV_MAPERR __SEGV_MAPERR /* Address not mapped to object. */
#endif /* __SEGV_MAPERR */
#ifdef __SEGV_ACCERR
#define SEGV_ACCERR __SEGV_ACCERR /* Invalid permissions for mapped object. */
#endif /* __SEGV_ACCERR */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __SEGV_... */



/* `si_code' values for SIGBUS signal. */
#if (defined(__BUS_ADRALN) || defined(__BUS_ADRERR) ||    \
     defined(__BUS_OBJERR) || defined(__BUS_MCEERR_AR) || \
     defined(__BUS_MCEERR_AO))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __BUS_ADRALN
	BUS_ADRALN    = __BUS_ADRALN,    /* Invalid address alignment. */
#endif /* __BUS_ADRALN */
#ifdef __BUS_ADRERR
	BUS_ADRERR    = __BUS_ADRERR,    /* Non-existent physical address. */
#endif /* __BUS_ADRERR */
#ifdef __BUS_OBJERR
	BUS_OBJERR    = __BUS_OBJERR,    /* Object specific hardware error. */
#endif /* __BUS_OBJERR */
#ifdef __BUS_MCEERR_AR
	BUS_MCEERR_AR = __BUS_MCEERR_AR, /* Hardware memory error: action required. */
#endif /* __BUS_MCEERR_AR */
#ifdef __BUS_MCEERR_AO
	BUS_MCEERR_AO = __BUS_MCEERR_AO  /* Hardware memory error: action optional. */
#endif /* __BUS_MCEERR_AO */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __BUS_ADRALN
#define BUS_ADRALN    BUS_ADRALN    /* Invalid address alignment. */
#endif /* __BUS_ADRALN */
#ifdef __BUS_ADRERR
#define BUS_ADRERR    BUS_ADRERR    /* Non-existent physical address. */
#endif /* __BUS_ADRERR */
#ifdef __BUS_OBJERR
#define BUS_OBJERR    BUS_OBJERR    /* Object specific hardware error. */
#endif /* __BUS_OBJERR */
#ifdef __BUS_MCEERR_AR
#define BUS_MCEERR_AR BUS_MCEERR_AR /* Hardware memory error: action required. */
#endif /* __BUS_MCEERR_AR */
#ifdef __BUS_MCEERR_AO
#define BUS_MCEERR_AO BUS_MCEERR_AO /* Hardware memory error: action optional. */
#endif /* __BUS_MCEERR_AO */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __BUS_ADRALN
#define BUS_ADRALN    __BUS_ADRALN    /* Invalid address alignment. */
#endif /* __BUS_ADRALN */
#ifdef __BUS_ADRERR
#define BUS_ADRERR    __BUS_ADRERR    /* Non-existent physical address. */
#endif /* __BUS_ADRERR */
#ifdef __BUS_OBJERR
#define BUS_OBJERR    __BUS_OBJERR    /* Object specific hardware error. */
#endif /* __BUS_OBJERR */
#ifdef __BUS_MCEERR_AR
#define BUS_MCEERR_AR __BUS_MCEERR_AR /* Hardware memory error: action required. */
#endif /* __BUS_MCEERR_AR */
#ifdef __BUS_MCEERR_AO
#define BUS_MCEERR_AO __BUS_MCEERR_AO /* Hardware memory error: action optional. */
#endif /* __BUS_MCEERR_AO */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __BUS_... */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */



#ifdef __USE_XOPEN_EXTENDED
/* `si_code' values for SIGTRAP signal. */
#if defined(__TRAP_BRKPT) || defined(__TRAP_TRACE)
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __TRAP_BRKPT
	TRAP_BRKPT = __TRAP_BRKPT, /* Process breakpoint. */
#endif /* __TRAP_BRKPT */
#ifdef __TRAP_TRACE
	TRAP_TRACE = __TRAP_TRACE  /* Process trace trap. */
#endif /* __TRAP_TRACE */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __TRAP_BRKPT
#define TRAP_BRKPT TRAP_BRKPT /* Process breakpoint. */
#endif /* __TRAP_BRKPT */
#ifdef __TRAP_TRACE
#define TRAP_TRACE TRAP_TRACE /* Process trace trap. */
#endif /* __TRAP_TRACE */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __TRAP_BRKPT
#define TRAP_BRKPT __TRAP_BRKPT /* Process breakpoint. */
#endif /* __TRAP_BRKPT */
#ifdef __TRAP_TRACE
#define TRAP_TRACE __TRAP_TRACE /* Process trace trap. */
#endif /* __TRAP_TRACE */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __TRAP_... */
#endif /* __USE_XOPEN_EXTENDED */



#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
/* `si_code' values for SIGCHLD signal. */
#if (defined(__CLD_EXITED) || defined(__CLD_KILLED) ||  \
     defined(__CLD_DUMPED) || defined(__CLD_TRAPPED) || \
     defined(__CLD_STOPPED) || defined(__CLD_CONTINUED))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __CLD_EXITED
	CLD_EXITED    = __CLD_EXITED,    /* Child has exited. */
#endif /* __CLD_EXITED */
#ifdef __CLD_KILLED
	CLD_KILLED    = __CLD_KILLED,    /* Child was killed. */
#endif /* __CLD_KILLED */
#ifdef __CLD_DUMPED
	CLD_DUMPED    = __CLD_DUMPED,    /* Child terminated abnormally. */
#endif /* __CLD_DUMPED */
#ifdef __CLD_TRAPPED
	CLD_TRAPPED   = __CLD_TRAPPED,   /* Traced child has trapped. */
#endif /* __CLD_TRAPPED */
#ifdef __CLD_STOPPED
	CLD_STOPPED   = __CLD_STOPPED,   /* Child has stopped. */
#endif /* __CLD_STOPPED */
#ifdef __CLD_CONTINUED
	CLD_CONTINUED = __CLD_CONTINUED  /* Stopped child has continued. */
#endif /* __CLD_CONTINUED */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __CLD_EXITED
#define CLD_EXITED    CLD_EXITED    /* Child has exited. */
#endif /* __CLD_EXITED */
#ifdef __CLD_KILLED
#define CLD_KILLED    CLD_KILLED    /* Child was killed. */
#endif /* __CLD_KILLED */
#ifdef __CLD_DUMPED
#define CLD_DUMPED    CLD_DUMPED    /* Child terminated abnormally. */
#endif /* __CLD_DUMPED */
#ifdef __CLD_TRAPPED
#define CLD_TRAPPED   CLD_TRAPPED   /* Traced child has trapped. */
#endif /* __CLD_TRAPPED */
#ifdef __CLD_STOPPED
#define CLD_STOPPED   CLD_STOPPED   /* Child has stopped. */
#endif /* __CLD_STOPPED */
#ifdef __CLD_CONTINUED
#define CLD_CONTINUED CLD_CONTINUED /* Stopped child has continued. */
#endif /* __CLD_CONTINUED */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __CLD_EXITED
#define CLD_EXITED    __CLD_EXITED    /* Child has exited. */
#endif /* __CLD_EXITED */
#ifdef __CLD_KILLED
#define CLD_KILLED    __CLD_KILLED    /* Child was killed. */
#endif /* __CLD_KILLED */
#ifdef __CLD_DUMPED
#define CLD_DUMPED    __CLD_DUMPED    /* Child terminated abnormally. */
#endif /* __CLD_DUMPED */
#ifdef __CLD_TRAPPED
#define CLD_TRAPPED   __CLD_TRAPPED   /* Traced child has trapped. */
#endif /* __CLD_TRAPPED */
#ifdef __CLD_STOPPED
#define CLD_STOPPED   __CLD_STOPPED   /* Child has stopped. */
#endif /* __CLD_STOPPED */
#ifdef __CLD_CONTINUED
#define CLD_CONTINUED __CLD_CONTINUED /* Stopped child has continued. */
#endif /* __CLD_CONTINUED */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __CLD_... */



/* `si_code' values for SIGPOLL signal. */
#if (defined(__POLL_IN) || defined(__POLL_OUT) || defined(__POLL_MSG) || \
     defined(__POLL_ERR) || defined(__POLL_PRI) || defined(__POLL_HUP))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __POLL_IN
	POLL_IN  = __POLL_IN,  /* Data input available. */
#endif /* __POLL_IN */
#ifdef __POLL_OUT
	POLL_OUT = __POLL_OUT, /* Output buffers available. */
#endif /* __POLL_OUT */
#ifdef __POLL_MSG
	POLL_MSG = __POLL_MSG, /* Input message available.   */
#endif /* __POLL_MSG */
#ifdef __POLL_ERR
	POLL_ERR = __POLL_ERR, /* I/O error. */
#endif /* __POLL_ERR */
#ifdef __POLL_PRI
	POLL_PRI = __POLL_PRI, /* High priority input available. */
#endif /* __POLL_PRI */
#ifdef __POLL_HUP
	POLL_HUP = __POLL_HUP  /* Device disconnected. */
#endif /* __POLL_HUP */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __POLL_IN
#define POLL_IN  POLL_IN  /* Data input available. */
#endif /* __POLL_IN */
#ifdef __POLL_OUT
#define POLL_OUT POLL_OUT /* Output buffers available. */
#endif /* __POLL_OUT */
#ifdef __POLL_MSG
#define POLL_MSG POLL_MSG /* Input message available. */
#endif /* __POLL_MSG */
#ifdef __POLL_ERR
#define POLL_ERR POLL_ERR /* I/O error. */
#endif /* __POLL_ERR */
#ifdef __POLL_PRI
#define POLL_PRI POLL_PRI /* High priority input available. */
#endif /* __POLL_PRI */
#ifdef __POLL_HUP
#define POLL_HUP POLL_HUP /* Device disconnected. */
#endif /* __POLL_HUP */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __POLL_IN
#define POLL_IN  __POLL_IN  /* Data input available. */
#endif /* __POLL_IN */
#ifdef __POLL_OUT
#define POLL_OUT __POLL_OUT /* Output buffers available. */
#endif /* __POLL_OUT */
#ifdef __POLL_MSG
#define POLL_MSG __POLL_MSG /* Input message available. */
#endif /* __POLL_MSG */
#ifdef __POLL_ERR
#define POLL_ERR __POLL_ERR /* I/O error. */
#endif /* __POLL_ERR */
#ifdef __POLL_PRI
#define POLL_PRI __POLL_PRI /* High priority input available. */
#endif /* __POLL_PRI */
#ifdef __POLL_HUP
#define POLL_HUP __POLL_HUP /* Device disconnected. */
#endif /* __POLL_HUP */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __POLL_... */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */
#endif /* __USE_POSIX199309 || __USE_XOPEN_EXTENDED || __USE_KOS */


#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)

/* Possible values for `struct sigaltstack::ss_flags.'. */
#if defined(__SS_ONSTACK) || defined(__SS_DISABLE) || defined(__SS_AUTODISARM)
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __SS_ONSTACK
	SS_ONSTACK    = __SS_ONSTACK,   /* out.flag: Currently executing from the alternate signal stack. */
#endif /* __SS_ONSTACK */
#ifdef __SS_DISABLE
	SS_DISABLE    = __SS_DISABLE,   /* in.flag: Disable the alternate signal stack. (all other flags are ignored when set)
	                                 * out.flag: The alternate signal stack is currently disabled. */
#endif /* __SS_DISABLE */
#ifdef __SS_AUTODISARM
	SS_AUTODISARM = __SS_AUTODISARM /* flag:     Disable  the  alternate signal  stack upon  signal handler
	                                 *           entry by  saving its  old configuration  and disabling  it
	                                 *           by  means  of  `SS_DISABLE',  before  restoring  its prior
	                                 *           setting  once the signal  handler returns, thus preventing
	                                 *           other signal handlers from recursing onto an in-use stack. */
#endif /* __SS_AUTODISARM */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __SS_ONSTACK
#define SS_ONSTACK    SS_ONSTACK    /* out.flag: Currently executing from the alternate signal stack. */
#endif /* __SS_ONSTACK */
#ifdef __SS_DISABLE
#define SS_DISABLE    SS_DISABLE    /* in.flag: Disable the alternate signal stack. (all other flags are ignored when set)
                                     * out.flag: The alternate signal stack is currently disabled. */
#endif /* __SS_DISABLE */
#ifdef __SS_AUTODISARM
#define SS_AUTODISARM SS_AUTODISARM /* flag:     Disable  the  alternate signal  stack upon  signal handler
                                     *           entry by  saving its  old configuration  and disabling  it
                                     *           by  means  of  `SS_DISABLE',  before  restoring  its prior
                                     *           setting  once the signal  handler returns, thus preventing
                                     *           other signal handlers from recursing onto an in-use stack. */
#endif /* __SS_AUTODISARM */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __SS_ONSTACK
#define SS_ONSTACK    __SS_ONSTACK    /* out.flag: Currently executing from the alternate signal stack. */
#endif /* __SS_ONSTACK */
#ifdef __SS_DISABLE
#define SS_DISABLE    __SS_DISABLE    /* in.flag: Disable the alternate signal stack. (all other flags are ignored when set)
                                       * out.flag: The alternate signal stack is currently disabled. */
#endif /* __SS_DISABLE */
#ifdef __SS_AUTODISARM
#define SS_AUTODISARM __SS_AUTODISARM /* flag:     Disable  the  alternate signal  stack upon  signal handler
                                       *           entry by  saving its  old configuration  and disabling  it
                                       *           by  means  of  `SS_DISABLE',  before  restoring  its prior
                                       *           setting  once the signal  handler returns, thus preventing
                                       *           other signal handlers from recursing onto an in-use stack. */
#endif /* __SS_AUTODISARM */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __SS_ONSTACK || __SS_DISABLE */

#ifdef __MINSIGSTKSZ
#define MINSIGSTKSZ __MINSIGSTKSZ /* Minimum stack size for a signal handler. */
#endif /* __MINSIGSTKSZ */

#ifdef __SIGSTKSZ
#define SIGSTKSZ __SIGSTKSZ /* System default stack size. */
#endif /* __SIGSTKSZ */

#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */



}
%#ifdef __CC__
%{

#if (defined(__USE_POSIX199309) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_KOS))
#ifndef __sigevent_t_defined
#define __sigevent_t_defined
typedef struct sigevent sigevent_t;
#endif /* !__sigevent_t_defined */
#ifndef __siginfo_t_defined
#define __siginfo_t_defined
typedef struct __siginfo_struct siginfo_t;
#endif /* !__siginfo_t_defined */
#ifndef __sigval_t_defined
#define __sigval_t_defined
typedef union sigval sigval_t;
#endif /* !__sigval_t_defined */
#endif /* __USE_POSIX199309 || __USE_XOPEN_EXTENDED || __USE_KOS */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
#ifndef __stack_t_defined
#define __stack_t_defined
typedef struct sigaltstack stack_t;
#endif /* !__stack_t_defined */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

#ifndef __std_sig_atomic_t_defined
#define __std_sig_atomic_t_defined
__NAMESPACE_STD_BEGIN
/* An integral type  that can be  modified atomically, without  the
 * possibility of a signal arriving in the middle of the operation. */
typedef __SIG_ATOMIC_TYPE__ sig_atomic_t;
__NAMESPACE_STD_END
#endif /* !__std_sig_atomic_t_defined */
#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __sig_atomic_t_defined
#define __sig_atomic_t_defined
__NAMESPACE_STD_USING(sig_atomic_t)
#endif /* !__sig_atomic_t_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */

#ifdef __USE_POSIX
#ifndef __sigset_t_defined
#define __sigset_t_defined
typedef struct __sigset_struct sigset_t;
#endif /* !__sigset_t_defined */
#endif /* __USE_POSIX */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#ifndef __pid_t_defined
#define __pid_t_defined
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */
#ifndef __uid_t_defined
#define __uid_t_defined
typedef __uid_t uid_t;
#endif /* !__uid_t_defined */
#endif /* __USE_XOPEN || __USE_XOPEN2K */

#ifndef ____sighandler_t_defined
#define ____sighandler_t_defined
typedef void (__LIBKCALL *__sighandler_t)(int __signo);
#endif /* !____sighandler_t_defined */

#ifdef __USE_GNU
#ifndef __sighandler_t_defined
#define __sighandler_t_defined
typedef __sighandler_t sighandler_t;
#endif /* !__sighandler_t_defined */
#endif /* __USE_GNU */

#ifdef __USE_MISC
#if !defined(NSIG) && defined(__NSIG)
#define NSIG __NSIG
#endif /* !NSIG && __NSIG */
#ifndef __sig_t_defined
#define __sig_t_defined
typedef __sighandler_t sig_t;
#endif /* !__sig_t_defined */
#endif /* __USE_MISC */

}


/* NOTE: We can only leave our the `!= 0' check in `sigismember()',
 *       and do `return sigset->word & mask',  when doing so  can't
 *       cause the value to be  truncated to zero. The later  would
 *       happen in the above when `mask > UINT_MAX', in which  case
 *       casting everything to `int' would  cut off the upper  non-
 *       zero  bits, and cause  the function to  return `0' when it
 *       should in fact return non-zero. */
%[define(DEFINE___PRIVATE_SIGSET_VALIDATE_SIGNO =
#ifndef __PRIVATE_SIGSET_VALIDATE_SIGNO
#if defined(__KERNEL__) && __SIZEOF_INT__ >= __SIZEOF_POINTER__
#define __PRIVATE_SIGSET_ISMEMBER_EXT /* nothing */
#else /* __KERNEL__ && __SIZEOF_INT__ >= __SIZEOF_POINTER__ */
#define __PRIVATE_SIGSET_ISMEMBER_EXT != 0
#endif /* !__KERNEL__ && __SIZEOF_INT__ < __SIZEOF_POINTER__ */
#if defined(__KERNEL__) && defined(__KOS__)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(@signo@) /* nothing */
#elif defined(__NSIG) && defined(__EINVAL)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(@signo@)     \
	if __unlikely(@signo@ <= 0 || @signo@ >= __NSIG) { \
		return __libc_seterrno(__EINVAL);          \
	}
#elif defined(__NSIG)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(@signo@)     \
	if __unlikely(@signo@ <= 0 || @signo@ >= __NSIG) { \
		return __libc_seterrno(1);                 \
	}
#elif defined(__EINVAL)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(@signo@) \
	if __unlikely(@signo@ <= 0) {                \
		return __libc_seterrno(__EINVAL);      \
	}
#else /* ... */
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(@signo@) \
	if __unlikely(@signo@ <= 0) {                \
		return __libc_seterrno(1);             \
	}
#endif /* !... */
#endif /* !__PRIVATE_SIGSET_VALIDATE_SIGNO */
)]

%[insert:prefix(
DEFINE___PRIVATE_SIGSET_VALIDATE_SIGNO
)]



%(c, ccompat){
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
}%{
#ifndef __std_size_t_defined
#define __std_size_t_defined
__NAMESPACE_STD_BEGIN
typedef __SIZE_TYPE__ size_t;
__NAMESPACE_STD_END
#endif /* !__std_size_t_defined */

#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __size_t_defined
#define __size_t_defined
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */
}%(c, ccompat){
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */
}%{

}

%[insert:std]

@@>> raise(3)
@@Raise a signal within the current thread.
@@In  a *-threaded process this is same as:
@@  *=multi:  `pthread_kill(pthread_self(), signo)'
@@  *=single: `kill(getpid(), signo)'
@@@return: 0:  Success
@@@return: -1: [errno=EINVAL] The given `signo' is invalid
[[std, userimpl, crt_dos_variant, decl_include("<bits/types.h>")]]
[[requires(($has_function(pthread_kill) && $has_function(pthread_self)) ||
           ($has_function(kill) && $has_function(getpid)))]]
[[libc, impl_include("<libc/errno.h>")]]
int raise($signo_t signo) {
@@pp_if $has_function(pthread_kill) && $has_function(pthread_self)@@
	errno_t error;
	error = pthread_kill(pthread_self(), signo);
	if unlikely(error != EOK)
		error = (errno_t)libc_seterrno(error);
	return (int)error;
@@pp_else@@
	return kill(getpid(), signo);
@@pp_endif@@
}

%[insert:function(__sysv_signal = sysv_signal)]

%#ifdef __USE_GNU
@@>> sysv_signal(3)
@@Wrapper for `sigaction(2)' to establish a signal handler as:
@@    >> struct sigaction act, oact
@@    >> act.sa_handler = handler;
@@    >> act.sa_flags   = (SA_RESETHAND | SA_NODEFER) & ~SA_RESTART;
@@    >> sigemptyset(&act.sa_mask);
@@    >> if (sigaction(signo, &act, &oact) != 0)
@@    >>     oact.sa_handler = SIG_ERR;
@@    >> return oact.sa_handler;
@@@return: * :      The previous signal handler function.
@@@return: SIG_ERR: Error (s.a. `errno')
[[decl_include("<bits/types.h>", "<bits/os/sigaction.h>")]]
[[export_alias("__sysv_signal"), crt_dos_variant]]
[[requires_include("<asm/os/signal.h>")]]
[[userimpl, requires(defined(@__SA_RESETHAND@) && defined(@__SA_NODEFER@) &&
                     defined(@__SIG_ERR@) && $has_function(sigaction))]]
[[impl_include("<asm/os/signal.h>")]]
[[impl_include("<bits/os/sigaction.h>")]]
$sighandler_t sysv_signal($signo_t signo, $sighandler_t handler) {
	struct @sigaction@ act, oact
	act.@sa_handler@ = handler;
	act.@sa_flags@   = @__SA_RESETHAND@ | @__SA_NODEFER@;
	sigemptyset(&act.@sa_mask@);
	if (sigaction(signo, &act, &oact) != 0)
	    oact.@sa_handler@ = @__SIG_ERR@;
	return oact.@sa_handler@;
}
%#endif /* __USE_GNU */


@@>> signal(2/3)
@@Non-portable  signal  handler  establishment  function  that  behaves
@@either like `sysv_signal()', `bsd_signal()', or has its own behavior.
@@On KOS, this function behaves identical to `bsd_signal()'
@@@return: * :      The previous signal handler function.
@@@return: SIG_ERR: Error (s.a. `errno')
[[std, no_crt_self_import, alias("sysv_signal")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_MISC)), preferred_alias("signal", "_signal")]]
[[crt_dos_variant, dos_export_as("DOS$_signal")]]
[[decl_include("<bits/types.h>", "<bits/os/sigaction.h>")]]
$sighandler_t signal($signo_t signo, $sighandler_t handler);

%#ifdef __USE_MISC
%#define sigmask(signo) __sigset_mask(signo)

@@>> ssignal(3)
@@Establish a software-signal-handler. This handler may or may not
@@be distinct from normal signal handlers, and should be triggered
@@by `gsignal(3)', rather than `raise(3)'.
@@On KOS, this function behaves identical to `bsd_signal()'
@@@return: * :      The previous signal handler function.
@@@return: SIG_ERR: Error (s.a. `errno')
[[decl_include("<bits/types.h>", "<bits/os/sigaction.h>"), crt_dos_variant]]
[[userimpl, requires_function(bsd_signal)]]
$sighandler_t ssignal($signo_t signo, $sighandler_t handler) {
	return bsd_signal(signo, handler);
}

@@>> gsignal(3)
@@Raise a software-signal  by invoking  a previously  established
@@software-signal-handler,  as   set  by   `ssignal(signo, ...)'.
@@This method by which a software signal is raised may or may not
@@be distinct from normal signal handlers.
@@On KOS, this function behaves identical to `raise()'
@@@return: 0:  Success
@@@return: -1: [errno=EINVAL] The given `signo' is invalid
[[decl_include("<bits/types.h>"), crt_dos_variant]]
[[userimpl, requires_function(raise)]]
int gsignal($signo_t signo) {
	return raise(signo);
}

@@>> sigblock(3)
@@Deprecated  method  of  SIG_BLOCK-ing  a  given  set  of
@@signals. Modern code should use `sigprocmask()' instead.
@@@return: * : First 32 bits of previous signal mask (or however many fit in `int')
[[deprecated("Using `sigprocmask(SIG_BLOCK)' instead")]]
[[requires_include("<asm/os/signal.h>"), export_alias("__sigblock")]]
[[requires(defined(__SIG_BLOCK) && $has_function(sigprocmask))]]
[[impl_include("<asm/os/signal.h>", "<bits/os/sigset.h>", "<hybrid/typecore.h>")]]
int sigblock(int mask) {
	sigset_t sigset, osigset;
	sigfillset(&sigset);
	sigset.@__val@[0] = (ulongptr_t)(unsigned int)mask;
@@pp_if __SIZEOF_POINTER__ > __SIZEOF_INT__@@
	sigset.__val[0] |= ((ulongptr_t)-1 << (__SIZEOF_INT__ * 8));
@@pp_endif@@
	if (sigprocmask(__SIG_BLOCK, &sigset, &osigset) != 0)
		sigemptyset(&osigset);
	return osigset.@__val@[0];
}

@@>> sigsetmask(3)
@@Deprecated method of SIG_SETMASK-ing a given set of signals.
@@Modern code should  use `sigprocmask(SIG_SETMASK)'  instead.
@@@return: * : First 32 bits of previous signal mask (or however many fit in `int')
[[deprecated("Using `sigprocmask()' instead")]]
[[requires_include("<asm/os/signal.h>"), export_alias("__sigsetmask")]]
[[requires(defined(__SIG_SETMASK) && $has_function(sigprocmask))]]
[[impl_include("<asm/os/signal.h>", "<bits/os/sigset.h>")]]
int sigsetmask(int mask) {
	sigset_t sigset, osigset;
	sigfillset(&sigset);
	sigset.@__val@[0] = (ulongptr_t)(unsigned int)mask;
@@pp_if __SIZEOF_POINTER__ > __SIZEOF_INT__@@
	sigset.__val[0] |= ((ulongptr_t)-1 << (__SIZEOF_INT__ * 8));
@@pp_endif@@
	if (sigprocmask(__SIG_SETMASK, &sigset, &osigset) != 0)
		sigemptyset(&osigset);
	return (int)(unsigned int)osigset.@__val@[0];
}

@@>> sigsetmask(3)
@@Deprecated method of  retrieving the masking-state  of
@@the lowest-numberred `sizeof(int) * NBBY - 1' signals.
@@@return: * : First 32 bits of signal mask (or however many fit in `int')
[[deprecated("Using `sigprocmask()' instead")]]
[[requires($has_function(sigprocmask)), export_alias("__siggetmask")]]
[[impl_include("<asm/os/signal.h>", "<bits/os/sigset.h>", "<hybrid/typecore.h>")]]
int siggetmask(void) {
	sigset_t sigset;
@@pp_if defined(__SIG_SETMASK)@@
	if (sigprocmask(__SIG_SETMASK, NULL, &sigset))
		return -1;
@@pp_else@@
	if (sigprocmask(0, NULL, &sigset))
		return -1;
@@pp_endif@@
	return (int)(unsigned int)sigset.@__val@[0];
}

@@>> __old_sigpause(3)
@@For historical reasons, this is the ABI `sigpause(3)' function...
[[hidden, requires($has_function(sigsuspend))]]
[[crt_name("sigpause"), export_alias("__sigpause")]]
[[impl_include("<asm/os/signal.h>", "<bits/os/sigset.h>", "<hybrid/typecore.h>")]]
int __old_sigpause(int sigmask0) {
	sigset_t sigset;
	sigfillset(&sigset);
	sigset.__val[0] = (ulongptr_t)(unsigned int)sigmask0;
#if __SIZEOF_POINTER__ > __SIZEOF_INT__
	sigset.__val[0] |= ((ulongptr_t)-1 << (__SIZEOF_INT__ * 8));
#endif /* __SIZEOF_POINTER__ > __SIZEOF_INT__ */
	return sigsuspend(&sigset);
}


%
%{
#ifndef sys_siglist
#ifdef _sys_siglist
#define sys_siglist _sys_siglist
#else /* _sys_siglist */
}
[[guard, const, wunused, nothrow, nonnull]]
[[section(".text.crt.errno.sys_siglist")]]
char const *const *__p_sys_siglist();
%{
#ifdef ____p_sys_siglist_defined
#define sys_siglist  __p_sys_siglist()
#define _sys_siglist __p_sys_siglist()
#endif /* ____p_sys_siglist_defined */
#ifndef _sys_siglist
#ifdef __CRT_HAVE_sys_siglist
#ifdef __NSIG
__CSDECLARE2(,char const *const sys_siglist[__NSIG],sys_siglist)
#else /* __NSIG */
__CSDECLARE2(,char const *const sys_siglist[],sys_siglist)
#endif /* !__NSIG */
#define sys_siglist  sys_siglist
#define _sys_siglist sys_siglist
#elif defined(__CRT_HAVE__sys_siglist)
#ifdef __NSIG
__CSDECLARE2(,char const *const _sys_siglist[__NSIG],_sys_siglist)
#else /* __NSIG */
__CSDECLARE2(,char const *const _sys_siglist[],_sys_siglist)
#endif /* !__NSIG */
#define sys_siglist  _sys_siglist
#define _sys_siglist _sys_siglist
#endif /* sys_siglist... */
#endif /* !_sys_siglist */
#endif /* !_sys_siglist */
#endif /* !sys_siglist */

#if !defined(_sys_siglist) && defined(sys_siglist)
#define _sys_siglist sys_siglist
#endif /* !_sys_siglist && sys_siglist */
}

%struct sigcontext;

@@Don't  call directly. Used internally to resume
@@execution when returning from a signal handler.
[[noreturn, decl_prefix(struct sigcontext;)]]
void sigreturn(struct sigcontext const *scp);

%#endif /* __USE_MISC */

%
%#ifdef __USE_BSD
%{
#ifndef sys_signame
#ifdef sys_sigabbrev
#define sys_signame sys_sigabbrev
#elif defined(__CRT_HAVE_sys_signame)
#ifdef __NSIG
__CSDECLARE2(,char const *const sys_signame[__NSIG],sys_signame)
#else /* __NSIG */
__CSDECLARE2(,char const *const sys_signame[],sys_signame)
#endif /* !__NSIG */
#define sys_signame sys_signame
#elif defined(__CRT_HAVE_sys_sigabbrev)
#ifdef __NO_COMPILER_SREDIRECT
#ifdef __NSIG
__CSREDIRECT2(,char const *const sys_signame[__NSIG],sys_signame,sys_sigabbrev)
#else /* __NSIG */
__CSREDIRECT2(,char const *const sys_signame[],sys_signame,sys_sigabbrev)
#endif /* !__NSIG */
#define sys_signame sys_signame
#else /* __NO_COMPILER_SREDIRECT */
#ifdef __NSIG
__CSDECLARE2(,char const *const sys_sigabbrev[__NSIG],sys_sigabbrev)
#else /* __NSIG */
__CSDECLARE2(,char const *const sys_sigabbrev[],sys_sigabbrev)
#endif /* !__NSIG */
#define sys_sigabbrev sys_sigabbrev
#define sys_signame   sys_sigabbrev
#endif /* !__NO_COMPILER_SREDIRECT */
#endif /* ... */
#endif /* !sys_signame */

#ifndef sys_nsig
#ifdef __CRT_HAVE_sys_nsig
__CSDECLARE(,int const,sys_nsig)
#define sys_nsig sys_nsig
#endif /* __CRT_HAVE_sys_nsig */
#endif /* !sys_nsig */
}
%#endif /* __USE_BSD */


%
%#ifdef __USE_XOPEN

@@>> bsd_signal(3)
@@Wrapper for `sigaction(2)' to establish a signal handler as:
@@    >> struct sigaction act, oact
@@    >> act.sa_handler = handler;
@@    >> sigemptyset(&act.sa_mask);
@@    >> sigaddset(&act.sa_mask, signo);
@@    >> act.sa_flags = sigismember(&[SIGNALS_WITH_SIGINTERRUPT], signo) ? 0 : SA_RESTART;
@@    >> SET_SIGRESTORE(act);
@@    >> if (sigaction(signo, &act, &oact) != 0)
@@    >>     oact.sa_handler = SIG_ERR;
@@    >> return oact.sa_handler;
@@    Where `SIGNALS_WITH_SIGINTERRUPT' is the set of signals for  which
@@    `siginterrupt(3)' had last been called with a non-zero `interrupt'
@@    argument
@@@return: * :      The previous signal handler function.
@@@return: SIG_ERR: Error (s.a. `errno')
[[decl_include("<bits/types.h>", "<bits/os/sigaction.h>"), crt_dos_variant]]
[[export_alias("__bsd_signal")]]
$sighandler_t bsd_signal($signo_t signo, $sighandler_t handler);

@@>> sigpause(3)
@@Atomically save and set the caller's signal mask to consist solely
@@of the signal signal `signo', then wait for that signal to  arrive
@@before restoring the old signal mask.
@@@return: -1: [errno=EINTR] The signal handler for `signo' was executed.
[[requires_function(sigsuspend)]]
[[crt_name("__xpg_sigpause"), decl_include("<bits/types.h>")]]
int sigpause($signo_t signo) {
	sigset_t mask;
	sigemptyset(&mask);
	sigaddset(&mask, signo);
	return sigsuspend(&mask);
}

%#endif /* __USE_XOPEN */
%
%#ifdef __USE_POSIX

@@>> kill(2)
@@Raise a signal `signo' within the process(es) specified by `pid':
@@  - pid > 0:   Deliver `signo' to a process who's PID matches `pid'.
@@  - pid == 0:  Deliver `signo' to every process within the caller's process group.
@@  - pid == -1: Deliver  `signo'  to  every process  the  caller has  permission  to send
@@               signals to, with the exception of a process with pid=1 (i.e. `/bin/init')
@@  - pid < -1:  Deliver `signo' to every process within the process group `-pid'
@@@param: signo: The signal number to deliver. When set to `0', no signal is  delivered,
@@               and this function can be used to test if the caller would be allowed to
@@               send signals to the process(es) specified by `pid'
@@@return: 0:    Success
@@@return: -1:   [errno=EINVAL] The given `signo' is invalid
@@@return: -1:   [errno=EPERM]  The caller does not have permission to send signals to `pid'
@@@return: -1:   [errno=ESRCH]  No process is identified by `pid'
[[decl_include("<bits/types.h>")]]
[[export_alias("__kill", "__libc_kill")]]
int kill($pid_t pid, $signo_t signo);

@@>> sigemptyset(3)
@@Clear the given signal set of all contained signals
@@@return: 0: Always returns `0'
[[kernel, decl_include("<bits/os/sigset.h>")]]
[[impl_include("<bits/os/sigset.h>")]]
int sigemptyset([[out]] $sigset_t *set) {
	bzeroc(set->__val, COMPILER_LENOF(set->__val), __SIZEOF_POINTER__);
	return 0;
}

@@>> sigfillset(3)
@@Add all possible signals (possibly even including undefined signals,
@@though these would be ignored by the kernel) to the given signal set
@@@return: 0: Always returns `0'
[[kernel, decl_include("<bits/os/sigset.h>")]]
[[libc, impl_include("<bits/os/sigset.h>")]]
int sigfillset([[out]] $sigset_t *set) {
@@pp_if __SIZEOF_POINTER__ == 8@@
	memsetq(set->__val, __UINT64_C(0xffffffffffffffff), COMPILER_LENOF(set->__val));
@@pp_elif __SIZEOF_POINTER__ == 4@@
	memsetl(set->__val, __UINT32_C(0xffffffff), COMPILER_LENOF(set->__val));
@@pp_elif __SIZEOF_POINTER__ == 2@@
	memsetw(set->__val, __UINT16_C(0xffff), COMPILER_LENOF(set->__val));
@@pp_else@@
	memset(set->__val, __UINT8_C(0xff), __SIZEOF_SIGSET_T__);
@@pp_endif@@
	return 0;
}


@@>> sigaddset(3)
@@Add only the given `signo' to the given signal set
@@@return: 0:  Success (Always returned by the kernel-version)
@@@return: -1: [errno=EINVAL] invalid `signo'.
@@             Not returned by the kernel-version of this function!
[[kernel, extern_inline, alias("__sigaddset")]]
[[if(!defined(__KERNEL__)), export_as("__sigaddset")]]
[[decl_include("<bits/types.h>", "<bits/os/sigset.h>")]]
[[impl_include("<libc/errno.h>", "<asm/os/signal.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
[[impl_prefix(DEFINE___PRIVATE_SIGSET_VALIDATE_SIGNO)]]
int sigaddset([[inout]] $sigset_t *set, $signo_t signo) {
	$ulongptr_t mask, word;
	__PRIVATE_SIGSET_VALIDATE_SIGNO(signo)
	mask = __sigset_mask(signo);
	word = __sigset_word(signo);
	set->__val[word] |= mask;
	return 0;
}

@@>> sigdelset(3)
@@Remove only the given `signo' from the given signal set
@@@return: 0:  Success (Always returned by the kernel-version)
@@@return: -1: [errno=EINVAL] invalid `signo'.
@@             Not returned by the kernel-version of this function!
[[kernel, extern_inline, alias("__sigdelset")]]
[[if(!defined(__KERNEL__)), export_as("__sigdelset")]]
[[decl_include("<bits/types.h>", "<bits/os/sigset.h>")]]
[[impl_include("<libc/errno.h>", "<asm/os/signal.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
[[impl_prefix(DEFINE___PRIVATE_SIGSET_VALIDATE_SIGNO)]]
int sigdelset([[inout]] $sigset_t *set, $signo_t signo) {
	$ulongptr_t mask, word;
	__PRIVATE_SIGSET_VALIDATE_SIGNO(signo)
	mask = __sigset_mask(signo);
	word = __sigset_word(signo);
	set->__val[word] &= ~mask;
	return 0;
}

@@>> sigismember(3)
@@Check if a given `signo' is apart of the a given signal set
@@@return: >1: The given `signo' is apart of `set' (may be returned by the kernel-version of this function)
@@@return:  1: The given `signo' is apart of `set'
@@@return:  0: The given `signo' isn't apart of `set'
@@@return: -1: [errno=EINVAL] invalid `signo'.
@@             Not returned by the kernel-version of this function!
[[kernel, extern_inline, pure, wunused, alias("__sigismember")]]
[[if(!defined(__KERNEL__)), export_as("__sigismember")]]
[[decl_include("<bits/types.h>", "<bits/os/sigset.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
[[impl_prefix(DEFINE___PRIVATE_SIGSET_VALIDATE_SIGNO)]]
int sigismember([[in]] $sigset_t const *set, $signo_t signo) {
	$ulongptr_t mask, word;
	__PRIVATE_SIGSET_VALIDATE_SIGNO(signo)
	mask = __sigset_mask(signo);
	word = __sigset_word(signo);
	return (set->__val[word] & mask) __PRIVATE_SIGSET_ISMEMBER_EXT;
}

@@Change  the signal mask for the calling thread. Note that portable
@@programs that also make use of multithreading must instead use the
@@pthread-specific  `pthread_sigmask()'  function instead,  as POSIX
@@states that  this function  behaves undefined  in such  scenarios.
@@However, on KOS, `pthread_sigmask()' is  simply an alias for  this
@@function,  and  `sigprocmask()'   always  operates   thread-local.
@@Note also  that on  KOS 2  additional functions  `getsigmaskptr()'
@@and `setsigmaskptr()'  exist, which  can be  used to  get/set  the
@@address of the signal mask used by the kernel.
@@@param how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK'
@@@return: 0:  Success
@@@return: -1: [errno=EINVAL] Invalid `how'
[[libc, decl_prefix(struct __sigset_struct;), decl_include("<features.h>")]]
[[export_alias("__sigprocmask", "__libc_sigprocmask", "pthread_sigmask", "thr_sigsetmask")]]
int sigprocmask(__STDC_INT_AS_UINT_T how,
                [[in_opt]] sigset_t const *set,
                [[out_opt]] sigset_t *oset);

%#ifdef __USE_KOS

%
%#ifdef __NSIG
%/* >> sigvalid(3)
% * Verify that `signo' is a valid signal number. */
%#define sigvalid(signo) ((signo) > 0 && (signo) < __NSIG)
%#endif /* __NSIG */
%

@@>> getsigmaskptr(3)
@@Return   the   current  signal   mask  pointer.
@@See the documentation of `setsigmaskptr(3)' for
@@what this function is all about.
@@@return: * : A pointer to the calling thread's current signal mask
[[libc, nonnull, wunused, decl_include("<bits/os/sigset.h>")]]
sigset_t *getsigmaskptr(void);

@@>> setsigmaskptr(3)
@@Set  the  current  signal  mask  pointer  to `sigmaskptr'
@@This  is  a kos-specific  function  that can  be  used to
@@speed up/replace  calls  to  `sigprocmask()'.  But  using
@@this function safely requires knowledge of its underlying
@@semantics. If you're unsure on those, you should  instead
@@just use the portable `sigprocmask()' and forget you ever
@@read this comment :)
@@Example usage:
@@>> static sigset_t const fullset = SIGSET_INIT_FULL;
@@>> sigset_t *oldset = setsigmaskptr((sigset_t *)&fullset);
@@>> // Code in here executes with all maskable signals masked
@@>> // Note however that code in here also mustn't call sigprocmask()
@@>> setsigmaskptr(oldset);
@@Equivalent code using sigprocmask (which has way more overhead):
@@>> static sigset_t const fullset = SIGSET_INIT_FULL;
@@>> sigset_t oldset;
@@>> sigprocmask(SIG_SETMASK, &fullset, &oldset);
@@>> // Code in here executes with all maskable signals masked
@@>> sigprocmask(SIG_SETMASK, &oldset, NULL);
@@@param: sigmaskptr: Address of the signal mask to use from now on.
@@@return: * : Address of the previously used signal mask.
[[libc, nonnull, decl_include("<bits/os/sigset.h>")]]
sigset_t *setsigmaskptr([[/*async_inout*/nonnull]] sigset_t *sigmaskptr);

@@>> setsigmaskfullptr(3)
@@Same as  `setsigmaskptr()',  but  set a  statically  allocated,  fully
@@filled signal  mask  as  the calling  thread's  current  signal  mask.
@@This essentially means that this  function can be used to  temporarily
@@disable the reception of all  signals within the calling thread,  thus
@@allowing the thread to run  without being interrupted (by another  but
@@SIGKILL and SIGSTOP, which can't be masked), until the returned signal
@@mask is restored.
@@>> sigset_t *os;
@@>> os = setsigmaskfullptr();
@@>> ...
@@>> setsigmaskptr(os);
[[libc, requires_function(setsigmaskptr)]]
[[decl_include("<bits/os/sigset.h>")]]
[[impl_include("<bits/os/sigset.h>")]]
[[userimpl, nonnull]] sigset_t *setsigmaskfullptr(void) {
	static sigset_t const ss_full = __SIGSET_INIT((__ULONGPTR_TYPE__)-1);
	return setsigmaskptr((sigset_t *)&ss_full);
}

%struct userprocmask;

@@>> getuserprocmask(3)
@@Return a pointer to the calling thread's userprocmask
@@This function is only  declared if supported by  libc
[[guard, const, nonnull, wunused, nothrow, decl_prefix(struct userprocmask;)]]
[[crt_impl_if(!defined(__KERNEL__) && defined(__LIBC_CONFIG_HAVE_USERPROCMASK))]]
struct userprocmask *getuserprocmask(void);

@@>> chkuserprocmask(3)
@@Following the calling thread's userprocmask becoming less
@@restrictive, check for pending signals and handle them if
@@necessary
@@This function is only declared if supported by libc
[[guard, nothrow]]
[[crt_impl_if(!defined(__KERNEL__) && defined(__LIBC_CONFIG_HAVE_USERPROCMASK))]]
void chkuserprocmask(void);

%#endif /* __USE_KOS */

@@>> sigsuspend(2)
@@Atomically save and  set the caller's  signal mask to  `set', then wait  for
@@one of the unmasked (iow: `!sigismember')-signals to arrive before restoring
@@the old signal mask.
@@@param: set: The set of signals on which to wait
@@@return: -1: [errno=EINTR] The signal handler for `signo' was executed.
[[cp, export_alias("__sigsuspend")]]
[[decl_include("<bits/os/sigset.h>")]]
int sigsuspend([[in]] sigset_t const *set);

@@>> sigaction(2)
@@Get/Set the  action that  shall  be performed  when  a
@@signal `signo' must be handled by the calling process.
@@This function will modify the caller's kernel-space signal handler  descriptor,
@@who's shared/unshared behavior between threads is controlled by `CLONE_SIGHAND'
@@@return: 0:  Success
@@@return: -1: [errno=EINVAL] The given `signo' is invalid
[[decl_include("<bits/types.h>")]]
[[export_alias("__sigaction"), decl_prefix(struct sigaction;)]]
int sigaction($signo_t signo,
              [[in_opt]] struct sigaction const *act,
              [[out_opt]] struct sigaction *oact);

@@>> sigpending(2)
@@Retrieve the set of signals that are pending
@@in  either  the calling  thread  and process
@@@return: 0: Success
[[decl_include("<bits/os/sigset.h>")]]
[[export_alias("__sigpending", "__libc_sigpending")]]
int sigpending([[out]] sigset_t *__restrict set);

@@>> sigwait(3)
@@Same as `sigsuspend(2)', but write-back the actual signal that was raised to `*signo'
@@@return: -1: [errno=EINTR] The signal handler for `signo' was executed.
[[cp, decl_include("<bits/os/sigset.h>", "<bits/types.h>")]]
int sigwait([[in]] sigset_t const *__restrict set,
            [[out]] $signo_t *__restrict signo);

%#ifdef __USE_GNU
@@>> sigisemptyset(3)
@@Check if the given signal set is empty
@@@return: != 0: Yes, it is empty
@@@return: == 0: No, at least 1 signal is contained
[[kernel, libc, pure, wunused, decl_include("<bits/os/sigset.h>")]]
int sigisemptyset([[in]] $sigset_t const *__restrict set) {
	size_t i;
	for (i = 0; i < COMPILER_LENOF(set->__val); ++i) {
		if (set->__val[i] != 0)
			return 0; /* Not empty! */
	}
	return 1;
}


@@>> sigandset(3)
@@Set-up every signal `S' from `set' as the result of `set[S] = left[S] & right[S]'
@@@return: 0: Always returns `0'
[[kernel, decl_include("<bits/os/sigset.h>")]]
int sigandset([[out]] $sigset_t *set,
              [[in]] $sigset_t const *left,
              [[in]] $sigset_t const *right) {
	size_t i;
	for (i = 0; i < COMPILER_LENOF(set->__val); ++i)
		set->__val[i] = left->__val[i] & right->__val[i];
	return 0;
}

@@>> sigorset(3)
@@Set-up every signal `S' from `set' as the result of `set[S] = left[S] | right[S]'
@@@return: 0: Always returns `0'
[[kernel, decl_include("<bits/os/sigset.h>")]]
int sigorset([[out]] $sigset_t *set,
             [[in]] $sigset_t const *left,
             [[in]] $sigset_t const *right) {
	size_t i;
	for (i = 0; i < COMPILER_LENOF(set->__val); ++i)
		set->__val[i] = left->__val[i] | right->__val[i];
	return 0;
}
%#endif /* __USE_GNU */


%#ifdef __USE_KOS
@@>> signandset(3)
@@Set-up every signal `S' from `set' as the result of `set[S] = left[S] & ~right[S]'
@@@return: 0: Always returns `0'
[[kernel, decl_include("<bits/os/sigset.h>")]]
int signandset([[out]] $sigset_t *set,
               [[in]] $sigset_t const *left,
               [[in]] $sigset_t const *right) {
	size_t i;
	for (i = 0; i < COMPILER_LENOF(set->__val); ++i)
		set->__val[i] = left->__val[i] & ~right->__val[i];
	return 0;
}
%#endif /* __USE_KOS */


%#ifdef __USE_POSIX199309

@@>> sigwaitinfo(2)
@@Same as `sigsuspend(2)',  but write-back extended  information in the  signal,
@@as it would/has also been passed to a signal handler's second (info) argument.
@@@param: set:  The set of signals on which to wait
@@@param: info: Information about the signal on which to wait.
@@@return: -1: [errno=EINTR] The signal handler for `signo' was executed.
[[cp, decl_include("<bits/os/siginfo.h>", "<bits/os/sigset.h>")]]
int sigwaitinfo([[in]] $sigset_t const *__restrict set,
                [[out_opt]] siginfo_t *__restrict info);

[[cp, ignore, nocrt, alias("sigtimedwait"), doc_alias("sigtimedwait")]]
[[decl_include("<bits/os/siginfo.h>", "<bits/os/sigset.h>", "<bits/os/timespec.h>")]]
int sigtimedwait32([[in]] $sigset_t const *__restrict set,
                   [[out_opt]] siginfo_t *__restrict info,
                   [[in_opt]] struct $timespec32 const *rel_timeout);

@@>> sigtimedwait(2), sigtimedwait64(2)
@@Same as `sigwaitinfo(2)', but stop waiting after a total of `rel_timeout' has passed
@@@param: set:         The set of signals on which to wait
@@@param: info:        Information about the signal on which to wait.
@@@param: rel_timeout: The timeout specifying for how long to wait (or `NULL' to wait indefinitely)
@@@return: -1: [errno=EINTR]  The signal handler for `signo' was executed.
@@@return: -1: [errno=EAGAIN] A total of `rel_timeout' has passed.
[[cp, decl_include("<bits/os/siginfo.h>", "<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("sigtimedwait")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("sigtimedwait64")]]
[[userimpl, requires($has_function(sigtimedwait32) || $has_function(sigtimedwait64))]]
int sigtimedwait([[in]] $sigset_t const *__restrict set,
                 [[out_opt]] siginfo_t *__restrict info,
                 [[in_opt]] struct timespec const *rel_timeout) {
@@pp_if $has_function(sigtimedwait64)@@
	struct timespec64 tmv;
	if (!rel_timeout)
		return sigtimedwait64(set, info, NULL);
	tmv.tv_sec  = (__time64_t)rel_timeout->tv_sec;
	tmv.tv_nsec = rel_timeout->tv_nsec;
	return sigtimedwait64(set, info, NULL);
@@pp_else@@
	struct timespec32 tmv;
	if (!rel_timeout)
		return sigtimedwait32(set, info, NULL);
	tmv.tv_sec  = (__time32_t)rel_timeout->tv_sec;
	tmv.tv_nsec = rel_timeout->tv_nsec;
	return sigtimedwait32(set, info, NULL);
@@pp_endif@@
}

@@>> sigqueue(2)
@@Similar to  `kill(2)',  but  `pid'  must  be positive  and  reference  a  process's  PID,
@@meaning that this function can only be used to send a signal to single, specific process.
@@@param: pid:   The PID of the process that shall receive the signal.
@@@param: signo: The signal number to deliver. When set to `0', no signal is  delivered,
@@               and this function can be used to test if the caller would be allowed to
@@               send signals to the process(es) specified by `pid'
@@@param: val:   An additional value to pass alongside the signal itself. This value can
@@               read as `info->si_value' from within a 3-arg signal handler established
@@               by `pid', or  may also be  returned by a  call to `sigwaitinfo(2)'  and
@@               friends made by `pid'.
@@@return: 0:    Success
@@@return: -1:   [errno=EINVAL] The given `signo' is invalid
@@@return: -1:   [errno=EPERM]  The caller does not have permission to send signals to `pid'
@@@return: -1:   [errno=ESRCH]  No process is identified by `pid'
[[decl_include("<bits/types.h>", "<bits/os/sigval.h>")]]
int sigqueue($pid_t pid, $signo_t signo, union sigval const val);

%#ifdef __USE_TIME64

[[preferred_time64_variant_of(sigtimedwait), doc_alias("sigtimedwait")]]
[[cp, userimpl, requires_function(sigtimedwait32)]]
[[decl_include("<bits/os/siginfo.h>", "<bits/os/timespec.h>")]]
int sigtimedwait64([[in]] $sigset_t const *__restrict set,
                   [[out_opt]] siginfo_t *__restrict info,
                   [[in_opt]] struct timespec64 const *rel_timeout) {
	struct timespec32 tmv;
	if (!rel_timeout)
		return sigtimedwait32(set, info, NULL);
	tmv.tv_sec  = (__time32_t)rel_timeout->tv_sec;
	tmv.tv_nsec = rel_timeout->tv_nsec;
	return sigtimedwait32(set, info, NULL);
}

%#endif /* __USE_TIME64 */
%#endif /* __USE_POSIX199309 */
%#endif /* __USE_POSIX */

%
%#ifdef __USE_KOS
@@>> sigqueueinfo(2)
@@Similar to  `sigqueue(2)',  but  instead  of  only being  able  to  specify  a  custom
@@signal  value, everything  about signal meta-data  can be specified  by this function.
@@Note however  that  various privileges  are  required  to provide  custom  values  for
@@different values of `uinfo' that don't match what the equivalent call to `sigqueue(2)'
@@would have used.
@@@param: pid:   The PID of the process that shall receive the signal.
@@@param: signo: The signal number to deliver. When set to `0', no signal is  delivered,
@@               and this function can be used to test if the caller would be allowed to
@@               send signals to the process(es) specified by `pid'
@@@param: uinfo: Signal information to pass alongside the signal itself.
@@@return: 0:    Success
@@@return: -1:   [errno=EINVAL] The given `signo' is invalid
@@@return: -1:   [errno=EINVAL] The given `signo' doesn't match `uinfo->si_signo'
@@@return: -1:   [errno=EPERM]  The caller does not have permission to send signals to `pid'
@@@return: -1:   [errno=EPERM]  `info->si_code' is invalid, and `pid' is a different process
@@@return: -1:   [errno=ESRCH]  No process is identified by `pid'
[[decl_include("<bits/types.h>", "<bits/os/siginfo.h>")]]
int sigqueueinfo($pid_t pid, $signo_t signo,
                 [[in]] siginfo_t const *uinfo);

@@>> tgsigqueueinfo(2)
@@Similar  to `sigqueueinfo(2)', rather than sending a signal to a process
@@as a whole, only send the signal to a single thread within that process.
@@@param: pid:   The PID of the process that shall receive the signal.
@@@param: signo: The signal number to deliver. When set to `0', no signal is  delivered,
@@               and this function can be used to test if the caller would be allowed to
@@               send signals to the process(es) specified by `pid'
@@@param: uinfo: Signal information to pass alongside the signal itself.
@@@return: 0:    Success
@@@return: -1:   [errno=EINVAL] The given `signo' is invalid
@@@return: -1:   [errno=EINVAL] The given `signo' doesn't match `uinfo->si_signo'
@@@return: -1:   [errno=EPERM]  The caller does not have permission to send signals to `pid'
@@@return: -1:   [errno=EPERM]  `info->si_code' is invalid, and `pid' is a different process
@@@return: -1:   [errno=ESRCH]  No process is identified by `pid'
[[decl_include("<bits/types.h>", "<bits/os/siginfo.h>")]]
int tgsigqueueinfo($pid_t pid, $pid_t tid, $signo_t signo,
                   [[in]] siginfo_t const *uinfo);
%#endif /* __USE_KOS */

%
%#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
@@>> killpg(3)
@@Alias for `kill(-pgrp, signo)'
@@@param: signo: The signal number to deliver. When set to `0', no signal is  delivered,
@@               and this function can be used to test if the caller would be allowed to
@@               send signals to the process(es) specified by `pid'
@@@return: 0:    Success
@@@return: -1:   [errno=EINVAL] The given `signo' is invalid
@@@return: -1:   [errno=EPERM]  The caller does not have permission to send signals to `pgrp'
@@@return: -1:   [errno=ESRCH]  No process group is identified by `pgrp'
[[decl_include("<bits/types.h>"), requires_function(kill)]]
int killpg($pid_t pgrp, $signo_t signo) {
	return kill(-pgrp, signo);
}
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

%
%#ifdef __USE_XOPEN2K8
@@>> psignal(3)
@@Same as `fprintf(stderr, "%s: %s\n", s, sigabbrev_np(signo) ? "SIG"+. : strdupf("Unknown signal %d", signo))'
@@When `s' is `NULL' or an empty string, omit the leading "%s: " from the format.
[[guard, decl_include("<bits/types.h>")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires(defined(__LOCAL_stderr) && $has_function(fprintf))]]
void psignal($signo_t signo, [[nullable]] char const *s) {
	char const *signam = sigabbrev_np(signo);
	if (s && *s)
		fprintf(stderr, "%s: ", s);
	if (signam) {
		fprintf(stderr, "SIG%s\n", signam);
	} else {
		fprintf(stderr, "Unknown signal %d\n", signo);
	}
}

@@>> psiginfo(3)
@@Similar to `psignal(3)', but instead print extended signal information from `*pinfo'
[[decl_include("<bits/os/siginfo.h>")]]
[[impl_include("<asm/os/signal.h>")]]
[[impl_include("<bits/crt/inttypes.h>")]]
[[impl_include("<bits/types.h>")]]
[[guard, requires_include("<libc/template/stdstreams.h>")]]
[[requires(defined(__LOCAL_stderr) && $has_function(fprintf))]]
void psiginfo([[in]] siginfo_t const *pinfo,
              [[in_opt]] char const *s) {
	char const *text;
	text = sigabbrev_np(pinfo->@si_signo@);
	if (s && *s)
		fprintf(stderr, "%s: ", s);
	if (text) {
		fprintf(stderr, "SIG%s (", text);
@@pp_if defined(__SIGRTMIN) && defined(__SIGRTMAX)@@
	} else if (pinfo->@si_signo@ >= __SIGRTMIN &&
	           pinfo->@si_signo@ <= __SIGRTMAX) {
		unsigned int offset;
		offset = (unsigned int)(pinfo->@si_signo@ - __SIGRTMIN);
		if (offset != 0) {
			fprintf(stderr, "SIGRTMIN+%u (", offset);
		} else {
			fprintf(stderr, "SIGRTMIN (");
		}
@@pp_endif@@
	} else {
		fprintf(stderr, "Unknown signal %d (", pinfo->@si_signo@);
	}
	text = sigcodedesc_np(pinfo->@si_signo@, pinfo->@si_code@);
	if (text) {
		fprintf(stderr, "%s ", text);
	} else {
		fprintf(stderr, "%u ", (unsigned int)pinfo->@si_code@);
	}
@@pp_if defined(__SIGILL) || defined(__SIGFPE) || defined(__SIGSEGV) || defined(__SIGBUS)@@
	if (0
@@pp_ifdef __SIGILL@@
	    || pinfo->@si_signo@ == __SIGILL
@@pp_endif@@
@@pp_ifdef __SIGFPE@@
	    || pinfo->@si_signo@ == __SIGFPE
@@pp_endif@@
@@pp_ifdef __SIGSEGV@@
	    || pinfo->@si_signo@ == __SIGSEGV
@@pp_endif@@
@@pp_ifdef __SIGBUS@@
	    || pinfo->@si_signo@ == __SIGBUS
@@pp_endif@@
	    ) {
		fprintf(stderr, "[%p])\n", pinfo->@si_addr@);
	} else
@@pp_endif@@
@@pp_ifdef __SIGCHLD@@
	if (pinfo->@si_signo@ == __SIGCHLD) {
		fprintf(stderr,
		        "%" __PRIN_PREFIX(__SIZEOF_PID_T__) "d %d "
		        "%" __PRIN_PREFIX(__SIZEOF_UID_T__) "d)\n",
		        (pid_t)pinfo->@si_pid@,
		        (int)pinfo->@si_status@,
		        (uid_t)pinfo->@si_uid@);
	} else
@@pp_endif@@
@@pp_ifdef __SIGPOLL@@
	if (pinfo->@si_signo@ == __SIGPOLL) {
		fprintf(stderr, "%" __PRIN_PREFIX(__SIZEOF_POINTER__) "d)\n",
		        (longptr_t)pinfo->@si_band@);
	} else
@@pp_endif@@
	{
		fprintf(stderr,
		        "%" __PRIN_PREFIX(__SIZEOF_PID_T__) "d "
		        "%" __PRIN_PREFIX(__SIZEOF_UID_T__) "d)\n",
		        (pid_t)pinfo->@si_pid@,
		        (uid_t)pinfo->@si_uid@);
	}
}

%#ifdef __USE_KOS
@@>> sigcodename_np(3)
@@Return a name of `code', as read from `siginfo_t::si_code',
@@and used  in  conjunction  with  a  given  signal  `signo'.
@@e.g.   `sigcodename_np(SIGILL, ILL_ILLOPC) -> "ILL_ILLOPC"'
[[kernel, const, wunused, decl_include("<bits/types.h>")]]
[[impl_include("<asm/os/signal.h>", "<asm/os/siginfo.h>")]]
char const *sigcodename_np($signo_t signo, int code) {
	char const *result = NULL;
/*[[[deemon
import util;
import * from deemon;
import * from ....misc.libgen.strendN;

@@List of (name: string, comment: string, kosCode: int)
@@For example: ("__POLL_IN", "Data input available", 1)
global signalCodes: {(string, string, int)...} = [];
for (local l: File.open("../../../include/asm/os/kos/siginfo.h", "r")) {
	l = l.strip().decode("utf-8");
	local name, code, comment;
	try {
		name, code, comment = l.scanf("# define %[^ ] %[^/]/" "* %[^*]")...;
		code    = getMacroIntValue(code.strip());
		comment = comment.strip().rstrip(".").rstrip();
	} catch (...) {
		continue;
	}
	signalCodes.append((name, code, comment));
}


global CODED_SIGNALS: {(string, string)...} = {
	("SIGILL", "__ILL_"),
	("SIGFPE", "__FPE_"),
	("SIGSEGV", "__SEGV_"),
	("SIGBUS", "__BUS_"),
	("SIGTRAP", "__TRAP_"),
	("SIGCHLD", "__CLD_"),
	("SIGPOLL", "__POLL_"),
};

print("@@pp_if defined(__KOS__) || defined(__linux__)@@");
function printSigCodeSelector(prefix: string) {
	local codes = [];
	for (local name, code, comment: signalCodes) {
		if (!name.startswith(prefix))
			continue;
		if (code < 0)
			code = code.unsigned8;
		if (code >= #codes)
			codes.resize(code + 1);
		codes[code] = name.lstrip("_") + "\0" + comment;
	}
	local partitions: {(int, {string...})...} = splitValues(codes);
	local isFirst = true;
	for (local minIndex, items: partitions) {
		local maxIndex = minIndex + #items - 1;
		if (isFirst) {
			print("		"),;
			isFirst = false;
		} else {
			print(" else "),;
		}
		print("if ("),;
		if (minIndex == maxIndex) {
			print("(unsigned int)code == ", minIndex.hex()),;
		} else if (minIndex == 0) {
			print("(unsigned int)code <= ", maxIndex.hex()),;
		} else {
			print("(unsigned int)code >= ", minIndex.hex(), " && "
			      "(unsigned int)code <= ", maxIndex.hex()),;
		}
		print(") {");
		if (minIndex == maxIndex) {
			print("			result = ", repr(items.first), ";");
			print("			code   = 0;");
		} else {
			local reprName = "repr_" + prefix.strip("_").lower();
			File.Writer text;
			for (local i, item: util.enumerate(items)) {
				if (!item)
					item = "\0";
				if (i != #items - 1)
					item = item + "\0";
				text << item;
			}
			print("			static char const ", reprName, "[] =\n			",
				"\n			".join(for (local e: text.string.segments(64)) repr(e)),
				";");
			print("			result = ", reprName, ";");
			if (minIndex)
				print("			code -= ", minIndex.hex(), ";");
		}
		print("		}"),;
	}
	print;
}
print("	switch (signo) {");
for (local signo_name, prefix: CODED_SIGNALS) {
	print("	case __", signo_name, ":");
	printSigCodeSelector(prefix);
	print("		break;");
	print;
}
print("	default:");
print("		code = (unsigned int)code & 0xff;");
printSigCodeSelector("__SI_");
print("		break;");
print("	}");
print("	if (result) {");
print("		for (code *= 2; code; --code)");
print("			result = strend(result) + 1;");
print("		if (!*result)");
print("			result = NULL;");
print("	}");
print("@@pp_else@@");
function printFallbackSigCodeSelector(prefix: string) {
	print("		switch (code) {");
	for (local name, code, comment: signalCodes) {
		if (!name.startswith(prefix))
			continue;
		print("@@pp_ifdef ", name, "@@");
		print("		case ", name, ": result = ", repr(name.lstrip("_") + "\0" + comment), "; break;");
		print("@@pp_endif@@");
	}
	print("		default: break;");
	print("		}");
}
print("	switch (signo) {");
print;
for (local signo_name, prefix: CODED_SIGNALS) {
	print("@@pp_ifdef __", signo_name, "@@");
	print("	case __", signo_name, ":");
	printFallbackSigCodeSelector(prefix);
	print("		break;");
	print("@@pp_endif@@");
	print;
}
print("	default:");
printFallbackSigCodeSelector("__SI_");
print("		break;");
print("	}");
print("@@pp_endif@@");
]]]*/
@@pp_if defined(__KOS__) || defined(__linux__)@@
	switch (signo) {
	case __SIGILL:
		if ((unsigned int)code <= 0x8) {
			static char const repr_ill[] =
			"\0\0ILL_ILLOPC\0Illegal opcode\0ILL_ILLOPN\0Illegal operand\0ILL_ILLAD"
			"R\0Illegal addressing mode\0ILL_ILLTRP\0Illegal trap\0ILL_PRVOPC\0Pri"
			"vileged opcode\0ILL_PRVREG\0Privileged register\0ILL_COPROC\0Coproce"
			"ssor error\0ILL_BADSTK\0Internal stack error";
			result = repr_ill;
		}
		break;

	case __SIGFPE:
		if ((unsigned int)code <= 0x8) {
			static char const repr_fpe[] =
			"\0\0FPE_INTDIV\0Integer divide by zero\0FPE_INTOVF\0Integer overflow\0"
			"FPE_FLTDIV\0Floating point divide by zero\0FPE_FLTOVF\0Floating poi"
			"nt overflow\0FPE_FLTUND\0Floating point underflow\0FPE_FLTRES\0Float"
			"ing point inexact result\0FPE_FLTINV\0Floating point invalid opera"
			"tion\0FPE_FLTSUB\0Subscript out of range";
			result = repr_fpe;
		}
		break;

	case __SIGSEGV:
		if ((unsigned int)code <= 0x2) {
			static char const repr_segv[] =
			"\0\0SEGV_MAPERR\0Address not mapped to object\0SEGV_ACCERR\0Invalid p"
			"ermissions for mapped object";
			result = repr_segv;
		}
		break;

	case __SIGBUS:
		if ((unsigned int)code <= 0x5) {
			static char const repr_bus[] =
			"\0\0BUS_ADRALN\0Invalid address alignment\0BUS_ADRERR\0Non-existent p"
			"hysical address\0BUS_OBJERR\0Object specific hardware error\0BUS_MC"
			"EERR_AR\0Hardware memory error: action required\0BUS_MCEERR_AO\0Har"
			"dware memory error: action optional";
			result = repr_bus;
		}
		break;

	case __SIGTRAP:
		if ((unsigned int)code <= 0x2) {
			static char const repr_trap[] =
			"\0\0TRAP_BRKPT\0Process breakpoint\0TRAP_TRACE\0Process trace trap";
			result = repr_trap;
		}
		break;

	case __SIGCHLD:
		if ((unsigned int)code <= 0x6) {
			static char const repr_cld[] =
			"\0\0CLD_EXITED\0Child has exited\0CLD_KILLED\0Child was killed\0CLD_DU"
			"MPED\0Child terminated abnormally\0CLD_TRAPPED\0Traced child has tr"
			"apped\0CLD_STOPPED\0Child has stopped\0CLD_CONTINUED\0Stopped child "
			"has continued";
			result = repr_cld;
		}
		break;

	case __SIGPOLL:
		if ((unsigned int)code <= 0x6) {
			static char const repr_poll[] =
			"\0\0POLL_IN\0Data input available\0POLL_OUT\0Output buffers available"
			"\0POLL_MSG\0Input message available\0POLL_ERR\0I/O error\0POLL_PRI\0Hi"
			"gh priority input available\0POLL_HUP\0Device disconnected";
			result = repr_poll;
		}
		break;

	default:
		code = (unsigned int)code & 0xff;
		if ((unsigned int)code == 0x0) {
			result = "SI_USER\0Sent by kill, sigsend";
			code   = 0;
		} else if ((unsigned int)code == 0x80) {
			result = "SI_KERNEL\0Send by kernel";
			code   = 0;
		} else if ((unsigned int)code == 0xc4) {
			result = "SI_ASYNCNL\0Sent by asynch name lookup completion";
			code   = 0;
		} else if ((unsigned int)code >= 0xfa && (unsigned int)code <= 0xff) {
			static char const repr_si[] =
			"SI_TKILL\0Sent by tkill\0SI_SIGIO\0Sent by queued SIGIO\0SI_ASYNCIO\0"
			"Sent by AIO completion\0SI_MESGQ\0Sent by real time mesq state cha"
			"nge\0SI_TIMER\0Sent by timer expiration\0SI_QUEUE\0Sent by sigqueue";
			result = repr_si;
			code -= 0xfa;
		}
		break;
	}
	if (result) {
		for (code *= 2; code; --code)
			result = strend(result) + 1;
		if (!*result)
			result = NULL;
	}
@@pp_else@@
	switch (signo) {

@@pp_ifdef __SIGILL@@
	case __SIGILL:
		switch (code) {
@@pp_ifdef __ILL_ILLOPC@@
		case __ILL_ILLOPC: result = "ILL_ILLOPC\0Illegal opcode"; break;
@@pp_endif@@
@@pp_ifdef __ILL_ILLOPN@@
		case __ILL_ILLOPN: result = "ILL_ILLOPN\0Illegal operand"; break;
@@pp_endif@@
@@pp_ifdef __ILL_ILLADR@@
		case __ILL_ILLADR: result = "ILL_ILLADR\0Illegal addressing mode"; break;
@@pp_endif@@
@@pp_ifdef __ILL_ILLTRP@@
		case __ILL_ILLTRP: result = "ILL_ILLTRP\0Illegal trap"; break;
@@pp_endif@@
@@pp_ifdef __ILL_PRVOPC@@
		case __ILL_PRVOPC: result = "ILL_PRVOPC\0Privileged opcode"; break;
@@pp_endif@@
@@pp_ifdef __ILL_PRVREG@@
		case __ILL_PRVREG: result = "ILL_PRVREG\0Privileged register"; break;
@@pp_endif@@
@@pp_ifdef __ILL_COPROC@@
		case __ILL_COPROC: result = "ILL_COPROC\0Coprocessor error"; break;
@@pp_endif@@
@@pp_ifdef __ILL_BADSTK@@
		case __ILL_BADSTK: result = "ILL_BADSTK\0Internal stack error"; break;
@@pp_endif@@
		default: break;
		}
		break;
@@pp_endif@@

@@pp_ifdef __SIGFPE@@
	case __SIGFPE:
		switch (code) {
@@pp_ifdef __FPE_INTDIV@@
		case __FPE_INTDIV: result = "FPE_INTDIV\0Integer divide by zero"; break;
@@pp_endif@@
@@pp_ifdef __FPE_INTOVF@@
		case __FPE_INTOVF: result = "FPE_INTOVF\0Integer overflow"; break;
@@pp_endif@@
@@pp_ifdef __FPE_FLTDIV@@
		case __FPE_FLTDIV: result = "FPE_FLTDIV\0Floating point divide by zero"; break;
@@pp_endif@@
@@pp_ifdef __FPE_FLTOVF@@
		case __FPE_FLTOVF: result = "FPE_FLTOVF\0Floating point overflow"; break;
@@pp_endif@@
@@pp_ifdef __FPE_FLTUND@@
		case __FPE_FLTUND: result = "FPE_FLTUND\0Floating point underflow"; break;
@@pp_endif@@
@@pp_ifdef __FPE_FLTRES@@
		case __FPE_FLTRES: result = "FPE_FLTRES\0Floating point inexact result"; break;
@@pp_endif@@
@@pp_ifdef __FPE_FLTINV@@
		case __FPE_FLTINV: result = "FPE_FLTINV\0Floating point invalid operation"; break;
@@pp_endif@@
@@pp_ifdef __FPE_FLTSUB@@
		case __FPE_FLTSUB: result = "FPE_FLTSUB\0Subscript out of range"; break;
@@pp_endif@@
		default: break;
		}
		break;
@@pp_endif@@

@@pp_ifdef __SIGSEGV@@
	case __SIGSEGV:
		switch (code) {
@@pp_ifdef __SEGV_MAPERR@@
		case __SEGV_MAPERR: result = "SEGV_MAPERR\0Address not mapped to object"; break;
@@pp_endif@@
@@pp_ifdef __SEGV_ACCERR@@
		case __SEGV_ACCERR: result = "SEGV_ACCERR\0Invalid permissions for mapped object"; break;
@@pp_endif@@
		default: break;
		}
		break;
@@pp_endif@@

@@pp_ifdef __SIGBUS@@
	case __SIGBUS:
		switch (code) {
@@pp_ifdef __BUS_ADRALN@@
		case __BUS_ADRALN: result = "BUS_ADRALN\0Invalid address alignment"; break;
@@pp_endif@@
@@pp_ifdef __BUS_ADRERR@@
		case __BUS_ADRERR: result = "BUS_ADRERR\0Non-existent physical address"; break;
@@pp_endif@@
@@pp_ifdef __BUS_OBJERR@@
		case __BUS_OBJERR: result = "BUS_OBJERR\0Object specific hardware error"; break;
@@pp_endif@@
@@pp_ifdef __BUS_MCEERR_AR@@
		case __BUS_MCEERR_AR: result = "BUS_MCEERR_AR\0Hardware memory error: action required"; break;
@@pp_endif@@
@@pp_ifdef __BUS_MCEERR_AO@@
		case __BUS_MCEERR_AO: result = "BUS_MCEERR_AO\0Hardware memory error: action optional"; break;
@@pp_endif@@
		default: break;
		}
		break;
@@pp_endif@@

@@pp_ifdef __SIGTRAP@@
	case __SIGTRAP:
		switch (code) {
@@pp_ifdef __TRAP_BRKPT@@
		case __TRAP_BRKPT: result = "TRAP_BRKPT\0Process breakpoint"; break;
@@pp_endif@@
@@pp_ifdef __TRAP_TRACE@@
		case __TRAP_TRACE: result = "TRAP_TRACE\0Process trace trap"; break;
@@pp_endif@@
		default: break;
		}
		break;
@@pp_endif@@

@@pp_ifdef __SIGCHLD@@
	case __SIGCHLD:
		switch (code) {
@@pp_ifdef __CLD_EXITED@@
		case __CLD_EXITED: result = "CLD_EXITED\0Child has exited"; break;
@@pp_endif@@
@@pp_ifdef __CLD_KILLED@@
		case __CLD_KILLED: result = "CLD_KILLED\0Child was killed"; break;
@@pp_endif@@
@@pp_ifdef __CLD_DUMPED@@
		case __CLD_DUMPED: result = "CLD_DUMPED\0Child terminated abnormally"; break;
@@pp_endif@@
@@pp_ifdef __CLD_TRAPPED@@
		case __CLD_TRAPPED: result = "CLD_TRAPPED\0Traced child has trapped"; break;
@@pp_endif@@
@@pp_ifdef __CLD_STOPPED@@
		case __CLD_STOPPED: result = "CLD_STOPPED\0Child has stopped"; break;
@@pp_endif@@
@@pp_ifdef __CLD_CONTINUED@@
		case __CLD_CONTINUED: result = "CLD_CONTINUED\0Stopped child has continued"; break;
@@pp_endif@@
		default: break;
		}
		break;
@@pp_endif@@

@@pp_ifdef __SIGPOLL@@
	case __SIGPOLL:
		switch (code) {
@@pp_ifdef __POLL_IN@@
		case __POLL_IN: result = "POLL_IN\0Data input available"; break;
@@pp_endif@@
@@pp_ifdef __POLL_OUT@@
		case __POLL_OUT: result = "POLL_OUT\0Output buffers available"; break;
@@pp_endif@@
@@pp_ifdef __POLL_MSG@@
		case __POLL_MSG: result = "POLL_MSG\0Input message available"; break;
@@pp_endif@@
@@pp_ifdef __POLL_ERR@@
		case __POLL_ERR: result = "POLL_ERR\0I/O error"; break;
@@pp_endif@@
@@pp_ifdef __POLL_PRI@@
		case __POLL_PRI: result = "POLL_PRI\0High priority input available"; break;
@@pp_endif@@
@@pp_ifdef __POLL_HUP@@
		case __POLL_HUP: result = "POLL_HUP\0Device disconnected"; break;
@@pp_endif@@
		default: break;
		}
		break;
@@pp_endif@@

	default:
		switch (code) {
@@pp_ifdef __SI_ASYNCNL@@
		case __SI_ASYNCNL: result = "SI_ASYNCNL\0Sent by asynch name lookup completion"; break;
@@pp_endif@@
@@pp_ifdef __SI_TKILL@@
		case __SI_TKILL: result = "SI_TKILL\0Sent by tkill"; break;
@@pp_endif@@
@@pp_ifdef __SI_SIGIO@@
		case __SI_SIGIO: result = "SI_SIGIO\0Sent by queued SIGIO"; break;
@@pp_endif@@
@@pp_ifdef __SI_ASYNCIO@@
		case __SI_ASYNCIO: result = "SI_ASYNCIO\0Sent by AIO completion"; break;
@@pp_endif@@
@@pp_ifdef __SI_MESGQ@@
		case __SI_MESGQ: result = "SI_MESGQ\0Sent by real time mesq state change"; break;
@@pp_endif@@
@@pp_ifdef __SI_TIMER@@
		case __SI_TIMER: result = "SI_TIMER\0Sent by timer expiration"; break;
@@pp_endif@@
@@pp_ifdef __SI_QUEUE@@
		case __SI_QUEUE: result = "SI_QUEUE\0Sent by sigqueue"; break;
@@pp_endif@@
@@pp_ifdef __SI_USER@@
		case __SI_USER: result = "SI_USER\0Sent by kill, sigsend"; break;
@@pp_endif@@
@@pp_ifdef __SI_KERNEL@@
		case __SI_KERNEL: result = "SI_KERNEL\0Send by kernel"; break;
@@pp_endif@@
		default: break;
		}
		break;
	}
@@pp_endif@@
/*[[[end]]]*/
	return result;
}

@@>> sigcodedesc_np(3)
@@Return a textual description of `code', as read from `siginfo_t::si_code',
@@and used in conjunction with a given signal `signo'. This function is used
@@for the implementation of `psiginfo(3)'
[[kernel, const, wunused, decl_include("<bits/types.h>")]]
[[requires_function(sigcodename_np)]]
char const *sigcodedesc_np($signo_t signo, int code) {
	char const *result = sigcodename_np(signo, code);
	if (result)
		result = strend(result) + 1;
	return result;
}

%#endif /* __USE_KOS */
%#endif /* __USE_XOPEN2K8 */

%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
@@>> siginterrupt(3)
@@Set the `SA_RESTART' of the already-established signal handler for `signo',
@@as well as cause any future handler established by `bsd_signal()' or one of
@@its aliases to immediately be established with `SA_RESTART' set/cleared
@@@param: interrupt: When == 0: clear `SA_RESTART' for the signal handler of `signo'
@@                   When != 0: set `SA_RESTART'  for the signal handler of  `signo'
@@@return: 0:  Success
@@@return: -1: [errno=EINVAL] The given `signo' is invalid
[[decl_include("<features.h>", "<bits/types.h>")]]
int siginterrupt($signo_t signo, __STDC_INT_AS_UINT_T interrupt);

@@>> sigstack(2)
@@Deprecated, and slightly different version of `sigaltstack(2)'
@@@return: 0:  Success
@@@return: -1: Error (s.a. `errno')
[[decl_include("<bits/os/sigstack.h>")]]
[[impl_include("<asm/os/signal.h>", "<bits/os/sigstack.h>")]]
[[requires_include("<asm/os/signal.h>")]]
[[requires(defined(@__SS_ONSTACK@) && defined(@__SS_DISABLE@) &&
           $has_function(sigaltstack))]]
int sigstack([[in_opt]] struct sigstack const *ss,
             [[out_opt]] struct sigstack *oss) {
	struct @sigaltstack@ ass, aoss;
	int result;
	if (ss) {
		ass.@ss_flags@ = ss->@ss_onstack@
		                 ? @__SS_ONSTACK@
		                 : @__SS_DISABLE@;
		ass.@ss_sp@   = ss->@ss_sp@;
		ass.@ss_size@ = (size_t)-1;
	}
	result = sigaltstack(ss ? &ass : NULL,
	                     oss ? &aoss : NULL);
	if (likely(!result) && oss) {
		oss->@ss_onstack@ = !!(aoss.@ss_flags@ & @__SS_ONSTACK@);
		oss->@ss_sp@      = aoss.@ss_sp@;
	}
	return result;
}


@@>> sigaltstack(2)
@@Get/Set the alternate signal stack for the calling thread. When set,
@@the alternate signal stack can be used to host signal handlers  that
@@have been established with the `SA_ONSTACK' flag in `sa_flags'.
@@@return: 0:  Success
@@@return: -1: Error (s.a. `errno')
[[decl_include("<bits/os/sigstack.h>")]]
int sigaltstack([[in_opt]] struct sigaltstack const *ss,
                [[out_opt]] struct sigaltstack *oss);
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

%
%#ifdef __USE_XOPEN_EXTENDED

[[static, requires_function(sigprocmask)]]
int set_single_signal_masked(int sig, int how) {
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, sig);
	return sigprocmask(how, &set, NULL);
}


@@>> sighold(3)
@@Mask a single signal  `signo', which is the  same
@@as `sigprocmask(SIG_BLOCK, MASKFOR(signo), NULL)'
@@@return: 0:  Success
@@@return: -1: Error (s.a. `errno')
[[decl_include("<bits/types.h>"), impl_include("<asm/os/signal.h>")]]
[[requires_include("<asm/os/signal.h>")]]
[[requires(defined(@__SIG_BLOCK@) && $has_function(set_single_signal_masked))]]
int sighold($signo_t signo) {
	return set_single_signal_masked(signo, @__SIG_BLOCK@);
}

@@>> sighold(3)
@@Unmask a single signal  `signo', which is the  same
@@as `sigprocmask(SIG_UNBLOCK, MASKFOR(signo), NULL)'
@@@return: 0:  Success
@@@return: -1: Error (s.a. `errno')
[[decl_include("<bits/types.h>"), impl_include("<asm/os/signal.h>")]]
[[requires_include("<asm/os/signal.h>")]]
[[requires(defined(@__SIG_UNBLOCK@) && $has_function(set_single_signal_masked))]]
int sigrelse($signo_t signo) {
	return set_single_signal_masked(signo, @__SIG_UNBLOCK@);
}

@@>> sigignore(3)
@@Change the disposition of `signo' to `SIG_IGN' using `bsd_signal(3)'
@@@return: 0:  Success
@@@return: -1: Error (s.a. `errno')
[[decl_include("<bits/types.h>"), impl_include("<asm/os/signal.h>")]]
[[requires_include("<asm/os/signal.h>")]]
[[requires(defined(@__SIG_IGN@) && defined(@__SIG_ERR@) &&
           $has_function(bsd_signal))]]
int sigignore($signo_t signo) {
	return bsd_signal(signo, (sighandler_t)@__SIG_IGN@) == (sighandler_t)@__SIG_ERR@ ? -1 : 0;
}

@@>> sigset(3)
@@Set the handler of `signo'  to `disp', or add `signo'  to
@@the calling threads's signal mask when `disp == SIG_HOLD'
@@@return: 0:  Success
@@@return: -1: Error (s.a. `errno')
[[impl_include("<libc/errno.h>", "<asm/os/signal.h>", "<bits/os/sigaction.h>")]]
[[requires_include("<asm/os/signal.h>"), decl_include("<bits/types.h>")]]
[[requires(defined(@__SIG_ERR@) && defined(@__SIG_HOLD@) &&
           defined(@__SIG_BLOCK@) && $has_function(sigprocmask) &&
           $has_function(sigaction))]]
$sighandler_t sigset($signo_t signo, $sighandler_t disp) {
	struct @sigaction@ act, oact;
	sigset_t set, oset;
	if unlikely(disp == (sighandler_t)@__SIG_ERR@)
		goto err_inval;
	sigemptyset(&set);
	sigaddset(&set, signo);
	if (disp == (sighandler_t)@__SIG_HOLD@) {
		if unlikely(sigprocmask(@__SIG_BLOCK@, &set, &oset) != 0)
			goto err;
		if unlikely(sigismember(&oset, signo))
			goto err;
		if unlikely(sigaction(signo, NULL, &oact) != 0)
			goto err;
		return oact.@sa_handler@;
	}
	act.@sa_handler@ = disp;
	sigemptyset(&act.@sa_mask@);
	act.@sa_flags@ = 0;
	if unlikely(sigaction(signo, &act, &oact) != 0)
		goto err;
	if unlikely(sigprocmask(SIG_UNBLOCK, &set, &oset) != 0)
		goto err;
	return sigismember(&oset, signo)
	       ? (sighandler_t)@__SIG_HOLD@
	       : oact.@sa_handler@;
err_inval:
@@pp_ifdef EINVAL@@
	(void)libc_seterrno(EINVAL);
@@pp_else@@
	(void)libc_seterrno(1);
@@pp_endif@@
err:
	return (sighandler_t)@__SIG_ERR@;
}

%#endif /* __USE_XOPEN_EXTENDED */
%


[[hidden, wunused, decl_include("<bits/types.h>")]]
[[export_alias("__libc_allocate_rtsig_private")]]
$signo_t __libc_allocate_rtsig(int high);

[[const, wunused, decl_include("<bits/types.h>")]]
[[requires_include("<asm/os/signal.h>")]]
[[export_alias("__libc_current_sigrtmin_private")]]
[[userimpl, requires(defined(__SIGRTMIN))]]
$signo_t __libc_current_sigrtmin() {
	return __SIGRTMIN;
}

[[const, wunused, decl_include("<bits/types.h>")]]
[[requires_include("<asm/os/signal.h>")]]
[[userimpl, requires(defined(__SIGRTMAX))]]
[[export_alias("__libc_current_sigrtmax_private")]]
$signo_t __libc_current_sigrtmax() {
	return __SIGRTMAX;
}

%
%#if defined(__USE_POSIX199506) || defined(__USE_UNIX98)

@@>> pthread_sigmask(3)
@@Thread-safe version of `sigprocmask(2)'. Note though, that on
@@many systems (including KOS), this function behaves identical
@@to `sigprocmask()', though portable programs should still use
@@this function if they intend to use multiple threads.
@@@return: EOK:    Success
@@@return: EINVAL: Invalid `how'
[[guard, decl_include("<features.h>", "<bits/os/sigset.h>", "<bits/types.h>")]]
/* NOTE: Aliasing to `sigprocmask' breaks the meaning of return values, but
 *       while not 100% conforming, I  don't personally see any problem  in
 *       doing it this ways, especially  since the only possible error  can
 *       only happen as the result of improper API use of an argument  that
 *       will almost always simply have a fixed, constant value. */
[[nocrt, alias("pthread_sigmask", "thr_sigsetmask", "sigprocmask")]]
$errno_t pthread_sigmask(__STDC_INT_AS_UINT_T how,
                         [[in_opt]] $sigset_t const *newmask,
                         [[out_opt]] $sigset_t *oldmask);


@@>> pthread_kill(3)
@@Portable function for sending a signal to a specific `pthread' within one's own process.
@@@return: EOK:    Success
@@@return: EINVAL: The given `signo' is invalid
[[guard, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
[[export_alias("thr_kill")]]
$errno_t pthread_kill($pthread_t pthread, $signo_t signo);

%#ifdef __USE_GNU
@@>> pthread_sigqueue(3)
@@This function is for `pthread_kill(3)', what `sigqueue(2)' is for  `kill(2)',
@@in that it sends a signal to `pthread', alongside a custom signal value `val'
@@@param: signo: The signal number to deliver. When set to `0', no signal is  delivered,
@@               and this function can be used to test if the caller would be allowed to
@@               send signals to the process(es) specified by `pid'
@@@param: val:   An additional value to pass alongside the signal itself. This value can
@@               read as `info->si_value' from within a 3-arg signal handler established
@@               by `pid', or  may also be  returned by a  call to `sigwaitinfo(2)'  and
@@               friends made by `pid'.
@@@return: EOK:    Success
@@@return: EINVAL: The given `signo' is invalid
@@@return: ESRCH:  The given `pthread' has already terminated, and could no longer handle the signal
[[guard, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>", "<bits/os/sigval.h>")]]
$errno_t pthread_sigqueue($pthread_t pthread,
                          $signo_t signo,
                          union sigval const val);
%#endif /* __USE_GNU */

%#endif /* __USE_POSIX199506 || __USE_UNIX98 */

%{
#ifdef __USE_KOS
/* Initialize a `sigset_t' as empty:
 * >> static sigset_t myset = SIGSET_INIT_EMPTY; */
#define SIGSET_INIT_EMPTY __SIGSET_INIT(0)

/* Initialize a `sigset_t' as filled:
 * >> static sigset_t myset = SIGSET_INIT_FULL; */
#define SIGSET_INIT_FULL __SIGSET_INIT((__ULONGPTR_TYPE__)-1)
#endif /* __USE_KOS */
}


%
%/* Glibc function aliases originally found in <bits/sigset.h>
% * Because these don't violate namespacing rules, and because
% * <bits/sigset.h> is included unconditionally, we also define
% * these unconditionally! */
%
%[insert:function(__sigemptyset = sigemptyset)]
%[insert:function(__sigfillset = sigfillset)]
%#ifdef __USE_GNU
%[insert:function(__sigisemptyset = sigisemptyset)]
%[insert:function(__sigandset = sigandset)]
%[insert:function(__sigorset = sigorset)]
%#endif /* __USE_GNU */
%[insert:prefix(
DEFINE___PRIVATE_SIGSET_VALIDATE_SIGNO
)]
%[insert:function(__sigismember = sigismember)]
%[insert:function(__sigaddset = sigaddset)]
%[insert:function(__sigdelset = sigdelset)]

%{
/* These appear in Glibc under these  names, however these names collide  with
 * some escapes in a couple of places, so only define them when we're supposed
 * to emulate Glibc as closely as possible. */
#ifdef __USE_GLIBC_BLOAT
#undef __sigmask
#undef __sigword
/* Return the mask or index for a specific signal `sig' within some sigset. */
#define __sigmask(sig) __sigset_mask(sig)
#define __sigword(sig) __sigset_word(sig)
#endif /* __USE_GLIBC_BLOAT */
}


%
%#ifdef __USE_NETBSD
%[insert:function(signalname = sigabbrev_np)]

@@>> signalnumber(3)
@@Similar to `strtosigno(3)', however ignore any leading `SIG*'
@@prefix of `name', and  do a case-insensitive compare  between
@@the given `name', and the  signal's actual name. When  `name'
@@isn't recognized, return `0' instead.
@@This function also handles stuff like "SIGRTMIN+1" or "9"
[[pure, wunused, impl_include("<asm/os/signal.h>")]]
[[decl_include("<bits/types.h>")]]
$signo_t signalnumber([[in]] const char *name) {
	$signo_t result;

	/* Skip "SIG" prefix. */
	if ((name[0] == 'S' || name[0] == 's') &&
	    (name[1] == 'I' || name[1] == 'i') &&
	    (name[2] == 'G' || name[2] == 'g'))
		name += 3;

	/* Check for known signal names. */
	for (result = 1; result < __NSIG; ++result) {
		char const *s = sigabbrev_np(result);
		if (likely(s) && strcasecmp(name, s) == 0)
			return result;
	}

	/* Signal alias names. */
@@pp_ifdef __SIGCHLD@@
	if (strcasecmp(name, "CLD") == 0)
		return __SIGCHLD;
@@pp_endif@@
@@pp_ifdef __SIGRPC@@
	if (strcasecmp(name, "RPC") == 0)
		return __SIGRPC;
@@pp_endif@@
@@pp_ifdef __SIGPOLL@@
	if (strcasecmp(name, "POLL") == 0)
		return __SIGPOLL;
@@pp_endif@@

	/* SIGRT* with offset. e.g. "RTMIN+1", "RTMAX-1" */
@@pp_if defined(__SIGRTMIN) && defined(__SIGRTMAX)@@
	if (memcasecmp(name, "RTMIN+", 6 * sizeof(char)) == 0) {
		name += 6;
		result = __SIGRTMIN + (signo_t)strtou32(name, (char **)&name, 10);
return_rt_signal:
		if (*name != '\0' || (result < __SIGRTMIN || result > __SIGRTMAX))
			result = 0;
		return result;
	}
	if (memcasecmp(name, "RTMAX-", 6 * sizeof(char)) == 0) {
		name += 6;
		result = __SIGRTMAX - (signo_t)strtou32(name, (char **)&name, 10);
		goto return_rt_signal;
	}
@@pp_endif@@

	/* Special case: the signal number itself. */
	result = strtou32(name, (char **)&name, 10);
	if (*name != '\0' || (result <= 0 || result >= __NSIG))
		result = 0;
	return 0;
}

@@>> signalnext(3)
@@Return the next-greater signal number that comes after `signo'
@@When  no such signal number exists, return `0'. When the given
@@`signo' is `0', return the lowest valid signal number.
[[const, wunused, impl_include("<asm/os/signal.h>")]]
[[decl_include("<bits/types.h>")]]
$signo_t signalnext($signo_t signo) {
	if (signo >= (__NSIG - 1))
		return 0;
	return signo + 1;
}
%#endif /* __USE_NETBSD */


%
%#ifdef __USE_SOLARIS
%#define SIG2STR_MAX 32
%[define(SIG2STR_MAX = 32)]

@@>> sig2str(3)
@@Wrapper around  `sigabbrev_np(3)', that  also adds  additional
@@handling for `SIGRTMIN...`SIGRTMAX' signals, which are encoded
@@in a way that is compatible with `str2sig(3)'.
[[requires_function(sigabbrev_np)]]
[[decl_include("<bits/types.h>")]]
[[impl_include("<asm/os/signal.h>")]]
[[section(".text.crt{|.dos}.solaris")]]
int sig2str($signo_t signo, [[out]] char buf[SIG2STR_MAX]) {
	char const *name = sigabbrev_np(signo);
	if (name) {
		/* Predefined name. */
		strcpy(buf, name);
		return 0;
	}
@@pp_if defined(__SIGRTMIN) && defined(__SIGRTMAX)@@
	if (signo >= __SIGRTMIN && signo <= __SIGRTMAX) {
		/* Realtime . */
		sprintf(buf, "RTMIN+%u", (unsigned int)(signo - __SIGRTMIN));
		return 0;
	}
@@pp_endif@@
	return -1;
}

@@>> str2sig(3)
@@More restrictive version of `signalnumber(3)':
@@ - Requires all name-characters to be upper-case
@@ - Doesn't automatically remove any "SIG" prefix.
@@@return: 0 : Success; `*p_signo' was filled
@@@return: -1: Unrecognized `name' (`errno(3)' was _NOT_ modified)
[[decl_include("<bits/types.h>")]]
[[requires_function(signalnumber)]]
[[section(".text.crt{|.dos}.solaris")]]
int str2sig([[in]] const char *name, [[out]] $signo_t *p_signo) {
	$signo_t result;
	size_t i;
	if (name[0] == 'S' && name[1] == 'I' && name[2] == 'G')
		return -1;
	for (i = 0; name[i]; ++i) {
		if (islower(name[i]))
			return -1;
	}
	result = signalnumber(name);
	if (result != 0) {
		*p_signo = result;
		return 0;
	}
	return -1;
}

%#endif /* __USE_SOLARIS */


%
%#endif /* __CC__ */
%{

__SYSDECL_END

}
