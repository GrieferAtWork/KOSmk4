/* HASH CRC-32:0x40e444e7 */
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
#ifndef _NETDB_H
#define _NETDB_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/crt/db/netdb.h>
#include <bits/types.h>
#include <netinet/in.h>
#include <stdint.h>

#ifdef __USE_MISC
#include <rpc/netdb.h>
#endif /* __USE_MISC */

#ifdef __USE_GNU
#include <bits/sigevent.h>
#include <bits/timespec.h>
#endif /* __USE_GNU */

__SYSDECL_BEGIN

/* Disclaimer: Documentation is taken from Glibc /usr/include/netdb.h */
  /* Copyright (C) 1996-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/* All data returned by the network data base library are supplied in
   host order and returned in network order (suitable for use in
   system calls). */

/* Absolute file name for network data base files. */
#define _PATH_HEQUIV        "/etc/hosts.equiv"
#define _PATH_HOSTS         "/etc/hosts"
#define _PATH_NETWORKS      "/etc/networks"
#define _PATH_NSSWITCH_CONF "/etc/nsswitch.conf"
#define _PATH_PROTOCOLS     "/etc/protocols"
#define _PATH_SERVICES      "/etc/services"


#if defined(__USE_MISC) || !defined(__USE_XOPEN2K8)
/* Possible values left in `h_errno'. */
#define HOST_NOT_FOUND  1 /* Authoritative Answer Host not found. */
#define TRY_AGAIN       2 /* Non-Authoritative Host not found, or SERVERFAIL. */
#define NO_RECOVERY     3 /* Non recoverable errors, FORMERR, REFUSED, NOTIMP. */
#define NO_DATA         4 /* Valid name, no data record of requested type. */
#endif /* __USE_MISC || !__USE_XOPEN2K8 */

#ifdef __USE_MISC
#define NETDB_INTERNAL  (-1)       /* See errno. */
#define NETDB_SUCCESS     0        /* No problem. */
#define NO_ADDRESS        NO_DATA  /* No address, look for MX record. */
#endif /* __USE_MISC */

#if defined(__USE_XOPEN2K) || defined(__USE_XOPEN_EXTENDED)
#define IPPORT_RESERVED  1024 /* Highest reserved Internet port number. */
#endif /* __USE_XOPEN2K || __USE_XOPEN_EXTENDED */

#ifdef __USE_GNU
#define SCOPE_DELIMITER  '%' /* Scope delimiter for getaddrinfo(), getnameinfo(). */
#endif /* __USE_GNU */


/* Extension from POSIX.1:2001. */
#ifdef __USE_XOPEN2K
#ifdef __USE_GNU
/* Lookup mode. */
#define GAI_WAIT   0
#define GAI_NOWAIT 1
#endif /* __USE_GNU */
/* Flags for `addrinfo::ai_flags' */
#define AI_PASSIVE                  0x0001 /* Socket address is intended for `bind'. */
#define AI_CANONNAME                0x0002 /* Request for canonical name. */
#define AI_NUMERICHOST              0x0004 /* Don't use name resolution. */
#define AI_V4MAPPED                 0x0008 /* IPv4 mapped addresses are acceptable. */
#define AI_ALL                      0x0010 /* Return IPv4 mapped and IPv6 addresses. */
#define AI_ADDRCONFIG               0x0020 /* Use configuration of this host to choose returned address type. */
#ifdef __USE_GNU
#define AI_IDN                      0x0040 /* IDN encode input (assuming it is encoded in the current locale's character set) before looking it up. */
#define AI_CANONIDN                 0x0080 /* Translate canonical name from IDN format. */
#define AI_IDN_ALLOW_UNASSIGNED     0x0100 /* Don't reject unassigned Unicode code points. */
#define AI_IDN_USE_STD3_ASCII_RULES 0x0200 /* Validate strings according to STD3 rules. */
#endif /* __USE_GNU */
#define AI_NUMERICSERV              0x0400 /* Don't use name resolution. */

