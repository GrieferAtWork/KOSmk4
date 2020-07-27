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
#ifndef GUARD_LIBC_LIBC_PTHREAD_H
#define GUARD_LIBC_LIBC_PTHREAD_H 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <kos/types.h>
#include <kos/anno.h>
#include <sched.h>

DECL_BEGIN


#define OFFSET_PTHREAD_TID       0
#define OFFSET_PTHREAD_REFCNT    (__SIZEOF_POINTER__ * 1)
#define OFFSET_PTHREAD_RETVAL    (__SIZEOF_POINTER__ * 2)
#define OFFSET_PTHREAD_TLS       (__SIZEOF_POINTER__ * 3)
#define OFFSET_PTHREAD_STACKADDR (__SIZEOF_POINTER__ * 4)
#define OFFSET_PTHREAD_STACKSIZE (__SIZEOF_POINTER__ * 5)
#define OFFSET_PTHREAD_FLAGS     (__SIZEOF_POINTER__ * 6)

#define PTHREAD_FNORMAL    0x0000 /* Normal pthread flags. */
#define PTHREAD_FUSERSTACK 0x0001 /* The thread's stack was provided by the user
                                   * and should not be unmapped automatically. */
#define PTHREAD_FNOSTACK   0x0002 /* The thread's stack area is unknown (this is the case for
                                   * the main thread, and any thread created by `clone()'). */

#ifdef __CC__
struct pthread {
	pid_t           pt_tid;        /* [const] Secondary TID (filled in by the kernel as the PTID and CTID) */
#if __SIZEOF_PID_T__ < __SIZEOF_POINTER__
	byte_t __pt_pad[__SIZEOF_POINTER__ - __SIZEOF_PID_T__];
#endif
	__WEAK refcnt_t pt_refcnt;     /* Reference counter for this control structure. */
	void           *pt_retval;     /* [lock(WRITE_ONCE)] Thread return value (as passed to `pthread_exit()') (also used as argument for `pt_start') */
	void           *pt_tls;        /* [const] TLS segment base address (allocated by `dltlsallocseg()', freed in `pthread_exit()') */
	void           *pt_stackaddr;  /* [const] Thread stack address */
	size_t          pt_stacksize;  /* [const] Thread stack size */
	uintptr_t       pt_flags;      /* [const] Flags (Set of `PTHREAD_F*') */
	cpu_set_t      *pt_cpuset;     /* Initial affinity cpuset. */
	size_t          pt_cpusetsize; /* Initial affinity cpuset size. */
};
#endif /* __CC__ */

DECL_END

#endif /* !GUARD_LIBC_LIBC_PTHREAD_H */
