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
%(c_prefix){
/* (>) Standard: POSIX.1-2004 (Issue 6, IEEE Std 1003.1-2004) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/netdb.h) */
/* (#) Portability: DragonFly BSD (/include/netdb.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/netdb.h) */
/* (#) Portability: FreeBSD       (/include/netdb.h) */
/* (#) Portability: GNU C Library (/resolv/netdb.h) */
/* (#) Portability: GNU Hurd      (/usr/include/netdb.h) */
/* (#) Portability: NetBSD        (/include/netdb.h) */
/* (#) Portability: OpenBSD       (/include/netdb.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/netdb.h) */
/* (#) Portability: diet libc     (/include/netdb.h) */
/* (#) Portability: libc4/5       (/include/netdb.h) */
/* (#) Portability: libc6         (/include/netdb.h) */
/* (#) Portability: mintlib       (/include/netdb.h) */
/* (#) Portability: musl libc     (/include/netdb.h) */
/* (#) Portability: uClibc        (/include/netdb.h) */
}

%[default:section(".text.crt{|.dos}.net.db")]

%[define_decl_include("<bits/os/sigevent.h>": ["struct sigevent"])]
%[define_decl_include("<bits/os/sockaddr.h>": ["struct sockaddr"])]

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(sa_family_t = __UINT16_TYPE__)]
%[define_replacement(socklen_t = __socklen_t)]
%[define_replacement(time32_t = __time32_t)]
%[define_replacement(time64_t = __time64_t)]
%[define_replacement(tv_sec = tv_sec)]
%[define_replacement(tv_nsec = tv_nsec)]
%[define_replacement(tv_usec = tv_usec)]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <bits/crt/db/netdb.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <netinet/in.h>
)]%{

#include <stdint.h>

#ifdef __USE_MISC
#include <rpc/netdb.h>
#endif /* __USE_MISC */

#ifdef __USE_GNU
#include <bits/os/sigevent.h> /* struct sigevent */
#include <bits/os/timespec.h> /* struct timespec */
#endif /* __USE_GNU */

/* TODO: Constants and structs from this header should
 *       be  moved  into <asm/>  and  <bits/> headers! */

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
		char              **h_addr_list; /* [0..1][1..n] List of addresses from name server. (List is terminated by a NULL-entry) */
		char               *h_addr;      /* [1..1] Address, for backward compatibility. */
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


}

%
%#if defined(__USE_MISC) || !defined(__USE_XOPEN2K8)
@@Function to get address of global `h_errno' variable
[[guard, const, wunused, nothrow]]
[[nonnull]] int *__h_errno_location();

%/* Error status for non-reentrant lookup functions.
% * We use a macro to access always the thread-specific `h_errno' variable. */
%#ifdef ____h_errno_location_defined
%#define h_errno   (*__h_errno_location())
%#endif /* ____h_errno_location_defined */
%#endif /* __USE_MISC || !__USE_XOPEN2K8 */

%
%#ifdef __USE_MISC
@@Print error indicated by `h_errno' variable on standard error.
@@if non-`NULL',  `str'  is  printed before  the  error  string.
[[cp]]
void herror(char const *str);

@@Return string associated with error `err_num'
[[const, wunused, nothrow]]
char const *hstrerror(int err_num);
%#endif /* __USE_MISC */


@@Open host  data  base  files and  mark  them  as  staying
@@open even after a later search if `stay_open' is non-zero
[[cp]]
void sethostent(int stay_open);

@@Close host data base files and clear `stay open' flag
[[cp_nokos]]
void endhostent();

@@Get next entry from host data base file. Open data base if necessary
[[cp]]
struct hostent *gethostent();

@@Return entry from host data base which address match `addr' with length `len' and type `type'
[[cp, decl_include("<bits/types.h>")]]
struct hostent *gethostbyaddr(void const *addr, socklen_t len, int type);

@@Return entry from host data base for host with `name'
[[cp]]
struct hostent *gethostbyname(char const *name);

%#ifdef __USE_MISC
@@Return entry from host data base for host with `name'. `af' must be
@@set to the address type which  is `AF_INET' for IPv4 or  `AF_INET6'
@@for IPv6.
@@This function is not part of POSIX and therefore no official
@@cancellation point
[[cp]]
struct hostent *gethostbyname2(char const *name, int af);

