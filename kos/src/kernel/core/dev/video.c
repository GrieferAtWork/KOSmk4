/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_DEV_VIDEO_C
#define GUARD_KERNEL_SRC_DEV_VIDEO_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <dev/video.h>
#include <kernel/driver.h>
#include <kernel/handle.h>
#include <kernel/handman.h>
#include <kernel/malloc.h>
#include <kernel/user.h>
#include <sched/async.h>
#include <sched/cred.h>
#include <sched/task.h>

#include <hybrid/overflow.h>

#include <kos/except.h>
#include <kos/ioctl/_openfd.h>
#include <kos/ioctl/video.h>
#include <kos/nopf.h>
#include <sys/ioctl.h>

#include <alloca.h>
#include <assert.h>
#include <atomic.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

/************************************************************************/
/* VIDEO TTY ACCESSOR                                                   */
/************************************************************************/

PUBLIC NONNULL_T((1, 2)) void
NOTHROW(FCALL vidttyaccess_v_setcells_ascii)(struct vidttyaccess *__restrict self,
                                             struct ansitty *__restrict tty, uintptr_t address,
                                             char const *ascii_string, size_t num_cells) {
	size_t i;
	for (i = 0; i < num_cells; ++i) {
		char32_t ch = (char32_t)ascii_string[i];
		(*self->vta_setcell)(self, tty, address + i, ch);
	}
}



/************************************************************************/
/* VIDEO TTY                                                            */
/************************************************************************/

/* Activate a given TTY. If an active userlock exists, the tty will not actually
 * be  made active, but will instead be  linked such that the userlock's release
 * will make the tty active. */
