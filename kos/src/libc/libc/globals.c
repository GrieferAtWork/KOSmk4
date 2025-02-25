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
#ifndef GUARD_LIBC_LIBC_GLOBALS_C
#define GUARD_LIBC_LIBC_GLOBALS_C 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <kos/exec/idata.h>
#include <kos/types.h>

#include "globals.h"

DECL_BEGIN

/* Globals defined by libdl.so */
#undef __peb
#undef __argc
#undef __argv
#undef _pgmptr
#undef __progname
#undef environ
DEFINE_NOREL_GLOBAL_META(struct process_peb, __peb, ".crt.glibc.application.init");
DEFINE_NOREL_GLOBAL_META(int, __argc, ".crt.dos.application.init");
DEFINE_NOREL_GLOBAL_META(char **, __argv, ".crt.dos.application.init");
DEFINE_NOREL_GLOBAL_META(char *, _pgmptr, ".crt.dos.application.init");
DEFINE_NOREL_GLOBAL_META(char *, __progname, ".crt.errno.utility");
DEFINE_NOREL_GLOBAL_META(char **, environ, ".crt.fs.environ");
DEFINE_PUBLIC_IDATA(_dl_argc, libc_bind___argc, __SIZEOF_INT__);                      /* From Glibc 2.0.4 */
DEFINE_PUBLIC_IDATA(_dl_argv, libc_bind___argv, __SIZEOF_POINTER__);                  /* For Glibc-compat */
DEFINE_PUBLIC_IDATA(__libc_argc, libc_bind___argc, __SIZEOF_INT__);                   /* From Glibc 2.0.4 */
DEFINE_PUBLIC_IDATA(__libc_argv, libc_bind___argv, __SIZEOF_POINTER__);               /* From Glibc 2.0.4 */
DEFINE_PUBLIC_IDATA(__assert_program_name, libc_bind___progname, __SIZEOF_POINTER__); /* For libc4/5-compat */


/* <stdlib.h> */
#undef _wenviron
#undef suboptarg
DEFINE_NOREL_GLOBAL_META(char32_t **, _wenviron, ".crt.dos.wchar.fs.environ");
DEFINE_NOREL_GLOBAL_META(char *, suboptarg, ".crt.application.getopt");


/* <stdio.h> */
#undef stdin
#undef stdout
#undef stderr
#undef stdtty
DEFINE_NOREL_GLOBAL_META(FILE *, stdin, ".crt.FILE.locked.read.read");
DEFINE_NOREL_GLOBAL_META(FILE *, stdout, ".crt.FILE.locked.write.write");
DEFINE_NOREL_GLOBAL_META(FILE *, stderr, ".crt.FILE.locked.write.write");
DEFINE_NOREL_GLOBAL_META(FILE *, stdtty, ".crt.dos.conio");
/* HINT: The actual std* symbols are exported from "libc/compat.c", since  they
 *       require special initialization based on symbols that only exist within
 *       that specific source file */


/* <error.h> */
#undef error_message_count
#undef error_print_progname
#undef error_one_per_line
DEFINE_NOREL_GLOBAL_META(PERROR_PRINT_PROGNAME, error_print_progname, ".crt.error");
DEFINE_NOREL_GLOBAL_META(unsigned int, error_message_count, ".crt.error");
DEFINE_NOREL_GLOBAL_META(int, error_one_per_line, ".crt.error");
PUBLIC ATTR_SECTION(".bss.crt.error") PERROR_PRINT_PROGNAME error_print_progname = NULL;
PUBLIC ATTR_SECTION(".bss.crt.error") unsigned int error_message_count = 0;
PUBLIC ATTR_SECTION(".bss.crt.error") int error_one_per_line = 0;


/* <regex.h> */
#undef re_syntax_options
DEFINE_NOREL_GLOBAL_META(__reg_syntax_t, re_syntax_options, ".crt.utility.regex");


/* <regexp.h> */
#undef loc1
#undef loc2
#undef locs
DEFINE_NOREL_GLOBAL_META(char *, loc1, ".crt.compat.glibc.regex");
DEFINE_NOREL_GLOBAL_META(char *, loc2, ".crt.compat.glibc.regex");
/*DEFINE_NOREL_GLOBAL_META(char *, locs, ".crt.compat.glibc.regex");*/ /* Never used */


