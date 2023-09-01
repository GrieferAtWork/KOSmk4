/*[[[magic
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
#ifndef GUARD_APPS_MISC_CC_C
#define GUARD_APPS_MISC_CC_C 1
#define __CRT_FREESTANDING

#include <hybrid/compiler.h>

#include <kos/ksysctl.h>
#include <kos/syscalls.h>

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

void _start(void) {
	char buf[128], *p = COMPILER_ENDOF(buf);
	size_t count, extra;
	count = sys_Xksysctl(KSYSCTL_SYSTEM_CLEARCACHES, NULL);
	*--p = '\n';
	*--p = 'B';
	if (count >= (1024 * 1024)) {
		*--p = 'i';
		*--p = 'M';
		extra = count % (1024 * 1024);
		extra *= 100;
		extra /= (1024 * 1024);
		count /= (1024 * 1024);
	} else if (count >= 1024) {
		*--p = 'i';
		*--p = 'K';
		extra = count % 1024;
		extra *= 100;
		extra /= 1024;
		count /= 1024;
	} else {
		extra = 0;
	}
	if (extra) {
		*--p = '0' + (extra % 10);
		*--p = '0' + (extra / 10);
		*--p = '.';
	}
	do {
		*--p = '0' + (count % 10);
		count /= 10;
	} while (count);
	*--p = ' ';
	*--p = ':';
	*--p = 'd';
	*--p = 'e';
	*--p = 'e';
	*--p = 'r';
	*--p = 'f';
	sys_Xwrite(STDOUT_FILENO, p, (size_t)(COMPILER_ENDOF(buf) - p));
	sys_Xexit(EXIT_SUCCESS);
}

#endif /* !GUARD_APPS_MISC_CC_C */