/* Error values for `getaddrinfo' function. */
#define EAI_BADFLAGS     (-1)   /* Invalid value for `ai_flags' field. */
#define EAI_NONAME       (-2)   /* NAME or SERVICE is unknown. */
#define EAI_AGAIN        (-3)   /* Temporary failure in name resolution. */
#define EAI_FAIL         (-4)   /* Non-recoverable failure in name res. */
#define EAI_FAMILY       (-6)   /* `ai_family' not supported. */
#define EAI_SOCKTYPE     (-7)   /* `ai_socktype' not supported. */
#define EAI_SERVICE      (-8)   /* SERVICE not supported for `ai_socktype'. */
#define EAI_MEMORY       (-10)  /* Memory allocation failure. */
#define EAI_SYSTEM       (-11)  /* System error returned in `errno'. */
#define EAI_OVERFLOW     (-12)  /* Argument buffer overflow. */
#ifdef __USE_GNU
#define EAI_NODATA       (-5)   /* No address associated with NAME. */
#define EAI_ADDRFAMILY   (-9)   /* Address family for NAME not supported. */
#define EAI_INPROGRESS   (-100) /* Processing request in progress. */
#define EAI_CANCELED     (-101) /* Request canceled. */
#define EAI_NOTCANCELED  (-102) /* Request not canceled. */
#define EAI_ALLDONE      (-103) /* All requests done. */
#define EAI_INTR         (-104) /* Interrupted by a signal. */
#define EAI_IDN_ENCODE   (-105) /* IDN encoding failed. */
#endif /* __USE_GNU */

#ifdef __USE_MISC
#define NI_MAXHOST      1025
#define NI_MAXSERV      32
#endif /* __USE_MISC */
#define NI_NUMERICHOST              0x0001 /* Don't try to look up hostname. */
#define NI_NUMERICSERV              0x0002 /* Don't convert port number to name. */
#define NI_NOFQDN                   0x0004 /* Only return nodename portion. */
#define NI_NAMEREQD                 0x0008 /* Don't return numeric addresses. */
#define NI_DGRAM                    0x0010 /* Look up UDP service rather than TCP. */
#ifdef __USE_GNU
#define NI_IDN                      0x0020 /* Convert name from IDN format. */
#define NI_IDN_ALLOW_UNASSIGNED     0x0040 /* Don't reject unassigned Unicode code points. */
#define NI_IDN_USE_STD3_ASCII_RULES 0x0080 /* Validate strings according to STD3 rules. */
#endif /* __USE_GNU */
#endif /* __USE_XOPEN2K */



#ifdef __CC__

/* Description of data base entry for a single host. */
struct hostent {
	/* XXX: It's unclear if h_name can be NULL! */
	char                   *h_name;      /* [0..1] Official name of host. */
	/* XXX: It's unclear if h_aliases can be NULL! (or is {NULL} when empty) */
	char                  **h_aliases;   /* [0..1][0..n] Alias list. (List is terminated by a NULL-entry) */
	__STDC_INT32_AS_SSIZE_T h_addrtype;  /* Host address type (One of `AF_*'; e.g. AF_INET or AF_INET6). */
	__STDC_INT32_AS_SIZE_T  h_length;    /* Length of the address (in bytes). */
#ifdef __USE_MISC
#ifdef __INTELLISENSE__ /* Better syntax highlighting */
	union {
	char                  **h_addr_list; /* [0..1][1..n] List of addresses from name server. (List is terminated by a NULL-entry) */
	char                   *h_addr;      /* [1..1] Address, for backward compatibility. */
	};
#else /* __INTELLISENSE__ */
	char                  **h_addr_list; /* [0..1][1..n] List of addresses from name server. (List is terminated by a NULL-entry) */
#define                     h_addr       h_addr_list[0] /* [1..1] Address, for backward compatibility. */
#endif /* !__INTELLISENSE__ */
#else /* __USE_MISC */
	char                  **h_addr_list; /* [0..1][1..n] List of addresses from name server. (List is terminated by a NULL-entry) */
#endif /* !__USE_MISC */
};


