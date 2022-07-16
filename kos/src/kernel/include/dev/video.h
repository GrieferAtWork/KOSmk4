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
#ifndef GUARD_KERNEL_INCLUDE_DEV_VIDEO_H
#define GUARD_KERNEL_INCLUDE_DEV_VIDEO_H 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <dev/ansitty.h>
#include <kernel/fs/chrdev.h>
#include <sched/async.h>

#include <hybrid/__minmax.h>

#include <kos/aref.h>
#include <kos/sched/shared-lock.h>

/*
 * Contrary to the name, the kernel video abstraction system itself doesn't
 * actually  expose any means of doing video mode switching or facilitating
 * direct video memory  access. Such  mechanisms must be  provided by  sub-
 * classes!
 *
 * Instead, the abstract video system  only defines the means to  creating
 * video terminals (~ala CTRL+ALT+[F1-F12]), as well as video locks, which
 * prevent the kernel from accessing video memory or video hardware.
 *
 * Additionally, operators are defined for implementing ANSI ttys, as well
 * as for the kernel's builtin debugger to take control of the screen  for
 * the purpose of displaying its commandline.
 *
 */

#ifdef __CC__
DECL_BEGIN

struct vidttyaccess;
struct vidtty;
struct vidlck;
struct viddev;


/************************************************************************/
/* VIDEO TTY ACCESSOR                                                   */
/************************************************************************/

union vidtty_cursor {
	uintptr_t          vtc_word;  /* Cursor position word. */
	struct {
		uintptr_half_t vtc_cellx; /* [< :vta_resx] Current cell in X */
		uintptr_half_t vtc_celly; /* [<= :vta_resy] Current cell in Y
		                           * NOTE: May only  be  equal  to  `:vta_resy'
		                           *       if `VIDTTYACCESS_F_EOL' is also set! */
	};
};

/* Flags for `struct vidttyaccess::vta_flags' */
#define VIDTTYACCESS_F_NORMAL 0x0000 /* Normal flags */
#define VIDTTYACCESS_F_ACTIVE 0x0001 /* [lock(vta_lock && vd_lock)]
                                      * This TTY  is currently  active.  When not  set,  video
                                      * hardware  must not be  accessed, and tty modifications
                                      * must be made to internal buffers that only get applied
                                      * when `vta_activate()' gets called. */
#define VIDTTYACCESS_F_EOL    0x0002 /* [lock(vta_lock)] Set while `vta_cursor.vtc_cellx == 0' as
                                      * the result  of the  previously line  being wrapped.  This
                                      * flag is cleared the next time a character is printed, but
                                      * if said character is '\n', it is silently ignored. */
/*      VIDTTYACCESS_F_       0x0004  * ... */
/*      VIDTTYACCESS_F_       0x0008  * ... */
/*      VIDTTYACCESS_F_       0x0010  * ... */
/*      VIDTTYACCESS_F_       0x0020  * ... */
/*      VIDTTYACCESS_F_       0x0040  * ... */
/*      VIDTTYACCESS_F_       0x0080  * ... */
/* NOTE: Flag bits >= 0x0100 are reserved for hardware-specific meaning. */

/* Video tty accessor descriptor.
 * Used for encoding TTY display mode info and the like. */
