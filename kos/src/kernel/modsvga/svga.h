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
#ifndef GUARD_MODSVGA_SVGA_H
#define GUARD_MODSVGA_SVGA_H 1

#include <kernel/compiler.h>

#include <dev/ansitty.h>
#include <kernel/mman/mnode.h>
#include <kernel/refcountable.h>
#include <kernel/types.h>
#include <sched/async.h>

#include <hw/video/vga.h>
#include <kos/aref.h>

#include <libsvga/chipset.h>

/* Include internal headers from libsvga */
#include "../../libsvga/basevga.h"
#include "../../libsvga/chipset.h"

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

union svga_tty_cursor {
	uintptr_t          stc_word;  /* Cursor position word. */
	struct {
		uintptr_half_t stc_cellx; /* [< sta_resx] Current cell in X */
		uintptr_half_t stc_celly; /* [<= sta_resy] Current cell in Y
		                           * NOTE: May only be equal to `sta_resy' when
		                           *       `SVGA_TTYACCESS_F_EOL' is also  set! */
	};
};


/* Flags for `struct svga_ttyaccess::sta_flags' */
#define SVGA_TTYACCESS_F_NORMAL 0x0000 /* Normal flags */
#define SVGA_TTYACCESS_F_ACTIVE 0x0001 /* [lock(sta_lock && svd_chipset.sc_lock)]
                                        * This TTY is currently active.
                                        * When not set, `sta_vmem' may not be accessed. */
#define SVGA_TTYACCESS_F_EOL    0x8000 /* [lock(sta_lock)] Set while `sta_cursor.stc_cellx == 0' as
                                        * the result  of the  previously line  being wrapped.  This
                                        * flag is cleared the next time a character is printed, but
                                        * if said character is '\n', it is silently ignored. */
#define _SVGA_TTYACCESS_F_HWCUROFF 0x4000 /* For hardware text-mode ttys: cursor is currently off. */
#define _SVGA_TTYACCESS_F_SWCURON  0x4000 /* For graphics tty: the cursor is currently shown. */

/* SVGA tty accessor descriptor.
 * Used for encoding TTY display mode info and the like. */
struct svga_ttyaccess {
	WEAK refcnt_t               sta_refcnt; /* Reference counter. */
	struct atomic_lock          sta_lock;   /* Lock for character movements. */
	struct svga_modeinfo const *sta_mode;   /* [1..1][const] Associated SVGA mode. */
	struct mnode                sta_vmem;   /* [const] Video memory mapping. (prepared+mapped)
	                                         * May only be accessed when `SVGA_TTYACCESS_F_ACTIVE' is set! */
	union {
		struct {
			/* NOTE: Cell size in `x' is always 9 */
			/* NOTE: Cell size in `y' is always 16 */
			uintptr_t             sta_flags;         /* [lock(sta_lock)] Set of `SVGA_TTYACCESS_F_*' */
			uintptr_half_t        sta_resx;          /* [const] # of character cells in X */
			uintptr_half_t        sta_resy;          /* [const] # of character cells in Y */
			size_t                sta_scan;          /* [const] Scanline size (in characters cells) */
			uintptr_half_t        sta_scroll_ystart; /* [lock(sta_lock)][<= sta_scroll_yend && <= sta_resy] Start scroll line (usualy `0') */
			uintptr_half_t        sta_scroll_yend;   /* [lock(sta_lock)][>= sta_scroll_ystart && <= sta_resy] End scroll line (usualy `sta_resy') */
			union svga_tty_cursor sta_cursor;        /* [lock(sta_lock)] Current cursor position. */
			uintptr_half_t       _sta_scrl_ymax;     /* [lock(sta_lock)][== sta_scroll_yend - 1] */
			uintptr_t            _sta_scrl1_to;      /* [lock(sta_lock)][== sta_scroll_ystart * sta_resx] */
			uintptr_t            _sta_scrl1_from;    /* [lock(sta_lock)][== (sta_scroll_ystart + 1) * sta_resx] */
			uintptr_t            _sta_scrl1_cnt;     /* [lock(sta_lock)][== sta_resx * ((sta_scroll_yend - sta_scroll_ystart) - 1)] */
			uintptr_t            _sta_scrl1_fil;     /* [lock(sta_lock)][== (sta_scroll_yend - 1) * sta_scan] */
#define svga_ttyaccess__update_scrl(self)                                                                      \
	((self)->_sta_scrl_ymax  = (self)->sta_scroll_yend - 1,                                                    \
	 (self)->_sta_scrl1_to   = (self)->sta_scroll_ystart * (self)->sta_resx,                                   \
	 (self)->_sta_scrl1_from = ((self)->sta_scroll_ystart + 1) * (self)->sta_resx,                             \
	 (self)->_sta_scrl1_cnt  = (self)->sta_resx * (((self)->sta_scroll_yend - (self)->sta_scroll_ystart) - 1), \
	 (self)->_sta_scrl1_fil  = ((self)->sta_scroll_yend - 1) * (self)->sta_scan)
		};
		Toblockop(mman)     _sta_mmlop;  /* Used internally */
		Tobpostlockop(mman) _sta_mmplop; /* Used internally */
	};
	/* TODO: support for custom fonts! */
	/* Operators... */

