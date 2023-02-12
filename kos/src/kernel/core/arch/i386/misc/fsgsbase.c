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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MISC_FSGSBASE_C
#define GUARD_KERNEL_CORE_ARCH_I386_MISC_FSGSBASE_C 1
#define DISABLE_BRANCH_PROFILING /* Don't profile this file */
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <hybrid/host.h>
#ifdef __x86_64__

#include <kernel/panic.h>
#include <kernel/types.h>
#include <kernel/x86/cpuid.h>
#include <kernel/x86/fsgsbase.h> /* x86_fsgsbase_patch() */

#include <hybrid/unaligned.h>

#include <asm/cpu-cpuid.h>

#include <assert.h>
#include <atomic.h>
#include <stddef.h>
#include <stdint.h>

#include "../fault/decode.h"

DECL_BEGIN

#define ENUM_FSGSBASE_REGISTERS(callback) \
	callback(rax)                         \
	callback(rcx)                         \
	callback(rdx)                         \
	callback(rbx)                         \
/*	callback(rsp) */                      \
	callback(rbp)                         \
	callback(rsi)                         \
	callback(rdi)                         \
	callback(r8)                          \
	callback(r9)                          \
	callback(r10)                         \
	callback(r11)                         \
	callback(r12)                         \
	callback(r13)                         \
	callback(r14)                         \
	callback(r15)
#define DEFINE_FSGSBASE_FUNCTIONS(reg)    \
	INTDEF byte_t __x64_rdfsbase_##reg[]; \
	INTDEF byte_t __x64_rdgsbase_##reg[]; \
	INTDEF byte_t __x64_wrfsbase_##reg[]; \
	INTDEF byte_t __x64_wrgsbase_##reg[];
ENUM_FSGSBASE_REGISTERS(DEFINE_FSGSBASE_FUNCTIONS)
#undef DEFINE_FSGSBASE_FUNCTIONS

enum{
	REGISTER_COUNT = 0
#define PLUS_ONE(x) +1
	ENUM_FSGSBASE_REGISTERS(PLUS_ONE)
#undef PLUS_ONE
};

typedef byte_t *fsgsbase_method_patches_t[REGISTER_COUNT];
typedef fsgsbase_method_patches_t fsgsbase_patches_t[4];

PRIVATE ATTR_COLDRODATA fsgsbase_patches_t const fsgsbase_patches = {
#define PATCH_RDFSBASE(reg) __x64_rdfsbase_##reg,
#define PATCH_RDGSBASE(reg) __x64_rdgsbase_##reg,
#define PATCH_WRFSBASE(reg) __x64_wrfsbase_##reg,
#define PATCH_WRGSBASE(reg) __x64_wrgsbase_##reg,
	{ ENUM_FSGSBASE_REGISTERS(PATCH_RDFSBASE) },
	{ ENUM_FSGSBASE_REGISTERS(PATCH_RDGSBASE) },
	{ ENUM_FSGSBASE_REGISTERS(PATCH_WRFSBASE) },
	{ ENUM_FSGSBASE_REGISTERS(PATCH_WRGSBASE) },
#undef PATCH_WRGSBASE
#undef PATCH_WRFSBASE
#undef PATCH_RDGSBASE
#undef PATCH_RDFSBASE
};



/* Patch one of the (rd|wr)(fs|gs)base instructions at `pc' to instead
 * become a call to one of the internal functions capable of emulating
 * the behavior of the instruction.
 * WARNING: Only the 64-bit variants of these instructions can be patched!
 *          The 32-bit variants cannot.
 * Before using this function, the caller should check that fsgsbase really
 * isn't  supported by  the host  CPU, as  indicated by `CPUID_7B_FSGSBASE'
 * @param: real_pc: The real  PC that  should  be used  for  DISP-offsets.
 *                  May differ from `pc' when `pc' points into an aliasing
 *                  memory mapping with write-access
 * @return: true:   Successfully patched the given code location.
 * @return: false:  The given code location was already patched,
 *                  or isn't  one  of  the  above  instructions. */
