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
#ifndef GUARD_KERNEL_SRC_MEMORY_DRIVER_C
#define GUARD_KERNEL_SRC_MEMORY_DRIVER_C 1
#define __WANT_MODULE_SECTION__ms_dead
#define __WANT_MODULE__md_mmlop
#define __WANT_DRIVER_SECTION_ds_sect
#define __WANT_DRIVER_d_module
#define __WANT_DRIVER__d_internals
#define __WANT_MNODE__mn_dead
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <debugger/hook.h>
#include <debugger/io.h>
#include <debugger/rt.h>
#include <kernel/arch/driver.h>
#include <kernel/debugtrap.h>
#include <kernel/except.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/fs.h>
#include <kernel/fs/node.h>
#include <kernel/fs/path.h>
#include <kernel/fs/vfs.h>
#include <kernel/handle-proto.h>
#include <kernel/heap.h>
#include <kernel/mman.h>
#include <kernel/mman/cache.h>
#include <kernel/mman/driver.h>
#include <kernel/mman/flags.h>
#include <kernel/mman/kram.h>
#include <kernel/mman/map.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/module-section-cache.h>
#include <kernel/mman/module.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/phys.h>
#include <kernel/mman/rw.h>
#include <kernel/mman/sync.h>
#include <kernel/mman/unmapped.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/syslog.h>
#include <kernel/vboxgdb.h>
#include <sched/sig.h>

#include <hybrid/align.h>
#include <hybrid/byteorder.h>
#include <hybrid/minmax.h>
#include <hybrid/overflow.h>
#include <hybrid/sched/atomic-lock.h>
#include <hybrid/sequence/bsearch.h>
#include <hybrid/sequence/rbtree.h>
#include <hybrid/typecore.h>

#include <kos/except.h>
#include <kos/except/reason/noexec.h>
#include <kos/nopf.h>

#include <alloca.h>
#include <assert.h>
#include <atomic.h>
#include <elf.h>
#include <errno.h>
#include <format-printer.h>
#include <inttypes.h>
#include <malloca.h>
#include <signal.h>
#include <stdalign.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <libcmdline/decode.h>
#include <libcmdline/encode.h>
#include <libunwind/eh_frame.h>
#include <libunwind/errno.h>
#include <libunwind/unwind.h>
#include <libzlib/inflate.h>


#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/* Max # of section headers accepted for driver modules.
 * A limit must be imposed to prevent malicious programs
 * from flooding kernel-space memory. */
#ifndef ELF_ARCH_MAXSHCOUNT
#define ELF_ARCH_MAXSHCOUNT 128
#endif /* !ELF_ARCH_MAXSHCOUNT */

DECL_BEGIN


#define THROW_FAULTY_ELF_ERROR(...)           \
	THROW(E_NOT_EXECUTABLE_FAULTY,            \
	      E_NOT_EXECUTABLE_FAULTY_FORMAT_ELF, \
	      __VA_ARGS__)

/************************************************************************/
/* Loaded driver enumeration (lockless!)                                */
/************************************************************************/

PRIVATE struct driver_loadlist default_loaded_drivers = {
	.dll_refcnt  = 2, /* +1:default_loaded_drivers, +1:drivers */
	.dll_count   = 1, /* Upon boot, only the kernel core driver exists. */
	.dll_drivers = { &kernel_driver }
};

/* [1..1] A descriptor for the set of currently loaded drivers.
 * NOTE: To retrieve this list, don't use `arref_get(&drivers)',
 *       but make use  of `get_driver_loadlist()' instead.  This
 *       must be done since the later will automatically try  to
 *       get rid of drivers that  have been destroyed, but  were
 *       unable to remove themselves from the load-list. */
PUBLIC struct driver_loadlist_arref drivers = ARREF_INIT(&default_loaded_drivers);
#ifdef CONFIG_HAVE_KERNEL_VBOXGDB
DEFINE_PUBLIC_ALIAS(_vboxgdb_kos_driver_state, drivers);
#endif /* CONFIG_HAVE_KERNEL_VBOXGDB */

/* Set to true if `drivers' may contain drivers
 * that  have been destroyed,  but could not be
 * removed due to lack of memory. */
PRIVATE bool loaded_drivers_contains_dead = false;



PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL driver_loadlist_destroy)(struct driver_loadlist *__restrict self) {
	size_t i;
	for (i = 0; i < self->dll_count; ++i)
		weakdecref(self->dll_drivers[i]);
	kfree(self);
}

/* Return the list of currently loaded drivers.
 * Note that this function is  NOBLOCK+NOTHROW! */
PUBLIC NOBLOCK ATTR_RETNONNULL WUNUSED REF struct driver_loadlist *
NOTHROW(FCALL get_driver_loadlist)(void) {
	REF struct driver_loadlist *result;
again:
	result = arref_get(&drivers);

	/* Only reap dead drivers from the load-list if the kernel
	 * hasn't been poisoned,  and debugger-mode isn't  active.
	 *
	 * iow: Only do this when the system is running "normal" */
	if (unlikely(loaded_drivers_contains_dead) &&
	    likely(!kernel_poisoned() && !dbg_active)) {
		bool cmpxch_ok;
		size_t i, newcount;
		REF struct driver_loadlist *new_dll;
		COMPILER_BARRIER();
		loaded_drivers_contains_dead = false;

		/* Try to construct a new driver load-list that doesn't
		 * contain any of the drivers that have been destroyed.
		 *
		 * For this purpose, figure out the set of drivers  that
		 * aren't already dead. This can easily be done by doing
		 * a tryincref() on every driver from the resulting set,
		 * and counting how many we got.
		 *
		 * After that point, we'll continue to hold a reference
		 * to every non-destroyed driver, meaning that the # of
		 * non-destroyed drivers in the resulting set will stay
		 * the same until we release those reference again. */
		for (i = 0, newcount = 0; i < result->dll_count; ++i) {
			if (tryincref(result->dll_drivers[i]))
				++newcount;
		}
		assert(newcount <= result->dll_count);

		/* Check for special case: all drivers are still alive.
		 * This  might  happen due  to race  conditions, etc... */
		if unlikely(newcount == result->dll_count) {
			/* Simply drop all of the references we acquired. */
			for (i = 0; i < result->dll_count; ++i)
				decref_unlikely(result->dll_drivers[i]);
			goto done;
		}

		if unlikely(newcount == 1) {
			/* Special  case:  only 1  driver remains,
			 * which has to be the kernel core driver! */
			new_dll = incref(&default_loaded_drivers);
		} else {
			size_t dst;

			/* Try to allocate a new driver load-list.
			 * If this fails, drop all of our references, change the
			 * `loaded_drivers_contains_dead' flag back to true, and
			 * silently return  the original  list (containing  some
			 * dead drivers), thus letting the next caller deal with
			 * the removal of dead drivers. */
			new_dll = (REF struct driver_loadlist *)kmalloc_nx(offsetof(struct driver_loadlist, dll_drivers) +
			                                                   newcount * sizeof(WEAK REF struct driver *),
			                                                   GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT);
			if unlikely(!new_dll) {
				/* Failed to allocate a  new loadlist, and there  are
				 * still some more dead drivers within the old one...
				 *
				 * In this case, leave the work to-be done up for the
				 * next caller of this function. */
				loaded_drivers_contains_dead = true;
				COMPILER_WRITE_BARRIER();

				for (i = 0; i < result->dll_count; ++i) {
					if (!wasdestroyed(result->dll_drivers[i]))
						decref_unlikely(result->dll_drivers[i]);
				}
				goto done;
			}

			/* Fill in the new driver load-list with all of the
			 * non-destroyed  drivers  from the  original list. */
			new_dll->dll_refcnt = 2; /* +1:return, +1:arref_cmpxch_inherit_new() */
			new_dll->dll_count  = newcount;
			for (i = 0, dst = 0; i < result->dll_count; ++i) {
				if (wasdestroyed(result->dll_drivers[i]))
					continue;
				new_dll->dll_drivers[dst] = weakincref(result->dll_drivers[i]);
				++dst;
			}
			assert(dst == newcount);
		}

		/* Try to exchange the  old driver load-list (which  contains
		 * some dead drivers) with the new one (which doesn't contain
		 * any dead drivers at the moment, since we're still  holding
		 * full references to all drivers that would have been  dead) */
		COMPILER_BARRIER();
		cmpxch_ok = arref_cmpxch_inherit_new(&drivers, result, new_dll);
		COMPILER_BARRIER();

		/* Drop all of  our references  to drivers  apart of  the set  of
		 * ones that haven't been destroyed yet. Note that by doing this,
		 * more  drivers may end up being destroyed, but that's ok, since
		 * those  drivers will  once again  be able  to remove themselves
		 * normally from the driver-load-list.
		 *
		 * Also note that we can  simply `decref()' every driver  from
		 * `new_dll' here, since that list contains only those drivers
		 * which weren't destroyed earlier, which  is the same set  as
		 * those which we were able to `tryincref()' above!
		 *
		 * As far as logic ordering goes, the only thing import here is
		 * that these decref() operations happen _after_ the CMPXCH  of
		 * the current driver load-list above! */
		for (i = 0; i < new_dll->dll_count; ++i)
			decref_unlikely(new_dll->dll_drivers[i]);

		/* Drop our reference to the old set of loaded drivers. */
		decref_likely(result);

		if (!cmpxch_ok) {
			/* The driver load-list changed in the mean time...
			 * Handle this case by trying again... */
			loaded_drivers_contains_dead = true;
			decref_nokill(new_dll); /* The would-be inherited-by-drivers reference */
			decref_likely(new_dll); /* The would-be returned reference */
			COMPILER_WRITE_BARRIER();
			goto again;
		}

		/* Success. - Simply return the (now smaller)
		 * set  of  (probably)  still-alive  drivers. */
		result = new_dll;
		COMPILER_BARRIER();
	}
done:
	return result;
}






/************************************************************************/
/* Driver section operator table                                        */
/************************************************************************/

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL driver_section_destroy)(struct driver_section *__restrict self) {
	REF struct driver *drv;
	drv = (REF struct driver *)self->ds_sect.ms_module;
	if (tryincref(drv)) {
		/* Try to remove `self' from the module's section vector. */
		uint16_t myindex;
		myindex = (uint16_t)(size_t)(self->ds_shdr - drv->d_shdr);
		assert(myindex < drv->d_shnum);

		/* Replace a pointer to `self' with `NULL'.
		 * There is the (very) unlikely case that someone reloaded
		 * the section before we were able to delete out  pointer,
		 * in which case that new section already took our spot! */
		awref_cmpxch(&drv->d_sections[myindex], self, NULL);
		decref_unlikely(drv);
	}
	weakdecref(drv);
	if (self->ds_infladdr != (KERNEL byte_t *)-1 &&
	    self->ds_infladdr != self->ds_addr) {
		mman_unmap_kram(self->ds_infladdr,
		                self->ds_inflsize);
	}
	if (!(self->ds_sect.ms_flags & SHF_ALLOC) &&
	    self->ds_addr != (KERNEL byte_t *)-1) {
		mman_unmap_kram_and_kfree(self->ds_addr,
		                          self->ds_sect.ms_size,
		                          self);
	} else {
		kfree(self);
	}
}

PRIVATE /*ATTR_PURE*/ WUNUSED NONNULL((1)) char const *
NOTHROW(FCALL driver_section_getname)(struct driver_section *__restrict self) {
	struct driver *drv;
	drv = (struct driver *)self->ds_sect.ms_module;
	assert(!wasdestroyed(drv));
	return drv->d_shstrtab + self->ds_shdr->sh_name;
}

PRIVATE WUNUSED NONNULL((1)) KERNEL byte_t *FCALL
driver_section_create_kernaddr_ex(struct driver_section *__restrict self,
                                  struct driver *__restrict drv) {
	struct mfile *file;
	assert(self->ds_sect.ms_size != 0);
	if ((file = driver_getfile(drv)) == NULL)
		THROW(E_NO_SUCH_OBJECT);
	return (byte_t *)mman_map(/* self:        */ &mman_kernel,
	                          /* hint:        */ MHINT_GETADDR(KERNEL_MHINT_TEMPORARY),
	                          /* num_bytes:   */ self->ds_sect.ms_size,
	                          /* prot:        */ (PROT_READ | PROT_WRITE) & ~PROT_SHARED,
	                          /* flags:       */ MHINT_GETMODE(KERNEL_MHINT_TEMPORARY),
	                          /* file:        */ file,
	                          /* file_fspath: */ drv->d_module.md_fspath,
	                          /* file_fsname: */ drv->d_module.md_fsname,
	                          /* file_pos:    */ (pos_t)self->ds_shdr->sh_offset);
}

PRIVATE WUNUSED NONNULL((1)) KERNEL byte_t *FCALL
driver_section_create_kernaddr(struct driver_section *__restrict self) {
	REF struct driver *drv;
	if unlikely(self->ds_sect.ms_size == 0)
		return (KERNEL byte_t *)KERNELSPACE_BASE + PAGESIZE;
	drv = (REF struct driver *)self->ds_sect.ms_module;
	if (!tryincref(drv))
		THROW(E_NO_SUCH_OBJECT);
	FINALLY_DECREF_UNLIKELY(drv);
	return driver_section_create_kernaddr_ex(self, drv);
}



PRIVATE WUNUSED NONNULL((1)) KERNEL byte_t *FCALL
driver_section_getaddr(struct driver_section *__restrict self) {
	byte_t *result;
	if (self->ds_addr != (KERNEL byte_t *)-1)
		return self->ds_addr;
	result = driver_section_create_kernaddr(self);
	if unlikely(!atomic_cmpxch(&self->ds_addr, (KERNEL byte_t *)-1, result)) {
		/* Race condition: some other thread already did this in the mean time... */
		mman_unmap_kram(result, self->ds_sect.ms_size);
	}
	return self->ds_addr;
}

PRIVATE WUNUSED NONNULL((1, 2)) KERNEL byte_t *FCALL
driver_section_getaddr_inflate(struct driver_section *__restrict self,
                               size_t *__restrict psize) {
	size_t dst_size, src_size;
	KERNEL byte_t *src_data, *dst_data;
	void *src_data_freeme_cookie;
	REF struct driver *drv;
	if (self->ds_infladdr != (KERNEL byte_t *)-1) {
		*psize = self->ds_inflsize;
		return self->ds_infladdr;
	}
	if (!(self->ds_sect.ms_flags & SHF_COMPRESSED)) {
		/* Section isn't actually compressed! */
		dst_data = driver_section_getaddr(self);
		atomic_write(&self->ds_inflsize, self->ds_sect.ms_size);
		atomic_cmpxch(&self->ds_infladdr, (KERNEL byte_t *)-1, dst_data);
		*psize = self->ds_sect.ms_size;
		return dst_data;
	}
	drv = (REF struct driver *)self->ds_sect.ms_module;
	if (!tryincref(drv))
		THROW(E_NO_SUCH_OBJECT);
	FINALLY_DECREF_UNLIKELY(drv);
	if unlikely(OVERFLOW_USUB(self->ds_sect.ms_size, sizeof(ElfW(Chdr)), &src_size))
		THROW(E_INVALID_ARGUMENT);
	src_data = self->ds_addr;
	src_data_freeme_cookie = NULL;
	if (src_data == (KERNEL byte_t *)-1) {
		/* Allocate a  cookie that  we can  later use  to
		 * asynchronously unmap the compressed data blob. */
		src_data_freeme_cookie = mman_unmap_kram_cookie_alloc();
		TRY {
			src_data = driver_section_create_kernaddr_ex(self, drv);
		} EXCEPT {
			mman_unmap_kram_cookie_free(src_data_freeme_cookie);
			RETHROW();
		}
	}
	{
		ElfW(Chdr) *chdr;
		RAII_FINALLY {
			if (src_data_freeme_cookie)
				mman_unmap_kram_and_kfree(src_data, self->ds_sect.ms_size, src_data_freeme_cookie);
		};
		chdr = (ElfW(Chdr) *)src_data;
		if unlikely(chdr->ch_type != ELFCOMPRESS_ZLIB)
			THROW(E_INVALID_ARGUMENT);
		dst_size = chdr->ch_size;
		dst_data = (byte_t *)mman_map_kram(NULL, dst_size, GFP_PREFLT);
		TRY {
			ssize_t error;
			struct zlib_reader reader;
			zlib_reader_init(&reader, chdr + 1, src_size);

			/* Decompress data. */
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
			if (dbg_active) {
				/* Display an on-screen message that we're decompressing stuff... */
				void *screen_buffer;
				char const *section_name;
				dbg_pprinter_arg_t pp;
				section_name = driver_section_getname(self);
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
				if (module_haspath_or_name(&drv->d_module)) {
					module_printpath_or_name(&drv->d_module, &dbg_pprinter, &pp);
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

			/* clear trailing data that could not be read. */
			if (dst_size > (size_t)error) {
				bzero((byte_t *)dst_data + (size_t)error,
				      dst_size - error);
			}
		} EXCEPT {
			mman_unmap_kram(dst_data, dst_size);
			RETHROW();
		}
	}
	atomic_write(&self->ds_inflsize, dst_size);
	atomic_cmpxch(&self->ds_infladdr, (KERNEL byte_t *)-1, dst_data);
	*psize = dst_size;
	return dst_data;
}


PRIVATE struct module_section_ops const driver_section_ops = {
	.ms_destroy         = (NONNULL_T((1)) void NOTHROW_T(FCALL *)(struct module_section *__restrict))&driver_section_destroy,
	.ms_getname         = (ATTR_PURE_T WUNUSED_T NONNULL_T((1)) char const *(FCALL *)(struct module_section *__restrict))&driver_section_getname,
	.ms_getaddr         = (WUNUSED_T NONNULL_T((1)) byte_t *(FCALL *)(struct module_section *__restrict))&driver_section_getaddr,
	.ms_getaddr_alias   = (WUNUSED_T NONNULL_T((1)) byte_t *(FCALL *)(struct module_section *__restrict))&driver_section_getaddr,
	.ms_getaddr_inflate = (WUNUSED_T NONNULL_T((1, 2)) byte_t *(FCALL *)(struct module_section *__restrict, size_t *__restrict))&driver_section_getaddr_inflate,
};





/************************************************************************/
/* Custom kernel driver data structures                                 */
/************************************************************************/
#ifdef __INTELLISENSE__
struct kernel_shstrtab { char zero; };
PRIVATE ATTR_COLDRODATA struct kernel_shstrtab const kernel_shstrtab_data = { 0 };
enum { KERNEL_SECTIONS_COUNT };
PRIVATE ATTR_COLDRODATA ElfW(Shdr) const kernel_shdr[KERNEL_SECTIONS_COUNT] = {};
PRIVATE struct driver_section_awref kernel_sections[KERNEL_SECTIONS_COUNT] = {};
#else /* __INTELLISENSE__ */
#define SECTION_DESCRIPTOR_INDEX     PP_CAT2(KERNEL_SECTION_INDEX_, __LINE__)
#define SECTION_DESCRIPTOR_SHSTRNAME PP_CAT2(ks_name_, __LINE__)

/* Define globals. */
#define INTERN_SECTION(symbol_name, name, type, flags, start, size, entsize, link, info) /* nothing */
#include "driver-kernel_sections.def"

/* Define the kernel's .shstrtab section */
struct kernel_shstrtab {
#define INTERN_SECTION(symbol_name, name, type, flags, start, size, entsize, link, info) \
	char SECTION_DESCRIPTOR_SHSTRNAME[sizeof(name)];
#include "driver-kernel_sections.def"
	char zero;
};

PRIVATE ATTR_COLDRODATA struct kernel_shstrtab const kernel_shstrtab_data = {
#define INTERN_SECTION(symbol_name, name, type, flags, start, size, entsize, link, info) \
	/* .SECTION_DESCRIPTOR_SHSTRNAME = */ name,
#include "driver-kernel_sections.def"
	/* .zero = */ 0
};



/* Define section indices */
enum {
#define INTERN_SECTION(symbol_name, name, type, flags, start, size, entsize, link, info) \
	SECTION_DESCRIPTOR_INDEX,
#include "driver-kernel_sections.def"
	KERNEL_SECTIONS_COUNT
};


/* Define the ELF section header vector. */
PRIVATE ATTR_COLDRODATA ElfW(Shdr) const kernel_shdr[KERNEL_SECTIONS_COUNT] = {
#define INTERN_SECTION(symbol_name, name, type, flags, start, size, entsize, link, info) \
	/* [SECTION_DESCRIPTOR_INDEX] = */ {                                                 \
		.sh_name      = offsetof(struct kernel_shstrtab, SECTION_DESCRIPTOR_SHSTRNAME),  \
		.sh_type      = (type),                                                          \
		.sh_flags     = (flags),                                                         \
		.sh_addr      = (uintptr_t)(start),                                              \
		.sh_offset    = 0,                                                               \
		.sh_size      = (uintptr_t)(size),                                               \
		.sh_link      = link,                                                            \
		.sh_info      = info,                                                            \
		.sh_addralign = 1,                                                               \
		.sh_entsize   = entsize,                                                         \
	},
#include "driver-kernel_sections.def"
};



/* Define the driver section descriptors. */
#define _SECTION(decl_name, name, type, flags, start, size, entsize, link, info)    \
	struct driver_section decl_name = {                                             \
		.ds_sect = {                                                                \
			.ms_refcnt  = 1,                                                        \
			.ms_ops     = &driver_section_ops,                                      \
			.ms_module  = &kernel_driver.d_module,                                  \
			.ms_size    = (size_t)(size),                                           \
			.ms_entsize = (size_t)(entsize),                                        \
			.ms_type    = (type),                                                   \
			.ms_flags   = (flags),                                                  \
			.ms_link    = (link),                                                   \
			.ms_info    = (info),                                                   \
			.ms_cache   = LIST_ENTRY_UNBOUND_INITIALIZER,                           \
		},                                                                          \
		.ds_shdr     = &kernel_shdr[SECTION_DESCRIPTOR_INDEX],                      \
		.ds_addr     = (byte_t *)(start),                                           \
		.ds_infladdr = (flags) & SHF_COMPRESSED ? (byte_t *)-1 : (byte_t *)(start), \
		.ds_inflsize = (flags) & SHF_COMPRESSED ? 0 : (size_t)(size),               \
	};
#define INTERN_SECTION(intern_name, name, type, flags, start, size, entsize, link, info) \
	INTERN _SECTION(intern_name, name, type, flags, start, size, entsize, link, info)
#define EXPORT_SECTION(export_name, name, type, flags, start, size, entsize, link, info) \
	PUBLIC _SECTION(export_name, name, type, flags, start, size, entsize, link, info)
#include "driver-kernel_sections.def"


/* Define the driver sections vector. */
PRIVATE struct driver_section_awref kernel_sections[KERNEL_SECTIONS_COUNT] = {
#define INTERN_SECTION(symbol_name, ...) /* [SECTION_DESCRIPTOR_INDEX] = */ AWREF_INIT(&symbol_name),
#include "driver-kernel_sections.def"
};
#endif /* !__INTELLISENSE__ */



extern byte_t __kernel_start[];
extern byte_t __kernel_end[];
extern byte_t __kernel_size[];
extern byte_t __kernel_size_nofree[];
extern byte_t __kernel_free_start[];
extern byte_t __kernel_free_size[];
extern byte_t __kernel_eh_frame_start[];
extern byte_t __kernel_eh_frame_end[];
#ifdef LIBUNWIND_HAVE_ARM_EXIDX
extern byte_t __kernel_ARM_exidx_start[];
extern byte_t __kernel_ARM_exidx_end[];
#endif /* LIBUNWIND_HAVE_ARM_EXIDX */

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL driver_free_)(struct driver *__restrict self) ASMNAME("driver_free");

PRIVATE WUNUSED NONNULL((1)) REF struct driver_section *FCALL
kernel_locksection_index(struct driver *__restrict UNUSED(self),
                         unsigned int section_index) {
	REF struct driver_section *result;
	if (section_index >= KERNEL_SECTIONS_COUNT)
		return NULL;
	result = awref_get(&kernel_sections[section_index]);
	return result;
}

PRIVATE WUNUSED NONNULL((1)) REF struct driver_section *FCALL
kernel_locksection(struct driver *__restrict self,
                   NCX char const *section_name) {
	unsigned int i;
	for (i = 0; i < KERNEL_SECTIONS_COUNT; ++i) {
		char const *name;
		name = (char *)&kernel_shstrtab_data + kernel_shdr[i].sh_name;
		if (strcmp(name, section_name) == 0)
			break; /* Found it! */
	}
	return kernel_locksection_index(self, i);
}

PRIVATE WUNUSED NONNULL((1, 3)) bool FCALL
driver_sectinfo(struct driver *__restrict self,
                uintptr_t module_relative_addr,
                struct module_sectinfo *__restrict info);

extern byte_t __kernel_text_start[];
extern byte_t __kernel_data_start[];

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) void const *
NOTHROW(FCALL kernel_get_tbase)(struct driver const *__restrict UNUSED(self)) {
	return __kernel_text_start;
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) void const *
NOTHROW(FCALL kernel_get_dbase)(struct driver const *__restrict UNUSED(self)) {
	return __kernel_data_start;
}



#ifndef KERNEL_DRIVER_NAME
#define KERNEL_DRIVER_NAME "kernel"
#endif /* !KERNEL_DRIVER_NAME */

#ifndef KERNEL_DRIVER_FILENAME
#define KERNEL_DRIVER_FILENAME "/os/kernel.bin"
#endif /* !KERNEL_DRIVER_FILENAME */

PRIVATE struct module_ops const kernel_module_ops = {
	.mo_free              = (NONNULL_T((1)) void NOTHROW_T(FCALL *)(struct module *__restrict))&driver_free_,  /* Needed for `module_isdriver()' */
	.mo_destroy           = (typeoffield(struct module_ops, mo_destroy))(void *)-1, /* Must never be called! */
	.mo_nonodes           = (typeoffield(struct module_ops, mo_nonodes))(void *)-1, /* Must never be called! */
	.mo_locksection       = (WUNUSED_T NONNULL_T((1)) REF struct module_section *(FCALL *)(struct module *__restrict, NCX char const *))&kernel_locksection,
	.mo_locksection_index = (WUNUSED_T NONNULL_T((1)) REF struct module_section *(FCALL *)(struct module *__restrict, unsigned int))&kernel_locksection_index,
	.mo_sectinfo          = (WUNUSED_T NONNULL_T((1, 3)) bool (FCALL *)(struct module *__restrict, uintptr_t, struct module_sectinfo *__restrict))&driver_sectinfo,
	.mo_get_tbase         = (WUNUSED_T NONNULL_T((1)) void const *NOTHROW_T(FCALL *)(struct module *__restrict))&kernel_get_tbase,
	.mo_get_dbase         = (WUNUSED_T NONNULL_T((1)) void const *NOTHROW_T(FCALL *)(struct module *__restrict))&kernel_get_dbase
};

PRIVATE ATTR_COLDRODATA char const kernel_driver_name[] = KERNEL_DRIVER_NAME;
INTERN ATTR_COLDDATA struct fdirent kernel_driver_fsname = {
	.fd_refcnt  = 2, /* +1: kernel_driver.d_module.md_fsname, +1: FORMMAN(&mman_kernel, thismman_execinfo.mei_dent) */
	.fd_ops     = &fdirent_empty_ops,
	.fd_ino     = 0,
#if __SIZEOF_POINTER__ == 8
	.fd_hash    = UINT64_C(0xe205ff2e0d3d550c),
#elif __SIZEOF_POINTER__ == 4
	.fd_hash    = UINT32_C(0x858bf1a8),
#else /* __SIZEOF_POINTER__ == ... */
	.fd_hash    = 0,
#endif /* __SIZEOF_POINTER__ != ... */
	.fd_namelen = COMPILER_STRLEN(KERNEL_DRIVER_FILENAME),
	.fd_type    = DT_REG,
	KERNEL_DRIVER_FILENAME
};

PUBLIC struct driver kernel_driver = {
	.d_module = {
		.md_refcnt     = 2,                         /* +1: kernel_driver, +1: d_state == DRIVER_STATE_LOADED */
		.md_weakrefcnt = 2 + KERNEL_SECTIONS_COUNT, /* +1:md_refcnt != 0, +1:md_nodecount != 0, +N: KERNEL_SECTIONS_COUNT */
		.md_nodecount  = 1, /* Any non-zero value is ok, but `1' is perfect here, since any mem-
		                     * node that is apart of the kernel core must never be unmapped, and
		                     * by setting `1' here, anyone attempting  to do so will cause  this
		                     * counter to drop to `0', which in turn will invoke the  BADPONITER
		                     * `mo_nonodes' callback and cause kernel panic! */
		.md_ops        = &kernel_module_ops,
		.md_mman       = &mman_kernel,
		.md_loadaddr   = 0,
		.md_loadmin    = __kernel_start,
		.md_loadmax    = __kernel_end - 1,
		.md_file       = NULL,
		{{ NULL, &kernel_driver_fsname, }},
#ifdef _MODULE_HAVE_SIZEOF_POINTER
		.md_sizeof_pointer = sizeof(void *),
#endif /* _MODULE_HAVE_SIZEOF_POINTER */
	},
	.d_state               = DRIVER_STATE_LOADED,
	.d_name                = kernel_driver_name,
	.d_cmdline             = NULL,
	.d_argc                = 0,
	.d_argv                = NULL,
	.d_depcnt              = 0,
	.d_depvec              = NULL,
	.d_dyncnt              = 0,
	.d_dynhdr              = NULL,
	.d_dynsym_tab          = NULL,
	.d_dynsym_cnt          = 0,
	.d_gnuhashtab          = NULL,
	.d_hashtab             = NULL,
	.d_dynstr              = NULL,
	.d_dynstr_end          = NULL,
	.d_shstrndx            = KERNEL_SECTIONS_COUNT - 1,
	.d_shnum               = KERNEL_SECTIONS_COUNT,
	.d_shdr                = (ElfW(Shdr) *)kernel_shdr,
	.d_sections            = kernel_sections,
	.d_shstrtab            = (char *)&kernel_shstrtab_data,
	.d_shstrsiz            = sizeof(kernel_shstrtab_data),
	.d_eh_frame_start      = __kernel_eh_frame_start,
	.d_eh_frame_end        = __kernel_eh_frame_end,
	.d_eh_frame_cache      = NULL,
	.d_eh_frame_cache_lock = ATOMIC_RWLOCK_INIT,
#ifdef LIBUNWIND_HAVE_ARM_EXIDX
	.d_ARM_exidx_start     = __kernel_ARM_exidx_start,
	.d_ARM_exidx_end       = __kernel_ARM_exidx_end,
#endif /* LIBUNWIND_HAVE_ARM_EXIDX */
	.d_phnum               = 2,
	.d_phdr                = {
		/* [0] = */ ELFW(PHDR_INIT)(
			/* .p_type   = */ PT_LOAD,
			/* .p_offset = */ 0, /* Doesn't matter... */
			/* .p_vaddr  = */ (uintptr_t)__kernel_start,
			/* .p_paddr  = */ (uintptr_t)__kernel_start - KERNEL_CORE_BASE,
			/* .p_filesz = */ (uintptr_t)__kernel_size_nofree,
			/* .p_memsz  = */ (uintptr_t)__kernel_size_nofree,
			/* .p_flags  = */ PF_X | PF_W | PF_R,
			/* .p_align  = */ PAGESIZE
		),
		/* [1] = */ ELFW(PHDR_INIT)(
			/* .p_type   = */ PT_LOAD,
			/* .p_offset = */ 0, /* Doesn't matter... */
			/* .p_vaddr  = */ (uintptr_t)__kernel_free_start,
			/* .p_paddr  = */ (uintptr_t)__kernel_free_start - KERNEL_CORE_BASE,
			/* .p_filesz = */ (uintptr_t)__kernel_free_size,
			/* .p_memsz  = */ (uintptr_t)__kernel_free_size,
			/* .p_flags  = */ PF_X | PF_W | PF_R,
			/* .p_align  = */ PAGESIZE
		)
	}
};




