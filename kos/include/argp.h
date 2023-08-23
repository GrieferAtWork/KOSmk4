/* HASH CRC-32:0xeb3d735f */
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
/* (#) Portability: EMX kLIBC     (/libc/include/argp.h) */
/* (#) Portability: GNU C Library (/argp/argp.h) */
/* (#) Portability: GNU Hurd      (/usr/include/argp.h) */
/* (#) Portability: libc6         (/include/argp.h) */
/* (#) Portability: mintlib       (/include/argp.h) */
#ifndef _ARGP_H
#define _ARGP_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>
#include <bits/crt/argp.h>

#ifdef __USE_GLIBC_BLOAT
#include <ctype.h>
#include <errno.h>
#include <getopt.h>
#include <limits.h>
#include <stdio.h>
#endif /* __USE_GLIBC_BLOAT */

/* ??? */
#if !defined(OPTION_ARG_OPTIONAL) && defined(__OPTION_ARG_OPTIONAL)
#define OPTION_ARG_OPTIONAL __OPTION_ARG_OPTIONAL /* ??? */
#endif /* !OPTION_ARG_OPTIONAL && __OPTION_ARG_OPTIONAL */
#if !defined(OPTION_HIDDEN) && defined(__OPTION_HIDDEN)
#define OPTION_HIDDEN __OPTION_HIDDEN /* Hide from `--help' */
#endif /* !OPTION_HIDDEN && __OPTION_HIDDEN */
#if !defined(OPTION_ALIAS) && defined(__OPTION_ALIAS)
#define OPTION_ALIAS __OPTION_ALIAS /* Alias for the last preceding non-OPTION_ALIAS option. */
#endif /* !OPTION_ALIAS && __OPTION_ALIAS */
#if !defined(OPTION_DOC) && defined(__OPTION_DOC)
#define OPTION_DOC __OPTION_DOC /* ??? */
#endif /* !OPTION_DOC && __OPTION_DOC */
#if !defined(OPTION_NO_USAGE) && defined(__OPTION_NO_USAGE)
#define OPTION_NO_USAGE __OPTION_NO_USAGE /* ??? */
#endif /* !OPTION_NO_USAGE && __OPTION_NO_USAGE */

/* ??? */
#if !defined(ARGP_ERR_UNKNOWN) && defined(__ARGP_ERR_UNKNOWN)
#define ARGP_ERR_UNKNOWN __ARGP_ERR_UNKNOWN /* ??? */
#endif /* !ARGP_ERR_UNKNOWN && __ARGP_ERR_UNKNOWN */

/* ??? */
#if !defined(ARGP_KEY_ARG) && defined(__ARGP_KEY_ARG)
#define ARGP_KEY_ARG __ARGP_KEY_ARG /* ??? */
#endif /* !ARGP_KEY_ARG && __ARGP_KEY_ARG */
#if !defined(ARGP_KEY_END) && defined(__ARGP_KEY_END)
#define ARGP_KEY_END __ARGP_KEY_END /* ??? */
#endif /* !ARGP_KEY_END && __ARGP_KEY_END */
#if !defined(ARGP_KEY_NO_ARGS) && defined(__ARGP_KEY_NO_ARGS)
#define ARGP_KEY_NO_ARGS __ARGP_KEY_NO_ARGS /* ??? */
#endif /* !ARGP_KEY_NO_ARGS && __ARGP_KEY_NO_ARGS */
#if !defined(ARGP_KEY_INIT) && defined(__ARGP_KEY_INIT)
#define ARGP_KEY_INIT __ARGP_KEY_INIT /* ??? */
#endif /* !ARGP_KEY_INIT && __ARGP_KEY_INIT */
#if !defined(ARGP_KEY_SUCCESS) && defined(__ARGP_KEY_SUCCESS)
#define ARGP_KEY_SUCCESS __ARGP_KEY_SUCCESS /* ??? */
#endif /* !ARGP_KEY_SUCCESS && __ARGP_KEY_SUCCESS */
#if !defined(ARGP_KEY_ERROR) && defined(__ARGP_KEY_ERROR)
#define ARGP_KEY_ERROR __ARGP_KEY_ERROR /* ??? */
#endif /* !ARGP_KEY_ERROR && __ARGP_KEY_ERROR */
#if !defined(ARGP_KEY_ARGS) && defined(__ARGP_KEY_ARGS)
#define ARGP_KEY_ARGS __ARGP_KEY_ARGS /* ??? */
#endif /* !ARGP_KEY_ARGS && __ARGP_KEY_ARGS */
#if !defined(ARGP_KEY_FINI) && defined(__ARGP_KEY_FINI)
#define ARGP_KEY_FINI __ARGP_KEY_FINI /* ??? */
#endif /* !ARGP_KEY_FINI && __ARGP_KEY_FINI */

