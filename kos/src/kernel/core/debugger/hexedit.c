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
#ifndef GUARD_KERNEL_SRC_DEBUGGER_HEXEDIT_C
#define GUARD_KERNEL_SRC_DEBUGGER_HEXEDIT_C 1
#define DISABLE_BRANCH_PROFILING 1

#include <kernel/compiler.h>

#include <kernel/debugger.h>
#ifndef CONFIG_NO_DEBUGGER
#include <kos/keyboard.h>
#include <kernel/except.h>
#include <kernel/paging.h>
#include <kernel/vm.h>
#include <alloca.h>
#include <ctype.h>
#include <string.h>
#include <hybrid/align.h>
#include <kos/kernel/cpu-state.h>

DECL_BEGIN

#define HD_REGION_ADDR  0 /* Address column is selected. */
#define HD_REGION_HEX   1 /* Low nibble is selected */
#define HD_REGION_HEX2  2 /* High nibble is selected */
#define HD_REGION_ASCII 3 /* Ascii representation is selected */


#define HD_MAXLINESIZE 64


PRIVATE ATTR_DBGTEXT bool
NOTHROW(FCALL hd_setbyte)(void *addr, byte_t value) {
	TRY {
		*(byte_t *)addr = value;
		return true;
	} EXCEPT {
	}
	{
		vm_vpage_t page;
		page = VM_ADDR2PAGE((vm_virt_t)addr);
		/* Try to force write-access to the associated page by directly
		 * accessing the underlying physical memory (if there is any). */
		if (pagedir_ismapped(page)) {
			vm_phys_t phys;
			phys = pagedir_translate((vm_virt_t)addr);
			vm_copytophys(phys, &value, 1);
			return true;
		}
	}
	return false;
}


PRIVATE ATTR_DBGTEXT bool
NOTHROW(FCALL hd_getbyte)(void *addr, byte_t *pvalue) {
	TRY {
		*pvalue = *(byte_t *)addr;
		return true;
	} EXCEPT {
	}
	{
		vm_vpage_t page;
		page = VM_ADDR2PAGE((vm_virt_t)addr);
		/* Try to force write-access to the associated page by directly
		 * accessing the underlying physical memory (if there is any). */
		if (pagedir_ismapped(page)) {
			vm_phys_t phys;
			phys = pagedir_translate((vm_virt_t)addr);
			vm_copyfromphys(pvalue, phys, 1);
			return true;
		}
	}
	return false;
}



struct hd_change {
	byte_t                         *hc_start;  /* Starting address */
	u8                              hc_length; /* Number of changed bytes */
	COMPILER_FLEXIBLE_ARRAY(byte_t, hc_data);  /* [hc_length] The actual changed data. */
};

#define HD_CHANGE_NEXT(x) (struct hd_change *)((x)->hc_data + CEIL_ALIGN((x)->hc_length, sizeof(void *)))


/* Buffer of pending memory changes. */
PRIVATE ATTR_DBGBSS byte_t hd_change_buffer[1024];
#define hd_change_buffer_init() memset(hd_change_buffer, 0, offsetof(struct hd_change, hc_data))


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
			if (!hd_setbyte(addr, iter->hc_data[i]))
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
				memmove((byte_t *)next + sizeof(void *), next,
				        (size_t)((byte_t *)last_change - (byte_t *)next));
			}
			iter->hc_data[iter->hc_length++] = value;
			return true;
		}
		iter = next;
	}
	/* Check if we can append a new change-block at the end. */
	if (((byte_t *)&last_change->hc_data + 1 + offsetof(struct hd_change, hc_data)) >=
	    COMPILER_ENDOF(hd_change_buffer))
		return false;
	last_change->hc_start   = addr;
	last_change->hc_length  = 1;
	last_change->hc_data[0] = value;
	last_change = HD_CHANGE_NEXT(last_change);
	last_change->hc_length = 0;
	return true;
}

PRIVATE ATTR_DBGTEXT void
NOTHROW(FCALL hd_changes_applyto)(byte_t *addr, byte_t *buf, size_t buflen, u64 *pchanged) {
	struct hd_change *iter;
	byte_t *endaddr = addr + buflen;
	iter = (struct hd_change *)hd_change_buffer;
	while (iter->hc_length) {
		byte_t *block_start, *block_end;
		block_start = iter->hc_start;
		block_end   = iter->hc_start + iter->hc_length;
		if (addr < block_end && endaddr > block_start) {
			size_t i;
			for (i = 0; i < buflen; ++i) {
				byte_t *effective_address;
				effective_address = addr + i;
				if (effective_address < block_start)
					continue;
				if (effective_address >= block_end)
					continue;
				if (pchanged)
					*pchanged |= ((u64)1 << i);
				buf[i] = iter->hc_data[effective_address - block_start];
			}
		}
		iter = HD_CHANGE_NEXT(iter);
	}
}


