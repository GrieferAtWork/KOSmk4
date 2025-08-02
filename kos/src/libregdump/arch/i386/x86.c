/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBREGDUMP_ARCH_I386_X86_C
#define GUARD_LIBREGDUMP_ARCH_I386_X86_C 1
#define DISABLE_BRANCH_PROFILING
#define _KOS_SOURCE 1
#define _KOS_KERNEL_SOURCE 1

#include "../../api.h"
/**/

#include <hybrid/compiler.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <kos/except.h>
#include <kos/exec/module.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/x86/gdt.h>
#include <kos/types.h>

#include <atomic.h>
#include <format-printer.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <libdebuginfo/addr2line.h>
#include <libdisasm/disassembler.h>
#include <libinstrlen/instrlen.h>
#include <libregdump/x86.h>

#include "x86.h"

#ifdef __KERNEL__
#include <kernel/x86/gdt.h>
#else /* __KERNEL__ */
#include <dlfcn.h>
#endif /* !__KERNEL__ */


DECL_BEGIN

#define BEGIN      \
	ssize_t temp, result = 0
#define END        \
	return result; \
err:               \
	return temp


#define DO(...)               do{if unlikely((temp = __VA_ARGS__) < 0)goto err;result+=temp;}__WHILE0
#define print(str, len)       DO((*self->rdp_printer)(self->rdp_printer_arg, str, len))
#define printf(...)           DO(format_printf(self->rdp_printer, self->rdp_printer_arg, __VA_ARGS__))
#define PRINT(str)            print(str, COMPILER_STRLEN(str))
#define format(format_option) DO(regdump_printer_format(self, format_option))

#ifdef __x86_64__
#define RPF  "r" /* RegisterPreFix */
#else /* __x86_64__ */
#define RPF  "e" /* RegisterPreFix */
#endif /* !__x86_64__ */

#ifdef __x86_64__
#define GPREGS_COUNT 16
#if 1
#define GPREGS_LEN(id) 2
#else
#define GPREGS_LEN(id) ((id) >= 8 && (id) <= 9 ? 1 : 2)
#endif
#define GPREGS_MAXLEN  2
#define GPREGS_FIRSTCH 'r'
PRIVATE char const gpregs_names[GPREGS_COUNT][2] = {
	{ '1', '5' },
	{ '1', '4' },
	{ '1', '3' },
	{ '1', '2' },
	{ '1', '1' },
	{ '1', '0' },
	{ '9', ' ' },
	{ '8', ' ' },
	{ 'd', 'i' },
	{ 's', 'i' },
	{ 'b', 'p' },
	{ 's', 'p' },
	{ 'b', 'x' },
	{ 'd', 'x' },
	{ 'c', 'x' },
	{ 'a', 'x' },
};
#else /* __x86_64__ */
#define GPREGS_COUNT 8
#define GPREGS_LEN(id) 2
#define GPREGS_MAXLEN  2
#define GPREGS_FIRSTCH 'e'
PRIVATE char const gpregs_names[GPREGS_COUNT][2] = {
	{ 'd', 'i' },
	{ 's', 'i' },
	{ 'b', 'p' },
	{ 's', 'p' },
	{ 'b', 'x' },
	{ 'd', 'x' },
	{ 'c', 'x' },
	{ 'a', 'x' }
};
#endif /* !__x86_64__ */

#ifdef __x86_64__
#define GPREGS_PER_LINE 2
INTERN NONNULL((1, 2)) ssize_t CC
libregdump_gpregs_with_sp(struct regdump_printer *__restrict self,
                          struct gpregsnsp const *__restrict data,
                          uintptr_t sp)
#else /* __x86_64__ */
#define GPREGS_PER_LINE 4
INTERN NONNULL((1, 2)) ssize_t CC
libregdump_gpregs_with_sp(struct regdump_printer *__restrict self,
                          struct gpregs const *__restrict data,
                          uintptr_t sp)
#endif /* !__x86_64__ */
{
	unsigned int i;
	BEGIN;
	format(REGDUMP_FORMAT_INDENT);
	for (i = 0; i < GPREGS_COUNT; ++i) {
		char name[2 + GPREGS_MAXLEN];
		name[0] = '%';
		name[1] = GPREGS_FIRSTCH;
		memcpy(name + 2, gpregs_names[i], GPREGS_MAXLEN, sizeof(char));
		format(REGDUMP_FORMAT_REGISTER_PREFIX);
		print(name, 2 + GPREGS_LEN(i));
		format(REGDUMP_FORMAT_REGISTER_SUFFIX);
		PRINT(" ");
		format(REGDUMP_FORMAT_VALUE_PREFIX);
#ifdef __x86_64__
		{
			uintptr_t used_value;
			if (i == 10) {
				used_value = sp;
			} else if (i > 10) {
				used_value = ((uintptr_t *)data)[i - 1];
			} else {
				used_value = ((uintptr_t *)data)[i];
			}
			printf("%p", used_value);
		}
#else /* __x86_64__ */
		printf("%p", i == 3 ? sp : ((uintptr_t *)data)[i]);
#endif /* !__x86_64__ */
		format(REGDUMP_FORMAT_VALUE_SUFFIX);
		print((i % GPREGS_PER_LINE) == (GPREGS_PER_LINE - 1) ? "\n" : " ", 1);
		if ((i % GPREGS_PER_LINE) == (GPREGS_PER_LINE - 1) && i != GPREGS_COUNT - 1)
			format(REGDUMP_FORMAT_INDENT);
	}
	END;
}

/* Print a general-purpose register (id is one of { a, c, d, b, S, D, B, P } (same as gcc inline assembly register constraints, with B for %ebp and P for %esp))
 * On x86_64, use `0-7' to indicate extended registers `r8-r15' */
INTERN NONNULL((1)) ssize_t CC
libregdump_gpreg(struct regdump_printer *__restrict self,
                 char id, uintptr_t value) {
	char name[4];
	BEGIN;
	format(REGDUMP_FORMAT_REGISTER_PREFIX);
	name[0] = '%';
	name[1] = GPREGS_FIRSTCH;
#ifdef __x86_64__
	if (id >= '0' && id <= '7') {
		if (id <= '1') {
			name[2] = itoa_decimal(8 + (id - '1'));
		} else {
			name[2] = itoa_decimal(1 + (id - '1'));
			name[3] = itoa_decimal(id - '2');
		}
		print(name, id <= 1 ? 3 : 4);
	} else
#endif /* __x86_64__ */
	{
		if (id == 'S' || id == 'D') {
			name[2] = 'a' + (id - 'A');
			name[3] = 'i';
		} else if (id == 'B') {
			name[2] = 'b';
			name[3] = 'p';
		} else if (id == 'P') {
			name[2] = 's';
			name[3] = 'p';
		} else {
			name[2] = id;
			name[3] = 'x';
		}
		print(name, 4);
	}
	format(REGDUMP_FORMAT_REGISTER_SUFFIX);
	PRINT(" ");
	format(REGDUMP_FORMAT_VALUE_PREFIX);
	printf("%p", value);
	format(REGDUMP_FORMAT_VALUE_SUFFIX);
	END;
}

INTERN NONNULL((1, 2)) ssize_t CC
libregdump_gpregs(struct regdump_printer *__restrict self,
                  struct gpregs const *__restrict data) {
#ifdef __x86_64__
	struct gpregsnsp nsp;
	nsp.gp_r15 = data->gp_r15;
	nsp.gp_r14 = data->gp_r14;
	nsp.gp_r13 = data->gp_r13;
	nsp.gp_r12 = data->gp_r12;
	nsp.gp_r11 = data->gp_r11;
	nsp.gp_r10 = data->gp_r10;
	nsp.gp_r9  = data->gp_r9;
	nsp.gp_r8  = data->gp_r8;
	nsp.gp_rdi = data->gp_rdi;
	nsp.gp_rsi = data->gp_rsi;
	nsp.gp_rbp = data->gp_rbp;
	nsp.gp_rbx = data->gp_rbx;
	nsp.gp_rdx = data->gp_rdx;
	nsp.gp_rcx = data->gp_rcx;
	nsp.gp_rax = data->gp_rax;
	return libregdump_gpregs_with_sp(self, &nsp, data->gp_rsp);
#else /* __x86_64__ */
	return libregdump_gpregs_with_sp(self, data, data->gp_esp);
#endif /* !__x86_64__ */
}

