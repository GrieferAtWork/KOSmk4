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
%[define_decl_include("<bits/crt/db/hostent.h>": ["struct hostent"])]
%[define_decl_include("<bits/crt/db/servent.h>": ["struct servent"])]
%[define_decl_include("<bits/crt/db/protoent.h>": ["struct protoent"])]
%[define_decl_include("<bits/crt/addrinfo.h>": ["struct addrinfo"])]
%[define_decl_include("<bits/crt/gaicb.h>": ["struct gaicb"])]



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
#include <asm/crt/netdb.h>
)]%[insert:prefix(
#include <bits/crt/db/netdb.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <netinet/in.h>
)]%{

#include <bits/crt/db/hostent.h>
#include <bits/crt/db/servent.h>
#include <bits/crt/db/protoent.h>
#ifdef __USE_XOPEN2K
#include <bits/crt/addrinfo.h>
#ifdef __USE_GNU
#include <bits/crt/gaicb.h>
#endif /* __USE_GNU */
#endif /* __USE_XOPEN2K */

#ifdef __USE_MISC
#include <rpc/netdb.h>
#endif /* __USE_MISC */

#ifdef __USE_GNU
#include <bits/os/sigevent.h> /* struct sigevent */
#include <bits/os/timespec.h> /* struct timespec */
#endif /* __USE_GNU */

#ifdef __USE_GLIBC_BLOAT
#include <stdint.h>
#endif /* __USE_GLIBC_BLOAT */

/* Paths for network configuration files. */
#if !defined(_PATH_HEQUIV) && defined(__PATH_HEQUIV)
#define _PATH_HEQUIV __PATH_HEQUIV /* `/etc/hosts.equiv' */
#endif /* !_PATH_HEQUIV && __PATH_HEQUIV */
#if !defined(_PATH_HOSTS) && defined(__PATH_HOSTS)
#define _PATH_HOSTS __PATH_HOSTS /* `/etc/hosts' */
#endif /* !_PATH_HOSTS && __PATH_HOSTS */
#if !defined(_PATH_NETWORKS) && defined(__PATH_NETWORKS)
#define _PATH_NETWORKS __PATH_NETWORKS /* `/etc/networks' */
#endif /* !_PATH_NETWORKS && __PATH_NETWORKS */
#if !defined(_PATH_NSSWITCH_CONF) && defined(__PATH_NSSWITCH_CONF)
#define _PATH_NSSWITCH_CONF __PATH_NSSWITCH_CONF /* `/etc/nsswitch.conf' */
#endif /* !_PATH_NSSWITCH_CONF && __PATH_NSSWITCH_CONF */
#if !defined(_PATH_PROTOCOLS) && defined(__PATH_PROTOCOLS)
#define _PATH_PROTOCOLS __PATH_PROTOCOLS /* `/etc/protocols' */
#endif /* !_PATH_PROTOCOLS && __PATH_PROTOCOLS */
#if !defined(_PATH_SERVICES) && defined(__PATH_SERVICES)
#define _PATH_SERVICES __PATH_SERVICES /* `/etc/services' */
#endif /* !_PATH_SERVICES && __PATH_SERVICES */


#if defined(__USE_MISC) || !defined(__USE_XOPEN2K8)
/* Possible values for `h_errno'. */
#if !defined(HOST_NOT_FOUND) && defined(__ENETDB_HOST_NOT_FOUND)
#define HOST_NOT_FOUND  __ENETDB_HOST_NOT_FOUND /* ??? */
#endif /* !HOST_NOT_FOUND && __ENETDB_HOST_NOT_FOUND */
#if !defined(TRY_AGAIN) && defined(__ENETDB_TRY_AGAIN)
#define TRY_AGAIN       __ENETDB_TRY_AGAIN      /* ??? */
#endif /* !TRY_AGAIN && __ENETDB_TRY_AGAIN */
#if !defined(NO_RECOVERY) && defined(__ENETDB_NO_RECOVERY)
#define NO_RECOVERY     __ENETDB_NO_RECOVERY    /* ??? */
#endif /* !NO_RECOVERY && __ENETDB_NO_RECOVERY */
#if !defined(NO_DATA) && defined(__ENETDB_NO_DATA)
#define NO_DATA         __ENETDB_NO_DATA        /* ??? */
#endif /* !NO_DATA && __ENETDB_NO_DATA */
#endif /* __USE_MISC || !__USE_XOPEN2K8 */

#ifdef __USE_MISC
#if !defined(NETDB_INTERNAL) && defined(__ENETDB_NETDB_INTERNAL)
#define NETDB_INTERNAL  __ENETDB_NETDB_INTERNAL /* s.a. `errno' */
#endif /* !NETDB_INTERNAL && __ENETDB_NETDB_INTERNAL */
#if !defined(NETDB_SUCCESS) && defined(__ENETDB_NETDB_SUCCESS)
#define NETDB_SUCCESS   __ENETDB_NETDB_SUCCESS  /* Success */
#endif /* !NETDB_SUCCESS && __ENETDB_NETDB_SUCCESS */
#if !defined(NO_ADDRESS) && defined(__ENETDB_NO_DATA)
#define NO_ADDRESS      __ENETDB_NO_DATA        /* ??? */
#endif /* !NO_ADDRESS && __ENETDB_NO_DATA */
#endif /* __USE_MISC */

#if defined(__USE_XOPEN2K) || defined(__USE_XOPEN_EXTENDED)
#ifndef IPPORT_RESERVED
#define IPPORT_RESERVED 1024 /* Greatest reserved port */
#endif /* !IPPORT_RESERVED */
#endif /* __USE_XOPEN2K || __USE_XOPEN_EXTENDED */

#ifdef __USE_GNU
#ifndef SCOPE_DELIMITER
#define SCOPE_DELIMITER  '%' /* ??? */
#endif /* !SCOPE_DELIMITER */
#endif /* __USE_GNU */


#ifdef __USE_XOPEN2K
#ifdef __USE_GNU
/* Possible values for `getaddrinfo_a(3)::mode' */
#if !defined(GAI_WAIT) && defined(__GAI_WAIT)
#define GAI_WAIT   __GAI_WAIT
#endif /* !GAI_WAIT && __GAI_WAIT */
#if !defined(GAI_NOWAIT) && defined(__GAI_NOWAIT)
#define GAI_NOWAIT __GAI_NOWAIT
#endif /* !GAI_NOWAIT && __GAI_NOWAIT */
#endif /* __USE_GNU */

/* Flags for `struct addrinfo::ai_flags' */
#if !defined(AI_PASSIVE) && defined(__AI_PASSIVE)
#define AI_PASSIVE __AI_PASSIVE /* ??? */
#endif /* !AI_PASSIVE && __AI_PASSIVE */
#if !defined(AI_CANONNAME) && defined(__AI_CANONNAME)
#define AI_CANONNAME __AI_CANONNAME /* ??? */
#endif /* !AI_CANONNAME && __AI_CANONNAME */
#if !defined(AI_NUMERICHOST) && defined(__AI_NUMERICHOST)
#define AI_NUMERICHOST __AI_NUMERICHOST /* ??? */
#endif /* !AI_NUMERICHOST && __AI_NUMERICHOST */
#if !defined(AI_V4MAPPED) && defined(__AI_V4MAPPED)
#define AI_V4MAPPED __AI_V4MAPPED /* ??? */
#endif /* !AI_V4MAPPED && __AI_V4MAPPED */
#if !defined(AI_ALL) && defined(__AI_ALL)
#define AI_ALL __AI_ALL /* ??? */
#endif /* !AI_ALL && __AI_ALL */
#if !defined(AI_ADDRCONFIG) && defined(__AI_ADDRCONFIG)
#define AI_ADDRCONFIG __AI_ADDRCONFIG /* ??? */
#endif /* !AI_ADDRCONFIG && __AI_ADDRCONFIG */
#ifdef __USE_GNU
#if !defined(AI_IDN) && defined(__AI_IDN)
#define AI_IDN __AI_IDN /* ??? */
#endif /* !AI_IDN && __AI_IDN */
#if !defined(AI_CANONIDN) && defined(__AI_CANONIDN)
#define AI_CANONIDN __AI_CANONIDN /* ??? */
#endif /* !AI_CANONIDN && __AI_CANONIDN */
#if !defined(AI_IDN_ALLOW_UNASSIGNED) && defined(__AI_IDN_ALLOW_UNASSIGNED)
#define AI_IDN_ALLOW_UNASSIGNED __AI_IDN_ALLOW_UNASSIGNED /* ??? */
#endif /* !AI_IDN_ALLOW_UNASSIGNED && __AI_IDN_ALLOW_UNASSIGNED */
#if !defined(AI_IDN_USE_STD3_ASCII_RULES) && defined(__AI_IDN_USE_STD3_ASCII_RULES)
#define AI_IDN_USE_STD3_ASCII_RULES __AI_IDN_USE_STD3_ASCII_RULES /* ??? */
#endif /* !AI_IDN_USE_STD3_ASCII_RULES && __AI_IDN_USE_STD3_ASCII_RULES */
#endif /* __USE_GNU */
#if !defined(AI_NUMERICSERV) && defined(__AI_NUMERICSERV)
#define AI_NUMERICSERV __AI_NUMERICSERV /* ??? */
#endif /* !AI_NUMERICSERV && __AI_NUMERICSERV */

/* Error values for `getaddrinfo' function. */
#if !defined(EAI_BADFLAGS) && defined(__EAI_BADFLAGS)
#define EAI_BADFLAGS __EAI_BADFLAGS /* ??? */
#endif /* !EAI_BADFLAGS && __EAI_BADFLAGS */
#if !defined(EAI_NONAME) && defined(__EAI_NONAME)
#define EAI_NONAME __EAI_NONAME /* ??? */
#endif /* !EAI_NONAME && __EAI_NONAME */
#if !defined(EAI_AGAIN) && defined(__EAI_AGAIN)
#define EAI_AGAIN __EAI_AGAIN /* ??? */
#endif /* !EAI_AGAIN && __EAI_AGAIN */
#if !defined(EAI_FAIL) && defined(__EAI_FAIL)
#define EAI_FAIL __EAI_FAIL /* ??? */
#endif /* !EAI_FAIL && __EAI_FAIL */
#if !defined(EAI_FAMILY) && defined(__EAI_FAMILY)
#define EAI_FAMILY __EAI_FAMILY /* ??? */
#endif /* !EAI_FAMILY && __EAI_FAMILY */
#if !defined(EAI_SOCKTYPE) && defined(__EAI_SOCKTYPE)
#define EAI_SOCKTYPE __EAI_SOCKTYPE /* ??? */
#endif /* !EAI_SOCKTYPE && __EAI_SOCKTYPE */
#if !defined(EAI_SERVICE) && defined(__EAI_SERVICE)
#define EAI_SERVICE __EAI_SERVICE /* ??? */
#endif /* !EAI_SERVICE && __EAI_SERVICE */
#if !defined(EAI_MEMORY) && defined(__EAI_MEMORY)
#define EAI_MEMORY __EAI_MEMORY /* ??? */
#endif /* !EAI_MEMORY && __EAI_MEMORY */
#if !defined(EAI_SYSTEM) && defined(__EAI_SYSTEM)
#define EAI_SYSTEM __EAI_SYSTEM /* ??? */
#endif /* !EAI_SYSTEM && __EAI_SYSTEM */
#if !defined(EAI_OVERFLOW) && defined(__EAI_OVERFLOW)
#define EAI_OVERFLOW __EAI_OVERFLOW /* ??? */
#endif /* !EAI_OVERFLOW && __EAI_OVERFLOW */
#ifdef __USE_GNU
#if !defined(EAI_NODATA) && defined(__EAI_NODATA)
#define EAI_NODATA __EAI_NODATA /* ??? */
#endif /* !EAI_NODATA && __EAI_NODATA */
#if !defined(EAI_ADDRFAMILY) && defined(__EAI_ADDRFAMILY)
#define EAI_ADDRFAMILY __EAI_ADDRFAMILY /* ??? */
#endif /* !EAI_ADDRFAMILY && __EAI_ADDRFAMILY */
#if !defined(EAI_INPROGRESS) && defined(__EAI_INPROGRESS)
#define EAI_INPROGRESS __EAI_INPROGRESS /* ??? */
#endif /* !EAI_INPROGRESS && __EAI_INPROGRESS */
#if !defined(EAI_CANCELED) && defined(__EAI_CANCELED)
#define EAI_CANCELED __EAI_CANCELED /* ??? */
#endif /* !EAI_CANCELED && __EAI_CANCELED */
#if !defined(EAI_NOTCANCELED) && defined(__EAI_NOTCANCELED)
#define EAI_NOTCANCELED __EAI_NOTCANCELED /* ??? */
#endif /* !EAI_NOTCANCELED && __EAI_NOTCANCELED */
#if !defined(EAI_ALLDONE) && defined(__EAI_ALLDONE)
#define EAI_ALLDONE __EAI_ALLDONE /* ??? */
#endif /* !EAI_ALLDONE && __EAI_ALLDONE */
#if !defined(EAI_INTR) && defined(__EAI_INTR)
#define EAI_INTR __EAI_INTR /* ??? */
#endif /* !EAI_INTR && __EAI_INTR */
#if !defined(EAI_IDN_ENCODE) && defined(__EAI_IDN_ENCODE)
#define EAI_IDN_ENCODE __EAI_IDN_ENCODE /* ??? */
#endif /* !EAI_IDN_ENCODE && __EAI_IDN_ENCODE */
#endif /* __USE_GNU */

#ifdef __USE_MISC
#if !defined(NI_MAXHOST) && defined(__NI_MAXHOST)
#define NI_MAXHOST __NI_MAXHOST /* Max length for `getnameinfo::host' */
#endif /* !NI_MAXHOST && __NI_MAXHOST */
#if !defined(NI_MAXSERV) && defined(__NI_MAXSERV)
#define NI_MAXSERV __NI_MAXSERV /* Max length for `getnameinfo::serv' */
#endif /* !NI_MAXSERV && __NI_MAXSERV */
#endif /* __USE_MISC */

#if !defined(NI_NUMERICHOST) && defined(__NI_NUMERICHOST)
#define NI_NUMERICHOST __NI_NUMERICHOST /* ??? */
#endif /* !NI_NUMERICHOST && __NI_NUMERICHOST */
#if !defined(NI_NUMERICSERV) && defined(__NI_NUMERICSERV)
#define NI_NUMERICSERV __NI_NUMERICSERV /* ??? */
#endif /* !NI_NUMERICSERV && __NI_NUMERICSERV */
#if !defined(NI_NOFQDN) && defined(__NI_NOFQDN)
#define NI_NOFQDN __NI_NOFQDN /* ??? */
#endif /* !NI_NOFQDN && __NI_NOFQDN */
#if !defined(NI_NAMEREQD) && defined(__NI_NAMEREQD)
#define NI_NAMEREQD __NI_NAMEREQD /* ??? */
#endif /* !NI_NAMEREQD && __NI_NAMEREQD */
#if !defined(NI_DGRAM) && defined(__NI_DGRAM)
#define NI_DGRAM __NI_DGRAM /* ??? */
#endif /* !NI_DGRAM && __NI_DGRAM */
#ifdef __USE_GNU
#if !defined(NI_IDN) && defined(__NI_IDN)
#define NI_IDN __NI_IDN /* ??? */
#endif /* !NI_IDN && __NI_IDN */
#if !defined(NI_IDN_ALLOW_UNASSIGNED) && defined(__NI_IDN_ALLOW_UNASSIGNED)
#define NI_IDN_ALLOW_UNASSIGNED __NI_IDN_ALLOW_UNASSIGNED /* ??? */
#endif /* !NI_IDN_ALLOW_UNASSIGNED && __NI_IDN_ALLOW_UNASSIGNED */
#if !defined(NI_IDN_USE_STD3_ASCII_RULES) && defined(__NI_IDN_USE_STD3_ASCII_RULES)
#define NI_IDN_USE_STD3_ASCII_RULES __NI_IDN_USE_STD3_ASCII_RULES /* ??? */
#endif /* !NI_IDN_USE_STD3_ASCII_RULES && __NI_IDN_USE_STD3_ASCII_RULES */
#endif /* __USE_GNU */
#endif /* __USE_XOPEN2K */



#ifdef __CC__
__SYSDECL_BEGIN

}

