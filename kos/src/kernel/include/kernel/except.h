/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
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

#include <bits/crt/format-printer.h>
#include <kos/except.h>

#ifdef __CC__
DECL_BEGIN

/* Exception informations for the calling thread. */
DATDEF ATTR_PERTASK struct exception_info this_exception_info;
#define THIS_EXCEPTION_INFO PERTASK(this_exception_info)

/* Struct field aliases (for improving binary compatibility when struct layouts change) */
DATDEF ATTR_PERTASK struct exception_data this_exception_data; /* ALIAS:this_exception_info.ei_data */
#define THIS_EXCEPTION_DATA PERTASK(this_exception_data)

DATDEF ATTR_PERTASK except_register_state_t this_exception_state; /* ALIAS:this_exception_info.ei_state */
#define THIS_EXCEPTION_STATE PERTASK(this_exception_state)

DATDEF ATTR_PERTASK except_code_t this_exception_code;                 /* ALIAS:this_exception_info.ei_code */
DATDEF ATTR_PERTASK except_class_t this_exception_class;               /* ALIAS:this_exception_info.ei_class */
DATDEF ATTR_PERTASK except_subclass_t this_exception_subclass;         /* ALIAS:this_exception_info.ei_subclass */
DATDEF ATTR_PERTASK uint8_t this_exception_flags;                      /* ALIAS:this_exception_info.ei_flags */
DATDEF ATTR_PERTASK union exception_data_pointers this_exception_args; /* ALIAS:this_exception_info.ei_data.e_args */
DATDEF ATTR_PERTASK void const *this_exception_faultaddr;              /* ALIAS:this_exception_info.ei_data.e_faultaddr */
#if EXCEPT_BACKTRACE_SIZE != 0
DATDEF ATTR_PERTASK void const *this_exception_trace[EXCEPT_BACKTRACE_SIZE]; /* ALIAS:this_exception_trace */
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */

/* Dump the current exception to printk(), using the target prefixed by `reason' */
FUNDEF void NOTHROW(VCALL except_printf)(char const *__restrict reason, ...);
FUNDEF void NOTHROW(KCALL except_vprintf)(char const *__restrict reason, __builtin_va_list args);
/* Print information about the current exception into `printer' */
FUNDEF ssize_t NOTHROW(KCALL except_print_into)(__pformatprinter printer, void *arg);

#ifndef __errno_t_defined
#define __errno_t_defined
typedef __errno_t errno_t;
#endif /* !errno_t_defined */

/* Ensure that  the  1-bits of  `input'  can  entirely be  masked  by  `allowed'
 * If this isn't the case, throw an `E_INVALID_ARGUMENT_UNKNOWN_FLAG' exception.
 * @param: context: One of `E_INVALID_ARGUMENT_CONTEXT_*' */
#define VALIDATE_FLAGSET(input, allowed, context)                                \
	(unlikely((input) & ~(allowed))                                              \
	 ? THROW(E_INVALID_ARGUMENT_UNKNOWN_FLAG, context, input, ~(allowed) /*,0*/) \
	 : (void)0)

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_EXCEPT_H */