PRIVATE ATTR_CONST WUNUSED char const *
NOTHROW(CC get_segment_value_name)(uint16_t seg) {
	char const *result = NULL;
	switch (seg & ~3) {
#define CASE(x) \
	case SEGMENT_##x: \
		result = #x;  \
		break
	CASE(KERNEL_CODE);
	CASE(KERNEL_DATA);
	CASE(USER_CODE);
	CASE(USER_DATA);
	CASE(CPU_LDT);
	CASE(CPU_TSS);
	CASE(USER_FSBASE);
	CASE(USER_GSBASE);
#ifdef __x86_64__
	CASE(CPU_LDT2);
	CASE(CPU_TSS2);
	CASE(USER_CODE32);
	CASE(USER_DATA32);
	CASE(KERNEL_CODE32);
	CASE(KERNEL_DATA32);
#else /* __x86_64__ */
	CASE(CPU_TSS_DF);
	CASE(KERNEL_FSBASE);
#endif /* !__x86_64__ */

#undef CASE
	default: break;
	}
	return result;
}


PRIVATE
#ifdef __KERNEL__
	NONNULL((1, 4, 5))
#else /* __KERNEL__ */
	NONNULL((1))
#endif /* !__KERNEL__ */
	ssize_t CC
libregdump_do_segment(struct regdump_printer *__restrict self,
                      char name, uint16_t value
#ifdef __KERNEL__
                      ,
                      struct desctab *__restrict gdt,
                      uint16_t *__restrict pldt
#endif /* __KERNEL__ */
                      ) {
#ifdef __KERNEL__
	struct desctab tab = *gdt;
	struct segment *seg;
#endif /* __KERNEL__ */
	BEGIN;
	format(REGDUMP_FORMAT_REGISTER_PREFIX);
	if (name == 'l') {
		PRINT("%ldt");
	} else if (name == 't') {
		PRINT("%tr");
	} else {
		char namebuf[3];
		namebuf[0] = '%';
		namebuf[1] = name;
		namebuf[2] = 's';
		print(namebuf, 3);
	}
	format(REGDUMP_FORMAT_REGISTER_SUFFIX);
	PRINT(" ");
	format(REGDUMP_FORMAT_VALUE_PREFIX);
	printf("%.4I16X", value);
	format(REGDUMP_FORMAT_VALUE_SUFFIX);
	if (value == 0) {
		PRINT(" -");
		goto done;
	}
	printf(" [%cdt+", (char)((value & 4) ? 'l' : 'g'));
	format(REGDUMP_FORMAT_OFFSET_PREFIX);
	printf("%#.2x", (unsigned int)(value & ~7));
	format(REGDUMP_FORMAT_OFFSET_SUFFIX);
	PRINT(",rpl=");
	format(REGDUMP_FORMAT_VALUE_PREFIX);
	printf("%u", (unsigned int)(value & 3));
	format(REGDUMP_FORMAT_VALUE_SUFFIX);
#ifdef __KERNEL__
	if (value & 4) {
		if (!*pldt)
			*pldt = __sldt();
		if ((uint16_t)(*pldt & ~7) >= (uint16_t)(tab.dt_limit + 1)) {
			PRINT("] ");
			format(REGDUMP_FORMAT_ERROR_PREFIX);
			printf("BAD: %%ldtr:%#.2x exceeds %%gdt.limit=%#.2x",
			       (unsigned int)*pldt,
			       (unsigned int)tab.dt_limit);
			format(REGDUMP_FORMAT_ERROR_SUFFIX);
			goto done;
		}
		seg = &((struct segment *)tab.dt_base)[SEGMENT_INDEX(*pldt)];
		if (!seg->s_descriptor.d_present) {
			PRINT("] ");
			format(REGDUMP_FORMAT_ERROR_PREFIX);
			printf("BAD: %%gdt[%%ldtr:%#.2x].present = 0",
			       (unsigned int)*pldt);
			format(REGDUMP_FORMAT_ERROR_SUFFIX);
			goto done;
		}
		if (seg->s_descriptor.d_type != SEGMENT_DESCRIPTOR_TYPE_LDT) {
			PRINT("] ");
			format(REGDUMP_FORMAT_ERROR_PREFIX);
			printf("BAD: %%gdt[%%ldtr:%#.2x].type = %#x (expected %x)",
			       (unsigned int)*pldt,
			       (unsigned int)seg->s_descriptor.d_type,
			       (unsigned int)SEGMENT_DESCRIPTOR_TYPE_LDT);
			format(REGDUMP_FORMAT_ERROR_SUFFIX);
			goto done;
		}
		tab.dt_base  = segment_rdbaseX(seg);
		tab.dt_limit = (uint16_t)segment_rdlimit(seg);
	}
	if ((uint16_t)(value & ~7) >= (uint16_t)(tab.dt_limit + 1)) {
		PRINT("] ");
		format(REGDUMP_FORMAT_ERROR_PREFIX);
		printf("BAD: exceeds %%%cdt.limit=%#.2x",
		       value & 4 ? 'l' : 'g', (unsigned int)tab.dt_limit);
		format(REGDUMP_FORMAT_ERROR_SUFFIX);
		goto done;
	}
	seg = &((struct segment *)tab.dt_base)[SEGMENT_INDEX(value)];
	PRINT(",dpl=");
	format(REGDUMP_FORMAT_VALUE_PREFIX);
	printf("%u", seg->s_descriptor.d_dpl);
	format(REGDUMP_FORMAT_VALUE_SUFFIX);
	PRINT(",");
	format(REGDUMP_FORMAT_VALUE_PREFIX);
	printf("%I32p", segment_rdbase(seg));
	format(REGDUMP_FORMAT_VALUE_SUFFIX);
	PRINT("+");
	format(REGDUMP_FORMAT_VALUE_PREFIX);
	printf("%#.8I32x", segment_rdlimit(seg));
	format(REGDUMP_FORMAT_VALUE_SUFFIX);
	PRINT(",");
	{
		char flags[5];
		format(REGDUMP_FORMAT_FLAG_PREFIX);
		flags[0] = seg->s_descriptor.d_code_or_data ? '-' : 's';
		flags[1] = seg->s_descriptor.d_type_bits.dtb_code ? 'x' : '-';
		flags[2] = seg->s_descriptor.d_type_bits.dtb_ec ? 'e' : 'c';
		flags[3] = seg->s_descriptor.d_type_bits.dtb_wr ? (seg->s_descriptor.d_type_bits.dtb_code ? 'r' : 'w') : '-';
		flags[4] = seg->s_descriptor.d_type_bits.dtb_accessed ? 'a' : '-';
		print(flags, 5);
		format(REGDUMP_FORMAT_FLAG_SUFFIX);
	}
#endif /* __KERNEL__ */
	PRINT("]");
	{
		char const *valuename;
		valuename = get_segment_value_name(value);
		if (valuename) {
			PRINT(" (");
			format(REGDUMP_FORMAT_VALUE_PREFIX);
			print(valuename, strlen(valuename));
			format(REGDUMP_FORMAT_VALUE_SUFFIX);
			if (value & 3) {
				PRINT("+");
				format(REGDUMP_FORMAT_OFFSET_PREFIX);
				printf("%u", (unsigned int)(value & 3));
				format(REGDUMP_FORMAT_OFFSET_SUFFIX);
			}
			PRINT(")");
		}
	}
done:
	END;
}

