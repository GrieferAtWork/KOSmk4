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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_C 1
#define __WANT_DNOTIFY_LINK__dnl_fildead
#define __WANT_FS_INIT
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/dirent.h>
#include <kernel/fs/notify-config.h> /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
#include <kernel/fs/notify.h>
#include <kernel/fs/null.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/phys.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <kos/except.h>
#include <kos/lockop.h>
#include <sys/param.h>

#include <assert.h>
#include <inttypes.h>
#include <stdalign.h>
#include <stddef.h>
#include <string.h>


DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/* Allocate physical memory for use with mem-parts created for `self'
 * This function is a more restrictive version of `page_malloc_part(1, max_pages, res_pages)',
 * in that it will also ensure that returned  pages are properly aligned, as well as that  the
 * given `max_pages' is  also properly aligned.  Note however that  so-long as the  size of  a
 * single file-block is <= PAGESIZE,  this function behaves 100%  identical to the above  call
 * to `page_malloc_part()' */
PUBLIC NOBLOCK WUNUSED NONNULL((1, 3)) physpage_t
NOTHROW(FCALL mfile_alloc_physmem)(struct mfile *__restrict self,
                                   physpagecnt_t max_pages,
                                   physpagecnt_t *__restrict res_pages) {
	physpage_t result, real_result;
	size_t page_alignment;
	assert(self->mf_iobashift <= self->mf_blockshift);
	assert(max_pages != 0);
	DBG_memset(res_pages, 0xcc, sizeof(*res_pages));
#ifndef NDEBUG
	if (self->mf_blockshift > PAGESHIFT) {
		size_t size_alignment;
		size_alignment = (size_t)1 << (self->mf_blockshift - PAGESHIFT);
		assertf(IS_ALIGNED(max_pages, size_alignment),
		        "Badly aligned max_pages %#" PRIxSIZ " for use with "
		        "file %p that requires %#" PRIxSIZ "-alignment",
		        max_pages, self, size_alignment);
	}
#endif /* !NDEBUG */

	/* Check   for  the  simple  case  where  natural  page
	 * alignment is enough to satisfy file-block alignment. */
	if likely(self->mf_iobashift <= PAGESHIFT)
		return page_malloc_part(1, max_pages, res_pages);
	page_alignment = (size_t)1 << (self->mf_iobashift - PAGESHIFT);
	result = page_malloc_part(page_alignment + page_alignment - 1,
	                          max_pages + page_alignment - 1,
	                          res_pages);
	if unlikely(result == PHYSPAGE_INVALID) {
		result = page_malloc(page_alignment);
		if (result != PHYSPAGE_INVALID) {
			*res_pages = page_alignment;
			if (!IS_ALIGNED(result, page_alignment)) {
				page_ccfree(result, max_pages);
				result = PHYSPAGE_INVALID;
				DBG_memset(res_pages, 0xcc, sizeof(*res_pages));
			}
		}
		return result;
	}

	/* Trim leading/trailing pages to satisfy the required alignment. */
	real_result = CEIL_ALIGN(result, page_alignment);
	if (real_result > result) {
		/* Trim leading */
		physpagecnt_t count;
		count = (physpagecnt_t)(real_result - result);
		page_ccfree(result, count);
		*res_pages -= count;
	}
	if (!IS_ALIGNED(*res_pages, page_alignment)) {
		/* Trim trailing */
		physpagecnt_t count;
		count = *res_pages & (page_alignment - 1);
		page_ccfree(result + *res_pages - count, count);
		*res_pages -= count;
	}

	assert(*res_pages >= page_alignment);
	assert(*res_pages <= max_pages);
	return real_result;
}


PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_changed)(struct mfile *__restrict self, uintptr_t what) {
	uintptr_t old_flags, new_flags;
	old_flags = ATOMIC_FETCHOR(self->mf_flags, what);
	new_flags = old_flags | what;
	if (old_flags != new_flags && self->mf_ops->mo_changed)
		(*self->mf_ops->mo_changed)(self, old_flags, new_flags);
}


#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
#ifndef __dnotify_link_slist_defined
#define __dnotify_link_slist_defined
SLIST_HEAD(dnotify_link_slist, dnotify_link);
#endif /* !__dnotify_link_slist_defined */
#endif /* CONFIG_HAVE_KERNEL_FS_NOTIFY */


