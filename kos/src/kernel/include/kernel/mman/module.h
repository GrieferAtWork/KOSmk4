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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MODULE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MODULE_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <hybrid/__assert.h>
#include <hybrid/sequence/list.h>

#include <bits/crt/format-printer.h>
#include <compat/config.h>

#ifdef __WANT_MODULE__md_mmlop
#include <kos/lockop.h>
#endif /* __WANT_MODULE__md_mmlop */

#ifdef __CC__
DECL_BEGIN

/* Common base-class for any kind of executable object descriptor:
 *   - Userspace library/application accessor interface (allowing
 *     for  kernel-space access to debug information contained in
 *     user-space application)
 *   - Kernelspace, dynamically loaded drivers
 */

struct module;
struct module_section;
struct mfile;
struct path;
struct fdirent;
struct mman;

struct module_section_ops {
	/* [1..1] Destroy the given module section. */
	NOBLOCK NONNULL_T((1)) void
	NOTHROW_T(FCALL *ms_destroy)(struct module_section *__restrict self);

	/* [1..1] Return the name of this section.
	 * If the name  can't be determined,  then return  `NULL'
	 * instead. Before calling this function, the caller must
	 * ensure that `!wasdestroyed(self->ms_module)') */
	BLOCKING ATTR_PURE_T WUNUSED_T NONNULL_T((1)) char const *
	(FCALL *ms_getname)(struct module_section *__restrict self);

	/* [1..1] Return the address of this module's section mapping.
	 * If the section  has the `SHF_ALLOC'  flag set, then  return
	 * the address at  which the section  had already been  loaded
	 * into memory as  the result of  the associated module  being
	 * loaded.
	 * Otherwise,  lazily  create a  kernel-space memory  mapping of
	 * the section's contents, and return a pointer to said mapping.
	 * In either  case, the  returned data-blob  (which has  a  size
	 * that is specified by  `self->ms_size') may be accessed  until
	 * the caller drops a reference from `self'
	 * WARNING: In case of user-space module sections that have  the
	 *          `SHF_ALLOC'  flag set, the returned buffer obviously
	 *          resides in user-space, also meaning that it may only
	 *          be accessed while the correct mman/pagedir is active */
	BLOCKING WUNUSED_T NONNULL_T((1)) byte_t USER CHECKED *
	(FCALL *ms_getaddr)(struct module_section *__restrict self);

	/* [1..1] Similar  to `ms_getaddr' (and  identical in case of
	 * kernel-space driver modules). However, a difference exists
	 * for user-space modules, in that user-space module sections
	 * that have the `SHF_ALLOC' flag  set will still be  aliased
	 * by  a  lazily allocated  kernel-space memory  mapping, the
	 * address of which is then  returned. As such, the  returned
	 * buffer  can be dereferenced  irregardless of the currently
	 * active mman, since it will be apart of kernel-space. */
	BLOCKING WUNUSED_T NONNULL_T((1)) KERNEL byte_t *
	(FCALL *ms_getaddr_alias)(struct module_section *__restrict self);

	/* [1..1] Similar to `ms_getaddr_alias()', but if the section
	 * contains compressed data, inflate  that data, map it  into
	 * the  kernel, and return a pointer to that mapping, as well
	 * as the size (in bytes) of the decompressed data blob.
	 *
	 * If the section isn't compressed, call `ms_getaddr_alias()'
	 * and write `self->ms_size' to `*psize' */
	BLOCKING WUNUSED_T NONNULL_T((1, 2)) KERNEL byte_t *
	(FCALL *ms_getaddr_inflate)(struct module_section *__restrict self,
	                            size_t *__restrict psize);
};

#undef _MODULE_HAVE_SIZEOF_POINTER
#if defined(__ARCH_HAVE_COMPAT) && __ARCH_COMPAT_SIZEOF_POINTER != __SIZEOF_POINTER__
#define _MODULE_HAVE_SIZEOF_POINTER
#endif /* __ARCH_HAVE_COMPAT && __ARCH_COMPAT_SIZEOF_POINTER != __SIZEOF_POINTER__ */

