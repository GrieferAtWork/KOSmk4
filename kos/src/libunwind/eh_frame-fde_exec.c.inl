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
//#define EH_FRAME_FDE_EXEC_CFA_STATE 1
//#define EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE 1
#define EH_FRAME_FDE_EXEC_CFA_LANDING_STATE 1
//#define EH_FRAME_FDE_EXEC_CFA_VALUE 1
//#define EH_FRAME_FDE_EXEC_CFA_RULE  1
#endif /* __INTELLISENSE__ */

#ifdef __KERNEL__
#include <sched/task.h> /* get_stack_avail() */

#include <alloca.h>
#else /* __KERNEL__ */
#include <malloc.h>
#endif /* !__KERNEL__ */

#include <string.h>
#include <hybrid/overflow.h>

#if (defined(EH_FRAME_FDE_EXEC_CFA_STATE) + \
     defined(EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE) + \
     defined(EH_FRAME_FDE_EXEC_CFA_LANDING_STATE) + \
     defined(EH_FRAME_FDE_EXEC_CFA_VALUE) + \
     defined(EH_FRAME_FDE_EXEC_CFA_RULE)) != 1
#error "Invalid configuration"
#endif /* ... */


DECL_BEGIN

#ifdef EH_FRAME_FDE_EXEC_CFA_STATE
#define LOCAL_SYM(x) cfa_state_##x
#elif defined(EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE)
#define LOCAL_SYM(x) cfa_sigframe_state_##x
#elif defined(EH_FRAME_FDE_EXEC_CFA_LANDING_STATE)
#define LOCAL_SYM(x) cfa_landing_state_##x
#elif defined(EH_FRAME_FDE_EXEC_CFA_VALUE)
#define LOCAL_SYM(x) cfa_value_##x
#elif defined(EH_FRAME_FDE_EXEC_CFA_RULE)
#define LOCAL_SYM(x) cfa_rule_##x
#endif /* ... */

typedef struct LOCAL_SYM(unwind_cfa_backup_state_struct) LOCAL_SYM(unwind_cfa_backup_state_t);
struct LOCAL_SYM(unwind_cfa_backup_state_struct) {
#ifdef EH_FRAME_FDE_EXEC_CFA_STATE
	unwind_cfa_state_t              cbs_backup; /* Backup data. */
#elif defined(EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE)
	unwind_cfa_sigframe_state_t     cbs_backup; /* Backup data. */
#elif defined(EH_FRAME_FDE_EXEC_CFA_LANDING_STATE)
	_unwind_cfa_landing_state_t     cbs_backup; /* Backup data. */
#elif defined(EH_FRAME_FDE_EXEC_CFA_VALUE)
	unwind_cfa_value_t              cbs_backup; /* Backup data. */
#elif defined(EH_FRAME_FDE_EXEC_CFA_RULE)
	unwind_cfa_register_t           cbs_backup; /* Backup data. */
#endif /* ... */
	LOCAL_SYM(unwind_cfa_backup_state_t) *cbs_prev;   /* [0..1] Previous backup */
};

#ifndef __KERNEL__
PRIVATE void
NOTHROW_NCX(CC LOCAL_SYM(unwind_cfa_backup_state_freechain))(LOCAL_SYM(unwind_cfa_backup_state_t) *base) {
	LOCAL_SYM(unwind_cfa_backup_state_t) *next;
	while (base) {
		next = base->cbs_prev;
		free(base);
		base = next;
	}
}
#endif /* !__KERNEL__ */


#if (defined(EH_FRAME_FDE_EXEC_CFA_STATE) || \
     defined(EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE) || \
     defined(EH_FRAME_FDE_EXEC_CFA_LANDING_STATE))
#ifdef EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE
#define LOCAL_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT   CFI_UNWIND_SIGFRAME_COMMON_REGISTER_MAXCOUNT
#define LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MAXCOUNT
#define local_cfi_unwind_register_dw2common         cfi_unwind_sigframe_register_dw2common
#define local_cfi_unwind_register_dw2uncommon       cfi_unwind_sigframe_register_dw2uncommon
#elif defined(EH_FRAME_FDE_EXEC_CFA_LANDING_STATE)
#define LOCAL_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT   CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT
#define LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT
#define local_cfi_unwind_register_dw2common         cfi_unwind_landing_register_dw2common
#define local_cfi_unwind_register_dw2uncommon       cfi_unwind_landing_register_dw2uncommon
#else /* ... */
#define LOCAL_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT   CFI_UNWIND_COMMON_REGISTER_MAXCOUNT
#define LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT
#define local_cfi_unwind_register_dw2common         cfi_unwind_register_dw2common
#define local_cfi_unwind_register_dw2uncommon       cfi_unwind_register_dw2uncommon
#endif /* !... */


#if (LOCAL_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT == 0 && LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT == 0)
#ifdef EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE
#error "Neither common, nor uncommon registers defined for SIGFRAME"
#elif defined(EH_FRAME_FDE_EXEC_CFA_LANDING_STATE)
#error "Neither common, nor uncommon registers defined for LANDING"
#else /* ... */
#error "Neither common, nor uncommon registers defined for NORMAL"
#endif /* !... */
#endif /* ... */
#endif /* EH_FRAME_FDE_EXEC_CFA_STATE || EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE || EH_FRAME_FDE_EXEC_CFA_LANDING_STATE */


