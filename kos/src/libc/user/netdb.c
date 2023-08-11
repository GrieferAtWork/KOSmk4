/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_NETDB_C
#define GUARD_LIBC_USER_NETDB_C 1

#include "../api.h"
#include "netdb.h"

DECL_BEGIN

/*[[[head:libc___h_errno_location,hash:CRC-32=0x2937b5c1]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") ATTR_CONST ATTR_RETNONNULL WUNUSED int *
NOTHROW(LIBCCALL libc___h_errno_location)(void)
/*[[[body:libc___h_errno_location]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("__h_errno_location"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc___h_errno_location]]]*/

/*[[[head:libc_herror,hash:CRC-32=0xfeb51337]]]*/
/* >> herror(3)
 * Same as `perror(3)' for `errno(3)', print `message' (if non-null),
 * alongside   the  value  of  `hstrerror(h_errno)'  to  `stderr(3)'. */
INTERN ATTR_SECTION(".text.crt.net.db") void
NOTHROW_CB_NCX(LIBCCALL libc_herror)(char const *message)
/*[[[body:libc_herror]]]*/
/*AUTO*/{
	(void)message;
	CRT_UNIMPLEMENTEDF("herror(message: %q)", message); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_herror]]]*/

/*[[[head:libc_hstrerror,hash:CRC-32=0xf210b408]]]*/
/* >> hstrerror(3)
 * Return error message for `h_error' */
INTERN ATTR_SECTION(".text.crt.net.db") ATTR_CONST WUNUSED char const *
NOTHROW(LIBCCALL libc_hstrerror)(int h_error)
/*[[[body:libc_hstrerror]]]*/
/*AUTO*/{
	(void)h_error;
	CRT_UNIMPLEMENTEDF("hstrerror(h_error: %x)", h_error); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_hstrerror]]]*/

/*[[[head:libc_sethostent,hash:CRC-32=0x23a4f1f2]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") void
NOTHROW_RPC(LIBCCALL libc_sethostent)(int stay_open)
/*[[[body:libc_sethostent]]]*/
/*AUTO*/{
	(void)stay_open;
	CRT_UNIMPLEMENTEDF("sethostent(stay_open: %x)", stay_open); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_sethostent]]]*/

/*[[[head:libc_endhostent,hash:CRC-32=0xe3736f34]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") void
NOTHROW_RPC_NOKOS(LIBCCALL libc_endhostent)(void)
/*[[[body:libc_endhostent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("endhostent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_endhostent]]]*/

/*[[[head:libc_gethostent,hash:CRC-32=0x9de52062]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") struct hostent *
NOTHROW_RPC(LIBCCALL libc_gethostent)(void)
/*[[[body:libc_gethostent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("gethostent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_gethostent]]]*/

/*[[[head:libc_gethostbyaddr,hash:CRC-32=0xfd8977d6]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") struct hostent *
NOTHROW_RPC(LIBCCALL libc_gethostbyaddr)(void const *addr,
                                         socklen_t len,
                                         int type)
/*[[[body:libc_gethostbyaddr]]]*/
/*AUTO*/{
	(void)addr;
	(void)len;
	(void)type;
	CRT_UNIMPLEMENTEDF("gethostbyaddr(addr: %p, len: %" PRIxN(__SIZEOF_SOCKLEN_T__) ", type: %x)", addr, len, type); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_gethostbyaddr]]]*/

/*[[[head:libc_gethostbyname,hash:CRC-32=0x533d010e]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") struct hostent *
NOTHROW_RPC(LIBCCALL libc_gethostbyname)(char const *name)
/*[[[body:libc_gethostbyname]]]*/
/*AUTO*/{
	(void)name;
	CRT_UNIMPLEMENTEDF("gethostbyname(name: %q)", name); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_gethostbyname]]]*/

/*[[[head:libc_gethostbyname2,hash:CRC-32=0x42431e14]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") struct hostent *
NOTHROW_RPC(LIBCCALL libc_gethostbyname2)(char const *name,
                                          int af)
/*[[[body:libc_gethostbyname2]]]*/
/*AUTO*/{
	(void)name;
	(void)af;
	CRT_UNIMPLEMENTEDF("gethostbyname2(name: %q, af: %x)", name, af); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_gethostbyname2]]]*/

/*[[[head:libc_gethostent_r,hash:CRC-32=0x8d84f175]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_gethostent_r)(struct hostent *__restrict result_buf,
                                        char *__restrict buf,
                                        size_t buflen,
                                        struct hostent **__restrict result,
                                        int *__restrict h_errnop)
/*[[[body:libc_gethostent_r]]]*/
/*AUTO*/{
	(void)result_buf;
	(void)buf;
	(void)buflen;
	(void)result;
	(void)h_errnop;
	CRT_UNIMPLEMENTEDF("gethostent_r(result_buf: %p, buf: %q, buflen: %Ix, result: %p, h_errnop: %p)", result_buf, buf, buflen, result, h_errnop); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_gethostent_r]]]*/

