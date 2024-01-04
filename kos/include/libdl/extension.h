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
#ifndef _LIBDL_EXTENSION_H
#define _LIBDL_EXTENSION_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include <hybrid/sequence/list.h>
#include <hybrid/typecore.h>

#include <kos/anno.h>
#include <kos/exec/elf.h>
#include <kos/types.h>

#include <elf.h>
#include <stdbool.h>

/* Writing a DL extension:
 *
 * ./my_libdl_extension.c:
 * >> #include <libdl/module.h>
 * >> #include <libdl/extension.h>
 * >> #include <dlfcn.h>
 * >>
 * >> ...
 * >>
 * >> PRIVATE struct dlmodule_format my_module_format = {
 * >>     .df_magic = { '1', '2', '3', '4', '5', '\n' },
 * >>     .df_magsz = 6,
 * >>     .df_open  = ...,
 * >>     ...
 * >> };
 * >>
 * >> PRIVATE __attribute__((constructor)) void init(void) {
 * >>     if (dlauxctrl(NULL,
 * >>                   DLAUXCTRL_REGISTER_EXTENSION,
 * >>                   &my_module_format,
 * >>                   sizeof(struct dlmodule_format),
 * >>                   sizeof(struct dlcore_ops))) {
 * >>         // At this point, `my_module_format.df_core' has been initialized,
 * >>         // and any future library loaded by `dlopen(3D)' will be check
 * >>         // for a magic header equal to `MY_MAGIC', and be processed
 * >>         // by `my_module_format.df_open' should that be the case.
 * >>     }
 * >> }
 *
 * Compile & install such an extension as (from a perspective within KOS itself):
 * KOS$ cc -o mydlext.so -shared my_libdl_extension.c
 *
 * ./file_using_mydlext.format:
 * >> 12345
 * >> This file will be recognized as a shared library by `mydlext.so'
 *
 * ./main.c:
 * >> #include <dlfcn.h>
 * >> int main() {
 * >>     void *mod;
 * >>     // Enable support for mydlext
 * >>     dlopen("./mydlext.so", RTLD_GLOBAL);
 * >>     // Open the custom dl extension ~library~
 * >>     mod = dlopen("./file_using_mydlext.format", RTLD_GLOBAL);
 * >>     ...
 * >> }
 *
 *
 */


DECL_BEGIN

/* Max number of ~magic~ bytes that a RTLD extension may require */
#undef DL_MODULE_MAXMAGIC
#define DL_MODULE_MAXMAGIC   __SIZEOF_ELFW(PHDR)

#ifdef __CC__

#ifndef __DlSection_defined
#define __DlSection_defined
struct dlsection;
typedef struct dlsection DlSection;
#endif /* !__DlSection_defined */

#ifndef __DlModule_defined
#define __DlModule_defined
struct dlmodule;
typedef struct dlmodule DlModule;
#endif /* !__DlModule_defined */

struct dlglobals;

/* Jump-table  of callbacks  which may  be invoked  by libdl extensions.
 * A pointer to this structure is stored by the libdl core in  extension
 * module-type ops descriptors during initialization of such extensions.
 * This table contains  internal callbacks  which may be  used by  libdl
 * extensions to call back into the libdl core.
 * Essentially, this is a reverse V-Table to expose internal libdl functions
 * to loader extensions (and loader extensions only), without clobbering the
 * actual export namespace (i.e. functions such as `dlopen(3D)') */
struct dlcore_ops {
#define DL_COREOP(attr, return, nothrow, cc, name, args) attr return nothrow(cc *name) args;
#define DL_COREFIELD(type, name)                         type *name;
#include "coreops.def"
};

struct __dl_info_struct;

struct dl_sect_info {
	void     *dsi_addr;     /* [0..1] Allocation section  address (when  non-NULL, pointer  to
	                         * the static program image to where the section's mapping starts) */
	size_t    dsi_size;     /* Section size (in bytes) */
	size_t    dsi_entsize;  /* Section entry size (in bytes) (or 0 if unknown) */
	uintptr_t dsi_link;     /* Index of another section that is linked by this one (or `0' if unused) */
	uintptr_t dsi_info;     /* Index of another section that is linked by this one (or `0' if unused) */
	uintptr_t dsi_elfflags; /* ELF section flags (set of `SHF_*' from <elf.h>) */
	pos64_t   dsi_offset;   /* Absolute file offset where section data starts. */
};

#ifndef ____dl_iterator_callback_defined
#define ____dl_iterator_callback_defined
struct dl_phdr_info;
/* Callback prototype for `dl_iterate_phdr()' */
typedef int (__DLFCN_CC *__dl_iterator_callback)(struct dl_phdr_info *__info,
                                                 __size_t __info_size, void *__arg);
#endif /* !____dl_iterator_callback_defined */


/* Module extension format.
 * NOTE: Module format extensions cannot be unloaded once loaded! */
struct dlmodule_format {
	/* Magic byte sequence for this module format extension. */
	byte_t df_magic[((DL_MODULE_MAXMAGIC -        /* Required base size */
	                  (__SIZEOF_POINTER__ - 1) +  /* Offset for `df_magsz' (see final addend below) */
	                  (__SIZEOF_POINTER__ - 1)) & /* Ceil-align addend */
	                 ~(__SIZEOF_POINTER__ - 1)) + /* Force pointer alignment */
	                (__SIZEOF_POINTER__ - 1)];    /* Added to place `df_magsz' at end of pointer-sized word */
	byte_t df_magsz; /* Length of this format's magic header. <= DL_MODULE_MAXMAGIC */

