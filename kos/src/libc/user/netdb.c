/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef GUARD_LIBC_USER_NETDB_C
#define GUARD_LIBC_USER_NETDB_C 1

#include "../api.h"
#include "netdb.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:__h_errno_location,hash:0x99f94bd1]]]*/
/* Function to get address of global `h_errno' variable */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.net.db.__h_errno_location") int *
NOTHROW_NCX(LIBCCALL libc___h_errno_location)(void)
/*[[[body:__h_errno_location]]]*/
{
	CRT_UNIMPLEMENTED("__h_errno_location"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:__h_errno_location]]]*/

/*[[[head:herror,hash:0x3ea5bf10]]]*/
/* Print error indicated by `h_errno' variable on standard error.
 * STR, if non-null, is printed before the error string */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.herror") void
NOTHROW_RPC(LIBCCALL libc_herror)(char const *str)
/*[[[body:herror]]]*/
{
	CRT_UNIMPLEMENTED("herror"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:herror]]]*/

/*[[[head:hstrerror,hash:0xd71518c4]]]*/
/* Return string associated with error ERR_NUM */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.net.db.hstrerror") char const *
NOTHROW_NCX(LIBCCALL libc_hstrerror)(int err_num)
/*[[[body:hstrerror]]]*/
{
	CRT_UNIMPLEMENTED("hstrerror"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:hstrerror]]]*/

/*[[[head:sethostent,hash:0x396ae22]]]*/
/* Open host data base files and mark them as staying
 * open even after a later search if STAY_OPEN is non-zero */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.sethostent") void
