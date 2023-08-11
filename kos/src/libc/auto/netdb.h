/* HASH CRC-32:0xee611af1 */
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
#ifndef GUARD_LIBC_AUTO_NETDB_H
#define GUARD_LIBC_AUTO_NETDB_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <netdb.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF void NOTHROW_RPC(LIBDCALL libd_sethostent)(int stay_open);
INTDEF struct hostent *NOTHROW_RPC(LIBDCALL libd_gethostbyaddr)(void const *addr, socklen_t len, int type);
INTDEF struct hostent *NOTHROW_RPC(LIBDCALL libd_gethostbyname)(char const *name);
INTDEF void NOTHROW_RPC(LIBDCALL libd_setnetent)(int stay_open);
INTDEF struct netent *NOTHROW_RPC(LIBDCALL libd_getnetbyaddr)(uint32_t net, int type);
INTDEF struct netent *NOTHROW_RPC(LIBDCALL libd_getnetbyname)(char const *name);
INTDEF void NOTHROW_RPC(LIBDCALL libd_setservent)(int stay_open);
INTDEF struct servent *NOTHROW_RPC(LIBDCALL libd_getservbyname)(char const *name, char const *proto);
INTDEF struct servent *NOTHROW_RPC(LIBDCALL libd_getservbyport)(int port, char const *proto);
INTDEF void NOTHROW_RPC(LIBDCALL libd_setprotoent)(int stay_open);
INTDEF struct protoent *NOTHROW_RPC(LIBDCALL libd_getprotobyname)(char const *name);
INTDEF struct protoent *NOTHROW_RPC(LIBDCALL libd_getprotobynumber)(int proto);
/* >> herror(3)
 * Same as `perror(3)' for `errno(3)', print `message' (if non-null),
 * alongside   the  value  of  `hstrerror(h_errno)'  to  `stderr(3)'. */
