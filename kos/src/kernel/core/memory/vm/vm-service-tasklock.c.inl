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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_VM_SERVICE_TASKLOCK_C_INL
#define GUARD_KERNEL_SRC_MEMORY_VM_VM_SERVICE_TASKLOCK_C_INL 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>
#include <kernel/vm.h>

#ifdef __INTELLISENSE__
#include "vm.c"
#endif

DECL_BEGIN


#define vm_has_pending_deltasks(self) (ATOMIC_READ((self)->v_deltasks) != NULL)

LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_clear_pending_deltasks)(struct vm *__restrict self) {
	REF struct task *iter, *next;
	iter = ATOMIC_XCH(self->v_deltasks, NULL);
	while (iter) {
		next = KEY_task_vm_dead__next(iter);
		assert(iter->t_vm == self);
		assert(iter->t_vm_tasks.ln_pself != NULL);
		LLIST_REMOVE(iter, t_vm_tasks);
		heap_free(&kernel_locked_heap, iter, iter->t_heapsz, GFP_NORMAL);
		iter = next;
	}
}

PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL vm_tasklock_trywrite)(struct vm *__restrict self) {
	if (!sync_trywrite(&self->v_tasklock))
		return false;
	vm_clear_pending_deltasks(self);
	return true;
}

PUBLIC NONNULL((1)) void KCALL
vm_tasklock_read(struct vm *__restrict self) THROWS(E_WOULDBLOCK) {
	sync_read(&self->v_tasklock);
	if unlikely(vm_has_pending_deltasks(self)) {
		if (sync_tryupgrade(&self->v_tasklock)) {
			vm_clear_pending_deltasks(self);
			sync_downgrade(self);
		}
	}
}

PUBLIC NONNULL((1)) bool KCALL
vm_tasklock_upgrade(struct vm *__restrict self) THROWS(E_WOULDBLOCK) {
	bool result;
	result = sync_upgrade(&self->v_tasklock);
	vm_clear_pending_deltasks(self);
	return result;
}

PUBLIC NONNULL((1)) void KCALL
vm_tasklock_write(struct vm *__restrict self) THROWS(E_WOULDBLOCK) {
	sync_write(&self->v_tasklock);
	vm_clear_pending_deltasks(self);
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_tasklock_endwrite)(struct vm *__restrict self) {
again:
	sync_endwrite(&self->v_tasklock);
	if unlikely(vm_has_pending_deltasks(self)) {
		if (sync_trywrite(&self->v_tasklock)) {
			vm_clear_pending_deltasks(self);
			goto again;
		}
	}
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_tasklock_endread)(struct vm *__restrict self) {
	sync_endread(&self->v_tasklock);
again_service:
	if unlikely(vm_has_pending_deltasks(self)) {
		if (sync_trywrite(&self->v_tasklock)) {
			vm_clear_pending_deltasks(self);
			sync_endwrite(&self->v_tasklock);
			goto again_service;
		}
	}
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_tasklock_end)(struct vm *__restrict self) {
	sync_end(&self->v_tasklock);
again_service:
	if unlikely(vm_has_pending_deltasks(self)) {
		if (sync_trywrite(&self->v_tasklock)) {
			vm_clear_pending_deltasks(self);
			sync_endwrite(&self->v_tasklock);
			goto again_service;
		}
	}
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_tasklock_downgrade)(struct vm *__restrict self) {
again:
	vm_clear_pending_deltasks(self);
	sync_downgrade(&self->v_tasklock);
	if unlikely(vm_has_pending_deltasks(self)) {
		if (sync_tryupgrade(&self->v_tasklock))
			goto again;
	}
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_tasklock_tryservice)(struct vm *__restrict self) {
	if (sync_trywrite(&self->v_tasklock)) {
		vm_clear_pending_deltasks(self);
		sync_endwrite(&self->v_tasklock);
	}
}


PUBLIC WUNUSED NONNULL((1)) bool
NOTHROW(KCALL vm_tasklock_read_nx)(struct vm *__restrict self) {
	bool result;
	result = sync_read_nx(&self->v_tasklock);
	if likely(result) {
		if unlikely(vm_has_pending_deltasks(self)) {
			if (sync_tryupgrade(&self->v_tasklock)) {
				vm_clear_pending_deltasks(self);
				sync_downgrade(&self->v_tasklock);
			}
		}
	}
	return result;
}

PUBLIC WUNUSED NONNULL((1)) bool
NOTHROW(KCALL vm_tasklock_write_nx)(struct vm *__restrict self) {
	bool result;
	result = sync_write_nx(&self->v_tasklock);
	if likely(result)
		vm_clear_pending_deltasks(self);
	return result;
}

PUBLIC WUNUSED NONNULL((1)) unsigned int
NOTHROW(KCALL vm_tasklock_upgrade_nx)(struct vm *__restrict self) {
	unsigned int result;
	result = sync_upgrade_nx(&self->v_tasklock);
	if likely(result != 0)
		vm_clear_pending_deltasks(self);
	return result;
}

PUBLIC NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(KCALL vm_tasklock_tryread)(struct vm *__restrict self) {
	bool result;
	result = sync_tryread(&self->v_tasklock);
	if likely(result) {
		if unlikely(vm_has_pending_deltasks(self)) {
			if (sync_tryupgrade(&self->v_tasklock)) {
				vm_clear_pending_deltasks(self);
				sync_downgrade(&self->v_tasklock);
			}
		}
	}
	return result;
}

PUBLIC NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(KCALL vm_tasklock_tryupgrade)(struct vm *__restrict self) {
	bool result;
	result = sync_tryupgrade(&self->v_tasklock);
	if likely(result)
		vm_clear_pending_deltasks(self);
	return result;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_VM_SERVICE_TASKLOCK_C_INL */