struct vidttyaccess {
	WEAK refcnt_t               vta_refcnt; /* Reference counter. */
	struct atomic_lock          vta_lock;   /* Lock for character movements. */
#ifdef __WANT_VIDTTYACCESS__vta_mmlop
	union {struct {
#endif /* __WANT_VIDTTYACCESS__vta_mmlop */
	uintptr_t                   vta_flags;         /* [lock(vta_lock)] Set of `VIDTTYACCESS_F_*' */
	uintptr_half_t              vta_cellw;         /* [const] Character cell width in pixels (usually `9') */
	uintptr_half_t              vta_cellh;         /* [const] Character cell height in pixels (usually `16') */
	uintptr_half_t              vta_resx;          /* [const] # of character cells in X */
	uintptr_half_t              vta_resy;          /* [const] # of character cells in Y */
	uintptr_half_t              vta_scan;          /* [const] Scanline size (in characters cells; usually the same as `vta_resx') */
	uintptr_half_t              vta_cellsize;      /* [const] Cell buffer size (in bytes); As expected by `vta_getcelldata' and `vta_setcelldata' */
	uintptr_half_t              vta_scroll_ystart; /* [lock(vta_lock)][<= vta_scroll_yend && <= vta_resy] Start scroll line (usualy `0') */
	uintptr_half_t              vta_scroll_yend;   /* [lock(vta_lock)][>= vta_scroll_ystart && <= vta_resy] End scroll line (usualy `vta_resy') */
	union vidtty_cursor         vta_cursor;        /* [lock(vta_lock)] Current cursor position. */
	uintptr_half_t             _vta_pad;           /* ... */
	uintptr_half_t             _vta_scrl_ymax;     /* [lock(vta_lock)][== vta_scroll_yend - 1] */
	uintptr_t                  _vta_scrl1_to;      /* [lock(vta_lock)][== vta_scroll_ystart * vta_resx] */
	uintptr_t                  _vta_scrl1_from;    /* [lock(vta_lock)][== (vta_scroll_ystart + 1) * vta_resx] */
	uintptr_t                  _vta_scrl1_cnt;     /* [lock(vta_lock)][== vta_resx * ((vta_scroll_yend - vta_scroll_ystart) - 1)] */
	uintptr_t                  _vta_scrl1_fil;     /* [lock(vta_lock)][== (vta_scroll_yend - 1) * vta_scan] */
#define _vidttyaccess_update_scrl(self)                                                                        \
	((self)->_vta_scrl_ymax  = (self)->vta_scroll_yend - 1,                                                    \
	 (self)->_vta_scrl1_to   = (self)->vta_scroll_ystart * (self)->vta_resx,                                   \
	 (self)->_vta_scrl1_from = ((self)->vta_scroll_ystart + 1) * (self)->vta_resx,                             \
	 (self)->_vta_scrl1_cnt  = (self)->vta_resx * (((self)->vta_scroll_yend - (self)->vta_scroll_ystart) - 1), \
	 (self)->_vta_scrl1_fil  = ((self)->vta_scroll_yend - 1) * (self)->vta_scan)
#ifdef __WANT_VIDTTYACCESS__vta_mmlop
	};
		Toblockop(mman)        _vta_mmlop;  /* Used internally */
		Tobpostlockop(mman)    _vta_mmplop; /* Used internally */
	};
#endif /* __WANT_VIDTTYACCESS__vta_mmlop */

	/* Operators... */

	/* [1..1] Called once `vta_refcnt == 0' */
	NOBLOCK NONNULL_T((1)) void
	NOTHROW_T(FCALL *vta_destroy)(struct vidttyaccess *__restrict self);


	/* [1..1][lock(vta_lock)] Set the contents of a single cell. (attributes are taken from `tty->at_ansi')
	 * NOTE: This operator may assume that `address' is visible on-screen
	 * @param: address: == CELL_X + CELL_Y * vta_scan */
	NOBLOCK NONNULL_T((1, 2)) void
	NOTHROW_T(FCALL *vta_setcell)(struct vidttyaccess *__restrict self,
	                              struct ansitty *__restrict tty,
	                              uintptr_t address, char32_t ch);

	/* [1..1][lock(vta_lock)] Hide the hardware cursor
	 * NOTE: This operator is only invoked when `VIDTTYACCESS_F_ACTIVE' is set. */
	NOBLOCK NONNULL_T((1)) void
	NOTHROW_T(FCALL *vta_hidecursor)(struct vidttyaccess *__restrict self);

	/* [1..1][lock(vta_lock)] Show the hardware cursor at the current cursor position.
	 * NOTE: This operator is only called when `vta_cursor.vtc_celly < vta_resy', which
	 *       compiled with the  invariant `vta_cursor.vtc_cellx < vta_resx' means  that
	 *       the cursor is guarantied visible on-screen.
	 * NOTE: This operator is only invoked when `VIDTTYACCESS_F_ACTIVE' is set. */
	NOBLOCK NONNULL_T((1)) void
	NOTHROW_T(FCALL *vta_showcursor)(struct vidttyaccess *__restrict self);

	/* [1..1][lock(vta_lock)] Copy cells across video memory.
	 * NOTE: The cell addresses taken by this function do _NOT_ account for large scanlines!
	 * @param: from_cellid/to_cellid: == CELL_X + CELL_Y * vta_resx */
	NOBLOCK NONNULL_T((1)) void
	NOTHROW_T(FCALL *vta_copycell)(struct vidttyaccess *__restrict self,
	                               uintptr_t to_cellid, uintptr_t from_cellid,
	                               size_t num_cells);

