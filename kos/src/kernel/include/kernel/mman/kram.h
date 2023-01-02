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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_KRAM_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_KRAM_H 1

#include <kernel/compiler.h>

#include <kernel/paging.h>
#include <kernel/types.h>

#include <hybrid/host.h> /* __ARCH_STACK_GROWS_DOWNWARDS */
#include <hybrid/sequence/list.h>

#include <asm/os/mman.h>       /* __MAP_FAILED */
#include <kos/kernel/paging.h> /* KERNEL_MHINT_HEAP */
#include <kos/lockop.h>

#ifdef __CC__
DECL_BEGIN

#ifndef __gfp_t_defined
#define __gfp_t_defined
typedef unsigned int gfp_t;
#endif /* !__gfp_t_defined */


/************************************************************************/
/* Additional GFP_* flags for `mman_map_kram()'                         */
/************************************************************************/

#define GFP_MAP_FIXED        0x0010 /* Map new kernel ram at exactly the given address.
                                     * If the given address is already in-use, fail  by
                                     * unconditionally returning `MAP_FAILED' */
#define GFP_MAP_32BIT        0x0040 /* The  backing  _physical_  memory  will  use  32-bit  addresses.
                                     * This differs from the normal meaning of the `MAP_32BIT' flag!!! */
#define GFP_MAP_PREPARED     0x0080 /* Set the `MNODE_F_MPREPARED'  node flag,  and ensure  that
                                     * the backing page directory address range is kept prepared
                                     * for the duration of the node's lifetime. */
#define GFP_MAP_BELOW        0x0100 /* [valid_if(!GFP_MAP_FIXED)] s.a. `MAP_GROWSDOWN' */
#define GFP_MAP_ABOVE        0x0200 /* [valid_if(!GFP_MAP_FIXED)] s.a. `MAP_GROWSUP' */
#define GFP_MAP_NOSPLIT  0x00040000 /* Set the `MNODE_F_NOSPLIT' flag for new nodes */
#define GFP_MAP_NOMERGE  0x00080000 /* Set the `MNODE_F_NOMERGE' flag for new nodes, and don't try to extend an existing node. */
#define GFP_MAP_NOASLR   0x40000000 /* [valid_if(!GFP_MAP_FIXED)] s.a. `MAP_NOASLR' */

/* Set of all of the GFP_* flags which control mapping behavior */
#define GFP_MAP_FLAGS                                   \
	(GFP_MAP_FIXED | GFP_MAP_32BIT | GFP_MAP_PREPARED | \
	 GFP_MAP_BELOW | GFP_MAP_ABOVE | GFP_MAP_NOASLR |   \
	 GFP_MAP_NOSPLIT | GFP_MAP_NOMERGE)



