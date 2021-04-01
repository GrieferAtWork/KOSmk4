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
#ifndef GUARD_KERNEL_SRC_MEMORY_MODULE_USERELF_C
#define GUARD_KERNEL_SRC_MEMORY_MODULE_USERELF_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

/**/
#include "module-userelf.h"

#ifdef CONFIG_HAVE_USERELF_MODULES

#include <debugger/config.h>
#include <debugger/hook.h>
#include <debugger/io.h>
#include <debugger/rt.h>
#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/kram.h>
#include <kernel/mman/map.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/module.h>
#include <sched/lockop.h>

#include <hybrid/atomic.h>
#include <hybrid/overflow.h>
#include <hybrid/sync/atomic-lock.h>

#include <kos/except.h>
#include <kos/kernel/paging.h>

#include <alloca.h>
#include <assert.h>
#include <stddef.h>
#include <string.h>

#include <libzlib/inflate.h>

#define HINT_ADDR(x, y) x
#define HINT_MODE(x, y) y
#define HINT_GETADDR(x) HINT_ADDR x
#define HINT_GETMODE(x) HINT_MODE x

#ifndef NDEBUG
#define DBG_memset(dst, byte, num_bytes) memset(dst, byte, num_bytes)
#else /* !NDEBUG */
#define DBG_memset(dst, byte, num_bytes) (void)0
#endif /* NDEBUG */

DECL_BEGIN

/************************************************************************/
/* UserELF Section cache                                                */
/************************************************************************/
LIST_HEAD(userelf_module_section_list, REF userelf_module_section);

/* [0..n][lock(uems_cache_lock)][link(ums_cache)]
 * Global  cache of UserELF section objects. In order to keep UserELF
 * module sections loaded for a while longer, even after the user has
 * dropped a reference to them (so-as  to allow for faster lookup  if
 * accessed again), a global cache of references to UserELF  sections
 * if kept. This cache is  maintained thus, that when the  associated
 * UserELF module is destroyed, it  will automatically remove all  of
 * its sections from this cache (via asynchronous lockop operations),
 * meaning that this  cache functions to  automatically clean up  the
 * sections belonging to destroyed modules. */
PRIVATE struct userelf_module_section_list uems_cache      = LIST_HEAD_INITIALIZER(uems_cache);
PRIVATE struct atomic_lock /*           */ uems_cache_lock = ATOMIC_LOCK_INIT;
PRIVATE struct lockop_slist /*          */ uems_cache_lops = SLIST_HEAD_INITIALIZER(uems_cache_lops);
#define _uems_cache_reap()      _lockop_reap_atomic_lock(&uems_cache_lops, &uems_cache_lock)
#define uems_cache_reap()       lockop_reap_atomic_lock(&uems_cache_lops, &uems_cache_lock)
#define uems_cache_tryacquire() atomic_lock_tryacquire(&uems_cache_lock)
#define uems_cache_acquire()    atomic_lock_acquire(&uems_cache_lock)
#define uems_cache_acquire_nx() atomic_lock_acquire_nx(&uems_cache_lock)
#define uems_cache_release()    (atomic_lock_release(&uems_cache_lock), uems_cache_reap())
#define uems_cache_release_f()  atomic_lock_release(&uems_cache_lock)
#define uems_cache_acquired()   atomic_lock_acquired(&uems_cache_lock)
#define uems_cache_available()  atomic_lock_available(&uems_cache_lock)

/* Clear the global cache of UserELF sections, and return a
 * number  representative of an approximation of the amount
 * of memory became available as a result of this. */
DEFINE_SYSTEM_CACHE_CLEAR(uem_clearsections);
INTERN NOBLOCK size_t NOTHROW(KCALL uem_clearsections)(void) {
	size_t result = 0;
	struct userelf_module_section_slist dead;
	if (!uems_cache_tryacquire())
		goto done;

	/* Remove all objects from the cache. */
	SLIST_INIT(&dead);
	while (!LIST_EMPTY(&uems_cache)) {
		REF struct userelf_module_section *sect;
		sect = LIST_FIRST(&uems_cache);
		LIST_UNBIND(sect, ums_cache);
		if (ATOMIC_DECFETCH(sect->ms_refcnt) == 0)
			SLIST_INSERT_HEAD(&dead, sect, _ums_dead);
	}
	uems_cache_release_f();

	/* Destroy dead sections. */
	while (!SLIST_EMPTY(&dead)) {
		struct userelf_module_section *sect;
		sect = SLIST_FIRST(&dead);
		SLIST_REMOVE_HEAD(&dead, _ums_dead);
		uems_destroy(sect);
		result += sizeof(struct userelf_module_section);
	}
	uems_cache_reap();
done:
	return result;
}
/************************************************************************/