struct module_section {
	WEAK refcnt_t                    ms_refcnt;  /* Reference counter. */
	struct module_section_ops const *ms_ops;     /* [1..1][const] Module section operators. */
	WEAK REF struct module          *ms_module;  /* [1..1][const] Associated module. */
	size_t                           ms_size;    /* [const] Size of the section (in bytes) */
	size_t                           ms_entsize; /* [const] Section entity size (or 0 if unknown) */
	unsigned int                     ms_type;    /* [const] Section type (s.a. `Elf_Shdr::sh_type'; one of `SHT_*' from <elf.h>) */
	unsigned int                     ms_flags;   /* [const] Section flags (s.a. `Elf_Shdr::sh_flags'; set of `SHF_*' from <elf.h>) */
	unsigned int                     ms_link;    /* [const] Section link (s.a. `Elf_Shdr::sh_link') */
	unsigned int                     ms_info;    /* [const] Section info (s.a. `Elf_Shdr::sh_info') */
#ifdef __WANT_MODULE_SECTION__ms_dead
	union {
		LIST_ENTRY(REF module_section) ms_cache; /* [0..1][lock(module_section_cache_lock)] Link entry for the section cache.
		                                          * When the associated module is destroyed, all of its sections are  removed
		                                          * from the section cache. */
		SLIST_ENTRY(module_section) _ms_dead;    /* Used internally for async destruction of dead sections. */
	};
#else /* __WANT_MODULE_SECTION__ms_dead */
	LIST_ENTRY(REF module_section)   ms_cache;   /* [0..1][lock(module_section_cache_lock)] Link entry for the section cache.
	                                              * When the associated module is destroyed, all of its sections are  removed
	                                              * from the section cache. */
#endif /* !__WANT_MODULE_SECTION__ms_dead */
};

#define module_section_destroy(self) (*(self)->ms_ops->ms_destroy)(self)
DEFINE_REFCNT_FUNCTIONS(struct module_section, ms_refcnt, module_section_destroy)

/* Wrappers for module section operators. */
#ifdef __INTELLISENSE__
BLOCKING WUNUSED NONNULL((1)) char const *(module_section_getname)(struct module_section *__restrict self);
BLOCKING WUNUSED NONNULL((1)) byte_t USER CHECKED *(module_section_getaddr)(struct module_section *__restrict self);
BLOCKING WUNUSED NONNULL((1)) KERNEL byte_t *(module_section_getaddr_alias)(struct module_section *__restrict self);
BLOCKING WUNUSED NONNULL((1, 2)) KERNEL byte_t *(module_section_getaddr_inflate)(struct module_section *__restrict self, size_t *__restrict psize);
#else /* __INTELLISENSE__ */
#define module_section_getname(self)                (*(self)->ms_ops->ms_getname)(self)
#define module_section_getaddr(self)                (*(self)->ms_ops->ms_getaddr)(self)
#define module_section_getaddr_alias(self)          (*(self)->ms_ops->ms_getaddr_alias)(self)
#define module_section_getaddr_inflate(self, psize) (*(self)->ms_ops->ms_getaddr_inflate)(self, psize)
#endif /* !__INTELLISENSE__ */

/* Same as the functions above, but preserve the current exception, and return `NULL' on error. */
FUNDEF BLOCKING WUNUSED NONNULL((1)) char const *NOTHROW(FCALL module_section_getname_nx)(struct module_section *__restrict self);
FUNDEF BLOCKING WUNUSED NONNULL((1)) byte_t USER CHECKED *NOTHROW(FCALL module_section_getaddr_nx)(struct module_section *__restrict self);
FUNDEF BLOCKING WUNUSED NONNULL((1)) KERNEL byte_t *NOTHROW(FCALL module_section_getaddr_alias_nx)(struct module_section *__restrict self);
FUNDEF BLOCKING WUNUSED NONNULL((1, 2)) KERNEL byte_t *NOTHROW(FCALL module_section_getaddr_inflate_nx)(struct module_section *__restrict self, size_t *__restrict psize);


