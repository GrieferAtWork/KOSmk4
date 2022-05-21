/* HASH CRC-32:0x58e6f136 */
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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/arpa/nameser.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/arpa/nameser.h) */
/* (#) Portability: FreeBSD       (/include/arpa/nameser.h) */
/* (#) Portability: GNU C Library (/resolv/arpa/nameser.h) */
/* (#) Portability: NetBSD        (/include/arpa/nameser.h) */
/* (#) Portability: OpenBSD       (/include/arpa/nameser.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/arpa/nameser.h) */
/* (#) Portability: diet libc     (/include/arpa/nameser.h) */
/* (#) Portability: libc4/5       (/include/arpa/nameser.h) */
/* (#) Portability: libc6         (/include/arpa/nameser.h) */
/* (#) Portability: mintlib       (/include/arpa/nameser.h) */
/* (#) Portability: musl libc     (/include/arpa/nameser.h) */
/* (#) Portability: uClibc        (/include/arpa/nameser.h) */
#ifndef _ARPA_NAMESER_H
#define _ARPA_NAMESER_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <hybrid/__byteswap.h>
#include <hybrid/__unaligned.h>

#include <sys/cdefs.h>
#include <sys/param.h>
#include <sys/types.h>

__SYSDECL_BEGIN

#define BIND_4_COMPAT

/* ??? */
#define __NAMESER      19991006 /* ??? */
#define NS_PACKETSZ    512      /* ??? */
#define NS_MAXDNAME    1025     /* ??? */
#define NS_MAXMSG      65535    /* ??? */
#define NS_MAXCDNAME   255      /* ??? */
#define NS_MAXLABEL    63       /* ??? */
#define NS_HFIXEDSZ    12       /* ??? */
#define NS_QFIXEDSZ    4        /* ??? */
#define NS_RRFIXEDSZ   10       /* ??? */
#define NS_INT32SZ     4        /* == sizeof(int32_t) */
#define NS_INT16SZ     2        /* == sizeof(int16_t) */
#define NS_INT8SZ      1        /* == sizeof(int8_t) */
#define NS_INADDRSZ    4        /* ??? */
#define NS_IN6ADDRSZ   16       /* ??? */
#define NS_CMPRSFLGS   0xc0     /* ??? */
#define NS_DEFAULTPORT 53       /* ??? */

/* ??? */
/*[[[enum]]]*/
#ifdef __CC__
typedef enum __ns_sect {
	ns_s_qd  = 0, /* ??? */
	ns_s_zn  = 0, /* ??? */
	ns_s_an  = 1, /* ??? */
	ns_s_pr  = 1, /* ??? */
	ns_s_ns  = 2, /* ??? */
	ns_s_ud  = 2, /* ??? */
	ns_s_ar  = 3, /* ??? */
	ns_s_max = 4
} ns_sect;
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define ns_s_qd  ns_s_qd  /* ??? */
#define ns_s_zn  ns_s_zn  /* ??? */
#define ns_s_an  ns_s_an  /* ??? */
#define ns_s_pr  ns_s_pr  /* ??? */
#define ns_s_ns  ns_s_ns  /* ??? */
#define ns_s_ud  ns_s_ud  /* ??? */
#define ns_s_ar  ns_s_ar  /* ??? */
#define ns_s_max ns_s_max
#else /* __COMPILER_PREFERR_ENUMS */
#define ns_s_qd  0 /* ??? */
#define ns_s_zn  0 /* ??? */
#define ns_s_an  1 /* ??? */
#define ns_s_pr  1 /* ??? */
#define ns_s_ns  2 /* ??? */
#define ns_s_ud  2 /* ??? */
#define ns_s_ar  3 /* ??? */
#define ns_s_max 4
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

/* ??? */
#ifdef __CC__
typedef struct __ns_msg {
	__u_char const *_msg;
	__u_char const *_eom;
	__uint16_t      _id;
	__uint16_t      _flags;
	__uint16_t      _counts[ns_s_max];
	__u_char const *_sections[ns_s_max];
	ns_sect         _sect;
	int             _rrnum;
	__u_char const *_msg_ptr;
} ns_msg;
#endif /* __CC__ */