/*[[[head:libc_gethostbyaddr_r,hash:CRC-32=0xf1b08b28]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_gethostbyaddr_r)(void const *__restrict addr,
                                           socklen_t len,
                                           int type,
                                           struct hostent *__restrict result_buf,
                                           char *__restrict buf,
                                           size_t buflen,
                                           struct hostent **__restrict result,
                                           int *__restrict h_errnop)
/*[[[body:libc_gethostbyaddr_r]]]*/
/*AUTO*/{
	(void)addr;
	(void)len;
	(void)type;
	(void)result_buf;
	(void)buf;
	(void)buflen;
	(void)result;
	(void)h_errnop;
	CRT_UNIMPLEMENTEDF("gethostbyaddr_r(addr: %p, len: %" PRIxN(__SIZEOF_SOCKLEN_T__) ", type: %x, result_buf: %p, buf: %q, buflen: %Ix, result: %p, h_errnop: %p)", addr, len, type, result_buf, buf, buflen, result, h_errnop); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_gethostbyaddr_r]]]*/

/*[[[head:libc_gethostbyname_r,hash:CRC-32=0x15244d08]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_gethostbyname_r)(char const *__restrict name,
                                           struct hostent *__restrict result_buf,
                                           char *__restrict buf,
                                           size_t buflen,
                                           struct hostent **__restrict result,
                                           int *__restrict h_errnop)
/*[[[body:libc_gethostbyname_r]]]*/
/*AUTO*/{
	(void)name;
	(void)result_buf;
	(void)buf;
	(void)buflen;
	(void)result;
	(void)h_errnop;
	CRT_UNIMPLEMENTEDF("gethostbyname_r(name: %q, result_buf: %p, buf: %q, buflen: %Ix, result: %p, h_errnop: %p)", name, result_buf, buf, buflen, result, h_errnop); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_gethostbyname_r]]]*/

/*[[[head:libc_gethostbyname2_r,hash:CRC-32=0xf60ad6dc]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_gethostbyname2_r)(char const *__restrict name,
                                            int af,
                                            struct hostent *__restrict result_buf,
                                            char *__restrict buf,
                                            size_t buflen,
                                            struct hostent **__restrict result,
                                            int *__restrict h_errnop)
/*[[[body:libc_gethostbyname2_r]]]*/
/*AUTO*/{
	(void)name;
	(void)af;
	(void)result_buf;
	(void)buf;
	(void)buflen;
	(void)result;
	(void)h_errnop;
	CRT_UNIMPLEMENTEDF("gethostbyname2_r(name: %q, af: %x, result_buf: %p, buf: %q, buflen: %Ix, result: %p, h_errnop: %p)", name, af, result_buf, buf, buflen, result, h_errnop); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_gethostbyname2_r]]]*/

/*[[[head:libc_setnetent,hash:CRC-32=0x5578b729]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") void
NOTHROW_RPC(LIBCCALL libc_setnetent)(int stay_open)
/*[[[body:libc_setnetent]]]*/
/*AUTO*/{
	(void)stay_open;
	CRT_UNIMPLEMENTEDF("setnetent(stay_open: %x)", stay_open); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_setnetent]]]*/

/*[[[head:libc_endnetent,hash:CRC-32=0xfe5e47ca]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") void
NOTHROW_RPC_NOKOS(LIBCCALL libc_endnetent)(void)
/*[[[body:libc_endnetent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("endnetent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_endnetent]]]*/

/*[[[head:libc_getnetent,hash:CRC-32=0xc5c94396]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") struct netent *
NOTHROW_RPC(LIBCCALL libc_getnetent)(void)
/*[[[body:libc_getnetent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("getnetent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getnetent]]]*/

/*[[[head:libc_getnetbyaddr,hash:CRC-32=0x2346f298]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") struct netent *
NOTHROW_RPC(LIBCCALL libc_getnetbyaddr)(uint32_t net,
                                        int type)
/*[[[body:libc_getnetbyaddr]]]*/
/*AUTO*/{
	(void)net;
	(void)type;
	CRT_UNIMPLEMENTEDF("getnetbyaddr(net: %" PRIx32 ", type: %x)", net, type); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getnetbyaddr]]]*/

/*[[[head:libc_getnetbyname,hash:CRC-32=0x72953a74]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") struct netent *
NOTHROW_RPC(LIBCCALL libc_getnetbyname)(char const *name)
/*[[[body:libc_getnetbyname]]]*/
/*AUTO*/{
	(void)name;
	CRT_UNIMPLEMENTEDF("getnetbyname(name: %q)", name); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getnetbyname]]]*/