/* Destroy a given mem-file */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_destroy)(struct mfile *__restrict self) {
	assertf(self->mf_parts == NULL ||
	        self->mf_parts == MFILE_PARTS_ANONYMOUS,
	        "Any remaining part should have kept us alive!\n"
	        "self->mf_parts = %p\n",
	        self->mf_parts);
	assertf(self->mf_changed.slh_first == NULL ||
	        self->mf_changed.slh_first == MFILE_PARTS_ANONYMOUS,
	        "Any remaining part should have kept us alive!\n"
	        "self->mf_changed.slh_first = %p\n",
	        self->mf_changed.slh_first);

	/* The  file may still  have a notify controller
	 * if its containing directory is being watched. */
#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
	if (self->mf_notify != NULL) {
		struct inotify_controller *notify;
		struct dnotify_link_slist deadlinks;
		COMPILER_READ_BARRIER();
		SLIST_INIT(&deadlinks);
		notify_lock_acquire();
		if ((notify = self->mf_notify) != NULL) {
			assertf(LIST_EMPTY(&notify->inc_listeners),
			        "Per-file listeners should have kept us "
			        "alive via `notify_listener::nl_file'");
			assertf(!LIST_EMPTY(&notify->inc_dirs),
			        "If this was also empty, then the notify "
			        "controller should have already been freed!");
			assertf(notify->inc_file == self,
			        "Notify contrller of different file? (%p != %p)",
			        notify->inc_file, self);

			/* Remove the file from watched directories that contain it. */
			do {
				struct dnotify_link *link;
				link = LIST_FIRST(&notify->inc_dirs);
				assertf(dnotify_link_getfil(link) == notify,
				        "%p != %p",
				        dnotify_link_getfil(link), notify);
				LIST_REMOVE(link, dnl_fillink);
				dnotify_link_tree_removenode(&link->dnl_dir->dnc_files, link);
				DBG_memset(&link->dnl_dir, 0xcc, sizeof(link->dnl_dir));
				SLIST_INSERT(&deadlinks, link, _dnl_fildead);
			} while (!LIST_EMPTY(&notify->inc_dirs));
		}
		notify_lock_release();
		if (notify) {
			struct mfile_stream_ops const *stream;
			stream = self->mf_ops->mo_stream;
			/* Detach the notify file handle (if that operator is defined) */
			if (stream && stream->mso_notify_detach)
				(*stream->mso_notify_detach)(self, notify->inc_fhnd);
			inotify_controller_free(notify);
		}
		while (!SLIST_EMPTY(&deadlinks)) {
			struct dnotify_link *link;
			link = SLIST_FIRST(&deadlinks);
			SLIST_REMOVE_HEAD(&deadlinks, _dnl_fildead);
			dnotify_link_destroy(link);
		}
	}
#endif /* CONFIG_HAVE_KERNEL_FS_NOTIFY */

	sig_broadcast_for_fini(&self->mf_initdone);
	if (self->mf_ops->mo_destroy) {
		(*self->mf_ops->mo_destroy)(self);
	} else {
		kfree(self);
	}
}



PRIVATE NONNULL((1)) void
NOTHROW(FCALL restore_changed_parts)(struct mfile *__restrict self,
                                     REF struct mpart *chain) {
	struct mpart *other_changes, **p_last, *more_changes;
	other_changes = ATOMIC_CMPXCH_VAL(self->mf_changed.slh_first,
	                                  NULL, chain);
	if (other_changes == NULL)
		return; /* Success */
	if (chain == NULL)
		return; /* No remaining changes. */
	if (other_changes == MFILE_PARTS_ANONYMOUS) {
		/* Changes may no longer be traced! */
clear_chain:
		while (chain) {
			struct mpart *next;
			next = SLIST_NEXT(chain, mp_changed);
			DBG_memset(&chain->mp_changed, 0xcc, sizeof(chain->mp_changed));
			decref(chain);
			chain = next;
		}
		return;
	}
	/* Find the last of the new changes. */
	p_last = SLIST_PNEXT(chain, mp_changed);
	while (*p_last)
		p_last = SLIST_PNEXT(*p_last, mp_changed);
	for (;;) {
		*p_last = other_changes;
		COMPILER_WRITE_BARRIER();
		more_changes = ATOMIC_CMPXCH_VAL(self->mf_changed.slh_first,
		                                 other_changes,
		                                 chain);
		if (more_changes == other_changes)
			break;
		if unlikely(other_changes == MFILE_PARTS_ANONYMOUS)
			goto clear_chain;
		other_changes = more_changes;
	}
}


