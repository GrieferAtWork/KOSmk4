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
#ifndef _LIBUNWIND_EH_FRAME_H
#define _LIBUNWIND_EH_FRAME_H 1

#include "api.h"
/**/

#include <kos/anno.h>
#include <bits/types.h>

#include "cfi.h"
#include "errno.h"

/* The `.eh_frame' section shall  contain 1 or more  Call Frame Information (CFI)  records.
 * The number of records present shall be determined by size of the section as contained in
 * the section header.  Each CFI record  contains a Common  Information Entry (CIE)  record
 * followed  by  1  or more  Frame  Description Entry  (FDE)  records. Both  CIEs  and FDEs
 * shall be aligned to an addressing unit sized boundary. */


/* The .eh_frame section consists of the concatenation of each compilation unit's
 * .eh_frame section. In turn, each compilation unit's .eh_frame looks as follows
 * (note that any single CU will usually include the following pattern at least 2
 * times (one CIE and one FDE), but may not do so at all, or may do so more  than
 * once  (or maybe even manage to re-use the CIE of another CU), meaning that the
 * number of repeats of the following pattern can't be assumed to correlate  with
 * the number of CUs):
 *
 ********************************************************************************************************************
 *                                                                                                                  *
 * ┌───────────────────────────────────────────────────────────────────────────────────────┐                        *
 * │ HEADER                                                                                │                        *
 * ├───────────────────────────────────────────────────────────────────────────────────────┘                        *
 * │     uint32_t             eh_chunk_size;      # Chunk size (including _all_ fields)                             *
 * │ #if eh_chunk_size == 0xffffffff                                                                                *
 * │     uint64_t             eh_chunk_size64;    # 64-bit chunk size override. This only exists (and must be       *
 * │                                              # be used instead of `eh_chunk_size'), when `eh_chunk_size'       *
 * │                                              # is equal to `0xffffffff'                                        *
 * │ #endif                                                                                                         *
 * │ #if <SECTION_IS_EH_FRAME>                                                                                      *
 * │     uint32_t             eh_cie_offset;      # Offset to CIE metadata-descriptor block. The absolute CIE start address
 * │                                              # is  calculated  as `(CIE *)((byte_t *)&eh_cie_offset - eh_cie_offset)'.
 * │                                              # iow: the CIE always comes before an FDE                         *
 * │                                              # When equal to `0', what follows is a chunk of out-of-band data (which
 * │                                              # usually contains CIE descriptors), and is simply skipped and ignored
 * │                                              # during unwind parsing.                                          *
 * │ #elif <SECTION_IS_DEBUG_FRAME>                                                                                 *
 * │     uint32_t             eh_cie_offset;      # Same as when `SECTION_IS_EH_FRAME', except:                     *
 * │                                              #  - For CIE location calculation:                                *
 * │                                              #    Instead of: `(CIE *)((byte_t *)&eh_cie_offset - eh_cie_offset)'
 * │                                              #    use:        `(CIE *)((byte_t *)debug_frame_start + eh_cie_offset)'
 * │                                              #  - For FDE vs. skip-chunk determination:                        *
 * │                                              #    Instead of: `0'                                              *
 * │                                              #    use:        `0xffffffff'                                     *
 * │ #endif                                                                                                         *
 * └────────────────────────────────────────────────────────────────────────────────────────                        *
 *                                                                                                                  *
 *                                                                                                                  *
 *                                                                                                                  *
 * ┌───────────────────────────────────────────────────────────────────────────────────────┐                        *
 * │ CIE (as pointed to by `eh_cie_offset')                                                │                        *
 * ├───────────────────────────────────────────────────────────────────────────────────────┘                        *
 * │     uint32_t             cie_size;      # CIE chunk size                                                       *
 * │ #if cie_size == 0xffffffff                                                                                     *
 * │     uint64_t             cie_size64;    # 64-bit chunk size override                                           *
 * │ #endif                                                                                                         *
 * │     uint32_t             cie_id;        # CIE record id (always `0' in .eh_frame / `0xffffffff' in .debug_frame)
 * │     uint8_t              cie_version;   # CIE descriptor version (see below)                                   *
 * │     char                 cie_augstr[];  # inline, NUL-terminated c-string of augmentation options. (see below) *
 * │ #if cie_version >= 4                                                                                           *
 * │     uint8_t              cie_addrsize;  # Address size (for `dwarf_decode_pointer(3)')                         *
 * │                                         # When not present, use `sizeof(void *)' instead!                      *
 * │     uint8_t              cie_segsize;   # Segment selector size (for `dwarf_decode_pointer(3)')                *
 * │                                         # When not present, use `0' instead!                                   *
 * │ #endif                                                                                                         *
 * │     uleb128_t            cie_codealign; # Code alignment (s.a. `unwind_fde_t::f_codealign')                    *
 * │     sleb128_t            cie_dataalign; # Data alignment (s.a. `unwind_fde_t::f_dataalign')                    *
 * │ #if cie_version >= 3                                                                                           *
 * │     uleb128_t            cie_retreg;    # Return register (s.a. `unwind_fde_t::f_retreg')                      *
 * │ #else                                                                                                          *
 * │     uint8_t              cie_retreg;    # Return register (s.a. `unwind_fde_t::f_retreg')                      *
 * │ #endif                                                                                                         *
 * │                                                                                                                *
 * │     // Augmentation data                                                                                       *
 * │ #if cie_augstr[0] == 'z'                                                                                       *
 * │     uleb128_t            cie_auglen;    # Augmentation data length                                             *
 * │     union {                                                                                                    *
 * │         byte_t cie_augdat[cie_auglen];  # Augmentation data                                                    *
 * │         union {                                                                                                *
 * │                                                                                                                *
 * │             uint8_t      cie_lsdaenc;   # [CH == 'L'] Encoding for `cie_lsdaaddr'                              *
 * │                                         # When not present, use `DW_EH_PE_absptr'                              *
 * │                                                                                                                *
 * │             struct {                                                                                           *
 * │                 uint8_t  cie_persoenc;  # Encoding for `cie_persoptr'                                          *
 * │                 [PTR]    cie_persoptr;  # Personality function pointer (s.a. `dwarf_decode_pointer(3)')        *
 * │             }            cie_persofun;  # [CH == 'P'] Personality info (s.a. `unwind_fde_t::f_persofun')       *
 * │                                                                                                                *
 * │             uint8_t      cie_ptrenc;    # [CH == 'R'] Encoding for pointers (s.a. `unwind_fde_t::f_ptrenc')    *
 * │                                         # When not present, use `DW_EH_PE_absptr'                              *
 * │                                                                                                                *
 * │         } cie_augfields[*];             # Augmentation fields are parsed based on the order                    *
 * │                                         # of characters in `cie_augstr', with one field for                    *
 * │                                         # every character, starting with `cie_augstr[1]',                      *
 * │                                         # and ending once '\0' is reached.                                     *
 * │     };                                                                                                         *
 * │ #endif                                                                                                         *
 * │                                                                                                                *
 * │     // Function instrumentation init text (this field extends until the end of the CIE)                        *
 * │     // s.a. `unwind_fde_t::f_inittext' and `unwind_fde_t::f_inittextend'                                       *
 * │     byte_t               cie_inittext[cie_size - offsetof(cie_inittext)];                                      *
 * │                                                                                                                *
 * └────────────────────────────────────────────────────────────────────────────────────────                        *
 *                                                                                                                  *
 *                                                                                                                  *
 *                                                                                                                  *
 * ┌───────────────────────────────────────────────────────────────────────────────────────┐                        *
 * │ FDE (as it appears immediately after `eh_cie_offset' when a CIE is not indicated)     │                        *
 * ├───────────────────────────────────────────────────────────────────────────────────────┘                        *
 * │                                                                                                                *
 * │     // Fields already seen within the header                                                                   *
 * │     uint32_t             fde_size;      # FDE Chunk size                                                       *
 * │ #if fde_size == 0xffffffff                                                                                     *
 * │     uint64_t             fde_size64;    # 64-bit chunk size override                                           *
 * │ #endif                                                                                                         *
 * │     uint32_t             fde_cie_off;   # s.a. `HEADER::eh_cie_offset' (points to a `CIE *cie')                *
 * │                                                                                                                *
 * │     [PTR]                fde_funbase;   # Function base address (encoding is `cie->cie_ptrenc'; s.a. `unwind_fde_t::f_pcstart')
 * │     [PTR]                fde_funsize;   # Function size (encoding is `DW_EH_PE_OFF(cie->cie_ptrenc)'; s.a. `unwind_fde_t::f_pcend')
 * │                                                                                                                *
 * │     // Additional augmentation data                                                                            *
 * │ #if cie->cie_augstr[0] == 'z'                                                                                  *
 * │     uleb128_t            fde_auglen;    # Augmentation data length                                             *
 * │     union {                                                                                                    *
 * │         byte_t fde_augdat[fde_auglen];  # Augmentation data                                                    *
 * │         union {                                                                                                *
 * │                                                                                                                *
 * │             [PTR]        fde_lsda;      # [CH == 'L'] s.a. `unwind_fde_t::f_lsdaaddr' (encoding is `cie->cie_lsdaenc')
 * │                                                                                                                *
 * │             void         fde_sigframe;  # [CH == 'S'] Mark this function as a signal frame (s.a. `unwind_fde_t::f_sigframe')
 * │                                         #             Note that this is only an imaginary field which depends entirely on
 * │                                         #             the associated CIE!                                      *
 * │                                                                                                                *
 * │         } fde_augfields[*];             # Augmentation fields are parsed based on the order of                 *
 * │                                         # characters in `cie->cie_augstr', with one field for                  *
 * │                                         # every character, starting with `cie->cie_augstr[1]',                 *
 * │                                         # and ending once '\0' is reached.                                     *
 * │     };                                                                                                         *
 * │ #endif                                                                                                         *
 * │                                                                                                                *
 * │     // Function instrumentation text (this field extends until the end of the FDE)                             *
 * │     // s.a. `unwind_fde_t::f_evaltext' and `unwind_fde_t::f_evaltextend'                                       *
 * │     byte_t               fde_text[fde_size - offsetof(fde_text)];                                              *
 * │                                                                                                                *
 * └────────────────────────────────────────────────────────────────────────────────────────                        *
 *                                                                                                                  *
 ********************************************************************************************************************
 *
 * Both  `CIE::cie_inittext', as well  as `FDE::fde_text' contain pseudo-instruction
 * sequences in the form of `DW_CFA_*' (s.a. <libunwind/cfi.h>) that are interpreted
 * by:
 *   - `unwind_fde_exec(3)'
 *   - `unwind_fde_sigframe_exec(3)'
 *   - `unwind_fde_landing_exec(3)'
 *   - `unwind_fde_rule(3)'
 *   - `unwind_fde_exec_cfa(3)'
 *
 */





