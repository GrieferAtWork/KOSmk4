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
#ifndef GUARD_LIBC_LIBC_DL_C
#define GUARD_LIBC_LIBC_DL_C 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <hybrid/atomic.h>

#include <kos/exec/ifunc.h>

#include <dlfcn.h>
#include <stdlib.h>

#include "dl.h"

DECL_BEGIN

#ifdef HAVE_LAZY_LIBDL_RELOCATIONS
#define DEFINE_LAZY_LIBDL_RELOCATION(section, Ptype, name)                    \
	PRIVATE ATTR_SECTION(".bss" section) Ptype pdyn_##name           = NULL;  \
	PRIVATE ATTR_SECTION(".rodata" section) char const name_##name[] = #name; \
	INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text" section)   \
	Ptype NOTHROW_NCX(LIBCCALL libc_get_##name)(void) {                       \
		if (!pdyn_##name) {                                                   \
			Ptype pfun;                                                       \
			*(void **)&pfun = dlsym(RTLD_DEFAULT, name_##name);               \
			if unlikely(!pfun)                                                \
				abort();                                                      \
			ATOMIC_WRITE(pdyn_##name, pfun);                                  \
		}                                                                     \
		return pdyn_##name;                                                   \
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






/************************************************************************/
/* __libc_dl*(3) (libc-exported aliases for libdl functions)            */
/************************************************************************/
DEFINE_PUBLIC_IFUNC(__libc_dlclose, libc_get_dlclose);
DEFINE_PUBLIC_IFUNC(__libc_dlopen_mode, libc_get_dlopen);
DEFINE_PUBLIC_IFUNC(__libc_dlsym, libc_get_dlsym);
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.compat.glibc") PDLSYM
NOTHROW_NCX(LIBCCALL libc_get_dlsym)(void) {
	/* `dlsym(3)'  is special, in  that we obviously  can't do `dlsym(RTLD_DEFAULT, "dlsym")' in
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
