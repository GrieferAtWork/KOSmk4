/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ASM_OS_TERMIOS_H
#define _ASM_OS_TERMIOS_H 1

#include <__stdinc.h>

#if defined(__KOS__) || defined(__linux__)
#include <asm/os/kos/termios.h>
#elif defined(__NetBSD__)
#include <asm/os/netbsd/termios.h>
#elif defined(__FreeBSD__)
#include <asm/os/freebsd/termios.h>
#elif defined(__solaris__)
#include <asm/os/solaris/termios.h>
#endif /* ... */

/* Substitute default values. */
#ifndef __VDISABLE
#define __VDISABLE '\0'
#endif /* !__VDISABLE */

#ifndef __CTRL
#define __CTRL(x)     ((x) & 31)
#endif /* !__CTRL */
#ifndef __CDISCARD
#define __CDISCARD    __CTRL('o') /* VDISCARD (Unsupported) */
#endif /* !__CDISCARD */
#ifndef __CDSUSP
#define __CDSUSP      __CTRL('y') /* VDSUSP */
#endif /* !__CDSUSP */
#ifndef __CEOF
#define __CEOF        __CTRL('d') /* VEOF */
#endif /* !__CEOF */
#ifndef __CEOL
#define __CEOL        __VDISABLE
#endif /* !__CEOL */
#ifndef __CEOL2
#define __CEOL2       __VDISABLE
#endif /* !__CEOL2 */
#ifndef __CERASE
#define __CERASE      __CTRL('h') /* VERASE (== 8; == '\b') */
#endif /* !__CERASE */
#ifndef __CINTR
#define __CINTR       __CTRL('c') /* VINTR */
#endif /* !__CINTR */
#ifndef __CKILL
#define __CKILL       __CTRL('u') /* VKILL */
#endif /* !__CKILL */
#ifndef __CLNEXT
#define __CLNEXT      __CTRL('v') /* VLNEXT */
#endif /* !__CLNEXT */
#ifndef __CMIN
#define __CMIN        1           /* VMIN */
#endif /* !__CMIN */
#ifndef __CQUIT
#define __CQUIT       __CTRL('\\')/* VQUIT */
#endif /* !__CQUIT */
#ifndef __CREPRINT
#define __CREPRINT    __CTRL('r') /* VREPRINT */
#endif /* !__CREPRINT */
#ifndef __CSTART
#define __CSTART      __CTRL('q') /* VSTART */
#endif /* !__CSTART */
#ifndef __CSTATUS
#define __CSTATUS     __CTRL('t') /* VSTATUS (Unsupported) */
#endif /* !__CSTATUS */
#ifndef __CSTOP
#define __CSTOP       __CTRL('s') /* VSTOP */
#endif /* !__CSTOP */
#ifndef __CSUSP
#define __CSUSP       __CTRL('z') /* VSUSP */
#endif /* !__CSUSP */
#ifndef __CSWTCH
#define __CSWTCH      __VDISABLE  /* VSWTCH */
#endif /* !__CSWTCH */
#ifndef __CTIME
#define __CTIME       0           /* VTIME */
#endif /* !__CTIME */
#ifndef __CWERASE
#define __CWERASE     __CTRL('w') /* VWERASE */
#endif /* !__CWERASE */



