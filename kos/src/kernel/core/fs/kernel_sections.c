/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_FS_DRIVER_C
#define GUARD_KERNEL_CORE_FS_DRIVER_C 1

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/types.h>

#include <elf.h>
#include <stddef.h>

DECL_BEGIN

#define SECTION_DESCRIPTOR_INDEX     PP_CAT2(KERNEL_SECTION_INDEX_, __LINE__)
#define SECTION_DESCRIPTOR_SHSTRNAME PP_CAT2(ks_name_, __LINE__)



/* Define globals. */
#define INTERN_SECTION(symbol_name, name, type, flags, start, size, entsize, link, info) /* nothing */
#include "kernel_sections.def"

/* Define the kernel's .shstrtab section */
struct kernel_shstrtab {
#define INTERN_SECTION(symbol_name, name, type, flags, start, size, entsize, link, info) \
	char SECTION_DESCRIPTOR_SHSTRNAME[sizeof(name)];
#include "kernel_sections.def"
	char zero;
};

INTERN_CONST ATTR_COLDRODATA struct kernel_shstrtab const kernel_shstrtab_data = {
#define INTERN_SECTION(symbol_name, name, type, flags, start, size, entsize, link, info) \
	/* .SECTION_DESCRIPTOR_SHSTRNAME = */ name,
#include "kernel_sections.def"
	/* .zero = */ 0
};



/* Define section indices */
enum {
#define INTERN_SECTION(symbol_name, name, type, flags, start, size, entsize, link, info) \
	SECTION_DESCRIPTOR_INDEX,
#include "kernel_sections.def"
	KERNEL_SECTIONS_COUNT
};


/* Define the ELF section header vector. */
INTERN_CONST ATTR_COLDRODATA ElfW(Shdr) const kernel_shdr[KERNEL_SECTIONS_COUNT] = {
#define INTERN_SECTION(symbol_name, name, type, flags, start, size, entsize, link, info)      \
	/* [SECTION_DESCRIPTOR_INDEX] = */ {                                                      \
		/* .sh_name      = */ offsetof(struct kernel_shstrtab, SECTION_DESCRIPTOR_SHSTRNAME), \
		/* .sh_type      = */ (type),                                                         \
		/* .sh_flags     = */ (flags),                                                        \
		/* .sh_addr      = */ (uintptr_t)(start),                                             \
		/* .sh_offset    = */ 0,                                                              \
		/* .sh_size      = */ (uintptr_t)(size),                                              \
		/* .sh_link      = */ link,                                                           \
		/* .sh_info      = */ info,                                                           \
		/* .sh_addralign = */ 1,                                                              \
		/* .sh_entsize   = */ entsize,                                                        \
	},
#include "kernel_sections.def"
};



#if __SIZEOF_POINTER__ > 4
#define _DRIVER_INIT_PAD { 0, },
#else /* __SIZEOF_POINTER__ > 4 */
#define _DRIVER_INIT_PAD /* nothing */
#endif /* __SIZEOF_POINTER__ <= 4 */

/* Define the driver section descriptors. */
#define _SECTION(decl_name, name, type, flags, start, size, entsize, link, info)         \
	struct driver_section decl_name = {                                                  \
		/* .ds_refcnt    = */ 2,                                                         \
		/* .ds_data      = */ (void *)(start),                                           \
		/* .ds_size      = */ (size_t)(size),                                            \
		/* .ds_entsize   = */ (size_t)(entsize),                                         \
		/* .ds_link      = */ (link),                                                    \
		/* .ds_info      = */ (info),                                                    \
		/* .ds_flags     = */ (flags),                                                   \
		/* .ds_module    = */ &kernel_driver,                                            \
		/* .ds_dangling  = */ NULL,                                                      \
		/* .ds_sectflags = */ DRIVER_DLSECTION_FNORMAL,                                  \
		/* .ds_index     = */ SECTION_DESCRIPTOR_INDEX,                                  \
		_DRIVER_INIT_PAD                                                                 \
		/* .ds_cdata     = */ (flags) & SHF_COMPRESSED ? (void *)(-1) : (void *)(start), \
		/* .ds_csize     = */ (flags) & SHF_COMPRESSED ? 0 : (size_t)(size),             \
	};
#define INTERN_SECTION(intern_name, name, type, flags, start, size, entsize, link, info) \
	INTERN _SECTION(intern_name, name, type, flags, start, size, entsize, link, info)
#define EXPORT_SECTION(export_name, name, type, flags, start, size, entsize, link, info) \
	PUBLIC _SECTION(export_name, name, type, flags, start, size, entsize, link, info)
#include "kernel_sections.def"


/* Define the driver sections vector. */
INTERN_CONST struct driver_section *const kernel_sections[KERNEL_SECTIONS_COUNT] = {
#define INTERN_SECTION(symbol_name, ...) /* [SECTION_DESCRIPTOR_INDEX] = */ &symbol_name,
#include "kernel_sections.def"
};



DECL_END

#endif /* !GUARD_KERNEL_CORE_FS_DRIVER_C */
