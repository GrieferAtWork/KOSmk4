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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_LOCKOP_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_LOCKOP_H 1

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_VM
#include <kernel/vm.h>
#else /* !CONFIG_USE_NEW_VM */
#include <kernel/paging.h>
#include <kernel/types.h>

#include <hybrid/sequence/list.h>

#ifdef __CC__
DECL_BEGIN

struct mman;
struct mlockop;
struct mpostlockop;

typedef NOBLOCK NONNULL((1)) void
/*NOTHROW*/ (FCALL *mpostlockop_callback_t)(struct mpostlockop *__restrict self);

struct mpostlockop {
	SLIST_ENTRY(mpostlockop) mplo_link; /* [lock(ATOMIC)] Next post-lock operation. */
	mpostlockop_callback_t   mplo_func; /* [1..1][const] Callback to invoke. */
};


/* Callback prototype for mman pending locked operations.
 * @return: NULL: Completed.
 * @return: * :   A descriptor for an operation to perform
 *                after the mman-lock  has been  released. */
typedef NOBLOCK NONNULL((1)) struct mpostlockop *
/*NOTHROW*/ (FCALL *mlockop_callback_t)(struct mlockop *__restrict self);

/* Memory-manager locked operation.
 * This struct describes a pending  operation that should be  executed
 * while holding a lock to the associated memory manager the next time
 * that someone releases its `mm_lock' */
struct mlockop {
	SLIST_ENTRY(mlockop) mlo_link; /* [lock(ATOMIC)] Next lock operation. */
	mlockop_callback_t   mlo_func; /* [1..1][const] Operation to perform. */
};

#ifndef __mlockop_slist_defined
#define __mlockop_slist_defined 1
SLIST_HEAD(mlockop_slist, mlockop);
#endif /* !__mlockop_slist_defined */

#ifndef __mpostlockop_slist_defined
#define __mpostlockop_slist_defined 1
SLIST_HEAD(mpostlockop_slist, mpostlockop);
#endif /* !__mpostlockop_slist_defined */

/* Aliasing symbol: `== FORMMAN(&mman_kernel, thismman_lockops)' */
#ifndef __mman_kernel_lockops_defined
#define __mman_kernel_lockops_defined 1
DATDEF struct mlockop_slist mman_kernel_lockops;
#endif /* !__mman_kernel_lockops_defined */

DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_VM */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_LOCKOP_H */
