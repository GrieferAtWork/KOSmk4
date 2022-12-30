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
/* (>) Standard: POSIX.2 (Issue 4, IEEE Std 1003.2-1992) */
/* (#) Portability: Cygwin        (/newlib/libc/include/sys/resource.h) */
/* (#) Portability: DJGPP         (/include/sys/resource.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/resource.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/resource.h) */
/* (#) Portability: FreeBSD       (/sys/sys/resource.h) */
/* (#) Portability: GNU C Library (/resource/sys/resource.h) */
/* (#) Portability: NetBSD        (/sys/sys/resource.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/sys/resource.h) */
/* (#) Portability: OpenBSD       (/sys/sys/resource.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/resource.h) */
/* (#) Portability: diet libc     (/include/sys/resource.h) */
/* (#) Portability: libc4/5       (/include/sys/resource.h) */
/* (#) Portability: mintlib       (/include/sys/resource.h) */
/* (#) Portability: musl libc     (/include/sys/resource.h) */
/* (#) Portability: uClibc        (/include/sys/resource.h) */
}

%[define_replacement(id_t = __id_t)]
%[default:section(".text.crt{|.dos}.sched.resource")]

%[define_decl_include("<bits/os/rlimit.h>": ["struct rlimit", "struct rlimit64"])]
%[define_decl_include("<bits/os/rusage.h>": ["struct rusage", "struct rusage64"])]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <asm/os/resource.h>
)]%[insert:prefix(
#include <bits/os/rlimit.h>  /* struct rlimit, struct rlimit64 */
)]%[insert:prefix(
#include <bits/os/rusage.h>  /* struct rusage, struct rusage64 */
)]%[insert:prefix(
#include <bits/os/timeval.h> /* struct timeval */
)]%[insert:prefix(
#include <bits/types.h>
)]%{


__SYSDECL_BEGIN

#if ((!defined(RLIMIT_CPU) && defined(__RLIMIT_CPU)) ||                                     \
     (!defined(RLIMIT_FSIZE) && defined(__RLIMIT_FSIZE)) ||                                 \
     (!defined(RLIMIT_DATA) && defined(__RLIMIT_DATA)) ||                                   \
     (!defined(RLIMIT_STACK) && defined(__RLIMIT_STACK)) ||                                 \
     (!defined(RLIMIT_CORE) && defined(__RLIMIT_CORE)) ||                                   \
     (!defined(RLIMIT_RSS) && defined(__RLIMIT_RSS)) ||                                     \
     (!defined(RLIMIT_NPROC) && defined(__RLIMIT_NPROC)) ||                                 \
     ((!defined(RLIMIT_NOFILE) || !defined(RLIMIT_OFILE)) && defined(__RLIMIT_NOFILE)) ||   \
     (!defined(RLIMIT_MEMLOCK) && defined(__RLIMIT_MEMLOCK)) ||                             \
     (!defined(RLIMIT_AS) && defined(__RLIMIT_AS)) ||                                       \
     (!defined(RLIMIT_LOCKS) && defined(__RLIMIT_LOCKS)) ||                                 \
     (!defined(RLIMIT_SIGPENDING) && defined(__RLIMIT_SIGPENDING)) ||                       \
     (!defined(RLIMIT_MSGQUEUE) && defined(__RLIMIT_MSGQUEUE)) ||                           \
     (!defined(RLIMIT_NICE) && defined(__RLIMIT_NICE)) ||                                   \
     (!defined(RLIMIT_RTPRIO) && defined(__RLIMIT_RTPRIO)) ||                               \
     (!defined(RLIMIT_RTTIME) && defined(__RLIMIT_RTTIME)) ||                               \
     ((!defined(RLIMIT_NLIMITS) || !defined(RLIM_NLIMITS)) && defined(__RLIMIT_NLIMITS)) || \
     (defined(__USE_KOS) && (!defined(RLIMIT_MAXFILE) && defined(__RLIMIT_MAXFILE))))
