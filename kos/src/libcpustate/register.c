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
#ifndef GUARD_LIBCPUSTATE_REGISTER_C
#define GUARD_LIBCPUSTATE_REGISTER_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/align.h>
#include <hybrid/host.h>

#include <asm/registers.h>
#include <kos/types.h>

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <libcpustate/register.h>

#if defined(__i386__) || defined(__x86_64__)
#include <asm/registers-compat.h>
#endif /* __i386__ || __x86_64__ */

DECL_BEGIN

#ifdef __x86_64__
#define REG_ISPREG      UINT32_C(0x80000000) /* Flag: register is pointer-sized */
#define REG_NAME_MAXLEN 12
#define register_db_entry_getregno(self, isa)                        \
	(!((self)->rde_regno & REG_ISPREG)                               \
	 ? (self)->rde_regno /* non-isa-specific register */             \
	 : (((self)->rde_regno & ~REG_ISPREG & ~X86_REGISTER_SIZEMASK) | \
	    (isa == ISA_I386 ? X86_REGISTER_SIZEMASK_4BYTE      \
	                              : X86_REGISTER_SIZEMASK_8BYTE)))
#elif defined(__i386__)
#define REG_NAME_MAXLEN 12
#elif defined(__arm__)
#define REG_NAME_MAXLEN 12
#else /* ... */
#error "Unsupported architecture"
#endif /* ... */

struct register_db_entry {
	cpu_regno_t rde_regno;                                                     /* Register ID */
	char        rde_name[CEIL_ALIGN(REG_NAME_MAXLEN, __SIZEOF_CPU_REGNO_T__)]; /* Register name */
};

#ifndef register_db_entry_getregno
#define register_db_entry_getregno(self, isa) (self)->rde_regno
#endif /* !register_db_entry_getregno */



