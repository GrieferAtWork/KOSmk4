/* HASH CRC-32:0x2bf36112 */
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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/syslog.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/syslog.h) */
/* (#) Portability: FreeBSD       (/sys/sys/syslog.h) */
/* (#) Portability: GNU C Library (/misc/sys/syslog.h) */
/* (#) Portability: NetBSD        (/sys/sys/syslog.h) */
/* (#) Portability: OpenBSD       (/sys/sys/syslog.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/syslog.h) */
/* (#) Portability: diet libc     (/include/sys/syslog.h) */
/* (#) Portability: libc4/5       (/include/sys/syslog.h) */
/* (#) Portability: mintlib       (/include/sys/syslog.h) */
/* (#) Portability: musl libc     (/include/sys/syslog.h) */
/* (#) Portability: uClibc        (/include/sys/syslog.h) */
#ifndef _SYS_SYSLOG_H
#define _SYS_SYSLOG_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/os/syslog.h>
#include <asm/os/paths.h> /* __PATH_LOG */

#ifdef __USE_KOS
#include <bits/crt/format-printer.h>
#endif /* __USE_KOS */


#if !defined(_PATH_LOG) && defined(__PATH_LOG)
#define _PATH_LOG __PATH_LOG /* Filesystem path to the kernel logger */
#endif /* !_PATH_LOG && __PATH_LOG */



#if !defined(LOG_EMERG) && defined(__LOG_EMERG)
#define LOG_EMERG   __LOG_EMERG   /* ... */
#endif /* !LOG_EMERG && __LOG_EMERG */
#if !defined(LOG_ALERT) && defined(__LOG_ALERT)
#define LOG_ALERT   __LOG_ALERT   /* ... */
#endif /* !LOG_ALERT && __LOG_ALERT */
#if !defined(LOG_CRIT) && defined(__LOG_CRIT)
#define LOG_CRIT    __LOG_CRIT    /* ... */
#endif /* !LOG_CRIT && __LOG_CRIT */
#if !defined(LOG_ERR) && defined(__LOG_ERR)
#define LOG_ERR     __LOG_ERR     /* ... */
#endif /* !LOG_ERR && __LOG_ERR */
#if !defined(LOG_WARNING) && defined(__LOG_WARNING)
#define LOG_WARNING __LOG_WARNING /* ... */
#endif /* !LOG_WARNING && __LOG_WARNING */
#if !defined(LOG_NOTICE) && defined(__LOG_NOTICE)
#define LOG_NOTICE  __LOG_NOTICE  /* ... */
#endif /* !LOG_NOTICE && __LOG_NOTICE */
#if !defined(LOG_INFO) && defined(__LOG_INFO)
#define LOG_INFO    __LOG_INFO    /* ... */
#endif /* !LOG_INFO && __LOG_INFO */
#if !defined(LOG_DEBUG) && defined(__LOG_DEBUG)
#define LOG_DEBUG   __LOG_DEBUG   /* ... */
#endif /* !LOG_DEBUG && __LOG_DEBUG */
#if !defined(LOG_PRIMASK) && defined(__LOG_PRIMASK)
#define LOG_PRIMASK __LOG_PRIMASK /* ... */
#endif /* !LOG_PRIMASK && __LOG_PRIMASK */

/* extract priority */
#ifdef LOG_PRIMASK
#define LOG_PRI(p)            ((p) & LOG_PRIMASK)
#define LOG_MAKEPRI(fac, pri) ((fac) | (pri))
#endif /* LOG_PRIMASK */

