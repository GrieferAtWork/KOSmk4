/* HASH CRC-32:0xf9eb4127 */
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
/* Function to get address of global `h_errno' variable */
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED int *NOTHROW(LIBCCALL libc___h_errno_location)(void);
/* Print error indicated by `h_errno' variable on standard error.
 * if non-`NULL',  `str'  is  printed before  the  error  string. */
INTDEF void NOTHROW_RPC(LIBCCALL libc_herror)(char const *str);
/* Return string associated with error `err_num' */
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(LIBCCALL libc_hstrerror)(int err_num);
/* Open host  data  base  files and  mark  them  as  staying
 * open even after a later search if `stay_open' is non-zero */
INTDEF void NOTHROW_RPC(LIBCCALL libc_sethostent)(int stay_open);
/* Close host data base files and clear `stay open' flag */
INTDEF void NOTHROW_RPC_NOKOS(LIBCCALL libc_endhostent)(void);
/* Get next entry from host data base file. Open data base if necessary */
INTDEF struct hostent *NOTHROW_RPC(LIBCCALL libc_gethostent)(void);
/* Return entry from host data base which address match `addr' with length `len' and type `type' */
INTDEF struct hostent *NOTHROW_RPC(LIBCCALL libc_gethostbyaddr)(void const *addr, socklen_t len, int type);
/* Return entry from host data base for host with `name' */
INTDEF struct hostent *NOTHROW_RPC(LIBCCALL libc_gethostbyname)(char const *name);
/* Return entry from host data base for host with `name'. `af' must be
 * set to the address type which  is `AF_INET' for IPv4 or  `AF_INET6'
 * for IPv6.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTDEF struct hostent *NOTHROW_RPC(LIBCCALL libc_gethostbyname2)(char const *name, int af);
/* Reentrant versions of  the functions above.  The additional  arguments
 * specify a buffer of `buflen' starting at `buf'. The last argument is a
 * pointer to a variable  which gets the value  which would be stored  in
 * the global variable `herrno' by the non-reentrant functions.
 * These functions are not part of POSIX and therefore no official cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_gethostent_r)(struct hostent *__restrict result_buf, char *__restrict buf, size_t buflen, struct hostent **__restrict result, int *__restrict h_errnop);
/* Reentrant versions of  the functions above.  The additional  arguments
 * specify a buffer of `buflen' starting at `buf'. The last argument is a
 * pointer to a variable  which gets the value  which would be stored  in
 * the global variable `herrno' by the non-reentrant functions.
 * These functions are not part of POSIX and therefore no official cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_gethostbyaddr_r)(void const *__restrict addr, socklen_t len, int type, struct hostent *__restrict result_buf, char *__restrict buf, size_t buflen, struct hostent **__restrict result, int *__restrict h_errnop);
/* Reentrant versions of  the functions above.  The additional  arguments
 * specify a buffer of `buflen' starting at `buf'. The last argument is a
 * pointer to a variable  which gets the value  which would be stored  in
 * the global variable `herrno' by the non-reentrant functions.
 * These functions are not part of POSIX and therefore no official cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_gethostbyname_r)(char const *__restrict name, struct hostent *__restrict result_buf, char *__restrict buf, size_t buflen, struct hostent **__restrict result, int *__restrict h_errnop);
/* Reentrant versions of  the functions above.  The additional  arguments
 * specify a buffer of `buflen' starting at `buf'. The last argument is a
 * pointer to a variable  which gets the value  which would be stored  in
 * the global variable `herrno' by the non-reentrant functions.
 * These functions are not part of POSIX and therefore no official cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_gethostbyname2_r)(char const *__restrict name, int af, struct hostent *__restrict result_buf, char *__restrict buf, size_t buflen, struct hostent **__restrict result, int *__restrict h_errnop);
/* Open  network data  base files  and mark  them as staying
 * open even after a later search if `stay_open' is non-zero */
