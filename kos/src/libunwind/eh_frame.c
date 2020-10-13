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
#ifndef GUARD_LIBUNWIND_EH_FRAME_C
#define GUARD_LIBUNWIND_EH_FRAME_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/byteorder.h>
#include <hybrid/overflow.h>
#include <hybrid/unaligned.h>

#include <kos/thread.h>
#include <kos/types.h>

#include <assert.h>
#include <string.h>

#include <libdebuginfo/dwarf.h>
#include <libunwind/cfi.h>
#include <libunwind/eh_frame.h>

#include "cfi.h"
#include "eh_frame.h"

#ifndef __KERNEL__
#include <dlfcn.h>
#endif /* !__KERNEL__ */

/* Relaxed CFA rules aren't currently needed (and as
 * a matter of fact: aren't anything that you'll find
 * apart of any standard. - I only though this is how
 * CFA was supposed to work at one point...) */
#undef CONFIG_DW_RELAXED_CFA_INITIALIZATION_RULES

#undef DEBUG_FRAME /* Build the .eh_frame parser! */

DECL_BEGIN

#undef CONFIG_NO_CFA_SIGFRAME_STATE
#if defined(CFI_UNWIND_NO_SIGFRAME_COMMON_UNCOMMON_REGISTERS) || \
    defined(__OPTIMIZE_SIZE__)
#define CONFIG_NO_CFA_SIGFRAME_STATE 1
#endif /* ... */

#define _convert_with_array(arr, index, error) \
	((index) >= COMPILER_LENOF(arr) ? (error) : arr[index])

/* Load register index convert arrays. */

/* Normal common/uncommon */
#ifndef cfi_unwind_register_dw2common
PRIVATE DEFINE_cfi_unwind_register_dw2common(_cur_dw2common);
#define cfi_unwind_register_dw2common(dw_regno) \
	_convert_with_array(_cur_dw2common, dw_regno, CFI_UNWIND_COMMON_REGISTER_COUNT)
#endif /* !cfi_unwind_register_dw2common */

#ifndef cfi_unwind_register_dw2uncommon
PRIVATE DEFINE_cfi_unwind_register_dw2uncommon(_cur_dw2uncommon);
#define cfi_unwind_register_dw2uncommon(dw_regno) \
	_convert_with_array(_cur_dw2uncommon, dw_regno, CFI_UNWIND_UNCOMMON_REGISTER_COUNT)
#endif /* !cfi_unwind_register_dw2uncommon */

#ifndef cfi_unwind_register_common2dw
PRIVATE DEFINE_cfi_unwind_register_common2dw(_cur_common2dw);
#define cfi_unwind_register_common2dw(common_regno) \
	_convert_with_array(_cur_common2dw, common_regno, CFI_UNWIND_REGISTER_COUNT)
#endif /* !cfi_unwind_register_common2dw */

#ifndef cfi_unwind_register_uncommon2dw
PRIVATE DEFINE_cfi_unwind_register_uncommon2dw(_cur_uncommon2dw);
#define cfi_unwind_register_uncommon2dw(uncommon_regno) \
	_convert_with_array(_cur_uncommon2dw, uncommon_regno, CFI_UNWIND_REGISTER_COUNT)
#endif /* !cfi_unwind_register_uncommon2dw */


/* Sigframe common/uncommon */
#ifndef cfi_unwind_sigframe_register_dw2common
PRIVATE DEFINE_cfi_unwind_sigframe_register_dw2common(_cur_sigframe_dw2common);
#define cfi_unwind_sigframe_register_dw2common(dw_regno) \
	_convert_with_array(_cur_sigframe_dw2common, dw_regno, CFI_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT)
#endif /* !cfi_unwind_sigframe_register_dw2common */

#ifndef cfi_unwind_sigframe_register_dw2uncommon
PRIVATE DEFINE_cfi_unwind_sigframe_register_dw2uncommon(_cur_sigframe_dw2uncommon);
#define cfi_unwind_sigframe_register_dw2uncommon(dw_regno) \
	_convert_with_array(_cur_sigframe_dw2uncommon, dw_regno, CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT)