PUBLIC BLOCKING NONNULL((1)) void FCALL
vidtty_activate(struct vidtty *__restrict self)
		THROWS(E_IOERROR) {
	struct viddev *dv = self->vty_dev;
	struct vidttyaccess *nt;
	REF struct mfile *old_active;
	struct vidtty *oldtty;
	/* One of the branches below wouldn't be NOEXCEPT if preemption wasn't enabled... */
	if (!PREEMPTION_ENABLED())
		THROW(E_WOULDBLOCK_PREEMPTED);
again:
	old_active = awref_get(&dv->vd_active);
	if (!old_active) {
		if (awref_ptr(&dv->vd_active) == NULL)
			goto got_old_active; /* Initial activation. */
		/* Because async destruction takes a write-lock to the chipset, we can
		 * just  wait for a write-lock to be released in order to wait for the
		 * active tty to finish unloading. */
		shared_lock_pollconnect(&dv->vd_lock);
		old_active = awref_get(&dv->vd_active);
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
	viddev_acquire(dv);
	RAII_FINALLY { viddev_release(dv); };

	/* Check if the active object changed. */
	COMPILER_READ_BARRIER();
	if (awref_ptr(&dv->vd_active) != old_active)
		goto again; /* Try again... */

	/* Special handling when the active object is a user-lock. */
	if (old_active && !mfile_isvidtty(old_active)) {
		struct vidlck *lck;
		lck = mfile_asvidlck(old_active);
		assert(lck->vlc_dev == dv);
		incref(self); /* For `lck->vlc_oldtty' */

		/* Check if `self' is already part of the restore chain.
		 * If so, remove it before re-inserting it at the front. */
		if (lck->vlc_oldtty) {
			struct vidtty **p_iter, *iter;
			p_iter = &lck->vlc_oldtty;
			while ((iter = *p_iter) != NULL) {
				if (iter == self) {
					*p_iter = self->vty_oldtty; /* Unlink. */
					decref_nokill(self);
					break;
				}
				p_iter = &iter->vty_oldtty;
			}
			/* Append the list of old ttys to the end `self' */
			if (lck->vlc_oldtty) {
				struct vidtty *last_tty;
				last_tty = container_of(p_iter, struct vidtty, vty_oldtty);
				last_tty->vty_oldtty = self->vty_oldtty;
				self->vty_oldtty     = lck->vlc_oldtty;
			}
		}
		lck->vlc_oldtty = self;
		return;
	}

	/* No userlock is active. -> activate this tty. */
	oldtty = mfile_asvidtty(old_active);

	/* Mark the old tty as inactive. */
	if (oldtty) {
		struct vidttyaccess *ot;
		assert(oldtty->vty_active);
		ot = arref_ptr(&oldtty->vty_tty); /* This can't change because we're holding the chipset lock! */
		atomic_lock_acquire(&ot->vta_lock);
		assert(ot->vta_flags & VIDTTYACCESS_F_ACTIVE);
		ot->vta_flags &= ~VIDTTYACCESS_F_ACTIVE;
		oldtty->vty_active = 0;
		atomic_lock_release(&ot->vta_lock);
	}

	/* Load the video mode of the caller's tty. */
	nt = arref_ptr(&self->vty_tty); /* This can't change because we're holding the chipset lock! */
	TRY {
		struct viddev_ops const *dv_ops;
		dv_ops = viddev_getops(dv);
		(*dv_ops->vdo_setttyvideomode)(dv, nt);
	} EXCEPT {
		/* NOTE: This right here assumes that `viddev_setmode()' throwing
		 *       didn't leave chipset  registers in  an undefined  state! */
		if (oldtty) {
			struct vidttyaccess *ot;
			ot = arref_ptr(&oldtty->vty_tty);   /* This can't change because we're holding the chipset lock! */
			atomic_lock_acquire(&ot->vta_lock); /* NOTHROW because preemption is enabled (s.a. above) */
			oldtty->vty_active = 1;
			ot->vta_flags |= VIDTTYACCESS_F_ACTIVE;
			(*ot->vta_activate)(ot);
			atomic_lock_release(&ot->vta_lock);
		}
		RETHROW();
	}
	/* NOTHROW FROM HERE ON! */

	/* Activate the tty accessor for the new active TTY */
	atomic_lock_acquire(&nt->vta_lock); /* NOTHROW because preemption is enabled (s.a. above) */
	nt->vta_flags |= VIDTTYACCESS_F_ACTIVE;
	self->vty_active = 1;
	(*nt->vta_activate)(nt);
	atomic_lock_release(&nt->vta_lock);

	/* Link old tty into restore list. */
	if (oldtty) {
		if (self->vty_oldtty) {
			struct vidtty **p_iter, *iter;
			p_iter = &self->vty_oldtty;
			while ((iter = *p_iter) != NULL) {
				if (iter == oldtty) {
					*p_iter = oldtty->vty_oldtty; /* Unlink. */
					decref_nokill(oldtty);
					break;
				}
				p_iter = &iter->vty_oldtty;
			}
			/* Append the list of old ttys to the end `self' */
			if (self->vty_oldtty) {
				struct vidtty *last_tty;
				last_tty = container_of(p_iter, struct vidtty, vty_oldtty);
				last_tty->vty_oldtty = oldtty->vty_oldtty;
				oldtty->vty_oldtty = self->vty_oldtty;
			}
		}

		/* Set-up the old-tty-restore link. */
		incref(oldtty);
		self->vty_oldtty = oldtty;
	}

	/* Set as active. */
	awref_set(&dv->vd_active, self);
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL vidtty_async_v_destroy)(struct async *__restrict self) {
	struct vidtty *me = _vidtty_fromasyncrestore(self);

	/* Clear remaining references. */
	decref_unlikely(me->vty_dev);
	xdecref_unlikely(me->vty_oldtty);

	/* Destroy the original underlying character-device. */
	chrdev_v_destroy(me);
}

PRIVATE NONNULL((1)) ktime_t FCALL
vidtty_async_v_connect(struct async *__restrict self) {
	struct vidtty *me = _vidtty_fromasyncrestore(self);
	shared_lock_pollconnect(&me->vty_dev->vd_lock);
	return KTIME_INFINITE;
}

PRIVATE WUNUSED NONNULL((1)) bool FCALL
vidtty_async_v_test(struct async *__restrict self) {
	struct vidtty *me = _vidtty_fromasyncrestore(self);
	return viddev_available(me->vty_dev);
}

PRIVATE WUNUSED NONNULL((1)) unsigned int FCALL
vidtty_async_v_work(struct async *__restrict self) {
	struct viddev_ops const *dv_ops;
	struct vidtty *me = _vidtty_fromasyncrestore(self);
	struct vidtty *nt = me->vty_oldtty;
	struct viddev *dv = me->vty_dev;
	struct vidttyaccess *ac;
	assert(PREEMPTION_ENABLED());
	if (!viddev_tryacquire(dv))
		return ASYNC_RESUME;
	RAII_FINALLY { viddev_release(dv); };
	assert(me->vty_active);
	assert(awref_ptr(&dv->vd_active) == me);

	/* Set the video mode used by `nt'
	 * NOTE: Because we're holding a lock to `dv', the tty access object can't change! */
	ac = arref_ptr(&nt->vty_tty);
	assert(!wasdestroyed(ac));
	assert(!(ac->vta_flags & VIDTTYACCESS_F_ACTIVE));
	assert(!nt->vty_active);
	dv_ops = viddev_getops(dv);
	(*dv_ops->vdo_setttyvideomode)(dv, ac);

	/* Mark the tty as active. */
	atomic_lock_acquire(&ac->vta_lock);     /* This can't throw because preemption is enabled. */
	ac->vta_flags |= VIDTTYACCESS_F_ACTIVE; /* Mark TTY accessor as active */
	nt->vty_active = 1;                     /* Mark TTY as active */
	(*ac->vta_activate)(ac);                /* This is NOBLOCK+NOTHROW */
	awref_set(&dv->vd_active, nt);          /* Remember TTY as active */
	atomic_lock_release(&ac->vta_lock);
	return ASYNC_FINISHED;
}

PRIVATE struct async_ops const vidtty_async_v_ops = {
	.ao_driver  = &drv_self,
	.ao_destroy = &vidtty_async_v_destroy,
	.ao_connect = &vidtty_async_v_connect,
	.ao_test    = &vidtty_async_v_test,
	.ao_work    = &vidtty_async_v_work,
};

/* Default vidtty operators. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vidtty_v_destroy)(struct mfile *__restrict self) {
	struct async *rstor;
	struct vidtty *me = mfile_asvidtty(self);
	arref_fini(&me->vty_tty);
	if (!me->vty_active) {
		ansittydev_v_destroy(self);
		return;
	}

	/* NOTE: ansitty-specific fields would have to be finalized here,
	 *       but none of those require any special finalization as of
	 *       right now. */

	/* Setup an async job to restore another tty. */
	rstor = _vidtty_toasyncrestore(me);
	async_init(rstor, &vidtty_async_v_ops);
	decref_unlikely(async_start(rstor));
}

