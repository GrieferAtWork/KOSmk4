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
#ifndef _NETINET_IPPORT_H
#define _NETINET_IPPORT_H 1

#include <__stdinc.h>

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
#define IPPORT_ECHO         7    /* Echo service. */
#define IPPORT_DISCARD      9    /* Discard transmissions service. */
#define IPPORT_SYSTAT       11   /* System status service. */
#define IPPORT_DAYTIME      13   /* Time of day service. */
#define IPPORT_NETSTAT      15   /* Network status service. */
#define IPPORT_FTP          21   /* File Transfer Protocol. */
#define IPPORT_TELNET       23   /* Telnet protocol. */
#define IPPORT_SMTP         25   /* Simple Mail Transfer Protocol. */
#define IPPORT_TIMESERVER   37   /* Timeserver service. */
#define IPPORT_NAMESERVER   42   /* Domain Name Service. */
#define IPPORT_WHOIS        43   /* Internet Whois service. */
#define IPPORT_MTP          57
#define IPPORT_TFTP         69   /* Trivial File Transfer Protocol. */
#define IPPORT_RJE          77
#define IPPORT_FINGER       79   /* Finger service. */
#define IPPORT_HTTP         80   /* Hypertext Transfer Protocol */
#define IPPORT_TTYLINK      87
#define IPPORT_SUPDUP       95   /* SUPDUP protocol. */
#define IPPORT_HTTPS        443  /* Hypertext Transfer Protocol Secure */
#define IPPORT_EXECSERVER   512  /* execd service. */
#define IPPORT_LOGINSERVER  513  /* rlogind service. */
#define IPPORT_CMDSERVER    514
#define IPPORT_EFSSERVER    520
#define IPPORT_BIFFUDP      512  /* UDP ports. */
#define IPPORT_WHOSERVER    513  /* ... */
#define IPPORT_ROUTESERVER  520  /* ... */
#define IPPORT_RESERVED     1024 /* Ports less than this value are reserved for privileged processes. */
#define IPPORT_USERRESERVED 5000 /* Ports greater this value are reserved for (non-privileged) servers. */


#endif /* !_NETINET_IPPORT_H */
