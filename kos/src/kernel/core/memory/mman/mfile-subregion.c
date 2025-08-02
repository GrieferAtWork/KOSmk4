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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_SUBREGION_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_SUBREGION_C 1
#define __WANT_MPART__mp_nodlsts
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/devfs.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/node.h>
#include <kernel/fs/null.h>
#include <kernel/fs/path.h>
#include <kernel/handle.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/flags.h>
#include <kernel/mman/mfile-subregion.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/paging.h>
#include <kernel/user.h>
#include <sched/atomic64.h>

#include <hybrid/align.h>
#include <hybrid/overflow.h>
#include <hybrid/sched/atomic-lock.h>
#include <hybrid/sequence/list.h>

#include <kos/except.h>
#include <kos/except/reason/illop.h>
#include <kos/except/reason/inval.h>
#include <kos/io.h>
#include <kos/kernel/handle.h>
#include <kos/lockop.h>
#include <kos/types.h>
#include <sys/types.h>

#include <assert.h>
#include <atomic.h>
#include <format-printer.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset(p, c, n) memset(p, c, n)
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(p, c, n) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

struct subregion_mfile;
LIST_HEAD(subregion_mfile_list, subregion_mfile);
struct subregion_mfile: mfile {
	union {
		struct {
			PAGEDIR_PAGEALIGNED pos_t srf_minaddr;   /* [const] Lowest address in `srf_base' that may be mapped */
			pos_t                     srf_maxaddr;   /* [const] Greatest address in `srf_base' that may be mapped (+1 and would be "PAGEDIR_PAGEALIGNED") */
			REF struct fdirent       *srf_nodename;  /* [1..1][const] Identifier for `struct mnode' */
		};
		Toblockop(subregion_mfile)     _srf_dellop;     /* Used internally during destruction */
		Tobpostlockop(subregion_mfile) _srf_delpostlop; /* Used internally during destruction */
	};
	struct atomic_lock                srf_lock;      /* Lock for stuff below */
	Toblockop_slist(subregion_mfile)  srf_lops;      /* Lock operators for `srf_lock' */
	REF struct mfile                 *srf_base;      /* [0..1][lock(srf_lock && CLEAR_ONCE)] Original base-file (never another sub-region) */
	REF struct subregion_mfile       *srf_parent;    /* [0..1][lock(srf_lock && CLEAR_ONCE)] Parent sub-region, or "NULL" if deleted or first-level sub-region */
	struct subregion_mfile_list       srf_children;  /* [0..n][lock(srf_lock)] List of sub-regions created directly from "self" */
	LIST_ENTRY(subregion_mfile)       srf_chain;     /* [0..1][lock(srf_parent->srf_lock && CLEAR_ONCE)] Entry in `srf_parent->srf_children' */
};

#define _subregion_lock_reap(self)      _oblockop_reap_atomic_lockT(self, srf_lops, srf_lock)
#define subregion_lock_reap(self)       oblockop_reap_atomic_lockT(self, srf_lops, srf_lock)
#define subregion_lock_mustreap(self)   oblockop_mustreap(&(self)->srf_lops)
#define subregion_lock_tryacquire(self) atomic_lock_tryacquire(&(self)->srf_lock)
#define subregion_lock_acquire(self)    atomic_lock_acquire(&(self)->srf_lock)
#define subregion_lock_acquire_nx(self) atomic_lock_acquire_nx(&(self)->srf_lock)
#define _subregion_lock_release(self)   atomic_lock_release(&(self)->srf_lock)
#define subregion_lock_release(self)    (atomic_lock_release(&(self)->srf_lock), subregion_lock_reap(self))
#define subregion_lock_acquired(self)   atomic_lock_acquired(&(self)->srf_lock)
#define subregion_lock_available(self)  atomic_lock_available(&(self)->srf_lock)
#define subregion_lock_waitfor(self)    atomic_lock_waitfor(&(self)->srf_lock)
#define subregion_lock_waitfor_nx(self) atomic_lock_waitfor_nx(&(self)->srf_lock)

#define mfile_assubregion(self) ((struct subregion_mfile *)(self))

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL subregion_unlink_from_parent_postlop)(Tobpostlockop(subregion_mfile) *__restrict lop,
                                                    struct subregion_mfile *__restrict UNUSED(parent)) {
	struct subregion_mfile *me = container_of(lop, struct subregion_mfile, _srf_delpostlop);
	kfree(me);
}

PRIVATE NOBLOCK NONNULL((1)) Tobpostlockop(subregion_mfile) *
NOTHROW(FCALL subregion_unlink_from_parent_lop)(Toblockop(subregion_mfile) *__restrict lop,
                                                struct subregion_mfile *__restrict UNUSED(parent)) {
	struct subregion_mfile *me = container_of(lop, struct subregion_mfile, _srf_dellop);
	if (LIST_ISBOUND(me, srf_chain))
		LIST_REMOVE(me, srf_chain);
	me->_srf_delpostlop.oplo_func = &subregion_unlink_from_parent_postlop;
	return &me->_srf_delpostlop;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL subregion_destroy)(struct mfile *__restrict self) {
	struct subregion_mfile *me = mfile_assubregion(self);
	struct subregion_mfile *parent = me->srf_parent;
#if !defined(NDEBUG) && !defined(NDEBUG_REFCNT)
	assert(wasdestroyed(me));
#endif /* !NDEBUG && !NDEBUG_REFCNT */
	assertf(LIST_EMPTY(&me->srf_children), "Childrent should have kept us alive");
	decref(me->srf_nodename);
	xdecref(me->srf_base);
	if (parent) {
		if (subregion_lock_tryacquire(parent)) {
			if (LIST_ISBOUND(me, srf_chain))
				LIST_REMOVE(me, srf_chain);
			subregion_lock_release(parent);
			decref(parent);
		} else {
			me->_srf_dellop.olo_func = &subregion_unlink_from_parent_lop;
			oblockop_enqueue(&parent->srf_lops, &me->_srf_dellop);
			_subregion_lock_reap(parent);
			decref_unlikely(parent);
			return;
		}
	}
	kfree(me);
}


