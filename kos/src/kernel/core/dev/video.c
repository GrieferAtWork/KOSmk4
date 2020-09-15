/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_DEV_VIDEO_C
#define GUARD_KERNEL_SRC_DEV_VIDEO_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/ansitty.h>
#include <dev/char.h>
#include <dev/video.h>
#include <kernel/types.h>
#include <kernel/user.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <kos/ioctl/video.h>
#include <linux/kd.h>
#include <linux/vt.h>

#include <assert.h>
#include <string.h>

#include <libvideo/codec/codecs.h>

DECL_BEGIN

LOCAL ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL vd_format_istext)(struct vd_format const *__restrict self) {
	return self->vdf_codec == VIDEO_CODEC_NONE;
}

PRIVATE NONNULL((1)) void KCALL
video_device_set_first_format(struct video_device *__restrict self,
                              bool first_tty_format) THROWS(...) {
	size_t i;
	struct vd_format fmt;
	for (i = 0;; ++i) {
		if (!(*self->vd_ops.vdf_listfmt)(self, &fmt, i, 1))
			break;
		if (vd_format_istext(&fmt) == first_tty_format) {
			(*self->vd_ops.vdf_setfmt)(self, &fmt);
			return;
		}
	}
	THROW(E_INVALID_ARGUMENT_BAD_VALUE,
	      E_INVALID_ARGUMENT_CONTEXT_VIDEO_MODE,
	      first_tty_format ? KD_TEXT : KD_GRAPHICS);
}

/* Generic video device ioctl() handler. */
PUBLIC NONNULL((1)) syscall_slong_t KCALL
video_device_ioctl(struct character_device *__restrict self, syscall_ulong_t cmd,
                   USER UNCHECKED void *arg, iomode_t mode) THROWS(...) {
	struct video_device *me;
	me = (struct video_device *)self;
	switch (cmd) {

	case VIDEOIO_LISTFORMAT: {
		size_t count;
		struct vd_lsfmt_struct data;
		validate_writable(arg, sizeof(struct vd_lsfmt_struct));
		memcpy(&data, arg, sizeof(struct vd_lsfmt_struct));
		COMPILER_READ_BARRIER();
		validate_writablem(data.lsf_buf, data.lsf_limit, sizeof(struct vd_format));
		count = (*me->vd_ops.vdf_listfmt)(me, data.lsf_buf, data.lsf_offset, data.lsf_limit);
		COMPILER_WRITE_BARRIER();
		((USER CHECKED struct vd_lsfmt_struct *)arg)->lsf_limit = (u32)count;
	}	break;

	case VIDEOIO_GETFORMAT:
		validate_writable(arg, sizeof(struct vd_format));
		(*me->vd_ops.vdf_getfmt)(me, (USER CHECKED struct vd_format *)arg);
		break;

	case VIDEOIO_SETFORMAT:
		validate_readable(arg, sizeof(struct vd_format));
		(*me->vd_ops.vdf_setfmt)(me, (USER CHECKED struct vd_format const *)arg);
		break;

	case VIDEOIO_GETPAL: {
		struct vd_pal_struct data;
		if (!me->vd_ops.vdf_getpal)
			goto fallback;
		validate_readable(arg, sizeof(struct vd_pal_struct));
		memcpy(&data, arg, sizeof(struct vd_pal_struct));
		COMPILER_READ_BARRIER();
		validate_writablem(data.vp_pal, VIDEO_CODEC_PALSIZ(data.vp_codec), sizeof(vd_color_t));
		(*me->vd_ops.vdf_getpal)(me, data.vp_codec, data.vp_pal);
	}	break;

	case VIDEOIO_SETPAL: {
		struct vd_pal_struct data;
		if (!me->vd_ops.vdf_setpal)
			goto fallback;
		validate_readable(arg, sizeof(struct vd_pal_struct));
		memcpy(&data, arg, sizeof(struct vd_pal_struct));
		COMPILER_READ_BARRIER();
		validate_readablem_opt(data.vp_pal, VIDEO_CODEC_PALSIZ(data.vp_codec), sizeof(vd_color_t));
		(*me->vd_ops.vdf_setpal)(me, data.vp_codec, data.vp_pal);
	}	break;

	case KDSETMODE: {
		if ((uintptr_t)arg == KD_TEXT) {
			video_device_set_first_format(me, true);
		} else if ((uintptr_t)arg == KD_GRAPHICS) {
			video_device_set_first_format(me, false);
		} else {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_VIDEO_MODE,
			      arg);
		}
	}	break;

	case KDGETMODE: {
		struct vd_format fmt;
		(*me->vd_ops.vdf_getfmt)(me, &fmt);
		validate_writable(arg, sizeof(int));
		*(USER CHECKED int *)arg = vd_format_istext(&fmt) ? KD_TEXT : KD_GRAPHICS;
	}	break;

	case VT_OPENQRY: {
		validate_writable(arg, sizeof(int));
		*(USER CHECKED int *)arg = 0;
	}	break;

	case VT_GETSTATE: {
		USER CHECKED struct vt_stat *vs;
		validate_writable(arg, sizeof(struct vt_stat));
		vs = (USER CHECKED struct vt_stat *)arg;
		vs->v_active = 0;
		vs->v_state  = 1;
	}	break;

	case VT_ACTIVATE:
		/* No-op... (for now) */
		break;

	case VT_WAITACTIVE:
		/* No-op... (for now) */
		break;

	case VT_DISALLOCATE:
		/* No-op... (for now) */
		break;

	case VT_RELDISP:
		/* No-op... (for now) */
		break;

	case VT_GETMODE: {
		USER CHECKED struct vt_mode *vs;
		validate_writable(arg, sizeof(struct vt_mode));
		vs = (USER CHECKED struct vt_mode *)arg;
		vs->mode   = VT_AUTO;
		vs->waitv  = 0;
		vs->relsig = 0;
		vs->acqsig = 0;
		vs->frsig  = 0;
	}	break;

	case VT_SETMODE:
		/* No-op... (for now) */
		break;

//TODO:	case PIO_CMAP:
//TODO:		validate_readable(arg, 48);
//TODO:		break;

	default:
		/* Fallback: Try to service a generic ansi ioctl() */
fallback:
		return ansitty_device_ioctl(self, cmd, arg, mode);
		break;
	}
	return 0;
}



