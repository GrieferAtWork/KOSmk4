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
#ifndef GUARD_KERNEL_SRC_MEMORY_MODULE_C
#define GUARD_KERNEL_SRC_MEMORY_MODULE_C 1
#define __WANT_MODULE__md_mmlop
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/rt.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/path.h>
#include <kernel/mman.h>
#include <kernel/mman/driver.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/module.h>
#include <kernel/paging.h>
#include <kernel/panic.h>

#include <compat/config.h>
#include <kos/anno.h>
#include <kos/except.h>

#include <assert.h>
#include <format-printer.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <sched/task.h>
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

/**/
#include "module-userelf.h"

/* Support for `unwind_for_debug(3)' */
#ifdef CONFIG_HAVE_KERNEL_USERELF_MODULES
#include <libdebuginfo/debug_frame.h>
#include <libunwind/errno.h>
#include <libunwind/unwind.h>

#ifdef __ARCH_HAVE_COMPAT
#include <libunwind/register.h>
#endif /* __ARCH_HAVE_COMPAT */
#endif /* CONFIG_HAVE_KERNEL_USERELF_MODULES */

DECL_BEGIN

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#define CURRENT_MMAN (unlikely(dbg_active) ? dbg_current->t_mman : THIS_MMAN)
#else /* CONFIG_HAVE_KERNEL_DEBUGGER */
#define CURRENT_MMAN THIS_MMAN
#endif /* !CONFIG_HAVE_KERNEL_DEBUGGER */

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/* Same as `module_locksection()', but preserve/discard errors and return `NULL' instead. */
PUBLIC WUNUSED NONNULL((1, 2)) REF struct module_section *
NOTHROW(FCALL module_locksection_nx)(struct module *__restrict self,
                                     char const *section_name) {
	REF struct module_section *result;
	NESTED_TRY {
		result = module_locksection(self, section_name);
	} EXCEPT {
		result = NULL;
	}
	return result;
}

PUBLIC WUNUSED NONNULL((1)) REF struct module_section *
NOTHROW(FCALL module_locksection_index_nx)(struct module *__restrict self,
                                           unsigned int section_index) {
	REF struct module_section *result;
	NESTED_TRY {
		result = module_locksection_index(self, section_index);
	} EXCEPT {
		result = NULL;
	}
	return result;
}


/* Print  the absolute filesystem path or name (filesystem
 * path excluding the leading  path) of the given  module.
 * If the module doesn't have a path/name (s.a. the macros
 * above), then nothing will be printed. */
PUBLIC NONNULL((1, 2)) ssize_t KCALL
module_printpath(struct module *__restrict self,
                 pformatprinter printer, void *arg) {
	ssize_t result = 0;
	if unlikely(self->md_fsname == NULL)
		goto done;
	if (self->md_fspath) {
		result = path_printent(self->md_fspath,
		                       self->md_fsname->fd_name,
		                       self->md_fsname->fd_namelen,
		                       printer, arg);
	} else if (self->md_fsname->fd_name[0] == '/') {
		result = (*printer)(arg,
		                    self->md_fsname->fd_name,
		                    self->md_fsname->fd_namelen);
	}
done:
	return result;
}

PUBLIC NONNULL((1, 2)) ssize_t KCALL
module_printname(struct module *__restrict self,
                 pformatprinter printer, void *arg) {
	ssize_t result = 0;
	char const *name;
	u16 namelen;
	if unlikely(self->md_fsname == NULL) {
		if (module_isdriver(self)) {
			name = module_asdriver(self)->d_name;
			return (*printer)(arg, name, strlen(name));
		}
		goto done;
	}
	name    = self->md_fsname->fd_name;
	namelen = self->md_fsname->fd_namelen;
	if (name[0] == '/') {
		char const *tail;
		tail    = (char const *)rawmemrchr(name + namelen, '/') + 1;
		namelen = (size_t)((name + namelen) - tail);
		name    = tail;
	}
	result = (*printer)(arg, name, namelen);
done:
	return result;
}

