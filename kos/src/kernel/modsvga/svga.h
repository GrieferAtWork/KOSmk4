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
#ifndef GUARD_MODSVGA_SVGA_H
#define GUARD_MODSVGA_SVGA_H 1

#include <kernel/compiler.h>

#include <dev/video.h>
#include <kernel/mman/mnode.h>
#include <kernel/refcountable.h>
#include <kernel/types.h>
#include <sched/async.h>

#include <hw/video/vga.h>
#include <kos/aref.h>
#include <kos/sched/shared-lock.h>

#include <libsvgadrv/chipset.h>

/* Include internal headers from `libsvgadrv' */
#include "../../libsvgadrv/basevga.h"
#include "../../libsvgadrv/chipset.h"

DECL_BEGIN

/*
 * The SVGA video driver serves the following functions:
 * - Implement an ANSI tty, preferably via high-resolution graphics
 *   If  high-resolution graphics aren't available, use normal text
 *   mode. (This is done during init)
 * - The ability for user-space to query and set video modes
 *   supported  by the associated chipset. When changing the
 *   video mode, the ANSI tty is simply resized.
 * - The ability for user-space to disable the TTY aspect, as well
 *   as to gain full control of VGA hardware.
 *   - When entering this mode, all VGA registers and all VGA memory
 *     that is relevant to eventually  restoring the old video  mode
 *     and the screen's contents are saved.
 *   - Userspace  is given a symbolic handle to an object that must
 *     be kept alive for as  long as user-space wishes to  maintain
 *     their exclusive hardware access  lock. Only one such  object
 *     can be handed out at a time, and trying to acquire more than
 *     one lock will block until the first is released.
 *   - Once this exclusive lock-object is destroyed (close(2)),
 *     then the saved register state is restored, including any
 *     and all video mode transitions.
 *
 */


struct svgadev;
struct svgatty;

/* Extension flags for `struct vidttyaccess::vta_flags' */
#define _SVGA_TTYACCESS_F_HWCUROFF 0x4000 /* For hardware text-mode ttys: cursor is currently off. */
#define _SVGA_TTYACCESS_F_SWCURON  0x4000 /* For graphics tty: the cursor is currently shown. */

/* SVGA tty accessor descriptor.
 * Used for encoding TTY display mode info and the like. */
struct svga_ttyaccess: vidttyaccess {
	struct svga_modeinfo const *sta_mode; /* [1..1][const] Associated SVGA mode. */
	struct mnode                sta_vmem; /* [const] Video memory mapping.  (prepared+mapped)
	                                       * Only access when `VIDTTYACCESS_F_ACTIVE' is set! */
};

INTDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_destroy)(struct vidttyaccess *__restrict self);
DEFINE_REFCNT_FUNCTIONS(struct svga_ttyaccess, vta_refcnt, svga_ttyaccess_destroy);

/* Check if a given `struct vidttyaccess' is actually `struct svga_ttyaccess' */
#define vidttyaccess_issvga(self)     ((self)->vta_destroy == &svga_ttyaccess_destroy)
#define vidttyaccess_assvga(self)     ((struct svga_ttyaccess *)(self))
#define vidttyaccess_assvga_txt(self) ((struct svga_ttyaccess_txt *)(self))
#define vidttyaccess_assvga_gfx(self) ((struct svga_ttyaccess_gfx *)(self))
#define svga_ttyaccess_astxt(self)    ((struct svga_ttyaccess_txt *)(self))
#define svga_ttyaccess_asgfx(self)    ((struct svga_ttyaccess_gfx *)(self))

/* Check what kind of tty sub-class you're dealing with. */
#define svga_ttyaccess_istxt(self) ((self)->vta_setcell == &svga_ttyaccess_v_setcell_txt)
#define svga_ttyaccess_isgfx(self) ((self)->vta_setcell != &svga_ttyaccess_v_setcell_txt)
INTDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL svga_ttyaccess_v_setcell_txt)(struct vidttyaccess *__restrict self,
                                            struct ansitty *__restrict tty,
                                            uintptr_t address, char32_t ch);


/* TEXT tty sub-class. */
struct svga_ttyaccess_txt: svga_ttyaccess {
	port_t                            stt_crt_icX;  /* [lock(vta_lock)] Either `VGA_CRT_IC' or `VGA_CRT_IM' */
	COMPILER_FLEXIBLE_ARRAY(uint16_t, stt_display); /* [vta_scan * vta_resy][lock(vta_lock)] Display contents. */
};
#define svga_ttyaccess_txt_vmem(self) ((uint16_t *)mnode_getaddr(&(self)->sta_vmem))
#define svga_ttyaccess_txt_dmem(self) ((self)->stt_display)