	/* [1..1][lock(sta_lock)] Set the contents of a single cell. (attributes are taken from `tty->at_ansi')
	 * NOTE: This operator may assume that `address' is visible on-screen
	 * @param: address: == CELL_X + CELL_Y * sta_scan */
	NOBLOCK NONNULL((1, 2)) void
	/*NOTHROW*/ (FCALL *sta_setcell)(struct svga_ttyaccess *__restrict self,
	                                 struct svgatty *__restrict tty,
	                                 uintptr_t address, char32_t ch);

	/* [1..1][lock(sta_lock)] Hide the hardware cursor
	 * NOTE: This operator is only invoked when `SVGA_TTYACCESS_F_ACTIVE' is set. */
	NOBLOCK NONNULL((1)) void
	/*NOTHROW*/ (FCALL *sta_hidecursor)(struct svga_ttyaccess *__restrict self);

	/* [1..1][lock(sta_lock)] Show the hardware cursor at the current cursor position.
	 * NOTE: This operator is only called when `sta_cursor.stc_celly < sta_resy', which
	 *       compiled with the  invariant `sta_cursor.stc_cellx < sta_resx' means  that
	 *       the cursor is guarantied visible on-screen.
	 * NOTE: This operator is only invoked when `SVGA_TTYACCESS_F_ACTIVE' is set. */
	NOBLOCK NONNULL((1)) void
	/*NOTHROW*/ (FCALL *sta_showcursor)(struct svga_ttyaccess *__restrict self);

	/* [1..1][lock(sta_lock)] Copy cells across video memory.
	 * NOTE: The cell addresses taken by this function do _NOT_ account for large scanlines!
	 * @param: from_cellid/to_cellid: == CELL_X + CELL_Y * sta_resx */
	NOBLOCK NONNULL((1)) void
	/*NOTHROW*/ (FCALL *sta_copycell)(struct svga_ttyaccess *__restrict self,
	                                  uintptr_t to_cellid, uintptr_t from_cellid,
	                                  size_t num_cells);

	/* [1..1][lock(sta_lock)] Same as:
	 * >> while (num_cells--) (*sta_setcell)(self, tty, start++, ch); */
	NOBLOCK NONNULL((1, 2)) void
	/*NOTHROW*/ (FCALL *sta_fillcells)(struct svga_ttyaccess *__restrict self,
	                                   struct svgatty *__restrict tty,
	                                   uintptr_t start, char32_t ch, size_t num_cells);

	/* [1..1][lock(sta_lock)] Do additional stuff needed after to activate this tty.
	 * This includes loading the tty's font into the video card and doing an initial
	 * full redraw of the entire screen.
	 * NOTE: This operator is only invoked when `SVGA_TTYACCESS_F_ACTIVE' is set. */
	NOBLOCK NONNULL((1)) void
	/*NOTHROW*/ (FCALL *sta_activate)(struct svga_ttyaccess *__restrict self);
};


INTDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_destroy)(struct svga_ttyaccess *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct svga_ttyaccess, sta_refcnt, svga_ttyaccess_destroy);


/* TEXT tty sub-class. */
struct svga_ttyaccess_txt: svga_ttyaccess {
	COMPILER_FLEXIBLE_ARRAY(uint16_t, stt_display);   /* [sta_scan * sta_resy][lock(sta_lock)] Display contents. */
};
#define svga_ttyaccess_txt_vmem(self) ((uint16_t *)mnode_getaddr(&(self)->sta_vmem))
#define svga_ttyaccess_txt_dmem(self) ((self)->stt_display)


