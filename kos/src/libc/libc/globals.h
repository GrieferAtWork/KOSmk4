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
#ifndef GUARD_LIBC_LIBC_GLOBALS_H
#define GUARD_LIBC_LIBC_GLOBALS_H 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <bits/crt/mbstate.h>     /* struct __mbstate */
#include <bits/crt/printf_info.h> /* __reg_syntax_t */
#include <bits/crt/regex.h>       /* __reg_syntax_t */
#include <kos/types.h>

#ifdef __CC__
#ifndef __KERNEL__
DECL_BEGIN

#define GET_NOREL_GLOBAL(name) (*(libc_pdyn_##name ? libc_pdyn_##name : libc_bind_##name()))
#define DECLARE_NOREL_GLOBAL_META(T, name) \
	INTDEF T *libc_pdyn_##name;            \
	INTDEF ATTR_CONST T *(LIBCCALL libc_bind_##name)(void)
#ifdef __INTELLISENSE__
#define DEFINE_NOREL_GLOBAL_META(T, name, section)                                     \
	INTERN ATTR_SECTION(".bss" section) T *libc_pdyn_##name               = __NULLPTR; \
	PRIVATE ATTR_SECTION(".rodata" section) char const libc_name_##name[] = #name;     \
	INTERN ATTR_CONST ATTR_SECTION(".text" section) T *(LIBCCALL libc_bind_##name)(void)
#else /* __INTELLISENSE__ */
#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>

#include <dlfcn.h>
#define DEFINE_NOREL_GLOBAL_META(T, name, section)                                         \
	INTERN ATTR_SECTION(".bss" section) T *libc_pdyn_##name               = __NULLPTR;     \
	PRIVATE ATTR_SECTION(".rodata" section) char const libc_name_##name[] = #name;         \
	INTERN ATTR_CONST ATTR_SECTION(".text" section) T *(LIBCCALL libc_bind_##name)(void) { \
		T *ptr = (T *)dlsym(RTLD_DEFAULT, libc_name_##name);                               \
		__hybrid_assert(ptr);                                                              \
		__hybrid_atomic_store(libc_pdyn_##name, ptr, __ATOMIC_RELEASE);                    \
		return ptr;                                                                        \
	}
#endif /* !__INTELLISENSE__ */


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
#undef environ
struct process_peb;
DECLARE_NOREL_GLOBAL_META(struct process_peb, __peb);
DECLARE_NOREL_GLOBAL_META(int, __argc);
DECLARE_NOREL_GLOBAL_META(char **, __argv);
DECLARE_NOREL_GLOBAL_META(char *, _pgmptr);    /* aka. `program_invocation_name', `__progname_full' */
DECLARE_NOREL_GLOBAL_META(char *, __progname); /* aka. `program_invocation_short_name' */
DECLARE_NOREL_GLOBAL_META(char **, environ);   /* aka. `_environ', `__environ' */
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


/* <stdlib.h> */
#undef _wenviron
DECLARE_NOREL_GLOBAL_META(char32_t **, _wenviron);
#define _wenviron GET_NOREL_GLOBAL(_wenviron)


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
#undef _LIBC_TEMPLATE_STDSTREAMS_H
#define _LIBC_TEMPLATE_STDSTREAMS_H 1
#undef __LOCAL_stdin
#undef __LOCAL_stdout
#undef __LOCAL_stderr
#undef __LOCAL_stdtty
#undef stdin
#undef stdout
#undef stderr
#undef stdtty
DECLARE_NOREL_GLOBAL_META(FILE *, stdin);
DECLARE_NOREL_GLOBAL_META(FILE *, stdout);
DECLARE_NOREL_GLOBAL_META(FILE *, stderr);
DECLARE_NOREL_GLOBAL_META(FILE *, stdtty);
#define __LOCAL_stdin  GET_NOREL_GLOBAL(stdin)
#define __LOCAL_stdout GET_NOREL_GLOBAL(stdout)
#define __LOCAL_stderr GET_NOREL_GLOBAL(stderr)
#define __LOCAL_stdtty GET_NOREL_GLOBAL(stdtty)
#define stdin          GET_NOREL_GLOBAL(stdin)
#define stdout         GET_NOREL_GLOBAL(stdout)
#define stderr         GET_NOREL_GLOBAL(stderr)
#define stdtty         GET_NOREL_GLOBAL(stdtty)


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
#undef __LOCAL_re_syntax_options
DECLARE_NOREL_GLOBAL_META(__reg_syntax_t, re_syntax_options);
#define re_syntax_options         GET_NOREL_GLOBAL(re_syntax_options)
#define __LOCAL_re_syntax_options GET_NOREL_GLOBAL(re_syntax_options)


/* <regexp.h> */
#undef loc1
#undef loc2
#undef locs
#undef __LOCAL_loc1
#undef __LOCAL_loc2
#undef __LOCAL_locs
DECLARE_NOREL_GLOBAL_META(char *, loc1);
DECLARE_NOREL_GLOBAL_META(char *, loc2);
/*DECLARE_NOREL_GLOBAL_META(char *, locs);*/ /* Never used */
#define loc1         GET_NOREL_GLOBAL(loc1)
#define loc2         GET_NOREL_GLOBAL(loc2)
#define locs         GET_NOREL_GLOBAL(locs)
#define __LOCAL_loc1 GET_NOREL_GLOBAL(loc1)
#define __LOCAL_loc2 GET_NOREL_GLOBAL(loc2)
#define __LOCAL_locs GET_NOREL_GLOBAL(locs)


/* <time.h> */
#undef __tzname
#undef __timezone
#undef __daylight
#undef tzname
#undef timezone
#undef daylight
#undef _dstbias
#undef __LOCAL_tzname
#undef __LOCAL_timezone
#undef __LOCAL_daylight
#undef __LOCAL_dstbias
#undef getdate_err
#undef __LOCAL_getdate_err
DECLARE_NOREL_GLOBAL_META(char *, tzname);
DECLARE_NOREL_GLOBAL_META(longptr_t, timezone);
DECLARE_NOREL_GLOBAL_META(int, daylight);
DECLARE_NOREL_GLOBAL_META(__LONG32_TYPE__, _dstbias);
DECLARE_NOREL_GLOBAL_META(int, getdate_err);
#define __tzname            GET_NOREL_GLOBAL(tzname)
#define __timezone          GET_NOREL_GLOBAL(timezone)
#define __daylight          GET_NOREL_GLOBAL(daylight)
#define tzname              GET_NOREL_GLOBAL(tzname)
#define timezone            GET_NOREL_GLOBAL(timezone)
#define daylight            GET_NOREL_GLOBAL(daylight)
#define _dstbias            GET_NOREL_GLOBAL(_dstbias)
#define getdate_err         GET_NOREL_GLOBAL(getdate_err)
#define __LOCAL_tzname      (&GET_NOREL_GLOBAL(tzname))
#define __LOCAL_timezone    GET_NOREL_GLOBAL(timezone)
#define __LOCAL_daylight    GET_NOREL_GLOBAL(daylight)
#define __LOCAL_dstbias     GET_NOREL_GLOBAL(_dstbias)
#define __LOCAL_getdate_err GET_NOREL_GLOBAL(getdate_err)


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


/* <signal.h> */
#ifndef __sigset_t_defined
#define __sigset_t_defined
struct __sigset_struct;
typedef struct __sigset_struct sigset_t;
#endif /* !__sigset_t_defined */
#undef _sigintr
DECLARE_NOREL_GLOBAL_META(sigset_t, _sigintr);
#define _sigintr GET_NOREL_GLOBAL(_sigintr)


/* <mbctype.h> */
#undef _mbctype
#undef _mbcasemap
#undef __LOCAL__mbctype
#undef __LOCAL__mbcasemap
DECLARE_NOREL_GLOBAL_META(unsigned char, _mbctype);
DECLARE_NOREL_GLOBAL_META(unsigned char, _mbcasemap);
#define _mbctype           (&GET_NOREL_GLOBAL(_mbctype))
#define _mbcasemap         (&GET_NOREL_GLOBAL(_mbcasemap))
#define __LOCAL__mbctype   (&GET_NOREL_GLOBAL(_mbctype))
#define __LOCAL__mbcasemap (&GET_NOREL_GLOBAL(_mbcasemap))


/* <stdlib.h> */
#undef MB_CUR_MAX
#undef __LOCAL_MB_CUR_MAX
INTDEF unsigned int libd___mb_cur_max;
#define MB_CUR_MAX         ((size_t)libd___mb_cur_max)
#define __LOCAL_MB_CUR_MAX ((size_t)libd___mb_cur_max)


/* <obstack.h> */
#undef obstack_alloc_failed_handler
#undef obstack_exit_failure
#undef __LOCAL_obstack_alloc_failed_handler
#undef __LOCAL_obstack_exit_failure
typedef void (__LIBKCALL *POBSTACK_ALLOC_FAILED_HANDLER)(void);
DECLARE_NOREL_GLOBAL_META(POBSTACK_ALLOC_FAILED_HANDLER, obstack_alloc_failed_handler);
DECLARE_NOREL_GLOBAL_META(int, obstack_exit_failure);
#define obstack_alloc_failed_handler         GET_NOREL_GLOBAL(obstack_alloc_failed_handler)
#define obstack_exit_failure                 GET_NOREL_GLOBAL(obstack_exit_failure)
#define __LOCAL_obstack_alloc_failed_handler GET_NOREL_GLOBAL(obstack_alloc_failed_handler)
#define __LOCAL_obstack_exit_failure         GET_NOREL_GLOBAL(obstack_exit_failure)


/* <libiberty.h> */
#undef libiberty_concat_ptr
#undef __LOCAL_libiberty_concat_ptr
DECLARE_NOREL_GLOBAL_META(char *, libiberty_concat_ptr);
#define libiberty_concat_ptr         GET_NOREL_GLOBAL(libiberty_concat_ptr)
#define __LOCAL_libiberty_concat_ptr GET_NOREL_GLOBAL(libiberty_concat_ptr)


/* <sys/single_threaded.h> */
#undef __libc_single_threaded
DECLARE_NOREL_GLOBAL_META(char, __libc_single_threaded);
#define __libc_single_threaded GET_NOREL_GLOBAL(__libc_single_threaded)


/* <wchar.h> */
#undef _mb_shift
DECLARE_NOREL_GLOBAL_META(struct __mbstate, _mb_shift);
#define _mb_shift GET_NOREL_GLOBAL(_mb_shift)


/* <printf.h> */
#undef __printf_function_table
#undef __printf_arginfo_table
DECLARE_NOREL_GLOBAL_META(__printf_function **, __printf_function_table);
DECLARE_NOREL_GLOBAL_META(__printf_arginfo_size_function **, __printf_arginfo_table);
#define __printf_function_table GET_NOREL_GLOBAL(__printf_function_table)
#define __printf_arginfo_table  GET_NOREL_GLOBAL(__printf_arginfo_table)


/* Misc... */
#undef __libc_enable_secure
#undef __LOCAL___libc_enable_secure
DECLARE_NOREL_GLOBAL_META(int, __libc_enable_secure);
#define __libc_enable_secure         GET_NOREL_GLOBAL(__libc_enable_secure)
#define __LOCAL___libc_enable_secure GET_NOREL_GLOBAL(__libc_enable_secure)

DECL_END
#endif /* !__KERNEL__ */
#endif /* __CC__ */

#endif /* !GUARD_LIBC_LIBC_GLOBALS_H */