/* ??? */
#ifdef __CC__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("mask")
#pragma push_macro("shift")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef mask
#undef shift
struct _ns_flagdata {
	int mask;
	int shift;
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("shift")
#pragma pop_macro("mask")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#if !defined(_ns_flagdata) && defined(__CRT_HAVE__ns_flagdata)
__CSDECLARE2(,struct _ns_flagdata const _ns_flagdata[],_ns_flagdata)
#define _ns_flagdata _ns_flagdata
#endif /* !_ns_flagdata && __CRT_HAVE__ns_flagdata */
#endif /* __CC__ */

/* ??? */
#define ns_msg_id(handle)             ((handle)._id + 0)
#define ns_msg_base(handle)           ((handle)._msg + 0)
#define ns_msg_end(handle)            ((handle)._eom + 0)
#define ns_msg_size(handle)           ((handle)._eom - (handle)._msg)
#define ns_msg_count(handle, section) ((handle)._counts[section] + 0)

/* ??? */
#ifdef __CC__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("name")
#pragma push_macro("type")
#pragma push_macro("rr_class")
#pragma push_macro("ttl")
#pragma push_macro("rdlength")
#pragma push_macro("rdata")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef name
#undef type
#undef rr_class
#undef ttl
#undef rdlength
#undef rdata
typedef struct __ns_rr {
	char            name[NS_MAXDNAME];
	__uint16_t      type;
	__uint16_t      rr_class;
	__uint32_t      ttl;
	__uint16_t      rdlength;
	__u_char const *rdata;
} ns_rr;
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("rdata")
#pragma pop_macro("rdlength")
#pragma pop_macro("ttl")
#pragma pop_macro("rr_class")
#pragma pop_macro("type")
#pragma pop_macro("name")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __CC__ */

/* ??? */
#define ns_rr_name(rr)  (((rr).name[0] != '\0') ? (rr).name : ".")
#define ns_rr_type(rr)  ((ns_type)((rr).type + 0))
#define ns_rr_class(rr) ((ns_class)((rr).rr_class + 0))
#define ns_rr_ttl(rr)   ((rr).ttl + 0)
#define ns_rr_rdlen(rr) ((rr).rdlength + 0)
#define ns_rr_rdata(rr) ((rr).rdata + 0)

/* ??? */
/*[[[enum]]]*/
#ifdef __CC__
typedef enum __ns_flag {
	ns_f_qr,     /* ??? */
	ns_f_opcode, /* ??? */
	ns_f_aa,     /* ??? */
	ns_f_tc,     /* ??? */
	ns_f_rd,     /* ??? */
	ns_f_ra,     /* ??? */
	ns_f_z,      /* ??? */
	ns_f_ad,     /* ??? */
	ns_f_cd,     /* ??? */
	ns_f_rcode,  /* ??? */
	ns_f_max
} ns_flag;
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define ns_f_qr     ns_f_qr     /* ??? */
#define ns_f_opcode ns_f_opcode /* ??? */
#define ns_f_aa     ns_f_aa     /* ??? */
#define ns_f_tc     ns_f_tc     /* ??? */
#define ns_f_rd     ns_f_rd     /* ??? */
#define ns_f_ra     ns_f_ra     /* ??? */
#define ns_f_z      ns_f_z      /* ??? */
#define ns_f_ad     ns_f_ad     /* ??? */
#define ns_f_cd     ns_f_cd     /* ??? */
#define ns_f_rcode  ns_f_rcode  /* ??? */
#define ns_f_max    ns_f_max
#else /* __COMPILER_PREFERR_ENUMS */
#define ns_f_qr     0  /* ??? */
#define ns_f_opcode 1  /* ??? */
#define ns_f_aa     2  /* ??? */
#define ns_f_tc     3  /* ??? */
#define ns_f_rd     4  /* ??? */
#define ns_f_ra     5  /* ??? */
#define ns_f_z      6  /* ??? */
#define ns_f_ad     7  /* ??? */
#define ns_f_cd     8  /* ??? */
#define ns_f_rcode  9  /* ??? */
#define ns_f_max    10
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

/* ??? */
/*[[[enum]]]*/
#ifdef __CC__
typedef enum __ns_opcode {
	ns_o_query  = 0, /* ??? */
	ns_o_iquery = 1, /* ??? */
	ns_o_status = 2, /* ??? */
	ns_o_notify = 4, /* ??? */
	ns_o_update = 5, /* ??? */
	ns_o_max    = 6
} ns_opcode;
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define ns_o_query  ns_o_query  /* ??? */
#define ns_o_iquery ns_o_iquery /* ??? */
#define ns_o_status ns_o_status /* ??? */
#define ns_o_notify ns_o_notify /* ??? */
#define ns_o_update ns_o_update /* ??? */
#define ns_o_max    ns_o_max
#else /* __COMPILER_PREFERR_ENUMS */
#define ns_o_query  0 /* ??? */
#define ns_o_iquery 1 /* ??? */
#define ns_o_status 2 /* ??? */
#define ns_o_notify 4 /* ??? */
#define ns_o_update 5 /* ??? */
#define ns_o_max    6
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

/* ??? */
/*[[[enum]]]*/
#ifdef __CC__
typedef enum __ns_rcode {
	ns_r_noerror  = 0,  /* ??? */
	ns_r_formerr  = 1,  /* ??? */
	ns_r_servfail = 2,  /* ??? */
	ns_r_nxdomain = 3,  /* ??? */
	ns_r_notimpl  = 4,  /* ??? */
	ns_r_refused  = 5,  /* ??? */
	ns_r_yxdomain = 6,  /* ??? */
	ns_r_yxrrset  = 7,  /* ??? */
	ns_r_nxrrset  = 8,  /* ??? */
	ns_r_notauth  = 9,  /* ??? */
	ns_r_notzone  = 10, /* ??? */
	ns_r_max      = 11,
	ns_r_badvers  = 16,
	ns_r_badsig   = 16,
	ns_r_badkey   = 17,
	ns_r_badtime  = 18
} ns_rcode;
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define ns_r_noerror  ns_r_noerror  /* ??? */
#define ns_r_formerr  ns_r_formerr  /* ??? */
#define ns_r_servfail ns_r_servfail /* ??? */
#define ns_r_nxdomain ns_r_nxdomain /* ??? */
#define ns_r_notimpl  ns_r_notimpl  /* ??? */
#define ns_r_refused  ns_r_refused  /* ??? */
#define ns_r_yxdomain ns_r_yxdomain /* ??? */
#define ns_r_yxrrset  ns_r_yxrrset  /* ??? */
#define ns_r_nxrrset  ns_r_nxrrset  /* ??? */
#define ns_r_notauth  ns_r_notauth  /* ??? */
#define ns_r_notzone  ns_r_notzone  /* ??? */
#define ns_r_max      ns_r_max
#define ns_r_badvers  ns_r_badvers
#define ns_r_badsig   ns_r_badsig
#define ns_r_badkey   ns_r_badkey
#define ns_r_badtime  ns_r_badtime
#else /* __COMPILER_PREFERR_ENUMS */
#define ns_r_noerror  0  /* ??? */
#define ns_r_formerr  1  /* ??? */
#define ns_r_servfail 2  /* ??? */
#define ns_r_nxdomain 3  /* ??? */
#define ns_r_notimpl  4  /* ??? */
#define ns_r_refused  5  /* ??? */
#define ns_r_yxdomain 6  /* ??? */
#define ns_r_yxrrset  7  /* ??? */
#define ns_r_nxrrset  8  /* ??? */
#define ns_r_notauth  9  /* ??? */
#define ns_r_notzone  10 /* ??? */
#define ns_r_max      11
#define ns_r_badvers  16
#define ns_r_badsig   16
#define ns_r_badkey   17
#define ns_r_badtime  18
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

/* ??? */
/*[[[enum]]]*/
#ifdef __CC__
typedef enum __ns_update_operation {
	ns_uop_delete = 0,
	ns_uop_add    = 1,
	ns_uop_max    = 2
} ns_update_operation;
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define ns_uop_delete ns_uop_delete
#define ns_uop_add    ns_uop_add
#define ns_uop_max    ns_uop_max
#else /* __COMPILER_PREFERR_ENUMS */
#define ns_uop_delete 0
#define ns_uop_add    1
#define ns_uop_max    2
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

#ifdef __CC__
/* ??? */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("name")
#pragma push_macro("alg")
#pragma push_macro("data")
#pragma push_macro("len")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef name
#undef alg
#undef data
#undef len
typedef struct ns_tsig_key {
	char           name[NS_MAXDNAME];
	char           alg[NS_MAXDNAME];
	unsigned char *data;
	int            len;
} ns_tsig_key;
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("len")
#pragma pop_macro("data")
#pragma pop_macro("alg")
#pragma pop_macro("name")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

/* ??? */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("counter")
#pragma push_macro("key")
#pragma push_macro("ctx")
#pragma push_macro("sig")
#pragma push_macro("siglen")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef counter
#undef key
#undef ctx
#undef sig
#undef siglen
typedef struct ns_tcp_tsig_state {
	int             counter;
	struct dst_key *key;
	void           *ctx;
	unsigned char   sig[NS_PACKETSZ];
	int             siglen;
} ns_tcp_tsig_state;
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("siglen")
#pragma pop_macro("sig")
#pragma pop_macro("ctx")
#pragma pop_macro("key")
#pragma pop_macro("counter")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __CC__ */

#define NS_TSIG_FUDGE        300
#define NS_TSIG_TCP_COUNT    100
#define NS_TSIG_ALG_HMAC_MD5 "HMAC-MD5.SIG-ALG.REG.INT"

#define NS_TSIG_ERROR_NO_TSIG  -10
#define NS_TSIG_ERROR_NO_SPACE -11
#define NS_TSIG_ERROR_FORMERR  -12

/* ??? */
/*[[[enum]]]*/
#ifdef __CC__
typedef enum __ns_type {
	ns_t_invalid  = 0,   /* ??? */
	ns_t_a        = 1,   /* ??? */
	ns_t_ns       = 2,   /* ??? */
	ns_t_md       = 3,   /* ??? */
	ns_t_mf       = 4,   /* ??? */
	ns_t_cname    = 5,   /* ??? */
	ns_t_soa      = 6,   /* ??? */
	ns_t_mb       = 7,   /* ??? */
	ns_t_mg       = 8,   /* ??? */
	ns_t_mr       = 9,   /* ??? */
	ns_t_null     = 10,  /* ??? */
	ns_t_wks      = 11,  /* ??? */
	ns_t_ptr      = 12,  /* ??? */
	ns_t_hinfo    = 13,  /* ??? */
	ns_t_minfo    = 14,  /* ??? */
	ns_t_mx       = 15,  /* ??? */
	ns_t_txt      = 16,  /* ??? */
	ns_t_rp       = 17,  /* ??? */
	ns_t_afsdb    = 18,  /* ??? */
	ns_t_x25      = 19,  /* ??? */
	ns_t_isdn     = 20,  /* ??? */
	ns_t_rt       = 21,  /* ??? */
	ns_t_nsap     = 22,  /* ??? */
	ns_t_nsap_ptr = 23,  /* ??? */
	ns_t_sig      = 24,  /* ??? */
	ns_t_key      = 25,  /* ??? */
	ns_t_px       = 26,  /* ??? */
	ns_t_gpos     = 27,  /* ??? */
	ns_t_aaaa     = 28,  /* ??? */
	ns_t_loc      = 29,  /* ??? */
	ns_t_nxt      = 30,  /* ??? */
	ns_t_eid      = 31,  /* ??? */
	ns_t_nimloc   = 32,  /* ??? */
	ns_t_srv      = 33,  /* ??? */
	ns_t_atma     = 34,  /* ??? */
	ns_t_naptr    = 35,  /* ??? */
	ns_t_kx       = 36,  /* ??? */
	ns_t_cert     = 37,  /* ??? */
	ns_t_a6       = 38,  /* ??? */
	ns_t_dname    = 39,  /* ??? */
	ns_t_sink     = 40,  /* ??? */
	ns_t_opt      = 41,  /* ??? */
	ns_t_apl      = 42,  /* ??? */
	ns_t_tkey     = 249, /* ??? */
	ns_t_tsig     = 250, /* ??? */
	ns_t_ixfr     = 251, /* ??? */
	ns_t_axfr     = 252, /* ??? */
	ns_t_mailb    = 253, /* ??? */
	ns_t_maila    = 254, /* ??? */
	ns_t_any      = 255, /* ??? */
	ns_t_zxfr     = 256, /* ??? */
	ns_t_max      = 65536
} ns_type;
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define ns_t_invalid  ns_t_invalid  /* ??? */
#define ns_t_a        ns_t_a        /* ??? */
#define ns_t_ns       ns_t_ns       /* ??? */
#define ns_t_md       ns_t_md       /* ??? */
#define ns_t_mf       ns_t_mf       /* ??? */
#define ns_t_cname    ns_t_cname    /* ??? */
#define ns_t_soa      ns_t_soa      /* ??? */
#define ns_t_mb       ns_t_mb       /* ??? */
#define ns_t_mg       ns_t_mg       /* ??? */
#define ns_t_mr       ns_t_mr       /* ??? */
#define ns_t_null     ns_t_null     /* ??? */
#define ns_t_wks      ns_t_wks      /* ??? */
#define ns_t_ptr      ns_t_ptr      /* ??? */
#define ns_t_hinfo    ns_t_hinfo    /* ??? */
#define ns_t_minfo    ns_t_minfo    /* ??? */
#define ns_t_mx       ns_t_mx       /* ??? */
#define ns_t_txt      ns_t_txt      /* ??? */
#define ns_t_rp       ns_t_rp       /* ??? */
#define ns_t_afsdb    ns_t_afsdb    /* ??? */
#define ns_t_x25      ns_t_x25      /* ??? */
#define ns_t_isdn     ns_t_isdn     /* ??? */
#define ns_t_rt       ns_t_rt       /* ??? */
#define ns_t_nsap     ns_t_nsap     /* ??? */
#define ns_t_nsap_ptr ns_t_nsap_ptr /* ??? */
#define ns_t_sig      ns_t_sig      /* ??? */
#define ns_t_key      ns_t_key      /* ??? */
#define ns_t_px       ns_t_px       /* ??? */
#define ns_t_gpos     ns_t_gpos     /* ??? */
#define ns_t_aaaa     ns_t_aaaa     /* ??? */
#define ns_t_loc      ns_t_loc      /* ??? */
#define ns_t_nxt      ns_t_nxt      /* ??? */
#define ns_t_eid      ns_t_eid      /* ??? */
#define ns_t_nimloc   ns_t_nimloc   /* ??? */
#define ns_t_srv      ns_t_srv      /* ??? */
#define ns_t_atma     ns_t_atma     /* ??? */
#define ns_t_naptr    ns_t_naptr    /* ??? */
#define ns_t_kx       ns_t_kx       /* ??? */
#define ns_t_cert     ns_t_cert     /* ??? */
#define ns_t_a6       ns_t_a6       /* ??? */
#define ns_t_dname    ns_t_dname    /* ??? */
#define ns_t_sink     ns_t_sink     /* ??? */
#define ns_t_opt      ns_t_opt      /* ??? */
#define ns_t_apl      ns_t_apl      /* ??? */
#define ns_t_tkey     ns_t_tkey     /* ??? */
#define ns_t_tsig     ns_t_tsig     /* ??? */
#define ns_t_ixfr     ns_t_ixfr     /* ??? */
#define ns_t_axfr     ns_t_axfr     /* ??? */
#define ns_t_mailb    ns_t_mailb    /* ??? */
#define ns_t_maila    ns_t_maila    /* ??? */
#define ns_t_any      ns_t_any      /* ??? */
#define ns_t_zxfr     ns_t_zxfr     /* ??? */
#define ns_t_max      ns_t_max
#else /* __COMPILER_PREFERR_ENUMS */
#define ns_t_invalid  0     /* ??? */
#define ns_t_a        1     /* ??? */
#define ns_t_ns       2     /* ??? */
#define ns_t_md       3     /* ??? */
#define ns_t_mf       4     /* ??? */
#define ns_t_cname    5     /* ??? */
#define ns_t_soa      6     /* ??? */
#define ns_t_mb       7     /* ??? */
#define ns_t_mg       8     /* ??? */
#define ns_t_mr       9     /* ??? */
#define ns_t_null     10    /* ??? */
#define ns_t_wks      11    /* ??? */
#define ns_t_ptr      12    /* ??? */
#define ns_t_hinfo    13    /* ??? */
#define ns_t_minfo    14    /* ??? */
#define ns_t_mx       15    /* ??? */
#define ns_t_txt      16    /* ??? */
#define ns_t_rp       17    /* ??? */
#define ns_t_afsdb    18    /* ??? */
#define ns_t_x25      19    /* ??? */
#define ns_t_isdn     20    /* ??? */
#define ns_t_rt       21    /* ??? */
#define ns_t_nsap     22    /* ??? */
#define ns_t_nsap_ptr 23    /* ??? */
#define ns_t_sig      24    /* ??? */
#define ns_t_key      25    /* ??? */
#define ns_t_px       26    /* ??? */
#define ns_t_gpos     27    /* ??? */
#define ns_t_aaaa     28    /* ??? */
#define ns_t_loc      29    /* ??? */
#define ns_t_nxt      30    /* ??? */
#define ns_t_eid      31    /* ??? */
#define ns_t_nimloc   32    /* ??? */
#define ns_t_srv      33    /* ??? */
#define ns_t_atma     34    /* ??? */
#define ns_t_naptr    35    /* ??? */
#define ns_t_kx       36    /* ??? */
#define ns_t_cert     37    /* ??? */
#define ns_t_a6       38    /* ??? */
#define ns_t_dname    39    /* ??? */
#define ns_t_sink     40    /* ??? */
#define ns_t_opt      41    /* ??? */
#define ns_t_apl      42    /* ??? */
#define ns_t_tkey     249   /* ??? */
#define ns_t_tsig     250   /* ??? */
#define ns_t_ixfr     251   /* ??? */
#define ns_t_axfr     252   /* ??? */
#define ns_t_mailb    253   /* ??? */
#define ns_t_maila    254   /* ??? */
#define ns_t_any      255   /* ??? */
#define ns_t_zxfr     256   /* ??? */
#define ns_t_max      65536
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

/* ??? */
#define ns_t_qt_p(t)  (ns_t_xfr_p(t) || (t) == ns_t_any || (t) == ns_t_mailb || (t) == ns_t_maila)
#define ns_t_mrr_p(t) ((t) == ns_t_tsig || (t) == ns_t_opt)
#define ns_t_rr_p(t)  (!ns_t_qt_p(t) && !ns_t_mrr_p(t))
#define ns_t_udp_p(t) ((t) != ns_t_axfr && (t) != ns_t_zxfr)
#define ns_t_xfr_p(t) ((t) == ns_t_axfr || (t) == ns_t_ixfr || (t) == ns_t_zxfr)

/* ??? */
/*[[[enum]]]*/
#ifdef __CC__
typedef enum __ns_class {
	ns_c_invalid = 0,   /* ??? */
	ns_c_in      = 1,   /* ??? */
	ns_c_2       = 2,   /* ??? */
	ns_c_chaos   = 3,   /* ??? */
	ns_c_hs      = 4,   /* ??? */
	ns_c_none    = 254, /* ??? */
	ns_c_any     = 255, /* ??? */
	ns_c_max     = 65536
} ns_class;
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define ns_c_invalid ns_c_invalid /* ??? */
#define ns_c_in      ns_c_in      /* ??? */
#define ns_c_2       ns_c_2       /* ??? */
#define ns_c_chaos   ns_c_chaos   /* ??? */
#define ns_c_hs      ns_c_hs      /* ??? */
#define ns_c_none    ns_c_none    /* ??? */
#define ns_c_any     ns_c_any     /* ??? */
#define ns_c_max     ns_c_max
#else /* __COMPILER_PREFERR_ENUMS */
#define ns_c_invalid 0     /* ??? */
#define ns_c_in      1     /* ??? */
#define ns_c_2       2     /* ??? */
#define ns_c_chaos   3     /* ??? */
#define ns_c_hs      4     /* ??? */
#define ns_c_none    254   /* ??? */
#define ns_c_any     255   /* ??? */
#define ns_c_max     65536
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

/* ??? */
/*[[[enum]]]*/
#ifdef __CC__
typedef enum __ns_key_types {
	ns_kt_rsa     = 1,  /* ??? */
	ns_kt_dh      = 2,  /* ??? */
	ns_kt_dsa     = 3,  /* ??? */
	ns_kt_private = 254 /* ??? */
} ns_key_types;
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define ns_kt_rsa     ns_kt_rsa     /* ??? */
#define ns_kt_dh      ns_kt_dh      /* ??? */
#define ns_kt_dsa     ns_kt_dsa     /* ??? */
#define ns_kt_private ns_kt_private /* ??? */
#else /* __COMPILER_PREFERR_ENUMS */
#define ns_kt_rsa     1   /* ??? */
#define ns_kt_dh      2   /* ??? */
#define ns_kt_dsa     3   /* ??? */
#define ns_kt_private 254 /* ??? */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

/*[[[enum]]]*/
#ifdef __CC__
typedef enum __ns_cert_types {
	cert_t_pkix = 1,   /* ??? */
	cert_t_spki = 2,   /* ??? */
	cert_t_pgp  = 3,   /* ??? */
	cert_t_url  = 253, /* ??? */
	cert_t_oid  = 254  /* ??? */
} ns_cert_types;
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define cert_t_pkix cert_t_pkix /* ??? */
#define cert_t_spki cert_t_spki /* ??? */
#define cert_t_pgp  cert_t_pgp  /* ??? */
#define cert_t_url  cert_t_url  /* ??? */
#define cert_t_oid  cert_t_oid  /* ??? */
#else /* __COMPILER_PREFERR_ENUMS */
#define cert_t_pkix 1   /* ??? */
#define cert_t_spki 2   /* ??? */
#define cert_t_pgp  3   /* ??? */
#define cert_t_url  253 /* ??? */
#define cert_t_oid  254 /* ??? */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

/* ??? */
#define NS_KEY_TYPEMASK       0xC000 /* ??? */
#define NS_KEY_TYPE_AUTH_CONF 0x0000 /* ??? */
#define NS_KEY_TYPE_CONF_ONLY 0x8000 /* ??? */
#define NS_KEY_TYPE_AUTH_ONLY 0x4000 /* ??? */
#define NS_KEY_TYPE_NO_KEY    0xC000 /* ??? */
/* ??? */
#define NS_KEY_NO_AUTH          0x8000 /* ??? */
#define NS_KEY_NO_CONF          0x4000 /* ??? */
#define NS_KEY_RESERVED2        0x2000 /* ??? */
#define NS_KEY_EXTENDED_FLAGS   0x1000 /* ??? */
#define NS_KEY_RESERVED4        0x0800 /* ??? */
#define NS_KEY_RESERVED5        0x0400 /* ??? */
#define NS_KEY_NAME_TYPE        0x0300 /* ??? */
#define NS_KEY_NAME_USER        0x0000 /* ??? */
#define NS_KEY_NAME_ENTITY      0x0200 /* ??? */
#define NS_KEY_NAME_ZONE        0x0100 /* ??? */
#define NS_KEY_NAME_RESERVED    0x0300 /* ??? */
#define NS_KEY_RESERVED8        0x0080 /* ??? */
#define NS_KEY_RESERVED9        0x0040 /* ??? */
#define NS_KEY_RESERVED10       0x0020 /* ??? */
#define NS_KEY_RESERVED11       0x0010 /* ??? */
#define NS_KEY_SIGNATORYMASK    0x000F /* ??? */
#define NS_KEY_RESERVED_BITMASK                                                  \
	(NS_KEY_RESERVED2 | NS_KEY_RESERVED4 | NS_KEY_RESERVED5 | NS_KEY_RESERVED8 | \
	 NS_KEY_RESERVED9 | NS_KEY_RESERVED10 | NS_KEY_RESERVED11)
#define NS_KEY_RESERVED_BITMASK2 0xFFFF /* ??? */
/* ??? */
#define NS_ALG_MD5RSA      1 /* ??? */
#define NS_ALG_DH          2 /* ??? */
#define NS_ALG_DSA         3 /* ??? */
#define NS_ALG_DSS         NS_ALG_DSA
#define NS_ALG_EXPIRE_ONLY 253 /* ??? */
#define NS_ALG_PRIVATE_OID 254 /* ??? */
/* ??? */
#define NS_KEY_PROT_TLS    1
#define NS_KEY_PROT_EMAIL  2
#define NS_KEY_PROT_DNSSEC 3
#define NS_KEY_PROT_IPSEC  4
#define NS_KEY_PROT_ANY    255

/* ??? */
#define NS_MD5RSA_MIN_BITS 512 /* ??? */
#define NS_MD5RSA_MAX_BITS 4096
/* ??? */
#define NS_MD5RSA_MAX_BYTES ((NS_MD5RSA_MAX_BITS + 7 / 8) * 2 + 3)
/* ??? */
#define NS_MD5RSA_MAX_BASE64 (((NS_MD5RSA_MAX_BYTES + 2) / 3) * 4)
#define NS_MD5RSA_MIN_SIZE   ((NS_MD5RSA_MIN_BITS + 7) / 8)
#define NS_MD5RSA_MAX_SIZE   ((NS_MD5RSA_MAX_BITS + 7) / 8)

#define NS_DSA_SIG_SIZE  41
#define NS_DSA_MIN_SIZE  213
#define NS_DSA_MAX_BYTES 405

/* ??? */
#define NS_SIG_TYPE   0  /* ??? */
#define NS_SIG_ALG    2  /* ??? */
#define NS_SIG_LABELS 3  /* ??? */
#define NS_SIG_OTTL   4  /* ??? */
#define NS_SIG_EXPIR  8  /* ??? */
#define NS_SIG_SIGNED 12 /* ??? */
#define NS_SIG_FOOT   16 /* ??? */
#define NS_SIG_SIGNER 18 /* ??? */
/* ??? */
#define NS_NXT_BITS            8
#define NS_NXT_BIT_SET(n, p)   ((p)[(n) / NS_NXT_BITS] |= (0x80 >> ((n) % NS_NXT_BITS)))
#define NS_NXT_BIT_CLEAR(n, p) ((p)[(n) / NS_NXT_BITS] &= ~(0x80 >> ((n) % NS_NXT_BITS)))
#define NS_NXT_BIT_ISSET(n, p) ((p)[(n) / NS_NXT_BITS] & (0x80 >> ((n) % NS_NXT_BITS)))
#define NS_NXT_MAX             127

/* ??? */
#define NS_OPT_DNSSEC_OK 0x8000u
#define NS_OPT_NSID      3

/* Encode/decode network data-words from a pointer-stream `s' */
#define NS_GET16(s, cp) (void)((s) = __hybrid_unaligned_getbe16(cp), (cp) += NS_INT16SZ)
#define NS_GET32(l, cp) (void)((l) = __hybrid_unaligned_getbe32(cp), (cp) += NS_INT32SZ)
#define NS_PUT16(s, cp) (void)(__hybrid_unaligned_setbe16(cp, s), (cp) += NS_INT16SZ)
#define NS_PUT32(l, cp) (void)(__hybrid_unaligned_setbe32(cp, l), (cp) += NS_INT32SZ)

#ifdef __CC__

#ifdef __CRT_HAVE_ns_get16
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1),unsigned int,__NOTHROW_NCX,ns_get16,(unsigned char const *__srcptr),(__srcptr))
#else /* __CRT_HAVE_ns_get16 */
#include <libc/local/arpa.nameser/ns_get16.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ns_get16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) unsigned int __NOTHROW_NCX(__LIBCCALL ns_get16)(unsigned char const *__srcptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ns_get16))(__srcptr); })
#endif /* !__CRT_HAVE_ns_get16 */
#ifdef __CRT_HAVE_ns_get32
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1),unsigned long,__NOTHROW_NCX,ns_get32,(unsigned char const *__srcptr),(__srcptr))
#else /* __CRT_HAVE_ns_get32 */
#include <libc/local/arpa.nameser/ns_get32.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ns_get32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) unsigned long __NOTHROW_NCX(__LIBCCALL ns_get32)(unsigned char const *__srcptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ns_get32))(__srcptr); })
#endif /* !__CRT_HAVE_ns_get32 */
#ifdef __CRT_HAVE_ns_put16
__CDECLARE_VOID(__ATTR_ACCESS_WR(2),__NOTHROW_NCX,ns_put16,(unsigned int __val, unsigned char *__destptr),(__val,__destptr))
#elif defined(__CRT_HAVE_putshort)
__CREDIRECT_VOID(__ATTR_ACCESS_WR(2),__NOTHROW_NCX,ns_put16,(unsigned int __val, unsigned char *__destptr),putshort,(__val,__destptr))
#elif defined(__CRT_HAVE___putshort)
__CREDIRECT_VOID(__ATTR_ACCESS_WR(2),__NOTHROW_NCX,ns_put16,(unsigned int __val, unsigned char *__destptr),__putshort,(__val,__destptr))
#else /* ... */
#include <libc/local/arpa.nameser/ns_put16.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ns_put16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_WR(2) void __NOTHROW_NCX(__LIBCCALL ns_put16)(unsigned int __val, unsigned char *__destptr) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ns_put16))(__val, __destptr); })
#endif /* !... */
#ifdef __CRT_HAVE_ns_put32
__CDECLARE_VOID(__ATTR_ACCESS_WR(2),__NOTHROW_NCX,ns_put32,(unsigned long __val, unsigned char *__destptr),(__val,__destptr))
#elif defined(__CRT_HAVE_putlong)
__CREDIRECT_VOID(__ATTR_ACCESS_WR(2),__NOTHROW_NCX,ns_put32,(unsigned long __val, unsigned char *__destptr),putlong,(__val,__destptr))
#elif defined(__CRT_HAVE___putlong)
__CREDIRECT_VOID(__ATTR_ACCESS_WR(2),__NOTHROW_NCX,ns_put32,(unsigned long __val, unsigned char *__destptr),__putlong,(__val,__destptr))
#else /* ... */
#include <libc/local/arpa.nameser/ns_put32.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ns_put32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_WR(2) void __NOTHROW_NCX(__LIBCCALL ns_put32)(unsigned long __val, unsigned char *__destptr) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ns_put32))(__val, __destptr); })
#endif /* !... */
__CDECLARE_OPT(,int,__NOTHROW_NCX,ns_initparse,(unsigned char const *__a, int __b, ns_msg *__c),(__a,__b,__c))
__CDECLARE_OPT(,int,__NOTHROW_NCX,ns_skiprr,(unsigned char const *__a, unsigned char const *__b, ns_sect __c, int __d),(__a,__b,__c,__d))
__CDECLARE_OPT(,int,__NOTHROW_NCX,ns_parserr,(ns_msg *__a, ns_sect __b, int __c, ns_rr *__d),(__a,__b,__c,__d))
__CDECLARE_OPT(,int,__NOTHROW_NCX,ns_sprintrr,(ns_msg const *__a, ns_rr const *__b, char const *__c, char const *__d, char *__e, size_t __f),(__a,__b,__c,__d,__e,__f))
__CDECLARE_OPT(,int,__NOTHROW_NCX,ns_sprintrrf,(unsigned char const *__a, size_t, char const *__b, ns_class __c, ns_type __d, unsigned long __e, unsigned char const *__f, size_t __g, char const *__h, char const *__i, char *__j, size_t __k),(__a,,__b,__c,__d,__e,__f,__g,__h,__i,__j,__k))
__CDECLARE_OPT(,int,__NOTHROW_NCX,ns_format_ttl,(unsigned long __a, char *__b, size_t __c),(__a,__b,__c))
__CDECLARE_OPT(,int,__NOTHROW_NCX,ns_parse_ttl,(char const *__a, unsigned long *__b),(__a,__b))
__CDECLARE_OPT(,u_int32_t,__NOTHROW_NCX,ns_datetosecs,(char const *__a, int *__b),(__a,__b))
__CDECLARE_OPT(,int,__NOTHROW_NCX,ns_name_ntol,(unsigned char const *__a, unsigned char *__b, size_t __c),(__a,__b,__c))
__CDECLARE_OPT(,int,__NOTHROW_NCX,ns_name_ntop,(unsigned char const *__a, char *__b, size_t __c),(__a,__b,__c))
__CDECLARE_OPT(,int,__NOTHROW_NCX,ns_name_pton,(char const *__a, unsigned char *__b, size_t __c),(__a,__b,__c))
__CDECLARE_OPT(,int,__NOTHROW_NCX,ns_name_unpack,(unsigned char const *__a, unsigned char const *__b, unsigned char const *__c, unsigned char *__d, size_t __e),(__a,__b,__c,__d,__e))
__CDECLARE_OPT(,int,__NOTHROW_NCX,ns_name_pack,(unsigned char const *__a, unsigned char *__b, int __c, unsigned char const **__d, unsigned char const **__e),(__a,__b,__c,__d,__e))
__CDECLARE_OPT(,int,__NOTHROW_NCX,ns_name_uncompress,(unsigned char const *__a, unsigned char const *__b, unsigned char const *__c, char *__d, size_t __e),(__a,__b,__c,__d,__e))
#ifdef __CRT_HAVE_ns_name_compress
__CDECLARE(,int,__NOTHROW_NCX,ns_name_compress,(char const *__srcbuf, unsigned char *__dstbuf, size_t __dstbufsize, unsigned char const **__d, unsigned char const **__e),(__srcbuf,__dstbuf,__dstbufsize,__d,__e))
#elif defined(__CRT_HAVE_dn_comp) && __SIZEOF_INT__ == __SIZEOF_SIZE_T__
__CREDIRECT(,int,__NOTHROW_NCX,ns_name_compress,(char const *__srcbuf, unsigned char *__dstbuf, size_t __dstbufsize, unsigned char const **__d, unsigned char const **__e),dn_comp,(__srcbuf,__dstbuf,__dstbufsize,__d,__e))
#elif defined(__CRT_HAVE___dn_comp) && __SIZEOF_INT__ == __SIZEOF_SIZE_T__
__CREDIRECT(,int,__NOTHROW_NCX,ns_name_compress,(char const *__srcbuf, unsigned char *__dstbuf, size_t __dstbufsize, unsigned char const **__d, unsigned char const **__e),__dn_comp,(__srcbuf,__dstbuf,__dstbufsize,__d,__e))
#else /* ... */
#include <libc/local/arpa.nameser/ns_name_compress.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ns_name_compress, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL ns_name_compress)(char const *__srcbuf, unsigned char *__dstbuf, size_t __dstbufsize, unsigned char const **__d, unsigned char const **__e) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ns_name_compress))(__srcbuf, __dstbuf, __dstbufsize, __d, __e); })
#endif /* !... */
__CDECLARE_OPT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,ns_name_skip,(unsigned char const **__p_msg_ptr, unsigned char const *__msg_end),(__p_msg_ptr,__msg_end))
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,ns_name_rollback,(unsigned char const *__a, unsigned char const **__b, unsigned char const **__c),(__a,__b,__c))
__CDECLARE_OPT(,int,__NOTHROW_NCX,ns_sign,(unsigned char *__a, int *__b, int __c, int __d, void *__e, unsigned char const *__f, int __g, unsigned char *__h, int *__i, time_t __j),(__a,__b,__c,__d,__e,__f,__g,__h,__i,__j))
__CDECLARE_OPT(,int,__NOTHROW_NCX,ns_sign2,(unsigned char *__a, int *__b, int __c, int __d, void *__e, unsigned char const *__f, int __g, unsigned char *__h, int *__i, time_t __j, unsigned char **__k, unsigned char **__l),(__a,__b,__c,__d,__e,__f,__g,__h,__i,__j,__k,__l))
__CDECLARE_OPT(,int,__NOTHROW_NCX,ns_sign_tcp,(unsigned char *__a, int *__b, int __c, int __d, ns_tcp_tsig_state *__e, int __f),(__a,__b,__c,__d,__e,__f))
__CDECLARE_OPT(,int,__NOTHROW_NCX,ns_sign_tcp2,(unsigned char *__a, int *__b, int __c, int __d, ns_tcp_tsig_state *__e, int __f, unsigned char **__g, unsigned char **__h),(__a,__b,__c,__d,__e,__f,__g,__h))
__CDECLARE_OPT(,int,__NOTHROW_NCX,ns_sign_tcp_init,(void *__a, unsigned char const *__b, int __c, ns_tcp_tsig_state *__d),(__a,__b,__c,__d))
__CDECLARE_OPT(,unsigned char *,__NOTHROW_NCX,ns_find_tsig,(unsigned char *__a, unsigned char *__b),(__a,__b))
__CDECLARE_OPT(,int,__NOTHROW_NCX,ns_verify,(unsigned char *__a, int *__b, void *__c, unsigned char const *__d, int __e, unsigned char *__f, int *__g, time_t *__h, int __i),(__a,__b,__c,__d,__e,__f,__g,__h,__i))
__CDECLARE_OPT(,int,__NOTHROW_NCX,ns_verify_tcp,(unsigned char *__a, int *__b, ns_tcp_tsig_state *__c, int __d),(__a,__b,__c,__d))
__CDECLARE_OPT(,int,__NOTHROW_NCX,ns_verify_tcp_init,(void *__a, unsigned char const *__b, int __c, ns_tcp_tsig_state *__d),(__a,__b,__c,__d))
__CDECLARE_OPT(,int,__NOTHROW_NCX,ns_samedomain,(char const *__a, char const *__b),(__a,__b))
__CDECLARE_OPT(,int,__NOTHROW_NCX,ns_subdomain,(char const *__a, char const *__b),(__a,__b))
__CDECLARE_OPT(,int,__NOTHROW_NCX,ns_makecanon,(char const *__a, char *__b, size_t __c),(__a,__b,__c))
__CDECLARE_OPT(,int,__NOTHROW_NCX,ns_samename,(char const *__a, char const *__b),(__a,__b))
#endif /* __CC__ */

__SYSDECL_END

#ifdef BIND_4_COMPAT
#include <arpa/nameser_compat.h>
#endif /* BIND_4_COMPAT */

#endif /* !_ARPA_NAMESER_H */