struct module_sectinfo {
	char const  *msi_name;    /* [0..1] Section name. */
	uintptr_t    msi_addr;    /* Section address. (module-relative) */
	size_t       msi_size;    /* Size of the section (in bytes) */
	size_t       msi_entsize; /* Section entity size (or 0 if unknown) */
	unsigned int msi_type;    /* Section type (s.a. `Elf_Shdr::sh_type'; one of `SHT_*') */
	unsigned int msi_flags;   /* Section flags (s.a. `Elf_Shdr::sh_flags'; set of `SHF_*') */
	unsigned int msi_link;    /* Section link (s.a. `Elf_Shdr::sh_link') */
	unsigned int msi_info;    /* Section info (s.a. `Elf_Shdr::sh_info') */
	unsigned int msi_index;   /* Section index (for use with `mo_locksection_index') */
};

struct module_ops {
	/* [1..1] Module free callback */
	NOBLOCK NONNULL_T((1)) void
	NOTHROW_T(FCALL *mo_free)(struct module *__restrict self);

	/* [1..1] Module destroy callback */
	NOBLOCK NONNULL_T((1)) void
	NOTHROW_T(FCALL *mo_destroy)(struct module *__restrict self);

	/* [1..1] Callback invoked when `md_nodecount' drops to 0.
	 * NOTE: This callback must be invoked while holding a
	 *       lock to the mappings-tree of `self->md_mman'. */
	NOBLOCK NONNULL_T((1)) void
	NOTHROW_T(FCALL *mo_nonodes)(struct module *__restrict self);

	/* [1..1] Return a reference for a module section, given its name.
	 * If   the  given  `section_name'  isn't  valid,  return  `NULL'. */
	BLOCKING WUNUSED_T NONNULL_T((1)) REF struct module_section *
	(FCALL *mo_locksection)(struct module *__restrict self,
	                        USER CHECKED char const *section_name);

	/* [1..1] Return a reference for a module section, given its index.
	 * If   the  given  `section_index'  isn't  valid,  return  `NULL'. */
	BLOCKING WUNUSED_T NONNULL_T((1)) REF struct module_section *
	(FCALL *mo_locksection_index)(struct module *__restrict self,
	                              unsigned int section_index);

	/* [1..1] Try to lookup information about the section that a given
	 * `module_relative_addr' belongs to, returning information  about
	 * that section in `*info'. Note that only SHF_ALLOC-sections  can
	 * be found using this function!
	 * @return: true: Success (section info was filled in) */
	BLOCKING WUNUSED_T NONNULL_T((1, 3)) __BOOL
	(FCALL *mo_sectinfo)(struct module *__restrict self,
	                     uintptr_t module_relative_addr,
	                     struct module_sectinfo *__restrict info);

	/* [1..1] Return the text/data base address for `self' (as used by unwinding)
	 * NOTE: `self' is only non-const in  order to allow for lazy  initialization.
	 * These functions may not alter the state of `self' in any observable manner! */
	BLOCKING WUNUSED_T NONNULL_T((1)) void const *NOTHROW_T(FCALL *mo_get_tbase)(struct module *__restrict self);
	BLOCKING WUNUSED_T NONNULL_T((1)) void const *NOTHROW_T(FCALL *mo_get_dbase)(struct module *__restrict self);
};