/************************************************************************/
/* Driver enumeration/lookup functions                                  */
/************************************************************************/
PUBLIC NOBLOCK WUNUSED REF struct driver *
NOTHROW(FCALL driver_fromaddr)(void const *addr) {
	REF struct driver_loadlist *ll;
	REF struct driver *result;
	size_t i;

	/* If possible, try to make use of the mnode->module  self-pointers!
	 * Note  however that this  requires acquiring a  lock to the kernel
	 * mman, which can't be done consistently without blocking. As such,
	 * we have a fallback further  below that uses the driver  load-list
	 * in order to find the relevant driver as a fall-back. */
	if (mman_lock_tryacquire(&mman_kernel)) {
		struct mnode *node;
		result = NULL;
		node   = mman_mappings_locate(&mman_kernel, addr);
		if (node) {
			result = (struct driver *)node->mn_module;

			/* NOTE: Any module we  find here should  _always_ be a  driver
			 *       module, but better be save than sorry, and check  that
			 *       this is the case, only constructing the to-be returned
			 *       reference if that is truly so. */
			if (result && (!module_isdriver((struct module *)result) ||
			               !tryincref(result)))
				result = NULL;
		}
		mman_lock_release(&mman_kernel);
		return result;
	}

	/* Try to do a binary search for `addr'.
	 * We take advantage of the fact that the driver list is
	 * sorted by the address  ranges used by the  individual
	 * drivers. */
	ll = get_driver_loadlist();
	assert_assume(ll->dll_count >= 1);
	BSEARCH_RANGE (i, ll->dll_drivers, ll->dll_count,
	                                   ->d_module.md_loadmin,
	                                   ->d_module.md_loadmax,
	               (byte_t const *)addr) {
		uint16_t phdr;
		uintptr_t driver_reladdr;
		result = ll->dll_drivers[i];

		/* Check  if the driver-relative address is being
		 * mapped by one of the driver's program headers!
		 * Note  that we can access the phdr-vector, even
		 * after the driver's been destroyed just fine! */
		driver_reladdr = (uintptr_t)addr - result->d_module.md_loadaddr;
		for (phdr = 0; phdr < result->d_phnum; ++phdr) {
			if (result->d_phdr[phdr].p_type != PT_LOAD)
				continue; /* Not a load-header! */
			if (driver_reladdr < result->d_phdr[phdr].p_vaddr)
				continue; /* Not this one! */
			if (driver_reladdr >= (result->d_phdr[phdr].p_vaddr +
			                       result->d_phdr[phdr].p_memsz))
				continue; /* Not this one! */

			/* Found it! */
			if unlikely(!tryincref(result))
				goto nope;
			decref_unlikely(ll);
			return result;
		}
		goto nope;
	}
nope:
	decref_unlikely(ll);
	return NULL;
}

PUBLIC NOBLOCK WUNUSED REF struct driver *
NOTHROW(FCALL driver_aboveaddr)(void const *addr) {
	REF struct driver_loadlist *ll;
	REF struct driver *result;
	size_t i;
	ll = get_driver_loadlist();
	assert_assume(ll->dll_count >= 1);
	for (i = 0; i < ll->dll_count; ++i) {
		result = ll->dll_drivers[i];
		if (addr >= result->d_module.md_loadmin) {
			if likely(tryincref(result)) {
				decref_unlikely(ll);
				return result;
			}
		}
	}
	decref_unlikely(ll);
	return NULL;
}

PUBLIC NOBLOCK WUNUSED REF struct driver *
NOTHROW(FCALL driver_next)(struct module *prev) {
	size_t i;
	REF struct driver *result;
	REF struct driver_loadlist *ll;
	ll = get_driver_loadlist();
	assert_assume(ll->dll_count >= 1);
	i = 0;
	if (prev != NULL) {
		/* Find the index of the successor of `prev' */
		for (;; ++i) {
			if (i >= ll->dll_count - 1)
				return NULL; /* No successor... */
			if (&ll->dll_drivers[i]->d_module == prev) {
				++i;
				break;
			}
		}
	}
	do {
		result = ll->dll_drivers[i];
		if (tryincref(result))
			break;
		result = NULL;
	} while (++i < ll->dll_count);
	decref_unlikely(ll);
	return result;
}

/* Lookup an already-loaded driver, given its name, filename, or  file.
 * Note that driver filenames (if  not absolute paths) are  interpreted
 * relative to the calling thread's current CWD, however absolute paths
 * are interpreted relative to `vfs_kernel' (i.e. are _NOT_ affected by
 * chroot(2)) */
PUBLIC WUNUSED REF struct driver *FCALL
driver_fromname(NCX char const *driver_name)
		THROWS(E_SEGFAULT) {
	size_t i;
	REF struct driver *result;
	REF struct driver_loadlist *ll;
	ll = get_driver_loadlist();
	FINALLY_DECREF_UNLIKELY(ll);
	assert_assume(ll->dll_count >= 1);
	for (i = 0; i < ll->dll_count; ++i) {
		result = ll->dll_drivers[i];
		if (!tryincref(result))
			continue;
		if (strcmp(result->d_name, driver_name) == 0)
			return result;
		decref_unlikely(result);
	}
	return NULL;
}

PUBLIC WUNUSED REF struct driver *FCALL
driver_fromname_with_len(NCX char const *driver_name,
                         size_t driver_name_len)
		THROWS(E_SEGFAULT) {
	size_t i;
	REF struct driver *result;
	REF struct driver_loadlist *ll;
	ll = get_driver_loadlist();
	FINALLY_DECREF_UNLIKELY(ll);
	assert_assume(ll->dll_count >= 1);
	for (i = 0; i < ll->dll_count; ++i) {
		result = ll->dll_drivers[i];
		if (!tryincref(result))
			continue;
		if (strcmpz(result->d_name, driver_name, driver_name_len) == 0)
			return result;
		decref_unlikely(result);
	}
	return NULL;
}

PUBLIC NOBLOCK WUNUSED NONNULL((1)) REF struct driver *
NOTHROW(FCALL driver_fromfile)(struct mfile *__restrict driver_file) {
	size_t i;
	REF struct driver *result;
	REF struct driver_loadlist *ll;
	ll = get_driver_loadlist();
	assert_assume(ll->dll_count >= 1);
	for (i = 0; i < ll->dll_count; ++i) {
		result = ll->dll_drivers[i];
		if (result->d_module.md_file == driver_file) {
			if (tryincref(result)) {
				decref_unlikely(ll);
				return result;
			}
			break;
		}
	}
	decref_unlikely(ll);
	return NULL;
}



/************************************************************************/
/* Driver helper functions                                              */
/************************************************************************/

/* Return the mem-file belonging to the given driver.
 * If the driver  wasn't loaded form  a file, try  to search for  that
 * file within the root filesystem within paths from `driver_libpath'.
 * If the file still can't be found, return `NULL'. */
PUBLIC BLOCKING WUNUSED NONNULL((1)) struct mfile *FCALL
driver_getfile(struct driver *__restrict self)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	if (!self->d_module.md_file) {
		/* TODO */
		COMPILER_IMPURE();
	}
	return self->d_module.md_file;
}




/************************************************************************/
/* Special handling for "drv_arg$..." symbols.                          */
/************************************************************************/


/* Known arg$ entry types:
 *   - DRIVER_ARGCASH_ENTRY_TYPE_STRING:   char   drv_arg$foo$s$bar[];        // == EXISTS("foo=$value") ? "$value" : "bar"
 *   - DRIVER_ARGCASH_ENTRY_TYPE_HEX:      byte_t drv_arg$foo$x$00000000[4];  // == EXISTS("foo=$value") ? tohex("$value") : tohex("00000000")
 *   - DRIVER_ARGCASH_ENTRY_TYPE_PRESENT:  bool   drv_arg$foo;                // == EXISTS("foo=$value") ? true : false
 *   - DRIVER_ARGCASH_ENTRY_TYPE_INT:      int    drv_arg$foo$d$42;           // == EXISTS("foo=$value") ? atoi("$value") : atoi("42")
 *   - DRIVER_ARGCASH_ENTRY_TYPE_UINT:     u32    drv_arg$foo$I32u$42;        // == EXISTS("foo=$value") ? atoi("$value") : atoi("42")
 *
 * NOTE: The  tohex() function is fairly simple, in that
 *       it will silently skip all non-xdigit characters
 *       during parsing! */
#define DRIVER_ARGCASH_ENTRY_TYPE_STRING  0x0000 /* String argument. */
#define DRIVER_ARGCASH_ENTRY_TYPE_HEX     0x0001 /* Hex blob. */
#define DRIVER_ARGCASH_ENTRY_TYPE_HASSIZE(x) ((x) >= DRIVER_ARGCASH_ENTRY_TYPE_PRESENT)
#define DRIVER_ARGCASH_ENTRY_TYPE_PRESENT 0x0002 /* Is-argument-present? */
#define DRIVER_ARGCASH_ENTRY_TYPE_INT     0x0003 /* Signed integer argument. */
#define DRIVER_ARGCASH_ENTRY_TYPE_UINT    0x0004 /* Unsigned integer argument. */

static intmax_t const argcash_sint_minmax[][2] = {
	/* [0] = */ { 0, 0 },
	/* [1] = */ { INT8_MIN,  INT8_MAX },
	/* [2] = */ { INT16_MIN, INT16_MAX },
	/* [3] = */ { 0, 0 },
	/* [4] = */ { INT32_MIN, INT32_MAX },
#if __SIZEOF_INTMAX_T__ > 8
	/* [5] = */ { 0, 0 },
	/* [6] = */ { 0, 0 },
	/* [7] = */ { 0, 0 },
	/* [8] = */ { INT64_MIN, INT64_MAX },
#endif /* __SIZEOF_INTMAX_T__ > 8 */
};

static uintmax_t const argcash_uint_minmax[] = {
	/* [0] = */ 0,
	/* [1] = */ UINT8_MAX,
	/* [2] = */ UINT16_MAX,
	/* [3] = */ 0,
	/* [4] = */ UINT32_MAX,
#if __SIZEOF_INTMAX_T__ > 8
	/* [5] = */ 0,
	/* [6] = */ 0,
	/* [7] = */ 0,
	/* [8] = */ UINT64_MAX,
#endif /* __SIZEOF_INTMAX_T__ > 8 */
};

/* Interpret `value' as `type' and (try) to write the  generated
 * data to `buf', returning the # of required bytes, and leaving
 * the contents of `buf' undefined when `return > bufsize'
 * NOTE: Don't use to resolve `DRIVER_ARGCASH_ENTRY_TYPE_PRESENT'! */
PRIVATE NONNULL((1, 2)) uintptr_half_t FCALL
argcash_eval(struct driver *__restrict self,
             char const *__restrict arg_name,
             byte_t *buf, uintptr_half_t bufsize,
             uintptr_half_t type, char const *value,
             char const *defl_value) {
	/* Simple case: When no value is provided, then we can
	 *              simply zero-initialize the data  blob. */
	if (!value) {
		if (type == DRIVER_ARGCASH_ENTRY_TYPE_STRING) {
			/* Special case: No value provided for a string argument
			 * requires  that  we write-back  a  zero-length string! */
			if (bufsize >= sizeof(char))
				*(char *)buf = '\0';
			return sizeof(char);
		}
		bzero(buf, bufsize);
		return bufsize;
	}

	switch (type) {

	case DRIVER_ARGCASH_ENTRY_TYPE_HEX: {
		/* For hex-argument, the required # of bytes for the hex-blob
		 * is always given by the # of hex-digits from  `defl_value'. */
		uintptr_half_t result = 0;
		if (defl_value) {
			size_t i;
			for (i = 0;; ++i) {
				char ch = defl_value[i];
				if (!ch)
					break;
				if ((ch >= '0' && ch <= '9') ||
				    (ch >= 'a' && ch <= 'f') ||
				    (ch >= 'A' && ch <= 'F'))
					++result;
			}
			result /= 2;
		}
		if (bufsize >= result) {
			/* Decode hex data from `value' */
			size_t i, dst;
			bzero(buf, result);
			for (i = 0, dst = 0; value[i]; ++i) {
				uint8_t high_nibble, low_nibble;
				char ch = value[i];
				if (ch >= '0' && ch <= '9') {
					high_nibble = ch - '0';
				} else if (ch >= 'a' && ch <= 'f') {
					high_nibble = 10 + (ch - 'a');
				} else if (ch >= 'A' && ch <= 'F') {
					high_nibble = 10 + (ch - 'A');
				} else {
					continue;
				}
				for (++i;; ++i) {
					ch = value[i];
					if (!ch) {
						printk(KERN_ERR "[mod][%s] Argument %q contains an incomplete hex-nibble in %q\n",
						       self->d_name, arg_name, value);
						THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_ARGCASH_X_BAD_NIBBLE);
					}
					if (ch >= '0' && ch <= '9') {
						low_nibble = ch - '0';
					} else if (ch >= 'a' && ch <= 'f') {
						low_nibble = 10 + (ch - 'a');
					} else if (ch >= 'A' && ch <= 'F') {
						low_nibble = 10 + (ch - 'A');
					} else {
						continue;
					}
					break;
				}

				/* Write-back the next hex-byte. */
				if (dst < result)
					buf[dst] = (high_nibble << 4) | low_nibble;
				++dst;
			}
			if (dst > result) {
				printk(KERN_ERR "[mod][%s] Argument %q requires %" PRIuSIZ " bytes, but %" PRIuSIZ " were given in %q\n",
				       self->d_name, arg_name, result, dst, value);
				THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_ARGCASH_X_TOO_LONG,
				                       result, dst);
			}
		}
		return result;
	}	break;

	case DRIVER_ARGCASH_ENTRY_TYPE_INT:
	case DRIVER_ARGCASH_ENTRY_TYPE_UINT: {
		errno_t error;
		union {
			intmax_t  im;
			uintmax_t um;
		} intval;
		if (type == DRIVER_ARGCASH_ENTRY_TYPE_INT) {
			intval.im = strtoimax_r(value, NULL, 0, &error);
			if (error == 0 && bufsize < lengthof(argcash_sint_minmax)) {
				if (intval.im < argcash_sint_minmax[bufsize][0] ||
				    intval.im > argcash_sint_minmax[bufsize][1])
					error = ERANGE;
			}
		} else {
			intval.um = strtoumax_r(value, NULL, 0, &error);
			if (error == 0 && bufsize < lengthof(argcash_uint_minmax)) {
				if (intval.um > argcash_uint_minmax[bufsize])
					error = ERANGE;
			}
		}

		/* Check for errors. */
		if (error != 0) {
			assert(error == ECANCELED || error == ERANGE || error == EINVAL);
			unsigned int reason;
			reason = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_ARGCASH_D_ECANCELED;
			if (error == ERANGE)
				reason = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_ARGCASH_D_ERANGE;
			if (error == EINVAL)
				reason = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_ARGCASH_D_EINVAL;
			THROW_FAULTY_ELF_ERROR(reason);
		}

		/* Write-back the fully parsed integer argument. */
		bzero(buf, bufsize);
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		memcpy(buf, &intval, MIN(sizeof(intval), bufsize));
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
		{
			size_t copy = MIN(sizeof(intval), bufsize);
			memcpy(buf, (byte_t *)&intval + sizeof(intval) - copy, copy);
		}
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		return bufsize;
	}	break;

	case DRIVER_ARGCASH_ENTRY_TYPE_STRING:
	default: {
		/* String argument. */
		size_t len = strlen(value);
		size_t res = (len + 1) * sizeof(char);

		/* Write-back the NUL-terminated string. */
		if (bufsize >= res)
			*(char *)mempcpy(buf, value, len, sizeof(char)) = '\0';
		return (uintptr_half_t)res;

	}	break;

	}
	return bufsize;
}

/* Check if one of the argument of `self' equals `name' */
PRIVATE ATTR_PURE WUNUSED NONNULL((1, 2)) bool
NOTHROW(FCALL driver_hasarg)(struct driver const *__restrict self,
                             char const *__restrict name) {
	size_t i;
	for (i = 0; i < self->d_argc; ++i) {
		if (strcmp(self->d_argv[i], name) == 0)
			return true;
	}
	return false;
}

/* Return  a  pointer   to  the  value-portion   of  an  argument   `name'
 * For this purpose, any of the following forms of arguments are accepted:
 *   - "$name=$value"
 *   - "$name:$value" */
PRIVATE ATTR_PURE WUNUSED NONNULL((1, 2)) char *
NOTHROW(FCALL driver_getargval)(struct driver const *__restrict self,
                                char const *__restrict name) {
	size_t i;
	size_t namelen = strlen(name);
	for (i = 0; i < self->d_argc; ++i) {
		char *arg = self->d_argv[i];
		if (bcmp(arg, name, namelen, sizeof(char)) != 0)
			continue;
		if (name[namelen] != '=' && name[namelen] != ':')
			continue;

		/* Found it! */
		return arg + namelen + 1;
	}
	return NULL;
}


struct alignas(__ALIGNOF_MAX_ALIGN_T__) driver_argcash_entry {
	size_t                        dace_next;  /* [const] Total size of this entry (in bytes) */
	uintptr_half_t                dace_type;  /* [const] Entry type (one of `DRIVER_ARGCASH_ENTRY_TYPE_*') */
	uintptr_half_t                dace_size;  /* [!0][const] Entry data size (in bytes) */
	byte_t                       *dace_data;  /* [1..dace_size][const] Entry data blob.
	                                           * Note that an effort is made to keep this pointer as close
	                                           * to  the associated driver's  load-range as possible, thus
	                                           * ensuring that use in PC-relative relocations is possible. */
	COMPILER_FLEXIBLE_ARRAY(char, dace_name); /* Name of the argument bound to this entry. */
};

struct driver_argcash {
	SLIST_ENTRY(driver_argcash) dac_link;   /* [0..1][const] Next arg$ descriptor. */
	PAGEDIR_PAGEALIGNED size_t  dac_size;   /* [const] Size of this descriptor (in bytes) */
	size_t                      dac_used;   /* [lock(:d_eh_frame_cache_lock)] # of bytes used.
	                                         * NOTE: Always aligned by `__ALIGNOF_MAX_ALIGN_T__' */
#if ((__SIZEOF_POINTER__ + __SIZEOF_SIZE_T__ * 2) % __ALIGNOF_MAX_ALIGN_T__) != 0
	byte_t                     _dac_pad[__ALIGNOF_MAX_ALIGN_T__ - ((__SIZEOF_POINTER__ + __SIZEOF_SIZE_T__ * 2) % __ALIGNOF_MAX_ALIGN_T__)];
#endif /* ((__SIZEOF_POINTER__ + __SIZEOF_SIZE_T__ * 2) % __ALIGNOF_MAX_ALIGN_T__) != 0 */
	struct driver_argcash_entry dac_ent[1]; /* First entry. */
};

/* Helper macros for locking argcash of a given driver. */
#define driver_argcash_mustreap     driver_eh_frame_cache_mustreap
#define driver_argcash_reap         driver_eh_frame_cache_reap
#define _driver_argcash_reap        _driver_eh_frame_cache_reap
#define driver_argcash_write        driver_eh_frame_cache_write
#define driver_argcash_write_nx     driver_eh_frame_cache_write_nx
#define driver_argcash_trywrite     driver_eh_frame_cache_trywrite
#define driver_argcash_endwrite     driver_eh_frame_cache_endwrite
#define _driver_argcash_endwrite    _driver_eh_frame_cache_endwrite
#define driver_argcash_read         driver_eh_frame_cache_read
#define driver_argcash_read_nx      driver_eh_frame_cache_read_nx
#define driver_argcash_tryread      driver_eh_frame_cache_tryread
#define _driver_argcash_endread     _driver_eh_frame_cache_endread
#define driver_argcash_endread      driver_eh_frame_cache_endread
#define _driver_argcash_end         _driver_eh_frame_cache_end
#define driver_argcash_end          driver_eh_frame_cache_end
#define driver_argcash_upgrade      driver_eh_frame_cache_upgrade
#define driver_argcash_upgrade_nx   driver_eh_frame_cache_upgrade_nx
#define driver_argcash_tryupgrade   driver_eh_frame_cache_tryupgrade
#define driver_argcash_downgrade    driver_eh_frame_cache_downgrade
#define driver_argcash_reading      driver_eh_frame_cache_reading
#define driver_argcash_writing      driver_eh_frame_cache_writing
#define driver_argcash_canread      driver_eh_frame_cache_canread
#define driver_argcash_canwrite     driver_eh_frame_cache_canwrite
#define driver_argcash_waitread     driver_eh_frame_cache_waitread
#define driver_argcash_waitwrite    driver_eh_frame_cache_waitwrite
#define driver_argcash_waitread_nx  driver_eh_frame_cache_waitread_nx
#define driver_argcash_waitwrite_nx driver_eh_frame_cache_waitwrite_nx


PRIVATE NONNULL((1)) struct driver_argcash *FCALL
driver_argcash_alloc(struct driver *__restrict self, size_t req_ent_size) {
	struct driver_argcash *result;
	void *kram;
	size_t minsize;
	byte_t *hint;
	minsize = offsetof(struct driver_argcash, dac_ent) + req_ent_size;
	minsize = CEIL_ALIGN(minsize, PAGESIZE);

	/* Allocate kernel ram and use the middle of the driver's
	 * load-range as the  mapping base-address hint,  meaning
	 * that the resulting mapped address will be close-by  to
	 * the driver's text  location, meaning that  it will  be
	 * most  likely that PC-relative relocations can be done. */
	hint = self->d_module.md_loadmin +
	       ((size_t)((self->d_module.md_loadmax + 1) -
	                 self->d_module.md_loadmin) /
	        2);

	/* NOTE: Also set `GFP_LOCKED' because arg$-symbols must
	 *       be  accessible  from  any  arbitrary   context! */
	kram = mman_map_kram(hint, minsize,
	                     GFP_LOCKED | GFP_PREFLT |
	                     GFP_MAP_BELOW | GFP_MAP_ABOVE);

	/* Store the arg$-table's size as the # of bytes of kram
	 * that we've just allocated. */
	result = (struct driver_argcash *)kram;
	result->dac_size = minsize;
	return result;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL driver_argcash_free)(struct driver_argcash *__restrict self) {
	mman_unmap_kram(self, self->dac_size);
}


/* Find an arg$-argument matching the given requirements.
 * If  no  such argument  exists, return  `NULL' instead. */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1, 4)) struct driver_argcash_entry *
NOTHROW(FCALL driver_argcash_find_locked)(struct driver const *__restrict self,
                                          uintptr_half_t type, uintptr_half_t size,
                                          char const *__restrict name) {
	struct driver_argcash *tab;
	SLIST_FOREACH (tab, &self->d_argcash, dac_link) {
		struct driver_argcash_entry *ent;
		byte_t *endptr = (byte_t *)tab + tab->dac_used;
		for (ent = tab->dac_ent; (byte_t *)ent < endptr;
		     ent = (struct driver_argcash_entry *)((byte_t *)ent + ent->dace_next)) {
			if (ent->dace_type != type)
				continue;
			if (strcmp(ent->dace_name, name) != 0)
				continue; /* Some other argument... */
			if (DRIVER_ARGCASH_ENTRY_TYPE_HASSIZE(type) &&
			    ent->dace_size != size)
				continue;

			/* Found it! */
			return ent;
		}
	}
	return NULL;
}

/* Try to allocate an `entsize'-large arg$-entry within `self' by
 * re-using available space  within already-existing arg$  blobs.
 * If doing so is impossible due to lack of available space, then
 * return `NULL' instead.
 * NOTE: Upon success, this function will _only_ initialize
 *       `return->dace_next'. All  other  fields  are  left
 *       uninitialized! */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) struct driver_argcash_entry *
NOTHROW(FCALL driver_argcash_alloc_locked)(struct driver *__restrict self,
                                           size_t entsize) {
	struct driver_argcash *tab;
	SLIST_FOREACH (tab, &self->d_argcash, dac_link) {
		size_t avail;
		assert(tab->dac_size >= tab->dac_used);
		avail = tab->dac_size - tab->dac_used;
		if (entsize >= avail) {
			struct driver_argcash_entry *result;

			/* Can allocate the new entry within this table! */
			result = (struct driver_argcash_entry *)((byte_t *)tab + tab->dac_used);
			tab->dac_used += entsize;

			/* Set the `dace_next'-pointer to point at the new table end. */
			result->dace_next = tab->dac_used;
			return result;
		}
	}
	return NULL;
}


/* Lookup or create a new descriptor for the named/typed `drv_arg$'-variable.
 * @param: type: One of `DRIVER_ARGCASH_ENTRY_TYPE_*'
 * @param: size: Size of the data-blob that should be referenced by the entry.
 *               Ignored for `STRING' and `HEX' entries.
 * @param: name: Name of the arg$ variable.
 * @param: defl: Default   value  string  to  interpret  for  the  variable.
 *               Ignored if the variable was already defined, as well as for
 *               `DRIVER_ARGCASH_ENTRY_TYPE_PRESENT'-style variables. May be
 *               set to `NULL' if not given.
 * @return: * : Descriptor for the variable. */
PRIVATE ATTR_NOINLINE ATTR_RETNONNULL WUNUSED NONNULL((1, 4)) struct driver_argcash_entry *FCALL
driver_argcash_lookup(struct driver *__restrict self,
                      uintptr_half_t type, uintptr_half_t size,
                      char const *__restrict name, char const *defl)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	struct driver_argcash_entry *ent;
	size_t namelen, entsize;
	byte_t *arg_data, *ent_data;
	uintptr_half_t arg_size;

	/* Step #1: Search for an existing instance of the named variable. */
	driver_argcash_read(self);
	ent = driver_argcash_find_locked(self, type, size, name);
	driver_argcash_endread(self);
	if (ent)
		return ent; /* Argument had already been accessed in the past! */

	/* Entry doesn't exist, so we need to create it.
	 * For this purpose, calculate how much memory we'll need in order to represent it! */
	namelen = strlen(name);

	/* Calculate an intermediate buffer for the arguments final encoded data value. */
	if (type == DRIVER_ARGCASH_ENTRY_TYPE_PRESENT) {
		arg_size = size;
		arg_data = (byte_t *)alloca(arg_size);
		bzero(arg_data, arg_size);
		if (driver_hasarg(self, name))
			memset(arg_data, 0xff, arg_size);
	} else {
		char const *value;
		value = driver_getargval(self, name);
		if (!value)
			value = defl;
		arg_data = NULL;
		arg_data = (byte_t *)alloca(size);
		arg_size = argcash_eval(self, name, arg_data, size, type, value, defl);
		if (arg_size > size) {
			arg_data = (byte_t *)alloca(size);
			argcash_eval(self, name, arg_data, size, type, value, defl);
		}
	}

	/* Figure out how large the actual entry needs to be. */
	entsize = offsetof(struct driver_argcash_entry, dace_name);
	entsize += (namelen + 1) * sizeof(char);
	entsize += CEIL_ALIGN(namelen, __ALIGNOF_MAX_ALIGN_T__) - 1;
	entsize &= ~(CEIL_ALIGN(namelen, __ALIGNOF_MAX_ALIGN_T__) - 1);
	entsize += arg_size;

	/* Try to create the missing arg$-argument. */
	driver_argcash_write(self);

	/* Since we've lost the lock in the mean time, we must re-check
	 * if the argument  has since been  created by another  thread. */
	ent = driver_argcash_find_locked(self, type, size, name);
	if unlikely(ent) {
		driver_argcash_endwrite(self);
		return ent; /* Argument had already been accessed in the past! */
	}

	/* Try to allocate a new entry by re-using available space. */
	ent = driver_argcash_alloc_locked(self, entsize);
	if (!ent) {
		struct driver_argcash *newtab;
		driver_argcash_endwrite(self);

		/* Allocate a new arg$ page able to hold at
		 * least  1 entry with a size of `entsize'. */
		newtab = driver_argcash_alloc(self, entsize);
		driver_argcash_write(self);
		ent = driver_argcash_find_locked(self, type, size, name);
		if unlikely(ent) {
			/* The entry has been created by another thread in the mean time... */
			driver_argcash_endwrite(self);
			driver_argcash_free(newtab);
			return ent;
		}

		/* Insert the new arg$ table into the list of tables of this driver. */
		SLIST_INSERT_HEAD(&self->d_argcash, newtab, dac_link);
		ent              = &newtab->dac_ent[0];
		newtab->dac_used = offsetof(struct driver_argcash, dac_ent) + entsize;
		ent->dace_next   = newtab->dac_used;
		assert(newtab->dac_used <= newtab->dac_size);
	}

	/* Initialize the contents of this new entry. */
	ent->dace_type = type;
	ent->dace_size = arg_size;
	ent_data = (byte_t *)ent->dace_name;
	ent_data = (byte_t *)mempcpy(ent_data, name, namelen, sizeof(char));
	*ent_data++ = '\0';
	ent_data = (byte_t *)CEIL_ALIGN((uintptr_t)ent_data, __ALIGNOF_MAX_ALIGN_T__);
	ent->dace_data = ent_data;
	memcpy(ent_data, arg_data, arg_size);
	driver_argcash_endwrite(self);
	return ent;
}


/* Resolve a `drv_arg$...'-style symbol. */
PRIVATE NONNULL((1, 2)) void FCALL
driver_argcash_resolve(struct driver *__restrict self,
                       struct driver_syminfo *__restrict info) {
	struct driver_argcash_entry *entry;
	NCX char const *uname, *unameend;
	NCX char const *utype, *utypeend;
	NCX char const *udefl, *udeflend;
	char *kname;
	uintptr_half_t arg_type;
	uintptr_half_t arg_size;

	/* Split the string at its $-bounds to get:
	 *   - The argument name
	 *   - The method by which to interpret the argument's typing (a printf-style format code)
	 *   - The default value to use if the argument wasn't given.
	 */
	uname    = info->dsi_name + 8;
	unameend = strchrnul(uname, '$');
	utype = utypeend = NULL;
	udefl = udeflend = NULL;
	if (*unameend) {
		utype    = unameend + 1;
		utypeend = strchrnul(utype, '$');
		if (*utypeend) {
			udefl    = utypeend + 1;
			udeflend = strend(udefl);
		}
	}

	arg_type = DRIVER_ARGCASH_ENTRY_TYPE_PRESENT;
	arg_size = sizeof(bool);
	if (utype) {
		NCX char const *iter;

		/* Parse the user-type string. */
		iter     = utype;
		arg_size = sizeof(int);
next_type_ch:
		if unlikely(iter >= utypeend) {
badtype:
			printk(KERN_ERR "[mod][%s] Invalid type string %$q in arg$-symbol %q",
			       self->d_name, (size_t)(utypeend - utype), utype, info->dsi_name);
			THROW(E_INVALID_ARGUMENT_UNEXPECTED_COMMAND);
		}
		switch (*iter++) {

		case 'h':
			if unlikely(iter >= utypeend)
				goto badtype;
			if (*iter == 'h') {
				++iter;
				arg_size = sizeof(char);
			} else {
				arg_size = sizeof(short);
			}
			goto next_type_ch;

		case 'l':
			if unlikely(iter >= utypeend)
				goto badtype;
			if (*iter == 'l') {
				++iter;
				arg_size = sizeof(__LONGLONG);
			} else {
				arg_size = sizeof(long);
			}
			goto next_type_ch;

		case 'I':
			arg_size = sizeof(void *);
			if unlikely(iter >= utypeend)
				goto badtype;
			if (*iter == '8') {
				++iter;
				arg_size = sizeof(int8_t);
			} else if (*iter == '1') {
				++iter;
				if unlikely(iter >= utypeend)
					goto badtype;
				if (*iter != '6')
					goto badtype;
				++iter;
				arg_size = sizeof(int16_t);
			} else if (*iter == '3') {
				++iter;
				if unlikely(iter >= utypeend)
					goto badtype;
				if (*iter != '2')
					goto badtype;
				++iter;
				arg_size = sizeof(int32_t);
			} else if (*iter == '6') {
				++iter;
				if unlikely(iter >= utypeend)
					goto badtype;
				if (*iter != '4')
					goto badtype;
				++iter;
				arg_size = sizeof(int64_t);
			} else {
				arg_size = sizeof(long);
			}
			goto next_type_ch;

		case 'z':
			arg_size = sizeof(size_t);
			goto next_type_ch;

		case 't':
			arg_size = sizeof(ptrdiff_t);
			goto next_type_ch;

		case 'L':
			arg_size = sizeof(wchar_t);
			goto next_type_ch;

		case 'j':
			arg_size = sizeof(intmax_t);
			goto next_type_ch;

		case 'd':
			arg_type = DRIVER_ARGCASH_ENTRY_TYPE_INT;
			break;

		case 'u':
			arg_type = DRIVER_ARGCASH_ENTRY_TYPE_UINT;
			break;

		case 'x':
			arg_type = DRIVER_ARGCASH_ENTRY_TYPE_HEX;
			arg_size = 0;
			break;

		case 's':
			arg_type = DRIVER_ARGCASH_ENTRY_TYPE_STRING;
			arg_size = 0;
			break;

		default:
			goto badtype;
		}
		if (iter != utypeend)
			goto badtype;
	}
	kname = (char *)malloca(((size_t)(unameend - uname) + 1) * sizeof(char));
	*(char *)mempcpy(kname, uname, (size_t)(unameend - uname), sizeof(char)) = '\0';
	{
		char *kdefl;
		kdefl = NULL;
		RAII_FINALLY {
			if (kdefl)
				freea(kdefl);
			freea(kname);
		};
		if (udefl < udeflend) {
			kdefl = (char *)malloca(((size_t)(udeflend - udefl) + 1) * sizeof(char));
			*(char *)mempcpy(kdefl, udefl, (size_t)(udeflend - udefl), sizeof(char)) = '\0';
		}
		entry = driver_argcash_lookup(self, arg_type, arg_size, kname, kdefl);
	}

	/* Write-back information from the argcash entry. */
	info->dsi_addr = entry->dace_data;
	info->dsi_size = entry->dace_size;
	info->dsi_bind = STB_GLOBAL;
}





