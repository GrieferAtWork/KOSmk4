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
#ifdef __INTELLISENSE__
#define BPP 24
#include "svga-dcoltty.c"
#endif /* __INTELLISENSE__ */

#ifndef BPP
#error "Must #define BPP"
#endif /* !BPP */

#include <hybrid/align.h>
#include <hybrid/unaligned.h>

#include <string.h>

DECL_BEGIN

#if BPP >= 5
#define BYTES_PER_PIXEL CEILDIV(BPP, 8)
#endif /* BPP >= 5 */

#ifndef CELLSIZE_X
#define CELLSIZE_X 9
#define CELLSIZE_Y 16
#endif /* !CELLSIZE_X */

#ifdef BYTES_PER_PIXEL
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL PP_CAT2(svga_ttyaccess_v_redraw_cell_gfx, BPP))(struct svga_ttyaccess_gfx *__restrict self,
                                                              uintptr_t address) {
	struct svga_gfxcell const *cell;
	uintptr_half_t cellx, celly;
	uintptr_half_t y;
	byte_t *dest;
	uint32_t bgfg[2];
	cellx = address % self->sta_scan;
	celly = address / self->sta_scan;
	dest  = (byte_t *)mnode_getaddr(&self->sta_vmem);
	dest += celly * self->stx_cellscan;
	dest += cellx * CELLSIZE_X * BYTES_PER_PIXEL;

	/* Load colors. */
	cell    = &self->stx_display[address];
	bgfg[0] = self->stx_colors[(cell->sgc_color & 0xf0) >> 4];
	bgfg[1] = self->stx_colors[(cell->sgc_color & 0x0f)];

	/* Go through scanlines. */
#if BYTES_PER_PIXEL == 1
#define SETPIXEL(addr, color) (*(addr) = (byte_t)(color))
#elif BYTES_PER_PIXEL == 2
#define SETPIXEL(addr, color) UNALIGNED_SET16((uint16_t *)(addr), (uint16_t)(color))
#elif BYTES_PER_PIXEL == 3
#define ADVPIXEL(addr, color) (byte_t *)mempcpy((addr), &(color), 3)
#elif BYTES_PER_PIXEL == 4
#define SETPIXEL(addr, color) UNALIGNED_SET32((uint32_t *)(addr), (uint32_t)(color))
#else /* BYTES_PER_PIXEL == ... */
#error "Unsupported BYTES_PER_PIXEL"
#endif /* BYTES_PER_PIXEL != ... */
	for (y = 0; y < CELLSIZE_Y; ++y) {
		uint8_t mask;
		byte_t *iter;
		uintptr_half_t x;
		mask = cell->sgc_lines[y];
		x    = 8;
		iter = dest;
		do {
			--x;
#ifdef ADVPIXEL
			iter = ADVPIXEL(iter, bgfg[(mask >> x) & 1]);
#else /* ADVPIXEL */
			SETPIXEL(iter, bgfg[(mask >> x) & 1]);
			iter += BYTES_PER_PIXEL;
#endif /* !ADVPIXEL */
		} while (x);

		/* Repeat the last pixel. */
#ifdef ADVPIXEL
		ADVPIXEL(iter, bgfg[mask & 1]);
#else /* ADVPIXEL */
		SETPIXEL(iter, bgfg[mask & 1]); /* Repeat the last pixel. */
#endif /* !ADVPIXEL */
		dest += self->sta_mode->smi_scanline;
	}
#undef ADVPIXEL
#undef SETPIXEL
}


#ifndef CURSOR_Y_OFFSET
#define CURSOR_X_OFFSET 0          /* X-offset for cursor */
#define CURSOR_Y_OFFSET 13         /* Y-offset for cursor */
#define CURSOR_HEIGHT   2          /* Height (in pixels) of cursor */
#define CURSOR_WIDTH    CELLSIZE_X /* Width (in pixels) of cursor */
#endif /* !CURSOR_Y_OFFSET */

#if (CURSOR_Y_OFFSET + CURSOR_HEIGHT) > CELLSIZE_Y
#error "Invalid configuration"
#endif /* ... */

#if (CURSOR_X_OFFSET + CURSOR_WIDTH) > CELLSIZE_X
#error "Invalid configuration"
#endif /* ... */


INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL PP_CAT2(svga_ttyaccess_v_redraw_cursor_gfx, BPP))(struct svga_ttyaccess *__restrict self) {
	struct svga_ttyaccess_gfx *me;
	byte_t *dst;
	unsigned int y;
	me = (struct svga_ttyaccess_gfx *)self;

	/* Figure out where the cursor goes. */
	dst = (byte_t *)mnode_getaddr(&me->sta_vmem);
	dst += me->stx_swcur.stc_celly * me->stx_cellscan;             /* Go to top-left of current line */
	dst += me->stx_swcur.stc_cellx * CELLSIZE_X * BYTES_PER_PIXEL; /* Go to top-left of current cell */
	dst += CURSOR_Y_OFFSET * me->sta_mode->smi_scanline;           /* Go to left of top-most cursor block */
	dst += CURSOR_X_OFFSET * BYTES_PER_PIXEL;                      /* To to start of cursor block. */
	for (y = 0; y < CURSOR_HEIGHT; ++y) {
#if BYTES_PER_PIXEL == 4
		memsetl(dst, (uint32_t)me->stx_ccolor, CURSOR_WIDTH);
#elif BYTES_PER_PIXEL == 2
		memsetw(dst, (uint16_t)me->stx_ccolor, CURSOR_WIDTH);
#elif BYTES_PER_PIXEL == 1
		memset(dst, (uint8_t)me->stx_ccolor, CURSOR_WIDTH);
#elif BYTES_PER_PIXEL == 3
		unsigned int x;
		byte_t *iter = dst;
		for (x = 0; x < CURSOR_WIDTH; ++x)
			iter = (byte_t *)mempcpy(iter, &me->stx_ccolor, 3);
#else /* BYTES_PER_PIXEL == ... */
#error "Unsupported BYTES_PER_PIXEL"
#endif /* BYTES_PER_PIXEL != ... */
		dst += me->sta_mode->smi_scanline;
	}
}

#else /* BYTES_PER_PIXEL */
#error TODO
#endif /* !BYTES_PER_PIXEL */

#undef BYTES_PER_PIXEL

DECL_END

#undef BPP
