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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MFILEMETA_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MFILEMETA_C 1
#define __WANT_DNOTIFY_LINK__dnl_fildead
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/dirent.h>
#include <kernel/fs/notify.h>
#include <kernel/malloc.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mfilemeta.h>

#include <assert.h>
#include <atomic.h>
#include <stddef.h>
#include <string.h>


DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
#ifndef __dnotify_link_slist_defined
#define __dnotify_link_slist_defined
SLIST_HEAD(dnotify_link_slist, dnotify_link);
#endif /* !__dnotify_link_slist_defined */
#endif /* CONFIG_HAVE_KERNEL_FS_NOTIFY */



/* Destroy the given mfile meta-data `self' that was originally allocated & initialized for `file' */
PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mfilemeta_destroy)(struct mfilemeta *self,
                                 struct mfile *file) {
	(void)file;

	/* Clean up a notify controller if one is attached to the file. */
#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
	if (self->mfm_notify != NULL) {
		struct inotify_controller *notify;
		struct dnotify_link_slist deadlinks;
		COMPILER_READ_BARRIER();
		SLIST_INIT(&deadlinks);
		notify_lock_acquire();
		if ((notify = self->mfm_notify) != NULL) {
			assertf(LIST_EMPTY(&notify->inc_listeners),
			        "Per-file listeners should have kept us "
			        "alive via `notify_listener::nl_file'");
			assertf(!LIST_EMPTY(&notify->inc_dirs),
			        "If this was also empty, then the notify "
			        "controller should have already been freed!");
			assertf(notify->inc_file == file,
			        "Notify contrller of different file? (%p != %p)",
			        notify->inc_file, file);

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
			stream = file->mf_ops->mo_stream;
			/* Detach the notify file handle (if that operator is defined) */
			if (stream && stream->mso_notify_detach)
				(*stream->mso_notify_detach)(file, notify->inc_fhnd);
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

	mfilemeta_free(self);
}


/* Ensure that `self->mf_meta' has been allocated, which is then returned. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) struct mfilemeta *FCALL
mfile_getmeta(struct mfile *__restrict self) THROWS(E_BADALLOC) {
	struct mfilemeta *result;
	/* Check if already allocated. */
	result = atomic_read(&self->mf_meta);
	if (result != NULL)
		return result;

	/* Allocate lazily */
	result = mfilemeta_alloc();
	mfilemeta_init(result, self);

	/* Install into the given file. */
	if likely(atomic_cmpxch(&self->mf_meta, NULL, result))
		return result;

	/* Race condition: another thread allocated also, and was faster than us! */
#ifdef MFILEMETA_DESTROY_MAYOMIT_AFTER_FRESH_INIT
	mfilemeta_free(result);
#else /* MFILEMETA_DESTROY_MAYOMIT_AFTER_FRESH_INIT */
	mfilemeta_destroy(result, self);
#endif /* !MFILEMETA_DESTROY_MAYOMIT_AFTER_FRESH_INIT */
	result = atomic_read(&self->mf_meta);
	assert(result != NULL);
	return result;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MFILEMETA_C */
