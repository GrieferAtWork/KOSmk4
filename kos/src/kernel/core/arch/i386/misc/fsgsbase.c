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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_FSGSBASE64_C
#define GUARD_KERNEL_CORE_ARCH_I386_FSGSBASE64_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <hybrid/host.h>
#ifdef __x86_64__

#include <kernel/fsgsbase.h>
#include <kernel/panic.h>
#include <kernel/types.h>

#include <hybrid/unaligned.h>

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "../fault/decode.h"

DECL_BEGIN

#define ENUM_FSGSBASE_REGISTERS(callback) \
	callback(rax)                         \
	callback(rcx)                         \
	callback(rdx)                         \
	callback(rbx)                         \
	callback(rbp)                         \
	callback(rdi)                         \
	callback(rsi)                         \
	callback(r8)                          \
	callback(r9)                          \
	callback(r10)                         \
	callback(r11)                         \
	callback(r12)                         \
	callback(r13)                         \
	callback(r14)                         \
	callback(r15)
#define DEFINE_FSGSBASE_FUNCTIONS(reg)       \
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
	{
#define PATCH_RDFSBASE(reg) __x64_rdfsbase_##reg,
		ENUM_FSGSBASE_REGISTERS(PATCH_RDFSBASE)
#undef PATCH_RDFSBASE
	},
	{
#define PATCH_RDGSBASE(reg) __x64_rdgsbase_##reg,
		ENUM_FSGSBASE_REGISTERS(PATCH_RDGSBASE)
#undef PATCH_RDGSBASE
	},
	{
#define PATCH_WRFSBASE(reg) __x64_wrfsbase_##reg,
		ENUM_FSGSBASE_REGISTERS(PATCH_WRFSBASE)
#undef PATCH_WRFSBASE
	},
	{
#define PATCH_WRGSBASE(reg) __x64_wrgsbase_##reg,
		ENUM_FSGSBASE_REGISTERS(PATCH_WRGSBASE)
#undef PATCH_WRGSBASE
	},
};



/* Patch one of the (rd|wr)(fs|gs)base instructions at `pc' to instead
 * become a call to one of the internal functions capable of emulating
 * the behavior of the instruction.
 * Before using this function, the caller should check that fsgsbase really
 * isn't supported by the host CPU, as indicated by `CPUID_7B_FSGSBASE'
 * @return: true:  Successfully patched the given code location.
 * @return: false: The given code location was already patched,
 *                 or isn't one of the above instructions. */
PUBLIC ATTR_COLDTEXT NOBLOCK bool
NOTHROW(KCALL x86_fsgsbase_patch)(void *__restrict pc) {
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
	if (!(rex & F_REX_W))
		return false; /* Wrong REX prefix */
	if (code[2] != 0x0f)
		return false; /* Wrong instruction */
	if (code[3] != 0xae)
		return false; /* Wrong instruction */
	byte = code[4]; /* mod r/m byte */
	if ((byte & MODRM_MOD_MASK) != (0x3 << MODRM_MOD_SHIFT))
		return false; /* Not a register operand. */
	regno = MODRM_GETRM(byte);
	if (rex & F_REX_B)
		regno |= 0x8;
	method = MODRM_GETREG(byte);
	if unlikely(method >= 4)
		return false; /* Invalid MODRM.REG method */
	if (regno >= 4) {
		if (regno == 4)
			return false; /* %rsp (not emulated for this register) */
		--regno;
	}
	patch = fsgsbase_patches[method][regno];
	/* Generate a call to `patch' */
	pcrel = (intptr_t)patch - (intptr_t)(code + 5);
#if 0 /* This can't happen because that would mean that `pc' is outside of the kernel's memory region. */
	if unlikely(!(pcrel >= INT32_MIN || pcrel <= INT32_MAX))
		return false; /* Code is too far apart. */
#else
	assertf(pcrel >= INT32_MIN || pcrel <= INT32_MAX,
	        "Attempted to patch code at %p, which is outside of the -2Gib...+2Gib range");
#endif
	/* Patch the affected code location. */
	code[0] = 0xe8;
	UNALIGNED_SET32((u32 *)(code + 1), (u32)pcrel);
	return true;
}


INTDEF uint32_t __x64_fixup_fsgsbase_start[];
INTDEF uint32_t __x64_fixup_fsgsbase_end[];

/* Patch all (rd|wr)(fs|gs)base text location within the kernel core. */
INTERN NOBLOCK ATTR_FREETEXT void
NOTHROW(KCALL fsgsbase_patch_kernel)(void) {
	uint32_t *iter;
	/* TODO: Call this function from _start64.S if the boot
	 *       CPU doesn't support the fsgsbase instruction set. */

	/* Patch all fsgsbase instructions within the kernel core. */
	for (iter = __x64_fixup_fsgsbase_start;
	     iter < __x64_fixup_fsgsbase_end; ++iter) {
		uintptr_t pc = KERNEL_CORE_BASE + *iter;
		bool was_ok = x86_fsgsbase_patch((void *)pc);
		if unlikely(!was_ok)
			kernel_panic(FREESTR("Failed to patch fsgsbase instruction at %p\n"), pc);
	}
}



DECL_END
#endif /* __x86_64__ */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_FSGSBASE64_C */
