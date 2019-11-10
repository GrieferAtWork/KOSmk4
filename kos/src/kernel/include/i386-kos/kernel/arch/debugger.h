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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_DEBUGGER_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_DEBUGGER_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>
#include <stdarg.h>

#ifndef CONFIG_NO_DEBUGGER
#include <kos/kernel/segment.h>
#include <kos/kernel/gdt.h>

DECL_BEGIN

#ifdef __CC__

/* The GDT and IDT used by the debugger. */
DATDEF struct segment x86_debug_gdt[SEGMENT_COUNT];
DATDEF struct idt_segment x86_debug_idt[256] ASMNAME("__x86_dbgidt");

#endif /* __CC__ */

DECL_END
#endif /* !CONFIG_NO_DEBUGGER */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_DEBUGGER_H */
