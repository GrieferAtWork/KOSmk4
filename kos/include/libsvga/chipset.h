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
#define SVGA_MODEINFO_F_LFB    0x0001 /* Linear frame buffer is available. */
#define SVGA_MODEINFO_F_PAL    0x0002 /* Palette-driven video mode. (Get/set palette colors `VGA_PEL_MSK' / `VGA_PEL_IW' / `VGA_PEL_D') */
#define SVGA_MODEINFO_F_BW     0x0004 /* Black-and-white video mode (`smi_colors' is # of possible gray-scale values) */
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


struct svga_modeinfo {
	__physaddr_t smi_lfb;                /* [valid_if(SVGA_MODEINFO_F_LFB)] Linear frame buffer base address (if available) */
	__uint32_t   smi_flags;              /* Mode flags (set of `SVGA_MODEINFO_F_*') */
	__uint32_t   smi_scanline;           /* [!0] Scanline size (in bytes; aligned by `sc_logicalwidth_align')
	                                      *      Usually is `>= CEIL_ALIGN(smi_resy, sc_logicalwidth_align)' */
	__uint16_t   smi_resx;               /* [!0] Resolution in X (when `SVGA_MODEINFO_F_TXT': # of character cells in X) */
	__uint16_t   smi_resy;               /* [!0] Resolution in Y (when `SVGA_MODEINFO_F_TXT': # of character cells in Y) */
	__shift_t    smi_bits_per_pixel;     /* [!0] Bits per pixel (when `SVGA_MODEINFO_F_TXT': 16) */
	__shift_t    smi_colorbits;          /* [!0][valid_if(!SVGA_MODEINFO_F_TXT)]
	                                      * # of bits per pixel that encode color (usually <= smi_bits_per_pixel, unless in
	                                      * `SVGA_MODEINFO_F_PLANAR').  Use  as  `NUM_PALETTE_COLORS = 1 << smi_colorbits'. */
	__shift_t    smi_rshift, smi_rbits;  /* [valid_if(!SVGA_MODEINFO_F_PAL && !SVGA_MODEINFO_F_BW)] Red color shift/bits */
	__shift_t    smi_gshift, smi_gbits;  /* [valid_if(!SVGA_MODEINFO_F_PAL && !SVGA_MODEINFO_F_BW)] Green color shift/bits */
	__shift_t    smi_bshift, smi_bbits;  /* [valid_if(!SVGA_MODEINFO_F_PAL && !SVGA_MODEINFO_F_BW)] Blue color shift/bits */
	/* Chipset-specific data (a total of `sco_modeinfosize - sizeof(struct svga_modeinfo)' bytes) goes here. */
};


struct svga_chipset;

/* Callback function for chipset string enumeration.
 * @param: name:  Spec string name.
 * @param: value: Spec string value.
 * @return: * :   pformatprinter-compatible return value. */
typedef __ATTR_NONNULL((2, 3)) __ssize_t
(LIBSVGA_CC *svga_chipset_enumstring_t)(void *arg,
                                        char const *__restrict name,
                                        char const *__restrict value);


struct svga_chipset_ops {

	/* [1..1][const] Chipset-specific finalization. */
	__NOBLOCK __ATTR_NONNULL((1)) void
	/*NOTHROW*/ (LIBSVGA_CC *sco_fini)(struct svga_chipset *__restrict self);

	/* [const][== sizeof(struct MYCHIPSET_svga_modeinfo)] */
	__size_t sco_modeinfosize;

	/* [0..1][const][lock(WRITE(sc_lock))]
	 * Enumerate chipset-specific identification strings. */
	__ATTR_NONNULL((1, 2)) __ssize_t
	(LIBSVGA_CC *sco_strings)(struct svga_chipset *__restrict self,
	                          svga_chipset_enumstring_t cb, void *arg);

