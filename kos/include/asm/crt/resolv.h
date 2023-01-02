/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ASM_CRT_RESOLV_H
#define _ASM_CRT_RESOLV_H 1

#include <__crt.h>
#include <__stdinc.h>

/* ??? */
#define __MAXNS            3 /* ??? */
#define __MAXDFLSRCH       3 /* ??? */
#define __MAXDNSRCH        6 /* ??? */
#define __LOCALDOMAINPARTS 2 /* ??? */

/* ??? */
#define __RES_TIMEOUT    5     /* ??? */
#define __MAXRESOLVSORT  10    /* ??? */
#define __RES_MAXNDOTS   15    /* ??? */
#define __RES_MAXRETRANS 30    /* ??? */
#define __RES_MAXRETRY   5     /* ??? */
#define __RES_DFLRETRY   2     /* ??? */
#define __RES_MAXTIME    65535 /* ??? */

/* ??? */
#define __RES 19991006

/* ??? */
#define __PATH_RESCONF "/etc/resolv.conf"

/* ??? */
#define __RES_F_VC       0x00000001 /* socket is TCP */
#define __RES_F_CONN     0x00000002 /* socket is connected */
#define __RES_F_EDNS0ERR 0x00000004 /* EDNS0 caused errors */

/* ??? */
#define __RES_EXHAUSTIVE 0x00000001 /* always do all queries */

/* ??? */
#define __RES_INIT        0x00000001 /* address initialized */
#define __RES_DEBUG       0x00000002 /* print debug messages */
#define __RES_AAONLY      0x00000004 /* authoritative answers only (!IMPL)*/
#define __RES_USEVC       0x00000008 /* use virtual circuit */
#define __RES_PRIMARY     0x00000010 /* query primary server only (!IMPL) */
#define __RES_IGNTC       0x00000020 /* ignore truncation errors */
#define __RES_RECURSE     0x00000040 /* recursion desired */
#define __RES_DEFNAMES    0x00000080 /* use default domain name */
#define __RES_STAYOPEN    0x00000100 /* Keep TCP socket open */
#define __RES_DNSRCH      0x00000200 /* search up local domain tree */
#define __RES_INSECURE1   0x00000400 /* type 1 security disabled */
#define __RES_INSECURE2   0x00000800 /* type 2 security disabled */
#define __RES_NOALIASES   0x00001000 /* shuts off HOSTALIASES feature */
#define __RES_USE_INET6   0x00002000 /* use/map IPv6 in gethostbyname() */
#define __RES_ROTATE      0x00004000 /* rotate ns list after each query */
#define __RES_NOCHECKNAME 0x00008000 /* do not check names for sanity (!IMPL) */
#define __RES_KEEPTSIG    0x00010000 /* do not strip TSIG records */
#define __RES_BLAST       0x00020000 /* blast all recursive servers */
#define __RES_USEBSTRING  0x00040000 /* IPv6 reverse lookup with byte strings */
#define __RES_NOIP6DOTINT 0x00080000 /* Do not use .ip6.int in IPv6 reverse lookup */
#define __RES_USE_EDNS0   0x00100000 /* Use EDNS0.  */
#define __RES_SNGLKUP     0x00200000 /* one outstanding request at a time */
#define __RES_SNGLKUPREOP 0x00400000 /* -"-, but open new socket for each request */
#define __RES_USE_DNSSEC  0x00800000 /* use DNSSEC using OK bit in OPT */
#define __RES_NOTLDQUERY  0x01000000 /* Do not look up unqualified name as a TLD.  */
#define __RES_DEFAULT     (__RES_RECURSE | __RES_DEFNAMES | __RES_DNSRCH | __RES_NOIP6DOTINT)

/* ??? */
#define __RES_PRF_STATS  0x00000001
#define __RES_PRF_UPDATE 0x00000002
#define __RES_PRF_CLASS  0x00000004
#define __RES_PRF_CMD    0x00000008
#define __RES_PRF_QUES   0x00000010
#define __RES_PRF_ANS    0x00000020
#define __RES_PRF_AUTH   0x00000040
#define __RES_PRF_ADD    0x00000080
#define __RES_PRF_HEAD1  0x00000100
#define __RES_PRF_HEAD2  0x00000200
#define __RES_PRF_TTLID  0x00000400
#define __RES_PRF_HEADX  0x00000800
#define __RES_PRF_QUERY  0x00001000
#define __RES_PRF_REPLY  0x00002000
#define __RES_PRF_INIT   0x00004000

#endif /* !_ASM_CRT_RESOLV_H */