/* GFX tty sub-class. */
struct svga_gfxcell {
	uint8_t sgc_lines[16]; /* Bitmasks to select fg/bg colors for each pixel. */
	uint8_t sgc_color;     /* fg/bg color for this cell. */
};
struct svga_ttyaccess_gfx: svga_ttyaccess {
	/* [1..1][lock(vta_lock)] Redraw the cell at `address' (index into `stx_display')
	 * NOTE: This operator is only invoked when `VIDTTYACCESS_F_ACTIVE' is set. */
	NOBLOCK NONNULL_T((1)) void
	NOTHROW_T(FCALL *stx_redraw_cell)(struct svga_ttyaccess_gfx *__restrict self,
	                                  uintptr_t address);
	/* [1..1][lock(vta_lock)] Draw a cursor at `stx_swcur'
	 * NOTE: This operator is only invoked when `VIDTTYACCESS_F_ACTIVE' is set. */
	NOBLOCK NONNULL_T((1)) void
	NOTHROW_T(FCALL *stx_redraw_cursor)(struct svga_ttyaccess_gfx *__restrict self);
	uint32_t                                     stx_ccolor;     /* [lock(vta_lock)] Cursor color. */
	union vidtty_cursor                          stx_swcur;      /* [valid_if(_SVGA_TTYACCESS_F_SWCURON)][lock(vta_lock)]
	                                                              * Current software cursor position. */
	uint32_t                                     stx_colors[16]; /* [const] Pre-calculated palette colors. */
	size_t                                       stx_cellscan;   /* [const][== 16 * sta_mode->smi_scanline] */
	uint32_t                                     stx_scanline;   /* [const][== sta_mode->smi_scanline] */
	COMPILER_FLEXIBLE_ARRAY(struct svga_gfxcell, stx_display);   /* [vta_resx * vta_resy][lock(vta_lock)] Display contents. */
};


/* SVGA tty instance */
struct svgatty: vidtty { };
#define vidtty_assvga(self)       ((struct svgatty *)(self))
#define ansittydev_assvgatty(self) vidtty_assvga(ansittydev_asvidtty(self))
#define chrdev_assvgatty(self)     vidtty_assvga(chrdev_asansitty(self))
#define device_assvgatty(self)     vidtty_assvga(device_asansitty(self))
#define devnode_assvgatty(self)    vidtty_assvga(devnode_asansitty(self))
#define fnode_assvgatty(self)      vidtty_assvga(fnode_asansitty(self))
#define mfile_assvgatty(self)      vidtty_assvga(mfile_asansitty(self))




struct svgalck: vidlck {
	struct svga_modeinfo const     *slc_mode;   /* [0..1][lock(vlc_dev->vd_lock)] Current video mode (for `SVGA_IOC_GETMODE' / `SVGA_IOC_SETMODE') */
	struct vga_regs                 slc_vregs;  /* [lock(vlc_dev->vd_lock)] Standard VGA registers to restore upon release. */
	COMPILER_FLEXIBLE_ARRAY(byte_t, slc_xregs); /* [lock(vlc_dev->vd_lock)][0..vlc_dev->svd_chipset.sco_regsize]
	                                             * Extended registers (restored with `sul_screen.sty_dev->svd_chipset.sco_setregs') */
};
#define vidlck_assvga(self)   ((struct svgalck *)(self))
#define mfile_assvgalck(self) vidlck_assvga(mfile_asvidlck(self))

#ifdef CONFIG_HAVE_DEBUGGER
/* Register-save structure for the builtin debugger. */
struct svga_dbgregs {
	bool                            sdr_hasxregs; /* Set to true if `sdr_xdata' contains chipset registers. */
	struct vga_regs                 sdr_vmode;    /* Saved standard VGA registers. */
	COMPILER_FLEXIBLE_ARRAY(byte_t, sdr_xdata);   /* Chipset register buffer + clobbered video-memory buffer (in that order) */
};
#endif /* CONFIG_HAVE_DEBUGGER */

