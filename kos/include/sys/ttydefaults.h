/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _SYS_TTYDEFAULTS_H
#define _SYS_TTYDEFAULTS_H 1

/* DISCLAIMER: _STRONGLY_ Based on '/usr/include/i386-linux-gnu/sys/ttydefaults.h' */

#include <__stdinc.h>

#include <bits/termios.h>   /* BRKINT, ISTRIP, ... */
#include <bits/posix_opt.h> /* _POSIX_VDISABLE */

__SYSDECL_BEGIN

#ifndef ECHOKE
#define ECHOKE  0004000 /* If ICANON is also set, KILL is echoed by erasing each character on the line, as specified by ECHOE and ECHOPRT */
#endif /* !ECHOKE */
#ifndef ECHOCTL
#define ECHOCTL 0001000 /* If ECHO is also set, terminal special characters other than TAB(\t), NL(\n),
                         * START, and STOP are echoed as ^X, where X is the character with ASCII code
                         * 0x40 greater than the special character. For example, character 0x08 (BS)
                         * is echoed as ^H */
#endif /* !ECHOCTL */

/* Defaults on values for `c_iflag', `c_oflag', `c_cflag' and `c_lflag'. */
#define TTYDEF_IFLAG                                                                  \
	(BRKINT /*| ISTRIP /* Don't turn this on by default... - Ever heard of unicode?*/ \
	 | ICRNL | IMAXBEL | IXON | IXANY | IUTF8 /* Turn on UTF-8 support by default! */)
#define TTYDEF_OFLAG                                                                 \
	(OPOST | ONLCR                                                                   \
	 /*| XTABS /* Not needed (apparently this converts tabs to spaces, though I have \
	            * no idea how termios should know how many spaces...) */)
#define TTYDEF_LFLAG                                            \
	(ECHO | ICANON | ISIG | IEXTEN | ECHOE | ECHOKE | ECHOCTL | \
	 /* These last two, linux doesn't enable by default,        \
	  * but I see no reason why one shouldn't! */               \
	 ECHOK | TOSTOP)
#define TTYDEF_CFLAG                                                                       \
	(CREAD | CS8 /* | CS7 /* Get with the times! Characters are now 8-bit! Unicode FTW! */ \
	 | PARENB | HUPCL)
#define TTYDEF_SPEED (B9600)

/* Control Character Defaults */
#define CTRL(x)     ((x) & 037)
#ifdef VDISCARD
#define CDISCARD    CTRL('o') /* VDISCARD (Unsupported) */
#endif /* VDISCARD */
#ifdef VDSUSP
#define CDSUSP      CTRL('y') /* VDSUSP */
#endif /* VDSUSP */
#ifdef VEOF
#define CEOF        CTRL('d') /* VEOF */
#endif /* VEOF */
#ifdef VEOL
#define CEOL        _POSIX_VDISABLE
#endif /* VEOL */
#ifdef VEOL2
#define CEOL2       _POSIX_VDISABLE
#endif /* VEOL2 */
#ifdef VERASE
#define CERASE      CTRL('h') /* VERASE (== 8; == '\b') */
#endif /* VERASE */
#ifdef VINTR
#define CINTR       CTRL('c') /* VINTR */
#endif /* VINTR */
#ifdef VKILL
#define CKILL       CTRL('u') /* VKILL */
#endif /* VKILL */
#ifdef VLNEXT
#define CLNEXT      CTRL('v') /* VLNEXT */
#endif /* VLNEXT */
#ifdef VMIN
#define CMIN        1         /* VMIN */
#endif /* VMIN */
#ifdef VQUIT
#define CQUIT       CTRL('\\')/* VQUIT */
#endif /* VQUIT */
#ifdef VREPRINT
#define CREPRINT    CTRL('r') /* VREPRINT */
#endif /* VREPRINT */
#ifdef VSTART
#define CSTART      CTRL('q') /* VSTART */
#endif /* VSTART */
#ifdef VSTATUS
#define CSTATUS     CTRL('t') /* VSTATUS (Unsupported) */
#endif /* VSTATUS */
#ifdef VSTOP
#define CSTOP       CTRL('s') /* VSTOP */
#endif /* VSTOP */
#ifdef VSUSP
#define CSUSP       CTRL('z') /* VSUSP */
#endif /* VSUSP */
#ifdef VSWTCH
#define CSWTCH      _POSIX_VDISABLE /* VSWTCH */
#endif /* VSWTCH */
#ifdef VTIME
#define CTIME       0         /* VTIME */
#endif /* VTIME */
#ifdef VWERASE
#define CWERASE     CTRL('w') /* VWERASE */
#endif /* VWERASE */

/* Some aliases... */
#ifdef CEOF
#define CEOT        CEOF
#endif /* CEOF */
#ifdef CEOL
#define CBRK        CEOL
#endif /* CEOL */
#ifdef CREPRINT
#define CRPRNT      CREPRINT
#endif /* CREPRINT */
#ifdef CDISCARD
#define CFLUSH      CDISCARD
#endif /* CDISCARD */

/* #define TTYDEFCHARS to include an array of default control characters. */
#ifdef TTYDEFCHARS
#undef TTYDEFCHARS
__PRIVATE cc_t ttydefchars[NCCS] = {
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
#endif /* TTYDEFCHARS */

__SYSDECL_END

#endif /* !_SYS_TTYDEFAULTS_H */

