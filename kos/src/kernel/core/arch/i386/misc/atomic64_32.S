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

#include <kernel/compiler.h>
#include <asm/cfi.h>

#define ST(name)                  \
	PUBLIC_FUNCTION(name##_r);    \
		nop; nop; nop; nop; nop;  \
	PUBLIC_FUNCTION(name)

#define EN(name) \
	END(name); END(name##_r)

/* CMPXCHG8B m64
 * Compare EDX:EAX with m64.
 * If equal, set ZF and load ECX:EBX into m64.
 * Else, clear ZF and load m64 into EDX:EAX. */

#define OVAL_LO  %eax
#define OVAL_HI  %edx
#define NVAL_LO  %ebx
#define NVAL_HI  %ecx


.section .text
ST(atomic64_read)
	.cfi_startproc
	/* u64 FCALL atomic64_read(struct atomic64 *self); */
	pushl_cfi_r %ebx
	pushl_cfi_r %esi
	movl   %ecx, %esi
	xorl   OVAL_LO, OVAL_LO
	xorl   OVAL_HI, OVAL_HI
	xorl   NVAL_LO, NVAL_LO
	xorl   NVAL_HI, NVAL_HI
	lock;  cmpxchg8b 0(%esi)
	popl_cfi_r %esi
	popl_cfi_r %ebx
	ret
	.cfi_endproc
EN(atomic64_read)



.section .text
ST(atomic64_cmpxch_val)
	.cfi_startproc
	/* u64 FCALL atomic64_cmpxch_val(struct atomic64 *self, u64 oldval, u64 newval); */
	pushl_cfi_r %ebx
	pushl_cfi_r %esi
	movl   %ecx, %esi
	movl   12(%esp), OVAL_LO
	movl   16(%esp), OVAL_HI
	movl   20(%esp), NVAL_LO
	movl   24(%esp), NVAL_HI
	lock;  cmpxchg8b 0(%esi)
	popl_cfi_r %esi
	popl_cfi_r %ebx
	ret    $(16)
	.cfi_endproc
EN(atomic64_cmpxch_val)



.section .text
ST(atomic64_cmpxch)
	.cfi_startproc
	/* bool FCALL atomic64_cmpxch(struct atomic64 *self, u64 oldval, u64 newval); */
	pushl_cfi_r %ebx
	pushl_cfi_r %esi
	movl   %ecx, %esi
	movl   12(%esp), OVAL_LO
	movl   16(%esp), OVAL_HI
	movl   20(%esp), NVAL_LO
	movl   24(%esp), NVAL_HI
	lock;  cmpxchg8b 0(%esi)
	popl_cfi_r %esi
	popl_cfi_r %ebx
	sete   %al
	movzbl %al, %eax
	ret    $(16)
	.cfi_endproc
EN(atomic64_cmpxch)



.section .text
ST(atomic64_xch)
	.cfi_startproc
	/* u64 FCALL atomic64_xch(struct atomic64 *self, u64 val); */
	pushl_cfi_r %ebx
	pushl_cfi_r %esi
	movl   %ecx, %esi
	movl   12(%esp), NVAL_LO
	movl   16(%esp), NVAL_HI
1:	lock;  cmpxchg8b 0(%esi)
	jne    1b
	popl_cfi_r %esi
	popl_cfi_r %ebx
	ret    $(8)
	.cfi_endproc
EN(atomic64_xch)



.section .text
ST(atomic64_write)
	.cfi_startproc
	/* void FCALL atomic64_write(struct atomic64 *self, u64 val); */
	pushl_cfi_r %ebx
	pushl_cfi_r %esi
	movl   %ecx, %esi
	movl   12(%esp), NVAL_LO
	movl   16(%esp), NVAL_HI
1:	lock;  cmpxchg8b 0(%esi)
	jne    1b
	popl_cfi_r %esi
	popl_cfi_r %ebx
	ret    $(8)
	.cfi_endproc
EN(atomic64_write)



.section .text
ST(atomic64_fetchadd)
	.cfi_startproc
	/* u64 FCALL atomic64_fetchadd(struct atomic64 *self, u64 value); */
	pushl_cfi_r %ebx
	pushl_cfi_r %esi
	movl   %ecx, %esi
1:	movl   OVAL_LO, NVAL_LO
	movl   OVAL_HI, NVAL_HI
	addl   12(%esp), NVAL_LO
	adcl   16(%esp), NVAL_HI
	lock;  cmpxchg8b 0(%esi)
	jne    1b
	popl_cfi_r %esi
	popl_cfi_r %ebx
	ret    $(8)
	.cfi_endproc
EN(atomic64_fetchadd)



.section .text
ST(atomic64_fetchand)
	.cfi_startproc
	/* u64 FCALL atomic64_fetchand(struct atomic64 *self, u64 value); */
	pushl_cfi_r %ebx
	pushl_cfi_r %esi
	movl   %ecx, %esi
1:	movl   OVAL_LO, NVAL_LO
	movl   OVAL_HI, NVAL_HI
	andl   12(%esp), NVAL_LO
	andl   16(%esp), NVAL_HI
	lock;  cmpxchg8b 0(%esi)
	jne    1b
	popl_cfi_r %esi
	popl_cfi_r %ebx
	ret    $(8)
	.cfi_endproc
EN(atomic64_fetchand)



.section .text
ST(atomic64_fetchor)
	.cfi_startproc
	/* u64 FCALL atomic64_fetchor(struct atomic64 *self, u64 value); */
	pushl_cfi_r %ebx
	pushl_cfi_r %esi
	movl   %ecx, %esi
1:	movl   OVAL_LO, NVAL_LO
	movl   OVAL_HI, NVAL_HI
	orl    12(%esp), NVAL_LO
	orl    16(%esp), NVAL_HI
	lock;  cmpxchg8b 0(%esi)
	jne    1b
	popl_cfi_r %esi
	popl_cfi_r %ebx
	ret    $(8)
	.cfi_endproc
EN(atomic64_fetchor)



.section .text
ST(atomic64_fetchxor)
	.cfi_startproc
	/* u64 FCALL atomic64_fetchxor(struct atomic64 *self, u64 value); */
	pushl_cfi_r %ebx
	pushl_cfi_r %esi
	movl   %ecx, %esi
1:	movl   OVAL_LO, NVAL_LO
	movl   OVAL_HI, NVAL_HI
	xorl   12(%esp), NVAL_LO
	xorl   16(%esp), NVAL_HI
	lock;  cmpxchg8b 0(%esi)
	jne    1b
	popl_cfi_r %esi
	popl_cfi_r %ebx
	ret    $(8)
	.cfi_endproc
EN(atomic64_fetchxor)



