/* HASH CRC-32:0x46446de */
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
/* (#) Portability: EMX kLIBC     (/libc/include/resolv.h) */
/* (#) Portability: FreeBSD       (/include/resolv.h) */
/* (#) Portability: GNU C Library (/resolv/resolv.h) */
/* (#) Portability: NetBSD        (/include/resolv.h) */
/* (#) Portability: OpenBSD       (/include/resolv.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/resolv.h) */
/* (#) Portability: diet libc     (/include/resolv.h) */
/* (#) Portability: libc4/5       (/include/resolv.h) */
/* (#) Portability: libc6         (/include/resolv.h) */
/* (#) Portability: mintlib       (/include/resolv.h) */
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
#include <asm/crt/resolv.h>
#include <bits/crt/resolv.h>

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

__CDECLARE_OPT(__ATTR_CONST,struct __res_state *,__NOTHROW_NCX,__res_state,(void),())
#ifdef __CRT_HAVE___res_state
#define _res (*__res_state())
#endif /* __CRT_HAVE___res_state */

#ifndef __BIND_NOSTATIC
#ifdef __CRT_HAVE_fp_nquery
__CDECLARE_VOID(,__NOTHROW_NCX,fp_nquery,(unsigned char const *__a, int __b, __FILE *__c),(__a,__b,__c))
#elif defined(__CRT_HAVE___fp_nquery)
__CREDIRECT_VOID(,__NOTHROW_NCX,fp_nquery,(unsigned char const *__a, int __b, __FILE *__c),__fp_nquery,(__a,__b,__c))
#endif /* ... */
#ifdef __CRT_HAVE_fp_query
__CDECLARE_VOID(,__NOTHROW_NCX,fp_query,(unsigned char const *__a, __FILE *__b),(__a,__b))
#elif defined(__CRT_HAVE___fp_query)
__CREDIRECT_VOID(,__NOTHROW_NCX,fp_query,(unsigned char const *__a, __FILE *__b),__fp_query,(__a,__b))
#endif /* ... */
#ifdef __CRT_HAVE_hostalias
__CDECLARE(,char const *,__NOTHROW_NCX,hostalias,(char const *__a),(__a))
#elif defined(__CRT_HAVE___hostalias)
__CREDIRECT(,char const *,__NOTHROW_NCX,hostalias,(char const *__a),__hostalias,(__a))
#endif /* ... */
#ifdef __CRT_HAVE_p_query
__CDECLARE_VOID(,__NOTHROW_NCX,p_query,(unsigned char const *__a),(__a))
#elif defined(__CRT_HAVE___p_query)
__CREDIRECT_VOID(,__NOTHROW_NCX,p_query,(unsigned char const *__a),__p_query,(__a))
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
__CDECLARE(,int,__NOTHROW_NCX,res_mkquery,(int __a, char const *__b, int __c, int __d, unsigned char const *__e, int __f, unsigned char const *__g, unsigned char *__h, int __i),(__a,__b,__c,__d,__e,__f,__g,__h,__i))
#elif defined(__CRT_HAVE___res_mkquery)
__CREDIRECT(,int,__NOTHROW_NCX,res_mkquery,(int __a, char const *__b, int __c, int __d, unsigned char const *__e, int __f, unsigned char const *__g, unsigned char *__h, int __i),__res_mkquery,(__a,__b,__c,__d,__e,__f,__g,__h,__i))
#endif /* ... */
#ifdef __CRT_HAVE_res_query
__CDECLARE(,int,__NOTHROW_NCX,res_query,(char const *__a, int __b, int __c, unsigned char *__d, int __e),(__a,__b,__c,__d,__e))
#elif defined(__CRT_HAVE___res_query)
__CREDIRECT(,int,__NOTHROW_NCX,res_query,(char const *__a, int __b, int __c, unsigned char *__d, int __e),__res_query,(__a,__b,__c,__d,__e))
#endif /* ... */
#ifdef __CRT_HAVE_res_querydomain
__CDECLARE(,int,__NOTHROW_NCX,res_querydomain,(char const *__a, char const *__b, int __c, int __d, unsigned char *__e, int __f),(__a,__b,__c,__d,__e,__f))
#elif defined(__CRT_HAVE___res_querydomain)
__CREDIRECT(,int,__NOTHROW_NCX,res_querydomain,(char const *__a, char const *__b, int __c, int __d, unsigned char *__e, int __f),__res_querydomain,(__a,__b,__c,__d,__e,__f))
#endif /* ... */
#ifdef __CRT_HAVE_res_search
__CDECLARE(,int,__NOTHROW_NCX,res_search,(char const *__a, int __b, int __c, unsigned char *__d, int __e),(__a,__b,__c,__d,__e))
#elif defined(__CRT_HAVE___res_search)
__CREDIRECT(,int,__NOTHROW_NCX,res_search,(char const *__a, int __b, int __c, unsigned char *__d, int __e),__res_search,(__a,__b,__c,__d,__e))
#endif /* ... */
#ifdef __CRT_HAVE_res_send
__CDECLARE(,int,__NOTHROW_NCX,res_send,(unsigned char const *__a, int __b, unsigned char *__c, int __d),(__a,__b,__c,__d))
#elif defined(__CRT_HAVE___res_send)
__CREDIRECT(,int,__NOTHROW_NCX,res_send,(unsigned char const *__a, int __b, unsigned char *__c, int __d),__res_send,(__a,__b,__c,__d))
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
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,sym_ston,(struct res_sym const *__symbols, char const *__wanted_name, int *__p_success),(__symbols,__wanted_name,__p_success))
#elif defined(__CRT_HAVE___sym_ston)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,sym_ston,(struct res_sym const *__symbols, char const *__wanted_name, int *__p_success),__sym_ston,(__symbols,__wanted_name,__p_success))
#else /* ... */
#include <libc/local/resolv/sym_ston.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(sym_ston, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL sym_ston)(struct res_sym const *__symbols, char const *__wanted_name, int *__p_success) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sym_ston))(__symbols, __wanted_name, __p_success); })
#endif /* !... */
#ifdef __CRT_HAVE_sym_ntos
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,sym_ntos,(struct res_sym const *__symbols, int __wanted_number, int *__p_success),(__symbols,__wanted_number,__p_success))
#elif defined(__CRT_HAVE___sym_ntos)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,sym_ntos,(struct res_sym const *__symbols, int __wanted_number, int *__p_success),__sym_ntos,(__symbols,__wanted_number,__p_success))
#else /* ... */
#include <libc/local/resolv/sym_ntos.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(sym_ntos, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL sym_ntos)(struct res_sym const *__symbols, int __wanted_number, int *__p_success) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sym_ntos))(__symbols, __wanted_number, __p_success); })
#endif /* !... */
#ifdef __CRT_HAVE_sym_ntop
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,sym_ntop,(struct res_sym const *__symbols, int __wanted_number, int *__p_success),(__symbols,__wanted_number,__p_success))
#elif defined(__CRT_HAVE___sym_ntop)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,sym_ntop,(struct res_sym const *__symbols, int __wanted_number, int *__p_success),__sym_ntop,(__symbols,__wanted_number,__p_success))
#else /* ... */
#include <libc/local/resolv/sym_ntop.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(sym_ntop, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL sym_ntop)(struct res_sym const *__symbols, int __wanted_number, int *__p_success) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sym_ntop))(__symbols, __wanted_number, __p_success); })
#endif /* !... */
#ifdef __CRT_HAVE_b64_ntop
__CDECLARE(,int,__NOTHROW_NCX,b64_ntop,(unsigned char const *__a, size_t __b, char *__c, size_t __d),(__a,__b,__c,__d))
#elif defined(__CRT_HAVE___b64_ntop)
__CREDIRECT(,int,__NOTHROW_NCX,b64_ntop,(unsigned char const *__a, size_t __b, char *__c, size_t __d),__b64_ntop,(__a,__b,__c,__d))
#endif /* ... */
#ifdef __CRT_HAVE_b64_pton
__CDECLARE(,int,__NOTHROW_NCX,b64_pton,(char const *__a, unsigned char *__b, size_t __c),(__a,__b,__c))
#elif defined(__CRT_HAVE___b64_pton)
__CREDIRECT(,int,__NOTHROW_NCX,b64_pton,(char const *__a, unsigned char *__b, size_t __c),__b64_pton,(__a,__b,__c))
#endif /* ... */
#ifdef __CRT_HAVE_loc_aton
__CDECLARE(,int,__NOTHROW_NCX,loc_aton,(char const *__a, unsigned char *__b),(__a,__b))
#elif defined(__CRT_HAVE___loc_aton)
__CREDIRECT(,int,__NOTHROW_NCX,loc_aton,(char const *__a, unsigned char *__b),__loc_aton,(__a,__b))
#endif /* ... */
#ifdef __CRT_HAVE_loc_ntoa
__CDECLARE(,char const *,__NOTHROW_NCX,loc_ntoa,(unsigned char const *__a, char *__b),(__a,__b))
#elif defined(__CRT_HAVE___loc_ntoa)
__CREDIRECT(,char const *,__NOTHROW_NCX,loc_ntoa,(unsigned char const *__a, char *__b),__loc_ntoa,(__a,__b))
#endif /* ... */
#ifdef __CRT_HAVE_dn_skipname
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,dn_skipname,(unsigned char const *__msg_ptr, unsigned char const *__end_of_msg),(__msg_ptr,__end_of_msg))
#elif defined(__CRT_HAVE___dn_skipname)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,dn_skipname,(unsigned char const *__msg_ptr, unsigned char const *__end_of_msg),__dn_skipname,(__msg_ptr,__end_of_msg))
#elif defined(__CRT_HAVE_ns_name_skip)
#include <libc/local/resolv/dn_skipname.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(dn_skipname, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL dn_skipname)(unsigned char const *__msg_ptr, unsigned char const *__end_of_msg) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dn_skipname))(__msg_ptr, __end_of_msg); })
#endif /* ... */
#ifdef __CRT_HAVE_ns_put32
__CREDIRECT_VOID(,__NOTHROW_NCX,putlong,(__UINT32_TYPE__ __a, unsigned char *__b),ns_put32,(__a,__b))
#elif defined(__CRT_HAVE_putlong)
__CDECLARE_VOID(,__NOTHROW_NCX,putlong,(__UINT32_TYPE__ __a, unsigned char *__b),(__a,__b))
#elif defined(__CRT_HAVE___putlong)
__CREDIRECT_VOID(,__NOTHROW_NCX,putlong,(__UINT32_TYPE__ __a, unsigned char *__b),__putlong,(__a,__b))
#else /* ... */
#include <libc/local/arpa.nameser/ns_put32.h>
__FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL putlong)(__UINT32_TYPE__ __a, unsigned char *__b) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ns_put32))((unsigned long)__a, __b); }
#endif /* !... */
#ifdef __CRT_HAVE_ns_put16
__CREDIRECT_VOID(,__NOTHROW_NCX,putshort,(__UINT16_TYPE__ __a, unsigned char *__b),ns_put16,(__a,__b))
#elif defined(__CRT_HAVE_putshort)
__CDECLARE_VOID(,__NOTHROW_NCX,putshort,(__UINT16_TYPE__ __a, unsigned char *__b),(__a,__b))
#elif defined(__CRT_HAVE___putshort)
__CREDIRECT_VOID(,__NOTHROW_NCX,putshort,(__UINT16_TYPE__ __a, unsigned char *__b),__putshort,(__a,__b))
#else /* ... */
#include <libc/local/arpa.nameser/ns_put16.h>
__FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL putshort)(__UINT16_TYPE__ __a, unsigned char *__b) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ns_put16))((unsigned int)__a, __b); }
#endif /* !... */
#ifdef __CRT_HAVE_p_class
__CDECLARE(,char const *,__NOTHROW_NCX,p_class,(int __a),(__a))
#elif defined(__CRT_HAVE___p_class)
__CREDIRECT(,char const *,__NOTHROW_NCX,p_class,(int __a),__p_class,(__a))
#endif /* ... */
#ifdef __CRT_HAVE_p_time
__CDECLARE(,char const *,__NOTHROW_NCX,p_time,(__UINT32_TYPE__ __a),(__a))
#elif defined(__CRT_HAVE___p_time)
__CREDIRECT(,char const *,__NOTHROW_NCX,p_time,(__UINT32_TYPE__ __a),__p_time,(__a))
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
__CDECLARE(,unsigned char const *,__NOTHROW_NCX,p_cdnname,(unsigned char const *__a, unsigned char const *__b, int __c, __FILE *__d),(__a,__b,__c,__d))
#elif defined(__CRT_HAVE___p_cdnname)
__CREDIRECT(,unsigned char const *,__NOTHROW_NCX,p_cdnname,(unsigned char const *__a, unsigned char const *__b, int __c, __FILE *__d),__p_cdnname,(__a,__b,__c,__d))
#endif /* ... */
#ifdef __CRT_HAVE_p_cdname
__CDECLARE(,unsigned char const *,__NOTHROW_NCX,p_cdname,(unsigned char const *__a, unsigned char const *__b, __FILE *__c),(__a,__b,__c))
#elif defined(__CRT_HAVE___p_cdname)
__CREDIRECT(,unsigned char const *,__NOTHROW_NCX,p_cdname,(unsigned char const *__a, unsigned char const *__b, __FILE *__c),__p_cdname,(__a,__b,__c))
#endif /* ... */
#ifdef __CRT_HAVE_p_fqnname
__CDECLARE(,unsigned char const *,__NOTHROW_NCX,p_fqnname,(unsigned char const *__a, unsigned char const *__b, int __c, char *__d, int __e),(__a,__b,__c,__d,__e))
#elif defined(__CRT_HAVE___p_fqnname)
__CREDIRECT(,unsigned char const *,__NOTHROW_NCX,p_fqnname,(unsigned char const *__a, unsigned char const *__b, int __c, char *__d, int __e),__p_fqnname,(__a,__b,__c,__d,__e))
#endif /* ... */
#ifdef __CRT_HAVE_p_fqname
__CDECLARE(,unsigned char const *,__NOTHROW_NCX,p_fqname,(unsigned char const *__a, unsigned char const *__b, __FILE *__c),(__a,__b,__c))
#elif defined(__CRT_HAVE___p_fqname)
__CREDIRECT(,unsigned char const *,__NOTHROW_NCX,p_fqname,(unsigned char const *__a, unsigned char const *__b, __FILE *__c),__p_fqname,(__a,__b,__c))
#endif /* ... */
#ifdef __CRT_HAVE_p_option
__CDECLARE(,char const *,__NOTHROW_NCX,p_option,(unsigned long __a),(__a))
#elif defined(__CRT_HAVE___p_option)
__CREDIRECT(,char const *,__NOTHROW_NCX,p_option,(unsigned long __a),__p_option,(__a))
#endif /* ... */
#ifdef __CRT_HAVE_p_secstodate
__CDECLARE(,char *,__NOTHROW_NCX,p_secstodate,(unsigned long __a),(__a))
#elif defined(__CRT_HAVE___p_secstodate)
__CREDIRECT(,char *,__NOTHROW_NCX,p_secstodate,(unsigned long __a),__p_secstodate,(__a))
#endif /* ... */
#ifdef __CRT_HAVE_dn_count_labels
__CDECLARE(,int,__NOTHROW_NCX,dn_count_labels,(char const *__a),(__a))
#elif defined(__CRT_HAVE___dn_count_labels)
__CREDIRECT(,int,__NOTHROW_NCX,dn_count_labels,(char const *__a),__dn_count_labels,(__a))
#endif /* ... */
#ifdef __CRT_HAVE_dn_comp
__CDECLARE(,int,__NOTHROW_NCX,dn_comp,(char const *__srcbuf, unsigned char *__dstbuf, int __dstbufsize, unsigned char **__d, unsigned char **__e),(__srcbuf,__dstbuf,__dstbufsize,__d,__e))
#elif defined(__CRT_HAVE___dn_comp)
__CREDIRECT(,int,__NOTHROW_NCX,dn_comp,(char const *__srcbuf, unsigned char *__dstbuf, int __dstbufsize, unsigned char **__d, unsigned char **__e),__dn_comp,(__srcbuf,__dstbuf,__dstbufsize,__d,__e))
#elif defined(__CRT_HAVE_ns_name_compress) && __SIZEOF_INT__ == __SIZEOF_SIZE_T__
__CREDIRECT(,int,__NOTHROW_NCX,dn_comp,(char const *__srcbuf, unsigned char *__dstbuf, int __dstbufsize, unsigned char **__d, unsigned char **__e),ns_name_compress,(__srcbuf,__dstbuf,__dstbufsize,__d,__e))
#else /* ... */
#include <libc/local/arpa.nameser/dn_comp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(dn_comp, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL dn_comp)(char const *__srcbuf, unsigned char *__dstbuf, int __dstbufsize, unsigned char **__d, unsigned char **__e) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dn_comp))(__srcbuf, __dstbuf, __dstbufsize, __d, __e); })
#endif /* !... */
#ifdef __CRT_HAVE_dn_expand
__CDECLARE(,int,__NOTHROW_NCX,dn_expand,(unsigned char const *__msg_ptr, unsigned char const *__end_of_msg, unsigned char const *__srcbuf, char *__dstbuf, int __dstbufsize),(__msg_ptr,__end_of_msg,__srcbuf,__dstbuf,__dstbufsize))
#elif defined(__CRT_HAVE___dn_expand)
__CREDIRECT(,int,__NOTHROW_NCX,dn_expand,(unsigned char const *__msg_ptr, unsigned char const *__end_of_msg, unsigned char const *__srcbuf, char *__dstbuf, int __dstbufsize),__dn_expand,(__msg_ptr,__end_of_msg,__srcbuf,__dstbuf,__dstbufsize))
#elif defined(__CRT_HAVE_ns_name_uncompress)
#include <libc/local/resolv/dn_expand.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(dn_expand, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL dn_expand)(unsigned char const *__msg_ptr, unsigned char const *__end_of_msg, unsigned char const *__srcbuf, char *__dstbuf, int __dstbufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dn_expand))(__msg_ptr, __end_of_msg, __srcbuf, __dstbuf, __dstbufsize); })
#endif /* ... */
#ifdef __CRT_HAVE_res_randomid
__CDECLARE(,unsigned int,__NOTHROW_NCX,res_randomid,(void),())
#elif defined(__CRT_HAVE___res_randomid)
__CREDIRECT(,unsigned int,__NOTHROW_NCX,res_randomid,(void),__res_randomid,())
#endif /* ... */
#ifdef __CRT_HAVE_res_nameinquery
__CDECLARE(,int,__NOTHROW_NCX,res_nameinquery,(char const *__a, int __b, int __c, unsigned char const *__d, unsigned char const *__e),(__a,__b,__c,__d,__e))
#elif defined(__CRT_HAVE___res_nameinquery)
__CREDIRECT(,int,__NOTHROW_NCX,res_nameinquery,(char const *__a, int __b, int __c, unsigned char const *__d, unsigned char const *__e),__res_nameinquery,(__a,__b,__c,__d,__e))
#endif /* ... */
#ifdef __CRT_HAVE_res_queriesmatch
__CDECLARE(,int,__NOTHROW_NCX,res_queriesmatch,(unsigned char const *__a, unsigned char const *__b, unsigned char const *__c, unsigned char const *__d),(__a,__b,__c,__d))
#elif defined(__CRT_HAVE___res_queriesmatch)
__CREDIRECT(,int,__NOTHROW_NCX,res_queriesmatch,(unsigned char const *__a, unsigned char const *__b, unsigned char const *__c, unsigned char const *__d),__res_queriesmatch,(__a,__b,__c,__d))
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
__CDECLARE_VOID(,__NOTHROW_NCX,fp_resstat,(res_state __a, __FILE *__b),(__a,__b))
#elif defined(__CRT_HAVE___fp_resstat)
__CREDIRECT_VOID(,__NOTHROW_NCX,fp_resstat,(res_state __a, __FILE *__b),__fp_resstat,(__a,__b))
#endif /* ... */
#ifdef __CRT_HAVE_res_npquery
__CDECLARE_VOID(,__NOTHROW_NCX,res_npquery,(res_state __a, unsigned char const *__b, int __c, __FILE *__d),(__a,__b,__c,__d))
#elif defined(__CRT_HAVE___res_npquery)
__CREDIRECT_VOID(,__NOTHROW_NCX,res_npquery,(res_state __a, unsigned char const *__b, int __c, __FILE *__d),__res_npquery,(__a,__b,__c,__d))
#endif /* ... */
#ifdef __CRT_HAVE_res_hostalias
__CDECLARE(,char const *,__NOTHROW_NCX,res_hostalias,(res_state __a, char const *__b, char *__c, size_t __d),(__a,__b,__c,__d))
#elif defined(__CRT_HAVE___res_hostalias)
__CREDIRECT(,char const *,__NOTHROW_NCX,res_hostalias,(res_state __a, char const *__b, char *__c, size_t __d),__res_hostalias,(__a,__b,__c,__d))
#endif /* ... */
#ifdef __CRT_HAVE_res_nquery
__CDECLARE(,int,__NOTHROW_NCX,res_nquery,(res_state __a, char const *__b, int __c, int __d, unsigned char *__e, int __f),(__a,__b,__c,__d,__e,__f))
#elif defined(__CRT_HAVE___res_nquery)
__CREDIRECT(,int,__NOTHROW_NCX,res_nquery,(res_state __a, char const *__b, int __c, int __d, unsigned char *__e, int __f),__res_nquery,(__a,__b,__c,__d,__e,__f))
#endif /* ... */
#ifdef __CRT_HAVE_res_nsearch
__CDECLARE(,int,__NOTHROW_NCX,res_nsearch,(res_state __a, char const *__b, int __c, int __d, unsigned char *__e, int __f),(__a,__b,__c,__d,__e,__f))
#elif defined(__CRT_HAVE___res_nsearch)
__CREDIRECT(,int,__NOTHROW_NCX,res_nsearch,(res_state __a, char const *__b, int __c, int __d, unsigned char *__e, int __f),__res_nsearch,(__a,__b,__c,__d,__e,__f))
#endif /* ... */
#ifdef __CRT_HAVE_res_nquerydomain
__CDECLARE(,int,__NOTHROW_NCX,res_nquerydomain,(res_state __a, char const *__b, char const *__c, int __d, int __e, unsigned char *__f, int __g),(__a,__b,__c,__d,__e,__f,__g))
#elif defined(__CRT_HAVE___res_nquerydomain)
__CREDIRECT(,int,__NOTHROW_NCX,res_nquerydomain,(res_state __a, char const *__b, char const *__c, int __d, int __e, unsigned char *__f, int __g),__res_nquerydomain,(__a,__b,__c,__d,__e,__f,__g))
#endif /* ... */
#ifdef __CRT_HAVE_res_nmkquery
__CDECLARE(,int,__NOTHROW_NCX,res_nmkquery,(res_state __a, int __b, char const *__c, int __d, int __e, unsigned char const *__f, int __g, unsigned char const *__h, unsigned char *__i, int __j),(__a,__b,__c,__d,__e,__f,__g,__h,__i,__j))
#elif defined(__CRT_HAVE___res_nmkquery)
__CREDIRECT(,int,__NOTHROW_NCX,res_nmkquery,(res_state __a, int __b, char const *__c, int __d, int __e, unsigned char const *__f, int __g, unsigned char const *__h, unsigned char *__i, int __j),__res_nmkquery,(__a,__b,__c,__d,__e,__f,__g,__h,__i,__j))
#endif /* ... */
#ifdef __CRT_HAVE_res_nsend
__CDECLARE(,int,__NOTHROW_NCX,res_nsend,(res_state __a, unsigned char const *__b, int __c, unsigned char *__d, int __e),(__a,__b,__c,__d,__e))
#elif defined(__CRT_HAVE___res_nsend)
__CREDIRECT(,int,__NOTHROW_NCX,res_nsend,(res_state __a, unsigned char const *__b, int __c, unsigned char *__d, int __e),__res_nsend,(__a,__b,__c,__d,__e))
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
#define __dn_comp dn_comp
#if defined(__CRT_HAVE_dn_count_labels) || defined(__CRT_HAVE___dn_count_labels)
#define __dn_count_labels dn_count_labels
#endif /* __CRT_HAVE_dn_count_labels || __CRT_HAVE___dn_count_labels */
#if defined(__CRT_HAVE_dn_expand) || defined(__CRT_HAVE___dn_expand) || defined(__CRT_HAVE_ns_name_uncompress)
#define __dn_expand dn_expand
#endif /* __CRT_HAVE_dn_expand || __CRT_HAVE___dn_expand || __CRT_HAVE_ns_name_uncompress */
#if defined(__CRT_HAVE_dn_skipname) || defined(__CRT_HAVE___dn_skipname) || defined(__CRT_HAVE_ns_name_skip)
#define __dn_skipname dn_skipname
#endif /* __CRT_HAVE_dn_skipname || __CRT_HAVE___dn_skipname || __CRT_HAVE_ns_name_skip */
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
#define __putlong putlong
#define __putshort putshort
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
#define __sym_ntop sym_ntop
#define __sym_ntos sym_ntos
#define __sym_ston sym_ston

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_RESOLV_H */
