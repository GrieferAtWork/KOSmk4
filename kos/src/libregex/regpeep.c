/*[[[magic
options["COMPILE.language"] = "c";
local gcc_opt = options.setdefault("GCC.options", []);
gcc_opt.removeif([](x) -> x.startswith("-O"));
// Actually: want to optimize to minimize stack memory usage, but this is the next-best thing
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
#ifndef GUARD_LIBREGEX_REGPEEP_C
#define GUARD_LIBREGEX_REGPEEP_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1
#define LIBREGEX_WANT_PROTOTYPES

#include "api.h"
/**/
#include <hybrid/compiler.h>

#include <hybrid/unaligned.h>

#include <kos/types.h>

#include <alloca.h>
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <unicode.h>

#include <libregex/regcomp.h>

#include "regcomp.h"
#include "regpeep.h"

#if 0
#include <sys/syslog.h>
#define HAVE_TRACE
#define TRACE(...) syslog(LOG_DEBUG, __VA_ARGS__)
#else
#define TRACE(...) (void)0
#endif

DECL_BEGIN

#define tswap(T, a, b)   \
	do {                 \
		T _temp = (b);   \
		(b)     = (a);   \
		(a)     = _temp; \
	}	__WHILE0

/* Check if 2 range overlap. */
#define RANGES_OVERLAP(r1_min, r1_max, r2_min, r2_max) \
	((r1_max) >= (r2_min) && (r2_max) >= (r1_min))

#define getb()      (*pc++)
#define getw()      (pc += 2, (int16_t)UNALIGNED_GET16((uint16_t const *)(pc - 2)))
#define int16_at(p) (*(int16_t *)(p))

INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) byte_t * /* from "./regcomp.c" */
NOTHROW_NCX(CC libre_opcode_next)(byte_t const *__restrict p_instr);

struct re_mini_interpreter {
	byte_t const                    *rmi_pc;         /* [1..1] PC for current instruction */
	byte_t const                    *rmi_endpc;      /* [1..1] Hard program end pointer */
	byte_t const                    *rmi_exact_data; /* [?..1] Data pointer for EXACT-like opcodes */
	uint8_t                          rmi_exact_nrem; /* # of remaining elements in `rmi_exact_data' */
	COMPILER_FLEXIBLE_ARRAY(uint8_t, rmi_vars); /* Values for code variables. */
};

#define _re_mini_interpreter_sizeof(nvars) \
	(offsetof(struct re_mini_interpreter, rmi_vars) + (nvars) * sizeof(uint8_t))
#define re_mini_interpreter_alloc(nvars) \
	((struct re_mini_interpreter *)alloca(_re_mini_interpreter_sizeof(nvars)))
#define re_mini_interpreter_init(self, pc, endpc) \
	(void)((self)->rmi_pc = (pc), (self)->rmi_endpc = (endpc), (self)->rmi_exact_nrem = 0)

/* Check if the interpreter is part-way into an EXACT-like opcode */
#define re_mini_interpreter_inpartialexact(self) \
	((self)->rmi_exact_nrem != 0)

/* Skip opcodes that don't relate to input matching, or otherwise
 * require special handling  (such as bi-branching  instructions)
 *
 * Also hard-stops if `self->rmi_endpc' is reached.
 * @return: * :              The currently loaded opcode
 * @return: REOP_MATCHED:    End-of-instruction-stream (or `rmi_endpc' reached)
 * @return: REOP_JMP_ONFAIL: At a bi-branch opcode (`int16_at(self->rmi_pc)' is the relevant delta)
 */
PRIVATE NONNULL((1)) byte_t
NOTHROW_NCX(CC re_mini_interpreter_getopcode)(struct re_mini_interpreter *__restrict self) {
	byte_t opcode;
	byte_t const *pc = self->rmi_pc;
again:
	if (pc == self->rmi_endpc) {
		opcode = REOP_MATCHED;
		goto done;
	}
	opcode = *pc++;
	switch (opcode) {

	case REOP_EXACT:
	case REOP_EXACT_ASCII_ICASE:
	case REOP_EXACT_UTF8_ICASE:
		if (self->rmi_exact_nrem == 0) {
			self->rmi_exact_data = pc + 1;
			self->rmi_exact_nrem = *pc;
			assert(self->rmi_exact_nrem > 0);
		}
		--pc;
		goto done;

	case REOP_GROUP_START:
	case REOP_GROUP_END:
	case REOP_GROUP_END_JMIN ... REOP_GROUP_END_JMAX:
		/* Don't care about groups */
		++pc;
		goto again;

	case REOP_AT_MIN ... REOP_AT_MAX:
		/* REOP_AT_* opcodes aren't enough to say for certain that branches never match.
		 * There are some cases where they could say so (e.g. when both branches specify
		 * AT-instructions that mutually exclusive), but  that's too complicated for  us
		 * to really care. */
		goto again;

	case REOP_POP_ONFAIL:
	case REOP_JMP_ONFAIL_DUMMY:
	case REOP_NOP:
		goto again;

	case REOP_POP_ONFAIL_AT:
	case REOP_JMP_ONFAIL_DUMMY_AT:
		pc += 2;
		goto again;

	case REOP_JMP: {
		int16_t delta;
		/* Unconditional jumps can just be followed */
		delta = getw();
		pc += delta;
		goto again;
	}

	case REOP_JMP_AND_RETURN_ONFAIL:
		opcode = REOP_JMP_ONFAIL;
		goto done;

	case REOP_DEC_JMP: {
		/* This is why we're implementing variables! */
		byte_t varid = getb();
		int16_t delta = getw();
		if (self->rmi_vars[varid] != 0) {
			--self->rmi_vars[varid];
			pc += delta;
		}
		goto again;
	}

	case REOP_DEC_JMP_AND_RETURN_ONFAIL: {
		byte_t varid = getb();
		pc += 2; /* delta */
		if (self->rmi_vars[varid] != 0) {
			--self->rmi_vars[varid];
			/* In this scenario, the instruction is bi-branching! */
			pc -= 3; /* Act like the varid was `REOP_JMP_AND_RETURN_ONFAIL' */
			opcode = REOP_JMP_ONFAIL;
			goto done;
		}
		goto again;
	}

	case REOP_SETVAR: {
		byte_t varid = getb();
		byte_t value = getb();
		self->rmi_vars[varid] = value;
		goto again;
	}

	case REOP_MATCHED_PERFECT:
		/* Normalize to `REOP_MATCHED' */
		opcode = REOP_MATCHED;
		--pc;
		goto done;

	default:
		/* Matching opcode (let the caller deal with this) */
		--pc;
		goto done;
	}
	__builtin_unreachable();
done:
	self->rmi_pc = pc;
	return opcode;
}