/* ??? */
#if !defined(ARGP_KEY_HELP_PRE_DOC) && defined(__ARGP_KEY_HELP_PRE_DOC)
#define ARGP_KEY_HELP_PRE_DOC __ARGP_KEY_HELP_PRE_DOC /* ??? */
#endif /* !ARGP_KEY_HELP_PRE_DOC && __ARGP_KEY_HELP_PRE_DOC */
#if !defined(ARGP_KEY_HELP_POST_DOC) && defined(__ARGP_KEY_HELP_POST_DOC)
#define ARGP_KEY_HELP_POST_DOC __ARGP_KEY_HELP_POST_DOC /* ??? */
#endif /* !ARGP_KEY_HELP_POST_DOC && __ARGP_KEY_HELP_POST_DOC */
#if !defined(ARGP_KEY_HELP_HEADER) && defined(__ARGP_KEY_HELP_HEADER)
#define ARGP_KEY_HELP_HEADER __ARGP_KEY_HELP_HEADER /* ??? */
#endif /* !ARGP_KEY_HELP_HEADER && __ARGP_KEY_HELP_HEADER */
#if !defined(ARGP_KEY_HELP_EXTRA) && defined(__ARGP_KEY_HELP_EXTRA)
#define ARGP_KEY_HELP_EXTRA __ARGP_KEY_HELP_EXTRA /* ??? */
#endif /* !ARGP_KEY_HELP_EXTRA && __ARGP_KEY_HELP_EXTRA */
#if !defined(ARGP_KEY_HELP_DUP_ARGS_NOTE) && defined(__ARGP_KEY_HELP_DUP_ARGS_NOTE)
#define ARGP_KEY_HELP_DUP_ARGS_NOTE __ARGP_KEY_HELP_DUP_ARGS_NOTE /* ??? */
#endif /* !ARGP_KEY_HELP_DUP_ARGS_NOTE && __ARGP_KEY_HELP_DUP_ARGS_NOTE */
#if !defined(ARGP_KEY_HELP_ARGS_DOC) && defined(__ARGP_KEY_HELP_ARGS_DOC)
#define ARGP_KEY_HELP_ARGS_DOC __ARGP_KEY_HELP_ARGS_DOC /* ??? */
#endif /* !ARGP_KEY_HELP_ARGS_DOC && __ARGP_KEY_HELP_ARGS_DOC */

