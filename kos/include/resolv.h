/* HASH CRC-32:0x5638d60d */
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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/resolv.h) */
/* (#) Portability: FreeBSD       (/include/resolv.h) */
/* (#) Portability: GNU C Library (/resolv/resolv.h) */
/* (#) Portability: NetBSD        (/include/resolv.h) */
/* (#) Portability: OpenBSD       (/include/resolv.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/resolv.h) */
/* (#) Portability: diet libc     (/include/resolv.h) */
/* (#) Portability: libc4/5       (/include/resolv.h) */
/* (#) Portability: libc6         (/include/resolv.h) */
/* (#) Portability: musl libc     (/include/resolv.h) */
/* (#) Portability: uClibc        (/include/resolv.h) */
#ifndef _RESOLV_H
#define _RESOLV_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <arpa/nameser.h>
#include <netinet/in.h>
#include <sys/cdefs.h>
#include <sys/param.h>
#include <sys/types.h>

#include <stdio.h>

/* ??? */
#define MAXNS            3 /* ??? */
#define MAXDFLSRCH       3 /* ??? */
#define MAXDNSRCH        6 /* ??? */
#define LOCALDOMAINPARTS 2 /* ??? */

/* ??? */
#define RES_TIMEOUT    5     /* ??? */
#define MAXRESOLVSORT  10    /* ??? */
#define RES_MAXNDOTS   15    /* ??? */
#define RES_MAXRETRANS 30    /* ??? */
#define RES_MAXRETRY   5     /* ??? */
#define RES_DFLRETRY   2     /* ??? */
#define RES_MAXTIME    65535 /* ??? */

/* ??? */
#define __RES 19991006

/* ??? */
#ifndef _PATH_RESCONF
#define _PATH_RESCONF "/etc/resolv.conf"
#endif /* !_PATH_RESCONF */

/* ??? */
#define RES_F_VC       0x00000001 /* socket is TCP */
#define RES_F_CONN     0x00000002 /* socket is connected */
#define RES_F_EDNS0ERR 0x00000004 /* EDNS0 caused errors */

/* ??? */
#define RES_EXHAUSTIVE 0x00000001 /* always do all queries */

/* ??? */
#define RES_INIT        0x00000001 /* address initialized */
#define RES_DEBUG       0x00000002 /* print debug messages */
#define RES_AAONLY      0x00000004 /* authoritative answers only (!IMPL)*/
#define RES_USEVC       0x00000008 /* use virtual circuit */
#define RES_PRIMARY     0x00000010 /* query primary server only (!IMPL) */
#define RES_IGNTC       0x00000020 /* ignore trucation errors */
#define RES_RECURSE     0x00000040 /* recursion desired */
#define RES_DEFNAMES    0x00000080 /* use default domain name */
#define RES_STAYOPEN    0x00000100 /* Keep TCP socket open */
#define RES_DNSRCH      0x00000200 /* search up local domain tree */
#define RES_INSECURE1   0x00000400 /* type 1 security disabled */
#define RES_INSECURE2   0x00000800 /* type 2 security disabled */
#define RES_NOALIASES   0x00001000 /* shuts off HOSTALIASES feature */
#define RES_USE_INET6   0x00002000 /* use/map IPv6 in gethostbyname() */
#define RES_ROTATE      0x00004000 /* rotate ns list after each query */
#define RES_NOCHECKNAME 0x00008000 /* do not check names for sanity (!IMPL) */
#define RES_KEEPTSIG    0x00010000 /* do not strip TSIG records */
#define RES_BLAST       0x00020000 /* blast all recursive servers */
#define RES_USEBSTRING  0x00040000 /* IPv6 reverse lookup with byte strings */
#define RES_NOIP6DOTINT 0x00080000 /* Do not use .ip6.int in IPv6 reverse lookup */
#define RES_USE_EDNS0   0x00100000 /* Use EDNS0.  */
#define RES_SNGLKUP     0x00200000 /* one outstanding request at a time */
#define RES_SNGLKUPREOP 0x00400000 /* -"-, but open new socket for each request */
#define RES_USE_DNSSEC 0x00800000  /* use DNSSEC using OK bit in OPT */
#define RES_NOTLDQUERY 0x01000000  /* Do not look up unqualified name as a TLD.  */
#define RES_DEFAULT     (RES_RECURSE | RES_DEFNAMES | RES_DNSRCH | RES_NOIP6DOTINT)

/* ??? */
#define RES_PRF_STATS  0x00000001
#define RES_PRF_UPDATE 0x00000002
#define RES_PRF_CLASS  0x00000004
#define RES_PRF_CMD    0x00000008
#define RES_PRF_QUES   0x00000010
#define RES_PRF_ANS    0x00000020
#define RES_PRF_AUTH   0x00000040
#define RES_PRF_ADD    0x00000080
#define RES_PRF_HEAD1  0x00000100
#define RES_PRF_HEAD2  0x00000200
#define RES_PRF_TTLID  0x00000400
#define RES_PRF_HEADX  0x00000800
#define RES_PRF_QUERY  0x00001000
#define RES_PRF_REPLY  0x00002000
#define RES_PRF_INIT   0x00004000

#ifdef __CC__
__SYSDECL_BEGIN

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
                             u_char const **__query, int *__querylen,
                             u_char *__ans, int __anssiz, int *__resplen);
typedef res_sendhookact
(__LIBKCALL *res_send_rhook)(struct sockaddr_in const *__ns,
                             u_char const *__query, int __querylen,
                             u_char *__ans, int __anssiz, int *__resplen);