PRIVATE WUNUSED NONNULL((1, 2, 3)) bool
NOTHROW_NCX(CC input_can_match_both_ex)(struct re_code const *code,
                                        struct re_mini_interpreter *int1,
                                        struct re_mini_interpreter *int2) {
	/* Process and compare opcodes from our 2 interpreters. */
	struct re_mini_interpreter *int1_copy;
	struct re_mini_interpreter *int2_copy;
	byte_t opcode1, opcode2;
#define swap_interpreters()                                        \
	do {                                                           \
		tswap(byte_t, opcode1, opcode2);                            \
		tswap(struct re_mini_interpreter *, int1_copy, int2_copy); \
	}	__WHILE0

	int1_copy = NULL;
	int2_copy = NULL;
again:
	opcode1 = re_mini_interpreter_getopcode(int1);
	opcode2 = re_mini_interpreter_getopcode(int2);

	/* Check for bi-branch */
	if (opcode1 == REOP_JMP_ONFAIL) {
		/* Must check both branches. */
		byte_t const *pc1, *pc2;
		pc1 = int1->rmi_pc + 3;
		pc2 = pc1 + int16_at(pc1 - 2);
		if (int1_copy == NULL)
			int1_copy = re_mini_interpreter_alloc(code->rc_nvars);
		if (int2_copy == NULL)
			int2_copy = re_mini_interpreter_alloc(code->rc_nvars);
		memcpy(int1_copy, int1, _re_mini_interpreter_sizeof(code->rc_nvars));
		memcpy(int2_copy, int2, _re_mini_interpreter_sizeof(code->rc_nvars));
		int1_copy->rmi_pc = pc2;
		if (input_can_match_both_ex(code, int1_copy, int2_copy))
			return true;
		int1->rmi_pc = pc1;
		goto again;
	}
	if (opcode2 == REOP_JMP_ONFAIL) {
		/* Must check both branches. */
		byte_t const *pc1, *pc2;
		pc1 = int2->rmi_pc + 3;
		pc2 = pc1 + int16_at(pc1 - 2);
		if (int1_copy == NULL)
			int1_copy = re_mini_interpreter_alloc(code->rc_nvars);
		if (int2_copy == NULL)
			int2_copy = re_mini_interpreter_alloc(code->rc_nvars);
		memcpy(int1_copy, int1, _re_mini_interpreter_sizeof(code->rc_nvars));
		memcpy(int2_copy, int2, _re_mini_interpreter_sizeof(code->rc_nvars));
		int2_copy->rmi_pc = pc2;
		if (input_can_match_both_ex(code, int1_copy, int2_copy))
			return true;
		int2->rmi_pc = pc1;
		goto again;
	}

	if (opcode1 != opcode2) {
		if (opcode1 == REOP_MATCHED || opcode2 == REOP_MATCHED) {
			/* One of the 2 interpreters reached its end before the other.
			 * -> Because of different length-requirements, it's  impossible
			 *    for any kind of input to exist that matches both branches! */
			return false;
		}
	} else {
		byte_t const *int1_nextpc, *int2_nextpc;
		/* Same opcodes */
		if (opcode1 == REOP_MATCHED)
			return true; /* Both branches reached their end simultaneously -> bi-matching input does exist */

		/* Special case: it's literally the same instruction */
		if unlikely(int1->rmi_pc == int2->rmi_pc)
			return true;

		/* Check if both branches use the exact same instruction.
		 * If so,  then  skip  ahead  to  the  next  instruction.
		 *
		 * Note that we can only do this when not partially into an exact-data opcode
		 */
		if (!re_mini_interpreter_inpartialexact(int1) &&
		    !re_mini_interpreter_inpartialexact(int2)) {
			int1_nextpc = libre_opcode_next(int1->rmi_pc);
			int2_nextpc = libre_opcode_next(int2->rmi_pc);
			if (((size_t)(int1_nextpc - int1->rmi_pc) == (size_t)(int2_nextpc - int2->rmi_pc)) &&
			    bcmp(int1->rmi_pc, int2->rmi_pc, (size_t)(int1_nextpc - int1->rmi_pc)) == 0) {
				/* Literally the same instruction, so just look at what comes after. */
				int1->rmi_pc = int1_nextpc;
				int2->rmi_pc = int2_nextpc;
				goto again;
			}
		}
	}

	/* Actually compare stuff matched by opcodes:
	 * - REOP_EXACT
	 * - REOP_EXACT_ASCII_ICASE
	 * - REOP_EXACT_UTF8_ICASE
	 * - REOP_ANY_MIN ... REOP_ANY_MAX   (for simplicity, we treat all of these as `REOP_ANY')
	 * - REOP_BYTE
	 * - REOP_NBYTE
	 * - REOP_BYTE2
	 * - REOP_NBYTE2
	 * - REOP_RANGE
	 * - REOP_NRANGE
	 * - REOP_CONTAINS_UTF8
	 * - REOP_NCONTAINS_UTF8
	 * - REOP_CS_UTF8
	 * - REOP_CS_BYTE
	 * - REOP_NCS_UTF8
	 */
	switch (opcode1) {

	case REOP_ANY_MIN ... REOP_ANY_MAX:
		int1->rmi_pc += 1;
		switch (opcode2) {

		case REOP_EXACT:
		case REOP_EXACT_ASCII_ICASE:
			if (!int2->rmi_exact_nrem)
				goto int2_after_exact_data;
			++int2->rmi_exact_data;
			--int2->rmi_exact_nrem;
			goto again;

		case REOP_EXACT_UTF8_ICASE:
			if (!int2->rmi_exact_nrem)
				goto int2_after_exact_data;
			int2->rmi_exact_data += unicode_utf8seqlen[*int2->rmi_exact_data];
			--int2->rmi_exact_nrem;
			goto again;

		case REOP_ANY_MIN ... REOP_ANY_MAX:
		case REOP_BYTE:
		case REOP_NBYTE:
		case REOP_BYTE2:
		case REOP_NBYTE2:
		case REOP_RANGE:
		case REOP_NRANGE:
		case REOP_CONTAINS_UTF8:
		case REOP_NCONTAINS_UTF8:
		case REOP_CS_UTF8:
		case REOP_CS_BYTE:
		case REOP_NCS_UTF8:
			int2->rmi_pc = libre_opcode_next(int2->rmi_pc);
			goto again;

		default: break;
		}
		goto can_match_both;

	case REOP_EXACT:
		if (!int1->rmi_exact_nrem)
			goto int1_after_exact_data;
		switch (opcode2) {

		case REOP_EXACT:
			for (;;) {
				byte_t int1_exact_byte;
				byte_t int2_exact_byte;
				if (!int1->rmi_exact_nrem)
					goto int1_after_exact_data;
				if (!int2->rmi_exact_nrem)
					goto int2_after_exact_data;
				int1_exact_byte = *int1->rmi_exact_data++;
				int2_exact_byte = *int2->rmi_exact_data++;
				if (int1_exact_byte != int2_exact_byte)
					return false; /* Miss-matching exact sequence */
				--int1->rmi_exact_nrem;
				--int2->rmi_exact_nrem;
			}
			__builtin_unreachable();

		case REOP_EXACT_ASCII_ICASE:
compare_ascii_icase_exact:
			for (;;) {
				byte_t int1_exact_byte;
				byte_t int2_exact_byte;
				if (!int1->rmi_exact_nrem)
					goto int1_after_exact_data;
				if (!int2->rmi_exact_nrem)
					goto int2_after_exact_data;
				int1_exact_byte = *int1->rmi_exact_data++;
				int2_exact_byte = *int2->rmi_exact_data++;
				if (int1_exact_byte != int2_exact_byte) {
					int1_exact_byte = (byte_t)tolower(int1_exact_byte);
					int2_exact_byte = (byte_t)tolower(int2_exact_byte);
					if (int1_exact_byte != int2_exact_byte)
						return false; /* Miss-matching exact sequence */
				}
				--int1->rmi_exact_nrem;
				--int2->rmi_exact_nrem;
			}
			__builtin_unreachable();

		case REOP_EXACT_UTF8_ICASE:
compare_ascii_utf8_icase_exact:
			for (;;) {
				byte_t int1_exact_byte;
				char32_t int2_exact_utf8;
				if (!int1->rmi_exact_nrem)
					goto int1_after_exact_data;
				if (!int2->rmi_exact_nrem)
					goto int2_after_exact_data;
				int1_exact_byte = *int1->rmi_exact_data++;
				int2_exact_utf8 = unicode_readutf8((char const **)&int2->rmi_exact_data);
				if (int1_exact_byte != int2_exact_utf8) {
					int1_exact_byte = (byte_t)tolower(int1_exact_byte);
					int2_exact_utf8 = unicode_tolower(int2_exact_utf8);
					if (int1_exact_byte != int2_exact_utf8)
						return false; /* Miss-matching exact sequence */
				}
				--int1->rmi_exact_nrem;
				--int2->rmi_exact_nrem;
			}
			__builtin_unreachable();

		case REOP_ANY_MIN ... REOP_ANY_MAX:
			++int1->rmi_exact_data;
			--int1->rmi_exact_nrem;
			++int2->rmi_pc;
			goto again;

		case REOP_BYTE:
		case REOP_NBYTE:
		case REOP_BYTE2:
		case REOP_NBYTE2:
		case REOP_RANGE:
		case REOP_NRANGE: {
			byte_t b1;
			b1 = *int1->rmi_exact_data++;
			--int1->rmi_exact_nrem;
			switch (opcode2) {
			case REOP_BYTE: {
				byte_t b2;
				++int2->rmi_pc;
				b2 = *int2->rmi_pc++;
				if (b1 != b2)
					return false; /* "(f|[g])" -> no input can match both */
				goto again;
			}
			case REOP_NBYTE: {
				byte_t b2;
				b2 = *int2->rmi_pc++;
				if (b1 == b2)
					return false; /* "(f|[^f])" -> no input can match both */
				goto again;
			}
			case REOP_BYTE2: {
				byte_t b2_1, b2_2;
				++int2->rmi_pc;
				b2_1 = *int2->rmi_pc++;
				b2_2 = *int2->rmi_pc++;
				if (b1 != b2_1 && b1 != b2_2)
					return false; /* "(f|[gh])" -> no input can match both */
				goto again;
			}
			case REOP_NBYTE2: {
				byte_t b2_1, b2_2;
				++int2->rmi_pc;
				b2_1 = *int2->rmi_pc++;
				b2_2 = *int2->rmi_pc++;
				if (b1 == b2_1 || b1 == b2_2)
					return false; /* "(f|[^f])" -> no input can match both */
				goto again;
			}
			case REOP_RANGE: {
				byte_t b2_1, b2_2;
				++int2->rmi_pc;
				b2_1 = *int2->rmi_pc++;
				b2_2 = *int2->rmi_pc++;
				if (b1 < b2_1 || b1 > b2_2)
					return false; /* "(f|[g-z])" -> no input can match both */
				goto again;
			}
			case REOP_NRANGE: {
				byte_t b2_1, b2_2;
				++int2->rmi_pc;
				b2_1 = *int2->rmi_pc++;
				b2_2 = *int2->rmi_pc++;
				if (b1 >= b2_1 && b1 <= b2_2)
					return false; /* "(f|[^e-g])" -> no input can match both */
				goto again;
			}
			default: __builtin_unreachable();
			}
		}

		case REOP_CONTAINS_UTF8:
		case REOP_NCONTAINS_UTF8:
		case REOP_CS_UTF8:
		case REOP_CS_BYTE:
		case REOP_NCS_UTF8:
			/* TODO */

		default: break;
		}
		goto can_match_both;

	case REOP_EXACT_ASCII_ICASE:
		if (!int1->rmi_exact_nrem)
			goto int1_after_exact_data;
		switch (opcode2) {

		case REOP_EXACT:
		case REOP_EXACT_ASCII_ICASE:
			goto compare_ascii_icase_exact;

		case REOP_EXACT_UTF8_ICASE:
			goto compare_ascii_utf8_icase_exact;

		case REOP_ANY_MIN ... REOP_ANY_MAX:
			++int1->rmi_exact_data;
			--int1->rmi_exact_nrem;
			int2->rmi_pc += 1;
			goto again;

		case REOP_BYTE:
		case REOP_NBYTE:
		case REOP_BYTE2:
		case REOP_NBYTE2:
		case REOP_RANGE:
		case REOP_NRANGE:
		case REOP_CONTAINS_UTF8:
		case REOP_NCONTAINS_UTF8:
		case REOP_CS_UTF8:
		case REOP_CS_BYTE:
		case REOP_NCS_UTF8:
			/* TODO */

		default: break;
		}
		goto can_match_both;

	case REOP_EXACT_UTF8_ICASE:
		if (!int1->rmi_exact_nrem)
			goto int1_after_exact_data;
		switch (opcode2) {

		case REOP_EXACT:
		case REOP_EXACT_ASCII_ICASE:
			swap_interpreters();
			goto compare_ascii_utf8_icase_exact;

		case REOP_EXACT_UTF8_ICASE:
			goto compare_ascii_icase_exact;

		case REOP_ANY_MIN ... REOP_ANY_MAX:
			int1->rmi_exact_data += unicode_utf8seqlen[*int1->rmi_exact_data];
			--int1->rmi_exact_nrem;
			int2->rmi_pc += 1;
			goto again;

		case REOP_BYTE:
		case REOP_NBYTE:
		case REOP_BYTE2:
		case REOP_NBYTE2:
		case REOP_RANGE:
		case REOP_NRANGE:
		case REOP_CONTAINS_UTF8:
		case REOP_NCONTAINS_UTF8:
		case REOP_CS_UTF8:
		case REOP_CS_BYTE:
		case REOP_NCS_UTF8:
			/* TODO */

		default: break;
		}
		goto can_match_both;

	case REOP_BYTE:
	case REOP_NBYTE:
	case REOP_BYTE2:
	case REOP_NBYTE2:
	case REOP_RANGE:
	case REOP_NRANGE:
	case REOP_CONTAINS_UTF8:
	case REOP_NCONTAINS_UTF8:
	case REOP_CS_UTF8:
	case REOP_CS_BYTE:
	case REOP_NCS_UTF8:
		/* TODO */

	default:
		goto can_match_both;
	}

can_match_both:

	/* Safety-case: assume that input _can_ match both sides */
	return true;
int1_after_exact_data:
	int1->rmi_pc = int1->rmi_exact_data;
	goto again;
int2_after_exact_data:
	int2->rmi_pc = int2->rmi_exact_data;
	goto again;
}