	/* [1..1][lock(vta_lock)] Same as:
	 * >> while (num_cells--) (*vta_setcell)(self, tty, start++, ch); */
	NOBLOCK NONNULL_T((1, 2)) void
	NOTHROW_T(FCALL *vta_fillcells)(struct vidttyaccess *__restrict self,
	                                struct ansitty *__restrict tty,
	                                uintptr_t start, char32_t ch, size_t num_cells);

	/* [1..1][lock(vta_lock)] Do additional stuff needed after to activate this tty.
	 * This includes loading the tty's font into the video card and doing an initial
	 * full redraw of the entire screen.
	 * NOTE: This operator is only invoked when `VIDTTYACCESS_F_ACTIVE' is set. */
	NOBLOCK NONNULL_T((1)) void
	NOTHROW_T(FCALL *vta_activate)(struct vidttyaccess *__restrict self);

	/* [1..1][lock(vta_lock)] Get data for the cell at `address'
	 * @param: address: == CELL_X + CELL_Y * vta_scan
	 * @param: buf:     A buffer of exactly `vta_cellsize' bytes. */
	NOBLOCK NONNULL_T((1, 3)) void
	NOTHROW_T(FCALL *vta_getcelldata)(struct vidttyaccess *__restrict self,
	                                  uintptr_t address, byte_t buf[]);

	/* [1..1][lock(vta_lock)] Set data for the cell at `address'
	 * @param: address: == CELL_X + CELL_Y * vta_scan
	 * @param: buf:     A buffer of exactly `vta_cellsize' bytes. */
	NOBLOCK NONNULL_T((1, 3)) void
	NOTHROW_T(FCALL *vta_setcelldata)(struct vidttyaccess *__restrict self,
	                                  uintptr_t address, byte_t const buf[]);
};

#define vidttyaccess_destroy(self) (*(self)->vta_destroy)(self)
DEFINE_REFCNT_FUNCTIONS(struct vidttyaccess, vta_refcnt, vidttyaccess_destroy)

#ifndef __vidttyaccess_arref_defined
#define __vidttyaccess_arref_defined
ARREF(vidttyaccess_arref, vidttyaccess);
#endif /* !__vidttyaccess_arref_defined */







/************************************************************************/
/* VIDEO TTY                                                            */
/************************************************************************/

/* Operators for `struct vidtty' */
struct vidtty_ops {
	struct ansittydev_ops vto_ansi; /* Ansi TTY operators. */
};

/* Video tty objects */
struct vidtty
#ifndef __WANT_FS_INLINE_STRUCTURES
    : ansittydev                          /* The underling ANSI tty */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct ansittydev         vty_ansi;   /* The underling ANSI tty */
#define _vidtty_asansi(x) &(x)->vty_ansi
#define _vidtty_ansi_     vty_ansi.
#else /* !__WANT_FS_INLINE_STRUCTURES */
#define _vidtty_asansi(x) x
#define _vidtty_ansi_     /* nothing */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
	struct vidttyaccess_arref vty_tty;    /* [1..1][lock(WRITE(vty_dev->vd_lock))]
	                                       * Only the pointed-to  may have the  `VIDTTYACCESS_F_ACTIVE'
	                                       * flag set. When you wish to set a new tty access object (as
	                                       * the result of a mode-change  request), you must clear  the
	                                       * `VIDTTYACCESS_F_ACTIVE' flag (if it was set).
	                                       *
	                                       * Also note that `VIDTTYACCESS_F_ACTIVE' can only ever be
	                                       * set when `vty_active'.  As such,  changing the  current
	                                       * foreground TTY of a video controller also requires that
	                                       * one create a new tty-access object for the new tty, and
	                                       * clear the  `VIDTTYACCESS_F_ACTIVE'  flag  for  the  old
	                                       * tty's access object. */
	REF struct viddev        *vty_dev;    /* [1..1][const] Video device. */
	REF struct vidtty        *vty_oldtty; /* [0..1][const_if(wasdestroyed(self))]
	                                       * [lock(vlc_dev->vd_lock)]
	                                       * TTY that is made active when this tty is destroyed. */
	unsigned int              vty_active; /* [lock(vty_dev->vd_lock)]
	                                       * [const_if(wasdestroyed(self))]
	                                       * Non-zero if this tty is currently active. */
};

