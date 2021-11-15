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
		viddev_acquire(self);
		RAII_FINALLY { viddev_release(self); };
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
PRIVATE BLOCKING NONNULL((1)) void FCALL
svgalck_v_restore(struct vidlck *__restrict self,
                  struct viddev *__restrict dev)
		THROWS(E_IOERROR) {
	struct svgalck *me = vidlck_assvga(self);
	struct svgadev *dv = viddev_assvga(dev);

	/* Restore chipset-specific registers. */
	(*dv->svd_chipset.sc_ops.sco_setregs)(&dv->svd_chipset, me->slc_xregs);

	/* Restore base-vga registers. */
	basevga_setregs(&me->slc_vmode);
}


PRIVATE NONNULL((1)) syscall_slong_t KCALL
svgalck_v_ioctl(struct mfile *__restrict self, syscall_ulong_t cmd,
                USER UNCHECKED void *arg, iomode_t mode) THROWS(...) {
	struct svgalck *me = vidlck_assvga(self);
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
		struct svgadev *dv = viddev_assvga(me->vlc_dev);
		struct svga_modeinfo const *newmode;
		validate_readable(arg, sizeof(struct svga_modeinfo));
		newmode = svgadev_findmode(viddev_assvga(me->vlc_dev), (USER CHECKED struct svga_modeinfo *)arg);
		viddev_acquire(dv);
		RAII_FINALLY { viddev_release(dv); };

		/* Set new video mode. */
		svgadev_setmode(dv, newmode);

		/* For text modes, also load the default font! */
		if (newmode->smi_flags & SVGA_MODEINFO_F_TXT)
			basevga_wrvmem(0x20000, basevga_defaultfont, sizeof(basevga_defaultfont));

		/* Remember last-set mode. */
		ATOMIC_WRITE(me->slc_mode, newmode);
	}	break;

	case SVGA_IOC_GETDEFMODE:
		return svgadev_ioctl_getdefmode(viddev_assvga(me->vlc_dev), (USER UNCHECKED struct svga_modeinfo *)arg);
	case SVGA_IOC_SETDEFMODE:
		return svgadev_ioctl_setdefmode(viddev_assvga(me->vlc_dev), (USER UNCHECKED struct svga_modeinfo const *)arg);
	case SVGA_IOC_LSMODES:
		return svgadev_ioctl_lsmodes(viddev_assvga(me->vlc_dev), (USER UNCHECKED struct svga_lsmodes *)arg);
	case SVGA_IOC_GETCSNAME:
		return svgadev_ioctl_getcsname(viddev_assvga(me->vlc_dev), (USER UNCHECKED char *)arg);
	case SVGA_IOC_CSSTRINGS:
		return svgadev_ioctl_getcsstrings(viddev_assvga(me->vlc_dev), (USER UNCHECKED struct svga_strings *)arg);

	default:
		return vidlck_v_ioctl(self, cmd, arg, mode);
		break;
	}
	return 0;
}


PRIVATE struct mfile_stream_ops const svgalck_v_stream_ops = {
	.mso_ioctl = &svgalck_v_ioctl,
	.mso_hop   = &vidlck_v_hop,
	/* TODO: mmap (including support for automatic bank switching) */
};

INTERN_CONST struct vidlck_ops const svgalck_ops = {
	.vlo_file = {
		.mo_destroy = &vidlck_v_destroy,
		.mo_stream  = &svgalck_v_stream_ops,
	},
	.vlo_restore = &svgalck_v_restore,
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
	common_resx = _otty->vta_resx;
	common_resy = _otty->vta_resy;
	if (common_resx > _ntty->vta_resx)
		common_resx = _ntty->vta_resx;
	if (common_resy > _ntty->vta_resy)
		common_resy = _ntty->vta_resy;
	if (svga_ttyaccess_istxt(_otty)) {
		struct svga_ttyaccess_txt *otty;
		otty = (struct svga_ttyaccess_txt *)_otty;
		if (svga_ttyaccess_istxt(_ntty)) {
			struct svga_ttyaccess_txt *ntty;
			ntty = (struct svga_ttyaccess_txt *)_ntty;
			for (y = 0; y < common_resy; ++y) {
				for (x = 0; x < common_resx; ++x) {
					uint16_t cell;
					cell = otty->stt_display[x + y * otty->vta_scan];
					ntty->stt_display[x + y * ntty->vta_scan] = cell;
				}
			}
		} else {
			struct svga_ttyaccess_gfx *ntty;
			ntty = (struct svga_ttyaccess_gfx *)_ntty;
			for (y = 0; y < common_resy; ++y) {
				for (x = 0; x < common_resx; ++x) {
					uint16_t cell = otty->stt_display[x + y * otty->vta_scan];
					memcpy(ntty->stx_display[x + y * ntty->vta_resx].sgc_lines,
					       basevga_defaultfont[cell & 0xff], 16);
					ntty->stx_display[x + y * ntty->vta_resx].sgc_color = (cell >> 8) & 0xff;
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
					cell = &otty->stx_display[x + y * otty->vta_scan];
					word = cell->sgc_color << 8;
					word |= try_ocr_on_gfxcell(cell);
					ntty->stt_display[x + y * ntty->vta_scan] = word;
				}
			}
		} else {
			struct svga_ttyaccess_gfx *ntty;
			ntty = (struct svga_ttyaccess_gfx *)_ntty;
			for (y = 0; y < common_resy; ++y) {
				for (x = 0; x < common_resx; ++x) {
					memcpy(&ntty->stx_display[x + y * ntty->vta_resx],
					       &otty->stx_display[x + y * otty->vta_resx],
					       sizeof(struct svga_gfxcell));
				}
			}
		}
	}
}

