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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_FUTEXFD_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_FUTEXFD_C 1

#include <kernel/compiler.h>

#include <kernel/handle-proto.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/futexfd.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/mpartmeta.h>
#include <kernel/mman/phys.h>
#include <misc/unlockinfo.h>

#include <compat/config.h>
#include <kos/asm/futex.h>
#include <kos/except.h>
#include <kos/futexexpr.h>
#include <kos/io.h>
#include <kos/kernel/memory.h>
#include <kos/types.h>

#include <stddef.h>
#include <stdint.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/kos/bits/futex-expr.h>
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN

/* Max # of expressions in `lfutexexpr()' when using `LFUTEX_FDBIT'
 * - The limit can be overwritten system-wide by use of "/proc/kos/futexfd-maxexpr"
 * - A thread with `CAP_SYS_RESOURCE' is always allowed to exceed this limit. */
PUBLIC ATTR_READMOSTLY size_t mfutexfd_maxexpr = LFUTEXFD_DEFAULT_MAXEXPR;


/* Destroy a given mem-futex-fd object. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfutexfd_destroy)(struct mfutexfd *__restrict self) {
	decref(self->mfd_futex);
	weakdecref(self->mfd_mman);
	kfree(self);
}

/* Handle operators for `HANDLE_TYPE_FUTEXFD' (`struct mfutexfd') */
DEFINE_HANDLE_REFCNT_FUNCTIONS(futexfd, struct mfutexfd);

INTERN BLOCKING NONNULL((1)) void KCALL
handle_futexfd_pollconnect(struct mfutexfd *__restrict self,
                           poll_mode_t what) THROWS(...) {
	if likely(what & POLLPRI)
		mfutex_connect_for_poll(self->mfd_futex);
}


struct unlock_mman_info: unlockinfo {
	struct mman *umi_mman; /* [1..1] MMan to unlock. */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL unlock_mman_info_unlock)(struct unlockinfo *__restrict self) {
	struct unlock_mman_info *me = (struct unlock_mman_info *)self;
	mman_lock_endread(me->umi_mman);
}


