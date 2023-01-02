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
#ifndef _LIBSCTRACE_TYPES_H
#define _LIBSCTRACE_TYPES_H 1

#include "api.h"
/**/

#include <compat/config.h> /* __ARCH_HAVE_COMPAT */

__DECL_BEGIN

#ifdef __CC__

/* Declare the main argument type repr enumerator. */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("__WANT_HAVE_SYSCALL_ARGUMENT_REPR_TYPES")
#pragma push_macro("__WANT_HAVE_SYSCALL_RETURN_REPR_TYPES")
#pragma push_macro("__WANT_SYSCALL_ARGUMENT_REPR_TYPES")
#pragma push_macro("__WANT_SYSCALL_RETURN_REPR_TYPES")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef __WANT_HAVE_SYSCALL_ARGUMENT_REPR_TYPES
#undef __WANT_HAVE_SYSCALL_RETURN_REPR_TYPES
#undef __WANT_SYSCALL_ARGUMENT_REPR_TYPES
#undef __WANT_SYSCALL_RETURN_REPR_TYPES
enum {
#define __WANT_HAVE_SYSCALL_ARGUMENT_REPR_TYPES 1
#define __WANT_SYSCALL_ARGUMENT_REPR_TYPES 1
#define __SYSCALL_REPR(type) type,
#ifdef __ARCH_HAVE_COMPAT
	/* Use the compatibility-mode header. */
#include <asm/syscall3264-types.h>
#else /* __ARCH_HAVE_COMPAT */
	/* Use the normal header. */
#include <asm/syscalls-types.h>
#endif /* !__ARCH_HAVE_COMPAT */
#ifndef HAVE_SC_REPR_POINTER
#define HAVE_SC_REPR_POINTER 1
	SC_REPR_POINTER,
#endif /* !HAVE_SC_REPR_POINTER */
	LIBSCTRACE_COUNT /* # of argument type representation codes. */
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("__WANT_SYSCALL_RETURN_REPR_TYPES")
#pragma pop_macro("__WANT_SYSCALL_ARGUMENT_REPR_TYPES")
#pragma pop_macro("__WANT_HAVE_SYSCALL_RETURN_REPR_TYPES")
#pragma pop_macro("__WANT_HAVE_SYSCALL_ARGUMENT_REPR_TYPES")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#endif /* __CC__ */

__DECL_END

#endif /* !_LIBSCTRACE_TYPES_H */
