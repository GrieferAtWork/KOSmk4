/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MEMORY_MODULE_USERELF_H
#define GUARD_KERNEL_SRC_MEMORY_MODULE_USERELF_H 1

#include <kernel/compiler.h>

/*[[[config CONFIG_HAVE_KERNEL_USERELF_MODULES = true]]]*/
#ifdef CONFIG_NO_KERNEL_USERELF_MODULES
#undef CONFIG_HAVE_KERNEL_USERELF_MODULES
#elif !defined(CONFIG_HAVE_KERNEL_USERELF_MODULES)
#define CONFIG_HAVE_KERNEL_USERELF_MODULES
#elif (-CONFIG_HAVE_KERNEL_USERELF_MODULES - 1) == -1
#undef CONFIG_HAVE_KERNEL_USERELF_MODULES
#define CONFIG_NO_KERNEL_USERELF_MODULES
#endif /* ... */
/*[[[end]]]*/

#if (defined(CONFIG_HAVE_KERNEL_USERELF_MODULES) || !defined(BUILDING_KERNEL_CORE))
#include <kernel/mman/module.h>

#include <hybrid/sequence/list.h>

#include <compat/kos/exec/elf.h> /* COMPAT_ELF_ARCH_CLASS */
#include <kos/aref.h>
#include <kos/exec/elf.h> /* ELF_ARCH_CLASS */
#include <kos/lockop.h>

#include <elf.h>

DECL_BEGIN

#undef UM_HYBRID
#if (defined(_MODULE_HAVE_SIZEOF_POINTER) && \
     COMPAT_ELF_ARCH_CLASS != ELF_ARCH_CLASS)
#define UM_HYBRID
#define UM_ElfW(type) union { Elf32_##type _32; Elf64_##type _64; }
#define UM_any(base) ((base)._32)
#define UM_field_r(sizeof_pointer, base, field) \
	((sizeof_pointer) == 4 ? (base)._32 field   \
	                       : (base)._64 field)
#define UM_field_ptr_r(sizeof_pointer, base, field)    \
	((sizeof_pointer) == 4 ? (void *)&(base)._32 field \
	                       : (void *)&(base)._64 field)
#define UM_sizeof_r(sizeof_pointer, T)                         \
	((sizeof_pointer) == 4 ? sizeof(((__typeof__(T) *)0)->_32) \
	                       : sizeof(((__typeof__(T) *)0)->_64))
#else /* ... */
#define UM_ElfW                                     ElfW
#define UM_field_r(sizeof_pointer, base, field)     (base) field
#define UM_field_ptr_r(sizeof_pointer, base, field) ((void *)&(base) field)
#define UM_sizeof_r(sizeof_pointer, T)              sizeof(T)
#define UM_any(base)                                (base)
#endif /* !... */
#define UM_field(mod, base, field)     UM_field_r((mod)->md_sizeof_pointer, base, field)
#define UM_field_ptr(mod, base, field) UM_field_ptr_r((mod)->md_sizeof_pointer, base, field)
#define UM_sizeof(mod, T)              UM_sizeof_r((mod)->md_sizeof_pointer, T)

typedef UM_ElfW(Shdr) UM_ElfW_Shdr;
typedef UM_ElfW(Shdr *) UM_ElfW_ShdrP;
typedef UM_ElfW(Chdr) UM_ElfW_Chdr;
typedef UM_ElfW(Ehdr) UM_ElfW_Ehdr;
typedef UM_ElfW(Phdr) UM_ElfW_Phdr;
typedef UM_ElfW(Phdr *) UM_ElfW_PhdrP;


struct userelf_module_section: module_section {
	UM_ElfW_Shdr        *ums_shdr;     /* [1..1][const] Section header. */
	byte_t USER CHECKED *ums_useraddr; /* [const] User-space address of `SHF_ALLOC' sections, or `(void *)-1' for others. */
	KERNEL byte_t       *ums_kernaddr; /* [0..1][lock(WRITE_ONCE)] Lazily allocated address of this section's
	                                    * kernel mapping. If not already mapped, set to `(void *)-1' instead. */
	KERNEL byte_t       *ums_infladdr; /* [0..1][lock(WRITE_ONCE)] Inflated section address. */
	size_t               ums_inflsize; /* [0..1][lock(WRITE_ONCE)] Inflated section size. */
};

AWREF(uems_awref, userelf_module_section);

#ifndef __module_section_slist_defined
#define __module_section_slist_defined
SLIST_HEAD(module_section_slist, module_section);
#endif /* !__module_section_slist_defined */