#ifdef EH_FRAME_FDE_EXEC_CFA_STATE
/* Execute CFA  result  instruction  until  `absolute_pc'  has  been  reached,
 * or   the  entirety  of   the  FDE  instruction   code  has  been  executed.
 * This function is used to fill in CFA result information at a given address,
 * which can then  be used  to unwind  a register  result for  the purpose  of
 * implementing  language-level,  zero-effort   exception  support,  as   well
 * as  for  generating   tracebacks  when   combined  with   `libdebuginfo.so'
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
#if CFI_UNWIND_SIGFRAME_COMMON_REGISTER_MAXCOUNT != 0 && CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MAXCOUNT != 0
	NONNULL((1, 4, 5, 6))
#elif CFI_UNWIND_SIGFRAME_COMMON_REGISTER_MAXCOUNT != 0 || CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MAXCOUNT != 0
	NONNULL((1, 3, 4, 5))
#else /* ... */
	NONNULL((1, 2, 3, 4))
#endif /* !... */
	unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_fde_exec_until)(unwind_fde_t *__restrict self, /* Only non-const for lazy initialized fields! */
                                            IF_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT(unwind_cfa_register_t *common_init_regs,)
                                            IF_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT(byte_t *uncommon_init_regs,)
                                            byte_t const *reader,
                                            byte_t const *end,
                                            unwind_cfa_state_t *__restrict result,
                                            void const *absolute_pc)
#elif defined(EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE)
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
PRIVATE
#if CFI_UNWIND_SIGFRAME_COMMON_REGISTER_MAXCOUNT != 0 && CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MAXCOUNT != 0
	NONNULL((1, 4, 5, 6))
#elif CFI_UNWIND_SIGFRAME_COMMON_REGISTER_MAXCOUNT != 0 || CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MAXCOUNT != 0
	NONNULL((1, 3, 4, 5))
#else /* ... */
	NONNULL((1, 2, 3, 4))
#endif /* !... */
	unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_sigframe_fde_exec_until)(unwind_fde_t *__restrict self, /* Only non-const for lazy initialized fields! */
                                                     IF_CFI_UNWIND_SIGFRAME_COMMON_REGISTER_MAXCOUNT(unwind_cfa_register_t *common_init_regs,)
                                                     IF_CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MAXCOUNT(byte_t *uncommon_init_regs,)
                                                     byte_t const *reader,
                                                     byte_t const *end,
                                                     unwind_cfa_sigframe_state_t *__restrict result,
                                                     void const *absolute_pc)
#elif defined(EH_FRAME_FDE_EXEC_CFA_LANDING_STATE)
/* Internal helper for calculating landing-pad rules. */
PRIVATE
#if CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT != 0 && CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT != 0
	NONNULL((1, 4, 5, 6))
#elif CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT != 0 || CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT != 0
	NONNULL((1, 3, 4, 5))
#else /* ... */
	NONNULL((1, 2, 3, 4))
#endif /* !... */
	unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_landing_fde_exec_until)(unwind_fde_t *__restrict self, /* Only non-const for lazy initialized fields! */
                                                    IF_CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT(unwind_cfa_register_t *common_init_regs,)
                                                    IF_CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT(byte_t *uncommon_init_regs,)
                                                    byte_t const *reader,
                                                    byte_t const *landing_start_reader,
                                                    byte_t const *end,
                                                    _unwind_cfa_landing_state_t *__restrict result,
                                                    void const *absolute_pc)
#elif defined(EH_FRAME_FDE_EXEC_CFA_VALUE)
/* Same as `unwind_fde_exec()', however only calculate the CFA restore descriptor.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
PRIVATE NONNULL((1, 2, 3, 4)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_fde_exec_cfa_until)(unwind_fde_t *__restrict self, /* Only non-const for lazy initialized fields! */
                                                byte_t const *reader,
                                                byte_t const *end,
                                                unwind_cfa_value_t *__restrict result,
                                                void const *absolute_pc)
#elif defined(EH_FRAME_FDE_EXEC_CFA_RULE)
/* Similar  to  `unwind_fde_exec()',   but  used   to  calculate   the
 * unwind  rule   for  `dw_regno'   at   the  given   text   location.
 * This  is  used  to  implement  unwinding  for  uncommon  registers,
 * since  `unwind_fde_exec()'   will  not   already  calculate   these
 * during the first  pass (thus keeping  down the memory  requirements
 * imposed on the one responsible for allocating `unwind_cfa_state_t')
 * @param: self: The FDE to execute in search of `absolute_pc'
 * @param: rule: The CFA register result controller to-be filled.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
PRIVATE NONNULL((1, 2, 3, 4)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_fde_exec_rule_until)(unwind_fde_t *__restrict self, /* Only non-const for lazy initialized fields! */
                                                 byte_t const *reader,
                                                 byte_t const *end,
                                                 unwind_cfa_register_t *__restrict rule,
                                                 unwind_regno_t dw_regno,
                                                 void const *absolute_pc)
