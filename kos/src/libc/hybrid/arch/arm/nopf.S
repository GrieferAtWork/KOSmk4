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
#ifndef GUARD_LIBC_HYBRID_ARCH_ARM_NOPF_S
#define GUARD_LIBC_HYBRID_ARCH_ARM_NOPF_S 1
#define __WANT_ARM_ATOMIC_ASM_HELPERS
#define __ASSEMBLER__ 1

#include <hybrid/compiler.h>

#include <asm/arm.h>

#include <cfi.h>

#include "restart-block.h"

.section .text.string.nopf
.cfi_startproc
INTERN_LABEL(libc_arm_nopf_begin):

/* Helper macros */
#define CLR_APSR_Z  msr APSR_nzcvq, #0
#define SET_APSR_Z  cmp r0, r0


/* NOPF Function implementations */
INTERN_FUNCTION(libc_arm_nopf_ldrb_r0_Br0B)
	ldrb   r0, [r0]
	CLR_APSR_Z          /* Force APSR.Z=0 */
	bx     lr
END(libc_arm_nopf_ldrb_r0_Br0B)

INTERN_FUNCTION(libc_arm_nopf_ldrh_r0_Br0B)
	ldrh   r0, [r0]
	CLR_APSR_Z          /* Force APSR.Z=0 */
	bx     lr
END(libc_arm_nopf_ldrh_r0_Br0B)

INTERN_FUNCTION(libc_arm_nopf_ldr_r0_Br0B)
	ldr    r0, [r0]
	CLR_APSR_Z          /* Force APSR.Z=0 */
	bx     lr
END(libc_arm_nopf_ldr_r0_Br0B)

INTERN_FUNCTION(libc_arm_nopf_ldrd_r0_r1_Br0B)
	ldrd   r0, r1, [r0]
	CLR_APSR_Z          /* Force APSR.Z=0 */
	bx     lr
END(libc_arm_nopf_ldrd_r0_r1_Br0B)



INTERN_FUNCTION(libc_arm_nopf_strb_r0_Br1B)
	strb   r0, [r1]
	CLR_APSR_Z          /* Force APSR.Z=0 */
	bx     lr
END(libc_arm_nopf_strb_r0_Br1B)

INTERN_FUNCTION(libc_arm_nopf_strh_r0_Br1B)
	strh   r0, [r1]
	CLR_APSR_Z          /* Force APSR.Z=0 */
	bx     lr
END(libc_arm_nopf_strh_r0_Br1B)

INTERN_FUNCTION(libc_arm_nopf_str_r0_Br1B)
	str    r0, [r1]
	CLR_APSR_Z          /* Force APSR.Z=0 */
	bx     lr
END(libc_arm_nopf_str_r0_Br1B)

INTERN_FUNCTION(libc_arm_nopf_strd_r0_r1_Br2B)
	strd   r0, r1, [r2]
	CLR_APSR_Z          /* Force APSR.Z=0 */
	bx     lr
END(libc_arm_nopf_strd_r0_r1_Br2B)



/* Atomic operations */
#ifdef ldaexb_OR_ldrexb
INTERN_FUNCTION(libc_arm_nopf_cmpxchb)
	IF_NOT_ldaexb__dmb_ish
1:	ldaexb_OR_ldrexb r3, [r0]
	cmp    r3, r1
	bne    2f
	stlexb_OR_strexb r12, r2, [r0]
	cmp    r12, #1      /* Check status (also sets APSR.Z=0 in case of no-branch) */
	bhs    1b           /* Repeat if STATUS >= 1 */
	IF_NOT_ldaexb__dmb_ish
2:	bx     lr
END(libc_arm_nopf_cmpxchb)
#elif defined(__ARM_ATOMIC_8_USE_RESTART)
INTERN_FUNCTION(libc_arm_nopf_cmpxchb)
RESTART_BLOCK_BEGIN
	ldrb   r3, [r0]
	cmp    r3, r1
RESTART_BLOCK_END
	streqb r2, [r0]
	CLR_APSR_Z          /* Force APSR.Z=0 */
	bx     lr
END(libc_arm_nopf_cmpxchb)
#endif /* ... */

#ifdef ldaexh_OR_ldrexh
INTERN_FUNCTION(libc_arm_nopf_cmpxchh)
	IF_NOT_ldaexh__dmb_ish
1:	ldaexh_OR_ldrexh r3, [r0]
	cmp    r3, r1
	bne    2f
	stlexh_OR_strexh r12, r2, [r0]
	cmp    r12, #1      /* Check status (also sets APSR.Z=0 in case of no-branch) */
	bhs    1b           /* Repeat if STATUS >= 1 */
	IF_NOT_ldaexh__dmb_ish
2:	bx     lr
END(libc_arm_nopf_cmpxchh)
#elif defined(__ARM_ATOMIC_16_USE_RESTART)
INTERN_FUNCTION(libc_arm_nopf_cmpxchh)
RESTART_BLOCK_BEGIN
	ldrh   r3, [r0]
	cmp    r3, r1
