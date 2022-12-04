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
#ifdef __INTELLISENSE__
#include "eh_frame.c"

#define EH_FRAME_CFA_APPLY
//#define EH_FRAME_CFA_SIGFRAME_APPLY
//#define  EH_FRAME_CFA_LANDING_APPLY
#endif /* __INTELLISENSE__ */

#if (defined(EH_FRAME_CFA_APPLY) +          \
     defined(EH_FRAME_CFA_SIGFRAME_APPLY) + \
     defined(EH_FRAME_CFA_LANDING_APPLY)) != 1
#error "Must #define exactly one of these macros"
#endif /* ... */


DECL_BEGIN

#ifdef EH_FRAME_CFA_APPLY
#ifdef CFI_UNWIND_COMMON_REGISTER_SP
#define LOCAL_CFI_UNWIND_COMMON_REGISTER_SP      CFI_UNWIND_COMMON_REGISTER_SP
#else /* CFI_UNWIND_COMMON_REGISTER_SP */
#define LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_SP    CFI_UNWIND_UNCOMMON_REGISTER_SP
#endif /* !CFI_UNWIND_COMMON_REGISTER_SP */
#define LOCAL_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT   CFI_UNWIND_COMMON_REGISTER_MAXCOUNT
#define LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT
#define local_cfi_unwind_register_common2dw      cfi_unwind_register_common2dw
#define local_cfi_unwind_register_uncommon2dw    cfi_unwind_register_uncommon2dw
#define local_libuw_unwind_fde_exec_until        libuw_unwind_fde_exec_until
#elif defined(EH_FRAME_CFA_SIGFRAME_APPLY)
#ifdef CFI_UNWIND_SIGFRAME_COMMON_REGISTER_SP
#define LOCAL_CFI_UNWIND_COMMON_REGISTER_SP      CFI_UNWIND_SIGFRAME_COMMON_REGISTER_SP
#else /* CFI_UNWIND_SIGFRAME_COMMON_REGISTER_SP */
#define LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_SP    CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_SP
#endif /* !CFI_UNWIND_SIGFRAME_COMMON_REGISTER_SP */
#define LOCAL_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT   CFI_UNWIND_SIGFRAME_COMMON_REGISTER_MAXCOUNT
#define LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MAXCOUNT
#define local_cfi_unwind_register_common2dw      cfi_unwind_sigframe_register_common2dw
#define local_cfi_unwind_register_uncommon2dw    cfi_unwind_sigframe_register_uncommon2dw
#define local_libuw_unwind_fde_exec_until        libuw_unwind_sigframe_fde_exec_until
#elif defined(EH_FRAME_CFA_LANDING_APPLY)
#ifdef CFI_UNWIND_LANDING_COMMON_REGISTER_SP
#define LOCAL_CFI_UNWIND_COMMON_REGISTER_SP      CFI_UNWIND_LANDING_COMMON_REGISTER_SP
#else /* CFI_UNWIND_LANDING_COMMON_REGISTER_SP */
#define LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_SP    CFI_UNWIND_LANDING_UNCOMMON_REGISTER_SP
#endif /* !CFI_UNWIND_LANDING_COMMON_REGISTER_SP */
#define LOCAL_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT   CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT
#define LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT
#define local_cfi_unwind_register_common2dw      cfi_unwind_landing_register_common2dw
#define local_cfi_unwind_register_uncommon2dw    cfi_unwind_landing_register_uncommon2dw
#endif /* ... */

#if LOCAL_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT != 0
#define LOCAL_IF_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT(...) __VA_ARGS__
#else /* LOCAL_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT != 0 */
#define LOCAL_IF_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT(...) /* nothing */
#endif /* LOCAL_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT == 0 */
#if LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT != 0
#define LOCAL_IF_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT(...) __VA_ARGS__
#else /* LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT != 0 */
#define LOCAL_IF_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT(...) /* nothing */
#endif /* LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT == 0 */



