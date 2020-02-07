/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.remove("-O3"))
	gcc_opt.append("-Os");
]]]*/
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_DEBUGGER_APPS_DBG_MAIN_C
#define GUARD_KERNEL_SRC_DEBUGGER_APPS_DBG_MAIN_C 1
#define DISABLE_BRANCH_PROFILING 1
#define _KOS_SOURCE 1 /* fuzzy_strcasecmp() */

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_DEBUGGER
#include <debugger/function.h>
#include <debugger/io.h>
#include <debugger/rt.h>
#include <kernel/except.h>

#include <kos/kernel/cpu-state.h>

#include <ctype.h>
#include <stddef.h>
#include <string.h>
#include <unicode.h>

DECL_BEGIN

INTDEF struct debug_function const __kernel_debug_functions_start[];
INTDEF struct debug_function const __kernel_debug_functions_end[];
INTDEF byte_t __kernel_debug_functions_size[];

/* Search for a debug function matching the given name.
 * @return: NULL: No function exists that matches `name' */
PUBLIC ATTR_DBGTEXT WUNUSED ATTR_PURE NONNULL((1))
struct debug_function const *KCALL
dbg_getfunc(char const *__restrict name) {
	struct debug_function const *iter;
	/* XXX: Maybe use a hash table? */
	for (iter = __kernel_debug_functions_start;
	     iter < __kernel_debug_functions_end; ++iter) {
		if (strcmp(iter->df_name, name) == 0)
			return iter;
	}
	return NULL;
}

/* Search for a debug function matching the given name most closely. */
PUBLIC ATTR_DBGTEXT WUNUSED ATTR_PURE NONNULL((1)) struct debug_function const *KCALL
dbg_getfunc_fuzzy(char const *__restrict name) {
	struct debug_function const *result = __kernel_debug_functions_start;
	struct debug_function const *iter;
	size_t score = (size_t)-1;
	for (iter = __kernel_debug_functions_start;
	     iter < __kernel_debug_functions_end; ++iter) {
		size_t new_score;
		new_score = fuzzy_strcasecmp(iter->df_name, name);
		if (new_score < score) {
			score  = new_score;
			result = iter;
		}
	}
	return result;
}

/* Search for a debug function who's name starts with `name'. */
PUBLIC ATTR_DBGTEXT WUNUSED ATTR_PURE NONNULL((1)) struct debug_function const *KCALL
dbg_getfunc_start(char const *__restrict name) {
	struct debug_function const *result = NULL;
	struct debug_function const *iter;
	size_t score    = (size_t)-1;
	size_t name_len = strlen(name);
	bool is_ambig   = false;
	for (iter = __kernel_debug_functions_start;
	     iter < __kernel_debug_functions_end; ++iter) {
		size_t new_score;
		size_t funclen    = strlen(iter->df_name);
		size_t comparelen = funclen;
		if (comparelen > name_len)
			comparelen = name_len;
		if (memcmp(iter->df_name, name, comparelen * sizeof(char)) != 0)
			continue;
		new_score = name_len >= funclen
		            ? name_len - funclen
		            : funclen - name_len;
		if (new_score < score) {
			is_ambig = false;
			score    = new_score;
			result   = iter;
		} else if (new_score == score) {
			is_ambig = true;
		}
	}
	if (is_ambig)
		result = NULL;
	return result;
}


PUBLIC ATTR_DBGTEXT NONNULL((1)) size_t
NOTHROW(KCALL dbg_autocomplete_command)(char *__restrict line,
                                        size_t bufsize,
                                        size_t num_written) {
	char *word_start;
	struct debug_function const *func;
	size_t namelen, maxbuf;
	word_start = line + num_written;
	while (word_start > line) {
		char32_t ch;
		char *temp = word_start;
		ch = unicode_readutf8_rev((char const **)&temp);
		if (unicode_isspace(ch))
			break;
		word_start = temp;
	}
	line[num_written] = '\0';
	func              = dbg_getfunc_start(word_start);
	if (!func)
		return 0;
	namelen = strlen(func->df_name);
	if (namelen < num_written - (size_t)(word_start - line))
		return 0;
	maxbuf = (size_t)((line + bufsize) - word_start);
	if (namelen > maxbuf)
		namelen = maxbuf;
	memcpy(word_start, func->df_name, namelen * sizeof(char));
	return ((size_t)(word_start - line) + namelen) - num_written;
}


