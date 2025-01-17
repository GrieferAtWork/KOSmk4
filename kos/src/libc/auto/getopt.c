/* HASH CRC-32:0xaa4e8e */
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
#ifndef GUARD_LIBC_AUTO_GETOPT_C
#define GUARD_LIBC_AUTO_GETOPT_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "getopt.h"
#include "../user/stdio.h"
#include "../user/stdlib.h"
#include "string.h"

DECL_BEGIN

#include "../libc/globals.h"
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
#ifndef __KERNEL__
#include <hybrid/typecore.h>
#include <bits/crt/getopt.h>
#include <libc/template/stdstreams.h>
#include <libc/template/getopt.h>
#include <parts/malloca.h>
/* Back-bone driver for `getopt(3)'
 * @param: flags: Set of:
 *   - 0x0001: Long options may be written with a single leading "-"
 *   - 0x0002: Force posix behavior (set by `__posix_getopt') */
INTERN ATTR_SECTION(".text.crt.application.getopt") WUNUSED NONNULL((2, 3)) int
NOTHROW_NCX(LIBCCALL libc_getopt_impl)(unsigned int argc,
                                       char const *argv[],
                                       char const *optstring,
                                       struct option const *longopts,
                                       unsigned int *longindex,
                                       unsigned int flags) {

	/* True if getopt has been initialized. */

	ATTR_SECTION(".data.crt.application.getopt")

	static bool getopt_initialized = false;

	/* 0: permute-argv       (permute non-options to the back of `argv')
	 * 1: optstring[0]=='-'  (yield non-options via `optarg' and `return == 1')
	 * 2: optstring[1]=='+'  (stop parsing on the first non-option argument) */

	ATTR_SECTION(".data.crt.application.getopt")

	static uint8_t getopt_parsemode = 0;

	/* Pointer to the  next character in  `argv[optind]' that hasn't  been
	 * parsed, yet (used for arguments containing multiple short-options).
	 *
	 * Points to an empty string if no further short options can be loaded. */

	ATTR_SECTION(".data.crt.application.getopt")

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
#ifdef __LOCAL_optreset
	    || __LOCAL_optreset
#endif /* __LOCAL_optreset */
	    ) {
#ifdef __LOCAL_optreset
		__LOCAL_optreset = 0;
#endif /* __LOCAL_optreset */
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

		           || libc_getenv("POSIXLY_CORRECT") != NULL

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

			if (optstring[0] != ':'
#ifdef __LOCAL_opterr
			    && __LOCAL_opterr
#endif /* __LOCAL_opterr */
			    ) {
				libc_fprintf(stderr, "%s: invalid option -- '%c'\n", argv[0], optch);
			}

#ifdef __LOCAL_optopt
			__LOCAL_optopt = (unsigned char)optch;
#endif /* __LOCAL_optopt */
			getopt_nextchar = "";
			return '?';
		}
		optspec_ptr = libc_strchr(optstring, optch);
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

		if (optstring[0] != ':'
#ifdef __LOCAL_opterr
		    && __LOCAL_opterr
#endif /* __LOCAL_opterr */
		    ) {
			libc_fprintf(stderr, "%s: option requires an argument -- '%c'\n", argv[0], optch);
		}

#ifdef __LOCAL_optopt
		__LOCAL_optopt = (unsigned char)optch;
