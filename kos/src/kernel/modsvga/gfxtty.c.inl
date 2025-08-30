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
#ifdef __INTELLISENSE__
#define BPP 4
//#define PLANAR
#include "gfxtty.c"
#endif /* __INTELLISENSE__ */

#ifndef BPP
#error "Must #define BPP"
#endif /* !BPP */

#include <hybrid/align.h>
#include <hybrid/unaligned.h>

#include <string.h>

#include <libsvgadrv/util/vgaio.h>

DECL_BEGIN

#if BPP >= 5
#define BYTES_PER_PIXEL CEILDIV(BPP, 8)
#endif /* BPP >= 5 */

#ifndef CELLSIZE_X
#define CELLSIZE_X 9
#define CELLSIZE_Y 16
#endif /* !CELLSIZE_X */

#ifndef CURSOR_Y_OFFSET
#define CURSOR_X_OFFSET 0          /* X-offset (in pixels) for cursor */
#define CURSOR_Y_OFFSET 13         /* Y-offset (in pixels) for cursor */
#define CURSOR_HEIGHT   2          /* Height (in pixels) of cursor */
#define CURSOR_WIDTH    CELLSIZE_X /* Width (in pixels) of cursor */
#endif /* !CURSOR_Y_OFFSET */

#if (CURSOR_Y_OFFSET + CURSOR_HEIGHT) > CELLSIZE_Y
#error "Invalid configuration"
#endif /* ... */

#if (CURSOR_X_OFFSET + CURSOR_WIDTH) > CELLSIZE_X
#error "Invalid configuration"
#endif /* ... */

/* GCC does a bunch of warnings:
 * >> assuming signed overflow does not occur when determining that expression is always non-negative
 * ...  relating  to  unsigned   math  done  with  "uintptr_half_t".   This  is  because  that   math
 * actually   happens  after  integer  promotion,  at  which   point  division  and  so  on  actually
 * becomes  signed  again.  --  Maybe   figure  out  a  way  to   keep  division  unsigned,  so   gcc
 * won't even try to use signed math? */
__pragma_GCC_diagnostic_push_ignored(Wstrict_overflow)

#ifdef BYTES_PER_PIXEL

/* GCC: """warning : 'bgfg' is used uninitialized [-Wuninitialized]"""
 * ME:  Nope! It definitly gets initialized. - See:
 *      >> bgfg[0] = self->stx_colors[(cell->sgc_color & 0xf0) >> 4];
 *      >> bgfg[1] = self->stx_colors[(cell->sgc_color & 0x0f)]; */
__pragma_GCC_diagnostic_push_ignored(Wuninitialized)

INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL PP_CAT2(svga_ttyaccess_v_redraw_cell_gfx, BPP))(struct svga_ttyaccess_gfx *__restrict self,
                                                              uintptr_t address) {
	struct svga_gfxcell const *cell;
	uintptr_half_t cellx, celly;
	uintptr_half_t y;
	byte_t *dst;
	uint32_t bgfg[2];
	cellx = address % self->vta_scan;
	celly = address / self->vta_scan;
	dst  = (byte_t *)mnode_getaddr(&self->sta_vmem);
	dst += celly * self->stx_cellscan;
	dst += cellx * CELLSIZE_X * BYTES_PER_PIXEL;

	/* Load colors. */
	cell    = &self->stx_display[address];
	bgfg[0] = self->stx_colors[(cell->sgc_color & 0xf0) >> 4];
	bgfg[1] = self->stx_colors[(cell->sgc_color & 0x0f)];

	/* Go through scanlines. */
#if BYTES_PER_PIXEL == 1
#define SETPIXEL(addr, color) (*(addr) = (byte_t)(color))
#elif BYTES_PER_PIXEL == 2
#define SETPIXEL(addr, color) UNALIGNED_SET16(addr, (uint16_t)(color))
#elif BYTES_PER_PIXEL == 3
#define ADVPIXEL(addr, color) (byte_t *)mempcpy((addr), &(color), 3)
#elif BYTES_PER_PIXEL == 4
#define SETPIXEL(addr, color) UNALIGNED_SET32(addr, (uint32_t)(color))
#else /* BYTES_PER_PIXEL == ... */
#error "Unsupported BYTES_PER_PIXEL"
#endif /* BYTES_PER_PIXEL != ... */
	for (y = 0; y < CELLSIZE_Y; ++y) {
		uint8_t mask;
		byte_t *iter;
		uintptr_half_t x;
		mask = cell->sgc_lines[y];
		x    = 8;
		iter = dst;
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
		dst += self->stx_scanline;
	}
#undef ADVPIXEL
#undef SETPIXEL
}

__pragma_GCC_diagnostic_pop_ignored(Wuninitialized)


INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL PP_CAT2(svga_ttyaccess_v_redraw_cursor_gfx, BPP))(struct svga_ttyaccess_gfx *__restrict self) {
	byte_t *dst;
	unsigned int y;

	/* Figure out where the cursor goes. */
	dst = (byte_t *)mnode_getaddr(&self->sta_vmem);
	dst += self->stx_swcur.vtc_celly * self->stx_cellscan;           /* Go to top-left of current line */
	dst += self->stx_swcur.vtc_cellx * CELLSIZE_X * BYTES_PER_PIXEL; /* Go to top-left of current cell */
	dst += CURSOR_Y_OFFSET * self->stx_scanline;                     /* Go to left of top-most cursor block */
	dst += CURSOR_X_OFFSET * BYTES_PER_PIXEL;                        /* To to start of cursor block. */
	for (y = 0; y < CURSOR_HEIGHT; ++y) {
#if BYTES_PER_PIXEL == 4
		memsetl(dst, (uint32_t)self->stx_ccolor, CURSOR_WIDTH);
#elif BYTES_PER_PIXEL == 2
		memsetw(dst, (uint16_t)self->stx_ccolor, CURSOR_WIDTH);
#elif BYTES_PER_PIXEL == 1
		memset(dst, (uint8_t)self->stx_ccolor, CURSOR_WIDTH);
#elif BYTES_PER_PIXEL == 3
		unsigned int x;
		byte_t *iter = dst;
		for (x = 0; x < CURSOR_WIDTH; ++x)
			iter = (byte_t *)mempcpy(iter, &self->stx_ccolor, 3);
#else /* BYTES_PER_PIXEL == ... */
#error "Unsupported BYTES_PER_PIXEL"
#endif /* BYTES_PER_PIXEL != ... */
		dst += self->stx_scanline;
	}
}

#elif BPP == 4

#ifdef PLANAR
#error "BPP == 4 only exists in non-PLANAR mode"
#endif /* !PLANAR */


/* Very weird pixel-format. You'd think this was
 * >> Byte:  B1......B2......B3......B4......B5......B6......B7......B8......
 * >> Pixel: AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPP
 * >> Bit:   3210321032103210321032103210321032103210321032103210321032103210
 *
 * But it's actually like this:
 * >> Byte:  B1......B2......B3......B4......B5......B6......B7......B8......
 * >> Pixel: ABCDEFGHABCDEFGHABCDEFGHABCDEFGHIJKLMNOPIJKLMNOPIJKLMNOPIJKLMNOP
 * >> Bit:   1111111122222222333333334444444411111111222222223333333344444444
 *
 * iow: the  4 bits of  every pixel are  written across 4 consecutive
 *      bytes, and on-top of that, they are written in reverse order!
 *
 * This format is actually closer to 1_p (planar 1bpp), except that the planes
 * have all been stamped down into a linear buffer, with planes switch  places
 * with each other every 4 bytes. */
