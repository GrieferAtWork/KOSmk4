/* HASH CRC-32:0xc8909782 */
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
#ifndef _GETOPT_H
#define _GETOPT_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <hybrid/typecore.h>
#include <bits/crt/getopt.h>

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

#ifndef __getopt_defined
#define __getopt_defined
#ifdef __CRT_HAVE_getopt
/* >> getopt(3), getopt_long(3), getopt_long_only(3)
 * Parse options from arguments, as passed to `main()', and specified by `optstring'.
 * Arguments in `argv' appear in one of the following forms:
 *  - "-x":        Returns "x"                      (assuming `optstring' contains "x")
 *  - "-x -y":     Returns "x"                      (assuming `optstring' contains "x" and "y")
 *  - "-xyz":      Returns "x", "y", and then "z"   (assuming `optstring' contains "x", "y" and "z")
 *  - "-ofoo":     Returns "o", with `optarg="foo"' (assuming `optstring' contains "o:")
 *  - "-o", "foo": Returns "o", with `optarg="foo"' (assuming `optstring' contains "o:")
 * Long options (`getopt_long(3)'-only)appear in the following formats:
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
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2, 3)),int,__NOTHROW_NCX,getopt,(int ___argc, char *const ___argv[], char const *__optstring),(___argc,___argv,__optstring))
#else /* __CRT_HAVE_getopt */
#include <libc/template/getopt.h>
#if defined(__CRT_HAVE_getopt_long) || (defined(__LOCAL_optarg) && defined(__LOCAL_optind))
#include <libc/local/getopt/getopt.h>
/* >> getopt(3), getopt_long(3), getopt_long_only(3)
 * Parse options from arguments, as passed to `main()', and specified by `optstring'.
 * Arguments in `argv' appear in one of the following forms:
 *  - "-x":        Returns "x"                      (assuming `optstring' contains "x")
 *  - "-x -y":     Returns "x"                      (assuming `optstring' contains "x" and "y")
 *  - "-xyz":      Returns "x", "y", and then "z"   (assuming `optstring' contains "x", "y" and "z")
 *  - "-ofoo":     Returns "o", with `optarg="foo"' (assuming `optstring' contains "o:")
 *  - "-o", "foo": Returns "o", with `optarg="foo"' (assuming `optstring' contains "o:")
 * Long options (`getopt_long(3)'-only)appear in the following formats:
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
__NAMESPACE_LOCAL_USING_OR_IMPL(getopt, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2, 3)) int __NOTHROW_NCX(__LIBCCALL getopt)(int ___argc, char *const ___argv[], char const *__optstring) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getopt))(___argc, ___argv, __optstring); })
#else /* __CRT_HAVE_getopt_long || (__LOCAL_optarg && __LOCAL_optind) */
#undef __getopt_defined
#endif /* !__CRT_HAVE_getopt_long && (!__LOCAL_optarg || !__LOCAL_optind) */
#endif /* !__CRT_HAVE_getopt */
#endif /* !__getopt_defined */
#ifdef __CRT_HAVE_getopt_long
/* >> getopt(3), getopt_long(3), getopt_long_only(3)
 * Parse options from arguments, as passed to `main()', and specified by `optstring'.
 * Arguments in `argv' appear in one of the following forms:
 *  - "-x":        Returns "x"                      (assuming `optstring' contains "x")
 *  - "-x -y":     Returns "x"                      (assuming `optstring' contains "x" and "y")
 *  - "-xyz":      Returns "x", "y", and then "z"   (assuming `optstring' contains "x", "y" and "z")
 *  - "-ofoo":     Returns "o", with `optarg="foo"' (assuming `optstring' contains "o:")
 *  - "-o", "foo": Returns "o", with `optarg="foo"' (assuming `optstring' contains "o:")
 * Long options (`getopt_long(3)'-only)appear in the following formats:
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
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2, 3)),int,__NOTHROW_NCX,getopt_long,(int ___argc, char *const ___argv[], char const *__optstring, struct option const *__longopts, int *__longindex),(___argc,___argv,__optstring,__longopts,__longindex))
#else /* __CRT_HAVE_getopt_long */
#include <libc/template/getopt.h>
#if defined(__LOCAL_optarg) && defined(__LOCAL_optind)
#include <libc/local/getopt/getopt_long.h>
/* >> getopt(3), getopt_long(3), getopt_long_only(3)
 * Parse options from arguments, as passed to `main()', and specified by `optstring'.
 * Arguments in `argv' appear in one of the following forms:
 *  - "-x":        Returns "x"                      (assuming `optstring' contains "x")
 *  - "-x -y":     Returns "x"                      (assuming `optstring' contains "x" and "y")
 *  - "-xyz":      Returns "x", "y", and then "z"   (assuming `optstring' contains "x", "y" and "z")
 *  - "-ofoo":     Returns "o", with `optarg="foo"' (assuming `optstring' contains "o:")
 *  - "-o", "foo": Returns "o", with `optarg="foo"' (assuming `optstring' contains "o:")
 * Long options (`getopt_long(3)'-only)appear in the following formats:
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
__NAMESPACE_LOCAL_USING_OR_IMPL(getopt_long, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2, 3)) int __NOTHROW_NCX(__LIBCCALL getopt_long)(int ___argc, char *const ___argv[], char const *__optstring, struct option const *__longopts, int *__longindex) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getopt_long))(___argc, ___argv, __optstring, __longopts, __longindex); })
#endif /* __LOCAL_optarg && __LOCAL_optind */
#endif /* !__CRT_HAVE_getopt_long */
#ifdef __CRT_HAVE_getopt_long_only
/* >> getopt(3), getopt_long(3), getopt_long_only(3)
 * Parse options from arguments, as passed to `main()', and specified by `optstring'.
 * Arguments in `argv' appear in one of the following forms:
 *  - "-x":        Returns "x"                      (assuming `optstring' contains "x")
 *  - "-x -y":     Returns "x"                      (assuming `optstring' contains "x" and "y")
 *  - "-xyz":      Returns "x", "y", and then "z"   (assuming `optstring' contains "x", "y" and "z")
 *  - "-ofoo":     Returns "o", with `optarg="foo"' (assuming `optstring' contains "o:")
 *  - "-o", "foo": Returns "o", with `optarg="foo"' (assuming `optstring' contains "o:")
 * Long options (`getopt_long(3)'-only)appear in the following formats:
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
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2, 3)),int,__NOTHROW_NCX,getopt_long_only,(int ___argc, char *const ___argv[], char const *__optstring, struct option const *__longopts, int *__longindex),(___argc,___argv,__optstring,__longopts,__longindex))
#else /* __CRT_HAVE_getopt_long_only */
#include <libc/template/getopt.h>
#if defined(__LOCAL_optarg) && defined(__LOCAL_optind)
#include <libc/local/getopt/getopt_long_only.h>
/* >> getopt(3), getopt_long(3), getopt_long_only(3)
 * Parse options from arguments, as passed to `main()', and specified by `optstring'.
 * Arguments in `argv' appear in one of the following forms:
 *  - "-x":        Returns "x"                      (assuming `optstring' contains "x")
 *  - "-x -y":     Returns "x"                      (assuming `optstring' contains "x" and "y")
 *  - "-xyz":      Returns "x", "y", and then "z"   (assuming `optstring' contains "x", "y" and "z")
 *  - "-ofoo":     Returns "o", with `optarg="foo"' (assuming `optstring' contains "o:")
 *  - "-o", "foo": Returns "o", with `optarg="foo"' (assuming `optstring' contains "o:")
 * Long options (`getopt_long(3)'-only)appear in the following formats:
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
__NAMESPACE_LOCAL_USING_OR_IMPL(getopt_long_only, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2, 3)) int __NOTHROW_NCX(__LIBCCALL getopt_long_only)(int ___argc, char *const ___argv[], char const *__optstring, struct option const *__longopts, int *__longindex) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getopt_long_only))(___argc, ___argv, __optstring, __longopts, __longindex); })
#endif /* __LOCAL_optarg && __LOCAL_optind */
#endif /* !__CRT_HAVE_getopt_long_only */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_GETOPT_H */
