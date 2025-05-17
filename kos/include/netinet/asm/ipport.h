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
/*!replace_with_include <netinet/ipport.h>*/
#ifndef _NETINET_ASM_IPPORT_H
#define _NETINET_ASM_IPPORT_H 1

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
#define __IPPORT_ECHO         7    /* Echo service. */
#define __IPPORT_DISCARD      9    /* Discard transmissions service. */
#define __IPPORT_SYSTAT       11   /* System status service. */
#define __IPPORT_DAYTIME      13   /* Time of day service. */
#define __IPPORT_NETSTAT      15   /* Network status service. */
#define __IPPORT_FTP          21   /* File Transfer Protocol. */
#define __IPPORT_TELNET       23   /* Telnet protocol. */
#define __IPPORT_SMTP         25   /* Simple Mail Transfer Protocol. */
#define __IPPORT_TIMESERVER   37   /* Timeserver service. */
#define __IPPORT_NAMESERVER   42   /* Domain Name Service. */
#define __IPPORT_WHOIS        43   /* Internet Whois service. */
#define __IPPORT_MTP          57
#define __IPPORT_TFTP         69   /* Trivial File Transfer Protocol. */
#define __IPPORT_RJE          77
#define __IPPORT_FINGER       79   /* Finger service. */
#define __IPPORT_HTTP         80   /* Hypertext Transfer Protocol */
#define __IPPORT_TTYLINK      87
#define __IPPORT_SUPDUP       95   /* SUPDUP protocol. */
#define __IPPORT_HTTPS        443  /* Hypertext Transfer Protocol Secure */
#define __IPPORT_EXECSERVER   512  /* execd service. */
#define __IPPORT_LOGINSERVER  513  /* rlogind service. */
#define __IPPORT_CMDSERVER    514
#define __IPPORT_EFSSERVER    520
#define __IPPORT_BIFFUDP      512  /* UDP ports. */
#define __IPPORT_WHOSERVER    513  /* ... */
#define __IPPORT_ROUTESERVER  520  /* ... */
#define __IPPORT_RESERVED     1024 /* Ports less than this value are reserved for privileged processes. */
#define __IPPORT_USERRESERVED 5000 /* Ports greater this value are reserved for (non-privileged) servers. */

#endif /* !_NETINET_ASM_IPPORT_H */
