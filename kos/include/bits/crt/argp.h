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
#ifndef _BITS_CRT_ARGP_H
#define _BITS_CRT_ARGP_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <asm/os/errno.h>
#include <bits/types.h>

/* Possible flags for `struct argp_option::flags' */
#define __OPTION_ARG_OPTIONAL 0x01 /* [valid_if(OPTION_ARG_OPTIONAL)] The argument is optional */
#define __OPTION_HIDDEN       0x02 /* Hide from `--help' */
#define __OPTION_ALIAS        0x04 /* Alias for the last preceding non-OPTION_ALIAS option. */
#define __OPTION_DOC          0x08 /* ??? */
#define __OPTION_NO_USAGE     0x10 /* ??? */

/* Special return values for `__argp_parser_t' */
#define __ARGP_ERR_UNKNOWN __E2BIG /* ??? */

/* Special values for `__argp_parser_t::key' */
#define __ARGP_KEY_ARG     0         /* ??? */
#define __ARGP_KEY_END     0x1000001 /* ??? */
#define __ARGP_KEY_NO_ARGS 0x1000002 /* ??? */
#define __ARGP_KEY_INIT    0x1000003 /* ??? */
#define __ARGP_KEY_SUCCESS 0x1000004 /* ??? */
#define __ARGP_KEY_ERROR   0x1000005 /* ??? */
#define __ARGP_KEY_ARGS    0x1000006 /* ??? */
#define __ARGP_KEY_FINI    0x1000007 /* ??? */

/* ??? */
#define __ARGP_KEY_HELP_PRE_DOC       0x2000001 /* ??? */
#define __ARGP_KEY_HELP_POST_DOC      0x2000002 /* ??? */
#define __ARGP_KEY_HELP_HEADER        0x2000003 /* ??? */
#define __ARGP_KEY_HELP_EXTRA         0x2000004 /* ??? */
#define __ARGP_KEY_HELP_DUP_ARGS_NOTE 0x2000005 /* ??? */
#define __ARGP_KEY_HELP_ARGS_DOC      0x2000006 /* ??? */

/* Possible flags for `argp_parse::flags' */
#define __ARGP_PARSE_ARGV0 0x0001 /* Don't skip over `argv[0]' */
#define __ARGP_NO_ERRS     0x0002 /* Don't print error messages about unknown options to stderr. Implies `ARGP_NO_EXIT' */
#define __ARGP_NO_ARGS     0x0004 /* Don't parse non-option arguments (iow: ones that don't start with `-'). Else, invoke `argp::parser' with `key=ARGP_KEY_ARG' for non-option arguments. */
#define __ARGP_IN_ORDER    0x0008 /* Parse in command-line order, rather than parsing options before arguments. */
#define __ARGP_NO_HELP     0x0010 /* Disable support for a standard `--help' option */
#define __ARGP_NO_EXIT     0x0020 /* Don't exit on error */
#define __ARGP_LONG_ONLY   0x0040 /* Long options may be written with a single leading "-" */
#define __ARGP_SILENT      (__ARGP_NO_EXIT | __ARGP_NO_ERRS | __ARGP_NO_HELP) /* Disable extras */

/* Possible flags for `argp_help::flags' and `argp_state_help::flags' */
#define __ARGP_HELP_USAGE       0x0001 /* ??? */
#define __ARGP_HELP_SHORT_USAGE 0x0002 /* ??? */
#define __ARGP_HELP_SEE         0x0004 /* ??? */
#define __ARGP_HELP_LONG        0x0008 /* ??? */
#define __ARGP_HELP_PRE_DOC     0x0010 /* ??? */
#define __ARGP_HELP_POST_DOC    0x0020 /* ??? */
#define __ARGP_HELP_DOC         (__ARGP_HELP_PRE_DOC | __ARGP_HELP_POST_DOC) /* ??? */
#define __ARGP_HELP_BUG_ADDR    0x0040 /* ??? */
#define __ARGP_HELP_LONG_ONLY   0x0080 /* ??? */
#define __ARGP_HELP_EXIT_ERR    0x0100 /* ??? */
#define __ARGP_HELP_EXIT_OK     0x0200 /* ??? */
#define __ARGP_HELP_STD_ERR     (__ARGP_HELP_SEE | __ARGP_HELP_EXIT_ERR) /* ??? */
#define __ARGP_HELP_STD_USAGE   (__ARGP_HELP_SHORT_USAGE | __ARGP_HELP_SEE | __ARGP_HELP_EXIT_ERR) /* ??? */
#define __ARGP_HELP_STD_HELP    (__ARGP_HELP_SHORT_USAGE | __ARGP_HELP_LONG | __ARGP_HELP_EXIT_OK | __ARGP_HELP_DOC | __ARGP_HELP_BUG_ADDR) /* ??? */

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("name")
#pragma push_macro("key")
#pragma push_macro("arg")
#pragma push_macro("flags")
#pragma push_macro("doc")
#pragma push_macro("group")
#pragma push_macro("state")
#pragma push_macro("options")
#pragma push_macro("parser")
#pragma push_macro("args_doc")
#pragma push_macro("children")
#pragma push_macro("text")
#pragma push_macro("help_filter")
#pragma push_macro("argp_domain")
#pragma push_macro("argp")
#pragma push_macro("header")
#pragma push_macro("root_argp")
#pragma push_macro("argc")
#pragma push_macro("argv")
#pragma push_macro("next")
#pragma push_macro("arg_num")
#pragma push_macro("quoted")
#pragma push_macro("input")
#pragma push_macro("child_inputs")
#pragma push_macro("hook")
#pragma push_macro("err_stream")
#pragma push_macro("out_stream")
#pragma push_macro("pstate")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#undef name
#undef key
#undef arg
#undef flags
#undef doc
#undef group
#undef state
#undef options
#undef parser
#undef args_doc
#undef children
#undef text
#undef help_filter
#undef argp_domain
#undef argp
#undef header
#undef root_argp
#undef argc
#undef argv
#undef next
#undef arg_num
#undef quoted
#undef input
#undef child_inputs
#undef hook
#undef err_stream
#undef out_stream
#undef pstate