/* Figure  out  if  libunwind  (should)  support  CFI capsules.
 * Since CFI capsules are a KOS extension, only support them on
 * KOS (for now, though since  they don't need kernel  support,
 * nothing  is stopping other  operating system from supporting
 * them as well).
 * Additionally, don't enable them within the KOS kernel,  since
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


#ifndef __unwind_regno_t_defined
#define __unwind_regno_t_defined
typedef __UINTPTR_HALF_TYPE__ unwind_regno_t;
#endif /* !__unwind_regno_t_defined */

typedef struct unwind_fde_struct {
	union {
		struct unwind_bases   f_bases;       /* Base addresses */
		struct {
			__NCX void const *f_tbase;       /* [0..1][in|out] Text base address. */
			__NCX void const *f_dbase;       /* [0..1][in|out] Text base address. */
			__NCX void const *f_pcstart;     /* [<= f_pcend] PC (Program counter) starting address (absolute). */
		};
	};
	__NCX void const         *f_pcend;       /* [>= f_pcstart] PC (Program counter) end address (absolute). */
	__uintptr_t               f_codealign;   /* Code alignment. (Multiplied with the delta argument of an advance location instruction) */
	__intptr_t                f_dataalign;   /* Data alignment. (Multiplied with the register offset argument of an offset instruction) */
	__NCX void const         *f_persofun;    /* [0..1] Address of a personality handler function. (absolute) */
	__NCX void const         *f_lsdaaddr;    /* [0..1] Address of a language-specific data area. (absolute) */
	__NCX __byte_t const     *f_inittext;    /* [0..1] Pointer to initial EH instructions (usually describing compiler-generated frames) (absolute) */
	__NCX __byte_t const     *f_inittextend; /* [0..1] End address of `f_inittext'. */
	__NCX __byte_t const     *f_evaltext;    /* [0..1] Pointer to FDE-specific EH instructions (This is the meat of it all) (absolute) */
	__NCX __byte_t const     *f_evaltextend; /* [0..1] End address of `f_evaltext'. */
	unwind_regno_t            f_retreg;      /* Return-address register number (One of `CFI_[ARCH]_UNWIND_REGISTER_[NAME]'). */
	__uint8_t                 f_ptrenc;      /* Encoding used for pointers (One of `DW_EH_PE_*') */
	__uint8_t                 f_sigframe;    /* Non-zero if this is a signal frame. */
	__uint8_t                 f_addrsize;    /* Size of an address. */
} unwind_fde_t;


