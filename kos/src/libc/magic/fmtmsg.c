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
%(c_prefix){
/* (#) Portability: DragonFly BSD (/include/fmtmsg.h) */
/* (#) Portability: FreeBSD       (/include/fmtmsg.h) */
/* (#) Portability: GNU C Library (/stdlib/fmtmsg.h) */
/* (#) Portability: GNU Hurd      (/usr/include/fmtmsg.h) */
/* (#) Portability: NetBSD        (/include/fmtmsg.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/fmtmsg.h) */
/* (#) Portability: libc6         (/include/fmtmsg.h) */
/* (#) Portability: musl libc     (/include/fmtmsg.h) */
}

%[define_replacement(regoff_t = __regoff_t)]

%[default:section(".text.crt{|.dos}.fmtmsg")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <asm/crt/fmtmsg.h>
)]%{

/* Possible flags for `fmtmsg(3)::classification' */
#if !defined(MM_HARD) && defined(__MM_HARD)
#define MM_HARD    __MM_HARD    /* Caused by hardware */
#endif /* !MM_HARD && __MM_HARD */
#if !defined(MM_SOFT) && defined(__MM_SOFT)
#define MM_SOFT    __MM_SOFT    /* Caused by software */
#endif /* !MM_SOFT && __MM_SOFT */
#if !defined(MM_FIRM) && defined(__MM_FIRM)
#define MM_FIRM    __MM_FIRM    /* Caused by firmware */
#endif /* !MM_FIRM && __MM_FIRM */
#if !defined(MM_APPL) && defined(__MM_APPL)
#define MM_APPL    __MM_APPL    /* Detected by application */
#endif /* !MM_APPL && __MM_APPL */
#if !defined(MM_UTIL) && defined(__MM_UTIL)
#define MM_UTIL    __MM_UTIL    /* Detected by utility */
#endif /* !MM_UTIL && __MM_UTIL */
#if !defined(MM_OPSYS) && defined(__MM_OPSYS)
#define MM_OPSYS   __MM_OPSYS   /* Detected by operating system */
#endif /* !MM_OPSYS && __MM_OPSYS */
#if !defined(MM_RECOVER) && defined(__MM_RECOVER)
#define MM_RECOVER __MM_RECOVER /* Error is recoverable */
#endif /* !MM_RECOVER && __MM_RECOVER */
#if !defined(MM_NRECOV) && defined(__MM_NRECOV)
#define MM_NRECOV  __MM_NRECOV  /* Error is non-recoverable */
#endif /* !MM_NRECOV && __MM_NRECOV */
#if !defined(MM_PRINT) && defined(__MM_PRINT)
#define MM_PRINT   __MM_PRINT   /* Print to `stderr(3)' */
#endif /* !MM_PRINT && __MM_PRINT */
#if !defined(MM_CONSOLE) && defined(__MM_CONSOLE)
#define MM_CONSOLE __MM_CONSOLE /* Print to `syslog(3)' */
#endif /* !MM_CONSOLE && __MM_CONSOLE */

/* Pre-defined values for `fmtmsg(3)::severity' */
#if !defined(MM_NOSEV) && defined(__MM_NOSEV)
#define MM_NOSEV   __MM_NOSEV   /* No severity level */
#endif /* !MM_NOSEV && __MM_NOSEV */
#if !defined(MM_HALT) && defined(__MM_HALT)
#define MM_HALT    __MM_HALT    /* Application will halt as a result */
#endif /* !MM_HALT && __MM_HALT */
#if !defined(MM_ERROR) && defined(__MM_ERROR)
#define MM_ERROR   __MM_ERROR   /* Non-fatal error encountered */
#endif /* !MM_ERROR && __MM_ERROR */
#if !defined(MM_WARNING) && defined(__MM_WARNING)
#define MM_WARNING __MM_WARNING /* Unusual non-error condition (== warning) */
#endif /* !MM_WARNING && __MM_WARNING */
#if !defined(MM_INFO) && defined(__MM_INFO)
#define MM_INFO    __MM_INFO    /* General information */
#endif /* !MM_INFO && __MM_INFO */

/* Return values for `fmtmsg(3)' */
#if !defined(MM_NOTOK) && defined(__MM_NOTOK)
#define MM_NOTOK __MM_NOTOK /* Arguments are bad */
#endif /* !MM_NOTOK && __MM_NOTOK */
#if !defined(MM_OK) && defined(__MM_OK)
#define MM_OK    __MM_OK    /* Success */
#endif /* !MM_OK && __MM_OK */
#if !defined(MM_NOMSG) && defined(__MM_NOMSG)
#define MM_NOMSG __MM_NOMSG /* Failed to print message to `stderr(3)' */
#endif /* !MM_NOMSG && __MM_NOMSG */
#if !defined(MM_NOCON) && defined(__MM_NOCON)
#define MM_NOCON __MM_NOCON /* Failed to print message to `syslog(3)' (never returned since syslog has no error-condition) */
#endif /* !MM_NOCON && __MM_NOCON */


/* NULL-placeholders for arguments of `fmtmsg(3)' */
#define MM_NULLMC  ((long)0)         /* Default value for `classification' */
#define MM_NULLLBL ((char const *)0) /* Default value for `label' */
#define MM_NULLSEV 0                 /* Default value for `severity' */
#define MM_NULLTXT ((char const *)0) /* Default value for `text' */
#define MM_NULLACT ((char const *)0) /* Default value for `action' */
#define MM_NULLTAG ((char const *)0) /* Default value for `tag' */

#ifdef __CC__
__SYSDECL_BEGIN

}