/* Return the name of the given module (or `NULL' if `!module_hasname(self)')
 * The returned pointer  is the  same as is  printed by  `module_printname()' */
PUBLIC ATTR_PURE WUNUSED NONNULL((1)) char const *
NOTHROW(FCALL module_getname)(struct module *__restrict self) {
	char const *result;
	if unlikely(self->md_fsname == NULL) {
		if (module_isdriver(self))
			return module_asdriver(self)->d_name;
		return NULL;
	}
	result = self->md_fsname->fd_name;
	if (result[0] == '/')
		result = (char const *)rawmemrchr(result + self->md_fsname->fd_namelen, '/') + 1;
	return result;
}

/* Try to print the module's path, and if that fails, print its name. */
PUBLIC NONNULL((1, 2)) ssize_t KCALL
module_printpath_or_name(struct module *__restrict self,
                         pformatprinter printer, void *arg) {
	ssize_t result = 0;
	if (self->md_fspath && self->md_fsname) {
		result = path_printent(self->md_fspath,
		                       self->md_fsname->fd_name,
		                       self->md_fsname->fd_namelen,
		                       printer, arg);
	} else if (self->md_fsname) {
		result = (*printer)(arg,
		                    self->md_fsname->fd_name,
		                    self->md_fsname->fd_namelen);
	} else if (module_isdriver(self)) {
		char const *name;
		name = module_asdriver(self)->d_name;
		return (*printer)(arg, name, strlen(name));
	}
	return result;
}



/* Same as the functions above, but preserve the current exception, and return `NULL' on error. */
PUBLIC BLOCKING WUNUSED NONNULL((1)) char const *
NOTHROW(FCALL module_section_getname_nx)(struct module_section *__restrict self) {
	char const *result;
	NESTED_TRY {
		result = module_section_getname(self);
	} EXCEPT {
		result = NULL;
	}
	return result;
}

PUBLIC BLOCKING WUNUSED NONNULL((1)) NCX byte_t *
NOTHROW(FCALL module_section_getaddr_nx)(struct module_section *__restrict self) {
	NCX byte_t *result;
	NESTED_TRY {
		result = module_section_getaddr(self);
	} EXCEPT {
		result = NULL;
	}
	return result;
}

PUBLIC BLOCKING WUNUSED NONNULL((1)) KERNEL NCX byte_t *
NOTHROW(FCALL module_section_getaddr_alias_nx)(struct module_section *__restrict self) {
	KERNEL NCX byte_t *result;
	NESTED_TRY {
		result = module_section_getaddr_alias(self);
	} EXCEPT {
		result = NULL;
	}
	return result;
}

PUBLIC BLOCKING WUNUSED NONNULL((1, 2)) KERNEL NCX byte_t *
NOTHROW(FCALL module_section_getaddr_inflate_nx)(struct module_section *__restrict self,
                                                 size_t *__restrict psize) {
	KERNEL NCX byte_t *result;
	NESTED_TRY {
		result = module_section_getaddr_inflate(self, psize);
	} EXCEPT {
		*psize = 0;
		result = NULL;
	}
	return result;
}








