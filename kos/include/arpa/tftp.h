/* HASH CRC-32:0x7f9abd8a */
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
#ifndef _ARPA_TFTP_H
#define _ARPA_TFTP_H 1

#include <__stdinc.h>

/* ??? */

#define SEGSIZE 512 /* ??? */

/* ??? */
#define RRQ   1 /* ??? */
#define WRQ   2 /* ??? */
#define DATA  3 /* ??? */
#define ACK   4 /* ??? */
#define ERROR 5 /* ??? */

#ifdef __CC__
__DECL_BEGIN

struct __ATTR_PACKED tftphdr {
	short th_opcode; /* ??? */
	union __ATTR_PACKED {
		char tu_padding[3]; /* ??? */
		struct __ATTR_PACKED {
			union __ATTR_PACKED {
				unsigned short tu_block; /* ??? */
				short tu_code;           /* ??? */
			} th_u3;
			char tu_data[0]; /* ??? */
		} th_u2;
		char tu_stuff[0]; /* ??? */
	} th_u1;
};
#define th_block th_u1.th_u2.th_u3.tu_block
#define th_code  th_u1.th_u2.th_u3.tu_code
#define th_stuff th_u1.tu_stuff
#define th_data  th_u1.th_u2.tu_data
#define th_msg   th_u1.th_u2.tu_data

__DECL_END
#endif /* __CC__ */

/* ??? */
#undef EUNDEF
#undef ENOTFOUND
#undef EACCESS
#undef ENOSPACE
#undef EBADOP
#undef EBADID
#undef EEXISTS
#undef ENOUSER
#define EUNDEF    0 /* ??? */
#define ENOTFOUND 1 /* ??? */
#define EACCESS   2 /* ??? */
#define ENOSPACE  3 /* ??? */
#define EBADOP    4 /* ??? */
#define EBADID    5 /* ??? */
#define EEXISTS   6 /* ??? */
#define ENOUSER   7 /* ??? */

#endif /* !_ARPA_TFTP_H */
