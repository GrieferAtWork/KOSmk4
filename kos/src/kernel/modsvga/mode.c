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

#include <kernel/driver-param.h>
#include <kernel/driver.h>
#include <kernel/handle.h>
#include <kernel/malloc.h>
#include <kernel/types.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <hw/video/vga.h>
#include <kos/except.h>
#include <kos/ioctl/svga.h>

#include <assert.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>

#include <libsvga/util/vgaio.h>

/**/
#include "svga.h"

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */


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
		task_connect(&self->svd_chipset.sc_lock.sl_wrwait);
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
		svga_chipset_read(&self->svd_chipset);
		result = (REF struct svgatty *)xincref(lck->slc_oldtty);
		svga_chipset_endread(&self->svd_chipset);
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

	/* SVGA-tty objects get auto-destroyed once they're no longer referenced.
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
	/* One of the except branches below wouldn't be NOEXCEPT if preemption wasn't enabled... */
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
		task_connect(&self->svd_chipset.sc_lock.sl_wrwait);
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
	svga_chipset_write(&self->svd_chipset);
	RAII_FINALLY { svga_chipset_endwrite(&self->svd_chipset); };

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
		ot = arref_ptr(&oldtty->sty_tty); /* This can't change because we're holding the chipset lock! */
		atomic_lock_acquire(&ot->sta_lock);
		ot->sta_flags &= ~SVGA_TTYACCESS_F_ACTIVE;
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

//TODO: /* Allocate  and activate a new userlock for a given SVGA device.
//TODO:  * If another lock already exists, this function will block until
//TODO:  * said lock is released. */
//TODO: INTERN BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct svgalck *FCALL
//TODO: svgadev_newuserlock(struct svgadev *__restrict self)
//TODO: 		THROWS(E_WOULDBLOCK) {
//TODO: 	/* TODO */
//TODO: }



/* Default graphics mode hints.
 *
 * Note that modes can always be switched via ioctl(2).
 * These are on hints used to select the initial  mode. */
DEFINE_CMDLINE_PARAM_UINT32_VAR(default_resx, "xres", 1024);
DEFINE_CMDLINE_PARAM_UINT32_VAR(default_resy, "yres", 768);
DEFINE_CMDLINE_PARAM_UINT8_VAR(default_bpp, "bpp", 32);


PRIVATE NOBLOCK ATTR_FREETEXT WUNUSED NONNULL((1)) uint64_t
NOTHROW(FCALL calculate_mode_cost)(struct svga_modeinfo const *__restrict mode,
                                   uint32_t xres, uint32_t yres, uint8_t bpp) {
	uint64_t result = 0;
	result += abs((int32_t)xres - (int32_t)mode->smi_resx);
	result += abs((int32_t)yres - (int32_t)mode->smi_resy);
	result += abs((int8_t)bpp - (int8_t)mode->smi_bits_per_pixel);
	if (mode->smi_bits_per_pixel > 32)
		return (uint64_t)-1; /* We only support BPP up to 32-bit! */
#if 1 /* TODO: multiple-pixels-per-byte graphics modes! */
	if (mode->smi_bits_per_pixel <= 4)
		return (uint64_t)-1;
#endif
#if 1 /* TODO: paged memory access! */
	if (!(mode->smi_flags & SVGA_MODEINFO_F_LFB))
		return (uint64_t)-1;
#endif
	return result;
}

PRIVATE NOBLOCK ATTR_FREETEXT ATTR_RETNONNULL WUNUSED NONNULL((1)) struct svga_modeinfo const *
NOTHROW(FCALL select_closest_video_mode)(struct svgadev *__restrict self,
                                         uint32_t xres, uint32_t yres, uint8_t bpp) {
	size_t i;
	uint64_t winner_cost;
	struct svga_modeinfo const *winner;
	winner      = svgadev_supmode(self, 0);
	winner_cost = calculate_mode_cost(winner, xres, yres, bpp);
	for (i = 1; i < self->svd_supmodec; ++i) {
		struct svga_modeinfo const *mode;
		uint64_t cost;
		mode = svgadev_supmode(self, i);
		cost = calculate_mode_cost(mode, xres, yres, bpp);
		if (winner_cost > cost) {
			winner_cost = cost;
			winner      = mode;
		}
	}
	return winner;
}

PRIVATE NOBLOCK ATTR_FREETEXT ATTR_RETNONNULL WUNUSED NONNULL((1)) struct svga_modeinfo const *
NOTHROW(FCALL get_default_video_mode)(struct svgadev *__restrict self) {
	return select_closest_video_mode(self, default_resx, default_resy, default_bpp);
}





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

	case SVGA_IOC_MAKEDEFTTY: {
		struct handle hand;
		REF struct svgatty *tty;
		tty = svgadev_newttyf(me, get_default_video_mode(me),
		                      MKDEV(DEV_MAJOR_AUTO, 0), "tty1");
		FINALLY_DECREF_UNLIKELY(tty);
		svgadev_activate_tty(me, tty);
		hand.h_type = HANDLE_TYPE_MFILE;
		hand.h_mode = IO_RDWR;
		hand.h_data = tty;
		return handle_install(THIS_HANDLE_MANAGER, hand);
	}	break;

		/* TODO: the promised ioctls for creating locks and ttys. */

	default:
		break;
	}

	/* Fallback: forward the currently active TTY */
	{
		REF struct svgatty *tty;
		tty = svgadev_getactivetty(me);
		if (tty) {
			FINALLY_DECREF_UNLIKELY(tty);
			return mfile_uioctl(tty, cmd, arg, mode);
		}
	}
	/* If no TTY is active, do a generic chrdev ioctl on the primary SVGA controller. */
	return chrdev_v_ioctl(self, cmd, arg, mode);
}

PRIVATE struct mfile_stream_ops const svgadev_v_stream_ops = {
	.mso_ioctl = &svgadev_v_ioctl,
	.mso_hop   = &chrdev_v_hop,
	.mso_tryas = &chrdev_v_tryas,
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
