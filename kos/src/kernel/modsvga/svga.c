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
#ifndef GUARD_MODSVGA_SVGA_C
#define GUARD_MODSVGA_SVGA_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver-param.h>
#include <kernel/driver.h>
#include <kernel/memory.h>
#include <kernel/mman.h>
#include <kernel/mman/sync.h>
#include <kernel/mman/unmapped.h>
#include <kernel/printk.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <kos/except.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libsvga/api.h>
#include <libsvga/chipset.h>
#include <libsvga/util/vgaio.h>

/**/
#include "svga.h"

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

#define ansitty_assvga(self) \
	container_of(self, struct svga_ansitty, at_ansi)
#define ansitty_getaccess(self) \
	arref_get(&ansitty_assvga(self)->sva_tty)


PRIVATE NONNULL((1, 2)) void FCALL
svga_setmode(struct svga_device *__restrict self,
             struct svga_modeinfo const *__restrict mode)
		THROWS(E_IOERROR) {

	/* Set the video mode requested by `tty' */
	(*self->svd_chipset.sc_ops.sco_setmode)(&self->svd_chipset, mode);

	/* Load default VGA font if `tty' uses hardware text mode. */
	if (mode->smi_flags & SVGA_MODEINFO_F_TXT) {
		basevga_wrvmem(0x20000, basevga_defaultfont, sizeof(basevga_defaultfont));

		/* Enable palette access */
		vga_setpas(basevga_IS1_R, 0);

		/* Write attribute registers relating to palette values. */
		if (basevga_flags & BASEVGA_FLAG_ISEGA) {
			uint8_t i;
			STATIC_ASSERT(sizeof(baseega_registers.vm_att_pal) == sizeof(basevga_defaultattpal));
			memcpy(baseega_registers.vm_att_pal, basevga_defaultattpal, sizeof(basevga_defaultattpal));
			vga_wattr(basevga_IS1_R, VGA_ATC_COLOR_PAGE,
			          (baseega_registers.vm_att_color_page & VGA_AT14_FRESERVED) | 0);
			for (i = 0; i < 16; ++i) {
				uint8_t temp;
				temp = baseega_registers.vm_att_pal[i];
				temp &= VGA_ATC_PALETTEn_FRESERVED;
				temp |= basevga_defaultattpal[i];
				vga_wattr(basevga_IS1_R, VGA_ATC_PALETTE0 + i, temp);
			}
		} else {
			uint8_t i, temp;
			temp = vga_rattr(basevga_IS1_R, VGA_ATC_COLOR_PAGE);
			temp &= VGA_AT14_FRESERVED;
			vga_wattr(basevga_IS1_R, VGA_ATC_COLOR_PAGE, temp);
			for (i = 0; i < 16; ++i) {
				temp = vga_rattr(basevga_IS1_R, VGA_ATC_PALETTE0 + i);
				temp &= VGA_ATC_PALETTEn_FRESERVED;
				temp |= basevga_defaultattpal[i];
				vga_wattr(basevga_IS1_R, VGA_ATC_PALETTE0 + i, temp);
			}
		}

		/* Disable palette access */
		vga_setpas(basevga_IS1_R, VGA_ATT_IW_PAS);
	}

	/* Load an ANSI-compatible color palette (if used by this mode) */
	if (mode->smi_flags & SVGA_MODEINFO_F_PAL)
		basevga_wrpal(0, basevga_defaultpal, 16);
}