struct module {
	WEAK refcnt_t               md_refcnt;     /* Reference counter. */
	WEAK refcnt_t               md_weakrefcnt; /* Weak reference counter. */
	refcnt_t                    md_nodecount;  /* [lock(md_mman->mm_lock)] # of  `struct mnode'
	                                            * structs that contain pointers to this module.
	                                            * When this drops to  0, which may only  happen
	                                            * once for any  given module, the  `mo_nonodes'
	                                            * operator must be invoked. */
	struct module_ops const    *md_ops;        /* [1..1][const] Module operators. */
	WEAK REF struct mman       *md_mman;       /* [1..1][const] Associated mman. */
	uintptr_t                   md_loadaddr;   /* [const] Load address of the module. */
	byte_t                     *md_loadmin;    /* [const] Lowest address mapped by this module. */
	byte_t                     *md_loadmax;    /* [const] Greatest address mapped by this module. */
	REF struct mfile           *md_file;       /* [0..1][lock(WRITE_ONCE)] The backing file of the executable. */
#ifdef __WANT_MODULE__md_mmlop
	union {
		struct {
			REF struct path    *md_fspath;     /* [0..1][const] Optional mapping path */
			REF struct fdirent *md_fsname;     /* [0..1][const] Optional mapping name */
		};
		Toblockop(mman)        _md_mmlop;      /* MMan cleanup lock operation */
		Tobpostlockop(mman)    _md_mmpostlop;  /* MMan cleanup post lock operation */
	};
#else /* __WANT_MODULE__md_mmlop */
	REF struct path            *md_fspath;     /* [0..1][const] Optional mapping path */
	REF struct fdirent         *md_fsname;     /* [0..1][const] Optional mapping name */
#endif /* !__WANT_MODULE__md_mmlop */
#ifdef _MODULE_HAVE_SIZEOF_POINTER
	byte_t                      md_sizeof_pointer; /* [const] `sizeof(void *)', as seen by this module. */
	byte_t                     _md_pad[sizeof(void *) - 1];
#else /* _MODULE_HAVE_SIZEOF_POINTER */
	byte_t                     _md_pad[sizeof(void *)];
#endif /* !_MODULE_HAVE_SIZEOF_POINTER */
	/* Module-specific data goes here.
	 * NOTE: Module-descriptors for  `/lib/libdl.so' have  `md_fspath == NULL',
	 *       while `md_fsname' points to a string reference that specific path. */
};

/* Increment/decrement  the  `md_nodecount' counter  of `self'
 * Note that this doesn't happen atomically because the caller
 * must be holding a lock to `self->md_mman->mm_lock'. */
#define module_inc_nodecount(self) \
	(void)(__hybrid_assert((self)->md_nodecount != 0), ++(self)->md_nodecount)
#define module_dec_nodecount(self)                     \
	(void)(__hybrid_assert((self)->md_nodecount != 0), \
	       (--(self)->md_nodecount || ((*(self)->md_ops->mo_nonodes)(self), 0)))

#define module_free(self)    (*(self)->md_ops->mo_free)(self)
#define module_destroy(self) (*(self)->md_ops->mo_destroy)(self)
DEFINE_REFCNT_FUNCTIONS(struct module, md_refcnt, module_destroy)
DEFINE_WEAKREFCNT_FUNCTIONS(struct module, md_weakrefcnt, module_free)

/* Clear all of the mman->mnode->module self-pointers associated with `self',
 * drop a weak reference from `self->md_mman', and finally `weakdecref(self)'
 * in order to finalize the destruction of `self'
 * Note that the process of clearing self-pointers, as well as the subsequent
 * destruction of `self' may be  performed asynchronously through use of  the
 * associated mman's lockop system.
 * NOTE: This function inherits a weak reference to `self->md_mman',
 *       as well as a weak reference to `self'! */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL module_clear_mnode_pointers_and_destroy)(WEAK REF struct module *__restrict self);


