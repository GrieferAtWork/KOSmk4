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
#ifndef GUARD_LIBC_USER_GETOPT_C
#define GUARD_LIBC_USER_GETOPT_C 1

#include "../api.h"
/**/

#include <alloca.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../libc/globals.h"
#include "getopt.h"

DECL_BEGIN

/* DISCLAIMER: The implementation in this file is derived from that of Glibc. */
/* TODO: Write KOS its own getopt(3) implementation (instead of copying one) */

/* Getopt for GNU.
   Copyright (C) 1987-2017 Free Software Foundation, Inc.
   This file is part of the GNU C Library and is also part of gnulib.
   Patches to this file should be submitted to both projects.

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



#define PERMUTE         0
#define RETURN_IN_ORDER 1
#define REQUIRE_ORDER   2

/* NOTE: We put everything into .data, even though some of it could go into .bss
 *       This is done  so that we  keep related data  more closely together  and
 *       possibly  reduce the number  of required #PFs  to load this sub-system. */
#define GETOPT_SECTION_DATA   ".data.crt.application.options"
#define GETOPT_SECTION_BSS    ".data.crt.application.options"
#define GETOPT_SECTION_TEXT   ".text.crt.application.options"
#define GETOPT_SECTION_RODATA ".rodata.crt.application.options"

DATDEF /**/ char *g_optarg ASMNAME("optarg");
DATDEF /*  */ int g_optind ASMNAME("optind");
DATDEF /*  */ int g_opterr ASMNAME("opterr");
DATDEF /*  */ int g_optopt ASMNAME("optopt");
PUBLIC ATTR_SECTION(GETOPT_SECTION_BSS) char *g_optarg = NULL;
PUBLIC ATTR_SECTION(GETOPT_SECTION_DATA) int g_optind  = 1;
PUBLIC ATTR_SECTION(GETOPT_SECTION_DATA) int g_opterr  = 1;
PUBLIC ATTR_SECTION(GETOPT_SECTION_DATA) int g_optopt  = '?';

PRIVATE ATTR_SECTION(GETOPT_SECTION_BSS) char *__nextchar   = NULL;
PRIVATE ATTR_SECTION(GETOPT_SECTION_BSS) int __first_nonopt = 0;
PRIVATE ATTR_SECTION(GETOPT_SECTION_BSS) int __last_nonopt  = 0;
PRIVATE ATTR_SECTION(GETOPT_SECTION_BSS) int __ordering     = 0;
PRIVATE ATTR_SECTION(GETOPT_SECTION_BSS) int __initialized  = 0;



#define DEFINE_STRING(name, str) \
	PRIVATE ATTR_SECTION(GETOPT_SECTION_RODATA) ATTR_ALIGNED(1) char const name[] = str
DEFINE_STRING(message_ambiguous_option, "%s: option `%s%s' is ambiguous\n");
DEFINE_STRING(message_ambiguous_option2, "%s: option `%s%s' is ambiguous; possibilities:");
DEFINE_STRING(message_ambiguous_option_variant, " `%s%s'");
DEFINE_STRING(message_unrecognized_option, "%s: unrecognized option `%s%s'\n");
DEFINE_STRING(message_option_takes_no_argument, "%s: option `%s%s' doesn't allow an argument\n");
DEFINE_STRING(message_requires_argument, "%s: option `%s%s' requires an argument\n");
DEFINE_STRING(message_requires_argument2, "%s: option requires an argument -- '%c'\n");
DEFINE_STRING(message_dash, "-");
DEFINE_STRING(message_dash_dash, "--");
DEFINE_STRING(message_dash_W_spc, "-W ");
DEFINE_STRING(message_invalid_option, "%s: invalid option -- '%c'\n");
DEFINE_STRING(message_POSIXLY_CORRECT, "POSIXLY_CORRECT");
#undef DEFINE_STRING


PRIVATE ATTR_SECTION(GETOPT_SECTION_TEXT)
void LIBCCALL exchange(char **argv) {
	int bottom = __first_nonopt;
	int middle = __last_nonopt;
	int top    = optind;
	char *temp;
	while (top > middle && middle > bottom) {
		if (top - middle > middle - bottom) {
			int i, len = middle - bottom;
			for (i = 0; i < len; ++i) {
				temp = argv[bottom + i];
				argv[bottom + i] = argv[top - (middle - bottom) + i];
				argv[top - (middle - bottom) + i] = temp;
			}
			top -= len;
		} else {
			int i, len = top - middle;
			for (i = 0; i < len; ++i) {
				temp             = argv[bottom + i];
				argv[bottom + i] = argv[middle + i];
				argv[middle + i] = temp;
			}
			bottom += len;
		}
	}
	__first_nonopt += (optind - __last_nonopt);
	__last_nonopt = optind;
}

