/* HASH CRC-32:0x618f41b7 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
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
#ifndef _NETDB_H
#define _NETDB_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/crt/netdb.h>
#include <bits/crt/db/netdb.h>
#include <bits/types.h>
#include <netinet/in.h>

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

__CDECLARE_VOID_OPT(,__NOTHROW_RPC,sethostent,(int __stay_open),(__stay_open))
__CDECLARE_VOID_OPT(,__NOTHROW_RPC_NOKOS,endhostent,(void),())
__CDECLARE_OPT(,struct hostent *,__NOTHROW_RPC,gethostent,(void),())
__CDECLARE_OPT(,struct hostent *,__NOTHROW_RPC,gethostbyaddr,(void const *__addr, socklen_t __len, int __type),(__addr,__len,__type))
__CDECLARE_OPT(,struct hostent *,__NOTHROW_RPC,gethostbyname,(char const *__name),(__name))
__CDECLARE_VOID_OPT(,__NOTHROW_RPC,setnetent,(int __stay_open),(__stay_open))
__CDECLARE_VOID_OPT(,__NOTHROW_RPC_NOKOS,endnetent,(void),())
__CDECLARE_OPT(,struct netent *,__NOTHROW_RPC,getnetent,(void),())
__CDECLARE_OPT(,struct netent *,__NOTHROW_RPC,getnetbyaddr,(uint32_t __net, int __type),(__net,__type))
__CDECLARE_OPT(,struct netent *,__NOTHROW_RPC,getnetbyname,(char const *__name),(__name))
__CDECLARE_VOID_OPT(,__NOTHROW_RPC,setservent,(int __stay_open),(__stay_open))
__CDECLARE_VOID_OPT(,__NOTHROW_RPC_NOKOS,endservent,(void),())
__CDECLARE_OPT(,struct servent *,__NOTHROW_RPC,getservent,(void),())
__CDECLARE_OPT(,struct servent *,__NOTHROW_RPC,getservbyname,(char const *__name, char const *__proto),(__name,__proto))
__CDECLARE_OPT(,struct servent *,__NOTHROW_RPC,getservbyport,(int __port, char const *__proto),(__port,__proto))
__CDECLARE_VOID_OPT(,__NOTHROW_RPC,setprotoent,(int __stay_open),(__stay_open))
__CDECLARE_VOID_OPT(,__NOTHROW_RPC_NOKOS,endprotoent,(void),())
__CDECLARE_OPT(,struct protoent *,__NOTHROW_RPC,getprotoent,(void),())
__CDECLARE_OPT(,struct protoent *,__NOTHROW_RPC,getprotobyname,(char const *__name),(__name))
__CDECLARE_OPT(,struct protoent *,__NOTHROW_RPC,getprotobynumber,(int __proto),(__proto))

#if defined(__USE_MISC) || !defined(__USE_XOPEN2K8)
#if !defined(____h_errno_location_defined) && defined(__CRT_HAVE___h_errno_location)
#define ____h_errno_location_defined
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,int *,__NOTHROW,__h_errno_location,(void),())
#endif /* !____h_errno_location_defined && __CRT_HAVE___h_errno_location */
#if !defined(h_errno) && defined(____h_errno_location_defined)
#define h_errno (*__h_errno_location())
#endif /* !h_errno && ____h_errno_location_defined */
#endif /* __USE_MISC || !__USE_XOPEN2K8 */

#ifdef __USE_MISC
/* >> herror(3)
 * Same as `perror(3)' for `errno(3)', print `message' (if non-null),
 * alongside   the  value  of  `hstrerror(h_errno)'  to  `stderr(3)'. */
__CDECLARE_VOID_OPT(,__NOTHROW_CB_NCX,herror,(char const *__message),(__message))
/* >> hstrerror(3)
 * Return error message for `h_error' */
