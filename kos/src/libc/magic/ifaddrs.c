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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(oflag_t = __oflag_t)]

%{
#include <features.h>
#include <sys/socket.h>

/* Derived from GLibc /usr/include/ifaddrs.h */
/* ifaddrs.h -- declarations for getting network interface addresses
   Copyright (C) 2002-2016 Free Software Foundation, Inc.
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

/* The `getifaddrs' function generates a linked list of these structures.
 * Each element of the list describes one network interface. */
struct ifaddrs {
	struct ifaddrs  *ifa_next;    /* Pointer to the next structure. */
	char            *ifa_name;    /* Name of this network interface. */
	__UINT32_TYPE__  ifa_flags;   /* Flags as from SIOCGIFFLAGS ioctl. */
	struct sockaddr *ifa_addr;    /* Network address of this interface. */
	struct sockaddr *ifa_netmask; /* Netmask of this interface. */
#ifdef __COMPILER_HAVE_TRANSPARENT_UNION
	union {
		union {
			/* At most one of the following two is valid. If the IFF_BROADCAST
			 * bit is set in `ifa_flags', then `ifa_broadaddr' is valid. If the
			 * IFF_POINTOPOINT bit is set, then `ifa_dstaddr' is valid.
			 * It is never the case that both these bits are set at once. */
			struct sockaddr *ifu_broadaddr; /* Broadcast address of this interface. */
			struct sockaddr *ifu_dstaddr;   /* Point-to-point destination address. */
		} ifa_ifu;
		struct sockaddr *ifa_broadaddr; /* Broadcast address of this interface. */
		struct sockaddr *ifa_dstaddr;   /* Point-to-point destination address. */
	};
#else /* __COMPILER_HAVE_TRANSPARENT_UNION */
	union {
		/* At most one of the following two is valid. If the IFF_BROADCAST
		 * bit is set in `ifa_flags', then `ifa_broadaddr' is valid. If the
		 * IFF_POINTOPOINT bit is set, then `ifa_dstaddr' is valid.
		 * It is never the case that both these bits are set at once. */
		struct sockaddr *ifu_broadaddr; /* Broadcast address of this interface. */
		struct sockaddr *ifu_dstaddr;   /* Point-to-point destination address. */
	} ifa_ifu;
#ifndef ifa_broadaddr
#define ifa_broadaddr ifa_ifu.ifu_broadaddr
#define ifa_dstaddr ifa_ifu.ifu_dstaddr
#endif /* !ifa_broadaddr */
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
	void *ifa_data; /* Address-specific data (may be unused). */
};

}


@@Create a linked list of `struct ifaddrs' structures, one for each
@@network interface on the host machine. If successful, store the
@@list in *IFAP and return 0. On errors, return -1 and set `errno'.
@@The storage returned in *IFAP is allocated dynamically and can
@@only be properly freed by passing it to `freeifaddrs'
getifaddrs:(struct ifaddrs **ifap) -> int;

@@Reclaim the storage allocated by a previous `getifaddrs' call
freeifaddrs:(struct ifaddrs *ifa);

%{

#endif /* __CC__ */

__SYSDECL_END

}
