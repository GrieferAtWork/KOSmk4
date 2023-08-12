/* HASH CRC-32:0xd647efcb */
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
/* (#) Portability: libbsd  (/include/bsd/unistd.h) */
/* (#) Portability: libc4/5 (/include/bsd/unistd.h) */
#ifndef _BSD_UNISTD_H
#define _BSD_UNISTD_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <unistd.h>
#include <fcntl.h> /* As seen in `libc4/5' */
#include <sys/stat.h> /* As seen in `libc4/5' */
#include <sys/time.h> /* As seen in `libc4/5' */

#ifdef __CC__
__SYSDECL_BEGIN

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

#ifdef __CRT_HAVE_getopt
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
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2, 3)),int,__NOTHROW_NCX,bsd_getopt,(int ___argc, char *const ___argv[], char const *__optstring),getopt,(___argc,___argv,__optstring))
#elif defined(__CRT_HAVE_bsd_getopt)
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
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2, 3)),int,__NOTHROW_NCX,bsd_getopt,(int ___argc, char *const ___argv[], char const *__optstring),(___argc,___argv,__optstring))
#else /* ... */
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
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2, 3)) int __NOTHROW_NCX(__LIBCCALL bsd_getopt)(int ___argc, char *const ___argv[], char const *__optstring) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getopt))(___argc, ___argv, __optstring); }
#endif /* __CRT_HAVE_getopt_long || (__LOCAL_optarg && __LOCAL_optind) */
#endif /* !... */
#if !defined(__getmode_defined) && defined(__CRT_HAVE_getmode)
#define __getmode_defined
/* >> setmode(3), getmode(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1),__mode_t,__NOTHROW_NCX,getmode,(void const *__bbox, __mode_t __mode),(__bbox,__mode))
#endif /* !__getmode_defined && __CRT_HAVE_getmode */
#if !defined(__setmode_defined) && defined(__CRT_HAVE_setmode)
#define __setmode_defined
/* >> setmode(3), getmode(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1),void *,__NOTHROW_NCX,setmode,(char const *__mode_str),(__mode_str))
#endif /* !__setmode_defined && __CRT_HAVE_setmode */
#ifndef __closefrom_defined
#define __closefrom_defined
#ifdef __CRT_HAVE_closefrom
/* >> closefrom(2)
 * Close all file descriptors with indices `>= lowfd' (s.a. `fcntl(F_CLOSEM)') */
__CDECLARE_VOID(,__NOTHROW_NCX,closefrom,(__fd_t __lowfd),(__lowfd))
#else /* __CRT_HAVE_closefrom */
#include <asm/os/fcntl.h>
#if ((defined(__CRT_HAVE_fcntl) || defined(__CRT_HAVE___fcntl) || defined(__CRT_HAVE___libc_fcntl)) && defined(__F_CLOSEM)) || defined(__CRT_HAVE_close_range)
#include <libc/local/unistd/closefrom.h>
/* >> closefrom(2)
 * Close all file descriptors with indices `>= lowfd' (s.a. `fcntl(F_CLOSEM)') */
__NAMESPACE_LOCAL_USING_OR_IMPL(closefrom, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL closefrom)(__fd_t __lowfd) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(closefrom))(__lowfd); })
#else /* ((__CRT_HAVE_fcntl || __CRT_HAVE___fcntl || __CRT_HAVE___libc_fcntl) && __F_CLOSEM) || __CRT_HAVE_close_range */
#undef __closefrom_defined
#endif /* ((!__CRT_HAVE_fcntl && !__CRT_HAVE___fcntl && !__CRT_HAVE___libc_fcntl) || !__F_CLOSEM) && !__CRT_HAVE_close_range */
#endif /* !__CRT_HAVE_closefrom */
#endif /* !__closefrom_defined */
#ifndef __setproctitle_defined
#define __setproctitle_defined
#ifdef __CRT_HAVE_setproctitle
/* >> setproctitle(3)
 * Set the program comm name. S.a.:
 *  - pthread_setname_np(3)
 *  - prctl(PR_SET_NAME)
 *  - "/proc/self/comm" */