#ifndef EH_FRAME_CFA_LANDING_APPLY
#ifdef EH_FRAME_CFA_APPLY
/* Execute CFA state  instruction until `absolute_pc'  has been  reached,
 * or  the entirety of  the FDE instruction code  has been executed. This
 * function is used to fill in CFA state information at a given  address,
 * which can then be used to unwind  a register state for the purpose  of
 * implementing language-level, zero-effort exception support, as well as
 * for generating tracebacks when combined with `libdebuginfo.so'
 * NOTE: Usually, the caller will have already ensured that:
 *       `self->f_pcstart <= absolute_pc && self->f_pcend >= absolute_pc'
 * @param: self:   The FDE to execute in search of `absolute_pc'
 * @param: result: CFA state descriptor, to-be filled with restore information upon success.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
INTERN NONNULL((1, 2)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_fde_exec)(unwind_fde_t *__restrict self, /* Only non-const for lazy initialized fields! */
                                      unwind_cfa_state_t *__restrict result,
                                      void const *absolute_pc)
#elif defined(EH_FRAME_CFA_SIGFRAME_APPLY)
/* Behaves  identical to `unwind_fde_exec()', and doesn't actually ever have to be
 * used, but performes better than `unwind_fde_exec()' when unwinding SIGNAL_FRAME
 * FDE  descriptors (though again:  use of this is  entirely optional; the regular
 * `unwind_fde_exec()' is just as capable  of unwinding signal frame  descriptors.
 * This function is  merely optimized  to better restore  registers commonly  used
 * within signal frames)
 * @param: self:   The FDE to execute in search of `absolute_pc'
 * @param: result: CFA state descriptor, to-be filled with restore information upon success.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
INTERN NONNULL((1, 2)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_fde_sigframe_exec)(unwind_fde_t *__restrict self, /* Only non-const for lazy initialized fields! */
                                               unwind_cfa_sigframe_state_t *__restrict result,
                                               void const *absolute_pc)
#endif /* ... */
{
	unwind_errno_t error;
	bzero(result, sizeof(*result));

	/* Execute the init-body */
	error = local_libuw_unwind_fde_exec_until(self,
	                                          LOCAL_IF_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT(NULL,)
	                                          LOCAL_IF_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT(NULL,)
	                                          self->f_inittext,
	                                          self->f_inittextend,
	                                          result,
	                                          (void *)-1);
	if likely(error == UNWIND_SUCCESS) {
		LOCAL_IF_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT(unwind_cfa_register_t common_init_regs[LOCAL_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT];)
		LOCAL_IF_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT(byte_t uncommon_init_regs[(LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT + NBBY) / NBBY];)
		LOCAL_IF_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT(STATIC_ASSERT(sizeof(common_init_regs) == sizeof(result->cs_regs));)
		LOCAL_IF_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT(STATIC_ASSERT(sizeof(uncommon_init_regs) == sizeof(result->cs_uncommon));)
		LOCAL_IF_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT(memcpy(common_init_regs, result->cs_regs, sizeof(result->cs_regs));)
		LOCAL_IF_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT(memcpy(uncommon_init_regs, result->cs_uncommon, sizeof(result->cs_uncommon));)
		/* Execute the eval-body */
		error = local_libuw_unwind_fde_exec_until(self,
		                                          LOCAL_IF_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT(common_init_regs,)
		                                          LOCAL_IF_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT(uncommon_init_regs,)
		                                          self->f_evaltext,
		                                          self->f_evaltextend,
		                                          result,
		                                          absolute_pc);
	}
	TRACE("unwind_fde_exec() -> %u\n", error);
	return error;
}
#endif /* !EH_FRAME_CFA_LANDING_APPLY */



#ifndef GUARDED_MEMCPY_DEFINED
#define GUARDED_MEMCPY_DEFINED 1
INTDEF WUNUSED bool
NOTHROW(CC guarded_memcpy)(void *dst, void const *src, size_t num_bytes);
#endif /* !GUARDED_MEMCPY_DEFINED */




