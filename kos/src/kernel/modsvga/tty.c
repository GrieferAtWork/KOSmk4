/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODSVGA_TTY_C
#define GUARD_MODSVGA_TTY_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/sync.h>
#include <kernel/mman/unmapped.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <hw/video/vga.h>
#include <kos/except.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

#include <libsvga/chipset.h>
#include <libsvga/util/vgaio.h>

/**/
#include "svga.h"


/************************************************************************/
/* SVGA ANSI TTY Implementation                                         */
/************************************************************************/

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/* Unmap, unprepare, and possibly free SVGA physical buffers.
 * The caller must be holding a write-lock to  `mman_kernel'. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_unmap_vmem)(struct svga_ttyaccess *__restrict self) {
	/* Remove the video-memory node from the kernel mman. */
	mman_mappings_removenode(&mman_kernel, &self->sta_vmem);

	/* Unmap+Sync+Unprepare the memory mapping. */
	mnode_pagedir_unmap(&self->sta_vmem);
	mnode_mman_supersync(&self->sta_vmem);
	mnode_pagedir_kernelunprepare(&self->sta_vmem);
}


PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(LOCKOP_CC svga_ttyaccess_destroy_postlop)(Tobpostlockop(mman) *__restrict self,
                                                  struct mman *__restrict UNUSED(obj)) {
	struct svga_ttyaccess *me;
	me = container_of(self, struct svga_ttyaccess, _sta_mmplop);
	kfree(me);
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(mman) *
NOTHROW(LOCKOP_CC svga_ttyaccess_destroy_lop)(Toblockop(mman) *__restrict self,
                                              struct mman *__restrict UNUSED(obj)) {
	struct svga_ttyaccess *me;
	me = container_of(self, struct svga_ttyaccess, _sta_mmlop);
	svga_ttyaccess_unmap_vmem(me);
	me->_sta_mmplop.oplo_func = &svga_ttyaccess_destroy_postlop;
	return &me->_sta_mmplop;
}

INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_destroy)(struct svga_ttyaccess *__restrict self) {
	/* Remove `self->sta_vmem' from the kernel mman. */
	if (mman_lock_trywrite(&mman_kernel)) {
		svga_ttyaccess_unmap_vmem(self);
		mman_lock_endwrite(&mman_kernel);
	} else {
		self->_sta_mmlop.olo_func = &svga_ttyaccess_destroy_lop;
		oblockop_enqueue(&mman_kernel_lockops, &self->_sta_mmlop);
		mman_lockops_reap(&mman_kernel);
		return;
	}
	kfree(self);
}






/* Scroll up once */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_scrollone)(struct svga_ttyaccess *__restrict me,
                                        struct svgatty *__restrict tty) {
	(*me->sta_copycell)(me, me->_sta_scrl1_to, me->_sta_scrl1_from, me->_sta_scrl1_cnt);
	(*me->sta_fillcells)(me, tty, me->_sta_scrl1_fil, ' ', me->sta_resx);
}


