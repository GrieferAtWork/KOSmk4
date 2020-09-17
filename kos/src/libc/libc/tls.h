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
#ifndef GUARD_LIBC_LIBC_TLS_H
#define GUARD_LIBC_LIBC_TLS_H 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <kos/except.h>
#include <kos/types.h>

DECL_BEGIN

#ifndef __KERNEL__


/* The different kinds of errno codes known to libc */
#define LIBC_ERRNO_KIND_KOS 0 /* __GEN_E* */
#define LIBC_ERRNO_KIND_DOS 1 /* __DOS_E* */
#define LIBC_ERRNO_KIND_NT  2 /* NT error codes */
#define LIBC_ERRNO_KIND_CYG 3 /* __CYG_E* */

#undef CONFIG_LIBC_HAVE_CACHED_TID
#if 1
#define CONFIG_LIBC_HAVE_CACHED_TID 1
#endif

#ifdef __CC__

struct pthread;
struct libc_tls {
	errno_t               t_errno_value; /* Errno value */
	unsigned int          t_errno_kind;  /* Errno kind (one of `LIBC_ERRNO_KIND_*') */
	struct pthread       *t_pthread;     /* [0..1] pthread_self() (lazily allocated) */
	struct exception_info t_except;      /* Exception information */
#ifdef CONFIG_LIBC_HAVE_CACHED_TID
	pid_t                 t_tid;         /* Calling thread TID (lazily initialized) */
#endif /* CONFIG_LIBC_HAVE_CACHED_TID */
};

/* LIBC per-thread data instance. */
INTDEF ATTR_THREAD struct libc_tls tls;

#endif /* __CC__ */
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_LIBC_TLS_H */