/* Operator access */
#define vidtty_getops(self) \
	((struct vidtty_ops const *)__COMPILER_REQTYPE(struct vidtty const *, self)->_vidtty_ansi_ _ansittydev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_ops)
#define _vidtty_assert_ops_(ops) _ansittydev_assert_ops_(&(ops)->vto_ansi)

/* Return a reference to the TTY accessor of `self' */
#define vidtty_getaccess(self)        arref_get(&(self)->vty_tty)
#define ansitty_getvidttyaccess(self) vidtty_getaccess(ansitty_asvidtty(self))

/* Helper macros for loading a `struct vidtty' from some other object. */
#define ansittydev_asvidtty(self) ((struct vidtty *)(self))
#define chrdev_asvidtty(self)     ansittydev_asvidtty(chrdev_asansitty(self))
#define device_asvidtty(self)     ansittydev_asvidtty(device_asansitty(self))
#define devnode_asvidtty(self)    ansittydev_asvidtty(devnode_asansitty(self))
#define fnode_asvidtty(self)      ansittydev_asvidtty(fnode_asansitty(self))
#define mfile_asvidtty(self)      ansittydev_asvidtty(mfile_asansitty(self))
#define ansitty_asvidtty(self)    __COMPILER_CONTAINER_OF(self, struct vidtty, _vidtty_ansi_ at_ansi)

/* Helper macros for checking if some object is a `struct vidtty'. */
#define ansittydev_isvidtty(self) ((self)->_vidtty_ansi_ at_ansi.at_ops.ato_putc == &_vidtty_v_putc)
#define chrdev_isvidtty(self)     (chrdev_isansitty(self) && ansittydev_isvidtty(chrdev_asansitty(self)))
#define device_isvidtty(self)     (device_isansitty(self) && ansittydev_isvidtty(device_asansitty(self)))
#define devnode_isvidtty(self)    (devnode_isansitty(self) && ansittydev_isvidtty(devnode_asansitty(self)))
#define fnode_isvidtty(self)      (fnode_isansitty(self) && ansittydev_isvidtty(fnode_asansitty(self)))
#define mfile_isvidtty(self)      (mfile_isansitty(self) && ansittydev_isvidtty(mfile_asansitty(self)))

/* Async job  started to  revert  to the  old  display
 * mode when this TTY is destroyed while `vty_active'. */
#define _vidtty_toasyncrestore(self) \
	((struct async *)&(self)->_vidtty_ansi_ at_ansi)
#define _vidtty_fromasyncrestore(self) \
	__COMPILER_CONTAINER_OF((struct ansitty *)__COMPILER_REQTYPE(struct async *, self), struct vidtty, _vidtty_ansi_ at_ansi)
STATIC_ASSERT(sizeof(struct async) <= sizeof(struct ansitty));

/* Activate a given TTY. If an active userlock exists, the tty will not actually
 * be  made active, but will instead be  linked such that the userlock's release
 * will make the tty active. */
FUNDEF BLOCKING NONNULL((1)) void FCALL
vidtty_activate(struct vidtty *__restrict self)
		THROWS(E_IOERROR);


