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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_OUTPUT_C
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_OUTPUT_C 1
#define DISABLE_BRANCH_PROFILING
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <debugger/hook.h>
#include <debugger/io.h>
#include <debugger/output.h>
#include <dev/video.h>
#include <kernel/mman/phys-access.h>
#include <kernel/mman/phys.h>

#include <hybrid/unaligned.h>

#include <hw/video/vga.h>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include <libsvgadrv/util/vgaio.h>

DECL_BEGIN

#undef VGATTY_MAP_B8000_IS_KERNELSPACE_BASE
#ifndef NO_PHYS_IDENTITY
#define HAVE_VGATTY_B8000
PRIVATE ATTR_DBGBSS uint32_t vgatty_b8000 = 0;
#define VGATTY_MAP_B8000 PHYS_TO_IDENTITY(vgatty_b8000)
#elif !defined(ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE)
#define VGATTY_MAP_B8000_IS_KERNELSPACE_BASE
#define VGATTY_MAP_B8000 ((byte_t *)KERNELSPACE_BASE)
#endif /* !NO_PHYS_IDENTITY */

/* Helpers for accessing text-mode video memory. */
#ifdef VGATTY_MAP_B8000
#define VGATTY_MAP_PEEK(index)                   (((u16 const *)VGATTY_MAP_B8000)[index])
#define VGATTY_MAP_POKE(index, word)             (((u16 *)VGATTY_MAP_B8000)[index] = (word))
#define VGATTY_MAP_COPYFROM(dst, off, num_bytes) memcpy(dst, VGATTY_MAP_B8000 + (off), num_bytes)
#define VGATTY_MAP_COPYTO(off, src, num_bytes)   memcpy(VGATTY_MAP_B8000 + (off), src, num_bytes)
#define VGATTY_MAP_COPYIN(doff, soff, num_bytes) memmove(VGATTY_MAP_B8000 + (doff), VGATTY_MAP_B8000 + (soff), num_bytes)
#else /* VGATTY_MAP_B8000 */
#define HAVE_VGATTY_B8000
PRIVATE ATTR_DBGBSS uint32_t vgatty_b8000 = 0;
#define VGATTY_MAP_PEEK(index)                   peekphysw((physaddr_t)vgatty_b8000 + 2 * (index))
#define VGATTY_MAP_POKE(index, word)             pokephysw((physaddr_t)vgatty_b8000 + 2 * (index), word)
#define VGATTY_MAP_COPYFROM(dst, off, num_bytes) copyfromphys(dst, (physaddr_t)vgatty_b8000 + (off), num_bytes)
#define VGATTY_MAP_COPYTO(off, src, num_bytes)   copytophys((physaddr_t)vgatty_b8000 + (off), src, num_bytes)
#define VGATTY_MAP_COPYIN(doff, soff, num_bytes) copyinphys((physaddr_t)vgatty_b8000 + (doff), (physaddr_t)vgatty_b8000 + (soff), num_bytes)
#endif /* !VGATTY_MAP_B8000 */

/* Either `VGA_CRT_IC' or `VGA_CRT_IM' */
PRIVATE ATTR_DBGBSS port_t vgatty_crt_icX;


/* We assume that the BIOS has loaded a cp437-compatible code page. */
PRIVATE ATTR_DBGRODATA byte_t const cp437_encode_a0_ff[] = {
	0xff,0xad,0x9b,0x9c,0x00,0x9d,0x00,0x15,0x00,0x00,0xa6,0xae,0xaa,0x00,0x00,0x00,
	0xf8,0xf1,0xfd,0x00,0x00,0xe6,0x14,0xfa,0x00,0x00,0xa7,0xaf,0xac,0xab,0x00,0xa8,
	0x00,0x00,0x00,0x00,0x8e,0x8f,0x92,0x80,0x00,0x90,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0xa5,0x00,0x00,0x00,0x00,0x99,0x00,0x00,0x00,0x00,0x00,0x9a,0x00,0x00,0xe1,
	0x85,0xa0,0x83,0x00,0x84,0x86,0x91,0x87,0x8a,0x82,0x88,0x89,0x8d,0xa1,0x8c,0x8b,
	0x00,0xa4,0x95,0xa2,0x93,0x00,0x94,0xf6,0x00,0x97,0xa3,0x96,0x81,0x00,0x00,0x98
};
static_assert(sizeof(cp437_encode_a0_ff) == ((0xff - 0xa0) + 1));