/* Load the next eh_frame function  descriptor from `*peh_frame_reader', which  must
 * either be a  pointer to the  start of the  `.eh_frame' section, or  be the  value
 * written back to `*peh_frame_reader' after a previous call to `unwind_fde_load()'.
 * NOTE: The caller must pre-initialize `result->f_tbase' and `result->f_dbase'!
 * @return: UNWIND_SUCCESS:  Successfully read the next FDE entry.
 * @return: UNWIND_NO_FRAME: Failed to read an FDE entry (Assume EOF) */
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t
__NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_FDE_LOAD)(__NCX __byte_t const **__restrict __peh_frame_reader,
                                                __NCX __byte_t const *__eh_frame_end,
                                                unwind_fde_t *__restrict __result,
                                                __uint8_t __sizeof_address);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t
__NOTHROW_NCX(LIBUNWIND_CC unwind_fde_load)(__NCX __byte_t const **__restrict __peh_frame_reader,
                                            __NCX __byte_t const *__eh_frame_end,
                                            unwind_fde_t *__restrict __result,
                                            __uint8_t __sizeof_address);
#endif /* LIBUNWIND_WANT_PROTOTYPES */

/* Same as `unwind_fde_load()', but quickly search for and return the
 * FDE descriptor containing  the given  `absolute_pc' text  address.
 * NOTE: The caller must pre-initialize `result->f_tbase' and `result->f_dbase'!
 * @assume(!return || result->f_pcstart <= absolute_pc);
 * @assume(!return || result->f_pcend > absolute_pc);
 * @return: UNWIND_SUCCESS:  Found the FDE entry associated with `absolute_pc'.
 * @return: UNWIND_NO_FRAME: Failed to read an FDE entry (Assume EOF) */