/************************************************************************/
PRIVATE /*ATTR_RETNONNULL*/ NONNULL((1)) UM_ElfW_ShdrP FCALL
uem_shdrs(struct userelf_module *__restrict self) {
	UM_ElfW_ShdrP result;
	size_t shsize;
	if (UM_any(self->um_shdrs))
		return self->um_shdrs;
	shsize         = self->um_shnum * UM_sizeof(self, UM_ElfW_Shdr);
	UM_any(result) = (__typeof__(UM_any(result)))kmalloc(shsize, GFP_PREFLT);
	TRY {
		if (!vm_datablock_isinode(self->md_file))
			THROW(E_INVALID_ARGUMENT);
		inode_readallk((struct inode *)self->md_file,
		               UM_any(result), shsize,
		               self->um_shoff);
	} EXCEPT {
		kfree(UM_any(result));
		RETHROW();
	}
	if (!ATOMIC_CMPXCH(UM_any(self->um_shdrs), NULL, UM_any(result)))
		kfree(UM_any(result));
	return self->um_shdrs;
}

PRIVATE NONNULL((1)) char *FCALL
uem_shstrtab(struct userelf_module *__restrict self) {
	UM_ElfW_ShdrP shdrs;
	UM_ElfW_Shdr *shstrtab;
	pos_t shstrtab_pos;
	size_t shstrtab_siz;
	char *shstrtab_str;
	if (self->um_shstrtab)
		return self->um_shstrtab;
	if unlikely(self->um_shstrndx >= self->um_shnum)
		return NULL;
	shdrs        = uem_shdrs(self);
	shstrtab     = (UM_ElfW_Shdr *)UM_field_ptr(self, shdrs, [self->um_shstrndx]);
	shstrtab_pos = (pos_t)UM_field(self, *shstrtab, .sh_offset);
	shstrtab_siz = UM_field(self, *shstrtab, .sh_size);
	shstrtab_str = (char *)kmalloc((shstrtab_siz + 1) * sizeof(char), GFP_PREFLT);
	TRY {
		if (!vm_datablock_isinode(self->md_file))
			THROW(E_INVALID_ARGUMENT);
		inode_readallk((struct inode *)self->md_file,
		               shstrtab_str, shstrtab_siz,
		               shstrtab_pos);
	} EXCEPT {
		kfree(shstrtab_str);
		RETHROW();
	}
	shstrtab_str[shstrtab_siz] = '\0';
	if (!ATOMIC_CMPXCH(self->um_shstrtab, NULL, shstrtab_str))
		kfree(shstrtab_str);
	return self->um_shstrtab;
}




/* Operator tables for userelf module objects. */
INTERN_CONST struct module_section_ops const uems_ops = {
	.ms_destroy         = (void (FCALL *)(struct module_section *__restrict))&uems_destroy,
	.ms_getname         = (char const *(FCALL *)(struct module_section *__restrict))&uems_getname,
	.ms_getaddr         = (void *(FCALL *)(struct module_section *__restrict))&uems_getaddr,
	.ms_getaddr_alias   = (void *(FCALL *)(struct module_section *__restrict))&uems_getaddr_alias,
	.ms_getaddr_inflate = (void *(FCALL *)(struct module_section *__restrict, size_t *__restrict))&uems_getaddr_inflate,
};

INTERN_CONST struct module_ops const uem_ops = {
	.mo_free              = (void (FCALL *)(struct module *__restrict))&uem_free,
	.mo_destroy           = (void (FCALL *)(struct module *__restrict))&uem_destroy,
	.mo_nonodes           = (void (FCALL *)(struct module *__restrict))&uem_nonodes,
	.mo_locksection       = (REF struct module_section *(FCALL *)(struct module *__restrict, USER CHECKED char const *))&uem_locksection,
	.mo_locksection_index = (REF struct module_section *(FCALL *)(struct module *__restrict, unsigned int))&uem_locksection_index,
};


/* UserELF module section operators */
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL uems_destroy)(struct userelf_module_section *__restrict self) {
	REF struct userelf_module *mod;
	mod = (REF struct userelf_module *)self->ms_module;
	if (tryincref(mod)) {
		/* Try to remove `self' from the module's section vector. */
		uint16_t myindex;
		myindex = (uint16_t)((size_t)((byte_t *)self->ums_shdr -
		                              (byte_t *)UM_any(mod->um_shdrs)) /
		                     UM_sizeof(mod, UM_ElfW_Shdr));
		assert(myindex < mod->um_shnum);
		/* Replace a pointer to `self' with `NULL'.
		 * There is the (very) unlikely case that someone reloaded
		 * the section before we were able to delete out  pointer,
		 * in which case that new section already took our spot! */
		awref_cmpxch(&mod->um_sections[myindex], self, NULL);
		decref_unlikely(mod);
	}
	weakdecref(mod);
	if (self->ums_infladdr != (KERNEL void *)-1 &&
	    self->ums_infladdr != self->ums_kernaddr) {
		mman_unmap_kram(self->ums_infladdr,
		                self->ums_inflsize);
	}
	if (self->ums_kernaddr != (KERNEL void *)-1) {
		mman_unmap_kram_and_kfree(self->ums_kernaddr,
		                          self->ms_size,
		                          self);
	} else {
		kfree(self);
	}
}