/* Whilst holding a lock to `mm', clear all  mnode->module
 * pointers that point to `self' by setting them to `NULL' */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL module_remove_from_mman)(struct module *__restrict self,
                                       struct mman *__restrict mm) {
	struct mnode_tree_minmax mima;
	struct mnode *node;
#ifndef NDEBUG
	size_t nodecount = 0;
#endif /* !NDEBUG */
#if defined(NDEBUG) && !defined(__OPTIMIZE_SIZE__)
	/* Fastpass  optimization: If there aren't any nodes
	 * left, then we don't actually have to do anything! */
	if (self->md_nodecount == 0)
		return;
#endif /* NDEBUG && !__OPTIMIZE_SIZE__ */

	mnode_tree_minmaxlocate(mm->mm_mappings,
	                        self->md_loadmin,
	                        self->md_loadmax,
	                        &mima);
	if unlikely(!mima.mm_min) {
#ifndef NDEBUG
		assert(self->md_nodecount == 0);
#endif /* !NDEBUG */
		return;
	}
	for (node = mima.mm_min;;) {
		/* Clear module self-pointers. */
		if (node->mn_module == self) {
#ifndef NDEBUG
			++nodecount;
#endif /* !NDEBUG */
			node->mn_module = NULL;
		}

		if (node == mima.mm_max)
			break;
		node = mnode_tree_nextnode(node);
		assert(node);
	}
#ifndef NDEBUG
	assertf(nodecount == self->md_nodecount,
	        "Wrong # of mnodes referencing this module:\n"
	        "Expected: %" PRIuSIZ "\n"
	        "Actually: %" PRIuSIZ "\n",
	        self->md_nodecount, nodecount);
	DBG_memset(&self->md_nodecount, 0xcc, sizeof(self->md_nodecount));
#endif /* !NDEBUG */
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL module_mman_cleanup_postlop)(Tobpostlockop(mman) *__restrict self,
                                           REF struct mman *__restrict mm) {
	WEAK REF struct module *me;
	me = container_of(self, struct module, _md_mmpostlop);

	/* Drop inherited references */
	assert(me->md_mman == mm);
	DBG_memset(&me->md_mman, 0xcc, sizeof(me->md_mman));
	decref_nokill(mm); /* nokill, because in order to get here, whoever ended
	                    * up reaping lock operations must still be holding  a
	                    * reference  to the mman, meaning that this reference
	                    * can't possibly be the last one of them all! */
	weakdecref_likely(me);
}

PRIVATE NOBLOCK NONNULL((1)) Tobpostlockop(mman) *
NOTHROW(FCALL module_mman_cleanup_lop)(Toblockop(mman) *__restrict self,
                                       REF struct mman *__restrict mm) {
	WEAK REF struct module *me;

	/* Clear all mnode->module self-pointers. */
	me = container_of(self, struct module, _md_mmlop);
	assert(me->md_mman == mm);
	module_remove_from_mman(me, mm);

	/* Setup a post-lock operation to drop all of our inherited references. */
	me->_md_mmpostlop.oplo_func = &module_mman_cleanup_postlop;
	return &me->_md_mmpostlop;
}


/* Clear all of the mman->mnode->module self-pointers associated with `self',
 * drop a weak reference from `self->md_mman', and finally `weakdecref(self)'
 * in order to finalize the destruction of `self'
 * Note that the process of clearing self-pointers, as well as the subsequent
 * destruction of `self' may be  performed asynchronously through use of  the
 * associated mman's lockop system.
 * NOTE: This function inherits a weak reference to `self->md_mman',
 *       as well as a weak reference to `self'! */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL module_clear_mnode_pointers_and_destroy)(WEAK REF struct module *__restrict self) {
	REF struct mman *mm;
	mm = self->md_mman;

	/* Try to acquire a proper reference to the associated mman.
	 * Note that if the mman has already been destroyed, then we
	 * can  assume that the  mman has already  died, and that we
	 * don't have to  manually clear self-pointers  from all  of
	 * its mem-nodes! */
	if (!tryincref(mm)) {
		DBG_memset(&self->md_mman, 0xcc, sizeof(self->md_mman));
		weakdecref_likely(self);
		weakdecref_unlikely(mm);
		return;
	}

	/* Remove module-self-pointers from `self' */
	if (mman_lock_tryacquire(mm)) {
		module_remove_from_mman(self, mm);
		_mman_lock_release(mm);
		DBG_memset(&self->md_mman, 0xcc, sizeof(self->md_mman));
		weakdecref_likely(self);
		mman_lockops_reap(mm);
	} else {
		/* Enqueue a lockop to clear all of our mnode->module self-pointers.
		 * NOTE: As  far as semantics  go, we let `module_mman_cleanup_lop()'
		 *       inherit the reference to `mm', as well as the weak reference
		 *       to `self'! */
		incref(mm); /* Need a second reference to drop below so we can safely reap! */
		self->_md_mmlop.olo_func = &module_mman_cleanup_lop;
		SLIST_ATOMIC_INSERT(&FORMMAN(mm, thismman_lockops),
		                    &self->_md_mmlop, olo_link);
		_mman_lockops_reap(mm);
	}
	decref_unlikely(mm);
	weakdecref_unlikely(mm);
}