@@Reentrant versions of  the functions above.  The additional  arguments
@@specify a buffer of `buflen' starting at `buf'. The last argument is a
@@pointer to a variable  which gets the value  which would be stored  in
@@the global variable `herrno' by the non-reentrant functions.
@@These functions are not part of POSIX and therefore no official cancellation point
[[cp, decl_include("<hybrid/typecore.h>")]]
int gethostent_r(struct hostent *__restrict result_buf,
                 char *__restrict buf, size_t buflen,
                 struct hostent **__restrict result,
                 int *__restrict h_errnop);

[[cp, doc_alias("gethostent_r"), decl_include("<bits/types.h>")]]
int gethostbyaddr_r(void const *__restrict addr, socklen_t len, int type,
                    struct hostent *__restrict result_buf,
                    char *__restrict buf, size_t buflen,
                    struct hostent **__restrict result,
                    int *__restrict h_errnop);

[[cp, doc_alias("gethostent_r"), decl_include("<bits/types.h>")]]
int gethostbyname_r(char const *__restrict name,
                    struct hostent *__restrict result_buf,
                    char *__restrict buf, size_t buflen,
                    struct hostent **__restrict result,
                    int *__restrict h_errnop);

[[cp, doc_alias("gethostent_r"), decl_include("<bits/types.h>")]]
int gethostbyname2_r(char const *__restrict name, int af,
                     struct hostent *__restrict result_buf,
                     char *__restrict buf, size_t buflen,
                     struct hostent **__restrict result,
                     int *__restrict h_errnop);
%#endif /* __USE_MISC */


@@Open  network data  base files  and mark  them as staying
@@open even after a later search if `stay_open' is non-zero
[[cp]]
void setnetent(int stay_open);

@@Close network data base files and clear `stay open' flag
[[cp_nokos]]
void endnetent();

@@Get next entry from network data base file. Open data base if necessary
[[cp]]
struct netent *getnetent();

@@Return entry from network data base which address match `net' and type `type'
[[cp, decl_include("<hybrid/typecore.h>")]]
struct netent *getnetbyaddr(uint32_t net, int type);

@@Return entry from network data base for network with `name'
[[cp]]
struct netent *getnetbyname(char const *name);

%
%#ifdef __USE_MISC
@@Reentrant   versions  of  the   functions  above.  The  additional
@@arguments specify a buffer of `buflen' starting at `buf'. The last
@@argument  is a  pointer to a  variable which gets  the value which
@@would  be  stored   in  the  global   variable  `herrno'  by   the
@@non-reentrant functions.
@@These functions are not part of POSIX and therefore no official
@@cancellation point
[[cp, decl_include("<hybrid/typecore.h>")]]
int getnetent_r(struct netent *__restrict result_buf,
                char *__restrict buf, size_t buflen,
                struct netent **__restrict result,
                int *__restrict h_errnop);

[[cp, doc_alias("getnetent_r"), decl_include("<hybrid/typecore.h>")]]
int getnetbyaddr_r(uint32_t net, int type,
                   struct netent *__restrict result_buf,
                   char *__restrict buf, size_t buflen,
                   struct netent **__restrict result,
                   int *__restrict h_errnop);

[[cp, doc_alias("getnetent_r"), decl_include("<hybrid/typecore.h>")]]
int getnetbyname_r(char const *__restrict name,
                   struct netent *__restrict result_buf,
                   char *__restrict buf, size_t buflen,
                   struct netent **__restrict result,
                   int *__restrict h_errnop);
%#endif /* __USE_MISC */


@@Open service data base files and mark them as staying open even
@@after a later search if `stay_open' is non-zero
[[cp]]
void setservent(int stay_open);

@@Close service data base files and clear `stay open' flag
[[cp_nokos]]
void endservent();

@@Get next entry from service data base file. Open data base if necessary
[[cp]]
struct servent *getservent();

@@Return entry from network data base for network with `name' and protocol `proto'
[[cp]]
struct servent *getservbyname(char const *name, char const *proto);

@@Return entry from service data base which matches port `port' and protocol `proto'
[[cp]]
struct servent *getservbyport(int port, char const *proto);