#endif /* ... */
{
#ifdef EH_FRAME_FDE_EXEC_CFA_LANDING_STATE
#define LOCAL_IF_SHOULD_APPLY_RULE if (reader >= landing_start_reader)
#else /* EH_FRAME_FDE_EXEC_CFA_LANDING_STATE */
#define LOCAL_IF_SHOULD_APPLY_RULE /* nothing (__IF1) */
#endif /* !EH_FRAME_FDE_EXEC_CFA_LANDING_STATE */

	uintptr_t current_pc;
	LOCAL_SYM(unwind_cfa_backup_state_t) *state_backup_list = NULL;
	LOCAL_SYM(unwind_cfa_backup_state_t) *state_backup_free = NULL; /* Free list of state backups. */
	assertf(((uintptr_t)absolute_pc >= (uintptr_t)self->f_pcstart &&
	         (uintptr_t)absolute_pc <= (uintptr_t)self->f_pcend) ||
	        (absolute_pc == (void *)-1),
	        "self->f_pcstart = %p\n"
	        "self->f_pcend   = %p\n"
	        "absolute_pc     = %p\n",
	        self->f_pcstart, self->f_pcend, absolute_pc);
	current_pc = (uintptr_t)self->f_pcstart;
#if (defined(EH_FRAME_FDE_EXEC_CFA_STATE) ||          \
     defined(EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE) || \
     defined(EH_FRAME_FDE_EXEC_CFA_LANDING_STATE))
#if LOCAL_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT != 0
#if LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT != 0
#define LOCAL_setregister(dw_regid, ...)                                                     \
	LOCAL_IF_SHOULD_APPLY_RULE {                                                             \
		unwind_regno_t temp;                                                                 \
		temp = local_cfi_unwind_register_dw2common(self->f_addrsize, dw_regid);              \
		if likely(temp < LOCAL_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT) {                        \
			/* Common register */                                                            \
			unwind_cfa_register_t *rule = &result->cs_regs[temp];                            \
			__VA_ARGS__;                                                                     \
		} else {                                                                             \
			temp = local_cfi_unwind_register_dw2uncommon(self->f_addrsize, dw_regid);        \
			if unlikely(temp >= LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT)                 \
				ERRORF(err_invalid_register, "regno=%u\n",                                   \
				       (unsigned int)(dw_regid));                                            \
			/* Uncommon register */                                                          \
			bitset_insert(result->cs_uncommon, temp);                                        \
			bitset_insert(result->cs_uncommon, LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT); \
		}                                                                                    \
	}
#else /* LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT != 0 */
#define LOCAL_setregister(dw_regid, ...)                                        \
	LOCAL_IF_SHOULD_APPLY_RULE {                                                \
		unwind_regno_t temp;                                                    \
		temp = local_cfi_unwind_register_dw2common(self->f_addrsize, dw_regid); \
		if likely(temp < LOCAL_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT) {           \
			/* Common register */                                               \
			unwind_cfa_register_t *rule = &result->cs_regs[temp];               \
			__VA_ARGS__;                                                        \
		} else {                                                                \
			ERRORF(err_invalid_register, "regno=%u\n",                          \
			       (unsigned int)(dw_regid));                                   \
		}                                                                       \
	}
#endif /* LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT == 0 */
#else /* LOCAL_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT != 0 */
#if LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT != 0
#define LOCAL_setregister(dw_regid, ...)                                                 \
	LOCAL_IF_SHOULD_APPLY_RULE {                                                         \
		unwind_regno_t temp;                                                             \
		temp = local_cfi_unwind_register_dw2uncommon(self->f_addrsize, dw_regid);        \
		if unlikely(temp >= LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT)                 \
			ERRORF(err_invalid_register, "regno=%u\n",                                   \
			       (unsigned int)(dw_regid));                                            \
		/* Uncommon register */                                                          \
		bitset_insert(result->cs_uncommon, temp);                                        \
		bitset_insert(result->cs_uncommon, LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT); \
	}
#else /* LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT != 0 */
#define LOCAL_setregister(dw_regid, ...)           \
	LOCAL_IF_SHOULD_APPLY_RULE {                   \
		ERRORF(err_invalid_register, "regno=%u\n", \
		       (unsigned int)(dw_regid));          \
	}
