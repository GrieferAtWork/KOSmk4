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
#ifndef _BITS_CRT_GAICB_H
#define _BITS_CRT_GAICB_H 1

#include <__stdinc.h>
#include <features.h>

#ifdef __CC__
__DECL_BEGIN

/* Structure used as control block for asynchronous lookup. */
struct gaicb {
	/* XXX: It's unclear if ar_name can be NULL! */
	char const            *ar_name;    /* [0..1] Name to look up. */
	/* XXX: It's unclear if ar_service can be NULL! */
	char const            *ar_service; /* [0..1] Service name. */
	/* XXX: It's unclear if ar_request can be NULL! */
	struct addrinfo const *ar_request; /* [0..1] Additional request specification. */
	/* XXX: It's unclear if ar_result can be NULL! */
	struct addrinfo       *ar_result;  /* [0..1] Pointer to result. */
	/* The following are internal elements. */
	__STDC_INT_AS_SIZE_T __return;
	__STDC_INT_AS_SIZE_T __glibc_reserved[5];
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_GAICB_H */