PRIVATE BLOCKING WUNUSED NONNULL((1, 2, 3)) REF struct mfile *KCALL
subregion_clamp_and_getbase(struct subregion_mfile *__restrict self,
                            size_t *__restrict p_num_bytes,
                            pos_t *__restrict p_addr) THROWS(...) {
	REF struct mfile *result;
	pos_t end_addr;
	if (OVERFLOW_UADD(*p_addr, self->srf_minaddr, p_addr)) {
/*return_dev_void_zero:*/
		*p_num_bytes = 0;
return_dev_void:
		return incref(&dev_void);
	}
	if (OVERFLOW_UADD(*p_addr, *p_num_bytes, &end_addr)) {
		end_addr     = (pos_t)-1;
		*p_num_bytes = (size_t)(end_addr - *p_addr);
	}
	if unlikely(!*p_num_bytes)
		goto return_dev_void;
	subregion_lock_acquire(self);
	result = self->srf_base;
	if unlikely(!result) {
		subregion_lock_release(self);
		goto return_dev_void;
	}
	if ((end_addr - 1) > self->srf_maxaddr)
		*p_num_bytes = (size_t)((self->srf_maxaddr + 1) - *p_addr);
	incref(result);
	subregion_lock_release(self);
	return result;
}

PRIVATE BLOCKING WUNUSED NONNULL((1)) size_t KCALL
subregion_pread(struct mfile *__restrict self, NCX void *dst,
                size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...) {
	struct subregion_mfile *me = mfile_assubregion(self);
	REF struct mfile *base = subregion_clamp_and_getbase(me, &num_bytes, &addr);
	FINALLY_DECREF_UNLIKELY(base);
	return mfile_upread(base, dst, num_bytes, addr, mode);
}

PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL
subregion_preadv(struct mfile *__restrict self, struct iov_buffer *__restrict dst,
                 size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...) {
	struct subregion_mfile *me = mfile_assubregion(self);
	REF struct mfile *base = subregion_clamp_and_getbase(me, &num_bytes, &addr);
	FINALLY_DECREF_UNLIKELY(base);
	return mfile_upreadv(base, dst, num_bytes, addr, mode);
}

PRIVATE BLOCKING WUNUSED NONNULL((1)) size_t KCALL
subregion_pwrite(struct mfile *__restrict self, NCX void const *src,
                 size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...) {
	struct subregion_mfile *me = mfile_assubregion(self);
	REF struct mfile *base = subregion_clamp_and_getbase(me, &num_bytes, &addr);
	FINALLY_DECREF_UNLIKELY(base);
	return mfile_upwrite(base, src, num_bytes, addr, mode);
}

PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL
subregion_pwritev(struct mfile *__restrict self, struct iov_buffer *__restrict src,
                  size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...) {
	struct subregion_mfile *me = mfile_assubregion(self);
	REF struct mfile *base = subregion_clamp_and_getbase(me, &num_bytes, &addr);
	FINALLY_DECREF_UNLIKELY(base);
	return mfile_upwritev(base, src, num_bytes, addr, mode);
}

PRIVATE BLOCKING NONNULL((1, 2)) void KCALL
subregion_mmap(struct mfile *__restrict self,
               struct handle_mmap_info *__restrict info) THROWS(...) {
	struct subregion_mfile *me = mfile_assubregion(self);
	xdecref(info->hmi_fspath);
	xdecref(info->hmi_fsname);
	info->hmi_fspath = NULL;
	info->hmi_fsname = incref(me->srf_nodename);
	subregion_lock_acquire(me);
	info->hmi_minaddr = me->srf_minaddr;
	info->hmi_maxaddr = me->srf_maxaddr;
	info->hmi_file    = me->srf_base;
	if (info->hmi_file == NULL) /* This happens when the subregion was deleted */
		info->hmi_file = &dev_void;
	incref(info->hmi_file);
	subregion_lock_release(me);
}

PRIVATE BLOCKING WUNUSED_T NONNULL_T((1)) REF void *KCALL
subregion_tryas(struct mfile *__restrict self,
                uintptr_half_t wanted_type) THROWS(...) {
	struct subregion_mfile *me = mfile_assubregion(self);
	switch (wanted_type) {
	case HANDLE_TYPE_DIRENT:
		return incref(me->srf_nodename);
	default: break;
	}
	return NULL;
}

PRIVATE BLOCKING NONNULL_T((1, 2)) ssize_t KCALL
subregion_printlink(struct mfile *__restrict self,
                    pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...) {
	ssize_t temp, result;
	struct subregion_mfile *me = mfile_assubregion(self);
	REF struct mfile *base;
	subregion_lock_acquire(me);
	base = me->srf_base;
	if (base == NULL)
		base = &dev_void;
	incref(base);
	subregion_lock_release(me);
	{
		FINALLY_DECREF_UNLIKELY(base);
		result = (*printer)(arg, "[", 1);
		if unlikely(result < 0)
			goto done;
		temp = mfile_uprintlink(base, printer, arg);
		if unlikely(temp < 0)
			goto err_temp;
		result += temp;
	}
	temp = format_printf(printer, arg,
	                     ":%" PRIxN(__SIZEOF_POS_T__) "-%" PRIxN(__SIZEOF_POS_T__) "]",
	                     me->srf_minaddr, me->srf_maxaddr);
	if unlikely(temp < 0)
		goto err_temp;
	result += temp;
done:
	return result;
err_temp:
	return temp;
}

PRIVATE BLOCKING NONNULL_T((1)) void KCALL
subregion_sync(struct mfile *__restrict self)
		THROWS(E_WOULDBLOCK, E_IOERROR, ...) {
	struct subregion_mfile *me = mfile_assubregion(self);
	REF struct mfile *base;
	subregion_lock_acquire(me);
	base = xincref(me->srf_base);
	subregion_lock_release(me);
	if (base) {
		FINALLY_DECREF_UNLIKELY(base);
		mfile_usync(base);
	}
}

PRIVATE ATTR_BLOCKLIKE_CC(info) NONNULL((1)) void
NOTHROW(KCALL subregion_cc)(struct mfile *__restrict self,
                            struct ccinfo *__restrict info) {
	struct subregion_mfile *me = mfile_assubregion(self);
	REF struct mfile *base;
	subregion_lock_acquire(me);
	base = xincref(me->srf_base);
	subregion_lock_release(me);
	if (base) {
		struct mfile_stream_ops const *stream;
		stream = base->mf_ops->mo_stream;
		if (stream && stream->mso_cc)
			(*stream->mso_cc)(base, info);
		decref_unlikely(base);
	}
}







