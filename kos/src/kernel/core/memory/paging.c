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


#ifdef __INTELLISENSE__
#define DEFINE_PAGEDIR_P_BEGIN(self) do
#define DEFINE_PAGEDIR_P_END(self)   __WHILE0
#else /* __INTELLISENSE__ */
#define DEFINE_PAGEDIR_P_BEGIN(self)                          \
	do {                                                      \
		PAGEDIR_P_SELFTYPE _old_pdir;                         \
		pflag_t _p_was = PREEMPTION_PUSHOFF();                \
		assert(IS_ALIGNED((uintptr_t)(self), PAGEDIR_ALIGN)); \
		_old_pdir = pagedir_get();                            \
		if (_old_pdir != (self))                              \
			pagedir_set(self);                                \
		do
#define DEFINE_PAGEDIR_P_END(self)  \
		__WHILE0;                   \
		if (_old_pdir != (self))    \
			pagedir_set(_old_pdir); \
		PREEMPTION_POP(_p_was);     \
	} __WHILE0
#endif /* !__INTELLISENSE__ */



PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_prepare_mapone_p") WUNUSED bool
NOTHROW(KCALL pagedir_prepare_mapone_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page) {
	bool result;
	DEFINE_PAGEDIR_P_BEGIN(self) {
		result = pagedir_prepare_mapone(virt_page);
	}
	DEFINE_PAGEDIR_P_END(self);
	return result;
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unprepare_mapone_p") void
NOTHROW(KCALL pagedir_unprepare_mapone_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t virt_page) {
	DEFINE_PAGEDIR_P_BEGIN(self) {
		pagedir_unprepare_mapone(virt_page);
	}
	DEFINE_PAGEDIR_P_END(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_maphintone_p") void
NOTHROW(KCALL pagedir_maphintone_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t virt_page,
                                    VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
	DEFINE_PAGEDIR_P_BEGIN(self) {
		pagedir_maphintone(virt_page, hint);
	}
	DEFINE_PAGEDIR_P_END(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_mapone_p") void
NOTHROW(KCALL pagedir_mapone_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t virt_page,
                                PHYS vm_ppage_t phys_page, u16 perm) {
	DEFINE_PAGEDIR_P_BEGIN(self) {
		pagedir_mapone(virt_page, phys_page, perm);
	}
	DEFINE_PAGEDIR_P_END(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unmapone_p") void
NOTHROW(KCALL pagedir_unmapone_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t virt_page) {
	DEFINE_PAGEDIR_P_BEGIN(self) {
		pagedir_unmapone(virt_page);
	}
	DEFINE_PAGEDIR_P_END(self);
}

#ifdef CONFIG_HAVE_PAGEDIR_UNWRITE
PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unwriteone_p") void
NOTHROW(KCALL pagedir_unwriteone_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t virt_page) {
	DEFINE_PAGEDIR_P_BEGIN(self) {
		pagedir_unwriteone(virt_page);
	}
	DEFINE_PAGEDIR_P_END(self);
}
#endif /* CONFIG_HAVE_PAGEDIR_UNWRITE */

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unmap_userspace_p") void
NOTHROW(KCALL pagedir_unmap_userspace_p)(VIRT pagedir_t *__restrict self,
                                         struct vm *__restrict sync_vm) {
	DEFINE_PAGEDIR_P_BEGIN(self) {
		pagedir_unmap_userspace(sync_vm);
	}
	DEFINE_PAGEDIR_P_END(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unmap_userspace_nosync_p") void
NOTHROW(KCALL pagedir_unmap_userspace_nosync_p)(VIRT pagedir_t *__restrict self) {
	DEFINE_PAGEDIR_P_BEGIN(self) {
		pagedir_unmap_userspace_nosync();
	}
	DEFINE_PAGEDIR_P_END(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_translate_p") WUNUSED PHYS vm_phys_t
NOTHROW(KCALL pagedir_translate_p)(VIRT pagedir_t *__restrict self, VIRT vm_virt_t virt_addr) {
	PHYS vm_phys_t result;
	DEFINE_PAGEDIR_P_BEGIN(self) {
		result = pagedir_translate(virt_addr);
	}
	DEFINE_PAGEDIR_P_END(self);
	return result;
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_ismapped_p") WUNUSED bool
NOTHROW(KCALL pagedir_ismapped_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t vpage) {
	bool result;
	DEFINE_PAGEDIR_P_BEGIN(self) {
		result = pagedir_ismapped(vpage);
	}
	DEFINE_PAGEDIR_P_END(self);
	return result;
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_iswritable_p") WUNUSED bool
NOTHROW(KCALL pagedir_iswritable_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t vpage) {
	bool result;
	DEFINE_PAGEDIR_P_BEGIN(self) {
		result = pagedir_iswritable(vpage);
	}
	DEFINE_PAGEDIR_P_END(self);
	return result;
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_isuseraccessible_p") WUNUSED bool
NOTHROW(KCALL pagedir_isuseraccessible_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t vpage) {
	bool result;
	DEFINE_PAGEDIR_P_BEGIN(self) {
		result = pagedir_isuseraccessible(vpage);
	}
	DEFINE_PAGEDIR_P_END(self);
	return result;
}

#ifdef CONFIG_HAVE_PAGEDIR_CHANGED
PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_haschanged_p") WUNUSED bool
NOTHROW(KCALL pagedir_haschanged_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t vpage) {
	bool result;
	DEFINE_PAGEDIR_P_BEGIN(self) {
		result = pagedir_haschanged(vpage);
	}
	DEFINE_PAGEDIR_P_END(self);
	return result;
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unsetchanged_p") void
NOTHROW(KCALL pagedir_unsetchanged_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t vpage) {
	DEFINE_PAGEDIR_P_BEGIN(self) {
		pagedir_unsetchanged(vpage);
	}
	DEFINE_PAGEDIR_P_END(self);
}
#endif /* CONFIG_HAVE_PAGEDIR_CHANGED */

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_prepare_map_p") WUNUSED bool
NOTHROW(KCALL pagedir_prepare_map_p)(VIRT pagedir_t *__restrict self,
                                     VIRT vm_vpage_t virt_page, size_t num_pages) {
	bool result;
	DEFINE_PAGEDIR_P_BEGIN(self) {
		result = pagedir_prepare_map(virt_page, num_pages);
	}
	DEFINE_PAGEDIR_P_END(self);
	return result;
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unprepare_map_p") void
NOTHROW(KCALL pagedir_unprepare_map_p)(VIRT pagedir_t *__restrict self,
                                       VIRT vm_vpage_t virt_page, size_t num_pages) {
	DEFINE_PAGEDIR_P_BEGIN(self) {
		pagedir_unprepare_map(virt_page, num_pages);
	}
	DEFINE_PAGEDIR_P_END(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_maphint_p") void
NOTHROW(KCALL pagedir_maphint_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t virt_page, size_t num_pages,
                                 VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
	DEFINE_PAGEDIR_P_BEGIN(self) {
		pagedir_maphint(virt_page, num_pages, hint);
	}
	DEFINE_PAGEDIR_P_END(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_map_p") void
NOTHROW(KCALL pagedir_map_p)(VIRT pagedir_t *__restrict self,
                             VIRT vm_vpage_t virt_page, size_t num_pages,
                             PHYS vm_ppage_t phys_page, u16 perm) {
	DEFINE_PAGEDIR_P_BEGIN(self) {
		pagedir_map(virt_page, num_pages, phys_page, perm);
	}
	DEFINE_PAGEDIR_P_END(self);
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unmap_p") void
NOTHROW(KCALL pagedir_unmap_p)(VIRT pagedir_t *__restrict self,
                               VIRT vm_vpage_t virt_page, size_t num_pages) {
	DEFINE_PAGEDIR_P_BEGIN(self) {
		pagedir_unmap(virt_page, num_pages);
	}
	DEFINE_PAGEDIR_P_END(self);
}

#ifdef CONFIG_HAVE_PAGEDIR_UNWRITE
PUBLIC NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.pagedir_p.pagedir_unwrite_p") void
NOTHROW(KCALL pagedir_unwrite_p)(VIRT pagedir_t *__restrict self,
                                 VIRT vm_vpage_t virt_page, size_t num_pages) {
	DEFINE_PAGEDIR_P_BEGIN(self) {
		pagedir_unwrite(virt_page, num_pages);
	}
	DEFINE_PAGEDIR_P_END(self);
}
#endif /* CONFIG_HAVE_PAGEDIR_UNWRITE */


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_PAGING_C */