/* Check if input exists that can match both code at `pc1' and `pc2'
 * @param: pc_end: PC for the (sub-)expression end address. We're allowed  to
 *                 assume that when either `pc1'  or `pc2' hits this  address
 *                 (but not at the same time), on all possible branches, then
 *                 no input exists that can match both branches.
 *                 Example: "b?" -> no input can both match "b" and the epsilon-branch
 * @return: true:  Yes, such input _does_ in deed exist (or it might if unsure).
 * @return: false: No, it's always one or the other. */
PRIVATE WUNUSED NONNULL((1, 2, 3, 4)) bool
NOTHROW_NCX(CC input_can_match_both)(struct re_code const *code,
                                     byte_t const *pc1,
                                     byte_t const *pc2,
                                     byte_t const *pc_end) {
	struct re_mini_interpreter *int1;
	struct re_mini_interpreter *int2;
	int1 = re_mini_interpreter_alloc(code->rc_nvars);
	int2 = re_mini_interpreter_alloc(code->rc_nvars);
	re_mini_interpreter_init(int1, pc1, pc_end);
	re_mini_interpreter_init(int2, pc2, pc_end);
	return input_can_match_both_ex(code, int1, int2);
}

/* Find the next unbalanced `REOP_MAYBE_POP_ONFAIL' opcode. */
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1)) byte_t *
NOTHROW_NCX(CC find_unbalanced_maybe_pop_onfail)(byte_t const *pc) {
	unsigned int onfail_recursion;
	byte_t opcode;
	onfail_recursion = 0;
dispatch:
	opcode = getb();
	switch (opcode) {

	case REOP_POP_ONFAIL:
		assert(onfail_recursion != 0);
		--onfail_recursion;
		goto dispatch;

	case REOP_MAYBE_POP_ONFAIL:
		if (onfail_recursion == 0)
			return (byte_t *)pc - 1;
		--onfail_recursion;
		goto dispatch;

	case REOP_JMP_ONFAIL_DUMMY_AT:
	case REOP_JMP_ONFAIL: {
		int16_t delta = getw();
		if (delta >= 0) {
			/* Follow the on-fail branch so the delta doesn't increase. */
			pc += delta;
			goto dispatch;
		}
		/* Don't follow the delta (we don't want to go  backwards),
		 * but because of that, need to increase on-fail recursion. */
		++onfail_recursion;
		goto dispatch;
	}

	case REOP_JMP: {
		/* Mandatory jump -> need to follow */
		int16_t delta = getw();
		pc += delta;
		goto dispatch;
	}

	case REOP_JMP_AND_RETURN_ONFAIL:
	case REOP_DEC_JMP_AND_RETURN_ONFAIL:
		/* Don't want to have to increase `onfail_recursion', so don't follow */
	default:
		pc = libre_opcode_next(pc - 1);
		goto dispatch;
	}
	__builtin_unreachable();
}