PRIVATE struct mfile_stream_ops const subregion_stream_ops = {
	.mso_pread     = &subregion_pread,
	.mso_preadv    = &subregion_preadv,
	.mso_pwrite    = &subregion_pwrite,
	.mso_pwritev   = &subregion_pwritev,
	.mso_mmap      = &subregion_mmap,
	.mso_tryas     = &subregion_tryas,
	.mso_printlink = &subregion_printlink,
	.mso_sync      = &subregion_sync,
	.mso_cc        = &subregion_cc,
};

/* Operator table for sub-region mfile-s */
PUBLIC_CONST struct mfile_ops const mfile_subregion_ops = {
	.mo_destroy = &subregion_destroy,
	.mo_stream  = &subregion_stream_ops,
};


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL subregion_name_destroy)(struct fdirent *__restrict self) {
	kfree(self);
}

PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) REF struct fnode *KCALL
subregion_name_opennode(struct fdirent *__restrict self,
                        struct fdirnode *__restrict dir)
		THROWS(E_BADALLOC, E_IOERROR, ...) {
	/* Simulate a deleted file. We could  in theory store a weak  reference
	 * to  the associated sub-region  file, and return  that file here, but
	 * then "struct subregion_mfile" would need to be derived from "fnode",
	 * rather than the much simpler "struct mfile". */
	(void)self;
	(void)dir;
	COMPILER_IMPURE();
	return NULL;
}

PRIVATE struct fdirent_ops const subregion_name_ops = {
	.fdo_destroy  = &subregion_name_destroy,
	.fdo_opennode = &subregion_name_opennode,
	.fdo_getino   = NULL,
};


PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct fdirent *KCALL
mfile_subregion_makename(struct subregion_mfile *__restrict self)
		THROWS(E_BADALLOC) {
	enum {
		MAX_NAME_LEN = COMPILER_STRLEN("subregion:[%" PRIMAXuPTR ":%"
		                               "" PRIMAXxN(__SIZEOF_POS_T__) "-%"
		                               "" PRIMAXxN(__SIZEOF_POS_T__) "]"),
	};
	REF struct fdirent *result;
	result = (REF struct fdirent *)kmalloc(offsetof(struct fdirent, fd_name) +
	                                       (MAX_NAME_LEN + 1) * sizeof(char),
	                                       GFP_NORMAL);
	/* Note that the name here doesn't actually matter; `mfile_subregion_delete()'
	 * will  compare region names by-pointer, so 2 sibling regions (with identical
	 * names)  won't accidentally revoke each other's mappings when deleted one at
	 * a time. */
	result->fd_refcnt  = 1;
	result->fd_ops     = &subregion_name_ops;
	result->fd_ino     = (ino_t)(uintptr_t)skew_kernel_pointer(self->srf_base);
	result->fd_namelen = sprintf(result->fd_name,
	                             "subregion:[%" PRIuPTR ":%"
	                             "" PRIxN(__SIZEOF_POS_T__) "-%"
	                             "" PRIxN(__SIZEOF_POS_T__) "]",
	                             skew_kernel_pointer(self->srf_base),
	                             self->srf_minaddr, self->srf_maxaddr);
	result->fd_hash = fdirent_hash(result->fd_name, result->fd_namelen);
	result->fd_type = DT_REG;
	return result;
}

PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct subregion_mfile *KCALL
mfile_subregion_create(struct mfile *__restrict self,
                       struct subregion_mfile *parent,
                       PAGEDIR_PAGEALIGNED pos_t minaddr, pos_t maxaddr)
		THROWS(E_BADALLOC, E_ILLEGAL_OPERATION) {
	REF struct subregion_mfile *result;

	/* Assert that "self" supports "raw" I/O */
	if (!mfile_hasrawio(self)) {
		THROW(E_ILLEGAL_OPERATION,
		      E_ILLEGAL_OPERATION_CONTEXT_SUBREGION_NOT_POSSIBLE);
	}

	result = (REF struct subregion_mfile *)kmalloc(sizeof(struct subregion_mfile), GFP_NORMAL);
	TRY {
		/* Initialize fields needed for "mfile_subregion_makename()", and allocate the name */
		result->srf_minaddr  = minaddr;
		result->srf_maxaddr  = maxaddr;
		result->srf_base     = self;
		result->srf_nodename = mfile_subregion_makename(result);
	} EXCEPT {
		kfree(result);
		RETHROW();
	}

	/* Initialize subregion-specific fields */
	atomic_lock_init(&result->srf_lock);
	SLIST_INIT(&result->srf_lops);
	assert(result->srf_base == self);
	incref(self); /* For `result->srf_base' */
	result->srf_parent = parent; /* incref'd later */
	LIST_INIT(&result->srf_children);
	LIST_ENTRY_UNBOUND_INIT(&result->srf_chain);

	/* Initialize common "mfile" fields.
	 *
	 * Note how we make the file fixed-size, matching
	 * the # of bytes between `maxaddr' and `minaddr' */
	result->mf_parts             = MFILE_PARTS_ANONYMOUS;
	result->mf_changed.slh_first = MFILE_PARTS_ANONYMOUS;
	result->mf_flags = MFILE_F_FIXEDFILESIZE | MFILE_FN_ATTRREADONLY | MFILE_F_ROFLAGS;
	atomic64_init(&result->mf_filesize, (uint64_t)((maxaddr - minaddr) + 1));
	result->mf_atime = realtime();
	result->mf_mtime = result->mf_atime;
	result->mf_ctime = result->mf_atime;
	result->mf_btime = result->mf_atime;
	_mfile_init(result, &mfile_subregion_ops,
	            self->mf_blockshift, self->mf_iobashift);

	/* If there is a parent, insert the new subregion into its child-list */
	if (parent) {
		assert(result->srf_parent == parent);
		incref(parent); /* For "result->srf_parent" */
		TRY {
			subregion_lock_acquire(parent);
		} EXCEPT {
			destroy(result);
			RETHROW();
		}
		assert(result->srf_base == parent->srf_base);
		assert(result->srf_minaddr >= parent->srf_minaddr);
		assert(result->srf_maxaddr <= parent->srf_maxaddr);
		LIST_INSERT_HEAD(&parent->srf_children, result, srf_chain);
		subregion_lock_release(parent);
	}
	return result;
}