/* Return a reference to the module which can be found at the given address.
 * For this purpose, that address may  either be a kernel-space address,  in
 * which  case a pointer to the relevant driver  is returned, or it may be a
 * user-space address, in  which case  memory mappings of  that address  are
 * inspected in order to check if a module has been loaded to that location.
 * If no module exists at `addr', return `NULL'. */
PUBLIC BLOCKING WUNUSED REF struct module *FCALL
module_fromaddr(NCX void const *addr) {
#ifdef CONFIG_HAVE_KERNEL_USERELF_MODULES
	if (ADDR_ISUSER(addr))
		return uem_fromaddr(CURRENT_MMAN, addr);
#else /* CONFIG_HAVE_KERNEL_USERELF_MODULES */
#define _MODULE_FROMADDR_IS_NOTHROW
#endif /* !CONFIG_HAVE_KERNEL_USERELF_MODULES */
	return driver_fromaddr(addr);
}

/* Search for, and return a reference to the lowest available module, such
 * that  `return->md_loadstart >= addr'. If no  such module exists, simply
 * return `NULL' instead. */
PUBLIC BLOCKING WUNUSED REF struct module *FCALL
module_aboveaddr(NCX void const *addr) {
#ifdef CONFIG_HAVE_KERNEL_USERELF_MODULES
#ifdef KERNELSPACE_HIGHMEM
	if (ADDR_ISUSER(addr)) {
		REF struct module *result;
		result = uem_aboveaddr(CURRENT_MMAN, addr);
		if (result)
			return result;

		/* Fallthru to find the first kernel-space module... */
		addr = (NCX void *)KERNELSPACE_BASE;
	}
	return driver_aboveaddr(addr);
#else /* KERNELSPACE_HIGHMEM */
	if (ADDR_ISKERN(addr)) {
		REF struct module *result;
		result = driver_aboveaddr(addr);
		if (result)
			return result;
	}
	return uem_aboveaddr(CURRENT_MMAN, addr);
#endif /* !KERNELSPACE_HIGHMEM */
#else /* CONFIG_HAVE_KERNEL_USERELF_MODULES */
#define _MODULE_ABOVEADDR_IS_NOTHROW
	return driver_aboveaddr(addr);
#endif /* !CONFIG_HAVE_KERNEL_USERELF_MODULES */
}

/* Return  a  reference  to  the  first  module  different  from  `prev',  such  that
 * `return->md_loadstart > prev->md_loadstart'.  When   `prev == NULL',  return   the
 * first module, which is the same as returned by `module_aboveaddr((void const *)0)' */
