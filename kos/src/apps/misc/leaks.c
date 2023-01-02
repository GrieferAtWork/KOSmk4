/*[[[magic
local opt = options.setdefault("GCC.options", []);
opt.removeif([](e) -> e.startswith("-fstack-protector"));
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
#ifndef GUARD_APPS_MISC_LEAKS_C
#define GUARD_APPS_MISC_LEAKS_C 1
#define __CRT_FREESTANDING

#include <kos/ksysctl.h>
#include <kos/syscalls.h>

#include <intrin.h>
#include <stddef.h>
#include <stdlib.h>

void _start(void) {
	if (sys_Xksysctl(KSYSCTL_SYSTEM_MEMORY_DUMP_LEAKS, NULL) != 0)
		__debugbreak();
	sys_Xexit(EXIT_SUCCESS);
}

#endif /* !GUARD_APPS_MISC_LEAKS_C */
