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
#ifndef GUARD_MODSVGA_MODE_C
#define GUARD_MODSVGA_MODE_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/handle.h>
#include <kernel/malloc.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cred.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <hw/video/vga.h>
#include <kos/except.h>
#include <kos/ioctl/svga.h>

#include <assert.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <libsvga/util/vgaio.h>

/**/
#include "svga.h"

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/************************************************************************/
/* ioctl helpers.                                                       */
/************************************************************************/

/* Return a pointer to the internal mode descriptor matching `mode' */
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1)) struct svga_modeinfo const *FCALL
svgadev_findmode(struct svgadev *__restrict self,
                 USER CHECKED struct svga_modeinfo const *mode)
		THROWS(E_SEGFAULT, E_NO_SUCH_OBJECT) {
	struct svga_modeinfo const *result;
	size_t i;
	for (i = 0; i < self->svd_supmodec; ++i) {
		result = svgadev_supmode(self, i);
		if (memcmp(result, mode, sizeof(struct svga_modeinfo)) == 0)
			return result;
	}
	THROW(E_NO_SUCH_OBJECT);
}

PRIVATE NONNULL((1)) syscall_slong_t KCALL
svgadev_ioctl_getdefmode(struct svgadev *__restrict self,
                         USER UNCHECKED struct svga_modeinfo *modeinfo)
		THROWS(E_SEGFAULT) {
	validate_writable(modeinfo, sizeof(*modeinfo));
	memcpy(modeinfo, self->svd_defmode, sizeof(*self->svd_defmode));
	return 0;
}

PRIVATE NONNULL((1)) syscall_slong_t KCALL
svgadev_ioctl_setdefmode(struct svgadev *__restrict self,
                         USER UNCHECKED struct svga_modeinfo const *modeinfo)
		THROWS(E_SEGFAULT, E_INSUFFICIENT_RIGHTS) {
	USER CHECKED struct svga_modeinfo const *reqmode;
	require(CAP_SYS_RAWIO);
	validate_readable(modeinfo, sizeof(*modeinfo));
	reqmode = svgadev_findmode(self, modeinfo);
	ATOMIC_WRITE(self->svd_defmode, reqmode);
	return 0;
}

PRIVATE NONNULL((1)) syscall_slong_t KCALL
svgadev_ioctl_lsmodes(struct svgadev *__restrict self,
                      USER UNCHECKED struct svga_lsmodes *info)
		THROWS(E_SEGFAULT, E_INSUFFICIENT_RIGHTS) {
	size_t i, ncopy, count;
	struct svga_lsmodes req;
	validate_readwrite(info, sizeof(*info));
	memcpy(&req, info, sizeof(req));
	validate_writablem(req.svl_buf, req.svl_count,
	                   sizeof(struct svga_modeinfo));
	if (OVERFLOW_USUB(self->svd_supmodec, req.svl_offset, &count))
		count = 0;
	ncopy = count;
	if (ncopy > req.svl_count)
		ncopy = req.svl_count;

	/* Copy mode information into user-space. */
	for (i = 0; i < ncopy; ++i) {
		struct svga_modeinfo const *mode;
		mode = svgadev_supmode(self, req.svl_offset + i);
		memcpy(&req.svl_buf[i], mode, sizeof(struct svga_modeinfo));
	}

	/* Write-back the # of written modes. */
	COMPILER_WRITE_BARRIER();
	info->svl_count = count;
	return 0;
}

PRIVATE NONNULL((1)) syscall_slong_t KCALL
svgadev_ioctl_getcsname(struct svgadev *__restrict self,
                        USER UNCHECKED char *result)
		THROWS(E_SEGFAULT, E_INSUFFICIENT_RIGHTS) {
	validate_writable(result, SVGA_CSNAMELEN * sizeof(char));
	memcpy(result, self->svd_csdriver->scd_name,
	       SVGA_CSNAMELEN, sizeof(char));
	return 0;
}


struct cs_strings_printer {
	struct svga_strings csp_req;    /* User-request. */
	size_t              csp_count;  /* # of written strings. */
	size_t              csp_reqbuf; /* Required buffer size. */
};

PRIVATE NONNULL((2, 3)) ssize_t LIBSVGA_CC
cs_strings_printer_cb(void *arg,
                      char const *__restrict name,
                      char const *__restrict value) {
	unsigned int i;
	char const *strings[] = { name, value };
	struct cs_strings_printer *me;
	me = (struct cs_strings_printer *)arg;
	if (me->csp_req.svs_start != 0) {
		--me->csp_req.svs_start;
		return 0; /* Skip this pair... */
	}
	for (i = 0; i < COMPILER_LENOF(strings); ++i) {
		char const *str;
		size_t len;
		str = strings[i];
		len = strlen(str);
		len = (len + 1) * sizeof(char);
		me->csp_reqbuf += (len + 1) * sizeof(char);
		if (len > me->csp_req.svs_bufsz)
			len = me->csp_req.svs_bufsz;
		me->csp_req.svs_buf = (USER CHECKED char *)mempcpy(me->csp_req.svs_buf,
		                                                   str, len);
		me->csp_req.svs_bufsz -= len;
	}
	++me->csp_count;
	--me->csp_req.svs_count;
	if (!me->csp_req.svs_count)
		return -1; /* Stop enumeration */
	return 0;
}

PRIVATE NONNULL((1)) syscall_slong_t KCALL
svgadev_ioctl_getcsstrings(struct svgadev *__restrict self,
                           USER UNCHECKED struct svga_strings *info)
		THROWS(E_SEGFAULT, E_INSUFFICIENT_RIGHTS) {
	struct cs_strings_printer req;
	validate_readwrite(info, sizeof(*info));
	memcpy(&req.csp_req, info, sizeof(req.csp_req));
	validate_writable(req.csp_req.svs_buf, (size_t)req.csp_req.svs_bufsz);

	/* Setup buffer requirements as empty. */
	req.csp_count  = 0;
	req.csp_reqbuf = 0;

	/* Check if we should (and can) enumerate strings. */
	if (req.csp_req.svs_count != 0 &&
	    self->svd_chipset.sc_ops.sco_strings != NULL) {
		svga_chipset_acquire(&self->svd_chipset);
		RAII_FINALLY { svga_chipset_release(&self->svd_chipset); };
		/* Enumerate strings. */
		(*self->svd_chipset.sc_ops.sco_strings)(&self->svd_chipset,
		                                        &cs_strings_printer_cb,
		                                        &req);
	}

	/* Write back string count information. */
	COMPILER_WRITE_BARRIER();
	info->svs_count = req.csp_count;
	info->svs_bufsz = req.csp_reqbuf;
	return 0;
}






