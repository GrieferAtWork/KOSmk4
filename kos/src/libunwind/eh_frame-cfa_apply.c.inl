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
#ifdef __INTELLISENSE__
#include "eh_frame.c"

//#define EH_FRAME_CFA_APPLY 1
#define EH_FRAME_CFA_SIGFRAME_APPLY 1
#endif /* __INTELLISENSE__ */

#if (defined(EH_FRAME_CFA_APPLY) + defined(EH_FRAME_CFA_SIGFRAME_APPLY)) != 1
#error "Must #define EH_FRAME_CFA_APPLY or EH_FRAME_CFA_SIGFRAME_APPLY"
#endif


DECL_BEGIN

#ifdef EH_FRAME_CFA_SIGFRAME_APPLY
#ifdef CFI_UNWIND_SIGFRAME_COMMON_REGISTER_SP
#define CFI_UNWIND_LOCAL_COMMON_REGISTER_SP      CFI_UNWIND_SIGFRAME_COMMON_REGISTER_SP
#else /* CFI_UNWIND_SIGFRAME_COMMON_REGISTER_SP */
#define CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_SP    CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_SP
#endif /* !CFI_UNWIND_SIGFRAME_COMMON_REGISTER_SP */
#define CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT   CFI_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT
#define CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT
#define cfi_unwind_local_register_common2dw      cfi_unwind_sigframe_register_common2dw
#define cfi_unwind_local_register_uncommon2dw    cfi_unwind_sigframe_register_uncommon2dw
#define libuw_unwind_local_fde_exec_until        libuw_unwind_sigframe_fde_exec_until
#else /* EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE */
#ifdef CFI_UNWIND_COMMON_REGISTER_SP
#define CFI_UNWIND_LOCAL_COMMON_REGISTER_SP      CFI_UNWIND_COMMON_REGISTER_SP
#else /* CFI_UNWIND_COMMON_REGISTER_SP */
#define CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_SP    CFI_UNWIND_UNCOMMON_REGISTER_SP
#endif /* !CFI_UNWIND_COMMON_REGISTER_SP */
#define CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT   CFI_UNWIND_COMMON_REGISTER_COUNT
#define CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT CFI_UNWIND_UNCOMMON_REGISTER_COUNT
#define cfi_unwind_local_register_common2dw      cfi_unwind_register_common2dw
#define cfi_unwind_local_register_uncommon2dw    cfi_unwind_register_uncommon2dw
#define libuw_unwind_local_fde_exec_until        libuw_unwind_fde_exec_until
#endif /* !EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE */



#ifdef EH_FRAME_CFA_SIGFRAME_APPLY
/* Behaves identical to `unwind_fde_exec()', and doesn't actually ever have to be
 * used, but performes better than `unwind_fde_exec()' when unwinding SIGNAL_FRAME
 * FDE descriptors (though again: use of this is entirely optional; the regular
 * `unwind_fde_exec()' is just as capable of unwinding signal frame descriptors.
 * This function is merely optimized to better restore registers commonly used
 * within signal frames)
 * @param: self:   The FDE to execute in search of `absolute_pc'
 * @param: result: CFA state descriptor, to-be filled with restore information upon success.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
INTERN NONNULL((1, 2)) unsigned int
NOTHROW_NCX(CC libuw_unwind_fde_sigframe_exec)(unwind_fde_t const *__restrict self,
                                               unwind_cfa_sigframe_state_t *__restrict result,
                                               void *absolute_pc)
#else /* EH_FRAME_CFA_SIGFRAME_APPLY */
/* Execute CFA result instruction until `absolute_pc' has been reached,
 * or the entirety of the FDE instruction code has been executed.
 * This function is used to fill in CFA result information at a given address,
 * which can then be used to unwind a register result for the purpose of
 * implementing language-level, zero-effort exception support, as well
 * as for generating tracebacks when combined with `libdebuginfo.so'
 * NOTE: Usually, the caller will have already ensured that:
 *      `self->f_pcstart <= absolute_pc && self->f_pcend >= absolute_pc'
 * @param: self:   The FDE to execute in search of `absolute_pc'
 * @param: result: CFA result descriptor, to-be filled with restore information upon success.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
INTERN NONNULL((1, 2)) unsigned int
NOTHROW_NCX(CC libuw_unwind_fde_exec)(unwind_fde_t const *__restrict self,
                                      unwind_cfa_state_t *__restrict result,
                                      void *absolute_pc)
#endif /* !EH_FRAME_CFA_SIGFRAME_APPLY */
{
	unsigned int error;
	unwind_order_index_t order = 0;
	memset(result, 0, sizeof(*result));
	/* Execute the init-body */
	error = libuw_unwind_local_fde_exec_until(self,
#if CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT != 0
	                                          NULL,
#endif /* CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT != 0 */
#if CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0
	                                          NULL,
#endif /* CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0 */
	                                          &order,
	                                          self->f_inittext,
	                                          self->f_inittextend,
	                                          result,
	                                          (void *)-1);
	if likely(error == UNWIND_SUCCESS) {
#if CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT != 0
		unwind_cfa_register_t common_init_regs[CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT];
#endif /* CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT != 0 */
#if CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0
		uintptr_half_t uncommon_init_regs[CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT];
#endif /* CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0 */
#if CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT != 0
		memcpy(common_init_regs, result->cs_regs, sizeof(result->cs_regs));
#endif /* CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT != 0 */
#if CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0
		memcpy(uncommon_init_regs, result->cs_uncorder, sizeof(result->cs_uncorder));
#endif /* CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0 */
		/* Execute the eval-body */
		error = libuw_unwind_local_fde_exec_until(self,
#if CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT != 0
		                                          common_init_regs,
#endif /* CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT != 0 */
#if CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0
		                                          uncommon_init_regs,
#endif /* CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0 */
		                                          &order,
		                                          self->f_evaltext,
		                                          self->f_evaltextend,
		                                          result,
		                                          absolute_pc);
	}
	TRACE("unwind_fde_exec() -> %u\n", error);
	return error;
}



