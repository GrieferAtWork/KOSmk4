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
/* (>) Standard: POSIX.1-2004 (Issue 6, IEEE Std 1003.1-2004) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/netinet/tcp.h) */
/* (#) Portability: DragonFly BSD (/sys/netinet/tcp.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/netinet/tcp.h) */
/* (#) Portability: FreeBSD       (/sys/netinet/tcp.h) */
/* (#) Portability: GNU C Library (/sysdeps/[...]/netinet/tcp.h) */
/* (#) Portability: GNU Hurd      (/usr/include/netinet/tcp.h) */
/* (#) Portability: NetBSD        (/sys/netinet/tcp.h) */
/* (#) Portability: OpenBSD       (/sys/netinet/tcp.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/netinet/tcp.h) */
/* (#) Portability: diet libc     (/include/netinet/tcp.h) */
/* (#) Portability: libc4/5       (/include/netinet/tcp.h) */
/* (#) Portability: libc6         (/include/netinet/tcp.h) */
/* (#) Portability: mintlib       (/include/netinet/tcp.h) */
/* (#) Portability: musl libc     (/include/netinet/tcp.h) */
/* (#) Portability: uClibc        (/include/netinet/tcp.h) */
#ifndef _NETINET_TCP_H
#define _NETINET_TCP_H 1

/*
 * Copyright (c) 1982, 1986, 1993
 *    The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *    @(#)tcp.h    8.1 (Berkeley) 6/10/93
 */

#include <__stdinc.h>
#include <features.h>

#include <hybrid/__bitfield.h>

/* User-settable options (used with setsockopt). */
#define TCP_NODELAY              1  /* Don't delay send to coalesce packets.  */
#define TCP_MAXSEG               2  /* Set maximum segment size.  */
#define TCP_CORK                 3  /* Control sending of partial frames.  */
#define TCP_KEEPIDLE             4  /* Start keeplives after this period. */
#define TCP_KEEPINTVL            5  /* Interval between keepalives. */
#define TCP_KEEPCNT              6  /* Number of keepalives before death. */
#define TCP_SYNCNT               7  /* Number of SYN retransmits. */
#define TCP_LINGER2              8  /* Life time of orphaned FIN-WAIT-2 state. */
#define TCP_DEFER_ACCEPT         9  /* Wake up listener only when data arrive. */
#define TCP_WINDOW_CLAMP         10 /* Bound advertised window. */
#define TCP_INFO                 11 /* Information about this connection. */
#define TCP_QUICKACK             12 /* Bock/reenable quick ACKs. */
#define TCP_CONGESTION           13 /* Congestion control algorithm. */
#define TCP_MD5SIG               14 /* TCP MD5 Signature (RFC2385). */
#define TCP_COOKIE_TRANSACTIONS  15 /* TCP Cookie Transactions. */
#define TCP_THIN_LINEAR_TIMEOUTS 16 /* Use linear timeouts for thin streams. */
#define TCP_THIN_DUPACK          17 /* Fast retrans. after 1 dupack. */
#define TCP_USER_TIMEOUT         18 /* How long for loss retry before timeout. */
#define TCP_REPAIR               19 /* TCP sock is under repair right now. */
#define TCP_REPAIR_QUEUE         20 /* Set TCP queue to repair. */
#define TCP_QUEUE_SEQ            21 /* Set sequence number of repaired queue. */
#define TCP_REPAIR_OPTIONS       22 /* Repair TCP connection options. */
#define TCP_FASTOPEN             23 /* Enable FastOpen on listeners. */
#define TCP_TIMESTAMP            24 /* TCP time stamp. */
#define TCP_NOTSENT_LOWAT        25 /* Limit number of unsent bytes in write queue. */
#define TCP_CC_INFO              26 /* Get Congestion Control (optional) info. */
#define TCP_SAVE_SYN             27 /* Record SYN headers for new connections. */
#define TCP_SAVED_SYN            28 /* Get SYN headers recorded for connection. */