/* Defaults on values for `c_iflag', `c_oflag', `c_cflag' and `c_lflag'. */
#ifndef __TTYDEF_IFLAG
#ifndef __PRIVATE_BRKINT
#ifdef __BRKINT
#define __PRIVATE_BRKINT __BRKINT
#else /* __BRKINT */
#define __PRIVATE_BRKINT 0
#endif /* !__BRKINT */
#endif /* !__PRIVATE_BRKINT */
#ifndef __PRIVATE_ICRNL
#ifdef __ICRNL
#define __PRIVATE_ICRNL   __ICRNL
#else /* __ICRNL */
#define __PRIVATE_ICRNL   0
#endif /* !__ICRNL */
#endif /* !__PRIVATE_ICRNL */
#ifndef __PRIVATE_IMAXBEL
#ifdef __IMAXBEL
#define __PRIVATE_IMAXBEL __IMAXBEL
#else /* __IMAXBEL */
#define __PRIVATE_IMAXBEL 0
#endif /* !__IMAXBEL */
#endif /* !__PRIVATE_IMAXBEL */
#ifndef __PRIVATE_IXON
#ifdef __IXON
#define __PRIVATE_IXON    __IXON
#else /* __IXON */
#define __PRIVATE_IXON    0
#endif /* !__IXON */
#endif /* !__PRIVATE_IXON */
#ifndef __PRIVATE_IXANY
#ifdef __IXANY
#define __PRIVATE_IXANY   __IXANY
#else /* __IXANY */
#define __PRIVATE_IXANY   0
#endif /* !__IXANY */
#endif /* !__PRIVATE_IXANY */
#ifndef __PRIVATE_IUTF8
#ifdef __IUTF8
#define __PRIVATE_IUTF8   __IUTF8
#else /* __IUTF8 */
#define __PRIVATE_IUTF8   0
#endif /* !__IUTF8 */
#endif /* !__PRIVATE_IUTF8 */
#define __TTYDEF_IFLAG                                                         \
	(/* ISTRIP | * Don't turn this on by default... - Ever heard of unicode?*/ \
	 __PRIVATE_BRKINT | __PRIVATE_ICRNL | __PRIVATE_IMAXBEL |                  \
	 __PRIVATE_IXON | __PRIVATE_IXANY |                                        \
	 __PRIVATE_IUTF8 /* Turn on UTF-8 support by default! */)
#endif /* !__TTYDEF_IFLAG */

#ifndef __TTYDEF_OFLAG
#ifndef __PRIVATE_OPOST
#ifdef __OPOST
#define __PRIVATE_OPOST   __OPOST
#else /* __OPOST */
#define __PRIVATE_OPOST   0
#endif /* !__OPOST */
#endif /* !__PRIVATE_OPOST */
#ifndef __PRIVATE_ONLCR
#ifdef __ONLCR
#define __PRIVATE_ONLCR   __ONLCR
#else /* __ONLCR */
#define __PRIVATE_ONLCR   0
#endif /* !__ONLCR */
#endif /* !__PRIVATE_ONLCR */
#define __TTYDEF_OFLAG                                                              \
	(__PRIVATE_OPOST | __PRIVATE_ONLCR                                              \
	 /*| XTABS * Not needed (apparently this converts tabs to spaces, though I have \
	           * no idea how termios should know how many spaces...) */)
#endif /* !__TTYDEF_OFLAG */

