/* HASH CRC-32:0xadc4bc0 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (>) Standard: POSIX.1-2004 (Issue 6, IEEE Std 1003.1-2004) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/net/if.h) */
/* (#) Portability: DragonFly BSD (/sys/net/if.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/net/if.h) */
/* (#) Portability: FreeBSD       (/sys/net/if.h) */
/* (#) Portability: GNU C Library (/sysdeps/[...]/net/if.h) */
/* (#) Portability: GNU Hurd      (/usr/include/net/if.h) */
/* (#) Portability: NetBSD        (/sys/net/if.h) */
/* (#) Portability: OpenBSD       (/sys/net/if.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/net/if.h) */
/* (#) Portability: diet libc     (/include/net/if.h) */
/* (#) Portability: libc4/5       (/include/net/if.h) */
/* (#) Portability: libc6         (/include/net/if.h) */
/* (#) Portability: mintlib       (/include/net/if.h) */
/* (#) Portability: musl libc     (/include/net/if.h) */
/* (#) Portability: uClibc        (/include/net/if.h) */
#ifndef _NET_IF_H
#define _NET_IF_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#ifdef __USE_MISC
#include <sys/types.h>
#include <sys/socket.h>
#endif /* __USE_MISC */

__SYSDECL_BEGIN

/* net/if.h -- declarations for inquiring about network interfaces
   Copyright (C) 1997-2016 Free Software Foundation, Inc.
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

/* Length of interface name. */
#ifndef IF_NAMESIZE
#ifdef IFNAMSIZ
#define IF_NAMESIZE IFNAMSIZ
#else /* IFNAMSIZ */
#define IF_NAMESIZE 16
#endif /* !IFNAMSIZ */
#endif /* !IF_NAMESIZE */

#ifdef __CC__
/* TODO: This structure should go into <bits/crt/if_nameindex-struct.h> */
struct if_nameindex {
	__STDC_UINT32_AS_SIZE_T if_index; /* 1, 2, ... */
	char                   *if_name;  /* null terminated name: "eth0", ... */
};
#endif /* __CC__ */

#ifdef __USE_MISC
#ifndef IFF_UP
/* Standard interface flags. */
/* TODO: These constants should go into <asm/os/if.h> */
#define IFF_UP          0x0001  /* Interface is up. */
#define IFF_BROADCAST   0x0002  /* Broadcast address valid. */
#define IFF_DEBUG       0x0004  /* Turn on debugging. */
#define IFF_LOOPBACK    0x0008  /* Is a loopback net. */
#define IFF_POINTOPOINT 0x0010  /* Interface is point-to-point link. */
#define IFF_NOTRAILERS  0x0020  /* Avoid use of trailers. */
#define IFF_RUNNING     0x0040  /* Resources allocated. */
#define IFF_NOARP       0x0080  /* No address resolution protocol. */
#define IFF_PROMISC     0x0100  /* Receive all packets. */
/* Not supported */
#define IFF_ALLMULTI    0x0200  /* Receive all multicast packets. */
#define IFF_MASTER      0x0400  /* Master of a load balancer. */
#define IFF_SLAVE       0x0800  /* Slave of a load balancer. */
#define IFF_MULTICAST   0x1000  /* Supports multicast. */
#define IFF_PORTSEL     0x2000  /* Can set media type. */
#define IFF_AUTOMEDIA   0x4000  /* Auto media select active. */
#define IFF_DYNAMIC     0x8000  /* Dialup device with changing addresses. */
#endif /* !IFF_UP */


/* The ifaddr structure contains information about one address of an
 * interface. They are maintained by the different address families,
 * are allocated and attached when an address is set, and are linked
 * together so all addresses for an interface can be located. */