#ifdef __USE_MISC
#include <bits/os/sockaddr_storage.h>
#include <bits/types.h>
#include <net/bits/types.h>

#ifdef __USE_GLIBC_BLOAT
#include <sys/types.h>
#include <sys/socket.h>
#endif /* __USE_GLIBC_BLOAT */

__SYSDECL_BEGIN

#ifdef __CC__
typedef __u_net32_t tcp_seq;
#endif /* __CC__ */

/* Bits for `th_flags' */
#define TH_FIN  0x01
#define TH_SYN  0x02
#define TH_RST  0x04
#define TH_PUSH 0x08
#define TH_ACK  0x10
#define TH_URG  0x20

/* TCP header. (Per RFC 793, September, 1981). */
#ifdef __CC__
struct tcphdr {
#ifdef __USE_KOS_PURE
	__u_net16_t  th_sport;   /* source port. */
	__u_net16_t  th_dport;   /* destination port. */
	tcp_seq      th_seq;     /* sequence number. */
	tcp_seq      th_ack;     /* acknowledgement number. */
#if __BYTE_ORDER == __LITTLE_ENDIAN
	__HYBRID_BITFIELD8_T th_x2 : 4;  /* (unused) */
	__HYBRID_BITFIELD8_T th_off : 4; /* data offset */
#elif __BYTE_ORDER == __BIG_ENDIAN
	__HYBRID_BITFIELD8_T th_off : 4; /* data offset */
	__HYBRID_BITFIELD8_T th_x2 : 4;  /* (unused) */
#endif
	__uint8_t    th_flags;   /* Set of `TH_*' */
	__u_net16_t  th_win;     /* window */
	__u_net16_t  th_sum;     /* checksum */
	__u_net16_t  th_urp;     /* urgent pointer */
#elif (defined(__COMPILER_HAVE_TRANSPARENT_STRUCT) && \
       defined(__COMPILER_HAVE_TRANSPARENT_UNION))
	union {
		struct {
			__u_net16_t  th_sport;   /* source port. */
			__u_net16_t  th_dport;   /* destination port. */
			tcp_seq      th_seq;     /* sequence number. */
			tcp_seq      th_ack;     /* acknowledgement number. */
#if __BYTE_ORDER == __LITTLE_ENDIAN
			__HYBRID_BITFIELD8_T th_x2 : 4;  /* (unused) */
			__HYBRID_BITFIELD8_T th_off : 4; /* data offset */
#elif __BYTE_ORDER == __BIG_ENDIAN
			__HYBRID_BITFIELD8_T th_off : 4; /* data offset */
			__HYBRID_BITFIELD8_T th_x2 : 4;  /* (unused) */
#endif
			__uint8_t    th_flags;   /* Set of `TH_*' */
			__u_net16_t  th_win;     /* window */
			__u_net16_t  th_sum;     /* checksum */
			__u_net16_t  th_urp;     /* urgent pointer */
		};
		struct {
			__u_net16_t source;  /* source port. */
			__u_net16_t dest;    /* destination port. */
			tcp_seq     seq;     /* sequence number. */
			tcp_seq     ack_seq; /* acknowledgement number. */
#if __BYTE_ORDER == __LITTLE_ENDIAN
			__HYBRID_BITFIELD8_T res1 : 4; /* (unused) */
			__HYBRID_BITFIELD8_T doff : 4; /* data offset */
			__HYBRID_BITFIELD8_T fin : 1;
			__HYBRID_BITFIELD8_T syn : 1;
			__HYBRID_BITFIELD8_T rst : 1;
			__HYBRID_BITFIELD8_T psh : 1;
			__HYBRID_BITFIELD8_T ack : 1;
			__HYBRID_BITFIELD8_T urg : 1;
			__HYBRID_BITFIELD8_T res2 : 2; /* (unused) */
#elif __BYTE_ORDER == __BIG_ENDIAN
			__HYBRID_BITFIELD8_T doff : 4; /* data offset */
			__HYBRID_BITFIELD8_T res1 : 4; /* (unused) */
			__HYBRID_BITFIELD8_T res2 : 2; /* (unused) */
			__HYBRID_BITFIELD8_T urg : 1;
			__HYBRID_BITFIELD8_T ack : 1;
			__HYBRID_BITFIELD8_T psh : 1;
			__HYBRID_BITFIELD8_T rst : 1;
			__HYBRID_BITFIELD8_T syn : 1;
			__HYBRID_BITFIELD8_T fin : 1;
#endif
			__u_net16_t window;  /* window */
			__u_net16_t check;   /* checksum */
			__u_net16_t urg_ptr; /* urgent pointer */
		};
	};