__CDECLARE_OPT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,hstrerror,(int __h_error),(__h_error))
__CDECLARE_OPT(,struct hostent *,__NOTHROW_RPC,gethostbyname2,(char const *__name, int __af),(__name,__af))
__CDECLARE_OPT(,int,__NOTHROW_RPC,gethostent_r,(struct hostent *__restrict __result_buf, char *__restrict __buf, size_t __buflen, struct hostent **__restrict __result, int *__restrict __h_errnop),(__result_buf,__buf,__buflen,__result,__h_errnop))
__CDECLARE_OPT(,int,__NOTHROW_RPC,gethostbyaddr_r,(void const *__restrict __addr, socklen_t __len, int __type, struct hostent *__restrict __result_buf, char *__restrict __buf, size_t __buflen, struct hostent **__restrict __result, int *__restrict __h_errnop),(__addr,__len,__type,__result_buf,__buf,__buflen,__result,__h_errnop))
__CDECLARE_OPT(,int,__NOTHROW_RPC,gethostbyname_r,(char const *__restrict __name, struct hostent *__restrict __result_buf, char *__restrict __buf, size_t __buflen, struct hostent **__restrict __result, int *__restrict __h_errnop),(__name,__result_buf,__buf,__buflen,__result,__h_errnop))
__CDECLARE_OPT(,int,__NOTHROW_RPC,gethostbyname2_r,(char const *__restrict __name, int __af, struct hostent *__restrict __result_buf, char *__restrict __buf, size_t __buflen, struct hostent **__restrict __result, int *__restrict __h_errnop),(__name,__af,__result_buf,__buf,__buflen,__result,__h_errnop))
__CDECLARE_OPT(,int,__NOTHROW_RPC,getnetent_r,(struct netent *__restrict __result_buf, char *__restrict __buf, size_t __buflen, struct netent **__restrict __result, int *__restrict __h_errnop),(__result_buf,__buf,__buflen,__result,__h_errnop))
__CDECLARE_OPT(,int,__NOTHROW_RPC,getnetbyaddr_r,(uint32_t __net, int __type, struct netent *__restrict __result_buf, char *__restrict __buf, size_t __buflen, struct netent **__restrict __result, int *__restrict __h_errnop),(__net,__type,__result_buf,__buf,__buflen,__result,__h_errnop))
__CDECLARE_OPT(,int,__NOTHROW_RPC,getnetbyname_r,(char const *__restrict __name, struct netent *__restrict __result_buf, char *__restrict __buf, size_t __buflen, struct netent **__restrict __result, int *__restrict __h_errnop),(__name,__result_buf,__buf,__buflen,__result,__h_errnop))
__CDECLARE_OPT(,int,__NOTHROW_RPC,getservent_r,(struct servent *__restrict __result_buf, char *__restrict __buf, size_t __buflen, struct servent **__restrict __result),(__result_buf,__buf,__buflen,__result))
__CDECLARE_OPT(,int,__NOTHROW_RPC,getservbyname_r,(char const *__restrict __name, char const *__restrict __proto, struct servent *__restrict __result_buf, char *__restrict __buf, size_t __buflen, struct servent **__restrict __result),(__name,__proto,__result_buf,__buf,__buflen,__result))
__CDECLARE_OPT(,int,__NOTHROW_RPC,getservbyport_r,(int __port, char const *__restrict __proto, struct servent *__restrict __result_buf, char *__restrict __buf, size_t __buflen, struct servent **__restrict __result),(__port,__proto,__result_buf,__buf,__buflen,__result))
__CDECLARE_OPT(,int,__NOTHROW_RPC,getprotoent_r,(struct protoent *__restrict __result_buf, char *__restrict __buf, size_t __buflen, struct protoent **__restrict __result),(__result_buf,__buf,__buflen,__result))
__CDECLARE_OPT(,int,__NOTHROW_RPC,getprotobyname_r,(char const *__restrict __name, struct protoent *__restrict __result_buf, char *__restrict __buf, size_t __buflen, struct protoent **__restrict __result),(__name,__result_buf,__buf,__buflen,__result))
__CDECLARE_OPT(,int,__NOTHROW_RPC,getprotobynumber_r,(int __proto, struct protoent *__restrict __result_buf, char *__restrict __buf, size_t __buflen, struct protoent **__restrict __result),(__proto,__result_buf,__buf,__buflen,__result))
__CDECLARE_OPT(,int,__NOTHROW_RPC,setnetgrent,(char const *__netgroup),(__netgroup))
__CDECLARE_VOID_OPT(,__NOTHROW_RPC_NOKOS,endnetgrent,(void),())
__CDECLARE_OPT(,int,__NOTHROW_RPC,getnetgrent,(char **__restrict __hostp, char **__restrict __userp, char **__restrict __domainp),(__hostp,__userp,__domainp))
__CDECLARE_OPT(,int,__NOTHROW_RPC,innetgr,(char const *__netgroup, char const *__host, char const *__user, char const *__domain),(__netgroup,__host,__user,__domain))
__CDECLARE_OPT(,int,__NOTHROW_RPC,getnetgrent_r,(char **__restrict __hostp, char **__restrict __userp, char **__restrict __domainp, char *__restrict __buf, size_t __buflen),(__hostp,__userp,__domainp,__buf,__buflen))
#if !defined(__rcmd_defined) && defined(__CRT_HAVE_rcmd)
#define __rcmd_defined
__CDECLARE(,int,__NOTHROW_RPC,rcmd,(char **__restrict __ahost, __UINT16_TYPE__ __rport, char const *__restrict __locuser, char const *__restrict __remuser, char const *__restrict __cmd, int *__restrict __fd2p),(__ahost,__rport,__locuser,__remuser,__cmd,__fd2p))
#endif /* !__rcmd_defined && __CRT_HAVE_rcmd */
#if !defined(__rcmd_af_defined) && defined(__CRT_HAVE_rcmd_af)
#define __rcmd_af_defined
__CDECLARE(,int,__NOTHROW_RPC,rcmd_af,(char **__restrict __ahost, __UINT16_TYPE__ __rport, char const *__restrict __locuser, char const *__restrict __remuser, char const *__restrict __cmd, int *__restrict __fd2p, sa_family_t __af),(__ahost,__rport,__locuser,__remuser,__cmd,__fd2p,__af))
#endif /* !__rcmd_af_defined && __CRT_HAVE_rcmd_af */
__CDECLARE_OPT(,int,__NOTHROW_RPC,rexec,(char **__restrict __ahost, int __rport, char const *__restrict __name, char const *__restrict __pass, char const *__restrict __cmd, int *__restrict __fd2p),(__ahost,__rport,__name,__pass,__cmd,__fd2p))
#if !defined(__rexec_af_defined) && defined(__CRT_HAVE_rexec_af)
#define __rexec_af_defined
__CDECLARE(,int,__NOTHROW_RPC,rexec_af,(char **__restrict __ahost, int __rport, char const *__restrict __name, char const *__restrict __pass, char const *__restrict __cmd, int *__restrict __fd2p, __UINT16_TYPE__ __af),(__ahost,__rport,__name,__pass,__cmd,__fd2p,__af))
#endif /* !__rexec_af_defined && __CRT_HAVE_rexec_af */
#if !defined(__ruserok_defined) && defined(__CRT_HAVE_ruserok)
#define __ruserok_defined
__CDECLARE(,int,__NOTHROW_RPC,ruserok,(char const *__rhost, int __suser, char const *__remuser, char const *__locuser),(__rhost,__suser,__remuser,__locuser))
#endif /* !__ruserok_defined && __CRT_HAVE_ruserok */
__CDECLARE_OPT(,int,__NOTHROW_RPC,ruserok_af,(char const *__rhost, int __suser, char const *__remuser, char const *__locuser, sa_family_t __af),(__rhost,__suser,__remuser,__locuser,__af))
__CDECLARE_OPT(,int,__NOTHROW_RPC,iruserok,(uint32_t __raddr, int __suser, char const *__remuser, char const *__locuser),(__raddr,__suser,__remuser,__locuser))
__CDECLARE_OPT(,int,__NOTHROW_RPC,iruserok_af,(void const *__raddr, int __suser, char const *__remuser, char const *__locuser, sa_family_t __af),(__raddr,__suser,__remuser,__locuser,__af))
#if !defined(__rresvport_defined) && defined(__CRT_HAVE_rresvport)
#define __rresvport_defined
__CDECLARE(,int,__NOTHROW_RPC,rresvport,(int *__alport),(__alport))
#endif /* !__rresvport_defined && __CRT_HAVE_rresvport */
#if !defined(__rresvport_af_defined) && defined(__CRT_HAVE_rresvport_af)
#define __rresvport_af_defined
__CDECLARE(,int,__NOTHROW_RPC,rresvport_af,(int *__alport, __UINT16_TYPE__ __af),(__alport,__af))
#endif /* !__rresvport_af_defined && __CRT_HAVE_rresvport_af */
#endif /* __USE_MISC */