/* @param: flags: Set of:
 *   - GFP_LOCKED:       Normal behavior
 *   - GFP_PREFLT:       Prefault everything
 *   - GFP_CALLOC:       Allocate from `mfile_zero' instead of `mfile_ndef'
 *   - GFP_ATOMIC:       Don't block when waiting to acquire any sort of lock.
 *   - GFP_NOMMAP:       Unconditionally throw `E_WOULDBLOCK_PREEMPTED'
 *   - GFP_MCHEAP:       Allocate the mnode and mpart using `mcoreheap_alloc_locked_nx()'.
 *                       This also  causes  the  `MNODE_F_COREPART'  /  `MPART_F_COREPART'
 *                       flags  to  be set  for each  resp. This  flag is  used internally
 *                       to resolve  the dependency  loop  between this  function  needing
 *                       to call kmalloc()  and kmalloc() needing  to call this  function.
 *   - GFP_MAP_FIXED:    Map memory at the given address `hint' exactly.
 *                       If memory has already been mapped at that address, then simply
 *                       return `MAP_INUSE' unconditionally.
 *   - GFP_MAP_32BIT:    Allocate   32-bit  physical  memory  addresses.  This  flag
 *                       should be combined with `GFP_LOCKED' to prevent the backing
 *                       physical memory  from being  altered (and  thus having  its
 *                       physical location altered).
 *   - GFP_MAP_PREPARED: Ensure that all mapped pages are prepared, and left as such
 *   - GFP_MAP_BELOW:    s.a. `MAP_GROWSDOWN'
 *   - GFP_MAP_ABOVE:    s.a. `MAP_GROWSUP'
 *   - GFP_MAP_NOASLR:   s.a. `MAP_NOASLR'
 *   - GFP_MAP_NOSPLIT:  Set the `MNODE_F_NOSPLIT' flag for new nodes
 *   - GFP_MAP_NOMERGE:  Set the `MNODE_F_NOMERGE' flag for new nodes, and don't try
 *                       to extend an existing node.
 *   - GFP_NOCLRC:       Don't call `syscache_clear()' to try to free up memory
 *   - GFP_NOSWAP:       Don't move memory to swap to free up memory
 *   - Other flags are silently ignored, but will be forwarded  onto
 *     other calls to kmalloc() that may need to be made internally.
 * Returned memory will be initialized as:
 *   - GFP_CALLOC: All zero-initialized
 *   - else:       #ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP: DEBUGHEAP_FRESH_MEMORY
 *                 #ifndef       CONFIG_HAVE_KERNEL_DEBUG_HEAP:       Undefined
 *
 * @param: hint:          Hint  for  where  the  mapping  should  go.  This  argument is
 *                        passed  onto  `mman_findunmapped()',  alongside  certain  bits
 *                        from `flags': `GFP_MAP_BELOW | GFP_MAP_ABOVE | GFP_MAP_NOASLR'
 *                        You may  pass  `NULL'  to use  either  `KERNEL_MHINT_HEAP'  or
 *                        `KERNEL_MHINT_LHEAP'   (based   on   `GFP_LOCKED')    instead.
 *                        When `GFP_MAP_FIXED' is set, this is the (possibly  unaligned)
 *                        address of where the mapping  should go. If not  page-aligned,
 *                        then the sub-page-misalignment will  be carried over into  the
 *                        return value. If another mapping  already exists at the  given
 *                        location, then unconditionally return `MAP_INUSE'
 * @param: num_bytes:     The  # of bytes to allocate. The actual amount is ceil-
 *                        aligned to multiples of  pages (after also including  a
 *                        possibly sub-page-misalignment from GFP_MAP_FIXED+hint)
 * @param: flags:         Allocation option flags (see above)
 * @param: min_alignment: The minimum alignment  for the returned  pointer. Ignored  when
 *                        the `GFP_MAP_FIXED' flag was given. Otherwise, a value  greater
 *                        than `PAGESIZE' can be used to ensure that the returned pointer
 *                        is aligned by multiple pages. s.a. `mman_findunmapped()'
 * @param: min_alignment_offset: Offset from `return' at which `min_alignment' shall be applied. */
FUNDEF NOBLOCK_IF(flags & GFP_ATOMIC) void *FCALL
mman_map_kram(void *hint, size_t num_bytes,
              gfp_t flags, size_t min_alignment DFL(PAGESIZE),
              ptrdiff_t min_alignment_offset DFL(0))
		THROWS(E_BADALLOC, E_WOULDBLOCK);


/* Non-throwing version of `mman_map_kram()'. Returns `MAP_FAILED' on error. */
FUNDEF NOBLOCK_IF(flags & GFP_ATOMIC) void *
NOTHROW(FCALL mman_map_kram_nx)(void *hint, size_t num_bytes, gfp_t flags,
                                size_t min_alignment DFL(PAGESIZE),
                                ptrdiff_t min_alignment_offset DFL(0));

/* Return value of `mman_map_kram()' and `mman_map_kram_nx()' if GFP_MAP_FIXED
 * is used with  an address that  is already being  mapped by something  else. */
#define MAP_INUSE ((void *)((byte_t *)__MAP_FAILED - 1))

/* Error return value for `mman_map_kram_nx()' */
#ifndef MAP_FAILED
#define MAP_FAILED __MAP_FAILED
#endif /* !MAP_FAILED */