INTERN NONNULL((1)) ssize_t CC
libregdump_cr0(struct regdump_printer *__restrict self,
               uintptr_t cr0) {
	BEGIN;
	format(REGDUMP_FORMAT_REGISTER_PREFIX);
	PRINT("%cr0");
	format(REGDUMP_FORMAT_REGISTER_SUFFIX);
	PRINT(" ");
	format(REGDUMP_FORMAT_VALUE_PREFIX);
	printf("%p", cr0);
	format(REGDUMP_FORMAT_VALUE_SUFFIX);
	if (cr0 & (CR0_PE | CR0_MP | CR0_EM | CR0_TS | CR0_ET |
	           CR0_NE | CR0_WP | CR0_AM | CR0_NW | CR0_CD | CR0_PG)) {
		PRINT(" [");
		if (cr0 & CR0_PE) {
			format(REGDUMP_FORMAT_FLAG_PREFIX);
			PRINT("pe");
			format(REGDUMP_FORMAT_FLAG_SUFFIX);
		}
#define PRINT_FLAG(name, f, before) \
		if (cr0 & (f)) {                        \
			if (cr0 & (before))                 \
				PRINT(",");                     \
			format(REGDUMP_FORMAT_FLAG_PREFIX); \
			PRINT(name);                        \
			format(REGDUMP_FORMAT_FLAG_SUFFIX); \
		}
		PRINT_FLAG("mp", CR0_MP, CR0_PE)
		PRINT_FLAG("em", CR0_EM, CR0_PE | CR0_MP)
		PRINT_FLAG("ts", CR0_TS, CR0_PE | CR0_MP | CR0_EM)
		PRINT_FLAG("et", CR0_ET, CR0_PE | CR0_MP | CR0_EM | CR0_TS)
		PRINT_FLAG("ne", CR0_NE, CR0_PE | CR0_MP | CR0_EM | CR0_TS | CR0_ET)
		PRINT_FLAG("wp", CR0_WP, CR0_PE | CR0_MP | CR0_EM | CR0_TS | CR0_ET | CR0_NE)
		PRINT_FLAG("am", CR0_AM, CR0_PE | CR0_MP | CR0_EM | CR0_TS | CR0_ET | CR0_NE | CR0_WP)
		PRINT_FLAG("nw", CR0_NW, CR0_PE | CR0_MP | CR0_EM | CR0_TS | CR0_ET | CR0_NE | CR0_WP | CR0_AM)
		PRINT_FLAG("cd", CR0_CD, CR0_PE | CR0_MP | CR0_EM | CR0_TS | CR0_ET | CR0_NE | CR0_WP | CR0_AM | CR0_NW)
		PRINT_FLAG("pg", CR0_PG, CR0_PE | CR0_MP | CR0_EM | CR0_TS | CR0_ET | CR0_NE | CR0_WP | CR0_AM | CR0_NW | CR0_CD)
#undef PRINT_FLAG
		PRINT("]");
	}
	END;
}

INTERN NONNULL((1)) ssize_t CC
libregdump_cr4(struct regdump_printer *__restrict self,
               uintptr_t cr4) {
	BEGIN;
	format(REGDUMP_FORMAT_REGISTER_PREFIX);
	PRINT("%cr4");
	format(REGDUMP_FORMAT_REGISTER_SUFFIX);
	PRINT(" ");
	format(REGDUMP_FORMAT_VALUE_PREFIX);
	printf("%p", cr4);
	format(REGDUMP_FORMAT_VALUE_SUFFIX);
	if (cr4 & (CR4_VME | CR4_PVI | CR4_TSD | CR4_DE | CR4_PSE | CR4_PAE | CR4_MCE |
	           CR4_PGE | CR4_PCE | CR4_OSFXSR | CR4_OSXMMEXCPT | CR4_UMIP | CR4_VMXE |
	           CR4_SMXE | CR4_FSGSBASE | CR4_PCIDE | CR4_OSXSAVE | CR4_SMEP | CR4_SMAP)) {
		PRINT(" [");
		if (cr4 & CR4_VME) {
			format(REGDUMP_FORMAT_FLAG_PREFIX);
			PRINT("vme");
			format(REGDUMP_FORMAT_FLAG_SUFFIX);
		}
#define PRINT_FLAG(name, f, before) \
		if (cr4 & (f)) {                        \
			if (cr4 & (before))                 \
				PRINT(",");                     \
			format(REGDUMP_FORMAT_FLAG_PREFIX); \
			PRINT(name);                        \
			format(REGDUMP_FORMAT_FLAG_SUFFIX); \
		}
		PRINT_FLAG("pvi", CR4_PVI, CR4_VME)
		PRINT_FLAG("tsd", CR4_TSD, CR4_VME | CR4_PVI)
		PRINT_FLAG("de", CR4_DE, CR4_VME | CR4_PVI | CR4_TSD)
		PRINT_FLAG("pse", CR4_PSE, CR4_VME | CR4_PVI | CR4_TSD | CR4_DE)
		PRINT_FLAG("pae", CR4_PAE, CR4_VME | CR4_PVI | CR4_TSD | CR4_DE | CR4_PSE)
		PRINT_FLAG("mce", CR4_MCE, CR4_VME | CR4_PVI | CR4_TSD | CR4_DE | CR4_PSE | CR4_PAE)
		PRINT_FLAG("pge", CR4_PGE, CR4_VME | CR4_PVI | CR4_TSD | CR4_DE | CR4_PSE | CR4_PAE | CR4_MCE)
		PRINT_FLAG("pce", CR4_PCE, CR4_VME | CR4_PVI | CR4_TSD | CR4_DE | CR4_PSE | CR4_PAE | CR4_MCE | CR4_PGE)
		PRINT_FLAG("osfxsr", CR4_OSFXSR, CR4_VME | CR4_PVI | CR4_TSD | CR4_DE | CR4_PSE | CR4_PAE | CR4_MCE | CR4_PGE | CR4_PCE)
		PRINT_FLAG("osxmmexcpt", CR4_OSXMMEXCPT, CR4_VME | CR4_PVI | CR4_TSD | CR4_DE | CR4_PSE | CR4_PAE | CR4_MCE | CR4_PGE | CR4_PCE | CR4_OSFXSR)
		PRINT_FLAG("umip", CR4_UMIP, CR4_VME | CR4_PVI | CR4_TSD | CR4_DE | CR4_PSE | CR4_PAE | CR4_MCE | CR4_PGE | CR4_PCE | CR4_OSFXSR | CR4_OSXMMEXCPT)
		PRINT_FLAG("vmxe", CR4_VMXE, CR4_VME | CR4_PVI | CR4_TSD | CR4_DE | CR4_PSE | CR4_PAE | CR4_MCE | CR4_PGE | CR4_PCE | CR4_OSFXSR | CR4_OSXMMEXCPT | CR4_UMIP)
		PRINT_FLAG("smxe", CR4_SMXE, CR4_VME | CR4_PVI | CR4_TSD | CR4_DE | CR4_PSE | CR4_PAE | CR4_MCE | CR4_PGE | CR4_PCE | CR4_OSFXSR | CR4_OSXMMEXCPT | CR4_UMIP | CR4_VMXE)
		PRINT_FLAG("fsgsbase", CR4_FSGSBASE, CR4_VME | CR4_PVI | CR4_TSD | CR4_DE | CR4_PSE | CR4_PAE | CR4_MCE | CR4_PGE | CR4_PCE | CR4_OSFXSR | CR4_OSXMMEXCPT | CR4_UMIP | CR4_VMXE | CR4_SMXE)
		PRINT_FLAG("pcide", CR4_PCIDE, CR4_VME | CR4_PVI | CR4_TSD | CR4_DE | CR4_PSE | CR4_PAE | CR4_MCE | CR4_PGE | CR4_PCE | CR4_OSFXSR | CR4_OSXMMEXCPT | CR4_UMIP | CR4_VMXE | CR4_SMXE | CR4_FSGSBASE)
		PRINT_FLAG("osxsave", CR4_OSXSAVE, CR4_VME | CR4_PVI | CR4_TSD | CR4_DE | CR4_PSE | CR4_PAE | CR4_MCE | CR4_PGE | CR4_PCE | CR4_OSFXSR | CR4_OSXMMEXCPT | CR4_UMIP | CR4_VMXE | CR4_SMXE | CR4_FSGSBASE | CR4_PCIDE)
		PRINT_FLAG("smep", CR4_SMEP, CR4_VME | CR4_PVI | CR4_TSD | CR4_DE | CR4_PSE | CR4_PAE | CR4_MCE | CR4_PGE | CR4_PCE | CR4_OSFXSR | CR4_OSXMMEXCPT | CR4_UMIP | CR4_VMXE | CR4_SMXE | CR4_FSGSBASE | CR4_PCIDE | CR4_OSXSAVE)
		PRINT_FLAG("smap", CR4_SMAP, CR4_VME | CR4_PVI | CR4_TSD | CR4_DE | CR4_PSE | CR4_PAE | CR4_MCE | CR4_PGE | CR4_PCE | CR4_OSFXSR | CR4_OSXMMEXCPT | CR4_UMIP | CR4_VMXE | CR4_SMXE | CR4_FSGSBASE | CR4_PCIDE | CR4_OSXSAVE | CR4_SMEP)
		PRINT_FLAG("pke", CR4_PKE, CR4_VME | CR4_PVI | CR4_TSD | CR4_DE | CR4_PSE | CR4_PAE | CR4_MCE | CR4_PGE | CR4_PCE | CR4_OSFXSR | CR4_OSXMMEXCPT | CR4_UMIP | CR4_VMXE | CR4_SMXE | CR4_FSGSBASE | CR4_PCIDE | CR4_OSXSAVE | CR4_SMEP | CR4_SMAP)
#undef PRINT_FLAG
		PRINT("]");
	}
	END;
}

