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
#ifndef _BITS_CRT_DB_TTYENT_H
#define _BITS_CRT_DB_TTYENT_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <hybrid/typecore.h>

#ifdef __CC__
__DECL_BEGIN

struct ttyent {
	char           *ty_name;    /* [1..1] terminal device name (without "/dev/" prefix) */
	char           *ty_getty;   /* [1..1] command to execute, usually getty */
	char           *ty_type;    /* [1..1] terminal type for termcap */
	int             ty_status;  /* status flags (Set of `TTY_ON | TTY_SECURE') */
#if __SIZEOF_POINTER__ >= __SIZEOF_INT__
	__BYTE_TYPE__ __ty_pad[__SIZEOF_POINTER__ - __SIZEOF_INT__]; /* ... */
#endif /* __SIZEOF_POINTER__ >= __SIZEOF_INT__ */
	char           *ty_window;  /* [0..1] command to start up window manager */
	char           *ty_comment; /* [0..1] comment field */
#if !defined(__CRT_GLC_PRIMARY)
	char           *ty_group;   /* [0..1] TTY group */
#endif /* !__CRT_GLC_PRIMARY */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_DB_TTYENT_H */
