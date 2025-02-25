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
#ifndef GUARD_LIBC_USER_STROPTS_C
#define GUARD_LIBC_USER_STROPTS_C 1

#include "../api.h"
#include "stropts.h"

DECL_BEGIN

/*[[[head:libc_isastream,hash:CRC-32=0x84e79703]]]*/
INTERN ATTR_SECTION(".text.crt.io.stropts") ATTR_FDARG(1) int
NOTHROW(LIBCCALL libc_isastream)(fd_t fd)
/*[[[body:libc_isastream]]]*/
/*AUTO*/{
	(void)fd;
	CRT_UNIMPLEMENTEDF("isastream(fd: %" PRIxN(__SIZEOF_FD_T__) ")", fd); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_isastream]]]*/

/*[[[head:libc_getmsg,hash:CRC-32=0x8701fd5a]]]*/
/* @param: pflags: Set of `MSG_HIPRI | MSG_ANY | MSG_BAND'
 * @return: MORECTL:  ???
 * @return: MOREDATA: ??? */
INTERN ATTR_SECTION(".text.crt.io.stropts") ATTR_FDARG(1) int
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
	CRT_UNIMPLEMENTEDF("getmsg(fd: %" PRIxN(__SIZEOF_FD_T__) ", ctlptr: %p, dataptr: %p, pflags: %p)", fd, ctlptr, dataptr, pflags); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_getmsg]]]*/

/*[[[head:libc_getpmsg,hash:CRC-32=0x7a8bd110]]]*/
/* @param: pflags: Set of `MSG_HIPRI | MSG_ANY | MSG_BAND'
 * @return: MORECTL:  ???
 * @return: MOREDATA: ??? */
INTERN ATTR_SECTION(".text.crt.io.stropts") ATTR_FDARG(1) int
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
	CRT_UNIMPLEMENTEDF("getpmsg(fd: %" PRIxN(__SIZEOF_FD_T__) ", ctlptr: %p, dataptr: %p, bandp: %p, pflags: %p)", fd, ctlptr, dataptr, bandp, pflags); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_getpmsg]]]*/

/*[[[head:libc_putmsg,hash:CRC-32=0x1da465e4]]]*/
/* @param: flags: Set of `MSG_HIPRI | MSG_ANY | MSG_BAND' */
INTERN ATTR_SECTION(".text.crt.io.stropts") ATTR_FDARG(1) int
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
	CRT_UNIMPLEMENTEDF("putmsg(fd: %" PRIxN(__SIZEOF_FD_T__) ", ctlptr: %p, dataptr: %p, flags: %x)", fd, ctlptr, dataptr, flags); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_putmsg]]]*/

/*[[[head:libc_putpmsg,hash:CRC-32=0x6858db9a]]]*/
/* @param: flags: Set of `MSG_HIPRI | MSG_ANY | MSG_BAND' */
INTERN ATTR_SECTION(".text.crt.io.stropts") ATTR_FDARG(1) int
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
	CRT_UNIMPLEMENTEDF("putpmsg(fd: %" PRIxN(__SIZEOF_FD_T__) ", ctlptr: %p, dataptr: %p, band: %x, flags: %x)", fd, ctlptr, dataptr, band, flags); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_putpmsg]]]*/

/*[[[head:libc_fattach,hash:CRC-32=0xdb510b46]]]*/
INTERN ATTR_SECTION(".text.crt.io.stropts") ATTR_FDARG(1) ATTR_IN(2) int
NOTHROW_RPC_KOS(LIBCCALL libc_fattach)(fd_t fd,
                                       char const *__restrict path)
/*[[[body:libc_fattach]]]*/
/*AUTO*/{
	(void)fd;
	(void)path;
	CRT_UNIMPLEMENTEDF("fattach(fd: %" PRIxN(__SIZEOF_FD_T__) ", path: %q)", fd, path); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_fattach]]]*/

/*[[[head:libc_fdetach,hash:CRC-32=0xbcf4adec]]]*/
INTERN ATTR_SECTION(".text.crt.io.stropts") ATTR_IN(1) int
NOTHROW_RPC_KOS(LIBCCALL libc_fdetach)(char const *__restrict path)
/*[[[body:libc_fdetach]]]*/
/*AUTO*/{
	(void)path;
	CRT_UNIMPLEMENTEDF("fdetach(path: %q)", path); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_fdetach]]]*/





/*[[[start:exports,hash:CRC-32=0x12ab880c]]]*/
DEFINE_PUBLIC_ALIAS_P(isastream,libc_isastream,ATTR_FDARG(1),int,NOTHROW,LIBCCALL,(fd_t fd),(fd));
DEFINE_PUBLIC_ALIAS_P(getmsg,libc_getmsg,ATTR_FDARG(1),int,NOTHROW_RPC,LIBCCALL,(fd_t fd, struct strbuf *__restrict ctlptr, struct strbuf *__restrict dataptr, __STDC_INT_AS_UINT_T *__restrict pflags),(fd,ctlptr,dataptr,pflags));
DEFINE_PUBLIC_ALIAS_P(getpmsg,libc_getpmsg,ATTR_FDARG(1),int,NOTHROW_RPC,LIBCCALL,(fd_t fd, struct strbuf *__restrict ctlptr, struct strbuf *__restrict dataptr, int *__restrict bandp, __STDC_INT_AS_UINT_T *__restrict pflags),(fd,ctlptr,dataptr,bandp,pflags));
DEFINE_PUBLIC_ALIAS_P(putmsg,libc_putmsg,ATTR_FDARG(1),int,NOTHROW_RPC,LIBCCALL,(fd_t fd, struct strbuf const *ctlptr, struct strbuf const *dataptr, __STDC_INT_AS_UINT_T flags),(fd,ctlptr,dataptr,flags));
DEFINE_PUBLIC_ALIAS_P(putpmsg,libc_putpmsg,ATTR_FDARG(1),int,NOTHROW_RPC,LIBCCALL,(fd_t fd, struct strbuf const *ctlptr, struct strbuf const *dataptr, __STDC_INT_AS_UINT_T band, __STDC_INT_AS_UINT_T flags),(fd,ctlptr,dataptr,band,flags));
DEFINE_PUBLIC_ALIAS_P(fattach,libc_fattach,ATTR_FDARG(1) ATTR_IN(2),int,NOTHROW_RPC_KOS,LIBCCALL,(fd_t fd, char const *__restrict path),(fd,path));
DEFINE_PUBLIC_ALIAS_P(fdetach,libc_fdetach,ATTR_IN(1),int,NOTHROW_RPC_KOS,LIBCCALL,(char const *__restrict path),(path));
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_STROPTS_C */