PUBLIC BLOCKING WUNUSED REF struct module *FCALL
module_next(struct module *prev) {
#ifdef CONFIG_HAVE_KERNEL_USERELF_MODULES
	if (!prev)
		return module_aboveaddr((void const *)0);
	if (prev->md_ops == &uem_ops) {
		/* Find the next UserELF module. */
		REF struct userelf_module *result;
		result = uem_next(prev->md_mman, prev);
#ifdef KERNELSPACE_HIGHMEM
		if (result)
			return result;

		/* Find the first kernel-space module. */
		return module_aboveaddr((NCX void *)KERNELSPACE_BASE);
#else /* KERNELSPACE_HIGHMEM */
		/* User-space exists in high memory, so the
		 * last  module has to be a UserELF module. */
		return NULL;
#endif /* !KERNELSPACE_HIGHMEM */
	}
#ifdef KERNELSPACE_HIGHMEM
	return driver_next(prev);
#else /* KERNELSPACE_HIGHMEM */
	{
		REF struct module *next;
		next = driver_next(prev);
		if (next)
			return next;
	}
	return uem_aboveaddr(CURRENT_MMAN, (void const *)USERSPACE_START);
#endif /* !KERNELSPACE_HIGHMEM */
#else /* CONFIG_HAVE_KERNEL_USERELF_MODULES */
#define _MODULE_NEXT_IS_NOTHROW
	return driver_next((struct driver *)prev);
#endif /* !CONFIG_HAVE_KERNEL_USERELF_MODULES */
}




/* Same as  the functions  above, but  preserve/restore the  old
 * exception if one ends up being thrown by the above functions,
 * and simply return `NULL', rather than RETHROW()-ing it. */
#ifdef _MODULE_FROMADDR_IS_NOTHROW
DEFINE_PUBLIC_ALIAS(module_fromaddr_nx, module_fromaddr);
#else /* _MODULE_FROMADDR_IS_NOTHROW */
PUBLIC WUNUSED REF struct module *
NOTHROW(FCALL module_fromaddr_nx)(VIRT void const *addr) {
	REF struct module *result;
	NESTED_TRY {
		result = module_fromaddr(addr);
	} EXCEPT {
		result = NULL;
	}
	return result;
}
#endif /* !_MODULE_FROMADDR_IS_NOTHROW */

#ifdef _MODULE_ABOVEADDR_IS_NOTHROW
DEFINE_PUBLIC_ALIAS(module_aboveaddr_nx, module_aboveaddr);
#else /* _MODULE_ABOVEADDR_IS_NOTHROW */
PUBLIC WUNUSED REF struct module *
NOTHROW(FCALL module_aboveaddr_nx)(NCX void const *addr) {
	REF struct module *result;
	NESTED_TRY {
		result = module_aboveaddr(addr);
	} EXCEPT {
		result = NULL;
	}
	return result;
}
#endif /* !_MODULE_ABOVEADDR_IS_NOTHROW */

#ifdef _MODULE_NEXT_IS_NOTHROW
DEFINE_PUBLIC_ALIAS(module_next_nx, module_next);
#else /* _MODULE_NEXT_IS_NOTHROW */
PUBLIC WUNUSED REF struct module *
NOTHROW(FCALL module_next_nx)(struct module *prev) {
	REF struct module *result;
	NESTED_TRY {
		result = module_next(prev);
	} EXCEPT {
		result = NULL;
	}
	return result;
}
#endif /* !_MODULE_NEXT_IS_NOTHROW */


/* Same as the functions above,  but rather than operating  the
 * usual THIS_MMAN/mman_kernel hybrid-combo, based on the given
 * `addr', operate exclusively on the given mman `self'
 * @param: self: The mman who's modules should be enumerated. */
#ifdef CONFIG_HAVE_KERNEL_USERELF_MODULES
PUBLIC BLOCKING WUNUSED NONNULL((1)) REF struct module *FCALL
mman_module_fromaddr(struct mman *__restrict self,
                     NCX void const *addr) {
	if (self == &mman_kernel)
		return driver_fromaddr(addr);
#ifdef CONFIG_HAVE_KERNEL_USERELF_MODULES
	return uem_fromaddr(self, addr);
#else /* CONFIG_HAVE_KERNEL_USERELF_MODULES */
	return NULL;
#endif /* !CONFIG_HAVE_KERNEL_USERELF_MODULES */
}

