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
NOTHROW(KCALL pagedir_prepare_mapone_p)(PAGEDIR_P_SELFTYPE self,
                                        PAGEDIR_PAGEALIGNED VIRT void *addr) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = pagedir_prepare_mapone(addr);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unprepare_mapone_p") void
NOTHROW(KCALL pagedir_unprepare_mapone_p)(PAGEDIR_P_SELFTYPE self,
                                          PAGEDIR_PAGEALIGNED VIRT void *addr) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unprepare_mapone(addr);
	}
	PAGEDIR_P_ENDUSE(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_maphintone_p") void
NOTHROW(KCALL pagedir_maphintone_p)(PAGEDIR_P_SELFTYPE self,
                                    PAGEDIR_PAGEALIGNED VIRT void *addr,
                                    VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_maphintone(addr, hint);
	}
	PAGEDIR_P_ENDUSE(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_mapone_p") void
NOTHROW(KCALL pagedir_mapone_p)(PAGEDIR_P_SELFTYPE self,
                                PAGEDIR_PAGEALIGNED VIRT void *addr,
                                PAGEDIR_PAGEALIGNED PHYS vm_phys_t phys, u16 perm) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_mapone(addr, phys, perm);
	}
	PAGEDIR_P_ENDUSE(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unmapone_p") void
NOTHROW(KCALL pagedir_unmapone_p)(PAGEDIR_P_SELFTYPE self,
                                  PAGEDIR_PAGEALIGNED VIRT void *addr) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unmapone(addr);
	}
	PAGEDIR_P_ENDUSE(self);
}

#ifdef ARCH_PAGEDIR_HAVE_UNWRITE
PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unwriteone_p") void
NOTHROW(KCALL pagedir_unwriteone_p)(PAGEDIR_P_SELFTYPE self,
                                    PAGEDIR_PAGEALIGNED VIRT void *addr) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unwriteone(addr);
	}
	PAGEDIR_P_ENDUSE(self);
}
#endif /* ARCH_PAGEDIR_HAVE_UNWRITE */

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_prepare_map_p") WUNUSED bool
NOTHROW(KCALL pagedir_prepare_map_p)(PAGEDIR_P_SELFTYPE self,
                                     PAGEDIR_PAGEALIGNED VIRT void *addr,
                                     PAGEDIR_PAGEALIGNED size_t num_bytes) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = pagedir_prepare_map(addr, num_bytes);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_prepare_map_p_keep") WUNUSED bool
NOTHROW(KCALL pagedir_prepare_map_keep_p)(PAGEDIR_P_SELFTYPE self,
                                          PAGEDIR_PAGEALIGNED VIRT void *addr,
                                          PAGEDIR_PAGEALIGNED size_t num_bytes) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = pagedir_prepare_map_keep(addr, num_bytes);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unprepare_map_p") void
NOTHROW(KCALL pagedir_unprepare_map_p)(PAGEDIR_P_SELFTYPE self,
                                       PAGEDIR_PAGEALIGNED VIRT void *addr,
                                       PAGEDIR_PAGEALIGNED size_t num_bytes) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unprepare_map(addr, num_bytes);
	}
	PAGEDIR_P_ENDUSE(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_maphint_p") void
NOTHROW(KCALL pagedir_maphint_p)(PAGEDIR_P_SELFTYPE self,
                                 PAGEDIR_PAGEALIGNED VIRT void *addr,
                                 PAGEDIR_PAGEALIGNED size_t num_bytes,
                                 VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_maphint(addr, num_bytes, hint);
	}
	PAGEDIR_P_ENDUSE(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_map_p") void
NOTHROW(KCALL pagedir_map_p)(PAGEDIR_P_SELFTYPE self,
                             PAGEDIR_PAGEALIGNED VIRT void *addr,
                             PAGEDIR_PAGEALIGNED size_t num_bytes,
                             PAGEDIR_PAGEALIGNED PHYS vm_phys_t phys,
                             u16 perm) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_map(addr, num_bytes, phys, perm);
	}
	PAGEDIR_P_ENDUSE(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unmap_p") void
NOTHROW(KCALL pagedir_unmap_p)(PAGEDIR_P_SELFTYPE self,
                               PAGEDIR_PAGEALIGNED VIRT void *addr,
                               PAGEDIR_PAGEALIGNED size_t num_bytes) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unmap(addr, num_bytes);
	}
	PAGEDIR_P_ENDUSE(self);
}

#ifdef ARCH_PAGEDIR_HAVE_UNWRITE
PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unwrite_p") void
NOTHROW(KCALL pagedir_unwrite_p)(PAGEDIR_P_SELFTYPE self,
                                 PAGEDIR_PAGEALIGNED VIRT void *addr,
                                 PAGEDIR_PAGEALIGNED size_t num_bytes) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unwrite(addr, num_bytes);
	}
	PAGEDIR_P_ENDUSE(self);
}
#endif /* ARCH_PAGEDIR_HAVE_UNWRITE */

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_ismapped_p") WUNUSED bool
NOTHROW(KCALL pagedir_ismapped_p)(PAGEDIR_P_SELFTYPE self,
                                  VIRT void const *addr) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = pagedir_ismapped(addr);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_iswritable_p") WUNUSED bool
NOTHROW(KCALL pagedir_iswritable_p)(PAGEDIR_P_SELFTYPE self,
                                    VIRT void *addr) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = pagedir_iswritable(addr);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_isuseraccessible_p") WUNUSED bool
NOTHROW(KCALL pagedir_isuseraccessible_p)(PAGEDIR_P_SELFTYPE self,
                                          VIRT void const *addr) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = pagedir_isuseraccessible(addr);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

#ifdef ARCH_PAGEDIR_HAVE_CHANGED
PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_haschanged_p") WUNUSED bool
NOTHROW(KCALL pagedir_haschanged_p)(PAGEDIR_P_SELFTYPE self,
                                    VIRT void *addr) {
	bool result;
	PAGEDIR_P_BEGINUSE(self) {
		result = pagedir_haschanged(addr);
	}
	PAGEDIR_P_ENDUSE(self);
	return result;
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unsetchanged_p") void
NOTHROW(KCALL pagedir_unsetchanged_p)(PAGEDIR_P_SELFTYPE self,
                                      VIRT void *addr) {
	PAGEDIR_P_BEGINUSE(self) {
		pagedir_unsetchanged(addr);
	}
	PAGEDIR_P_ENDUSE(self);
}
#endif /* ARCH_PAGEDIR_HAVE_CHANGED */

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
