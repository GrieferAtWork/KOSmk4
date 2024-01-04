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
#ifndef GUARD_LIBINSTRLEN_INSTRLEN_C
#define GUARD_LIBINSTRLEN_INSTRLEN_C 1
#define _KOS_SOURCE 1
#define _KOS_KERNEL_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/except.h>
#include <kos/types.h>

#include <stddef.h>
#include <string.h>

#include <libinstrlen/instrlen.h>

#include "instrlen.h"

#ifndef __INTELLISENSE__
#ifdef ARCH_INSTRLEN_SOURCE_FILE
#include ARCH_INSTRLEN_SOURCE_FILE
#endif /* ARCH_INSTRLEN_SOURCE_FILE */
#endif /* !__INTELLISENSE__ */

DECL_BEGIN

#ifdef __KERNEL__
/* In kernel-space, also catch `E_WOULDBLOCK', as may be thrown by accessing
 * memory that hasn't been loaded  while preemption was disabled (since  the
 * kernel would not be allowed to block in such a scenario) */
#define WAS_SEGFAULT() (was_thrown(E_SEGFAULT) || was_thrown(E_WOULDBLOCK))
#else /* __KERNEL__ */
#define WAS_SEGFAULT() (was_thrown(E_SEGFAULT))
#endif /* !__KERNEL__ */


/* #define ARCH_HAVE_INSTRUCTION_LENGTH 1 */
/* #define ARCH_HAVE_INSTRUCTION_SUCC 1 */
/* #define ARCH_HAVE_INSTRUCTION_PRED 1 */
/* #define ARCH_HAVE_INSTRUCTION_TRYSUCC 1 */
/* #define ARCH_HAVE_INSTRUCTION_TRYPRED 1 */


/* Return the length of an instruction that starts at `pc'
 * WARNING: This function may trigger a segmentation fault when `pc' is an invalid pointer.
 * @return: 0 : The pointed-to instruction wasn't recognized. */
#ifndef ARCH_HAVE_INSTRUCTION_LENGTH
INTERN ATTR_PURE WUNUSED size_t
NOTHROW_NCX(CC libil_instruction_length)(void const *pc, isa_t isa) {
#ifdef ARCH_HAVE_INSTRUCTION_SUCC
	byte_t *next_pc;
	next_pc = libil_instruction_succ(pc, isa);
	if unlikely(!next_pc)
		return 0;
	return (size_t)(next_pc - (byte_t *)pc);
#elif defined(LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH)
	(void)pc;
	(void)isa;
	return LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH(isa);
#else /* ... */
#error "No way to implement `libil_instruction_length()'"
#endif /* !... */
}
#endif /* !ARCH_HAVE_INSTRUCTION_LENGTH */

/* Return a pointer to the successor/predecessor instruction of `pc',
 * assuming  that `pc'  points to  the start  of another instruction.
 * WARNING: These functions may trigger a segmentation fault when `pc' is an invalid pointer.
 * @param: isa: The ISA type (s.a. `Xcpustate_getisa()' or `ISA_DEFAULT')
 * @return: NULL: The pointed-to instruction wasn't recognized. */
#ifndef ARCH_HAVE_INSTRUCTION_SUCC
INTERN ATTR_PURE WUNUSED byte_t *
NOTHROW_NCX(CC libil_instruction_succ)(void const *pc, isa_t isa) {
#ifdef ARCH_HAVE_INSTRUCTION_LENGTH
	size_t length;
	length = libil_instruction_length(pc, isa);
	if unlikely(!length)
		return NULL;
	return (byte_t *)pc + length;
#elif defined(LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH)
	(void)isa;
	return (byte_t *)pc + LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH(isa);
#else /* ... */
#error "No way to implement `libil_instruction_succ()'"
#endif /* !... */
}
#endif /* !ARCH_HAVE_INSTRUCTION_SUCC */

#ifndef ARCH_HAVE_INSTRUCTION_PRED
#ifdef LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH
INTERN ATTR_PURE WUNUSED byte_t *
NOTHROW_NCX(CC libil_instruction_pred)(void const *pc, isa_t isa) {
	(void)isa;
	return (byte_t *)pc - LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH(isa);
}
#elif defined(ARCH_INSTRUCTION_MAXLENGTH)
/* # of instructions to back-track in order to verify that
 * some  given instruction point fits into the instruction
 * stream described by surrounding instructions. */