#endif /* !cfi_unwind_sigframe_register_dw2uncommon */

#ifndef cfi_unwind_sigframe_register_common2dw
PRIVATE DEFINE_cfi_unwind_sigframe_register_common2dw(_cur_sigframe_common2dw);
#define cfi_unwind_sigframe_register_common2dw(common_regno) \
	_convert_with_array(_cur_sigframe_common2dw, common_regno, CFI_UNWIND_REGISTER_COUNT)
#endif /* !cfi_unwind_sigframe_register_common2dw */

#ifndef cfi_unwind_sigframe_register_uncommon2dw
PRIVATE DEFINE_cfi_unwind_sigframe_register_uncommon2dw(_cur_sigframe_uncommon2dw);
#define cfi_unwind_sigframe_register_uncommon2dw(uncommon_regno) \
	_convert_with_array(_cur_sigframe_uncommon2dw, uncommon_regno, CFI_UNWIND_REGISTER_COUNT)
#endif /* !cfi_unwind_sigframe_register_uncommon2dw */


/* Landing-pad common/uncommon */
#ifndef cfi_unwind_landing_register_dw2common
PRIVATE DEFINE_cfi_unwind_landing_register_dw2common(_cur_landing_dw2common);
#define cfi_unwind_landing_register_dw2common(dw_regno) \
	_convert_with_array(_cur_landing_dw2common, dw_regno, CFI_UNWIND_LANDING_COMMON_REGISTER_COUNT)
#endif /* !cfi_unwind_landing_register_dw2common */

#ifndef cfi_unwind_landing_register_dw2uncommon
PRIVATE DEFINE_cfi_unwind_landing_register_dw2uncommon(_cur_landing_dw2uncommon);
#define cfi_unwind_landing_register_dw2uncommon(dw_regno) \
	_convert_with_array(_cur_landing_dw2uncommon, dw_regno, CFI_UNWIND_LANDING_UNCOMMON_REGISTER_COUNT)
#endif /* !cfi_unwind_landing_register_dw2uncommon */

#ifndef cfi_unwind_landing_register_common2dw
PRIVATE DEFINE_cfi_unwind_landing_register_common2dw(_cur_landing_common2dw);
#define cfi_unwind_landing_register_common2dw(common_regno) \
	_convert_with_array(_cur_landing_common2dw, common_regno, CFI_UNWIND_REGISTER_COUNT)
#endif /* !cfi_unwind_landing_register_common2dw */

#ifndef cfi_unwind_landing_register_uncommon2dw
PRIVATE DEFINE_cfi_unwind_landing_register_uncommon2dw(_cur_landing_uncommon2dw);
#define cfi_unwind_landing_register_uncommon2dw(uncommon_regno) \
	_convert_with_array(_cur_landing_uncommon2dw, uncommon_regno, CFI_UNWIND_REGISTER_COUNT)
#endif /* !cfi_unwind_landing_register_uncommon2dw */





#ifndef __INTELLISENSE__
DECL_END
#define FIND_SPECIFIC_ADDRESS
#include "eh_frame-find_fde.c.inl"
/**/
#include "eh_frame-find_fde.c.inl"

#define EH_FRAME_FDE_EXEC_CFA_STATE 1
#include "eh_frame-fde_exec.c.inl"

#ifndef CONFIG_NO_CFA_SIGFRAME_STATE
#define EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE 1
#include "eh_frame-fde_exec.c.inl"
#endif /* !CONFIG_NO_CFA_SIGFRAME_STATE */

#define EH_FRAME_FDE_EXEC_CFA_VALUE 1
#include "eh_frame-fde_exec.c.inl"
#define EH_FRAME_FDE_EXEC_CFA_RULE 1
#include "eh_frame-fde_exec.c.inl"
#define EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT 1
#include "eh_frame-fde_exec.c.inl"

DECL_BEGIN
#else /* !__INTELLISENSE__ */

