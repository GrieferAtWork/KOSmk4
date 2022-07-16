/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif([](x) -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MEMORY_POISON_HEAP_C
#define GUARD_KERNEL_CORE_ARCH_I386_MEMORY_POISON_HEAP_C 1

#include <kernel/compiler.h>

#include <kernel/poison-heap.h>

#ifdef CONFIG_HAVE_KERNEL_POISON_HEAP
#include <kernel/driver-param.h>
#include <kernel/types.h>
#include <kernel/mman/phys.h>

#include <hybrid/host.h>
#include <hybrid/unaligned.h>

#include <asm/intrin.h>
#include <kos/kernel/paging.h>

DECL_BEGIN

struct ph_item {
	byte_t     *pi_loc; /* Location where to inject the redirection/return */
	union {
		byte_t *pi_dst; /* [valid_if(ADDR_ISKERN(pi_dst))] Target where-to point a redirection */
		size_t  pi_ret; /* [valid_if(!ADDR_ISKERN(pi_dst))] # of bytes to unwind during a ret. The
		                 * least significant bit indicates that the function should return  0/NULL */
	};
};

#define PH_DECLARE_FUNC(heap_symbol, ph_heap_symbol)       \
	extern byte_t d_##heap_symbol[] ASMNAME(#heap_symbol); \
	extern byte_t d_##ph_heap_symbol[] ASMNAME(#ph_heap_symbol);
#define PH_DECLARE_VOID(heap_symbol, ph_heap_symbol, argc) \
	extern byte_t d_##heap_symbol[] ASMNAME(#heap_symbol);
#define PH_DECLARE_ZERO(heap_symbol, ph_heap_symbol, argc) \
	extern byte_t d_##heap_symbol[] ASMNAME(#heap_symbol);
KERNEL_POISON_HEAP_ENUMERATE_BINDINGS(PH_DECLARE_FUNC,
                                      PH_DECLARE_VOID,
                                      PH_DECLARE_ZERO)
#undef PH_DECLARE_ZERO
#undef PH_DECLARE_VOID
#undef PH_DECLARE_FUNC

PRIVATE ATTR_COLDRODATA struct ph_item const ph_install_seq[] = {
#define PH_INSTALL_FUNC(heap_symbol, ph_heap_symbol)       { d_##heap_symbol, { d_##ph_heap_symbol } },
#ifdef __x86_64__
#define PH_INSTALL_VOID(heap_symbol, ph_heap_symbol, argc) { d_##heap_symbol, { (byte_t *)0 } },
#define PH_INSTALL_ZERO(heap_symbol, ph_heap_symbol, argc) { d_##heap_symbol, { (byte_t *)1 } },
#else /* __x86_64__ */
#define PH_INSTALL_VOID(heap_symbol, ph_heap_symbol, argc) { d_##heap_symbol, { (byte_t *)((uintptr_t)argc * 4) } },
#define PH_INSTALL_ZERO(heap_symbol, ph_heap_symbol, argc) { d_##heap_symbol, { (byte_t *)((uintptr_t)argc * 4 + 1) } },
#endif /* !__x86_64__ */
	KERNEL_POISON_HEAP_ENUMERATE_BINDINGS(PH_INSTALL_FUNC,
	                                      PH_INSTALL_VOID,
	                                      PH_INSTALL_ZERO)
#undef PH_INSTALL_ZERO
#undef PH_INSTALL_VOID
#undef PH_INSTALL_FUNC
};


/* Boot option: Don't bind the poison heap upon kernel panic. */
DEFINE_CMDLINE_FLAG_VAR(boot_no_poison_heap, "no_poison_heap");


/* Install poison heap overrides.
 * NOTE: This function must be called immediately
 *       after `_kernel_poisoned' is set to true. */
INTERN NOBLOCK ATTR_COLDTEXT void NOTHROW(KCALL ph_install)(void) {
	unsigned int i;
	if (boot_no_poison_heap)
		return;
	for (i = 0; i < COMPILER_LENOF(ph_install_seq); ++i) {
		/* Buffer of override instructions. */
		byte_t buf[8];
		size_t buflen = 0;
		struct ph_item const *item;
		item = &ph_install_seq[i];
		if (ADDR_ISKERN(item->pi_dst)) {
			s32 disp;
			/* Write a `jmp' instruction. */
			buf[buflen++] = 0xe9;
			disp = (s32)((intptr_t)(item->pi_dst) -
			             (intptr_t)(item->pi_loc + buflen + 4));
			UNALIGNED_SET32((u32 *)&buf[buflen], (u32)disp);
			buflen += 4;
		} else {
			/* write a `ret' with an optional `xorP %Pax, %Pax' prefix */
			if (item->pi_ret & 1) {
				/* Override to have the function return NULL/0 */
#ifdef __x86_64__
				buf[buflen++] = 0x48; /* REX */
#endif /* __x86_64__ */
				buf[buflen++] = 0x31; /* xorl */
				buf[buflen++] = 0xc0; /* %eax, %eax */
			}
#ifndef __x86_64__
			if (item->pi_ret >= 2) {
				/* use a `ret imm16' instruction */
				buf[buflen++] = 0xc2; /* ret imm16 */
				UNALIGNED_SET16((u16 *)&buf[buflen],
				                (u16)(item->pi_ret & ~1));
				buflen += 2;
			} else
#endif /* !__x86_64__ */
			{
				/* Use a normal `ret' instruction */
				buf[buflen++] = 0xc3; /* ret */
			}
		}
		/* Write the modified instruction */
		copytophys((physaddr_t)((uintptr_t)item->pi_loc -
		                       KERNEL_CORE_BASE),
		           buf, buflen);
	}
	__flush_instruction_cache();
}

DECL_END
#endif /* CONFIG_HAVE_KERNEL_POISON_HEAP */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MEMORY_POISON_HEAP_C */
