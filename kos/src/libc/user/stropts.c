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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
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

/*[[[head:isastream,hash:CRC-32=0x14bf4ed9]]]*/
/* Test whether FILDES is associated with a STREAM-based file */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.io.stropts.isastream") int
NOTHROW(LIBCCALL libc_isastream)(fd_t fildes)
/*[[[body:isastream]]]*/
{
	(void)fildes;
	CRT_UNIMPLEMENTED("isastream"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:isastream]]]*/

/*[[[head:getmsg,hash:CRC-32=0x98a0cdc9]]]*/
/* Receive next message from a STREAMS file */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.io.stropts.getmsg") int
NOTHROW_RPC(LIBCCALL libc_getmsg)(fd_t fildes,
                                  struct strbuf *__restrict ctlptr,
                                  struct strbuf *__restrict dataptr,
                                  int *__restrict flagsp)
/*[[[body:getmsg]]]*/
{
	(void)fildes;
	(void)ctlptr;
	(void)dataptr;
	(void)flagsp;
	CRT_UNIMPLEMENTED("getmsg"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getmsg]]]*/

/*[[[head:getpmsg,hash:CRC-32=0x33a8bb65]]]*/
/* Receive next message from a STREAMS file, with *FLAGSP allowing to control which message. */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.io.stropts.getpmsg") int
NOTHROW_RPC(LIBCCALL libc_getpmsg)(fd_t fildes,
                                   struct strbuf *__restrict ctlptr,
                                   struct strbuf *__restrict dataptr,
                                   int *__restrict bandp,
                                   int *__restrict flagsp)
/*[[[body:getpmsg]]]*/
{
	(void)fildes;
	(void)ctlptr;
	(void)dataptr;
	(void)bandp;
	(void)flagsp;
	CRT_UNIMPLEMENTED("getpmsg"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getpmsg]]]*/

/*[[[head:putmsg,hash:CRC-32=0xdaa1b657]]]*/
/* Send a message on a STREAM */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.io.stropts.putmsg") int
NOTHROW_RPC(LIBCCALL libc_putmsg)(fd_t fildes,
                                  struct strbuf const *ctlptr,
                                  struct strbuf const *dataptr,
                                  int flags)
/*[[[body:putmsg]]]*/
{
	(void)fildes;
	(void)ctlptr;
	(void)dataptr;
	(void)flags;
	CRT_UNIMPLEMENTED("putmsg"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:putmsg]]]*/

/*[[[head:putpmsg,hash:CRC-32=0xa58cbaf0]]]*/
/* Send a message on a STREAM to the BAND */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.io.stropts.putpmsg") int
NOTHROW_RPC(LIBCCALL libc_putpmsg)(fd_t fildes,
                                   struct strbuf const *ctlptr,
                                   struct strbuf const *dataptr,
                                   int band,
                                   int flags)
/*[[[body:putpmsg]]]*/
{
	(void)fildes;
	(void)ctlptr;
	(void)dataptr;
	(void)band;
	(void)flags;
	CRT_UNIMPLEMENTED("putpmsg"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:putpmsg]]]*/

/*[[[head:fattach,hash:CRC-32=0x2de49da0]]]*/
/* Attach a STREAMS-based file descriptor FILDES to a file PATH in the file system name space */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.io.stropts.fattach") int
NOTHROW_RPC_KOS(LIBCCALL libc_fattach)(fd_t fildes,
                                       char const *__restrict path)
/*[[[body:fattach]]]*/
{
	(void)fildes;
	(void)path;
	CRT_UNIMPLEMENTED("fattach"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:fattach]]]*/

/*[[[head:fdetach,hash:CRC-32=0x5aeea7f8]]]*/
/* Detach a name PATH from a STREAMS-based file descriptor */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.io.stropts.fdetach") int
NOTHROW_RPC_KOS(LIBCCALL libc_fdetach)(char const *__restrict path)
/*[[[body:fdetach]]]*/
{
	(void)path;
	CRT_UNIMPLEMENTED("fdetach"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:fdetach]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x5fc1307c]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(isastream, libc_isastream);
DEFINE_PUBLIC_WEAK_ALIAS(getmsg, libc_getmsg);
DEFINE_PUBLIC_WEAK_ALIAS(getpmsg, libc_getpmsg);
DEFINE_PUBLIC_WEAK_ALIAS(putmsg, libc_putmsg);
DEFINE_PUBLIC_WEAK_ALIAS(putpmsg, libc_putpmsg);
DEFINE_PUBLIC_WEAK_ALIAS(fattach, libc_fattach);
DEFINE_PUBLIC_WEAK_ALIAS(fdetach, libc_fdetach);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_STROPTS_C */