RESTART_BLOCK_END
	streqh r2, [r0]
	CLR_APSR_Z          /* Force APSR.Z=0 */
	bx     lr
END(libc_arm_nopf_cmpxchh)
#endif /* ... */

#ifdef ldaex_OR_ldrex
INTERN_FUNCTION(libc_arm_nopf_cmpxch)
	IF_NOT_ldaex__dmb_ish
1:	ldaex_OR_ldrex r3, [r0]
	cmp    r3, r1
	bne    2f
	stlex_OR_strex r12, r2, [r0]
	cmp    r12, #1      /* Check status (also sets APSR.Z=0 in case of no-branch) */
	bhs    1b           /* Repeat if STATUS >= 1 */
	IF_NOT_ldaex__dmb_ish
2:	bx     lr
END(libc_arm_nopf_cmpxch)
#elif defined(__ARM_ATOMIC_32_USE_RESTART)
INTERN_FUNCTION(libc_arm_nopf_cmpxch)
RESTART_BLOCK_BEGIN
	ldr    r3, [r0]
	cmp    r3, r1
RESTART_BLOCK_END
	streq  r2, [r0]
	CLR_APSR_Z          /* Force APSR.Z=0 */
	bx     lr
END(libc_arm_nopf_cmpxch)
#endif /* ... */

#ifdef ldaexd_OR_ldrexd
INTERN_FUNCTION(libc_arm_nopf_cmpxchd)
	IF_NOT_ldaexd__dmb_ish
1:	ldaexd_OR_ldrexd r4, r5, [r6]
	cmp    r5, r1
	cmpeq  r4, r0
	bne    2f
	stlexd_OR_strexd r12, r2, r3, [r6]
	cmp    r12, #1      /* Check status (also sets APSR.Z=0 in case of no-branch) */
	bhs    1b           /* Repeat if STATUS >= 1 */
	IF_NOT_ldaexd__dmb_ish
2:	bx     lr
END(libc_arm_nopf_cmpxchd)
#elif defined(__ARM_ATOMIC_64_USE_RESTART)
INTERN_FUNCTION(libc_arm_nopf_cmpxchd)
	CLR_APSR_Z          /* Force APSR.Z=0 */
RESTART_BLOCK_BEGIN
	ldmia  r6, {r4, r5}
	cmp    r5, r1
	cmpeq  r4, r0
RESTART_BLOCK_END
	stmiaeq r6, {r2, r3}
	CLR_APSR_Z          /* Force APSR.Z=0 */
	bx     lr
END(libc_arm_nopf_cmpxchd)
#endif /* ... */

INTERN_LABEL(libc_arm_nopf_end):



INTERN_FUNCTION(libc_arm_nopf_ret)
	SET_APSR_Z          /* Force APSR.Z=1 */
	bx     lr
END(libc_arm_nopf_ret)



/* Implement alignment wrapers */
#ifdef __ARM_ATOMIC_8_ALIGN_TO_32
/* @in  uint8_t *r0_addr
 * @in  uint8_t  r1_oldval
 * @in  uint8_t  r2_newval
 * @out uint8_t  r3_real_oldval
 *
 * >> r4_saved_oldval = r1_oldval;
 * >> r5_saved_newval = r2_newval;
 * >> switch (r0_addr & 3) {
 * >> case N:
 * >> again_caseN:
 * >>     r12_addr       = r0_addr;
 * >>     r0_addr        = r0_addr - N;
 * >>     r0_oldval32    = libc_arm_nopf_ldr_r0_Br0B(r0_addr);
 * >>     r3_real_oldval = (r0_oldval32 >> (N * 8)) & 0xff;
 * >>     if (r3_real_oldval != r4_saved_oldval) {
 * >>         r0_addr = r12_addr;
 * >>         break;
 * >>     }
 * >>     r1_oldval       = r0_oldval32 & ~(0x000000ff << (N * 8));
 * >>     r2_newval       = r1_oldval | (r5_saved_newval << (N * 8));
 * >>     r1_oldval       = r1_oldval | (r4_saved_oldval << (N * 8));
 * >>     r0_addr         = r12_addr;
 * >>     r3_real_oldval  = libc_arm_nopf_cmpxch(r0_addr, r1_oldval, r2_newval);
 * >>     if (APSR.Z) {
 * >>         r1_oldval = r4_saved_oldval;
 * >>         r2_newval = r5_saved_newval;
 * >>         return;
 * >>     }
 * >>     if (r3_real_oldval != r1_oldval) {
 * >>         goto again_caseN;
 * >>     }
 * >>     r3_real_oldval = (r3_real_oldval >> (N * 8)) & 0xff;
 * >>     break;
 * >> }
 * >> r1_oldval = r4_saved_oldval;
 * >> r2_newval = r5_saved_newval;
 * >> SET_APSR_Z;
 * >> return;
 */
