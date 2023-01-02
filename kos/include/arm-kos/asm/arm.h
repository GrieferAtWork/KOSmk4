/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ARM_KOS_ASM_ARM_H
#define _ARM_KOS_ASM_ARM_H 1

#include <__stdinc.h>

#include <hybrid/__asm.h>

/************************************************************************/
/* ARM UNIFIED ASSEMBLY CONFIGURATION HEADERS                           */
/************************************************************************/
/* This header should be included by all ARM assembly source files, as it
 * provides various helper macros, and configure the assembler to  output
 * bytecode for the intended target. */



/* Fill in missing compiler macros */
#ifndef __ARM_ARCH
#define __ARM_ARCH 6
#endif /* !__ARM_ARCH */

#ifdef __ARM_ARCH_6K__
#define __ARM_ARCH_NAME armv6k
#else /* __ARM_ARCH_6K__ */
#define __ARM_ARCH_NAME __PP_CAT2(armv,__ARM_ARCH)
#endif /* !__ARM_ARCH_6K__ */


/* Bitset of supported ldrex operand sizes. */
#ifndef __ARM_FEATURE_LDREX
#if __ARM_ARCH >= 7 || (__ARM_ARCH >= 6 && defined(__ARM_ARCH_6K__))
#define __ARM_FEATURE_LDREX 0xf
#elif __ARM_ARCH >= 6
#define __ARM_FEATURE_LDREX 0x4
#endif /* ... */
#endif /* !__ARM_FEATURE_LDREX */


/* Required stack alignment */
#define __ARM_STACK_ALIGNMENT 8

/* Return the number of required alignment bytes after `num_pushed_bytes' */
#define __ARM_STACK_ALIGN_OFFSET(num_pushed_bytes) \
	((__ARM_STACK_ALIGNMENT - ((num_pushed_bytes) % __ARM_STACK_ALIGNMENT)) % __ARM_STACK_ALIGNMENT)

/* Helper macro to force canonical stack alignment after `num_pushed_bytes'. */
#define __ARM_STACK_ALIGN_AFTER(num_pushed_bytes)                                                                                   \
	__ASM_L(.if ((num_pushed_bytes) % __ARM_STACK_ALIGNMENT) != 0)                                                                  \
	__ASM_L(	sub sp, sp, __PRIVATE_ARM_STACK_ALIGN_POUND (__ARM_STACK_ALIGNMENT - ((num_pushed_bytes) % __ARM_STACK_ALIGNMENT))) \
	__ASM_L(	.cfi_adjust_cfa_offset (__ARM_STACK_ALIGNMENT - ((num_pushed_bytes) % __ARM_STACK_ALIGNMENT)))                      \
	__ASM_L(.endif)
#define __ARM_STACK_UNALIGN_AFTER(num_pushed_bytes)                                                                                 \
	__ASM_L(.if ((num_pushed_bytes) % __ARM_STACK_ALIGNMENT) != 0)                                                                  \
	__ASM_L(	add sp, sp, __PRIVATE_ARM_STACK_ALIGN_POUND (__ARM_STACK_ALIGNMENT - ((num_pushed_bytes) % __ARM_STACK_ALIGNMENT))) \
	__ASM_L(	.cfi_adjust_cfa_offset -(__ARM_STACK_ALIGNMENT - ((num_pushed_bytes) % __ARM_STACK_ALIGNMENT)))                     \
	__ASM_L(.endif)
#define __ARM_STACK_GET_BEFORE_ALIGN(dst_reg, num_pushed_bytes)                                                                          \
	__ASM_L(.if ((num_pushed_bytes) % __ARM_STACK_ALIGNMENT) != 0)                                                                       \
	__ASM_L(	add dst_reg, sp, __PRIVATE_ARM_STACK_ALIGN_POUND (__ARM_STACK_ALIGNMENT - ((num_pushed_bytes) % __ARM_STACK_ALIGNMENT))) \
	__ASM_L(.else)                                                                                                                       \
	__ASM_L(	mov dst_reg, sp)                                                                                                         \
	__ASM_L(.endif)
#define __PRIVATE_ARM_STACK_ALIGN_POUND #


#ifdef __ASSEMBLER__

/* Stack alignment helpers. */
#define STACK_ALIGNMENT            __ARM_STACK_ALIGNMENT
#define STACK_ALIGN_OFFSET         __ARM_STACK_ALIGN_OFFSET
#define ASM_STACK_ALIGN_AFTER      __ARM_STACK_ALIGN_AFTER
#define ASM_STACK_UNALIGN_AFTER    __ARM_STACK_UNALIGN_AFTER
#define ASM_STACK_GET_BEFORE_ALIGN __ARM_STACK_GET_BEFORE_ALIGN

#ifndef __INTELLISENSE__
.arch __ARM_ARCH_NAME
.syntax unified
.arm
#endif /* !__INTELLISENSE__ */
#endif /* __ASSEMBLER__ */

#ifndef __COMPILER_NO_GCC_ASM_MACROS
__ASM_BEGIN

/* If possible, emulate instructions added by later ARM revisions. */
#if __ARM_ARCH < 7
__ASM_L(.macro dmb mode:req)
__ASM_L(	mcr    p15, 0, r0, c7, c10, 5) /* dmb    ish */
__ASM_L(.endm)
#endif /* __ARM_ARCH < 7 */