#define SETPIXEL(line, x, v)                               \
	do {                                                   \
		byte_t *p   = line + (((x) >> 3) << 2);            \
		byte_t mask = (byte_t)1 << (7 - ((x) & 7));        \
		p[0] = (p[0] & ~mask) | (mask * (((v) >> 0) & 1)); \
		p[1] = (p[1] & ~mask) | (mask * (((v) >> 1) & 1)); \
		p[2] = (p[2] & ~mask) | (mask * (((v) >> 2) & 1)); \
		p[3] = (p[3] & ~mask) | (mask * (((v) >> 3) & 1)); \
	}	__WHILE0
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_redraw_cell_gfx4)(struct svga_ttyaccess_gfx *__restrict self,
                                                 uintptr_t address) {
#if 1
	struct svga_gfxcell const *cell;
	uintptr_half_t cellx, celly;
	uintptr_half_t y, xoff;
	byte_t *dst;
	byte_t *base;
	uint8_t plane;

	cellx = address % self->vta_scan;
	celly = address / self->vta_scan;
	base  = (byte_t *)mnode_getaddr(&self->sta_vmem);
	base += (celly * self->stx_cellscan);
	base += ((cellx * CELLSIZE_X) / 8) * 4;
	xoff = (uintptr_half_t)(cellx * CELLSIZE_X) % 8;

	/* Load colors. */
	cell = &self->stx_display[address];

	/* Go through scanlines. */
	for (plane = 0; plane < 4; ++plane) {
		dst = base + plane;
		for (y = 0; y < CELLSIZE_Y; ++y) {
			uint8_t mask;
			union {
				uint8_t b[2];
				uint16_t w;
			} vmem;

			mask = cell->sgc_lines[y];

			/* Apply colors
			 *
			 * Repeat for each of the 8 bits in `mask':
			 * ```
			 *     mask   fg   bg    result
			 *        0    0    0    0
			 *        0    0    1    1
			 *        0    1    0    0
			 *        0    1    1    1
			 *        1    0    0    0
			 *        1    0    1    0
			 *        1    1    0    1
			 *        1    1    1    1
			 * ```
			 * Solution: `result = (fg & mask) | (bg & ~mask);'
			 *
			 * Verbose code:
			 * >> uint8_t bgfgbits[2], i, bit;
			 * >> bgfgbits[0] = (cell->sgc_color >> (4 + plane)) & 1;
			 * >> bgfgbits[1] = (cell->sgc_color >> plane) & 1;
			 * >> for (i = 0; i < 8; ++i) {
			 * >>     bit = (mask >> i) & 1;
			 * >>     mask &= ~(1 << i);
			 * >>     mask |= bgfgbits[bit] << i;
			 * >> }
			 */
#if 1
			{
				uint8_t bg, fg;
				bg   = ((cell->sgc_color >> (4 + plane)) & 1) * 0xff;
				fg   = ((cell->sgc_color >> plane) & 1) * 0xff;
				mask = (fg & mask) | (bg & ~mask);
			}
#else
			{
				uint8_t bgfgbits[2], i, bit;
				bgfgbits[0] = (cell->sgc_color >> (4 + plane)) & 1;
				bgfgbits[1] = (cell->sgc_color >> plane) & 1;
				for (i = 0; i < 8; ++i) {
					bit = (mask >> i) & 1;
					mask &= ~(1 << i);
					mask |= bgfgbits[bit] << i;
				}
			}
#endif
			switch (xoff) {

			case 0:
				/* 76543210|0_______ */
				vmem.b[0] = mask;
				vmem.b[1] = dst[4];
				vmem.b[1] &= 0x7f;
				vmem.b[1] |= (mask & 1) << 7;
				break;

#define BITMASK(n) ((1 << (n)) - 1)
#define OVERRIDE_BITS(xoff)                                        \
				vmem.b[0] = dst[0];                                \
				vmem.b[1] = dst[4];                                \
				vmem.b[0] &= ~BITMASK(8 - xoff);                   \
				vmem.b[0] |= mask >> xoff;                         \
				vmem.b[1] &= BITMASK(8 - (xoff + 1));              \
				vmem.b[1] |= (mask & BITMASK(xoff)) << (8 - xoff); \
				vmem.b[1] |= (mask & 1) << (8 - (xoff + 1));
			case 1: OVERRIDE_BITS(1); break; /* _7654321|00______ */
			case 2: OVERRIDE_BITS(2); break; /* __765432|100_____ */
			case 3: OVERRIDE_BITS(3); break; /* ___76543|2100____ */
			case 4: OVERRIDE_BITS(4); break; /* ____7654|32100___ */
			case 5: OVERRIDE_BITS(5); break; /* _____765|432100__ */
			case 6: OVERRIDE_BITS(6); break; /* ______76|5432100_ */
#undef OVERRIDE_BITS

			case 7:
				/* _______7|65432100 */
				vmem.b[0] = dst[0];
				vmem.b[1] = (mask << 1) | (mask & 1);
				vmem.b[0] &= 0xfe;
				vmem.b[0] |= (mask & 0x80) >> 7;
				break;

			default: __builtin_unreachable();
			}
			dst[0] = vmem.b[0];
			dst[4] = vmem.b[1];
			dst += self->stx_scanline;
		}
	}
#else
	byte_t *line;
	uintptr_half_t cellx, celly;
	uintptr_half_t linex, y;
	uint8_t colors[2];
	struct svga_gfxcell const *cell;
	cellx = address % self->vta_scan;
	celly = address / self->vta_scan;
	line  = (byte_t *)mnode_getaddr(&self->sta_vmem);
	line += (celly * self->stx_cellscan);
	linex = (cellx * CELLSIZE_X);
	cell = &self->stx_display[address];
	colors[0] = self->stx_colors[(cell->sgc_color >> 4) & 0xf];
	colors[1] = self->stx_colors[(cell->sgc_color) & 0xf];

	for (y = 0; y < CELLSIZE_Y; ++y) {
		uint8_t v, mask = cell->sgc_lines[y];
		uintptr_half_t x;
		for (x = 0; x < 8; ++x) {
			v = colors[(mask >> (7 - x)) & 1];
			SETPIXEL(line, linex + x, v);
		}
		v = colors[mask & 1];
		SETPIXEL(line, linex + x, v);
		line += self->stx_scanline;
	}
#endif
}

INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_redraw_cursor_gfx4)(struct svga_ttyaccess_gfx *__restrict self) {
#if 1
	uintptr_half_t y, xoff;
	byte_t *dst;
	byte_t *base;
	uint8_t plane;

	/* Figure out where the cursor goes. */
	base = (byte_t *)mnode_getaddr(&self->sta_vmem);
	base += self->stx_swcur.vtc_celly * self->stx_cellscan; /* Go to top-left of current line */
	base += CURSOR_Y_OFFSET * self->stx_scanline;           /* Go to left of top-most cursor block */
	base += (((self->stx_swcur.vtc_cellx * CELLSIZE_X) + CURSOR_X_OFFSET) / 8) * 4;
	xoff = (uintptr_half_t)((self->stx_swcur.vtc_cellx * CELLSIZE_X) + CURSOR_X_OFFSET) % 8;

	for (plane = 0; plane < 4; ++plane) {
		dst = base + plane;
		for (y = 0; y < CURSOR_HEIGHT; ++y) {
#define CSHAPE 0x1ff /* Cursor horizontal shape (1: white bit; 0: black bit) */
			union {
				uint8_t b[2];
				uint16_t w;
			} vmem;
			switch (xoff) {

			case 0:
				/* 87654321|0_______ */
				vmem.b[0] = (CSHAPE >> 1);
				vmem.b[1] = dst[4];
				vmem.b[1] &= 0x7f;
				vmem.b[1] |= (CSHAPE & 1) << 7;
				break;

#define BITMASK(n) ((1 << (n)) - 1)
#define OVERRIDE_BITS(xoff)                                                 \
				vmem.b[0] = dst[0];                                         \
				vmem.b[1] = dst[4];                                         \
				vmem.b[0] &= ~BITMASK(8 - xoff);                            \
				vmem.b[0] |= (CSHAPE >> 1) >> xoff;                         \
				vmem.b[1] &= BITMASK(8 - (xoff + 1));                       \
				vmem.b[1] |= ((CSHAPE >> 1) & BITMASK(xoff)) << (8 - xoff); \
				vmem.b[1] |= (CSHAPE & 1) << (8 - (xoff + 1));
			case 1: OVERRIDE_BITS(1); break; /* _8765432|10______ */
			case 2: OVERRIDE_BITS(2); break; /* __876543|210_____ */
			case 3: OVERRIDE_BITS(3); break; /* ___87654|3210____ */
			case 4: OVERRIDE_BITS(4); break; /* ____8765|43210___ */
			case 5: OVERRIDE_BITS(5); break; /* _____876|543210__ */
			case 6: OVERRIDE_BITS(6); break; /* ______87|6543210_ */
#undef OVERRIDE_BITS

			case 7:
				/* _______8|76543210 */
				vmem.b[0] = dst[0];
				vmem.b[1] = CSHAPE & 0xff;
				vmem.b[0] &= 0xfe;
				vmem.b[0] |= (CSHAPE & 0x100) >> 8;
				break;

			default: __builtin_unreachable();
			}
			dst[0] = vmem.b[0];
			dst[4] = vmem.b[1];
			dst += self->stx_scanline;
		}
#undef CSHAPE
	}
#else
	byte_t *line;
	uintptr_half_t curx, y, x;

	/* Figure out where the cursor goes. */
	line = (byte_t *)mnode_getaddr(&self->sta_vmem);
	line += self->stx_swcur.vtc_celly * self->stx_cellscan;
	line += CURSOR_Y_OFFSET * self->stx_scanline;
	curx = (self->stx_swcur.vtc_cellx * CELLSIZE_X) + CURSOR_X_OFFSET;
	for (y = 0; y < CURSOR_HEIGHT; ++y) {
		for (x = 0; x < CURSOR_WIDTH; ++x)
			SETPIXEL(line, curx + x, self->stx_ccolor);
		line += self->stx_scanline;
	}
#endif
}

#undef SETPIXEL

#elif BPP == 2

#ifndef PLANAR
#error "BPP == 2 only exists in PLANAR mode"
#endif /* !PLANAR */


/* 2-bits-per-pixel mode is super-weird:
 * - In actuality, every pixel is 8 bits
 * - But the address of a pixel is:
 *   >> PLANE = X % 4
 *   >> OFFST = X / 4 + Y * scanline
 */

/* Functions to set pixel colors in planar mode. */
#define SETCELL_P0_X0 { dst[0] = CELLPIXEL(0); dst[1] = CELLPIXEL(4); dst[2] = CELLPIXEL(7); /* 8 */ }
#define SETCELL_P1_X0 { dst[0] = CELLPIXEL(1); dst[1] = CELLPIXEL(5); }
#define SETCELL_P2_X0 { dst[0] = CELLPIXEL(2); dst[1] = CELLPIXEL(6); }
#define SETCELL_P3_X0 { dst[0] = CELLPIXEL(3); dst[1] = CELLPIXEL(7); }

#define SETCELL_P1_X1 { dst[0] = CELLPIXEL(0); dst[1] = CELLPIXEL(4); dst[2] = CELLPIXEL(7); /* 8 */ }
#define SETCELL_P2_X1 { dst[0] = CELLPIXEL(1); dst[1] = CELLPIXEL(5); }
#define SETCELL_P3_X1 { dst[0] = CELLPIXEL(2); dst[1] = CELLPIXEL(6); }
#define SETCELL_P0_X1 { dst[1] = CELLPIXEL(3); dst[2] = CELLPIXEL(7); }

