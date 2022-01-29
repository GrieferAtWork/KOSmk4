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
%(c_prefix){
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
}

%[default:section(".text.crt{|.dos}.net.nameser")]
%[define_replacement(fd_t = __fd_t)]

%[insert:prefix(
#include <features.h>
)]%{

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

}


%[define_replacement(res_send_qhook = res_send_qhook)]
%[define_replacement(res_send_rhook = res_send_rhook)]
%[define_type_class(res_send_qhook = "TP")]
%[define_type_class(res_send_rhook = "TP")]
%[define_type_class(res_state = "TP")]
%[define_replacement(res_state = "struct __res_state *")]


[[const]] struct __res_state *__res_state(void);
%[insert:pp_if($has_function(__res_state))]
%#define _res (*__res_state())
%[insert:pp_endif]

%
%#ifndef __BIND_NOSTATIC
[[export_alias("__fp_nquery")]] void fp_nquery(u_char const *a, int b, FILE *c);
[[export_alias("__fp_query")]] void fp_query(u_char const *a, FILE *b);
[[export_alias("__hostalias")]] char const *hostalias(char const *a);
[[export_alias("__p_query")]] void p_query(u_char const *a);
[[export_alias("__res_close")]] void res_close(void);
[[export_alias("__res_init")]] int res_init(void);
[[export_alias("__res_isourserver")]] int res_isourserver(struct sockaddr_in const *a);
[[export_alias("__res_mkquery")]] int res_mkquery(int a, char const *b, int c, int d, u_char const *e, int f, u_char const *g, u_char *h, int i);
[[export_alias("__res_query")]] int res_query(char const *a, int b, int c, u_char *d, int e);
[[export_alias("__res_querydomain")]] int res_querydomain(char const *a, char const *b, int c, int d, u_char *e, int f);
[[export_alias("__res_search")]] int res_search(char const *a, int b, int c, u_char *d, int e);
[[export_alias("__res_send")]] int res_send(u_char const *a, int b, u_char *c, int d);
%#endif /* !__BIND_NOSTATIC */

[[export_alias("__res_hnok")]] int res_hnok(char const *a);
[[export_alias("__res_ownok")]] int res_ownok(char const *a);
[[export_alias("__res_mailok")]] int res_mailok(char const *a);
[[export_alias("__res_dnok")]] int res_dnok(char const *a);
[[export_alias("__sym_ston")]] int sym_ston(struct res_sym const *a, char const *b, int *c);
[[export_alias("__sym_ntos")]] char const *sym_ntos(struct res_sym const *a, int b, int *c);
[[export_alias("__sym_ntop")]] char const *sym_ntop(struct res_sym const *a, int b, int *c);
[[export_alias("__b64_ntop")]] int b64_ntop(u_char const *a, size_t b, char *c, size_t d);
[[export_alias("__b64_pton")]] int b64_pton(char const *a, u_char *b, size_t c);
[[export_alias("__loc_aton")]] int loc_aton(char const *a, u_char *b);
[[export_alias("__loc_ntoa")]] char const *loc_ntoa(u_char const *a, char *b);
[[export_alias("__dn_skipname")]] int dn_skipname(u_char const *a, u_char const *b);
[[export_alias("__putlong")]] void putlong(u_int32_t a, u_char *b);
[[export_alias("__putshort")]] void putshort(u_int16_t a, u_char *b);
[[export_alias("__p_class")]] char const *p_class(int a);
[[export_alias("__p_time")]] char const *p_time(u_int32_t a);
[[export_alias("__p_type")]] char const *p_type(int a);
[[export_alias("__p_rcode")]] char const *p_rcode(int a);
[[export_alias("__p_cdnname")]] u_char const *p_cdnname(u_char const *a, u_char const *b, int c, FILE *d);
[[export_alias("__p_cdname")]] u_char const *p_cdname(u_char const *a, u_char const *b, FILE *c);
[[export_alias("__p_fqnname")]] u_char const *p_fqnname(u_char const *a, u_char const *b, int c, char *d, int e);
[[export_alias("__p_fqname")]] u_char const *p_fqname(u_char const *a, u_char const *b, FILE *c);
[[export_alias("__p_option")]] char const *p_option(u_long a);
[[export_alias("__p_secstodate")]] char *p_secstodate(u_long a);
[[export_alias("__dn_count_labels")]] int dn_count_labels(char const *a);
[[export_alias("__dn_comp")]] int dn_comp(char const *a, u_char *b, int c, u_char **d, u_char **e);
[[export_alias("__dn_expand")]] int dn_expand(u_char const *a, u_char const *b, u_char const *c, char *d, int e);
[[export_alias("__res_randomid")]] u_int res_randomid(void);
[[export_alias("__res_nameinquery")]] int res_nameinquery(char const *a, int b, int c, u_char const *d, u_char const *e);
[[export_alias("__res_queriesmatch")]] int res_queriesmatch(u_char const *a, u_char const *b, u_char const *c, u_char const *d);
[[export_alias("__p_section")]] char const *p_section(int a, int b);
[[export_alias("__res_ninit")]] int res_ninit(res_state a);
[[export_alias("__res_nisourserver")]] int res_nisourserver(res_state a, struct sockaddr_in const *b);
[[export_alias("__fp_resstat")]] void fp_resstat(res_state a, FILE *b);
[[export_alias("__res_npquery")]] void res_npquery(res_state a, u_char const *b, int c, FILE *d);
[[export_alias("__res_hostalias")]] char const *res_hostalias(res_state a, char const *b, char *c, size_t d);
[[export_alias("__res_nquery")]] int res_nquery(res_state a, char const *b, int c, int d, u_char *e, int f);
[[export_alias("__res_nsearch")]] int res_nsearch(res_state a, char const *b, int c, int d, u_char *e, int f);
[[export_alias("__res_nquerydomain")]] int res_nquerydomain(res_state a, char const *b, char const *c, int d, int e, u_char *f, int g);
[[export_alias("__res_nmkquery")]] int res_nmkquery(res_state a, int b, char const *c, int d, int e, u_char const *f, int g, u_char const *h, u_char *i, int j);
[[export_alias("__res_nsend")]] int res_nsend(res_state a, u_char const *b, int c, u_char *d, int e);
[[export_alias("__res_nclose")]] void res_nclose(res_state a);


