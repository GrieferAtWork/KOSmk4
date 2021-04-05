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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MODULE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MODULE_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <hybrid/__assert.h>

#include <bits/crt/format-printer.h>
#include <compat/config.h>

#ifdef __WANT_MODULE__md_mmlop
#include <sched/lockop.h>
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
struct directory_entry;
struct mman;

struct module_section_ops {
	/* [1..1] Destroy the given module section. */
	NOBLOCK NONNULL((1)) void
	/*NOTHROW*/ (FCALL *ms_destroy)(struct module_section *__restrict self);

	/* [1..1] Return the name of this section.
	 * If the name  can't be determined,  then return  `NULL'
	 * instead. Before calling this function, the caller must
	 * ensure that `!wasdestroyed(self->ms_module)') */
	/*ATTR_PURE*/ WUNUSED NONNULL((1)) char const *
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
	WUNUSED NONNULL((1)) USER CHECKED void *
	(FCALL *ms_getaddr)(struct module_section *__restrict self);

	/* [1..1] Similar  to `ms_getaddr' (and  identical in case of
	 * kernel-space driver modules). However, a difference exists
	 * for user-space modules, in that user-space module sections
	 * that have the `SHF_ALLOC' flag  set will still be  aliased
	 * by  a  lazily allocated  kernel-space memory  mapping, the
	 * address of which is then  returned. As such, the  returned
	 * buffer  can be dereferenced  irregardless of the currently
	 * active mman, since it will be apart of kernel-space. */
	WUNUSED NONNULL((1)) KERNEL CHECKED void *
	(FCALL *ms_getaddr_alias)(struct module_section *__restrict self);

	/* [1..1] Similar to `ms_getaddr_alias()', but if the section
	 * contains compressed data, inflate  that data, map it  into
	 * the  kernel, and return a pointer to that mapping, as well
	 * as the size (in bytes) of the decompressed data blob. */
	WUNUSED NONNULL((1, 2)) KERNEL CHECKED void *
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
	unsigned int                     ms_type;    /* [const] Section type (s.a. `ElfNN_Shdr::sh_type'; one of `SHT_*') */
	unsigned int                     ms_flags;   /* [const] Section flags (s.a. `ElfNN_Shdr::sh_flags'; set of `SHF_*') */
	unsigned int                     ms_link;    /* [const] Section link (s.a. `ElfNN_Shdr::sh_link') */
	unsigned int                     ms_info;    /* [const] Section info (s.a. `ElfNN_Shdr::sh_info') */
};

#define module_section_destroy(self) (*(self)->ms_ops->ms_destroy)(self)
DEFINE_REFCOUNT_FUNCTIONS(struct module_section, ms_refcnt, module_section_destroy)

/* Wrappers for module section operators. */
#ifdef __INTELLISENSE__
WUNUSED NONNULL((1)) char const *(module_section_getname)(struct module_section *__restrict self);
WUNUSED NONNULL((1)) USER CHECKED void *(module_section_getaddr)(struct module_section *__restrict self);
WUNUSED NONNULL((1)) KERNEL CHECKED void *(module_section_getaddr_alias)(struct module_section *__restrict self);
WUNUSED NONNULL((1)) KERNEL CHECKED void *(module_section_getaddr_inflate)(struct module_section *__restrict self, size_t *__restrict psize);
#else /* __INTELLISENSE__ */
#define module_section_getname(self)                (*(self)->ms_ops->ms_getname)(self)
#define module_section_getaddr(self)                (*(self)->ms_ops->ms_getaddr)(self)
#define module_section_getaddr_alias(self)          (*(self)->ms_ops->ms_getaddr_alias)(self)
#define module_section_getaddr_inflate(self, psize) (*(self)->ms_ops->ms_getaddr_inflate)(self, psize)
#endif /* !__INTELLISENSE__ */



struct module_ops {
	/* [1..1] Module free callback */
	NOBLOCK NONNULL((1)) void
	/*NOTHROW*/ (FCALL *mo_free)(struct module *__restrict self);

	/* [1..1] Module destroy callback */
	NOBLOCK NONNULL((1)) void
	/*NOTHROW*/ (FCALL *mo_destroy)(struct module *__restrict self);

	/* [1..1] Callback invoked when `md_nodecount' drops to 0.
	 * NOTE: This callback must be invoked while holding a
	 *       lock to the mappings-tree of `self->md_mman'. */
	NOBLOCK NONNULL((1)) void
	/*NOTHROW*/ (FCALL *mo_nonodes)(struct module *__restrict self);

	/* [1..1] Return a reference for a module section, given its name.
	 * If   the  given  `section_name'  isn't  valid,  return  `NULL'. */
	WUNUSED NONNULL((1)) REF struct module_section *
	(FCALL *mo_locksection)(struct module *__restrict self,
	                        USER CHECKED char const *section_name);

