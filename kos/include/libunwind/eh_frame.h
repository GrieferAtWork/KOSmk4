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
#ifndef _LIBUNWIND_EH_FRAME_H
#define _LIBUNWIND_EH_FRAME_H 1

#include "api.h"
#include "cfi.h"
#include <bits/types.h>

/* The `.eh_frame' section shall contain 1 or more Call Frame Information (CFI) records.
 * The number of records present shall be determined by size of the section as contained in
 * the section header. Each CFI record contains a Common Information Entry (CIE) record
 * followed by 1 or more Frame Description Entry (FDE) records. Both CIEs and FDEs
 * shall be aligned to an addressing unit sized boundary. */


#undef SIZEOF_UNWIND_ORDER_INDEX_T
#if ((CFI_UNWIND_COMMON_REGISTER_COUNT + CFI_UNWIND_UNCOMMON_REGISTER_COUNT) > 0xffff) || \
    ((CFI_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT + CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT) > 0xffff)
#define SIZEOF_UNWIND_ORDER_INDEX_T 4
#elif ((CFI_UNWIND_COMMON_REGISTER_COUNT + CFI_UNWIND_UNCOMMON_REGISTER_COUNT) > 0xff) || \
      ((CFI_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT + CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT) > 0xff)
#define SIZEOF_UNWIND_ORDER_INDEX_T 2
#else
#define SIZEOF_UNWIND_ORDER_INDEX_T 1
#endif

#ifdef __CC__
__DECL_BEGIN


/* Index ordering type used for keeping track of the order
 * in which individual registers should be unwound.
 * While not actually specified by the DWARF standard, KOS will
 * follow a strict unwind order where register rules defined last
 * will get executed before rules defined earlier. */
#if SIZEOF_UNWIND_ORDER_INDEX_T == 4
typedef __uint32_t unwind_order_index_t;
#elif SIZEOF_UNWIND_ORDER_INDEX_T == 2
typedef __uint16_t unwind_order_index_t;
#elif SIZEOF_UNWIND_ORDER_INDEX_T == 1
typedef __uint8_t unwind_order_index_t;
#else
#error "Invalid `SIZEOF_UNWIND_ORDER_INDEX_T'"
#endif


typedef struct unwind_fde_struct {
	void       *f_pcstart;     /* [<= f_pcend] PC (Program counter) starting address (absolute). */
	void       *f_pcend;       /* [>= f_pcstart] PC (Program counter) end address (absolute). */
	__uintptr_t f_codealign;   /* Code alignment. (Multiplied with the delta argument of an advance location instruction) */
	__intptr_t  f_dataalign;   /* Data alignment. (Multiplied with the register offset argument of an offset instruction) */
	void       *f_persofun;    /* [0..1] Address of a personality handler function. (absolute) */
	void       *f_lsdaaddr;    /* [0..1] Address of a language-specific data block. (absolute) */
	__byte_t   *f_inittext;    /* [0..1] Pointer to initial EH instructions (usually describing compiler-generated frames) (absolute) */
	__byte_t   *f_inittextend; /* [0..1] End address of `f_inittext'. */
	__byte_t   *f_evaltext;    /* [0..1] Pointer to FDE-specific EH instructions (This is the meat of it all) (absolute) */
	__byte_t   *f_evaltextend; /* [0..1] End address of `f_evaltext'. */
	__UINTPTR_HALF_TYPE__
	            f_retreg;      /* Return-address register number (One of `CFI_[ARCH]_UNWIND_REGISTER_[NAME]'). */
	__uint8_t   f_encptr;      /* Encoding used for pointers (One of `DW_EH_PE_*') */
	__uint8_t   f_enclsda;     /* Encoding used for LSDA (One of `DW_EH_PE_*') */
	__uint8_t   f_encperso;    /* Encoding used for personality function pointer (One of `DW_EH_PE_*') */
	__uint8_t   f_sigframe;    /* Non-zero if this is a signal frame. */
	__uint8_t   f_addrsize;    /* Size of an address. */
} unwind_fde_t;


/* Load the next eh_frame function descriptor from `*peh_frame_reader', which
 * must either be a pointer to the start of the `.eh_frame' section, to be the
 * value written back to `*peh_frame_reader' after a previous call to `unwind_fde_load()'.
 * @return: UNWIND_SUCCESS:  Successfully read the next FDE entry.
 * @return: UNWIND_NO_FRAME: Failed to read an FDE entry (Assume EOF) */
