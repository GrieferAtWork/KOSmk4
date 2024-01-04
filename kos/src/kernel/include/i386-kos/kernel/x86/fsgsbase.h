/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_FSGSBASE_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_FSGSBASE_H 1

#include <hybrid/compiler.h>
#include <hybrid/__asm.h>
#include <hybrid/host.h>

#ifdef __x86_64__
#include <kos/kernel/paging.h>

/* On x86_64, there may potentially exist 4 instruction:
 *   - rdfsbase
 *   - rdgsbase
 *   - wrfsbase
 *   - wrgsbase
 * These instructions are only present when a certain CPUID bit (CPUID_7B_FSGSBASE)
 * is  set, but if that bit isn't set,  these instruction must be emulated by using
 * certain calls to (rd|wr)msr, which we emulate on x86_64 at runtime by saving the
 * address  of every use of these instructions in a big list that gets relocated at
 * runtime if this CPU feature isn't present.
 * This can be done fairly easily, since the opcode sequence for any of the aforementioned
 * instructions  is always 5 bytes (when the operand  is 64-bit, which is should always be
 * within   the   kernel,  as   a   32-bit  operand   would   mean  a   truncated  result)
 * These  5 bits can  then easily be replaced  with a call-instruction  to a function that
 * emulates  the  instruction's  behavior  by  simply  setting  the  proper  MSR register. */
__ASM_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("rdfsbase")
#pragma push_macro("rdgsbase")
#pragma push_macro("wrfsbase")
#pragma push_macro("wrgsbase")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef rdfsbase
#undef rdgsbase
#undef wrfsbase
#undef wrgsbase

#if defined(CONFIG_ASSUME_CPU_SUPPORTS_FSGSBASE) || !defined(BUILDING_KERNEL_CORE)
__ASM_L(.macro safe_rdfsbase reg:req)
__ASM_L(	rdfsbase __ASM_ARG(\reg))
__ASM_L(.endm)

__ASM_L(.macro safe_rdgsbase reg:req)
__ASM_L(	rdgsbase __ASM_ARG(\reg))
__ASM_L(.endm)

__ASM_L(.macro safe_wrfsbase reg:req)
__ASM_L(	wrfsbase __ASM_ARG(\reg))
__ASM_L(.endm)

__ASM_L(.macro safe_wrgsbase reg:req)
__ASM_L(	wrgsbase __ASM_ARG(\reg))
__ASM_L(.endm)

#else /* CONFIG_ASSUME_CPU_SUPPORTS_FSGSBASE || !BUILDING_KERNEL_CORE */

#define __MODREL_POINTER(x) .int x - KERNEL_CORE_BASE
__ASM_L(.macro safe_rdfsbase reg:req)
__ASM_L(.pushsection .rodata.free.x86.fixup_fsgsbase)
__ASM_L(	__MODREL_POINTER(991f))
__ASM_L(.popsection)
__ASM_L(991: rdfsbase __ASM_ARG(\reg))
__ASM_L(.endm)

__ASM_L(.macro safe_rdgsbase reg:req)
__ASM_L(.pushsection .rodata.free.x86.fixup_fsgsbase)
__ASM_L(	__MODREL_POINTER(991f))
__ASM_L(.popsection)
__ASM_L(991: rdgsbase __ASM_ARG(\reg))
__ASM_L(.endm)

__ASM_L(.macro safe_wrfsbase reg:req)
__ASM_L(.pushsection .rodata.free.x86.fixup_fsgsbase)
__ASM_L(	__MODREL_POINTER(991f))
__ASM_L(.popsection)
__ASM_L(991: wrfsbase __ASM_ARG(\reg))
__ASM_L(.endm)

__ASM_L(.macro safe_wrgsbase reg:req)
__ASM_L(.pushsection .rodata.free.x86.fixup_fsgsbase)
__ASM_L(	__MODREL_POINTER(991f))
__ASM_L(.popsection)
__ASM_L(991: wrgsbase __ASM_ARG(\reg))
__ASM_L(.endm)
#undef __MODREL_POINTER
#endif /* !CONFIG_ASSUME_CPU_SUPPORTS_FSGSBASE && BUILDING_KERNEL_CORE */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("wrgsbase")
#pragma pop_macro("wrfsbase")
#pragma pop_macro("rdgsbase")
#pragma pop_macro("rdfsbase")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */


#ifdef __ASSEMBLER__
#ifndef CONFIG_ASSUME_CPU_SUPPORTS_FSGSBASE
/* Re-map the fs/gs instructions to automatically make use of the relocation tables. */
#define rdfsbaseq  safe_rdfsbase
#define rdgsbaseq  safe_rdgsbase
#define wrfsbaseq  safe_wrfsbase
#define wrgsbaseq  safe_wrgsbase
#define rdfsbase   ;.error "Dont use `rdfsbase`, use `rdfsbaseq` instead";
#define rdgsbase   ;.error "Dont use `rdgsbase`, use `rdgsbaseq` instead";
#define wrfsbase   ;.error "Dont use `wrfsbase`, use `wrfsbaseq` instead";
#define wrgsbase   ;.error "Dont use `wrgsbase`, use `wrgsbaseq` instead";
#define rdfsbasel  ;.error "Dont use `rdfsbasel`, use `rdfsbaseq` instead";
#define rdgsbasel  ;.error "Dont use `rdgsbasel`, use `rdgsbaseq` instead";
#define wrfsbasel  ;.error "Dont use `wrfsbasel`, use `wrfsbaseq` instead";
#define wrgsbasel  ;.error "Dont use `wrgsbasel`, use `wrgsbaseq` instead";
#endif /* !CONFIG_ASSUME_CPU_SUPPORTS_FSGSBASE */
#endif /* __ASSEMBLER__ */

__ASM_END


#ifdef __CC__
#include <kernel/compiler.h>
#include <hybrid/host.h>

DECL_BEGIN

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
FUNDEF NOBLOCK __BOOL
NOTHROW(FCALL x86_fsgsbase_patch)(void *pc, void const *real_pc);

DECL_END

#endif /* __CC__ */

#endif /* __x86_64__ */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_FSGSBASE_H */
