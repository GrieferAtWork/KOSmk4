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
#ifndef _ARM_KOS_LIBUNWIND_ARM_EXTAB_H
#define _ARM_KOS_LIBUNWIND_ARM_EXTAB_H 1

#include <libunwind/api.h>
/**/

#include <__crt.h>

#include <hybrid/__assert.h>
#include <hybrid/typecore.h>

#include <bits/crt/inttypes.h>
#include <bits/types.h>

#include <libunwind/except.h>

/*
 * Unwinding support for ".ARM.extab" (and ".ARM.exidx")
 *
 * Refs:
 * - https://github.com/ARM-software/abi-aa/releases/download/2022Q1/ehabi32.pdf
 */

#ifdef __CC__
__DECL_BEGIN

/************************************************************************/
/* SECTION .ARM.exidx                                                   */
/************************************************************************/

/* Special value for `aeie_extab_prel31': unwinding isn't possible. */
#define EXIDX_CANTUNWIND 0x1

/* Encode a prel31 word, given a pointer to its address. */
#define ARM_prel31_decode(p_word) \
	((__byte_t *)(p_word) + ((*(__int32_t *)(p_word) << 1) >> 1))

struct ARM_exidx_entry {
	__uint32_t aeie_fbase_prel31; /* PREL31 encoded starting address of linked function (0x80000000 must be clear). */
	__uint32_t aeie_extab_prel31; /* 1: [(. & 0x80000000) == 0] PREL31 encoded address of the exception table entry
	                               * 2: [(. & 0x80000000) != 0] The exception handling table entry itself (inlined)
	                               *                            s.a.           `ARM_extab_entry::aete_perso_prel31'
	                               * 3: [. == EXIDX_CANTUNWIND] Unwinding is impossible. */
};



/* Locate the entry corresponding to a given `absolute_pc' within a given `.ARM.exidx' section.
 * @return: * :   Address of `.ARM.exidx' entry corresponding to `absolute_pc'
 * @return: NULL: No unwind entry associated with `absolute_pc' */
typedef __ATTR_PURE_T __ATTR_WUNUSED_T __ATTR_NONNULL_T((1, 2)) struct ARM_exidx_entry const *
__NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_ARM_EXIDX_LOCATE)(__byte_t const *__ARM_exidx_start,
                                                        __byte_t const *__ARM_exidx_end,
                                                        void const *__absolute_pc);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) struct ARM_exidx_entry const *
__NOTHROW_NCX(LIBUNWIND_CC unwind_ARM_exidx_locate)(__byte_t const *__ARM_exidx_start,
                                                    __byte_t const *__ARM_exidx_end,
                                                    void const *__absolute_pc);
#endif /* LIBUNWIND_WANT_PROTOTYPES */




/************************************************************************/
/* SECTION .ARM.extab                                                   */
/************************************************************************/
struct ARM_extab_entry {
	__uint32_t aete_perso_prel31; /* 1: [(. & 0x80000000) == 0] PREL31 encoded address of personality function (`_Unwind_Personality_Fn').
	                               * 2: [(. & 0xf0000000) == 0x80000000] Compact  run-time  support  personality  function
	                               *                                     Function is selected by `0x0f000000' (bits 24-27)
	                               *                                     Remaining bytes are already part of data-area */
	/* Unwind data for personality function. A pointer to this data area
	 * is returned by `_Unwind_GetLanguageSpecificData(3E)' when  called
	 * from within a `_Unwind_Personality_Fn'
	 *
	 * For run-time support personality function, the format of this area,
	 * as well as any bytes in-lined in `aete_perso_prel31' is  documented
	 * in `10.3 Frame unwinding instructions' of `ehabi32.pdf'.
	 */
	__COMPILER_FLEXIBLE_ARRAY(__uint32_t, aete_perso_data);
};


/* Pre-defined run-time support personality functions.
 * Personality functions are selected by bits 24-27 of `ARM_extab_entry::aete_perso_prel31'
 *
 * Note that for obvious reasons, the KOS kernel will not invoke user-space  personality
 * functions when unwinding a user-space stack (such as in the built-in debugger). Thus,
 * it will _ONLY_ interpret run-time support personality functions. */