INTERN WUNUSED NONNULL((1)) char const *FCALL
uems_getname(struct userelf_module_section *__restrict self) {
	struct userelf_module *mod;
	size_t stroffset;
	char const *result;
	mod = (struct userelf_module *)self->ms_module;
	assert(!wasdestroyed(mod));
	stroffset = UM_field(mod, *self->ums_shdr, .sh_name);
	/* Verify that the string table offset is in-bounds. */
	if unlikely(stroffset >= UM_field(mod, mod->um_shdrs, [mod->um_shstrndx].sh_size))
		return NULL;
	result = uem_shstrtab(mod);
	if likely(result)
		result += stroffset;
	return result;
}

INTERN WUNUSED NONNULL((1)) USER CHECKED void *FCALL
uems_getaddr(struct userelf_module_section *__restrict self) {
	if (self->ms_flags & SHF_ALLOC)
		return self->ums_useraddr;
	return uems_getaddr_alias(self);
}

PRIVATE WUNUSED NONNULL((1)) KERNEL void *FCALL
uems_create_kernaddr_ex(struct userelf_module_section *__restrict self,
                        struct userelf_module *__restrict mod) {
	return mman_map(/* self:          */ &mman_kernel,
	                /* hint:          */ HINT_GETADDR(KERNEL_VMHINT_TEMPORARY),
	                /* num_bytes:     */ self->ms_size,
	                /* prot:          */ (PROT_READ | PROT_WRITE) & ~PROT_SHARED,
	                /* flags:         */ HINT_GETMODE(KERNEL_VMHINT_TEMPORARY),
	                /* file:          */ mod->md_file,
	                /* file_fspath:   */ mod->md_fspath,
	                /* file_fsname:   */ mod->md_fsname,
	                /* file_pos:      */ (pos_t)UM_field(mod, *self->ums_shdr, .sh_offset));
}

PRIVATE WUNUSED NONNULL((1)) KERNEL void *FCALL
uems_create_kernaddr(struct userelf_module_section *__restrict self) {
	REF struct userelf_module *mod;
	mod = (REF struct userelf_module *)self->ms_module;
	if (!tryincref(mod))
		THROW(E_NO_SUCH_OBJECT);
	FINALLY_DECREF_UNLIKELY(mod);
	return uems_create_kernaddr_ex(self, mod);
}



INTERN WUNUSED NONNULL((1)) KERNEL void *FCALL
uems_getaddr_alias(struct userelf_module_section *__restrict self) {
	void *result;
	if (self->ums_kernaddr != (KERNEL void *)-1)
		return self->ums_kernaddr;
	result = uems_create_kernaddr(self);
	if unlikely(!ATOMIC_CMPXCH(self->ums_kernaddr, (KERNEL void *)-1, result)) {
		/* Race condition: some other thread already did this in the mean time... */
		mman_unmap_kram(result, self->ms_size);
	}
	return self->ums_kernaddr;
}