/* Kinds of resource limit. */
/*[[[enum]]]*/
#ifdef __CC__
enum __rlimit_resource {
#if !defined(RLIMIT_CPU) && defined(__RLIMIT_CPU)
	RLIMIT_CPU        = __RLIMIT_CPU,        /* ??? */
#endif /* !RLIMIT_CPU && __RLIMIT_CPU */
#if !defined(RLIMIT_FSIZE) && defined(__RLIMIT_FSIZE)
	RLIMIT_FSIZE      = __RLIMIT_FSIZE,      /* ??? */
#endif /* !RLIMIT_FSIZE && __RLIMIT_FSIZE */
#if !defined(RLIMIT_DATA) && defined(__RLIMIT_DATA)
	RLIMIT_DATA       = __RLIMIT_DATA,       /* ??? */
#endif /* !RLIMIT_DATA && __RLIMIT_DATA */
#if !defined(RLIMIT_STACK) && defined(__RLIMIT_STACK)
	RLIMIT_STACK      = __RLIMIT_STACK,      /* ??? */
#endif /* !RLIMIT_STACK && __RLIMIT_STACK */
#if !defined(RLIMIT_CORE) && defined(__RLIMIT_CORE)
	RLIMIT_CORE       = __RLIMIT_CORE,       /* ??? */
#endif /* !RLIMIT_CORE && __RLIMIT_CORE */
#if !defined(RLIMIT_RSS) && defined(__RLIMIT_RSS)
	RLIMIT_RSS        = __RLIMIT_RSS,        /* ??? */
#endif /* !RLIMIT_RSS && __RLIMIT_RSS */
#if !defined(RLIMIT_NPROC) && defined(__RLIMIT_NPROC)
	RLIMIT_NPROC      = __RLIMIT_NPROC,      /* ??? */
#endif /* !RLIMIT_NPROC && __RLIMIT_NPROC */
#if !defined(RLIMIT_NOFILE) && defined(__RLIMIT_NOFILE)
	RLIMIT_NOFILE     = __RLIMIT_NOFILE,     /* Max # of open file descriptors (total; does not affect greatest usable FD number) */
#endif /* !RLIMIT_NOFILE && __RLIMIT_NOFILE */
#if !defined(RLIMIT_OFILE) && defined(__RLIMIT_NOFILE)
	RLIMIT_OFILE      = __RLIMIT_NOFILE,     /* Max # of open file descriptors (total; does not affect greatest usable FD number) */
#endif /* !RLIMIT_OFILE && __RLIMIT_NOFILE */
#if !defined(RLIMIT_MEMLOCK) && defined(__RLIMIT_MEMLOCK)
	RLIMIT_MEMLOCK    = __RLIMIT_MEMLOCK,    /* ??? */
#endif /* !RLIMIT_MEMLOCK && __RLIMIT_MEMLOCK */
#if !defined(RLIMIT_AS) && defined(__RLIMIT_AS)
	RLIMIT_AS         = __RLIMIT_AS,         /* ??? */
#endif /* !RLIMIT_AS && __RLIMIT_AS */
#if !defined(RLIMIT_LOCKS) && defined(__RLIMIT_LOCKS)
	RLIMIT_LOCKS      = __RLIMIT_LOCKS,      /* ??? */
#endif /* !RLIMIT_LOCKS && __RLIMIT_LOCKS */
#if !defined(RLIMIT_SIGPENDING) && defined(__RLIMIT_SIGPENDING)
	RLIMIT_SIGPENDING = __RLIMIT_SIGPENDING, /* ??? */
#endif /* !RLIMIT_SIGPENDING && __RLIMIT_SIGPENDING */
#if !defined(RLIMIT_MSGQUEUE) && defined(__RLIMIT_MSGQUEUE)
	RLIMIT_MSGQUEUE   = __RLIMIT_MSGQUEUE,   /* ??? */
#endif /* !RLIMIT_MSGQUEUE && __RLIMIT_MSGQUEUE */
#if !defined(RLIMIT_NICE) && defined(__RLIMIT_NICE)
	RLIMIT_NICE       = __RLIMIT_NICE,       /* ??? */
#endif /* !RLIMIT_NICE && __RLIMIT_NICE */
#if !defined(RLIMIT_RTPRIO) && defined(__RLIMIT_RTPRIO)
	RLIMIT_RTPRIO     = __RLIMIT_RTPRIO,     /* ??? */
#endif /* !RLIMIT_RTPRIO && __RLIMIT_RTPRIO */
#if !defined(RLIMIT_RTTIME) && defined(__RLIMIT_RTTIME)
	RLIMIT_RTTIME     = __RLIMIT_RTTIME,     /* ??? */
#endif /* !RLIMIT_RTTIME && __RLIMIT_RTTIME */
#if !defined(RLIMIT_NLIMITS) && defined(__RLIMIT_NLIMITS)
	RLIMIT_NLIMITS    = __RLIMIT_NLIMITS,    /* Total # of (standard) resource limits */
#endif /* !RLIMIT_NLIMITS && __RLIMIT_NLIMITS */
#if !defined(RLIM_NLIMITS) && defined(__RLIMIT_NLIMITS)
	RLIM_NLIMITS      = __RLIMIT_NLIMITS,    /* Total # of (standard) resource limits */
#endif /* !RLIM_NLIMITS && __RLIMIT_NLIMITS */