#else /* ... */
#ifdef __COMPILER_HAVE_TRANSPARENT_UNION
	union {
		__u_net16_t  th_sport;   /* source port. */
		__u_net16_t  source;     /* source port. */
	};
	union {
		__u_net16_t  th_dport;   /* destination port. */
		__u_net16_t  dest;       /* destination port. */
	};
	union {
		tcp_seq      th_seq;     /* sequence number. */
		tcp_seq      seq;        /* sequence number. */
	};
	union {
		tcp_seq      th_ack;     /* acknowledgement number. */
		tcp_seq      ack_seq;    /* acknowledgement number. */
	};
#else /* __COMPILER_HAVE_TRANSPARENT_UNION */
	__u_net16_t      source;     /* source port. */
	__u_net16_t      dest;       /* destination port. */
	tcp_seq          seq;        /* sequence number. */
	tcp_seq          ack_seq;    /* acknowledgement number. */
#define th_sport     source      /* source port. */
#define th_dport     dest        /* destination port. */
#define th_seq       seq         /* sequence number. */
#define th_ack       ack_seq     /* acknowledgement number. */
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
#if __BYTE_ORDER == __LITTLE_ENDIAN
	__HYBRID_BITFIELD8_T res1 : 4; /* (unused) */
	__HYBRID_BITFIELD8_T doff : 4; /* data offset */
#elif __BYTE_ORDER == __BIG_ENDIAN
	__HYBRID_BITFIELD8_T doff : 4; /* data offset */
	__HYBRID_BITFIELD8_T res1 : 4; /* (unused) */
#endif
#define th_x2  res1 /* (unused) */
#define th_off doff /* data offset */
	union {
		__uint8_t    th_flags;   /* Set of `TH_*' */
		struct {
#if __BYTE_ORDER == __LITTLE_ENDIAN
			__HYBRID_BITFIELD8_T fin : 1;
			__HYBRID_BITFIELD8_T syn : 1;
			__HYBRID_BITFIELD8_T rst : 1;
			__HYBRID_BITFIELD8_T psh : 1;
			__HYBRID_BITFIELD8_T ack : 1;
			__HYBRID_BITFIELD8_T urg : 1;
			__HYBRID_BITFIELD8_T res2 : 2;
#elif __BYTE_ORDER == __BIG_ENDIAN
			__HYBRID_BITFIELD8_T res2 : 2;
			__HYBRID_BITFIELD8_T urg : 1;
			__HYBRID_BITFIELD8_T ack : 1;
			__HYBRID_BITFIELD8_T psh : 1;
			__HYBRID_BITFIELD8_T rst : 1;
			__HYBRID_BITFIELD8_T syn : 1;
			__HYBRID_BITFIELD8_T fin : 1;
#endif
		}
#ifndef __COMPILER_HAVE_TRANSPARENT_STRUCT
		_th_flag_bits
#define fin  _th_flag_bits.fin
#define syn  _th_flag_bits.syn
#define rst  _th_flag_bits.rst
#define psh  _th_flag_bits.psh
#define ack  _th_flag_bits.ack
#define urg  _th_flag_bits.urg
#define res2 _th_flag_bits.res2
#endif /* !__COMPILER_HAVE_TRANSPARENT_STRUCT */
		;
	}