PRIVATE NONNULL((1)) void LIBANSITTY_CC
video_stub_putc(struct ansitty *__restrict UNUSED(self),
                char32_t UNUSED(ch)) {
	/* no-op */
}

PRIVATE struct ansitty_operators const video_stubtty = {
	/* .ato_putc = */ &video_stub_putc,
};

/* Initialize a given video device.
 * NOTE: `ops->ato_output' must be set to NULL when calling this function.
 *       The internal routing of this callback to injecting keyboard output
 *       is done dynamically when the ANSI TTY is connected to the output
 *       channel of a `struct tty_device'
 * This function initializes the following operators:
 *   - cd_type.ct_write = &ansitty_device_write;  // Mustn't be re-assigned!
 *   - cd_type.ct_fini  = &video_device_fini;     // Must be called by an override
 *   - cd_type.ct_ioctl = &video_device_ioctl;    // Must be called by an override
 * The following operators must still be defined by the caller:
 *   - cd_type.ct_mmap  = &...;  // mmap() the linear frame buffer for the current video format
 *                               //  - The behavior of mmap() in terminal mode is weakly undefined
 *                               //  - The contents/behavior of old mappings after a mode change
 *                               //    are weakly undefined
 */
PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL video_device_cinit)(struct video_device *__restrict self,
                                  struct video_device_ops const *__restrict ops,
                                  struct ansitty_operators const *tty_ops) {
	assert(ops->vdf_listfmt);
	assert(ops->vdf_getfmt);
	assert(ops->vdf_setfmt);
	assert((ops->vdf_getpal != NULL) == (ops->vdf_setpal != NULL));
	memcpy(&self->vd_ops, ops, sizeof(struct video_device_ops));
	if (!tty_ops)
		tty_ops = &video_stubtty;
	ansitty_device_cinit(self, tty_ops);
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_DEV_VIDEO_C */