/* Helper for always generating the correct code sequence to load a 32-bit constant `value' into a register `reg' */
__ASM_L(.macro ldreg reg:req, value:req)
__ASM_L(.if __ASM_ARG(\value) >= 0 && __ASM_ARG(\value) < 65535)
__ASM_L(	mov    __ASM_ARG(\reg), #__ASM_ARG(\value))
__ASM_L(.else)
__ASM_L(	ldr    __ASM_ARG(\reg), =__ASM_ARG(\value))
__ASM_L(.endif)
__ASM_L(.endm)

__ASM_END
#endif /* !__COMPILER_NO_GCC_ASM_MACROS */




/************************************************************************/
/* HELPERS                                                              */
/************************************************************************/

#ifdef __WANT_ARM_ATOMIC_ASM_HELPERS
/* Define helper macros to describe how to implement atomic operations.
 * (s.a. `/kos/include/arm-kos/README.md')
 *
 * 8-bit:
 *    - __ARM_ATOMIC_8_USE_LDAEXB
 *    - __ARM_ATOMIC_8_USE_LDREXB
 *    - __ARM_ATOMIC_8_ALIGN_TO_32
 *    - __ARM_ATOMIC_8_USE_RESTART
 *
 * 16-bit:
 *    - __ARM_ATOMIC_16_USE_LDAEXH
 *    - __ARM_ATOMIC_16_USE_LDREXH
 *    - __ARM_ATOMIC_16_ALIGN_TO_32
 *    - __ARM_ATOMIC_16_USE_RESTART
 *
 * 32-bit:
 *    - __ARM_ATOMIC_32_USE_LDAEX
 *    - __ARM_ATOMIC_32_USE_LDREX
 *    - __ARM_ATOMIC_32_USE_RESTART
 *
 * 64-bit:
 *    - __ARM_ATOMIC_64_USE_LDAEXD
 *    - __ARM_ATOMIC_64_USE_LDREXD
 *    - __ARM_ATOMIC_64_USE_RESTART
 */
#if __ARM_ARCH >= 8
#define __ARM_ATOMIC_8_USE_LDAEXB   /* ldaexb */
#define __ARM_ATOMIC_16_USE_LDAEXH  /* ldaexh */
#define __ARM_ATOMIC_32_USE_LDAEX   /* ldaex */
#define __ARM_ATOMIC_64_USE_LDAEXD  /* ldaexd */
#elif (__ARM_FEATURE_LDREX & 0xf) == 0xf
#define __ARM_ATOMIC_8_USE_LDREXB   /* ldrexb */
#define __ARM_ATOMIC_16_USE_LDREXH  /* ldrexh */
#define __ARM_ATOMIC_32_USE_LDREX   /* ldrex */
#define __ARM_ATOMIC_64_USE_LDREXD  /* ldrexd */
#elif (__ARM_FEATURE_LDREX & 4)
#define __ARM_ATOMIC_8_ALIGN_TO_32  /* align to 32-bit */
#define __ARM_ATOMIC_16_ALIGN_TO_32 /* align to 32-bit */
#define __ARM_ATOMIC_32_USE_LDREX   /* ldrex */
#define __ARM_ATOMIC_64_USE_RESTART /* Use interrupt restart trick */
#else /* ... */
#define __ARM_ATOMIC_8_USE_RESTART  /* Use interrupt restart trick */
#define __ARM_ATOMIC_16_USE_RESTART /* Use interrupt restart trick */
#define __ARM_ATOMIC_32_USE_RESTART /* Use interrupt restart trick */
#define __ARM_ATOMIC_64_USE_RESTART /* Use interrupt restart trick */
#endif /* !... */

#ifdef __ARM_ATOMIC_8_USE_LDAEXB
#define ldaexb_OR_ldrexb       ldaexb
#define stlexb_OR_strexb       stlexb
#define IF_NOT_ldaexb__dmb_ish /* nothing */
#elif defined(__ARM_ATOMIC_8_USE_LDREXB)
#define ldaexb_OR_ldrexb       ldrexb
#define stlexb_OR_strexb       strexb
#define IF_NOT_ldaexb__dmb_ish dmb ish
#endif /* ... */
#ifdef __ARM_ATOMIC_16_USE_LDAEXH
#define ldaexh_OR_ldrexh       ldaexh
#define stlexh_OR_strexh       stlexh
#define IF_NOT_ldaexh__dmb_ish /* nothing */
#elif defined(__ARM_ATOMIC_16_USE_LDREXH)
#define ldaexh_OR_ldrexh       ldrexh
#define stlexh_OR_strexh       strexh
#define IF_NOT_ldaexh__dmb_ish dmb ish
#endif /* ... */
#ifdef __ARM_ATOMIC_32_USE_LDAEX
#define ldaex_OR_ldrex        ldaex
#define stlex_OR_strex        stlex
#define IF_NOT_ldaex__dmb_ish /* nothing */
#elif defined(__ARM_ATOMIC_32_USE_LDREX)
#define ldaex_OR_ldrex        ldrex
#define stlex_OR_strex        strex
#define IF_NOT_ldaex__dmb_ish dmb ish
#endif /* !__ARM_ATOMIC_32_USE_LDAEXB */
#ifdef __ARM_ATOMIC_64_USE_LDAEXD
#define ldaexd_OR_ldrexd       ldaexd
#define stlexd_OR_strexd       stlexd
#define IF_NOT_ldaexd__dmb_ish /* nothing */
#elif defined(__ARM_ATOMIC_64_USE_LDREXD)
#define ldaexd_OR_ldrexd       ldrexd
#define stlexd_OR_strexd       strexd
#define IF_NOT_ldaexd__dmb_ish dmb ish
#endif /* ... */
#endif /* __WANT_ARM_ATOMIC_ASM_HELPERS */


#endif /* !_ARM_KOS_ASM_ARM_H */
