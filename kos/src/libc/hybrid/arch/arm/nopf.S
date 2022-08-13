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
#ifndef GUARD_LIBC_HYBRID_ARCH_ARM_NOPF_S
#define GUARD_LIBC_HYBRID_ARCH_ARM_NOPF_S 1
#define __ASSEMBLER__ 1

#include <hybrid/compiler.h>

#include <cfi.h>

.section .text.string.nopf
.cfi_startproc
INTERN_LABEL(libc_arm_nopf_begin):

/* Helper macros */
#define CLR_APSR_Z  msr APSR_nzcvq, #0
#define SET_APSR_Z  cmp r0, r0


/* NOPF Function implementations */
INTERN_FUNCTION(libc_arm_nopf_ldrb_r0_Br0B)
	CLR_APSR_Z          /* Force APSR.Z=0 */
	ldrb   r0, [r0]
	bx     lr
END(libc_arm_nopf_ldrb_r0_Br0B)

INTERN_FUNCTION(libc_arm_nopf_ldrh_r0_Br0B)
	CLR_APSR_Z          /* Force APSR.Z=0 */
	ldrh   r0, [r0]
	bx     lr
END(libc_arm_nopf_ldrh_r0_Br0B)

INTERN_FUNCTION(libc_arm_nopf_ldr_r0_Br0B)
	CLR_APSR_Z          /* Force APSR.Z=0 */
	ldr    r0, [r0]
	bx     lr
END(libc_arm_nopf_ldr_r0_Br0B)

INTERN_FUNCTION(libc_arm_nopf_ldrd_r0_r1_Br0B)
	CLR_APSR_Z          /* Force APSR.Z=0 */
	ldrd   r0, r1, [r0]
	bx     lr
END(libc_arm_nopf_ldrd_r0_r1_Br0B)



INTERN_FUNCTION(libc_arm_nopf_strb_r1_Br0B)
	CLR_APSR_Z          /* Force APSR.Z=0 */
	strb   r1, [r0]
	bx     lr
END(libc_arm_nopf_strb_r1_Br0B)

INTERN_FUNCTION(libc_arm_nopf_strh_r1_Br0B)
	CLR_APSR_Z          /* Force APSR.Z=0 */
	strh   r1, [r0]
	bx     lr
END(libc_arm_nopf_strh_r1_Br0B)

INTERN_FUNCTION(libc_arm_nopf_str_r1_Br0B)
	CLR_APSR_Z          /* Force APSR.Z=0 */
	str    r1, [r0]
	bx     lr
END(libc_arm_nopf_str_r1_Br0B)

INTERN_FUNCTION(libc_arm_nopf_strd_r1_r2_Br0B)
	CLR_APSR_Z          /* Force APSR.Z=0 */
	strd   r1, r2, [r0]
	bx     lr
END(libc_arm_nopf_strd_r1_r2_Br0B)



INTERN_FUNCTION(libc_arm_nopf_cmpxchb)
	CLR_APSR_Z          /* Force APSR.Z=0 */
1:	ldaexb r3, [r0]
	cmp    r3, r1
	bne    2f
	stlexb r12, r2, [r0]
	cmp    r12, #1      /* Check status (also sets APSR.Z=0 in case of no-branch) */
	bhs    1b           /* Repeat if STATUS >= 1 */
2:	bx     lr
END(libc_arm_nopf_cmpxchb)

INTERN_FUNCTION(libc_arm_nopf_cmpxchh)
	CLR_APSR_Z          /* Force APSR.Z=0 */
1:	ldaexh r3, [r0]
	cmp    r3, r1
	bne    2f
	stlexh r12, r2, [r0]
	cmp    r12, #1      /* Check status (also sets APSR.Z=0 in case of no-branch) */
	bhs    1b           /* Repeat if STATUS >= 1 */
2:	bx     lr
END(libc_arm_nopf_cmpxchh)

INTERN_FUNCTION(libc_arm_nopf_cmpxch)
	CLR_APSR_Z          /* Force APSR.Z=0 */
1:	ldaex  r3, [r0]
	cmp    r3, r1
	bne    2f
	stlex  r12, r2, [r0]
	cmp    r12, #1      /* Check status (also sets APSR.Z=0 in case of no-branch) */
	bhs    1b           /* Repeat if STATUS >= 1 */
2:	bx     lr
END(libc_arm_nopf_cmpxch)

INTERN_FUNCTION(libc_arm_nopf_cmpxchd)
	CLR_APSR_Z          /* Force APSR.Z=0 */
1:	ldaexd r4, r5, [r6]
	cmp    r5, r1
	cmpeq  r4, r0
	bne    2f
	stlexd r12, r2, r3, [r6]
	cmp    r12, #1      /* Check status (also sets APSR.Z=0 in case of no-branch) */
	bhs    1b           /* Repeat if STATUS >= 1 */
2:	bx     lr
END(libc_arm_nopf_cmpxchd)

INTERN_LABEL(libc_arm_nopf_end):



INTERN_FUNCTION(libc_arm_nopf_ret)
	SET_APSR_Z          /* Force APSR.Z=1 */
	bx     lr
END(libc_arm_nopf_ret)
.cfi_endproc



DEFINE_PUBLIC_ALIAS(arm_nopf_begin, libc_arm_nopf_begin);
DEFINE_PUBLIC_ALIAS(arm_nopf_end, libc_arm_nopf_end);
DEFINE_PUBLIC_ALIAS(arm_nopf_ret, libc_arm_nopf_ret);
DEFINE_PUBLIC_ALIAS(arm_nopf_ldrb_r0_Br0B, libc_arm_nopf_ldrb_r0_Br0B);
DEFINE_PUBLIC_ALIAS(arm_nopf_ldrh_r0_Br0B, libc_arm_nopf_ldrh_r0_Br0B);
DEFINE_PUBLIC_ALIAS(arm_nopf_ldr_r0_Br0B, libc_arm_nopf_ldr_r0_Br0B);
DEFINE_PUBLIC_ALIAS(arm_nopf_ldrd_r0_r1_Br0B, libc_arm_nopf_ldrd_r0_r1_Br0B);
DEFINE_PUBLIC_ALIAS(arm_nopf_strb_r1_Br0B, libc_arm_nopf_strb_r1_Br0B);
DEFINE_PUBLIC_ALIAS(arm_nopf_strh_r1_Br0B, libc_arm_nopf_strh_r1_Br0B);
DEFINE_PUBLIC_ALIAS(arm_nopf_str_r1_Br0B, libc_arm_nopf_str_r1_Br0B);
DEFINE_PUBLIC_ALIAS(arm_nopf_strd_r1_r2_Br0B, libc_arm_nopf_strd_r1_r2_Br0B);
DEFINE_PUBLIC_ALIAS(arm_nopf_cmpxchb, libc_arm_nopf_cmpxchb);
DEFINE_PUBLIC_ALIAS(arm_nopf_cmpxchh, libc_arm_nopf_cmpxchh);
DEFINE_PUBLIC_ALIAS(arm_nopf_cmpxch, libc_arm_nopf_cmpxch);
DEFINE_PUBLIC_ALIAS(arm_nopf_cmpxchd, libc_arm_nopf_cmpxchd);


#endif /* !GUARD_LIBC_HYBRID_ARCH_ARM_NOPF_S */