/* Possible flags for `argp_parse::flags' */
#if !defined(ARGP_PARSE_ARGV0) && defined(__ARGP_PARSE_ARGV0)
#define ARGP_PARSE_ARGV0 __ARGP_PARSE_ARGV0 /* Don't skip over `argv[0]' */
#endif /* !ARGP_PARSE_ARGV0 && __ARGP_PARSE_ARGV0 */
#if !defined(ARGP_NO_ERRS) && defined(__ARGP_NO_ERRS)
#define ARGP_NO_ERRS __ARGP_NO_ERRS /* Don't print error messages about unknown options to stderr. Implies `ARGP_NO_EXIT' */
#endif /* !ARGP_NO_ERRS && __ARGP_NO_ERRS */
#if !defined(ARGP_NO_ARGS) && defined(__ARGP_NO_ARGS)
#define ARGP_NO_ARGS __ARGP_NO_ARGS /* Don't parse non-option arguments (iow: ones that don't start with `-'). Else, invoke `argp::parser' with `key=ARGP_KEY_ARG' for non-option arguments. */
#endif /* !ARGP_NO_ARGS && __ARGP_NO_ARGS */
#if !defined(ARGP_IN_ORDER) && defined(__ARGP_IN_ORDER)
#define ARGP_IN_ORDER __ARGP_IN_ORDER /* Parse in command-line order, rather than parsing options before arguments. */
#endif /* !ARGP_IN_ORDER && __ARGP_IN_ORDER */
#if !defined(ARGP_NO_HELP) && defined(__ARGP_NO_HELP)
#define ARGP_NO_HELP __ARGP_NO_HELP /* Disable support for a standard `--help' option */
#endif /* !ARGP_NO_HELP && __ARGP_NO_HELP */
#if !defined(ARGP_NO_EXIT) && defined(__ARGP_NO_EXIT)
#define ARGP_NO_EXIT __ARGP_NO_EXIT /* Don't exit on error */
#endif /* !ARGP_NO_EXIT && __ARGP_NO_EXIT */
#if !defined(ARGP_LONG_ONLY) && defined(__ARGP_LONG_ONLY)
#define ARGP_LONG_ONLY __ARGP_LONG_ONLY /* Long options may be written with a single leading "-" */
#endif /* !ARGP_LONG_ONLY && __ARGP_LONG_ONLY */
#if !defined(ARGP_SILENT) && defined(__ARGP_SILENT)
#define ARGP_SILENT __ARGP_SILENT /* Disable extras */
#endif /* !ARGP_SILENT && __ARGP_SILENT */

/* Possible flags for `argp_help::flags' */
#if !defined(ARGP_HELP_USAGE) && defined(__ARGP_HELP_USAGE)
#define ARGP_HELP_USAGE __ARGP_HELP_USAGE /* ??? */
#endif /* !ARGP_HELP_USAGE && __ARGP_HELP_USAGE */
#if !defined(ARGP_HELP_SHORT_USAGE) && defined(__ARGP_HELP_SHORT_USAGE)
#define ARGP_HELP_SHORT_USAGE __ARGP_HELP_SHORT_USAGE /* ??? */
#endif /* !ARGP_HELP_SHORT_USAGE && __ARGP_HELP_SHORT_USAGE */
#if !defined(ARGP_HELP_SEE) && defined(__ARGP_HELP_SEE)
#define ARGP_HELP_SEE __ARGP_HELP_SEE /* ??? */
#endif /* !ARGP_HELP_SEE && __ARGP_HELP_SEE */
#if !defined(ARGP_HELP_LONG) && defined(__ARGP_HELP_LONG)
#define ARGP_HELP_LONG __ARGP_HELP_LONG /* ??? */
#endif /* !ARGP_HELP_LONG && __ARGP_HELP_LONG */
#if !defined(ARGP_HELP_PRE_DOC) && defined(__ARGP_HELP_PRE_DOC)
#define ARGP_HELP_PRE_DOC __ARGP_HELP_PRE_DOC /* ??? */
#endif /* !ARGP_HELP_PRE_DOC && __ARGP_HELP_PRE_DOC */
#if !defined(ARGP_HELP_POST_DOC) && defined(__ARGP_HELP_POST_DOC)
#define ARGP_HELP_POST_DOC __ARGP_HELP_POST_DOC /* ??? */
#endif /* !ARGP_HELP_POST_DOC && __ARGP_HELP_POST_DOC */
#if !defined(ARGP_HELP_DOC) && defined(__ARGP_HELP_DOC)
#define ARGP_HELP_DOC __ARGP_HELP_DOC /* ??? */
#endif /* !ARGP_HELP_DOC && __ARGP_HELP_DOC */
#if !defined(ARGP_HELP_BUG_ADDR) && defined(__ARGP_HELP_BUG_ADDR)
#define ARGP_HELP_BUG_ADDR __ARGP_HELP_BUG_ADDR /* ??? */
#endif /* !ARGP_HELP_BUG_ADDR && __ARGP_HELP_BUG_ADDR */
#if !defined(ARGP_HELP_LONG_ONLY) && defined(__ARGP_HELP_LONG_ONLY)
#define ARGP_HELP_LONG_ONLY __ARGP_HELP_LONG_ONLY /* ??? */
#endif /* !ARGP_HELP_LONG_ONLY && __ARGP_HELP_LONG_ONLY */
#if !defined(ARGP_HELP_EXIT_ERR) && defined(__ARGP_HELP_EXIT_ERR)
#define ARGP_HELP_EXIT_ERR __ARGP_HELP_EXIT_ERR /* ??? */
#endif /* !ARGP_HELP_EXIT_ERR && __ARGP_HELP_EXIT_ERR */
#if !defined(ARGP_HELP_EXIT_OK) && defined(__ARGP_HELP_EXIT_OK)
#define ARGP_HELP_EXIT_OK __ARGP_HELP_EXIT_OK /* ??? */
#endif /* !ARGP_HELP_EXIT_OK && __ARGP_HELP_EXIT_OK */
#if !defined(ARGP_HELP_STD_ERR) && defined(__ARGP_HELP_STD_ERR)
#define ARGP_HELP_STD_ERR __ARGP_HELP_STD_ERR /* ??? */
#endif /* !ARGP_HELP_STD_ERR && __ARGP_HELP_STD_ERR */
#if !defined(ARGP_HELP_STD_USAGE) && defined(__ARGP_HELP_STD_USAGE)
#define ARGP_HELP_STD_USAGE __ARGP_HELP_STD_USAGE /* ??? */
#endif /* !ARGP_HELP_STD_USAGE && __ARGP_HELP_STD_USAGE */
#if !defined(ARGP_HELP_STD_HELP) && defined(__ARGP_HELP_STD_HELP)
#define ARGP_HELP_STD_HELP __ARGP_HELP_STD_HELP /* ??? */
#endif /* !ARGP_HELP_STD_HELP && __ARGP_HELP_STD_HELP */


