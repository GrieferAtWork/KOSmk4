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
#ifndef _BITS_OS_KOS_IFREQ_H
#define _BITS_OS_KOS_IFREQ_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <asm/os/net-if.h>    /* __IF_NAMESIZE */
#include <bits/os/ifmap.h>    /* struct ifmap */
#include <bits/os/sockaddr.h> /* struct sockaddr */
#include <bits/types.h>

#ifdef __CC__
__DECL_BEGIN

#undef ifr_name
#undef ifr_addr
#undef ifr_dstaddr
#undef ifr_broadaddr
#undef ifr_netmask
#undef ifr_hwaddr
#undef ifr_flags
#undef ifr_metric
#undef ifr_ifindex
#undef ifr_bandwidth
#undef ifr_qlen
#undef ifr_mtu
#undef ifr_map
#undef ifr_slave
#undef ifr_newname
#undef ifr_data
#undef ifr_settings

struct ifreq {
#ifdef __USE_KOS_PURE
	char ifr_name[__IF_NAMESIZE];
#elif defined(__COMPILER_HAVE_TRANSPARENT_UNION)
	union {
		char ifr_name[__IF_NAMESIZE];
		union {
			char ifrn_name[__IF_NAMESIZE];
		} ifr_ifrn;
	};
#else /* __COMPILER_HAVE_TRANSPARENT_UNION */
#define ifr_name ifr_ifrn.ifrn_name
	union {
		char ifrn_name[__IF_NAMESIZE];
	} ifr_ifrn;
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
#ifdef __COMPILER_HAVE_TRANSPARENT_UNION
	union {
		struct sockaddr     ifr_addr;                       /* ??? */
		struct sockaddr     ifr_dstaddr;                    /* ??? */
		struct sockaddr     ifr_broadaddr;                  /* ??? */
		struct sockaddr     ifr_netmask;                    /* ??? */
		struct sockaddr     ifr_hwaddr;                     /* ??? */
#ifdef __USE_KOS_ALTERATIONS
		__UINT16_TYPE__     ifr_flags;                      /* ??? */
		__UINT32_TYPE__     ifr_metric;                     /* ??? */
		__UINT32_TYPE__     ifr_ifindex;                    /* ??? */
		__UINT32_TYPE__     ifr_bandwidth;                  /* ??? */
		__UINT32_TYPE__     ifr_qlen;                       /* ??? */
		__UINT32_TYPE__     ifr_mtu;                        /* ??? */
#else /* __USE_KOS_ALTERATIONS */
		__INT16_TYPE__      ifr_flags;                      /* ??? */
		__INT32_TYPE__      ifr_metric;                     /* ??? */
		__INT32_TYPE__      ifr_ifindex;                    /* ??? */
		__INT32_TYPE__      ifr_bandwidth;                  /* ??? */
		__INT32_TYPE__      ifr_qlen;                       /* ??? */
		__INT32_TYPE__      ifr_mtu;                        /* ??? */
#endif /* !__USE_KOS_ALTERATIONS */
		struct ifmap        ifr_map;                        /* ??? */
		char                ifr_slave[__IF_NAMESIZE];       /* ??? */
		char                ifr_newname[__IF_NAMESIZE];     /* ??? */
		__caddr_t           ifr_data;                       /* ??? */
#ifndef __USE_KOS_PURE
		union {
			struct sockaddr    ifru_addr;                   /* ??? */
			struct sockaddr    ifru_dstaddr;                /* ??? */
			struct sockaddr    ifru_broadaddr;              /* ??? */
			struct sockaddr    ifru_netmask;                /* ??? */
			struct sockaddr    ifru_hwaddr;                 /* ??? */
#ifdef __USE_KOS_ALTERATIONS
			__UINT16_TYPE__    ifru_flags;                  /* ??? */
			__UINT32_TYPE__    ifru_ivalue;                 /* ??? */
			__UINT32_TYPE__    ifru_mtu;                    /* ??? */
#else /* __USE_KOS_ALTERATIONS */
			__INT16_TYPE__     ifru_flags;                  /* ??? */
			__INT32_TYPE__     ifru_ivalue;                 /* ??? */
			__INT32_TYPE__     ifru_mtu;                    /* ??? */
#endif /* !__USE_KOS_ALTERATIONS */
			struct ifmap       ifru_map;                    /* ??? */
			char               ifru_slave[__IF_NAMESIZE];   /* ??? */
			char               ifru_newname[__IF_NAMESIZE]; /* ??? */
			__caddr_t          ifru_data;                   /* ??? */
		} ifr_ifru;
#endif /* !__USE_KOS_PURE */
	};
#else /* __COMPILER_HAVE_TRANSPARENT_UNION */
	union {
		struct sockaddr    ifru_addr;                   /* ??? */
		struct sockaddr    ifru_dstaddr;                /* ??? */
		struct sockaddr    ifru_broadaddr;              /* ??? */
		struct sockaddr    ifru_netmask;                /* ??? */
		struct sockaddr    ifru_hwaddr;                 /* ??? */
#ifdef __USE_KOS_ALTERATIONS
		__UINT16_TYPE__    ifru_flags;                  /* ??? */
		__UINT32_TYPE__    ifru_ivalue;                 /* ??? */
		__UINT32_TYPE__    ifru_mtu;                    /* ??? */
#else /* __USE_KOS_ALTERATIONS */
		__INT16_TYPE__     ifru_flags;                  /* ??? */
		__INT32_TYPE__     ifru_ivalue;                 /* ??? */
		__INT32_TYPE__     ifru_mtu;                    /* ??? */
#endif /* !__USE_KOS_ALTERATIONS */
		struct ifmap       ifru_map;                    /* ??? */
		char               ifru_slave[__IF_NAMESIZE];   /* ??? */
		char               ifru_newname[__IF_NAMESIZE]; /* ??? */
		__caddr_t          ifru_data;                   /* ??? */
	} ifr_ifru;
#define ifr_addr      ifr_ifru.ifru_addr      /* ??? */
#define ifr_dstaddr   ifr_ifru.ifru_dstaddr   /* ??? */
#define ifr_broadaddr ifr_ifru.ifru_broadaddr /* ??? */
#define ifr_netmask   ifr_ifru.ifru_netmask   /* ??? */
#define ifr_hwaddr    ifr_ifru.ifru_hwaddr    /* ??? */
#define ifr_flags     ifr_ifru.ifru_flags     /* ??? */
#define ifr_metric    ifr_ifru.ifru_ivalue    /* ??? */
#define ifr_ifindex   ifr_ifru.ifru_ivalue    /* ??? */
#define ifr_bandwidth ifr_ifru.ifru_ivalue    /* ??? */
#define ifr_qlen      ifr_ifru.ifru_ivalue    /* ??? */
#define ifr_mtu       ifr_ifru.ifru_mtu       /* ??? */
#define ifr_map       ifr_ifru.ifru_map       /* ??? */
#define ifr_slave     ifr_ifru.ifru_slave     /* ??? */
#define ifr_newname   ifr_ifru.ifru_newname   /* ??? */
#define ifr_data      ifr_ifru.ifru_data      /* ??? */
#define ifr_settings  ifr_ifru.ifru_settings  /* ??? */
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_KOS_IFREQ_H */