	/* Extended resource limits (OS-specific) */
#if defined(__USE_KOS) && defined(__RLIMIT_MAXFILE)
	RLIMIT_MAXFILE    = __RLIMIT_MAXFILE,    /* greatest usable FD number */
#endif /* __USE_KOS && __RLIMIT_MAXFILE */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#if !defined(RLIMIT_CPU) && defined(__RLIMIT_CPU)
#define RLIMIT_CPU        RLIMIT_CPU        /* ??? */
#endif /* !RLIMIT_CPU && __RLIMIT_CPU */
#if !defined(RLIMIT_FSIZE) && defined(__RLIMIT_FSIZE)
#define RLIMIT_FSIZE      RLIMIT_FSIZE      /* ??? */
#endif /* !RLIMIT_FSIZE && __RLIMIT_FSIZE */
#if !defined(RLIMIT_DATA) && defined(__RLIMIT_DATA)
#define RLIMIT_DATA       RLIMIT_DATA       /* ??? */
#endif /* !RLIMIT_DATA && __RLIMIT_DATA */
#if !defined(RLIMIT_STACK) && defined(__RLIMIT_STACK)
#define RLIMIT_STACK      RLIMIT_STACK      /* ??? */
#endif /* !RLIMIT_STACK && __RLIMIT_STACK */
#if !defined(RLIMIT_CORE) && defined(__RLIMIT_CORE)
#define RLIMIT_CORE       RLIMIT_CORE       /* ??? */
#endif /* !RLIMIT_CORE && __RLIMIT_CORE */
#if !defined(RLIMIT_RSS) && defined(__RLIMIT_RSS)
#define RLIMIT_RSS        RLIMIT_RSS        /* ??? */
#endif /* !RLIMIT_RSS && __RLIMIT_RSS */
#if !defined(RLIMIT_NPROC) && defined(__RLIMIT_NPROC)
#define RLIMIT_NPROC      RLIMIT_NPROC      /* ??? */
#endif /* !RLIMIT_NPROC && __RLIMIT_NPROC */
#if !defined(RLIMIT_NOFILE) && defined(__RLIMIT_NOFILE)
#define RLIMIT_NOFILE     RLIMIT_NOFILE     /* Max # of open file descriptors (total; does not affect greatest usable FD number) */
#endif /* !RLIMIT_NOFILE && __RLIMIT_NOFILE */
#if !defined(RLIMIT_OFILE) && defined(__RLIMIT_NOFILE)
#define RLIMIT_OFILE      RLIMIT_OFILE      /* Max # of open file descriptors (total; does not affect greatest usable FD number) */
#endif /* !RLIMIT_OFILE && __RLIMIT_NOFILE */
#if !defined(RLIMIT_MEMLOCK) && defined(__RLIMIT_MEMLOCK)
#define RLIMIT_MEMLOCK    RLIMIT_MEMLOCK    /* ??? */
#endif /* !RLIMIT_MEMLOCK && __RLIMIT_MEMLOCK */
#if !defined(RLIMIT_AS) && defined(__RLIMIT_AS)
#define RLIMIT_AS         RLIMIT_AS         /* ??? */
#endif /* !RLIMIT_AS && __RLIMIT_AS */
#if !defined(RLIMIT_LOCKS) && defined(__RLIMIT_LOCKS)
#define RLIMIT_LOCKS      RLIMIT_LOCKS      /* ??? */
#endif /* !RLIMIT_LOCKS && __RLIMIT_LOCKS */
#if !defined(RLIMIT_SIGPENDING) && defined(__RLIMIT_SIGPENDING)
#define RLIMIT_SIGPENDING RLIMIT_SIGPENDING /* ??? */
#endif /* !RLIMIT_SIGPENDING && __RLIMIT_SIGPENDING */
#if !defined(RLIMIT_MSGQUEUE) && defined(__RLIMIT_MSGQUEUE)
#define RLIMIT_MSGQUEUE   RLIMIT_MSGQUEUE   /* ??? */
#endif /* !RLIMIT_MSGQUEUE && __RLIMIT_MSGQUEUE */
#if !defined(RLIMIT_NICE) && defined(__RLIMIT_NICE)
#define RLIMIT_NICE       RLIMIT_NICE       /* ??? */
#endif /* !RLIMIT_NICE && __RLIMIT_NICE */
#if !defined(RLIMIT_RTPRIO) && defined(__RLIMIT_RTPRIO)
#define RLIMIT_RTPRIO     RLIMIT_RTPRIO     /* ??? */
#endif /* !RLIMIT_RTPRIO && __RLIMIT_RTPRIO */
#if !defined(RLIMIT_RTTIME) && defined(__RLIMIT_RTTIME)
#define RLIMIT_RTTIME     RLIMIT_RTTIME     /* ??? */
#endif /* !RLIMIT_RTTIME && __RLIMIT_RTTIME */
#if !defined(RLIMIT_NLIMITS) && defined(__RLIMIT_NLIMITS)
#define RLIMIT_NLIMITS    RLIMIT_NLIMITS    /* Total # of (standard) resource limits */
#endif /* !RLIMIT_NLIMITS && __RLIMIT_NLIMITS */
#if !defined(RLIM_NLIMITS) && defined(__RLIMIT_NLIMITS)
#define RLIM_NLIMITS      RLIM_NLIMITS      /* Total # of (standard) resource limits */
#endif /* !RLIM_NLIMITS && __RLIMIT_NLIMITS */