#ifndef LIBINSTRLEN_ARCH_INSTRUCTION_VERIFY_DISTANCE
#define LIBINSTRLEN_ARCH_INSTRUCTION_VERIFY_DISTANCE 16
#endif /* !LIBINSTRLEN_ARCH_INSTRUCTION_VERIFY_DISTANCE */

/* Return the length the longest valid instruction with a length <= maxlen that ends at `pc'
 * If no such instruction exists, return `0' instead. */
PRIVATE ATTR_PURE WUNUSED uint8_t
NOTHROW_NCX(CC predmaxone)(void const *pc, isa_t isa, uint8_t maxlen) {
	byte_t const *result;
	result = (byte_t const *)pc - maxlen;
#ifdef __NON_CALL_EXCEPTIONS
	TRY
#endif /* __NON_CALL_EXCEPTIONS */
	{
		for (; (uintptr_t)result < (uintptr_t)pc; ++result) {
			byte_t *nextptr;
			nextptr = libil_instruction_succ(result, isa);
			if (nextptr == (byte_t const *)pc)
				return (uint8_t)(size_t)((byte_t const *)pc - result);
		}
	}
#ifdef __NON_CALL_EXCEPTIONS
	EXCEPT {
		if unlikely(!WAS_SEGFAULT())
			RETHROW();
	}
#endif /* __NON_CALL_EXCEPTIONS */
	return 0;
}


INTERN ATTR_PURE WUNUSED byte_t *
NOTHROW_NCX(CC libil_instruction_pred)(void const *pc, isa_t isa) {
	byte_t const *iter, *lowest_iter;
	unsigned int i;
	uint8_t maxlen[LIBINSTRLEN_ARCH_INSTRUCTION_VERIFY_DISTANCE];
#ifdef __NON_CALL_EXCEPTIONS
	NESTED_EXCEPTION; /* Needed for the TRY in `predmaxone' */
#endif /* __NON_CALL_EXCEPTIONS */
	memset(maxlen, ARCH_INSTRUCTION_MAXLENGTH,
	       LIBINSTRLEN_ARCH_INSTRUCTION_VERIFY_DISTANCE,
	       sizeof(uint8_t));
	lowest_iter = (byte_t const *)pc;
	iter        = (byte_t const *)pc;
	for (i = 0; i < LIBINSTRLEN_ARCH_INSTRUCTION_VERIFY_DISTANCE; ++i) {
		uint8_t length;
find_shorter_instructions:
		length = predmaxone(iter, isa, maxlen[i]);
		if (!length) {
			/* Try to go back and find a shorter instruction. */
			while (i) {
				maxlen[i] = ARCH_INSTRUCTION_MAXLENGTH;
				--i;
				iter += maxlen[i];
				--maxlen[i];
				if (maxlen[i] != 0)
					goto find_shorter_instructions;
			}
			goto done_backtrack;
		}
		maxlen[i] = length;
		iter -= length;
		if (lowest_iter > iter)
			lowest_iter = iter;
	}
done_backtrack:
	if (lowest_iter >= (byte_t const *)pc)
		return NULL; /* No base-reference found... */
	/* Find  the  start  of the  first  instruction that
	 * ends at `>= pc', but starts at `>= rev_iter_curr' */
	iter = lowest_iter;
	for (;;) {
		byte_t const *next;
		next = libil_instruction_succ(iter, isa);
		if (!next)
			break; /* No such instruction... */
		if (next >= pc)
			return (byte_t *)iter; /* Found it! */
		iter = next;
	}
	return NULL;
}
#else /* ... */
#error "No way to implement `libil_instruction_pred()'"
#endif /* !... */
#endif /* !ARCH_HAVE_INSTRUCTION_PRED */



/* Same as above, but handle E_SEGFAULT (and E_WOULDBLOCK in kernel-space) by returning `NULL'
 * Other  exceptions are propagated normally (which could  happen due to VIO access emulation)
 * @param: isa: The ISA type (s.a. `Xcpustate_getisa()' or `ISA_DEFAULT') */
