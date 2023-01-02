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
#ifndef GUARD_LIBC_LIBC_EXCEPT_H
#define GUARD_LIBC_LIBC_EXCEPT_H 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <kos/except.h>
#include <kos/kernel/cpu-state.h>
#include <sys/syslog.h>

#include <libunwind/except.h>

#include "tls.h"

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


#undef libc_except_info
#undef libc_except_data
#undef libc_except_register_state
#undef libc_except_code
#undef libc_except_active
#undef libc_except_class
#undef libc_except_subclass
#undef except_info
#undef except_data
#undef except_register_state
#undef except_code
#undef except_active
#undef except_class
#undef except_subclass

/* Re-link direct use of error accessors to the TLS segment. */
#define libc_except_info()           (&current.pt_except)
#define libc_except_data()           (&current.pt_except.ei_data)
#define libc_except_register_state() (&current.pt_except.ei_state)
#define libc_except_code()           (current.pt_except.ei_code)
#define libc_except_active()         (current.pt_except.ei_code != EXCEPT_CODEOF(E_OK))
#define libc_except_class()          (current.pt_except.ei_class)
#define libc_except_subclass()       (current.pt_except.ei_subclass)
#define except_info()                libc_except_info()
#define except_data()                libc_except_data()
#define except_register_state()      libc_except_register_state()
#define except_code()                libc_except_code()
#define except_active()              libc_except_active()
#define except_class()               libc_except_class()
#define except_subclass()            libc_except_subclass()


DECL_BEGIN

#ifdef __CC__

struct exception_data;
struct exception_info;

/* Returns non-zero if there is an active exception. */
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED struct exception_info *NOTHROW_NCX(LIBCCALL libc_except_info)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED struct exception_data *NOTHROW_NCX(LIBCCALL libc_except_data)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED except_register_state_t *NOTHROW_NCX(LIBCCALL libc_except_register_state)(void);
INTDEF ATTR_PURE WUNUSED except_code_t NOTHROW_NCX(LIBCCALL libc_except_code)(void);
INTDEF ATTR_PURE WUNUSED bool NOTHROW_NCX(LIBCCALL libc_except_active)(void);
INTDEF ATTR_PURE WUNUSED except_class_t NOTHROW_NCX(LIBCCALL libc_except_class)(void);
INTDEF ATTR_PURE WUNUSED except_subclass_t NOTHROW_NCX(LIBCCALL libc_except_subclass)(void);

/* Functions implemented in assembly. */
INTDEF ATTR_NORETURN void NOTHROW_NCX(LIBCCALL libc_except_throw_current)(void);
INTDEF ATTR_NORETURN void NOTHROW_NCX(LIBCCALL libc_except_rethrow)(void);
INTDEF ATTR_NORETURN void (__EXCEPT_THROW_CC libc_except_throw)(except_code_t code);
INTDEF ATTR_NORETURN void (__EXCEPT_THROWN_CC libc_except_thrown)(except_code_t code, unsigned int argc, ...);

/* Unwind the stack for a KERNKOS exception. */
INTDEF WUNUSED except_register_state_t *
NOTHROW_NCX(__EXCEPT_UNWIND_CC libc_except_unwind)(except_register_state_t *__restrict state);

#ifndef __KERNEL__
INTDEF NONNULL((1, 2)) except_register_state_t *NOTHROW_NCX(__EXCEPT_UNWIND_CC libc_Unwind_RaiseException_impl)(except_register_state_t *__restrict state, struct _Unwind_Exception *exception_object);
INTDEF WUNUSED NONNULL((1, 2)) except_register_state_t *NOTHROW_NCX(__EXCEPT_UNWIND_CC libc_Unwind_Resume_impl)(except_register_state_t *__restrict state, struct _Unwind_Exception *exception_object);
INTDEF NONNULL((1, 2)) except_register_state_t *NOTHROW_NCX(__EXCEPT_UNWIND_CC libc_Unwind_Resume_or_Rethrow_impl)(except_register_state_t *__restrict state, struct _Unwind_Exception *__restrict exception_object);
INTDEF NONNULL((1, 2, 3)) except_register_state_t *NOTHROW_NCX(__EXCEPT_UNWIND_CC libc_Unwind_ForcedUnwind_impl)(except_register_state_t *__restrict state, struct _Unwind_Exception *__restrict exception_object, _Unwind_Stop_Fn stop, void *stop_arg);
INTDEF NONNULL((1, 2)) _Unwind_Reason_Code __EXCEPT_UNWIND_CC libc_Unwind_Backtrace_impl(except_register_state_t *__restrict state, _Unwind_Trace_Fn func, void *arg);