#endif /* __LOCAL_optopt */
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
			if (libc_strcmp(argv[nonoption_end], "--") == 0) {
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
				libc_memmovedownc(&argv[i],
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
			if (arg[2] == '\0' && libc_strchr(optstring, arg[1]) != NULL)
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
			if (longopt->name == NULL) {
				byte_t *ambig_set;
				struct option const *candidate;

				/* long options are special, in that (so-long as it's not ambiguous),
				 * you're allowed to  specify only  part of the  long option's  name:
				 * $ ls --almo
				 * Works, and behaves the same as:
				 * $ ls --almost-all */
				ambig_set = NULL;
				candidate = NULL;
				for (longopt = longopts; longopt->name != NULL; ++longopt) {
					if (libc_strncmp(longopt->name, arg, optname_len) != 0) /* Check for starts-with */
						continue;
					if (candidate == NULL) {
						candidate = longopt;
					} else {
						size_t longopt_id;
#ifdef __malloca_mayfail
						if (ambig_set == (byte_t *)-1)
							continue; /* Failed to allocate set of candidates. */
#endif /* __malloca_mayfail */
						if (ambig_set == NULL) {
							size_t num_options;
							num_options = (size_t)(longopt - longopts) + 1;
							while (longopts[num_options].name != NULL)
								++num_options;
							num_options += (__CHAR_BIT__ - 1);
							num_options /= __CHAR_BIT__;
							ambig_set = (byte_t *)__malloca(num_options);
#ifdef __malloca_mayfail
							if (ambig_set == NULL) {
								/* Failed to allocate set of candidates. */
								ambig_set = (byte_t *)-1;
								continue;
							}
#endif /* __malloca_mayfail */
							libc_bzero(ambig_set, num_options);
							longopt_id = (size_t)(candidate - longopts);
							ambig_set[longopt_id / __CHAR_BIT__] |= (byte_t)1 << (longopt_id % __CHAR_BIT__);
						}
						longopt_id = (size_t)(longopt - longopts);
						ambig_set[longopt_id / __CHAR_BIT__] |= (byte_t)1 << (longopt_id % __CHAR_BIT__);
					}
				}
				if (ambig_set != NULL) {
#ifdef __malloca_mayfail
					if (ambig_set == (byte_t *)-1) {
						/* Error: ambiguous long option */

						if (optstring[0] != ':'
#ifdef __LOCAL_opterr
						    && __LOCAL_opterr
#endif /* __LOCAL_opterr */
						    ) {
							libc_fprintf(stderr, "%s: option `%s%s' is ambiguous\n",
							        argv[0], longopt_prefix, arg);
						}

					} else
#endif /* __malloca_mayfail */
					{
						/* Error: ambiguous long option */

						if (optstring[0] != ':'
#ifdef __LOCAL_opterr
						    && __LOCAL_opterr
#endif /* __LOCAL_opterr */
						    ) {
							size_t longopt_id;
							libc_fprintf(stderr, "%s: option `%s%s' is ambiguous; possibilities:",
							        argv[0], longopt_prefix, arg);
							for (longopt_id = 0; longopts[longopt_id].name; ++longopt_id) {
								if (!(ambig_set[longopt_id / __CHAR_BIT__] & (byte_t)1 << (longopt_id % __CHAR_BIT__)))
									continue;
								libc_fprintf(stderr, " `%s%s'", longopt_prefix, longopts[longopt_id].name);
							}

							libc_fputc('\n', stderr);



						}

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
				if ((flags & 0x0001) && arg == &argv[*p_optind][1] && libc_strchr(optstring, *arg) != NULL)
					goto not_a_long_option;

				/* Error: no such long option */

				if (optstring[0] != ':'
#ifdef __LOCAL_opterr
				    && __LOCAL_opterr
#endif /* __LOCAL_opterr */
				    ) {
					libc_fprintf(stderr, "%s: unrecognized option `%s%s'\n", argv[0], longopt_prefix, arg);
				}

err_longopt_common:
				++(*p_optind);
#ifdef __LOCAL_optopt
				__LOCAL_optopt = 0;
#endif /* __LOCAL_optopt */
				return '?';
			}

			/* Check for exact match. */
			if (libc_strcmpz(longopt->name, arg, optname_len) == 0)
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
			if (longopt->has_arg != __no_argument) {
				*p_optarg = arg;
			} else {

				if (optstring[0] != ':'
#ifdef __LOCAL_opterr
				    && __LOCAL_opterr
#endif /* __LOCAL_opterr */
				    ) {
					libc_fprintf(stderr, "%s: option `%s%s' doesn't allow an argument\n",
					        argv[0], longopt_prefix, longopt->name);
				}

#ifdef __LOCAL_optopt
				__LOCAL_optopt = longopt->val;
#endif /* __LOCAL_optopt */
				return '?';
			}
		} else if (longopt->has_arg == __required_argument) {
			/* Must take the argument from `argv[*p_optind]' */
			if (*p_optind >= argc) {

				if (optstring[0] != ':'
#ifdef __LOCAL_opterr
				    && __LOCAL_opterr
#endif /* __LOCAL_opterr */
				    ) {
					libc_fprintf(stderr, "%s: option `%s%s' requires an argument\n",
					        argv[0], longopt_prefix, longopt->name);
				}

#ifdef __LOCAL_optopt
				__LOCAL_optopt = longopt->val;
#endif /* __LOCAL_optopt */
				goto err_return_col_or_qmark;
			}
			*p_optarg = argv[(*p_optind)++];
		}
		if (longindex != NULL)
			*longindex = (unsigned int)(size_t)(longopt - longopts);
		if (longopt->flag != NULL) {
			*longopt->flag = longopt->val;
			return 0;
		}
		return longopt->val;
	}

	/* It's not a long option, so it _has_ to be a short option! */
not_a_long_option:
	getopt_nextchar = arg;
	goto parse_short_option_from_getopt_nextchar;
err_return_col_or_qmark:
	return optstring[0] == ':' ? ':' : '?';
}
/* >> getopt(3), getopt_long(3), getopt_long_only(3)
 * Parse options from arguments, as passed to `main()', and specified by `optstring'.
 * Arguments in `argv' appear in one of the following forms:
 *  - "-x":        Returns "x"                      (assuming `optstring' contains "x")
 *  - "-x -y":     Returns "x"                      (assuming `optstring' contains "x" and "y")
 *  - "-xyz":      Returns "x", "y", and then "z"   (assuming `optstring' contains "x", "y" and "z")
 *  - "-ofoo":     Returns "o", with `optarg="foo"' (assuming `optstring' contains "o:")
 *  - "-o", "foo": Returns "o", with `optarg="foo"' (assuming `optstring' contains "o:")
 * Long options (`getopt_long(3)'-only) appear in the following formats:
 *  - "--out":        Returns `longopts["out"].val'                      (assuming `longopts["out"].has_arg != required_argument')
 *  - "--out=foo":    Returns `longopts["out"].val', with `optarg="foo"' (assuming `longopts["out"].has_arg != no_argument')
 *  - "--out", "foo": Returns `longopts["out"].val', with `optarg="foo"' (assuming `longopts["out"].has_arg != no_argument')
 * When `getopt_long_only(3)' is used, long options may also be written with a single leading "-".
 *
 * This function interacts with the globals variables `optarg', `optind', `opterr' and `optopt'.
 * For  more information on  how these variables/are-used-by `getopt(3)'  (and friends), see the
 * documentation of the respective variable.
 *
 * The first character of `optstring' can be used to affect the behavior of this function:
 *  - '-': Each  non-option argument will be handled as though it was the argument of an option '\1'
 *         In other words: ["/bin/myapp", "-x", "foo", "bar"] (with `optstring="-x:"') would then be
 *         enumerated as  {[getopt:'x',optarg="foo"],  [getopt:1,optarg="bar"],  [getopt:-1]}.  Note
 *         that the special "--" argument still causes `getopt(3)' to return `-1' (with `optind' set
 *         to the 1 plus  the index of the  "--"-argument), even when this  option is used,  meaning
 *         that  when  using  this  option,  the  caller  must  handle  non-option  arguments  like:
 *         >> int opt;
 *         >> while ((opt = getopt(argc, argv, "-xy:z")) != -1) {
 *         >>     if (opt == 1)
 *         >>         handle_non_option_argument(optarg);
 *         >>     ...
 *         >> }
 *         >> while (optind < argc)
 *         >>     handle_non_option_argument(argv[optind++]);
 *         In this case, elements of `argv' are never permutated (and `argv' can be const).
 *  - '+': Stop parsing as soon as the first non-option argument is encountered. This is also the
 *         behavior when `optstring[0]' isn't a special character, and "$POSIXLY_CORRECT" is set,
 *         or `__posix_getopt(3)' was used.
 *         In this case, elements of `argv' are never permutated (and `argv' can be const).
 *  - ...: Default behavior (`optstring[0]'  isn't '-' or  '+'). In this  case, scanning of  `argv'
 *         does not stop at the first non-option argument, but only once the actual end is reached,
 *         or  an argument "--" is encountered. Once that is done, `getopt(3)' will return with the
 *         elements of `argv'  permutated such  that all  non-option arguments  appear (in  correct
 *         order) within `argv', starting at `argv[optind]'.
 *         e.g. Once option processing  is done, ["-afoo", "bar", "-c", "--", "-x"]  will
 *              result in `argv[optind...argc-1]' to be the array ["bar", "-x"] (assuming
 *              an `optstring' similar to "a:cx")
 *  - ':': Same as setting `opterr = 0' (may be combined with any of the other special flags by
 *         writing it _AFTER_ the other special flag; e.g. "+:xy:z")
 *
 * @param: argc: Number of arguments in `argv'
 * @param: argv: Argument vector from `main()' -- Shouldn't  actually be `const' here, since  this
 *               function may permute the  order of elements in  `argv' (to gather all  non-option
 *               arguments at the end), unless `optstring[0] == '+'', `__posix_getopt(3)' is used,
 *               or "$POSIXLY_CORRECT" is defined.
 * @param: optstring: [1..1] Options string (see above)
 * @param: longopts:  [0..1] Long options array (terminated by an all-NULL/0 element)
 * @param: longindex: [0..1] When non-NULL, set to the index of the matched long-option,
 *                           if  one was matched.  If none was (i.e.  a short option was
 *                           matched), the contents of this pointer are left  unchanged.
 * @return: 1 : The given `optstring' starts with '-', and a non-option argument `optarg' was encountered.
 * @return:'?': Error while processing options, or '?' appears in `optstring' (or as an `struct option::val')
 *              In the case of an error (and unless disabled by ':' or `opterr'), a message has already  been
 *              written to `stderr'.
 * @return: 0 : A long option was matched with `struct option::flag != NULL'.
 * @return: * : Either  a short option (return is that option's character-code), or a long-long (return is
 *              that option's `struct option::val', so-long as `struct option::flag == NULL') was matched.
 * @return: -1: Argument processing is done. Non-option arguments are in `argv[optind...argc-1]' */
INTERN ATTR_SECTION(".text.crt.application.getopt") WUNUSED NONNULL((2, 3)) int
NOTHROW_NCX(LIBCCALL libc_getopt)(int argc,
                                  char *const argv[],
                                  char const *optstring) {
	return libc_getopt_long(argc, argv, optstring, NULL, NULL);
}
INTERN ATTR_SECTION(".text.crt.application.getopt") WUNUSED NONNULL((2, 3)) int
NOTHROW_NCX(LIBCCALL libc___posix_getopt)(int argc,
                                          char *const argv[],
                                          char const *optstring) {
	return libc_getopt_impl((unsigned int)argc, (char const **)argv, optstring, NULL, NULL, 2);
}
/* >> getopt(3), getopt_long(3), getopt_long_only(3)
 * Parse options from arguments, as passed to `main()', and specified by `optstring'.
 * Arguments in `argv' appear in one of the following forms:
 *  - "-x":        Returns "x"                      (assuming `optstring' contains "x")
 *  - "-x -y":     Returns "x"                      (assuming `optstring' contains "x" and "y")
 *  - "-xyz":      Returns "x", "y", and then "z"   (assuming `optstring' contains "x", "y" and "z")
 *  - "-ofoo":     Returns "o", with `optarg="foo"' (assuming `optstring' contains "o:")
 *  - "-o", "foo": Returns "o", with `optarg="foo"' (assuming `optstring' contains "o:")
 * Long options (`getopt_long(3)'-only) appear in the following formats:
 *  - "--out":        Returns `longopts["out"].val'                      (assuming `longopts["out"].has_arg != required_argument')
 *  - "--out=foo":    Returns `longopts["out"].val', with `optarg="foo"' (assuming `longopts["out"].has_arg != no_argument')
 *  - "--out", "foo": Returns `longopts["out"].val', with `optarg="foo"' (assuming `longopts["out"].has_arg != no_argument')
 * When `getopt_long_only(3)' is used, long options may also be written with a single leading "-".
 *
 * This function interacts with the globals variables `optarg', `optind', `opterr' and `optopt'.
 * For  more information on  how these variables/are-used-by `getopt(3)'  (and friends), see the
 * documentation of the respective variable.
 *
 * The first character of `optstring' can be used to affect the behavior of this function:
 *  - '-': Each  non-option argument will be handled as though it was the argument of an option '\1'
 *         In other words: ["/bin/myapp", "-x", "foo", "bar"] (with `optstring="-x:"') would then be
 *         enumerated as  {[getopt:'x',optarg="foo"],  [getopt:1,optarg="bar"],  [getopt:-1]}.  Note
 *         that the special "--" argument still causes `getopt(3)' to return `-1' (with `optind' set
 *         to the 1 plus  the index of the  "--"-argument), even when this  option is used,  meaning
 *         that  when  using  this  option,  the  caller  must  handle  non-option  arguments  like:
 *         >> int opt;
 *         >> while ((opt = getopt(argc, argv, "-xy:z")) != -1) {
 *         >>     if (opt == 1)
 *         >>         handle_non_option_argument(optarg);
 *         >>     ...
 *         >> }
 *         >> while (optind < argc)
 *         >>     handle_non_option_argument(argv[optind++]);
 *         In this case, elements of `argv' are never permutated (and `argv' can be const).
 *  - '+': Stop parsing as soon as the first non-option argument is encountered. This is also the
 *         behavior when `optstring[0]' isn't a special character, and "$POSIXLY_CORRECT" is set,
 *         or `__posix_getopt(3)' was used.
 *         In this case, elements of `argv' are never permutated (and `argv' can be const).
 *  - ...: Default behavior (`optstring[0]'  isn't '-' or  '+'). In this  case, scanning of  `argv'
 *         does not stop at the first non-option argument, but only once the actual end is reached,
 *         or  an argument "--" is encountered. Once that is done, `getopt(3)' will return with the
 *         elements of `argv'  permutated such  that all  non-option arguments  appear (in  correct
 *         order) within `argv', starting at `argv[optind]'.
 *         e.g. Once option processing  is done, ["-afoo", "bar", "-c", "--", "-x"]  will
 *              result in `argv[optind...argc-1]' to be the array ["bar", "-x"] (assuming
 *              an `optstring' similar to "a:cx")
 *  - ':': Same as setting `opterr = 0' (may be combined with any of the other special flags by
 *         writing it _AFTER_ the other special flag; e.g. "+:xy:z")
 *
 * @param: argc: Number of arguments in `argv'
 * @param: argv: Argument vector from `main()' -- Shouldn't  actually be `const' here, since  this
 *               function may permute the  order of elements in  `argv' (to gather all  non-option
 *               arguments at the end), unless `optstring[0] == '+'', `__posix_getopt(3)' is used,
 *               or "$POSIXLY_CORRECT" is defined.
 * @param: optstring: [1..1] Options string (see above)
 * @param: longopts:  [0..1] Long options array (terminated by an all-NULL/0 element)
 * @param: longindex: [0..1] When non-NULL, set to the index of the matched long-option,
 *                           if  one was matched.  If none was (i.e.  a short option was
 *                           matched), the contents of this pointer are left  unchanged.
 * @return: 1 : The given `optstring' starts with '-', and a non-option argument `optarg' was encountered.
 * @return:'?': Error while processing options, or '?' appears in `optstring' (or as an `struct option::val')
 *              In the case of an error (and unless disabled by ':' or `opterr'), a message has already  been
 *              written to `stderr'.
 * @return: 0 : A long option was matched with `struct option::flag != NULL'.
 * @return: * : Either  a short option (return is that option's character-code), or a long-long (return is
 *              that option's `struct option::val', so-long as `struct option::flag == NULL') was matched.
 * @return: -1: Argument processing is done. Non-option arguments are in `argv[optind...argc-1]' */
INTERN ATTR_SECTION(".text.crt.application.getopt") WUNUSED NONNULL((2, 3)) int
NOTHROW_NCX(LIBCCALL libc_getopt_long)(int argc,
                                       char *const argv[],
                                       char const *optstring,
                                       struct option const *longopts,
                                       int *longindex) {
	return libc_getopt_impl((unsigned int)argc, (char const **)argv, optstring,
	                   longopts, (unsigned int *)longindex, 0);
}
/* >> getopt(3), getopt_long(3), getopt_long_only(3)
 * Parse options from arguments, as passed to `main()', and specified by `optstring'.
 * Arguments in `argv' appear in one of the following forms:
 *  - "-x":        Returns "x"                      (assuming `optstring' contains "x")
 *  - "-x -y":     Returns "x"                      (assuming `optstring' contains "x" and "y")
 *  - "-xyz":      Returns "x", "y", and then "z"   (assuming `optstring' contains "x", "y" and "z")
 *  - "-ofoo":     Returns "o", with `optarg="foo"' (assuming `optstring' contains "o:")
 *  - "-o", "foo": Returns "o", with `optarg="foo"' (assuming `optstring' contains "o:")
 * Long options (`getopt_long(3)'-only) appear in the following formats:
 *  - "--out":        Returns `longopts["out"].val'                      (assuming `longopts["out"].has_arg != required_argument')
 *  - "--out=foo":    Returns `longopts["out"].val', with `optarg="foo"' (assuming `longopts["out"].has_arg != no_argument')
 *  - "--out", "foo": Returns `longopts["out"].val', with `optarg="foo"' (assuming `longopts["out"].has_arg != no_argument')
 * When `getopt_long_only(3)' is used, long options may also be written with a single leading "-".
 *
 * This function interacts with the globals variables `optarg', `optind', `opterr' and `optopt'.
 * For  more information on  how these variables/are-used-by `getopt(3)'  (and friends), see the
 * documentation of the respective variable.
 *
 * The first character of `optstring' can be used to affect the behavior of this function:
 *  - '-': Each  non-option argument will be handled as though it was the argument of an option '\1'
 *         In other words: ["/bin/myapp", "-x", "foo", "bar"] (with `optstring="-x:"') would then be
 *         enumerated as  {[getopt:'x',optarg="foo"],  [getopt:1,optarg="bar"],  [getopt:-1]}.  Note
 *         that the special "--" argument still causes `getopt(3)' to return `-1' (with `optind' set
 *         to the 1 plus  the index of the  "--"-argument), even when this  option is used,  meaning
 *         that  when  using  this  option,  the  caller  must  handle  non-option  arguments  like:
 *         >> int opt;
 *         >> while ((opt = getopt(argc, argv, "-xy:z")) != -1) {
 *         >>     if (opt == 1)
 *         >>         handle_non_option_argument(optarg);
 *         >>     ...
 *         >> }
 *         >> while (optind < argc)
 *         >>     handle_non_option_argument(argv[optind++]);
 *         In this case, elements of `argv' are never permutated (and `argv' can be const).
 *  - '+': Stop parsing as soon as the first non-option argument is encountered. This is also the
 *         behavior when `optstring[0]' isn't a special character, and "$POSIXLY_CORRECT" is set,
 *         or `__posix_getopt(3)' was used.
 *         In this case, elements of `argv' are never permutated (and `argv' can be const).
 *  - ...: Default behavior (`optstring[0]'  isn't '-' or  '+'). In this  case, scanning of  `argv'
 *         does not stop at the first non-option argument, but only once the actual end is reached,
 *         or  an argument "--" is encountered. Once that is done, `getopt(3)' will return with the
 *         elements of `argv'  permutated such  that all  non-option arguments  appear (in  correct
 *         order) within `argv', starting at `argv[optind]'.
 *         e.g. Once option processing  is done, ["-afoo", "bar", "-c", "--", "-x"]  will
 *              result in `argv[optind...argc-1]' to be the array ["bar", "-x"] (assuming
 *              an `optstring' similar to "a:cx")
 *  - ':': Same as setting `opterr = 0' (may be combined with any of the other special flags by
 *         writing it _AFTER_ the other special flag; e.g. "+:xy:z")
 *
 * @param: argc: Number of arguments in `argv'
 * @param: argv: Argument vector from `main()' -- Shouldn't  actually be `const' here, since  this
 *               function may permute the  order of elements in  `argv' (to gather all  non-option
 *               arguments at the end), unless `optstring[0] == '+'', `__posix_getopt(3)' is used,
 *               or "$POSIXLY_CORRECT" is defined.
 * @param: optstring: [1..1] Options string (see above)
 * @param: longopts:  [0..1] Long options array (terminated by an all-NULL/0 element)
 * @param: longindex: [0..1] When non-NULL, set to the index of the matched long-option,
 *                           if  one was matched.  If none was (i.e.  a short option was
 *                           matched), the contents of this pointer are left  unchanged.
 * @return: 1 : The given `optstring' starts with '-', and a non-option argument `optarg' was encountered.
 * @return:'?': Error while processing options, or '?' appears in `optstring' (or as an `struct option::val')
 *              In the case of an error (and unless disabled by ':' or `opterr'), a message has already  been
 *              written to `stderr'.
 * @return: 0 : A long option was matched with `struct option::flag != NULL'.
 * @return: * : Either  a short option (return is that option's character-code), or a long-long (return is
 *              that option's `struct option::val', so-long as `struct option::flag == NULL') was matched.
 * @return: -1: Argument processing is done. Non-option arguments are in `argv[optind...argc-1]' */
INTERN ATTR_SECTION(".text.crt.application.getopt") WUNUSED NONNULL((2, 3)) int
NOTHROW_NCX(LIBCCALL libc_getopt_long_only)(int argc,
                                            char *const argv[],
                                            char const *optstring,
                                            struct option const *longopts,
                                            int *longindex) {
	return libc_getopt_impl((unsigned int)argc, (char const **)argv, optstring,
	                   longopts, (unsigned int *)longindex, 1);
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(bsd_getopt,libc_getopt,WUNUSED NONNULL((2, 3)),int,NOTHROW_NCX,LIBCCALL,(int argc, char *const argv[], char const *optstring),(argc,argv,optstring));
DEFINE_PUBLIC_ALIAS_P(getopt,libc_getopt,WUNUSED NONNULL((2, 3)),int,NOTHROW_NCX,LIBCCALL,(int argc, char *const argv[], char const *optstring),(argc,argv,optstring));
DEFINE_PUBLIC_ALIAS_P(__posix_getopt,libc___posix_getopt,WUNUSED NONNULL((2, 3)),int,NOTHROW_NCX,LIBCCALL,(int argc, char *const argv[], char const *optstring),(argc,argv,optstring));
DEFINE_PUBLIC_ALIAS_P(getopt_long,libc_getopt_long,WUNUSED NONNULL((2, 3)),int,NOTHROW_NCX,LIBCCALL,(int argc, char *const argv[], char const *optstring, struct option const *longopts, int *longindex),(argc,argv,optstring,longopts,longindex));
DEFINE_PUBLIC_ALIAS_P(getopt_long_only,libc_getopt_long_only,WUNUSED NONNULL((2, 3)),int,NOTHROW_NCX,LIBCCALL,(int argc, char *const argv[], char const *optstring, struct option const *longopts, int *longindex),(argc,argv,optstring,longopts,longindex));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_GETOPT_C */
