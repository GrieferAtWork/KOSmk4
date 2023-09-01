/*[[[magic
// Libssp is the one responsible for stack-smash-protection, so prevent
// a dependency loop by getting rid  of SSP within the library  itself.
local opt = options.setdefault("GCC.options", []);
opt.removeif(e -> e.startswith("-fstack-protector"));
]]]*/
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
#ifndef GUARD_LIBSSP_SSP_C
#define GUARD_LIBSSP_SSP_C 1

#include <hybrid/compiler.h>

#include <hybrid/host.h>

#include <kos/config/config.h> /* Pull in config-specific macro overrides */
#include <kos/types.h>
#include <sys/syslog.h>

DECL_BEGIN

IMPDAT uintptr_t __stack_chk_guard;               /* from `libc.so' */
IMPDEF ATTR_NORETURN void __stack_chk_fail(void); /* from `libc.so' */

#define SECTION_CRT_ASSERT ".text.crt.assert"

INTERN ATTR_SECTION(SECTION_CRT_ASSERT)
ATTR_NORETURN void __stack_chk_fail_local(void) {
	__stack_chk_fail();
}

DECL_END

#endif /* !GUARD_LIBSSP_SSP_C */