typedef __ATTR_NONNULL_T((4)) unwind_errno_t
__NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_FDE_SCAN)(__NCX __byte_t const *__eh_frame_start,
                                                __NCX __byte_t const *__eh_frame_end,
                                                __VIRT void const *__absolute_pc,
                                                unwind_fde_t *__restrict __result,
                                                __uint8_t __sizeof_address);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((4)) unwind_errno_t
__NOTHROW_NCX(LIBUNWIND_CC unwind_fde_scan)(__NCX __byte_t const *__eh_frame_start,
                                            __NCX __byte_t const *__eh_frame_end,
                                            __VIRT void const *__absolute_pc,
                                            unwind_fde_t *__restrict __result,
                                            __uint8_t __sizeof_address);
#endif /* LIBUNWIND_WANT_PROTOTYPES */



typedef struct unwind_cfa_register_struct {
	/* Canonical Frame Address register restore descriptor. */
	union {
		__NCX __byte_t const *cr_expr;  /* [valid_if(cr_rule == rule_expression || cr_rule == rule_val_expression)]
		                                 * [1..1] Expression.
		                                 * NOTE: This  pointer  is  directed  at  a  `dwarf_uleb128_t',
		                                 *       describing the amount of types that follow immediately
		                                 *       after, containing expression text. */
		__intptr_t            cr_value; /* [valid_if(cr_rule != rule_expression && cr_rule != rule_val_expression)]
		                                 * Register value. */
	};
	__uint8_t                 cr_rule;  /* Register rule (One of `DW_CFA_register_rule_*') */
	__uint8_t                 cr_pad[sizeof(void *) - 1]; /* ... */
} unwind_cfa_register_t;

