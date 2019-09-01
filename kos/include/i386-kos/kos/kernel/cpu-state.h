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
#ifndef _I386_KOS_KOS_KERNEL_CPU_STATE_H
#define _I386_KOS_KOS_KERNEL_CPU_STATE_H 1

#include <hybrid/host.h>


/* Define all cpu state structures used by the system.
 * On i386/x86_64, these are:
 *  - ucpustate: UserCpuState
 *               Used mainly by userspace and contains all
 *               general-purpose, and segment registers
 *               The address of the state has no relevance
 *  - lcpustate: LittleCpuState
 *               Kept as small as possible, this cpu state
 *               can be used to describe the minimal register
 *               state required by SysV to allow C code to
 *               function without errors.
 *  - kcpustate: KernelCpuState
 *               A small, but complete cpu state designed for
 *               unwinding the stack within the same privilege
 *               level, however cannot be used for unwinding
 *               from kernel- to user-space.
 *  - icpustate: InterruptCpuState
 *               Used for describing a full cpu state meant to
 *               be used for returning from an interrupt.
 *               This state is special in that it doesn't contain
 *               an entry for the %gs register (unless when returning
 *               to vm86), and that it contains an inlined IRET tail,
 *               meaning that the %esp value loaded by this state
 *               depends on the state's address.
 *  - scpustate: SchedulerCpuState
 *               Very similar to `icpustate', but used by the
 *               scheduler. The only difference to `icpustate' is
 *               that this state also contains a field for `%gs'
 *  - fcpustate: FullCpuState
 *               A full cpu state, contains every regular not related
 *               to floating point handling, including values to-be
 *               loaded into descriptor caches and what-not.
 */

#ifdef __x86_64__
#include "cpu-state64.h"
#else /* __x86_64__ */
#include "cpu-state32.h"
#endif /* !__x86_64__ */

#endif /* !_I386_KOS_KOS_KERNEL_CPU_STATE_H */