typedef unsigned int
(LIBUNWIND_CC *PUNWIND_FDE_LOAD)(__byte_t **__restrict peh_frame_reader,
                                 __byte_t *__restrict eh_frame_end,
                                 unwind_fde_t *__restrict result,
                                 __uint8_t sizeof_address);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL unsigned int
__NOTHROW_NCX(LIBUNWIND_CC unwind_fde_load)(__byte_t **__restrict peh_frame_reader,
                                            __byte_t *__restrict eh_frame_end,
                                            unwind_fde_t *__restrict result,
                                            __uint8_t sizeof_address);
#endif /* LIBUNWIND_WANT_PROTOTYPES */

/* Same as `unwind_fde_load()', but quickly search for and return the
 * FDE descriptor containing the given `absolute_pc' text address.
 * @assume(!return || result->f_pcstart <= absolute_pc);
 * @assume(!return || result->f_pcend > absolute_pc);
 * @return: UNWIND_SUCCESS:  Found the FDE entry associated with `ABSOLUTE_PC'.
 * @return: UNWIND_NO_FRAME: Failed to read an FDE entry (Assume EOF) */
typedef unsigned int
(LIBUNWIND_CC *PUNWIND_FDE_SCAN)(__byte_t *__restrict eh_frame_start,
                                 __byte_t *__restrict eh_frame_end,
                                 void *absolute_pc,
                                 unwind_fde_t *__restrict result,
                                 __uint8_t sizeof_address);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL unsigned int
__NOTHROW_NCX(LIBUNWIND_CC unwind_fde_scan)(__byte_t *__restrict eh_frame_start,
                                            __byte_t *__restrict eh_frame_end,
                                            void *absolute_pc,
                                            unwind_fde_t *__restrict result,
                                            __uint8_t sizeof_address);
#endif /* LIBUNWIND_WANT_PROTOTYPES */



typedef struct unwind_cfa_register_struct {
	/* Canonical Frame Address register restore descriptor. */
	union {
		__byte_t         *cr_expr;  /* [valid_if(cr_rule == rule_expression || cr_rule == rule_val_expression)]
		                             * [1..1] Expression.
		                             * NOTE: This pointer is directed at a `dwarf_uleb128_t',
		                             *       describing the amount of types that follow immediately
		                             *       after, containing expression text. */
		__intptr_t        cr_value; /* [valid_if(cr_rule != rule_expression && cr_rule != rule_val_expression)]
		                             * Register value. */
	};
	unwind_order_index_t  cr_order; /* Register restore order index (entries with greater values must be restored first). */
	__uint8_t             cr_rule;  /* Register rule (One of `DW_CFA_register_rule_*') */
#if (SIZEOF_UNWIND_ORDER_INDEX_T + 1) < __SIZEOF_POINTER__
	__uint8_t             cr_pad[sizeof(void *) - (1 + sizeof(unwind_order_index_t))]; /* ... */
#endif /* (SIZEOF_UNWIND_ORDER_INDEX_T + 1) < __SIZEOF_POINTER__ */
} unwind_cfa_register_t;

#define UNWIND_CFA_VALUE_UNSET      0 /* Not set... */
#define UNWIND_CFA_VALUE_REGISTER   1 /* Register location. (default) */
#define UNWIND_CFA_VALUE_EXPRESSION 2 /* Expression. */
typedef struct unwind_cfa_value_struct {
	/* Canonical Frame Address value descriptor. */
	__UINTPTR_HALF_TYPE__ cv_type;  /* CFA type (One of `UNWIND_CFA_VALUE_*') */
	__UINTPTR_HALF_TYPE__ cv_reg;   /* [valid_if(cv_type == UNWIND_CFA_VALUE_REGISTER)] CFA register. */
	union {
		__byte_t         *cv_expr;  /* [valid_if(cv_type == UNWIND_CFA_VALUE_EXPRESSION)][1..1] Expression.
		                             * NOTE: This pointer is directed at a `uleb128', describing
		                             *       the amount of types that follow immediately after,
		                             *       containing expression text. */
		__intptr_t        cv_value; /* [valid_if(cv_type == UNWIND_CFA_VALUE_REGISTER)]
		                             * Address offset (added to the value of `cc_regno') */
	};
} unwind_cfa_value_t;

