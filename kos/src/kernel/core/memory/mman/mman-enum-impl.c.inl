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
#ifdef __INTELLISENSE__
#include "mman-enum.c"
//#define DEFINE_mman_enum
#define DEFINE_mman_enum_ex
#endif /* __INTELLISENSE__ */

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <debugger/rt.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/path.h>
#include <kernel/mman.h>
#include <kernel/mman/enum.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>

#include <hybrid/overflow.h>

#include <kos/types.h>

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#if (defined(DEFINE_mman_enum) + defined(DEFINE_mman_enum_ex)) != 1
#error "Must #define exactly one of these macros"
#endif /* ... */

DECL_BEGIN

#ifdef DEFINE_mman_enum_ex
/* Account for the state of `part' within the given sub-range.
 * The caller is holding a lock to `part'. */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mman_enum_ex_account_for_part)(struct mmapinfo_ex *__restrict info,
                                             struct mpart *__restrict part,
                                             mpart_reladdr_t addr, size_t num_bytes) {
	struct mfile *file = part->mp_file;
	size_t partrel_blocks_min, partrel_blocks_max;

	/* Calculate the range of blocks being accessed by `addr...+=num_bytes' */
	partrel_blocks_min = addr >> file->mf_blockshift;
	partrel_blocks_max = (addr + num_bytes - 1) >> file->mf_blockshift;
	if unlikely(part->mp_state == MPART_ST_SWP || part->mp_state == MPART_ST_SWP_SC) {
		/* Special case: part currently lives in swap memory. */
		size_t i, inswap_blocks;
		if (!mpart_hasblockstate(part)) {
			inswap_blocks = (partrel_blocks_max - partrel_blocks_min) + 1;
		} else {
			inswap_blocks = 0;
			for (i = partrel_blocks_min; i <= partrel_blocks_max; ++i) {
				unsigned int st = mpart_getblockstate(part, i);
				if (st == MPART_BLOCK_ST_CHNG)
					++inswap_blocks;
			}
		}
		inswap_blocks <<= file->mf_blockshift;
		info->mmix_swap += inswap_blocks;
		info->mmix_loaded += inswap_blocks;
		info->mmix_changed += inswap_blocks;
	} else {
		if (part->mp_flags & MPART_F_MLOCK)
			info->mmix_locked += num_bytes;
		if (part->mp_state != MPART_ST_VOID)
			info->mmix_alloc += num_bytes;

		/* Scan the part's state. */
		if (!mpart_hasblockstate(part)) {
			size_t blocks_size;
			blocks_size = (partrel_blocks_max - partrel_blocks_min) + 1;
			blocks_size <<= file->mf_blockshift;
			info->mmix_loaded += blocks_size;
			info->mmix_changed += blocks_size;
		} else {
			size_t i, blocksize = mfile_getblocksize(file);
			for (i = partrel_blocks_min; i <= partrel_blocks_max; ++i) {
				unsigned int st = mpart_getblockstate(part, i);
				if (st == MPART_BLOCK_ST_CHNG) {
					info->mmix_changed += blocksize;
					info->mmix_loaded += blocksize;
				} else if (st == MPART_BLOCK_ST_LOAD) {
					info->mmix_loaded += blocksize;
				}
			}
		}
	}
}
#endif /* DEFINE_mman_enum_ex */

#ifdef DEFINE_mman_enum
/* Enumerate all mappings contained within the given `enum_minaddr...enum_maxaddr'
 * address range within the given VM `self'. This function will automatically  re-
 * assemble  memory mappings that  had previously been  split into multiple nodes,
 * such that adjacent  `struct mnode's that describe  a contiguous memory  mapping
 * do not appear as individual, separate nodes.
 * @param: cb:           A callback  that  should  be  invoked for  every  mapped  memory  region
 *                       contained with the given address range `enum_minaddr' ... `enum_maxaddr'
 *                       The  sum of return  values returned by this  callback will eventually be
 *                       returned by this function, unless `cb()' returns a negative value, which
 *                       will  cause enumeration to  halt immediately, and that  same value to be
 *                       propagated to the caller.
 *                       Note that mappings are enumerated  in strictly ascending order, and  that
 *                       this function guaranties that even in the modifications being made to the
 *                       given `self' while enumeration takes  place, the `mmi_min' of all  future
 *                       mappings will always be `> mmi_max' of every already/currently enumerated
 *                       mapping.
 * @param: arg:          An argument (cookie) to-be passed to `cb()'
 * @param: enum_minaddr: The starting address of mappings to-be enumerated, such that any mapping
 *                       that overlap  with `enum_minaddr ... enum_maxaddr'  will be  enumerated.
 * @param: enum_maxaddr: Same as `enum_minaddr', but specifies the max address of any enumerated
 *                       mapping. */
PUBLIC BLOCKING_IF(BLOCKING(cb)) NONNULL((1, 2)) ssize_t KCALL
mman_enum(struct mman *__restrict self, mman_enum_callback_t cb, void *arg,
          UNCHECKED void *enum_minaddr, UNCHECKED void *enum_maxaddr)
		THROWS(E_WOULDBLOCK)
