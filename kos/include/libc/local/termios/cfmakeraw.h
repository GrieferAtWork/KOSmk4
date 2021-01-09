/* HASH CRC-32:0xbab399e4 */
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
#ifndef __local_cfmakeraw_defined
#define __local_cfmakeraw_defined 1
#include <__crt.h>
#include <bits/os/termios.h>
#include <asm/os/termios.h>
__NAMESPACE_LOCAL_BEGIN
/* >> cfmakeraw(3)
 * Set ~raw~ mode for the given `termios_p' (in/out; meaning that `termios_p' must already be initialized)
 * This entails the CANON and all control characters being disabled, as well as
 * any sort of input/output text processing no longer taking place. */
__LOCAL_LIBC(cfmakeraw) __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(cfmakeraw))(struct termios *__restrict __termios_p) {
	/* As documented here: http://man7.org/linux/man-pages/man3/termios.3.html
	 * Note that the following additions were made:
	 *  - Clear `IXOFF' (ensuring that TTY output can be streamed)
	 *  - Always set `CREAD' (ensuring that data can be received) */

/*[[[deemon
local ops = {
	("c_iflag", false, ["IGNBRK", "BRKINT", "PARMRK", "ISTRIP", "INLCR", "IGNCR", "ICRNL", "IXON", "IXOFF"]),
	("c_oflag", false, ["OPOST"]),
	("c_lflag", false, ["ECHO", "ECHONL", "ICANON", "ISIG", "IEXTEN"]),
	("c_cflag", false, ["CSIZE", "PARENB"]),
	("c_cflag", true,  ["CS8", "CREAD"]),
};
for (local field, add, flags: ops) {
	print("	/" "* ", field, " (", add ? "addend" : "remove", ")", " *" "/");
	print("@@pp_if "),;
	print(" || ".join(for (local f: flags) "defined(__" + f + ")"), "@@");
	for (local f: flags) {
		print("@@pp_ifndef __PRIVATE_", f, "@@");
		print("@@pp_ifdef __", f, "@@");
		print("#define __PRIVATE_", f, " __", f);
		print("@@pp_else@@");
		print("#define __PRIVATE_", f, " 0");
		print("@@pp_endif@@");
		print("@@pp_endif@@");
	}
	print("	termios_p->@", field, "@ ", add ? "|= " : "&= ~", "("),;
	print(" | ".join(for (local f: flags) "__PRIVATE_" + f), ");");
	print("@@pp_endif@@");
	print;
}
]]]*/
	/* c_iflag (remove) */
#if defined(__IGNBRK) || defined(__BRKINT) || defined(__PARMRK) || defined(__ISTRIP) || defined(__INLCR) || defined(__IGNCR) || defined(__ICRNL) || defined(__IXON) || defined(__IXOFF)
#ifndef __PRIVATE_IGNBRK
#ifdef __IGNBRK
#define __PRIVATE_IGNBRK __IGNBRK
#else /* __IGNBRK */
#define __PRIVATE_IGNBRK 0
#endif /* !__IGNBRK */
#endif /* !__PRIVATE_IGNBRK */
#ifndef __PRIVATE_BRKINT
#ifdef __BRKINT
#define __PRIVATE_BRKINT __BRKINT
#else /* __BRKINT */
#define __PRIVATE_BRKINT 0
#endif /* !__BRKINT */
#endif /* !__PRIVATE_BRKINT */
#ifndef __PRIVATE_PARMRK
#ifdef __PARMRK
#define __PRIVATE_PARMRK __PARMRK
#else /* __PARMRK */
#define __PRIVATE_PARMRK 0
#endif /* !__PARMRK */
#endif /* !__PRIVATE_PARMRK */
#ifndef __PRIVATE_ISTRIP
#ifdef __ISTRIP
#define __PRIVATE_ISTRIP __ISTRIP
#else /* __ISTRIP */
#define __PRIVATE_ISTRIP 0
#endif /* !__ISTRIP */
#endif /* !__PRIVATE_ISTRIP */
#ifndef __PRIVATE_INLCR
#ifdef __INLCR
#define __PRIVATE_INLCR __INLCR
#else /* __INLCR */
#define __PRIVATE_INLCR 0
#endif /* !__INLCR */
#endif /* !__PRIVATE_INLCR */
#ifndef __PRIVATE_IGNCR
#ifdef __IGNCR
#define __PRIVATE_IGNCR __IGNCR
#else /* __IGNCR */
#define __PRIVATE_IGNCR 0
#endif /* !__IGNCR */
#endif /* !__PRIVATE_IGNCR */
#ifndef __PRIVATE_ICRNL
#ifdef __ICRNL
#define __PRIVATE_ICRNL __ICRNL
#else /* __ICRNL */
#define __PRIVATE_ICRNL 0
#endif /* !__ICRNL */
#endif /* !__PRIVATE_ICRNL */
#ifndef __PRIVATE_IXON
#ifdef __IXON
#define __PRIVATE_IXON __IXON
#else /* __IXON */
#define __PRIVATE_IXON 0
#endif /* !__IXON */
#endif /* !__PRIVATE_IXON */
#ifndef __PRIVATE_IXOFF
#ifdef __IXOFF
#define __PRIVATE_IXOFF __IXOFF
#else /* __IXOFF */
#define __PRIVATE_IXOFF 0
#endif /* !__IXOFF */
#endif /* !__PRIVATE_IXOFF */
	__termios_p->c_iflag &= ~(__PRIVATE_IGNBRK | __PRIVATE_BRKINT | __PRIVATE_PARMRK | __PRIVATE_ISTRIP | __PRIVATE_INLCR | __PRIVATE_IGNCR | __PRIVATE_ICRNL | __PRIVATE_IXON | __PRIVATE_IXOFF);
#endif /* __IGNBRK || __BRKINT || __PARMRK || __ISTRIP || __INLCR || __IGNCR || __ICRNL || __IXON || __IXOFF */

	/* c_oflag (remove) */
#ifdef __OPOST
#ifndef __PRIVATE_OPOST

#define __PRIVATE_OPOST __OPOST



#endif /* !__PRIVATE_OPOST */
	__termios_p->c_oflag &= ~(__PRIVATE_OPOST);
#endif /* __OPOST */

	/* c_lflag (remove) */
#if defined(__ECHO) || defined(__ECHONL) || defined(__ICANON) || defined(__ISIG) || defined(__IEXTEN)
#ifndef __PRIVATE_ECHO
#ifdef __ECHO
#define __PRIVATE_ECHO __ECHO
#else /* __ECHO */
#define __PRIVATE_ECHO 0
#endif /* !__ECHO */
#endif /* !__PRIVATE_ECHO */
#ifndef __PRIVATE_ECHONL
#ifdef __ECHONL
#define __PRIVATE_ECHONL __ECHONL
#else /* __ECHONL */
#define __PRIVATE_ECHONL 0
#endif /* !__ECHONL */
#endif /* !__PRIVATE_ECHONL */
#ifndef __PRIVATE_ICANON
#ifdef __ICANON
#define __PRIVATE_ICANON __ICANON
#else /* __ICANON */
#define __PRIVATE_ICANON 0
#endif /* !__ICANON */
#endif /* !__PRIVATE_ICANON */
#ifndef __PRIVATE_ISIG
#ifdef __ISIG
#define __PRIVATE_ISIG __ISIG
#else /* __ISIG */
#define __PRIVATE_ISIG 0
#endif /* !__ISIG */
#endif /* !__PRIVATE_ISIG */
#ifndef __PRIVATE_IEXTEN
#ifdef __IEXTEN
#define __PRIVATE_IEXTEN __IEXTEN
#else /* __IEXTEN */
#define __PRIVATE_IEXTEN 0
#endif /* !__IEXTEN */
#endif /* !__PRIVATE_IEXTEN */
	__termios_p->c_lflag &= ~(__PRIVATE_ECHO | __PRIVATE_ECHONL | __PRIVATE_ICANON | __PRIVATE_ISIG | __PRIVATE_IEXTEN);
#endif /* __ECHO || __ECHONL || __ICANON || __ISIG || __IEXTEN */

	/* c_cflag (remove) */
#if defined(__CSIZE) || defined(__PARENB)
#ifndef __PRIVATE_CSIZE
#ifdef __CSIZE
#define __PRIVATE_CSIZE __CSIZE
#else /* __CSIZE */
#define __PRIVATE_CSIZE 0
#endif /* !__CSIZE */
#endif /* !__PRIVATE_CSIZE */
#ifndef __PRIVATE_PARENB
#ifdef __PARENB
#define __PRIVATE_PARENB __PARENB
#else /* __PARENB */
#define __PRIVATE_PARENB 0
#endif /* !__PARENB */
#endif /* !__PRIVATE_PARENB */
	__termios_p->c_cflag &= ~(__PRIVATE_CSIZE | __PRIVATE_PARENB);
#endif /* __CSIZE || __PARENB */

	/* c_cflag (addend) */
#if defined(__CS8) || defined(__CREAD)
#ifndef __PRIVATE_CS8
#ifdef __CS8
#define __PRIVATE_CS8 __CS8
#else /* __CS8 */
#define __PRIVATE_CS8 0
#endif /* !__CS8 */
#endif /* !__PRIVATE_CS8 */
#ifndef __PRIVATE_CREAD
#ifdef __CREAD
#define __PRIVATE_CREAD __CREAD
#else /* __CREAD */
#define __PRIVATE_CREAD 0
#endif /* !__CREAD */
#endif /* !__PRIVATE_CREAD */
	__termios_p->c_cflag |= (__PRIVATE_CS8 | __PRIVATE_CREAD);
#endif /* __CS8 || __CREAD */
/*[[[end]]]*/

	/* c_cc[VMIN] */
#ifdef __VMIN
#ifdef __CMIN
	__termios_p->c_cc[__VMIN] = __CMIN;
#else /* __CMIN */
	__termios_p->c_cc[__VMIN] = 1; /* Read returns when one byte was read. */
#endif /* !__CMIN */
#endif /* __VMIN */

	/* c_cc[VTIME] */
#ifdef __VTIME
#ifdef __CTIME
	__termios_p->c_cc[__VTIME] = __CTIME;
#else /* __CTIME */
	__termios_p->c_cc[__VTIME] = 0;
#endif /* !__CTIME */
#endif /* __VTIME */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_cfmakeraw_defined
#define __local___localdep_cfmakeraw_defined 1
#define __localdep_cfmakeraw __LIBC_LOCAL_NAME(cfmakeraw)
#endif /* !__local___localdep_cfmakeraw_defined */
#endif /* !__local_cfmakeraw_defined */
