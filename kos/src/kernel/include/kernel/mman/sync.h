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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_SYNC_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_SYNC_H 1

#include <kernel/compiler.h>

#include <kernel/paging.h>
#include <kernel/types.h>

#ifdef __CC__
DECL_BEGIN

struct mman;

/* High-level page directory syncing functions. */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL mman_sync_p)(struct mman *__restrict self, PAGEDIR_PAGEALIGNED UNCHECKED void *addr, PAGEDIR_PAGEALIGNED size_t num_bytes);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL mman_syncone_p)(struct mman *__restrict self, PAGEDIR_PAGEALIGNED UNCHECKED void *addr);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL mman_syncall_p)(struct mman *__restrict self);

#ifndef CONFIG_NO_SMP
/* Same as `mman_sync_p(THIS_MMAN, ...)' (The sync is done on every CPU that uses the caller's mman) */
FUNDEF NOBLOCK void NOTHROW(FCALL mman_sync)(PAGEDIR_PAGEALIGNED UNCHECKED void *addr, PAGEDIR_PAGEALIGNED size_t num_bytes);
FUNDEF NOBLOCK void NOTHROW(FCALL mman_syncone)(PAGEDIR_PAGEALIGNED UNCHECKED void *addr);
FUNDEF NOBLOCK void NOTHROW(FCALL mman_syncall)(void);

/* Same as `mman_sync_p(&mman_kernel, ...)' (The sync is performed on every CPU, for any mman) */
FUNDEF NOBLOCK void NOTHROW(FCALL mman_supersync)(PAGEDIR_PAGEALIGNED UNCHECKED void *addr, PAGEDIR_PAGEALIGNED size_t num_bytes);
FUNDEF NOBLOCK void NOTHROW(FCALL mman_supersyncone)(PAGEDIR_PAGEALIGNED UNCHECKED void *addr);
FUNDEF NOBLOCK void NOTHROW(FCALL mman_supersyncall)(void);
#else /* !CONFIG_NO_SMP */
#define mman_sync(addr, num_bytes) pagedir_sync(addr, num_bytes)
#define mman_syncone(addr)         pagedir_syncone(addr)
FUNDEF NOBLOCK void NOTHROW(FCALL mman_syncall)(void);
#define mman_supersync(addr, num_bytes) pagedir_sync(addr, num_bytes)
#define mman_supersyncone(addr)         pagedir_syncone(addr)
#define mman_supersyncall()             pagedir_syncall()
#endif /* CONFIG_NO_SMP */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_SYNC_H */