	/* Extended resource limits (OS-specific) */
#if defined(__USE_KOS) && defined(__RLIMIT_MAXFILE)
#define RLIMIT_MAXFILE    RLIMIT_MAXFILE    /* greatest usable FD number */
#endif /* __USE_KOS && __RLIMIT_MAXFILE */
#else /* __COMPILER_PREFERR_ENUMS */
#if !defined(RLIMIT_CPU) && defined(__RLIMIT_CPU)
#define RLIMIT_CPU        __RLIMIT_CPU        /* ??? */
#endif /* !RLIMIT_CPU && __RLIMIT_CPU */
#if !defined(RLIMIT_FSIZE) && defined(__RLIMIT_FSIZE)
#define RLIMIT_FSIZE      __RLIMIT_FSIZE      /* ??? */
#endif /* !RLIMIT_FSIZE && __RLIMIT_FSIZE */
#if !defined(RLIMIT_DATA) && defined(__RLIMIT_DATA)
#define RLIMIT_DATA       __RLIMIT_DATA       /* ??? */
#endif /* !RLIMIT_DATA && __RLIMIT_DATA */
#if !defined(RLIMIT_STACK) && defined(__RLIMIT_STACK)
#define RLIMIT_STACK      __RLIMIT_STACK      /* ??? */
#endif /* !RLIMIT_STACK && __RLIMIT_STACK */
#if !defined(RLIMIT_CORE) && defined(__RLIMIT_CORE)
#define RLIMIT_CORE       __RLIMIT_CORE       /* ??? */
#endif /* !RLIMIT_CORE && __RLIMIT_CORE */
#if !defined(RLIMIT_RSS) && defined(__RLIMIT_RSS)
#define RLIMIT_RSS        __RLIMIT_RSS        /* ??? */
#endif /* !RLIMIT_RSS && __RLIMIT_RSS */
#if !defined(RLIMIT_NPROC) && defined(__RLIMIT_NPROC)
#define RLIMIT_NPROC      __RLIMIT_NPROC      /* ??? */
#endif /* !RLIMIT_NPROC && __RLIMIT_NPROC */
#if !defined(RLIMIT_NOFILE) && defined(__RLIMIT_NOFILE)
#define RLIMIT_NOFILE     __RLIMIT_NOFILE     /* Max # of open file descriptors (total; does not affect greatest usable FD number) */
#endif /* !RLIMIT_NOFILE && __RLIMIT_NOFILE */
#if !defined(RLIMIT_OFILE) && defined(__RLIMIT_NOFILE)
#define RLIMIT_OFILE      __RLIMIT_NOFILE     /* Max # of open file descriptors (total; does not affect greatest usable FD number) */
#endif /* !RLIMIT_OFILE && __RLIMIT_NOFILE */
#if !defined(RLIMIT_MEMLOCK) && defined(__RLIMIT_MEMLOCK)
#define RLIMIT_MEMLOCK    __RLIMIT_MEMLOCK    /* ??? */
#endif /* !RLIMIT_MEMLOCK && __RLIMIT_MEMLOCK */
#if !defined(RLIMIT_AS) && defined(__RLIMIT_AS)
#define RLIMIT_AS         __RLIMIT_AS         /* ??? */
#endif /* !RLIMIT_AS && __RLIMIT_AS */
#if !defined(RLIMIT_LOCKS) && defined(__RLIMIT_LOCKS)
#define RLIMIT_LOCKS      __RLIMIT_LOCKS      /* ??? */
#endif /* !RLIMIT_LOCKS && __RLIMIT_LOCKS */
#if !defined(RLIMIT_SIGPENDING) && defined(__RLIMIT_SIGPENDING)
#define RLIMIT_SIGPENDING __RLIMIT_SIGPENDING /* ??? */
#endif /* !RLIMIT_SIGPENDING && __RLIMIT_SIGPENDING */
#if !defined(RLIMIT_MSGQUEUE) && defined(__RLIMIT_MSGQUEUE)
#define RLIMIT_MSGQUEUE   __RLIMIT_MSGQUEUE   /* ??? */
#endif /* !RLIMIT_MSGQUEUE && __RLIMIT_MSGQUEUE */
#if !defined(RLIMIT_NICE) && defined(__RLIMIT_NICE)
#define RLIMIT_NICE       __RLIMIT_NICE       /* ??? */
#endif /* !RLIMIT_NICE && __RLIMIT_NICE */
#if !defined(RLIMIT_RTPRIO) && defined(__RLIMIT_RTPRIO)
#define RLIMIT_RTPRIO     __RLIMIT_RTPRIO     /* ??? */
#endif /* !RLIMIT_RTPRIO && __RLIMIT_RTPRIO */
#if !defined(RLIMIT_RTTIME) && defined(__RLIMIT_RTTIME)
#define RLIMIT_RTTIME     __RLIMIT_RTTIME     /* ??? */
#endif /* !RLIMIT_RTTIME && __RLIMIT_RTTIME */
#if !defined(RLIMIT_NLIMITS) && defined(__RLIMIT_NLIMITS)
#define RLIMIT_NLIMITS    __RLIMIT_NLIMITS    /* Total # of (standard) resource limits */
#endif /* !RLIMIT_NLIMITS && __RLIMIT_NLIMITS */
#if !defined(RLIM_NLIMITS) && defined(__RLIMIT_NLIMITS)
#define RLIM_NLIMITS      __RLIMIT_NLIMITS    /* Total # of (standard) resource limits */
#endif /* !RLIM_NLIMITS && __RLIMIT_NLIMITS */