	/* [1..1][const][lock(WRITE(sc_lock))]
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
	__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)) __BOOL
	(LIBSVGA_CC *sco_getmode)(struct svga_chipset *__restrict self,
	                          struct svga_modeinfo *__restrict result,
	                          __uintptr_t *__restrict p_index)
			__THROWS(E_IOERROR);

	/* [1..1][const][lock(WRITE(sc_lock))]
	 * - Set a given video `mode' and update `self->sc_mode' to match `mode'
	 * - The contents of `mode' have previously been retrieved via `sco_getmode'
	 * - Prior to this function being  called for the first  time,
	 *   `self->sc_mode.smi_bits_per_pixel' may be `0' to indicate
	 *   that the current video mode is unknown. */
	__ATTR_NONNULL((1, 2)) void
	(LIBSVGA_CC *sco_setmode)(struct svga_chipset *__restrict self,
	                          struct svga_modeinfo const *__restrict mode);

	/* [1..1][const][lock(WRITE(sc_lock))]
	 * - Save/load all chipset registers to/from a `sco_regsize'-long `regbuf'
	 * - These functions can be used  to save/restore the current video  mode
	 *   even before `sco_setmode' was called for the first time. They should
	 *   also  be used before  exclusive display control is  handed to a user
	 *   application, and after that application relinquishes control. */
	__ATTR_NONNULL((1, 2)) void
	(LIBSVGA_CC *sco_getregs)(struct svga_chipset *__restrict self, __byte_t regbuf[]);
	__ATTR_NONNULL((1, 2)) void
	(LIBSVGA_CC *sco_setregs)(struct svga_chipset *__restrict self, __byte_t const regbuf[]);

	/* [const] Required buffer size for `sco_getregs' / `sco_setregs'. */
	__size_t sco_regsize;

	/* NOTE: Operators below may be altered by chipset drivers during `sco_setmode()'
	 *       This should be fine since they can already only be called while  already
	 *       holding a lock to `sc_lock', which prevents one from changing the mode.
	 * Additionally, they may not actually be initialized prior to the first call to
	 * `sco_setmode()'. */

	/* [1..1][lock(WRITE(sc_lock))]
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
	 * @assume(!(self->sc_mode.smi_flags & SVGA_MODEINFO_F_LFB)); */
	__ATTR_NONNULL((1)) void
	(LIBSVGA_CC *sco_setwindow)(struct svga_chipset *__restrict self, __size_t window)
			__THROWS(E_IOERROR);
	/* [1..1][lock(WRITE(sc_lock))] Same as `sco_setwindow', but *may* only update `sc_rdwindow' */
	__ATTR_NONNULL((1)) void
	(LIBSVGA_CC *sco_setrdwindow)(struct svga_chipset *__restrict self, __size_t window)
			__THROWS(E_IOERROR);
	/* [1..1][lock(WRITE(sc_lock))] Same as `sco_setwindow', but *may* only update `sc_wrwindow' */
	__ATTR_NONNULL((1)) void
	(LIBSVGA_CC *sco_setwrwindow)(struct svga_chipset *__restrict self, __size_t window)
			__THROWS(E_IOERROR);

	/* [1..1][lock(WRITE(sc_lock))]
	 * - Set display start offset to `offset' pixels from `self->sc_mode.smi_vmembase'
	 * - Set `self->sc_displaystart = offset;'
	 * - Not available in text-mode video modes.
	 * @assume(WAS_CALLED(sco_setmode));
	 * @assume(self->sc_displaystart != offset);
	 * @assume(offset <= self->sc_vmemsize * 8 / self->sc_mode.smi_bits_per_pixel);
	 * @assume(!(self->sc_mode.smi_flags & SVGA_MODEINFO_F_TXT)); */
	__ATTR_NONNULL((1)) void
	(LIBSVGA_CC *sco_setdisplaystart)(struct svga_chipset *__restrict self, __size_t offset)
			__THROWS(E_IOERROR);

