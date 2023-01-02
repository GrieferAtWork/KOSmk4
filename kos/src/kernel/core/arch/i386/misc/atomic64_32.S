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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MISC_ATOMIC64_32_S
#define GUARD_KERNEL_CORE_ARCH_I386_MISC_ATOMIC64_32_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>

#include <sched/cpu.h>

#include <asm/cacheline.h>
#include <cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/ttest.h>

/* i386-specific atomic64 ABI fallback implementation. */


#ifdef CONFIG_NO_SMP
#define LOCK()    \
	pushfl_cfi_r; \
	cli;
#define UNLOCK() \
	popfl_cfi_r
#define LOCK_NOPR() \
	/* nothing */
#define UNLOCK_NOPR() \
	/* nothing */
#else /* CONFIG_NO_SMP */

.section .bss
/* The lock object used to guard against SMP races */
	.align __ARCH_CACHELINESIZE
PRIVATE_OBJECT(atomic64_lock)
	/* Make sure that this object's doesn't share its cacheline with anything else! */
	.int 0
	.align __ARCH_CACHELINESIZE
END(atomic64_lock)

.section .text.cold
PRIVATE_FUNCTION(atomic64_waitfor)
	.cfi_startproc
	ttest  mask=EFLAGS_IF, loc=4(%esp)
	jz     1f
	pushl_cfi_r %eax
	EXTERN(task_yield)
	call   task_yield
	popl_cfi_r %eax
	ret
1:	pause
	ret
	.cfi_endproc
END(atomic64_waitfor)

#define LOCK(gp_clobberl)                    \
	pushfl_cfi_r;                            \
	cli;                                     \
991:movl   $(1), gp_clobberl;                \
	lock   xchgl gp_clobberl, atomic64_lock; \
	testl  gp_clobberl, gp_clobberl;         \
	jnz    992f;                             \
	.pushsection .text.cold;                 \
992:	pushl $(991b);                       \
		jmp   atomic64_waitfor;              \
	.popsection
#define LOCK_NOPR()                   \
	pushl_cfi_r %eax;                 \
991:movl   $(1), %eax;                \
	lock   xchgl %eax, atomic64_lock; \
	testl  %eax, %eax;                \
	jnz    992f;                      \
	.pushsection .text.cold;          \
992:	pause;                        \
		jmp   991b;                   \
	.popsection;                      \
	popl_cfi_r %eax
#define UNLOCK_NOPR() \
	movl $(0), atomic64_lock;
#define UNLOCK()              \
	movl $(0), atomic64_lock; \
	popfl_cfi_r
#endif /* !CONFIG_NO_SMP */

.section .text
.cfi_startproc

/* Atomically read a 64-bit data word from `self' */
PUBLIC_FUNCTION(__i386_atomic64_read)
	/* >> __i386_atomic64_read
	 * IN:      %edi = (atomic64_t *)self
	 * OUT:     %eax = (u32)(RETURN & 0xffffffff)
	 *          %edx = (u32)(RETURN & 0xffffffff00000000) >> 32
	 * CLOBBER: %eflags, %ebx, %ecx */
	LOCK(%eax)
	movl   0(%edi), %eax
	movl   4(%edi), %edx
	UNLOCK()
	ret
END(__i386_atomic64_read)

/* Atomically write a 64-bit data word to `self' */
PUBLIC_FUNCTION(__i386_atomic64_write)
	/* >> __i386_atomic64_write
	 * IN:      %edi = (atomic64_t *)self
	 *          %ebx = (u32)(value & 0xffffffff)
	 *          %ecx = (u32)(value & 0xffffffff00000000) >> 32
	 * OUT:     -
	 * CLOBBER: %eflags, %eax, %edx */
	LOCK(%eax)
	movl   %ebx, 0(%edi)
	movl   %ecx, 4(%edi)
	UNLOCK()
	ret
END(__i386_atomic64_write)