#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __error_t_defined
#define __error_t_defined
typedef __errno_t error_t;
#endif /* !__error_t_defined */

typedef __argp_parser_t argp_parser_t;

/* Globals... */
#ifndef argp_program_version
#ifdef __LOCAL_argp_program_version
#define argp_program_version __LOCAL_argp_program_version
#elif defined(__CRT_HAVE_argp_program_version)
__CSDECLARE(, char const *, argp_program_version)
#define argp_program_version argp_program_version
#endif /* ... */
#endif /* !argp_program_version */

#ifndef argp_program_version_hook
#ifdef __LOCAL_argp_program_version_hook
#define argp_program_version_hook __LOCAL_argp_program_version_hook
#elif defined(__CRT_HAVE_argp_program_version_hook)
__CSDECLARE(, __argp_program_version_hook_t, argp_program_version_hook)
#define argp_program_version_hook argp_program_version_hook
#endif /* ... */
#endif /* !argp_program_version_hook */

#ifndef argp_program_bug_address
#ifdef __LOCAL_argp_program_bug_address
#define argp_program_bug_address __LOCAL_argp_program_bug_address
#elif defined(__CRT_HAVE_argp_program_bug_address)
__CSDECLARE(, char const *, argp_program_bug_address)
#define argp_program_bug_address argp_program_bug_address
#endif /* ... */
#endif /* !argp_program_bug_address */

#ifndef argp_err_exit_status
#ifdef __LOCAL_argp_err_exit_status
#define argp_err_exit_status __LOCAL_argp_err_exit_status
#elif defined(__CRT_HAVE_argp_err_exit_status)
__CSDECLARE(, int, argp_err_exit_status)
#define argp_err_exit_status argp_err_exit_status
#endif /* ... */
#endif /* !argp_err_exit_status */

#ifdef __CRT_HAVE_argp_parse
/* >> argp_parse(3)
 * @param: flags: Set  of  `ARGP_PARSE_ARGV0  | ARGP_NO_ERRS  |  ARGP_NO_ARGS |
 *                ARGP_IN_ORDER | ARGP_NO_HELP | ARGP_NO_EXIT | ARGP_LONG_ONLY' */
__CDECLARE(__ATTR_IN(1) __ATTR_INS(3, 2) __ATTR_OUT(5),error_t,__NOTHROW_NCX,argp_parse,(struct argp const *__restrict __ap, int ___argc, char **__restrict ___argv, unsigned int __flags, int *__restrict __arg_index, void *__input),(__ap,___argc,___argv,__flags,__arg_index,__input))
#elif defined(__CRT_HAVE___argp_parse)
/* >> argp_parse(3)
 * @param: flags: Set  of  `ARGP_PARSE_ARGV0  | ARGP_NO_ERRS  |  ARGP_NO_ARGS |
 *                ARGP_IN_ORDER | ARGP_NO_HELP | ARGP_NO_EXIT | ARGP_LONG_ONLY' */
