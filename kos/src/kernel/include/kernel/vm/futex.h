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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_VM_FUTEX_H
#define GUARD_KERNEL_INCLUDE_KERNEL_VM_FUTEX_H 1

#include <kernel/compiler.h>

#include <kernel/mman/mpartmeta.h>

#define fc_tree     mpm_ftx
#define fc_dead     mpm_ftx_dead.slh_first
#define fc_rtm_vers mpm_rtm_vers
#define vmf_refcnt  mfu_refcnt
#define vmf_part    mfu_part
#define vmf_tree    mfu_mtaent
#define vmf_signal  mfu_signal
#define vmf_ndead   _mfu_dead.sle_next

#define vm_futex_alloc()                         ((struct mfutex *)kmalloc(sizeof(struct mfutex), GFP_NORMAL))
#define vm_futex_allocf(gfp_flags)               ((struct mfutex *)kmalloc(sizeof(struct mfutex), gfp_flags))
#define vm_futex_allocf_nx(gfp_flags)            ((struct mfutex *)kmalloc_nx(sizeof(struct mfutex), gfp_flags))
#define vm_futex_free(p)                         mfutex_free(p)
#define vm_futex_destroy(self)                   mfutex_destroy(self)
#define vm_futex_controller_alloc()              ((struct mpartmeta *)kmalloc(sizeof(struct mpartmeta), GFP_CALLOC))
#define vm_futex_controller_allocf(gfp_flags)    ((struct mpartmeta *)kmalloc(sizeof(struct mpartmeta), (gfp_flags) | GFP_CALLOC))
#define vm_futex_controller_allocf_nx(gfp_flags) ((struct mpartmeta *)kmalloc_nx(sizeof(struct mpartmeta), (gfp_flags) | GFP_CALLOC))
#define vm_futex_controller_free(p)              kfree(p)

/* Futex API */
#define VM_DATAPART_GETFUTEX_OUTOFRANGE                      MPART_FUTEX_OOB
#define vm_datablock_getfutex(self, offset)                  mfile_createfutex(self, offset)
#define vm_datablock_getfutex_existing(self, offset)         mfile_lookupfutex(self, offset)
#define vm_getfutex(effective_vm, addr)                      mman_createfutex(effective_vm, addr)
#define vm_getfutex_existing(effective_vm, addr)             mman_lookupfutex(effective_vm, addr)
#define vm_futex_broadcast(futex_address)                    mman_broadcastfutex(futex_address)

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_VM_FUTEX_H */
