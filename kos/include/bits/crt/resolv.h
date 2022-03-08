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
#ifndef _BITS_CRT_RESOLV_H
#define _BITS_CRT_RESOLV_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <asm/crt/resolv.h>
#include <bits/types.h>
#include <netinet/bits/in.h>
#include <netinet/in.h>

#ifdef __CC__
__DECL_BEGIN

#ifndef __res_state_defined
#define __res_state_defined
typedef enum {
	res_goahead,
	res_nextns,
	res_modified,
	res_done,
	res_error
} res_sendhookact;

typedef res_sendhookact
(__LIBKCALL *res_send_qhook)(struct sockaddr_in *const *__ns,
                             __u_char const **__query, int *__querylen,
                             __u_char *__ans, int __anssiz, int *__resplen);
typedef res_sendhookact
(__LIBKCALL *res_send_rhook)(struct sockaddr_in const *__ns,
                             __u_char const *__query, int __querylen,
                             __u_char *__ans, int __anssiz, int *__resplen);

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("name")
#pragma push_macro("type")
#pragma push_macro("rr_class")
#pragma push_macro("ttl")
#pragma push_macro("rdlength")
#pragma push_macro("rdata")
#pragma push_macro("retrans")
#pragma push_macro("retry")
#pragma push_macro("options")
#pragma push_macro("nscount")
#pragma push_macro("nsaddr_list")
#pragma push_macro("id")
#pragma push_macro("dnsrch")
#pragma push_macro("defdname")
#pragma push_macro("pfcode")
#pragma push_macro("ndots")
#pragma push_macro("nsort")
#pragma push_macro("ipv6_unavail")
#pragma push_macro("unused")
#pragma push_macro("addr")
#pragma push_macro("mask")
#pragma push_macro("sort_list")
#pragma push_macro("qhook")
#pragma push_macro("rhook")
#pragma push_macro("res_h_errno")
#pragma push_macro("pad")
#pragma push_macro("nsmap")
#pragma push_macro("nssocks")
#pragma push_macro("nscount6")
#pragma push_macro("nsinit")
#pragma push_macro("nsaddrs")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef name
#undef type
#undef rr_class
#undef ttl
#undef rdlength
#undef rdata
#undef retrans
#undef retry
#undef options
#undef nscount
#undef nsaddr_list
#undef id
#undef dnsrch
#undef defdname
#undef pfcode
#undef ndots
#undef nsort
#undef ipv6_unavail
#undef unused
#undef addr
#undef mask
#undef sort_list
#undef qhook
#undef rhook
#undef res_h_errno
#undef pad
#undef nsmap
#undef nssocks
#undef nscount6
#undef nsinit
#undef nsaddrs
typedef struct __res_state {
	int                retrans;                 /* ??? */
	int                retry;                   /* ??? */
	__u_long           options;                 /* ??? */
	int                nscount;                 /* ??? */
	struct sockaddr_in nsaddr_list[__MAXNS];    /* ??? */
#define nsaddr         nsaddr_list[0]           /* ??? */
	__u_short          id;                      /* ??? */
	__byte_t         __rs_pad1[2];              /* ... */
	char              *dnsrch[__MAXDNSRCH + 1]; /* ??? */
	char               defdname[256];           /* ??? */
	__u_long           pfcode;                  /* ??? */
	unsigned int       ndots : 4;               /* ??? */
	unsigned int       nsort : 4;               /* ??? */
	unsigned int       ipv6_unavail : 1;        /* ??? */
	unsigned int       unused : 23;             /* ??? */
	struct {
		struct in_addr addr;                    /* ??? */
		__uint32_t     mask;                    /* ??? */
	} sort_list[__MAXRESOLVSORT];               /* ??? */
#if __SIZEOF_POINTER__ >= 8
	__byte_t         __rs_pad2[4];              /* ... */
#endif /* __SIZEOF_POINTER__ >= 8 */
	res_send_qhook     qhook;                   /* ??? */
	res_send_rhook     rhook;                   /* ??? */
	int                res_h_errno;             /* ??? */
	int               _vcsock;                  /* ??? */
	__u_int           _flags;                   /* ??? */
#if __SIZEOF_POINTER__ >= 8
	__byte_t         __rs_pad3[4];              /* ... */
#endif /* __SIZEOF_POINTER__ >= 8 */
	union {
		char           pad[52]; /* ... */
		struct {
			__uint16_t           nscount;        /* ??? */
			__uint16_t           nsmap[__MAXNS];   /* ??? */
			int                  nssocks[__MAXNS]; /* ??? */
			__uint16_t           nscount6;       /* ??? */
			__uint16_t           nsinit;         /* ??? */
			struct sockaddr_in6 *nsaddrs[__MAXNS]; /* ??? */
			__UINT32_TYPE__     _initstamp[2];   /* ??? */
		} _ext;
	} _u;
} *res_state;
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("nsaddrs")
#pragma pop_macro("nsinit")
#pragma pop_macro("nscount6")
#pragma pop_macro("nssocks")
#pragma pop_macro("nsmap")
#pragma pop_macro("pad")
#pragma pop_macro("res_h_errno")
#pragma pop_macro("rhook")
#pragma pop_macro("qhook")
#pragma pop_macro("sort_list")
#pragma pop_macro("mask")
#pragma pop_macro("addr")
#pragma pop_macro("unused")
#pragma pop_macro("ipv6_unavail")
#pragma pop_macro("nsort")
#pragma pop_macro("ndots")
#pragma pop_macro("pfcode")
#pragma pop_macro("defdname")
#pragma pop_macro("dnsrch")
#pragma pop_macro("id")
#pragma pop_macro("nsaddr_list")
#pragma pop_macro("nscount")
#pragma pop_macro("options")
#pragma pop_macro("retry")
#pragma pop_macro("retrans")
#pragma pop_macro("rdata")
#pragma pop_macro("rdlength")
#pragma pop_macro("ttl")
#pragma pop_macro("rr_class")
#pragma pop_macro("type")
#pragma pop_macro("name")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* !__res_state_defined */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("number")
#pragma push_macro("name")
#pragma push_macro("humanname")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef number
#undef name
#undef humanname
struct res_sym {
	int   number;    /* ??? */
	char *name;      /* ??? */
	char *humanname; /* ??? */
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("humanname")
#pragma pop_macro("name")
#pragma pop_macro("number")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_RESOLV_H */