PUBLIC NONNULL((1)) syscall_slong_t KCALL
vidtty_v_ioctl(struct mfile *__restrict self, ioctl_t cmd,
               NCX UNCHECKED void *arg, iomode_t mode) THROWS(...) {
	struct vidtty *me = mfile_asvidtty(self);
	switch (cmd) {

	case VID_IOC_ACTIVATE:
		/* Activate TTY */
		require(CAP_SYS_RAWIO);
		vidtty_activate(me);
		return 0;

	case TIOCGWINSZ:
	case _IO_WITHTYPE(TIOCGWINSZ, struct winsize): {
		/* Because we know the actual cell sizes, we can implement
		 * GWINSZ  more correctly than the generic ansitty's ioctl */
		NCX struct winsize *result;
		REF struct vidttyaccess *tty;
		validate_writable(arg, sizeof(struct winsize));
		result = (NCX struct winsize *)arg;
		tty    = vidtty_getaccess(me);
		FINALLY_DECREF_UNLIKELY(tty);
		result->ws_col    = (typeof(result->ws_col))tty->vta_resx;
		result->ws_row    = (typeof(result->ws_row))tty->vta_resy;
		result->ws_xpixel = (typeof(result->ws_xpixel))(tty->vta_resx * tty->vta_cellw);
		result->ws_ypixel = (typeof(result->ws_ypixel))(tty->vta_resy * tty->vta_cellh);
		return 0;
	}	break;

	case VID_IOC_GETTTYINFO: {
		REF struct vidttyaccess *tty;
		NCX struct vidttyinfo *info;
		info = (NCX struct vidttyinfo *)arg;
		validate_writable(info, sizeof(*info));
		tty = vidtty_getaccess(me);
		FINALLY_DECREF_UNLIKELY(tty);
		info->vti_cellw    = tty->vta_cellw;
		info->vti_cellh    = tty->vta_cellh;
		info->vti_resx     = tty->vta_resx;
		info->vti_resy     = tty->vta_resy;
		info->vti_cellsize = tty->vta_cellsize;
		return 0;
	}	break;

	case VID_IOC_GETCELLDATA:
	case VID_IOC_SETCELLDATA: {
		byte_t *buf;
		REF struct vidttyaccess *tty;
		struct vidttycelldata info;
		uint16_t x, y, xend, yend;
		validate_readable(arg, sizeof(info));
		memcpy(&info, arg, sizeof(info));
		tty = vidtty_getaccess(me);
		FINALLY_DECREF_UNLIKELY(tty);
		/* Verify bounds. */
		if unlikely(info.vcd_x + info.vcd_w > tty->vta_resx) {
			THROW(E_INDEX_ERROR_OUT_OF_BOUNDS,
			      info.vcd_x + info.vcd_w,
			      0, tty->vta_resx);
		}
		if unlikely(info.vcd_y + info.vcd_h > tty->vta_resy) {
			THROW(E_INDEX_ERROR_OUT_OF_BOUNDS,
			      info.vcd_y + info.vcd_h,
			      0, tty->vta_resy);
		}
		xend = info.vcd_x + info.vcd_w;
		yend = info.vcd_y + info.vcd_h;
		buf  = (byte_t *)alloca(tty->vta_cellsize);

		/* Transfer cell data. */
		if (cmd == VID_IOC_GETCELLDATA) {
			validate_writable(info.vcd_dat, info.vcd_w * info.vcd_h * tty->vta_cellsize);
			for (y = info.vcd_y; y < yend; ++y) {
				for (x = info.vcd_x; x < xend; ++x) {
					uintptr_t addr = x + y * tty->vta_scan;
					atomic_lock_acquire(&tty->vta_lock);
					(*tty->vta_getcelldata)(tty, addr, buf);
					atomic_lock_release(&tty->vta_lock);
					info.vcd_dat = (byte_t *)mempcpy(info.vcd_dat, buf,
					                                 tty->vta_cellsize);
				}
			}
		} else {
			validate_readable(info.vcd_dat, info.vcd_w * info.vcd_h * tty->vta_cellsize);
			for (y = info.vcd_y; y < yend; ++y) {
				for (x = info.vcd_x; x < xend; ++x) {
					uintptr_t addr = x + y * tty->vta_scan;
					memcpy(buf, info.vcd_dat, tty->vta_cellsize);
					info.vcd_dat += tty->vta_cellsize;
					atomic_lock_acquire(&tty->vta_lock);
					(*tty->vta_setcelldata)(tty, addr, buf);
					atomic_lock_release(&tty->vta_lock);
				}
			}
		}
		return 0;
	}	break;

	case VID_IOC_GETCURSOR: {
		REF struct vidttyaccess *tty;
		union vidtty_cursor cur;
		validate_writable(arg, 4);
		tty = vidtty_getaccess(me);
		/* Get cursor position word */
		{
			FINALLY_DECREF_UNLIKELY(tty);
			atomic_lock_acquire(&tty->vta_lock);
			cur.vtc_word = tty->vta_cursor.vtc_word;
			atomic_lock_release(&tty->vta_lock);
		}
		((NCX uint16_t *)arg)[0] = cur.vtc_cellx;
		((NCX uint16_t *)arg)[1] = cur.vtc_celly;
		return 0;
	}	break;

	case VID_IOC_SETCURSOR: {
		REF struct vidttyaccess *tty;
		union vidtty_cursor cur;
		validate_readable(arg, 4);
		cur.vtc_cellx = ((NCX uint16_t const *)arg)[0];
		cur.vtc_celly = ((NCX uint16_t const *)arg)[1];
		tty           = vidtty_getaccess(me);
		FINALLY_DECREF_UNLIKELY(tty);

		/* Verify bounds. */
		if unlikely(cur.vtc_cellx >= tty->vta_resx)
			THROW(E_INDEX_ERROR_OUT_OF_BOUNDS, cur.vtc_cellx, tty->vta_resx - 1);
		if unlikely(cur.vtc_celly >= tty->vta_resy)
			THROW(E_INDEX_ERROR_OUT_OF_BOUNDS, cur.vtc_celly, tty->vta_resy - 1);

		/* Set cursor position word */
		atomic_lock_acquire(&tty->vta_lock);
		tty->vta_cursor.vtc_word = cur.vtc_word;
		if (tty->vta_flags & VIDTTYACCESS_F_ACTIVE)
			(*tty->vta_showcursor)(tty);
		atomic_lock_release(&tty->vta_lock);
		return 0;
	}	break;

	default:
		break;
	}
	return ansittydev_v_ioctl(self, cmd, arg, mode);
}




/* Scroll up once */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL vidtty_scrollone)(struct vidttyaccess *__restrict me,
                                struct ansitty *__restrict tty) {
	(*me->vta_copycell)(me, me->_vta_scrl1_to, me->_vta_scrl1_from, me->_vta_scrl1_cnt);
	(*me->vta_fillcells)(me, tty, me->_vta_scrl1_fil, ' ', me->vta_resx);
}

