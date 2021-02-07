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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_FSUPER_LOCKOP_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_FSUPER_LOCKOP_H 1

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_FS
#include <fs/node.h>
#else /* !CONFIG_USE_NEW_FS */
#include <kernel/types.h>

#include <hybrid/sequence/list.h>

#ifdef __CC__
DECL_BEGIN

struct fsuper;
struct fsuper_lockop;
struct fsuper_postlockop;

typedef NOBLOCK NONNULL((1, 2)) void
/*NOTHROW*/ (FCALL *fsuper_postlockop_callback_t)(struct fsuper_postlockop *__restrict self,
                                                  struct fsuper *__restrict part);

struct fsuper_postlockop {
	SLIST_ENTRY(fsuper_postlockop) fsplo_link; /* [0..1] Next post-lock operation. */
	fsuper_postlockop_callback_t   fsplo_func; /* [1..1][const] Callback to invoke. */
};


/* Callback prototype for fs-superblock pending locked operations.
 * @return: NULL: Completed.
 * @return: * :   A descriptor for an operation to perform
 *                after the fsuper-lock has been released. */
typedef NOBLOCK NONNULL((1, 2)) struct fsuper_postlockop *
/*NOTHROW*/ (FCALL *fsuper_lockop_callback_t)(struct fsuper_lockop *__restrict self,
                                              struct fsuper *__restrict part);

struct fsuper_lockop {
	SLIST_ENTRY(fsuper_lockop) fslo_link; /* [0..1] Next lock operation. */
	fsuper_lockop_callback_t   fslo_func; /* [1..1][const] Operation to perform. */
};

DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_FSUPER_LOCKOP_H */