INTDEF void NOTHROW_RPC(LIBCCALL libc_setnetent)(int stay_open);
/* Close network data base files and clear `stay open' flag */
INTDEF void NOTHROW_RPC_NOKOS(LIBCCALL libc_endnetent)(void);
/* Get next entry from network data base file. Open data base if necessary */
INTDEF struct netent *NOTHROW_RPC(LIBCCALL libc_getnetent)(void);
/* Return entry from network data base which address match `net' and type `type' */
INTDEF struct netent *NOTHROW_RPC(LIBCCALL libc_getnetbyaddr)(uint32_t net, int type);
/* Return entry from network data base for network with `name' */
INTDEF struct netent *NOTHROW_RPC(LIBCCALL libc_getnetbyname)(char const *name);
/* Reentrant   versions  of  the   functions  above.  The  additional
 * arguments specify a buffer of `buflen' starting at `buf'. The last
 * argument  is a  pointer to a  variable which gets  the value which
 * would  be  stored   in  the  global   variable  `herrno'  by   the
 * non-reentrant functions.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_getnetent_r)(struct netent *__restrict result_buf, char *__restrict buf, size_t buflen, struct netent **__restrict result, int *__restrict h_errnop);
/* Reentrant   versions  of  the   functions  above.  The  additional
 * arguments specify a buffer of `buflen' starting at `buf'. The last
 * argument  is a  pointer to a  variable which gets  the value which
 * would  be  stored   in  the  global   variable  `herrno'  by   the
 * non-reentrant functions.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_getnetbyaddr_r)(uint32_t net, int type, struct netent *__restrict result_buf, char *__restrict buf, size_t buflen, struct netent **__restrict result, int *__restrict h_errnop);
/* Reentrant   versions  of  the   functions  above.  The  additional
 * arguments specify a buffer of `buflen' starting at `buf'. The last
 * argument  is a  pointer to a  variable which gets  the value which
 * would  be  stored   in  the  global   variable  `herrno'  by   the
 * non-reentrant functions.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_getnetbyname_r)(char const *__restrict name, struct netent *__restrict result_buf, char *__restrict buf, size_t buflen, struct netent **__restrict result, int *__restrict h_errnop);
/* Open service data base files and mark them as staying open even
 * after a later search if `stay_open' is non-zero */
INTDEF void NOTHROW_RPC(LIBCCALL libc_setservent)(int stay_open);
/* Close service data base files and clear `stay open' flag */
INTDEF void NOTHROW_RPC_NOKOS(LIBCCALL libc_endservent)(void);
/* Get next entry from service data base file. Open data base if necessary */
INTDEF struct servent *NOTHROW_RPC(LIBCCALL libc_getservent)(void);
/* Return entry from network data base for network with `name' and protocol `proto' */
INTDEF struct servent *NOTHROW_RPC(LIBCCALL libc_getservbyname)(char const *name, char const *proto);
/* Return entry from service data base which matches port `port' and protocol `proto' */
INTDEF struct servent *NOTHROW_RPC(LIBCCALL libc_getservbyport)(int port, char const *proto);
/* Reentrant  versions  of  the  functions  above.  The additional
 * arguments specify  a  buffer  of `buflen'  starting  at  `buf'.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_getservent_r)(struct servent *__restrict result_buf, char *__restrict buf, size_t buflen, struct servent **__restrict result);
/* Reentrant  versions  of  the  functions  above.  The additional
 * arguments specify  a  buffer  of `buflen'  starting  at  `buf'.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_getservbyname_r)(char const *__restrict name, char const *__restrict proto, struct servent *__restrict result_buf, char *__restrict buf, size_t buflen, struct servent **__restrict result);
/* Reentrant  versions  of  the  functions  above.  The additional
 * arguments specify  a  buffer  of `buflen'  starting  at  `buf'.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_getservbyport_r)(int port, char const *__restrict proto, struct servent *__restrict result_buf, char *__restrict buf, size_t buflen, struct servent **__restrict result);
/* Open protocol data base files and mark them as staying open even
 * after a later search if `stay_open' is non-zero */
