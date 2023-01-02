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
#ifndef GUARD_KERNEL_SRC_MEMORY_MODULE_USERELF_C
#define GUARD_KERNEL_SRC_MEMORY_MODULE_USERELF_C 1
#define __WANT_MODULE_SECTION__ms_dead
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

/**/
#include "module-userelf.h"

#ifdef CONFIG_HAVE_KERNEL_USERELF_MODULES

#include <debugger/config.h>
#include <debugger/hook.h>
#include <debugger/io.h>
#include <debugger/rt.h>
#include <kernel/execabi.h> /* execabi_system_rtld_file, compat_execabi_system_rtld_file */
#include <kernel/fs/dirent.h>
#include <kernel/fs/node.h>
#include <kernel/fs/path.h>
#include <kernel/fs/vfs.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/cc.h>
#include <kernel/mman/event.h>
#include <kernel/mman/flags.h>
#include <kernel/mman/kram.h>
#include <kernel/mman/map.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/module-section-cache.h>
#include <kernel/mman/module.h>
#include <kernel/mman/ramfile.h> /* `struct mramfile' */
#include <kernel/panic.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/overflow.h>
#include <hybrid/sched/atomic-lock.h>

#include <compat/config.h>
#include <kos/except.h>
#include <kos/exec/rtld.h>
#include <kos/kernel/paging.h>
#include <kos/lockop.h>

#include <alloca.h>
#include <assert.h>
#include <dirent.h>
#include <limits.h>
#include <stddef.h>
#include <string.h>

#include <libzlib/inflate.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/kos/exec/rtld.h>
#endif /* __ARCH_HAVE_COMPAT */

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <kernel/mman/execinfo.h>

#include <inttypes.h>
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/* Max # of section headers accepted for UserELF modules.
 * A limit must be imposed to prevent malicious  programs
 * from flooding kernel-space memory. */
#ifndef ELF_ARCH_MAXSHCOUNT
#define ELF_ARCH_MAXSHCOUNT 128
#endif /* !ELF_ARCH_MAXSHCOUNT */

#ifndef ELF_ARCH_MAXDYNCOUNT
#define ELF_ARCH_MAXDYNCOUNT 256
#endif /* !ELF_ARCH_MAXDYNCOUNT */

#ifndef ELF_ARCH_MAXSHSTRTAB_SIZ
#define ELF_ARCH_MAXSHSTRTAB_SIZ 65536
#endif /* !ELF_ARCH_MAXSHSTRTAB_SIZ */

DECL_BEGIN

/************************************************************************/
PRIVATE BLOCKING NONNULL((1)) UM_ElfW_ShdrP FCALL
uem_shdrs(struct userelf_module *__restrict self) {
	UM_ElfW_ShdrP result;
	size_t shsize;
	if (UM_any(self->um_shdrs))
		return self->um_shdrs;
	shsize         = self->um_shnum * UM_sizeof(self, UM_ElfW_Shdr);
	UM_any(result) = (typeof(UM_any(result)))kmalloc(shsize, GFP_PREFLT);
	TRY {
		mfile_readall(self->md_file, UM_any(result),
		              shsize, self->um_shoff);
	} EXCEPT {
		kfree(UM_any(result));
		RETHROW();
	}
	if unlikely(!ATOMIC_CMPXCH(UM_any(self->um_shdrs),
	                           NULL, UM_any(result)))
		kfree(UM_any(result));
	return self->um_shdrs;
}

PRIVATE BLOCKING NONNULL((1)) char *FCALL
uem_shstrtab(struct userelf_module *__restrict self) {
	UM_ElfW_ShdrP shdrs;
	UM_ElfW_Shdr *shstrtab;
	pos_t shstrtab_pos;
	size_t shstrtab_siz;
	char *shstrtab_str;
	if (self->um_shstrtab)
		return self->um_shstrtab;
	assert(self->um_shstrndx < self->um_shnum);
	shdrs        = uem_shdrs(self);
	shstrtab     = (UM_ElfW_Shdr *)UM_field_ptr(self, shdrs, [self->um_shstrndx]);
	shstrtab_pos = (pos_t)UM_field(self, *shstrtab, .sh_offset);
	shstrtab_siz = UM_field(self, *shstrtab, .sh_size);
	if unlikely(shstrtab_siz > ELF_ARCH_MAXSHSTRTAB_SIZ)
		return NULL;
	shstrtab_str = (char *)kmalloc((shstrtab_siz + 1) * sizeof(char), GFP_PREFLT);
	TRY {
		mfile_readall(self->md_file, shstrtab_str,
		              shstrtab_siz, shstrtab_pos);
	} EXCEPT {
		kfree(shstrtab_str);
		RETHROW();
	}
	shstrtab_str[shstrtab_siz] = '\0';
	if (!ATOMIC_CMPXCH(self->um_shstrtab, NULL, shstrtab_str))
		kfree(shstrtab_str);
	return self->um_shstrtab;
}


PRIVATE WUNUSED NONNULL((1)) void const *
NOTHROW(FCALL get_segment_start_byflags)(struct userelf_module const *__restrict self,
                                         ElfW(Word) pf_flags) {
	void const *result;
	ElfW(Half) i;
	COMPILER_IMPURE();

	/* Search for the lowest program header with the correct flags. */
	for (result = (void const *)-1, i = 0; i < self->um_phnum; ++i) {
		uintptr_t hdraddr;
		if (UM_field(self, self->um_phdrs, [i].p_type) != PT_LOAD)
			continue;
		if ((UM_field(self, self->um_phdrs, [i].p_flags) & (PF_R | PF_W | PF_X)) != pf_flags)
			continue;
		hdraddr = self->md_loadaddr + UM_field(self, self->um_phdrs, [i].p_vaddr);
		if ((uintptr_t)result > hdraddr)
			result = (void *)hdraddr;
	}
	if (result == (void const *)-1)
		result = NULL;
	return result;
}

PRIVATE WUNUSED NONNULL((1)) void const *
NOTHROW(FCALL uem_get_tbase)(struct userelf_module *__restrict self) {
	return get_segment_start_byflags(self, PF_R | PF_X);
}

#if defined(__i386__) || (defined(__x86_64__) && defined(__ARCH_HAVE_COMPAT))
PRIVATE BLOCKING WUNUSED NONNULL((1)) uint32_t FCALL
scan_dynamic_for_DT_PLTGOT(struct mfile *__restrict file,
                           pos_t dynamic_offset,
                           size_t dynamic_count) {
	Elf32_Dyn *dynamic;
	uint32_t result = 0;
	size_t i, total_size;
	if unlikely(dynamic_count == 0)
		goto done;
	total_size = dynamic_count * sizeof(Elf32_Dyn);
	dynamic    = (Elf32_Dyn *)alloca(total_size);
	mfile_readall(file, dynamic, total_size, dynamic_offset);
	for (i = 0; i < dynamic_count; ++i) {
		if (dynamic[i].d_tag == DT_PLTGOT) {
			result = dynamic[i].d_un.d_ptr;
			break;
		}
	}
done:
	return result;
}

PRIVATE BLOCKING WUNUSED NONNULL((1)) void const *
NOTHROW(FCALL uem_get_dbase_386)(struct userelf_module *__restrict self) {
#ifdef UM_HYBRID
#define um_phdrs32 um_phdrs._32
#else /* UM_HYBRID */
#define um_phdrs32 um_phdrs
#endif /* !UM_HYBRID */

	/* Special case for data-base on i386:
	 * For reference, see Glibc: `/sysdeps/generic/unwind-dw2-fde-glibc.c' */
	uintptr_t result;
	if (self->_um_DT_PLTGOT == (uint32_t)-1) {
		size_t i;
		for (i = 0; i < self->um_phnum; ++i) {
			if (self->um_phdrs32[i].p_type != PT_DYNAMIC)
				continue;
			if (self->um_phdrs32[i].p_filesz > (ELF_ARCH_MAXDYNCOUNT * sizeof(Elf32_Dyn)))
				break;
			NESTED_TRY {
				self->_um_DT_PLTGOT = scan_dynamic_for_DT_PLTGOT(self->md_file,
				                                                 (pos_t)self->um_phdrs32[i].p_offset,
				                                                 self->um_phdrs32[i].p_filesz / sizeof(Elf32_Dyn));
			} EXCEPT {
				self->_um_DT_PLTGOT = 0;
			}
			goto done;
		}
		self->_um_DT_PLTGOT = 0;
	}
done:
	result = self->_um_DT_PLTGOT;
	if (result != 0)
		result += self->md_loadaddr;
	return (void const *)result;
#undef um_phdrs32
}
#endif /* __i386__ || (__x86_64__ && __ARCH_HAVE_COMPAT) */

PRIVATE BLOCKING WUNUSED NONNULL((1)) void const *
NOTHROW(FCALL uem_get_dbase)(struct userelf_module *__restrict self) {
#if defined(__i386__) && !defined(__x86_64__)
	return uem_get_dbase_386(self);
#elif defined(__x86_64__) && defined(__ARCH_HAVE_COMPAT)
	void const *result;
	if (module_sizeof_pointer(self) == 4) {
		result = uem_get_dbase_386(self);
	} else {
		result = get_segment_start_byflags(self, PF_R | PF_W);
	}
	return result;
#else /* ... */
	return get_segment_start_byflags(self, PF_R | PF_W);
#endif /* !... */
}




/* Operator tables for userelf module objects. */
INTERN_CONST struct module_section_ops const uems_ops = {
	.ms_destroy         = (NONNULL_T((1)) void NOTHROW_T(FCALL *)(struct module_section *__restrict))&uems_destroy,
	.ms_getname         = (ATTR_PURE_T WUNUSED_T NONNULL_T((1)) char const *NOTHROW_T(FCALL *)(struct module_section *__restrict))&uems_getname,
	.ms_getaddr         = (WUNUSED_T NONNULL_T((1)) byte_t *NOTHROW_T(FCALL *)(struct module_section *__restrict))&uems_getaddr,
	.ms_getaddr_alias   = (WUNUSED_T NONNULL_T((1)) byte_t *NOTHROW_T(FCALL *)(struct module_section *__restrict))&uems_getaddr_alias,
	.ms_getaddr_inflate = (WUNUSED_T NONNULL_T((1, 2)) byte_t *NOTHROW_T(FCALL *)(struct module_section *__restrict, size_t *__restrict))&uems_getaddr_inflate,
};

INTERN_CONST struct module_ops const uem_ops = {
	.mo_free              = (NONNULL_T((1)) void NOTHROW_T(FCALL *)(struct module *__restrict))&uem_free,
	.mo_destroy           = (NONNULL_T((1)) void NOTHROW_T(FCALL *)(struct module *__restrict))&uem_destroy,
	.mo_nonodes           = (NONNULL_T((1)) void NOTHROW_T(FCALL *)(struct module *__restrict))&uem_nonodes,
	.mo_locksection       = (WUNUSED_T NONNULL_T((1)) REF struct module_section *NOTHROW_T(FCALL *)(struct module *__restrict, USER CHECKED char const *))&uem_locksection,
	.mo_locksection_index = (WUNUSED_T NONNULL_T((1)) REF struct module_section *NOTHROW_T(FCALL *)(struct module *__restrict, unsigned int))&uem_locksection_index,
	.mo_sectinfo          = (WUNUSED_T NONNULL_T((1, 3)) bool NOTHROW_T(FCALL *)(struct module *__restrict, uintptr_t, struct module_sectinfo *__restrict))&uem_sectinfo,
	.mo_get_tbase         = (WUNUSED_T NONNULL_T((1)) void const *NOTHROW_T(FCALL *)(struct module *__restrict))&uem_get_tbase,
	.mo_get_dbase         = (WUNUSED_T NONNULL_T((1)) void const *NOTHROW_T(FCALL *)(struct module *__restrict))&uem_get_dbase
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
	if (self->ums_infladdr != (KERNEL byte_t *)-1 &&
	    self->ums_infladdr != self->ums_kernaddr) {
		mman_unmap_kram(self->ums_infladdr,
		                self->ums_inflsize);
	}
	if (self->ums_kernaddr != (KERNEL byte_t *)-1) {
		mman_unmap_kram_and_kfree(self->ums_kernaddr,
		                          self->ms_size,
		                          self);
	} else {
		kfree(self);
	}
}