/************************************************************************/
/* SVGALCK                                                              */
/************************************************************************/
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svgalck_async_v_destroy)(struct async *__restrict self) {
	struct svgalck *me = container_of(self, struct svgalck, slc_rstor);

	/* Clear remaining references. */
	decref_unlikely(me->slc_dev);
	xdecref_unlikely(me->slc_oldtty);

	/* Destroy the original underlying character-device. */
	chrdev_v_destroy(me);
}

PRIVATE NONNULL((1)) ktime_t FCALL
svgalck_async_v_connect(struct async *__restrict self) {
	struct svgalck *me = container_of(self, struct svgalck, slc_rstor);
	shared_lock_pollconnect(&me->slc_dev->svd_chipset.sc_lock);
	return KTIME_INFINITE;
}

PRIVATE WUNUSED NONNULL((1)) bool FCALL
svgalck_async_v_test(struct async *__restrict self) {
	struct svgalck *me = container_of(self, struct svgalck, slc_rstor);
	return svga_chipset_available(&me->slc_dev->svd_chipset);
}

PRIVATE WUNUSED NONNULL((1)) unsigned int FCALL
svgalck_async_v_work(struct async *__restrict self) {
	struct svgalck *me = container_of(self, struct svgalck, slc_rstor);
	struct svgatty *nt = me->slc_oldtty;
	struct svgadev *dv = me->slc_dev;
	struct svga_ttyaccess *ac;
	assert(PREEMPTION_ENABLED());
	if (!svga_chipset_tryacquire(&dv->svd_chipset))
		return ASYNC_RESUME;
	RAII_FINALLY { svga_chipset_release(&dv->svd_chipset); };
	assert(awref_ptr(&dv->svd_active) == me);

	/* Restore extended registers. (Only do this once if `svgadev_setmode()' below throws) */
	if (me->slc_mode != (struct svga_modeinfo const *)-1) {
		(*dv->svd_chipset.sc_ops.sco_setregs)(&dv->svd_chipset, me->slc_xregs);
		basevga_setregs(&me->slc_vmode);
		me->slc_mode = (struct svga_modeinfo const *)-1;
	}

	/* Set the video mode used by `nt'
	 * NOTE: Because we're holding a lock to `dv', the tty access object can't change! */
	ac = arref_ptr(&nt->sty_tty);
	assert(!wasdestroyed(ac));
	assert(!(ac->sta_flags & SVGA_TTYACCESS_F_ACTIVE));
	assert(!nt->sty_active);
	svgadev_setmode(dv, ac->sta_mode);

	/* Mark the tty as active. */
	atomic_lock_acquire(&ac->sta_lock);       /* This can't throw because preemption is enabled. */
	ac->sta_flags |= SVGA_TTYACCESS_F_ACTIVE; /* Mark TTY accessor as active */
	nt->sty_active = 1;                       /* Mark TTY as active */
	(*ac->sta_activate)(ac);                  /* This is NOBLOCK+NOTHROW */
	awref_set(&dv->svd_active, nt);           /* Remember TTY as active */
	atomic_lock_release(&ac->sta_lock);
	return ASYNC_FINISHED;
}


PRIVATE struct async_ops const svgalck_async_v_ops = {
	.ao_driver  = &drv_self,
	.ao_destroy = &svgalck_async_v_destroy,
	.ao_connect = &svgalck_async_v_connect,
	.ao_test    = &svgalck_async_v_test,
	.ao_work    = &svgalck_async_v_work,
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL svgalck_v_destroy)(struct mfile *__restrict self) {
	struct svgalck *me = (struct svgalck *)self;
	/* Setup an async job to restore another tty. */
	async_init(&me->slc_rstor, &svgalck_async_v_ops);
	decref_unlikely(async_start(&me->slc_rstor));
}

PRIVATE NONNULL((1)) syscall_slong_t KCALL
svgalck_v_ioctl(struct mfile *__restrict self, syscall_ulong_t cmd,
                USER UNCHECKED void *arg, iomode_t mode) THROWS(...) {
	struct svgalck *me = (struct svgalck *)self;
	switch (cmd) {

	case SVGA_IOC_GETMODE: {
		struct svga_modeinfo const *mymode;
		validate_writable(arg, sizeof(struct svga_modeinfo));
		mymode = ATOMIC_READ(me->slc_mode);
		if (!mymode)
			THROW(E_NO_SUCH_OBJECT);
		memcpy(arg, mymode, sizeof(struct svga_modeinfo));
		return 0;
	}	break;

	case SVGA_IOC_SETMODE: {
		struct svgadev *dv = me->slc_dev;
		struct svga_modeinfo const *newmode;
		validate_readable(arg, sizeof(struct svga_modeinfo));
		newmode = svgadev_findmode(me->slc_dev, (USER CHECKED struct svga_modeinfo *)arg);
		svga_chipset_acquire(&dv->svd_chipset);
		RAII_FINALLY { svga_chipset_release(&dv->svd_chipset); };

		/* Set new video mode. */
		svgadev_setmode(dv, newmode);

		/* For text modes, also load the default font! */
		if (newmode->smi_flags & SVGA_MODEINFO_F_TXT)
			basevga_wrvmem(0x20000, basevga_defaultfont, sizeof(basevga_defaultfont));

		/* Remember last-set mode. */
		ATOMIC_WRITE(me->slc_mode, newmode);
	}	break;

	case SVGA_IOC_GETDEFMODE:
		return svgadev_ioctl_getdefmode(me->slc_dev, (USER UNCHECKED struct svga_modeinfo *)arg);
	case SVGA_IOC_SETDEFMODE:
		return svgadev_ioctl_setdefmode(me->slc_dev, (USER UNCHECKED struct svga_modeinfo const *)arg);
	case SVGA_IOC_LSMODES:
		return svgadev_ioctl_lsmodes(me->slc_dev, (USER UNCHECKED struct svga_lsmodes *)arg);
	case SVGA_IOC_GETCSNAME:
		return svgadev_ioctl_getcsname(me->slc_dev, (USER UNCHECKED char *)arg);
	case SVGA_IOC_CSSTRINGS:
		return svgadev_ioctl_getcsstrings(me->slc_dev, (USER UNCHECKED struct svga_strings *)arg);

	default:
		return mfile_v_ioctl(self, cmd, arg, mode);
		break;
	}
	return 0;
}


PRIVATE struct mfile_stream_ops const svgalck_v_stream_ops = {
	.mso_ioctl = &svgalck_v_ioctl,
	/* TODO: mmap (including support for automatic bank switching) */
};