#endif /* LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT == 0 */
#endif /* LOCAL_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT == 0 */
#elif defined(EH_FRAME_FDE_EXEC_CFA_RULE)
#define LOCAL_setregister(dw_regid, ...) \
	LOCAL_IF_SHOULD_APPLY_RULE {         \
		if ((dw_regid) == dw_regno) {    \
			/* Common register */        \
			__VA_ARGS__;                 \
		}                                \
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
			TRACE("DW_CFA_offset(%" PRIu8 ")\n", operand);
			{
#if (defined(EH_FRAME_FDE_EXEC_CFA_STATE) ||          \
     defined(EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE) || \
     defined(EH_FRAME_FDE_EXEC_CFA_LANDING_STATE) ||  \
     defined(EH_FRAME_FDE_EXEC_CFA_RULE))
				intptr_t value;
				value = ((intptr_t)dwarf_decode_uleb128((byte_t const **)&reader) * self->f_dataalign);
				LOCAL_setregister(operand, {
					rule->cr_rule  = DW_CFA_register_rule_offsetn;
					rule->cr_value = value;
				});
#else /* ... */
				dwarf_decode_uleb128((byte_t const **)&reader);
#endif /* !... */
			}
		} else if (opcode == DW_CFA_restore) {
			TRACE("DW_CFA_restore\n");
#if (defined(EH_FRAME_FDE_EXEC_CFA_STATE) ||          \
     defined(EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE) || \
     defined(EH_FRAME_FDE_EXEC_CFA_LANDING_STATE))
			LOCAL_IF_SHOULD_APPLY_RULE {
				unwind_regno_t temp;
#if LOCAL_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT != 0
				temp = local_cfi_unwind_register_dw2common(self->f_addrsize, operand);
				if likely(temp < LOCAL_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT) {
					/* Common register */
					if unlikely(!common_init_regs) {
						bzero(&result->cs_regs[temp], sizeof(result->cs_regs[temp]));
					} else {
						memcpy(&result->cs_regs[temp], &common_init_regs[temp],
						       sizeof(result->cs_regs[temp]));
					}
				} else
#endif /* LOCAL_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT != 0 */
				{
#if LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT != 0
					temp = local_cfi_unwind_register_dw2uncommon(self->f_addrsize, operand);
					if unlikely(temp >= LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT)
						ERRORF(err_invalid_register, "regno=%u\n", (unsigned int)operand);
					bitset_remove(result->cs_uncommon, temp);
					if likely(uncommon_init_regs && bitset_contains(uncommon_init_regs, temp)) {
						bitset_insert(result->cs_uncommon, temp);
						bitset_insert(result->cs_uncommon, LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT);
					}
#else /* LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT != 0 */
					ERRORF(err_invalid_register, "regno=%u\n", (unsigned int)operand);
#endif /* LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT == 0 */
				}
			}
#elif defined(EH_FRAME_FDE_EXEC_CFA_RULE)
			if (operand == dw_regno) {
				/* Delete the restore rule, thus causing our caller `libuw_unwind_fde_rule()'
				 * to   re-attempt   the   call   using   the   init-body  `self->f_inittext' */
				rule->cr_rule = DW_CFA_register_rule_undefined;
			}
#endif /* ... */
		} else {
			switch (operand) {

			CASE(DW_CFA_set_loc)
				/* Decode the PC pointer according to FDE pointer encoding. */
				current_pc = (uintptr_t)dwarf_decode_pointer((byte_t const **)&reader,
				                                             self->f_ptrenc,
				                                             self->f_addrsize,
				                                             &self->f_bases);
				current_pc += (uintptr_t)self->f_pcstart;
				break;

			CASE(DW_CFA_advance_loc1)
				current_pc += (uintptr_t)(*(uint8_t const *)reader) * self->f_codealign;
				reader += 1;
				break;

			CASE(DW_CFA_advance_loc2)
				current_pc += (uintptr_t)UNALIGNED_GET16((uint16_t const *)reader) * self->f_codealign;
				reader += 2;
				break;

			CASE(DW_CFA_advance_loc4)
				current_pc += (uintptr_t)UNALIGNED_GET32((uint32_t const *)reader) * self->f_codealign;
				reader += 4;
				break;

#if __SIZEOF_POINTER__ >= 8
			CASE(DW_CFA_MIPS_advance_loc8)
				current_pc += (uintptr_t)UNALIGNED_GET64((uint64_t const *)reader) * self->f_codealign;
				reader += 8;
				break;
#endif /* __SIZEOF_POINTER__ >= 8 */

#if (defined(EH_FRAME_FDE_EXEC_CFA_STATE) ||          \
     defined(EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE) || \
     defined(EH_FRAME_FDE_EXEC_CFA_LANDING_STATE) ||  \
     defined(EH_FRAME_FDE_EXEC_CFA_RULE))
			CASE(DW_CFA_offset_extended) {
				unwind_regno_t reg;
				intptr_t value;
				reg   = (unwind_regno_t)dwarf_decode_uleb128((byte_t const **)&reader);
				value = ((intptr_t)dwarf_decode_uleb128((byte_t const **)&reader) * self->f_dataalign);
				LOCAL_setregister(reg, {
					rule->cr_rule  = DW_CFA_register_rule_offsetn;
					rule->cr_value = value;
				});
			}	break;

			CASE(DW_CFA_restore_extended) {
				unwind_regno_t reg;
				reg = (unwind_regno_t)dwarf_decode_uleb128((byte_t const **)&reader);
#if (defined(EH_FRAME_FDE_EXEC_CFA_STATE) ||         \
     defined(EH_FRAME_FDE_EXEC_CFA_LANDING_STATE) || \
     defined(EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE))
				LOCAL_IF_SHOULD_APPLY_RULE {
					unwind_regno_t temp;
#if LOCAL_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT != 0
					temp = local_cfi_unwind_register_dw2common(self->f_addrsize, reg);
					if likely(temp < LOCAL_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT) {
						/* Common register */
						if unlikely(!common_init_regs) {
							bzero(&result->cs_regs[temp], sizeof(result->cs_regs[temp]));
						} else {
							memcpy(&result->cs_regs[temp], &common_init_regs[temp],
							       sizeof(result->cs_regs[temp]));
						}
					} else
#endif /* LOCAL_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT != 0 */
					{
#if LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT != 0
						temp = local_cfi_unwind_register_dw2uncommon(self->f_addrsize, reg);
						if unlikely(temp >= LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT)
							ERRORF(err_invalid_register, "regno=%u\n", (unsigned int)reg);
						bitset_remove(result->cs_uncommon, temp);
						if likely(uncommon_init_regs && bitset_contains(uncommon_init_regs, temp)) {
							bitset_insert(result->cs_uncommon, temp);
							bitset_insert(result->cs_uncommon, LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT); ;
						}
#else /* LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT != 0 */
						ERRORF(err_invalid_register, "regno=%u\n", (unsigned int)reg);
#endif /* LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT == 0 */
					}
				}
#elif defined(EH_FRAME_FDE_EXEC_CFA_RULE)
				if (reg == dw_regno) {
					/* Delete the restore rule, thus causing our caller `libuw_unwind_fde_rule()'
					 * to   re-attempt   the   call   using   the   init-body  `self->f_inittext' */
					rule->cr_rule = DW_CFA_register_rule_undefined;
				}
#endif /* ... */
			}	break;

			CASE(DW_CFA_same_value)