/* Description of data base entry for a single service. */
struct servent {
	/* XXX: It's unclear if s_name can be NULL! */
	char                  *s_name;    /* [0..1] Official service name. */
	/* XXX: It's unclear if s_aliases can be NULL! (or is {NULL} when empty) */
	char                 **s_aliases; /* [0..1][0..n] Alias list. (List is terminated by a NULL-entry) */
	__STDC_INT32_AS_SIZE_T s_port;    /* Port number. */
	/* XXX: It's unclear if s_proto can be NULL! */
	char                  *s_proto;   /* [0..1] Protocol to use. */
};


/* Description of data base entry for a single service. */
struct protoent {
	/* XXX: It's unclear if p_name can be NULL! */
	char                   *p_name;    /* [0..1] Official protocol name. */
	/* XXX: It's unclear if p_aliases can be NULL! (or is {NULL} when empty) */
	char                  **p_aliases; /* [0..1][0..n] Alias list. */
	__STDC_INT32_AS_SSIZE_T p_proto;   /* Protocol number. */
};



/* Extension from POSIX.1:2001. */
#ifdef __USE_XOPEN2K
/* Structure to contain information about address of a service provider. */
struct addrinfo {
	__STDC_INT32_AS_SIZE_T  ai_flags;     /* Input flags. */
	__STDC_INT32_AS_SSIZE_T ai_family;    /* Protocol family for socket. */
	__STDC_INT32_AS_SSIZE_T ai_socktype;  /* Socket type. */
	__STDC_INT32_AS_SSIZE_T ai_protocol;  /* Protocol for socket. */
	socklen_t               ai_addrlen;   /* Length of socket address. */
	struct sockaddr        *ai_addr;      /* [0..ai_addrlen] Socket address for socket. */
	char                   *ai_canonname; /* [0..1] Canonical name for service location (or NULL if not requested; s.a. `AI_CANONNAME'). */
	struct addrinfo        *ai_next;      /* [0..1] Pointer to next in list. (or NULL for the last entry) */
};

#ifdef __USE_GNU
/* Structure used as control block for asynchronous lookup. */
struct gaicb {
	/* XXX: It's unclear if ar_name can be NULL! */
	char const            *ar_name;    /* [0..1] Name to look up. */
	/* XXX: It's unclear if ar_service can be NULL! */
	char const            *ar_service; /* [0..1] Service name. */
	/* XXX: It's unclear if ar_request can be NULL! */
	struct addrinfo const *ar_request; /* [0..1] Additional request specification. */
	/* XXX: It's unclear if ar_result can be NULL! */
	struct addrinfo       *ar_result;  /* [0..1] Pointer to result. */
	/* The following are internal elements. */
	__STDC_INT32_AS_SIZE_T __return;
	__STDC_INT32_AS_SIZE_T __glibc_reserved[5];
};
#endif /* __USE_GNU */
#endif /* __USE_XOPEN2K */



#if defined(__USE_MISC) || !defined(__USE_XOPEN2K8)
#ifndef ____h_errno_location_defined
#define ____h_errno_location_defined 1
#ifdef __CRT_HAVE___h_errno_location
/* Function to get address of global `h_errno' variable */
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,int *,__NOTHROW_NCX,__h_errno_location,(void),())
#else /* __CRT_HAVE___h_errno_location */
#undef ____h_errno_location_defined
#endif /* !__CRT_HAVE___h_errno_location */
#endif /* !____h_errno_location_defined */
/* Error status for non-reentrant lookup functions.
 * We use a macro to access always the thread-specific `h_errno' variable. */
#ifdef ____h_errno_location_defined
#define h_errno   (*__h_errno_location())
#endif /* ____h_errno_location_defined */
#endif /* __USE_MISC || !__USE_XOPEN2K8 */

#ifdef __USE_MISC
/* Print error indicated by `h_errno' variable on standard error.
 * STR, if non-null, is printed before the error string */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC,herror,(char const *__str),(__str))
