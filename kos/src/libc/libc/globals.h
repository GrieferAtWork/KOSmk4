/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_LIBC_GLOBALS_H
#define GUARD_LIBC_LIBC_GLOBALS_H 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <kos/types.h>

#ifdef __CC__
DECL_BEGIN

#ifndef __KERNEL__

#if defined(__OPTIMIZE_SIZE__) && 0 /* -Os is a per-file option, so don't do global config based on it! */
/* Disable norel access. */
#define GET_NOREL_GLOBAL(name)             __bind_##name
#define DECLARE_NOREL_GLOBAL_META(T, name) DATDEF T __bind_##name ASMNAME(#name)
#define DEFINE_NOREL_GLOBAL_META(T, name)  DATDEF T __bind_##name ASMNAME(#name)
#else /* __OPTIMIZE_SIZE__ */
#define GET_NOREL_GLOBAL(name) (*(__pdyn_##name ? __pdyn_##name : __##name##_impl()))
#define DECLARE_NOREL_GLOBAL_META(T, name) \
	INTDEF T *__pdyn_##name;               \
	INTDEF ATTR_CONST T *(LIBCCALL __##name##_impl)(void)
#ifdef __INTELLISENSE__
#define DEFINE_NOREL_GLOBAL_META(T, name, section)                                  \
	INTERN ATTR_SECTION(".bss" section) T *__pdyn_##name               = __NULLPTR; \
	PRIVATE ATTR_SECTION(".rodata" section) char const __name_##name[] = #name;     \
	INTERN ATTR_CONST ATTR_SECTION(".text" section) T *(LIBCCALL __##name##_impl)(void)
#else /* __INTELLISENSE__ */
#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>

#include <dlfcn.h>
#define DEFINE_NOREL_GLOBAL_META(T, name, section)                                        \
	INTERN ATTR_SECTION(".bss" section) T *__pdyn_##name               = __NULLPTR;       \
	PRIVATE ATTR_SECTION(".rodata" section) char const __name_##name[] = #name;           \
	INTERN ATTR_CONST ATTR_SECTION(".text" section) T *(LIBCCALL __##name##_impl)(void) { \
		T *ptr = (T *)dlsym(RTLD_DEFAULT, __name_##name);                                 \
		__hybrid_assert(ptr);                                                             \
		__hybrid_atomic_store(__pdyn_##name, ptr, __ATOMIC_RELEASE);                      \
		return ptr;                                                                       \
	}
#endif /* !__INTELLISENSE__ */
#endif /* !__OPTIMIZE_SIZE__ */


/* Globals defined by libdl.so */
#undef ____peb_defined
#define ____peb_defined
#undef __peb
#undef __argc
#undef __argv
#undef __LOCAL_program_invocation_name
#undef __LOCAL_program_invocation_name_p
#undef program_invocation_name
#undef __progname_full
#undef _pgmptr
#undef __LOCAL_program_invocation_short_name
#undef __LOCAL_program_invocation_short_name_p
#undef program_invocation_short_name
#undef __progname
#undef __LOCAL_environ
#undef __environ
#undef _environ
#undef _wenviron
#undef environ
struct process_peb;
DECLARE_NOREL_GLOBAL_META(struct process_peb, __peb);
DECLARE_NOREL_GLOBAL_META(int, __argc);
DECLARE_NOREL_GLOBAL_META(char **, __argv);
DECLARE_NOREL_GLOBAL_META(char *, _pgmptr);    /* aka. `program_invocation_name', `__progname_full' */
DECLARE_NOREL_GLOBAL_META(char *, __progname); /* aka. `program_invocation_short_name' */
DECLARE_NOREL_GLOBAL_META(char **, environ);   /* aka. `_environ', `__environ' */
DECLARE_NOREL_GLOBAL_META(char32_t **, _wenviron);
#define __peb                                   GET_NOREL_GLOBAL(__peb)
#define __argc                                  GET_NOREL_GLOBAL(__argc)
#define __argv                                  GET_NOREL_GLOBAL(__argv)
#define __LOCAL_program_invocation_name         GET_NOREL_GLOBAL(_pgmptr)
#define __LOCAL_program_invocation_name_p       GET_NOREL_GLOBAL(_pgmptr)
#define program_invocation_name                 GET_NOREL_GLOBAL(_pgmptr)
#define __progname_full                         GET_NOREL_GLOBAL(_pgmptr)
#define _pgmptr                                 GET_NOREL_GLOBAL(_pgmptr)
#define __LOCAL_program_invocation_short_name   GET_NOREL_GLOBAL(__progname)
#define __LOCAL_program_invocation_short_name_p GET_NOREL_GLOBAL(__progname)
#define program_invocation_short_name           GET_NOREL_GLOBAL(__progname)
#define __progname                              GET_NOREL_GLOBAL(__progname)
#define __LOCAL_environ                         GET_NOREL_GLOBAL(environ)
#define __environ                               GET_NOREL_GLOBAL(environ)
#define _environ                                GET_NOREL_GLOBAL(environ)
#define environ                                 GET_NOREL_GLOBAL(environ)
#define _wenviron                               GET_NOREL_GLOBAL(_wenviron)



/* <stdio.h> */
#ifndef __std_FILE_defined
#define __std_FILE_defined
__NAMESPACE_STD_BEGIN
typedef __FILE FILE;
__NAMESPACE_STD_END
#endif /* !__std_FILE_defined */
#ifndef __FILE_defined
#define __FILE_defined
__NAMESPACE_STD_USING(FILE)
#endif /* !__FILE_defined */
#undef __local_stdstream_defined
#undef __stdstreams_defined
#undef __LOCAL_stdin
#undef __LOCAL_stdout
#undef __LOCAL_stderr
#undef stdin
#undef stdout
#undef stderr
DECLARE_NOREL_GLOBAL_META(FILE *, stdin);
DECLARE_NOREL_GLOBAL_META(FILE *, stdout);
DECLARE_NOREL_GLOBAL_META(FILE *, stderr);
#define __local_stdstream_defined
#define __LOCAL_stdin  GET_NOREL_GLOBAL(stdin)
#define __LOCAL_stdout GET_NOREL_GLOBAL(stdout)
#define __LOCAL_stderr GET_NOREL_GLOBAL(stderr)
#define __stdstreams_defined
#define stdin  GET_NOREL_GLOBAL(stdin)
#define stdout GET_NOREL_GLOBAL(stdout)
#define stderr GET_NOREL_GLOBAL(stderr)


/* <error.h> */
#undef __LOCAL_error_print_progname
#undef __LOCAL_error_message_count
#undef __LOCAL_error_one_per_line
#undef error_message_count
#undef error_print_progname
#undef error_one_per_line
typedef void (LIBKCALL *PERROR_PRINT_PROGNAME)(void);
DECLARE_NOREL_GLOBAL_META(PERROR_PRINT_PROGNAME, error_print_progname);
DECLARE_NOREL_GLOBAL_META(unsigned int, error_message_count);
DECLARE_NOREL_GLOBAL_META(int, error_one_per_line);
#define __LOCAL_error_print_progname GET_NOREL_GLOBAL(error_print_progname)
#define __LOCAL_error_message_count  GET_NOREL_GLOBAL(error_message_count)
#define __LOCAL_error_one_per_line   GET_NOREL_GLOBAL(error_one_per_line)
#define error_print_progname         GET_NOREL_GLOBAL(error_print_progname)
#define error_message_count          GET_NOREL_GLOBAL(error_message_count)
#define error_one_per_line           GET_NOREL_GLOBAL(error_one_per_line)


/* <regex.h> */
#undef re_syntax_options
#ifndef __reg_syntax_t_defined
#define __reg_syntax_t_defined
typedef __ULONGPTR_TYPE__ reg_syntax_t; /* Set of `RE_*' */
#endif /* !__reg_syntax_t_defined */
DECLARE_NOREL_GLOBAL_META(reg_syntax_t, re_syntax_options);
#define re_syntax_options GET_NOREL_GLOBAL(re_syntax_options)


/* <time.h> */
#undef __tzname
#undef __timezone
#undef __daylight
#undef tzname
#undef timezone
#undef daylight
DECLARE_NOREL_GLOBAL_META(char *, tzname);
DECLARE_NOREL_GLOBAL_META(longptr_t, timezone);
DECLARE_NOREL_GLOBAL_META(int, daylight);
#define __tzname   GET_NOREL_GLOBAL(tzname)
#define __timezone GET_NOREL_GLOBAL(timezone)
#define __daylight GET_NOREL_GLOBAL(daylight)
#define tzname     GET_NOREL_GLOBAL(tzname)
#define timezone   GET_NOREL_GLOBAL(timezone)
#define daylight   GET_NOREL_GLOBAL(daylight)


/* <getopt.h> */
#undef optarg
#undef optind
#undef opterr
#undef optopt
DECLARE_NOREL_GLOBAL_META(char *, optarg);
DECLARE_NOREL_GLOBAL_META(int, optind);
DECLARE_NOREL_GLOBAL_META(int, opterr);
DECLARE_NOREL_GLOBAL_META(int, optopt);
#define optarg GET_NOREL_GLOBAL(optarg)
#define optind GET_NOREL_GLOBAL(optind)
#define opterr GET_NOREL_GLOBAL(opterr)
#define optopt GET_NOREL_GLOBAL(optopt)


/* <libintl.h> */
#undef _nl_msg_cat_cntr
DECLARE_NOREL_GLOBAL_META(int, _nl_msg_cat_cntr);
#define _nl_msg_cat_cntr GET_NOREL_GLOBAL(_nl_msg_cat_cntr)


/* <math.h> */
#undef signgam
#undef __signgam
#undef __LOCAL_signgam
DECLARE_NOREL_GLOBAL_META(int, signgam);
#define signgam         GET_NOREL_GLOBAL(signgam)
#define __LOCAL_signgam GET_NOREL_GLOBAL(signgam)
#define __signgam()     (&signgam)

#endif /* !__KERNEL__ */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_LIBC_LIBC_GLOBALS_H */