/*[[[head:libc_getnetent_r,hash:CRC-32=0x2d2fd254]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_getnetent_r)(struct netent *__restrict result_buf,
                                       char *__restrict buf,
                                       size_t buflen,
                                       struct netent **__restrict result,
                                       int *__restrict h_errnop)
/*[[[body:libc_getnetent_r]]]*/
/*AUTO*/{
	(void)result_buf;
	(void)buf;
	(void)buflen;
	(void)result;
	(void)h_errnop;
	CRT_UNIMPLEMENTEDF("getnetent_r(result_buf: %p, buf: %q, buflen: %Ix, result: %p, h_errnop: %p)", result_buf, buf, buflen, result, h_errnop); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_getnetent_r]]]*/

/*[[[head:libc_getnetbyaddr_r,hash:CRC-32=0x28c4db0e]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_getnetbyaddr_r)(uint32_t net,
                                          int type,
                                          struct netent *__restrict result_buf,
                                          char *__restrict buf,
                                          size_t buflen,
                                          struct netent **__restrict result,
                                          int *__restrict h_errnop)
/*[[[body:libc_getnetbyaddr_r]]]*/
/*AUTO*/{
	(void)net;
	(void)type;
	(void)result_buf;
	(void)buf;
	(void)buflen;
	(void)result;
	(void)h_errnop;
	CRT_UNIMPLEMENTEDF("getnetbyaddr_r(net: %" PRIx32 ", type: %x, result_buf: %p, buf: %q, buflen: %Ix, result: %p, h_errnop: %p)", net, type, result_buf, buf, buflen, result, h_errnop); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_getnetbyaddr_r]]]*/

/*[[[head:libc_getnetbyname_r,hash:CRC-32=0xa1e63aee]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_getnetbyname_r)(char const *__restrict name,
                                          struct netent *__restrict result_buf,
                                          char *__restrict buf,
                                          size_t buflen,
                                          struct netent **__restrict result,
                                          int *__restrict h_errnop)
/*[[[body:libc_getnetbyname_r]]]*/
/*AUTO*/{
	(void)name;
	(void)result_buf;
	(void)buf;
	(void)buflen;
	(void)result;
	(void)h_errnop;
	CRT_UNIMPLEMENTEDF("getnetbyname_r(name: %q, result_buf: %p, buf: %q, buflen: %Ix, result: %p, h_errnop: %p)", name, result_buf, buf, buflen, result, h_errnop); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_getnetbyname_r]]]*/

/*[[[head:libc_setservent,hash:CRC-32=0xc81fee2b]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") void
NOTHROW_RPC(LIBCCALL libc_setservent)(int stay_open)
/*[[[body:libc_setservent]]]*/
/*AUTO*/{
	(void)stay_open;
	CRT_UNIMPLEMENTEDF("setservent(stay_open: %x)", stay_open); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_setservent]]]*/

/*[[[head:libc_endservent,hash:CRC-32=0x9a7fcb04]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") void
NOTHROW_RPC_NOKOS(LIBCCALL libc_endservent)(void)
/*[[[body:libc_endservent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("endservent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_endservent]]]*/

/*[[[head:libc_getservent,hash:CRC-32=0x6a265b3a]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") struct servent *
NOTHROW_RPC(LIBCCALL libc_getservent)(void)
/*[[[body:libc_getservent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("getservent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getservent]]]*/

/*[[[head:libc_getservbyname,hash:CRC-32=0x3fbf69d1]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") struct servent *
NOTHROW_RPC(LIBCCALL libc_getservbyname)(char const *name,
                                         char const *proto)
/*[[[body:libc_getservbyname]]]*/
/*AUTO*/{
	(void)name;
	(void)proto;
	CRT_UNIMPLEMENTEDF("getservbyname(name: %q, proto: %q)", name, proto); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getservbyname]]]*/

/*[[[head:libc_getservbyport,hash:CRC-32=0x6cb7cee7]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") struct servent *
NOTHROW_RPC(LIBCCALL libc_getservbyport)(int port,
                                         char const *proto)
/*[[[body:libc_getservbyport]]]*/
/*AUTO*/{
	(void)port;
	(void)proto;
	CRT_UNIMPLEMENTEDF("getservbyport(port: %x, proto: %q)", port, proto); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getservbyport]]]*/

/*[[[head:libc_getservent_r,hash:CRC-32=0x7ac60c7d]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_getservent_r)(struct servent *__restrict result_buf,
                                        char *__restrict buf,
                                        size_t buflen,
                                        struct servent **__restrict result)
/*[[[body:libc_getservent_r]]]*/
/*AUTO*/{
	(void)result_buf;
	(void)buf;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTEDF("getservent_r(result_buf: %p, buf: %q, buflen: %Ix, result: %p)", result_buf, buf, buflen, result); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_getservent_r]]]*/