#define PEEP_ONFAIL_STACK_F_NORMAL            0x0000 /* Normal flags */
#define PEEP_ONFAIL_STACK_F_UNBALANCED_ONFAIL 0x0001 /* Flag: a  variable number of on-fail items may
                                                      *       get left behind after the code was run. */

/* Perform onfail-stack peephole optimization on the given pc-range.
 * It  is assumed that the given range forms a singular basic-block,
 * in that all code-paths within the range eventually converge  back
 * at `pc_end' */
PRIVATE NONNULL((1, 2, 3)) unsigned int
NOTHROW_NCX(CC peep_onfail_stack)(struct re_code *code,
                                  byte_t *pc,
                                  byte_t *pc_end) {
	unsigned int result;
	byte_t opcode;
	result = PEEP_ONFAIL_STACK_F_NORMAL;
dispatch:
	if (pc >= pc_end)
		return result;
	opcode = getb();
	switch (opcode) {

#ifndef NDEBUG
	case REOP_MAYBE_POP_ONFAIL:
		assert_failed("Should not have encountered `REOP_MAYBE_POP_ONFAIL' on its own");
		__builtin_unreachable();
#endif /* !NDEBUG */

	case REOP_JMP_ONFAIL_DUMMY_AT:
	case REOP_JMP_ONFAIL: {
		unsigned int inner_flags;
		bool bimatch_possible;
		byte_t *expr_start, *expr_end, *onfail_pc;
		int16_t delta = getw();
		assertf(delta >= 0, "Compiler should only ever generate position offsets for `REOP_JMP_ONFAIL[_DUMMY]'");

		/* In all code-generation cases, `REOP_JMP_ONFAIL' is always followed
		 * by a code-block "<X>", which we now have to find the end of, so we
		 * can optimize it.
		 *
		 * This can easily be done by finding the next unbalanced `REOP_MAYBE_POP_ONFAIL' */
		expr_start = pc;
		onfail_pc  = pc + delta;
		expr_end   = find_unbalanced_maybe_pop_onfail(expr_start);
		assert(*expr_end == REOP_MAYBE_POP_ONFAIL);
		assert(expr_end < pc_end);
		inner_flags = peep_onfail_stack(code, expr_start, expr_end); /* Recursively optimize */
		result |= inner_flags;

		/* Figure out how we should replace the trailing `REOP_MAYBE_POP_ONFAIL' */
		bimatch_possible = input_can_match_both(code, expr_start, onfail_pc, pc_end);
		if (bimatch_possible) {
			/* Even after the non-failing branch has been matched, it is still possible
			 * for input to be constructed such that we'll need to roll-back to run the
			 * second branch -> as such, we can't pop the fail-stack here. */
			if (opcode == REOP_JMP_ONFAIL_DUMMY_AT) {
				pc[-3] = REOP_NOP;
				pc[-2] = REOP_NOP;
				pc[-1] = REOP_NOP;
			}
			*expr_end++ = REOP_NOP;
			*expr_end++ = REOP_NOP;
			*expr_end++ = REOP_NOP;

			/* By needing to leave behind items, the on-fail stack becomes unpredictable. */
			result |= PEEP_ONFAIL_STACK_F_UNBALANCED_ONFAIL;
		} else {
			/* Having reached `expr_end', and after matching the contained expression,
			 * it is guarantied that no input can still be matching the other  branch.
			 *
			 * As such, we can pop on-fail items until we hit the one that was originally
			 * pushed by the `REOP_JMP_ONFAIL' above. */
			if (inner_flags & PEEP_ONFAIL_STACK_F_UNBALANCED_ONFAIL) {
				/* Need to encode the more complicated `REOP_POP_ONFAIL_AT' opcode. */
				*expr_end++ = REOP_POP_ONFAIL_AT;
				int16_at(expr_end) = (int16_t)(onfail_pc - (expr_end + 2));
				expr_end += 2;
			} else {
				/* Can encode the simple `REOP_POP_ONFAIL' opcode. */
				/* XXX: This sequence could be inserted  as early as the opcode  following
				 *      which  `input_can_match_both()' noticed the  inability of the non-
				 *      fail  branch ever matching the fail-branch (but only when the non-
				 *      fail branch didn't branch yet again  before that point; if it  did
				 *      that, then this sequence would need to be inserted in every branch
				 *      that exists in the non-fail-branch,  but also only if those  inner
				 *      branches are exclusive to one-another; else the on-fail items  for
				 *      those  branches mustn't be popped; it gets complicated, so for now
				 *      this right here should be enough)
				 * example: "a([[:alpha:]]X[bB]|[[:lower:]]Y[bB])c"
				 *    >>     REOP_BYTE       "a"
				 *    >>     REOP_GROUP_START 0
				 *    >>     REOP_JMP_ONFAIL 1f
				 *    >>     REOP_CS_UTF8    [RECS_ISALPHA, RECS_DONE]
				 *    >>     REOP_BYTE       "X"
				 *    >> #   REOP_POP_ONFAIL // OPTIMAL POSITION
				 *    >>     REOP_CS_UTF8    [RECS_CHAR2 "bB"]
				 *    >> #   REOP_POP_ONFAIL // OUR POSITION
				 *    >>     REOP_JMP        2f
				 *    >> 1:  REOP_CS_UTF8    [RECS_ISLOWER, RECS_DONE]
				 *    >>     REOP_BYTE       "Y"
				 *    >>     REOP_CS_UTF8    [RECS_CHAR2 "bB"]
				 *    >> 2:  REOP_GROUP_END  0
				 *    >>     REOP_BYTE       "c"
				 */
				if (opcode == REOP_JMP_ONFAIL_DUMMY_AT) {
					/* Don't need to identify frame, so can use more compact encoding! */
					pc[-3] = REOP_JMP_ONFAIL_DUMMY;
					pc[-2] = REOP_NOP;
					pc[-1] = REOP_NOP;
				}
				*expr_end++ = REOP_POP_ONFAIL;
				*expr_end++ = REOP_NOP;
				*expr_end++ = REOP_NOP;
			}
		}
		pc = expr_end;
		goto dispatch;
	}

	case REOP_JMP: {
		/* Do jump-threading, and delete jumps with 0-offsets */
		ptrdiff_t total_delta;
		int16_t delta = getw();
		byte_t *target_pc;
		target_pc = pc + delta;
		while (*target_pc == REOP_JMP) {
			++target_pc;
			delta     = int16_at(target_pc);
			target_pc = target_pc + 2 + delta;
		}
		total_delta = target_pc - pc;
		if (total_delta == 0) {
			pc[-3] = REOP_NOP;
			pc[-2] = REOP_NOP;
			pc[-1] = REOP_NOP;
			goto dispatch;
		}
		if (total_delta > INT16_MIN && total_delta < INT16_MAX)
			int16_at(pc - 2) = (int16_t)total_delta;
		goto dispatch;
	}	break;

	default:
		/* Note how we don't follow `REOP_JMP' or `REOP_DEC_JMP' here!
		 *
		 * That's because we're no a logic-analyzer, but only here to locate
		 * positions that */
		pc = libre_opcode_next(pc - 1);
		goto dispatch;
	}
	__builtin_unreachable();
}


