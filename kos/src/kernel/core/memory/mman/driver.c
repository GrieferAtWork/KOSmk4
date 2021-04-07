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
#ifndef GUARD_KERNEL_SRC_MEMORY_DRIVER_C
#define GUARD_KERNEL_SRC_MEMORY_DRIVER_C 1
#define __WANT_MODULE_SECTION__ms_dead
#define __WANT_MODULE__md_mmlop
#define __WANT_DRIVER_SECTION_ds_sect
#define __WANT_DRIVER_d_module
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#ifdef CONFIG_USE_NEW_DRIVER
#include <debugger/config.h>
#include <debugger/hook.h>
#include <debugger/io.h>
#include <debugger/rt.h>
#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/arch/driver.h>
#include <kernel/heap.h>
#include <kernel/mman.h>
#include <kernel/mman/driver.h>
#include <kernel/mman/kram.h>
#include <kernel/mman/map.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/module.h>
#include <kernel/mman/rw.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/syslog.h>
#include <sched/signal.h>

#include <hybrid/atomic.h>
#include <hybrid/overflow.h>
#include <hybrid/sequence/bsearch.h>
#include <hybrid/sequence/rbtree.h>
#include <hybrid/typecore.h>

#include <alloca.h>
#include <assert.h>
#include <elf.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <libunwind/eh_frame.h>
#include <libunwind/unwind.h>
#include <libzlib/inflate.h>


#if __SIZEOF_POINTER__ == 4
#define BADPOINTER UINT32_C(0xcccccccc)
#elif __SIZEOF_POINTER__ == 8
#define BADPOINTER UINT64_C(0xcccccccccccccccc)
#elif __SIZEOF_POINTER__ == 2
#define BADPOINTER UINT16_C(0xcccc)
#elif __SIZEOF_POINTER__ == 1
#define BADPOINTER UINT8_C(0xcc)
#else /* __SIZEOF_POINTER__ == ... */
#error "Unsupported sizeof(void *)"
#endif /* __SIZEOF_POINTER__ != ... */

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

#ifndef CONFIG_USE_NEW_FS
#define mfile_read(self, dst, num_bytes, pos)    inode_readk((struct inode *)(self), dst, num_bytes, pos)
#define mfile_readall(self, dst, num_bytes, pos) inode_readallk((struct inode *)(self), dst, num_bytes, pos)
#endif /* !CONFIG_USE_NEW_FS */


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

PRIVATE /*ATTR_PURE*/ WUNUSED NONNULL((1)) char const *FCALL
driver_section_getname(struct driver_section *__restrict self) {
	struct driver *drv;
	char const *result;
	drv = (struct driver *)self->ds_sect.ms_module;
	assert(!wasdestroyed(drv));
	result = driver_getshstrtab(drv);
	if (result)
		result += self->ds_shdr->sh_name;
	return result;
}

PRIVATE WUNUSED NONNULL((1)) KERNEL byte_t *FCALL
driver_section_create_kernaddr_ex(struct driver_section *__restrict self,
                                  struct driver *__restrict drv) {
	struct mfile *file = driver_getfile(drv);
	if (!file)
		THROW(E_NO_SUCH_OBJECT);
	return (byte_t *)mman_map(/* self:        */ &mman_kernel,
	                          /* hint:        */ HINT_GETADDR(KERNEL_VMHINT_TEMPORARY),
	                          /* num_bytes:   */ self->ds_sect.ms_size,
	                          /* prot:        */ (PROT_READ | PROT_WRITE) & ~PROT_SHARED,
	                          /* flags:       */ HINT_GETMODE(KERNEL_VMHINT_TEMPORARY),
	                          /* file:        */ file,
	                          /* file_fspath: */ drv->d_module.md_fspath,
	                          /* file_fsname: */ drv->d_module.md_fsname,
	                          /* file_pos:    */ (pos_t)self->ds_shdr->sh_offset);
}

PRIVATE WUNUSED NONNULL((1)) KERNEL byte_t *FCALL
driver_section_create_kernaddr(struct driver_section *__restrict self) {
	REF struct driver *drv;
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
	if unlikely(!ATOMIC_CMPXCH(self->ds_addr, (KERNEL byte_t *)-1, result)) {
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
		ATOMIC_WRITE(self->ds_inflsize, self->ds_sect.ms_size);
		ATOMIC_CMPXCH(self->ds_infladdr, (KERNEL byte_t *)-1, dst_data);
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
		src_data_freeme_cookie = kmalloc(sizeof(struct mman_unmap_kram_job),
		                                 GFP_LOCKED | GFP_PREFLT);
		TRY {
			src_data = driver_section_create_kernaddr_ex(self, drv);
		} EXCEPT {
			kfree(src_data_freeme_cookie);
			RETHROW();
		}
	}
	TRY {
		ElfW(Chdr) *chdr;
		chdr = (ElfW(Chdr) *)src_data;
		if unlikely(chdr->ch_type != ELFCOMPRESS_ZLIB)
			THROW(E_INVALID_ARGUMENT);
		dst_size = chdr->ch_size;
		dst_data = (byte_t *)mman_map_kram(NULL, dst_size, GFP_PREFLT);
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
			mman_unmap_kram_and_kfree(src_data, self->ds_sect.ms_size, src_data_freeme_cookie);
		RETHROW();
	}
	if (src_data_freeme_cookie)
		mman_unmap_kram_and_kfree(src_data, self->ds_sect.ms_size, src_data_freeme_cookie);
	ATOMIC_WRITE(self->ds_inflsize, dst_size);
	ATOMIC_CMPXCH(self->ds_infladdr, (KERNEL byte_t *)-1, dst_data);
	*psize = dst_size;
	return dst_data;
}