/* Scroll up once */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_scrollone)(struct svga_ttyaccess *__restrict me,
                                        struct svga_ansitty *__restrict self) {
	(*me->sta_copycell)(me, 0, me->sta_scan, me->sta_resx * (me->sta_resy - 1));
	(*me->sta_fillcells)(me, me->sta_scan * (me->sta_resy - 1), ' ', me->sta_resx, self);
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
		if (me->sta_cursor.stc_celly >= me->sta_resy) {
			me->sta_cursor.stc_celly = me->sta_resy - 1;
			svga_ttyaccess_scrollone(me, ansitty_assvga(self));
		}
		advance = TABSIZE - (me->sta_cursor.stc_cellx % TABSIZE);
		if ((me->sta_cursor.stc_cellx + advance) > me->sta_resx)
			advance = me->sta_resx - me->sta_cursor.stc_cellx;
		(*me->sta_fillcells)(me,
		                     me->sta_cursor.stc_cellx +
		                     me->sta_cursor.stc_celly *
		                     me->sta_scan,
		                     ' ', advance,
		                     ansitty_assvga(self));
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
		if (me->sta_cursor.stc_celly >= me->sta_resy) {
			me->sta_cursor.stc_celly = me->sta_resy - 1;
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
			(*me->sta_fillcells)(me,
			                     me->sta_cursor.stc_cellx +
			                     me->sta_cursor.stc_celly *
			                     me->sta_scan,
			                     ' ',
			                     me->sta_resx - me->sta_cursor.stc_cellx,
			                     ansitty_assvga(self));
		}
		me->sta_cursor.stc_cellx = 0;
		break;

	case '\n':
		/* Ignore '\n' after an implicit line-wrap. */
		if (!(me->sta_flags & SVGA_TTYACCESS_F_EOL))
			++me->sta_cursor.stc_celly;
		if (me->sta_cursor.stc_celly >= me->sta_resy) {
			me->sta_cursor.stc_celly = me->sta_resy - 1;
			svga_ttyaccess_scrollone(me, ansitty_assvga(self));
		}
		break;

	default: {
		/* Check if we need to scroll. */
		if (me->sta_cursor.stc_celly >= me->sta_resy) {
			me->sta_cursor.stc_celly = me->sta_resy - 1;
			svga_ttyaccess_scrollone(me, ansitty_assvga(self));
		}

		/* Print the character to the screen. */
		(*me->sta_setcell)(me,
		                   me->sta_cursor.stc_cellx +
		                   me->sta_cursor.stc_celly *
		                   me->sta_scan,
		                   ch, ansitty_assvga(self));

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
				if (!(self->at_ttymode & ANSITTY_MODE_HIDECURSOR))
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
	if (!(self->at_ttymode & ANSITTY_MODE_HIDECURSOR))
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
	if (update_hw_cursor && !(self->at_ttymode & ANSITTY_MODE_HIDECURSOR))
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
		(*me->sta_fillcells)(me, dstaddr, ' ', overflow,
		                     ansitty_assvga(self));
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
	(*me->sta_fillcells)(me, dstaddr, ch, count,
	                     ansitty_assvga(self));
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

	/* Update the state of the on-screen cursor. */
	if (new_ttymode & ANSITTY_MODE_HIDECURSOR) {
		(*me->sta_hidecursor)(me);
	} else if (me->sta_cursor.stc_celly < me->sta_resy) {
		(*me->sta_showcursor)(me);
	}
	atomic_lock_release(&me->sta_lock);
}


PRIVATE struct ansitty_operators const svga_ansitty_ops = {
	.ato_putc       = &svga_ansitty_v_putc,
	.ato_setcursor  = &svga_ansitty_v_setcursor,
	.ato_getcursor  = &svga_ansitty_v_getcursor,
	.ato_getsize    = &svga_ansitty_v_getsize,
	.ato_copycell   = &svga_ansitty_v_copycell,
	.ato_fillcell   = &svga_ansitty_v_fillcell,
	.ato_setttymode = &svga_ansitty_v_setttymode,
};



/* Unmap, unprepare, and possibly free SVGA physical buffers.
 * The caller must be holding a write-lock to  `mman_kernel'. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_unmap_vmem)(struct svga_ttyaccess *__restrict self) {
	mman_mappings_removenode(&mman_kernel, &self->sta_vmem);

	/* This tty wasn't active in the end, then `page_free()'
	 * the  physical  memory pointed-to  by `self->sta_vmem' */
	if (!(self->sta_flags & SVGA_TTYACCESS_F_ACTIVE)) {
		byte_t *iter, *end;
		iter = (byte_t *)mnode_getaddr(&self->sta_vmem);
		end  = (byte_t *)mnode_getendaddr(&self->sta_vmem);
		for (; iter < end; iter += PAGESIZE) {
			physaddr_t addr = pagedir_translate(iter);
			physpage_t page = physaddr2page(addr);
			page_freeone(page);
		}
	}

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


PRIVATE NOBLOCK WUNUSED NONNULL((2)) uint16_t
NOTHROW(FCALL svga_ttyaccess_makecell_htxt)(char32_t ch,
                                            struct svga_ansitty *__restrict tty) {
	uint16_t result;
	result = (uint16_t)basevga_defaultfont_encode(ch);
	result |= (uint16_t)tty->at_ansi.at_color << 8;
	return result;
}

PRIVATE NOBLOCK NONNULL((1, 4)) void
NOTHROW(FCALL svga_ttyaccess_v_setcell_htxt)(struct svga_ttyaccess *__restrict self,
                                             uintptr_t address, char32_t ch,
                                             struct svga_ansitty *__restrict tty) {
	u16 *cell;
	cell = (u16 *)mnode_getaddr(&self->sta_vmem);
	cell += address;
	*cell = svga_ttyaccess_makecell_htxt(ch, tty);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_hidecursor_htxt)(struct svga_ttyaccess *__restrict self) {
	/* Don't touch the actual hardware registers when we're not the active TTY! */
	if (!(self->sta_flags & SVGA_TTYACCESS_F_ACTIVE))
		return;
	if (!(self->sta_flags & _SVGA_TTYACCESS_F_HWCUROFF)) {
		vga_wcrt(VGA_CRTC_CURSOR_START, vga_rcrt(VGA_CRTC_CURSOR_START) | VGA_CRA_FCURSOR_DISABLE);
		self->sta_flags |= _SVGA_TTYACCESS_F_HWCUROFF;
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_showcursor_htxt)(struct svga_ttyaccess *__restrict self) {
	uint16_t address;
	/* Don't touch the actual hardware registers when we're not the active TTY! */
	if (!(self->sta_flags & SVGA_TTYACCESS_F_ACTIVE))
		return;

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
	src = (u16 *)mnode_getaddr(&self->sta_vmem);
	dst = (u16 *)mnode_getaddr(&self->sta_vmem);
	src += from_cellid;
	dst += to_cellid;
	memmovew(dst, src, num_cells);
}

PRIVATE NOBLOCK NONNULL((1)) uint16_t
NOTHROW(FCALL svga_ttyaccess_getcell_htxt_without_overscan)(struct svga_ttyaccess *__restrict self,
                                                            uintptr_t screen_index) {
	u16 const *src;
	size_t delta = self->sta_scan - self->sta_resx;
	screen_index += (screen_index / self->sta_resx) * delta;
	src = (u16 const *)mnode_getaddr(&self->sta_vmem);
	src += screen_index;
	return *src;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_setcell_htxt_without_overscan)(struct svga_ttyaccess *__restrict self,
                                                            uintptr_t screen_index, uint16_t val) {
	u16 *dst;
	size_t delta = self->sta_scan - self->sta_resx;
	screen_index += (screen_index / self->sta_resx) * delta;
	dst = (u16 *)mnode_getaddr(&self->sta_vmem);
	dst += screen_index;
	*dst = val;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_copycell_htxt_overscan)(struct svga_ttyaccess *__restrict self,
                                                       uintptr_t to_cellid, uintptr_t from_cellid,
                                                       size_t num_cells) {
	if (from_cellid < to_cellid) {
		while (num_cells--) {
			u16 word;
			word = svga_ttyaccess_getcell_htxt_without_overscan(self, from_cellid);
			svga_ttyaccess_setcell_htxt_without_overscan(self, to_cellid, word);
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
			word = svga_ttyaccess_getcell_htxt_without_overscan(self, from_cellid);
			svga_ttyaccess_setcell_htxt_without_overscan(self, to_cellid, word);
		}
	}
}

PRIVATE NOBLOCK NONNULL((1, 5)) void
NOTHROW(FCALL svga_ttyaccess_v_fillcells_htxt)(struct svga_ttyaccess *__restrict self,
                                               uintptr_t start, char32_t ch, size_t num_cells,
                                               struct svga_ansitty *__restrict tty) {
	u16 *cell, word;
	cell = (u16 *)mnode_getaddr(&self->sta_vmem);
	cell += start;
	word = svga_ttyaccess_makecell_htxt(ch, tty);
	memsetw(cell, word, num_cells);
}


/* Create a TTY access object for the given `mode' */
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) REF struct svga_ttyaccess *FCALL
svga_makettyaccess(struct svga_device *__restrict self,
                   struct svga_modeinfo const *__restrict mode) {
	void *mapbase;
	REF struct svga_ttyaccess *result;
	size_t vmemsize;
	(void)self;
	if (!(mode->smi_flags & SVGA_MODEINFO_F_LFB))
		THROW(E_NOT_IMPLEMENTED_TODO); /* TODO: paged memory access! */
	vmemsize = mode->smi_scanline * mode->smi_resy;
	vmemsize = CEIL_ALIGN(vmemsize, PAGESIZE);
	result   = (REF struct svga_ttyaccess *)kmalloc(sizeof(struct svga_ttyaccess), GFP_NORMAL);
	TRY {
		/* Initialize the `sta_vmem' node of `result' */
		mman_lock_write(&mman_kernel);
		mapbase = mman_getunmapped_or_unlock_device(vmemsize);

		/* Prepare the buffer region */
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
		if unlikely(!pagedir_kernelprepare(mapbase, vmemsize)) {
			mman_lock_endwrite(&mman_kernel);
			THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
		}
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
	} EXCEPT {
		kfree(result);
		RETHROW();
	}

	result->sta_vmem.mn_minaddr = (byte_t *)mapbase;
	result->sta_vmem.mn_maxaddr = (byte_t *)mapbase + vmemsize - 1;
	result->sta_vmem.mn_flags   = MNODE_F_PWRITE | MNODE_F_PREAD | MNODE_F_SHARED |
	                              MNODE_F_MPREPARED | MNODE_F_KERNPART | MNODE_F_NOSPLIT |
	                              MNODE_F_NOMERGE;
	result->sta_vmem.mn_part    = NULL; /* Reserved node. */
	result->sta_vmem.mn_fspath  = NULL;
	result->sta_vmem.mn_fsname  = NULL;
	result->sta_vmem.mn_mman    = &mman_kernel;
	DBG_memset(&result->sta_vmem.mn_partoff, 0xcc, sizeof(result->sta_vmem.mn_partoff));
	DBG_memset(&result->sta_vmem.mn_link, 0xcc, sizeof(result->sta_vmem.mn_link));
	LIST_ENTRY_UNBOUND_INIT(&result->sta_vmem.mn_writable);
	mman_mappings_insert(&mman_kernel, &result->sta_vmem);
	mman_lock_endwrite(&mman_kernel);

	/* Bind video memory to our custom buffer mapping. */
	pagedir_map(mapbase, vmemsize, (physaddr_t)mode->smi_lfb,
	            PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE);

	/* Initialize all the resulting fields of `result' */
	result->sta_refcnt = 1;
	atomic_lock_init(&result->sta_lock);
	result->sta_mode  = mode;
	result->sta_flags = SVGA_TTYACCESS_F_ACTIVE; /* Must mark as active since we already mapped physical memory! */
	if (mode->smi_flags & SVGA_MODEINFO_F_TXT) {
		result->sta_resx       = mode->smi_resx;
		result->sta_resy       = mode->smi_resy;
		result->sta_cellw      = 8;
		result->sta_cellh      = 16;
		result->sta_scan       = mode->smi_scanline / 2;
		result->sta_setcell    = &svga_ttyaccess_v_setcell_htxt;
		result->sta_hidecursor = &svga_ttyaccess_v_hidecursor_htxt;
		result->sta_showcursor = &svga_ttyaccess_v_showcursor_htxt;
		result->sta_copycell   = &svga_ttyaccess_v_copycell_htxt_nooverscan;
		result->sta_fillcells  = &svga_ttyaccess_v_fillcells_htxt;
		if (result->sta_scan > result->sta_resx)
			result->sta_copycell = &svga_ttyaccess_v_copycell_htxt_overscan;
	} else {
		/* TODO */
		THROW(E_NOT_IMPLEMENTED_TODO);
	}
	result->sta_cursor.stc_word = 0;
	return result;
}




PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL svga_v_destroy)(struct mfile *__restrict self) {
	struct svga_device *me = (struct svga_device *)mfile_asansitty(self);
	arref_fini(&me->sva_tty);
	kfree((void *)me->svd_supmodev);
	(*me->svd_chipset.sc_ops.sco_fini)(&me->svd_chipset);
	ansittydev_v_destroy(self);
}