/* Return string associated with error ERR_NUM */
__CDECLARE_OPT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW_NCX,hstrerror,(int __err_num),(__err_num))
#endif /* __USE_MISC */
/* Open host data base files and mark them as staying
 * open even after a later search if STAY_OPEN is non-zero */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC,sethostent,(int __stay_open),(__stay_open))
/* Close host data base files and clear `stay open' flag */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC_NOKOS,endhostent,(void),())
/* Get next entry from host data base file. Open data base if necessary */
__CDECLARE_OPT(,struct hostent *,__NOTHROW_RPC,gethostent,(void),())
/* Return entry from host data base which address match ADDR with length LEN and type TYPE */
__CDECLARE_OPT(,struct hostent *,__NOTHROW_RPC,gethostbyaddr,(void const *__addr, socklen_t __len, int __type),(__addr,__len,__type))
/* Return entry from host data base for host with NAME */
__CDECLARE_OPT(,struct hostent *,__NOTHROW_RPC,gethostbyname,(char const *__name),(__name))
#ifdef __USE_MISC
/* Return entry from host data base for host with NAME. AF must be
 * set to the address type which is `AF_INET' for IPv4 or `AF_INET6'
 * for IPv6.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE_OPT(,struct hostent *,__NOTHROW_RPC,gethostbyname2,(char const *__name, int __af),(__name,__af))
/* Reentrant versions of the functions above. The additional arguments
 * specify a buffer of BUFLEN starting at BUF. The last argument is a
 * pointer to a variable which gets the value which would be stored in
 * the global variable `herrno' by the non-reentrant functions.
 * These functions are not part of POSIX and therefore no official cancellation point */
__CDECLARE_OPT(,int,__NOTHROW_RPC,gethostent_r,(struct hostent *__restrict __result_buf, char *__restrict __buf, size_t __buflen, struct hostent **__restrict __result, int *__restrict __h_errnop),(__result_buf,__buf,__buflen,__result,__h_errnop))
/* Reentrant versions of the functions above. The additional arguments
 * specify a buffer of BUFLEN starting at BUF. The last argument is a
 * pointer to a variable which gets the value which would be stored in
 * the global variable `herrno' by the non-reentrant functions.
 * These functions are not part of POSIX and therefore no official cancellation point */
__CDECLARE_OPT(,int,__NOTHROW_RPC,gethostbyaddr_r,(void const *__restrict __addr, socklen_t __len, int __type, struct hostent *__restrict __result_buf, char *__restrict __buf, size_t __buflen, struct hostent **__restrict __result, int *__restrict __h_errnop),(__addr,__len,__type,__result_buf,__buf,__buflen,__result,__h_errnop))
/* Reentrant versions of the functions above. The additional arguments
 * specify a buffer of BUFLEN starting at BUF. The last argument is a
 * pointer to a variable which gets the value which would be stored in
 * the global variable `herrno' by the non-reentrant functions.
 * These functions are not part of POSIX and therefore no official cancellation point */
__CDECLARE_OPT(,int,__NOTHROW_RPC,gethostbyname_r,(char const *__restrict __name, struct hostent *__restrict __result_buf, char *__restrict __buf, size_t __buflen, struct hostent **__restrict __result, int *__restrict __h_errnop),(__name,__result_buf,__buf,__buflen,__result,__h_errnop))
/* Reentrant versions of the functions above. The additional arguments
 * specify a buffer of BUFLEN starting at BUF. The last argument is a
 * pointer to a variable which gets the value which would be stored in
 * the global variable `herrno' by the non-reentrant functions.
 * These functions are not part of POSIX and therefore no official cancellation point */
__CDECLARE_OPT(,int,__NOTHROW_RPC,gethostbyname2_r,(char const *__restrict __name, int __af, struct hostent *__restrict __result_buf, char *__restrict __buf, size_t __buflen, struct hostent **__restrict __result, int *__restrict __h_errnop),(__name,__af,__result_buf,__buf,__buflen,__result,__h_errnop))
#endif /* __USE_MISC */
/* Open network data base files and mark them as staying
 * open even after a later search if STAY_OPEN is non-zero */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC,setnetent,(int __stay_open),(__stay_open))