/*[[[head:libc_getservbyname_r,hash:CRC-32=0x5b7661ff]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_getservbyname_r)(char const *__restrict name,
                                           char const *__restrict proto,
                                           struct servent *__restrict result_buf,
                                           char *__restrict buf,
                                           size_t buflen,
                                           struct servent **__restrict result)
/*[[[body:libc_getservbyname_r]]]*/
/*AUTO*/{
	(void)name;
	(void)proto;
	(void)result_buf;
	(void)buf;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTEDF("getservbyname_r(name: %q, proto: %q, result_buf: %p, buf: %q, buflen: %Ix, result: %p)", name, proto, result_buf, buf, buflen, result); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_getservbyname_r]]]*/

/*[[[head:libc_getservbyport_r,hash:CRC-32=0x1ee96906]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_getservbyport_r)(int port,
                                           char const *__restrict proto,
                                           struct servent *__restrict result_buf,
                                           char *__restrict buf,
                                           size_t buflen,
                                           struct servent **__restrict result)
/*[[[body:libc_getservbyport_r]]]*/
/*AUTO*/{
	(void)port;
	(void)proto;
	(void)result_buf;
	(void)buf;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTEDF("getservbyport_r(port: %x, proto: %q, result_buf: %p, buf: %q, buflen: %Ix, result: %p)", port, proto, result_buf, buf, buflen, result); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_getservbyport_r]]]*/

/*[[[head:libc_setprotoent,hash:CRC-32=0x2fde2b95]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") void
NOTHROW_RPC(LIBCCALL libc_setprotoent)(int stay_open)
/*[[[body:libc_setprotoent]]]*/
/*AUTO*/{
	(void)stay_open;
	CRT_UNIMPLEMENTEDF("setprotoent(stay_open: %x)", stay_open); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_setprotoent]]]*/

/*[[[head:libc_endprotoent,hash:CRC-32=0x28403d17]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") void
NOTHROW_RPC_NOKOS(LIBCCALL libc_endprotoent)(void)
/*[[[body:libc_endprotoent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("endprotoent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_endprotoent]]]*/

/*[[[head:libc_getprotoent,hash:CRC-32=0x150a0851]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") struct protoent *
NOTHROW_RPC(LIBCCALL libc_getprotoent)(void)
/*[[[body:libc_getprotoent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("getprotoent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getprotoent]]]*/

/*[[[head:libc_getprotobyname,hash:CRC-32=0x9ff89f2a]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") struct protoent *
NOTHROW_RPC(LIBCCALL libc_getprotobyname)(char const *name)
/*[[[body:libc_getprotobyname]]]*/
/*AUTO*/{
	(void)name;
	CRT_UNIMPLEMENTEDF("getprotobyname(name: %q)", name); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getprotobyname]]]*/

/*[[[head:libc_getprotobynumber,hash:CRC-32=0x70bc2f3c]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") struct protoent *
NOTHROW_RPC(LIBCCALL libc_getprotobynumber)(int proto)
/*[[[body:libc_getprotobynumber]]]*/
/*AUTO*/{
	(void)proto;
	CRT_UNIMPLEMENTEDF("getprotobynumber(proto: %x)", proto); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getprotobynumber]]]*/

/*[[[head:libc_getprotoent_r,hash:CRC-32=0x10c28544]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_getprotoent_r)(struct protoent *__restrict result_buf,
                                         char *__restrict buf,
                                         size_t buflen,
                                         struct protoent **__restrict result)
/*[[[body:libc_getprotoent_r]]]*/
/*AUTO*/{
	(void)result_buf;
	(void)buf;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTEDF("getprotoent_r(result_buf: %p, buf: %q, buflen: %Ix, result: %p)", result_buf, buf, buflen, result); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_getprotoent_r]]]*/

/*[[[head:libc_getprotobyname_r,hash:CRC-32=0xa50ad72b]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_getprotobyname_r)(char const *__restrict name,
                                            struct protoent *__restrict result_buf,
                                            char *__restrict buf,
                                            size_t buflen,
                                            struct protoent **__restrict result)
/*[[[body:libc_getprotobyname_r]]]*/
/*AUTO*/{
	(void)name;
	(void)result_buf;
	(void)buf;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTEDF("getprotobyname_r(name: %q, result_buf: %p, buf: %q, buflen: %Ix, result: %p)", name, result_buf, buf, buflen, result); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_getprotobyname_r]]]*/

/*[[[head:libc_getprotobynumber_r,hash:CRC-32=0x57e015fe]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_getprotobynumber_r)(int proto,
                                              struct protoent *__restrict result_buf,
                                              char *__restrict buf,
                                              size_t buflen,
                                              struct protoent **__restrict result)
/*[[[body:libc_getprotobynumber_r]]]*/
/*AUTO*/{
	(void)proto;
	(void)result_buf;
	(void)buf;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTEDF("getprotobynumber_r(proto: %x, result_buf: %p, buf: %q, buflen: %Ix, result: %p)", proto, result_buf, buf, buflen, result); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_getprotobynumber_r]]]*/

