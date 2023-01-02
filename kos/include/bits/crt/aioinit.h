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
#ifndef _BITS_CRT_AIOINIT_H
#define _BITS_CRT_AIOINIT_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#ifdef __CC__
__DECL_BEGIN

struct aioinit {
	__INT32_TYPE__ aio_threads;   /* Max number of simultaneous live AIO service threads. */
	__INT32_TYPE__ aio_num;       /* ... */
	__INT32_TYPE__ aio_locks;     /* ... */
	__INT32_TYPE__ aio_usedba;    /* ... */
	__INT32_TYPE__ aio_debug;     /* ... */
	__INT32_TYPE__ aio_numusers;  /* ... */
	__INT32_TYPE__ aio_idle_time; /* Seconds until an idle AIO thread self-terminates */
	__INT32_TYPE__ aio_reserved;  /* ... */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_AIOINIT_H */