#ifndef __TTYDEF_LFLAG
#ifndef __PRIVATE_ECHO
#ifdef __ECHO
#define __PRIVATE_ECHO    __ECHO
#else /* __ECHO */
#define __PRIVATE_ECHO    0
#endif /* !__ECHO */
#endif /* !__PRIVATE_ECHO */
#ifndef __PRIVATE_ICANON
#ifdef __ICANON
#define __PRIVATE_ICANON  __ICANON
#else /* __ICANON */
#define __PRIVATE_ICANON  0
#endif /* !__ICANON */
#endif /* !__PRIVATE_ICANON */
#ifndef __PRIVATE_ISIG
#ifdef __ISIG
#define __PRIVATE_ISIG    __ISIG
#else /* __ISIG */
#define __PRIVATE_ISIG    0
#endif /* !__ISIG */
#endif /* !__PRIVATE_ISIG */
#ifndef __PRIVATE_IEXTEN
#ifdef __IEXTEN
#define __PRIVATE_IEXTEN  __IEXTEN
#else /* __IEXTEN */
#define __PRIVATE_IEXTEN  0
#endif /* !__IEXTEN */
#endif /* !__PRIVATE_IEXTEN */
#ifndef __PRIVATE_ECHOE
#ifdef __ECHOE
#define __PRIVATE_ECHOE   __ECHOE
#else /* __ECHOE */
#define __PRIVATE_ECHOE   0
#endif /* !__ECHOE */
#endif /* !__PRIVATE_ECHOE */
#ifndef __PRIVATE_ECHOKE
#ifdef __ECHOKE
#define __PRIVATE_ECHOKE  __ECHOKE
#else /* __ECHOKE */
#define __PRIVATE_ECHOKE  0
#endif /* !__ECHOKE */
#endif /* !__PRIVATE_ECHOKE */
#ifndef __PRIVATE_ECHOCTL
#ifdef __ECHOCTL
#define __PRIVATE_ECHOCTL __ECHOCTL
#else /* __ECHOCTL */
#define __PRIVATE_ECHOCTL 0
#endif /* !__ECHOCTL */
#endif /* !__PRIVATE_ECHOCTL */
#ifndef __PRIVATE_ECHOK
#ifdef __ECHOK
#define __PRIVATE_ECHOK   __ECHOK
#else /* __ECHOK */
#define __PRIVATE_ECHOK   0
#endif /* !__ECHOK */
#endif /* !__PRIVATE_ECHOK */
#ifndef __PRIVATE_TOSTOP
#ifdef __TOSTOP
#define __PRIVATE_TOSTOP  __TOSTOP
#else /* __TOSTOP */
#define __PRIVATE_TOSTOP  0
#endif /* !__TOSTOP */
#endif /* !__PRIVATE_TOSTOP */
#define __TTYDEF_LFLAG                                                       \
	(__PRIVATE_ECHO | __PRIVATE_ICANON | __PRIVATE_ISIG |                    \
	 __PRIVATE_IEXTEN | __PRIVATE_ECHOE | __PRIVATE_ECHOKE |                 \
	 __PRIVATE_ECHOCTL | /* These last two, linux doesn't enable by default, \
	                      * but I see no reason why one shouldn't! */        \
	 __PRIVATE_ECHOK | __PRIVATE_TOSTOP)
#endif /* !__TTYDEF_LFLAG */

#ifndef __TTYDEF_CFLAG
#ifndef __PRIVATE_CREAD
#ifdef __CREAD
#define __PRIVATE_CREAD  __CREAD
#else /* __CREAD */
#define __PRIVATE_CREAD  0
#endif /* !__CREAD */
#endif /* !__PRIVATE_CREAD */
#ifndef __PRIVATE_CS8
#ifdef __CS8
#define __PRIVATE_CS8  __CS8
#else /* __CS8 */
#define __PRIVATE_CS8  0
#endif /* !__CS8 */
#endif /* !__PRIVATE_CS8 */
#ifndef __PRIVATE_PARENB
#ifdef __PARENB
#define __PRIVATE_PARENB  __PARENB
#else /* __PARENB */
#define __PRIVATE_PARENB  0
#endif /* !__PARENB */
#endif /* !__PRIVATE_PARENB */
#ifndef __PRIVATE_HUPCL
#ifdef __HUPCL
#define __PRIVATE_HUPCL  __HUPCL
#else /* __HUPCL */
#define __PRIVATE_HUPCL  0
#endif /* !__HUPCL */
#endif /* !__PRIVATE_HUPCL */
#define __TTYDEF_CFLAG                                      \
	(__PRIVATE_CREAD | __PRIVATE_PARENB | __PRIVATE_HUPCL | \
	 __PRIVATE_CS8 /* | CS7 * Get with the times! Characters are now 8-bit! Unicode FTW! */)
#endif /* !__TTYDEF_CFLAG */


#ifndef __TTYDEF_SPEED
#ifdef __B9600
#define __TTYDEF_SPEED __B9600
#endif /* __B9600 */
#endif /* !__TTYDEF_SPEED */


#endif /* !_ASM_OS_TERMIOS_H */