/*[[[head:libc_setnetgrent,hash:CRC-32=0x1ec56114]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_setnetgrent)(char const *netgroup)
/*[[[body:libc_setnetgrent]]]*/
/*AUTO*/{
	(void)netgroup;
	CRT_UNIMPLEMENTEDF("setnetgrent(netgroup: %q)", netgroup); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_setnetgrent]]]*/

/*[[[head:libc_endnetgrent,hash:CRC-32=0x837644f0]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") void
NOTHROW_RPC_NOKOS(LIBCCALL libc_endnetgrent)(void)
/*[[[body:libc_endnetgrent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("endnetgrent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_endnetgrent]]]*/

/*[[[head:libc_getnetgrent,hash:CRC-32=0x70f78394]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_getnetgrent)(char **__restrict hostp,
                                       char **__restrict userp,
                                       char **__restrict domainp)
/*[[[body:libc_getnetgrent]]]*/
/*AUTO*/{
	(void)hostp;
	(void)userp;
	(void)domainp;
	CRT_UNIMPLEMENTEDF("getnetgrent(hostp: %p, userp: %p, domainp: %p)", hostp, userp, domainp); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_getnetgrent]]]*/

/*[[[head:libc_innetgr,hash:CRC-32=0x161ee05d]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_innetgr)(char const *netgroup,
                                   char const *host,
                                   char const *user,
                                   char const *domain)
/*[[[body:libc_innetgr]]]*/
/*AUTO*/{
	(void)netgroup;
	(void)host;
	(void)user;
	(void)domain;
	CRT_UNIMPLEMENTEDF("innetgr(netgroup: %q, host: %q, user: %q, domain: %q)", netgroup, host, user, domain); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_innetgr]]]*/

/*[[[head:libc_getnetgrent_r,hash:CRC-32=0x62fafe75]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_getnetgrent_r)(char **__restrict hostp,
                                         char **__restrict userp,
                                         char **__restrict domainp,
                                         char *__restrict buf,
                                         size_t buflen)
/*[[[body:libc_getnetgrent_r]]]*/
/*AUTO*/{
	(void)hostp;
	(void)userp;
	(void)domainp;
	(void)buf;
	(void)buflen;
	CRT_UNIMPLEMENTEDF("getnetgrent_r(hostp: %p, userp: %p, domainp: %p, buf: %q, buflen: %Ix)", hostp, userp, domainp, buf, buflen); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_getnetgrent_r]]]*/

/*[[[head:libc_rcmd,hash:CRC-32=0xa65ca190]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_rcmd)(char **__restrict ahost,
                                uint16_t rport,
                                char const *__restrict locuser,
                                char const *__restrict remuser,
                                char const *__restrict cmd,
                                int *__restrict fd2p)
/*[[[body:libc_rcmd]]]*/
/*AUTO*/{
	(void)ahost;
	(void)rport;
	(void)locuser;
	(void)remuser;
	(void)cmd;
	(void)fd2p;
	CRT_UNIMPLEMENTEDF("rcmd(ahost: %p, rport: %" PRIx16 ", locuser: %q, remuser: %q, cmd: %q, fd2p: %p)", ahost, rport, locuser, remuser, cmd, fd2p); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_rcmd]]]*/

/*[[[head:libc_rcmd_af,hash:CRC-32=0xd263b4a0]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_rcmd_af)(char **__restrict ahost,
                                   uint16_t rport,
                                   char const *__restrict locuser,
                                   char const *__restrict remuser,
                                   char const *__restrict cmd,
                                   int *__restrict fd2p,
                                   sa_family_t af)
/*[[[body:libc_rcmd_af]]]*/
/*AUTO*/{
	(void)ahost;
	(void)rport;
	(void)locuser;
	(void)remuser;
	(void)cmd;
	(void)fd2p;
	(void)af;
	CRT_UNIMPLEMENTEDF("rcmd_af(ahost: %p, rport: %" PRIx16 ", locuser: %q, remuser: %q, cmd: %q, fd2p: %p, af: %" PRIx16 ")", ahost, rport, locuser, remuser, cmd, fd2p, af); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_rcmd_af]]]*/

/*[[[head:libc_rexec,hash:CRC-32=0x55c08094]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_rexec)(char **__restrict ahost,
                                 int rport,
                                 char const *__restrict name,
                                 char const *__restrict pass,
                                 char const *__restrict cmd,
                                 int *__restrict fd2p)
/*[[[body:libc_rexec]]]*/
/*AUTO*/{
	(void)ahost;
	(void)rport;
	(void)name;
	(void)pass;
	(void)cmd;
	(void)fd2p;
	CRT_UNIMPLEMENTEDF("rexec(ahost: %p, rport: %x, name: %q, pass: %q, cmd: %q, fd2p: %p)", ahost, rport, name, pass, cmd, fd2p); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_rexec]]]*/

