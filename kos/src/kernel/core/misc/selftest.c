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
#ifndef GUARD_KERNEL_SRC_MISC_SELFTEST_C
#define GUARD_KERNEL_SRC_MISC_SELFTEST_C 1

#include <kernel/compiler.h>
#include <kernel/selftest.h>

#ifdef CONFIG_HAVE_KERNEL_SELFTEST
#include <kernel/boot.h>
#include <kernel/driver-param.h>
#include <kernel/printk.h>

DECL_BEGIN

typedef void (KCALL *PSELFTEST)(void);

extern PSELFTEST const __kernel_selftest_start[];
extern PSELFTEST const __kernel_selftest_end[];

/* Kernel commandline option: Disable self-tests during boot. */
INTERN ATTR_FREEBSS bool config_notest = false;
DEFINE_VERY_EARLY_KERNEL_COMMANDLINE_OPTION(config_notest,
                                            KERNEL_COMMANDLINE_OPTION_TYPE_BOOL,
                                            "notest");

INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_selftest)(void) {
	if (!config_notest) {
		PSELFTEST const *iter;
		printk(FREESTR(KERN_INFO "[boot] Running self-tests\n"));
		for (iter = __kernel_selftest_start;
			 iter < __kernel_selftest_end; ++iter) {
			(**iter)();
		}
		printk(FREESTR(KERN_INFO "[boot] All self-tests OK\n"));
	}
}

DECL_END
#endif /* CONFIG_HAVE_KERNEL_SELFTEST */

#endif /* !GUARD_KERNEL_SRC_MISC_SELFTEST_C */