#ifdef EH_FRAME_CFA_APPLY
/* Apply  a given CFA  unwind state in order  to apply register information
 * from `reg_getter'  to `reg_setter'.  Note  however that  only  registers
 * with a rule other than `DW_CFA_register_rule_undefined' will be applied,
 * meaning  that `*reg_setter'  will not  get invoked  for these registers.
 * WARNING: This function will modify `self' in such a manner that repeated calls
 *          require  that `self' must be restored to its state prior to a call to
 *          this function before a repeated call can be made!
 * @param: self:        The CFA state to-be used when applying registers
 * @param: absolute_pc: Same value as was previously used to calculate `fde' from `self'
 * @return: UNWIND_SUCCESS:               ...
 * @return: UNWIND_INVALID_REGISTER:      ...
 * @return: UNWIND_SEGFAULT:              ...
 * @return: UNWIND_EMULATOR_*:            ...
 * @return: UNWIND_APPLY_NOADDR_REGISTER: ... */
INTERN NONNULL((1, 2, 4, 6)) unwind_errno_t CC
libuw_unwind_cfa_apply(unwind_cfa_state_t *__restrict self,
                       unwind_fde_t *__restrict fde, /* Only non-const for lazy initialized fields! */
                       void const *absolute_pc,
                       unwind_getreg_t reg_getter, void const *reg_getter_arg,
                       unwind_setreg_t reg_setter, void *reg_setter_arg)
#elif defined(EH_FRAME_CFA_SIGFRAME_APPLY)
/* For use with `unwind_fde_sigframe_exec()': Apply register rules previously calculated.
 * @param: self:        The CFA state to-be used when applying registers
 * @param: absolute_pc: Same value as was previously used to calculate `fde' from `self'
 * @return: UNWIND_SUCCESS:               ...
 * @return: UNWIND_INVALID_REGISTER:      ...
 * @return: UNWIND_SEGFAULT:              ...
 * @return: UNWIND_EMULATOR_*:            ...
 * @return: UNWIND_APPLY_NOADDR_REGISTER: ... */
INTERN NONNULL((1, 2, 4, 6)) unwind_errno_t CC
libuw_unwind_cfa_sigframe_apply(unwind_cfa_sigframe_state_t *__restrict self,
                                unwind_fde_t *__restrict fde, /* Only non-const for lazy initialized fields! */
                                void const *absolute_pc,
                                unwind_getreg_t reg_getter, void const *reg_getter_arg,
                                unwind_setreg_t reg_setter, void *reg_setter_arg)
#elif defined(EH_FRAME_CFA_LANDING_APPLY)
/* For use with `unwind_fde_landing_exec()': Apply register rules previously calculated.
 * @param: self:        The CFA state to-be used when applying registers
 * @param: absolute_pc: Same value as was previously used to calculate `fde' from `self'
 * @return: UNWIND_SUCCESS:               ...
 * @return: UNWIND_INVALID_REGISTER:      ...
 * @return: UNWIND_SEGFAULT:              ...
 * @return: UNWIND_EMULATOR_*:            ...
 * @return: UNWIND_APPLY_NOADDR_REGISTER: ... */
PRIVATE NONNULL((1, 2, 4, 6)) unwind_errno_t CC
_unwind_cfa_landing_apply(_unwind_cfa_landing_state_t *__restrict self,
                          unwind_fde_t *__restrict fde, /* Only non-const for lazy initialized fields! */
                          void const *absolute_pc,
                          unwind_getreg_t reg_getter, void const *reg_getter_arg,
                          unwind_setreg_t reg_setter, void *reg_setter_arg)