#ifdef __CC__
#undef ifa_broadaddr
#undef ifa_dstaddr
/* TODO: This structure should go into <bits/ifaddr-struct.h> */
struct ifaddr {
	struct sockaddr     ifa_addr; /* Address of interface. */
#ifdef __COMPILER_HAVE_TRANSPARENT_UNION
	union {
		/* TODO: Get rid of the member redundancy where when `__USE_KOS_PURE' is defined */
		struct sockaddr ifa_broadaddr; /* broadcast address. */
		struct sockaddr ifa_dstaddr;   /* other end of link. */
		union {
			struct sockaddr ifu_broadaddr; /* broadcast address. */
			struct sockaddr ifu_dstaddr;   /* other end of link. */
		}                   ifa_ifu;
	};
#else /* __COMPILER_HAVE_TRANSPARENT_UNION */
	union {
		struct sockaddr ifu_broadaddr;
		struct sockaddr ifu_dstaddr;
	}                   ifa_ifu;
#define ifa_broadaddr ifa_ifu.ifu_broadaddr /* broadcast address. */
#define ifa_dstaddr   ifa_ifu.ifu_dstaddr   /* other end of link. */
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
	struct iface       *ifa_ifp;  /* Back-pointer to interface. */
	struct ifaddr      *ifa_next; /* Next address for interface. */
};
#endif /* __CC__ */

/* Device mapping structure. I'd just gone off and designed  a
 * beautiful scheme using only loadable modules with arguments
 * for driver options and along come the PCMCIA people 8)
 *
 * Ah  well. The get() side of this is good for WDSETUP, and it'll be
 * handy for debugging things. The set side is fine for now and being
 * very small might be worth keeping for clean configuration. */

