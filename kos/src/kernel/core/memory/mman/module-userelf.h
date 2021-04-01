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
#ifndef GUARD_KERNEL_SRC_MEMORY_MODULE_USERELF_H
#define GUARD_KERNEL_SRC_MEMORY_MODULE_USERELF_H 1

#include <kernel/compiler.h>

#undef CONFIG_HAVE_USERELF_MODULES
#if 1
#define CONFIG_HAVE_USERELF_MODULES 1
#endif

#ifdef CONFIG_HAVE_USERELF_MODULES
#include <kernel/mman/module.h>
#include <sched/lockop.h>

#include <hybrid/sequence/list.h>

#include <compat/kos/exec/elf.h> /* COMPAT_ELF_ARCH_CLASS */
#include <kos/aref.h>
#include <kos/exec/elf.h> /* ELF_ARCH_CLASS */

#include <elf.h>

DECL_BEGIN

#undef UM_HYBRID
#if (defined(_MODULE_HAVE_SIZEOF_POINTER) && \
     COMPAT_ELF_ARCH_CLASS != ELF_ARCH_CLASS)
#define UM_HYBRID
#define UM_ElfW(type) union { Elf32_##type _32; Elf64_##type _64; }
#define UM_any(base) ((base)._32)
#define UM_field(mod, base, field)                    \
	((mod)->md_sizeof_pointer == 4 ? (base)._32 field \
	                               : (base)._64 field)
#define UM_field_ptr(mod, base, field)                         \
	((mod)->md_sizeof_pointer == 4 ? (void *)&(base)._32 field \
	                               : (void *)&(base)._64 field)
#define UM_sizeof(mod, T)                                              \
	((mod)->md_sizeof_pointer == 4 ? sizeof(((__typeof__(T) *)0)->_32) \
	                               : sizeof(((__typeof__(T) *)0)->_64))
#else /* ... */
#define UM_ElfW                        ElfW
#define UM_field(mod, base, field)     (base) field
#define UM_field_ptr(mod, base, field) ((void *)&(base) field)
#define UM_sizeof(mod, T)              sizeof(T)
#define UM_any(base)                   (base)
#endif /* !... */

typedef UM_ElfW(Shdr) UM_ElfW_Shdr;
typedef UM_ElfW(Shdr *) UM_ElfW_ShdrP;
typedef UM_ElfW(Chdr) UM_ElfW_Chdr;


struct userelf_module_section: module_section {
	UM_ElfW_Shdr                              *ums_shdr;     /* [1..1][const] Section header. */
	USER CHECKED void                         *ums_useraddr; /* [const] User-space address of `SHF_ALLOC' sections, or `(void *)-1' for others. */
	KERNEL void                               *ums_kernaddr; /* [0..1][lock(WRITE_ONCE)] Lazily allocated address of this section's
	                                                          * kernel mapping. If not already mapped, set to `(void *)-1' instead. */
	KERNEL void                               *ums_infladdr; /* [0..1][lock(WRITE_ONCE)] Inflated section address. */
	size_t                                     ums_inflsize; /* [0..1][lock(WRITE_ONCE)] Inflated section size. */
	union {
		LIST_ENTRY(REF userelf_module_section) ums_cache;    /* [0..1][lock(INTERN(uems_cache_lock))]  Link entry for the UserELF section cache.
		                                                      * When the associated UserELF module is destroyed, all of its sections are removed
		                                                      * from the section cache. */
		SLIST_ENTRY(userelf_module_section)   _ums_dead;     /* Used internally for async destruction of dead sections. */
	};
};

AWREF(uems_awref, userelf_module_section);
SLIST_HEAD(userelf_module_section_slist, userelf_module_section);

