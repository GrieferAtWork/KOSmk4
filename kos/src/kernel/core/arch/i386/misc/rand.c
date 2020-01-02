/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_RAND_C
#define GUARD_KERNEL_CORE_ARCH_I386_RAND_C 1
#define DISABLE_BRANCH_PROFILING 1 /* Don't profile this file */
#define _KOS_SOURCE 1

#include <kernel/compiler.h>
#include <kernel/rand.h>
#include <kernel/printk.h>
#include <sys/io.h>

DECL_BEGIN

PRIVATE ATTR_FREERODATA u8 const cmos_registers[] = {
	0x00, /* CMOS_SECOND  */
	0x02, /* CMOS_MINUTE  */
	0x04, /* CMOS_HOUR    */
	0x07, /* CMOS_DAY     */
	0x08, /* CMOS_MONTH   */
	0x09  /* CMOS_YEAR    */
};

INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_rand_entropy)(void) {
	unsigned int i;
	u8 entropy[COMPILER_LENOF(cmos_registers)];
	u32 boot_seed = 0;

	/* Gather entropy from CMOS registers. */
	for (i = 0; i < COMPILER_LENOF(cmos_registers); ++i) {
		outb((port_t)0x70, cmos_registers[i]);
		entropy[i] = inb((port_t)0x71);
	}

	/* Combine entropy to generate our boot seed. */
	for (i = 0; i < COMPILER_LENOF(entropy); ++i) {
		boot_seed <<= (32 / COMPILER_LENOF(entropy));
		boot_seed ^= entropy[i];
	}
	/*boot_seed = 0xAB091919;*/

	/* Set the boot seed for our pseudo-random number generator. */
	krand_seed = boot_seed;
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_RAND_C */
