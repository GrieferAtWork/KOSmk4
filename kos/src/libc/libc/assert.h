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
#ifndef GUARD_LIBC_LIBC_ASSERT_H
#define GUARD_LIBC_LIBC_ASSERT_H 1
#define _KOS_KERNEL_SOURCE 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <kos/kernel/cpu-state.h>
#include <kos/types.h>

DECL_BEGIN

#ifndef FCALL
#define FCALL __FCALL
#endif /* !FCALL */

struct assert_args {
	va_list          aa_args;    /* Variable arguments for `aa_format' */
	struct kcpustate aa_state;   /* CPU state pointing after the call to an assertion handler function */
	char const      *aa_expr;    /* [0..1] Faulting expression */
	char const      *aa_file;    /* [0..1] Faulting file name */
	unsigned int     aa_line;    /* Faulting line number */
	char const      *aa_func;    /* [0..1] Faulting function name */
	char const      *aa_format;  /* [0..1] Fault message printf-format */
};

/* Core undefined-behavior handlers. (called from assembly) */
INTDEF ATTR_NOINLINE ATTR_NORETURN void FCALL libc_assertion_failure_core(struct assert_args *__restrict args);
INTDEF ATTR_NOINLINE ATTR_NORETURN void FCALL libc_stack_failure_core(struct kcpustate *__restrict state);
INTDEF ATTR_NOINLINE ATTR_NORETURN void FCALL libc_abort_failure_core(struct kcpustate *__restrict state);
#ifdef __KERNEL__
INTDEF ATTR_NOINLINE struct kcpustate *FCALL libc_assertion_check_core(struct assert_args *__restrict args);
#endif /* __KERNEL__ */


DATDEF uintptr_t __stack_chk_guard;
FUNDEF ATTR_NORETURN void __stack_chk_fail(void);
INTDEF ATTR_NORETURN void __stack_chk_fail_local(void);


DECL_END

#endif /* !GUARD_LIBC_LIBC_ASSERT_H */
