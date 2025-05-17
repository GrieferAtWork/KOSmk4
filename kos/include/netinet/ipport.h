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
#ifndef _NETINET_IPPORT_H
#define _NETINET_IPPORT_H 1

#include <__stdinc.h>

#include <netinet/asm/ipport.h>

/* Documentation taken from Glibc /usr/include/netinet/in.h */
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
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


/* Standard well-known ports. */
#if !defined(IPPORT_ECHO) && defined(__IPPORT_ECHO)
#define IPPORT_ECHO         __IPPORT_ECHO       /* Echo service. */
#endif /* !IPPORT_ECHO && __IPPORT_ECHO */
#if !defined(IPPORT_DISCARD) && defined(__IPPORT_DISCARD)
#define IPPORT_DISCARD      __IPPORT_DISCARD    /* Discard transmissions service. */
#endif /* !IPPORT_DISCARD && __IPPORT_DISCARD */
#if !defined(IPPORT_SYSTAT) && defined(__IPPORT_SYSTAT)
#define IPPORT_SYSTAT       __IPPORT_SYSTAT     /* System status service. */
#endif /* !IPPORT_SYSTAT && __IPPORT_SYSTAT */
#if !defined(IPPORT_DAYTIME) && defined(__IPPORT_DAYTIME)
#define IPPORT_DAYTIME      __IPPORT_DAYTIME    /* Time of day service. */
#endif /* !IPPORT_DAYTIME && __IPPORT_DAYTIME */
#if !defined(IPPORT_NETSTAT) && defined(__IPPORT_NETSTAT)
#define IPPORT_NETSTAT      __IPPORT_NETSTAT    /* Network status service. */
#endif /* !IPPORT_NETSTAT && __IPPORT_NETSTAT */
#if !defined(IPPORT_FTP) && defined(__IPPORT_FTP)
#define IPPORT_FTP          __IPPORT_FTP        /* File Transfer Protocol. */
#endif /* !IPPORT_FTP && __IPPORT_FTP */
#if !defined(IPPORT_TELNET) && defined(__IPPORT_TELNET)
#define IPPORT_TELNET       __IPPORT_TELNET     /* Telnet protocol. */
#endif /* !IPPORT_TELNET && __IPPORT_TELNET */
#if !defined(IPPORT_SMTP) && defined(__IPPORT_SMTP)
#define IPPORT_SMTP         __IPPORT_SMTP       /* Simple Mail Transfer Protocol. */
#endif /* !IPPORT_SMTP && __IPPORT_SMTP */
#if !defined(IPPORT_TIMESERVER) && defined(__IPPORT_TIMESERVER)
#define IPPORT_TIMESERVER   __IPPORT_TIMESERVER /* Timeserver service. */
#endif /* !IPPORT_TIMESERVER && __IPPORT_TIMESERVER */
#if !defined(IPPORT_NAMESERVER) && defined(__IPPORT_NAMESERVER)
#define IPPORT_NAMESERVER   __IPPORT_NAMESERVER /* Domain Name Service. */
#endif /* !IPPORT_NAMESERVER && __IPPORT_NAMESERVER */
#if !defined(IPPORT_WHOIS) && defined(__IPPORT_WHOIS)
#define IPPORT_WHOIS        __IPPORT_WHOIS      /* Internet Whois service. */
#endif /* !IPPORT_WHOIS && __IPPORT_WHOIS */
#if !defined(IPPORT_MTP) && defined(__IPPORT_MTP)
#define IPPORT_MTP          __IPPORT_MTP
#endif /* !IPPORT_MTP && __IPPORT_MTP */
#if !defined(IPPORT_TFTP) && defined(__IPPORT_TFTP)
#define IPPORT_TFTP         __IPPORT_TFTP /* Trivial File Transfer Protocol. */
#endif /* !IPPORT_TFTP && __IPPORT_TFTP */
#if !defined(IPPORT_RJE) && defined(__IPPORT_RJE)
#define IPPORT_RJE          __IPPORT_RJE
#endif /* !IPPORT_RJE && __IPPORT_RJE */
#if !defined(IPPORT_FINGER) && defined(__IPPORT_FINGER)
#define IPPORT_FINGER       __IPPORT_FINGER /* Finger service. */
#endif /* !IPPORT_FINGER && __IPPORT_FINGER */
#if !defined(IPPORT_HTTP) && defined(__IPPORT_HTTP)
#define IPPORT_HTTP         __IPPORT_HTTP   /* Hypertext Transfer Protocol */
#endif /* !IPPORT_HTTP && __IPPORT_HTTP */
#if !defined(IPPORT_TTYLINK) && defined(__IPPORT_TTYLINK)
#define IPPORT_TTYLINK      __IPPORT_TTYLINK
#endif /* !IPPORT_TTYLINK && __IPPORT_TTYLINK */
#if !defined(IPPORT_SUPDUP) && defined(__IPPORT_SUPDUP)
#define IPPORT_SUPDUP       __IPPORT_SUPDUP      /* SUPDUP protocol. */
#endif /* !IPPORT_SUPDUP && __IPPORT_SUPDUP */
#if !defined(IPPORT_HTTPS) && defined(__IPPORT_HTTPS)
#define IPPORT_HTTPS        __IPPORT_HTTPS       /* Hypertext Transfer Protocol Secure */
#endif /* !IPPORT_HTTPS && __IPPORT_HTTPS */
#if !defined(IPPORT_EXECSERVER) && defined(__IPPORT_EXECSERVER)
#define IPPORT_EXECSERVER   __IPPORT_EXECSERVER  /* execd service. */
#endif /* !IPPORT_EXECSERVER && __IPPORT_EXECSERVER */
#if !defined(IPPORT_LOGINSERVER) && defined(__IPPORT_LOGINSERVER)
#define IPPORT_LOGINSERVER  __IPPORT_LOGINSERVER /* rlogind service. */
#endif /* !IPPORT_LOGINSERVER && __IPPORT_LOGINSERVER */
#if !defined(IPPORT_CMDSERVER) && defined(__IPPORT_CMDSERVER)
#define IPPORT_CMDSERVER    __IPPORT_CMDSERVER
#endif /* !IPPORT_CMDSERVER && __IPPORT_CMDSERVER */
#if !defined(IPPORT_EFSSERVER) && defined(__IPPORT_EFSSERVER)
#define IPPORT_EFSSERVER    __IPPORT_EFSSERVER
#endif /* !IPPORT_EFSSERVER && __IPPORT_EFSSERVER */
#if !defined(IPPORT_BIFFUDP) && defined(__IPPORT_BIFFUDP)
#define IPPORT_BIFFUDP      __IPPORT_BIFFUDP      /* UDP ports. */
#endif /* !IPPORT_BIFFUDP && __IPPORT_BIFFUDP */
#if !defined(IPPORT_WHOSERVER) && defined(__IPPORT_WHOSERVER)
#define IPPORT_WHOSERVER    __IPPORT_WHOSERVER    /* ... */
#endif /* !IPPORT_WHOSERVER && __IPPORT_WHOSERVER */
#if !defined(IPPORT_ROUTESERVER) && defined(__IPPORT_ROUTESERVER)
#define IPPORT_ROUTESERVER  __IPPORT_ROUTESERVER  /* ... */
#endif /* !IPPORT_ROUTESERVER && __IPPORT_ROUTESERVER */
#if !defined(IPPORT_RESERVED) && defined(__IPPORT_RESERVED)
#define IPPORT_RESERVED     __IPPORT_RESERVED     /* Ports less than this value are reserved for privileged processes. */
#endif /* !IPPORT_RESERVED && __IPPORT_RESERVED */
#if !defined(IPPORT_USERRESERVED) && defined(__IPPORT_USERRESERVED)
#define IPPORT_USERRESERVED __IPPORT_USERRESERVED /* Ports greater this value are reserved for (non-privileged) servers. */
#endif /* !IPPORT_USERRESERVED && __IPPORT_USERRESERVED */

#endif /* !_NETINET_IPPORT_H */
