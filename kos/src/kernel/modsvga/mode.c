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
#ifndef GUARD_MODSVGA_MODE_C
#define GUARD_MODSVGA_MODE_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <kernel/driver.h>
#include <kernel/handle.h>
#include <kernel/handman.h>
#include <kernel/malloc.h>
#include <kernel/rt/except-handler.h> /* userexcept_sysret_inject_self() */
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cred.h>
#include <sched/group.h>
#include <sched/posix-signal.h> /* task_raisesignalprocessgroup() */
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/host.h>
#include <hybrid/overflow.h>

#include <hw/video/vga.h>
#include <kos/except.h>
#include <kos/except/reason/illop.h>
#include <kos/except/reason/inval.h>
#include <kos/ioctl/svga.h>
#include <sys/mkdev.h>

#include <assert.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <libsvgadrv/util/vgaio.h>

#if defined(__i386__) || defined(__x86_64__)
#include <kernel/x86/cpuid.h>
#endif /* __i386__ || __x86_64__ */

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
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) {
	struct svga_modeinfo const *result;
	size_t i;
	for (i = 0; i < self->svd_supmodec; ++i) {
		result = svgadev_supmode(self, i);
		if (bcmp(result, mode, sizeof(struct svga_modeinfo)) == 0)
			return result;
	}
	THROW(E_INVALID_ARGUMENT_BAD_VALUE,
	      E_INVALID_ARGUMENT_CONTEXT_SVGA_INVALID_MODE);
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

PRIVATE NONNULL((2, 3)) ssize_t LIBSVGADRV_CC
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
	for (i = 0; i < lengthof(strings); ++i) {
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
	basevga_setregs(&me->slc_vregs);
}


PRIVATE NONNULL((1)) syscall_slong_t KCALL
svgalck_v_ioctl(struct mfile *__restrict self, ioctl_t cmd,
                USER UNCHECKED void *arg, iomode_t mode) THROWS(...) {
	struct svgalck *me = vidlck_assvga(self);
	switch (cmd) {

	case SVGA_IOC_GETMODE: {
		struct svga_modeinfo const *mymode;
		validate_writable(arg, sizeof(struct svga_modeinfo));
		mymode = ATOMIC_READ(me->slc_mode);
		if (!mymode) {
			THROW(E_ILLEGAL_BECAUSE_NOT_READY,
			      E_ILLEGAL_OPERATION_CONTEXT_SVGA_NO_MODE_SET);
		}
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
		if (newmode->smi_flags & SVGA_MODEINFO_F_TXT) {
			uint32_t fontbase;
			uint8_t cmap;
			cmap = baseega_registers.vr_mode.vm_seq_character_map;
			if (!(basevga_flags & BASEVGA_FLAG_ISEGA))
				cmap = vga_rseq(VGA_SEQ_CHARACTER_MAP);
			cmap     = VGA_SR03_CSETA_GET(cmap);
			fontbase = 0x20000 + basevga_fontoffset[cmap];
			basevga_wrvmem(fontbase, basevga_defaultfont, sizeof(basevga_defaultfont));
		}

		/* Remember last-set mode. */
		ATOMIC_WRITE(me->slc_mode, newmode);
		return 0;
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
		break;
	}
	return vidlck_v_ioctl(self, cmd, arg, mode);
}


PRIVATE struct mfile_stream_ops const svgalck_v_stream_ops = {
	.mso_ioctl = &svgalck_v_ioctl,
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
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) byte_t
NOTHROW(FCALL try_ocr_on_gfxcell)(struct svga_gfxcell const *__restrict cell) {
	unsigned int i;
	for (i = 0; i < 256; ++i) {
		if (bcmp(basevga_defaultfont[i], cell->sgc_lines, 16) == 0)
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
PRIVATE BLOCKING NONNULL((1, 2)) void FCALL
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

/* Same   as  `svgatty_settty()',  but  follow  up  by  sending
 * SIGWINCH to the foreground process group of an attached tty. */
PRIVATE BLOCKING NONNULL((1, 2)) void FCALL
svgatty_settty_with_winch(struct svgatty *__restrict self,
                          struct svga_ttyaccess *__restrict ntty) {
	REF struct mkttydev *utty;
	REF struct procgrp *fggrp;
	svgatty_settty(self, ntty);
	utty = awref_get(&self->at_tty);
	if (!utty)
		return; /* No tty attached. */
	fggrp = awref_get(&utty->t_fproc);
	decref_unlikely(utty);
	if (!fggrp)
		return; /* No foreground process. */
	{
		FINALLY_DECREF_UNLIKELY(fggrp);
		_task_raisesignoprocessgroup(fggrp, SIGWINCH);
	}

	/* In case the calling process is part of the same group,
	 * enqueue the calling thread  to try serving the  signal
	 * after the current system call returns. */
	userexcept_sysret_inject_self();
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
	svgatty_settty_with_winch(self, newtty);
	return 0;
}


PRIVATE NONNULL((1)) syscall_slong_t KCALL
svgatty_v_ioctl(struct mfile *__restrict self, ioctl_t cmd,
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
		break;
	}
	return vidtty_v_ioctl(self, cmd, arg, mode);
}

/* SVGA TTY device operators. */
PRIVATE struct mfile_stream_ops const svgatty_v_stream_ops = {
	.mso_write = &vidtty_v_write,
	.mso_ioctl = &svgatty_v_ioctl,
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

	/* Write attribute registers relating to palette values. */
	if (mode->smi_flags & SVGA_MODEINFO_F_PAL) {

		/* In 16-color palette modes, as well as when in text-mode,
		 * program ATC palette registers as  REG[i] = i. This  way,
		 * text colors can be  programmed directly using the  first
		 * 16 colors of the ~actual~ palette. */
		if ((mode->smi_flags & SVGA_MODEINFO_F_TXT) ||
		    (mode->smi_colorbits <= 4)) {
			if (basevga_flags & BASEVGA_FLAG_ISEGA) {
				port_t is1_rx;
				uint8_t i;
				baseega_registers.vr_mode.vm_att_color_page &= VGA_AT14_FRESERVED;
				baseega_registers.vr_mode.vm_att_color_page |= 0;
				is1_rx = VGA_IS1_RC;
				if (!(baseega_registers.vr_mode.vm_mis & VGA_MIS_FCOLOR))
					is1_rx = VGA_IS1_RM;
				vga_wattr(is1_rx, VGA_ATC_COLOR_PAGE, baseega_registers.vr_mode.vm_att_color_page);
				for (i = 0; i < 16; ++i) {
					uint8_t temp;
					temp = baseega_registers.vr_mode.vm_att_pal[i];
					temp &= VGA_ATC_PALETTEn_FRESERVED;
					temp |= i;
					vga_wattr(is1_rx, VGA_ATC_PALETTE0 + i, temp);
					baseega_registers.vr_mode.vm_att_pal[i] = temp;
				}
				if (mode->smi_flags & SVGA_MODEINFO_F_TXT) {
					baseega_registers.vr_mode.vm_att_mode &= ~VGA_AT10_FBLINK;
					baseega_registers.vr_mode.vm_att_mode |= VGA_AT10_FDUP9;
					vga_wattr(is1_rx, VGA_ATC_MODE, baseega_registers.vr_mode.vm_att_mode);
				}
			} else {
				port_t is1_rx;
				uint8_t i, temp;
				is1_rx = VGA_IS1_RC;
				if (!(vga_rmis() & VGA_MIS_FCOLOR))
					is1_rx = VGA_IS1_RM;
				temp = vga_rattr(is1_rx, VGA_ATC_COLOR_PAGE);
				temp &= VGA_AT14_FRESERVED;
				vga_wattr(is1_rx, VGA_ATC_COLOR_PAGE, temp);
				for (i = 0; i < 16; ++i) {
					temp = vga_rattr(is1_rx, VGA_ATC_PALETTE0 + i);
					temp &= VGA_ATC_PALETTEn_FRESERVED;
					temp |= i;
					vga_wattr(is1_rx, VGA_ATC_PALETTE0 + i, temp);
				}
				if (mode->smi_flags & SVGA_MODEINFO_F_TXT) {
					/* Disable "blinky" if it was enabled by the chip.
					 * Also enable `VGA_AT10_FDUP9' while we're at it. */
					temp = vga_rattr(is1_rx, VGA_ATC_MODE);
					vga_wattr(is1_rx, VGA_ATC_MODE, (temp & ~VGA_AT10_FBLINK) | VGA_AT10_FDUP9);
				}
			}
		} /* 16-color palette mode. */

		if (mode->smi_colorbits == 1) {
			/* Black & white emulation. */
			basevga_wrpal(0, basevga_monopal, 16);
		} else {
			/* Load an ANSI-compatible color palette */
			basevga_wrpal(0, basevga_defaultpal, 16);
		}
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
	 * Because `device_registerf()' set the GLOBAL bit, we simply clear it here.
	 *
	 * XXX: Technically, clearing `MFILE_FN_GLOBAL_REF'  like this is  unsafe, as  someone
	 *      else might set the flag again because of the `<WAS_SET_PREVIOUSLY>' condition. */
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
	struct svgadev *me;
	me = (struct svgadev *)mfile_aschrdev(self);
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
	svgadev_dbg_fini(me);
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */
	kfree((void *)me->svd_supmodev);
	(*me->svd_chipset.sc_ops.sco_fini)(&me->svd_chipset);
	chrdev_v_destroy(self);
}

PRIVATE NONNULL((1)) syscall_slong_t KCALL
svgadev_v_ioctl(struct mfile *__restrict self, ioctl_t cmd,
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
		if likely(tty) {
			FINALLY_DECREF_UNLIKELY(tty);
			return svgatty_v_ioctl(tty, cmd, arg, mode);
		}
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
		                      makedev(MKDEV_MAJOR_AUTO, 0), "%s", name);
		FINALLY_DECREF_UNLIKELY(tty);
		hand.h_type = HANDLE_TYPE_MFILE;
		hand.h_mode = IO_RDWR;
		hand.h_data = tty;
		return handles_install_openfd(hand, &info->smt_res);
	}	break;

	default:
		break;
	}
	return viddev_v_ioctl(self, cmd, arg, mode);
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
PRIVATE BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct vidlck *FCALL
svgadev_v_alloclck(struct viddev *__restrict self, struct vidtty *active_tty)
		THROWS(E_IOERROR, E_WOULDBLOCK) {
	struct svgadev *me = viddev_assvga(self);
	REF struct svgalck *result;
	result = (REF struct svgalck *)kmalloc(offsetof(struct svgalck, slc_xregs) +
	                                       me->svd_chipset.sc_ops.sco_regsize,
	                                       GFP_NORMAL);
	TRY {
		/* Save Base-VGA registers. */
		basevga_getregs(&result->slc_vregs);

		/* Save chipset-specific registers. */
		(*me->svd_chipset.sc_ops.sco_getregs)(&me->svd_chipset, result->slc_xregs);
	} EXCEPT {
		kfree(result);
		RETHROW();
	}

	/* Fill in operators. (as requirested by the caller) */
	result->mf_ops = &svgalck_ops.vlo_file;

	/* If we're overriding an active TTY, then we know what the current video-mode is! */
	result->slc_mode = NULL;
	if (active_tty != NULL)
		result->slc_mode = vidttyaccess_assvga(arref_ptr(&active_tty->vty_tty))->sta_mode;

	/* All other fields of `result' are filled by the caller! */
	return result;
}

PRIVATE struct mfile_stream_ops const svgadev_v_stream_ops = {
	.mso_write  = &viddev_v_write,
	.mso_writev = &viddev_v_writev,
	.mso_ioctl  = &svgadev_v_ioctl,
	.mso_tryas  = &viddev_v_tryas,
};


#ifdef CONFIG_HAVE_KERNEL_DEBUGGER

PRIVATE NOBLOCK ATTR_FREETEXT ATTR_PURE WUNUSED NONNULL((1)) uint64_t
NOTHROW(FCALL calculate_dbgmode_cost)(struct svga_modeinfo const *__restrict mode) {
	uint64_t result = 0;
	if (mode->smi_bits_per_pixel > 32)
		return (uint64_t)-1; /* We only support BPP up to 32-bit! */
#if 1 /* TODO: 4-bit mode */
	if (mode->smi_bits_per_pixel == 4)
		return (uint64_t)-1;
#endif
#if 1 /* TODO: paged memory access! */
	if (!(mode->smi_flags & SVGA_MODEINFO_F_LFB))
		return (uint64_t)-1;
#endif
	if (mode->smi_flags & SVGA_MODEINFO_F_TXT) {
		result += abs((int32_t)80 - (int32_t)mode->smi_resx);
		result += abs((int32_t)25 - (int32_t)mode->smi_resy);
	} else {
		result += abs((int32_t)(80 * 9) - (int32_t)mode->smi_resx);
		result += abs((int32_t)(25 * 16) - (int32_t)mode->smi_resy);
		result += abs((int8_t)16 - (int8_t)mode->smi_bits_per_pixel);
		result += UINT64_C(0x100000000);
	}
	return result;
}

/* Select and return the video mode that should be used for the builtin debugger. */
PRIVATE NOBLOCK ATTR_FREETEXT ATTR_PURE NONNULL((1)) struct svga_modeinfo const *
NOTHROW(FCALL svgadev_dbg_selectmode)(struct svgadev *__restrict self) {
	size_t i;
	uint64_t winner_cost;
	struct svga_modeinfo const *winner;
	winner      = svgadev_supmode(self, 0);
	winner_cost = calculate_dbgmode_cost(winner);
	for (i = 1; i < self->svd_supmodec; ++i) {
		struct svga_modeinfo const *mode;
		uint64_t cost;
		mode = svgadev_supmode(self, i);
		cost = calculate_dbgmode_cost(mode);
		if (winner_cost > cost) {
			winner_cost = cost;
			winner      = mode;
		}
	}
	return winner;
}

/* SVGA device debugger integration. */
INTERN ATTR_FREETEXT NONNULL((1)) void FCALL
svgadev_dbg_init(struct svgadev *__restrict self) {
	struct svga_modeinfo const *mode;
	size_t dregsize;

	/* Select the video mode that will be used in the builtin debugger.
	 * As  documented, we try to use an  80x25 text mode for this, esp.
	 * because this minimizes the amount of video memory that might get
	 * clobbered. (And thus has to be saved+restored) */
	mode = svgadev_dbg_selectmode(self);

	/* Figure out how large the extended register must needs to be. */
	dregsize = offsetof(struct svga_dbgregs, sdr_xdata);
	dregsize += self->svd_chipset.sc_ops.sco_regsize;
	if (mode->smi_flags & SVGA_MODEINFO_F_TXT) {
		dregsize += mode->smi_resx * mode->smi_resy * 2; /* On-screen text. */
		dregsize += 256 * 32;                            /* Text-mode font storage. */
	} else {
		/* If  the debugger can't use hardware text-mode, then
		 * we need to preserve the actual display memory (oof) */
		dregsize += mode->smi_resx * mode->smi_scanline;
	}

	/* Allocate a sufficiently sized buffer for the debugger TTY.
	 * Note  that we allocate this stuff with GFP_LOCKED+PREALLOC
	 * so that using it from within the debugger doesn't fault.
	 *
	 * Technically, we don't need to do that, but it improves the
	 * chances of still working  even when after being  poisoned. */
	self->svd_dbgsav = (struct svga_dbgregs *)kmalloc(dregsize, GFP_LOCKED | GFP_PREFLT);
	TRY {
		/* Allocate a tty-access object for use by the builtin debugger. */
		self->svd_dbgtty = svgadev_makettyaccess(self, mode);
	} EXCEPT {
		kfree(self->svd_dbgsav);
		RETHROW();
	}
}

INTERN NONNULL((1)) void
NOTHROW(FCALL svgadev_dbg_fini)(struct svgadev *__restrict self) {
	assert(self->svd_dbgtty->vta_refcnt == 1);
	destroy(self->svd_dbgtty);
	kfree(self->svd_dbgsav);
}


/* Save video memory to `buf', as may get clobbered by `tty' */
PRIVATE NONNULL((1, 2)) void
NOTHROW(FCALL dbg_save_vmem)(struct svga_ttyaccess *__restrict tty,
                             byte_t buf[]) {
	struct svga_modeinfo const *mode = tty->sta_mode;
	if (mode->smi_flags & SVGA_MODEINFO_F_TXT) {
		uint8_t cmap;
		size_t i;

		/* Save the text-mode page. */
#if defined(__i386__) || defined(__x86_64__)
		if (sys86_isqemu_accel()) {
			/* For some reason, accessing video memory here crashes QEMU:
			 * >> vcpu run failed for vcpu  0
			 */
			bzero(buf, tty->vta_resy * tty->vta_resx, 2);
		} else
#endif /* __i386__ || __x86_64__ */
		{
			byte_t *vmem;
			vmem = (byte_t *)mnode_getaddr(&tty->sta_vmem);
			for (i = 0; i < tty->vta_resy; ++i) {
				memcpy(buf, vmem, tty->vta_resx * 2);
				vmem += mode->smi_scanline;
				buf += tty->vta_resx * 2;
			}
		}

		/* Save memory re-used for the text-mode font. */
		cmap = baseega_registers.vr_mode.vm_seq_character_map;
		if (!(basevga_flags & BASEVGA_FLAG_ISEGA))
			cmap = vga_rseq(VGA_SEQ_CHARACTER_MAP);
		cmap = VGA_SR03_CSETA_GET(cmap);
		basevga_rdvmem(0x20000 + basevga_fontoffset[cmap], buf, 256 * 32);
	} else {
		/* Save the entire screen. */
		memcpy(buf, mnode_getaddr(&tty->sta_vmem),
		       mode->smi_resx * mode->smi_scanline);
	}
}

/* Load video memory from `buf', as may get clobbered by `tty' */
PRIVATE NONNULL((1, 2)) void
NOTHROW(FCALL dbg_load_vmem)(struct svga_ttyaccess *__restrict tty,
                             byte_t const buf[]) {
	struct svga_modeinfo const *mode = tty->sta_mode;
	if (mode->smi_flags & SVGA_MODEINFO_F_TXT) {
		uint8_t cmap;
		size_t i;
		byte_t *vmem;

		/* Restore the text-mode page. */
		vmem = (byte_t *)mnode_getaddr(&tty->sta_vmem);
		for (i = 0; i < tty->vta_resy; ++i) {
			memcpy(vmem, buf, tty->vta_resx * 2);
			vmem += mode->smi_scanline;
			buf += tty->vta_resx * 2;
		}

		/* Restore memory re-used for the text-mode font. */
		cmap = baseega_registers.vr_mode.vm_seq_character_map;
		if (!(basevga_flags & BASEVGA_FLAG_ISEGA))
			cmap = vga_rseq(VGA_SEQ_CHARACTER_MAP);
		cmap = VGA_SR03_CSETA_GET(cmap);
		basevga_wrvmem(0x20000 + basevga_fontoffset[cmap], buf, 256 * 32);
	} else {
		/* Restore the entire screen. */
		memcpy(mnode_getaddr(&tty->sta_vmem), buf,
		       mode->smi_resx * mode->smi_scanline);
	}
}

PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1)) struct vidttyaccess *
NOTHROW(FCALL svgadev_v_enterdbg)(struct viddev *__restrict self) {
	struct svga_ttyaccess *tty;
	struct svgadev *me;
	struct svga_dbgregs *sav;

	me  = viddev_assvga(self);
	tty = me->svd_dbgtty;
	sav = me->svd_dbgsav;

	/* Don't do unnecessary assertions in here! */
	/*assert(tty->vta_refcnt == 1);*/

	/* Save VGA registers into the designated state. */
	basevga_getregs(&sav->sdr_vmode);

	/* Preserve video memory that might get clobbered by `tty' */
	dbg_save_vmem(tty, sav->sdr_xdata + me->svd_chipset.sc_ops.sco_regsize);

	/* Save extended registers. */
	sav->sdr_hasxregs = true;
	NESTED_TRY {
		(*me->svd_chipset.sc_ops.sco_getregs)(&me->svd_chipset,
		                                      sav->sdr_xdata);
	} EXCEPT {
		/* This is a really bad sign, but let's try to keep
		 * on  moving, even if it's all we can really do at
		 * this point. */
		sav->sdr_hasxregs = false;
	}

	/* Switch display hardware into the video mode used by the debugger's tty.
	 * We  can only hope that this doesn't  throw an exception, but there's no
	 * way around this short of forcing the debugger-tty to always be visible,
	 * which wouldn't make any sense at all... */
	svgadev_setmode(me, tty->sta_mode);

	/* Activate the debugger tty. */
	tty->vta_flags |= VIDTTYACCESS_F_ACTIVE;
	(*tty->vta_activate)(tty);

	/* Return a pointer to the debugger's tty. */
	return tty;
}

PRIVATE NONNULL((1)) void
NOTHROW(FCALL svgadev_v_leavedbg)(struct viddev *__restrict self) {
	struct svga_ttyaccess *tty;
	struct svgadev *me;
	struct svga_dbgregs *sav;
	me  = viddev_assvga(self);
	tty = me->svd_dbgtty;
	sav = me->svd_dbgsav;

	/* Don't do unnecessary assertions in here! */
	/*assert(tty->vta_refcnt == 1);*/

	/* Deactivate the tty. */
	tty->vta_flags &= ~VIDTTYACCESS_F_ACTIVE;

	/* Restore extended chipset registers. */
	if (sav->sdr_hasxregs) {
		NESTED_TRY {
			(*me->svd_chipset.sc_ops.sco_setregs)(&me->svd_chipset,
			                                      sav->sdr_xdata);
		} EXCEPT {
		}
	}

	/* Restore video memory that might have gotten clobbered by `tty' */
	dbg_load_vmem(tty, sav->sdr_xdata + me->svd_chipset.sc_ops.sco_regsize);

	/* Restore basic VGA registers. */
	basevga_setregs(&sav->sdr_vmode);
}
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */


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
	.vdo_alloclck        = &svgadev_v_alloclck,
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
	.vdo_enterdbg = &svgadev_v_enterdbg,
	.vdo_leavedbg = &svgadev_v_leavedbg,
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */
};



DECL_END

#endif /* !GUARD_MODSVGA_MODE_C */