#define UNWIND_CFA_VALUE_UNSET      0 /* Not set... */
#define UNWIND_CFA_VALUE_REGISTER   1 /* Register location. (default) */
#define UNWIND_CFA_VALUE_EXPRESSION 2 /* Expression. */
typedef struct unwind_cfa_value_struct {
	/* Canonical Frame Address value descriptor. */
	unwind_regno_t cv_type;  /* CFA type (One of `UNWIND_CFA_VALUE_*') */
	unwind_regno_t cv_reg;   /* [valid_if(cv_type == UNWIND_CFA_VALUE_REGISTER)] CFA register. */
	union {
		__NCX __byte_t const *cv_expr;  /* [1..1][valid_if(cv_type == UNWIND_CFA_VALUE_EXPRESSION)] Expression.
		                                 * NOTE: This pointer is directed at a `uleb128', describing
		                                 *       the  amount of bytes that follow immediately after,
		                                 *       containing expression text. */
		__intptr_t            cv_value; /* [valid_if(cv_type == UNWIND_CFA_VALUE_REGISTER)]
		                                 * Address offset (added to the value of `cv_reg') */
	};
} unwind_cfa_value_t;

typedef struct unwind_cfa_state_struct {
#if CFI_UNWIND_COMMON_REGISTER_MAXCOUNT != 0
	unwind_cfa_register_t cs_regs[CFI_UNWIND_COMMON_REGISTER_MAXCOUNT]; /* Common register restore rules. */
#endif /* CFI_UNWIND_COMMON_REGISTER_MAXCOUNT != 0 */
#if CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT != 0
	byte_t cs_uncommon[(CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT + __CHAR_BIT__) / __CHAR_BIT__]; /* Bitset of used uncommon registers. (last bit is set if any of the others are) */
#endif /* CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT != 0 */
	unwind_cfa_value_t    cs_cfa; /* Canonical Frame Address evaluation rule. */
} unwind_cfa_state_t;

typedef struct unwind_cfa_sigframe_state_struct {
	/* WARNING: Do not  use the  members of  this struct  directly!
	 *          When libunwind is built with `-Os', functions using
	 *          this struct will actually interpret it as though it
	 *          was a `unwind_cfa_state_t'. */
#if CFI_UNWIND_SIGFRAME_COMMON_REGISTER_MAXCOUNT != 0
	unwind_cfa_register_t cs_regs[CFI_UNWIND_SIGFRAME_COMMON_REGISTER_MAXCOUNT];       /* Common register restore rules. */
#endif /* CFI_UNWIND_SIGFRAME_COMMON_REGISTER_MAXCOUNT != 0 */
#if CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MAXCOUNT != 0
	byte_t cs_uncommon[(CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MAXCOUNT + __CHAR_BIT__) / __CHAR_BIT__]; /* Bitset of used uncommon registers. (last bit is set if any of the others are) */
#endif /* CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MAXCOUNT != 0 */
	unwind_cfa_value_t    cs_cfa; /* Canonical Frame Address evaluation rule. */
} unwind_cfa_sigframe_state_t;