PRIVATE struct register_db_entry const register_db[] = {
#define REG(id, name) { id, name }
#if defined(__x86_64__) || defined(__i386__)
	/************************************************************************/
	/* X86                                                                  */
	/************************************************************************/
#ifdef __x86_64__
#define PEG(id, name) REG(id | REG_ISPREG, name)
#define R64(id, name) REG(id, name),
#else /* __x86_64__ */
#define PEG(id, name) REG(id, name)
#define R64(id, name) /* nothing */
#endif /* !__x86_64__ */

	/* Portable register names */
	PEG(X86_REGISTER_MISC_PIP, /*               */ "pc"),
	PEG(X86_REGISTER_GENERAL_PURPOSE_PSP, /*    */ "sp"),

	/* X86-specific register names     */
	REG(X86_REGISTER_GENERAL_PURPOSE_AL, /*     */ "al"),
	REG(X86_REGISTER_GENERAL_PURPOSE_CL, /*     */ "cl"),
	REG(X86_REGISTER_GENERAL_PURPOSE_DL, /*     */ "dl"),
	REG(X86_REGISTER_GENERAL_PURPOSE_BL, /*     */ "bl"),
	REG(X86_REGISTER_GENERAL_PURPOSE_AH, /*     */ "ah"),
	REG(X86_REGISTER_GENERAL_PURPOSE_CH, /*     */ "ch"),
	REG(X86_REGISTER_GENERAL_PURPOSE_DH, /*     */ "dh"),
	REG(X86_REGISTER_GENERAL_PURPOSE_BH, /*     */ "bh"),
#ifdef __x86_64__
	REG(X86_REGISTER_GENERAL_PURPOSE_SPL, /*    */ "spl"),
	REG(X86_REGISTER_GENERAL_PURPOSE_BPL, /*    */ "bpl"),
	REG(X86_REGISTER_GENERAL_PURPOSE_SIL, /*    */ "sil"),
	REG(X86_REGISTER_GENERAL_PURPOSE_DIL, /*    */ "dil"),
#endif /* __x86_64__ */

	REG(X86_REGISTER_GENERAL_PURPOSE_AX, /*     */ "ax"),
	REG(X86_REGISTER_GENERAL_PURPOSE_CX, /*     */ "cx"),
	REG(X86_REGISTER_GENERAL_PURPOSE_DX, /*     */ "dx"),
	REG(X86_REGISTER_GENERAL_PURPOSE_BX, /*     */ "bx"),
//	REG(X86_REGISTER_GENERAL_PURPOSE_SP, /*     */ "sp"),
	REG(X86_REGISTER_GENERAL_PURPOSE_BP, /*     */ "bp"),
	REG(X86_REGISTER_GENERAL_PURPOSE_SI, /*     */ "si"),
	REG(X86_REGISTER_GENERAL_PURPOSE_DI, /*     */ "di"),
	REG(X86_REGISTER_MISC_IP, /*                */ "ip"),
	REG(X86_REGISTER_MISC_FLAGS, /*             */ "flags"),

	REG(X86_REGISTER_GENERAL_PURPOSE_EAX, /*    */ "eax"),
	REG(X86_REGISTER_GENERAL_PURPOSE_ECX, /*    */ "ecx"),
	REG(X86_REGISTER_GENERAL_PURPOSE_EDX, /*    */ "edx"),
	REG(X86_REGISTER_GENERAL_PURPOSE_EBX, /*    */ "ebx"),
	REG(X86_REGISTER_GENERAL_PURPOSE_ESP, /*    */ "esp"),
	REG(X86_REGISTER_GENERAL_PURPOSE_EBP, /*    */ "ebp"),
	REG(X86_REGISTER_GENERAL_PURPOSE_ESI, /*    */ "esi"),
	REG(X86_REGISTER_GENERAL_PURPOSE_EDI, /*    */ "edi"),
	REG(X86_REGISTER_MISC_EIP, /*               */ "eip"),
	REG(X86_REGISTER_MISC_EFLAGS, /*            */ "eflags"),

	PEG(X86_REGISTER_GENERAL_PURPOSE_PAX, /*    */ "pax"),
	PEG(X86_REGISTER_GENERAL_PURPOSE_PCX, /*    */ "pcx"),
	PEG(X86_REGISTER_GENERAL_PURPOSE_PDX, /*    */ "pdx"),
	PEG(X86_REGISTER_GENERAL_PURPOSE_PBX, /*    */ "pbx"),
	PEG(X86_REGISTER_GENERAL_PURPOSE_PSP, /*    */ "psp"),
	PEG(X86_REGISTER_GENERAL_PURPOSE_PBP, /*    */ "pbp"),
	PEG(X86_REGISTER_GENERAL_PURPOSE_PSI, /*    */ "psi"),
	PEG(X86_REGISTER_GENERAL_PURPOSE_PDI, /*    */ "pdi"),
	PEG(X86_REGISTER_MISC_PIP, /*               */ "pip"),
	PEG(X86_REGISTER_MISC_PFLAGS, /*            */ "pflags"),

#ifdef __x86_64__
	REG(X86_REGISTER_GENERAL_PURPOSE_RAX, /*    */ "rax"),
	REG(X86_REGISTER_GENERAL_PURPOSE_RCX, /*    */ "rcx"),
	REG(X86_REGISTER_GENERAL_PURPOSE_RDX, /*    */ "rdx"),
	REG(X86_REGISTER_GENERAL_PURPOSE_RBX, /*    */ "rbx"),
	REG(X86_REGISTER_GENERAL_PURPOSE_RSP, /*    */ "rsp"),
	REG(X86_REGISTER_GENERAL_PURPOSE_RBP, /*    */ "rbp"),
	REG(X86_REGISTER_GENERAL_PURPOSE_RSI, /*    */ "rsi"),
	REG(X86_REGISTER_GENERAL_PURPOSE_RDI, /*    */ "rdi"),
	REG(X86_REGISTER_MISC_RIP, /*               */ "rip"),
	REG(X86_REGISTER_MISC_RFLAGS, /*            */ "rflags"),
	REG(X86_REGISTER_GENERAL_PURPOSE_R8, /*     */ "r8"),
	REG(X86_REGISTER_GENERAL_PURPOSE_R9, /*     */ "r9"),
	REG(X86_REGISTER_GENERAL_PURPOSE_R10, /*    */ "r10"),
	REG(X86_REGISTER_GENERAL_PURPOSE_R11, /*    */ "r11"),
	REG(X86_REGISTER_GENERAL_PURPOSE_R12, /*    */ "r12"),
	REG(X86_REGISTER_GENERAL_PURPOSE_R13, /*    */ "r13"),
	REG(X86_REGISTER_GENERAL_PURPOSE_R14, /*    */ "r14"),
	REG(X86_REGISTER_GENERAL_PURPOSE_R15, /*    */ "r15"),

	REG(X86_REGISTER_GENERAL_PURPOSE_R8D, /*    */ "r8d"),
	REG(X86_REGISTER_GENERAL_PURPOSE_R9D, /*    */ "r9d"),
	REG(X86_REGISTER_GENERAL_PURPOSE_R10D, /*   */ "r10d"),
	REG(X86_REGISTER_GENERAL_PURPOSE_R11D, /*   */ "r11d"),
	REG(X86_REGISTER_GENERAL_PURPOSE_R12D, /*   */ "r12d"),
	REG(X86_REGISTER_GENERAL_PURPOSE_R13D, /*   */ "r13d"),
	REG(X86_REGISTER_GENERAL_PURPOSE_R14D, /*   */ "r14d"),
	REG(X86_REGISTER_GENERAL_PURPOSE_R15D, /*   */ "r15d"),

	REG(X86_REGISTER_GENERAL_PURPOSE_R8W, /*    */ "r8w"),
	REG(X86_REGISTER_GENERAL_PURPOSE_R9W, /*    */ "r9w"),
	REG(X86_REGISTER_GENERAL_PURPOSE_R10W, /*   */ "r10w"),
	REG(X86_REGISTER_GENERAL_PURPOSE_R11W, /*   */ "r11w"),
	REG(X86_REGISTER_GENERAL_PURPOSE_R12W, /*   */ "r12w"),
	REG(X86_REGISTER_GENERAL_PURPOSE_R13W, /*   */ "r13w"),
	REG(X86_REGISTER_GENERAL_PURPOSE_R14W, /*   */ "r14w"),
	REG(X86_REGISTER_GENERAL_PURPOSE_R15W, /*   */ "r15w"),

	REG(X86_REGISTER_GENERAL_PURPOSE_R8L, /*    */ "r8l"),
	REG(X86_REGISTER_GENERAL_PURPOSE_R9L, /*    */ "r9l"),
	REG(X86_REGISTER_GENERAL_PURPOSE_R10L, /*   */ "r10l"),
	REG(X86_REGISTER_GENERAL_PURPOSE_R11L, /*   */ "r11l"),
	REG(X86_REGISTER_GENERAL_PURPOSE_R12L, /*   */ "r12l"),
	REG(X86_REGISTER_GENERAL_PURPOSE_R13L, /*   */ "r13l"),
	REG(X86_REGISTER_GENERAL_PURPOSE_R14L, /*   */ "r14l"),
	REG(X86_REGISTER_GENERAL_PURPOSE_R15L, /*   */ "r15l"),
#endif /* __x86_64__ */

	REG(X86_REGISTER_SEGMENT_ES, /*             */ "es"),
	REG(X86_REGISTER_SEGMENT_CS, /*             */ "cs"),
	REG(X86_REGISTER_SEGMENT_SS, /*             */ "ss"),
	REG(X86_REGISTER_SEGMENT_DS, /*             */ "ds"),
	REG(X86_REGISTER_SEGMENT_FS, /*             */ "fs"),
	REG(X86_REGISTER_SEGMENT_GS, /*             */ "gs"),

	REG(X86_REGISTER_CONTROL_CR0, /*            */ "cr0"),
	REG(X86_REGISTER_CONTROL_CR2, /*            */ "cr2"),
	REG(X86_REGISTER_CONTROL_CR3, /*            */ "cr3"),
	REG(X86_REGISTER_CONTROL_CR4, /*            */ "cr4"),
#ifdef __x86_64__
	REG(X86_REGISTER_CONTROL_CR8, /*            */ "cr8"),
#endif /* __x86_64__ */

	REG(X86_REGISTER_FLOAT_ST0, /*              */ "st0"),
	REG(X86_REGISTER_FLOAT_ST1, /*              */ "st1"),
	REG(X86_REGISTER_FLOAT_ST2, /*              */ "st2"),
	REG(X86_REGISTER_FLOAT_ST3, /*              */ "st3"),
	REG(X86_REGISTER_FLOAT_ST4, /*              */ "st4"),
	REG(X86_REGISTER_FLOAT_ST5, /*              */ "st5"),
	REG(X86_REGISTER_FLOAT_ST6, /*              */ "st6"),
	REG(X86_REGISTER_FLOAT_ST7, /*              */ "st7"),

	REG(X86_REGISTER_FLOAT_ST0, /*              */ "st(0)"),
	REG(X86_REGISTER_FLOAT_ST1, /*              */ "st(1)"),
	REG(X86_REGISTER_FLOAT_ST2, /*              */ "st(2)"),
	REG(X86_REGISTER_FLOAT_ST3, /*              */ "st(3)"),
	REG(X86_REGISTER_FLOAT_ST4, /*              */ "st(4)"),
	REG(X86_REGISTER_FLOAT_ST5, /*              */ "st(5)"),
	REG(X86_REGISTER_FLOAT_ST6, /*              */ "st(6)"),
	REG(X86_REGISTER_FLOAT_ST7, /*              */ "st(7)"),

	REG(X86_REGISTER_MMX_MM0, /*                */ "mm0"),
	REG(X86_REGISTER_MMX_MM1, /*                */ "mm1"),
	REG(X86_REGISTER_MMX_MM2, /*                */ "mm2"),
	REG(X86_REGISTER_MMX_MM3, /*                */ "mm3"),
	REG(X86_REGISTER_MMX_MM4, /*                */ "mm4"),
	REG(X86_REGISTER_MMX_MM5, /*                */ "mm5"),
	REG(X86_REGISTER_MMX_MM6, /*                */ "mm6"),
	REG(X86_REGISTER_MMX_MM7, /*                */ "mm7"),

	REG(X86_REGISTER_XMM_XMM0, /*               */ "xmm0"),
	REG(X86_REGISTER_XMM_XMM1, /*               */ "xmm1"),
	REG(X86_REGISTER_XMM_XMM2, /*               */ "xmm2"),
	REG(X86_REGISTER_XMM_XMM3, /*               */ "xmm3"),
	REG(X86_REGISTER_XMM_XMM4, /*               */ "xmm4"),
	REG(X86_REGISTER_XMM_XMM5, /*               */ "xmm5"),
	REG(X86_REGISTER_XMM_XMM6, /*               */ "xmm6"),
	REG(X86_REGISTER_XMM_XMM7, /*               */ "xmm7"),
#ifdef __x86_64__
	REG(X86_REGISTER_XMM_XMM8, /*               */ "xmm8"),
	REG(X86_REGISTER_XMM_XMM9, /*               */ "xmm9"),
	REG(X86_REGISTER_XMM_XMM10, /*              */ "xmm10"),
	REG(X86_REGISTER_XMM_XMM11, /*              */ "xmm11"),
	REG(X86_REGISTER_XMM_XMM12, /*              */ "xmm12"),
	REG(X86_REGISTER_XMM_XMM13, /*              */ "xmm13"),
	REG(X86_REGISTER_XMM_XMM14, /*              */ "xmm14"),
	REG(X86_REGISTER_XMM_XMM15, /*              */ "xmm15"),
#endif /* __x86_64__ */

	REG(X86_REGISTER_YMM_YMM0, /*               */ "ymm0"),
	REG(X86_REGISTER_YMM_YMM1, /*               */ "ymm1"),
	REG(X86_REGISTER_YMM_YMM2, /*               */ "ymm2"),
	REG(X86_REGISTER_YMM_YMM3, /*               */ "ymm3"),
	REG(X86_REGISTER_YMM_YMM4, /*               */ "ymm4"),
	REG(X86_REGISTER_YMM_YMM5, /*               */ "ymm5"),
	REG(X86_REGISTER_YMM_YMM6, /*               */ "ymm6"),
	REG(X86_REGISTER_YMM_YMM7, /*               */ "ymm7"),
#ifdef __x86_64__
	REG(X86_REGISTER_YMM_YMM8, /*               */ "ymm8"),
	REG(X86_REGISTER_YMM_YMM9, /*               */ "ymm9"),
	REG(X86_REGISTER_YMM_YMM10, /*              */ "ymm10"),
	REG(X86_REGISTER_YMM_YMM11, /*              */ "ymm11"),
	REG(X86_REGISTER_YMM_YMM12, /*              */ "ymm12"),
	REG(X86_REGISTER_YMM_YMM13, /*              */ "ymm13"),
	REG(X86_REGISTER_YMM_YMM14, /*              */ "ymm14"),
	REG(X86_REGISTER_YMM_YMM15, /*              */ "ymm15"),
#endif /* __x86_64__ */

	REG(X86_REGISTER_DEBUG_DR0, /*              */ "dr0"),
	REG(X86_REGISTER_DEBUG_DR1, /*              */ "dr1"),
	REG(X86_REGISTER_DEBUG_DR2, /*              */ "dr2"),
	REG(X86_REGISTER_DEBUG_DR3, /*              */ "dr3"),
	REG(X86_REGISTER_DEBUG_DR6, /*              */ "dr6"),
	REG(X86_REGISTER_DEBUG_DR7, /*              */ "dr7"),

	REG(X86_REGISTER_MISC_TR, /*                */ "tr"),
	REG(X86_REGISTER_MISC_LDT, /*               */ "ldt"),
	REG(X86_REGISTER_MISC_GDT_LIMIT, /*         */ "gdt.limit"),
	PEG(X86_REGISTER_MISC_GDT_BASE, /*          */ "gdt.base"),
	REG(X86_REGISTER_MISC_GDT_BASEL, /*         */ "gdt.basel"),
	R64(X86_REGISTER_MISC_GDT_BASEQ, /*         */ "gdt.baseq")
	REG(X86_REGISTER_MISC_IDT_LIMIT, /*         */ "idt.limit"),
	PEG(X86_REGISTER_MISC_IDT_BASE, /*          */ "idt.base"),
	REG(X86_REGISTER_MISC_IDT_BASEL, /*         */ "idt.basel"),
	R64(X86_REGISTER_MISC_IDT_BASEQ, /*         */ "idt.baseq")
	PEG(X86_REGISTER_MISC_FSBASE, /*            */ "fs.base"),
	REG(X86_REGISTER_MISC_FSBASEL, /*           */ "fs.basel"),
	R64(X86_REGISTER_MISC_FSBASEQ, /*           */ "fs.baseq")
	PEG(X86_REGISTER_MISC_GSBASE, /*            */ "gs.base"),
	REG(X86_REGISTER_MISC_GSBASEL, /*           */ "gs.basel"),
	R64(X86_REGISTER_MISC_GSBASEQ, /*           */ "gs.baseq")
	REG(X86_REGISTER_MISC_FCW, /*               */ "fcw"),
	REG(X86_REGISTER_MISC_FSW, /*               */ "fsw"),
	REG(X86_REGISTER_MISC_FTW, /*               */ "ftw"),
	REG(X86_REGISTER_MISC_FTWX, /*              */ "ftwx"),
	REG(X86_REGISTER_MISC_FOP, /*               */ "fop"),
	PEG(X86_REGISTER_MISC_FIP, /*               */ "fip"),
	REG(X86_REGISTER_MISC_FIPL, /*              */ "fipl"),
	R64(X86_REGISTER_MISC_FIPQ, /*              */ "fipq")
	REG(X86_REGISTER_MISC_FCS, /*               */ "fcs"),
	PEG(X86_REGISTER_MISC_FDP, /*               */ "fdp"),
	REG(X86_REGISTER_MISC_FDPL, /*              */ "fdpl"),
	R64(X86_REGISTER_MISC_FDPQ, /*              */ "fdpq")
	REG(X86_REGISTER_MISC_FDS, /*               */ "fds"),
	REG(X86_REGISTER_MISC_MXCSR, /*             */ "mxcsr"),
	REG(X86_REGISTER_MISC_MXCSR_MASK, /*        */ "mxcsr_mask"),
#undef R64
#undef PEG
#elif defined(__arm__)

	/************************************************************************/
	/* ARM                                                                  */
	/************************************************************************/

	/* Portable register names */
	REG(ARM_REGISTER_PC, /*                     */ "pc"),
	REG(ARM_REGISTER_SP, /*                     */ "sp"),

	REG(ARM_REGISTER_R0, /*                     */ "r0"),
	REG(ARM_REGISTER_R1, /*                     */ "r1"),
	REG(ARM_REGISTER_R2, /*                     */ "r2"),
	REG(ARM_REGISTER_R3, /*                     */ "r3"),
	REG(ARM_REGISTER_R4, /*                     */ "r4"),
	REG(ARM_REGISTER_R5, /*                     */ "r5"),
	REG(ARM_REGISTER_R6, /*                     */ "r6"),
	REG(ARM_REGISTER_R7, /*                     */ "r7"),
	REG(ARM_REGISTER_R8, /*                     */ "r8"),
	REG(ARM_REGISTER_R9, /*                     */ "r9"),
	REG(ARM_REGISTER_R10, /*                    */ "r10"),
	REG(ARM_REGISTER_R11, /*                    */ "r11"),
	REG(ARM_REGISTER_R12, /*                    */ "r12"),
//	REG(ARM_REGISTER_SP, /*                     */ "sp"),
	REG(ARM_REGISTER_LR, /*                     */ "lr"),
//	REG(ARM_REGISTER_PC, /*                     */ "pc"),
	REG(ARM_REGISTER_R0, /*                     */ "r0"),
	REG(ARM_REGISTER_R8_USR, /*                 */ "r8_usr"),
	REG(ARM_REGISTER_R9_USR, /*                 */ "r9_usr"),
	REG(ARM_REGISTER_R10_USR, /*                */ "r10_usr"),
	REG(ARM_REGISTER_R11_USR, /*                */ "r11_usr"),
	REG(ARM_REGISTER_R12_USR, /*                */ "r12_usr"),
	REG(ARM_REGISTER_SP_USR, /*                 */ "sp_usr"),
	REG(ARM_REGISTER_LR_USR, /*                 */ "lr_usr"),
	REG(ARM_REGISTER_R8_FIQ, /*                 */ "r8_fiq"),
	REG(ARM_REGISTER_R9_FIQ, /*                 */ "r9_fiq"),
	REG(ARM_REGISTER_R10_FIQ, /*                */ "r10_fiq"),
	REG(ARM_REGISTER_R11_FIQ, /*                */ "r11_fiq"),
	REG(ARM_REGISTER_R12_FIQ, /*                */ "r12_fiq"),
	REG(ARM_REGISTER_SP_FIQ, /*                 */ "sp_fiq"),
	REG(ARM_REGISTER_LR_FIQ, /*                 */ "lr_fiq"),
	REG(ARM_REGISTER_SP_IRQ, /*                 */ "sp_irq"),
	REG(ARM_REGISTER_LR_IRQ, /*                 */ "lr_irq"),
	REG(ARM_REGISTER_SP_SVC, /*                 */ "sp_svc"),
	REG(ARM_REGISTER_LR_SVC, /*                 */ "lr_svc"),
	REG(ARM_REGISTER_SP_ABT, /*                 */ "sp_abt"),
	REG(ARM_REGISTER_LR_ABT, /*                 */ "lr_abt"),
	REG(ARM_REGISTER_SP_UND, /*                 */ "sp_und"),
	REG(ARM_REGISTER_LR_UND, /*                 */ "lr_und"),
	REG(ARM_REGISTER_CPSR, /*                   */ "cpsr"),
	REG(ARM_REGISTER_SPSR, /*                   */ "spsr"),
	REG(ARM_REGISTER_SPSR_FIQ, /*               */ "spsr_fiq"),
	REG(ARM_REGISTER_SPSR_IRQ, /*               */ "spsr_irq"),
	REG(ARM_REGISTER_SPSR_SVC, /*               */ "spsr_svc"),
	REG(ARM_REGISTER_SPSR_ABT, /*               */ "spsr_abt"),
	REG(ARM_REGISTER_SPSR_UND, /*               */ "spsr_und"),
	REG(ARM_REGISTER_TLSBASE, /*                */ "tlsbase"),
#else /* ... */
#error "Unsupported architecture"
#endif /* !... */
#undef REG
};