INTERN BLOCKING WUNUSED NONNULL((1)) char const *FCALL
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

INTERN BLOCKING WUNUSED NONNULL((1)) USER CHECKED byte_t *FCALL
uems_getaddr(struct userelf_module_section *__restrict self) {
	if (self->ms_flags & SHF_ALLOC)
		return self->ums_useraddr;
	return uems_getaddr_alias(self);
}

PRIVATE BLOCKING WUNUSED NONNULL((1)) KERNEL byte_t *FCALL
uems_create_kernaddr_ex(struct userelf_module_section *__restrict self,
                        struct userelf_module *__restrict mod) {
	assert(self->ms_size != 0);
	return (byte_t *)mman_map(/* self:        */ &mman_kernel,
	                          /* hint:        */ MHINT_GETADDR(KERNEL_MHINT_TEMPORARY),
	                          /* num_bytes:   */ self->ms_size,
	                          /* prot:        */ (PROT_READ | PROT_WRITE) & ~PROT_SHARED,
	                          /* flags:       */ MHINT_GETMODE(KERNEL_MHINT_TEMPORARY),
	                          /* file:        */ mod->md_file,
	                          /* file_fspath: */ mod->md_fspath,
	                          /* file_fsname: */ mod->md_fsname,
	                          /* file_pos:    */ (pos_t)UM_field(mod, *self->ums_shdr, .sh_offset));
}

PRIVATE BLOCKING WUNUSED NONNULL((1)) KERNEL byte_t *FCALL
uems_create_kernaddr(struct userelf_module_section *__restrict self) {
	REF struct userelf_module *mod;
	if unlikely(self->ms_size == 0)
		return (KERNEL byte_t *)KERNELSPACE_BASE + PAGESIZE;
	mod = (REF struct userelf_module *)self->ms_module;
	if (!tryincref(mod))
		THROW(E_NO_SUCH_OBJECT);
	FINALLY_DECREF_UNLIKELY(mod);
	return uems_create_kernaddr_ex(self, mod);
}



INTERN BLOCKING WUNUSED NONNULL((1)) KERNEL byte_t *FCALL
uems_getaddr_alias(struct userelf_module_section *__restrict self) {
	byte_t *result;
	if (self->ums_kernaddr != (KERNEL byte_t *)-1)
		return self->ums_kernaddr;
	result = uems_create_kernaddr(self);
	if unlikely(!ATOMIC_CMPXCH(self->ums_kernaddr, (KERNEL byte_t *)-1, result)) {
		/* Race condition: some other thread already did this in the mean time... */
		mman_unmap_kram(result, self->ms_size);
	}
	return self->ums_kernaddr;
}

INTERN BLOCKING WUNUSED NONNULL((1, 2)) KERNEL byte_t *FCALL
uems_getaddr_inflate(struct userelf_module_section *__restrict self,
                     size_t *__restrict psize) {
	size_t sizeof_cdhr;
	size_t dst_size, src_size;
	KERNEL byte_t *src_data, *dst_data;
	void *src_data_freeme_cookie;
	REF struct userelf_module *mod;
	if (self->ums_infladdr != (KERNEL byte_t *)-1) {
		*psize = self->ums_inflsize;
		return self->ums_infladdr;
	}
	if (!(self->ms_flags & SHF_COMPRESSED)) {
		/* Section isn't actually compressed! */
		dst_data = uems_getaddr_alias(self);
		ATOMIC_WRITE(self->ums_inflsize, self->ms_size);
		ATOMIC_CMPXCH(self->ums_infladdr, (KERNEL byte_t *)-1, dst_data);
		*psize = self->ms_size;
		return dst_data;
	}
	mod = (REF struct userelf_module *)self->ms_module;
	if (!tryincref(mod))
		THROW(E_NO_SUCH_OBJECT);
	FINALLY_DECREF_UNLIKELY(mod);
	sizeof_cdhr = UM_sizeof(mod, UM_ElfW_Chdr);
	if unlikely(OVERFLOW_USUB(self->ms_size, sizeof_cdhr, &src_size))
		THROW(E_INVALID_ARGUMENT);
	src_data = self->ums_kernaddr;
	src_data_freeme_cookie = NULL;
	if (src_data == (KERNEL byte_t *)-1) {
		/* Allocate a  cookie that  we can  later use  to
		 * asynchronously unmap the compressed data blob. */
		src_data_freeme_cookie = mman_unmap_kram_cookie_alloc();
		TRY {
			src_data = uems_create_kernaddr_ex(self, mod);
		} EXCEPT {
			mman_unmap_kram_cookie_free(src_data_freeme_cookie);
			RETHROW();
		}
	}
	{
		UM_ElfW_Chdr *chdr;
		RAII_FINALLY {
			if (src_data_freeme_cookie)
				mman_unmap_kram_and_kfree(src_data, self->ms_size, src_data_freeme_cookie);
		};
		chdr = (UM_ElfW_Chdr *)src_data;
		if unlikely(UM_field(mod, *chdr, .ch_type) != ELFCOMPRESS_ZLIB)
			THROW(E_INVALID_ARGUMENT);
		dst_size = UM_field(mod, *chdr, .ch_size);
		dst_data = (KERNEL byte_t *)mman_map_kram(NULL, dst_size, GFP_PREFLT);
		TRY {
			ssize_t error;
			struct zlib_reader reader;
			zlib_reader_init(&reader, src_data + sizeof_cdhr, src_size);

			/* Decompress data. */
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
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
				if (module_haspath_or_name(mod)) {
					module_printpath_or_name(mod, &dbg_pprinter, &pp);
				} else {
					dbg_pprinter_putuni(&pp, '?');
				}
				dbg_pprinter_putuni(&pp, ':');
				dbg_pprinter(&pp, section_name, strlen(section_name));
				dbg_pprinter(&pp, DBGSTR("..."), 3);
				dbg_loadcolor();
				dbg_endupdate();
				error = zlib_reader_read(&reader, dst_data, dst_size);
				dbg_setscreendata(0, dbg_screen_height - 1, dbg_screen_width, 1, screen_buffer);
			} else {
				error = zlib_reader_read(&reader, dst_data, dst_size);
			}
#else /* CONFIG_HAVE_KERNEL_DEBUGGER */
			error = zlib_reader_read(&reader, dst_data, dst_size);
#endif /* !CONFIG_HAVE_KERNEL_DEBUGGER */
			zlib_reader_fini(&reader);
			if unlikely(error < 0)
				THROW(E_INVALID_ARGUMENT);

			/* clear all trailing data that could not be read. */
			if (dst_size > (size_t)error) {
				bzero((byte_t *)dst_data + (size_t)error,
				      dst_size - error);
			}
		} EXCEPT {
			mman_unmap_kram(dst_data, dst_size);
			RETHROW();
		}
	}
	ATOMIC_WRITE(self->ums_inflsize, dst_size);
	ATOMIC_CMPXCH(self->ums_infladdr, (KERNEL byte_t *)-1, dst_data);
	*psize = dst_size;
	return dst_data;
}

/* UserELF module operators */
DEFINE_PUBLIC_ALIAS(_userelf_module_free, uem_free); /* Needed by `moddbx' to identify UserELF modules! */
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
		sect = (struct userelf_module_section *)SLIST_FIRST(&me->_um_deadsect);
		SLIST_REMOVE_HEAD(&me->_um_deadsect, _ms_dead);
		uems_destroy((struct userelf_module_section *)sect);
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
		if unlikely(!LIST_ISBOUND(sect, ms_cache)) {
			decref_unlikely(sect);
			continue; /* Section isn't apart of the cache... */
		}
		LIST_UNBIND(sect, ms_cache);
		decref_nokill(sect); /* The reference from the section cache. */

		/* Drop the reference we got from `awref_get()'
		 * If this ends up destroying the section, then enqueue said
		 * destruction to be performed  as part of the  post-lockop. */
		if (ATOMIC_DECFETCH(sect->ms_refcnt) == 0)
			SLIST_INSERT(&me->_um_deadsect, sect, _ms_dead);
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
	kfree(UM_any(self->um_phdrs));
	kfree(UM_any(self->um_shdrs));
	kfree(self->um_shstrtab);

	/* Remove all of the UserELF module's sections from the global sections cache. */
	while (self->um_shnum) {
		REF struct userelf_module_section *sect;
		--self->um_shnum;
		sect = awref_get(&self->um_sections[self->um_shnum]);
		if (!sect)
			continue; /* Section was never allocated or is dead. */
		if unlikely(!LIST_ISBOUND(sect, ms_cache)) {
			decref_unlikely(sect);
			continue; /* Section isn't apart of the cache... */
		}

		/* Must remove this section from the cache. */
		if (module_section_cache_tryacquire()) {
			if likely(LIST_ISBOUND(sect, ms_cache)) {
				LIST_UNBIND(sect, ms_cache);
				decref_nokill(sect);
			}
			_module_section_cache_release();
			decref_likely(sect);
			module_section_cache_reap();
		} else {
			/* Must use a lockop to unbind the section
			 * once the cache lock becomes  available.
			 *
			 * For this purpose,  we (re-)use the  original
			 * UserELF module object as a storage container
			 * for the lockop  descriptor that's then  used
			 * to  remove all of the module's sections from
			 * the module section cache. */
			++self->um_shnum; /* Must do the last section once again! */
			self->_um_sc_lop.lo_func = &uem_unbind_sections_and_destroy_lop;
			SLIST_ATOMIC_INSERT(&module_section_cache_lops, &self->_um_sc_lop, lo_link);
			decref_unlikely(sect);
			_module_section_cache_reap();
			return;
		}
	}

	module_clear_mnode_pointers_and_destroy(self);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL uem_nonodes_cleanup_postlop)(Tobpostlockop(mman) *__restrict self,
                                           struct mman *__restrict UNUSED(mm)) {
	struct userelf_module *me;
	me = container_of(self, struct userelf_module, _um_cc_postlop);
	assert(wasdestroyed(me));
	assert(me->md_ops == &uem_ops);
	uem_destroy(me);
}

