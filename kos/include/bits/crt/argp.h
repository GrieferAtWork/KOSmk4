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
#ifndef _BITS_CRT_ARGP_H
#define _BITS_CRT_ARGP_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <asm/os/errno.h>
#include <bits/types.h>

/* ??? */
#define __OPTION_ARG_OPTIONAL 0x1  /* ??? */
#define __OPTION_HIDDEN       0x2  /* ??? */
#define __OPTION_ALIAS        0x4  /* ??? */
#define __OPTION_DOC          0x8  /* ??? */
#define __OPTION_NO_USAGE     0x10 /* ??? */

/* ??? */
#define __ARGP_ERR_UNKNOWN __E2BIG /* ??? */

/* ??? */
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

/* ??? */
#define __ARGP_PARSE_ARGV0 0x01 /* ??? */
#define __ARGP_NO_ERRS     0x02 /* ??? */
#define __ARGP_NO_ARGS     0x04 /* ??? */
#define __ARGP_IN_ORDER    0x08 /* ??? */
#define __ARGP_NO_HELP     0x10 /* ??? */
#define __ARGP_NO_EXIT     0x20 /* ??? */
#define __ARGP_LONG_ONLY   0x40 /* ??? */
#define __ARGP_SILENT      (__ARGP_NO_EXIT | __ARGP_NO_ERRS | __ARGP_NO_HELP) /* ??? */

/* ??? */
#define __ARGP_HELP_USAGE       0x01 /* ??? */
#define __ARGP_HELP_SHORT_USAGE 0x02 /* ??? */
#define __ARGP_HELP_SEE         0x04 /* ??? */
#define __ARGP_HELP_LONG        0x08 /* ??? */
#define __ARGP_HELP_PRE_DOC     0x10 /* ??? */
#define __ARGP_HELP_POST_DOC    0x20 /* ??? */
#define __ARGP_HELP_DOC         (__ARGP_HELP_PRE_DOC | __ARGP_HELP_POST_DOC) /* ??? */
#define __ARGP_HELP_BUG_ADDR    0x40  /* ??? */
#define __ARGP_HELP_LONG_ONLY   0x80  /* ??? */
#define __ARGP_HELP_EXIT_ERR    0x100 /* ??? */
#define __ARGP_HELP_EXIT_OK     0x200 /* ??? */
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
#pragma push_macro("options")
#pragma push_macro("parser")
#pragma push_macro("args_doc")
#pragma push_macro("children")
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
#undef options
#undef parser
#undef args_doc
#undef children
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
	char const *name;
	int         key;
	char const *arg;
	int         flags;
	char const *doc;
	int         group;
};

typedef __errno_t (__LIBKCALL *__argp_parser_t)(int __key, char *__arg, struct argp_state *__state);

struct argp {
	struct argp_option const *options;
	__argp_parser_t           parser;
	char const               *args_doc;
	char const               *doc;
	struct argp_child const  *children;
	char        *(__LIBKCALL *help_filter)(int __key, char const *__text, void *__input);
	char const               *argp_domain;
};

struct argp_child {
	struct argp const *argp;
	int                flags;
	char const        *header;
	int                group;
};

struct argp_state {
	struct argp const *root_argp;
	int                argc;
	char             **argv;
	int                next;
	unsigned           flags;
	unsigned           arg_num;
	int                quoted;
	void              *input;
	void             **child_inputs;
	void              *hook;
	char              *name;
	__FILE            *err_stream;
	__FILE            *out_stream;
	void              *pstate;
};

typedef void (__LIBKCALL *__argp_program_version_hook_t)(__FILE *__restrict __stream, struct argp_state *__restrict __state);

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("name")
#pragma pop_macro("key")
#pragma pop_macro("arg")
#pragma pop_macro("flags")
#pragma pop_macro("doc")
#pragma pop_macro("group")
#pragma pop_macro("options")
#pragma pop_macro("parser")
#pragma pop_macro("args_doc")
#pragma pop_macro("children")
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