__CREDIRECT(__ATTR_IN(1) __ATTR_INS(3, 2) __ATTR_OUT(5),error_t,__NOTHROW_NCX,argp_parse,(struct argp const *__restrict __ap, int ___argc, char **__restrict ___argv, unsigned int __flags, int *__restrict __arg_index, void *__input),__argp_parse,(__ap,___argc,___argv,__flags,__arg_index,__input))
#endif /* ... */
#ifdef __CRT_HAVE_argp_help
/* >> argp_parse(3)
 * @param: flags: Set of `ARGP_HELP_*' */
__CDECLARE_VOID(__ATTR_IN(1) __ATTR_IN(4) __ATTR_INOUT(2),__NOTHROW_NCX,argp_help,(struct argp const *__restrict __ap, __FILE *__restrict __stream, unsigned int __flags, char __KOS_FIXED_CONST *__restrict __name),(__ap,__stream,__flags,__name))
#elif defined(__CRT_HAVE___argp_parse)
/* >> argp_parse(3)
 * @param: flags: Set of `ARGP_HELP_*' */
__CREDIRECT_VOID(__ATTR_IN(1) __ATTR_IN(4) __ATTR_INOUT(2),__NOTHROW_NCX,argp_help,(struct argp const *__restrict __ap, __FILE *__restrict __stream, unsigned int __flags, char __KOS_FIXED_CONST *__restrict __name),__argp_parse,(__ap,__stream,__flags,__name))
#endif /* ... */
#ifdef __CRT_HAVE_argp_state_help
/* >> argp_state_help(3)
 * @param: flags: Set of `ARGP_HELP_*' */
__CDECLARE_VOID(__ATTR_INOUT_OPT(2) __ATTR_IN_OPT(1),__NOTHROW_NCX,argp_state_help,(struct argp_state const *__restrict __state, __FILE *__restrict __stream, unsigned int __flags),(__state,__stream,__flags))
#elif defined(__CRT_HAVE___argp_state_help)
/* >> argp_state_help(3)
 * @param: flags: Set of `ARGP_HELP_*' */