/*
 * Unmapping kernel ram without blocking is quite the complicated task,
 * but  it is not impossible. We must differentiate between 2 different
 * kind of mappings which the caller wants us to delete:
 *  - Writable mappings    (w/o file write-back) (`mukj_done' should be [0..1])
 *  - Read-only mappings                         (`mukj_done' should be [1..1])
 *
 * In the case of writable mappings, the solution is fairly simple, since
 * all that really needs to  be done is (ab-)use  a small portion of  the
 * region  being free'd as a `struct lockop' that is enqueued for running
 * when a lock to the kernel mman becomes available.
 *
 * Once  that lock is  available, iteratively go through  all nodes of the
 * region (splitting the region at  the front if necessary, and  asserting
 * that  any partial  node doesn't  have the  `MNODE_F_NOSPLIT' flag set).
 * For every node  encountered in this  manner, try to  acquire a lock  to
 * the associated mem-part.  If this lock  cannot be acquired,  re-purpose
 * the  region being freed  as a `Toblockop(mpart)'  that is executed once
 * that  lock becomes  available. If  this was  done, the Toblockop(mpart)
 * will try to  acquire a lock  to the kernel  mman. On success,  continue
 * as  if the  original mman->part  locking order  attempt was successful.
 * Else, re-purpose the `Toblockop(mpart)' as yet another `struct lockop',
 * and  enqueue that  one back onto  the kernel mman  lock-job queue, thus
 * letting  the request bounce back and forth without ever blocking, until
 * both locks can be acquired at the same time.
 *
 * Once  both locks are held, do the  actual unmap. For this purpose, when
 * needing  to split the node, special handling  is also done to deal with
 * `MNODE_F_MHINT' nodes to  prevent possible race  conditions with  other
 * CPUs/threads accessing memory below or  above the region that is  being
 * unmapped. Namely, forcibly pre-initializing all pages affected by this,
 * and waiting for `mman_kernel_hintinit_inuse' to become zero.
 *
 * If the unmap itself (or the  attempt to partially split a  leading/trailing
 * node/part) fails (due to lack of memory during a split or pagedir_prepare),
 * then the unmap  operation is enqueued  as a `struct lockop'  in such a  way
 * that it will _not_ be (re-)attempted immediately once the caller (which  is
 * usually `_mman_lockops_reap()')  releases their  lock to  the kernel  mman.
 * The idea here is to hope that more memory will be available once the kernel
 * mman is unlocked the next time around.
 *
 * If the remainder of the requested unmap-area is now gone, then  we're
 * done. Otherwise, if the current locking order is mman->part (that is:
 * the current request  originates from  a `Toblockop(mpart)'),  release
 * the part lock. Then, continue searching  for the next node to  unmap.
 *
 * When unmapping a read-only mapping, things are a bit more complicated,
 * since it's not possible to (ab-)use the region being free'd as a lock-
 * job  descriptor  (either  a  `struct lockop'  or  `Toblockop(mpart)').
 * In this case, unmapping is only possible if the caller sacrifices  yet
 * another  dynamically allocated (and most importantly: writable) region
 * of memory: a `struct mman_unmap_kram_job'.
 *
 * In this case, instead of always re-using the actual region that is being
 * unmapped  as temporary storage for storing lock jobs, the caller provide
 * a single, common  storage that  is continuously re-purposed  for use  as
 * all of the different lock-jobs which may be needed until the region  has
 * been fully unmapped. Once this has been achieved, the unmap kram job  is
 * enqueued to have its `mukj_done' callback be run once the caller  (which
 * is usually `_mman_lockops_reap()') has released their lock on the kernel
 * mman. This callback should then do the necessary work to either free, or
 * re-purpose  the `struct mman_unmap_kram_job' that it is contained inside
 * of.
 *
 * For convenience, the  internal implementation uses  `struct mman_unmap_kram_job'
 * in  all cases, but  will check if  the `struct mman_unmap_kram_job' is contained
 * inside of the address  range that it is  trying to unmap. If  this is the  case,
 * then `mukj_done' will never be  executed (is considered [valid_if(false)]),  and
 * the `struct mman_unmap_kram_job'  itself will  move up  in memory  as nodes  are
 * successfully deleted, such that `job->mukj_minaddr == (void *)job' will continue
 * to  be the case, where `job->mukj_minaddr' is  the starting address of the range
 * that is still left to-be free'd
 */
struct mman_unmap_kram_job;
SLIST_HEAD(mman_unmap_kram_job_slist, mman_unmap_kram_job);

/* Completion callback for an mman-unmap-kram job. */
typedef NOBLOCK NONNULL_T((1)) void
NOTHROW_T(FCALL *mman_unmap_kram_job_done_t)(struct mman_unmap_kram_job *__restrict self);

struct mman_unmap_kram_job {
	/* [0..1] Callback executed once the job is finished (See the description above).
	 * NOTE: This  callback is guarantied  to only be invoked  _after_ any lock which
	 *       may have been held to the kernel mman, or a backing mem-part has already
	 *       been released, so you're free to trylock() anything you want (so long as
	 *       you make sure that the call is non-blocking). */
	mman_unmap_kram_job_done_t mukj_done;
	byte_t                    *mukj_minaddr; /* Lowest address being unmapped.
	                                          * When equal to `(byte_t *)self', then the
	                                          * unmap job is  considered to be  in-line. */
	byte_t                    *mukj_maxaddr; /* Greatest address being unmapped. */
	gfp_t                      mukj_flags;   /* Set of `0 | GFP_CALLOC' */
	union {
		Toblockop(mman)                  mukj_lop_mm;      /* MMan lockop */
		Toblockop(mpart)                 mukj_lop_mp;      /* MPart lockop */
		Tobpostlockop(mman)              mukj_post_lop_mm; /* MMan post-lockop */
		Tobpostlockop(mpart)             mukj_post_lop_mp; /* MPart post-lockop */
		SLIST_ENTRY(mman_unmap_kram_job) mukj_link;        /* List link (used internally) */
	};
};