/* Return an arch-specific register constant, given its name
 * @param: isa: Instruction-set-assembly to which the given name belongs
 * @return: CPU_REGISTER_NONE: No such register. */
INTERN WUNUSED ATTR_PURE NONNULL((2)) cpu_regno_t
NOTHROW_NCX(CC libcpu_register_byname)(isa_t isa,
                                       char const *__restrict name,
                                       size_t namelen) {
	size_t i;
	(void)isa;
	for (i = 0; i < lengthof(register_db); ++i) {
		struct register_db_entry const *entry = &register_db[i];
		if (strlen(entry->rde_name) != namelen)
			continue;
		if (memcasecmp(entry->rde_name, name, namelen) == 0) {
			/* Found it! */
			return register_db_entry_getregno(entry, isa);
		}
	}
	return CPU_REGISTER_NONE;
}


/* Enumerate all register names that are accepted by `register_byname'
 * @return: >= 0: Sum of return values of `cb'
 * @return: <  0: First negative return value of `cb' (enumerate was aborted) */
INTERN NONNULL((1)) ssize_t
NOTHROW_NCX(CC libcpu_register_listnames)(pregister_listnames_callback_t cb,
                                          void *cookie) {
	size_t i;
	ssize_t temp, result = 0;
	for (i = 0; i < lengthof(register_db); ++i) {
		char const *name = register_db[i].rde_name;
		size_t namelen   = strlen(name);
		temp = (*cb)(cookie, name, namelen);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	return result;
err:
	return temp;
}



/* Return the size of a given CPU register (in bytes) */
INTERN WUNUSED ATTR_CONST size_t
NOTHROW_NCX(CC libcpu_register_sizeof)(cpu_regno_t regno) {
#if defined(__i386__) || defined(__x86_64__)
	return X86_REGISTER_SIZEOF(regno);
#else /* ... */
	(void)regno;
	return sizeof(void *);
#endif /* !... */
}

/* Return the flags of a given CPU register */
INTERN WUNUSED ATTR_CONST cpu_regno_flags_t
NOTHROW_NCX(CC libcpu_register_flags)(cpu_regno_t regno) {
	cpu_regno_flags_t result = CPU_REGNO_F_NORMAL;
#if defined(__i386__) || defined(__x86_64__)
	if ((regno & X86_REGISTER_CLASSMASK) == X86_REGISTER_FLOAT ||
	    (regno & X86_REGISTER_CLASSMASK) == X86_REGISTER_MMX ||
	    (regno & X86_REGISTER_CLASSMASK) == X86_REGISTER_XMM ||
	    (regno & X86_REGISTER_CLASSMASK) == X86_REGISTER_YMM) {
		result |= CPU_REGNO_F_FPUREG;
	} else if ((regno & X86_REGISTER_CLASSMASK) == X86_REGISTER_MISC) {
		if (((regno & X86_REGISTER_IDMASK) == (X86_REGISTER_MISC_FSW & X86_REGISTER_IDMASK)) ||
		    ((regno & X86_REGISTER_IDMASK) == (X86_REGISTER_MISC_FTW & X86_REGISTER_IDMASK)) ||
		    ((regno & X86_REGISTER_IDMASK) == (X86_REGISTER_MISC_FTWX & X86_REGISTER_IDMASK)) ||
		    ((regno & X86_REGISTER_IDMASK) == (X86_REGISTER_MISC_FOP & X86_REGISTER_IDMASK)) ||
		    ((regno & X86_REGISTER_IDMASK) == (X86_REGISTER_MISC_FIPL & X86_REGISTER_IDMASK)) ||
		    ((regno & X86_REGISTER_IDMASK) == (X86_REGISTER_MISC_FCS & X86_REGISTER_IDMASK)) ||
		    ((regno & X86_REGISTER_IDMASK) == (X86_REGISTER_MISC_FDPL & X86_REGISTER_IDMASK)) ||
		    ((regno & X86_REGISTER_IDMASK) == (X86_REGISTER_MISC_FDS & X86_REGISTER_IDMASK)) ||
		    ((regno & X86_REGISTER_IDMASK) == (X86_REGISTER_MISC_MXCSR & X86_REGISTER_IDMASK)) ||
		    ((regno & X86_REGISTER_IDMASK) == (X86_REGISTER_MISC_MXCSR_MASK & X86_REGISTER_IDMASK))) {
			result |= CPU_REGNO_F_FPUREG;
		}
	}
#else /* ... */
	(void)regno;
#endif /* !... */
	return result;
}



/* Exports */
DEFINE_PUBLIC_ALIAS(register_sizeof, libcpu_register_sizeof);
DEFINE_PUBLIC_ALIAS(register_flags, libcpu_register_flags);
DEFINE_PUBLIC_ALIAS(register_byname, libcpu_register_byname);
DEFINE_PUBLIC_ALIAS(register_listnames, libcpu_register_listnames);

DECL_END

#endif /* !GUARD_LIBCPUSTATE_REGISTER_C */
