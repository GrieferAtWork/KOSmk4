/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_ENUM_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_ENUM_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/mman.h>
#include <kernel/mman/enum.h>

#include <kos/except.h>

DECL_BEGIN

/* Enumerate all mappings contained within the given `enum_minaddr...enum_maxaddr'
 * address range within the given VM `self'. This function will automatically re-
 * assemble memory mappings that had previously been split into multiple nodes,
 * such that adjacent `struct mnode's that describe a contiguous memory mapping
 * do not appear as individual, separate nodes.
 * @param: cb:           A callback that should be invoked for every mapped memory region
 *                       contained with the given address range `enum_minaddr' ... `enum_maxaddr'
 *                       The sum of return values returned by this callback will eventually be
 *                       returned by this function, unless `cb()' returns a negative value, which
 *                       will cause enumeration to halt immediately, and that same value to be
 *                       propagated to the caller.
 *                       Note that mappings are enumerated in strictly ascending order, and that
 *                       this function guaranties that even in the modifications being made to the
 *                       given `self' while enumeration takes place, the `mmi_min' of all future
 *                       mappings will always be `> mmi_max' of every already/currently enumerated
 *                       mapping.
 * @param: arg:          An argument (cookie) to-be passed to `cb()'
 * @param: enum_minaddr: The starting address of mappings to-be enumerated, such that any mapping
 *                       that overlap with `enum_minaddr ... enum_maxaddr' will be enumerated.
 * @param: enum_maxaddr: Same as `enum_minaddr', but specifies the max address of any enumerated
 *                       mapping. */
FUNDEF ssize_t KCALL
mman_enum(struct mman *__restrict self, mman_enum_callback_t cb, void *arg,
          UNCHECKED void *enum_minaddr, UNCHECKED void *enum_maxaddr) {
	(void)self;
	(void)cb;
	(void)arg;
	(void)enum_minaddr;
	(void)enum_maxaddr;
	COMPILER_IMPURE();
	/* TODO */
	return 0;
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_ENUM_C */