/* Create a new, distinct sub-region wrapper around "self".
 * Memory mappings created by this mapping will behave  the
 * same as mappings created by  "self", only that they  are
 * offset by "minaddr", and cannot exceed "maxaddr".
 *
 * Additionally, `mfile_subregion_delete()' can be used  to
 * replace all memory  mappings created  from the  returned
 * mfile (or some other  sub-region mfile created from  it)
 * with "/dev/void" without running the risk of this revoke
 * failing due to OOM.
 *
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_FILE_SUBREGION_BOUNDS: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_ALIGNMENT:E_INVALID_ARGUMENT_CONTEXT_FILE_SUBREGION_UNALIGNED_MINADDR: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_ALIGNMENT:E_INVALID_ARGUMENT_CONTEXT_FILE_SUBREGION_UNALIGNED_MAXADDR: [...]
 * @throw: E_ILLEGAL_OPERATION:E_ILLEGAL_OPERATION_CONTEXT_SUBREGION_NOT_POSSIBLE:
 *         Given file `self' does not support "raw" I/O, and also isn't another sub-region mfile.
 *         >> !mfile_has_rawio(self) && self->mf_ops != &mfile_subregion_ops
 * @throw: E_ILLEGAL_OPERATION:E_ILLEGAL_OPERATION_CONTEXT_MMAP_BEYOND_END_OF_FILE:
 *         Given file `maxaddr' is greater than the or equal to current size of `self' */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mfile *KCALL
mfile_subregion(struct mfile *__restrict self,
                PAGEDIR_PAGEALIGNED pos_t minaddr, pos_t maxaddr)
		THROWS(E_BADALLOC, E_INVALID_ARGUMENT, E_ILLEGAL_OPERATION) {
	pos_t self_size;

	/* Verify relation of minaddr/maxaddr */
	if (minaddr > maxaddr) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_FILE_SUBREGION_BOUNDS,
		      (uint32_t)minaddr, (uint32_t)(minaddr >> 32),
		      (uint32_t)maxaddr, (uint32_t)(maxaddr >> 32));
	}

	/* Verify that "minaddr" and "maxaddr" are properly aligned */
	if unlikely((minaddr & PAGEMASK) != 0) {
		THROW(E_INVALID_ARGUMENT_BAD_ALIGNMENT,
		      E_INVALID_ARGUMENT_CONTEXT_FILE_SUBREGION_UNALIGNED_MINADDR,
		      (uintptr_t)minaddr, (uintptr_t)PAGEMASK /*, (uintptr_t)0*/);
	}
	if unlikely((maxaddr & PAGEMASK) != PAGEMASK) {
		THROW(E_INVALID_ARGUMENT_BAD_ALIGNMENT,
		      E_INVALID_ARGUMENT_CONTEXT_FILE_SUBREGION_UNALIGNED_MAXADDR,
		      (uintptr_t)maxaddr, (uintptr_t)PAGEMASK, (uintptr_t)PAGEMASK);
	}

	/* Verify that "maxaddr" does not exceed the size of the underlying file.
	 * Note how we allow mapping beyond the end by aligning "self" to the nearest page boundary. */
	self_size = mfile_getsize(self);
	/* This overflow-check is here for 2^64 files like /dev/mem */
	if (!OVERFLOW_UADD(self_size, PAGEMASK, &self_size)) {
		self_size &= ~PAGEMASK;
		if (maxaddr >= self_size) {
			THROW(E_INVALID_OPERATION,
			      E_ILLEGAL_OPERATION_CONTEXT_MMAP_BEYOND_END_OF_FILE,
			      (uint32_t)maxaddr, (uint32_t)(maxaddr >> 32),
			      (uint32_t)self_size, (uint32_t)(self_size >> 32));
		}
	}

	/* Deal with the case where "self" is another sub-region file. */
	if (self->mf_ops == &mfile_subregion_ops) {
		REF struct mfile *base;
		struct subregion_mfile *me = mfile_assubregion(self);
		minaddr += me->srf_minaddr;
		maxaddr += me->srf_minaddr;
		subregion_lock_acquire(me);
		base = me->srf_base;
		if unlikely(!base)
			base = &dev_void;
		incref(base);
		subregion_lock_release(me);
		FINALLY_DECREF_UNLIKELY(base);
		return mfile_subregion_create(base, me, minaddr, maxaddr);
	}
	return mfile_subregion_create(self, NULL, minaddr, maxaddr);
}

/* Return the name used by file mappings made by a given sub-region mfile "self"
 * @assume(self->mf_ops == &mfile_subregion_ops); */
PUBLIC NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct fdirent *
NOTHROW(FCALL mfile_subregion_getname)(struct mfile *__restrict self) {
	struct subregion_mfile *me = mfile_assubregion(self);
	assert(me->mf_ops == &mfile_subregion_ops);
	return incref(me->srf_nodename);
}






/* Recursively tryincref() + acquire locks to all children of "self"
 * Destroyed  children are automatically  unbound from "self" during
 * this phase (meaning that after  this call, the caller holds  both
 * locks and references to all children of "self")
 *
 * The caller must already be holding a lock to "self".
 *
 * If the lock  to some child  cannot be acquired,  the locks to  all
 * children that were already locked are released, and those children
 * are then decref'd,  before a  reference to the  blocking child  is
 * returned.
 *
 * @return: NULL: All children were incref'd and locked
 * @return: * :   No children were incref'd or locked, and this is
 *                a reference to a  child whose lock is  blocking. */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) REF struct subregion_mfile *
