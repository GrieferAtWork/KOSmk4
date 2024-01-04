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
#ifndef GUARD_KERNEL_SRC_MEMORY_PAGING_C
#define GUARD_KERNEL_SRC_MEMORY_PAGING_C 1
#define __OMIT_PAGING_CONSTANT_P_WRAPPERS 1

#include <kernel/compiler.h>

#include <kernel/paging.h>
#include <kernel/types.h>
#include <sched/task.h>

#include <hybrid/align.h>

#include <assert.h>
#include <stdbool.h>

DECL_BEGIN

/* Implement page-directory specific operations using `PAGEDIR_P_(BEGIN|END)USE' */

ATTR_SECTION(".text.kernel.pagedir_p.pagedir_prepareone_p")
PUBLIC NOBLOCK ATTR_WEAK WUNUSED bool
NOTHROW(KCALL pagedir_prepareone_p)(pagedir_phys_t self,
                                    PAGEDIR_PAGEALIGNED VIRT void *addr) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = pagedir_prepareone(addr);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unprepareone_p")
PUBLIC NOBLOCK ATTR_WEAK void
NOTHROW(KCALL pagedir_unprepareone_p)(pagedir_phys_t self,
                                      PAGEDIR_PAGEALIGNED VIRT void *addr) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unprepareone(addr);
	}
	PAGEDIR_P_ENDUSE(self);
}

ATTR_SECTION(".text.kernel.pagedir_p.pagedir_maphintone_p")
PUBLIC NOBLOCK ATTR_WEAK void
NOTHROW(KCALL pagedir_maphintone_p)(pagedir_phys_t self,
                                    PAGEDIR_PAGEALIGNED VIRT void *addr,
                                    VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_maphintone(addr, hint);
	}
	PAGEDIR_P_ENDUSE(self);
}

ATTR_SECTION(".text.kernel.pagedir_p.pagedir_mapone_p")
PUBLIC NOBLOCK ATTR_WEAK void
NOTHROW(KCALL pagedir_mapone_p)(pagedir_phys_t self,
                                PAGEDIR_PAGEALIGNED VIRT void *addr,
                                PAGEDIR_PAGEALIGNED physaddr_t phys,
                                pagedir_prot_t prot) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_mapone(addr, phys, prot);
	}
	PAGEDIR_P_ENDUSE(self);
}

ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unmapone_p")
PUBLIC NOBLOCK ATTR_WEAK void
NOTHROW(KCALL pagedir_unmapone_p)(pagedir_phys_t self,
                                  PAGEDIR_PAGEALIGNED VIRT void *addr) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unmapone(addr);
	}
	PAGEDIR_P_ENDUSE(self);
}

#ifdef ARCH_PAGEDIR_HAVE_DENYWRITE
ATTR_SECTION(".text.kernel.pagedir_p.pagedir_denywriteone_p")
PUBLIC NOBLOCK ATTR_WEAK void
NOTHROW(KCALL pagedir_denywriteone_p)(pagedir_phys_t self,
                                      PAGEDIR_PAGEALIGNED VIRT void *addr) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_denywriteone(addr);
	}
	PAGEDIR_P_ENDUSE(self);
}
#endif /* ARCH_PAGEDIR_HAVE_DENYWRITE */

ATTR_SECTION(".text.kernel.pagedir_p.pagedir_prepare_p")
PUBLIC NOBLOCK ATTR_WEAK WUNUSED bool
NOTHROW(KCALL pagedir_prepare_p)(pagedir_phys_t self,
                                 PAGEDIR_PAGEALIGNED VIRT void *addr,
                                 PAGEDIR_PAGEALIGNED size_t num_bytes) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = pagedir_prepare(addr, num_bytes);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unprepare_p")
PUBLIC NOBLOCK ATTR_WEAK void
NOTHROW(KCALL pagedir_unprepare_p)(pagedir_phys_t self,
                                   PAGEDIR_PAGEALIGNED VIRT void *addr,
                                   PAGEDIR_PAGEALIGNED size_t num_bytes) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unprepare(addr, num_bytes);
	}
	PAGEDIR_P_ENDUSE(self);
}

ATTR_SECTION(".text.kernel.pagedir_p.pagedir_maphint_p")
PUBLIC NOBLOCK ATTR_WEAK void
NOTHROW(KCALL pagedir_maphint_p)(pagedir_phys_t self,
                                 PAGEDIR_PAGEALIGNED VIRT void *addr,
                                 PAGEDIR_PAGEALIGNED size_t num_bytes,
                                 VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_maphint(addr, num_bytes, hint);
	}
	PAGEDIR_P_ENDUSE(self);
}