PUBLIC NONNULL((1)) void LIBANSITTY_CC
vidtty_v_putc(struct ansitty *__restrict self,
              char32_t ch) {
	REF struct vidttyaccess *me;
	me = ansitty_getvidttyaccess(self);
	FINALLY_DECREF_UNLIKELY(me);
	atomic_lock_acquire(&me->vta_lock);
	switch (ch) {

	case 7: /* BEL */
		/* TODO */
		break;

	case '\t': {
#define TABSIZE 8
		uintptr_half_t advance;
		/* Check if we need to scroll. */
		if (me->vta_cursor.vtc_celly >= me->vta_scroll_yend) {
			me->vta_cursor.vtc_celly = me->_vta_scrl_ymax;
			vidtty_scrollone(me, self);
		}
		advance = TABSIZE - (me->vta_cursor.vtc_cellx % TABSIZE);
		if ((me->vta_cursor.vtc_cellx + advance) > me->vta_resx)
			advance = me->vta_resx - me->vta_cursor.vtc_cellx;
		(*me->vta_fillcells)(me, self,
		                     me->vta_cursor.vtc_cellx +
		                     me->vta_cursor.vtc_celly *
		                     me->vta_scan,
		                     ' ', advance);
		me->vta_cursor.vtc_cellx += advance;
		if (me->vta_cursor.vtc_cellx >= me->vta_resx) {
			me->vta_cursor.vtc_cellx = 0;
			++me->vta_cursor.vtc_celly;

			/* Set the EOL flag after an implicit line-feed */
			me->vta_flags |= VIDTTYACCESS_F_EOL;
			goto maybe_hide_cursor_after_eol;
		}
	}	break;

	case '\b':
		if (OVERFLOW_USUB(me->vta_cursor.vtc_cellx, 1, &me->vta_cursor.vtc_cellx)) {
			me->vta_cursor.vtc_cellx = me->vta_resx - 1;
			if (OVERFLOW_USUB(me->vta_cursor.vtc_celly, 1, &me->vta_cursor.vtc_celly)) {
				/* Stay in the top-left. */
				me->vta_cursor.vtc_cellx = 0;
				me->vta_cursor.vtc_celly = 0;
			}
		}
		/* Check if we need to scroll. */
		if (me->vta_cursor.vtc_celly >= me->vta_scroll_yend) {
			me->vta_cursor.vtc_celly = me->_vta_scrl_ymax;
			vidtty_scrollone(me, self);
		}
		break;

	case '\r':
		if (me->vta_flags & VIDTTYACCESS_F_EOL) {
			/* Go to the original line after a line-wrap. */
			me->vta_cursor.vtc_cellx = 0;
			--me->vta_cursor.vtc_celly;
			break;
		}
		if (self->at_ttymode & ANSITTY_MODE_NEWLINE_CLRFREE) {
			/* Clear trailing spaces */
			(*me->vta_fillcells)(me, self,
			                     me->vta_cursor.vtc_cellx +
			                     me->vta_cursor.vtc_celly *
			                     me->vta_scan,
			                     ' ',
			                     me->vta_resx - me->vta_cursor.vtc_cellx);
		}
		me->vta_cursor.vtc_cellx = 0;
		break;

	case '\n':
		/* Ignore '\n' after an implicit line-wrap. */
		if (!(me->vta_flags & VIDTTYACCESS_F_EOL))
			++me->vta_cursor.vtc_celly;
		if (me->vta_cursor.vtc_celly >= me->vta_scroll_yend) {
			me->vta_cursor.vtc_celly = me->_vta_scrl_ymax;
			vidtty_scrollone(me, self);
		}
		break;

	default: {
		/* Check if we need to scroll. */
		if (me->vta_cursor.vtc_celly >= me->vta_scroll_yend) {
			me->vta_cursor.vtc_celly = me->_vta_scrl_ymax;
			vidtty_scrollone(me, self);
		}

		/* Print the character to the screen. */
		(*me->vta_setcell)(me, self,
		                   me->vta_cursor.vtc_cellx +
		                   me->vta_cursor.vtc_celly *
		                   me->vta_scan,
		                   ch);

		/* Advance the cursor. */
		++me->vta_cursor.vtc_cellx;

		/* Check for line overflow. */
		if (me->vta_cursor.vtc_cellx >= me->vta_resx) {
			me->vta_cursor.vtc_cellx = 0;
			++me->vta_cursor.vtc_celly;

			/* Set the EOL flag after an implicit line-feed */
			me->vta_flags |= VIDTTYACCESS_F_EOL;
maybe_hide_cursor_after_eol:
			if (me->vta_cursor.vtc_celly >= me->vta_resy) {
				/* Hide the hardware cursor (if it was visible before) */
				if (!(self->at_ttymode & ANSITTY_MODE_HIDECURSOR) &&
				    (me->vta_flags & VIDTTYACCESS_F_ACTIVE))
					(*me->vta_hidecursor)(me);
				goto after_clear_eol_nocursor;
			}
			goto after_clear_eol;
		}
	}	break;

	}

	/* Clear the EOL flag. */
	me->vta_flags &= ~VIDTTYACCESS_F_EOL;
after_clear_eol:
	if (!(self->at_ttymode & ANSITTY_MODE_HIDECURSOR) &&
	    (me->vta_flags & VIDTTYACCESS_F_ACTIVE))
		(*me->vta_showcursor)(me); /* Update hardware cursor. */
after_clear_eol_nocursor:
	atomic_lock_release(&me->vta_lock);
}

