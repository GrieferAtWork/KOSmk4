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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_LIBC_EXCEPT_H
#define GUARD_LIBC_LIBC_EXCEPT_H 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <kos/except.h>
#include <kos/kernel/cpu-state.h>
#include <sys/syslog.h>

#include <libunwind/except.h>

#ifndef __KERNEL__
#include <kos/except-handler.h> /* __EXCEPT_HANDLER_CC */
#endif /* !__KERNEL__ */


#ifdef __CC__
#define SECTION_EXCEPT_TEXT    ATTR_SECTION(".text.crt.except")
#define SECTION_EXCEPT_DATA    ATTR_SECTION(".data.crt.except")
#define SECTION_EXCEPT_BSS     ATTR_SECTION(".bss.crt.except")
#define SECTION_EXCEPT_RODATA  ATTR_SECTION(".rodata.crt.except")
#define SECTION_EXCEPT_STRING  ATTR_SECTION(".rodata.crt.except")
#else /* __CC__ */
#define SECTION_EXCEPT_TEXT    .text.crt.except
#define SECTION_EXCEPT_DATA    .data.crt.except
#define SECTION_EXCEPT_BSS     .bss.crt.except
#define SECTION_EXCEPT_RODATA  .rodata.crt.except
#define SECTION_EXCEPT_STRING  .rodata.crt.except
#endif /* !__CC__ */


DECL_BEGIN

#ifdef __CC__

struct exception_data;
struct exception_info;

/* Returns non-zero if there is an active exception. */
INTDEF WUNUSED ATTR_CONST ATTR_RETNONNULL struct exception_info *NOTHROW_NCX(LIBCCALL libc_error_info)(void);
INTDEF WUNUSED ATTR_CONST ATTR_RETNONNULL struct exception_data *NOTHROW_NCX(LIBCCALL libc_error_data)(void);
INTDEF WUNUSED ATTR_CONST ATTR_RETNONNULL error_register_state_t *NOTHROW_NCX(LIBCCALL libc_error_register_state)(void);
INTDEF WUNUSED ATTR_PURE error_code_t NOTHROW_NCX(LIBCCALL libc_error_code)(void);
INTDEF WUNUSED ATTR_PURE bool NOTHROW_NCX(LIBCCALL libc_error_active)(void);
INTDEF WUNUSED ATTR_PURE error_class_t NOTHROW_NCX(LIBCCALL libc_error_class)(void);
INTDEF WUNUSED ATTR_PURE error_subclass_t NOTHROW_NCX(LIBCCALL libc_error_subclass)(void);

/* Functions implemented in assembly. */
INTDEF ATTR_NORETURN void NOTHROW_NCX(LIBCCALL libc_error_throw_current)(void);
INTDEF ATTR_NORETURN void NOTHROW_NCX(LIBCCALL libc_error_rethrow)(void);
INTDEF ATTR_NORETURN void (__ERROR_THROW_CC libc_error_throw)(error_code_t code);
INTDEF ATTR_NORETURN void (__ERROR_THROWN_CC libc_error_thrown)(error_code_t code, unsigned int argc, ...);

/* Unwind the stack for a KERNKOS exception. */
INTDEF WUNUSED error_register_state_t *
NOTHROW_NCX(__ERROR_UNWIND_CC libc_error_unwind)(error_register_state_t *__restrict state);

#ifndef __KERNEL__
INTDEF NONNULL((1, 2)) error_register_state_t *NOTHROW_NCX(__ERROR_UNWIND_CC libc_Unwind_RaiseException_impl)(error_register_state_t *__restrict state, struct _Unwind_Exception *exception_object);
INTDEF WUNUSED NONNULL((1, 2)) error_register_state_t *NOTHROW_NCX(__ERROR_UNWIND_CC libc_Unwind_Resume_impl)(error_register_state_t *__restrict state, struct _Unwind_Exception *exception_object);
INTDEF NONNULL((1, 2)) error_register_state_t *NOTHROW_NCX(__ERROR_UNWIND_CC libc_Unwind_Resume_or_Rethrow_impl)(error_register_state_t *__restrict state, struct _Unwind_Exception *__restrict exception_object);
INTDEF NONNULL((1, 2, 3)) error_register_state_t *NOTHROW_NCX(__ERROR_UNWIND_CC libc_Unwind_ForcedUnwind_impl)(error_register_state_t *__restrict state, struct _Unwind_Exception *__restrict exception_object, _Unwind_Stop_Fn stop, void *stop_arg);
INTDEF NONNULL((1, 2)) _Unwind_Reason_Code __ERROR_UNWIND_CC libc_Unwind_Backtrace_impl(error_register_state_t *__restrict state, _Unwind_Trace_Fn func, void *arg);