PRIVATE NONNULL((1)) void LIBANSITTY_CC
svga_ansitty_v_putc(struct ansitty *__restrict self,
                    char32_t ch) {
	REF struct svga_ttyaccess *me;
	me = ansitty_getaccess(self);
	FINALLY_DECREF_UNLIKELY(me);
	atomic_lock_acquire(&me->sta_lock);
	switch (ch) {

	case 7: /* BEL */
		/* TODO */
		break;

	case '\t': {
#define TABSIZE 8
		uintptr_half_t advance;
		/* Check if we need to scroll. */
		if (me->sta_cursor.stc_celly >= me->sta_scroll_yend) {
			me->sta_cursor.stc_celly = me->_sta_scrl_ymax;
			svga_ttyaccess_scrollone(me, ansitty_assvga(self));
		}
		advance = TABSIZE - (me->sta_cursor.stc_cellx % TABSIZE);
		if ((me->sta_cursor.stc_cellx + advance) > me->sta_resx)
			advance = me->sta_resx - me->sta_cursor.stc_cellx;
		(*me->sta_fillcells)(me, ansitty_assvga(self),
		                     me->sta_cursor.stc_cellx +
		                     me->sta_cursor.stc_celly *
		                     me->sta_scan,
		                     ' ', advance);
		me->sta_cursor.stc_cellx += advance;
		if (me->sta_cursor.stc_cellx >= me->sta_resx) {
			me->sta_cursor.stc_cellx = 0;
			++me->sta_cursor.stc_celly;

			/* Set the EOL flag after an implicit line-feed */
			me->sta_flags |= SVGA_TTYACCESS_F_EOL;
			goto maybe_hide_cursor_after_eol;
		}
	}	break;

	case '\b':
		if (OVERFLOW_USUB(me->sta_cursor.stc_cellx, 1, &me->sta_cursor.stc_cellx)) {
			me->sta_cursor.stc_cellx = me->sta_resx - 1;
			if (OVERFLOW_USUB(me->sta_cursor.stc_celly, 1, &me->sta_cursor.stc_celly)) {
				/* Stay in the top-left. */
				me->sta_cursor.stc_cellx = 0;
				me->sta_cursor.stc_celly = 0;
			}
		}
		/* Check if we need to scroll. */
		if (me->sta_cursor.stc_celly >= me->sta_scroll_yend) {
			me->sta_cursor.stc_celly = me->_sta_scrl_ymax;
			svga_ttyaccess_scrollone(me, ansitty_assvga(self));
		}
		break;

	case '\r':
		if (me->sta_flags & SVGA_TTYACCESS_F_EOL) {
			/* Go to the original line after a line-wrap. */
			me->sta_cursor.stc_cellx = 0;
			--me->sta_cursor.stc_celly;
			break;
		}
		if (self->at_ttymode & ANSITTY_MODE_NEWLINE_CLRFREE) {
			/* Clear trailing spaces */
			(*me->sta_fillcells)(me, ansitty_assvga(self),
			                     me->sta_cursor.stc_cellx +
			                     me->sta_cursor.stc_celly *
			                     me->sta_scan,
			                     ' ',
			                     me->sta_resx - me->sta_cursor.stc_cellx);
		}
		me->sta_cursor.stc_cellx = 0;
		break;

	case '\n':
		/* Ignore '\n' after an implicit line-wrap. */
		if (!(me->sta_flags & SVGA_TTYACCESS_F_EOL))
			++me->sta_cursor.stc_celly;
		if (me->sta_cursor.stc_celly >= me->sta_scroll_yend) {
			me->sta_cursor.stc_celly = me->_sta_scrl_ymax;
			svga_ttyaccess_scrollone(me, ansitty_assvga(self));
		}
		break;

	default: {
		/* Check if we need to scroll. */
		if (me->sta_cursor.stc_celly >= me->sta_scroll_yend) {
			me->sta_cursor.stc_celly = me->_sta_scrl_ymax;
			svga_ttyaccess_scrollone(me, ansitty_assvga(self));
		}

		/* Print the character to the screen. */
		(*me->sta_setcell)(me, ansitty_assvga(self),
		                   me->sta_cursor.stc_cellx +
		                   me->sta_cursor.stc_celly *
		                   me->sta_scan,
		                   ch);

		/* Advance the cursor. */
		++me->sta_cursor.stc_cellx;

		/* Check for line overflow. */
		if (me->sta_cursor.stc_cellx >= me->sta_resx) {
			me->sta_cursor.stc_cellx = 0;
			++me->sta_cursor.stc_celly;

			/* Set the EOL flag after an implicit line-feed */
			me->sta_flags |= SVGA_TTYACCESS_F_EOL;
maybe_hide_cursor_after_eol:
			if (me->sta_cursor.stc_celly >= me->sta_resy) {
				/* Hide the hardware cursor (if it was visible before) */
				if (!(self->at_ttymode & ANSITTY_MODE_HIDECURSOR) &&
				    (me->sta_flags & SVGA_TTYACCESS_F_ACTIVE))
					(*me->sta_hidecursor)(me);
				goto after_clear_eol_nocursor;
			}
			goto after_clear_eol;
		}
	}	break;

	}

	/* Clear the EOL flag. */
	me->sta_flags &= ~SVGA_TTYACCESS_F_EOL;
after_clear_eol:
	if (!(self->at_ttymode & ANSITTY_MODE_HIDECURSOR) &&
	    (me->sta_flags & SVGA_TTYACCESS_F_ACTIVE))
		(*me->sta_showcursor)(me); /* Update hardware cursor. */
after_clear_eol_nocursor:
	atomic_lock_release(&me->sta_lock);
}

PRIVATE NONNULL((1)) void LIBANSITTY_CC
svga_ansitty_v_setcursor(struct ansitty *__restrict self,
                         ansitty_coord_t x, ansitty_coord_t y,
                         bool update_hw_cursor) {
	REF struct svga_ttyaccess *me;
	me = ansitty_getaccess(self);
	FINALLY_DECREF_UNLIKELY(me);
	if unlikely(x >= me->sta_resx)
		x = me->sta_resx - 1;
	if unlikely(y >= me->sta_resy)
		y = me->sta_resy - 1;
	atomic_lock_acquire(&me->sta_lock);
	me->sta_cursor.stc_cellx = x;
	me->sta_cursor.stc_celly = y;
	me->sta_flags &= ~SVGA_TTYACCESS_F_EOL;
	if (update_hw_cursor &&
	    !(self->at_ttymode & ANSITTY_MODE_HIDECURSOR) &&
	    (me->sta_flags & SVGA_TTYACCESS_F_ACTIVE))
		(*me->sta_showcursor)(me); /* Update hardware cursor. */
	atomic_lock_release(&me->sta_lock);
}

PRIVATE NONNULL((1, 2)) void LIBANSITTY_CC
svga_ansitty_v_getcursor(struct ansitty *__restrict self,
                         ansitty_coord_t ppos[2]) {
	union svga_tty_cursor cur;
	REF struct svga_ttyaccess *me;
	me           = ansitty_getaccess(self);
	cur.stc_word = ATOMIC_READ(me->sta_cursor.stc_word);
	ppos[0]      = cur.stc_cellx;
	ppos[1]      = cur.stc_celly;
	decref_unlikely(me);
}