typedef struct __res_state {
	int                retrans;               /* ??? */
	int                retry;                 /* ??? */
	u_long             options;               /* ??? */
	int                nscount;               /* ??? */
	struct sockaddr_in nsaddr_list[MAXNS];    /* ??? */
#define nsaddr         nsaddr_list[0]         /* ??? */
	u_short            id;                    /* ??? */
	__byte_t         __rs_pad1[2];            /* ... */
	char              *dnsrch[MAXDNSRCH + 1]; /* ??? */
	char               defdname[256];         /* ??? */
	u_long             pfcode;                /* ??? */
	unsigned int       ndots : 4;             /* ??? */
	unsigned int       nsort : 4;             /* ??? */
	unsigned int       ipv6_unavail : 1;      /* ??? */
	unsigned int       unused : 23;           /* ??? */
	struct {
		struct in_addr addr;                  /* ??? */
		u_int32_t      mask;                  /* ??? */
	} sort_list[MAXRESOLVSORT];               /* ??? */
#if __SIZEOF_POINTER__ >= 8
	__byte_t         __rs_pad2[4];            /* ... */
#endif /* __SIZEOF_POINTER__ >= 8 */
	res_send_qhook     qhook;                 /* ??? */
	res_send_rhook     rhook;                 /* ??? */
	int                res_h_errno;           /* ??? */
	int               _vcsock;                /* ??? */
	u_int             _flags;                 /* ??? */
#if __SIZEOF_POINTER__ >= 8
	__byte_t         __rs_pad3[4];            /* ... */
#endif /* __SIZEOF_POINTER__ >= 8 */
	union {
		char           pad[52]; /* ... */
		struct {
			u_int16_t            nscount;        /* ??? */
			u_int16_t            nsmap[MAXNS];   /* ??? */
			int                  nssocks[MAXNS]; /* ??? */
			u_int16_t            nscount6;       /* ??? */
			u_int16_t            nsinit;         /* ??? */
			struct sockaddr_in6 *nsaddrs[MAXNS]; /* ??? */
			__UINT32_TYPE__     _initstamp[2];   /* ??? */
		} _ext;
	} _u;
} *res_state;
#endif /* !__res_state_defined */

struct res_sym {
	int   number;    /* ??? */
	char *name;      /* ??? */
	char *humanname; /* ??? */
};

__CDECLARE_OPT(__ATTR_CONST,struct __res_state *,__NOTHROW_NCX,__res_state,(void),())
#ifdef __CRT_HAVE___res_state
#define _res (*__res_state())
#endif /* __CRT_HAVE___res_state */