INTDEF NONNULL((1)) _Unwind_Reason_Code NOTHROW_NCX(LIBCCALL libc_Unwind_Resume_or_Rethrow)(struct _Unwind_Exception *__restrict exception_object);
INTDEF NONNULL((1, 2)) _Unwind_Reason_Code NOTHROW_NCX(LIBCCALL libc_Unwind_ForcedUnwind)(struct _Unwind_Exception *__restrict exception_object, _Unwind_Stop_Fn stop, void *stop_arg);
INTDEF NONNULL((1)) _Unwind_Reason_Code NOTHROW_NCX(LIBCCALL libc_Unwind_Backtrace)(_Unwind_Trace_Fn func, void *arg);

INTDEF WUNUSED ATTR_PURE NONNULL((1)) _Unwind_Word NOTHROW_NCX(LIBCCALL libc_Unwind_GetCFA)(struct _Unwind_Context const *__restrict self);
INTDEF WUNUSED ATTR_PURE NONNULL((1)) _Unwind_Ptr NOTHROW_NCX(LIBCCALL libc_Unwind_GetDataRelBase)(struct _Unwind_Context const *__restrict self);
INTDEF WUNUSED ATTR_PURE NONNULL((1)) _Unwind_Ptr NOTHROW_NCX(LIBCCALL libc_Unwind_GetTextRelBase)(struct _Unwind_Context const *__restrict self);
INTDEF WUNUSED ATTR_PURE void *NOTHROW_NCX(LIBCCALL libc_Unwind_FindEnclosingFunction)(void *pc);

/* Kernel-level exception handling (mode #2/#3 and mode #4). */
INTDEF error_register_state_t *__EXCEPT_HANDLER_CC libc_except_handler3_impl(error_register_state_t *__restrict state, struct exception_data *__restrict error);
INTDEF error_register_state_t *__EXCEPT_HANDLER_CC libc_except_handler4_impl(error_register_state_t *__restrict state, struct exception_data *__restrict error);
INTDEF ATTR_NORETURN void __EXCEPT_HANDLER_CC libc_except_handler3(error_register_state_t *__restrict state, struct exception_data *__restrict error);
INTDEF ATTR_NORETURN void __EXCEPT_HANDLER_CC libc_except_handler4(error_register_state_t *__restrict state, struct exception_data *__restrict error);

#define EXCEPT_INITIALIZER_KERNEL_EXCEPTION_HANDLER()                                           \
	do {                                                                                        \
		/* Bind the kernel-space exception handler using `sys_set_exception_handler()' */       \
		sys_set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND | EXCEPT_HANDLER_FLAG_SETHANDLER, \
		                          &libc_except_handler4, NULL);                                 \
	} __WHILE0

#endif /* !__KERNEL__ */

INTDEF NONNULL((1)) _Unwind_Reason_Code NOTHROW_NCX(LIBCCALL libc_Unwind_RaiseException)(struct _Unwind_Exception *__restrict exception_object);
INTDEF ATTR_NORETURN NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_Unwind_Resume)(struct _Unwind_Exception *__restrict exception_object);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_Unwind_DeleteException)(struct _Unwind_Exception *__restrict exception_object);
INTDEF WUNUSED ATTR_PURE NONNULL((1)) uintptr_t NOTHROW_NCX(LIBCCALL libc_Unwind_GetGR)(struct _Unwind_Context const *__restrict context, int index);
INTDEF ATTR_LEAF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_Unwind_SetGR)(struct _Unwind_Context *__restrict context, int index, uintptr_t value);
INTDEF WUNUSED ATTR_PURE NONNULL((1)) uintptr_t NOTHROW_NCX(LIBCCALL libc_Unwind_GetIP)(struct _Unwind_Context const *__restrict context);
INTDEF ATTR_LEAF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_Unwind_SetIP)(struct _Unwind_Context *__restrict context, uintptr_t value);
INTDEF WUNUSED ATTR_PURE NONNULL((1)) uintptr_t NOTHROW_NCX(LIBCCALL libc_Unwind_GetLanguageSpecificData)(struct _Unwind_Context const *__restrict context);
INTDEF WUNUSED ATTR_PURE NONNULL((1)) uintptr_t NOTHROW_NCX(LIBCCALL libc_Unwind_GetRegionStart)(struct _Unwind_Context const *__restrict context);
INTDEF WUNUSED ATTR_LEAF NONNULL((1, 2)) uintptr_t NOTHROW_NCX(LIBCCALL libc_Unwind_GetIPInfo)(struct _Unwind_Context const *__restrict context, int *__restrict ip_before_insn);

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_LIBC_LIBC_EXCEPT_H */