struct svgadev: viddev {
#ifdef CONFIG_HAVE_DEBUGGER
	REF struct svga_ttyaccess        *svd_dbgtty;   /* [1..1][const] TTY accessor for the builtin debugger. */
	struct svga_dbgregs              *svd_dbgsav;   /* [1..1][const] Saved VGA registers while within the builtin debugger. */
#endif /* CONFIG_HAVE_DEBUGGER */
	byte_t const                     *svd_supmodev; /* [0..n][const][owned] Array of supported video modes. */
	size_t                            svd_supmodec; /* [!0][const] # of supported video modes. */
	size_t                            svd_supmodeS; /* [const] Aligned sizeof() supported video modes. */
	struct svga_modeinfo const       *svd_defmode;  /* [1..1][lock(ATOMIC)] Default video mode. (points into `svd_supmodev') */
	struct svga_chipset_driver const *svd_csdriver; /* [1..1][const] SVGA driver. */
	struct svga_chipset               svd_chipset;  /* SVGA Chipset driver. */
};
#define viddev_assvga(self)     ((struct svgadev *)(self))
#define chrdev_assvgadev(self)  viddev_assvga(chrdev_asviddev(self))
#define device_assvgadev(self)  viddev_assvga(device_asviddev(self))
#define devnode_assvgadev(self) viddev_assvga(devnode_asviddev(self))
#define fnode_assvgadev(self)   viddev_assvga(fnode_asviddev(self))
#define mfile_assvgadev(self)   viddev_assvga(mfile_asviddev(self))

INTDEF struct vidtty_ops const svgatty_ops; /* Operators for `struct svgatty' */
INTDEF struct vidlck_ops const svgalck_ops; /* Operators for `struct svgalck' */
INTDEF struct viddev_ops const svgadev_ops; /* Operators for `struct svgadev' */

/* Check the object pointed to by `vd_active' is a lock or a TTY */
#define svga_active_islck(self) ((self)->mf_ops == &svgalck_ops.vlo_file)
#define svga_active_istty(self) ((self)->mf_ops != &svgalck_ops.vlo_file)

/* Return a `struct svga_modeinfo const *' for the i'th supported video mode if `self' */
#define svgadev_supmode(self, i) \
	((struct svga_modeinfo const *)((self)->svd_supmodev + ((i) * (self)->svd_supmodeS)))


/* Create a TTY access object for the given `mode' */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) REF struct svga_ttyaccess *FCALL
svgadev_makettyaccess(struct svgadev *__restrict self,
                      struct svga_modeinfo const *__restrict mode);

/* Set the SVGA video mode to `mode' */
INTDEF NONNULL((1, 2)) void FCALL
svgadev_setmode(struct svgadev *__restrict self,
                struct svga_modeinfo const *__restrict mode)
		THROWS(E_IOERROR);


/* Create a new  tty for a  given SVGA  device.
 * Note that the tty has yet to be made active! */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) REF struct svgatty *FCALL
svgadev_vnewttyf(struct svgadev *__restrict self,
                 struct svga_modeinfo const *__restrict mode, dev_t devno,
                 char const *__restrict format, __builtin_va_list args)
		THROWS(E_WOULDBLOCK);
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) REF struct svgatty *VCALL
svgadev_newttyf(struct svgadev *__restrict self,
                struct svga_modeinfo const *__restrict mode, dev_t devno,
                char const *__restrict format, ...)
		THROWS(E_WOULDBLOCK);


#ifdef CONFIG_HAVE_DEBUGGER
/* SVGA device debugger integration. */
INTDEF FREE NONNULL((1)) void FCALL svgadev_dbg_init(struct svgadev *__restrict self);
INTDEF NONNULL((1)) void NOTHROW(FCALL svgadev_dbg_fini)(struct svgadev *__restrict self);
#endif /* CONFIG_HAVE_DEBUGGER */



/************************************************************************/
/* Default font data                                                    */
/************************************************************************/

/* Default text-mode palette colors for KOS (these are set-up for ANSI TTY compatibility) */
INTDEF struct vga_palcolor const basevga_defaultpal[16];

/* Monochrome emulation palette. */
INTDEF struct vga_palcolor const basevga_monopal[16];

/* Default text-mode font for KOS. */
INTDEF byte_t const basevga_defaultfont[256][32];

/* Map from `VGA_SR03_CSET_*' to the actual offset within plane #2. */
INTDEF uint16_t const basevga_fontoffset[8];

/* Return the font-map index (iow: the value that should be written
 * to plane#0) in order to represent a given UTF-32 character `ch'. */
INTDEF ATTR_CONST byte_t
NOTHROW(FCALL basevga_defaultfont_encode)(char32_t ch);

DECL_END

#endif /* !GUARD_MODSVGA_SVGA_H */