INTDEF void NOTHROW_RPC(LIBCCALL libc_setprotoent)(int stay_open);
/* Close protocol data base files and clear `stay open' flag */
INTDEF void NOTHROW_RPC_NOKOS(LIBCCALL libc_endprotoent)(void);
/* Get next entry from protocol data base file. Open data base if necessary */
INTDEF struct protoent *NOTHROW_RPC(LIBCCALL libc_getprotoent)(void);
/* Return entry from protocol data base for network with `name' */
INTDEF struct protoent *NOTHROW_RPC(LIBCCALL libc_getprotobyname)(char const *name);
/* Return entry from protocol data base which number is `proto' */
INTDEF struct protoent *NOTHROW_RPC(LIBCCALL libc_getprotobynumber)(int proto);
/* Reentrant  versions  of  the  functions  above.  The additional
 * arguments specify  a  buffer  of `buflen'  starting  at  `buf'.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_getprotoent_r)(struct protoent *__restrict result_buf, char *__restrict buf, size_t buflen, struct protoent **__restrict result);
/* Reentrant  versions  of  the  functions  above.  The additional
 * arguments specify  a  buffer  of `buflen'  starting  at  `buf'.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_getprotobyname_r)(char const *__restrict name, struct protoent *__restrict result_buf, char *__restrict buf, size_t buflen, struct protoent **__restrict result);
/* Reentrant  versions  of  the  functions  above.  The additional
 * arguments specify  a  buffer  of `buflen'  starting  at  `buf'.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_getprotobynumber_r)(int proto, struct protoent *__restrict result_buf, char *__restrict buf, size_t buflen, struct protoent **__restrict result);
/* Establish  network   group   `netgroup'   for   enumeration.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_setnetgrent)(char const *netgroup);
/* Free  all  space allocated  by previous  `setnetgrent' call.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTDEF void NOTHROW_RPC_NOKOS(LIBCCALL libc_endnetgrent)(void);
/* Get next member of netgroup established by last `setnetgrent'  call
 * and return pointers to elements in `hostp', `userp', and `domainp'.
 * This  function  is  not part  of  POSIX and  therefore  no official
 * cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_getnetgrent)(char **__restrict hostp, char **__restrict userp, char **__restrict domainp);
/* Test whether `netgroup' contains the triple `(host, user, domain)'.
 * This  function  is  not part  of  POSIX and  therefore  no official
 * cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_innetgr)(char const *netgroup, char const *host, char const *user, char const *domain);
/* Reentrant version of `getnetgrent' where result is placed in `buf'.
 * This  function  is  not part  of  POSIX and  therefore  no official
 * cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_getnetgrent_r)(char **__restrict hostp, char **__restrict userp, char **__restrict domainp, char *__restrict buf, size_t buflen);
/* Call `rshd' at port `rport' on remote machine `*ahost' to execute `cmd'.
 * The  local  user is  `locuser',  on the  remote  machine the  command is
 * executed as `remuser'. In `*fd2p' the  descriptor to the socket for  the
 * connection is  returned.  The  caller  must have  the  right  to  use  a
 * reserved  port.  When  the   function  returns  `*ahost'  contains   the
 * official host name.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_rcmd)(char **__restrict ahost, uint16_t rport, char const *__restrict locuser, char const *__restrict remuser, char const *__restrict cmd, int *__restrict fd2p);
/* This is the equivalent function where the protocol can be selected
 * and which therefore can be used for IPv6.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_rcmd_af)(char **__restrict ahost, uint16_t rport, char const *__restrict locuser, char const *__restrict remuser, char const *__restrict cmd, int *__restrict fd2p, sa_family_t af);
/* Call  `rexecd' at port  `rport' on remote  machine `*ahost' to execute
 * `cmd'. The process  runs at the  remote machine using  the ID of  user
 * `name' whose cleartext password is `passwd'. In `*fd2p' the descriptor
 * to  the  socket  for the  connection  is returned.  When  the function
 * returns    `*ahost'     contains    the     official    host     name.
 * This  function  is  not  part  of  POSIX  and  therefore  no  official
 * cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_rexec)(char **__restrict ahost, int rport, char const *__restrict name, char const *__restrict pass, char const *__restrict cmd, int *__restrict fd2p);
/* This is the equivalent function where the protocol can be selected
 * and which therefore can be used for IPv6.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_rexec_af)(char **__restrict ahost, int rport, char const *__restrict name, char const *__restrict pass, char const *__restrict cmd, int *__restrict fd2p, sa_family_t af);
/* Check whether user `remuser' on system `rhost' is allowed to login
 * as `locuser'. If  `suser' is  not zero  the user  tries to  become
 * superuser. Return 0 if it is possible.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_ruserok)(char const *rhost, int suser, char const *remuser, char const *locuser);
/* This is the equivalent function where the protocol can be selected
 * and which therefore can be used for IPv6.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_ruserok_af)(char const *rhost, int suser, char const *remuser, char const *locuser, sa_family_t af);
/* Check whether user  `remuser' on system  indicated by IPv4  address
 * `raddr' is allowed to login as `locuser'. Non-IPv4 (e.g., IPv6) are
 * not supported. If  `suser' is  not zero  the user  tries to  become
 * superuser. Return 0 if it is possible.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_iruserok)(uint32_t raddr, int suser, char const *remuser, char const *locuser);
/* This is the equivalent function where the family is the address
 * pointed  to by `raddr'  is determined by the  value of `af'. It
 * therefore can be used for IPv6
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_iruserok_af)(void const *raddr, int suser, char const *remuser, char const *locuser, sa_family_t af);
/* Try to allocate reserved port, returning a descriptor for a socket opened
 * at this port  or -1  if unsuccessful. The  search for  an available  port
 * will   start   at   `alport'   and   continues   with   lower    numbers.
 * This   function  is  not   part  of  POSIX   and  therefore  no  official
 * cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_rresvport)(int *alport);
/* This is the equivalent function where the protocol can be selected
 * and which therefore can be used for IPv6.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_rresvport_af)(int *alport, sa_family_t af);
/* Translate name of a service location and/or a service name to set of socket addresses */
INTDEF int NOTHROW_RPC(LIBCCALL libc_getaddrinfo)(char const *__restrict name, char const *__restrict service, struct addrinfo const *__restrict req, struct addrinfo **__restrict pai);
/* Free `addrinfo' structure `ai' including associated storage */
INTDEF void NOTHROW_NCX(LIBCCALL libc_freeaddrinfo)(struct addrinfo *ai);
/* Convert error return from getaddrinfo() to a string */
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(LIBCCALL libc_gai_strerror)(int ecode);
/* Translate a socket address to a location and service name */
INTDEF int NOTHROW_RPC(LIBCCALL libc_getnameinfo)(struct sockaddr const *__restrict sa, socklen_t salen, char *__restrict host, socklen_t hostlen, char *__restrict serv, socklen_t servlen, int flags);
/* Enqueue `ent' requests from the `list'. If `mode' is GAI_WAIT wait until all
 * requests  are  handled. If  `wait'  is GAI_NOWAIT  return  immediately after
 * queueing  the   requests  and   signal   completion  according   to   `sig'.
 * This   function   is  not   part  of   POSIX   and  therefore   no  official
 * cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_getaddrinfo_a)(int mode, struct gaicb *list[__restrict_arr], int ent, struct sigevent *__restrict sig);
/* Suspend execution of the thread until at least one of the `ent'  requests
 * in `list' is handled. If `timeout' is not a null pointer it specifies the
 * longest time the function keeps  waiting before returning with an  error.
 * This   function  is  not   part  of  POSIX   and  therefore  no  official
 * cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_gai_suspend)(struct gaicb const *const list[], int ent, struct timespec const *timeout);
/* Suspend execution of the thread until at least one of the `ent'  requests
 * in `list' is handled. If `timeout' is not a null pointer it specifies the
 * longest time the function keeps  waiting before returning with an  error.
 * This   function  is  not   part  of  POSIX   and  therefore  no  official
 * cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_gai_suspend64)(struct gaicb const *const list[], int ent, struct timespec64 const *timeout);
/* Get the error status of the request `req' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_gai_error)(struct gaicb *req);
/* Cancel the requests associated with `gaicbp' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_gai_cancel)(struct gaicb *gaicbp);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_NETDB_H */
