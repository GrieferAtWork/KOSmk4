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
#ifndef GUARD_LIBC_LIBC_GLOBALS_C
#define GUARD_LIBC_LIBC_GLOBALS_C 1

/* Keep this one the first */
#include "../api.h"
/**/

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


/* <stdlib.h> */
#undef _wenviron
DEFINE_NOREL_GLOBAL_META(char32_t **, _wenviron, ".crt.dos.wchar.fs.environ");


/* <stdio.h> */
#undef stdin
#undef stdout
#undef stderr
DEFINE_NOREL_GLOBAL_META(FILE *, stdin, ".crt.FILE.locked.read.read");
DEFINE_NOREL_GLOBAL_META(FILE *, stdout, ".crt.FILE.locked.write.write");
DEFINE_NOREL_GLOBAL_META(FILE *, stderr, ".crt.FILE.locked.write.write");
/* HINT: The actual std* symbols are  exported from "user/stdio.c", since  they
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
DEFINE_NOREL_GLOBAL_META(reg_syntax_t, re_syntax_options, ".crt.utility.regex");
PUBLIC ATTR_SECTION(".bss.crt.utility.regex") reg_syntax_t re_syntax_options = 0;


/* <time.h> */
#undef tzname
#undef timezone
#undef daylight
#undef __tzname
#undef __timezone
#undef __daylight
DEFINE_NOREL_GLOBAL_META(char *, tzname, ".crt.time.timezone");
DEFINE_NOREL_GLOBAL_META(longptr_t, timezone, ".crt.time.timezone");
DEFINE_NOREL_GLOBAL_META(int, daylight, ".crt.time.timezone");
PUBLIC ATTR_SECTION(".bss.crt.time.timezone") char *tzname[2]    = { NULL, NULL };
PUBLIC ATTR_SECTION(".bss.crt.time.timezone") longptr_t timezone = 0;
PUBLIC ATTR_SECTION(".bss.crt.time.timezone") int daylight       = 0;
DEFINE_PUBLIC_ALIAS(__tzname, tzname);
DEFINE_PUBLIC_ALIAS(__timezone, timezone);
DEFINE_PUBLIC_ALIAS(__daylight, daylight);


/* <getopt.h> */
#undef optarg
#undef optind
#undef opterr
#undef optopt
DEFINE_NOREL_GLOBAL_META(char *, optarg, ".crt.application.options");
DEFINE_NOREL_GLOBAL_META(int, optind, ".crt.application.options");
DEFINE_NOREL_GLOBAL_META(int, opterr, ".crt.application.options");
DEFINE_NOREL_GLOBAL_META(int, optopt, ".crt.application.options");
/* HINT: The getopt global variables are defined in "user/getopt.c"
 *       to prevent  redundancy of  section information  meta-data. */



DECL_END

#endif /* !GUARD_LIBC_LIBC_GLOBALS_C */