#ifndef __COMPILER_HAVE_TRANSPARENT_UNION
	_th_flags_and_bits
#define th_flags _th_flags_and_bits.th_flags
#ifdef __COMPILER_HAVE_TRANSPARENT_STRUCT
#undef fin
#undef syn
#undef rst
#undef psh
#undef ack
#undef urg
#undef res2
#define fin  _th_flags_and_bits._th_flag_bits.fin
#define syn  _th_flags_and_bits._th_flag_bits.syn
#define rst  _th_flags_and_bits._th_flag_bits.rst
#define psh  _th_flags_and_bits._th_flag_bits.psh
#define ack  _th_flags_and_bits._th_flag_bits.ack
#define urg  _th_flags_and_bits._th_flag_bits.urg
#define res2 _th_flags_and_bits._th_flag_bits.res2
#else /* __COMPILER_HAVE_TRANSPARENT_STRUCT */
#define fin  _th_flags_and_bits.fin
#define syn  _th_flags_and_bits.syn
#define rst  _th_flags_and_bits.rst
#define psh  _th_flags_and_bits.psh
#define ack  _th_flags_and_bits.ack
#define urg  _th_flags_and_bits.urg
#define res2 _th_flags_and_bits.res2
#endif /* !__COMPILER_HAVE_TRANSPARENT_STRUCT */
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
	;
#ifdef __COMPILER_HAVE_TRANSPARENT_UNION
	union {
		__u_net16_t th_win;  /* window */
		__u_net16_t window;  /* window */
	};
	union {
		__u_net16_t th_sum;  /* checksum */
		__u_net16_t check;   /* checksum */
	};
	union {
		__u_net16_t th_urp;  /* urgent pointer */
		__u_net16_t urg_ptr; /* urgent pointer */
	};
#else /* __COMPILER_HAVE_TRANSPARENT_UNION */
	__u_net16_t window;  /* window */
	__u_net16_t check;   /* checksum */
	__u_net16_t urg_ptr; /* urgent pointer */
#define th_win  window   /* window */
#define th_sum  check    /* checksum */
#define th_urp  urg_ptr  /* urgent pointer */
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
#endif /* !... */
};
#endif /* __CC__ */

