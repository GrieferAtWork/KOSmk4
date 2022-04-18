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
%(c_prefix){
/* (#) Portability: Cygwin        (/newlib/libc/include/getopt.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/getopt.h) */
/* (#) Portability: FreeBSD       (/include/getopt.h) */
/* (#) Portability: GNU C Library (/posix/getopt.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/getopt.h) */
/* (#) Portability: NetBSD        (/include/getopt.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/getopt.h) */
/* (#) Portability: OpenBSD       (/include/getopt.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/getopt.h) */
/* (#) Portability: diet libc     (/include/getopt.h) */
/* (#) Portability: libbsd        (/include/bsd/getopt.h) */
/* (#) Portability: libc4/5       (/include/getopt.h) */
/* (#) Portability: libc6         (/include/getopt.h) */
/* (#) Portability: libcmini      (/include/getopt.h) */
/* (#) Portability: mintlib       (/include/getopt.h) */
/* (#) Portability: musl libc     (/include/getopt.h) */
/* (#) Portability: uClibc        (/include/getopt.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[define_partial_replacement(argc = ___argc)]
%[define_partial_replacement(argv = ___argv)]
%[define_partial_replacement(envp = ___envp)]
%[default:section(".text.crt{|.dos}.application.options")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%{

/* Documentation taken from Glibc /usr/include/getopt.h */
/* Declarations for getopt.
   Copyright (C) 1989-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

__SYSDECL_BEGIN

/* Names for the values of the `has_arg' field of `struct option'. */
/*[[[enum]]]*/
#ifdef __CC__
enum {
	no_argument       = 0,
	required_argument = 1,
	optional_argument = 2
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define no_argument       no_argument
#define required_argument required_argument
#define optional_argument optional_argument
#else /* __COMPILER_PREFERR_ENUMS */
#define no_argument       0
#define required_argument 1
#define optional_argument 2
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

#ifdef __CC__

}%[push_macro @undef { optarg optind opterr optopt option name has_arg flag val }]%{

#ifdef __CRT_HAVE_optarg
/* For   communication  from  `getopt'  to  the  caller.
 * When `getopt' finds an option that takes an argument,
 * the argument value is returned here.
 * Also,  when  `ordering'  is   RETURN_IN_ORDER,
 * each non-option argv-element is returned here. */
__LIBC char *optarg;
#endif /* __CRT_HAVE_optarg */

#ifdef __CRT_HAVE_optind
/* Index in `argv' of the next element to be scanned.
 * - This  is  used for  communication  to and  from  the caller
 *   and for communication between successive calls to `getopt'.
 * - On entry to `getopt', zero means this is the first call; initialize.
 * - When `getopt' returns -1, this is the index of the first of
 *   the non-option elements that the caller should itself scan.
 * - Otherwise, `optind'  communicates from  one call  to
 *   the next how much of `argv' has been scanned so far. */
__LIBC __INT32_TYPE__ optind;
#endif /* __CRT_HAVE_optind */

#ifdef __CRT_HAVE_opterr
/* Callers store zero here to inhibit the error message
 * `getopt'   prints    for    unrecognized    options. */
__LIBC __INT32_TYPE__ opterr;
#endif /* __CRT_HAVE_opterr */

#ifdef __CRT_HAVE_optopt
/* Set to an option character which was unrecognized. */
__LIBC __INT32_TYPE__ optopt;
#endif /* __CRT_HAVE_optopt */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("name")
#pragma push_macro("has_arg")
#pragma push_macro("flag")
#pragma push_macro("val")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef name
#undef has_arg
#undef flag
#undef val

/* Describe the long-named options requested by the application.
 *
 * The  LONG_OPTIONS argument  to getopt_long  or getopt_long_only  is a vector
 * of `struct option' terminated by an element containing a name which is zero.
 *
 * - The field `has_arg' is:
 *     - no_argument       (or 0) if the option does not take an argument,
 *     - required_argument (or 1) if the option requires an argument,
 *     - optional_argument (or 2) if the option takes an optional argument.
 * - If the field `flag' is not NULL, it points to a variable that is set
 *   to  the value given in the field `val' when the option is found, but
 *   left unchanged if the option is not found.
 * - To have a long-named option do something  other than set an `int' to  a
 *   compiled-in constant, such as set a value from `optarg', set the option
 *   's `flag' field to zero and its `val' field to a nonzero value
 *  (the equivalent single-letter option character, if there is one).
 *   For long options that have a zero `flag' field, `getopt' returns
 *   the contents of the `val' field. */
struct option {
	char const      *name;
	__INT32_TYPE__   has_arg;
	__INT32_TYPE__  *flag;
	__INT32_TYPE__   val;
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("val")
#pragma pop_macro("flag")
#pragma pop_macro("has_arg")
#pragma pop_macro("name")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

}

@@Return the option  character from  OPTS just read.  Return -1  when
@@there  are no  more options.  For unrecognized  options, or options
@@missing arguments, `optopt' is set to the option letter, and '?' is
@@returned.
@@- The OPTS string is a list of characters which are recognized option
@@  letters, optionally followed by colons, specifying that that letter
@@  takes an argument, to be placed in `optarg'.
@@- If a letter in OPTS is followed by two colons, its argument is
@@  optional. This  behavior  is  specific to  the  GNU  `getopt'.
@@- The  argument `--' causes  premature termination of argument
@@  scanning, explicitly telling `getopt' that there are no more
@@  options.
@@- If OPTS begins with `--', then non-option arguments are treated as
@@  arguments to the option '\0'. This behavior is specific to the GNU
@@  `getopt'
[[guard, wunused]]
int getopt(int argc, char *const argv[], char const *shortopts);

[[wunused, doc_alias("getopt")]]
int getopt_long(int argc, char *const argv[],
                char const *shortopts,
                struct option const *longopts,
                int *longind);

[[wunused, doc_alias("getopt")]]
int getopt_long_only(int argc, char *const argv[],
                     char const *shortopts,
                     struct option const *longopts,
                     int *longind);


%
%[pop_macro]%{

#endif /* __CC__ */

__SYSDECL_END

}