#define ARM_EXTAB_RTSUP_PERSO___AEABI_UNWIND_CPP_PR0 0  /* __aeabi_unwind_cpp_pr0 */
#define ARM_EXTAB_RTSUP_PERSO___AEABI_UNWIND_CPP_PR1 1  /* __aeabi_unwind_cpp_pr1 */
#define ARM_EXTAB_RTSUP_PERSO___AEABI_UNWIND_CPP_PR2 2  /* __aeabi_unwind_cpp_pr2 */
#define ARM_EXTAB_RTSUP_PERSO_RESERVED3              3  /* reserved */
#define ARM_EXTAB_RTSUP_PERSO_RESERVED4              4  /* reserved */
#define ARM_EXTAB_RTSUP_PERSO_RESERVED5              5  /* reserved */
#define ARM_EXTAB_RTSUP_PERSO_RESERVED6              6  /* reserved */
#define ARM_EXTAB_RTSUP_PERSO_RESERVED7              7  /* reserved */
#define ARM_EXTAB_RTSUP_PERSO_RESERVED8              8  /* reserved */
#define ARM_EXTAB_RTSUP_PERSO_RESERVED9              9  /* reserved */
#define ARM_EXTAB_RTSUP_PERSO_RESERVED10             10 /* reserved */
#define ARM_EXTAB_RTSUP_PERSO_RESERVED11             11 /* reserved */
#define ARM_EXTAB_RTSUP_PERSO_RESERVED12             12 /* reserved */
#define ARM_EXTAB_RTSUP_PERSO_RESERVED13             13 /* reserved */
#define ARM_EXTAB_RTSUP_PERSO_RESERVED14             14 /* reserved */
#define ARM_EXTAB_RTSUP_PERSO_RESERVED15             15 /* reserved */


/* ABI runtime support unwind functions.
 *
 * Specs require programs that index these functions in `ARM_extab_entry::aete_perso_prel31'
 * to produce `R_ARM_NONE' relocations against them (even though these relocations don't end
 * up  being acted upon by the RTLD). However, since they're referenced, they have to appear
 * as publicly visible, and must therefor be apart of the public interface.
 *
 * For the sake of simplicity, these functions are implemented by libunwind, however  libc
 * also exports them via IFUNC aliases which in turn will lazily load and link against our
 * library ("libunwind.so"). */
typedef _Unwind_Personality_Fn P__AEABI_UNWIND_CPP_PR0;
typedef _Unwind_Personality_Fn P__AEABI_UNWIND_CPP_PR1;
typedef _Unwind_Personality_Fn P__AEABI_UNWIND_CPP_PR2;
typedef __ATTR_NONNULL_T((2, 3)) _Unwind_Reason_Code __NOTHROW_NCX_T(__LIBKCALL P__AEABI_UNWIND_CPP_PRN)(_Unwind_State __state, _Unwind_Control_Block *__ucbp, _Unwind_Context *__context, unsigned int __n);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((2, 3)) _Unwind_Reason_Code __NOTHROW_NCX(__LIBKCALL __aeabi_unwind_cpp_pr0)(_Unwind_State __state, _Unwind_Control_Block *__ucbp, _Unwind_Context *__context);
LIBUNWIND_DECL __ATTR_NONNULL((2, 3)) _Unwind_Reason_Code __NOTHROW_NCX(__LIBKCALL __aeabi_unwind_cpp_pr1)(_Unwind_State __state, _Unwind_Control_Block *__ucbp, _Unwind_Context *__context);
LIBUNWIND_DECL __ATTR_NONNULL((2, 3)) _Unwind_Reason_Code __NOTHROW_NCX(__LIBKCALL __aeabi_unwind_cpp_pr2)(_Unwind_State __state, _Unwind_Control_Block *__ucbp, _Unwind_Context *__context);
LIBUNWIND_DECL __ATTR_NONNULL((2, 3)) _Unwind_Reason_Code __NOTHROW_NCX(__LIBKCALL __aeabi_unwind_cpp_prN)(_Unwind_State __state, _Unwind_Control_Block *__ucbp, _Unwind_Context *__context, unsigned int __n);
#endif /* LIBUNWIND_WANT_PROTOTYPES */