	/* [1..1][lock(WRITE(sc_lock))]
	 * - Set  logical screen width  to `offset' bytes and
	 *   write the new value into `self->sc_logicalwidth'
	 * - The  logical screen  width is  the #  of bytes the
	 *   video card  will add  to the  start of  a line  in
	 *   order to get the memory location of the next line.
	 * - The value must be aligned by `self->sc_logicalwidth_align'
	 * - The default value is `smi_scanline'
	 * - Not available in text-mode video modes.
	 * @assume(WAS_CALLED(sco_setmode));
	 * @assume(self->sc_logicalwidth != offset);
	 * @assume(IS_ALIGNED(offset, self->sc_logicalwidth_align));
	 * @assume(offset <= sc_logicalwidth_max);
	 * @assume(!(self->sc_mode.smi_flags & SVGA_MODEINFO_F_TXT)); */
	__ATTR_NONNULL((1)) void
	(LIBSVGA_CC *sco_setlogicalwidth)(struct svga_chipset *__restrict self, __uint32_t offset)
			__THROWS(E_IOERROR);
};

struct svga_chipset {
	struct svga_chipset_ops sc_ops;                /* [const] Chipset operators. */
	struct shared_rwlock    sc_lock;               /* Lock for this chipset. */
	__size_t                sc_vmemsize;           /* [const] Video memory size (in bytes; usually a multiple of 64K). */
	__size_t                sc_rdwindow;           /* [lock(sc_lock)][< CEILDIV(sc_vmemsize, 64 * 1024)][valid_if(sc_mode.smi_bits_per_pixel != 0)]
	                                                * Current display window for reads. */
	__size_t                sc_wrwindow;           /* [lock(sc_lock)][< CEILDIV(sc_vmemsize, 64 * 1024)][valid_if(sc_mode.smi_bits_per_pixel != 0)]
	                                                * Current display window for writes. */
	__size_t                sc_displaystart;       /* [lock(sc_lock)][valid_if(sc_mode.smi_bits_per_pixel != 0)]
	                                                * Current display start (pixels from  `sc_mode.smi_vmembase'
	                                                * to the beginning of the screen; usually top-left corner) */
	__uint32_t              sc_logicalwidth;       /* [lock(sc_lock)][valid_if(sc_mode.smi_bits_per_pixel != 0)]
	                                                * Current logical screen width (in bytes; updated by `sco_setlogicalwidth') */
	__uint32_t              sc_logicalwidth_max;   /* [lock(sc_lock)][valid_if(sc_mode.smi_bits_per_pixel != 0)]
	                                                * Max value allowed for `sc_logicalwidth' */
	__uint32_t              sc_logicalwidth_align; /* [lock(sc_lock)][valid_if(sc_mode.smi_bits_per_pixel != 0)]
	                                                * Alignment requirements of `sc_logicalwidth' */
	struct svga_modeinfo    sc_mode;               /* [lock(sc_lock)][valid_if(sc_mode.smi_bits_per_pixel != 0)]
	                                                * Current display mode */
	/* Chipset-specific data goes here. */
};