PUBLIC WUNUSED NONNULL((1)) size_t LIBANSITTY_CC
vidtty_v_puts_ascii(struct ansitty *__restrict self,
                    NCX uint8_t const *utf8_string,
                    size_t n_chars) {
	char buf[256];
	size_t avail_cells;
	size_t result;
	REF struct vidttyaccess *me;

	/* Read data into a temporary buffer since the caller-given one is "NCX",
	 * meaning it could be  a faulty user-space pointer,  or be part of  VIO. */
	if (n_chars > COMPILER_LENOF(buf))
		n_chars = COMPILER_LENOF(buf);

	/* Count the # of leading, non-control (printable) ASCII characters. */
	for (result = 0; result < n_chars; ++result) {
		if (!readb_nopf((NCX uint8_t const *)&utf8_string[result], (uint8_t *)&buf[result]))
			break;
		/* TODO: Handle consecutive \r\n, etc, thereby further
		 *       reducing  the  # of  necessary  render calls. */
		if ((unsigned char)buf[result] <= 0x1f ||
		    (unsigned char)buf[result] >= 0x7f)
			break; /* Non-printable, or non-ASCII */
	}

	/* Check  if there is  a point in  doing a batched render.
	 * If there is less than 1 viable character, then we might
	 * as well let the caller print 1-character-at-a-time. */
	if (result <= 1)
		return 0;

	me = ansitty_getvidttyaccess(self);
	FINALLY_DECREF_UNLIKELY(me);
	atomic_lock_acquire(&me->vta_lock);

	/* Check if we need to scroll. */
	if (me->vta_cursor.vtc_celly >= me->vta_scroll_yend) {
		me->vta_cursor.vtc_celly = me->_vta_scrl_ymax;
		vidtty_scrollone(me, self);
	}

	/* Figure out how many consecutive cells can be filled. */
	avail_cells = me->vta_resx - me->vta_cursor.vtc_cellx;
	if (me->vta_scan == me->vta_resx) {
		size_t whole_rows = (me->vta_scroll_yend - 1) - me->vta_cursor.vtc_celly;
		avail_cells += whole_rows * me->vta_scan;
	}
	if (result > avail_cells)
		result = avail_cells;

	/* Transfer data from "buf" into cells. */
	(*me->vta_setcells_ascii)(me, self,
	                          me->vta_cursor.vtc_cellx +
	                          me->vta_cursor.vtc_celly *
	                          me->vta_scan,
	                          buf, result);

	/* Advance the cursor. */
	me->vta_cursor.vtc_cellx += result;
	if (me->vta_cursor.vtc_cellx >= me->vta_resx) {
		me->vta_cursor.vtc_celly += me->vta_cursor.vtc_cellx / me->vta_resx;
		me->vta_cursor.vtc_cellx = me->vta_cursor.vtc_cellx % me->vta_resx;

		/* Set the EOL flag after an implicit line-feed */
		if (me->vta_cursor.vtc_cellx == 0)
			me->vta_flags |= VIDTTYACCESS_F_EOL;
		if (me->vta_cursor.vtc_celly >= me->vta_resy) {
			/* Hide the hardware cursor (if it was visible before) */
			if (!(self->at_ttymode & ANSITTY_MODE_HIDECURSOR) &&
			    (me->vta_flags & VIDTTYACCESS_F_ACTIVE))
				(*me->vta_hidecursor)(me);
			goto after_clear_eol_nocursor;
		}
		goto after_clear_eol;
	}

	/* Clear the EOL flag. */
	me->vta_flags &= ~VIDTTYACCESS_F_EOL;
after_clear_eol:
	if (!(self->at_ttymode & ANSITTY_MODE_HIDECURSOR) &&
	    (me->vta_flags & VIDTTYACCESS_F_ACTIVE))
		(*me->vta_showcursor)(me); /* Update hardware cursor. */
after_clear_eol_nocursor:
	atomic_lock_release(&me->vta_lock);
	return result;
}

PUBLIC NONNULL((1)) void LIBANSITTY_CC
vidtty_v_setcursor(struct ansitty *__restrict self,
                   ansitty_coord_t x, ansitty_coord_t y,
                   bool update_hw_cursor) {
	REF struct vidttyaccess *me;
	me = ansitty_getvidttyaccess(self);
	FINALLY_DECREF_UNLIKELY(me);
	if unlikely(x >= me->vta_resx)
		x = me->vta_resx - 1;
	if unlikely(y >= me->vta_resy)
		y = me->vta_resy - 1;
	atomic_lock_acquire(&me->vta_lock);
	me->vta_cursor.vtc_cellx = x;
	me->vta_cursor.vtc_celly = y;
	me->vta_flags &= ~VIDTTYACCESS_F_EOL;
	if (update_hw_cursor &&
	    !(self->at_ttymode & ANSITTY_MODE_HIDECURSOR) &&
	    (me->vta_flags & VIDTTYACCESS_F_ACTIVE))
		(*me->vta_showcursor)(me); /* Update hardware cursor. */
	atomic_lock_release(&me->vta_lock);
}

PUBLIC NONNULL((1, 2)) void LIBANSITTY_CC
vidtty_v_getcursor(struct ansitty *__restrict self,
                   ansitty_coord_t ppos[2]) {
	union vidtty_cursor cur;
	REF struct vidttyaccess *me;
	me = ansitty_getvidttyaccess(self);
	cur.vtc_word = atomic_read(&me->vta_cursor.vtc_word);
	ppos[0]      = cur.vtc_cellx;
	ppos[1]      = cur.vtc_celly;
	decref_unlikely(me);
}

PUBLIC NONNULL((1, 2)) void LIBANSITTY_CC
vidtty_v_getsize(struct ansitty *__restrict self,
                 ansitty_coord_t psize[2]) {
	REF struct vidttyaccess *me;
	me = ansitty_getvidttyaccess(self);
	psize[0] = me->vta_resx;
	psize[1] = me->vta_resy;
	decref_unlikely(me);
}

PUBLIC NONNULL((1)) void LIBANSITTY_CC
vidtty_v_copycell(struct ansitty *__restrict self,
                  ansitty_offset_t dst_offset,
                  ansitty_coord_t count) {
	REF struct vidttyaccess *me;
	uintptr_t srcaddr, dstaddr, copyend, dispend;
	me = ansitty_getvidttyaccess(self);
	FINALLY_DECREF_UNLIKELY(me);
	atomic_lock_acquire(&me->vta_lock);
	srcaddr = me->vta_cursor.vtc_celly;
	/* Yes: vta_resx (and not `vta_scan'); s.a. the documentation of `vta_copycell' */
	srcaddr *= me->vta_resx;
	srcaddr += me->vta_cursor.vtc_cellx;
	dstaddr = srcaddr + dst_offset;

	/* Limit copy range at the start of destination */
	if ((intptr_t)dstaddr < 0) {
		size_t underflow;
		underflow = (size_t)0 - dstaddr;
		dstaddr   = 0;
		if (OVERFLOW_UADD(srcaddr, underflow, &srcaddr))
			goto done;
	}

	/* Limit copy range at the end of the destination */
	if (OVERFLOW_UADD(dstaddr, count, &copyend)) {
		count   = ((uintptr_t)-1) - dstaddr;
		copyend = ((uintptr_t)-1);
	}
	dispend = me->vta_resy * me->vta_resx;
	if (copyend > dispend) {
		size_t overflow = copyend - me->vta_resy;
		if (OVERFLOW_USUB(count, overflow, &count))
			goto done;
	}

	/* Limit copy range at the end of the source */
	if unlikely(OVERFLOW_UADD(srcaddr, count, &copyend) || copyend > dispend) {
		size_t maxcount, overflow;
		maxcount = dispend - srcaddr;
		overflow = count - maxcount;

		/* Do the actual cell-copy. */
		assert(srcaddr <= dispend);
		assert(dstaddr <= dispend);
		assert((srcaddr + maxcount) <= dispend);
		assert((dstaddr + maxcount) <= dispend);
		(*me->vta_copycell)(me, dstaddr, srcaddr, maxcount);

		/* Fill `overflow' cells at `dstaddr + maxcount' with ' ' */
		dstaddr += maxcount;
		if (me->vta_scan > me->vta_resx) {
			size_t delta = me->vta_scan - me->vta_resx;
			dstaddr += (dstaddr / me->vta_resx) * delta;
		}
		(*me->vta_fillcells)(me, self, dstaddr, ' ', overflow);
	} else {
		/* Do the actual cell-copy. */
		assert(srcaddr <= dispend);
		assert(dstaddr <= dispend);
		assert((srcaddr + count) <= dispend);
		assert((dstaddr + count) <= dispend);
		(*me->vta_copycell)(me, dstaddr, srcaddr, count);
	}

done:
	atomic_lock_release(&me->vta_lock);
}