PUBLIC BLOCKING WUNUSED NONNULL((1)) REF struct module *FCALL
mman_module_aboveaddr(struct mman *__restrict self,
                      NCX void const *addr) {
	if (self == &mman_kernel)
		return driver_aboveaddr(addr);
#ifdef CONFIG_HAVE_KERNEL_USERELF_MODULES
	return uem_aboveaddr(self, addr);
#else /* CONFIG_HAVE_KERNEL_USERELF_MODULES */
	return NULL;
#endif /* !CONFIG_HAVE_KERNEL_USERELF_MODULES */
}

PUBLIC BLOCKING WUNUSED NONNULL((1)) REF struct module *FCALL
mman_module_next(struct mman *__restrict self, struct module *prev) {
	if (self == &mman_kernel)
		return driver_next(prev);
#ifdef CONFIG_HAVE_KERNEL_USERELF_MODULES
	return uem_next(self, prev);
#else /* CONFIG_HAVE_KERNEL_USERELF_MODULES */
	return NULL;
#endif /* !CONFIG_HAVE_KERNEL_USERELF_MODULES */
}

PUBLIC WUNUSED NONNULL((1)) REF struct module *
NOTHROW(FCALL mman_module_fromaddr_nx)(struct mman *__restrict self,
                                       NCX void const *addr) {
	REF struct module *result;
	NESTED_TRY {
		result = mman_module_fromaddr(self, addr);
	} EXCEPT {
		result = NULL;
	}
	return result;
}

PUBLIC WUNUSED NONNULL((1)) REF struct module *
NOTHROW(FCALL mman_module_aboveaddr_nx)(struct mman *__restrict self,
                                        NCX void const *addr) {
	REF struct module *result;
	NESTED_TRY {
		result = mman_module_aboveaddr(self, addr);
	} EXCEPT {
		result = NULL;
	}
	return result;
}

PUBLIC WUNUSED NONNULL((1)) REF struct module *
NOTHROW(FCALL mman_module_next_nx)(struct mman *__restrict self,
                                   struct module *prev) {
	REF struct module *result;
	NESTED_TRY {
		result = mman_module_next(self, prev);
	} EXCEPT {
		result = NULL;
	}
	return result;
}

#else /* CONFIG_HAVE_KERNEL_USERELF_MODULES */
PUBLIC BLOCKING WUNUSED NONNULL((1)) REF struct module *FCALL
mman_module_fromaddr(struct mman *__restrict self,
                     NCX void const *addr) {
	if (self == &mman_kernel)
		return driver_fromaddr(addr);
	return NULL;
}
PUBLIC BLOCKING WUNUSED NONNULL((1)) REF struct module *FCALL
mman_module_aboveaddr(struct mman *__restrict self,
                      NCX void const *addr) {
	if (self == &mman_kernel)
		return driver_aboveaddr(addr);
	return NULL;
}

PUBLIC BLOCKING WUNUSED NONNULL((1)) REF struct module *FCALL
mman_module_next(struct mman *__restrict self, struct module *prev) {
	if (self == &mman_kernel)
		return driver_next(prev);
	return NULL;
}

DEFINE_PUBLIC_ALIAS(mman_module_fromaddr_nx, mman_module_fromaddr);
DEFINE_PUBLIC_ALIAS(mman_module_aboveaddr_nx, mman_module_aboveaddr);
DEFINE_PUBLIC_ALIAS(mman_module_next_nx, mman_module_next);
#endif /* !CONFIG_HAVE_KERNEL_USERELF_MODULES */