PRIVATE NONNULL((1)) syscall_slong_t KCALL
svga_v_ioctl(struct mfile *__restrict self, syscall_ulong_t cmd,
             USER UNCHECKED void *arg, iomode_t mode) THROWS(...) {
	struct svga_device *me = (struct svga_device *)mfile_asansitty(self);
	/* TODO: the promised ioctls for creating locks, ttys and changing video modes.
	 * NOTE: The  video-mode-change  part  should also  be  put into
	 *       `svga_ansitty_v_ioctl()' and `svga_userlock_v_ioctl()'. */
	(void)me;
	return ansittydev_v_ioctl(self, cmd, arg, mode);
}


/* SVGA TTY device operators. */
PRIVATE struct mfile_stream_ops const svga_v_stream_ops = {
	.mso_write = &ansittydev_v_write,
	.mso_ioctl = &svga_v_ioctl,
	.mso_hop   = &ansittydev_v_hop,
	.mso_tryas = &ansittydev_v_tryas,
};

PRIVATE struct ansittydev_ops const svga_ansittydev_ops = {{{{{
	.no_file = {
		.mo_destroy = &svga_v_destroy,
		.mo_changed = &ansittydev_v_changed,
		.mo_stream  = &svga_v_stream_ops,
	},
	.no_wrattr = &ansittydev_v_wrattr,
}}}}};