#ifdef __USE_XOPEN2K
__CDECLARE_OPT(,int,__NOTHROW_RPC,getaddrinfo,(char const *__restrict __name, char const *__restrict __service, struct addrinfo const *__restrict __req, struct addrinfo **__restrict __pai),(__name,__service,__req,__pai))
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,freeaddrinfo,(struct addrinfo *__ai),(__ai))
__CDECLARE_OPT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,gai_strerror,(int __ecode),(__ecode))
__CDECLARE_OPT(,int,__NOTHROW_RPC,getnameinfo,(struct sockaddr const *__restrict __sa, socklen_t __salen, char *__restrict __host, socklen_t __hostlen, char *__restrict __serv, socklen_t __servlen, int __flags),(__sa,__salen,__host,__hostlen,__serv,__servlen,__flags))
#endif /* __USE_XOPEN2K */

#ifdef __USE_GNU
#ifndef __sigevent_t_defined
#define __sigevent_t_defined
typedef struct sigevent sigevent_t;
#endif /* !__sigevent_t_defined */
__CDECLARE_OPT(,int,__NOTHROW_RPC,getaddrinfo_a,(int __mode, struct gaicb *__list[__restrict_arr], int __ent, struct sigevent *__restrict __sig),(__mode,__list,__ent,__sig))
__CDECLARE_OPT(,int,__NOTHROW_NCX,gai_error,(struct gaicb *__req),(__req))
__CDECLARE_OPT(,int,__NOTHROW_NCX,gai_cancel,(struct gaicb *__gaicbp),(__gaicbp))
#if defined(__CRT_HAVE_gai_suspend) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CDECLARE(,int,__NOTHROW_RPC,gai_suspend,(struct gaicb const *const __list[], int __ent, struct timespec const *__timeout),(__list,__ent,__timeout))
#elif defined(__CRT_HAVE_gai_suspend64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(,int,__NOTHROW_RPC,gai_suspend,(struct gaicb const *const __list[], int __ent, struct timespec const *__timeout),gai_suspend64,(__list,__ent,__timeout))
#elif defined(__CRT_HAVE___gai_suspend_time64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(,int,__NOTHROW_RPC,gai_suspend,(struct gaicb const *const __list[], int __ent, struct timespec const *__timeout),__gai_suspend_time64,(__list,__ent,__timeout))
#elif defined(__CRT_HAVE_gai_suspend64) || defined(__CRT_HAVE___gai_suspend_time64) || defined(__CRT_HAVE_gai_suspend)
#include <libc/local/netdb/gai_suspend.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(gai_suspend, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBCCALL gai_suspend)(struct gaicb const *const __list[], int __ent, struct timespec const *__timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gai_suspend))(__list, __ent, __timeout); })
#endif /* ... */

#ifdef __USE_TIME64
#if defined(__CRT_HAVE_gai_suspend) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(,int,__NOTHROW_RPC,gai_suspend64,(struct gaicb const *const __list[], int __ent, struct timespec64 const *__timeout),gai_suspend,(__list,__ent,__timeout))
#elif defined(__CRT_HAVE_gai_suspend64)
__CDECLARE(,int,__NOTHROW_RPC,gai_suspend64,(struct gaicb const *const __list[], int __ent, struct timespec64 const *__timeout),(__list,__ent,__timeout))
#elif defined(__CRT_HAVE___gai_suspend_time64)
__CREDIRECT(,int,__NOTHROW_RPC,gai_suspend64,(struct gaicb const *const __list[], int __ent, struct timespec64 const *__timeout),__gai_suspend_time64,(__list,__ent,__timeout))
#elif defined(__CRT_HAVE_gai_suspend)
#include <libc/local/netdb/gai_suspend64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(gai_suspend64, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBCCALL gai_suspend64)(struct gaicb const *const __list[], int __ent, struct timespec64 const *__timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gai_suspend64))(__list, __ent, __timeout); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_GNU */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_NETDB_H */
