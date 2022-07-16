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
#ifdef __INTELLISENSE__
#include "../emulate.c.inl"
#endif /* __INTELLISENSE__ */

EMU86_INTELLISENSE_BEGIN(cpuid) {

#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#if EMU86_EMULATE_CONFIG_WANT_CPUID
case EMU86_OPCODE_ENCODE(0x0fa2): {
	/* 0F A2     CPUID     Returns  processor identification and feature information to the
	 *                     EAX, EBX, ECX, and EDX registers, as determined by input entered
	 *                     in EAX (in some cases, ECX as well). */
#ifdef EMU86_EMULATE_HANDLE_CPUID
	/* Allow for custom expressions for handling _all_ CPUID leaves. */
	EMU86_EMULATE_HANDLE_CPUID();
#else /* EMU86_EMULATE_HANDLE_CPUID */
	u32 eax;

#ifndef EMU86_EMULATE_CPUID_BRAND_STRING_WORD
#ifndef EMU86_EMULATE_CPUID_BRAND_STRING_DECL
#ifndef EMU86_EMULATE_CPUID_BRAND_STRING
#define EMU86_EMULATE_CPUID_BRAND_STRING                       \
	{                                                          \
		'K', 'O', 'S', ' ', 'l', 'i', 'b', 'e', 'm', 'u', '8', \
		'6', ' ', 'e', 'm', 'u', 'l', 'a', 't', 'o', 'r', ' ', \
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', \
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '  \
	}
#endif /* !EMU86_EMULATE_CPUID_BRAND_STRING */
	PRIVATE ATTR_ALIGNED(4) char const emu86_brandstring[48] = EMU86_EMULATE_CPUID_BRAND_STRING;
#define EMU86_EMULATE_CPUID_BRAND_STRING_DECL  emu86_brandstring
#endif /* !EMU86_EMULATE_CPUID_BRAND_STRING_DECL */
#define EMU86_EMULATE_CPUID_BRAND_STRING_WORD(i) \
	((uint32_t const *)EMU86_EMULATE_CPUID_BRAND_STRING_DECL)[i]
#endif /* !EMU86_EMULATE_CPUID_BRAND_STRING_WORD */

	/* TODO: Add `EMU86_EMULATE_CONFIG_WANT_*' checks to all feature bitsets! */

	eax = EMU86_GETEAX();
	if (eax & 0x80000000) {
		switch (eax) {

		case 0x80000000:
			EMU86_SETEAX(0x80000004); /* Max supported leaf */
			goto cpuid_setinfo0_noeax;

		case 0x80000001: {
			enum {
				ECX_FEATURES = CPUID_80000001C_ABM |
				               CPUID_80000001C_3DNOWPREFETCH |
				               CPUID_80000001C_TBM |
				               0,
				EDX_FEATURES = CPUID_80000001D_CMOV |
#ifdef EMU86_EMULATE_RETURN_AFTER_SYSCALL
				               CPUID_80000001D_SYSCALL |
#endif /* EMU86_EMULATE_RETURN_AFTER_SYSCALL */
#if EMU86_EMULATE_CONFIG_WANT_CMPXCHG8B && defined(EMU86_MEM_ATOMIC_CMPXCHQ)
				               CPUID_80000001D_CX8 |
#endif /* EMU86_EMULATE_CONFIG_WANT_CMPXCHG8B && EMU86_MEM_ATOMIC_CMPXCHQ */
				               0,
			};
			EMU86_SETEAX(0);
			EMU86_SETEBX(0);
			EMU86_SETECX(ECX_FEATURES);
			EMU86_SETEDX(EDX_FEATURES);
		}	break;

		case 0x80000002:
			EMU86_SETEAX(EMU86_EMULATE_CPUID_BRAND_STRING_WORD(0));
			EMU86_SETEBX(EMU86_EMULATE_CPUID_BRAND_STRING_WORD(1));
			EMU86_SETECX(EMU86_EMULATE_CPUID_BRAND_STRING_WORD(2));
			EMU86_SETEDX(EMU86_EMULATE_CPUID_BRAND_STRING_WORD(3));
			break;
		case 0x80000003:
			EMU86_SETEAX(EMU86_EMULATE_CPUID_BRAND_STRING_WORD(4));
			EMU86_SETEBX(EMU86_EMULATE_CPUID_BRAND_STRING_WORD(5));
			EMU86_SETECX(EMU86_EMULATE_CPUID_BRAND_STRING_WORD(6));
			EMU86_SETEDX(EMU86_EMULATE_CPUID_BRAND_STRING_WORD(7));
			break;
		default:
			/* DEFAULT: Return the same information as the greatest supported leaf */
		case 0x80000004:
			EMU86_SETEAX(EMU86_EMULATE_CPUID_BRAND_STRING_WORD(8));
			EMU86_SETEBX(EMU86_EMULATE_CPUID_BRAND_STRING_WORD(9));
			EMU86_SETECX(EMU86_EMULATE_CPUID_BRAND_STRING_WORD(10));
			EMU86_SETEDX(EMU86_EMULATE_CPUID_BRAND_STRING_WORD(11));
			break;
		}
	} else {
		switch (eax) {

		case 0:
			EMU86_SETEAX(7); /* Max supported leaf */
cpuid_setinfo0_noeax:
			EMU86_SETEBX(ENCODE_INT32('G', 'e', 'n', 'u'));
			EMU86_SETEDX(ENCODE_INT32('i', 'n', 'e', 'I'));
			EMU86_SETECX(ENCODE_INT32('n', 't', 'e', 'l'));
			break;

		case 1: {
			enum {
				ECX_FEATURES = CPUID_1C_MOVBE |
				               CPUID_1C_POPCNT |
#if LIBEMU86_CONFIG_WANT_64BIT && EMU86_EMULATE_CONFIG_WANT_CMPXCHG16B && defined(EMU86_MEM_ATOMIC_CMPXCHX)
				               CPUID_1C_CX16 |
#endif /* LIBEMU86_CONFIG_WANT_64BIT && EMU86_EMULATE_CONFIG_WANT_CMPXCHG16B && EMU86_MEM_ATOMIC_CMPXCHX */
				               0,
				EDX_FEATURES = CPUID_1D_CMOV |
				               CPUID_1D_CLFSH |
#ifdef EMU86_EMULATE_RETURN_AFTER_SYSENTER
				               CPUID_1D_SEP |
#endif /* EMU86_EMULATE_RETURN_AFTER_SYSENTER */
#if EMU86_EMULATE_CONFIG_WANT_CMPXCHG8B && defined(EMU86_MEM_ATOMIC_CMPXCHQ)
				               CPUID_1D_CX8 |
#endif /* EMU86_EMULATE_CONFIG_WANT_CMPXCHG8B && EMU86_MEM_ATOMIC_CMPXCHQ */
				               0,
			};
			EMU86_SETEAX(((UINT32_C(3) << CPUID_1A_STEPPING_S) & CPUID_1A_STEPPING_M) |
			             ((UINT32_C(6) << CPUID_1A_MODEL_S) & CPUID_1A_MODEL_M) |
			             ((UINT32_C(6) << CPUID_1A_FAMILY_S) & CPUID_1A_FAMILY_M) |
			             ((UINT32_C(0) << CPUID_1A_PROCTYPE_S) & CPUID_1A_PROCTYPE_M) |
			             ((UINT32_C(0) << CPUID_1A_EXMODEL_S) & CPUID_1A_EXMODEL_M) |
			             ((UINT32_C(0) << CPUID_1A_EXFAMILY_S) & CPUID_1A_EXFAMILY_M));
			EMU86_SETEBX(0x00000800); /* ??? */
			EMU86_SETECX(ECX_FEATURES);
			EMU86_SETEDX(EDX_FEATURES);
		}	break;

		default:
			/* DEFAULT: Return the same information as the greatest supported leaf */
		case 7: {
			enum {
				EBX_FEATURES = CPUID_7B_CLFLUSHOPT |
				               CPUID_7B_CLWB |
				               CPUID_7B_FSGSBASE | /* TODO: Optional */
				               0,
				ECX_FEATURES = CPUID_7C_PREFETCHWT1 |
				               0,
			};
			EMU86_SETEAX(0);
			EMU86_SETEBX(EBX_FEATURES);
			EMU86_SETECX(ECX_FEATURES);
			EMU86_SETEDX(0);
		}	break;

		}
	}
#endif /* !EMU86_EMULATE_HANDLE_CPUID */
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case EMU86_OPCODE_ENCODE(0x0fa2):
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */

}
EMU86_INTELLISENSE_END