/************************************************************************/
/* Driver symbol lookup functions                                       */
/************************************************************************/
PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) bool FCALL
driver_dlsym_drv(struct driver *__restrict self,
                 struct driver_syminfo *__restrict info)
		THROWS(E_SEGFAULT, ...) {
	NCX char const *name = info->dsi_name + 4;
	if (strcmp(name, "self") == 0) {
		info->dsi_addr = self;
		info->dsi_size = sizeof(*self);
		goto ok;
	}
	if (name[0] == 'l' && name[1] == 'o' &&
	    name[2] == 'a' && name[3] == 'd') {
		NCX char const *load_name = name + 4;
		if (strcmp(load_name, "addr") == 0) {
			info->dsi_addr = (void *)self->d_module.md_loadaddr;
			goto ok_size0;
		}
		if (strcmp(load_name, "min") == 0) {
			info->dsi_addr = self->d_module.md_loadmin;
			goto ok_size0;
		}
		if (strcmp(load_name, "max") == 0) {
			info->dsi_addr = self->d_module.md_loadmax;
			goto ok_size0;
		}
	}
	if (strcmp(name, "name") == 0) {
		info->dsi_addr = (void *)self->d_name;
		info->dsi_size = (strlen(self->d_name) + 1) * sizeof(char);
		goto ok;
	}
	if (strcmp(name, "file") == 0) {
		info->dsi_addr = driver_getfile(self);
		info->dsi_size = sizeof(void *);
		goto ok;
	}
	if (strcmp(name, "cmdline") == 0) {
		info->dsi_addr = (void *)self->d_cmdline;
		info->dsi_size = (strlen(self->d_cmdline) + 1) * sizeof(char);
		goto ok;
	}
	if (name[0] == 'a' && name[1] == 'r' && name[2] == 'g') {
		NCX char const *arg_name = name + 3;
		if (strcmp(arg_name, "c") == 0) {
			info->dsi_addr = &self->d_argc;
			info->dsi_size = sizeof(self->d_argc);
			goto ok;
		}
		if (strcmp(arg_name, "v") == 0) {
			info->dsi_addr = self->d_argv;
			info->dsi_size = self->d_argc * sizeof(char *);
			goto ok;
		}

		/* Special case: `drv_arg$...' symbols! */
		if (arg_name[0] == '$') {
			driver_argcash_resolve(self, info);
			return true;
		}
	}
	return false;
ok_size0:
	info->dsi_size = 0;
ok:
	info->dsi_bind = STB_GLOBAL;
	return true;
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) u32 FCALL
gnu_symhash(NCX char const *name) THROWS(E_SEGFAULT) {
	u32 h = 5381;
	for (; *name; ++name) {
		h = h * 33 + (u8)*name;
	}
	return h;
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) u32 FCALL
elf_symhash(NCX char const *name) THROWS(E_SEGFAULT) {
	u32 h = 0;
	while (*name) {
		u32 g;
		h = (h << 4) + *name++;
		g = h & 0xf0000000;
		if (g)
			h ^= g >> 24;
		h &= ~g;
	}
	return h;
}


struct kernel_syment {
	char const *ks_name; /* [0..1] Symbol name (NULL for sentinel) */
	void       *ks_addr; /* Symbol address */
	u32         ks_size; /* Symbol size */
	u32         ks_hash; /* Symbol hash (s.a. `elf_symhash()') */
};
struct kernel_symtab {
	uintptr_t                                     ds_mask;  /* Hash mask. */
	COMPILER_FLEXIBLE_ARRAY(struct kernel_syment, ds_list); /* Symbol map. */
};

/* The kernel symbol table (containing everything marked as PUBLIC) */
extern struct kernel_symtab kernel_symbol_table;

/* Lookup a symbol within the kernel core's symbol table. */
PRIVATE WUNUSED NONNULL((1)) bool FCALL
kernel_dlsym(struct driver_syminfo *__restrict info)
		THROWS(E_SEGFAULT, ...) {
	uint32_t hash = info->dsi_elfhash;
	uint32_t i, perturb;
	if (hash == (uint32_t)-1)
		hash = info->dsi_elfhash = elf_symhash(info->dsi_name);
	perturb = i = hash & kernel_symbol_table.ds_mask;

	/* NOTE: Changes to this algorithm must be mirrored in /src/kernel/core/.sources */
	for (;; i = ((i << 2) + i + perturb + 1), perturb >>= 5) {
		uint32_t index;
		index = i & kernel_symbol_table.ds_mask;
		if (!kernel_symbol_table.ds_list[index].ks_name)
			break; /* Sentinel */
		if (kernel_symbol_table.ds_list[index].ks_hash != hash)
			continue; /* Different hash */
		if (strcmp(kernel_symbol_table.ds_list[index].ks_name, info->dsi_name) != 0)
			continue; /* Different name */

		/* Found it! */
		info->dsi_addr = kernel_symbol_table.ds_list[index].ks_addr;
		info->dsi_size = kernel_symbol_table.ds_list[index].ks_size;
		info->dsi_bind = STB_GLOBAL;
		return true;
	}
	return false;
}

#if ELF_ARCH_CLASS == ELFCLASS32
#define ELF_CLASSBITS 32
#elif ELF_ARCH_CLASS == ELFCLASS64
#define ELF_CLASSBITS 64
#else /* ELF_ARCH_CLASS == ... */
#define ELF_CLASSBITS (__SIZEOF_POINTER__ * 8)
#endif /* ELF_ARCH_CLASS != ... */


PRIVATE ATTR_COLD ATTR_NOINLINE NONNULL((1, 2)) void FCALL
print_corrupted_symbol_table_error_message(struct driver *__restrict self,
                                           char const *__restrict kind) {
	printk(KERN_ERR "[mod] %s symbol hash table of ", kind);
	module_printpath_or_name(&self->d_module, &syslog_printer, SYSLOG_LEVEL_ERR);
	printk(KERN_ERR "is corrupt\n");
}

/* Lookup a symbol from the ELF .dynsym section. */
PRIVATE WUNUSED NONNULL((1, 2)) ElfW(Sym) const *FCALL
driver_dlsym_elf(struct driver *__restrict self,
                 struct driver_syminfo *__restrict info)
		THROWS(E_SEGFAULT, ...) {
	ElfW(Sym) const *result;

	/************************************************************************/
	/* GNU hash table support                                               */
	/************************************************************************/
	if (self->d_gnuhashtab) {
		/* This implementation is derived from:
		 * https://flapenguin.me/2017/05/10/elf-lookup-dt-gnu-hash/
		 * https://sourceware.org/ml/binutils/2006-10/msg00377.html
		 */
		ElfW(GnuHashTable) const *gnu_ht;
		ElfW(Word) symid, gh_symoffset;
		ElfW(Word) const *gh_buckets;
		ElfW(Word) const *gh_chains;
		ElfW(Addr) bloom_word, bloom_mask;
		uint32_t hash;
		gnu_ht = self->d_gnuhashtab;
		hash   = info->dsi_gnuhash;
		if (hash == (uint32_t)-1)
			hash = info->dsi_gnuhash = gnu_symhash(info->dsi_name);
		if unlikely(!gnu_ht->gh_bloom_size || !gnu_ht->gh_bloom_size)
			goto nosym_no_gnu_ht;
		gh_symoffset = gnu_ht->gh_symoffset;
		gh_buckets   = (ElfW(Word) const *)(gnu_ht->gh_bloom + gnu_ht->gh_bloom_size);
		gh_chains    = (ElfW(Word) const *)(gh_buckets + gnu_ht->gh_nbuckets);
		bloom_word   = gnu_ht->gh_bloom[(hash / ELF_CLASSBITS) % gnu_ht->gh_bloom_size];
		bloom_mask   = ((ElfW(Addr))1 << (hash % ELF_CLASSBITS)) |
		               ((ElfW(Addr))1 << ((hash >> gnu_ht->gh_bloom_shift) % ELF_CLASSBITS));
		if ((bloom_word & bloom_mask) != bloom_mask)
			goto nosym;
		symid = gh_buckets[hash % gnu_ht->gh_nbuckets];
		if unlikely(symid < gh_symoffset)
			goto nosym;

		/* Search for the symbol. */
		for (;; ++symid) {
			ElfW(Word) enthash;
			result  = self->d_dynsym_tab + symid;
			enthash = gh_chains[symid - gh_symoffset];
			if likely((hash | 1) == (enthash | 1)) {
				if likely(strcmp(info->dsi_name, self->d_dynstr + result->st_name) != 0)
					return result; /* Found it! */
			}
			if unlikely(enthash & 1)
				break; /* End of chain */
		}
		goto nosym;
	}

	/************************************************************************/
	/* ELF hash table support                                               */
	/************************************************************************/
search_elf_table:
	if (self->d_hashtab) {
		ElfW(HashTable) const *elf_ht;
		ElfW(Word) const *ht_chains;
		ElfW(Word) max_attempts, chain;
		uint32_t hash;
		elf_ht = self->d_hashtab;
		hash   = info->dsi_elfhash;
		if (hash == (uint32_t)-1)
			hash = info->dsi_elfhash = elf_symhash(info->dsi_name);
		if unlikely(!elf_ht->ht_nbuckts || !elf_ht->ht_nchains)
			goto nosym_no_elf_ht;
		max_attempts = elf_ht->ht_nchains;
		ht_chains    = elf_ht->ht_table + elf_ht->ht_nbuckts;
		chain        = elf_ht->ht_table[hash % elf_ht->ht_nbuckts];
		do {
			if unlikely(chain == STN_UNDEF)
				break; /* End of chain. */
			if unlikely(chain >= elf_ht->ht_nchains)
				goto nosym_no_elf_ht; /* Corrupted hash-table */
			result = self->d_dynsym_tab + chain;
			if likely(strcmp(info->dsi_name, self->d_dynstr + result->st_name) == 0)
				return result; /* Found it! */

			/* Load the next chain entry. */
			chain = ht_chains[chain];
		} while likely(--max_attempts);
		goto nosym;
	}

	/************************************************************************/
	/* Do a linear search over the symbol table.                            */
	/************************************************************************/
search_dynsym:
	if (self->d_dynsym_tab) {
		ElfW(Sym) const *dynsym;
		size_t i, dyncnt;
		dynsym = self->d_dynsym_tab;
		dyncnt = self->d_dynsym_cnt;
		for (i = 0; i < dyncnt; ++i) {
			char const *symname;
			symname = self->d_dynstr + dynsym[i].st_name;
			if (strcmp(info->dsi_name, symname) != 0)
				continue;
			/* Found it! */
			return &dynsym[i];
		}
	}
nosym:
	return NULL;

nosym_no_gnu_ht:
	print_corrupted_symbol_table_error_message(self, "GNU");
	self->d_gnuhashtab = NULL;
	goto search_elf_table;

nosym_no_elf_ht:
	print_corrupted_symbol_table_error_message(self, "ELF");
	self->d_hashtab = NULL;
	goto search_dynsym;
}




#ifndef CONFIG_NO_SMP
/* Lock that must be held while reading/writing the `st_value'
 * field  of any driver symbol using one of the indirect types
 * `STT_GNU_IFUNC' and `STT_KOS_IDATA'
 *
 * Note that this is an SMP-lock! */
PRIVATE struct atomic_lock driver_isym_lock = ATOMIC_LOCK_INIT;
#endif /* !CONFIG_NO_SMP */
#define driver_isym_acquire() atomic_lock_acquire_smp(&driver_isym_lock)
#define driver_isym_release() atomic_lock_release_smp(&driver_isym_lock)
#define driver_isym_break()   atomic_lock_release_smp_b(&driver_isym_lock)


/* Copy data to physical memory located at the virtual
 * address that `dst' points to. This in turns  allows
 * writes  to virtual memory that'd otherwise be read-
 * only. */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL copy_to_phys_of_virt)(void const *dst,
                                    void const *src,
                                    size_t num_bytes) {
	while (num_bytes) {
		physaddr_t phys_dst;
		size_t maxbytes;
		phys_dst = pagedir_translate(dst);
		maxbytes = PAGESIZE - ((uintptr_t)dst & PAGEMASK);
		if (maxbytes > num_bytes)
			maxbytes = num_bytes;
		copytophys_onepage(phys_dst, src, maxbytes);
		if (maxbytes >= num_bytes)
			break;
		dst = (byte_t const *)dst + maxbytes;
		src = (byte_t const *)src + maxbytes;
		num_bytes -= maxbytes;
	}
}

PRIVATE NONNULL((1, 2, 3)) void FCALL
resolve_elf_symbol(struct driver *__restrict self,
                   struct driver_syminfo *__restrict info,
                   ElfW(Sym) const *__restrict symbol)
		THROWS(E_SEGFAULT, ...) {
	ElfW(Addr) st_addr;
	unsigned char st_info;
	st_info = read_once(&symbol->st_info);
	if (ELFW(ST_TYPE)(st_info) == STT_GNU_IFUNC ||
	    ELFW(ST_TYPE)(st_info) == STT_KOS_IDATA) {
		ElfW(Addr) newaddr;
		unsigned char newinfo;

		/* Special case: Indirect symbol! */
		driver_isym_acquire();
		st_info = symbol->st_info;
		st_addr = symbol->st_value;
		driver_isym_release();
		if unlikely(ELFW(ST_TYPE)(st_info) != STT_GNU_IFUNC &&
		            ELFW(ST_TYPE)(st_info) != STT_KOS_IDATA)
			goto normal_symbol;
		if (symbol->st_shndx != SHN_ABS)
			st_addr += self->d_module.md_loadaddr;

		/* Resolve dynamic address. */
		st_addr = (*(ElfW(Addr)(*)(void))(void *)st_addr)();

		/* Write-back the resolved address, and change
		 * the typing of  the symbol to  no longer  be
		 * indirect! */
		newaddr = st_addr;
		if (symbol->st_shndx != SHN_ABS)
			newaddr -= self->d_module.md_loadaddr;
		newinfo = ELFW(ST_INFO)(ELFW(ST_BIND)(st_info),
		                        ELFW(ST_TYPE)(st_info) == STT_GNU_IFUNC
		                        ? STT_FUNC
		                        : STT_OBJECT);

		/* Check if we're still dealing with an indirect symbol.
		 * if that's no longer the case, then we must abort, and
		 * discard the results we got from calling the  indirect
		 * function! */
		driver_isym_acquire();
		st_info = symbol->st_info;
		if unlikely(ELFW(ST_TYPE)(st_info) != STT_GNU_IFUNC &&
		            ELFW(ST_TYPE)(st_info) != STT_KOS_IDATA) {
			driver_isym_break();
			goto normal_symbol;
		}

		/* _VERY_ important! must write `st_info' second, since knowing
		 * that it indicates an  indirect symbol, `st_value' is  _only_
		 * guarded against reads/writes  from other cpus/threads  while
		 * that's still the case.
		 * As such, the write to `st_value' _must_ happen _before_ the
		 * write to `st_info'. - Otherwise this'd be a race condition! */
		COMPILER_BARRIER();
		copy_to_phys_of_virt(&symbol->st_value, &newaddr, sizeof(symbol->st_value));
		COMPILER_BARRIER();
		copy_to_phys_of_virt(&symbol->st_info, &newinfo, sizeof(symbol->st_info));
		COMPILER_BARRIER();
		driver_isym_release();
		/* XXX: Do we need to do some explicit cache flushing here? */
		/* XXX: Why not just temporarily try to remap the pagedir for write?
		 *      Then we  can just  write to  the normal  virtual  address... */
	} else {
normal_symbol:
		st_addr = symbol->st_value;
		if (symbol->st_shndx != SHN_ABS)
			st_addr += self->d_module.md_loadaddr;
	}
	info->dsi_addr = (void *)st_addr;
	info->dsi_size = symbol->st_size;
	info->dsi_bind = ELFW(ST_BIND)(st_info);
}


/* Lookup a symbol  within a driver,  given its  name.
 * Note that this function will _not_ look into driver
 * dependencies in order to resolve that symbol.
 * NOTE: This function also takes care of the special
 *       set of `drv_*' symbols!
 * @return: true:  Found a symbol matching the given name.
 * @return: false: No symbol matching the given name found. */
PUBLIC BLOCKING WUNUSED NONNULL((1, 2)) bool FCALL
driver_dlsym_local(struct driver *__restrict self,
                   struct driver_syminfo *__restrict info)
		THROWS(E_SEGFAULT, ...) {
	ElfW(Sym) const *symbol;

	/* Check for special symbols from the `drv_*' namespace. */
	if (info->dsi_name[0] == 'd' && info->dsi_name[1] == 'r' &&
	    info->dsi_name[2] == 'v' && info->dsi_name[3] == '_') {
		if (driver_dlsym_drv(self, info))
			return true;
	}

	/* Check for the special case with the kernel core. */
	if (self == &kernel_driver)
		return kernel_dlsym(info);

	/* Do a generic ELF .dynsym lookup. */
	symbol = driver_dlsym_elf(self, info);
	if (symbol && symbol->st_shndx != SHN_UNDEF) {
		resolve_elf_symbol(self, info, symbol);
		return true;
	}
	return false;
}



#define DRIVER_DLSYM_EX_NOENT 0 /* Symbol not found */
#define DRIVER_DLSYM_EX_OK    1 /* Success */
#define DRIVER_DLSYM_EX_EOF   2 /* No drivers found at `depth' */

PRIVATE BLOCKING WUNUSED NONNULL((1, 2, 3)) unsigned int FCALL
driver_dlsym_ex(struct driver *__restrict self,
                struct driver_syminfo *__restrict info,
                REF struct driver **__restrict p_driver,
                unsigned int depth)
		THROWS(E_SEGFAULT, ...) {
	unsigned int result, status;
	size_t i;
	if (depth == 0) {
		if (driver_dlsym_local(self, info)) {
			*p_driver = incref(self);
			return DRIVER_DLSYM_EX_OK;
		}
		return DRIVER_DLSYM_EX_NOENT;
	}
	--depth;
	result = DRIVER_DLSYM_EX_EOF;
	for (i = 0; i < self->d_depcnt; ++i) {
		REF struct driver *dep;
		dep = axref_get(&self->d_depvec[i]);
		if (!dep)
			continue;
		{
			FINALLY_DECREF_UNLIKELY(dep);
			status = driver_dlsym_ex(dep, info, p_driver, depth);
		}
		if (status != DRIVER_DLSYM_EX_EOF) {
			result = status;
			if (result == DRIVER_DLSYM_EX_OK)
				break;
		}
	}
	return result;
}

PRIVATE NOBLOCK WUNUSED unsigned int
NOTHROW(FCALL get_max_dependency_depth)(void) {
	unsigned int result;
	REF struct driver_loadlist *ll;
	ll     = get_driver_loadlist();
	result = (unsigned int)ll->dll_count;
	decref_unlikely(ll);
	return result;
}

/* Same  as `driver_dlsym_local()', but if that function fails,
 * or  returns a weak  symbol, scan all  of the dependencies of
 * `self'  for another symbol with the same name. If a non-weak
 * symbol is found return it. Otherwise, return the first  weak
 * symbol encountered during the search, and if all that fails,
 * return `false' to indicate failure.
 * @return: *   : Found a symbol matching the given name in this driver.
 * @return: NULL: No symbol matching the given name found. */
PUBLIC BLOCKING WUNUSED NONNULL((1, 2)) REF struct driver *FCALL
driver_dlsym(struct driver *__restrict self,
             struct driver_syminfo *__restrict info)
		THROWS(E_SEGFAULT, ...) {
	unsigned int status, depth, max_depth;
	struct driver *resdrv = self;
	bool result = driver_dlsym_local(self, info);

	/* All drivers have an implicit dependency on the kernel core! */
	if (!result) {
		resdrv = &kernel_driver;
		result = kernel_dlsym(info);
	}
	if (!result) {
		max_depth = get_max_dependency_depth();
		for (depth = 0; depth < max_depth; ++depth) {
			status = driver_dlsym_ex(self, info, &resdrv, depth);
			if (status != DRIVER_DLSYM_EX_NOENT) {
				if (status == DRIVER_DLSYM_EX_OK) {
					if (info->dsi_bind == STB_WEAK) {
						++depth;
						goto find_nonweak_after;
					}
					return resdrv;
				}
				break;
			}
		}
		return NULL;
	}
	incref(resdrv);
	if (info->dsi_bind == STB_WEAK) {
		REF struct driver *drv2;
		struct driver_syminfo info2;
		depth     = 0;
		max_depth = get_max_dependency_depth();
find_nonweak_after:
		info2.dsi_name    = info->dsi_name;
		info2.dsi_elfhash = info->dsi_elfhash;
		info2.dsi_gnuhash = info->dsi_gnuhash;
		for (; depth < max_depth; ++depth) {
			status = driver_dlsym_ex(self, &info2, &drv2, depth);
			if (status != DRIVER_DLSYM_EX_NOENT) {
				if (status == DRIVER_DLSYM_EX_EOF)
					break;
				assert(status == DRIVER_DLSYM_EX_OK);
				if (info2.dsi_bind == STB_WEAK) {
					/* Another weak symbol (skip; we only ever use the first one found!) */
					decref_unlikely(drv2);
					continue;
				}
				info->dsi_addr = info2.dsi_addr;
				info->dsi_size = info2.dsi_size;
				info->dsi_bind = info2.dsi_bind;
				decref_unlikely(resdrv);
				return drv2;
			}
		}
	}
	return resdrv;
}

/* Search for a symbol in all loaded drivers, following the order
 * of drivers, as they appear returned by `get_driver_loadlist()'
 * @return: *   : Found a symbol matching the given name in this driver.
 * @return: NULL: No symbol matching the given name found. */
PUBLIC BLOCKING WUNUSED NONNULL((1)) REF struct driver *FCALL
driver_dlsym_global(struct driver_syminfo *__restrict info)
		THROWS(E_SEGFAULT, ...) {
	size_t i;
	REF struct driver_loadlist *ll;
	ll = get_driver_loadlist();
	FINALLY_DECREF_UNLIKELY(ll);
	assert_assume(ll->dll_count >= 1);
	for (i = 0; i < ll->dll_count; ++i) {
		bool ok;
		REF struct driver *d;
		d = ll->dll_drivers[i];
		if (!tryincref(d))
			continue;
		TRY {
			ok = driver_dlsym_local(d, info);
		} EXCEPT {
			decref_unlikely(d);
			RETHROW();
		}
		if (!ok) {
			decref_unlikely(d);
			continue;
		}
		if (info->dsi_bind == STB_WEAK) {
			/* Try to find another driver that may define this symbol as non-weak! */
			struct driver_syminfo info2;
			info2.dsi_name    = info->dsi_name;
			info2.dsi_elfhash = info->dsi_elfhash;
			info2.dsi_gnuhash = info->dsi_gnuhash;
			for (++i; i < ll->dll_count; ++i) {
				REF struct driver *d2;
				d2 = ll->dll_drivers[i];
				if (!tryincref(d2))
					continue;
				TRY {
					ok = driver_dlsym_local(d, &info2);
				} EXCEPT {
					decref_unlikely(d2);
					decref_unlikely(d);
					RETHROW();
				}

				/* Only accept non-weak symbols at this point! */
				if (!ok || info2.dsi_bind == STB_WEAK) {
					decref_unlikely(d2);
					continue;
				}

				/* Found a non-weak symbol! */
				info->dsi_addr = info2.dsi_addr;
				info->dsi_size = info2.dsi_size;
				info->dsi_bind = info2.dsi_bind;
				decref_unlikely(d);
				return d2;
			}
		}
		return d;
	}
	return NULL;
}

/* Helper wrappers for the above functions that simply take the
 * name of the symbol and will return its address, or `NULL' if
 * no such symbol could be found. */
PUBLIC BLOCKING WUNUSED NONNULL((1)) void *FCALL
driver_dlsym_local_f(struct driver *__restrict self,
                     NCX char const *name)
		THROWS(E_SEGFAULT, ...) {
	struct driver_syminfo info;
	driver_syminfo_init(&info, name);
	if (!driver_dlsym_local(self, &info))
		info.dsi_addr = NULL;
	return info.dsi_addr;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL driver_destroy)(struct driver *__restrict self);

PUBLIC BLOCKING WUNUSED NONNULL((1)) void *FCALL
driver_dlsym_f(struct driver *__restrict self,
               NCX char const *name)
		THROWS(E_SEGFAULT, ...) {
	struct driver_syminfo info;
	REF struct driver *drv;
	driver_syminfo_init(&info, name);
again:
	drv = driver_dlsym(self, &info);
	if (drv) {
		if unlikely(atomic_decfetch(&drv->d_module.md_refcnt) == 0) {
			driver_destroy(drv);
			goto again;
		}
	} else {
		info.dsi_addr = NULL;
	}
	return info.dsi_addr;
}

PUBLIC BLOCKING WUNUSED void *FCALL
driver_dlsym_global_f(NCX char const *name)
		THROWS(E_SEGFAULT, ...) {
	struct driver_syminfo info;
	REF struct driver *drv;
	driver_syminfo_init(&info, name);
again:
	drv = driver_dlsym_global(&info);
	if (drv) {
		if unlikely(atomic_decfetch(&drv->d_module.md_refcnt) == 0) {
			driver_destroy(drv);
			goto again;
		}
	} else {
		info.dsi_addr = NULL;
	}
	return info.dsi_addr;
}



PRIVATE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL kernel_dladdr)(struct driver_symaddr *__restrict info,
                             void const *addr) {
	uintptr_t i;
	for (i = 0; i <= kernel_symbol_table.ds_mask; ++i) {
		void *end;
		if ((byte_t *)kernel_symbol_table.ds_list[i].ks_addr > (byte_t *)addr)
			continue;
		end = (void *)((uintptr_t)kernel_symbol_table.ds_list[i].ks_addr +
		               kernel_symbol_table.ds_list[i].ks_size);
		if ((byte_t *)addr >= (byte_t *)end)
			continue;
		/* Found it! */
		info->dsa_addr = kernel_symbol_table.ds_list[i].ks_addr;
		info->dsa_size = kernel_symbol_table.ds_list[i].ks_size;
		info->dsa_name = kernel_symbol_table.ds_list[i].ks_name;
		info->dsa_bind = STB_GLOBAL;
		return true;
	}
	return false;
}

PRIVATE NOBLOCK WUNUSED NONNULL((1)) ElfW(Sym) const *
NOTHROW(FCALL driver_dladdr_elf)(struct driver *__restrict self,
                                 uintptr_t driver_reladdr) {
	size_t i, count;
	ElfW(Sym) const *result;
	uintptr_t prev_symbol_end;
	count = self->d_dynsym_cnt;

	/* First pass: Search for a symbol that contains the given address exactly. */
	for (i = 0; i < count; ++i) {
		result = &self->d_dynsym_tab[i];
		if (result->st_shndx == SHN_UNDEF ||
		    result->st_shndx == SHN_ABS)
			continue;
		if (result->st_value > driver_reladdr)
			continue;
		if (result->st_value == driver_reladdr)
			return result; /* Exact match */
		if (result->st_size != 0) {
			/* Symbol has a defined size value. */
			if (driver_reladdr < (result->st_value + result->st_size))
				return result; /* The given address is contained within this one. */
		}
	}

	/* Second pass: Search for the nearest open-ended symbol defined below `driver_reladdr' */
	prev_symbol_end = 0;
	result = NULL;
	for (i = 0; i < count; ++i) {
		ElfW(Sym) const *sym;
		sym = &self->d_dynsym_tab[i];
		if (sym->st_shndx == SHN_UNDEF ||
		    sym->st_shndx == SHN_ABS)
			continue;
		if (sym->st_value > driver_reladdr)
			continue;
		if (result->st_size != 0) {
			uintptr_t symend;
			symend = result->st_value + result->st_size;
			assertf(symend <= driver_reladdr,
			        "Otherwise, the symbol would be a perfect match, which "
			        "we would have already detected during the first pass");
			if (symend > prev_symbol_end) {
				/* Closer matching symbol. */
				prev_symbol_end = symend;
				result          = NULL; /* Closed end */
			}
		} else if (sym->st_value > prev_symbol_end) {
			/* Open-ended symbol above previous symbol.
			 * Use this one unless we find another one that's closer. */
			prev_symbol_end = sym->st_value;
			result          = sym;
		}
	}
	assert(!result || (result->st_shndx != SHN_UNDEF &&
	                   result->st_shndx != SHN_ABS));
	assert(!result || result->st_size == 0);
	assert(!result || result->st_value < driver_reladdr);
	return result;
}

/* Do the reverse of the `driver_dlsym()' functions above, and resolve
 * a driver-relative `driver_reladdr' to  try to determine info  about
 * the symbol that contains that address.
 * @return: true:  Success.
 * @return: false: Failure. */
PUBLIC NOBLOCK WUNUSED NONNULL((1, 3)) bool
NOTHROW(FCALL driver_dladdr_local)(struct driver *__restrict self,
                                   uintptr_t driver_reladdr,
                                   struct driver_symaddr *__restrict info) {
	ElfW(Sym) const *symbol;

	/* Special case for the kernel core. */
	if (self == &kernel_driver)
		return kernel_dladdr(info, (void *)driver_reladdr);

	/* Do a generic ELF .dynsym lookup. */
	symbol = driver_dladdr_elf(self, driver_reladdr);
	if (symbol) {
		info->dsa_addr = (void *)(self->d_module.md_loadaddr + symbol->st_value);
		info->dsa_size = symbol->st_size;
		info->dsa_name = self->d_dynstr + symbol->st_name;
		info->dsa_bind = ELFW(ST_BIND)(symbol->st_info);
		return true;
	}
	return false;
}

/* Similar to `driver_dladdr_local()', but uses `driver_fromaddr()'
 * to lookup the module containing  `addr', and follows this up  by
 * using `driver_dladdr_local()' */