PRIVATE
#if CFI_UNWIND_COMMON_REGISTER_COUNT != 0 && CFI_UNWIND_UNCOMMON_REGISTER_COUNT != 0
	NONNULL((1, 4, 5, 6, 7))
#elif CFI_UNWIND_COMMON_REGISTER_COUNT != 0 || CFI_UNWIND_UNCOMMON_REGISTER_COUNT != 0
	NONNULL((1, 3, 4, 5, 6))
#else /* ... */
	NONNULL((1, 2, 3, 4, 5))
#endif /* !... */
	unsigned int
NOTHROW_NCX(CC libuw_unwind_fde_exec_until)(unwind_fde_t const *__restrict self,
#if CFI_UNWIND_COMMON_REGISTER_COUNT != 0
                                            unwind_cfa_register_t *common_init_regs,
#endif /* CFI_UNWIND_COMMON_REGISTER_COUNT != 0 */
#if CFI_UNWIND_UNCOMMON_REGISTER_COUNT != 0
                                            unwind_regno_t *uncommon_init_regs,
#endif /* CFI_UNWIND_UNCOMMON_REGISTER_COUNT != 0 */
                                            unwind_order_index_t *__restrict porder,
                                            byte_t *__restrict reader,
                                            byte_t *__restrict end,
                                            unwind_cfa_state_t *__restrict result,
                                            void *absolute_pc);

PRIVATE
#if CFI_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT != 0 && CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT != 0
	NONNULL((1, 4, 5, 6, 7))
#elif CFI_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT != 0 || CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT != 0
	NONNULL((1, 3, 4, 5, 6))
#else /* ... */
	NONNULL((1, 2, 3, 4, 5))
#endif /* !... */
	unsigned int
NOTHROW_NCX(CC libuw_unwind_sigframe_fde_exec_until)(unwind_fde_t const *__restrict self,
#if CFI_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT != 0
                                                     unwind_cfa_register_t *common_init_regs,
#endif /* CFI_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT != 0 */
#if CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT != 0
                                                     unwind_regno_t *uncommon_init_regs,
#endif /* CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT != 0 */
                                                     unwind_order_index_t *__restrict porder,
                                                     byte_t *__restrict reader,
                                                     byte_t *__restrict end,
                                                     unwind_cfa_sigframe_state_t *__restrict result,
                                                     void *absolute_pc);

PRIVATE NONNULL((1, 2, 3, 4)) unsigned int
NOTHROW_NCX(CC libuw_unwind_fde_exec_cfa_until)(unwind_fde_t const *__restrict self,
                                                byte_t *__restrict reader,
                                                byte_t *__restrict end,
                                                unwind_cfa_value_t *__restrict result,
                                                void *absolute_pc);

PRIVATE NONNULL((1, 2, 3, 4)) unsigned int
NOTHROW_NCX(CC libuw_unwind_fde_exec_rule_until)(unwind_fde_t const *__restrict self,
                                                 byte_t *__restrict reader,
                                                 byte_t *__restrict end,
                                                 unwind_cfa_register_t *__restrict rule,
                                                 unwind_regno_t dw_regno,
                                                 void *absolute_pc);
#endif /* __INTELLISENSE__ */




