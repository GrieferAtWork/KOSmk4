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
#ifndef _LIBUNWIND_EH_FRAME_H
#define _LIBUNWIND_EH_FRAME_H 1

#include "api.h"
/**/

#include <bits/types.h>

#include "cfi.h"

/* The `.eh_frame' section shall contain 1 or more Call Frame Information (CFI) records.
 * The number of records present shall be determined by size of the section as contained in
 * the section header. Each CFI record contains a Common Information Entry (CIE) record
 * followed by 1 or more Frame Description Entry (FDE) records. Both CIEs and FDEs
 * shall be aligned to an addressing unit sized boundary. */


#undef SIZEOF_UNWIND_ORDER_INDEX_T
#if (((CFI_UNWIND_COMMON_REGISTER_COUNT + CFI_UNWIND_UNCOMMON_REGISTER_COUNT) > 0xffff) || \
     ((CFI_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT + CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT) > 0xffff))
#define SIZEOF_UNWIND_ORDER_INDEX_T 4
#elif (((CFI_UNWIND_COMMON_REGISTER_COUNT + CFI_UNWIND_UNCOMMON_REGISTER_COUNT) > 0xff) || \
       ((CFI_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT + CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT) > 0xff))
#define SIZEOF_UNWIND_ORDER_INDEX_T 2
#else /* ... */
#define SIZEOF_UNWIND_ORDER_INDEX_T 1
#endif /* !... */


/* Figure out if libunwind (should) support CFI capsules.
 * Since CFI capsules are a KOS extension, only support them on
 * KOS (for now, though since they don't need kernel support,
 * nothing is stopping other operating system from supporting
 * them as well).
 * Additionally, don't enable them within the KOS kernel, since
 * capsules add a small amount of overhead to exception handling
 * that isn't actually needed/used within the KOS kernel (though
 * this too can be changed at any point) */
#ifndef __KOS__
#undef LIBUNWIND_CONFIG_SUPPORT_CFI_CAPSULES
#elif defined(__KOS__) && defined(__KERNEL__)
#undef LIBUNWIND_CONFIG_SUPPORT_CFI_CAPSULES
#else /* ... */
#define LIBUNWIND_CONFIG_SUPPORT_CFI_CAPSULES 1
#endif /* !... */


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
#else /* SIZEOF_UNWIND_ORDER_INDEX_T == ... */
#error "Invalid `SIZEOF_UNWIND_ORDER_INDEX_T'"
#endif /* SIZEOF_UNWIND_ORDER_INDEX_T != ... */

#ifndef __unwind_regno_t_defined
#define __unwind_regno_t_defined 1
typedef __UINTPTR_HALF_TYPE__ unwind_regno_t;
#endif /* !__unwind_regno_t_defined */



typedef struct unwind_fde_struct {
	void          *f_pcstart;     /* [<= f_pcend] PC (Program counter) starting address (absolute). */
	void          *f_pcend;       /* [>= f_pcstart] PC (Program counter) end address (absolute). */
	__uintptr_t    f_codealign;   /* Code alignment. (Multiplied with the delta argument of an advance location instruction) */
	__intptr_t     f_dataalign;   /* Data alignment. (Multiplied with the register offset argument of an offset instruction) */
	void          *f_persofun;    /* [0..1] Address of a personality handler function. (absolute) */
	void          *f_lsdaaddr;    /* [0..1] Address of a language-specific data block. (absolute) */
	__byte_t      *f_inittext;    /* [0..1] Pointer to initial EH instructions (usually describing compiler-generated frames) (absolute) */
	__byte_t      *f_inittextend; /* [0..1] End address of `f_inittext'. */
	__byte_t      *f_evaltext;    /* [0..1] Pointer to FDE-specific EH instructions (This is the meat of it all) (absolute) */
	__byte_t      *f_evaltextend; /* [0..1] End address of `f_evaltext'. */
	unwind_regno_t f_retreg;      /* Return-address register number (One of `CFI_[ARCH]_UNWIND_REGISTER_[NAME]'). */
	__uint8_t      f_encptr;      /* Encoding used for pointers (One of `DW_EH_PE_*') */
	__uint8_t      f_sigframe;    /* Non-zero if this is a signal frame. */
	__uint8_t      f_addrsize;    /* Size of an address. */
} unwind_fde_t;


