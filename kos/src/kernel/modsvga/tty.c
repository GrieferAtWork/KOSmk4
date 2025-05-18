/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
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
#include <hybrid/overflow.h>
#include <hybrid/unaligned.h>

#include <hw/video/vga.h>
#include <kos/except.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

#include <libsvgadrv/chipset.h>
#include <libsvgadrv/util/vgaio.h>

/**/
#include "svga.h"


/************************************************************************/
/* SVGA ANSI TTY Implementation                                         */
/************************************************************************/

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset(p, c, n) memset(p, c, n)
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(p, c, n) (void)0
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




PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((2)) uint16_t
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

PRIVATE NOBLOCK ATTR_PURE NONNULL((1)) uint16_t
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
	UNALIGNED_SET16(buf, svga_ttyaccess_txt_dmem(me)[address]);
}

PRIVATE NOBLOCK NONNULL((1, 3)) void
NOTHROW(FCALL svga_ttyaccess_v_setcelldata_txt)(struct vidttyaccess *__restrict self,
                                                uintptr_t address, byte_t const buf[]) {
	uint16_t word = UNALIGNED_GET16(buf);
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
	physaddr_t mapaddr;

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
	                            MNODE_F_NOMERGE | MNODE_F_STATICPART;
	self->sta_vmem.mn_part    = NULL; /* Reserved node. */
	self->sta_vmem.mn_fspath  = NULL;
	self->sta_vmem.mn_fsname  = NULL;
	self->sta_vmem.mn_mman    = &mman_kernel;
	self->sta_vmem.mn_module  = NULL;
	DBG_memset(&self->sta_vmem.mn_partoff, 0xcc, sizeof(self->sta_vmem.mn_partoff));
	DBG_memset(&self->sta_vmem.mn_link, 0xcc, sizeof(self->sta_vmem.mn_link));
	LIST_ENTRY_UNBOUND_INIT(&self->sta_vmem.mn_writable);
	mman_mappings_insert_and_verify(&mman_kernel, &self->sta_vmem);
	mman_lock_endwrite(&mman_kernel);

	/* Bind video memory to our custom buffer mapping. */
	mapaddr = (physaddr_t)mode->smi_lfb;
	if (!(mode->smi_flags & SVGA_MODEINFO_F_LFB))
		mapaddr = (physaddr_t)0xA0000;
	pagedir_map(mapbase, vmemsize, mapaddr,
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
	                                                  dispsz, GFP_LOCKED | GFP_PREFLT);

	/* Initialize common fields. */
	TRY {
		svga_ttyaccess_initvmem(result, mode);
	} EXCEPT {
		kfree(result);
		RETHROW();
	}
	result->vta_resx           = mode->smi_resx;
	result->vta_resy           = mode->smi_resy;
	result->vta_scan           = mode->smi_scanline / 2;
	result->vta_cellsize       = 2;
	result->vta_activate       = &svga_ttyaccess_v_activate_txt;
	result->vta_setcell        = &svga_ttyaccess_v_setcell_txt;
	result->vta_hidecursor     = &svga_ttyaccess_v_hidecursor_txt;
	result->vta_showcursor     = &svga_ttyaccess_v_showcursor_txt;
	result->vta_copycell       = &svga_ttyaccess_v_copycell_txt_nooverscan;
	result->vta_fillcells      = &svga_ttyaccess_v_fillcells_txt;
	result->vta_getcelldata    = &svga_ttyaccess_v_getcelldata_txt;
	result->vta_setcelldata    = &svga_ttyaccess_v_setcelldata_txt;
	result->vta_setcells_ascii = &vidttyaccess_v_setcells_ascii;
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
	svga_ttyaccess_gfx_hw_async_waitfor(self);
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

LOCAL ATTR_RETNONNULL WUNUSED NOBLOCK NONNULL((1)) byte_t const *
NOTHROW(FCALL svga_ttyaccess_gfx_font_getglyph)(struct svga_ttyaccess_gfx *__restrict self,
                                                char32_t ch) {
	(void)self;
	/* TODO: Support for more than 256 characters (user-space should be able to
	 *       provide its own, custom font that should we should be able to then
	 *       use here) */
	return basevga_defaultfont[basevga_defaultfont_encode(ch)];
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_activate_gfx)(struct vidttyaccess *__restrict self) {
	/* Redraw the entire screen after reactivation. */
	struct svga_ttyrect rect;
	struct svga_ttyaccess_gfx *me = vidttyaccess_assvga_gfx(self);
	svga_makettyaccess_redraw_cells_gfx(me, 0, me->vta_resx * me->vta_resy);

	/* Perform HW update */
	rect.sttr_x = 0;
	rect.sttr_y = 0;
	rect.sttr_w = me->vta_resx;
	rect.sttr_h = me->vta_resy;
	(*me->stx_hw_updaterect)(me, &rect);
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL svga_ttyaccess_v_setcell_gfx_impl)(struct svga_ttyaccess_gfx *__restrict me,
                                                 struct ansitty *__restrict tty,
                                                 uintptr_t address, char32_t ch) {
	byte_t const *pattern;
	pattern = svga_ttyaccess_gfx_font_getglyph(me, ch);
	memcpy(me->stx_display[address].sgc_lines, pattern, 16);
	me->stx_display[address].sgc_color = tty->at_color;

	/* Don't touch display memory when not active! */
	if unlikely(!(me->vta_flags & VIDTTYACCESS_F_ACTIVE))
		return;
	svga_ttyaccess_gfx_hw_async_waitfor(me);
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
NOTHROW(FCALL svga_ttyaccess_v_setcell_gfx)(struct vidttyaccess *__restrict self,
                                            struct ansitty *__restrict tty,
                                            uintptr_t address, char32_t ch) {
	struct svga_ttyaccess_gfx *me = vidttyaccess_assvga_gfx(self);
	svga_ttyaccess_v_setcell_gfx_impl(me, tty, address, ch);
	(*me->stx_hw_updatecell)(me, address);
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL svga_ttyaccess_v_setcells_ascii_gfx)(struct vidttyaccess *__restrict self,
                                                   struct ansitty *__restrict tty, uintptr_t address,
                                                   char const *ascii_string, size_t num_cells) {
	size_t i;
	struct svga_ttyaccess_gfx *me = vidttyaccess_assvga_gfx(self);
	for (i = 0; i < num_cells; ++i) {
		char32_t ch = (char32_t)ascii_string[i];
		svga_ttyaccess_v_setcell_gfx_impl(me, tty, address + i, ch);
	}
	(*me->stx_hw_updateline)(me, address, num_cells);
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
	pattern = svga_ttyaccess_gfx_font_getglyph(me, ch);
	src     = &me->stx_display[start];
	memcpy(src->sgc_lines, pattern, 16);
	src->sgc_color = tty->at_color;
	count          = num_cells - 1;
	if unlikely(!count) {
		/* Don't touch display memory when not active! */
		if unlikely(!(me->vta_flags & VIDTTYACCESS_F_ACTIVE))
			return;
		svga_ttyaccess_gfx_hw_async_waitfor(me);
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

		/* Perform HW update */
		(*me->stx_hw_updatecell)(me, start);
		return;
	}

	/* Copy template into all additional cells. */
	dst = src + 1;
	do {
		dst = (struct svga_gfxcell *)mempcpy(dst, src, sizeof(struct svga_gfxcell));
	} while (--count);

	/* Don't touch display memory when not active! */
	if likely(me->vta_flags & VIDTTYACCESS_F_ACTIVE) {
		/* In certain where all pixels of "src" are identical (e.g. when ch='  '),
		 * we can use hardware acceleration (e.g. SVGA's SVGA_CMD_RECT_FILL) to do
		 * the fill for us. */
#ifdef SVGA_HAVE_HW_ASYNC_FILLRECT
		if (me->stx_chipset->sc_ops.sco_hw_async_fillrect &&
		    num_cells > 32) { /* Random threshold so we don't do this for small fills */
			/* Rect-fill for ' ' and '█' */
			uint8_t line0 = src->sgc_lines[0];
			uintptr_t end;
			uintptr_half_t src_x1;
			uintptr_half_t src_y1;
			uintptr_half_t src_x2;
			uintptr_half_t src_y2;
			uint8_t color_index;
			uint32_t color;
			struct svga_rect rect;
			if (line0 == 0x00 || line0 == 0xff) {
				unsigned int i;
				for (i = 1; i < COMPILER_LENOF(src->sgc_lines); ++i) {
					if (src->sgc_lines[i] != line0)
						goto do_normal_fill;
				}
			}
			end    = start + num_cells;
			src_x1 = start % self->vta_resx;
			src_y1 = start / self->vta_resx;
			src_x2 = end % self->vta_resx;
			src_y2 = end / self->vta_resx;
			if (src_x2 == 0) {
				src_x2 = self->vta_resx;
				--src_y2;
			}
			color_index = line0 ? ((src->sgc_color & 0x0f))
				                : ((src->sgc_color & 0xf0) >> 4);
			color = me->stx_colors[color_index];
#define FILL_RECT(p_rect, color)                                                                  \
			do {                                                                                  \
				(*me->stx_chipset->sc_ops.sco_hw_async_fillrect)(me->stx_chipset, p_rect, color); \
				if (me->stx_chipset->sc_ops.sco_updaterect)                                       \
					(*me->stx_chipset->sc_ops.sco_updaterect)(me->stx_chipset, p_rect);           \
			}	__WHILE0

			if (src_x1 > 0) {
				rect.svr_x = src_x1 * 9;
				rect.svr_y = src_y1 * 16;
				rect.svr_w = (me->vta_resx - src_x1) * 9;
				rect.svr_h = 16;
				FILL_RECT(&rect, color);
				src_x1 = 0;
				++src_y1;
			}
			if (src_x2 < self->vta_resx) {
				rect.svr_x = 0;
				rect.svr_y = src_y2 * 16;
				rect.svr_w = src_x2 * 9;
				rect.svr_h = 16;
				FILL_RECT(&rect, color);
				src_x2 = self->vta_resx;
				--src_y2;
			}
			if (src_y1 <= src_y2) {
				rect.svr_x = src_x1 * 9;
				rect.svr_y = src_y1 * 16;
				rect.svr_w = (src_x2 - src_x1) * 9;
				rect.svr_h = ((src_y2 - src_y1) + 1) * 16;
				FILL_RECT(&rect, color);
			}
			return;
#undef FILL_RECT
		}
do_normal_fill:
#endif /* SVGA_HAVE_HW_ASYNC_FILLRECT */
		svga_makettyaccess_redraw_cells_gfx(me, start, num_cells);
		(*me->stx_hw_updateline)(me, start, num_cells);
	}
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
	if likely(me->vta_flags & VIDTTYACCESS_F_ACTIVE) {
		/* In  the general case (where this operator is used for scrolling),
		 * we can use hardware acceleration (e.g. SVGA's SVGA_CMD_RECT_COPY)
		 * to do the move for us! */
#ifdef SVGA_HAVE_HW_ASYNC_COPYRECT
		if (me->stx_chipset->sc_ops.sco_hw_async_copyrect) {
			uintptr_t end_from_cellid = from_cellid + num_cells;
			uintptr_t end_to_cellid   = to_cellid + num_cells;
			uintptr_half_t src_x1 = from_cellid % self->vta_resx;
			uintptr_half_t src_y1 = from_cellid / self->vta_resx;
			uintptr_half_t src_x2 = end_from_cellid % self->vta_resx;
			uintptr_half_t src_y2 = end_from_cellid / self->vta_resx;
			uintptr_half_t dst_x1 = to_cellid % self->vta_resx;
			uintptr_half_t dst_y1 = to_cellid / self->vta_resx;
			uintptr_half_t dst_x2 = end_to_cellid % self->vta_resx;
			uintptr_half_t dst_y2 = end_to_cellid / self->vta_resx;
			if (src_x2 == 0) {
				src_x2 = self->vta_resx;
				--src_y2;
			}
			if (dst_x2 == 0) {
				dst_x2 = self->vta_resx;
				--dst_y2;
			}
			if (((src_x1 == 0 && src_x2 == self->vta_resx) || (src_y1 == src_y2)) &&
			    ((dst_x1 == 0 && dst_x2 == self->vta_resx) || (dst_y1 == dst_y2))) {
				/* Able to do a rect-based copy. */
				struct svga_copyrect rect;
				bool must_hide_cusor;

				/* Because we render our TTY cursor on the regular background layer,
				 * we have to clear it from the display if it is being rendered, and
				 * is part of the source region that is being copied */
				must_hide_cusor = (me->vta_flags & _SVGA_TTYACCESS_F_SWCURON) != 0;
				if (must_hide_cusor) {
					uintptr_t cursor_addr;
					cursor_addr = me->stx_swcur.vtc_cellx +
					              me->stx_swcur.vtc_celly *
					              me->vta_resx;
					if (cursor_addr >= from_cellid && cursor_addr < end_from_cellid) {
						svga_ttyaccess_gfx_hw_async_waitfor(me);
						(*me->stx_redraw_cell)(me, cursor_addr);
					} else {
						must_hide_cusor = false;
					}
				}

				/* Calculate rects to-be copied on-screen. */
				rect.svcr_sx = src_x1 * 9;
				rect.svcr_sy = src_y1 * 16;
				rect.svcr_dx = dst_x1 * 9;
				rect.svcr_dy = dst_y1 * 16;
				rect.svcr_w  = (src_x2 - src_x1) * 9;
				rect.svcr_h  = ((src_y2 - src_y1) + 1) * 16;

				(*me->stx_chipset->sc_ops.sco_hw_async_copyrect)(me->stx_chipset, &rect);
				if (me->stx_chipset->sc_ops.sco_updaterect)
					(*me->stx_chipset->sc_ops.sco_updaterect)(me->stx_chipset, &rect.svcr_dest);
				if (must_hide_cusor) {
					svga_ttyaccess_gfx_hw_async_waitfor(me); /* TODO: Not needed if `svga_ttyaccess_v_redraw_cursor_hwgfx' is used */
					(*me->stx_redraw_cursor)(me);
				}
				return;
			}
		}
#endif /* SVGA_HAVE_HW_ASYNC_COPYRECT */

		svga_makettyaccess_redraw_cells_gfx(me, to_cellid, num_cells);
		(*me->stx_hw_updateline)(me, to_cellid, num_cells);
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_showcursor_gfx)(struct vidttyaccess *__restrict self) {
	struct svga_ttyaccess_gfx *me = vidttyaccess_assvga_gfx(self);
	uintptr_t naddress;
	svga_ttyaccess_gfx_hw_async_waitfor(me);

	/* Redraw the cursor's old cell to hide it. */
	if (me->vta_flags & _SVGA_TTYACCESS_F_SWCURON) {
		uintptr_t oaddress;
		oaddress = me->stx_swcur.vtc_cellx +
		           me->stx_swcur.vtc_celly *
		           me->vta_resx;
		(*me->stx_redraw_cell)(me, oaddress);
		(*me->stx_hw_updatecell)(me, oaddress);
	}

	/* Remember the new software cursor position. */
	me->stx_swcur.vtc_word = me->vta_cursor.vtc_word;
	me->vta_flags |= _SVGA_TTYACCESS_F_SWCURON;

	/* Draw a cursor at the new position. */
	(*me->stx_redraw_cursor)(me);

	/* Perform HW update */
	naddress = me->stx_swcur.vtc_cellx +
	           me->stx_swcur.vtc_celly *
	           me->vta_resx;
	(*me->stx_hw_updatecell)(me, naddress);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_hidecursor_gfx)(struct vidttyaccess *__restrict self) {
	struct svga_ttyaccess_gfx *me = vidttyaccess_assvga_gfx(self);
	if (me->vta_flags & _SVGA_TTYACCESS_F_SWCURON) {
		uintptr_t address;
		/* Redraw cell to override the cursor.
		 * Technically, we'd only need to redraw the area actually occupied
		 * by  the cursor, but this is keeping  it a little more simple! :) */
		address = me->stx_swcur.vtc_cellx +
		          me->stx_swcur.vtc_celly *
		          me->vta_resx;
		svga_ttyaccess_gfx_hw_async_waitfor(me);
		(*me->stx_redraw_cell)(me, address);
		(*me->stx_hw_updatecell)(me, address);
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
	if (me->vta_flags & VIDTTYACCESS_F_ACTIVE) {
		svga_ttyaccess_gfx_hw_async_waitfor(me);
		(*me->stx_redraw_cell)(me, address);
		(*me->stx_hw_updatecell)(me, address);
	}
}


PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL svga_ttyaccess_v_hw_updaterect_gfx_9_16)(struct svga_ttyaccess_gfx *__restrict self,
                                                       struct svga_ttyrect const *__restrict rect) {
	struct svga_rect hw_rect;
	hw_rect.svr_x = rect->sttr_x * 9;
	hw_rect.svr_y = rect->sttr_y * 16;
	hw_rect.svr_w = rect->sttr_w * 9;
	hw_rect.svr_h = rect->sttr_h * 16;
	(*self->stx_chipset->sc_ops.sco_updaterect)(self->stx_chipset, &hw_rect);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_hw_updateline_gfx_9_16)(struct svga_ttyaccess_gfx *__restrict self,
                                                       uintptr_t address, size_t num_cells) {
	uintptr_t end;
	uintptr_half_t start_x, end_x;
	uintptr_half_t start_y, end_y;
	struct svga_ttyrect rect;
	start_x = address % self->vta_scan;
	start_y = address / self->vta_scan;
	end     = address + num_cells;
	end_x   = end % self->vta_scan;
	end_y   = end / self->vta_scan;
	if (end_x == 0) {
		--end_y;
		end_x = self->vta_resx;
	}
	if (start_y == end_y) {
		/* Simple case: everything is in 1 row. */
		rect.sttr_x = start_x;
		rect.sttr_y = start_y;
		rect.sttr_w = end_x - start_x;
		rect.sttr_h = 1;
		(*self->stx_hw_updaterect)(self, &rect);
	} else if (start_x == 0 && end_x == self->vta_resx) {
		/* Simple case: updating whole lines from start-to-end */
		rect.sttr_x = 0;
		rect.sttr_y  = start_y;
		rect.sttr_w = end_x;
		rect.sttr_h = (end_y - start_y) + 1;
		(*self->stx_hw_updaterect)(self, &rect);
	} else {
		/* Complicated case:
		 * ......................XXXXXXXX
		 * XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
		 * XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
		 * XXXXXX........................
		 */
		if (start_x != 0) {
			rect.sttr_x = start_x;
			rect.sttr_y = start_y;
			rect.sttr_w = self->vta_resx - start_x;
			rect.sttr_h = 1;
			(*self->stx_hw_updaterect)(self, &rect);
			start_x = 0;
			++start_y;
		}

		if (end_x != self->vta_resx) {
			rect.sttr_x = 0;
			rect.sttr_y = end_y;
			rect.sttr_w = end_x;
			rect.sttr_h = 1;
			(*self->stx_hw_updaterect)(self, &rect);
			--end_y;
			end_x = self->vta_resx;
		}

		if (start_y <= end_y) {
			rect.sttr_x = 0;
			rect.sttr_y = start_y;
			rect.sttr_w = self->vta_resx;
			rect.sttr_h = (end_y - start_y) + 1;
			(*self->stx_hw_updaterect)(self, &rect);
		}
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_hw_updatecell_gfx_9_16)(struct svga_ttyaccess_gfx *__restrict self,
                                                       uintptr_t address) {
	struct svga_rect hw_rect;
	hw_rect.svr_x = address % self->vta_scan;
	hw_rect.svr_y = address / self->vta_scan;
	hw_rect.svr_x *= 9;
	hw_rect.svr_y *= 16;
	hw_rect.svr_w = 9;
	hw_rect.svr_h = 16;
	(*self->stx_chipset->sc_ops.sco_updaterect)(self->stx_chipset, &hw_rect);
}

INTERN NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL svga_ttyaccess_v_hw_updaterect_noop)(struct svga_ttyaccess_gfx *__restrict self,
                                                   struct svga_ttyrect const *__restrict rect) {
	(void)self;
	(void)rect;
	COMPILER_IMPURE();
}

INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_hw_updateline_noop)(struct svga_ttyaccess_gfx *__restrict self,
                                                   uintptr_t address, size_t num_cells) {
	(void)self;
	(void)address;
	(void)num_cells;
	COMPILER_IMPURE();
}

INTDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_hw_updatecell_noop)(struct svga_ttyaccess_gfx *__restrict self,
                                                   uintptr_t address)
		ASMNAME("svga_ttyaccess_v_hw_updaterect_noop");




PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) REF struct svga_ttyaccess_gfx *FCALL
svga_makettyaccess_gfx(struct svgadev *__restrict self,
                       struct svga_modeinfo const *__restrict mode) {
	REF struct svga_ttyaccess_gfx *result;
	size_t dispsz;
	uintptr_half_t cells_x = mode->smi_resx / 9;
	uintptr_half_t cells_y = mode->smi_resy / 16;

	/* Allocate the object. */
	dispsz = cells_x * cells_y * sizeof(struct svga_gfxcell);
	result = (REF struct svga_ttyaccess_gfx *)kmalloc(offsetof(struct svga_ttyaccess_gfx, stx_display) +
	                                                  dispsz, GFP_LOCKED | GFP_PREFLT);

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
	result->vta_setcell        = &svga_ttyaccess_v_setcell_gfx;
	result->vta_showcursor     = &svga_ttyaccess_v_showcursor_gfx;
	result->vta_hidecursor     = &svga_ttyaccess_v_hidecursor_gfx;
	result->vta_copycell       = &svga_ttyaccess_v_copycell_gfx;
	result->vta_fillcells      = &svga_ttyaccess_v_fillcells_gfx;
	result->vta_activate       = &svga_ttyaccess_v_activate_gfx;
	result->vta_cellsize       = sizeof(struct svga_gfxcell);
	result->vta_getcelldata    = &svga_ttyaccess_v_getcelldata_gfx;
	result->vta_setcelldata    = &svga_ttyaccess_v_setcelldata_gfx;
	result->vta_setcells_ascii = &svga_ttyaccess_v_setcells_ascii_gfx;
	result->stx_chipset        = &self->svd_chipset;

	/* Fill in HW update operators (if required by the chipset) */
	if (self->svd_chipset.sc_ops.sco_updaterect) {
		result->stx_hw_updatecell = &svga_ttyaccess_v_hw_updatecell_gfx_9_16;
		result->stx_hw_updateline = &svga_ttyaccess_v_hw_updateline_gfx_9_16;
		result->stx_hw_updaterect = &svga_ttyaccess_v_hw_updaterect_gfx_9_16;
	} else {
		result->stx_hw_updatecell = &svga_ttyaccess_v_hw_updatecell_noop;
		result->stx_hw_updateline = &svga_ttyaccess_v_hw_updateline_noop;
		result->stx_hw_updaterect = &svga_ttyaccess_v_hw_updaterect_noop;
	}

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
	case 1:
		if (mode->smi_flags & SVGA_MODEINFO_F_PLANAR) {
			SETOPS(1_p);
		} else {
			/* This right here is monochrome! */
			SETOPS(1);
		}
		break;

	case 2:
		/* 2-bpp non-planar  wouldn't make  any sense,  so
		 * we assume that `SVGA_MODEINFO_F_PLANAR' is set. */
		SETOPS(2_p);
		break;

//TODO:	case 3 ... 4:
//TODO:		if (!(mode->smi_flags & SVGA_MODEINFO_F_LFB))
//TODO:			goto notsup; /* TODO: Auto-window selection via custom #PF handling */
//TODO:		SETOPS(4);
//TODO:		break;

	case 5 ... 8:
		if (!(mode->smi_flags & SVGA_MODEINFO_F_LFB))
			goto notsup; /* TODO: Auto-window selection via custom #PF handling */
		SETOPS(8);
		break;

	case 9 ... 16:
		if (!(mode->smi_flags & SVGA_MODEINFO_F_LFB))
			goto notsup; /* TODO: Auto-window selection via custom #PF handling */
		SETOPS(16);
		break;

	case 17 ... 24:
		if (!(mode->smi_flags & SVGA_MODEINFO_F_LFB))
			goto notsup; /* TODO: Auto-window selection via custom #PF handling */
		SETOPS(24);
		break;

	case 25 ... 32:
		SETOPS(32);
		break;
#undef SETOPS
#endif /* !__INTELLISENSE__ */

	default:
		/* Unsupported # of bits-per-pixel. */
notsup:
		destroy(result);
		THROW(E_NOT_IMPLEMENTED_UNSUPPORTED);
		break;
	}

	/* If available, use hardware-acceleration to draw the cursor overlay. */