INTERN NONNULL((1)) ssize_t CC
libregdump_dr6(struct regdump_printer *__restrict self,
               uintptr_t dr6) {
	BEGIN;
	format(REGDUMP_FORMAT_REGISTER_PREFIX);
	PRINT("%dr6");
	format(REGDUMP_FORMAT_REGISTER_SUFFIX);
	PRINT(" ");
	format(REGDUMP_FORMAT_VALUE_PREFIX);
	printf("%p", dr6);
	format(REGDUMP_FORMAT_VALUE_SUFFIX);
	if (dr6 & (DR6_B0 | DR6_B1 | DR6_B2 | DR6_B3 |
	           DR6_BD | DR6_BS | DR6_BT | DR6_RTM)) {
		PRINT(" [");
		if (dr6 & DR6_B0) {
			format(REGDUMP_FORMAT_FLAG_PREFIX);
			PRINT("b0");
			format(REGDUMP_FORMAT_FLAG_SUFFIX);
		}
#define PRINT_FLAG(name, f, before) \
		if (dr6 & (f)) {                        \
			if (dr6 & (before))                 \
				PRINT(",");                     \
			format(REGDUMP_FORMAT_FLAG_PREFIX); \
			PRINT(name);                        \
			format(REGDUMP_FORMAT_FLAG_SUFFIX); \
		}
		PRINT_FLAG("b1", DR6_B1, DR6_B0)
		PRINT_FLAG("b2", DR6_B2, DR6_B0 | DR6_B1)
		PRINT_FLAG("b3", DR6_B3, DR6_B0 | DR6_B1 | DR6_B2)
		PRINT_FLAG("bd", DR6_BD, DR6_B0 | DR6_B1 | DR6_B2 | DR6_B3)
		PRINT_FLAG("bs", DR6_BS, DR6_B0 | DR6_B1 | DR6_B2 | DR6_B3 | DR6_BD)
		PRINT_FLAG("bt", DR6_BT, DR6_B0 | DR6_B1 | DR6_B2 | DR6_B3 | DR6_BD | DR6_BS)
		PRINT_FLAG("rtm", DR6_RTM, DR6_B0 | DR6_B1 | DR6_B2 | DR6_B3 | DR6_BD | DR6_BS | DR6_BT)
#undef PRINT_FLAG
		PRINT("]");
	}
	END;
}

INTERN NONNULL((1)) ssize_t CC
libregdump_dr7(struct regdump_printer *__restrict self,
               uintptr_t dr7) {
	BEGIN;
	format(REGDUMP_FORMAT_REGISTER_PREFIX);
	PRINT("%dr7");
	format(REGDUMP_FORMAT_REGISTER_SUFFIX);
	PRINT(" ");
	format(REGDUMP_FORMAT_VALUE_PREFIX);
	printf("%p", dr7);
	format(REGDUMP_FORMAT_VALUE_SUFFIX);
	if (dr7 & (DR7_LE | DR7_GE | DR7_RTM | DR7_GD)) {
		PRINT(" [");
		if (dr7 & DR7_LE) {
			format(REGDUMP_FORMAT_FLAG_PREFIX);
			PRINT("le");
			format(REGDUMP_FORMAT_FLAG_SUFFIX);
		}
#define PRINT_FLAG(name, f, before) \
		if (dr7 & (f)) {                        \
			if (dr7 & (before))                 \
				PRINT(",");                     \
			format(REGDUMP_FORMAT_FLAG_PREFIX); \
			PRINT(name);                        \
			format(REGDUMP_FORMAT_FLAG_SUFFIX); \
		}
		PRINT_FLAG("ge", DR7_GE, DR7_LE)
		PRINT_FLAG("rtm", DR7_RTM, DR7_LE | DR7_GE)
		PRINT_FLAG("gd", DR7_GD, DR7_LE | DR7_GE | DR7_RTM)
#undef PRINT_FLAG
		PRINT("]");
	}
	if (dr7 & (DR7_L0 | DR7_G0 | DR7_L1 | DR7_G1 |
	           DR7_L2 | DR7_G2 | DR7_L3 | DR7_G3)) {
		unsigned int i;
		bool is_first = true;
		PRINT(" [");
		for (i = 0; i < DR7_BREAKPOINT_COUNT; ++i) {
			char desc[2];
			unsigned int mode = dr7 & (unsigned int)(DR7_LN(i) | DR7_GN(i));
			unsigned int cond, size;
			if (!mode)
				continue;
			desc[0] = mode == (unsigned int)(DR7_LN(i) | DR7_GN(i))
			          ? 'b'
			          : mode == (unsigned int)DR7_LN(i)
			            ? 'l'
			            : 'g';
			desc[1] = itoa_decimal(i);
			if (!is_first)
				PRINT(",");
			format(REGDUMP_FORMAT_FLAG_PREFIX);
			print(desc, 2);
			format(REGDUMP_FORMAT_FLAG_SUFFIX);
			cond = (dr7 >> DR7_CN_SHIFT(i)) & 3;
			size = (dr7 >> DR7_SN_SHIFT(i)) & 3;
			PRINT(":");
#ifndef __x86_64__
			format(REGDUMP_FORMAT_FLAG_PREFIX);
#endif /* !__x86_64__ */
			switch (cond) {

			case DR_CEXEC:
#ifdef __x86_64__
				format(REGDUMP_FORMAT_FLAG_PREFIX);
#endif /* __x86_64__ */
				PRINT("x");
#ifdef __x86_64__
				format(REGDUMP_FORMAT_FLAG_SUFFIX);
#endif /* __x86_64__ */
				break;

			case DR_CWRITE:
#ifdef __x86_64__
				format(REGDUMP_FORMAT_FLAG_PREFIX);
#endif /* __x86_64__ */
				PRINT("w");
#ifdef __x86_64__
				format(REGDUMP_FORMAT_FLAG_SUFFIX);
#endif /* __x86_64__ */
				break;

			case DR_CREADWRITE:
#ifdef __x86_64__
				format(REGDUMP_FORMAT_FLAG_PREFIX);
#endif /* __x86_64__ */
				PRINT("rw");
#ifdef __x86_64__
				format(REGDUMP_FORMAT_FLAG_SUFFIX);
#endif /* __x86_64__ */
				break;

#ifndef __x86_64__
			case DR_CIO:
				PRINT("io");
				break;
#endif
#ifdef __x86_64__
			default:
				format(REGDUMP_FORMAT_ERROR_PREFIX);
				PRINT("?");
				format(REGDUMP_FORMAT_ERROR_SUFFIX);
				break;
#else /* __x86_64__ */
			default:
				__builtin_unreachable();
#endif /* !__x86_64__ */
			}
#ifndef __x86_64__
			format(REGDUMP_FORMAT_FLAG_SUFFIX);
#endif /* !__x86_64__ */
			switch (size) {
			case DR_S1: size = 1; break;
			case DR_S2: size = 2; break;
			case DR_S4: size = 4; break;
			case DR_S8: size = 8; break;
			default:
				__builtin_unreachable();
			}
			PRINT("+");
			format(REGDUMP_FORMAT_OFFSET_PREFIX);
			printf("%u", (unsigned int)size);
			format(REGDUMP_FORMAT_OFFSET_SUFFIX);
			is_first = false;
		}
		PRINT("]");
	}
	END;
}