INTERN_CONST struct mfile_ops const svgalck_ops = {
	.mo_destroy = &svgalck_v_destroy,
	.mo_stream  = &svgalck_v_stream_ops,
};





/************************************************************************/
/* SVGATTY                                                              */
/************************************************************************/

/* Try to do optical character recognition on `cell->sgc_lines'
 * It sound more fancy than it is. - We just compare the  lines
 * with `basevga_defaultfont' and see if we get a match.
 *
 * Upon error, return `0' (which should be disabled as U+FFFD: �) */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) byte_t
NOTHROW(FCALL try_ocr_on_gfxcell)(struct svga_gfxcell const *__restrict cell) {
	unsigned int i;
	for (i = 0; i < 256; ++i) {
		if (memcmp(basevga_defaultfont[i], cell->sgc_lines, 16) == 0)
			break;
	}
	return i & 0xff;
}

/* Convert the contents of `otty' into `ntty' */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL convert_tty_contents)(struct svga_ttyaccess const *__restrict _otty,
                                    struct svga_ttyaccess *__restrict _ntty) {
	uintptr_half_t x, y, common_resx, common_resy;
	common_resx = _otty->sta_resx;
	common_resy = _otty->sta_resy;
	if (common_resx > _ntty->sta_resx)
		common_resx = _ntty->sta_resx;
	if (common_resy > _ntty->sta_resy)
		common_resy = _ntty->sta_resy;
	if (svga_ttyaccess_istxt(_otty)) {
		struct svga_ttyaccess_txt *otty;
		otty = (struct svga_ttyaccess_txt *)_otty;
		if (svga_ttyaccess_istxt(_ntty)) {
			struct svga_ttyaccess_txt *ntty;
			ntty = (struct svga_ttyaccess_txt *)_ntty;
			for (y = 0; y < common_resy; ++y) {
				for (x = 0; x < common_resx; ++x) {
					uint16_t cell;
					cell = otty->stt_display[x + y * otty->sta_scan];
					ntty->stt_display[x + y * ntty->sta_scan] = cell;
				}
			}
		} else {
			struct svga_ttyaccess_gfx *ntty;
			ntty = (struct svga_ttyaccess_gfx *)_ntty;
			for (y = 0; y < common_resy; ++y) {
				for (x = 0; x < common_resx; ++x) {
					uint16_t cell = otty->stt_display[x + y * otty->sta_scan];
					memcpy(ntty->stx_display[x + y * ntty->sta_resx].sgc_lines,
					       basevga_defaultfont[cell & 0xff], 16);
					ntty->stx_display[x + y * ntty->sta_resx].sgc_color = (cell >> 8) & 0xff;
				}
			}
		}
	} else {
		struct svga_ttyaccess_gfx *otty;
		otty = (struct svga_ttyaccess_gfx *)_otty;
		if (svga_ttyaccess_istxt(_ntty)) {
			struct svga_ttyaccess_txt *ntty;
			ntty = (struct svga_ttyaccess_txt *)_ntty;
			for (y = 0; y < common_resy; ++y) {
				for (x = 0; x < common_resx; ++x) {
					struct svga_gfxcell const *cell;
					uint16_t word;
					cell = &otty->stx_display[x + y * otty->sta_scan];
					word = cell->sgc_color << 8;
					word |= try_ocr_on_gfxcell(cell);
					ntty->stt_display[x + y * ntty->sta_scan] = word;
				}
			}
		} else {
			struct svga_ttyaccess_gfx *ntty;
			ntty = (struct svga_ttyaccess_gfx *)_ntty;
			for (y = 0; y < common_resy; ++y) {
				for (x = 0; x < common_resx; ++x) {
					memcpy(&ntty->stx_display[x + y * ntty->sta_resx],
					       &otty->stx_display[x + y * otty->sta_resx],
					       sizeof(struct svga_gfxcell));
				}
			}
		}
	}
}

/* Safely update the tty pointed-to by `self->sty_tty' */
INTERN BLOCKING NOCONNECT NONNULL((1, 2)) void FCALL
svgatty_settty(struct svgatty *__restrict self,
               struct svga_ttyaccess *__restrict ntty) {
	struct svga_ttyaccess *otty;
	struct svgadev *dev;

	/* One of the branches below wouldn't be NOEXCEPT if preemption wasn't enabled... */
	if (!PREEMPTION_ENABLED())
		THROW(E_WOULDBLOCK_PREEMPTED);
	dev = self->sty_dev;
	svga_chipset_acquire(&dev->svd_chipset);
	RAII_FINALLY { svga_chipset_release(&dev->svd_chipset); };
	otty = arref_ptr(&self->sty_tty);
	assertf(otty != ntty, "Only pass new ttys!");
	assertf(!isshared(ntty), "Only pass new ttys!");

	/* Mark the old tty as inactive. */
	atomic_lock_acquire(&otty->sta_lock);
	otty->sta_flags &= ~SVGA_TTYACCESS_F_ACTIVE;
	atomic_lock_release(&otty->sta_lock);

	/* If this tty is active, update the hardware video mode. */
	if (self->sty_active) {
		TRY {
			svgadev_setmode(dev, ntty->sta_mode);
		} EXCEPT {
			atomic_lock_acquire(&otty->sta_lock);
			otty->sta_flags |= SVGA_TTYACCESS_F_ACTIVE;
			(*otty->sta_activate)(otty);
			atomic_lock_release(&otty->sta_lock);
			RETHROW();
		}
	}

	/* Copy tty cell contents of d-buffers from `otty' to `ntty' */
	convert_tty_contents(otty, ntty);

	/* Copy some attributes from `otty' to `ntty' */
	assert(!(ntty->sta_flags & SVGA_TTYACCESS_F_EOL));
	ntty->sta_flags |= otty->sta_flags & SVGA_TTYACCESS_F_EOL;
	ntty->sta_cursor = otty->sta_cursor;
	if (ntty->sta_cursor.stc_cellx >= ntty->sta_resx)
		ntty->sta_cursor.stc_cellx = ntty->sta_resx - 1;
	if (ntty->sta_cursor.stc_celly >= ntty->sta_resy) {
		ntty->sta_cursor.stc_celly = ntty->sta_resy - 1;
		if (ntty->sta_flags & SVGA_TTYACCESS_F_EOL)
			ntty->sta_cursor.stc_celly = ntty->sta_resy;
	}
	ntty->sta_scroll_ystart = otty->sta_scroll_ystart;
	ntty->sta_scroll_yend   = otty->sta_scroll_yend;
	if (ntty->sta_scroll_ystart > ntty->sta_resy)
		ntty->sta_scroll_ystart = ntty->sta_resy;
	if (ntty->sta_scroll_yend > ntty->sta_resy)
		ntty->sta_scroll_yend = ntty->sta_resy;
	/* Special case: if the old tty's scroll region covered the whole
	 *               screen, then  let the  new  tty's do  the  same! */
	if (otty->sta_scroll_yend == otty->sta_resy)
		ntty->sta_scroll_yend = ntty->sta_resy;
	svga_ttyaccess__update_scrl(ntty);

	/* If this tty is active, mark the caller-given accessor as active. */
	atomic_lock_acquire(&ntty->sta_lock);
	assert(!(ntty->sta_flags & SVGA_TTYACCESS_F_ACTIVE));
	if (self->sty_active) {
		ntty->sta_flags |= SVGA_TTYACCESS_F_ACTIVE;
		/* Also invoke the accessor's activation-callback. */
		(*ntty->sta_activate)(ntty);
	}

	/* Remember the new tty as active. */
	arref_set(&self->sty_tty, ntty);
	atomic_lock_release(&ntty->sta_lock);
}




