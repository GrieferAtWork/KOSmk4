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
#ifndef GUARD_LIBC_LIBC_TLS_GLOBALS_C
#define GUARD_LIBC_LIBC_TLS_GLOBALS_C 1

#include "../api.h"
/**/

#include "dl.h"
#include "tls-globals.h"
#include "tls.h"
/**/

#include <malloc.h>
#include <pthread.h>
#include <stdlib.h>

DECL_BEGIN

PRIVATE ATTR_SECTION(".bss.crt.sched.pthread") struct libc_tlsglobals mainthread_globals = {};

PRIVATE ATTR_SECTION(".text.crt.sched.pthread") WUNUSED bool
NOTHROW(LIBCCALL get_LIBC_TLS_GLOBALS_ALLOW_UNSAFE)(void) {
	int *sym;
	char *env;

	/* Check for the relevant environment variable. */
	env = getenv("LIBC_TLS_GLOBALS_ALLOW_UNSAFE");
	if (env != NULL)
		return *env != '\0';

	/* Check if the hosted program defines a symbol `int __libc_tls_globals_allow_unsafe'.
	 * If it does,  that symbol  being non-zero is  used as  the configuration  indicator. */
	sym = (int *)dlsym(RTLD_DEFAULT, "__libc_tls_globals_allow_unsafe");
	if (sym != NULL)
		return *sym != 0;

	/* Fallback: don't allow unsafe TLS-globals re-use. */
	return false;
}

PRIVATE ATTR_NORETURN ATTR_SECTION(".text.crt.sched.pthread") void
NOTHROW(LIBCCALL abort_tls_globals_alloc_failed)(void) {
	/* Allow applications to define a function which we call here:
	 * >> PUBLIC void __libc_tls_globals_alloc_failed(void); */
	void (*handler)(void);
	*(void **)&handler = dlsym(RTLD_DEFAULT, "__libc_tls_globals_alloc_failed");
	if (handler != NULL)
		(*handler)();
	abort();
}

/* Return a pointer to the calling thread's tls-globals controller. */
ATTR_SECTION(".text.crt.sched.pthread")
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED struct libc_tlsglobals *
NOTHROW(LIBCCALL libc_get_tlsglobals)(void) {
	struct libc_tlsglobals *result = current.pt_tglobals;
	if likely(result)
		return result;

	/* TLS globals haven't been allocated for the calling thread. */
	if (pthread_main_np()) {
		result = &mainthread_globals;
	} else {
		result = (struct libc_tlsglobals *)calloc(sizeof(struct libc_tlsglobals));
		if unlikely(!result) {
			if (!get_LIBC_TLS_GLOBALS_ALLOW_UNSAFE())
				abort_tls_globals_alloc_failed();
			result = &mainthread_globals;
		}
	}
	current.pt_tglobals = result;
	return result;
}

/* Finalize `self' (called when a pthread exits, but not called for the main thread) */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) void
NOTHROW(LIBCCALL libc_fini_tlsglobals)(struct libc_tlsglobals *__restrict self) {
/*[[[begin:libc_fini_tlsglobals]]]*/
	free(self->ltg_getpass_buf);
	free(self->ltg_cuserid_buf);
	free(self->ltg_devname_buf);
	free(self->ltg_ptsname_buf);
	free(self->ltg_ttyname_buf);
/*[[[end:libc_fini_tlsglobals]]]*/
}


DECL_END

#endif /* !GUARD_LIBC_LIBC_TLS_GLOBALS_C */