/* Similar to `unwind_fde_exec()', but used to calculate the
 * unwind rule for `dw_regno' at the given text location.
 * This is used to implement unwinding for uncommon registers,
 * since `unwind_fde_exec()' will not already calculate these
 * during the first pass (thus keeping down the memory requirements
 * imposed on the one responsible for allocating `unwind_cfa_state_t')
 * @param: self:   The FDE to execute in search of `absolute_pc'
 * @param: result: The CFA register result controller to-be filled.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
INTERN NONNULL((1, 2)) unsigned int
NOTHROW_NCX(CC libuw_unwind_fde_rule)(unwind_fde_t const *__restrict self,
                                      unwind_cfa_register_t *__restrict result,
                                      unwind_regno_t dw_regno,
                                      void *absolute_pc) {
	unsigned int error;
	/* `libuw_unwind_fde_exec_rule_until()' won't initialize
	 * the result, so pre-initialize it to an undefined state. */
	result->cr_rule = DW_CFA_register_rule_undefined;
	/* Start out by scanning the evaluation-body, as it's most
	 * likely to contain the unwind rule requested by the caller. */
	error = libuw_unwind_fde_exec_rule_until(self,
	                                         self->f_evaltext,
	                                         self->f_evaltextend,
	                                         result,
	                                         dw_regno,
	                                         absolute_pc);
	if (error == UNWIND_SUCCESS && result->cr_rule == DW_CFA_register_rule_undefined) {
		/* If we couldn't find it in the init-body, try the eval-body. */
		error = libuw_unwind_fde_exec_rule_until(self,
		                                         self->f_inittext,
		                                         self->f_inittextend,
		                                         result,
		                                         dw_regno,
		                                         absolute_pc);
	}
	return error;
}



/* Same as `unwind_fde_exec()', however only calculate the CFA restore descriptor.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
INTERN NONNULL((1, 2)) unsigned int
NOTHROW_NCX(CC libuw_unwind_fde_exec_cfa)(unwind_fde_t const *__restrict self,
                                          unwind_cfa_value_t *__restrict result,
                                          void *absolute_pc) {
	unsigned int error;
	memset(result, 0, sizeof(*result));
	error = libuw_unwind_fde_exec_cfa_until(self,
	                                        self->f_inittext,
	                                        self->f_inittextend,
	                                        result,
	                                        (void *)-1);
	if likely(error == UNWIND_SUCCESS) {
		error = libuw_unwind_fde_exec_cfa_until(self,
		                                        self->f_evaltext,
		                                        self->f_evaltextend,
		                                        result,
		                                        absolute_pc);
	}
	TRACE("unwind_fde_exec_cfa() -> %u\n", error);
	return error;
}

PRIVATE NONNULL((1, 2, 4)) unsigned int CC
execute_eh_frame_expression(byte_t *__restrict expression_pointer,
                            unwind_getreg_t reg_getter,
                            void const *reg_callback_arg,
                            uintptr_t *__restrict presult,
                            uintptr_t cfa_value) {
	unwind_ste_t top;
	unwind_emulator_t emulator;
	size_t expr_length;
	expr_length = dwarf_decode_uleb128((byte_t **)&expression_pointer);
	memset(&emulator, 0, sizeof(emulator));
	emulator.ue_pc             = expression_pointer;
	emulator.ue_pc_start       = expression_pointer;
	emulator.ue_pc_end         = expression_pointer + expr_length;
	emulator.ue_regget         = reg_getter;
	emulator.ue_regget_arg     = reg_callback_arg;
	emulator.ue_addrsize       = sizeof(void *);
	emulator.ue_bjmprem        = UNWIND_EMULATOR_BJMPREM_DEFAULT;
	emulator.ue_call_frame_cfa = cfa_value;
	emulator.ue_tlsbase        = (byte_t *)-1;
	top.s_type   = UNWIND_STE_CONSTANT;
	top.s_uconst = cfa_value;
	return libuw_unwind_emulator_exec_autostack(&emulator,
	                                            &top,
	                                            NULL,
	                                            presult);
}

STATIC_ASSERT(CFI_REGISTER_SIZE(CFI_UNWIND_REGISTER_SP) == sizeof(uintptr_t));
STATIC_ASSERT(CFI_REGISTER_SIZE(CFI_UNWIND_REGISTER_PC) == sizeof(void *));



/* Calculate the CFA (CanonicalFrameAddress) of the given CFA restore descriptor.
 * @param: self: The CFA state to-be used to calculate the CFA
 * @return: UNWIND_SUCCESS:               ...
 * @return: UNWIND_INVALID_REGISTER:      ...
 * @return: UNWIND_SEGFAULT:              ...
 * @return: UNWIND_EMULATOR_*:            ...
 * @return: UNWIND_APPLY_NOADDR_REGISTER: ... */
