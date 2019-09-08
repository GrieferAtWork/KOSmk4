/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

%[default_impl_section(.text.crt.net.inet)]
%[define_replacement(fd_t = __fd_t)]
%[define_replacement(pid_t = __pid_t)]

%{
#include <features.h>
#include <bits/types.h>
#include <netinet/in.h>

/* Documentation taken from Glibc /usr/include/arpa/inet.h */
/* Copyright (C) 1997-2016 Free Software Foundation, Inc.
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


__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __socklen_t_defined
#define __socklen_t_defined 1
typedef __socklen_t socklen_t;
#endif /* !__socklen_t_defined */

}

@@Convert Internet host address from numbers-and-dots
@@notation in CP into binary data in network byte order
[cp_kos] inet_addr:(char const *cp) -> in_addr_t;

@@Return the local host address part of the Internet address in IN
[cp_kos] inet_lnaof:(struct in_addr inaddr) -> in_addr_t;

@@Make Internet host address in network byte order by
@@combining the network number NET with the local address HOST
[cp_kos] inet_makeaddr:(in_addr_t net, in_addr_t host) -> struct in_addr;

@@Return network number part of the Internet address IN
[cp_kos] inet_netof:(struct in_addr inaddr) -> in_addr_t;

@@Extract the network number in network byte order from
@@the address in numbers-and-dots natation starting at CP
[cp_kos] inet_network:(char const *cp) -> in_addr_t;

@@Convert Internet number in IN to ASCII representation. The return
@@value is a pointer to an internal array containing the string
[cp_kos] inet_ntoa:(struct in_addr inaddr) -> char *;

@@Convert from presentation format of an Internet number in buffer
@@starting at CP to the binary network format and store result for
@@interface type AF in buffer starting at BUF
[cp_kos] inet_pton:(int af, char const *__restrict cp, void *__restrict buf) -> int;

@@Convert a Internet address in binary network format for interface
@@type AF in buffer starting at CP to presentation form and place
@@result in buffer of length LEN astarting at BUF
[cp_kos] inet_ntop:(int af, void const *__restrict cp, char *__restrict buf, socklen_t len) -> char const *;

%
%/* The following functions are not part of XNS 5.2. */
%#ifdef __USE_MISC

@@Convert Internet host address from numbers-and-dots notation in CP
@@into binary data and store the result in the structure INP
[cp_kos] inet_aton:(char const *cp, struct in_addr *inp) -> int;

@@Format a network number NET into presentation format and place
@@result in buffer starting at BUF with length of LEN bytes
[cp_kos] inet_neta:(in_addr_t net, char *buf, size_t len) -> char *;

@@Convert network number for interface type AF in buffer starting at
@@CP to presentation format.  The result will specifiy BITS bits of
@@the number
[cp_kos] inet_net_ntop:(int af, void const *cp, int bits, char *buf, size_t len) -> char *;

@@Convert network number for interface type AF from presentation in
@@buffer starting at CP to network format and store result int
@@buffer starting at BUF of size LEN
[cp_kos] inet_net_pton:(int af, char const *cp, void *buf, size_t len) -> int;

@@Convert ASCII representation in hexadecimal form of the Internet
@@address to binary form and place result in buffer of length LEN
@@starting at BUF
[cp_kos] inet_nsap_addr:(char const *cp, unsigned char *buf, int len) -> unsigned int;

@@Convert internet address in binary form in LEN bytes starting
@@at CP a presentation form and place result in BUF
[cp_kos] inet_nsap_ntoa:(int len, unsigned char const *cp, char *buf) -> char *;

%#endif /* __USE_MISC */


%{

#endif /* __CC__ */

__SYSDECL_END

}