PUBLIC NOBLOCK ATTR_COLDTEXT bool
NOTHROW(FCALL x86_fsgsbase_patch)(void *pc, void const *real_pc) {
	/* F3 REX.W 0F AE /0 RDFSBASE r64 */
	/* F3 REX.W 0F AE /1 RDGSBASE r64 */
	/* F3 REX.W 0F AE /2 WRFSBASE r64 */
	/* F3 REX.W 0F AE /3 WRGSBASE r64 */
	byte_t rex, regno, method;
	byte_t *code = (byte_t *)pc;
	byte_t byte = code[0];
	void *patch;
	intptr_t pcrel;
	if (byte == 0xf3) {
		byte = code[1];
		if (!(byte >= 0x40 && byte <= 0x4f))
			return false; /* Missing REX prefix */
	} else if (byte >= 0x40 && byte <= 0x4f) {
		if (code[1] != 0xf3)
			return false; /* Missing F3 prefix */
	} else {
		return false; /* Missing REX/F3 prefix */
	}
	rex = byte & 0xf;
	if (!(rex & 8)) /* REX.W */
		return false; /* Wrong REX prefix */
	if (code[2] != 0x0f)
		return false; /* Wrong instruction */
	if (code[3] != 0xae)
		return false; /* Wrong instruction */
	byte = code[4]; /* mod r/m byte */
	if ((byte & EMU86_MODRM_MOD_MASK) != (0x3 << EMU86_MODRM_MOD_SHIFT))
		return false; /* Not a register operand. */
	regno = EMU86_MODRM_GETRM(byte);
	if (rex & 0x1) /* REX.B */
		regno |= 0x8;
	method = EMU86_MODRM_GETREG(byte);
	if unlikely(method >= 4)
		return false; /* Invalid MODRM.REG method */
	if (regno >= 4) {
		if (regno == 4)
			return false; /* %rsp (not emulated for this register) */
		--regno;
	}
	patch = fsgsbase_patches[method][regno];
	/* Generate a call to `patch' */
	pcrel = (intptr_t)patch - (intptr_t)((byte_t *)real_pc + 5);
	if unlikely(!(pcrel >= INT32_MIN || pcrel <= INT32_MAX))
		return false; /* Code is too far apart. */
	/* Patch the affected code location. */
	{
		union {
			u64 qword;
			u8  bytes[8];
		} oldword, newword;
		unsigned int patch_offset = 0;
		if (((uintptr_t)code & PAGEMASK) >= PAGESIZE - 8) {
			patch_offset = 3;
			code -= 3;
		}
		/* Use atomics to modify memory to ensure that code is always in a consistent state! */
		do {
			oldword.qword = atomic_read((u64 *)code);
			newword.qword = oldword.qword;
			newword.bytes[patch_offset] = 0xe8;
			UNALIGNED_SET32((u32 *)&newword.bytes[patch_offset + 1], (u32)pcrel);
		} while (!atomic_cmpxch_weak((u64 *)code, oldword.qword, newword.qword));
	}
	return true;
}


INTDEF FREE uint32_t __x86_fixup_fsgsbase_start[];
INTDEF FREE uint32_t __x86_fixup_fsgsbase_end[];

/* Patch all (rd|wr)(fs|gs)base text location within the kernel core. */
INTERN NOBLOCK ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_fsgsbase)(void) {
	uint32_t *iter;
	/* Check if our CPU supports fsgsbase. If it does, the we don't  have
	 * to do anything, and we can NOP out calls to `x86_fsgsbase_patch()' */
	if (X86_HAVE_FSGSBASE) {
		*((byte_t *)&x86_fsgsbase_patch + 0) = 0xc3; /* ret */
		return;
	}
	/* Patch all fsgsbase instructions within the kernel core. */
	for (iter = __x86_fixup_fsgsbase_start;
	     iter < __x86_fixup_fsgsbase_end; ++iter) {
		void *pc = (byte_t *)KERNEL_CORE_BASE + *iter;
		bool was_ok = x86_fsgsbase_patch(pc, pc);
		if unlikely(!was_ok)
			kernel_panic(FREESTR("Failed to patch fsgsbase instruction at %p\n"), pc);
	}
}



DECL_END
#endif /* __x86_64__ */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MISC_FSGSBASE_C */
