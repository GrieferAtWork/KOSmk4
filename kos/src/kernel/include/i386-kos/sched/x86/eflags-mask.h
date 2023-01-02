/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_X86_EFLAGS_MASK_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_X86_EFLAGS_MASK_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/atomic64.h>

#ifdef __CC__
DECL_BEGIN

/* Mask/Flag pair used to modify eflags when calling into user-space:
 *  - raise(): A user-space posix signal handler is invoked
 *  - THROW(): A user-space exception handler (s.a. `set_exception_handler()') is called
 * This  descriptor  is mainly  used  to ensure  SysV  ABI compliance  when it
 * comes  to  clearing  the #DF  flag  before calling  a  user-space function,
 * which is  doubly  important  when  we call  an  exception  handler  as  the
 * result  of  user-space  invoking  an  exception-enabled  system-call, which
 * is done by setting EFLAGS.DF=1  before triggering the system call,  meaning
 * that this right here is also used to ensure that when the exception handler
 * calls  more system calls, those won't be triggered with exceptions enabled.
 * This mask/flag pair can be modified by:
 *  - Passing a `user_eflags_mask=mask,flag' kernel commandline option
 *  - Reading/writing to/from `/proc/sys/x86/user_eflags_mask'
 * NOTE: The later only allows for bits  to be changed that are  masked
 *       by `cred_allow_eflags_modify_mask()' for the thread attempting
 *       to perform the modification. */
union x86_user_eflags_mask_union {
	struct {
		uint32_t uem_mask; /* Set of bits masked */
		uint32_t uem_flag; /* Set of bits set */
	};
	uint64_t uem_word;
};

DATDEF atomic64_t x86_user_eflags_mask;

/* Same as `x86_user_eflags_mask', but used during exec()
 * May be set by:
 *  - Passing a `exec_eflags_mask=mask,flag' kernel commandline option
 *  - Reading/writing to/from `/proc/sys/x86/exec_eflags_mask'
 *  - Reading/writing to/from `/proc/sys/x86/keepiopl/exec' */
DATDEF atomic64_t x86_exec_eflags_mask;

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_X86_EFLAGS_MASK_H */
