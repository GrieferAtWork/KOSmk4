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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_REGISTER_BY_NAME_C
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_REGISTER_BY_NAME_C 1
#define DISABLE_BRANCH_PROFILING

#include <kernel/compiler.h>

#include <debugger/config.h>

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <debugger/rt.h>

#include <hybrid/host.h>

#include <asm/registers-compat.h>
#include <asm/registers.h>

#include <string.h>
#include <unicode.h>

DECL_BEGIN

#ifdef __x86_64__
#define IF32(...) /* nothing */
#define IF64(...) __VA_ARGS__
#define IFELSE3264(x32, x64) x64
#else /* __x86_64__ */
#define IF32(...) __VA_ARGS__
#define IF64(...) /* nothing */
#define IFELSE3264(x32, x64) x32
#endif /* !__x86_64__ */

/* Return the ID (one of `X86_REGISTER_*' from <asm/registers.h>,
 * or one  of `X86_DBGREGISTER_*')  from a  given register  name. */
PUBLIC ATTR_PURE WUNUSED NONNULL((1)) unsigned int
NOTHROW(KCALL x86_dbg_regfromname)(char const *__restrict name,
                                   size_t namelen) {
#define EQNOCASE(ch, lower_ch) ((ch) == (lower_ch) || (ch) == ((lower_ch) + ('A' - 'a')))
#define CASENOCASE(lower_ch)   case lower_ch: case (lower_ch) + ('A' - 'a')
	unsigned int result, flags = 0;
	/* Trim trailing spaces. */
	while (namelen) {
		char32_t ch;
		char const *endp = name + namelen;
		ch = unicode_readutf8_rev_n(&endp, name);
		if (!unicode_isspace(ch))
			break;
		namelen -= (size_t)(name - endp);
	}
	if unlikely(!namelen)
		goto unknown;
	if (*name == '.' && namelen == 1)
		return X86_REGISTER_MISC_PIP; /* Special case: current program counter. */
	if (namelen == 2) {
		/* Check for special, portable names. */
		if (EQNOCASE(name[0], 's') && EQNOCASE(name[0], 'p'))
			return X86_REGISTER_GENERAL_PURPOSE_PSP;
		if ((EQNOCASE(name[0], 'p') && EQNOCASE(name[0], 'c')) ||
		    (EQNOCASE(name[0], 'i') && EQNOCASE(name[0], 'p')))
			return X86_REGISTER_MISC_PIP;
	}
	/* Skip leading space characters */
#define SKIP_LEADING_SPACE()                            \
	while (namelen) {                                   \
		char32_t ch;                                    \
		char const *endp = name;                        \
		ch = unicode_readutf8_n(&endp, name + namelen); \
		if (!unicode_isspace(ch))                       \
			break;                                      \
		namelen -= (size_t)(endp - name);               \
		name = endp;                                    \
	}
	SKIP_LEADING_SPACE();
	if (*name == '%' || *name == '$') {
		++name;
		++namelen;
		/* Skip additional space characters after a `%' or `$' prefix! */
		SKIP_LEADING_SPACE();
	}
	if (namelen >= 2 && EQNOCASE(name[0], 'x') &&
	    (name[1] == '.' || name[1] == ':')) {
		name    += 2;
		namelen -= 2;
		flags |= X86_DBGREGISTER_FEXCEPTREGISTER;
	} else if (namelen >= 6 &&
	           EQNOCASE(name[0], 'e') && EQNOCASE(name[1], 'x') &&
	           EQNOCASE(name[2], 'c') && EQNOCASE(name[3], 'e') &&
	           EQNOCASE(name[4], 'p') && EQNOCASE(name[5], 't') &&
	           (name[6] == '.' || name[6] == ':')) {
		name    += 6;
		namelen -= 6;
		flags |= X86_DBGREGISTER_FEXCEPTREGISTER;
	}
	if unlikely(!namelen)
		goto unknown;
	if (EQNOCASE(name[0], 'p'))
		goto do_pax;
#ifdef __x86_64__
	if (EQNOCASE(name[0], 'r')) {
do_pax:
		++name;
		--namelen;
		if (namelen == 3) {
			if (name[0] == '1' && (name[1] >= '0' && name[1] <= '5')) {
				switch (name[2]) {

				CASENOCASE('d'):
					result = X86_REGISTER_GENERAL_PURPOSE_R10D + (name[1] - '0');
					goto done;

				CASENOCASE('w'):
					result = X86_REGISTER_GENERAL_PURPOSE_R10W + (name[1] - '0');
					goto done;

				CASENOCASE('l'):
					result = X86_REGISTER_GENERAL_PURPOSE_R10L + (name[1] - '0');
					goto done;

				default:
					break;
				}
			}
		}
		if (namelen == 2) {
			switch (name[1]) {

			CASENOCASE('x'):
				switch (name[0]) {
				CASENOCASE('a'): result = X86_REGISTER_GENERAL_PURPOSE_RAX; goto done;
				CASENOCASE('c'): result = X86_REGISTER_GENERAL_PURPOSE_RCX; goto done;
				CASENOCASE('d'): result = X86_REGISTER_GENERAL_PURPOSE_RDX; goto done;
				CASENOCASE('b'): result = X86_REGISTER_GENERAL_PURPOSE_RBX; goto done;
				default: break;
				}
				break;

			CASENOCASE('p'):
				switch (name[0]) {
				CASENOCASE('s'): result = X86_REGISTER_GENERAL_PURPOSE_RSP; goto done;
				CASENOCASE('b'): result = X86_REGISTER_GENERAL_PURPOSE_RBP; goto done;
				CASENOCASE('i'): result = X86_REGISTER_MISC_RIP; goto done;
				default: break;
				}
				break;

			CASENOCASE('i'):
				switch (name[0]) {
				CASENOCASE('s'): result = X86_REGISTER_GENERAL_PURPOSE_RSI; goto done;
				CASENOCASE('d'): result = X86_REGISTER_GENERAL_PURPOSE_RDI; goto done;
				default: break;
				}
				break;

			CASENOCASE('d'):
				switch (name[0]) {
				CASENOCASE('8'): result = X86_REGISTER_GENERAL_PURPOSE_R8D; goto done;
				CASENOCASE('9'): result = X86_REGISTER_GENERAL_PURPOSE_R9D; goto done;
				default: break;
				}
				break;

			CASENOCASE('w'):
				switch (name[0]) {
				CASENOCASE('8'): result = X86_REGISTER_GENERAL_PURPOSE_R8W; goto done;
				CASENOCASE('9'): result = X86_REGISTER_GENERAL_PURPOSE_R9W; goto done;
				default: break;
				}
				break;

			CASENOCASE('l'):
				switch (name[0]) {
				CASENOCASE('8'): result = X86_REGISTER_GENERAL_PURPOSE_R8L; goto done;
				CASENOCASE('9'): result = X86_REGISTER_GENERAL_PURPOSE_R9L; goto done;
				default: break;
				}
				break;

			case '0' ... '5':
				if (name[0] == '1') {
					result = X86_REGISTER_GENERAL_PURPOSE_R10 + (name[1] - '0');
					goto done;
				}
				break;

			default:
				break;
			}
		}
		if (namelen == 1) {
			switch (name[0]) {

			case '8':
				result = X86_REGISTER_GENERAL_PURPOSE_R8;
				goto done;

			case '9':
				result = X86_REGISTER_GENERAL_PURPOSE_R9;
				goto done;

			default:
				break;
			}
		}
		if (namelen == 5 &&
		    EQNOCASE(name[0], 'f') && EQNOCASE(name[1], 'l') &&
		    EQNOCASE(name[2], 'a') && EQNOCASE(name[3], 'g') &&
		    EQNOCASE(name[4], 's')) {
			result = X86_REGISTER_MISC_RFLAGS;
			goto done;
		}
	}
#endif /* __x86_64__ */
	if (EQNOCASE(name[0], 'e')) {
#ifndef __x86_64__
	do_pax:
#endif /* !__x86_64__ */
		++name;
		--namelen;
		if (namelen == 2) {
			switch (name[1]) {

			CASENOCASE('x'):
				switch (name[0]) {
				CASENOCASE('a'): result = X86_REGISTER_GENERAL_PURPOSE_EAX; goto done;
				CASENOCASE('c'): result = X86_REGISTER_GENERAL_PURPOSE_ECX; goto done;
				CASENOCASE('d'): result = X86_REGISTER_GENERAL_PURPOSE_EDX; goto done;
				CASENOCASE('b'): result = X86_REGISTER_GENERAL_PURPOSE_EBX; goto done;
				default: break;
				}
				break;

			CASENOCASE('p'):
				switch (name[0]) {
				CASENOCASE('s'): result = X86_REGISTER_GENERAL_PURPOSE_ESP; goto done;
				CASENOCASE('b'): result = X86_REGISTER_GENERAL_PURPOSE_EBP; goto done;
				CASENOCASE('i'): result = X86_REGISTER_MISC_EIP; goto done;
				default: break;
				}
				break;

			CASENOCASE('i'):
				switch (name[0]) {
				CASENOCASE('s'): result = X86_REGISTER_GENERAL_PURPOSE_ESI; goto done;
				CASENOCASE('d'): result = X86_REGISTER_GENERAL_PURPOSE_EDI; goto done;
				default: break;
				}
				break;

			default:
				break;
			}
		}
		if (namelen == 5 &&
		    EQNOCASE(name[0], 'f') && EQNOCASE(name[1], 'l') &&
		    EQNOCASE(name[2], 'a') && EQNOCASE(name[3], 'g') &&
		    EQNOCASE(name[4], 's')) {
			result = X86_REGISTER_MISC_EFLAGS;
			goto done;
		}
	}

	if (namelen == 2) {
		switch (name[1]) {

		CASENOCASE('l'):
			switch (name[0]) {
			CASENOCASE('a'): result = X86_REGISTER_GENERAL_PURPOSE_AL; goto done;
			CASENOCASE('c'): result = X86_REGISTER_GENERAL_PURPOSE_CL; goto done;
			CASENOCASE('d'): result = X86_REGISTER_GENERAL_PURPOSE_DL; goto done;
			CASENOCASE('b'): result = X86_REGISTER_GENERAL_PURPOSE_BL; goto done;
			default: break;
			}
			break;

		CASENOCASE('h'):
			switch (name[0]) {
			CASENOCASE('a'): result = X86_REGISTER_GENERAL_PURPOSE_AH; goto done;
			CASENOCASE('c'): result = X86_REGISTER_GENERAL_PURPOSE_CH; goto done;
			CASENOCASE('d'): result = X86_REGISTER_GENERAL_PURPOSE_DH; goto done;
			CASENOCASE('b'): result = X86_REGISTER_GENERAL_PURPOSE_BH; goto done;
			default: break;
			}
			break;

		CASENOCASE('s'):
			switch (name[0]) {
			CASENOCASE('e'): result = X86_REGISTER_SEGMENT_ES; goto done;
			CASENOCASE('c'): result = X86_REGISTER_SEGMENT_CS; goto done;
			CASENOCASE('s'): result = X86_REGISTER_SEGMENT_SS; goto done;
			CASENOCASE('d'): result = X86_REGISTER_SEGMENT_DS; goto done;
			CASENOCASE('f'): result = X86_REGISTER_SEGMENT_FS; goto done;
			CASENOCASE('g'): result = X86_REGISTER_SEGMENT_GS; goto done;
			default: break;
			}
			break;

		CASENOCASE('x'):
			switch (name[0]) {
			CASENOCASE('a'): result = X86_REGISTER_GENERAL_PURPOSE_AX; goto done;
			CASENOCASE('c'): result = X86_REGISTER_GENERAL_PURPOSE_CX; goto done;
			CASENOCASE('d'): result = X86_REGISTER_GENERAL_PURPOSE_DX; goto done;
			CASENOCASE('b'): result = X86_REGISTER_GENERAL_PURPOSE_BX; goto done;
			default: break;
			}
			break;

		CASENOCASE('p'):
			switch (name[0]) {
			CASENOCASE('s'): result = X86_REGISTER_GENERAL_PURPOSE_SP; goto done;
			CASENOCASE('b'): result = X86_REGISTER_GENERAL_PURPOSE_BP; goto done;
			CASENOCASE('i'): result = X86_REGISTER_MISC_IP; goto done;
			default: break;
			}
			break;

		CASENOCASE('i'):
			switch (name[0]) {
			CASENOCASE('s'): result = X86_REGISTER_GENERAL_PURPOSE_SI; goto done;
			CASENOCASE('d'): result = X86_REGISTER_GENERAL_PURPOSE_DI; goto done;
			default: break;
			}
			break;

		CASENOCASE('r'):
			switch (name[0]) {
			CASENOCASE('t'): result = X86_REGISTER_MISC_TR; goto done;
			default: break;
			}
			break;

		default:
			break;
		}
	}

	if (namelen == 3 &&
	    EQNOCASE(name[0], 'c') &&
	    EQNOCASE(name[1], 'r') &&
	    ((name[2] >= '0' && name[2] <= '4' && name[2] != '1')
	     IF64(|| name[2] == '8'))) {
		result = X86_REGISTER_CONTROL_CR0 + (name[2] - '0');
		goto done;
	}
	if (namelen == 3 &&
	    EQNOCASE(name[0], 's') &&
	    EQNOCASE(name[1], 't') &&
	    (name[2] >= '0' && name[2] <= '7')) {
		result = X86_REGISTER_FLOAT_ST0 + (name[2] - '0');
		goto done;
	}
	if (namelen == 5 &&
	    EQNOCASE(name[0], 's') &&
	    EQNOCASE(name[1], 't') &&
	    (name[2] == '(') &&
	    /* TODO: Allow white-space as in `st ( 0 )'
	     *                            here: ^ ^ ^ */
	    (name[3] >= '0' && name[3] <= '7') &&
	    (name[4] == ')')) {
		result = X86_REGISTER_FLOAT_ST0 + (name[3] - '0');
		goto done;
	}
	if (namelen == 3 &&
	    EQNOCASE(name[0], 'm') &&
	    EQNOCASE(name[1], 'm') &&
	    (name[2] >= '0' && name[2] <= '7')) {
		result = X86_REGISTER_MMX_MM0 + (name[2] - '0');
		goto done;
	}
	if (namelen == 4 && EQNOCASE(name[0], 'x') &&
	    EQNOCASE(name[1], 'm') && EQNOCASE(name[2], 'm') &&
	    (name[3] >= '0' && name[3] <= IFELSE3264('7', '9'))) {
		result = X86_REGISTER_XMM_XMM0 + (name[3] - '0');
		goto done;
	}
#ifdef __x86_64__
	if (namelen == 5 &&
	    EQNOCASE(name[0], 'x') && EQNOCASE(name[1], 'm') &&
	    EQNOCASE(name[2], 'm') && name[3] == '1' &&
	    (name[4] >= '0' && name[4] <= '4')) {
		result = X86_REGISTER_XMM_XMM0 + (name[4] - '0');
		goto done;
	}
#endif /* __x86_64__ */
	if (namelen == 4 && EQNOCASE(name[0], 'y') &&
	    EQNOCASE(name[1], 'm') && EQNOCASE(name[2], 'm') &&
	    (name[3] >= '0' && name[3] <= IFELSE3264('7', '9'))) {
		result = X86_REGISTER_YMM_YMM0 + (name[3] - '0');
		goto done;
	}
#ifdef __x86_64__
	if (namelen == 5 &&
	    EQNOCASE(name[0], 'y') && EQNOCASE(name[1], 'm') &&
	    EQNOCASE(name[2], 'm') && name[3] == '1' &&
	    (name[4] >= '0' && name[4] <= '4')) {
		result = X86_REGISTER_YMM_YMM0 + (name[4] - '0');
		goto done;
	}
#endif /* __x86_64__ */
	if (namelen == 3 &&
	    EQNOCASE(name[0], 'd') &&
	    EQNOCASE(name[1], 'r') &&
	    (name[2] >= '0' && name[2] <= '7' &&
	     name[2] != '4' && name[2] != '5')) {
		result = X86_REGISTER_DEBUG_DR0 + (name[2] - '0');
		goto done;
	}
	if (namelen == 5 &&
	    EQNOCASE(name[0], 'f') && EQNOCASE(name[1], 'l') &&
	    EQNOCASE(name[2], 'a') && EQNOCASE(name[3], 'g') &&
	    EQNOCASE(name[4], 's')) {
		result = X86_REGISTER_MISC_FLAGS;
		goto done;
	}
	if (namelen >= 3 && EQNOCASE(name[1], 'd') && EQNOCASE(name[2], 't')) {
		if ((namelen == 3 && EQNOCASE(name[0], 'l')) ||
		    (namelen == 4 && EQNOCASE(name[0], 'l') && EQNOCASE(name[3], 'r'))) {
			result = X86_REGISTER_MISC_LDT;
			goto done;
		}
		if (namelen >= 8 &&
		    (EQNOCASE(name[0], 'g') || EQNOCASE(name[0], 'i'))) {
			bool is_gdt = EQNOCASE(name[0], 'g');
			name += 3;
			namelen -= 3;
			SKIP_LEADING_SPACE();
			if unlikely(!namelen)
				goto unknown;
			if (name[0] != '.')
				goto unknown;
			++name;
			--namelen;
			SKIP_LEADING_SPACE();
			/* %gdt.limit, %gdt.base */
			/* %idt.limit, %idt.base */
			if (namelen == 5 && EQNOCASE(name[0], 'l') &&
			    EQNOCASE(name[1], 'i') && EQNOCASE(name[2], 'm') &&
			    EQNOCASE(name[3], 'i') && EQNOCASE(name[4], 't')) {
				result = is_gdt ? X86_REGISTER_MISC_GDT_LIMIT
				                : X86_REGISTER_MISC_IDT_LIMIT;
				goto done;
			}
			if (namelen >= 4 &&
			    EQNOCASE(name[0], 'b') && EQNOCASE(name[1], 'a') &&
			    EQNOCASE(name[2], 's') && EQNOCASE(name[3], 'e')) {
				if (namelen == 4) {
					result = is_gdt ? X86_REGISTER_MISC_GDT_BASE
					                : X86_REGISTER_MISC_IDT_BASE;
					goto done;
				}
				if (namelen == 5 && EQNOCASE(name[4], 'l')) {
					result = is_gdt ? X86_REGISTER_MISC_GDT_BASEL
					                : X86_REGISTER_MISC_IDT_BASEL;
					goto done;
				}
#ifdef __x86_64__
				if (namelen == 5 && EQNOCASE(name[4], 'q')) {
					result = is_gdt ? X86_REGISTER_MISC_GDT_BASEQ
					                : X86_REGISTER_MISC_IDT_BASEQ;
					goto done;
				}
#endif /* __x86_64__ */
			}

		}
	}

#ifdef __x86_64__
	if (namelen == 3 && EQNOCASE(name[2], 'l')) {
		switch (name[1]) {

		CASENOCASE('p'):
			switch (name[0]) {
			CASENOCASE('s'): result = X86_REGISTER_GENERAL_PURPOSE_SPL; goto done;
			CASENOCASE('b'): result = X86_REGISTER_GENERAL_PURPOSE_BPL; goto done;
			default: break;
			}
			break;

		CASENOCASE('i'):
			switch (name[0]) {
			CASENOCASE('s'): result = X86_REGISTER_GENERAL_PURPOSE_SIL; goto done;
			CASENOCASE('d'): result = X86_REGISTER_GENERAL_PURPOSE_DIL; goto done;
			default: break;
			}
			break;

		default: break;
		}
	}
#endif /* __x86_64__ */

	/* (fs|gs).base */
	if (namelen >= 7 &&
	    (EQNOCASE(name[0], 'f') || EQNOCASE(name[0], 'g')) &&
	    EQNOCASE(name[1], 's') && name[2] == '.' &&
	    EQNOCASE(name[3], 'b') && EQNOCASE(name[4], 'a') &&
	    EQNOCASE(name[5], 's') && EQNOCASE(name[6], 'e')) {
		result = EQNOCASE(name[0], 'f')
		         ? (X86_REGISTER_MISC_FSBASE & ~X86_REGISTER_SIZEMASK)
		         : (X86_REGISTER_MISC_GSBASE & ~X86_REGISTER_SIZEMASK);
		if (namelen == 7) {
			flags |= X86_REGISTER_SIZEMASK_PBYTE;
			goto done;
		}
		if (namelen == 8) {
			if (EQNOCASE(name[7], 'l')) {
				flags |= X86_REGISTER_SIZEMASK_4BYTE;
				goto done;
			}
#ifdef __x86_64__
			if (EQNOCASE(name[7], 'q')) {
				flags |= X86_REGISTER_SIZEMASK_8BYTE;
				goto done;
			}
#endif /* __x86_64__ */
		}
	}

	/* (fs|gs)base */
	if (namelen >= 6 &&
	    (EQNOCASE(name[0], 'f') || EQNOCASE(name[0], 'g')) &&
	    EQNOCASE(name[1], 's') && EQNOCASE(name[2], 'b') &&
	    EQNOCASE(name[3], 'a') && EQNOCASE(name[4], 's') &&
	    EQNOCASE(name[5], 'e')) {
		result = EQNOCASE(name[0], 'f')
		         ? (X86_REGISTER_MISC_FSBASE & ~X86_REGISTER_SIZEMASK)
		         : (X86_REGISTER_MISC_GSBASE & ~X86_REGISTER_SIZEMASK);
		if (namelen == 6) {
			flags |= X86_REGISTER_SIZEMASK_PBYTE;
			goto done;
		}
		if (namelen == 7) {
			if (EQNOCASE(name[6], 'l')) {
				flags |= X86_REGISTER_SIZEMASK_4BYTE;
				goto done;
			}
#ifdef __x86_64__
			if (EQNOCASE(name[6], 'q')) {
				flags |= X86_REGISTER_SIZEMASK_8BYTE;
				goto done;
			}
#endif /* __x86_64__ */
		}
	}

	if (namelen >= 3 && EQNOCASE(name[0], 'f')) {
		switch (name[1]) {

		CASENOCASE('c'):
			if (namelen == 3) {
				switch (name[2]) {
				CASENOCASE('w'): result = X86_REGISTER_MISC_FCW; goto done;
				CASENOCASE('s'): result = X86_REGISTER_MISC_FCS; goto done;
				default: break;
				}
			}
			break;

		CASENOCASE('s'):
			if (namelen == 3) {
				switch (name[2]) {
				CASENOCASE('w'): result = X86_REGISTER_MISC_FSW; goto done;
				default: break;
				}
			}
			break;

		CASENOCASE('t'):
			if (EQNOCASE(name[2], 'w')) {
				if (namelen == 3) {
					result = X86_REGISTER_MISC_FTW;
					goto done;
				}
				if (namelen == 4 && EQNOCASE(name[3], 'x')) {
					result = X86_REGISTER_MISC_FTWX;
					goto done;
				}
			}
			break;

		CASENOCASE('o'):
			if (namelen == 3) {
				switch (name[2]) {
				CASENOCASE('p'): result = X86_REGISTER_MISC_FOP; goto done;
				default: break;
				}
			}
			break;

		CASENOCASE('i'):
			if (EQNOCASE(name[2], 'p')) {
				if (namelen == 3) {
					result = X86_REGISTER_MISC_FIP;
					goto done;
				}
				if (namelen == 4) {
					if (EQNOCASE(name[3], 'l')) {
						result = X86_REGISTER_MISC_FIPL;
						goto done;
					}
#ifdef __x86_64__
					if (EQNOCASE(name[3], 'q')) {
						result = X86_REGISTER_MISC_FIPQ;
						goto done;
					}
#endif /* __x86_64__ */
				}
			}
			break;

		CASENOCASE('d'):
			if (EQNOCASE(name[2], 'p')) {
				if (namelen == 3) {
					result = X86_REGISTER_MISC_FDP;
					goto done;
				}
				if (namelen == 4) {
					if (EQNOCASE(name[3], 'l')) {
						result = X86_REGISTER_MISC_FDPL;
						goto done;
					}
#ifdef __x86_64__
					if (EQNOCASE(name[3], 'q')) {
						result = X86_REGISTER_MISC_FDPQ;
						goto done;
					}
#endif /* __x86_64__ */
				}
			}
			break;

		default:
			break;
		}
	}

	if (namelen >= 5 && EQNOCASE(name[0], 'm') &&
	    EQNOCASE(name[1], 'x') && EQNOCASE(name[2], 'c') &&
	    EQNOCASE(name[3], 's') && EQNOCASE(name[4], 'r')) {
		if (namelen == 5) {
			result = X86_REGISTER_MISC_MXCSR;
			goto done;
		}
		if (namelen == 10 && EQNOCASE(name[5], '_') &&
		    EQNOCASE(name[6], 'm') && EQNOCASE(name[7], 'a') &&
		    EQNOCASE(name[8], 's') && EQNOCASE(name[9], 'k')) {
			result = X86_REGISTER_MISC_MXCSR_MASK;
			goto done;
		}
	}

#ifdef __x86_64__
	/* kernel_gsbase, kernel_gs.base */
	if (namelen >= 13 &&
	    EQNOCASE(name[0], 'k') && EQNOCASE(name[1], 'e') &&
	    EQNOCASE(name[2], 'r') && EQNOCASE(name[3], 'n') &&
	    EQNOCASE(name[4], 'e') && EQNOCASE(name[5], 'l') &&
	    EQNOCASE(name[6], '_') && EQNOCASE(name[7], 'g') &&
	    EQNOCASE(name[8], 's')) {
		char const *temp = name + 9;
		size_t templen   = namelen - 9;
		if (*temp == '.') {
			++temp;
			--templen;
		}
		if (templen >= 4 &&
		    EQNOCASE(temp[0], 'b') && EQNOCASE(temp[1], 'a') &&
		    EQNOCASE(temp[2], 's') && EQNOCASE(temp[3], 'e')) {
			if (templen == 4) {
				result = X86_REGISTER_MISC_KGSBASE;
				goto done;
			}
			if (templen == 5) {
				if (EQNOCASE(temp[4], 'l')) {
					result = X86_REGISTER_MISC_KGSBASEL;
					goto done;
				}
				if (EQNOCASE(temp[4], 'q')) {
					result = X86_REGISTER_MISC_KGSBASEQ;
					goto done;
				}
			}
		}
	}
#endif /* __x86_64__ */
#undef SKIP_LEADING_SPACE

unknown:
	return X86_REGISTER_NONE;
done:
	result |= flags;
	return result;
}


DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_REGISTER_BY_NAME_C */
