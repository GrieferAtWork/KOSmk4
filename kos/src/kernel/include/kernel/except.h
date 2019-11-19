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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_EXCEPT_H
#define GUARD_KERNEL_INCLUDE_KERNEL_EXCEPT_H 1

#include <kernel/compiler.h>

#include <kernel/arch/except.h>
#include <kernel/types.h>
#include <sched/pertask.h>

#include <bits/format-printer.h>
#include <bits/types.h>
#include <kos/except.h>

DECL_BEGIN

#ifdef __CC__

/* Exception informations for the calling thread. */
DATDEF ATTR_PERTASK struct exception_info this_exception_info;
#define THIS_EXCEPTION_INFO PERTASK(this_exception_info)

/* Struct field aliases (for improving binary compatibility when struct layouts change) */
DATDEF ATTR_PERTASK struct exception_data this_exception_data; /* ALIAS:this_exception_info.ei_data */
#define THIS_EXCEPTION_DATA PERTASK(this_exception_data)

DATDEF ATTR_PERTASK error_register_state_t this_exception_state; /* ALIAS:this_exception_info.ei_state */
#define THIS_EXCEPTION_STATE PERTASK(this_exception_state)

DATDEF ATTR_PERTASK error_code_t this_exception_code;                             /* ALIAS:this_exception_info.ei_code */
DATDEF ATTR_PERTASK error_class_t this_exception_class;                           /* ALIAS:this_exception_info.ei_class */
DATDEF ATTR_PERTASK error_subclass_t this_exception_subclass;                     /* ALIAS:this_exception_info.ei_subclass */
DATDEF ATTR_PERTASK __uintptr_t this_exception_pointers[EXCEPTION_DATA_POINTERS]; /* ALIAS:this_exception_info.ei_data.e_pointers */
DATDEF ATTR_PERTASK __uintptr_t this_exception_flags;                             /* ALIAS:this_exception_info.ei_flags */
DATDEF ATTR_PERTASK void *this_exception_faultaddr;                               /* ALIAS:this_exception_info.ei_data.e_faultaddr */
#if EXCEPT_BACKTRACE_SIZE != 0
DATDEF ATTR_PERTASK void *this_exception_trace[EXCEPT_BACKTRACE_SIZE]; /* ALIAS:this_exception_trace */
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */

#ifndef __INTELLISENSE__
#undef error_info
#undef error_data
#undef error_active
#undef error_code
#undef error_class
#undef error_subclass
#define error_info()     (&THIS_EXCEPTION_INFO)
#define error_data()     (&THIS_EXCEPTION_DATA)
#define error_active()   (PERTASK_GET(this_exception_code) != 0)
#define error_code()     PERTASK_GET(this_exception_code)
#define error_class()    PERTASK_GET(this_exception_class)
#define error_subclass() PERTASK_GET(this_exception_subclass)
#endif /* !__INTELLISENSE__ */

/* Dump the current exception to printk(), using the target prefixed by `reason' */
FUNDEF void NOTHROW(VCALL error_printf)(char const *__restrict reason, ...);
FUNDEF void NOTHROW(KCALL error_vprintf)(char const *__restrict reason, __builtin_va_list args);
/* Print information about the current exception into `printer' */
FUNDEF ssize_t NOTHROW(KCALL error_print_into)(__pformatprinter printer, void *arg);

#ifndef __errno_t_defined
#define __errno_t_defined 1
typedef __errno_t errno_t;
#endif /* !errno_t_defined */

/* Ensure that the 1-bits of `input' can entirely be masked by `allowed'
 * If this isn't the case, throw an `E_INVALID_ARGUMENT_UNKNOWN_FLAG' exception.
 * @param: context: One of `E_INVALID_ARGUMENT_CONTEXT_*' */
#define VALIDATE_FLAGSET(input, allowed, context)                                \
	(unlikely((input) & ~(allowed))                                              \
	 ? THROW(E_INVALID_ARGUMENT_UNKNOWN_FLAG, context, input, ~(allowed) /*,0*/) \
	 : (void)0)

/* Enable nested exception handling, such that the
 * original exception is always restored, even when
 * exception handling code caused another exception,
 * when that exception has already been handled:
 * >> TRY {
 * >>     ...
 * >> } EXCEPT {
 * >>     EXCEPT_ALLOW_NESTING;
 * >>     TRY {
 * >>         ...         // Some other code that can cause further excpetion
 * >>     } EXCEPT {
 * >>     }
 * >>     RETHROW();
 * >>     // The original exception (from the first TRY-block) will be restored here
 * >> }
 */
#define EXCEPT_ALLOW_NESTING  \
	(void)0 /* TODO: Copy the current exception context into a local variable w/ RAII used to restore it once the scope is left. */

#endif /* __CC__ */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_EXCEPT_H */