%
%#ifdef __USE_MISC
@@Reentrant  versions  of  the  functions  above.  The additional
@@arguments specify  a  buffer  of `buflen'  starting  at  `buf'.
@@These functions are not part of POSIX and therefore no official
@@cancellation point
[[cp, decl_include("<hybrid/typecore.h>")]]
int getservent_r(struct servent *__restrict result_buf,
                 char *__restrict buf, size_t buflen,
                 struct servent **__restrict result);

[[cp, doc_alias("getservent_r"), decl_include("<hybrid/typecore.h>")]]
int getservbyname_r(char const *__restrict name,
                    char const *__restrict proto,
                    struct servent *__restrict result_buf,
                    char *__restrict buf, size_t buflen,
                    struct servent **__restrict result);

[[cp, doc_alias("getservent_r"), decl_include("<hybrid/typecore.h>")]]
int getservbyport_r(int port, char const *__restrict proto,
                    struct servent *__restrict result_buf,
                    char *__restrict buf, size_t buflen,
                    struct servent **__restrict result);
%#endif /* __USE_MISC */


@@Open protocol data base files and mark them as staying open even
@@after a later search if `stay_open' is non-zero
[[cp]]
void setprotoent(int stay_open);

@@Close protocol data base files and clear `stay open' flag
[[cp_nokos]]
void endprotoent();

@@Get next entry from protocol data base file. Open data base if necessary
[[cp]]
struct protoent *getprotoent();

@@Return entry from protocol data base for network with `name'
[[cp]]
struct protoent *getprotobyname(char const *name);

@@Return entry from protocol data base which number is `proto'
[[cp]]
struct protoent *getprotobynumber(int proto);

%
%#ifdef __USE_MISC
@@Reentrant  versions  of  the  functions  above.  The additional
@@arguments specify  a  buffer  of `buflen'  starting  at  `buf'.
@@These functions are not part of POSIX and therefore no official
@@cancellation point
[[cp, decl_include("<hybrid/typecore.h>")]]
int getprotoent_r(struct protoent *__restrict result_buf,
                  char *__restrict buf, size_t buflen,
                  struct protoent **__restrict result);

[[cp, doc_alias("getprotoent_r"), decl_include("<hybrid/typecore.h>")]]
int getprotobyname_r(char const *__restrict name,
                     struct protoent *__restrict result_buf,
                     char *__restrict buf, size_t buflen,
                     struct protoent **__restrict result);

[[cp, doc_alias("getprotoent_r"), decl_include("<hybrid/typecore.h>")]]
int getprotobynumber_r(int proto,
                       struct protoent *__restrict result_buf,
                       char *__restrict buf, size_t buflen,
                       struct protoent **__restrict result);

@@Establish  network   group   `netgroup'   for   enumeration.
@@This function is not part of POSIX and therefore no official
@@cancellation point
[[cp]]
int setnetgrent(char const *netgroup);

@@Free  all  space allocated  by previous  `setnetgrent' call.
@@This function is not part of POSIX and therefore no official
@@cancellation point
[[cp_nokos]]
void endnetgrent();

@@Get next member of netgroup established by last `setnetgrent'  call
@@and return pointers to elements in `hostp', `userp', and `domainp'.
@@This  function  is  not part  of  POSIX and  therefore  no official
@@cancellation point
[[cp]]
int getnetgrent(char **__restrict hostp,
                char **__restrict userp,
                char **__restrict domainp);

@@Test whether `netgroup' contains the triple `(host, user, domain)'.
@@This  function  is  not part  of  POSIX and  therefore  no official
@@cancellation point
[[cp]]
int innetgr(char const *netgroup,
            char const *host,
            char const *user,
            char const *domain);

@@Reentrant version of `getnetgrent' where result is placed in `buf'.
@@This  function  is  not part  of  POSIX and  therefore  no official
@@cancellation point
[[cp, decl_include("<hybrid/typecore.h>")]]
int getnetgrent_r(char **__restrict hostp,
                  char **__restrict userp,
                  char **__restrict domainp,
                  char *__restrict buf,
                  size_t buflen);
%#endif /* __USE_MISC */