/*
 * Format of data processed by `__aeabi_unwind_cpp_prN':
 *
 * - Uses a byte-instruction stream from `struct ARM_extab_entry' / `struct ARM_exidx_entry'
 * - Variables:
 *   >> uint8_t   INSTRUCTIONS[];    // Terminated by "finish" instruction
 *   >> uint32_t *DESCRIPTORS_BASE;  // [0..1]
 *   >> bool      DESCRIPTORS_16BIT; // [valid_if(DESCRIPTORS_BASE != NULL)]
 *   Setup (s.a. `struct ARM_unwind_rt_emulator'):
 *   >> if (exidx->aeie_extab_prel31 & 0x80000000) {
 *   >>     // Only `ARM_EXTAB_RTSUP_PERSO___AEABI_UNWIND_CPP_PR0' can be inlined
 *   >>     assert((exidx->aeie_extab_prel31 & 0xff000000) == 0x80000000);
 *   >>     INSTRUCTIONS = [exidx->aeie_extab_prel31 & 0xff0000 >> 16,
 *   >>                     exidx->aeie_extab_prel31 & 0x00ff00 >> 8,
 *   >>                     exidx->aeie_extab_prel31 & 0x0000ff];
 *   >>     DESCRIPTORS_BASE = NULL;
 *   >> } else {
 *   >>     if (N == 0) { // Su16
 *   >>         DESCRIPTORS_16BIT = true;
 *   >>         INSTRUCTIONS = [extab->aete_perso_prel31 & 0xff0000 >> 16,
 *   >>                         extab->aete_perso_prel31 & 0x00ff00 >> 8,
 *   >>                         extab->aete_perso_prel31 & 0x0000ff];
 *   >>         DESCRIPTORS_BASE = extab->aete_perso_data;
 *   >>     } else {
 *   >>         uint8_t extra_word = extab->aete_perso_prel31 & 0xff0000 >> 16;
 *   >>         DESCRIPTORS_16BIT = N == 1; // N==1: Lu16; else: Lu32
 *   >>         INSTRUCTIONS = [extab->aete_perso_prel31 & 0x00ff00 >> 8,
 *   >>                         extab->aete_perso_prel31 & 0x0000ff];
 *   >>         uint32_t *iter = extab->aete_perso_data;
 *   >>         for (; extra_word; --extra_word) {
 *   >>             uint32_t word = *iter++;
 *   >>             INSTRUCTIONS.append(word & 0xff000000 >> 24);
 *   >>             INSTRUCTIONS.append(word & 0x00ff0000 >> 16);
 *   >>             INSTRUCTIONS.append(word & 0x0000ff00 >> 8);
 *   >>             INSTRUCTIONS.append(word & 0x000000ff);
 *   >>         }
 *   >>         DESCRIPTORS_BASE = iter;
 *   >>     }
 *   >> }
 *   >> INSTRUCTIONS.append(0b10110000); // Implied "finish"
 *
 * Processing of `INSTRUCTIONS' (note that register names like `SP' are the standard arm register indices):
 * >> int i = 0;
 * >> bool did_set_pc = false;
 * >> for (;;) {
 * >> #define readbyte() INSTRUCTIONS[i++]
 * >>     uint8_t opcode = readbyte();
 * >>     switch (opcode) {
 * >>
 * >>     case 0b00xxxxxx: // for VRS[SP] += 0x04..0x100;
 * >>         VRS[SP] = VRS[SP] + ((opcode & 0x3f) << 2) + 4;
 * >>         break;
 * >>
 * >>     case 0b01xxxxxx: // for VRS[SP] -= 0x04..0x100;
 * >>         VRS[SP] = VRS[SP] - ((opcode & 0x3f) << 2) - 4;
 * >>         break;
 * >>
 * >>     case 0b1000xxxx: // Pop registers {r4,...,r15}
 * >>         uint16_t mask = ((opcode & 0xf) << 8) | readbyte();
 * >>         if (mask == 0) {
 * >>             // Refuse to unwind (for debug tracebacks: try another unwind mechanism)
 * >>             return _URC_FAILURE;
 * >>         }
 * >>         uint32_t vsp = VRS[SP];
 * >>         bool loadsp  = (mask & (1 << (SP - 4))) != 0;
 * >>         if (mask & (1 << (PC - 4)))
 * >>             did_set_pc = true;
 * >>         for (uint8_t regno = 4; mask; ++regno, mask >>= 1) {
 * >>             if (mask & 1) {
 * >>                 VRS[regno] = *(uint32_t *)vsp;
 * >>                 vsp += 4;
 * >>             }
 * >>         }
 * >>         if (!loadsp)
 * >>             VRS[SP] = vsp;
 * >>         break;
 * >>
 * >>     case 0b1001xxxx: // Set vsp from register
 * >>         uint8_t regno = opcode & 0xf;
 * >>         if (regno == 13 || regno == 15)
 * >>             return _URC_FAILURE; // Reserved instructions
 * >>         VRS[SP] = VRS[regno];
 * >>         break;
 * >>
 * >>     case 0b1010xxxx: // Pop {r4,...,r12[,r14]}
 * >>         uint8_t pop_rmax = 4 + (opcode & 7);
 * >>         bool pop_r14 = (opcode & 8) != 0;
 * >>         for (uint8_t regno = 4; regno <= pop_rmax; ++regno) {
 * >>             VRS[regno] = *(uint32_t *)VRS[SP];
 * >>             VRS[SP] += 4;
 * >>         }
 * >>         if (pop_r14) {
 * >>             VRS[14] = *(uint32_t *)VRS[SP];
 * >>             VRS[SP] += 4;
 * >>         }
 * >>         break;
 * >>
 * >>     case 0b10110000: // finish
 * >>         if (!did_set_pc)
 * >>             VRS[PC] = VRS[LR];
 * >>         goto done;
 * >>
 * >>     case 0b10110001: // Pop registers {r0,...,r3}
 * >>         opcode = readbyte();
 * >>         if ((opcode & 0xf0) != 0)
 * >>             return _URC_FAILURE; // Bad opcode
 * >>         if ((opcode & 0x0f) == 0)
 * >>             return _URC_FAILURE; // Bad opcode
 * >>         uint8_t mask = opcode & 0x0f;
 * >>         for (uint8_t regno = 0; mask; ++regno, mask >>= 1) {
 * >>             if (mask & 1) {
 * >>                 VRS[regno] = *(uint32_t *)VRS[SP];
 * >>                 VRS[SP] += 4;
 * >>             }
 * >>         }
 * >>         goto done;
 * >>
 * >>     case 0b10110010: // Large offsets for SP
 * >>         uleb128_t offset = read_uleb128(INSTRUCTIONS, &i);
 * >>         VRS[SP] = VRS[SP] + 0x204 + (offset << 2);
 * >>         break;
 * >>
 * >>     case 0b10110011: // TODO: Pop floating-point registers
 * >>     case 0b10110100: // TODO: Pop Return Address Authentication Code pseudo-register
 * >>     case 0b10111xxx: // TODO: Pop VFP double-precision registers D[8]-D[8+nnn] saved (as if) by FSTMFDX
 * >>     case 0b11000xxx: // TODO: Intel Wireless MMX pop wR[10]-wR[10+nnn]
 * >>     case 0b11000110: // TODO: Intel Wireless MMX pop wR[ssss]-wR[ssss+cccc]
 * >>     case 0b11000111: // TODO: Intel Wireless MMX pop wCGR registers under mask {wCGR3,2,1,0}
 * >>     case 0b11001000: // TODO: Pop VFP double precision registers D[16+ssss]-D[16+ssss+cccc] saved (as if) by VPUSH
 * >>     case 0b11001001: // TODO: Pop VFP double-precision registers D[8]-D[8+nnn] saved (as if) by VPUSH
 * >>
 * >>     default:
 * >>         return _URC_FAILURE; // Bad opcode
 * >>     }
 * >> }
 * >> done:;
 */


