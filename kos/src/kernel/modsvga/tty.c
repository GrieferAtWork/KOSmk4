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
#define __WANT_VIDTTYACCESS__vta_mmlop
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
#include <hybrid/unaligned.h>

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
	me = container_of(self, struct svga_ttyaccess, _vta_mmplop);
	kfree(me);
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(mman) *
NOTHROW(LOCKOP_CC svga_ttyaccess_destroy_lop)(Toblockop(mman) *__restrict self,
                                              struct mman *__restrict UNUSED(obj)) {
	struct svga_ttyaccess *me;
	me = container_of(self, struct svga_ttyaccess, _vta_mmlop);
	svga_ttyaccess_unmap_vmem(me);
	me->_vta_mmplop.oplo_func = &svga_ttyaccess_destroy_postlop;
	return &me->_vta_mmplop;
}

INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_destroy)(struct vidttyaccess *__restrict self) {
	struct svga_ttyaccess *me;
	me = vidttyaccess_assvga(self);
	/* Remove `me->sta_vmem' from the kernel mman. */
	if (mman_lock_trywrite(&mman_kernel)) {
		svga_ttyaccess_unmap_vmem(me);
		mman_lock_endwrite(&mman_kernel);
	} else {
		me->_vta_mmlop.olo_func = &svga_ttyaccess_destroy_lop;
		oblockop_enqueue(&mman_kernel_lockops, &me->_vta_mmlop);
		mman_lockops_reap(&mman_kernel);
		return;
	}
	kfree(me);
}




PRIVATE NOBLOCK WUNUSED NONNULL((2)) uint16_t
NOTHROW(FCALL svga_ttyaccess_makecell_txt)(char32_t ch,
                                           struct ansitty *__restrict tty) {
	uint16_t result;
	result = (uint16_t)basevga_defaultfont_encode(ch);
	result |= (uint16_t)tty->at_color << 8;
	return result;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_activate_txt)(struct vidttyaccess *__restrict self) {
	struct svga_ttyaccess_txt *me;
	uint32_t fontbase;
	uint8_t temp;
	me = vidttyaccess_assvga_txt(self);

	/* Load the default font into video memory. */
	temp = baseega_registers.vr_mode.vm_seq_character_map;
	if (!(basevga_flags & BASEVGA_FLAG_ISEGA))
		temp = vga_rseq(VGA_SEQ_CHARACTER_MAP);
	temp     = VGA_SR03_CSETA_GET(temp);
	fontbase = 0x20000 + basevga_fontoffset[temp];
	basevga_wrvmem(fontbase, basevga_defaultfont, sizeof(basevga_defaultfont));

	temp = baseega_registers.vr_mode.vm_mis;
	if (!(basevga_flags & BASEVGA_FLAG_ISEGA))
		temp = vga_rmis();
	me->stt_crt_icX = VGA_CRT_IC;
	if (!(temp & VGA_MIS_FCOLOR))
		me->stt_crt_icX = VGA_CRT_IM;

	/* Populate the video text page with the expected contents. */
	memcpyw(svga_ttyaccess_txt_vmem(me),
	        svga_ttyaccess_txt_dmem(me),
	        me->vta_scan * me->vta_resy);
}