/* Default vidtty operators. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vidtty_v_destroy)(struct mfile *__restrict self);
#define vidtty_v_changed ansittydev_v_changed
#define vidtty_v_wrattr  ansittydev_v_wrattr
#define vidtty_v_tryas   ansittydev_v_tryas
#define vidtty_v_write   ansittydev_v_write /* Cannot be overwritten! */
FUNDEF NONNULL((1)) syscall_slong_t KCALL
vidtty_v_ioctl(struct mfile *__restrict self, ioctl_t cmd,
               USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
DATDEF struct ansitty_operators const vidtty_ansitty_ops;
/* Functions, as referenced in `vidtty_ansitty_ops' (you should never need these) */
FUNDEF NONNULL((1)) void LIBANSITTY_CC _vidtty_v_putc(struct ansitty *__restrict self, char32_t ch) ASMNAME("vidtty_v_putc");
FUNDEF NONNULL((1)) void LIBANSITTY_CC _vidtty_v_setcursor(struct ansitty *__restrict self, ansitty_coord_t x, ansitty_coord_t y, bool update_hw_cursor) ASMNAME("vidtty_v_setcursor");
FUNDEF NONNULL((1, 2)) void LIBANSITTY_CC _vidtty_v_getcursor(struct ansitty *__restrict self, ansitty_coord_t ppos[2]) ASMNAME("vidtty_v_getcursor");
FUNDEF NONNULL((1, 2)) void LIBANSITTY_CC _vidtty_v_getsize(struct ansitty *__restrict self, ansitty_coord_t psize[2]) ASMNAME("vidtty_v_getsize");
FUNDEF NONNULL((1)) void LIBANSITTY_CC _vidtty_v_copycell(struct ansitty *__restrict self, ansitty_offset_t dst_offset, ansitty_coord_t count) ASMNAME("vidtty_v_copycell");
FUNDEF NONNULL((1)) void LIBANSITTY_CC _vidtty_v_fillcell(struct ansitty *__restrict self, char32_t ch, ansitty_coord_t count) ASMNAME("vidtty_v_fillcell");
FUNDEF NONNULL((1)) void LIBANSITTY_CC _vidtty_v_setttymode(struct ansitty *__restrict self, uint16_t new_ttymode) ASMNAME("vidtty_v_setttymode");
FUNDEF NONNULL((1)) void LIBANSITTY_CC _vidtty_v_scrollregion(struct ansitty *__restrict self, ansitty_coord_t start_line, ansitty_coord_t end_line) ASMNAME("vidtty_v_scrollregion");
FUNDEF NONNULL((1)) void LIBANSITTY_CC _vidtty_v_output(struct ansitty *__restrict self, void const *data, size_t datalen) ASMNAME("ansittydev_v_output");
FUNDEF NONNULL((1)) void LIBANSITTY_CC _vidtty_v_setled(struct ansitty *__restrict self, uint8_t mask, uint8_t flag) ASMNAME("ansittydev_v_setled");
FUNDEF NONNULL((1, 2)) __BOOL LIBANSITTY_CC _vidtty_v_termios(struct ansitty *__restrict self, struct termios *__restrict oldios, struct termios const *newios) ASMNAME("ansittydev_v_termios");


/* Initialize common+basic fields. The caller must still initialize:
 *  - self->_vidtty_ansi_ _ansittydev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_flags |= MFILE_FN_GLOBAL_REF;  # s.a. `device_registerf()'
 *  - self->_vidtty_ansi_ _ansittydev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_allnodes;  # s.a. `device_registerf()'
 *  - self->_vidtty_ansi_ _ansittydev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_supent;    # s.a. `device_registerf()'
 *  - self->_vidtty_ansi_ _ansittydev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_ino;       # s.a. `device_registerf()'
 *  - self->_vidtty_ansi_ _ansittydev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_mode;      # Something or'd with S_IFCHR
 *  - self->_vidtty_ansi_ _ansittydev_chr_ _chrdev_dev_ _device_devnode_ dn_devno;                     # s.a. `device_registerf()'
 *  - self->_vidtty_ansi_ _ansittydev_chr_ _chrdev_dev_ dv_driver;                                     # As `incref(drv_self)'
 *  - self->_vidtty_ansi_ _ansittydev_chr_ _chrdev_dev_ dv_dirent;                                     # s.a. `device_registerf()'
 *  - self->_vidtty_ansi_ _ansittydev_chr_ _chrdev_dev_ dv_byname_node;                                # s.a. `device_registerf()'
 *  - self->vty_dev;
 *  - self->vty_tty;
 * @param: struct vidtty           *self: Video TTY to initialize.
 * @param: struct vidtty_ops const *ops:  Video TTY operators. */
#define _vidtty_init(self, ops)                                                        \
	(_vidtty_assert_ops_(ops)                                                          \
	 _chrdev_init(_ansittydev_aschr(_vidtty_asansi(self)), &(ops)->vto_ansi.ato_cdev), \
	 ansitty_init(&(self)->_vidtty_ansi_ at_ansi, &vidtty_ansitty_ops),                \
	 awref_init(&(self)->_vidtty_ansi_ at_tty, __NULLPTR),                             \
	 (self)->vty_active = 0, (self)->vty_oldtty = __NULLPTR)
#define _vidtty_cinit(self, ops)                                                        \
	(_vidtty_assert_ops_(ops)                                                           \
	 _chrdev_cinit(_ansittydev_aschr(_vidtty_asansi(self)), &(ops)->vto_ansi.ato_cdev), \
	 ansitty_init(&(self)->_vidtty_ansi_ at_ansi, &vidtty_ansitty_ops),                 \
	 awref_cinit(&(self)->_vidtty_ansi_ at_tty, __NULLPTR),                             \
	 __hybrid_assert((self)->vty_active == 0),                                          \
	 __hybrid_assert((self)->vty_oldtty == __NULLPTR))
/* Finalize a partially initialized `struct vidtty' (as initialized by `_vidtty_init()') */
#define _vidtty_fini(self) _chrdev_fini(_ansittydev_aschr(_vidtty_asansi(self)))






/************************************************************************/
/* VIDEO LOCK                                                           */
/************************************************************************/

/* Operators for `struct vidtty' */
struct vidlck_ops {
	struct mfile_ops vlo_file; /* Mem-file operators. */

	/* [1..1][lock(dev->vd_lock)]
	 * Restore  _all_  (standard+chipset-specific) registers  to what
	 * they were before the lock was created. This operator is called
	 * from an async worker during destruction of the video lock. */
	BLOCKING NONNULL_T((1)) void
	(FCALL *vlo_restore)(struct vidlck *__restrict self,
	                     struct viddev *__restrict dev)
			THROWS(E_IOERROR);
};

struct vidlck
#ifndef __WANT_FS_INLINE_STRUCTURES
    : mfile                        /* The underling file */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct mfile       vlc_file;   /* The underling file */
#define _vidlck_asfile(x) &(x)->vlc_file
#define _vidlck_file_     vlc_file.
#else /* !__WANT_FS_INLINE_STRUCTURES */
#define _vidlck_asfile(x) x
#define _vidlck_file_     /* nothing */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
	REF struct viddev *vlc_dev;    /* [1..1][const] Video device. */
	REF struct vidtty *vlc_oldtty; /* [0..1][lock(vlc_dev->vd_lock)] TTY that is made active when this tty is destroyed. */
	struct async       vlc_rstor;  /* A pre-allocated async controller used to release the lock. */
	/* Sub-classes will define everything register data to restore here. */
};

