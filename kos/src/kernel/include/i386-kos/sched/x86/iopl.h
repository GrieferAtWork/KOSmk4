/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_X86_IOPL_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_X86_IOPL_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

DECL_BEGIN

#ifdef __CC__

/* When true, iopl() is kept after fork() (w/o CLONE_THREAD) */
DATDEF bool x86_iopl_keep_after_fork;

/* When true, iopl() is kept after clone() (w/ CLONE_THREAD) */
DATDEF bool x86_iopl_keep_after_clone;

struct task;

/* Get/Set the iopl() value of the given thread.
 * @return: * : All functions return the iopl() active prior to the call being made. */
FUNDEF unsigned int KCALL
x86_getiopl(struct task *__restrict thread)
		THROWS(E_WOULDBLOCK);
FUNDEF unsigned int KCALL
x86_setiopl(struct task *__restrict thread,
            unsigned int new_iopl,
            bool check_creds DFL(true))
		THROWS(E_WOULDBLOCK, E_INSUFFICIENT_RIGHTS);

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_X86_IOPL_H */
