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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODRTM_MEMORY_H
#define GUARD_MODRTM_MEMORY_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <kernel/vm.h>

#include <hybrid/__assert.h>

#include "rtm.h"

DECL_BEGIN

struct rtm_memory_region {
	void                           *mr_addr;  /* Region starting address. (1-byte granularity) */
	size_t                          mr_size;  /* [!0] Size of this region (in bytes) */
	REF /*struct vm_datapart*/void *mr_part;  /* [1..1] The datapart used for backing this region.
	                                           * NOTE: The least significant bit of this pointer is
	                                           *       used to indicate if `mr_data' has been modified. */
	uintptr_t                       mr_vers;  /* Region RTM version before the initial read. */
	COMPILER_FLEXIBLE_ARRAY(byte_t, mr_data); /* [mr_size] Cached RTM region data. */
};
#define rtm_memory_region_getpart(self)    ((REF struct vm_datapart *)((uintptr_t)(self)->mr_part & ~1))
#define rtm_memory_region_waschanged(self) (((uintptr_t)(self)->mr_part & 1) != 0)

struct rtm_memory {
	size_t                     rm_mem_used; /* Sum of `kmalloc_usable_size()' of `rm_regionv' and
	                                         * `rm_regionv[i] | i in [0, rm_regionc)'. When this
	                                         * value would grow larger than `rtm_memory_limit', the
	                                         * current RTM operation must fail with `RTM_ABORT_CAPACITY' */
	size_t                     rm_regionc;  /* # of elements from `rm_regionv' that are currently in use. */
	struct rtm_memory_region **rm_regionv;  /* [1..1][owned][0..rm_regionc][owned] Vector of in-use memory regions.
	                                         * Sorted ascendingly by `mr_addr', meaning that an bsearch with a worst
	                                         * case lookup time of O(log2(n)) can be used for locating specific memory
	                                         * regions. (though in practice, most programs will only ever use 2 regions:
	                                         * one for the calling program's stack, and the other for the parts of memory
	                                         * that the program is actually intending to modify) */
	bool                       rm_chkuser;  /* [const] When true, verify that `addr' doesn't point into kernel-space
	                                         * as part of the execution of `rtm_memory_read()' and `rtm_memory_write()'
	                                         * before constructing a new, or extending an existing RTM memory region. */
};

/* Max amount of kernel heap memory that may be used by
 * a single instance of a `struct rtm_memory' structure. */
INTDEF size_t rtm_memory_limit;


/* Initialize a given `struct rtm_memory' */
#define RTM_MEMORY_INIT(chkuser) { 0, 0, __NULLPTR, chkuser }
#define rtm_memory_init(self, chkuser) \
	((self)->rm_mem_used = 0,          \
	 (self)->rm_regionc  = 0,          \
	 (self)->rm_regionv  = __NULLPTR,  \
	 (self)->rm_chkuser  = (chkuser))
#define rtm_memory_cinit(self, chkuser)                \
	(__hybrid_assert((self)->rm_mem_used == 0),        \
	 __hybrid_assert((self)->rm_regionc == 0),         \
	 __hybrid_assert((self)->rm_regionv == __NULLPTR), \
	 (self)->rm_chkuser = (chkuser))

/* Finalize a given `struct rtm_memory' */
INTDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL rtm_memory_fini)(struct rtm_memory *__restrict self);

/* Read RTM memory.
 * @throw: E_SEGFAULT: Faulty `addr', or `addr' points into a VIO mapping.
 * @throw: E_BADALLOC: Not enough memory, or `rtm_memory_limit' has been reached. */
INTDEF NONNULL((1, 3)) void FCALL
rtm_memory_read(struct rtm_memory *__restrict self, USER void const *addr,
                void *__restrict buf, size_t num_bytes)
		THROWS(E_BADALLOC, E_SEGFAULT);

/* Write RTM memory.
 * @throw: E_SEGFAULT: Faulty `addr', or `addr' points into a VIO mapping.
 * @throw: E_BADALLOC: Not enough memory, or `rtm_memory_limit' has been reached. */
INTDEF NONNULL((1, 3)) void FCALL
rtm_memory_write(struct rtm_memory *__restrict self, USER void *addr,
                 void const *__restrict buf, size_t num_bytes)
		THROWS(E_BADALLOC, E_SEGFAULT);

/* Atomically verify RTM version integrity, as well as apply RTM memory modifications.
 * @return: true:  Memory successfully applied
 * @return: false: Version of memory inconsistency detected (try again) */
INTDEF NONNULL((1)) bool FCALL
rtm_memory_apply(struct rtm_memory const *__restrict self);


DECL_END

#endif /* !GUARD_MODRTM_MEMORY_H */
