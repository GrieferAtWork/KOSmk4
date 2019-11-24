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
#ifndef GUARD_KERNEL_SRC_DEBUGGER_EDIT_C
#define GUARD_KERNEL_SRC_DEBUGGER_EDIT_C 1
#define _KOS_SOURCE 1
#define DISABLE_BRANCH_PROFILING 1

#include <kernel/compiler.h>

#include <kernel/debugger.h>
#ifndef CONFIG_NO_DEBUGGER
#include <kos/keyboard.h>
#include <ctype.h>
#include <string.h>

DECL_BEGIN

PRIVATE ATTR_DBGBSS char shouldnt_happen[2];

PRIVATE ATTR_DBGTEXT void
NOTHROW(FCALL dbg_drawedit)(int x, int y, unsigned int field_width,
                            char *leftptr, char *textptr, char *endptr) {
	unsigned int textlen;
	unsigned int text_offset;
	textlen = (unsigned int)(endptr - leftptr);
	if unlikely(textlen > field_width)
		textlen = field_width;
	dbg_pprintf(x, y, "%$s", (size_t)textlen, leftptr);
	if (textlen < field_width) {
		unsigned int i;
		/* Fill in unused trailing space. */
		for (i = textlen; i < field_width; ++i)
			dbg_pputuni(x + i, y, ' ');
	}
	if (textptr < leftptr) {
do_hide_cursor:
		dbg_setcur_visible(DBG_SETCUR_VISIBLE_HIDE);
	} else {
		text_offset = (unsigned int)(textptr - leftptr);
		if unlikely(text_offset > field_width)
			goto do_hide_cursor;
		dbg_setcur(x + text_offset, y);
		dbg_setcur_visible(DBG_SETCUR_VISIBLE_SHOW);
	}
}

/* Process input for an edit field at the given position, allowing
 * the user to type in input text, with that text then being written
 * to the given `buf'.
 * Note that if `buf' is non-empty (buf[0] != '\0') upon entry,
 * editing will resume with the current contents of `buf'
 * @return: * : One of `DBG_EDITFIELD_RETURN_*' */
