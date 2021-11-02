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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_ENUM_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_ENUM_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <debugger/rt.h>
#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/mman.h>
#include <kernel/mman/enum.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <sched/task.h>

#include <hybrid/overflow.h>

#include <kos/except.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

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
		THROWS(E_WOULDBLOCK) {
	ssize_t temp, result = 0;
	struct mmapinfo mi;
#ifndef CONFIG_USE_NEW_FS
	size_t num_nodes = 0;
#endif /* !CONFIG_USE_NEW_FS */
	while (enum_minaddr <= enum_maxaddr) {
		struct mnode_tree_minmax mima;
		struct mnode *node;
		struct mpart *part;
again_lookup_node:
#ifndef CONFIG_USE_NEW_FS
		mi.mmi_index = num_nodes++;
#endif /* !CONFIG_USE_NEW_FS */
#ifdef CONFIG_HAVE_DEBUGGER
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
					if (node->mn_part == NULL)
						break;
					expected_offset = mi.mmi_offset;
					expected_offset += (size_t)((byte_t *)mnode_getminaddr(node) -
					                            (byte_t *)mi.mmi_min);
					/* Check that the part maps the expected location. */
					part_ok = (part->mp_file == mi.mmi_file) &&
					          (mnode_getfileaddr(node) == expected_offset);
					if (!part_ok)
						break;
				} else {
					if (node->mn_part != NULL)
						break;
				}
				/* The secondary node is considered to be apart of the same mapping! */
#ifndef CONFIG_USE_NEW_FS
				++num_nodes;
#endif /* !CONFIG_USE_NEW_FS */
			}

			/* Limit the enumerated address range to the requested range */
			if (mi.mmi_max > enum_maxaddr)
				mi.mmi_max = enum_maxaddr;
#ifdef CONFIG_USE_NEW_FS
			mi._mmi_node = mima.mm_min;
#endif /* CONFIG_USE_NEW_FS */

			/* Invoke the given callback. */
			temp = (*cb)(arg, &mi);
		} else
#endif /* CONFIG_HAVE_DEBUGGER */
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
			part         = node->mn_part;
			if (part) {
				if (!mpart_lock_tryacquire(part)) {
waitfor_part:
					/* Wait for the lock of `part' to become available. */
					incref(part);
					mman_lock_endread(self);
					FINALLY_DECREF_UNLIKELY(part);
					mpart_lock_waitfor(part);
#ifndef CONFIG_USE_NEW_FS
					num_nodes = mi.mmi_index;
#endif /* !CONFIG_USE_NEW_FS */
					goto again_lookup_node;
				}
				mi.mmi_file   = incref(part->mp_file);
				mi.mmi_offset = mnode_getfileaddr(node);
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
					if (node->mn_part == NULL)
						break;
					expected_offset = mi.mmi_offset;
					expected_offset += (size_t)((byte_t *)mnode_getminaddr(node) -
					                            (byte_t *)mi.mmi_min);
					if (!mpart_lock_tryacquire(part)) {
						xdecref_unlikely(mi.mmi_file);
						xdecref_unlikely(mi.mmi_fsname);
						xdecref_unlikely(mi.mmi_fspath);
						DBG_memset(&mi.mmi_file, 0xcc, sizeof(mi.mmi_file));
						DBG_memset(&mi.mmi_fsname, 0xcc, sizeof(mi.mmi_fsname));
						DBG_memset(&mi.mmi_fspath, 0xcc, sizeof(mi.mmi_fspath));
						goto waitfor_part;
					}
					/* Check that the part maps the expected location. */
					part_ok = (part->mp_file == mi.mmi_file) &&
					          (mnode_getfileaddr(node) == expected_offset);
					mpart_lock_release(part);
					if (!part_ok)
						break;
				} else {
					if (node->mn_part != NULL)
						break;
				}
				/* The secondary node is considered to be apart of the same mapping! */
#ifndef CONFIG_USE_NEW_FS
				++num_nodes;
#endif /* !CONFIG_USE_NEW_FS */
			}
			mman_lock_endread(self);

			/* Limit the enumerated address range to the requested range */
			if (mi.mmi_max > enum_maxaddr)
				mi.mmi_max = enum_maxaddr;

			/* Invoke the given callback. */
			FINALLY_XDECREF_UNLIKELY(mi.mmi_file);
			FINALLY_XDECREF_UNLIKELY(mi.mmi_fsname);
			FINALLY_XDECREF_UNLIKELY(mi.mmi_fspath);
#ifdef CONFIG_USE_NEW_FS
			mi._mmi_node = mima.mm_min;
#endif /* CONFIG_USE_NEW_FS */
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