INTERN WUNUSED NONNULL((1, 2)) KERNEL void *FCALL
uems_getaddr_inflate(struct userelf_module_section *__restrict self,
                     size_t *__restrict psize) {
	size_t dst_size, src_size;
	KERNEL void *src_data, *dst_data;
	void *src_data_freeme_cookie;
	REF struct userelf_module *mod;
	if (self->ums_infladdr != (KERNEL void *)-1) {
		*psize = self->ums_inflsize;
		return self->ums_infladdr;
	}
	if (!(self->ms_flags & SHF_COMPRESSED)) {
		/* Section isn't actually compressed! */
		dst_data = uems_getaddr_alias(self);
		ATOMIC_WRITE(self->ums_inflsize, self->ms_size);
		ATOMIC_CMPXCH(self->ums_infladdr, (KERNEL void *)-1, dst_data);
		*psize = self->ms_size;
		return dst_data;
	}
	mod = (REF struct userelf_module *)self->ms_module;
	if (!tryincref(mod))
		THROW(E_NO_SUCH_OBJECT);
	FINALLY_DECREF_UNLIKELY(mod);
	if unlikely(OVERFLOW_USUB(self->ms_size, UM_sizeof(mod, UM_ElfW_Chdr), &src_size))
		THROW(E_INVALID_ARGUMENT);
	src_data  = self->ums_kernaddr;
	src_data_freeme_cookie = NULL;
	if (src_data == (KERNEL void *)-1) {
		/* Allocate a  cookie that  we can  later use  to
		 * asynchronously unmap the compressed data blob. */
		src_data_freeme_cookie = kmalloc(sizeof(struct mman_unmap_kram_job),
		                                 GFP_LOCKED | GFP_PREFLT);
		TRY {
			src_data = uems_create_kernaddr_ex(self, mod);
		} EXCEPT {
			kfree(src_data_freeme_cookie);
			RETHROW();
		}
	}
	TRY {
		UM_ElfW_Chdr *chdr;
		chdr = (UM_ElfW_Chdr *)src_data;
		if unlikely(UM_field(mod, *chdr, .ch_type) != ELFCOMPRESS_ZLIB)
			THROW(E_INVALID_ARGUMENT);
		dst_size = UM_field(mod, *chdr, .ch_size);
		dst_data = mman_map_kram(NULL, dst_size, GFP_PREFLT);
		TRY {
			ssize_t error;
			struct zlib_reader reader;
			zlib_reader_init(&reader, src_data, src_size);
			/* Decompress data. */
#ifdef CONFIG_HAVE_DEBUGGER
			if (dbg_active) {
				/* Display an on-screen message that we're decompressing stuff... */
				void *screen_buffer;
				char const *section_name;
				dbg_pprinter_arg_t pp;
				section_name = uems_getname(self);
				if (!section_name)
					section_name = DBGSTR("?");
				screen_buffer = alloca(dbg_screen_width * dbg_screen_cellsize);
				dbg_getscreendata(0, dbg_screen_height - 1, dbg_screen_width, 1, screen_buffer);
				dbg_beginupdate();
				dbg_savecolor();
				dbg_setcolor(ANSITTY_CL_BLACK, ANSITTY_CL_LIGHT_GRAY);
				dbg_hline(0, dbg_screen_height - 1, dbg_screen_width, ' ');
				dbg_pprinter_arg_init(&pp, 0, dbg_screen_height - 1);
				dbg_pprinter(&pp, DBGSTR("Decompressing "), 14);
				if (module_haspath(mod)) {
					module_printpath(mod, &dbg_pprinter, &pp);
				} else if (module_hasname(mod)) {
					module_printname(mod, &dbg_pprinter, &pp);
				} else {
					dbg_pprinter(&pp, DBGSTR("?"), 1);
				}
				dbg_pprinter(&pp, DBGSTR(":"), 1);
				dbg_pprinter(&pp, section_name, strlen(section_name));
				dbg_pprinter(&pp, DBGSTR("..."), 1);
				dbg_loadcolor();
				dbg_endupdate();
				error = zlib_reader_read(&reader, dst_data, dst_size);
				dbg_setscreendata(0, dbg_screen_height - 1, dbg_screen_width, 1, screen_buffer);
			} else {
				error = zlib_reader_read(&reader, dst_data, dst_size);
			}
#else /* CONFIG_HAVE_DEBUGGER */
			error = zlib_reader_read(&reader, dst_data, dst_size);
#endif /* !CONFIG_HAVE_DEBUGGER */
			zlib_reader_fini(&reader);
			if unlikely(error < 0)
				THROW(E_INVALID_ARGUMENT);
			/* clear all trailing data that could not be read. */
			if (dst_size > (size_t)error) {
				memset((byte_t *)dst_data + (size_t)error,
				       0, dst_size - error);
			}
		} EXCEPT {
			mman_unmap_kram(dst_data, dst_size);
			RETHROW();
		}
	} EXCEPT {
		if (src_data_freeme_cookie)
			mman_unmap_kram_and_kfree(src_data, self->ms_size, src_data_freeme_cookie);
		RETHROW();
	}
	if (src_data_freeme_cookie)
		mman_unmap_kram_and_kfree(src_data, self->ms_size, src_data_freeme_cookie);
	ATOMIC_WRITE(self->ums_inflsize, dst_size);
	ATOMIC_CMPXCH(self->ums_infladdr, (KERNEL void *)-1, dst_data);
	*psize = dst_size;
	return dst_data;
}

/* UserELF module operators */
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL uem_free)(struct userelf_module *__restrict self) {
	kfree(self);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL uem_unbind_sections_and_destroy_postlop)(struct postlockop *__restrict self) {
	struct userelf_module *me;
	me = container_of(self, struct userelf_module, _um_sc_postlop);

	/* Destroy dead sections! */
	while (!SLIST_EMPTY(&me->_um_deadsect)) {
		struct userelf_module_section *sect;
		sect = SLIST_FIRST(&me->_um_deadsect);
		SLIST_REMOVE_HEAD(&me->_um_deadsect, _ums_dead);
		uems_destroy(sect);
	}

	/* Proceed normally with the full destruction
	 * of the original UserELF module. */
	module_clear_mnode_pointers_and_destroy(me);
}