PRIVATE struct module_section_ops const driver_section_ops = {
	.ms_destroy         = (void (FCALL *)(struct module_section *__restrict))&driver_section_destroy,
	.ms_getname         = (char const *(FCALL *)(struct module_section *__restrict))&driver_section_getname,
	.ms_getaddr         = (byte_t *(FCALL *)(struct module_section *__restrict))&driver_section_getaddr,
	.ms_getaddr_alias   = (byte_t *(FCALL *)(struct module_section *__restrict))&driver_section_getaddr,
	.ms_getaddr_inflate = (byte_t *(FCALL *)(struct module_section *__restrict, size_t *__restrict))&driver_section_getaddr_inflate,
};





/************************************************************************/
/* Custom kernel driver data structures                                 */
/************************************************************************/
#ifdef __INTELLISENSE__
struct kernel_shstrtab { char zero; };
INTERN_CONST ATTR_COLDRODATA struct kernel_shstrtab const kernel_shstrtab_data = { 0 };
enum { KERNEL_SECTIONS_COUNT };
INTERN_CONST ATTR_COLDRODATA ElfW(Shdr) const kernel_shdr[KERNEL_SECTIONS_COUNT] = {};
INTERN_CONST struct driver_section_awref kernel_sections[KERNEL_SECTIONS_COUNT] = {};
#else /* __INTELLISENSE__ */
#define SECTION_DESCRIPTOR_INDEX     PP_CAT2(KERNEL_SECTION_INDEX_, __LINE__)
#define SECTION_DESCRIPTOR_SHSTRNAME PP_CAT2(ks_name_, __LINE__)

/* Define globals. */
#define INTERN_SECTION(symbol_name, name, type, flags, start, size, entsize, link, info) /* nothing */
#include "../../fs/kernel_sections.def"

/* Define the kernel's .shstrtab section */
struct kernel_shstrtab {
#define INTERN_SECTION(symbol_name, name, type, flags, start, size, entsize, link, info) \
	char SECTION_DESCRIPTOR_SHSTRNAME[sizeof(name)];
#include "../../fs/kernel_sections.def"
	char zero;
};

INTERN_CONST ATTR_COLDRODATA struct kernel_shstrtab const kernel_shstrtab_data = {
#define INTERN_SECTION(symbol_name, name, type, flags, start, size, entsize, link, info) \
	/* .SECTION_DESCRIPTOR_SHSTRNAME = */ name,
#include "../../fs/kernel_sections.def"
	/* .zero = */ 0
};



/* Define section indices */
enum {
#define INTERN_SECTION(symbol_name, name, type, flags, start, size, entsize, link, info) \
	SECTION_DESCRIPTOR_INDEX,
#include "../../fs/kernel_sections.def"
	KERNEL_SECTIONS_COUNT
};


/* Define the ELF section header vector. */
INTERN_CONST ATTR_COLDRODATA ElfW(Shdr) const kernel_shdr[KERNEL_SECTIONS_COUNT] = {
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
#include "../../fs/kernel_sections.def"
};



/* Define the driver section descriptors. */
#define _SECTION(decl_name, name, type, flags, start, size, entsize, link, info) \
	struct driver_section decl_name = {                                          \
		.ds_sect = {                                                             \
			.ms_refcnt  = 1,                                                     \
			.ms_ops     = &driver_section_ops,                                   \
			.ms_module  = &kernel_driver,                                        \
			.ms_size    = (size_t)(size),                                        \
			.ms_entsize = (size_t)(entsize),                                     \
			.ms_type    = (type),                                                \
			.ms_flags   = (flags),                                               \
			.ms_link    = (link),                                                \
			.ms_info    = (info),                                                \
			.ms_cache   = LIST_ENTRY_UNBOUND_INITIALIZER,                        \
		},                                                                       \
		.ds_shdr     = &kernel_shdr[SECTION_DESCRIPTOR_INDEX],                   \
		.ds_addr     = (void *)(start),                                          \
		.ds_infladdr = (flags) & SHF_COMPRESSED ? (void *)-1 : (void *)(start),  \
		.ds_inflsize = (flags) & SHF_COMPRESSED ? 0 : (size_t)(size),            \
	};
#define INTERN_SECTION(intern_name, name, type, flags, start, size, entsize, link, info) \
	INTERN _SECTION(intern_name, name, type, flags, start, size, entsize, link, info)
#define EXPORT_SECTION(export_name, name, type, flags, start, size, entsize, link, info) \
	PUBLIC _SECTION(export_name, name, type, flags, start, size, entsize, link, info)
#include "../../fs/kernel_sections.def"