NOTHROW(KCALL mfile_subregion_tryincref_and_trylock_children)(struct subregion_mfile *__restrict self) {
	struct subregion_mfile *child_iter;
	assert(subregion_lock_acquired(self));
	LIST_FOREACH_SAFE (child_iter, &self->srf_children, srf_chain) {
		if (!tryincref(child_iter)) {
			/* Remove dead children */
			LIST_UNBIND(child_iter, srf_chain);
			continue;
		}
		if (!subregion_lock_tryacquire(child_iter)) {
			/* Blocking child :( */
			struct subregion_mfile *rev_iter = child_iter;

			/* Release+decref children already locked. */
			while (rev_iter != LIST_FIRST(&self->srf_children)) {
				rev_iter = LIST_PREV_UNSAFE(rev_iter, srf_chain);
				subregion_lock_release(rev_iter);
				decref_unlikely(rev_iter);
			}

			/* Return reference to blocking child */
			return child_iter;
		}
		assertf(child_iter->srf_base == self->srf_base,
		        "Even when a child is deleted, it should immediately "
		        "remove itself from the parent's list of children");
		assert(child_iter->srf_minaddr >= self->srf_minaddr);
		assert(child_iter->srf_maxaddr <= self->srf_maxaddr);
	}
	return NULL;
}

/* Do the inverse of `mfile_subregion_tryincref_and_trylock_children()' after a successful call:
 * - Release locks from all children, and then proceed to decref those children.
 * - The lock to "self" is _NOT_ released, however (that must be done by the caller) */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL mfile_subregion_unlock_and_decref_children)(struct subregion_mfile *__restrict self) {
	struct subregion_mfile *child_iter;
	assert(subregion_lock_acquired(self));
	LIST_FOREACH (child_iter, &self->srf_children, srf_chain) {
		subregion_lock_release(child_iter);
		decref_unlikely(child_iter);
	}
}

/* Do the inverse of `mfile_subregion_tryincref_and_trylock_children_r()' */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL mfile_subregion_unlock_and_decref_children_r)(struct subregion_mfile *__restrict self) {
	struct subregion_mfile *child_iter;
	assert(subregion_lock_acquired(self));
	LIST_FOREACH (child_iter, &self->srf_children, srf_chain) {
		mfile_subregion_unlock_and_decref_children_r(child_iter);
		subregion_lock_release(child_iter);
		decref_unlikely(child_iter);
	}
}

/* Same as `mfile_subregion_tryincref_and_trylock_children()', but do so
 * recursively,  meaning that children-of-children  will be incref'd and
 * locked also. */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) REF struct subregion_mfile *
NOTHROW(KCALL mfile_subregion_tryincref_and_trylock_children_r)(struct subregion_mfile *__restrict self) {
	REF struct subregion_mfile *blocking;
	assert(subregion_lock_acquired(self));
	blocking = mfile_subregion_tryincref_and_trylock_children(self);
	if likely(blocking == NULL) {
		struct subregion_mfile *child_iter;
		LIST_FOREACH (child_iter, &self->srf_children, srf_chain) {
			blocking = mfile_subregion_tryincref_and_trylock_children_r(child_iter);
			if unlikely(blocking) {
				struct subregion_mfile *rev_iter = child_iter;
				while (rev_iter != LIST_FIRST(&self->srf_children)) {
					rev_iter = LIST_PREV_UNSAFE(rev_iter, srf_chain);
					mfile_subregion_unlock_and_decref_children_r(rev_iter);
				}
				mfile_subregion_unlock_and_decref_children(self);
				break;
			}
		}
	}
	return blocking;
}


struct mfile_mman_lock_filter {
	pos_t                         mfmlf_minaddr;    /* Min address of mpart-s to lock */
	pos_t                         mfmlf_maxaddr;    /* Max address of mpart-s to lock */
	struct subregion_mfile const *mfmlf_mnode_name; /* [?..?] Only lock mmans of mnode's featuring this, or one of it's children as "mn_fsname" */
};

PRIVATE ATTR_PURE WUNUSED NONNULL((1, 2)) bool
NOTHROW(FCALL subregion_mfile_references_name)(struct subregion_mfile const *__restrict self,
                                               struct fdirent const *__restrict name) {
	struct subregion_mfile const *child;
	if (self->srf_nodename == name)
		return true;
	LIST_FOREACH (child, &self->srf_children, srf_chain) {
		if (subregion_mfile_references_name(child, name))
			return true;
	}
	return false;
}
#define mfile_mman_lock_filter_references_name(self, name) \
	subregion_mfile_references_name((self)->mfmlf_mnode_name, name)


/* Check if "mm" is referenced by another mpart encountered before (not including) "stop_at" */
PRIVATE NOBLOCK WUNUSED NONNULL((1, 2, 3)) bool
NOTHROW(KCALL _mfile_parts_contains_mman_before)(struct mpart_tree_minmax const *__restrict mima,
                                                 struct mfile_mman_lock_filter const *__restrict filter,
                                                 struct mman const *__restrict mm, struct mnode const *stop_at) {
	struct mpart *iter = mima->mm_min;
	assert(mima->mm_min);
	assert(mima->mm_max);
	for (;;) {
		unsigned int i;
		assert(!wasdestroyed(iter));
		assert(mpart_lock_acquired(iter));
		for (i = 0; i < lengthof(iter->_mp_nodlsts); ++i) {
			struct mnode *node;
			LIST_FOREACH (node, &iter->_mp_nodlsts[i], mn_link) {
				assert(node->mn_part == iter);
				if (node->mn_fspath != NULL)
					continue;
				if (node->mn_fsname == NULL)
					continue;
				if (!mfile_mman_lock_filter_references_name(filter, node->mn_fsname))
					continue;
				if (node == stop_at)
					goto nope;
				if (mm == node->mn_mman)
					return true;
			}
		}
		if (iter == mima->mm_max)
			break;
		iter = mpart_tree_nextnode(iter);
	}
nope:
	return false;
}

