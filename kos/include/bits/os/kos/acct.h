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
#ifndef _BITS_OS_KOS_ACCT_H
#define _BITS_OS_KOS_ACCT_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

__DECL_BEGIN

#define ACCT_COMM 16
#define AHZ       100

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define ACCT_BYTEORDER 0x80
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
#define ACCT_BYTEORDER 0x00
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */

/*[[[enum]]]*/
#ifdef __CC__
enum {
	AFORK = 0x01, /* ??? */
	ASU   = 0x02, /* ??? */
	ACORE = 0x08, /* ??? */
	AXSIG = 0x10  /* ??? */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define AFORK AFORK /* ??? */
#define ASU   ASU   /* ??? */
#define ACORE ACORE /* ??? */
#define AXSIG AXSIG /* ??? */
#else /* __COMPILER_PREFERR_ENUMS */
#define AFORK 1  /* ??? */
#define ASU   2  /* ??? */
#define ACORE 8  /* ??? */
#define AXSIG 16 /* ??? */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/


#ifdef __CC__
typedef __UINT16_TYPE__ comp_t;

struct acct {
	__BYTE_TYPE__   ac_flag;                /* ??? */
	__UINT16_TYPE__ ac_uid;                 /* ??? */
	__UINT16_TYPE__ ac_gid;                 /* ??? */
	__UINT16_TYPE__ ac_tty;                 /* ??? */
	__UINT32_TYPE__ ac_btime;               /* ??? */
	comp_t          ac_utime;               /* ??? */
	comp_t          ac_stime;               /* ??? */
	comp_t          ac_etime;               /* ??? */
	comp_t          ac_mem;                 /* ??? */
	comp_t          ac_io;                  /* ??? */
	comp_t          ac_rw;                  /* ??? */
	comp_t          ac_minflt;              /* ??? */
	comp_t          ac_majflt;              /* ??? */
	comp_t          ac_swaps;               /* ??? */
	__UINT32_TYPE__ ac_exitcode;            /* ??? */
	__CHAR8_TYPE__  ac_comm[ACCT_COMM + 1]; /* ??? */
	__BYTE_TYPE__   ac_pad[10];             /* ??? */
};

struct acct_v3 {
	__BYTE_TYPE__   ac_flag;            /* ??? */
	__BYTE_TYPE__   ac_version;         /* ??? */
	__UINT16_TYPE__ ac_tty;             /* ??? */
	__UINT32_TYPE__ ac_exitcode;        /* ??? */
	__UINT32_TYPE__ ac_uid;             /* ??? */
	__UINT32_TYPE__ ac_gid;             /* ??? */
	__UINT32_TYPE__ ac_pid;             /* ??? */
	__UINT32_TYPE__ ac_ppid;            /* ??? */
	__UINT32_TYPE__ ac_btime;           /* ??? */
	float           ac_etime;           /* ??? */
	comp_t          ac_utime;           /* ??? */
	comp_t          ac_stime;           /* ??? */
	comp_t          ac_mem;             /* ??? */
	comp_t          ac_io;              /* ??? */
	comp_t          ac_rw;              /* ??? */
	comp_t          ac_minflt;          /* ??? */
	comp_t          ac_majflt;          /* ??? */
	comp_t          ac_swaps;           /* ??? */
	__CHAR8_TYPE__  ac_comm[ACCT_COMM]; /* ??? */
};
#endif /* __CC__ */

__DECL_END

#endif /* !_BITS_OS_KOS_ACCT_H */