/* Define the driver sections vector. */
INTERN_CONST struct driver_section_awref kernel_sections[KERNEL_SECTIONS_COUNT] = {
#define INTERN_SECTION(symbol_name, ...) /* [SECTION_DESCRIPTOR_INDEX] = */ AWREF_INIT(&symbol_name),
#include "../../fs/kernel_sections.def"
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


PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL driver_free)(struct module *__restrict self) {
	kfree(self);
}

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
                   USER CHECKED char const *section_name) {
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
kernel_sectinfo(struct driver *__restrict UNUSED(self),
                uintptr_t module_relative_addr,
                struct module_sectinfo *__restrict info) {
	unsigned int i;
	bool allow_section_end_pointers;
	allow_section_end_pointers = false;
again:
	for (i = 0; i < KERNEL_SECTIONS_COUNT; ++i) {
		if (module_relative_addr < kernel_shdr[i].sh_addr)
			continue;
		if (module_relative_addr >= kernel_shdr[i].sh_addr + kernel_shdr[i].sh_size) {
			if (!allow_section_end_pointers)
				continue;
			if (module_relative_addr > kernel_shdr[i].sh_addr + kernel_shdr[i].sh_size)
				continue;
		}
		/* Found it! (fill in section information for our caller) */
		info->msi_name    = (char *)&kernel_shstrtab_data + kernel_shdr[i].sh_name;
		info->msi_addr    = kernel_shdr[i].sh_addr;
		info->msi_size    = kernel_shdr[i].sh_size;
		info->msi_entsize = kernel_shdr[i].sh_entsize;
		info->msi_type    = kernel_shdr[i].sh_type;
		info->msi_flags   = kernel_shdr[i].sh_flags;
		info->msi_link    = kernel_shdr[i].sh_link;
		info->msi_info    = kernel_shdr[i].sh_info;
		info->msi_index   = i;
		return true;
	}
	if (!allow_section_end_pointers) {
		allow_section_end_pointers = true;
		goto again;
	}
	return false;
}



#ifndef KERNEL_DRIVER_NAME
#define KERNEL_DRIVER_NAME "kernel"
#endif /* !KERNEL_DRIVER_NAME */

#ifndef KERNEL_DRIVER_FILENAME
#define KERNEL_DRIVER_FILENAME "/os/kernel.bin"
#endif /* !KERNEL_DRIVER_FILENAME */

PRIVATE struct module_ops const kernel_module_ops = {
	.mo_free              = &driver_free,
	.mo_destroy           = (typeof(((struct module_ops *)0)->mo_destroy))BADPOINTER, /* Must never be called! */
	.mo_nonodes           = (typeof(((struct module_ops *)0)->mo_nonodes))BADPOINTER, /* Must never be called! */
	.mo_locksection       = (REF struct module_section *(FCALL *)(struct module *__restrict, USER CHECKED char const *))&kernel_locksection,
	.mo_locksection_index = (REF struct module_section *(FCALL *)(struct module *__restrict, unsigned int))&kernel_locksection_index,
	.mo_sectinfo          = (bool (FCALL *)(struct module *__restrict, uintptr_t, struct module_sectinfo *__restrict))&kernel_sectinfo,
};

PRIVATE ATTR_COLDRODATA char const kernel_driver_name[] = KERNEL_DRIVER_NAME;
PRIVATE ATTR_COLDDATA struct directory_entry kernel_driver_fsname = {
	.de_refcnt   = 1, /* +1: kernel_driver.d_module.md_fsname */
	.de_heapsize = offsetof(struct directory_entry, de_name) + sizeof(KERNEL_DRIVER_FILENAME),
	.de_next     = NULL,
	.de_bypos    = LIST_ENTRY_UNBOUND_INITIALIZER,
	.de_fsdata   = {},
	.de_pos      = 0,
	.de_ino      = 0,
	.de_hash     = 0,
	.de_namelen  = COMPILER_STRLEN(KERNEL_DRIVER_FILENAME),
	.de_type     = DT_REG,
	.de_name     = KERNEL_DRIVER_FILENAME
};

PUBLIC struct driver kernel_driver = {
	.d_module = {
		.md_refcnt     = 2, /* +1: kernel_driver, +1: d_state == DRIVER_STATE_LOADED */
		.md_weakrefcnt = 1 + KERNEL_SECTIONS_COUNT,
		.md_nodecount  = 1, /* TODO */
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
	.d_eh_frame_start      = __kernel_eh_frame_start,
	.d_eh_frame_end        = __kernel_eh_frame_end,
	.d_eh_frame_cache      = NULL,
	.d_eh_frame_cache_lock = ATOMIC_RWLOCK_INIT,
	.d_dyncnt              = 0,
	.d_dynhdr              = NULL,
	.d_dynsym_tab          = NULL,
	.d_dynsym_cnt          = 0,
	.d_gnuhashtab          = NULL,
	.d_hashtab             = NULL,
	.d_dynstr              = NULL,
	.d_dynstr_end          = NULL,
	.d_shoff               = 0,
	.d_shstrndx            = KERNEL_SECTIONS_COUNT - 1,
	.d_shnum               = KERNEL_SECTIONS_COUNT,
	.d_shdr                = kernel_shdr,
	.d_sections            = kernel_sections,
	.d_shstrtab            = (char *)&kernel_shstrtab_data,
	.d_shstrsiz            = sizeof(kernel_shstrtab_data),
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


/* Signal broadcast whenever the `d_state' of any loaded driver changes. */
PUBLIC struct sig driver_state_changed = SIG_INIT;


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
			 *       reference if that is truly the case. */
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
	BSEARCHR (i, ll->dll_drivers, ll->dll_count,
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

/* Lookup an already-loaded driver, given its name or file. */
PUBLIC WUNUSED REF struct driver *FCALL
driver_fromname(USER CHECKED char const *driver_name)
		THROWS(E_SEGFAULT) {
	size_t i;
	REF struct driver *result;
	REF struct driver_loadlist *ll;
	ll = get_driver_loadlist();
	FINALLY_DECREF_UNLIKELY(ll);
	assert_assume(ll->dll_count >= 1);
	for (i = 0; i < ll->dll_count; ++i) {
		result = ll->dll_drivers[i];
		if (strcmp(result->d_name, driver_name) == 0) {
			if (tryincref(result))
				return result;
			break;
		}
	}
	return NULL;
}

PUBLIC WUNUSED REF struct driver *FCALL
driver_fromname_with_len(USER CHECKED char const *driver_name,
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
		if (strcmpz(result->d_name, driver_name, driver_name_len) == 0) {
			if (tryincref(result))
				return result;
			break;
		}
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
PUBLIC WUNUSED NONNULL((1)) struct mfile *FCALL
driver_getfile(struct driver *__restrict self)
		THROWS(E_IOERROR, E_WOULDBLOCK, E_BADALLOC) {
	if (!self->d_module.md_file) {
		/* TODO */
		COMPILER_IMPURE();
	}
	return self->d_module.md_file;
}

/* Try to return a mapping for the given driver's section headers.
 * If this fails, return `NULL' instead. */
PUBLIC WUNUSED NONNULL((1)) ElfW(Shdr) const *FCALL
driver_getshdrs(struct driver *__restrict self)
		THROWS(E_IOERROR, E_WOULDBLOCK, E_BADALLOC) {
	if (!self->d_shdr) {
		struct mfile *file;
		file = driver_getfile(self);
		if likely(file) {
			ElfW(Shdr) *result;
			size_t shsize;
			shsize = self->d_shnum * sizeof(ElfW(Shdr));
			result = (ElfW(Shdr) *)kmalloc(shsize, GFP_NORMAL);
			TRY {
				mfile_readall(file, result, shsize, (pos_t)self->d_shoff);
			} EXCEPT {
				kfree(result);
				RETHROW();
			}
			if unlikely(!ATOMIC_CMPXCH(self->d_shdr, NULL, result))
				kfree(result);
		}
	}
	return self->d_shdr;
}

/* Try to return a mapping for the given driver's .shstrtab section.
 * If this fails, return `NULL' instead. */
PUBLIC WUNUSED NONNULL((1)) char const *FCALL
driver_getshstrtab(struct driver *__restrict self)
		THROWS(E_IOERROR, E_WOULDBLOCK, E_BADALLOC) {
	if (!self->d_shstrtab) {
		ElfW(Shdr) const *shdr;
		struct mfile *file;
		if ((file = driver_getfile(self)) != NULL &&
			(shdr = driver_getshdrs(self)) != NULL) {
			char *result;
			size_t siz;
			siz    = shdr[self->d_shstrndx].sh_size;
			result = (char *)kmalloc((siz + 1) * sizeof(char), GFP_NORMAL);
			TRY {
				mfile_readall(file, result, siz * sizeof(char),
				              (pos_t)shdr[self->d_shstrndx].sh_offset);
			} EXCEPT {
				kfree(result);
				RETHROW();
			}
			result[siz] = '\0';
			COMPILER_WRITE_BARRIER();
			ATOMIC_WRITE(self->d_shstrsiz, siz);
			if unlikely(!ATOMIC_CMPXCH(self->d_shstrtab, NULL, result))
				kfree(result);
		}
	}
	return self->d_shstrtab;
}




/************************************************************************/
/* Driver symbol lookup functions                                       */
/************************************************************************/
PRIVATE WUNUSED NONNULL((1, 2)) bool FCALL
driver_dlsym_drv(struct driver *__restrict self,
                 struct driver_syminfo *__restrict info)
		THROWS(E_SEGFAULT, ...) {
	USER CHECKED char const *name = info->dsi_name + 4;
	if (strcmp(name, "self") == 0) {
		info->dsi_addr = self;
		info->dsi_size = sizeof(*self);
		goto ok;
	}
	if (name[0] == 'l' && name[1] == 'o' &&
	    name[2] == 'a' && name[3] == 'd') {
		USER CHECKED char const *load_name = name + 4;
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
		info->dsi_size = (strlen(self->d_cmdline) + 1) * sizeof(char);sizeof(void *);
		goto ok;
	}
	if (name[0] == 'a' && name[1] == 'r' && name[2] == 'g') {
		USER CHECKED char const *arg_name = name + 3;
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
		if (arg_name[0] == '$') {
			/* TODO */
		}
	}
	return false;
ok_size0:
	info->dsi_size = 0;
ok:
	info->dsi_bind = STB_GLOBAL;
	return true;
}

LOCAL ATTR_PURE WUNUSED NONNULL((1)) u32 FCALL
gnu_symhash(USER CHECKED char const *name) {
	u32 h = 5381;
	for (; *name; ++name) {
		h = h * 33 + (u8)*name;
	}
	return h;
}

LOCAL ATTR_PURE WUNUSED NONNULL((1)) u32 FCALL
elf_symhash(USER CHECKED char const *name) {
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
                                           char const *kind) {
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
	{
		ElfW(GnuHashTable) const *gnu_ht;
		if ((gnu_ht = self->d_gnuhashtab) != NULL) {
			/* This implementation is derived from:
			 * https://flapenguin.me/2017/05/10/elf-lookup-dt-gnu-hash/
			 * https://sourceware.org/ml/binutils/2006-10/msg00377.html
			 */
			ElfW(Word) symid, gh_symoffset;
			ElfW(Word) const *gh_buckets;
			ElfW(Word) const *gh_chains;
			ElfW(Addr) bloom_word, bloom_mask;
			uint32_t hash = info->dsi_gnuhash;
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
					if likely(strcmp(info->dsi_name, self->d_dynstr + result->st_name) == 0)
						return result; /* Found it! */
				}
				if unlikely(enthash & 1)
					break; /* End of chain */
			}
			goto nosym;
		}
	}

search_elf_table:
	/************************************************************************/
	/* ELF hash table support                                               */
	/************************************************************************/
	{
		ElfW(HashTable) const *elf_ht;
		if ((elf_ht = self->d_hashtab) != NULL) {
			ElfW(Word) const *ht_chains;
			ElfW(Word) max_attempts, chain;
			uint32_t hash = info->dsi_elfhash;
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
	}

search_dynsym:
	/************************************************************************/
	/* Do a linear search over the symbol table.                            */
	/************************************************************************/
	{
		ElfW(Sym) const *dynsym;
		if ((dynsym = self->d_dynsym_tab) != NULL) {
			size_t i, dyncnt;
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



/* Lookup a symbol  within a driver,  given its  name.
 * Note that this function will _not_ look into driver
 * dependencies in order to resolve that symbol.
 * NOTE: This function also takes care of the special
 *       set of `drv_*' symbols!
 * @return: true:  Found a symbol matching the given name.
 * @return: false: No symbol matching the given name found. */
PUBLIC WUNUSED NONNULL((1, 2)) bool FCALL
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
		uintptr_t st_addr;
		unsigned char st_info;
		st_info = ATOMIC_READ(symbol->st_info);
		st_addr = symbol->st_value;
		if (symbol->st_shndx != SHN_ABS)
			st_addr += self->d_module.md_loadaddr;
		if (ELFW(ST_TYPE)(st_info) == STT_GNU_IFUNC ||
		    ELFW(ST_TYPE)(st_info) == STT_KOS_IDATA) {
			/* Resolve dynamic address. */
			st_addr = (*(uintptr_t(*)(void))st_addr)();
			/* TODO: Write-back the resolved address, and change
			 *       the typing of  the symbol to  no longer  be
			 *       indirect! */
		}
		info->dsi_addr = (void *)st_addr;
		info->dsi_size = symbol->st_size;
		info->dsi_bind = ELFW(ST_BIND)(st_info);
		return true;
	}
	return false;
}



#define DRIVER_DLSYM_EX_NOENT 0 /* Symbol not found */
#define DRIVER_DLSYM_EX_OK    1 /* Success */
#define DRIVER_DLSYM_EX_EOF   2 /* No drivers found at `depth' */

PRIVATE WUNUSED NONNULL((1, 2)) unsigned int FCALL
driver_dlsym_ex(struct driver *__restrict self,
                struct driver_syminfo *__restrict info,
                unsigned int depth)
		THROWS(E_SEGFAULT, ...) {
	unsigned int result, status;
	size_t i;
	if (depth == 0) {
		if (driver_dlsym_local(self, info))
			return DRIVER_DLSYM_EX_OK;
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
			status = driver_dlsym_ex(dep, info, depth);
		}
		if (status != DRIVER_DLSYM_EX_EOF) {
			result = status;
			if (result == DRIVER_DLSYM_EX_OK)
				break;
		}
	}
	return result;
}

/* Same  as `driver_dlsym_local()', but if that function fails,
 * or  returns a weak  symbol, scan all  of the dependencies of
 * `self'  for another symbol with the same name. If a non-weak
 * symbol is found return it. Otherwise, return the first  weak
 * symbol encountered during the search, and if all that fails,
 * return `false' to indicate failure.
 * @return: true:  Found a symbol matching the given name.
 * @return: false: No symbol matching the given name found. */
PUBLIC WUNUSED NONNULL((1, 2)) bool FCALL
driver_dlsym(struct driver *__restrict self,
             struct driver_syminfo *__restrict info)
		THROWS(E_SEGFAULT, ...) {
	unsigned int status, depth, max_depth;
	bool result = driver_dlsym_local(self, info);
	/* All drivers have an implicit dependency on the kernel core! */
	if (!result)
		result = kernel_dlsym(info);
	if (!result) {
		REF struct driver_loadlist *ll;
		ll        = get_driver_loadlist();
		max_depth = (unsigned int)ll->dll_count;
		decref_unlikely(ll);
		for (depth = 0; depth < max_depth; ++depth) {
			status = driver_dlsym_ex(self, info, depth);
			if (status != DRIVER_DLSYM_EX_NOENT) {
				if (status == DRIVER_DLSYM_EX_OK) {
					result = true;
					if (info->dsi_bind == STB_WEAK) {
						++depth;
						goto find_nonweak_after;
					}
				}
				break;
			}
		}
	} else if (info->dsi_bind == STB_WEAK) {
		REF struct driver_loadlist *ll;
		struct driver_syminfo info2;
		ll        = get_driver_loadlist();
		max_depth = (unsigned int)ll->dll_count;
		decref_unlikely(ll);
		depth = 0;
find_nonweak_after:
		info2.dsi_name    = info->dsi_name;
		info2.dsi_elfhash = info->dsi_elfhash;
		info2.dsi_gnuhash = info->dsi_gnuhash;
		for (; depth < max_depth; ++depth) {
			status = driver_dlsym_ex(self, &info2, depth);
			if (status != DRIVER_DLSYM_EX_NOENT) {
				if (status == DRIVER_DLSYM_EX_OK && info2.dsi_bind == STB_WEAK)
					continue; /* Another weak symbol (skip; we only ever use the first one found!) */
				info->dsi_addr = info2.dsi_addr;
				info->dsi_size = info2.dsi_size;
				info->dsi_bind = info2.dsi_bind;
				break;
			}
		}
	}
	return result;
}

/* Search for a symbol in all loaded drivers, following the order
 * of drivers, as they appear returned by `get_driver_loadlist()' */
PUBLIC WUNUSED NONNULL((1)) bool FCALL
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
		{
			FINALLY_DECREF_UNLIKELY(d);
			ok = driver_dlsym_local(d, info);
		}
		if (!ok)
			continue;
		if (info->dsi_bind == STB_WEAK) {
			/* Try to find another driver that may define this symbol as non-weak! */
			struct driver_syminfo info2;
			info2.dsi_name    = info->dsi_name;
			info2.dsi_elfhash = info->dsi_elfhash;
			info2.dsi_gnuhash = info->dsi_gnuhash;
			for (++i; i < ll->dll_count; ++i) {
				d = ll->dll_drivers[i];
				if (!tryincref(d))
					continue;
				{
					FINALLY_DECREF_UNLIKELY(d);
					ok = driver_dlsym_local(d, info);
				}
				/* Only accept non-weak symbols at this point! */
				if (!ok || info2.dsi_bind == STB_WEAK)
					continue;
				/* Found a non-weak symbol! */
				info->dsi_addr = info2.dsi_addr;
				info->dsi_size = info2.dsi_size;
				info->dsi_bind = info2.dsi_bind;
				break;
			}
		}
		return true;
	}
	return false;
}

/* Helper wrappers for the above functions that simply take the
 * name of the symbol and will return its address, or `NULL' if
 * no such symbol could be found. */
PUBLIC WUNUSED NONNULL((1)) void *FCALL
driver_dlsym_local_f(struct driver *__restrict self,
                     USER CHECKED char const *name)
		THROWS(E_SEGFAULT, ...) {
	struct driver_syminfo info;
	driver_syminfo_init(&info, name);
	if (!driver_dlsym_local(self, &info))
		info.dsi_addr = NULL;
	return info.dsi_addr;
}

PUBLIC WUNUSED NONNULL((1)) void *FCALL
driver_dlsym_f(struct driver *__restrict self,
               USER CHECKED char const *name)
		THROWS(E_SEGFAULT, ...) {
	struct driver_syminfo info;
	driver_syminfo_init(&info, name);
	if (!driver_dlsym(self, &info))
		info.dsi_addr = NULL;
	return info.dsi_addr;
}

PUBLIC WUNUSED NONNULL((1)) void *FCALL
driver_dlsym_global_f(USER CHECKED char const *name)
		THROWS(E_SEGFAULT, ...) {
	struct driver_syminfo info;
	driver_syminfo_init(&info, name);
	if (!driver_dlsym_global(&info))
		info.dsi_addr = NULL;
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

/* Do the reverse of the `dlsym()' functions above, and resolve
 * a  driver-relative `driver_reladdr' to try to determine info
 * about the symbol that contains that address.
 * @return: true:  Success.
 * @return: false: Failure. */
PUBLIC NOBLOCK WUNUSED NONNULL((1, 2)) bool
NOTHROW(FCALL driver_dladdr_local)(struct driver *__restrict self,
                                   struct driver_symaddr *__restrict info,
                                   uintptr_t driver_reladdr) {
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
PUBLIC NOBLOCK WUNUSED NONNULL((1)) REF struct driver *
NOTHROW(FCALL driver_dladdr)(struct driver_symaddr *__restrict info,
                             void const *addr) {
	REF struct driver *drv;
	drv = driver_fromaddr(addr);
	if (!drv)
		return NULL;
	if (!driver_dladdr_local(drv, info,
	                         (uintptr_t)addr -
	                         drv->d_module.md_loadaddr)) {
		decref_unlikely(drv);
		drv = NULL;
	}
	return drv;
}


/* FDE Cache API */
struct driver_fde_cache {
	unwind_fde_t                           dfc_fde;    /* Cached FDE */
	size_t                                 dfc_heapsz; /* Allocated heap size (least significant bit is R/B-bit; 0:black; 1:red) */
	LLRBTREE_NODE(struct driver_fde_cache) dfc_node;   /* R/B-node */
};
#define driver_fde_cache_heapsz(self) ((self)->dfc_heapsz & ~1)

DECL_END

#define RBTREE_LEFT_LEANING
#define RBTREE_OMIT_REMOVE
#define RBTREE_OMIT_REMOVENODE
#define RBTREE_OMIT_INSERT
#define RBTREE_WANT_TRYINSERT
#define RBTREE_DECL                PRIVATE
#define RBTREE_IMPL                PRIVATE
#define RBTREE(name)               dfc_##name
#define RBTREE_T                   struct driver_fde_cache
#define RBTREE_Tkey                void const *
#define RBTREE_CC                  FCALL
#define RBTREE_NOTHROW             NOTHROW
#define RBTREE_NODEPATH            dfc_node
#define RBTREE_ISRED(self)         ((self)->dfc_heapsz & 1)
#define RBTREE_SETRED(self)        (void)((self)->dfc_heapsz |= 1)
#define RBTREE_SETBLACK(self)      (void)((self)->dfc_heapsz &= ~1)
#define RBTREE_FLIPCOLOR(self)     (void)((self)->dfc_heapsz ^= 1)
#define RBTREE_COPYCOLOR(dst, src) (void)((dst)->dfc_heapsz &= ~1, (dst)->dfc_heapsz |= ((src)->dfc_heapsz & 1))
#define RBTREE_GETNODE(self)       (self)->dfc_node
#define RBTREE_GETMINKEY(node)     (node)->dfc_fde.f_pcstart
#define RBTREE_GETMAXKEY(node)     ((byte_t *)(node)->dfc_fde.f_pcend - 1)
#include <hybrid/sequence/rbtree-abi.h>

DECL_BEGIN

PRIVATE ATTR_USED NOBLOCK NONNULL((1)) size_t
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

/* Try to clear the FDE cache of the given, or of all loaded drivers. */
PRIVATE ATTR_USED NOBLOCK NONNULL((1)) size_t
NOTHROW(FCALL clear_fde_cache)(struct driver *__restrict self) {
	size_t result = 0;
	if (atomic_rwlock_trywrite(&self->d_eh_frame_cache_lock)) {
		struct driver_fde_cache *tree;
		tree = self->d_eh_frame_cache;
		self->d_eh_frame_cache = NULL;
		atomic_rwlock_endwrite(&self->d_eh_frame_cache_lock);
		if (tree)
			result = dfc_freetree(tree);
	}
	return result;
}

DEFINE_SYSTEM_CACHE_CLEAR(clear_fde_caches);
PRIVATE ATTR_USED NOBLOCK size_t
NOTHROW(KCALL clear_fde_caches)(void) {
	size_t i, result = 0;
	REF struct driver_loadlist *ll;
	ll = get_driver_loadlist();
	for (i = 0; i < ll->dll_count; ++i) {
		REF struct driver *drv;
		drv = ll->dll_drivers[i];
		if (!tryincref(drv))
			continue;
		result += clear_fde_cache(drv);
		decref_unlikely(drv);
	}
	decref_unlikely(ll);
	return result;
}


/* Lookup the FDE descriptor for a given `absolute_pc', whilst trying to
 * make use of the FDE cache of `self'.
 * @return: * : One of `UNWIND_*' from <libunwind/api.h> */
PUBLIC NOBLOCK NONNULL((1)) unsigned int
NOTHROW(FCALL driver_findfde)(struct driver *__restrict self, void const *absolute_pc,
                              unwind_fde_t *__restrict result) {
	unsigned int status;

	/* Try to look through the driver's FDE cache for a descriptor. */
	if (atomic_rwlock_tryread(&self->d_eh_frame_cache_lock)) {
		struct driver_fde_cache *cache;
		cache = dfc_locate(self->d_eh_frame_cache, absolute_pc);
		if (cache) {
			memcpy(result, &cache->dfc_fde, sizeof(unwind_fde_t));
			atomic_rwlock_endread(&self->d_eh_frame_cache_lock);
			return UNWIND_SUCCESS;
		}
		atomic_rwlock_endread(&self->d_eh_frame_cache_lock);
	}

	/* Scan the .eh_frame section of the driver. */
	status = unwind_fde_scan(self->d_eh_frame_start,
	                         self->d_eh_frame_end,
	                         absolute_pc, result,
	                         sizeof(void *));

	/* Try to cache the results  upon success, but don't do  so
	 * if the kernel's been poisoned, or trying to the lock the
	 * cache for writing would most likely block. */
	if likely(status == UNWIND_SUCCESS && !kernel_poisoned() &&
	          atomic_rwlock_canwrite(&self->d_eh_frame_cache_lock)) {
		struct heapptr cp;
		assert(absolute_pc >= result->f_pcstart);
		assert(absolute_pc < result->f_pcend);
		cp = heap_alloc_untraced_nx(&kernel_locked_heap,
		                            sizeof(struct driver_fde_cache),
		                            GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT);
		if (cp.hp_siz != 0) {
			struct driver_fde_cache *cache;
			cache = (struct driver_fde_cache *)cp.hp_ptr;
			memcpy(&cache->dfc_fde, result, sizeof(unwind_fde_t));
			cache->dfc_heapsz = cp.hp_siz;
			if likely(atomic_rwlock_trywrite(&self->d_eh_frame_cache_lock)) {
				bool ok;
				/* Try to insert the entry into the cache. */
				ok = dfc_tryinsert(&self->d_eh_frame_cache, cache);
				atomic_rwlock_endwrite(&self->d_eh_frame_cache_lock);
				if unlikely(!ok)
					goto cannot_cache;
			} else {
cannot_cache:
				heap_free_untraced(&kernel_locked_heap,
				                   cp.hp_ptr, cp.hp_siz,
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
 * caches for quick (O(1))  repeated access to an  FDE located within a  known
 * function. */
INTERN NOBLOCK NONNULL((2)) unsigned int
NOTHROW_NCX(KCALL libuw_unwind_fde_find)(void const *absolute_pc,
                                         unwind_fde_t *__restrict result) {
	unsigned int error;
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
DEFINE_PUBLIC_ALIAS(unwind_fde_find, libuw_unwind_fde_find);








/************************************************************************/
/* Driver load/unload functions                                         */
/************************************************************************/

/* Initialize the given driver by transitioning its state  to
 * `DRIVER_STATE_LOADED'. If this fails, or if the driver was
 * already finalized, its state is set to `DRIVER_STATE_KILL'
 * instead. */
PUBLIC NONNULL((1)) void FCALL
driver_initialize(struct driver *__restrict self)
		THROWS(E_WOULDBLOCK, E_FSERROR, E_NOT_EXECUTABLE);

/* Finalize the given driver. Note that this function is NOTHROW,
 * but isn't necessarily NOBLOCK! - Driver finalizers are allowed
 * to block and throw exceptions (meaning that this function  may
 * also block), and any exception  thrown will be written to  the
 * system log. However, any such exceptions are silently ignored,
 * and driver finalization will always continue regardless.
 *
 * Note however that driver program text/data will only be
 * unmapped once the driver's weak reference counter drops
 * to `0'! */
PUBLIC NONNULL((1)) void
NOTHROW(FCALL driver_finalize)(struct driver *__restrict self);


/* Load & return  a driver from  a given `driver_file'.  The
 * returned driver may  not have been  initialized, yet.  As
 * such, the  caller  should  use  `driver_initialize()'  in
 * order to ensure that the returned driver was initialized.
 * @param: pnew_driver_loaded: When non-NULL, set to true/false in
 *                             order to indicate  if the  returned
 *                             driver was newly loaded, or already
 *                             present before. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct driver *KCALL
driver_loadmod_file(struct mfile *__restrict driver_file,
                    struct path *driver_path,
                    struct directory_entry *driver_dentry,
                    USER CHECKED char const *driver_cmdline,
                    bool *pnew_driver_loaded)
		THROWS(E_SEGFAULT, E_NOT_EXECUTABLE, E_BADALLOC, E_IOERROR);
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct driver *KCALL
driver_loadmod_blob(USER CHECKED void const *base, size_t num_bytes,
                    USER CHECKED char const *driver_cmdline,
                    bool *pnew_driver_loaded)
		THROWS(E_SEGFAULT, E_NOT_EXECUTABLE, E_BADALLOC, E_IOERROR);
PUBLIC ATTR_RETNONNULL WUNUSED REF struct driver *KCALL
driver_loadmod(USER CHECKED char const *driver_name,
               USER CHECKED char const *driver_cmdline,
               bool *pnew_driver_loaded)
		THROWS(E_SEGFAULT, E_NOT_EXECUTABLE, E_BADALLOC, E_IOERROR, E_FSERROR);


/* Helper-wrappers for the functions above that will automatically
 * ensure that the driver is initialized successfully, and if said
 * initialization were to cause an exception, finalize the  driver
 * to have it be unloaded once again. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct driver *KCALL
driver_insmod_file(struct mfile *__restrict driver_file,
                   struct path *driver_path,
                   struct directory_entry *driver_dentry,
                   USER CHECKED char const *driver_cmdline,
                   bool *pnew_driver_loaded)
		THROWS(E_SEGFAULT, E_NOT_EXECUTABLE, E_BADALLOC, E_IOERROR) {
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

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct driver *KCALL
driver_insmod_blob(USER CHECKED void const *base, size_t num_bytes,
                   USER CHECKED char const *driver_cmdline,
                   bool *pnew_driver_loaded)
		THROWS(E_SEGFAULT, E_NOT_EXECUTABLE, E_BADALLOC, E_IOERROR) {
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

PUBLIC ATTR_RETNONNULL WUNUSED REF struct driver *KCALL
driver_insmod(USER CHECKED char const *driver_name,
              USER CHECKED char const *driver_cmdline,
              bool *pnew_driver_loaded)
		THROWS(E_SEGFAULT, E_NOT_EXECUTABLE, E_BADALLOC, E_IOERROR, E_FSERROR) {
	REF struct driver *result;
	result = driver_loadmod(driver_name, driver_cmdline, pnew_driver_loaded);
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
PUBLIC NONNULL((1)) unsigned int FCALL
driver_try_decref_and_delmod(/*inherit(always)*/ REF struct driver *__restrict self,
                             unsigned int flags)
		THROWS(E_WOULDBLOCK);



/* Unload a driver from the kernel core.
 * @param: driver_name: The name of the driver, or its
 *                      filename (when the first character is `/')
 * @param: flags: Set of `DRIVER_DELMOD_F_*'
 * @return: * :   One of `DRIVER_DELMOD_ST_*' */
PUBLIC NONNULL((1)) unsigned int FCALL
driver_delmod(USER CHECKED char const *driver_name,
              unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
PUBLIC NONNULL((1)) unsigned int FCALL
driver_delmod_file(struct mfile *__restrict driver_file,
                   unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);





/************************************************************************/
/* Loaded driver enumeration (lockless!)                                */
/************************************************************************/
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL driver_loadlist_destroy)(struct driver_loadlist *__restrict self);

/* Return the list of currently loaded drivers.
 * Note that this function is  NOBLOCK+NOTHROW! */
PUBLIC NOBLOCK ATTR_RETNONNULL WUNUSED REF struct driver_loadlist *
NOTHROW(FCALL get_driver_loadlist)(void);



/* [1..1] The current driver library path.
 * This path  is  a  ':'-separated list  of  UNIX-style  pathnames
 * that are used to resolve dependencies of kernel driver modules.
 * By default, this  string is  KERNEL_DRIVER_DEFAULT_LIBRARY_PATH */
PUBLIC struct driver_libpath_arref driver_libpath;



DECL_END
#endif /* CONFIG_USE_NEW_DRIVER */

#endif /* !GUARD_KERNEL_SRC_MEMORY_DRIVER_C */