struct ARM_unwind_rt_emulator {
	__uint32_t const *aure_instr_data;  /* [0..aure_instr_datac] Pointer to where to load extra data words. */
	__uint32_t        aure_instr_word;  /* [valid_if(aure_instr_wordc != 0)] Current data word
	                                     * Most  significant  byte is  next  instruction byte. */
	__uint8_t         aure_instr_wordc; /* [<= 3] # of instruction bytes still left in `aure_instr_word' */
	__uint8_t         aure_instr_datac; /* # of additional (32-bit) words of 4-instruction tuples to read from `aure_instr_data' */
};

#ifdef NDEBUG
#define _ARM_unwind_rt_emulator_init_inline_dbg_init(self) /* nothing */
#elif __SIZEOF_POINTER__ == 4
#define _ARM_unwind_rt_emulator_init_inline_dbg_init(self) ((self)->aure_instr_data = (__uint32_t const *)__UINT32_C(0xcccccccc)),
#elif __SIZEOF_POINTER__ == 8
#define _ARM_unwind_rt_emulator_init_inline_dbg_init(self) ((self)->aure_instr_data = (__uint32_t const *)__UINT64_C(0xcccccccccccccccc)),
#elif __SIZEOF_POINTER__ == 2
#define _ARM_unwind_rt_emulator_init_inline_dbg_init(self) ((self)->aure_instr_data = (__uint32_t const *)__UINT16_C(0xcccc)),
#elif __SIZEOF_POINTER__ == 1
#define _ARM_unwind_rt_emulator_init_inline_dbg_init(self) ((self)->aure_instr_data = (__uint32_t const *)__UINT8_C(0xcc)),
#else /* __SIZEOF_POINTER__ == ... */
#define _ARM_unwind_rt_emulator_init_inline_dbg_init(self) /* nothing */
#endif /* __SIZEOF_POINTER__ != ... */