#if 0 /* Handled identical to UNDEFINED for the purpose of unwinding at runtime */
			{
				unwind_regno_t reg;
				reg = (unwind_regno_t)dwarf_decode_uleb128((byte_t const **)&reader);
				LOCAL_setregister(reg, {
					rule->cr_rule = DW_CFA_register_rule_same_value;
				});
			}	break;
#endif
			CASE(DW_CFA_undefined) {
				unwind_regno_t reg;
				reg = (unwind_regno_t)dwarf_decode_uleb128((byte_t const **)&reader);
#ifdef EH_FRAME_FDE_EXEC_CFA_RULE
				if (reg == dw_regno) {
					/* We can't set `DW_CFA_register_rule_undefined', because then the caller
					 * would assume that we don't know  anything about the register, and  may
					 * proceed to ask  the init-body (which  may potentially know  something)
					 * We don't want  that! -  Instead, we want  the unwinder  to simply  not
					 * touch  this register at all, which we can do by telling them to simply
					 * keep the previous value for this register. */
					rule->cr_rule = DW_CFA_register_rule_same_value;
				}
#else /* EH_FRAME_FDE_EXEC_CFA_RULE */
				LOCAL_IF_SHOULD_APPLY_RULE {
					unwind_regno_t temp;
#if LOCAL_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT != 0
					temp = local_cfi_unwind_register_dw2common(self->f_addrsize, reg);
					if __untraced(temp < LOCAL_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT) {
						/* Common register */
						result->cs_regs[temp].cr_rule = DW_CFA_register_rule_undefined;
					} else
#endif /* LOCAL_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT != 0 */
					{
#if LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT != 0
						temp = local_cfi_unwind_register_dw2uncommon(self->f_addrsize, reg);
						if __untraced(temp >= LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT)
							ERRORF(err_invalid_register, "regno=%u\n", (unsigned int)reg);
						bitset_remove(result->cs_uncommon, temp); /* Don't evaluate */
#else /* LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT != 0 */
						ERRORF(err_invalid_register, "regno=%u\n", (unsigned int)reg);
#endif /* LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT == 0 */
					}
				}
#endif /* !EH_FRAME_FDE_EXEC_CFA_RULE */
			}	break;

			CASE(DW_CFA_register) {
				unwind_regno_t reg1;
				uintptr_t reg2;
				reg1 = (unwind_regno_t)dwarf_decode_uleb128((byte_t const **)&reader);
				reg2 = dwarf_decode_uleb128((byte_t const **)&reader);
				if unlikely(reg2 >= CFI_UNWIND_REGISTER_MAXCOUNT)
					ERRORF(err_invalid_register, "regno=%" PRIuPTR "\n", reg2);
				LOCAL_setregister(reg1, {
					rule->cr_rule  = DW_CFA_register_rule_register;
					rule->cr_value = (intptr_t)reg2;
				});
			}	break;

#else /* EH_FRAME_FDE_EXEC_CFA_STATE || EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE || EH_FRAME_FDE_EXEC_CFA_LANDING_STATE */

			CASE(DW_CFA_offset_extended)
			CASE(DW_CFA_register)
			CASE(DW_CFA_val_offset)
			CASE(DW_CFA_GNU_negative_offset_extended)
				dwarf_decode_uleb128((byte_t const **)&reader);
				ATTR_FALLTHROUGH
			CASE(DW_CFA_restore_extended)
			CASE(DW_CFA_undefined)
			CASE(DW_CFA_same_value)
				dwarf_decode_uleb128((byte_t const **)&reader);
				break;

			CASE(DW_CFA_offset_extended_sf)
			CASE(DW_CFA_val_offset_sf)
				dwarf_decode_uleb128((byte_t const **)&reader);
				dwarf_decode_sleb128((byte_t const **)&reader);
				break;

