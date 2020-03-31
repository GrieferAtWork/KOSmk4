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
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_DEBUGGER
#include <debugger/function.h>
#include <debugger/io.h>
#include <debugger/rt.h>
#include <debugger/util.h>
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
		size_t funclen = strlen(iter->df_name);
		if (funclen < name_len)
			continue;
		if (memcmp(iter->df_name, name, name_len * sizeof(char)) != 0)
			continue;
		new_score = name_len - funclen;
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


PRIVATE ATTR_DBGTEXT NONNULL((1)) size_t
NOTHROW(KCALL dbg_autocomplete)(char *__restrict line,
                                size_t bufsize,
                                size_t cursor) {
	char *word_start, temp;
	struct debug_function const *func;
	size_t namelen, maxbuf;
	word_start = line + cursor;
	while (word_start > line) {
		char32_t ch;
		char *temp = word_start;
		ch = unicode_readutf8_rev((char const **)&temp);
		if (unicode_isspace(ch))
			break;
		word_start = temp;
	}
	temp = line[cursor];
	line[cursor] = '\0';
	func = dbg_getfunc_start(word_start);
	line[cursor] = temp;
	if (!func)
		return cursor;
	namelen = strlen(func->df_name);
	if (namelen <= cursor - (size_t)(word_start - line))
		return cursor;
	maxbuf = (size_t)((line + bufsize) - word_start);
	if (namelen >= maxbuf)
		namelen = maxbuf - 1;
	memmoveup(word_start + namelen, line + cursor, bufsize - cursor);
	memcpy(word_start, func->df_name, namelen, sizeof(char));
	return (size_t)(word_start - line) + namelen;
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
			/* TODO: It would be nice if we printed commands in alphabetical order here... */
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


#define DBG_ARGC_MAX        16  /* Max # of different arguments. */
#define DBG_MAXLINE         128 /* Default max length of an input line */
#define DBG_MAXLINE_BACKLOG 512 /* Max # of bytes in the cmdline backlog */

PRIVATE ATTR_DBGBSS char cmdline[DBG_MAXLINE];
PRIVATE ATTR_DBGBSS char *argv[DBG_ARGC_MAX];


/* Debug commandline backlog (entries are separated by \0) */
PRIVATE ATTR_DBGBSS char cmdline_backlog[DBG_MAXLINE_BACKLOG];
PRIVATE ATTR_DBGBSS size_t cmdline_latest;    /* Start index of the latest/next entry */
PRIVATE ATTR_DBGBSS size_t cmdline_current;   /* Start index of the currently viewed entry */

/* true if the user first typed a cmdline, then used arrows to browse the
 * backlog without executing their newly typed command (in this case, the
 * command written before `cmdline_latest' was never actually executed) */
PRIVATE ATTR_DBGBSS bool cmdline_didsavetemp;

PRIVATE NOBLOCK ATTR_DBGTEXT void
NOTHROW(KCALL cmdline_backlog_append)(char const *cmdln, size_t len) {
	size_t avail;
	if (len >= DBG_MAXLINE_BACKLOG)
		return; /* Shouldn't happen! */
again:
	avail = DBG_MAXLINE_BACKLOG - cmdline_latest;
	if (len >= avail) {
		/* Delete the oldest backlog entry. */
		size_t oldest_len = strlen(cmdline_backlog);
		memmovedown(cmdline_backlog,
		            cmdline_backlog + oldest_len,
		            cmdline_latest - oldest_len,
		            sizeof(char));
		if (cmdline_current < oldest_len)
			cmdline_current = 0;
		else {
			cmdline_current -= oldest_len;
		}
		cmdline_latest -= oldest_len;
		cmdline_backlog[cmdline_latest] = '\0';
		goto again;
	}
	memcpy(&cmdline_backlog[cmdline_latest],
	       cmdln, len, sizeof(char));
	cmdline_backlog[cmdline_latest + len] = '\0';
	cmdline_latest += len + 1;
}

PRIVATE NOBLOCK ATTR_DBGTEXT void
NOTHROW(KCALL cmdline_backlog_try_appendcurrent)(void) {
	size_t cmdline_len = strlen(cmdline);
	if (cmdline_current != cmdline_latest) {
		char *cursel;
		/* Delete a temporarily saved commandline. */
		if (cmdline_didsavetemp) {
			char *tempstart;
			tempstart = (char *)memrend(cmdline_backlog, '\0', cmdline_latest - 1) + 1;
			cmdline_latest = (size_t)(tempstart - cmdline_backlog);
			cmdline_didsavetemp = false;
		}
		/* If the currently selected entry wasn't modified from its
		 * original, then don't re-add it to the backlog once again! */
		cursel = cmdline_backlog + cmdline_current;
		if (cmdline_len == strlen(cursel) &&
		    memcmp(cmdline, cursel, cmdline_len * sizeof(char)) == 0)
			return;
	}
	if (cmdline_len != 0)
		cmdline_backlog_append(cmdline, cmdline_len);
	cmdline_current = cmdline_latest;
}

PRIVATE NOBLOCK ATTR_DBGTEXT bool
NOTHROW(KCALL cmdline_backlog_prev)(void) {
	char *prev_cmdline;
	if (!cmdline_current)
		return false; /* The oldest possible entry is already selected. */
	if (cmdline_current == cmdline_latest && !cmdline_didsavetemp) {
		/* Save the current (incomplete) commandline. */
		cmdline_backlog_append(cmdline, strlen(cmdline));
		cmdline_didsavetemp = true;
	}
	prev_cmdline = (char *)memrend(cmdline_backlog, '\0', cmdline_current - 1) + 1;
	cmdline_current = (size_t)(prev_cmdline - cmdline_backlog);
	memcpy(cmdline, prev_cmdline, strlen(prev_cmdline) + 1, sizeof(char));
	return true;
}

PRIVATE NOBLOCK ATTR_DBGTEXT bool
NOTHROW(KCALL cmdline_backlog_next)(void) {
	char *next_cmdline, *cmdline_end;
	if (cmdline_current == cmdline_latest)
		return false;
	next_cmdline = strend(cmdline_backlog + cmdline_current) + 1;
	cmdline_current = (size_t)(next_cmdline - cmdline_backlog);
	if (cmdline_current > cmdline_latest)
		cmdline_current = cmdline_latest;
	/* Load this commandline. */
	cmdline_end = strend(next_cmdline);
	memcpy(cmdline, next_cmdline, (size_t)(cmdline_end - next_cmdline) + 1, sizeof(char));
	if ((cmdline_end + 1) >= cmdline_backlog + cmdline_latest && cmdline_didsavetemp) {
		cmdline_latest = (size_t)(next_cmdline - cmdline_backlog);
		cmdline_didsavetemp = false;
	}
	return true;
}




/* Split the given commandline and store the arguments in `argv' */
PRIVATE ATTR_DBGTEXT size_t KCALL
split_cmdline(char *__restrict cmdln,
              char **__restrict argv,
              size_t argc_max) {
	size_t argi, i;
	size_t cmdline_len;
	if unlikely(!argc_max) {
		return 0;
	}
	/* Skip leading space. */
	while (isspace(*cmdln))
		++cmdln;
	/* Check for empty commandline. */
	if (!*cmdln)
		return 0;
	--argc_max;
	i = 0, argi = 1;
	cmdline_len = strlen(cmdln);
	argv[0]     = cmdln;
	for (;;) {
		char ch = cmdln[i];
		/* Escaped characters. */
		if (ch == '\\') {
			--cmdline_len;
			memmovedown(&cmdln[i],
			            &cmdln[i + 1],
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
			memmovedown(&cmdln[i],
			            &cmdln[i + 1],
			            cmdline_len - i,
			            sizeof(char));
			while (i < cmdline_len) {
				ch = cmdln[i];
				if (ch == '\\') {
					--cmdline_len;
					memmovedown(&cmdln[i],
					            &cmdln[i + 1],
					            cmdline_len - i,
					            sizeof(char));
					++i;
					if (i >= cmdline_len)
						break;
					continue;
				}
				if (ch == end_ch) {
					--cmdline_len;
					memmovedown(&cmdln[i],
					            &cmdln[i + 1],
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
			cmdln[i] = '\0'; /* Terminate the previous argument. */
			++i;
			/* Skip multiple consecutive spaces. */
			while (i < cmdline_len && isspace(cmdln[i]))
				++i;
			if (i >= cmdline_len)
				break;
			/* Start a new argument. */
			argv[argi] = &cmdln[i];
			++argi;
			if (argi >= argc_max) {
				while (cmdline_len && isspace(cmdln[cmdline_len - 1]))
					--cmdline_len;
				cmdln[cmdline_len] = '\0';
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



PUBLIC ATTR_DBGTEXT void KCALL
dbg_main(uintptr_t show_welcome) {
	/* Reset the backlog */
	cmdline_backlog[0]  = '\0';
	cmdline_latest      = 0;
	cmdline_current     = 0;
	cmdline_didsavetemp = false;

	/* The main entry function for the debugger.
	 * Called once the debugger context of single-core + no preemptive interrupts was set up. */
	if (show_welcome) {
		dbg_print(DBGSTR("Use CTRL + SHIFT + UP/DOWN/PAGE_UP/PAGE_DOWN/HOME/END to scroll\n"
		                 "Type " DF_SETFGCOLOR(DBG_COLOR_WHITE) "help" DF_DEFFGCOLOR
		                 " for a list of commands\n"));
	}
	for (;;) {
		dbg_attr_t attr;
		size_t argc;
		uintptr_t errorcode;
		struct debug_function const *cmd;
		/* Force-enable render-to-screen. */
again_readline:
		dbg_endupdate(true);
		/* Add a visual indicator for when the exit state doesn't match the currently
		 * viewed state (thus informing the user that they need to type `apply' before
		 * exit if they wish to return to the modified state) */
		dbg_attr = dbg_default_attr;
		if (dbg_changedview())
			dbg_print(DBGSTR(DF_COLOR(DBG_COLOR_LIME, DBG_COLOR_DARK_GRAY, "!")));
		dbg_print(DBGSTR("> "));
		attr = dbg_attr;
		dbg_setcolor(DBG_COLOR_WHITE, DBG_COLOR_DARK_GRAY);
		dbg_setcur_visible(true);
		{
			unsigned int code, field_width;
			u32 cur = dbg_getcur();
			size_t cursor_pos, screen_left;
			cmdline[0] = '\0';
			/* Switch back to the latest entry in the backlog */
			cmdline_current = cmdline_latest;
/*continue_readline_sol:*/
			cursor_pos = screen_left = 0;
continue_readline:
			field_width = dbg_screen_width - DBG_GETCUR_X(cur);
			code = dbg_editfield(DBG_GETCUR_X(cur), DBG_GETCUR_Y(cur),
			                     field_width, cmdline, DBG_MAXLINE,
			                     &cursor_pos, &screen_left);
			switch (code) {

			case DBG_EDITFIELD_RETURN_ENTER:
				break;

			case DBG_EDITFIELD_RETURN_TAB:
				cursor_pos = dbg_autocomplete(cmdline, DBG_MAXLINE, cursor_pos);
				goto continue_readline;

			case DBG_EDITFIELD_RETURN_CTRL_C: {
				unsigned int curx;
				dbg_setcolor(DBG_COLOR_WHITE, DBG_COLOR_BLACK);
				dbg_draweditfield(DBG_GETCUR_X(cur), DBG_GETCUR_Y(cur),
				                  field_width, cmdline, DBG_MAXLINE,
				                  &cursor_pos, &screen_left);
				dbg_setcur(DBG_GETCUR_X(cur) + cursor_pos - screen_left,
				           DBG_GETCUR_Y(cur));
				curx = dbg_getcur_x();
				dbg_attr = dbg_default_attr;
				if (curx < dbg_screen_width - 2)
					dbg_print(DBGSTR("^C\n"));
				else if (curx == dbg_screen_width - 2)
					dbg_print(DBGSTR("^C"));
				else if (curx == dbg_screen_width - 1)
					dbg_putc('^');
				else {
					dbg_putc('\n');
				}
			}	goto again_readline;

			case DBG_EDITFIELD_RETURN_CTRL_D:
				return; /* Exit (logout) */

			case DBG_EDITFIELD_RETURN_UP:
				if (cmdline_backlog_prev()) {
continue_readline_eol:
					cursor_pos  = strlen(cmdline);
					screen_left = 0;
				}
				goto continue_readline;

			case DBG_EDITFIELD_RETURN_DOWN:
				if (cmdline_backlog_next())
					goto continue_readline_eol;
				goto continue_readline;

			default:
				goto continue_readline;
			}
			dbg_setcur_visible(false);
			dbg_setcolor(DBG_COLOR_WHITE, DBG_COLOR_BLACK);
			dbg_draweditfield(DBG_GETCUR_X(cur), DBG_GETCUR_Y(cur),
			                  field_width, cmdline, DBG_MAXLINE,
			                  &cursor_pos, &screen_left);
			dbg_putc('\n');
		}
		dbg_attr = attr;
		cmdline_backlog_try_appendcurrent();
		argc = split_cmdline(cmdline, argv, DBG_ARGC_MAX);
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
			errorcode = (*cmd->df_main)(argc, argv);
		} EXCEPT {
			error_print_into(&dbg_printer, NULL);
			errorcode = 1;
		}
		if (errorcode == DBG_FUNCTION_INVALID_ARGUMENTS) {
			dbg_print(DBGSTR(DF_SETCOLOR(DBG_COLOR_MAROON, DBG_COLOR_LIGHT_GRAY)
			                 "Invalid arguments" DF_RESETATTR "\n"));
		}
	}
}


DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_DEBUGGER_APPS_DBG_MAIN_C */
