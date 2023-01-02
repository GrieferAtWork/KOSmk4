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
#ifndef _KOS_BITS_FUTEX_EXPR_H
#define _KOS_BITS_FUTEX_EXPR_H 1

#include <__stdinc.h>

#include <bits/types.h>

#ifdef __CC__
__DECL_BEGIN

struct lfutexexpr {
	/* The definition structure of expression-based futex waiting.
	 * Using this, you can specify arbitrarily complex expressions
	 * that all have to be true in order for a wait to take place. */
	__ptrdiff_t       fe_offset;    /* Offset of the `lfutex_t' object from the base-pointer. */
	__syscall_ulong_t fe_condition; /* Futex wait condition (must be one of `LFUTEX_WAIT_(WHILE|UNTIL)*')
	                                 * For the  last expression  in the  list, set  to  `LFUTEX_EXPREND'. */
	__syscall_ulong_t fe_val;       /* First condition operand (depending on `fe_condition') */
	__syscall_ulong_t fe_val2;      /* Second condition operand (depending on `fe_condition') */
};

#define LFUTEXEXPR_INIT(offset, cond, val, val2)  { offset, cond, val, val2 }

__DECL_END
#endif /* __CC__ */


#endif /* !_KOS_BITS_FUTEX_EXPR_H */
