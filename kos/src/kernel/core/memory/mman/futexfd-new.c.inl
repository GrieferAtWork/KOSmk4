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
#include "futexfd.c"
#define DEFINE_mfutexfd_new
//#define DEFINE_compat_mfutexfd_new
#endif /* __INTELLISENSE__ */

#if (defined(DEFINE_mfutexfd_new) + \
     defined(DEFINE_compat_mfutexfd_new)) != 1
#error "Must #define exactly one of these"
#endif /* ... */

#include <kernel/user.h>

#include <hybrid/align.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>

#include <stddef.h>

DECL_BEGIN

#ifdef DEFINE_compat_mfutexfd_new
#define LOCAL_sizeof_pointer    __ARCH_COMPAT_SIZEOF_POINTER
#define LOCAL_mfutexfd_new      compat_mfutexfd_new
#define LOCAL_struct_lfutexexpr struct compat_lfutexexpr
#else /* DEFINE_compat_mfutexfd_new */
#define LOCAL_sizeof_pointer    __SIZEOF_POINTER__
#define LOCAL_mfutexfd_new      mfutexfd_new
#define LOCAL_struct_lfutexexpr struct lfutexexpr
#endif /* !DEFINE_compat_mfutexfd_new */

/* Create a new futexfd object.
 * @throw: E_INSUFFICIENT_RIGHTS: Tried to exceed `mfutexfd_maxexpr' w/o `CAP_SYS_RESOURCE' */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mfutexfd *FCALL
LOCAL_mfutexfd_new(REF struct mfutex *__restrict futex,
                   USER UNCHECKED void *base,
                   USER CHECKED LOCAL_struct_lfutexexpr const *expr)
		THROWS(E_BADALLOC, E_SEGFAULT, E_INSUFFICIENT_RIGHTS) {
	REF struct mfutexfd *result;
	size_t count = 0;
	while (expr[count].fe_condition != LFUTEX_EXPREND) {
		++count;
		if (count >= mfutexfd_maxexpr)
			require(CAP_SYS_RESOURCE);
	}

	/* Allocate the new futexfd object. */
	result = (REF struct mfutexfd *)kmalloc(offsetof(struct mfutexfd, mfd_expr) +
	                                        (count + 1) * sizeof(struct lfutexexpr),
	                                        GFP_NORMAL);
	TRY {
		size_t i, dst;

		/* Initialize expressions. */
		for (i = dst = 0; i < count; ++i) {
			result->mfd_expr[dst].fe_offset = (uintptr_t)base + expr[i].fe_offset;
			/* !!! Never use compat_validate_readable here -- (base+fe_offset might produce large pointers) */
			validate_readable((void *)result->mfd_expr[dst].fe_offset, LOCAL_sizeof_pointer);

			/* To ensure that the expression address is always contained within a singular
			 * mem-node, we require that it  be aligned to the  size of the accessed  data
			 * word. */
			if (!IS_ALIGNED(result->mfd_expr[dst].fe_offset, LOCAL_sizeof_pointer))
				THROW(E_SEGFAULT_UNALIGNED, result->mfd_expr[dst].fe_offset,
				      0, LOCAL_sizeof_pointer);

			result->mfd_expr[dst].fe_condition = expr[i].fe_condition;
			result->mfd_expr[dst].fe_val       = expr[i].fe_val;
			result->mfd_expr[dst].fe_val2      = expr[i].fe_val2;
			COMPILER_READ_BARRIER();

			/* Select white-listed expressions. */
			switch (result->mfd_expr[dst].fe_condition) {

			case LFUTEX_EXPREND:
				goto done_expr;

			case LFUTEX_NOP:
				/* Remove this expression. */
				continue;

				/* Normal expressions. */
			case LFUTEX_WAIT_WHILE:
			case LFUTEX_WAIT_UNTIL:
			case LFUTEX_WAIT_WHILE_ABOVE:
			case LFUTEX_WAIT_WHILE_BELOW:
			case LFUTEX_WAIT_WHILE_BITMASK:
			case LFUTEX_WAIT_UNTIL_BITMASK:
				break;

			/* TODO: Support for memcmp-based futex codes */

			default:
				THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
				      E_INVALID_ARGUMENT_CONTEXT_LFUTEX_OP,
				      result->mfd_expr[dst].fe_condition);
			}

			/* Set operand size flag. */
#if ((defined(LFUTEX_WAIT_32BIT) && (LFUTEX_WAIT_32BIT != 0)) || \
     (defined(LFUTEX_WAIT_64BIT) && (LFUTEX_WAIT_64BIT != 0)))
#if defined(LFUTEX_WAIT_32BIT) && LOCAL_sizeof_pointer == 4
			result->mfd_expr[dst].fe_condition |= LFUTEX_WAIT_32BIT;
#elif defined(LFUTEX_WAIT_64BIT) && LOCAL_sizeof_pointer == 8
			result->mfd_expr[dst].fe_condition |= LFUTEX_WAIT_64BIT;
#else /* LOCAL_sizeof_pointer == ... */
#error "Unsupported `LOCAL_sizeof_pointer'"
#endif /* LOCAL_sizeof_pointer != ... */
#endif /* LFUTEX_WAIT_32BIT || LFUTEX_WAIT_64BIT */
			++dst;
		}
done_expr:
		if unlikely(dst < count) {
			/* Trim unused expressions. */
			struct mfutexfd *new_result;
			new_result = (struct mfutexfd *)krealloc(result,
			                                         (dst + 1) * sizeof(struct lfutexexpr),
			                                         GFP_NORMAL);
			if likely(new_result)
				result = new_result;
		}
		if unlikely(dst == 0) {
			/* Not allowed: no expressions */
			THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
			      E_INVALID_ARGUMENT_CONTEXT_LFUTEX_OP,
			      LFUTEX_EXPREND);
		}

		/* Mark the end of the expression list */
		result->mfd_expr[dst] = result->mfd_expr[dst - 1];
		result->mfd_expr[dst].fe_condition = LFUTEX_EXPREND;
#ifdef LFUTEX_WAIT_BITMASK
		result->mfd_expr[dst].fe_condition |= result->mfd_expr[dst - 1].fe_condition & LFUTEX_WAIT_BITMASK;
#endif /* LFUTEX_WAIT_BITMASK */
	} EXCEPT {
		kfree(result);
		RETHROW();
	}

	/* Fill in remaining fields */
	result->mfd_refcnt = 1;
	result->mfd_futex  = incref(futex);
	result->mfd_mman   = weakincref(THIS_MMAN);
	return result;
}

#undef LOCAL_sizeof_pointer
#undef LOCAL_mfutexfd_new
#undef LOCAL_struct_lfutexexpr

DECL_END

#undef DEFINE_mfutexfd_new
#undef DEFINE_compat_mfutexfd_new