/*[[[head:libc_rexec_af,hash:CRC-32=0xc59a6e22]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_rexec_af)(char **__restrict ahost,
                                    int rport,
                                    char const *__restrict name,
                                    char const *__restrict pass,
                                    char const *__restrict cmd,
                                    int *__restrict fd2p,
                                    sa_family_t af)
/*[[[body:libc_rexec_af]]]*/
/*AUTO*/{
	(void)ahost;
	(void)rport;
	(void)name;
	(void)pass;
	(void)cmd;
	(void)fd2p;
	(void)af;
	CRT_UNIMPLEMENTEDF("rexec_af(ahost: %p, rport: %x, name: %q, pass: %q, cmd: %q, fd2p: %p, af: %" PRIx16 ")", ahost, rport, name, pass, cmd, fd2p, af); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_rexec_af]]]*/

/*[[[head:libc_ruserok,hash:CRC-32=0x3bb85afa]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_ruserok)(char const *rhost,
                                   int suser,
                                   char const *remuser,
                                   char const *locuser)
/*[[[body:libc_ruserok]]]*/
/*AUTO*/{
	(void)rhost;
	(void)suser;
	(void)remuser;
	(void)locuser;
	CRT_UNIMPLEMENTEDF("ruserok(rhost: %q, suser: %x, remuser: %q, locuser: %q)", rhost, suser, remuser, locuser); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_ruserok]]]*/

/*[[[head:libc_ruserok_af,hash:CRC-32=0x2ef33b0]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_ruserok_af)(char const *rhost,
                                      int suser,
                                      char const *remuser,
                                      char const *locuser,
                                      sa_family_t af)
/*[[[body:libc_ruserok_af]]]*/
/*AUTO*/{
	(void)rhost;
	(void)suser;
	(void)remuser;
	(void)locuser;
	(void)af;
	CRT_UNIMPLEMENTEDF("ruserok_af(rhost: %q, suser: %x, remuser: %q, locuser: %q, af: %" PRIx16 ")", rhost, suser, remuser, locuser, af); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_ruserok_af]]]*/

/*[[[head:libc_iruserok,hash:CRC-32=0xa6d93f06]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_iruserok)(uint32_t raddr,
                                    int suser,
                                    char const *remuser,
                                    char const *locuser)
/*[[[body:libc_iruserok]]]*/
/*AUTO*/{
	(void)raddr;
	(void)suser;
	(void)remuser;
	(void)locuser;
	CRT_UNIMPLEMENTEDF("iruserok(raddr: %" PRIx32 ", suser: %x, remuser: %q, locuser: %q)", raddr, suser, remuser, locuser); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_iruserok]]]*/

/*[[[head:libc_iruserok_af,hash:CRC-32=0x7ed0a242]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_iruserok_af)(void const *raddr,
                                       int suser,
                                       char const *remuser,
                                       char const *locuser,
                                       sa_family_t af)
/*[[[body:libc_iruserok_af]]]*/
/*AUTO*/{
	(void)raddr;
	(void)suser;
	(void)remuser;
	(void)locuser;
	(void)af;
	CRT_UNIMPLEMENTEDF("iruserok_af(raddr: %p, suser: %x, remuser: %q, locuser: %q, af: %" PRIx16 ")", raddr, suser, remuser, locuser, af); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_iruserok_af]]]*/

/*[[[head:libc_rresvport,hash:CRC-32=0xbdaf278f]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_rresvport)(int *alport)
/*[[[body:libc_rresvport]]]*/
/*AUTO*/{
	(void)alport;
	CRT_UNIMPLEMENTEDF("rresvport(alport: %p)", alport); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_rresvport]]]*/

/*[[[head:libc_rresvport_af,hash:CRC-32=0x3c3b5435]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_rresvport_af)(int *alport,
                                        sa_family_t af)
/*[[[body:libc_rresvport_af]]]*/
/*AUTO*/{
	(void)alport;
	(void)af;
	CRT_UNIMPLEMENTEDF("rresvport_af(alport: %p, af: %" PRIx16 ")", alport, af); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_rresvport_af]]]*/

/*[[[head:libc_getaddrinfo,hash:CRC-32=0x70cf056]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_getaddrinfo)(char const *__restrict name,
                                       char const *__restrict service,
                                       struct addrinfo const *__restrict req,
                                       struct addrinfo **__restrict pai)
/*[[[body:libc_getaddrinfo]]]*/
/*AUTO*/{
	(void)name;
	(void)service;
	(void)req;
	(void)pai;
	CRT_UNIMPLEMENTEDF("getaddrinfo(name: %q, service: %q, req: %p, pai: %p)", name, service, req, pai); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_getaddrinfo]]]*/

/*[[[head:libc_freeaddrinfo,hash:CRC-32=0x5c28a0b1]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") void
NOTHROW_NCX(LIBCCALL libc_freeaddrinfo)(struct addrinfo *ai)
/*[[[body:libc_freeaddrinfo]]]*/
/*AUTO*/{
	(void)ai;
	CRT_UNIMPLEMENTEDF("freeaddrinfo(ai: %p)", ai); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_freeaddrinfo]]]*/