/* Load the next eh_frame function descriptor from `*PEH_FRAME_READER', which
 * must either be a pointer to the start of the `.eh_frame' section, or be the
 * value written back to `*PEH_FRAME_READER' after a previous call to `unwind_fde_load()'.
 * @return: UNWIND_SUCCESS:  Successfully read the next FDE entry.
 * @return: UNWIND_NO_FRAME: Failed to read an FDE entry (Assume EOF) */
typedef __ATTR_NONNULL((1, 2, 3)) unsigned int
(LIBUNWIND_CC *PUNWIND_FDE_LOAD)(__byte_t **__restrict __peh_frame_reader,
                                 __byte_t *__restrict __eh_frame_end,
                                 unwind_fde_t *__restrict __result,
                                 __uint8_t __sizeof_address);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 2, 3)) unsigned int
__NOTHROW_NCX(LIBUNWIND_CC unwind_fde_load)(__byte_t **__restrict __peh_frame_reader,
                                            __byte_t *__restrict __eh_frame_end,
                                            unwind_fde_t *__restrict __result,
                                            __uint8_t __sizeof_address);
#endif /* LIBUNWIND_WANT_PROTOTYPES */

/* Same as `unwind_fde_load()', but quickly search for and return the
 * FDE descriptor containing the given `ABSOLUTE_PC' text address.
 * @assume(!return || RESULT->f_pcstart <= ABSOLUTE_PC);
 * @assume(!return || RESULT->f_pcend > ABSOLUTE_PC);
 * @return: UNWIND_SUCCESS:  Found the FDE entry associated with `ABSOLUTE_PC'.
 * @return: UNWIND_NO_FRAME: Failed to read an FDE entry (Assume EOF) */
typedef __ATTR_NONNULL((1, 2, 4)) unsigned int
(LIBUNWIND_CC *PUNWIND_FDE_SCAN)(__byte_t *__restrict __eh_frame_start,
                                 __byte_t *__restrict __eh_frame_end,
                                 void *__absolute_pc,
                                 unwind_fde_t *__restrict __result,
                                 __uint8_t __sizeof_address);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 2, 4)) unsigned int
__NOTHROW_NCX(LIBUNWIND_CC unwind_fde_scan)(__byte_t *__restrict __eh_frame_start,
                                            __byte_t *__restrict __eh_frame_end,
                                            void *__absolute_pc,
                                            unwind_fde_t *__restrict __result,
                                            __uint8_t __sizeof_address);
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
	unwind_regno_t cv_type;  /* CFA type (One of `UNWIND_CFA_VALUE_*') */
	unwind_regno_t cv_reg;   /* [valid_if(cv_type == UNWIND_CFA_VALUE_REGISTER)] CFA register. */
	union {
		__byte_t  *cv_expr;  /* [valid_if(cv_type == UNWIND_CFA_VALUE_EXPRESSION)][1..1] Expression.
		                      * NOTE: This pointer is directed at a `uleb128', describing
		                      *       the amount of types that follow immediately after,
		                      *       containing expression text. */
		__intptr_t cv_value; /* [valid_if(cv_type == UNWIND_CFA_VALUE_REGISTER)]
		                      * Address offset (added to the value of `cv_reg') */
	};
} unwind_cfa_value_t;

typedef struct unwind_cfa_state_struct {
#if CFI_UNWIND_COMMON_REGISTER_COUNT != 0
	unwind_cfa_register_t cs_regs[CFI_UNWIND_COMMON_REGISTER_COUNT];       /* Common register restore rules. */
#endif /* CFI_UNWIND_COMMON_REGISTER_COUNT != 0 */
#if CFI_UNWIND_UNCOMMON_REGISTER_COUNT != 0
	unwind_order_index_t  cs_uncorder[CFI_UNWIND_UNCOMMON_REGISTER_COUNT]; /* Restore order for uncommon registers (0 means unused). */
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
	unwind_order_index_t  cs_uncorder[CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT]; /* Restore order for uncommon registers (0 means unused). */
#endif /* CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT != 0 */
	unwind_cfa_value_t    cs_cfa; /* Canonical Frame Address evaluation rule. */
} unwind_cfa_sigframe_state_t;