PUBLIC NONNULL((1)) void LIBANSITTY_CC
vidtty_v_fillcell(struct ansitty *__restrict self,
                  char32_t ch,
                  ansitty_coord_t count) {
	REF struct vidttyaccess *me;
	uintptr_t dstaddr, fillend, dispend;
	me = ansitty_getvidttyaccess(self);
	FINALLY_DECREF_UNLIKELY(me);
	atomic_lock_acquire(&me->vta_lock);
	dstaddr = me->vta_cursor.vtc_cellx +
	          me->vta_cursor.vtc_celly *
	          me->vta_resx;
	dispend = me->vta_resy * me->vta_resx;
	/* Limit `count' to what can be put on-screen. */
	if (OVERFLOW_UADD(dstaddr, count, &fillend) || fillend > dispend) {
		if unlikely(OVERFLOW_USUB(dispend, dstaddr, &count))
			goto done;
	}

	/* Adjust `count' for scanlines */
	if (me->vta_scan > me->vta_resx) {
		size_t aligned_size;
		size_t delta = me->vta_scan - me->vta_resx;
		dstaddr      = me->vta_cursor.vtc_cellx + me->vta_cursor.vtc_celly * me->vta_scan;
		aligned_size = dstaddr % me->vta_scan; /* # of characters before first line */
		aligned_size += count;                 /* Total number of characters from start of first line */
		aligned_size /= me->vta_resx;          /* Number of line-feeds included in the fill. */
		count += aligned_size * delta;         /* Include delta induced by line-feeds. */
	}

	/* Do the fill. */
	(*me->vta_fillcells)(me, self, dstaddr, ch, count);
done:
	atomic_lock_release(&me->vta_lock);
}

PUBLIC NONNULL((1)) void LIBANSITTY_CC
vidtty_v_setttymode(struct ansitty *__restrict self) {
	REF struct vidttyaccess *me;
	me = ansitty_getvidttyaccess(self);
	FINALLY_DECREF_UNLIKELY(me);
	atomic_lock_acquire(&me->vta_lock);
	if likely(me->vta_flags & VIDTTYACCESS_F_ACTIVE) {
		/* Update the state of the on-screen cursor. */
		if (self->at_ttymode & ANSITTY_MODE_HIDECURSOR) {
			(*me->vta_hidecursor)(me);
		} else if (me->vta_cursor.vtc_celly < me->vta_resy) {
			(*me->vta_showcursor)(me);
		}
	}
	atomic_lock_release(&me->vta_lock);
}

PUBLIC NONNULL((1)) void LIBANSITTY_CC
vidtty_v_scrollregion(struct ansitty *__restrict self) {
	ansitty_coord_t sl = self->at_scroll_sl;
	ansitty_coord_t el = self->at_scroll_el;
	REF struct vidttyaccess *me;
	if (sl < 0)
		sl = 0;
	me = ansitty_getvidttyaccess(self);
	FINALLY_DECREF_UNLIKELY(me);
	if (el > me->vta_resy)
		el = me->vta_resy;
	if (sl > el)
		sl = el;
	atomic_lock_acquire(&me->vta_lock);
	me->vta_scroll_ystart = sl;
	me->vta_scroll_yend   = el;
	_vidttyaccess_update_scrl(me);
	atomic_lock_release(&me->vta_lock);
}

PUBLIC_CONST struct ansitty_operators const vidtty_ansitty_ops = {
	.ato_putc         = &_vidtty_v_putc,
	.ato_setcursor    = &_vidtty_v_setcursor,
	.ato_getcursor    = &_vidtty_v_getcursor,
	.ato_getsize      = &_vidtty_v_getsize,
	.ato_copycell     = &_vidtty_v_copycell,
	.ato_fillcell     = &_vidtty_v_fillcell,
	.ato_setttymode   = &_vidtty_v_setttymode,
	.ato_scrollregion = &_vidtty_v_scrollregion,
	.ato_output       = &_vidtty_v_output,
	.ato_setled       = &_vidtty_v_setled,
	.ato_termios      = &_vidtty_v_termios,
	.ato_puts_ascii   = &_vidtty_v_puts_ascii,
};






/************************************************************************/
/* VIDEO LOCK                                                           */
/************************************************************************/

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL vidlck_async_v_destroy)(struct async *__restrict self) {
	struct vidlck *me = container_of(self, struct vidlck, vlc_rstor);

	/* Clear remaining references. */
	decref_unlikely(me->vlc_dev);
	xdecref_unlikely(me->vlc_oldtty);

	/* Free the lock control structure. */
	kfree(me);
}

PRIVATE NONNULL((1)) ktime_t FCALL
vidlck_async_v_connect(struct async *__restrict self) {
	struct vidlck *me = container_of(self, struct vidlck, vlc_rstor);
	shared_lock_pollconnect(&me->vlc_dev->vd_lock);
	return KTIME_INFINITE;
}