PUBLIC NOBLOCK WUNUSED NONNULL((2)) REF struct driver *
NOTHROW(FCALL driver_dladdr)(void const *addr,
                             struct driver_symaddr *__restrict info) {
	REF struct driver *drv;
	drv = driver_fromaddr(addr);
	if (!drv)
		return NULL;
	if (!driver_dladdr_local(drv,
	                         (uintptr_t)addr - drv->d_module.md_loadaddr,
	                         info)) {
		decref_unlikely(drv);
		drv = NULL;
	}
	return drv;
}


/* FDE Cache API */
struct driver_fde_cache {
	unwind_fde_t                    dfc_fde;    /* Cached FDE */
	size_t                          dfc_heapsz; /* Allocated heap size (least significant bit is R/B-bit; 0:black; 1:red) */
	LLRBTREE_NODE(driver_fde_cache) dfc_node;   /* R/B-node */
};
#define driver_fde_cache_heapsz(self) ((self)->dfc_heapsz & ~1)

DECL_END

#define RBTREE_LEFT_LEANING
#define RBTREE_OMIT_REMOVE
#define RBTREE_OMIT_REMOVENODE
#define RBTREE_OMIT_INSERT
#define RBTREE_WANT_TRYINSERT
#define RBTREE_DECL            PRIVATE
#define RBTREE_IMPL            PRIVATE
#define RBTREE(name)           dfc_##name
#define RBTREE_T               struct driver_fde_cache
#define RBTREE_Tkey            void const *
#define RBTREE_CC              FCALL
#define RBTREE_NOTHROW         NOTHROW
#define RBTREE_NODEFIELD       dfc_node
#define RBTREE_REDFIELD        dfc_heapsz
#define RBTREE_REDBIT          0x1
#define RBTREE_GETNODE(self)   (self)->dfc_node
#define RBTREE_GETMINKEY(node) (node)->dfc_fde.f_pcstart
#define RBTREE_GETMAXKEY(node) ((byte_t *)(node)->dfc_fde.f_pcend - 1)
#include <hybrid/sequence/rbtree-abi.h>

DECL_BEGIN

INTERN ATTR_USED NOBLOCK NONNULL((1)) size_t
NOTHROW(FCALL dfc_freetree)(struct driver_fde_cache *__restrict tree) {
	size_t result, temp;
	struct driver_fde_cache *mi, *ma;
	result = 0;
again:
	mi   = tree->dfc_node.rb_lhs;
	ma   = tree->dfc_node.rb_rhs;
	temp = driver_fde_cache_heapsz(tree);
	result += temp;
	heap_free_untraced(&kernel_locked_heap, tree, temp, GFP_LOCKED);
	if (mi) {
		if (ma)
			result += dfc_freetree(ma);
		tree = mi;
		goto again;
	}
	if (ma) {
		tree = ma;
		goto again;
	}
	return result;
}


/* Lookup  the FDE descriptor for a given `absolute_pc',
 * whilst trying to make use of the FDE cache of `self'.
 * @return: * : One of `UNWIND_*' from <libunwind/errno.h> */
PUBLIC NOBLOCK NONNULL((1)) unwind_errno_t
NOTHROW(FCALL driver_findfde)(struct driver *__restrict self, void const *absolute_pc,
                              unwind_fde_t *__restrict result) {
	unwind_errno_t status;

	/* Try to look through the driver's FDE cache for a descriptor. */
	if (driver_eh_frame_cache_tryread(self)) {
		struct driver_fde_cache *cache;
		cache = dfc_locate(self->d_eh_frame_cache, absolute_pc);
		if (cache) {
			memcpy(result, &cache->dfc_fde, sizeof(unwind_fde_t));
			driver_eh_frame_cache_endread(self);
			return UNWIND_SUCCESS;
		}
		driver_eh_frame_cache_endread(self);
	}

	/* Scan the .eh_frame section of the driver. */
	result->f_tbase = NULL; /* Lazily loaded (if needed) */
	result->f_dbase = NULL; /* Lazily loaded (if needed) */
	status = unwind_fde_scan(self->d_eh_frame_start,
	                         self->d_eh_frame_end,
	                         absolute_pc, result,
	                         sizeof(void *));

	/* Try to cache the results  upon success, but don't do  so
	 * if the kernel's been poisoned, or trying to the lock the
	 * cache for writing would most likely block. */
	if likely(status == UNWIND_SUCCESS && !kernel_poisoned() &&
	          driver_eh_frame_cache_canwrite(self)) {
		heapptr_t cp;
		assert(absolute_pc >= result->f_pcstart);
		assert(absolute_pc < result->f_pcend);
		cp = heap_alloc_untraced_nx(&kernel_locked_heap,
		                            sizeof(struct driver_fde_cache),
		                            GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT);
		if (heapptr_getsiz(cp) != 0) {
			struct driver_fde_cache *cache;
			cache = (struct driver_fde_cache *)heapptr_getptr(cp);
			memcpy(&cache->dfc_fde, result, sizeof(unwind_fde_t));
			cache->dfc_heapsz = heapptr_getsiz(cp);
			if likely(driver_eh_frame_cache_trywrite(self)) {
				bool ok;

				/* Try to insert the entry into the cache. */
				ok = dfc_tryinsert(&self->d_eh_frame_cache, cache);
				driver_eh_frame_cache_endwrite(self);
				if unlikely(!ok)
					goto cannot_cache;
			} else {
cannot_cache:
				heap_free_untraced(&kernel_locked_heap,
				                   heapptr_getptr(cp), heapptr_getsiz(cp),
				                   GFP_LOCKED);
			}
		}
	}
	return status;
}



/* NOTE: This function is normally part of libunwind, but in kernel-space
 *       is implemented here so-as to allow for per-driver caching of FDE
 *       descriptors. */

/* Lookup FDE information  associated with a  given program counter  position.
 * Using integration with KOS's DL extension APIs, this function automatically
 * accesses the `.eh_frame' sections of  the module associated with the  given
 * address, as well as  keep track of a  lazily allocated address-tree of  FDE
 * caches for quick (O(log2)) repeated access to an FDE located within a known
 * function. */
DEFINE_PUBLIC_ALIAS(unwind_fde_find, libuw_unwind_fde_find);
INTERN NOBLOCK NONNULL((2)) unwind_errno_t
NOTHROW_NCX(KCALL libuw_unwind_fde_find)(VIRT void const *absolute_pc,
                                         unwind_fde_t *__restrict result) {
	unwind_errno_t error;
	REF struct driver *d;

	/* Figure out which driver is mapped at the given `absolute_pc' */
	d = driver_fromaddr(absolute_pc);
	if unlikely(!d)
		return UNWIND_NO_FRAME;

	/* Lookup the FDE descriptor within the driver */
	error = driver_findfde(d, absolute_pc, result);
	decref_unlikely(d);
	return error;
}








/************************************************************************/
/* Driver load/unload functions                                         */
/************************************************************************/

/* Signal broadcast whenever the `d_state' of any loaded driver changes. */
PUBLIC struct sig driver_state_changed = SIG_INIT;

/* Perform the necessary actions after the state of
 * `self' has been set to `DRIVER_STATE_FINI_DEPS'. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL driver_runstate_fini_deps)(struct driver *__restrict self) {
	size_t i;

	/* Go over all dependencies and clear them. */
	for (i = 0; i < self->d_depcnt; ++i)
		axref_clear(&self->d_depvec[i]);

	/* Drop the self-reference that was held by the
	 * driver's state being `!= DRIVER_STATE_KILL'. */
	atomic_write(&self->d_state, DRIVER_STATE_KILL);
	decref_nokill(self);
	sig_broadcast(driver_changesignal(self));
}


/* Initialize driver dependencies. */
PRIVATE BLOCKING NONNULL((1)) void FCALL
driver_runstate_init_deps(struct driver *__restrict self)
		THROWS(...) {
	ElfW(Dyn) const *elf_dynamic;
	size_t i, elf_dynsize, dst = 0;
	elf_dynamic = self->d_dynhdr;
	elf_dynsize = self->d_dyncnt;
	for (i = 0; i < elf_dynsize; ++i) {
		char const *filename;
		REF struct driver *dependency;
		if (elf_dynamic[i].d_tag != DT_NEEDED)
			continue; /* We only care about dependencies! */
		if unlikely(dst >= self->d_depcnt)
			THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_NEEDED, dst);
		filename = self->d_dynstr + elf_dynamic[i].d_un.d_ptr;
		if unlikely(filename < self->d_dynstr || filename >= self->d_dynstr_end)
			THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_NEEDED, dst);

		/* Check  for  special case:  loading driver  dependencies before
		 * the root filesystem has been mounted (i.e. bootloader drivers) */
		if unlikely(!atomic_read_relaxed(&vfs_kernel.vf_root)) {
			dependency = driver_fromname(filename);
			if unlikely(!dependency) {
				char const *name;

				/* We  get here if  a driver loaded  as a bootloader module
				 * required another driver as a dependency, with that other
				 * driver not having been provided in the same manner.
				 *
				 * In  this case, tell the user that they've booted KOS in
				 * an impossible configuration, also informing them of the
				 * missing driver.
				 *
				 * Note that when built with the builtin debugger enabled,
				 * the user will even be prompted with a really nice error
				 * message! ;) */
				name = strchr(filename, '/');
				name = name ? name + 1 : filename;
				dependency = driver_fromname(name);
				if unlikely(!dependency) {
					kernel_panic("Cannot load dependency %q of driver %q\n"
					             "Consider starting KOS with the dependency as a boot-module",
					             name, self->d_name);
				}
			}

			/* Make sure that the dependency has been initialized.
			 * This way, bootloader drivers are always initialized
			 * boot-up, no matter the order.
			 * Only in the case of circular dependencies can  the
			 * initialization order be affected by load ordering! */
			if likely(dependency)
				driver_initialize(dependency);
		} else {
			/* Recursively load the dependent driver. */
			dependency = driver_insmod(filename);
		}

		/* Write the dependency back into the vector of dependencies. */
		axref_set_inherit(&self->d_depvec[dst], dependency);
		++dst;
	}
	if unlikely(dst < self->d_depcnt)
		THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_NEEDED, dst);
}


/* Remove write-permissions from normally read-only program headers
 * that had none-the-less been mapped  as writable for the sake  of
 * allowing TEXT-relocations to be applied.
 * This function is called during driver initialization once driver
 * relocations have being applied. */
PRIVATE NONNULL((1)) void FCALL
driver_disable_textrel(struct driver *__restrict self)
		THROWS(E_WOULDBLOCK) {
	ElfW(Half) i;
	bool haslock  = false;
	bool mustsync = false;
	for (i = 0; i < self->d_phnum; ++i) {
		struct mnode_tree_minmax mima;
		struct mnode *node;
		byte_t const *phdr_minaddr;
		byte_t const *phdr_maxaddr;
		if (self->d_phdr[i].p_type != PT_LOAD)
			continue; /* Not a load header */
		if (self->d_phdr[i].p_flags & PF_W)
			continue; /* This one's supposed to be writable! */
		phdr_minaddr = (byte_t const *)(self->d_module.md_loadaddr +
		                                self->d_phdr[i].p_vaddr);
		phdr_maxaddr = phdr_minaddr + self->d_phdr[i].p_memsz;
		/* Must make this header writable! */
		if (!haslock) {
			mman_lock_acquire(&mman_kernel);
			haslock = true;
		}
		mman_mappings_minmaxlocate(&mman_kernel, phdr_minaddr,
		                           phdr_maxaddr, &mima);
		if unlikely(!mima.mm_min)
			continue;
		for (node = mima.mm_min;;) {
			if ((node->mn_flags & MNODE_F_PWRITE) &&
			    (node->mn_module == &self->d_module)) {
				assert(node->mn_part != NULL);
				assert(node->mn_flags & MNODE_F_MPREPARED);
				/* Remap this node w/o write-permissions.
				 * NOTE: We know that write-access should't be a
				 *       thing here, since we skip `PF_W' above. */
				node->mn_flags &= ~MNODE_F_PWRITE;
				mpart_mmap_force(node->mn_part, mnode_getaddr(node),
				                 mnode_getsize(node), node->mn_partoff,
				                 mnode_getperm_force(node));
				/* 'have to sync the driver on all CPUs down below! */
				mustsync = true;
			}
			if (node == mima.mm_max)
				break;
			node = mnode_tree_nextnode(node);
			assert(node);
		}
	}
	if (haslock)
		mman_lock_release(&mman_kernel);
	if (mustsync) {
		mman_supersync(self->d_module.md_loadmin,
		               (size_t)((self->d_module.md_loadmax + 1) -
		                        (self->d_module.md_loadmin)));
	}
}


#define DRIVER_RELOC_F_NORMAL   0x0000 /* Normal relocation flags. */
#define DRIVER_RELOC_F_SYMBOLIC 0x0001 /* DT_SYMBOLIC was set. */

struct driver_reloc_syminfo: driver_syminfo {
	/* NOTE: The `dsi_name' field ~may~ be left undefined! */
	struct driver *drs_orig;   /* [1..1][out] The driver that defines the requested symbol. */
	struct driver *drs_self;   /* [1..1][const] The driver who's relocations are being applied. */
	unsigned int   drs_rflags; /* [const] Relocation flags (set of `DRIVER_RELOC_F_*') */
};

PRIVATE NONNULL((1)) void FCALL
driver_dlsym_for_reloc(struct driver_reloc_syminfo *__restrict self,
                       uintptr_t symbol_id) {
	size_t i;
	ElfW(Sym) const *sym;
	struct driver *me = self->drs_self;
	if unlikely(symbol_id >= me->d_dynsym_cnt)
		THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SYMBOL, symbol_id);
	sym = &me->d_dynsym_tab[symbol_id];
	if ((sym->st_shndx != SHN_UNDEF) &&
	    (self->drs_rflags & DRIVER_RELOC_F_SYMBOLIC) &&
	    (ELFW(ST_BIND)(sym->st_info) != STB_WEAK)) {
		/* Bind the driver's own, local symbol. */
bind_own_sym:
		resolve_elf_symbol(me, self, sym);
		self->drs_orig = me;
		return;
	}

	self->dsi_name = me->d_dynstr + sym->st_name;
	if unlikely(self->dsi_name < me->d_dynstr || self->dsi_name >= me->d_dynstr_end)
		THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SYMNAME, sym->st_name);
	self->dsi_elfhash = (uint32_t)-1;
	self->dsi_gnuhash = (uint32_t)-1;

	/* Check for special symbols from the `drv_*' namespace. */
	if (self->dsi_name[0] == 'd' && self->dsi_name[1] == 'r' &&
	    self->dsi_name[2] == 'v' && self->dsi_name[3] == '_') {
		if (driver_dlsym_drv(me, self)) {
			self->drs_orig = me;
			return;
		}
	}

	/* Search for kernel core for the requested symbol. */
	if (kernel_dlsym(self)) {
		self->drs_orig = &kernel_driver;
		return;
	}

	/* Search through dependencies of the driver itself. */
	for (i = 0; i < me->d_depcnt; ++i) {
		REF struct driver *depdrv;
		depdrv = axref_get(&me->d_depvec[i]);
		if (!depdrv)
			continue;
		{
			FINALLY_DECREF_UNLIKELY(depdrv);
			self->drs_orig = driver_dlsym(depdrv, self);
		}
		if (self->drs_orig) {
			struct driver_syminfo info2;
			decref_unlikely(self->drs_orig);
			if (self->dsi_bind != STB_WEAK)
				return;
			/* Found a weak symbol!
			 * Note  that we must  also handle the case  where our own driver
			 * already defined a weak symbol due to `DRIVER_RELOC_F_SYMBOLIC' */
			if ((sym->st_shndx != SHN_UNDEF) &&
			    (self->drs_rflags & DRIVER_RELOC_F_SYMBOLIC) &&
			    (ELFW(ST_BIND)(sym->st_info) == STB_WEAK)) {
				resolve_elf_symbol(me, self, sym);
				self->drs_orig = me;
			}
			/* Go through all other dependencies and look for a driver
			 * that defines this symbol as something other than  weak! */
			info2.dsi_name    = self->dsi_name;
			info2.dsi_elfhash = self->dsi_elfhash;
			info2.dsi_gnuhash = self->dsi_gnuhash;
			for (++i; i < me->d_depcnt; ++i) {
				REF struct driver *depdrv2;
				depdrv = axref_get(&me->d_depvec[i]);
				if (!depdrv)
					continue;
				{
					FINALLY_DECREF_UNLIKELY(depdrv);
					depdrv2 = driver_dlsym(depdrv, &info2);
				}
				if (!depdrv2)
					continue;
				decref_unlikely(depdrv2);
				if (info2.dsi_bind != STB_WEAK) {
					/* Found a non-weak symbol! */
					self->dsi_addr = info2.dsi_addr;
					self->dsi_size = info2.dsi_size;
					self->dsi_bind = info2.dsi_bind;
					self->drs_orig = depdrv2;
					break;
				}
			}
			return;
		}
	}

	/* Fallback: If the driver itself also defines the symbol, bind against that one! */
	if (sym->st_shndx != SHN_UNDEF)
		goto bind_own_sym;

	/* Special case: weak symbols that are never defined may be bound to ADDR=0 */
	if (ELFW(ST_BIND)(sym->st_info) == STB_WEAK) {
		self->dsi_addr = NULL;
		self->dsi_size = 0;
		self->dsi_bind = STB_WEAK;
		self->drs_orig = NULL;
		return;
	}

	/* Lastly: print an error message, and throw an exception. */
	printk(KERN_ERR "[mod][%s] Relocation against unknown symbol %q\n",
	       me->d_name, self->dsi_name);
	THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NO_SYMBOL,
	                       sym->st_name);
}


#ifndef __INTELLISENSE__
#define DEFINE_driver_do_apply_relocations_vector
#include "driver-relocate.c.inl"
#if ELF_ARCH_USESRELA
#define DEFINE_driver_do_apply_relocations_vector_addend
#include "driver-relocate.c.inl"
#endif /* ELF_ARCH_USESRELA */
#else /* !__INTELLISENSE__ */

/* @param: reloc_flags: Set of `DRIVER_RELOC_FLAG_*' */
PRIVATE BLOCKING NONNULL((1, 2)) void KCALL
driver_do_apply_relocations_vector(struct driver *__restrict self,
                                   ElfW(Rel) *__restrict vector,
                                   size_t count, unsigned int reloc_flags);

/* @param: reloc_flags: Set of `DRIVER_RELOC_FLAG_*' */
PRIVATE BLOCKING NONNULL((1, 2)) void KCALL
driver_do_apply_relocations_vector_addend(struct driver *__restrict self,
                                          ElfW(Rela) *__restrict vector,
                                          size_t count, unsigned int reloc_flags);

#endif /* __INTELLISENSE__ */


/* Initialize driver relocations, but stop if the driver's state is altered. */
PRIVATE BLOCKING NONNULL((1)) void FCALL
driver_runstate_init_relo(struct driver *__restrict self) THROWS(...) {
	unsigned int reloc_flags = DRIVER_RELOC_F_NORMAL;
	ElfW(Rel) *rel_base      = NULL;
	size_t rel_count         = 0;
	ElfW(Rel) *jmp_base      = NULL;
	size_t jmp_size          = 0;
#if ELF_ARCH_USESRELA
	ElfW(Rela) *rela_base     = NULL;
	size_t rela_count         = 0;
	bool jmp_rels_have_addend = false;
#endif /* ELF_ARCH_USESRELA */
	size_t i;

	/* Service relocations of the module. */
	for (i = 0; i < self->d_dyncnt; ++i) {
		ElfW(Dyn) tag = self->d_dynhdr[i];
		switch (tag.d_tag) {

		case DT_NULL:
			goto done_dynamic;

		case DT_REL:
			rel_base = (ElfW(Rel) *)(self->d_module.md_loadaddr + tag.d_un.d_ptr);
			break;

		case DT_RELSZ:
			rel_count = tag.d_un.d_val / sizeof(ElfW(Rel));
			break;

		case DT_JMPREL:
			jmp_base = (ElfW(Rel) *)(self->d_module.md_loadaddr + tag.d_un.d_ptr);
			break;

		case DT_PLTRELSZ:
#if !ELF_ARCH_USESRELA
			jmp_size = tag.d_un.d_val / sizeof(ElfW(Rel));
#else /* !ELF_ARCH_USESRELA */
			jmp_size = tag.d_un.d_val;
#endif /* ELF_ARCH_USESRELA */
			break;

#if ELF_ARCH_USESRELA
		case DT_RELA:
			rela_base = (ElfW(Rela) *)(self->d_module.md_loadaddr + tag.d_un.d_ptr);
			break;

		case DT_RELASZ:
			rela_count = tag.d_un.d_val / sizeof(ElfW(Rela));
			break;

		case DT_PLTREL:
			if (tag.d_un.d_val == DT_RELA)
				jmp_rels_have_addend = true;
			break;
#endif /* ELF_ARCH_USESRELA */

		case DT_FLAGS:
			if (tag.d_un.d_val & DF_SYMBOLIC)
				reloc_flags |= DRIVER_RELOC_F_SYMBOLIC;
			break;

		case DT_SYMBOLIC:
			reloc_flags |= DRIVER_RELOC_F_SYMBOLIC;
			break;

		default: break;
		}
	}
done_dynamic:

	/* Actually apply relocations. */
	driver_do_apply_relocations_vector(self, rel_base, rel_count, reloc_flags);
#if !ELF_ARCH_USESRELA
	driver_do_apply_relocations_vector(self, jmp_base, jmp_size, reloc_flags);
#else /* !ELF_ARCH_USESRELA */
	driver_do_apply_relocations_vector_addend(self, rela_base, rela_count, reloc_flags);
	if (jmp_rels_have_addend) {
		driver_do_apply_relocations_vector_addend(self,
		                                          (ElfW(Rela) *)jmp_base,
		                                          jmp_size / sizeof(ElfW(Rela)),
		                                          reloc_flags);
	} else {
		driver_do_apply_relocations_vector(self, jmp_base,
		                                   jmp_size / sizeof(ElfW(Rel)),
		                                   reloc_flags);
	}
#endif /* ELF_ARCH_USESRELA */

	/* Perform arch-specific driver initialization. */
#ifdef ARCH_HAVE_ARCH_DRIVER_INITIALIZE
	arch_driver_initialize(self);
#endif /* ARCH_HAVE_ARCH_DRIVER_INITIALIZE */

	/* Disable text relocations for read-only program sections of the driver. */
	driver_disable_textrel(self);
}


typedef void (*driver_initfini_t)(int argc, char *argv[]);

struct driver_initfini_vector {
	size_t             difv_siz; /* # of callbacks. */
	driver_initfini_t *difv_vec; /* [1..1][difv_siz] Callbacks. */
};

/* Check if the given address range is mapped by the given driver. */
PRIVATE NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL driver_ismapped)(struct driver *__restrict self,
                               void const *addr, size_t num_bytes) {
	ElfW(Half) i;
	byte_t const *minaddr;
	byte_t const *maxaddr;
	minaddr = (byte_t const *)addr;
	maxaddr = (byte_t const *)addr + num_bytes - 1;
	if unlikely(minaddr > maxaddr)
		goto fail;
	if unlikely(minaddr < self->d_module.md_loadmin)
		goto fail;
	if unlikely(maxaddr > self->d_module.md_loadmax)
		goto fail;
	if (mman_lock_tryacquire(&mman_kernel)) {
		/* Search for the mem-nodes that should point back to `self' */
		for (;;) {
			struct mnode *node;
			node = mman_mappings_locate(&mman_kernel, minaddr);
			if unlikely(!node)
				break;
			if (maxaddr <= (byte_t const *)mnode_getmaxaddr(node)) {
				mman_lock_release(&mman_kernel);
				return true;
			}
			minaddr = (byte_t const *)mnode_getendaddr(node);
		}
		mman_lock_release(&mman_kernel);
	} else {
		/* Find the program header that contains the given address range. */
again_scan_phdrs:
		for (i = 0; i < self->d_phnum; ++i) {
			byte_t const *phdr_minaddr;
			byte_t const *phdr_maxaddr;
			if (self->d_phdr[i].p_type != PT_LOAD)
				continue;
			phdr_minaddr = (byte_t const *)(self->d_module.md_loadaddr + self->d_phdr[i].p_vaddr);
			phdr_maxaddr = phdr_minaddr + self->d_phdr[i].p_memsz;
			if (!(minaddr >= phdr_minaddr && minaddr <= phdr_maxaddr))
				continue;

			/* This header contains at least 1 byte of the requested range! */
			if (maxaddr <= phdr_maxaddr)
				return true;
			minaddr = phdr_maxaddr + 1;
			goto again_scan_phdrs;
		}
	}
fail:
	return false;
}

/* @param: name: The tag-name (e.g. "DT_INIT_ARRAY") */
PRIVATE NOBLOCK NONNULL((1, 4, 5)) void
NOTHROW(FCALL driver_get_initfini_array)(struct driver *__restrict self,
                                         intptr_t elf_dt_array, intptr_t elf_dt_array_sz,
                                         struct driver_initfini_vector *__restrict result,
                                         char const *__restrict name) {
	size_t i;
	result->difv_vec = NULL;
	result->difv_siz = 0;
	for (i = 0; i < self->d_dyncnt; ++i) {
		if (self->d_dynhdr[i].d_tag == elf_dt_array) {
			result->difv_vec = (driver_initfini_t *)(self->d_module.md_loadaddr +
			                                         self->d_dynhdr[i].d_un.d_ptr);
		} else if (self->d_dynhdr[i].d_tag == elf_dt_array_sz) {
			result->difv_siz = self->d_dynhdr[i].d_un.d_val / sizeof(driver_initfini_t);
		}
	}
	if (result->difv_siz) {
		/* Make sure that the array is in-bounds of the driver! */
		if unlikely(!result->difv_vec) {
			result->difv_siz = 0;
		} else {
			if unlikely(!driver_ismapped(self, (void *)result->difv_vec,
			                             result->difv_siz * sizeof(driver_initfini_t))) {
				printk(KERN_WARNING "[mod][%s] Driver %s-array at %p-%p is not mapped in of %p-%p (loadaddr: %p)\n",
				       self->d_name, name, result->difv_vec,
				       (byte_t *)(void *)result->difv_vec + result->difv_siz * sizeof(driver_initfini_t),
				       self->d_module.md_loadmin, self->d_module.md_loadmax, self->d_module.md_loadaddr);
				result->difv_vec = NULL;
				result->difv_siz = 0;
			}
		}
	}
}

PRIVATE BLOCKING NONNULL((1, 4)) void FCALL
driver_run_initfini_array(struct driver *__restrict self,
                          intptr_t elf_dt_array, intptr_t elf_dt_array_sz,
                          char const *__restrict name,
                          unsigned int flags) THROWS(...) {
	size_t i;
	struct driver_initfini_vector vec;
	driver_get_initfini_array(self, elf_dt_array, elf_dt_array_sz, &vec, name);
	for (i = 0; i < vec.difv_siz; ++i) {
		driver_initfini_t func;
		if unlikely(memcpy_nopf(&func, &vec.difv_vec[i], sizeof(func)) != 0) {
			printk(KERN_WARNING "[mod][%s] Failed to load %s[%" PRIuSIZ "] (of %" PRIuSIZ ") at %p. "
			                    "Address not mapped in %p-%p (loadaddr: %p)\n",
			       self->d_name, name, i, vec.difv_siz, &vec.difv_vec[i],
			       self->d_module.md_loadmin, self->d_module.md_loadmax,
			       self->d_module.md_loadaddr);
			continue;
		}

		/* Verify that at least the first byte of the function is mapped by the driver. */
		if unlikely(!driver_ismapped(self, (void *)func, 1)) {
			printk(KERN_WARNING "[mod][%s] Function %p from %s[%" PRIuSIZ "] (of %" PRIuSIZ ") at %p "
			                    "is not mapped in %p-%p (loadaddr: %p)\n",
			       self->d_name, (void *)func, name, i, vec.difv_siz, &vec.difv_vec[i],
			       self->d_module.md_loadmin, self->d_module.md_loadmax,
			       self->d_module.md_loadaddr);
			continue;
		}

		/* Actually invoke the function! */
		TRY {
			(*func)((int)(unsigned int)self->d_argc, self->d_argv);
		} EXCEPT {
			except_printf("running driver %q function %p from %s[%" PRIuSIZ "] (of %" PRIuSIZ ") at %p",
			              self->d_name, (void *)func, name, i, vec.difv_siz, &vec.difv_vec[i]);
			if (!(flags & DRIVER_INITFINI_F_FORCEFINI))
				RETHROW();
		}
	}
}

PRIVATE BLOCKING NONNULL((1, 3)) void FCALL
driver_run_initfini_func(struct driver *__restrict self, intptr_t elf_dt_func,
                         char const *__restrict name, unsigned int flags) THROWS(...) {
	size_t i;
	driver_initfini_t func = NULL;
	/* Search for a function matching the specified tag. */
	for (i = 0; i < self->d_dyncnt; ++i) {
		if (self->d_dynhdr[i].d_tag == elf_dt_func) {
			func = (driver_initfini_t)(void *)(self->d_module.md_loadaddr +
			                                   self->d_dynhdr[i].d_un.d_ptr);
			break;
		}
	}
	if (!func)
		return;

	/* Verify that at least the first byte of the function is mapped by the driver. */
	if unlikely(!driver_ismapped(self, (void *)func, 1)) {
		printk(KERN_WARNING "[mod][%s] %s-function at %p is not mapped in %p-%p (loadaddr: %p)\n",
		       self->d_name, name, (void *)func,
		       self->d_module.md_loadmin, self->d_module.md_loadmax,
		       self->d_module.md_loadaddr);
		return;
	}

	/* Actually invoke the function! */
	TRY {
		(*func)((int)(unsigned int)self->d_argc, self->d_argv);
	} EXCEPT {
		except_printf("running driver %q %s-function at %p",
		              self->d_name, name, (void *)func);
		if (!(flags & DRIVER_INITFINI_F_FORCEFINI))
			RETHROW();
	}
}

/************************************************************************/
/* Driver-specific constructor/finalization callbacks                   */
/************************************************************************/
PRIVATE BLOCKING NONNULL((1)) void FCALL
driver_runinit_DT_PREINITARR(struct driver *__restrict self) THROWS(...) {
	driver_run_initfini_array(self, DT_PREINIT_ARRAY, DT_PREINIT_ARRAYSZ,
	                          "DT_PREINIT_ARRAY", DRIVER_INITFINI_F_NORMAL);
}

PRIVATE BLOCKING NONNULL((1)) void FCALL
driver_runinit_DT_INITARR(struct driver *__restrict self) THROWS(...) {
	driver_run_initfini_array(self, DT_INIT_ARRAY, DT_INIT_ARRAYSZ,
	                          "DT_INIT_ARRAY", DRIVER_INITFINI_F_NORMAL);
}

PRIVATE BLOCKING NONNULL((1)) void FCALL
driver_runinit_DT_INIT(struct driver *__restrict self) THROWS(...) {
	driver_run_initfini_func(self, DT_INIT, "DT_INIT", DRIVER_INITFINI_F_NORMAL);
}

PRIVATE BLOCKING NONNULL((1)) void FCALL
driver_runfini_DT_FINI(struct driver *__restrict self, unsigned int flags) THROWS(...) {
	driver_run_initfini_func(self, DT_FINI, "DT_FINI", flags);
}

PRIVATE BLOCKING NONNULL((1)) void FCALL
driver_runfini_DT_FINIARR(struct driver *__restrict self, unsigned int flags) THROWS(...) {
	driver_run_initfini_array(self, DT_FINI_ARRAY, DT_FINI_ARRAYSZ,
	                          "DT_FINI_ARRAY", flags);
}

