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
#include <format-printer.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

DECL_BEGIN

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
	info->hmi_minaddr += me->srf_minaddr; /* TODO: Handle overflow */
	info->hmi_maxaddr += me->srf_minaddr; /* TODO: Handle overflow */
	if (info->hmi_maxaddr > me->srf_maxaddr)
		info->hmi_maxaddr = me->srf_maxaddr;
	info->hmi_file = me->srf_base;
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
	self_size = CEIL_ALIGN(self_size, PAGESIZE);
	if (maxaddr >= self_size) {
		THROW(E_ILLEGAL_OPERATION,
		      E_ILLEGAL_OPERATION_CONTEXT_MMAP_BEYOND_END_OF_FILE,
		      (uint32_t)maxaddr, (uint32_t)(maxaddr >> 32),
		      (uint32_t)self_size, (uint32_t)(self_size >> 32));
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



/* Delete all memory mappings created from a given sub-region mfile "self",
 * as well as recursively do the same for any further sub-regions that  may
 * have been created using "self".
 *
 * @assume(self->mf_ops == &mfile_subregion_ops);
 * @throw: E_WOULDBLOCK_PREEMPTED: Preemption is disabled (never happens if called from user-space) */
PUBLIC NONNULL((1)) void KCALL
mfile_subregion_delete(struct mfile *__restrict self)
		THROWS(E_WOULDBLOCK_PREEMPTED) {
	struct subregion_mfile *me = mfile_assubregion(self);
	struct mfile *base;
	assert(me->mf_ops == &mfile_subregion_ops);
	(void)me;

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

	/* Acquire lock to "base" (so we can then lock all the mpart-s) */
	if (!mfile_lock_trywrite(base)) {
		incref(base);
		LOCAL_unlockall();
		FINALLY_DECREF_UNLIKELY(base);
		mfile_lock_waitwrite(base);
		goto again;
	}
#undef LOCAL_unlockall
#define LOCAL_unlockall()       \
	(mfile_lock_endwrite(base), \
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
	 subregion_lock_release(me))

	/* Check if "base" has been deleted.
	 * XXX: This is an edge-case that is not fully handled:
	 *      When a file is deleted, its memory mappings are
	 *      not altered, and as such, we also won't be able
	 *      to replace those mappings with /dev/void... */
	if likely(base->mf_parts != MFILE_PARTS_ANONYMOUS) {
		/* Acquire locks to the mem-parts of "base" */
		REF struct mpart *blocking_part;
		blocking_part = mfile_tryincref_and_lock_parts_r(base, me->srf_minaddr, me->srf_maxaddr);
		if unlikely(blocking_part) {
			LOCAL_unlockall();
			FINALLY_DECREF_UNLIKELY(blocking_part);
			mpart_lock_waitfor(blocking_part);
			goto again;
		}
	}
#undef LOCAL_unlockall
#define LOCAL_unlockall()                                                          \
	((base->mf_parts == MFILE_PARTS_ANONYMOUS) ||                                  \
	 (mfile_unlock_and_decref_parts_r(base, me->srf_minaddr, me->srf_maxaddr), 0), \
	 mfile_subregion_unlock_and_decref_children_r(me),                             \
	 mfile_lock_endwrite(base),                                                    \
	 subregion_lock_release(me))

	/* Acquire locks to all mman-s referenced by mnode-s  linked
	 * to mpart-s of "base" within the subregion's address range */
	/* TODO */


	/* TODO: Have a special "mfile" that allows for creation of arbitrary sub-regions of other mfile-s,
	 *       while also having the ability to NOTHROW void-out all memory mappings made using that same
	 *       mfile:
	 * - Only possible to create sub-regions of mfile-s with "mfile_hasrawio()" (or other sub-region mfile-s)
	 * - Override  "mo_stream->mso_mmap" to re-direct to underlying file, while also applying region
	 *   offset. Additionally, inject special values for "hmi_fspath" / "hmi_fsname" that are unique
	 *   to the sub-region mfile (meaning mnode-s created  can later be identified by these  special
	 *   path / name values)
	 *   Also: briefly lock "subregion_file" and assert that it hasn't been void'ed, yet.
	 *         if it has been voided, simply  re-direct the mmap request to  `/dev/void'.
	 * - Provide an IOCTL to void out any memory mapping created from the sub-region, implemented as:
	 *   >> struct mfile *base = subregion_file->srf_base;
	 *   >> // Acquire locks to mparts and mmans that were created
	 *   >> // using the sub-region (rather than the original file)
	 *   >> //
	 *   >> // Since all locks here are atomic, the ioctl is NOTHROW for user-space.
	 *   >> //
	 *   >> // By acquiring write-locks to all components that are able to reach the
	 *   >> // mnode in some way, we can gauranty that no-one might possibly still be
	 *   >> // reading the fields of the mnode, also meaning that we're allowed to
	 *   >> // write to the (normally) [const] "mn_part" field.
	 *   >> //
	 *   >> // Note that this acquires:
	 *   >> // - mfile: mf_lock                    (of "subregion_file", to prevent creation or more mappings)
	 *   >> // - mfile: mf_lock                    (of "base")
	 *   >> // - mpart: tryincref+MPART_F_LOCKBIT  (of any non-destroyed mpart with nodes referencing the path+name of "subregion_file")
	 *   >> // - mnode: tryincref+mn_mman->mm_lock (of any non-destroyed mnode->mman referencing the path+name of "subregion_file")
	 *   >> INCREF_AND_LOCK_ALL_MPARTS_AND_MMANS_OF_MPARTS_REFERENCING(base,
	 *   >>         mnode_path: subregion_file->srf_path,
	 *   >>         mnode_name: subregion_file->srf_name);
	 *   >> struct mpart *part;
	 *   >> FOREACH_MPART_SAFE (part, base) {
	 *   >>     struct mnode *node;
	 *   >>     if (wasdestroyed(part))
	 *   >>         continue;
	 *   >>     if (!HAS_MNODES_WITH_PATH_AND_NAME(part, subregion_file->srf_path, subregion_file->srf_name))
	 *   >>         continue;
	 *   >>     FOREACH_MNODE_SAFE (node, part) {
	 *   >>         struct mman *mm = node->mn_mman;
	 *   >>         assert(node->mn_part == part);
	 *   >>         if (wasdestroyed(mm))
	 *   >>             continue;
	 *   >>         if (node->mn_fspath != subregion_file->srf_path)
	 *   >>             continue;
	 *   >>         if (node->mn_fsname != subregion_file->srf_name)
	 *   >>             continue;
	 *   >>
	 *   >>         // Remove "node" from "part" and mark as "MNODE_F_VOIDMEM"
	 *   >>         atomic_or(&node->mn_flags, MNODE_F_VOIDMEM);
	 *   >>         atomic_write(&node->mn_part, NULL);
	 *   >>         decref_nokill(part);
	 *   >>         LIST_REMOVE(node, mn_link);
	 *   >>
	 *   >>         // Not valid if "mn_part == NULL"
	 *   >>         if (LIST_ISBOUND(node, mn_writable))
	 *   >>             LIST_REMOVE(node, mn_writable);
	 *   >>
	 *   >>         // Hard-replace live memory mapping with /dev/void
	 *   >>         if (mnode_pagedir_prepare_p(mm->mm_pagedir_p, node)) {
	 *   >>             mnode_pagedir_mapvoid_p(mm->mm_pagedir_p, node, prot_from_mnodeflags(node->mn_flags));
	 *   >>             mnode_pagedir_unprepare_p(mm->mm_pagedir_p, node);
	 *   >>         } else {
	 *   >>             pagedir_unmap_userspace_p(mm->mm_pagedir_p);
	 *   >>         }
	 *   >>         mnode_pagedir_sync_smp_p(mm->mm_pagedir_p, node);
	 *   >>
	 *   >>         // Release lock/reference to mman not referenced again
	 *   >>         if (!IS_MMAN_REFERENCED_AGAIN_LATER(mm)) {
	 *   >>             mman_lock_endwrite(mm);
	 *   >>             decref(mm);
	 *   >>         }
	 *   >>     }
	 *   >>     mpart_lock_release(part);
	 *   >>     decref(part);
	 *   >> }
	 *   >> mfile_lock_endwrite(base);
	 *   >> MARK_AS_VOID(subregion_file); // Cause future mmap-s to go to /dev/void
	 *   >> mfile_lock_endwrite(subregion_file);
	 */

	/* TODO */
	LOCAL_unlockall();
	THROW(E_NOT_IMPLEMENTED_TODO);
#undef LOCAL_unlockall
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_SUBREGION_C */
