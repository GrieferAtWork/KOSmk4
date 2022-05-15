/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_DIRHANDLEX_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_DIRHANDLEX_H 1

#include <kernel/compiler.h>

#include <kernel/fs/dirhandle.h>
#include <kernel/types.h>
#include <sched/atomic64.h>
#include <sched/sig-completion.h>

#include <hybrid/__atomic.h>

#include <kos/aref.h>

/*
 * Support structures for `F_NOTIFY' (built on-top of dirhandle+notifyfd)
 *
 * TODO:
 * - Missing support for F_SETOWN_EX
 * - Missing support for F_SETSIG with real-time signals
 * - Missing support for SI_SIGIO and siginfo_t::si_fd
 *   TODO: man says that `si_fd' is the fd used when calling F_SETSIG
 *   TODO: man says that a real-time signal is used when F_SETSIG!=0,
 *         and   otherwise   a   queuing   signal   SIGIO   is  used.
 *
 */

#ifdef __CC__
DECL_BEGIN

struct notifyfd;
struct taskpid;

#ifndef __taskpid_arref_defined
#define __taskpid_arref_defined
ARREF(taskpid_arref, taskpid);
#endif /* !__taskpid_arref_defined */

struct dirhandlex_hdr {
	/* This structure appears prepended before `struct dirhandle'
	 * when  the dir object  is of type `HANDLE_TYPE_DIRHANDLEX'! */
	REF struct notifyfd  *dxh_notify; /* [1..1][const] Associated notify controller. */
	struct sig_completion dxh_com;    /* [const] Completion controller listening to `dxh_notify->nf_avail' */
	signo_t               dxh_sigio;  /* [lock(ATOMIC)][sigvalid(.)] Signal send upon notify */
	/* TODO: To support F_SETOWN_EX, we must be able to specify target types:
	 *  - thread         (deliver signal using `_task_raisesignothread()')
	 *  - process        (deliver signal using `_task_raisesignoprocess()')
	 *  - process-group  (deliver signal using `_task_raisesignoprocessgroup()')
	 */
	struct taskpid_arref  dxh_thrio;  /* [1..1] Some thread in the process that should receive `dxh_sigio'. */
	/* This is where the normal `struct dirhandle' exists, as well as where
	 * the object address of the associated `struct dirhandlex' points  to!
	 *
	 * This shared base address was chosen to make it easier to simply re-use
	 * the  same handle  operators and other  things as already  used for the
	 * regular `struct dirhandle'. */
};


/************************************************************************/
/* HANDLE_TYPE_DIRHANDLEX                                               */
/************************************************************************/
#ifdef __cplusplus
struct dirhandlex: dirhandle { /* Underlying directory handle */
};
#else /* __cplusplus */
struct dirhandlex {
	struct dirhandle dx_dir; /* Underlying directory handle */
};
#endif /* !__cplusplus */

/* Destroy the given dirhandlex object. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL dirhandlex_destroy)(struct dirhandlex *__restrict self);
DEFINE_REFCNT_FUNCTIONS(struct dirhandlex, dh_refcnt, dirhandlex_destroy)

/* Return the nhdr of a given `struct dirhandle *self' */
#define dirhandlex_ashdr(self)  (((struct dirhandlex_hdr *)(self)) - 1)
#define dirhandlex_fromhdr(hdr) ((struct dirhandlex *)((hdr) + 1))

/* Add/remove a `struct dirhandle_nhdr' prefix from a given directory handle.
 * For  this purpose, a new object needs  to be constructed, which the caller
 * should then use to replace the old object in the caller's handle table. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct dirhandlex *KCALL
dirhandle_xadd(struct dirhandle *__restrict self);
#if 0
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct dirhandle *KCALL
dirhandle_xdel(struct dirhandlex *__restrict self);
#endif


/* Implementation for `fcntl(F_NOTIFY)'
 * @param: flags: Set of `DN_*' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL dirhandlex_setnotify)(struct dirhandlex *__restrict self,
                                    syscall_ulong_t flags);

#define dirhandlex_hdr_getsigio(self)         __hybrid_atomic_load((self)->dxh_sigio, __ATOMIC_ACQUIRE)         /* F_GETSIG */
#define dirhandlex_hdr_setsigio(self, sigio)  __hybrid_atomic_store((self)->dxh_sigio, sigio, __ATOMIC_RELEASE) /* F_SETSIG */
#define dirhandlex_hdr_gettaskpid(self)       arref_get(&(self)->dxh_thrio)                                     /* F_GETOWN */
#define dirhandlex_hdr_settaskpid(self, tpid) arref_set(&(self)->dxh_thrio, tpid)                               /* F_SETOWN */
#define dirhandlex_getsigio(self)             dirhandlex_hdr_getsigio(dirhandlex_ashdr(self))
#define dirhandlex_setsigio(self, sigio)      dirhandlex_hdr_setsigio(dirhandlex_ashdr(self), sigio)
#define dirhandlex_gettaskpid(self)           dirhandlex_hdr_gettaskpid(dirhandlex_ashdr(self))
#define dirhandlex_settaskpid(self, tpid)     dirhandlex_hdr_settaskpid(dirhandlex_ashdr(self), tpid)

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_DIRHANDLEX_H */
