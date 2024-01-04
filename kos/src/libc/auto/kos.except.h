/* HASH CRC-32:0x8554060c */
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
#ifndef GUARD_LIBC_AUTO_KOS_EXCEPT_H
#define GUARD_LIBC_AUTO_KOS_EXCEPT_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <kos/except.h>

DECL_BEGIN

/* Make use of inline optimizations when possible! */
#ifndef __INTELLISENSE__
#ifdef __arch_except_data
#define libc_except_data() __arch_except_data()
#endif /* __arch_except_data */
#ifdef __arch_except_code
#define libc_except_code() __arch_except_code()
#endif /* __arch_except_code */
#ifdef __arch_except_active
#define libc_except_active() __arch_except_active()
#endif /* __arch_except_active */
#ifdef __arch_except_class
#define libc_except_class() __arch_except_class()
#endif /* __arch_except_class */
#ifdef __arch_except_subclass
#define libc_except_subclass() __arch_except_subclass()
#endif /* __arch_except_subclass */
#ifdef __arch_except_register_state
#define libc_except_register_state() __arch_except_register_state()
#endif /* __arch_except_register_state */
#ifdef __arch_except_info
#define libc_except_info() __arch_except_info()
#endif /* __arch_except_info */
#endif /* !__INTELLISENSE__ */
#include <bits/crt/format-printer.h>
#ifndef __pformatprinter_defined
#define __pformatprinter_defined
typedef __pformatprinter pformatprinter;
#endif /* !__pformatprinter_defined */
/* >> except_as_errno(3)
 * Transform the  given exception  into  a posix  errno  value.
 * When no special errno is defined for `data', return `EPERM'. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) errno_t NOTHROW_NCX(LIBKCALL libc_except_as_errno)(struct exception_data const *__restrict self);
/* >> except_as_signal(3)
 * Transform the given exception into a posix signal.
 * If doing this is possible, fill in `*result' and return `true'.
 * Otherwise, `*result' is left in an undefined state, and `false'
 * is returned. */
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(2) bool NOTHROW_NCX(LIBKCALL libc_except_as_signal)(struct exception_data const *__restrict self, struct __siginfo_struct *__restrict result);
/* >> except_name(3)
 * Return the name of the  given error, or `NULL'  if
 * unknown. This name is one of the `E_*' identifier.
 * E.g.: `except_name(EXCEPT_CODEOF(E_BADALLOC))' -> "E_BADALLOC" */
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(LIBKCALL libc_except_name)(except_code_t code);
/* >> except_priority(3)
 * Return the priority for a given error code, where exceptions
 * with greater priorities should take  the place of ones  with
 * lower priorities in  situations where multiple  simultaneous
 * errors can't be prevented. */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBKCALL libc_except_priority)(except_code_t code);
/* >> except_print_short_description(3)
 * Print a short, single-line (without trailing linefeed) description  of
 * the given error `data', including the error code, name and for certain
 * errors, prominent error arguments.
 * @param: flags: Set of `EXCEPT_PRINT_SHORT_DESCRIPTION_FLAG_*'
 * @return: * : The usual pformatprinter-compatible return value */
INTDEF ATTR_IN(3) NONNULL((1)) ssize_t NOTHROW_NCX(LIBKCALL libc_except_print_short_description)(pformatprinter printer, void *arg, struct exception_data const *data, uintptr_t flags);
/* >> except_nesting_begin(3)
 * Begin a nested  TRY-block. (i.e. inside  of another EXCEPT  block)
 * Don't call this function directly; use `NESTED_EXCEPTION' instead. */
INTDEF ATTR_INOUT(1) void NOTHROW(__EXCEPT_NESTING_BEGIN_CC libc_except_nesting_begin)(struct _exception_nesting_data *__restrict saved);
/* >> except_nesting_end(3)
 * End a nested TRY-block. (i.e. inside of another EXCEPT block) */
INTDEF ATTR_IN(1) void NOTHROW(__EXCEPT_NESTING_END_CC libc_except_nesting_end)(struct _exception_nesting_data const *__restrict saved);

DECL_END

#endif /* !GUARD_LIBC_AUTO_KOS_EXCEPT_H */
