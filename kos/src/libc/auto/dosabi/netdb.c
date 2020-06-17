/* HASH CRC-32:0xdee3cf3 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_NETDB_C
#define GUARD_LIBC_AUTO_DOSABI_NETDB_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/netdb.h"

DECL_BEGIN

/* Print error indicated by `h_errno' variable on standard error.
 * STR, if non-null, is printed before the error string */
INTERN ATTR_SECTION(".text.crt.dos.net.db") void
NOTHROW_RPC(LIBDCALL libd_herror)(char const *str) {
	libc_herror(str);
}
/* Return string associated with error ERR_NUM */
INTERN ATTR_SECTION(".text.crt.dos.net.db") ATTR_CONST WUNUSED char const *
NOTHROW_NCX(LIBDCALL libd_hstrerror)(int err_num) {
	return libc_hstrerror(err_num);
}
/* Open host data base files and mark them as staying
 * open even after a later search if STAY_OPEN is non-zero */
INTERN ATTR_SECTION(".text.crt.dos.net.db") void
NOTHROW_RPC(LIBDCALL libd_sethostent)(int stay_open) {
	libc_sethostent(stay_open);
}
/* Return entry from host data base which address match ADDR with length LEN and type TYPE */
INTERN ATTR_SECTION(".text.crt.dos.net.db") struct hostent *
NOTHROW_RPC(LIBDCALL libd_gethostbyaddr)(void const *addr,
                                         socklen_t len,
                                         int type) {
	return libc_gethostbyaddr(addr, len, type);
}
/* Return entry from host data base for host with NAME */
INTERN ATTR_SECTION(".text.crt.dos.net.db") struct hostent *
NOTHROW_RPC(LIBDCALL libd_gethostbyname)(char const *name) {
	return libc_gethostbyname(name);
}
/* Return entry from host data base for host with NAME. AF must be
 * set to the address type which is `AF_INET' for IPv4 or `AF_INET6'
 * for IPv6.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") struct hostent *
NOTHROW_RPC(LIBDCALL libd_gethostbyname2)(char const *name,
                                          int af) {
	return libc_gethostbyname2(name, af);
}
/* Reentrant versions of the functions above. The additional arguments
 * specify a buffer of BUFLEN starting at BUF. The last argument is a
 * pointer to a variable which gets the value which would be stored in
 * the global variable `herrno' by the non-reentrant functions.
 * These functions are not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_gethostent_r)(struct hostent *__restrict result_buf,
                                        char *__restrict buf,
                                        size_t buflen,
                                        struct hostent **__restrict result,
                                        int *__restrict h_errnop) {
	return libc_gethostent_r(result_buf, buf, buflen, result, h_errnop);
}
/* Reentrant versions of the functions above. The additional arguments
 * specify a buffer of BUFLEN starting at BUF. The last argument is a
 * pointer to a variable which gets the value which would be stored in
 * the global variable `herrno' by the non-reentrant functions.
 * These functions are not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_gethostbyaddr_r)(void const *__restrict addr,
                                           socklen_t len,
                                           int type,
                                           struct hostent *__restrict result_buf,
                                           char *__restrict buf,
                                           size_t buflen,
                                           struct hostent **__restrict result,
                                           int *__restrict h_errnop) {
	return libc_gethostbyaddr_r(addr, len, type, result_buf, buf, buflen, result, h_errnop);
}
/* Reentrant versions of the functions above. The additional arguments
 * specify a buffer of BUFLEN starting at BUF. The last argument is a
 * pointer to a variable which gets the value which would be stored in
 * the global variable `herrno' by the non-reentrant functions.
 * These functions are not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_gethostbyname_r)(char const *__restrict name,
                                           struct hostent *__restrict result_buf,
                                           char *__restrict buf,
                                           size_t buflen,
                                           struct hostent **__restrict result,
                                           int *__restrict h_errnop) {
	return libc_gethostbyname_r(name, result_buf, buf, buflen, result, h_errnop);
}
/* Reentrant versions of the functions above. The additional arguments
 * specify a buffer of BUFLEN starting at BUF. The last argument is a
 * pointer to a variable which gets the value which would be stored in
 * the global variable `herrno' by the non-reentrant functions.
 * These functions are not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_gethostbyname2_r)(char const *__restrict name,
                                            int af,
                                            struct hostent *__restrict result_buf,
                                            char *__restrict buf,
                                            size_t buflen,
                                            struct hostent **__restrict result,
                                            int *__restrict h_errnop) {
	return libc_gethostbyname2_r(name, af, result_buf, buf, buflen, result, h_errnop);
}
/* Open network data base files and mark them as staying
 * open even after a later search if STAY_OPEN is non-zero */