	struct dlcore_ops       *df_core; /* [1..1] Initialized by the libdl core: A jump-table of callbacks defined by the core. */
#ifdef __BUILDING_LIBDL
	struct dlmodule_format  *df_next; /* [1..1] Next dl module extension format. */
#else /* __BUILDING_LIBDL */
	struct dlmodule_format *_df_next; /* [1..1] Next dl module extension format. */
#endif /* !__BUILDING_LIBDL */

	/* [1..1] Open a DL module, given a header, filename and file descriptor.
	 * NOTE: This function is only called when `bcmp(header, df_magic, df_magsz) == 0'! */
	NONNULL((1, 2)) __REF DlModule *(LIBDL_CC *df_open)(byte_t const header[DL_MODULE_MAXMAGIC],
	                                                    /*inherit(on_success,HEAP)*/ char *__restrict filename,
	                                                    /*inherit(on_success)*/ fd_t fd);

	/* Special return value for `df_open' to instruct libdl to continue
	 * searching for a  matching module format  (to-be used for  module
	 * formats that store  additional magic bytes  somewhere else  than
	 * at the start of some given file). */
#define DLMODULE_FORMAT_OPEN_BAD_MAGIC ((DlModule *)-1)

	/* [1..1] Finalizer callback, to-be invoked when the module is destroyed.
	 * NOTE: This callback is also responsible for calling `sys_unmap()' on
	 *       any mapped program segment  associated with the given  module. */
	NONNULL((1)) void (LIBDL_CC *df_fini)(DlModule *__restrict self);

	/* [0..1] Run user-defined module initializers. */
	NONNULL((1)) void (LIBDL_CC *df_run_initializers)(DlModule *__restrict self);

	/* [0..1] Run user-defined module finalizers (but don't run `dm_finalize'). */
	NONNULL((1)) void (LIBDL_CC *df_run_finalizers)(DlModule *__restrict self);

	/* [1..1] Check if `module_relative_pointer' points into a mapped segment. */
	NONNULL((1)) bool (LIBDL_CC *df_ismapped)(DlModule *__restrict self,
	                                          uintptr_t module_relative_pointer);

	/* [1..1] Format-specific symbol lookup.
	 * @return: * : One of `DLMODULE_FORMAT_DLSYM_*' */
	NONNULL((1, 2, 3)) int (LIBDL_CC *df_dlsym)(DlModule *__restrict self,
	                                            char const *__restrict symbol_name,
	                                            void **__restrict psymbol_addr,
	                                            size_t *psymbol_size);
#define DLMODULE_FORMAT_DLSYM_WEAK  1    /* Symbol found, but it is weak */
#define DLMODULE_FORMAT_DLSYM_OK    0    /* Symbol found */
#define DLMODULE_FORMAT_DLSYM_ERROR (-1) /* Symbol could not be found (dlerror() was not modified) */

	/* [0..1] Format-specific implementation of `dladdr()'. */
	NONNULL((1)) int (LIBDL_CC *df_dladdr)(DlModule *__restrict self,
	                                       uintptr_t module_relative_pointer,
	                                       struct __dl_info_struct *info);

	/* [0..1] Return the index of a section, given its name.
	 *        If necessary, lazily initialize `self->dm_shnum'
	 * @return: >= self->dm_shnum: Unknown section `name' (dlerror() was not modified) */
	NONNULL((1, 2)) uintptr_t (LIBDL_CC *df_dlsectindex)(DlModule *__restrict self, char const *__restrict name);

	/* [0..1] Return information about a section, given its index.
	 *        If necessary, lazily initialize `self->dm_shnum'
	 * @return: != 0: Invalid section index (dlerror() was modified) */
	NONNULL((1, 3)) int (LIBDL_CC *df_dlsectinfo)(DlModule *__restrict self, uintptr_t index,
	                                              struct dl_sect_info *__restrict result);

	/* [0..1] Return the name of a section, given its index.
	 *        If necessary, lazily initialize `self->dm_shnum'
	 * @return: NULL: Invalid section index (dlerror() was modified) */
	NONNULL((1)) char const *(LIBDL_CC *df_dlsectname)(DlModule *__restrict self, uintptr_t index);

	/* [0..1] Enumerate individual program headers in an ELF-like way.
	 *        This operator should fill in:
	 *        >> info->dlpi_phdr
	 *        >> info->dlpi_phnum
	 *        Then invoke `(*callback)(info, sizeof(*info), arg)' and
	 *        propagate its return value.
	 * If this operator isn't provided, the module will be enumerated as though
	 * it only had a single program header spanning `dm_loadstart...dm_loadend' */
	NONNULL((1, 2, 3)) int
	(LIBDL_CC *df_lsphdrs)(DlModule *__restrict self,
	                       struct dl_phdr_info *__restrict info,
	                       __dl_iterator_callback callback, void *arg);

	/* [0..1] Implement extension-specific auxiliary DL control commands.
	 * @param: self: The module on which  the operation is invoked.  When
	 *               the user passed `NULL' to `dlauxctrl()', the current
	 *               main application  module is  used. If  that one  was
	 *               provided  by  an  extension, this  operator  will be
	 *               invoked from that extension.
	 * @param: cmd:  The command being invoked. Note that this will never
	 *               be any of th standard commands, as this operator  is
	 *               essentially just called in the fallback branch after
	 *               all standard commands were checked.
	 * @param: args: Additional arguments (varargs)
	 * @return: * :  Return value for `dlauxctrl()'. Any manipulation of
	 *               `dlerror()' must be done by this operator (if  such
	 *               manipulation is desired).
	 *               This includes the case where `cmd' isn't recognized! */
	NONNULL((1)) void *
	(LIBDL_CC *df_dlauxctrl)(DlModule *__restrict self,
	                         unsigned int cmd,
	                         __builtin_va_list args);

	/* Add more functions here. */
};



#endif /* __CC__ */

DECL_END

#endif /* !_LIBDL_EXTENSION_H */
