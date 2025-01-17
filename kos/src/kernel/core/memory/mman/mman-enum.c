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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_ENUM_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_ENUM_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <debugger/rt.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/path.h>
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
			struct mpart *nextpart;
			nextpart = next->mn_part;
			if (nextpart == NULL)
				break;
			expected_offset = offset_at_addr;
			expected_offset -= (size_t)((byte_t *)addr -
			                            (byte_t *)mnode_getminaddr(next));
			if (!mpart_lock_tryacquire(nextpart)) {
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
			part_ok = (nextpart->mp_file == info->mmi_file) &&
			          (mnode_getfileaddr(next) == expected_offset);
			mpart_lock_release(nextpart);
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
			struct mpart *nextpart;
			nextpart = next->mn_part;
			if (nextpart == NULL)
				break;
			expected_offset = offset_at_addr;
			expected_offset += (size_t)((byte_t *)mnode_getminaddr(next) -
			                            (byte_t *)addr);
			if (!mpart_lock_tryacquire(nextpart))
				goto handle_blocking_part;

			/* Check that the part maps the expected location. */
			part_ok = (nextpart->mp_file == info->mmi_file) &&
			          (mnode_getfileaddr(next) == expected_offset);
			mpart_lock_release(nextpart);
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
	info->_mmi_node = lo;
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

DECL_END

#ifndef __INTELLISENSE__
#define DEFINE_mman_enum
#include "mman-enum-impl.c.inl"
#define DEFINE_mman_enum_ex
#include "mman-enum-impl.c.inl"
#endif /* !__INTELLISENSE__ */


#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_ENUM_C */