#define SETCELL_P2_X2 { dst[0] = CELLPIXEL(0); dst[1] = CELLPIXEL(4); dst[2] = CELLPIXEL(7); /* 8 */ }
#define SETCELL_P3_X2 { dst[0] = CELLPIXEL(1); dst[1] = CELLPIXEL(5); }
#define SETCELL_P0_X2 { dst[1] = CELLPIXEL(2); dst[2] = CELLPIXEL(6); }
#define SETCELL_P1_X2 { dst[1] = CELLPIXEL(3); dst[2] = CELLPIXEL(7); }

#define SETCELL_P3_X3 { dst[0] = CELLPIXEL(0); dst[1] = CELLPIXEL(4); dst[2] = CELLPIXEL(7); /* 8 */ }
#define SETCELL_P0_X3 { dst[1] = CELLPIXEL(1); dst[2] = CELLPIXEL(5); }
#define SETCELL_P1_X3 { dst[1] = CELLPIXEL(2); dst[2] = CELLPIXEL(6); }
#define SETCELL_P2_X3 { dst[1] = CELLPIXEL(3); dst[2] = CELLPIXEL(7); }

#define SETCELL_P0_Xi(i)                     \
	switch (i) {                             \
	case 0: SETCELL_P0_X0; break;            \
	case 1: SETCELL_P0_X1; break;            \
	case 2: SETCELL_P0_X2; break;            \
	case 3: SETCELL_P0_X3; break;            \
	default: __builtin_unreachable(); break; \
	}
#define SETCELL_P1_Xi(i)                     \
	switch (i) {                             \
	case 0: SETCELL_P1_X0; break;            \
	case 1: SETCELL_P1_X1; break;            \
	case 2: SETCELL_P1_X2; break;            \
	case 3: SETCELL_P1_X3; break;            \
	default: __builtin_unreachable(); break; \
	}
#define SETCELL_P2_Xi(i)                     \
	switch (i) {                             \
	case 0: SETCELL_P2_X0; break;            \
	case 1: SETCELL_P2_X1; break;            \
	case 2: SETCELL_P2_X2; break;            \
	case 3: SETCELL_P2_X3; break;            \
	default: __builtin_unreachable(); break; \
	}
#define SETCELL_P3_Xi(i)                     \
	switch (i) {                             \
	case 0: SETCELL_P3_X0; break;            \
	case 1: SETCELL_P3_X1; break;            \
	case 2: SETCELL_P3_X2; break;            \
	case 3: SETCELL_P3_X3; break;            \
	default: __builtin_unreachable(); break; \
	}

INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_redraw_cell_gfx2_p)(struct svga_ttyaccess_gfx *__restrict self,
                                                   uintptr_t address) {
	struct svga_gfxcell const *cell;
	uintptr_half_t cellx, celly;
	uintptr_half_t y, xoff;
	byte_t *dst, *base;
	uint8_t colors[2];
	uint8_t saved_seq_plane_write;
	saved_seq_plane_write = vga_rseq(VGA_SEQ_PLANE_WRITE);

	cellx = address % self->vta_scan;
	celly = address / self->vta_scan;
	base  = (byte_t *)mnode_getaddr(&self->sta_vmem);
	base += (celly * self->stx_cellscan);
	base += (cellx * CELLSIZE_X) / 4;
	xoff = (uintptr_half_t)(cellx * CELLSIZE_X) % 4;

	/* Load colors. */
	cell = &self->stx_display[address];

	colors[0] = self->stx_colors[(cell->sgc_color >> 4) & 0xf];
	colors[1] = self->stx_colors[(cell->sgc_color) & 0xf];
#define CELLPIXEL(x) colors[(mask >> (7 - (x))) & 1]

	/* Write to plane 0. */
	vga_wseq(VGA_SEQ_PLANE_WRITE, (saved_seq_plane_write & ~VGA_SR02_FALL_PLANES) | VGA_SR02_FPLANE(0));
	for (dst = base, y = 0; y < CELLSIZE_Y; ++y) {
		uint8_t mask;
		mask = cell->sgc_lines[y];
		SETCELL_P0_Xi(xoff);
		dst += self->stx_scanline;
	}
	COMPILER_WRITE_BARRIER();

	/* Write to plane 1. */
	vga_wseq(VGA_SEQ_PLANE_WRITE, (saved_seq_plane_write & ~VGA_SR02_FALL_PLANES) | VGA_SR02_FPLANE(1));
	for (dst = base, y = 0; y < CELLSIZE_Y; ++y) {
		uint8_t mask;
		mask = cell->sgc_lines[y];
		SETCELL_P1_Xi(xoff);
		dst += self->stx_scanline;
	}
	COMPILER_WRITE_BARRIER();

	/* Write to plane 2. */
	vga_wseq(VGA_SEQ_PLANE_WRITE, (saved_seq_plane_write & ~VGA_SR02_FALL_PLANES) | VGA_SR02_FPLANE(2));
	for (dst = base, y = 0; y < CELLSIZE_Y; ++y) {
		uint8_t mask;
		mask = cell->sgc_lines[y];
		SETCELL_P2_Xi(xoff);
		dst += self->stx_scanline;
	}
	COMPILER_WRITE_BARRIER();

	/* Write to plane 3. */
	vga_wseq(VGA_SEQ_PLANE_WRITE, (saved_seq_plane_write & ~VGA_SR02_FALL_PLANES) | VGA_SR02_FPLANE(3));
	for (dst = base, y = 0; y < CELLSIZE_Y; ++y) {
		uint8_t mask;
		mask = cell->sgc_lines[y];
		SETCELL_P3_Xi(xoff);
		dst += self->stx_scanline;
	}
	COMPILER_WRITE_BARRIER();
#undef CELLPIXEL
}


