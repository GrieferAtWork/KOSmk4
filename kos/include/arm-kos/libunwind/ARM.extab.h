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
#ifndef _ARM_KOS_LIBUNWIND_ARM_EXTAB_H
#define _ARM_KOS_LIBUNWIND_ARM_EXTAB_H 1

#include <libunwind/api.h>
/**/

#include <__crt.h>

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
	                               * 2: [(. & 0xf0000000) == 0x80000000] Compact run-time  support  personality  function
	                               *                                     Function is selected by `0xf000000' (bits 24-27)
	                               *                                     Remaining bytes are already part of data-area */
	/* Unwind data for personality function. A pointer to this data area
	 * is returned by `_Unwind_GetLanguageSpecificData(3E)' when  called
	 * from within a `_Unwind_Personality_Fn'
	 *
	 * For run-time support personality function, the format of this area,
	 * as well as any bytes in-lined in `aete_perso_prel31' is  documented
	 * in `10.3 Frame unwinding instructions' of `ehabi32.pdf'.
	 */
	__COMPILER_FLEXIBLE_ARRAY(__byte_t, aete_perso_data);
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


__DECL_END
#endif /* __CC__ */

#endif /* !_ARM_KOS_LIBUNWIND_ARM_EXTAB_H */