/* Delete instruction code bytes. */
PRIVATE NONNULL((1, 2)) void
NOTHROW_NCX(CC libre_compiler_delcode)(struct re_compiler *__restrict self,
                                       byte_t *delpc, size_t num_bytes) {
	byte_t *pc, opcode;
	byte_t *del_minpc = delpc;
	byte_t *del_maxpc = delpc + num_bytes - 1;
	assert(num_bytes >= 1);

	/* Adjust relative jumps that go across the deleted range. */
	pc = ((struct re_code *)self->rec_cbase)->rc_code;
again:
	opcode = getb();
	switch (opcode) {

	case REOP_GROUP_MATCH_JMIN ... REOP_GROUP_MATCH_JMAX:
	case REOP_GROUP_END_JMIN ... REOP_GROUP_END_JMAX: {
		byte_t old_delta, new_delta;
		byte_t *skip_maxpc;
		old_delta = (opcode >= REOP_GROUP_MATCH_JMIN && opcode <= REOP_GROUP_MATCH_JMAX)
		             ? REOP_GROUP_MATCH_Joff(opcode)
		             : REOP_GROUP_END_Joff(opcode);
		skip_maxpc = pc + old_delta - 1;
		if (RANGES_OVERLAP(pc, skip_maxpc, del_minpc, del_maxpc)) {
			/* Figure out how many trailing bytes of the jump are being deleted.
			 * Consider the following 2 cases:
			 * >>     jmp     1f
			 * >>     DELME1
			 * >> 1:  DELME2
			 *
			 * >>     jmp     1f
			 * >>     DELME
			 * >>     KEEPME1
			 * >> 1:  KEEPME2
			 */
			if (del_maxpc <= skip_maxpc) {
				/* Deleted range is entirely contained in skipped area */
				new_delta = old_delta - (byte_t)num_bytes;
			} else {
				/* Deleted range extends past end of jump-area
				 * -> As such, the jump must go to the start of the deleted area */
				assert((del_minpc - pc) >= 3);
				new_delta = (byte_t)(del_minpc - pc);
			}
			pc[-1] -= old_delta;
			pc[-1] += new_delta;
			assert((pc[-1] >= REOP_GROUP_MATCH_JMIN && pc[-1] <= REOP_GROUP_MATCH_JMAX) ||
			       (pc[-1] >= REOP_GROUP_END_JMIN && pc[-1] <= REOP_GROUP_END_JMAX));
		}
		++pc; /* gid */
		goto again;
	}

	case REOP_DEC_JMP:
	case REOP_DEC_JMP_AND_RETURN_ONFAIL:
		pc += 1;
		ATTR_FALLTHROUGH
	case REOP_POP_ONFAIL_AT:
	case REOP_JMP_ONFAIL:
	case REOP_JMP_ONFAIL_DUMMY_AT:
	case REOP_JMP:
	case REOP_JMP_AND_RETURN_ONFAIL: {
		int16_t old_delta;
		byte_t *skip_minpc, *skip_maxpc;

		/* `*pc' points at a 16-bit relative jump-offset */
		old_delta = int16_at(pc);
		pc += 2;
		if (old_delta < 0) {
			skip_maxpc = pc - 1;
			skip_minpc = pc + old_delta;
			assert(skip_minpc <= skip_maxpc);
			if (!RANGES_OVERLAP(skip_minpc, skip_maxpc, del_minpc, del_maxpc))
				goto again;
			/* Figure out how many leading bytes of the jump are being deleted.
			 * Consider the following 2 cases:
			 * >>     DELME1
			 * >> 1:  DELME2
			 * >>     jmp     1b
			 *
			 * >> 1:  KEEPME1
			 * >>     DELME
			 * >>     KEEPME2
			 * >>     jmp     1b
			 */
			if (del_minpc >= skip_minpc) {
				/* The entire delete-range lies within the area skipped over by the jump */
				int16_at(pc - 2) += num_bytes;
			} else {
				int16_at(pc - 2) = (int16_t)((del_maxpc + 1) - pc);
			}
		} else if (old_delta > 0) {
			skip_minpc = pc;
			skip_maxpc = pc + old_delta - 1;
			assert(skip_minpc <= skip_maxpc);
			if (!RANGES_OVERLAP(skip_minpc, skip_maxpc, del_minpc, del_maxpc))
				goto again;
			/* Figure out how many trailing bytes of the jump are being deleted.
			 * Consider the following 2 cases:
			 * >>     jmp     1f
			 * >>     DELME1
			 * >> 1:  DELME2
			 *
			 * >>     jmp     1f
			 * >>     DELME
			 * >>     KEEPME1
			 * >> 1:  KEEPME2
			 */
			if (del_maxpc <= skip_maxpc) {
				/* Deleted range is entirely contained in skipped area */
				int16_at(pc - 2) -= (byte_t)num_bytes;
			} else {
				/* Deleted range extends past end of jump-area
				 * -> As such, the jump must go to the start of the deleted area */
				int16_at(pc - 2) = (int16_t)(del_minpc - pc);
			}
		}
		goto again;
	}

	case REOP_MATCHED:
	case REOP_MATCHED_PERFECT:
		break;

	default:
		pc = libre_opcode_next(pc - 1);
		goto again;
	}

	/* Jump-offsets have been adjusted. - Now to actually removed data. */
	memmovedown(delpc,
	            delpc + num_bytes,
	            self->rec_cpos - (delpc + num_bytes));
	self->rec_cpos -= num_bytes;
}