/* GFX tty sub-class. */
struct svga_gfxcell {
	uint8_t sgc_lines[16]; /* Bitmasks to select fg/bg colors for each pixel. */
	uint8_t sgc_color;     /* fg/bg color for this color. */
};
struct svga_ttyaccess_gfx: svga_ttyaccess {
	/* [1..1][lock(sta_lock)] Redraw the cell at `address' (index into `stx_display')
	 * NOTE: This operator is only invoked when `SVGA_TTYACCESS_F_ACTIVE' is set. */
	NOBLOCK NONNULL((1)) void
	/*NOTHROW*/ (FCALL *stx_redraw_cell)(struct svga_ttyaccess_gfx *__restrict self,
	                                     uintptr_t address);
	/* [1..1][lock(sta_lock)] Draw a cursor at `stx_swcur'
	 * NOTE: This operator is only invoked when `SVGA_TTYACCESS_F_ACTIVE' is set. */
	NOBLOCK NONNULL((1)) void
	/*NOTHROW*/ (FCALL *stx_redraw_cursor)(struct svga_ttyaccess *__restrict self);
	uint32_t                                     stx_ccolor;     /* [lock(sta_lock)] Cursor color. */
	union svga_tty_cursor                        stx_swcur;      /* [valid_if(_SVGA_TTYACCESS_F_SWCURON)][lock(sta_lock)]
	                                                              * Current software cursor position. */
	uint32_t                                     stx_colors[16]; /* [const] Pre-calculated palette colors. */
	size_t                                       stx_cellscan;   /* [const][== 16 * mode->smi_scanline] */
	COMPILER_FLEXIBLE_ARRAY(struct svga_gfxcell, stx_display);   /* [sta_resx * sta_resy][lock(sta_lock)] Display contents. */
};



ARREF(svga_ttyaccess_arref, svga_ttyaccess);


/* SVGA tty instance */
struct svgatty: ansittydev {
	REF struct svgadev         *sty_dev;    /* [1..1][const] SVGA device. */
	REF struct svgatty         *sty_oldtty; /* [0..1][const_if(wasdestroyed(self))]
	                                         * [lock(slc_dev->svd_chipset.sc_lock)]
	                                         * TTY that is made active when this tty is destroyed. */
	unsigned int                sty_active; /* [lock(sty_dev->svd_chipset.sc_lock)]
	                                         * [const_if(wasdestroyed(self))]
	                                         * Non-zero if this tty is currently active. */
	struct svga_ttyaccess_arref sty_tty;    /* [1..1][lock(WRITE(sty_dev->svd_chipset.sc_lock))]
	                                         * Only the pointed-to may have the `SVGA_TTYACCESS_F_ACTIVE'
	                                         * flag set. When you with to set a new tty access object (as
	                                         * the result of a mode-change  request), you must clear  the
	                                         * `SVGA_TTYACCESS_F_ACTIVE' flag (if it is set).
	                                         *
	                                         * Also  note that `SVGA_TTYACCESS_F_ACTIVE' can only ever
	                                         * be set when `sty_active'. As such, changing the current
	                                         * foreground TTY of an SVGA controller also requires that
	                                         * one create a new tty-access object for the new tty, and
	                                         * clear the  `SVGA_TTYACCESS_F_ACTIVE' flag  for the  old
	                                         * tty's access object. */
};
#define ansitty_assvga(self)    container_of(self, struct svgatty, at_ansi)
#define ansitty_getaccess(self) arref_get(&ansitty_assvga(self)->sty_tty)

/* Safely update the tty pointed-to by `self->sty_tty' */
INTDEF BLOCKING NOCONNECT NONNULL((1, 2)) void FCALL
svgatty_settty(struct svgatty *__restrict self,
               struct svga_ttyaccess *__restrict tty);


/* Async job  started to  revert  to the  old  display
 * mode when this TTY is destroyed while `sty_active'. */
#define _svgatty_toasyncrestore(self) \
	((struct async *)&(self)->at_ansi)
#define _svgatty_fromasyncrestore(self) \
	container_of((struct ansitty *)__COMPILER_REQTYPE(struct async *, self), struct svgatty, at_ansi)
STATIC_ASSERT(sizeof(struct async) <= sizeof(struct ansitty));