[[cp]]
void sethostent(int stay_open);

[[cp_nokos]]
void endhostent();

[[cp, decl_include("<bits/crt/db/hostent.h>")]]
struct hostent *gethostent();

[[cp, decl_include("<bits/types.h>", "<bits/crt/db/hostent.h>")]]
struct hostent *gethostbyaddr(void const *addr, socklen_t len, int type);

[[cp, decl_include("<bits/crt/db/hostent.h>")]]
struct hostent *gethostbyname(char const *name);



[[cp]]
void setnetent(int stay_open);

[[cp_nokos]]
void endnetent();

[[cp, decl_include("<bits/crt/db/netent.h>")]]
struct netent *getnetent();

[[cp, decl_include("<hybrid/typecore.h>", "<bits/crt/db/netent.h>")]]
struct netent *getnetbyaddr(uint32_t net, int type);

[[cp, decl_include("<bits/crt/db/netent.h>")]]
struct netent *getnetbyname(char const *name);



[[cp]]
void setservent(int stay_open);

[[cp_nokos]]
void endservent();

[[cp, decl_include("<bits/crt/db/servent.h>")]]
struct servent *getservent();

[[cp, decl_include("<bits/crt/db/servent.h>")]]
struct servent *getservbyname(char const *name, char const *proto);

