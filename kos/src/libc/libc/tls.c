/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
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

#include <errno.h>
#include <signal.h>

#include "tls.h"

DECL_BEGIN

/* LIBC per-thread data instance. */
INTERN ATTR_THREAD struct pthread current = {
#ifdef __LIBC_CONFIG_HAVE_USERPROCMASK
	.pt_pmask = {
		.lpm_pmask = USERPROCMASK_INIT(/* mytid:   */ 0,
		                               /* sigsize: */ sizeof(sigset_t),
		                               /* sigmask: */ NULL,
		                               /* flags:   */ USERPROCMASK_FLAG_NORMAL,
		                               /* pending: */ SIGSET_INIT_EMPTY),
		.lpm_masks = {
			[0] = SIGSET_INIT_EMPTY,
			[1] = SIGSET_INIT_EMPTY
		}
	},
#else /* __LIBC_CONFIG_HAVE_USERPROCMASK */
	.pt_tid         = 0,
#endif /* !__LIBC_CONFIG_HAVE_USERPROCMASK */
	.pt_refcnt      = 2,
	.pt_retval      = NULL,
	.pt_tls         = NULL,
	.pt_stackaddr   = NULL,
	.pt_stacksize   = 0,
	.pt_flags       = PTHREAD_FUSERSTACK | PTHREAD_FNOSTACK,
	.pt_pidfd       = -1,
	.pt_suspended   = 0,
	.pt_cpuset      = NULL,
	.pt_cpusetsize  = 0,
	.pt_except = {
		.ei_state = {},
		{ .ei_code = EXCEPT_CODEOF(E_OK) },
#if EXCEPT_BACKTRACE_SIZE != 0
		.ei_trace = { NULL, },
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
		.ei_flags = EXCEPT_FNORMAL,
		.ei_nesting = 0,
	},
	.pt_errno_kind  = LIBC_ERRNO_KIND_KOS,
	.pt_errno_value = EOK,
	.pt_tglobals    = NULL
};


DECL_END

#endif /* !GUARD_LIBC_LIBC_TLS_C */