/* Set the SVGA video mode to `mode' */
INTERN NONNULL((1, 2)) void FCALL
svgadev_setmode(struct svgadev *__restrict self,
                struct svga_modeinfo const *__restrict mode)
		THROWS(E_IOERROR) {

	/* Set the video mode requested by `tty' */
	(*self->svd_chipset.sc_ops.sco_setmode)(&self->svd_chipset, mode);

	/* Load default VGA font if `tty' uses hardware text mode. */
	if (mode->smi_flags & SVGA_MODEINFO_F_TXT) {

		/* Enable palette access */
		vga_setpas(basevga_IS1_R, 0);

		/* Write attribute registers relating to palette values. */
		if (basevga_flags & BASEVGA_FLAG_ISEGA) {
			uint8_t i;
			baseega_registers.vm_att_color_page &= VGA_AT14_FRESERVED;
			baseega_registers.vm_att_color_page |= 0;
			vga_wattr(basevga_IS1_R, VGA_ATC_COLOR_PAGE, baseega_registers.vm_att_color_page);
			for (i = 0; i < 16; ++i) {
				uint8_t temp;
				temp = baseega_registers.vm_att_pal[i];
				temp &= VGA_ATC_PALETTEn_FRESERVED;
				temp |= i;
				vga_wattr(basevga_IS1_R, VGA_ATC_PALETTE0 + i, temp);
				baseega_registers.vm_att_pal[i] = temp;
			}
			baseega_registers.vm_att_mode &= ~VGA_AT10_FBLINK;
			baseega_registers.vm_att_mode |= VGA_AT10_FDUP9;
			vga_wattr(basevga_IS1_R, VGA_ATC_MODE, baseega_registers.vm_att_mode);
		} else {
			uint8_t i, temp;
			temp = vga_rattr(basevga_IS1_R, VGA_ATC_COLOR_PAGE);
			temp &= VGA_AT14_FRESERVED;
			vga_wattr(basevga_IS1_R, VGA_ATC_COLOR_PAGE, temp);
			for (i = 0; i < 16; ++i) {
				temp = vga_rattr(basevga_IS1_R, VGA_ATC_PALETTE0 + i);
				temp &= VGA_ATC_PALETTEn_FRESERVED;
				temp |= i;
				vga_wattr(basevga_IS1_R, VGA_ATC_PALETTE0 + i, temp);
			}

			/* Disable "blinky" if it was enabled by the chip.
			 * Also enable `VGA_AT10_FDUP9' while we're at it. */
			temp = vga_rattr(basevga_IS1_R, VGA_ATC_MODE);
			vga_wattr(basevga_IS1_R, VGA_ATC_MODE, (temp & ~VGA_AT10_FBLINK) | VGA_AT10_FDUP9);
		}

		/* Disable palette access */
		vga_setpas(basevga_IS1_R, VGA_ATT_IW_PAS);
	}

	/* Load an ANSI-compatible color palette (if used by this mode) */
	if (mode->smi_flags & SVGA_MODEINFO_F_PAL)
		basevga_wrpal(0, basevga_defaultpal, 16);
}



/* Return a reference to the currently "active" tty (or the one that will become
 * active after a currently held user-lock is released). If no such TTY  exists,
 * return NULL instead. */
INTERN BLOCKING NOCONNECT WUNUSED NONNULL((1)) REF struct svgatty *FCALL
svgadev_getactivetty(struct svgadev *__restrict self) {
	REF struct mfile *active;
again:
	active = awref_get(&self->svd_active);
	if (!active) {
		/* This can happen for 2 reasons:
		 *  - No TTY is active
		 *  - The active tty is being destroyed
		 *
		 * In the later case, we must want for the async destruction to finish! */
		if (awref_ptr(&self->svd_active) == NULL)
			return NULL;

		/* Because async destruction takes a write-lock to the chipset, we can
		 * just  wait for a write-lock to be released in order to wait for the
		 * active tty to finish unloading. */
		shared_lock_pollconnect(&self->svd_chipset.sc_lock);
		active = awref_get(&self->svd_active);
		if unlikely(active) {
			task_disconnectall();
			goto got_active;
		}
		task_waitfor();
		goto again;
	}
got_active:

	/* If the active obejct is a TTY, then we know that's the active TTY */
	if (svga_active_istty(active))
		return (REF struct svgatty *)mfile_asansitty(active);

	/* Last case: the active object is a userlock.
	 * In this case, return a reference to the tty that will be restored once that lock is released. */
	{
		struct svgalck *lck;
		REF struct svgatty *result;
		lck = (struct svgalck *)active;
		assert(lck->slc_dev == self);
		/* In order to read from `slc_oldtty', we need a lock to the chipset driver. */
		FINALLY_DECREF_UNLIKELY(lck);
		svga_chipset_acquire(&self->svd_chipset);
		result = (REF struct svgatty *)xincref(lck->slc_oldtty);
		svga_chipset_release(&self->svd_chipset);
		return result;
	}
}




