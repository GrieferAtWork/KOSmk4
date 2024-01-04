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
#ifndef _BITS_OS_KOS_TERMIOS_H
#define _BITS_OS_KOS_TERMIOS_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#define NCCS 32

#ifdef __CC__
__DECL_BEGIN

typedef __UINT8_TYPE__  cc_t;
typedef __UINT32_TYPE__ speed_t;
typedef __UINT32_TYPE__ tcflag_t;

struct termios {
	tcflag_t c_iflag;    /* input mode flags. */
	tcflag_t c_oflag;    /* output mode flags. */
	tcflag_t c_cflag;    /* control mode flags. */
	tcflag_t c_lflag;    /* local mode flags. */
	cc_t     c_line;     /* line discipline. */
	cc_t     c_cc[NCCS]; /* control characters. */
	speed_t  c_ispeed;   /* input speed. */
	speed_t  c_ospeed;   /* output speed. */
};
struct termios2 {
	tcflag_t c_iflag;    /* input mode flags. */
	tcflag_t c_oflag;    /* output mode flags. */
	tcflag_t c_cflag;    /* control mode flags. */
	tcflag_t c_lflag;    /* local mode flags. */
	cc_t     c_line;     /* line discipline. */
	cc_t     c_cc[19];   /* control characters. */
	speed_t  c_ispeed;   /* input speed. */
	speed_t  c_ospeed;   /* output speed. */
};

__DECL_END
#endif /* __CC__ */

#define _HAVE_STRUCT_TERMIOS_C_ISPEED 1
#define _HAVE_STRUCT_TERMIOS_C_OSPEED 1

#define _IOT_termios /* Hurd ioctl type field. */ \
	_IOT(_IOTS(cflag_t), 4, _IOTS(cc_t), NCCS, _IOTS(speed_t), 2)

#endif /* !_BITS_OS_KOS_TERMIOS_H */
