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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_FUTEX_SYSCALLS_C
#define GUARD_KERNEL_SRC_MEMORY_VM_FUTEX_SYSCALLS_C 1
#define _TIME64_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <kernel/vm.h>
#include <kernel/panic.h>
#include <kernel/vm/futex.h>

#include <hybrid/atomic.h>

#include <assert.h>

#include "vm-nodeapi.h"

DECL_BEGIN


DEFINE_SYSCALL6(syscall_slong_t, futex,
                USER UNCHECKED uint32_t *, uaddr,
                syscall_ulong_t, futex_op,
                uint32_t, val,
                USER UNCHECKED struct __timespec32 const *, timeout_or_val2,
                USER UNCHECKED uint32_t *, uaddr2,
                uint32_t, val3) {
	kernel_panic("TODO");
}

DEFINE_SYSCALL5(syscall_slong_t, lfutex,
                USER UNCHECKED uintptr_t *, uaddr,
                syscall_ulong_t, futex_op,
                uintptr_t, val,
                USER UNCHECKED struct timespec64 const *, timeout,
                uintptr_t, val2) {
	kernel_panic("TODO");
}

DEFINE_SYSCALL6(syscall_slong_t, lfutexlock,
                USER UNCHECKED uintptr_t *, ulockaddr,
                USER UNCHECKED uintptr_t *, uaddr,
                syscall_ulong_t, futex_op,
                uintptr_t, val,
                USER UNCHECKED struct timespec64 const *, timeout,
                uintptr_t, val2) {
	kernel_panic("TODO");
}

DEFINE_SYSCALL6(errno_t, lfutexexpr,
                USER UNCHECKED uintptr_t *, uaddr,
                USER UNCHECKED void *, base,
                USER UNCHECKED struct lfutexexpr const *, exprv,
                size_t, exprc,
                USER UNCHECKED struct timespec64 const *, timeout,
                syscall_ulong_t, timeout_flags) {
	kernel_panic("TODO");
}

DEFINE_SYSCALL6(errno_t, lfutexlockexpr,
                USER UNCHECKED uintptr_t *, ulockaddr,
                USER UNCHECKED void *, base,
                USER UNCHECKED struct lfutexexpr const *, exprv,
                size_t, exprc,
                USER UNCHECKED struct timespec64 const *, timeout,
                syscall_ulong_t, timeout_flags) {
	kernel_panic("TODO");
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_FUTEX_SYSCALLS_C */
