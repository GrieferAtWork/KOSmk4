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
#ifndef GUARD_LIBREGDUMP_ARCH_I386_REGISTER_C
#define GUARD_LIBREGDUMP_ARCH_I386_REGISTER_C 1
#define _KOS_SOURCE 1

#include "../../api.h"
/**/

#include <hybrid/compiler.h>

#include <asm/registers.h>
#include <kos/types.h>

#include <assert.h>
#include <format-printer.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <libregdump/register.h>

#include "register.h"

DECL_BEGIN

struct gp_register_name {
#ifdef __x86_64__
#define GP_REGISTER_NAME_MAXLEN 4
	char grn_b[5]; /* al, cl, ..., r15l */
	char grn_w[5]; /* ax, cx, ..., r15w */
	char grn_l[5]; /* eax, ecx, ..., r15d */
	char grn_q[4]; /* rax, rcx, ..., r15 */
#define GP_REGISTER_NAME_INIT(b, w, l, q) { b, w, l, q }
#else /* __x86_64__ */
#define GP_REGISTER_NAME_MAXLEN 3
	char grn_b[3]; /* al, cl, ..., bh */
	char grn_w[3]; /* ax, cx, ..., di */
	char grn_l[4]; /* eax, ecx, ..., edi */
#define GP_REGISTER_NAME_INIT(b, w, l, q) { b, w, l }
#endif /* !__x86_64__ */
};

PRIVATE uint8_t const gp_register_name_offsets[] = {
	offsetof(struct gp_register_name, grn_b),
	offsetof(struct gp_register_name, grn_w),
	offsetof(struct gp_register_name, grn_l),
#ifdef __x86_64__
	offsetof(struct gp_register_name, grn_q),
#endif /* __x86_64__ */
};

PRIVATE struct gp_register_name const gpreg_names[] = {
	[(X86_REGISTER_GENERAL_PURPOSE_AX & X86_REGISTER_IDMASK)] = GP_REGISTER_NAME_INIT("al", "ax", "eax", "rax"),
	[(X86_REGISTER_GENERAL_PURPOSE_CX & X86_REGISTER_IDMASK)] = GP_REGISTER_NAME_INIT("cl", "cx", "ecx", "rcx"),
	[(X86_REGISTER_GENERAL_PURPOSE_DX & X86_REGISTER_IDMASK)] = GP_REGISTER_NAME_INIT("dl", "dx", "edx", "rdx"),
	[(X86_REGISTER_GENERAL_PURPOSE_BX & X86_REGISTER_IDMASK)] = GP_REGISTER_NAME_INIT("bl", "bx", "ebx", "rbx"),
	[(X86_REGISTER_GENERAL_PURPOSE_SP & X86_REGISTER_IDMASK)] = GP_REGISTER_NAME_INIT("ah", "sp", "esp", "rsp"),
	[(X86_REGISTER_GENERAL_PURPOSE_BP & X86_REGISTER_IDMASK)] = GP_REGISTER_NAME_INIT("ch", "bp", "ebp", "rbp"),
	[(X86_REGISTER_GENERAL_PURPOSE_SI & X86_REGISTER_IDMASK)] = GP_REGISTER_NAME_INIT("dh", "si", "esi", "rsi"),
	[(X86_REGISTER_GENERAL_PURPOSE_DI & X86_REGISTER_IDMASK)] = GP_REGISTER_NAME_INIT("bh", "di", "edi", "rdi"),
#ifdef __x86_64__
	[(X86_REGISTER_GENERAL_PURPOSE_R8 & X86_REGISTER_IDMASK)]  = GP_REGISTER_NAME_INIT("r8l", "r8w", "r8d", "r8"),
	[(X86_REGISTER_GENERAL_PURPOSE_R9 & X86_REGISTER_IDMASK)]  = GP_REGISTER_NAME_INIT("r9l", "r9w", "r9d", "r9"),
	[(X86_REGISTER_GENERAL_PURPOSE_R10 & X86_REGISTER_IDMASK)] = GP_REGISTER_NAME_INIT("r10l", "r10w", "r10d", "r10"),
	[(X86_REGISTER_GENERAL_PURPOSE_R11 & X86_REGISTER_IDMASK)] = GP_REGISTER_NAME_INIT("r11l", "r11w", "r11d", "r11"),
	[(X86_REGISTER_GENERAL_PURPOSE_R12 & X86_REGISTER_IDMASK)] = GP_REGISTER_NAME_INIT("r12l", "r12w", "r12d", "r12"),
	[(X86_REGISTER_GENERAL_PURPOSE_R13 & X86_REGISTER_IDMASK)] = GP_REGISTER_NAME_INIT("r13l", "r13w", "r13d", "r13"),
	[(X86_REGISTER_GENERAL_PURPOSE_R14 & X86_REGISTER_IDMASK)] = GP_REGISTER_NAME_INIT("r14l", "r14w", "r14d", "r14"),
	[(X86_REGISTER_GENERAL_PURPOSE_R15 & X86_REGISTER_IDMASK)] = GP_REGISTER_NAME_INIT("r15l", "r15w", "r15d", "r15"),
#endif /* __x86_64__ */
};