PRIVATE NONNULL((1, 2)) void LIBANSITTY_CC
svga_ansitty_v_getsize(struct ansitty *__restrict self,
                       ansitty_coord_t psize[2]) {
	REF struct svga_ttyaccess *me;
	me       = ansitty_getaccess(self);
	psize[0] = me->sta_resx;
	psize[1] = me->sta_resy;
	decref_unlikely(me);
}

PRIVATE NONNULL((1)) void LIBANSITTY_CC
svga_ansitty_v_copycell(struct ansitty *__restrict self,
                        ansitty_offset_t dst_offset,
                        ansitty_coord_t count) {
	REF struct svga_ttyaccess *me;
	uintptr_t srcaddr, dstaddr, copyend, dispend;
	me = ansitty_getaccess(self);
	FINALLY_DECREF_UNLIKELY(me);
	atomic_lock_acquire(&me->sta_lock);
	srcaddr = me->sta_cursor.stc_celly;
	/* Yes: sta_resx (and not `sta_scan'); s.a. the documentation of `sta_copycell' */
	srcaddr *= me->sta_resx;
	srcaddr += me->sta_cursor.stc_cellx;
	dstaddr = srcaddr + dst_offset;

	/* Limit copy range at the start of destination */
	if ((intptr_t)dstaddr < 0) {
		size_t underflow;
		underflow = (size_t)0 - dstaddr;
		dstaddr   = 0;
		if (OVERFLOW_UADD(srcaddr, underflow, &srcaddr))
			goto done;
	}

	/* Limit copy range at the end of the destination */
	if (OVERFLOW_UADD(dstaddr, count, &copyend)) {
		count   = ((uintptr_t)-1) - dstaddr;
		copyend = ((uintptr_t)-1);
	}
	dispend = me->sta_resy * me->sta_resx;
	if (copyend > dispend) {
		size_t overflow = copyend - me->sta_resy;
		if (OVERFLOW_USUB(count, overflow, &count))
			goto done;
	}

	/* Limit copy range at the end of the source */
	if unlikely(OVERFLOW_UADD(srcaddr, count, &copyend) || copyend > dispend) {
		size_t maxcount, overflow;
		maxcount = dispend - srcaddr;
		overflow = count - maxcount;

		/* Do the actual cell-copy. */
		assert(srcaddr <= dispend);
		assert(dstaddr <= dispend);
		assert((srcaddr + maxcount) <= dispend);
		assert((dstaddr + maxcount) <= dispend);
		(*me->sta_copycell)(me, dstaddr, srcaddr, maxcount);

		/* Fill `overflow' cells at `dstaddr + maxcount' with ' ' */
		dstaddr += maxcount;
		if (me->sta_scan > me->sta_resx) {
			size_t delta = me->sta_scan - me->sta_resx;
			dstaddr += (dstaddr / me->sta_resx) * delta;
		}
		(*me->sta_fillcells)(me, ansitty_assvga(self),
		                     dstaddr, ' ', overflow);
	} else {
		/* Do the actual cell-copy. */
		assert(srcaddr <= dispend);
		assert(dstaddr <= dispend);
		assert((srcaddr + count) <= dispend);
		assert((dstaddr + count) <= dispend);
		(*me->sta_copycell)(me, dstaddr, srcaddr, count);
	}

done:
	atomic_lock_release(&me->sta_lock);
}

PRIVATE NONNULL((1)) void LIBANSITTY_CC
svga_ansitty_v_fillcell(struct ansitty *__restrict self,
                        char32_t ch,
                        ansitty_coord_t count) {
	REF struct svga_ttyaccess *me;
	uintptr_t dstaddr, fillend, dispend;
	me = ansitty_getaccess(self);
	FINALLY_DECREF_UNLIKELY(me);
	atomic_lock_acquire(&me->sta_lock);
	dstaddr = me->sta_cursor.stc_cellx +
	          me->sta_cursor.stc_celly *
	          me->sta_resx;
	dispend = me->sta_resy * me->sta_resx;
	/* Limit `count' to what can be put on-screen. */
	if (OVERFLOW_UADD(dstaddr, count, &fillend) || fillend > dispend) {
		if unlikely(OVERFLOW_USUB(dispend, dstaddr, &count))
			goto done;
	}

	/* Adjust `count' for scanlines */
	if (me->sta_scan > me->sta_resx) {
		size_t aligned_size;
		size_t delta = me->sta_scan - me->sta_resx;
		dstaddr      = me->sta_cursor.stc_cellx + me->sta_cursor.stc_celly * me->sta_scan;
		aligned_size = dstaddr % me->sta_scan; /* # of characters before first line */
		aligned_size += count;                 /* Total number of characters from start of first line */
		aligned_size /= me->sta_resx;          /* Number of line-feeds included in the fill. */
		count += aligned_size * delta;         /* Include delta induced by line-feeds. */
	}

	/* Do the fill. */
	(*me->sta_fillcells)(me, ansitty_assvga(self),
	                     dstaddr, ch, count);
done:
	atomic_lock_release(&me->sta_lock);
}