#ifdef __KERNEL__
#define SEGMENTS_BEGIN      \
	{                       \
		struct desctab gdt; \
		uint16_t ldt = 0;   \
		__sgdt(&gdt);
#define SEGMENTS_END \
	}
#define SEGMENTS_BEGIN_NOLDT \
	{                        \
		struct desctab gdt;  \
		__sgdt(&gdt);
#define SEGMENTS_END_NOLDT \
	}
#define SEGMENTS_ARGS  , &gdt, &ldt
#else /* __KERNEL__ */
#define SEGMENTS_BEGIN       /* nothing */
#define SEGMENTS_END         /* nothing */
#define SEGMENTS_BEGIN_NOLDT /* nothing */
#define SEGMENTS_END_NOLDT   /* nothing */
#define SEGMENTS_ARGS        /* nothing */
#endif /* !__KERNEL__ */


INTERN NONNULL((1, 2)) ssize_t CC
libregdump_sgregs(struct regdump_printer *__restrict self,
                  struct sgregs const *__restrict data) {
	BEGIN;
	SEGMENTS_BEGIN
	format(REGDUMP_FORMAT_INDENT);
	DO(libregdump_do_segment(self, 'e', data->sg_es16 SEGMENTS_ARGS));
	PRINT("\n");
	format(REGDUMP_FORMAT_INDENT);
	DO(libregdump_do_segment(self, 'd', data->sg_ds16 SEGMENTS_ARGS));
	PRINT("\n");
	format(REGDUMP_FORMAT_INDENT);
	DO(libregdump_do_segment(self, 'f', data->sg_fs16 SEGMENTS_ARGS));
	PRINT("\n");
	format(REGDUMP_FORMAT_INDENT);
	DO(libregdump_do_segment(self, 'g', data->sg_gs16 SEGMENTS_ARGS));
	PRINT("\n");
	SEGMENTS_END
	END;
}

INTERN NONNULL((1, 2)) ssize_t CC
libregdump_sgregs_with_cs_ss(struct regdump_printer *__restrict self,
                             struct sgregs const *__restrict data,
                             uint16_t cs, uint16_t ss) {
	BEGIN;
	SEGMENTS_BEGIN
#ifdef __KERNEL__
	format(REGDUMP_FORMAT_INDENT);
	DO(libregdump_do_segment(self, 'e', data->sg_es16 SEGMENTS_ARGS));
	PRINT("\n");
	format(REGDUMP_FORMAT_INDENT);
	DO(libregdump_do_segment(self, 'd', data->sg_ds16 SEGMENTS_ARGS));
	PRINT("\n");
	format(REGDUMP_FORMAT_INDENT);
	DO(libregdump_do_segment(self, 'f', data->sg_fs16 SEGMENTS_ARGS));
	PRINT("\n");
	format(REGDUMP_FORMAT_INDENT);
	DO(libregdump_do_segment(self, 'g', data->sg_gs16 SEGMENTS_ARGS));
	PRINT("\n");
#else /* __KERNEL__ */
	DO(libregdump_sgregs(self, data));
#endif /* !__KERNEL__ */
	format(REGDUMP_FORMAT_INDENT);
	DO(libregdump_do_segment(self, 'c', cs SEGMENTS_ARGS));
	PRINT("\n");
	format(REGDUMP_FORMAT_INDENT);
	DO(libregdump_do_segment(self, 's', ss SEGMENTS_ARGS));
	PRINT("\n");
	SEGMENTS_END
	END;
}

INTERN NONNULL((1, 2)) ssize_t CC
libregdump_sgregs_with_cs_ss_tr_ldt(struct regdump_printer *__restrict self,
                                    struct sgregs const *__restrict data,
                                    uint16_t cs, uint16_t ss,
                                    uint16_t tr, uint16_t ldt) {
	BEGIN;
	SEGMENTS_BEGIN_NOLDT
#ifdef __KERNEL__
	format(REGDUMP_FORMAT_INDENT);
	DO(libregdump_do_segment(self, 'e', data->sg_es16 SEGMENTS_ARGS));
	PRINT("\n");
	format(REGDUMP_FORMAT_INDENT);
	DO(libregdump_do_segment(self, 'd', data->sg_ds16 SEGMENTS_ARGS));
	PRINT("\n");
	format(REGDUMP_FORMAT_INDENT);
	DO(libregdump_do_segment(self, 'f', data->sg_fs16 SEGMENTS_ARGS));
	PRINT("\n");
	format(REGDUMP_FORMAT_INDENT);
	DO(libregdump_do_segment(self, 'g', data->sg_gs16 SEGMENTS_ARGS));
	PRINT("\n");
	format(REGDUMP_FORMAT_INDENT);
	DO(libregdump_do_segment(self, 'c', cs SEGMENTS_ARGS));
	PRINT("\n");
	format(REGDUMP_FORMAT_INDENT);
	DO(libregdump_do_segment(self, 's', ss SEGMENTS_ARGS));
	PRINT("\n");
#else /* __KERNEL__ */
	DO(libregdump_sgregs_with_cs_ss(self, data, cs, ss));
#endif /* !__KERNEL__ */
	format(REGDUMP_FORMAT_INDENT);
	DO(libregdump_do_segment(self, 't', tr SEGMENTS_ARGS));
	PRINT("\n");
	format(REGDUMP_FORMAT_INDENT);
	DO(libregdump_do_segment(self, 'l', ldt SEGMENTS_ARGS));
	PRINT("\n");
	SEGMENTS_END_NOLDT
	END;
}

#ifdef __x86_64__
PRIVATE NONNULL((1)) ssize_t CC
libregdump_do_sgbase(struct regdump_printer *__restrict self,
                     char name, uintptr_t value) {
	char namestr[8];
	BEGIN;
	format(REGDUMP_FORMAT_REGISTER_PREFIX);
	namestr[0] = '%';
	namestr[1] = name;
	namestr[2] = 's';
	namestr[3] = '.';
	namestr[4] = 'b';
	namestr[5] = 'a';
	namestr[6] = 's';
	namestr[7] = 'e';
	print(namestr, 8);
	format(REGDUMP_FORMAT_REGISTER_SUFFIX);
	PRINT(" ");
	format(REGDUMP_FORMAT_VALUE_PREFIX);
	printf("%p", value);
	format(REGDUMP_FORMAT_VALUE_SUFFIX);
	END;
}
INTERN NONNULL((1, 2)) ssize_t CC
libregdump_sgbase(struct regdump_printer *__restrict self,
                  struct sgbase const *__restrict data) {
	BEGIN;
	DO(libregdump_do_sgbase(self, 'f', data->sg_fsbase));
	PRINT(" ");
	DO(libregdump_do_sgbase(self, 'g', data->sg_gsbase));
	END;
}
#endif /* __x86_64__ */

/* Print a segment register (id is one of { d[s], e[s], f[s], g[s], c[s], s[s], t[r], l[dt] } (pass the character that doesn't appear in brackets)) */
INTERN NONNULL((1)) ssize_t CC
libregdump_sreg(struct regdump_printer *__restrict self,
                char id, uint16_t value) {
	ssize_t result;
	SEGMENTS_BEGIN
	result = libregdump_do_segment(self, id, value SEGMENTS_ARGS);
	SEGMENTS_END
	return result;
}