PRIVATE char const sgreg_names[][4] = {
	[(X86_REGISTER_SEGMENT_ES & X86_REGISTER_IDMASK)] = "%es",
	[(X86_REGISTER_SEGMENT_CS & X86_REGISTER_IDMASK)] = "%cs",
	[(X86_REGISTER_SEGMENT_SS & X86_REGISTER_IDMASK)] = "%ss",
	[(X86_REGISTER_SEGMENT_DS & X86_REGISTER_IDMASK)] = "%ds",
	[(X86_REGISTER_SEGMENT_FS & X86_REGISTER_IDMASK)] = "%fs",
	[(X86_REGISTER_SEGMENT_GS & X86_REGISTER_IDMASK)] = "%gs",
};


#define NUMBERED_CLASS_INDEXOF(regno)                                   \
	((((regno) & X86_REGISTER_CLASSMASK) >> _X86_REGISTER_CLASSSHIFT) - \
	 (X86_REGISTER_SEGMENT >> _X86_REGISTER_CLASSSHIFT))
PRIVATE char const numbered_register_prefixes[][4] = {
	[NUMBERED_CLASS_INDEXOF(X86_REGISTER_SEGMENT)] = { '%', 's', 0, 0 },
	[NUMBERED_CLASS_INDEXOF(X86_REGISTER_CONTROL)] = { '%', 'c', 'r', 0 },
	[NUMBERED_CLASS_INDEXOF(X86_REGISTER_FLOAT)]   = { '%', 's', 't', '(' },
	[NUMBERED_CLASS_INDEXOF(X86_REGISTER_MMX)]     = { '%', 'm', 'm', 0 },
	[NUMBERED_CLASS_INDEXOF(X86_REGISTER_XMM)]     = { '%', 'x', 'm', 'm' },
	[NUMBERED_CLASS_INDEXOF(X86_REGISTER_YMM)]     = { '%', 'y', 'm', 'm' },
	[NUMBERED_CLASS_INDEXOF(X86_REGISTER_DEBUG)]   = { '%', 'd', 'r', 0 },
};

static_assert(X86_REGISTER_SIZEOF_SHIFT(X86_REGISTER_SIZEMASK_1BYTE) == 0);
static_assert(X86_REGISTER_SIZEOF_SHIFT(X86_REGISTER_SIZEMASK_2BYTE) == 1);
static_assert(X86_REGISTER_SIZEOF_SHIFT(X86_REGISTER_SIZEMASK_4BYTE) == 2);
static_assert(X86_REGISTER_SIZEOF_SHIFT(X86_REGISTER_SIZEMASK_8BYTE) == 3);
static_assert(X86_REGISTER_SIZEOF(X86_REGISTER_SIZEMASK_1BYTE) == 1);
static_assert(X86_REGISTER_SIZEOF(X86_REGISTER_SIZEMASK_2BYTE) == 2);
static_assert(X86_REGISTER_SIZEOF(X86_REGISTER_SIZEMASK_4BYTE) == 4);
static_assert(X86_REGISTER_SIZEOF(X86_REGISTER_SIZEMASK_8BYTE) == 8);




/* Print the name of a system register `regno', as it appears
 * in `E_ILLEGAL_INSTRUCTION_REGISTER' exceptions, or defined
 * in  <asm/registers.h>. When `regno'  is unknown, its value
 * is printed in a generic manner.
 * @param: printer: Output printer
 * @param: arg:     Cookie for `printer'
 * @param: regno:   One of the constants from <asm/registers.h>
 * @return: * : pformatprinter-compatible return value. */