/* Close network data base files and clear `stay open' flag */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC_NOKOS,endnetent,(void),())
/* Get next entry from network data base file. Open data base if necessary */
__CDECLARE_OPT(,struct netent *,__NOTHROW_RPC,getnetent,(void),())
/* Return entry from network data base which address match NET and type TYPE */
__CDECLARE_OPT(,struct netent *,__NOTHROW_RPC,getnetbyaddr,(uint32_t __net, int __type),(__net,__type))
/* Return entry from network data base for network with NAME */
__CDECLARE_OPT(,struct netent *,__NOTHROW_RPC,getnetbyname,(char const *__name),(__name))

#ifdef __USE_MISC
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF. The last
 * argument is a pointer to a variable which gets the value which
 * would be stored in the global variable `herrno' by the
 * non-reentrant functions.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE_OPT(,int,__NOTHROW_RPC,getnetent_r,(struct netent *__restrict __result_buf, char *__restrict __buf, size_t __buflen, struct netent **__restrict __result, int *__restrict __h_errnop),(__result_buf,__buf,__buflen,__result,__h_errnop))
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF. The last
 * argument is a pointer to a variable which gets the value which
 * would be stored in the global variable `herrno' by the
 * non-reentrant functions.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE_OPT(,int,__NOTHROW_RPC,getnetbyaddr_r,(uint32_t __net, int __type, struct netent *__restrict __result_buf, char *__restrict __buf, size_t __buflen, struct netent **__restrict __result, int *__restrict __h_errnop),(__net,__type,__result_buf,__buf,__buflen,__result,__h_errnop))
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF. The last
 * argument is a pointer to a variable which gets the value which
 * would be stored in the global variable `herrno' by the
 * non-reentrant functions.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE_OPT(,int,__NOTHROW_RPC,getnetbyname_r,(char const *__restrict __name, struct netent *__restrict __result_buf, char *__restrict __buf, size_t __buflen, struct netent **__restrict __result, int *__restrict __h_errnop),(__name,__result_buf,__buf,__buflen,__result,__h_errnop))
#endif /* __USE_MISC */
/* Open service data base files and mark them as staying open even
 * after a later search if STAY_OPEN is non-zero */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC,setservent,(int __stay_open),(__stay_open))
/* Close service data base files and clear `stay open' flag */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC_NOKOS,endservent,(void),())
/* Get next entry from service data base file. Open data base if necessary */
__CDECLARE_OPT(,struct servent *,__NOTHROW_RPC,getservent,(void),())
/* Return entry from network data base for network with NAME and protocol PROTO */
__CDECLARE_OPT(,struct servent *,__NOTHROW_RPC,getservbyname,(char const *__name, char const *__proto),(__name,__proto))
/* Return entry from service data base which matches port PORT and protocol PROTO */
__CDECLARE_OPT(,struct servent *,__NOTHROW_RPC,getservbyport,(int __port, char const *__proto),(__port,__proto))

#ifdef __USE_MISC
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE_OPT(,int,__NOTHROW_RPC,getservent_r,(struct servent *__restrict __result_buf, char *__restrict __buf, size_t __buflen, struct servent **__restrict __result),(__result_buf,__buf,__buflen,__result))
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE_OPT(,int,__NOTHROW_RPC,getservbyname_r,(char const *__restrict __name, char const *__restrict __proto, struct servent *__restrict __result_buf, char *__restrict __buf, size_t __buflen, struct servent **__restrict __result),(__name,__proto,__result_buf,__buf,__buflen,__result))
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE_OPT(,int,__NOTHROW_RPC,getservbyport_r,(int __port, char const *__restrict __proto, struct servent *__restrict __result_buf, char *__restrict __buf, size_t __buflen, struct servent **__restrict __result),(__port,__proto,__result_buf,__buf,__buflen,__result))
#endif /* __USE_MISC */
/* Open protocol data base files and mark them as staying open even
 * after a later search if STAY_OPEN is non-zero */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC,setprotoent,(int __stay_open),(__stay_open))