PUBLIC ATTR_DBGTEXT unsigned int
NOTHROW(FCALL dbg_editfield)(int x, int y, unsigned int field_width,
                             char *buf, size_t buflen) {
	char *screen_left, *pos, *endptr, *bufend;
	if unlikely(field_width < 2)
		field_width = 2;
	if unlikely(buflen < 2) {
		/* This really shouldn't happen... */
		buf    = shouldnt_happen;
		buflen = sizeof(shouldnt_happen);
		memset(shouldnt_happen, 0, sizeof(shouldnt_happen));
	}
	bufend = buf + buflen;
	screen_left = buf;
	buf[buflen - 1] = '\0';
	pos = endptr = strend(buf);
	for (;;) {
		char ch;
		size_t onscreen;
		unsigned int key;
		if (screen_left > pos)
			screen_left = pos;
		onscreen = (size_t)(pos - screen_left);
		if (onscreen > field_width - 1)
			screen_left = pos - (field_width - 1);
		dbg_drawedit(x, y, field_width, screen_left, pos, endptr);
		if (!dbg_hasuni()) {
			do {
				key = dbg_getkey();
			} while (key & KEY_FRELEASED);
			switch (key) {

			case KEY_ESC:
				return DBG_EDITFIELD_RETURN_ESC;
			case KEY_ENTER:
				return DBG_EDITFIELD_RETURN_ENTER;
			case KEY_TAB:
				if (dbg_isholding_shift())
					return DBG_EDITFIELD_RETURN_SHIFT_TAB;
				return DBG_EDITFIELD_RETURN_TAB;
			case KEY_F1 ... KEY_F10:
				return DBG_EDITFIELD_RETURN_F(1 + (key - KEY_F1));
			case KEY_F11 ... KEY_F12:
				return DBG_EDITFIELD_RETURN_F(11 + (key - KEY_F11));
			case KEY_F13 ... KEY_F24:
				return DBG_EDITFIELD_RETURN_F(13 + (key - KEY_F13));

			case KEY_BACKSPACE: {
				unsigned int n;
				if (pos <= buf) {
					dbg_bell();
					continue;
				}
				n = 1;
				if (dbg_isholding_ctrl()) {
					char *newend = pos;
					while (newend > buf && isspace(newend[-1]))
						--newend;
					while (newend > buf && !isspace(newend[-1]))
						--newend;
					n = (unsigned int)(pos - newend);
				}
				memmovedown(pos - n, pos,
				            (size_t)(endptr - pos),
				            sizeof(char));
				pos -= n;
				endptr -= n;
				*endptr = 0;
			}	continue;

			case KEY_DELETE: {
				unsigned int n;
				if (pos >= endptr) {
					dbg_bell();
					continue;
				}
				n = 1;
				if (dbg_isholding_ctrl()) {
					char *newend = pos;
					while (newend < endptr && !isspace(*newend))
						++newend;
					while (newend < endptr && isspace(*newend))
						++newend;
					n = (unsigned int)(newend - pos);
				}
				memmovedown(pos, pos + n,
				            (size_t)(endptr - pos),
				            sizeof(char));
				endptr -= n;
				*endptr = 0;
			}	continue;

			case KEY_LEFT: {
				unsigned int n;
				if (pos <= buf) {
					dbg_bell();
					continue;
				}
				n = 1;
				if (dbg_isholding_ctrl()) {
					char *newpos = pos;
					while (newpos > buf && isspace(newpos[-1]))
						--newpos;
					while (newpos > buf && !isspace(newpos[-1]))
						--newpos;
					n = (unsigned int)(pos - newpos);
				}
				pos -= n;
			}	continue;

			case KEY_RIGHT: {
				unsigned int n;
				if (pos >= endptr) {
					dbg_bell();
					continue;
				}
				n = 1;
				if (dbg_isholding_ctrl()) {
					char *newpos = pos;
					while (newpos < endptr && !isspace(*newpos))
						++newpos;
					while (newpos < endptr && isspace(*newpos))
						++newpos;
					n = (unsigned int)(newpos - pos);
				}
				pos += n;
			}	continue;

			case KEY_HOME:
				if (pos <= buf) {
					dbg_bell();
					continue;
				}
				pos = buf;
				continue;

			case KEY_END:
				if (pos >= endptr) {
					dbg_bell();
					continue;
				}
				pos = endptr;
				continue;

			case KEY_UP:
			case KEY_DOWN:
				continue;

			default:
				break;
			}
			dbg_purgeuni();
			dbg_ungetkey(key);
		}
		ch = dbg_trygetc();
		if (!ch)
			continue;
		if (endptr >= bufend) {
			dbg_bell();
			continue; /* Buffer is full */
		}
		memmoveup(pos + 1, pos,
		          (size_t)(endptr - pos),
		          sizeof(char));
		*pos++ = ch;
		++endptr;
		*endptr = 0;
	}
}



/* Same as `dbg_editfield()', but only draw the edit field. */
PUBLIC ATTR_DBGTEXT void
NOTHROW(FCALL dbg_draweditfield)(int x, int y, unsigned int field_width,
                                 char *buf, size_t buflen) {
	char *endptr;
	size_t onscreen;
	if unlikely(field_width < 2)
		field_width = 2;
	if unlikely(buflen < 2) {
		/* This really shouldn't happen... */
		buf    = shouldnt_happen;
		buflen = sizeof(shouldnt_happen);
		memset(shouldnt_happen, 0, sizeof(shouldnt_happen));
	}
	buf[buflen - 1] = '\0';
	endptr = strend(buf);
	onscreen = (size_t)(endptr - buf);
	if (onscreen > field_width - 1)
		buf = endptr - (field_width - 1);
	dbg_drawedit(x, y, field_width, buf, endptr, endptr);
}


DECL_END
#endif /* !CONFIG_NO_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_DEBUGGER_EDIT_C */