PRIVATE NOBLOCK NONNULL((1)) Tobpostlockop(mman) *
NOTHROW(FCALL uem_nonodes_cleanup_lop)(Toblockop(mman) *__restrict self,
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
	result->ms_refcnt    = 2; /* +1:return, +1:module_section_cache */
	result->ms_ops       = &uems_ops;
	result->ms_module    = weakincref(self);
	result->ms_size      = UM_field(self, *shdr, .sh_size);
	result->ms_entsize   = UM_field(self, *shdr, .sh_entsize);
	result->ms_type      = UM_field(self, *shdr, .sh_type);
	result->ms_flags     = UM_field(self, *shdr, .sh_flags);
	result->ms_link      = UM_field(self, *shdr, .sh_link);
	result->ms_info      = UM_field(self, *shdr, .sh_info);
	result->ums_shdr     = shdr;
	result->ums_useraddr = (USER CHECKED byte_t *)-1;
	result->ums_kernaddr = (KERNEL byte_t *)-1;
	result->ums_infladdr = (KERNEL byte_t *)-1;
	result->ums_inflsize = 0;
	if (result->ms_flags & SHF_ALLOC) {
		/* Set the user-space load-address for allocated sections. */
		result->ums_useraddr = (USER CHECKED byte_t *)(self->md_loadaddr +
		                                               UM_field(self, *shdr, .sh_addr));
	}

	/* Acquire a lock to the module section cache. */
	TRY {
		module_section_cache_acquire();
	} EXCEPT {
		destroy(result);
		RETHROW();
	}

	/* Replace a previously destroyed section object with the new section! */
	if (!awref_replacedead(&self->um_sections[section_index], result)) {
		module_section_cache_release();
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
	LIST_INSERT_HEAD(&module_section_cache, result, ms_cache);

	/* Release the lock from the module section cache. */
	module_section_cache_release();

	return result;
}


INTERN BLOCKING WUNUSED NONNULL((1)) REF struct userelf_module_section *FCALL
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


INTERN BLOCKING WUNUSED NONNULL((1)) REF struct userelf_module_section *FCALL
uem_locksection_index(struct userelf_module *__restrict self,
                      unsigned int section_index) {
	UM_ElfW_ShdrP shdrs;
	if unlikely(section_index >= self->um_shnum)
		return NULL;
	shdrs = uem_shdrs(self);
	if unlikely(!UM_any(shdrs))
		return NULL;
	return uem_locksection_index_impl(self, (UM_ElfW_Shdr *)UM_field_ptr(self, shdrs, [section_index]),
	                                  (uint16_t)section_index);
}

INTERN BLOCKING WUNUSED NONNULL((1, 3)) bool FCALL
uem_sectinfo(struct userelf_module *__restrict self,
             uintptr_t module_relative_addr,
             struct module_sectinfo *__restrict info) {
	uint16_t i;
	UM_ElfW_ShdrP shdrs;
	bool allow_section_end_pointers;
	allow_section_end_pointers = false;
	shdrs = uem_shdrs(self);
	if unlikely(!UM_any(shdrs))
		return false;
again:
	for (i = 0; i < self->um_shnum; ++i) {
		char *shstrtab;
		uintptr_t sh_addr, sh_size;
		uintptr_t sh_name;
		size_t shstrtab_siz;
		sh_addr = UM_field(self, shdrs, [i].sh_addr);
		sh_size = UM_field(self, shdrs, [i].sh_size);
		if (!(UM_field(self, shdrs, [i].sh_flags) & SHF_ALLOC))
			continue; /* Section isn't allocated, so this one can't be it. */
		if (module_relative_addr < sh_addr)
			continue;
		if (module_relative_addr >= sh_addr + sh_size) {
			if (!allow_section_end_pointers)
				continue;
			if (module_relative_addr > sh_addr + sh_size)
				continue;
		}

		/* Found it! (fill in section information for our caller) */
		info->msi_name    = NULL;
		info->msi_addr    = sh_addr;
		info->msi_size    = sh_size;
		info->msi_entsize = UM_field(self, shdrs, [i].sh_entsize);
		info->msi_type    = UM_field(self, shdrs, [i].sh_type);
		info->msi_flags   = UM_field(self, shdrs, [i].sh_flags);
		info->msi_link    = UM_field(self, shdrs, [i].sh_link);
		info->msi_info    = UM_field(self, shdrs, [i].sh_info);
		info->msi_index   = (unsigned int)i;
		if likely((shstrtab = uem_shstrtab(self)) != NULL) {
			shstrtab_siz = UM_field(self, shdrs, [self->um_shstrndx].sh_size);
			sh_name      = UM_field(self, shdrs, [i].sh_name);
			if likely(sh_name < shstrtab_siz) {
				info->msi_name = shstrtab + sh_name;
			}
		}
		return true;
	}
	if (!allow_section_end_pointers) {
		allow_section_end_pointers = true;
		goto again;
	}
	return false;
}



/************************************************************************/
/* UserELF Module creation                                              */
/************************************************************************/

LIST_HEAD(userelf_module_list, userelf_module);
SLIST_HEAD(userelf_module_slist, userelf_module);

/* [0..n][lock(mman::mm_lock)] Per-mman UserELF Module Cache */
PRIVATE ATTR_PERMMAN ATTR_ALIGN(struct REF userelf_module_list)
thismman_uemc = LIST_HEAD_INITIALIZER(thismman_uemc);


/* Clear the UEMC cache of the given mman when said mman is destroyed. */
DEFINE_PERMMAN_FINI(fini_thismman_uemc);
PRIVATE ATTR_USED NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fini_thismman_uemc)(struct mman *__restrict self) {
	while (!LIST_EMPTY(&FORMMAN(self, thismman_uemc))) {
		REF struct userelf_module *mod;
		mod = LIST_FIRST(&FORMMAN(self, thismman_uemc));
		LIST_UNBIND(mod, um_cache);
		decref_likely(mod);
	}
}

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
INTERN NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1, 2)) void
NOTHROW(FCALL system_cc_mman_module_cache)(struct mman *__restrict self,
                                           struct ccinfo *__restrict info) {
	struct userelf_module_slist dead;

	/* Try to acquire the lock because we may need to be NOBLOCK! */
	if (!mman_lock_tryacquire(self)) {
		if (ccinfo_noblock(info))
			return;
		if (!mman_lock_acquire_nx(self))
			return;
	}

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
	_mman_lock_release(self);

	/* Destroy all dead UserELF modules. */
	while (!SLIST_EMPTY(&dead)) {
		struct userelf_module *mod;
		mod = SLIST_FIRST(&dead);
		SLIST_REMOVE_HEAD(&dead, _um_dead);
		ccinfo_account(info, sizeof(struct userelf_module));
		uem_destroy(mod);
	}

	/* Reap lock operations relatively late! */
	mman_lockops_reap(self);
}

/* Special return values for `uem_trycreate()' */
#define UEM_TRYCREATE_UNLOCKED       ((REF struct userelf_module *)-1)
#define UEM_TRYCREATE_UNLOCKED_NOUEM ((REF struct userelf_module *)-2)

/* Same as `UEM_TRYCREATE_UNLOCKED', but must call `mman_mergenodes()' if nothing can be bound. */
#define UEM_TRYCREATE_UNLOCKED_MERGE ((REF struct userelf_module *)-3)



/* Try to create  a UserELF  module based on  the knowledge  that
 * the given mman `self' has a mapping for `file' at `node_addr',
 * with an in-file offset of `node_fpos'.
 *
 * Check if `file' is an ELF module that can be mapped such that
 * the given addr<==>file relation might be correct, and if  so,
 * also  check that other mappings that should exist as a result
 * of  such a memory mapping being created, are present as well.
 * If all of this checks out, create the new UserELF module, and
 * bind it to all of the mem-nodes that were created as a result
 * of the UserELF module.
 *
 * If it turns out that `file' isn't an ELF module, or that the
 * given  addr<==>file relation is impossible for that specific
 * ELF module, return `UEM_TRYCREATE_UNLOCKED_NOUEM'
 *
 * If  the given  `file' is an  ELF module that  can sustain the
 * given addr<==>file relation, but after the lock to `self' was
 * re-acquired, it is found that  the mapping at `node_addr'  no
 * longer matches a  file-mapping of `file'  with the  specified
 * offset,  the lock to  `self' is released  once again, and the
 * function  returns  `UEM_TRYCREATE_UNLOCKED' to  indicate that
 * the call must be repeated after arguments were  re-generated.
 *
 * This function is called without any locks held, and also
 * always returns without any locks held. */
PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) REF struct userelf_module *FCALL
uem_create_from_mapping(struct mman *__restrict self,
                        struct mfile *__restrict file,
                        USER CHECKED byte_t *node_addr,
                        pos_t node_fpos) {
	/* NOTE: Since the addr<==>file values were loaded from mem-nodes,
	 *       we can assume  that they're always  properly aligned,  as
	 *       it's impossible  for file  mappings to  be created,  such
	 *       that the PAGEMASK'd  part of the  addr/fpos don't  match. */
	REF struct userelf_module *result;
	pos_t file_size, phoff, shoff;
	UM_ElfW_Ehdr ehdr;
	uint16_t phnum, shnum;
	UM_ElfW_PhdrP phdrv;
	size_t phsize, shsize;
#ifdef _MODULE_HAVE_SIZEOF_POINTER
	byte_t sizeof_pointer = sizeof(void *);
#endif /* _MODULE_HAVE_SIZEOF_POINTER */

	/* First step: Load what we hope will be the Elf_Ehdr */
	if (mfile_read(file, &ehdr, sizeof(ehdr), 0) < sizeof(ehdr))
		goto not_an_elf_file;

	/* Verify that this is a valid EHDR. */
	if (UM_any(ehdr).e_ident[EI_MAG0] != ELFMAG0)
		goto not_an_elf_file;
	if (UM_any(ehdr).e_ident[EI_MAG1] != ELFMAG1)
		goto not_an_elf_file;
	if (UM_any(ehdr).e_ident[EI_MAG2] != ELFMAG2)
		goto not_an_elf_file;
	if (UM_any(ehdr).e_ident[EI_MAG3] != ELFMAG3)
		goto not_an_elf_file;
	if (UM_any(ehdr).e_ident[EI_VERSION] != EV_CURRENT)
		goto not_an_elf_file;
#if !defined(__ARCH_HAVE_COMPAT) || COMPAT_ELF_ARCH_CLASS == ELF_ARCH_CLASS
	if (UM_any(ehdr).e_ident[EI_CLASS] != ELF_ARCH_CLASS)
		goto not_an_elf_file;
#endif /* !__ARCH_HAVE_COMPAT || COMPAT_ELF_ARCH_CLASS == ELF_ARCH_CLASS */
#if !defined(__ARCH_HAVE_COMPAT) || COMPAT_ELF_ARCH_DATA == ELF_ARCH_DATA
	if (UM_any(ehdr).e_ident[EI_DATA] != ELF_ARCH_DATA)
		goto not_an_elf_file;
#endif /* !__ARCH_HAVE_COMPAT || COMPAT_ELF_ARCH_DATA == ELF_ARCH_DATA */
	if (UM_any(ehdr).e_machine != ELF_ARCH_MACHINE) {
#ifdef __ARCH_HAVE_COMPAT
		/* Check for compatibility-mode support... */
		if (UM_any(ehdr).e_machine != COMPAT_ELF_ARCH_MACHINE)
			goto not_an_elf_file;
#if COMPAT_ELF_ARCH_CLASS != ELF_ARCH_CLASS
		if (UM_any(ehdr).e_ident[EI_CLASS] != COMPAT_ELF_ARCH_CLASS)
			goto not_an_elf_file;
#endif /* COMPAT_ELF_ARCH_CLASS != ELF_ARCH_CLASS */
#if COMPAT_ELF_ARCH_DATA != ELF_ARCH_DATA
		if (UM_any(ehdr).e_ident[EI_DATA] != COMPAT_ELF_ARCH_DATA)
			goto not_an_elf_file;
#endif /* COMPAT_ELF_ARCH_DATA != ELF_ARCH_DATA */
#ifdef _MODULE_HAVE_SIZEOF_POINTER
		sizeof_pointer = __ARCH_COMPAT_SIZEOF_POINTER;
#endif /* _MODULE_HAVE_SIZEOF_POINTER */
#else /* __ARCH_HAVE_COMPAT */
		goto not_an_elf_file;
#endif /* !__ARCH_HAVE_COMPAT */
	} else {
#if defined(__ARCH_HAVE_COMPAT) && COMPAT_ELF_ARCH_CLASS != ELF_ARCH_CLASS
		if (UM_any(ehdr).e_ident[EI_CLASS] != ELF_ARCH_CLASS)
			goto not_an_elf_file;
#endif /* __ARCH_HAVE_COMPAT && COMPAT_ELF_ARCH_CLASS != ELF_ARCH_CLASS */
#if defined(__ARCH_HAVE_COMPAT) && COMPAT_ELF_ARCH_DATA != ELF_ARCH_DATA
		if (UM_any(ehdr).e_ident[EI_DATA] != ELF_ARCH_DATA)
			goto not_an_elf_file;
#endif /* __ARCH_HAVE_COMPAT && COMPAT_ELF_ARCH_DATA != ELF_ARCH_DATA */
	}

	/* We only accept executable, and .so files as UserELF modules. */
	if (UM_field_r(sizeof_pointer, ehdr, .e_type) != ET_EXEC &&
	    UM_field_r(sizeof_pointer, ehdr, .e_type) != ET_DYN)
		goto not_an_elf_file;

	/* Verify integrity of the ELF Ehdr */
	if (UM_field_r(sizeof_pointer, ehdr, .e_phentsize) != UM_sizeof_r(sizeof_pointer, UM_ElfW_Phdr))
		goto not_an_elf_file;
	if (UM_field_r(sizeof_pointer, ehdr, .e_shentsize) != UM_sizeof_r(sizeof_pointer, UM_ElfW_Shdr))
		goto not_an_elf_file;

	file_size = mfile_getsize(file);

	/* Validate section indices/offsets */
	shnum = UM_field_r(sizeof_pointer, ehdr, .e_shnum);
	if (shnum > ELF_ARCH_MAXSHCOUNT)
		goto not_an_elf_file;
	if (UM_field_r(sizeof_pointer, ehdr, .e_shstrndx) >= shnum)
		goto not_an_elf_file;
	shoff  = (pos_t)UM_field_r(sizeof_pointer, ehdr, .e_shoff);
	shsize = UM_sizeof_r(sizeof_pointer, UM_ElfW_Shdr) * shnum;
	{
		pos_t shend;
		if (OVERFLOW_UADD(shoff, shsize, &shend) || shend > file_size)
			goto not_an_elf_file;
	}

	/* Validate/decode program header indices/offsets */
	phnum = UM_field_r(sizeof_pointer, ehdr, .e_phnum);
	if (phnum > ELF_ARCH_MAXPHCOUNT)
		goto not_an_elf_file; /* Must still limit the max # of program headers! */
	phoff  = (pos_t)UM_field_r(sizeof_pointer, ehdr, .e_phoff);
	phsize = UM_sizeof_r(sizeof_pointer, UM_ElfW_Phdr) * phnum;
	{
		pos_t phend;
		if (OVERFLOW_UADD(phoff, phsize, &phend) || phend > file_size)
			goto not_an_elf_file;
	}

	/* Allocate+load the Elf program header vector! */
	UM_any(phdrv) = (typeof(UM_any(phdrv)))kmalloc(phsize, GFP_NORMAL);
	TRY {
		if (mfile_read(file, UM_any(phdrv), phsize, phoff) < phsize)
			goto not_an_elf_file_phdrv;
	} EXCEPT {
		kfree(UM_any(phdrv));
		RETHROW();
	}
	TRY {
		uint16_t i;
		uintptr_t loadaddr;
		bool must_split_phdr_nodes;

		/* Validate that all program headers look like OK Elf_Phdr items! */
		for (i = 0; i < phnum; ++i) {
			if (UM_field_r(sizeof_pointer, phdrv, [i].p_type) != PT_LOAD)
				continue; /* Allow anything for non-load headers! */
			if (UM_field_r(sizeof_pointer, phdrv, [i].p_flags) & ~(PF_X | PF_W | PF_R))
				goto not_an_elf_file_phdrv;
			if ((UM_field_r(sizeof_pointer, phdrv, [i].p_offset) & PAGEMASK) !=
			    (UM_field_r(sizeof_pointer, phdrv, [i].p_vaddr) & PAGEMASK))
				goto not_an_elf_file_phdrv;
		}

		/* Find the program header that contains `node_fpos' */
		for (i = 0;; ++i) {
			size_t aligned_phdr_file_size, aligned_phdr_file_shift;
			pos_t aligned_phdr_file_pos, aligned_phdr_file_end;
			if (i >= phnum)
				goto not_an_elf_file_phdrv;
			if (UM_field_r(sizeof_pointer, phdrv, [i].p_type) != PT_LOAD)
				continue; /* Must be a load-header! */
			aligned_phdr_file_pos   = (pos_t)UM_field_r(sizeof_pointer, phdrv, [i].p_offset);
			aligned_phdr_file_size  = UM_field_r(sizeof_pointer, phdrv, [i].p_filesz);
			aligned_phdr_file_shift = (size_t)(aligned_phdr_file_pos & (PAGESIZE - 1));
			aligned_phdr_file_size += aligned_phdr_file_shift;
			aligned_phdr_file_pos -= aligned_phdr_file_shift;
			if (node_fpos < aligned_phdr_file_pos)
				continue;
			if (OVERFLOW_UADD(aligned_phdr_file_pos, aligned_phdr_file_size, &aligned_phdr_file_end))
				goto not_an_elf_file_phdrv;
			if (node_fpos < aligned_phdr_file_end) {
				/* All right! We've found the program header that (supposedly)  was
				 * used to map the node who's origin our caller wants us to verify.
				 *
				 * Assuming that the mapping is legit, we can use this information
				 * to  determine the load-offset (i.e. the ASLR key) that was used
				 * when the module was mapped, and that is needed to locate  other
				 * nodes that would also belong to this module. */
				USER byte_t *segment_address;
				uintptr_t offset_in_segment;
				offset_in_segment = (uintptr_t)(node_fpos - aligned_phdr_file_pos);
				segment_address   = node_addr - offset_in_segment;
				/* Calculate the effective module load address. */
				loadaddr = (uintptr_t)segment_address - (UM_field_r(sizeof_pointer, phdrv, [i].p_vaddr) -
				                                         aligned_phdr_file_shift);
				break;
			}
		}

		/* At this point, we can be fairly certain that we've found a
		 * proper UserELF module, meaning that we should move forward
		 * by actually creating its descriptor! */
		result = (REF struct userelf_module *)kmalloc(offsetof(struct userelf_module, um_sections) +
		                                              (shnum * sizeof(struct uems_awref)),
		                                              GFP_CALLOC);
		_userelf_module_init_arch(result);
		result->um_shoff      = shoff;
		result->um_phnum      = phnum;
		result->um_shnum      = shnum;
		result->um_shstrndx   = UM_field_r(sizeof_pointer, ehdr, .e_shstrndx);
		result->um_phdrs      = phdrv;       /* Inherited on success */
/*		UM_any(result->um_shdrs) = NULL;*/   /* Already done by GFP_CALLOC */
/*		result->um_shstrtab   = NULL;*/      /* Already done by GFP_CALLOC */
		result->md_refcnt     = 2;           /* +1: return, +1: thismman_uemc */
		result->md_weakrefcnt = 1;
/*		result->md_nodecount  = 0;*/         /* Already done by GFP_CALLOC; Incremented later! */
		result->md_ops        = &uem_ops;
		result->md_loadaddr   = loadaddr;
		result->md_loadmin    = (byte_t *)-1;
/*		result->md_loadmax    = (void *)0;*/ /* Already done by GFP_CALLOC */
/*		result->md_fspath     = NULL;*/      /* Already done by GFP_CALLOC */
/*		result->md_fsname     = NULL;*/      /* Already done by GFP_CALLOC */
#ifdef _MODULE_HAVE_SIZEOF_POINTER
		result->md_sizeof_pointer = sizeof_pointer;
#endif /* _MODULE_HAVE_SIZEOF_POINTER */

		/* Re-acquire a lock to the mman. */
		TRY {
			mman_lock_acquire(self);
		} EXCEPT {
			kfree(result);
			RETHROW();
		}

		/* Verify that the `node_addr<==>node_fpos' mapping is still a thing! */
		{
			struct mnode *node;
			struct mpart *part;
			pos_t real_node_fpos;
			node = mman_mappings_locate(self, node_addr);
			if unlikely(!node)
				goto not_an_elf_file_phdrv_result_mmlock;
			part = node->mn_part;
			if unlikely(!part) {
something_changed:
				mman_lock_release(self);
				kfree(result);
				kfree(UM_any(phdrv));
				return UEM_TRYCREATE_UNLOCKED;
			}
			if unlikely(ATOMIC_READ(part->mp_file) != file)
				goto something_changed;

			/* Calculate the current file-position mapped at `node_addr',
			 * and  make sure that it doesn't differ from what our caller
			 * has told us to base our assumption upon.
			 * NOTE: No need to lock `part',  because our lock to  `self'
			 *       also guaranties that the part's address change isn't
			 *       altered! */
			real_node_fpos = mnode_getfileaddrat(node, node_addr);
			if unlikely(real_node_fpos != node_fpos)
				goto something_changed;
		}

		/* Verify that all PT_LOAD-segments of `result' are mapped correctly. */
		must_split_phdr_nodes = false;
		for (i = 0; i < phnum; ++i) {
			struct mnode *node;
			struct mnode_tree_minmax mima;
			byte_t *minaddr, *maxaddr;
			pos_t ph_fpos;
			uintptr_t ph_prot;
			if (UM_field_r(sizeof_pointer, phdrv, [i].p_type) != PT_LOAD)
				continue; /* Allow anything for non-load headers! */
			ph_prot = mnodeflags_from_elfpf(UM_field_r(sizeof_pointer, phdrv, [i].p_flags));
			ph_fpos = (pos_t)UM_field_r(sizeof_pointer, phdrv, [i].p_offset);
			minaddr = (byte_t *)UM_field_r(sizeof_pointer, phdrv, [i].p_vaddr) + loadaddr;
			maxaddr = (byte_t *)minaddr + UM_field_r(sizeof_pointer, phdrv, [i].p_memsz);
			if ((uintptr_t)minaddr & PAGEMASK) {
				/* Must also account for base-address shift within the header's file-offset. */
				if (OVERFLOW_USUB(ph_fpos, (uintptr_t)minaddr & PAGEMASK, &ph_fpos))
					goto not_an_elf_file_phdrv_result_mmlock;
				minaddr = (byte_t *)((uintptr_t)minaddr & ~PAGEMASK);
			}
			maxaddr = (byte_t *)CEIL_ALIGN((uintptr_t)maxaddr, PAGESIZE) - 1;
			if unlikely(minaddr >= maxaddr)
				goto not_an_elf_file_phdrv_result_mmlock;
			mnode_tree_minmaxlocate(self->mm_mappings, minaddr, maxaddr, &mima);
			if unlikely(!mima.mm_min)
				goto not_an_elf_file_phdrv_result_mmlock;
			if unlikely(minaddr < (byte_t *)mnode_getminaddr(mima.mm_min))
				goto not_an_elf_file_phdrv_result_mmlock;
			if unlikely(maxaddr > (byte_t *)mnode_getmaxaddr(mima.mm_max))
				goto not_an_elf_file_phdrv_result_mmlock;
			if unlikely(minaddr > (byte_t *)mnode_getminaddr(mima.mm_min) ||
			            maxaddr < (byte_t *)mnode_getmaxaddr(mima.mm_max))
				must_split_phdr_nodes = true;
			if (result->md_loadmin > minaddr)
				result->md_loadmin = minaddr;
			if (result->md_loadmax < maxaddr)
				result->md_loadmax = maxaddr;
			for (node = mima.mm_min;;) {
				struct mfile *node_file;

				/* Load filesystem name info, and make sure it's consistent
				 * across  all segments that actually offer filesystem name
				 * information. */
				if (!result->md_fspath && !result->md_fsname) {
					result->md_fspath = node->mn_fspath;
					result->md_fsname = node->mn_fsname;
				} else if (result->md_fspath != node->mn_fspath ||
				           result->md_fsname != node->mn_fsname) {
					if (node->mn_fspath || node->mn_fsname)
						goto not_an_elf_file_phdrv_result_mmlock;
				}

				/* Verify that the node's protection flags include at least all
				 * of the permissions required by the ELF Program header.  More
				 * permissions are allowed, in case of stuff like TEXTREL being
				 * handled at the moment, but less permissions aren't allowed. */
				if unlikely((node->mn_flags & ph_prot) != ph_prot)
					goto not_an_elf_file_phdrv_result_mmlock;

				/* This node must either be a file-mapping of `self' with the
				 * appropriate offset described by `phdrv[i]', or point at  a
				 * zero-initialized .bss-style file. */
				if unlikely(!node->mn_part)
					goto not_an_elf_file_phdrv_result_mmlock;
				node_file = ATOMIC_READ(node->mn_part->mp_file);
				if (node_file == file) {
					/* Verify file-offsets */
					pos_t expected_fpos, actual_fpos;
					expected_fpos = ph_fpos + (size_t)((byte_t *)mnode_getminaddr(node) - minaddr);
					actual_fpos   = mnode_getfileaddr(node);
					if (expected_fpos != actual_fpos)
						goto not_an_elf_file_phdrv_result_mmlock;
				} else if (mfile_isdevzero(node_file)) {
					/* Allow zero-memory for .bss-style mappings! */
				} else {
					/* Unexpected file mapping... (not a valid UserELF mapping!) */
					goto not_an_elf_file_phdrv_result_mmlock;
				}

				/* Deal with the case where another module is already bound to this address... */
				if unlikely(node->mn_module != NULL) {
					/* There's already another module that's mapped here...
					 *
					 * Simple case: If the module's already been destroyed,
					 *              just remove it manually! */
					if (wasdestroyed(node->mn_module)) {
set_node_nullptr:
						module_dec_nodecount(node->mn_module);
						node->mn_module = NULL;
					} else {
						/* Check  for race condition: another thread created
						 * the module that was requested before we got here.
						 *
						 * In  this case, use `node->mn_module' as result,
						 * but also check that it  can be found in all  of
						 * the places where we expect it to be located at. */
						if (node == mima.mm_min &&
						    node->mn_module->md_ops == &uem_ops &&
						    node->mn_module->md_loadaddr == result->md_loadaddr &&
						    node->mn_module->md_file == file &&
						    node->mn_module->md_nodecount != 0) {
							for (++i; i < phnum; ++i) {
								if (UM_field_r(sizeof_pointer, phdrv, [i].p_type) != PT_LOAD)
									continue; /* Allow anything for non-load headers! */
								minaddr = (byte_t *)UM_field_r(sizeof_pointer, phdrv, [i].p_vaddr) + loadaddr;
								maxaddr = (byte_t *)minaddr + UM_field_r(sizeof_pointer, phdrv, [i].p_memsz);
								minaddr = (byte_t *)FLOOR_ALIGN((uintptr_t)minaddr, PAGESIZE);
								maxaddr = (byte_t *)CEIL_ALIGN((uintptr_t)maxaddr, PAGESIZE) - 1;
								if unlikely(minaddr >= maxaddr)
									goto not_an_elf_file_phdrv_result_mmlock;
								if (result->md_loadmin > minaddr)
									result->md_loadmin = minaddr;
								if (result->md_loadmax < maxaddr)
									result->md_loadmax = maxaddr;
							}
							if (node->mn_module->md_loadmin == result->md_loadmin &&
							    node->mn_module->md_loadmax == result->md_loadmax) {
								/* Same module -> Re-use what was already registered! */
								REF struct userelf_module *new_result;
								new_result = (REF struct userelf_module *)node->mn_module;
								if (!tryincref(new_result))
									goto set_node_nullptr;
								mman_lock_release(self);
								kfree(result);
								kfree(UM_any(phdrv));
								return new_result;
							}
						}

						/* Complicated case: Something weird happened between
						 * us and a different variant of the same module. And
						 * considering that we're still dealing with the same
						 * underlying `mfile', better be safe than sorry, and
						 * simply go down the not-an-elf-file path... */
						goto not_an_elf_file_phdrv_result_mmlock;
					}
				}
				if (node == mima.mm_max)
					break;
				{
					void *endaddr;
					endaddr = mnode_getendaddr(node);
					node    = mnode_tree_nextnode(node);
					assert(node);
					if (mnode_getaddr(node) != endaddr)
						goto not_an_elf_file_phdrv_result_mmlock;
				}
			}
		}

		if (must_split_phdr_nodes) {
			for (i = 0; i < phnum; ++i) {
				struct mnode_tree_minmax mima;
				byte_t *minaddr, *maxaddr;
				if (UM_field_r(sizeof_pointer, phdrv, [i].p_type) != PT_LOAD)
					continue; /* Allow anything for non-load headers! */
				minaddr = (byte_t *)UM_field_r(sizeof_pointer, phdrv, [i].p_vaddr) + loadaddr;
				maxaddr = (byte_t *)minaddr + UM_field_r(sizeof_pointer, phdrv, [i].p_memsz);
				minaddr = (byte_t *)FLOOR_ALIGN((uintptr_t)minaddr, PAGESIZE);
				maxaddr = (byte_t *)CEIL_ALIGN((uintptr_t)maxaddr, PAGESIZE) - 1;
				assert(minaddr < maxaddr);
again_locate_minmax:
				mnode_tree_minmaxlocate(self->mm_mappings, minaddr, maxaddr, &mima);

				/* If necessary, split larger nodes at program header bounds. */
				TRY {
					if unlikely(minaddr > (byte_t *)mnode_getminaddr(mima.mm_min)) {
						if (!mnode_split_or_unlock(self, mima.mm_min, minaddr, NULL)) {
something_changed_merge:
							mman_lock_release(self);
							kfree(result);
							kfree(UM_any(phdrv));
							return UEM_TRYCREATE_UNLOCKED_MERGE;
						}
						goto again_locate_minmax;
					}
					if unlikely(maxaddr < (byte_t *)mnode_getmaxaddr(mima.mm_max)) {
						if (!mnode_split_or_unlock(self, mima.mm_max, maxaddr + 1, NULL))
							goto something_changed_merge;
						goto again_locate_minmax;
					}
				} EXCEPT {
					kfree(result);
					mman_mergenodes(self);
					RETHROW();
				}
			}
		}

		/* Add self-pointers for `result' to `self'. */
		for (i = 0; i < phnum; ++i) {
			struct mnode *node;
			struct mnode_tree_minmax mima;
			byte_t *minaddr, *maxaddr;
			if (UM_field_r(sizeof_pointer, phdrv, [i].p_type) != PT_LOAD)
				continue; /* Allow anything for non-load headers! */
			minaddr = (byte_t *)UM_field_r(sizeof_pointer, phdrv, [i].p_vaddr) + loadaddr;
			maxaddr = (byte_t *)minaddr + UM_field_r(sizeof_pointer, phdrv, [i].p_memsz);
			minaddr = (byte_t *)FLOOR_ALIGN((uintptr_t)minaddr, PAGESIZE);
			maxaddr = (byte_t *)CEIL_ALIGN((uintptr_t)maxaddr, PAGESIZE) - 1;
			assert(minaddr < maxaddr);
			mnode_tree_minmaxlocate(self->mm_mappings, minaddr, maxaddr, &mima);
			assert(minaddr == (byte_t *)mnode_getminaddr(mima.mm_min));
			assert(maxaddr == (byte_t *)mnode_getmaxaddr(mima.mm_max));
			assert(mima.mm_min);
			assert(result->md_loadmin <= minaddr);
			assert(result->md_loadmax >= maxaddr);
			for (node = mima.mm_min;;) {
				assert(!node->mn_module);

				/* Set the module self-pointer. */
				node->mn_module = result;
				++result->md_nodecount;

				if (node == mima.mm_max)
					break;
#ifdef NDEBUG
				node = mnode_tree_nextnode(node);
#else /* NDEBUG */
				{
					void *endaddr;
					endaddr = mnode_getendaddr(node);
					node    = mnode_tree_nextnode(node);
					assert(node);
					assertf(mnode_getaddr(node) == endaddr,
					        "mnode_getaddr(node) = %p\n"
					        "endaddr             = %p\n",
					        mnode_getaddr(node), endaddr);
				}
#endif /* !NDEBUG */
			}
		}
		if unlikely(result->md_nodecount == 0)
			goto not_an_elf_file_phdrv_result_mmlock_mergenodes; /* _really_ shouldn't happen... */

		/* Add `result' to the cache of `self'.
		 * NOTE: The reference inherited here was accounted for by the init of `md_refcnt'! */
		LIST_INSERT_HEAD(&FORMMAN(self, thismman_uemc), result, um_cache);

		/* Fill in remaining fields of `result' */
		xincref(result->md_fspath);
		xincref(result->md_fsname);
		result->md_mman = weakincref(self);
		result->md_file = incref(file);
		mman_mergenodes_inrange(self, result->md_loadmin, result->md_loadmax);
		mman_lock_release(self);
	} EXCEPT {
		kfree(UM_any(phdrv));
		RETHROW();
	}
	/*kfree(UM_any(phdrv));*/ /* In this case, inherited by `result' */
	return result;
not_an_elf_file_phdrv_result_mmlock_mergenodes:
	mman_mergenodes_locked(self);
not_an_elf_file_phdrv_result_mmlock:
	mman_lock_release(self);
/*not_an_elf_file_phdrv_result:*/
	kfree(result);
not_an_elf_file_phdrv:
	kfree(UM_any(phdrv));
not_an_elf_file:
	return UEM_TRYCREATE_UNLOCKED_NOUEM;
}