PRIVATE NONNULL((1)) void FCALL
driver_runfini_unbindglob(struct driver *__restrict self) {
#if 0
	bool result;
	(void)self;
	result = driver_clear_execabis(self);

	/* TODO: Delete global hooks of `self':
	 *   - blkdev_register()
	 *   - chrdev_register()
	 *   - nicdev_setdefault()
	 *   - register_filesystem_type()
	 *   - fs_filesystems                       (All filesystem implemented by `self')
	 *   - fs_filesystems                       (All filesystem using a block-device implemented by `self')
	 *   - kernel_debugtraps_install()
	 *   - driver_loaded_callbacks
	 *   - driver_finalized_callbacks
	 *   - driver_unloaded_callbacks
	 *   - mman_onexec_callbacks
	 *   - mman_oninit_callbacks
	 *   - mman_onfini_callbacks
	 *   - mman_onclone_callbacks
	 *   - isr_register()
	 *   - syslog_sink_register()
	 *   - mrtm_hooks
	 *   - register_async_worker()              (Delete all workers with callbacks apart of `self')
	 *   - async_job_start()                    (Cancel all running jobs with callbacks apart of `self')
	 *   - realtime_clock
	 * XXX:
	 *   - What about file handles that somehow reference the driver, including
	 *     stuff   like   HANDLE_TYPE_FILEHANDLE->f_node->fn_super->fs_dev?  We
	 *     should  probably try  to find these  files, and close  them in their
	 *     accompanying handle manager.
	 *     We can enumerate open handle managers by enumerating threads!
	 *   - This function should also have a  return value to indicate if  it
	 *     even  did something, and if it did,  the caller should be able to
	 *     call us multiple times to do a kind-of keep-killing-until-it-dies
	 *     functionality, alongside doing other things in-between.
	 */
	return result;
#endif
	/* TODO */
	(void)self;
	COMPILER_IMPURE();
}


/* Initialize the given driver by transitioning its state  to
 * `DRIVER_STATE_LOADED'. If this fails, or if the driver was
 * already finalized, its state is set to `DRIVER_STATE_KILL'
 * instead.
 * @param: flags: Set of `DRIVER_INITFINI_F_*' */
PUBLIC BLOCKING NONNULL((1)) void FCALL
driver_initialize(struct driver *__restrict self, unsigned int flags)
		THROWS(E_WOULDBLOCK, E_FSERROR, E_NOT_EXECUTABLE, ...) {
	uintptr_t state;
again:
	state = atomic_read(&self->d_state);
	switch (state) {

	case DRIVER_STATE_INIT: {
		/* Start initialization. */
		if (!atomic_cmpxch_weak(&self->d_state,
		                        DRIVER_STATE_INIT,
		                        DRIVER_STATE_INIT_DEPS))
			goto again;
		atomic_write(&self->_d_initthread, THIS_TASK);
		sig_broadcast(driver_changesignal(self));

		/* At this point, we have exclusive authority to initialize
		 * the given driver however we  want, as well as the  right
		 * to finalize it if something happens that we don't  like! */
		TRY {

			/* Step #1: Like already indicate by `DRIVER_STATE_INIT_DEPS',
			 *          we  have to load+initialize  other drivers that we
			 *          have dependencies upon.
			 *          Note that in the  case of cyclic dependencies,  the
			 *          init-loop is broken by the init_thread == THIS_TASK
			 *          check when  `driver_initialize()'  is  called  with
			 *          `d_state == DRIVER_STATE_INIT_DEPS'! */
			if (self->d_depcnt != 0)
				driver_runstate_init_deps(self);

			/* Step #2: service relocations. */
			atomic_write(&self->d_state, DRIVER_STATE_INIT_RELO);
			sig_broadcast(driver_changesignal(self));
			driver_runstate_init_relo(self);
			if (atomic_read(&self->d_state) != DRIVER_STATE_INIT_RELO) {
				/* This can happen if a IFUNC/IDATA element called `driver_finalize()' */
				assert(self->d_state == DRIVER_STATE_FINI_RDPS);
				goto abort_init_deps;
			}

			/* Inform any attached debugger of the new driver.
			 * NOTE: This is done after relocations, but before initializers, so that
			 *       a debugger is able to safely set breakpoints without  overriding
			 *       memory locations possibly affected by relocations. */
#ifdef CONFIG_HAVE_KERNEL_VBOXGDB
			vboxgdb_trap(VBOXGDB_TRAP_LIBRARY);
#endif /* CONFIG_HAVE_KERNEL_VBOXGDB */
			if (kernel_debugtrap_enabled()) {
				struct debugtrap_reason r;
				r.dtr_signo  = SIGTRAP;
				r.dtr_reason = DEBUGTRAP_REASON_LIBRARY;
				kernel_debugtrap(&r);
			}

		} EXCEPT {
			atomic_write(&self->_d_initthread, NULL);
			atomic_write(&self->d_state, DRIVER_STATE_FINI_DEPS);
			sig_broadcast(driver_changesignal(self));
			driver_runstate_fini_deps(self);
			RETHROW();
		}

		TRY {
			/* Step #3: Run driver DT_PREINIT_ARRAY constructors. */
			atomic_write(&self->d_state, DRIVER_STATE_INIT_CT_PREINITARR);
			sig_broadcast(driver_changesignal(self));
			driver_runinit_DT_PREINITARR(self);
			if (atomic_read(&self->d_state) != DRIVER_STATE_INIT_CT_PREINITARR)
				goto abort_init_DT_FINIARR;

			/* Step #4: Run driver DT_INIT_ARRAY constructors. */
			atomic_write(&self->d_state, DRIVER_STATE_INIT_CT_INITARR);
			sig_broadcast(driver_changesignal(self));
			driver_runinit_DT_INITARR(self);
			if (atomic_read(&self->d_state) != DRIVER_STATE_INIT_CT_INITARR)
				goto abort_init_DT_FINIARR;
		} EXCEPT {
			atomic_write(&self->d_state, DRIVER_STATE_FINI_DT_FINIARR);
			sig_broadcast(driver_changesignal(self));
			NESTED_TRY {
				driver_runfini_DT_FINIARR(self, flags);
			} EXCEPT {
				atomic_write(&self->_d_initthread, NULL);
				atomic_write(&self->d_state, DRIVER_STATE_FAIL_DT_FINIARR);
				sig_broadcast(driver_changesignal(self));
				RETHROW();
			}
			atomic_write(&self->_d_initthread, NULL);
			atomic_write(&self->d_state, DRIVER_STATE_FINI_DEPS);
			sig_broadcast(driver_changesignal(self));
			driver_runstate_fini_deps(self);
			RETHROW();
		}

		TRY {
			/* Step #5: Run the driver DT_INIT callback. */
			atomic_write(&self->d_state, DRIVER_STATE_INIT_CT_INIT);
			sig_broadcast(driver_changesignal(self));
			driver_runinit_DT_INIT(self);
			if (atomic_read(&self->d_state) != DRIVER_STATE_INIT_CT_INIT)
				goto abort_init_DT_FINI;
		} EXCEPT {
			{
				NESTED_EXCEPTION;
				atomic_write(&self->d_state, DRIVER_STATE_FINI_DT_FINI);
				sig_broadcast(driver_changesignal(self));
				TRY {
					driver_runfini_DT_FINI(self, flags);
				} EXCEPT {
					atomic_write(&self->_d_initthread, NULL);
					atomic_write(&self->d_state, DRIVER_STATE_FAIL_DT_FINI);
					sig_broadcast(driver_changesignal(self));
					RETHROW();
				}
				atomic_write(&self->d_state, DRIVER_STATE_FINI_DT_FINIARR);
				sig_broadcast(driver_changesignal(self));
				TRY {
					driver_runfini_DT_FINIARR(self, flags);
				} EXCEPT {
					atomic_write(&self->_d_initthread, NULL);
					atomic_write(&self->d_state, DRIVER_STATE_FAIL_DT_FINIARR);
					sig_broadcast(driver_changesignal(self));
					RETHROW();
				}
			}
			atomic_write(&self->_d_initthread, NULL);
			atomic_write(&self->d_state, DRIVER_STATE_FINI_DEPS);
			sig_broadcast(driver_changesignal(self));
			driver_runstate_fini_deps(self);
			RETHROW();
		}

		/* Step #6: Indicate that the driver has been initialized! */
		atomic_write(&self->_d_initthread, NULL);
		atomic_write(&self->d_state, DRIVER_STATE_LOADED);
		sig_broadcast(driver_changesignal(self));
		break;

		/* These can happen if a driver initializer called `driver_finalize()' */
abort_init_DT_FINI:
		assert(self->d_state == DRIVER_STATE_FINI_DT_FINI);
		TRY {
			driver_runfini_DT_FINI(self, flags);
		} EXCEPT {
			atomic_write(&self->_d_initthread, NULL);
			atomic_write(&self->d_state, DRIVER_STATE_FAIL_DT_FINI);
			sig_broadcast(driver_changesignal(self));
			RETHROW();
		}
		atomic_write(&self->d_state, DRIVER_STATE_FINI_DT_FINIARR);
		sig_broadcast(driver_changesignal(self));
abort_init_DT_FINIARR:
		assert(self->d_state == DRIVER_STATE_FINI_DT_FINIARR);
		TRY {
			driver_runfini_DT_FINIARR(self, flags);
		} EXCEPT {
			atomic_write(&self->_d_initthread, NULL);
			atomic_write(&self->d_state, DRIVER_STATE_FAIL_DT_FINIARR);
			sig_broadcast(driver_changesignal(self));
			RETHROW();
		}
		atomic_write(&self->d_state, DRIVER_STATE_FINI_UNBINDGLOB);
		sig_broadcast(driver_changesignal(self));
/*abort_init_globalhooks:*/
		assert(self->d_state == DRIVER_STATE_FINI_UNBINDGLOB);
		TRY {
			driver_runfini_unbindglob(self);
		} EXCEPT {
			atomic_write(&self->_d_initthread, NULL);
			atomic_write(&self->d_state, DRIVER_STATE_FAIL_UNBINDGLOB);
			sig_broadcast(driver_changesignal(self));
			RETHROW();
		}
abort_init_deps:
		atomic_write(&self->_d_initthread, NULL);
		atomic_write(&self->d_state, DRIVER_STATE_FINI_DEPS);
		sig_broadcast(driver_changesignal(self));
		driver_runstate_fini_deps(self);
	}	break;

	case DRIVER_STATE_INIT_DEPS:
	case DRIVER_STATE_INIT_RELO:
	case DRIVER_STATE_INIT_CT_PREINITARR:
	case DRIVER_STATE_INIT_CT_INITARR:
	case DRIVER_STATE_INIT_CT_INIT: {
		/* Wait for another thread to finish the initialization.
		 * However, make sure to deal  with the case where  it's
		 * the calling thread that's doing the init! */
		struct task *init_thread;
		init_thread = atomic_read(&self->_d_initthread);
		if unlikely(state != atomic_read(&self->d_state))
			goto again;
		if unlikely(init_thread == THIS_TASK)
			return; /* Don't cause a deadlock by waiting for ourselves to finish init! */

		/* Wait for the driver's state to change. */
		task_connect(driver_changesignal(self));
		if unlikely(atomic_read(&self->d_state) != state) {
			task_disconnectall();
			break;
		}
		task_waitfor();
		goto again;
	}	break;

	default:
		/* All other states indicate already-initialized,  or
		 * already-finalized (with no way of re-initializing)
		 *
		 * iow: We don't have to do anything in these cases! */
		break;
	}
}

/* Finalize the given driver. Note that driver finalizers are
 * allowed to block and  throw exceptions (meaning that  this
 * function  may  also block  and throw).  Additionally, this
 * function  may wait  for a  driver that  is currently being
 * initialized or finalized  by another to  finish doing  so,
 * however if it's the caller thread that does the init/fini,
 * then this function will  return immediately, so-as to  not
 * cause a deadlock!
 * @param: flags: Set of `DRIVER_INITFINI_F_*' */
PUBLIC BLOCKING NONNULL((1)) void FCALL
driver_finalize(struct driver *__restrict self, unsigned int flags)
		THROWS(...) {
	uintptr_t state;
again:
	state = atomic_read(&self->d_state);
	switch (state) {

	case DRIVER_STATE_INIT:
		/* Directly switch over to the FINI_TEXT state. */
		if (!atomic_cmpxch_weak(&self->d_state,
		                        DRIVER_STATE_INIT,
		                        DRIVER_STATE_KILL))
			goto again;
		sig_broadcast(driver_changesignal(self));

		/* Drop the self-reference that was held by the
		 * driver's state being `!= DRIVER_STATE_KILL'. */
		decref_nokill(self);
		break;

	case DRIVER_STATE_INIT_DEPS:
	case DRIVER_STATE_INIT_RELO:
	case DRIVER_STATE_INIT_CT_PREINITARR:
	case DRIVER_STATE_INIT_CT_INITARR:
	case DRIVER_STATE_INIT_CT_INIT: {
		/* The driver  is being  initialized _right_  _now_
		 * In  this case, we must differentiate between the
		 * case where it's the calling thread that does the
		 * init, or some other thread.
		 *
		 * In the former case, we  must mark the driver  for
		 * finalization, and return to our caller, such that
		 * the call to `driver_initialize()' from further up
		 * the stack can initiate the actual finalization.
		 *
		 * In the later case, we must wait for the other thread
		 * to finish initialization,  so we  can instigate  the
		 * driver's finalization immediately afterwards. */
		struct task *init_thread;
		init_thread = atomic_read(&self->_d_initthread);
		if unlikely(state != atomic_read(&self->d_state))
			goto again;
		if unlikely(init_thread == THIS_TASK) {
			unsigned int new_state;
			new_state = DRIVER_STATE_FINI_RDPS;
			if (state == DRIVER_STATE_INIT_CT_PREINITARR ||
			    state == DRIVER_STATE_INIT_CT_INITARR) {
				state = DRIVER_STATE_FINI_DT_FINIARR;
			} else if (state == DRIVER_STATE_INIT_CT_INIT) {
				state = DRIVER_STATE_FINI_DT_FINI;
			}

			/* Mark the driver for lazy finalization once
			 * we return back up the stack to our caller! */
			if (!atomic_cmpxch_weak(&self->d_state, state, new_state))
				goto again;
			sig_broadcast(driver_changesignal(self));
			return;
		}

		/* Wait for another thread to finish initialization. */
		task_connect(driver_changesignal(self));
		if unlikely(state != atomic_read(&self->d_state)) {
			task_disconnectall();
			goto again;
		}
		task_waitfor();
		goto again;
	}	break;

	case DRIVER_STATE_LOADED:
	case DRIVER_STATE_FAIL_DT_FINI: {
		/* The actual heart-piece of `driver_finalize()':
		 * Finalize a driver  that is fully  initialized. */
		if (!atomic_cmpxch_weak(&self->d_state, state,
		                        DRIVER_STATE_FINI_DT_FINI))
			goto again;

		/* Run second-stage driver finalizers. */
		atomic_write(&self->_d_initthread, THIS_TASK);
		sig_broadcast(driver_changesignal(self));
		TRY {
			driver_runfini_DT_FINI(self, flags);
		} EXCEPT {
			atomic_write(&self->_d_initthread, NULL);
			atomic_write(&self->d_state, DRIVER_STATE_FAIL_DT_FINI);
			sig_broadcast(driver_changesignal(self));
			RETHROW();
		}

		/* Run normal driver finalizers. */
		atomic_write(&self->d_state, DRIVER_STATE_FINI_DT_FINIARR);
do_handle_fini_dtors:
		sig_broadcast(driver_changesignal(self));
		TRY {
			driver_runfini_DT_FINIARR(self, flags);
		} EXCEPT {
			atomic_write(&self->_d_initthread, NULL);
			atomic_write(&self->d_state, DRIVER_STATE_FAIL_DT_FINIARR);
			sig_broadcast(driver_changesignal(self));
			RETHROW();
		}

		/* Unbind global driver hooks. */
		atomic_write(&self->d_state, DRIVER_STATE_FINI_UNBINDGLOB);
do_handle_fini_unbindglob:
		sig_broadcast(driver_changesignal(self));
		TRY {
			driver_runfini_unbindglob(self);
		} EXCEPT {
			atomic_write(&self->_d_initthread, NULL);
			atomic_write(&self->d_state, DRIVER_STATE_FAIL_UNBINDGLOB);
			sig_broadcast(driver_changesignal(self));
			RETHROW();
		}

		/* Finalize driver dependencies... */
		atomic_write(&self->_d_initthread, NULL);
		atomic_write(&self->d_state, DRIVER_STATE_FINI_DEPS);
		sig_broadcast(driver_changesignal(self));
		driver_runstate_fini_deps(self);
	}	break;

	case DRIVER_STATE_FAIL_DT_FINIARR:
		/* Try to restart a previously failed step. */
		if (!atomic_cmpxch_weak(&self->d_state,
		                        DRIVER_STATE_FAIL_DT_FINIARR,
		                        DRIVER_STATE_FINI_DT_FINIARR))
			goto again;
		atomic_write(&self->_d_initthread, THIS_TASK);
		goto do_handle_fini_dtors;

	case DRIVER_STATE_FAIL_UNBINDGLOB:
		/* Try to restart a previously failed step. */
		if (!atomic_cmpxch_weak(&self->d_state,
		                        DRIVER_STATE_FAIL_UNBINDGLOB,
		                        DRIVER_STATE_FINI_UNBINDGLOB))
			goto again;
		atomic_write(&self->_d_initthread, THIS_TASK);
		goto do_handle_fini_unbindglob;

	case DRIVER_STATE_FINI_DT_FINI:
	case DRIVER_STATE_FINI_DT_FINIARR:
	case DRIVER_STATE_FINI_UNBINDGLOB:
	case DRIVER_STATE_FINI_RDPS: {
		/* Check if this is a recursive call (if it is, don't do anything!) */
		struct task *fini_thread;
		fini_thread = atomic_read(&self->_d_initthread);
		if (state != atomic_read(&self->d_state))
			goto again;
		if (fini_thread == THIS_TASK)
			return; /* Ignore recursive calls. */
		ATTR_FALLTHROUGH
	case DRIVER_STATE_FINI_DEPS:
		/* Wait for the state to change. */
		task_connect(driver_changesignal(self));
		if (state != atomic_read(&self->d_state)) {
			task_disconnectall();
			goto again;
		}
		task_waitfor();
		goto again;
	}	break;

	default:
		/* All other states indicate already-finalized, or currently finalizing.
		 * iow: We don't have to do anything in these cases! */
		break;
	}
}



/************************************************************************/
/* The primary driver operators table.                                  */
/************************************************************************/
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL driver_free_)(struct driver *__restrict self) {
	kfree(self);
}

/* Try to  remove all  dead drivers  from the  load-list.
 * If this fails to lack of memory, or failure to acquire
 * some  internal locks without blocking, return `false'.
 * Upon success, return `true' */
PRIVATE NOBLOCK bool
NOTHROW(FCALL remove_dead_drivers_from_loadlist)(void) {
	REF struct driver_loadlist *old_ll;
	REF struct driver_loadlist *new_ll;
	size_t i, count;
	bool cmpxch_ok;

again:
	old_ll = arref_get(&drivers);

	/* Count the # of non-destroyed drivers.
	 * Note that this # may decrease over time, but is
	 * guarantied  not to increase (meaning we can use
	 * it as an upper limit  to the # of drivers  that
	 * the new load-list must be able to hold) */
	assert_assume(old_ll->dll_count >= 1);
	for (i = 0, count = 0; i < old_ll->dll_count; ++i) {
		if (!wasdestroyed(old_ll->dll_drivers[i]))
			++count;
	}
	assert(count <= old_ll->dll_count);
	if unlikely(count == old_ll->dll_count) {
		/* This _really_ shouldn't happen, given how this
		 * function is meant to be called after a  driver
		 * has just been destroyed.
		 * However,  this _could_ happen if someone else
		 * already did the work of removing our caller's
		 * dead  driver, as is automatically done by the
		 * `get_driver_loadlist()' function! */
		decref_unlikely(old_ll);
		return true;
	}

	/* Allocate the new load-list descriptor. */
	if unlikely(count == 1) {
		/* Special case: only the kernel remains! */
		new_ll = incref(&default_loaded_drivers);
	} else {
		size_t dst;
		new_ll = (REF struct driver_loadlist *)kmalloc_nx(offsetof(struct driver_loadlist, dll_drivers) +
		                                                  (count * sizeof(WEAK REF struct driver *)),
		                                                  GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT);
		if unlikely(!new_ll) {
			decref_unlikely(old_ll);
			return false;
		}

		/* Construct new weak references for all (still) non-destroyed drivers. */
		for (i = 0, dst = 0; i < old_ll->dll_count; ++i) {
			if (wasdestroyed(old_ll->dll_drivers[i]))
				continue;
			assert(dst <= count);
			new_ll->dll_drivers[dst] = weakincref(old_ll->dll_drivers[i]);
			++dst;
		}
		if unlikely(dst < count) {
			/* More drivers died, so we can try to strip
			 * some  more memory from our new load-list. */
			REF struct driver_loadlist *temp;
			temp = (REF struct driver_loadlist *)krealloc_nx(new_ll,
			                                                 offsetof(struct driver_loadlist, dll_drivers) +
			                                                 (dst * sizeof(WEAK REF struct driver *)),
			                                                 GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT);
			if likely(temp != NULL)
				new_ll = temp;
		}
		new_ll->dll_refcnt = 1;
		new_ll->dll_count  = dst;
	}

	/* Try to write-back the new (truncated) set of drivers. */
	cmpxch_ok = arref_cmpxch_inherit_new(&drivers, old_ll, new_ll);
	decref_likely(old_ll);
	if (!cmpxch_ok) {
		/* The load-list changed in the mean time.
		 * -> Must try again! */
		decref_likely(new_ll);
		goto again;
	}

	/* Success! (dead drivers were removed; though more may have
	 * already popped up once again, thanks to race  conditions) */
	return true;
}


/* Perform all remaining destroy operations after the given driver
 * `self'  has had  all of  its mem-nodes  unmapped and destroyed. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL driver_destroy_after_mnodes)(struct driver *__restrict self) {
	/* Cleanup drv_arg$-symbols  _after_  we've  destroyed  mem-nodes,
	 * thus allowing users to assume that any kind of address returned
	 * by  one of the driver dlsym() functions will remain valid until
	 * that driver has been unmapped from kernel memory! */
	while (!SLIST_EMPTY(&self->d_argcash)) {
		struct driver_argcash *cash;
		cash = SLIST_FIRST(&self->d_argcash);
		SLIST_REMOVE_HEAD(&self->d_argcash, dac_link);
		driver_argcash_free(cash);
	}
	DBG_memset(&self->d_argcash, 0xcc, sizeof(self->d_argcash));
	weakdecref(self);
}

/* Free all nodes from the given list of dead nodes. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL driver_deadnodes_freelist)(struct mnode_slist *__restrict deadnodes) {
	while (!SLIST_EMPTY(deadnodes)) {
		struct mnode *node;
		node = SLIST_FIRST(deadnodes);
		SLIST_REMOVE_HEAD(deadnodes, _mn_dead);
		mnode_destroy(node);
	}
}

/* While holding a lock to the kernel mman, unmap all of  the
 * mappings that are associated with the given driver `self'.
 * Destroyed nodes are added to `deadlist' */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mman_remove_driver_nodes)(struct driver *__restrict self,
                                        struct mnode_slist *__restrict deadlist) {
	/* Go over all mem-nodes that cover the address range of `self',
	 * and  remove+unmap+unprepare all that have module-pointers set
	 * to point back at `self'.
	 * Doing this should result in exactly `self->d_module.md_nodecount'
	 * nodes being removed! */
	struct mnode_tree_minmax mima;
again_find_nodes:
	mman_mappings_minmaxlocate(&mman_kernel,
	                           self->d_module.md_loadmin,
	                           self->d_module.md_loadmax,
	                           &mima);
	if (mima.mm_min != NULL) {
		struct mnode *node;
		for (node = mima.mm_min;;) {
			if likely(node->mn_module == &self->d_module) {
#ifndef NDEBUG
				assert(self->d_module.md_nodecount != 0);
				--self->d_module.md_nodecount;
#endif /* !NDEBUG */

				/* Driver  nodes  _must_ have  the PREPARED  flag set.
				 * Otherwise, we'd be unable to unmap them as NOTHROW! */
				assert(node->mn_flags & MNODE_F_MPREPARED);

				/* If necessary, remove from the list of writable nodes.
				 * This list is a no-op for kernel-space, but must still
				 * be kept a valid linked  list (and not contain bad  or
				 * dangling pointers) */
				if unlikely(node->mn_part != NULL && LIST_ISBOUND(node, mn_writable))
					LIST_REMOVE(node, mn_writable);

				/* Must get rid of this node! */
				mman_mappings_removenode(&mman_kernel, node);

				/* Unmap+sync+unprepare the node. */
				mnode_pagedir_unmap(node);
				mnode_mman_supersync(node);
				mnode_pagedir_kernelunprepare(node);

				/* Set the UNMAPPED flag for the node */
				atomic_or(&node->mn_flags, MNODE_F_UNMAPPED);

				/* Add the node to the list of dead nodes. */
				SLIST_INSERT(deadlist, node, _mn_dead);
				goto again_find_nodes;
			}
			if (node == mima.mm_max)
				break;
			node = mnode_tree_nextnode(node);
			assert(node);
		}
	}
#ifdef NDEBUG
	self->d_module.md_nodecount = 0;
#else /* NDEBUG */
	assert(self->d_module.md_nodecount == 0);
#endif /* !NDEBUG */
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL driver_finitext_postlop)(Tobpostlockop(mman) *__restrict lop,
                                       struct mman *__restrict UNUSED(mm)) {
	REF struct driver *me;
	me = container_of(lop, struct driver, _d_mm_postlop);

	/* Destroy all of the dead mem-nodes. */
	driver_deadnodes_freelist(&me->_d_deadnodes);
	DBG_memset(&me->_d_deadnodes, 0xcc, sizeof(me->_d_deadnodes));

	/* The weak reference originally inherited from
	 * `driver_clear_mnode_pointers_and_destroy()' */
	driver_destroy_after_mnodes(me);
}

PRIVATE NOBLOCK NONNULL((1)) Tobpostlockop(mman) *
NOTHROW(FCALL driver_finitext_lop)(Toblockop(mman) *__restrict lop,
                                   struct mman *__restrict UNUSED(mm)) {
	struct driver *me;
	me = container_of(lop, struct driver, _d_mm_lop);

	if likely(me->d_module.md_nodecount != 0) {
		/* Unmap driver text sections. */
		mman_remove_driver_nodes(me, &me->_d_deadnodes);
		assert(!SLIST_EMPTY(&me->_d_deadnodes));
		weakdecref_nokill(me); /* Reference inherited from `md_nodecount' dropping to 0 */
	}

	/* Setup a post lock operation to broadcast the state-change,
	 * as well  as  drop  the  weak  reference  we've  inherited. */
	me->_d_mm_postlop.oplo_func = &driver_finitext_postlop;
	return &me->_d_mm_postlop;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL driver_clear_mnode_pointers_and_destroy)(struct driver *__restrict self) {
	kfree(self->d_sections);
	DBG_memset(&self->d_shnum, 0xcc, sizeof(self->d_shnum));
	DBG_memset(&self->d_sections, 0xcc, sizeof(self->d_sections));

	/* Using  lock operations, remove all of the mnode
	 * self-pointers back towards this driver from the
	 * kernel mman. */
	if (self->d_module.md_nodecount != 0) {
		/* Initialize the list of dead mem-nodes. */
		SLIST_INIT(&self->_d_deadnodes);
		if (mman_lock_tryacquire(&mman_kernel)) {
			COMPILER_READ_BARRIER();
			if unlikely(self->d_module.md_nodecount == 0) {
				_mman_lock_release(&mman_kernel);
			} else {
				mman_remove_driver_nodes(self, &self->_d_deadnodes);
				_mman_lock_release(&mman_kernel);
				/* Destroy all of the dead mem-nodes. */
				assert(!SLIST_EMPTY(&self->_d_deadnodes));
				driver_deadnodes_freelist(&self->_d_deadnodes);
				DBG_memset(&self->_d_deadnodes, 0xcc, sizeof(self->_d_deadnodes));
				weakdecref_nokill(self); /* Reference inherited from `md_nodecount' dropping to 0 */
			}
			mman_lockops_reap(&mman_kernel);
			driver_destroy_after_mnodes(self); /* Reference inherited from `md_refcnt' dropping to 0 */
		} else {
			self->_d_mm_lop.olo_func = &driver_finitext_lop;
			SLIST_ATOMIC_INSERT(&mman_kernel_lockops, &self->_d_mm_lop, olo_link);
			_mman_lockops_reap(&mman_kernel);
		}
	} else {
		driver_destroy_after_mnodes(self); /* Reference inherited from `md_refcnt' dropping to 0 */
	}
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL driver_unbind_sections_and_destroy_postlop)(struct postlockop *__restrict self) {
	struct driver *me;
	me = container_of(self, struct driver, _d_postlop);

	/* Destroy dead sections! */
	while (!SLIST_EMPTY(&me->_d_deadsect)) {
		struct driver_section *sect;
		sect = (struct driver_section *)SLIST_FIRST(&me->_d_deadsect);
		SLIST_REMOVE_HEAD(&me->_d_deadsect, _ms_dead);
		driver_section_destroy(sect);
	}
	DBG_memset(&me->_d_deadsect, 0xcc, sizeof(me->_d_deadsect));

	/* Proceed normally with the full destruction
	 * of the original driver module. */
	driver_clear_mnode_pointers_and_destroy(me);
}