PRIVATE ATTR_SECTION(GETOPT_SECTION_TEXT) int LIBCCALL
process_long_option(int argc, char **argv, char const *optstring,
                    struct option const *longopts, int *longind,
                    int long_only, int print_errors, char const *prefix) {
	char *nameend;
	size_t namelen;
	struct option const *p, *pfound = NULL;
	int n_options, option_index;
	for (nameend = __nextchar;
	     *nameend && *nameend != '=';
	     ++nameend)
		;
	namelen = nameend - __nextchar;
	for (p = longopts, n_options = 0; p->name; p++, n_options++) {
		if (strncmp(p->name, __nextchar, namelen) == 0 &&
		    namelen == strlen(p->name)) {
			pfound       = p;
			option_index = n_options;
			break;
		}
	}
	if (pfound == NULL) {
		unsigned char *ambig_set = NULL;
		int ambig_malloced       = 0;
		int ambig_fallback       = 0;
		int indfound             = -1;
		for (p = longopts, option_index = 0; p->name; p++, option_index++) {
			if (strncmp(p->name, __nextchar, namelen) == 0) {
				if (pfound == NULL) {
					pfound   = p;
					indfound = option_index;
				} else if (long_only ||
				           pfound->has_arg != p->has_arg ||
				           pfound->flag != p->flag ||
				           pfound->val != p->val) {
					if (!ambig_fallback) {
						if (!print_errors) {
							ambig_fallback = 1;
						} else if (!ambig_set) {
							if (n_options < 512) {
								ambig_set = (unsigned char *)alloca(n_options);
							} else if ((ambig_set = (unsigned char *)malloc(n_options)) == NULL) {
								ambig_fallback = 1;
							} else {
								ambig_malloced = 1;
							}
							if (ambig_set) {
								bzero(ambig_set, n_options);
								ambig_set[indfound] = 1;
							}
						}
						if (ambig_set)
							ambig_set[option_index] = 1;
					}
				}
			}
		}
		if (ambig_set || ambig_fallback) {
			if (print_errors) {
				if (ambig_fallback) {
					fprintf(stderr, message_ambiguous_option, argv[0], prefix, __nextchar);
				} else {
					flockfile(stderr);
					fprintf(stderr, message_ambiguous_option2, argv[0], prefix, __nextchar);
					for (option_index = 0; option_index < n_options; option_index++) {
						if (ambig_set[option_index])
							fprintf(stderr, message_ambiguous_option_variant, prefix, longopts[option_index].name);
					}
					fputc('\n', stderr);
					funlockfile(stderr);
				}
			}
			if (ambig_malloced)
				free(ambig_set);
			__nextchar += strlen(__nextchar);
			++optind;
			optopt = 0;
			return '?';
		}
		option_index = indfound;
	}
	if (pfound == NULL) {
		if (!long_only || argv[optind][1] == '-' ||
		    strchr(optstring, *__nextchar) == NULL) {
			if (print_errors)
				fprintf(stderr, message_unrecognized_option, argv[0], prefix, __nextchar);
			__nextchar = NULL;
			++optind;
			optopt = 0;
			return '?';
		}
		return -1;
	}
	++optind;
	__nextchar = NULL;
	if (*nameend) {
		if (pfound->has_arg) {
			optarg = nameend + 1;
		} else {
			if (print_errors)
				fprintf(stderr, message_option_takes_no_argument, argv[0], prefix, pfound->name);
			optopt = pfound->val;
			return '?';
		}
	} else if (pfound->has_arg == 1) {
		if (optind < argc) {
			optarg = argv[optind++];
		} else {
			if (print_errors)
				fprintf(stderr, message_requires_argument, argv[0], prefix, pfound->name);
			optopt = pfound->val;
			return optstring[0] == ':' ? ':' : '?';
		}
	}
	if (longind != NULL)
		*longind = option_index;
	if (pfound->flag) {
		*pfound->flag = pfound->val;
		return 0;
	}
	return pfound->val;
}


PRIVATE ATTR_SECTION(GETOPT_SECTION_TEXT) char const *LIBCCALL
_getopt_initialize(int UNUSED(argc), char **UNUSED(argv),
                   char const *optstring, int posixly_correct) {
	if (optind == 0)
		optind = 1;
	__first_nonopt = __last_nonopt = optind;
	__nextchar                     = NULL;
	if (optstring[0] == '-') {
		__ordering = RETURN_IN_ORDER;
		++optstring;
	} else if (optstring[0] == '+') {
		__ordering = REQUIRE_ORDER;
		++optstring;
	} else if (posixly_correct || !!getenv(message_POSIXLY_CORRECT)) {
		__ordering = REQUIRE_ORDER;
	} else {
		__ordering = PERMUTE;
	}
	__initialized = 1;
	return optstring;
}