/* Wrappers for module operators. */
#ifdef __INTELLISENSE__
BLOCKING WUNUSED NONNULL((1)) REF struct module_section *(module_locksection)(struct module *__restrict self, USER CHECKED char const *section_name);
BLOCKING WUNUSED NONNULL((1)) REF struct module_section *(module_locksection_index)(struct module *__restrict self, unsigned int section_index);
BLOCKING WUNUSED NONNULL((1, 3)) __BOOL (module_sectinfo)(struct module *__restrict self, uintptr_t module_relative_addr, struct module_sectinfo *__restrict info);
/* Return the module's text/data base address, as used during unwinding. */
WUNUSED NONNULL((1)) void const *NOTHROW(module_get_tbase)(struct module *__restrict self);
WUNUSED NONNULL((1)) void const *NOTHROW(module_get_dbase)(struct module *__restrict self);
#else /* __INTELLISENSE__ */
#define module_locksection(self, section_name)            (*(self)->md_ops->mo_locksection)(self, section_name)
#define module_locksection_index(self, section_index)     (*(self)->md_ops->mo_locksection_index)(self, section_index)
#define module_sectinfo(self, module_relative_addr, info) (*(self)->md_ops->mo_sectinfo)(self, module_relative_addr, info)
#define module_get_tbase(self)                            (*(self)->md_ops->mo_get_tbase)(self)
#define module_get_dbase(self)                            (*(self)->md_ops->mo_get_dbase)(self)
#endif /* !__INTELLISENSE__ */

/* Same as `module_locksection()', but preserve/discard errors and return `NULL' instead. */
FUNDEF WUNUSED NONNULL((1, 2)) REF struct module_section *
NOTHROW(FCALL module_locksection_nx)(struct module *__restrict self, char const *section_name);
FUNDEF WUNUSED NONNULL((1)) REF struct module_section *
NOTHROW(FCALL module_locksection_index_nx)(struct module *__restrict self, unsigned int section_index);


/* Return the size of a pointer for the given module. */
#ifdef _MODULE_HAVE_SIZEOF_POINTER
#define module_sizeof_pointer(self) ((self)->md_sizeof_pointer)
#else /* _MODULE_HAVE_SIZEOF_POINTER */
#define module_sizeof_pointer(self) sizeof(void *)
#endif /* !_MODULE_HAVE_SIZEOF_POINTER */

/* Check if a given module must be executed in compatibility mode. */
#ifndef module_iscompat
#ifdef _MODULE_HAVE_SIZEOF_POINTER
#define module_iscompat(self) (module_sizeof_pointer(self) != sizeof(void *))
#else /* _MODULE_HAVE_SIZEOF_POINTER */
#define module_iscompat(self) 0
#endif /* !_MODULE_HAVE_SIZEOF_POINTER */
#endif /* !module_iscompat */

/* Check if a given module is actually a `struct driver'
 * Note  that when this is not the case, you are allowed
 * to assume  that the  module represents  some sort  of
 * user-space executable object. */
#define module_ops_isdriver(self) ((self)->mo_free == &_driver_free_callback)
#define module_isdriver(self)     ((self)->md_ops->mo_free == &_driver_free_callback)
#define module_asdriver(self)     ((struct driver *)(self))
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL _driver_free_callback)(struct module *__restrict self) ASMNAME("driver_free");


/* Check if the given module has a path and/or name. */
#define module_haspath(self) \
	((self)->md_fsname != __NULLPTR && ((self)->md_fspath != __NULLPTR || (self)->md_fsname->fd_name[0] == '/'))
#define module_hasname(self)         ((self)->md_fsname != __NULLPTR || module_isdriver(self))
#define module_haspath_or_name(self) ((self)->md_fsname != __NULLPTR || module_isdriver(self))

/* Return the name of the given module (or `NULL' if `!module_hasname(self)')
 * The returned pointer  is the  same as is  printed by  `module_printname()' */
FUNDEF ATTR_PURE WUNUSED NONNULL((1)) char const *
NOTHROW(FCALL module_getname)(struct module *__restrict self);

/* Print  the absolute filesystem path or name (filesystem
 * path excluding the leading  path) of the given  module.
 * If the module doesn't have a path/name (s.a. the macros
 * above), then nothing will be printed. */