PRIVATE NONNULL((1)) void LIBANSITTY_CC
svga_ansitty_v_setttymode(struct ansitty *__restrict self,
                          uint16_t new_ttymode) {
	REF struct svga_ttyaccess *me;
	me = ansitty_getaccess(self);
	FINALLY_DECREF_UNLIKELY(me);
	atomic_lock_acquire(&me->sta_lock);
	if likely(me->sta_flags & SVGA_TTYACCESS_F_ACTIVE) {
		/* Update the state of the on-screen cursor. */
		if (new_ttymode & ANSITTY_MODE_HIDECURSOR) {
			(*me->sta_hidecursor)(me);
		} else if (me->sta_cursor.stc_celly < me->sta_resy) {
			(*me->sta_showcursor)(me);
		}
	}
	atomic_lock_release(&me->sta_lock);
}

PRIVATE NONNULL((1)) void LIBANSITTY_CC
svga_ansitty_v_scrollregion(struct ansitty *__restrict self,
                            ansitty_coord_t start_line,
                            ansitty_coord_t end_line) {
	REF struct svga_ttyaccess *me;
	me = ansitty_getaccess(self);
	FINALLY_DECREF_UNLIKELY(me);
	atomic_lock_acquire(&me->sta_lock);
	if (start_line < 0)
		start_line = 0;
	if (end_line > me->sta_resy)
		end_line = me->sta_resy;
	if (start_line > end_line)
		start_line = end_line;
	me->sta_scroll_ystart = start_line;
	me->sta_scroll_yend   = end_line;
	svga_ttyaccess__update_scrl(me);
	atomic_lock_release(&me->sta_lock);
}


INTERN_CONST struct ansitty_operators const svga_ansitty_ops = {
	.ato_putc         = &svga_ansitty_v_putc,
	.ato_setcursor    = &svga_ansitty_v_setcursor,
	.ato_getcursor    = &svga_ansitty_v_getcursor,
	.ato_getsize      = &svga_ansitty_v_getsize,
	.ato_copycell     = &svga_ansitty_v_copycell,
	.ato_fillcell     = &svga_ansitty_v_fillcell,
	.ato_setttymode   = &svga_ansitty_v_setttymode,
	.ato_scrollregion = &svga_ansitty_v_scrollregion,
};



