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
#ifndef GUARD_LIBC_LIBC_COMPAT_C
#define GUARD_LIBC_LIBC_COMPAT_C 1

/*
 * Misc functions needed for ABI compatibility with other platforms.
 */

#include "../api.h"
/**/

#include <kos/exec/peb.h>

#include <stdlib.h> /* exit() */

#include "globals.h"

DECL_BEGIN

DEFINE_PUBLIC_ALIAS(__libc_start_main, libc_start_main);
INTERN ATTR_SECTION(".text.crt.glibc.application.init") NONNULL((1)) int LIBCCALL
libc_start_main(int (*main)(int, char **, char **),
                int argc, char **ubp_av,
                void (*init)(void),
                void (*fini)(void),
                void (*rtld_fini)(void),
                void *stack_end) {
	int exit_code;
	struct process_peb *peb;

	/* All of these will contain garbage... */
	(void)argc;
	(void)ubp_av;
	(void)init;
	(void)fini;
	(void)rtld_fini;
	(void)stack_end;

	/* Use the PEB to pass the correct information. */
	peb       = &__peb;
	exit_code = (*main)(peb->pp_argc,
	                    peb->pp_argv,
	                    peb->pp_envp);
	exit(exit_code);
}


#if defined(__i386__) && !defined(__x86_64__)
/* >> void __libc_init(int argc, char *argv[], char *envp[]);
 * Instead of its usual purpose of initializing libc, we define
 * this  function  to write-back  parameters with  their proper
 * values onto the stack, thus allowing the caller to  continue
 * working with them.
 *
 * This may not look like it makes much sense since normally
 * parameters like this can't be  accessed by the caller  of
 * the  function, but `__libc_init()' is provided for compat
 * with old linux programs (1990-2001-ish) that had a custom
 * assembly _start function which essentially did this:
 * >> pushl   <envp>   # With the emulated stub-PEB, this pushes <TOP_OF_STACK>
 * >> pushl   <argv>   # With the emulated stub-PEB, this pushes <TOP_OF_STACK>
 * >> pushl   <argc>   # With the emulated stub-PEB, this pushes `0'
 * >> ...
 * >> call    __libc_init
 * >> ...
 * >> call    main     # Note that arguments for main are never re-loaded,
 * >>                  # meaning that modifications by `__libc_init' are
 * >>                  # preserved! */
DEFINE_PUBLIC_ALIAS(__libc_init, libc___libc_init);

/* Yes GCC. I know it looks like those assignments don't do anything...
 * But  trust me on this one. - Just don't try to optimize them away ;) */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"

/* Prevent GCC from (rightfully) optimizing  away
 * (seemingly unnecessary) parameter assignments. */
__attribute__((optimize("-O0")))
INTERN ATTR_SECTION(".text.crt.glibc.application.init") void LIBCCALL
libc___libc_init(int argc, char *argv[], char *envp[]) {
	struct process_peb *peb;
	peb  = &__peb;
	argc = peb->pp_argc;
	argv = peb->pp_argv;
	envp = peb->pp_envp;
}

#pragma GCC diagnostic pop
#endif /* __i386__ && !__x86_64__ */

DECL_END


/************************************************************************/
/* <fpu_control.h>                                                      */
/************************************************************************/
#if __has_include(<fpu_control.h>)
#include <fpu_control.h>

DECL_BEGIN

#ifndef _FPU_DEFAULT
#ifndef _FPU_IEEE
#define _FPU_IEEE 0
#endif /* !_FPU_IEEE */
#define _FPU_DEFAULT _FPU_IEEE
#endif /* !_FPU_DEFAULT */
#ifndef _FPU_RESERVED
#define _FPU_RESERVED 0
#endif /* !_FPU_RESERVED */

/* >> __fpu_control(3)
 * Control word set during startup of old linux applications. */
#if _FPU_DEFAULT == 0
INTERN ATTR_SECTION(".bss.crt.math.float") fpu_control_t libc___fpu_control = _FPU_DEFAULT;
#else /* _FPU_DEFAULT == 0 */
INTERN ATTR_SECTION(".data.crt.math.float") fpu_control_t libc___fpu_control = _FPU_DEFAULT;
#endif /* _FPU_DEFAULT != 0 */
DEFINE_PUBLIC_ALIAS(__fpu_control, libc___fpu_control);

/* >> __setfpucw(3)
 * Function called by old linux applications to set `__fpu_control()'. */
DEFINE_PUBLIC_ALIAS(__setfpucw, libc___setfpucw);
INTERN ATTR_SECTION(".text.crt.math.float") void
NOTHROW_NCX(LIBCCALL libc___setfpucw)(fpu_control_t ctrl) {
#if _FPU_RESERVED != 0
	fpu_control_t word;
	_FPU_GETCW(word);
	word &= _FPU_RESERVED;
	word |= ctrl & ~_FPU_RESERVED;
	_FPU_SETCW(word);
#else /* _FPU_RESERVED != 0 */
	_FPU_SETCW(ctrl);
#endif /* _FPU_RESERVED == 0 */
}

DECL_END
#endif /* __has_include(<fpu_control.h>) */

#endif /* !GUARD_LIBC_LIBC_COMPAT_C */