ATTR_SECTION(".text.kernel.pagedir_p.pagedir_map_p")
PUBLIC NOBLOCK ATTR_WEAK void
NOTHROW(KCALL pagedir_map_p)(pagedir_phys_t self,
                             PAGEDIR_PAGEALIGNED VIRT void *addr,
                             PAGEDIR_PAGEALIGNED size_t num_bytes,
                             PAGEDIR_PAGEALIGNED physaddr_t phys,
                             pagedir_prot_t prot) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_map(addr, num_bytes, phys, prot);
	}
	PAGEDIR_P_ENDUSE(self);
}

ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unmap_p")
PUBLIC NOBLOCK ATTR_WEAK void
NOTHROW(KCALL pagedir_unmap_p)(pagedir_phys_t self,
                               PAGEDIR_PAGEALIGNED VIRT void *addr,
                               PAGEDIR_PAGEALIGNED size_t num_bytes) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unmap(addr, num_bytes);
	}
	PAGEDIR_P_ENDUSE(self);
}

#ifdef ARCH_PAGEDIR_HAVE_DENYWRITE
ATTR_SECTION(".text.kernel.pagedir_p.pagedir_denywrite_p")
PUBLIC NOBLOCK ATTR_WEAK void
NOTHROW(KCALL pagedir_denywrite_p)(pagedir_phys_t self,
                                   PAGEDIR_PAGEALIGNED VIRT void *addr,
                                   PAGEDIR_PAGEALIGNED size_t num_bytes) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_denywrite(addr, num_bytes);
	}
	PAGEDIR_P_ENDUSE(self);
}
#endif /* ARCH_PAGEDIR_HAVE_DENYWRITE */

ATTR_SECTION(".text.kernel.pagedir_p.pagedir_ismapped_p")
PUBLIC NOBLOCK ATTR_WEAK WUNUSED ATTR_ACCESS_NONE(2) bool
NOTHROW(KCALL pagedir_ismapped_p)(pagedir_phys_t self,
                                  VIRT void const *addr) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = pagedir_ismapped(addr);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

ATTR_SECTION(".text.kernel.pagedir_p.pagedir_iswritable_p")
PUBLIC NOBLOCK ATTR_WEAK WUNUSED bool
NOTHROW(KCALL pagedir_iswritable_p)(pagedir_phys_t self,
                                    VIRT void *addr) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = pagedir_iswritable(addr);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

ATTR_SECTION(".text.kernel.pagedir_p.pagedir_isuseraccessible_p")
PUBLIC NOBLOCK ATTR_WEAK WUNUSED ATTR_ACCESS_NONE(2) bool
NOTHROW(KCALL pagedir_isuseraccessible_p)(pagedir_phys_t self,
                                          VIRT void const *addr) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = pagedir_isuseraccessible(addr);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

#ifdef ARCH_PAGEDIR_HAVE_CHANGED
ATTR_SECTION(".text.kernel.pagedir_p.pagedir_haschanged_p")
PUBLIC NOBLOCK ATTR_WEAK WUNUSED bool
NOTHROW(KCALL pagedir_haschanged_p)(pagedir_phys_t self,
                                    VIRT void *addr) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = pagedir_haschanged(addr);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unsetchanged_p")
PUBLIC NOBLOCK ATTR_WEAK void
NOTHROW(KCALL pagedir_unsetchanged_p)(pagedir_phys_t self,
                                      VIRT void *addr) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unsetchanged(addr);
	}
	PAGEDIR_P_ENDUSE(self);
}
#endif /* ARCH_PAGEDIR_HAVE_CHANGED */

ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unmap_userspace_p")
PUBLIC NOBLOCK ATTR_WEAK void
NOTHROW(KCALL pagedir_unmap_userspace_p)(pagedir_phys_t self) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unmap_userspace();
	}
	PAGEDIR_P_ENDUSE(self);
}

ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unmap_userspace_nosync_p")
PUBLIC NOBLOCK ATTR_WEAK void
NOTHROW(KCALL pagedir_unmap_userspace_nosync_p)(pagedir_phys_t self) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unmap_userspace_nosync();
	}
	PAGEDIR_P_ENDUSE(self);
}

ATTR_SECTION(".text.kernel.pagedir_p.pagedir_translate_p")
PUBLIC NOBLOCK ATTR_WEAK WUNUSED ATTR_ACCESS_NONE(2) physaddr_t
NOTHROW(KCALL pagedir_translate_p)(pagedir_phys_t self,
                                   VIRT void const *virt_addr) {
	physaddr_t result;
	PAGEDIR_P_BEGINUSE(self) {
		result = pagedir_translate(virt_addr);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_PAGING_C */
