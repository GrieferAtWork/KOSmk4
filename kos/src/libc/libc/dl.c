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
#ifndef GUARD_LIBC_LIBC_DL_C
#define GUARD_LIBC_LIBC_DL_C 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <hybrid/atomic.h>

#include <dlfcn.h>
#include <stdlib.h>

#include "dl.h"

DECL_BEGIN

#ifdef HAVE_LAZY_LIBDL_RELOCATIONS
#define DEFINE_LAZY_LIBDL_RELOCATION(section, Ptype, name)                                   \
	PRIVATE ATTR_SECTION(".bss" section ".pdyn_" #name) Ptype pdyn_##name           = NULL;  \
	PRIVATE ATTR_SECTION(".rodata" section ".name_" #name) char const name_##name[] = #name; \
	INTERN ATTR_SECTION(".text" section ".libc_get_" #name)                                  \
	ATTR_RETNONNULL WUNUSED Ptype NOTHROW_NCX(LIBCCALL libc_get_##name)(void) {              \
		if (!pdyn_##name) {                                                                  \
			Ptype pfun;                                                                      \
			*(void **)&pfun = dlsym(RTLD_DEFAULT, name_##name);                              \
			if unlikely(!pfun)                                                               \
				abort();                                                                     \
			ATOMIC_WRITE(pdyn_##name, pfun);                                                 \
		}                                                                                    \
		return pdyn_##name;                                                                  \
	}
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLOPEN_SECTION, PDLOPEN, dlopen)
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLCLOSE_SECTION, PDLCLOSE, dlclose)
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLTLSALLOCSEG_SECTION, PDLTLSALLOCSEG, dltlsallocseg)
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLTLSFREESEG_SECTION, PDLTLSFREESEG, dltlsfreeseg)
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLGETHANDLE_SECTION, PDLGETHANDLE, dlgethandle)
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLGETMODULE_SECTION, PDLGETMODULE, dlgetmodule)
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLMODULEFD_SECTION, PDLMODULEFD, dlmodulefd)
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLAUXCTRL_SECTION, PDLAUXCTRL, dlauxctrl)
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLERROR_SECTION, PDLERROR, dlerror)
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLMODULEBASE_SECTION, PDLMODULEBASE, dlmodulebase)
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLEXCEPTAWARE_SECTION, PDLEXCEPTAWARE, dlexceptaware)
DEFINE_LAZY_LIBDL_RELOCATION(LIBC_DLTLSADDR2_SECTION, PDLTLSADDR2, dltlsaddr2)
#undef DEFINE_LAZY_LIBDL_RELOCATION
#endif /* HAVE_LAZY_LIBDL_RELOCATIONS */

DECL_END

#endif /* !GUARD_LIBC_LIBC_DL_C */