/* Without blocking, unmap a given region of kernel RAM.
 * NOTE: The  caller must ensure that the given the address range can
 *       be  written to without any chance of that write blocking, or
 *       resulting in an exception. (i.e. don't use this one to unmap
 *       file mappings or the like...)
 *       If your intend is to unmap mappings that don't fulfill this
 *       requirement, the you should read the description of `struct
 *       mman_unmap_kram_job' and use `mman_unmap_kram_locked_ex()'
 * @param: flags:   Set of `0 | GFP_CALLOC'. When `GFP_CALLOC' is given, allows
 *                  the memory  management system  to assume  that the  backing
 *                  physical  memory  is zero-initialized.  If you're  not sure
 *                  if this is  the case,  better pass  `0'. If  you lie  here,
 *                  calloc() might arbitrarily break... */
FUNDEF NOBLOCK void
NOTHROW(FCALL mman_unmap_kram)(PAGEDIR_PAGEALIGNED void *addr,
                               size_t num_bytes, gfp_t flags DFL(0));

/* Same as `mman_unmap_kram()', but may be used to improve efficiency
 * when the caller is already holding a lock to `mman_kernel.mm_lock' */
FUNDEF NOBLOCK void
NOTHROW(FCALL mman_unmap_kram_locked)(PAGEDIR_PAGEALIGNED void *addr,
                                      size_t num_bytes, gfp_t flags DFL(0));

/* Try to unmap kernel memory while the caller is holding a lock to the kernel mman.
 * NOTE: This function can be used to delete any kind of kernel-space memory  mapping,
 *       but special care must be taken when it comes to read-only, or shared copy-on-
 *       write memory mappings (see the documentation of `struct mman_unmap_kram_job')
 * @param: locked_part: If non-NULL, a part which may be assumed as locked by the caller.
 * @return: MMAN_UNMAP_KRAM_LOCKED_EX_DONE:  Success (you must invoke the done-callback)
 * @return: MMAN_UNMAP_KRAM_LOCKED_EX_ASYNC: Success (memory will  be free'd  asynchronously)
 *                                           In this case, so-long as the job isn't allocated
 *                                           in-line  with the memory being free'd, the given
 *                                           done-callback is responsible to free `job'
 * @return: * : Insufficient memory (re-queue the returned job for later execution) */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct mman_unmap_kram_job *
NOTHROW(FCALL mman_unmap_kram_locked_ex)(struct mman_unmap_kram_job *__restrict job,
                                         struct mpart *locked_part DFL(__NULLPTR));
#define MMAN_UNMAP_KRAM_LOCKED_EX_DONE  ((struct mman_unmap_kram_job *)-1) /* The job was finished (caller must run `mukj_done' after releasing locks) */
#define MMAN_UNMAP_KRAM_LOCKED_EX_ASYNC ((struct mman_unmap_kram_job *)-2) /* The job will be completed asynchronously*/

/* Do all of the necessary locking and queuing to eventually bring `job' to completion. */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) void
NOTHROW(FCALL mman_unmap_kram_ex)(/*inherit(always)*/ struct mman_unmap_kram_job *__restrict job);

/* Helper  function that can  be used to unmap  anything by re-using  `freeme', which must be
 * a kmalloc-pointer with `kmalloc_usable_size(freeme) >= sizeof(struct mman_unmap_kram_job)'
 * in order to represent intermediate storage for.
 * NOTE: The  given  `addr...+=num_bytes' address  range  is automatically
 *       expanded to encompass all whole pages touched by the given range. */
FUNDEF NOBLOCK NONNULL((3)) void
NOTHROW(FCALL mman_unmap_kram_and_kfree)(void const *addr, size_t num_bytes,
                                         void *__restrict freeme, gfp_t flags DFL(0));

/* Helper macros to  alloc/free a cookie  that can later  be
 * used in order  to service  `mman_unmap_kram_and_kfree()'.
 * Note however  that you  are in  no way  obligated to  use
 * these functions  specifically. -  You  can use  any  kind
 * of other dynamically  allocated data  structure, so  long
 * as that structure can hold a `struct mman_unmap_kram_job' */
#define mman_unmap_kram_cookie_alloc()    kmalloc(sizeof(struct mman_unmap_kram_job), GFP_LOCKED | GFP_PREFLT)
#define mman_unmap_kram_cookie_free(self) kfree(self)

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_KRAM_H */