#endif /* !EH_FRAME_FDE_EXEC_CFA_STATE && !EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE && !EH_FRAME_FDE_EXEC_CFA_LANDING_STATE */

			CASE(DW_CFA_remember_state)
			CASE(DW_CFA_KOS_startcapsule) {
				LOCAL_SYM(unwind_cfa_backup_state_t) *backup;
				backup = state_backup_free;
				if (backup) {
					state_backup_free = backup->cbs_prev;
				} else {
					/* Check if we have enough stack space left to create a backup. */
#ifdef __KERNEL__
					if (get_stack_avail() < ((256 * sizeof(void *)) + sizeof(LOCAL_SYM(unwind_cfa_backup_state_t))))
						ERRORF(err_nomem, "get_stack_avail()=%" PRIuSIZ "\n", get_stack_avail());
					backup = (LOCAL_SYM(unwind_cfa_backup_state_t) *)alloca(sizeof(LOCAL_SYM(unwind_cfa_backup_state_t)));
#else /* __KERNEL__ */
					backup = (LOCAL_SYM(unwind_cfa_backup_state_t) *)malloc(sizeof(LOCAL_SYM(unwind_cfa_backup_state_t)));
					if unlikely(!backup)
						ERROR(err_nomem);
#endif /* !__KERNEL__ */
				}
#ifdef EH_FRAME_FDE_EXEC_CFA_RULE
				memcpy(&backup->cbs_backup, rule, sizeof(backup->cbs_backup));
#else /* EH_FRAME_FDE_EXEC_CFA_RULE */
				memcpy(&backup->cbs_backup, result, sizeof(backup->cbs_backup));
#endif /* !EH_FRAME_FDE_EXEC_CFA_RULE */
				backup->cbs_prev  = state_backup_list;
				state_backup_list = backup;
			}	break;

			CASE(DW_CFA_restore_state)
			CASE(DW_CFA_KOS_endcapsule) {
				LOCAL_SYM(unwind_cfa_backup_state_t) *backup;
				backup = state_backup_list;
				if unlikely(!backup)
					ERROR(err_illegal_instruction);
#ifdef EH_FRAME_FDE_EXEC_CFA_RULE
				memcpy(rule, &backup->cbs_backup, sizeof(backup->cbs_backup));
#else /* EH_FRAME_FDE_EXEC_CFA_RULE */
				memcpy(result, &backup->cbs_backup, sizeof(backup->cbs_backup));
#endif /* !EH_FRAME_FDE_EXEC_CFA_RULE */
				/* Delete the backup descriptor (and add it to the free-list) */
				state_backup_list = backup->cbs_prev;
				backup->cbs_prev  = state_backup_free;
				state_backup_free = backup;
			}	break;

#ifdef EH_FRAME_FDE_EXEC_CFA_RULE
			CASE(DW_CFA_def_cfa_expression) {
				uintptr_t expr_size;
skip_expression:
				expr_size = dwarf_decode_uleb128((byte_t const **)&reader);
				if unlikely(OVERFLOW_UADD((uintptr_t)reader, expr_size,
				                          (uintptr_t *)(byte_t const **)&reader) ||
				            reader > end) {
					ERRORF(err_illegal_instruction,
					       "reader=%p, expr_size=%" PRIuSIZ "(%#" PRIxSIZ "), end=%p\n",
					       (uintptr_t)reader - expr_size,
					       expr_size, expr_size, end);
				}
			}	break;

			CASE(DW_CFA_def_cfa)
				dwarf_decode_uleb128((byte_t const **)&reader);
				ATTR_FALLTHROUGH
			CASE(DW_CFA_def_cfa_register)
			CASE(DW_CFA_def_cfa_offset)
				dwarf_decode_uleb128((byte_t const **)&reader);
				break;
			CASE(DW_CFA_def_cfa_sf)
				dwarf_decode_uleb128((byte_t const **)&reader);
				ATTR_FALLTHROUGH
			CASE(DW_CFA_def_cfa_offset_sf)
				dwarf_decode_sleb128((byte_t const **)&reader);
				break;

#else /* EH_FRAME_FDE_EXEC_CFA_RULE */

#if (defined(EH_FRAME_FDE_EXEC_CFA_STATE) ||          \
     defined(EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE) || \
     defined(EH_FRAME_FDE_EXEC_CFA_LANDING_STATE))
