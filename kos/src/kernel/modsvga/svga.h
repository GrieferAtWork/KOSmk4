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
 * ```
 *  svga_device  ==>  svga_ansitty  ==>  svga_screendata
 *   |                 ^                   ^
 *   |                 |                   |
 *   |           +-----+                   |
 *   v           |                         |
 *  svd_active --+--> svga_userlock =======/
 * ```
 *
 */


struct svga_device;
struct svga_ansitty;

/* Screen data - common context structure for user-locks and TTYs.
 * For both,  the  `fn_fsdata'  field points  to  this  structure! */
struct svga_screendata {
	REF struct svga_device *ssd_dev;    /* [1..1][const][ref_if(:self != ssd_dev)] SVGA device. */
	unsigned int            ssd_active; /* [const_if(svga_active_islock(:self))]
	                                     * [lock(ssd_dev->svd_chipset.sc_lock)]
	                                     * Non-zero if this screen is active. */
	REF struct async       *ssd_deact;  /* [1..1][const][valid_if(:self != ssd_dev)]
	                                     * Async job that can be used (once) to deactivate this
	                                     * screen in response  to the  screen being  destroyed.
	                                     *
	                                     * When `ssd_active' at the time of the
	                                     */
};


struct svga_userlock: chrdev {
	struct svga_screendata          sul_screen; /* Screen data. */
	REF struct svga_ansitty        *sul_oldtty; /* [1..1][const] TTY that is made active when this userlock is released. */
	struct vga_mode                 sul_vmode;  /* [const] Standard VGA registers to restore upon release. */
	COMPILER_FLEXIBLE_ARRAY(byte_t, sul_xregs); /* [const][0..sul_screen.ssd_dev->svd_chipset.sco_regsize]
	                                             * Extended registers (restored with `sul_screen.ssd_dev->
	                                             * svd_chipset.sco_setregs') */
};



/* SVGA tty accessor descriptor.
 * Used for encoding TTY display mode info and the like.
 *
 * NOTES:
 *  - It is assumed that  this object is never  destroyed
 *    for as long as the associated `struct svga_ansitty'
 *    is still alive.
 *  - Don't expose this object to user-space
 */
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
#define SVGA_TTYACCESS_F_ACTIVE 0x0001 /* [lock(sta_lock && CLEAR_ONCE)] This TTY is currently active.
                                        * When not set, `sta_vmem'  points to anonymous physical  ram. */
#define SVGA_TTYACCESS_F_EOL    0x8000 /* [lock(sta_lock)] Set while `sta_cursor.stc_cellx == 0' as
                                        * the result  of the  previously line  being wrapped.  This
                                        * flag is cleared the next time a character is printed, but
                                        * if said character is '\n', it is silently ignored. */
#define _SVGA_TTYACCESS_F_HWCUROFF 0x4000 /* For hardware text-mode ttys: cursor is currently off. */
#define _SVGA_TTYACCESS_F_SWCURON  0x4000 /* For graphics tty: the cursor is currently shown. */

struct svga_ttyaccess {
	WEAK refcnt_t               sta_refcnt; /* Reference counter. */
	struct atomic_lock          sta_lock;   /* Lock for character movements. */
	struct svga_modeinfo const *sta_mode;   /* [1..1][const] Associated SVGA mode. */
	struct mnode                sta_vmem;   /* [const] Video memory mapping. (prepared+mapped)
	                                         * When `SVGA_TTYACCESS_F_ACTIVE' is cleared, then
	                                         * the pointed-to physical  memory must be  free'd
	                                         * during destruction of the access object. */
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
	                                 struct svga_ansitty *__restrict tty,
	                                 uintptr_t address, char32_t ch);

	/* [1..1][lock(sta_lock)] Hide the hardware cursor */
	NOBLOCK NONNULL((1)) void
	/*NOTHROW*/ (FCALL *sta_hidecursor)(struct svga_ttyaccess *__restrict self);

	/* [1..1][lock(sta_lock)] Show the hardware cursor at the current cursor position.
	 * NOTE: This operator is only called when `sta_cursor.stc_celly < sta_resy', which
	 *       compiled with the  invariant `sta_cursor.stc_cellx < sta_resx' means  that
	 *       the cursor is guarantied visible on-screen. */
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
	                                   struct svga_ansitty *__restrict tty,
	                                   uintptr_t start, char32_t ch, size_t num_cells);

	/* [1..1][lock(sta_lock)] Redraw the entire screen (called when this TTY is reactivated) */
	NOBLOCK NONNULL((1)) void
	/*NOTHROW*/ (FCALL *sta_redraw)(struct svga_ttyaccess *__restrict self);

};

INTDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svga_ttyaccess_destroy)(struct svga_ttyaccess *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct svga_ttyaccess, sta_refcnt, svga_ttyaccess_destroy);

struct svga_ttyaccess_txt: svga_ttyaccess {
	COMPILER_FLEXIBLE_ARRAY(uint16_t, stt_display);   /* [sta_scan * sta_resy][lock(sta_lock)] Display contents. */
};
#define svga_ttyaccess_txt_vmem(self) ((uint16_t *)mnode_getaddr(&(self)->sta_vmem))
#define svga_ttyaccess_txt_dmem(self) ((self)->stt_display)

#define svga_ttyaccess_txt_setcell(self, addr, word) \
	(svga_ttyaccess_txt_vmem(self)[addr] =           \
	 svga_ttyaccess_txt_dmem(self)[addr] = (word))
#define svga_ttyaccess_txt_fillcell(self, addr, word, count)     \
	(memsetw(&svga_ttyaccess_txt_dmem(self)[addr], word, count), \
	 memsetw(&svga_ttyaccess_txt_vmem(self)[addr], word, count))


/* GFX tty sub-class. */
struct svga_gfxcell {
	uint8_t sgc_lines[16]; /* Bitmasks to select fg/bg colors for each pixel. */
	uint8_t sgc_color;     /* fg/bg color for this color. */
};

struct svga_ttyaccess_gfx: svga_ttyaccess {
	/* [1..1][lock(sta_lock)] Redraw the cell at `address' (index into `stx_display') */
	NOBLOCK NONNULL((1)) void
	/*NOTHROW*/ (FCALL *stx_redraw_cell)(struct svga_ttyaccess_gfx *__restrict self,
	                                     uintptr_t address);
	/* [1..1][lock(sta_lock)] Draw a cursor at `stx_swcur' */
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
struct svga_ansitty: ansittydev {
	struct svga_screendata      sva_screen; /* Screen data. */
	struct svga_ttyaccess_arref sva_tty;    /* [1..1][lock(ATOMIC)] TTY I/O access.
	                                         * Only the pointed-to may have the `SVGA_TTYACCESS_F_ACTIVE'
	                                         * flag set. When you with to set a new tty access object (as
	                                         * the result of a mode-change  request), you must clear  the
	                                         * `SVGA_TTYACCESS_F_ACTIVE' flag (if it is set).
	                                         *
	                                         * Also  note that `SVGA_TTYACCESS_F_ACTIVE' can only ever be
	                                         * set when  `sva_screen.ssd_active'. As  such, changing  the
	                                         * current foreground TTY of an SVGA controller also requires
	                                         * that one create a new  tty-access object for the new  tty,
	                                         * and  clear the `SVGA_TTYACCESS_F_ACTIVE'  flag for the old
	                                         * tty's access object. */
};

/* Check the object pointed to by `svd_active' is a userlock or a TTY */
#define svga_active_islock(self) 0 /* TODO (use operator pointers) */
#define svga_active_istty(self)  1 /* TODO (use operator pointers) */


AWREF(chrdev_awref, chrdev);
struct svga_device: svga_ansitty {
	struct chrdev_awref               svd_active;   /* [1..1][lock(WRITE(svd_chipset.sc_lock))] Active TTY or user-lock. */
	byte_t const                     *svd_supmodev; /* [0..n][const][owned] Array of supported video modes. */
	size_t                            svd_supmodec; /* [const] # of supported video modes. */
	size_t                            svd_supmodeS; /* [const] Aligned sizeof() supported video modes. */
	struct svga_chipset_driver const *svd_csdriver; /* [1..1][const] SVGA driver. */
	struct svga_chipset               svd_chipset;  /* SVGA Chipset driver. */
};

/* Return a `struct svga_modeinfo const *' for the i'th supported video mode if `self' */
#define svga_device_supmode(self, i) \
	((struct svga_modeinfo const *)((self)->svd_supmodev + ((i) * (self)->svd_supmodeS)))





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
