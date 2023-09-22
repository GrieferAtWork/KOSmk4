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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILEMETA_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILEMETA_H 1

#include <kernel/compiler.h>
#include <kernel/mman/mfile.h>

#ifdef __CC__
DECL_BEGIN

#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
struct inotify_controller;
#endif /* CONFIG_HAVE_KERNEL_FS_NOTIFY */

/* mfile-metadata controller.
 *
 * Used to store volatile metadata components surrounding `struct mfile' that
 * are too rarely used to justify putting them into the base mfile structure.
 *
 * This includes:
 * - inotify controllers (as used for monitoring files for changes)
 * - user-space file locks (as used by `flock(2)')
 * - ...
 */
struct mfilemeta {
#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
	struct inotify_controller *mfm_notify; /* [0..1][owned][lock(!PREEMPTION && :notify_lock)] Notify controller. */
#endif /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
	int placeholder;
	/* TODO: flock() support */
};

#define mfilemeta_alloc()          (struct mfilemeta *)kmalloc(sizeof(struct mfilemeta), GFP_NORMAL)
#define mfilemeta_free(self)       kfree(self)
#define mfilemeta_xfree(self)      kfree(self)
#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
#define mfilemeta_init(self, file) (void)((self)->mfm_notify = __NULLPTR)
#else /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
#define mfilemeta_init(self, file) (void)0
#endif /* !CONFIG_HAVE_KERNEL_FS_NOTIFY */

/* Destroy the given mfile meta-data `self' that was originally allocated & initialized for `file' */
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mfilemeta_destroy)(struct mfilemeta *self, struct mfile *file);

/* When this is defined, `mfilemeta_destroy()' can be replaced with `mfilemeta_free()',
 * even after `mfilemeta_init()'  was called,  so-long as the  mfilemeta object  hadn't
 * actually been installed into the associated file. */
#define MFILEMETA_DESTROY_MAYOMIT_AFTER_FRESH_INIT

/* Ensure that `self->mf_meta' has been allocated, which is then returned. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) struct mfilemeta *FCALL
mfile_getmeta(struct mfile *__restrict self) THROWS(E_BADALLOC);


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILEMETA_H */