#ifndef __mfile_axref_defined
#define __mfile_axref_defined
AXREF(mfile_axref, mfile);
#endif /* !__mfile_axref_defined */



/* Open the filesystem location for the given `rtld_fsfile' */
PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) REF struct mfile *FCALL
open_system_rtld_fsfile(struct mfile_axref *__restrict rtld_fsfile,
                        struct fdirent *__restrict rtld_name) {
	REF struct mfile *result;
again:
	result = axref_get(rtld_fsfile);
	if (!result && !kernel_poisoned()) {
		TRY {
			REF struct path *root;
			u32 remaining_symlinks;
			vfs_rootlock_read(&vfs_kernel);
			root = incref(vfs_kernel.vf_root);
			vfs_rootlock_endread(&vfs_kernel);
			FINALLY_DECREF_UNLIKELY(root);
			remaining_symlinks = SYMLOOP_MAX;

			/* Open the libdl file. (+1 because we want to be relative to the root) */
			result = path_traversefull_ex(root, &remaining_symlinks, rtld_name->fd_name + 1);
			if unlikely(!mfile_hasrawio(result)) {
				decref_unlikely(result);
				THROW(E_FSERROR);
			}

			/* Try to cache the resulting file object. */
			if (!axref_cmpxch(rtld_fsfile, NULL, result)) {
				decref_likely(result);
				goto again;
			}
		} EXCEPT {
			if (!was_thrown(E_FSERROR))
				RETHROW();
			result = NULL;
		}
	}
	return result;
}


