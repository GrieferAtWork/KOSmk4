/* HASH CRC-32:0x4717fc9c */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
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

INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED struct exception_data *NOTHROW_NCX(LIBKCALL libc_error_data)(void);
INTDEF ATTR_PURE WUNUSED error_code_t NOTHROW_NCX(LIBKCALL libc_error_code)(void);
INTDEF ATTR_PURE WUNUSED bool NOTHROW_NCX(LIBKCALL libc_error_active)(void);
INTDEF ATTR_PURE WUNUSED error_class_t NOTHROW_NCX(LIBKCALL libc_error_class)(void);
INTDEF ATTR_PURE WUNUSED error_subclass_t NOTHROW_NCX(LIBKCALL libc_error_subclass)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED error_register_state_t *NOTHROW_NCX(LIBKCALL libc_error_register_state)(void);
#ifndef __KERNEL__
/* Transform the given exception into a posix errno value */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_error_as_errno)(struct exception_data const *__restrict data);
/* Transform the given exception into a posix signal.
 * If doing this is possible, fill in `*result' and return `true'.
 * Otherwise, `*result' is left in an undefined state, and `false' is returned. */
INTDEF WUNUSED NONNULL((1, 2)) bool NOTHROW_NCX(LIBCCALL libc_error_as_signal)(struct exception_data const *__restrict data, struct __siginfo_struct *__restrict result);
#endif /* !__KERNEL__ */
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED struct exception_info *NOTHROW_NCX(LIBKCALL libc_error_info)(void);
/* Unwind the given register state to propagate the currently set error.
 * Following this, the returned register state should then be loaded. */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) error_register_state_t *NOTHROW_NCX(__ERROR_UNWIND_CC libc_error_unwind)(error_register_state_t *__restrict state);
/* Throw the currently set (in `error_data()') exception. */
INTDEF ATTR_COLD ATTR_NORETURN void NOTHROW_NCX(LIBKCALL libc_error_throw_current)(void);
/* Rethrow the current exception (same as a c++ `throw;' expression) */
INTDEF ATTR_COLD ATTR_NORETURN void NOTHROW_NCX(LIBKCALL libc_error_rethrow)(void);
/* Throw an exception and fill exception pointers with all zeroes */
INTDEF ATTR_COLD ATTR_NORETURN void NOTHROW_NCX(__ERROR_THROW_CC libc_error_throw)(error_code_t code);
/* Throw an exception and load `argc' pointers from varargs */
INTDEF ATTR_COLD ATTR_NORETURN void NOTHROW_NCX(__ERROR_THROWN_CC libc_error_thrown)(error_code_t code, unsigned int _argc, ...);

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_EXCEPT_H */
