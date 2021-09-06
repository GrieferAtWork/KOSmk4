/* HASH CRC-32:0x100f5a79 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_KOS_EXCEPT_H
#define GUARD_LIBC_AUTO_KOS_EXCEPT_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <kos/except.h>

DECL_BEGIN

/* Make use of inline optimizations when possible! */
#ifndef __INTELLISENSE__
#ifdef __arch_error_data
#define libc_error_data() __arch_error_data()
#endif /* __arch_error_data */
#ifdef __arch_error_code
#define libc_error_code() __arch_error_code()
#endif /* __arch_error_code */
#ifdef __arch_error_active
#define libc_error_active() __arch_error_active()
#endif /* __arch_error_active */
#ifdef __arch_error_class
#define libc_error_class() __arch_error_class()
#endif /* __arch_error_class */
#ifdef __arch_error_subclass
#define libc_error_subclass() __arch_error_subclass()
#endif /* __arch_error_subclass */
#ifdef __arch_error_register_state
#define libc_error_register_state() __arch_error_register_state()
#endif /* __arch_error_register_state */
#ifdef __arch_error_info
#define libc_error_info() __arch_error_info()
#endif /* __arch_error_info */
#endif /* !__INTELLISENSE__ */
/* Transform the given exception into a posix errno value */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) errno_t NOTHROW_NCX(LIBKCALL libc_error_as_errno)(struct exception_data const *__restrict self);
/* Transform the given exception into a posix signal.
 * If   doing  this  is   possible,  fill  in   `*result'  and  return  `true'.
 * Otherwise, `*result' is left in an undefined state, and `false' is returned. */
INTDEF WUNUSED NONNULL((1, 2)) bool NOTHROW_NCX(LIBKCALL libc_error_as_signal)(struct exception_data const *__restrict self, struct __siginfo_struct *__restrict result);
/* Return the name of the given error, or `NULL' if unknown.
 * This  name  is   the  same  as   the  `E_*'   identifier.
 * E.g.: `error_name(ERROR_CODEOF(E_BADALLOC))' -> "E_BADALLOC" */
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(LIBKCALL libc_error_name)(error_code_t code);
/* Return the priority for a given error code, where exceptions
 * with greater priorities should take  the place of ones  with
 * lower priorities in  situations where multiple  simultaneous
 * errors can't be prevented. */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBKCALL libc_error_priority)(error_code_t code);
/* Begin a nested TRY-block. (i.e. inside of another EXCEPT block) */
INTDEF NONNULL((1)) void NOTHROW(__ERROR_NESTING_BEGIN_CC libc_error_nesting_begin)(struct _exception_nesting_data *__restrict saved);
/* End a nested TRY-block. (i.e. inside of another EXCEPT block) */
INTDEF NONNULL((1)) void NOTHROW(__ERROR_NESTING_END_CC libc_error_nesting_end)(struct _exception_nesting_data *__restrict saved);

DECL_END

#endif /* !GUARD_LIBC_AUTO_KOS_EXCEPT_H */