INTERN NONNULL((1, 2)) ssize_t CC
libregdump_coregs(struct regdump_printer *__restrict self,
                  struct coregs const *__restrict data) {
	BEGIN;
	format(REGDUMP_FORMAT_INDENT);
	DO(libregdump_cr0(self, data->co_cr0));
	PRINT("    ");
	format(REGDUMP_FORMAT_REGISTER_PREFIX);
	PRINT("%cr2");
	format(REGDUMP_FORMAT_REGISTER_SUFFIX);
	PRINT(" ");
	format(REGDUMP_FORMAT_VALUE_PREFIX);
	printf("%p", data->co_cr2);
	format(REGDUMP_FORMAT_VALUE_SUFFIX);
	PRINT("\n");
	format(REGDUMP_FORMAT_INDENT);
	DO(libregdump_cr4(self, data->co_cr4));
	PRINT("    ");
	format(REGDUMP_FORMAT_REGISTER_PREFIX);
	PRINT("%cr3");
	format(REGDUMP_FORMAT_REGISTER_SUFFIX);
	PRINT(" ");
	format(REGDUMP_FORMAT_VALUE_PREFIX);
	printf("%p", data->co_cr3);
	format(REGDUMP_FORMAT_VALUE_SUFFIX);
	PRINT("\n");
	END;
}

PRIVATE NONNULL((1)) ssize_t CC
libregdump_do_drx(struct regdump_printer *__restrict self,
                  unsigned int n, void *drx, uintptr_t dr7) {
	unsigned int mode;
	BEGIN;
	format(REGDUMP_FORMAT_REGISTER_PREFIX);
	{
		char name[4];
		name[0] = '%';
		name[1] = 'd';
		name[2] = 'r';
		name[3] = itoa_decimal(n);
		print(name, 4);
	}
	format(REGDUMP_FORMAT_REGISTER_SUFFIX);
	PRINT(" ");
	format(REGDUMP_FORMAT_VALUE_PREFIX);
	printf("%p", drx);
	format(REGDUMP_FORMAT_VALUE_SUFFIX);
	mode = dr7 & (DR7_LN(n) | DR7_GN(n));
	if (mode) {
		unsigned int cond, size;
		cond = (dr7 >> DR7_CN_SHIFT(n)) & 3;
		size = (dr7 >> DR7_SN_SHIFT(n)) & 3;
		switch (size) {
		case DR_S1: size = 1; break;
		case DR_S2: size = 2; break;
		case DR_S4: size = 4; break;
		case DR_S8: size = 8; break;
		default:
			__builtin_unreachable();
		}
		PRINT(" (");
		switch (cond) {

		case DR_CEXEC:
			PRINT("exec {");
			break;

		case DR_CWRITE:
			PRINT("write {");
			break;

		case DR_CREADWRITE:
			PRINT("read/write {");
			break;

#ifndef __x86_64__
		case DR_CIO:
			PRINT("io {");
			break;
#endif /* !__x86_64__ */

#ifdef __x86_64__
		default:
			format(REGDUMP_FORMAT_ERROR_PREFIX);
			PRINT("UNKNOWN");
			format(REGDUMP_FORMAT_ERROR_SUFFIX);
			PRINT(" {");
			break;
#else /* __x86_64__ */
		default:
			__builtin_unreachable();
#endif /* !__x86_64__ */
		}
		format(REGDUMP_FORMAT_VALUE_PREFIX);
		printf("%p", drx);
		format(REGDUMP_FORMAT_VALUE_SUFFIX);
		PRINT("-");
		format(REGDUMP_FORMAT_VALUE_PREFIX);
		printf("%p", (byte_t *)drx + size - 1);
		format(REGDUMP_FORMAT_VALUE_SUFFIX);
		PRINT(")");
	}
	END;
}

INTERN NONNULL((1, 2)) ssize_t CC
libregdump_drregs(struct regdump_printer *__restrict self,
                  struct drregs const *__restrict data) {
	BEGIN;
	if (data->dr_dr7 & (DR7_L0 | DR7_G0)) {
		format(REGDUMP_FORMAT_INDENT);
		DO(libregdump_do_drx(self, 0, data->dr_dr0, data->dr_dr7));
		PRINT("\n");
	}
	if (data->dr_dr7 & (DR7_L1 | DR7_G1)) {
		format(REGDUMP_FORMAT_INDENT);
		DO(libregdump_do_drx(self, 1, data->dr_dr1, data->dr_dr7));
		PRINT("\n");
	}
	if (data->dr_dr7 & (DR7_L2 | DR7_G2)) {
		format(REGDUMP_FORMAT_INDENT);
		DO(libregdump_do_drx(self, 2, data->dr_dr2, data->dr_dr7));
		PRINT("\n");
	}
	if (data->dr_dr7 & (DR7_L3 | DR7_G3)) {
		format(REGDUMP_FORMAT_INDENT);
		DO(libregdump_do_drx(self, 3, data->dr_dr3, data->dr_dr7));
		PRINT("\n");
	}
	format(REGDUMP_FORMAT_INDENT);
	DO(libregdump_dr7(self, data->dr_dr7));
	if (data->dr_dr7 & (DR7_L0 | DR7_G0 | DR7_L1 | DR7_G1 |
	                    DR7_L2 | DR7_G2 | DR7_L3 | DR7_G3)) {
		PRINT("\n");
		format(REGDUMP_FORMAT_INDENT);
	} else {
		PRINT("    ");
	}
	DO(libregdump_dr6(self, data->dr_dr6));
	PRINT("\n");
	END;
}

/* Print the eflags/rflags register */
INTERN NONNULL((1)) ssize_t CC
libregdump_flags(struct regdump_printer *__restrict self,
                 uintptr_t flags) {
	char arith[5];
	BEGIN;
	format(REGDUMP_FORMAT_REGISTER_PREFIX);
	PRINT("%" RPF "flags");
	format(REGDUMP_FORMAT_REGISTER_SUFFIX);
	PRINT(" ");
	format(REGDUMP_FORMAT_VALUE_PREFIX);
	printf("%.4p", flags);
	format(REGDUMP_FORMAT_VALUE_SUFFIX);
	PRINT(" [");
	arith[0] = flags & EFLAGS_CF ? 'c' : '-';
	arith[1] = flags & EFLAGS_PF ? 'p' : '-';
	arith[2] = flags & EFLAGS_ZF ? 'z' : '-';
	arith[3] = flags & EFLAGS_SF ? 's' : '-';
	arith[4] = flags & EFLAGS_OF ? 'o' : '-';
	format(REGDUMP_FORMAT_FLAG_PREFIX);
	print(arith, 5);
	format(REGDUMP_FORMAT_FLAG_SUFFIX);
	PRINT("]");
	if (flags & (EFLAGS_AF | EFLAGS_TF | EFLAGS_IF | EFLAGS_DF |
	             EFLAGS_NT | EFLAGS_RF | EFLAGS_VM | EFLAGS_AC |
	             EFLAGS_VIF | EFLAGS_VIP | EFLAGS_ID)) {
		PRINT(" [");
		if (flags & EFLAGS_AF) {
			format(REGDUMP_FORMAT_FLAG_PREFIX);
			PRINT("af");
			format(REGDUMP_FORMAT_FLAG_SUFFIX);
		}
#define PRINT_FLAG(name, f, before) \
		if (flags & (f)) {                      \
			if (flags & (before))               \
				PRINT(",");                     \
			format(REGDUMP_FORMAT_FLAG_PREFIX); \
			PRINT(name);                        \
			format(REGDUMP_FORMAT_FLAG_SUFFIX); \
		}
		PRINT_FLAG("tf", EFLAGS_TF, EFLAGS_AF)
		PRINT_FLAG("if", EFLAGS_IF, EFLAGS_AF | EFLAGS_TF)
		PRINT_FLAG("df", EFLAGS_DF, EFLAGS_AF | EFLAGS_TF | EFLAGS_IF)
		PRINT_FLAG("nt", EFLAGS_NT, EFLAGS_AF | EFLAGS_TF | EFLAGS_IF | EFLAGS_DF)
		PRINT_FLAG("rf", EFLAGS_RF, EFLAGS_AF | EFLAGS_TF | EFLAGS_IF | EFLAGS_DF | EFLAGS_NT)
		PRINT_FLAG("vm", EFLAGS_VM, EFLAGS_AF | EFLAGS_TF | EFLAGS_IF | EFLAGS_DF | EFLAGS_NT | EFLAGS_RF)
		PRINT_FLAG("ac", EFLAGS_AC, EFLAGS_AF | EFLAGS_TF | EFLAGS_IF | EFLAGS_DF | EFLAGS_NT | EFLAGS_RF | EFLAGS_VM)
		PRINT_FLAG("vif", EFLAGS_VIF, EFLAGS_AF | EFLAGS_TF | EFLAGS_IF | EFLAGS_DF | EFLAGS_NT | EFLAGS_RF | EFLAGS_VM | EFLAGS_AC)
		PRINT_FLAG("vip", EFLAGS_VIP, EFLAGS_AF | EFLAGS_TF | EFLAGS_IF | EFLAGS_DF | EFLAGS_NT | EFLAGS_RF | EFLAGS_VM | EFLAGS_AC | EFLAGS_VIF)
		PRINT_FLAG("id", EFLAGS_ID, EFLAGS_AF | EFLAGS_TF | EFLAGS_IF | EFLAGS_DF | EFLAGS_NT | EFLAGS_RF | EFLAGS_VM | EFLAGS_AC | EFLAGS_VIF | EFLAGS_VIP)
#undef PRINT_FLAG
		PRINT("]");
	}
	PRINT(" [iopl=");
	format(REGDUMP_FORMAT_VALUE_PREFIX);
	printf("%u", EFLAGS_GETIOPL(flags));
	format(REGDUMP_FORMAT_VALUE_SUFFIX);
	PRINT("]");
	END;
}