#ifdef CONFIG_HAVE_KERNEL_USERELF_MODULES
LOCAL NONNULL((1, 5, 7)) unwind_errno_t KCALL
unwind_userspace_with_section(struct module *__restrict mod, VIRT void const *absolute_pc,
                              NCX byte_t const *eh_frame_data, size_t eh_frame_size,
                              unwind_getreg_t reg_getter, void const *reg_getter_arg,
                              unwind_setreg_t reg_setter, void *reg_setter_arg,
                              bool is_debug_frame) {
	unwind_errno_t result;
	REF struct mman *oldmm;
	REF struct mman *newmm = mod->md_mman;
	unwind_fde_t fde;
	if (!tryincref(newmm))
		return UNWIND_NO_FRAME;

	/* Must switch VM to the one of `mod' in order to get user-space memory
	 * into the expected  state for  the unwind  handler to  do its  thing. */
	oldmm = task_xchmman_inherit(newmm);
	RAII_FINALLY { task_setmman_inherit(oldmm); };

	/* NOTE: We  use the  user-space's mapping  of the  .eh_frame section here,
	 *       since `.eh_frame' often uses  pointer encodings that are  relative
	 *       to the .eh_frame-section itself, meaning that in order to properly
	 *       decode the contained  information, its mapping  must be placed  at
	 *       the correct location.
	 * Another alternative to fixing this would be to add a load-offset argument
	 * to `dwarf_decode_pointer()', as well as recursively all of the  eh_frame-
	 * related functions that somehow make use  of it, where this argument  then
	 * describes the offset from the .eh_frame that was loaded, towards the  one
	 * that would actually exist for user-space.
	 * However the added complexity isn't worth it for this one special  case,
	 * and since we already have to switch VM to the user-space's one in order
	 * to restore registers that were spilled onto the stack, we might as well
	 * also  make use of  the actual `.eh_frame' section  (assuming that it is
	 * where it should be) */
	fde.f_tbase = module_get_tbase(mod);
	fde.f_dbase = module_get_dbase(mod);
	if (is_debug_frame) {
		uintptr_t module_relative_addr;
		module_relative_addr = (uintptr_t)absolute_pc - mod->md_loadaddr;
		result = unwind_fde_scan_df(eh_frame_data,
		                            eh_frame_data + eh_frame_size,
		                            module_relative_addr, &fde,
		                            module_sizeof_pointer(mod));
		if (result == UNWIND_SUCCESS) {
			/* Must adjust for load address. */
			fde.f_pcstart = (void *)((uintptr_t)fde.f_pcstart + mod->md_loadaddr);
			fde.f_pcend   = (void *)((uintptr_t)fde.f_pcend + mod->md_loadaddr);
			assert(fde.f_persofun == NULL);
			assert(fde.f_lsdaaddr == NULL);
		}
	} else {
		result = unwind_fde_scan(eh_frame_data,
		                         eh_frame_data + eh_frame_size,
		                         absolute_pc, &fde,
		                         module_sizeof_pointer(mod));
	}
	if (result == UNWIND_SUCCESS) {
		/* Found the FDE. - Now to execute it's program! */
		unwind_cfa_state_t cfa;
		result = unwind_fde_exec(&fde, &cfa, absolute_pc);
		if unlikely(result == UNWIND_SUCCESS) {
			/* And finally: Apply register modifications. */
			result = unwind_cfa_apply(&cfa, &fde, absolute_pc,
			                          reg_getter, reg_getter_arg,
			                          reg_setter, reg_setter_arg);
		}
	}
	return result;
}

