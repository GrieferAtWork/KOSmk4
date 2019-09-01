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
%[default_impl_section(.text.crt.net.ether)]

%{
#include <features.h>
#include <netinet/if_ether.h>

__SYSDECL_BEGIN

/* Documentation taken from Glibc /usr/include/netinet/ether.h */
/* Functions for storing Ethernet addresses in ASCII and mapping to hostnames.
   Copyright (C) 1996-2016 Free Software Foundation, Inc.
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

#ifdef __CC__

}

@@Convert 48 bit Ethernet ADDRess to ASCII
[cp_kos] ether_ntoa:(struct ether_addr const *addr) -> char *;
[cp_kos][doc_alias(ether_ntoa)] ether_ntoa_r:(struct ether_addr const *addr, char *buf) -> char *;

@@Convert ASCII string S to 48 bit Ethernet address
[cp_kos] ether_aton:(char const *asc) -> struct ether_addr *;
[cp_kos][doc_alias(ether_aton)] ether_aton_r:(char const *asc, struct ether_addr *addr) -> struct ether_addr *;

@@Map 48 bit Ethernet number ADDR to HOSTNAME
[cp_kos] ether_ntohost:(char *hostname, struct ether_addr const *addr) -> int;

@@Map HOSTNAME to 48 bit Ethernet address
[cp_kos] ether_hostton:(char const *hostname, struct ether_addr *addr) -> int;

@@Scan LINE and set ADDR and HOSTNAME
[cp_kos] ether_line:(char const *line, struct ether_addr *addr, char *hostname) -> int;


%{

#endif /* __CC__ */

__SYSDECL_END

}