PRIVATE WUNUSED NONNULL((1)) bool FCALL
vidlck_async_v_test(struct async *__restrict self) {
	struct vidlck *me = container_of(self, struct vidlck, vlc_rstor);
	return viddev_available(me->vlc_dev);
}

PRIVATE WUNUSED NONNULL((1)) unsigned int FCALL
vidlck_async_v_work(struct async *__restrict self) {
	struct vidlck *me = container_of(self, struct vidlck, vlc_rstor);
	struct vidtty *nt = me->vlc_oldtty;
	struct viddev *dv = me->vlc_dev;
	struct vidttyaccess *ac;
	struct viddev_ops const *dv_ops;
	assert(PREEMPTION_ENABLED());
	if (!viddev_tryacquire(dv))
		return ASYNC_RESUME;
	RAII_FINALLY { viddev_release(dv); };
	assert(awref_ptr(&dv->vd_active) == me);

	/* Restore extended registers. (Only do this once if `vdo_setttyvideomode()' below throws) */
	if (!(me->mf_flags & _MFILE_FN__RBRED)) {
		struct vidlck_ops const *ops;
		ops = vidlck_getops(me);
		(*ops->vlo_restore)(me, dv);
		me->mf_flags |= _MFILE_FN__RBRED;
	}

	/* Set the video mode used by `nt'
	 * NOTE: Because we're holding a lock to `dv', the tty access object can't change! */
	ac = arref_ptr(&nt->vty_tty);
	assert(!wasdestroyed(ac));
	assert(!(ac->vta_flags & VIDTTYACCESS_F_ACTIVE));
	assert(!nt->vty_active);
	dv_ops = viddev_getops(dv);
	(*dv_ops->vdo_setttyvideomode)(dv, ac);

	/* Mark the tty as active. */
	atomic_lock_acquire(&ac->vta_lock);     /* This can't throw because preemption is enabled. */
	ac->vta_flags |= VIDTTYACCESS_F_ACTIVE; /* Mark TTY accessor as active */
	nt->vty_active = 1;                     /* Mark TTY as active */
	(*ac->vta_activate)(ac);                /* This is NOBLOCK+NOTHROW */
	awref_set(&dv->vd_active, nt);          /* Remember TTY as active */
	atomic_lock_release(&ac->vta_lock);
	return ASYNC_FINISHED;
}


PRIVATE struct async_ops const vidlck_async_v_ops = {
	.ao_driver  = &drv_self,
	.ao_destroy = &vidlck_async_v_destroy,
	.ao_connect = &vidlck_async_v_connect,
	.ao_test    = &vidlck_async_v_test,
	.ao_work    = &vidlck_async_v_work,
};

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vidlck_v_destroy)(struct mfile *__restrict self) {
	struct vidlck *me = mfile_asvidlck(self);
	assert(!(me->mf_flags & _MFILE_FN__RBRED));
	/* Setup an async job to restore another tty. */
	async_init(&me->vlc_rstor, &vidlck_async_v_ops);
	decref_unlikely(async_start(&me->vlc_rstor));
}









/************************************************************************/
/* VIDEO DEVICE                                                         */
/************************************************************************/

/* Return a reference to the currently "active" tty (or the one that will become
 * active after a currently held user-lock is released). If no such TTY  exists,
 * return NULL instead. */
PUBLIC BLOCKING WUNUSED NONNULL((1)) REF struct vidtty *FCALL
viddev_getactivetty(struct viddev *__restrict self) {
	REF struct mfile *active;
again:
	active = awref_get(&self->vd_active);
	if (!active) {
		/* This can happen for 2 reasons:
		 *  - No TTY is active
		 *  - The active tty is being destroyed
		 *
		 * In the later case, we must want for the async destruction to finish! */
		if (awref_ptr(&self->vd_active) == NULL)
			return NULL;

		/* Because async destruction takes a write-lock to the chipset, we can
		 * just  wait for a write-lock to be released in order to wait for the
		 * active tty to finish unloading. */
		shared_lock_pollconnect(&self->vd_lock);
		active = awref_get(&self->vd_active);
		if unlikely(active) {
			task_disconnectall();
			goto got_active;
		}
		task_waitfor();
		goto again;
	}
got_active:

	/* If the active object is a TTY, then we know that's the active TTY */
	if (mfile_isvidtty(active))
		return mfile_asvidtty(active);

	/* Last case: the active object is a userlock.
	 * In this case, return a reference to the tty that will be restored once that lock is released. */
	{
		struct vidlck *lck;
		REF struct vidtty *result;
		lck = mfile_asvidlck(active);
		assert(lck->vlc_dev == self);
		/* In order to read from `vlc_oldtty', we need a lock to the chipset driver. */
		FINALLY_DECREF_UNLIKELY(lck);
		viddev_acquire(self);
		result = lck->vlc_oldtty;
		xincref(result);
		viddev_release(self);
		return result;
	}
}

