/* HASH CRC-32:0xfd00fddc */
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
#ifndef GUARD_LIBC_AUTO_GETOPT_H
#define GUARD_LIBC_AUTO_GETOPT_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <getopt.h>

DECL_BEGIN

#ifndef __KERNEL__
/* Back-bone driver for `getopt(3)'
 * @param: flags: Set of:
 *   - 0x0001: Long options may be written with a single leading "-"
 *   - 0x0002: Force posix behavior (set by `__posix_getopt') */
INTDEF WUNUSED NONNULL((2, 3)) int NOTHROW_NCX(LIBCCALL libc_getopt_impl)(unsigned int argc, char const *argv[], char const *optstring, struct option const *longopts, unsigned int *longindex, unsigned int flags);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
INTDEF WUNUSED NONNULL((2, 3)) int NOTHROW_NCX(LIBDCALL libd_getopt)(int argc, char *const argv[], char const *optstring);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
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
INTDEF WUNUSED NONNULL((2, 3)) int NOTHROW_NCX(LIBCCALL libc_getopt)(int argc, char *const argv[], char const *optstring);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED NONNULL((2, 3)) int NOTHROW_NCX(LIBDCALL libd___posix_getopt)(int argc, char *const argv[], char const *optstring);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED NONNULL((2, 3)) int NOTHROW_NCX(LIBCCALL libc___posix_getopt)(int argc, char *const argv[], char const *optstring);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
INTDEF WUNUSED NONNULL((2, 3)) int NOTHROW_NCX(LIBDCALL libd_getopt_long)(int argc, char *const argv[], char const *optstring, struct option const *longopts, int *longindex);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
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
INTDEF WUNUSED NONNULL((2, 3)) int NOTHROW_NCX(LIBCCALL libc_getopt_long)(int argc, char *const argv[], char const *optstring, struct option const *longopts, int *longindex);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
INTDEF WUNUSED NONNULL((2, 3)) int NOTHROW_NCX(LIBDCALL libd_getopt_long_only)(int argc, char *const argv[], char const *optstring, struct option const *longopts, int *longindex);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
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
INTDEF WUNUSED NONNULL((2, 3)) int NOTHROW_NCX(LIBCCALL libc_getopt_long_only)(int argc, char *const argv[], char const *optstring, struct option const *longopts, int *longindex);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_GETOPT_H */