/* Atomically compare-exchange a 64-bit data word from `self' */
PUBLIC_FUNCTION(__i386_atomic64_cmpxch)
	/* >> __i386_atomic64_cmpxch
	 * IN:      %edi = (atomic64_t *)self
	 *          %eax = (u32)(oldval & 0x00000000ffffffff)
	 *          %edx = (u32)(oldval & 0xffffffff00000000) >> 32
	 *          %ebx = (u32)(newval & 0x00000000ffffffff)
	 *          %ecx = (u32)(newval & 0xffffffff00000000) >> 32
	 * OUT:     %eax = (u32)(REAL_OLD_VALUE & 0x00000000ffffffff)
	 *          %edx = (u32)(REAL_OLD_VALUE & 0xffffffff00000000) >> 32
	 *          %eflags.ZF = (REAL_OLD_VALUE == oldval) ? 1 : 0
	 * CLOBBER: %eflags\ZF */
	pushfl_cfi
	ttest  mask=EFLAGS_IF, loc=0(%esp)
	.cfi_remember_state
	jz     .Lcmpxch_nopf
	popfl_cfi
	cli
	LOCK_NOPR()
	cmpl   %eax, 0(%edi)
	jne    .Lcmpxch_ne
	cmpl   %edx, 4(%edi)
	jne    .Lcmpxch_ne
	movl   %ebx, 0(%edi)
	movl   %ecx, 4(%edi)
	jmp    .Lcmpxch_done
.Lcmpxch_ne:
	movl   0(%edi), %eax
	movl   4(%edi), %edx
.Lcmpxch_done:
	sti
	ret

.Lcmpxch_nopf:
	.cfi_restore_state
	popfl_cfi
	LOCK_NOPR()
	cmpl   %eax, 0(%edi)
	jne    .Lcmpxch_ne_nopf
	cmpl   %edx, 4(%edi)
	jne    .Lcmpxch_ne_nopf
	movl   %ebx, 0(%edi)
	movl   %ecx, 4(%edi)
	jmp    .Lcmpxch_done_nopf
.Lcmpxch_ne_nopf:
	movl   0(%edi), %eax
	movl   4(%edi), %edx
.Lcmpxch_done_nopf:
	UNLOCK_NOPR()
	ret
END(__i386_atomic64_cmpxch)

/* Atomically exchange a 64-bit data word from `self' */
PUBLIC_FUNCTION(__i386_atomic64_xch)
	/* >> __i386_atomic64_xch
	 * IN:      %edi = (atomic64_t *)self
	 *          %ebx = (u32)(value & 0xffffffff)
	 *          %ecx = (u32)(value & 0xffffffff00000000) >> 32
	 * OUT:     %eax = (u32)(oldval & 0x00000000ffffffff)
	 *          %edx = (u32)(oldval & 0xffffffff00000000) >> 32
	 * CLOBBER: %eflags */
	LOCK(%eax)
	movl   0(%edi), %eax
	movl   4(%edi), %edx
	movl   %ebx, 0(%edi)
	movl   %ecx, 4(%edi)
	UNLOCK()
	ret
END(__i386_atomic64_xch)

/* Atomically fetch-and-add a 64-bit data word from `self' */
PUBLIC_FUNCTION(__i386_atomic64_fetchadd)
	/* >> __i386_atomic64_fetchadd
	 * IN:      %edi = (atomic64_t *)self
	 *          %ebx = (u32)(addend & 0xffffffff)
	 *          %ecx = (u32)(addend & 0xffffffff00000000) >> 32
	 * OUT:     %eax = (u32)(oldval & 0x00000000ffffffff)
	 *          %edx = (u32)(oldval & 0xffffffff00000000) >> 32
	 * CLOBBER: %eflags, %ebx, %ecx */
	LOCK(%eax)
	/* %eax:%edx = oldval */
	movl   0(%edi), %eax
	movl   4(%edi), %edx
	/* %ebx:%ecx += oldval */
	addl   %eax, %ebx
	adcl   %edx, %ecx
	/* value = %ebx:%ecx */
	movl   %ebx, 0(%edi)
	movl   %ecx, 4(%edi)
	UNLOCK()
	ret
END(__i386_atomic64_fetchadd)

/* Atomically fetch-and-and a 64-bit data word from `self' */
PUBLIC_FUNCTION(__i386_atomic64_fetchand)
	/* >> __i386_atomic64_fetchand
	 * IN:      %edi = (atomic64_t *)self
	 *          %ebx = (u32)(addend & 0xffffffff)
	 *          %ecx = (u32)(addend & 0xffffffff00000000) >> 32
	 * OUT:     %eax = (u32)(oldval & 0x00000000ffffffff)
	 *          %edx = (u32)(oldval & 0xffffffff00000000) >> 32
	 * CLOBBER: %eflags, %ebx, %ecx */
	LOCK(%eax)
	/* %eax:%edx = oldval */
	movl   0(%edi), %eax
	movl   4(%edi), %edx
	/* %ebx:%ecx &= oldval */
	andl   %eax, %ebx
	andl   %edx, %ecx
	/* value = %ebx:%ecx */
	movl   %ebx, 0(%edi)
	movl   %ecx, 4(%edi)
	UNLOCK()
	ret