INTERN ATTR_SECTION(".text.crt.dos.net.db") void
NOTHROW_RPC(LIBDCALL libd_setnetent)(int stay_open) {
	libc_setnetent(stay_open);
}
/* Return entry from network data base which address match NET and type TYPE */
INTERN ATTR_SECTION(".text.crt.dos.net.db") struct netent *
NOTHROW_RPC(LIBDCALL libd_getnetbyaddr)(uint32_t net,
                                        int type) {
	return libc_getnetbyaddr(net, type);
}
/* Return entry from network data base for network with NAME */
INTERN ATTR_SECTION(".text.crt.dos.net.db") struct netent *
NOTHROW_RPC(LIBDCALL libd_getnetbyname)(char const *name) {
	return libc_getnetbyname(name);
}
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF. The last
 * argument is a pointer to a variable which gets the value which
 * would be stored in the global variable `herrno' by the
 * non-reentrant functions.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_getnetent_r)(struct netent *__restrict result_buf,
                                       char *__restrict buf,
                                       size_t buflen,
                                       struct netent **__restrict result,
                                       int *__restrict h_errnop) {
	return libc_getnetent_r(result_buf, buf, buflen, result, h_errnop);
}
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF. The last
 * argument is a pointer to a variable which gets the value which
 * would be stored in the global variable `herrno' by the
 * non-reentrant functions.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_getnetbyaddr_r)(uint32_t net,
                                          int type,
                                          struct netent *__restrict result_buf,
                                          char *__restrict buf,
                                          size_t buflen,
                                          struct netent **__restrict result,
                                          int *__restrict h_errnop) {
	return libc_getnetbyaddr_r(net, type, result_buf, buf, buflen, result, h_errnop);
}
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF. The last
 * argument is a pointer to a variable which gets the value which
 * would be stored in the global variable `herrno' by the
 * non-reentrant functions.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_getnetbyname_r)(char const *__restrict name,
                                          struct netent *__restrict result_buf,
                                          char *__restrict buf,
                                          size_t buflen,
                                          struct netent **__restrict result,
                                          int *__restrict h_errnop) {
	return libc_getnetbyname_r(name, result_buf, buf, buflen, result, h_errnop);
}
/* Open service data base files and mark them as staying open even
 * after a later search if STAY_OPEN is non-zero */
INTERN ATTR_SECTION(".text.crt.dos.net.db") void
NOTHROW_RPC(LIBDCALL libd_setservent)(int stay_open) {
	libc_setservent(stay_open);
}
/* Return entry from network data base for network with NAME and protocol PROTO */
INTERN ATTR_SECTION(".text.crt.dos.net.db") struct servent *
NOTHROW_RPC(LIBDCALL libd_getservbyname)(char const *name,
                                         char const *proto) {
	return libc_getservbyname(name, proto);
}
/* Return entry from service data base which matches port PORT and protocol PROTO */
INTERN ATTR_SECTION(".text.crt.dos.net.db") struct servent *
NOTHROW_RPC(LIBDCALL libd_getservbyport)(int port,
                                         char const *proto) {
	return libc_getservbyport(port, proto);
}
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_getservent_r)(struct servent *__restrict result_buf,
                                        char *__restrict buf,
                                        size_t buflen,
                                        struct servent **__restrict result) {
	return libc_getservent_r(result_buf, buf, buflen, result);
}
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_getservbyname_r)(char const *__restrict name,
                                           char const *__restrict proto,
                                           struct servent *__restrict result_buf,
                                           char *__restrict buf,
                                           size_t buflen,
                                           struct servent **__restrict result) {
	return libc_getservbyname_r(name, proto, result_buf, buf, buflen, result);
}
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_getservbyport_r)(int port,
                                           char const *__restrict proto,
                                           struct servent *__restrict result_buf,
                                           char *__restrict buf,
                                           size_t buflen,
                                           struct servent **__restrict result) {
	return libc_getservbyport_r(port, proto, result_buf, buf, buflen, result);
}
/* Open protocol data base files and mark them as staying open even
 * after a later search if STAY_OPEN is non-zero */
INTERN ATTR_SECTION(".text.crt.dos.net.db") void
NOTHROW_RPC(LIBDCALL libd_setprotoent)(int stay_open) {
	libc_setprotoent(stay_open);
}
/* Return entry from protocol data base for network with NAME */
INTERN ATTR_SECTION(".text.crt.dos.net.db") struct protoent *
NOTHROW_RPC(LIBDCALL libd_getprotobyname)(char const *name) {
	return libc_getprotobyname(name);
}
/* Return entry from protocol data base which number is PROTO */
INTERN ATTR_SECTION(".text.crt.dos.net.db") struct protoent *
NOTHROW_RPC(LIBDCALL libd_getprotobynumber)(int proto) {
	return libc_getprotobynumber(proto);
}
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_getprotoent_r)(struct protoent *__restrict result_buf,
                                         char *__restrict buf,
                                         size_t buflen,
                                         struct protoent **__restrict result) {
	return libc_getprotoent_r(result_buf, buf, buflen, result);
}
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_getprotobyname_r)(char const *__restrict name,
                                            struct protoent *__restrict result_buf,
                                            char *__restrict buf,
                                            size_t buflen,
                                            struct protoent **__restrict result) {
	return libc_getprotobyname_r(name, result_buf, buf, buflen, result);
}
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_getprotobynumber_r)(int proto,
                                              struct protoent *__restrict result_buf,
                                              char *__restrict buf,
                                              size_t buflen,
                                              struct protoent **__restrict result) {
	return libc_getprotobynumber_r(proto, result_buf, buf, buflen, result);
}
/* Establish network group NETGROUP for enumeration.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_setnetgrent)(char const *netgroup) {
	return libc_setnetgrent(netgroup);
}
/* Get next member of netgroup established by last `setnetgrent' call
 * and return pointers to elements in HOSTP, USERP, and DOMAINP.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_getnetgrent)(char **__restrict hostp,
                                       char **__restrict userp,
                                       char **__restrict domainp) {
	return libc_getnetgrent(hostp, userp, domainp);
}
/* Test whether NETGROUP contains the triple (HOST, USER, DOMAIN).
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_innetgr)(char const *netgroup,
                                   char const *host,
                                   char const *user,
                                   char const *domain) {
	return libc_innetgr(netgroup, host, user, domain);
}
/* Reentrant version of `getnetgrent' where result is placed in BUFFER.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_getnetgrent_r)(char **__restrict hostp,
                                         char **__restrict userp,
                                         char **__restrict domainp,
                                         char *__restrict buf,
                                         size_t buflen) {
	return libc_getnetgrent_r(hostp, userp, domainp, buf, buflen);
}
/* Call `rshd' at port RPORT on remote machine *AHOST to execute CMD.
 * The local user is LOCUSER, on the remote machine the command is
 * executed as REMUSER. In *FD2P the descriptor to the socket for the
 * connection is returned. The caller must have the right to use a
 * reserved port. When the function returns *AHOST contains the
 * official host name.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_rcmd)(char **__restrict ahost,
                                uint16_t rport,
                                char const *__restrict locuser,
                                char const *__restrict remuser,
                                char const *__restrict cmd,
                                int *__restrict fd2p) {
	return libc_rcmd(ahost, rport, locuser, remuser, cmd, fd2p);
}
/* This is the equivalent function where the protocol can be selected
 * and which therefore can be used for IPv6.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_rcmd_af)(char **__restrict ahost,
                                   uint16_t rport,
                                   char const *__restrict locuser,
                                   char const *__restrict remuser,
                                   char const *__restrict cmd,
                                   int *__restrict fd2p,
                                   sa_family_t af) {
	return libc_rcmd_af(ahost, rport, locuser, remuser, cmd, fd2p, af);
}
/* Call `rexecd' at port RPORT on remote machine *AHOST to execute
 * CMD. The process runs at the remote machine using the ID of user
 * NAME whose cleartext password is PASSWD. In *FD2P the descriptor
 * to the socket for the connection is returned. When the function
 * returns *AHOST contains the official host name.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_rexec)(char **__restrict ahost,
                                 int rport,
                                 char const *__restrict name,
                                 char const *__restrict pass,
                                 char const *__restrict cmd,
                                 int *__restrict fd2p) {
	return libc_rexec(ahost, rport, name, pass, cmd, fd2p);
}
/* This is the equivalent function where the protocol can be selected
 * and which therefore can be used for IPv6.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_rexec_af)(char **__restrict ahost,
                                    int rport,
                                    char const *__restrict name,
                                    char const *__restrict pass,
                                    char const *__restrict cmd,
                                    int *__restrict fd2p,
                                    sa_family_t af) {
	return libc_rexec_af(ahost, rport, name, pass, cmd, fd2p, af);
}
/* Check whether user REMUSER on system RHOST is allowed to login as LOCUSER.
 * If SUSER is not zero the user tries to become superuser. Return 0 if
 * it is possible.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_ruserok)(char const *rhost,
                                   int suser,
                                   char const *remuser,
                                   char const *locuser) {
	return libc_ruserok(rhost, suser, remuser, locuser);
}
/* This is the equivalent function where the protocol can be selected
 * and which therefore can be used for IPv6.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_ruserok_af)(char const *rhost,
                                      int suser,
                                      char const *remuser,
                                      char const *locuser,
                                      sa_family_t af) {
	return libc_ruserok_af(rhost, suser, remuser, locuser, af);
}
/* Check whether user REMUSER on system indicated by IPv4 address
 * RADDR is allowed to login as LOCUSER. Non-IPv4 (e.g., IPv6) are
 * not supported. If SUSER is not zero the user tries to become
 * superuser. Return 0 if it is possible.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_iruserok)(uint32_t raddr,
                                    int suser,
                                    char const *remuser,
                                    char const *locuser) {
	return libc_iruserok(raddr, suser, remuser, locuser);
}
/* This is the equivalent function where the pfamiliy if the address
 * pointed to by RADDR is determined by the value of AF. It therefore
 * can be used for IPv6
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_iruserok_af)(void const *raddr,
                                       int suser,
                                       char const *remuser,
                                       char const *locuser,
                                       sa_family_t af) {
	return libc_iruserok_af(raddr, suser, remuser, locuser, af);
}
/* Try to allocate reserved port, returning a descriptor for a socket opened
 * at this port or -1 if unsuccessful. The search for an available port
 * will start at ALPORT and continues with lower numbers.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_rresvport)(int *alport) {
	return libc_rresvport(alport);
}
/* This is the equivalent function where the protocol can be selected
 * and which therefore can be used for IPv6.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_rresvport_af)(int *alport,
                                        sa_family_t af) {
	return libc_rresvport_af(alport, af);
}
/* Translate name of a service location and/or a service name to set of socket addresses */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_getaddrinfo)(char const *__restrict name,
                                       char const *__restrict service,
                                       struct addrinfo const *__restrict req,
                                       struct addrinfo **__restrict pai) {
	return libc_getaddrinfo(name, service, req, pai);
}
/* Free `addrinfo' structure AI including associated storage */
INTERN ATTR_SECTION(".text.crt.dos.net.db") void
NOTHROW_NCX(LIBDCALL libd_freeaddrinfo)(struct addrinfo *ai) {
	libc_freeaddrinfo(ai);
}
/* Convert error return from getaddrinfo() to a string */
INTERN ATTR_SECTION(".text.crt.dos.net.db") ATTR_CONST WUNUSED char const *
NOTHROW_NCX(LIBDCALL libd_gai_strerror)(int ecode) {
	return libc_gai_strerror(ecode);
}
/* Translate a socket address to a location and service name */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_getnameinfo)(struct sockaddr const *__restrict sa,
                                       socklen_t salen,
                                       char *__restrict host,
                                       socklen_t hostlen,
                                       char *__restrict serv,
                                       socklen_t servlen,
                                       int flags) {
	return libc_getnameinfo(sa, salen, host, hostlen, serv, servlen, flags);
}
/* Enqueue ENT requests from the LIST. If MODE is GAI_WAIT wait until all
 * requests are handled. If WAIT is GAI_NOWAIT return immediately after
 * queueing the requests and signal completion according to SIG.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_getaddrinfo_a)(int mode,
                                         struct gaicb *list[__restrict_arr],
                                         int ent,
                                         struct sigevent *__restrict sig) {
	return libc_getaddrinfo_a(mode, list, ent, sig);
}
/* Suspend execution of the thread until at least one of the ENT requests
 * in LIST is handled. If TIMEOUT is not a null pointer it specifies the
 * longest time the function keeps waiting before returning with an error.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_gai_suspend)(struct gaicb const *const list[],
                                       int ent,
                                       struct timespec const *timeout) {
	return libc_gai_suspend(list, ent, timeout);
}
/* Suspend execution of the thread until at least one of the ENT requests
 * in LIST is handled. If TIMEOUT is not a null pointer it specifies the
 * longest time the function keeps waiting before returning with an error.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_RPC(LIBDCALL libd_gai_suspend64)(struct gaicb const *const list[],
                                         int ent,
                                         struct timespec64 const *timeout) {
	return libc_gai_suspend64(list, ent, timeout);
}
/* Get the error status of the request REQ */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_NCX(LIBDCALL libd_gai_error)(struct gaicb *req) {
	return libc_gai_error(req);
}
/* Cancel the requests associated with GAICBP */
INTERN ATTR_SECTION(".text.crt.dos.net.db") int
NOTHROW_NCX(LIBDCALL libd_gai_cancel)(struct gaicb *gaicbp) {
	return libc_gai_cancel(gaicbp);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$herror, libd_herror);
