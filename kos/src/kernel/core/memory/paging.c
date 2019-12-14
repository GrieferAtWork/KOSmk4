/* Copyright (c) 2019 Griefer@Work                                            *
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

#ifdef CONFIG_USE_NEW_PAGING
PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.npagedir_prepare_mapone_p") WUNUSED bool
NOTHROW(KCALL npagedir_prepare_mapone_p)(PAGEDIR_P_SELFTYPE self,
                                         PAGEDIR_PAGEALIGNED VIRT void *addr) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = npagedir_prepare_mapone(addr);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.npagedir_unprepare_mapone_p") void
NOTHROW(KCALL npagedir_unprepare_mapone_p)(PAGEDIR_P_SELFTYPE self,
                                           PAGEDIR_PAGEALIGNED VIRT void *addr) {
	PAGEDIR_P_BEGINUSE(self) {
		npagedir_unprepare_mapone(addr);
	}
	PAGEDIR_P_ENDUSE(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.npagedir_maphintone_p") void
NOTHROW(KCALL npagedir_maphintone_p)(PAGEDIR_P_SELFTYPE self,
                                     PAGEDIR_PAGEALIGNED VIRT void *addr,
                                     VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
	PAGEDIR_P_BEGINUSE(self) {
		npagedir_maphintone(addr, hint);
	}
	PAGEDIR_P_ENDUSE(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.npagedir_mapone_p") void
NOTHROW(KCALL npagedir_mapone_p)(PAGEDIR_P_SELFTYPE self,
                                 PAGEDIR_PAGEALIGNED VIRT void *addr,
                                 PAGEDIR_PAGEALIGNED PHYS vm_phys_t phys, u16 perm) {
	PAGEDIR_P_BEGINUSE(self) {
		npagedir_mapone(addr, phys, perm);
	}
	PAGEDIR_P_ENDUSE(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.npagedir_unmapone_p") void
NOTHROW(KCALL npagedir_unmapone_p)(PAGEDIR_P_SELFTYPE self,
                                   PAGEDIR_PAGEALIGNED VIRT void *addr) {
	PAGEDIR_P_BEGINUSE(self) {
		npagedir_unmapone(addr);
	}
	PAGEDIR_P_ENDUSE(self);
}

#ifdef CONFIG_HAVE_PAGEDIR_UNWRITE
PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.npagedir_unwriteone_p") void
NOTHROW(KCALL npagedir_unwriteone_p)(PAGEDIR_P_SELFTYPE self,
                                     PAGEDIR_PAGEALIGNED VIRT void *addr) {
	PAGEDIR_P_BEGINUSE(self) {
		npagedir_unwriteone(addr);
	}
	PAGEDIR_P_ENDUSE(self);
}
#endif /* CONFIG_HAVE_PAGEDIR_UNWRITE */

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.npagedir_prepare_map_p") WUNUSED bool
NOTHROW(KCALL npagedir_prepare_map_p)(PAGEDIR_P_SELFTYPE self,
                                      PAGEDIR_PAGEALIGNED VIRT void *addr,
                                      PAGEDIR_PAGEALIGNED size_t num_bytes) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = npagedir_prepare_map(addr, num_bytes);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.npagedir_prepare_map_p_keep") WUNUSED bool
NOTHROW(KCALL npagedir_prepare_map_keep_p)(PAGEDIR_P_SELFTYPE self,
                                           PAGEDIR_PAGEALIGNED VIRT void *addr,
                                           PAGEDIR_PAGEALIGNED size_t num_bytes) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = npagedir_prepare_map_keep(addr, num_bytes);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.npagedir_unprepare_map_p") void