struct svgalck: mfile {
	REF struct svgadev             *slc_dev;    /* [1..1][const] SVGA device. */
	REF struct svgatty             *slc_oldtty; /* [0..1][lock(slc_dev->svd_chipset.sc_lock)] TTY that is made active when this tty is destroyed. */
	struct svga_modeinfo const     *slc_mode;   /* [0..1][lock(slc_dev->svd_chipset.sc_lock)] Current video mode (for `SVGA_IOC_GETMODE' / `SVGA_IOC_SETMODE') */
	struct async                    slc_rstor;  /* A pre-allocated async controller used to release the lock. */
	struct vga_mode                 slc_vmode;  /* [lock(slc_dev->svd_chipset.sc_lock)] Standard VGA registers to restore upon release. */
	COMPILER_FLEXIBLE_ARRAY(byte_t, slc_xregs); /* [lock(slc_dev->svd_chipset.sc_lock)][0..slc_dev->svd_chipset.sco_regsize]
	                                             * Extended registers (restored with `sul_screen.sty_dev->svd_chipset.sco_setregs') */
};


#ifndef __mfile_awref_defined
#define __mfile_awref_defined
AWREF(mfile_awref, mfile);
#endif /* !__mfile_awref_defined */

struct svgadev: chrdev {
	struct mfile_awref                svd_active;   /* [0..1][lock(WRITE(svd_chipset.sc_lock))] Active TTY or  user-lock.
	                                                 * When this points to a dead file, that file _must_ clean up itself! */
	byte_t const                     *svd_supmodev; /* [0..n][const][owned] Array of supported video modes. */
	size_t                            svd_supmodec; /* [!0][const] # of supported video modes. */
	size_t                            svd_supmodeS; /* [const] Aligned sizeof() supported video modes. */
	struct svga_modeinfo const       *svd_defmode;  /* [1..1][lock(ATOMIC)] Default video mode. (points into `svd_supmodev') */
	struct svga_chipset_driver const *svd_csdriver; /* [1..1][const] SVGA driver. */
	struct svga_chipset               svd_chipset;  /* SVGA Chipset driver. */
};

INTDEF struct ansitty_operators const svga_ansitty_ops; /* ANSI TTY operators. */
INTDEF struct ansittydev_ops const svgatty_ops;         /* Operators for `struct svgatty' */
INTDEF struct mfile_ops const svgalck_ops;              /* Operators for `struct svgalck' */
INTDEF struct chrdev_ops const svgadev_ops;             /* Operators for `struct svgadev' */

/* Check the object pointed to by `svd_active' is a userlock or a TTY */
#define svga_active_istty(self)  ((self)->mf_ops == &svgatty_ops.ato_cdev.cdo_dev.do_node.dno_node.no_file)
#define svga_active_islock(self) ((self)->mf_ops != &svgatty_ops.ato_cdev.cdo_dev.do_node.dno_node.no_file)

/* Return a `struct svga_modeinfo const *' for the i'th supported video mode if `self' */
#define svgadev_supmode(self, i) \
	((struct svga_modeinfo const *)((self)->svd_supmodev + ((i) * (self)->svd_supmodeS)))


/* Return a reference to the currently "active" tty (or the one that will become
 * active after a currently held user-lock is released). If no such TTY  exists,
 * return NULL instead. */
INTDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) REF struct svgatty *FCALL
svgadev_getactivetty(struct svgadev *__restrict self);

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

/* Activate a given TTY. If an active userlock exists, the tty will not actually
 * be  made active, but will instead be  linked such that the userlock's release
 * will make the tty active. */
INTDEF BLOCKING NONNULL((1, 2)) void FCALL
svgadev_activate_tty(struct svgadev *__restrict self,
                     struct svgatty *__restrict tty)
		THROWS(E_WOULDBLOCK);

/* Allocate  and activate a new userlock for a given SVGA device.
 * If another lock already exists, this function will block until
 * said lock is released. */
INTDEF BLOCKING NOCONNECT ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct svgalck *FCALL
svgadev_newuserlock(struct svgadev *__restrict self)
		THROWS(E_WOULDBLOCK);





/************************************************************************/
/* Default font data                                                    */
/************************************************************************/

/* Default text-mode palette colors for KOS (these are set-up for ANSI TTY compatibility) */
INTDEF struct vga_palcolor const basevga_defaultpal[16];

/* Default text-mode font for KOS. */
INTDEF byte_t const basevga_defaultfont[256][32];

/* Return the font-map index (iow: the value that should be written
 * to plane#0) in order to represent a given UTF-32 character `ch'. */
INTDEF ATTR_CONST byte_t
NOTHROW(FCALL basevga_defaultfont_encode)(char32_t ch);

DECL_END

#endif /* !GUARD_MODSVGA_SVGA_H */