#ifdef __CC__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("mem_start")
#pragma push_macro("mem_end")
#pragma push_macro("base_addr")
#pragma push_macro("irq")
#pragma push_macro("dma")
#pragma push_macro("port")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef mem_start
#undef mem_end
#undef base_addr
#undef irq
#undef dma
#undef port
/* TODO: This structure should go into <bits/ifmap-struct.h> */
struct ifmap {
	__ULONGPTR_TYPE__ mem_start;
	__ULONGPTR_TYPE__ mem_end;
	__UINT16_TYPE__   base_addr;
	__UINT8_TYPE__    irq;
	__UINT8_TYPE__    dma;
	__UINT8_TYPE__    port;
	__UINT8_TYPE__    __pad[3]; /* 3 bytes spare */
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("port")
#pragma pop_macro("dma")
#pragma pop_macro("irq")
#pragma pop_macro("base_addr")
#pragma pop_macro("mem_end")
#pragma pop_macro("mem_start")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __CC__ */

/* Interface request structure used for socket ioctl's. All interface
 * ioctl's must have parameter definitions which begin with ifr_name.
 * The remainder may be interface specific. */

#ifndef IFHWADDRLEN
#define IFHWADDRLEN     6
#endif /* !IFHWADDRLEN */
#ifndef IFNAMSIZ
#define IFNAMSIZ        IF_NAMESIZE
#endif /* !IFNAMSIZ */
#ifndef __ifreq_defined
#define __ifreq_defined
#ifdef __CC__
/* TODO: This structure should go into <bits/ifreq-struct.h> */
struct ifreq {
#ifdef __COMPILER_HAVE_TRANSPARENT_UNION
	union {
		/* TODO: Get rid of the member redundancy where when `__USE_KOS_PURE' is defined */
		char ifr_name[IFNAMSIZ]; /* if name, e.g. "en0" */
		union {
			char ifrn_name[IFNAMSIZ]; /* if name, e.g. "en0" */
		} ifr_ifrn;
	};
#else /* __COMPILER_HAVE_TRANSPARENT_UNION */
#define ifr_name ifr_ifrn.ifrn_name /* interface name  */
	union {
		char ifrn_name[IFNAMSIZ]; /* if name, e.g. "en0" */
	} ifr_ifrn;
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
#if defined(__COMPILER_HAVE_TRANSPARENT_UNION) && defined(__COMPILER_HAVE_TRANSPARENT_STRUCT)
	union {
		struct {
			/* TODO: Get rid of the member redundancy where when `__USE_KOS_PURE' is defined */
			struct sockaddr     ifr_addr;
			struct sockaddr     ifr_dstaddr;
			struct sockaddr     ifr_broadaddr;
			struct sockaddr     ifr_netmask;
			struct sockaddr     ifr_hwaddr;
#ifdef __USE_KOS_ALTERATIONS
			__UINT16_TYPE__     ifr_flags;
#else /* __USE_KOS_ALTERATIONS */
			__INT16_TYPE__      ifr_flags;
#endif /* !__USE_KOS_ALTERATIONS */
			union {
#ifdef __USE_KOS_ALTERATIONS
				__UINT32_TYPE__ ifr_metric;    /* metric */
				__UINT32_TYPE__ ifr_ifindex;   /* interface index */
				__UINT32_TYPE__ ifr_bandwidth; /* link bandwidth */
				__UINT32_TYPE__ ifr_qlen;      /* Queue length  */
#else /* __USE_KOS_ALTERATIONS */
				__INT32_TYPE__  ifr_metric;    /* metric */
				__INT32_TYPE__  ifr_ifindex;   /* interface index */
				__INT32_TYPE__  ifr_bandwidth; /* link bandwidth */
				__INT32_TYPE__  ifr_qlen;      /* Queue length  */
#endif /* !__USE_KOS_ALTERATIONS */
			};
#ifdef __USE_KOS_ALTERATIONS
			__UINT32_TYPE__     ifr_mtu;
#else /* __USE_KOS_ALTERATIONS */
			__INT32_TYPE__      ifr_mtu;
#endif /* !__USE_KOS_ALTERATIONS */
			struct ifmap        ifr_map;
			char                ifr_slave[IFNAMSIZ]; /* Just fits the size */
			char                ifr_newname[IFNAMSIZ];
			__caddr_t           ifr_data;
		};
		union {
			struct sockaddr    ifru_addr;
			struct sockaddr    ifru_dstaddr;
			struct sockaddr    ifru_broadaddr;
			struct sockaddr    ifru_netmask;
			struct sockaddr    ifru_hwaddr;
#ifdef __USE_KOS_ALTERATIONS
			__UINT16_TYPE__    ifru_flags;
			__UINT32_TYPE__    ifru_ivalue;
			__UINT32_TYPE__    ifru_mtu;
#else /* __USE_KOS_ALTERATIONS */
			__INT16_TYPE__     ifru_flags;
			__INT32_TYPE__     ifru_ivalue;
			__INT32_TYPE__     ifru_mtu;
#endif /* !__USE_KOS_ALTERATIONS */
			struct ifmap       ifru_map;
			char               ifru_slave[IFNAMSIZ]; /* Just fits the size */
			char               ifru_newname[IFNAMSIZ];
			__caddr_t          ifru_data;
		} ifr_ifru;
	};
#else /* __COMPILER_HAVE_TRANSPARENT_UNION && __COMPILER_HAVE_TRANSPARENT_STRUCT */
	union {
		struct sockaddr    ifru_addr;
		struct sockaddr    ifru_dstaddr;
		struct sockaddr    ifru_broadaddr;
		struct sockaddr    ifru_netmask;
		struct sockaddr    ifru_hwaddr;
#ifdef __USE_KOS_ALTERATIONS
		__UINT16_TYPE__    ifru_flags;
		__UINT32_TYPE__    ifru_ivalue;
		__UINT32_TYPE__    ifru_mtu;
#else /* __USE_KOS_ALTERATIONS */
		__INT16_TYPE__     ifru_flags;
		__INT32_TYPE__     ifru_ivalue;
		__INT32_TYPE__     ifru_mtu;
#endif /* !__USE_KOS_ALTERATIONS */
		struct ifmap       ifru_map;
		char               ifru_slave[IFNAMSIZ]; /* Just fits the size */
		char               ifru_newname[IFNAMSIZ];
		__caddr_t          ifru_data;
	} ifr_ifru;
#define ifr_addr      ifr_ifru.ifru_addr      /* address */
#define ifr_dstaddr   ifr_ifru.ifru_dstaddr   /* other end of p-p lnk */
#define ifr_broadaddr ifr_ifru.ifru_broadaddr /* broadcast address */
#define ifr_netmask   ifr_ifru.ifru_netmask   /* interface net mask */
#define ifr_hwaddr    ifr_ifru.ifru_hwaddr    /* MAC address  */
#define ifr_flags     ifr_ifru.ifru_flags     /* flags */
#define ifr_metric    ifr_ifru.ifru_ivalue    /* metric */
#define ifr_ifindex   ifr_ifru.ifru_ivalue    /* interface index */
#define ifr_bandwidth ifr_ifru.ifru_ivalue    /* link bandwidth */
#define ifr_qlen      ifr_ifru.ifru_ivalue    /* Queue length  */
#define ifr_mtu       ifr_ifru.ifru_mtu       /* mtu */
#define ifr_map       ifr_ifru.ifru_map       /* device map */
#define ifr_slave     ifr_ifru.ifru_slave     /* slave device */
#define ifr_newname   ifr_ifru.ifru_newname   /* New name */
#define ifr_data      ifr_ifru.ifru_data      /* for use by interface */
#define ifr_settings  ifr_ifru.ifru_settings  /* Device/proto settings*/
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION || !__COMPILER_HAVE_TRANSPARENT_STRUCT */
};
#endif /* __CC__ */
#endif /* !__ifreq_defined */

#define _IOT_ifreq        _IOT(_IOTS(char), IFNAMSIZ, _IOTS(char), 16, 0, 0)
#define _IOT_ifreq_short  _IOT(_IOTS(char), IFNAMSIZ, _IOTS(short), 1, 0, 0)
#define _IOT_ifreq_int    _IOT(_IOTS(char), IFNAMSIZ, _IOTS(int), 1, 0, 0)


/* Structure  used  in   SIOCGIFCONF  request.  Used   to
 * retrieve interface configuration  for machine  (useful
 * for programs which must know all networks accessible). */
#ifdef __CC__
#ifndef __ifconf_defined
#define __ifconf_defined
/* TODO: This structure should go into <bits/ifconf-struct.h> */
struct ifconf {
	__INT32_TYPE__    ifc_len; /* size of buffer */
#ifdef __COMPILER_HAVE_TRANSPARENT_UNION
	union {
		/* TODO: Get rid of the member redundancy where when `__USE_KOS_PURE' is defined */
		char         *ifc_buf; /* buffer address */
		struct ifreq *ifc_req; /* array of structures */
		union {
			char         *ifcu_buf; /* buffer address */
			struct ifreq *ifcu_req; /* array of structures */
		} ifc_ifcu;
	};
#else /* __COMPILER_HAVE_TRANSPARENT_UNION */
	union {
		char         *ifcu_buf; /* buffer address */
		struct ifreq *ifcu_req; /* array of structures */
	} ifc_ifcu;
#define ifc_buf ifc_ifcu.ifcu_buf /* buffer address */
#define ifc_req ifc_ifcu.ifcu_req /* array of structures */
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
};
#endif /* !__ifconf_defined */
#endif /* __CC__ */
#define _IOT_ifconf _IOT(_IOTS(struct ifconf), 1, 0, 0, 0, 0) /* not right */
#endif /* __USE_MISC */

#ifdef __CC__

/* Convert an interface name to an index, and vice versa */
__CDECLARE_OPT(,unsigned int,__NOTHROW_RPC_KOS,if_nametoindex,(char const *__ifname),(__ifname))
/* Convert an interface name to an index, and vice versa */
__CDECLARE_OPT(,char *,__NOTHROW_RPC_KOS,if_indextoname,(unsigned int __ifindex, char *__ifname),(__ifindex,__ifname))
/* Return a list of all interfaces and their indices */
__CDECLARE_OPT(,struct if_nameindex *,__NOTHROW_RPC_KOS,if_nameindex,(void),())
/* Free the data returned from if_nameindex */
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,if_freenameindex,(struct if_nameindex *__ptr),(__ptr))

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_NET_IF_H */