[[cp, decl_include("<bits/crt/db/servent.h>")]]
struct servent *getservbyport(int port, char const *proto);



[[cp]]
void setprotoent(int stay_open);

[[cp_nokos]]
void endprotoent();

[[cp, decl_include("<bits/crt/db/protoent.h>")]]
struct protoent *getprotoent();

[[cp, decl_include("<bits/crt/db/protoent.h>")]]
struct protoent *getprotobyname(char const *name);

[[cp, decl_include("<bits/crt/db/protoent.h>")]]
struct protoent *getprotobynumber(int proto);



%
%#if defined(__USE_MISC) || !defined(__USE_XOPEN2K8)
[[guard, const, wunused, nothrow, nonnull]] int *__h_errno_location();

%{
#if !defined(h_errno) && defined(____h_errno_location_defined)
#define h_errno (*__h_errno_location())
#endif /* !h_errno && ____h_errno_location_defined */
}
%#endif /* __USE_MISC || !__USE_XOPEN2K8 */

%
%#ifdef __USE_MISC
@@>> herror(3)
@@Same as `perror(3)' for `errno(3)', print `message' (if non-null),
@@alongside   the  value  of  `hstrerror(h_errno)'  to  `stderr(3)'.
[[cp_stdio]]
void herror([[nullable]] char const *message);

