/* HASH CRC-32:0x5c5beb73 */
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

INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED struct exception_data *NOTHROW(LIBKCALL libc_except_data)(void);
INTDEF ATTR_PURE WUNUSED except_code_t NOTHROW(LIBKCALL libc_except_code)(void);
INTDEF ATTR_PURE WUNUSED bool NOTHROW(LIBKCALL libc_except_active)(void);
INTDEF ATTR_PURE WUNUSED except_class_t NOTHROW(LIBKCALL libc_except_class)(void);
INTDEF ATTR_PURE WUNUSED except_subclass_t NOTHROW(LIBKCALL libc_except_subclass)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED except_register_state_t *NOTHROW(LIBKCALL libc_except_register_state)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED struct exception_info *NOTHROW(LIBKCALL libc_except_info)(void);
/* Unwind the given register state to propagate the currently set error.
 * Following this, the  returned register state  should then be  loaded. */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) except_register_state_t *NOTHROW_NCX(__EXCEPT_UNWIND_CC libc_except_unwind)(except_register_state_t *__restrict state);
/* Throw the currently set (in `except_data()') exception. */
INTDEF ATTR_COLD ATTR_NORETURN void (LIBKCALL libc_except_throw_current)(void) THROWS(...);
/* Rethrow the current exception (same as a c++ `throw;' expression) */
INTDEF ATTR_COLD ATTR_NORETURN void (LIBKCALL libc_except_rethrow)(void) THROWS(...);
/* Throw an exception and fill exception pointers with all zeroes */
INTDEF ATTR_COLD ATTR_NORETURN void (__EXCEPT_THROW_CC libc_except_throw)(except_code_t code) THROWS(...);
/* Throw an exception and load `argc' pointers from varargs */
INTDEF ATTR_COLD ATTR_NORETURN void (__EXCEPT_THROWN_CC libc_except_thrown)(except_code_t code, unsigned int _argc, ...) THROWS(...);
#ifndef __KERNEL__
/* Assertion check handler for missing `TRY' nesting */
INTDEF ATTR_COLD ATTR_NORETURN void NOTHROW(LIBCCALL libc__except_badusage_no_nesting)(void);
/* Assert that a TRY-block is currently allowed (iow: that no error is active) */
INTDEF void NOTHROW(LIBCCALL libc__except_check_no_nesting)(void);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_EXCEPT_H */