/*[[[head:libc_gai_strerror,hash:CRC-32=0x554a0b04]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") ATTR_CONST WUNUSED char const *
NOTHROW(LIBCCALL libc_gai_strerror)(int ecode)
/*[[[body:libc_gai_strerror]]]*/
/*AUTO*/{
	(void)ecode;
	CRT_UNIMPLEMENTEDF("gai_strerror(ecode: %x)", ecode); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_gai_strerror]]]*/

/*[[[head:libc_getnameinfo,hash:CRC-32=0xc2233bbd]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_getnameinfo)(struct sockaddr const *__restrict sa,
                                       socklen_t salen,
                                       char *__restrict host,
                                       socklen_t hostlen,
                                       char *__restrict serv,
                                       socklen_t servlen,
                                       int flags)
/*[[[body:libc_getnameinfo]]]*/
/*AUTO*/{
	(void)sa;
	(void)salen;
	(void)host;
	(void)hostlen;
	(void)serv;
	(void)servlen;
	(void)flags;
	CRT_UNIMPLEMENTEDF("getnameinfo(sa: %p, salen: %" PRIxN(__SIZEOF_SOCKLEN_T__) ", host: %q, hostlen: %" PRIxN(__SIZEOF_SOCKLEN_T__) ", serv: %q, servlen: %" PRIxN(__SIZEOF_SOCKLEN_T__) ", flags: %x)", sa, salen, host, hostlen, serv, servlen, flags); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_getnameinfo]]]*/

/*[[[head:libc_getaddrinfo_a,hash:CRC-32=0x58a5b7a]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_getaddrinfo_a)(int mode,
                                         struct gaicb *list[__restrict_arr],
                                         int ent,
                                         struct sigevent *__restrict sig)
/*[[[body:libc_getaddrinfo_a]]]*/
/*AUTO*/{
	(void)mode;
	(void)list;
	(void)ent;
	(void)sig;
	CRT_UNIMPLEMENTEDF("getaddrinfo_a(mode: %x, list: %p, ent: %x, sig: %p)", mode, list, ent, sig); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_getaddrinfo_a]]]*/

/*[[[head:libc_gai_suspend,hash:CRC-32=0x166e4979]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_gai_suspend)(struct gaicb const *const list[],
                                       int ent,
                                       struct timespec const *timeout)
/*[[[body:libc_gai_suspend]]]*/
{
	(void)list;
	(void)ent;
	(void)timeout;
	CRT_UNIMPLEMENTED("gai_suspend"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:libc_gai_suspend]]]*/

/*[[[head:libc_gai_error,hash:CRC-32=0xb0937d1e]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_NCX(LIBCCALL libc_gai_error)(struct gaicb *req)
/*[[[body:libc_gai_error]]]*/
/*AUTO*/{
	(void)req;
	CRT_UNIMPLEMENTEDF("gai_error(req: %p)", req); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_gai_error]]]*/

/*[[[head:libc_gai_cancel,hash:CRC-32=0xc7b9eb5d]]]*/
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_NCX(LIBCCALL libc_gai_cancel)(struct gaicb *gaicbp)
/*[[[body:libc_gai_cancel]]]*/
/*AUTO*/{
	(void)gaicbp;
	CRT_UNIMPLEMENTEDF("gai_cancel(gaicbp: %p)", gaicbp); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_gai_cancel]]]*/