#if CURSOR_WIDTH == 9
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_redraw_cursor_gfx2_p)(struct svga_ttyaccess_gfx *__restrict self) {
	uintptr_half_t xoff, y;
	byte_t *dst, *base;
	uint8_t color = (uint8_t)self->stx_ccolor;
	uint8_t saved_seq_plane_write;
	saved_seq_plane_write = vga_rseq(VGA_SEQ_PLANE_WRITE);

	/* Figure out where the cursor goes. */
	base = (byte_t *)mnode_getaddr(&self->sta_vmem);
	base += self->stx_swcur.vtc_celly * self->stx_cellscan; /* Go to top-left of current line */
	base += CURSOR_Y_OFFSET * self->stx_scanline;           /* Go to left of top-most cursor block */
	base += (uintptr_half_t)((self->stx_swcur.vtc_cellx * CELLSIZE_X) + CURSOR_X_OFFSET) / 4;
	xoff = (uintptr_half_t)((self->stx_swcur.vtc_cellx * CELLSIZE_X) + CURSOR_X_OFFSET) % 4;

#define CELLPIXEL(i) color
	vga_wseq(VGA_SEQ_PLANE_WRITE, (saved_seq_plane_write & ~VGA_SR02_FALL_PLANES) | VGA_SR02_FPLANE(0));
	for (dst = base, y = 0; y < CURSOR_HEIGHT; ++y) {
		SETCELL_P0_Xi(xoff);
		dst += self->stx_scanline;
	}
	COMPILER_WRITE_BARRIER();

	vga_wseq(VGA_SEQ_PLANE_WRITE, (saved_seq_plane_write & ~VGA_SR02_FALL_PLANES) | VGA_SR02_FPLANE(1));
	for (dst = base, y = 0; y < CURSOR_HEIGHT; ++y) {
		SETCELL_P1_Xi(xoff);
		dst += self->stx_scanline;
	}
	COMPILER_WRITE_BARRIER();

	vga_wseq(VGA_SEQ_PLANE_WRITE, (saved_seq_plane_write & ~VGA_SR02_FALL_PLANES) | VGA_SR02_FPLANE(2));
	for (dst = base, y = 0; y < CURSOR_HEIGHT; ++y) {
		SETCELL_P2_Xi(xoff);
		dst += self->stx_scanline;
	}
	COMPILER_WRITE_BARRIER();

	vga_wseq(VGA_SEQ_PLANE_WRITE, (saved_seq_plane_write & ~VGA_SR02_FALL_PLANES) | VGA_SR02_FPLANE(3));
	for (dst = base, y = 0; y < CURSOR_HEIGHT; ++y) {
		SETCELL_P3_Xi(xoff);
		dst += self->stx_scanline;
	}
	COMPILER_WRITE_BARRIER();
#undef CELLPIXEL
}
#else /* CURSOR_WIDTH == 9 */
#error "Unsupported `CURSOR_WIDTH'"
#endif /* CURSOR_WIDTH != 9 */

#elif BPP == 1

#ifdef PLANAR
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_redraw_cell_gfx1_p)(struct svga_ttyaccess_gfx *__restrict self,
                                                   uintptr_t address)
#else /* PLANAR */
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_redraw_cell_gfx1)(struct svga_ttyaccess_gfx *__restrict self,
                                                 uintptr_t address)