__CREDIRECT_VOID(__ATTR_INOUT_OPT(2) __ATTR_IN_OPT(1),__NOTHROW_NCX,argp_state_help,(struct argp_state const *__restrict __state, __FILE *__restrict __stream, unsigned int __flags),__argp_state_help,(__state,__stream,__flags))
#endif /* ... */
#ifdef __CRT_HAVE_argp_usage
__CDECLARE_VOID(__ATTR_IN(1),__NOTHROW_NCX,argp_usage,(struct argp_state const *__state),(__state))
#elif defined(__CRT_HAVE___argp_usage)
__CREDIRECT_VOID(__ATTR_IN(1),__NOTHROW_NCX,argp_usage,(struct argp_state const *__state),__argp_usage,(__state))
#else /* ... */
#include <libc/template/stdstreams.h>
#if (defined(__CRT_HAVE_argp_state_help) || defined(__CRT_HAVE___argp_state_help)) && defined(__LOCAL_stderr) && defined(__ARGP_HELP_STD_USAGE)
#include <libc/local/argp/argp_usage.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(argp_usage, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) void __NOTHROW_NCX(__LIBCCALL argp_usage)(struct argp_state const *__state) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argp_usage))(__state); })
#endif /* (__CRT_HAVE_argp_state_help || __CRT_HAVE___argp_state_help) && __LOCAL_stderr && __ARGP_HELP_STD_USAGE */
#endif /* !... */
#ifdef __CRT_HAVE_argp_error
__LIBC __ATTR_IN(2) __ATTR_IN_OPT(1) __ATTR_LIBC_PRINTF(2, 3) void __NOTHROW_NCX(__VLIBCCALL argp_error)(struct argp_state const *__restrict __state, char const *__restrict __format, ...) __CASMNAME_SAME("argp_error");
#elif defined(__CRT_HAVE___argp_error)
__LIBC __ATTR_IN(2) __ATTR_IN_OPT(1) __ATTR_LIBC_PRINTF(2, 3) void __NOTHROW_NCX(__VLIBCCALL argp_error)(struct argp_state const *__restrict __state, char const *__restrict __format, ...) __CASMNAME("__argp_error");
#elif (defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_argp_state_help) || defined(__CRT_HAVE___argp_state_help)) && defined(__ARGP_HELP_STD_ERR)
#include <libc/local/argp/argp_error.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(argp_error, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_IN_OPT(1) __ATTR_LIBC_PRINTF(2, 3) void __NOTHROW_NCX(__VLIBCCALL argp_error)(struct argp_state const *__restrict __state, char const *__restrict __format, ...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argp_error))(__state, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define argp_error(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argp_error))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE_argp_failure
__LIBC __ATTR_IN(4) __ATTR_IN_OPT(1) __ATTR_LIBC_PRINTF(4, 5) void __NOTHROW_NCX(__VLIBCCALL argp_failure)(struct argp_state const *__restrict __state, int __status, __errno_t __errnum, char const *__restrict __format, ...) __CASMNAME_SAME("argp_failure");
#elif defined(__CRT_HAVE___argp_failure)
__LIBC __ATTR_IN(4) __ATTR_IN_OPT(1) __ATTR_LIBC_PRINTF(4, 5) void __NOTHROW_NCX(__VLIBCCALL argp_failure)(struct argp_state const *__restrict __state, int __status, __errno_t __errnum, char const *__restrict __format, ...) __CASMNAME("__argp_failure");
#elif (defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE_xexit))
#include <libc/local/argp/argp_failure.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(argp_failure, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(4) __ATTR_IN_OPT(1) __ATTR_LIBC_PRINTF(4, 5) void __NOTHROW_NCX(__VLIBCCALL argp_failure)(struct argp_state const *__restrict __state, int __status, __errno_t __errnum, char const *__restrict __format, ...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argp_failure))(__state, __status, __errnum, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define argp_failure(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argp_failure))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE__option_is_short
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_NCX,_option_is_short,(struct argp_option const *__opt),(__opt))
#elif defined(__CRT_HAVE___option_is_short)
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_NCX,_option_is_short,(struct argp_option const *__opt),__option_is_short,(__opt))
#elif defined(__OPTION_DOC)
#include <libc/local/argp/_option_is_short.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_option_is_short, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_NCX(__LIBCCALL _option_is_short)(struct argp_option const *__opt) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_option_is_short))(__opt); })
#endif /* ... */
#ifdef __CRT_HAVE__option_is_end
/* >> _option_is_end(3)
 * Check if `opt' represents the end of an option-chain */
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_NCX,_option_is_end,(struct argp_option const *__opt),(__opt))
#elif defined(__CRT_HAVE___option_is_end)
/* >> _option_is_end(3)
 * Check if `opt' represents the end of an option-chain */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_NCX,_option_is_end,(struct argp_option const *__opt),__option_is_end,(__opt))
#else /* ... */
#include <libc/local/argp/_option_is_end.h>
/* >> _option_is_end(3)
 * Check if `opt' represents the end of an option-chain */
__NAMESPACE_LOCAL_USING_OR_IMPL(_option_is_end, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_NCX(__LIBCCALL _option_is_end)(struct argp_option const *__opt) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_option_is_end))(__opt); })
#endif /* !... */
#ifdef __CRT_HAVE__argp_input
__CDECLARE(__ATTR_IN_OPT(1) __ATTR_IN_OPT(2),void *,__NOTHROW_NCX,_argp_input,(struct argp const *__restrict __ap, struct argp_state const *__restrict __state),(__ap,__state))
#elif defined(__CRT_HAVE___argp_input)
__CREDIRECT(__ATTR_IN_OPT(1) __ATTR_IN_OPT(2),void *,__NOTHROW_NCX,_argp_input,(struct argp const *__restrict __ap, struct argp_state const *__restrict __state),__argp_input,(__ap,__state))
#endif /* ... */
#ifdef __CRT_HAVE_argp_parse
/* >> argp_parse(3)
 * @param: flags: Set  of  `ARGP_PARSE_ARGV0  | ARGP_NO_ERRS  |  ARGP_NO_ARGS |
 *                ARGP_IN_ORDER | ARGP_NO_HELP | ARGP_NO_EXIT | ARGP_LONG_ONLY' */
