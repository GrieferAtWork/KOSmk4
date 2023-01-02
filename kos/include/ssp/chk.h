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
#ifndef _SSP_CHK_H
#define _SSP_CHK_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <hybrid/__assert.h>
#include <hybrid/typecore.h>

#include <bits/crt/inttypes.h>

__DECL_BEGIN

#ifdef __CC__
#ifdef __PRIP_PREFIX
#define __ssp_chk_dstbuf(funcname, buf, required_bufsize, available_bufsize)        \
	do {                                                                            \
		if ((available_bufsize) != (__SIZE_TYPE__)-1) {                             \
			__hybrid_assertf((required_bufsize) <= (available_bufsize),             \
			                 "%s: Buffer at %p (%" __PRIP_PREFIX "u bytes) is "     \
			                 "smaller than the accessed %" __PRIP_PREFIX "u bytes", \
			                 funcname, buf, required_bufsize, available_bufsize);   \
		}                                                                           \
	}	__WHILE0
#else /* __PRIP_PREFIX */
#define __ssp_chk_dstbuf(funcname, buf, required_bufsize, available_bufsize)      \
	do {                                                                          \
		if ((available_bufsize) != (__SIZE_TYPE__)-1) {                           \
			__hybrid_assertf((required_bufsize) <= (available_bufsize),           \
			                 "%s: Buffer at %p (%zu bytes) is "                   \
			                 "smaller than the accessed %zu bytes",               \
			                 funcname, buf, required_bufsize, available_bufsize); \
		}                                                                         \
	}	__WHILE0
#endif /* !__PRIP_PREFIX */
#endif /* __CC__ */

__DECL_END

#endif /* !_SSP_CHK_H */