#endif /* !PLANAR */
{
	struct svga_gfxcell const *cell;
	uintptr_half_t cellx, celly;
	uintptr_half_t y, xoff;
	byte_t *dst;
#ifdef PLANAR
	byte_t *base;
	uint8_t plane;
	uint8_t saved_seq_plane_write;
	uint8_t saved_gfx_plane_read;
	saved_seq_plane_write = vga_rseq(VGA_SEQ_PLANE_WRITE);
	saved_gfx_plane_read  = vga_rgfx(VGA_GFX_PLANE_READ);
#endif /* PLANAR */

	cellx = address % self->vta_scan;
	celly = address / self->vta_scan;
	dst  = (byte_t *)mnode_getaddr(&self->sta_vmem);
	dst += (celly * self->stx_cellscan);
	dst += (cellx * CELLSIZE_X) / 8;
	xoff = (uintptr_half_t)(cellx * CELLSIZE_X) % 8;

	/* Load colors. */
	cell = &self->stx_display[address];

	/* Go through scanlines. */
#ifdef PLANAR
	base = dst;
	for (plane = 0; plane < 4; ++plane)
#endif /* PLANAR */
	{

		/* Select the appropriate plane. */
#ifdef PLANAR
		COMPILER_WRITE_BARRIER();
		vga_wseq(VGA_SEQ_PLANE_WRITE, (saved_seq_plane_write & ~VGA_SR02_FALL_PLANES) | VGA_SR02_FPLANE(plane));
		vga_wgfx(VGA_GFX_PLANE_READ, (saved_gfx_plane_read & ~VGA_GR04_FREADMAP) | VGA_GR04_READMAP(plane));
		COMPILER_WRITE_BARRIER();
#endif /* PLANAR */

		for (y = 0; y < CELLSIZE_Y; ++y) {
			uint8_t mask;
			union {
				uint8_t b[2];
				uint16_t w;
			} vmem;

			mask = cell->sgc_lines[y];

#ifdef PLANAR
			/* Apply colors
			 *
			 * Repeat for each of the 8 bits in `mask':
			 * ```
			 *     mask   fg   bg    result
			 *        0    0    0    0
			 *        0    0    1    1
			 *        0    1    0    0
			 *        0    1    1    1
			 *        1    0    0    0
			 *        1    0    1    0
			 *        1    1    0    1
			 *        1    1    1    1
			 * ```
			 * Solution: `result = (fg & mask) | (bg & ~mask);'
			 *
			 * Verbose code:
			 * >> uint8_t bgfgbits[2], i, bit;
			 * >> bgfgbits[0] = (cell->sgc_color >> (4 + plane)) & 1;
			 * >> bgfgbits[1] = (cell->sgc_color >> plane) & 1;
			 * >> for (i = 0; i < 8; ++i) {
			 * >>     bit = (mask >> i) & 1;
			 * >>     mask &= ~(1 << i);
			 * >>     mask |= bgfgbits[bit] << i;
			 * >> }
			 */
#if 1
			{
				uint8_t bg, fg;
				bg   = ((cell->sgc_color >> (4 + plane)) & 1) * 0xff;
				fg   = ((cell->sgc_color >> plane) & 1) * 0xff;
				mask = (fg & mask) | (bg & ~mask);
			}
#else
			{
				uint8_t bgfgbits[2], i, bit;
				bgfgbits[0] = (cell->sgc_color >> (4 + plane)) & 1;
				bgfgbits[1] = (cell->sgc_color >> plane) & 1;
				for (i = 0; i < 8; ++i) {
					bit = (mask >> i) & 1;
					mask &= ~(1 << i);
					mask |= bgfgbits[bit] << i;
				}
			}
#endif
#endif /* PLANAR */
			switch (xoff) {

			case 0:
				/* 76543210|0_______ */
				vmem.b[0] = mask;
				vmem.b[1] = dst[1];
				vmem.b[1] &= 0x7f;
				vmem.b[1] |= (mask & 1) << 7;
				break;

#define BITMASK(n) ((1 << (n)) - 1)
#define OVERRIDE_BITS(xoff)                                        \
				vmem.w = UNALIGNED_GET16(dst);                     \
				vmem.b[0] &= ~BITMASK(8 - xoff);                   \
				vmem.b[0] |= mask >> xoff;                         \
				vmem.b[1] &= BITMASK(8 - (xoff + 1));              \
				vmem.b[1] |= (mask & BITMASK(xoff)) << (8 - xoff); \
				vmem.b[1] |= (mask & 1) << (8 - (xoff + 1));
			case 1: OVERRIDE_BITS(1); break; /* _7654321|00______ */
			case 2: OVERRIDE_BITS(2); break; /* __765432|100_____ */
			case 3: OVERRIDE_BITS(3); break; /* ___76543|2100____ */
			case 4: OVERRIDE_BITS(4); break; /* ____7654|32100___ */
			case 5: OVERRIDE_BITS(5); break; /* _____765|432100__ */
			case 6: OVERRIDE_BITS(6); break; /* ______76|5432100_ */
#undef OVERRIDE_BITS

			case 7:
				/* _______7|65432100 */
				vmem.b[0] = dst[0];
				vmem.b[1] = (mask << 1) | (mask & 1);
				vmem.b[0] &= 0xfe;
				vmem.b[0] |= (mask & 0x80) >> 7;
				break;

			default: __builtin_unreachable();
			}
			UNALIGNED_SET16(dst, vmem.w);
			dst += self->stx_scanline;
		}

#ifdef PLANAR
		dst = base;
#endif /* PLANAR */
	}
}