/* Sync unwritten changes made to parts within the given address range.
 * @return: * : The total # of bytes that have been synced. */
PUBLIC BLOCKING NONNULL((1)) pos_t FCALL
mfile_sync(struct mfile *__restrict self)
		THROWS(E_WOULDBLOCK, ...) {
	pos_t result = 0;
	REF struct mpart *changes;
	/* Clear the changed flag.
	 * This  has to be happen _before_ we read out the changed-part
	 * list, such that changed parts added after we've consumed all
	 * currently changed parts  will cause the  CHANGED flag to  be
	 * set once again, without it ever being cleared when there are
	 * no changed parts at all. */
	for (;;) {
		uintptr_t flags;
		flags = ATOMIC_READ(self->mf_flags);
		if (flags & MFILE_F_DELETED)
			break;
		if (!(flags & MFILE_F_CHANGED))
			break;
		if (ATOMIC_CMPXCH_WEAK(self->mf_flags, flags, flags & ~MFILE_F_CHANGED))
			break;
	}
	do {
		changes = ATOMIC_READ(self->mf_changed.slh_first);
		if (/*changes == NULL || */ /* The NULL-case is implicitly handled below */
		    changes == MFILE_PARTS_ANONYMOUS)
			return 0;
	} while (!ATOMIC_CMPXCH_WEAK(self->mf_changed.slh_first,
	                             changes, NULL));
	TRY {
		/* Sync all parts. */
		while (changes) {
			REF struct mpart *next;
			next = SLIST_NEXT(changes, mp_changed);
			result += mpart_sync(changes);
			decref(changes);
			changes = next;
		}
	} EXCEPT {
		restore_changed_parts(self, changes);
		RETHROW();
	}
	return result;
}


PRIVATE struct mfile_ops const mfile_ndef_ops = { NULL };

PUBLIC struct mfile mfile_ndef = {
	MFILE_INIT_mf_refcnt(1), /* +1: mfile_ndef */
	MFILE_INIT_mf_ops(&mfile_ndef_ops),
	MFILE_INIT_mf_lock,
	MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),
	MFILE_INIT_mf_initdone,
	MFILE_INIT_mf_lockops,
	MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
	MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),
#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
	MFILE_INIT_mf_notify,
#endif /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
	MFILE_INIT_mf_flags(MFILE_F_ATTRCHANGED | MFILE_F_CHANGED |
	                    MFILE_F_NOATIME | MFILE_F_NOMTIME |
	                    MFILE_F_FIXEDFILESIZE),
	MFILE_INIT_mf_trunclock,
	MFILE_INIT_mf_filesize((uint64_t)-1),
	MFILE_INIT_mf_atime(0, 0),
	MFILE_INIT_mf_mtime(0, 0),
	MFILE_INIT_mf_ctime(0, 0),
	MFILE_INIT_mf_btime(0, 0),
};


#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
#define MFILE_INIT_mf_notify_ MFILE_INIT_mf_notify,
#else /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
#define MFILE_INIT_mf_notify_ /* nothing */
#endif /* !CONFIG_HAVE_KERNEL_FS_NOTIFY */


/* Fallback  files for anonymous memory. These behave the same as `mfile_zero',
 * but one exists for every possible `mf_blockshift' (where the index into this
 * array is equal to that file's `mf_blockshift' value)
 * As such, these files are used by `mfile_delete()' as replacement mappings
 * of the original file. */