	/* Extended resource limits (OS-specific) */
#if defined(__USE_KOS) && defined(__RLIMIT_MAXFILE)
#define RLIMIT_MAXFILE    __RLIMIT_MAXFILE    /* greatest usable FD number */
#endif /* __USE_KOS && __RLIMIT_MAXFILE */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */


#if !defined(RLIM_INFINITY) && defined(__RLIM_INFINITY)
#define RLIM_INFINITY   __RLIM_INFINITY   /* Unlimited */
#endif /* !RLIM_INFINITY && __RLIM_INFINITY */
#ifdef __USE_LARGEFILE64
#if !defined(RLIM64_INFINITY) && defined(__RLIM64_INFINITY)
#define RLIM64_INFINITY __RLIM64_INFINITY /* Unlimited */
#endif /* !RLIM64_INFINITY && __RLIM64_INFINITY */
#endif /* __USE_LARGEFILE64 */

#ifndef RLIM_SAVED_MAX
#if !defined(RLIM_SAVED_MAX) && defined(RLIM_INFINITY)
#define RLIM_SAVED_MAX RLIM_INFINITY
#endif /* !RLIM_SAVED_MAX */
#ifndef RLIM_SAVED_CUR
#endif /* !RLIM_SAVED_MAX && RLIM_INFINITY */
#if !defined(RLIM_SAVED_CUR) && defined(RLIM_INFINITY)
#define RLIM_SAVED_CUR RLIM_INFINITY
#endif /* !RLIM_SAVED_CUR */
#endif /* !RLIM_SAVED_CUR && RLIM_INFINITY */

#if ((!defined(PRIO_PROCESS) && defined(__PRIO_PROCESS)) || \
     (!defined(PRIO_PGRP) && defined(__PRIO_PGRP)) ||       \
     (!defined(PRIO_USER) && defined(__PRIO_USER)))