PRIVATE ATTR_NOINLINE NONNULL((2, 4)) unwind_errno_t LIBUNWIND_CC
unwind_userspace(VIRT void const *absolute_pc,
                 unwind_getreg_t reg_getter, void const *reg_getter_arg,
                 unwind_setreg_t reg_setter, void *reg_setter_arg) {
	/* Unwind a user-space location. */
	unwind_errno_t result = UNWIND_NO_FRAME;
	REF struct module *mod;

	/* Lookup the module at the given address. */
	mod = module_fromaddr_nx(absolute_pc);
	if likely(mod) {
		unsigned int i;
#ifdef __ARCH_HAVE_COMPAT
		struct unwind_getreg_compat_data compat_getreg_data;
		struct unwind_setreg_compat_data compat_setreg_data;
#endif /* __ARCH_HAVE_COMPAT */
		FINALLY_DECREF_UNLIKELY(mod);

		/* Check if compatibility mode support is needed. */
#ifdef __ARCH_HAVE_COMPAT
		if (module_iscompat(mod)) {
			unwind_getreg_compat_data_init(&compat_getreg_data, reg_getter, reg_getter_arg);
			unwind_setreg_compat_data_init(&compat_setreg_data, reg_setter, reg_setter_arg);
			reg_getter     = &unwind_getreg_compat;
			reg_setter     = &unwind_setreg_compat;
			reg_getter_arg = &compat_getreg_data;
			reg_setter_arg = &compat_setreg_data;
		}
#endif /* __ARCH_HAVE_COMPAT */

		/* Search for the `.eh_frame' and `.debug_frame' sections. */
		for (i = 0; i < 2; ++i) {
			size_t size;
			NCX byte_t const *data;
			REF struct module_section *sect;
			static char const section_names[][16] = { ".eh_frame", ".debug_frame" };
			if ((sect = module_locksection(mod, section_names[i])) == NULL)
				continue;
			FINALLY_DECREF_UNLIKELY(sect);

			/* Load a mapping for the section. */
			if (i == 0) {
				/* Special case: the `.eh_frame' must be allocated in user-space,
				 *               and we also need to  parse it in its  user-space
				 *               location,  since  it may  contain  some pointer-
				 *               relative offsets which we'd otherwise  interpret
				 *               incorrectly. */
				if unlikely(!(sect->ms_flags & SHF_ALLOC))
					continue;
				data = module_section_getaddr_nx(sect);
				if unlikely(!data)
					continue;
				size = sect->ms_size;
			} else {
				data = module_section_getaddr_inflate_nx(sect, &size);
				if unlikely(size == 0)
					continue;
			}
			result = unwind_userspace_with_section(mod, absolute_pc, data, size,
			                                       reg_getter, reg_getter_arg,
			                                       reg_setter, reg_setter_arg,
			                                       i != 0);
			if (result != UNWIND_NO_FRAME)
				break;
		}
	}
	return result;
}


PUBLIC NONNULL((2, 4)) unwind_errno_t LIBDEBUGINFO_CC
unwind_for_debug(VIRT void const *absolute_pc,
                 unwind_getreg_t reg_getter, void const *reg_getter_arg,
                 unwind_setreg_t reg_setter, void *reg_setter_arg) {
	unwind_errno_t result;

	/* For non-userspace addresses, use the regular, old unwind() function! */
	if (!ADDR_ISUSER(absolute_pc)) {
		result = unwind(absolute_pc,
		                reg_getter, reg_getter_arg,
		                reg_setter, reg_setter_arg);
	} else if unlikely(kernel_poisoned()) {
		/* Refuse to touch user-space modules if poisoned */
		result = UNWIND_NO_FRAME;
	} else {
		result = unwind_userspace(absolute_pc,
		                          reg_getter, reg_getter_arg,
		                          reg_setter, reg_setter_arg);
	}
	return result;
}
#else /* CONFIG_HAVE_KERNEL_USERELF_MODULES */
PUBLIC NONNULL((2, 4)) unwind_errno_t LIBDEBUGINFO_CC
unwind_for_debug(VIRT void const *absolute_pc,
                 unwind_getreg_t reg_getter, void const *reg_getter_arg,
                 unwind_setreg_t reg_setter, void *reg_setter_arg) {
	/* Use the normal unwind(3) to implement unwind_for_debug(3) */
	return unwind(absolute_pc,
	              reg_getter, reg_getter_arg,
	              reg_setter, reg_setter_arg);
}
#endif /* !CONFIG_HAVE_KERNEL_USERELF_MODULES */

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MODULE_C */
