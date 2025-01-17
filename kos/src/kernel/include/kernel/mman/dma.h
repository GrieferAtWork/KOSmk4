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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_DMA_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_DMA_H 1

#include <kernel/compiler.h>

#include <kernel/mman/mpart.h>
#include <kernel/mman/mpartmeta.h>
#include <kernel/paging.h>
#include <kernel/refcountable.h>
#include <kernel/types.h>

#ifdef __CC__
DECL_BEGIN

struct mman;
struct iov_buffer;

typedef REF struct mpart *mdma_lock_t;


/* Callback for enumerating physical memory ranges for the purposes of DMA
 * @param: cookie:    The same `cookie' given to `mman_dma'
 * @param: paddr:     The physical memory base address of the range.
 * @param: num_bytes: The number of bytes found within the range.
 * @param: lock:      The lock used to lock the associated DMA range.
 *                    The function is responsible to _always_ release
 *                    this lock  via `mdma_lock_release()',  possibly
 *                    asynchronously at a later point in time. */
typedef BLOCKING NONNULL_T((4)) ssize_t
(KCALL *mdma_range_callback_t)(void *cookie, physaddr_t paddr, size_t num_bytes,
                               /*inherit(always)*/ mdma_lock_t lock);

/* Release the given DMA lock */
#ifdef __INTELLISENSE__
NOBLOCK NONNULL((1)) void
NOTHROW(mdma_lock_release)(/*inherit(always)*/ mdma_lock_t self);
#else /* __INTELLISENSE__ */
#define mdma_lock_release(self) \
	decref_unlikely(mpart_dma_dellock(self))
#endif /* !__INTELLISENSE__ */

/* Same as `mdma_lock_release()', but caller guaranties that this is not the last lock. */
#ifdef __INTELLISENSE__
NOBLOCK NONNULL((1)) void
NOTHROW(mdma_lock_release_nokill)(/*inherit(always)*/ mdma_lock_t self);
#else /* __INTELLISENSE__ */
#define mdma_lock_release_nokill(self)                                      \
	(__hybrid_atomic_dec(&(self)->mp_meta->mpm_dmalocks, __ATOMIC_SEQ_CST), \
	 decref_nokill(self))
#endif /* !__INTELLISENSE__ */

/* Start DMAing on  memory within the  specified address  range.
 * This function is used to lock physical memory for the purpose
 * of use with `mfile_direct_[read|write]()'.
 *
 * @param: prange:    A callback that is invoked for each affected physical memory range
 *                    When this callback returns a negative value, stop enumeration  and
 *                    propagate said return value.
 * @param: cookie:    Cookie-argument passed to `prange' upon execution.
 * @param: addr:      The base address where locking should start.
 * @param: num_bytes: The number of continuous bytes that should be locked.
 * @param: flags:     Set of `0 | MMAN_FAULT_F_WRITE'. When `MMAN_FAULT_F_WRITE' is given, unshare
 *                    copy-on-write  mappings of  associated memory,  allowing the  caller to then
 *                    write  to the acquired memory ranges without accidentally having any changes
 *                    made appear in PRIVATE mappings of the associated memory region.
 * @return: >= :      Sum of positive return values of `*prange'
 * @return: < 0:      Enumeration was stopped because `*prange' return this negative value.
 *
 * Exceptions thrown by this function:
 * WARNING: *prange may have already been invoked when this happens!
 * @throw: E_WOULDBLOCK:        ...
 * @throw: E_BADALLOC:          ...
 * @throw: E_SEGFAULT_UNMAPPED: An address was reached that isn't mapped or is reserved
 * @throw: E_SEGFAULT_UNMAPPED: Hit a VIO mapping (which can't be DMA'd) (context includes `E_SEGFAULT_CONTEXT_VIO')
 * @throw: E_SEGFAULT_READONLY: `MMAN_FAULT_F_WRITE' was given and an address is mapped without PROT_WRITE
 *                              WARNING: *prange may have already been invoked
 * @throw: E_FSERROR_READONLY:  Attempted to fault write-access for a SHARED mapping of a MFILE_F_READONLY file. */
FUNDEF BLOCKING NONNULL((1)) ssize_t KCALL
mman_dma(mdma_range_callback_t prange, void *cookie,
         UNCHECKED void *addr, size_t num_bytes, unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_FSERROR_READONLY, ...);

/* Simple wrapper for `mman_dma()' that just consecutively
 * invokes said function for all of the given iov  ranges. */
FUNDEF BLOCKING NONNULL((1, 3)) ssize_t KCALL
mman_dmav(mdma_range_callback_t prange, void *cookie,
          struct iov_buffer const *__restrict buffer, size_t buf_offset,
          size_t num_bytes, unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_FSERROR_READONLY, ...);





/* Subclass of the generic refcountable object that will release a DMA-lock upon destruction.
 * You can use  this in  conjunction with `struct aio_multihandle::am_obj'  to construct  AIO
 * handles which will  automatically release DMA  locks upon AIO  completion, thus making  it
 * possible to automate "VADDR->PADDR->AIO_THROUGH_PHYS".
 *
 * This functionality is used to implement DMA locking for `mfile_direct_[read|write]' when
 * called on virtual memory buffers. */
struct refcountable_dmalock
#ifdef __cplusplus
    : refcountable                     /* Underlying refcountable controller. */
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct refcountable      rdl_rcb;  /* Underlying refcountable controller. */
#endif /* !__cplusplus */
	mdma_lock_t              rld_lock; /* [1..1][const] DMA-lock that is released when this object is destroyed. */
	REF struct refcountable *rld_misc; /* [0..1][const] Misc inner object to also decref upon destruction. */
};

/* Callback for `struct refcountable_dmalock::rca_destroy' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL refcountable_dmalock_destroy)(struct refcountable *__restrict self);
DEFINE_REFCNT_FUNCTIONS(struct refcountable_dmalock, rca_refcnt, refcountable_dmalock_destroy)

/* A function that may be called as-is from `mdma_range_callback_t' in order
 * to convert  a  DMA-lock  to `lock'  into  a  refcnt-controlled  DMA-lock. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct refcountable_dmalock *FCALL
refcountable_dmalock_new(/*inherit(always)*/ mdma_lock_t lock, struct refcountable *misc)
		THROWS(E_BADALLOC);

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_DMA_H */
