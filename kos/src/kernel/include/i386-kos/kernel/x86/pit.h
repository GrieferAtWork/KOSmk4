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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_PIT_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_PIT_H 1

#include <kernel/compiler.h>

#include <hybrid/sync/atomic-rwlock.h>

#include <hw/timer/pit.h>

DECL_BEGIN

#ifdef __CC__
#ifndef CONFIG_NO_SMP
/* Lock used to synchronize access to the PIT.
 * WARNING: When acquiring this lock, you must first disable preemption:
 * >> for (;;) {
 * >>     PREEMPTION_DISABLE();
 * >>     if (sync_trywrite(&x86_pit_lock))
 * >>         break;
 * >>     PREEMPTION_ENABLE();
 * >>     task_yield();
 * >> }
 * In single-core mode, it is sufficient to only disable preemption. */
DATDEF struct atomic_rwlock x86_pit_lock;
#endif /* !CONFIG_NO_SMP */
#endif /* __CC__ */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_PIT_H */