/* Delete REOP_NOP opcodes */
PRIVATE NONNULL((1)) void
NOTHROW_NCX(CC libre_compiler_delnops)(struct re_compiler *__restrict self) {
	byte_t *pc, opcode;
	pc = ((struct re_code *)self->rec_cbase)->rc_code;
again:
	opcode = getb();
	switch (opcode) {

	case REOP_NOP: {
		size_t nopcount;
		--pc;
		nopcount = 1;
		while (pc[nopcount] == REOP_NOP)
			++nopcount;
		libre_compiler_delcode(self, pc, nopcount);
		/* Notice how we don't adjust `pc' here; that's
		 * because `*pc' now points at the next opcode! */
		goto again;
	}

	case REOP_MATCHED:
	case REOP_MATCHED_PERFECT:
		break;

	default:
		pc = libre_opcode_next(pc - 1);
		goto again;
	}

}



/* Apply peephole optimizations to the code produced by `self' */
INTERN NONNULL((1)) void
NOTHROW_NCX(CC libre_compiler_peephole)(struct re_compiler *__restrict self) {

	/* Insert `REOP_POP_ONFAIL' opcodes.
	 *
	 * Compare the matches of  bi-branches (e.g. `REOP_JMP_ONFAIL'). If  no
	 * input exists that can possibly match both branches, then the on-fail
	 * item can be popped at the point where this becomes a guaranty in the
	 * non-failing branch.
	 * -> Optimize "ab?c" -> once "ab" has been matched, there's no
	 *    point in keeping the on-fail item that could match input "ac",
	 *    since we already know that it could never match
	 *    >>     REOP_BYTE       "a"
	 *    >>     REOP_JMP_ONFAIL 1f
	 *    >>     REOP_BYTE       "b"
	 *    >>     REOP_POP_ONFAIL     // <<< It is our job to insert this opcode right here!
	 *    >> 1:  REOP_BYTE       "c"
	 * -> Optimize "a([[:alpha:]]X[bB]|[[:lower:]]Y[bB])c" Once  'X' has  been
	 *    matched in the first branch, it is a guaranty that the second branch
	 *    can never be matched (until then it wasn't, since input exists  that
	 *    can match both [[:alpha:]] and [[:lower:]]).
	 *    >>     REOP_BYTE       "a"
	 *    >>     REOP_GROUP_START 0
	 *    >>     REOP_JMP_ONFAIL 1f
	 *    >>     REOP_CS_UTF8    [RECS_ISALPHA, RECS_DONE]
	 *    >>     // NOTE: The POP_ONFAIL isn't be inserted here, because input
	 *    >>     //       exists that matches both `RECS_ISALPHA' and `RECS_ISLOWER'
	 *    >>     REOP_BYTE       "X"
	 *    >>     REOP_POP_ONFAIL // <<< It is our job to insert this opcode right here!
	 *    >>     REOP_CS_UTF8    [RECS_CHAR2 "bB"]
	 *    >>     REOP_JMP        2f
	 *    >> 1:  REOP_CS_UTF8    [RECS_ISLOWER, RECS_DONE]
	 *    >>     REOP_BYTE       "Y"
	 *    >>     REOP_CS_UTF8    [RECS_CHAR2 "bB"]
	 *    >> 2:  REOP_GROUP_END  0
	 *    >>     REOP_BYTE       "c"
	 * -> Care must be taken not to insert an `REOP_POP_ONFAIL' opcode AFTER
	 *    the failing and non-failing branches have already re-joined. (XXX:
	 *    why not let the compiler produce a filler  `REOP_MAYBE_POP_ONFAIL'
	 *    opcode if appropriate? We could  then replace/move that opcode  to
	 *    the earliest-most location, and  replace with `REOP_NOP' if  input
	 *    exists that matches both branches, or `REOP_POP_ONFAIL' if no such
	 *    input exists)
	 *
	 *
	 * If both branches always consume  the same number of  bytes/characters
	 * (prior to joining back together), then the non-failing branch can pop
	 * the on-fail item prior to re-joining.
	 * -> Optimize "a(foo|[Ff]oo)b" -> once "afoo" has been matched, there's no
	 *    point in keeping the on-fail item for "[Ff]oo". Even though it  could
	 *    also match input "afoob", it won't be  able to do so any better  than
	 *    the "foo" branch.
	 */
	peep_onfail_stack(((struct re_code *)self->rec_cbase),
	                  ((struct re_code *)self->rec_cbase)->rc_code,
	                  self->rec_cpos);

	/* Remove all NOP opcodes from the code-stream */
	libre_compiler_delnops(self);

	/* XXX: On host architectures without unaligned memory access, reflow generated
	 *      code by inserting `REOP_NOP' opcodes before instructions with unaligned
	 *      jump offsets.
	 *
	 * What makes this complicated is the fact that doing so can break  jump-offsets,
	 * meaning that such a mechanism would first have to identify all jumps, the make
	 * relocations for each of them, then go through and insert padding NOPs,  before
	 * finally re-applying relocations, thus fixing the jump-offsets it just broken.
	 *
	 * Furthermore, I'm not entirely certain if doing this would even be beneficial
	 * to  performance, as the extra NOPs must be just as slow as the unconditional
	 * unaligned reads currently done by `getw()' in "./regexec.c".
	 */
}

DECL_END

#endif /* !GUARD_LIBREGEX_REGPEEP_C */