/* Create a new  tty for a  given SVGA  device.
 * Note that the tty has yet to be made active! */
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) REF struct svgatty *FCALL
svgadev_vnewttyf(struct svgadev *__restrict self,
                 struct svga_modeinfo const *__restrict mode, dev_t devno,
                 char const *__restrict format, __builtin_va_list args)
		THROWS(E_WOULDBLOCK) {
	REF struct svgatty *result;
	/* Allocate a new TTY object. */
	result = (REF struct svgatty *)kmalloc(sizeof(struct svgatty), GFP_NORMAL);

	/* Initialize basic fields. */
	incref(self); /* For `result->sty_dev' */
	result->sty_dev    = self;
	result->sty_active = 0; /* Not active by default. */
	result->sty_oldtty = NULL;
	result->fn_mode   = S_IFCHR | 0600;
	result->dv_driver = incref(&drv_self);
	_ansittydev_init(result, &svgatty_ops, &svga_ansitty_ops);
	TRY {
		REF struct svga_ttyaccess *tty;
		/* Allocate a tty-access object for the default TTY */
		tty = svgadev_makettyaccess(self, mode);
		arref_init(&result->sty_tty, tty);

		TRY {
			/* Register the device. */
			device_vregisterf(result, devno, format, args);
		} EXCEPT {
			destroy(arref_ptr(&result->sty_tty));
			RETHROW();
		}
	} EXCEPT {
		_ansittydev_fini(result);
		decref_nokill(&drv_self);
		decref_nokill(self);
		kfree(result);
		RETHROW();
	}

	/* SVGA-tty objects get  auto-destroyed once they're  no longer  referenced.
	 * Because `device_registerf()' set the GLOBAL bit, we simply clear it here. */
	if (ATOMIC_FETCHAND(result->mf_flags, ~MFILE_FN_GLOBAL_REF) & MFILE_FN_GLOBAL_REF)
		decref_nokill(result);
	return result;
}

INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) REF struct svgatty *VCALL
svgadev_newttyf(struct svgadev *__restrict self,
                struct svga_modeinfo const *__restrict mode, dev_t devno,
                char const *__restrict format, ...)
		THROWS(E_WOULDBLOCK) {
	REF struct svgatty *result;
	va_list args;
	va_start(args, format);
	RAII_FINALLY { va_end(args); };
	result = svgadev_vnewttyf(self, mode, devno, format, args);
	return result;
}

/* Activate a given TTY. If an active userlock exists, the tty will not actually
 * be  made active, but will instead be  linked such that the userlock's release
 * will make the tty active. */
INTERN BLOCKING NONNULL((1, 2)) void FCALL
svgadev_activate_tty(struct svgadev *__restrict self,
                     struct svgatty *__restrict tty)
		THROWS(E_WOULDBLOCK) {
	struct svga_ttyaccess *nt;
	REF struct mfile *old_active;
	struct svgatty *oldtty;
	/* One of the branches below wouldn't be NOEXCEPT if preemption wasn't enabled... */
	if (!PREEMPTION_ENABLED())
		THROW(E_WOULDBLOCK_PREEMPTED);
again:
	old_active = awref_get(&self->svd_active);
	if (!old_active) {
		if (awref_ptr(&self->svd_active) == NULL)
			goto got_old_active; /* Initial activation. */
		/* Because async destruction takes a write-lock to the chipset, we can
		 * just  wait for a write-lock to be released in order to wait for the
		 * active tty to finish unloading. */
		shared_lock_pollconnect(&self->svd_chipset.sc_lock);
		old_active = awref_get(&self->svd_active);
		if unlikely(old_active) {
			task_disconnectall();
			goto got_old_active;
		}
		task_waitfor();
		goto again;
	}
got_old_active:

	/* Acquire a lock to the chipset. */
	FINALLY_XDECREF_UNLIKELY(old_active);
	svga_chipset_acquire(&self->svd_chipset);
	RAII_FINALLY { svga_chipset_release(&self->svd_chipset); };

	/* Check if the active object changed. */
	COMPILER_READ_BARRIER();
	if (awref_ptr(&self->svd_active) != old_active)
		goto again; /* Try again... */

	/* Special handling when the active object is a user-lock. */
	if (old_active && svga_active_islock(old_active)) {
		struct svgalck *lck;
		lck = (struct svgalck *)old_active;
		assert(lck->slc_dev == self);
		incref(tty); /* For `lck->slc_oldtty' */

		/* Check if `tty' is already part of the restore  chain.
		 * If so, remove it before re-inserting it at the front. */
		if (lck->slc_oldtty) {
			struct svgatty **p_iter, *iter;
			p_iter = &lck->slc_oldtty;
			while ((iter = *p_iter) != NULL) {
				if (iter == tty) {
					*p_iter = tty->sty_oldtty; /* Unlink. */
					decref_nokill(tty);
					break;
				}
				p_iter = &iter->sty_oldtty;
			}
			/* Append the list of old ttys to the end `tty' */
			if (lck->slc_oldtty) {
				struct svgatty *last_tty;
				last_tty = container_of(p_iter, struct svgatty, sty_oldtty);
				last_tty->sty_oldtty = tty->sty_oldtty;
				tty->sty_oldtty      = lck->slc_oldtty;
			}
		}
		lck->slc_oldtty = tty;
		return;
	}

	/* No userlock is active. -> activate this tty. */
	oldtty = (struct svgatty *)old_active;

	/* Mark the old tty as inactive. */
	if (oldtty) {
		struct svga_ttyaccess *ot;
		assert(oldtty->sty_active);
		ot = arref_ptr(&oldtty->sty_tty); /* This can't change because we're holding the chipset lock! */
		atomic_lock_acquire(&ot->sta_lock);
		assert(ot->sta_flags & SVGA_TTYACCESS_F_ACTIVE);
		ot->sta_flags &= ~SVGA_TTYACCESS_F_ACTIVE;
		oldtty->sty_active = 0;
		atomic_lock_release(&ot->sta_lock);
	}

	/* Load the video mode of the caller's tty. */
	nt = arref_ptr(&tty->sty_tty); /* This can't change because we're holding the chipset lock! */
	TRY {
		svgadev_setmode(self, nt->sta_mode);
	} EXCEPT {
		/* NOTE: This right here assumes that `svgadev_setmode()' throwing
		 *       didn't  leave  chipset registers  in an  undefined state! */
		if (oldtty) {
			struct svga_ttyaccess *ot;
			ot = arref_ptr(&oldtty->sty_tty);   /* This can't change because we're holding the chipset lock! */
			atomic_lock_acquire(&ot->sta_lock); /* NOTHROW because preemption is enabled (s.a. above) */
			oldtty->sty_active = 1;
			ot->sta_flags |= SVGA_TTYACCESS_F_ACTIVE;
			(*ot->sta_activate)(ot);
			atomic_lock_release(&ot->sta_lock);
		}
		RETHROW();
	}
	/* NOTHROW FROM HERE ON! */

	/* Activate the tty accessor for the new active TTY */
	atomic_lock_acquire(&nt->sta_lock); /* NOTHROW because preemption is enabled (s.a. above) */
	nt->sta_flags |= SVGA_TTYACCESS_F_ACTIVE;
	tty->sty_active = 1;
	(*nt->sta_activate)(nt);
	atomic_lock_release(&nt->sta_lock);

	/* Link old tty into restore list. */
	if (oldtty) {
		if (tty->sty_oldtty) {
			struct svgatty **p_iter, *iter;
			p_iter = &tty->sty_oldtty;
			while ((iter = *p_iter) != NULL) {
				if (iter == oldtty) {
					*p_iter = oldtty->sty_oldtty; /* Unlink. */
					decref_nokill(oldtty);
					break;
				}
				p_iter = &iter->sty_oldtty;
			}
			/* Append the list of old ttys to the end `tty' */
			if (tty->sty_oldtty) {
				struct svgatty *last_tty;
				last_tty = container_of(p_iter, struct svgatty, sty_oldtty);
				last_tty->sty_oldtty = oldtty->sty_oldtty;
				oldtty->sty_oldtty = tty->sty_oldtty;
			}
		}

		/* Set-up the old-tty-restore link. */
		incref(oldtty);
		tty->sty_oldtty = oldtty;
	}

	/* Set as active. */
	awref_set(&self->svd_active, tty);
}