#ifdef LIBUNWIND_CONFIG_SUPPORT_CFI_CAPSULES
typedef struct _unwind_cfa_landing_state_struct {
#if CFI_UNWIND_LANDING_COMMON_REGISTER_COUNT != 0
	unwind_cfa_register_t cs_regs[CFI_UNWIND_LANDING_COMMON_REGISTER_COUNT];       /* Common register restore rules. */
#endif /* CFI_UNWIND_LANDING_COMMON_REGISTER_COUNT != 0 */
#if CFI_UNWIND_LANDING_UNCOMMON_REGISTER_COUNT != 0
	unwind_order_index_t  cs_uncorder[CFI_UNWIND_LANDING_UNCOMMON_REGISTER_COUNT]; /* Restore order for uncommon registers (0 means unused). */
#endif /* CFI_UNWIND_LANDING_UNCOMMON_REGISTER_COUNT != 0 */
	unwind_cfa_value_t    cs_cfa; /* Canonical Frame Address evaluation rule. */
} _unwind_cfa_landing_state_t;
#endif /* LIBUNWIND_CONFIG_SUPPORT_CFI_CAPSULES */

typedef struct unwind_cfa_landing_state_struct {
	__uintptr_t                 cs_lp_adjustment; /* Landing-pad adjustment (~ala `DW_CFA_GNU_args_size') */
#ifdef LIBUNWIND_CONFIG_SUPPORT_CFI_CAPSULES
	__uintptr_t                 cs_has_capsules;  /* Non-zero if `cs_regs[*].cr_order != 0 || cs_uncorder[*] != 0' */
	_unwind_cfa_landing_state_t cs_state;         /* Canonical Frame Address evaluation rule. */
#endif /* LIBUNWIND_CONFIG_SUPPORT_CFI_CAPSULES */
} unwind_cfa_landing_state_t;


/* Execute CFA state instruction until `ABSOLUTE_PC' has been reached,
 * or the entirety of the FDE instruction code has been executed.
 * This function is used to fill in CFA state information at a given address,
 * which can then be used to unwind a register state for the purpose of
 * implementing language-level, zero-effort exception support, as well
 * as for generating tracebacks when combined with `libdebuginfo.so'
 * NOTE: Usually, the caller will have already ensured that:
 *      `SELF->f_pcstart <= ABSOLUTE_PC && SELF->f_pcend >= ABSOLUTE_PC'
 * @param: SELF:   The FDE to execute in search of `ABSOLUTE_PC'
 * @param: RESULT: CFA state descriptor, to-be filled with restore information upon success.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
typedef __ATTR_NONNULL((1, 2)) unsigned int
(LIBUNWIND_CC *PUNWIND_FDE_EXEC)(unwind_fde_t const *__restrict __self,
                                 unwind_cfa_state_t *__restrict __result,
                                 void *__absolute_pc);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 2)) unsigned int
__NOTHROW_NCX(LIBUNWIND_CC unwind_fde_exec)(unwind_fde_t const *__restrict __self,
                                            unwind_cfa_state_t *__restrict __result,
                                            void *__absolute_pc);
#endif /* LIBUNWIND_WANT_PROTOTYPES */



/* Behaves identical to `unwind_fde_exec()', and doesn't actually ever have to be
 * used, but performes better than `unwind_fde_exec()' when unwinding SIGNAL_FRAME
 * FDE descriptors (though again: use of this is entirely optional; the regular
 * `unwind_fde_exec()' is just as capable of unwinding signal frame descriptors.
 * This function is merely optimized to better restore registers commonly used
 * within signal frames)
 * @param: SELF:   The FDE to execute in search of `__absolute_pc'
 * @param: RESULT: CFA state descriptor, to-be filled with restore information upon success.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
typedef __ATTR_NONNULL((1, 2)) unsigned int
(LIBUNWIND_CC *PUNWIND_FDE_SIGFRAME_EXEC)(unwind_fde_t const *__restrict __self,
                                          unwind_cfa_sigframe_state_t *__restrict __result,
                                          void *__absolute_pc);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 2)) unsigned int
__NOTHROW_NCX(LIBUNWIND_CC unwind_fde_sigframe_exec)(unwind_fde_t const *__restrict __self,
                                                     unwind_cfa_sigframe_state_t *__restrict __result,
                                                     void *__absolute_pc);
#endif /* LIBUNWIND_WANT_PROTOTYPES */