#ifdef LIBUNWIND_CONFIG_SUPPORT_CFI_CAPSULES
typedef struct _unwind_cfa_landing_state_struct {
#if CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT != 0
	unwind_cfa_register_t cs_regs[CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT];       /* Common register restore rules. */
#endif /* CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT != 0 */
#if CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT != 0
	byte_t cs_uncommon[(CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT + __CHAR_BIT__) / __CHAR_BIT__]; /* Bitset of used uncommon registers. (last bit is set if any of the others are) */
#endif /* CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT != 0 */
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
typedef __ATTR_NONNULL_T((1, 2)) unwind_errno_t
__NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_FDE_EXEC)(unwind_fde_t *__restrict __self, /* Only non-const for lazy initialized fields! */
                                                unwind_cfa_state_t *__restrict __result,
                                                __VIRT void const *__absolute_pc);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 2)) unwind_errno_t
__NOTHROW_NCX(LIBUNWIND_CC unwind_fde_exec)(unwind_fde_t *__restrict __self, /* Only non-const for lazy initialized fields! */
                                            unwind_cfa_state_t *__restrict __result,
                                            __VIRT void const *__absolute_pc);
#endif /* LIBUNWIND_WANT_PROTOTYPES */



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
typedef __ATTR_NONNULL_T((1, 2)) unwind_errno_t
__NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_FDE_SIGFRAME_EXEC)(unwind_fde_t *__restrict __self, /* Only non-const for lazy initialized fields! */
                                                         unwind_cfa_sigframe_state_t *__restrict __result,
                                                         __VIRT void const *__absolute_pc);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 2)) unwind_errno_t
__NOTHROW_NCX(LIBUNWIND_CC unwind_fde_sigframe_exec)(unwind_fde_t *__restrict __self, /* Only non-const for lazy initialized fields! */
                                                     unwind_cfa_sigframe_state_t *__restrict __result,
                                                     __VIRT void const *__absolute_pc);
#endif /* LIBUNWIND_WANT_PROTOTYPES */


/* Behaves similar to `unwind_fde_exec()', but must  be used to calculate the  CFA
 * for the purpose of jumping to a  custom `landingpad_pc' as part of handling  an
 * exceptions which  originates from  `absolute_pc' within  the current  cfi-proc.
 * This function calculates the relative CFI-capsule offset between `absolute_pc',
 * and `landingpad_pc', as well as the GNU-argsize adjustment. Once this is  done,
 * the caller must use `unwind_cfa_landing_apply()' to apply these transformations
 * onto some given register state, which may then be used to resume execution.
 * @param: self:   The FDE to execute in search of `absolute_pc'
 * @param: result: CFA state descriptor, to-be filled with restore information upon success.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
typedef __ATTR_NONNULL_T((1, 2)) unwind_errno_t
__NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_FDE_LANDING_EXEC)(unwind_fde_t *__restrict __self, /* Only non-const for lazy initialized fields! */
                                                        unwind_cfa_landing_state_t *__restrict __result,
                                                        __VIRT void const *__absolute_pc,
                                                        __NCX void const *__landingpad_pc);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 2)) unwind_errno_t
__NOTHROW_NCX(LIBUNWIND_CC unwind_fde_landing_exec)(unwind_fde_t *__restrict __self, /* Only non-const for lazy initialized fields! */
                                                    unwind_cfa_landing_state_t *__restrict __result,
                                                    __VIRT void const *__absolute_pc,
                                                    __NCX void const *__landingpad_pc);
#endif /* LIBUNWIND_WANT_PROTOTYPES */