INTDEF NONNULL((1)) _Unwind_Reason_Code NOTHROW_NCX(LIBCCALL libc_Unwind_Resume_or_Rethrow)(struct _Unwind_Exception *__restrict exception_object);
INTDEF NONNULL((1, 2)) _Unwind_Reason_Code NOTHROW_NCX(LIBCCALL libc_Unwind_ForcedUnwind)(struct _Unwind_Exception *__restrict exception_object, _Unwind_Stop_Fn stop, void *stop_arg);
INTDEF NONNULL((1)) _Unwind_Reason_Code NOTHROW_NCX(LIBCCALL libc_Unwind_Backtrace)(_Unwind_Trace_Fn func, void *arg);

INTDEF ATTR_PURE WUNUSED NONNULL((1)) _Unwind_Word NOTHROW_NCX(LIBCCALL libc_Unwind_GetCFA)(struct _Unwind_Context *__restrict self); /* Only non-const for lazy initialized fields! */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) _Unwind_Ptr NOTHROW_NCX(LIBCCALL libc_Unwind_GetDataRelBase)(struct _Unwind_Context *__restrict self); /* Only non-const for lazy initialized fields! */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) _Unwind_Ptr NOTHROW_NCX(LIBCCALL libc_Unwind_GetTextRelBase)(struct _Unwind_Context *__restrict self); /* Only non-const for lazy initialized fields! */
INTDEF ATTR_PURE WUNUSED void *NOTHROW_NCX(LIBCCALL libc_Unwind_FindEnclosingFunction)(void const *pc);

/* Kernel-level exception handling (mode #2/#3 and mode #4). */
INTDEF except_register_state_t *__EXCEPT_HANDLER_CC libc_except_handler3_impl(except_register_state_t *__restrict state, struct exception_data *__restrict error);
INTDEF except_register_state_t *__EXCEPT_HANDLER_CC libc_except_handler4_impl(except_register_state_t *__restrict state, struct exception_data *__restrict error);
INTDEF ATTR_NORETURN void __EXCEPT_HANDLER_CC libc_except_handler3(except_register_state_t *__restrict state, struct exception_data *__restrict error);
INTDEF ATTR_NORETURN void __EXCEPT_HANDLER_CC libc_except_handler4(except_register_state_t *__restrict state, struct exception_data *__restrict error);

#define EXCEPT_INITIALIZER_KERNEL_EXCEPTION_HANDLER()                                           \
	do {                                                                                        \
		/* Bind the kernel-space exception handler using `sys_set_exception_handler()' */       \
		sys_set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND | EXCEPT_HANDLER_FLAG_SETHANDLER, \
		                          &libc_except_handler4, NULL);                                 \
	}	__WHILE0

#endif /* !__KERNEL__ */

INTDEF NONNULL((1)) _Unwind_Reason_Code NOTHROW_NCX(LIBCCALL libc_Unwind_RaiseException)(struct _Unwind_Exception *__restrict exception_object);
INTDEF ATTR_NORETURN NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_Unwind_Resume)(struct _Unwind_Exception *__restrict exception_object);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_Unwind_DeleteException)(struct _Unwind_Exception *__restrict exception_object);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uintptr_t NOTHROW_NCX(LIBCCALL libc_Unwind_GetGR)(struct _Unwind_Context const *__restrict context, int index);
INTDEF ATTR_LEAF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_Unwind_SetGR)(struct _Unwind_Context *__restrict context, int index, uintptr_t value);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uintptr_t NOTHROW_NCX(LIBCCALL libc_Unwind_GetIP)(struct _Unwind_Context const *__restrict context);
INTDEF ATTR_LEAF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_Unwind_SetIP)(struct _Unwind_Context *__restrict context, uintptr_t value);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uintptr_t NOTHROW_NCX(LIBCCALL libc_Unwind_GetLanguageSpecificData)(struct _Unwind_Context const *__restrict context);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uintptr_t NOTHROW_NCX(LIBCCALL libc_Unwind_GetRegionStart)(struct _Unwind_Context const *__restrict context);
INTDEF WUNUSED ATTR_LEAF NONNULL((1, 2)) uintptr_t NOTHROW_NCX(LIBCCALL libc_Unwind_GetIPInfo)(struct _Unwind_Context const *__restrict context, int *__restrict ip_before_insn);

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_LIBC_LIBC_EXCEPT_H */
