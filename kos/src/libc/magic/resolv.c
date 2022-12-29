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
/* (#) Portability: DragonFly BSD (/include/resolv.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/resolv.h) */
/* (#) Portability: FreeBSD       (/include/resolv.h) */
/* (#) Portability: GNU C Library (/resolv/resolv.h) */
/* (#) Portability: GNU Hurd      (/usr/include/resolv.h) */
/* (#) Portability: NetBSD        (/include/resolv.h) */
/* (#) Portability: OpenBSD       (/include/resolv.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/resolv.h) */
/* (#) Portability: diet libc     (/include/resolv.h) */
/* (#) Portability: libc4/5       (/include/resolv.h) */
/* (#) Portability: libc6         (/include/resolv.h) */
/* (#) Portability: mintlib       (/include/resolv.h) */
/* (#) Portability: musl libc     (/include/resolv.h) */
/* (#) Portability: uClibc        (/include/resolv.h) */
}

%[default:section(".text.crt{|.dos}.net.nameser")]
%[define_replacement(fd_t = __fd_t)]

%[define_decl_include_implication("<bits/crt/resolv.h>" => [
	"<bits/types.h>", "<netinet/bits/in.h>", "<netinet/in.h>",
])]

%[define_decl_include("<bits/crt/resolv.h>": [
	"res_sendhookact", "res_send_qhook", "res_send_rhook",
	"struct __res_state", "res_state"
])]


%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <asm/crt/resolv.h>
)]%[insert:prefix(
#include <bits/crt/resolv.h>
)]%{

#include <arpa/nameser.h>
#include <netinet/in.h>
#include <sys/cdefs.h>
#include <sys/param.h>
#include <sys/types.h>

#include <stdio.h>

/* ??? */
#define MAXNS            __MAXNS            /* ??? */
#define MAXDFLSRCH       __MAXDFLSRCH       /* ??? */
#define MAXDNSRCH        __MAXDNSRCH        /* ??? */
#define LOCALDOMAINPARTS __LOCALDOMAINPARTS /* ??? */

/* ??? */
#define RES_TIMEOUT    __RES_TIMEOUT    /* ??? */
#define MAXRESOLVSORT  __MAXRESOLVSORT  /* ??? */
#define RES_MAXNDOTS   __RES_MAXNDOTS   /* ??? */
#define RES_MAXRETRANS __RES_MAXRETRANS /* ??? */
#define RES_MAXRETRY   __RES_MAXRETRY   /* ??? */
#define RES_DFLRETRY   __RES_DFLRETRY   /* ??? */
#define RES_MAXTIME    __RES_MAXTIME    /* ??? */

/* ??? */
#ifndef _PATH_RESCONF
#define _PATH_RESCONF __PATH_RESCONF
#endif /* !_PATH_RESCONF */

/* ??? */
#define RES_F_VC       __RES_F_VC       /* socket is TCP */
#define RES_F_CONN     __RES_F_CONN     /* socket is connected */
#define RES_F_EDNS0ERR __RES_F_EDNS0ERR /* EDNS0 caused errors */

/* ??? */
#define RES_EXHAUSTIVE __RES_EXHAUSTIVE /* always do all queries */

/* ??? */
#define RES_INIT        __RES_INIT        /* address initialized */
#define RES_DEBUG       __RES_DEBUG       /* print debug messages */
#define RES_AAONLY      __RES_AAONLY      /* authoritative answers only (!IMPL)*/
#define RES_USEVC       __RES_USEVC       /* use virtual circuit */
#define RES_PRIMARY     __RES_PRIMARY     /* query primary server only (!IMPL) */
#define RES_IGNTC       __RES_IGNTC       /* ignore truncation errors */
#define RES_RECURSE     __RES_RECURSE     /* recursion desired */
#define RES_DEFNAMES    __RES_DEFNAMES    /* use default domain name */
#define RES_STAYOPEN    __RES_STAYOPEN    /* Keep TCP socket open */
#define RES_DNSRCH      __RES_DNSRCH      /* search up local domain tree */
#define RES_INSECURE1   __RES_INSECURE1   /* type 1 security disabled */
#define RES_INSECURE2   __RES_INSECURE2   /* type 2 security disabled */
#define RES_NOALIASES   __RES_NOALIASES   /* shuts off HOSTALIASES feature */
#define RES_USE_INET6   __RES_USE_INET6   /* use/map IPv6 in gethostbyname() */
#define RES_ROTATE      __RES_ROTATE      /* rotate ns list after each query */
#define RES_NOCHECKNAME __RES_NOCHECKNAME /* do not check names for sanity (!IMPL) */
#define RES_KEEPTSIG    __RES_KEEPTSIG    /* do not strip TSIG records */
#define RES_BLAST       __RES_BLAST       /* blast all recursive servers */
#define RES_USEBSTRING  __RES_USEBSTRING  /* IPv6 reverse lookup with byte strings */
#define RES_NOIP6DOTINT __RES_NOIP6DOTINT /* Do not use .ip6.int in IPv6 reverse lookup */
#define RES_USE_EDNS0   __RES_USE_EDNS0   /* Use EDNS0.  */
#define RES_SNGLKUP     __RES_SNGLKUP     /* one outstanding request at a time */
#define RES_SNGLKUPREOP __RES_SNGLKUPREOP /* -"-, but open new socket for each request */
#define RES_USE_DNSSEC  __RES_USE_DNSSEC  /* use DNSSEC using OK bit in OPT */
#define RES_NOTLDQUERY  __RES_NOTLDQUERY  /* Do not look up unqualified name as a TLD.  */
#define RES_DEFAULT     __RES_DEFAULT

/* ??? */
#define RES_PRF_STATS  __RES_PRF_STATS
#define RES_PRF_UPDATE __RES_PRF_UPDATE
#define RES_PRF_CLASS  __RES_PRF_CLASS
#define RES_PRF_CMD    __RES_PRF_CMD
#define RES_PRF_QUES   __RES_PRF_QUES
#define RES_PRF_ANS    __RES_PRF_ANS
#define RES_PRF_AUTH   __RES_PRF_AUTH
#define RES_PRF_ADD    __RES_PRF_ADD
#define RES_PRF_HEAD1  __RES_PRF_HEAD1
#define RES_PRF_HEAD2  __RES_PRF_HEAD2
#define RES_PRF_TTLID  __RES_PRF_TTLID
#define RES_PRF_HEADX  __RES_PRF_HEADX
#define RES_PRF_QUERY  __RES_PRF_QUERY
#define RES_PRF_REPLY  __RES_PRF_REPLY
#define RES_PRF_INIT   __RES_PRF_INIT

#ifdef __CC__
__SYSDECL_BEGIN

}