PRIVATE NOBLOCK NONNULL((1)) struct postlockop *
NOTHROW(FCALL driver_unbind_sections_and_destroy_lop)(struct lockop *__restrict self) {
	struct driver *me;
	me = container_of(self, struct driver, _d_lop);
	SLIST_INIT(&me->_d_deadsect);

	/* Remove all sections from the driver. */
	while (me->d_shnum) {
		REF struct driver_section *sect;
		--me->d_shnum;
		sect = awref_get(&me->d_sections[me->d_shnum]);
		if (!sect)
			continue; /* Section was never allocated or is dead. */
		if unlikely(!LIST_ISBOUND(&sect->ds_sect, ms_cache)) {
			decref_unlikely(sect);
			continue; /* Section isn't apart of the cache... */
		}
		LIST_UNBIND(&sect->ds_sect, ms_cache);
		decref_nokill(sect); /* The reference from the section cache. */

		/* Drop the reference we got from `awref_get()'
		 * If this ends up destroying the section, then enqueue said
		 * destruction to be performed  as part of the  post-lockop. */
		if (atomic_decfetch(&sect->ds_sect.ms_refcnt) == 0)
			SLIST_INSERT(&me->_d_deadsect, &sect->ds_sect, _ms_dead);
	}

	/* Do the rest of the module destruction, as well as the
	 * cleanup  of dead sections  from within a post-lockop,
	 * thereby reducing the amount of time spent holding the
	 * module section cache lock. */
	me->_d_postlop.plo_func = &driver_unbind_sections_and_destroy_postlop;
	return &me->_d_postlop;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL driver_destroy)(struct driver *__restrict self) {
	/* Log a system message informing the user that  this
	 * driver is now officially dead, and will no  longer
	 * appear in load-lists (or at the very least: should
	 * always be skipped when encountered) */
	printk(KERN_NOTICE "[mod][-] Delmod: %q\n", self->d_name);

	/* Change the driver's state from KILL to DEAD */
	assert(self->d_module.md_mman == &mman_kernel);
	assert(self->d_state == DRIVER_STATE_KILL);
	atomic_write(&self->d_state, DRIVER_STATE_DEAD);
	sig_broadcast(driver_changesignal(self));

	/* Clear out members that are no longer valid for a destroyed driver. */
	xdecref(self->d_module.md_file);
	xdecref(self->d_module.md_fspath);
	xdecref(self->d_module.md_fsname);
	kfree(self->d_cmdline);
	kfree(self->d_argv);
	kfree(self->d_depvec);
	if (self->d_eh_frame_cache != NULL)
		dfc_freetree(self->d_eh_frame_cache);
	kfree(self->d_shdr);
	kfree(self->d_shstrtab);

	/* Invalidate fields that may no longer be accessed. */
	DBG_memset(&self->d_module.md_file, 0xcc, sizeof(self->d_module.md_file));
	DBG_memset(&self->d_module.md_fspath, 0xcc, sizeof(self->d_module.md_fspath));
	DBG_memset(&self->d_module.md_fsname, 0xcc, sizeof(self->d_module.md_fsname));
	DBG_memset(&self->d_name, 0xcc, sizeof(self->d_name));
	DBG_memset(&self->d_cmdline, 0xcc, sizeof(self->d_cmdline));
	DBG_memset(&self->d_argc, 0xcc, sizeof(self->d_argc));
	DBG_memset(&self->d_argv, 0xcc, sizeof(self->d_argv));
	DBG_memset(&self->d_depcnt, 0xcc, sizeof(self->d_depcnt));
	DBG_memset(&self->d_depvec, 0xcc, sizeof(self->d_depvec));
	DBG_memset(&self->d_eh_frame_start, 0xcc, sizeof(self->d_eh_frame_start));
	DBG_memset(&self->d_eh_frame_end, 0xcc, sizeof(self->d_eh_frame_end));
	DBG_memset(&self->d_eh_frame_cache, 0xcc, sizeof(self->d_eh_frame_cache));
	DBG_memset(&self->d_eh_frame_cache_lock, 0xcc, sizeof(self->d_eh_frame_cache_lock));
	DBG_memset(&self->d_dyncnt, 0xcc, sizeof(self->d_dyncnt));
	DBG_memset(&self->d_dynhdr, 0xcc, sizeof(self->d_dynhdr));
	DBG_memset(&self->d_dynsym_tab, 0xcc, sizeof(self->d_dynsym_tab));
	DBG_memset(&self->d_dynsym_cnt, 0xcc, sizeof(self->d_dynsym_cnt));
	DBG_memset(&self->d_gnuhashtab, 0xcc, sizeof(self->d_gnuhashtab));
	DBG_memset(&self->d_hashtab, 0xcc, sizeof(self->d_hashtab));
	DBG_memset(&self->d_dynstr, 0xcc, sizeof(self->d_dynstr));
	DBG_memset(&self->d_dynstr_end, 0xcc, sizeof(self->d_dynstr_end));
	DBG_memset(&self->d_shstrndx, 0xcc, sizeof(self->d_shstrndx));
	DBG_memset(&self->d_shdr, 0xcc, sizeof(self->d_shdr));
	DBG_memset(&self->d_shstrtab, 0xcc, sizeof(self->d_shstrtab));
	DBG_memset(&self->d_shstrsiz, 0xcc, sizeof(self->d_shstrsiz));
	DBG_memset(&self->_d_mm_lop, 0xcc, sizeof(self->_d_mm_lop));
	DBG_memset(&self->_d_initthread, 0xcc, sizeof(self->_d_initthread));
	DBG_memset(&self->d_phdr, 0xcc, self->d_phnum * sizeof(ElfW(Phdr)));
	DBG_memset(&self->d_phnum, 0xcc, sizeof(self->d_phnum));
#ifdef LIBUNWIND_HAVE_ARM_EXIDX
	DBG_memset(&self->d_ARM_exidx_start, 0xcc, sizeof(self->d_ARM_exidx_start));
	DBG_memset(&self->d_ARM_exidx_end, 0xcc, sizeof(self->d_ARM_exidx_end));
#endif /* LIBUNWIND_HAVE_ARM_EXIDX */

	/* Try to remove `self' from the current `drivers'. And if
	 * that's not possible, set `loaded_drivers_contains_dead'
	 * For  simplicity, just remove  _all_ dead drivers (which
	 * ought  to include `self', since `wasdestroyed(self)' is
	 * the case at this point!) */
	if (!remove_dead_drivers_from_loadlist())
		loaded_drivers_contains_dead = true;

	/* Using lock operations, remove all still-loaded
	 * driver sections from the module section cache. */
	while (self->d_shnum) {
		REF struct driver_section *sect;
		--self->d_shnum;
		sect = awref_get(&self->d_sections[self->d_shnum]);
		if (!sect)
			continue; /* Section was never allocated or is dead. */
		if unlikely(!LIST_ISBOUND(&sect->ds_sect, ms_cache)) {
			decref_unlikely(sect);
			continue; /* Section isn't apart of the cache... */
		}

		/* Must remove this section from the cache. */
		if (module_section_cache_tryacquire()) {
			if likely(LIST_ISBOUND(&sect->ds_sect, ms_cache)) {
				LIST_UNBIND(&sect->ds_sect, ms_cache);
				decref_nokill(sect);
			}
			_module_section_cache_release();
			decref_likely(sect);
			module_section_cache_reap();
		} else {
			/* Must use a lockop to unbind the section
			 * once the cache lock becomes  available.
			 *
			 * For  this  purpose, we  (re-)use  the original
			 * driver  object as a  storage container for the
			 * a lockop descriptor that's then used to remove
			 * all  of the module's  sections from the module
			 * section cache. */
			++self->d_shnum; /* Must do the last section once again! */
			self->_d_lop.lo_func = &driver_unbind_sections_and_destroy_lop;
			SLIST_ATOMIC_INSERT(&module_section_cache_lops, &self->_d_lop, lo_link);
			decref_unlikely(sect);
			_module_section_cache_reap();
			return;
		}
	}
	driver_clear_mnode_pointers_and_destroy(self);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL driver_nonodes_cleanup_postlop)(Tobpostlockop(mman) *__restrict self,
                                              struct mman *__restrict UNUSED(mm)) {
	struct driver *me;
	me = container_of(self, struct driver, _d_mm_postlop);
	driver_free_(me);
}

PRIVATE NOBLOCK NONNULL((1)) Tobpostlockop(mman) *
NOTHROW(FCALL driver_nonodes_cleanup_lop)(Toblockop(mman) *__restrict self,
                                          struct mman *__restrict UNUSED(mm)) {
	struct driver *me;
	me = container_of(self, struct driver, _d_mm_lop);
	me->_d_mm_postlop.oplo_func = &driver_nonodes_cleanup_postlop;
	return &me->_d_mm_postlop;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL driver_nonodes)(struct driver *__restrict self) {
	/* The node-counter of drivers is always holding an implicit weak reference.
	 * Once  all mem-nodes have  gone away, we must  simply drop that reference. */
	assert(self->d_module.md_weakrefcnt >= 1);
	if (atomic_decfetch(&self->d_module.md_weakrefcnt) == 0) {

		/* Enqueue a lock operation for the kernel mman to-be performed
		 * once the kernel mman lock has been released in order to free
		 * the driver control structure.
		 * We don't do this inline to reduce the time spent holding onto
		 * the kernel mman mappings lock (which our caller is  currently
		 * holding) */
		self->_d_mm_lop.olo_func = &driver_nonodes_cleanup_lop;
		SLIST_ATOMIC_INSERT(&mman_kernel_lockops,
		                    &self->_d_mm_lop, olo_link);

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

PRIVATE NOBLOCK NONNULL((1, 2)) bool
NOTHROW(FCALL image_validate)(struct driver *__restrict self,
                              void const *src, size_t num_bytes);

PRIVATE WUNUSED NONNULL((1)) REF struct driver_section *FCALL
driver_locksection_index(struct driver *__restrict self,
                         unsigned int section_index) {
	ElfW(Shdr) *shdr;
	REF struct driver_section *result;

	/* Check if the given section index is valid. */
	if unlikely(section_index >= self->d_shnum)
		return NULL;

	/* Try to return an already-loaded section */
again:
	result = awref_get(&self->d_sections[section_index]);
	if (result)
		return result;

	/* Must create a new section object. */
	result = (REF struct driver_section *)kmalloc(sizeof(struct driver_section),
	                                              GFP_PREFLT);

	/* Fill in information about the section. */
	shdr = &self->d_shdr[section_index];
	result->ds_sect.ms_refcnt  = 2; /* +1:return, +1:module_section_cache */
	result->ds_sect.ms_ops     = &driver_section_ops;
	result->ds_sect.ms_module  = weakincref(&self->d_module);
	result->ds_sect.ms_size    = shdr->sh_size;
	result->ds_sect.ms_entsize = shdr->sh_entsize;
	result->ds_sect.ms_type    = shdr->sh_type;
	result->ds_sect.ms_flags   = shdr->sh_flags;
	result->ds_sect.ms_link    = shdr->sh_link;
	result->ds_sect.ms_info    = shdr->sh_info;
	result->ds_shdr            = shdr;
	result->ds_addr            = (byte_t *)-1;
	result->ds_infladdr        = (byte_t *)-1;
	result->ds_inflsize        = 0;
	if (shdr->sh_flags & SHF_ALLOC) {
		byte_t *addr;
		addr = (byte_t *)(self->d_module.md_loadaddr + shdr->sh_addr);
		if (image_validate(self, addr, shdr->sh_size)) {
			result->ds_addr = addr;
			if (!(shdr->sh_flags & SHF_COMPRESSED)) {
				result->ds_infladdr = addr;
				result->ds_inflsize = shdr->sh_size;
			}
		}
	}

	/* Acquire a lock to the module section cache. */
	TRY {
		module_section_cache_acquire();
	} EXCEPT {
		destroy(result);
		RETHROW();
	}

	/* Replace a previously destroyed section object with the new section! */
	if (!awref_replacedead(&self->d_sections[section_index], result)) {
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
	LIST_INSERT_HEAD(&module_section_cache, &result->ds_sect, ms_cache);

	/* Release the lock from the module section cache. */
	module_section_cache_release();

	return result;
}

PRIVATE WUNUSED NONNULL((1)) REF struct driver_section *FCALL
driver_locksection(struct driver *__restrict self,
                   NCX char const *section_name) {
	unsigned int i;
	for (i = 0; i < self->d_shnum; ++i) {
		char const *name;
		if unlikely(self->d_shdr[i].sh_name >= self->d_shstrsiz)
			continue; /* Shouldn't happen... */
		name = self->d_shstrtab + self->d_shdr[i].sh_name;
		if (strcmp(name, section_name) == 0)
			break; /* Found it! */
	}
	return driver_locksection_index(self, i);
}


PRIVATE WUNUSED NONNULL((1, 3)) bool FCALL
driver_sectinfo(struct driver *__restrict self,
                uintptr_t module_relative_addr,
                struct module_sectinfo *__restrict info) {
	unsigned int i;
	bool allow_section_end_pointers;
	allow_section_end_pointers = false;
again:
	for (i = 0; i < self->d_shnum; ++i) {
		if (module_relative_addr < self->d_shdr[i].sh_addr)
			continue;
		if (module_relative_addr >= self->d_shdr[i].sh_addr + self->d_shdr[i].sh_size) {
			if (!allow_section_end_pointers)
				continue;
			if (module_relative_addr > self->d_shdr[i].sh_addr + self->d_shdr[i].sh_size)
				continue;
		}

		/* Found it! (fill in section information for our caller) */
		info->msi_name    = (char *)&kernel_shstrtab_data + self->d_shdr[i].sh_name;
		info->msi_addr    = self->d_shdr[i].sh_addr;
		info->msi_size    = self->d_shdr[i].sh_size;
		info->msi_entsize = self->d_shdr[i].sh_entsize;
		info->msi_type    = self->d_shdr[i].sh_type;
		info->msi_flags   = self->d_shdr[i].sh_flags;
		info->msi_link    = self->d_shdr[i].sh_link;
		info->msi_info    = self->d_shdr[i].sh_info;
		info->msi_index   = i;
		return true;
	}
	if (!allow_section_end_pointers) {
		allow_section_end_pointers = true;
		goto again;
	}
	return false;
}


PRIVATE ATTR_PURE WUNUSED NONNULL((1)) void const *
NOTHROW(FCALL get_segment_start_byflags)(struct driver const *__restrict self,
                                         ElfW(Word) pf_flags) {
	void const *result;
	ElfW(Half) i;
	/* Search for the lowest program header with the correct flags. */
	for (result = (void const *)-1, i = 0; i < self->d_phnum; ++i) {
		uintptr_t hdraddr;
		if (self->d_phdr[i].p_type != PT_LOAD)
			continue;
		if ((self->d_phdr[i].p_flags & (PF_R | PF_W | PF_X)) != pf_flags)
			continue;
		hdraddr = self->d_module.md_loadaddr + self->d_phdr[i].p_vaddr;
		if ((uintptr_t)result > hdraddr)
			result = (void *)hdraddr;
	}
	if (result == (void const *)-1)
		result = NULL;
	return result;
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) void const *
NOTHROW(FCALL driver_get_tbase)(struct driver const *__restrict self) {
	return get_segment_start_byflags(self, PF_R | PF_X);
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) void const *
NOTHROW(FCALL driver_get_dbase)(struct driver const *__restrict self) {
#if defined(__i386__) && !defined(__x86_64__)
	/* Special case for data-base on i386:
	 * For reference, see Glibc: `/sysdeps/generic/unwind-dw2-fde-glibc.c' */
	size_t i;
	for (i = 0; i < self->d_dyncnt; ++i) {
		if (self->d_dynhdr[i].d_tag == DT_PLTGOT) {
			return (void const *)(self->d_module.md_loadaddr +
			                      self->d_dynhdr[i].d_un.d_ptr);
		}
	}
	return NULL;
#else /* __i386__ && !__x86_64__ */
	return get_segment_start_byflags(self, PF_R | PF_W);
#endif /* !__i386__ || __x86_64__ */
}



PRIVATE struct module_ops const driver_module_ops = {
	.mo_free              = (NONNULL_T((1)) void NOTHROW_T(FCALL *)(struct module *__restrict))&driver_free_,
	.mo_destroy           = (NONNULL_T((1)) void NOTHROW_T(FCALL *)(struct module *__restrict))&driver_destroy,
	.mo_nonodes           = (NONNULL_T((1)) void NOTHROW_T(FCALL *)(struct module *__restrict))&driver_nonodes,
	.mo_locksection       = (WUNUSED_T NONNULL_T((1)) REF struct module_section *(FCALL *)(struct module *__restrict, NCX char const *))&driver_locksection,
	.mo_locksection_index = (WUNUSED_T NONNULL_T((1)) REF struct module_section *(FCALL *)(struct module *__restrict, unsigned int))&driver_locksection_index,
	.mo_sectinfo          = (WUNUSED_T NONNULL_T((1, 3)) bool (FCALL *)(struct module *__restrict, uintptr_t, struct module_sectinfo *__restrict))&driver_sectinfo,
	.mo_get_tbase         = (WUNUSED_T NONNULL_T((1)) void const *NOTHROW_T(FCALL *)(struct module *__restrict))&driver_get_tbase,
	.mo_get_dbase         = (WUNUSED_T NONNULL_T((1)) void const *NOTHROW_T(FCALL *)(struct module *__restrict))&driver_get_dbase
};



PRIVATE NONNULL((1)) void FCALL
driver_verify_ElfEhdr(ElfW(Ehdr) const *__restrict ehdr)
		THROWS(E_NOT_EXECUTABLE) {
	unsigned int reason;
	if unlikely(ehdr->e_ident[EI_MAG0] != ELFMAG0 ||
	            ehdr->e_ident[EI_MAG1] != ELFMAG1 ||
	            ehdr->e_ident[EI_MAG2] != ELFMAG2 ||
	            ehdr->e_ident[EI_MAG3] != ELFMAG3)
		THROW(E_NOT_EXECUTABLE_NOT_A_BINARY);
	reason = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADCLASS;
	if unlikely(ehdr->e_ident[EI_CLASS] != KERNEL_DRIVER_REQUIRED_CLASS)
		goto err_elf_reason;
	reason = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADORDER;
	if unlikely(ehdr->e_ident[EI_DATA] != KERNEL_DRIVER_REQUIRED_DATA)
		goto err_elf_reason;
	reason = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADVERSION;
	if unlikely(ehdr->e_ident[EI_VERSION] != EV_CURRENT)
		goto err_elf_reason;
	reason = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADVERSION2;
	if unlikely(ehdr->e_version != EV_CURRENT)
		goto err_elf_reason;
	reason = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADTYPE;
	if unlikely(ehdr->e_type != ET_DYN)
		goto err_elf_reason;
	reason = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADMACH;
	if unlikely(ehdr->e_machine != KERNEL_DRIVER_REQUIRED_MACHINE)
		goto err_elf_reason;
	reason = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADHEADER;
	if unlikely(ehdr->e_ehsize < offsetafter(ElfW(Ehdr), e_phnum))
		goto err_elf_reason;
	reason = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADSEGMENTS;
	if unlikely(ehdr->e_phentsize != sizeof(ElfW(Phdr)))
		goto err_elf_reason;
	return;
err_elf_reason:
	THROW(E_NOT_EXECUTABLE_FAULTY,
	      E_NOT_EXECUTABLE_FAULTY_FORMAT_ELF,
	      reason);
}


PRIVATE NONNULL((1)) void FCALL
driver_init_cmdline(struct driver *__restrict self,
                    NCX char const *cmdline)
		THROWS(E_BADALLOC, E_SEGFAULT, E_WOULDBLOCK) {
	size_t cmdline_size;
	char *cmdline_copy;
	cmdline_size = strlen(cmdline);
	cmdline_copy = (char *)kmalloc((cmdline_size + 2) * sizeof(char),
	                               GFP_LOCKED | GFP_PREFLT);
	TRY {
		memcpy(cmdline_copy, cmdline, cmdline_size, sizeof(char));

		/* Add a double-NUL terminator to allow the commandline
		 * to  always be interpreted into a NUL-NUL string-list */
		cmdline_copy[cmdline_size + 0] = '\0';
		cmdline_copy[cmdline_size + 1] = '\0';

		/* Split the commandline through use of libcmdline */
		self->d_argv = cmdline_decode_argv(cmdline_copy, &self->d_argc,
		                                   GFP_LOCKED | GFP_PREFLT);
	} EXCEPT {
		kfree(cmdline_copy);
		RETHROW();
	}
	self->d_cmdline = cmdline_copy;
}


/* Destroy a partially initialized driver `self' */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL destroy_partially_initialized_driver)(struct driver *__restrict self) {
	kfree(self->d_depvec);
	kfree(self->d_sections);
	kfree(self->d_shstrtab);
	kfree(self->d_shdr);
	kfree(self->d_argv);
	kfree(self->d_cmdline);
	kfree(self);
}

PRIVATE NOBLOCK ATTR_PURE NONNULL((1, 2)) bool
NOTHROW(FCALL image_validate)(struct driver *__restrict self,
                              void const *src, size_t num_bytes) {
	return (byte_t const *)src >= self->d_module.md_loadmin &&
	       (byte_t const *)src + num_bytes <= (self->d_module.md_loadmax + 1);
}

PRIVATE NOBLOCK NONNULL((1, 2)) bool
NOTHROW(FCALL image_read_nopf)(struct driver *__restrict self,
                               void *dst, void const *src,
                               size_t num_bytes) {
	if unlikely(!image_validate(self, src, num_bytes))
		return false;
	return memcpy_nopf(dst, src, num_bytes) == 0;
}

/* Using the driver's currently loaded image,
 * initialize the following fields of `self':
 *
 * >> char const               *d_name;
 * >> byte_t const             *d_eh_frame_start;
 * >> byte_t const             *d_eh_frame_end;
 * >> #ifdef LIBUNWIND_HAVE_ARM_EXIDX
 * >> byte_t const             *d_ARM_exidx_start;
 * >> byte_t const             *d_ARM_exidx_end;
 * >> #endif // LIBUNWIND_HAVE_ARM_EXIDX
 * >> size_t                    d_dyncnt;
 * >> ElfW(Dyn) const          *d_dynhdr;
 * >> ElfW(Sym) const          *d_dynsym_tab;
 * >> size_t                    d_dynsym_cnt;
 * >> ElfW(GnuHashTable) const *d_gnuhashtab;
 * >> ElfW(HashTable) const    *d_hashtab;
 * >> char const               *d_dynstr;
 * >> char const               *d_dynstr_end;
 *
 * @return: 0 : Success
 * @return: * : Corrupted image (`return' is one of `E_NOT_EXECUTABLE_FAULTY_REASON_ELF_*') */
PRIVATE NOBLOCK NONNULL((1)) unsigned int
NOTHROW(FCALL driver_load_image_pointers)(struct driver *__restrict self,
                                          uintptr_t reasons[2]) {
	char lastch;
	size_t i;
	ElfW(Half) pt_dynamic_idx;
	uintptr_t soname_offset;
	size_t dynstr_size;

	/* Locate the `.dynamic' section */
	for (pt_dynamic_idx = 0;; ++pt_dynamic_idx) {
		if (pt_dynamic_idx >= self->d_phnum)
			return E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NO_DYNAMIC;
		if (read_once(&self->d_phdr[pt_dynamic_idx].p_type) == PT_DYNAMIC)
			break;
	}

	/* Write-back information about the `.dynamic' section. */
	self->d_dynhdr = (ElfW(Dyn) *)(self->d_module.md_loadaddr + self->d_phdr[pt_dynamic_idx].p_vaddr);
	self->d_dyncnt = self->d_phdr[pt_dynamic_idx].p_memsz / sizeof(ElfW(Dyn));
	if (!image_validate(self, self->d_dynhdr, self->d_dyncnt * sizeof(ElfW(Dyn))))
		return E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_DYNAMIC;
	self->d_dynsym_tab = NULL;
	self->d_gnuhashtab = NULL;
	self->d_hashtab    = NULL;
	self->d_dynstr     = NULL;
	soname_offset      = (uintptr_t)-1;
	dynstr_size        = (size_t)-1;
	for (i = 0; i < self->d_dyncnt; ++i) {
		ElfW(Dyn) tag;
		if (memcpy_nopf(&tag, &self->d_dynhdr[i], sizeof(tag)) != 0)
			return E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_DYNAMIC;
		switch (tag.d_tag) {

		case DT_NULL:
			self->d_dyncnt = i;
			goto done_dynhdr;

		case DT_SONAME:
			soname_offset = tag.d_un.d_ptr;
			break;

		case DT_STRTAB:
			self->d_dynstr = (char *)(self->d_module.md_loadaddr + tag.d_un.d_ptr);
			break;

		case DT_STRSZ:
			dynstr_size = tag.d_un.d_val;
			break;

		case DT_HASH:
			self->d_hashtab = (ElfW(HashTable) *)(self->d_module.md_loadaddr + tag.d_un.d_ptr);
			break;

		case DT_GNU_HASH:
			self->d_gnuhashtab = (ElfW(GnuHashTable) const *)(self->d_module.md_loadaddr + tag.d_un.d_ptr);
			break;

		case DT_SYMTAB:
			self->d_dynsym_tab = (ElfW(Sym) *)(self->d_module.md_loadaddr + tag.d_un.d_ptr);
			break;

		case DT_SYMENT:
			if unlikely(tag.d_un.d_val != sizeof(ElfW(Sym)))
				THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SYMENT, tag.d_un.d_ptr);
			break;

		case DT_RELAENT:
			if unlikely(tag.d_un.d_val != sizeof(ElfW(Rela)))
				THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_RELAENT, tag.d_un.d_ptr);
			break;

		case DT_RELENT:
			if unlikely(tag.d_un.d_val != sizeof(ElfW(Rel)))
				THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_RELENT, tag.d_un.d_ptr);
			break;

		default:
			break;
		}
	}
done_dynhdr:
	if unlikely(!self->d_dynstr)
		return E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NO_SONAME;
	if (dynstr_size == (size_t)-1) {
		/* Determine the .dynstr segment size by searching for the associated section header. */
		for (i = 0; i < self->d_shnum; ++i) {
			byte_t const *sect_start, *sect_end;
			if (!(self->d_shdr[i].sh_flags & SHF_ALLOC))
				continue; /* Unallocated section... */
			sect_start = (byte_t const *)(self->d_module.md_loadaddr +
			                              self->d_shdr[i].sh_addr);
			if unlikely(!image_validate(self, sect_start, self->d_shdr[i].sh_size))
				continue;
			sect_end = sect_start + self->d_shdr[i].sh_size;
			if ((byte_t const *)self->d_dynstr >= (byte_t const *)sect_start &&
			    (byte_t const *)self->d_dynstr < (byte_t const *)sect_end) {
				/* Found the section! */
				dynstr_size = (size_t)(sect_end - (byte_t const *)self->d_dynstr);
				goto got_dynstr_size;
			}
		}

		/* Check which program header contains the .dynstr segment. */
		for (i = 0; i < self->d_phnum; ++i) {
			byte_t const *phdr_start, *phdr_end;
			if (self->d_phdr[i].p_type != PT_LOAD)
				continue;
			phdr_start = (byte_t const *)(self->d_module.md_loadaddr +
			                              self->d_phdr[i].p_vaddr);
			phdr_end = phdr_start + self->d_phdr[i].p_memsz;
			if ((byte_t const *)self->d_dynstr >= (byte_t const *)phdr_start &&
			    (byte_t const *)self->d_dynstr < (byte_t const *)phdr_end) {
				/* Found the program header! */
				dynstr_size = (size_t)(phdr_end - (byte_t const *)self->d_dynstr);
				goto got_dynstr_size;
			}
		}

		/* Error: Nothing appears to be mapping the .dynstr segment... */
		reasons[0] = (uintptr_t)self->d_dynstr - self->d_module.md_loadaddr;
		reasons[1] = 1;
		return E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_DYNSTR;
	}
got_dynstr_size:
	if unlikely(!image_validate(self, self->d_dynstr, dynstr_size)) {
		reasons[0] = (uintptr_t)self->d_dynstr - self->d_module.md_loadaddr;
		reasons[1] = dynstr_size;
		return E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_DYNSTR;
	}
	if unlikely(soname_offset >= dynstr_size)
		return E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SONAME;

	/* Try to include as many trailing NUL characters with .dynstr as possible. */
	while ((byte_t const *)(self->d_dynstr + dynstr_size) <= self->d_module.md_loadmax &&
	       memcpy_nopf(&lastch, &self->d_dynstr[dynstr_size], sizeof(lastch)) == 0 &&
	       lastch == '\0')
		++dynstr_size;
	self->d_dynstr_end = self->d_dynstr + dynstr_size;
	self->d_name       = self->d_dynstr + soname_offset;

	/* Make sure that `d_name' isn't an empty string! */
	if (memcpy_nopf(&lastch, self->d_name, sizeof(lastch)) != 0 || lastch == '\0')
		return E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SONAME;

	/* Make sure that the DT_SONAME string is NUL-terminated _before_ the end of the .dynstr table. */
	{
		size_t soname_len = 1;
		for (;;) {
			if (memcpy_nopf(&lastch, &self->d_name[soname_len], sizeof(lastch)) != 0)
				return E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SONAME;
			if (lastch == '\0')
				break;
			++soname_len;
		}
	}

	/* Verify .dynsym & friends. */
	if (self->d_dynsym_tab != NULL) {
		self->d_dynsym_cnt = 0;
		if (self->d_hashtab) {
			struct {
				ElfW(Word) ht_nbuckts; /* # of buckets. */
				ElfW(Word) ht_nchains; /* # of symbols. */
			} hashtab_hdr;
			size_t hashsize, temp;
			if (!image_read_nopf(self, &hashtab_hdr, self->d_hashtab, sizeof(hashtab_hdr))) {
bad_elf_symhash:
				reasons[0] = (uintptr_t)self->d_hashtab - self->d_module.md_loadaddr;
				return E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SYMHASH;
			}

			/* Verify that the ELF `.hash' section is in-bounds of the driver image. */
			if (OVERFLOW_UMUL(hashtab_hdr.ht_nbuckts, sizeof(ElfW(Word)), &temp))
				goto bad_elf_symhash;
			if (OVERFLOW_UADD(offsetof(ElfW(HashTable), ht_table), temp, &hashsize))
				goto bad_elf_symhash;
			if (OVERFLOW_UMUL(hashtab_hdr.ht_nbuckts, sizeof(ElfW(Word)), &temp))
				goto bad_elf_symhash;
			if (OVERFLOW_UADD(hashsize, temp, &hashsize))
				goto bad_elf_symhash;
			if (!image_validate(self, self->d_hashtab, hashsize))
				goto bad_elf_symhash;
			if (self->d_dynsym_cnt == 0)
				self->d_dynsym_cnt = (size_t)hashtab_hdr.ht_nchains;
		}
		if (self->d_gnuhashtab) {
			size_t count;
			struct {
				ElfW(Word) gh_nbuckets;      /* # of buckets. */
				ElfW(Word) gh_symoffset;     /* Offset of symbol indices. */
				ElfW(Word) gh_bloom_size;    /* # of elements in the bloom table. */
				ElfW(Word) gh_bloom_shift;   /* Shift for bloom masks */
			} hashtab_hdr;
			ElfW(Word) const *buckets, *chains;
			if (!image_read_nopf(self, &hashtab_hdr, self->d_gnuhashtab, sizeof(hashtab_hdr))) {
bad_gnu_symhash:
				reasons[0] = (uintptr_t)self->d_hashtab - self->d_module.md_loadaddr;
				return E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_GNUSYMHASH;
			}

			/* GNU hash tables are a bit more complicated, since we need  to
			 * find the symbol with the greatest index, then add +1 to that. */
			buckets = (ElfW(Word) const *)(self->d_gnuhashtab->gh_bloom + hashtab_hdr.gh_bloom_size);
			chains  = (ElfW(Word) const *)(buckets + hashtab_hdr.gh_nbuckets);
			if unlikely(!image_validate(self, self->d_gnuhashtab,
			                            (size_t)((byte_t const *)chains -
			                                     (byte_t const *)self->d_gnuhashtab)))
				goto bad_gnu_symhash;
			if (memcpy_nopf(&count, &chains[-1], sizeof(count)) != 0)
				goto bad_gnu_symhash;
			for (;;) {
				ElfW(Word) word;
				if (!image_read_nopf(self, &word, &chains[count - hashtab_hdr.gh_symoffset], sizeof(word)))
					goto bad_gnu_symhash;
				if ((word & 1) != 0)
					break;
				++count;
			}
			if (self->d_dynsym_cnt == 0)
				self->d_dynsym_cnt = count;
		}
		if (self->d_dynsym_cnt == 0) {
			/* Calculate # of symbols based on section info. */
			for (i = 0; i < self->d_shnum; ++i) {
				byte_t const *sect_start, *sect_end;
				if (!(self->d_shdr[i].sh_flags & SHF_ALLOC))
					continue; /* Unallocated section... */
				sect_start = (byte_t const *)(self->d_module.md_loadaddr +
				                              self->d_shdr[i].sh_addr);
				if unlikely(!image_validate(self, sect_start, self->d_shdr[i].sh_size))
					continue;
				sect_end = sect_start + self->d_shdr[i].sh_size;
				if ((byte_t const *)self->d_dynsym_tab >= (byte_t const *)sect_start &&
				    (byte_t const *)self->d_dynsym_tab < (byte_t const *)sect_end) {
					/* Found the section! */
					self->d_dynsym_cnt = (size_t)((ElfW(Sym) const *)sect_end - self->d_dynsym_tab);
					goto got_dynsym_size;
				}
			}

			/* Calculate # of symbols based on program headers. */
			for (i = 0; i < self->d_phnum; ++i) {
				byte_t const *phdr_start, *phdr_end;
				if (self->d_phdr[i].p_type != PT_LOAD)
					continue;
				phdr_start = (byte_t const *)(self->d_module.md_loadaddr +
				                              self->d_phdr[i].p_vaddr);
				phdr_end = phdr_start + self->d_phdr[i].p_memsz;
				if ((byte_t const *)self->d_dynstr >= (byte_t const *)phdr_start &&
				    (byte_t const *)self->d_dynstr < (byte_t const *)phdr_end) {
					/* Found the program header! */
					self->d_dynsym_cnt = (size_t)((ElfW(Sym) const *)phdr_end - self->d_dynsym_tab);
					goto got_dynsym_size;
				}
			}
err_bad_dynsym:
			reasons[0] = (uintptr_t)self->d_dynsym_tab - self->d_module.md_loadaddr;
			return E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_DYNSYM;
		}

		/* Verify that the .dynsym section is in-bounds. */
		{
			size_t dynsym_size;
			if unlikely(OVERFLOW_UMUL(self->d_dynsym_cnt, sizeof(ElfW(Sym)), &dynsym_size))
				goto err_bad_dynsym;
			if unlikely(!image_validate(self, self->d_dynsym_tab, dynsym_size))
				goto err_bad_dynsym;
		}

	} else {
		/* Without a symbol table, there can be no hash table(s) */
		self->d_dynsym_cnt = 0;
		self->d_hashtab    = NULL;
		self->d_gnuhashtab = NULL;
	}