PUBLIC struct mfile mfile_anon[BITSOF(void *)] = {
#define INIT_ANON_FILE(i)                                           \
	{                                                               \
		MFILE_INIT_mf_refcnt(1), /* +1: mfile_ndef */               \
		MFILE_INIT_mf_ops(&mfile_anon_ops[i]),                      \
		MFILE_INIT_mf_lock,                                         \
		MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),                 \
		MFILE_INIT_mf_initdone,                                     \
		MFILE_INIT_mf_lockops,                                      \
		MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),               \
		MFILE_INIT_mf_blockshift(i, i),                             \
		MFILE_INIT_mf_notify_                                       \
		MFILE_INIT_mf_flags(MFILE_F_ATTRCHANGED | MFILE_F_CHANGED | \
		                    MFILE_F_NOATIME | MFILE_F_NOMTIME |     \
		                    MFILE_F_FIXEDFILESIZE),                 \
		MFILE_INIT_mf_trunclock,                                    \
		MFILE_INIT_mf_filesize((uint64_t)-1),                       \
		MFILE_INIT_mf_atime(0, 0),                                  \
		MFILE_INIT_mf_mtime(0, 0),                                  \
		MFILE_INIT_mf_ctime(0, 0),                                  \
		MFILE_INIT_mf_btime(0, 0),                                  \
	}
	INIT_ANON_FILE(0),  INIT_ANON_FILE(1),  INIT_ANON_FILE(2),  INIT_ANON_FILE(3),
	INIT_ANON_FILE(4),  INIT_ANON_FILE(5),  INIT_ANON_FILE(6),  INIT_ANON_FILE(7),
#if (__SIZEOF_POINTER__ * NBBY) > 8
	INIT_ANON_FILE(8),  INIT_ANON_FILE(9),  INIT_ANON_FILE(10), INIT_ANON_FILE(11),
	INIT_ANON_FILE(12), INIT_ANON_FILE(13), INIT_ANON_FILE(14), INIT_ANON_FILE(15),
#if (__SIZEOF_POINTER__ * NBBY) > 16
	INIT_ANON_FILE(16), INIT_ANON_FILE(17), INIT_ANON_FILE(18), INIT_ANON_FILE(19),
	INIT_ANON_FILE(20), INIT_ANON_FILE(21), INIT_ANON_FILE(22), INIT_ANON_FILE(23),
	INIT_ANON_FILE(24), INIT_ANON_FILE(25), INIT_ANON_FILE(26), INIT_ANON_FILE(27),
	INIT_ANON_FILE(28), INIT_ANON_FILE(29), INIT_ANON_FILE(30), INIT_ANON_FILE(31),
#if (__SIZEOF_POINTER__ * NBBY) > 32
	INIT_ANON_FILE(32), INIT_ANON_FILE(33), INIT_ANON_FILE(34), INIT_ANON_FILE(35),
	INIT_ANON_FILE(36), INIT_ANON_FILE(37), INIT_ANON_FILE(38), INIT_ANON_FILE(39),
	INIT_ANON_FILE(40), INIT_ANON_FILE(41), INIT_ANON_FILE(42), INIT_ANON_FILE(43),
	INIT_ANON_FILE(44), INIT_ANON_FILE(45), INIT_ANON_FILE(46), INIT_ANON_FILE(47),
	INIT_ANON_FILE(48), INIT_ANON_FILE(49), INIT_ANON_FILE(50), INIT_ANON_FILE(51),
	INIT_ANON_FILE(52), INIT_ANON_FILE(53), INIT_ANON_FILE(54), INIT_ANON_FILE(55),
	INIT_ANON_FILE(56), INIT_ANON_FILE(57), INIT_ANON_FILE(58), INIT_ANON_FILE(59),
	INIT_ANON_FILE(60), INIT_ANON_FILE(61), INIT_ANON_FILE(62), INIT_ANON_FILE(63),
#if (__SIZEOF_POINTER__ * NBBY) > 64
#error Unsupported sizeof(void *)
#endif /* (__SIZEOF_POINTER__ * NBBY) > 64 */
#endif /* (__SIZEOF_POINTER__ * NBBY) > 32 */
#endif /* (__SIZEOF_POINTER__ * NBBY) > 16 */
#endif /* (__SIZEOF_POINTER__ * NBBY) > 8 */
#undef INIT_ANON_FILE
};


#define ANON_LOADBLOCKS_CALLBACK(i)           \
	((i) == PAGESHIFT ? &mfile_zero_loadpages \
	                  : &mfile_zero_loadblocks)