FUNDEF BLOCKING_IF(BLOCKING(printer)) NONNULL((1, 2)) ssize_t KCALL
module_printpath(struct module *__restrict self, __pformatprinter printer, void *arg);
FUNDEF BLOCKING_IF(BLOCKING(printer)) NONNULL((1, 2)) ssize_t KCALL
module_printname(struct module *__restrict self, __pformatprinter printer, void *arg);

/* Try to print the module's path, and if that fails, print its name. */
FUNDEF BLOCKING_IF(BLOCKING(printer)) NONNULL((1, 2)) ssize_t KCALL
module_printpath_or_name(struct module *__restrict self, __pformatprinter printer, void *arg);


/* Return a reference to the module which can be found at the given address.
 * For this purpose, that address may  either be a kernel-space address,  in
 * which  case a pointer to the relevant driver  is returned, or it may be a
 * user-space address, in  which case  memory mappings of  that address  are
 * inspected in order to check if a module has been loaded to that location.
 * If no module exists at `addr', return `NULL'. */
FUNDEF BLOCKING WUNUSED REF struct module *FCALL
module_fromaddr(USER CHECKED void const *addr);

/* Search for, and return a reference to the lowest available module, such
 * that  `return->md_loadstart >= addr'. If no  such module exists, simply
 * return `NULL' instead. */
FUNDEF WUNUSED REF struct module *FCALL
module_aboveaddr(USER CHECKED void const *addr);

/* Return  a  reference  to  the  first  module  different  from  `prev',  such  that
 * `return->md_loadstart > prev->md_loadstart'.  When   `prev == NULL',  return   the
 * first module, which is the same as returned by `module_aboveaddr((void const *)0)' */
FUNDEF WUNUSED REF struct module *FCALL
module_next(struct module *prev);
#define module_first() module_aboveaddr((void const *)0)


/* Same as  the functions  above, but  preserve/restore the  old
 * exception if one ends up being thrown by the above functions,
 * and simply return `NULL', rather than RETHROW()-ing it. */
FUNDEF BLOCKING WUNUSED REF struct module *NOTHROW(FCALL module_fromaddr_nx)(USER CHECKED void const *addr);
FUNDEF BLOCKING WUNUSED REF struct module *NOTHROW(FCALL module_aboveaddr_nx)(USER CHECKED void const *addr);
FUNDEF BLOCKING WUNUSED REF struct module *NOTHROW(FCALL module_next_nx)(struct module *prev);
#define module_first_nx() module_aboveaddr_nx((void const *)0)

/* Same as the functions above,  but rather than operating  the
 * usual THIS_MMAN/mman_kernel hybrid-combo, based on the given
 * `addr', operate exclusively on the given mman `self'
 * @param: self: The mman who's modules should be enumerated. */
FUNDEF BLOCKING WUNUSED NONNULL((1)) REF struct module *FCALL mman_module_fromaddr(struct mman *__restrict self, USER CHECKED void const *addr);
FUNDEF BLOCKING WUNUSED NONNULL((1)) REF struct module *FCALL mman_module_aboveaddr(struct mman *__restrict self, USER CHECKED void const *addr);
FUNDEF BLOCKING WUNUSED NONNULL((1)) REF struct module *FCALL mman_module_next(struct mman *__restrict self, struct module *prev);
FUNDEF BLOCKING WUNUSED NONNULL((1)) REF struct module *NOTHROW(FCALL mman_module_fromaddr_nx)(struct mman *__restrict self, USER CHECKED void const *addr);
FUNDEF BLOCKING WUNUSED NONNULL((1)) REF struct module *NOTHROW(FCALL mman_module_aboveaddr_nx)(struct mman *__restrict self, USER CHECKED void const *addr);
FUNDEF BLOCKING WUNUSED NONNULL((1)) REF struct module *NOTHROW(FCALL mman_module_next_nx)(struct mman *__restrict self, struct module *prev);
#define mman_module_first(self)    mman_module_aboveaddr(self, (void const *)0)
#define mman_module_first_nx(self) mman_module_aboveaddr_nx(self, (void const *)0)


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MODULE_H */