#if CURSOR_WIDTH == 9
#ifdef PLANAR
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_redraw_cursor_gfx1_p)(struct svga_ttyaccess_gfx *__restrict self)
#else /* PLANAR */
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_v_redraw_cursor_gfx1)(struct svga_ttyaccess_gfx *__restrict self)
#endif /* !PLANAR */
{
	uintptr_half_t y, xoff;
	byte_t *dst;
#ifdef PLANAR
	byte_t *base;
	uint8_t plane;
	uint8_t saved_seq_plane_write;
	uint8_t saved_gfx_plane_read;
	saved_seq_plane_write = vga_rseq(VGA_SEQ_PLANE_WRITE);
	saved_gfx_plane_read  = vga_rgfx(VGA_GFX_PLANE_READ);
#endif /* PLANAR */

	/* Figure out where the cursor goes. */
	dst = (byte_t *)mnode_getaddr(&self->sta_vmem);
	dst += self->stx_swcur.vtc_celly * self->stx_cellscan; /* Go to top-left of current line */
	dst += CURSOR_Y_OFFSET * self->stx_scanline;           /* Go to left of top-most cursor block */
	dst += ((self->stx_swcur.vtc_cellx * CELLSIZE_X) + CURSOR_X_OFFSET) / 8;
	xoff = (uintptr_half_t)((self->stx_swcur.vtc_cellx * CELLSIZE_X) + CURSOR_X_OFFSET) % 8;

#ifdef PLANAR
	base = dst;
	for (plane = 0; plane < 4; ++plane)
#endif /* PLANAR */
	{

		/* Select the appropriate plane. */
#ifdef PLANAR
		COMPILER_WRITE_BARRIER();
		vga_wseq(VGA_SEQ_PLANE_WRITE, (saved_seq_plane_write & ~VGA_SR02_FALL_PLANES) | VGA_SR02_FPLANE(plane));
		vga_wgfx(VGA_GFX_PLANE_READ, (saved_gfx_plane_read & ~VGA_GR04_FREADMAP) | VGA_GR04_READMAP(plane));
		COMPILER_WRITE_BARRIER();
#endif /* PLANAR */

		for (y = 0; y < CURSOR_HEIGHT; ++y) {
#define CSHAPE 0x1ff /* Cursor horizontal shape (1: white bit; 0: black bit) */
			union {
				uint8_t b[2];
				uint16_t w;
			} vmem;
			switch (xoff) {

			case 0:
				/* 87654321|0_______ */
				vmem.b[0] = (CSHAPE >> 1);
				vmem.b[1] = dst[1];
				vmem.b[1] &= 0x7f;
				vmem.b[1] |= (CSHAPE & 1) << 7;
				break;

#define BITMASK(n) ((1 << (n)) - 1)
#define OVERRIDE_BITS(xoff)                                                 \
				vmem.w = UNALIGNED_GET16(dst);                              \
				vmem.b[0] &= ~BITMASK(8 - xoff);                            \
				vmem.b[0] |= (CSHAPE >> 1) >> xoff;                         \
				vmem.b[1] &= BITMASK(8 - (xoff + 1));                       \
				vmem.b[1] |= ((CSHAPE >> 1) & BITMASK(xoff)) << (8 - xoff); \
				vmem.b[1] |= (CSHAPE & 1) << (8 - (xoff + 1));
			case 1: OVERRIDE_BITS(1); break; /* _8765432|10______ */
			case 2: OVERRIDE_BITS(2); break; /* __876543|210_____ */
			case 3: OVERRIDE_BITS(3); break; /* ___87654|3210____ */
			case 4: OVERRIDE_BITS(4); break; /* ____8765|43210___ */
			case 5: OVERRIDE_BITS(5); break; /* _____876|543210__ */
			case 6: OVERRIDE_BITS(6); break; /* ______87|6543210_ */
#undef OVERRIDE_BITS

			case 7:
				/* _______8|76543210 */
				vmem.b[0] = dst[0];
				vmem.b[1] = CSHAPE & 0xff;
				vmem.b[0] &= 0xfe;
				vmem.b[0] |= (CSHAPE & 0x100) >> 8;
				break;

			default: __builtin_unreachable();
			}
			UNALIGNED_SET16(dst, vmem.w);
			dst += self->stx_scanline;
		}

#ifdef PLANAR
		dst = base;
#endif /* PLANAR */
#undef CSHAPE
	}
}
#else /* CURSOR_WIDTH == 9 */
#error "Unsupported `CURSOR_WIDTH'"
#endif /* CURSOR_WIDTH != 9 */
#else /* ... */
#error "Unsupported BPP"
#endif /* !... */

#undef BYTES_PER_PIXEL

__pragma_GCC_diagnostic_pop_ignored(Wstrict_overflow)

DECL_END

#undef PLANAR
#undef BPP
