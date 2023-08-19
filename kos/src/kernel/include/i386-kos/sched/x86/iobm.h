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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_X86_IOBM_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_X86_IOBM_H 1

#include <kernel/compiler.h>

#include <kernel/malloc-defs.h>
#include <kernel/types.h>
#include <sched/pertask.h>

#include <stdbool.h>

#ifdef __CC__
DECL_BEGIN

struct ioperm_bitmap {
	WEAK refcnt_t ib_refcnt; /* Reference counter (when > 1, the bitmap becomes read-only/copy-on-write) */
	WEAK refcnt_t ib_share;  /* Reference counter for how many threads share this I/O permissions bitmap. */
	union {
		uintptr_t _ib_pages_ptr[sizeof(physaddr_t) / sizeof(uintptr_t)];
		physaddr_t ib_pages;  /* [owned(page_free(physaddr2page(.), 2))][const]
		                       * First physical page containing io permission bits. */
	};
};

/* An empty I/O permissions map (that also mustn't ever be modified) */
DATDEF struct ioperm_bitmap ioperm_bitmap_empty;

/* [0..1][lock(WRITE_ONCE)]
 * The I/O permissions bitmap of the calling thread.
 * Lazily allocated during `ioperm()' and `#PF' (s.a. documentation in <sched/tss.h>) */
DATDEF ATTR_PERTASK REF struct ioperm_bitmap *this_x86_ioperm_bitmap;
#define THIS_X86_IOPERM_BITMAP    PERTASK_GET(this_x86_ioperm_bitmap)

/* [0..1][lock(THIS_CPU && !PREEMPTION_ENABLED())]
 * The I/O  permissions  bitmap  currently active  within  the  calling  CPU.
 * Set to `NULL' during preemption; Filled in during the first #PF that ended
 * up being caused by  the CPU trying to  access the I/O permissions  bitmap. */
DATDEF ATTR_PERCPU struct ioperm_bitmap *thiscpu_x86_ioperm_bitmap;


/* Destroy the given I/O permissions bitmap. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL ioperm_bitmap_destroy)(struct ioperm_bitmap *__restrict self);
DEFINE_REFCNT_FUNCTIONS(struct ioperm_bitmap, ib_refcnt, ioperm_bitmap_destroy)

/* Allocate a new io permissions bitmap with all permission bits set to disallow access. */
FUNDEF ATTR_MALLOC ATTR_RETNONNULL WUNUSED REF struct ioperm_bitmap *KCALL
ioperm_bitmap_alloc(void) THROWS(E_BADALLOC);
FUNDEF ATTR_BLOCKLIKE_GFP(flags) ATTR_MALLOC ATTR_RETNONNULL WUNUSED
REF struct ioperm_bitmap *KCALL ioperm_bitmap_allocf(gfp_t flags) THROWS(E_BADALLOC);
FUNDEF ATTR_BLOCKLIKE_GFP(flags) ATTR_MALLOC WUNUSED
REF struct ioperm_bitmap *NOTHROW(KCALL ioperm_bitmap_allocf_nx)(gfp_t flags);

/* Create a copy of the given I/O permissions bitmap. */
FUNDEF ATTR_MALLOC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct ioperm_bitmap *KCALL
ioperm_bitmap_copy(struct ioperm_bitmap const *__restrict self) THROWS(E_BADALLOC);
FUNDEF ATTR_BLOCKLIKE_GFP(flags) ATTR_MALLOC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct ioperm_bitmap *KCALL
ioperm_bitmap_copyf(struct ioperm_bitmap const *__restrict self, gfp_t flags) THROWS(E_BADALLOC);
FUNDEF ATTR_BLOCKLIKE_GFP(flags) ATTR_MALLOC WUNUSED NONNULL((1)) REF struct ioperm_bitmap *
NOTHROW(KCALL ioperm_bitmap_copyf_nx)(struct ioperm_bitmap const *__restrict self, gfp_t flags);

/* Turn permission bits for a given range on/off. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL ioperm_bitmap_setrange)(struct ioperm_bitmap *__restrict self,
                                      u16 minport, u16 maxport, bool turn_on);

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_X86_IOBM_H */