got_dynsym_size:

	/* Locate this driver's `.eh_frame' section. */
	self->d_eh_frame_start = NULL;
	self->d_eh_frame_end   = NULL;
	for (i = 0; i < self->d_shnum; ++i) {
#define EH_FRAME_SECTION_NAME ".eh_frame"
		char namebuf[sizeof(EH_FRAME_SECTION_NAME)];
		if unlikely(self->d_shdr[i].sh_name >= self->d_shstrsiz)
			continue;
		if (memcpy_nopf(namebuf, self->d_shstrtab + self->d_shdr[i].sh_name, sizeof(namebuf)) != 0)
			continue;
		if (bcmp(namebuf, EH_FRAME_SECTION_NAME, sizeof(EH_FRAME_SECTION_NAME)) != 0)
			continue;
#undef EH_FRAME_SECTION_NAME
		/* Found the `.eh_frame' section! */

		/* Make sure that `.eh_frame' has the SHF_ALLOC flag set! */
		if unlikely(!(self->d_shdr[i].sh_flags & SHF_ALLOC)) {
			reasons[0] = i;
			return E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NALLOC_EH_FRAME;
		}

		/* Set `.eh_frame' section pointers. */
		self->d_eh_frame_start = (byte_t const *)(self->d_module.md_loadaddr + self->d_shdr[i].sh_addr);
		self->d_eh_frame_end   = self->d_eh_frame_start + self->d_shdr[i].sh_size;
		if unlikely(self->d_eh_frame_start > self->d_eh_frame_end ||
		            self->d_eh_frame_start < self->d_module.md_loadmin ||
		            self->d_eh_frame_end > (self->d_module.md_loadmax + 1)) {
			reasons[0] = self->d_shdr[i].sh_addr;
			reasons[1] = self->d_shdr[i].sh_size;
			return E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_EH_FRAME;
		}
		break;
	}

	/* Locate this driver's `.ARM.exidx' section. */
#ifdef LIBUNWIND_HAVE_ARM_EXIDX
	self->d_ARM_exidx_start = NULL;
	self->d_ARM_exidx_end   = NULL;
	for (i = 0; i < self->d_phnum; ++i) {
		if (self->d_phdr[i].p_type == PT_ARM_EXIDX) {
			self->d_ARM_exidx_start = (byte_t const *)(self->d_module.md_loadaddr + self->d_phdr[i].p_vaddr);
			self->d_ARM_exidx_end   = self->d_ARM_exidx_start + self->d_phdr[i].p_memsz;
			if unlikely(self->d_ARM_exidx_start > self->d_ARM_exidx_end ||
			            self->d_ARM_exidx_start < self->d_module.md_loadmin ||
			            self->d_ARM_exidx_end > (self->d_module.md_loadmax + 1)) {
				reasons[0] = self->d_phdr[i].p_vaddr;
				reasons[1] = self->d_phdr[i].p_memsz;
				return E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_EH_FRAME;
			}
			goto got_ARM_exidx;
		}
	}
	/* Just in case its program-header is missing, also search for a section _named_ ".ARM.exidx" */
	for (i = 0; i < self->d_shnum; ++i) {
#define ARM_EXIDX_SECTION_NAME ".ARM.exidx"
		char namebuf[sizeof(ARM_EXIDX_SECTION_NAME)];
		if unlikely(self->d_shdr[i].sh_name >= self->d_shstrsiz)
			continue;
		if (memcpy_nopf(namebuf, self->d_shstrtab + self->d_shdr[i].sh_name, sizeof(namebuf)) != 0)
			continue;
		if (bcmp(namebuf, ARM_EXIDX_SECTION_NAME, sizeof(ARM_EXIDX_SECTION_NAME)) != 0)
			continue;
#undef ARM_EXIDX_SECTION_NAME
		/* Found the `.ARM.exidx' section! */

		/* Make sure that `.ARM.exidx' has the SHF_ALLOC flag set! */
		if unlikely(!(self->d_shdr[i].sh_flags & SHF_ALLOC)) {
			reasons[0] = i;
			return E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NALLOC_ARM_EXIDX;
		}

		/* Set `.ARM.exidx' section pointers. */
		self->d_ARM_exidx_start = (byte_t const *)(self->d_module.md_loadaddr + self->d_shdr[i].sh_addr);
		self->d_ARM_exidx_end   = self->d_ARM_exidx_start + self->d_shdr[i].sh_size;
		if unlikely(self->d_ARM_exidx_start > self->d_ARM_exidx_end ||
		            self->d_ARM_exidx_start < self->d_module.md_loadmin ||
		            self->d_ARM_exidx_end > (self->d_module.md_loadmax + 1)) {
			reasons[0] = self->d_shdr[i].sh_addr;
			reasons[1] = self->d_shdr[i].sh_size;
			return E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_ARM_EXIDX;
		}
		goto got_ARM_exidx;
	}

got_ARM_exidx:
#endif /* LIBUNWIND_HAVE_ARM_EXIDX */

	return 0;
}

PRIVATE WUNUSED NONNULL((1)) struct mnode *FCALL
create_mnode_for_phdr(ElfW(Phdr) const *__restrict phdr,
                      NCX byte_t const *base, size_t num_bytes,
                      struct path *drv_fspath, struct fdirent *drv_fsname)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT) {
	struct mnode *node;
	struct mpart *part;

	/* Allocate a new node/part pair. */
	node = (struct mnode *)kmalloc(sizeof(struct mnode), GFP_LOCKED | GFP_PREFLT);
	TRY {
		part = (struct mpart *)kmalloc(sizeof(struct mpart), GFP_LOCKED | GFP_PREFLT);
		TRY {
			PAGEDIR_PAGEALIGNED uintptr_t vaddr;
			PAGEDIR_PAGEALIGNED size_t vsize;
			size_t faddr, fsize, voffs;
			vaddr = phdr->p_vaddr;
			voffs = vaddr & PAGEMASK;
			vsize = phdr->p_memsz + voffs;
			vaddr -= voffs;
			vsize = CEIL_ALIGN(vsize, PAGESIZE);
			faddr = phdr->p_offset;
			fsize = phdr->p_filesz;

			/* Verify that the in-file bounds for the initialization template are OK */
			if unlikely(faddr + fsize < faddr || faddr + fsize > num_bytes) {
				THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_PHDR_OFFSET,
				                       phdr->p_offset, phdr->p_filesz);
			}

			/* Verify that the file-size doesn't exceed the mem-size. */
			if unlikely(voffs + fsize > vsize) {
				THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_PHDR_FSIZE,
				                       phdr->p_filesz, phdr->p_memsz);
			}

			/* Initialize all of the basic fields. */
			node->mn_minaddr = (byte_t *)vaddr;
			node->mn_maxaddr = (byte_t *)vaddr + vsize - 1;
			if unlikely(vsize < phdr->p_memsz || node->mn_minaddr > node->mn_maxaddr) {
				THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_PHDR_VADDR,
				                       phdr->p_vaddr, phdr->p_memsz);
			}
			node->mn_flags   = mnodeflags_from_elfpf(phdr->p_flags) |
			                   MNODE_F_SHARED | MNODE_F_MPREPARED |
			                   MNODE_F_MLOCK | MNODE_F_PWRITE; /* Force write-access for relocations */
			node->mn_part    = part;
			node->mn_fspath  = drv_fspath;
			node->mn_fsname  = drv_fsname;
			node->mn_mman    = &mman_kernel;
			node->mn_partoff = 0;
			node->mn_link.le_prev = &part->mp_share.lh_first;
			node->mn_link.le_next = NULL;
			DBG_memset(&node->mn_module, 0xcc, sizeof(node->mn_module)); /* Done later... */
			LIST_ENTRY_UNBOUND_INIT(&node->mn_writable);
			part->mp_refcnt = 1; /* +1:node->mn_part */
			part->mp_flags  = MPART_F_MLOCK;
			part->mp_xflags = MPART_XF_NORMAL;
			part->mp_file   = &mfile_zero;
			LIST_INIT(&part->mp_copy);
			part->mp_share.lh_first = node;
			SLIST_INIT(&part->mp_lockops);
			LIST_ENTRY_UNBOUND_INIT(&part->mp_allparts);
			part->mp_minaddr = (pos_t)(0);
			part->mp_maxaddr = (pos_t)(vsize - 1);
			DBG_memset(&part->mp_changed, 0xcc, sizeof(part->mp_changed));
			_mpart_init_asanon(part);
			part->mp_blkst_ptr = NULL; /* All parts marked as `MPART_BLOCK_ST_CHNG' */
			part->mp_meta      = NULL;

			/* Allocate physical memory for the part. */
			mpart_ll_allocmem(part, vsize / PAGESIZE);

			/* And with that, all of the data from the part's been
			 * initialized. Now all that's left  to be done is  to
			 * copy over data from the caller-given initialization
			 * blob, and paste it into the part's physical  memory
			 * buffer! */
			TRY {
				mpart_reladdr_t dst = 0;

				/* Zero-initialize a couple of leading bytes. */
				if (voffs != 0) {
					mpart_ll_bzeromemcc(part, dst, voffs);
					dst += voffs;
				}

				/* Copy file initialization data from the template. */
				if (fsize != 0) {
					mpart_ll_writemem(part, dst, base + faddr, fsize);
					dst += fsize;
				}

				/* Finally, zero-initialize all of the trailing (.bss-style) memory. */
				assert(dst <= vsize);
				if (dst < vsize)
					mpart_ll_bzeromemcc(part, dst, vsize - dst);
			} EXCEPT {
				mpart_ll_freemem(part);
				RETHROW();
			}
			incref(&mfile_zero); /* Reference for `part->mp_file' */
			xincref(drv_fspath); /* Reference for `node->mn_fspath' */
			xincref(drv_fsname); /* Reference for `node->mn_fsname' */
		} EXCEPT {
			kfree(part);
			RETHROW();
		}
	} EXCEPT {
		kfree(node);
		RETHROW();
	}
	return node;
}


/* Create  a driver from the given parameters (or return an already-
 * loaded driver that matches the `DT_SONAME' attribute found within
 * the given data-blob) */
PRIVATE BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct driver *KCALL
driver_create(NCX byte_t const *base, size_t num_bytes,
              struct mfile *drv_file, struct path *drv_fspath,
              struct fdirent *drv_fsname,
              NCX char const *drv_cmdline,
              bool *pnew_driver_loaded)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT, E_IOERROR, E_NOT_EXECUTABLE, ...) {
	REF struct driver *result;
	ElfW(Dyn) const *pt_dynamic, *pt_dynamic_end;
	ElfW(Ehdr) const *ehdr;
	ElfW(Phdr) const *phdrv;
	ElfW(Half) phidx, phnum;
	size_t dt_needed_count;
	if unlikely(num_bytes < sizeof(ElfW(Ehdr)))
		THROW(E_NOT_EXECUTABLE_TOOSMALL);

	/* First of: Verify that we're actually dealing with an ELF File. */
	ehdr = (ElfW(Ehdr) const *)base;
	driver_verify_ElfEhdr(ehdr);

	/* Validate the program header pointers. */
	phdrv = (ElfW(Phdr) const *)(base + read_once(&ehdr->e_phoff));
	phnum = read_once(&ehdr->e_phnum);
	if unlikely(phnum > KERNEL_DRIVER_MAXPROGRAMHEADERCOUNT)
		THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_TOOMANYSEGMENTS, phnum);
	if unlikely(!phnum)
		THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NOSEGMENTS);
	if unlikely((byte_t const *)(phdrv) < base ||
	            (byte_t const *)(phdrv + phnum) > base + num_bytes) {
		THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_HEADERS,
		                       (size_t)((byte_t const *)phdrv - base));
	}

	/* Search for the .dynamic section.
	 * We  need find this section first, because it contains the DT_SONAME
	 * tag which we need to determine the driver's name, which is used for
	 * matching the driver against other, already-loaded drivers in  order
	 * to prevent  unnecessary work  when it  comes to  ensuring that  any
	 * driver is only loaded once! */
	for (phidx = 0;; ++phidx) {
		if (phidx >= phnum)
			THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NO_DYNAMIC);
		if (read_once(&phdrv[phidx].p_type) == PT_DYNAMIC)
			break;
	}

	/* Load the in-file range of the .dynamic program header */
	pt_dynamic     = (ElfW(Dyn) const *)(base + read_once(&phdrv[phidx].p_offset));
	pt_dynamic_end = (ElfW(Dyn) const *)((byte_t const *)pt_dynamic + phdrv[phidx].p_filesz);

	/* Ensure that the .dynamic program header bounds are valid. */
	if unlikely((byte_t const *)pt_dynamic > (byte_t const *)pt_dynamic_end ||
	            (byte_t const *)pt_dynamic < base ||
	            (byte_t const *)pt_dynamic_end > base + num_bytes) {
		THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_DYNAMIC,
		                       (size_t)((byte_t const *)pt_dynamic - base));
	}

	/* Search for an existing driver, based on this one's DT_SONAME */
	{
		uintptr_t dynstr_vla    = (uintptr_t)-1;
		uintptr_t soname_offset = (uintptr_t)-1;
		ElfW(Dyn) const *iter;
		dt_needed_count = 0;
		for (iter = pt_dynamic;
		     iter < pt_dynamic_end; ++iter) {
			switch (read_once(&iter->d_tag)) {

			case DT_NULL:
				pt_dynamic_end = iter;
				goto done_dynhdr_for_soname;

			case DT_NEEDED:
				++dt_needed_count;
				break;

			case DT_SONAME:
				soname_offset = read_once(&iter->d_un.d_ptr);
				break;

			case DT_STRTAB:
				dynstr_vla = read_once(&iter->d_un.d_ptr);
				break;

			default:
				break;
			}
		}

done_dynhdr_for_soname:
		/* Make sure that we found both a .dynstr section, as well as a DT_SONAME tag. */
		if unlikely(dynstr_vla == (uintptr_t)-1 || soname_offset == (uintptr_t)-1)
			THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NO_SONAME);

		/* Figure out which PT_LOAD-phdr contains `dynstr_vla' */
		for (phidx = 0;; ++phidx) {
			char *dynstr_base;
			size_t dynstr_offset;
			size_t dynstr_size;
			char *so_name_start;
			char *so_name_end;
			ElfW(Addr) p_vaddr;
			size_t p_filesz;
			if (phidx >= phnum)
				THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SONAME, dynstr_vla);
			if (read_once(&phdrv[phidx].p_type) != PT_LOAD)
				continue;
			p_vaddr = read_once(&phdrv[phidx].p_vaddr);
			if (p_vaddr > dynstr_vla)
				continue;
			p_filesz = read_once(&phdrv[phidx].p_filesz);

			/* Technically p_memsz, but any pointer above would
			 * always  be an empty string, which isn't allowed! */
			if (p_vaddr + p_filesz <= dynstr_vla)
				continue;

			/* Found the segment. */
			dynstr_offset = dynstr_vla - p_vaddr; /* Offset of `.dynstr' in segment */
			dynstr_base   = (char *)(base + read_once(&phdrv[phidx].p_offset) + dynstr_offset);
			dynstr_size   = p_filesz - dynstr_offset;

			/* Make sure that .dynstr is in-bounds of the driver image. */
			if unlikely((byte_t const *)dynstr_base < base || soname_offset > dynstr_size ||
			            (byte_t const *)(dynstr_base + dynstr_size) > base + num_bytes) {
				THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SONAME,
				                       (size_t)((byte_t const *)dynstr_base - base));
			}
			so_name_start = dynstr_base + soname_offset;
			so_name_end   = (char *)memend(so_name_start, '\0', dynstr_size - soname_offset);

			/* All right! we've got the DT_SONAME string!
			 * -> Search for an existing driver with this name. */
			result = driver_fromname_with_len(so_name_start, (size_t)(so_name_end - so_name_start));
			if (result) {
				if (pnew_driver_loaded)
					*pnew_driver_loaded = false;
				return result; /* This driver has already been loaded. */
			}
			break;
		}
	}

	/* Load + initialize a new driver. */
	result = (REF struct driver *)kmalloc(offsetof(struct driver, d_phdr) +
	                                      phnum * sizeof(ElfW(Phdr)),
	                                      GFP_LOCKED | GFP_CALLOC | GFP_PREFLT);
	TRY {
		uintptr_t shoff;
		struct mnode_slist nodes;

		/* Copy program headers. */
		memcpy(result->d_phdr, phdrv, phnum, sizeof(ElfW(Phdr)));

		/* Initialize the driver commandline. */
		if (drv_cmdline) {
			driver_init_cmdline(result, drv_cmdline);
		} else {
			/* Always allocate an argument vector, even if that vector is empty. */
			result->d_argv    = (char **)kmalloc(1 * sizeof(char *), GFP_CALLOC | GFP_LOCKED | GFP_PREFLT);
			result->d_cmdline = (char *)kmalloc(sizeof(char), GFP_CALLOC | GFP_LOCKED | GFP_PREFLT);
		}

		shoff              = (uintptr_t)read_once(&ehdr->e_shoff);
		result->d_shstrndx = read_once(&ehdr->e_shstrndx);
		result->d_shnum    = read_once(&ehdr->e_shnum);
		COMPILER_READ_BARRIER();
		if unlikely(read_once(&ehdr->e_shentsize) != sizeof(ElfW(Shdr)))
			THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SHENT, ehdr->e_shentsize);
		if unlikely(result->d_shnum > ELF_ARCH_MAXSHCOUNT)
			THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_TOOMANYSECTIONS, result->d_shnum);

		/* Validate offsets for section headers */
		if unlikely(result->d_shstrndx >= result->d_shnum) {
			THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SHSTRNDX,
			                       result->d_shstrndx, result->d_shnum);
		}
		if unlikely(shoff >= num_bytes || shoff + (result->d_shnum * sizeof(ElfW(Shdr))) > num_bytes) {
			THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SHOFF,
			                       shoff, result->d_shnum, num_bytes);
		}

		/* Load the sections header into memory. */
		result->d_shdr = (ElfW(Shdr) *)kmalloc(result->d_shnum * sizeof(ElfW(Shdr)), GFP_PREFLT);
		memcpy((ElfW(Shdr) *)result->d_shdr, base + shoff,
		       result->d_shnum, sizeof(ElfW(Shdr)));

		/* Allocate the driver section reference vector. */
		result->d_sections = (struct driver_section_awref *)kmalloc(result->d_shnum *
		                                                            sizeof(struct driver_section_awref),
		                                                            GFP_PREFLT | GFP_CALLOC);

		/* Load the section header string table. */
		{
			ElfW(Shdr) const *shstrtab;
			size_t shstrtab_size;
			char const *shstrtab_base, *shstrtab_end;
			shstrtab = &result->d_shdr[result->d_shstrndx];
			if unlikely(shstrtab->sh_type == SHT_NOBITS) {
				THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NOBITS_SHSTRTAB,
				                       result->d_shstrndx);
			}
			shstrtab_base = (char *)(base + shstrtab->sh_offset);
			shstrtab_size = shstrtab->sh_size;
			shstrtab_end  = shstrtab_base + shstrtab_size;
			if unlikely((byte_t const *)shstrtab_end < (byte_t const *)shstrtab_base ||
			            (byte_t const *)shstrtab_base < base ||
			            (byte_t const *)shstrtab_end > base + num_bytes) {
				THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SHSTRTAB,
				                       (size_t)((byte_t const *)shstrtab_base - base),
				                       shstrtab_size, num_bytes);
			}
			while (shstrtab_size && !shstrtab_base[shstrtab_size - 1])
				--shstrtab_size;

			/* Load the .shstrtab section into memory. */
			result->d_shstrtab = (char *)kmalloc((shstrtab_size + 1) * sizeof(char), GFP_PREFLT);
			memcpy((char *)result->d_shstrtab, shstrtab_base, shstrtab_size, sizeof(char));
			((char *)result->d_shstrtab)[shstrtab_size] = '\0';
			result->d_shstrsiz = shstrtab_size;
		}

		/* Allocate the vector of dependencies. */
		result->d_depcnt = dt_needed_count;
		result->d_depvec = (struct driver_axref *)kmalloc(dt_needed_count * sizeof(struct driver_axref),
		                                                  GFP_CALLOC | GFP_PREFLT);

		/* Create fully faulted+locked mnode/mpart pairs
		 * for all  of  the  driver's  program  headers. */
		SLIST_INIT(&nodes);
		TRY {

			result->d_module.md_loadmin = (byte_t *)-1;
			for (phidx = 0; phidx < phnum; ++phidx) {
				struct mnode *node;
				if (result->d_phdr[phidx].p_type != PT_LOAD)
					continue;

				/* Create a new node for this program header. */
				node = create_mnode_for_phdr(&result->d_phdr[phidx],
				                             base, num_bytes,
				                             drv_fspath,
				                             drv_fsname);
				SLIST_INSERT(&nodes, node, _mn_dead);

				/* Update the new driver's min/max bounds according to the new node. */
				if (result->d_module.md_loadmin > node->mn_minaddr)
					result->d_module.md_loadmin = node->mn_minaddr;
				if (result->d_module.md_loadmax < node->mn_maxaddr)
					result->d_module.md_loadmax = node->mn_maxaddr;
			}

			/* The following _really_ shouldn't happen... */
			if unlikely(SLIST_EMPTY(&nodes))
				THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NOSEGMENTS);
			assert(result->d_module.md_loadmin <= result->d_module.md_loadmax);

			/* Fill in simple fields. */
			result->d_module.md_refcnt     = 2; /* +1:<return-value>, +1:The self-reference of `DRIVER_STATE_INIT' */
			result->d_module.md_weakrefcnt = 3; /* +1:md_refcnt != 0, +1:md_nodecount != 0, +1:new_ll->dll_drivers[new_ll_insert_index] */
/*			result->d_module.md_nodecount  = 0; */ /* Already initialized by `GFP_CALLOC' */
			result->d_module.md_ops        = &driver_module_ops;
			result->d_module.md_mman       = &mman_kernel; /* !!! NOT A REFERENCE */
			result->d_module.md_file       = xincref(drv_file);
			result->d_module.md_fspath     = xincref(drv_fspath);
			result->d_module.md_fsname     = xincref(drv_fsname);
#ifdef _MODULE_HAVE_SIZEOF_POINTER
			result->d_module.md_sizeof_pointer = sizeof(void *);
#endif /* _MODULE_HAVE_SIZEOF_POINTER */
#if DRIVER_STATE_INIT != 0
			result->d_state = DRIVER_STATE_INIT;
#endif /* DRIVER_STATE_INIT != 0 */
			result->d_phnum = phnum;
/*			result->d_eh_frame_cache = NULL;*/ /* Already initialized by `GFP_CALLOC' */
			atomic_rwlock_cinit(&result->d_eh_frame_cache_lock);

			TRY {
				REF struct driver_loadlist *old_ll;
				REF struct driver_loadlist *new_ll;

				/* Allocate a new `struct driver_loadlist' descriptor
				 * which can then be used to replace the current one. */
again_get_driver_loadlist:
				old_ll = arref_get(&drivers);
				FINALLY_DECREF_UNLIKELY(old_ll);
				new_ll = (REF struct driver_loadlist *)kmalloc(offsetof(struct driver_loadlist, dll_drivers) +
				                                               (old_ll->dll_count + 1) *
				                                               sizeof(WEAK REF struct driver *),
				                                               GFP_LOCKED | GFP_PREFLT);
				TRY {
					syscache_version_t cache_version = SYSCACHE_VERSION_INIT;
					size_t i, new_ll_insert_index;
					uintptr_t loadaddr;

					/* Acquire a lock to the kernel mman, so we can insert the new nodes. */
again_acquire_mman_lock:
					mman_lock_acquire(&mman_kernel);

					/************************************************************************/
					/* !!!NOEXCEPT FROM HERE!!!                                             */
					/************************************************************************/

					/* Figure out where we want to load the driver. */
					{
						void *loadbase;
						size_t loadsize;
						loadsize = (size_t)((result->d_module.md_loadmax + 1) -
						                    (result->d_module.md_loadmin));
						loadbase = mman_findunmapped(&mman_kernel,
						                             MHINT_GETADDR(KERNEL_MHINT_DRIVER),
						                             loadsize,
						                             MHINT_GETMODE(KERNEL_MHINT_DRIVER));
						if unlikely(loadbase == MAP_FAILED) {
							mman_lock_release(&mman_kernel);
							if (syscache_clear_s(&cache_version))
								goto again_acquire_mman_lock;
							/*driver_deadnodes_freelist(&nodes);*/
							/*destroy_partially_initialized_driver(result);*/
							THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY, loadsize);
						}
						loadaddr = (uintptr_t)((byte_t *)loadbase - result->d_module.md_loadmin);
					}
					result->d_module.md_loadaddr = loadaddr;
					result->d_module.md_loadmin += loadaddr;
					result->d_module.md_loadmax += loadaddr;

					/* Insert all of the driver's mem-nodes into the kernel mman. */
					while (!SLIST_EMPTY(&nodes)) {
						struct mnode *node;
						node = SLIST_FIRST(&nodes);
						SLIST_REMOVE_HEAD(&nodes, _mn_dead);

						/* Relocate the node relative to our chosen `loadaddr'.
						 * NOTE: Because we're using anonymous,  pre-initialized,
						 *       locked mem-parts to  back these  nodes, we  know
						 *       that the  associated mem-parts  won't have  been
						 *       truncated since we've created them above, simply
						 *       because we're the only ones who even know  about
						 *       their existence! */
						node->mn_minaddr += loadaddr;
						node->mn_maxaddr += loadaddr;

						/* Keep track of the # of nodes that map our driver. */
						node->mn_module = &result->d_module;
						++result->d_module.md_nodecount;

						/* Insert this node into the kernel mman. */
						if unlikely(!mman_mappings_tryinsert(&mman_kernel, node)) {
							/* This could happen if the different program headers
							 * overlap with each other (which would be indicative
							 * of a faulty driver file)
							 *
							 * As such, undo all already-inserted nodes, followed
							 * by throwing an exception. */
							SLIST_INSERT(&nodes, node, _mn_dead);
							mman_remove_driver_nodes(result, &nodes);
							mman_lock_release(&mman_kernel);
							/*driver_deadnodes_freelist(&nodes);*/
							/*destroy_partially_initialized_driver(result);*/
							THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_SEGMENTOVERLAP);
						}

						/* Prepare the kernel page directory for the driver. */
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
						if unlikely(!mnode_pagedir_kernelprepare(node)) {
							SLIST_INSERT(&nodes, node, _mn_dead);
							mman_remove_driver_nodes(result, &nodes);
							mman_lock_release(&mman_kernel);
							/*driver_deadnodes_freelist(&nodes);*/
							/*destroy_partially_initialized_driver(result);*/
							THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, 1);
						}
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */

						/* Force-map the node's part into kernelspace. */
						mpart_mmap_force(node->mn_part, mnode_getaddr(node),
						                 mnode_getsize(node), node->mn_partoff,
						                 mnode_getperm_force(node) |
						                 /* Always force write-access  for all mappings,  until
						                  * `driver_initialize()' has finished applying relocs. */
						                 PAGEDIR_PROT_WRITE);
					}
					assert(result->d_module.md_nodecount != 0);

					/* Sync the fact that we've just created bunch of new memory mappings. */
					pagedir_sync(result->d_module.md_loadmin,
					             (size_t)((result->d_module.md_loadmax + 1) -
					                      (result->d_module.md_loadmin)));

					/* At this point, we still have to initialize all of the following,
					 * all of which depend on where we end up loading the driver to, or
					 * are simply easier to calculate once we've mapped the driver:
					 * >> char const               *d_name;
					 * >> byte_t const             *d_eh_frame_start;
					 * >> byte_t const             *d_eh_frame_end;
					 * >> #ifdef LIBUNWIND_HAVE_ARM_EXIDX
					 * >> byte_t const             *d_ARM_exidx_start;
					 * >> byte_t const             *d_ARM_exidx_end;
					 * >> #endif // LIBUNWIND_HAVE_ARM_EXIDX
					 * >> size_t                    d_dyncnt;
					 * >> ElfW(Dyn) const          *d_dynhdr;
					 * >> ElfW(Sym) const          *d_dynsym_tab;
					 * >> size_t                    d_dynsym_cnt;
					 * >> ElfW(GnuHashTable) const *d_gnuhashtab;
					 * >> ElfW(HashTable) const    *d_hashtab;
					 * >> char const               *d_dynstr;
					 * >> char const               *d_dynstr_end;
					 *
					 * NOTE: At this point, we can  also already access the  driver's
					 *       memory mappings (everything was prefaulted at the start,
					 *       meaning  that  everything should  be mapped  right now).
					 *       However, still make use of `memcpy_nopf()', since faulty
					 *       driver files can still cause problems at this point. */
					{
						unsigned int status;
						uintptr_t reasons[2] = { 0, 0 };
						status = driver_load_image_pointers(result, reasons);
						if unlikely(status != 0) {
							mman_remove_driver_nodes(result, &nodes);
							mman_lock_release(&mman_kernel);
							THROW_FAULTY_ELF_ERROR(status, reasons[0], reasons[1]);
						}
					}

					/* Check if the current driver load list already contains
					 * a driver with  a name  identical to  `result->d_name'. */
					new_ll_insert_index = old_ll->dll_count;
					assert_assume(old_ll->dll_count >= 1);
					for (i = 0; i < old_ll->dll_count; ++i) {
						REF struct driver *other_driver;
						other_driver = old_ll->dll_drivers[i];
						if (result->d_module.md_loadmin < other_driver->d_module.md_loadmin)
							new_ll_insert_index = i;
						if (!tryincref(other_driver))
							continue;
						if unlikely(strcmp(other_driver->d_name, result->d_name) == 0) {
							/* Driver already loaded... (undo everything...) */
							mman_remove_driver_nodes(result, &nodes);
							_mman_lock_release(&mman_kernel);
							kfree(new_ll);
							xdecref_nokill(drv_file);
							xdecref_nokill(drv_fspath);
							xdecref_nokill(drv_fsname);
							driver_deadnodes_freelist(&nodes);
							destroy_partially_initialized_driver(result);
							mman_lockops_reap(&mman_kernel);
							if (pnew_driver_loaded)
								*pnew_driver_loaded = false;
							return other_driver;
						}
						decref_unlikely(other_driver);
					}

					/* Initialize the new driver load-list */
					new_ll->dll_refcnt = 1;
					new_ll->dll_count  = old_ll->dll_count + 1;
					memcpy(&new_ll->dll_drivers[0], &old_ll->dll_drivers[0],
					       new_ll_insert_index, sizeof(WEAK REF struct driver *));
					new_ll->dll_drivers[new_ll_insert_index] = result;
					memcpy(&new_ll->dll_drivers[new_ll_insert_index + 1],
					       &old_ll->dll_drivers[new_ll_insert_index],
					       old_ll->dll_count - new_ll_insert_index,
					       sizeof(WEAK REF struct driver *));
					assert_assume(old_ll->dll_count >= 1);
					for (i = 0; i < old_ll->dll_count; ++i)
						weakincref(old_ll->dll_drivers[i]);

					/* Remove drivers that have since been destroyed from the driver load list. */
					for (i = 0; i < new_ll->dll_count;) {
						if likely(!wasdestroyed(new_ll->dll_drivers[i])) {
							++i;
							continue;
						}
						weakdecref_nokill(new_ll->dll_drivers[i]);
						--new_ll->dll_count;
						memmovedown(&new_ll->dll_drivers[i],
						            &new_ll->dll_drivers[i + 1],
						            new_ll->dll_count - i,
						            sizeof(WEAK REF struct driver *));
					}

					/* Write-back the new driver load-list, and check that the  driver
					 * load-list hasn't changed  since then. (If  it did change,  then
					 * there's a chance that the `result'-driver has since been loaded
					 * by some other thread...) */
					if unlikely(!arref_cmpxch_inherit_new(&drivers, old_ll, new_ll)) {

						/* The set of loaded drivers has changed.
						 * Undo everything we did since we've read out `old_ll' */
						struct mnode *node;
						mman_remove_driver_nodes(result, &nodes);
						_mman_lock_release(&mman_kernel);
						destroy(new_ll);
						mman_lockops_reap(&mman_kernel);

						/* Undo relocations already performed based on `loadaddr' */
						/*result->d_module.md_loadaddr = 0;*/ /* Not needed... */
						result->d_module.md_loadmin -= loadaddr;
						result->d_module.md_loadmax -= loadaddr;
						SLIST_FOREACH (node, &nodes, _mn_dead) {
							node->mn_minaddr -= loadaddr;
							node->mn_maxaddr -= loadaddr;
						}
						goto again_get_driver_loadlist;
					}

					/* With everything initialized and double-check for consistency, we
					 * can  finally release our lock from the kernel mman, knowing that
					 * the new driver has been safely loaded into the kernel. */
					mman_lock_release(&mman_kernel);
				} EXCEPT {
					kfree(new_ll);
					RETHROW();
				}
			} EXCEPT {
				xdecref_nokill(drv_file);
				xdecref_nokill(drv_fspath);
				xdecref_nokill(drv_fsname);
				RETHROW();
			}
		} EXCEPT {
			driver_deadnodes_freelist(&nodes);
			RETHROW();
		}
	} EXCEPT {
		destroy_partially_initialized_driver(result);
		RETHROW();
	}

	printk(KERN_NOTICE "[mod][+] Insmod: %q\n", result->d_name);
	if (pnew_driver_loaded)
		*pnew_driver_loaded = true;
	return result;
}


