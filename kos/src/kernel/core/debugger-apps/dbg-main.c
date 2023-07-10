/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif(x -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_KERNEL_SRC_DEBUGGER_APPS_DBG_MAIN_C
#define GUARD_KERNEL_SRC_DEBUGGER_APPS_DBG_MAIN_C 1
#define DISABLE_BRANCH_PROFILING
#define _KOS_SOURCE 1 /* fuzzy_strcasecmp() */
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/debugger.h>

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <kernel/except.h>

#include <hybrid/align.h>
#include <hybrid/overflow.h>

#include <kos/kernel/cpu-state.h>
#include <kos/keyboard.h>

#include <alloca.h>
#include <ctype.h>
#include <stddef.h>
#include <string.h>
#include <unicode.h>

DECL_BEGIN


/*[[[config CONFIG_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE = true
 * Always display a list above of the commandline containing the
 * names of all commands start with the currently entered  word.
 *
 * ```
 *   lsMOD   lsMEM   lsRAM
 *   lsBLK   lsCHR
 * $ ls_
 * ```
 *
 * Where uppercase letter are printed in a different color. (and _ is the cursor)
 * Without this  option,  this list  is  only  displayed after  TAB  is  pressed.
 * ]]]*/
#ifdef CONFIG_NO_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE
#undef CONFIG_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE
#elif !defined(CONFIG_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE)
#define CONFIG_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE
#elif (-CONFIG_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE - 1) == -1
#undef CONFIG_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE
#define CONFIG_NO_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE
#endif /* ... */
/*[[[end]]]*/


/* ColorConfiguration for the auto-completion box. */
#define AUTOCOMPLETE_CC_BADCMD     ANSITTY_CL_RED             /* Text-color for unmatched commands */
#define AUTOCOMPLETE_CC_BACKGROUND ANSITTY_CL_DARK_GRAY       /* Background color for the auto-completion box */
#define AUTOCOMPLETE_CC_MATCHFG    ANSITTY_CL_WHITE           /* Foreground color for matched text */
#define AUTOCOMPLETE_CC_MATCHBG    AUTOCOMPLETE_CC_BACKGROUND /* Background color for matched text */
#define AUTOCOMPLETE_CC_SUGGESTFG  ANSITTY_CL_LIGHT_GRAY      /* Foreground color for suggested text */
#define AUTOCOMPLETE_CC_SUGGESTBG  AUTOCOMPLETE_CC_BACKGROUND /* Background color for suggested text */



#define DBG_ARGC_MAX        16  /* Max # of different arguments. */
#define DBG_MAXLINE         128 /* Default max length of an input line */
#define DBG_MAXLINE_BACKLOG 512 /* Max # of bytes in the cmdline backlog */

PRIVATE ATTR_DBGBSS char cmdline[DBG_MAXLINE];
PRIVATE ATTR_DBGBSS char *argv[DBG_ARGC_MAX];


/* Split the given commandline and store the arguments in `argv'
 * @param: pincomplete: When non-NULL, set to true when the `cmdln'  ends
 *                      with an incomplete " or '-sequence, or a trailing
 *                      \-character */
PRIVATE ATTR_DBGTEXT size_t KCALL
split_cmdline(char *__restrict cmdln,
              char **__restrict argv,
              size_t argc_max,
              bool *pincomplete) {
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
			cmdln[cmdline_len] = 0;
			++i;
			if (i >= cmdline_len) {
break_incomplete:
				if (pincomplete)
					*pincomplete = true;
				break;
			}
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
			cmdln[cmdline_len] = 0;
			while (i < cmdline_len) {
				ch = cmdln[i];
				if (ch == '\\') {
					--cmdline_len;
					memmovedown(&cmdln[i],
					            &cmdln[i + 1],
					            cmdline_len - i,
					            sizeof(char));
					cmdln[cmdline_len] = 0;
					++i;
					if (i >= cmdline_len)
						goto break_incomplete;
					continue;
				}
				if (ch == end_ch) {
					--cmdline_len;
					memmovedown(&cmdln[i],
					            &cmdln[i + 1],
					            cmdline_len - i,
					            sizeof(char));
					cmdln[cmdline_len] = 0;
					break;
				}
				++i;
			}
			if (i >= cmdline_len)
				goto break_incomplete;
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





PRIVATE ATTR_USED ATTR_DBGTEXT void DBG_CALL
autocomplete_help(size_t argc, char *argv[],
                  dbg_autocomplete_cb_t cb, void *arg,
                  char const *starts_with,
                  size_t starts_with_len) {
	struct dbg_commandhook const *current;
	struct dbg_hookiterator iter;
	(void)argc;
	(void)argv;
	dbg_hookiterator_init(&iter);
	for (;;) {
		current = DBG_HOOKITERATOR_NEXT_FILTERED(&iter, DBG_HOOK_COMMAND);
		if (!current)
			break;
		if (bcmp(current->dc_name, starts_with, starts_with_len, sizeof(char)) != 0)
			continue; /* Skip this one */
		(*cb)(arg, current->dc_name, strlen(current->dc_name));
	}
	dbg_hookiterator_fini(&iter);
}

DBG_COMMAND(help, autocomplete_help, DBG_COMMANDHOOK_FLAG_AUTOEXCLUSIVE,
            "help\n"
            "\tDisplay a list of available commands\n"
            "help command\n"
            "\tDisplay help specific to " AC_WHITE("command") "\n",
            argc, argv) {
	--argc;
	++argv;
	if (!argc) {
		struct dbg_commandhook const *current;
		struct dbg_hookiterator iter;
		size_t max_name_length;
		unsigned int i, commands_per_line = 1;
		dbg_print(DBGSTR("Available commands (type "
		                 AC_FG(ANSITTY_CL_WHITE)
		                 "help <command>" AC_FGDEF
		                 " for more details)\n"));
		max_name_length = 1;
		dbg_hookiterator_init(&iter);
		for (;;) {
			size_t hooknamelen;
			current = DBG_HOOKITERATOR_NEXT_FILTERED(&iter, DBG_HOOK_COMMAND);
			if (!current)
				break;
			hooknamelen = strlen(current->dc_name);
			if (max_name_length < hooknamelen)
				max_name_length = hooknamelen;
		}
		dbg_hookiterator_fini(&iter);
		commands_per_line = dbg_screen_width / (max_name_length + 1);
		if unlikely(!commands_per_line) {
			commands_per_line = 1;
		}
		max_name_length = dbg_screen_width / commands_per_line;
		dbg_hookiterator_init(&iter);
		for (i = 0;;) {
			current = DBG_HOOKITERATOR_NEXT_FILTERED(&iter, DBG_HOOK_COMMAND);
			if (!current)
				break;
			/* XXX: It would be nice if we printed commands in alphabetical order here... */
			dbg_printf(DBGSTR(AC_WHITE("%?-s")), max_name_length, current->dc_name);
			if ((i % commands_per_line) == (commands_per_line - 1))
				dbg_putc('\n');
			++i;
		}
		dbg_hookiterator_fini(&iter);
		if (((i - 1) % commands_per_line) != (commands_per_line - 1))
			dbg_putc('\n');
	} else {
		while (argc) {
			struct dbg_commandhook const *command;
			command  = dbg_lookup_command(*argv);
			if (!command) {
				command = dbg_lookup_command_fuzzy(*argv);
				dbg_printf(DBGSTR("Unknown command " AC_COLOR(ANSITTY_CL_LIGHT_GRAY, ANSITTY_CL_MAROON) "%#q" AC_DEFCOLOR
				                  " (Did you mean " AC_FG(ANSITTY_CL_WHITE) "%s" AC_FGDEF "?)\n"),
				           *argv, command->dc_name);
			} else {
				char const *hookhelp;
				hookhelp = NULL;
				if (dbg_commandhook_hashelp(command))
					hookhelp = command->dc_help;
				dbg_printf(DBGSTR(AC_FG(ANSITTY_CL_WHITE) "%s" AC_FGDEF ":\n"),
				           command->dc_name);
				if (!hookhelp)
					hookhelp = DBGSTR("\tNo help available\n");
				dbg_print(hookhelp);
			}
			--argc;
			++argv;
		}
	}
	return 0;
}





struct dbg_autocomplete_cnt_cookie {
#define DBG_AUTOCOMPLETE_COMMON_MAXLEN (DBG_MAXLINE / 4)
	char   *acc_starts;    /* [1..1][const] Incomplete starting string. */
	size_t  acc_startslen; /* [const] Length of `acc_starts' */
	size_t  acc_count;     /* # of matching auto-completions */
	char    acc_common[DBG_AUTOCOMPLETE_COMMON_MAXLEN];
	                       /* First couple of character common to all completions.
	                        * Either NUL- or EOF-terminated. */
};

PRIVATE ATTR_DBGTEXT void DBG_CALL
dbg_autocomplete_countmatches(void *arg,
                              char const *name,
                              size_t namelen) {
	struct dbg_autocomplete_cnt_cookie *cookie;
	cookie = (struct dbg_autocomplete_cnt_cookie *)arg;
	if (namelen < cookie->acc_startslen)
		return; /* Not a match */
	if (bcmp(name, cookie->acc_starts, cookie->acc_startslen, sizeof(char)) != 0)
		return; /* Not a match */
	name += cookie->acc_startslen;
	namelen -= cookie->acc_startslen;
	if (cookie->acc_count == 0) {
		/* First entry. */
		if (namelen > DBG_AUTOCOMPLETE_COMMON_MAXLEN)
			namelen = DBG_AUTOCOMPLETE_COMMON_MAXLEN;
		memcpy(cookie->acc_common, name, namelen);
		if (namelen < DBG_AUTOCOMPLETE_COMMON_MAXLEN)
			cookie->acc_common[namelen] = '\0';
	} else {
		size_t i;
		for (i = 0; i < DBG_AUTOCOMPLETE_COMMON_MAXLEN; ++i) {
			if (cookie->acc_common[i] != name[i]) {
				cookie->acc_common[i] = '\0'; /* Different text. */
				break;
			}
		}
	}
	++cookie->acc_count;
}

struct dbg_autocomplete_ins_cookie {
	char   *acc_starts;    /* [1..1][const] Incomplete starting string. */
	size_t  acc_startslen; /* [const] Length of `acc_starts' */
	char   *acc_dest;      /* [0..1] Destination buffer (cleared to NULL after the insert) */
	size_t  acc_destavl;   /* [IN] Available buffer size in `acc_dest' */
	size_t  acc_destdel;   /* [IN] # of characters to delete at `acc_dest' */
	size_t  acc_destmov;   /* [IN] # of characters to keep after `acc_dest' */
	size_t  acc_destreq;   /* [OUT] Required buffer size in `acc_dest' */
};

PRIVATE ATTR_DBGTEXT void DBG_CALL
dbg_autocomplete_insertmatch(void *arg,
                             char const *name,
                             size_t namelen) {
	struct dbg_autocomplete_ins_cookie *cookie;
	cookie = (struct dbg_autocomplete_ins_cookie *)arg;
	if (!cookie->acc_dest)
		return; /* Already inserted. */
	if (namelen < cookie->acc_startslen)
		return; /* Not a match */
	if (bcmp(name, cookie->acc_starts, cookie->acc_startslen, sizeof(char)) != 0)
		return; /* Not a match */
	cookie->acc_destreq = namelen;
	if (namelen <= cookie->acc_destavl) {
		memmovedown(cookie->acc_dest,
		            cookie->acc_dest + cookie->acc_destdel,
		            cookie->acc_destmov, sizeof(char));
		memmoveup(cookie->acc_dest + namelen,
		          cookie->acc_dest,
		          cookie->acc_destmov, sizeof(char));
		memcpy(cookie->acc_dest, name, namelen, sizeof(char));
		cookie->acc_dest[namelen + cookie->acc_destmov] = '\0';
	}
	cookie->acc_dest = NULL;
}

PRIVATE ATTR_DBGTEXT void DBG_CALL
dbg_autocomplete_longestmatch(void *arg,
                              char const *name,
                              size_t namelen) {
	struct dbg_autocomplete_cnt_cookie *cookie;
	cookie = (struct dbg_autocomplete_cnt_cookie *)arg;
	if (namelen < cookie->acc_startslen)
		return; /* Not a match */
	if (bcmp(name, cookie->acc_starts, cookie->acc_startslen, sizeof(char)) != 0)
		return; /* Not a match */
	if (cookie->acc_count < namelen)
		cookie->acc_count = namelen;
}

struct dbg_autocomplete_prn_cookie {
	char        *acc_starts;         /* [1..1][const] Incomplete starting string. */
	size_t       acc_startslen;      /* [const] Length of `acc_starts' */
	unsigned int acc_match_count;    /* Max # of remaining matches to print. */
	unsigned int acc_match_width;    /* [!0][const] Max width of a single match +1 / width of a column
	                                  * NOTE: longer matches are truncated and extended with `...' */
	unsigned int acc_matchlist_x;    /* [const] Starting X-offset of the match list. */
	unsigned int acc_matchlist_cury; /* Current output line Y. */
	int          acc_matchlist_nxty; /* [const] Offset to the next output line. */
	unsigned int acc_matchlist_colx; /* [< acc_matchlist_colc] Current column index */
	unsigned int acc_matchlist_col0; /* [const] Cloumn index with which to start a line */
	unsigned int acc_matchlist_colc; /* [!0][const] # of horizontal columns in use */
};

PRIVATE ATTR_DBGTEXT void DBG_CALL
dbg_autocomplete_matchlist(void *arg,
                           char const *name,
                           size_t namelen) {
	struct dbg_autocomplete_prn_cookie *cookie;
	dbg_pprinter_arg_t printer;
	size_t unmatched_length;
	cookie = (struct dbg_autocomplete_prn_cookie *)arg;
	if (namelen < cookie->acc_startslen)
		return; /* Not a match */
	if (bcmp(name, cookie->acc_starts, cookie->acc_startslen, sizeof(char)) != 0)
		return; /* Not a match */
	if (!cookie->acc_match_count)
		return; /* No space for any more matches. */
	unmatched_length = namelen - cookie->acc_startslen;
	dbg_pprinter_arg_init(&printer,
	                      cookie->acc_matchlist_x +
	                      cookie->acc_matchlist_colx *
	                      cookie->acc_match_width,
	                      cookie->acc_matchlist_cury);
	if likely(namelen <= cookie->acc_match_width - 1) {
		/* Print the matched portion in a different color. */
		dbg_setcolor(AUTOCOMPLETE_CC_MATCHFG, AUTOCOMPLETE_CC_MATCHBG);
		dbg_pprinter(&printer, name, cookie->acc_startslen);
do_print_unmatched:
		dbg_setcolor(AUTOCOMPLETE_CC_SUGGESTFG, AUTOCOMPLETE_CC_SUGGESTBG);
		dbg_pprinter(&printer, name + cookie->acc_startslen, unmatched_length);
	} else {
		/* Match is too long (truncate and extend with trailing `...') */
		unsigned int lenavail = cookie->acc_match_width - 1;
		bool print_dots = false;
		if unlikely(!lenavail)
			return; /* Shouldn't happen */
		if likely(lenavail >= 3) {
			lenavail -= 3;
			print_dots = true;
		}
		if (cookie->acc_startslen <= lenavail) {
			/* The matched portion cannot be printed completely. */
			dbg_setcolor(AUTOCOMPLETE_CC_MATCHFG, AUTOCOMPLETE_CC_MATCHBG);
			dbg_pprinter(&printer, name, lenavail);
		} else {
			dbg_setcolor(AUTOCOMPLETE_CC_MATCHFG, AUTOCOMPLETE_CC_MATCHBG);
			dbg_pprinter(&printer, name, cookie->acc_startslen);
			lenavail -= cookie->acc_startslen;
			if unlikely(lenavail >= unmatched_length)
				goto do_print_unmatched; /* Shouldn't happen... */
			dbg_setcolor(AUTOCOMPLETE_CC_SUGGESTFG, AUTOCOMPLETE_CC_SUGGESTBG);
			dbg_pprinter(&printer, name + cookie->acc_startslen, lenavail);
		}
		if (print_dots) {
			dbg_setcolor(AUTOCOMPLETE_CC_SUGGESTFG, AUTOCOMPLETE_CC_SUGGESTBG);
			dbg_pprinter(&printer, DBGSTR("..."), 3);
		}
	}
	/* Advance the  */
	--cookie->acc_match_count;
	++cookie->acc_matchlist_colx;
	if (cookie->acc_matchlist_colx >= cookie->acc_matchlist_colc)
		cookie->acc_matchlist_colx = 0; /* Wrap to start of line. */
	if (cookie->acc_matchlist_colx == cookie->acc_matchlist_col0)
		cookie->acc_matchlist_cury += cookie->acc_matchlist_nxty; /* Next line. */
}


/* Wait for user-input in the  form of a key-down event  (key-up
 * events are discarded), but don't consume that key-down event. */
PRIVATE ATTR_DBGTEXT void
NOTHROW(KCALL dbg_waitforinput)(void) {
	/* Wait for the user to press a button. */
	if (!dbg_hasuni() && !dbg_haschar()) {
		for (;;) {
			u16 key;
			key = dbg_getkey();
			if (KEY_ISDOWN(key)) {
				dbg_ungetkey(key);
				break;
			}
		}
	}
}


/* @param: insert_match: When true, insert a matched word when there is only one that matches.
 * @param: pbad_cmd:     Set to true if the written command is badly formatted. */
PRIVATE ATTR_DBGTEXT ATTR_NOINLINE size_t KCALL
dbg_autocomplete(size_t cursor,
                 u32 screen_cursor_pos
#ifdef CONFIG_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE
                 , bool *pbad_cmd
                 , bool insert_match
#endif /* CONFIG_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE */
                 ) {
	size_t argc, effective_argc;
	dbg_autocomplete_t autofun;
	uintptr_t func_flags;
	char *cmdline_copy;
	union {
		struct dbg_autocomplete_cnt_cookie cnt;
		struct dbg_autocomplete_ins_cookie ins;
		struct dbg_autocomplete_prn_cookie prn;
	} cookie;
	/* Set to `true' if the current word is incomplete (no
	 * trailing space, or incomplete ", ', or \-sequence). */
	bool incomplete_word;
	{
		size_t i = cursor;
		/* Don't do anything  if the  cursor is  at the  start of  the
		 * commandline, or is only preceded by white-space characters. */
		if (!cursor)
			goto done;
		do {
			--i;
			if (!isspace(cmdline[i]))
				goto do_autocomplete;
		} while (i);
		goto done;
	}
do_autocomplete:
	incomplete_word = false;
	cmdline_copy = (char *)alloca(cursor + 1);
	*(char *)mempcpy(cmdline_copy, cmdline, cursor) = '\0';
	argc = split_cmdline(cmdline_copy, argv, DBG_ARGC_MAX, &incomplete_word);
	if (!incomplete_word) {
		/* Check for trailing space in the original commandline. */
		if (!cursor || !isspace(cmdline[cursor - 1]))
			incomplete_word = true;
	}
	if (argc == 0 || (argc == 1 && incomplete_word)) {
		/* Auto-complete the name of a command
		 * -> Same as the auto-completion for `help' */
		autofun    = &autocomplete_help;
		func_flags = DBG_COMMANDHOOK_FLAG_AUTOEXCLUSIVE;
	} else {
		/* Auto-complete arguments for a command `argv[0]' */
		struct dbg_commandhook const *command;
		command = dbg_lookup_command(argv[0]);
		if unlikely(!command) {
			/* No such command (can't auto-complete).
			 * -> Re-print the command name in red */
setcolor_badcmd:
#ifdef CONFIG_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE
			if (pbad_cmd)
				*pbad_cmd = true;
#endif /* CONFIG_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE */
			goto done;
		}
		if (!dbg_commandhook_hasauto(command)) {
			if ((argc >= 2 || incomplete_word) &&
			    (command->dc_flag & DBG_COMMANDHOOK_FLAG_AUTOEXCLUSIVE))
				goto setcolor_badcmd;
			goto done; /* No auto-completion for this function... */
		}
		autofun    = command->dc_auto;
		func_flags = command->dc_flag;
	}
	effective_argc   = argc;
	if (incomplete_word) {
		if (!effective_argc)
			goto set_starts_empty_string;
		--effective_argc;
		cookie.cnt.acc_starts    = argv[effective_argc];
		cookie.cnt.acc_startslen = strlen(cookie.cnt.acc_starts);
		argv[effective_argc] = NULL;
	} else {
set_starts_empty_string:
		cookie.cnt.acc_starts    = strend(cmdline_copy);
		cookie.cnt.acc_startslen = 0;
	}
	/* Figure out how many options match. */
	cookie.cnt.acc_count = 0;
	(*autofun)(effective_argc, argv,
	           &dbg_autocomplete_countmatches, &cookie.cnt,
	           cookie.cnt.acc_starts, cookie.cnt.acc_startslen);
	if (cookie.cnt.acc_count == 0) {
		if (func_flags & DBG_COMMANDHOOK_FLAG_AUTOEXCLUSIVE)
			goto setcolor_badcmd;
		goto done; /* Nothing to do here! */
	}
#ifdef CONFIG_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE
	if (insert_match)
#endif /* CONFIG_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE */
	{
		if (cookie.cnt.acc_common[0] != '\0' &&
		    (memchr(cookie.cnt.acc_common, '\0', sizeof(cookie.cnt.acc_common)) != NULL ||
		     cookie.cnt.acc_count >= 2)) {
			size_t comlen, avail, postlen = strlen(cmdline + cursor);
			if (OVERFLOW_USUB(DBG_MAXLINE - 1, cursor + postlen, &avail))
				goto done; /* Shouldn't happen... */
			comlen = strnlen(cookie.cnt.acc_common, DBG_AUTOCOMPLETE_COMMON_MAXLEN);
			if (comlen > avail)
				comlen = avail;
			if unlikely(!comlen)
				goto done;
			memmoveup(cmdline + cursor + comlen, cmdline + cursor, postlen, sizeof(char));
			memcpy(cmdline + cursor, cookie.cnt.acc_common, comlen, sizeof(char));
			cmdline[cursor + comlen + postlen] = '\0';
			cursor += comlen;
			if (comlen == DBG_AUTOCOMPLETE_COMMON_MAXLEN)
				goto do_autocomplete;
			return cursor;
		} else if (cookie.cnt.acc_count == 1) {
			/* Auto-complete this single word. */
			size_t new_cursor;
			if unlikely(cursor < cookie.cnt.acc_startslen)
				goto done; /* shouldn't happen... */
			if unlikely(bcmp(cmdline + cursor - cookie.cnt.acc_startslen,
			                 cookie.cnt.acc_starts, cookie.cnt.acc_startslen,
			                 sizeof(char)) != 0)
				goto done; /* Shouldn't happen... */
			new_cursor = cursor - cookie.cnt.acc_startslen;
			if unlikely(new_cursor >= (DBG_MAXLINE - 1))
				goto done; /* Shouldn't happen... */
			cookie.ins.acc_destavl   = (DBG_MAXLINE - 1) - new_cursor;
			cookie.ins.acc_dest      = cmdline + new_cursor;
			cookie.ins.acc_destdel   = cookie.cnt.acc_startslen;
			cookie.ins.acc_destmov   = strlen(cmdline + cursor);
/*			cookie.ins.acc_starts    = cookie.cnt.acc_starts; */
/*			cookie.ins.acc_startslen = cookie.cnt.acc_startslen; */
			(*autofun)(effective_argc, argv,
			           &dbg_autocomplete_insertmatch, &cookie.ins,
			           cookie.ins.acc_starts, cookie.ins.acc_startslen);
			if unlikely(cookie.ins.acc_dest != NULL)
				goto done; /* shouldn't happen... (match no found) */
			if unlikely(cookie.ins.acc_destreq > cookie.ins.acc_destavl)
				goto do_print_options; /* Prevent overflow */
			new_cursor += cookie.ins.acc_destreq;
			return new_cursor;
		}
	}
do_print_options:
	/* Print a list of all available options and
	 * wait  until the user presses another key. */
	{
		size_t match_count;
		unsigned int matchlist_y, wordstart_x;
		unsigned int matchlist_sx, matchlist_sy;
		void *matchlist_screendata_backup;

		/* Figure out the length of the longest match. */
		match_count = cookie.cnt.acc_count;
		cookie.cnt.acc_count = 0;
		(*autofun)(effective_argc, argv,
		           &dbg_autocomplete_longestmatch, &cookie.cnt,
		           cookie.cnt.acc_starts, cookie.cnt.acc_startslen);
		if unlikely(!cookie.cnt.acc_count)
			goto done; /* Shouldn't happen... */
		cookie.prn.acc_match_width = (unsigned int)cookie.cnt.acc_count + 1; /* +1 for spacing between columns */

		if unlikely(cookie.prn.acc_match_width > dbg_screen_width)
			cookie.prn.acc_match_width = dbg_screen_width;
		if unlikely(!cookie.prn.acc_match_width)
			goto done; /* Shouldn't happen */
		/* Figure out where we want to print the match-list at. */
		wordstart_x = DBG_GETCUR_X(screen_cursor_pos);
		if (wordstart_x < cookie.cnt.acc_startslen)
			wordstart_x = cookie.cnt.acc_startslen; /* Current word is truncated. */
		wordstart_x -= cookie.cnt.acc_startslen;
		/* Figure out how many match columns we want to print. */
		cookie.prn.acc_matchlist_x = wordstart_x % cookie.prn.acc_match_width;
		matchlist_sx = dbg_screen_width - cookie.prn.acc_matchlist_x;
		if (matchlist_sx < cookie.prn.acc_match_width) {
set_fullwidth_print:
			if (cookie.prn.acc_match_width > dbg_screen_width)
				cookie.prn.acc_match_width = dbg_screen_width;
			matchlist_sx = cookie.prn.acc_match_width;
			cookie.prn.acc_matchlist_x = (dbg_screen_width - matchlist_sx) / 2;
			cookie.prn.acc_matchlist_colc = 1;
		} else {
			cookie.prn.acc_matchlist_colc = matchlist_sx / cookie.prn.acc_match_width;
			if (!cookie.prn.acc_matchlist_colc)
				goto set_fullwidth_print;
			matchlist_sx = cookie.prn.acc_matchlist_colc * cookie.prn.acc_match_width;
		}
		cookie.prn.acc_matchlist_col0 = (wordstart_x - cookie.prn.acc_matchlist_x) / cookie.prn.acc_match_width;
		cookie.prn.acc_matchlist_colx = cookie.prn.acc_matchlist_col0;
		matchlist_sy = CEILDIV(match_count, cookie.prn.acc_matchlist_colc);
		cookie.prn.acc_match_count = cookie.prn.acc_matchlist_colc * matchlist_sy;
		cookie.prn.acc_matchlist_cury = DBG_GETCUR_Y(screen_cursor_pos);
		if ((cookie.prn.acc_matchlist_cury + matchlist_sy <= dbg_screen_height) ||
			(cookie.prn.acc_matchlist_cury + 1 < dbg_screen_height / 2)) {
do_print_below:
			/* Print the list below the commandline */
			++cookie.prn.acc_matchlist_cury;
			matchlist_y = cookie.prn.acc_matchlist_cury;
			if unlikely(matchlist_y >= dbg_screen_height) {
				--cookie.prn.acc_matchlist_cury;
				if unlikely(!cookie.prn.acc_matchlist_cury)
					goto done; /* Shouldn't happen... */
				goto do_print_above;
			}
			cookie.prn.acc_matchlist_nxty = 1;
		} else {
			if unlikely(!cookie.prn.acc_matchlist_cury)
				goto do_print_below; /* Shouldn't happen... */
do_print_above:
			/* Print the list above the commandline */
			if (cookie.prn.acc_matchlist_cury < matchlist_sy) {
				/* Don't write past the top of the screen. */
				matchlist_sy = cookie.prn.acc_matchlist_cury;
				cookie.prn.acc_match_count = matchlist_sy * cookie.prn.acc_matchlist_colc;
			}
			matchlist_y = cookie.prn.acc_matchlist_cury - matchlist_sy;
			--cookie.prn.acc_matchlist_cury;
			cookie.prn.acc_matchlist_nxty = -1;
		}
		if (matchlist_y + matchlist_sy > dbg_screen_height) {
			/* Don't write past the end of the screen. */
			matchlist_sy = dbg_screen_height - matchlist_y;
			cookie.prn.acc_match_count = matchlist_sy * cookie.prn.acc_matchlist_colc;
		}
		/* Backup the screen-area containing the match list. */
		matchlist_screendata_backup = alloca(matchlist_sx * matchlist_sy * dbg_screen_cellsize);
		dbg_savecolor();
		dbg_beginupdate();
		dbg_getscreendata(cookie.prn.acc_matchlist_x, matchlist_y,
		                  matchlist_sx, matchlist_sy,
		                  matchlist_screendata_backup);
		dbg_setcolor(AUTOCOMPLETE_CC_BACKGROUND, AUTOCOMPLETE_CC_BACKGROUND);
		dbg_fillbox(cookie.prn.acc_matchlist_x, matchlist_y,
		            matchlist_sx, matchlist_sy, ' ');
		/* Print the match list. */
		(*autofun)(effective_argc, argv,
		           &dbg_autocomplete_matchlist, &cookie.prn,
		           cookie.prn.acc_starts, cookie.prn.acc_startslen);
		dbg_endupdate(true);
		/* Wait for the user to press a button. */
		dbg_waitforinput();
		/* Restore the screen-area we overwrote with the completion list. */
		dbg_setscreendata(cookie.prn.acc_matchlist_x, matchlist_y,
		                  matchlist_sx, matchlist_sy,
		                  matchlist_screendata_backup);
		/* Restore original output color */
		dbg_loadcolor();
	}
done:
	return cursor;
}



DBG_COMMAND(exit,
            "exit\n"
            "\tExit debugger mode and resume execution (same as pressing CTRL+D)\n") {
	dbg_exit();
}

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
		size_t oldest_len;
		oldest_len = strlen(cmdline_backlog) + 1;
		memmovedown(cmdline_backlog,
		            cmdline_backlog + oldest_len,
		            cmdline_latest - oldest_len,
		            sizeof(char));
		if (cmdline_current < oldest_len) {
			cmdline_current = 0;
		} else {
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
		/* If the currently selected entry wasn't modified from  its
		 * original, then don't re-add it to the backlog once again! */
		cursel = cmdline_backlog + cmdline_current;
		if (cmdline_len == strlen(cursel) &&
		    bcmp(cmdline, cursel, cmdline_len, sizeof(char)) == 0)
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




PUBLIC ATTR_DBGTEXT void KCALL
dbg_main(uintptr_t show_welcome) {
	NESTED_EXCEPTION;

	/* Reset the backlog */
	cmdline_backlog[0]  = '\0';
	cmdline_latest      = 0;
	cmdline_current     = 0;
	cmdline_didsavetemp = false;

	/* The main entry function for the debugger.
	 * Called once the debugger context of single-core + no preemptive interrupts was set up. */
	if (show_welcome) {
		dbg_print(DBGSTR("Use CTRL + SHIFT + UP/DOWN/PAGE_UP/PAGE_DOWN/HOME/END to scroll\n"
		                 "Type " AC_WHITE("help") " for a list of commands\n"));
	}
	for (;;) {
		size_t argc;
		intptr_t errorcode;
		struct dbg_commandhook const *cmd;
again_readline:
		/* Force-enable the await-user sub-system. */
		dbg_awaituser_end(true);
		dbg_awaituser_begin(DBG_AWAIT_GETC);

		/* Force-enable render-to-screen. */
		dbg_endupdate(true);
		/* Add a visual indicator for when the exit state doesn't match the  currently
		 * viewed state (thus informing the user that they need to type `apply' before
		 * exit if they wish to return to the modified state) */
		dbg_setcolor(dbg_getdefaultcolor());
		if (dbg_rt_changedview())
			dbg_print(DBGSTR(AC_WITHCOLOR(ANSITTY_CL_LIME, ANSITTY_CL_DARK_GRAY, "!")));
		dbg_print(DBGSTR("> "));
		dbg_savecolor();
		dbg_setcolor(ANSITTY_CL_WHITE, ANSITTY_CL_DARK_GRAY);
		dbg_setcur_visible(true);
		{
#ifdef CONFIG_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE
			bool should_print_autocomplete, did_press_tab;
#endif /* CONFIG_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE */
			unsigned int code, field_width;
			u32 cur = dbg_getcur();
			size_t cursor_pos, screen_left;
			cmdline[0] = '\0';
			/* Switch back to the latest entry in the backlog */
			cmdline_current = cmdline_latest;
/*continue_readline_sol:*/
			cursor_pos = screen_left = 0;
#ifdef CONFIG_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE
			should_print_autocomplete = true;
			did_press_tab             = false;
#endif /* CONFIG_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE */
continue_readline:
			field_width = dbg_screen_width - DBG_GETCUR_X(cur);
#ifdef CONFIG_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE
			if (should_print_autocomplete || did_press_tab) {
				bool badcmd = false;
				/* Don't  allow  auto-completion to  be aborted
				 * if we got here because the user pressed TAB! */
				if (did_press_tab)
					dbg_awaituser_end(true);
				TRY {
					cursor_pos = dbg_autocomplete(cursor_pos,
					                              DBG_MAKECUR(DBG_GETCUR_X(cur) + (cursor_pos -
					                                                               screen_left),
					                                          DBG_GETCUR_Y(cur)),
					                              &badcmd, did_press_tab);
				} EXCEPT {
					/* Handle exceptions during auto-complete */
					except_print_into(&dbg_printer, NULL);
					goto again_readline;
				}
				if (badcmd) {
					dbg_beginupdate();
					dbg_setcolor(AUTOCOMPLETE_CC_BADCMD, ANSITTY_CL_DARK_GRAY);
					dbg_draweditfield(DBG_GETCUR_X(cur), DBG_GETCUR_Y(cur),
					                  field_width, cmdline, DBG_MAXLINE,
					                  &cursor_pos, &screen_left);
					dbg_endupdate();
					/* Wait for the user to press a button. */
					dbg_waitforinput();
					dbg_setcolor(ANSITTY_CL_WHITE, ANSITTY_CL_DARK_GRAY);
				}
			}
			did_press_tab             = false;
			should_print_autocomplete = true;
#endif /* CONFIG_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE */
			code = dbg_editfield(DBG_GETCUR_X(cur), DBG_GETCUR_Y(cur),
			                     field_width, cmdline, DBG_MAXLINE,
			                     &cursor_pos, &screen_left,
#ifdef CONFIG_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE
			                     true
#else /* CONFIG_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE */
			                     false
#endif /* !CONFIG_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE */
			                     );
			switch (code) {

#ifdef CONFIG_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE
			case DBG_EDITFIELD_RETURN_ESC:
				/* Re-print while hiding the auto completion menu. */
				should_print_autocomplete = false;
				goto continue_readline;
#endif /* CONFIG_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE */

			case DBG_EDITFIELD_RETURN_ENTER:
				break;

			case DBG_EDITFIELD_RETURN_TAB:
#ifdef CONFIG_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE
				did_press_tab = true;
#else /* CONFIG_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE */
				cursor_pos = dbg_autocomplete(cursor_pos,
				                              DBG_MAKECUR(DBG_GETCUR_X(cur) + (cursor_pos -
				                                                               screen_left),
				                                          DBG_GETCUR_Y(cur)));
#endif /* !CONFIG_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE */
				goto continue_readline;

			case DBG_EDITFIELD_RETURN_CTRL_C: {
				unsigned int curx;
				dbg_setcolor(ANSITTY_CL_WHITE, ANSITTY_CL_BLACK);
				dbg_draweditfield(DBG_GETCUR_X(cur), DBG_GETCUR_Y(cur),
				                  field_width, cmdline, DBG_MAXLINE,
				                  &cursor_pos, &screen_left);
				dbg_setcur(DBG_GETCUR_X(cur) + cursor_pos - screen_left,
				           DBG_GETCUR_Y(cur));
				curx = dbg_getcur_x();
				dbg_setcolor(dbg_getdefaultcolor());
				if (curx < dbg_screen_width - 2) {
					dbg_print(DBGSTR("^C\n"));
				} else if (curx == dbg_screen_width - 2) {
					dbg_print(DBGSTR("^C"));
				} else if (curx == dbg_screen_width - 1) {
					dbg_putc('^');
				} else {
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
#ifdef CONFIG_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE
continue_readline_noauto:
				should_print_autocomplete = false;
				goto continue_readline;
#else /* CONFIG_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE */
#define continue_readline_noauto continue_readline
				goto continue_readline;
#endif /* !CONFIG_KERNEL_DEBUGGER_ALWAYS_SHOW_AUTOCOMLETE */

			case DBG_EDITFIELD_RETURN_DOWN:
				if (cmdline_backlog_next())
					goto continue_readline_eol;
				goto continue_readline_noauto;

			default:
				goto continue_readline;
			}
			dbg_setcur_visible(false);
			dbg_setcolor(ANSITTY_CL_WHITE, ANSITTY_CL_BLACK);
			dbg_draweditfield(DBG_GETCUR_X(cur), DBG_GETCUR_Y(cur),
			                  field_width, cmdline, DBG_MAXLINE,
			                  &cursor_pos, &screen_left);
			dbg_logecho(cmdline);
			dbg_putc('\n');
		}
		dbg_loadcolor();
		/* Force-disable the await-user sub-system. */
		dbg_awaituser_end(true);
		cmdline_backlog_try_appendcurrent();
		argc = split_cmdline(cmdline, argv, DBG_ARGC_MAX, NULL);
		if (!argc)
			continue;
		cmd = dbg_lookup_command(argv[0]);
		if unlikely(!cmd) {
			cmd = dbg_lookup_command_fuzzy(argv[0]);
			dbg_print(DBGSTR("Unknown command "));
			dbg_savecolor();
			dbg_setcolor(ANSITTY_CL_LIGHT_GRAY, ANSITTY_CL_MAROON);
			dbg_printf(DBGSTR("%#q"), argv[0]);
			dbg_loadcolor();
			dbg_print(DBGSTR(" (did you mean "));
			dbg_savecolor();
			dbg_setfgcolor(ANSITTY_CL_WHITE);
			dbg_print(cmd->dc_name);
			dbg_loadcolor();
			dbg_print(DBGSTR("?)\n"));
			continue;
		}
		TRY {
			errorcode = dbg_commandhook_exec(cmd, argc, argv);
		} EXCEPT {
			except_print_into(&dbg_printer, NULL);
			errorcode = 1;
		}
		if (errorcode == DBG_STATUS_INVALID_ARGUMENTS) {
			dbg_print(DBGSTR(AC_COLOR(ANSITTY_CL_MAROON, ANSITTY_CL_LIGHT_GRAY)
			                 "Invalid arguments" AC_DEFATTR "\n"));
		}
	}
}


DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_DEBUGGER_APPS_DBG_MAIN_C */
