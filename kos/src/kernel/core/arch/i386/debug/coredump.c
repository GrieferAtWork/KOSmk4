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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUG_COREDUMP_C
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUG_COREDUMP_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/coredump.h>
#include <kernel/except.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <sched/cred.h>
#include <sched/rpc.h>
#include <sched/signal.h>

#include <hybrid/host.h>
#include <hybrid/pointer.h>

#include <asm/cpu-flags.h>
#include <asm/registers.h>
#include <bits/os/kos/siginfo-convert.h>
#include <kos/bits/coredump.h>
#include <kos/bits/coredump32.h>
#include <kos/bits/exception_data-convert.h>
#include <kos/bits/exception_data.h>
#include <kos/bits/exception_data32.h>
#include <kos/except/reason/inval.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state-verify.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/cpu-state32.h>
#include <sys/wait.h>

#include <assert.h>
#include <malloca.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>

#include <librpc/rpc.h>
#include <libunwind/api.h>

#ifndef __INTELLISENSE__
#ifdef __ARCH_WANT_SYSCALL_COREDUMP
#define DEFINE_COREDUMP32 1
#include "coredump-impl.c.inl"
#endif /* __ARCH_WANT_SYSCALL_COREDUMP */
#ifdef __ARCH_WANT_COMPAT_SYSCALL_COREDUMP
#define DEFINE_COREDUMP64 1
#include "coredump-impl.c.inl"
#endif /* __ARCH_WANT_COMPAT_SYSCALL_COREDUMP */
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUG_COREDUMP_C */