struct userelf_module: module {
	union {
		LIST_ENTRY(REF userelf_module)         um_cache;     /* [0..1][lock(md_mman->mm_lock)][valid_if(md_nodecount != 0)]
		                                                      * Link entry within the UserELF  module cache of the  associated
		                                                      * mman.  When bound, then  this link entry  holds a reference to
		                                                      * the associated module. Additionally, when `md_nodecount' drops
		                                                      * to `0', the module is  removed from the UserELF module  cache,
		                                                      * as per use of the `mo_nonodes' operator. */
		Toblockop(struct mman)                _um_cc_lop;    /* Used for async destruction as the result of removal from the UserELF cache. */
		Tobpostlockop(struct mman)            _um_cc_postlop;/* *ditto* */
		struct lockop                         _um_sc_lop;    /* Used for async removal of sections from the UserELF section cache. */
		struct postlockop                     _um_sc_postlop;/* *ditto* */
		SLIST_ENTRY(userelf_module)           _um_dead;      /* Used internally to chain dead UserELF modules. */
	};
	pos_t                                      um_phoff;     /* [const] == Elf_Ehdr::e_phoff. */
	pos_t                                      um_shoff;     /* [const] == Elf_Ehdr::e_shoff. */
	uint16_t                                   um_phnum;     /* [const] == Elf_Ehdr::e_phnum. */
	uint16_t                                   um_shnum;     /* [const] == Elf_Ehdr::e_shnum. */
	uint16_t                                   um_shstrndx;  /* [const] == Elf_Ehdr::e_shstrndx. (< ue_shnum) */
	uint16_t                                  _um_pad;       /* ... */
	UM_ElfW_ShdrP                              um_shdrs;     /* [0..1][lock(WRICE_ONCE)] Section headers */
	union {
		char                                  *um_shstrtab;  /* [0..1][lock(WRITE_ONCE)][owned] Section headers string table. */
		struct userelf_module_section_slist   _um_deadsect;  /* [link(_ums_dead)] Used internally for async destruction of dead sections. */
	};
	COMPILER_FLEXIBLE_ARRAY(struct uems_awref, um_sections); /* [0..1][lock(WRITE_ONCE)][ue_shnum] Section cache. */
};

/* Operator tables for userelf module objects. */
INTDEF struct module_section_ops const uems_ops;
INTDEF struct module_ops const uem_ops;

/* UserELF module section operators */
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL uems_destroy)(struct userelf_module_section *__restrict self);
INTDEF WUNUSED NONNULL((1)) char const *FCALL uems_getname(struct userelf_module_section *__restrict self);
INTDEF WUNUSED NONNULL((1)) USER CHECKED void *FCALL uems_getaddr(struct userelf_module_section *__restrict self);
INTDEF WUNUSED NONNULL((1)) KERNEL void *FCALL uems_getaddr_alias(struct userelf_module_section *__restrict self);
INTDEF WUNUSED NONNULL((1, 2)) KERNEL void *FCALL uems_getaddr_inflate(struct userelf_module_section *__restrict self, size_t *__restrict psize);

/* UserELF module operators */
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL uem_free)(struct userelf_module *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL uem_destroy)(struct userelf_module *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL uem_nonodes)(struct userelf_module *__restrict self);
INTDEF WUNUSED NONNULL((1)) REF struct userelf_module_section *FCALL uem_locksection(struct userelf_module *__restrict self, USER CHECKED char const *section_name);
INTDEF WUNUSED NONNULL((1)) REF struct userelf_module_section *FCALL uem_locksection_index(struct userelf_module *__restrict self, unsigned int section_index);

/* Generic UserELF module creation functions. */
INTDEF WUNUSED NONNULL((1)) REF struct userelf_module *FCALL uem_fromaddr(struct mman *__restrict self, USER CHECKED void const *addr);
INTDEF WUNUSED NONNULL((1)) REF struct userelf_module *FCALL uem_aboveaddr(struct mman *__restrict self, USER CHECKED void const *addr);
INTDEF WUNUSED NONNULL((1)) REF struct userelf_module *FCALL uem_next(struct mman *__restrict self, struct userelf_module *__restrict prev);

/* Clear the global cache of UserELF sections, and return a
 * number  representative of an approximation of the amount
 * of memory became available as a result of this. */
INTDEF NOBLOCK size_t NOTHROW(KCALL uem_clearsections)(void);

DECL_END
#endif /* CONFIG_HAVE_USERELF_MODULES */

#endif /* !GUARD_KERNEL_SRC_MEMORY_MODULE_USERELF_H */