/*[[[enum]]]*/
#ifdef __CC__
enum {
	TCP_ESTABLISHED = 1,
	TCP_SYN_SENT    = 2,
	TCP_SYN_RECV    = 3,
	TCP_FIN_WAIT1   = 4,
	TCP_FIN_WAIT2   = 5,
	TCP_TIME_WAIT   = 6,
	TCP_CLOSE       = 7,
	TCP_CLOSE_WAIT  = 8,
	TCP_LAST_ACK    = 9,
	TCP_LISTEN      = 10,
	TCP_CLOSING     = 11, /* not a valid state */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define TCP_ESTABLISHED TCP_ESTABLISHED
#define TCP_SYN_SENT    TCP_SYN_SENT
#define TCP_SYN_RECV    TCP_SYN_RECV
#define TCP_FIN_WAIT1   TCP_FIN_WAIT1
#define TCP_FIN_WAIT2   TCP_FIN_WAIT2
#define TCP_TIME_WAIT   TCP_TIME_WAIT
#define TCP_CLOSE       TCP_CLOSE
#define TCP_CLOSE_WAIT  TCP_CLOSE_WAIT
#define TCP_LAST_ACK    TCP_LAST_ACK
#define TCP_LISTEN      TCP_LISTEN
#define TCP_CLOSING     TCP_CLOSING     /* not a valid state */
#else /* __COMPILER_PREFERR_ENUMS */
#define TCP_ESTABLISHED 1
#define TCP_SYN_SENT    2
#define TCP_SYN_RECV    3
#define TCP_FIN_WAIT1   4
#define TCP_FIN_WAIT2   5
#define TCP_TIME_WAIT   6
#define TCP_CLOSE       7
#define TCP_CLOSE_WAIT  8
#define TCP_LAST_ACK    9
#define TCP_LISTEN      10
#define TCP_CLOSING     11 /* not a valid state */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/




#define TCPOPT_EOL              0
#define TCPOPT_NOP              1
#define TCPOPT_MAXSEG           2
#define TCPOLEN_MAXSEG          4
#define TCPOPT_WINDOW           3
#define TCPOLEN_WINDOW          3
#define TCPOPT_SACK_PERMITTED   4 /* Experimental */
#define TCPOLEN_SACK_PERMITTED  2
#define TCPOPT_SACK             5 /* Experimental */
#define TCPOPT_TIMESTAMP        8
#define TCPOLEN_TIMESTAMP       10
#define TCPOLEN_TSTAMP_APPA    (TCPOLEN_TIMESTAMP+2) /* appendix A */
#define TCPOPT_TSTAMP_HDR      (TCPOPT_NOP<<24|TCPOPT_NOP<<16|TCPOPT_TIMESTAMP<<8|TCPOLEN_TIMESTAMP)

/* Default maximum segment size for TCP.
 * With an IP MSS  of 576, this is  536,
 * but 512 is probably more  convenient.
 * This should be defined as MIN(512, IP_MSS - sizeof(struct tcpiphdr)). */
#define TCP_MSS                 512
#define TCP_MAXWIN              65535 /* largest value for (unscaled) window */
#define TCP_MAX_WINSHIFT        14    /* maximum window shift */
#define SOL_TCP                 6     /* TCP level */

#define TCPI_OPT_TIMESTAMPS     1
#define TCPI_OPT_SACK           2
#define TCPI_OPT_WSCALE         4
#define TCPI_OPT_ECN            8  /* ECN was negociated at TCP session init */
#define TCPI_OPT_ECN_SEEN       16 /* we received at least one packet with ECT */
#define TCPI_OPT_SYN_DATA       32 /* SYN-ACK acked data in SYN sent or rcvd */

/* Values for tcpi_state. */
/*[[[enum]]]*/
#ifdef __CC__
enum tcp_ca_state {
	TCP_CA_Open     = 0,
	TCP_CA_Disorder = 1,
	TCP_CA_CWR      = 2,
	TCP_CA_Recovery = 3,
	TCP_CA_Loss     = 4
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define TCP_CA_Open     TCP_CA_Open
#define TCP_CA_Disorder TCP_CA_Disorder
#define TCP_CA_CWR      TCP_CA_CWR
#define TCP_CA_Recovery TCP_CA_Recovery
#define TCP_CA_Loss     TCP_CA_Loss
#else /* __COMPILER_PREFERR_ENUMS */
#define TCP_CA_Open     0
#define TCP_CA_Disorder 1
#define TCP_CA_CWR      2
#define TCP_CA_Recovery 3
#define TCP_CA_Loss     4
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

#ifdef __CC__
struct tcp_info {
	__uint8_t  tcpi_state;
	__uint8_t  tcpi_ca_state;
	__uint8_t  tcpi_retransmits;
	__uint8_t  tcpi_probes;
	__uint8_t  tcpi_backoff;
	__uint8_t  tcpi_options;
	__uint8_t  tcpi_snd_wscale : 4;
	__uint8_t  tcpi_rcv_wscale : 4;
	__uint32_t tcpi_rto;
	__uint32_t tcpi_ato;
	__uint32_t tcpi_snd_mss;
	__uint32_t tcpi_rcv_mss;
	__uint32_t tcpi_unacked;
	__uint32_t tcpi_sacked;
	__uint32_t tcpi_lost;
	__uint32_t tcpi_retrans;
	__uint32_t tcpi_fackets;
	/* Times. */
	__uint32_t tcpi_last_data_sent;
	__uint32_t tcpi_last_ack_sent; /* Not remembered, sorry. */
	__uint32_t tcpi_last_data_recv;
	__uint32_t tcpi_last_ack_recv;
	/* Metrics. */
	__uint32_t tcpi_pmtu;
	__uint32_t tcpi_rcv_ssthresh;
	__uint32_t tcpi_rtt;
	__uint32_t tcpi_rttvar;
	__uint32_t tcpi_snd_ssthresh;
	__uint32_t tcpi_snd_cwnd;
	__uint32_t tcpi_advmss;
	__uint32_t tcpi_reordering;
	__uint32_t tcpi_rcv_rtt;
	__uint32_t tcpi_rcv_space;
	__uint32_t tcpi_total_retrans;
};
#endif /* __CC__ */

/* For TCP_MD5SIG socket option. */
#define TCP_MD5SIG_MAXKEYLEN    80

#ifdef __CC__
struct tcp_md5sig {
	struct sockaddr_storage tcpm_addr;   /* Address associated. */
	__uint16_t            __tcpm_pad1;   /* Zero. */
	__uint16_t              tcpm_keylen; /* Key length. */
	__uint32_t            __tcpm_pad2;   /* Zero. */
	__uint8_t               tcpm_key[TCP_MD5SIG_MAXKEYLEN]; /* Key (binary). */
};
#endif /* __CC__ */

/* For socket repair options. */
#ifdef __CC__
struct tcp_repair_opt {
	__uint32_t opt_code;
	__uint32_t opt_val;
};
#endif /* __CC__ */

/* Queue to repair, for TCP_REPAIR_QUEUE. */
/*[[[enum]]]*/
#ifdef __CC__
enum {
	TCP_NO_QUEUE   = 0,
	TCP_RECV_QUEUE = 1,
	TCP_SEND_QUEUE = 2,
	TCP_QUEUES_NR  = 3,
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define TCP_NO_QUEUE   TCP_NO_QUEUE
#define TCP_RECV_QUEUE TCP_RECV_QUEUE
#define TCP_SEND_QUEUE TCP_SEND_QUEUE
#define TCP_QUEUES_NR  TCP_QUEUES_NR
#else /* __COMPILER_PREFERR_ENUMS */
#define TCP_NO_QUEUE   0
#define TCP_RECV_QUEUE 1
#define TCP_SEND_QUEUE 2
#define TCP_QUEUES_NR  3
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

/* For cookie transactions socket options. */
#define TCP_COOKIE_MIN         8  /*  64-bits */
#define TCP_COOKIE_MAX         16 /* 128-bits */
#define TCP_COOKIE_PAIR_SIZE  (2*TCP_COOKIE_MAX)

/* Flags for both getsockopt and setsockopt */
#define TCP_COOKIE_IN_ALWAYS  (1 << 0) /* Discard SYN without cookie */
#define TCP_COOKIE_OUT_NEVER  (1 << 1) /* Prohibit outgoing cookies, supersedes everything. */

/* Flags for getsockopt */
#define TCP_S_DATA_IN         (1 << 2) /* Was data received? */
#define TCP_S_DATA_OUT        (1 << 3) /* Was data sent? */

#define TCP_MSS_DEFAULT         536U   /* IPv4 (RFC1122, RFC2581) */
#define TCP_MSS_DESIRED        1220U   /* IPv6 (tunneled), EDNS0 (RFC3226) */

#ifdef __CC__
struct tcp_cookie_transactions {
	__uint16_t   tcpct_flags;
	__uint8_t  __tcpct_pad1;
	__uint8_t    tcpct_cookie_desired;
	__uint16_t   tcpct_s_data_desired;
	__uint16_t   tcpct_used;
	__uint8_t    tcpct_value[TCP_MSS_DEFAULT];
};
#endif /* __CC__ */

__SYSDECL_END

#endif /* __USE_MISC */

#endif /* !_NETINET_TCP_H */
