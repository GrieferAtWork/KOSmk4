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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/syslog.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/syslog.h) */
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
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.system.syslog")]

%[assume_defined_in_kos(LOG_EMERG, __LOG_EMERG)]
%[assume_defined_in_kos(LOG_ALERT, __LOG_ALERT)]
%[assume_defined_in_kos(LOG_CRIT, __LOG_CRIT)]
%[assume_defined_in_kos(LOG_ERR, __LOG_ERR)]
%[assume_defined_in_kos(LOG_WARNING, __LOG_WARNING)]
%[assume_defined_in_kos(LOG_NOTICE, __LOG_NOTICE)]
%[assume_defined_in_kos(LOG_INFO, __LOG_INFO)]
%[assume_defined_in_kos(LOG_DEBUG, __LOG_DEBUG)]
%[assume_defined_in_kos(LOG_PRIMASK, __LOG_PRIMASK)]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <asm/os/syslog.h>
)]%[insert:prefix(
#include <asm/os/paths.h> /* __PATH_LOG */
)]%{

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
}

void closelog();

[[cp, decl_include("<features.h>")]]
void openlog(char const *ident,
             __STDC_INT_AS_UINT_T option,
             __STDC_INT_AS_UINT_T facility);

[[decl_include("<features.h>")]]
int setlogmask(__STDC_INT_AS_UINT_T mask);

[[cp, decl_include("<features.h>")]]
void syslog(__STDC_INT_AS_UINT_T level,
            [[in, format("printf")]] char const *format, ...)
	%{printf("vsyslog")}

%
%#ifdef __USE_MISC
[[cp, decl_include("<features.h>")]]
[[requires_dependent_function(syslog_printer)]]
void vsyslog(__STDC_INT_AS_UINT_T level,
             [[in, format("printf")]] char const *format,
             $va_list args) {
	format_vprintf(&syslog_printer,
	               (void *)(uintptr_t)(unsigned int)level,
	               format,
	               args);
}
%#endif /* __USE_MISC */

%
%#ifdef __USE_KOS
@@Helper functions for printing to the system log
[[cp, no_crt_dos_wrapper, cc(__FORMATPRINTER_CC)]]
[[decl_include("<bits/crt/format-printer.h>")]]
$ssize_t syslog_printer(void *arg,
                        [[in(datalen)]] char const *__restrict data,
                        $size_t datalen);

%#define SYSLOG_PRINTER_CLOSURE(level) ((void *)(__uintptr_t)(__STDC_INT_AS_UINT_T)(level))
%#endif /* __USE_KOS */


%{

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

}