#ifdef CONFIG_USE_NEW_FS
PRIVATE WUNUSED NONNULL((1, 2, 3)) bool
NOTHROW(KCALL mman_mapinfo_and_unlock)(struct mman *__restrict self,
                                       struct mmapinfo *__restrict info,
                                       struct mnode *__restrict lo) {
	struct mpart *part;
	struct mnode *hi;
	pos_t offset_at_addr;
	UNCHECKED void *addr;

	/* Fill in the initial set of information. */
	part = lo->mn_part;
	if (part) {
		addr           = mnode_getminaddr(lo);
		offset_at_addr = mnode_getfileaddr(lo);
		if (!mpart_lock_tryacquire(part)) {
waitfor_part:
			incref(part);
			mman_lock_endread(self);
			FINALLY_DECREF_UNLIKELY(part);
			mpart_lock_waitfor(part);
			return false;
		}
		info->mmi_file = incref(lo->mn_part->mp_file);
		mpart_lock_release(part);
	} else {
		addr           = (UNCHECKED void *)-1;
		offset_at_addr = 0;
		info->mmi_file = NULL;
	}
	info->mmi_flags  = lo->mn_flags & MMAPINFO_FLAGS_MASK;
	info->mmi_fspath = xincref(lo->mn_fspath);
	info->mmi_fsname = xincref(lo->mn_fsname);

	hi = lo;

	/* Check if the mapping area extends downwards */
	for (;;) {
		struct mnode *next;
		next = mnode_tree_prevnode(lo);
		if (!next)
			break;
		if (mnode_getendaddr(next) != mnode_getaddr(lo))
			break; /* Not a continuous mapping */
		if (info->mmi_flags != (next->mn_flags & MMAPINFO_FLAGS_MASK))
			break; /* Different flags */
		if (info->mmi_fsname != next->mn_fsname ||
		    info->mmi_fspath != next->mn_fspath)
			break; /* Different file name */
		if (part) {
			pos_t expected_offset;
			bool part_ok;
			if (next->mn_part == NULL)
				break;
			expected_offset = offset_at_addr;
			expected_offset -= (size_t)((byte_t *)addr -
			                            (byte_t *)mnode_getminaddr(next));
			if (!mpart_lock_tryacquire(part)) {
handle_blocking_part:
				xdecref_unlikely(info->mmi_file);
				xdecref_unlikely(info->mmi_fsname);
				xdecref_unlikely(info->mmi_fspath);
				DBG_memset(&info->mmi_file, 0xcc, sizeof(info->mmi_file));
				DBG_memset(&info->mmi_fsname, 0xcc, sizeof(info->mmi_fsname));
				DBG_memset(&info->mmi_fspath, 0xcc, sizeof(info->mmi_fspath));
				goto waitfor_part;
			}

			/* Check that the part maps the expected location. */
			part_ok = (part->mp_file == info->mmi_file) &&
			          (mnode_getfileaddr(next) == expected_offset);
			mpart_lock_release(part);
			if (!part_ok)
				break;
		} else {
			if (next->mn_part != NULL)
				break;
		}
		lo = next;
	}

	/* Check if the mapping area extends upwards */
	for (;;) {
		struct mnode *next;
		next = mnode_tree_nextnode(hi);
		if (!next)
			break;
		if (mnode_getendaddr(hi) != mnode_getaddr(next))
			break; /* Not a continuous mapping */
		if (info->mmi_flags != (next->mn_flags & MMAPINFO_FLAGS_MASK))
			break; /* Different flags */
		if (info->mmi_fsname != next->mn_fsname ||
		    info->mmi_fspath != next->mn_fspath)
			break; /* Different file name */
		if (part) {
			pos_t expected_offset;
			bool part_ok;
			if (next->mn_part == NULL)
				break;
			expected_offset = offset_at_addr;
			expected_offset += (size_t)((byte_t *)mnode_getminaddr(next) -
			                            (byte_t *)addr);
			if (!mpart_lock_tryacquire(part))
				goto handle_blocking_part;

			/* Check that the part maps the expected location. */
			part_ok = (part->mp_file == info->mmi_file) &&
			          (mnode_getfileaddr(next) == expected_offset);
			mpart_lock_release(part);
			if (!part_ok)
				break;
		} else {
			if (next->mn_part != NULL)
				break;
		}
		hi = next;
	}

	/* Fill in remaining info. */
	info->mmi_min = mnode_getminaddr(lo);
	info->mmi_max = mnode_getmaxaddr(hi);
	mman_lock_endread(self);
#ifdef CONFIG_USE_NEW_FS
	info->_mmi_node = lo;
#endif /* CONFIG_USE_NEW_FS */
	info->mmi_offset = offset_at_addr;
	info->mmi_offset -= (size_t)((byte_t *)addr - (byte_t *)mnode_getminaddr(lo));
	return true;
}


/* Lookup information about the mapping at `addr' and write that information to `*info'
 * Upon success, the caller must `mmapinfo_fini(info);'
 * @return: true:  Success: mapping information was stored in `*info'
 * @return: false: No mapping exists at `addr' */
PUBLIC WUNUSED NONNULL((1, 2)) bool KCALL
mman_mapinfo(struct mman *__restrict self,
             struct mmapinfo *__restrict info,
             UNCHECKED void *addr)
		THROWS(E_WOULDBLOCK) {
	struct mnode *node;
	do {
		mman_lock_read(self);
		node = mman_mappings_locate(self, addr);
		if unlikely(!node) {
			/* No mapping at this address. */
			mman_lock_endread(self);
			return false;
		}
	} while (!mman_mapinfo_and_unlock(self, info, node));
	return true;
}

/* Return map information for the first node with a base-address `>= addr'
 * Upon success, the caller must `mmapinfo_fini(info);'
 * @return: true:  Success: mapping information was stored in `*info'
 * @return: false: No mapping exists at `addr' */
PUBLIC WUNUSED NONNULL((1, 2)) bool KCALL
mman_mapinfo_above(struct mman *__restrict self,
                   struct mmapinfo *__restrict info,
                   UNCHECKED void *addr)
		THROWS(E_WOULDBLOCK) {
	struct mnode_tree_minmax mima;
	do {
		mman_lock_read(self);
		mman_mappings_minmaxlocate(self, addr, (void *)-1, &mima);
		if unlikely(!mima.mm_min) {
			/* No mapping at this address. */
			mman_lock_endread(self);
			return false;
		}
	} while (!mman_mapinfo_and_unlock(self, info, mima.mm_min));
	return true;
}
#endif /* CONFIG_USE_NEW_FS */


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_ENUM_C */
