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
#ifndef GUARD_LIBVIDEO_DRIVER_ADAPTER_SVGA_C
#define GUARD_LIBVIDEO_DRIVER_ADAPTER_SVGA_C 1
#define __VIDEO_BUFFER_const /* nothing */
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#ifdef HAVE_SVGA_ADAPTER
#include <hybrid/compiler.h>

#include <hybrid/overflow.h>

#include <kos/io.h>
#include <kos/ioctl/svga.h>
#include <sys/ioctl.h>
#include <sys/perm.h>
#include <sys/syslog.h>

#include <assert.h>
#include <atomic.h>
#include <dlfcn.h>
#include <errno.h>
#include <malloc.h>
#include <malloca.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

#include <libvideo/driver/adapter.h>
#include <libvideo/gfx/buffer/rambuffer.h>
#include <libvideo/gfx/codec/codec-extra.h>
#include <libvideo/gfx/codec/codec.h>
#include <libvideo/gfx/codec/palette.h>
#include <libvideo/rect.h>

#include "svga.h"

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset(p, c, n) memset(p, c, n)
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(p, c, n) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

#define LOGERR(format, ...) \
	syslog(LOG_ERR, "[libvideo-driver,svga.c:%d] " format, __LINE__, ##__VA_ARGS__)


PRIVATE ATTR_IN(1) ATTR_OUT(2) void CC
modeinfo_to_codecspecs(struct svga_modeinfo const *__restrict modeinfo,
                       struct video_codec_specs *__restrict specs) {
	bzero(specs, sizeof(*specs));
	if (modeinfo->smi_flags & SVGA_MODEINFO_F_PAL)
		specs->vcs_flags |= VIDEO_CODEC_FLAG_PAL;
	if (modeinfo->smi_flags & SVGA_MODEINFO_F_BW)
		specs->vcs_flags |= VIDEO_CODEC_FLAG_LUM;

	specs->vcs_bpp = modeinfo->smi_bits_per_pixel;
	if (specs->vcs_flags & (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_LUM)) {
		specs->vcs_rmask = ((video_pixel_t)1 << modeinfo->smi_colorbits) - 1;
		specs->vcs_gmask = specs->vcs_rmask;
		specs->vcs_bmask = specs->vcs_rmask;
	} else {
		specs->vcs_rmask = (((video_pixel_t)1 << modeinfo->smi_rbits) - 1) << modeinfo->smi_rshift;
		specs->vcs_gmask = (((video_pixel_t)1 << modeinfo->smi_gbits) - 1) << modeinfo->smi_gshift;
		specs->vcs_bmask = (((video_pixel_t)1 << modeinfo->smi_bbits) - 1) << modeinfo->smi_bshift;
	}
	specs->vcs_amask = 0;
}

/* Convert SVGA mode-info into an associated monitor-mode descriptor. */
PRIVATE WUNUSED ATTR_IN(1) ATTR_OUT(2) int CC
modeinfo_to_monitormode(struct svga_modeinfo const *__restrict modeinfo,
                        struct video_monitor_mode *__restrict monitor_mode) {
	/* Convert the SVGA video mode into libvideo codec specs. */
	if (modeinfo->smi_flags & SVGA_MODEINFO_F_TXT) {
		monitor_mode->vmm_codec = video_codec_lookup(VIDEO_CODEC_X_TILE16);
		if unlikely(!monitor_mode->vmm_codec)
			goto err;
		video_codec_incref(monitor_mode->vmm_codec);
	} else if (modeinfo->smi_bits_per_pixel == 4) {
		monitor_mode->vmm_codec = video_codec_lookup(VIDEO_CODEC_X_VBE16);
		if unlikely(!monitor_mode->vmm_codec)
			goto err;
		video_codec_incref(monitor_mode->vmm_codec);
	} else {
		struct video_codec_specs specs;
		modeinfo_to_codecspecs(modeinfo, &specs);
		monitor_mode->vmm_codec = video_codec_fromspecs(&specs);
		if unlikely(!monitor_mode->vmm_codec)
			goto err;
	}
	monitor_mode->vmm_xres = modeinfo->smi_resx;
	monitor_mode->vmm_yres = modeinfo->smi_resy;
	monitor_mode->vmm_hz   = 60; /* Guess */
	return 0;
err:
	return -1;
}

/* Returned buffer is malloc'd and must be free()'d by the caller.
 * This function must be called while `sva_cslock' is being  held.
 * @return: * :   SVGA mode info descriptor (suitable for use with the chipset)
 * @return: NULL: [errno=*] Error
 * @return: NULL: [errno=EINVAL] Given `monitor_mode' isn't a supported mode */
PRIVATE WUNUSED ATTR_IN(1) struct svga_modeinfo *CC
monitormode_to_modeinfo(struct svga_adapter *__restrict self,
                        struct video_monitor_mode const *__restrict monitor_mode) {
	uintptr_t iterator_index = 0;
	struct svga_modeinfo *result;
	result = (struct svga_modeinfo *)malloc(self->sva_cs.sc_ops.sco_modeinfosize);
	if unlikely(!result)
		goto err;
	while ((*self->sva_cs.sc_ops.sco_getmode)(&self->sva_cs, result, &iterator_index)) {
		struct video_codec const *codec;
		if (monitor_mode->vmm_xres != result->smi_resx)
			continue;
		if (monitor_mode->vmm_yres != result->smi_resy)
			continue;
		codec = monitor_mode->vmm_codec;
		if (result->smi_flags & SVGA_MODEINFO_F_TXT) {
			if (codec->vc_codec != VIDEO_CODEC_X_TILE16)
				continue;
		} else if (result->smi_bits_per_pixel == 4) {
			if (codec->vc_codec != VIDEO_CODEC_X_VBE16)
				continue;
		} else {
			struct video_codec_specs specs;
			modeinfo_to_codecspecs(result, &specs);
			if (codec != video_codec_lookup_specs(&specs)) {
				if (codec->vc_specs.vcs_flags != specs.vcs_flags)
					continue;
				if (codec->vc_specs.vcs_bpp != specs.vcs_bpp)
					continue;
				if (codec->vc_specs.vcs_rmask != specs.vcs_rmask)
					continue;
				if (codec->vc_specs.vcs_gmask != specs.vcs_gmask)
					continue;
				if (codec->vc_specs.vcs_bmask != specs.vcs_bmask)
					continue;
				if (codec->vc_specs.vcs_amask != specs.vcs_amask)
					continue;
			}
		}
		/* Found it! */
		return result;
	}
	free(result);
	errno = EINVAL;
err:
	return NULL;
}

PRIVATE NONNULL((1)) void CC
svga_close(struct video_adapter *__restrict self) {
	struct svga_adapter *me = video_adapter_assvga(self);
	struct svga_buffer *buffer = axref_ptr(&me->sva_buffer);
	if (buffer) {
		assertf(atomic_read(&buffer->vb_refcnt) == 1,
		        "Tried to close SVGA adapter while "
		        "display buffer still referenced");
		atomic_write(&buffer->vb_refcnt, 0);
		video_buffer_destroy(buffer);
	}
	if (me->sva_modeinfo) {
		video_monitor_mode_fini(&me->sva_mode);
		free(me->sva_modeinfo);
	}
	(*me->sva_cs.sc_ops.sco_fini)(&me->sva_cs);
	(void)dlclose(me->sva_libphys);
	(void)dlclose(me->sva_libsvgadrv);
	(void)close(me->sva_vdlck);
	free(me);
}

PRIVATE WUNUSED ATTR_INOUT(1) REF struct video_monitor *CC
svga_getmonitor(struct video_adapter *__restrict self, size_t index) {
	REF struct video_monitor *result;
	struct svga_adapter *me = video_adapter_assvga(self);
	if (index != 0) {
		errno = ERANGE;
		return NULL;
	}
	result = &me->sva_monitor;
	video_monitor_incref(result);
	return result;
}


/* Populate descriptors with info regarding the currently set video mode.
 * Must  be called if  `svga_adapter_modeset() == false' when the display
 * buffer is requested.
 * Caller must be holding the CS-lock. */
PRIVATE WUNUSED ATTR_INOUT(1) int CC
svga_set_current_mode(struct svga_adapter *__restrict self) {
	struct svga_csmode csmode;
	struct svga_modeinfo *modeinfo;
	assert(!self->sva_modeinfo);
	modeinfo = (struct svga_modeinfo *)malloc(self->sva_cs.sc_ops.sco_modeinfosize);
	if unlikely(!modeinfo)
		goto err;

	/* Load currently active video mode */
	bzero(&csmode, sizeof(csmode));
	csmode.svcm_buf   = modeinfo;
	csmode.svcm_bufsz = self->sva_cs.sc_ops.sco_modeinfosize;
	if unlikely(ioctl(self->sva_vdlck, SVGA_IOC_GETCSMODE, &csmode)) {
		LOGERR("Failed to determine chipset mode\n");
		goto err_modeinfo;
	}
	if unlikely(csmode.svcm_bufsz != self->sva_cs.sc_ops.sco_modeinfosize) {
		LOGERR("chipset %q: kernel mode size %#" PRIxSIZ " differs from expected size %#" PRIxSIZ "\n",
		       self->sva_drv->scd_name, csmode.svcm_bufsz, self->sva_cs.sc_ops.sco_modeinfosize);
		errno = EIO;
		goto err_modeinfo;
	}

	/* Initialize CS mode operators as per the currently set mode. */
	(*self->sva_cs.sc_ops.sco_curmode)(&self->sva_cs, modeinfo);

	/* Load a descriptor for the currently active high-level video mode */
	if unlikely(modeinfo_to_monitormode(modeinfo, &self->sva_mode))
		goto err_modeinfo;
	assert(!self->sva_modeinfo);
	self->sva_modeinfo = modeinfo; /* Inherit */
	return 0;
err_modeinfo:
	free(modeinfo);
err:
	return -1;
}


PRIVATE ATTR_INOUT(1) ATTR_IN(2) void LIBVIDEO_GFX_CC
svga_hw_updaterect(struct video_display *__restrict self,
                   struct video_rect const *__restrict rect) {
	struct svga_adapter *me = svga_monitor_getadapter(video_display_assvga(self));
	struct svga_rect cs_rect;
	struct video_rect in_rect = *rect;
	svga_res_t cs_xend, cs_yend;
	if (in_rect.vr_xmin < 0) {
		if (OVERFLOW_USUB(in_rect.vr_xdim, (video_dim_t)-in_rect.vr_xmin, &in_rect.vr_xdim))
			return;
		in_rect.vr_xmin = 0;
	}
	if (in_rect.vr_ymin < 0) {
		if (OVERFLOW_USUB(in_rect.vr_ydim, (video_dim_t)-in_rect.vr_ymin, &in_rect.vr_ydim))
			return;
		in_rect.vr_ymin = 0;
	}
	if (OVERFLOW_UCAST(in_rect.vr_xmin, &cs_rect.svr_x))
		return;
	if (OVERFLOW_UCAST(in_rect.vr_ymin, &cs_rect.svr_y))
		return;
	if (OVERFLOW_UADD(in_rect.vr_xmin, in_rect.vr_xdim, &cs_xend))
		cs_xend = (svga_res_t)-1;
	if (OVERFLOW_UADD(in_rect.vr_ymin, in_rect.vr_ydim, &cs_yend))
		cs_yend = (svga_res_t)-1;
	cs_rect.svr_w = cs_xend - cs_rect.svr_x;
	cs_rect.svr_h = cs_yend - cs_rect.svr_y;
	svga_adapter_cs_acquire(me);
	if unlikely(cs_xend > (svga_res_t)me->sva_mode.vmm_xres) {
		if (cs_rect.svr_x >= (svga_res_t)me->sva_mode.vmm_xres)
			goto done;
		cs_rect.svr_w = (svga_res_t)me->sva_mode.vmm_xres - cs_rect.svr_x;
	}
	if unlikely(cs_yend > (svga_res_t)me->sva_mode.vmm_yres) {
		if (cs_rect.svr_y >= (svga_res_t)me->sva_mode.vmm_yres)
			goto done;
		cs_rect.svr_h = (svga_res_t)me->sva_mode.vmm_yres - cs_rect.svr_y;
	}
	(*me->sva_cs.sc_modeops.sco_updaterect)(&me->sva_cs, &cs_rect);
done:
	svga_adapter_cs_release(me);
}

PRIVATE ATTR_INOUT(1) ATTR_IN(2) void LIBVIDEO_GFX_CC
svga_hw_updaterects(struct video_display *__restrict self,
                    struct video_rect const *__restrict rects, size_t n_rects) {
	for (; n_rects; --n_rects, ++rects)
		svga_hw_updaterect(self, rects);
}

PRIVATE NONNULL((1, 2)) void CC
svga_noop_updaterect(struct video_display *__restrict self,
                     struct video_rect const *__restrict rect) {
	(void)self;
	(void)rect;
	COMPILER_IMPURE();
}

PRIVATE NONNULL((1, 2)) void CC
svga_noop_updaterects(struct video_display *__restrict self,
                      struct video_rect const *__restrict rects,
                      size_t n_rects) {
	(void)self;
	(void)rects;
	(void)n_rects;
	COMPILER_IMPURE();
}



PRIVATE NONNULL((1)) void LIBVIDEO_GFX_FCC
svga_buffer_destroy(struct video_buffer *__restrict self) {
	struct svga_buffer *me = video_buffer_assvga(self);
	struct svga_adapter *svga = svga_buffer_getadapter(me);
	(*svga->sva_libphys_unmap)(me->rb_data, me->svb_rb_total);
	__video_buffer_fini_common(me);
	free(me);
}


PRIVATE WUNUSED NONNULL((1)) REF struct video_palette *CC
svga_palette_new(struct svga_adapter *__restrict self, shift_t colorbits) {
	video_pixel_t i, palsize;
	struct video_palette *result;
	struct svga_palette_color *colors;
	palsize = (video_pixel_t)1 << colorbits;
	colors  = (struct svga_palette_color *)malloca(palsize, sizeof(struct svga_palette_color));
	if unlikely(!colors) {
		LOGERR("Failed to allocate palette color buffer: %m\n");
		goto err;
	}

	/* Load SVGA palette */
	(*self->sva_cs.sc_modeops.sco_getpal)(&self->sva_cs, 0, palsize, colors);

	/* Allocate video palette */
	result = video_domain_newpalette(self, palsize);
	if unlikely(!result) {
		LOGERR("Failed to allocate palette controller: %m\n");
		freea(colors);
		goto err;
	}
	for (i = 0; i < palsize; ++i) {
		struct svga_palette_color color = colors[i];
		video_color_t vcolor = VIDEO_COLOR_RGB(color.spc_r, color.spc_g, color.spc_b);
		result->vp_pal[i] = vcolor;
	}
	freea(colors);
	return video_palette_optimize(result);
err:
	return NULL;
}


/* Create a new video buffer for the video mode currently set in "self" */
PRIVATE WUNUSED ATTR_INOUT(1) REF struct svga_buffer *CC
svga_newbuffer(struct svga_adapter *__restrict self) {
	REF struct svga_buffer *result;
	struct video_buffer_ops const *rambuffer_ops;
	struct svga_modeinfo *modeinfo;
	physaddr_t lfb_addr;
	result = (REF struct svga_buffer *)malloc(sizeof(struct svga_buffer));
	if unlikely(!result)
		goto err;

	/* Inherit all operators from "rambuffer_ops" by default. */
	rambuffer_ops = video_rambuffer_ops();
	memcpy(&result->svb_ops, rambuffer_ops, sizeof(struct video_buffer_ops));

	/* Override certain operators */
	result->svb_ops.vi_destroy = &svga_buffer_destroy;
	if (self->sva_cs.sc_modeops.sco_hw_async_copyrect ||
	    self->sva_cs.sc_modeops.sco_hw_async_fillrect) {
		/* TODO: Hook into GFX to provide hardware-accelerated fill/blit operators */
	}

	/* Map LFB for "result" */
	modeinfo = self->sva_modeinfo;
	result->rb_stride    = modeinfo->smi_scanline;
	result->svb_rb_total = modeinfo->smi_scanline * modeinfo->smi_resy;
	lfb_addr = modeinfo->smi_lfb;
	if (!(modeinfo->smi_flags & SVGA_MODEINFO_F_LFB))
		lfb_addr = (physaddr_t)0xA0000;
	result->rb_data = (byte_t *)(*self->sva_libphys_map)(lfb_addr, result->svb_rb_total);
	if unlikely(result->rb_data == MAP_FAILED)
		goto err_r;

	/* Allocate palette (if necessary) */
	result->vb_surf.vs_flags = VIDEO_GFX_F_NORMAL;
	result->vb_surf.vs_pal = NULL;
	if (self->sva_mode.vmm_codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_PAL) {
		shift_t cbits = self->sva_mode.vmm_codec->vc_specs.vcs_cbits;
		result->vb_surf.vs_pal = svga_palette_new(self, cbits);
		if unlikely(!result->vb_surf.vs_pal)
			goto err_r_data;
		result->vb_surf.vs_flags |= VIDEO_GFX_F_PALOBJ;
	}

	/* Fill in remaining fields. */
	result->vb_codec = self->sva_mode.vmm_codec;
	video_codec_incref(result->vb_codec);
	__video_buffer_init_domain(result, self);
	__video_buffer_init_ops(result, &result->svb_ops);
	__video_buffer_init_dim(result, modeinfo->smi_resx, modeinfo->smi_resy);
	result->vb_surf.vs_buffer = result;
	result->vb_refcnt = 1;
	return result;
err_r_data:
	(*self->sva_libphys_unmap)(result->rb_data, result->svb_rb_total);
err_r:
	free(result);
err:
	return NULL;
}


/* Return a video buffer for interfacing with SVGA display memory */
PRIVATE WUNUSED ATTR_INOUT(1) REF struct video_buffer *CC
svga_getbuffer(struct video_display *__restrict self) {
	struct svga_adapter *me = svga_monitor_getadapter(video_display_assvga(self));
	REF struct video_buffer *result = axref_get(&me->sva_buffer);
	if (!result) {
		svga_adapter_cs_acquire(me);
		result = axref_get(&me->sva_buffer);
		if (!result) {
			/* If no mode has been set yet, load whatever is currently set by video hardware right now. */
			if (!svga_adapter_modeset(me)) {
				if unlikely(svga_set_current_mode(me))
					goto err_lock;
				assert(svga_adapter_modeset(me));
			}

			/* Update updaterect() operator linkage as appropriate for the current video mode. */
			if (me->sva_cs.sc_modeops.sco_updaterect) {
				atomic_write(&me->sva_monitor_ops.vmo_display.vdo_updaterect, &svga_hw_updaterect);
				atomic_write(&me->sva_monitor_ops.vmo_display.vdo_updaterects, &svga_hw_updaterects);
			} else {
				atomic_write(&me->sva_monitor_ops.vmo_display.vdo_updaterect, &svga_noop_updaterect);
				atomic_write(&me->sva_monitor_ops.vmo_display.vdo_updaterects, &svga_noop_updaterects);
			}

			result = svga_newbuffer(me);
			if unlikely(!result)
				goto err_lock;
			axref_set(&me->sva_buffer, result);
		}
		svga_adapter_cs_release(me);
	}
	return result;
err_lock:
	svga_adapter_cs_release(me);
	return NULL;
}


PRIVATE WUNUSED ATTR_INOUT(1) NONNULL((2)) ssize_t CC
svga_lsmodes(struct video_monitor *__restrict self,
             video_monitor_lsmodes_cb_t cb, void *cookie) {
	ssize_t temp, result = 0;
	struct svga_modeinfo *modeinfo;
	struct svga_adapter *me = svga_monitor_getadapter(video_monitor_assvga(self));
	uintptr_t iterator_index = 0;
	modeinfo = (struct svga_modeinfo *)malloc(me->sva_cs.sc_ops.sco_modeinfosize);
	if unlikely(!modeinfo)
		goto err;
	svga_adapter_cs_acquire(me);
	while ((*me->sva_cs.sc_ops.sco_getmode)(&me->sva_cs, modeinfo, &iterator_index)) {
		struct video_monitor_mode mode;
		svga_adapter_cs_release(me);
		if unlikely(modeinfo_to_monitormode(modeinfo, &mode))
			goto err_modeinfo;
		temp = (*cb)(cookie, &mode);
		video_monitor_mode_fini(&mode);
		if unlikely(temp < 0) {
			result = temp;
			goto done;
		}
		result += temp;
		svga_adapter_cs_acquire(me);
	}
	svga_adapter_cs_release(me);
done:
	free(modeinfo);
	return result;
err_modeinfo:
	free(modeinfo);
err:
	return -1;
}

PRIVATE WUNUSED ATTR_INOUT(1) ATTR_OUT(2) int CC
svga_getmode(struct video_monitor *__restrict self,
             struct video_monitor_mode *__restrict mode) {
	struct svga_adapter *me = svga_monitor_getadapter(video_monitor_assvga(self));
	svga_adapter_cs_acquire(me);
	/* If no mode has been set yet, load whatever is currently set by video hardware right now. */
	if (!svga_adapter_modeset(me)) {
		if unlikely(svga_set_current_mode(me))
			goto err_lock;
		assert(svga_adapter_modeset(me));
	}
	memcpy(mode, &me->sva_mode, sizeof(struct video_monitor_mode));
	video_codec_incref(mode->vmm_codec);
	svga_adapter_cs_release(me);
	return 0;
err_lock:
	svga_adapter_cs_release(me);
	return -1;
}

PRIVATE WUNUSED ATTR_INOUT(1) ATTR_IN(2) int CC
svga_setmode(struct video_monitor *__restrict self,
             struct video_monitor_mode const *__restrict mode) {
	struct svga_modeinfo *old_modeinfo;
	struct svga_modeinfo *modeinfo;
	struct svga_adapter *me = svga_monitor_getadapter(video_monitor_assvga(self));
	svga_adapter_cs_acquire(me);
	modeinfo = monitormode_to_modeinfo(me, mode);
	if unlikely(!modeinfo)
		goto err_lock;

	/* Load the new video mode into hardware */
	(*me->sva_cs.sc_ops.sco_setmode)(&me->sva_cs, modeinfo);

	/* Remember the new video mode */
	old_modeinfo = me->sva_modeinfo;
	if (old_modeinfo)
		video_monitor_mode_fini(&me->sva_mode);
	memcpy(&me->sva_mode, mode, sizeof(struct video_monitor_mode));
	axref_clear(&me->sva_buffer);
	svga_adapter_cs_release(me);
	free(old_modeinfo);
	return 0;
err_lock:
	svga_adapter_cs_release(me);
	return -1;
}



/* Create (and return) a new video lock */
PRIVATE WUNUSED fd_t CC create_video_lock(fd_t svga) {
	struct openfd vdlck;
	bzero(&vdlck, sizeof(vdlck));
	vdlck.of_flags = IO_CLOEXEC;
	if (ioctl(svga, SVGA_IOC_MAKELCK, &vdlck) < 0) {
		LOGERR("SVGA_IOC_MAKELCK failed: %m\n");
		return -1;
	}
	return vdlck.of_hint;
}

/* Try to open `fd' as an SVGA video adapter.
 * @return: * :   Success
 * @return: NULL: Error (s.a. `errno')
 * @return: SVGA_TRYOPEN_BADDEV: Given `fd' is not for `/dev/svga' */
INTERN WUNUSED struct svga_adapter *CC
svga_tryopen(/*inherited(on_success)*/ fd_t fd) {
	char csname[SVGA_CSNAMELEN];
	struct svga_adapter *result;
	{
		PSVGA_CHIPSET_GETDRIVERS svga_chipset_getdrivers;
		struct svga_chipset_driver const *result__sva_drv;
		size_t sizeof_result;
		fd_t result__sva_vdlck;
		void *result__sva_libsvgadrv;

		/* Lookup SVGA chipset name (this also asserts that "fd" is for /dev/svga) */
		if (ioctl(fd, SVGA_IOC_GETCSNAME, csname) < 0) {
			LOGERR("SVGA_IOC_GETCSNAME failed: %m\n");
			return SVGA_TRYOPEN_BADDEV;
		}

		/* Acquire an SVGA video lock. This is a global lock, which also guaranties
		 * that all code below is executed by exactly _1_ thread (system-wide),  so
		 * there is no need for any sort of extra locking. */
		result__sva_vdlck = create_video_lock(fd);
		if unlikely(result__sva_vdlck < 0)
			goto err;

		/* Make sure we  (ring#3) have I/O  permissions. These will  probably
		 * be needed by "libsvgadrv" in order to perform any chipset-specific
		 * I/O operations and so on. */
		if (iopl(3)) {
			LOGERR("iopl failed: %m\n");
_err_vdlck:
			(void)close(result__sva_vdlck);
			goto err;
		}

		/* Load "libsvgadrv" (user-land version) */
		result__sva_libsvgadrv = dlopen(LIBSVGADRV_LIBRARY_NAME, RTLD_LOCAL);
		if unlikely(!result__sva_libsvgadrv) {
			LOGERR("dlerror: %s\n", dlerror());
			goto _err_vdlck;
		}
		*(void **)&svga_chipset_getdrivers = dlsym(result__sva_libsvgadrv, "svga_chipset_getdrivers");
		if unlikely(!svga_chipset_getdrivers) {
			LOGERR("dlerror: %s\n", dlerror());
_err_vdlck_libsvgadrv:
			(void)dlclose(result__sva_libsvgadrv);
			goto _err_vdlck;
		}

		/* Find the relevant chipset driver. */
		result__sva_drv = (*svga_chipset_getdrivers)();
		if unlikely(!result__sva_drv) {
			LOGERR("No drivers available\n");
			goto _err_vdlck_libsvgadrv;
		}
		while (strcmp(result__sva_drv->scd_name, csname) != 0) {
			if unlikely(!result__sva_drv->scd_probe) {
				LOGERR("No driver matching active chipset %q\n", csname);
				errno = ENODEV;
				goto _err_vdlck_libsvgadrv;
			}
			++result__sva_drv;
		}

		/* Allocate the screen buffer control structure, and include
		 * space needed  to embed  libsvgadrv's chipset  controller. */
		sizeof_result = offsetof(struct svga_adapter, sva_cs) + result__sva_drv->scd_cssize;
		result = (struct svga_adapter *)malloc(sizeof_result);
		if unlikely(!result)
			goto _err_vdlck_libsvgadrv;
		/* Fill in fields that were already calculated above. */
		result->sva_drv        = result__sva_drv;
		result->sva_vdlck      = result__sva_vdlck;
		result->sva_libsvgadrv = result__sva_libsvgadrv;
	}

	/* Load libphys (which we are going to need for mapping the display LFB) */
	result->sva_libphys = dlopen(LIBPHYS_LIBRARY_NAME, RTLD_LOCAL);
	if unlikely(!result->sva_libphys) {
		LOGERR("dlerror: %s\n", dlerror());
		goto err_r_vdlck_libsvgadrv;
	}
	*(void **)&result->sva_libphys_map = dlsym(result->sva_libphys, "mmapphys");
	if unlikely(!result->sva_libphys_map) {
		LOGERR("dlerror: %s\n", dlerror());
		goto err_r_vdlck_libsvgadrv_libphys;
	}
	*(void **)&result->sva_libphys_unmap = dlsym(result->sva_libphys, "munmapphys");
	if unlikely(!result->sva_libphys_unmap) {
		LOGERR("dlerror: %s\n", dlerror());
		goto err_r_vdlck_libsvgadrv_libphys;
	}

	/* Initialize the chipset for user-space. */
	/* TODO: Add a second  function "driver->scd_open"  that's allowed to  assume that  the
	 *       chipset is correct, meaning it won't have to probe for the driver's existence. */
	bzero(&result->sva_cs.sc_modeops, sizeof(result->sva_cs.sc_modeops));
	if (!(*result->sva_drv->scd_probe)(&result->sva_cs)) {
		LOGERR("Failed to init chipset %q\n", csname);
		goto err_r_vdlck_libsvgadrv_libphys;
	}

	/* Re-use RAM-domain operators */
	{
		struct video_domain const *ramdomain = video_ramdomain();
		result->vd_newbuffer       = ramdomain->vd_newbuffer;
		result->vd_formem          = ramdomain->vd_formem;
		result->vd_supported_codec = ramdomain->vd_supported_codec;
		result->vd_newpalette      = ramdomain->vd_newpalette;
	}

	/* Fill in other fields of "result" */
	result->sva_modeinfo = NULL; /* NULL here indicates that mode has not been set (s.a. `svga_adapter_modeset()') */
	result->vad_ops = &result->sva_adapter_ops;
	result->sva_adapter_ops.vdro_close      = &svga_close;
	result->sva_adapter_ops.vdro_getmonitor = &svga_getmonitor;
	result->sva_monitor.vd_ops    = &result->sva_monitor_ops.vmo_display;
	result->sva_monitor.vd_domain = result;
	result->sva_monitor.vd_refcnt = 1;
	DBG_memset(&result->sva_monitor_ops.vmo_display.vdo_destroy, 0xcc,
	           sizeof(result->sva_monitor_ops.vmo_display.vdo_destroy));
	result->sva_monitor_ops.vmo_display.vdo_getbuffer = &svga_getbuffer;
	/* The updaterect() operators get overwritten during mode-set as appropriate */
	result->sva_monitor_ops.vmo_display.vdo_updaterect  = &svga_noop_updaterect;
	result->sva_monitor_ops.vmo_display.vdo_updaterects = &svga_noop_updaterects;
	result->sva_monitor_ops.vmo_lsmodes = &svga_lsmodes;
	result->sva_monitor_ops.vmo_getmode = &svga_getmode;
	result->sva_monitor_ops.vmo_setmode = &svga_setmode;
	shared_lock_init(&result->sva_cslock);
	axref_init(&result->sva_buffer, NULL);

	(void)close(fd); /* Inherit on success (though we don't need it since we have a video lock) */
	return result;
/*
err_r_vdlck_libsvgadrv_libphys_cs:
	(*result->sva_cs.sc_ops.sco_fini)(&result->sva_cs);*/
err_r_vdlck_libsvgadrv_libphys:
	(void)dlclose(result->sva_libphys);
err_r_vdlck_libsvgadrv:
	(void)dlclose(result->sva_libsvgadrv);
/*err_r_vdlck:*/
	(void)close(result->sva_vdlck);
/*err_r:*/
	free(result);
err:
	return NULL;
}

DECL_END
#endif /* HAVE_SVGA_ADAPTER */

#endif /* !GUARD_LIBVIDEO_DRIVER_ADAPTER_SVGA_C */
