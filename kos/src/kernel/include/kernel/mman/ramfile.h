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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_RAMFILE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_RAMFILE_H 1

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_VM
#include <kernel/vm.h>
#else /* !CONFIG_USE_NEW_VM */
#include <kernel/mman/mfile.h>
#include <kernel/mman/mpart.h>

#ifdef __CC__
DECL_BEGIN

struct mramfile {
	struct mfile mrf_file; /* The ram-file */
	struct mpart mrf_part; /* The (only) ram part. */
};

#ifdef __WANT_MPART_INIT
/* >> MRAMFILE_INIT(struct mramfile &self, physpage_t first_page, physpagecnt_t page_count)
 * Initialize a given mem-ram-file, given a simple physical
 * location of where the file's backing data may be found. */
#define MRAMFILE_INIT(self, first_page, page_count, num_bytes)                     \
	{                                                                              \
		MFILE_INIT_EX(2, &mfile_ndef_ops, &(self).mrf_part, __NULLPTR, PAGESHIFT), \
		MPART_INIT_PHYS(&(self).mrf_file, first_page, page_count, num_bytes)       \
	}
#endif /* __WANT_MPART_INIT */

DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_VM */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_RAMFILE_H */