#define RESULT_CFA result->cs_cfa
#else /* ... */
#define RESULT_CFA (*result)
#endif /* !... */

			CASE(DW_CFA_def_cfa) {
				uintptr_t reg;
				reg = dwarf_decode_uleb128((byte_t const **)&reader);
				if unlikely(reg >= CFI_UNWIND_REGISTER_MAXCOUNT)
					ERRORF(err_invalid_register, "regno=%" PRIuPTR "\n", reg);
				RESULT_CFA.cv_type = UNWIND_CFA_VALUE_REGISTER;
				RESULT_CFA.cv_reg = (unwind_regno_t)reg;
				RESULT_CFA.cv_value = (intptr_t)dwarf_decode_uleb128((byte_t const **)&reader);
			}	break;

			CASE(DW_CFA_def_cfa_sf) {
				uintptr_t reg;
				reg = dwarf_decode_uleb128((byte_t const **)&reader);
				if unlikely(reg >= CFI_UNWIND_REGISTER_MAXCOUNT)
					ERRORF(err_invalid_register, "regno=%" PRIuPTR "\n", reg);
				RESULT_CFA.cv_type = UNWIND_CFA_VALUE_REGISTER;
				RESULT_CFA.cv_reg = (unwind_regno_t)reg;
				RESULT_CFA.cv_value = (intptr_t)(dwarf_decode_sleb128((byte_t const **)&reader) * self->f_dataalign);
			}	break;

			CASE(DW_CFA_def_cfa_register) {
				uintptr_t reg;
				if unlikely(RESULT_CFA.cv_type != UNWIND_CFA_VALUE_REGISTER) {
					/* Only allowed when using a register [, or not already set]. */
#ifdef CONFIG_DW_RELAXED_CFA_INITIALIZATION_RULES
					if (RESULT_CFA.cv_type == UNWIND_CFA_VALUE_UNSET) {
						RESULT_CFA.cv_type  = UNWIND_CFA_VALUE_REGISTER;
						RESULT_CFA.cv_value = 0;
					} else
#endif /* CONFIG_DW_RELAXED_CFA_INITIALIZATION_RULES */
					{
						ERRORF(err_illegal_instruction, "cv_type=%u\n", (unsigned int)RESULT_CFA.cv_type);
					}
				}
				reg = dwarf_decode_uleb128((byte_t const **)&reader);
				if unlikely(reg >= CFI_UNWIND_REGISTER_MAXCOUNT)
					ERRORF(err_invalid_register, "regno=%" PRIuPTR "\n", reg);
				RESULT_CFA.cv_reg = (unwind_regno_t)reg;
				/*RESULT_CFA.cv_value = ...;*/ /* Keep the old offset */
			}	break;

			CASE(DW_CFA_def_cfa_offset)
				if unlikely(RESULT_CFA.cv_type != UNWIND_CFA_VALUE_REGISTER) {
					/* Only allowed when using a register, or not already set. */
#ifdef CONFIG_DW_RELAXED_CFA_INITIALIZATION_RULES
					if (RESULT_CFA.cv_type == UNWIND_CFA_VALUE_UNSET) {
						RESULT_CFA.cv_type = UNWIND_CFA_VALUE_REGISTER;
						RESULT_CFA.cv_reg  = CFI_UNWIND_REGISTER_SP(self->f_addrsize);
					} else
#endif /* CONFIG_DW_RELAXED_CFA_INITIALIZATION_RULES */
					{
						ERRORF(err_illegal_instruction, "cv_type=%u\n", (unsigned int)RESULT_CFA.cv_type);
					}
				}
				RESULT_CFA.cv_value = (intptr_t)dwarf_decode_uleb128((byte_t const **)&reader);
				break;

			CASE(DW_CFA_def_cfa_offset_sf)
				if unlikely(RESULT_CFA.cv_type != UNWIND_CFA_VALUE_REGISTER) {
					/* Only allowed when using a register, or not already set. */
#ifdef CONFIG_DW_RELAXED_CFA_INITIALIZATION_RULES
					if (RESULT_CFA.cv_type == UNWIND_CFA_VALUE_UNSET) {
						RESULT_CFA.cv_type = UNWIND_CFA_VALUE_REGISTER;
						RESULT_CFA.cv_reg  = CFI_UNWIND_REGISTER_SP(self->f_addrsize);
					} else
#endif /* CONFIG_DW_RELAXED_CFA_INITIALIZATION_RULES */
					{
						ERRORF(err_illegal_instruction, "cv_type=%u\n", (unsigned int)RESULT_CFA.cv_type);
					}
				}
				RESULT_CFA.cv_value = (intptr_t)(dwarf_decode_sleb128((byte_t const **)&reader) * self->f_dataalign);
				break;

			CASE(DW_CFA_def_cfa_expression) {
				uintptr_t expr_size;
				RESULT_CFA.cv_type = UNWIND_CFA_VALUE_EXPRESSION;
				RESULT_CFA.cv_expr = reader;
skip_expression:
				expr_size = dwarf_decode_uleb128((byte_t const **)&reader);
				if unlikely(OVERFLOW_UADD((uintptr_t)reader,
				                          expr_size, (uintptr_t *)(byte_t const **)&reader) ||
				            reader > end) {
					ERRORF(err_illegal_instruction,
					       "reader=%p, expr_size=%" PRIuSIZ "(%#" PRIxSIZ "), end=%p\n",
					       (uintptr_t)reader - expr_size,
					       expr_size, expr_size, end);
				}
			}	break;

#undef RESULT_CFA
#endif /* !EH_FRAME_FDE_EXEC_CFA_RULE */