#ifdef __USE_KOS
#if !defined(LOG_ERROR) && defined(__LOG_ERR)
#define LOG_ERROR   __LOG_ERR
#endif /* !LOG_ERROR && __LOG_ERR */
#if !defined(LOG_WARN) && defined(__LOG_WARNING)
#define LOG_WARN    __LOG_WARNING
#endif /* !LOG_WARN && __LOG_WARNING */
#if !defined(LOG_CONFIRM) && defined(__LOG_NOTICE)
#define LOG_CONFIRM __LOG_NOTICE
#endif /* !LOG_CONFIRM && __LOG_NOTICE */
#if !defined(LOG_MESSAGE) && defined(__LOG_INFO)
#define LOG_MESSAGE __LOG_INFO
#endif /* !LOG_MESSAGE && __LOG_INFO */
#endif /* __USE_KOS */

/* TODO: All  of the below  has been lifted from  KOSmk2/3, but hasn't been
 *       updated to fit what is done on KOSmk4, nor has it been  re-checked
 *       against the codes used by linux (there may be differences here...) */

/* facility codes */
#define LOG_KERN        (0 << 3)                 /* ... */
#define LOG_USER        (1 << 3)                 /* ... */
#define LOG_MAIL        (2 << 3)                 /* ... */
#define LOG_DAEMON      (3 << 3)                 /* ... */
#define LOG_AUTH        (4 << 3)                 /* ... */
#define LOG_SYSLOG      (5 << 3)                 /* ... */
#define LOG_LPR         (6 << 3)                 /* ... */
#define LOG_NEWS        (7 << 3)                 /* ... */
#define LOG_UUCP        (8 << 3)                 /* ... */
#define LOG_CRON        (9 << 3)                 /* ... */
#define LOG_AUTHPRIV    (10 << 3)                /* ... */
#define LOG_FTP         (11 << 3)                /* ... */
#define LOG_LOCAL0      (16 << 3)                /* ... */
#define LOG_LOCAL1      (17 << 3)                /* ... */
#define LOG_LOCAL2      (18 << 3)                /* ... */
#define LOG_LOCAL3      (19 << 3)                /* ... */
#define LOG_LOCAL4      (20 << 3)                /* ... */
#define LOG_LOCAL5      (21 << 3)                /* ... */
#define LOG_LOCAL6      (22 << 3)                /* ... */
#define LOG_LOCAL7      (23 << 3)                /* ... */
#define LOG_NFACILITIES 24                       /* # of facilities */
#define LOG_FACMASK     0x03f8                   /* ... */
#define LOG_FAC(p)      (((p)&LOG_FACMASK) >> 3) /* ... */

/* arguments to setlogmask. */
#define LOG_MASK(pri) (1 << (pri))             /* ... */
#define LOG_UPTO(pri) ((1 << ((pri) + 1)) - 1) /* ... */

#define LOG_PID    0x01 /* ... */
#define LOG_CONS   0x02 /* ... */
#define LOG_ODELAY 0x04 /* ... */
#define LOG_NDELAY 0x08 /* ... */
#define LOG_NOWAIT 0x10 /* ... */
#define LOG_PERROR 0x20 /* ... */


#ifdef __CC__
__SYSDECL_BEGIN
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,closelog,(void),())
__CDECLARE_VOID_OPT(,__NOTHROW_RPC,openlog,(char const *__ident, __STDC_INT_AS_UINT_T __option, __STDC_INT_AS_UINT_T __facility),(__ident,__option,__facility))
__CDECLARE_OPT(,int,__NOTHROW_NCX,setlogmask,(__STDC_INT_AS_UINT_T __mask),(__mask))
#ifdef __CRT_HAVE_syslog
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((2)) void __NOTHROW_RPC(__VLIBCCALL syslog)(__STDC_INT_AS_UINT_T __level, char const *__format, ...) __CASMNAME_SAME("syslog");
#elif defined(__CRT_HAVE_vsyslog) || defined(__CRT_HAVE_syslog_printer)
#include <libc/local/sys.syslog/syslog.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(syslog, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((2)) void __NOTHROW_RPC(__VLIBCCALL syslog)(__STDC_INT_AS_UINT_T __level, char const *__format, ...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(syslog))(__level, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define syslog(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(syslog))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */

#ifdef __USE_MISC
#ifdef __CRT_HAVE_vsyslog
__CDECLARE_VOID(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((2)),__NOTHROW_RPC,vsyslog,(__STDC_INT_AS_UINT_T __level, char const *__format, __builtin_va_list __args),(__level,__format,__args))
#elif defined(__CRT_HAVE_syslog_printer)
#include <libc/local/sys.syslog/vsyslog.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vsyslog, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((2)) void __NOTHROW_RPC(__LIBCCALL vsyslog)(__STDC_INT_AS_UINT_T __level, char const *__format, __builtin_va_list __args) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vsyslog))(__level, __format, __args); })
#endif /* ... */
#endif /* __USE_MISC */

#ifdef __USE_KOS
#ifdef __CRT_HAVE_syslog_printer
/* Helper functions for printing to the system log */
__LIBC __ATTR_NONNULL((2)) __SSIZE_TYPE__ __NOTHROW_RPC(__FORMATPRINTER_CC syslog_printer)(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen) __CASMNAME_SAME("syslog_printer");
#endif /* __CRT_HAVE_syslog_printer */
#define SYSLOG_PRINTER_CLOSURE(level) ((void *)(__uintptr_t)(__STDC_INT_AS_UINT_T)(level))
#endif /* __USE_KOS */

#ifdef SYSLOG_NAMES
#define INTERNAL_NOPRI 0x10 /* the "no priority" priority */
#define INTERNAL_MARK  LOG_MAKEPRI(LOG_NFACILITIES << 3, 0) /* mark "facility" */
typedef struct _code {
	char *c_name;
	int   c_val;
} CODE;
CODE prioritynames[] = {
	{ "alert", LOG_ALERT },
	{ "crit", LOG_CRIT },
	{ "debug", LOG_DEBUG },
	{ "emerg", LOG_EMERG },
	{ "err", LOG_ERR },
	{ "error", LOG_ERR },        /* DEPRECATED */
	{ "info", LOG_INFO },
	{ "none", INTERNAL_NOPRI },        /* INTERNAL */
	{ "notice", LOG_NOTICE },
	{ "panic", LOG_EMERG },        /* DEPRECATED */
	{ "warn", LOG_WARNING },        /* DEPRECATED */
	{ "warning", LOG_WARNING },
	{ NULL, -1 }
};

CODE facilitynames[] = {
	{ "auth", LOG_AUTH },
	{ "authpriv", LOG_AUTHPRIV },
	{ "cron", LOG_CRON },
	{ "daemon", LOG_DAEMON },
	{ "ftp", LOG_FTP },
	{ "kern", LOG_KERN },
	{ "lpr", LOG_LPR },
	{ "mail", LOG_MAIL },
	{ "mark", INTERNAL_MARK },        /* INTERNAL */
	{ "news", LOG_NEWS },
	{ "security", LOG_AUTH },        /* DEPRECATED */
	{ "syslog", LOG_SYSLOG },
	{ "user", LOG_USER },
	{ "uucp", LOG_UUCP },
	{ "local0", LOG_LOCAL0 },
	{ "local1", LOG_LOCAL1 },
	{ "local2", LOG_LOCAL2 },
	{ "local3", LOG_LOCAL3 },
	{ "local4", LOG_LOCAL4 },
	{ "local5", LOG_LOCAL5 },
	{ "local6", LOG_LOCAL6 },
	{ "local7", LOG_LOCAL7 },
#ifdef __KERNEL__
	{ "fs", LOG_FS },
	{ "mem", LOG_MEM },
	{ "hw", LOG_HW },
	{ "irq", LOG_IRQ },
	{ "exec", LOG_EXEC },
	{ "sched", LOG_SCHED },
	{ "boot", LOG_BOOT },
	{ "io", LOG_IO },
#endif /* __KERNEL__ */
	{ NULL, -1 }
};
#endif /* SYSLOG_NAMES */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_SYSLOG_H */