/* Close protocol data base files and clear `stay open' flag */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC_NOKOS,endprotoent,(void),())
/* Get next entry from protocol data base file. Open data base if necessary */
__CDECLARE_OPT(,struct protoent *,__NOTHROW_RPC,getprotoent,(void),())
/* Return entry from protocol data base for network with NAME */
__CDECLARE_OPT(,struct protoent *,__NOTHROW_RPC,getprotobyname,(char const *__name),(__name))
/* Return entry from protocol data base which number is PROTO */
__CDECLARE_OPT(,struct protoent *,__NOTHROW_RPC,getprotobynumber,(int __proto),(__proto))

#ifdef __USE_MISC
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE_OPT(,int,__NOTHROW_RPC,getprotoent_r,(struct protoent *__restrict __result_buf, char *__restrict __buf, size_t __buflen, struct protoent **__restrict __result),(__result_buf,__buf,__buflen,__result))
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE_OPT(,int,__NOTHROW_RPC,getprotobyname_r,(char const *__restrict __name, struct protoent *__restrict __result_buf, char *__restrict __buf, size_t __buflen, struct protoent **__restrict __result),(__name,__result_buf,__buf,__buflen,__result))
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE_OPT(,int,__NOTHROW_RPC,getprotobynumber_r,(int __proto, struct protoent *__restrict __result_buf, char *__restrict __buf, size_t __buflen, struct protoent **__restrict __result),(__proto,__result_buf,__buf,__buflen,__result))
/* Establish network group NETGROUP for enumeration.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE_OPT(,int,__NOTHROW_RPC,setnetgrent,(char const *__netgroup),(__netgroup))
/* Free all space allocated by previous `setnetgrent' call.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC_NOKOS,endnetgrent,(void),())
/* Get next member of netgroup established by last `setnetgrent' call
 * and return pointers to elements in HOSTP, USERP, and DOMAINP.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE_OPT(,int,__NOTHROW_RPC,getnetgrent,(char **__restrict __hostp, char **__restrict __userp, char **__restrict __domainp),(__hostp,__userp,__domainp))
/* Test whether NETGROUP contains the triple (HOST, USER, DOMAIN).
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE_OPT(,int,__NOTHROW_RPC,innetgr,(char const *__netgroup, char const *__host, char const *__user, char const *__domain),(__netgroup,__host,__user,__domain))
/* Reentrant version of `getnetgrent' where result is placed in BUFFER.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE_OPT(,int,__NOTHROW_RPC,getnetgrent_r,(char **__restrict __hostp, char **__restrict __userp, char **__restrict __domainp, char *__restrict __buf, size_t __buflen),(__hostp,__userp,__domainp,__buf,__buflen))
#endif /* __USE_MISC */