/* Create a new video lock object for a given video device. */
PUBLIC BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct vidlck *FCALL
viddev_newlck(struct viddev *__restrict self) {
	REF struct vidlck *result;
	REF struct mfile *active;
	struct vidtty *active_tty;
	/* One of the branches below wouldn't be NOEXCEPT if preemption wasn't enabled... */
	if (!PREEMPTION_ENABLED())
		THROW(E_WOULDBLOCK_PREEMPTED);
again:
	active = awref_get(&self->vd_active);
	if (!active) {
		if (awref_ptr(&self->vd_active) == NULL)
			goto got_active;
		/* wait for the lock to fully go again. */
		shared_lock_pollconnect(&self->vd_lock);
		active = awref_get(&self->vd_active);
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
	if (active && !mfile_isvidtty(active)) {
		/* Wait for the lock to go away. */
		shared_lock_pollconnect(&self->vd_lock);
		if (awref_ptr(&self->vd_active) != active) {
			task_disconnectall();
			goto again;
		}
		task_waitfor();
		goto again;
	}
	assert(!active || mfile_isvidtty(active));
	active_tty = mfile_asvidtty(active);

	/* All right! Now get a lock to the chipset and
	 * check  that the active object didn't change. */
	viddev_acquire(self);
	RAII_FINALLY { viddev_release(self); };
	if unlikely(awref_ptr(&self->vd_active) != active_tty)
		goto again;

	/* Disable the active tty. */
	if (active_tty) {
		struct vidttyaccess *tty;
		tty = arref_ptr(&active_tty->vty_tty);
		atomic_lock_acquire(&tty->vta_lock);
		assert(active_tty->vty_active);
		assert(tty->vta_flags & VIDTTYACCESS_F_ACTIVE);
		tty->vta_flags &= ~VIDTTYACCESS_F_ACTIVE;
		active_tty->vty_active = 0;
		atomic_lock_release(&tty->vta_lock);
	}
	TRY {
		/* Use the designated operator to allocate the raw video lock,
		 * and  populate its device-specific data-area with a snapshot
		 * of the current register state. */
		struct viddev_ops const *ops;
		ops    = viddev_getops(self);
		result = (*ops->vdo_alloclck)(self, active_tty);
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
	assert(result->mf_ops);
	assert(result->mf_ops->mo_destroy);

	/* Fill remaining fields. */
	_mfile_init_common(result);
	_mfile_init_blockshift(result, PAGESHIFT, PAGESHIFT);
	result->mf_parts             = MFILE_PARTS_ANONYMOUS;
	result->mf_changed.slh_first = MFILE_PARTS_ANONYMOUS;
	atomic64_init(&result->mf_filesize, 0),
	result->mf_flags = (MFILE_F_READONLY | MFILE_F_ATTRCHANGED | MFILE_F_CHANGED |
	                    MFILE_F_NOATIME | MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO |
	                    MFILE_F_NOMTIME | MFILE_F_FIXEDFILESIZE),
	result->mf_atime = realtime();
	result->mf_mtime = result->mf_atime;
	result->mf_ctime = result->mf_atime;
	result->mf_btime = result->mf_atime;
	incref(self);       /* For `result->vlc_dev' */
	incref(active_tty); /* For `result->vlc_oldtty' */
	result->vlc_dev    = self;
	result->vlc_oldtty = active_tty;

	/* Remember that `result' is now active. */
	awref_set(&self->vd_active, result);
	return result;
}


/* Default operators for `struct viddev'. */
PUBLIC NONNULL((1)) syscall_slong_t KCALL
viddev_v_ioctl(struct mfile *__restrict self, ioctl_t cmd,
               NCX UNCHECKED void *arg, iomode_t mode) THROWS(...) {
	struct viddev *me = mfile_asviddev(self);
	switch (cmd) {

	case VID_IOC_MAKELCK: {
		struct handle hand;
		REF struct vidlck *lck;

		/* Require raw I/O.  - Without  this, the  lock
		 * probably wouldn't do you any good anyways... */
		require(CAP_SYS_RAWIO);

		/* Create lock object. */
		lck = viddev_newlck(me);
		FINALLY_DECREF_UNLIKELY(lck);

		/* Store lock object in a handle. */
		hand.h_type = HANDLE_TYPE_MFILE;
		hand.h_mode = IO_RDWR;
		hand.h_data = lck;
		return handles_install_openfd(hand, (NCX UNCHECKED struct openfd *)arg);
	}	break;

	default:
		break;
	}

	/* Forward these ioctls to the currently active tty. */
	if (_IOC_TYPE(cmd) == _IOC_TYPE(TIOCGWINSZ) ||
	    _IOC_TYPE(cmd) == _IOC_TYPE(VID_IOC_GETTTYINFO)) {
		REF struct vidtty *tty;
		tty = viddev_getactivetty(me);
		if likely(tty) {
			FINALLY_DECREF_UNLIKELY(tty);
			return mfile_uioctl(tty, cmd, arg, mode);
		}
	}

	/* Do a generic character-device ioctl */
	return chrdev_v_ioctl(self, cmd, arg, mode);
}

PUBLIC BLOCKING WUNUSED NONNULL((1)) size_t KCALL
viddev_v_write(struct mfile *__restrict self, NCX void const *src,
               size_t num_bytes, iomode_t mode) THROWS(...) {
	/* Direct writes to an video device go to the currently active tty. */
	struct viddev *me = (struct viddev *)mfile_asansitty(self);
	REF struct vidtty *tty;
	tty = viddev_getactivetty(me);
	if unlikely(!tty)
		return 0; /* Indicate EOF */
	FINALLY_DECREF_UNLIKELY(tty);
	assert(tty->mf_ops->mo_stream != NULL &&
	       tty->mf_ops->mo_stream->mso_write == &ansittydev_v_write);
	return ansittydev_v_write(tty, src, num_bytes, mode);
}

PUBLIC BLOCKING WUNUSED NONNULL((1)) size_t KCALL
viddev_v_writev(struct mfile *__restrict self, struct iov_buffer *__restrict src,
                size_t num_bytes, iomode_t mode) THROWS(...) {
	/* Direct writes to an video device go to the currently active tty. */
	struct viddev *me = (struct viddev *)mfile_asansitty(self);
	REF struct vidtty *tty;
	tty = viddev_getactivetty(me);
	if unlikely(!tty)
		return 0; /* Indicate EOF */
	FINALLY_DECREF_UNLIKELY(tty);
	assert(tty->mf_ops->mo_stream != NULL &&
	       tty->mf_ops->mo_stream->mso_write == &ansittydev_v_write);
	return mfile_uwritev(tty, src, num_bytes, mode);
}

PUBLIC_CONST struct mfile_stream_ops const viddev_v_stream_ops = {
	.mso_write  = &viddev_v_write,
	.mso_writev = &viddev_v_writev,
	.mso_ioctl  = &viddev_v_ioctl,
	.mso_tryas  = &viddev_v_tryas,
};


/* [0..1] Default video device adapter. (Used to implement output in the builtin debugger) */
PUBLIC struct viddev_axref viddev_default = AXREF_INIT(NULL);


DECL_END

#endif /* !GUARD_KERNEL_SRC_DEV_VIDEO_C */