#ifndef __KERNEL__
PRIVATE void *pdyn_libinstrlen  = NULL;
PRIVATE void *pdyn_libdebuginfo = NULL;
PRIVATE void *pdyn_libdisasm    = NULL;

PRIVATE __attribute__((__destructor__))
void fini_libraries(void) {
	if (pdyn_libinstrlen && pdyn_libinstrlen != (void *)-1)
		dlclose(pdyn_libinstrlen);
	if (pdyn_libdebuginfo && pdyn_libdebuginfo != (void *)-1)
		dlclose(pdyn_libdebuginfo);
	if (pdyn_libdisasm && pdyn_libdisasm != (void *)-1)
		dlclose(pdyn_libdisasm);
}

#define DEFINE_LIBRARY_OPEN(open_libname, libname, LIBNAME_LIBRARY_NAME) \
	PRIVATE void *open_libname(void) {                                   \
		void *result;                                                    \
	again:                                                               \
		result = atomic_read(&libname);                                  \
		if (result == NULL) {                                            \
			result = dlopen(LIBNAME_LIBRARY_NAME, RTLD_LOCAL);           \
			if (!result)                                                 \
				result = (void *)-1;                                     \
			if (!atomic_cmpxch(&libname, NULL, result)) {                \
				if (result != (void *)-1)                                \
					dlclose(result);                                     \
				goto again;                                              \
			}                                                            \
		}                                                                \
		if (result == (void *)-1)                                        \
			result = NULL;                                               \
		return result;                                                   \
	}
DEFINE_LIBRARY_OPEN(open_libinstrlen, pdyn_libinstrlen, LIBINSTRLEN_LIBRARY_NAME)
DEFINE_LIBRARY_OPEN(open_libdebuginfo, pdyn_libdebuginfo, LIBDEBUGINFO_LIBRARY_NAME)
DEFINE_LIBRARY_OPEN(open_libdisasm, pdyn_libdisasm, LIBDISASM_LIBRARY_NAME)
#undef DEFINE_LIBRARY_OPEN

PRIVATE PDEBUG_ADDR2LINE_SECTIONS_LOCK /*  */ pdyn_debug_addr2line_sections_lock   = NULL;
PRIVATE PDEBUG_ADDR2LINE_SECTIONS_UNLOCK /**/ pdyn_debug_addr2line_sections_unlock = NULL;
PRIVATE PDEBUG_ADDR2LINE /*                */ pdyn_debug_addr2line                 = NULL;
PRIVATE PINSTRUCTION_PRED_NX /*            */ pdyn_instruction_pred_nx             = NULL;
PRIVATE PDISASM_SINGLE /*                  */ pdyn_disasm_single                   = NULL;
#define debug_addr2line_sections_lock   (*pdyn_debug_addr2line_sections_lock)
#define debug_addr2line_sections_unlock (*pdyn_debug_addr2line_sections_unlock)
#define debug_addr2line                 (*pdyn_debug_addr2line)
#define instruction_pred_nx             (*pdyn_instruction_pred_nx)
#define disasm_single                   (*pdyn_disasm_single)

#define ENSURE_LIBINSTRLEN() ensure_libinstrlen()
PRIVATE bool CC ensure_libinstrlen(void) {
	void *libinstrlen;
	if (pdyn_instruction_pred_nx)
		return true;
	libinstrlen = open_libinstrlen();
	if unlikely(!libinstrlen)
		return false;
	COMPILER_WRITE_BARRIER();
	*(void **)&pdyn_instruction_pred_nx = dlsym(libinstrlen, "instruction_pred_nx");
	COMPILER_WRITE_BARRIER();
	return pdyn_instruction_pred_nx != NULL;
}

#define ENSURE_LIBDEBUGINFO() ensure_libdebuginfo()
PRIVATE bool CC ensure_libdebuginfo(void) {
	void *libdebuginfo;
	if (pdyn_debug_addr2line)
		return true;
	libdebuginfo = open_libdebuginfo();
	if unlikely(!libdebuginfo)
		return false;
	*(void **)&pdyn_debug_addr2line_sections_lock   = dlsym(libdebuginfo, "debug_addr2line_sections_lock");
	if unlikely(!pdyn_debug_addr2line_sections_lock)
		return false;
	*(void **)&pdyn_debug_addr2line_sections_unlock = dlsym(libdebuginfo, "debug_addr2line_sections_unlock");
	if unlikely(!pdyn_debug_addr2line_sections_unlock)
		return false;
	COMPILER_WRITE_BARRIER();
	*(void **)&pdyn_debug_addr2line = dlsym(libdebuginfo, "debug_addr2line");
	COMPILER_WRITE_BARRIER();
	return pdyn_debug_addr2line != NULL;
}

#define ENSURE_LIBDISASM() ensure_libdisasm()
PRIVATE bool CC ensure_libdisasm(void) {
	void *libdisasm;
	if (pdyn_disasm_single)
		return true;
	libdisasm = open_libdisasm();
	if unlikely(!libdisasm)
		return false;
	COMPILER_WRITE_BARRIER();
	*(void **)&pdyn_disasm_single = dlsym(libdisasm, "disasm_single");
	COMPILER_WRITE_BARRIER();
	return pdyn_disasm_single != NULL;
}

#else /* !__KERNEL__ */
#define ENSURE_LIBINSTRLEN()  true
#define ENSURE_LIBDEBUGINFO() true
#define ENSURE_LIBDISASM()    true
#endif /* __KERNEL__ */