#define HD_SETDATA_LOW  0 /* Write low nibble */
#define HD_SETDATA_HIGH 1 /* Write high nibble */
#define HD_SETDATA_BOTH 2 /* Write low & high nibble */

PRIVATE ATTR_DBGTEXT char const *
NOTHROW(FCALL hd_setdata)(void *addr, unsigned int how, byte_t value) {
	byte_t newval;
	if (how == HD_SETDATA_BOTH) {
		newval = value;
	} else {
		hd_getbyte(addr, &newval);
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

PRIVATE ATTR_DBGBSS unsigned int hd_linesize  = 0; /* Number of bytes per line */
PRIVATE ATTR_DBGBSS unsigned int hd_linealign = 0; /* Lowest power-of-two number which may be used to align an address */
PRIVATE ATTR_DBGBSS unsigned int hd_hexpad    = 0; /* Number of empty cells before the hex view */
PRIVATE ATTR_DBGBSS unsigned int hd_asciipad  = 0; /* Number of empty cells before the ascii view */


/* Get the bytes for a given line of hex data.
 * @return: * : Bitset of valid bytes (usually 0xffff). */
PRIVATE ATTR_DBGTEXT u64 FCALL
hd_getline(void *start_addr, byte_t data[HD_MAXLINESIZE], u64 *pchanged) {
	TRY {
		COMPILER_READ_BARRIER();
		memcpy(data, start_addr, hd_linesize);
		COMPILER_READ_BARRIER();
	} EXCEPT {
		goto tryhard;
	}
	hd_changes_applyto((byte_t *)start_addr, data, hd_linesize, pchanged);
	return (u64)-1;
tryhard:
	/* Something's wrong with the address. - Try to copy each byte individually. */
	{
		u64 result = (u64)-1;
		unsigned int i;
		for (i = 0; i < hd_linesize; ++i) {
			TRY {
				COMPILER_READ_BARRIER();
				data[i] = ((byte_t *)start_addr)[i];
				COMPILER_READ_BARRIER();
			} EXCEPT {
				result &= ~((u64)1 << i);
			}
		}
		hd_changes_applyto((byte_t *)start_addr, data, hd_linesize, pchanged);
		return result;
	}
}

LOCAL ATTR_DBGTEXT char FCALL
hd_tohex(byte_t val, bool is_valid) {
	if (!is_valid)
		return '?';
	if (val <= 9)
		return '0' + val;
	return 'A' + (val - 10);
}


/* @param: start_addr: Starting address (the first address displayed at the top-left)
 * @param: sel_addr:   The currently selected address.
 * @param: sel_region: The selected region (one of `HD_REGION_*') */
PRIVATE ATTR_DBGTEXT void FCALL
hd_printscreen(void *start_addr, void *sel_addr,
               unsigned int sel_region,
               char const *status,
               bool is_readonly) {
	unsigned int i, line, column, sel_column;
	byte_t line_data[HD_MAXLINESIZE];
	u64 line_valid, line_changed;
	u32 dst_cursor_pos = (u32)-1;
	byte_t sel_byte = 0;
	bool sel_byte_is_valid = true;
	sel_column = (unsigned int)((uintptr_t)((byte_t *)sel_addr -
	                                        (byte_t *)start_addr) %
	                            hd_linesize);
	/* Always hide the cursor during rendering. */
	dbg_setcur_visible(DBG_SETCUR_VISIBLE_HIDE);
	for (line = 0; line < dbg_screen_height - 1; ++line) {
		void *line_addr = (byte_t *)start_addr + line * hd_linesize;
		bool is_line_selected;
		is_line_selected = (byte_t *)sel_addr >= (byte_t *)line_addr &&
		                   (byte_t *)sel_addr < (byte_t *)line_addr + hd_linesize;
		line_changed = 0;
		line_valid = hd_getline(line_addr, line_data, &line_changed);
		dbg_attr = dbg_default_attr;
		if (sel_region == HD_REGION_ADDR) {
			if (is_line_selected) {
				dbg_setcolor(DBG_COLOR_BLACK, DBG_COLOR_LIGHT_GRAY);
			} else {
				dbg_setbgcolor(DBG_COLOR_DARK_GRAY);
			}
		} else {
			dbg_setbgcolor(DBG_COLOR_BLACK);
		}
		dbg_setcur(0, line);
		dbg_printf(DBGSTR("%p"), line_addr);
		dbg_attr = dbg_default_attr;
		for (i = 0; i < hd_hexpad; ++i)
			dbg_putc(' ');
		/* Print the hex representation */
		for (column = 0; column < hd_linesize; ++column) {
			bool is_valid = (line_valid & ((u64)1 << column)) != 0;
			bool was_changed = (line_changed & ((u64)1 << column)) != 0;
			byte_t b = line_data[column];
			if (column != 0)
				dbg_putc(' ');
			dbg_attr = dbg_default_attr;
			if (sel_region == HD_REGION_HEX || sel_region == HD_REGION_HEX2) {
				if (column == sel_column || is_line_selected) {
					dbg_setcolor(DBG_COLOR_BLACK, DBG_COLOR_LIGHT_GRAY);
				} else {
					dbg_setbgcolor(DBG_COLOR_DARK_GRAY);
				}
			} else {
				dbg_setbgcolor(DBG_COLOR_BLACK);
			}
			if (was_changed)
				dbg_setfgcolor(DBG_COLOR_RED);
			if (((byte_t *)line_addr + column) == (byte_t *)sel_addr) {
				dbg_attr_t temp;
				sel_byte          = b;
				sel_byte_is_valid = is_valid;
				if (sel_region == HD_REGION_HEX) {
					temp = dbg_attr;
					dbg_setcolor(DBG_COLOR_GREEN, DBG_COLOR_BLACK);
					dst_cursor_pos = dbg_getcur();
					dbg_putc(hd_tohex(b >> 4, is_valid));
					dbg_attr = temp;
					dbg_putc(hd_tohex(b & 0xf, is_valid));
				} else if (sel_region == HD_REGION_HEX2) {
					dbg_putc(hd_tohex(b >> 4, is_valid));
					temp = dbg_attr;
					dbg_setcolor(DBG_COLOR_GREEN, DBG_COLOR_BLACK);
					dst_cursor_pos = dbg_getcur();
					dbg_putc(hd_tohex(b & 0xf, is_valid));
					dbg_attr = temp;
				} else {
					dbg_setcolor(DBG_COLOR_GREEN, DBG_COLOR_BLACK);
					dbg_putc(hd_tohex(b >> 4, is_valid));
					dbg_putc(hd_tohex(b & 0xf, is_valid));
				}
			} else {
				dbg_putc(hd_tohex(b >> 4, is_valid));
				dbg_putc(hd_tohex(b & 0xf, is_valid));
			}
		}
		/* Print the ascii representation */
		dbg_attr = dbg_default_attr;
		for (i = 0; i < hd_asciipad; ++i)
			dbg_putc(' ');
		for (column = 0; column < hd_linesize; ++column) {
			byte_t b = line_data[column];
			bool is_valid = (line_valid & ((u64)1 << column)) != 0;
			bool was_changed = (line_changed & ((u64)1 << column)) != 0;
			char ch = !is_valid ? '.' : (isprint(b) ? (char)b : '.');
			dbg_attr = dbg_default_attr;
			if (sel_region == HD_REGION_ASCII) {
				if (column == sel_column || is_line_selected) {
					dbg_setcolor(DBG_COLOR_BLACK, DBG_COLOR_LIGHT_GRAY);
				} else {
					dbg_setbgcolor(DBG_COLOR_DARK_GRAY);
				}
			} else {
				dbg_setbgcolor(DBG_COLOR_BLACK);
			}
			if (was_changed)
				dbg_setfgcolor(DBG_COLOR_RED);
			if (((byte_t *)line_addr + column) == (byte_t *)sel_addr) {
				if (sel_region == HD_REGION_ASCII) {
					dbg_attr_t temp;
					temp = dbg_attr;
					dbg_setcolor(DBG_COLOR_GREEN, DBG_COLOR_BLACK);
					dst_cursor_pos = dbg_getcur();
					dbg_putc(ch);
					dbg_attr = temp;
				} else {
					dbg_setcolor(DBG_COLOR_GREEN, DBG_COLOR_BLACK);
					dbg_putc(ch);
				}
			} else {
				dbg_putc(ch);
			}
		}
	}
	dbg_setcolor(DBG_COLOR_BLACK, DBG_COLOR_LIGHT_GRAY);
	dbg_hline(0, dbg_screen_height - 1, dbg_screen_width, ' ');
	dbg_setcur(0, dbg_screen_height - 1);
	dbg_printf(DBGSTR("%p:"), sel_addr);
	if (sel_byte_is_valid) {
		dbg_printf(DBGSTR("%.2I8x"), sel_byte);
	} else {
		dbg_print(DBGSTR("??"));
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
		dbg_setcur_visible(DBG_SETCUR_VISIBLE_SHOW);
	}
}

INTERN ATTR_DBGTEXT bool
NOTHROW(FCALL dbg_hd_addrdiag)(uintptr_t *paddr) {
	PRIVATE ATTR_DBGRODATA char const diag_title[] = "Go to address";
	unsigned int edit_width = dbg_screen_width / 3;
	unsigned int edit_x = (dbg_screen_width - edit_width) / 2;
	unsigned int diag_x = edit_x - 2;
	unsigned int diag_height = 5;
	unsigned int diag_width = edit_width + 4;
	unsigned int diag_y = ((dbg_screen_height - diag_height) / 2);
	unsigned int edit_y = diag_y + 2;
	char exprbuf[256];
	unsigned int what;
	dbg_setcolor(DBG_COLOR_BLACK, DBG_COLOR_LIGHT_GRAY);
	dbg_fillrect_singlestroke(diag_x, diag_y, diag_width, diag_height);
	dbg_fillbox(diag_x + 1, diag_y + 1, diag_width - 2, diag_height - 2, ' ');
	dbg_pprint(diag_x + (diag_width - COMPILER_STRLEN(diag_title)) / 2, diag_y, diag_title);
	exprbuf[0] = 0;
	dbg_setcolor(DBG_COLOR_WHITE, DBG_COLOR_BLACK);
	do what = dbg_editfield(edit_x, edit_y, edit_width, exprbuf, sizeof(exprbuf));
	while (what != DBG_EDITFIELD_RETURN_ENTER &&
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
"F2:          Go to address"
;

#define ADDRSPACE_HALFSIZE ((((size_t)-1)/2)+1)

PRIVATE ATTR_DBGTEXT void *
NOTHROW(FCALL hd_main)(void *addr, bool is_readonly) {
	void *start_addr, *end_addr;
	unsigned int sel_region;
	char const *status = NULL;
	start_addr = (void *)(((uintptr_t)addr & ~(hd_linealign - 1)) -
	                      ((dbg_screen_height - 1) / 2) * hd_linesize);
	end_addr = (void *)((uintptr_t)start_addr + (hd_linesize * (dbg_screen_height - 1)));
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
#define ADDRESS_COLUMN   (((uintptr_t)addr - (uintptr_t)start_addr) % hd_linesize)

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
			if (sel_region == HD_REGION_HEX2) {
				sel_region = HD_REGION_HEX;
				continue;
			}
			if (ADDRESS_COLUMN == 0)
				continue;
			if (sel_region == HD_REGION_ASCII) {
				addr = (byte_t *)addr - 1;
			} else if (sel_region == HD_REGION_HEX) {
				addr = (byte_t *)addr - 1;
				sel_region = HD_REGION_HEX2;
			}
			continue;

		case KEY_RIGHT:
			if (sel_region == HD_REGION_HEX) {
				sel_region = HD_REGION_HEX2;
				continue;
			}
			if (ADDRESS_COLUMN == hd_linesize - 1)
				continue;
			if (sel_region == HD_REGION_ASCII) {
				addr = (byte_t *)addr + 1;
			} else if (sel_region == HD_REGION_HEX2) {
				addr = (byte_t *)addr + 1;
				sel_region = HD_REGION_HEX;
			}
			continue;

		case KEY_HOME:
			if (sel_region == HD_REGION_ADDR)
				continue;
			addr = (byte_t *)addr - ADDRESS_COLUMN;
			if (sel_region == HD_REGION_HEX2)
				sel_region = HD_REGION_HEX;
			continue;

		case KEY_END:
			if (sel_region == HD_REGION_ADDR)
				continue;
			addr = ((byte_t *)addr - ADDRESS_COLUMN) + (hd_linesize - 1);
			if (sel_region == HD_REGION_HEX)
				sel_region = HD_REGION_HEX2;
			continue;

		case KEY_PAGEUP:
			if (dbg_isholding_ctrl()) {
				addr = (void *)((uintptr_t)start_addr + ADDRESS_COLUMN);
			} else {
				size_t offset;
				offset     = (dbg_screen_height - 1) * hd_linesize;
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
				offset     = (dbg_screen_height - 1) * hd_linesize;
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
					if (sel_region == HD_REGION_HEX)
						sel_region = HD_REGION_ADDR;
				}
			} else {
				if (sel_region == HD_REGION_ASCII)
					sel_region = HD_REGION_ADDR;
				else {
					++sel_region;
					if (sel_region == HD_REGION_HEX2)
						sel_region = HD_REGION_ASCII;
				}
			}
			continue;

		case KEY_ESC:
			if (hd_has_changes()) {
				dbg_setcur_visible(DBG_SETCUR_VISIBLE_HIDE);
				dbg_setcolor(DBG_COLOR_BLACK, DBG_COLOR_LIGHT_GRAY);
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
			dbg_setcur_visible(DBG_SETCUR_VISIBLE_HIDE);
			dbg_setcolor(DBG_COLOR_BLACK, DBG_COLOR_LIGHT_GRAY);
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

		case KEY_F3 ... KEY_F4:
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
				status = hd_setdata(addr, HD_SETDATA_BOTH, (byte_t)uni);
				if (!status)
					addr = (byte_t *)addr + 1;
			} else {
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
				if (sel_region == HD_REGION_HEX2) {
					status = hd_setdata(addr, HD_SETDATA_HIGH, nibble);
					if (!status) {
						addr = (byte_t *)addr + 1;
						sel_region = HD_REGION_HEX;
					}
				} else {
					status = hd_setdata(addr, HD_SETDATA_LOW, nibble);
					if (!status)
						sel_region = HD_REGION_HEX2;
				}
			}
		}
	}
done:
	return addr;
}

PRIVATE ATTR_DBGTEXT unsigned int
NOTHROW(FCALL dbg_get_used_cells)(void) {
	return (sizeof(void *) * 2) + /* Address column */
	       (hd_linesize * 3) +    /* Hex column (+1 for leading padding space) */
	       (hd_linesize + 1);     /* Ascii column (+1 for leading padding space) */
}

PRIVATE ATTR_DBGTEXT void
NOTHROW(FCALL dbg_calculate_linesize)(void) {
	unsigned int usedcells, unused_cells;
	hd_linesize = 1;
	hd_hexpad   = 1;
	hd_asciipad = 1;
	for (;;) {
		usedcells = dbg_get_used_cells();
		if (usedcells >= dbg_screen_width)
			break;
		++hd_linesize;
	}
	if unlikely(hd_linesize > HD_MAXLINESIZE)
		hd_linesize = HD_MAXLINESIZE;
	if (usedcells > dbg_screen_width)
		--hd_linesize;
	if unlikely(hd_linesize & 1)
		--hd_linesize;
	hd_linealign = 2;
	while (hd_linealign < hd_linesize && !(hd_linesize & (hd_linealign - 1)))
		hd_linealign <<= 1;
	unused_cells = usedcells - (dbg_get_used_cells() - 2);
	hd_hexpad   = unused_cells / 2;
	hd_asciipad = unused_cells - hd_hexpad;
}


/* Open an interactive hex editor at `addr'
 * @return: * : The final selected address when the editor was closed. */
PUBLIC ATTR_DBGTEXT void *
NOTHROW(FCALL dbg_hexedit)(void *addr, bool is_readonly) {
	bool was_cursor_visible;
	void *buf, *result;
	u32 oldcur;
	dbg_attr_t oldattr;
	/* Save terminal settings and display contents. */
	was_cursor_visible = dbg_setcur_visible(DBG_SETCUR_VISIBLE_TEST);
	dbg_setcur_visible(DBG_SETCUR_VISIBLE_HIDE);
	buf = alloca(dbg_screen_width * dbg_screen_height * dbg_screen_cellsize);
	oldcur = dbg_getcur();
	oldattr = dbg_attr;
	dbg_getscreendata(0, 0, dbg_screen_width, dbg_screen_height, buf);

	/* Figure out how many bytes we want to display on each line. */
	dbg_calculate_linesize();
	hd_change_buffer_init();
	result = hd_main(addr, is_readonly);

	/* Restore display contents and terminal settings. */
	dbg_setscreendata(0, 0, dbg_screen_width, dbg_screen_height, buf);
	dbg_attr = oldattr;
	dbg_setcur(DBG_GETCUR_X(oldcur), DBG_GETCUR_Y(oldcur));
	if (was_cursor_visible)
		dbg_setcur_visible(DBG_SETCUR_VISIBLE_SHOW);
	return result;
}


DEFINE_DEBUG_FUNCTION(
		"h",
		"h [ADDR=pc]\n"
		"\tOpen an interactive hex editor at ADDR\n",
		argc, argv) {
	void *addr = (void *)FCPUSTATE_PC(dbg_viewstate);
	if (argc >= 2) {
		if (!dbg_evaladdr(argv[1], (uintptr_t *)&addr))
			return DBG_FUNCTION_INVALID_ARGUMENTS;
	}
	dbg_hexedit(addr, true);
	return 0;
}


DECL_END
#endif /* !CONFIG_NO_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_DEBUGGER_HEXEDIT_C */