struct argp;
struct argp_state;
struct argp_child;

struct argp_option {
	char const *name;  /* [0..1] Long name for the option (without the "-" or "--" prefixes) */
	int         key;   /* The key passed to `struct argp::parser' to indicate this option (when `isprint(key)', also doubles as a short option) */
	char const *arg;   /* [0..1] When non-null, this option takes an argument (in which case this is the name of the argument, as shown by `--help') */
	int         flags; /* Option flags (set of `OPTION_*') */
	char const *doc;   /* Documentation text for this option (when `name' and `key' are NULL/0, this is not indented and acts as a group header) */
	int         group; /* ??? */
};

typedef __errno_t (__LIBKCALL *__argp_parser_t)(int key, char *arg, struct argp_state *state);

struct argp {
	struct argp_option const *options;     /* [0..n] List of options (terminated by a 0-name,key,doc,group-entry) */
	__argp_parser_t           parser;      /* [0..1] Parser callback. */
	char const               *args_doc;    /* [0..1] Usage text (if needed, printed as "Usage: {args_doc.replace("\n", "\n  or:  ")}"). */
	char const               *doc;         /* ??? */
	struct argp_child const  *children;    /* [0..n] List of extra argp-parsers (treated as extensions to `options'; terminated by a `argp_child::argp==NULL' entry) */
	char        *(__LIBKCALL *help_filter)(int key, char const *text, void *input); /* [0..1] Filter function for help texts (must re-return `text', `NULL', or an malloc'd string) */
	char const               *argp_domain; /* [0..1] Value for `domainname' used in calls to `dgettext(3)' for translating strings (HINT: if NULL, `dgettext(3)' behaves like `gettext(3)'). */
};

struct argp_child {
	struct argp const *argp;   /* [1..1] Child argp descriptor. */
	int                flags;  /* ??? */
	char const        *header; /* ??? */
	int                group;  /* ??? */
};

struct argp_state {
	struct argp const *root_argp;    /* [1..1] The original root-argp. */
	int                argc;         /* Argument count. */
	char             **argv;         /* [1..1][0..argc] Argument vector. */
	int                next;         /* [<= argc] Index of next argument yet to be parsed in `argv' */
	unsigned int       flags;        /* Flags argument, as passed to `argp_parse(3)' (see argp_parse(3) for recognized flags) */
	unsigned int       arg_num;      /* Non-option argument number, incremented (and thus unique) after each call to `root_argp->parser(ARGP_KEY_ARG)' */
	int                quoted;       /* Index of the first argument after "--" (or `0' if "--" has not been encountered) */
	void              *input;        /* [?..?] Value of the `input' argument passed to `argp_parse(3)' */
	void             **child_inputs; /* ??? */
	void              *hook;         /* ??? */
	char              *name;         /* [0..1] Program name (defaults to `argv[0]' or `program_invocation_name') */
	__FILE            *err_stream;   /* [1..1] Output stream used as `stderr' */
	__FILE            *out_stream;   /* [1..1] Output stream used as `stdout' */
	void              *pstate;       /* ??? */
};

typedef void (__LIBKCALL *__argp_program_version_hook_t)(__FILE *__restrict __stream, struct argp_state *__restrict __state);

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("name")
#pragma pop_macro("key")
#pragma pop_macro("arg")
#pragma pop_macro("flags")
#pragma pop_macro("doc")
#pragma pop_macro("group")
#pragma pop_macro("state")
#pragma pop_macro("options")
#pragma pop_macro("parser")
#pragma pop_macro("args_doc")
#pragma pop_macro("children")
#pragma pop_macro("text")
#pragma pop_macro("help_filter")
#pragma pop_macro("argp_domain")
#pragma pop_macro("argp")
#pragma pop_macro("header")
#pragma pop_macro("root_argp")
#pragma pop_macro("argc")
#pragma pop_macro("argv")
#pragma pop_macro("next")
#pragma pop_macro("arg_num")
#pragma pop_macro("quoted")
#pragma pop_macro("input")
#pragma pop_macro("child_inputs")
#pragma pop_macro("hook")
#pragma pop_macro("err_stream")
#pragma pop_macro("out_stream")
#pragma pop_macro("pstate")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__SYSDECL_END
#endif /* __CC__ */


#endif /* !_BITS_CRT_ARGP_H */
