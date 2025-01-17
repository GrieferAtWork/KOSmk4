/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_LIBC_DL_C
#define GUARD_LIBC_LIBC_DL_C 1
#define _GNU_SOURCE 1

/* Need to define this one so headers expose `struct dl_find_object' for us. */
#define __CRT_HAVE__dl_find_object

/* Keep this one the first */
#include "../api.h"
/**/


#include <kos/exec/ifunc.h>

#include <atomic.h>
#include <dlfcn.h>
#include <elf.h>
#include <link.h>
#include <stdlib.h>
#include <string.h>

#include "dl.h"

DECL_BEGIN

#ifdef HAVE_LAZY_LIBDL_RELOCATIONS
#define DEFINE_LAZY_LIBDL_RELOCATION(section, Ptype, name)                    \
	PRIVATE ATTR_SECTION(".bss" section) Ptype pdyn_##name           = NULL;  \
	PRIVATE ATTR_SECTION(".rodata" section) char const name_##name[] = #name; \
	INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text" section)   \
	Ptype NOTHROW_NCX(LIBCCALL libc_get_##name)(void) {                       \
		Ptype result = atomic_read(&pdyn_##name);                             \
		if (!result) {                                                        \
			*(void **)&result = dlsym(RTLD_DEFAULT, name_##name);             \
			if unlikely(!result)                                              \
				abort();                                                      \
			atomic_write(&pdyn_##name, result);                               \
		}                                                                     \
		return result;                                                        \
	}
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLOPEN_SECTION, PDLOPEN, dlopen)
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLCLOSE_SECTION, PDLCLOSE, dlclose)
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLTLSALLOCSEG_SECTION, PDLTLSALLOCSEG, dltlsallocseg)
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLTLSFREESEG_SECTION, PDLTLSFREESEG, dltlsfreeseg)
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLGETHANDLE_SECTION, PDLGETHANDLE, dlgethandle)
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLGETMODULE_SECTION, PDLGETMODULE, dlgetmodule)
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLMODULEFD_SECTION, PDLMODULEFD, dlmodulefd)
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLMODULENAME_SECTION, PDLMODULENAME, dlmodulename)
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLAUXCTRL_SECTION, PDLAUXCTRL, dlauxctrl)
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLINFO_SECTION, PDLINFO, dlinfo)
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLLOCKSECTION_SECTION, PDLLOCKSECTION, dllocksection)
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLUNLOCKSECTION_SECTION, PDLUNLOCKSECTION, dlunlocksection)
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLERROR_SECTION, PDLERROR, dlerror)
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLMODULEBASE_SECTION, PDLMODULEBASE, dlmodulebase)
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLEXCEPTAWARE_SECTION, PDLEXCEPTAWARE, dlexceptaware)
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLTLSADDR_SECTION, PDLTLSADDR, dltlsaddr)
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLTLSADDR2_SECTION, PDLTLSADDR2, dltlsaddr2)
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLTLSALLOC_SECTION, PDLTLSALLOC, dltlsalloc)
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLTLSFREE_SECTION, PDLTLSFREE, dltlsfree)
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLADDR_SECTION, PDLADDR, dladdr)
#undef DEFINE_LAZY_LIBDL_RELOCATION
#endif /* HAVE_LAZY_LIBDL_RELOCATIONS */

#undef EH_FRAME_NAME
#if DLFO_EH_SEGMENT_TYPE == PT_ARM_EXIDX
#define EH_FRAME_NAME ".ARM.exidx"
#elif DLFO_EH_SEGMENT_TYPE == PT_GNU_EH_FRAME
#define EH_FRAME_NAME ".eh_frame"
#else /* DLFO_EH_SEGMENT_TYPE == ... */
#error "Unable to determine name of eh_frame section from `DLFO_EH_SEGMENT_TYPE'"
#endif /* DLFO_EH_SEGMENT_TYPE != ... */