/* ??? */
/*[[[enum]]]*/
#ifdef __CC__
enum __priority_which {
#if !defined(PRIO_PROCESS) && defined(__PRIO_PROCESS)
	PRIO_PROCESS = __PRIO_PROCESS, /* ??? */
#endif /* !PRIO_PROCESS && __PRIO_PROCESS */
#if !defined(PRIO_PGRP) && defined(__PRIO_PGRP)
	PRIO_PGRP    = __PRIO_PGRP,    /* ??? */
#endif /* !PRIO_PGRP && __PRIO_PGRP */
#if !defined(PRIO_USER) && defined(__PRIO_USER)
	PRIO_USER    = __PRIO_USER     /* ??? */
#endif /* !PRIO_USER && __PRIO_USER */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#if !defined(PRIO_PROCESS) && defined(__PRIO_PROCESS)
#define PRIO_PROCESS PRIO_PROCESS /* ??? */
#endif /* !PRIO_PROCESS && __PRIO_PROCESS */
#if !defined(PRIO_PGRP) && defined(__PRIO_PGRP)
#define PRIO_PGRP    PRIO_PGRP    /* ??? */
#endif /* !PRIO_PGRP && __PRIO_PGRP */
#if !defined(PRIO_USER) && defined(__PRIO_USER)
#define PRIO_USER    PRIO_USER    /* ??? */
#endif /* !PRIO_USER && __PRIO_USER */
#else /* __COMPILER_PREFERR_ENUMS */
#if !defined(PRIO_PROCESS) && defined(__PRIO_PROCESS)
#define PRIO_PROCESS __PRIO_PROCESS /* ??? */
#endif /* !PRIO_PROCESS && __PRIO_PROCESS */
#if !defined(PRIO_PGRP) && defined(__PRIO_PGRP)
#define PRIO_PGRP    __PRIO_PGRP    /* ??? */
#endif /* !PRIO_PGRP && __PRIO_PGRP */
#if !defined(PRIO_USER) && defined(__PRIO_USER)
#define PRIO_USER    __PRIO_USER    /* ??? */
#endif /* !PRIO_USER && __PRIO_USER */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */


#if ((!defined(RUSAGE_SELF) && defined(__RUSAGE_SELF)) ||         \
     (!defined(RUSAGE_CHILDREN) && defined(__RUSAGE_CHILDREN)) || \
     (defined(__USE_GNU) && (!defined(RUSAGE_THREAD) && defined(__RUSAGE_THREAD))))
