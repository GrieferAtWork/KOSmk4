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
//#define EH_FRAME_FDE_EXEC_CFA_STATE 1
//#define EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE 1
//#define EH_FRAME_FDE_EXEC_CFA_VALUE 1
#define EH_FRAME_FDE_EXEC_CFA_RULE 1
//#define EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT 1
#endif

#ifdef __KERNEL__
#include <sched/task.h>        /* stack_avail() */
#include <alloca.h>
#else /* __KERNEL__ */
#include <malloc.h>
#endif /* !__KERNEL__ */

#include <string.h>
#include <hybrid/overflow.h>

#if (defined(EH_FRAME_FDE_EXEC_CFA_STATE) + \
     defined(EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE) + \
     defined(EH_FRAME_FDE_EXEC_CFA_VALUE) + \
     defined(EH_FRAME_FDE_EXEC_CFA_RULE) + \
     defined(EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT)) != 1
#error "Invalid configuration"
#endif


DECL_BEGIN

#ifdef EH_FRAME_FDE_EXEC_CFA_STATE
#define SYM(x) cfa_state_##x
#elif defined(EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE)
#define SYM(x) cfa_sigframe_state_##x
#elif defined(EH_FRAME_FDE_EXEC_CFA_VALUE)
#define SYM(x) cfa_value_##x
#elif defined(EH_FRAME_FDE_EXEC_CFA_RULE)
#define SYM(x) cfa_rule_##x
#elif defined(EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT)
#define SYM(x) landing_pad_##x
#endif /* ... */

typedef struct SYM(unwind_cfa_backup_state_struct) SYM(unwind_cfa_backup_state_t);
struct SYM(unwind_cfa_backup_state_struct) {
#ifdef EH_FRAME_FDE_EXEC_CFA_STATE
	unwind_cfa_state_t              cbs_backup; /* Backup data. */
#elif defined(EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE)
	unwind_cfa_sigframe_state_t     cbs_backup; /* Backup data. */
#elif defined(EH_FRAME_FDE_EXEC_CFA_VALUE)
	unwind_cfa_value_t              cbs_backup; /* Backup data. */
#elif defined(EH_FRAME_FDE_EXEC_CFA_RULE)
	unwind_cfa_register_t           cbs_backup; /* Backup data. */
#elif defined(EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT)
	uintptr_t                       cbs_backup; /* Backup data. */
#endif /* ... */
	SYM(unwind_cfa_backup_state_t) *cbs_prev;   /* [0..1] Previous backup */
};

#ifndef __KERNEL__
PRIVATE void
NOTHROW_NCX(CC SYM(unwind_cfa_backup_state_freechain))(SYM(unwind_cfa_backup_state_t) *base) {
	SYM(unwind_cfa_backup_state_t) *next;
	while (base) {
		next = base->cbs_prev;
		free(base);
		base = next;
	}
}
#endif


#if defined(EH_FRAME_FDE_EXEC_CFA_STATE) || \
    defined(EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE)
#ifdef EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE
#define CFI_UNWIND_LOCAL_CFA_STATE_T             unwind_cfa_sigframe_state_t
#define CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT   CFI_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT
#define CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT
#define cfi_unwind_local_register_dw2common      cfi_unwind_sigframe_register_dw2common
#define cfi_unwind_local_register_dw2uncommon    cfi_unwind_sigframe_register_dw2uncommon
#else /* EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE */
#define CFI_UNWIND_LOCAL_CFA_STATE_T             unwind_cfa_state_t
#define CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT   CFI_UNWIND_COMMON_REGISTER_COUNT
#define CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT CFI_UNWIND_UNCOMMON_REGISTER_COUNT
#define cfi_unwind_local_register_dw2common      cfi_unwind_register_dw2common
#define cfi_unwind_local_register_dw2uncommon    cfi_unwind_register_dw2uncommon
#endif /* !EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE */


#if CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT == 0 && \
    CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT == 0
#ifdef EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE
#error "Neither common, nor uncommon registers defined for SIGFRAME"
#else /* EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE */
#error "Neither common, nor uncommon registers defined for NORMAL"
#endif /* !EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE */
#endif /* ... */


#if CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT != 0
PRIVATE NONNULL((1)) void
NOTHROW_NCX(CC SYM(set_common_order_ffh))(CFI_UNWIND_LOCAL_CFA_STATE_T *__restrict self,
                                          uintptr_half_t com_regno) {
	unwind_order_index_t base;
	uintptr_half_t i;
	base = self->cs_regs[com_regno].cr_order;
	for (i = 0; i < CFI_UNWIND_COMMON_REGISTER_COUNT; ++i) {
		if (self->cs_regs[i].cr_order > base)
			--self->cs_regs[i].cr_order;
	}
#if CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT != 0
	for (i = 0; i < CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT; ++i) {
		if (self->cs_uncorder[i] > base)
			--self->cs_uncorder[i];
	}
#endif /* CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT != 0 */
	self->cs_regs[com_regno].cr_order = (unwind_order_index_t)-1;
}
#endif /* CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT != 0 */