/* Helpers for accessing `struct svga_chipset::sc_lock' */
#define /*        */ _svga_chipset_reap(self)        (void)0
#define /*        */ svga_chipset_reap(self)         (void)0
#define /*        */ svga_chipset_mustreap(self)     0
#define /*BLOCKING*/ svga_chipset_write(self)        shared_rwlock_write(&(self)->sc_lock)
#define /*BLOCKING*/ svga_chipset_write_nx(self)     shared_rwlock_write_nx(&(self)->sc_lock)
#define /*        */ svga_chipset_trywrite(self)     shared_rwlock_trywrite(&(self)->sc_lock)
#define /*        */ svga_chipset_endwrite(self)     (shared_rwlock_endwrite(&(self)->sc_lock), svga_chipset_reap(self))
#define /*        */ _svga_chipset_endwrite(self)    shared_rwlock_endwrite(&(self)->sc_lock)
#define /*BLOCKING*/ svga_chipset_read(self)         shared_rwlock_read(&(self)->sc_lock)
#define /*BLOCKING*/ svga_chipset_read_nx(self)      shared_rwlock_read_nx(&(self)->sc_lock)
#define /*        */ svga_chipset_tryread(self)      shared_rwlock_tryread(&(self)->sc_lock)
#define /*        */ _svga_chipset_endread(self)     shared_rwlock_endread(&(self)->sc_lock)
#define /*        */ svga_chipset_endread(self)      (void)(shared_rwlock_endread(&(self)->sc_lock) && (svga_chipset_reap(self), 0))
#define /*        */ _svga_chipset_end(self)         shared_rwlock_end(&(self)->sc_lock)
#define /*        */ svga_chipset_end(self)          (void)(shared_rwlock_end(&(self)->sc_lock) && (svga_chipset_reap(self), 0))
#define /*BLOCKING*/ svga_chipset_upgrade(self)      shared_rwlock_upgrade(&(self)->sc_lock)
#define /*        */ svga_chipset_tryupgrade(self)   shared_rwlock_tryupgrade(&(self)->sc_lock)
#define /*        */ svga_chipset_downgrade(self)    shared_rwlock_downgrade(&(self)->sc_lock)
#define /*        */ svga_chipset_reading(self)      shared_rwlock_reading(&(self)->sc_lock)
#define /*        */ svga_chipset_writing(self)      shared_rwlock_writing(&(self)->sc_lock)
#define /*        */ svga_chipset_canread(self)      shared_rwlock_canread(&(self)->sc_lock)
#define /*        */ svga_chipset_canwrite(self)     shared_rwlock_canwrite(&(self)->sc_lock)
#define /*BLOCKING*/ svga_chipset_waitread(self)     shared_rwlock_waitread(&(self)->sc_lock)
#define /*BLOCKING*/ svga_chipset_waitwrite(self)    shared_rwlock_waitwrite(&(self)->sc_lock)
#define /*BLOCKING*/ svga_chipset_waitread_nx(self)  shared_rwlock_waitread_nx(&(self)->sc_lock)
#define /*BLOCKING*/ svga_chipset_waitwrite_nx(self) shared_rwlock_waitwrite_nx(&(self)->sc_lock)


struct svga_chipset_driver {
	__size_t scd_cssize; /* == sizeof(struct MYCHIPSET_svga_chipset) */

	/* [1..1] Probe for the presence of this chipset and initialize `self'
	 *        For this, `self' must point to a `scd_cssize'-byte long buffer.
	 * @return: true:  Chipset found.
	 * @return: false: Chipset isn't present. */
	__ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
	(LIBSVGA_CC *scd_probe)(struct svga_chipset *__restrict self);

	/* Chipset name. */
	char scd_name[16];
};



/* Return the list of supported VGA chipset drivers (terminated by a bzero'd entry)
 * This list is sorted from most specific- to most generic driver. As such, some of
 * the later drivers might also  be usable even when one  of the former ones  could
 * also be used.
 *
 * As such, when probing for devices you should simply iterate this list until you
 * find a driver  for which probing  succeeds. Once that  happens, simply keep  on
 * using that driver. */
typedef __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED struct svga_chipset_driver const *
/*__NOTHROW*/ (LIBSVGA_CC *PSVGA_CHIPSET_GETDRIVERS)(void);
#ifdef LIBSVGA_WANT_PROTOTYPES
LIBSVGA_DECL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED struct svga_chipset_driver const *
__NOTHROW(LIBSVGA_CC svga_chipset_getdrivers)(void);
#endif /* LIBSVGA_WANT_PROTOTYPES */


__DECL_END
#endif /* __CC__ */

#endif /* !_LIBSVGA_CHIPSET_H */