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
#ifndef _LIBSVGA_CHIPSET_H
#define _LIBSVGA_CHIPSET_H 1

#include "api.h"
/**/

#include <bits/types.h>
#include <kos/sched/shared-rwlock.h>

#ifdef __CC__
__DECL_BEGIN

#ifndef __shift_t
#define __shift_t __SHIFT_TYPE__
#endif /* !__shift_t */

/* Flags for `struct svga_modeinfo::smi_flags' */
#define SVGA_MODEINFO_F_LFB 0x0001 /* Linear  */
#define SVGA_MODEINFO_F_PAL 0x0002 /* Palette-driven video mode. (Get/set palette colors `VGA_PEL_MSK' / `VGA_PEL_IW' / `VGA_PEL_D') */
#define SVGA_MODEINFO_F_BW  0x0004 /* Black-and-white video mode (`smi_colors' is # of possible gray-scale values) */

struct svga_modeinfo {
	__physaddr_t smi_lfb;                /* [valid_if(SVGA_MODEINFO_F_LFB)] Linear frame buffer base address (if available) */
	__size_t     smi_vmemsize;           /* Video memory size (in bytes). */
	__size_t     smi_vpagecnt;           /* [== CEILDIV(smi_vmemsize, 64K)] # of video pages */
	__uint32_t   smi_flags;              /* Mode flags (set of `SVGA_MODEINFO_F_*') */
	__uint16_t   smi_resx;               /* Resolution in X */
	__uint16_t   smi_resy;               /* Resolution in Y */
	__size_t     smi_totalpixels;        /* `smi_vmemsize * 8 / smi_bits_per_pixel' */
	__uint8_t    smi_bytes_per_pixel;    /* Bytes per pixel (rounded up) */
	__uint8_t    smi_bits_per_pixel;     /* Bits per pixel */
	__uint32_t   smi_colors;             /* # of possible different colors  on-screen at the same  time.
	                                      * For palette-driven mode, the # of colors within the palette. */
	__uint32_t   smi_scanline;           /* Scanline size (in bytes; aligned by `smi_logicalwidth_align')
	                                      * Usually is  `>= CEIL_ALIGN(smi_resy, smi_logicalwidth_align)' */
	__uint32_t   smi_logicalwidth_align; /* Alignment requirements of `sc_logicalwidth' */
	__uint32_t   smi_logicalwidth_max;   /* Max value allowed for `sc_logicalwidth' */
	__shift_t    smi_rshift, smi_rbits;  /* [valid_if(!SVGA_MODEINFO_F_PAL && !SVGA_MODEINFO_F_BW)] Red color shift/bits */
	__shift_t    smi_gshift, smi_gbits;  /* [valid_if(!SVGA_MODEINFO_F_PAL && !SVGA_MODEINFO_F_BW)] Green color shift/bits */
	__shift_t    smi_bshift, smi_bbits;  /* [valid_if(!SVGA_MODEINFO_F_PAL && !SVGA_MODEINFO_F_BW)] Blue color shift/bits */
	/* Chipset-specific data (a total of `sco_modeinfosize - sizeof(struct svga_modeinfo)' bytes) goes here. */
};


struct svga_chipset;
struct svga_chipset_ops {

	/* [== sizeof(struct MYCHIPSET_svga_modeinfo)] */
	__size_t sco_modeinfosize;

	/* [1..1][lock(WRITE(sc_lock))]
	 * - Return  information about the first mode with a cs-specific ID that
	 *   is `>= *p_index'. If no such mode exists, return `false'. Otherwise
	 *   advance `*p_index' to point to the next mode and return `true'.
	 * - `result' is a `sco_modeinfosize'-bytes large buffer allocated by the
	 *   caller. If the caller decides they  want to use some specific  mode,
	 *   they will pass `result' to `sco_setmode()'
	 * @return: true:  Another mode was retrieved.
	 * @return: false: All modes enumerated. */
	__BOOL (LIBSVGA_CC *sco_getmode)(struct svga_chipset *__restrict self,
	                                 struct svga_modeinfo *__restrict result,
	                                 __uintptr_t *__restrict p_index)
			__THROWS(E_IOERROR);

	/* [1..1][lock(WRITE(sc_lock))]
	 * - Set a given video `mode' and update `self->sc_mode' to match `mode'
	 * - The contents of `mode' have previously been retrieved via `sco_getmode'
	 * - Prior to this function being  called for the first  time,
	 *   `self->sc_mode.smi_bits_per_pixel' may be `0' to indicate
	 *   that the current video mode is unknown. */
	void (LIBSVGA_CC *sco_setmode)(struct svga_chipset *__restrict self,
	                               struct svga_modeinfo const *__restrict mode);