typedef struct unwind_cfa_state_struct {
#if CFI_UNWIND_COMMON_REGISTER_COUNT != 0
	unwind_cfa_register_t cs_regs[CFI_UNWIND_COMMON_REGISTER_COUNT];       /* Common register restore rules. */
#endif /* CFI_UNWIND_COMMON_REGISTER_COUNT != 0 */
#if CFI_UNWIND_UNCOMMON_REGISTER_COUNT != 0
	unwind_order_index_t cs_uncorder[CFI_UNWIND_UNCOMMON_REGISTER_COUNT]; /* Restore order for uncommon registers (0 means unused). */
#endif /* CFI_UNWIND_UNCOMMON_REGISTER_COUNT != 0 */
	unwind_cfa_value_t    cs_cfa; /* Canonical Frame Address evaluation rule. */
} unwind_cfa_state_t;

typedef struct unwind_cfa_sigframe_state_struct {
	/* WARNING: Do not use the members of this struct directly!
	 *          When libunwind is built with -Os, functions using
	 *          this struct will actually interpret it as though it
	 *          was a `unwind_cfa_state_t'. */
#if CFI_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT != 0
	unwind_cfa_register_t cs_regs[CFI_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT];       /* Common register restore rules. */
#endif /* CFI_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT != 0 */
#if CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT != 0
	unwind_order_index_t cs_uncorder[CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT]; /* Restore order for uncommon registers (0 means unused). */
#endif /* CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT != 0 */
	unwind_cfa_value_t    cs_cfa; /* Canonical Frame Address evaluation rule. */
} unwind_cfa_sigframe_state_t;


/* Execute CFA state instruction until `absolute_pc' has been reached,
 * or the entirety of the FDE instruction code has been executed.
 * This function is used to fill in CFA state information at a given address,
 * which can then be used to unwind a register state for the purpose of
 * implementing language-level, zero-effort exception support, as well
 * as for generating tracebacks when combined with `libdebuginfo.so'
 * NOTE: Usually, the caller will have already ensured that:
 *      `self->f_pcstart <= absolute_pc && self->f_pcend >= absolute_pc'
 * @param: self:   The FDE to execute in search of `absolute_pc'
 * @param: result: CFA state descriptor, to-be filled with restore information upon success.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
typedef unsigned int
(LIBUNWIND_CC *PUNWIND_FDE_EXEC)(unwind_fde_t const *__restrict self,
                                 unwind_cfa_state_t *__restrict result,
                                 void *absolute_pc);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL unsigned int
__NOTHROW_NCX(LIBUNWIND_CC unwind_fde_exec)(unwind_fde_t const *__restrict self,
                                            unwind_cfa_state_t *__restrict result,
                                            void *absolute_pc);
#endif /* LIBUNWIND_WANT_PROTOTYPES */



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
typedef unsigned int
(LIBUNWIND_CC *PUNWIND_FDE_SIGFRAME_EXEC)(unwind_fde_t const *__restrict self,
                                          unwind_cfa_sigframe_state_t *__restrict result,
                                          void *absolute_pc);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL unsigned int
__NOTHROW_NCX(LIBUNWIND_CC unwind_fde_sigframe_exec)(unwind_fde_t const *__restrict self,
                                                     unwind_cfa_sigframe_state_t *__restrict result,
                                                     void *absolute_pc);
#endif /* LIBUNWIND_WANT_PROTOTYPES */



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
typedef unsigned int
(LIBUNWIND_CC *PUNWIND_FDE_RULE)(unwind_fde_t const *__restrict self,
                                 unwind_cfa_register_t *__restrict result,
                                 __UINTPTR_HALF_TYPE__ dw_regno,
                                 void *absolute_pc);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL unsigned int
__NOTHROW_NCX(LIBUNWIND_CC unwind_fde_rule)(unwind_fde_t const *__restrict self,
                                            unwind_cfa_register_t *__restrict result,
                                            __UINTPTR_HALF_TYPE__ dw_regno,
                                            void *absolute_pc);
#endif /* LIBUNWIND_WANT_PROTOTYPES */


/* Same as `unwind_fde_exec()', however only calculate the CFA restore descriptor.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
typedef unsigned int
(LIBUNWIND_CC *PUNWIND_FDE_EXEC_CFA)(unwind_fde_t const *__restrict self,
                                     unwind_cfa_value_t *__restrict result,
                                     void *absolute_pc);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL unsigned int
__NOTHROW_NCX(LIBUNWIND_CC unwind_fde_exec_cfa)(unwind_fde_t const *__restrict self,
                                                unwind_cfa_value_t *__restrict result,
                                                void *absolute_pc);
#endif /* LIBUNWIND_WANT_PROTOTYPES */


