/* HASH CRC-32:0xf2d78983 */
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
#ifndef GUARD_LIBC_USER_KOS_EXCEPT_H
#define GUARD_LIBC_USER_KOS_EXCEPT_H 1

#include "../api.h"
#include "../auto/kos.except.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <kos/except.h>

DECL_BEGIN

/* >> except_data(3)
 * Return a pointer to the thread-local descriptor of the current exception */
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED struct exception_data *NOTHROW(LIBKCALL libc_except_data)(void);
/* >> except_code(3)
 * Return the current exception code, or `EXCEPT_CODEOF(E_OK)' when none is active */
INTDEF ATTR_PURE WUNUSED except_code_t NOTHROW(LIBKCALL libc_except_code)(void);
/* >> except_active(3)
 * Check if an exception is active; same as `except_code() != EXCEPT_CODEOF(E_OK)' */
INTDEF ATTR_PURE WUNUSED bool NOTHROW(LIBKCALL libc_except_active)(void);
/* >> except_class(3)
 * Return the current exception class; same as `EXCEPT_CLASS(except_code())' */
INTDEF ATTR_PURE WUNUSED except_class_t NOTHROW(LIBKCALL libc_except_class)(void);
/* >> except_subclass(3)
 * Return the current exception sub-class; same as `EXCEPT_SUBCLASS(except_code())' */
INTDEF ATTR_PURE WUNUSED except_subclass_t NOTHROW(LIBKCALL libc_except_subclass)(void);
/* >> except_register_state(3)
 * Return  the register state  at the time the  current exception was thrown.
 * The returned block of memory is only valid when `except_active() == true'. */
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED except_register_state_t *NOTHROW(LIBKCALL libc_except_register_state)(void);
/* >> except_info(3)
 * Return a pointer to the thread-local exception info structure.
 * Note  that the exact  layout of this  structure depends on how
 * libc/the kernel was configured. For the sake of compatibility,
 * try to  use `except_data()'  and `except_register_state()'  in
 * favor of this function. */
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED struct exception_info *NOTHROW(LIBKCALL libc_except_info)(void);
/* >> except_unwind(3)
 * Unwind the given register state to propagate the currently set error.
 * Following this, the  returned register state  should then be  loaded. */
INTDEF ATTR_RETNONNULL WUNUSED ATTR_INOUT(1) except_register_state_t *NOTHROW_NCX(__EXCEPT_UNWIND_CC libc_except_unwind)(except_register_state_t *__restrict state);
/* >> except_throw_current(3)
 * Throw the currently set (in `except_data()') exception. */
INTDEF ATTR_COLD ATTR_NORETURN void (LIBKCALL libc_except_throw_current)(void) THROWS(...);
/* >> except_rethrow(3)
 * Rethrow the current exception (same as a c++ `throw;' expression) */
INTDEF ATTR_COLD ATTR_NORETURN void (LIBKCALL libc_except_rethrow)(void) THROWS(...);
/* >> except_throw(3)
 * Throw an exception and fill exception pointers with all zeroes */
INTDEF ATTR_COLD ATTR_NORETURN void (__EXCEPT_THROW_CC libc_except_throw)(except_code_t code) THROWS(...);
/* >> except_thrown(3)
 * Throw an exception and load `argc' pointers from varargs */
INTDEF ATTR_COLD ATTR_NORETURN void (__EXCEPT_THROWN_CC libc_except_thrown)(except_code_t code, unsigned int _argc, ...) THROWS(...);
#ifndef __KERNEL__
/* >> _except_badusage_no_nesting(3)
 * Assertion check handler for missing `TRY' nesting */
INTDEF ATTR_COLD ATTR_NORETURN void NOTHROW(LIBCCALL libc__except_badusage_no_nesting)(void);
/* >> _except_check_no_nesting(3)
 * Assert that a TRY-block is currently allowed (iow: that no error is active) */
INTDEF void NOTHROW(LIBCCALL libc__except_check_no_nesting)(void);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_EXCEPT_H */