#ifdef __USE_MISC
/* Call `rshd' at port RPORT on remote machine *AHOST to execute CMD.
 * The local user is LOCUSER, on the remote machine the command is
 * executed as REMUSER. In *FD2P the descriptor to the socket for the
 * connection is returned. The caller must have the right to use a
 * reserved port. When the function returns *AHOST contains the
 * official host name.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE_OPT(,int,__NOTHROW_RPC,rcmd,(char **__restrict __ahost, __UINT16_TYPE__ __rport, char const *__restrict __locuser, char const *__restrict __remuser, char const *__restrict __cmd, int *__restrict __fd2p),(__ahost,__rport,__locuser,__remuser,__cmd,__fd2p))
/* This is the equivalent function where the protocol can be selected
 * and which therefore can be used for IPv6.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE_OPT(,int,__NOTHROW_RPC,rcmd_af,(char **__restrict __ahost, __UINT16_TYPE__ __rport, char const *__restrict __locuser, char const *__restrict __remuser, char const *__restrict __cmd, int *__restrict __fd2p, sa_family_t __af),(__ahost,__rport,__locuser,__remuser,__cmd,__fd2p,__af))
/* Call `rexecd' at port RPORT on remote machine *AHOST to execute
 * CMD. The process runs at the remote machine using the ID of user
 * NAME whose cleartext password is PASSWD. In *FD2P the descriptor
 * to the socket for the connection is returned. When the function
 * returns *AHOST contains the official host name.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE_OPT(,int,__NOTHROW_RPC,rexec,(char **__restrict __ahost, int __rport, char const *__restrict __name, char const *__restrict __pass, char const *__restrict __cmd, int *__restrict __fd2p),(__ahost,__rport,__name,__pass,__cmd,__fd2p))
/* This is the equivalent function where the protocol can be selected
 * and which therefore can be used for IPv6.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE_OPT(,int,__NOTHROW_RPC,rexec_af,(char **__restrict __ahost, int __rport, char const *__restrict __name, char const *__restrict __pass, char const *__restrict __cmd, int *__restrict __fd2p, sa_family_t __af),(__ahost,__rport,__name,__pass,__cmd,__fd2p,__af))
/* Check whether user REMUSER on system RHOST is allowed to login as LOCUSER.
 * If SUSER is not zero the user tries to become superuser. Return 0 if
 * it is possible.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE_OPT(,int,__NOTHROW_RPC,ruserok,(char const *__rhost, int __suser, char const *__remuser, char const *__locuser),(__rhost,__suser,__remuser,__locuser))
/* This is the equivalent function where the protocol can be selected
 * and which therefore can be used for IPv6.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE_OPT(,int,__NOTHROW_RPC,ruserok_af,(char const *__rhost, int __suser, char const *__remuser, char const *__locuser, sa_family_t __af),(__rhost,__suser,__remuser,__locuser,__af))
/* Check whether user REMUSER on system indicated by IPv4 address
 * RADDR is allowed to login as LOCUSER. Non-IPv4 (e.g., IPv6) are
 * not supported. If SUSER is not zero the user tries to become
 * superuser. Return 0 if it is possible.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE_OPT(,int,__NOTHROW_RPC,iruserok,(uint32_t __raddr, int __suser, char const *__remuser, char const *__locuser),(__raddr,__suser,__remuser,__locuser))
/* This is the equivalent function where the pfamiliy if the address
 * pointed to by RADDR is determined by the value of AF. It therefore
 * can be used for IPv6
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE_OPT(,int,__NOTHROW_RPC,iruserok_af,(void const *__raddr, int __suser, char const *__remuser, char const *__locuser, sa_family_t __af),(__raddr,__suser,__remuser,__locuser,__af))
/* Try to allocate reserved port, returning a descriptor for a socket opened
 * at this port or -1 if unsuccessful. The search for an available port
 * will start at ALPORT and continues with lower numbers.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE_OPT(,int,__NOTHROW_RPC,rresvport,(int *__alport),(__alport))
/* This is the equivalent function where the protocol can be selected
 * and which therefore can be used for IPv6.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE_OPT(,int,__NOTHROW_RPC,rresvport_af,(int *__alport, sa_family_t __af),(__alport,__af))
#endif /* __USE_MISC */

/* Extension from POSIX.1:2001. */
#ifdef __USE_XOPEN2K
/* Translate name of a service location and/or a service name to set of socket addresses */
__CDECLARE_OPT(,int,__NOTHROW_RPC,getaddrinfo,(char const *__restrict __name, char const *__restrict __service, struct addrinfo const *__restrict __req, struct addrinfo **__restrict __pai),(__name,__service,__req,__pai))
/* Free `addrinfo' structure AI including associated storage */
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,freeaddrinfo,(struct addrinfo *__ai),(__ai))
/* Convert error return from getaddrinfo() to a string */
__CDECLARE_OPT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW_NCX,gai_strerror,(int __ecode),(__ecode))
/* Translate a socket address to a location and service name */
__CDECLARE_OPT(,int,__NOTHROW_RPC,getnameinfo,(struct sockaddr const *__restrict __sa, socklen_t __salen, char *__restrict __host, socklen_t __hostlen, char *__restrict __serv, socklen_t __servlen, int __flags),(__sa,__salen,__host,__hostlen,__serv,__servlen,__flags))
#endif /* __USE_XOPEN2K */