INTERN BLOCKING WUNUSED NONNULL((1)) poll_mode_t KCALL
handle_futexfd_polltest(struct mfutexfd *__restrict self,
                        poll_mode_t what) THROWS(...) {
	size_t i;
	struct unlock_mman_info unlock;
	struct lfutexexpr const *expr;
	struct mnode *node;
	struct mpart *part;
	mpart_reladdr_t expraddr;
	physaddr_t exprphys;
	union {
#ifdef LFUTEX_WAIT_32BIT
		uint32_t v32;
#endif /* LFUTEX_WAIT_32BIT */
#ifdef LFUTEX_WAIT_64BIT
		uint64_t v64;
#endif /* LFUTEX_WAIT_64BIT */
	} val;

	unlock.ui_unlock = &unlock_mman_info_unlock;
	unlock.umi_mman  = self->mfd_mman;
	if (!tryincref(unlock.umi_mman)) {
err_hup:
		return (what & POLLPRI) | POLLRDHUP | POLLHUP;
	}
	FINALLY_DECREF_UNLIKELY(unlock.umi_mman);
again_lock_mman:
	mman_lock_read(unlock.umi_mman);
	i    = 0;
	expr = &self->mfd_expr[0];
	goto begin_first_expression;
nextexpr:

	/* Lookup the mnode/mpart of this expression. */
	expr = &self->mfd_expr[i];
	if ((byte_t *)expr->fe_offset < (byte_t *)mnode_getminaddr(node) ||
	    (byte_t *)expr->fe_offset > (byte_t *)mnode_getmaxaddr(node)) {

		/* Release a lock from the previous part. */
		mpart_lock_release(part);

		/* Node differs from previous expression, or no node loaded yet. */
begin_first_expression:
		node = mman_mappings_locate(unlock.umi_mman, (void *)expr->fe_offset);

		/* Verify the existence of a node, and that it is readable. */
		if unlikely(!node || !(node->mn_flags & MNODE_F_PREAD)) {
			mman_lock_endread(unlock.umi_mman);
			goto err_hup;
		}

		part = node->mn_part;
		if unlikely(!part) {
			mman_lock_endread(unlock.umi_mman);
			goto err_hup;
		}

		/* Acquire a lock to the mem-part. */
		if (mpart_lock_tryacquire(part)) {
			incref(part);
			mman_lock_endread(unlock.umi_mman);
			FINALLY_DECREF_UNLIKELY(part);
			mpart_lock_waitfor(part);
			goto again_lock_mman;
		}

		/* Make sure that the mem-part is loaded into memory. */
		if (MPART_ST_INCORE(part->mp_state)) {
			struct mpart_setcore_data dat;
			incref(part); /* Reference needed in case an unlock must be done. */
			mpart_setcore_data_init(&dat);
			TRY {
				if (!mpart_setcore_or_unlock(part, &unlock, &dat)) {
					/* Force the part into the core. */
					do {
						mpart_lock_acquire(part);
					} while (!mpart_setcore_or_unlock(part, NULL, &dat));
					decref_unlikely(part);
					goto again_lock_mman;
				}
			} EXCEPT {
				decref_unlikely(part);
				mpart_setcore_data_fini(&dat);
				mpart_lockops_reap(part);
				RETHROW();
			}
			decref_nokill(part);
		}
	}

	/* Make sure the range accessed by the caller is allocated. */
	expraddr = mnode_getpartaddrat(node, expr->fe_offset);
	if (!mpart_load_or_unlock(part, &unlock, expraddr,
	                          LFUTEXEXPR_CMD_SIZEOF(expr->fe_condition)))
		goto again_lock_mman;

	/* Lookup physical address of expression value. */
	exprphys = mpart_getphysaddr(part, expraddr);

	/* Read expression value. */
#if defined(LFUTEX_WAIT_32BIT) && defined(LFUTEX_WAIT_64BIT)
	if (LFUTEX_WAIT_IS32(expr->fe_condition)) {
		val.v32 = peekphysl(exprphys);
	} else {
		val.v64 = peekphysq(exprphys);
	}
#elif defined(LFUTEX_WAIT_64BIT)
	val.v64 = peekphysq(exprphys);
#elif defined(LFUTEX_WAIT_32BIT)
	val.v32 = peekphysl(exprphys);
#else /* ... */
#error "Invalid configuration"
#endif /* !... */

	/* Evaluate the expression. */
	switch (expr->fe_condition) {

		/* Deal with special condition code: LFUTEX_EXPREND */
#ifdef LFUTEX_WAIT_32BIT
	case LFUTEX_WAIT_32BIT | LFUTEX_EXPREND:
#endif /* LFUTEX_WAIT_32BIT */
#ifdef LFUTEX_WAIT_64BIT
	case LFUTEX_WAIT_64BIT | LFUTEX_EXPREND:
#endif /* LFUTEX_WAIT_64BIT */
		/* Last expression reached, but none of them were true
		 * -> The condition being polled for isn't applicable
		 *    at the moment! */
		mpart_lock_release(part);
		mman_lock_endread(unlock.umi_mman);
		return 0;

		/* 32-bit expressions. */
#ifdef LFUTEX_WAIT_32BIT
	case LFUTEX_WAIT_32BIT | LFUTEX_WAIT_WHILE:
		if (val.v32 != (uint32_t)expr->fe_val)
			goto gotmatch;
		break;

	case LFUTEX_WAIT_32BIT | LFUTEX_WAIT_UNTIL:
		if (val.v32 == (uint32_t)expr->fe_val)
			goto gotmatch;
		break;

	case LFUTEX_WAIT_32BIT | LFUTEX_WAIT_WHILE_ABOVE:
		if (!(val.v32 > (uint32_t)expr->fe_val))
			goto gotmatch;
		break;

	case LFUTEX_WAIT_32BIT | LFUTEX_WAIT_WHILE_BELOW:
		if (!(val.v32 < (uint32_t)expr->fe_val))
			goto gotmatch;
		break;

	case LFUTEX_WAIT_32BIT | LFUTEX_WAIT_WHILE_BITMASK:
		if (!((val.v32 & (uint32_t)expr->fe_val) == (uint32_t)expr->fe_val2))
			goto gotmatch;
		break;

	case LFUTEX_WAIT_32BIT | LFUTEX_WAIT_UNTIL_BITMASK:
		if (!((val.v32 & (uint32_t)expr->fe_val) != (uint32_t)expr->fe_val2))
			goto gotmatch;
		break;
#endif /* LFUTEX_WAIT_32BIT */

		/* 64-bit expressions. */
#ifdef LFUTEX_WAIT_64BIT
	case LFUTEX_WAIT_64BIT | LFUTEX_WAIT_WHILE:
		if (val.v64 != (uint64_t)expr->fe_val)
			goto gotmatch;
		break;

	case LFUTEX_WAIT_64BIT | LFUTEX_WAIT_UNTIL:
		if (val.v64 == (uint64_t)expr->fe_val)
			goto gotmatch;
		break;

	case LFUTEX_WAIT_64BIT | LFUTEX_WAIT_WHILE_ABOVE:
		if (!(val.v64 > (uint64_t)expr->fe_val))
			goto gotmatch;
		break;

	case LFUTEX_WAIT_64BIT | LFUTEX_WAIT_WHILE_BELOW:
		if (!(val.v64 < (uint64_t)expr->fe_val))
			goto gotmatch;
		break;

	case LFUTEX_WAIT_64BIT | LFUTEX_WAIT_WHILE_BITMASK:
		if (!((val.v64 & (uint64_t)expr->fe_val) == (uint64_t)expr->fe_val2))
			goto gotmatch;
		break;

	case LFUTEX_WAIT_64BIT | LFUTEX_WAIT_UNTIL_BITMASK:
		if (!((val.v64 & (uint64_t)expr->fe_val) != (uint64_t)expr->fe_val2))
			goto gotmatch;
		break;
#endif /* LFUTEX_WAIT_64BIT */

	default: __builtin_unreachable();
	}

	/* Check the next expression. */
	++i;
	goto nextexpr;
gotmatch:
	mpart_lock_release(part);
	mman_lock_endread(unlock.umi_mman);
	return what & POLLPRI;
}


DECL_END

#ifndef __INTELLISENSE__
#define DEFINE_mfutexfd_new
#include "futexfd-new.c.inl"
#ifdef __ARCH_HAVE_COMPAT
#define DEFINE_compat_mfutexfd_new
#include "futexfd-new.c.inl"
#endif /* __ARCH_HAVE_COMPAT */
#endif /* !__INTELLISENSE__ */


#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_FUTEXFD_C */