INTERN NONNULL((1, 2, 4)) unsigned int CC
libuw_unwind_cfa_calculate_cfa(unwind_cfa_value_t const *__restrict self,
                               unwind_getreg_t reg_getter,
                               void const *reg_callback_arg,
                               uintptr_t *__restrict presult) {
	/* Calculate the CFA value. */
	if (self->cv_type == UNWIND_CFA_VALUE_REGISTER) {
		if unlikely(CFI_REGISTER_SIZE(self->cv_reg) != sizeof(uintptr_t))
			ERRORF(err_noaddr_register, "regno=%u", (unsigned int)self->cv_reg);
		if unlikely(!(*reg_getter)(reg_callback_arg,
		                           self->cv_reg,
		                           presult))
			ERRORF(err_invalid_register, "regno=%u", (unsigned int)self->cv_reg);
		*presult += self->cv_value;
	} else if (self->cv_type == UNWIND_CFA_VALUE_EXPRESSION) {
		/* Use a CFI emulator to calculate the CFA base value. */
		return execute_eh_frame_expression(self->cv_expr,
		                                   reg_getter,
		                                   reg_callback_arg,
		                                   presult,
		                                   0);
	} else {
		*presult = 0;
	}
	return UNWIND_SUCCESS;
err_invalid_register:
	return UNWIND_INVALID_REGISTER;
err_noaddr_register:
	return UNWIND_APPLY_NOADDR_REGISTER;
}

#ifndef __INTELLISENSE__
DECL_END

#define EH_FRAME_CFA_APPLY 1
#include "eh_frame-cfa_apply.c.inl"

#ifndef CONFIG_NO_CFA_SIGFRAME_STATE
#define EH_FRAME_CFA_SIGFRAME_APPLY 1
#include "eh_frame-cfa_apply.c.inl"
#endif /* !CONFIG_NO_CFA_SIGFRAME_STATE */

#define EH_FRAME_CFA_LANDING_APPLY 1
#include "eh_frame-cfa_apply.c.inl"

DECL_BEGIN
#endif /* !__INTELLISENSE__ */




/* Alias the sigframe variants on-top of the regular ones. */
#ifdef CONFIG_NO_CFA_SIGFRAME_STATE
DEFINE_INTERN_ALIAS(libuw_unwind_fde_sigframe_exec, libuw_unwind_fde_exec);
DEFINE_INTERN_ALIAS(libuw_unwind_cfa_sigframe_apply, libuw_unwind_cfa_apply);
#endif /* CONFIG_NO_CFA_SIGFRAME_STATE */

DEFINE_PUBLIC_ALIAS(unwind_fde_load, libuw_unwind_fde_load);
DEFINE_PUBLIC_ALIAS(unwind_fde_scan, libuw_unwind_fde_scan);
DEFINE_PUBLIC_ALIAS(unwind_fde_exec, libuw_unwind_fde_exec);
DEFINE_PUBLIC_ALIAS(unwind_fde_landing_exec, libuw_unwind_fde_landing_exec);
DEFINE_PUBLIC_ALIAS(unwind_fde_sigframe_exec, libuw_unwind_fde_sigframe_exec);
DEFINE_PUBLIC_ALIAS(unwind_fde_rule, libuw_unwind_fde_rule);
DEFINE_PUBLIC_ALIAS(unwind_fde_exec_cfa, libuw_unwind_fde_exec_cfa);
DEFINE_PUBLIC_ALIAS(unwind_cfa_apply, libuw_unwind_cfa_apply);
DEFINE_PUBLIC_ALIAS(unwind_cfa_landing_apply, libuw_unwind_cfa_landing_apply);
DEFINE_PUBLIC_ALIAS(unwind_cfa_sigframe_apply, libuw_unwind_cfa_sigframe_apply);
DEFINE_PUBLIC_ALIAS(unwind_cfa_calculate_cfa, libuw_unwind_cfa_calculate_cfa);

DECL_END

#endif /* !GUARD_LIBUNWIND_EH_FRAME_C */