@@>> hstrerror(3)
@@Return error message for `h_error'
[[const, wunused, nothrow]]
char const *hstrerror(int h_error);




[[cp, decl_include("<bits/crt/db/hostent.h>")]]
struct hostent *gethostbyname2(char const *name, int af);

[[cp, decl_include("<hybrid/typecore.h>", "<bits/crt/db/hostent.h>")]]
[[export_as("__gethostent_r")]] /* From Glibc 2.0.4 */
int gethostent_r(struct hostent *__restrict result_buf,
                 char *__restrict buf, size_t buflen,
                 struct hostent **__restrict result,
                 int *__restrict h_errnop);

[[cp, doc_alias("gethostent_r"), decl_include("<bits/types.h>", "<bits/crt/db/hostent.h>")]]
[[export_as("__gethostbyaddr_r")]] /* From Glibc 2.0.4 */
int gethostbyaddr_r(void const *__restrict addr, socklen_t len, int type,
                    struct hostent *__restrict result_buf,
                    char *__restrict buf, size_t buflen,
                    struct hostent **__restrict result,
                    int *__restrict h_errnop);

[[cp, doc_alias("gethostent_r"), decl_include("<bits/types.h>", "<bits/crt/db/hostent.h>")]]
[[export_as("__gethostbyname_r")]] /* From Glibc 2.0.4 */
int gethostbyname_r(char const *__restrict name,
                    struct hostent *__restrict result_buf,
                    char *__restrict buf, size_t buflen,
                    struct hostent **__restrict result,
                    int *__restrict h_errnop);

[[cp, doc_alias("gethostent_r"), decl_include("<bits/types.h>", "<bits/crt/db/hostent.h>")]]
[[export_as("__gethostbyname2_r")]] /* From Glibc 2.0.4 */
int gethostbyname2_r(char const *__restrict name, int af,
                     struct hostent *__restrict result_buf,
                     char *__restrict buf, size_t buflen,
                     struct hostent **__restrict result,
                     int *__restrict h_errnop);




[[cp, decl_include("<hybrid/typecore.h>", "<bits/crt/db/netent.h>")]]
[[export_as("__getnetent_r")]] /* From Glibc 2.0.4 */
int getnetent_r(struct netent *__restrict result_buf,
                char *__restrict buf, size_t buflen,
                struct netent **__restrict result,
                int *__restrict h_errnop);

[[cp, doc_alias("getnetent_r"), decl_include("<hybrid/typecore.h>", "<bits/crt/db/netent.h>")]]
[[export_as("__getnetbyaddr_r")]] /* From Glibc 2.0.4 */
int getnetbyaddr_r(uint32_t net, int type,
                   struct netent *__restrict result_buf,
                   char *__restrict buf, size_t buflen,
                   struct netent **__restrict result,
                   int *__restrict h_errnop);

[[cp, doc_alias("getnetent_r"), decl_include("<hybrid/typecore.h>", "<bits/crt/db/netent.h>")]]
[[export_as("__getnetbyname_r")]] /* From Glibc 2.0.4 */
int getnetbyname_r(char const *__restrict name,
                   struct netent *__restrict result_buf,
                   char *__restrict buf, size_t buflen,
                   struct netent **__restrict result,
                   int *__restrict h_errnop);




[[cp, decl_include("<hybrid/typecore.h>", "<bits/crt/db/servent.h>")]]
[[export_as("__getservent_r")]] /* From Glibc 2.0.4 */
int getservent_r(struct servent *__restrict result_buf,
                 char *__restrict buf, size_t buflen,
                 struct servent **__restrict result);

[[cp, doc_alias("getservent_r"), decl_include("<hybrid/typecore.h>", "<bits/crt/db/servent.h>")]]
[[export_as("__getservbyname_r")]] /* From Glibc 2.0.4 */
int getservbyname_r(char const *__restrict name,
                    char const *__restrict proto,
                    struct servent *__restrict result_buf,
                    char *__restrict buf, size_t buflen,
                    struct servent **__restrict result);

[[cp, doc_alias("getservent_r"), decl_include("<hybrid/typecore.h>", "<bits/crt/db/servent.h>")]]
[[export_as("__getservbyport_r")]] /* From Glibc 2.0.4 */
int getservbyport_r(int port, char const *__restrict proto,
                    struct servent *__restrict result_buf,
                    char *__restrict buf, size_t buflen,
                    struct servent **__restrict result);




[[cp, decl_include("<hybrid/typecore.h>", "<bits/crt/db/protoent.h>")]]
[[export_as("__getprotoent_r")]] /* From Glibc 2.0.4 */
int getprotoent_r(struct protoent *__restrict result_buf,
                  char *__restrict buf, size_t buflen,
                  struct protoent **__restrict result);

[[cp, doc_alias("getprotoent_r"), decl_include("<hybrid/typecore.h>", "<bits/crt/db/protoent.h>")]]
[[export_as("__getprotobyname_r")]] /* From Glibc 2.0.4 */
int getprotobyname_r(char const *__restrict name,
                     struct protoent *__restrict result_buf,
                     char *__restrict buf, size_t buflen,
                     struct protoent **__restrict result);

[[cp, doc_alias("getprotoent_r")]]
[[decl_include("<hybrid/typecore.h>", "<bits/crt/db/protoent.h>")]]
[[export_as("__getprotobynumber_r")]] /* From Glibc 2.0.4 */
int getprotobynumber_r(int proto,
                       struct protoent *__restrict result_buf,
                       char *__restrict buf, size_t buflen,
                       struct protoent **__restrict result);



[[cp]]
int setnetgrent(char const *netgroup);

[[cp_nokos]]
void endnetgrent();

[[cp]]
int getnetgrent(char **__restrict hostp,
                char **__restrict userp,
                char **__restrict domainp);

[[cp]]
int innetgr(char const *netgroup,
            char const *host,
            char const *user,
            char const *domain);

[[cp, decl_include("<hybrid/typecore.h>")]]
[[export_as("__getnetgrent_r")]] /* From Glibc 2.0.4 */
int getnetgrent_r(char **__restrict hostp,
                  char **__restrict userp,
                  char **__restrict domainp,
                  char *__restrict buf,
                  size_t buflen);




[[cp, guard, decl_include("<hybrid/typecore.h>")]]
int rcmd(char **__restrict ahost, $uint16_t rport,
         char const *__restrict locuser,
         char const *__restrict remuser,
         char const *__restrict cmd,
         int *__restrict fd2p);

[[cp, guard, decl_include("<bits/types.h>")]]
int rcmd_af(char **__restrict ahost, $uint16_t rport,
            char const *__restrict locuser,
            char const *__restrict remuser,
            char const *__restrict cmd,
            int *__restrict fd2p, sa_family_t af);

[[cp]]
int rexec(char **__restrict ahost, int rport,
          char const *__restrict name,
          char const *__restrict pass,
          char const *__restrict cmd,
          int *__restrict fd2p);

[[cp, guard, decl_include("<bits/types.h>")]]
int rexec_af(char **__restrict ahost, int rport,
             char const *__restrict name,
             char const *__restrict pass,
             char const *__restrict cmd,
             int *__restrict fd2p,
             $sa_family_t af);

[[cp, guard]]
int ruserok(char const *rhost, int suser,
            char const *remuser,
            char const *locuser);

[[cp, decl_include("<bits/types.h>")]]
int ruserok_af(char const *rhost, int suser,
               char const *remuser,
               char const *locuser,
               sa_family_t af);

[[cp, decl_include("<hybrid/typecore.h>")]]
int iruserok(uint32_t raddr, int suser,
             char const *remuser,
             char const *locuser);

[[cp, decl_include("<bits/types.h>")]]
int iruserok_af(void const *raddr, int suser,
                char const *remuser,
                char const *locuser,
                sa_family_t af);

[[cp, guard]]
int rresvport(int *alport);

[[cp, guard, decl_include("<hybrid/typecore.h>")]]
int rresvport_af(int *alport, $sa_family_t af);
%#endif /* __USE_MISC */



%
%#ifdef __USE_XOPEN2K
[[cp]]
[[decl_include("<bits/crt/addrinfo.h>")]]
int getaddrinfo(char const *__restrict name,
                char const *__restrict service,
                struct addrinfo const *__restrict req,
                struct addrinfo **__restrict pai);

[[decl_include("<bits/crt/addrinfo.h>")]]
void freeaddrinfo(struct addrinfo *ai);

[[const, wunused, nothrow]]
char const *gai_strerror(int ecode);

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


[[cp, decl_include("<bits/os/sigevent.h>")]]
[[decl_include("<bits/crt/gaicb.h>")]]
int getaddrinfo_a(int mode,
                  struct gaicb *list[__restrict_arr], int ent,
                  struct sigevent *__restrict sig);

[[decl_include("<bits/crt/gaicb.h>")]]
int gai_error(struct gaicb *req);

[[decl_include("<bits/crt/gaicb.h>")]]
int gai_cancel(struct gaicb *gaicbp);

[[cp, no_crt_self_import, decl_include("<bits/crt/gaicb.h>", "<bits/os/timespec.h>")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("gai_suspend")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("gai_suspend64", "__gai_suspend_time64")]]
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
[[cp, doc_alias("gai_suspend"), ignore, nocrt, alias("gai_suspend")]]
[[decl_include("<bits/crt/gaicb.h>", "<bits/os/timespec.h>")]]
int gai_suspend32(struct gaicb const *const list[],
                  int ent, struct $timespec32 const *timeout);

[[cp, preferred_time64_variant_of(gai_suspend), doc_alias("gai_suspend")]]
[[time64_export_alias("__gai_suspend_time64")]]
[[userimpl, requires_function(gai_suspend32), decl_include("<bits/crt/gaicb.h>", "<bits/os/timespec.h>")]]
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
%#endif /* __USE_GNU */



%{

__SYSDECL_END
#endif /* __CC__ */

}