PRIVATE NOBLOCK NONNULL((1)) struct postlockop *
NOTHROW(FCALL uem_unbind_sections_and_destroy_lop)(struct lockop *__restrict self) {
	struct userelf_module *me;
	me = container_of(self, struct userelf_module, _um_sc_lop);
	SLIST_INIT(&me->_um_deadsect);

	/* Remove all sections from the . */
	while (me->um_shnum) {
		REF struct userelf_module_section *sect;
		--me->um_shnum;
		sect = awref_get(&me->um_sections[me->um_shnum]);
		if (!sect)
			continue; /* Section was never allocated or is dead. */
		if unlikely(!LIST_ISBOUND(sect, ums_cache)) {
			decref_unlikely(sect);
			continue; /* Section isn't apart of the cache... */
		}
		LIST_UNBIND(sect, ums_cache);
		decref_nokill(sect); /* The reference from the section cache. */

		/* Drop the reference we got from `awref_get()'
		 * If this ends up destroying the section, then enqueue said
		 * destruction to be performed  as part of the  post-lockop. */
		if (ATOMIC_DECFETCH(sect->ms_refcnt) == 0)
			SLIST_INSERT(&me->_um_deadsect, sect, _ums_dead);
	}

	/* Do the rest of the module destruction, as well as the
	 * cleanup  of dead sections  from within a post-lockop,
	 * thereby reducing the amount of time spent holding the
	 * UEMS cache lock. */
	me->_um_sc_postlop.plo_func = &uem_unbind_sections_and_destroy_postlop;
	return &me->_um_sc_postlop;
}

INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL uem_destroy)(struct userelf_module *__restrict self) {
	decref_unlikely(self->md_file);
	xdecref_unlikely(self->md_fspath);
	xdecref_unlikely(self->md_fsname);
	kfree(UM_any(self->um_shdrs));
	kfree(self->um_shstrtab);

	/* Remove all of the UserELF module's sections from the global sections cache. */
	while (self->um_shnum) {
		REF struct userelf_module_section *sect;
		--self->um_shnum;
		sect = awref_get(&self->um_sections[self->um_shnum]);
		if (!sect)
			continue; /* Section was never allocated or is dead. */
		if unlikely(!LIST_ISBOUND(sect, ums_cache)) {
			decref_unlikely(sect);
			continue; /* Section isn't apart of the cache... */
		}

		/* Must remove this section from the cache. */
		if (uems_cache_tryacquire()) {
			if likely(LIST_ISBOUND(sect, ums_cache)) {
				LIST_UNBIND(sect, ums_cache);
				decref_nokill(sect);
			}
			uems_cache_release_f();
			decref_likely(sect);
			uems_cache_reap();
		} else {
			/* Must  use  a lockop  to unbind  the section
			 * once the UEMS cache lock becomes available.
			 *
			 * For this purpose,  we (re-)use the  original
			 * UserELF module object as a storage container
			 * for the a lockop descriptor that's then used
			 * to  remove all of the module's sections from
			 * the UserELF section cache. */
			++self->um_shnum; /* Must do the last section once again! */
			self->_um_sc_lop.lo_func = &uem_unbind_sections_and_destroy_lop;
			SLIST_ATOMIC_INSERT(&uems_cache_lops, &self->_um_sc_lop, lo_link);
			decref_unlikely(sect);
			_uems_cache_reap();
			return;
		}
	}

	module_clear_mnode_pointers_and_destroy(self);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL uem_nonodes_cleanup_postlop)(Tobpostlockop(struct mman) *__restrict self,
                                           struct mman *__restrict UNUSED(mm)) {
	struct userelf_module *me;
	me = container_of(self, struct userelf_module, _um_cc_postlop);
	assert(wasdestroyed(me));
	assert(me->md_ops == &uem_ops);
	uem_destroy(me);
}

PRIVATE NOBLOCK NONNULL((1)) Tobpostlockop(struct mman) *
NOTHROW(FCALL uem_nonodes_cleanup_lop)(Toblockop(struct mman) *__restrict self,
                                       struct mman *__restrict UNUSED(mm)) {
	struct userelf_module *me;
	me = container_of(self, struct userelf_module, _um_cc_lop);
	me->_um_cc_postlop.oplo_func = &uem_nonodes_cleanup_postlop;
	return &me->_um_cc_postlop;
}

INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL uem_nonodes)(struct userelf_module *__restrict self) {
	/* Remove `self' from the UserELF module cache of the associated
	 * VM  (in case the module was apart  of said cache), and drop a
	 * reference when this was the case.
	 *
	 * Note that `self' may have already been destroyed when the
	 * module was already removed from the UserELF module  cache
	 * for some other reason.
	 *
	 * In  either  case, we  know that  `self'  can't have  been fully
	 * destroyed,  since  we get  here  via one  of  the mnode->module
	 * self-pointers, which are cleared as part of module destruction.
	 * Furthermore,  due  to the  fact  that our  caller  is currently
	 * holding  a  lock  to  `self->md_mman->mm_lock',  we  know  that
	 * a potential  async destroy  operation will  only commence  once
	 * our caller has released said lock.
	 * iow: We much check for `wasdestroyed(self)' and no-op out
	 *      if that is the case! */
	if unlikely(wasdestroyed(self))
		return;

	if (LIST_ISBOUND(self, um_cache)) {
		/* Remove from the UserELF module cache. */
		assert(!wasdestroyed(self->md_mman));
		assert(mman_lock_acquired(self->md_mman));
		LIST_REMOVE(self, um_cache);
		DBG_memset(&self->um_cache, 0xcc, sizeof(self->um_cache));

		/* Drop a reference from `self'. If this results in `self'
		 * being  destroyed, then delay  invocation of the destroy
		 * function until our caller ends up releasing their  lock
		 * to the associated mman's mappings tree.
		 *
		 * We can do this by enqueuing a lockop->postlockop wrapper. */
		if (ATOMIC_DECFETCH(self->md_refcnt) == 0) {
			self->_um_cc_lop.olo_func = &uem_nonodes_cleanup_lop;
			SLIST_ATOMIC_INSERT(&FORMMAN(self->md_mman, thismman_lockops),
			                    &self->_um_cc_lop, olo_link);
			/* DONT REAP LOCKOPS HERE!
			 *
			 * It won't work since our caller still holds a lock to
			 * the  associated mman's mappings lock. Also: the only
			 * reason  we're  enqueuing the  destruction  of `self'
			 * via  a lockop is  so it can  happen _after_ the mman
			 * lock has been released!
			 *
			 * Note however that doing a normal decref() here  would
			 * also be semantically acceptable, however by doing the
			 * actual destruction later, we can reduce the amount of
			 * time spent holding onto the mman's mappings lock! */
		}
	}
}


INTERN WUNUSED NONNULL((1)) REF struct userelf_module_section *FCALL
uem_locksection_index_impl(struct userelf_module *__restrict self,
                           UM_ElfW_Shdr *shdr, uint16_t section_index) {
	REF struct userelf_module_section *result;
again:
	result = awref_get(&self->um_sections[section_index]);
	if (result)
		return result;

	/* Actually create the new section */
	result = (REF struct userelf_module_section *)kmalloc(sizeof(struct userelf_module_section),
	                                                      GFP_PREFLT);

	/* Fill in information about the section. */
	result->ms_refcnt    = 1;
	result->ms_ops       = &uems_ops;
	result->ms_module    = weakincref(self);
	result->ms_size      = UM_field(self, *shdr, .sh_size);
	result->ms_entsize   = UM_field(self, *shdr, .sh_entsize);
	result->ms_type      = UM_field(self, *shdr, .sh_type);
	result->ms_flags     = UM_field(self, *shdr, .sh_flags);
	result->ms_link      = UM_field(self, *shdr, .sh_link);
	result->ms_info      = UM_field(self, *shdr, .sh_info);
	result->ums_shdr     = shdr;
	result->ums_useraddr = (USER CHECKED void *)-1;
	result->ums_kernaddr = (KERNEL void *)-1;
	result->ums_infladdr = (KERNEL void *)-1;
	result->ums_inflsize = 0;
	if (result->ms_flags & SHF_ALLOC) {
		/* Set the user-space load-address for allocated sections. */
		result->ums_useraddr = (USER CHECKED void *)(self->md_loadaddr +
		                                             UM_field(self, *shdr, .sh_addr));
	}

	/* Acquire a lock to the UserELF section cache. */
	TRY {
		uems_cache_acquire();
	} EXCEPT {
		destroy(result);
		RETHROW();
	}

	/* Replace a previously destroyed section object with the new section! */
	if (!awref_replacedead(&self->um_sections[section_index], result)) {
		uems_cache_release();
		destroy(result);
		goto again;
	}

	/* Add the new section to the sections cache.
	 * This is done to prevent the section from being destroyed
	 * the  second the caller of `module_locksection()' ends up
	 * dropping the reference we return.
	 *
	 * However, sections are  automatically removed  from
	 * the cache when the associated module is destroyed. */
	LIST_INSERT_HEAD(&uems_cache, result, ums_cache);

	/* Release the lock from the UserELF section cache. */
	uems_cache_release();

	return result;
}


INTERN WUNUSED NONNULL((1)) REF struct userelf_module_section *FCALL
uem_locksection(struct userelf_module *__restrict self,
                USER CHECKED char const *section_name) {
	uint16_t i;
	UM_ElfW_ShdrP shdrs;
	char *shstrtab_str;
	size_t shstrtab_siz;
	shstrtab_str = uem_shstrtab(self);
	if unlikely(!shstrtab_str)
		return NULL;
	shdrs        = self->um_shdrs;
	shstrtab_siz = UM_field(self, shdrs, [self->um_shstrndx].sh_size);
	for (i = 0; i < self->um_shnum; ++i) {
		size_t stroffset;
		char const *sect_name;
		stroffset = UM_field(self, shdrs, [i].sh_name);
		if unlikely(stroffset >= shstrtab_siz)
			continue; /* Shouldn't happen... */
		sect_name = shstrtab_str + stroffset;
		if (strcmp(section_name, sect_name) != 0)
			continue; /* Different name... */
		return uem_locksection_index_impl(self, (UM_ElfW_Shdr *)UM_field_ptr(self, shdrs, [i]), i);
	}
	return NULL;
}