PRIVATE ATTR_DBGRODATA byte_t const cp437_encode_2550_256C[] = {
	205,186,213,214,201,184,183,187,212,211,200,190,189,188,198,
	199,204,181,182,185,209,210,203,207,208,202,216,215,206,
};
static_assert(sizeof(cp437_encode_2550_256C) == ((0x256C - 0x2550) + 1));

PRIVATE NOBLOCK ATTR_DBGTEXT ATTR_CONST WUNUSED byte_t
NOTHROW(FCALL cp437_encode)(char32_t unicode) {
	if (unicode >= 0x20 && unicode <= 0x7f)
		return unicode;
	if (unicode >= 0xa0 && unicode <= 0xff)
		return cp437_encode_a0_ff[unicode - 0xa0];
	if (unicode >= 0x2550 && unicode <= 0x256C)
		return cp437_encode_2550_256C[unicode - 0x2550];
	switch (unicode) {

	case 0x0192: return 159;

	case 0x0393: return 226;
	case 0x0398: return 233;
	case 0x03A3: return 228;
	case 0x03A6: return 232;
	case 0x03A9: return 234;
	case 0x03B1: return 224;
	case 0x03B4: return 235;
	case 0x03B5: return 238;
	case 0x03C0: return 227;
	case 0x03C3: return 229;
	case 0x03C4: return 231;
	case 0x03C6: return 237;

	case 0x2022: return 7;

	case 0x203C: return 19;

	case 0x207F: return 252;

	case 0x20A7: return 158;

	case 0x2190: return 27;
	case 0x2191: return 24;
	case 0x2192: return 26;
	case 0x2193: return 25;
	case 0x2194: return 29;
	case 0x2195: return 18;

	case 0x21A8: return 23;

	case 0x2219: return 249;
	case 0x221A: return 251;
	case 0x221E: return 236;
	case 0x221F: return 28;

	case 0x2229: return 239;

	case 0x2248: return 247;

	case 0x2261: return 240;
	case 0x2264: return 243;
	case 0x2265: return 242;

	case 0x2302: return 127;
	case 0x2310: return 169;

	case 0x2320: return 244;
	case 0x2321: return 245;

	case 0x2500: return 196;
	case 0x2502: return 179;
	case 0x250C: return 218;
	case 0x2510: return 191;
	case 0x2514: return 192;
	case 0x2518: return 217;
	case 0x251C: return 195;
	case 0x2524: return 180;
	case 0x252C: return 194;
	case 0x2534: return 193;
	case 0x253C: return 197;

	case 0x2580: return 223;
	case 0x2584: return 220;
	case 0x2588: return 219;
	case 0x258C: return 221;

	case 0x2590: return 222;
	case 0x2591: return 176;
	case 0x2592: return 177;
	case 0x2593: return 178;

	case 0x25A0: return 254;
	case 0x25AC: return 22;
	case 0x25B2: return 30;
	case 0x25BA: return 16;
	case 0x25BC: return 31;
	case 0x25C4: return 17;
	case 0x25CB: return 9;
	case 0x25D8: return 8;
	case 0x25D9: return 10;

	case 0x263A: return 1;
	case 0x263B: return 2;
	case 0x263C: return 15;
	case 0x2640: return 12;
	case 0x2642: return 11;

	case 0x2660: return 6;
	case 0x2663: return 5;
	case 0x2665: return 3;
	case 0x2666: return 4;
	case 0x266A: return 13;
	case 0x266B: return 14;

	default:
		break;
	}
	return '?';
}




PRIVATE NOBLOCK ATTR_DBGTEXT NONNULL((1, 2)) void
NOTHROW(FCALL vgatty_v_setcell)(struct vidttyaccess *__restrict UNUSED(self),
                                struct ansitty *__restrict tty,
                                uintptr_t address, char32_t ch) {
	uint16_t word;
	word = (tty->at_color << 8) | cp437_encode(ch);
	VGATTY_MAP_POKE(address, word);
}