INTERN NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL svga_ttyaccess_v_setcell_txt)(struct vidttyaccess *__restrict self,
                                            struct ansitty *__restrict tty,
                                            uintptr_t address, char32_t ch) {
	u16 word;
	struct svga_ttyaccess_txt *me;
	me   = vidttyaccess_assvga_txt(self);
	word = svga_ttyaccess_makecell_txt(ch, tty);
	svga_ttyaccess_txt_dmem(me)[address] = word;
	if likely(me->vta_flags & VIDTTYACCESS_F_ACTIVE)
		svga_ttyaccess_txt_vmem(me)[address] = word;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_hidecursor_txt)(struct vidttyaccess *__restrict self) {
	struct svga_ttyaccess_txt *me;
	me = vidttyaccess_assvga_txt(self);
	if (!(me->vta_flags & _SVGA_TTYACCESS_F_HWCUROFF)) {
		uint8_t temp;
		temp = baseega_registers.vr_mode.vm_crt_cursor_start;
		if (!(basevga_flags & BASEVGA_FLAG_ISEGA))
			temp = vga_rcrt(me->stt_crt_icX, VGA_CRTC_CURSOR_START);
		temp |= VGA_CRA_FCURSOR_DISABLE;
		vga_wcrt(me->stt_crt_icX, VGA_CRTC_CURSOR_START, temp);
		baseega_registers.vr_mode.vm_crt_cursor_start = temp;
		me->vta_flags |= _SVGA_TTYACCESS_F_HWCUROFF;
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_showcursor_txt)(struct vidttyaccess *__restrict self) {
	struct svga_ttyaccess_txt *me;
	uint16_t address;
	me = vidttyaccess_assvga_txt(self);

	/* Write the intended cursor position into hardware. */
	address = me->vta_cursor.vtc_cellx +
	          me->vta_cursor.vtc_celly *
	          me->vta_scan;
	vga_wcrt(me->stt_crt_icX, VGA_CRTC_CURSOR_HI, (uint8_t)(address >> 8));
	vga_wcrt(me->stt_crt_icX, VGA_CRTC_CURSOR_LO, (uint8_t)(address));

	/* Show the cursor if it was hidden before. */
	if (me->vta_flags & _SVGA_TTYACCESS_F_HWCUROFF) {
		uint8_t temp;
		temp = baseega_registers.vr_mode.vm_crt_cursor_start;
		if (!(basevga_flags & BASEVGA_FLAG_ISEGA))
			temp = vga_rcrt(me->stt_crt_icX, VGA_CRTC_CURSOR_START);
		temp &= ~VGA_CRA_FCURSOR_DISABLE;
		vga_wcrt(me->stt_crt_icX, VGA_CRTC_CURSOR_START, temp);
		baseega_registers.vr_mode.vm_crt_cursor_start = temp;
		me->vta_flags &= ~_SVGA_TTYACCESS_F_HWCUROFF;
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_copycell_txt_nooverscan)(struct vidttyaccess *__restrict self,
                                                        uintptr_t to_cellid, uintptr_t from_cellid,
                                                        size_t num_cells) {
	u16 *dst, *src;
	struct svga_ttyaccess_txt *me;
	me  = vidttyaccess_assvga_txt(self);
	src = svga_ttyaccess_txt_dmem(me) + from_cellid;
	dst = svga_ttyaccess_txt_dmem(me) + to_cellid;
	src = memmovew(dst, src, num_cells); /* Modify display buffer */
	if (me->vta_flags & VIDTTYACCESS_F_ACTIVE) {
		dst = svga_ttyaccess_txt_vmem(me) + to_cellid;
		memcpyw(dst, src, num_cells); /* Copy to video memory */
	}
}

PRIVATE NOBLOCK NONNULL((1)) uint16_t
NOTHROW(FCALL svga_ttyaccess_getcell_txt_without_overscan)(struct svga_ttyaccess_txt *__restrict self,
                                                           uintptr_t screen_index) {
	size_t delta = self->vta_scan - self->vta_resx;
	screen_index += (screen_index / self->vta_resx) * delta;
	return svga_ttyaccess_txt_dmem(self)[screen_index];
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_setcell_txt_without_overscan)(struct svga_ttyaccess_txt *__restrict self,
                                                           uintptr_t screen_index, uint16_t val) {
	size_t delta = self->vta_scan - self->vta_resx;
	screen_index += (screen_index / self->vta_resx) * delta;
	svga_ttyaccess_txt_dmem(self)[screen_index] = val;
	if (self->vta_flags & VIDTTYACCESS_F_ACTIVE)
		svga_ttyaccess_txt_vmem(self)[screen_index] = val;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_copycell_txt_overscan)(struct vidttyaccess *__restrict self,
                                                      uintptr_t to_cellid, uintptr_t from_cellid,
                                                      size_t num_cells) {
	struct svga_ttyaccess_txt *me;
	me = vidttyaccess_assvga_txt(self);
	if (from_cellid < to_cellid) {
		while (num_cells--) {
			u16 word;
			word = svga_ttyaccess_getcell_txt_without_overscan(me, from_cellid);
			svga_ttyaccess_setcell_txt_without_overscan(me, to_cellid, word);
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
			word = svga_ttyaccess_getcell_txt_without_overscan(me, from_cellid);
			svga_ttyaccess_setcell_txt_without_overscan(me, to_cellid, word);
		}
	}
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL svga_ttyaccess_v_fillcells_txt)(struct vidttyaccess *__restrict self,
                                              struct ansitty *__restrict tty,
                                              uintptr_t start, char32_t ch, size_t num_cells) {
	u16 word;
	struct svga_ttyaccess_txt *me;
	me   = vidttyaccess_assvga_txt(self);
	word = svga_ttyaccess_makecell_txt(ch, tty);
	memsetw(&svga_ttyaccess_txt_dmem(me)[start], word, num_cells);
	if (me->vta_flags & VIDTTYACCESS_F_ACTIVE)
		memsetw(&svga_ttyaccess_txt_vmem(me)[start], word, num_cells);
}

PRIVATE NOBLOCK NONNULL((1, 3)) void
NOTHROW(FCALL svga_ttyaccess_v_getcelldata_txt)(struct vidttyaccess *__restrict self,
                                                uintptr_t address, byte_t buf[]) {
	struct svga_ttyaccess_txt *me;
	me = vidttyaccess_assvga_txt(self);
	UNALIGNED_SET16((u16 *)buf, svga_ttyaccess_txt_dmem(me)[address]);
}

PRIVATE NOBLOCK NONNULL((1, 3)) void
NOTHROW(FCALL svga_ttyaccess_v_setcelldata_txt)(struct vidttyaccess *__restrict self,
                                                uintptr_t address, byte_t const buf[]) {
	uint16_t word = UNALIGNED_GET16((u16 const *)buf);
	struct svga_ttyaccess_txt *me;
	me = vidttyaccess_assvga_txt(self);
	svga_ttyaccess_txt_dmem(me)[address] = word;
	if (me->vta_flags & VIDTTYACCESS_F_ACTIVE)
		svga_ttyaccess_txt_vmem(me)[address] = word;
}



/* Initialize `self->sta_vmem' as the relevant physical memory mapping. */
PRIVATE NONNULL((1, 2)) void FCALL
svga_ttyaccess_initvmem(struct svga_ttyaccess *__restrict self,
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
		svga_ttyaccess_initvmem(result, mode);
	} EXCEPT {
		kfree(result);
		RETHROW();
	}
	result->vta_resx        = mode->smi_resx;
	result->vta_resy        = mode->smi_resy;
	result->vta_scan        = mode->smi_scanline / 2;
	result->vta_cellsize    = 2;
	result->vta_activate    = &svga_ttyaccess_v_activate_txt;
	result->vta_setcell     = &svga_ttyaccess_v_setcell_txt;
	result->vta_hidecursor  = &svga_ttyaccess_v_hidecursor_txt;
	result->vta_showcursor  = &svga_ttyaccess_v_showcursor_txt;
	result->vta_copycell    = &svga_ttyaccess_v_copycell_txt_nooverscan;
	result->vta_fillcells   = &svga_ttyaccess_v_fillcells_txt;
	result->vta_getcelldata = &svga_ttyaccess_v_getcelldata_txt;
	result->vta_setcelldata = &svga_ttyaccess_v_setcelldata_txt;
	if (result->vta_scan > result->vta_resx)
		result->vta_copycell = &svga_ttyaccess_v_copycell_txt_overscan;
	result->vta_scroll_ystart = 0;
	result->vta_scroll_yend   = result->vta_resy;
	_vidttyaccess_update_scrl(result);

	/* Fill in the saved display state. */
	memsetw(svga_ttyaccess_txt_dmem(result),
	        ' ' | (ANSITTY_CL_DEFAULT << 8),
	        result->vta_scan * result->vta_resy);
	return result;
}



/************************************************************************/
/* Graphics mode TTY                                                    */
/************************************************************************/

/* Redraw graphics cells
 * NOTE: This functions may only be called when `VIDTTYACCESS_F_ACTIVE' is set. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_makettyaccess_redraw_cells_gfx)(struct svga_ttyaccess_gfx *__restrict self,
                                                   uintptr_t start, size_t num_cells) {
	uintptr_t i;
	for (i = 0; i < num_cells; ++i)
		(*self->stx_redraw_cell)(self, start + i);

	/* Check if we need to redraw the cursor. */
	if (self->vta_flags & _SVGA_TTYACCESS_F_SWCURON) {
		uintptr_t cursor_addr;
		cursor_addr = self->stx_swcur.vtc_cellx +
		              self->stx_swcur.vtc_celly *
		              self->vta_resx;
		if (cursor_addr >= start && cursor_addr < start + num_cells)
			(*self->stx_redraw_cursor)(self);
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_activate_gfx)(struct vidttyaccess *__restrict self) {
	/* Redraw the entire screen after reactivation. */
	struct svga_ttyaccess_gfx *me = vidttyaccess_assvga_gfx(self);
	svga_makettyaccess_redraw_cells_gfx(me, 0, me->vta_resx * me->vta_resy);
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL svga_ttyaccess_v_setcell_gfx)(struct vidttyaccess *__restrict self,
                                            struct ansitty *__restrict tty,
                                            uintptr_t address, char32_t ch) {
	struct svga_ttyaccess_gfx *me = vidttyaccess_assvga_gfx(self);
	byte_t const *pattern;
	pattern = basevga_defaultfont[basevga_defaultfont_encode(ch)];
	memcpy(me->stx_display[address].sgc_lines, pattern, 16);
	me->stx_display[address].sgc_color = tty->at_color;

	/* Don't touch display memory when not active! */
	if unlikely(!(me->vta_flags & VIDTTYACCESS_F_ACTIVE))
		return;
	(*me->stx_redraw_cell)(me, address);

	/* Check if we need to redraw the cursor. */
	if (me->vta_flags & _SVGA_TTYACCESS_F_SWCURON) {
		uintptr_t cursor_addr;
		cursor_addr = me->stx_swcur.vtc_cellx +
		              me->stx_swcur.vtc_celly *
		              me->vta_resx;
		if (cursor_addr == address)
			(*me->stx_redraw_cursor)(me);
	}
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL svga_ttyaccess_v_fillcells_gfx)(struct vidttyaccess *__restrict self,
                                              struct ansitty *__restrict tty,
                                              uintptr_t start, char32_t ch, size_t num_cells) {
	struct svga_ttyaccess_gfx *me = vidttyaccess_assvga_gfx(self);
	struct svga_gfxcell *src, *dst;
	byte_t const *pattern;
	size_t count;
	if unlikely(!num_cells)
		return;
	/* Properly fill in the first cell. */
	pattern = basevga_defaultfont[basevga_defaultfont_encode(ch)];
	src     = &me->stx_display[start];
	memcpy(src->sgc_lines, pattern, 16);
	src->sgc_color = tty->at_color;
	count          = num_cells - 1;
	if unlikely(!count) {
		/* Don't touch display memory when not active! */
		if unlikely(!(me->vta_flags & VIDTTYACCESS_F_ACTIVE))
			return;
		(*me->stx_redraw_cell)(me, start);

		/* Check if we need to redraw the cursor. */
		if (me->vta_flags & _SVGA_TTYACCESS_F_SWCURON) {
			uintptr_t cursor_addr;
			cursor_addr = me->stx_swcur.vtc_cellx +
			              me->stx_swcur.vtc_celly *
			              me->vta_resx;
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
	if likely(me->vta_flags & VIDTTYACCESS_F_ACTIVE)
		svga_makettyaccess_redraw_cells_gfx(me, start, num_cells);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_copycell_gfx)(struct vidttyaccess *__restrict self,
                                             uintptr_t to_cellid, uintptr_t from_cellid,
                                             size_t num_cells) {
	struct svga_ttyaccess_gfx *me = vidttyaccess_assvga_gfx(self);
	struct svga_gfxcell *dst, *src;
	src = me->stx_display + from_cellid;
	dst = me->stx_display + to_cellid;
	memmove(dst, src, num_cells, sizeof(struct svga_gfxcell));
	if likely(me->vta_flags & VIDTTYACCESS_F_ACTIVE)
		svga_makettyaccess_redraw_cells_gfx(me, to_cellid, num_cells);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_showcursor_gfx)(struct vidttyaccess *__restrict self) {
	struct svga_ttyaccess_gfx *me = vidttyaccess_assvga_gfx(self);

	/* Redraw the cursor's old cell to hide it. */
	if (me->vta_flags & _SVGA_TTYACCESS_F_SWCURON) {
		(*me->stx_redraw_cell)(me,
		                       me->stx_swcur.vtc_cellx +
		                       me->stx_swcur.vtc_celly *
		                       me->vta_resx);
	}

	/* Remember the new software cursor position. */
	me->stx_swcur.vtc_word = me->vta_cursor.vtc_word;
	me->vta_flags |= _SVGA_TTYACCESS_F_SWCURON;

	/* Draw a cursor at the new position. */
	(*me->stx_redraw_cursor)(me);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_hidecursor_gfx)(struct vidttyaccess *__restrict self) {
	struct svga_ttyaccess_gfx *me = vidttyaccess_assvga_gfx(self);
	if (me->vta_flags & _SVGA_TTYACCESS_F_SWCURON) {
		/* Redraw cell to override the cursor.
		 * Technically, we'd only need to redraw the area actually occupied
		 * by  the cursor, but this is keeping  it a little more simple! :) */
		(*me->stx_redraw_cell)(me,
		                       me->stx_swcur.vtc_cellx +
		                       me->stx_swcur.vtc_celly *
		                       me->vta_resx);
		me->vta_flags &= ~_SVGA_TTYACCESS_F_SWCURON;
	}
}

PRIVATE NOBLOCK NONNULL((1, 3)) void
NOTHROW(FCALL svga_ttyaccess_v_getcelldata_gfx)(struct vidttyaccess *__restrict self,
                                                uintptr_t address, byte_t buf[]) {
	struct svga_ttyaccess_gfx *me;
	me = vidttyaccess_assvga_gfx(self);
	memcpy(buf, &me->stx_display[address], sizeof(struct svga_gfxcell));
}

PRIVATE NOBLOCK NONNULL((1, 3)) void
NOTHROW(FCALL svga_ttyaccess_v_setcelldata_gfx)(struct vidttyaccess *__restrict self,
                                                uintptr_t address, byte_t const buf[]) {
	struct svga_ttyaccess_gfx *me;
	me = vidttyaccess_assvga_gfx(self);
	memcpy(&me->stx_display[address], buf, sizeof(struct svga_gfxcell));
	if (me->vta_flags & VIDTTYACCESS_F_ACTIVE)
		(*me->stx_redraw_cell)(me, address);
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
		svga_ttyaccess_initvmem(result, mode);
	} EXCEPT {
		kfree(result);
		RETHROW();
	}

	/* Configure dimensions. */
	result->vta_resy          = mode->smi_resy / 16;
	result->vta_resx          = mode->smi_resx / 9;
	result->vta_scan          = result->vta_resx;
	result->stx_scanline      = mode->smi_scanline;
	result->stx_cellscan      = 16 * mode->smi_scanline;
	result->vta_scroll_ystart = 0;
	result->vta_scroll_yend   = result->vta_resy;
	_vidttyaccess_update_scrl(result);

	/* Configure operators. */
	result->vta_setcell     = &svga_ttyaccess_v_setcell_gfx;
	result->vta_showcursor  = &svga_ttyaccess_v_showcursor_gfx;
	result->vta_hidecursor  = &svga_ttyaccess_v_hidecursor_gfx;
	result->vta_copycell    = &svga_ttyaccess_v_copycell_gfx;
	result->vta_fillcells   = &svga_ttyaccess_v_fillcells_gfx;
	result->vta_activate    = &svga_ttyaccess_v_activate_gfx;
	result->vta_cellsize    = sizeof(struct svga_gfxcell);
	result->vta_getcelldata = &svga_ttyaccess_v_getcelldata_gfx;
	result->vta_setcelldata = &svga_ttyaccess_v_setcelldata_gfx;

	/* BPP-specific operators. */
	switch (mode->smi_bits_per_pixel) {
#ifndef __INTELLISENSE__
#define SETOPS(bpp)                                                                    \
	{                                                                                  \
		INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL PP_CAT2(svga_ttyaccess_v_redraw_cell_gfx, bpp))(struct svga_ttyaccess_gfx *__restrict self, uintptr_t address); \
		INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL PP_CAT2(svga_ttyaccess_v_redraw_cursor_gfx, bpp))(struct svga_ttyaccess_gfx *__restrict self); \
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
#define sixbit2eight(x) ((((x) + 1) << 2) - 1)
			dcl = ((sixbit2eight(col.vpc_r) >> (8 - mode->smi_rbits)) << mode->smi_rshift) |
			      ((sixbit2eight(col.vpc_g) >> (8 - mode->smi_gbits)) << mode->smi_gshift) |
			      ((sixbit2eight(col.vpc_b) >> (8 - mode->smi_bbits)) << mode->smi_bshift);
#undef sixbit2eight
			result->stx_colors[i] = dcl;
		}
	}

	/* Use a white cursor by default. */
	result->stx_ccolor = result->stx_colors[ANSITTY_CL_WHITE];
	result->stx_swcur.vtc_word = 0;

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

	/* Fill in missing standard fields. */
	result->vta_refcnt  = 1;
	atomic_lock_init(&result->vta_lock);
	result->vta_flags           = VIDTTYACCESS_F_NORMAL;
	result->vta_cursor.vtc_word = 0;
	result->vta_cellw           = 9;
	result->vta_cellh           = 16;
	result->vta_destroy         = &svga_ttyaccess_destroy;
	result->sta_mode            = mode;
	return result;
}

DECL_END

#endif /* !GUARD_MODSVGA_TTY_C */