INTERN NONNULL((1)) ssize_t CC
libregdump_register_name(pformatprinter printer, void *arg,
                         uintptr_t regno) {
	ssize_t result;
	switch (regno & X86_REGISTER_CLASSMASK) {

	case X86_REGISTER_GENERAL_PURPOSE: {
		size_t len;
		char regname_with_percent[GP_REGISTER_NAME_MAXLEN + 2];
		char const *regname;
		unsigned int id = regno & X86_REGISTER_IDMASK;
		if unlikely(id >= lengthof(gpreg_names)) {
#ifdef __x86_64__
			if (regno >= X86_REGISTER_GENERAL_PURPOSE_SPL &&
			    regno <= X86_REGISTER_GENERAL_PURPOSE_DIL) {
				/* Special case: low byte of pointer register */
				static char const bpointer_names[4][4] = {
					[(X86_REGISTER_GENERAL_PURPOSE_SPL - X86_REGISTER_GENERAL_PURPOSE_SPL)] = "spl",
					[(X86_REGISTER_GENERAL_PURPOSE_BPL - X86_REGISTER_GENERAL_PURPOSE_SPL)] = "bpl",
					[(X86_REGISTER_GENERAL_PURPOSE_SIL - X86_REGISTER_GENERAL_PURPOSE_SPL)] = "sil",
					[(X86_REGISTER_GENERAL_PURPOSE_DIL - X86_REGISTER_GENERAL_PURPOSE_SPL)] = "dil",
				};
				regname = bpointer_names[regno - X86_REGISTER_GENERAL_PURPOSE_SPL];
			} else
#endif /* __x86_64__ */
			{
				goto fallback;
			}
		} else {
			unsigned int shft;
			struct gp_register_name const *set;
			set     = &gpreg_names[id];
			shft    = X86_REGISTER_SIZEOF_SHIFT(regno);
#ifndef __x86_64__
			if (shft == 3) /* Don't have 64-bit registers */
				goto fallback;
#endif /* !__x86_64__ */
			regname = (char const *)((byte_t const *)set + gp_register_name_offsets[shft]);
		}
		regname_with_percent[0] = '%';
		len = (size_t)(stpcpy(regname_with_percent + 1, regname) - regname_with_percent);
		result = (*printer)(arg, regname_with_percent, len);
	}	break;

	case X86_REGISTER_SEGMENT:
		if ((regno & X86_REGISTER_IDMASK) <= lengthof(sgreg_names)) {
			result = (*printer)(arg, sgreg_names[regno & X86_REGISTER_IDMASK], 3);
			break;
		}
		ATTR_FALLTHROUGH
	case X86_REGISTER_CONTROL:
	case X86_REGISTER_DEBUG:
#ifndef __x86_64__
		if ((regno & X86_REGISTER_SIZEMASK) != X86_REGISTER_SIZEMASK_4BYTE)
			goto fallback;
#endif /* !__x86_64__ */
		ATTR_FALLTHROUGH
	case X86_REGISTER_FLOAT:
	case X86_REGISTER_MMX:
	case X86_REGISTER_XMM:
	case X86_REGISTER_YMM: {
		static_assert(X86_REGISTER_IDMASK == 1023);
		char regname[COMPILER_STRLEN(numbered_register_prefixes[0]) +
		             COMPILER_STRLEN("1023") + 2];
		char const *prefix;
		size_t len;

		if ((regno & X86_REGISTER_SIZEMASK) != 0) {
#ifndef __x86_64__
			if (((regno & X86_REGISTER_CLASSMASK) == X86_REGISTER_CONTROL ||
			     (regno & X86_REGISTER_CLASSMASK) == X86_REGISTER_DEBUG) &&
			    (regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_PTR) {
				/* Allowed */
			} else
#endif /* !__x86_64__ */
			if ((regno & X86_REGISTER_CLASSMASK) == X86_REGISTER_SEGMENT &&
			    (regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_2BYTE) {
				/* Allowed */
			} else {
				goto fallback;
			}
		}

		/* Print the register name */
		prefix = numbered_register_prefixes[NUMBERED_CLASS_INDEXOF(regno)];
		len    = sprintf(regname, "%4s%u", prefix, regno & X86_REGISTER_IDMASK);
		if (prefix[COMPILER_STRLEN(numbered_register_prefixes[0]) - 1] == '(')
			regname[len++] = ')';
		result = (*printer)(arg, regname, len);
	}	break;

	case X86_REGISTER_MISC: {
		char const *fixed_name;
		char regname[32], *ptr = regname;
#define MISC(x) ((x) & ~(X86_REGISTER_CLASSMASK))
		*ptr++ = '%';
		switch (MISC(regno)) {

		case MISC(X86_REGISTER_MISC_IP):
		case MISC(X86_REGISTER_MISC_EIP):
		case MISC(X86_REGISTER_MISC_FLAGS):
		case MISC(X86_REGISTER_MISC_EFLAGS):
#ifdef __x86_64__
		case MISC(X86_REGISTER_MISC_RIP):
		case MISC(X86_REGISTER_MISC_RFLAGS):
#endif /* __x86_64__ */
		{
#ifdef __x86_64__
			static char const sz_prefix[][2] = { "", "e", "r" };
#else /* __x86_64__ */
			static char const sz_prefix[][2] = { "", "e" };
#endif /* !__x86_64__ */
			unsigned int sz_shft;
			sz_shft = X86_REGISTER_SIZEOF_SHIFT(regno);
			ptr     = stpcpy(ptr, sz_prefix[sz_shft - 1]);
			if ((regno & X86_REGISTER_IDMASK) == (X86_REGISTER_MISC_IP & X86_REGISTER_IDMASK)) {
				ptr = stpcpy(ptr, "ip");
			} else {
				ptr = stpcpy(ptr, "flags");
			}
		}	break;

		case X86_REGISTER_MISC_TR:
			fixed_name = "%tr";
do_fixed_name:
			result = (*printer)(arg, fixed_name, strlen(fixed_name));
			goto done;

#define FIXED_NAME_CASE(id, name) case MISC(id): fixed_name = name; goto do_fixed_name
		FIXED_NAME_CASE(X86_REGISTER_MISC_LDT, "%ldt");
		FIXED_NAME_CASE(X86_REGISTER_MISC_GDT_LIMIT, "%gdt.limit");
		FIXED_NAME_CASE(X86_REGISTER_MISC_IDT_LIMIT, "%idt.limit");
		FIXED_NAME_CASE(X86_REGISTER_MISC_GDT_BASEL, "%gdt.basel");
		FIXED_NAME_CASE(X86_REGISTER_MISC_IDT_BASEL, "%idt.basel");
#ifdef __x86_64__
		FIXED_NAME_CASE(X86_REGISTER_MISC_GDT_BASEQ, "%gdt.baseq");
		FIXED_NAME_CASE(X86_REGISTER_MISC_IDT_BASEQ, "%idt.baseq");
#endif /* __x86_64__ */
		FIXED_NAME_CASE(X86_REGISTER_MISC_FSBASEL, "%fs.basel");
		FIXED_NAME_CASE(X86_REGISTER_MISC_GSBASEL, "%gs.basel");
#ifdef __x86_64__
		FIXED_NAME_CASE(X86_REGISTER_MISC_FSBASEQ, "%fs.baseq");
		FIXED_NAME_CASE(X86_REGISTER_MISC_GSBASEQ, "%gs.baseq");
		FIXED_NAME_CASE(X86_REGISTER_MISC_KGSBASEL, "%kernel_gs.basel");
		FIXED_NAME_CASE(X86_REGISTER_MISC_KGSBASEQ, "%kernel_gs.baseq");
#endif /* __x86_64__ */
		FIXED_NAME_CASE(X86_REGISTER_MISC_FCW, "%fcw");
		FIXED_NAME_CASE(X86_REGISTER_MISC_FSW, "%fsw");
		FIXED_NAME_CASE(X86_REGISTER_MISC_FTW, "%ftw");
		FIXED_NAME_CASE(X86_REGISTER_MISC_FTWX, "%ftwx");
		FIXED_NAME_CASE(X86_REGISTER_MISC_FOP, "%fop");
		FIXED_NAME_CASE(X86_REGISTER_MISC_FIPL, "%fipl");
		FIXED_NAME_CASE(X86_REGISTER_MISC_FCS, "%fcs");
		FIXED_NAME_CASE(X86_REGISTER_MISC_FDPL, "%fdpl");
		FIXED_NAME_CASE(X86_REGISTER_MISC_FDS, "%fds");
#ifdef __x86_64__
		FIXED_NAME_CASE(X86_REGISTER_MISC_FIPQ, "%fipq");
		FIXED_NAME_CASE(X86_REGISTER_MISC_FDPQ, "%fdpq");
#endif /* __x86_64__ */
		FIXED_NAME_CASE(X86_REGISTER_MISC_MXCSR, "%mxcsr");
		FIXED_NAME_CASE(X86_REGISTER_MISC_MXCSR_MASK, "%mxcsr_mask");
		FIXED_NAME_CASE(X86_REGISTER_MISC_MWAIT, "mwait:%ecx");
		FIXED_NAME_CASE(X86_REGISTER_MISC_MONITOR, "monitor:%ecx");
		FIXED_NAME_CASE(X86_REGISTER_MISC_TPAUSE, "tpause:operand");
		FIXED_NAME_CASE(X86_REGISTER_MISC_ENCLS, "encls:%eax");
		FIXED_NAME_CASE(X86_REGISTER_MISC_ENCLU, "enclu:%eax");
		FIXED_NAME_CASE(X86_REGISTER_MISC_GI, "GlobalInterrupt");
#undef FIXED_NAME_CASE

		default:
			goto fallback;
		}
#undef MISC
		result = (*printer)(arg, regname, (size_t)(ptr - regname));
	}	break;

	default:
		/* Fallback: print a generic register name. */
fallback:
		result = format_printf(printer, arg, "reg.%#" PRIxPTR, regno);
		break;
	}
done:
	return result;
}


DEFINE_PUBLIC_ALIAS(regdump_register_name, libregdump_register_name);

DECL_END

#endif /* !GUARD_LIBREGDUMP_ARCH_I386_REGISTER_C */