/* Safely update the tty pointed-to by `self->vty_tty' */
INTERN BLOCKING NOCONNECT NONNULL((1, 2)) void FCALL
svgatty_settty(struct svgatty *__restrict self,
               struct svga_ttyaccess *__restrict ntty) {
	struct svga_ttyaccess *otty;
	struct svgadev *dev;

	/* One of the branches below wouldn't be NOEXCEPT if preemption wasn't enabled... */
	if (!PREEMPTION_ENABLED())
		THROW(E_WOULDBLOCK_PREEMPTED);
	dev = viddev_assvga(self->vty_dev);
	viddev_acquire(dev);
	RAII_FINALLY { viddev_release(dev); };
	otty = vidttyaccess_assvga(arref_ptr(&self->vty_tty));
	assertf(otty != ntty, "Only pass new ttys!");
	assertf(!isshared(ntty), "Only pass new ttys!");

	/* Mark the old tty as inactive. */
	atomic_lock_acquire(&otty->vta_lock);
	otty->vta_flags &= ~VIDTTYACCESS_F_ACTIVE;
	atomic_lock_release(&otty->vta_lock);

	/* If this tty is active, update the hardware video mode. */
	if (self->vty_active) {
		TRY {
			svgadev_setmode(dev, ntty->sta_mode);
		} EXCEPT {
			atomic_lock_acquire(&otty->vta_lock);
			otty->vta_flags |= VIDTTYACCESS_F_ACTIVE;
			(*otty->vta_activate)(otty);
			atomic_lock_release(&otty->vta_lock);
			RETHROW();
		}
	}

	/* Copy tty cell contents of d-buffers from `otty' to `ntty' */
	convert_tty_contents(otty, ntty);

	/* Copy some attributes from `otty' to `ntty' */
	assert(!(ntty->vta_flags & VIDTTYACCESS_F_EOL));
	ntty->vta_flags |= otty->vta_flags & VIDTTYACCESS_F_EOL;
	ntty->vta_cursor = otty->vta_cursor;
	if (ntty->vta_cursor.vtc_cellx >= ntty->vta_resx)
		ntty->vta_cursor.vtc_cellx = ntty->vta_resx - 1;
	if (ntty->vta_cursor.vtc_celly >= ntty->vta_resy) {
		ntty->vta_cursor.vtc_celly = ntty->vta_resy - 1;
		if (ntty->vta_flags & VIDTTYACCESS_F_EOL)
			ntty->vta_cursor.vtc_celly = ntty->vta_resy;
	}
	ntty->vta_scroll_ystart = otty->vta_scroll_ystart;
	ntty->vta_scroll_yend   = otty->vta_scroll_yend;
	if (ntty->vta_scroll_ystart > ntty->vta_resy)
		ntty->vta_scroll_ystart = ntty->vta_resy;
	if (ntty->vta_scroll_yend > ntty->vta_resy)
		ntty->vta_scroll_yend = ntty->vta_resy;
	/* Special case: if the old tty's scroll region covered the whole
	 *               screen, then  let the  new  tty's do  the  same! */
	if (otty->vta_scroll_yend == otty->vta_resy)
		ntty->vta_scroll_yend = ntty->vta_resy;
	_vidttyaccess_update_scrl(ntty);

	/* If this tty is active, mark the caller-given accessor as active. */
	atomic_lock_acquire(&ntty->vta_lock);
	assert(!(ntty->vta_flags & VIDTTYACCESS_F_ACTIVE));
	if (self->vty_active) {
		ntty->vta_flags |= VIDTTYACCESS_F_ACTIVE;
		/* Also invoke the accessor's activation-callback. */
		(*ntty->vta_activate)(ntty);
	}

	/* Remember the new tty as active. */
	arref_set(&self->vty_tty, ntty);
	atomic_lock_release(&ntty->vta_lock);
}