/* Check if "mm" is referenced by another mpart encountered after (not including) "start_after_*" */
PRIVATE NOBLOCK WUNUSED NONNULL((1, 2, 3)) bool
NOTHROW(KCALL _mfile_parts_contains_mman_after)(struct mpart_tree_minmax const *__restrict mima,
                                                struct mfile_mman_lock_filter const *__restrict filter,
                                                struct mman const *__restrict mm,
                                                unsigned int start_after_list,
                                                struct mnode *start_after_node) {
	unsigned int i = start_after_list;
	struct mpart *iter = mima->mm_min;
	struct mnode *node = start_after_node;
	assert(mima->mm_min);
	assert(mima->mm_max);
	goto start;
	for (;;) {
		assert(!wasdestroyed(iter));
		assert(mpart_lock_acquired(iter));
		for (i = 0; i < lengthof(iter->_mp_nodlsts); ++i) {
			LIST_FOREACH (node, &iter->_mp_nodlsts[i], mn_link) {
				assert(node->mn_part == iter);
				if (node->mn_fspath != NULL)
					continue;
				if (node->mn_fsname == NULL)
					continue;
				if (!mfile_mman_lock_filter_references_name(filter, node->mn_fsname))
					continue;
				if (mm == node->mn_mman)
					return true;
start:;
			}
		}
		if (iter == mima->mm_max)
			break;
		iter = mpart_tree_nextnode(iter);
	}
/*nope:*/
	return false;
}

#define mfile_unlock_and_decref_mmans_of_parts(self, filter) \
	mfile_unlock_and_decref_mmans_of_parts_before(self, filter, NULL)

/* Do the inverse of `mfile_tryincref_and_trylock_mmans_of_parts()',
 * but  stop  releasing   locks  when   "stop_at"  is   encountered. */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL mfile_unlock_and_decref_mmans_of_parts_before)(struct mfile *__restrict self,
                                                             struct mfile_mman_lock_filter const *__restrict filter,
                                                             struct mnode const *stop_at) {
	struct mpart_tree_minmax mima;
	assert(self->mf_parts != MFILE_PARTS_ANONYMOUS);
	assert((mima.mm_min != NULL) == (mima.mm_max != NULL));
	if (mima.mm_min) {
		struct mpart *iter = mima.mm_min;
		for (;;) {
			unsigned int i;
			assert(!wasdestroyed(iter));
			assert(mpart_lock_acquired(iter));
			for (i = 0; i < lengthof(iter->_mp_nodlsts); ++i) {
				struct mnode *node;
				LIST_FOREACH (node, &iter->_mp_nodlsts[i], mn_link) {
					REF struct mman *mm;
					assert(node->mn_part == iter);
					if (node == stop_at)
						return;
					if (node->mn_fspath != NULL)
						continue;
					if (node->mn_fsname == NULL)
						continue;
					if (!mfile_mman_lock_filter_references_name(filter, node->mn_fsname))
						continue;
					mm = node->mn_mman;
					if (wasdestroyed(mm))
						continue; /* Dead mman */
					if (!mman_lock_writing(mm))
						continue; /* Already unlock */

					/* Make sure that the reason "mm" is locked isn't  because
					 * someone else is holding that lock after we released it. */
					if (_mfile_parts_contains_mman_before(&mima, filter, mm, node))
						continue; /* Someone else is holding the lock */
					mman_lock_endwrite(mm);
					decref_unlikely(mm);
				}
			}
			if (iter == mima.mm_max)
				break;
			iter = mpart_tree_nextnode(iter);
		}
	}
}

/* Incref + trylock every distinct mman that is mapping some part of  "self"
 * On success (all locks +  references acquired), return "NULL". On  failure
 * (a blocking mman was encountered), release all already-acquired locks and
 * return a reference to the blocking mman.
 *
 * This is only done for parts/nodes matching "filter" */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) REF struct mman *
NOTHROW(KCALL mfile_tryincref_and_trylock_mmans_of_parts)(struct mfile *__restrict self,
                                                          struct mfile_mman_lock_filter const *__restrict filter) {
	struct mpart_tree_minmax mima;
	assert(mfile_lock_writing(self));
	assert(self->mf_parts != MFILE_PARTS_ANONYMOUS);
	mpart_tree_minmaxlocate(self->mf_parts,
	                        filter->mfmlf_minaddr,
	                        filter->mfmlf_maxaddr,
	                        &mima);
	assert((mima.mm_min != NULL) == (mima.mm_max != NULL));
	if (mima.mm_min) {
		struct mpart *iter = mima.mm_min;
		for (;;) {
			unsigned int i;
			assert(!wasdestroyed(iter));
			assert(mpart_lock_acquired(iter));
			for (i = 0; i < lengthof(iter->_mp_nodlsts); ++i) {
				struct mnode *node;
				LIST_FOREACH (node, &iter->_mp_nodlsts[i], mn_link) {
					REF struct mman *mm;
					assert(node->mn_part == iter);
					if (node->mn_fspath != NULL)
						continue;
					if (node->mn_fsname == NULL)
						continue;
					if (!mfile_mman_lock_filter_references_name(filter, node->mn_fsname))
						continue;
					mm = node->mn_mman;
					if (!tryincref(mm))
						continue; /* Dead mman */
					if (!mman_lock_trywrite(mm)) {
						/* Maybe we just already locked this one? */
						bool already_locked;
						already_locked = _mfile_parts_contains_mman_before(&mima, filter, mm, node);
						if (already_locked) {
							/* Already locked :) */
							decref_nokill(mm);
						} else {
							/* Nope: we're not the ones holding this lock! */
							mfile_unlock_and_decref_mmans_of_parts_before(self, filter, node);
							return mm;
						}
					}
				}
			}
			if (iter == mima.mm_max)
				break;
			iter = mpart_tree_nextnode(iter);
		}
	}
	return NULL;
}


/* Mark  "self" as  having been  deleted. The  caller must be
 * holding locks to both "self", and (if present) its parent.
 * the caller must also be holding a reference to "srf_base",
 * since this function assumes that decref'ing it won't cause
 * the base-file to ever be destroyed. */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL subregion_mfile_maskdeleted)(struct subregion_mfile *__restrict self) {
	assert(subregion_lock_acquired(self));
	assertf(LIST_EMPTY(&self->srf_children), "Caller must delete+unbind children first");
	decref_nokill(self->srf_base);
	self->srf_base = NULL;
	if (self->srf_parent) {
		assert(subregion_lock_acquired(self->srf_parent));
		assert(LIST_ISBOUND(self, srf_chain));
		decref_nokill(self->srf_parent);
		self->srf_parent = NULL;
		LIST_UNBIND(self, srf_chain);
	}
}

