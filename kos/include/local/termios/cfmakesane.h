/* HASH CRC-32:0x12c19255 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_cfmakesane_defined
#define __local_cfmakesane_defined 1
#include <__crt.h>
#include <bits/termios.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: memset from string */
#ifndef __local___localdep_memset_defined
#define __local___localdep_memset_defined 1
#ifdef __CRT_HAVE_memset
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memset,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),memset,(__dst,__byte,__n_bytes))
#else /* __CRT_HAVE_memset */
__NAMESPACE_LOCAL_END
#include <local/string/memset.h>
__NAMESPACE_LOCAL_BEGIN
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
#define __localdep_memset __LIBC_LOCAL_NAME(memset)
#endif /* !__CRT_HAVE_memset */
#endif /* !__local___localdep_memset_defined */
__NAMESPACE_LOCAL_END
#include <sys/ttydefaults.h>
__NAMESPACE_LOCAL_BEGIN
/* Set ~sane~ mode for the given `termios_p' (out-only; meaning that `termios_p' gets initialized by this function)
 * Sane here refers to setting all values to their defaults, as they are defined in <sys/ttydefaults.h> */
__LOCAL_LIBC(cfmakesane) __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(cfmakesane))(struct termios *__restrict __termios_p) {
	/* Set sane values. */
	__localdep_memset(__termios_p, 0, sizeof(*__termios_p));
#ifdef TTYDEF_CFLAG
	__termios_p->c_cflag  = TTYDEF_CFLAG;
#endif /* TTYDEF_CFLAG */
#ifdef TTYDEF_IFLAG
	__termios_p->c_iflag  = TTYDEF_IFLAG;
#endif /* TTYDEF_IFLAG */
#ifdef TTYDEF_LFLAG
	__termios_p->c_lflag  = TTYDEF_LFLAG;
#endif /* TTYDEF_LFLAG */
#ifdef TTYDEF_OFLAG
	__termios_p->c_oflag  = TTYDEF_OFLAG;
#endif /* TTYDEF_OFLAG */
#ifdef TTYDEF_SPEED
	__termios_p->c_ispeed = TTYDEF_SPEED;
	__termios_p->c_ospeed = TTYDEF_SPEED;
#endif /* TTYDEF_SPEED */
#ifndef _POSIX_VDISABLE
#define _POSIX_VDISABLE '\0'
#endif /* !condition */
#ifdef VINTR
#ifdef CINTR
	__termios_p->c_cc[VINTR] = CINTR;
#else /* CINTR */
	__termios_p->c_cc[VINTR] = _POSIX_VDISABLE;
#endif /* !CINTR */
#endif /* VINTR */
#ifdef VQUIT
#ifdef CQUIT
	__termios_p->c_cc[VQUIT] = CQUIT;
#else /* CQUIT */
	__termios_p->c_cc[VQUIT] = _POSIX_VDISABLE;
#endif /* !CQUIT */
#endif /* VQUIT */
#ifdef VERASE
#ifdef CERASE
	__termios_p->c_cc[VERASE] = CERASE;
#else /* CERASE */
	__termios_p->c_cc[VERASE] = _POSIX_VDISABLE;
#endif /* !CERASE */
#endif /* VERASE */
#ifdef VKILL
#ifdef CKILL
	__termios_p->c_cc[VKILL] = CKILL;
#else /* CKILL */
	__termios_p->c_cc[VKILL] = _POSIX_VDISABLE;
#endif /* !CKILL */
#endif /* VKILL */
#ifdef VEOF
#ifdef CEOF
	__termios_p->c_cc[VEOF] = CEOF;
#else /* CEOF */
	__termios_p->c_cc[VEOF] = _POSIX_VDISABLE;
#endif /* !CEOF */
#endif /* VEOF */
#ifdef VTIME
#ifdef CTIME
	__termios_p->c_cc[VTIME] = CTIME;
#else /* CTIME */
	__termios_p->c_cc[VTIME] = _POSIX_VDISABLE;
#endif /* !CTIME */
#endif /* VTIME */
#ifdef VMIN
#ifdef CMIN
	__termios_p->c_cc[VMIN] = CMIN;
#else /* CMIN */
	__termios_p->c_cc[VMIN] = _POSIX_VDISABLE;
#endif /* !CMIN */
#endif /* VMIN */
#ifdef VSWTCH
#ifdef CSWTCH
	__termios_p->c_cc[VSWTCH] = CSWTCH;
#else /* CSWTCH */
	__termios_p->c_cc[VSWTCH] = _POSIX_VDISABLE;
#endif /* !CSWTCH */
#endif /* VSWTCH */
#ifdef VSTART
#ifdef CSTART
	__termios_p->c_cc[VSTART] = CSTART;
#else /* CSTART */
	__termios_p->c_cc[VSTART] = _POSIX_VDISABLE;
#endif /* !CSTART */
#endif /* VSTART */
#ifdef VSTOP
#ifdef CSTOP
	__termios_p->c_cc[VSTOP] = CSTOP;
#else /* CSTOP */
	__termios_p->c_cc[VSTOP] = _POSIX_VDISABLE;
#endif /* !CSTOP */
#endif /* VSTOP */
#ifdef VSUSP
#ifdef CSUSP
	__termios_p->c_cc[VSUSP] = CSUSP;
#else /* CSUSP */
	__termios_p->c_cc[VSUSP] = _POSIX_VDISABLE;
#endif /* !CSUSP */
#endif /* VSUSP */
#ifdef VEOL
#ifdef CEOL
	__termios_p->c_cc[VEOL] = CEOL;
#else /* CEOL */
	__termios_p->c_cc[VEOL] = _POSIX_VDISABLE;
#endif /* !CEOL */
#endif /* VEOL */
#ifdef VREPRINT
#ifdef CREPRINT
	__termios_p->c_cc[VREPRINT] = CREPRINT;
#else /* CREPRINT */
	__termios_p->c_cc[VREPRINT] = _POSIX_VDISABLE;
#endif /* !CREPRINT */
#endif /* VREPRINT */
#ifdef VDISCARD
#ifdef CDISCARD
	__termios_p->c_cc[VDISCARD] = CDISCARD;
#else /* CDISCARD */
	__termios_p->c_cc[VDISCARD] = _POSIX_VDISABLE;
#endif /* !CDISCARD */
#endif /* VDISCARD */
#ifdef VWERASE
#ifdef CWERASE
	__termios_p->c_cc[VWERASE] = CWERASE;
#else /* CWERASE */
	__termios_p->c_cc[VWERASE] = _POSIX_VDISABLE;
#endif /* !CWERASE */
#endif /* VWERASE */
#ifdef VLNEXT
#ifdef CLNEXT
	__termios_p->c_cc[VLNEXT] = CLNEXT;
#else /* CLNEXT */
	__termios_p->c_cc[VLNEXT] = _POSIX_VDISABLE;
#endif /* !CLNEXT */
#endif /* VLNEXT */
#ifdef VEOL2
#ifdef CEOL2
	__termios_p->c_cc[VEOL2] = CEOL2;
#else /* CEOL2 */
	__termios_p->c_cc[VEOL2] = _POSIX_VDISABLE;
#endif /* !CEOL2 */
#endif /* VEOL2 */
#ifdef VDSUSP
#ifdef CDSUSP
	__termios_p->c_cc[VDSUSP] = CDSUSP;
#else /* CDSUSP */
	__termios_p->c_cc[VDSUSP] = _POSIX_VDISABLE;
#endif /* !CDSUSP */
#endif /* VDSUSP */
#ifdef VSTATUS
#ifdef CSTATUS
	__termios_p->c_cc[VSTATUS] = CSTATUS;
#else /* CSTATUS */
	__termios_p->c_cc[VSTATUS] = _POSIX_VDISABLE;
#endif /* !CSTATUS */
#endif /* VSTATUS */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_cfmakesane_defined
#define __local___localdep_cfmakesane_defined 1
#define __localdep_cfmakesane __LIBC_LOCAL_NAME(cfmakesane)
#endif /* !__local___localdep_cfmakesane_defined */
#endif /* !__local_cfmakesane_defined */