@@>> fmtmsg(3)
@@Print a message to `stderr(3)' and/or `syslog(3)'. The exact  format
@@in which the mssage is printed, alongside additional severity levels
@@depends on `$MSGVERB', `$SEV_LEVEL' and `addseverity(3)'.
@@@param: classification: Set of:
@@         - `MM_PRINT', `MM_CONSOLE', or `MM_PRINT | MM_CONSOLE'
@@         - `MM_HARD', `MM_FIRM' or `MM_SOFT'
@@         - `MM_APPL', `MM_UTIL' or `MM_OPSYS'
@@         - `MM_RECOVER' or `MM_NRECOV'
@@@param: label:    Message source, as "<domain>:<util>", where  "<domain>"
@@                  must not be longer than 10 chars, and "<util>" must not
@@                  be longer than 14 chars.
@@@param: severity: Message severity code (extra severity codes can be
@@                  defined by `addseverity(3)'  or via  `$SEV_LEVEL')
@@@param: text:     Error condition (e.g. "bad arguments given")
@@@param: action:   Steps to fix the error (if printed, is prefixed by "TO FIX: ")
@@@param: tag:      Reference to online docs for more info on error (should include `label')
@@@return: MM_NOTOK: Arguments are bad
@@@return: MM_OK:    Success
@@@return: MM_NOMSG: Failed to print message to `stderr(3)'
[[decl_include("<features.h>")]]
int fmtmsg(long classification,
           [[nullable]] char const *label,
           __STDC_INT_AS_UINT_T severity,
           [[nullable]] char const *text,
           [[nullable]] char const *action,
           [[nullable]] char const *tag);


%
%#ifdef __USE_MISC
@@>> addseverity(3)
@@Add  (`s != NULL') or remove  (`s == NULL') custom severity levels.
@@By default (and these cannot be overwritten or removed), levels 0-4
@@are defined as:
@@ - 0: MM_NOSEV:   [""]        No severity level
@@ - 1: MM_HALT:    ["HALT"]    Application will halt as a result
@@ - 2: MM_ERROR:   ["ERROR"]   Non-fatal error encountered
@@ - 3: MM_WARNING: ["WARNING"] Unusual non-error condition (== warning)
@@ - 4: MM_INFO:    ["INFO"]    General information
@@Additionally,  `$SEV_LEVEL' is used  to define additional severity
@@levels  dynamically (just like  this function can  be used to) the
@@first time this function (or `fmtmsg(3)') is called. The format of
@@the `$SEV_LEVEL' variable follows posix specifications, and unlike
@@with the 5 default severity levels, these can be removed again, or
@@further overwritten by use of this function
@@@param: severity: The ID to assign for the new severity level (must be >= 5)
@@@param: s: - When non-NULL, define (or override) the label for `severity'.
@@           - When NULL, remove the definition for `severity'
@@@return: MM_OK:    Success
@@@return: MM_NOTOK: The given `severity' is `< 5' (errno was not modified)
@@@return: MM_NOTOK: Out of memory (errno was set to `ENOMEM')
@@@return: MM_NOTOK: No such `severity' and `s == NULL' (errno was not modified)
[[decl_include("<features.h>")]]
int addseverity(__STDC_INT_AS_UINT_T severity, [[nullable]] char const *s);
%#endif /* __USE_MISC */


%{

__SYSDECL_END
#endif /* __CC__ */

}