#define RTLD_PHDR_COUNT 4 /* The RTLD has exactly 4 program headers! (s.a. `_rtld.ld') */

/* Same as `uem_create_from_mapping()', but used for special
 * handling  concerning  the (or  "a") system  RTLD library. */
PRIVATE BLOCKING WUNUSED NONNULL((1, 2, 3, 4)) REF struct userelf_module *FCALL
uem_create_system_rtld(struct mman *__restrict self,
                       struct mfile *__restrict rtld_file,
                       struct mfile_axref *__restrict rtld_fsfile,
                       struct fdirent *__restrict rtld_name,
                       USER CHECKED byte_t *node_addr, pos_t node_fpos) {
	REF struct userelf_module *result;
	REF struct mfile *file;
	UM_ElfW_ShdrP shdrs;
#if (defined(_MODULE_HAVE_SIZEOF_POINTER) && \
    COMPAT_ELF_ARCH_CLASS != ELF_ARCH_CLASS)
	union {
		Elf32_Phdr _32[RTLD_PHDR_COUNT];
		Elf64_Phdr _64[RTLD_PHDR_COUNT];
	} phdrv;
#else /* ... */
	ElfW(Phdr) phdrv[RTLD_PHDR_COUNT];
#endif /* !... */
	UM_ElfW_Ehdr ehdr;
	size_t loadsize;
	uint16_t shnum;
	pos_t shoff, file_size;
	uintptr_t loadaddr;
#ifdef _MODULE_HAVE_SIZEOF_POINTER
	byte_t sizeof_pointer = sizeof(void *);
#endif /* _MODULE_HAVE_SIZEOF_POINTER */
	file = open_system_rtld_fsfile(rtld_fsfile, rtld_name);
	if unlikely(!file)
		return UEM_TRYCREATE_UNLOCKED_NOUEM;
	TRY {

		/* First step: Load what we hope will be the Elf_Ehdr */
		if (mfile_read(file, &ehdr, sizeof(ehdr), 0) < sizeof(ehdr))
			goto not_an_elf_file;

		/* Verify that this is a valid EHDR. */
		if (UM_any(ehdr).e_ident[EI_MAG0] != ELFMAG0)
			goto not_an_elf_file;
		if (UM_any(ehdr).e_ident[EI_MAG1] != ELFMAG1)
			goto not_an_elf_file;
		if (UM_any(ehdr).e_ident[EI_MAG2] != ELFMAG2)
			goto not_an_elf_file;
		if (UM_any(ehdr).e_ident[EI_MAG3] != ELFMAG3)
			goto not_an_elf_file;
		if (UM_any(ehdr).e_ident[EI_VERSION] != EV_CURRENT)
			goto not_an_elf_file;
#ifdef __ARCH_HAVE_COMPAT
		if (rtld_file == &compat_execabi_system_rtld_file.mrf_file) {
			if (UM_any(ehdr).e_ident[EI_CLASS] != COMPAT_ELF_ARCH_CLASS)
				goto not_an_elf_file;
			if (UM_any(ehdr).e_ident[EI_DATA] != COMPAT_ELF_ARCH_DATA)
				goto not_an_elf_file;
			if (UM_any(ehdr).e_machine != COMPAT_ELF_ARCH_MACHINE)
				goto not_an_elf_file;
#ifdef _MODULE_HAVE_SIZEOF_POINTER
			sizeof_pointer = __ARCH_COMPAT_SIZEOF_POINTER;
#endif /* _MODULE_HAVE_SIZEOF_POINTER */
		} else
#endif /* __ARCH_HAVE_COMPAT */
		{
			if (UM_any(ehdr).e_ident[EI_CLASS] != ELF_ARCH_CLASS)
				goto not_an_elf_file;
			if (UM_any(ehdr).e_ident[EI_DATA] != ELF_ARCH_DATA)
				goto not_an_elf_file;
			if (UM_any(ehdr).e_machine != ELF_ARCH_MACHINE)
				goto not_an_elf_file;
		}
		if (UM_field_r(sizeof_pointer, ehdr, .e_type) != ET_DYN)
			goto not_an_elf_file;
		if (UM_field_r(sizeof_pointer, ehdr, .e_phentsize) != UM_sizeof_r(sizeof_pointer, UM_ElfW_Phdr))
			goto not_an_elf_file;
		if (UM_field_r(sizeof_pointer, ehdr, .e_shentsize) != UM_sizeof_r(sizeof_pointer, UM_ElfW_Shdr))
			goto not_an_elf_file;
		if (UM_field_r(sizeof_pointer, ehdr, .e_phnum) != RTLD_PHDR_COUNT)
			goto not_an_elf_file;

		file_size = mfile_getsize(file);

		/* Validate section indices/offsets */
		shnum = UM_field_r(sizeof_pointer, ehdr, .e_shnum);
		if (shnum > ELF_ARCH_MAXSHCOUNT)
			goto not_an_elf_file;
		if (UM_field_r(sizeof_pointer, ehdr, .e_shstrndx) >= shnum)
			goto not_an_elf_file;
		{
			size_t phsize;
			pos_t phoff, phend;
			phoff  = (pos_t)UM_field_r(sizeof_pointer, ehdr, .e_phoff);
			phsize = UM_sizeof_r(sizeof_pointer, UM_ElfW_Phdr) * RTLD_PHDR_COUNT;
			if (OVERFLOW_UADD(phoff, phsize, &phend) || phend > file_size)
				goto not_an_elf_file;

			/* Allocate+load the Elf program header vector! */
			if (mfile_read(file, UM_any(phdrv), phsize, phoff) < phsize)
				goto not_an_elf_file;
		}

		/* Validate that the program headers are consistent! */
		if (UM_field_r(sizeof_pointer, phdrv, [0].p_type) != PT_LOAD)
			goto not_an_elf_file;
		if (UM_field_r(sizeof_pointer, phdrv, [1].p_type) != PT_LOAD)
			goto not_an_elf_file;

		/* Only the first 2 program  headers are actually loaded into  memory.
		 * S.a. `options[OPT_ELF_FLATTEN_ALLOWED_HEADERS]' in `libdl/.sources' */
		if (UM_field_r(sizeof_pointer, phdrv, [0].p_vaddr) != 0)
			goto not_an_elf_file;
		if (UM_field_r(sizeof_pointer, phdrv, [1].p_vaddr) < UM_field_r(sizeof_pointer, phdrv, [0].p_memsz))
			goto not_an_elf_file;
		loadsize = UM_field_r(sizeof_pointer, phdrv, [1].p_vaddr) +
		           UM_field_r(sizeof_pointer, phdrv, [1].p_memsz);

		/* Calculate the  load-size, which  is  the upper  limit  for
		 * sections who's SHF_ALLOC flags may be considered as valid. */
		loadsize = CEIL_ALIGN(loadsize, PAGESIZE);

		/* Because the first program header has a base-address at `0',
		 * we  can easily  deduce the  the `loadaddr'  as the accessed
		 * node address  minus  the  offset  into  the  flattened  ELF
		 * binary that was mapped by the kernel! */
		loadaddr = (uintptr_t)node_addr - (uintptr_t)node_fpos;

		/* Load section headers, so we can fix-up SHF_ALLOC for
		 * sections that  aren't actually  mapped into  memory! */
		{
			pos_t shend;
			size_t shsize;
			shoff  = (pos_t)UM_field_r(sizeof_pointer, ehdr, .e_shoff);
			shsize = UM_sizeof_r(sizeof_pointer, UM_ElfW_Shdr) * shnum;
			if (OVERFLOW_UADD(shoff, shsize, &shend) || shend > file_size)
				goto not_an_elf_file;
			UM_any(shdrs) = (typeof(UM_any(shdrs)))kmalloc(shsize, GFP_PREFLT);
			TRY {
				mfile_readall(file, UM_any(shdrs), shsize, shoff);
			} EXCEPT {
				kfree(UM_any(shdrs));
				RETHROW();
			}
		}
		{
			uint16_t i;
			/* Fix-up section headers. */
			for (i = 0; i < shnum; ++i) {
				uintptr_t loadend;
				if (!(UM_field_r(sizeof_pointer, shdrs, [i].sh_flags) & SHF_ALLOC))
					continue;
				if (OVERFLOW_UADD(UM_field_r(sizeof_pointer, shdrs, [i].sh_addr),
				                  UM_field_r(sizeof_pointer, shdrs, [i].sh_size),
				                  &loadend))
					loadend = (uintptr_t)-1;
				if (loadend >= loadsize) {
#if (defined(_MODULE_HAVE_SIZEOF_POINTER) && \
     COMPAT_ELF_ARCH_CLASS != ELF_ARCH_CLASS)
					if (sizeof_pointer == 4) {
						shdrs._32[i].sh_flags &= ~SHF_ALLOC;
					} else {
						shdrs._64[i].sh_flags &= ~SHF_ALLOC;
					}
#else /* ... */
					shdrs[i].sh_flags &= ~SHF_ALLOC;
#endif /* !... */
				}
			}
		}
		TRY {
			/* Construct the actual UserELF module descriptor. */
			result = (REF struct userelf_module *)kmalloc(offsetof(struct userelf_module, um_sections) +
			                                              (shnum * sizeof(struct uems_awref)),
			                                              GFP_CALLOC);
			TRY {
				UM_any(result->um_phdrs) = (typeof(UM_any(result->um_phdrs)))kmalloc(RTLD_PHDR_COUNT *
				                                                                     UM_sizeof_r(sizeof_pointer, UM_ElfW_Phdr),
				                                                                     GFP_NORMAL);
			} EXCEPT {
				kfree(result);
				RETHROW();
			}

			/* Copy program header information. */
			memcpy(UM_any(result->um_phdrs), UM_any(phdrv), RTLD_PHDR_COUNT,
			       UM_sizeof_r(sizeof_pointer, UM_ElfW_Phdr));
			_userelf_module_init_arch(result);
			result->um_phnum      = RTLD_PHDR_COUNT;
			result->um_shoff      = shoff;
			result->um_shnum      = shnum;
			result->um_shstrndx   = UM_field_r(sizeof_pointer, ehdr, .e_shstrndx);
			result->um_shdrs      = shdrs;
			result->md_refcnt     = 2; /* +1: return, +1: thismman_uemc */
			result->md_weakrefcnt = 1;
			result->md_ops        = &uem_ops;
			result->md_loadaddr   = loadaddr;
			result->md_loadmin    = (byte_t *)loadaddr;
			result->md_loadmax    = (byte_t *)loadaddr + loadsize - 1;
#ifdef _MODULE_HAVE_SIZEOF_POINTER
			result->md_sizeof_pointer = sizeof_pointer;
#endif /* _MODULE_HAVE_SIZEOF_POINTER */

			/* Re-acquire a lock to the mman. */
			TRY {
				mman_lock_acquire(self);
			} EXCEPT {
				kfree(UM_any(result->um_phdrs));
				kfree(result);
				RETHROW();
			}

			/* Make sure that the mapping at `node_addr' hasn't changed! */
			{
				struct mnode *node;
				struct mpart *part;
				pos_t real_node_fpos;
				node = mman_mappings_locate(self, node_addr);
				if unlikely(!node)
					goto not_an_elf_file_shdrs_result_mmlock;
				part = node->mn_part;
				if unlikely(!part) {
something_changed:
					mman_lock_release(self);
					kfree(UM_any(result->um_phdrs));
					kfree(result);
					kfree(UM_any(shdrs));
					decref_unlikely(file);
					return UEM_TRYCREATE_UNLOCKED;
				}
				if unlikely(ATOMIC_READ(part->mp_file) != rtld_file)
					goto something_changed;
				real_node_fpos = mnode_getfileaddrat(node, node_addr);
				if unlikely(real_node_fpos != node_fpos)
					goto something_changed;
			}

			/* Go over all nodes within `loadaddr...+=loadsize' and assign
			 * the newly created UserELF module as the associated  module. */
			{
				struct mnode *node;
				struct mnode_tree_minmax mima;
				mman_mappings_minmaxlocate(self, result->md_loadmin,
				                           result->md_loadmax, &mima);
				if likely(mima.mm_min != NULL) {
					/* Check if there is already a module mapping here... */
					for (node = mima.mm_min;;) {
						if unlikely(node->mn_module != NULL) {
							if (wasdestroyed(node->mn_module)) {
set_node_nullptr:
								module_dec_nodecount(node->mn_module);
								node->mn_module = NULL;
							} else if (node == mima.mm_min &&
							           node->mn_module->md_fspath == NULL &&
							           node->mn_module->md_fsname == rtld_name) {
								/* Another instance of the RTLD mapping.
								 * -> If it covers the entirety of our own one's
								 *    address  range, then someone else was just
								 *    faster than us.
								 *    Otherwise, something went wrong... */
								REF struct userelf_module *new_result;
								new_result = (REF struct userelf_module *)node->mn_module;
								while (node != mima.mm_max) {
									node = mnode_tree_nextnode(node);
									assert(node);
									if (node->mn_module != new_result)
										goto not_an_elf_file_shdrs_result_mmlock;
								}
								if (!tryincref(new_result))
									goto set_node_nullptr;
								mman_lock_release(self);
								kfree(UM_any(result->um_phdrs));
								kfree(result);
								kfree(UM_any(shdrs));
								decref_unlikely(file);
								return new_result;
							} else {
								goto not_an_elf_file_shdrs_result_mmlock;
							}
						}
						if (node == mima.mm_max)
							break;
						node = mnode_tree_nextnode(node);
					}

					/* Deal with previously merged nodes. */
					if unlikely(result->md_loadmin != (byte_t *)mnode_getminaddr(mima.mm_min) ||
					            result->md_loadmax != (byte_t *)mnode_getmaxaddr(mima.mm_max)) {
						if unlikely(result->md_loadmin < (byte_t *)mnode_getminaddr(mima.mm_min))
							goto not_an_elf_file_shdrs_result_mmlock;
						if unlikely(result->md_loadmax > (byte_t *)mnode_getmaxaddr(mima.mm_max))
							goto not_an_elf_file_shdrs_result_mmlock;
						TRY {
							if (result->md_loadmin > (byte_t *)mnode_getminaddr(mima.mm_min)) {
								if (!mnode_split_or_unlock(self, mima.mm_min, result->md_loadmin, NULL)) {
something_changed_merge:
									mman_lock_release(self);
									kfree(UM_any(result->um_phdrs));
									kfree(result);
									kfree(UM_any(shdrs));
									decref_unlikely(file);
									return UEM_TRYCREATE_UNLOCKED_MERGE;
								}
								mman_mappings_minmaxlocate(self, result->md_loadmin,
								                           result->md_loadmax, &mima);
							}
							if (result->md_loadmax < (byte_t *)mnode_getmaxaddr(mima.mm_max)) {
								if (!mnode_split_or_unlock(self, mima.mm_max, result->md_loadmax + 1, NULL))
									goto something_changed_merge;
								mman_mappings_minmaxlocate(self, result->md_loadmin,
								                           result->md_loadmax, &mima);
							}
						} EXCEPT {
							mman_mergenodes(self);
							kfree(UM_any(result->um_phdrs));
							kfree(result);
							RETHROW();
						}
					}

					/* Set the module self-pointers. */
					for (node = mima.mm_min;;) {
						assert(!node->mn_module);
						node->mn_module = result;
						++result->md_nodecount;
						if (node == mima.mm_max)
							break;
						node = mnode_tree_nextnode(node);
					}
				}
			}

			if unlikely(result->md_nodecount == 0)
				goto not_an_elf_file_shdrs_result_mmlock_mergenodes; /* _really_ shouldn't happen... */

			/* Add `result' to the cache of `self'.
			 * NOTE: The reference inherited here was accounted for by the init of `md_refcnt'! */
			LIST_INSERT_HEAD(&FORMMAN(self, thismman_uemc), result, um_cache);

			/* Fill in remaining fields of `result' */
			result->md_fsname = incref(rtld_name);
			result->md_mman   = weakincref(self);
			result->md_file   = file; /* Inherit reference. */
			mman_lock_release(self);
		} EXCEPT {
			kfree(UM_any(shdrs));
			RETHROW();
		}
	} EXCEPT {
		decref_unlikely(file);
		RETHROW();
	}
	return result;