/* <time.h> */
#undef tzname
#undef timezone
#undef daylight
#undef _dstbias
#undef getdate_err
DEFINE_NOREL_GLOBAL_META(char *, tzname, ".crt.time.timezone");
DEFINE_NOREL_GLOBAL_META(longptr_t, timezone, ".crt.time.timezone");
DEFINE_NOREL_GLOBAL_META(int, daylight, ".crt.time.timezone");
DEFINE_NOREL_GLOBAL_META(__LONG32_TYPE__, _dstbias, ".crt.dos.time.timezone");
DEFINE_NOREL_GLOBAL_META(int, getdate_err, ".crt.time");


/* <getopt.h> */
#undef optarg
#undef optind
#undef opterr
#undef optopt
#undef optreset
DEFINE_NOREL_GLOBAL_META(char *, optarg, ".crt.application.getopt");
DEFINE_NOREL_GLOBAL_META(int, optind, ".crt.application.getopt");
DEFINE_NOREL_GLOBAL_META(int, opterr, ".crt.application.getopt");
DEFINE_NOREL_GLOBAL_META(int, optopt, ".crt.application.getopt");
DEFINE_NOREL_GLOBAL_META(int, optreset, ".crt.application.getopt");


/* <libintl.h> */
#undef _nl_msg_cat_cntr
DEFINE_NOREL_GLOBAL_META(int, _nl_msg_cat_cntr, ".crt.i18n");


/* <math.h> */
#undef signgam
DEFINE_NOREL_GLOBAL_META(int, signgam, ".crt.math.math");


/* <signal.h> */
#undef _sigintr
DEFINE_NOREL_GLOBAL_META(sigset_t, _sigintr, ".crt.sched.signal");


/* <mbctype.h> */
#undef _mbctype
#undef _mbcasemap
DEFINE_NOREL_GLOBAL_META(unsigned char, _mbctype, ".crt.dos.mbstring");
DEFINE_NOREL_GLOBAL_META(unsigned char, _mbcasemap, ".crt.dos.mbstring");


/* <obstack.h> */
#undef obstack_alloc_failed_handler
#undef obstack_exit_failure
DEFINE_NOREL_GLOBAL_META(POBSTACK_ALLOC_FAILED_HANDLER, obstack_alloc_failed_handler, ".crt.heap.obstack");
DEFINE_NOREL_GLOBAL_META(int, obstack_exit_failure, ".crt.heap.obstack");


/* <libiberty.h> */
#undef libiberty_concat_ptr
DEFINE_NOREL_GLOBAL_META(char *, libiberty_concat_ptr, ".crt.libiberty");


/* <sys/single_threaded.h> */
#undef __libc_single_threaded
DEFINE_NOREL_GLOBAL_META(char, __libc_single_threaded, ".crt.sched.pthread");


/* <wchar.h> */
#undef _mb_shift
DEFINE_NOREL_GLOBAL_META(struct __mbstate, _mb_shift, ".crt.compat.linux");


/* <printf.h> */
#undef __printf_function_table
#undef __printf_arginfo_table
DEFINE_NOREL_GLOBAL_META(__printf_function **, __printf_function_table, ".crt.compat.glibc.printf");
DEFINE_NOREL_GLOBAL_META(__printf_arginfo_size_function **, __printf_arginfo_table, ".crt.compat.glibc.printf");


/* <argp.h> */
#undef argp_program_version
#undef argp_program_version_hook
#undef argp_program_bug_address
#undef argp_err_exit_status
DEFINE_NOREL_GLOBAL_META(char const *, argp_program_version, ".crt.compat.glibc.string.argp");
DEFINE_NOREL_GLOBAL_META(__argp_program_version_hook_t, argp_program_version_hook, ".crt.compat.glibc.string.argp");
DEFINE_NOREL_GLOBAL_META(char const *, argp_program_bug_address, ".crt.compat.glibc.string.argp");
DEFINE_NOREL_GLOBAL_META(int, argp_err_exit_status, ".crt.compat.glibc.string.argp");


/* Misc... */
#undef __libc_enable_secure
DEFINE_NOREL_GLOBAL_META(int, __libc_enable_secure, ".crt.compat.glibc");


DECL_END

#endif /* !GUARD_LIBC_LIBC_GLOBALS_C */