/* Allocate  and activate a new userlock for a given SVGA device.
 * If another lock already exists, this function will block until
 * said lock is released. */
INTERN BLOCKING NOCONNECT ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct svgalck *FCALL
svgadev_newuserlock(struct svgadev *__restrict self)
		THROWS(E_WOULDBLOCK) {
	REF struct svgalck *result;
	/* One of the branches below wouldn't be NOEXCEPT if preemption wasn't enabled... */
	if (!PREEMPTION_ENABLED())
		THROW(E_WOULDBLOCK_PREEMPTED);
	result = (REF struct svgalck *)kmalloc(offsetof(struct svgalck, slc_xregs) +
	                                       self->svd_chipset.sc_ops.sco_regsize,
	                                       GFP_NORMAL);
	TRY {
		REF struct mfile *active;
		struct svgatty *active_tty;
again:
		active = awref_get(&self->svd_active);
		if (!active) {
			if (awref_ptr(&self->svd_active) == NULL)
				goto got_active;
			/* wait for the lock to fully go again. */
			shared_lock_pollconnect(&self->svd_chipset.sc_lock);
			active = awref_get(&self->svd_active);
			if unlikely(active) {
				task_disconnectall();
				goto got_active;
			}
			task_waitfor();
			goto again;
		}
got_active:

		/* Check if the active object is another lock. */
		FINALLY_XDECREF_UNLIKELY(active);
		if (active && svga_active_islock(active)) {
			/* Wait for the lock to go away. */
			shared_lock_pollconnect(&self->svd_chipset.sc_lock);
			if (awref_ptr(&self->svd_active) != active) {
				task_disconnectall();
				goto again;
			}
			task_waitfor();
			goto again;
		}
		assert(!active || svga_active_istty(active));
		active_tty = (struct svgatty *)mfile_asansitty(active);

		/* All right! Now get a lock to the chipset and
		 * check  that the active object didn't change. */
		svga_chipset_acquire(&self->svd_chipset);
		RAII_FINALLY { svga_chipset_release(&self->svd_chipset); };
		if unlikely(awref_ptr(&self->svd_active) != active_tty)
			goto again;

		/* Disable the active tty. */
		if (active_tty) {
			struct svga_ttyaccess *tty;
			tty = arref_ptr(&active_tty->sty_tty);
			atomic_lock_acquire(&tty->sta_lock);
			assert(active_tty->sty_active);
			assert(tty->sta_flags & SVGA_TTYACCESS_F_ACTIVE);
			tty->sta_flags &= ~SVGA_TTYACCESS_F_ACTIVE;
			active_tty->sty_active = 0;
			atomic_lock_release(&tty->sta_lock);
		}
		TRY {
			/* Save Base-VGA registers. */
			basevga_getregs(&result->slc_vmode);

			/* Save chipset-specific registers. */
			(*self->svd_chipset.sc_ops.sco_getregs)(&self->svd_chipset, result->slc_xregs);
		} EXCEPT {
			/* Re-activate the old TTY */
			if (active_tty) {
				struct svga_ttyaccess *tty;
				tty = arref_ptr(&active_tty->sty_tty);
				atomic_lock_acquire(&tty->sta_lock); /* NOTHROW because preemption is enabled! */
				tty->sta_flags |= SVGA_TTYACCESS_F_ACTIVE;
				active_tty->sty_active = 1;
				(*tty->sta_activate)(tty);
				atomic_lock_release(&tty->sta_lock);
			}
			RETHROW();
		}

		/* NOEXCEPT FROM HERE ON! */

		/* Fill remaining fields. */
		_mfile_init(result, &svgalck_ops, PAGESHIFT, PAGESHIFT);
		result->mf_parts             = MFILE_PARTS_ANONYMOUS;
		result->mf_changed.slh_first = MFILE_PARTS_ANONYMOUS;
		result->mf_flags = MFILE_F_READONLY | MFILE_F_ATTRCHANGED | MFILE_F_CHANGED |
		                   MFILE_F_NOATIME | MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO |
		                   MFILE_F_NOMTIME | MFILE_F_FIXEDFILESIZE;
		atomic64_init(&result->mf_filesize,
		              sizeof(struct vga_mode) +
		              self->svd_chipset.sc_ops.sco_regsize);
		result->mf_atime = realtime();
		result->mf_mtime = result->mf_atime;
		result->mf_ctime = result->mf_atime;
		incref(self);       /* For `result->slc_dev' */
		incref(active_tty); /* For `result->slc_oldtty' */
		result->slc_dev    = self;
		result->slc_oldtty = active_tty;
		result->slc_mode   = NULL; /* No video mode override (yet) */

		/* If we're overriding  an active TTY,  then
		 * we know what the previous video-mode was! */
		if (active_tty != NULL)
			result->slc_mode = arref_ptr(&active_tty->sty_tty)->sta_mode;
		DBG_memset(&result->slc_rstor, 0xcc, sizeof(result->slc_rstor));

		/* Remember that `result' is now active. */
		awref_set(&self->svd_active, result);
	} EXCEPT {
		kfree(result);
		RETHROW();
	}
	return result;
}









/************************************************************************/
/* Operators for the SVGA ansitty devices.                              */
/************************************************************************/
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL svgatty_async_v_destroy)(struct async *__restrict self) {
	struct svgatty *me = _svgatty_fromasyncrestore(self);

	/* Clear remaining references. */
	decref_unlikely(me->sty_dev);
	xdecref_unlikely(me->sty_oldtty);

	/* Destroy the original underlying character-device. */
	chrdev_v_destroy(me);
}

