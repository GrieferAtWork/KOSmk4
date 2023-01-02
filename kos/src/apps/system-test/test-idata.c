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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_IDATA_C
#define GUARD_APPS_SYSTEM_TEST_TEST_IDATA_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#undef NDEBUG

/* System headers are smart enough to define `sys_errlist' not as an external
 * data object, but rather as a  direct invocation of its resolver  function,
 * which in turn would allow its initialization to be delayed until the point
 * of first use.
 * Now that is good  and all, but we're  not here to have  the headers help  us
 * write the most optimal  code possible. -  No: we're here  to test the  idata
 * system, meaning that we want these 2 symbols to be linked as actual external
 * data objects.
 * So by pre-defining macros with the these names, we can make the headers think
 * that  these symbols have  already been defined,  thus preventing headers from
 * actually defining them! */
#define sys_errlist DONT_DEFINE_sys_errlist
#define sys_nerr    DONT_DEFINE_sys_nerr
#include <hybrid/compiler.h>

#include <kos/types.h>
#include <system-test/ctest.h>

#include <errno.h>
#include <string.h>
#include <dlfcn.h>
#include <signal.h>
#undef sys_errlist
#undef sys_nerr

DECL_BEGIN

extern char const *const sys_errlist[];
extern int sys_nerr;

DEFINE_TEST(idata) {
	unsigned int i;
	/* Make sure that IDATA works when used with
	 * regularly  linked  global  data  objects. */
	for (i = 0; i < (unsigned int)sys_nerr; ++i) {
		char const *a = sys_errlist[i];
		char const *b = strerrordesc_np(i);
		EQf(a, b, "i = %u", i);
	}
	{
		char const *const *sys_siglist_p;
		char const *const *_sys_siglist_p;
		/* Also make sure that IDATA works when used with dlsym()
		 * Note that we don't use `sys_errlist' for this, because
		 * that variable may have been copied out of libc because
		 * it was likely linked with a R_xxx_COPY relocation. */
		sys_siglist_p  = (char const *const *)dlsym(RTLD_DEFAULT, "sys_siglist");
		ISnonnullf(sys_siglist_p, "%s", dlerror());
		_sys_siglist_p = (char const *const *)dlsym(RTLD_DEFAULT, "_sys_siglist");
		ISnonnullf(_sys_siglist_p, "%s", dlerror());
		EQ(sys_siglist_p, _sys_siglist_p);
		for (i = 0; i < NSIG; ++i) {
			char const *a = sys_siglist_p[i];
			char const *b = sigdescr_np(i);
			EQf(a, b, "i = %u", i);
		}
	}

}


DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_IDATA_C */