/* ??? */
/*[[[enum]]]*/
#ifdef __CC__
enum __rusage_who {
#if !defined(RUSAGE_SELF) && defined(__RUSAGE_SELF)
	RUSAGE_SELF     = __RUSAGE_SELF,     /* ??? */
#endif /* !RUSAGE_SELF && __RUSAGE_SELF */
#if !defined(RUSAGE_CHILDREN) && defined(__RUSAGE_CHILDREN)
	RUSAGE_CHILDREN = __RUSAGE_CHILDREN, /* ??? */
#endif /* !RUSAGE_CHILDREN && __RUSAGE_CHILDREN */
#ifdef __USE_GNU
#if !defined(RUSAGE_THREAD) && defined(__RUSAGE_THREAD)
	RUSAGE_THREAD   = __RUSAGE_THREAD    /* ??? */
#endif /* !RUSAGE_THREAD && __RUSAGE_THREAD */
#endif /* __USE_GNU */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#if !defined(RUSAGE_SELF) && defined(__RUSAGE_SELF)
#define RUSAGE_SELF     RUSAGE_SELF     /* ??? */
#endif /* !RUSAGE_SELF && __RUSAGE_SELF */
#if !defined(RUSAGE_CHILDREN) && defined(__RUSAGE_CHILDREN)
#define RUSAGE_CHILDREN RUSAGE_CHILDREN /* ??? */
#endif /* !RUSAGE_CHILDREN && __RUSAGE_CHILDREN */
#ifdef __USE_GNU
#if !defined(RUSAGE_THREAD) && defined(__RUSAGE_THREAD)
#define RUSAGE_THREAD   RUSAGE_THREAD   /* ??? */
#endif /* !RUSAGE_THREAD && __RUSAGE_THREAD */
#endif /* __USE_GNU */
#else /* __COMPILER_PREFERR_ENUMS */
#if !defined(RUSAGE_SELF) && defined(__RUSAGE_SELF)
#define RUSAGE_SELF     __RUSAGE_SELF     /* ??? */
#endif /* !RUSAGE_SELF && __RUSAGE_SELF */
#if !defined(RUSAGE_CHILDREN) && defined(__RUSAGE_CHILDREN)
#define RUSAGE_CHILDREN __RUSAGE_CHILDREN /* ??? */
#endif /* !RUSAGE_CHILDREN && __RUSAGE_CHILDREN */
#ifdef __USE_GNU
#if !defined(RUSAGE_THREAD) && defined(__RUSAGE_THREAD)
#define RUSAGE_THREAD   __RUSAGE_THREAD   /* ??? */
#endif /* !RUSAGE_THREAD && __RUSAGE_THREAD */
#endif /* __USE_GNU */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */

/* Min/max thread/process priority */
#if !defined(PRIO_MIN) && defined(__PRIO_MIN)
#define PRIO_MIN __PRIO_MIN /* Minimum priority */
#endif /* !PRIO_MIN && __PRIO_MIN */
#if !defined(PRIO_MAX) && defined(__PRIO_MAX)
#define PRIO_MAX __PRIO_MAX /* Maximum priority */
#endif /* !PRIO_MAX && __PRIO_MAX */


#ifdef __CC__

#ifndef __rlim_t_defined
#define __rlim_t_defined
typedef __rlim_t rlim_t; /* Resource limit quantity */
#endif /* !__rlim_t_defined */

#ifdef __USE_LARGEFILE64
#ifndef __rlim64_t_defined
#define __rlim64_t_defined
typedef __rlim64_t rlim64_t; /* Resource limit quantity (64-bit) */
#endif /* !__rlim64_t_defined */
#endif /* __USE_LARGEFILE64 */

#ifndef __id_t_defined
#define __id_t_defined
typedef __id_t id_t;
#endif /* !__id_t_defined */

#if defined(__USE_GNU) && defined(__COMPILER_PREFERR_ENUMS)
typedef enum __rlimit_resource __rlimit_resource_t;
typedef enum __rusage_who      __rusage_who_t;
typedef enum __priority_which  __priority_which_t;
#else /* __USE_GNU && __COMPILER_PREFERR_ENUMS */
typedef int __rlimit_resource_t;
typedef int __rusage_who_t;
typedef int __priority_which_t;
#endif /* !__USE_GNU || !__COMPILER_PREFERR_ENUMS */

}