PRIVATE NOBLOCK ATTR_DBGTEXT NONNULL((1)) void
NOTHROW(FCALL vgatty_v_hidecursor)(struct vidttyaccess *__restrict UNUSED(self)) {
	/* Hide cursor. */
	vga_wcrt(vgatty_crt_icX, VGA_CRTC_CURSOR_START,
	         vga_rcrt(vgatty_crt_icX, VGA_CRTC_CURSOR_START) |
	         VGA_CRA_FCURSOR_DISABLE);
}

PRIVATE NOBLOCK ATTR_DBGTEXT NONNULL((1)) void
NOTHROW(FCALL vgatty_v_showcursor)(struct vidttyaccess *__restrict self) {
	uint16_t address;

	/* Write the intended cursor position into hardware. */
	address = self->vta_cursor.vtc_cellx + self->vta_cursor.vtc_celly * 80;
	vga_wcrt(vgatty_crt_icX, VGA_CRTC_CURSOR_HI, (uint8_t)(address >> 8));
	vga_wcrt(vgatty_crt_icX, VGA_CRTC_CURSOR_LO, (uint8_t)(address));

	/* Show the cursor if it was hidden before. */
	vga_wcrt(vgatty_crt_icX, VGA_CRTC_CURSOR_START,
	         vga_rcrt(vgatty_crt_icX, VGA_CRTC_CURSOR_START) &
	         ~VGA_CRA_FCURSOR_DISABLE);
}

PRIVATE NOBLOCK ATTR_DBGTEXT NONNULL((1)) void
NOTHROW(FCALL vgatty_v_copycell)(struct vidttyaccess *__restrict UNUSED(self),
                                 uintptr_t to_cellid, uintptr_t from_cellid,
                                 size_t num_cells) {
	VGATTY_MAP_COPYIN(to_cellid * 2, from_cellid * 2, num_cells * 2);
}

PRIVATE NOBLOCK ATTR_DBGTEXT NONNULL((1, 2)) void
NOTHROW(FCALL vgatty_v_fillcells)(struct vidttyaccess *__restrict self,
                                  struct ansitty *__restrict tty,
                                  uintptr_t start, char32_t ch, size_t num_cells) {
	while (num_cells--)
		vgatty_v_setcell(self, tty, start++, ch);
}

PRIVATE NOBLOCK ATTR_DBGTEXT NONNULL((1)) void
NOTHROW(FCALL vgatty_v_activate)(struct vidttyaccess *__restrict UNUSED(self)) {
	/* No additional work needed to be done in here! */
}

PRIVATE NOBLOCK ATTR_DBGTEXT NONNULL((1, 3)) void
NOTHROW(FCALL vgatty_v_getcelldata)(struct vidttyaccess *__restrict UNUSED(self),
                                    uintptr_t address, byte_t buf[]) {
	uint16_t word = VGATTY_MAP_PEEK(address);
	UNALIGNED_SET16((uint16_t *)buf, word);
}

PRIVATE NOBLOCK ATTR_DBGTEXT NONNULL((1, 3)) void
NOTHROW(FCALL vgatty_v_setcelldata)(struct vidttyaccess *__restrict UNUSED(self),
                                    uintptr_t address, byte_t const buf[]) {
	uint16_t word;
	word = UNALIGNED_GET16((uint16_t const *)buf);
	VGATTY_MAP_POKE(address, word);
}


PRIVATE ATTR_DBGDATA struct vidttyaccess vgatty = {
	.vta_refcnt        = 1,
	.vta_lock          = ATOMIC_LOCK_INIT,
	.vta_flags         = VIDTTYACCESS_F_ACTIVE,
	.vta_cellw         = 9,
	.vta_cellh         = 16,
	.vta_resx          = 80,
	.vta_resy          = 25,
	.vta_scan          = 80,
	.vta_cellsize      = 2,
	.vta_scroll_ystart = 0,     /* Reset by `dbg_reset_tty()' */
	.vta_scroll_yend   = 0,     /* Reset by `dbg_reset_tty()' */
	.vta_cursor        = { 0 }, /* Reset by `dbg_reset_tty()' */
	.vta_destroy       = (typeoffield(struct vidttyaccess, vta_destroy))(void *)-1,
	.vta_setcell       = &vgatty_v_setcell,
	.vta_hidecursor    = &vgatty_v_hidecursor,
	.vta_showcursor    = &vgatty_v_showcursor,
	.vta_copycell      = &vgatty_v_copycell,
	.vta_fillcells     = &vgatty_v_fillcells,
	.vta_activate      = &vgatty_v_activate,
	.vta_getcelldata   = &vgatty_v_getcelldata,
	.vta_setcelldata   = &vgatty_v_setcelldata,
};


