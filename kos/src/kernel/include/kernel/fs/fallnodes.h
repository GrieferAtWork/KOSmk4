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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_FALLNODES_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_FALLNODES_H 1

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_FS
#include <fs/node.h>
#else /* !CONFIG_USE_NEW_FS */
#include <kernel/types.h>

#include <hybrid/__atomic.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sync/atomic-lock.h>

#ifndef REF_IF
#define REF_IF __REF_IF
#endif /* !REF_IF */

#ifdef __CC__
DECL_BEGIN

/* All file-nodes and/or super-blocks API */

struct fnode;
struct fsuper;

struct fallsuper_postlockop;
struct fallsuper_lockop;
struct fallnodes_postlockop;
struct fallnodes_lockop;

/* All of  these  callbacks  behave/operate in  the  expected  manner.
 * For documentation reference, you may look at <kernel/mman/lockop.h> */

typedef NOBLOCK NONNULL((1)) void
/*NOTHROW*/ (FCALL *fallnodes_postlockop_callback_t)(struct fallnodes_postlockop *__restrict self);
typedef NOBLOCK NONNULL((1)) struct fallnodes_postlockop *
/*NOTHROW*/ (FCALL *fallnodes_lockop_callback_t)(struct fallnodes_lockop *__restrict self);
typedef NOBLOCK NONNULL((1)) void
/*NOTHROW*/ (FCALL *fallsuper_postlockop_callback_t)(struct fallsuper_postlockop *__restrict self);
typedef NOBLOCK NONNULL((1)) struct fallsuper_postlockop *
/*NOTHROW*/ (FCALL *fallsuper_lockop_callback_t)(struct fallsuper_lockop *__restrict self);

struct fallnodes_postlockop {
	SLIST_ENTRY(fallnodes_postlockop) fanplo_link; /* [0..1] Next post-lock operation. */
	fallnodes_postlockop_callback_t   fanplo_func; /* [1..1][const] Callback to invoke. */
};

struct fallnodes_lockop {
	SLIST_ENTRY(fallnodes_postlockop) fanplo_link; /* [0..1] Next post-lock operation. */
	fallnodes_postlockop_callback_t   fanplo_func; /* [1..1][const] Callback to invoke. */
};

struct fallsuper_postlockop {
	SLIST_ENTRY(fallsuper_postlockop) fasplo_link; /* [0..1] Next post-lock operation. */
	fallsuper_postlockop_callback_t   fasplo_func; /* [1..1][const] Callback to invoke. */
};

struct fallsuper_lockop {
	SLIST_ENTRY(fallsuper_postlockop) fasplo_link; /* [0..1] Next post-lock operation. */
	fallsuper_postlockop_callback_t   fasplo_func; /* [1..1][const] Callback to invoke. */
};


#ifndef __fallnodes_lockop_slist_defined
#define __fallnodes_lockop_slist_defined
SLIST_HEAD(fallnodes_lockop_slist, fallnodes_lockop);
#endif /* !__fallnodes_lockop_slist_defined */
#ifndef __fallsuper_lockop_slist_defined
#define __fallsuper_lockop_slist_defined
SLIST_HEAD(fallsuper_lockop_slist, fallsuper_lockop);
#endif /* !__fallsuper_lockop_slist_defined */


#ifndef __fnode_list_defined
#define __fnode_list_defined
LIST_HEAD(fnode_list, fnode);
#endif /* !__fnode_list_defined */
#ifndef __fsuper_list_defined
#define __fsuper_list_defined
LIST_HEAD(fsuper_list, fsuper);
#endif /* !__fsuper_list_defined */


/************************************************************************/
/* List of all file-nodes (excluding superblock root nodes)             */
/************************************************************************/

/* [0..n][lock(fallnodes_list)] List of all file nodes */
REF_IF([*].mf_flags & MFILE_FN_GLOBAL_REF)
DATDEF struct fnode_list fallnodes_list;

/* Lock for `fallnodes_list' */
DATDEF struct atomic_lock fallnodes_lock;

/* Lock operations for `fallnodes_list' */
DATDEF struct fallnodes_lockop_slist fallnodes_lockops;

/* Reap pending operations from `fallnodes_lockops' */
FUNDEF NOBLOCK void NOTHROW(KCALL _fallnodes_reap)(void);
#define fallnodes_mustreap() \
	(__hybrid_atomic_load(fallnodes_lockops.slh_first, __ATOMIC_ACQUIRE) != __NULLPTR)
#ifdef __OPTIMIZE_SIZE__
#define fallnodes_reap() _fallnodes_reap()
#else /* __OPTIMIZE_SIZE__ */
#define fallnodes_reap() (void)(!fallnodes_mustreap() || (_fallnodes_reap(), 0))
#endif /* !__OPTIMIZE_SIZE__ */
#define fallnodes_lock_tryacquire() atomic_lock_tryacquire(&fallnodes_lock)
#define fallnodes_lock_acquire()    atomic_lock_acquire(&fallnodes_lock)
#define fallnodes_lock_acquire_nx() atomic_lock_acquire_nx(&fallnodes_lock)
#define fallnodes_lock_release_f()  atomic_lock_release(&fallnodes_lock)
#define fallnodes_lock_release()    (atomic_lock_release(&fallnodes_lock), fallnodes_reap())
#define fallnodes_lock_acquired()   atomic_lock_acquired(&fallnodes_lock)
#define fallnodes_lock_available()  atomic_lock_available(&fallnodes_lock)



/************************************************************************/
/* List of all super blocks                                             */
/************************************************************************/

/* [0..n][lock(fallsuper_list)] List of all file super */
REF_IF([*].mf_flags & MFILE_FN_GLOBAL_REF)
DATDEF struct fsuper_list fallsuper_list;

/* Lock for `fallsuper_list' */
DATDEF struct atomic_lock fallsuper_lock;

/* Lock operations for `fallsuper_list' */
DATDEF struct fallsuper_lockop_slist fallsuper_lockops;

/* Reap pending operations from `fallsuper_lockops' */
FUNDEF NOBLOCK void NOTHROW(KCALL _fallsuper_reap)(void);
#define fallsuper_mustreap() \
	(__hybrid_atomic_load(fallsuper_lockops.slh_first, __ATOMIC_ACQUIRE) != __NULLPTR)
#ifdef __OPTIMIZE_SIZE__
#define fallsuper_reap() _fallsuper_reap()
#else /* __OPTIMIZE_SIZE__ */
#define fallsuper_reap() (void)(!fallsuper_mustreap() || (_fallsuper_reap(), 0))
#endif /* !__OPTIMIZE_SIZE__ */
#define fallsuper_lock_tryacquire() atomic_lock_tryacquire(&fallsuper_lock)
#define fallsuper_lock_acquire()    atomic_lock_acquire(&fallsuper_lock)
#define fallsuper_lock_acquire_nx() atomic_lock_acquire_nx(&fallsuper_lock)
#define fallsuper_lock_release_f()  atomic_lock_release(&fallsuper_lock)
#define fallsuper_lock_release()    (atomic_lock_release(&fallsuper_lock), fallsuper_reap())
#define fallsuper_lock_acquired()   atomic_lock_acquired(&fallsuper_lock)
#define fallsuper_lock_available()  atomic_lock_available(&fallsuper_lock)




DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_FALLNODES_H */
