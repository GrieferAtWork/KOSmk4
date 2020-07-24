/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_LIBC_TLS_C
#define GUARD_LIBC_LIBC_TLS_C 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <kos/except.h>
#include <kos/types.h>

#include "tls.h"

DECL_BEGIN

/* LIBC per-thread data instance. */
INTERN ATTR_THREAD struct libc_tls tls = {
	/* .t_errno_value = */ 0,
	/* .t_errno_kind  = */ LIBC_ERRNO_KIND_KOS,
	/* .t_pthread     = */ NULL,
	/* .t_except      = */ {
		/* .ei_state = */ {},
#if EXCEPT_BACKTRACE_SIZE != 0
		/* .ei_trace = */ {},
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
		/* .ei_flags = */ EXCEPT_FNORMAL,
		{
			/* .ei_code = */ ERROR_CODEOF(E_OK)
		}
	},
#ifdef CONFIG_LIBC_HAVE_CACHED_TID
	/* .t_tid         = */ 0
#endif /* CONFIG_LIBC_HAVE_CACHED_TID */
};


DECL_END

#endif /* !GUARD_LIBC_LIBC_TLS_C */
