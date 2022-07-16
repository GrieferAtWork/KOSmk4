/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif([](x) -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_DEBUGGER_APPS_HEXEDIT_C
#define GUARD_KERNEL_SRC_DEBUGGER_APPS_HEXEDIT_C 1
#define DISABLE_BRANCH_PROFILING
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <debugger/hook.h>
#include <debugger/io.h>
#include <debugger/rt.h>
#include <debugger/util.h>
#include <kernel/except.h>
#include <kernel/paging.h>
#include <kernel/types.h>

#include <hybrid/align.h>
#include <hybrid/byteorder.h>
#include <hybrid/byteswap.h>
#include <hybrid/unaligned.h>

#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/keyboard.h>

#include <alloca.h>
#include <ctype.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <libinstrlen/instrlen.h>

DECL_BEGIN

#define HD_REGION_ADDR  0 /* Address column is selected. */
#define HD_REGION_HEX   1 /* Low nibble is selected */
#define HD_REGION_ASCII 2 /* Ascii representation is selected */

#define HD_MAXLINESIZE 64


#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define HD_LE_DEFAULT 1
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
#define HD_LE_DEFAULT 0
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */




struct hd_change {
	byte_t                         *hc_start;  /* Starting address */
	u8                              hc_length; /* Number of changed bytes */
	COMPILER_FLEXIBLE_ARRAY(byte_t, hc_data);  /* [hc_length] The actual changed data. */
};

#define HD_CHANGE_NEXT(x) \
	(struct hd_change *)((x)->hc_data + CEIL_ALIGN((x)->hc_length, sizeof(void *)))


/* Buffer of pending memory changes. */
PRIVATE ATTR_DBGBSS byte_t hd_change_buffer[1024];
#define hd_change_buffer_init() \
	bzero(hd_change_buffer, offsetof(struct hd_change, hc_data))


PRIVATE ATTR_DBGTEXT bool
NOTHROW(FCALL hd_has_changes)(void) {
	struct hd_change *iter;
	iter = (struct hd_change *)hd_change_buffer;
	return iter->hc_length != 0;
}

PRIVATE ATTR_DBGTEXT void
NOTHROW(FCALL hd_discard_changes)(void) {
	hd_change_buffer_init();
}

PRIVATE ATTR_DBGTEXT bool
NOTHROW(FCALL hd_changes_commit)(void) {
	struct hd_change *iter;
	bool result = true;
	iter = (struct hd_change *)hd_change_buffer;
	while (iter->hc_length) {
		size_t i;
		for (i = 0; i < iter->hc_length; ++i) {
			byte_t *addr = iter->hc_start + i;
			if (dbg_writememory(addr, &iter->hc_data[i], 1, true) != 0)
				result = false;
		}
		iter = HD_CHANGE_NEXT(iter);
	}
	hd_change_buffer_init();
	return result;
}

PRIVATE ATTR_DBGTEXT bool
NOTHROW(FCALL hd_changes_append)(byte_t *addr, byte_t value) {
	struct hd_change *iter, *last_change;
	byte_t *block_start, *block_end;
	iter = (struct hd_change *)hd_change_buffer;
	/* Check if the given address overlaps with some existing change-block. */
	while (iter->hc_length) {
		block_start = iter->hc_start;
		block_end   = iter->hc_start + iter->hc_length;
		if (addr >= block_start && addr < block_end) {
			iter->hc_data[addr - block_start] = value;
			return true;
		}
		iter = HD_CHANGE_NEXT(iter);
	}
	last_change = iter;

	/* Check if the given address can be appended. */
	iter = (struct hd_change *)hd_change_buffer;
	while (iter->hc_length) {
		struct hd_change *next = HD_CHANGE_NEXT(iter);
		block_end = iter->hc_start + iter->hc_length;
		if (addr == block_end) {
			/* Append at the end of this change-block */
			if (&iter->hc_data[iter->hc_length] >= (byte_t *)next) {
				/* Must shift future changes before we can append to this one. */
				if (&last_change->hc_data[sizeof(void *)] > COMPILER_ENDOF(hd_change_buffer))
					return false;
				memmoveup((byte_t *)next + sizeof(void *), next,
				          (size_t)((byte_t *)last_change - (byte_t *)next));
			}
			iter->hc_data[iter->hc_length++] = value;
			return true;
		}
		iter = next;
	}
	/* Check if we can append a new change-block at the end. */
	if (((byte_t *)&last_change->hc_data + 1 +
	     offsetof(struct hd_change, hc_data)) >=
	    COMPILER_ENDOF(hd_change_buffer))
		return false;
	last_change->hc_start   = addr;
	last_change->hc_length  = 1;
	last_change->hc_data[0] = value;
	last_change             = HD_CHANGE_NEXT(last_change);
	last_change->hc_length  = 0;
	return true;
}

PRIVATE ATTR_DBGTEXT void
NOTHROW(FCALL hd_changes_applyto)(void const *addr, byte_t *buf,
                                  size_t buflen, u64 *pchanged) {
	struct hd_change *iter;
	byte_t const *endaddr;
	endaddr = (byte_t const *)addr + buflen;
	iter    = (struct hd_change *)hd_change_buffer;
	while (iter->hc_length) {
		byte_t *block_start, *block_end;
		block_start = iter->hc_start;
		block_end   = iter->hc_start + iter->hc_length;
		if (addr < block_end && endaddr > block_start) {
			size_t i;
			for (i = 0; i < buflen; ++i) {
				byte_t const *effective_address;
				effective_address = (byte_t const *)addr + i;
				if (effective_address < block_start)
					continue;
				if (effective_address >= block_end)
					continue;
				if (pchanged)
					*pchanged |= ((u64)1 << i);
				buf[i] = iter->hc_data[(size_t)(effective_address -
				                                block_start)];
			}
		}
		iter = HD_CHANGE_NEXT(iter);
	}
}


#define HD_SETDATA_LOW 0  /* Write low nibble */
#define HD_SETDATA_HIGH 1 /* Write high nibble */
#define HD_SETDATA_BOTH 2 /* Write low & high nibble */

PRIVATE ATTR_DBGTEXT char const *
NOTHROW(FCALL hd_setdata)(void *addr, unsigned int how, byte_t value) {
	byte_t newval;
	if (how == HD_SETDATA_BOTH) {
		newval = value;
	} else {
		if (dbg_readmemory(addr, &newval, 1) != 0)
			newval = 0;
		hd_changes_applyto((byte_t *)addr, &newval, 1, NULL);
		if (how == HD_SETDATA_LOW) {
			newval &= 0x0f;
			newval |= value << 4;
		} else {
			newval &= 0xf0;
			newval |= value & 0xf;
		}
	}
	if (!hd_changes_append((byte_t *)addr, newval))
		return DBGSTR("Too many changes made (must save before editing may continue)");
	return NULL;
}

PRIVATE ATTR_DBGBSS bool hd_hex_le = false; /* View hex in little-endian */

PRIVATE ATTR_DBGBSS unsigned int hd_hex_nibble       = 0; /* The current hex nibble (< hd_nibbles_per_word) */
PRIVATE ATTR_DBGBSS unsigned int hd_nibbles_per_word = 0; /* Max number of nibbles per word (2, 4, 8 or 16) */
#define hd_bytes_per_word (hd_nibbles_per_word / 2)
PRIVATE ATTR_DBGBSS unsigned int hd_linewords = 0; /* Number of words per line */
PRIVATE ATTR_DBGBSS unsigned int hd_linesize  = 0; /* Number of bytes per line (== hd_linewords * hd_bytes_per_word) */
PRIVATE ATTR_DBGBSS unsigned int hd_linealign = 0; /* Lowest power-of-two number which may be used to align an address */
PRIVATE ATTR_DBGBSS unsigned int hd_hexpad    = 0; /* Number of empty cells before the hex view */
PRIVATE ATTR_DBGBSS unsigned int hd_asciipad  = 0; /* Number of empty cells before the ascii view */


PRIVATE ATTR_DBGTEXT void
NOTHROW(FCALL dbg_calculate_linesize)(void);


/* Get the bytes for a given line of hex data.
 * @return: * : Bitset of valid bytes (usually 0xffff). */
PRIVATE ATTR_DBGTEXT u64 FCALL
hd_getline(void const *start_addr, byte_t data[HD_MAXLINESIZE], u64 *pchanged) {
	size_t error;
	u64 result = (u64)-1;
	error = dbg_readmemory(start_addr, data, hd_linesize);
	if unlikely(error != 0) {
		/* Something's wrong with the address. - Try to copy each byte individually. */
		unsigned int i;
		for (i = 0; i < hd_linesize; ++i) {
			void const *baddr;
			baddr = (byte_t const *)start_addr + i;
			error = dbg_readmemory(baddr, &data[i], 1);
			if (error != 0)
				result &= ~((u64)1 << i);
		}
	}
	hd_changes_applyto(start_addr, data, hd_linesize, pchanged);
	return result;
}


/* Convert a nibble index */
LOCAL ATTR_DBGTEXT ATTR_PURE unsigned int
NOTHROW(FCALL hd_convnibble)(unsigned int nibble, unsigned int sel_region) {
	if (hd_hex_le && sel_region == HD_REGION_HEX)
		nibble = (((hd_bytes_per_word - 1) - (nibble / 2)) * 2) + (nibble & 1);
	return nibble;
}

LOCAL ATTR_CONST ATTR_DBGTEXT char
NOTHROW(FCALL hd_tohex)(byte_t val, bool is_valid) {
	if (!is_valid)
		return '?';
	return _itoa_upper_digits[val];
}


/* @param: start_addr: Starting address (the first address displayed at the top-left)
 * @param: sel_addr:   The currently selected address.
 * @param: sel_region: The selected region (one of `HD_REGION_*') */
PRIVATE ATTR_DBGTEXT void FCALL
hd_printscreen(void *start_addr, void *sel_addr,
               unsigned int sel_region,
               char const *status,
               bool is_readonly) {
	unsigned int i, line, column_word, sel_byte, sel_column;
	byte_t line_data[HD_MAXLINESIZE];
	u64 line_valid, line_changed;
	u32 dst_cursor_pos     = (u32)-1;
	byte_t sel_word[8]     = { 0, 0, 0, 0, 0, 0, 0, 0 };
	bool sel_byte_is_valid = true;
	sel_byte   = (unsigned int)((uintptr_t)((byte_t *)sel_addr -
	                                        (byte_t *)start_addr) %
	                            hd_linesize);
	sel_column = sel_byte / hd_bytes_per_word;
	sel_byte += hd_hex_nibble / 2;
	/* Always hide the cursor during rendering. */
	dbg_setcur_visible(false);
	for (line = 0; line < dbg_screen_height - 1; ++line) {
		void *line_addr = (byte_t *)start_addr + line * hd_linesize;
		bool is_line_selected;
		is_line_selected = (byte_t *)sel_addr >= (byte_t *)line_addr &&
		                   (byte_t *)sel_addr < (byte_t *)line_addr + hd_linesize;
		line_changed = 0;
		line_valid   = hd_getline(line_addr, line_data, &line_changed);
		dbg_setcolor(dbg_getdefaultcolor());
		if (sel_region == HD_REGION_ADDR) {
			if (is_line_selected) {
				dbg_setcolor(ANSITTY_CL_BLACK, ANSITTY_CL_LIGHT_GRAY);
			} else {
				dbg_setbgcolor(ANSITTY_CL_DARK_GRAY);
			}
		} else {
			dbg_setbgcolor(ANSITTY_CL_BLACK);
		}
		dbg_setcur(0, line);
		dbg_printf(DBGSTR("%p"), line_addr);
		dbg_setcolor(dbg_getdefaultcolor());
		for (i = 0; i < hd_hexpad; ++i)
			dbg_putc(' ');
		/* Print the hex representation */
		for (column_word = 0; column_word < hd_linewords; ++column_word) {
#define VALID_BYTE(i)   ((line_valid & ((u64)1 << (i))) != 0)
#define CHANGED_BYTE(i) ((line_changed & ((u64)1 << (i))) != 0)
			bool is_valid = VALID_BYTE(column_word * hd_bytes_per_word);
			unsigned int nibble_byte;
			byte_t *pb = &line_data[column_word * hd_bytes_per_word];
			for (nibble_byte = 1; nibble_byte < hd_nibbles_per_word; ++nibble_byte) {
				if (!VALID_BYTE((column_word * hd_bytes_per_word) + nibble_byte)) {
					is_valid = false;
					break;
				}
			}
#undef VALID_BYTE
			if (column_word != 0)
				dbg_putc(' ');
			dbg_setcolor(dbg_getdefaultcolor());
			if (sel_region == HD_REGION_HEX) {
				if (column_word == sel_column || is_line_selected) {
					dbg_setcolor(ANSITTY_CL_BLACK, ANSITTY_CL_LIGHT_GRAY);
				} else {
					dbg_setbgcolor(ANSITTY_CL_DARK_GRAY);
				}
			} else {
				dbg_setbgcolor(ANSITTY_CL_BLACK);
			}
			if ((byte_t *)sel_addr >= ((byte_t *)line_addr + (column_word * hd_bytes_per_word)) &&
			    (byte_t *)sel_addr < ((byte_t *)line_addr + ((column_word + 1) * hd_bytes_per_word))) {
				/* This is the currently selected word! */
				memcpy(sel_word, pb, hd_bytes_per_word);
				sel_byte_is_valid = is_valid;
				for (nibble_byte = 0; nibble_byte < hd_bytes_per_word; ++nibble_byte) {
					byte_t b;
					unsigned int nibble_byte_index = nibble_byte;
					if (hd_hex_le)
						nibble_byte_index = (hd_bytes_per_word - 1) - nibble_byte;
					dbg_savecolor();
					b = pb[nibble_byte_index];
					if (CHANGED_BYTE(column_word * hd_bytes_per_word + nibble_byte_index))
						dbg_setfgcolor(ANSITTY_CL_RED);
					if (sel_region == HD_REGION_HEX) {
						if (nibble_byte_index == (hd_hex_nibble / 2)) {
							if (hd_hex_nibble & 1) {
								dbg_putc(hd_tohex(b >> 4, is_valid));
								dbg_savecolor();
								dbg_setcolor(ANSITTY_CL_GREEN, ANSITTY_CL_BLACK);
								dst_cursor_pos = dbg_getcur();
								dbg_putc(hd_tohex(b & 0xf, is_valid));
								dbg_loadcolor();
							} else {
								dbg_savecolor();
								dbg_setcolor(ANSITTY_CL_GREEN, ANSITTY_CL_BLACK);
								dst_cursor_pos = dbg_getcur();
								dbg_putc(hd_tohex(b >> 4, is_valid));
								dbg_loadcolor();
								dbg_putc(hd_tohex(b & 0xf, is_valid));
							}
						} else {
							dbg_putc(hd_tohex(b >> 4, is_valid));
							dbg_putc(hd_tohex(b & 0xf, is_valid));
						}
					} else {
						dbg_setcolor(ANSITTY_CL_GREEN, ANSITTY_CL_BLACK);
						dbg_putc(hd_tohex(b >> 4, is_valid));
						dbg_putc(hd_tohex(b & 0xf, is_valid));
					}
					dbg_loadcolor();
				}
			} else {
				for (nibble_byte = 0; nibble_byte < hd_bytes_per_word; ++nibble_byte) {
					byte_t b;
					unsigned int nibble_byte_index = nibble_byte;
					if (hd_hex_le)
						nibble_byte_index = (hd_bytes_per_word - 1) - nibble_byte;
					b = pb[nibble_byte_index];
					dbg_savecolor();
					if (CHANGED_BYTE(column_word * hd_bytes_per_word + nibble_byte_index))
						dbg_setfgcolor(ANSITTY_CL_RED);
					dbg_putc(hd_tohex(b >> 4, is_valid));
					dbg_putc(hd_tohex(b & 0xf, is_valid));
					dbg_loadcolor();
				}
			}
		}
		/* Print the ascii representation */
		dbg_setcolor(dbg_getdefaultcolor());
		for (i = 0; i < hd_asciipad; ++i)
			dbg_putc(' ');
		for (i = 0; i < hd_linesize; ++i) {
			byte_t b = line_data[i];
			bool is_valid = (line_valid & ((u64)1 << i)) != 0;
			bool was_changed = (line_changed & ((u64)1 << i)) != 0;
			char ch = is_valid && isprint(b) ? (char)b : '.';
			dbg_setcolor(dbg_getdefaultcolor());
			if (sel_region == HD_REGION_ASCII) {
				if (i == sel_byte || is_line_selected) {
					dbg_setcolor(ANSITTY_CL_BLACK, ANSITTY_CL_LIGHT_GRAY);
				} else {
					dbg_setbgcolor(ANSITTY_CL_DARK_GRAY);
				}
			} else {
				dbg_setbgcolor(ANSITTY_CL_BLACK);
			}
			if (was_changed)
				dbg_setfgcolor(ANSITTY_CL_RED);
			if (((byte_t *)line_addr + i) == (byte_t *)sel_addr + hd_hex_nibble / 2) {
				if (sel_region == HD_REGION_ASCII) {
					dbg_savecolor();
					dbg_setcolor(ANSITTY_CL_GREEN, ANSITTY_CL_BLACK);
					dst_cursor_pos = dbg_getcur();
					dbg_putc(ch);
					dbg_loadcolor();
				} else {
					dbg_setcolor(ANSITTY_CL_GREEN, ANSITTY_CL_BLACK);
					dbg_putc(ch);
				}
			} else {
				dbg_putc(ch);
			}
		}
	}
	dbg_setcolor(ANSITTY_CL_BLACK, ANSITTY_CL_LIGHT_GRAY);
	dbg_hline(0, dbg_screen_height - 1, dbg_screen_width, ' ');
	dbg_setcur(0, dbg_screen_height - 1);
	dbg_printf(DBGSTR("%p:"), sel_addr);
	if (sel_byte_is_valid) {
		switch (hd_bytes_per_word) {

		default:
			dbg_printf(DBGSTR("%.2" PRIx8), *(u8 const *)sel_word);
			break;

		case 2:
			dbg_printf(DBGSTR("%.4" PRIx16),
			           hd_hex_le
			           ? UNALIGNED_GETLE16((u16 const *)sel_word)
			           : UNALIGNED_GETBE16((u16 const *)sel_word));
			break;

		case 4:
			dbg_printf(DBGSTR("%.8" PRIx32),
			           hd_hex_le
			           ? UNALIGNED_GETLE32((u32 const *)sel_word)
			           : UNALIGNED_GETBE32((u32 const *)sel_word));
			break;

		case 8:
			dbg_printf(DBGSTR("%.16" PRIx64),
			           hd_hex_le
			           ? UNALIGNED_GETLE64((u64 const *)sel_word)
			           : UNALIGNED_GETBE64((u64 const *)sel_word));
			break;
		}
	} else {
		for (i = 0; i < hd_bytes_per_word; ++i)
			dbg_print(DBGSTR("??"));
	}
	/* Print the current display mode. */
	if (hd_nibbles_per_word <= 2) {
		dbg_print(DBGSTR(" u8"));
	} else {
		dbg_printf(DBGSTR(" %ce%u"),
		           hd_hex_le ? 'l' : 'b',
		           hd_nibbles_per_word * 4);
	}
	if (is_readonly)
		dbg_print(DBGSTR(" [ro]"));
	if (!status)
		status = DBGSTR("F1:help");
	{
		size_t status_len = strlen(status);
		dbg_pprint(dbg_screen_width - status_len,
		           dbg_screen_height - 1, status);
	}
	if (dst_cursor_pos != (u32)-1) {
		/* Display the cursor at a custom location */
		dbg_setcur(DBG_GETCUR_X(dst_cursor_pos),
		           DBG_GETCUR_Y(dst_cursor_pos));
		dbg_setcur_visible(true);
	}
}

INTERN ATTR_DBGTEXT bool
NOTHROW(FCALL dbg_hd_addrdiag)(uintptr_t *paddr) {
	PRIVATE ATTR_DBGRODATA char const diag_title[] = "Go to address";
	unsigned int edit_width  = dbg_screen_width / 3;
	unsigned int edit_x      = (dbg_screen_width - edit_width) / 2;
	unsigned int diag_x      = edit_x - 2;
	unsigned int diag_height = 5;
	unsigned int diag_width  = edit_width + 4;
	unsigned int diag_y      = ((dbg_screen_height - diag_height) / 2);
	unsigned int edit_y      = diag_y + 2;
	char exprbuf[256];
	unsigned int what;
	dbg_setcolor(ANSITTY_CL_BLACK, ANSITTY_CL_LIGHT_GRAY);
	dbg_fillrect_singlestroke(diag_x, diag_y, diag_width, diag_height);
	dbg_fillbox(diag_x + 1, diag_y + 1, diag_width - 2, diag_height - 2, ' ');
	dbg_pprint(diag_x + (diag_width - COMPILER_STRLEN(diag_title)) / 2, diag_y, diag_title);
	exprbuf[0] = 0;
	dbg_setcolor(ANSITTY_CL_WHITE, ANSITTY_CL_BLACK);
	do {
		what = dbg_editfield(edit_x,
		                     edit_y,
		                     edit_width,
		                     exprbuf,
		                     sizeof(exprbuf));
	} while (what != DBG_EDITFIELD_RETURN_ENTER &&
	         what != DBG_EDITFIELD_RETURN_ESC);
	if (what == DBG_EDITFIELD_RETURN_ESC)
		return false;
	return dbg_evaladdr(exprbuf, paddr);
}


PRIVATE ATTR_DBGRODATA char const hd_help[] =
"Esc:         Exit            F1:                  Help\n"
"Tab:         Next column     Shift+Tab:           Prev column\n"
"Arrow Keys:  Navigate        Home/End/Pg-Up/Down: Navigate\n"
"Ctrl+Pg-Up:  Go to top       Ctrl+Pg-Down:        Go to bottom\n"
"0-9,a-f,A-F: Set Hex Nibble  Any ascii key:       Set character\n"
"Esc/F1:      Close Help      F12:                 Toggle readonly\n"
"CTRL+S       Save changes    CTRL+Z/Y             Discard changes\n"
"F2:          Go to address   F4:                  Cycle display mode";


PRIVATE ATTR_DBGTEXT void *
NOTHROW(FCALL hd_main)(void *addr, bool is_readonly) {
	void *start_addr, *end_addr;
	unsigned int sel_region;
	char const *status = NULL;
	start_addr = (void *)(((uintptr_t)addr & ~(hd_linealign - 1)) -
                  ((dbg_screen_height - 1) / 2) * hd_linesize);
	end_addr   = (void *)((uintptr_t)start_addr + (hd_linesize * (dbg_screen_height - 1)));
	sel_region = HD_REGION_HEX;
	for (;;) {
		u32 uni;
		unsigned int key;
		if (addr < start_addr || addr >= end_addr) {
			size_t shift;
			if (addr < start_addr) {
				shift      = ((((byte_t *)start_addr - (byte_t *)addr) + (hd_linesize - 1)) / hd_linesize) * hd_linesize;
				start_addr = (byte_t *)start_addr - shift;
				end_addr   = (byte_t *)end_addr - shift;
			} else if (addr >= end_addr) {
				shift      = ((((byte_t *)addr - (byte_t *)end_addr) / hd_linesize) + 1) * hd_linesize;
				start_addr = (byte_t *)start_addr + shift;
				end_addr   = (byte_t *)end_addr + shift;
			}
		}
		hd_printscreen(start_addr, addr, sel_region, status, is_readonly);
		do {
			key = dbg_getkey();
		} while (key & KEY_FRELEASED);
		status = NULL;
		switch (key) {
#define ADDRESS_COLUMN (((uintptr_t)addr - (uintptr_t)start_addr) % hd_linesize)

		case KEY_UP:
			if (dbg_isholding_ctrl()) {
				start_addr = (byte_t *)start_addr - hd_linesize;
				end_addr   = (byte_t *)end_addr - hd_linesize;
			} else {
				addr = (byte_t *)addr - hd_linesize;
			}
			continue;

		case KEY_DOWN:
			if (dbg_isholding_ctrl()) {
				start_addr = (byte_t *)start_addr + hd_linesize;
				end_addr   = (byte_t *)end_addr + hd_linesize;
			} else {
				addr = (byte_t *)addr + hd_linesize;
			}
			continue;

		case KEY_LEFT:
			hd_hex_nibble = hd_convnibble(hd_hex_nibble, sel_region);
			if (sel_region == HD_REGION_HEX && hd_hex_nibble != 0) {
				--hd_hex_nibble;
			} else if (sel_region == HD_REGION_ASCII && hd_hex_nibble >= 2) {
				hd_hex_nibble -= 2;
				hd_hex_nibble &= ~1;
			} else if (ADDRESS_COLUMN != 0) {
				if (sel_region == HD_REGION_ASCII) {
					addr          = (byte_t *)addr - hd_bytes_per_word;
					hd_hex_nibble = hd_nibbles_per_word - 2;
				} else if (sel_region == HD_REGION_HEX) {
					addr          = (byte_t *)addr - hd_bytes_per_word;
					hd_hex_nibble = hd_nibbles_per_word - 1;
				}
			}
			hd_hex_nibble = hd_convnibble(hd_hex_nibble, sel_region);
			continue;

		case KEY_RIGHT:
			hd_hex_nibble = hd_convnibble(hd_hex_nibble, sel_region);
			if (sel_region == HD_REGION_HEX) {
				if (hd_hex_nibble < hd_nibbles_per_word - 1) {
					++hd_hex_nibble;
				} else if (ADDRESS_COLUMN < hd_linesize - hd_bytes_per_word) {
					addr          = (byte_t *)addr + hd_bytes_per_word;
					hd_hex_nibble = 0;
				}
			} else if (sel_region == HD_REGION_ASCII) {
				if (((((uintptr_t)addr + (hd_hex_nibble / 2)) -
				      (uintptr_t)start_addr) %
				     hd_linesize) < hd_linesize - 1) {
					hd_hex_nibble += 2;
					hd_hex_nibble &= ~1;
					if (hd_hex_nibble >= hd_nibbles_per_word) {
						addr = (byte_t *)addr + hd_bytes_per_word;
						hd_hex_nibble = 0;
					}
				}
			}
			hd_hex_nibble = hd_convnibble(hd_hex_nibble, sel_region);
			continue;

		case KEY_HOME:
			if (sel_region == HD_REGION_ADDR)
				continue;
			addr = (byte_t *)addr - ADDRESS_COLUMN;
			if (sel_region == HD_REGION_HEX || sel_region == HD_REGION_ASCII)
				hd_hex_nibble = hd_convnibble(0, sel_region);
			continue;

		case KEY_END:
			if (sel_region == HD_REGION_ADDR)
				continue;
			addr = ((byte_t *)addr - ADDRESS_COLUMN) + (hd_linesize - hd_bytes_per_word);
			if (sel_region == HD_REGION_HEX) {
				hd_hex_nibble = hd_convnibble(hd_nibbles_per_word - 1, sel_region);
			} else if (sel_region == HD_REGION_ASCII) {
				hd_hex_nibble = hd_convnibble(hd_nibbles_per_word - 2, sel_region);
			}
			continue;

		case KEY_PAGEUP:
			if (dbg_isholding_ctrl()) {
				addr = (void *)((uintptr_t)start_addr + ADDRESS_COLUMN);
			} else {
				size_t offset;
				offset     = (size_t)(dbg_screen_height - 1) * hd_linesize;
				addr       = (byte_t *)addr - offset;
				start_addr = (byte_t *)start_addr - offset;
				end_addr   = (byte_t *)end_addr - offset;
			}
			continue;

		case KEY_PAGEDOWN:
			if (dbg_isholding_ctrl()) {
				addr = (void *)(((uintptr_t)end_addr - hd_linesize) + ADDRESS_COLUMN);
			} else {
				size_t offset;
				offset     = (size_t)(dbg_screen_height - 1) * hd_linesize;
				addr       = (byte_t *)addr + offset;
				start_addr = (byte_t *)start_addr + offset;
				end_addr   = (byte_t *)end_addr + offset;
			}
			continue;

		case KEY_TAB:
			if (dbg_isholding_shift()) {
				if (sel_region == HD_REGION_ADDR)
					sel_region = HD_REGION_ASCII;
				else {
					--sel_region;
				}
			} else {
				if (sel_region == HD_REGION_ASCII)
					sel_region = HD_REGION_ADDR;
				else {
					++sel_region;
				}
			}
			continue;

		case KEY_ESC:
			if (hd_has_changes()) {
				dbg_setcur_visible(false);
				dbg_setcolor(ANSITTY_CL_BLACK, ANSITTY_CL_LIGHT_GRAY);
				dbg_messagebox(DBGSTR("Really Exit?"),
				               DBGSTR("Unsaved changes still exist\n"
				                      " - Press Enter to ignore and exit anyways\n"
				                      " - Press Esc to continue editing"));
				do {
					key = dbg_getkey();
				} while (key != KEY_ESC && key != KEY_ENTER);
				if (key != KEY_ENTER)
					continue;
			}
			goto done;

		case KEY_F1:
			dbg_setcur_visible(false);
			dbg_setcolor(ANSITTY_CL_BLACK, ANSITTY_CL_LIGHT_GRAY);
			dbg_messagebox(DBGSTR("Help"), hd_help);
			/* Wait until the user presses ESC or F1 */
			do {
				key = dbg_getkey();
			} while (key != KEY_F1 && key != KEY_ESC);
			continue;

		case KEY_F2: {
			uintptr_t newaddr;
			if (dbg_hd_addrdiag(&newaddr))
				addr = (void *)newaddr;
		}	continue;

		case KEY_Z:
		case KEY_Y:
			if (dbg_isholding_ctrl()) {
				hd_discard_changes();
				continue;
			}
			break;

		case KEY_S:
			if (dbg_isholding_ctrl()) {
				if (!hd_changes_commit())
					status = DBGSTR("Failed to apply all changes");
				continue;
			}
			break;

		case KEY_F12:
			is_readonly = !is_readonly;
			continue;

		case KEY_F4: {
			unsigned int i, n = 1;
			if (dbg_isholding_shift())
				n = 6;
			for (i = 0; i < n; ++i) {
				if (hd_hex_le == HD_LE_DEFAULT && hd_nibbles_per_word > 2) {
					hd_hex_le = !HD_LE_DEFAULT;
					continue;
				}
				hd_hex_le           = HD_LE_DEFAULT;
				hd_nibbles_per_word = hd_nibbles_per_word * 2;
				if (hd_nibbles_per_word > 16)
					hd_nibbles_per_word = 2;
				hd_hex_nibble += ((uintptr_t)addr & (hd_bytes_per_word - 1)) * 2;
				addr = (byte_t *)((uintptr_t)addr & ~(hd_bytes_per_word - 1));
				addr = (byte_t *)addr + (hd_hex_nibble & ~(hd_nibbles_per_word - 1)) / 2;
				hd_hex_nibble &= (hd_nibbles_per_word - 1);
				dbg_calculate_linesize();
			}
		}	continue;

		case KEY_F3:
		case KEY_F7 ... KEY_F8:
		case KEY_F10 ... KEY_F11:
		case KEY_F13 ... KEY_F24:
			continue;

		default:
			break;
		}
		/* Write memory. */
		if (sel_region != HD_REGION_ADDR) {
			dbg_purgeuni();
			dbg_ungetkey(key);
			uni = dbg_trygetuni();
			if (!uni || uni >= 0x100)
				continue;
			if (is_readonly) {
				status = DBGSTR("Cannot edit: In read-only mode");
				continue;
			}
			if (sel_region == HD_REGION_ASCII) {
				status = hd_setdata((byte_t *)addr + (hd_hex_nibble / 2),
				                    HD_SETDATA_BOTH, (byte_t)uni);
				if (!status) {
					hd_hex_nibble += 2;
					hd_hex_nibble &= ~1;
					if (hd_hex_nibble >= hd_nibbles_per_word) {
						addr          = (byte_t *)addr + hd_bytes_per_word;
						hd_hex_nibble = 0;
					}
				}
			} else if (sel_region == HD_REGION_HEX) {
				byte_t nibble;
				if (uni >= '0' && uni <= '9')
					nibble = uni - '0';
				else if (uni >= 'a' && uni <= 'f')
					nibble = 10 + (uni - 'a');
				else if (uni >= 'A' && uni <= 'F')
					nibble = 10 + (uni - 'A');
				else {
					continue;
				}
				status = hd_setdata((byte_t *)addr + (hd_hex_nibble / 2),
				                    hd_hex_nibble & 1 ? HD_SETDATA_HIGH
				                                      : HD_SETDATA_LOW,
				                    nibble);
				if (!status) {
					hd_hex_nibble = hd_convnibble(hd_hex_nibble, sel_region);
					++hd_hex_nibble;
					if (hd_hex_nibble >= hd_nibbles_per_word) {
						addr          = (byte_t *)addr + hd_bytes_per_word;
						hd_hex_nibble = 0;
					}
					hd_hex_nibble = hd_convnibble(hd_hex_nibble, sel_region);
				}
			}
		}
	}
done:
	return addr;
}

PRIVATE ATTR_DBGTEXT unsigned int
NOTHROW(FCALL dbg_get_used_cells)(void) {
	return (sizeof(void *) * 2) +                           /* Address column */
	       (hd_linewords * (hd_nibbles_per_word + 1)) - 1 + /* Hex column (+1 for spaces between words) */
	       hd_linesize;                                     /* Ascii column */
}

PRIVATE ATTR_DBGTEXT void
NOTHROW(FCALL dbg_calculate_linesize)(void) {
	unsigned int usedcells, unused_cells;
	hd_linewords = 1;
	hd_linesize  = 1 * hd_bytes_per_word;
	hd_hexpad    = 1;
	hd_asciipad  = 1;
	for (;;) {
		usedcells = dbg_get_used_cells();
		if (usedcells >= dbg_screen_width)
			break;
		++hd_linewords;
		hd_linesize += hd_bytes_per_word;
	}
	if unlikely(hd_linewords > HD_MAXLINESIZE / hd_bytes_per_word)
		hd_linewords = HD_MAXLINESIZE / hd_bytes_per_word;
	if (dbg_get_used_cells() > dbg_screen_width)
		--hd_linewords;
	if unlikely(hd_linewords & 1)
		--hd_linewords;
	hd_linealign = 2;
	hd_linesize  = hd_linewords * hd_bytes_per_word;
	while (hd_linealign < hd_linesize && !(hd_linesize & (hd_linealign - 1)))
		hd_linealign <<= 1;
	/* Try to get 8-byte alignment */
	if (hd_linesize > 8 && hd_linewords >= 8) {
		hd_linealign = 8;
		hd_linewords = (hd_linesize & ~7) / hd_bytes_per_word;
		hd_linesize  = hd_linewords * hd_bytes_per_word;
	}
	usedcells    = dbg_get_used_cells();
	unused_cells = dbg_screen_width >= usedcells ? dbg_screen_width - usedcells : 0;
	hd_hexpad    = unused_cells / 2;
	hd_asciipad  = unused_cells - hd_hexpad;
}


/* Open an interactive hex editor at `addr'
 * @return: * : The final selected address when the editor was closed. */
PUBLIC ATTR_DBGTEXT void *
NOTHROW(FCALL dbg_hexedit)(void *addr, bool is_readonly) {
	bool was_cursor_visible;
	void *buf, *result;
	u32 oldcur;
	u8 old_hex_nibble;
	u8 old_nibbles_per_word;
	bool old_show_le;

	/* Save terminal settings and display contents. */
	was_cursor_visible = dbg_setcur_visible(false);
	buf      = alloca(dbg_screen_width * dbg_screen_height * dbg_screen_cellsize);
	oldcur   = dbg_getcur();
	dbg_logecho_pushoff();
	dbg_savecolor();
	dbg_getscreendata(0, 0, dbg_screen_width, dbg_screen_height, buf);

	/* Configure hexedit settings */
	old_hex_nibble       = hd_hex_nibble;
	old_nibbles_per_word = hd_nibbles_per_word;
	old_show_le          = hd_hex_le;
	hd_hex_nibble        = 0;
	hd_nibbles_per_word  = 2;
	hd_hex_le            = HD_LE_DEFAULT;

	/* Figure out how many bytes we want to display on each line. */
	dbg_calculate_linesize();
	hd_change_buffer_init();
	result = hd_main(addr, is_readonly);

	/* Restore hexedit settings */
	hd_hex_nibble       = old_hex_nibble;
	hd_nibbles_per_word = old_nibbles_per_word;
	hd_hex_le           = old_show_le;
	hd_change_buffer_init(); /* XXX: During a recursive call, changes made are lost! */
	if (old_nibbles_per_word != 0)
		dbg_calculate_linesize();

	/* Restore display contents and terminal settings. */
	dbg_setscreendata(0, 0, dbg_screen_width, dbg_screen_height, buf);
	dbg_loadcolor();
	dbg_logecho_pop();
	dbg_setcur(DBG_GETCUR_X(oldcur), DBG_GETCUR_Y(oldcur));
	dbg_setcur_visible(was_cursor_visible);
	return result;
}


DBG_COMMAND(h,
            "h [ADDR=faultpc]\n"
            "\tOpen an interactive hex editor at ADDR\n",
            argc, argv) {
	void *addr;
	addr = dbg_getfaultpcreg(DBG_REGLEVEL_VIEW);
	if (argc >= 2) {
		if (!dbg_evaladdr(argv[1], (uintptr_t *)&addr))
			return DBG_STATUS_INVALID_ARGUMENTS;
	}
	dbg_hexedit(addr, true);
	return 0;
}


DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_DEBUGGER_APPS_HEXEDIT_C */
