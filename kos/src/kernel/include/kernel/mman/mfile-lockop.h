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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILE_LOCKOP_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILE_LOCKOP_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <hybrid/sequence/list.h>

#ifdef __CC__
DECL_BEGIN

struct mman;
struct mfile_lockop;
struct mfile_postlockop;

typedef NOBLOCK NONNULL((1, 2)) void
/*NOTHROW*/ (FCALL *mfile_postlockop_callback_t)(struct mfile_postlockop *__restrict self,
                                                 struct mfile *__restrict file);

struct mfile_postlockop {
	SLIST_ENTRY(mfile_postlockop) mfplo_link; /* [lock(ATOMIC)] Next post-lock operation. */
	mfile_postlockop_callback_t   mfplo_func; /* [1..1][const] Callback to invoke. */
};


/* Callback prototype for mfile pending locked operations.
 * @return: NULL: Completed.
 * @return: * :   A descriptor for an operation to perform
 *                after the mfile-lock has been released. */
typedef NOBLOCK NONNULL((1, 2)) struct mfile_postlockop *
/*NOTHROW*/ (FCALL *mfile_lockop_callback_t)(struct mfile_lockop *__restrict self,
                                             struct mfile *__restrict file);

struct mfile_lockop {
	SLIST_ENTRY(mfile_lockop) mflo_link; /* [lock(ATOMIC)] Next lock operation. */
	mfile_lockop_callback_t   mflo_func; /* [1..1][const] Operation to perform. */
};

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILE_LOCKOP_H */