PRIVATE NOBLOCK WUNUSED NONNULL((2)) uint16_t
NOTHROW(FCALL svga_ttyaccess_makecell_htxt)(char32_t ch,
                                            struct svgatty *__restrict tty) {
	uint16_t result;
	result = (uint16_t)basevga_defaultfont_encode(ch);
	result |= (uint16_t)tty->at_ansi.at_color << 8;
	return result;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_activate_htxt)(struct svga_ttyaccess *__restrict self) {
	struct svga_ttyaccess_txt *me;
	me = (struct svga_ttyaccess_txt *)self;

	/* Load the default font into video memory. */
	basevga_wrvmem(0x20000, basevga_defaultfont, sizeof(basevga_defaultfont));

	/* Populate the video text page with the expected contents. */
	memcpy(svga_ttyaccess_txt_vmem(me),
	       svga_ttyaccess_txt_dmem(me),
	       me->sta_scan * me->sta_resx);
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL svga_ttyaccess_v_setcell_htxt)(struct svga_ttyaccess *__restrict self,
                                             struct svgatty *__restrict tty,
                                             uintptr_t address, char32_t ch) {
	u16 word;
	struct svga_ttyaccess_txt *me;
	me   = (struct svga_ttyaccess_txt *)self;
	word = svga_ttyaccess_makecell_htxt(ch, tty);
	svga_ttyaccess_txt_dmem(me)[address] = word;
	if likely(me->sta_flags & SVGA_TTYACCESS_F_ACTIVE)
		svga_ttyaccess_txt_vmem(me)[address] = word;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_hidecursor_htxt)(struct svga_ttyaccess *__restrict self) {
	if (!(self->sta_flags & _SVGA_TTYACCESS_F_HWCUROFF)) {
		vga_wcrt(VGA_CRTC_CURSOR_START, vga_rcrt(VGA_CRTC_CURSOR_START) | VGA_CRA_FCURSOR_DISABLE);
		self->sta_flags |= _SVGA_TTYACCESS_F_HWCUROFF;
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_showcursor_htxt)(struct svga_ttyaccess *__restrict self) {
	uint16_t address;

	/* Write the intended cursor position into hardware. */
	address = self->sta_cursor.stc_cellx +
	          self->sta_cursor.stc_celly *
	          self->sta_scan;
	vga_wcrt(VGA_CRTC_CURSOR_HI, (uint8_t)(address >> 8));
	vga_wcrt(VGA_CRTC_CURSOR_LO, (uint8_t)(address));

	/* Show the cursor if it was hidden before. */
	if (self->sta_flags & _SVGA_TTYACCESS_F_HWCUROFF) {
		vga_wcrt(VGA_CRTC_CURSOR_START, vga_rcrt(VGA_CRTC_CURSOR_START) & ~VGA_CRA_FCURSOR_DISABLE);
		self->sta_flags &= ~_SVGA_TTYACCESS_F_HWCUROFF;
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_copycell_htxt_nooverscan)(struct svga_ttyaccess *__restrict self,
                                                         uintptr_t to_cellid, uintptr_t from_cellid,
                                                         size_t num_cells) {
	u16 *dst, *src;
	struct svga_ttyaccess_txt *me;
	me  = (struct svga_ttyaccess_txt *)self;
	src = svga_ttyaccess_txt_dmem(me) + from_cellid;
	dst = svga_ttyaccess_txt_dmem(me) + to_cellid;
	src = memmovew(dst, src, num_cells); /* Modify display buffer */
	if (self->sta_flags & SVGA_TTYACCESS_F_ACTIVE) {
		dst = svga_ttyaccess_txt_vmem(me) + to_cellid;
		memcpyw(dst, src, num_cells); /* Copy to video memory */
	}
}

PRIVATE NOBLOCK NONNULL((1)) uint16_t
NOTHROW(FCALL svga_ttyaccess_getcell_htxt_without_overscan)(struct svga_ttyaccess_txt *__restrict self,
                                                            uintptr_t screen_index) {
	size_t delta = self->sta_scan - self->sta_resx;
	screen_index += (screen_index / self->sta_resx) * delta;
	return svga_ttyaccess_txt_dmem(self)[screen_index];
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_setcell_htxt_without_overscan)(struct svga_ttyaccess_txt *__restrict self,
                                                            uintptr_t screen_index, uint16_t val) {
	size_t delta = self->sta_scan - self->sta_resx;
	screen_index += (screen_index / self->sta_resx) * delta;
	svga_ttyaccess_txt_dmem(self)[screen_index] = val;
	if (self->sta_flags & SVGA_TTYACCESS_F_ACTIVE)
		svga_ttyaccess_txt_vmem(self)[screen_index] = val;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_copycell_htxt_overscan)(struct svga_ttyaccess *__restrict self,
                                                       uintptr_t to_cellid, uintptr_t from_cellid,
                                                       size_t num_cells) {
	struct svga_ttyaccess_txt *me;
	me  = (struct svga_ttyaccess_txt *)self;
	if (from_cellid < to_cellid) {
		while (num_cells--) {
			u16 word;
			word = svga_ttyaccess_getcell_htxt_without_overscan(me, from_cellid);
			svga_ttyaccess_setcell_htxt_without_overscan(me, to_cellid, word);
			++from_cellid;
			++to_cellid;
		}
	} else {
		from_cellid += num_cells;
		to_cellid += num_cells;
		while (num_cells--) {
			u16 word;
			--from_cellid;
			--to_cellid;
			word = svga_ttyaccess_getcell_htxt_without_overscan(me, from_cellid);
			svga_ttyaccess_setcell_htxt_without_overscan(me, to_cellid, word);
		}
	}
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL svga_ttyaccess_v_fillcells_htxt)(struct svga_ttyaccess *__restrict self,
                                               struct svgatty *__restrict tty,
                                               uintptr_t start, char32_t ch, size_t num_cells) {
	u16 word;
	struct svga_ttyaccess_txt *me;
	me   = (struct svga_ttyaccess_txt *)self;
	word = svga_ttyaccess_makecell_htxt(ch, tty);
	memsetw(&svga_ttyaccess_txt_dmem(me)[start], word, num_cells);
	if (me->sta_flags & SVGA_TTYACCESS_F_ACTIVE)
		memsetw(&svga_ttyaccess_txt_vmem(me)[start], word, num_cells);
}

/* Initialize the following fields of `self':
 * - self->sta_refcnt = 1;
 * - atomic_lock_init(&self->sta_lock);
 * - self->sta_mode  = mode;
 * - self->sta_flags = SVGA_TTYACCESS_F_ACTIVE;
 * - self->sta_vmem  = ...;
 * - self->sta_cursor.stc_word = 0; */
PRIVATE NONNULL((1, 2)) void FCALL
svga_ttyaccess_initcommon(struct svga_ttyaccess *__restrict self,
                          struct svga_modeinfo const *__restrict mode)
		THROWS(E_WOULDBLOCK) {
	void *mapbase;
	size_t vmemsize;

	/* Initialize the `sta_vmem' node of `self' */
	vmemsize = mode->smi_scanline * mode->smi_resy;
	vmemsize = CEIL_ALIGN(vmemsize, PAGESIZE);
	mman_lock_write(&mman_kernel);
	mapbase = mman_getunmapped_or_unlock_device(vmemsize);

	/* Prepare the buffer region */
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	if unlikely(!pagedir_kernelprepare(mapbase, vmemsize)) {
		mman_lock_endwrite(&mman_kernel);
		THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
	}
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
	self->sta_vmem.mn_minaddr = (byte_t *)mapbase;
	self->sta_vmem.mn_maxaddr = (byte_t *)mapbase + vmemsize - 1;
	self->sta_vmem.mn_flags   = MNODE_F_PWRITE | MNODE_F_PREAD | MNODE_F_SHARED |
	                              MNODE_F_MPREPARED | MNODE_F_KERNPART | MNODE_F_NOSPLIT |
	                              MNODE_F_NOMERGE;
	self->sta_vmem.mn_part    = NULL; /* Reserved node. */
	self->sta_vmem.mn_fspath  = NULL;
	self->sta_vmem.mn_fsname  = NULL;
	self->sta_vmem.mn_mman    = &mman_kernel;
	DBG_memset(&self->sta_vmem.mn_partoff, 0xcc, sizeof(self->sta_vmem.mn_partoff));
	DBG_memset(&self->sta_vmem.mn_link, 0xcc, sizeof(self->sta_vmem.mn_link));
	LIST_ENTRY_UNBOUND_INIT(&self->sta_vmem.mn_writable);
	mman_mappings_insert(&mman_kernel, &self->sta_vmem);
	mman_lock_endwrite(&mman_kernel);

	/* Bind video memory to our custom buffer mapping. */
	pagedir_map(mapbase, vmemsize, (physaddr_t)mode->smi_lfb,
	            PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE);

	/* Initialize all the resulting fields of `self' */
	self->sta_refcnt = 1;
	atomic_lock_init(&self->sta_lock);
	self->sta_mode  = mode;
	self->sta_flags = SVGA_TTYACCESS_F_ACTIVE; /* Must mark as active since we already mapped physical memory! */
	self->sta_cursor.stc_word = 0;
}



PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) REF struct svga_ttyaccess_txt *FCALL
svga_makettyaccess_txt(struct svgadev *__restrict UNUSED(self),
                       struct svga_modeinfo const *__restrict mode) {
	REF struct svga_ttyaccess_txt *result;
	size_t dispsz;

	/* Allocate the object. */
	dispsz = mode->smi_resy * mode->smi_scanline * sizeof(uint16_t);
	result = (REF struct svga_ttyaccess_txt *)kmalloc(offsetof(struct svga_ttyaccess_txt, stt_display) +
	                                                  dispsz,
	                                                  GFP_NORMAL);
	/* Initialize common fields. */
	TRY {
		svga_ttyaccess_initcommon(result, mode);
	} EXCEPT {
		kfree(result);
		RETHROW();
	}
	result->sta_resx       = mode->smi_resx;
	result->sta_resy       = mode->smi_resy;
	result->sta_scan       = mode->smi_scanline / 2;
	result->sta_activate   = &svga_ttyaccess_v_activate_htxt;
	result->sta_setcell    = &svga_ttyaccess_v_setcell_htxt;
	result->sta_hidecursor = &svga_ttyaccess_v_hidecursor_htxt;
	result->sta_showcursor = &svga_ttyaccess_v_showcursor_htxt;
	result->sta_copycell   = &svga_ttyaccess_v_copycell_htxt_nooverscan;
	result->sta_fillcells  = &svga_ttyaccess_v_fillcells_htxt;
	if (result->sta_scan > result->sta_resx)
		result->sta_copycell = &svga_ttyaccess_v_copycell_htxt_overscan;
	result->sta_scroll_ystart = 0;
	result->sta_scroll_yend   = result->sta_resy;
	svga_ttyaccess__update_scrl(result);

	/* Fill in the saved display state.
	 * This is the only time we read from display memory! */
	memcpy(svga_ttyaccess_txt_dmem(result),
	       svga_ttyaccess_txt_vmem(result),
	       dispsz);
	return result;
}



/************************************************************************/
/* Graphics mode TTY                                                    */
/************************************************************************/

/* Redraw graphics cells
 * NOTE: This functions may only be called when `SVGA_TTYACCESS_F_ACTIVE' is set. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_makettyaccess_redraw_cells_gfx)(struct svga_ttyaccess_gfx *__restrict self,
                                                   uintptr_t start, size_t num_cells) {
	uintptr_t i;
	for (i = 0; i < num_cells; ++i)
		(*self->stx_redraw_cell)(self, start + i);

	/* Check if we need to redraw the cursor. */
	if (self->sta_flags & _SVGA_TTYACCESS_F_SWCURON) {
		uintptr_t cursor_addr;
		cursor_addr = self->stx_swcur.stc_cellx +
		              self->stx_swcur.stc_celly *
		              self->sta_resx;
		if (cursor_addr >= start && cursor_addr < start + num_cells)
			(*self->stx_redraw_cursor)(self);
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_activate_gfx)(struct svga_ttyaccess *__restrict self) {
	/* Redraw the entire screen after reactivation. */
	struct svga_ttyaccess_gfx *me = (struct svga_ttyaccess_gfx *)self;
	svga_makettyaccess_redraw_cells_gfx(me, 0, me->sta_resx * me->sta_resy);
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL svga_ttyaccess_v_setcell_gfx)(struct svga_ttyaccess *__restrict self,
                                            struct svgatty *__restrict tty,
                                            uintptr_t address, char32_t ch) {
	struct svga_ttyaccess_gfx *me = (struct svga_ttyaccess_gfx *)self;
	byte_t const *pattern;
	pattern = basevga_defaultfont[basevga_defaultfont_encode(ch)];
	memcpy(me->stx_display[address].sgc_lines, pattern, 16);
	me->stx_display[address].sgc_color = tty->at_ansi.at_color;

	/* Don't touch display memory when not active! */
	if unlikely(!(me->sta_flags & SVGA_TTYACCESS_F_ACTIVE))
		return;
	(*me->stx_redraw_cell)(me, address);

	/* Check if we need to redraw the cursor. */
	if (me->sta_flags & _SVGA_TTYACCESS_F_SWCURON) {
		uintptr_t cursor_addr;
		cursor_addr = me->stx_swcur.stc_cellx +
		              me->stx_swcur.stc_celly *
		              me->sta_resx;
		if (cursor_addr == address)
			(*me->stx_redraw_cursor)(me);
	}
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL svga_ttyaccess_v_fillcells_gfx)(struct svga_ttyaccess *__restrict self,
                                              struct svgatty *__restrict tty,
                                              uintptr_t start, char32_t ch, size_t num_cells) {
	struct svga_ttyaccess_gfx *me = (struct svga_ttyaccess_gfx *)self;
	struct svga_gfxcell *src, *dst;
	byte_t const *pattern;
	size_t count;
	if unlikely(!num_cells)
		return;
	/* Properly fill in the first cell. */
	pattern = basevga_defaultfont[basevga_defaultfont_encode(ch)];
	src     = &me->stx_display[start];
	memcpy(src->sgc_lines, pattern, 16);
	src->sgc_color = tty->at_ansi.at_color;
	count          = num_cells - 1;
	if unlikely(!count) {
		/* Don't touch display memory when not active! */
		if unlikely(!(me->sta_flags & SVGA_TTYACCESS_F_ACTIVE))
			return;
		(*me->stx_redraw_cell)(me, start);

		/* Check if we need to redraw the cursor. */
		if (me->sta_flags & _SVGA_TTYACCESS_F_SWCURON) {
			uintptr_t cursor_addr;
			cursor_addr = me->stx_swcur.stc_cellx +
			              me->stx_swcur.stc_celly *
			              me->sta_resx;
			if (cursor_addr == start)
				(*me->stx_redraw_cursor)(me);
		}
		return;
	}

	/* Copy template into all additional cells. */
	dst = src + 1;
	do {
		dst = (struct svga_gfxcell *)mempcpy(dst, src, sizeof(struct svga_gfxcell));
	} while (--count);

	/* Don't touch display memory when not active! */
	if likely(me->sta_flags & SVGA_TTYACCESS_F_ACTIVE)
		svga_makettyaccess_redraw_cells_gfx(me, start, num_cells);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_copycell_gfx)(struct svga_ttyaccess *__restrict self,
                                             uintptr_t to_cellid, uintptr_t from_cellid,
                                             size_t num_cells) {
	struct svga_gfxcell *dst, *src;
	struct svga_ttyaccess_gfx *me;
	me  = (struct svga_ttyaccess_gfx *)self;
	src = me->stx_display + from_cellid;
	dst = me->stx_display + to_cellid;
	memmove(dst, src, num_cells, sizeof(struct svga_gfxcell));
	if likely(me->sta_flags & SVGA_TTYACCESS_F_ACTIVE)
		svga_makettyaccess_redraw_cells_gfx(me, to_cellid, num_cells);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_showcursor_gfx)(struct svga_ttyaccess *__restrict self) {
	struct svga_ttyaccess_gfx *me;
	me = (struct svga_ttyaccess_gfx *)self;

	/* Redraw the cursor's old cell to hide it. */
	if (me->sta_flags & _SVGA_TTYACCESS_F_SWCURON) {
		(*me->stx_redraw_cell)(me,
		                       me->stx_swcur.stc_cellx +
		                       me->stx_swcur.stc_celly *
		                       me->sta_resx);
	}

	/* Remember the new software cursor position. */
	me->stx_swcur.stc_word = me->sta_cursor.stc_word;
	me->sta_flags |= _SVGA_TTYACCESS_F_SWCURON;

	/* Draw a cursor at the new position. */
	(*me->stx_redraw_cursor)(me);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_hidecursor_gfx)(struct svga_ttyaccess *__restrict self) {
	struct svga_ttyaccess_gfx *me;
	me = (struct svga_ttyaccess_gfx *)self;
	if (me->sta_flags & _SVGA_TTYACCESS_F_SWCURON) {
		/* Redraw cell to override the cursor.
		 * Technically, we'd only need to redraw the area actually occupied
		 * by  the cursor, but this is keeping  it a little more simple! :) */
		(*me->stx_redraw_cell)(me,
		                       me->stx_swcur.stc_cellx +
		                       me->stx_swcur.stc_celly *
		                       me->sta_resx);
		me->sta_flags &= ~_SVGA_TTYACCESS_F_SWCURON;
	}
}


PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) REF struct svga_ttyaccess_gfx *FCALL
svga_makettyaccess_gfx(struct svgadev *__restrict UNUSED(self),
                       struct svga_modeinfo const *__restrict mode) {
	REF struct svga_ttyaccess_gfx *result;
	size_t dispsz;
	uintptr_half_t cells_x = mode->smi_resx / 9;
	uintptr_half_t cells_y = mode->smi_resy / 16;

	/* Allocate the object. */
	dispsz = cells_x * cells_y * sizeof(struct svga_gfxcell);
	result = (REF struct svga_ttyaccess_gfx *)kmalloc(offsetof(struct svga_ttyaccess_gfx, stx_display) +
	                                                  dispsz,
	                                                  GFP_NORMAL);

	/* Initialize common fields. */
	TRY {
		svga_ttyaccess_initcommon(result, mode);
	} EXCEPT {
		kfree(result);
		RETHROW();
	}

	/* Configure dimensions. */
	result->sta_resy          = mode->smi_resy / 16;
	result->sta_resx          = mode->smi_resx / 9;
	result->sta_scan          = result->sta_resx;
	result->stx_cellscan      = 16 * mode->smi_scanline;
	result->sta_scroll_ystart = 0;
	result->sta_scroll_yend   = result->sta_resy;
	svga_ttyaccess__update_scrl(result);

	/* Configure operators. */
	result->sta_setcell    = &svga_ttyaccess_v_setcell_gfx;
	result->sta_showcursor = &svga_ttyaccess_v_showcursor_gfx;
	result->sta_hidecursor = &svga_ttyaccess_v_hidecursor_gfx;
	result->sta_copycell   = &svga_ttyaccess_v_copycell_gfx;
	result->sta_fillcells  = &svga_ttyaccess_v_fillcells_gfx;
	result->sta_activate   = &svga_ttyaccess_v_activate_gfx;

	/* BPP-specific operators. */
	switch (mode->smi_bits_per_pixel) {
#ifndef __INTELLISENSE__
#define SETOPS(bpp)                                                                    \
	{                                                                                  \
		INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL PP_CAT2(svga_ttyaccess_v_redraw_cell_gfx, bpp))(struct svga_ttyaccess_gfx *__restrict self, uintptr_t address); \
		INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL PP_CAT2(svga_ttyaccess_v_redraw_cursor_gfx, bpp))(struct svga_ttyaccess *__restrict self); \
		result->stx_redraw_cell   = &PP_CAT2(svga_ttyaccess_v_redraw_cell_gfx, bpp);   \
		result->stx_redraw_cursor = &PP_CAT2(svga_ttyaccess_v_redraw_cursor_gfx, bpp); \
	}
