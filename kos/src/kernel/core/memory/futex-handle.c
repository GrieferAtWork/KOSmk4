/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MEMORY_FUTEX_HANDLE_C
#define GUARD_KERNEL_SRC_MEMORY_FUTEX_HANDLE_C 1
#define _KOS_SOURCE 1
#define _TIME64_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/handle-proto.h>
#include <kernel/handle.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mpartmeta.h>
#include <sched/cred.h>

#include <hybrid/atomic.h>

#include <kos/except/reason/inval.h>
#include <kos/hop/futex.h>

#include <errno.h>

DECL_BEGIN

/* futex handle operation. */
DEFINE_HANDLE_REFCNT_FUNCTIONS(futex, struct mfutex);

INTDEF NONNULL((1)) syscall_slong_t KCALL
handle_futex_hop(struct mfutex *__restrict self, syscall_ulong_t cmd,
                 USER UNCHECKED void *arg, iomode_t mode) THROWS(...) {
	switch (cmd) {

	case HOP_FUTEX_OPEN_MPART: {
		struct handle hnd;
		REF struct mpart *part;
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		part = mfutex_getpart(self);
		if (!part)
			return -EOWNERDEAD;
		FINALLY_DECREF_UNLIKELY(part);
		hnd.h_type = HANDLE_TYPE_MPART;
		hnd.h_mode = mode;
		hnd.h_data = part;
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, hnd);
	}	break;

	case HOP_FUTEX_OPEN_MFILE: {
		struct handle hnd;
		REF struct mfile *file;
		REF struct mpart *part;
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		part = mfutex_getpart(self);
		if (!part)
			return -EOWNERDEAD;
		{
			FINALLY_DECREF_UNLIKELY(part);
			mpart_lock_acquire(part);
			file = incref(part->mp_file);
			mpart_lock_release(part);
		}
		FINALLY_DECREF_UNLIKELY(file);
		hnd.h_type = HANDLE_TYPE_MFILE;
		hnd.h_mode = mode;
		hnd.h_data = file;
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, hnd);
	}	break;

	case HOP_FUTEX_ISWAITING:
		return mfutex_iswaiting(self) ? 1 : 0;

	case HOP_FUTEX_BROADCAST:
		return mfutex_broadcast(self);

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND,
		      cmd);
		break;
	}
	return 0;
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_FUTEX_HANDLE_C */