#ifdef __USE_GNU
/* Enqueue ENT requests from the LIST. If MODE is GAI_WAIT wait until all
 * requests are handled. If WAIT is GAI_NOWAIT return immediately after
 * queueing the requests and signal completion according to SIG.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE_OPT(,int,__NOTHROW_RPC,getaddrinfo_a,(int __mode, struct gaicb *__list[__restrict_arr], int __ent, struct sigevent *__restrict __sig),(__mode,__list,__ent,__sig))
#if defined(__CRT_HAVE_gai_suspend64) && defined(__USE_TIME_BITS64)
/* Suspend execution of the thread until at least one of the ENT requests
 * in LIST is handled. If TIMEOUT is not a null pointer it specifies the
 * longest time the function keeps waiting before returning with an error.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__CREDIRECT(,int,__NOTHROW_RPC,gai_suspend,(struct gaicb const *const __list[], int __ent, struct timespec const *__timeout),gai_suspend64,(__list,__ent,__timeout))
#elif defined(__CRT_HAVE_gai_suspend) && !defined(__USE_TIME_BITS64)
/* Suspend execution of the thread until at least one of the ENT requests
 * in LIST is handled. If TIMEOUT is not a null pointer it specifies the
 * longest time the function keeps waiting before returning with an error.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE(,int,__NOTHROW_RPC,gai_suspend,(struct gaicb const *const __list[], int __ent, struct timespec const *__timeout),(__list,__ent,__timeout))
#elif defined(__CRT_HAVE_gai_suspend64) || defined(__CRT_HAVE_gai_suspend)
#include <local/netdb/gai_suspend.h>
/* Suspend execution of the thread until at least one of the ENT requests
 * in LIST is handled. If TIMEOUT is not a null pointer it specifies the
 * longest time the function keeps waiting before returning with an error.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__NAMESPACE_LOCAL_USING_OR_IMPL(gai_suspend, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBCCALL gai_suspend)(struct gaicb const *const __list[], int __ent, struct timespec const *__timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gai_suspend))(__list, __ent, __timeout); })
#endif /* ... */

#ifdef __USE_TIME64
#ifdef __CRT_HAVE_gai_suspend64
/* Suspend execution of the thread until at least one of the ENT requests
 * in LIST is handled. If TIMEOUT is not a null pointer it specifies the
 * longest time the function keeps waiting before returning with an error.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE(,int,__NOTHROW_RPC,gai_suspend64,(struct gaicb const *const __list[], int __ent, struct timespec64 const *__timeout),(__list,__ent,__timeout))
#elif defined(__CRT_HAVE_gai_suspend) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Suspend execution of the thread until at least one of the ENT requests
 * in LIST is handled. If TIMEOUT is not a null pointer it specifies the
 * longest time the function keeps waiting before returning with an error.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__CREDIRECT(,int,__NOTHROW_RPC,gai_suspend64,(struct gaicb const *const __list[], int __ent, struct timespec64 const *__timeout),gai_suspend,(__list,__ent,__timeout))
#elif defined(__CRT_HAVE_gai_suspend)
#include <local/netdb/gai_suspend64.h>
/* Suspend execution of the thread until at least one of the ENT requests
 * in LIST is handled. If TIMEOUT is not a null pointer it specifies the
 * longest time the function keeps waiting before returning with an error.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__NAMESPACE_LOCAL_USING_OR_IMPL(gai_suspend64, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBCCALL gai_suspend64)(struct gaicb const *const __list[], int __ent, struct timespec64 const *__timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gai_suspend64))(__list, __ent, __timeout); })
#endif /* ... */
#endif /* __USE_TIME64 */
/* Get the error status of the request REQ */
__CDECLARE_OPT(,int,__NOTHROW_NCX,gai_error,(struct gaicb *__req),(__req))
/* Cancel the requests associated with GAICBP */
__CDECLARE_OPT(,int,__NOTHROW_NCX,gai_cancel,(struct gaicb *__gaicbp),(__gaicbp))
#endif /* __USE_GNU */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_NETDB_H */