/************************************************************************/
/* Operators for the SVGA ansitty devices.                              */
/************************************************************************/
PRIVATE NONNULL((1)) syscall_slong_t KCALL
svgatty_ioctl_getmode(struct svgatty *__restrict self,
                      USER UNCHECKED struct svga_modeinfo *modeinfo) {
	REF struct svga_ttyaccess *tty;
	validate_writable(modeinfo, sizeof(*modeinfo));
	tty = vidttyaccess_assvga(arref_get(&self->vty_tty));
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
	newmode = svgadev_findmode(viddev_assvga(self->vty_dev), modeinfo);

	/* Allocate a new tty */
	newtty = svgadev_makettyaccess(viddev_assvga(self->vty_dev), newmode);
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

	case SVGA_IOC_GETMODE:
		return svgatty_ioctl_getmode(me, (USER UNCHECKED struct svga_modeinfo *)arg);
	case SVGA_IOC_SETMODE:
		return svgatty_ioctl_setmode(me, (USER UNCHECKED struct svga_modeinfo const *)arg);
	case SVGA_IOC_GETDEFMODE:
		return svgadev_ioctl_getdefmode(viddev_assvga(me->vty_dev), (USER UNCHECKED struct svga_modeinfo *)arg);
	case SVGA_IOC_SETDEFMODE:
		return svgadev_ioctl_setdefmode(viddev_assvga(me->vty_dev), (USER UNCHECKED struct svga_modeinfo const *)arg);
	case SVGA_IOC_LSMODES:
		return svgadev_ioctl_lsmodes(viddev_assvga(me->vty_dev), (USER UNCHECKED struct svga_lsmodes *)arg);
	case SVGA_IOC_GETCSNAME:
		return svgadev_ioctl_getcsname(viddev_assvga(me->vty_dev), (USER UNCHECKED char *)arg);
	case SVGA_IOC_CSSTRINGS:
		return svgadev_ioctl_getcsstrings(viddev_assvga(me->vty_dev), (USER UNCHECKED struct svga_strings *)arg);

	default:
		return vidtty_v_ioctl(self, cmd, arg, mode);
		break;
	}
	return 0;
}

/* SVGA TTY device operators. */
PRIVATE struct mfile_stream_ops const svgatty_v_stream_ops = {
	.mso_write = &vidtty_v_write,
	.mso_ioctl = &svgatty_v_ioctl,
	.mso_hop   = &vidtty_v_hop,
	.mso_tryas = &vidtty_v_tryas,
};

INTERN_CONST struct vidtty_ops const svgatty_ops = {{{{{{
	.no_file = {
		.mo_destroy = &vidtty_v_destroy,
		.mo_changed = &vidtty_v_changed,
		.mo_stream  = &svgatty_v_stream_ops,
	},
	.no_wrattr = &vidtty_v_wrattr,
}}}}}};