INTDEF void NOTHROW_CB_NCX(LIBDCALL libd_herror)(char const *message);
/* >> hstrerror(3)
 * Return error message for `h_error' */
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(LIBDCALL libd_hstrerror)(int h_error);
INTDEF struct hostent *NOTHROW_RPC(LIBDCALL libd_gethostbyname2)(char const *name, int af);
INTDEF int NOTHROW_RPC(LIBDCALL libd_gethostent_r)(struct hostent *__restrict result_buf, char *__restrict buf, size_t buflen, struct hostent **__restrict result, int *__restrict h_errnop);
INTDEF int NOTHROW_RPC(LIBDCALL libd_gethostbyaddr_r)(void const *__restrict addr, socklen_t len, int type, struct hostent *__restrict result_buf, char *__restrict buf, size_t buflen, struct hostent **__restrict result, int *__restrict h_errnop);
INTDEF int NOTHROW_RPC(LIBDCALL libd_gethostbyname_r)(char const *__restrict name, struct hostent *__restrict result_buf, char *__restrict buf, size_t buflen, struct hostent **__restrict result, int *__restrict h_errnop);
INTDEF int NOTHROW_RPC(LIBDCALL libd_gethostbyname2_r)(char const *__restrict name, int af, struct hostent *__restrict result_buf, char *__restrict buf, size_t buflen, struct hostent **__restrict result, int *__restrict h_errnop);
INTDEF int NOTHROW_RPC(LIBDCALL libd_getnetent_r)(struct netent *__restrict result_buf, char *__restrict buf, size_t buflen, struct netent **__restrict result, int *__restrict h_errnop);
INTDEF int NOTHROW_RPC(LIBDCALL libd_getnetbyaddr_r)(uint32_t net, int type, struct netent *__restrict result_buf, char *__restrict buf, size_t buflen, struct netent **__restrict result, int *__restrict h_errnop);
INTDEF int NOTHROW_RPC(LIBDCALL libd_getnetbyname_r)(char const *__restrict name, struct netent *__restrict result_buf, char *__restrict buf, size_t buflen, struct netent **__restrict result, int *__restrict h_errnop);
INTDEF int NOTHROW_RPC(LIBDCALL libd_getservent_r)(struct servent *__restrict result_buf, char *__restrict buf, size_t buflen, struct servent **__restrict result);
INTDEF int NOTHROW_RPC(LIBDCALL libd_getservbyname_r)(char const *__restrict name, char const *__restrict proto, struct servent *__restrict result_buf, char *__restrict buf, size_t buflen, struct servent **__restrict result);
INTDEF int NOTHROW_RPC(LIBDCALL libd_getservbyport_r)(int port, char const *__restrict proto, struct servent *__restrict result_buf, char *__restrict buf, size_t buflen, struct servent **__restrict result);
INTDEF int NOTHROW_RPC(LIBDCALL libd_getprotoent_r)(struct protoent *__restrict result_buf, char *__restrict buf, size_t buflen, struct protoent **__restrict result);
INTDEF int NOTHROW_RPC(LIBDCALL libd_getprotobyname_r)(char const *__restrict name, struct protoent *__restrict result_buf, char *__restrict buf, size_t buflen, struct protoent **__restrict result);
INTDEF int NOTHROW_RPC(LIBDCALL libd_getprotobynumber_r)(int proto, struct protoent *__restrict result_buf, char *__restrict buf, size_t buflen, struct protoent **__restrict result);
INTDEF int NOTHROW_RPC(LIBDCALL libd_setnetgrent)(char const *netgroup);
INTDEF int NOTHROW_RPC(LIBDCALL libd_getnetgrent)(char **__restrict hostp, char **__restrict userp, char **__restrict domainp);
INTDEF int NOTHROW_RPC(LIBDCALL libd_innetgr)(char const *netgroup, char const *host, char const *user, char const *domain);
INTDEF int NOTHROW_RPC(LIBDCALL libd_getnetgrent_r)(char **__restrict hostp, char **__restrict userp, char **__restrict domainp, char *__restrict buf, size_t buflen);
INTDEF int NOTHROW_RPC(LIBDCALL libd_rcmd)(char **__restrict ahost, uint16_t rport, char const *__restrict locuser, char const *__restrict remuser, char const *__restrict cmd, int *__restrict fd2p);
INTDEF int NOTHROW_RPC(LIBDCALL libd_rcmd_af)(char **__restrict ahost, uint16_t rport, char const *__restrict locuser, char const *__restrict remuser, char const *__restrict cmd, int *__restrict fd2p, sa_family_t af);
INTDEF int NOTHROW_RPC(LIBDCALL libd_rexec)(char **__restrict ahost, int rport, char const *__restrict name, char const *__restrict pass, char const *__restrict cmd, int *__restrict fd2p);
INTDEF int NOTHROW_RPC(LIBDCALL libd_rexec_af)(char **__restrict ahost, int rport, char const *__restrict name, char const *__restrict pass, char const *__restrict cmd, int *__restrict fd2p, sa_family_t af);
INTDEF int NOTHROW_RPC(LIBDCALL libd_ruserok)(char const *rhost, int suser, char const *remuser, char const *locuser);
INTDEF int NOTHROW_RPC(LIBDCALL libd_ruserok_af)(char const *rhost, int suser, char const *remuser, char const *locuser, sa_family_t af);
INTDEF int NOTHROW_RPC(LIBDCALL libd_iruserok)(uint32_t raddr, int suser, char const *remuser, char const *locuser);
INTDEF int NOTHROW_RPC(LIBDCALL libd_iruserok_af)(void const *raddr, int suser, char const *remuser, char const *locuser, sa_family_t af);
INTDEF int NOTHROW_RPC(LIBDCALL libd_rresvport)(int *alport);
INTDEF int NOTHROW_RPC(LIBDCALL libd_rresvport_af)(int *alport, sa_family_t af);
INTDEF int NOTHROW_RPC(LIBDCALL libd_getaddrinfo)(char const *__restrict name, char const *__restrict service, struct addrinfo const *__restrict req, struct addrinfo **__restrict pai);
INTDEF void NOTHROW_NCX(LIBDCALL libd_freeaddrinfo)(struct addrinfo *ai);
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(LIBDCALL libd_gai_strerror)(int ecode);
INTDEF int NOTHROW_RPC(LIBDCALL libd_getnameinfo)(struct sockaddr const *__restrict sa, socklen_t salen, char *__restrict host, socklen_t hostlen, char *__restrict serv, socklen_t servlen, int flags);
INTDEF int NOTHROW_RPC(LIBDCALL libd_getaddrinfo_a)(int mode, struct gaicb *list[__restrict_arr], int ent, struct sigevent *__restrict sig);
INTDEF int NOTHROW_NCX(LIBDCALL libd_gai_error)(struct gaicb *req);
INTDEF int NOTHROW_NCX(LIBDCALL libd_gai_cancel)(struct gaicb *gaicbp);
INTDEF int NOTHROW_RPC(LIBDCALL libd_gai_suspend)(struct gaicb const *const list[], int ent, struct timespec const *timeout);
INTDEF int NOTHROW_RPC(LIBDCALL libd_gai_suspend64)(struct gaicb const *const list[], int ent, struct timespec64 const *timeout);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_NETDB_H */