INTERN_FUNCTION(libc_arm_nopf_cmpxchb)
	.cfi_remember_state
	push_cfi_r {r4, r5, lr}
	b      . /* TODO */
	pop    {r4, r5, pc}
	.cfi_restore_state
END(libc_arm_nopf_cmpxchb)
#endif /* __ARM_ATOMIC_8_ALIGN_TO_32 */

#ifdef __ARM_ATOMIC_16_ALIGN_TO_32
/* @in  uint16_t *r0_addr
 * @in  uint16_t  r1_oldval
 * @in  uint16_t  r2_newval
 * @out uint16_t  r3_real_oldval
 *
 * >> r4_saved_oldval = r1_oldval;
 * >> r5_saved_newval = r2_newval;
 * >> switch (r0_addr & 2) {
 * >> case N:
 * >> again_caseN:
 * >>     r12_addr       = r0_addr;
 * >>     r0_addr        = r0_addr - N;
 * >>     r0_oldval32    = libc_arm_nopf_ldr_r0_Br0B(r0_addr);
 * >>     r3_real_oldval = (r0_oldval32 >> (N * 8)) & 0xffff;
 * >>     if (r3_real_oldval != r4_saved_oldval) {
 * >>         r0_addr = r12_addr;
 * >>         break;
 * >>     }
 * >>     r1_oldval       = r0_oldval32 & ~(0x0000ffff << (N * 8));
 * >>     r2_newval       = r1_oldval | (r5_saved_newval << (N * 8));
 * >>     r1_oldval       = r1_oldval | (r4_saved_oldval << (N * 8));
 * >>     r0_addr         = r12_addr;
 * >>     r3_real_oldval  = libc_arm_nopf_cmpxch(r0_addr, r1_oldval, r2_newval);
 * >>     if (APSR.Z) {
 * >>         r1_oldval = r4_saved_oldval;
 * >>         r2_newval = r5_saved_newval;
 * >>         return;
 * >>     }
 * >>     if (r3_real_oldval != r1_oldval) {
 * >>         goto again_caseN;
 * >>     }
 * >>     r3_real_oldval = (r3_real_oldval >> (N * 8)) & 0xffff;
 * >>     break;
 * >> }
 * >> r1_oldval = r4_saved_oldval;
 * >> r2_newval = r5_saved_newval;
 * >> SET_APSR_Z;
 * >> return;
 */
INTERN_FUNCTION(libc_arm_nopf_cmpxchh)
	/*.cfi_remember_state*/
	push_cfi_r {r0, r1, r2, lr}
	b      . /* TODO */
	bl     libc_arm_nopf_cmpxch
	pop    {r0, r1, r2, pc}
	/*.cfi_restore_state*/
END(libc_arm_nopf_cmpxchh)
#endif /* __ARM_ATOMIC_16_ALIGN_TO_32 */


.cfi_endproc



DEFINE_PUBLIC_ALIAS(arm_nopf_begin, libc_arm_nopf_begin);
DEFINE_PUBLIC_ALIAS(arm_nopf_end, libc_arm_nopf_end);
DEFINE_PUBLIC_ALIAS(arm_nopf_ret, libc_arm_nopf_ret);
DEFINE_PUBLIC_ALIAS(arm_nopf_ldrb_r0_Br0B, libc_arm_nopf_ldrb_r0_Br0B);
DEFINE_PUBLIC_ALIAS(arm_nopf_ldrh_r0_Br0B, libc_arm_nopf_ldrh_r0_Br0B);
DEFINE_PUBLIC_ALIAS(arm_nopf_ldr_r0_Br0B, libc_arm_nopf_ldr_r0_Br0B);
DEFINE_PUBLIC_ALIAS(arm_nopf_ldrd_r0_r1_Br0B, libc_arm_nopf_ldrd_r0_r1_Br0B);
DEFINE_PUBLIC_ALIAS(arm_nopf_strb_r0_Br1B, libc_arm_nopf_strb_r0_Br1B);
DEFINE_PUBLIC_ALIAS(arm_nopf_strh_r0_Br1B, libc_arm_nopf_strh_r0_Br1B);
DEFINE_PUBLIC_ALIAS(arm_nopf_str_r0_Br1B, libc_arm_nopf_str_r0_Br1B);
DEFINE_PUBLIC_ALIAS(arm_nopf_strd_r0_r1_Br2B, libc_arm_nopf_strd_r0_r1_Br2B);
DEFINE_PUBLIC_ALIAS(arm_nopf_cmpxchb, libc_arm_nopf_cmpxchb);
DEFINE_PUBLIC_ALIAS(arm_nopf_cmpxchh, libc_arm_nopf_cmpxchh);
DEFINE_PUBLIC_ALIAS(arm_nopf_cmpxch, libc_arm_nopf_cmpxch);
DEFINE_PUBLIC_ALIAS(arm_nopf_cmpxchd, libc_arm_nopf_cmpxchd);


#endif /* !GUARD_LIBC_HYBRID_ARCH_ARM_NOPF_S */
