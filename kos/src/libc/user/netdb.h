/* HASH CRC-32:0xc749675d */
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
#ifndef GUARD_LIBC_USER_NETDB_H
#define GUARD_LIBC_USER_NETDB_H 1

#include "../api.h"
#include "../auto/netdb.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <netdb.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF void NOTHROW_RPC(LIBCCALL libc_sethostent)(int stay_open);
INTDEF void NOTHROW_RPC_NOKOS(LIBCCALL libc_endhostent)(void);
INTDEF struct hostent *NOTHROW_RPC(LIBCCALL libc_gethostent)(void);
INTDEF struct hostent *NOTHROW_RPC(LIBCCALL libc_gethostbyaddr)(void const *addr, socklen_t len, int type);
INTDEF struct hostent *NOTHROW_RPC(LIBCCALL libc_gethostbyname)(char const *name);
INTDEF void NOTHROW_RPC(LIBCCALL libc_setnetent)(int stay_open);
INTDEF void NOTHROW_RPC_NOKOS(LIBCCALL libc_endnetent)(void);
INTDEF struct netent *NOTHROW_RPC(LIBCCALL libc_getnetent)(void);
INTDEF struct netent *NOTHROW_RPC(LIBCCALL libc_getnetbyaddr)(uint32_t net, int type);
INTDEF struct netent *NOTHROW_RPC(LIBCCALL libc_getnetbyname)(char const *name);
INTDEF void NOTHROW_RPC(LIBCCALL libc_setservent)(int stay_open);
INTDEF void NOTHROW_RPC_NOKOS(LIBCCALL libc_endservent)(void);
INTDEF struct servent *NOTHROW_RPC(LIBCCALL libc_getservent)(void);
INTDEF struct servent *NOTHROW_RPC(LIBCCALL libc_getservbyname)(char const *name, char const *proto);
INTDEF struct servent *NOTHROW_RPC(LIBCCALL libc_getservbyport)(int port, char const *proto);
INTDEF void NOTHROW_RPC(LIBCCALL libc_setprotoent)(int stay_open);
INTDEF void NOTHROW_RPC_NOKOS(LIBCCALL libc_endprotoent)(void);
INTDEF struct protoent *NOTHROW_RPC(LIBCCALL libc_getprotoent)(void);
INTDEF struct protoent *NOTHROW_RPC(LIBCCALL libc_getprotobyname)(char const *name);
INTDEF struct protoent *NOTHROW_RPC(LIBCCALL libc_getprotobynumber)(int proto);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED int *NOTHROW(LIBCCALL libc___h_errno_location)(void);
/* >> herror(3)
 * Same as `perror(3)' for `errno(3)', print `message' (if non-null),
 * alongside   the  value  of  `hstrerror(h_errno)'  to  `stderr(3)'. */