PRIVATE ATTR_DBGTEXT uintptr_t DBG_CALL
debug_exit(size_t argc, char *argv[]) {
	(void)argc;
	(void)argv;
	return 0;
}

REGISTER_DEBUG_FUNCTION_EX(
		"exit",
		"exit\n"
		"\tExit debugger mode and resume execution\n",
		debug_exit);

DEFINE_DEBUG_FUNCTION(
		"help",
		"help\n"
		"\tDisplay a list of available commands\n"
		"help command\n"
		"\tDisplay help specific to " DF_WHITE("command") "\n"
		, argc, argv) {
	--argc;
	++argv;
	if (!argc) {
		struct debug_function const *iter;
		size_t max_name_length;
		unsigned int i, commands_per_line = 1;
		dbg_print(DBGSTR("Available commands (type "
		                 DF_SETFGCOLOR(DBG_COLOR_WHITE)
		                 "help <command>" DF_DEFFGCOLOR
		                 " for more details)\n"));
		max_name_length = 1;
		for (iter = __kernel_debug_functions_start;
		     iter < __kernel_debug_functions_end; ++iter) {
			size_t temp = strlen(iter->df_name);
			if (max_name_length < temp)
				max_name_length = temp;
		}
		commands_per_line = dbg_screen_width / (max_name_length + 1);
		if unlikely(!commands_per_line) {
			commands_per_line = 1;
		}
		max_name_length   = dbg_screen_width / commands_per_line;
		i                 = 0;
		for (iter = __kernel_debug_functions_start;
		     iter < __kernel_debug_functions_end; ++iter) {
			dbg_printf(DBGSTR(DF_WHITE("%?-s")), max_name_length, iter->df_name);
			if ((i % commands_per_line) == (commands_per_line - 1))
				dbg_putc('\n');
			++i;
		}
		if (((i - 1) % commands_per_line) != (commands_per_line - 1))
			dbg_putc('\n');
	} else {
		while (argc) {
			struct debug_function const *func;
			func = dbg_getfunc(*argv);
			if (!func) {
				func = dbg_getfunc_fuzzy(*argv);
				dbg_printf(DBGSTR("Unknown command " DF_SETCOLOR(DBG_COLOR_LIGHT_GRAY, DBG_COLOR_MAROON) "%#q" DF_DEFCOLOR
				                  " (Did you mean " DF_SETFGCOLOR(DBG_COLOR_WHITE) "%s" DF_DEFFGCOLOR "?)\n"),
				           *argv, func->df_name);
			} else {
				dbg_printf(DF_SETFGCOLOR(DBG_COLOR_WHITE) "%s" DF_DEFFGCOLOR ":\n",
				           func->df_name);
				if (func->df_help) {
					dbg_print(func->df_help);
				} else {
					dbg_print(DBGSTR("\tNo help available\n"));
				}
			}
			--argc;
			++argv;
		}
	}
	return 0;
}


#define DBG_ARGC_MAX  32

PRIVATE char cmdline[DBG_MAXLINE];
PRIVATE char *argv[DBG_ARGC_MAX];