#ifndef GUARDED_MEMCPY_DEFINED
#define GUARDED_MEMCPY_DEFINED 1
INTDEF WUNUSED bool
NOTHROW(CC guarded_memcpy)(void *dst, void const *src, size_t num_bytes);
#endif /* !GUARDED_MEMCPY_DEFINED */




#ifdef EH_FRAME_CFA_SIGFRAME_APPLY
/* For use with `unwind_fde_sigframe_exec()': Apply register rules previously calculated.
 * @param: self:        The CFA state to-be used when applying registers
 * @param: absolute_pc: Same value as was previously used to calculate `fde' from `self'
 * @return: UNWIND_SUCCESS:               ...
 * @return: UNWIND_INVALID_REGISTER:      ...
 * @return: UNWIND_SEGFAULT:              ...
 * @return: UNWIND_EMULATOR_*:            ...
 * @return: UNWIND_APPLY_NOADDR_REGISTER: ... */
INTERN NONNULL((1, 2, 4, 6)) unsigned int CC
libuw_unwind_cfa_sigframe_apply(unwind_cfa_sigframe_state_t *__restrict self,
                                unwind_fde_t const *__restrict fde, void *absolute_pc,
                                unwind_getreg_t reg_getter, void const *reg_getter_arg,
                                unwind_setreg_t reg_setter, void *reg_setter_arg)
#else /* EH_FRAME_CFA_SIGFRAME_APPLY */
/* Apply a given CFA unwind state in order to apply register information from from reg_getter to reg_setter.
 * Note however that only registers with a rule other than `DW_CFA_register_rule_undefined'
 * will be applied, meaning that `*reg_setter' will not get invoked for these registers.
 * WARNING: This function will modify `self' in such a manner that repeated calls
 *          require that `self' must be restored to its state prior to a call to
 *          this function before a repeated call can be made!
 * @param: self:        The CFA state to-be used when applying registers
 * @param: absolute_pc: Same value as was previously used to calculate `fde' from `self'
 * @return: UNWIND_SUCCESS:               ...
 * @return: UNWIND_INVALID_REGISTER:      ...
 * @return: UNWIND_SEGFAULT:              ...
 * @return: UNWIND_EMULATOR_*:            ...
 * @return: UNWIND_APPLY_NOADDR_REGISTER: ... */
INTERN NONNULL((1, 2, 4, 6)) unsigned int CC
libuw_unwind_cfa_apply(unwind_cfa_state_t *__restrict self,
                       unwind_fde_t const *__restrict fde, void *absolute_pc,
                       unwind_getreg_t reg_getter, void const *reg_getter_arg,
                       unwind_setreg_t reg_setter, void *reg_setter_arg)
