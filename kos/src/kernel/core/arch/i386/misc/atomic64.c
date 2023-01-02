/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif([](x) -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MISC_ATOMIC64_C
#define GUARD_KERNEL_CORE_ARCH_I386_MISC_ATOMIC64_C 1
#define DISABLE_BRANCH_PROFILING /* Don't profile this file */
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <hybrid/host.h>

#ifndef __x86_64__
#include <kernel/boot.h>
#include <kernel/types.h>
#include <kernel/x86/cpuid.h>
#include <sched/atomic64.h>

#include <asm/cpu-cpuid.h>
#include <asm/intrin.h>

#include <assert.h>
#include <inttypes.h>
#include <string.h>

DECL_BEGIN

extern byte_t __i386_atomic64_read[];
extern byte_t __i386_atomic64_write[];
extern byte_t __i386_atomic64_cmpxch[];
extern byte_t __i386_atomic64_xch[];
extern byte_t __i386_atomic64_fetchadd[];
extern byte_t __i386_atomic64_fetchand[];
extern byte_t __i386_atomic64_fetchor[];
extern byte_t __i386_atomic64_fetchxor[];


/* i386-specific atomic64 ABI cmpxchg8b-specific implementation. */
PRIVATE ATTR_FREERODATA byte_t const __i386_cmpxchg8b_read[] = {
	0x89, 0xc3,             /*     movl   %eax, %ebx         */
	0x89, 0xd1,             /*     movl   %edx, %ecx         */
	0xf0, 0x0f, 0xc7, 0x0f, /*     lock   cmpxchg8b (%edi)   */
	0xc3,                   /*     ret                       */
};

PRIVATE ATTR_FREERODATA byte_t const __i386_cmpxchg8b_cmpxch[] = {
	0xf0, 0x0f, 0xc7, 0x0f, /*     lock   cmpxchg8b (%edi)   */
	0xc3,                   /*     ret                       */
};

/* also used for `__i386_atomic64_write' */
PRIVATE ATTR_FREERODATA byte_t const __i386_cmpxchg8b_xch[] = {
	0xf0, 0x0f, 0xc7, 0x0f, /* 1:  lock   cmpxchg8b (%edi)   */
	0x75, 0xfb,             /*     jne    1b                 */
	0xc3,                   /*     ret                       */
};

#define I386_CMPXCHG8B_FETCHxxx(lo_opcode_, hi_opcode_)           \
	{                                                             \
		0x55,                   /*     pushl  %ebp             */ \
		0x56,                   /*     pushl  %esi             */ \
		0x89, 0xdd,             /*     movl   %ebx, %ebp       */ \
		0x89, 0xce,             /*     movl   %ecx, %esi       */ \
		0x89, 0xd8,             /*     movl   %ebx, %eax       */ \
		0x89, 0xca,             /*     movl   %ecx, %edx       */ \
		0xf0, 0x0f, 0xc7, 0x0f, /*     lock   cmpxchg8b (%edi) */ \
		lo_opcode_, 0xc3,       /* 1:  <lo>l  %eax, %ebx       */ \
		hi_opcode_, 0xd1,       /*     <hi>l  %edx, %ecx       */ \
		0xf0, 0x0f, 0xc7, 0x0f, /*     lock   cmpxchg8b (%edi) */ \
		0x75, 0x03,             /*     jne    2f               */ \
		0x5e,                   /*     popl   %esi             */ \
		0x5d,                   /*     popl   %ebp             */ \
		0xc3,                   /*     ret                     */ \
		0x89, 0xeb,             /* 2:  movl   %ebp, %ebx       */ \
		0x89, 0xf1,             /*     movl   %esi, %ecx       */ \
		0xeb, 0xee,             /*     jmp    1b               */ \
	}

PRIVATE ATTR_FREERODATA byte_t const __i386_cmpxchg8b_fetchadd[] = I386_CMPXCHG8B_FETCHxxx(0x01, 0x11); /* addl, adcl */
PRIVATE ATTR_FREERODATA byte_t const __i386_cmpxchg8b_fetchand[] = I386_CMPXCHG8B_FETCHxxx(0x21, 0x21); /* andl, andl */
PRIVATE ATTR_FREERODATA byte_t const __i386_cmpxchg8b_fetchor[]  = I386_CMPXCHG8B_FETCHxxx(0x09, 0x09); /* orl,  orl  */
PRIVATE ATTR_FREERODATA byte_t const __i386_cmpxchg8b_fetchxor[] = I386_CMPXCHG8B_FETCHxxx(0x31, 0x31); /* xorl, xorl */
#undef I386_CMPXCHG8B_FETCHxxx

/* Initialize the atomic64 configuration */
INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_atomic64)(void) {
	if (X86_HAVE_CMPXCHG8B) {
		/* Machine has native 64-bit atomic support. */
		memcpy(__i386_atomic64_read, __i386_cmpxchg8b_read, sizeof(__i386_cmpxchg8b_read));
		memcpy(__i386_atomic64_write, __i386_cmpxchg8b_xch, sizeof(__i386_cmpxchg8b_xch));
		memcpy(__i386_atomic64_cmpxch, __i386_cmpxchg8b_cmpxch, sizeof(__i386_cmpxchg8b_cmpxch));
		memcpy(__i386_atomic64_xch, __i386_cmpxchg8b_xch, sizeof(__i386_cmpxchg8b_xch));
		memcpy(__i386_atomic64_fetchadd, __i386_cmpxchg8b_fetchadd, sizeof(__i386_cmpxchg8b_fetchadd));
		memcpy(__i386_atomic64_fetchand, __i386_cmpxchg8b_fetchand, sizeof(__i386_cmpxchg8b_fetchand));
		memcpy(__i386_atomic64_fetchor, __i386_cmpxchg8b_fetchor, sizeof(__i386_cmpxchg8b_fetchor));
		memcpy(__i386_atomic64_fetchxor, __i386_cmpxchg8b_fetchxor, sizeof(__i386_cmpxchg8b_fetchxor));
		__flush_instruction_cache();
	}

#if !defined(NDEBUG) && 1
	{
		atomic64_t a = ATOMIC64_INIT(16);
		assertf(atomic64_read(&a) == 16, "%" PRIu64, _atomic64_val(a));
		atomic64_write(&a, 12);
		assertf(atomic64_read(&a) == 12, "%" PRIu64, _atomic64_val(a));
		assertf(atomic64_cmpxch_val(&a, 12, 14) == 12, "%" PRIu64, _atomic64_val(a));
		assertf(atomic64_cmpxch_val(&a, 12, 14) == 14, "%" PRIu64, _atomic64_val(a));
		assertf(atomic64_cmpxch(&a, 14, 13) == true, "%" PRIu64, _atomic64_val(a));
		assertf(atomic64_cmpxch(&a, 14, 13) == false, "%" PRIu64, _atomic64_val(a));
		assertf(atomic64_read(&a) == 13, "%" PRIu64, _atomic64_val(a));
		assertf(atomic64_fetchadd(&a, 7) == 13, "%" PRIu64, _atomic64_val(a));
		assertf(atomic64_read(&a) == 20, "%" PRIu64, _atomic64_val(a));
	}
#endif
}

DECL_END

#endif /* !__x86_64__ */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MISC_ATOMIC64_C */