/* Behaves similar to `unwind_fde_exec()', but must be used to calculate the CFA
 * for the purpose of jumping to a custom `LANDINGPAD_PC' as part of handling an
 * exceptions which originates from `ABSOLUTE_PC' within the current cfi-proc.
 * This function is calculates the relative CFI-capsule offset between `ABSOLUTE_PC',
 * and `LANDINGPAD_PC', as well as the GNU-argsize adjustment. Once this is done,
 * the caller must use `unwind_cfa_landing_apply()' to apply the these transformations
 * onto some given register state, which may then be used to resume execution.
 * @param: SELF:   The FDE to execute in search of `__absolute_pc'
 * @param: RESULT: CFA state descriptor, to-be filled with restore information upon success.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
typedef __ATTR_NONNULL((1, 2)) unsigned int
(LIBUNWIND_CC *PUNWIND_FDE_LANDING_EXEC)(unwind_fde_t const *__restrict __self,
                                         unwind_cfa_landing_state_t *__restrict __result,
                                         void *__absolute_pc, void *__landingpad_pc);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 2)) unsigned int
__NOTHROW_NCX(LIBUNWIND_CC unwind_fde_landing_exec)(unwind_fde_t const *__restrict __self,
                                                    unwind_cfa_landing_state_t *__restrict __result,
                                                    void *__absolute_pc, void *__landingpad_pc);
#endif /* LIBUNWIND_WANT_PROTOTYPES */



/* Similar to `unwind_fde_exec()', but used to calculate the
 * unwind rule for `dw_regno' at the given text location.
 * This is used to implement unwinding for uncommon registers,
 * since `unwind_fde_exec()' will not already calculate these
 * during the first pass (thus keeping down the memory requirements
 * imposed on the one responsible for allocating `unwind_cfa_state_t')
 * @param: SELF:   The FDE to execute in search of `ABSOLUTE_PC'
 * @param: RESULT: The CFA register result controller to-be filled.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
typedef __ATTR_NONNULL((1, 2)) unsigned int
(LIBUNWIND_CC *PUNWIND_FDE_RULE)(unwind_fde_t const *__restrict __self,
                                 unwind_cfa_register_t *__restrict __result,
                                 unwind_regno_t dw_regno,
                                 void *__absolute_pc);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 2)) unsigned int
__NOTHROW_NCX(LIBUNWIND_CC unwind_fde_rule)(unwind_fde_t const *__restrict __self,
                                            unwind_cfa_register_t *__restrict __result,
                                            unwind_regno_t dw_regno,
                                            void *__absolute_pc);
#endif /* LIBUNWIND_WANT_PROTOTYPES */


/* Same as `unwind_fde_exec()', however only calculate the CFA restore descriptor.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
typedef __ATTR_NONNULL((1, 2)) unsigned int
(LIBUNWIND_CC *PUNWIND_FDE_EXEC_CFA)(unwind_fde_t const *__restrict __self,
                                     unwind_cfa_value_t *__restrict __result,
                                     void *__absolute_pc);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 2)) unsigned int
__NOTHROW_NCX(LIBUNWIND_CC unwind_fde_exec_cfa)(unwind_fde_t const *__restrict __self,
                                                unwind_cfa_value_t *__restrict __result,
                                                void *__absolute_pc);
#endif /* LIBUNWIND_WANT_PROTOTYPES */


/* Apply a given CFA unwind state in order to apply register information from from `REG_GETTER' to `REG_SETTER'.
 * Note however that only registers with a rule other than `DW_CFA_register_rule_undefined'
 * will be applied, meaning that `*REG_SETTER' will not get invoked for these registers.
 * WARNING: This function will modify `SELF' in such a manner that repeated calls
 *          require that `SELF' must be restored to its state prior to a call to
 *          this function before a repeated call can be made!
 * @param: SELF:        The CFA state to-be used when applying registers
 * @param: ABSOLUTE_PC: Same value as was previously used to calculate `FDE' from `SELF'
 * @return: UNWIND_SUCCESS:               ...
 * @return: UNWIND_INVALID_REGISTER:      ...
 * @return: UNWIND_SEGFAULT:              ...
 * @return: UNWIND_EMULATOR_*:            ...
 * @return: UNWIND_APPLY_NOADDR_REGISTER: ... */
typedef __ATTR_NONNULL((1, 2, 4, 6)) unsigned int
(LIBUNWIND_CC *PUNWIND_CFA_APPLY)(unwind_cfa_state_t *__restrict __self,
                                  unwind_fde_t const *__restrict __fde, void *__absolute_pc,
                                  unwind_getreg_t __reg_getter, void const *__reg_getter_arg,
                                  unwind_setreg_t __reg_setter, void *__reg_setter_arg);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 2, 4, 6)) unsigned int LIBUNWIND_CC
unwind_cfa_apply(unwind_cfa_state_t *__restrict __self,
                 unwind_fde_t const *__restrict __fde, void *__absolute_pc,
                 unwind_getreg_t __reg_getter, void const *__reg_getter_arg,
                 unwind_setreg_t __reg_setter, void *__reg_setter_arg);
