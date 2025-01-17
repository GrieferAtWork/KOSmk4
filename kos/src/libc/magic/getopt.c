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
%(c_prefix){
/* (#) Portability: Cygwin        (/newlib/libc/include/getopt.h) */
/* (#) Portability: DragonFly BSD (/include/getopt.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/getopt.h) */
/* (#) Portability: FreeBSD       (/include/getopt.h) */
/* (#) Portability: GNU C Library (/posix/getopt.h) */
/* (#) Portability: GNU Hurd      (/usr/include/getopt.h) */
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
%[default:section(".text.crt{|.dos}.application.getopt")]

%(auto_source){
#include "../libc/globals.h"
}

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%[insert:prefix(
#include <bits/crt/getopt.h>
)]%{

__SYSDECL_BEGIN

/* Possible values for `struct option::has_arg' */
#if !defined(no_argument) && defined(__no_argument)
#define no_argument       __no_argument       /* Option does not take an argument */
#endif /* !no_argument && __no_argument */
#if !defined(required_argument) && defined(__required_argument)
#define required_argument __required_argument /* Option requires an argument to be present */
#endif /* !required_argument && __required_argument */
#if !defined(optional_argument) && defined(__optional_argument)
#define optional_argument __optional_argument /* Option accepts an optional argument. */
#endif /* !optional_argument && __optional_argument */


#ifdef __CC__

/* >> optarg(3)
 * Set to the argument of the option returned by `getopt(3)' (and friends).
 * When returning an option that doesn't take an argument, `optarg' is  set
 * to `NULL'.
 *
 * Pre-initialized to `NULL' */
#ifndef optarg
#ifdef __LOCAL_optarg
#define optarg __LOCAL_optarg
#elif defined(__CRT_HAVE_optarg)
__CSDECLARE(,char *,optarg)
#define optarg optarg
#endif /* ... */
#endif /* !optarg */

/* >> optind(3)
 * Index of the next `argv'-element that `getopt(3)' (and friends) should parse.
 * In order for parsing to  start over, this should be  set to `1'. In order  to
 * fully re-initialize the getopt-parser, it should be set to `0' (in which case
 * libc will re-load flags from `optstring[0]', and `$POSIXLY_CORRECT').
 *
 * Once all arguments have been processed, `getopt(3)' returns `-1', and `optind'
 * is set to the value of the first non-argument argv-element (when all  elements
 * of `argv' are arguments, it is set to `argc')
 *
 * Pre-initialized to `1' */
#ifndef optind
#ifdef __LOCAL_optind
#define optind __LOCAL_optind
#elif defined(__CRT_HAVE_optind)
__CSDECLARE(,int,optind)
#define optind optind
#endif /* ... */
#endif /* !optind */

/* >> opterr(3)
 * When non-zero, `getopt(3)' will print error messages to `stderr', unless the
 * first character of `optstring' is `:'.  Setting this global variable to  `0'
 * will suppress error messages being  printed, allowing the application to  do
 * its own error-handling without libc doing anything extra.
 *
 * Pre-initialized to `1' */
#ifndef opterr
#ifdef __LOCAL_opterr
#define opterr __LOCAL_opterr
#elif defined(__CRT_HAVE_opterr)
__CSDECLARE(,int,opterr)
#define opterr opterr
#endif /* ... */
#endif /* !opterr */

/* >> optopt(3)
 * Filled in by `getopt(3)' (and friends) with the character-code of a malformed
 * option when one is encountered (this is done alongside an error being printed
 * to `stderr' (but see `opterr'), and `?' being returned by `getopt(3)').
 *
 * In the case of long options (s.a. `getopt_long(3)'), a malformed long option
 * results in that option's `struct option::val' being written to this  global.
 *
 * Pre-initialized to `(unsigned char)'?'' */
#ifndef optopt
#ifdef __LOCAL_optopt
#define optopt __LOCAL_optopt
#elif defined(__CRT_HAVE_optopt)
__CSDECLARE(,int,optopt)
#define optopt optopt
#endif /* ... */
#endif /* !optopt */

#ifdef __USE_NETBSD
/* >> optreset(3)
 * When set to non-zero, the next call to `getopt(3)' will reset the internal
 * parser. The resulting behavior is the same as when `optind' is set to `0'.
 * Once the reset is done, this variable is set to `0' again.
 *
 * Pre-initialized to `0' */
#ifndef optreset
#ifdef __LOCAL_optreset
#define optreset __LOCAL_optreset
#elif defined(__CRT_HAVE_optreset)
__CSDECLARE(,int,optreset)
#define optreset optreset
#endif /* ... */
#endif /* !optreset */
#endif /* __USE_NETBSD */

}

%(auto_source){
#ifndef __KERNEL__
#undef optarg
#undef optind
#undef opterr
#undef optopt
#undef optreset
INTDEF char *libc_optarg;
INTDEF int libc_optind;
INTDEF int libc_opterr;
INTDEF int libc_optopt;
INTDEF int libc_optreset;
INTERN ATTR_SECTION(".data.crt.application.getopt") char *libc_optarg = NULL;
INTERN ATTR_SECTION(".data.crt.application.getopt") int libc_optind = 1;
INTERN ATTR_SECTION(".data.crt.application.getopt") int libc_opterr = 1;
INTERN ATTR_SECTION(".data.crt.application.getopt") int libc_optopt = '?';
INTERN ATTR_SECTION(".data.crt.application.getopt") int libc_optreset = 0;
DEFINE_PUBLIC_ALIAS(optarg, libc_optarg);
DEFINE_PUBLIC_ALIAS(optind, libc_optind);
DEFINE_PUBLIC_ALIAS(opterr, libc_opterr);
DEFINE_PUBLIC_ALIAS(optopt, libc_optopt);
DEFINE_PUBLIC_ALIAS(optreset, libc_optreset);
#define optarg   GET_NOREL_GLOBAL(optarg)
#define optind   GET_NOREL_GLOBAL(optind)
#define opterr   GET_NOREL_GLOBAL(opterr)
#define optopt   GET_NOREL_GLOBAL(optopt)
#define optreset GET_NOREL_GLOBAL(optreset)
#endif /* !__KERNEL__ */
}


@@Back-bone driver for `getopt(3)'
@@@param: flags: Set of:
@@  - 0x0001: Long options may be written with a single leading "-"
@@  - 0x0002: Force posix behavior (set by `__posix_getopt')
[[static, wunused]]
[[decl_include("<bits/crt/getopt.h>")]]
[[requires_include("<libc/template/getopt.h>")]]
[[requires(defined(__LOCAL_optarg) && defined(__LOCAL_optind))]]
[[impl_include("<hybrid/typecore.h>")]]
[[impl_include("<bits/crt/getopt.h>")]]
[[impl_include("<libc/template/stdstreams.h>")]]
[[impl_include("<libc/template/getopt.h>")]]
[[impl_include("<parts/malloca.h>")]]
int getopt_impl(unsigned int argc,
                [[nonnull]] char const *argv[],
                [[nonnull]] char const *optstring,
                [[nullable]] struct option const *longopts,
                [[nullable]] unsigned int *longindex,
                unsigned int flags) {

	/* True if getopt has been initialized. */
@@pp_ifdef __BUILDING_LIBC@@
	ATTR_SECTION(".data.crt.application.getopt")
@@pp_endif@@
	static bool getopt_initialized = false;

	/* 0: permute-argv       (permute non-options to the back of `argv')
	 * 1: optstring[0]=='-'  (yield non-options via `optarg' and `return == 1')
	 * 2: optstring[1]=='+'  (stop parsing on the first non-option argument) */
@@pp_ifdef __BUILDING_LIBC@@
	ATTR_SECTION(".data.crt.application.getopt")
@@pp_endif@@
	static uint8_t getopt_parsemode = 0;

	/* Pointer to the  next character in  `argv[optind]' that hasn't  been
	 * parsed, yet (used for arguments containing multiple short-options).
	 *
	 * Points to an empty string if no further short options can be loaded. */
@@pp_ifdef __BUILDING_LIBC@@
	ATTR_SECTION(".data.crt.application.getopt")
@@pp_endif@@
	static char const *getopt_nextchar = NULL;

	/* Pointers-to-globals */
	unsigned int *p_optind = (unsigned int *)&__LOCAL_optind;
	char const  **p_optarg = (char const **)&__LOCAL_optarg;

	/* Current argument */
	char const *arg;
	char const *longopt_prefix;

	/*syslog(LOG_DEBUG, "getopt(%d, [", argc);
	for (unsigned int i = 0; i < argc; ++i)
		syslog(LOG_DEBUG, "%s%q", i ? ", " : "", argv[i]);
	syslog(LOG_DEBUG, "], %q, flags: %#x) [getopt_parsemode: %u, getopt_nextchar: %q, optind: %u]\n",
	       optstring, flags, (unsigned int)getopt_parsemode, getopt_nextchar, *p_optind);*/

	/* (re-)initialize getopt parser configuration on first use (or when `optind == 0'). */
	if (!getopt_initialized || *p_optind == 0
@@pp_ifdef __LOCAL_optreset@@
	    || __LOCAL_optreset
@@pp_endif@@
	    ) {
@@pp_ifdef __LOCAL_optreset@@
		__LOCAL_optreset = 0;
@@pp_endif@@
		if (*p_optind == 0)
			*p_optind = 1;
		getopt_nextchar    = "";
		getopt_initialized = true;

		/* Figure out which parsing mode to use. */
		if (*optstring == '-') {
			getopt_parsemode = 1;
			++optstring;
		} else if (*optstring == '+') {
			getopt_parsemode = 2;
			++optstring;
		} else if ((flags & 2)
@@pp_if $has_function(getenv)@@
		           || getenv("POSIXLY_CORRECT") != NULL
@@pp_endif@@
		           ) {
			getopt_parsemode = 2;
		} else {
			getopt_parsemode = 0;
		}
	} else {
		if (*optstring == '-' || *optstring == '+')
			++optstring;
	}

	/* Default: no argument (if appropriate, this gets overwritten later) */
	*p_optarg = NULL;

	/* Check if a short-option-group is currently in progress. */
	if (*getopt_nextchar != '\0') {
		/* Parse the next character from a multi-char short option. */
		char optch;
		char const *optspec_ptr;
parse_short_option_from_getopt_nextchar:
		optch = *getopt_nextchar++;
		if unlikely(optch == ':' || optch == ';') {
err_bad_getopt_nextchar:
@@pp_if $has_function(fprintf) && defined(__LOCAL_stderr)@@
			if (optstring[0] != ':'
@@pp_ifdef __LOCAL_opterr@@
			    && __LOCAL_opterr
@@pp_endif@@
			    ) {
				fprintf(stderr, "%s: invalid option -- '%c'\n", argv[0], optch);
			}
@@pp_endif@@
@@pp_ifdef __LOCAL_optopt@@
			__LOCAL_optopt = (unsigned char)optch;
@@pp_endif@@
			getopt_nextchar = "";
			return '?';
		}
		optspec_ptr = strchr(optstring, optch);
		if unlikely(optspec_ptr == NULL)
			goto err_bad_getopt_nextchar;
		if (optch == 'W' && optspec_ptr[1] == ';' && longopts != NULL) {
			/* Special case: `-Wfoo' and `-W foo' behave like "--foo" */
			if (*getopt_nextchar != '\0') {
				arg = getopt_nextchar;
				++(*p_optind);
			} else {
				++(*p_optind); /* consume option-argument */
				if unlikely(*p_optind >= argc)
					goto err_optch_requires_argument;
				arg = argv[(*p_optind)++]; /* consume argument operand */
			}
			longopt_prefix = "-W ";
			goto do_arg_long_option;
		}

		/* Check if this option takes an argument. */
		if (optspec_ptr[1] == ':') {
			if (optspec_ptr[2] == ':') {
				/* Special case: optional short-argument (only allowed for something like "-ofile.txt") */
				if (*getopt_nextchar != '\0') {
					*p_optarg = getopt_nextchar;
					++(*p_optind);
				}
			} else {
				if (*getopt_nextchar != '\0') {
					/* Option argument is next remainder of current argument */
					*p_optarg = getopt_nextchar;
					++(*p_optind);
				} else {
					/* Option argument is next argv-argument */
					++(*p_optind); /* consume option-argument */
					if unlikely(*p_optind >= argc)
						goto err_optch_requires_argument;
					*p_optarg = argv[(*p_optind)++]; /* consume argument operand */
				}
			}
			/* Mark short-option-group as being empty now. */
			getopt_nextchar = "";
		} else {
			if (*getopt_nextchar == '\0')
				++(*p_optind); /* End-of-options-group-argument */
		}
		return (unsigned char)optch;

err_optch_requires_argument:
@@pp_if $has_function(fprintf) && defined(__LOCAL_stderr)@@
		if (optstring[0] != ':'
@@pp_ifdef __LOCAL_opterr@@
		    && __LOCAL_opterr
@@pp_endif@@
		    ) {
			fprintf(stderr, "%s: option requires an argument -- '%c'\n", argv[0], optch);
		}
@@pp_endif@@
@@pp_ifdef __LOCAL_optopt@@
		__LOCAL_optopt = (unsigned char)optch;
@@pp_endif@@
		goto err_return_col_or_qmark;
	}

	/* No short-option-group in progress -- load the next argument from argv. */
	if (*p_optind >= argc)
		return -1; /* No more options... */

load_arg_from__ind__p_optind:
	arg = argv[*p_optind];
#define GETOPT_IS_NONOPTION_ARGUMENT(arg) ((arg)[0] != '-' || (arg)[1] == '\0')
	if (GETOPT_IS_NONOPTION_ARGUMENT(arg)) {
		unsigned int i, nonoption_start, nonoption_end, nonoption_insert;
		/* Non-option argument encountered. */
		if (getopt_parsemode == 2)
			return -1; /* stop parsing on the first non-option argument */
		if (getopt_parsemode == 1) {
			*p_optarg = arg;
			++(*p_optind);
			return 1;
		}
		/* Check if there are only non-option arguments from on out. */
		for (i = *p_optind + 1; i < argc; ++i) {
			arg = argv[i];
			if (!GETOPT_IS_NONOPTION_ARGUMENT(arg))
				goto not_already_permuted;
		}
		/* There are only non-option arguments remaining, so we're done! */
		return -1;
not_already_permuted:
		/* Permutate `argv' to move all non-option arguments to the end,
		 * or immediately  after  the  "--" argument  (if  it's  there). */
		nonoption_start  = *p_optind;
		nonoption_end    = nonoption_start;
		nonoption_insert = argc;
		while (nonoption_end < argc) {
			if (strcmp(argv[nonoption_end], "--") == 0) {
				nonoption_insert = nonoption_end + 1;
				break;
			}
			++nonoption_end;
		}

		/* Move shift all non-option arguments in `[nonoption_start,nonoption_end)'
		 * such  that they  all appear  at (what  is currently) `nonoption_insert'. */
		i = nonoption_end;
		while (i > nonoption_start) {
			--i;
			arg = argv[i];
			if (GETOPT_IS_NONOPTION_ARGUMENT(arg)) {
				--nonoption_insert;
				memmovedownc(&argv[i],
				             &argv[i + 1],
				             nonoption_insert - i,
				             sizeof(char const *));
				argv[nonoption_insert] = arg;
			}
		}
		goto load_arg_from__ind__p_optind;
	}
#undef GETOPT_IS_NONOPTION_ARGUMENT

	/* Got an option argument in `arg = argv[*p_optind]'. */
	++arg; /* Skip leading '-' */

	if (arg[0] == '-' && arg[1] == '\0') {
		/* Special case: "--" */
		++(*p_optind); /* Consume "--" */
		return -1; /* No more options... (rest of argv are just normal arguments) */
	}

	/* Check for long options. */
	if (longopts) {
		struct option const *longopt;
		size_t optname_len;
		if (*arg == '-') {
			/* "--" always indicates a long option */
			++arg;
			longopt_prefix = "--";
		} else {
			/* When `getopt_long_only(3)' was used, we also accept "-" for long options. */
			if (!(flags & 0x0001))
				goto not_a_long_option;
			if (arg[1] == '\0')
				goto not_a_long_option;
			if (arg[2] == '\0' && strchr(optstring, arg[1]) != NULL)
				goto not_a_long_option;
			longopt_prefix = "-";
		}
do_arg_long_option:

		/* Figure out the length of the long option name in `arg' */
		for (optname_len = 0; arg[optname_len] != '\0' &&
		                      arg[optname_len] != '=';)
			++optname_len;

		/* Check if there is a long option matching the given name. */
		for (longopt = longopts;; ++longopt) {
			if (longopt->@name@ == NULL) {
				byte_t *ambig_set;
				struct option const *candidate;

				/* long options are special, in that (so-long as it's not ambiguous),
				 * you're allowed to  specify only  part of the  long option's  name:
				 * $ ls --almo
				 * Works, and behaves the same as:
				 * $ ls --almost-all */
				ambig_set = NULL;
				candidate = NULL;
				for (longopt = longopts; longopt->@name@ != NULL; ++longopt) {
					if (strncmp(longopt->@name@, arg, optname_len) != 0) /* Check for starts-with */
						continue;
					if (candidate == NULL) {
						candidate = longopt;
					} else {
						size_t longopt_id;
@@pp_ifdef __malloca_mayfail@@
						if (ambig_set == (byte_t *)-1)
							continue; /* Failed to allocate set of candidates. */
@@pp_endif@@
						if (ambig_set == NULL) {
							size_t num_options;
							num_options = (size_t)(longopt - longopts) + 1;
							while (longopts[num_options].@name@ != NULL)
								++num_options;
							num_options += (__CHAR_BIT__ - 1);
							num_options /= __CHAR_BIT__;
							ambig_set = (byte_t *)__malloca(num_options);
@@pp_ifdef __malloca_mayfail@@
							if (ambig_set == NULL) {
								/* Failed to allocate set of candidates. */
								ambig_set = (byte_t *)-1;
								continue;
							}
@@pp_endif@@
							bzero(ambig_set, num_options);
							longopt_id = (size_t)(candidate - longopts);
							ambig_set[longopt_id / __CHAR_BIT__] |= (byte_t)1 << (longopt_id % __CHAR_BIT__);
						}
						longopt_id = (size_t)(longopt - longopts);
						ambig_set[longopt_id / __CHAR_BIT__] |= (byte_t)1 << (longopt_id % __CHAR_BIT__);
					}
				}
				if (ambig_set != NULL) {
@@pp_ifdef __malloca_mayfail@@
					if (ambig_set == (byte_t *)-1) {
						/* Error: ambiguous long option */
@@pp_if $has_function(fprintf) && defined(__LOCAL_stderr)@@
						if (optstring[0] != ':'
@@pp_ifdef __LOCAL_opterr@@
						    && __LOCAL_opterr
@@pp_endif@@
						    ) {
							fprintf(stderr, "%s: option `%s%s' is ambiguous\n",
							        argv[0], longopt_prefix, arg);
						}
@@pp_endif@@
					} else
@@pp_endif@@
					{
						/* Error: ambiguous long option */
@@pp_if $has_function(fprintf) && defined(__LOCAL_stderr)@@
						if (optstring[0] != ':'
@@pp_ifdef __LOCAL_opterr@@
						    && __LOCAL_opterr
@@pp_endif@@
						    ) {
							size_t longopt_id;
							fprintf(stderr, "%s: option `%s%s' is ambiguous; possibilities:",
							        argv[0], longopt_prefix, arg);
							for (longopt_id = 0; longopts[longopt_id].@name@; ++longopt_id) {
								if (!(ambig_set[longopt_id / __CHAR_BIT__] & (byte_t)1 << (longopt_id % __CHAR_BIT__)))
									continue;
								fprintf(stderr, " `%s%s'", longopt_prefix, longopts[longopt_id].@name@);
							}
@@pp_if $has_function(fputc)@@
							fputc('\n', stderr);
@@pp_else@@
							fprintf(stderr, "\n");
@@pp_endif@@
						}
@@pp_endif@@
						__freea(ambig_set);
					}
					goto err_longopt_common;
				}
				if (candidate != NULL) {
					/* Only a single candidate exists -> that's the one we want to use! */
					longopt = candidate;
					goto do_use_longopt;
				}

				/* If we got here due to something like "-foo", then go to the normal handler instead. */
				if ((flags & 0x0001) && arg == &argv[*p_optind][1] && strchr(optstring, *arg) != NULL)
					goto not_a_long_option;

				/* Error: no such long option */
@@pp_if $has_function(fprintf) && defined(__LOCAL_stderr)@@
				if (optstring[0] != ':'
@@pp_ifdef __LOCAL_opterr@@
				    && __LOCAL_opterr
@@pp_endif@@
				    ) {
					fprintf(stderr, "%s: unrecognized option `%s%s'\n", argv[0], longopt_prefix, arg);
				}
@@pp_endif@@
err_longopt_common:
				++(*p_optind);
@@pp_ifdef __LOCAL_optopt@@
				__LOCAL_optopt = 0;
@@pp_endif@@
				return '?';
			}

			/* Check for exact match. */
			if (strcmpz(longopt->@name@, arg, optname_len) == 0)
				break; /* Found it! */
		}
do_use_longopt:

		/* We found the long-option, and its potential argument.
		 * Now to match the 2 against each other (and assert the
		 * presence or absence of an argument) */
		++(*p_optind); /* Consume the argument containing the long-option itself. */
		arg += optname_len; /* Jump to the '\0' or '=<arg>' */
		if (*arg == '=') {
			/* Long option has an argument in `argv' */
			++arg;
			if (longopt->@has_arg@ != __no_argument) {
				*p_optarg = arg;
			} else {
@@pp_if $has_function(fprintf) && defined(__LOCAL_stderr)@@
				if (optstring[0] != ':'
@@pp_ifdef __LOCAL_opterr@@
				    && __LOCAL_opterr
@@pp_endif@@
				    ) {
					fprintf(stderr, "%s: option `%s%s' doesn't allow an argument\n",
					        argv[0], longopt_prefix, longopt->@name@);
				}
@@pp_endif@@
@@pp_ifdef __LOCAL_optopt@@
				__LOCAL_optopt = longopt->@val@;
@@pp_endif@@
				return '?';
			}
		} else if (longopt->@has_arg@ == __required_argument) {
			/* Must take the argument from `argv[*p_optind]' */
			if (*p_optind >= argc) {
@@pp_if $has_function(fprintf) && defined(__LOCAL_stderr)@@
				if (optstring[0] != ':'
@@pp_ifdef __LOCAL_opterr@@
				    && __LOCAL_opterr
@@pp_endif@@
				    ) {
					fprintf(stderr, "%s: option `%s%s' requires an argument\n",
					        argv[0], longopt_prefix, longopt->@name@);
				}
@@pp_endif@@
@@pp_ifdef __LOCAL_optopt@@
				__LOCAL_optopt = longopt->@val@;
@@pp_endif@@
				goto err_return_col_or_qmark;
			}
			*p_optarg = argv[(*p_optind)++];
		}
		if (longindex != NULL)
			*longindex = (unsigned int)(size_t)(longopt - longopts);
		if (longopt->@flag@ != NULL) {
			*longopt->@flag@ = longopt->@val@;
			return 0;
		}
		return longopt->@val@;
	}

	/* It's not a long option, so it _has_ to be a short option! */
not_a_long_option:
	getopt_nextchar = arg;
	goto parse_short_option_from_getopt_nextchar;
err_return_col_or_qmark:
	return optstring[0] == ':' ? ':' : '?';
}



@@>> getopt(3), getopt_long(3), getopt_long_only(3)
@@Parse options from arguments, as passed to `main()', and specified by `optstring'.
@@Arguments in `argv' appear in one of the following forms:
@@ - "-x":        Returns "x"                      (assuming `optstring' contains "x")
@@ - "-x -y":     Returns "x"                      (assuming `optstring' contains "x" and "y")
@@ - "-xyz":      Returns "x", "y", and then "z"   (assuming `optstring' contains "x", "y" and "z")
@@ - "-ofoo":     Returns "o", with `optarg="foo"' (assuming `optstring' contains "o:")
@@ - "-o", "foo": Returns "o", with `optarg="foo"' (assuming `optstring' contains "o:")
@@Long options (`getopt_long(3)'-only) appear in the following formats:
@@ - "--out":        Returns `longopts["out"].val'                      (assuming `longopts["out"].has_arg != required_argument')
@@ - "--out=foo":    Returns `longopts["out"].val', with `optarg="foo"' (assuming `longopts["out"].has_arg != no_argument')
@@ - "--out", "foo": Returns `longopts["out"].val', with `optarg="foo"' (assuming `longopts["out"].has_arg != no_argument')
@@When `getopt_long_only(3)' is used, long options may also be written with a single leading "-".
@@
@@This function interacts with the globals variables `optarg', `optind', `opterr' and `optopt'.
@@For  more information on  how these variables/are-used-by `getopt(3)'  (and friends), see the
@@documentation of the respective variable.
@@
@@The first character of `optstring' can be used to affect the behavior of this function:
@@ - '-': Each  non-option argument will be handled as though it was the argument of an option '\1'
@@        In other words: ["/bin/myapp", "-x", "foo", "bar"] (with `optstring="-x:"') would then be
@@        enumerated as  {[getopt:'x',optarg="foo"],  [getopt:1,optarg="bar"],  [getopt:-1]}.  Note
@@        that the special "--" argument still causes `getopt(3)' to return `-1' (with `optind' set
@@        to the 1 plus  the index of the  "--"-argument), even when this  option is used,  meaning
@@        that  when  using  this  option,  the  caller  must  handle  non-option  arguments  like:
@@        >> int opt;
@@        >> while ((opt = getopt(argc, argv, "-xy:z")) != -1) {
@@        >>     if (opt == 1)
@@        >>         handle_non_option_argument(optarg);
@@        >>     ...
@@        >> }
@@        >> while (optind < argc)
@@        >>     handle_non_option_argument(argv[optind++]);
@@        In this case, elements of `argv' are never permutated (and `argv' can be const).
@@ - '+': Stop parsing as soon as the first non-option argument is encountered. This is also the
@@        behavior when `optstring[0]' isn't a special character, and "$POSIXLY_CORRECT" is set,
@@        or `__posix_getopt(3)' was used.
@@        In this case, elements of `argv' are never permutated (and `argv' can be const).
@@ - ...: Default behavior (`optstring[0]'  isn't '-' or  '+'). In this  case, scanning of  `argv'
@@        does not stop at the first non-option argument, but only once the actual end is reached,
@@        or  an argument "--" is encountered. Once that is done, `getopt(3)' will return with the
@@        elements of `argv'  permutated such  that all  non-option arguments  appear (in  correct
@@        order) within `argv', starting at `argv[optind]'.
@@        e.g. Once option processing  is done, ["-afoo", "bar", "-c", "--", "-x"]  will
@@             result in `argv[optind...argc-1]' to be the array ["bar", "-x"] (assuming
@@             an `optstring' similar to "a:cx")
@@ - ':': Same as setting `opterr = 0' (may be combined with any of the other special flags by
@@        writing it _AFTER_ the other special flag; e.g. "+:xy:z")
@@
@@@param: argc: Number of arguments in `argv'
@@@param: argv: Argument vector from `main()' -- Shouldn't  actually be `const' here, since  this
@@              function may permute the  order of elements in  `argv' (to gather all  non-option
@@              arguments at the end), unless `optstring[0] == '+'', `__posix_getopt(3)' is used,
@@              or "$POSIXLY_CORRECT" is defined.
@@@param: optstring: [1..1] Options string (see above)
@@@param: longopts:  [0..1] Long options array (terminated by an all-NULL/0 element)
@@@param: longindex: [0..1] When non-NULL, set to the index of the matched long-option,
@@                          if  one was matched.  If none was (i.e.  a short option was
@@                          matched), the contents of this pointer are left  unchanged.
@@@return: 1 : The given `optstring' starts with '-', and a non-option argument `optarg' was encountered.
@@@return:'?': Error while processing options, or '?' appears in `optstring' (or as an `struct option::val')
@@             In the case of an error (and unless disabled by ':' or `opterr'), a message has already  been
@@             written to `stderr'.
@@@return: 0 : A long option was matched with `struct option::flag != NULL'.
@@@return: * : Either  a short option (return is that option's character-code), or a long-long (return is
@@             that option's `struct option::val', so-long as `struct option::flag == NULL') was matched.
@@@return: -1: Argument processing is done. Non-option arguments are in `argv[optind...argc-1]'
[[guard, wunused]]
[[requires_function(getopt_long)]]
[[export_alias("bsd_getopt")]] /* getopt with support for `optreset' (which ours already has) */
int getopt(int argc,
           [[nonnull]] char *const argv[],
           [[nonnull]] char const *optstring) {
	return getopt_long(argc, argv, optstring, NULL, NULL);
}

[[hidden, wunused]]
[[requires_function(getopt_impl)]]
int __posix_getopt(int argc,
                   [[nonnull]] char *const argv[],
                   [[nonnull]] char const *optstring) {
	return getopt_impl((unsigned int)argc, (char const **)argv, optstring, NULL, NULL, 2);
}

[[wunused, doc_alias("getopt")]]
[[decl_include("<bits/crt/getopt.h>")]]
[[requires_function(getopt_impl)]]
int getopt_long(int argc,
                [[nonnull]] char *const argv[],
                [[nonnull]] char const *optstring,
                [[nullable]] struct option const *longopts,
                [[nullable]] int *longindex) {
	return getopt_impl((unsigned int)argc, (char const **)argv, optstring,
	                   longopts, (unsigned int *)longindex, 0);
}

[[wunused, doc_alias("getopt")]]
[[decl_include("<bits/crt/getopt.h>")]]
[[requires_function(getopt_impl)]]
int getopt_long_only(int argc,
                     [[nonnull]] char *const argv[],
                     [[nonnull]] char const *optstring,
                     [[nullable]] struct option const *longopts,
                     [[nullable]] int *longindex) {
	return getopt_impl((unsigned int)argc, (char const **)argv, optstring,
	                   longopts, (unsigned int *)longindex, 1);
}


%{

#endif /* __CC__ */

__SYSDECL_END

}
