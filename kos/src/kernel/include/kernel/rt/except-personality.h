/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_RT_EXCEPT_PERSONALIY_H
#define GUARD_KERNEL_INCLUDE_KERNEL_RT_EXCEPT_PERSONALIY_H 1

/* Kernel exception handling personality definitions.
 * aka. `.cfi_personality',  `__gcc_personality_v0()' */

#include <kernel/compiler.h>

#include <kernel/arch/rt/except-personality.h> /* arch-override for `EXCEPT_PERSONALITY_CC' */

#include <hybrid/typecore.h>

#include <kos/kernel/cpu-state-helpers.h> /* kcpustate_getpc */
#include <kos/kernel/cpu-state.h>         /* struct kcpustate */

#include <libunwind/eh_frame.h>
#include <libunwind/register.h>

/* Possible values for `_Unwind_Reason_Code'. Semantically speaking,
 * these are broadly  equivalent to the  equally named reason  codes
 * found in- and defined by `<libunwind/except.h>' */
#define _URC_INSTALL_CONTEXT     0 /* An exception handler was found, and `uc_state' was updated and should be jumped to (after adjusting for `DW_CFA_GNU_args_size') */
#define _URC_INSTALL_CONTEXT_NOW 1 /* Same as `_URC_INSTALL_CONTEXT', but don't adjust for `DW_CFA_GNU_args_size' */
#define _URC_CONTINUE_UNWIND     2 /* Continue unwinding to search for an exception handler. */
#define _URC_END_OF_STACK        3 /* Abort the search for exception handlers, and panic() because of unhandled exception. */


#define OFFSET__UNWIND_CONTEXT_FDE            0
#define OFFSET__UNWIND_CONTEXT_STATE          __SIZEOF_UNWIND_FDE
#define OFFSET__UNWIND_CONTEXT_ADJPC          (__SIZEOF_UNWIND_FDE + __SIZEOF_POINTER__)
#define OFFSET__UNWIND_CONTEXT_PC_BEFORE_INSN (__SIZEOF_UNWIND_FDE + (__SIZEOF_POINTER__ * 2))
#define SIZEOF__UNWIND_CONTEXT                (__SIZEOF_UNWIND_FDE + (__SIZEOF_POINTER__ * 3))

#ifdef __CC__
DECL_BEGIN

#ifndef EXCEPT_PERSONALITY_CC
#define EXCEPT_PERSONALITY_CC KCALL
#endif /* !EXCEPT_PERSONALITY_CC */

struct unwind_fde_struct;
struct kcpustate;

struct _Unwind_Context {
	unwind_fde_t      uc_fde;            /* Currently relevant FDE */
	struct kcpustate *uc_state;          /* [1..1] Program state */
	void const       *uc_adjpc;          /* Currently relevant program counter. Same as PC in `uc_state',
	                                      * but already adjusted as per `uc_pc_before_insn' (such that it
	                                      * can always be used in "uc_adjpc >= start && uc_adjpc < end") */
	__BYTE_TYPE__     uc_pc_before_insn; /* Non-zero if the last FDE was a signal frame. */
	__BYTE_TYPE__ _uc_pad[__SIZEOF_POINTER__ - 1]; /* ... */
};

#ifndef ___Unwind_Reason_Code_defined
#define ___Unwind_Reason_Code_defined
typedef unsigned int _Unwind_Reason_Code; /* One of `EXCEPT_PERSONALITY_*' */
#endif /* !___Unwind_Reason_Code_defined */


/* The  prototype by which custom personality function  must abide within the KOS kernel.
 * When called, `context->uc_state' refers to the state _within_ the associated function;
 * not the state after that function has been unwound!
 * NOTES:
 *  - `.cfi_personality 0, <some-function-implemented-as-_Unwind_Personality_Fn>'
 *  - The value specified by `.cfi_lsda 0, <lsda-value>' can be read from `context->uc_fde.f_lsdaaddr'
 * @param: context: Exception context
 * @return: * : One of `DWARF_PERSO_*' */
typedef ABNORMAL_RETURN NONNULL_T((1)) _Unwind_Reason_Code
NOTHROW_T(EXCEPT_PERSONALITY_CC *_Unwind_Personality_Fn)(struct _Unwind_Context *__restrict context);