#endif /* LIBUNWIND_WANT_PROTOTYPES */



/* For use with `unwind_fde_sigframe_exec()': Apply register rules previously calculated.
 * @param: SELF:        The CFA state to-be used when applying registers
 * @param: ABSOLUTE_PC: Same value as was previously used to calculate `FDE' from `SELF'
 * @return: UNWIND_SUCCESS:               ...
 * @return: UNWIND_INVALID_REGISTER:      ...
 * @return: UNWIND_SEGFAULT:              ...
 * @return: UNWIND_EMULATOR_*:            ...
 * @return: UNWIND_APPLY_NOADDR_REGISTER: ... */
typedef __ATTR_NONNULL((1, 2, 4, 6)) unsigned int
(LIBUNWIND_CC *PUNWIND_CFA_SIGFRAME_APPLY)(unwind_cfa_sigframe_state_t *__restrict __self,
                                           unwind_fde_t const *__restrict __fde, void *__absolute_pc,
                                           unwind_getreg_t __reg_getter, void const *__reg_getter_arg,
                                           unwind_setreg_t __reg_setter, void *__reg_setter_arg);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 2, 4, 6)) unsigned int LIBUNWIND_CC
unwind_cfa_sigframe_apply(unwind_cfa_sigframe_state_t *__restrict __self,
                          unwind_fde_t const *__restrict __fde, void *__absolute_pc,
                          unwind_getreg_t __reg_getter, void const *__reg_getter_arg,
                          unwind_setreg_t __reg_setter, void *__reg_setter_arg);
#endif /* LIBUNWIND_WANT_PROTOTYPES */



/* For use with `unwind_fde_landing_exec()': Apply register rules previously calculated.
 * @param: SELF:        The CFA state to-be used when applying registers
 * @param: ABSOLUTE_PC: Same value as was previously used to calculate `FDE' from `SELF'
 * @return: UNWIND_SUCCESS:               ...
 * @return: UNWIND_INVALID_REGISTER:      ...
 * @return: UNWIND_SEGFAULT:              ...
 * @return: UNWIND_EMULATOR_*:            ...
 * @return: UNWIND_APPLY_NOADDR_REGISTER: ... */
typedef __ATTR_NONNULL((1, 2, 4, 6)) unsigned int
(LIBUNWIND_CC *PUNWIND_CFA_LANDING_APPLY)(unwind_cfa_landing_state_t *__restrict __self,
                                          unwind_fde_t const *__restrict __fde, void *__absolute_pc,
                                          unwind_getreg_t __reg_getter, void const *__reg_getter_arg,
                                          unwind_setreg_t __reg_setter, void *__reg_setter_arg);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 2, 4, 6)) unsigned int LIBUNWIND_CC
unwind_cfa_landing_apply(unwind_cfa_landing_state_t *__restrict __self,
                         unwind_fde_t const *__restrict __fde, void *__absolute_pc,
                         unwind_getreg_t __reg_getter, void const *__reg_getter_arg,
                         unwind_setreg_t __reg_setter, void *__reg_setter_arg);
#endif /* LIBUNWIND_WANT_PROTOTYPES */



/* Calculate the CFA (CanonicalFrameAddress) of the given CFA restore descriptor.
 * @param: SELF: The CFA state to-be used to calculate the CFA
 * @return: UNWIND_SUCCESS:               ...
 * @return: UNWIND_INVALID_REGISTER:      ...
 * @return: UNWIND_SEGFAULT:              ...
 * @return: UNWIND_EMULATOR_*:            ...
 * @return: UNWIND_APPLY_NOADDR_REGISTER: ... */
typedef __ATTR_NONNULL((1, 2, 4)) unsigned int
(LIBUNWIND_CC *PUNWIND_CFA_CALCULATE_CFA)(unwind_cfa_value_t const *__restrict __self,
                                          unwind_getreg_t __reg_getter,
                                          void const *__reg_getter_arg,
                                          __uintptr_t *__restrict __presult);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 2, 4)) unsigned int LIBUNWIND_CC
unwind_cfa_calculate_cfa(unwind_cfa_value_t const *__restrict __self,
                         unwind_getreg_t __reg_getter,
                         void const *__reg_getter_arg,
                         __uintptr_t *__restrict __presult);
#endif /* LIBUNWIND_WANT_PROTOTYPES */


__DECL_END
#endif /* __CC__ */


#endif /* !_LIBUNWIND_EH_FRAME_H */