#ifndef __BIND_NOSTATIC
#ifdef __CRT_HAVE_fp_nquery
__CDECLARE_VOID(,__NOTHROW_NCX,fp_nquery,(u_char const *__a, int __b, FILE *__c),(__a,__b,__c))
#elif defined(__CRT_HAVE___fp_nquery)
__CREDIRECT_VOID(,__NOTHROW_NCX,fp_nquery,(u_char const *__a, int __b, FILE *__c),__fp_nquery,(__a,__b,__c))
#endif /* ... */
#ifdef __CRT_HAVE_fp_query
__CDECLARE_VOID(,__NOTHROW_NCX,fp_query,(u_char const *__a, FILE *__b),(__a,__b))
#elif defined(__CRT_HAVE___fp_query)
__CREDIRECT_VOID(,__NOTHROW_NCX,fp_query,(u_char const *__a, FILE *__b),__fp_query,(__a,__b))
#endif /* ... */
#ifdef __CRT_HAVE_hostalias
__CDECLARE(,char const *,__NOTHROW_NCX,hostalias,(char const *__a),(__a))
#elif defined(__CRT_HAVE___hostalias)
__CREDIRECT(,char const *,__NOTHROW_NCX,hostalias,(char const *__a),__hostalias,(__a))
#endif /* ... */
#ifdef __CRT_HAVE_p_query
__CDECLARE_VOID(,__NOTHROW_NCX,p_query,(u_char const *__a),(__a))
#elif defined(__CRT_HAVE___p_query)
__CREDIRECT_VOID(,__NOTHROW_NCX,p_query,(u_char const *__a),__p_query,(__a))
#endif /* ... */
#ifdef __CRT_HAVE_res_close
__CDECLARE_VOID(,__NOTHROW_NCX,res_close,(void),())
#elif defined(__CRT_HAVE___res_close)
__CREDIRECT_VOID(,__NOTHROW_NCX,res_close,(void),__res_close,())
#endif /* ... */
#ifdef __CRT_HAVE_res_init
__CDECLARE(,int,__NOTHROW_NCX,res_init,(void),())
#elif defined(__CRT_HAVE___res_init)
__CREDIRECT(,int,__NOTHROW_NCX,res_init,(void),__res_init,())
#endif /* ... */
#ifdef __CRT_HAVE_res_isourserver
__CDECLARE(,int,__NOTHROW_NCX,res_isourserver,(struct sockaddr_in const *__a),(__a))
#elif defined(__CRT_HAVE___res_isourserver)
__CREDIRECT(,int,__NOTHROW_NCX,res_isourserver,(struct sockaddr_in const *__a),__res_isourserver,(__a))
#endif /* ... */
#ifdef __CRT_HAVE_res_mkquery
__CDECLARE(,int,__NOTHROW_NCX,res_mkquery,(int __a, char const *__b, int __c, int __d, u_char const *__e, int __f, u_char const *__g, u_char *__h, int __i),(__a,__b,__c,__d,__e,__f,__g,__h,__i))
#elif defined(__CRT_HAVE___res_mkquery)
__CREDIRECT(,int,__NOTHROW_NCX,res_mkquery,(int __a, char const *__b, int __c, int __d, u_char const *__e, int __f, u_char const *__g, u_char *__h, int __i),__res_mkquery,(__a,__b,__c,__d,__e,__f,__g,__h,__i))
#endif /* ... */
#ifdef __CRT_HAVE_res_query
__CDECLARE(,int,__NOTHROW_NCX,res_query,(char const *__a, int __b, int __c, u_char *__d, int __e),(__a,__b,__c,__d,__e))
#elif defined(__CRT_HAVE___res_query)
__CREDIRECT(,int,__NOTHROW_NCX,res_query,(char const *__a, int __b, int __c, u_char *__d, int __e),__res_query,(__a,__b,__c,__d,__e))
#endif /* ... */
#ifdef __CRT_HAVE_res_querydomain
__CDECLARE(,int,__NOTHROW_NCX,res_querydomain,(char const *__a, char const *__b, int __c, int __d, u_char *__e, int __f),(__a,__b,__c,__d,__e,__f))
#elif defined(__CRT_HAVE___res_querydomain)
__CREDIRECT(,int,__NOTHROW_NCX,res_querydomain,(char const *__a, char const *__b, int __c, int __d, u_char *__e, int __f),__res_querydomain,(__a,__b,__c,__d,__e,__f))
#endif /* ... */
#ifdef __CRT_HAVE_res_search
__CDECLARE(,int,__NOTHROW_NCX,res_search,(char const *__a, int __b, int __c, u_char *__d, int __e),(__a,__b,__c,__d,__e))
#elif defined(__CRT_HAVE___res_search)
__CREDIRECT(,int,__NOTHROW_NCX,res_search,(char const *__a, int __b, int __c, u_char *__d, int __e),__res_search,(__a,__b,__c,__d,__e))
#endif /* ... */
#ifdef __CRT_HAVE_res_send
__CDECLARE(,int,__NOTHROW_NCX,res_send,(u_char const *__a, int __b, u_char *__c, int __d),(__a,__b,__c,__d))
#elif defined(__CRT_HAVE___res_send)
__CREDIRECT(,int,__NOTHROW_NCX,res_send,(u_char const *__a, int __b, u_char *__c, int __d),__res_send,(__a,__b,__c,__d))
#endif /* ... */
#endif /* !__BIND_NOSTATIC */
#ifdef __CRT_HAVE_res_hnok
__CDECLARE(,int,__NOTHROW_NCX,res_hnok,(char const *__a),(__a))
#elif defined(__CRT_HAVE___res_hnok)
__CREDIRECT(,int,__NOTHROW_NCX,res_hnok,(char const *__a),__res_hnok,(__a))
#endif /* ... */
#ifdef __CRT_HAVE_res_ownok
__CDECLARE(,int,__NOTHROW_NCX,res_ownok,(char const *__a),(__a))
#elif defined(__CRT_HAVE___res_ownok)
__CREDIRECT(,int,__NOTHROW_NCX,res_ownok,(char const *__a),__res_ownok,(__a))
#endif /* ... */
#ifdef __CRT_HAVE_res_mailok
__CDECLARE(,int,__NOTHROW_NCX,res_mailok,(char const *__a),(__a))
#elif defined(__CRT_HAVE___res_mailok)
__CREDIRECT(,int,__NOTHROW_NCX,res_mailok,(char const *__a),__res_mailok,(__a))
#endif /* ... */
#ifdef __CRT_HAVE_res_dnok
__CDECLARE(,int,__NOTHROW_NCX,res_dnok,(char const *__a),(__a))
#elif defined(__CRT_HAVE___res_dnok)
__CREDIRECT(,int,__NOTHROW_NCX,res_dnok,(char const *__a),__res_dnok,(__a))
#endif /* ... */
#ifdef __CRT_HAVE_sym_ston
__CDECLARE(,int,__NOTHROW_NCX,sym_ston,(struct res_sym const *__a, char const *__b, int *__c),(__a,__b,__c))
#elif defined(__CRT_HAVE___sym_ston)
__CREDIRECT(,int,__NOTHROW_NCX,sym_ston,(struct res_sym const *__a, char const *__b, int *__c),__sym_ston,(__a,__b,__c))
#endif /* ... */
#ifdef __CRT_HAVE_sym_ntos
__CDECLARE(,char const *,__NOTHROW_NCX,sym_ntos,(struct res_sym const *__a, int __b, int *__c),(__a,__b,__c))
#elif defined(__CRT_HAVE___sym_ntos)
__CREDIRECT(,char const *,__NOTHROW_NCX,sym_ntos,(struct res_sym const *__a, int __b, int *__c),__sym_ntos,(__a,__b,__c))
#endif /* ... */
#ifdef __CRT_HAVE_sym_ntop
__CDECLARE(,char const *,__NOTHROW_NCX,sym_ntop,(struct res_sym const *__a, int __b, int *__c),(__a,__b,__c))
#elif defined(__CRT_HAVE___sym_ntop)
__CREDIRECT(,char const *,__NOTHROW_NCX,sym_ntop,(struct res_sym const *__a, int __b, int *__c),__sym_ntop,(__a,__b,__c))
#endif /* ... */
#ifdef __CRT_HAVE_b64_ntop
__CDECLARE(,int,__NOTHROW_NCX,b64_ntop,(u_char const *__a, size_t __b, char *__c, size_t __d),(__a,__b,__c,__d))
#elif defined(__CRT_HAVE___b64_ntop)
__CREDIRECT(,int,__NOTHROW_NCX,b64_ntop,(u_char const *__a, size_t __b, char *__c, size_t __d),__b64_ntop,(__a,__b,__c,__d))
#endif /* ... */
#ifdef __CRT_HAVE_b64_pton
__CDECLARE(,int,__NOTHROW_NCX,b64_pton,(char const *__a, u_char *__b, size_t __c),(__a,__b,__c))
#elif defined(__CRT_HAVE___b64_pton)
__CREDIRECT(,int,__NOTHROW_NCX,b64_pton,(char const *__a, u_char *__b, size_t __c),__b64_pton,(__a,__b,__c))
#endif /* ... */
#ifdef __CRT_HAVE_loc_aton
__CDECLARE(,int,__NOTHROW_NCX,loc_aton,(char const *__a, u_char *__b),(__a,__b))
#elif defined(__CRT_HAVE___loc_aton)
__CREDIRECT(,int,__NOTHROW_NCX,loc_aton,(char const *__a, u_char *__b),__loc_aton,(__a,__b))
#endif /* ... */
#ifdef __CRT_HAVE_loc_ntoa
__CDECLARE(,char const *,__NOTHROW_NCX,loc_ntoa,(u_char const *__a, char *__b),(__a,__b))
#elif defined(__CRT_HAVE___loc_ntoa)
__CREDIRECT(,char const *,__NOTHROW_NCX,loc_ntoa,(u_char const *__a, char *__b),__loc_ntoa,(__a,__b))
#endif /* ... */
#ifdef __CRT_HAVE_dn_skipname
__CDECLARE(,int,__NOTHROW_NCX,dn_skipname,(u_char const *__a, u_char const *__b),(__a,__b))
#elif defined(__CRT_HAVE___dn_skipname)
__CREDIRECT(,int,__NOTHROW_NCX,dn_skipname,(u_char const *__a, u_char const *__b),__dn_skipname,(__a,__b))
#endif /* ... */
#ifdef __CRT_HAVE_putlong
__CDECLARE_VOID(,__NOTHROW_NCX,putlong,(u_int32_t __a, u_char *__b),(__a,__b))
#elif defined(__CRT_HAVE___putlong)
__CREDIRECT_VOID(,__NOTHROW_NCX,putlong,(u_int32_t __a, u_char *__b),__putlong,(__a,__b))
#endif /* ... */
#ifdef __CRT_HAVE_putshort
__CDECLARE_VOID(,__NOTHROW_NCX,putshort,(u_int16_t __a, u_char *__b),(__a,__b))
#elif defined(__CRT_HAVE___putshort)
__CREDIRECT_VOID(,__NOTHROW_NCX,putshort,(u_int16_t __a, u_char *__b),__putshort,(__a,__b))
#endif /* ... */
#ifdef __CRT_HAVE_p_class
__CDECLARE(,char const *,__NOTHROW_NCX,p_class,(int __a),(__a))
#elif defined(__CRT_HAVE___p_class)
__CREDIRECT(,char const *,__NOTHROW_NCX,p_class,(int __a),__p_class,(__a))
#endif /* ... */
#ifdef __CRT_HAVE_p_time
__CDECLARE(,char const *,__NOTHROW_NCX,p_time,(u_int32_t __a),(__a))
#elif defined(__CRT_HAVE___p_time)
__CREDIRECT(,char const *,__NOTHROW_NCX,p_time,(u_int32_t __a),__p_time,(__a))
#endif /* ... */
#ifdef __CRT_HAVE_p_type
__CDECLARE(,char const *,__NOTHROW_NCX,p_type,(int __a),(__a))
#elif defined(__CRT_HAVE___p_type)
__CREDIRECT(,char const *,__NOTHROW_NCX,p_type,(int __a),__p_type,(__a))
#endif /* ... */
#ifdef __CRT_HAVE_p_rcode
__CDECLARE(,char const *,__NOTHROW_NCX,p_rcode,(int __a),(__a))
#elif defined(__CRT_HAVE___p_rcode)
__CREDIRECT(,char const *,__NOTHROW_NCX,p_rcode,(int __a),__p_rcode,(__a))
#endif /* ... */
#ifdef __CRT_HAVE_p_cdnname
__CDECLARE(,u_char const *,__NOTHROW_NCX,p_cdnname,(u_char const *__a, u_char const *__b, int __c, FILE *__d),(__a,__b,__c,__d))
#elif defined(__CRT_HAVE___p_cdnname)
__CREDIRECT(,u_char const *,__NOTHROW_NCX,p_cdnname,(u_char const *__a, u_char const *__b, int __c, FILE *__d),__p_cdnname,(__a,__b,__c,__d))
#endif /* ... */
#ifdef __CRT_HAVE_p_cdname
__CDECLARE(,u_char const *,__NOTHROW_NCX,p_cdname,(u_char const *__a, u_char const *__b, FILE *__c),(__a,__b,__c))
#elif defined(__CRT_HAVE___p_cdname)
__CREDIRECT(,u_char const *,__NOTHROW_NCX,p_cdname,(u_char const *__a, u_char const *__b, FILE *__c),__p_cdname,(__a,__b,__c))
#endif /* ... */
#ifdef __CRT_HAVE_p_fqnname
__CDECLARE(,u_char const *,__NOTHROW_NCX,p_fqnname,(u_char const *__a, u_char const *__b, int __c, char *__d, int __e),(__a,__b,__c,__d,__e))
#elif defined(__CRT_HAVE___p_fqnname)
__CREDIRECT(,u_char const *,__NOTHROW_NCX,p_fqnname,(u_char const *__a, u_char const *__b, int __c, char *__d, int __e),__p_fqnname,(__a,__b,__c,__d,__e))
#endif /* ... */
#ifdef __CRT_HAVE_p_fqname
__CDECLARE(,u_char const *,__NOTHROW_NCX,p_fqname,(u_char const *__a, u_char const *__b, FILE *__c),(__a,__b,__c))
#elif defined(__CRT_HAVE___p_fqname)
__CREDIRECT(,u_char const *,__NOTHROW_NCX,p_fqname,(u_char const *__a, u_char const *__b, FILE *__c),__p_fqname,(__a,__b,__c))
#endif /* ... */
#ifdef __CRT_HAVE_p_option
__CDECLARE(,char const *,__NOTHROW_NCX,p_option,(u_long __a),(__a))
#elif defined(__CRT_HAVE___p_option)
__CREDIRECT(,char const *,__NOTHROW_NCX,p_option,(u_long __a),__p_option,(__a))
#endif /* ... */
#ifdef __CRT_HAVE_p_secstodate
__CDECLARE(,char *,__NOTHROW_NCX,p_secstodate,(u_long __a),(__a))
#elif defined(__CRT_HAVE___p_secstodate)
__CREDIRECT(,char *,__NOTHROW_NCX,p_secstodate,(u_long __a),__p_secstodate,(__a))
#endif /* ... */
#ifdef __CRT_HAVE_dn_count_labels
__CDECLARE(,int,__NOTHROW_NCX,dn_count_labels,(char const *__a),(__a))
#elif defined(__CRT_HAVE___dn_count_labels)
__CREDIRECT(,int,__NOTHROW_NCX,dn_count_labels,(char const *__a),__dn_count_labels,(__a))
#endif /* ... */
#ifdef __CRT_HAVE_dn_comp
__CDECLARE(,int,__NOTHROW_NCX,dn_comp,(char const *__a, u_char *__b, int __c, u_char **__d, u_char **__e),(__a,__b,__c,__d,__e))
#elif defined(__CRT_HAVE___dn_comp)
__CREDIRECT(,int,__NOTHROW_NCX,dn_comp,(char const *__a, u_char *__b, int __c, u_char **__d, u_char **__e),__dn_comp,(__a,__b,__c,__d,__e))
#endif /* ... */
#ifdef __CRT_HAVE_dn_expand
__CDECLARE(,int,__NOTHROW_NCX,dn_expand,(u_char const *__a, u_char const *__b, u_char const *__c, char *__d, int __e),(__a,__b,__c,__d,__e))
#elif defined(__CRT_HAVE___dn_expand)
__CREDIRECT(,int,__NOTHROW_NCX,dn_expand,(u_char const *__a, u_char const *__b, u_char const *__c, char *__d, int __e),__dn_expand,(__a,__b,__c,__d,__e))
#endif /* ... */
#ifdef __CRT_HAVE_res_randomid
__CDECLARE(,u_int,__NOTHROW_NCX,res_randomid,(void),())
#elif defined(__CRT_HAVE___res_randomid)
__CREDIRECT(,u_int,__NOTHROW_NCX,res_randomid,(void),__res_randomid,())
#endif /* ... */
#ifdef __CRT_HAVE_res_nameinquery
__CDECLARE(,int,__NOTHROW_NCX,res_nameinquery,(char const *__a, int __b, int __c, u_char const *__d, u_char const *__e),(__a,__b,__c,__d,__e))
#elif defined(__CRT_HAVE___res_nameinquery)
__CREDIRECT(,int,__NOTHROW_NCX,res_nameinquery,(char const *__a, int __b, int __c, u_char const *__d, u_char const *__e),__res_nameinquery,(__a,__b,__c,__d,__e))
#endif /* ... */
#ifdef __CRT_HAVE_res_queriesmatch
__CDECLARE(,int,__NOTHROW_NCX,res_queriesmatch,(u_char const *__a, u_char const *__b, u_char const *__c, u_char const *__d),(__a,__b,__c,__d))
#elif defined(__CRT_HAVE___res_queriesmatch)
__CREDIRECT(,int,__NOTHROW_NCX,res_queriesmatch,(u_char const *__a, u_char const *__b, u_char const *__c, u_char const *__d),__res_queriesmatch,(__a,__b,__c,__d))
#endif /* ... */
#ifdef __CRT_HAVE_p_section
__CDECLARE(,char const *,__NOTHROW_NCX,p_section,(int __a, int __b),(__a,__b))
#elif defined(__CRT_HAVE___p_section)
__CREDIRECT(,char const *,__NOTHROW_NCX,p_section,(int __a, int __b),__p_section,(__a,__b))
#endif /* ... */
#ifdef __CRT_HAVE_res_ninit
__CDECLARE(,int,__NOTHROW_NCX,res_ninit,(res_state __a),(__a))
#elif defined(__CRT_HAVE___res_ninit)
__CREDIRECT(,int,__NOTHROW_NCX,res_ninit,(res_state __a),__res_ninit,(__a))
#endif /* ... */
#ifdef __CRT_HAVE_res_nisourserver
__CDECLARE(,int,__NOTHROW_NCX,res_nisourserver,(res_state __a, struct sockaddr_in const *__b),(__a,__b))
#elif defined(__CRT_HAVE___res_nisourserver)
__CREDIRECT(,int,__NOTHROW_NCX,res_nisourserver,(res_state __a, struct sockaddr_in const *__b),__res_nisourserver,(__a,__b))
#endif /* ... */
#ifdef __CRT_HAVE_fp_resstat
__CDECLARE_VOID(,__NOTHROW_NCX,fp_resstat,(res_state __a, FILE *__b),(__a,__b))
#elif defined(__CRT_HAVE___fp_resstat)
__CREDIRECT_VOID(,__NOTHROW_NCX,fp_resstat,(res_state __a, FILE *__b),__fp_resstat,(__a,__b))
#endif /* ... */
#ifdef __CRT_HAVE_res_npquery
__CDECLARE_VOID(,__NOTHROW_NCX,res_npquery,(res_state __a, u_char const *__b, int __c, FILE *__d),(__a,__b,__c,__d))
#elif defined(__CRT_HAVE___res_npquery)
__CREDIRECT_VOID(,__NOTHROW_NCX,res_npquery,(res_state __a, u_char const *__b, int __c, FILE *__d),__res_npquery,(__a,__b,__c,__d))
#endif /* ... */
#ifdef __CRT_HAVE_res_hostalias
__CDECLARE(,char const *,__NOTHROW_NCX,res_hostalias,(res_state __a, char const *__b, char *__c, size_t __d),(__a,__b,__c,__d))
#elif defined(__CRT_HAVE___res_hostalias)
__CREDIRECT(,char const *,__NOTHROW_NCX,res_hostalias,(res_state __a, char const *__b, char *__c, size_t __d),__res_hostalias,(__a,__b,__c,__d))
#endif /* ... */
#ifdef __CRT_HAVE_res_nquery
__CDECLARE(,int,__NOTHROW_NCX,res_nquery,(res_state __a, char const *__b, int __c, int __d, u_char *__e, int __f),(__a,__b,__c,__d,__e,__f))
#elif defined(__CRT_HAVE___res_nquery)
__CREDIRECT(,int,__NOTHROW_NCX,res_nquery,(res_state __a, char const *__b, int __c, int __d, u_char *__e, int __f),__res_nquery,(__a,__b,__c,__d,__e,__f))
#endif /* ... */
#ifdef __CRT_HAVE_res_nsearch
__CDECLARE(,int,__NOTHROW_NCX,res_nsearch,(res_state __a, char const *__b, int __c, int __d, u_char *__e, int __f),(__a,__b,__c,__d,__e,__f))
#elif defined(__CRT_HAVE___res_nsearch)
__CREDIRECT(,int,__NOTHROW_NCX,res_nsearch,(res_state __a, char const *__b, int __c, int __d, u_char *__e, int __f),__res_nsearch,(__a,__b,__c,__d,__e,__f))
#endif /* ... */
#ifdef __CRT_HAVE_res_nquerydomain
__CDECLARE(,int,__NOTHROW_NCX,res_nquerydomain,(res_state __a, char const *__b, char const *__c, int __d, int __e, u_char *__f, int __g),(__a,__b,__c,__d,__e,__f,__g))
#elif defined(__CRT_HAVE___res_nquerydomain)
__CREDIRECT(,int,__NOTHROW_NCX,res_nquerydomain,(res_state __a, char const *__b, char const *__c, int __d, int __e, u_char *__f, int __g),__res_nquerydomain,(__a,__b,__c,__d,__e,__f,__g))
#endif /* ... */
#ifdef __CRT_HAVE_res_nmkquery
__CDECLARE(,int,__NOTHROW_NCX,res_nmkquery,(res_state __a, int __b, char const *__c, int __d, int __e, u_char const *__f, int __g, u_char const *__h, u_char *__i, int __j),(__a,__b,__c,__d,__e,__f,__g,__h,__i,__j))
#elif defined(__CRT_HAVE___res_nmkquery)
__CREDIRECT(,int,__NOTHROW_NCX,res_nmkquery,(res_state __a, int __b, char const *__c, int __d, int __e, u_char const *__f, int __g, u_char const *__h, u_char *__i, int __j),__res_nmkquery,(__a,__b,__c,__d,__e,__f,__g,__h,__i,__j))
#endif /* ... */
#ifdef __CRT_HAVE_res_nsend
__CDECLARE(,int,__NOTHROW_NCX,res_nsend,(res_state __a, u_char const *__b, int __c, u_char *__d, int __e),(__a,__b,__c,__d,__e))
#elif defined(__CRT_HAVE___res_nsend)
__CREDIRECT(,int,__NOTHROW_NCX,res_nsend,(res_state __a, u_char const *__b, int __c, u_char *__d, int __e),__res_nsend,(__a,__b,__c,__d,__e))
#endif /* ... */
#ifdef __CRT_HAVE_res_nclose
__CDECLARE_VOID(,__NOTHROW_NCX,res_nclose,(res_state __a),(__a))
#elif defined(__CRT_HAVE___res_nclose)
__CREDIRECT_VOID(,__NOTHROW_NCX,res_nclose,(res_state __a),__res_nclose,(__a))
#endif /* ... */