struct userelf_module: module {
	union {
		LIST_ENTRY(REF userelf_module)         um_cache;      /* [0..1][lock(md_mman->mm_lock)][valid_if(md_nodecount != 0)]
		                                                       * Link entry within the UserELF  module cache of the  associated
		                                                       * mman.  When bound, then  this link entry  holds a reference to
		                                                       * the associated module. Additionally, when `md_nodecount' drops
		                                                       * to `0', the module is  removed from the UserELF module  cache,
		                                                       * as per use of the `mo_nonodes' operator. */
		Toblockop(mman)                       _um_cc_lop;     /* Used for async destruction as the result of removal from the UserELF cache. */
		Tobpostlockop(mman)                   _um_cc_postlop; /* *ditto* */
		struct lockop                         _um_sc_lop;     /* Used for async removal of sections from the UserELF section cache. */
		struct postlockop                     _um_sc_postlop; /* *ditto* */
		SLIST_ENTRY(userelf_module)           _um_dead;       /* Used internally to chain dead UserELF modules. */
	};
	pos_t                                      um_shoff;      /* [const] == Elf_Ehdr::e_shoff. */
	uint16_t                                   um_phnum;      /* [const] == Elf_Ehdr::e_phnum. */
	uint16_t                                   um_shnum;      /* [const] == Elf_Ehdr::e_shnum. */
	uint16_t                                   um_shstrndx;   /* [const] == Elf_Ehdr::e_shstrndx. (< ue_shnum) */
	uint16_t                                  _um_pad;        /* ... */
#if defined(__i386__) || (defined(__x86_64__) && defined(__ARCH_HAVE_COMPAT))
	uint32_t                                  _um_DT_PLTGOT;
#define _userelf_module_init__um_DT_PLTGOT(self) ((self)->_um_DT_PLTGOT = (uint32_t)-1)
#endif /* __i386__ || (__x86_64__ && __ARCH_HAVE_COMPAT) */
	UM_ElfW_PhdrP                              um_phdrs;      /* [1..um_phnum][const][owned] Program headers */
	UM_ElfW_ShdrP                              um_shdrs;      /* [0..1][lock(WRICE_ONCE)][owned] Section headers */
	union {
		char                                  *um_shstrtab;   /* [0..1][lock(WRITE_ONCE)][owned] Section headers string table. */
		struct module_section_slist           _um_deadsect;   /* [link(_ums_dead)] Used internally for async destruction of dead sections. */
	};
	COMPILER_FLEXIBLE_ARRAY(struct uems_awref, um_sections);  /* [0..1][lock(WRITE_ONCE)][ue_shnum] Section cache. */
};

#ifndef _userelf_module_init__um_DT_PLTGOT
#define _userelf_module_init__um_DT_PLTGOT(self) (void)0
#endif /* !_userelf_module_init__um_DT_PLTGOT */

/* Initialize arch-specific fields of `self' */
#define _userelf_module_init_arch(self) \
	(_userelf_module_init__um_DT_PLTGOT(self))



#ifdef BUILDING_KERNEL_CORE
/* Operator tables for userelf module objects. */
INTDEF struct module_section_ops const uems_ops;
INTDEF struct module_ops const uem_ops;

/* UserELF module section operators */
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL uems_destroy)(struct userelf_module_section *__restrict self);
INTDEF BLOCKING WUNUSED NONNULL((1)) char const *FCALL uems_getname(struct userelf_module_section *__restrict self);
INTDEF BLOCKING WUNUSED NONNULL((1)) byte_t USER CHECKED *FCALL uems_getaddr(struct userelf_module_section *__restrict self);
INTDEF BLOCKING WUNUSED NONNULL((1)) KERNEL byte_t *FCALL uems_getaddr_alias(struct userelf_module_section *__restrict self);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) KERNEL byte_t *FCALL uems_getaddr_inflate(struct userelf_module_section *__restrict self, size_t *__restrict psize);

/* UserELF module operators */
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL uem_free)(struct userelf_module *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL uem_destroy)(struct userelf_module *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL uem_nonodes)(struct userelf_module *__restrict self);
INTDEF BLOCKING WUNUSED NONNULL((1)) REF struct userelf_module_section *FCALL uem_locksection(struct userelf_module *__restrict self, USER CHECKED char const *section_name);
INTDEF BLOCKING WUNUSED NONNULL((1)) REF struct userelf_module_section *FCALL uem_locksection_index(struct userelf_module *__restrict self, unsigned int section_index);
INTDEF BLOCKING WUNUSED NONNULL((1, 3)) bool FCALL uem_sectinfo(struct userelf_module *__restrict self, uintptr_t module_relative_addr, struct module_sectinfo *__restrict info);


/* Generic UserELF module creation functions. */
INTDEF BLOCKING WUNUSED NONNULL((1)) REF struct userelf_module *FCALL uem_fromaddr(struct mman *__restrict self, USER CHECKED void const *addr);
INTDEF BLOCKING WUNUSED NONNULL((1)) REF struct userelf_module *FCALL uem_aboveaddr(struct mman *__restrict self, USER CHECKED void const *addr);
INTDEF BLOCKING WUNUSED NONNULL((1)) REF struct userelf_module *FCALL uem_next(struct mman *__restrict self, struct module *__restrict prev);
#endif /* BUILDING_KERNEL_CORE */

DECL_END
#endif /* CONFIG_HAVE_KERNEL_USERELF_MODULES || !BUILDING_KERNEL_CORE */

#endif /* !GUARD_KERNEL_SRC_MEMORY_MODULE_USERELF_H */