/* Same  as  `subregion_mfile_maskdeleted()', but  also  recursively mark
 * all children as deleted, and afterwards, unlock+decref those children. */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL subregion_mfile_maskdeleted_and_unlock_and_decref_children_r)(struct subregion_mfile *__restrict self) {
	struct subregion_mfile *child_iter;
	LIST_FOREACH_SAFE (child_iter, &self->srf_children, srf_chain) {
		assert(child_iter->srf_parent == self);
		assert(LIST_ISBOUND(child_iter, srf_chain));
		subregion_mfile_maskdeleted_and_unlock_and_decref_children_r(child_iter);
		subregion_lock_release(child_iter);
		decref(child_iter);
	}
	subregion_mfile_maskdeleted(self);
}


/* Mark all mnode-s  matching "filter" with  "MNODE_F_VOIDMEM"
 * and override their memory mappings in their respective page
 * directories.
 *
 * Dead mman-s are skipped  automatically, but the caller  is
 * responsible to be holding references and locks to anything
 * that may potentially be touched here.
 *
 * This function will also unlock+decref every distinct mman
 * that had some of its mappings void'ed-out.
 *
 * !!! THIS FUNCTION CANNOT BE ROLLED BACK !!!
 */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL mfile_replace_mappings_with_void_and_unlock_and_decref_mmans)(struct mfile *__restrict self,
                                                                            struct mfile_mman_lock_filter const *__restrict filter) {
	struct mpart_tree_minmax mima;
	assert(mfile_lock_writing(self));
	assert(self->mf_parts != MFILE_PARTS_ANONYMOUS);
	mpart_tree_minmaxlocate(self->mf_parts,
	                        filter->mfmlf_minaddr,
	                        filter->mfmlf_maxaddr,
	                        &mima);
	assert((mima.mm_min != NULL) == (mima.mm_max != NULL));
	if (mima.mm_min) {
		for (;;) {
			unsigned int i;
			assert(!wasdestroyed(mima.mm_min));
			assert(mpart_lock_acquired(mima.mm_min));
			for (i = 0; i < lengthof(mima.mm_min->_mp_nodlsts); ++i) {
				struct mnode *node;
				LIST_FOREACH_SAFE (node, &mima.mm_min->_mp_nodlsts[i], mn_link) {
					REF struct mman *mm;
					assert(node->mn_part == mima.mm_min);
					if (node->mn_fspath != NULL)
						continue;
					if (node->mn_fsname == NULL)
						continue;
					if (!mfile_mman_lock_filter_references_name(filter, node->mn_fsname))
						continue;
					mm = node->mn_mman;
					if unlikely(wasdestroyed(mm))
						continue; /* Dead mman */
					assert(mman_lock_writing(mm));

					/* Remove "node" from "part" and mark as "MNODE_F_VOIDMEM"
					 * NOTE: The flag may (seem) to already be set for certain mnode-s at
					 *       this point, but this only appears so because `MNODE_F_MLOCK'
					 *       and `MNODE_F_VOIDMEM' share the same bit. */
					atomic_or(&node->mn_flags, MNODE_F_VOIDMEM);
					atomic_write(&node->mn_part, NULL);
					decref_nokill(mima.mm_min); /* Reference stolen from "node->mn_part" */
					LIST_REMOVE(node, mn_link);
					DBG_memset(&node->mn_link, 0xcc, sizeof(node->mn_link));

					/* Unlink from mman's list of writable nodes (in case it was  bound)
					 * This list link isn't valid for mnode-s with NULL-parts, so we can
					 * even DBG_memset the link entry. */
					if (LIST_ISBOUND(node, mn_writable))
						LIST_REMOVE(node, mn_writable);
					DBG_memset(&node->mn_writable, 0xcc, sizeof(node->mn_writable));

					/* Hard-replace live memory mapping with /dev/void. */
					if (mnode_pagedir_prepare_p(mm->mm_pagedir_p, node)) {
						mnode_pagedir_mapvoid_p(mm->mm_pagedir_p, node, prot_from_mnodeflags(node->mn_flags));
						mnode_pagedir_unprepare_p(mm->mm_pagedir_p, node);
					} else {
						/* Just unmap userspace and let the #PF handler re-build it. */
						pagedir_unmap_userspace_p(mm->mm_pagedir_p);
					}
					mnode_pagedir_sync_smp_p(mm->mm_pagedir_p, node);

					/* decref+unlock the associated mman if it isn't referenced again. */
					if (!_mfile_parts_contains_mman_after(&mima, filter, mm, i, node)) {
						mman_lock_endwrite(mm);
						decref_unlikely(mm);
					}
				}
			}
			if (mima.mm_min == mima.mm_max)
				break;
			mima.mm_min = mpart_tree_nextnode(mima.mm_min);
		}
	}
}


/* Delete all memory mappings created from a given sub-region mfile "self",
 * as well as recursively do the same for any further sub-regions that  may
 * have been created using "self".
 *
 * @assume(self->mf_ops == &mfile_subregion_ops);
 * @throw: E_WOULDBLOCK_PREEMPTED: Preemption is disabled (never happens if called from user-space) */