#endif /* ... */
{
	unsigned int i;
	unwind_errno_t result;
	uintptr_t cfa;
#ifdef LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_SP
#ifndef EH_FRAME_CFA_LANDING_APPLY
	bool has_sp_rule;
#endif /* !EH_FRAME_CFA_LANDING_APPLY */
#endif /* LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_SP */
	union {
		byte_t bytes[CFI_REGISTER_MAXSIZE];
		uintptr_t addr;
	} reg_buf;

#ifdef LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_SP
#ifndef EH_FRAME_CFA_LANDING_APPLY
	has_sp_rule = bitset_contains(self->cs_uncommon, LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_SP(fde->f_addrsize));
#endif /* !EH_FRAME_CFA_LANDING_APPLY */
#endif /* LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_SP */

	/* Step #1: Calculate the CFA (CanonicalFrameAddress) */
	result = libuw_unwind_fde_calculate_cfa(fde,
	                                        &self->cs_cfa,
	                                        reg_getter,
	                                        reg_getter_arg,
	                                        &cfa);
	TRACE("unwind_cfa_apply():unwind_fde_calculate_cfa() -> %u (%p)\n", result, cfa);
	if unlikely(result != UNWIND_SUCCESS)
		goto done;

	/* Apply common new register values. */
#if LOCAL_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT != 0
	for (i = 0; i < LOCAL_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT; ++i) {
		unwind_regno_t dw_regno;
		unwind_cfa_register_t *rule;
		dw_regno = local_cfi_unwind_register_common2dw(fde->f_addrsize, i);
		rule     = &self->cs_regs[i];
		TRACE("UNWIND(reg: %u, rule: %u)\n",
		      (unsigned int)dw_regno,
		      (unsigned int)rule->cr_rule);
		switch (rule->cr_rule) {

		case DW_CFA_register_rule_register:
			result = (*reg_getter)(reg_getter_arg, (unwind_regno_t)rule->cr_value, reg_buf.bytes);
			if unlikely(result != UNWIND_SUCCESS)
				ERRORF(done, "regno=%u (%u)\n", (unsigned int)rule->cr_value, result);
			result = (*reg_setter)(reg_setter_arg, dw_regno, reg_buf.bytes);
			if unlikely(result != UNWIND_SUCCESS)
				ERRORF(done, "regno=%u (%u)\n", (unsigned int)dw_regno, result);
			break;

		case DW_CFA_register_rule_offsetn: {
			void const *addr;
			if unlikely(OVERFLOW_SADD((intptr_t)cfa, (intptr_t)rule->cr_value, (intptr_t *)&reg_buf.addr))
				ERRORF(err_segfault, "cfa=%p, cr_value=%p\n", cfa, rule->cr_value);
			addr = (void const *)reg_buf.addr;
#ifndef CFI_REGISTER_MEMSIZE_IS_SIZE
			bzero(reg_buf.bytes, sizeof(reg_buf.bytes));
#endif /* !CFI_REGISTER_MEMSIZE_IS_SIZE */
			if unlikely(!guarded_memcpy(reg_buf.bytes, addr, CFI_REGISTER_MEMSIZE(fde->f_addrsize, dw_regno))) {
				ERRORF(err_segfault, "reg_buf.addr=%p, cfa=%p, cr_value=%p, cv_type=%u, cv_reg=%u, cv_value=%p\n",
				       reg_buf.addr, cfa, rule->cr_value,
				       (unsigned int)self->cs_cfa.cv_type,
				       (unsigned int)self->cs_cfa.cv_reg,
				       (uintptr_t)self->cs_cfa.cv_value);
			}
			result = (*reg_setter)(reg_setter_arg, dw_regno, reg_buf.bytes);
			if unlikely(result != UNWIND_SUCCESS)
				ERRORF(done, "regno=%u (%u)\n", (unsigned int)dw_regno, result);
		}	break;

		case DW_CFA_register_rule_val_offsetn:
			if unlikely(CFI_REGISTER_SIZE(fde->f_addrsize, dw_regno) != sizeof(uintptr_t))
				ERRORF(err_noaddr_register, "regno=%u\n", (unsigned int)dw_regno);
			/* No overflow checks here, because we don't reference the memory. */
			reg_buf.addr = cfa + rule->cr_value;
			result = (*reg_setter)(reg_setter_arg, dw_regno, reg_buf.bytes);
			if unlikely(result != UNWIND_SUCCESS)
				ERRORF(done, "regno=%u (%u)\n", (unsigned int)dw_regno, result);
			break;

		case DW_CFA_register_rule_val_expression:
			if unlikely(CFI_REGISTER_SIZE(fde->f_addrsize, dw_regno) != sizeof(uintptr_t)) {
				/* XXX: Wouldn't DW_OP_piece be used for this? */
				ERRORF(err_noaddr_register, "regno=%u\n", (unsigned int)dw_regno);
			}
			result = execute_eh_frame_expression(fde,
			                                     rule->cr_expr,
			                                     reg_getter,
			                                     reg_getter_arg,
			                                     &reg_buf.addr,
			                                     cfa);
			if unlikely(result != UNWIND_SUCCESS)
				goto done;
			result = (*reg_setter)(reg_setter_arg, dw_regno, reg_buf.bytes);
			if unlikely(result != UNWIND_SUCCESS)
				ERRORF(done, "regno=%u (%u)\n", (unsigned int)dw_regno, result);
			break;

		case DW_CFA_register_rule_expression: {
			void const *addr;
			result = execute_eh_frame_expression(fde,
			                                     rule->cr_expr,
			                                     reg_getter,
			                                     reg_getter_arg,
			                                     &reg_buf.addr,
			                                     cfa);
			if unlikely(result != UNWIND_SUCCESS)
				goto done;
			assert(sizeof(reg_buf.bytes) >= CFI_REGISTER_MEMSIZE(fde->f_addrsize, dw_regno));
			addr = (void const *)reg_buf.addr;
#ifndef CFI_REGISTER_MEMSIZE_IS_SIZE
			bzero(reg_buf.bytes, sizeof(reg_buf.bytes));
#endif /* !CFI_REGISTER_MEMSIZE_IS_SIZE */
			if unlikely(!guarded_memcpy(reg_buf.bytes, addr, CFI_REGISTER_MEMSIZE(fde->f_addrsize, dw_regno))) {
				ERRORF(err_segfault, "regno=%u, src=%p, num_bytes=%" PRIuSIZ "\n",
				       (unsigned int)dw_regno, (void const *)reg_buf.addr,
				       (size_t)CFI_REGISTER_MEMSIZE(fde->f_addrsize, dw_regno));
			}
			result = (*reg_setter)(reg_setter_arg, dw_regno, reg_buf.bytes);
			if unlikely(result != UNWIND_SUCCESS)
				ERRORF(done, "regno=%u (%u)\n", (unsigned int)dw_regno, result);
		}	break;

		default: break;
		}
	}
#endif /* LOCAL_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT != 0 */

#if LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT != 0
	if (bitset_contains(self->cs_uncommon, LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT)) {
		for (i = 0; i < LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT; ++i) {
			unwind_regno_t dw_regno;
			unwind_cfa_register_t rule;
			if (!bitset_contains(self->cs_uncommon, i))
				continue; /* Not this one... */
			dw_regno = local_cfi_unwind_register_uncommon2dw(fde->f_addrsize, i);
			DOTRACE("Uncommon register used: %u (%u)\n", (unsigned int)dw_regno, (unsigned int)i);
			result = libuw_unwind_fde_rule(fde, &rule, dw_regno, absolute_pc);
			if unlikely(result != UNWIND_SUCCESS)
				goto done;
			TRACE("UNWIND(reg: %u, rule: %u)\n",
			      (unsigned int)dw_regno,
			      (unsigned int)rule.cr_rule);
			switch (rule.cr_rule) {

			case DW_CFA_register_rule_register:
				result = (*reg_getter)(reg_getter_arg, (unwind_regno_t)rule.cr_value, reg_buf.bytes);
				if unlikely(result != UNWIND_SUCCESS)
					ERRORF(done, "regno=%u (%u)\n", (unsigned int)rule.cr_value, result);
				result = (*reg_setter)(reg_setter_arg, dw_regno, reg_buf.bytes);
				if unlikely(result != UNWIND_SUCCESS)
					ERRORF(done, "regno=%u (%u)\n", (unsigned int)dw_regno, result);
				break;

			case DW_CFA_register_rule_offsetn: {
				void const *addr;
				if unlikely(OVERFLOW_SADD((intptr_t)cfa, (intptr_t)rule.cr_value, (intptr_t *)&reg_buf.addr))
					ERRORF(err_segfault, "cfa=%p, cr_value=%p\n", cfa, rule.cr_value);
				addr = (void const *)reg_buf.addr;
#ifndef CFI_REGISTER_MEMSIZE_IS_SIZE
				bzero(reg_buf.bytes, sizeof(reg_buf.bytes));
#endif /* !CFI_REGISTER_MEMSIZE_IS_SIZE */
				if unlikely(!guarded_memcpy(reg_buf.bytes, addr, CFI_REGISTER_MEMSIZE(fde->f_addrsize, dw_regno))) {
					ERRORF(err_segfault, "reg_buf.addr=%p, cfa=%p, cr_value=%p, cv_type=%u, cv_reg=%u, cv_value=%p\n",
					       reg_buf.addr, cfa, rule.cr_value,
					       (unsigned int)self->cs_cfa.cv_type,
					       (unsigned int)self->cs_cfa.cv_reg,
					       (uintptr_t)self->cs_cfa.cv_value);
				}
				result = (*reg_setter)(reg_setter_arg, dw_regno, reg_buf.bytes);
				if unlikely(result != UNWIND_SUCCESS)
					ERRORF(done, "regno=%u (%u)\n", (unsigned int)dw_regno, result);
			}	break;

			case DW_CFA_register_rule_val_offsetn:
				if unlikely(CFI_REGISTER_SIZE(fde->f_addrsize, dw_regno) != sizeof(uintptr_t))
					ERRORF(err_noaddr_register, "regno=%u\n", (unsigned int)dw_regno);
				/* No overflow checks here, because we don't reference the memory. */
				reg_buf.addr = cfa + rule.cr_value;
				result = (*reg_setter)(reg_setter_arg, dw_regno, reg_buf.bytes);
				if unlikely(result != UNWIND_SUCCESS)
					ERRORF(done, "regno=%u (%u)\n", (unsigned int)dw_regno, result);
				break;

			case DW_CFA_register_rule_val_expression:
				if unlikely(CFI_REGISTER_SIZE(fde->f_addrsize, dw_regno) != sizeof(uintptr_t)) {
					/* XXX: Wouldn't DW_OP_piece be used for this? */
					ERRORF(err_noaddr_register, "regno=%u\n", (unsigned int)dw_regno);
				}
				result = execute_eh_frame_expression(fde,
				                                     rule.cr_expr,
				                                     reg_getter,
				                                     reg_getter_arg,
				                                     &reg_buf.addr,
				                                     cfa);
				if unlikely(result != UNWIND_SUCCESS)
					goto done;
				result = (*reg_setter)(reg_setter_arg, dw_regno, reg_buf.bytes);
				if unlikely(result != UNWIND_SUCCESS)
					ERRORF(done, "regno=%u (%u)\n", (unsigned int)dw_regno, result);
				break;

			case DW_CFA_register_rule_expression: {
				void const *addr;
				result = execute_eh_frame_expression(fde,
				                                     rule.cr_expr,
				                                     reg_getter,
				                                     reg_getter_arg,
				                                     &reg_buf.addr,
				                                     cfa);
				if unlikely(result != UNWIND_SUCCESS)
					goto done;
				assert(sizeof(reg_buf.bytes) >= CFI_REGISTER_MEMSIZE(fde->f_addrsize, dw_regno));
				addr = (void const *)reg_buf.addr;
#ifndef CFI_REGISTER_MEMSIZE_IS_SIZE
				bzero(reg_buf.bytes, sizeof(reg_buf.bytes));
#endif /* !CFI_REGISTER_MEMSIZE_IS_SIZE */
				if unlikely(!guarded_memcpy(reg_buf.bytes, addr, CFI_REGISTER_MEMSIZE(fde->f_addrsize, dw_regno))) {
					ERRORF(err_segfault, "regno=%u, src=%p, num_bytes=%" PRIuSIZ "\n",
					       (unsigned int)dw_regno, (void const *)reg_buf.addr,
					       (size_t)CFI_REGISTER_MEMSIZE(fde->f_addrsize, dw_regno));
				}
				result = (*reg_setter)(reg_setter_arg, dw_regno, reg_buf.bytes);
				if unlikely(result != UNWIND_SUCCESS)
					ERRORF(done, "regno=%u (%u)\n", (unsigned int)dw_regno, result);
			}	break;

			default: break;
			}
		}
	}
#endif /* LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT != 0 */

	assertf(self->cs_cfa.cv_type != UNWIND_CFA_VALUE_UNSET,
	        "No CFA for %p...%p (GDB doesn't like this)",
	        fde->f_pcstart, (byte_t const *)fde->f_pcend - 1);

#ifndef EH_FRAME_CFA_LANDING_APPLY
	/* Set the new CFA value as content of the SP register. */
	if (self->cs_cfa.cv_type != UNWIND_CFA_VALUE_UNSET &&
	    /* Only  apply  if no  other register  rule was  already defined  for SP
	     * This allows users to  satisfy gdb by providing  a CFA rule but  still
	     * provide a value for SP by providing an explicit register rule for it. */
#ifdef LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_SP
	    !has_sp_rule
#elif defined(LOCAL_CFI_UNWIND_COMMON_REGISTER_SP)
	    (self->cs_regs[LOCAL_CFI_UNWIND_COMMON_REGISTER_SP(fde->f_addrsize)].cr_rule == DW_CFA_register_rule_undefined)
#endif /* ... */
	    ) {
		/* Check if we should apply signal frame transformations.
		 * Note that we only do this if we have a CFA rule and do intend on applying it.
		 * In  any other case, applying sigframe transformation wouldn't make any sense,
		 * and would even cause problems by interfering with GDB erroring out with:
		 *   - Backtrace stopped: previous frame inner to this frame (corrupt stack?)
		 * This can be caused when one frame's return-SP is greater than it's caller,
		 * which  should normally never be the case,  but can happen when a custom-SP
		 * restore rule was defined.
		 * Right now, GDB allows SP to be any value during unwind when either the called,
		 * or the calling frame are marked as .cfi_signal_frame.
		 * In  my opinion, this should be loosened a bit to only stop unwinding if the fully
		 * unwound frame ends up being a carbon copy of a previous frame, rather than always
		 * failing when SP isn't where GDB would like it to be at.
		 * Anyways, what you as a KOS developer should take away from this is:
		 *   - Any custom assembly  function that  assigns a  new ESP  from either  another
		 *     stack, or somewhere further up the stack must be marked as .cfi_signal_frame
		 *   - The KOS unwind mechanism will ignore .cfi_def_cfa and .cfi_signal_frame when
		 *     another rule  exists  that  assigns explicit  unwinding  behavior  for  %esp
		 *   - GDB  will _NOT_ working properly unless every  function has a CFA rule defined.
		 *     For this purpose, you can usually use `.cfi_def_cfa %esp, 0', however be warned
		 *     that  the value of  this expression is used  as the FRAME-ID  which GDB uses to
		 *     identify frames, so try to keep its value unique, I guess...
		 *   - With all of this in mind, a custom register restore function would look like this:
		 * >>     .cfi_startproc simple
		 * >>     .cfi_def_cfa %esp, 0
		 * >>     .cfi_signal_frame
		 * >> #define DEFINE_REGISTER_ADDRESS(reg) \
		 * >>     .cfi_escape DW_CFA_expression;   \
		 * >>     .cfi_escape reg;                 \
		 * >>     .cfi_escape ...;                 \
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
		 * >>          // shows up properly in backtraces
		 * >> PUBLIC_FUNCTION(MyRegisterUnwindFunction)
		 * >>     ...
		 * >>     .cfi_endproc
		 * >> END(MyRegisterUnwindFunction)
		 */
		TRACE("UNWIND(cfa=%p)\n", cfa);
		result = (*reg_setter)(reg_setter_arg, CFI_UNWIND_REGISTER_SP(fde->f_addrsize), &cfa);
		if unlikely(result != UNWIND_SUCCESS)
			ERRORF(done, "regno=%u (%u)\n", (unsigned int)CFI_UNWIND_REGISTER_SP(fde->f_addrsize), result);
	}
#endif /* !EH_FRAME_CFA_LANDING_APPLY */
done:
	return result;
err_segfault:
	return UNWIND_SEGFAULT;
err_noaddr_register:
	return UNWIND_APPLY_NOADDR_REGISTER;
}

#undef local_cfi_unwind_register_uncommon2dw
#undef local_cfi_unwind_register_common2dw
#undef local_libuw_unwind_fde_exec_until
#undef LOCAL_IF_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT
#undef LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT
#undef LOCAL_IF_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT
#undef LOCAL_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT
#undef LOCAL_CFI_UNWIND_COMMON_REGISTER_SP
#undef LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_SP

#undef EH_FRAME_CFA_LANDING_APPLY
#undef EH_FRAME_CFA_SIGFRAME_APPLY
#undef EH_FRAME_CFA_APPLY

DECL_END
