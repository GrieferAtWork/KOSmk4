/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_VM_HANDLE_C
#define GUARD_KERNEL_SRC_MEMORY_VM_VM_HANDLE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/aio.h>
#include <kernel/except.h>
#include <kernel/handle-proto.h>
#include <kernel/handle.h>
#include <kernel/user.h>
#include <kernel/vm.h>

#include <kos/except-inval.h>
#include <kos/hop.h>

#include <assert.h>
#include <string.h>

DECL_BEGIN

/* VM HANDLE OPERATIONS */
DEFINE_HANDLE_REFCNT_FUNCTIONS(vm, struct vm)

INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_vm_pread(struct vm *__restrict self,
                USER CHECKED void *dst, size_t num_bytes,
                pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	vm_read(self, (void *)(uintptr_t)addr, dst, num_bytes, false);
	return num_bytes;
}

INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_vm_pwrite(struct vm *__restrict self,
                 USER CHECKED void const *src, size_t num_bytes,
                 pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	vm_write(self, (void *)(uintptr_t)addr, src, num_bytes, false);
	return num_bytes;
}

DEFINE_HANDLE_PREADV_FROM_PREAD(vm, struct vm)
DEFINE_HANDLE_PWRITEV_FROM_PWRITE(vm, struct vm)
DEFINE_HANDLE_APREAD_FROM_PREAD(vm, struct vm)
DEFINE_HANDLE_APWRITE_FROM_PWRITE(vm, struct vm)
DEFINE_HANDLE_APREADV_FROM_PREADV(vm, struct vm)
DEFINE_HANDLE_APWRITEV_FROM_PWRITEV(vm, struct vm)

//INTERN NONNULL((1)) pos_t KCALL /* TODO: Use vm_prefault()??? */
//handle_vm_allocate(struct vm *__restrict self,
//                   fallocate_mode_t mode,
//                   pos_t start, pos_t length) THROWS(...) {
//}

INTERN NONNULL((1)) void KCALL
handle_vm_sync(struct vm *__restrict self) THROWS(...) {
	vm_paged_syncmem(self);
}
DEFINE_INTERN_ALIAS(handle_vm_datasync, handle_vm_sync);

INTERN NONNULL((1)) syscall_slong_t KCALL
handle_vm_hop(struct vm *__restrict self, syscall_ulong_t cmd,
              USER UNCHECKED void *arg, iomode_t mode)
		THROWS(...) {
	(void)self;
	(void)arg;
	(void)mode;
	COMPILER_IMPURE();
	switch (cmd) {

	/* TODO */

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND,
		      cmd);
		break;
	}
	return 0;
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_VM_HANDLE_C */