__CREDIRECT(__ATTR_IN(1) __ATTR_INS(3, 2) __ATTR_OUT(5),error_t,__NOTHROW_NCX,__argp_parse,(struct argp const *__restrict __ap, int ___argc, char **__restrict ___argv, unsigned int __flags, int *__restrict __arg_index, void *__input),argp_parse,(__ap,___argc,___argv,__flags,__arg_index,__input))
#elif defined(__CRT_HAVE___argp_parse)
/* >> argp_parse(3)
 * @param: flags: Set  of  `ARGP_PARSE_ARGV0  | ARGP_NO_ERRS  |  ARGP_NO_ARGS |
 *                ARGP_IN_ORDER | ARGP_NO_HELP | ARGP_NO_EXIT | ARGP_LONG_ONLY' */
__CDECLARE(__ATTR_IN(1) __ATTR_INS(3, 2) __ATTR_OUT(5),error_t,__NOTHROW_NCX,__argp_parse,(struct argp const *__restrict __ap, int ___argc, char **__restrict ___argv, unsigned int __flags, int *__restrict __arg_index, void *__input),(__ap,___argc,___argv,__flags,__arg_index,__input))
#endif /* ... */
#ifdef __CRT_HAVE_argp_help
/* >> argp_parse(3)
 * @param: flags: Set of `ARGP_HELP_*' */
__CREDIRECT_VOID(__ATTR_IN(1) __ATTR_IN(4) __ATTR_INOUT(2),__NOTHROW_NCX,__argp_help,(struct argp const *__restrict __ap, __FILE *__restrict __stream, unsigned int __flags, char __KOS_FIXED_CONST *__restrict __name),argp_help,(__ap,__stream,__flags,__name))
#elif defined(__CRT_HAVE___argp_parse)
/* >> argp_parse(3)
 * @param: flags: Set of `ARGP_HELP_*' */
__CREDIRECT_VOID(__ATTR_IN(1) __ATTR_IN(4) __ATTR_INOUT(2),__NOTHROW_NCX,__argp_help,(struct argp const *__restrict __ap, __FILE *__restrict __stream, unsigned int __flags, char __KOS_FIXED_CONST *__restrict __name),__argp_parse,(__ap,__stream,__flags,__name))
#endif /* ... */
#ifdef __CRT_HAVE_argp_state_help
/* >> argp_state_help(3)
 * @param: flags: Set of `ARGP_HELP_*' */
__CREDIRECT_VOID(__ATTR_INOUT_OPT(2) __ATTR_IN_OPT(1),__NOTHROW_NCX,__argp_state_help,(struct argp_state const *__restrict __state, __FILE *__restrict __stream, unsigned int __flags),argp_state_help,(__state,__stream,__flags))
#elif defined(__CRT_HAVE___argp_state_help)
/* >> argp_state_help(3)
 * @param: flags: Set of `ARGP_HELP_*' */