INTERN WUNUSED NONNULL((1)) REF struct userelf_module_section *FCALL
uem_locksection_index(struct userelf_module *__restrict self,
                      unsigned int section_index) {
	UM_ElfW_ShdrP shdrs;
	if unlikely(section_index >= self->um_shnum)
		return NULL;
	shdrs = uem_shdrs(self);
	return uem_locksection_index_impl(self, (UM_ElfW_Shdr *)UM_field_ptr(self, shdrs, [section_index]),
	                                  (uint16_t)section_index);
}



/************************************************************************/
/* UserELF Module creation                                              */
/************************************************************************/

LIST_HEAD(userelf_module_list, userelf_module);
SLIST_HEAD(userelf_module_slist, userelf_module);

/* [0..n][lock(mman::mm_lock)] Per-mman UserELF Module Cache */
PRIVATE ATTR_PERMMAN struct REF userelf_module_list
thismman_uemc = LIST_HEAD_INITIALIZER(thismman_uemc);


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
	size_t result = 0;
	struct userelf_module_slist dead;

	/* Try to acquire the lock because we need to be NOBLOCK! */
	if (!mman_lock_tryacquire(self))
		goto done;

	/* Clear the UEMC cache. */
	SLIST_INIT(&dead);
	while (!LIST_EMPTY(&FORMMAN(self, thismman_uemc))) {
		REF struct userelf_module *mod;
		mod = LIST_FIRST(&FORMMAN(self, thismman_uemc));
		LIST_UNBIND(mod, um_cache);
		/* Drop  references  originally   held  by  the   cache.
		 * Modules that end up dying are added to the dead-list,
		 * where they will be destroyed once we've released  our
		 * lock to the mman. */
		if (ATOMIC_DECFETCH(mod->md_refcnt) == 0) {
			/* Add to the dead-list. */
			SLIST_INSERT(&dead, mod, _um_dead);
		}
	}
	mman_lock_release_f(self);

	/* Destroy all dead UserELF modules. */
	while (!SLIST_EMPTY(&dead)) {
		struct userelf_module *mod;
		mod = SLIST_FIRST(&dead);
		SLIST_REMOVE_HEAD(&dead, _um_dead);
		uem_destroy(mod);
		result += sizeof(struct userelf_module);
	}

	/* Reap lock operations relatively late! */
	mman_lockops_reap(self);
done:
	return result;
}



/* Special return values for `uem_trycreate()' */
#define UEM_TRYCREATE_UNLOCKED       ((REF struct userelf_module *)-1)
#define UEM_TRYCREATE_UNLOCKED_NOUEM ((REF struct userelf_module *)-2)

/* Try to create a UserELF module for the given `node' from `self'.
 * For this purpose, this function  is called while holding a  lock
 * to the mappings-tree of `self',  which this function is  allowed
 * to release/re-acquire, depending on necessity.
 * The locking lock is as follows:
 *
 *   IN:  >> mman_lock_acquired(self)
 *
 *   OUT: return == NULL:
 *        >> mman_lock_acquired(self)
 *        Lock was never released, and `node' doesn't
 *        point  at something that could be a UserELF
 *        module.
 *
 *   OUT: return == UEM_TRYCREATE_UNLOCKED:
 *        >> !mman_lock_acquired(self)
 *        Lock  was released, but `node' was unmapped/altered
 *        in some unexpected way after the lock to `self' was
 *        first lost.
 *        The caller should handle this case by re-gaining  a
 *        lock to `self', and either starting over, or simply
 *        re-loading `node' based on its address.
 *
 *   OUT: return == UEM_TRYCREATE_UNLOCKED_NOUEM:
 *        >> !mman_lock_acquired(self)
 *        Lock was released before it was determined that the
 *        given  `node' doesn't reference anything that might
 *        resemble a UserELF module.
 *
 *   OUT: return == *:
 *        >> !mman_lock_acquired(self)
 *        Successfully created a UserELF module for `node'.
 *
 *   OUT: EXCEPT:
 *        >> !mman_lock_acquired(self)
 *        An   exception   was  thrown
 */
PRIVATE REF struct userelf_module *FCALL
uem_trycreate(struct mman *__restrict self,
              struct mnode *__restrict node) {
	REF struct userelf_module *result;

	/* Quick check: Is there already a module registered under this node? */
	result = (REF struct userelf_module *)node->mn_module;
	if (result != NULL) {
		if unlikely(result->md_ops != &uem_ops)
			return NULL; /* Shouldn't happen... */

		/* Try to get a reference to the pointed-to module.
		 * Note  that  since `mn_module'  contains indirect
		 * weak  references, we have to tryincref() in case
		 * the pointed-to module isn't cached, and is being
		 * destroyed at the moment. */
		if likely(tryincref(result)) {
			assertf(result->md_nodecount >= 1,
			        "We know that there is at least 1 node!");
			mman_lock_release(self);
			return result;
		}

		/* Cleanup dead UserELF modules. */
		node->mn_module = NULL;
	}

	/* Check if this node might qualify as a UserELF module. */
	/* TODO */


	COMPILER_IMPURE();
	(void)self;
	(void)node;
	/* TODO */
	return NULL;
}