PRIVATE ATTR_SECTION(GETOPT_SECTION_TEXT) int LIBCCALL
_getopt_internal_r(int argc, char **argv, char const *optstring,
                   struct option const *longopts, int *longind,
                   int long_only, int posixly_correct) {
	int print_errors = opterr;
	if (argc < 1)
		return -1;
	optarg = NULL;
	if (optind == 0 || !__initialized) {
		optstring = _getopt_initialize(argc, argv, optstring, posixly_correct);
	} else if (optstring[0] == '-' ||
	           optstring[0] == '+') {
		++optstring;
	}
	if (optstring[0] == ':')
		print_errors = 0;
#define NONOPTION_P (argv[optind][0] != '-' || argv[optind][1] == '\0')
	if (__nextchar == NULL || *__nextchar == '\0') {
		if (__last_nonopt > optind)
			__last_nonopt = optind;
		if (__first_nonopt > optind)
			__first_nonopt = optind;
		if (__ordering == PERMUTE) {
			if (__first_nonopt != __last_nonopt && __last_nonopt != optind) {
				exchange(argv);
			} else if (__last_nonopt != optind) {
				__first_nonopt = optind;
			}
			while (optind < argc && NONOPTION_P)
				++optind;
			__last_nonopt = optind;
		}
		if (optind != argc && strcmp(argv[optind], "--") == 0) {
			++optind;
			if (__first_nonopt != __last_nonopt && __last_nonopt != optind) {
				exchange(argv);
			} else if (__first_nonopt == __last_nonopt) {
				__first_nonopt = optind;
			}
			__last_nonopt = argc;
			optind        = argc;
		}
		if (optind == argc) {
			if (__first_nonopt != __last_nonopt)
				optind = __first_nonopt;
			return -1;
		}
		if (NONOPTION_P) {
			if (__ordering == REQUIRE_ORDER)
				return -1;
			optarg = argv[optind++];
			return 1;
		}
		if (longopts) {
			if (argv[optind][1] == '-') {
				__nextchar = argv[optind] + 2;
				return process_long_option(argc, argv, optstring, longopts,
				                           longind, long_only,
				                           print_errors,
				                           message_dash_dash);
			}
			if (long_only &&
			    (argv[optind][2] || !strchr(optstring, argv[optind][1]))) {
				int code;
				__nextchar = argv[optind] + 1;
				code = process_long_option(argc, argv, optstring, longopts,
				                           longind, long_only,
				                           print_errors,
				                           message_dash);
				if (code != -1)
					return code;
			}
		}
		__nextchar = argv[optind] + 1;
	}
	{
		char c = *__nextchar++;
		char const *temp = strchr(optstring, c);
		if (*__nextchar == '\0')
			++optind;
		if (temp == NULL || c == ':' || c == ';') {
			if (print_errors)
				fprintf(stderr, message_invalid_option, argv[0], c);
			optopt = (unsigned char)c;
			return '?';
		}
		if (temp[0] == 'W' && temp[1] == ';' && longopts != NULL) {
			if (*__nextchar != '\0') {
				optarg = __nextchar;
			} else if (optind == argc) {
				if (print_errors)
					fprintf(stderr, message_requires_argument2, argv[0], c);
				optopt = (unsigned char)c;
				c      = optstring[0] == ':' ? ':' : '?';
				return c;
			} else {
				optarg = argv[optind];
			}
			__nextchar = optarg;
			optarg     = NULL;
			return process_long_option(argc,
			                           argv,
			                           optstring,
			                           longopts,
			                           longind,
			                           /* long_only */ 0,
			                           print_errors,
			                           message_dash_W_spc);
		}
		if (temp[1] == ':') {
			if (temp[2] == ':') {
				if (*__nextchar != '\0') {
					optarg = __nextchar;
					optind++;
				} else {
					optarg = NULL;
				}
				__nextchar = NULL;
			} else {
				if (*__nextchar != '\0') {
					optarg = __nextchar;
					++optind;
				} else if (optind == argc) {
					if (print_errors)
						fprintf(stderr, message_requires_argument2, argv[0], c);
					optopt = (unsigned char)c;
					c      = optstring[0] == ':' ? ':' : '?';
				} else {
					optarg = argv[optind++];
				}
				__nextchar = NULL;
			}
		}
		return c;
	}
}


DEFINE_PUBLIC_ALIAS(__posix_getopt,libc___posix_getopt);
INTERN WUNUSED ATTR_SECTION(".text.crt.application.options") int
NOTHROW_NCX(LIBCCALL libc___posix_getopt)(int argc,
                                          char *const argv[],
                                          char const *shortopts) {
	return _getopt_internal_r(argc, (char **)argv, shortopts,
	                          NULL, NULL, 0, 1);
}