#else /* DEFINE_mman_enum */
/* Same as `mman_enum()', but provide some more (additional) accounting info about mappings. */
FUNDEF BLOCKING_IF(BLOCKING(cb)) NONNULL((1, 2)) ssize_t KCALL
mman_enum_ex(struct mman *__restrict self, mman_enum_ex_callback_t cb, void *arg,
             UNCHECKED void *enum_minaddr, UNCHECKED void *enum_maxaddr)
		THROWS(E_WOULDBLOCK)
#endif /* !DEFINE_mman_enum */
{
	ssize_t temp, result = 0;
#ifdef DEFINE_mman_enum
	struct mmapinfo mi;
#else /* DEFINE_mman_enum */
	struct mmapinfo_ex mi;
#endif /* !DEFINE_mman_enum */
	while (enum_minaddr <= enum_maxaddr) {
		struct mnode_tree_minmax mima;
		struct mnode *node;
		struct mpart *part;
again_lookup_node:
#ifdef DEFINE_mman_enum_ex
		mi.mmix_locked  = 0;
		mi.mmix_alloc   = 0;
		mi.mmix_loaded  = 0;
		mi.mmix_changed = 0;
		mi.mmix_swap    = 0;
#endif /* DEFINE_mman_enum_ex */
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
		if unlikely(dbg_active) {
			/* Do everything while ignoring all of the locks (or refs).
			 *
			 * The debugger uses  this function for  `lsmm', and  yes:
			 * by not acquiring  locks, there is  a chance that  we'll
			 * crash because mappings may be in an inconsistent state.
			 *
			 * But  if  we did  try to  acquire  locks, then  it also
			 * wouldn't work because task_yield() within the debugger
			 * throws an exception. */
			mnode_tree_minmaxlocate(self->mm_mappings,
			                        enum_minaddr,
			                        enum_maxaddr,
			                        &mima);
			node = mima.mm_min;
			if (!node)
				break;
			mi.mmi_min   = mnode_getminaddr(node);
			mi.mmi_flags = node->mn_flags & MMAPINFO_FLAGS_MASK;
			part         = node->mn_part;
			if (part) {
				mi.mmi_file   = part->mp_file;
				mi.mmi_offset = mnode_getfileaddr(node);
#ifdef DEFINE_mman_enum_ex
				mman_enum_ex_account_for_part(&mi, part, node->mn_partoff,
				                              mnode_getsize(node));
#endif /* DEFINE_mman_enum_ex */
			} else {
				mi.mmi_file   = NULL;
				mi.mmi_offset = 0;
			}
			if (mi.mmi_min < enum_minaddr) {
				if (part != NULL) {
					mi.mmi_offset += (size_t)((byte_t *)enum_minaddr -
					                          (byte_t *)mi.mmi_min);
				}
				mi.mmi_min = enum_minaddr;
			}
			mi.mmi_fspath = node->mn_fspath;
			mi.mmi_fsname = node->mn_fsname;
			for (;;) {
				mi.mmi_max = mnode_getmaxaddr(node);
				if (mi.mmi_max >= enum_maxaddr)
					break;
				if (node == mima.mm_max)
					break; /* Nothing hereafter -> We're done! */
				/* Search for adjacent nodes that may reference the same underlying file. */
				node = mnode_tree_nextnode(node);
				assertf(node != NULL,
				        "But the last node should have been `mima.mm_max', "
				        "and we didn't get to that one, yet...");
				if ((byte_t *)mi.mmi_max + 1 !=  mnode_getminaddr(node))
					break; /* Not a continuous mapping */
				if (mi.mmi_flags != (node->mn_flags & MMAPINFO_FLAGS_MASK))
					break; /* Different flags */
				if (mi.mmi_fsname != node->mn_fsname ||
				    mi.mmi_fspath != node->mn_fspath)
					break; /* Different file name */
				if (part) {
					pos_t expected_offset;
					bool part_ok;
					struct mpart *nextpart;
					nextpart = node->mn_part;
					if (nextpart == NULL)
						break;
					expected_offset = mi.mmi_offset;
					expected_offset += (size_t)((byte_t *)mnode_getminaddr(node) -
					                            (byte_t *)mi.mmi_min);
					/* Check that the part maps the expected location. */
					part_ok = (nextpart->mp_file == mi.mmi_file) &&
					          (mnode_getfileaddr(node) == expected_offset);
					if (!part_ok)
						break;
#ifdef DEFINE_mman_enum_ex
					mman_enum_ex_account_for_part(&mi, nextpart,
					                              node->mn_partoff,
					                              mnode_getsize(node));
#endif /* DEFINE_mman_enum_ex */
				} else {
					if (node->mn_part != NULL)
						break;
				}
				/* The secondary node is considered to be apart of the same mapping! */
			}

			/* Limit the enumerated address range to the requested range */
			if (mi.mmi_max > enum_maxaddr)
				mi.mmi_max = enum_maxaddr;
			mi._mmi_node = mima.mm_min;

			/* Invoke the given callback. */
			temp = (*cb)(arg, &mi);
		} else
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */
		{
			mman_lock_read(self);
			mnode_tree_minmaxlocate(self->mm_mappings,
			                        enum_minaddr,
			                        enum_maxaddr,
			                        &mima);
			node = mima.mm_min;
			if (!node) {
				mman_lock_endread(self);
				break;
			}
			mi.mmi_min   = mnode_getminaddr(node);
			mi.mmi_flags = node->mn_flags & MMAPINFO_FLAGS_MASK;
			part = node->mn_part;
			if (part) {
				if (!mpart_lock_tryacquire(part)) {
waitfor_part:
					/* Wait for the lock of `part' to become available. */
					incref(part);
					mman_lock_endread(self);
					FINALLY_DECREF_UNLIKELY(part);
					mpart_lock_waitfor(part);
					goto again_lookup_node;
				}
				mi.mmi_file   = incref(part->mp_file);
				mi.mmi_offset = mnode_getfileaddr(node);
#ifdef DEFINE_mman_enum_ex
				mman_enum_ex_account_for_part(&mi, part, node->mn_partoff,
				                              mnode_getsize(node));
#endif /* DEFINE_mman_enum_ex */
				mpart_lock_release(part);
			} else {
				mi.mmi_file   = NULL;
				mi.mmi_offset = 0;
			}
			if (mi.mmi_min < enum_minaddr) {
				if (part != NULL) {
					mi.mmi_offset += (size_t)((byte_t *)enum_minaddr -
					                          (byte_t *)mi.mmi_min);
				}
				mi.mmi_min = enum_minaddr;
			}
			mi.mmi_fspath = xincref(node->mn_fspath);
			mi.mmi_fsname = xincref(node->mn_fsname);
			for (;;) {
				mi.mmi_max = mnode_getmaxaddr(node);
				if (mi.mmi_max >= enum_maxaddr)
					break;
				if (node == mima.mm_max)
					break; /* Nothing hereafter -> We're done! */
				/* Search for adjacent nodes that may reference the same underlying file. */
				node = mnode_tree_nextnode(node);
				assertf(node != NULL,
				        "But the last node should have been `mima.mm_max', "
				        "and we didn't get to that one, yet...");
				if ((byte_t *)mi.mmi_max + 1 !=  mnode_getminaddr(node))
					break; /* Not a continuous mapping */
				if (mi.mmi_flags != (node->mn_flags & MMAPINFO_FLAGS_MASK))
					break; /* Different flags */
				if (mi.mmi_fsname != node->mn_fsname ||
				    mi.mmi_fspath != node->mn_fspath)
					break; /* Different file name */
				if (part) {
					pos_t expected_offset;
					bool part_ok;
					struct mpart *nextpart;
					nextpart = node->mn_part;
					if (nextpart == NULL)
						break;
					expected_offset = mi.mmi_offset;
					expected_offset += (size_t)((byte_t *)mnode_getminaddr(node) -
					                            (byte_t *)mi.mmi_min);
					if (!mpart_lock_tryacquire(nextpart)) {
						xdecref_unlikely(mi.mmi_file);
						xdecref_unlikely(mi.mmi_fsname);
						xdecref_unlikely(mi.mmi_fspath);
						DBG_memset(&mi.mmi_file, 0xcc, sizeof(mi.mmi_file));
						DBG_memset(&mi.mmi_fsname, 0xcc, sizeof(mi.mmi_fsname));
						DBG_memset(&mi.mmi_fspath, 0xcc, sizeof(mi.mmi_fspath));
						goto waitfor_part;
					}
					/* Check that the part maps the expected location. */
					part_ok = (nextpart->mp_file == mi.mmi_file) &&
					          (mnode_getfileaddr(node) == expected_offset);
#ifdef DEFINE_mman_enum_ex
					if (part_ok) {
						mman_enum_ex_account_for_part(&mi, nextpart,
						                              node->mn_partoff,
						                              mnode_getsize(node));
					}
#endif /* DEFINE_mman_enum_ex */
					mpart_lock_release(nextpart);
					if (!part_ok)
						break;
				} else {
					if (node->mn_part != NULL)
						break;
				}
				/* The secondary node is considered to be apart of the same mapping! */
			}
			mman_lock_endread(self);

			/* Limit the enumerated address range to the requested range */
			if (mi.mmi_max > enum_maxaddr)
				mi.mmi_max = enum_maxaddr;

			/* Invoke the given callback. */
			FINALLY_XDECREF_UNLIKELY(mi.mmi_file);
			FINALLY_XDECREF_UNLIKELY(mi.mmi_fsname);
			FINALLY_XDECREF_UNLIKELY(mi.mmi_fspath);
			mi._mmi_node = mima.mm_min;
			temp = (*cb)(arg, &mi);
		}
		if unlikely(temp < 0)
			return temp;
		result += temp;
		if (OVERFLOW_UADD((uintptr_t)mi.mmi_max, 1,
		                  (uintptr_t *)&enum_minaddr))
			break;
	}
	return result;
}

DECL_END

#undef DEFINE_mman_enum_ex
#undef DEFINE_mman_enum
