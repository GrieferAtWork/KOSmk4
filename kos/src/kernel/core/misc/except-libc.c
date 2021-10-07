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

INTERN WUNUSED ATTR_CONST ATTR_RETNONNULL struct exception_info *
NOTHROW_NCX(LIBCCALL libc_error_info)(void) {
	return &THIS_EXCEPTION_INFO;
}

INTERN WUNUSED ATTR_CONST ATTR_RETNONNULL struct exception_data *
NOTHROW_NCX(LIBCCALL libc_error_data)(void) {
	return &THIS_EXCEPTION_DATA;
}

INTERN WUNUSED ATTR_CONST ATTR_RETNONNULL error_register_state_t *
NOTHROW_NCX(LIBCCALL libc_error_register_state)(void) {
	return &THIS_EXCEPTION_STATE;
}

INTERN ATTR_PURE WUNUSED error_code_t
NOTHROW_NCX(LIBCCALL libc_error_code)(void) {
	return PERTASK_GET(this_exception_code);
}

INTERN ATTR_PURE WUNUSED bool
NOTHROW_NCX(LIBCCALL libc_error_active)(void) {
	return PERTASK_NE(this_exception_code, ERROR_CODEOF(E_OK));
}

INTERN ATTR_PURE WUNUSED error_class_t
NOTHROW_NCX(LIBCCALL libc_error_class)(void) {
	return PERTASK_GET(this_exception_class);
}

INTERN ATTR_PURE WUNUSED error_subclass_t
NOTHROW_NCX(LIBCCALL libc_error_subclass)(void) {
	return PERTASK_GET(this_exception_subclass);
}

DEFINE_PUBLIC_ALIAS(error_info, libc_error_info);
DEFINE_PUBLIC_ALIAS(error_data, libc_error_data);
DEFINE_PUBLIC_ALIAS(error_register_state, libc_error_register_state);
DEFINE_PUBLIC_ALIAS(error_code, libc_error_code);
DEFINE_PUBLIC_ALIAS(error_active, libc_error_active);
DEFINE_PUBLIC_ALIAS(error_class, libc_error_class);
DEFINE_PUBLIC_ALIAS(error_subclass, libc_error_subclass);

DECL_END

#endif /* !GUARD_KERNEL_SRC_MISC_EXCEPT_LIBC_C */