%
%/* Underscore aliases */
%#ifndef __BIND_NOSTATIC
%[insert:pp_if($has_function(fp_nquery))]
%#define __fp_nquery fp_nquery
%[insert:pp_endif]
%[insert:pp_if($has_function(fp_query))]
%#define __fp_query fp_query
%[insert:pp_endif]
%[insert:pp_if($has_function(hostalias))]
%#define __hostalias hostalias
%[insert:pp_endif]
%[insert:pp_if($has_function(p_query))]
%#define __p_query p_query
%[insert:pp_endif]
%[insert:pp_if($has_function(res_close))]
%#define __res_close res_close
%[insert:pp_endif]
%[insert:pp_if($has_function(res_init))]
%#define __res_init res_init
%[insert:pp_endif]
%[insert:pp_if($has_function(res_isourserver))]
%#define __res_isourserver res_isourserver
%[insert:pp_endif]
%[insert:pp_if($has_function(res_mkquery))]
%#define __res_mkquery res_mkquery
%[insert:pp_endif]
%[insert:pp_if($has_function(res_query))]
%#define __res_query res_query
%[insert:pp_endif]
%[insert:pp_if($has_function(res_querydomain))]
%#define __res_querydomain res_querydomain
%[insert:pp_endif]
%[insert:pp_if($has_function(res_search))]
%#define __res_search res_search
%[insert:pp_endif]
%[insert:pp_if($has_function(res_send))]
%#define __res_send res_send
%[insert:pp_endif]
%#endif /* !__BIND_NOSTATIC */
%[insert:pp_if($has_function(b64_ntop))]
%#define __b64_ntop b64_ntop
%[insert:pp_endif]
%[insert:pp_if($has_function(b64_pton))]
%#define __b64_pton b64_pton
%[insert:pp_endif]
%[insert:pp_if($has_function(dn_comp))]
%#define __dn_comp dn_comp
%[insert:pp_endif]
%[insert:pp_if($has_function(dn_count_labels))]
%#define __dn_count_labels dn_count_labels
%[insert:pp_endif]
%[insert:pp_if($has_function(dn_expand))]
%#define __dn_expand dn_expand
%[insert:pp_endif]
%[insert:pp_if($has_function(dn_skipname))]
%#define __dn_skipname dn_skipname
%[insert:pp_endif]
%[insert:pp_if($has_function(fp_resstat))]
%#define __fp_resstat fp_resstat
%[insert:pp_endif]
%[insert:pp_if($has_function(loc_aton))]
%#define __loc_aton loc_aton
%[insert:pp_endif]
%[insert:pp_if($has_function(loc_ntoa))]
%#define __loc_ntoa loc_ntoa
%[insert:pp_endif]
%[insert:pp_if($has_function(p_cdname))]
%#define __p_cdname p_cdname
%[insert:pp_endif]
%[insert:pp_if($has_function(p_cdnname))]
%#define __p_cdnname p_cdnname
%[insert:pp_endif]
%[insert:pp_if($has_function(p_class))]
%#define __p_class p_class
%[insert:pp_endif]
%[insert:pp_if($has_function(p_fqname))]
%#define __p_fqname p_fqname
%[insert:pp_endif]
%[insert:pp_if($has_function(p_fqnname))]
%#define __p_fqnname p_fqnname
%[insert:pp_endif]
%[insert:pp_if($has_function(p_option))]
%#define __p_option p_option
%[insert:pp_endif]
%[insert:pp_if($has_function(p_secstodate))]
%#define __p_secstodate p_secstodate
%[insert:pp_endif]
%[insert:pp_if($has_function(p_section))]
%#define __p_section p_section
%[insert:pp_endif]
%[insert:pp_if($has_function(p_time))]
%#define __p_time p_time
%[insert:pp_endif]
%[insert:pp_if($has_function(p_type))]
%#define __p_type p_type
%[insert:pp_endif]
%[insert:pp_if($has_function(p_rcode))]
%#define __p_rcode p_rcode
%[insert:pp_endif]
%[insert:pp_if($has_function(putlong))]
%#define __putlong putlong
%[insert:pp_endif]
%[insert:pp_if($has_function(putshort))]
%#define __putshort putshort
%[insert:pp_endif]
%[insert:pp_if($has_function(res_dnok))]
%#define __res_dnok res_dnok
%[insert:pp_endif]
%[insert:pp_if($has_function(res_hnok))]
%#define __res_hnok res_hnok
%[insert:pp_endif]
%[insert:pp_if($has_function(res_hostalias))]
%#define __res_hostalias res_hostalias
%[insert:pp_endif]
%[insert:pp_if($has_function(res_mailok))]
%#define __res_mailok res_mailok
%[insert:pp_endif]
%[insert:pp_if($has_function(res_nameinquery))]
%#define __res_nameinquery res_nameinquery
%[insert:pp_endif]
%[insert:pp_if($has_function(res_nclose))]
%#define __res_nclose res_nclose
%[insert:pp_endif]
%[insert:pp_if($has_function(res_ninit))]
%#define __res_ninit res_ninit
%[insert:pp_endif]
%[insert:pp_if($has_function(res_nmkquery))]
%#define __res_nmkquery res_nmkquery
%[insert:pp_endif]
%[insert:pp_if($has_function(res_npquery))]
%#define __res_npquery res_npquery
%[insert:pp_endif]
%[insert:pp_if($has_function(res_nquery))]
%#define __res_nquery res_nquery
%[insert:pp_endif]
%[insert:pp_if($has_function(res_nquerydomain))]
%#define __res_nquerydomain res_nquerydomain
%[insert:pp_endif]
%[insert:pp_if($has_function(res_nsearch))]
%#define __res_nsearch res_nsearch
%[insert:pp_endif]
%[insert:pp_if($has_function(res_nsend))]
%#define __res_nsend res_nsend
%[insert:pp_endif]
%[insert:pp_if($has_function(res_nisourserver))]
%#define __res_nisourserver res_nisourserver
%[insert:pp_endif]
%[insert:pp_if($has_function(res_ownok))]
%#define __res_ownok res_ownok
%[insert:pp_endif]
%[insert:pp_if($has_function(res_queriesmatch))]
%#define __res_queriesmatch res_queriesmatch
%[insert:pp_endif]
%[insert:pp_if($has_function(res_randomid))]
%#define __res_randomid res_randomid
%[insert:pp_endif]
%[insert:pp_if($has_function(sym_ntop))]
%#define __sym_ntop sym_ntop
%[insert:pp_endif]
%[insert:pp_if($has_function(sym_ntos))]
%#define __sym_ntos sym_ntos
%[insert:pp_endif]
%[insert:pp_if($has_function(sym_ston))]
%#define __sym_ston sym_ston
%[insert:pp_endif]
%{

__SYSDECL_END
#endif /* __CC__ */

}
