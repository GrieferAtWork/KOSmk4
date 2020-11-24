/* HASH CRC-32:0x1081aab3 */
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
#include <bits/os/termios.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: memset from string */
#ifndef __local___localdep_memset_defined
#define __local___localdep_memset_defined 1
#ifdef __CRT_HAVE_memset
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* >> memset(3)
 * Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memset,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),memset,(__dst,__byte,__n_bytes))
#else /* __CRT_HAVE_memset */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memset.h>
__NAMESPACE_LOCAL_BEGIN
/* >> memset(3)
 * Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
#define __localdep_memset __LIBC_LOCAL_NAME(memset)
#endif /* !__CRT_HAVE_memset */
#endif /* !__local___localdep_memset_defined */
__NAMESPACE_LOCAL_END
#include <bits/posix_opt.h>
#include <asm/os/termios.h>
__NAMESPACE_LOCAL_BEGIN
/* >> cfmakesane(3)
 * Set ~sane~ mode for the given `termios_p' (out-only; meaning that `termios_p' gets initialized by this function)
 * Sane here refers to setting all values to their defaults, as they are defined in <sys/ttydefaults.h> */
__LOCAL_LIBC(cfmakesane) __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(cfmakesane))(struct termios *__restrict __termios_p) {
	/* Set sane values. */
	__localdep_memset(__termios_p, 0, sizeof(*__termios_p));
#ifdef __TTYDEF_CFLAG
	__termios_p->c_cflag  = __TTYDEF_CFLAG;
#endif /* __TTYDEF_CFLAG */
#ifdef __TTYDEF_IFLAG
	__termios_p->c_iflag  = __TTYDEF_IFLAG;
#endif /* __TTYDEF_IFLAG */
#ifdef __TTYDEF_LFLAG
	__termios_p->c_lflag  = __TTYDEF_LFLAG;
#endif /* __TTYDEF_LFLAG */
#ifdef __TTYDEF_OFLAG
	__termios_p->c_oflag  = __TTYDEF_OFLAG;
#endif /* __TTYDEF_OFLAG */
#ifdef __TTYDEF_SPEED
	__termios_p->c_ispeed = __TTYDEF_SPEED;
	__termios_p->c_ospeed = __TTYDEF_SPEED;
#endif /* __TTYDEF_SPEED */
#ifndef __VDISABLE
#define __VDISABLE '\0'
#endif /* !__VDISABLE */
#ifdef __VINTR
#ifdef __CINTR
	__termios_p->c_cc[__VINTR] = __CINTR;
#elif __VDISABLE
	__termios_p->c_cc[__VINTR] = __VDISABLE;
#endif /* ... */
#endif /* __VINTR */
#ifdef __VQUIT
#ifdef __CQUIT
	__termios_p->c_cc[__VQUIT] = __CQUIT;
#elif __VDISABLE
	__termios_p->c_cc[__VQUIT] = __VDISABLE;
#endif /* ... */
#endif /* __VQUIT */
#ifdef __VERASE
#ifdef __CERASE
	__termios_p->c_cc[__VERASE] = __CERASE;
#elif __VDISABLE
	__termios_p->c_cc[__VERASE] = __VDISABLE;
#endif /* ... */
#endif /* __VERASE */
#ifdef __VKILL
#ifdef __CKILL
	__termios_p->c_cc[__VKILL] = __CKILL;
#elif __VDISABLE
	__termios_p->c_cc[__VKILL] = __VDISABLE;
#endif /* ... */
#endif /* __VKILL */
#ifdef __VEOF
#ifdef __CEOF
	__termios_p->c_cc[__VEOF] = __CEOF;
#elif __VDISABLE
	__termios_p->c_cc[__VEOF] = __VDISABLE;
#endif /* ... */
#endif /* __VEOF */
#ifdef __VTIME
#ifdef __CTIME
	__termios_p->c_cc[__VTIME] = __CTIME;
#elif __VDISABLE
	__termios_p->c_cc[__VTIME] = __VDISABLE;
#endif /* ... */
#endif /* __VTIME */
#ifdef __VMIN
#ifdef __CMIN
	__termios_p->c_cc[__VMIN] = __CMIN;
#elif __VDISABLE
	__termios_p->c_cc[__VMIN] = __VDISABLE;
#endif /* ... */
#endif /* __VMIN */
#ifdef __VSWTCH
#ifdef __CSWTCH
	__termios_p->c_cc[__VSWTCH] = __CSWTCH;
#elif __VDISABLE
	__termios_p->c_cc[__VSWTCH] = __VDISABLE;
#endif /* ... */
#endif /* __VSWTCH */
#ifdef __VSTART
#ifdef __CSTART
	__termios_p->c_cc[__VSTART] = __CSTART;
#elif __VDISABLE
	__termios_p->c_cc[__VSTART] = __VDISABLE;
#endif /* ... */
#endif /* __VSTART */
#ifdef __VSTOP
#ifdef __CSTOP
	__termios_p->c_cc[__VSTOP] = __CSTOP;
#elif __VDISABLE
	__termios_p->c_cc[__VSTOP] = __VDISABLE;
#endif /* ... */
#endif /* __VSTOP */
#ifdef __VSUSP
#ifdef __CSUSP
	__termios_p->c_cc[__VSUSP] = __CSUSP;
#elif __VDISABLE
	__termios_p->c_cc[__VSUSP] = __VDISABLE;
#endif /* ... */
#endif /* __VSUSP */
#ifdef __VEOL
#ifdef __CEOL
	__termios_p->c_cc[__VEOL] = __CEOL;
#elif __VDISABLE
	__termios_p->c_cc[__VEOL] = __VDISABLE;
#endif /* ... */
#endif /* __VEOL */
#ifdef __VREPRINT
#ifdef __CREPRINT
	__termios_p->c_cc[__VREPRINT] = __CREPRINT;
#elif __VDISABLE
	__termios_p->c_cc[__VREPRINT] = __VDISABLE;
#endif /* ... */
#endif /* __VREPRINT */
#ifdef __VDISCARD
#ifdef __CDISCARD
	__termios_p->c_cc[__VDISCARD] = __CDISCARD;
#elif __VDISABLE
	__termios_p->c_cc[__VDISCARD] = __VDISABLE;
#endif /* ... */
#endif /* __VDISCARD */
#ifdef __VWERASE
#ifdef __CWERASE
	__termios_p->c_cc[__VWERASE] = __CWERASE;
#elif __VDISABLE
	__termios_p->c_cc[__VWERASE] = __VDISABLE;
#endif /* ... */
#endif /* __VWERASE */
#ifdef __VLNEXT
#ifdef __CLNEXT
	__termios_p->c_cc[__VLNEXT] = __CLNEXT;
#elif __VDISABLE
	__termios_p->c_cc[__VLNEXT] = __VDISABLE;
#endif /* ... */
#endif /* __VLNEXT */
#ifdef __VEOL2
#ifdef __CEOL2
	__termios_p->c_cc[__VEOL2] = __CEOL2;
#elif __VDISABLE
	__termios_p->c_cc[__VEOL2] = __VDISABLE;
#endif /* ... */
#endif /* __VEOL2 */
#ifdef __VDSUSP
#ifdef __CDSUSP
	__termios_p->c_cc[__VDSUSP] = __CDSUSP;
#elif __VDISABLE
	__termios_p->c_cc[__VDSUSP] = __VDISABLE;
#endif /* ... */
#endif /* __VDSUSP */
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
#define __local___localdep_cfmakesane_defined 1
#define __localdep_cfmakesane __LIBC_LOCAL_NAME(cfmakesane)
#endif /* !__local___localdep_cfmakesane_defined */
#endif /* !__local_cfmakesane_defined */