/************************************************************************/
/* _dl_find_object(3)                                                   */
/************************************************************************/
DEFINE_PUBLIC_ALIAS(_dl_find_object, libc__dl_find_object);
INTERN ATTR_SECTION(".text.crt.compat.glibc") ATTR_OUT(2) int
NOTHROW_NCX(DLFCN_CC libc__dl_find_object)(void const *address,
                                           struct dl_find_object *result) {
	struct dl_section *eh_frame;
	void *handle;
	bzero(result, sizeof(*result)); /* Forward compat */

	/* No need to lookup the handle with INCREF, since specs say that we're
	 * allowed to assume that no  other thread will dlclose(3D) the  module
	 * while we're working in here. */
	handle = dlgethandle(address, DLGETHANDLE_FNORMAL);
	if unlikely(!handle)
		goto err;
//	result->dlfo_flags     = 0; /* """Currently unused and always 0""" */
	result->dlfo_map_start = dlauxctrl(handle, DLAUXCTRL_GET_LOADSTART);
	result->dlfo_map_end   = dlauxctrl(handle, DLAUXCTRL_GET_LOADEND);
#if DLFO_STRUCT_HAS_EH_DBASE
	result->dlfo_eh_dbase = dlauxctrl(handle, DLAUXCTRL_GET_DATABASE);
#endif /* DLFO_STRUCT_HAS_EH_DBASE */

	/* NOTE: On KOS, you can (technically) just cast a dl-handle into a `struct link_map',
	 *       and while that probably won't ever change, for the sake of ensuring that this
	 *       function  will work forever, we still make the call to have libdl do the cast
	 *       for us. */
	if unlikely(dlinfo(handle, RTLD_DI_LINKMAP, &result->dlfo_link_map) != 0)
		goto err; /* Shouldn't get here... */

	/* Load the .eh_frame section (but don't load its data if that hasn't been
	 * loaded already; we need that data to stay loaded, even after we  unlock
	 * the section, so it needs to be apart of a PT_LOAD header) */
	eh_frame = dllocksection(handle, EH_FRAME_NAME, DLLOCKSECTION_FNODATA);
	if (eh_frame) {
		if (eh_frame->ds_data != (void *)-1) {
			result->dlfo_eh_frame = eh_frame->ds_data;
#if DLFO_STRUCT_HAS_EH_COUNT
			result->dlfo_eh_count = eh_frame->ds_size / 8;
#endif /* DLFO_STRUCT_HAS_EH_COUNT */
		}
		dlunlocksection(eh_frame);
	}

	return 0;
err:
	return -1;
}






/************************************************************************/
/* __libc_dl*(3) (libc-exported aliases for libdl functions)            */
/************************************************************************/
DEFINE_PUBLIC_IFUNC(__libc_dlclose, libc_get_dlclose);
DEFINE_PUBLIC_IFUNC(__libc_dlopen_mode, libc_get_dlopen);
DEFINE_PUBLIC_IFUNC(__libc_dlsym, libc_get_dlsym);
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.compat.glibc") PDLSYM
NOTHROW_NCX(LIBCCALL libc_get_dlsym)(void) {
	/* `dlsym(3D)' is special, in that  we obviously can't do `dlsym(RTLD_DEFAULT, "dlsym")'  in
	 * order to load its address  and thus prevent any  relocations against `dlsym'. So  instead
	 * it's one of the  very few relocations that  our libc is allowed  to have. -- This  getter
	 * function for it only needs to exist so we have a way by which to export  `__libc_dlsym()'
	 * (here, we do so by binding  it as an IFUNC that resolves  to the actual libdl address  at
	 * runtime, meaning that in the end, `dlsym(libc, "__libc_dlsym") == dlsym(libdl, "dlsym")') */

#if 1
	/* This right here might look stupid, but it actually _does_ serve a purpose:
	 * If we were to directly access `&dlsym', we'd also get the correct address,
	 * but if we did that, then `dlsym' could no longer be lazily resolved.
	 *
	 * Think about it: lazy resolve works by redirecting the initial call to some
	 * external function to a special wrapper (`dl_load_lazy_relocation') that is
	 * found in libdl. That wrapper will  resolve the symbol, write its  absolute
	 * address into the calling module's GOT, and then proceed to call the symbol
	 * with the register state at the time of the original call.
	 *
	 * But if we did `&dlsym', there wouldn't be any call to trigger lazy symbol
	 * binding. And indeed: doing `&dlsym' causes an `R_386_GLOB_DAT' relocation
	 * to `dlsym' in order to resolve its address in the GOT during module load.
	 *
	 * However: `R_386_GLOB_DAT' obviously can't  use lazy relocations,  meaning
	 * if we directly took the address of `dlsym', then libdl would no longer be
	 * able  to lazily resolve libc's (our) use  of `dlsym', and would be forced
	 * to  resolve the symbol as soon as our library gets loaded, which would be
	 * a tiny bit slower than doing so lazily.
	 *
	 * As  such, the  seemingly non-sensical  construct you're  seeing below does
	 * actually serve a purpose, that purpose being to speed up initialization of
	 * libc! */
	return (PDLSYM)dlsym(RTLD_DEFAULT, "dlsym");
#else
	/* TLDR: this would also work, but would also prevent lazy (RTLD_LAZY) symbol binding. */
	return &dlsym;
#endif
}


DECL_END

#endif /* !GUARD_LIBC_LIBC_DL_C */
