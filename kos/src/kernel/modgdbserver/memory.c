/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODGDBSERVER_MEMORY_C
#define GUARD_MODGDBSERVER_MEMORY_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>
#include <kernel/except.h>

#include <sched/task.h>
#include <kernel/vm.h>

#include "gdb.h"

DECL_BEGIN

/* Read/Write memory
 * WARNING: `GDB_WriteMemory()' and `GDB_VM_WriteMemory()' may modify the contents of the given `buf'! 
 * @return: 0 : The copy operation completed without any problems.
 * @return: * : The number of bytes that could not be transfered.
 *              The affected memory ranges are:
 *               - `addr + num_bytes - return ... addr + num_bytes - 1'
 *               - `buf + num_bytes - return ... buf + num_bytes - 1' */
INTERN NONNULL((1, 3)) size_t
NOTHROW(FCALL GDB_ReadMemory)(struct task *__restrict thread,
                              vm_virt_t addr, void *buf, size_t num_bytes) {
	size_t result;
	if (ADDR_IS_KERNEL(addr))
		result = GDB_VM_ReadMemory(&vm_kernel, addr, buf, num_bytes);
	else {
		REF struct vm *effective_vm;
		effective_vm = task_getvm(thread);
		result = GDB_VM_ReadMemory(effective_vm, addr, buf, num_bytes);
		decref_unlikely(effective_vm);
	}
	return result;
}

INTERN NONNULL((1, 3)) size_t
NOTHROW(FCALL GDB_WriteMemory)(struct task *__restrict thread,
                               vm_virt_t addr, void *buf, size_t num_bytes) {
	size_t result;
	if (ADDR_IS_KERNEL(addr))
		result = GDB_VM_WriteMemory(&vm_kernel, addr, buf, num_bytes);
	else {
		REF struct vm *effective_vm;
		effective_vm = task_getvm(thread);
		result = GDB_VM_WriteMemory(effective_vm, addr, buf, num_bytes);
		decref_unlikely(effective_vm);
	}
	return result;
}

INTERN NONNULL((1, 3)) size_t
NOTHROW(FCALL GDB_ReadMemoryWithoutSwBreak)(struct task *__restrict thread,
                                            vm_virt_t addr, void *buf, size_t num_bytes) {
	size_t result;
	if (ADDR_IS_KERNEL(addr))
		result = GDB_VM_ReadMemoryWithoutSwBreak(&vm_kernel, addr, buf, num_bytes);
	else {
		REF struct vm *effective_vm;
		effective_vm = task_getvm(thread);
		result = GDB_VM_ReadMemoryWithoutSwBreak(effective_vm, addr, buf, num_bytes);
		decref_unlikely(effective_vm);
	}
	return result;
}

INTERN NONNULL((1, 3)) size_t
NOTHROW(FCALL GDB_WriteMemoryWithoutSwBreak)(struct task *__restrict thread,
                                             vm_virt_t addr, void const *buf, size_t num_bytes) {
	size_t result;
	if (ADDR_IS_KERNEL(addr))
		result = GDB_VM_WriteMemoryWithoutSwBreak(&vm_kernel, addr, buf, num_bytes);
	else {
		REF struct vm *effective_vm;
		effective_vm = task_getvm(thread);
		result = GDB_VM_WriteMemoryWithoutSwBreak(effective_vm, addr, buf, num_bytes);
		decref_unlikely(effective_vm);
	}
	return result;
}

INTERN NONNULL((1, 3)) size_t
NOTHROW(FCALL GDB_VM_ReadMemory)(struct vm *__restrict effective_vm,
                                 vm_virt_t addr, void *buf, size_t num_bytes) {
	size_t result;
	result = GDB_VM_ReadMemoryWithoutSwBreak(effective_vm, addr, buf, num_bytes);
	GDB_ExcludeSwBreak(effective_vm, addr, buf, num_bytes - __builtin_expect(result, 0));
	return result;
}

INTERN NONNULL((1, 3)) size_t
NOTHROW(FCALL GDB_VM_WriteMemory)(struct vm *__restrict effective_vm,
                                  vm_virt_t addr, void *buf, size_t num_bytes) {
	size_t result;
	GDB_IncludeSwBreak(effective_vm, addr, buf, num_bytes);
	result = GDB_VM_WriteMemoryWithoutSwBreak(effective_vm, addr, buf, num_bytes);
	return result;
}

INTERN NONNULL((1, 3)) size_t
NOTHROW(FCALL GDB_VM_ReadMemoryWithoutSwBreak)(struct vm *__restrict effective_vm,
                                               vm_virt_t addr, void *buf, size_t num_bytes) {
	size_t result;
	result = vm_read_nopf(buf, effective_vm, (void const *)addr, num_bytes);
	if (result) {
		TRY {
			/* TODO: vm_read() may invoke RPC callbacks, which may in
			 *       turn throw exceptions such as `E_EXIT_THREAD' */
			vm_read(buf, effective_vm, (void const *)addr, num_bytes, true);
			result = 0;
		} EXCEPT {
		}
	}
	return result;
}

INTERN NONNULL((1, 3)) size_t
NOTHROW(FCALL GDB_VM_WriteMemoryWithoutSwBreak)(struct vm *__restrict effective_vm,
                                                vm_virt_t addr, void const *buf, size_t num_bytes) {
	size_t result;
	result = vm_write_nopf(effective_vm, (void *)addr, buf, num_bytes);
	if (result) {
		TRY {
			/* TODO: vm_write() may invoke RPC callbacks, which may in
			 *       turn throw exceptions such as `E_EXIT_THREAD' */
			vm_write(effective_vm, (void *)addr, buf, num_bytes, true);
			result = 0;
		} EXCEPT {
		}
	}
	return result;
}


DECL_END

#endif /* !GUARD_MODGDBSERVER_MEMORY_C */
