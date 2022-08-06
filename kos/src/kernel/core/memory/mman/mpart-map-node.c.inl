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
#ifdef __INTELLISENSE__
#include "mpart-map.c"
//#define DEFINE_mpart_mmap_node
#define DEFINE_mpart_mmap_node_p
#endif /* __INTELLISENSE__ */

#include <debugger/rt.h>
#include <kernel/mman.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart-blkst.h>
#include <kernel/mman/mpart.h>
#include <kernel/paging.h>
#include <sched/task.h>

#include <hybrid/align.h>

#include <assert.h>
#include <stddef.h>

DECL_BEGIN

/* A slightly smarter equivalent of:
 * >> pagedir_prot_t prot;
 * >> prot = mnode_getprot(node);
 * >> prot = mpart_mmap(self, addr, size, offset);
 * >> return prot;
 * However, unlike that piece of code, this one determines if write
 * access can be granted on a per-page basis (see the documentation
 * of `mpart_iscopywritable()'  and  `mpart_issharewritable()'  for
 * when write-access can be given)
 * @return: * : The union (or aka. |-ed together) set of `PAGEDIR_PROT_*'
 *              flags  used to  map pages  from the  given address range. */
#ifdef DEFINE_mpart_mmap_node
PUBLIC NOBLOCK NONNULL((1, 5)) pagedir_prot_t
NOTHROW(FCALL mpart_mmap_node)(struct mpart const *__restrict self,
                               PAGEDIR_PAGEALIGNED void *addr,
                               PAGEDIR_PAGEALIGNED size_t size,
                               PAGEDIR_PAGEALIGNED mpart_reladdr_t offset,
                               struct mnode const *__restrict node)
#define LOCAL_mpart_mmap(addr, size, offset, prot) \
	mpart_mmap(self, addr, size, offset, prot)
#elif defined(DEFINE_mpart_mmap_node_p)
/* Same as `mpart_mmap_node()', but map into the given page directory. */
PUBLIC NOBLOCK NONNULL((1, 6)) pagedir_prot_t
NOTHROW(FCALL mpart_mmap_node_p)(struct mpart const *__restrict self,
                                 pagedir_phys_t pdir,
                                 PAGEDIR_PAGEALIGNED void *addr,
                                 PAGEDIR_PAGEALIGNED size_t size,
                                 PAGEDIR_PAGEALIGNED mpart_reladdr_t offset,
                                 struct mnode const *__restrict node)
#define LOCAL_mpart_mmap(addr, size, offset, prot) \
	mpart_mmap_p(self, pdir, addr, size, offset, prot)
#else /* ... */
#error "Invalid configuration"
#endif /* !... */
{
	pagedir_prot_t prot, result;
	prot = mnode_getperm_force(node);

	/* Check for simple case: No write access needed. */
	if (!(prot & PAGEDIR_PROT_WRITE))
		return LOCAL_mpart_mmap(addr, size, offset, prot);

	/* Deal with write permissions on a per-page basis! */
	result = 0;
	while (size) {
		size_t part;
		pagedir_prot_t used_perm = prot;
		bool is_writable;

		/* Select permissions on a per-page basis! */
		part        = PAGESIZE;
		is_writable = mpart_iswritable(self, offset, PAGESIZE, node);
		/* TODO: This can be done _much_ more efficiently:
		 *   #1: Add a general rule that mem-part node-lists should be sorted by `mn_partoff'
		 *   #2: Iterate the mem-part's list of nodes only once here when determining which
		 *       portions of the part can be mapped with write-access. */
		while (part < size && (is_writable == !!mpart_iswritable(self, offset + part, PAGESIZE, node)))
			part += PAGESIZE;

		/* Disallow write-access if need be. */
		if (!is_writable)
			used_perm &= ~PAGEDIR_PROT_WRITE;

		/* Map this portion. */
		result |= LOCAL_mpart_mmap(addr, part, offset, used_perm);

		/* Account for remainder. */
		addr = (byte_t *)addr + part;
		offset += part;
		size -= part;
	}
	return result;
}

#undef LOCAL_mpart_mmap

DECL_END

#undef DEFINE_mpart_mmap_node
#undef DEFINE_mpart_mmap_node_p