INTERN NONNULL((1)) void /* INTERN because also used in `filesys/null.c' (for `dev_zero') */
NOTHROW(KCALL mfile_zero_loadpages)(struct mfile *__restrict UNUSED(self),
                                    pos_t UNUSED(addr),
                                    physaddr_t buf, size_t num_bytes,
                                    struct aio_multihandle *__restrict UNUSED(aio)) {
	size_t start, end, num_pages;
	physpage_t page;
	/* Skip pages that were already zero-initialized before-hand! */
	assert(IS_ALIGNED(buf, PAGESIZE));
	assert(IS_ALIGNED(num_bytes, PAGESIZE));
	page      = physaddr2page(buf);
	num_pages = num_bytes >> PAGESHIFT;
	for (start = 0; start < num_pages;) {
		if (page_iszero(page + start)) {
			++start;
			continue;
		}
		end = start + 1;
		while (end < num_pages && !page_iszero(page + end))
			++end;
		/* Manually zero-init all pages from start...end */
		memsetphyspages(physpage2addr(page + start), 0,
		                (end - start) * PAGESIZE);
		start = end + 1;
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL mfile_zero_loadblocks)(struct mfile *__restrict UNUSED(self),
                                     pos_t UNUSED(addr),
                                     physaddr_t buf, size_t num_bytes,
                                     struct aio_multihandle *__restrict UNUSED(aio)) {
	bzerophyscc(buf, num_bytes);
}



PUBLIC_CONST struct mfile_ops const mfile_anon_ops[BITSOF(void *)] = {
#define INIT_ANON_OPS(i)                             \
	{                                                \
		.mo_loadblocks = ANON_LOADBLOCKS_CALLBACK(i) \
	}
	INIT_ANON_OPS(0),  INIT_ANON_OPS(1),  INIT_ANON_OPS(2),  INIT_ANON_OPS(3),
	INIT_ANON_OPS(4),  INIT_ANON_OPS(5),  INIT_ANON_OPS(6),  INIT_ANON_OPS(7),
#if (__SIZEOF_POINTER__ * NBBY) > 8
	INIT_ANON_OPS(8),  INIT_ANON_OPS(9),  INIT_ANON_OPS(10), INIT_ANON_OPS(11),
	INIT_ANON_OPS(12), INIT_ANON_OPS(13), INIT_ANON_OPS(14), INIT_ANON_OPS(15),
#if (__SIZEOF_POINTER__ * NBBY) > 16
	INIT_ANON_OPS(16), INIT_ANON_OPS(17), INIT_ANON_OPS(18), INIT_ANON_OPS(19),
	INIT_ANON_OPS(20), INIT_ANON_OPS(21), INIT_ANON_OPS(22), INIT_ANON_OPS(23),
	INIT_ANON_OPS(24), INIT_ANON_OPS(25), INIT_ANON_OPS(26), INIT_ANON_OPS(27),
	INIT_ANON_OPS(28), INIT_ANON_OPS(29), INIT_ANON_OPS(30), INIT_ANON_OPS(31),
#if (__SIZEOF_POINTER__ * NBBY) > 32
	INIT_ANON_OPS(32), INIT_ANON_OPS(33), INIT_ANON_OPS(34), INIT_ANON_OPS(35),
	INIT_ANON_OPS(36), INIT_ANON_OPS(37), INIT_ANON_OPS(38), INIT_ANON_OPS(39),
	INIT_ANON_OPS(40), INIT_ANON_OPS(41), INIT_ANON_OPS(42), INIT_ANON_OPS(43),
	INIT_ANON_OPS(44), INIT_ANON_OPS(45), INIT_ANON_OPS(46), INIT_ANON_OPS(47),
	INIT_ANON_OPS(48), INIT_ANON_OPS(49), INIT_ANON_OPS(50), INIT_ANON_OPS(51),
	INIT_ANON_OPS(52), INIT_ANON_OPS(53), INIT_ANON_OPS(54), INIT_ANON_OPS(55),
	INIT_ANON_OPS(56), INIT_ANON_OPS(57), INIT_ANON_OPS(58), INIT_ANON_OPS(59),
	INIT_ANON_OPS(60), INIT_ANON_OPS(61), INIT_ANON_OPS(62), INIT_ANON_OPS(63),
#if (__SIZEOF_POINTER__ * NBBY) > 64
#error Unsupported sizeof(void *)
#endif /* (__SIZEOF_POINTER__ * NBBY) > 64 */
#endif /* (__SIZEOF_POINTER__ * NBBY) > 32 */
#endif /* (__SIZEOF_POINTER__ * NBBY) > 16 */
#endif /* (__SIZEOF_POINTER__ * NBBY) > 8 */
#undef INIT_ANON_OPS
#undef ANON_LOADBLOCKS_CALLBACK
};

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_C */