NOTHROW(KCALL npagedir_unprepare_map_p)(PAGEDIR_P_SELFTYPE self,
                                        PAGEDIR_PAGEALIGNED VIRT void *addr,
                                        PAGEDIR_PAGEALIGNED size_t num_bytes) {
	PAGEDIR_P_BEGINUSE(self) {
		npagedir_unprepare_map(addr, num_bytes);
	}
	PAGEDIR_P_ENDUSE(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.npagedir_maphint_p") void
NOTHROW(KCALL npagedir_maphint_p)(PAGEDIR_P_SELFTYPE self,
                                  PAGEDIR_PAGEALIGNED VIRT void *addr,
                                  PAGEDIR_PAGEALIGNED size_t num_bytes,
                                  VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
	PAGEDIR_P_BEGINUSE(self) {
		npagedir_maphint(addr, num_bytes, hint);
	}
	PAGEDIR_P_ENDUSE(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.npagedir_map_p") void
NOTHROW(KCALL npagedir_map_p)(PAGEDIR_P_SELFTYPE self,
                              PAGEDIR_PAGEALIGNED VIRT void *addr,
                              PAGEDIR_PAGEALIGNED size_t num_bytes,
                              PAGEDIR_PAGEALIGNED PHYS vm_phys_t phys,
                              u16 perm) {
	PAGEDIR_P_BEGINUSE(self) {
		npagedir_map(addr, num_bytes, phys, perm);
	}
	PAGEDIR_P_ENDUSE(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.npagedir_unmap_p") void
NOTHROW(KCALL npagedir_unmap_p)(PAGEDIR_P_SELFTYPE self,
                                PAGEDIR_PAGEALIGNED VIRT void *addr,
                                PAGEDIR_PAGEALIGNED size_t num_bytes) {
	PAGEDIR_P_BEGINUSE(self) {
		npagedir_unmap(addr, num_bytes);
	}
	PAGEDIR_P_ENDUSE(self);
}

#ifdef CONFIG_HAVE_PAGEDIR_UNWRITE
PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.npagedir_unwrite_p") void
NOTHROW(KCALL npagedir_unwrite_p)(PAGEDIR_P_SELFTYPE self,
                                  PAGEDIR_PAGEALIGNED VIRT void *addr,
                                  PAGEDIR_PAGEALIGNED size_t num_bytes) {
	PAGEDIR_P_BEGINUSE(self) {
		npagedir_unwrite(addr, num_bytes);
	}
	PAGEDIR_P_ENDUSE(self);
}
#endif /* CONFIG_HAVE_PAGEDIR_UNWRITE */

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.npagedir_ismapped_p") WUNUSED bool
NOTHROW(KCALL npagedir_ismapped_p)(PAGEDIR_P_SELFTYPE self,
                                   VIRT void *addr) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = npagedir_ismapped(addr);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.npagedir_iswritable_p") WUNUSED bool
NOTHROW(KCALL npagedir_iswritable_p)(PAGEDIR_P_SELFTYPE self,
                                     VIRT void *addr) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = npagedir_iswritable(addr);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.npagedir_isuseraccessible_p") WUNUSED bool
NOTHROW(KCALL npagedir_isuseraccessible_p)(PAGEDIR_P_SELFTYPE self,
                                           VIRT void *addr) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = npagedir_isuseraccessible(addr);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

#ifdef CONFIG_HAVE_PAGEDIR_CHANGED
PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.npagedir_haschanged_p") WUNUSED bool
NOTHROW(KCALL npagedir_haschanged_p)(PAGEDIR_P_SELFTYPE self,
                                     VIRT void *addr) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = npagedir_haschanged(addr);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.npagedir_unsetchanged_p") void
NOTHROW(KCALL npagedir_unsetchanged_p)(PAGEDIR_P_SELFTYPE self,
                                       VIRT void *addr) {
	PAGEDIR_P_BEGINUSE(self) {
		npagedir_unsetchanged(addr);
	}
	PAGEDIR_P_ENDUSE(self);
}
#endif /* CONFIG_HAVE_PAGEDIR_CHANGED */

#else /* CONFIG_USE_NEW_PAGING */

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_prepare_mapone_p") WUNUSED bool
NOTHROW(KCALL pagedir_prepare_mapone_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = pagedir_prepare_mapone(virt_page);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unprepare_mapone_p") void
NOTHROW(KCALL pagedir_unprepare_mapone_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unprepare_mapone(virt_page);
	}
	PAGEDIR_P_ENDUSE(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_maphintone_p") void
NOTHROW(KCALL pagedir_maphintone_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page,
                                    VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_maphintone(virt_page, hint);
	}
	PAGEDIR_P_ENDUSE(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_mapone_p") void
NOTHROW(KCALL pagedir_mapone_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page,
                                PHYS pageptr_t phys_page, u16 perm) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_mapone(virt_page, phys_page, perm);
	}
	PAGEDIR_P_ENDUSE(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unmapone_p") void
NOTHROW(KCALL pagedir_unmapone_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unmapone(virt_page);
	}
	PAGEDIR_P_ENDUSE(self);
}

#ifdef CONFIG_HAVE_PAGEDIR_UNWRITE
PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unwriteone_p") void
NOTHROW(KCALL pagedir_unwriteone_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unwriteone(virt_page);
	}
	PAGEDIR_P_ENDUSE(self);
}
#endif /* CONFIG_HAVE_PAGEDIR_UNWRITE */

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_ismapped_p") WUNUSED bool
NOTHROW(KCALL pagedir_ismapped_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t vpage) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = pagedir_ismapped(vpage);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_iswritable_p") WUNUSED bool
NOTHROW(KCALL pagedir_iswritable_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t vpage) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = pagedir_iswritable(vpage);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_isuseraccessible_p") WUNUSED bool
NOTHROW(KCALL pagedir_isuseraccessible_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t vpage) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = pagedir_isuseraccessible(vpage);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

#ifdef CONFIG_HAVE_PAGEDIR_CHANGED
PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_haschanged_p") WUNUSED bool
NOTHROW(KCALL pagedir_haschanged_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t vpage) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = pagedir_haschanged(vpage);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unsetchanged_p") void
NOTHROW(KCALL pagedir_unsetchanged_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t vpage) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unsetchanged(vpage);
	}
	PAGEDIR_P_ENDUSE(self);
}
#endif /* CONFIG_HAVE_PAGEDIR_CHANGED */

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_prepare_map_p") WUNUSED bool
NOTHROW(KCALL pagedir_prepare_map_p)(PAGEDIR_P_SELFTYPE self,
                                     VIRT vm_vpage_t virt_page, size_t num_pages) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = pagedir_prepare_map(virt_page, num_pages);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_prepare_map_p_keep") WUNUSED bool
NOTHROW(KCALL pagedir_prepare_map_keep_p)(PAGEDIR_P_SELFTYPE self,
                                          VIRT vm_vpage_t virt_page, size_t num_pages) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = pagedir_prepare_map_keep(virt_page, num_pages);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unprepare_map_p") void
NOTHROW(KCALL pagedir_unprepare_map_p)(PAGEDIR_P_SELFTYPE self,
                                       VIRT vm_vpage_t virt_page, size_t num_pages) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unprepare_map(virt_page, num_pages);
	}
	PAGEDIR_P_ENDUSE(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_maphint_p") void
NOTHROW(KCALL pagedir_maphint_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page, size_t num_pages,
                                 VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_maphint(virt_page, num_pages, hint);
	}
	PAGEDIR_P_ENDUSE(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_map_p") void
NOTHROW(KCALL pagedir_map_p)(PAGEDIR_P_SELFTYPE self,
                             VIRT vm_vpage_t virt_page, size_t num_pages,
                             PHYS pageptr_t phys_page, u16 perm) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_map(virt_page, num_pages, phys_page, perm);
	}
	PAGEDIR_P_ENDUSE(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unmap_p") void
NOTHROW(KCALL pagedir_unmap_p)(PAGEDIR_P_SELFTYPE self,
                               VIRT vm_vpage_t virt_page, size_t num_pages) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unmap(virt_page, num_pages);
	}
	PAGEDIR_P_ENDUSE(self);
}

#ifdef CONFIG_HAVE_PAGEDIR_UNWRITE
PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unwrite_p") void
NOTHROW(KCALL pagedir_unwrite_p)(PAGEDIR_P_SELFTYPE self,
                                 VIRT vm_vpage_t virt_page, size_t num_pages) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unwrite(virt_page, num_pages);
	}
	PAGEDIR_P_ENDUSE(self);
}
#endif /* CONFIG_HAVE_PAGEDIR_UNWRITE */
#endif /* !CONFIG_USE_NEW_PAGING */


PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unmap_userspace_p") void
NOTHROW(KCALL pagedir_unmap_userspace_p)(PAGEDIR_P_SELFTYPE self,
                                         struct vm *__restrict sync_vm) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unmap_userspace(sync_vm);
	}
	PAGEDIR_P_ENDUSE(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unmap_userspace_nosync_p") void
NOTHROW(KCALL pagedir_unmap_userspace_nosync_p)(PAGEDIR_P_SELFTYPE self) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unmap_userspace_nosync();
	}
	PAGEDIR_P_ENDUSE(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_translate_p") WUNUSED PHYS vm_phys_t
NOTHROW(KCALL pagedir_translate_p)(PAGEDIR_P_SELFTYPE self,
                                   VIRT void *virt_addr) {
	PHYS vm_phys_t result;
	PAGEDIR_P_BEGINUSE(self) {
		result = pagedir_translate(virt_addr);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_PAGING_C */