/************************************************************************/
/* Primary SVGA Video Device.                                           */
/************************************************************************/

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
	incref(self); /* For `result->vty_dev' */
	result->vty_dev   = self;
	result->fn_mode   = S_IFCHR | 0600;
	result->dv_driver = incref(&drv_self);
	_vidtty_init(result, &svgatty_ops);
	TRY {
		REF struct svga_ttyaccess *tty;
		/* Allocate a tty-access object for the default TTY */
		tty = svgadev_makettyaccess(self, mode);
		arref_init(&result->vty_tty, tty);

		TRY {
			/* Register the device. */
			device_vregisterf(result, devno, format, args);
		} EXCEPT {
			destroy(arref_ptr(&result->vty_tty));
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
	struct svgadev *me = mfile_assvgadev(self);
	switch (cmd) {

	case SVGA_IOC_GETMODE:
	case SVGA_IOC_SETMODE: {
		/* Forward  these ioctls to the currently "active" tty,
		 * or the tty that will become active once a video lock
		 * is released. */
		REF struct svgatty *tty;
		tty = vidtty_assvga(viddev_getactivetty(me));
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

	default:
		return viddev_v_ioctl(self, cmd, arg, mode);
		break;
	}
	return 0;
}


PRIVATE BLOCKING NONNULL((1, 2)) void FCALL
svgadev_v_setttyvideomode(struct viddev *__restrict self,
                          struct vidttyaccess const *__restrict tty)
		THROWS(E_IOERROR) {
	struct svgadev *me       = viddev_assvga(self);
	struct svga_ttyaccess *ty = vidttyaccess_assvga(tty);
	svgadev_setmode(me, ty->sta_mode);
}


/* Allocate  and activate a new userlock for a given SVGA device.
 * If another lock already exists, this function will block until
 * said lock is released. */
PRIVATE BLOCKING NOCONNECT ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct vidlck *FCALL
svgadev_v_newlck(struct viddev *__restrict self)
		THROWS(E_IOERROR, E_WOULDBLOCK) {
	struct svgadev *me = viddev_assvga(self);
	REF struct svgalck *result;
	/* One of the branches below wouldn't be NOEXCEPT if preemption wasn't enabled... */
	if (!PREEMPTION_ENABLED())
		THROW(E_WOULDBLOCK_PREEMPTED);
	result = (REF struct svgalck *)kmalloc(offsetof(struct svgalck, slc_xregs) +
	                                       me->svd_chipset.sc_ops.sco_regsize,
	                                       GFP_NORMAL);
	TRY {
		REF struct mfile *active;
		struct svgatty *active_tty;
again:
		active = awref_get(&me->vd_active);
		if (!active) {
			if (awref_ptr(&me->vd_active) == NULL)
				goto got_active;
			/* wait for the lock to fully go again. */
			shared_lock_pollconnect(&me->vd_lock);
			active = awref_get(&me->vd_active);
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
		if (active && svga_active_islck(active)) {
			/* Wait for the lock to go away. */
			shared_lock_pollconnect(&me->vd_lock);
			if (awref_ptr(&me->vd_active) != active) {
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
		viddev_acquire(me);
		RAII_FINALLY { viddev_release(me); };
		if unlikely(awref_ptr(&me->vd_active) != active_tty)
			goto again;

		/* Disable the active tty. */
		if (active_tty) {
			struct svga_ttyaccess *tty;
			tty = vidttyaccess_assvga(arref_ptr(&active_tty->vty_tty));
			atomic_lock_acquire(&tty->vta_lock);
			assert(active_tty->vty_active);
			assert(tty->vta_flags & VIDTTYACCESS_F_ACTIVE);
			tty->vta_flags &= ~VIDTTYACCESS_F_ACTIVE;
			active_tty->vty_active = 0;
			atomic_lock_release(&tty->vta_lock);
		}
		TRY {
			/* Save Base-VGA registers. */
			basevga_getregs(&result->slc_vmode);

			/* Save chipset-specific registers. */
			(*me->svd_chipset.sc_ops.sco_getregs)(&me->svd_chipset, result->slc_xregs);
		} EXCEPT {
			/* Re-activate the old TTY */
			if (active_tty) {
				struct vidttyaccess *tty;
				tty = arref_ptr(&active_tty->vty_tty);
				atomic_lock_acquire(&tty->vta_lock); /* NOTHROW because preemption is enabled! */
				tty->vta_flags |= VIDTTYACCESS_F_ACTIVE;
				active_tty->vty_active = 1;
				(*tty->vta_activate)(tty);
				atomic_lock_release(&tty->vta_lock);
			}
			RETHROW();
		}

		/* NOEXCEPT FROM HERE ON! */

		/* Fill remaining fields. */
		_vidlck_init(result, &svgalck_ops);
		incref(me);       /* For `result->vlc_dev' */
		incref(active_tty); /* For `result->vlc_oldtty' */
		result->vlc_dev    = me;
		result->vlc_oldtty = active_tty;
		result->slc_mode   = NULL; /* No video mode override (yet) */

		/* If we're overriding  an active TTY,  then
		 * we know what the previous video-mode was! */
		if (active_tty != NULL)
			result->slc_mode = vidttyaccess_assvga(arref_ptr(&active_tty->vty_tty))->sta_mode;

		/* Remember that `result' is now active. */
		awref_set(&me->vd_active, result);
	} EXCEPT {
		kfree(result);
		RETHROW();
	}
	return result;
}

PRIVATE struct mfile_stream_ops const svgadev_v_stream_ops = {
	.mso_write  = &viddev_v_write,
	.mso_writev = &viddev_v_writev,
	.mso_ioctl  = &svgadev_v_ioctl,
	.mso_hop    = &viddev_v_hop,
	.mso_tryas  = &viddev_v_tryas,
};

/* Operators for `struct svgadev' */
INTERN_CONST struct viddev_ops const svgadev_ops = {
	.vdo_chr = {{{{
		.no_file = {
			.mo_destroy = &svgadev_v_destroy,
			.mo_changed = &viddev_v_changed,
			.mo_stream  = &svgadev_v_stream_ops,
		},
		.no_wrattr = &viddev_v_wrattr,
	}}}},
	.vdo_setttyvideomode = &svgadev_v_setttyvideomode,
	.vdo_newlck          = &svgadev_v_newlck,
};



DECL_END

#endif /* !GUARD_MODSVGA_MODE_C */
