/* HASH CRC-32:0x66830351 */
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
#ifndef __local_cfmakesane_defined
#define __local_cfmakesane_defined
#include <__crt.h>
#include <bits/os/termios.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_bzero_defined
#define __local___localdep_bzero_defined
#ifdef __CRT_HAVE_bzero
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_OUTS(1, 2),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE___bzero)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_OUTS(1, 2),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),__bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE_explicit_bzero)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_OUTS(1, 2),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),explicit_bzero,(__dst,__num_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/bzero.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_bzero __LIBC_LOCAL_NAME(bzero)
#endif /* !... */
#endif /* !__local___localdep_bzero_defined */
__NAMESPACE_LOCAL_END
#include <bits/posix_opt.h>
#include <asm/os/termios.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(cfmakesane) __ATTR_OUT(1) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(cfmakesane))(struct termios *__restrict __termios_p) {
	/* Default everything to ZERO */
	(__NAMESPACE_LOCAL_SYM __localdep_bzero)(__termios_p, sizeof(*__termios_p));

	/* Set sane flag values. */
#if defined(__TTYDEF_CFLAG) && __TTYDEF_CFLAG
	__termios_p->c_cflag  = __TTYDEF_CFLAG;
#endif /* __TTYDEF_CFLAG && __TTYDEF_CFLAG */
#if defined(__TTYDEF_IFLAG) && __TTYDEF_IFLAG
	__termios_p->c_iflag  = __TTYDEF_IFLAG;
#endif /* __TTYDEF_IFLAG && __TTYDEF_IFLAG */
#if defined(__TTYDEF_LFLAG) && __TTYDEF_LFLAG
	__termios_p->c_lflag  = __TTYDEF_LFLAG;
#endif /* __TTYDEF_LFLAG && __TTYDEF_LFLAG */
#if defined(__TTYDEF_OFLAG) && __TTYDEF_OFLAG
	__termios_p->c_oflag  = __TTYDEF_OFLAG;
#endif /* __TTYDEF_OFLAG && __TTYDEF_OFLAG */
#if defined(__TTYDEF_SPEED) && __TTYDEF_SPEED
	__termios_p->c_ispeed = __TTYDEF_SPEED;
	__termios_p->c_ospeed = __TTYDEF_SPEED;
#endif /* __TTYDEF_SPEED && __TTYDEF_SPEED */

	/* ^C: Send SIGINT to the foreground process (requires `ISIG') */
#ifdef __VINTR
#ifdef __CINTR
	__termios_p->c_cc[__VINTR] = __CINTR;
#elif __VDISABLE
	__termios_p->c_cc[__VINTR] = __VDISABLE;
#endif /* ... */
#endif /* __VINTR */

	/* ^\: Send SIGQUIT to the foreground process (requires `ISIG') */
#ifdef __VQUIT
#ifdef __CQUIT
	__termios_p->c_cc[__VQUIT] = __CQUIT;
#elif __VDISABLE
	__termios_p->c_cc[__VQUIT] = __VDISABLE;
#endif /* ... */
#endif /* __VQUIT */

	/* ^H (aka. \b): Erase the last character from the input canon (requires `ECHOE') */
#ifdef __VERASE
#ifdef __CERASE
	__termios_p->c_cc[__VERASE] = __CERASE;
#elif __VDISABLE
	__termios_p->c_cc[__VERASE] = __VDISABLE;
#endif /* ... */
#endif /* __VERASE */

	/* ^U: Clear the entire input canon (requires `ECHOK') */
#ifdef __VKILL
#ifdef __CKILL
	__termios_p->c_cc[__VKILL] = __CKILL;
#elif __VDISABLE
	__termios_p->c_cc[__VKILL] = __VDISABLE;
#endif /* ... */
#endif /* __VKILL */

	/* ^D: Cause read(2) from the TTY to return 0 once (thus indicating input EOF) */
#ifdef __VEOF
#ifdef __CEOF
	__termios_p->c_cc[__VEOF] = __CEOF;
#elif __VDISABLE
	__termios_p->c_cc[__VEOF] = __VDISABLE;
#endif /* ... */
#endif /* __VEOF */

	/* ... */
#ifdef __VTIME
#ifdef __CTIME
	__termios_p->c_cc[__VTIME] = __CTIME;
#elif __VDISABLE
	__termios_p->c_cc[__VTIME] = __VDISABLE;
#endif /* ... */
#endif /* __VTIME */

	/* Minimum number of input bytes to-be returned by read(2) from the TTY */
#ifdef __VMIN
#ifdef __CMIN
	__termios_p->c_cc[__VMIN] = __CMIN;
#elif __VDISABLE
	__termios_p->c_cc[__VMIN] = __VDISABLE;
#endif /* ... */
#endif /* __VMIN */

	/* ... */
#ifdef __VSWTCH
#ifdef __CSWTCH
	__termios_p->c_cc[__VSWTCH] = __CSWTCH;
#elif __VDISABLE
	__termios_p->c_cc[__VSWTCH] = __VDISABLE;
#endif /* ... */
#endif /* __VSWTCH */

	/* ^Q: Restart stopped output (After VSTOP; causes pending TTY output to be flushed) */
#ifdef __VSTART
#ifdef __CSTART
	__termios_p->c_cc[__VSTART] = __CSTART;
#elif __VDISABLE
	__termios_p->c_cc[__VSTART] = __VDISABLE;
#endif /* ... */
#endif /* __VSTART */

	/* ^S: Suspend TTY display output until `VSTART' */
#ifdef __VSTOP
#ifdef __CSTOP
	__termios_p->c_cc[__VSTOP] = __CSTOP;
#elif __VDISABLE
	__termios_p->c_cc[__VSTOP] = __VDISABLE;
#endif /* ... */
#endif /* __VSTOP */

	/* ^Z: Send SIGTSTP to the foreground process (requires `ISIG') */
#ifdef __VSUSP
#ifdef __CSUSP
	__termios_p->c_cc[__VSUSP] = __CSUSP;
#elif __VDISABLE
	__termios_p->c_cc[__VSUSP] = __VDISABLE;
#endif /* ... */
#endif /* __VSUSP */

	/* \0: An additional end-of-line character used to flush the canon (by default, only \n is recognized) */
#ifdef __VEOL
#ifdef __CEOL
	__termios_p->c_cc[__VEOL] = __CEOL;
#elif __VDISABLE
	__termios_p->c_cc[__VEOL] = __VDISABLE;
#endif /* ... */
#endif /* __VEOL */

	/* ^R: Re-echo the current contents of the input canon (requires `IEXTEN') */
#ifdef __VREPRINT
#ifdef __CREPRINT
	__termios_p->c_cc[__VREPRINT] = __CREPRINT;
#elif __VDISABLE
	__termios_p->c_cc[__VREPRINT] = __VDISABLE;
#endif /* ... */
#endif /* __VREPRINT */

	/* <UNSUPPORTED> */
#ifdef __VDISCARD
#ifdef __CDISCARD
	__termios_p->c_cc[__VDISCARD] = __CDISCARD;
#elif __VDISABLE
	__termios_p->c_cc[__VDISCARD] = __VDISABLE;
#endif /* ... */
#endif /* __VDISCARD */

	/* ^W: Erase the last-written word (while (isspace(last)) erase(); while (!isspace(last)) erase()) (Requires `ECHOE' and `IEXTEN') */
#ifdef __VWERASE
#ifdef __CWERASE
	__termios_p->c_cc[__VWERASE] = __CWERASE;
#elif __VDISABLE
	__termios_p->c_cc[__VWERASE] = __VDISABLE;
#endif /* ... */
#endif /* __VWERASE */

	/* ^V: The next input character is escaped, in that any special meaning it would normally have is dismissed */
#ifdef __VLNEXT
#ifdef __CLNEXT
	__termios_p->c_cc[__VLNEXT] = __CLNEXT;
#elif __VDISABLE
	__termios_p->c_cc[__VLNEXT] = __VDISABLE;
#endif /* ... */
#endif /* __VLNEXT */

	/* \0: An additional end-of-line character used to flush the canon (by default, only \n is recognized) */
#ifdef __VEOL2
#ifdef __CEOL2
	__termios_p->c_cc[__VEOL2] = __CEOL2;
#elif __VDISABLE
	__termios_p->c_cc[__VEOL2] = __VDISABLE;
#endif /* ... */
#endif /* __VEOL2 */

	/* ... */
#ifdef __VDSUSP
#ifdef __CDSUSP
	__termios_p->c_cc[__VDSUSP] = __CDSUSP;
#elif __VDISABLE
	__termios_p->c_cc[__VDSUSP] = __VDISABLE;
#endif /* ... */
#endif /* __VDSUSP */

	/* ... */
#ifdef __VSTATUS
#ifdef __CSTATUS
	__termios_p->c_cc[__VSTATUS] = __CSTATUS;
#elif __VDISABLE
	__termios_p->c_cc[__VSTATUS] = __VDISABLE;
#endif /* ... */
#endif /* __VSTATUS */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_cfmakesane_defined
#define __local___localdep_cfmakesane_defined
#define __localdep_cfmakesane __LIBC_LOCAL_NAME(cfmakesane)
#endif /* !__local___localdep_cfmakesane_defined */
#endif /* !__local_cfmakesane_defined */