/*[[[head:libc_getopt,hash:CRC-32=0x9f540adc]]]*/
/* Return the option  character from  OPTS just read.  Return -1  when
 * there  are no  more options.  For unrecognized  options, or options
 * missing arguments, `optopt' is set to the option letter, and '?' is
 * returned.
 * - The OPTS string is a list of characters which are recognized option
 *   letters, optionally followed by colons, specifying that that letter
 *   takes an argument, to be placed in `optarg'.
 * - If a letter in OPTS is followed by two colons, its argument is
 *   optional. This  behavior  is  specific to  the  GNU  `getopt'.
 * - The  argument `--' causes  premature termination of argument
 *   scanning, explicitly telling `getopt' that there are no more
 *   options.
 * - If OPTS begins with `--', then non-option arguments are treated as
 *   arguments to the option '\0'. This behavior is specific to the GNU
 *   `getopt' */
INTERN ATTR_SECTION(".text.crt.application.options") WUNUSED int
NOTHROW_NCX(LIBCCALL libc_getopt)(int argc,
                                  char *const argv[],
                                  char const *shortopts)
/*[[[body:libc_getopt]]]*/
{
	return _getopt_internal_r(argc,
	                          (char **)argv,
	                          shortopts,
	                          NULL,
	                          NULL,
	                          0,
	                          0);
}
/*[[[end:libc_getopt]]]*/

/*[[[head:libc_getopt_long,hash:CRC-32=0x3e3f0d76]]]*/
/* Return the option  character from  OPTS just read.  Return -1  when
 * there  are no  more options.  For unrecognized  options, or options
 * missing arguments, `optopt' is set to the option letter, and '?' is
 * returned.
 * - The OPTS string is a list of characters which are recognized option
 *   letters, optionally followed by colons, specifying that that letter
 *   takes an argument, to be placed in `optarg'.
 * - If a letter in OPTS is followed by two colons, its argument is
 *   optional. This  behavior  is  specific to  the  GNU  `getopt'.
 * - The  argument `--' causes  premature termination of argument
 *   scanning, explicitly telling `getopt' that there are no more
 *   options.
 * - If OPTS begins with `--', then non-option arguments are treated as
 *   arguments to the option '\0'. This behavior is specific to the GNU
 *   `getopt' */
INTERN ATTR_SECTION(".text.crt.application.options") WUNUSED int
NOTHROW_NCX(LIBCCALL libc_getopt_long)(int argc,
                                       char *const argv[],
                                       char const *shortopts,
                                       struct option const *longopts,
                                       int *longind)
/*[[[body:libc_getopt_long]]]*/
{
	return _getopt_internal_r(argc,
	                          (char **)argv,
	                          shortopts,
	                          longopts,
	                          longind,
	                          0,
	                          0);
}
/*[[[end:libc_getopt_long]]]*/

/*[[[head:libc_getopt_long_only,hash:CRC-32=0xd1eb6c31]]]*/
/* Return the option  character from  OPTS just read.  Return -1  when
 * there  are no  more options.  For unrecognized  options, or options
 * missing arguments, `optopt' is set to the option letter, and '?' is
 * returned.
 * - The OPTS string is a list of characters which are recognized option
 *   letters, optionally followed by colons, specifying that that letter
 *   takes an argument, to be placed in `optarg'.
 * - If a letter in OPTS is followed by two colons, its argument is
 *   optional. This  behavior  is  specific to  the  GNU  `getopt'.
 * - The  argument `--' causes  premature termination of argument
 *   scanning, explicitly telling `getopt' that there are no more
 *   options.
 * - If OPTS begins with `--', then non-option arguments are treated as
 *   arguments to the option '\0'. This behavior is specific to the GNU
 *   `getopt' */
INTERN ATTR_SECTION(".text.crt.application.options") WUNUSED int
NOTHROW_NCX(LIBCCALL libc_getopt_long_only)(int argc,
                                            char *const argv[],
                                            char const *shortopts,
                                            struct option const *longopts,
                                            int *longind)
/*[[[body:libc_getopt_long_only]]]*/
{
	return _getopt_internal_r(argc,
	                          (char **)argv,
	                          shortopts,
	                          longopts,
	                          longind,
	                          1,
	                          0);
}
/*[[[end:libc_getopt_long_only]]]*/





/*[[[start:exports,hash:CRC-32=0xbacef226]]]*/
DEFINE_PUBLIC_ALIAS(getopt, libc_getopt);
DEFINE_PUBLIC_ALIAS(getopt_long, libc_getopt_long);
DEFINE_PUBLIC_ALIAS(getopt_long_only, libc_getopt_long_only);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_GETOPT_C */