/* Operator access */
#define vidlck_getops(self) \
	((struct vidlck_ops const *)__COMPILER_REQTYPE(struct vidlck const *, self)->_vidlck_file_ mf_ops)

/* Helper macros for loading a `struct vidtty' from some other object. */
#define mfile_asvidlck(self) ((struct vidlck *)(self))

/* Initialize common+basic fields. The caller must still initialize:
 *  - self->vlc_dev;
 *  - self->vlc_oldtty;
 * @param: struct vidlck           *self: Video lock to initialize.
 * @param: struct vidlck_ops const *ops:  Video lock operators. */
#define _vidlck_init(self, ops)                                                     \
	(_mfile_init(self, &(ops)->vlo_file, PAGESHIFT, PAGESHIFT),                     \
	 (self)->mf_parts             = MFILE_PARTS_ANONYMOUS,                          \
	 (self)->mf_changed.slh_first = MFILE_PARTS_ANONYMOUS,                          \
	 atomic64_init(&(self)->mf_filesize, 0),                                        \
	 (self)->mf_flags = (MFILE_F_READONLY | MFILE_F_ATTRCHANGED | MFILE_F_CHANGED | \
	                     MFILE_F_NOATIME | MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO |    \
	                     MFILE_F_NOMTIME | MFILE_F_FIXEDFILESIZE),                  \
	 (self)->mf_btime = (self)->mf_ctime =                                          \
	 (self)->mf_mtime = (self)->mf_atime = realtime())
#define _vidlck_cinit(self, ops)                                                    \
	(_mfile_cinit(self, &(ops)->vlo_file, PAGESHIFT, PAGESHIFT),                    \
	 (self)->mf_parts             = MFILE_PARTS_ANONYMOUS,                          \
	 (self)->mf_changed.slh_first = MFILE_PARTS_ANONYMOUS,                          \
	 atomic64_cinit(&(self)->mf_filesize, 0),                                       \
	 (self)->mf_flags = (MFILE_F_READONLY | MFILE_F_ATTRCHANGED | MFILE_F_CHANGED | \
	                     MFILE_F_NOATIME | MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO |    \
	                     MFILE_F_NOMTIME | MFILE_F_FIXEDFILESIZE),                  \
	 (self)->mf_btime = (self)->mf_ctime =                                          \
	 (self)->mf_mtime = (self)->mf_atime = realtime())

/* Finalize a partially initialized `struct vidlck' (as initialized by `_vidlck_init()') */
#define _vidlck_fini(self) (void)0

#ifndef __realtime_defined
#define __realtime_defined
FUNDEF NOBLOCK WUNUSED struct timespec NOTHROW(KCALL realtime)(void);
#endif /* !__realtime_defined */


