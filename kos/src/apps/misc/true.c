/*[[[magic
local opt = options.setdefault("GCC.options", []);
opt.removeif(x -> x.startswith("-fstack-protector"));
opt.removeif(x -> x.startswith("-g"));
]]]*/
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_APPS_MISC_TRUE_C
#define GUARD_APPS_MISC_TRUE_C 1
#define __CRT_FREESTANDING

#include <kos/syscalls.h>

#include <stdlib.h>

#ifndef EXIT_CODE
#define EXIT_CODE EXIT_SUCCESS
#endif /* !EXIT_CODE */

void _start(void) {
	sys_Xexit(EXIT_CODE);
}

#endif /* !GUARD_APPS_MISC_TRUE_C */