#endif /* !EH_FRAME_CFA_SIGFRAME_APPLY */
{
	unsigned int result;
	uintptr_t cfa;
	union {
		byte_t bytes[CFI_UNWIND_REGISTER_MAXSIZE];
		uintptr_t addr;
	} reg_buf;
#ifdef CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_SP
	bool has_sp_rule;
	has_sp_rule = self->cs_uncorder[CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_SP] != 0;
#endif /* CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_SP */

	/* Step #1: Calculate the CFA (CanonicalFrameAddress) */
	result = libuw_unwind_cfa_calculate_cfa(&self->cs_cfa,
	                                        reg_getter,
	                                        reg_getter_arg,
	                                        &cfa);
	TRACE("unwind_cfa_apply():unwind_cfa_calculate_cfa() -> %u (%p)\n", result, cfa);
	if unlikely(result != UNWIND_SUCCESS)
		goto done;
	/* Apply new register values.
	 * The order in which this is done should depend
	 * on the order in which rules were defined:
	 * >> .cfi_XXX  %eax
	 * >> .cfi_XXX  %ecx
	 * >> .cfi_XXX  %edx
	 * >> .cfi_XXX  %ecx
	 * ORDER: ECX, EDX, EAX
	 * RULES: Restore newer registers first */
	for (;;) {
#if CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT != 0 && \
    CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0
		bool max_order_is_common = true;
#endif /* CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT != 0 && CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0 */
		unwind_order_index_t max_order = 0;
		uintptr_half_t i, max_index = 0;
		uintptr_half_t dw_regno;
		unwind_cfa_register_t *rule;
#if CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0
		unwind_cfa_register_t uncommon_rule;
#endif /* CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0 */
#if CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT != 0
		/* Search common registers */
		for (i = 0; i < CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT; ++i) {
			if (self->cs_regs[i].cr_order > max_order) {
				max_order = self->cs_regs[i].cr_order;
				max_index = i;
			}
		}
#endif /* CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT != 0 */
#if CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0
		/* Search uncommon registers */
		for (i = 0; i < CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT; ++i) {
			if (self->cs_uncorder[i] > max_order) {
				max_order = self->cs_uncorder[i];
				max_index = i;
				max_order_is_common = false;
			}
		}
#endif /* CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0 */
		if (max_order == 0)
			break;
		/* Don't repeat ourself. */
#if CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT != 0 && \
    CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0
		if (max_order_is_common)
#endif /* CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT != 0 && CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0 */
#if CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT != 0
		{
			dw_regno = cfi_unwind_local_register_common2dw(max_index);
			rule = &self->cs_regs[max_index];
			rule->cr_order = 0;
		}
#endif /* CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT != 0 */
#if CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT != 0 && \
    CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0
		else
#endif /* CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT != 0 && CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0 */
#if CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0
		{
			dw_regno = cfi_unwind_local_register_uncommon2dw(max_index);
			DOTRACE("Uncommon register used: %u (%u)\n",
			      (unsigned int)dw_regno,
			      (unsigned int)max_index);
			self->cs_uncorder[max_index] = 0;
			rule = &uncommon_rule;
			result = libuw_unwind_fde_rule(fde, &uncommon_rule,
			                               dw_regno, absolute_pc);
			if unlikely(result != UNWIND_SUCCESS)
				goto done;
		}
#endif /* CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0 */
		TRACE("UNWIND(reg:%u,order:%u,rule:%u)\n",
		      (unsigned int)dw_regno,
		      (unsigned int)max_order,
		      (unsigned int)rule->cr_rule);
		switch (rule->cr_rule) {

		case DW_CFA_register_rule_register:
			if unlikely(!(*reg_getter)(reg_getter_arg,
			                           (uintptr_half_t)rule->cr_value,
			                           reg_buf.bytes))
				ERROR(err_invalid_register);
			if unlikely(!(*reg_setter)(reg_setter_arg,
			                           dw_regno,
			                           reg_buf.bytes))
				ERROR(err_invalid_register);
			break;

		case DW_CFA_register_rule_offsetn:
			if unlikely(OVERFLOW_SADD((intptr_t)cfa,
			                          (intptr_t)rule->cr_value,
			                          (intptr_t *)&reg_buf.addr))
				ERRORF(err_segfault, "cfa = %p; cr_value = %p\n", cfa, rule->cr_value);
			if unlikely(!guarded_memcpy(reg_buf.bytes,
			                            (void const *)reg_buf.addr,
			                            CFI_REGISTER_SIZE(dw_regno))) {
				ERRORF(err_segfault, "reg_buf.addr = %p; cfa = %p; cr_value = %p; cv_type = %u; cv_reg = %u; cv_value = %p\n",
				       reg_buf.addr, cfa, rule->cr_value,
				       (unsigned int)self->cs_cfa.cv_type,
				       (unsigned int)self->cs_cfa.cv_reg, (uintptr_t)self->cs_cfa.cv_value);
			}
			if unlikely(!(*reg_setter)(reg_setter_arg,
			                           dw_regno,
			                           reg_buf.bytes))
				ERROR(err_invalid_register);
			break;

		case DW_CFA_register_rule_val_offsetn:
			if unlikely(CFI_REGISTER_SIZE(dw_regno) != sizeof(uintptr_t))
				ERROR(err_noaddr_register);
			/* No overflow checks here, because we don't reference the memory. */
			reg_buf.addr = cfa + rule->cr_value;
			if unlikely(!(*reg_setter)(reg_setter_arg,
			                           dw_regno,
			                           reg_buf.bytes))
				ERROR(err_invalid_register);
			break;

		case DW_CFA_register_rule_val_expression:
			if unlikely(CFI_REGISTER_SIZE(dw_regno) != sizeof(uintptr_t))
				ERROR(err_noaddr_register); /* XXX: Wouldn't DW_OP_piece be used for this? */
			result = execute_eh_frame_expression(rule->cr_expr,
			                                     reg_getter,
			                                     reg_getter_arg,
			                                     &reg_buf.addr,
			                                     cfa);
			if unlikely(result != UNWIND_SUCCESS)
				goto done;
			if unlikely(!(*reg_setter)(reg_setter_arg,
			                           dw_regno,
			                           reg_buf.bytes))
				ERROR(err_invalid_register);
			break;

		case DW_CFA_register_rule_expression:
			result = execute_eh_frame_expression(rule->cr_expr,
			                                     reg_getter,
			                                     reg_getter_arg,
			                                     &reg_buf.addr,
			                                     cfa);
			if unlikely(result != UNWIND_SUCCESS)
				goto done;
			if unlikely(!guarded_memcpy(reg_buf.bytes,
			                            (void const *)reg_buf.addr,
			                            CFI_REGISTER_SIZE(dw_regno)))
				ERROR(err_segfault);
			if unlikely(!(*reg_setter)(reg_setter_arg,
			                           dw_regno,
			                           reg_buf.bytes))
				ERROR(err_invalid_register);
			break;

		default: break;
		}
	}
	assertf(self->cs_cfa.cv_type != UNWIND_CFA_VALUE_UNSET,
	        "No CFA for %p...%p (GDB doesn't like this)",
	        fde->f_pcstart, (byte_t *)fde->f_pcend - 1);

	/* Set the new CFA value as content of the SP register. */
	if (self->cs_cfa.cv_type != UNWIND_CFA_VALUE_UNSET &&
	    /* Only apply if no other register rule was already defined for SP
	     * This allows users to satisfy gdb by providing a CFA rule but still
	     * provide a value for SP by providing an explicit register rule for it. */
#ifdef CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_SP
	    !has_sp_rule
#elif defined(CFI_UNWIND_LOCAL_COMMON_REGISTER_SP)
	    (self->cs_regs[CFI_UNWIND_LOCAL_COMMON_REGISTER_SP].cr_rule == DW_CFA_register_rule_undefined)
#endif /* ... */
	    ) {
		/* Check if we should apply signal frame transformations.
		 * Note that we only do this if we have a CFA rule and do intend on applying it.
		 * In any other case, applying sigframe transformation wouldn't make any sense,
		 * and would even cause problems by interfering with GDB erroring out with:
		 *   - Backtrace stopped: previous frame inner to this frame (corrupt stack?)
		 * This can be caused when one frame's return-SP is greater than it's caller,
		 * which should normally never be the case, but can happen when a custom-SP
		 * restore rule was defined.
		 * Right now, GDB allows SP to be any value during unwind when either the called,
		 * or the calling frame are marked as .cfi_signal_frame.
		 * In my opinion, this should be loosened a bit to only stop unwinding if the fully
		 * unwound frame ends up being a carbon copy of a previous frame, rather than always
		 * failing when SP isn't where GDB would like it to be at.
		 * Anyways, what you as a KOS developer should take away from this is:
		 *   - Any custom assembly function that assigns a new ESP from either another
		 *     stack, or somewhere further up the stack must be marked as .cfi_signal_frame
		 *   - The KOS unwind mechanism will ignore .cfi_def_cfa and .cfi_signal_frame when
		 *     another rule exists that assign behavior to unwinding %esp
		 *   - GDB will _NOT_ working properly unless every function has a CFA rule defined.
		 *     For this purpose, you can usually use `.cfi_def_cfa %esp, 0', however be warned
		 *     that the value of this expression is used as the FRAME-ID which GDB uses to
		 *     identify frames, so try to keep its value unique I guess...
		 *   - With all of this in mind, a custom register restore function would look like this:
		 * >>     .cfi_startproc simple
		 * >>     .cfi_def_cfa %esp, 0
		 * >>     .cfi_signal_frame
		 * >> #define DEFINE_REGISTER_ADDRESS(reg) \
		 * >>     .cfi_escape DW_CFA_expression; \
		 * >>     .cfi_escape reg; \
		 * >>     .cfi_escape ...; \
		 * >>     ...;
		 * >>     DEFINE_REGISTER_ADDRESS(CFI_386_UNWIND_REGISTER_EDI)
		 * >>     DEFINE_REGISTER_ADDRESS(CFI_386_UNWIND_REGISTER_ESI)
		 * >>     DEFINE_REGISTER_ADDRESS(CFI_386_UNWIND_REGISTER_EBP)
		 * >>     DEFINE_REGISTER_ADDRESS(CFI_386_UNWIND_REGISTER_ESP)  // This rule right here overrides normal CFA unwinding
		 * >>     DEFINE_REGISTER_ADDRESS(CFI_386_UNWIND_REGISTER_EBX)
		 * >>     DEFINE_REGISTER_ADDRESS(CFI_386_UNWIND_REGISTER_EDX)
		 * >>     DEFINE_REGISTER_ADDRESS(CFI_386_UNWIND_REGISTER_ECX)
		 * >>     DEFINE_REGISTER_ADDRESS(CFI_386_UNWIND_REGISTER_EAX)
		 * >>     DEFINE_REGISTER_ADDRESS(CFI_386_UNWIND_REGISTER_EFLAGS)
		 * >>     DEFINE_REGISTER_ADDRESS(CFI_386_UNWIND_REGISTER_EIP)
		 * >>     DEFINE_REGISTER_ADDRESS(CFI_386_UNWIND_REGISTER_ES)
		 * >>     DEFINE_REGISTER_ADDRESS(CFI_386_UNWIND_REGISTER_CS)
		 * >>     DEFINE_REGISTER_ADDRESS(CFI_386_UNWIND_REGISTER_SS)
		 * >>     DEFINE_REGISTER_ADDRESS(CFI_386_UNWIND_REGISTER_DS)
		 * >>     DEFINE_REGISTER_ADDRESS(CFI_386_UNWIND_REGISTER_FS)
		 * >>     DEFINE_REGISTER_ADDRESS(CFI_386_UNWIND_REGISTER_GS)
		 * >> #undef DEFINE_REGISTER_ADDRESS
		 * >>     nop  // So that a return-pc directed at `MyRegisterUnwindFunction'
		 * >>          // shows up properly in backtraced
		 * >> PUBLIC_FUNCTION(MyRegisterUnwindFunction)
		 * >>     
		 * >>     .cfi_endproc
		 * >> END(MyRegisterUnwindFunction)
		 */
		TRACE("UNWIND(cfa=%p)\n", cfa);
		if unlikely(!(*reg_setter)(reg_setter_arg,
		                           CFI_UNWIND_REGISTER_SP,
		                           &cfa))
			ERROR(err_invalid_register);
	}
done:
	return result;
err_segfault:
	return UNWIND_SEGFAULT;
err_invalid_register:
	return UNWIND_INVALID_REGISTER;
err_noaddr_register:
	return UNWIND_APPLY_NOADDR_REGISTER;
}

#undef cfi_unwind_local_register_uncommon2dw
#undef cfi_unwind_local_register_common2dw
#undef libuw_unwind_local_fde_exec_until
#undef CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT
#undef CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT
#undef CFI_UNWIND_LOCAL_COMMON_REGISTER_SP
#undef CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_SP

#undef EH_FRAME_CFA_SIGFRAME_APPLY
#undef EH_FRAME_CFA_APPLY

DECL_END
