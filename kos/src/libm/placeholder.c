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
#ifndef GUARD_LIBM_PLACEHOLDER_C
#define GUARD_LIBM_PLACEHOLDER_C 1
#define _KOS_SOURCE 1

#include "api.h"

#include <hybrid/compiler.h>

DECL_BEGIN

/* libm doesn't actually do anything in KOS.
 * All of the math functions are already defined in libc (for compatibility with DOS),
 * so when libm is loaded,  attempting to dlsym() or simply  use one of the many  math
 * functions will cause `libdl.so' to walk the dependency tree of libm (which contains
 * libc.so), allowing it to find the implementations provided there.
 * We could in theory provide some linux/gnu-specific math functions here and keep them
 * out of libc, however given that this really isn't necessary, not doing anything here
 * works just as well. */

DECL_END

#endif /* !GUARD_LIBM_PLACEHOLDER_C */