INTERN WUNUSED NONNULL((1)) REF struct userelf_module *FCALL
uem_fromaddr(struct mman *__restrict self,
             USER CHECKED void const *addr) {
	REF struct userelf_module *result;
	struct mnode *node;
again:
	mman_lock_acquire(self);
	node = mman_mappings_locate(self, addr);
	if (!node) {
		mman_lock_release(self);
		return NULL;
	}

	/* Try to create a UserELF module ontop of this node. */
	result = uem_trycreate(self, node);

	/* Handle all of the different cases... */
	if (result == NULL) {
		mman_lock_release(self);
	} else if (result == UEM_TRYCREATE_UNLOCKED) {
		goto again;
	} else if (result == UEM_TRYCREATE_UNLOCKED_NOUEM) {
		result = NULL;
	}
	return result;
}

INTERN WUNUSED NONNULL((1)) REF struct userelf_module *FCALL
uem_aboveaddr(struct mman *__restrict self,
              USER CHECKED void const *addr) {
	REF struct userelf_module *result;
	struct mnode *node;
	struct mnode_tree_minmax mima;
again:
	mman_lock_acquire(self);
	mman_mappings_minmaxlocate(self, addr, (void *)-1, &mima);
	node = mima.mm_min;
	if (!node) {
		mman_lock_release(self);
		return NULL;
	}
	for (;;) {
		void *node_minaddr = mnode_getminaddr(node);
		void *node_maxaddr = mnode_getmaxaddr(node);

		/* Try to create a UserELF module ontop of this node. */
		result = uem_trycreate(self, node);

		/* Handle all of the different cases... */
		if (result == NULL) {
			if (node == mima.mm_max) {
				mman_lock_release(self);
				return NULL;
			}
			node = mnode_tree_nextnode(node);
			assert(node);
		} else if (result == UEM_TRYCREATE_UNLOCKED) {
			addr = node_minaddr;
			goto again;
		} else if (result == UEM_TRYCREATE_UNLOCKED_NOUEM) {
			addr = (byte_t *)node_maxaddr + 1;
			goto again;
		} else {
			/* Got it! */
			break;
		}
	}
	return result;
}

INTERN WUNUSED NONNULL((1)) REF struct userelf_module *FCALL
uem_next(struct mman *__restrict self,
         struct userelf_module *__restrict prev) {
	REF struct userelf_module *result;
	struct mnode *node;
	struct mnode_tree_minmax mima;
	void *minaddr;
	/* Because UserELF modules can be embedded inside of each other,
	 * we have to start looking  for them starting immediatly  after
	 * the original node. */
	minaddr = (byte_t *)prev->md_loadstart + PAGESIZE;
again:
	mman_lock_acquire(self);
	mman_mappings_minmaxlocate(self, minaddr, (void *)-1, &mima);
	node = mima.mm_min;
	if (!node) {
		mman_lock_release(self);
		return NULL;
	}
	for (;;) {
		void *node_minaddr, *node_maxaddr;

		/* Check if this node is known to be bound to the old module.
		 * If it is, then simply skip this node! */
		if (node->mn_module == prev) {
nextnode:
			if (node == mima.mm_max) {
				mman_lock_release(self);
				return NULL;
			}
			node = mnode_tree_nextnode(node);
			assert(node);
			continue;
		}

		node_minaddr = mnode_getminaddr(node);
		node_maxaddr = mnode_getmaxaddr(node);

		/* Try to create a UserELF module ontop of this node. */
		result = uem_trycreate(self, node);

		/* Handle all of the different cases... */
		if (result == NULL) {
			goto nextnode;
		} else if (result == UEM_TRYCREATE_UNLOCKED) {
			minaddr = node_minaddr;
			goto again;
		} else if (result == UEM_TRYCREATE_UNLOCKED_NOUEM) {
			minaddr = (byte_t *)node_maxaddr + 1;
			goto again;
		} else if (result == prev) {
			/* Got the same module all over again... (skip this node) */
			minaddr = (byte_t *)node_maxaddr + 1;
			decref_nokill(result);
			goto again;
		} else {
			/* Found the actual next UserELF module! */
			break;
		}
	}
	return result;
}


DECL_END
#endif /* CONFIG_HAVE_USERELF_MODULES */

#endif /* !GUARD_KERNEL_SRC_MEMORY_MODULE_USERELF_C */
