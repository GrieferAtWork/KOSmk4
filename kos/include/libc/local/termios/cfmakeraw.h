/* HASH CRC-32:0x6be1a0e4 */
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
#ifndef __local_cfmakeraw_defined
#define __local_cfmakeraw_defined
#include <__crt.h>
#include <bits/os/termios.h>
#include <asm/os/termios.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(cfmakeraw) __ATTR_ACCESS_RW(1) void
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
	local head = "termios_p->@{}@ {}(" .format({ field, add ? "|= " : "&= ~" });
	print("	", head, "0");
	head = " " * #head;
	for (local f: flags) {
		print("@@pp_ifdef __", f, "@@");
		print("	", head, "| __", f);
		print("@@pp_endif@@");
	}
	print("	", head, ");");
	print("@@pp_endif@@");
	print;
}
]]]*/
	/* c_iflag (remove) */
#if defined(__IGNBRK) || defined(__BRKINT) || defined(__PARMRK) || defined(__ISTRIP) || defined(__INLCR) || defined(__IGNCR) || defined(__ICRNL) || defined(__IXON) || defined(__IXOFF)
	__termios_p->c_iflag &= ~(0
#ifdef __IGNBRK
	                          | __IGNBRK
#endif /* __IGNBRK */
#ifdef __BRKINT
	                          | __BRKINT
#endif /* __BRKINT */
#ifdef __PARMRK
	                          | __PARMRK
#endif /* __PARMRK */
#ifdef __ISTRIP
	                          | __ISTRIP
#endif /* __ISTRIP */
#ifdef __INLCR
	                          | __INLCR
#endif /* __INLCR */
#ifdef __IGNCR
	                          | __IGNCR
#endif /* __IGNCR */
#ifdef __ICRNL
	                          | __ICRNL
#endif /* __ICRNL */
#ifdef __IXON
	                          | __IXON
#endif /* __IXON */
#ifdef __IXOFF
	                          | __IXOFF
#endif /* __IXOFF */
	                          );
#endif /* __IGNBRK || __BRKINT || __PARMRK || __ISTRIP || __INLCR || __IGNCR || __ICRNL || __IXON || __IXOFF */

	/* c_oflag (remove) */
#ifdef __OPOST
	__termios_p->c_oflag &= ~(0

	                          | __OPOST

	                          );
#endif /* __OPOST */

	/* c_lflag (remove) */
#if defined(__ECHO) || defined(__ECHONL) || defined(__ICANON) || defined(__ISIG) || defined(__IEXTEN)
	__termios_p->c_lflag &= ~(0
#ifdef __ECHO
	                          | __ECHO
#endif /* __ECHO */
#ifdef __ECHONL
	                          | __ECHONL
#endif /* __ECHONL */
#ifdef __ICANON
	                          | __ICANON
#endif /* __ICANON */
#ifdef __ISIG
	                          | __ISIG
#endif /* __ISIG */
#ifdef __IEXTEN
	                          | __IEXTEN
#endif /* __IEXTEN */
	                          );
#endif /* __ECHO || __ECHONL || __ICANON || __ISIG || __IEXTEN */

	/* c_cflag (remove) */
#if defined(__CSIZE) || defined(__PARENB)
	__termios_p->c_cflag &= ~(0
#ifdef __CSIZE
	                          | __CSIZE
#endif /* __CSIZE */
#ifdef __PARENB
	                          | __PARENB
#endif /* __PARENB */
	                          );
#endif /* __CSIZE || __PARENB */

	/* c_cflag (addend) */
#if defined(__CS8) || defined(__CREAD)
	__termios_p->c_cflag |= (0
#ifdef __CS8
	                         | __CS8
#endif /* __CS8 */
#ifdef __CREAD
	                         | __CREAD
#endif /* __CREAD */
	                         );
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
#define __local___localdep_cfmakeraw_defined
#define __localdep_cfmakeraw __LIBC_LOCAL_NAME(cfmakeraw)
#endif /* !__local___localdep_cfmakeraw_defined */
#endif /* !__local_cfmakeraw_defined */