%[define_replacement(res_send_qhook = res_send_qhook)]
%[define_replacement(res_send_rhook = res_send_rhook)]
%[define_type_class(res_send_qhook = "TP")]
%[define_type_class(res_send_rhook = "TP")]
%[define_type_class(res_state = "TP")]
%[define_replacement(res_state = "struct __res_state *")]

/* TODO: Figure out what these functions do and (try to) implement them */


[[decl_include("<bits/crt/resolv.h>")]]
[[const]] struct __res_state *__res_state(void);

%[insert:pp_if($has_function(__res_state))]
%#define _res (*__res_state())
%[insert:pp_endif]

%
%#ifndef __BIND_NOSTATIC
[[export_alias("__fp_nquery")]]
void fp_nquery($u_char const *a, int b, $FILE *c);

[[export_alias("__fp_query")]]
void fp_query($u_char const *a, $FILE *b);

[[export_alias("__hostalias")]]
char const *hostalias(char const *a);

[[export_alias("__p_query")]]
void p_query($u_char const *a);

[[export_alias("__res_close")]]
void res_close(void);

[[export_alias("__res_init")]]
int res_init(void);

[[export_alias("__res_isourserver")]]
int res_isourserver(struct sockaddr_in const *a);

[[export_alias("__res_mkquery")]]
int res_mkquery(int a, char const *b, int c, int d, $u_char const *e, int f, $u_char const *g, $u_char *h, int i);

[[export_alias("__res_query")]]
int res_query(char const *a, int b, int c, $u_char *d, int e);

[[export_alias("__res_querydomain")]]
int res_querydomain(char const *a, char const *b, int c, int d, $u_char *e, int f);

[[export_alias("__res_search")]]
int res_search(char const *a, int b, int c, $u_char *d, int e);

[[export_alias("__res_send")]]
int res_send($u_char const *a, int b, $u_char *c, int d);
%#endif /* !__BIND_NOSTATIC */


[[export_alias("__res_hnok")]]
int res_hnok(char const *a);

[[export_alias("__res_ownok")]]
int res_ownok(char const *a);

[[export_alias("__res_mailok")]]
int res_mailok(char const *a);

[[export_alias("__res_dnok")]]
int res_dnok(char const *a);

