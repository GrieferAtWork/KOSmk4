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
#ifndef GUARD_KERNEL_SRC_MEMORY_MODULE_C
#define GUARD_KERNEL_SRC_MEMORY_MODULE_C 1
#define __WANT_MODULE__md_mmlop
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/mman.h>
#include <kernel/mman/driver.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/module.h>
#include <kernel/paging.h>

#include <assert.h>
#include <format-printer.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>

/**/
#include "module-userelf.h"

DECL_BEGIN

#ifndef NDEBUG
#define DBG_memset(dst, byte, num_bytes) memset(dst, byte, num_bytes)
#else /* !NDEBUG */
#define DBG_memset(dst, byte, num_bytes) (void)0
#endif /* NDEBUG */

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
		                       self->md_fsname->de_name,
		                       self->md_fsname->de_namelen,
		                       printer, arg);
	} else if (self->md_fsname->de_name[0] == '/') {
		result = (*printer)(arg,
		                    self->md_fsname->de_name,
		                    self->md_fsname->de_namelen);
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
#ifdef CONFIG_USE_NEW_DRIVER
	if (module_isdriver(self)) {
		name = ((struct driver *)self)->d_name;
		return (*printer)(arg, name, strlen(name));
	}
#endif /* CONFIG_USE_NEW_DRIVER */
	if unlikely(self->md_fsname == NULL)
		goto done;
	name    = self->md_fsname->de_name;
	namelen = self->md_fsname->de_namelen;
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

/* Try to print the module's path, and if that fails, print its name. */
PUBLIC NONNULL((1, 2)) ssize_t KCALL
module_printpath_or_name(struct module *__restrict self,
                         pformatprinter printer, void *arg) {
	ssize_t result = 0;
	if (self->md_fspath && self->md_fsname) {
		result = path_printent(self->md_fspath,
		                       self->md_fsname->de_name,
		                       self->md_fsname->de_namelen,
		                       printer, arg);
	}
#ifdef CONFIG_USE_NEW_DRIVER
	else if (module_isdriver(self) &&
	         (!self->md_fsname || self->md_fsname->de_name[0] != '/')) {
		char const *name;
		name = ((struct driver *)self)->d_name;
		return (*printer)(arg, name, strlen(name));
	}
#endif /* CONFIG_USE_NEW_DRIVER */
	else if (self->md_fsname) {
		result = (*printer)(arg,
		                    self->md_fsname->de_name,
		                    self->md_fsname->de_namelen);
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
NOTHROW(FCALL module_mman_cleanup_postlop)(Tobpostlockop(struct mman) *__restrict self,
                                           REF struct mman *__restrict mm) {
	WEAK REF struct module *me;
	me = container_of(self, struct module, _md_mmpostlop);
	/* Drop inherited references */
	assert(me->md_mman == mm);
	DBG_memset(&me->md_mman, 0xcc, sizeof(me->md_mman));
	decref_nokill(mm); /* nokill, because in order to get here, whoever ended
	                    * up reaping lock operations must still be holding a
	                    * reference to the mman, meaning that this reference
	                    * can't possibly be the last one of them all! */
	weakdecref_likely(me);
}

PRIVATE NOBLOCK NONNULL((1)) Tobpostlockop(struct mman) *
NOTHROW(FCALL module_mman_cleanup_lop)(Toblockop(struct mman) *__restrict self,
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
NOTHROW(FCALL module_clear_mnode_pointers_and_destroy)(struct module *__restrict self) {
	REF struct mman *mm;
	mm = self->md_mman;

	/* Try to acquire a proper reference to the associated mman.
	 * Note that if the mman had already been destroyed, then we
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
		mman_lock_release_f(mm);
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
PUBLIC WUNUSED REF struct module *FCALL
module_fromaddr(USER CHECKED void const *addr) {
#ifdef CONFIG_HAVE_USERELF_MODULES
	if (ADDR_ISUSER(addr))
		return uem_fromaddr(THIS_MMAN, addr);
#endif /* CONFIG_HAVE_USERELF_MODULES */

#ifdef CONFIG_USE_NEW_DRIVER
	return driver_fromaddr(addr);
#else /* CONFIG_USE_NEW_DRIVER */
	COMPILER_IMPURE();
	(void)addr;
	return NULL;
#endif /* !CONFIG_USE_NEW_DRIVER */
}

/* Search for, and return a reference to the lowest available module, such
 * that  `return->md_loadstart >= addr'. If no  such module exists, simply
 * return `NULL' instead. */
PUBLIC WUNUSED REF struct module *FCALL
module_aboveaddr(USER CHECKED void const *addr) {
#ifdef CONFIG_HAVE_USERELF_MODULES
#ifdef KERNELSPACE_HIGHMEM
	if (ADDR_ISUSER(addr)) {
		REF struct module *result;
		result = uem_aboveaddr(THIS_MMAN, addr);
		if (result)
			return result;
		/* Fallthru to find the first kernel-space module... */
		addr = (USER CHECKED void *)KERNELSPACE_BASE;
	}
#endif /* KERNELSPACE_HIGHMEM */
#endif /* CONFIG_HAVE_USERELF_MODULES */

#ifdef CONFIG_USE_NEW_DRIVER
	return driver_aboveaddr(addr);
#else /* CONFIG_USE_NEW_DRIVER */
	COMPILER_IMPURE();
	(void)addr;
	return NULL;
#endif /* !CONFIG_USE_NEW_DRIVER */
}

/* Return  a  reference  to  the  first  module  different  from  `prev',  such  that
 * `return->md_loadstart > prev->md_loadstart'.  When   `prev == NULL',  return   the
 * first module, which is the same as returned by `module_aboveaddr((void const *)0)' */
PUBLIC WUNUSED REF struct module *FCALL
module_next(struct module *prev) {
	/* Special case: lookup the lowest-address module currently visible. */
	if (!prev)
		return module_aboveaddr((void const *)0);
#ifdef CONFIG_HAVE_USERELF_MODULES
	if (prev->md_ops == &uem_ops) {
		/* Find the next UserELF module. */
		REF struct userelf_module *result;
		struct userelf_module *ue_prev;
		ue_prev = (struct userelf_module *)prev;
		result  = uem_next(ue_prev->md_mman, ue_prev);
#ifdef KERNELSPACE_HIGHMEM
		if (result)
			return result;
		/* Find the first kernel-space module. */
		return module_aboveaddr((USER CHECKED void *)KERNELSPACE_BASE);
#else /* KERNELSPACE_HIGHMEM */
		/* User-space exists in high memory, so the
		 * last  module has to be a UserELF module. */
		return NULL;
#endif /* !KERNELSPACE_HIGHMEM */
	}
#endif /* CONFIG_HAVE_USERELF_MODULES */

#ifdef CONFIG_USE_NEW_DRIVER
	return driver_next((struct driver *)prev);
#else /* CONFIG_USE_NEW_DRIVER */
	COMPILER_IMPURE();
	(void)prev;
	return NULL;
#endif /* !CONFIG_USE_NEW_DRIVER */
}




/* Same as  the functions  above, but  preserve/restore the  old
 * exception if one ends up being thrown by the above functions,
 * and simply return `NULL', rather than RETHROW()-ing it. */
PUBLIC WUNUSED REF struct module *
NOTHROW(FCALL module_fromaddr_nx)(USER CHECKED void const *addr) {
	REF struct module *result;
	NESTED_TRY {
		result = module_fromaddr(addr);
	} EXCEPT {
		result = NULL;
	}
	return result;
}

PUBLIC WUNUSED REF struct module *
NOTHROW(FCALL module_aboveaddr_nx)(USER CHECKED void const *addr) {
	REF struct module *result;
	NESTED_TRY {
		result = module_aboveaddr(addr);
	} EXCEPT {
		result = NULL;
	}
	return result;
}

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


#ifndef CONFIG_HAVE_USERELF_MODULES
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
PUBLIC NOBLOCK NONNULL((1)) size_t
NOTHROW(FCALL mman_clear_module_cache)(struct mman *__restrict self) {
	COMPILER_IMPURE();
	(void)self;
	return 0;
}
#endif /* !CONFIG_HAVE_USERELF_MODULES */




DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MODULE_C */
