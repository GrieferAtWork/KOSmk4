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
#ifndef GUARD_LIBC_USER_STROPTS_C
#define GUARD_LIBC_USER_STROPTS_C 1

#include "../api.h"
#include "stropts.h"

DECL_BEGIN

/*[[[head:libc_isastream,hash:CRC-32=0x195903e8]]]*/
INTERN ATTR_SECTION(".text.crt.io.stropts") int
NOTHROW(LIBCCALL libc_isastream)(fd_t fd)
/*[[[body:libc_isastream]]]*/
/*AUTO*/{
	(void)fd;
	CRT_UNIMPLEMENTEDF("isastream(%" PRIxN(__SIZEOF_FD_T__) ")", fd); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_isastream]]]*/

/*[[[head:libc_getmsg,hash:CRC-32=0xc7e3994]]]*/
/* @param: pflags: Set of `MSG_HIPRI | MSG_ANY | MSG_BAND'
 * @return: MORECTL:  ???
 * @return: MOREDATA: ??? */
INTERN ATTR_SECTION(".text.crt.io.stropts") int
NOTHROW_RPC(LIBCCALL libc_getmsg)(fd_t fd,
                                  struct strbuf *__restrict ctlptr,
                                  struct strbuf *__restrict dataptr,
                                  __STDC_INT_AS_UINT_T *__restrict pflags)
/*[[[body:libc_getmsg]]]*/
/*AUTO*/{
	(void)fd;
	(void)ctlptr;
	(void)dataptr;
	(void)pflags;
	CRT_UNIMPLEMENTEDF("getmsg(%" PRIxN(__SIZEOF_FD_T__) ", %p, %p, %p)", fd, ctlptr, dataptr, pflags); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getmsg]]]*/

/*[[[head:libc_getpmsg,hash:CRC-32=0xa553be7e]]]*/
/* @param: pflags: Set of `MSG_HIPRI | MSG_ANY | MSG_BAND'
 * @return: MORECTL:  ???
 * @return: MOREDATA: ??? */
INTERN ATTR_SECTION(".text.crt.io.stropts") int
NOTHROW_RPC(LIBCCALL libc_getpmsg)(fd_t fd,
                                   struct strbuf *__restrict ctlptr,
                                   struct strbuf *__restrict dataptr,
                                   int *__restrict bandp,
                                   __STDC_INT_AS_UINT_T *__restrict pflags)
/*[[[body:libc_getpmsg]]]*/
/*AUTO*/{
	(void)fd;
	(void)ctlptr;
	(void)dataptr;
	(void)bandp;
	(void)pflags;
	CRT_UNIMPLEMENTEDF("getpmsg(%" PRIxN(__SIZEOF_FD_T__) ", %p, %p, %p, %p)", fd, ctlptr, dataptr, bandp, pflags); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getpmsg]]]*/

/*[[[head:libc_putmsg,hash:CRC-32=0x3e031ec0]]]*/
/* @param: flags: Set of `MSG_HIPRI | MSG_ANY | MSG_BAND' */
INTERN ATTR_SECTION(".text.crt.io.stropts") int
NOTHROW_RPC(LIBCCALL libc_putmsg)(fd_t fd,
                                  struct strbuf const *ctlptr,
                                  struct strbuf const *dataptr,
                                  __STDC_INT_AS_UINT_T flags)
/*[[[body:libc_putmsg]]]*/
/*AUTO*/{
	(void)fd;
	(void)ctlptr;
	(void)dataptr;
	(void)flags;
	CRT_UNIMPLEMENTEDF("putmsg(%" PRIxN(__SIZEOF_FD_T__) ", %p, %p, %x)", fd, ctlptr, dataptr, flags); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_putmsg]]]*/

/*[[[head:libc_putpmsg,hash:CRC-32=0x5bfcc902]]]*/
/* @param: flags: Set of `MSG_HIPRI | MSG_ANY | MSG_BAND' */
INTERN ATTR_SECTION(".text.crt.io.stropts") int
NOTHROW_RPC(LIBCCALL libc_putpmsg)(fd_t fd,
                                   struct strbuf const *ctlptr,
                                   struct strbuf const *dataptr,
                                   __STDC_INT_AS_UINT_T band,
                                   __STDC_INT_AS_UINT_T flags)
/*[[[body:libc_putpmsg]]]*/
/*AUTO*/{
	(void)fd;
	(void)ctlptr;
	(void)dataptr;
	(void)band;
	(void)flags;
	CRT_UNIMPLEMENTEDF("putpmsg(%" PRIxN(__SIZEOF_FD_T__) ", %p, %p, %x, %x)", fd, ctlptr, dataptr, band, flags); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_putpmsg]]]*/

/*[[[head:libc_fattach,hash:CRC-32=0x36f5d8b7]]]*/
INTERN ATTR_SECTION(".text.crt.io.stropts") ATTR_IN(2) int
NOTHROW_RPC_KOS(LIBCCALL libc_fattach)(fd_t fd,
                                       char const *__restrict path)
/*[[[body:libc_fattach]]]*/
/*AUTO*/{
	(void)fd;
	(void)path;
	CRT_UNIMPLEMENTEDF("fattach(%" PRIxN(__SIZEOF_FD_T__) ", %q)", fd, path); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_fattach]]]*/

/*[[[head:libc_fdetach,hash:CRC-32=0xbcf4adec]]]*/
INTERN ATTR_SECTION(".text.crt.io.stropts") ATTR_IN(1) int
NOTHROW_RPC_KOS(LIBCCALL libc_fdetach)(char const *__restrict path)
/*[[[body:libc_fdetach]]]*/
/*AUTO*/{
	(void)path;
	CRT_UNIMPLEMENTEDF("fdetach(%q)", path); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_fdetach]]]*/





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