/* Underscore aliases */
#ifndef __BIND_NOSTATIC
#if defined(__CRT_HAVE_fp_nquery) || defined(__CRT_HAVE___fp_nquery)
#define __fp_nquery fp_nquery
#endif /* __CRT_HAVE_fp_nquery || __CRT_HAVE___fp_nquery */
#if defined(__CRT_HAVE_fp_query) || defined(__CRT_HAVE___fp_query)
#define __fp_query fp_query
#endif /* __CRT_HAVE_fp_query || __CRT_HAVE___fp_query */
#if defined(__CRT_HAVE_hostalias) || defined(__CRT_HAVE___hostalias)
#define __hostalias hostalias
#endif /* __CRT_HAVE_hostalias || __CRT_HAVE___hostalias */
#if defined(__CRT_HAVE_p_query) || defined(__CRT_HAVE___p_query)
#define __p_query p_query
#endif /* __CRT_HAVE_p_query || __CRT_HAVE___p_query */
#if defined(__CRT_HAVE_res_close) || defined(__CRT_HAVE___res_close)
#define __res_close res_close
#endif /* __CRT_HAVE_res_close || __CRT_HAVE___res_close */
#if defined(__CRT_HAVE_res_init) || defined(__CRT_HAVE___res_init)
#define __res_init res_init
#endif /* __CRT_HAVE_res_init || __CRT_HAVE___res_init */
#if defined(__CRT_HAVE_res_isourserver) || defined(__CRT_HAVE___res_isourserver)
#define __res_isourserver res_isourserver
#endif /* __CRT_HAVE_res_isourserver || __CRT_HAVE___res_isourserver */
#if defined(__CRT_HAVE_res_mkquery) || defined(__CRT_HAVE___res_mkquery)
#define __res_mkquery res_mkquery
#endif /* __CRT_HAVE_res_mkquery || __CRT_HAVE___res_mkquery */
#if defined(__CRT_HAVE_res_query) || defined(__CRT_HAVE___res_query)
#define __res_query res_query
#endif /* __CRT_HAVE_res_query || __CRT_HAVE___res_query */
#if defined(__CRT_HAVE_res_querydomain) || defined(__CRT_HAVE___res_querydomain)
#define __res_querydomain res_querydomain
#endif /* __CRT_HAVE_res_querydomain || __CRT_HAVE___res_querydomain */
#if defined(__CRT_HAVE_res_search) || defined(__CRT_HAVE___res_search)
#define __res_search res_search
#endif /* __CRT_HAVE_res_search || __CRT_HAVE___res_search */
#if defined(__CRT_HAVE_res_send) || defined(__CRT_HAVE___res_send)
#define __res_send res_send
#endif /* __CRT_HAVE_res_send || __CRT_HAVE___res_send */
#endif /* !__BIND_NOSTATIC */
#if defined(__CRT_HAVE_b64_ntop) || defined(__CRT_HAVE___b64_ntop)
#define __b64_ntop b64_ntop
#endif /* __CRT_HAVE_b64_ntop || __CRT_HAVE___b64_ntop */
#if defined(__CRT_HAVE_b64_pton) || defined(__CRT_HAVE___b64_pton)
#define __b64_pton b64_pton
#endif /* __CRT_HAVE_b64_pton || __CRT_HAVE___b64_pton */
#if defined(__CRT_HAVE_dn_comp) || defined(__CRT_HAVE___dn_comp)
#define __dn_comp dn_comp
#endif /* __CRT_HAVE_dn_comp || __CRT_HAVE___dn_comp */
#if defined(__CRT_HAVE_dn_count_labels) || defined(__CRT_HAVE___dn_count_labels)
#define __dn_count_labels dn_count_labels
#endif /* __CRT_HAVE_dn_count_labels || __CRT_HAVE___dn_count_labels */
#if defined(__CRT_HAVE_dn_expand) || defined(__CRT_HAVE___dn_expand)
#define __dn_expand dn_expand
#endif /* __CRT_HAVE_dn_expand || __CRT_HAVE___dn_expand */
#if defined(__CRT_HAVE_dn_skipname) || defined(__CRT_HAVE___dn_skipname)
#define __dn_skipname dn_skipname
#endif /* __CRT_HAVE_dn_skipname || __CRT_HAVE___dn_skipname */
#if defined(__CRT_HAVE_fp_resstat) || defined(__CRT_HAVE___fp_resstat)
#define __fp_resstat fp_resstat
#endif /* __CRT_HAVE_fp_resstat || __CRT_HAVE___fp_resstat */
#if defined(__CRT_HAVE_loc_aton) || defined(__CRT_HAVE___loc_aton)
#define __loc_aton loc_aton
#endif /* __CRT_HAVE_loc_aton || __CRT_HAVE___loc_aton */
#if defined(__CRT_HAVE_loc_ntoa) || defined(__CRT_HAVE___loc_ntoa)
#define __loc_ntoa loc_ntoa
#endif /* __CRT_HAVE_loc_ntoa || __CRT_HAVE___loc_ntoa */
#if defined(__CRT_HAVE_p_cdname) || defined(__CRT_HAVE___p_cdname)
#define __p_cdname p_cdname
#endif /* __CRT_HAVE_p_cdname || __CRT_HAVE___p_cdname */
#if defined(__CRT_HAVE_p_cdnname) || defined(__CRT_HAVE___p_cdnname)
#define __p_cdnname p_cdnname
#endif /* __CRT_HAVE_p_cdnname || __CRT_HAVE___p_cdnname */
#if defined(__CRT_HAVE_p_class) || defined(__CRT_HAVE___p_class)
#define __p_class p_class
#endif /* __CRT_HAVE_p_class || __CRT_HAVE___p_class */
#if defined(__CRT_HAVE_p_fqname) || defined(__CRT_HAVE___p_fqname)
#define __p_fqname p_fqname
#endif /* __CRT_HAVE_p_fqname || __CRT_HAVE___p_fqname */
#if defined(__CRT_HAVE_p_fqnname) || defined(__CRT_HAVE___p_fqnname)
#define __p_fqnname p_fqnname
#endif /* __CRT_HAVE_p_fqnname || __CRT_HAVE___p_fqnname */
#if defined(__CRT_HAVE_p_option) || defined(__CRT_HAVE___p_option)
#define __p_option p_option
#endif /* __CRT_HAVE_p_option || __CRT_HAVE___p_option */
#if defined(__CRT_HAVE_p_secstodate) || defined(__CRT_HAVE___p_secstodate)
#define __p_secstodate p_secstodate
#endif /* __CRT_HAVE_p_secstodate || __CRT_HAVE___p_secstodate */
#if defined(__CRT_HAVE_p_section) || defined(__CRT_HAVE___p_section)
#define __p_section p_section
#endif /* __CRT_HAVE_p_section || __CRT_HAVE___p_section */
#if defined(__CRT_HAVE_p_time) || defined(__CRT_HAVE___p_time)
#define __p_time p_time
#endif /* __CRT_HAVE_p_time || __CRT_HAVE___p_time */
#if defined(__CRT_HAVE_p_type) || defined(__CRT_HAVE___p_type)
#define __p_type p_type
#endif /* __CRT_HAVE_p_type || __CRT_HAVE___p_type */
#if defined(__CRT_HAVE_p_rcode) || defined(__CRT_HAVE___p_rcode)
#define __p_rcode p_rcode
#endif /* __CRT_HAVE_p_rcode || __CRT_HAVE___p_rcode */
#if defined(__CRT_HAVE_putlong) || defined(__CRT_HAVE___putlong)
#define __putlong putlong
#endif /* __CRT_HAVE_putlong || __CRT_HAVE___putlong */
#if defined(__CRT_HAVE_putshort) || defined(__CRT_HAVE___putshort)
#define __putshort putshort
#endif /* __CRT_HAVE_putshort || __CRT_HAVE___putshort */
#if defined(__CRT_HAVE_res_dnok) || defined(__CRT_HAVE___res_dnok)
#define __res_dnok res_dnok
#endif /* __CRT_HAVE_res_dnok || __CRT_HAVE___res_dnok */
#if defined(__CRT_HAVE_res_hnok) || defined(__CRT_HAVE___res_hnok)
#define __res_hnok res_hnok
#endif /* __CRT_HAVE_res_hnok || __CRT_HAVE___res_hnok */
#if defined(__CRT_HAVE_res_hostalias) || defined(__CRT_HAVE___res_hostalias)
#define __res_hostalias res_hostalias
#endif /* __CRT_HAVE_res_hostalias || __CRT_HAVE___res_hostalias */
#if defined(__CRT_HAVE_res_mailok) || defined(__CRT_HAVE___res_mailok)
#define __res_mailok res_mailok
#endif /* __CRT_HAVE_res_mailok || __CRT_HAVE___res_mailok */
#if defined(__CRT_HAVE_res_nameinquery) || defined(__CRT_HAVE___res_nameinquery)
#define __res_nameinquery res_nameinquery
#endif /* __CRT_HAVE_res_nameinquery || __CRT_HAVE___res_nameinquery */
#if defined(__CRT_HAVE_res_nclose) || defined(__CRT_HAVE___res_nclose)
#define __res_nclose res_nclose
#endif /* __CRT_HAVE_res_nclose || __CRT_HAVE___res_nclose */
#if defined(__CRT_HAVE_res_ninit) || defined(__CRT_HAVE___res_ninit)
#define __res_ninit res_ninit
#endif /* __CRT_HAVE_res_ninit || __CRT_HAVE___res_ninit */
#if defined(__CRT_HAVE_res_nmkquery) || defined(__CRT_HAVE___res_nmkquery)
#define __res_nmkquery res_nmkquery
#endif /* __CRT_HAVE_res_nmkquery || __CRT_HAVE___res_nmkquery */
#if defined(__CRT_HAVE_res_npquery) || defined(__CRT_HAVE___res_npquery)
#define __res_npquery res_npquery
#endif /* __CRT_HAVE_res_npquery || __CRT_HAVE___res_npquery */
#if defined(__CRT_HAVE_res_nquery) || defined(__CRT_HAVE___res_nquery)
#define __res_nquery res_nquery
#endif /* __CRT_HAVE_res_nquery || __CRT_HAVE___res_nquery */
#if defined(__CRT_HAVE_res_nquerydomain) || defined(__CRT_HAVE___res_nquerydomain)
#define __res_nquerydomain res_nquerydomain
#endif /* __CRT_HAVE_res_nquerydomain || __CRT_HAVE___res_nquerydomain */
#if defined(__CRT_HAVE_res_nsearch) || defined(__CRT_HAVE___res_nsearch)
#define __res_nsearch res_nsearch
#endif /* __CRT_HAVE_res_nsearch || __CRT_HAVE___res_nsearch */
#if defined(__CRT_HAVE_res_nsend) || defined(__CRT_HAVE___res_nsend)
#define __res_nsend res_nsend
#endif /* __CRT_HAVE_res_nsend || __CRT_HAVE___res_nsend */
#if defined(__CRT_HAVE_res_nisourserver) || defined(__CRT_HAVE___res_nisourserver)
#define __res_nisourserver res_nisourserver
#endif /* __CRT_HAVE_res_nisourserver || __CRT_HAVE___res_nisourserver */
#if defined(__CRT_HAVE_res_ownok) || defined(__CRT_HAVE___res_ownok)
#define __res_ownok res_ownok
#endif /* __CRT_HAVE_res_ownok || __CRT_HAVE___res_ownok */
#if defined(__CRT_HAVE_res_queriesmatch) || defined(__CRT_HAVE___res_queriesmatch)
#define __res_queriesmatch res_queriesmatch
#endif /* __CRT_HAVE_res_queriesmatch || __CRT_HAVE___res_queriesmatch */
#if defined(__CRT_HAVE_res_randomid) || defined(__CRT_HAVE___res_randomid)
#define __res_randomid res_randomid
#endif /* __CRT_HAVE_res_randomid || __CRT_HAVE___res_randomid */
#if defined(__CRT_HAVE_sym_ntop) || defined(__CRT_HAVE___sym_ntop)
#define __sym_ntop sym_ntop
#endif /* __CRT_HAVE_sym_ntop || __CRT_HAVE___sym_ntop */
#if defined(__CRT_HAVE_sym_ntos) || defined(__CRT_HAVE___sym_ntos)
#define __sym_ntos sym_ntos
#endif /* __CRT_HAVE_sym_ntos || __CRT_HAVE___sym_ntos */
#if defined(__CRT_HAVE_sym_ston) || defined(__CRT_HAVE___sym_ston)
#define __sym_ston sym_ston
#endif /* __CRT_HAVE_sym_ston || __CRT_HAVE___sym_ston */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_RESOLV_H */