PRIVATE NONNULL((1, 2, 4)) ssize_t CC
libregdump_do_ip_addr2line_info(struct regdump_printer *__restrict self,
                                di_debug_addr2line_t const *__restrict info,
                                uintptr_t relpc,
                                bool *__restrict pdid_lf_after_eip) {
	BEGIN;
	if (info->al_name || info->al_srcfile || info->al_srcline) {
		PRINT("\n");
		format(REGDUMP_FORMAT_INDENT);
		format(REGDUMP_FORMAT_INDENT);
	}
	if (info->al_name) {
		PRINT("[");
		format(REGDUMP_FORMAT_VALUE_PREFIX);
		print(info->al_name, strlen(info->al_name));
		format(REGDUMP_FORMAT_VALUE_SUFFIX);
		PRINT("+");
		format(REGDUMP_FORMAT_OFFSET_PREFIX);
		printf("%" PRIuSIZ, (size_t)(relpc - info->al_symstart));
		format(REGDUMP_FORMAT_OFFSET_SUFFIX);
		PRINT("]");
	}
	if (info->al_srcfile) {
		if (info->al_name)
			PRINT(" ");
		PRINT("[");
		format(REGDUMP_FORMAT_VALUE_PREFIX);
		print(info->al_srcfile, strlen(info->al_srcfile));
		format(REGDUMP_FORMAT_VALUE_SUFFIX);
		PRINT("]");
	}
	if (info->al_srcline) {
		if (info->al_name || info->al_srcfile)
			PRINT(" ");
		PRINT("[line=");
		format(REGDUMP_FORMAT_VALUE_PREFIX);
		printf("%" PRIuPTR, info->al_srcline);
		format(REGDUMP_FORMAT_VALUE_SUFFIX);
		if (info->al_srccol) {
			PRINT(",");
			format(REGDUMP_FORMAT_VALUE_PREFIX);
			printf("%" PRIuPTR, info->al_srccol);
			format(REGDUMP_FORMAT_VALUE_SUFFIX);
		}
		PRINT("]\n");
		*pdid_lf_after_eip = true;
	} else if (info->al_name || info->al_srcfile) {
		*pdid_lf_after_eip = true;
		PRINT("\n");
	}
	END;
}


/* Print the InstructionPointer register. */
INTERN NONNULL((1)) ssize_t CC
libregdump_ip(struct regdump_printer *__restrict self,
              uintptr_t ip, isa_t isa) {
	BEGIN;
	format(REGDUMP_FORMAT_INDENT);
	format(REGDUMP_FORMAT_REGISTER_PREFIX);
	PRINT("%" RPF "ip");
	format(REGDUMP_FORMAT_REGISTER_SUFFIX);
	PRINT(" ");
	format(REGDUMP_FORMAT_VALUE_PREFIX);
	printf("%p", ip);
	format(REGDUMP_FORMAT_VALUE_SUFFIX);
	{
		uintptr_t prev_ip = 0;
		bool did_lf_after_eip = false;
		if (ENSURE_LIBINSTRLEN())
			prev_ip = (uintptr_t)instruction_pred_nx((void const *)ip, isa);
		if (!prev_ip)
			prev_ip = ip;
		if (prev_ip == ip) {
			--prev_ip;
		} else {
			PRINT(" [orig=");
			format(REGDUMP_FORMAT_VALUE_PREFIX);
			printf("%p", prev_ip);
			format(REGDUMP_FORMAT_VALUE_SUFFIX);
			PRINT("]");
		}
		if (ENSURE_LIBDEBUGINFO()) {
			REF module_t *ip_module;
			ip_module = module_fromaddr_nx((void const *)ip);
			if (ip_module) {
				di_addr2line_sections_t sections;
				di_addr2line_dl_sections_t dl_sections;
				temp = 0;
				if (debug_addr2line_sections_lock(ip_module, &sections, &dl_sections) ==
				    DEBUG_INFO_ERROR_SUCCESS) {
					di_debug_addr2line_t info;
					uintptr_t relpc = prev_ip - module_getloadaddr(ip_module);
					if (debug_addr2line(&sections, &info, relpc, 0, 0) == DEBUG_INFO_ERROR_SUCCESS)
						temp = libregdump_do_ip_addr2line_info(self, &info, relpc, &did_lf_after_eip);
					debug_addr2line_sections_unlock(&dl_sections);
				}
				module_decref_unlikely(ip_module);
				if unlikely(temp < 0)
					goto err;
				result += temp;
			}
		}
		if (ENSURE_LIBDISASM()) {
			if (!did_lf_after_eip)
				PRINT("\n");
			format(REGDUMP_FORMAT_INDENT);
			format(REGDUMP_FORMAT_INDENT);
			PRINT("[");
			NESTED_TRY {
				DO(disasm_single(self->rdp_printer, self->rdp_printer_arg, (void *)prev_ip,
				                 DISASSEMBLER_TARGET_CURRENT, DISASSEMBLER_FNORMAL));
			} EXCEPT {
				except_class_t cls = except_class();
				if (EXCEPTCLASS_ISRTLPRIORITY(cls))
					RETHROW();
				format(REGDUMP_FORMAT_ERROR_PREFIX);
				printf("error:%s", except_name(except_code()));
				format(REGDUMP_FORMAT_ERROR_SUFFIX);
			}
			PRINT("]\n");
			did_lf_after_eip = true;
		}
		if unlikely(!did_lf_after_eip)
			PRINT("\n");
	}
	END;
}

INTERN NONNULL((1, 2)) ssize_t CC
libregdump_gdt(struct regdump_printer *__restrict self,
               struct desctab const *__restrict gdt) {
	BEGIN;
	format(REGDUMP_FORMAT_INDENT);
	format(REGDUMP_FORMAT_REGISTER_PREFIX);
	PRINT("%gdt");
	format(REGDUMP_FORMAT_REGISTER_SUFFIX);
	PRINT(" ");
	format(REGDUMP_FORMAT_VALUE_PREFIX);
	printf("%p", gdt->dt_base);
	format(REGDUMP_FORMAT_VALUE_SUFFIX);
	PRINT("+");
	format(REGDUMP_FORMAT_VALUE_PREFIX);
	printf("%" PRIu16, gdt->dt_limit);
	format(REGDUMP_FORMAT_VALUE_SUFFIX);
	PRINT("\n");
	END;
}

INTERN NONNULL((1, 2)) ssize_t CC
libregdump_idt(struct regdump_printer *__restrict self,
               struct desctab const *__restrict idt) {
	BEGIN;
	format(REGDUMP_FORMAT_INDENT);
	format(REGDUMP_FORMAT_REGISTER_PREFIX);
	PRINT("%idt");
	format(REGDUMP_FORMAT_REGISTER_SUFFIX);
	PRINT(" ");
	format(REGDUMP_FORMAT_VALUE_PREFIX);
	printf("%p", idt->dt_base);
	format(REGDUMP_FORMAT_VALUE_SUFFIX);
	PRINT("+");
	format(REGDUMP_FORMAT_VALUE_PREFIX);
	printf("%" PRIu16, idt->dt_limit);
	format(REGDUMP_FORMAT_VALUE_SUFFIX);
	PRINT("\n");
	END;
}


DEFINE_PUBLIC_ALIAS(regdump_gpreg, libregdump_gpreg);
DEFINE_PUBLIC_ALIAS(regdump_gpregs, libregdump_gpregs);
DEFINE_PUBLIC_ALIAS(regdump_gpregs_with_sp, libregdump_gpregs_with_sp);
DEFINE_PUBLIC_ALIAS(regdump_sgregs, libregdump_sgregs);
DEFINE_PUBLIC_ALIAS(regdump_sgregs_with_cs_ss, libregdump_sgregs_with_cs_ss);
DEFINE_PUBLIC_ALIAS(regdump_sgregs_with_cs_ss_tr_ldt, libregdump_sgregs_with_cs_ss_tr_ldt);
#ifdef __x86_64__
DEFINE_PUBLIC_ALIAS(regdump_sgbase, libregdump_sgbase);
#endif /* __x86_64__ */
DEFINE_PUBLIC_ALIAS(regdump_coregs, libregdump_coregs);
DEFINE_PUBLIC_ALIAS(regdump_cr0, libregdump_cr0);
DEFINE_PUBLIC_ALIAS(regdump_cr4, libregdump_cr4);
DEFINE_PUBLIC_ALIAS(regdump_dr6, libregdump_dr6);
DEFINE_PUBLIC_ALIAS(regdump_dr7, libregdump_dr7);
DEFINE_PUBLIC_ALIAS(regdump_drregs, libregdump_drregs);
DEFINE_PUBLIC_ALIAS(regdump_sreg, libregdump_sreg);
DEFINE_PUBLIC_ALIAS(regdump_flags, libregdump_flags);
DEFINE_PUBLIC_ALIAS(regdump_ip, libregdump_ip);
DEFINE_PUBLIC_ALIAS(regdump_gdt, libregdump_gdt);
DEFINE_PUBLIC_ALIAS(regdump_idt, libregdump_idt);


DECL_END

#endif /* !GUARD_LIBREGDUMP_ARCH_I386_X86_C */