	/* [1..1] Return a reference for a module section, given its index.
	 * If   the  given  `section_index'  isn't  valid,  return  `NULL'. */
	WUNUSED NONNULL((1)) REF struct module_section *
	(FCALL *mo_locksection_index)(struct module *__restrict self,
	                              unsigned int section_index);
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
	void                       *md_loadmin;    /* [const] Lowest address mapped by this module. */
	void                       *md_loadmax;    /* [const] Greatest address mapped by this module. */
	REF struct mfile           *md_file;       /* [1..1][const] The backing file of the executable. */
#ifdef __WANT_MODULE__md_mmlop
	union {
		struct {
			REF struct path            *md_fspath; /* [0..1][const] Optional mapping path */
			REF struct directory_entry *md_fsname; /* [0..1][const] Optional mapping name */
		};
		Toblockop(struct mman)     _md_mmlop;     /* MMan cleanup lock operation */
		Tobpostlockop(struct mman) _md_mmpostlop; /* MMan cleanup post lock operation */
	};
#else /* __WANT_MODULE__md_mmlop */
	REF struct path            *md_fspath;     /* [0..1][const] Optional mapping path */
	REF struct directory_entry *md_fsname;     /* [0..1][const] Optional mapping name */
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

/* Increment/decrement the `md_nodecount' counter of `self' */
#define module_inc_nodecount(self) \
	(void)(__hybrid_assert((self)->md_nodecount != 0), ++(self)->md_nodecount)
#define module_dec_nodecount(self)                     \
	(void)(__hybrid_assert((self)->md_nodecount != 0), \
	       (--(self)->md_nodecount || ((*(self)->md_ops->mo_nonodes)(self), 0)))

#define module_free(self)    (*(self)->md_ops->mo_free)(self)
#define module_destroy(self) (*(self)->md_ops->mo_destroy)(self)
DEFINE_REFCOUNT_FUNCTIONS(struct module, md_refcnt, module_destroy)
DEFINE_WEAKREFCOUNT_FUNCTIONS(struct module, md_weakrefcnt, module_free)

/* Clear all of the mman->mnode->module self-pointers associated with `self',
 * drop a weak reference from `self->md_mman', and finally `weakdecref(self)'
 * in order to finalize the destruction of `self'
 * Note that the process of clearing self-pointers, as well as the subsequent
 * destruction of `self' may be  performed asynchronously through use of  the
 * associated mman's lockop system.
 * NOTE: This function inherits a weak reference to `self->md_mman',
 *       as well as a weak reference to `self'! */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL module_clear_mnode_pointers_and_destroy)(struct module *__restrict self);


/* Wrappers for module operators. */
#ifdef __INTELLISENSE__
WUNUSED NONNULL((1)) REF struct module_section *(module_locksection)(struct module *__restrict self, USER CHECKED char const *section_name);
WUNUSED NONNULL((1)) REF struct module_section *(module_locksection_index)(struct module *__restrict self, unsigned int section_index);
#else /* __INTELLISENSE__ */
#define module_locksection(self, section_name)        (*(self)->md_ops->mo_locksection)(self, section_name)
#define module_locksection_index(self, section_index) (*(self)->md_ops->mo_locksection_index)(self, section_index)
#endif /* !__INTELLISENSE__ */

/* Return the size of a pointer for the given module. */
#ifdef _MODULE_HAVE_SIZEOF_POINTER
#define module_sizeof_pointer(self) ((self)->md_sizeof_pointer)
#else /* _MODULE_HAVE_SIZEOF_POINTER */
#define module_sizeof_pointer(self) sizeof(void *)
#endif /* !_MODULE_HAVE_SIZEOF_POINTER */


/* Check if the given module has a path and/or name. */
#define module_haspath(self) \
	((self)->md_fsname != __NULLPTR && ((self)->md_fspath != __NULLPTR || (self)->md_fsname->de_name[0] == '/'))
#define module_hasname(self) \
	((self)->md_fsname != __NULLPTR)

/* Print  the absolute filesystem path or name (filesystem
 * path excluding the leading  path) of the given  module.
 * If the module doesn't have a path/name (s.a. the macros
 * above), then nothing will be printed. */
FUNDEF NONNULL((1, 2)) ssize_t KCALL
module_printpath(struct module *__restrict self, __pformatprinter printer, void *arg);
FUNDEF NONNULL((1, 2)) ssize_t KCALL
module_printname(struct module *__restrict self, __pformatprinter printer, void *arg);


/* Return a reference to the module which can be found at the given address.
 * For this purpose, that address may  either be a kernel-space address,  in
 * which  case a pointer to the relevant driver  is returned, or it may be a
 * user-space address, in  which case  memory mappings of  that address  are
 * inspected in order to check if a module has been loaded to that location.
 * If no module exists at `addr', return `NULL'. */
FUNDEF WUNUSED REF struct module *FCALL
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


/* Same as  the functions  above, but  preserve/restore the  old
 * exception if one ends up being thrown by the above functions,
 * and simply return `NULL', rather than RETHROW()-ing it. */
FUNDEF WUNUSED REF struct module *NOTHROW(FCALL module_fromaddr_nx)(USER CHECKED void const *addr);
FUNDEF WUNUSED REF struct module *NOTHROW(FCALL module_aboveaddr_nx)(USER CHECKED void const *addr);
FUNDEF WUNUSED REF struct module *NOTHROW(FCALL module_next_nx)(struct module *prev);

/* Clear the module cache of the given mman.
 *
 * Lazily loaded user-space modules end up being placed in this cache when
 * first loaded, as  the mnode->module link  doesn't actually represent  a
 * reference (which is intentional), meaning that a cache of recently used
 * module objects is needed in order  to keep module objects alive  beyond
 * the single initial reference returned  by the module lookup  functions.
 *
 * The mman module cache never has to be cleared, but may be cleared in
 * order to free up system memory during a shortage. */
FUNDEF NOBLOCK NONNULL((1)) size_t
NOTHROW(FCALL mman_clear_module_cache)(struct mman *__restrict self);


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MODULE_H */
