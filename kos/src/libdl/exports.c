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
#ifndef GUARD_LIBDL_EXPORTS_C
#define GUARD_LIBDL_EXPORTS_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

/* Keep this one the first */
#include "dl.h"
/**/

#include <kos/exec/peb.h>

DECL_BEGIN

/* None of the stuff below actually ends up in the final  binary.
 * However, these symbols  *do* appear in  the export table,  and
 * libdl contains special code to recognize these symbols by-name
 * when queried using `dlsym(3D)'.
 *
 * As such, the definitions below are there for `ld(1)` to find
 * these symbols and not complain that they would be  undefined
 * when it links programs against our `libdl.so'. */

#undef environ
#undef _environ
#undef __environ
PUBLIC ATTR_SECTION(".fakedata") char **environ = NULL;
DEFINE_PUBLIC_ALIAS(_environ, environ);
DEFINE_PUBLIC_ALIAS(__environ, environ);

PUBLIC ATTR_SECTION(".fakedata") struct process_peb __peb = { 0 };
PUBLIC ATTR_SECTION(".fakedata") size_t __argc = 0;
PUBLIC ATTR_SECTION(".fakedata") char **__argv = NULL;
PUBLIC ATTR_SECTION(".fakedata") char *program_invocation_name = NULL;
PUBLIC ATTR_SECTION(".fakedata") char *program_invocation_short_name = NULL;
DEFINE_PUBLIC_ALIAS(_pgmptr, program_invocation_name);
DEFINE_PUBLIC_ALIAS(__progname_full, program_invocation_name);
DEFINE_PUBLIC_ALIAS(__progname, program_invocation_short_name);

DECL_END

#endif /* !GUARD_LIBDL_EXPORTS_C */