/* Similar to `unwind_fde_exec()', but only decode `DW_CFA_GNU_args_size' instructions
 * in order to calculate the proper exception_handler landing-pad-stack-adjustment that
 * is required to properly re-align the stack before jumping to a local exception handler.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
typedef unsigned int
(LIBUNWIND_CC *PUNWIND_FDE_EXEC_LANDING_PAD_ADJUSTMENT)(unwind_fde_t const *__restrict self,
                                                        __uintptr_t *__restrict result,
                                                        void *absolute_pc);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL unsigned int
__NOTHROW_NCX(LIBUNWIND_CC unwind_fde_exec_landing_pad_adjustment)(unwind_fde_t const *__restrict self,
                                                                   __uintptr_t *__restrict psp_adjustment,
                                                                   void *absolute_pc);
#endif /* LIBUNWIND_WANT_PROTOTYPES */


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
typedef unsigned int
(LIBUNWIND_CC *PUNWIND_CFA_APPLY)(unwind_cfa_state_t *__restrict self,
                                  unwind_fde_t const *__restrict fde, void *absolute_pc,
                                  unwind_getreg_t reg_getter, void const *reg_getter_arg,
                                  unwind_setreg_t reg_setter, void *reg_setter_arg);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL unsigned int LIBUNWIND_CC
unwind_cfa_apply(unwind_cfa_state_t *__restrict self,
                 unwind_fde_t const *__restrict fde, void *absolute_pc,
                 unwind_getreg_t reg_getter, void const *reg_getter_arg,
                 unwind_setreg_t reg_setter, void *reg_setter_arg);
#endif /* LIBUNWIND_WANT_PROTOTYPES */



/* For use with `unwind_fde_sigframe_exec()': Apply register rules previously calculated.
 * @param: self:        The CFA state to-be used when applying registers
 * @param: absolute_pc: Same value as was previously used to calculate `fde' from `self'
 * @return: UNWIND_SUCCESS:               ...
 * @return: UNWIND_INVALID_REGISTER:      ...
 * @return: UNWIND_SEGFAULT:              ...
 * @return: UNWIND_EMULATOR_*:            ...
 * @return: UNWIND_APPLY_NOADDR_REGISTER: ... */
typedef unsigned int
(LIBUNWIND_CC *PUNWIND_CFA_SIGFRAME_APPLY)(unwind_cfa_sigframe_state_t *__restrict self,
                                           unwind_fde_t const *__restrict fde, void *absolute_pc,
                                           unwind_getreg_t reg_getter, void const *reg_getter_arg,
                                           unwind_setreg_t reg_setter, void *reg_setter_arg);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL unsigned int LIBUNWIND_CC
unwind_cfa_sigframe_apply(unwind_cfa_sigframe_state_t *__restrict self,
                          unwind_fde_t const *__restrict fde, void *absolute_pc,
                          unwind_getreg_t reg_getter, void const *reg_getter_arg,
                          unwind_setreg_t reg_setter, void *reg_setter_arg);
#endif /* LIBUNWIND_WANT_PROTOTYPES */



/* Calculate the CFA (CanonicalFrameAddress) of the given CFA restore descriptor.
 * @param: self: The CFA state to-be used to calculate the CFA
 * @return: UNWIND_SUCCESS:               ...
 * @return: UNWIND_INVALID_REGISTER:      ...
 * @return: UNWIND_SEGFAULT:              ...
 * @return: UNWIND_EMULATOR_*:            ...
 * @return: UNWIND_APPLY_NOADDR_REGISTER: ... */
typedef unsigned int
(LIBUNWIND_CC *PUNWIND_CFA_CALCULATE_CFA)(unwind_cfa_value_t const *__restrict self,
                                          unwind_getreg_t reg_getter,
                                          void const *reg_callback_arg,
                                          __uintptr_t *__restrict presult);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL unsigned int LIBUNWIND_CC
unwind_cfa_calculate_cfa(unwind_cfa_value_t const *__restrict self,
                         unwind_getreg_t reg_getter,
                         void const *reg_callback_arg,
                         __uintptr_t *__restrict presult);
#endif /* LIBUNWIND_WANT_PROTOTYPES */


__DECL_END
#endif /* __CC__ */


#endif /* !_LIBUNWIND_EH_FRAME_H */