#if CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0
PRIVATE NONNULL((1)) void
NOTHROW_NCX(CC SYM(set_uncommon_order_ffh))(CFI_UNWIND_LOCAL_CFA_STATE_T *__restrict self,
                                            uintptr_half_t uncom_regno) {
	unwind_order_index_t base;
	uintptr_half_t i;
	base = self->cs_uncorder[uncom_regno];
	for (i = 0; i < CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT; ++i) {
		if (self->cs_uncorder[i] > base)
			--self->cs_uncorder[i];
	}
#if CFI_UNWIND_COMMON_REGISTER_COUNT != 0
	for (i = 0; i < CFI_UNWIND_COMMON_REGISTER_COUNT; ++i) {
		if (self->cs_regs[i].cr_order > base)
			--self->cs_regs[i].cr_order;
	}
#endif /* CFI_UNWIND_COMMON_REGISTER_COUNT != 0 */
	self->cs_uncorder[uncom_regno] = (unwind_order_index_t)-1;
}
#endif /* CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0 */

#undef CFI_UNWIND_LOCAL_CFA_STATE_T
#endif /* EH_FRAME_FDE_EXEC_CFA_STATE || EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE */


#ifdef EH_FRAME_FDE_EXEC_CFA_STATE
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
PRIVATE
#if CFI_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT != 0 && CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT != 0
	NONNULL((1, 4, 5, 6, 7))
#elif CFI_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT != 0 || CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT != 0
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
                                            uintptr_half_t *uncommon_init_regs,
#endif /* CFI_UNWIND_UNCOMMON_REGISTER_COUNT != 0 */
                                            unwind_order_index_t *__restrict porder,
                                            byte_t *__restrict reader,
                                            byte_t *__restrict end,
                                            unwind_cfa_state_t *__restrict result,
                                            void *absolute_pc)
#elif defined(EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE)
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
                                                     uintptr_half_t *uncommon_init_regs,
#endif /* CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT != 0 */
                                                     unwind_order_index_t *__restrict porder,
                                                     byte_t *__restrict reader,
                                                     byte_t *__restrict end,
                                                     unwind_cfa_sigframe_state_t *__restrict result,
                                                     void *absolute_pc)