END(__i386_atomic64_fetchand)

/* Atomically fetch-and-or a 64-bit data word from `self' */
PUBLIC_FUNCTION(__i386_atomic64_fetchor)
	/* >> __i386_atomic64_fetchor
	 * IN:      %edi = (atomic64_t *)self
	 *          %ebx = (u32)(addend & 0xffffffff)
	 *          %ecx = (u32)(addend & 0xffffffff00000000) >> 32
	 * OUT:     %eax = (u32)(oldval & 0x00000000ffffffff)
	 *          %edx = (u32)(oldval & 0xffffffff00000000) >> 32
	 * CLOBBER: %eflags, %ebx, %ecx */
	LOCK(%eax)
	/* %eax:%edx = oldval */
	movl   0(%edi), %eax
	movl   4(%edi), %edx
	/* %ebx:%ecx |= oldval */
	orl    %eax, %ebx
	orl    %edx, %ecx
	/* value = %ebx:%ecx */
	movl   %ebx, 0(%edi)
	movl   %ecx, 4(%edi)
	UNLOCK()
	ret
END(__i386_atomic64_fetchor)

/* Atomically fetch-and-xor a 64-bit data word from `self' */
PUBLIC_FUNCTION(__i386_atomic64_fetchxor)
	/* >> __i386_atomic64_fetchxor
	 * IN:      %edi = (atomic64_t *)self
	 *          %ebx = (u32)(addend & 0xffffffff)
	 *          %ecx = (u32)(addend & 0xffffffff00000000) >> 32
	 * OUT:     %eax = (u32)(oldval & 0x00000000ffffffff)
	 *          %edx = (u32)(oldval & 0xffffffff00000000) >> 32
	 * CLOBBER: %eflags, %ebx, %ecx */
	LOCK(%eax)
	/* %eax:%edx = oldval */
	movl   0(%edi), %eax
	movl   4(%edi), %edx
	/* %ebx:%ecx ^= oldval */
	xorl   %eax, %ebx
	xorl   %edx, %ecx
	/* value = %ebx:%ecx */
	movl   %ebx, 0(%edi)
	movl   %ecx, 4(%edi)
	UNLOCK()
	ret
END(__i386_atomic64_fetchxor)

.cfi_endproc


.section .text.cold
/* Because gcc  refuses  to  properly compile  the  inline-assembly  wrappers
 * when not building with __OPTIMIZE__, we need to provide a C-ABI compatible
 * wrapper. (ugh...) */
.cfi_startproc
/* Atomically compare-exchange a 64-bit data word from `self' */
PUBLIC_FUNCTION(atomic64_cmpxch_val)
	/* >> __i386_atomic64_cmpxch
	 * ```
	 * IN:       4(%esp) = self
	 *           8(%esp) = (oldval & 0x00000000ffffffff)
	 *          12(%esp) = (oldval & 0xffffffff00000000) >> 32
	 *          16(%esp) = (newval & 0x00000000ffffffff)
	 *          20(%esp) = (newval & 0xffffffff00000000) >> 32
	 * OUT:     %eax = (u32)(REAL_OLD_VALUE & 0x00000000ffffffff)
	 *          %edx = (u32)(REAL_OLD_VALUE & 0xffffffff00000000) >> 32
	 *          %eflags.ZF = (REAL_OLD_VALUE == oldval) ? 1 : 0
	 * CLOBBER: %ecx, %eflags\ZF
	 * ``` */
	pushl_cfi_r %edi
	pushl_cfi_r %ebx
	movl   (8 +  4)(%esp), %edi /* (atomic64_t *)self */
	movl   (8 +  8)(%esp), %eax /* (oldval & 0x00000000ffffffff) */
	movl   (8 + 12)(%esp), %edx /* (oldval & 0xffffffff00000000) >> 32 */
	movl   (8 + 16)(%esp), %ebx /* (newval & 0x00000000ffffffff) */
	movl   (8 + 20)(%esp), %ecx /* (newval & 0xffffffff00000000) >> 32 */
	EXTERN(__i386_atomic64_cmpxch)
	call   __i386_atomic64_cmpxch
	popl_cfi_r %ebx
	popl_cfi_r %edi
	ret    $(20)
END(atomic64_cmpxch_val)
.cfi_endproc



#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MISC_ATOMIC64_32_S */
