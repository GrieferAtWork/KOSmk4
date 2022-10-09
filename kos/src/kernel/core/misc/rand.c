/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MISC_RAND_C
#define GUARD_KERNEL_SRC_MISC_RAND_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver-param.h>
#include <kernel/rand.h>
#include <kernel/types.h>

#include <hybrid/atomic.h>

#include <stddef.h>

DECL_BEGIN

/* The current kernel seed. */
PUBLIC WEAK u32 krand_seed = 0; /* Filled during early boot with a truly random value. */
DEFINE_EARLY_KERNEL_COMMANDLINE_OPTION(krand_seed, KERNEL_COMMANDLINE_OPTION_TYPE_UINT32, "seed");


PRIVATE u32 const rand_map[] = {
	0x11e0ebcc, 0xa914eba6, 0xe400e438, 0xa6c4a4df,
	0x0da46171, 0x4b9a27d1, 0x201910ae, 0x95e213cb,
	0xd5ce0943, 0x00005fdc, 0x0319257d, 0x09280b06,
	0x1148c0a6, 0x07a24139, 0x021214a6, 0x03221af8
};

/* Generate and return a 32-bit, pseudo-random integer. */
PUBLIC NOBLOCK WUNUSED ATTR_LEAF u32
NOTHROW(KCALL krand32)(void) {
	u32 old_seed, new_seed;
	do {
		new_seed = old_seed = ATOMIC_READ(krand_seed);
		new_seed = (((new_seed + 7) << 1) / 3);
		new_seed ^= rand_map[(new_seed >> (new_seed & 7)) % lengthof(rand_map)];
	} while (!ATOMIC_CMPXCH_WEAK(krand_seed, old_seed, new_seed));
	return old_seed;
}

/* Same as `krand32()', but use `*pseed' instead of `krand_seed'
 * WARNING: Unlike `krand32()', `*pseed' is _NOT_ modified atomically!
 *          This means that `krand32_r(&krand_seed)' is _NOT_ equal to
 *          a call to `krand32()', since the call would result in weak
 *          undefined behavior when  called from  multiple threads  at
 *          the same time */
PUBLIC NOBLOCK WUNUSED ATTR_LEAF NONNULL((1)) u32
NOTHROW(KCALL krand32_r)(u32 *__restrict pseed) {
	u32 old_seed, new_seed;
	new_seed = old_seed = *pseed;
	new_seed = (((new_seed + 7) << 1) / 3);
	new_seed ^= rand_map[(new_seed >> (new_seed & 7)) % lengthof(rand_map)];
	*pseed = new_seed;
	return old_seed;
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_MISC_RAND_C */