[[export_alias("__sym_ston")]]
[[decl_include("<bits/crt/resolv.h>")]]
[[impl_include("<bits/crt/resolv.h>")]]
int sym_ston([[in]] struct res_sym const *symbols,
             [[in]] char const *wanted_name,
             [[out_opt]] int *p_success) {
	while (symbols->@name@ != NULL) {
		if (strcasecmp(symbols->@name@, wanted_name) == 0) {
			if (p_success)
				*p_success = 1;
			goto done;
		}
		++symbols;
	}
	if (p_success)
		*p_success = 0;
done:
	return symbols->@number@;
}

[[export_alias("__sym_ntos")]]
[[decl_include("<bits/crt/resolv.h>")]]
[[impl_include("<bits/crt/resolv.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
[[nonnull]] char const *sym_ntos([[in]] struct res_sym const *symbols,
                                 int wanted_number,
                                 [[out_opt]] int *p_success) {
@@pp_if __SIZEOF_INT__ == 4@@
	static char fallback_namebuf[COMPILER_LENOF("-2147483648")];
@@pp_elif __SIZEOF_INT__ == 8@@
	static char fallback_namebuf[COMPILER_LENOF("-9223372036854775808")];
@@pp_elif __SIZEOF_INT__ == 2@@
	static char fallback_namebuf[COMPILER_LENOF("-32768")];
@@pp_elif __SIZEOF_INT__ == 1@@
	static char fallback_namebuf[COMPILER_LENOF("-128")];
@@pp_else@@
#error "Unsupported sizeof(int)"
@@pp_endif@@
	while (symbols->@name@ != NULL) {
		if (symbols->@number@ == wanted_number) {
			if (p_success)
				*p_success = 1;
			return symbols->@name@;
		}
		++symbols;
	}
	if (p_success)
		*p_success = 0;
	sprintf(fallback_namebuf, "%d", wanted_number);
	return fallback_namebuf;
}

[[export_alias("__sym_ntop")]]
[[decl_include("<bits/crt/resolv.h>")]]
[[impl_include("<bits/crt/resolv.h>")]]
[[nonnull]] char const *sym_ntop([[in]] struct res_sym const *symbols,
                                 int wanted_number,
                                 [[out_opt]] int *p_success) {
	while (symbols->@name@ != NULL) {
		if (symbols->@number@ == wanted_number) {
			if (p_success)
				*p_success = 1;
			return symbols->@humanname@;
		}
		++symbols;
	}
	/* Re-use the fallback path of `sym_ntos(3)' */
	return sym_ntos(symbols, wanted_number, p_success);
}

[[export_alias("__b64_ntop")]]
[[decl_include("<hybrid/typecore.h>")]]
int b64_ntop($u_char const *a, size_t b, char *c, size_t d);

[[export_alias("__b64_pton")]]
[[decl_include("<hybrid/typecore.h>")]]
int b64_pton(char const *a, $u_char *b, size_t c);

[[export_alias("__loc_aton")]]
int loc_aton(char const *a, $u_char *b);

[[export_alias("__loc_ntoa")]]
char const *loc_ntoa($u_char const *a, char *b);

[[export_alias("__dn_skipname")]]
[[decl_include("<bits/types.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
[[requires_function(ns_name_skip)]]
int dn_skipname([[in]] $u_char const *msg_ptr,
                [[nonnull]] $u_char const *end_of_msg) {
	u_char const *orig_msg_ptr = msg_ptr;
	if (ns_name_skip(&msg_ptr, end_of_msg) == -1)
		return -1;
	return (int)(unsigned int)(size_t)(msg_ptr - orig_msg_ptr);
}

[[decl_include("<hybrid/typecore.h>")]]
void putlong($u_int32_t a, $u_char *b) = ns_put32;

[[decl_include("<hybrid/typecore.h>")]]
void putshort($u_int16_t a, $u_char *b) = ns_put16;

[[export_alias("__p_class")]]
char const *p_class(int a);

[[decl_include("<hybrid/typecore.h>")]]
[[export_alias("__p_time")]]
char const *p_time($u_int32_t a);

[[export_alias("__p_type")]]
char const *p_type(int a);

[[export_alias("__p_rcode")]]
char const *p_rcode(int a);

[[export_alias("__p_cdnname")]]
$u_char const *p_cdnname($u_char const *a, $u_char const *b, int c, $FILE *d);

[[export_alias("__p_cdname")]]
$u_char const *p_cdname($u_char const *a, $u_char const *b, $FILE *c);

[[export_alias("__p_fqnname")]]
$u_char const *p_fqnname($u_char const *a, $u_char const *b, int c, char *d, int e);

[[export_alias("__p_fqname")]]
$u_char const *p_fqname($u_char const *a, $u_char const *b, $FILE *c);

[[export_alias("__p_option")]]
char const *p_option($u_long a);

[[export_alias("__p_secstodate")]]
char *p_secstodate($u_long a);

[[export_alias("__dn_count_labels")]]
int dn_count_labels(char const *a);

%[insert:function(dn_comp = dn_comp)] /* Implemented in "arpa.nameser.c" */

[[decl_include("<bits/types.h>"), impl_include("<hybrid/typecore.h>")]]
[[export_alias("__dn_expand"), requires_function(ns_name_uncompress)]]
int dn_expand($u_char const *msg_ptr, $u_char const *end_of_msg,
              $u_char const *srcbuf, char *dstbuf, int dstbufsize) {
	int n = ns_name_uncompress(msg_ptr, end_of_msg, srcbuf,
	                           dstbuf, (size_t)dstbufsize);
	if (n > 0 && dstbuf[0] == '.')
		dstbuf[0] = '\0';
	return n;
}

[[export_alias("__res_randomid")]]
$u_int res_randomid(void);

[[export_alias("__res_nameinquery")]]
int res_nameinquery(char const *a, int b, int c, $u_char const *d, $u_char const *e);

[[export_alias("__res_queriesmatch")]]
int res_queriesmatch($u_char const *a, $u_char const *b, $u_char const *c, $u_char const *d);

[[export_alias("__p_section")]]
char const *p_section(int a, int b);

[[export_alias("__res_ninit"), decl_include("<bits/crt/resolv.h>")]]
int res_ninit(res_state a);

[[export_alias("__res_nisourserver"), decl_include("<bits/crt/resolv.h>")]]
int res_nisourserver(res_state a, struct sockaddr_in const *b);

[[export_alias("__fp_resstat"), decl_include("<bits/crt/resolv.h>")]]
void fp_resstat(res_state a, $FILE *b);

[[export_alias("__res_npquery"), decl_include("<bits/crt/resolv.h>")]]
void res_npquery(res_state a, $u_char const *b, int c, $FILE *d);

[[decl_include("<hybrid/typecore.h>")]]
[[export_alias("__res_hostalias"), decl_include("<bits/crt/resolv.h>")]]
char const *res_hostalias(res_state a, char const *b, char *c, size_t d);

[[export_alias("__res_nquery"), decl_include("<bits/crt/resolv.h>")]]
int res_nquery(res_state a, char const *b, int c, int d, $u_char *e, int f);

[[export_alias("__res_nsearch"), decl_include("<bits/crt/resolv.h>")]]
int res_nsearch(res_state a, char const *b, int c, int d, $u_char *e, int f);

[[export_alias("__res_nquerydomain"), decl_include("<bits/crt/resolv.h>")]]
int res_nquerydomain(res_state a, char const *b, char const *c, int d, int e, $u_char *f, int g);

[[export_alias("__res_nmkquery"), decl_include("<bits/crt/resolv.h>")]]
int res_nmkquery(res_state a, int b, char const *c, int d, int e, $u_char const *f, int g, $u_char const *h, $u_char *i, int j);

[[export_alias("__res_nsend"), decl_include("<bits/crt/resolv.h>")]]
int res_nsend(res_state a, $u_char const *b, int c, $u_char *d, int e);

[[export_alias("__res_nclose"), decl_include("<bits/crt/resolv.h>")]]
void res_nclose(res_state a);


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

%(auto_header){
#undef __fp_nquery
#undef __fp_query
#undef __hostalias
#undef __p_query
#undef __res_close
#undef __res_init
#undef __res_isourserver
#undef __res_mkquery
#undef __res_query
#undef __res_querydomain
#undef __res_search
#undef __res_send
#undef __b64_ntop
#undef __b64_pton
#undef __dn_comp
#undef __dn_count_labels
#undef __dn_expand
#undef __dn_skipname
#undef __fp_resstat
#undef __loc_aton
#undef __loc_ntoa
#undef __p_cdname
#undef __p_cdnname
#undef __p_class
#undef __p_fqname
#undef __p_fqnname
#undef __p_option
#undef __p_secstodate
#undef __p_section
#undef __p_time
#undef __p_type
#undef __p_rcode
#undef __putlong
#undef __putshort
#undef __res_dnok
#undef __res_hnok
#undef __res_hostalias
#undef __res_mailok
#undef __res_nameinquery
#undef __res_nclose
#undef __res_ninit
#undef __res_nmkquery
#undef __res_npquery
#undef __res_nquery
#undef __res_nquerydomain
#undef __res_nsearch
#undef __res_nsend
#undef __res_nisourserver
#undef __res_ownok
#undef __res_queriesmatch
#undef __res_randomid
#undef __sym_ntop
#undef __sym_ntos
#undef __sym_ston
}

%{

__SYSDECL_END
#endif /* __CC__ */

}