__CDECLARE_VOID(__ATTR_INOUT_OPT(2) __ATTR_IN_OPT(1),__NOTHROW_NCX,__argp_state_help,(struct argp_state const *__restrict __state, __FILE *__restrict __stream, unsigned int __flags),(__state,__stream,__flags))
#endif /* ... */
#ifdef __CRT_HAVE_argp_usage
__CREDIRECT_VOID(__ATTR_IN(1),__NOTHROW_NCX,__argp_usage,(struct argp_state const *__state),argp_usage,(__state))
#elif defined(__CRT_HAVE___argp_usage)
__CDECLARE_VOID(__ATTR_IN(1),__NOTHROW_NCX,__argp_usage,(struct argp_state const *__state),(__state))
#else /* ... */
#include <libc/template/stdstreams.h>
#if (defined(__CRT_HAVE_argp_state_help) || defined(__CRT_HAVE___argp_state_help)) && defined(__LOCAL_stderr) && defined(__ARGP_HELP_STD_USAGE)
#include <libc/local/argp/argp_usage.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) void __NOTHROW_NCX(__LIBCCALL __argp_usage)(struct argp_state const *__state) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argp_usage))(__state); }
#endif /* (__CRT_HAVE_argp_state_help || __CRT_HAVE___argp_state_help) && __LOCAL_stderr && __ARGP_HELP_STD_USAGE */
#endif /* !... */
#ifdef __CRT_HAVE_argp_error
__LIBC __ATTR_IN(2) __ATTR_IN_OPT(1) __ATTR_LIBC_PRINTF(2, 3) void __NOTHROW_NCX(__VLIBCCALL __argp_error)(struct argp_state const *__restrict __state, char const *__restrict __format, ...) __CASMNAME("argp_error");
#elif defined(__CRT_HAVE___argp_error)
__LIBC __ATTR_IN(2) __ATTR_IN_OPT(1) __ATTR_LIBC_PRINTF(2, 3) void __NOTHROW_NCX(__VLIBCCALL __argp_error)(struct argp_state const *__restrict __state, char const *__restrict __format, ...) __CASMNAME_SAME("__argp_error");
#elif (defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_argp_state_help) || defined(__CRT_HAVE___argp_state_help)) && defined(__ARGP_HELP_STD_ERR)
#include <libc/local/argp/argp_error.h>
#define __argp_error(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argp_error))(__VA_ARGS__)
#endif /* ... */
#ifdef __CRT_HAVE_argp_failure
__LIBC __ATTR_IN(4) __ATTR_IN_OPT(1) __ATTR_LIBC_PRINTF(4, 5) void __NOTHROW_NCX(__VLIBCCALL __argp_failure)(struct argp_state const *__restrict __state, int __status, __errno_t __errnum, char const *__restrict __format, ...) __CASMNAME("argp_failure");
#elif defined(__CRT_HAVE___argp_failure)
__LIBC __ATTR_IN(4) __ATTR_IN_OPT(1) __ATTR_LIBC_PRINTF(4, 5) void __NOTHROW_NCX(__VLIBCCALL __argp_failure)(struct argp_state const *__restrict __state, int __status, __errno_t __errnum, char const *__restrict __format, ...) __CASMNAME_SAME("__argp_failure");
#elif (defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE_xexit))
#include <libc/local/argp/argp_failure.h>
#define __argp_failure(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argp_failure))(__VA_ARGS__)
#endif /* ... */
#ifdef __CRT_HAVE__option_is_short
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_NCX,__option_is_short,(struct argp_option const *__opt),_option_is_short,(__opt))
#elif defined(__CRT_HAVE___option_is_short)
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_NCX,__option_is_short,(struct argp_option const *__opt),(__opt))
#elif defined(__OPTION_DOC)
#include <libc/local/argp/_option_is_short.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_NCX(__LIBCCALL __option_is_short)(struct argp_option const *__opt) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_option_is_short))(__opt); }
#endif /* ... */
#ifdef __CRT_HAVE__option_is_end
/* >> _option_is_end(3)
 * Check if `opt' represents the end of an option-chain */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_NCX,__option_is_end,(struct argp_option const *__opt),_option_is_end,(__opt))
#elif defined(__CRT_HAVE___option_is_end)
/* >> _option_is_end(3)
 * Check if `opt' represents the end of an option-chain */
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_NCX,__option_is_end,(struct argp_option const *__opt),(__opt))
#else /* ... */
#include <libc/local/argp/_option_is_end.h>
/* >> _option_is_end(3)
 * Check if `opt' represents the end of an option-chain */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_NCX(__LIBCCALL __option_is_end)(struct argp_option const *__opt) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_option_is_end))(__opt); }
#endif /* !... */
#ifdef __CRT_HAVE__argp_input
__CREDIRECT(__ATTR_IN_OPT(1) __ATTR_IN_OPT(2),void *,__NOTHROW_NCX,__argp_input,(struct argp const *__restrict __ap, struct argp_state const *__restrict __state),_argp_input,(__ap,__state))
#elif defined(__CRT_HAVE___argp_input)
__CDECLARE(__ATTR_IN_OPT(1) __ATTR_IN_OPT(2),void *,__NOTHROW_NCX,__argp_input,(struct argp const *__restrict __ap, struct argp_state const *__restrict __state),(__ap,__state))
#endif /* ... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_ARGP_H */