/* Default operators for `struct vidlck' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vidlck_v_destroy)(struct mfile *__restrict self);
#define vidlck_v_ioctl      mfile_v_ioctl
#define vidlck_v_stream_ops UNDEFINED









/************************************************************************/
/* VIDEO DEVICE                                                         */
/************************************************************************/

#ifndef __mfile_awref_defined
#define __mfile_awref_defined
AWREF(mfile_awref, mfile);
#endif /* !__mfile_awref_defined */

/* Operators for `struct viddev' */
struct viddev_ops {
	struct chrdev_ops vdo_chr; /* Character device operators. */

	/* [1..1][lock(self->vd_lock)]
	 * Set video mode associated with a TTY access object. */
	BLOCKING NONNULL_T((1, 2)) void
	(FCALL *vdo_setttyvideomode)(struct viddev *__restrict self,
	                             struct vidttyaccess const *__restrict tty)
			THROWS(E_IOERROR);

	/* [1..1][lock(self->vd_lock)]
	 * Allocate a new video lock. This operator must _ONLY_ initialize the fields:
	 *  - return->_vidlck_file_ mf_ops = &MY_vidlck_ops.vlo_file; # Something that includes a destructor that calls `vidlck_v_destroy()'
	 *  - return->...                                             # Sub-class specific fields (primarily including video registers)
	 * All other fields are initialized by the caller. */
	BLOCKING ATTR_RETNONNULL_T WUNUSED_T NONNULL_T((1)) struct vidlck *
	(FCALL *vdo_alloclck)(struct viddev *__restrict self,
	                      struct vidtty *active_tty)
			THROWS(E_IOERROR, E_WOULDBLOCK);

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
	/* [0..1] Activate and return a video tty object for use within the builtin debugger.
	 * - Called while the debugger is already active (dbg_active).
	 * - Must _NOT_ clear the contents of the display buffer of the returned  tty.
	 *   Instead,  anything which  may still be  stored within the  buffer must be
	 *   displayed on-screen as-is. If the caller wishes to clear the screen, they
	 *   must  do so themselves, even if this would mean getting a glimpse at what
	 *   was displayed just before the debugger was exited the last time.
	 * - No requirements on minimal terminal size are made, but try to aim for 80x25,
	 *   as  this is  the resolution which  most debugger applets  were designed for. */
	ATTR_RETNONNULL_T WUNUSED_T NONNULL_T((1)) struct vidttyaccess *
	NOTHROW_T(FCALL *vdo_enterdbg)(struct viddev *__restrict self);

	/* [0..1] Restore video registers as the result of exiting the builtin debugger.
	 * - Called while the debugger is still active (dbg_active).
	 * - s.a. `vdo_enterdbg()'
	 * - This function and `vdo_enterdbg()' are also used to implement the `screen' command */
	NONNULL_T((1)) void
	NOTHROW_T(FCALL *vdo_leavedbg)(struct viddev *__restrict self);
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

};

/* Video device. */
struct viddev
#ifndef __WANT_FS_INLINE_STRUCTURES
    : chrdev                      /* The underling character device */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct chrdev      vd_chr;    /* The underling character device */
#define _viddev_aschr(x) &(x)->vd_chr
#define _viddev_chr_     vty_chr.
#else /* !__WANT_FS_INLINE_STRUCTURES */
#define _viddev_aschr(x) x
#define _viddev_chr_     /* nothing */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
	struct shared_lock vd_lock;   /* Lock for this video device. */
	struct mfile_awref vd_active; /* [0..1][lock(WRITE(vd_lock))] Active TTY or  user-lock.
	                               * When this points to a dead file, that file _must_ clean up itself! */
};

/* Operator access */
#define viddev_getops(self) \
	((struct viddev_ops const *)__COMPILER_REQTYPE(struct viddev const *, self)->_viddev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_ops)
#define _viddev_assert_ops_(ops) _chrdev_assert_ops_(&(ops)->vto_ansi)

/* Helper macros for loading a `struct viddev' from some other object. */
#define chrdev_asviddev(self)     ((struct viddev *)(self))
#define device_asviddev(self)     chrdev_asviddev(device_aschrdev(self))
#define devnode_asviddev(self)    chrdev_asviddev(devnode_aschrdev(self))
#define fnode_asviddev(self)      chrdev_asviddev(fnode_aschrdev(self))
#define mfile_asviddev(self)      chrdev_asviddev(mfile_aschrdev(self))