not_an_elf_file_shdrs_result_mmlock_mergenodes:
	mman_mergenodes_locked(self);
not_an_elf_file_shdrs_result_mmlock:
	mman_lock_release(self);
	kfree(UM_any(result->um_phdrs));
	kfree(result);
	kfree(UM_any(shdrs));
not_an_elf_file:
	decref_unlikely(file);
	return UEM_TRYCREATE_UNLOCKED_NOUEM;
}


PRIVATE struct mfile_axref system_rtld_fsfile = AXREF_INIT(NULL);
PRIVATE struct fdirent system_rtld_dirent = {
	.fd_refcnt  = 1,
	.fd_ops     = &fdirent_empty_ops,
	.fd_ino     = 0,
	.fd_hash    = _RTLD_LIBDL_HASH,
	.fd_namelen = COMPILER_STRLEN(RTLD_LIBDL),
	.fd_type    = DT_REG,
	/* .fd_name = */ RTLD_LIBDL
};

#ifdef __ARCH_HAVE_COMPAT
PRIVATE struct mfile_axref compat_system_rtld_fsfile = AXREF_INIT(NULL);
PRIVATE struct fdirent compat_system_rtld_dirent = {
	.fd_refcnt  = 1,
	.fd_ops     = &fdirent_empty_ops,
	.fd_ino     = 0,
	.fd_hash    = _COMPAT_RTLD_LIBDL_HASH,
	.fd_namelen = COMPILER_STRLEN(COMPAT_RTLD_LIBDL),
	.fd_type    = DT_REG,
	/* .fd_name = */ COMPAT_RTLD_LIBDL
};
#endif /* __ARCH_HAVE_COMPAT */