#ifdef VGATTY_MAP_B8000_IS_KERNELSPACE_BASE
PRIVATE ATTR_DBGBSS pagedir_pushval_t vgatty_saved_b8000 = 0;
#endif /* VGATTY_MAP_B8000_IS_KERNELSPACE_BASE */

/* Saved text-mode memory */
#define TEXTPAGESIZE (80 * 25 * 2)
PRIVATE ATTR_DBGBSS byte_t vgatty_smem[TEXTPAGESIZE];

/* Exchange the contents of `vgatty_smem' and the video memory. */
INTERN ATTR_DBGTEXT void NOTHROW(FCALL vgatty_smem_exchange)(void) {
	byte_t tempbuf[TEXTPAGESIZE];
	VGATTY_MAP_COPYFROM(tempbuf, 0, TEXTPAGESIZE);
	VGATTY_MAP_COPYTO(0, vgatty_smem, TEXTPAGESIZE);
	memcpy(vgatty_smem, tempbuf, TEXTPAGESIZE);
}

/* Arch-specific, fallback functions  for acquiring a  terminal.
 * These work the same as `vdo_enterdbg' / `vdo_leavedbg' when a
 * proper  video adapter has been configured in `viddev_default' */
INTERN ATTR_DBGTEXT ATTR_RETNONNULL WUNUSED struct vidttyaccess *
NOTHROW(FCALL dbg_fallback_acquiretty)(void) {
#ifndef HAVE_VGATTY_B8000
	uint32_t vgatty_b8000;
#endif /* !HAVE_VGATTY_B8000 */
	/* Figure out where the on-screen text buffer must go. */
	static ATTR_DBGRODATA uint32_t const b8000_addresses[4] = {
		[VGA_GR06_FMM_128K >> VGA_GR06_FMM_SHIFT]   = 0xA0000,
		[VGA_GR06_FMM_64K >> VGA_GR06_FMM_SHIFT]    = 0xA0000,
		[VGA_GR06_FMM_32K_LO >> VGA_GR06_FMM_SHIFT] = 0xB0000,
		[VGA_GR06_FMM_32K_HI >> VGA_GR06_FMM_SHIFT] = 0xB8000,
	};
	uint8_t gfx_misc = vga_rgfx(VGA_GFX_MISC);
	vgatty_b8000     = b8000_addresses[(gfx_misc & VGA_GR06_FMM_MASK) >> VGA_GR06_FMM_SHIFT];

	/* Determine CRT control port. */
	vgatty_crt_icX = VGA_CRT_IC;
	if (!(vga_rmis() & VGA_MIS_FCOLOR))
		vgatty_crt_icX = VGA_CRT_IM;

	/* Create video memory mapping. */
#ifdef VGATTY_MAP_B8000_IS_KERNELSPACE_BASE
	vgatty_saved_b8000 = pagedir_push_mapone(VGATTY_MAP_B8000,
	                                         (physaddr_t)vgatty_b8000,
	                                         PAGEDIR_PROT_READ |
	                                         PAGEDIR_PROT_WRITE);
#endif /* VGATTY_MAP_B8000_IS_KERNELSPACE_BASE */

	/* Save text-mode memory. */
	vgatty_smem_exchange();

	/* Don't do any mode switching or trying to load a font into video memory.
	 * Since no custom video adapter driver has been loaded, we simply  assume
	 * defaults for everything,  including the BIOS  having set-up 80x25  text
	 * mode, as well as loaded a font into video memory. */

	return &vgatty;
}

INTERN ATTR_DBGTEXT void
NOTHROW(FCALL dbg_fallback_releasetty)(void) {
	/* Restore text-mode memory. */
	vgatty_smem_exchange();

	/* Remove video memory mapping. */
#ifdef VGATTY_MAP_B8000_IS_KERNELSPACE_BASE
	pagedir_pop_mapone(VGATTY_MAP_B8000, vgatty_saved_b8000);
	pagedir_syncone(VGATTY_MAP_B8000);
#endif /* VGATTY_MAP_B8000_IS_KERNELSPACE_BASE */
}


DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_OUTPUT_C */