/* Similar to `unwind_fde_exec()', but used to calculate the unwind rule
 * for `dw_regno' at the given text location. This is used to  implement
 * unwinding  for uncommon registers, since `unwind_fde_exec()' will not
 * already  calculate these during the first pass (thus keeping down the
 * memory requirements  imposed on  the one  responsible for  allocating
 * `unwind_cfa_state_t')
 * @param: self:   The FDE to execute in search of `absolute_pc'
 * @param: result: The CFA register result controller to-be filled.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
typedef __ATTR_NONNULL_T((1, 2)) unwind_errno_t
__NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_FDE_RULE)(unwind_fde_t *__restrict __self, /* Only non-const for lazy initialized fields! */
                                                unwind_cfa_register_t *__restrict __result,
                                                unwind_regno_t __dw_regno,
                                                __VIRT void const *__absolute_pc);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 2)) unwind_errno_t
__NOTHROW_NCX(LIBUNWIND_CC unwind_fde_rule)(unwind_fde_t *__restrict __self, /* Only non-const for lazy initialized fields! */
                                            unwind_cfa_register_t *__restrict __result,
                                            unwind_regno_t __dw_regno,
                                            __VIRT void const *__absolute_pc);
#endif /* LIBUNWIND_WANT_PROTOTYPES */


/* Same as `unwind_fde_exec()', however only calculate the CFA restore descriptor.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
typedef __ATTR_NONNULL_T((1, 2)) unwind_errno_t
__NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_FDE_EXEC_CFA)(unwind_fde_t *__restrict __self, /* Only non-const for lazy initialized fields! */
                                                    unwind_cfa_value_t *__restrict __result,
                                                    __VIRT void const *__absolute_pc);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 2)) unwind_errno_t
__NOTHROW_NCX(LIBUNWIND_CC unwind_fde_exec_cfa)(unwind_fde_t *__restrict __self, /* Only non-const for lazy initialized fields! */
                                                unwind_cfa_value_t *__restrict __result,
                                                __VIRT void const *__absolute_pc);
#endif /* LIBUNWIND_WANT_PROTOTYPES */


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
typedef __ATTR_NONNULL_T((1, 2, 4, 6)) unwind_errno_t
(LIBUNWIND_CC *PUNWIND_CFA_APPLY)(unwind_cfa_state_t *__restrict __self,
                                  unwind_fde_t *__restrict __fde, /* Only non-const for lazy initialized fields! */
                                  __VIRT void const *__absolute_pc,
                                  unwind_getreg_t __reg_getter, void const *__reg_getter_arg,
                                  unwind_setreg_t __reg_setter, void *__reg_setter_arg);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 2, 4, 6)) unwind_errno_t LIBUNWIND_CC
unwind_cfa_apply(unwind_cfa_state_t *__restrict __self,
                 unwind_fde_t *__restrict __fde, /* Only non-const for lazy initialized fields! */
                 __VIRT void const *__absolute_pc,
                 unwind_getreg_t __reg_getter, void const *__reg_getter_arg,
                 unwind_setreg_t __reg_setter, void *__reg_setter_arg);
#endif /* LIBUNWIND_WANT_PROTOTYPES */



/* For use with `unwind_fde_sigframe_exec()': Apply register rules previously calculated.
 * @param: self:        The CFA state to-be used when applying registers
 * @param: absolute_pc: Same value as was previously used to calculate `fde' from `self'
 * @return: UNWIND_SUCCESS:               ...
 * @return: UNWIND_INVALID_REGISTER:      ...
 * @return: UNWIND_SEGFAULT:              ...
 * @return: UNWIND_EMULATOR_*:            ...
 * @return: UNWIND_APPLY_NOADDR_REGISTER: ... */
typedef __ATTR_NONNULL_T((1, 2, 4, 6)) unwind_errno_t
(LIBUNWIND_CC *PUNWIND_CFA_SIGFRAME_APPLY)(unwind_cfa_sigframe_state_t *__restrict __self,
                                           unwind_fde_t *__restrict __fde, /* Only non-const for lazy initialized fields! */
                                           __VIRT void const *__absolute_pc,
                                           unwind_getreg_t __reg_getter, void const *__reg_getter_arg,
                                           unwind_setreg_t __reg_setter, void *__reg_setter_arg);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 2, 4, 6)) unwind_errno_t LIBUNWIND_CC
