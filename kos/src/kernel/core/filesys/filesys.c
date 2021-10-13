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
#ifndef GUARD_KERNEL_CORE_FILESYS_FILESYS_C
#define GUARD_KERNEL_CORE_FILESYS_FILESYS_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/fs/devfs.h>
#include <kernel/fs/filesys.h>

#include <hybrid/atomic.h>

#include <stdbool.h>
#include <stddef.h>

DECL_BEGIN


/* Global set of registered filesystem formats. */
PUBLIC struct ffilesys_list ffilesys_formats_list = { .lh_first = &devfs_filesys };
PUBLIC struct atomic_lock ffilesys_formats_lock = ATOMIC_LOCK_INIT;
PUBLIC struct lockop_slist ffilesys_formats_lops = SLIST_HEAD_INITIALIZER(ffilesys_formats_lops);


/* Register a given filesystem format.
 * @return: true:  Success.
 * @return: false: The format was already registered. */
PUBLIC NONNULL((1)) bool FCALL
ffilesys_register(struct ffilesys *__restrict self)
		THROWS(E_WOULDBLOCK) {
	ffilesys_formats_acquire();
	if unlikely(LIST_ISBOUND(self, ffs_link)) {
		ffilesys_formats_release();
		return false;
	}
	self->_ffs_lop.lo_func = NULL; /* Needed for `ffilesys_unregister()' */
	LIST_INSERT_HEAD(&ffilesys_formats_list, self, ffs_link);
	incref(self);
	ffilesys_formats_release();
	return true;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(LOCKOP_CC ffilesys_unregister_postlop)(struct postlockop *__restrict self) {
	REF struct ffilesys *me;
	me = container_of(self, struct ffilesys, _ffs_plop);
	decref_unlikely(me);
}
PRIVATE NOBLOCK NONNULL((1)) struct postlockop *
NOTHROW(LOCKOP_CC ffilesys_unregister_lop)(struct lockop *__restrict self) {
	REF struct ffilesys *me;
	me = container_of(self, struct ffilesys, _ffs_lop);
	LIST_UNBIND(me, ffs_link);
	me->_ffs_plop.plo_func = &ffilesys_unregister_postlop;
	return &me->_ffs_plop;
}


/* Unregister a given filesystem format.
 * @return: true:  Success.
 * @return: false: The format wasn't registered. */
PUBLIC NONNULL((1)) bool
NOTHROW(FCALL ffilesys_unregister)(struct ffilesys *__restrict self) {
	if (!LIST_ISBOUND(self, ffs_link))
		return false;
	if (!ATOMIC_CMPXCH(self->_ffs_lop.lo_func, NULL, &ffilesys_unregister_lop))
		return false;
	if (ffilesys_formats_tryacquire()) {
		LIST_UNBIND(self, ffs_link);
		ffilesys_formats_release();
		decref_unlikely(self);
	} else {
		/* Remove asynchronously */
		lockop_enqueue(&ffilesys_formats_lops, &self->_ffs_lop);
		_ffilesys_formats_reap();
	}
	return true;
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_FILESYS_C */