/* >> void ARM_unwind_rt_emulator_init_inline(struct ARM_unwind_rt_emulator *self,
 * >>                                         uint32_t aeie_extab_prel31);
 * Initialize `self' from an inlined `aeie_extab_prel31' word */
#define ARM_unwind_rt_emulator_init_inline(self, aeie_extab_prel31)      \
	(__hybrid_assertf(((aeie_extab_prel31)&__UINT32_C(0x80000000)) != 0, \
	                  "Not an inlined word:\n"                           \
	                  "aeie_extab_prel31 = %#" __PRI4_PREFIX "x",        \
	                  (__uint32_t)(aeie_extab_prel31)),                  \
	 _ARM_unwind_rt_emulator_init_inline_dbg_init(self)                  \
	 (self)->aure_instr_word  = (__uint32_t)(aeie_extab_prel31) << 8,    \
	 (self)->aure_instr_wordc = 3,                                       \
	 (self)->aure_instr_datac = 0)

/* >> void ARM_unwind_rt_emulator_init_extab(struct ARM_unwind_rt_emulator *self,
 * >>                                        struct ARM_extab_entry const *extab_entry);
 * Initialize `self' from a given `extab_entry' */
#define ARM_unwind_rt_emulator_init_extab(self, extab_entry)                                       \
	((self)->aure_instr_data = (extab_entry)->aete_perso_data,                                     \
	 (self)->aure_instr_word = (extab_entry)->aete_perso_prel31,                                   \
	 __hybrid_assertf(((self)->aure_instr_word & __UINT32_C(0x80000000)) != 0,                     \
	                  "Not a run-time support personality function:\n"                             \
	                  "aete_perso_prel31 = %#" __PRI4_PREFIX "x",                                  \
	                  (self)->aure_instr_word),                                                    \
	 __hybrid_assertf(((self)->aure_instr_word & __UINT32_C(0x0f000000)) < __UINT32_C(0x03000000), \
	                  "Unsupported a run-time support personality function:\n"                     \
	                  "aete_perso_prel31 = %#" __PRI4_PREFIX "x",                                  \
	                  (self)->aure_instr_word),                                                    \
	 ((self)->aure_instr_word & __UINT32_C(0x0f000000)) == 0                                       \
	 ? (void)((self)->aure_instr_wordc = 3, /* Su16 */                                             \
	          (self)->aure_instr_datac = 0,                                                        \
	          (self)->aure_instr_word <<= 8)                                                       \
	 : (void)((self)->aure_instr_wordc = 2, /* Lu16 / Lu32 */                                      \
	          (self)->aure_instr_datac = ((self)->aure_instr_word >> 16) & 0xff,                   \
	          (self)->aure_instr_word <<= 16))

