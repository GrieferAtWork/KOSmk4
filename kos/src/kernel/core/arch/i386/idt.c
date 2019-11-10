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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_IDT_C
#define GUARD_KERNEL_CORE_ARCH_I386_IDT_C 1

#include <kernel/compiler.h>

#include <kernel/idt-foreach.h>
#include <kernel/idt.h>
#include <kernel/types.h>

#include <kos/kernel/cpu-state.h>
#include <kos/kernel/segment.h>

DECL_BEGIN

#ifdef CONFIG_NO_DEBUGGER
#define ISR_DEFINE_HILO(id)              \
	INTDEF byte_t __x86_defidtlo_##id[]; \
	INTDEF byte_t __x86_defidthi_##id[];
#else /* CONFIG_NO_DEBUGGER */
#define ISR_DEFINE_HILO(id)              \
	INTDEF byte_t __x86_defidtlo_##id[]; \
	INTDEF byte_t __x86_defidthi_##id[]; \
	INTDEF byte_t __x86_dbgidtlo_##id[]; \
	INTDEF byte_t __x86_dbgidthi_##id[];
#endif /* !CONFIG_NO_DEBUGGER */
IDT_X86_FOREACH(ISR_DEFINE_HILO)
#undef ISR_DEFINE_HILO
#ifdef __x86_64__
#define ISR_DEFINE_HILO(prefix, id)       \
	/* [0x##id] = */ {                    \
		/* .i_seg = */ { {                \
			 .s_u = (u64)prefix##lo_##id, \
		} },                              \
		/* .i_ext = */ { {                \
			 .s_u = (u64)prefix##hi_##id, \
		} }                               \
	},
#else /* __x86_64__ */
#define ISR_DEFINE_HILO(prefix, id)            \
	/* [0x##id] = */ {                         \
		/* .i_seg = */ { { {                   \
			/* .s_ul = */(u32)prefix##lo_##id, \
			/* .s_uh = */(u32)prefix##hi_##id  \
		} } }                                  \
	},
#endif /* !__x86_64__ */


/************************************************************************/
/* The Default InterruptDescriptorTable used by KOS                     */
/************************************************************************/
PUBLIC ATTR_SECTION(".data.hot") struct idt_segment x86_defidt[256] = {
#define ISR_DEFINE(id) ISR_DEFINE_HILO(__x86_defidt, id)
	IDT_X86_FOREACH(ISR_DEFINE)
#undef ISR_DEFINE
};

PUBLIC_CONST ATTR_SECTION(".rodata.cold") struct desctab const x86_defidt_ptr = {
	/* .dt_limit = */ sizeof(x86_defidt) - 1,
	/* .dt_base  = */ (uintptr_t)x86_defidt
};


/************************************************************************/
/* The InterruptDescriptorTable used by the builtin debugger            */
/************************************************************************/
#ifndef CONFIG_NO_DEBUGGER
PUBLIC ATTR_SECTION(".data.cold") struct idt_segment x86_dbgidt[256] = {
#define ISR_DEFINE(id) ISR_DEFINE_HILO(__x86_dbgidt, id)
	IDT_X86_FOREACH(ISR_DEFINE)
#undef ISR_DEFINE
};

PUBLIC_CONST ATTR_SECTION(".rodata.cold") struct desctab const x86_dbgidt_ptr = {
	/* .dt_limit = */ sizeof(x86_dbgidt) - 1,
	/* .dt_base  = */ (uintptr_t)x86_dbgidt
};
#endif /* !CONFIG_NO_DEBUGGER */




DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_IDT_C */