%
%#ifdef __USE_MISC
@@Call `rshd' at port `rport' on remote machine `*ahost' to execute `cmd'.
@@The  local  user is  `locuser',  on the  remote  machine the  command is
@@executed as `remuser'. In `*fd2p' the  descriptor to the socket for  the
@@connection is  returned.  The  caller  must have  the  right  to  use  a
@@reserved  port.  When  the   function  returns  `*ahost'  contains   the
@@official host name.
@@This function is not part of POSIX and therefore no official
@@cancellation point
[[cp, guard, decl_include("<hybrid/typecore.h>")]]
int rcmd(char **__restrict ahost, $uint16_t rport,
         char const *__restrict locuser,
         char const *__restrict remuser,
         char const *__restrict cmd,
         int *__restrict fd2p);

@@This is the equivalent function where the protocol can be selected
@@and which therefore can be used for IPv6.
@@This function is not part of POSIX and therefore no official
@@cancellation point
[[cp, guard, decl_include("<hybrid/typecore.h>")]]
int rcmd_af(char **__restrict ahost, $uint16_t rport,
            char const *__restrict locuser,
            char const *__restrict remuser,
            char const *__restrict cmd,
            int *__restrict fd2p, sa_family_t af);

@@Call  `rexecd' at port  `rport' on remote  machine `*ahost' to execute
@@`cmd'. The process  runs at the  remote machine using  the ID of  user
@@`name' whose cleartext password is `passwd'. In `*fd2p' the descriptor
@@to  the  socket  for the  connection  is returned.  When  the function
@@returns    `*ahost'     contains    the     official    host     name.
@@This  function  is  not  part  of  POSIX  and  therefore  no  official
@@cancellation point
[[cp]]
int rexec(char **__restrict ahost, int rport,
          char const *__restrict name,
          char const *__restrict pass,
          char const *__restrict cmd,
          int *__restrict fd2p);

@@This is the equivalent function where the protocol can be selected
@@and which therefore can be used for IPv6.
@@This function is not part of POSIX and therefore no official
@@cancellation point
[[cp, guard, decl_include("<hybrid/typecore.h>")]]
int rexec_af(char **__restrict ahost, int rport,
             char const *__restrict name,
             char const *__restrict pass,
             char const *__restrict cmd,
             int *__restrict fd2p,
             $sa_family_t af);

@@Check whether user `remuser' on system `rhost' is allowed to login
@@as `locuser'. If  `suser' is  not zero  the user  tries to  become
@@superuser. Return 0 if it is possible.
@@This function is not part of POSIX and therefore no official
@@cancellation point
[[cp, guard]]
int ruserok(char const *rhost, int suser,
            char const *remuser,
            char const *locuser);

@@This is the equivalent function where the protocol can be selected
@@and which therefore can be used for IPv6.
@@This function is not part of POSIX and therefore no official
@@cancellation point
[[cp, decl_include("<hybrid/typecore.h>")]]
int ruserok_af(char const *rhost, int suser,
               char const *remuser,
               char const *locuser,
               sa_family_t af);

@@Check whether user  `remuser' on system  indicated by IPv4  address
@@`raddr' is allowed to login as `locuser'. Non-IPv4 (e.g., IPv6) are
@@not supported. If  `suser' is  not zero  the user  tries to  become
@@superuser. Return 0 if it is possible.
@@This function is not part of POSIX and therefore no official
@@cancellation point
[[cp, decl_include("<hybrid/typecore.h>")]]
int iruserok(uint32_t raddr, int suser,
             char const *remuser,
             char const *locuser);

@@This is the equivalent function where the family is the address
@@pointed  to by `raddr'  is determined by the  value of `af'. It
@@therefore can be used for IPv6
@@This function is not part of POSIX and therefore no official
@@cancellation point
[[cp, decl_include("<hybrid/typecore.h>")]]
int iruserok_af(void const *raddr, int suser,
                char const *remuser,
                char const *locuser,
                sa_family_t af);

@@Try to allocate reserved port, returning a descriptor for a socket opened
@@at this port  or -1  if unsuccessful. The  search for  an available  port
@@will   start   at   `alport'   and   continues   with   lower    numbers.
@@This   function  is  not   part  of  POSIX   and  therefore  no  official
@@cancellation point
[[cp, guard]]
int rresvport(int *alport);

@@This is the equivalent function where the protocol can be selected
@@and which therefore can be used for IPv6.
@@This function is not part of POSIX and therefore no official
@@cancellation point
[[cp, guard, decl_include("<hybrid/typecore.h>")]]
int rresvport_af(int *alport, $sa_family_t af);
%#endif /* __USE_MISC */


%
%/* Extension from POSIX.1:2001. */
%#ifdef __USE_XOPEN2K
@@Translate name of a service location and/or a service name to set of socket addresses
[[cp]]
int getaddrinfo(char const *__restrict name,
                char const *__restrict service,
                struct addrinfo const *__restrict req,
                struct addrinfo **__restrict pai);

@@Free `addrinfo' structure `ai' including associated storage
void freeaddrinfo(struct addrinfo *ai);