unwind_cfa_sigframe_apply(unwind_cfa_sigframe_state_t *__restrict __self,
                          unwind_fde_t *__restrict __fde, /* Only non-const for lazy initialized fields! */
                          __VIRT void const *__absolute_pc,
                          unwind_getreg_t __reg_getter, void const *__reg_getter_arg,
                          unwind_setreg_t __reg_setter, void *__reg_setter_arg);
#endif /* LIBUNWIND_WANT_PROTOTYPES */



/* For use with `unwind_fde_landing_exec()': Apply register rules previously calculated.
 * @param: self:        The CFA state to-be used when applying registers
 * @param: absolute_pc: Same value as was previously used to calculate `fde' from `self'
 * @return: UNWIND_SUCCESS:               ...
 * @return: UNWIND_INVALID_REGISTER:      ...
 * @return: UNWIND_SEGFAULT:              ...
 * @return: UNWIND_EMULATOR_*:            ...
 * @return: UNWIND_APPLY_NOADDR_REGISTER: ... */
typedef __ATTR_NONNULL_T((1, 2, 4, 6)) unwind_errno_t
(LIBUNWIND_CC *PUNWIND_CFA_LANDING_APPLY)(unwind_cfa_landing_state_t *__restrict __self,
                                          unwind_fde_t *__restrict __fde, /* Only non-const for lazy initialized fields! */
                                          __VIRT void const *__absolute_pc,
                                          unwind_getreg_t __reg_getter, void const *__reg_getter_arg,
                                          unwind_setreg_t __reg_setter, void *__reg_setter_arg);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 2, 4, 6)) unwind_errno_t LIBUNWIND_CC
unwind_cfa_landing_apply(unwind_cfa_landing_state_t *__restrict __self,
                         unwind_fde_t *__restrict __fde, /* Only non-const for lazy initialized fields! */
                         __VIRT void const *__absolute_pc,
                         unwind_getreg_t __reg_getter, void const *__reg_getter_arg,
                         unwind_setreg_t __reg_setter, void *__reg_setter_arg);
#endif /* LIBUNWIND_WANT_PROTOTYPES */



/* Calculate the CFA (CanonicalFrameAddress) of the given CFA restore descriptor.
 * @param: self: The CFA state to-be used to calculate the CFA
 * @return: UNWIND_SUCCESS:               ...
 * @return: UNWIND_INVALID_REGISTER:      ...
 * @return: UNWIND_SEGFAULT:              ...
 * @return: UNWIND_EMULATOR_*:            ...
 * @return: UNWIND_APPLY_NOADDR_REGISTER: ... */
typedef __ATTR_NONNULL_T((1, 2, 3, 5)) unwind_errno_t
(LIBUNWIND_CC *PUNWIND_FDE_CALCULATE_CFA)(unwind_fde_t *__restrict __fde, /* Only non-const for lazy initialized fields! */
                                          unwind_cfa_value_t const *__restrict __self,
                                          unwind_getreg_t __reg_getter,
                                          void const *__reg_getter_arg,
                                          __uintptr_t *__restrict __presult);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 2, 3, 5)) unwind_errno_t LIBUNWIND_CC
unwind_fde_calculate_cfa(unwind_fde_t *__restrict __fde, /* Only non-const for lazy initialized fields! */
                         unwind_cfa_value_t const *__restrict __self,
                         unwind_getreg_t __reg_getter,
                         void const *__reg_getter_arg,
                         __uintptr_t *__restrict __presult);
#endif /* LIBUNWIND_WANT_PROTOTYPES */


__DECL_END
#endif /* __CC__ */


#endif /* !_LIBUNWIND_EH_FRAME_H */