PUBLIC NONNULL((1)) void KCALL
mfile_subregion_delete(struct mfile *__restrict self)
		THROWS(E_WOULDBLOCK_PREEMPTED) {
	struct mfile_mman_lock_filter mman_filter;
	struct subregion_mfile *me = mfile_assubregion(self);
	struct subregion_mfile *parent;
	struct mfile *base;
	assert(me->mf_ops == &mfile_subregion_ops);
	(void)me;
	mman_filter.mfmlf_minaddr    = me->srf_minaddr;
	mman_filter.mfmlf_maxaddr    = me->srf_maxaddr;
	mman_filter.mfmlf_mnode_name = me;

again:
	subregion_lock_acquire(me);
#define LOCAL_unlockall() \
	subregion_lock_release(me)
	base = me->srf_base;
	if (!base) {
		/* Subregion was already deleted -> nothing left to do */
		LOCAL_unlockall();
		return;
	}

	/* Acquire a lock to the parent of "me" (if there is one)
	 * This lock will be needed to later remove "me" from the
	 * parent's list of children. */
	parent = me->srf_parent;
	if (parent && !subregion_lock_tryacquire(parent)) {
		incref(parent);
		LOCAL_unlockall();
		FINALLY_DECREF_UNLIKELY(parent);
		subregion_lock_waitfor(parent);
		goto again;
	}
#undef LOCAL_unlockall
#define LOCAL_unlockall()                              \
	(!(parent) || (subregion_lock_release(parent), 0), \
	 subregion_lock_release(me))

	/* Acquire lock to "base" (so we can then lock all the mpart-s) */
	if (!mfile_lock_trywrite(base)) {
		incref(base);
		LOCAL_unlockall();
		FINALLY_DECREF_UNLIKELY(base);
		mfile_lock_waitwrite(base);
		goto again;
	}
#undef LOCAL_unlockall
#define LOCAL_unlockall()                              \
	(mfile_lock_endwrite(base),                        \
	 !(parent) || (subregion_lock_release(parent), 0), \
	 subregion_lock_release(me))

	/* Recursively incref + acquire locks to all children created from "me" */
	{
		REF struct subregion_mfile *blocking_child;
		blocking_child = mfile_subregion_tryincref_and_trylock_children_r(me);
		if unlikely(blocking_child) {
			LOCAL_unlockall();
			FINALLY_DECREF_UNLIKELY(blocking_child);
			subregion_lock_waitfor(blocking_child);
			goto again;
		}
	}
#undef LOCAL_unlockall
#define LOCAL_unlockall()                              \
	(mfile_subregion_unlock_and_decref_children_r(me), \
	 mfile_lock_endwrite(base),                        \
	 !(parent) || (subregion_lock_release(parent), 0), \
	 subregion_lock_release(me))

	/* Check if "base" has been deleted.
	 * XXX: This is an edge-case that is not fully handled:
	 *      When a file is deleted, its memory mappings are
	 *      not altered, and as such, we also won't be able
	 *      to replace those mappings with /dev/void... */
	if likely(base->mf_parts != MFILE_PARTS_ANONYMOUS) {
		/* Acquire locks to the mem-parts of "base"
		 *
		 * Since all of our children are necessarily further sub-regions
		 * of the address-range of "me", we can just
		 */
		REF struct mman *blocking_mman;
		REF struct mpart *blocking_part;
		blocking_part = mfile_tryincref_and_lock_parts_r(base, mman_filter.mfmlf_minaddr, mman_filter.mfmlf_maxaddr);
		if unlikely(blocking_part) {
			LOCAL_unlockall();
			FINALLY_DECREF_UNLIKELY(blocking_part);
			mpart_lock_waitfor(blocking_part);
			goto again;
		}
#undef LOCAL_unlockall
#define LOCAL_unlockall()                                                                                  \
		((base->mf_parts == MFILE_PARTS_ANONYMOUS) ||                                                      \
		 (mfile_unlock_and_decref_parts_r(base, mman_filter.mfmlf_minaddr, mman_filter.mfmlf_maxaddr), 0), \
		 mfile_subregion_unlock_and_decref_children_r(me),                                                 \
		 mfile_lock_endwrite(base),                                                                        \
		 !(parent) || (subregion_lock_release(parent), 0),                                                 \
		 subregion_lock_release(me))

		/* Acquire locks to all mman-s referenced by mnode-s  linked
		 * to mpart-s of "base" within the subregion's address range */
		blocking_mman = mfile_tryincref_and_trylock_mmans_of_parts(base, &mman_filter);
		if unlikely(blocking_mman) {
			LOCAL_unlockall();
			FINALLY_DECREF_UNLIKELY(blocking_mman);
			mman_lock_waitwrite(blocking_mman);
			goto again;
		}
#undef LOCAL_unlockall
#define LOCAL_unlockall()                                                                              \
		((base->mf_parts == MFILE_PARTS_ANONYMOUS) ||                                                  \
		 (mfile_unlock_and_decref_mmans_of_parts(base, &mman_filter),                                  \
		  mfile_unlock_and_decref_parts_r(base, mman_filter.mfmlf_minaddr, mman_filter.mfmlf_maxaddr), \
		  0),                                                                                          \
		 mfile_subregion_unlock_and_decref_children_r(me),                                             \
		 mfile_lock_endwrite(base),                                                                    \
		 !(parent) || (subregion_lock_release(parent), 0),                                             \
		 subregion_lock_release(me))

		/* At this point, all relevant locks are acquired, and
		 * we  can proceed to  replace mappings with /dev/void */
		mfile_replace_mappings_with_void_and_unlock_and_decref_mmans(self, &mman_filter);

		/* Release locks to mman-s and mpart-s here. This must be done before
		 * the  actual tree of sub-regions is marked as deleted, because once
		 * that has happened, said tree can no longer be walked, also meaning
		 * we'd no longer know which mpart-s/mnode-s/mman-s we've locked. */
//		mfile_unlock_and_decref_mmans_of_parts(base, &mman_filter); /* Already done by previous call */
		mfile_unlock_and_decref_parts_r(base, mman_filter.mfmlf_minaddr, mman_filter.mfmlf_maxaddr);
	}
#undef LOCAL_unlockall
#define LOCAL_unlockall()                              \
	(mfile_subregion_unlock_and_decref_children_r(me), \
	 mfile_lock_endwrite(base),                        \
	 !(parent) || (subregion_lock_release(parent), 0), \
	 subregion_lock_release(me))

	/* Will be dropped later, but needed here so "base"
	 * isn't destroyed  while  locks  are  still  held. */
	incref(base);

	/* With mappings  replaced  with  /dev/void,  we
	 * can now mark "me" and all children as deleted
	 *
	 * Since this  destroys the  tree of  sub-regions
	 * originating  from "me", it  must also decref +
	 * release locks from our children at this point. */
	subregion_mfile_maskdeleted_and_unlock_and_decref_children_r(me);
	assert(LIST_EMPTY(&me->srf_children));
#undef LOCAL_unlockall
#define LOCAL_unlockall()                              \
	(/*mfile_subregion_unlock_and_decref_children_r(me),*/ \
	 mfile_lock_endwrite(base),                        \
	 !(parent) || (subregion_lock_release(parent), 0), \
	 subregion_lock_release(me))

	/* Release all (remaining) locks */
	LOCAL_unlockall();

	/* Drop manual reference from above. */
	decref(base);
#undef LOCAL_unlockall
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_SUBREGION_C */
