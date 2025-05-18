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
#ifndef _LIBSVGADRV_CHIPSET_H
#define _LIBSVGADRV_CHIPSET_H 1

#include "api.h"
/**/

#include <bits/types.h>
#include <kos/anno.h>

#include <stdint.h>

#ifndef SVGA_CSNAMELEN
#define SVGA_CSNAMELEN 16
#endif /* !SVGA_CSNAMELEN */


/* Build feature flags: enable support for certain
 * hardware-accelerated  2D  rendering techniques.
 *
 * Note that not  every chipset is  able to  support
 * all/any of these operations (as a matter of fact:
 * no chipset is actually  able to support *all*  of
 * these)
 *
 * NOTES:
 * - Generally, "SVGA_HAVE_HW_SCROLL" is only supported
 *   by *old* chipsets (like basic VGA/EGA), and can be
 *   used to change the VRAM base address+scanline from
 *   which the graphics cards reads display data.
 *   - By assigning a larger "sco_setlogicalwidth", you
 *     are then able  to have an  off-screen buffer  of
 *     graphics data, which you can scroll into view by
 *     changing "sco_setdisplaystart".  The  same  also
 *     goes for vertical scrolling.
 *
 * - "SVGA_HAVE_HW_ASYNC_*" are features supported by
 *   more  modern graphics cards, and are represent a
 *   set  of operations the graphics card can perform
 *   to manipulate VRAM while the CPU isn't looking.
 */
#undef SVGA_HAVE_HW_SCROLL         /* sco_setdisplaystart + sco_setlogicalwidth */
#undef SVGA_HAVE_HW_ASYNC_COPYRECT /* sco_hw_async_copyrect */
#undef SVGA_HAVE_HW_ASYNC_FILLRECT /* sco_hw_async_fillrect */
#ifndef __KERNEL__
#define SVGA_HAVE_HW_SCROLL /* Unused by modsvga, and therefor not enabled here */
#endif /* !__KERNEL__ */
#define SVGA_HAVE_HW_ASYNC_COPYRECT
#define SVGA_HAVE_HW_ASYNC_FILLRECT


#undef SVGA_HAVE_HW_ASYNC_WAITFOR
#if (defined(SVGA_HAVE_HW_ASYNC_COPYRECT) || \
     defined(SVGA_HAVE_HW_ASYNC_FILLRECT))
#define SVGA_HAVE_HW_ASYNC_WAITFOR
#endif /* SVGA_HAVE_HWRENDER_* */

#ifdef __CC__
__DECL_BEGIN

#ifndef __shift_t
#define __shift_t __SHIFT_TYPE__
#endif /* !__shift_t */