NOTHROW_RPC(LIBCCALL libc_sethostent)(int stay_open)
/*[[[body:sethostent]]]*/
{
	CRT_UNIMPLEMENTED("sethostent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:sethostent]]]*/

/*[[[head:endhostent,hash:0xd0a667f6]]]*/
/* Close host data base files and clear `stay open' flag */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.endhostent") void
NOTHROW_NCX(LIBCCALL libc_endhostent)(void)
/*[[[body:endhostent]]]*/
{
	CRT_UNIMPLEMENTED("endhostent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:endhostent]]]*/

/*[[[head:gethostent,hash:0xe067a892]]]*/
/* Get next entry from host data base file. Open data base if necessary */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.gethostent") struct hostent *
NOTHROW_RPC(LIBCCALL libc_gethostent)(void)
/*[[[body:gethostent]]]*/
{
	CRT_UNIMPLEMENTED("gethostent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:gethostent]]]*/

/*[[[head:gethostbyaddr,hash:0xe285965e]]]*/
/* Return entry from host data base which address match ADDR with length LEN and type TYPE */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.gethostbyaddr") struct hostent *
NOTHROW_RPC(LIBCCALL libc_gethostbyaddr)(void const *addr,
                                         socklen_t len,
                                         int type)
/*[[[body:gethostbyaddr]]]*/
{
	CRT_UNIMPLEMENTED("gethostbyaddr"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:gethostbyaddr]]]*/

/*[[[head:gethostbyname,hash:0x6617ca6e]]]*/
/* Return entry from host data base for host with NAME */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.gethostbyname") struct hostent *
NOTHROW_RPC(LIBCCALL libc_gethostbyname)(char const *name)
/*[[[body:gethostbyname]]]*/
{
	CRT_UNIMPLEMENTED("gethostbyname"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:gethostbyname]]]*/

/*[[[head:gethostbyname2,hash:0x9ae87c62]]]*/
/* Return entry from host data base for host with NAME. AF must be
 * set to the address type which is `AF_INET' for IPv4 or `AF_INET6'
 * for IPv6.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.gethostbyname2") struct hostent *
NOTHROW_RPC(LIBCCALL libc_gethostbyname2)(char const *name,
                                          int af)
/*[[[body:gethostbyname2]]]*/
{
	CRT_UNIMPLEMENTED("gethostbyname2"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:gethostbyname2]]]*/

/*[[[head:gethostent_r,hash:0x684787a1]]]*/
/* Reentrant versions of the functions above. The additional arguments
 * specify a buffer of BUFLEN starting at BUF. The last argument is a
 * pointer to a variable which gets the value which would be stored in
 * the global variable `herrno' by the non-reentrant functions.
 * These functions are not part of POSIX and therefore no official cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.gethostent_r") int
NOTHROW_RPC(LIBCCALL libc_gethostent_r)(struct hostent *__restrict result_buf,
                                        char *__restrict buf,
                                        size_t buflen,
                                        struct hostent **__restrict result,
                                        int *__restrict h_errnop)
/*[[[body:gethostent_r]]]*/
{
	CRT_UNIMPLEMENTED("gethostent_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:gethostent_r]]]*/

/*[[[head:gethostbyaddr_r,hash:0xc91a1cc2]]]*/
/* Reentrant versions of the functions above. The additional arguments
 * specify a buffer of BUFLEN starting at BUF. The last argument is a
 * pointer to a variable which gets the value which would be stored in
 * the global variable `herrno' by the non-reentrant functions.
 * These functions are not part of POSIX and therefore no official cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.gethostbyaddr_r") int
NOTHROW_RPC(LIBCCALL libc_gethostbyaddr_r)(void const *__restrict addr,
                                           socklen_t len,
                                           int type,
                                           struct hostent *__restrict result_buf,
                                           char *__restrict buf,
                                           size_t buflen,
                                           struct hostent **__restrict result,
                                           int *__restrict h_errnop)
/*[[[body:gethostbyaddr_r]]]*/
{
	CRT_UNIMPLEMENTED("gethostbyaddr_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:gethostbyaddr_r]]]*/

/*[[[head:gethostbyname_r,hash:0x9f3b757a]]]*/
/* Reentrant versions of the functions above. The additional arguments
 * specify a buffer of BUFLEN starting at BUF. The last argument is a
 * pointer to a variable which gets the value which would be stored in
 * the global variable `herrno' by the non-reentrant functions.
 * These functions are not part of POSIX and therefore no official cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.gethostbyname_r") int
NOTHROW_RPC(LIBCCALL libc_gethostbyname_r)(char const *__restrict name,
                                           struct hostent *__restrict result_buf,
                                           char *__restrict buf,
                                           size_t buflen,
                                           struct hostent **__restrict result,
                                           int *__restrict h_errnop)
/*[[[body:gethostbyname_r]]]*/
{
	CRT_UNIMPLEMENTED("gethostbyname_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:gethostbyname_r]]]*/

/*[[[head:gethostbyname2_r,hash:0x4416a039]]]*/
/* Reentrant versions of the functions above. The additional arguments
 * specify a buffer of BUFLEN starting at BUF. The last argument is a
 * pointer to a variable which gets the value which would be stored in
 * the global variable `herrno' by the non-reentrant functions.
 * These functions are not part of POSIX and therefore no official cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.gethostbyname2_r") int
NOTHROW_RPC(LIBCCALL libc_gethostbyname2_r)(char const *__restrict name,
                                            int af,
                                            struct hostent *__restrict result_buf,
                                            char *__restrict buf,
                                            size_t buflen,
                                            struct hostent **__restrict result,
                                            int *__restrict h_errnop)
/*[[[body:gethostbyname2_r]]]*/
{
	CRT_UNIMPLEMENTED("gethostbyname2_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:gethostbyname2_r]]]*/

/*[[[head:setnetent,hash:0xa72e77f9]]]*/
/* Open network data base files and mark them as staying
 * open even after a later search if STAY_OPEN is non-zero */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.setnetent") void
NOTHROW_RPC(LIBCCALL libc_setnetent)(int stay_open)
/*[[[body:setnetent]]]*/
{
	CRT_UNIMPLEMENTED("setnetent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:setnetent]]]*/

/*[[[head:endnetent,hash:0xf4ba4ec1]]]*/
/* Close network data base files and clear `stay open' flag */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.endnetent") void
NOTHROW_RPC_NOKOS(LIBCCALL libc_endnetent)(void)
/*[[[body:endnetent]]]*/
{
	CRT_UNIMPLEMENTED("endnetent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:endnetent]]]*/

/*[[[head:getnetent,hash:0x85fe8738]]]*/
/* Get next entry from network data base file. Open data base if necessary */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.getnetent") struct netent *
NOTHROW_RPC(LIBCCALL libc_getnetent)(void)
/*[[[body:getnetent]]]*/
{
	CRT_UNIMPLEMENTED("getnetent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:getnetent]]]*/

/*[[[head:getnetbyaddr,hash:0xbe1b41a]]]*/
/* Return entry from network data base which address match NET and type TYPE */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.getnetbyaddr") struct netent *
NOTHROW_RPC(LIBCCALL libc_getnetbyaddr)(uint32_t net,
                                        int type)
/*[[[body:getnetbyaddr]]]*/
{
	CRT_UNIMPLEMENTED("getnetbyaddr"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:getnetbyaddr]]]*/

/*[[[head:getnetbyname,hash:0x5c63559]]]*/
/* Return entry from network data base for network with NAME */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.getnetbyname") struct netent *
NOTHROW_RPC(LIBCCALL libc_getnetbyname)(char const *name)
/*[[[body:getnetbyname]]]*/
{
	CRT_UNIMPLEMENTED("getnetbyname"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:getnetbyname]]]*/

/*[[[head:getnetent_r,hash:0xa2a0f831]]]*/
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF. The last
 * argument is a pointer to a variable which gets the value which
 * would be stored in the global variable `herrno' by the
 * non-reentrant functions.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.getnetent_r") int
NOTHROW_RPC(LIBCCALL libc_getnetent_r)(struct netent *__restrict result_buf,
                                       char *__restrict buf,
                                       size_t buflen,
                                       struct netent **__restrict result,
                                       int *__restrict h_errnop)
/*[[[body:getnetent_r]]]*/
{
	CRT_UNIMPLEMENTED("getnetent_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getnetent_r]]]*/

/*[[[head:getnetbyaddr_r,hash:0x331ed394]]]*/
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF. The last
 * argument is a pointer to a variable which gets the value which
 * would be stored in the global variable `herrno' by the
 * non-reentrant functions.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.getnetbyaddr_r") int
NOTHROW_RPC(LIBCCALL libc_getnetbyaddr_r)(uint32_t net,
                                          int type,
                                          struct netent *__restrict result_buf,
                                          char *__restrict buf,
                                          size_t buflen,
                                          struct netent **__restrict result,
                                          int *__restrict h_errnop)
/*[[[body:getnetbyaddr_r]]]*/
{
	CRT_UNIMPLEMENTED("getnetbyaddr_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getnetbyaddr_r]]]*/

/*[[[head:getnetbyname_r,hash:0xa8170ac3]]]*/
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF. The last
 * argument is a pointer to a variable which gets the value which
 * would be stored in the global variable `herrno' by the
 * non-reentrant functions.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.getnetbyname_r") int
NOTHROW_RPC(LIBCCALL libc_getnetbyname_r)(char const *__restrict name,
                                          struct netent *__restrict result_buf,
                                          char *__restrict buf,
                                          size_t buflen,
                                          struct netent **__restrict result,
                                          int *__restrict h_errnop)
/*[[[body:getnetbyname_r]]]*/
{
	CRT_UNIMPLEMENTED("getnetbyname_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getnetbyname_r]]]*/

/*[[[head:setservent,hash:0x8a50d3d1]]]*/
/* Open service data base files and mark them as staying open even
 * after a later search if STAY_OPEN is non-zero */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.setservent") void
NOTHROW_RPC(LIBCCALL libc_setservent)(int stay_open)
/*[[[body:setservent]]]*/
{
	CRT_UNIMPLEMENTED("setservent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:setservent]]]*/

/*[[[head:endservent,hash:0xc832ea74]]]*/
/* Close service data base files and clear `stay open' flag */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.endservent") void
NOTHROW_RPC_NOKOS(LIBCCALL libc_endservent)(void)
/*[[[body:endservent]]]*/
{
	CRT_UNIMPLEMENTED("endservent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:endservent]]]*/

/*[[[head:getservent,hash:0x20b8b5b4]]]*/
/* Get next entry from service data base file. Open data base if necessary */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.getservent") struct servent *
NOTHROW_RPC(LIBCCALL libc_getservent)(void)
/*[[[body:getservent]]]*/
{
	CRT_UNIMPLEMENTED("getservent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:getservent]]]*/

/*[[[head:getservbyname,hash:0x4437d51c]]]*/
/* Return entry from network data base for network with NAME and protocol PROTO */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.getservbyname") struct servent *
NOTHROW_RPC(LIBCCALL libc_getservbyname)(char const *name,
                                         char const *proto)
/*[[[body:getservbyname]]]*/
{
	CRT_UNIMPLEMENTED("getservbyname"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:getservbyname]]]*/

/*[[[head:getservbyport,hash:0xb93ec65]]]*/
/* Return entry from service data base which matches port PORT and protocol PROTO */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.getservbyport") struct servent *
NOTHROW_RPC(LIBCCALL libc_getservbyport)(int port,
                                         char const *proto)
/*[[[body:getservbyport]]]*/
{
	CRT_UNIMPLEMENTED("getservbyport"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:getservbyport]]]*/

/*[[[head:getservent_r,hash:0x3b36ac90]]]*/
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.getservent_r") int
NOTHROW_RPC(LIBCCALL libc_getservent_r)(struct servent *__restrict result_buf,
                                        char *__restrict buf,
                                        size_t buflen,
                                        struct servent **__restrict result)
/*[[[body:getservent_r]]]*/
{
	CRT_UNIMPLEMENTED("getservent_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getservent_r]]]*/

/*[[[head:getservbyname_r,hash:0xf5dd54f9]]]*/
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.getservbyname_r") int
NOTHROW_RPC(LIBCCALL libc_getservbyname_r)(char const *__restrict name,
                                           char const *__restrict __proto,
                                           struct servent *__restrict result_buf,
                                           char *__restrict buf,
                                           size_t buflen,
                                           struct servent **__restrict result)
/*[[[body:getservbyname_r]]]*/
{
	CRT_UNIMPLEMENTED("getservbyname_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getservbyname_r]]]*/

/*[[[head:getservbyport_r,hash:0xfbd4c1de]]]*/
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.getservbyport_r") int
NOTHROW_RPC(LIBCCALL libc_getservbyport_r)(int __port,
                                           char const *__restrict __proto,
                                           struct servent *__restrict result_buf,
                                           char *__restrict buf,
                                           size_t buflen,
                                           struct servent **__restrict result)
/*[[[body:getservbyport_r]]]*/
{
	CRT_UNIMPLEMENTED("getservbyport_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getservbyport_r]]]*/

/*[[[head:setprotoent,hash:0x16f6c066]]]*/
/* Open protocol data base files and mark them as staying open even
 * after a later search if STAY_OPEN is non-zero */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.setprotoent") void
NOTHROW_RPC(LIBCCALL libc_setprotoent)(int stay_open)
/*[[[body:setprotoent]]]*/
{
	CRT_UNIMPLEMENTED("setprotoent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:setprotoent]]]*/

/*[[[head:endprotoent,hash:0xa81ee0af]]]*/
/* Close protocol data base files and clear `stay open' flag */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.endprotoent") void
NOTHROW_RPC_NOKOS(LIBCCALL libc_endprotoent)(void)
/*[[[body:endprotoent]]]*/
{
	CRT_UNIMPLEMENTED("endprotoent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:endprotoent]]]*/

/*[[[head:getprotoent,hash:0x66380fde]]]*/
/* Get next entry from protocol data base file. Open data base if necessary */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.getprotoent") struct protoent *
NOTHROW_RPC(LIBCCALL libc_getprotoent)(void)
/*[[[body:getprotoent]]]*/
{
	CRT_UNIMPLEMENTED("getprotoent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:getprotoent]]]*/

/*[[[head:getprotobyname,hash:0xd2d06248]]]*/
/* Return entry from protocol data base for network with NAME */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.getprotobyname") struct protoent *
NOTHROW_RPC(LIBCCALL libc_getprotobyname)(char const *name)
/*[[[body:getprotobyname]]]*/
{
	CRT_UNIMPLEMENTED("getprotobyname"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:getprotobyname]]]*/

/*[[[head:getprotobynumber,hash:0x2d073da5]]]*/
/* Return entry from protocol data base which number is PROTO */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.getprotobynumber") struct protoent *
NOTHROW_RPC(LIBCCALL libc_getprotobynumber)(int proto)
/*[[[body:getprotobynumber]]]*/
{
	CRT_UNIMPLEMENTED("getprotobynumber"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:getprotobynumber]]]*/

/*[[[head:getprotoent_r,hash:0xaf17698c]]]*/
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.getprotoent_r") int
NOTHROW_RPC(LIBCCALL libc_getprotoent_r)(struct protoent *__restrict result_buf,
                                         char *__restrict buf,
                                         size_t buflen,
                                         struct protoent **__restrict result)
/*[[[body:getprotoent_r]]]*/
{
	CRT_UNIMPLEMENTED("getprotoent_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getprotoent_r]]]*/

/*[[[head:getprotobyname_r,hash:0xc3f15c9b]]]*/
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.getprotobyname_r") int
NOTHROW_RPC(LIBCCALL libc_getprotobyname_r)(char const *__restrict name,
                                            struct protoent *__restrict result_buf,
                                            char *__restrict buf,
                                            size_t buflen,
                                            struct protoent **__restrict result)
/*[[[body:getprotobyname_r]]]*/
{
	CRT_UNIMPLEMENTED("getprotobyname_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getprotobyname_r]]]*/

/*[[[head:getprotobynumber_r,hash:0xf9efa4c6]]]*/
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.getprotobynumber_r") int
NOTHROW_RPC(LIBCCALL libc_getprotobynumber_r)(int __proto,
                                              struct protoent *__restrict result_buf,
                                              char *__restrict buf,
                                              size_t buflen,
                                              struct protoent **__restrict result)
/*[[[body:getprotobynumber_r]]]*/
{
	CRT_UNIMPLEMENTED("getprotobynumber_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getprotobynumber_r]]]*/

/*[[[head:setnetgrent,hash:0xe6ee459b]]]*/
/* Establish network group NETGROUP for enumeration.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.setnetgrent") int
NOTHROW_RPC(LIBCCALL libc_setnetgrent)(char const *netgroup)
/*[[[body:setnetgrent]]]*/
{
	CRT_UNIMPLEMENTED("setnetgrent"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:setnetgrent]]]*/

/*[[[head:endnetgrent,hash:0x30dd7292]]]*/
/* Free all space allocated by previous `setnetgrent' call.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.endnetgrent") void
NOTHROW_RPC_NOKOS(LIBCCALL libc_endnetgrent)(void)
/*[[[body:endnetgrent]]]*/
{
	CRT_UNIMPLEMENTED("endnetgrent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:endnetgrent]]]*/

/*[[[head:getnetgrent,hash:0xa44728dc]]]*/
/* Get next member of netgroup established by last `setnetgrent' call
 * and return pointers to elements in HOSTP, USERP, and DOMAINP.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.getnetgrent") int
NOTHROW_RPC(LIBCCALL libc_getnetgrent)(char **__restrict hostp,
                                       char **__restrict userp,
                                       char **__restrict domainp)
/*[[[body:getnetgrent]]]*/
{
	CRT_UNIMPLEMENTED("getnetgrent"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getnetgrent]]]*/

/*[[[head:innetgr,hash:0x70e59e5b]]]*/
/* Test whether NETGROUP contains the triple (HOST, USER, DOMAIN).
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.innetgr") int
NOTHROW_RPC(LIBCCALL libc_innetgr)(char const *netgroup,
                                   char const *host,
                                   char const *user,
                                   char const *domain)
/*[[[body:innetgr]]]*/
{
	CRT_UNIMPLEMENTED("innetgr"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:innetgr]]]*/

/*[[[head:getnetgrent_r,hash:0xaf11a177]]]*/
/* Reentrant version of `getnetgrent' where result is placed in BUFFER.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.getnetgrent_r") int
NOTHROW_RPC(LIBCCALL libc_getnetgrent_r)(char **__restrict hostp,
                                         char **__restrict userp,
                                         char **__restrict domainp,
                                         char *__restrict buf,
                                         size_t buflen)
/*[[[body:getnetgrent_r]]]*/
{
	CRT_UNIMPLEMENTED("getnetgrent_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getnetgrent_r]]]*/

/*[[[head:rcmd,hash:0x55ddd004]]]*/
/* Call `rshd' at port RPORT on remote machine *AHOST to execute CMD.
 * The local user is LOCUSER, on the remote machine the command is
 * executed as REMUSER. In *FD2P the descriptor to the socket for the
 * connection is returned. The caller must have the right to use a
 * reserved port. When the function returns *AHOST contains the
 * official host name.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.rcmd") int
NOTHROW_RPC(LIBCCALL libc_rcmd)(char **__restrict ahost,
                                uint16_t rport,
                                char const *__restrict locuser,
                                char const *__restrict remuser,
                                char const *__restrict cmd,
                                int *__restrict fd2p)
/*[[[body:rcmd]]]*/
{
	CRT_UNIMPLEMENTED("rcmd"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:rcmd]]]*/

/*[[[head:rcmd_af,hash:0x7f018fba]]]*/
/* This is the equivalent function where the protocol can be selected
 * and which therefore can be used for IPv6.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.rcmd_af") int
NOTHROW_RPC(LIBCCALL libc_rcmd_af)(char **__restrict ahost,
                                   uint16_t rport,
                                   char const *__restrict locuser,
                                   char const *__restrict remuser,
                                   char const *__restrict cmd,
                                   int *__restrict fd2p,
                                   sa_family_t af)
/*[[[body:rcmd_af]]]*/
{
	CRT_UNIMPLEMENTED("rcmd_af"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:rcmd_af]]]*/

/*[[[head:rexec,hash:0xbcb04022]]]*/
/* Call `rexecd' at port RPORT on remote machine *AHOST to execute
 * CMD. The process runs at the remote machine using the ID of user
 * NAME whose cleartext password is PASSWD. In *FD2P the descriptor
 * to the socket for the connection is returned. When the function
 * returns *AHOST contains the official host name.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.rexec") int
NOTHROW_RPC(LIBCCALL libc_rexec)(char **__restrict ahost,
                                 int rport,
                                 char const *__restrict name,
                                 char const *__restrict pass,
                                 char const *__restrict cmd,
                                 int *__restrict fd2p)
/*[[[body:rexec]]]*/
{
	CRT_UNIMPLEMENTED("rexec"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:rexec]]]*/

/*[[[head:rexec_af,hash:0xcb8363a2]]]*/
/* This is the equivalent function where the protocol can be selected
 * and which therefore can be used for IPv6.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.rexec_af") int
NOTHROW_RPC(LIBCCALL libc_rexec_af)(char **__restrict ahost,
                                    int rport,
                                    char const *__restrict name,
                                    char const *__restrict pass,
                                    char const *__restrict cmd,
                                    int *__restrict fd2p,
                                    sa_family_t af)
/*[[[body:rexec_af]]]*/
{
	CRT_UNIMPLEMENTED("rexec_af"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:rexec_af]]]*/

/*[[[head:ruserok,hash:0x49373566]]]*/
/* Check whether user REMUSER on system RHOST is allowed to login as LOCUSER.
 * If SUSER is not zero the user tries to become superuser. Return 0 if
 * it is possible.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.ruserok") int
NOTHROW_RPC(LIBCCALL libc_ruserok)(char const *rhost,
                                   int suser,
                                   char const *remuser,
                                   char const *locuser)
/*[[[body:ruserok]]]*/
{
	CRT_UNIMPLEMENTED("ruserok"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:ruserok]]]*/

/*[[[head:ruserok_af,hash:0x3125e165]]]*/
/* This is the equivalent function where the protocol can be selected
 * and which therefore can be used for IPv6.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.ruserok_af") int
NOTHROW_RPC(LIBCCALL libc_ruserok_af)(char const *rhost,
                                      int suser,
                                      char const *remuser,
                                      char const *locuser,
                                      sa_family_t af)
/*[[[body:ruserok_af]]]*/
{
	CRT_UNIMPLEMENTED("ruserok_af"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:ruserok_af]]]*/

/*[[[head:iruserok,hash:0x8f07e2d1]]]*/
/* Check whether user REMUSER on system indicated by IPv4 address
 * RADDR is allowed to login as LOCUSER. Non-IPv4 (e.g., IPv6) are
 * not supported. If SUSER is not zero the user tries to become
 * superuser. Return 0 if it is possible.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.iruserok") int
NOTHROW_RPC(LIBCCALL libc_iruserok)(uint32_t raddr,
                                    int suser,
                                    char const *remuser,
                                    char const *locuser)
/*[[[body:iruserok]]]*/
{
	CRT_UNIMPLEMENTED("iruserok"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:iruserok]]]*/

/*[[[head:iruserok_af,hash:0x7c8d5b15]]]*/
/* This is the equivalent function where the pfamiliy if the address
 * pointed to by RADDR is determined by the value of AF. It therefore
 * can be used for IPv6
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.iruserok_af") int
NOTHROW_RPC(LIBCCALL libc_iruserok_af)(void const *raddr,
                                       int suser,
                                       char const *remuser,
                                       char const *locuser,
                                       sa_family_t af)
/*[[[body:iruserok_af]]]*/
{
	CRT_UNIMPLEMENTED("iruserok_af"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:iruserok_af]]]*/

/*[[[head:rresvport,hash:0xcccf24a6]]]*/
/* Try to allocate reserved port, returning a descriptor for a socket opened
 * at this port or -1 if unsuccessful. The search for an available port
 * will start at ALPORT and continues with lower numbers.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.rresvport") int
NOTHROW_RPC(LIBCCALL libc_rresvport)(int *alport)
/*[[[body:rresvport]]]*/
{
	CRT_UNIMPLEMENTED("rresvport"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:rresvport]]]*/

/*[[[head:rresvport_af,hash:0xebe85ab3]]]*/
/* This is the equivalent function where the protocol can be selected
 * and which therefore can be used for IPv6.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.rresvport_af") int
NOTHROW_RPC(LIBCCALL libc_rresvport_af)(int *alport,
                                        sa_family_t af)
/*[[[body:rresvport_af]]]*/
{
	CRT_UNIMPLEMENTED("rresvport_af"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:rresvport_af]]]*/

/*[[[head:getaddrinfo,hash:0x538e1efb]]]*/
/* Translate name of a service location and/or a service name to set of socket addresses */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.getaddrinfo") int
NOTHROW_RPC(LIBCCALL libc_getaddrinfo)(char const *__restrict name,
                                       char const *__restrict service,
                                       const struct addrinfo *__restrict req,
                                       struct addrinfo **__restrict pai)
/*[[[body:getaddrinfo]]]*/
{
	CRT_UNIMPLEMENTED("getaddrinfo"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getaddrinfo]]]*/

/*[[[head:freeaddrinfo,hash:0x774b4a04]]]*/
/* Free `addrinfo' structure AI including associated storage */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.freeaddrinfo") void
NOTHROW_NCX(LIBCCALL libc_freeaddrinfo)(struct addrinfo *ai)
/*[[[body:freeaddrinfo]]]*/
{
	CRT_UNIMPLEMENTED("freeaddrinfo"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:freeaddrinfo]]]*/

/*[[[head:gai_strerror,hash:0xc483c1c6]]]*/
/* Convert error return from getaddrinfo() to a string */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.net.db.gai_strerror") char const *
NOTHROW_NCX(LIBCCALL libc_gai_strerror)(int ecode)
/*[[[body:gai_strerror]]]*/
{
	CRT_UNIMPLEMENTED("gai_strerror"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:gai_strerror]]]*/

/*[[[head:getnameinfo,hash:0x565a573]]]*/
/* Translate a socket address to a location and service name */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.getnameinfo") int
NOTHROW_RPC(LIBCCALL libc_getnameinfo)(struct sockaddr const *__restrict sa,
                                       socklen_t salen,
                                       char *__restrict host,
                                       socklen_t hostlen,
                                       char *__restrict serv,
                                       socklen_t servlen,
                                       int flags)
/*[[[body:getnameinfo]]]*/
{
	CRT_UNIMPLEMENTED("getnameinfo"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getnameinfo]]]*/

/*[[[head:getaddrinfo_a,hash:0xeaa2b68e]]]*/
/* Enqueue ENT requests from the LIST. If MODE is GAI_WAIT wait until all
 * requests are handled. If WAIT is GAI_NOWAIT return immediately after
 * queueing the requests and signal completion according to SIG.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.getaddrinfo_a") int
NOTHROW_RPC(LIBCCALL libc_getaddrinfo_a)(int mode,
                                         struct gaicb *list[__restrict_arr],
                                         int ent,
                                         struct sigevent *__restrict sig)
/*[[[body:getaddrinfo_a]]]*/
{
	CRT_UNIMPLEMENTED("getaddrinfo_a"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getaddrinfo_a]]]*/

/*[[[head:gai_suspend,hash:0x312fe314]]]*/
/* Suspend execution of the thread until at least one of the ENT requests
 * in LIST is handled. If TIMEOUT is not a null pointer it specifies the
 * longest time the function keeps waiting before returning with an error.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.gai_suspend") int
NOTHROW_RPC(LIBCCALL libc_gai_suspend)(struct gaicb const *const list[],
                                       int ent,
                                       struct timespec const *timeout)
/*[[[body:gai_suspend]]]*/
{
	CRT_UNIMPLEMENTED("gai_suspend"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:gai_suspend]]]*/

/*[[[head:gai_error,hash:0x8e5a7910]]]*/
/* Get the error status of the request REQ */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.gai_error") int
NOTHROW_NCX(LIBCCALL libc_gai_error)(struct gaicb *req)
/*[[[body:gai_error]]]*/
{
	CRT_UNIMPLEMENTED("gai_error"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:gai_error]]]*/

/*[[[head:gai_cancel,hash:0x964f3107]]]*/
/* Cancel the requests associated with GAICBP */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.gai_cancel") int
NOTHROW_NCX(LIBCCALL libc_gai_cancel)(struct gaicb *gaicbp)
/*[[[body:gai_cancel]]]*/
{
	CRT_UNIMPLEMENTED("gai_cancel"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:gai_cancel]]]*/

/*[[[head:gai_suspend64,hash:0x4d7d39d5]]]*/
/* Suspend execution of the thread until at least one of the ENT requests
 * in LIST is handled. If TIMEOUT is not a null pointer it specifies the
 * longest time the function keeps waiting before returning with an error.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_gai_suspend64, libc_gai_suspend);
#else
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.db.gai_suspend64") int
NOTHROW_RPC(LIBCCALL libc_gai_suspend64)(struct gaicb const *const list[],
                                         int ent,
                                         struct timespec64 const *timeout)
/*[[[body:gai_suspend64]]]*/
{
	CRT_UNIMPLEMENTED("gai_suspend64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
#endif /* MAGIC:alias */
/*[[[end:gai_suspend64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0x5b587244]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(__h_errno_location, libc___h_errno_location);
DEFINE_PUBLIC_WEAK_ALIAS(herror, libc_herror);
DEFINE_PUBLIC_WEAK_ALIAS(hstrerror, libc_hstrerror);
DEFINE_PUBLIC_WEAK_ALIAS(sethostent, libc_sethostent);
DEFINE_PUBLIC_WEAK_ALIAS(endhostent, libc_endhostent);
DEFINE_PUBLIC_WEAK_ALIAS(gethostent, libc_gethostent);
DEFINE_PUBLIC_WEAK_ALIAS(gethostbyaddr, libc_gethostbyaddr);
DEFINE_PUBLIC_WEAK_ALIAS(gethostbyname, libc_gethostbyname);
DEFINE_PUBLIC_WEAK_ALIAS(gethostbyname2, libc_gethostbyname2);
DEFINE_PUBLIC_WEAK_ALIAS(gethostent_r, libc_gethostent_r);
DEFINE_PUBLIC_WEAK_ALIAS(gethostbyaddr_r, libc_gethostbyaddr_r);
DEFINE_PUBLIC_WEAK_ALIAS(gethostbyname_r, libc_gethostbyname_r);
DEFINE_PUBLIC_WEAK_ALIAS(gethostbyname2_r, libc_gethostbyname2_r);
DEFINE_PUBLIC_WEAK_ALIAS(setnetent, libc_setnetent);
DEFINE_PUBLIC_WEAK_ALIAS(endnetent, libc_endnetent);
DEFINE_PUBLIC_WEAK_ALIAS(getnetent, libc_getnetent);
DEFINE_PUBLIC_WEAK_ALIAS(getnetbyaddr, libc_getnetbyaddr);
DEFINE_PUBLIC_WEAK_ALIAS(getnetbyname, libc_getnetbyname);
DEFINE_PUBLIC_WEAK_ALIAS(getnetent_r, libc_getnetent_r);
DEFINE_PUBLIC_WEAK_ALIAS(getnetbyaddr_r, libc_getnetbyaddr_r);
DEFINE_PUBLIC_WEAK_ALIAS(getnetbyname_r, libc_getnetbyname_r);
DEFINE_PUBLIC_WEAK_ALIAS(setservent, libc_setservent);
DEFINE_PUBLIC_WEAK_ALIAS(endservent, libc_endservent);
DEFINE_PUBLIC_WEAK_ALIAS(getservent, libc_getservent);
DEFINE_PUBLIC_WEAK_ALIAS(getservbyname, libc_getservbyname);
DEFINE_PUBLIC_WEAK_ALIAS(getservbyport, libc_getservbyport);
DEFINE_PUBLIC_WEAK_ALIAS(getservent_r, libc_getservent_r);
DEFINE_PUBLIC_WEAK_ALIAS(getservbyname_r, libc_getservbyname_r);
DEFINE_PUBLIC_WEAK_ALIAS(getservbyport_r, libc_getservbyport_r);
DEFINE_PUBLIC_WEAK_ALIAS(setprotoent, libc_setprotoent);
DEFINE_PUBLIC_WEAK_ALIAS(endprotoent, libc_endprotoent);
DEFINE_PUBLIC_WEAK_ALIAS(getprotoent, libc_getprotoent);
DEFINE_PUBLIC_WEAK_ALIAS(getprotobyname, libc_getprotobyname);
DEFINE_PUBLIC_WEAK_ALIAS(getprotobynumber, libc_getprotobynumber);
DEFINE_PUBLIC_WEAK_ALIAS(getprotoent_r, libc_getprotoent_r);
DEFINE_PUBLIC_WEAK_ALIAS(getprotobyname_r, libc_getprotobyname_r);
DEFINE_PUBLIC_WEAK_ALIAS(getprotobynumber_r, libc_getprotobynumber_r);
DEFINE_PUBLIC_WEAK_ALIAS(setnetgrent, libc_setnetgrent);
DEFINE_PUBLIC_WEAK_ALIAS(endnetgrent, libc_endnetgrent);
DEFINE_PUBLIC_WEAK_ALIAS(getnetgrent, libc_getnetgrent);
DEFINE_PUBLIC_WEAK_ALIAS(innetgr, libc_innetgr);
DEFINE_PUBLIC_WEAK_ALIAS(getnetgrent_r, libc_getnetgrent_r);
DEFINE_PUBLIC_WEAK_ALIAS(rcmd, libc_rcmd);
DEFINE_PUBLIC_WEAK_ALIAS(rcmd_af, libc_rcmd_af);
DEFINE_PUBLIC_WEAK_ALIAS(rexec, libc_rexec);
DEFINE_PUBLIC_WEAK_ALIAS(rexec_af, libc_rexec_af);
DEFINE_PUBLIC_WEAK_ALIAS(ruserok, libc_ruserok);
DEFINE_PUBLIC_WEAK_ALIAS(ruserok_af, libc_ruserok_af);
DEFINE_PUBLIC_WEAK_ALIAS(iruserok, libc_iruserok);
DEFINE_PUBLIC_WEAK_ALIAS(iruserok_af, libc_iruserok_af);
DEFINE_PUBLIC_WEAK_ALIAS(rresvport, libc_rresvport);
DEFINE_PUBLIC_WEAK_ALIAS(rresvport_af, libc_rresvport_af);
DEFINE_PUBLIC_WEAK_ALIAS(getaddrinfo, libc_getaddrinfo);
DEFINE_PUBLIC_WEAK_ALIAS(freeaddrinfo, libc_freeaddrinfo);
DEFINE_PUBLIC_WEAK_ALIAS(gai_strerror, libc_gai_strerror);
DEFINE_PUBLIC_WEAK_ALIAS(getnameinfo, libc_getnameinfo);
DEFINE_PUBLIC_WEAK_ALIAS(getaddrinfo_a, libc_getaddrinfo_a);
DEFINE_PUBLIC_WEAK_ALIAS(gai_suspend, libc_gai_suspend);
DEFINE_PUBLIC_WEAK_ALIAS(gai_suspend64, libc_gai_suspend64);
DEFINE_PUBLIC_WEAK_ALIAS(gai_error, libc_gai_error);
DEFINE_PUBLIC_WEAK_ALIAS(gai_cancel, libc_gai_cancel);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_NETDB_C */