#elif defined(EH_FRAME_FDE_EXEC_CFA_VALUE)
/* Same as `unwind_fde_exec()', however only calculate the CFA restore descriptor.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
PRIVATE NONNULL((1, 2, 3, 4)) unsigned int
NOTHROW_NCX(CC libuw_unwind_fde_exec_cfa_until)(unwind_fde_t const *__restrict self,
                                                byte_t *__restrict reader,
                                                byte_t *__restrict end,
                                                unwind_cfa_value_t *__restrict result,
                                                void *absolute_pc)
#elif defined(EH_FRAME_FDE_EXEC_CFA_RULE)
/* Similar to `unwind_fde_exec()', but used to calculate the
 * unwind rule for `dw_regno' at the given text location.
 * This is used to implement unwinding for uncommon registers,
 * since `unwind_fde_exec()' will not already calculate these
 * during the first pass (thus keeping down the memory requirements
 * imposed on the one responsible for allocating `unwind_cfa_state_t')
 * @param: self: The FDE to execute in search of `absolute_pc'
 * @param: rule: The CFA register result controller to-be filled.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
PRIVATE NONNULL((1, 2, 3, 4)) unsigned int
NOTHROW_NCX(CC libuw_unwind_fde_exec_rule_until)(unwind_fde_t const *__restrict self,
                                                 byte_t *__restrict reader,
                                                 byte_t *__restrict end,
                                                 unwind_cfa_register_t *__restrict rule,
                                                 uintptr_half_t dw_regno,
                                                 void *absolute_pc)
#elif defined(EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT)
/* Similar to `unwind_fde_exec()', but only decode `DW_CFA_GNU_args_size' instructions
 * in order to calculate the proper exception_handler landing-pad-stack-adjustment that
 * is required to re-align the stack before jumping to a local exception handler.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
INTERN NONNULL((1, 2)) unsigned int
NOTHROW_NCX(LIBUNWIND_CC libuw_unwind_fde_exec_landing_pad_adjustment)(unwind_fde_t const *__restrict self,
                                                                       uintptr_t *__restrict psp_adjustment,
                                                                       void *absolute_pc)
#endif /* ... */
{
#ifdef EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT
	byte_t *reader = self->f_evaltext;
	byte_t *end    = self->f_evaltextend;
#endif /* EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT */
	uintptr_t current_pc;
#ifdef EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT
	uintptr_t result = 0;
#endif /* EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT */
	SYM(unwind_cfa_backup_state_t) *state_backup_list = NULL;
	SYM(unwind_cfa_backup_state_t) *state_backup_free = NULL; /* Free list of state backups. */
	assertf(((uintptr_t)absolute_pc >= (uintptr_t)self->f_pcstart &&
	         (uintptr_t)absolute_pc <= (uintptr_t)self->f_pcend) ||
	        (absolute_pc == (void *)-1),
	        "self->f_pcstart = %p\n"
	        "self->f_pcend   = %p\n"
	        "absolute_pc     = %p\n",
	        self->f_pcstart, self->f_pcend, absolute_pc);
	current_pc = (uintptr_t)self->f_pcstart;
#if defined(EH_FRAME_FDE_EXEC_CFA_STATE) || defined(EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE)

#if CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT != 0
#if CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0
#define SET_REGISTER(dw_regid, ...)                                       \
	{                                                                     \
		uintptr_half_t temp;                                              \
		temp = cfi_unwind_local_register_dw2common(dw_regid);             \
		if likely(temp < CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT) {        \
			/* Common register */                                         \
			unwind_cfa_register_t *rule;                                  \
			rule = &result->cs_regs[temp];                                \
			if unlikely(*porder == (unwind_order_index_t)-1) {            \
				SYM(set_common_order_ffh)(result, temp);                  \
			} else {                                                      \
				rule->cr_order = ++*porder;                               \
			}                                                             \
			__VA_ARGS__;                                                  \
		} else {                                                          \
			temp = cfi_unwind_local_register_dw2uncommon(dw_regid);       \
			if unlikely(temp >= CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT) \
				ERROR(err_invalid_register);                              \
			/* Uncommon register */                                       \
			if unlikely(*porder == (unwind_order_index_t)-1) {            \
				SYM(set_uncommon_order_ffh)(result, temp);                \
			} else {                                                      \
				result->cs_uncorder[temp] = ++*porder;                    \
			}                                                             \
		}                                                                 \
	}
#else /* CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0 */
#define SET_REGISTER(dw_regid, ...)                                \
	{                                                              \
		uintptr_half_t temp;                                       \
		temp = cfi_unwind_local_register_dw2common(dw_regid);      \
		if likely(temp < CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT) { \
			/* Common register */                                  \
			unwind_cfa_register_t *rule;                           \
			rule           = &result->cs_regs[temp];               \
			if unlikely(*porder == (unwind_order_index_t)-1) {     \
				SYM(set_common_order_ffh)(result, temp);           \
			} else {                                               \
				rule->cr_order = ++*porder;                        \
			}                                                      \
			__VA_ARGS__;                                           \
		} else {                                                   \
			ERROR(err_invalid_register);                           \
		}                                                          \
	}
#endif /* CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT == 0 */
#else /* CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT != 0 */
#if CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0
#define SET_REGISTER(dw_regid, ...)                                   \
	{                                                                 \
		uintptr_half_t temp;                                          \
		temp = cfi_unwind_local_register_dw2uncommon(dw_regid);       \
		if unlikely(temp >= CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT) \
			ERROR(err_invalid_register);                              \
		/* Uncommon register */                                       \
		if unlikely(*porder == (unwind_order_index_t)-1) {            \
			SYM(set_uncommon_order_ffh)(result, temp);                \
		} else {                                                      \
			result->cs_uncorder[temp] = ++*porder;                    \
		}                                                             \
	}
#else /* CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0 */
#define SET_REGISTER(dw_regid, ...)  \
	{                                \
		ERROR(err_invalid_register); \
	}
#endif /* CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT == 0 */
#endif /* CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT == 0 */
#elif defined(EH_FRAME_FDE_EXEC_CFA_RULE)
#define SET_REGISTER(dw_regid, ...)   \
	{                                 \
		if ((dw_regid) == dw_regno) { \
			/* Common register */     \
			__VA_ARGS__;              \
		}                             \
	}
#endif /* ... */
	while (reader < end && current_pc <= (uintptr_t)absolute_pc) {
		uint8_t opcode, operand;
		opcode  = *reader++;
		operand = opcode & 0x3f;
		opcode  = opcode & 0xc0;
		if (opcode == DW_CFA_advance_loc) {
			TRACE("DW_CFA_advance_loc\n");
			current_pc += (uintptr_t)operand * self->f_codealign;
		} else if (opcode == DW_CFA_offset) {
			TRACE("DW_CFA_offset(%I8u)\n", operand);
			{
#if defined(EH_FRAME_FDE_EXEC_CFA_STATE) || \
    defined(EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE) || \
    defined(EH_FRAME_FDE_EXEC_CFA_RULE)
				intptr_t value;
				value = ((intptr_t)dwarf_decode_uleb128((byte_t **)&reader) * self->f_dataalign);
				SET_REGISTER(operand, {
					rule->cr_rule  = DW_CFA_register_rule_offsetn;
					rule->cr_value = value;
				});
#else /* ... */
				dwarf_decode_uleb128((byte_t **)&reader);
#endif /* !... */
			}
		} else if (opcode == DW_CFA_restore) {
			TRACE("DW_CFA_restore\n");
#if defined(EH_FRAME_FDE_EXEC_CFA_STATE) || \
    defined(EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE)
			{
				uintptr_half_t temp;
#if CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT != 0
				temp = cfi_unwind_local_register_dw2common(operand);
				if likely(temp < CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT) {
					/* Common register */
					if unlikely(!common_init_regs) {
						memset(&result->cs_regs[temp], 0, sizeof(result->cs_regs[temp]));
					} else {
						memcpy(&result->cs_regs[temp], &common_init_regs[temp],
						       sizeof(result->cs_regs[temp]));
					}
				} else
#endif /* CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT != 0 */
				{
#if CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0
					temp = cfi_unwind_local_register_dw2uncommon(operand);
					if unlikely(temp >= CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT)
						ERROR(err_invalid_register);
					if unlikely(!uncommon_init_regs) {
						result->cs_uncorder[temp] = 0;
					} else {
						result->cs_uncorder[temp] = uncommon_init_regs[temp];
					}
#else /* CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0 */
					ERROR(err_invalid_register);
#endif /* CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT == 0 */
				}
			}
#elif defined(EH_FRAME_FDE_EXEC_CFA_RULE)
			if (operand == dw_regno) {
				/* Delete the restore rule, thus causing our caller `libuw_unwind_fde_rule()'
				 * to re-attempt the call using the init-body `self->f_inittext' */
				rule->cr_rule = DW_CFA_register_rule_undefined;
			}
#endif /* ... */
		} else {
			switch (operand) {

			CASE(DW_CFA_set_loc)
				/* Decode the PC pointer according to FDE pointer encoding. */
				current_pc = dwarf_decode_pointer((byte_t **)&reader,
				                                  self->f_encptr,
				                                  self->f_addrsize,
				                                  0,
				                                  0,
				                                  (uintptr_t)self->f_pcstart);
				current_pc += (uintptr_t)self->f_pcstart;
				break;

			CASE(DW_CFA_advance_loc1)
				current_pc += (uintptr_t) * (uint8_t *)reader * self->f_codealign;
				reader += 1;
				break;

			CASE(DW_CFA_advance_loc2)
				current_pc += (uintptr_t)UNALIGNED_GET16((uint16_t *)reader) * self->f_codealign;
				reader += 2;
				break;

			CASE(DW_CFA_advance_loc4)
				current_pc += (uintptr_t)UNALIGNED_GET32((uint32_t *)reader) * self->f_codealign;
				reader += 4;
				break;

#if defined(EH_FRAME_FDE_EXEC_CFA_STATE) || \
    defined(EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE) || \
    defined(EH_FRAME_FDE_EXEC_CFA_RULE)
			CASE(DW_CFA_offset_extended) {
				uintptr_half_t reg;
				intptr_t value;
				reg = (uintptr_half_t)dwarf_decode_uleb128((byte_t **)&reader);
				value = ((intptr_t)dwarf_decode_uleb128((byte_t **)&reader) * self->f_dataalign);
				SET_REGISTER(reg, {
					rule->cr_rule  = DW_CFA_register_rule_offsetn;
					rule->cr_value = value;
				});
			}	break;

			CASE(DW_CFA_restore_extended) {
				uintptr_half_t reg;
				reg = (uintptr_half_t)dwarf_decode_uleb128((byte_t **)&reader);
#if defined(EH_FRAME_FDE_EXEC_CFA_STATE) || \
    defined(EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE)
				{
					uintptr_half_t temp;
#if CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT != 0
					temp = cfi_unwind_local_register_dw2common(reg);
					if likely(temp < CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT) {
						/* Common register */
						if unlikely(!common_init_regs) {
							memset(&result->cs_regs[temp], 0, sizeof(result->cs_regs[temp]));
						} else {
							memcpy(&result->cs_regs[temp], &common_init_regs[temp],
							       sizeof(result->cs_regs[temp]));
						}
					} else
#endif /* CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT != 0 */
					{
#if CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0
						temp = cfi_unwind_local_register_dw2uncommon(reg);
						if unlikely(temp >= CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT)
							ERROR(err_invalid_register);
						if unlikely(!uncommon_init_regs) {
							result->cs_uncorder[temp] = 0;
						} else {
							result->cs_uncorder[temp] = uncommon_init_regs[temp];
						}
#else /* CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0 */
						ERROR(err_invalid_register);
#endif /* CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT == 0 */
					}
				}
#elif defined(EH_FRAME_FDE_EXEC_CFA_RULE)
				if (reg == dw_regno) {
					/* Delete the restore rule, thus causing our caller `libuw_unwind_fde_rule()'
					 * to re-attempt the call using the init-body `self->f_inittext' */
					rule->cr_rule = DW_CFA_register_rule_undefined;
				}
#endif /* ... */
			}	break;

			CASE(DW_CFA_same_value)
#if 0 /* Handled identical to UNDEFINED for the purpose of unwinding at runtime */
			{
				uintptr_half_t reg;
				reg = (uintptr_half_t)dwarf_decode_uleb128((byte_t **)&reader);
				SET_REGISTER(reg, {
					rule->cr_rule = DW_CFA_register_rule_same_value;
				});
			}	break;
#endif
			CASE(DW_CFA_undefined) {
				uintptr_half_t reg;
#ifndef EH_FRAME_FDE_EXEC_CFA_RULE
				uintptr_half_t temp;
#endif /* !EH_FRAME_FDE_EXEC_CFA_RULE */
				reg = (uintptr_half_t)dwarf_decode_uleb128((byte_t **)&reader);
#ifdef EH_FRAME_FDE_EXEC_CFA_RULE
				if (reg == dw_regno) {
					/* We can't set `DW_CFA_register_rule_undefined', because then the caller
					 * would assume that we don't know anything about the register, and may
					 * proceed to ask the init-body (which may potentially know something)
					 * We don't want that! - Instead, we want the unwinder to simply not
					 * touch this register at all, which we can do by telling them to simply
					 * keep the previous value for this register. */
					rule->cr_rule = DW_CFA_register_rule_same_value;
				}
#else /* EH_FRAME_FDE_EXEC_CFA_RULE */
#if CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT != 0
				temp = cfi_unwind_local_register_dw2common(reg);
				if __untraced(temp < CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT) {
					/* Common register */
					result->cs_regs[temp].cr_rule  = DW_CFA_register_rule_undefined;
					result->cs_regs[temp].cr_order = 0; /* Don't evaluate */
				} else
#endif /* CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT != 0 */
				{
#if CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0
					temp = cfi_unwind_local_register_dw2uncommon(reg);
					if __untraced(temp >= CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT)
						ERROR(err_invalid_register);
					result->cs_uncorder[temp] = 0; /* Don't evaluate */
#else /* CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT != 0 */
					ERROR(err_invalid_register);
#endif /* CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT == 0 */
				}
#endif /* !EH_FRAME_FDE_EXEC_CFA_RULE */
			}	break;

			CASE(DW_CFA_register) {
				uintptr_half_t reg1;
				uintptr_t reg2;
				reg1 = (uintptr_half_t)dwarf_decode_uleb128((byte_t **)&reader);
				reg2 = dwarf_decode_uleb128((byte_t **)&reader);
				if unlikely(reg2 >= CFI_UNWIND_REGISTER_COUNT)
					ERROR(err_invalid_register);
				SET_REGISTER(reg1, {
					rule->cr_rule  = DW_CFA_register_rule_register;
					rule->cr_value = (intptr_t)reg2;
				});
			}	break;

#else /* EH_FRAME_FDE_EXEC_CFA_STATE || EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE */

			CASE(DW_CFA_offset_extended)
			CASE(DW_CFA_register)
#ifdef EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT
			CASE(DW_CFA_def_cfa)
#endif /* EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT */
			CASE(DW_CFA_val_offset)
			CASE(DW_CFA_GNU_negative_offset_extended)
				dwarf_decode_uleb128((byte_t **)&reader);
				ATTR_FALLTHROUGH
			CASE(DW_CFA_restore_extended)
			CASE(DW_CFA_undefined)
			CASE(DW_CFA_same_value)
#ifdef EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT
			CASE(DW_CFA_def_cfa_register)
			CASE(DW_CFA_def_cfa_offset)
#endif /* EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT */
				dwarf_decode_uleb128((byte_t **)&reader);
				break;

#ifdef EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT
			CASE(DW_CFA_def_cfa_sf)
#endif /* EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT */
			CASE(DW_CFA_offset_extended_sf)
			CASE(DW_CFA_val_offset_sf)
				dwarf_decode_uleb128((byte_t **)&reader);
#ifdef EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT
			ATTR_FALLTHROUGH
			CASE(DW_CFA_def_cfa_offset_sf)
#endif /* EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT */
				dwarf_decode_sleb128((byte_t **)&reader);
				break;

#endif /* !EH_FRAME_FDE_EXEC_CFA_STATE && !EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE */

			CASE(DW_CFA_remember_state) {
				SYM(unwind_cfa_backup_state_t) *backup;
				backup = state_backup_free;
				if (backup) {
					state_backup_free = backup->cbs_prev;
				} else {
					/* Check if we have enough stack space left to create a backup. */
#ifdef __KERNEL__
					if (stack_avail() < ((256 * sizeof(void *)) + sizeof(SYM(unwind_cfa_backup_state_t))))
						ERROR(err_nomem);
					backup = (SYM(unwind_cfa_backup_state_t) *)alloca(sizeof(SYM(unwind_cfa_backup_state_t)));
#else /* __KERNEL__ */
					backup = (SYM(unwind_cfa_backup_state_t) *)malloc(sizeof(SYM(unwind_cfa_backup_state_t)));
					if unlikely(!backup)
						ERROR(err_nomem);
#endif /* !__KERNEL__ */
				}
#ifdef EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT
				backup->cbs_backup = result;
#elif defined(EH_FRAME_FDE_EXEC_CFA_RULE)
				memcpy(&backup->cbs_backup, rule, sizeof(backup->cbs_backup));
#else /* ... */
				memcpy(&backup->cbs_backup, result, sizeof(backup->cbs_backup));
#endif /* !... */
				backup->cbs_prev  = state_backup_list;
				state_backup_list = backup;
			}	break;

			CASE(DW_CFA_restore_state) {
				SYM(unwind_cfa_backup_state_t) *backup;
				backup = state_backup_list;
				if unlikely(!backup)
					ERROR(err_illegal_instruction);
#ifdef EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT
				result = backup->cbs_backup;
#elif defined(EH_FRAME_FDE_EXEC_CFA_RULE)
				memcpy(rule, &backup->cbs_backup, sizeof(backup->cbs_backup));
#else /* ... */
				memcpy(result, &backup->cbs_backup, sizeof(backup->cbs_backup));
#endif /* !... */
				/* Delete the backup descriptor (and add it to the free-list) */
				state_backup_list = backup->cbs_prev;
				backup->cbs_prev  = state_backup_free;
				state_backup_free = backup;
			}	break;

#if defined(EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT) || \
    defined(EH_FRAME_FDE_EXEC_CFA_RULE)
			CASE(DW_CFA_def_cfa_expression) {
				uintptr_t expr_size;
skip_expression:
				expr_size = dwarf_decode_uleb128((byte_t **)&reader);
				if (OVERFLOW_UADD((uintptr_t)reader, expr_size, (uintptr_t *)(byte_t **)&reader))
					ERROR(err_illegal_instruction);
				if (reader > end)
					ERROR(err_illegal_instruction);
			}	break;

#ifdef EH_FRAME_FDE_EXEC_CFA_RULE
			CASE(DW_CFA_def_cfa)
				dwarf_decode_uleb128((byte_t **)&reader);
				ATTR_FALLTHROUGH
			CASE(DW_CFA_def_cfa_register)
			CASE(DW_CFA_def_cfa_offset)
				dwarf_decode_uleb128((byte_t **)&reader);
				break;
			CASE(DW_CFA_def_cfa_sf)
				dwarf_decode_uleb128((byte_t **)&reader);
				ATTR_FALLTHROUGH
			CASE(DW_CFA_def_cfa_offset_sf)
				dwarf_decode_sleb128((byte_t **)&reader);
				break;
#endif /* EH_FRAME_FDE_EXEC_CFA_RULE */

#else /* EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT || EH_FRAME_FDE_EXEC_CFA_RULE */

#if defined(EH_FRAME_FDE_EXEC_CFA_STATE) || \
    defined(EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE)
#define RESULT_CFA result->cs_cfa
#else /* ... */
#define RESULT_CFA (*result)
#endif /* !... */

			CASE(DW_CFA_def_cfa) {
				uintptr_t reg;
				reg = dwarf_decode_uleb128((byte_t **)&reader);
				if unlikely(reg >= CFI_UNWIND_REGISTER_COUNT)
					ERROR(err_invalid_register);
				RESULT_CFA.cv_type = UNWIND_CFA_VALUE_REGISTER;
				RESULT_CFA.cv_reg = (uintptr_half_t)reg;
				RESULT_CFA.cv_value = (intptr_t)dwarf_decode_uleb128((byte_t **)&reader);
			}	break;

			CASE(DW_CFA_def_cfa_sf) {
				uintptr_t reg;
				reg = dwarf_decode_uleb128((byte_t **)&reader);
				if unlikely(reg >= CFI_UNWIND_REGISTER_COUNT)
					ERROR(err_invalid_register);
				RESULT_CFA.cv_type = UNWIND_CFA_VALUE_REGISTER;
				RESULT_CFA.cv_reg = (uintptr_half_t)reg;
				RESULT_CFA.cv_value = (intptr_t)(dwarf_decode_sleb128((byte_t **)&reader) * self->f_dataalign);
			}	break;

			CASE(DW_CFA_def_cfa_register) {
				uintptr_t reg;
				if unlikely(RESULT_CFA.cv_type != UNWIND_CFA_VALUE_REGISTER)
					ERROR(err_illegal_instruction); /* Only allowed when using a register. */
				reg = dwarf_decode_uleb128((byte_t **)&reader);
				if unlikely(reg >= CFI_UNWIND_REGISTER_COUNT)
					ERROR(err_invalid_register);
				RESULT_CFA.cv_reg = (uintptr_half_t)reg;
				/*RESULT_CFA.cv_value = ...;*/ /* Keep the old offset */
			}	break;

			CASE(DW_CFA_def_cfa_offset)
				if unlikely(RESULT_CFA.cv_type != UNWIND_CFA_VALUE_REGISTER)
					ERROR(err_illegal_instruction); /* Only allowed when using a register. */
				RESULT_CFA.cv_value = (intptr_t)dwarf_decode_uleb128((byte_t **)&reader);
				break;

			CASE(DW_CFA_def_cfa_offset_sf)
				if unlikely(RESULT_CFA.cv_type != UNWIND_CFA_VALUE_REGISTER)
					ERROR(err_illegal_instruction); /* Only allowed when using a register. */
				RESULT_CFA.cv_value = (intptr_t)(dwarf_decode_sleb128((byte_t **)&reader) * self->f_dataalign);
				break;

			CASE(DW_CFA_def_cfa_expression) {
				uintptr_t expr_size;
				RESULT_CFA.cv_type = UNWIND_CFA_VALUE_EXPRESSION;
				RESULT_CFA.cv_expr = reader;
skip_expression:
				expr_size = dwarf_decode_uleb128((byte_t **)&reader);
				if unlikely(OVERFLOW_UADD((uintptr_t)reader, expr_size, (uintptr_t *)(byte_t **)&reader))
					ERROR(err_illegal_instruction);
				if unlikely(reader > end)
					ERROR(err_illegal_instruction);
			}	break;

#undef RESULT_CFA
#endif /* !EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT && !EH_FRAME_FDE_EXEC_CFA_RULE */


#if defined(EH_FRAME_FDE_EXEC_CFA_STATE) || \
    defined(EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE) || \
    defined(EH_FRAME_FDE_EXEC_CFA_RULE)
			CASE(DW_CFA_expression) {
				uintptr_half_t reg;
				reg = (uintptr_half_t)dwarf_decode_uleb128((byte_t **)&reader);
				SET_REGISTER(reg, {
					rule->cr_rule = DW_CFA_register_rule_expression;
					rule->cr_expr = reader;
				});
				goto skip_expression;
			}	break;

			CASE(DW_CFA_offset_extended_sf) {
				uintptr_half_t reg;
				intptr_t value;
				reg   = (uintptr_half_t)dwarf_decode_uleb128((byte_t **)&reader);
				value = (dwarf_decode_sleb128((byte_t **)&reader) * self->f_dataalign);
				SET_REGISTER(reg, {
					rule->cr_rule  = DW_CFA_register_rule_offsetn;
					rule->cr_value = value;
				});
			}	break;

			CASE(DW_CFA_val_offset) {
				uintptr_half_t reg;
				intptr_t value;
				reg = (uintptr_half_t)dwarf_decode_uleb128((byte_t **)&reader);
				value = ((intptr_t)dwarf_decode_uleb128((byte_t **)&reader) * self->f_dataalign);
				SET_REGISTER(reg, {
					rule->cr_rule  = DW_CFA_register_rule_val_offsetn;
					rule->cr_value = value;
				});
			}	break;

			CASE(DW_CFA_val_offset_sf) {
				uintptr_half_t reg;
				intptr_t value;
				reg = (uintptr_half_t)dwarf_decode_uleb128((byte_t **)&reader);
				value = (dwarf_decode_sleb128((byte_t **)&reader) * self->f_dataalign);
				SET_REGISTER(reg, {
					rule->cr_rule  = DW_CFA_register_rule_val_offsetn;
					rule->cr_value = value;
				});
			}	break;

			CASE(DW_CFA_val_expression) {
				uintptr_half_t reg;
				reg = (uintptr_half_t)dwarf_decode_uleb128((byte_t **)&reader);
				SET_REGISTER(reg, {
					rule->cr_rule = DW_CFA_register_rule_val_expression;
					rule->cr_expr = reader;
				});
				goto skip_expression;
			}	break;

			CASE(DW_CFA_GNU_negative_offset_extended) {
				uintptr_half_t reg;
				intptr_t value;
				reg = (uintptr_half_t)dwarf_decode_uleb128((byte_t **)&reader);
				value = -((intptr_t)dwarf_decode_uleb128((byte_t **)&reader) * self->f_dataalign);
				SET_REGISTER(reg, {
					rule->cr_rule  = DW_CFA_register_rule_offsetn;
					rule->cr_value = value;
				});
			}	break;
#else /* EH_FRAME_FDE_EXEC_CFA_STATE || EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE || EH_FRAME_FDE_EXEC_CFA_RULE */

			CASE(DW_CFA_expression)
			CASE(DW_CFA_val_expression)
				dwarf_decode_uleb128((byte_t **)&reader);
				goto skip_expression;

#endif /* !EH_FRAME_FDE_EXEC_CFA_STATE && !EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE && !EH_FRAME_FDE_EXEC_CFA_RULE */

			CASE(DW_CFA_GNU_args_size)
				/* Landing pad stack adjustment */
#ifdef EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT
				result = dwarf_decode_uleb128((byte_t **)&reader);
#else /* EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT */
				dwarf_decode_uleb128((byte_t **)&reader);
#endif /* !EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT */
				break;

			CASE(DW_CFA_nop) /* no-op. */
				break;

			default:
				ERRORF(err_unknown_instruction, "operand = 0x%.2I8x\n", operand);
			}
		}
	}
#undef cfi_unwind_local_register_dw2uncommon
#undef cfi_unwind_local_register_dw2common
#undef CFI_UNWIND_LOCAL_UNCOMMON_REGISTER_COUNT
#undef CFI_UNWIND_LOCAL_COMMON_REGISTER_COUNT
#undef SET_REGISTER
#ifndef __KERNEL__
	SYM(unwind_cfa_backup_state_freechain)(state_backup_free);
	SYM(unwind_cfa_backup_state_freechain)(state_backup_list);
#endif /* !__KERNEL__ */
#ifdef EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT
	*psp_adjustment = result;
#endif /* EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT */
	return UNWIND_SUCCESS;
#ifndef __KERNEL__
	{
		unsigned int error;
err_unknown_instruction:
		error = UNWIND_CFA_UNKNOWN_INSTRUCTION;
		goto err_common;
err_nomem:
		error = UNWIND_BADALLOC;
		goto err_common;
#ifndef EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT
err_invalid_register:
		error = UNWIND_INVALID_REGISTER;
		goto err_common;
#endif /* !EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT */
err_illegal_instruction:
		error = UNWIND_CFA_ILLEGAL_INSTRUCTION;
err_common:
		SYM(unwind_cfa_backup_state_freechain)(state_backup_free);
		SYM(unwind_cfa_backup_state_freechain)(state_backup_list);
		return error;
	}
#else /* !__KERNEL__ */
err_unknown_instruction:
	return UNWIND_CFA_UNKNOWN_INSTRUCTION;
err_nomem:
	return UNWIND_BADALLOC;
#ifndef EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT
err_invalid_register:
	return UNWIND_INVALID_REGISTER;
#endif /* !EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT */
err_illegal_instruction:
	return UNWIND_CFA_ILLEGAL_INSTRUCTION;
#endif /* __KERNEL__ */
}

#undef SYM

#undef EH_FRAME_FDE_EXEC_CFA_STATE
#undef EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE
#undef EH_FRAME_FDE_EXEC_CFA_RULE
#undef EH_FRAME_FDE_EXEC_CFA_VALUE
#undef EH_FRAME_FDE_EXEC_LANDING_PAD_ADJUSTMENT


DECL_END