/* Default graphics mode hints.
 *
 * Note that modes can always be switched via ioctl(2).
 * These are on hints used to select the initial  mode. */
DEFINE_CMDLINE_PARAM_UINT32_VAR(default_resx, "xres", 1024);
DEFINE_CMDLINE_PARAM_UINT32_VAR(default_resy, "yres", 768);
DEFINE_CMDLINE_PARAM_UINT8_VAR(default_bpp, "bpp", 24);


PRIVATE NOBLOCK ATTR_FREETEXT WUNUSED NONNULL((1)) uint64_t
NOTHROW(FCALL calculate_mode_cost)(struct svga_modeinfo const *__restrict mode,
                                   uint32_t xres, uint32_t yres, uint8_t bpp) {
	uint64_t result = 0;
	result += abs((int32_t)xres - (int32_t)mode->smi_resx);
	result += abs((int32_t)yres - (int32_t)mode->smi_resy);
	result += abs((int8_t)bpp - (int8_t)mode->smi_bits_per_pixel);
#if 1 /* TODO: Remove me */
	if (!(mode->smi_flags & SVGA_MODEINFO_F_TXT))
		return (uint64_t)-1;
#endif
	return result;
}

PRIVATE NOBLOCK ATTR_FREETEXT ATTR_RETNONNULL WUNUSED NONNULL((1)) struct svga_modeinfo const *
NOTHROW(FCALL select_closest_video_mode)(struct svga_device *__restrict self,
                                         uint32_t xres, uint32_t yres, uint8_t bpp) {
	size_t i;
	uint64_t winner_cost;
	struct svga_modeinfo const *winner;
	winner      = svga_device_supmode(self, 0);
	winner_cost = calculate_mode_cost(winner, xres, yres, bpp);
	for (i = 1; i < self->svd_supmodec; ++i) {
		struct svga_modeinfo const *mode;
		uint64_t cost;
		mode = svga_device_supmode(self, i);
		cost = calculate_mode_cost(mode, xres, yres, bpp);
		if (winner_cost > cost) {
			winner_cost = cost;
			winner      = mode;
		}
	}
	return winner;
}

