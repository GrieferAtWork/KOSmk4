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
/* (#) Portability: DragonFly BSD (/sys/sys/ttydefaults.h) */
/* (#) Portability: FreeBSD       (/sys/sys/ttydefaults.h) */
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/sys/ttydefaults.h) */
/* (#) Portability: NetBSD        (/sys/sys/ttydefaults.h) */
/* (#) Portability: OpenBSD       (/sys/sys/ttydefaults.h) */
/* (#) Portability: mintlib       (/include/sys/ttydefaults.h) */
/* (#) Portability: musl libc     (/include/sys/ttydefaults.h) */
/* (#) Portability: uClibc        (/include/sys/ttydefaults.h) */
/*!included_by <sys/ioctl.h>*/
/*!included_by <termios.h>*/
#ifndef _SYS_TTYDEFAULTS_H
#define _SYS_TTYDEFAULTS_H 1

/* DISCLAIMER: _STRONGLY_ Based on '/usr/include/i386-linux-gnu/sys/ttydefaults.h' */

#include <__stdinc.h>

#include <asm/os/termios.h> /* __BRKINT, __ISTRIP, ... */
#include <bits/posix_opt.h>  /* _POSIX_VDISABLE */

/* Defaults on values for `c_iflag', `c_oflag', `c_cflag' and `c_lflag'. */
#if !defined(TTYDEF_IFLAG) && defined(__TTYDEF_IFLAG)
#define TTYDEF_IFLAG __TTYDEF_IFLAG
#endif /* !TTYDEF_IFLAG && __TTYDEF_IFLAG */
#if !defined(TTYDEF_OFLAG) && defined(__TTYDEF_OFLAG)
#define TTYDEF_OFLAG __TTYDEF_OFLAG
#endif /* !TTYDEF_OFLAG && __TTYDEF_OFLAG */
#if !defined(TTYDEF_LFLAG) && defined(__TTYDEF_LFLAG)
#define TTYDEF_LFLAG __TTYDEF_LFLAG
#endif /* !TTYDEF_LFLAG && __TTYDEF_LFLAG */
#if !defined(TTYDEF_CFLAG) && defined(__TTYDEF_CFLAG)
#define TTYDEF_CFLAG __TTYDEF_CFLAG
#endif /* !TTYDEF_CFLAG && __TTYDEF_CFLAG */

/* Default TTY speed. */
#if !defined(TTYDEF_SPEED) && defined(__TTYDEF_SPEED)
#define TTYDEF_SPEED __TTYDEF_SPEED
#endif /* !TTYDEF_SPEED && __TTYDEF_SPEED */