/* Pre-defined personality functions */
FUNDEF WUNUSED NONNULL((1)) _Unwind_Reason_Code NOTHROW(EXCEPT_PERSONALITY_CC __gcc_personality_v0)(struct _Unwind_Context *__restrict context);
FUNDEF WUNUSED NONNULL((1)) _Unwind_Reason_Code NOTHROW(EXCEPT_PERSONALITY_CC __gxx_personality_v0)(struct _Unwind_Context *__restrict context);
#ifdef BUILDING_KERNEL_CORE
INTDEF WUNUSED NONNULL((1)) _Unwind_Reason_Code NOTHROW(EXCEPT_PERSONALITY_CC libc_gxx_personality_v0)(struct _Unwind_Context *__restrict context);
#endif /* BUILDING_KERNEL_CORE */


/* Some more compatibility (via macros, so API-only) with user-space/standard exception handling */
typedef uintptr_t _Unwind_Ptr;
typedef uintptr_t _Unwind_Word;
#define _Unwind_GetLanguageSpecificData(context) ((_Unwind_Ptr)(context)->uc_fde.f_lsdaaddr)
#define _Unwind_GetRegionStart(context)          ((_Unwind_Ptr)(context)->uc_fde.f_pcstart)
#define _Unwind_GetIPInfo(context, ip_before_insn)               \
	(*(ip_before_insn) = ((context)->uc_pc_before_insn ? 1 : 0), \
	 (_Unwind_Ptr)kcpustate_getpc((context)->uc_state))
#define _Unwind_GetIP(context)        ((_Unwind_Ptr)kcpustate_getpc((context)->uc_state))
#define _Unwind_SetIP(context, value) kcpustate_setpc((context)->uc_state, value)
#define _Unwind_GetGR(context, regno) \
	__XBLOCK({ _Unwind_Word _result; __XRETURN unwind_getreg_kcpustate((context)->uc_state, regno, &_result) == UNWIND_SUCCESS ? _result : 0; })
#define _Unwind_SetGR(context, regno, value) \
	__XBLOCK({ _Unwind_Word _value = (value); (void)unwind_setreg_kcpustate_p(&(context)->uc_state, regno, &_value); })

/* Never defined by the kernel (only here because  needed
 * for `_Unwind_Resume', which is called by the compiler)
 *
 * One could argue that "struct _Unwind_Exception" is simply our
 * `struct exception_data', since `__gxx_personality_v0'  pushes
 * that value for the compiler to pass to `__cxa_begin_catch()'. */
struct _Unwind_Exception;
#define _Unwind_DeleteException(object) (void)0



/************************************************************************/
/* Symbols referenced by the compiler...                                */
/************************************************************************/


/* NOTE: _Unwind_Resume() is more  akin to  deemon's `end finally'  instruction
 *       (with the exception of not being invoked when a finally wasn't entered
 *       because of  an exception),  rather than  `except_rethrow()', which  is
 *       equivalent to `throw except'.
 * However, since kernel exception handling  is rather simplistic, we  can
 * simply handle it the same way we handle rethrow, except that we mustn't
 * set the `EXCEPT_FRETHROW' flag.
 * @param: object: Ignored and unused
 */
FUNDEF ATTR_NORETURN void NOTHROW_NCX(ATTR_CDECL _Unwind_Resume)(struct _Unwind_Exception *object);

/* Alias for `except_rethrow()' */
FUNDEF ATTR_NORETURN void ATTR_CDECL __cxa_rethrow(void);

/* These are generated around catch-blocks. "__cxa_begin_catch" is a
 * no-op that simply re-returns `ptr'. Exception handling will  have
 * previously set-up `ptr' as `&except_data()->e_args'
 *
 * `__cxa_end_catch()' actually serves a purpose however, that purpose
 * being to clear the  thrown exception, unless the  `EXCEPT_FRETHROW'
 * flag is set (in which case it will clear `EXCEPT_FRETHROW', but not
 * do anything beyond that). */
FUNDEF void *NOTHROW(ATTR_CDECL __cxa_begin_catch)(/*struct _Unwind_Exception**/ void *ptr);
FUNDEF void /*NOTHROW*/(ATTR_CDECL __cxa_end_catch)(void);

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_RT_EXCEPT_PERSONALIY_H */