PRIVATE NONNULL((1)) ktime_t FCALL
svgatty_async_v_connect(struct async *__restrict self) {
	struct svgatty *me = _svgatty_fromasyncrestore(self);
	shared_lock_pollconnect(&me->sty_dev->svd_chipset.sc_lock);
	return KTIME_INFINITE;
}

PRIVATE WUNUSED NONNULL((1)) bool FCALL
svgatty_async_v_test(struct async *__restrict self) {
	struct svgatty *me = _svgatty_fromasyncrestore(self);
	return svga_chipset_available(&me->sty_dev->svd_chipset);
}

PRIVATE WUNUSED NONNULL((1)) unsigned int FCALL
svgatty_async_v_work(struct async *__restrict self) {
	struct svgatty *me = _svgatty_fromasyncrestore(self);
	struct svgatty *nt = me->sty_oldtty;
	struct svgadev *dv = me->sty_dev;
	struct svga_ttyaccess *ac;
	assert(PREEMPTION_ENABLED());
	if (!svga_chipset_tryacquire(&dv->svd_chipset))
		return ASYNC_RESUME;
	RAII_FINALLY { svga_chipset_release(&dv->svd_chipset); };
	assert(me->sty_active);
	assert(awref_ptr(&dv->svd_active) == me);

	/* Set the video mode used by `nt'
	 * NOTE: Because we're holding a lock to `dv', the tty access object can't change! */
	ac = arref_ptr(&nt->sty_tty);
	assert(!wasdestroyed(ac));
	assert(!(ac->sta_flags & SVGA_TTYACCESS_F_ACTIVE));
	assert(!nt->sty_active);
	svgadev_setmode(dv, ac->sta_mode);

	/* Mark the tty as active. */
	atomic_lock_acquire(&ac->sta_lock);       /* This can't throw because preemption is enabled. */
	ac->sta_flags |= SVGA_TTYACCESS_F_ACTIVE; /* Mark TTY accessor as active */
	nt->sty_active = 1;                       /* Mark TTY as active */
	(*ac->sta_activate)(ac);                  /* This is NOBLOCK+NOTHROW */
	awref_set(&dv->svd_active, nt);           /* Remember TTY as active */
	atomic_lock_release(&ac->sta_lock);
	return ASYNC_FINISHED;
}


PRIVATE struct async_ops const svgatty_async_v_ops = {
	.ao_driver  = &drv_self,
	.ao_destroy = &svgatty_async_v_destroy,
	.ao_connect = &svgatty_async_v_connect,
	.ao_test    = &svgatty_async_v_test,
	.ao_work    = &svgatty_async_v_work,
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL svgatty_v_destroy)(struct mfile *__restrict self) {
	struct async *rstor;
	struct svgatty *me = (struct svgatty *)mfile_aschrdev(self);
	arref_fini(&me->sty_tty);
	if (!me->sty_active) {
		ansittydev_v_destroy(self);
		return;
	}
	/* NOTE: ansitty-specific fields would have to be finalized here,
	 *       but none of those require any special finalization as of
	 *       right now. */

	/* Setup an async job to restore another tty. */
	rstor = _svgatty_toasyncrestore(me);
	async_init(rstor, &svgatty_async_v_ops);
	decref_unlikely(async_start(rstor));
}

PRIVATE NONNULL((1)) syscall_slong_t KCALL
svgatty_ioctl_getmode(struct svgatty *__restrict self,
                      USER UNCHECKED struct svga_modeinfo *modeinfo) {
	REF struct svga_ttyaccess *tty;
	validate_writable(modeinfo, sizeof(*modeinfo));
	tty = arref_get(&self->sty_tty);
	FINALLY_DECREF_UNLIKELY(tty);
	memcpy(modeinfo, tty->sta_mode, sizeof(struct svga_modeinfo));
	return 0;
}

PRIVATE NONNULL((1)) syscall_slong_t KCALL
svgatty_ioctl_setmode(struct svgatty *__restrict self,
                      USER UNCHECKED struct svga_modeinfo const *modeinfo) {
	REF struct svga_ttyaccess *newtty;
	struct svga_modeinfo const *newmode;
	validate_readable(modeinfo, sizeof(*modeinfo));

	/* New special permissions to set the video mode.
	 * For this purpose, you need to be allowed to also do this on your own! */
	require(CAP_SYS_RAWIO);

	/* Lookup the requested mode. */
	newmode = svgadev_findmode(self->sty_dev, modeinfo);

	/* Allocate a new tty */
	newtty = svgadev_makettyaccess(self->sty_dev, newmode);
	FINALLY_DECREF_UNLIKELY(newtty);

	/* Set the new tty. */
	svgatty_settty(self, newtty);
	return 0;
}


PRIVATE NONNULL((1)) syscall_slong_t KCALL
svgatty_v_ioctl(struct mfile *__restrict self, syscall_ulong_t cmd,
                USER UNCHECKED void *arg, iomode_t mode) THROWS(...) {
	struct svgatty *me = (struct svgatty *)mfile_asansitty(self);
	switch (cmd) {

	case SVGA_IOC_ACTIVATE:
		require(CAP_SYS_RAWIO);
		svgadev_activate_tty(me->sty_dev, me);
		break;

	case SVGA_IOC_GETMODE:
		return svgatty_ioctl_getmode(me, (USER UNCHECKED struct svga_modeinfo *)arg);

	case SVGA_IOC_SETMODE:
		return svgatty_ioctl_setmode(me, (USER UNCHECKED struct svga_modeinfo const *)arg);

	case SVGA_IOC_GETDEFMODE:
		return svgadev_ioctl_getdefmode(me->sty_dev, (USER UNCHECKED struct svga_modeinfo *)arg);
	case SVGA_IOC_SETDEFMODE:
		return svgadev_ioctl_setdefmode(me->sty_dev, (USER UNCHECKED struct svga_modeinfo const *)arg);
	case SVGA_IOC_LSMODES:
		return svgadev_ioctl_lsmodes(me->sty_dev, (USER UNCHECKED struct svga_lsmodes *)arg);
	case SVGA_IOC_GETCSNAME:
		return svgadev_ioctl_getcsname(me->sty_dev, (USER UNCHECKED char *)arg);
	case SVGA_IOC_CSSTRINGS:
		return svgadev_ioctl_getcsstrings(me->sty_dev, (USER UNCHECKED struct svga_strings *)arg);

	default:
		return ansittydev_v_ioctl(self, cmd, arg, mode);
		break;
	}
	return 0;
}

/* SVGA TTY device operators. */
PRIVATE struct mfile_stream_ops const svgatty_v_stream_ops = {
	.mso_write = &ansittydev_v_write,
	.mso_ioctl = &svgatty_v_ioctl,
	.mso_hop   = &ansittydev_v_hop,
	.mso_tryas = &ansittydev_v_tryas,
};