/*[[[head:libc_gai_suspend64,hash:CRC-32=0x600a2365]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_gai_suspend64, libc_gai_suspend);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_gai_suspend64)(struct gaicb const *const list[],
                                         int ent,
                                         struct timespec64 const *timeout)
/*[[[body:libc_gai_suspend64]]]*/
{
	(void)list;
	(void)ent;
	(void)timeout;
	CRT_UNIMPLEMENTED("gai_suspend64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
#endif /* MAGIC:alias */
/*[[[end:libc_gai_suspend64]]]*/





/*[[[start:exports,hash:CRC-32=0x17e37c1b]]]*/
DEFINE_PUBLIC_ALIAS(sethostent, libc_sethostent);
DEFINE_PUBLIC_ALIAS(endhostent, libc_endhostent);
DEFINE_PUBLIC_ALIAS(gethostent, libc_gethostent);
DEFINE_PUBLIC_ALIAS(gethostbyaddr, libc_gethostbyaddr);
DEFINE_PUBLIC_ALIAS(gethostbyname, libc_gethostbyname);
DEFINE_PUBLIC_ALIAS(setnetent, libc_setnetent);
DEFINE_PUBLIC_ALIAS(endnetent, libc_endnetent);
DEFINE_PUBLIC_ALIAS(getnetent, libc_getnetent);
DEFINE_PUBLIC_ALIAS(getnetbyaddr, libc_getnetbyaddr);
DEFINE_PUBLIC_ALIAS(getnetbyname, libc_getnetbyname);
DEFINE_PUBLIC_ALIAS(setservent, libc_setservent);
DEFINE_PUBLIC_ALIAS(endservent, libc_endservent);
DEFINE_PUBLIC_ALIAS(getservent, libc_getservent);
DEFINE_PUBLIC_ALIAS(getservbyname, libc_getservbyname);
DEFINE_PUBLIC_ALIAS(getservbyport, libc_getservbyport);
DEFINE_PUBLIC_ALIAS(setprotoent, libc_setprotoent);
DEFINE_PUBLIC_ALIAS(endprotoent, libc_endprotoent);
DEFINE_PUBLIC_ALIAS(getprotoent, libc_getprotoent);
DEFINE_PUBLIC_ALIAS(getprotobyname, libc_getprotobyname);
DEFINE_PUBLIC_ALIAS(getprotobynumber, libc_getprotobynumber);
DEFINE_PUBLIC_ALIAS(__h_errno_location, libc___h_errno_location);
DEFINE_PUBLIC_ALIAS(herror, libc_herror);
DEFINE_PUBLIC_ALIAS(hstrerror, libc_hstrerror);
DEFINE_PUBLIC_ALIAS(gethostbyname2, libc_gethostbyname2);
DEFINE_PUBLIC_ALIAS(gethostent_r, libc_gethostent_r);
DEFINE_PUBLIC_ALIAS(gethostbyaddr_r, libc_gethostbyaddr_r);
DEFINE_PUBLIC_ALIAS(gethostbyname_r, libc_gethostbyname_r);
DEFINE_PUBLIC_ALIAS(gethostbyname2_r, libc_gethostbyname2_r);
DEFINE_PUBLIC_ALIAS(getnetent_r, libc_getnetent_r);
DEFINE_PUBLIC_ALIAS(getnetbyaddr_r, libc_getnetbyaddr_r);
DEFINE_PUBLIC_ALIAS(getnetbyname_r, libc_getnetbyname_r);
DEFINE_PUBLIC_ALIAS(getservent_r, libc_getservent_r);
DEFINE_PUBLIC_ALIAS(getservbyname_r, libc_getservbyname_r);
DEFINE_PUBLIC_ALIAS(getservbyport_r, libc_getservbyport_r);
DEFINE_PUBLIC_ALIAS(getprotoent_r, libc_getprotoent_r);
DEFINE_PUBLIC_ALIAS(getprotobyname_r, libc_getprotobyname_r);
DEFINE_PUBLIC_ALIAS(getprotobynumber_r, libc_getprotobynumber_r);
DEFINE_PUBLIC_ALIAS(setnetgrent, libc_setnetgrent);
DEFINE_PUBLIC_ALIAS(endnetgrent, libc_endnetgrent);
DEFINE_PUBLIC_ALIAS(getnetgrent, libc_getnetgrent);
DEFINE_PUBLIC_ALIAS(innetgr, libc_innetgr);
DEFINE_PUBLIC_ALIAS(getnetgrent_r, libc_getnetgrent_r);
DEFINE_PUBLIC_ALIAS(rcmd, libc_rcmd);
DEFINE_PUBLIC_ALIAS(rcmd_af, libc_rcmd_af);
DEFINE_PUBLIC_ALIAS(rexec, libc_rexec);
DEFINE_PUBLIC_ALIAS(rexec_af, libc_rexec_af);
DEFINE_PUBLIC_ALIAS(ruserok, libc_ruserok);
DEFINE_PUBLIC_ALIAS(ruserok_af, libc_ruserok_af);
DEFINE_PUBLIC_ALIAS(iruserok, libc_iruserok);
DEFINE_PUBLIC_ALIAS(iruserok_af, libc_iruserok_af);
DEFINE_PUBLIC_ALIAS(rresvport, libc_rresvport);
DEFINE_PUBLIC_ALIAS(rresvport_af, libc_rresvport_af);
DEFINE_PUBLIC_ALIAS(getaddrinfo, libc_getaddrinfo);
DEFINE_PUBLIC_ALIAS(freeaddrinfo, libc_freeaddrinfo);
DEFINE_PUBLIC_ALIAS(gai_strerror, libc_gai_strerror);
DEFINE_PUBLIC_ALIAS(getnameinfo, libc_getnameinfo);
DEFINE_PUBLIC_ALIAS(getaddrinfo_a, libc_getaddrinfo_a);
DEFINE_PUBLIC_ALIAS(gai_error, libc_gai_error);
DEFINE_PUBLIC_ALIAS(gai_cancel, libc_gai_cancel);
DEFINE_PUBLIC_ALIAS(gai_suspend, libc_gai_suspend);
DEFINE_PUBLIC_ALIAS(gai_suspend64, libc_gai_suspend64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_NETDB_C */
