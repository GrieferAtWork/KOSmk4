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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_EXCEPT_HANDLER_H
#define GUARD_KERNEL_INCLUDE_SCHED_EXCEPT_HANDLER_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/arch/except-handler.h>
#include <sched/pertask.h>

#include <kos/except-handler.h>

DECL_BEGIN

/* User-space exception handler descriptor. */
#ifdef __CC__
struct user_except_handler {
	uintptr_t                     ueh_mode;    /* Handler mode (One of `EXCEPT_HANDLER_MODE_*' + set of `EXCEPT_HANDLER_FLAG_*') */
	USER CHECKED except_handler_t ueh_handler; /* [valid_if(EXCEPT_HANDLER_FLAG_SETHANDLER)] Handler entry point */
	USER CHECKED void            *ueh_stack;   /* Handler stack (or `EXCEPT_HANDLER_SP_CURRENT' when not set)
	                                            * NOTE: This pointer also doubles as the user-space sigaltstack! */
};

/* User-space exception handler mode for the current thread. */
DATDEF ATTR_PERTASK struct user_except_handler this_user_except_handler;

/* [0..1] User-space TID address used to implement functionality such as `pthread_join()'
 *        When the associated thread exits, it will:
 *        >> pid_t *addr = PERTASK_GET(this_tid_address);
 *        >> if (addr) {
 *        >>     TRY {
 *        >>         *addr = 0;
 *        >>         vm_futex_broadcast(addr);
 *        >>     } EXCEPT {
 *        >>         if (!was_thrown(E_SEGFAULT) ||
 *        >>             error_data()->e_pointers[0] != (uintptr_t)addr)
 *        >>             error_printf("...");
 *        >>     }
 *        >> }
 * When a new thread is created by clone(), the `CLONE_CHILD_CLEARTID' flag will cause
 * the given `ctid' to be used as the initial value for `this_tid_address', while the
 * `CLONE_CHILD_SETTID' flag will cause the same address to be filled with the thread's
 * TID. */
DATDEF ATTR_PERTASK USER CHECKED pid_t *this_tid_address;

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_EXCEPT_HANDLER_H */