PRIVATE NOBLOCK ATTR_FREETEXT ATTR_RETNONNULL WUNUSED NONNULL((1)) struct svga_modeinfo const *
NOTHROW(FCALL get_default_video_mode)(struct svga_device *__restrict self) {
	return select_closest_video_mode(self, default_resx, default_resy, default_bpp);
}

/* Construct a default tty accessor object for `self' */
PRIVATE ATTR_FREETEXT ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct svga_ttyaccess *FCALL
svga_make_default_ttyaccess(struct svga_device *__restrict self) {
	REF struct svga_ttyaccess *result;
	struct svga_modeinfo const *mode;
	mode   = get_default_video_mode(self);
	result = svga_makettyaccess(self, mode);
	return result;
}


PRIVATE ATTR_FREETEXT NONNULL((2, 3)) ssize_t LIBSVGA_CC
svga_init_enumstring_callback(void *arg,
                              char const *__restrict name,
                              char const *__restrict value) {
	struct svga_chipset_driver const *driver;
	driver = (struct svga_chipset_driver const *)arg;
	printk(FREESTR(KERN_INFO "[svga] Chipset string %s.%s: %q\n"),
	       driver->scd_name, name, value);
	return 0;
}

#ifdef CONFIG_BUILDING_KERNEL_CORE
INTERN ATTR_FREETEXT void KCALL kernel_initialize_svga_driver(void)
#else /* CONFIG_BUILDING_KERNEL_CORE */
PRIVATE ATTR_FREETEXT DRIVER_INIT void KCALL svga_init(void)
#endif /* !CONFIG_BUILDING_KERNEL_CORE */
{
	struct svga_device *self;
	struct svga_chipset_driver const *drivers;
	size_t i, maxsize;

	/* Load available chipset drivers. */
	drivers = libsvga_chipset_getdrivers();

	/* Figure out the max required struct size for chipsets. */
	maxsize = 0;
	for (i = 0; drivers[i].scd_probe; ++i) {
		if (maxsize < drivers[i].scd_cssize)
			maxsize = drivers[i].scd_cssize;
	}

	/* Allocate an SVGA device buffer that is large enough to support any driver. */
	maxsize += offsetof(struct svga_device, svd_chipset);
	self = (struct svga_device *)kmalloc(maxsize, GFP_NORMAL);
	TRY {
		/* Go through the list of chipsets and probe for each of them. */
		for (i = 0;; ++i) {
			if unlikely(!drivers[i].scd_probe) {
				printk(FREESTR(KERN_ERR "[svga] No supported chipset detected\n"));
				kfree(self);
				return;
			}
			if ((*drivers[i].scd_probe)(&self->svd_chipset))
				break; /* Found one! */
		}
		TRY {
			byte_t *modev;
			size_t modec;
			uintptr_t iterator;

			self->svd_csdriver = &drivers[i];
			printk(FREESTR(KERN_INFO "[svga] Video chipset detected: %s\n"),
			       self->svd_csdriver->scd_name);

			/* Print chipset-specific strings. */
			if (self->svd_chipset.sc_ops.sco_strings) {
				(*self->svd_chipset.sc_ops.sco_strings)(&self->svd_chipset,
				                                      &svga_init_enumstring_callback,
				                                      (void *)self->svd_csdriver);
			}

			/* Found the chipset. - Now to enumerate all of its supported video modes. */
			self->svd_supmodeS = self->svd_chipset.sc_ops.sco_modeinfosize;
			self->svd_supmodeS = CEIL_ALIGN(self->svd_supmodeS, sizeof(void *));

			modec = 0;
			modev = (byte_t *)kmalloc_nx(32 * self->svd_supmodeS, GFP_NORMAL);
			if (!modev)
				modev = (byte_t *)kmalloc(self->svd_supmodeS, GFP_NORMAL);
			TRY {
				REF struct svga_ttyaccess *tty;

				/* Might not make much sense to force a lock here, but it's part of the contract... */
				svga_chipset_write(&self->svd_chipset);
				RAII_FINALLY { svga_chipset_endwrite(&self->svd_chipset); };

				iterator = 0;
				for (;;) {
					struct svga_modeinfo *mode;
					size_t avail, used;
					used  = modec * self->svd_supmodeS;
					avail = kmalloc_usable_size(modev);
					avail -= used;
					if (avail < self->svd_chipset.sc_ops.sco_modeinfosize) {
						byte_t *new_modev;
						avail = kmalloc_usable_size(modev) * 2;
						new_modev = (byte_t *)krealloc_nx(modev, avail, GFP_NORMAL);
						if unlikely(!new_modev) {
							size_t needed;
							needed = used;
							needed += self->svd_chipset.sc_ops.sco_modeinfosize;
							new_modev = (byte_t *)krealloc(modev, needed, GFP_NORMAL);
						}
						modev = new_modev;
					}

					/* Query mode information. */
					mode = (struct svga_modeinfo *)((byte_t *)modev + used);
					if (!(*self->svd_chipset.sc_ops.sco_getmode)(&self->svd_chipset, mode, &iterator))
						break; /* Done! */
					++modec; /* Remember that we've got another mode now! */

#if !defined(NDEBUG) && 1 /* XXX: Remove me */
					{
						char modenamebuf[64];
						char flagsbuf[64] = "", *ptr = flagsbuf;
						if (mode->smi_flags & SVGA_MODEINFO_F_LFB)
							ptr = stpcpy(ptr, "|lfb");
						if (mode->smi_flags & SVGA_MODEINFO_F_PAL)
							ptr = stpcpy(ptr, "|pal");
						if (mode->smi_flags & SVGA_MODEINFO_F_BW)
							ptr = stpcpy(ptr, "|bw");
						if (mode->smi_flags & SVGA_MODEINFO_F_TXT)
							ptr = stpcpy(ptr, "|txt");
						if (mode->smi_flags & SVGA_MODEINFO_F_PLANAR)
							ptr = stpcpy(ptr, "|planar");
						sprintf(modenamebuf, "%" PRIu32 "x%" PRIu32 "x%" PRIu8,
						        mode->smi_resx, mode->smi_resy, mode->smi_bits_per_pixel);

						printk(KERN_INFO "[svga] Supported: %-12s {flags:%s",
						       modenamebuf, flagsbuf + 1);
						if (mode->smi_flags & SVGA_MODEINFO_F_LFB)
							printk(KERN_INFO ",lfb:%#" PRIx64, (uint64_t)mode->smi_lfb);
						printk(KERN_INFO ",scan:%" PRIu32, mode->smi_scanline);
						if (!(mode->smi_flags & SVGA_MODEINFO_F_TXT))
							printk(KERN_INFO ",col:%" PRIu8, mode->smi_colorbits);
						if (!(mode->smi_flags & (SVGA_MODEINFO_F_PAL | SVGA_MODEINFO_F_BW))) {
							printk(KERN_INFO ",r:%" PRIu8 "@%" PRIu8
							                 ",g:%" PRIu8 "@%" PRIu8
							                 ",b:%" PRIu8 "@%" PRIu8,
							       mode->smi_rbits, mode->smi_rshift,
							       mode->smi_gbits, mode->smi_gshift,
							       mode->smi_bbits, mode->smi_bshift);
						}
						printk(KERN_INFO "}\n");
					}
#endif
				}

				/* Verify that we've got at least 1 mode. */
				if unlikely(!modec) {
					printk(FREESTR(KERN_ERR "[svga] No supported video modes detected?\n"));
					THROW(E_IOERROR);
				}

				/* Save the mode list. */
				self->svd_supmodec = modec;
				self->svd_supmodev = modev;

				/* Release unused memory from the modes list. */
				--modec;
				modec *= self->svd_supmodeS;
				modec += self->svd_chipset.sc_ops.sco_modeinfosize;
				modev = (byte_t *)krealloc_nx(modev, modec, GFP_NORMAL);
				if likely(modev != NULL)
					self->svd_supmodev = modev;

				/* By default the SVGA controller itself is active. */
				awref_init(&self->svd_active, self);

				/* Initialize the default TTY */
				self->sva_screen.ssd_dev    = self;
				self->sva_screen.ssd_active = 1;
				DBG_memset(&self->sva_screen.ssd_deact, 0xcc, sizeof(self->sva_screen.ssd_deact));
				tty = svga_make_default_ttyaccess(self);
				arref_init(&self->sva_tty, tty);
				TRY {
					/* Set the video mode requested by `tty' */
					svga_setmode(self, tty->sta_mode);

					/* Initialize underlying device objects. */
					_ansittydev_init(self, &svga_ansittydev_ops, &svga_ansitty_ops);

					/* Fill in remaining fields. */
					self->fn_mode   = S_IFCHR | 0600;
					self->dv_driver = incref(&drv_self);

					/* Register the device. */
					TRY {
						device_registerf(self, MKDEV(DEV_MAJOR_AUTO, 0), "svga");
					} EXCEPT {
						decref_nokill(&drv_self);
						RETHROW();
					}
				} EXCEPT {
					destroy(tty);
					RETHROW();
				}
			} EXCEPT {
				kfree(modev);
				RETHROW();
			}
		} EXCEPT {
			(*self->svd_chipset.sc_ops.sco_fini)(&self->svd_chipset);
			RETHROW();
		}
	} EXCEPT {
		kfree(self);
		RETHROW();
	}
}


DECL_END

#endif /* !GUARD_MODSVGA_SVGA_C */