INTDEF void NOTHROW_CB_NCX(LIBCCALL libc_herror)(char const *message);
/* >> hstrerror(3)
 * Return error message for `h_error' */
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(LIBCCALL libc_hstrerror)(int h_error);
INTDEF struct hostent *NOTHROW_RPC(LIBCCALL libc_gethostbyname2)(char const *name, int af);
INTDEF int NOTHROW_RPC(LIBCCALL libc_gethostent_r)(struct hostent *__restrict result_buf, char *__restrict buf, size_t buflen, struct hostent **__restrict result, int *__restrict h_errnop);
INTDEF int NOTHROW_RPC(LIBCCALL libc_gethostbyaddr_r)(void const *__restrict addr, socklen_t len, int type, struct hostent *__restrict result_buf, char *__restrict buf, size_t buflen, struct hostent **__restrict result, int *__restrict h_errnop);
INTDEF int NOTHROW_RPC(LIBCCALL libc_gethostbyname_r)(char const *__restrict name, struct hostent *__restrict result_buf, char *__restrict buf, size_t buflen, struct hostent **__restrict result, int *__restrict h_errnop);
INTDEF int NOTHROW_RPC(LIBCCALL libc_gethostbyname2_r)(char const *__restrict name, int af, struct hostent *__restrict result_buf, char *__restrict buf, size_t buflen, struct hostent **__restrict result, int *__restrict h_errnop);
INTDEF int NOTHROW_RPC(LIBCCALL libc_getnetent_r)(struct netent *__restrict result_buf, char *__restrict buf, size_t buflen, struct netent **__restrict result, int *__restrict h_errnop);
INTDEF int NOTHROW_RPC(LIBCCALL libc_getnetbyaddr_r)(uint32_t net, int type, struct netent *__restrict result_buf, char *__restrict buf, size_t buflen, struct netent **__restrict result, int *__restrict h_errnop);
INTDEF int NOTHROW_RPC(LIBCCALL libc_getnetbyname_r)(char const *__restrict name, struct netent *__restrict result_buf, char *__restrict buf, size_t buflen, struct netent **__restrict result, int *__restrict h_errnop);
INTDEF int NOTHROW_RPC(LIBCCALL libc_getservent_r)(struct servent *__restrict result_buf, char *__restrict buf, size_t buflen, struct servent **__restrict result);
INTDEF int NOTHROW_RPC(LIBCCALL libc_getservbyname_r)(char const *__restrict name, char const *__restrict proto, struct servent *__restrict result_buf, char *__restrict buf, size_t buflen, struct servent **__restrict result);
INTDEF int NOTHROW_RPC(LIBCCALL libc_getservbyport_r)(int port, char const *__restrict proto, struct servent *__restrict result_buf, char *__restrict buf, size_t buflen, struct servent **__restrict result);
INTDEF int NOTHROW_RPC(LIBCCALL libc_getprotoent_r)(struct protoent *__restrict result_buf, char *__restrict buf, size_t buflen, struct protoent **__restrict result);
INTDEF int NOTHROW_RPC(LIBCCALL libc_getprotobyname_r)(char const *__restrict name, struct protoent *__restrict result_buf, char *__restrict buf, size_t buflen, struct protoent **__restrict result);
INTDEF int NOTHROW_RPC(LIBCCALL libc_getprotobynumber_r)(int proto, struct protoent *__restrict result_buf, char *__restrict buf, size_t buflen, struct protoent **__restrict result);
INTDEF int NOTHROW_RPC(LIBCCALL libc_setnetgrent)(char const *netgroup);
INTDEF void NOTHROW_RPC_NOKOS(LIBCCALL libc_endnetgrent)(void);
INTDEF int NOTHROW_RPC(LIBCCALL libc_getnetgrent)(char **__restrict hostp, char **__restrict userp, char **__restrict domainp);
INTDEF int NOTHROW_RPC(LIBCCALL libc_innetgr)(char const *netgroup, char const *host, char const *user, char const *domain);
INTDEF int NOTHROW_RPC(LIBCCALL libc_getnetgrent_r)(char **__restrict hostp, char **__restrict userp, char **__restrict domainp, char *__restrict buf, size_t buflen);
INTDEF int NOTHROW_RPC(LIBCCALL libc_rcmd)(char **__restrict ahost, uint16_t rport, char const *__restrict locuser, char const *__restrict remuser, char const *__restrict cmd, int *__restrict fd2p);
INTDEF int NOTHROW_RPC(LIBCCALL libc_rcmd_af)(char **__restrict ahost, uint16_t rport, char const *__restrict locuser, char const *__restrict remuser, char const *__restrict cmd, int *__restrict fd2p, sa_family_t af);
INTDEF int NOTHROW_RPC(LIBCCALL libc_rexec)(char **__restrict ahost, int rport, char const *__restrict name, char const *__restrict pass, char const *__restrict cmd, int *__restrict fd2p);
INTDEF int NOTHROW_RPC(LIBCCALL libc_rexec_af)(char **__restrict ahost, int rport, char const *__restrict name, char const *__restrict pass, char const *__restrict cmd, int *__restrict fd2p, sa_family_t af);
INTDEF int NOTHROW_RPC(LIBCCALL libc_ruserok)(char const *rhost, int suser, char const *remuser, char const *locuser);
INTDEF int NOTHROW_RPC(LIBCCALL libc_ruserok_af)(char const *rhost, int suser, char const *remuser, char const *locuser, sa_family_t af);
INTDEF int NOTHROW_RPC(LIBCCALL libc_iruserok)(uint32_t raddr, int suser, char const *remuser, char const *locuser);
INTDEF int NOTHROW_RPC(LIBCCALL libc_iruserok_af)(void const *raddr, int suser, char const *remuser, char const *locuser, sa_family_t af);
INTDEF int NOTHROW_RPC(LIBCCALL libc_rresvport)(int *alport);
INTDEF int NOTHROW_RPC(LIBCCALL libc_rresvport_af)(int *alport, sa_family_t af);
INTDEF int NOTHROW_RPC(LIBCCALL libc_getaddrinfo)(char const *__restrict name, char const *__restrict service, struct addrinfo const *__restrict req, struct addrinfo **__restrict pai);
INTDEF void NOTHROW_NCX(LIBCCALL libc_freeaddrinfo)(struct addrinfo *ai);
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(LIBCCALL libc_gai_strerror)(int ecode);
INTDEF int NOTHROW_RPC(LIBCCALL libc_getnameinfo)(struct sockaddr const *__restrict sa, socklen_t salen, char *__restrict host, socklen_t hostlen, char *__restrict serv, socklen_t servlen, int flags);
INTDEF int NOTHROW_RPC(LIBCCALL libc_getaddrinfo_a)(int mode, struct gaicb *list[__restrict_arr], int ent, struct sigevent *__restrict sig);
INTDEF int NOTHROW_NCX(LIBCCALL libc_gai_error)(struct gaicb *req);
INTDEF int NOTHROW_NCX(LIBCCALL libc_gai_cancel)(struct gaicb *gaicbp);
INTDEF int NOTHROW_RPC(LIBCCALL libc_gai_suspend)(struct gaicb const *const list[], int ent, struct timespec const *timeout);
INTDEF int NOTHROW_RPC(LIBCCALL libc_gai_suspend64)(struct gaicb const *const list[], int ent, struct timespec64 const *timeout);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_NETDB_H */