INTERN_CONST struct ansittydev_ops const svgatty_ops = {{{{{
	.no_file = {
		.mo_destroy = &svgatty_v_destroy,
		.mo_changed = &ansittydev_v_changed,
		.mo_stream  = &svgatty_v_stream_ops,
	},
	.no_wrattr = &ansittydev_v_wrattr,
}}}}};






/************************************************************************/
/* Operators for the primary SVGA device.                               */
/************************************************************************/
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL svgadev_v_destroy)(struct mfile *__restrict self) {
	struct svgadev *me = (struct svgadev *)mfile_aschrdev(self);
	kfree((void *)me->svd_supmodev);
	(*me->svd_chipset.sc_ops.sco_fini)(&me->svd_chipset);
	chrdev_v_destroy(self);
}

PRIVATE NONNULL((1)) syscall_slong_t KCALL
svgadev_v_ioctl(struct mfile *__restrict self, syscall_ulong_t cmd,
                USER UNCHECKED void *arg, iomode_t mode) THROWS(...) {
	struct svgadev *me = (struct svgadev *)mfile_asansitty(self);
	switch (cmd) {

	case SVGA_IOC_GETMODE:
	case SVGA_IOC_SETMODE: {
		/* Forward  these ioctls to the currently "active" tty,
		 * or the tty that will become active once a video lock
		 * is released. */
		REF struct svgatty *tty;
		tty = svgadev_getactivetty(me);
		if unlikely(!tty)
			THROW(E_NO_SUCH_OBJECT);
		FINALLY_DECREF_UNLIKELY(tty);
		return svgatty_v_ioctl(tty, cmd, arg, mode);
	}	break;

	case SVGA_IOC_GETDEFMODE:
		return svgadev_ioctl_getdefmode(me, (USER UNCHECKED struct svga_modeinfo *)arg);
	case SVGA_IOC_SETDEFMODE:
		return svgadev_ioctl_setdefmode(me, (USER UNCHECKED struct svga_modeinfo const *)arg);
	case SVGA_IOC_LSMODES:
		return svgadev_ioctl_lsmodes(me, (USER UNCHECKED struct svga_lsmodes *)arg);
	case SVGA_IOC_GETCSNAME:
		return svgadev_ioctl_getcsname(me, (USER UNCHECKED char *)arg);
	case SVGA_IOC_CSSTRINGS:
		return svgadev_ioctl_getcsstrings(me, (USER UNCHECKED struct svga_strings *)arg);

	case SVGA_IOC_MAKETTY: {
		USER CHECKED struct svga_maketty *info;
		USER CHECKED char const *name;
		struct handle hand;
		REF struct svgatty *tty;
		require(CAP_SYS_RAWIO);
		info = (USER CHECKED struct svga_maketty *)arg;
		validate_readable(info, sizeof(*info));
		name = ATOMIC_READ(info->smt_name);
		validate_readable(name, 1);
		/* Create the new TTY */
		tty = svgadev_newttyf(me, svgadev_findmode(me, &info->smt_mode),
		                      MKDEV(DEV_MAJOR_AUTO, 0), "%s", name);
		FINALLY_DECREF_UNLIKELY(tty);
		hand.h_type = HANDLE_TYPE_MFILE;
		hand.h_mode = IO_RDWR;
		hand.h_data = tty;
		return handle_installhop(&info->smt_res, hand);
	}	break;

	case SVGA_IOC_MAKELCK: {
		struct handle hand;
		REF struct svgalck *lck;

		/* Require raw I/O.  - Without  this, the  lock
		 * probably wouldn't do you any good anyways... */
		require(CAP_SYS_RAWIO);

		/* Create lock object. */
		lck = svgadev_newuserlock(me);
		FINALLY_DECREF_UNLIKELY(lck);

		/* Store lock object in a handle. */
		hand.h_type = HANDLE_TYPE_MFILE;
		hand.h_mode = IO_RDWR;
		hand.h_data = lck;
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, hand);
	}	break;

	default:
		return chrdev_v_ioctl(self, cmd, arg, mode);
		break;
	}
	return 0;
}


PRIVATE BLOCKING WUNUSED NONNULL((1)) size_t KCALL
svgadev_v_write(struct mfile *__restrict self, USER CHECKED void const *src,
                size_t num_bytes, iomode_t mode) THROWS(...) {
	/* Writes to an SVGA master device go to the currently active tty. */
	struct svgadev *me = (struct svgadev *)mfile_asansitty(self);
	REF struct svgatty *tty;
	tty = svgadev_getactivetty(me);
	if unlikely(!tty)
		return 0; /* Indicate EOF */
	FINALLY_DECREF_UNLIKELY(tty);
	assert(tty->mf_ops->mo_stream != NULL &&
	       tty->mf_ops->mo_stream->mso_write == &ansittydev_v_write);
	return ansittydev_v_write(tty, src, num_bytes, mode);
}

PRIVATE BLOCKING WUNUSED NONNULL((1)) size_t KCALL
svgadev_v_writev(struct mfile *__restrict self, struct iov_buffer *__restrict src,
                 size_t num_bytes, iomode_t mode) THROWS(...) {
	/* Writes to an SVGA master device go to the currently active tty. */
	struct svgadev *me = (struct svgadev *)mfile_asansitty(self);
	REF struct svgatty *tty;
	tty = svgadev_getactivetty(me);
	if unlikely(!tty)
		return 0; /* Indicate EOF */
	FINALLY_DECREF_UNLIKELY(tty);
	assert(tty->mf_ops->mo_stream != NULL &&
	       tty->mf_ops->mo_stream->mso_write == &ansittydev_v_write);
	return mfile_uwritev(tty, src, num_bytes, mode);
}


PRIVATE struct mfile_stream_ops const svgadev_v_stream_ops = {
	.mso_write  = &svgadev_v_write,
	.mso_writev = &svgadev_v_writev,
	.mso_ioctl  = &svgadev_v_ioctl,
	.mso_hop    = &chrdev_v_hop,
	.mso_tryas  = &chrdev_v_tryas,
};

/* Operators for `struct svgadev' */
INTERN_CONST struct chrdev_ops const svgadev_ops = {{{{
	.no_file = {
		.mo_destroy = &svgadev_v_destroy,
		.mo_changed = &chrdev_v_changed,
		.mo_stream  = &svgadev_v_stream_ops,
	},
	.no_wrattr = &chrdev_v_wrattr,
}}}};



DECL_END

#endif /* !GUARD_MODSVGA_MODE_C */
