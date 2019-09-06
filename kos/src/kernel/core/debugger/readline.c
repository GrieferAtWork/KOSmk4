/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.remove("-O3"))
	gcc_opt.append("-Os");
]]]*/
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_DEBUGGER_READLINE_C
#define GUARD_KERNEL_SRC_DEBUGGER_READLINE_C 1
#define DISABLE_BRANCH_PROFILING 1

#include <kernel/compiler.h>

#include <kernel/debugger.h>
#ifndef CONFIG_NO_DEBUGGER
#include <kos/keyboard.h>

#include <string.h>
#include <unicode.h>
#include <assert.h>

DECL_BEGIN



///* Buffer for input backlog. */
//PRIVATE char dbg_backlog_text[4096];

PUBLIC ATTR_DBGTEXT size_t KCALL
dbg_readline(/*utf-8*/char *__restrict buf,
             size_t bufsize,
             dbg_autocomplete_t autocomplete) {
	char ch;
	size_t count;
	if unlikely(!bufsize)
		return 0;
	--bufsize; /* Reserve for trailing \0 character. */
	count = 0;
	while (count < bufsize) {
		ch = dbg_getc();
		if (ch == '\b') {
			if (count) {
				dbg_print(DBGSTR("\b \b"));
				--count;
			}
			continue;
		}
		if (ch == '\t' && autocomplete) {
			size_t i, more_chars;
			more_chars = (*autocomplete)(buf, bufsize, count);
			assert(count + more_chars <= bufsize);
			/* Re-print the current line */
			for (i = 0; i < count; ++i)
				dbg_print(DBGSTR("\b \b"));
			count += more_chars;
			for (i = 0; i < count; ++i)
				dbg_putc(buf[i]);
			continue;
		}
		/* TODO: Support for history (UP/DOWN) & reverse search (CRTL+R) */
		dbg_putc(ch);
		buf[count] = ch;
		++count;
		if (ch == '\n')
			break;
	}
	buf[count] = '\0';
	return count;
}



DECL_END
#endif /* !CONFIG_NO_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_DEBUGGER_READLINE_C */
