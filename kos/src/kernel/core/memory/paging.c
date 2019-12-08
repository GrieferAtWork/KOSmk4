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
NOTHROW(KCALL pagedir_unprepare_mapone_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t virt_page) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unprepare_mapone(virt_page);
	}
	PAGEDIR_P_ENDUSE(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_maphintone_p") void
NOTHROW(KCALL pagedir_maphintone_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t virt_page,
                                    VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_maphintone(virt_page, hint);
	}
	PAGEDIR_P_ENDUSE(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_mapone_p") void
NOTHROW(KCALL pagedir_mapone_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t virt_page,
                                PHYS vm_ppage_t phys_page, u16 perm) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_mapone(virt_page, phys_page, perm);
	}
	PAGEDIR_P_ENDUSE(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unmapone_p") void
NOTHROW(KCALL pagedir_unmapone_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t virt_page) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unmapone(virt_page);
	}
	PAGEDIR_P_ENDUSE(self);
}

#ifdef CONFIG_HAVE_PAGEDIR_UNWRITE
PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unwriteone_p") void
NOTHROW(KCALL pagedir_unwriteone_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t virt_page) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unwriteone(virt_page);
	}
	PAGEDIR_P_ENDUSE(self);
}
#endif /* CONFIG_HAVE_PAGEDIR_UNWRITE */

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unmap_userspace_p") void
NOTHROW(KCALL pagedir_unmap_userspace_p)(VIRT pagedir_t *__restrict self,
                                         struct vm *__restrict sync_vm) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unmap_userspace(sync_vm);
	}
	PAGEDIR_P_ENDUSE(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unmap_userspace_nosync_p") void
NOTHROW(KCALL pagedir_unmap_userspace_nosync_p)(VIRT pagedir_t *__restrict self) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unmap_userspace_nosync();
	}
	PAGEDIR_P_ENDUSE(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_translate_p") WUNUSED PHYS vm_phys_t
NOTHROW(KCALL pagedir_translate_p)(VIRT pagedir_t *__restrict self, VIRT vm_virt_t virt_addr) {
	PHYS vm_phys_t result;
	PAGEDIR_P_BEGINUSE(self) {
		result = pagedir_translate(virt_addr);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_ismapped_p") WUNUSED bool
NOTHROW(KCALL pagedir_ismapped_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t vpage) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = pagedir_ismapped(vpage);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_iswritable_p") WUNUSED bool
NOTHROW(KCALL pagedir_iswritable_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t vpage) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = pagedir_iswritable(vpage);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_isuseraccessible_p") WUNUSED bool
NOTHROW(KCALL pagedir_isuseraccessible_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t vpage) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = pagedir_isuseraccessible(vpage);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

#ifdef CONFIG_HAVE_PAGEDIR_CHANGED
PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_haschanged_p") WUNUSED bool
NOTHROW(KCALL pagedir_haschanged_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t vpage) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = pagedir_haschanged(vpage);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unsetchanged_p") void
NOTHROW(KCALL pagedir_unsetchanged_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t vpage) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unsetchanged(vpage);
	}
	PAGEDIR_P_ENDUSE(self);
}
#endif /* CONFIG_HAVE_PAGEDIR_CHANGED */

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_prepare_map_p") WUNUSED bool
NOTHROW(KCALL pagedir_prepare_map_p)(VIRT pagedir_t *__restrict self,
                                     VIRT vm_vpage_t virt_page, size_t num_pages) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = pagedir_prepare_map(virt_page, num_pages);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unprepare_map_p") void
NOTHROW(KCALL pagedir_unprepare_map_p)(VIRT pagedir_t *__restrict self,
                                       VIRT vm_vpage_t virt_page, size_t num_pages) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unprepare_map(virt_page, num_pages);
	}
	PAGEDIR_P_ENDUSE(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_maphint_p") void
NOTHROW(KCALL pagedir_maphint_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t virt_page, size_t num_pages,
                                 VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_maphint(virt_page, num_pages, hint);
	}
	PAGEDIR_P_ENDUSE(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_map_p") void
NOTHROW(KCALL pagedir_map_p)(VIRT pagedir_t *__restrict self,
                             VIRT vm_vpage_t virt_page, size_t num_pages,
                             PHYS vm_ppage_t phys_page, u16 perm) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_map(virt_page, num_pages, phys_page, perm);
	}
	PAGEDIR_P_ENDUSE(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unmap_p") void
NOTHROW(KCALL pagedir_unmap_p)(VIRT pagedir_t *__restrict self,
                               VIRT vm_vpage_t virt_page, size_t num_pages) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unmap(virt_page, num_pages);
	}
	PAGEDIR_P_ENDUSE(self);
}

#ifdef CONFIG_HAVE_PAGEDIR_UNWRITE
PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unwrite_p") void
NOTHROW(KCALL pagedir_unwrite_p)(VIRT pagedir_t *__restrict self,
                                 VIRT vm_vpage_t virt_page, size_t num_pages) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unwrite(virt_page, num_pages);
	}
	PAGEDIR_P_ENDUSE(self);
}
#endif /* CONFIG_HAVE_PAGEDIR_UNWRITE */


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_PAGING_C */