/* Helper macros for `struct viddev::vd_lock' */
#define _viddev_reap(self)      (void)0
#define viddev_reap(self)       (void)0
#define viddev_mustreap(self)   0
#define viddev_tryacquire(self) shared_lock_tryacquire(&(self)->vd_lock)
#define viddev_acquire(self)    shared_lock_acquire(&(self)->vd_lock)
#define viddev_acquire_nx(self) shared_lock_acquire_nx(&(self)->vd_lock)
#define _viddev_release(self)   shared_lock_release(&(self)->vd_lock)
#define viddev_release(self)    (shared_lock_release(&(self)->vd_lock), viddev_reap(self))
#define viddev_acquired(self)   shared_lock_acquired(&(self)->vd_lock)
#define viddev_available(self)  shared_lock_available(&(self)->vd_lock)

/* Return a reference to the currently "active" tty (or the one that will become
 * active after a currently held user-lock is released). If no such TTY  exists,
 * return NULL instead. */
FUNDEF BLOCKING WUNUSED NONNULL((1)) REF struct vidtty *FCALL
viddev_getactivetty(struct viddev *__restrict self);

/* Create a new video lock object for a given video device. */
FUNDEF BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct vidlck *FCALL
viddev_newlck(struct viddev *__restrict self);


/* Default operators for `struct viddev'. */
#define viddev_v_destroy chrdev_v_destroy
#define viddev_v_changed chrdev_v_changed
#define viddev_v_wrattr  chrdev_v_wrattr
#define viddev_v_tryas   chrdev_v_tryas
FUNDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL
viddev_v_write(struct mfile *__restrict self, USER CHECKED void const *src,
               size_t num_bytes, iomode_t mode) THROWS(...);
FUNDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL
viddev_v_writev(struct mfile *__restrict self, struct iov_buffer *__restrict src,
                size_t num_bytes, iomode_t mode) THROWS(...);
FUNDEF NONNULL((1)) syscall_slong_t KCALL
viddev_v_ioctl(struct mfile *__restrict self, ioctl_t cmd,
               USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
DATDEF struct mfile_stream_ops const viddev_v_stream_ops;

/* Initialize common+basic fields. The caller must still initialize:
 *  - self->_viddev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_flags |= MFILE_FN_GLOBAL_REF;  # s.a. `device_registerf()'
 *  - self->_viddev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_allnodes;  # s.a. `device_registerf()'
 *  - self->_viddev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_supent;    # s.a. `device_registerf()'
 *  - self->_viddev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_ino;       # s.a. `device_registerf()'
 *  - self->_viddev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_mode;      # Something or'd with S_IFCHR
 *  - self->_viddev_chr_ _chrdev_dev_ _device_devnode_ dn_devno;                     # s.a. `device_registerf()'
 *  - self->_viddev_chr_ _chrdev_dev_ dv_driver;                                     # As `incref(drv_self)'
 *  - self->_viddev_chr_ _chrdev_dev_ dv_dirent;                                     # s.a. `device_registerf()'
 *  - self->_viddev_chr_ _chrdev_dev_ dv_byname_node;                                # s.a. `device_registerf()'
 * @param: struct viddev           *self: Video device to initialize.
 * @param: struct viddev_ops const *ops:  Video device operators. */
#define _viddev_init(self, ops)                          \
	(_chrdev_init(_viddev_aschr(self), &(ops)->vdo_chr), \
	 shared_lock_init(&(self)->vd_lock),                 \
	 awref_init(&(self)->vd_active, __NULLPTR))
#define _viddev_cinit(self, ops)                          \
	(_chrdev_cinit(_viddev_aschr(self), &(ops)->vdo_chr), \
	 shared_lock_cinit(&(self)->vd_lock),                 \
	 awref_cinit(&(self)->vd_active, __NULLPTR))
/* Finalize a partially initialized `struct viddev' (as initialized by `_viddev_init()') */
#define _viddev_fini(self) _chrdev_fini(_viddev_aschr(self))

#ifndef __viddev_axref_defined
#define __viddev_axref_defined
AXREF(viddev_axref, viddev);
#endif /* !__viddev_axref_defined */

/* [0..1] Default video device adapter. (Used to implement output in the builtin debugger) */
DATDEF struct viddev_axref viddev_default;

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_DEV_VIDEO_H */