/* Flags for `struct svga_modeinfo::smi_flags' */
#define SVGA_MODEINFO_F_LFB    0x0001 /* Linear frame buffer is available. */
#define SVGA_MODEINFO_F_PAL    0x0002 /* Palette-driven video mode. (Get/set palette colors `VGA_PEL_MSK' / `VGA_PEL_IW' / `VGA_PEL_D') */
#define SVGA_MODEINFO_F_BW     0x0004 /* Black-and-white video mode (`1 << smi_colorbits' is  # of possible gray-scale  values)
                                       * May still be combined with `SVGA_MODEINFO_F_PAL' for emulation of specific b/w colors. */
#define SVGA_MODEINFO_F_TXT    0x0008 /* Text video mode. When set, you may also assume that `SVGA_MODEINFO_F_LFB' and
                                       * `SVGA_MODEINFO_F_PAL' are also set.
                                       * With this, `smi_lfb' points at a `smi_scanline * smi_resy'-large buffer,  where
                                       * each character cell is a 16-bit word,  with upper 8 bits selecting fg/bg  color
                                       * palette indices (alongside the "blink" bit based on `VGA_AT10_FBLINK'), and the
                                       * low 8 bits select the character index from the currently loaded font. */
#define SVGA_MODEINFO_F_PLANAR 0x0010 /* Planar video mode. In this case, `smi_bits_per_pixel < smi_colorbits', such  that
                                       * each plane defines `smi_bits_per_pixel' bits of a whole, totaling `smi_colorbits'
                                       * bits across `smi_colorbits / smi_bits_per_pixel' planes. Also note that this flag
                                       * implies `SVGA_MODEINFO_F_PAL'.
                                       *
                                       * There are 2 possible configurations for this:
                                       *  - smi_bits_per_pixel == 1 && smi_colorbits == 4:
                                       *    This is a 16-color mode, with each plane holding exactly 1 bit of the final palette index
                                       *  - smi_bits_per_pixel == 2 && smi_colorbits == 8:
                                       *    This is a 256-color mode, with each plane holding exactly 2 bits of the final palette index */


typedef __uint16_t svga_res_t; /* Video resolution */
struct svga_modeinfo {
	__physaddr_t smi_lfb;                /* [valid_if(SVGA_MODEINFO_F_LFB)] Linear frame buffer base address (if available) */
	__uint32_t   smi_flags;              /* Mode flags (set of `SVGA_MODEINFO_F_*') */
	__uint32_t   smi_scanline;           /* [!0] Scanline size (in bytes; aligned by `sc_logicalwidth_align')
	                                      *      Usually is `>= CEIL_ALIGN(smi_resy, sc_logicalwidth_align)' */
	svga_res_t   smi_resx;               /* [!0] Resolution in X (when `SVGA_MODEINFO_F_TXT': # of character cells in X) */
	svga_res_t   smi_resy;               /* [!0] Resolution in Y (when `SVGA_MODEINFO_F_TXT': # of character cells in Y) */
	__shift_t    smi_bits_per_pixel;     /* [!0] Bits per pixel (when `SVGA_MODEINFO_F_TXT': 16)
	                                      * Usually one of `1', `2', `4', `8', `16', `24', `32'. */
	__shift_t    smi_colorbits;          /* [!0][valid_if(!SVGA_MODEINFO_F_TXT)]
	                                      * # of bits per pixel that encode color (usually <= smi_bits_per_pixel, unless in
	                                      * `SVGA_MODEINFO_F_PLANAR').  Use  as  `NUM_PALETTE_COLORS = 1 << smi_colorbits'. */
	__shift_t    smi_rshift, smi_rbits;  /* [valid_if(!SVGA_MODEINFO_F_PAL && !SVGA_MODEINFO_F_BW)] Red color shift/bits */
	__shift_t    smi_gshift, smi_gbits;  /* [valid_if(!SVGA_MODEINFO_F_PAL && !SVGA_MODEINFO_F_BW)] Green color shift/bits */
	__shift_t    smi_bshift, smi_bbits;  /* [valid_if(!SVGA_MODEINFO_F_PAL && !SVGA_MODEINFO_F_BW)] Blue color shift/bits */
	/* Chipset-specific data (a total of `sco_modeinfosize - sizeof(struct svga_modeinfo)' bytes) goes here. */
};


struct svga_rect {
	svga_res_t svr_x; /* X pixel coord (offset from screen left) */
	svga_res_t svr_y; /* Y pixel coord (offset from screen top) */
	svga_res_t svr_w; /* Width (in pixels) */
	svga_res_t svr_h; /* Height (in pixels) */
};

#ifdef SVGA_HAVE_HW_ASYNC_COPYRECT
struct svga_copyrect {
	svga_res_t svcr_sx; /* Source X pixel coord (offset from screen left) */
	svga_res_t svcr_sy; /* Source Y pixel coord (offset from screen top) */
	union {
		struct {
			svga_res_t svcr_dx; /* Destination X pixel coord (offset from screen left) */
			svga_res_t svcr_dy; /* Destination Y pixel coord (offset from screen top) */
			svga_res_t svcr_w;  /* Width (in pixels) */
			svga_res_t svcr_h;  /* Height (in pixels) */
		};
		struct svga_rect svcr_dest; /* Destination rect */
	};
};
#endif /* SVGA_HAVE_HW_ASYNC_COPYRECT */


struct svga_chipset;

/* Callback function for chipset string enumeration.
 * @param: name:  Spec string name.
 * @param: value: Spec string value.
 * @return: * :   pformatprinter-compatible return value. */
typedef __ATTR_NONNULL_T((2, 3)) __ssize_t
(LIBSVGADRV_CC *svga_chipset_enumstring_t)(void *arg,
                                           char const *__restrict name,
                                           char const *__restrict value);


struct svga_palette_color {
	__uint8_t spc_r; /* Red */
	__uint8_t spc_g; /* Green */
	__uint8_t spc_b; /* Blue */
};

struct svga_chipset_ops {

	/* [1..1][const] Chipset-specific finalization. */
	__NOBLOCK __ATTR_NONNULL_T((1)) void
	__NOTHROW_T(LIBSVGADRV_CC *sco_fini)(struct svga_chipset *__restrict self);

	/* [const][== sizeof(struct MYCHIPSET_svga_modeinfo)] */
	__size_t sco_modeinfosize;

	/* [0..1][const][lock(EXTERNAL)]
	 * Enumerate chipset-specific identification strings. */
	__ATTR_NONNULL_T((1, 2)) __ssize_t
	(LIBSVGADRV_CC *sco_strings)(struct svga_chipset *__restrict self,
	                             svga_chipset_enumstring_t cb, void *arg);

	/* [1..1][const][lock(EXTERNAL)]
	 * - Return  information about the first mode with a cs-specific ID that
	 *   is `>= *p_index'. If no such mode exists, return `false'. Otherwise
	 *   advance `*p_index' to point to the next mode and return `true'.
	 * - `result' is a `sco_modeinfosize'-bytes large buffer allocated by the
	 *   caller. If the caller decides they  want to use some specific  mode,
	 *   they will pass `result' to `sco_setmode()'
	 * - The caller guaranties that `*p_index' is either `0', or whatever
	 *   was  written  back to  that  variable during  a  preceding call.
	 * @return: true:  Another mode was retrieved.
	 * @return: false: All modes enumerated. */
	__ATTR_WUNUSED __ATTR_NONNULL_T((1, 2, 3)) __BOOL
	(LIBSVGADRV_CC *sco_getmode)(struct svga_chipset *__restrict self,
	                             struct svga_modeinfo *__restrict result,
	                             __uintptr_t *__restrict p_index)
			__THROWS(E_IOERROR);

	/* [1..1][const][lock(EXTERNAL)]
	 * - Set a given video  mode to `mode'.
	 * - The contents of `mode' have previously been retrieved via `sco_getmode'
	 * - Prior to this function being called for the first time, any  function
	 *   that documents making use of `CURRENT_VIDEO_MODE' must not be called;
	 *   iow: be considered `[valid_if(WAS_CALLED(sco_setmode))]' */
	__ATTR_NONNULL_T((1, 2)) void
	(LIBSVGADRV_CC *sco_setmode)(struct svga_chipset *__restrict self,
	                             struct svga_modeinfo const *__restrict mode);

	/* [1..1][const][lock(EXTERNAL)]
	 * - Save/load all chipset registers to/from a `sco_regsize'-long `regbuf'
	 * - These functions can be used  to save/restore the current video  mode
	 *   even before `sco_setmode' was called for the first time. They should
	 *   also  be used before  exclusive display control is  handed to a user
	 *   application, and after that application relinquishes control. */
	__ATTR_NONNULL_T((1, 2)) void
	(LIBSVGADRV_CC *sco_getregs)(struct svga_chipset *__restrict self, __byte_t regbuf[]);
	__ATTR_NONNULL_T((1, 2)) void
	(LIBSVGADRV_CC *sco_setregs)(struct svga_chipset *__restrict self, __byte_t const regbuf[]);

	/* [const] Required buffer size for `sco_getregs' / `sco_setregs'. */
	__size_t sco_regsize;

	/* [1..1][const][lock(EXTERNAL)]
	 * - Get/set (parts of) the video palette.
	 * - Weak undefined behavior when current video mode has no palette
	 * - Caller must ensure that `base + count <= 0x100'
	 * - In most cases, this will simply read/write the core VGA palette */
	__ATTR_NONNULL_T((1)) void
	(LIBSVGADRV_CC *sco_getpal)(struct svga_chipset *__restrict self,
	                            __uint8_t base, __uint8_t count,
	                            __NCX struct svga_palette_color *buf);
	__ATTR_NONNULL_T((1)) void
	(LIBSVGADRV_CC *sco_setpal)(struct svga_chipset *__restrict self,
	                            __uint8_t base, __uint8_t count,
	                            __NCX struct svga_palette_color const *buf);

	/* NOTE: Operators below may be altered by chipset drivers during `sco_setmode()'
	 *       This should be fine since they can already only be called while  already
	 *       holding a lock to `EXTERNAL', which prevents one from changing the mode.
	 * Additionally, they may not actually be initialized prior to the first call to
	 * `sco_setmode()'. */

	/* [1..1][lock(EXTERNAL)]
	 * - Set the current display window to the `window'th 64K chunk
	 * - This function makes it so that the 64K physical memory at A0000-AFFFF
	 *   will be mapped to video card memory `VIDEO_MEMORY + window * 0x10000'
	 * - This operator will set `self->sc_rdwindow = self->sc_wrwindow = window'
	 * - These functions may only be used if no LFB (linear frame buffer) is
	 *   available. If such a buffer is available, you must mmap() `smi_lfb'
	 *   and just directly modify its backing memory!
	 * @assume(windows != sc_rdwindow || windows != sc_wrwindow); // as relevant
	 * @assume(WAS_CALLED(sco_setmode));
	 * @assume(window < CEILDIV(self->sc_vmemsize, 64 * 1024));
	 * @assume(!(CURRENT_VIDEO_MODE.smi_flags & SVGA_MODEINFO_F_LFB)); */
	__ATTR_NONNULL_T((1)) void
	(LIBSVGADRV_CC *sco_setwindow)(struct svga_chipset *__restrict self, __size_t window)
			__THROWS(E_IOERROR);
	/* [1..1][lock(EXTERNAL)] Same as `sco_setwindow', but *may* only update `sc_rdwindow' */
	__ATTR_NONNULL_T((1)) void
	(LIBSVGADRV_CC *sco_setrdwindow)(struct svga_chipset *__restrict self, __size_t window)
			__THROWS(E_IOERROR);
	/* [1..1][lock(EXTERNAL)] Same as `sco_setwindow', but *may* only update `sc_wrwindow' */
	__ATTR_NONNULL_T((1)) void
	(LIBSVGADRV_CC *sco_setwrwindow)(struct svga_chipset *__restrict self, __size_t window)
			__THROWS(E_IOERROR);

#ifdef SVGA_HAVE_HW_SCROLL
	/* [0..1][lock(EXTERNAL)]
	 * - Set  display start offset  to `offset' pixels from
	 *   `CURRENT_VIDEO_MODE.smi_lfb' or the start of video
	 *   memory
	 * - The offset is calculated as `X + Y * self->sc_logicalwidth'
	 * - It is undefined what happens when `sco_setlogicalwidth' is  used
	 *   to alter `sc_logicalwidth', as its value affects the calculation
	 *   of  the display start  offset, so you  should probably call this
	 *   function after changing the logical display width.
	 * - Set `self->sc_displaystart = offset;'
	 * - Not available in text-mode video modes.
	 * - Set to "NULL" if never supported
	 * @assume(WAS_CALLED(sco_setmode));
	 * @assume(offset <= self->sc_vmemsize * 8 / CURRENT_VIDEO_MODE.smi_bits_per_pixel);
	 * @assume(!(CURRENT_VIDEO_MODE.smi_flags & SVGA_MODEINFO_F_TXT)); */
	__ATTR_NONNULL_T((1)) void
	(LIBSVGADRV_CC *sco_setdisplaystart)(struct svga_chipset *__restrict self, __size_t offset)
			__THROWS(E_IOERROR);

	/* [0..1][lock(EXTERNAL)]
	 * - Set  logical screen width  to `width' pixels and
	 *   write the new value into `self->sc_logicalwidth'
	 * - The logical screen  width is the  # of pixels  the
	 *   video card  will add  to the  start of  a line  in
	 *   order to get the memory location of the next line.
	 * - The value must be aligned by `self->sc_logicalwidth_align'
	 * - The default value is `smi_scanline'
	 * - Not available in text-mode video modes.
	 * - Set to "NULL" if never supported
	 * @assume(WAS_CALLED(sco_setmode));
	 * @assume(IS_ALIGNED(width, self->sc_logicalwidth_align));
	 * @assume(width <= sc_logicalwidth_max);
	 * @assume(!(CURRENT_VIDEO_MODE.smi_flags & SVGA_MODEINFO_F_TXT)); */
	__ATTR_NONNULL_T((1)) void
	(LIBSVGADRV_CC *sco_setlogicalwidth)(struct svga_chipset *__restrict self, __uint32_t width)
			__THROWS(E_IOERROR);
#endif /* SVGA_HAVE_HW_SCROLL */

	/* [0..1][lock(EXTERNAL)]
	 * Indicate to the chipset that a rect of pixels may have been modified.
	 * Caller must ensure that the rect does not exceed the set  resolution. */
	__ATTR_NONNULL_T((1, 2)) void
	NOTHROW_T(LIBSVGADRV_CC *sco_updaterect)(struct svga_chipset *__restrict self,
	                                         struct svga_rect const *__restrict rect);

	/* [0..1][lock(EXTERNAL)]
	 * Optional hardware rendering support APIs.
	 * - sco_hw_async_waitfor:  Wait  for HW rendering to be finished.
	 *                          This must be done to prevent artifacts
	 *                          when wanting to access the framebuffer
	 *                          directly.
	 * - sco_hw_async_copyrect: Perform a hardware-accelerated copy of pixels
	 * - sco_hw_async_fillrect: Perform a hardware-accelerated fill of pixels
	 */
#ifdef SVGA_HAVE_HW_ASYNC_WAITFOR
	__ATTR_NONNULL_T((1)) void
	NOTHROW_T(LIBSVGADRV_CC *sco_hw_async_waitfor)(struct svga_chipset *__restrict self);
#endif /* SVGA_HAVE_HW_ASYNC_WAITFOR */
#ifdef SVGA_HAVE_HW_ASYNC_COPYRECT
	__ATTR_NONNULL_T((1, 2)) void
	NOTHROW_T(LIBSVGADRV_CC *sco_hw_async_copyrect)(struct svga_chipset *__restrict self,
	                                                struct svga_copyrect const *__restrict rect);
#endif /* SVGA_HAVE_HW_ASYNC_COPYRECT */
#ifdef SVGA_HAVE_HW_ASYNC_FILLRECT
	/* @param: color: Fill-color (set-up as per `smi_*shift' / `smi_*bits' from `svga_modeinfo') */
	__ATTR_NONNULL_T((1, 2)) void
	NOTHROW_T(LIBSVGADRV_CC *sco_hw_async_fillrect)(struct svga_chipset *__restrict self,
	                                                struct svga_rect const *__restrict rect,
	                                                uint32_t color);
#endif /* SVGA_HAVE_HW_ASYNC_FILLRECT */
};

struct svga_chipset {
	struct svga_chipset_ops sc_ops;                /* [const] Chipset operators. */
	__size_t                sc_vmemsize;           /* [const] Video memory size (in bytes; usually a multiple of 64K). */
	__size_t                sc_rdwindow;           /* [lock(EXTERNAL)][< CEILDIV(sc_vmemsize, 64 * 1024)][valid_if(WAS_CALLED(sco_setmode) && !SVGA_MODEINFO_F_LFB)]
	                                                * Current display window for reads. */
	__size_t                sc_wrwindow;           /* [lock(EXTERNAL)][< CEILDIV(sc_vmemsize, 64 * 1024)][valid_if(WAS_CALLED(sco_setmode) && !SVGA_MODEINFO_F_LFB)]
	                                                * Current display window for writes. */
#ifdef SVGA_HAVE_HW_SCROLL
	__size_t                sc_displaystart;       /* [lock(EXTERNAL)][valid_if(WAS_CALLED(sco_setmode) && sco_setdisplaystart != NULL)]
	                                                * Current display  start (pixels  from  `CURRENT_VIDEO_MODE.smi_lfb', or  the  start
	                                                * of video memory, to the beginning of the screen; usually top-left corner). */
	__uint32_t              sc_logicalwidth;       /* [lock(EXTERNAL)][valid_if(WAS_CALLED(sco_setmode) && sco_setlogicalwidth != NULL)]
	                                                * Current  logical  screen  width  (in  pixels;  updated  by  `sco_setlogicalwidth')
	                                                * This  is  the  # of  pixel  between the  start  of  two lines,  commonly  known as
	                                                * the scanline,  only  this  time  expressed in  pixels,  rather  than  bytes.  Also
	                                                * note that  because  scanlines  always have  to  start  on whole  bytes,  there  is
	                                                * a alignment requirement of `sc_logicalwidth_align' pixels. */
	__uint32_t              sc_logicalwidth_max;   /* [lock(EXTERNAL)][valid_if(WAS_CALLED(sco_setmode) && sco_setlogicalwidth != NULL)] Max value allowed for `sc_logicalwidth' */
	__uint32_t              sc_logicalwidth_align; /* [lock(EXTERNAL)][valid_if(WAS_CALLED(sco_setmode) && sco_setlogicalwidth != NULL)] Alignment requirements of `sc_logicalwidth' */
#endif /* SVGA_HAVE_HW_SCROLL */
	/* Chipset-specific data goes here. */
};


struct svga_chipset_driver {
	__size_t scd_cssize; /* == sizeof(struct MYCHIPSET_svga_chipset) */

	/* [1..1] Probe for the presence of this chipset and initialize `self'
	 *        For this, `self' must point to a `scd_cssize'-byte long buffer.
	 * NOTE: This function may not necessarily initialize the following fields,
	 *       and  is allowed to assume that the caller has pre-initialized them
	 *       to NULL/0 (all the optional chipset operator):
	 * - self->sc_ops.sco_setdisplaystart
	 * - self->sc_ops.sco_setlogicalwidth
	 * - self->sc_ops.sco_updaterect_push
	 * - self->sc_ops.sco_updaterect_commit
	 * @return: true:  Chipset found.
	 * @return: false: Chipset isn't present. */
	__ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) __BOOL
	(LIBSVGADRV_CC *scd_probe)(struct svga_chipset *__restrict self);

	/* Chipset name. */
	char scd_name[SVGA_CSNAMELEN];
};



/* Return the list of supported VGA chipset drivers (terminated by a bzero'd entry)
 * This list is sorted from most specific- to most generic driver. As such, some of
 * the later drivers might also  be usable even when one  of the former ones  could
 * also be used.
 *
 * As such, when probing for devices you should simply iterate this list until you
 * find a driver  for which probing  succeeds. Once that  happens, simply keep  on
 * using that driver. */
typedef __ATTR_PURE_T __ATTR_RETNONNULL_T __ATTR_WUNUSED_T struct svga_chipset_driver const *
__NOTHROW_T(LIBSVGADRV_CC *PSVGA_CHIPSET_GETDRIVERS)(void);
#ifdef LIBSVGADRV_WANT_PROTOTYPES
LIBSVGADRV_DECL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED struct svga_chipset_driver const *
__NOTHROW(LIBSVGADRV_CC svga_chipset_getdrivers)(void);
#endif /* LIBSVGADRV_WANT_PROTOTYPES */


__DECL_END
#endif /* __CC__ */

#endif /* !_LIBSVGADRV_CHIPSET_H */