%[define_type_class(__rlimit_resource_t = "TD")]
%[define_type_class(__rusage_who_t = "TD")]
%[define_type_class(__priority_which_t = "TD")]
%[define_replacement(__rlimit_resource_t = int)]
%[define_replacement(__rusage_who_t = int)]
%[define_replacement(__priority_which_t = int)]


%#ifdef __USE_GNU
[[decl_include("<bits/os/rlimit.h>", "<bits/types.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__), alias("prlimit")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__), alias("prlimit64")]]
int prlimit($pid_t pid, __rlimit_resource_t resource,
            [[in_opt]] struct rlimit const *new_limit,
            [[out_opt]] struct rlimit *old_limit);

%#ifdef __USE_LARGEFILE64
[[preferred_rlim64_variant_of(prlimit)]]
[[decl_include("<bits/os/rlimit.h>", "<bits/types.h>")]]
int prlimit64($pid_t pid, __rlimit_resource_t resource,
              [[in_opt]] struct rlimit64 const *new_limit,
              [[out_opt]] struct rlimit64 *old_limit);
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_GNU */


[[decl_include("<bits/os/rlimit.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__), alias("getrlimit", "__getrlimit", "__libc_getrlimit")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__), alias("getrlimit64")]]
[[export_as("__getrlimit", "__libc_getrlimit")]]
int getrlimit(__rlimit_resource_t resource,
              [[out]] struct rlimit *rlimits);

[[decl_include("<bits/os/rlimit.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__), alias("setrlimit", "__setrlimit", "__libc_setrlimit")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__), alias("setrlimit64")]]
[[export_as("__setrlimit", "__libc_setrlimit")]]
int setrlimit(__rlimit_resource_t resource,
              [[in]] struct rlimit const *rlimits);

[[decl_include("<bits/os/rusage.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("getrusage", "__getrusage", "__libc_getrusage")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("getrusage64")]]
[[export_as("__getrusage", "__libc_getrusage")]]
int getrusage(__rusage_who_t who,
              [[out]] struct rusage *usage);

%#ifdef __USE_TIME64
[[preferred_time64_variant_of(getrusage), doc_alias("getrusage")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), preferred_alias("__getrusage", "__libc_getrusage")]]
[[decl_include("<bits/os/rusage.h>")]]
int getrusage64(__rusage_who_t who,
                [[out]] struct rusage64 *usage); /* TODO: Inline implementation using `getrusage()' */
%#endif /* __USE_TIME64 */

@@>> getpriority(2), setpriority(2)
@@@param: which: One of `PRIO_PROCESS', `PRIO_PGRP' or `PRIO_USER'
@@@param: who:   An ID in the namespace indicated by `which'
[[decl_include("<bits/types.h>")]]
int getpriority(__priority_which_t which, id_t who);

[[decl_include("<bits/types.h>"), doc_alias("getpriority")]]
[[export_alias("__setpriority", "__libc_setpriority")]]
int setpriority(__priority_which_t which, id_t who, int prio);

%
%#ifdef __USE_LARGEFILE64
[[preferred_rlim64_variant_of(getrlimit)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__), preferred_alias("__getrlimit", "__libc_getrlimit")]]
[[decl_include("<bits/os/rlimit.h>")]]
int getrlimit64(__rlimit_resource_t resource,
                [[out]] struct rlimit64 *rlimits);

[[preferred_rlim64_variant_of(setrlimit)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__), preferred_alias("__setrlimit", "__libc_setrlimit")]]
[[decl_include("<bits/os/rlimit.h>")]]
int setrlimit64(__rlimit_resource_t resource,
                [[in]] struct rlimit64 const *rlimits);
%#endif /* __USE_LARGEFILE64 */


%{

#endif /* __CC__ */

__SYSDECL_END

}