INTERN NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1)) void
NOTHROW(KCALL system_cc_rtld_fsfile)(struct ccinfo *__restrict info) {
	REF struct mfile *mf;
	mf = axref_xch_inherit(&system_rtld_fsfile, NULL);
	if (mf && ATOMIC_DECFETCH(mf->mf_refcnt) == 0) {
		ccinfo_account(info, sizeof(struct mfile));
		mfile_destroy(mf);
	}
#ifdef __ARCH_HAVE_COMPAT
	mf = axref_xch_inherit(&compat_system_rtld_fsfile, NULL);
	if (mf && ATOMIC_DECFETCH(mf->mf_refcnt) == 0) {
		ccinfo_account(info, sizeof(struct mfile));
		mfile_destroy(mf);
	}
#endif /* __ARCH_HAVE_COMPAT */
}





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
PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) REF struct userelf_module *FCALL
uem_trycreate(struct mman *__restrict self,
              struct mnode *__restrict node,
              unsigned int skipped_neighbor = (unsigned int)-1) {
	bool did_unlock;
	REF struct userelf_module *result;
	struct mpart *part;
	struct mfile *file;

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
	if unlikely(node->mn_flags & (MNODE_F_MPREPARED | MNODE_F_KERNPART | MNODE_F_MHINT))
		return NULL; /* Certain flags can't be set for UserELF modules. */

	/* Acquire a lock to the node's part. */
	part = node->mn_part;
	if unlikely(!part)
		return NULL; /* Mustn't be a reserved node. */

	if (!mpart_lock_tryacquire(part)) {
		/* Release mman lock & spin until we get the part-lock! */
		incref(part);
		mman_lock_release(self);
		FINALLY_DECREF_UNLIKELY(part);
		mpart_lock_waitfor(part);
		return UEM_TRYCREATE_UNLOCKED;
	}

	file = part->mp_file;

	/* Check  for  specific files  that are  known to
	 * never be able to be apart of a UserELF module. */
	if (file == &mfile_ndef || file == &mfile_phys) {
		mpart_lock_release(part);
		return NULL;
	}

	did_unlock = false;
	if (mfile_isdevzero(file)) {
		/* Special case: zero-initialized memory.
		 * In this case, we may be dealing with a .bss segment
		 * of a UserELF module, in which case we should try to
		 * see if we can find a neighboring node that has also
		 * been yet to  be considered as  part of any  UserELF
		 * module, may form one in conjunction with this node. */
		unsigned int i;
		mpart_lock_release(part);
		for (i = 0; i < 2; ++i) {
			void *minaddr, *maxaddr;
			struct mnode *neighbor;
			if (i == skipped_neighbor)
				continue; /* Skip this neighbor. */
			neighbor = i == 0 ? mnode_tree_prevnode(node)
			                  : mnode_tree_nextnode(node);
			if (!neighbor)
				continue; /* No neighbor */
			if (neighbor->mn_module != NULL)
				continue; /* Already apart of a known (different) module */
			if (i == 0 ? mnode_getendaddr(neighbor) != mnode_getaddr(node)
			           : mnode_getaddr(neighbor) != mnode_getendaddr(node))
				continue; /* Not an immediate neighbor. */
			minaddr = mnode_getminaddr(node);
			maxaddr = mnode_getmaxaddr(node);

			/* Don't let the recursive call bounce back the call to our
			 * original node. - Do this by disallowing the inner callee
			 * from checking our original node for adjacency. */
			result = uem_trycreate(self, neighbor, i == 0 ? 1 : 0);
			if (result == UEM_TRYCREATE_UNLOCKED ||
			    result == UEM_TRYCREATE_UNLOCKED_MERGE) {
				/* Try again... */
				return result;
			} else if (result == UEM_TRYCREATE_UNLOCKED_NOUEM) {
				/* Not the preceding node.
				 * Acquire the mman lock and see if anything's changed. */
				did_unlock = true;
				mman_lock_acquire(self);
				if (mman_mappings_locate(self, minaddr) != node ||
				    mnode_getminaddr(node) != minaddr ||
				    mnode_getmaxaddr(node) != maxaddr ||
				    node->mn_part != part)
					return UEM_TRYCREATE_UNLOCKED;
			} else if (result != NULL) {
				/* Potential  success (but let's  re-try in case the
				 * module discovered is actually a different module)
				 *
				 * If we were successful, then `node->mn_module' may
				 * have been filled with `result' by `uem_trycreate' */
				decref_unlikely(result);
				return UEM_TRYCREATE_UNLOCKED;
			}
		}

		/* Special case: if this node was originally created by
		 * a file mapping, but has since been unshared (as  the
		 * result of a write), then the backing file will  have
		 * been set as one of the anon-files.
		 *
		 * Additionally, some shared libraries may set-up gaps
		 * between their different  program headers  (possibly
		 * to  aid in debugging  by making out-of-bound memory
		 * access fault more often), so even if `node' doesn't
		 * have  an immediate neighbor, that doesn't mean that
		 * it can't possibly be apart of a library.
		 *
		 * However, in the event that  `node' is the result  of
		 * a since unshared copy-on-write mapping, it may still
		 * contain  information  about the  original filesystem
		 * name.
		 * And if that's the case, then we can try to scan the
		 * entire mman for other  nodes with the same  fsname.
		 * If we find one, and that one doesn't already  point
		 * at some other user-space module, then we can try to
		 * construct a  UserELF module  for it.  And if  we're
		 * lucky, then doing  so may just  fill in the  module
		 * pointer for our own node! */
		if (node->mn_fsname) {
			for (i = 0; i < 2; ++i) {
				struct mnode *neighbor;
				if (i == skipped_neighbor)
					continue; /* Skip neighbors in this direction. */
				neighbor = node;
				for (;;) {
					void *minaddr, *maxaddr;
					neighbor = i == 0 ? mnode_tree_prevnode(neighbor)
					                  : mnode_tree_nextnode(neighbor);
					if (!neighbor)
						break; /* No more neighbors in this direction */
					if (neighbor->mn_fsname != node->mn_fsname ||
					    neighbor->mn_fspath != node->mn_fspath)
						continue; /* Different filesystem name... */
					if (neighbor->mn_module != NULL) {
						/* There is a known module under this name, but it doesn't contain our node! */
						goto anon_mem_not_a_module;
					}
					minaddr = mnode_getminaddr(node);
					maxaddr = mnode_getmaxaddr(node);

					/* Try to create a module for `neighbor' */
					result = uem_trycreate(self, neighbor, i == 0 ? 1 : 0);
					if (result == UEM_TRYCREATE_UNLOCKED ||
					    result == UEM_TRYCREATE_UNLOCKED_MERGE) {
						/* Try again... */
						return result;
					} else if (result == UEM_TRYCREATE_UNLOCKED_NOUEM) {
						/* Not the preceding node.
						 * Acquire the mman lock and see if anything's changed. */
						did_unlock = true;
						mman_lock_acquire(self);
						if (mman_mappings_locate(self, minaddr) != node ||
						    mnode_getminaddr(node) != minaddr ||
						    mnode_getmaxaddr(node) != maxaddr ||
						    node->mn_part != part)
							return UEM_TRYCREATE_UNLOCKED;
					} else if (result != NULL) {
						/* Potential  success (but let's  re-try in case the
						 * module discovered is actually a different module)
						 *
						 * If we were successful, then `node->mn_module' may
						 * have been filled with `result' by `uem_trycreate' */
						decref_unlikely(result);
						return UEM_TRYCREATE_UNLOCKED;
					}
				}
			}
		}
anon_mem_not_a_module:
		if (did_unlock) {
			mman_lock_release(self);
			return UEM_TRYCREATE_UNLOCKED_NOUEM;
		}
		return NULL;
	}

	/* Deal with the special RTLD files. (that are mapped by the
	 * kernel, but are also expected to exist on-disk  alongside
	 * all of the other, regular libraries) */
	if (file == &execabi_system_rtld_file.mrf_file) {
		/* Special handling for /lib[64]/libdl.so */
		USER CHECKED byte_t *node_addr;
		pos_t node_fpos;
		node_addr = (byte_t *)mnode_getaddr(node);
		node_fpos = mnode_getfileaddr(node);
		mpart_lock_release(part);
		mman_lock_release(self);
		result = uem_create_system_rtld(self, file,
		                                &system_rtld_fsfile,
		                                &system_rtld_dirent,
		                                node_addr, node_fpos);
		assertf(result != NULL, "Other values are used to indicate failure!");
		return result;
	}

#ifdef __ARCH_HAVE_COMPAT
	if (file == &compat_execabi_system_rtld_file.mrf_file) {
		/* Special handling for /lib/libdl.so */
		USER CHECKED byte_t *node_addr;
		pos_t node_fpos;
		node_addr = (byte_t *)mnode_getaddr(node);
		node_fpos = mnode_getfileaddr(node);
		mpart_lock_release(part);
		mman_lock_release(self);
		result = uem_create_system_rtld(self, file,
		                                &compat_system_rtld_fsfile,
		                                &compat_system_rtld_dirent,
		                                node_addr, node_fpos);
		assertf(result != NULL, "Other values are used to indicate failure!");
		return result;
	}
#endif /* __ARCH_HAVE_COMPAT */

	/* Assume that we're dealing with an actual file-mapping. */
	{
		USER CHECKED byte_t *node_addr;
		pos_t node_fpos;
		incref(file);
		node_addr = (byte_t *)mnode_getaddr(node);
		node_fpos = mnode_getfileaddr(node);
		mpart_lock_release(part);
		mman_lock_release(self);

		/* Try to create a new UserELF module! */
		FINALLY_DECREF_UNLIKELY(file);
		result = uem_create_from_mapping(self, file, node_addr, node_fpos);
		assertf(result != NULL, "Other values are used to indicate failure!");
	}
	return result;
}




INTERN BLOCKING WUNUSED NONNULL((1)) REF struct userelf_module *FCALL
uem_fromaddr(struct mman *__restrict self,
             USER CHECKED void const *addr) {
	REF struct userelf_module *result;
	struct mnode *node;
	bool must_merge;
	must_merge = false;
	TRY {
again:
		mman_lock_acquire(self);
		node = mman_mappings_locate(self, addr);
		if (!node) {
/*unlock_and_return_NULL:*/
			if unlikely(must_merge)
				mman_mergenodes_locked(self);
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
		} else if (result == UEM_TRYCREATE_UNLOCKED_MERGE) {
			must_merge = true;
			goto again;
		} else if (result == UEM_TRYCREATE_UNLOCKED_NOUEM) {
			result = NULL;
		}
	} EXCEPT {
		if unlikely(must_merge)
			mman_mergenodes(self);
		RETHROW();
	}
	if unlikely(must_merge)
		mman_mergenodes(self);
	return result;
}

INTERN BLOCKING WUNUSED NONNULL((1)) REF struct userelf_module *FCALL
uem_aboveaddr(struct mman *__restrict self,
              USER CHECKED void const *addr) {
	REF struct userelf_module *result;
	struct mnode *node;
	struct mnode_tree_minmax mima;
	bool must_merge;
	must_merge = false;
	TRY {
again:
		mman_lock_acquire(self);
		mman_mappings_minmaxlocate(self, addr, (void *)-1, &mima);
		node = mima.mm_min;
		if (!node) {
unlock_and_return_NULL:
			if unlikely(must_merge)
				mman_mergenodes_locked(self);
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
				if (node == mima.mm_max)
					goto unlock_and_return_NULL;
				node = mnode_tree_nextnode(node);
				assert(node);
			} else if (result == UEM_TRYCREATE_UNLOCKED) {
				addr = node_minaddr;
				goto again;
			} else if (result == UEM_TRYCREATE_UNLOCKED_MERGE) {
				addr       = node_minaddr;
				must_merge = true;
				goto again;
			} else if (result == UEM_TRYCREATE_UNLOCKED_NOUEM) {
				addr = (byte_t *)node_maxaddr + 1;
				goto again;
			} else {
				/* Got it! */
				break;
			}
		}
	} EXCEPT {
		if unlikely(must_merge)
			mman_mergenodes(self);
		RETHROW();
	}
	if unlikely(must_merge)
		mman_mergenodes(self);
	return result;
}

INTERN BLOCKING WUNUSED NONNULL((1)) REF struct userelf_module *FCALL
uem_next(struct mman *__restrict self,
         struct module *__restrict prev) {
	REF struct userelf_module *result;
	struct mnode *node;
	struct mnode_tree_minmax mima;
	void *minaddr;
	bool must_merge;

	/* Because UserELF modules can be embedded inside of each other,
	 * we have to start looking for them starting immediately  after
	 * the original node. */
	minaddr = prev->md_loadmin + PAGESIZE;

	must_merge = false;
	TRY {
again:
		mman_lock_acquire(self);
		mman_mappings_minmaxlocate(self, minaddr, (void *)-1, &mima);
		node = mima.mm_min;
		if (!node) {
unlock_and_return_NULL:
			if unlikely(must_merge)
				mman_mergenodes_locked(self);
			mman_lock_release(self);
			return NULL;
		}
		for (;;) {
			void *node_minaddr, *node_maxaddr;

			/* Check if this node is known to be bound to the old module.
			 * If it is, then simply skip this node! */
			if (node->mn_module == prev) {
nextnode:
				if (node == mima.mm_max)
					goto unlock_and_return_NULL;
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
			} else if (result == UEM_TRYCREATE_UNLOCKED_MERGE) {
				minaddr    = node_minaddr;
				must_merge = true;
				goto again;
			} else if (result == UEM_TRYCREATE_UNLOCKED_NOUEM) {
				minaddr = (byte_t *)node_maxaddr + 1;
				goto again;
			} else if (result == prev) {
				/* Got the same module all over again... (skip this node) */
				minaddr = (byte_t *)node_maxaddr + 1;
				decref_nokill(result);
				goto again;
			} else if (result->md_loadmin <= prev->md_loadmin) {
				/* Got a module that is based below the current module... (skip this node) */
				minaddr = (byte_t *)node_maxaddr + 1;
				decref(result);
				goto again;
			} else {
				/* Found the actual next UserELF module! */
				break;
			}
		}
	} EXCEPT {
		if unlikely(must_merge)
			mman_mergenodes(self);
		RETHROW();
	}
	if unlikely(must_merge)
		mman_mergenodes(self);
	return result;
}


#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
DBG_COMMAND(lslib,
            "lslib\n"
            "\tEnumerate user-space libraries\n") {
	REF struct module *mod;
	struct mfile *exec_file;
	struct mman *mm;
	mm        = dbg_current->t_mman;
	exec_file = FORMMAN(mm, thismman_execinfo).mei_file;
	dbg_print(DBGSTR("name                            loadaddr minaddr  maxaddr\n"));
	for (mod = mman_module_first_nx(mm); mod;) {
		ssize_t len;
		FINALLY_DECREF_UNLIKELY(mod);
		dbg_savecolor();
		if (mod->md_file == exec_file) {
			/* Highlight the main executable. */
			dbg_setcolor(ANSITTY_CL_WHITE,
			             ANSITTY_CL_DARK_GRAY);
		}
		if (module_haspath_or_name(mod)) {
			len = module_printpath_or_name(mod, &dbg_printer, NULL);
		} else {
			dbg_putc('?');
			len = 1;
		}
		while (len < 31) {
			dbg_putc(' ');
			++len;
		}
		dbg_printf(DBGSTR(" %.8" PRIxPTR " %.8" PRIxPTR " %.8" PRIxPTR "\n"),
		           mod->md_loadaddr,
		           mod->md_loadmin,
		           mod->md_loadmax);
		dbg_loadcolor();
		mod = mman_module_next_nx(mm, mod);
	}
	return 0;
}
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

DECL_END
#endif /* CONFIG_HAVE_KERNEL_USERELF_MODULES */

#endif /* !GUARD_KERNEL_SRC_MEMORY_MODULE_USERELF_C */