@@Convert error return from getaddrinfo() to a string
[[const, wunused, nothrow]]
char const *gai_strerror(int ecode);

@@Translate a socket address to a location and service name
[[cp, decl_include("<bits/types.h>", "<bits/os/sockaddr.h>")]]
int getnameinfo(struct sockaddr const *__restrict sa, socklen_t salen,
                char *__restrict host, socklen_t hostlen,
                char *__restrict serv, socklen_t servlen,
                int flags);
%#endif /* __USE_XOPEN2K */

%
%#ifdef __USE_GNU

%{
#ifndef __sigevent_t_defined
#define __sigevent_t_defined
typedef struct sigevent sigevent_t;
#endif /* !__sigevent_t_defined */
}


@@Enqueue `ent' requests from the `list'. If `mode' is GAI_WAIT wait until all
@@requests  are  handled. If  `wait'  is GAI_NOWAIT  return  immediately after
@@queueing  the   requests  and   signal   completion  according   to   `sig'.
@@This   function   is  not   part  of   POSIX   and  therefore   no  official
@@cancellation point
[[cp, decl_include("<bits/os/sigevent.h>")]]
int getaddrinfo_a(int mode,
                  struct gaicb *list[__restrict_arr], int ent,
                  struct sigevent *__restrict sig);

@@Suspend execution of the thread until at least one of the `ent'  requests
@@in `list' is handled. If `timeout' is not a null pointer it specifies the
@@longest time the function keeps  waiting before returning with an  error.
@@This   function  is  not   part  of  POSIX   and  therefore  no  official
@@cancellation point
[[cp, no_crt_self_import, decl_include("<bits/os/timespec.h>")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("gai_suspend")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("gai_suspend64")]]
[[userimpl, requires($has_function(gai_suspend64) || $has_function(gai_suspend32))]]
int gai_suspend(struct gaicb const *const list[],
                int ent, struct timespec const *timeout) {
@@pp_if $has_function(gai_suspend32)@@
	struct timespec32 tmo32;
	if (!timeout)
		return gai_suspend32(list, ent, NULL);
	tmo32.tv_sec  = (time32_t)timeout->tv_sec;
	tmo32.tv_nsec = timeout->tv_nsec;
	return gai_suspend32(list, ent, &tmo32);
@@pp_else@@
	struct timespec64 tmo64;
	if (!timeout)
		return gai_suspend64(list, ent, NULL);
	tmo64.tv_sec  = (time64_t)timeout->tv_sec;
	tmo64.tv_nsec = timeout->tv_nsec;
	return gai_suspend64(list, ent, &tmo64);
@@pp_endif@@
}

%
%#ifdef __USE_TIME64
[[cp, doc_alias("gai_suspend"), ignore, nocrt, alias("gai_suspend"), decl_include("<bits/os/timespec.h>")]]
int gai_suspend32(struct gaicb const *const list[],
                  int ent, struct $timespec32 const *timeout);

[[cp, preferred_time64_variant_of(gai_suspend), doc_alias("gai_suspend")]]
[[userimpl, requires_function(gai_suspend32), decl_include("<bits/os/timespec.h>")]]
int gai_suspend64(struct gaicb const *const list[],
                  int ent, struct timespec64 const *timeout) {
	struct timespec32 tmo32;
	if (!timeout)
		return gai_suspend32(list, ent, NULL);
	tmo32.tv_sec  = (time32_t)timeout->tv_sec;
	tmo32.tv_nsec = timeout->tv_nsec;
	return gai_suspend32(list, ent, &tmo32);
}
%#endif /* __USE_TIME64 */

@@Get the error status of the request `req'
int gai_error(struct gaicb *req);

@@Cancel the requests associated with `gaicbp'
int gai_cancel(struct gaicb *gaicbp);
%#endif /* __USE_GNU */



%{

#endif /* __CC__ */

__SYSDECL_END

}