#ifndef ARCH_HAVE_INSTRUCTION_SUCC_NX
INTERN ATTR_PURE WUNUSED byte_t *
NOTHROW_NCX(CC libil_instruction_succ_nx)(void const *pc, isa_t isa) {
	byte_t *result;
#ifdef __NON_CALL_EXCEPTIONS
	NESTED_TRY
#endif /* __NON_CALL_EXCEPTIONS */
	{
		result = libil_instruction_succ(pc, isa);
	}
#ifdef __NON_CALL_EXCEPTIONS
	EXCEPT {
		if unlikely(!WAS_SEGFAULT())
			RETHROW();
		result = NULL;
	}
#endif /* __NON_CALL_EXCEPTIONS */
	return result;
}
#endif /* !ARCH_HAVE_INSTRUCTION_SUCC_NX */

#ifndef ARCH_HAVE_INSTRUCTION_PRED_NX
INTERN ATTR_PURE WUNUSED byte_t *
NOTHROW_NCX(CC libil_instruction_pred_nx)(void const *pc, isa_t isa) {
	byte_t *result;
#ifdef __NON_CALL_EXCEPTIONS
	NESTED_TRY
#endif /* __NON_CALL_EXCEPTIONS */
	{
		result = libil_instruction_pred(pc, isa);
	}
#ifdef __NON_CALL_EXCEPTIONS
	EXCEPT {
		if unlikely(!WAS_SEGFAULT())
			RETHROW();
		result = NULL;
	}
#endif /* __NON_CALL_EXCEPTIONS */
	return result;
}
#endif /* !ARCH_HAVE_INSTRUCTION_PRED_NX */



/* Same as `instruction_(succ|pred)_nx', but return pc +/- 1 instead of NULL.
 * @param: isa: The ISA type (s.a. `Xcpustate_getisa()' or `ISA_DEFAULT') */
#ifndef ARCH_HAVE_INSTRUCTION_TRYSUCC
INTERN ATTR_PURE ATTR_RETNONNULL WUNUSED byte_t *
NOTHROW_NCX(CC libil_instruction_trysucc)(void const *pc, isa_t isa) {
	byte_t *result;
	result = libil_instruction_succ_nx(pc, isa);
	if unlikely(!result)
		result = (byte_t *)pc + 1;
	return result;
}
#endif /* !ARCH_HAVE_INSTRUCTION_TRYSUCC */

#ifndef ARCH_HAVE_INSTRUCTION_TRYPRED
INTERN ATTR_PURE ATTR_RETNONNULL WUNUSED byte_t *
NOTHROW_NCX(CC libil_instruction_trypred)(void const *pc, isa_t isa) {
	byte_t *result;
	result = libil_instruction_pred_nx(pc, isa);
	if unlikely(!result)
		result = (byte_t *)pc - 1;
	return result;
}
#endif /* !ARCH_HAVE_INSTRUCTION_TRYPRED */



#ifndef ARCH_HAVE_INSTRUCTION_LENGTH
DEFINE_PUBLIC_ALIAS(instruction_length, libil_instruction_length);
#endif /* !ARCH_HAVE_INSTRUCTION_LENGTH */

#ifndef ARCH_HAVE_INSTRUCTION_SUCC
DEFINE_PUBLIC_ALIAS(instruction_succ, libil_instruction_succ);
#endif /* !ARCH_HAVE_INSTRUCTION_SUCC */

#ifndef ARCH_HAVE_INSTRUCTION_PRED
DEFINE_PUBLIC_ALIAS(instruction_pred, libil_instruction_pred);
#endif /* !ARCH_HAVE_INSTRUCTION_PRED */

#ifndef ARCH_HAVE_INSTRUCTION_SUCC_NX
DEFINE_PUBLIC_ALIAS(instruction_succ_nx, libil_instruction_succ_nx);
#endif /* !ARCH_HAVE_INSTRUCTION_SUCC_NX */

#ifndef ARCH_HAVE_INSTRUCTION_PRED_NX
DEFINE_PUBLIC_ALIAS(instruction_pred_nx, libil_instruction_pred_nx);
#endif /* !ARCH_HAVE_INSTRUCTION_PRED_NX */

#ifndef ARCH_HAVE_INSTRUCTION_TRYSUCC
DEFINE_PUBLIC_ALIAS(instruction_trysucc, libil_instruction_trysucc);
#endif /* !ARCH_HAVE_INSTRUCTION_TRYSUCC */

#ifndef ARCH_HAVE_INSTRUCTION_TRYPRED
DEFINE_PUBLIC_ALIAS(instruction_trypred, libil_instruction_trypred);
#endif /* !ARCH_HAVE_INSTRUCTION_TRYPRED */

DECL_END

#endif /* !GUARD_LIBINSTRLEN_INSTRLEN_C */