/* Control Character Defaults */
#if !defined(CTRL) && defined(__CTRL)
#define CTRL(x)  __CTRL(x)
#endif /* !CTRL && __CTRL */
#if !defined(CDISCARD) && defined(__CDISCARD)
#define CDISCARD __CDISCARD /* VDISCARD (Unsupported) */
#endif /* !CDISCARD && __CDISCARD */
#if !defined(CDSUSP) && defined(__CDSUSP)
#define CDSUSP   __CDSUSP   /* VDSUSP */
#endif /* !CDSUSP && __CDSUSP */
#if !defined(CEOF) && defined(__CEOF)
#define CEOF     __CEOF     /* VEOF */
#endif /* !CEOF && __CEOF */
#if !defined(CEOL) && defined(__CEOL)
#define CEOL     __CEOL
#endif /* !CEOL && __CEOL */
#if !defined(CEOL2) && defined(__CEOL2)
#define CEOL2    __CEOL2
#endif /* !CEOL2 && __CEOL2 */
#if !defined(CERASE) && defined(__CERASE)
#define CERASE   __CERASE   /* VERASE (== 8; == '\b') */
#endif /* !CERASE && __CERASE */
#if !defined(CINTR) && defined(__CINTR)
#define CINTR    __CINTR    /* VINTR */
#endif /* !CINTR && __CINTR */
#if !defined(CKILL) && defined(__CKILL)
#define CKILL    __CKILL    /* VKILL */
#endif /* !CKILL && __CKILL */
#if !defined(CLNEXT) && defined(__CLNEXT)
#define CLNEXT   __CLNEXT   /* VLNEXT */
#endif /* !CLNEXT && __CLNEXT */
#if !defined(CMIN) && defined(__CMIN)
#define CMIN     __CMIN     /* VMIN */
#endif /* !CMIN && __CMIN */
#if !defined(CQUIT) && defined(__CQUIT)
#define CQUIT    __CQUIT    /* VQUIT */
#endif /* !CQUIT && __CQUIT */
#if !defined(CREPRINT) && defined(__CREPRINT)
#define CREPRINT __CREPRINT /* VREPRINT */
#endif /* !CREPRINT && __CREPRINT */
#if !defined(CSTART) && defined(__CSTART)
#define CSTART   __CSTART   /* VSTART */
#endif /* !CSTART && __CSTART */
#if !defined(CSTATUS) && defined(__CSTATUS)
#define CSTATUS  __CSTATUS  /* VSTATUS (Unsupported) */
#endif /* !CSTATUS && __CSTATUS */
#if !defined(CSTOP) && defined(__CSTOP)
#define CSTOP    __CSTOP    /* VSTOP */
#endif /* !CSTOP && __CSTOP */
#if !defined(CSUSP) && defined(__CSUSP)
#define CSUSP    __CSUSP    /* VSUSP */
#endif /* !CSUSP && __CSUSP */
#if !defined(CSWTCH) && defined(__CSWTCH)
#define CSWTCH   __CSWTCH   /* VSWTCH */
#endif /* !CSWTCH && __CSWTCH */
#if !defined(CTIME) && defined(__CTIME)
#define CTIME    __CTIME    /* VTIME */
#endif /* !CTIME && __CTIME */
#if !defined(CWERASE) && defined(__CWERASE)
#define CWERASE  __CWERASE  /* VWERASE */
#endif /* !CWERASE && __CWERASE */

/* Some aliases... */
#if !defined(CEOT) && defined(__CEOF)
#define CEOT   __CEOF
#endif /* !CEOT && __CEOF */
#if !defined(CBRK) && defined(__CEOL)
#define CBRK   __CEOL
#endif /* !CBRK && __CEOL */
#if !defined(CRPRNT) && defined(__CREPRINT)
#define CRPRNT __CREPRINT
#endif /* !CRPRNT && __CREPRINT */
#if !defined(CFLUSH) && defined(__CDISCARD)
#define CFLUSH __CDISCARD
#endif /* !CFLUSH && __CDISCARD */

/* #define TTYDEFCHARS to include an array of default control characters. */
#ifdef TTYDEFCHARS
#undef TTYDEFCHARS
__SYSDECL_BEGIN
__PRIVATE cc_t ttydefchars[NCCS] = {
	/* FIXME: This part here is not portable! */
	/* [VINTR]    = */ CINTR,
	/* [VQUIT]    = */ CQUIT,
	/* [VERASE]   = */ CERASE,
	/* [VKILL]    = */ CKILL,
	/* [VEOF]     = */ CEOF,
	/* [VTIME]    = */ CTIME,
	/* [VMIN]     = */ CMIN,
	/* [VSWTCH]   = */ CSWTCH,
	/* [VSTART]   = */ CSTART,
	/* [VSTOP]    = */ CSTOP,
	/* [VSUSP]    = */ CSUSP,
	/* [VEOL]     = */ CEOL,
	/* [VREPRINT] = */ CREPRINT,
	/* [VDISCARD] = */ CDISCARD,
	/* [VWERASE]  = */ CWERASE,
	/* [VLNEXT]   = */ CLNEXT,
	/* [VEOL2]    = */ CEOL2,
};
__SYSDECL_END
#endif /* TTYDEFCHARS */

#endif /* !_SYS_TTYDEFAULTS_H */