/* Initialize `self' from a given `exidx_entry'
 * @return: NULL: Initialized `self'
 * @return: * :   Cannot initialize RT-emulator because the returned,
 *                custom personality function  must be used  instead. */
__LOCAL __ATTR_NONNULL((1, 2)) _Unwind_Personality_Fn
__NOTHROW(LIBUNWIND_CC ARM_unwind_rt_emulator_init)(struct ARM_unwind_rt_emulator *__restrict self,
                                                    struct ARM_exidx_entry const *__restrict exidx_entry) {
	__uint32_t extab_prel31 = exidx_entry->aeie_extab_prel31;
	if (extab_prel31 == EXIDX_CANTUNWIND) {
		/* Special case: cannot unwind (same as the "refuse to unwind" instruction) */
		_ARM_unwind_rt_emulator_init_inline_dbg_init(self)
		self->aure_instr_word  = __UINT32_C(0x80000000); /* 0b10000000 0b00000000 */
		self->aure_instr_wordc = 2;
		self->aure_instr_datac = 0;
	} else if ((extab_prel31 & __UINT32_C(0x80000000)) != 0) {
		/* Inlined instruction word (with up to 3 instructions) */
		ARM_unwind_rt_emulator_init_inline(self, extab_prel31);
	} else {
		/* prel31 pointer into ".ARM.extab" section */
		struct ARM_extab_entry const *extab_entry;
		extab_entry = (struct ARM_extab_entry const *)ARM_prel31_decode(&exidx_entry->aeie_extab_prel31);
		if ((extab_entry->aete_perso_prel31 & __UINT32_C(0x80000000)) == 0) {
			/* Special case: custom personality function */
			void *perso_addr = ARM_prel31_decode(&extab_entry->aete_perso_prel31);
			return (_Unwind_Personality_Fn)perso_addr;
		}
		ARM_unwind_rt_emulator_init_extab(self, extab_entry);
	}
	return __NULLPTR;
}



/* Check if the instruction decode of `self' has reached the end of input data. */
#define ARM_unwind_rt_emulator_instr_isdone(self) \
	(!(self)->aure_instr_wordc && !(self)->aure_instr_datac)

/* Read the next instruction unwind byte from `self'
 * !!! Causes undefined behavior when `ARM_unwind_rt_emulator_instr_isdone(self)' */
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __uint8_t
__NOTHROW(LIBUNWIND_CC ARM_unwind_rt_emulator_instr_readbyte)(struct ARM_unwind_rt_emulator *__restrict self) {
	__uint8_t result;
	if (self->aure_instr_wordc == 0) {
		__hybrid_assert(self->aure_instr_datac != 0);
		self->aure_instr_word = *self->aure_instr_data++;
		--self->aure_instr_datac;
		self->aure_instr_word = 4;
	}
	result = (self->aure_instr_word >> 24) & 0xff;
	self->aure_instr_word <<= 8;
	--self->aure_instr_wordc;
	return result;
}


__DECL_END
#endif /* __CC__ */

#endif /* !_ARM_KOS_LIBUNWIND_ARM_EXTAB_H */