DEFINE_PUBLIC_ALIAS(DOS$hstrerror, libd_hstrerror);
DEFINE_PUBLIC_ALIAS(DOS$sethostent, libd_sethostent);
DEFINE_PUBLIC_ALIAS(DOS$gethostbyaddr, libd_gethostbyaddr);
DEFINE_PUBLIC_ALIAS(DOS$gethostbyname, libd_gethostbyname);
DEFINE_PUBLIC_ALIAS(DOS$gethostbyname2, libd_gethostbyname2);
DEFINE_PUBLIC_ALIAS(DOS$gethostent_r, libd_gethostent_r);
DEFINE_PUBLIC_ALIAS(DOS$gethostbyaddr_r, libd_gethostbyaddr_r);
DEFINE_PUBLIC_ALIAS(DOS$gethostbyname_r, libd_gethostbyname_r);
DEFINE_PUBLIC_ALIAS(DOS$gethostbyname2_r, libd_gethostbyname2_r);
DEFINE_PUBLIC_ALIAS(DOS$setnetent, libd_setnetent);
DEFINE_PUBLIC_ALIAS(DOS$getnetbyaddr, libd_getnetbyaddr);
DEFINE_PUBLIC_ALIAS(DOS$getnetbyname, libd_getnetbyname);
DEFINE_PUBLIC_ALIAS(DOS$getnetent_r, libd_getnetent_r);
DEFINE_PUBLIC_ALIAS(DOS$getnetbyaddr_r, libd_getnetbyaddr_r);
DEFINE_PUBLIC_ALIAS(DOS$getnetbyname_r, libd_getnetbyname_r);
DEFINE_PUBLIC_ALIAS(DOS$setservent, libd_setservent);
DEFINE_PUBLIC_ALIAS(DOS$getservbyname, libd_getservbyname);
DEFINE_PUBLIC_ALIAS(DOS$getservbyport, libd_getservbyport);
DEFINE_PUBLIC_ALIAS(DOS$getservent_r, libd_getservent_r);
DEFINE_PUBLIC_ALIAS(DOS$getservbyname_r, libd_getservbyname_r);
DEFINE_PUBLIC_ALIAS(DOS$getservbyport_r, libd_getservbyport_r);
DEFINE_PUBLIC_ALIAS(DOS$setprotoent, libd_setprotoent);
DEFINE_PUBLIC_ALIAS(DOS$getprotobyname, libd_getprotobyname);
DEFINE_PUBLIC_ALIAS(DOS$getprotobynumber, libd_getprotobynumber);
DEFINE_PUBLIC_ALIAS(DOS$getprotoent_r, libd_getprotoent_r);
DEFINE_PUBLIC_ALIAS(DOS$getprotobyname_r, libd_getprotobyname_r);
DEFINE_PUBLIC_ALIAS(DOS$getprotobynumber_r, libd_getprotobynumber_r);
DEFINE_PUBLIC_ALIAS(DOS$setnetgrent, libd_setnetgrent);
DEFINE_PUBLIC_ALIAS(DOS$getnetgrent, libd_getnetgrent);
DEFINE_PUBLIC_ALIAS(DOS$innetgr, libd_innetgr);
DEFINE_PUBLIC_ALIAS(DOS$getnetgrent_r, libd_getnetgrent_r);
DEFINE_PUBLIC_ALIAS(DOS$rcmd, libd_rcmd);
DEFINE_PUBLIC_ALIAS(DOS$rcmd_af, libd_rcmd_af);
DEFINE_PUBLIC_ALIAS(DOS$rexec, libd_rexec);
DEFINE_PUBLIC_ALIAS(DOS$rexec_af, libd_rexec_af);
DEFINE_PUBLIC_ALIAS(DOS$ruserok, libd_ruserok);
DEFINE_PUBLIC_ALIAS(DOS$ruserok_af, libd_ruserok_af);
DEFINE_PUBLIC_ALIAS(DOS$iruserok, libd_iruserok);
DEFINE_PUBLIC_ALIAS(DOS$iruserok_af, libd_iruserok_af);
DEFINE_PUBLIC_ALIAS(DOS$rresvport, libd_rresvport);
DEFINE_PUBLIC_ALIAS(DOS$rresvport_af, libd_rresvport_af);
DEFINE_PUBLIC_ALIAS(DOS$getaddrinfo, libd_getaddrinfo);
DEFINE_PUBLIC_ALIAS(DOS$freeaddrinfo, libd_freeaddrinfo);
DEFINE_PUBLIC_ALIAS(DOS$gai_strerror, libd_gai_strerror);
DEFINE_PUBLIC_ALIAS(DOS$getnameinfo, libd_getnameinfo);
DEFINE_PUBLIC_ALIAS(DOS$getaddrinfo_a, libd_getaddrinfo_a);
DEFINE_PUBLIC_ALIAS(DOS$gai_suspend, libd_gai_suspend);
DEFINE_PUBLIC_ALIAS(DOS$gai_suspend64, libd_gai_suspend64);
DEFINE_PUBLIC_ALIAS(DOS$gai_error, libd_gai_error);
DEFINE_PUBLIC_ALIAS(DOS$gai_cancel, libd_gai_cancel);

#endif /* !GUARD_LIBC_AUTO_DOSABI_NETDB_C */