	/* [1..1][lock(WRITE(sc_lock))]
	 * - Save/load all chipset registers to/from a `sc_regsize'-long `regbuf'
	 * - These functions can be used  to save/restore the current video  mode
	 *   even before `sco_setmode' was called for the first time. They should
	 *   also  be used before  exclusive display control is  handed to a user
	 *   application, and after that application relinquishes control. */
	void (LIBSVGA_CC *sco_getregs)(struct svga_chipset *__restrict self, __byte_t regbuf[]);
	void (LIBSVGA_CC *sco_setregs)(struct svga_chipset *__restrict self, __byte_t const regbuf[]);

	/* [1..1][lock(WRITE(sc_lock))]
	 * - Set the current display page to the `pageno'th 64K chunk
	 * - This function makes it so that the 64K physical memory at A0000-AFFFF
	 *   will be mapped to video card memory `VIDEO_MEMORY + pageno * 0x10000'
	 * - This operator will set `self->sc_rdpageno = self->sc_wrpageno = pageno'
	 * - These functions may only be used if no LFB (linear frame buffer) is
	 *   available. If such a buffer is available, you must mmap() `smi_lfb'
	 *   and just directly modify its backing memory!
	 * @assume(WAS_CALLED(sco_setmode));
	 * @assume(pageno < self->sc_mode.smi_vpagecnt);
	 * @assume(!(self->sc_mode.smi_flags & SVGA_MODEINFO_F_LFB)); */
	void (LIBSVGA_CC *sco_setpage)(struct svga_chipset *__restrict self, __size_t pageno)
			__THROWS(E_IOERROR);
	/* [1..1][lock(WRITE(sc_lock))] Same as `sco_setpage', but *may* only update `sc_rdpageno' */
	void (LIBSVGA_CC *sco_setrdpage)(struct svga_chipset *__restrict self, __size_t pageno)
			__THROWS(E_IOERROR);
	/* [1..1][lock(WRITE(sc_lock))] Same as `sco_setpage', but *may* only update `sc_wrpageno' */
	void (LIBSVGA_CC *sco_setwrpage)(struct svga_chipset *__restrict self, __size_t pageno)
			__THROWS(E_IOERROR);

	/* [1..1][lock(WRITE(sc_lock))]
	 * @assume(offset < self->sc_mode.smi_vpagecnt);
	 * - Set display start offset to `offset' pixels from `self->sc_mode.smi_vmembase'
	 * @assume(WAS_CALLED(sco_setmode));
	 * @assume(offset <= smi_totalpixels); */
	void (LIBSVGA_CC *sco_setdisplaystart)(struct svga_chipset *__restrict self, __size_t offset)
			__THROWS(E_IOERROR);

	/* [1..1][lock(WRITE(sc_lock))]
	 * - Set  logical screen width  to `offset' bytes and
	 *   write the new value into `self->sc_logicalwidth'
	 * - The  logical screen  width is  the #  of bytes the
	 *   video card  will add  to the  start of  a line  in
	 *   order to get the memory location of the next line.
	 * - The value must be aligned by `self->sc_logicalwidth_align'
	 * - The default value is `smi_scanline'
	 * @assume(WAS_CALLED(sco_setmode));
	 * @assume(IS_ALIGNED(offset, self->sc_mode.smi_logicalwidth_align));
	 * @assume(offset <= smi_logicalwidth_max); */
	void (LIBSVGA_CC *sco_setlogicalwidth)(struct svga_chipset *__restrict self, __uint32_t offset)
			__THROWS(E_IOERROR);
};

struct svga_chipset {
	struct svga_chipset_ops const *sc_ops;          /* [1..1][const] Chipset operators. */
	struct shared_rwlock           sc_lock;         /* Lock for this chipset. */
	__size_t                       sc_regsize;      /* [const] Required buffer size for `sco_getregs' / `sco_setregs'. */
	__size_t                       sc_rdpageno;     /* [lock(sc_lock)][< sc_mode.smi_vpagecnt][valid_if(sc_mode.smi_bits_per_pixel != 0)]
	                                                 * Current display page for reads. */
	__size_t                       sc_wrpageno;     /* [lock(sc_lock)][< sc_mode.smi_vpagecnt][valid_if(sc_mode.smi_bits_per_pixel != 0)]
	                                                 * Current display page for writes. */
	__size_t                       sc_displaystart; /* [lock(sc_lock)][valid_if(sc_mode.smi_bits_per_pixel != 0)]
	                                                 * Current display start (pixels from `sc_mode.smi_vmembase'
	                                                 * to the beginning of the screen; usually top-left corner) */
	__uint32_t                     sc_logicalwidth; /* [lock(sc_lock)][valid_if(sc_mode.smi_bits_per_pixel != 0)]
	                                                 * Current logical screen width (in bytes; updated by `sco_setlogicalwidth') */
	struct svga_modeinfo           sc_mode;         /* [lock(sc_lock)][valid_if(sc_mode.smi_bits_per_pixel != 0)]
	                                                 * Current display mode */
	/* Chipset-specific data goes here. */
};



__DECL_END
#endif /* __CC__ */

#endif /* !_LIBSVGA_CHIPSET_H */