__LIBC __ATTR_IN(1) __ATTR_LIBC_PRINTF(1, 2) void __NOTHROW_NCX(__VLIBCCALL setproctitle)(char const *__format, ...) __CASMNAME_SAME("setproctitle");
#else /* __CRT_HAVE_setproctitle */
#include <linux/prctl.h>
#if ((defined(__CRT_HAVE_prctl) && defined(PR_SET_NAME)) || ((defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current) || defined(__CRT_HAVE_thr_self) || defined(__CRT_HAVE_cthread_self)) && (defined(__CRT_HAVE_pthread_setname_np) || defined(__CRT_HAVE_pthread_set_name_np) || defined(__CRT_HAVE_cthread_set_name)))) && (defined(__TASK_COMM_LEN) || defined(__CRT_HAVE_vstrdupf) || defined(__CRT_HAVE_vasprintf) || ((defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free))))
#include <libc/local/stdlib/setproctitle.h>
/* >> setproctitle(3)
 * Set the program comm name. S.a.:
 *  - pthread_setname_np(3)
 *  - prctl(PR_SET_NAME)
 *  - "/proc/self/comm" */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(setproctitle, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_LIBC_PRINTF(1, 2) void __NOTHROW_NCX(__VLIBCCALL setproctitle)(char const *__format, ...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setproctitle))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define setproctitle(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setproctitle))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#else /* ((__CRT_HAVE_prctl && PR_SET_NAME) || ((__CRT_HAVE_pthread_self || __CRT_HAVE_thrd_current || __CRT_HAVE_thr_self || __CRT_HAVE_cthread_self) && (__CRT_HAVE_pthread_setname_np || __CRT_HAVE_pthread_set_name_np || __CRT_HAVE_cthread_set_name))) && (__TASK_COMM_LEN || __CRT_HAVE_vstrdupf || __CRT_HAVE_vasprintf || ((__CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free))) */
#undef __setproctitle_defined
#endif /* ((!__CRT_HAVE_prctl || !PR_SET_NAME) && ((!__CRT_HAVE_pthread_self && !__CRT_HAVE_thrd_current && !__CRT_HAVE_thr_self && !__CRT_HAVE_cthread_self) || (!__CRT_HAVE_pthread_setname_np && !__CRT_HAVE_pthread_set_name_np && !__CRT_HAVE_cthread_set_name))) || (!__TASK_COMM_LEN && !__CRT_HAVE_vstrdupf && !__CRT_HAVE_vasprintf && ((!__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_free && !__CRT_HAVE_cfree && !__CRT_HAVE___libc_free))) */
#endif /* !__CRT_HAVE_setproctitle */
#endif /* !__setproctitle_defined */
#ifndef __getpeereid_defined
#define __getpeereid_defined
#ifdef __CRT_HAVE_getpeereid
/* >> getpeereid(3)
 * Convenience wrapper for `getsockopt(sockfd, SOL_SOCKET, SO_PEERCRED)' */
__CDECLARE(__ATTR_FDARG(1) __ATTR_OUT(2) __ATTR_OUT(3),int,__NOTHROW_NCX,getpeereid,(__fd_t __sockfd, uid_t *__euid, gid_t *__egid),(__sockfd,__euid,__egid))
#else /* __CRT_HAVE_getpeereid */
#include <asm/os/socket.h>
#if defined(__CRT_HAVE_getsockopt) && defined(__SOL_SOCKET) && defined(__SO_PEERCRED)
#include <libc/local/unistd/getpeereid.h>
/* >> getpeereid(3)
 * Convenience wrapper for `getsockopt(sockfd, SOL_SOCKET, SO_PEERCRED)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(getpeereid, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) __ATTR_OUT(2) __ATTR_OUT(3) int __NOTHROW_NCX(__LIBCCALL getpeereid)(__fd_t __sockfd, uid_t *__euid, gid_t *__egid) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getpeereid))(__sockfd, __euid, __egid); })
#else /* __CRT_HAVE_getsockopt && __SOL_SOCKET && __SO_PEERCRED */
#undef __getpeereid_defined
#endif /* !__CRT_HAVE_getsockopt || !__SOL_SOCKET || !__SO_PEERCRED */
#endif /* !__CRT_HAVE_getpeereid */
#endif /* !__getpeereid_defined */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_BSD_UNISTD_H */