/* Split the given commandline and store the arguments in `argv' */
PRIVATE size_t KCALL
split_cmdline(char *__restrict cmdline,
              char **__restrict argv,
              size_t argc_max) {
	size_t argi, i;
	size_t cmdline_len;
	if unlikely(!argc_max) {
		return 0;
	}
	/* Skip leading space. */
	while (isspace(*cmdline))
		++cmdline;
	/* Check for empty commandline. */
	if (!*cmdline)
		return 0;
	--argc_max;
	i = 0, argi = 1;
	cmdline_len = strlen(cmdline);
	argv[0]     = cmdline;
	for (;;) {
		char ch = cmdline[i];
		/* Escaped characters. */
		if (ch == '\\') {
			--cmdline_len;
			memmovedown(&cmdline[i],
			            &cmdline[i + 1],
			            cmdline_len - i,
			            sizeof(char));
			++i;
			if (i >= cmdline_len)
				break;
			continue;
		}
		/* String arguments. */
		if (ch == '\'' || ch == '\"') {
			char end_ch = ch;
			--cmdline_len;
			memmovedown(&cmdline[i],
			            &cmdline[i + 1],
			            cmdline_len - i,
			            sizeof(char));
			while (i < cmdline_len) {
				ch = cmdline[i];
				if (ch == '\\') {
					--cmdline_len;
					memmovedown(&cmdline[i],
					            &cmdline[i + 1],
					            cmdline_len - i,
					            sizeof(char));
					++i;
					if (i >= cmdline_len)
						break;
					continue;
				}
				if (ch == end_ch) {
					--cmdline_len;
					memmovedown(&cmdline[i],
					            &cmdline[i + 1],
					            cmdline_len - i,
					            sizeof(char));
					break;
				}
				++i;
			}
			if (i >= cmdline_len)
				break;
			continue;
		}
		/* Space -> Argument separator. */
		if (isspace(ch)) {
			cmdline[i] = '\0'; /* Terminate the previous argument. */
			++i;
			/* Skip multiple consecutive spaces. */
			while (i < cmdline_len && isspace(cmdline[i]))
				++i;
			if (i >= cmdline_len)
				break;
			/* Start a new argument. */
			argv[argi] = &cmdline[i];
			++argi;
			if (argi >= argc_max) {
				while (cmdline_len && isspace(cmdline[cmdline_len - 1]))
					--cmdline_len;
				cmdline[cmdline_len] = '\0';
				break;
			}
			continue;
		}
		++i;
		if (i >= cmdline_len)
			break;
	}
	/* Always terminate argv with a NULL entry. */
	argv[argi] = NULL;
	return argi;
}



PUBLIC void KCALL
dbg_main(uintptr_t show_welcome) {
	/* The main entry function for the debugger.
	 * Called once the debugger context of single-core + no preemptive interrupts has setup. */
	if (show_welcome) {
		dbg_print(DBGSTR("Use CTRL + SHIFT + UP/DOWN/PAGE_UP/PAGE_DOWN/HOME/END to scroll\n"
		                 "Type " DF_SETFGCOLOR(DBG_COLOR_WHITE) "help" DF_DEFFGCOLOR
		                 " for a list of commands\n"));
	}
	for (;;) {
		dbg_attr_t attr;
		size_t argc;
		struct debug_function const *cmd;
		/* Force-enable render-to-screen. */
		dbg_endupdate(true);
		/* Add a visual indicator for when the exit state doesn't match the currently
		 * viewed state (thus informing the user that they need to type `apply' before
		 * exit if they wish to return to the modified state) */
		if (dbg_changedview())
			dbg_print(DBGSTR(DF_COLOR(DBG_COLOR_LIME, DBG_COLOR_DARK_GRAY, "!")));
		dbg_print(DBGSTR("> "));
		attr = dbg_attr;
		dbg_setfgcolor(DBG_COLOR_WHITE);
		dbg_setcur_visible(true);
		dbg_readline(cmdline, DBG_MAXLINE, &dbg_autocomplete_command);
		dbg_setcur_visible(false);
		dbg_attr = attr;
		argc     = split_cmdline(cmdline, argv, DBG_ARGC_MAX);
		if (!argc)
			continue;
		cmd = dbg_getfunc(argv[0]);
		if unlikely(!cmd) {
			cmd = dbg_getfunc_fuzzy(argv[0]);
			dbg_print(DBGSTR("Unknown command "));
			attr = dbg_attr;
			dbg_setcolor(DBG_COLOR_LIGHT_GRAY, DBG_COLOR_MAROON);
			dbg_printf(DBGSTR("%#q"), argv[0]);
			dbg_attr = attr;
			dbg_print(DBGSTR(" (did you mean "));
			attr = dbg_attr;
			dbg_setfgcolor(DBG_COLOR_WHITE);
			dbg_print(cmd->df_name);
			dbg_attr = attr;
			dbg_print(DBGSTR("?)\n"));
			continue;
		}
		if (cmd->df_main == &debug_exit)
			break;
		TRY {
			(*cmd->df_main)(argc, argv);
		} EXCEPT {
			error_print_into(&dbg_printer, NULL);
		}
	}
}


DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_DEBUGGER_APPS_DBG_MAIN_C */