#ifdef SVGA_HAVE_HW_ASYNC_FILLRECT
//	if (self->svd_chipset.sc_ops.sco_hw_async_fillrect)
//		result->stx_redraw_cursor = &svga_ttyaccess_v_redraw_cursor_hwgfx; /* TODO */
#endif /* SVGA_HAVE_HW_ASYNC_FILLRECT */

	/* Precalculate palette colors. */
	if (mode->smi_flags & SVGA_MODEINFO_F_PAL) {
		unsigned int i;
		for (i = 0; i < 16; ++i)
			result->stx_colors[i] = i;
	} else {
		unsigned int i;
		for (i = 0; i < 16; ++i) {
			struct svga_palette_color col;
			uint32_t dcl; /* DirectCoLor */
			col = basevga_defaultpal[i];
			dcl = ((col.spc_r >> (8 - mode->smi_rbits)) << mode->smi_rshift) |
			      ((col.spc_g >> (8 - mode->smi_gbits)) << mode->smi_gshift) |
			      ((col.spc_b >> (8 - mode->smi_bbits)) << mode->smi_bshift);
			result->stx_colors[i] = dcl;
		}
	}

	/* Use a white cursor by default. */
	result->stx_ccolor = result->stx_colors[ANSITTY_CL_WHITE];
	result->stx_swcur.vtc_word = 0;

	/* Fill in the saved display state. */
	bzero(result->stx_display, dispsz);

	/* Set default color for all cells. */
	{
		size_t i;
		for (i = 0; i < cells_x * cells_y; ++i)
			result->stx_display[i].sgc_color = ANSITTY_CL_DEFAULT;
	}

	return result;
}


/* Create  a  TTY  access  object  for  the  given   `mode'.
 * The caller must ensure that `return' dies *BEFORE* `self' */
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
	result->vta_refcnt = 1;
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
