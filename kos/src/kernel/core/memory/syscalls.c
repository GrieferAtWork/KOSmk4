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
#ifndef GUARD_KERNEL_SRC_MEMORY_SYSCALLS_C
#define GUARD_KERNEL_SRC_MEMORY_SYSCALLS_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <kernel/vm.h>
#include <sched/cred.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <kos/except/reason/inval.h>
#include <kos/exec/elf.h>
#include <sys/mman.h>

#include <assert.h>
#include <elf.h>
#include <errno.h>
#include <string.h>

/* TODO: Completely re-write this file for use with the new mman! */

DECL_BEGIN

STATIC_ASSERT(PROT_NONE   == VM_PROT_NONE);
STATIC_ASSERT(PROT_EXEC   == VM_PROT_EXEC);
STATIC_ASSERT(PROT_WRITE  == VM_PROT_WRITE);
STATIC_ASSERT(PROT_READ   == VM_PROT_READ);
STATIC_ASSERT(PROT_SHARED == VM_PROT_SHARED);
#ifdef VM_PROT_LOOSE
STATIC_ASSERT(PROT_LOOSE  == VM_PROT_LOOSE);
#endif /* VM_PROT_LOOSE */

LOCAL void KCALL
getdatablock_from_handle(unsigned int fd,
                         struct handle_mmap_info *__restrict info) {
	struct handle hnd = handle_lookup(fd);
	TRY {
#ifndef NDEBUG
		info->hmi_file = NULL;
#endif /* !NDEBUG */
		info->hmi_minaddr = (pos_t)0;
		info->hmi_maxaddr = (pos_t)-1;
		info->hmi_fspath  = NULL;
		info->hmi_fsname  = NULL;
		handle_mmap(hnd, info);
#ifndef NDEBUG
		assert(info->hmi_file != NULL);
#endif /* !NDEBUG */
	} EXCEPT {
		decref(hnd);
		RETHROW();
	}
	decref(hnd);
}




/************************************************************************/
/* mremap()                                                             */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_MREMAP
//TODO:FUNDEF void *(__ARCH_SYSCALLCC sys_mremap)(void *old_address, size_t old_size, size_t new_size, syscall_ulong_t flags, void *new_address) THROWS(...);
#endif /* __ARCH_WANT_SYSCALL_MREMAP */

DECL_END

#ifndef __INTELLISENSE__
#ifdef __ARCH_WANT_SYSCALL_MAPLIBRARY
#include "syscalls-maplibrary-impl.c.inl"
#endif /* __ARCH_WANT_SYSCALL_MAPLIBRARY */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_MAPLIBRARY
#define DEFINE_COMPAT_MAPLIBRARY 1
#include "syscalls-maplibrary-impl.c.inl"
#endif /* __ARCH_WANT_COMPAT_SYSCALL_MAPLIBRARY */

#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_KERNEL_SRC_MEMORY_SYSCALLS_C */
