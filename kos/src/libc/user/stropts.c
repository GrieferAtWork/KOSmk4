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
#ifndef GUARD_LIBC_USER_STROPTS_C
#define GUARD_LIBC_USER_STROPTS_C 1

#include "../api.h"
#include "stropts.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:libc_isastream,hash:CRC-32=0x2908900d]]]*/
/* Test whether FILDES is associated with a STREAM-based file */
INTERN ATTR_SECTION(".text.crt.io.stropts") int
NOTHROW(LIBCCALL libc_isastream)(fd_t fildes)
/*[[[body:libc_isastream]]]*/
/*AUTO*/{
	(void)fildes;
	CRT_UNIMPLEMENTED("isastream"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_isastream]]]*/

/*[[[head:libc_getmsg,hash:CRC-32=0xc1af7690]]]*/
/* Receive next message from a STREAMS file */
INTERN ATTR_SECTION(".text.crt.io.stropts") int
NOTHROW_RPC(LIBCCALL libc_getmsg)(fd_t fildes,
                                  struct strbuf *__restrict ctlptr,
                                  struct strbuf *__restrict dataptr,
                                  int *__restrict flagsp)
/*[[[body:libc_getmsg]]]*/
/*AUTO*/{
	(void)fildes;
	(void)ctlptr;
	(void)dataptr;
	(void)flagsp;
	CRT_UNIMPLEMENTED("getmsg"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getmsg]]]*/

/*[[[head:libc_getpmsg,hash:CRC-32=0x62b6f1a7]]]*/
/* Receive next message from a STREAMS file, with *FLAGSP allowing to control which message. */
INTERN ATTR_SECTION(".text.crt.io.stropts") int
NOTHROW_RPC(LIBCCALL libc_getpmsg)(fd_t fildes,
                                   struct strbuf *__restrict ctlptr,
                                   struct strbuf *__restrict dataptr,
                                   int *__restrict bandp,
                                   int *__restrict flagsp)
/*[[[body:libc_getpmsg]]]*/
/*AUTO*/{
	(void)fildes;
	(void)ctlptr;
	(void)dataptr;
	(void)bandp;
	(void)flagsp;
	CRT_UNIMPLEMENTED("getpmsg"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getpmsg]]]*/

/*[[[head:libc_putmsg,hash:CRC-32=0x561a26e3]]]*/
/* Send a message on a STREAM */
INTERN ATTR_SECTION(".text.crt.io.stropts") int
NOTHROW_RPC(LIBCCALL libc_putmsg)(fd_t fildes,
                                  struct strbuf const *ctlptr,
                                  struct strbuf const *dataptr,
                                  int flags)
/*[[[body:libc_putmsg]]]*/
/*AUTO*/{
	(void)fildes;
	(void)ctlptr;
	(void)dataptr;
	(void)flags;
	CRT_UNIMPLEMENTED("putmsg"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_putmsg]]]*/

/*[[[head:libc_putpmsg,hash:CRC-32=0x8d496aef]]]*/
/* Send a message on a STREAM to the BAND */
INTERN ATTR_SECTION(".text.crt.io.stropts") int
NOTHROW_RPC(LIBCCALL libc_putpmsg)(fd_t fildes,
                                   struct strbuf const *ctlptr,
                                   struct strbuf const *dataptr,
                                   int band,
                                   int flags)
/*[[[body:libc_putpmsg]]]*/
/*AUTO*/{
	(void)fildes;
	(void)ctlptr;
	(void)dataptr;
	(void)band;
	(void)flags;
	CRT_UNIMPLEMENTED("putpmsg"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_putpmsg]]]*/

/*[[[head:libc_fattach,hash:CRC-32=0x4412fa6b]]]*/
/* Attach a STREAMS-based file descriptor FILDES to a file PATH in the file system name space */
INTERN ATTR_SECTION(".text.crt.io.stropts") NONNULL((2)) int
NOTHROW_RPC_KOS(LIBCCALL libc_fattach)(fd_t fildes,
                                       char const *__restrict path)
/*[[[body:libc_fattach]]]*/
/*AUTO*/{
	(void)fildes;
	(void)path;
	CRT_UNIMPLEMENTED("fattach"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_fattach]]]*/

/*[[[head:libc_fdetach,hash:CRC-32=0xa9c32b13]]]*/
/* Detach a name PATH from a STREAMS-based file descriptor */
INTERN ATTR_SECTION(".text.crt.io.stropts") NONNULL((1)) int
NOTHROW_RPC_KOS(LIBCCALL libc_fdetach)(char const *__restrict path)
/*[[[body:libc_fdetach]]]*/
/*AUTO*/{
	(void)path;
	CRT_UNIMPLEMENTED("fdetach"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_fdetach]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x6ef1e8e1]]]*/
DEFINE_PUBLIC_ALIAS(isastream, libc_isastream);
DEFINE_PUBLIC_ALIAS(getmsg, libc_getmsg);
DEFINE_PUBLIC_ALIAS(getpmsg, libc_getpmsg);
DEFINE_PUBLIC_ALIAS(putmsg, libc_putmsg);
DEFINE_PUBLIC_ALIAS(putpmsg, libc_putpmsg);
DEFINE_PUBLIC_ALIAS(fattach, libc_fattach);
DEFINE_PUBLIC_ALIAS(fdetach, libc_fdetach);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_STROPTS_C */
