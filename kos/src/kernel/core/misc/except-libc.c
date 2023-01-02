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
#ifndef GUARD_KERNEL_SRC_MISC_EXCEPT_LIBC_C
#define GUARD_KERNEL_SRC_MISC_EXCEPT_LIBC_C 1

/* Kernel implementation of functions from <kos/except.h> */

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/types.h>

#ifndef LIBCCALL
#define LIBCCALL __LIBCCALL
#endif /* !LIBCCALL */

DECL_BEGIN

INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED struct exception_info *
NOTHROW_NCX(LIBCCALL libc_except_info)(void) {
	return &THIS_EXCEPTION_INFO;
}

INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED struct exception_data *
NOTHROW_NCX(LIBCCALL libc_except_data)(void) {
	return &THIS_EXCEPTION_DATA;
}

INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED except_register_state_t *
NOTHROW_NCX(LIBCCALL libc_except_register_state)(void) {
	return &THIS_EXCEPTION_STATE;
}

INTERN ATTR_PURE WUNUSED except_code_t
NOTHROW_NCX(LIBCCALL libc_except_code)(void) {
	return PERTASK_GET(this_exception_code);
}

INTERN ATTR_PURE WUNUSED bool
NOTHROW_NCX(LIBCCALL libc_except_active)(void) {
	return PERTASK_NE(this_exception_code, EXCEPT_CODEOF(E_OK));
}

INTERN ATTR_PURE WUNUSED except_class_t
NOTHROW_NCX(LIBCCALL libc_except_class)(void) {
	return PERTASK_GET(this_exception_class);
}

INTERN ATTR_PURE WUNUSED except_subclass_t
NOTHROW_NCX(LIBCCALL libc_except_subclass)(void) {
	return PERTASK_GET(this_exception_subclass);
}

DEFINE_PUBLIC_ALIAS(except_info, libc_except_info);
DEFINE_PUBLIC_ALIAS(except_data, libc_except_data);
DEFINE_PUBLIC_ALIAS(except_register_state, libc_except_register_state);
DEFINE_PUBLIC_ALIAS(except_code, libc_except_code);
DEFINE_PUBLIC_ALIAS(except_active, libc_except_active);
DEFINE_PUBLIC_ALIAS(except_class, libc_except_class);
DEFINE_PUBLIC_ALIAS(except_subclass, libc_except_subclass);

DECL_END

#endif /* !GUARD_KERNEL_SRC_MISC_EXCEPT_LIBC_C */