/* Load & return  a driver from  a given `driver_file'.  The
 * returned driver may  not have been  initialized, yet.  As
 * such, the  caller  should  use  `driver_initialize()'  in
 * order to ensure that the returned driver was initialized.
 * @param: pnew_driver_loaded: When non-NULL, set to true/false in
 *                             order to indicate  if the  returned
 *                             driver was newly loaded, or already
 *                             present before. */
PUBLIC BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct driver *KCALL
driver_loadmod_file(struct mfile *__restrict driver_file,
                    struct path *driver_path,
                    struct fdirent *driver_dentry,
                    NCX char const *driver_cmdline,
                    bool *pnew_driver_loaded)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT, E_NOT_EXECUTABLE, E_IOERROR, ...) {
	REF struct driver *result;

	/* Check if we've already got a driver loaded under `driver_file' */
	result = driver_fromfile(driver_file);
	if (result) {
		if (pnew_driver_loaded)
			*pnew_driver_loaded = false;
	} else {
		/* Fallback: Try to create a new driver. */
		void *unmap_cookie, *tempmap;
		pos_t tempmap_size = mfile_getsize(driver_file);

		/* Impose a limit on how large driver files may be. */
		if (tempmap_size >= (pos_t)UINT32_C(0x10000000))
			THROW(E_NOT_EXECUTABLE_TOOLARGE);

		/* Allocate  a cookie which we can use to NOBLOCK-unmap the temporary
		 * mapping of the given `driver_file' once we're done, or upon error. */
		unmap_cookie = mman_unmap_kram_cookie_alloc();

		/* Create a temporary memory mapping of the given file. */
		TRY {
			tempmap = mman_map(/* self:          */ &mman_kernel,
			                   /* hint:          */ MHINT_GETADDR(KERNEL_MHINT_TEMPORARY),
			                   /* num_bytes:     */ (size_t)tempmap_size,
			                   /* prot:          */ PROT_READ | PROT_WRITE,
			                   /* flags:         */ MHINT_GETMODE(KERNEL_MHINT_TEMPORARY),
			                   /* file:          */ driver_file,
			                   /* file_fspath:   */ driver_path,
			                   /* file_fsname:   */ driver_dentry,
			                   /* file_pos:      */ (pos_t)0);
		} EXCEPT {
			mman_unmap_kram_cookie_free(unmap_cookie);
			RETHROW();
		}
		RAII_FINALLY {
			/* Delete the temporary mapping created above. */
			mman_unmap_kram_and_kfree(tempmap, (size_t)tempmap_size,
			                          unmap_cookie);
		};

		/* Create a driver from the file mapping. */
		result = driver_create((byte_t const *)tempmap,
		                       (size_t)tempmap_size,
		                       driver_file, driver_path,
		                       driver_dentry, driver_cmdline,
		                       pnew_driver_loaded);
	}
	return result;
}

PUBLIC BLOCKING ATTR_RETNONNULL WUNUSED ATTR_INS(1, 2) REF struct driver *KCALL
driver_loadmod_blob(NCX void const *base, size_t num_bytes,
                    NCX char const *driver_cmdline,
                    bool *pnew_driver_loaded)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT, E_NOT_EXECUTABLE, E_IOERROR, ...) {
	REF struct driver *result;

	/* Try to create a driver from the given blob. */
	result = driver_create((NCX byte_t const *)base,
	                       num_bytes, NULL, NULL, NULL,
	                       driver_cmdline, pnew_driver_loaded);
	return result;
}

/* Load a driver, given its filename. */
PRIVATE BLOCKING ATTR_RETNONNULL WUNUSED REF struct driver *KCALL
driver_loadmod_filename(NCX char const *driver_filename,
                        NCX char const *driver_cmdline,
                        bool *pnew_driver_loaded)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT, E_NOT_EXECUTABLE, E_FSERROR, E_IOERROR, ...) {
	REF struct driver *result;
	REF struct mfile *driver_file;
	REF struct path *driver_path;
	REF struct fdirent *driver_dentry;

	/* Open the specified file. */
	driver_file = path_traversefull(AT_FDCWD, driver_filename, fs_atflags(0),
	                                &driver_path, &driver_dentry);
	FINALLY_DECREF_UNLIKELY(driver_path);
	FINALLY_DECREF_UNLIKELY(driver_dentry);
	FINALLY_DECREF_UNLIKELY(driver_file);

	/* Verify that we're dealing with a regular file. */
	if (!mfile_hasrawio(driver_file))
		THROW(E_NOT_EXECUTABLE_NOT_REGULAR);

	/* Try to create a driver from the given file. */
	result = driver_loadmod_file(driver_file, driver_path, driver_dentry,
	                             driver_cmdline, pnew_driver_loaded);
	return result;
}


struct path_segment {
	NCX char const *ps_base; /* Segment base */
	size_t                   ps_size; /* Segment length */
};

/* Extract the last segment from `path', and update
 * `*p_pathlen'  to point at the preceding segment. */
PRIVATE WUNUSED NONNULL((2, 3)) bool KCALL
path_get_last_segment_raw(NCX char const *path,
                          size_t *__restrict p_pathlen,
                          struct path_segment *__restrict result)
		THROWS(E_SEGFAULT) {
	char const *seg_start;
	size_t pathlen = *p_pathlen;

	/* Skip trailing slashes. */
	while (pathlen && path[pathlen - 1] == '/')
		--pathlen;
	if (!pathlen)
		return false;

	/* Find the start of the current segment. */
	seg_start = (char const *)memrend(path, '/', pathlen) + 1;

	/* Write back results. */
	result->ps_base = seg_start;
	result->ps_size = (size_t)((path + pathlen) - seg_start);
	*p_pathlen      = (size_t)(seg_start - path);
	return true;
}

PRIVATE WUNUSED NONNULL((2, 3)) bool KCALL
path_get_last_segment(NCX char const *path,
                      size_t *__restrict p_pathlen,
                      struct path_segment *__restrict result)
		THROWS(E_SEGFAULT) {
	size_t indirection;
	indirection = 0;
again:
	if (path_get_last_segment_raw(path, p_pathlen, result)) {
		/* Check for special directories '.' and '..' */
		if (result->ps_size == 1 && result->ps_base[0] == '.')
			goto again;
		if (result->ps_size == 2 && result->ps_base[0] == '.' && result->ps_base[1] == '.') {
			++indirection;
			goto again;
		}
		if (indirection) {
			--indirection;
			goto again;
		}
		return true;
	}
	return false;
}

/* Check if the given `pth' equals `pth_str...pth_len' */
PRIVATE WUNUSED NONNULL((1)) bool KCALL
path_equals_string(struct path *__restrict pth,
                   NCX char const *pth_str,
                   size_t pth_len)
		THROWS(E_SEGFAULT) {
	bool path_is_root = false;
	struct path_segment lastseg;
	while (pth_len && pth_str[0] == '/') {
		path_is_root = true;
		++pth_str;
		--pth_len;
	}
	while (path_get_last_segment(pth_str, &pth_len, &lastseg)) {
		if (lastseg.ps_size != pth->p_name->fd_namelen)
			goto nope;
		if (bcmp(pth->p_name->fd_name, lastseg.ps_base,
		         lastseg.ps_size, sizeof(char)) != 0)
			goto nope;
		if unlikely((pth = pth->p_parent) == NULL)
			goto nope;
	}
	if (path_is_root)
		return pth == atomic_read_relaxed(&vfs_kernel.vf_root);
	return pth == atomic_read_relaxed(&THIS_FS->fs_cwd);
nope:
	return false;
}


PUBLIC WUNUSED REF struct driver *FCALL
driver_fromfilename(NCX char const *driver_filename)
		THROWS(E_SEGFAULT) {
	REF struct driver *result;
	REF struct driver_loadlist *ll;
	char const *name;
	size_t pathlen, i;
	name = strrchr(driver_filename, '/');
	if (name) {
		pathlen = (size_t)(name - driver_filename);
		++name;
	} else {
		pathlen = 0;
		name    = driver_filename;
	}
	ll = get_driver_loadlist();
	FINALLY_DECREF_UNLIKELY(ll);
	for (i = 0; i < ll->dll_count; ++i) {
		result = ll->dll_drivers[i];
		if (!tryincref(result))
			continue;
		if (result->d_module.md_fspath && result->d_module.md_fsname) {
			TRY {
				if (strcmp(result->d_module.md_fsname->fd_name, name) == 0 &&
				    path_equals_string(result->d_module.md_fspath,
				                       driver_filename, pathlen))
					return result; /* This is the one! */
			} EXCEPT {
				decref_unlikely(result);
				RETHROW();
			}
		}
		decref_unlikely(result);
	}
	return NULL;
}

PUBLIC WUNUSED REF struct driver *FCALL
driver_fromfilename_with_len(NCX char const *driver_filename,
                             size_t driver_filename_len)
		THROWS(E_SEGFAULT) {
	REF struct driver *result;
	REF struct driver_loadlist *ll;
	char const *name;
	size_t namelen, pathlen, i;
	name = (char const *)memrchr(driver_filename, '/', driver_filename_len);
	if (name) {
		pathlen = (size_t)(name - driver_filename);
		++name;
		namelen = (size_t)((driver_filename + driver_filename_len) - name);
	} else {
		pathlen = 0;
		name    = driver_filename;
		namelen = driver_filename_len;
	}
	ll = get_driver_loadlist();
	FINALLY_DECREF_UNLIKELY(ll);
	for (i = 0; i < ll->dll_count; ++i) {
		result = ll->dll_drivers[i];
		if (!tryincref(result))
			continue;
		if (result->d_module.md_fspath && result->d_module.md_fsname) {
			TRY {
				if (result->d_module.md_fsname->fd_namelen == namelen &&
				    bcmp(result->d_module.md_fsname->fd_name,
				         name, namelen, sizeof(char)) == 0 &&
				    path_equals_string(result->d_module.md_fspath,
				                       driver_filename, pathlen))
					return result; /* This is the one! */
			} EXCEPT {
				decref_unlikely(result);
				RETHROW();
			}
		}
		decref_unlikely(result);
	}
	return NULL;
}


PRIVATE BLOCKING WUNUSED REF struct driver *KCALL
driver_loadmod_file_in_path(char const *__restrict path, size_t pathlen,
                            NCX char const *driver_name, size_t driver_namelen,
                            NCX char const *driver_cmdline,
                            bool *pnew_driver_loaded,
                            bool create_new_drivers)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT, E_NOT_EXECUTABLE, E_FSERROR, E_IOERROR, ...) {
	REF struct driver *result;
	char *buf, *p;

	/* Strip leading/trailing slashes from strings. */
	while (pathlen && path[pathlen - 1] == '/')
		--pathlen;
	while (driver_namelen && driver_name[0] == '/') {
		++driver_name;
		--driver_namelen;
	}
	buf = (char *)malloca((pathlen + driver_namelen + 2) * sizeof(char));
	RAII_FINALLY { freea(buf); };

	/* Construct the filename  */
	p = (char *)mempcpy(buf, path, pathlen, sizeof(char));
	*p++ = '/';
	p = (char *)mempcpy(p, driver_name, driver_namelen, sizeof(char));
	*p++ = '\0';
	if (create_new_drivers) {
		/* Second-phase (actually load new drivers) */
		result = driver_loadmod_filename(buf, driver_cmdline,
		                                 pnew_driver_loaded);
	} else {
		result = driver_fromfilename(buf);
	}
	return result;
}

PRIVATE BLOCKING WUNUSED REF struct driver *KCALL
driver_loadmod_file_with_path(struct driver_libpath_struct *__restrict lp,
                              NCX char const *driver_name,
                              NCX char const *driver_cmdline,
                              bool *pnew_driver_loaded,
                              bool create_new_drivers)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT, E_NOT_EXECUTABLE, E_FSERROR, E_IOERROR, ...) {
	REF struct driver *result;
	char const *sep;
	char const *path_start = lp->dlp_path;
	size_t driver_namelen  = strlen(driver_name);
	for (;;) {
		sep = strchrnul(path_start, ':');
		TRY {
			result = driver_loadmod_file_in_path(path_start, (size_t)(sep - path_start),
			                                     driver_name, driver_namelen,
			                                     driver_cmdline, pnew_driver_loaded,
			                                     create_new_drivers);
		} EXCEPT {
			except_code_t code = except_code();
			if (EXCEPT_CLASS(code) != E_FSERROR || !E_FSERROR_IS_FILE_NOT_FOUND(code))
				RETHROW(); /* Something other than file-not-found */
			if (create_new_drivers && !*sep)
				RETHROW(); /* This is the last possible path to search in the second phase. */
			result = NULL;
		}
		if (result)
			break;
		if (!*sep)
			break;
		path_start = sep + 1;
	}
	return result;
}

/* Load a driver, given its name. */
PUBLIC BLOCKING ATTR_RETNONNULL WUNUSED REF struct driver *KCALL
driver_loadmod(NCX char const *driver_name,
               NCX char const *driver_cmdline,
               bool *pnew_driver_loaded)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT, E_NOT_EXECUTABLE, E_FSERROR, E_IOERROR, ...) {
	REF struct driver *result;

	/* Check if the given `driver_name' is actually a file-path.
	 * We can identify paths  by them containing slashes  (`/'),
	 * and if  this is  the case,  rather than  searching for  a
	 * driver  with a specific name, we must search for one with
	 * a specific filename. */
	if (strchr(driver_name, '/')) {
		/* Check if we've already got a driver with this filename. */
		result = driver_fromfilename(driver_name);
		if (result) {
			if (pnew_driver_loaded)
				*pnew_driver_loaded = true;
		} else {
			result = driver_loadmod_filename(driver_name,
			                                 driver_cmdline,
			                                 pnew_driver_loaded);
		}
	} else if ((result = driver_fromname(driver_name)) != NULL) {
		if (pnew_driver_loaded)
			*pnew_driver_loaded = true;
	} else {
		REF struct driver_libpath_struct *lp;

		/* Search for a  file matching `driver_name'  in the  driver
		 * library path list (which usually contains `/os/drivers'). */
		lp = arref_get(&driver_libpath);
		FINALLY_DECREF_UNLIKELY(lp);

		/* Don't create new drivers during the first pass. */
		result = driver_loadmod_file_with_path(lp, driver_name,
		                                       driver_cmdline,
		                                       pnew_driver_loaded,
		                                       false);
		if (!result) {
			/* If no already-loaded driver matches the given name,
			 * then do a second pass where we actually open files,
			 * map them, and call `driver_create()' */
			result = driver_loadmod_file_with_path(lp, driver_name,
			                                       driver_cmdline,
			                                       pnew_driver_loaded,
			                                       true);
		}
	}
	return result;
}


/* Helper-wrappers for the functions above that will automatically
 * ensure that the driver is initialized successfully, and if said
 * initialization were to cause an exception, finalize the  driver
 * to have it be unloaded once again. */
PUBLIC BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct driver *KCALL
driver_insmod_file(struct mfile *__restrict driver_file,
                   struct path *driver_path,
                   struct fdirent *driver_dentry,
                   NCX char const *driver_cmdline,
                   bool *pnew_driver_loaded)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT, E_NOT_EXECUTABLE, E_IOERROR, ...) {
	REF struct driver *result;
	result = driver_loadmod_file(driver_file, driver_path, driver_dentry,
	                             driver_cmdline, pnew_driver_loaded);
	TRY {
		driver_initialize(result);
	} EXCEPT {
		decref(result);
		RETHROW();
	}
	return result;
}

PUBLIC BLOCKING ATTR_RETNONNULL WUNUSED ATTR_INS(1, 2) REF struct driver *KCALL
driver_insmod_blob(NCX void const *base, size_t num_bytes,
                   NCX char const *driver_cmdline,
                   bool *pnew_driver_loaded)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT, E_NOT_EXECUTABLE, E_IOERROR, ...) {
	REF struct driver *result;
	result = driver_loadmod_blob(base, num_bytes,
	                             driver_cmdline,
	                             pnew_driver_loaded);
	TRY {
		driver_initialize(result);
	} EXCEPT {
		decref(result);
		RETHROW();
	}
	return result;
}

PUBLIC BLOCKING ATTR_RETNONNULL WUNUSED REF struct driver *KCALL
driver_insmod(NCX char const *driver_name,
              NCX char const *driver_cmdline,
              bool *pnew_driver_loaded)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT, E_NOT_EXECUTABLE, E_FSERROR, E_IOERROR, ...) {
	REF struct driver *result;
	result = driver_loadmod(driver_name, driver_cmdline,
	                        pnew_driver_loaded);
	TRY {
		driver_initialize(result);
	} EXCEPT {
		decref(result);
		RETHROW();
	}
	return result;
}



/* Try to unload a driver module.
 * This function will:
 *   - Call `driver_finalize()'
 *   - if (!DRIVER_DELMOD_F_NODEPEND):
 *         Search for other modules  make use of `self'  through
 *         dependencies and finalize all of them such that their
 *         dependency vectors  can  be  cleared,  including  the
 *         contained references to `self'
 *   - weakincref(self);
 *   - if (DRIVER_DELMOD_F_FORCE):
 *         force the refcnt of `self' to 0
 *     else:
 *         Drop a reference from `self'
 *   - if (!DRIVER_DELMOD_F_NONBLOCK):
 *         Wait for `self' to reach its `DRIVER_STATE_DEAD'-state
 *   - weakdecref(self);
 * @param: self:                      The driver to try to unload.
 * @param: flags:                     Set of `DRIVER_DELMOD_F_*'
 * @return: DRIVER_DELMOD_ST_SUCCESS: Successfully unloaded the driver and inherited the reference to `self'
 * @return: DRIVER_DELMOD_ST_INUSE:   Only when  `DRIVER_DELMOD_F_NONBLOCK' is  given: There  are
 *                                    still other references to `self' that aren't accounted for.
 * @return: DRIVER_DELMOD_ST_INUSE:   The given driver `self' is `kernel_driver' */
PUBLIC BLOCKING NONNULL((1)) unsigned int FCALL
driver_try_decref_and_delmod(/*inherit(always)*/ REF struct driver *__restrict self,
                             unsigned int flags)
		THROWS(E_WOULDBLOCK) {
	TRY {
		if unlikely(self == &kernel_driver) {
			decref_nokill(self);
			return DRIVER_DELMOD_ST_INUSE; /* Not allowed! */
		}

		/* Always finalize the driver */
		driver_finalize(self);

		if (atomic_cmpxch(&self->d_module.md_refcnt, 1, 0))
			goto success;
		if (!(flags & DRIVER_DELMOD_F_NODEPEND)) {
			/* Search for, and delete modules that are using `self' */
			size_t j;
			REF struct driver_loadlist *dll;
			bool changed;
again_search_for_depending_drivers:
			dll = arref_get(&drivers);
			for (j = 0; j < dll->dll_count; ++j) {
				struct driver *d;
				size_t i;
				d = dll->dll_drivers[j];
				if (d == self)
					continue;
				if (!tryincref(d))
					continue;
				/* Check if this driver has a dependency on us. */
				for (i = 0; i < d->d_depcnt; ++i) {
					if (axref_ptr(&d->d_depvec[i]) != self)
						continue;
					TRY {
						/* Recursively delete this driver. */
						driver_try_decref_and_delmod(d, flags);
						/* Even if 1 depending driver could not be unloaded, keep on finalizing
						 * all other drivers to give the first  one more time to come to  terms
						 * with the fact that it is being unloaded.
						 * If everything works out, we'll still be able to destroy our driver
						 * in the final atomic_cmpxch() below. */
						goto find_next_dependent_driver;
					} EXCEPT {
						decref_unlikely(dll);
						RETHROW();
					}
				}
				decref_unlikely(d);
find_next_dependent_driver:
				;
			}
			/* If the set of loaded drivers has changed, then
			 * we  have to check  for more depending drivers. */
			changed = arref_ptr(&drivers) != dll;
			decref_unlikely(dll);
			if unlikely(changed)
				goto again_search_for_depending_drivers;
		}
	} EXCEPT {
		decref(self);
		RETHROW();
	}

	/* Check if we can get rid of the last reference */
	if (atomic_cmpxch(&self->d_module.md_refcnt, 1, 0))
		goto success;

	if (flags & DRIVER_DELMOD_F_FORCE) {
		refcnt_t remaining_references;
		remaining_references = atomic_cmpxch_val(&self->d_module.md_refcnt, 1, 0);
		if unlikely(remaining_references == 1)
			goto success;
		/* Forcing the kernel to do this is really bad, and the only situation
		 * where  us getting won't end up in  the kernel crashing, is when the
		 * driver really did leak one of its references.
		 * Now granted, the driver may have intentionally leaked one of its
		 * references, but even still: this is bad... */
		printk(KERN_CRIT "[mod][%s] Force unload driver with %" PRIuSIZ " unaccounted references\n",
		       self->d_name, remaining_references);
		{
			DATDEF u8 __kernel_poisoned ASMNAME("_kernel_poisoned");
			atomic_or(&__kernel_poisoned, _KERNEL_POISON_FORCEDELMOD);
		}
		atomic_write(&self->d_module.md_refcnt, 0);
		goto success;
	}
	if (!(flags & DRIVER_DELMOD_F_NONBLOCK)) {
		/* Wait for the driver to be destroyed. */
		task_connect(driver_changesignal(self)); /* This is broadcast when the driver gets destroyed. */
		weakincref(self);                        /* Keep the driver control structure alive */
again_decref_and_waitfor_destroy:
		decref(self); /* We'll re-acquire this reference of something goes wrong. */
		if unlikely(wasdestroyed(self)) {
			task_disconnectall();
			goto drop_weakref_after_destroyed;
		}
		TRY {
			task_waitfor();
		} EXCEPT {
			/* Drop the weak reference we took above. */
			weakdecref(self);
			RETHROW();
		}
		/* Check if we can still acquire references. */
		if unlikely(tryincref(self)) {
			TRY {
				task_connect(driver_changesignal(self));
			} EXCEPT {
				decref_unlikely(self);
				RETHROW();
			}
			goto again_decref_and_waitfor_destroy;
		}
drop_weakref_after_destroyed:
		/* Yes: the driver is dead!
		 * Now all that's left is the weak reference we still have from above. */
		weakdecref(self);
		return DRIVER_DELMOD_ST_SUCCESS;
	}
	return DRIVER_DELMOD_ST_INUSE;
success:
	/* Successfully caused the reference counter to drop to zero! */
	driver_destroy(self);
	return DRIVER_DELMOD_ST_SUCCESS;
}



/* Unload a driver from the kernel core.
 * @param: driver_name: The name of the driver, or its
 *                      filename (when the first character is `/')
 * @param: flags: Set of `DRIVER_DELMOD_F_*'
 * @return: * :   One of `DRIVER_DELMOD_ST_*' */
PUBLIC BLOCKING unsigned int FCALL
driver_delmod(NCX char const *driver_name,
              unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	unsigned int result;
	REF struct driver *drv;
	/* Lookup the requested driver. */
	drv = driver_name[0] == '/'
	      ? driver_fromfilename(driver_name)
	      : driver_fromname(driver_name);
	if (!drv)
		return DRIVER_DELMOD_ST_UNKNOWN;
	/* Try to unload the driver. */
	result = driver_try_decref_and_delmod(drv, flags);
	return result;
}

PUBLIC BLOCKING NONNULL((1)) unsigned int FCALL
driver_delmod_file(struct mfile *__restrict driver_file,
                   unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	unsigned int result;
	REF struct driver *drv;
	/* Lookup the requested driver. */
	drv = driver_fromfile(driver_file);
	if (!drv)
		return DRIVER_DELMOD_ST_UNKNOWN;
	/* Try to unload the driver. */
	result = driver_try_decref_and_delmod(drv, flags);
	return result;
}



#ifndef KERNEL_DRIVER_DEFAULT_LIBRARY_PATH
#define KERNEL_DRIVER_DEFAULT_LIBRARY_PATH "/os/drivers"
#endif /* !KERNEL_DRIVER_DEFAULT_LIBRARY_PATH */

/* The default library path.
 * By default, this string is simply set to "/os/drivers"
 * NOTE: This path can be restored with
 *      `ksysctl_set_driver_library_path(KSYSCTL_DRIVER_LIBRARY_PATH_DEFAULT)' */
INTERN struct driver_libpath_struct default_library_path = {
	.dlp_refcnt = 2, /* +1:default_library_path, +1:driver_libpath */
	KERNEL_DRIVER_DEFAULT_LIBRARY_PATH
};

/* [1..1] The current driver library path.
 * This path  is  a  ':'-separated list  of  UNIX-style  pathnames
 * that are used to resolve dependencies of kernel driver modules.
 * By default, this  string is  KERNEL_DRIVER_DEFAULT_LIBRARY_PATH */
PUBLIC struct driver_libpath_arref driver_libpath = ARREF_INIT(&default_library_path);


/************************************************************************/
/* Bootloader driver support                                            */
/************************************************************************/

#ifndef CONFIG_NO_BOOTLOADER_DRIVERS
/* Initialize  (link,  relocate &  initialize)  all drivers
 * loaded via the kernel commandline as bootloader modules.
 * This  is done as a separate step from the actual loading
 * of  drivers so-as to allow for inter-driver dependencies
 * to be resolved correctly. */
INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_loaded_drivers)(void) {
	bool found_some;
	REF struct driver_loadlist *dll;
	size_t i;
again:
	dll = arref_get(&drivers);
	found_some = false;
	for (i = 0; i < dll->dll_count; ++i) {
		uintptr_t old_state, new_state;
		REF struct driver *drv;
		drv = dll->dll_drivers[i];
		if unlikely(!tryincref(drv))
			continue;
		old_state = atomic_read(&drv->d_state);
		driver_initialize(drv);
		new_state = atomic_read(&drv->d_state);
		decref_unlikely(drv);
		/* Keep on restarting bootloader driver init
		 * for  as long as driver states change, and
		 * haven't yet transitioned to LOADED. */
		if (old_state != new_state && new_state != DRIVER_STATE_LOADED)
			found_some = true;
	}
	decref_unlikely(dll);
	if (found_some)
		goto again;
}
#endif /* !CONFIG_NO_BOOTLOADER_DRIVERS */


#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
DBG_COMMAND(lsmod,
            "lsmod\n"
            "\tList all currently loaded drivers\n") {
	size_t i, longest_name, longest_cmdl;
	REF struct driver_loadlist *ds;
	ds           = arref_get(&drivers);
	longest_name = 4;
	longest_cmdl = 7;
	for (i = 0; i < ds->dll_count; ++i) {
		struct driver *d;
		size_t temp;
		d = ds->dll_drivers[i];
		if (wasdestroyed(d) || d == &kernel_driver)
			continue; /* Dead driver... */
		temp = strlen(d->d_name);
		if (longest_name < temp)
			longest_name = temp;
		temp = (size_t)cmdline_encode(&format_length, NULL, d->d_argc, d->d_argv);
		if (longest_cmdl < temp)
			longest_cmdl = temp;
	}
	if (longest_name > 24)
		longest_name = 24;
	{
		unsigned int maxwidth;
		maxwidth = dbg_screen_width - (longest_name + 4 + (3 * sizeof(void *) * 2));
		if (longest_cmdl > maxwidth)
			longest_cmdl = maxwidth;
		if (longest_cmdl < 7)
			longest_cmdl = 7;
	}
#if __SIZEOF_POINTER__ == 8
	dbg_printf(DBGSTR("%-*s %-*s loadaddr         minaddr          maxaddr\n"),
	           longest_name, DBGSTR("name"),
	           longest_cmdl, DBGSTR("cmdline"));
#else /* __SIZEOF_POINTER__ == 8 */
	dbg_printf(DBGSTR("%-*s %-*s loadaddr minaddr  maxaddr\n"),
	           longest_name, DBGSTR("name"),
	           longest_cmdl, DBGSTR("cmdline"));
#endif /* __SIZEOF_POINTER__ == 8 */
	for (i = 0; i < ds->dll_count; ++i) {
		struct driver *d;
		size_t temp;
		d = ds->dll_drivers[i];
		if (wasdestroyed(d) || d == &kernel_driver)
			continue; /* Dead driver... */
		if (d->d_state >= DRIVER_STATE_KILL) {
			/* Already finalized */
			dbg_setfgcolor(ANSITTY_CL_MAROON);
		} else if (d->d_state > DRIVER_STATE_LOADED) {
			/* In the process of being finalized */
			dbg_setfgcolor(ANSITTY_CL_RED);
		} else if (d->d_state < DRIVER_STATE_LOADED) {
			/* In the process of being initialized */
			dbg_setfgcolor(ANSITTY_CL_YELLOW);
		}
		dbg_printf(DBGSTR("%-*s "), longest_name, d->d_name);
		temp = (size_t)cmdline_encode(&dbg_printer, NULL, d->d_argc, d->d_argv);
		if (longest_cmdl > temp)
			format_repeat(&dbg_printer, NULL, ' ', longest_cmdl - temp);
		dbg_printf(DBGSTR(" %p %p %p" AC_DEFATTR "\n"),
		           d->d_module.md_loadaddr,
		           d->d_module.md_loadmin,
		           d->d_module.md_loadmax);
	}
	decref_nokill(ds);
	return 0;
}

DBG_COMMAND(cmdline,
            "cmdline\n"
            "\tPrint the kernel commandline (ala " AC_WHITE("/proc/cmdline") ")\n") {
	cmdline_encode(&dbg_printer, NULL,
	               kernel_driver.d_argc,
	               kernel_driver.d_argv);
	dbg_putc('\n');
	return 0;
}
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_DRIVER_C */