#if (defined(EH_FRAME_FDE_EXEC_CFA_STATE) ||          \
     defined(EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE) || \
     defined(EH_FRAME_FDE_EXEC_CFA_LANDING_STATE) ||  \
     defined(EH_FRAME_FDE_EXEC_CFA_RULE))
			CASE(DW_CFA_expression) {
				unwind_regno_t reg;
				reg = (unwind_regno_t)dwarf_decode_uleb128((byte_t const **)&reader);
				LOCAL_setregister(reg, {
					rule->cr_rule = DW_CFA_register_rule_expression;
					rule->cr_expr = reader;
				});
				goto skip_expression;
			}	break;

			CASE(DW_CFA_offset_extended_sf) {
				unwind_regno_t reg;
				intptr_t value;
				reg   = (unwind_regno_t)dwarf_decode_uleb128((byte_t const **)&reader);
				value = (dwarf_decode_sleb128((byte_t const **)&reader) * self->f_dataalign);
				LOCAL_setregister(reg, {
					rule->cr_rule  = DW_CFA_register_rule_offsetn;
					rule->cr_value = value;
				});
			}	break;

			CASE(DW_CFA_val_offset) {
				unwind_regno_t reg;
				intptr_t value;
				reg = (unwind_regno_t)dwarf_decode_uleb128((byte_t const **)&reader);
				value = ((intptr_t)dwarf_decode_uleb128((byte_t const **)&reader) * self->f_dataalign);
				LOCAL_setregister(reg, {
					rule->cr_rule  = DW_CFA_register_rule_val_offsetn;
					rule->cr_value = value;
				});
			}	break;

			CASE(DW_CFA_val_offset_sf) {
				unwind_regno_t reg;
				intptr_t value;
				reg = (unwind_regno_t)dwarf_decode_uleb128((byte_t const **)&reader);
				value = (dwarf_decode_sleb128((byte_t const **)&reader) * self->f_dataalign);
				LOCAL_setregister(reg, {
					rule->cr_rule  = DW_CFA_register_rule_val_offsetn;
					rule->cr_value = value;
				});
			}	break;

			CASE(DW_CFA_val_expression) {
				unwind_regno_t reg;
				reg = (unwind_regno_t)dwarf_decode_uleb128((byte_t const **)&reader);
				LOCAL_setregister(reg, {
					rule->cr_rule = DW_CFA_register_rule_val_expression;
					rule->cr_expr = reader;
				});
				goto skip_expression;
			}	break;

			CASE(DW_CFA_GNU_negative_offset_extended) {
				unwind_regno_t reg;
				intptr_t value;
				reg = (unwind_regno_t)dwarf_decode_uleb128((byte_t const **)&reader);
				value = -((intptr_t)dwarf_decode_uleb128((byte_t const **)&reader) * self->f_dataalign);
				LOCAL_setregister(reg, {
					rule->cr_rule  = DW_CFA_register_rule_offsetn;
					rule->cr_value = value;
				});
			}	break;
#else /* EH_FRAME_FDE_EXEC_CFA_STATE || EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE || EH_FRAME_FDE_EXEC_CFA_RULE */

			CASE(DW_CFA_expression)
			CASE(DW_CFA_val_expression)
				dwarf_decode_uleb128((byte_t const **)&reader);
				goto skip_expression;

#endif /* !EH_FRAME_FDE_EXEC_CFA_STATE && !EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE && !EH_FRAME_FDE_EXEC_CFA_RULE */

			CASE(DW_CFA_GNU_args_size)
				/* Landing pad stack adjustment */
				dwarf_decode_uleb128((byte_t const **)&reader);
				break;

			CASE(DW_CFA_nop) /* no-op. */
				break;

			default:
				ERRORF(err_unknown_instruction, "operand=%#.2" PRIx8 "\n", operand);
			}
		}
	}
#undef local_cfi_unwind_register_dw2uncommon
#undef local_cfi_unwind_register_dw2common
#undef LOCAL_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT
#undef LOCAL_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT
#undef LOCAL_setregister
#ifndef __KERNEL__
	LOCAL_SYM(unwind_cfa_backup_state_freechain)(state_backup_free);
	LOCAL_SYM(unwind_cfa_backup_state_freechain)(state_backup_list);
#endif /* !__KERNEL__ */
	return UNWIND_SUCCESS;
#ifndef __KERNEL__
	{
		unwind_errno_t error;
err_unknown_instruction:
		error = UNWIND_CFA_UNKNOWN_INSTRUCTION;
		goto err_common;
err_nomem:
		error = UNWIND_BADALLOC;
		goto err_common;
err_invalid_register:
		error = UNWIND_INVALID_REGISTER;
		goto err_common;
err_illegal_instruction:
		error = UNWIND_CFA_ILLEGAL_INSTRUCTION;
err_common:
		LOCAL_SYM(unwind_cfa_backup_state_freechain)(state_backup_free);
		LOCAL_SYM(unwind_cfa_backup_state_freechain)(state_backup_list);
		return error;
	}
#else /* !__KERNEL__ */
err_unknown_instruction:
	return UNWIND_CFA_UNKNOWN_INSTRUCTION;
err_nomem:
	return UNWIND_BADALLOC;
err_invalid_register:
	return UNWIND_INVALID_REGISTER;
err_illegal_instruction:
	return UNWIND_CFA_ILLEGAL_INSTRUCTION;
#endif /* __KERNEL__ */
}

#undef LOCAL_IF_SHOULD_APPLY_RULE
#undef LOCAL_SYM

#undef EH_FRAME_FDE_EXEC_CFA_STATE
#undef EH_FRAME_FDE_EXEC_CFA_LANDING_STATE
#undef EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE
#undef EH_FRAME_FDE_EXEC_CFA_RULE
#undef EH_FRAME_FDE_EXEC_CFA_VALUE

DECL_END