//TODO:	case 1:         SETOPS(1);  break;
//TODO:	case 2:         SETOPS(2);  break;
//TODO:	case 3 ... 4:   SETOPS(4);  break;
	case 5 ... 8:   SETOPS(8);  break;
	case 9 ... 16:  SETOPS(16); break;
	case 17 ... 24: SETOPS(24); break;
	case 25 ... 32: SETOPS(32); break;
#undef SETOPS
#endif /* !__INTELLISENSE__ */

	default:
		/* Unsupported # of bits-per-pixel. */
		destroy(result);
		THROW(E_NOT_IMPLEMENTED_UNSUPPORTED);
		break;
	}

	/* Precalculate palette colors. */
	if (mode->smi_flags & SVGA_MODEINFO_F_PAL) {
		unsigned int i;
		for (i = 0; i < 16; ++i)
			result->stx_colors[i] = i;
	} else {
		unsigned int i;
		for (i = 0; i < 16; ++i) {
			struct vga_palcolor col;
			uint32_t dcl; /* DirectCoLor */
			col = basevga_defaultpal[i];
			dcl = (((col.vpc_r << 2) >> (8 - mode->smi_rbits)) << mode->smi_rshift) |
			      (((col.vpc_g << 2) >> (8 - mode->smi_gbits)) << mode->smi_gshift) |
			      (((col.vpc_b << 2) >> (8 - mode->smi_bbits)) << mode->smi_bshift);
			result->stx_colors[i] = dcl;
		}
	}

	/* Use a white cursor by default. */
	result->stx_ccolor = result->stx_colors[ANSITTY_CL_WHITE];
	result->stx_swcur.stc_word = 0;

	/* Fill in the saved display state. */
	memset(result->stx_display, 0, dispsz);

	/* Set default color for all cells. */
	{
		size_t i;
		for (i = 0; i < cells_x * cells_y; ++i)
			result->stx_display[i].sgc_color = ANSITTY_CL_DEFAULT;
	}

	return result;
}


/* Create a TTY access object for the given `mode' */
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) REF struct svga_ttyaccess *FCALL
svgadev_makettyaccess(struct svgadev *__restrict self,
                      struct svga_modeinfo const *__restrict mode) {
	REF struct svga_ttyaccess *result;
	/* Support both hardware text-mode, as well as
	 * software emulation for higher  resolutions! */
	if (mode->smi_flags & SVGA_MODEINFO_F_TXT) {
		result = svga_makettyaccess_txt(self, mode);
	} else {
		result = svga_makettyaccess_gfx(self, mode);
	}
	return result;
}

DECL_END

#endif /* !GUARD_MODSVGA_TTY_C */
