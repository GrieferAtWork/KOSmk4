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
#ifndef GUARD_LIBVIDEO_GFX_SCREEN_C
#define GUARD_LIBVIDEO_GFX_SCREEN_C 1
#define LIBVIDEO_GFX_EXPOSE_INTERNALS
#define _KOS_SOURCE 1

#include "api.h"

#include <hybrid/compiler.h>

#include <hybrid/overflow.h>

#include <kos/anno.h>
#include <kos/io.h>
#include <kos/ioctl/svga.h>
#include <kos/sched/shared-lock.h>
#include <kos/types.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/perm.h>
#include <sys/syslog.h>

#include <assert.h>
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <malloc.h>
#include <malloca.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

#include <libphys/api.h>
#include <libphys/phys.h>
#include <libsvgadrv/api.h>
#include <libsvgadrv/chipset.h>
#include <libvideo/codec/api.h>
#include <libvideo/codec/codecs.h>
#include <libvideo/codec/format.h>
#include <libvideo/codec/palette.h>
#include <libvideo/codec/pixel.h>
#include <libvideo/codec/types.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/screen.h>
/**/

#include "ram-buffer.h"
#include "screen.h"

DECL_BEGIN

struct svga_screen: video_rambuffer {
	struct screen_buffer_ops          ss_ops;           /* [const] Screen buffer operators. */
	REF struct video_codec_handle    *ss_codec_handle;  /* [1..1][const] Custom codec keep-alive handle */
	fd_t                              ss_vdlck;         /* [const] Video lock file */
	void                             *ss_libphys;       /* [1..1][const] Handle for libphys */
	PMMAPPHYS                         ss_libphys_map;   /* [1..1][const] Helper to map physical memory */
	PMUNMAPPHYS                       ss_libphys_unmap; /* [1..1][const] Helper to unmap physical memory */
	void                             *ss_libsvgadrv;    /* [1..1][const] Handle for libsvgadrv */
	struct svga_chipset_driver const *ss_drv;           /* [1..1][const] SVGA driver */
	struct shared_lock                ss_cslock;        /* Lock for interfacing with `ss_cs' */
	struct svga_chipset               ss_cs;            /* [1..1][const] SVGA chipset */
};

#define _svga_screen_cs_reap(self)      (void)0
#define svga_screen_cs_reap(self)       (void)0
#define svga_screen_cs_mustreap(self)   0
#define svga_screen_cs_tryacquire(self) shared_lock_tryacquire(&(self)->ss_cslock)
#define svga_screen_cs_acquire(self)    shared_lock_acquire(&(self)->ss_cslock)
#define svga_screen_cs_acquire_nx(self) shared_lock_acquire_nx(&(self)->ss_cslock)
#define _svga_screen_cs_release(self)   shared_lock_release(&(self)->ss_cslock)
#define svga_screen_cs_release(self)    (shared_lock_release(&(self)->ss_cslock), svga_screen_cs_reap(self))
#define svga_screen_cs_acquired(self)   shared_lock_acquired(&(self)->ss_cslock)
#define svga_screen_cs_available(self)  shared_lock_available(&(self)->ss_cslock)


PRIVATE NONNULL((1, 2)) void CC
svga_screen_updaterect_noop(struct screen_buffer *__restrict self,
                            struct video_buffer_rect const *__restrict rect) {
	(void)self;
	(void)rect;
	COMPILER_IMPURE();
}

PRIVATE NONNULL((1, 2)) void CC
svga_screen_updaterects_noop(struct screen_buffer *__restrict self,
                             struct video_buffer_rect const *__restrict rects,
                             size_t n_rects) {
	(void)self;
	(void)rects;
	(void)n_rects;
	COMPILER_IMPURE();
}

PRIVATE NONNULL((1, 2)) void CC
svga_screen_updaterect_cs(struct screen_buffer *__restrict self,
                          struct video_buffer_rect const *__restrict rect) {
	struct svga_screen *me = (struct svga_screen *)self;
	struct svga_rect cs_rect;
	if unlikely(rect->vbr_startx <= 0) {
		cs_rect.svr_x = 0;
		if (OVERFLOW_USUB(rect->vbr_sizex, -rect->vbr_sizex, &cs_rect.svr_w) ||
		    cs_rect.svr_w > self->vb_size_x)
			cs_rect.svr_w = self->vb_size_x;
	} else {
		if (OVERFLOW_UCAST((video_coord_t)rect->vbr_startx, &cs_rect.svr_x) ||
		    cs_rect.svr_x >= self->vb_size_x)
			return;
		if (OVERFLOW_USUB(self->vb_size_x, cs_rect.svr_x, &cs_rect.svr_w))
			return;
	}
	if unlikely(rect->vbr_starty <= 0) {
		cs_rect.svr_y = 0;
		if (OVERFLOW_USUB(rect->vbr_sizey, -rect->vbr_sizey, &cs_rect.svr_h) ||
		    cs_rect.svr_h > self->vb_size_y)
			cs_rect.svr_h = self->vb_size_y;
	} else {
		if (OVERFLOW_UCAST((video_coord_t)rect->vbr_starty, &cs_rect.svr_y) ||
		    cs_rect.svr_y >= self->vb_size_y)
			return;
		if (OVERFLOW_USUB(self->vb_size_y, cs_rect.svr_y, &cs_rect.svr_h))
			return;
	}
	svga_screen_cs_acquire(me);
	(*me->ss_cs.sc_modeops.sco_updaterect)(&me->ss_cs, &cs_rect);
	svga_screen_cs_release(me);
}

PRIVATE NONNULL((1, 2)) void CC
svga_screen_updaterects_cs(struct screen_buffer *__restrict self,
                           struct video_buffer_rect const *__restrict rects,
                           size_t n_rects) {
	size_t i;
	for (i = 0; i < n_rects; ++i)
		svga_screen_updaterect_cs(self, &rects[i]);
}



PRIVATE NONNULL((1)) void CC
svga_screen_destroy(struct video_buffer *__restrict self) {
	struct svga_screen *me = (struct svga_screen *)self;
	assert(me->vb_ops == &me->ss_ops.sbo_video);
	/* Finalize */
	(*me->ss_cs.sc_ops.sco_fini)(&me->ss_cs);
	(*me->ss_libphys_unmap)(me->vb_data, me->vb_total);
	(void)dlclose(me->ss_libsvgadrv);
	(void)dlclose(me->ss_libphys);
	(void)close(me->ss_vdlck);
	if (me->vb_format.vf_pal)
		video_palette_decref(me->vb_format.vf_pal);
	video_codec_handle_decref(me->ss_codec_handle);
	(void)free(me);
}

#define LOGERR(format, ...) \
	syslog(LOG_ERR, "[libvideo][svga-screen:%d] " format, __LINE__, ##__VA_ARGS__)

PRIVATE WUNUSED NONNULL((1)) REF struct video_palette *CC
svga_palette_new(struct svga_chipset *__restrict cs, shift_t colorbits) {
	size_t i, palsize;
	struct video_palette *result;
	struct svga_palette_color *colors;
	palsize = (size_t)1 << colorbits;
	colors  = (struct svga_palette_color *)malloca(palsize, sizeof(struct svga_palette_color));
	if unlikely(!colors) {
		LOGERR("Failed to allocate palette color buffer: %m\n");
		goto err;
	}

	/* Load SVGA palette */
	(*cs->sc_modeops.sco_getpal)(cs, 0, palsize, colors);

	/* Allocate video palette */
	result = video_palette_create(palsize);
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
	return result;
err:
	return NULL;
}


PRIVATE NONNULL((1, 2)) void CC
svga_modeinfo_to_codec_specs(struct svga_modeinfo const *__restrict self,
                             struct video_codec_specs *__restrict result) {
	syslog(LOG_DEBUG,
	       "Video mode:\n"
	       "self->smi_flags          = %#x\n"
	       "self->smi_bits_per_pixel = %u\n"
	       "self->smi_colorbits      = %u\n"
	       "self->smi_rshift         = %u\n"
	       "self->smi_rbits          = %u\n"
	       "self->smi_gshift         = %u\n"
	       "self->smi_gbits          = %u\n"
	       "self->smi_bshift         = %u\n"
	       "self->smi_bbits          = %u\n"
	       "",
	       (unsigned int)self->smi_flags,
	       (unsigned int)self->smi_bits_per_pixel,
	       (unsigned int)self->smi_colorbits,
	       (unsigned int)self->smi_rshift,
	       (unsigned int)self->smi_rbits,
	       (unsigned int)self->smi_gshift,
	       (unsigned int)self->smi_gbits,
	       (unsigned int)self->smi_bshift,
	       (unsigned int)self->smi_bbits);
	bzero(result, sizeof(*result));
	if (self->smi_flags & SVGA_MODEINFO_F_PAL)
		result->vcs_flags |= VIDEO_CODEC_FLAG_PAL;
	if (self->smi_flags & SVGA_MODEINFO_F_BW)
		result->vcs_flags |= VIDEO_CODEC_FLAG_GRAY;

	result->vcs_bpp = self->smi_bits_per_pixel;
	if (result->vcs_flags & (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_GRAY)) {
		result->vcs_rmask = ((video_pixel_t)1 << self->smi_colorbits) - 1;
		result->vcs_gmask = result->vcs_rmask;
		result->vcs_bmask = result->vcs_rmask;
	} else {
		result->vcs_rmask = (((video_pixel_t)1 << self->smi_rbits) - 1) << self->smi_rshift;
		result->vcs_gmask = (((video_pixel_t)1 << self->smi_gbits) - 1) << self->smi_gshift;
		result->vcs_bmask = (((video_pixel_t)1 << self->smi_bbits) - 1) << self->smi_bshift;
	}
	result->vcs_amask = 0;
}

PRIVATE WUNUSED REF struct svga_screen *CC
svga_newscreen(struct screen_buffer_hint *hint) {
	fd_t svga;
	void *libsvgadrv;
	struct screen_buffer_hint _default_hint;
	PSVGA_CHIPSET_GETDRIVERS svga_chipset_getdrivers;
	struct openfd vdlck;
	struct svga_modeinfo *mode;
	struct video_codec_specs codec_specs;
	REF struct svga_screen *result;
	struct svga_chipset_driver const *driver;
	char csname[SVGA_CSNAMELEN];

	/* Access the SVGA video driver (/bin/init will have already loaded it) */
	svga = open("/dev/svga", O_RDWR | O_CLOEXEC);
	if unlikely(svga < 0) {
		LOGERR("Failed to open svga driver: %m\n");
		goto err;
	}

	/* Acquire a video lock. If  another video lock already exists,  this
	 * will block until that lock goes away. Since video locks are stored
	 * in file descriptors, a process  exiting while owning a video  lock
	 * will see that lock be closed automatically by the kernel.
	 *
	 * Additionally, the kernel links video locks against the libsvgadrv,
	 * which in turn keep a full  copy of the video chipset's  registers,
	 * meaning we're free to do whatever with want with the chipset,  and
	 * can  rest assured that  our process exiting  will restore a known-
	 * good register state, as well  as automatically switch back to  the
	 * terminal UI provided by /dev/console (aka. /dev/svga1) */
	bzero(&vdlck, sizeof(vdlck));
	vdlck.of_flags = IO_CLOEXEC;
	if (ioctl(svga, SVGA_IOC_MAKELCK, &vdlck) < 0) {
		LOGERR("SVGA_IOC_MAKELCK failed: %m\n");
		goto err_svga;
	}

	/* Figure out which chipset we're using (so we can more easily
	 * load  the user-land version of the driver to gain access to
	 * any chipset-specific I/O operations we might need) */
	if (ioctl(vdlck.of_hint, SVGA_IOC_GETCSNAME, csname) < 0) {
		LOGERR("SVGA_IOC_GETCSNAME failed: %m\n");
		goto err_svga_vdlck;
	}

	/* Make sure we  (ring#3) have I/O  permissions. These will  probably
	 * be needed by "libsvgadrv" in order to perform any chipset-specific
	 * I/O operations and so on. */
	if (iopl(3)) {
		LOGERR("iopl failed: %m\n");
		goto err_svga_vdlck;
	}

	/* Load "libsvgadrv" (user-land version) */
	libsvgadrv = dlopen(LIBSVGADRV_LIBRARY_NAME, RTLD_LOCAL);
	if unlikely(!libsvgadrv) {
		LOGERR("dlerror: %s\n", dlerror());
		goto err_svga_vdlck;
	}
	*(void **)&svga_chipset_getdrivers = dlsym(libsvgadrv, "svga_chipset_getdrivers");
	if unlikely(!svga_chipset_getdrivers) {
		LOGERR("dlerror: %s\n", dlerror());
		goto err_svga_vdlck_libsvgadrv;
	}

	/* Find the relevant chipset driver. */
	driver = (*svga_chipset_getdrivers)();
	if unlikely(!driver) {
		LOGERR("No drivers available\n");
		goto err_svga_vdlck_libsvgadrv;
	}
	while (strcmp(driver->scd_name, csname) != 0) {
		if unlikely(!driver->scd_probe) {
			LOGERR("No driver matching active chipset %q\n", csname);
			errno = ENODEV;
			goto err_svga_vdlck_libsvgadrv;
		}
		++driver;
	}

	/* Allocate the screen buffer control structure, and include
	 * space needed  to embed  libsvgadrv's chipset  controller. */
	{
		size_t bufsz = offsetof(struct svga_screen, ss_cs) +
		               driver->scd_cssize;
		result = (REF struct svga_screen *)malloc(bufsz);
		if unlikely(!result)
			goto err_svga_vdlck_libsvgadrv;
	}

	/* Initialize the chipset for user-space. */
	/* TODO: Add a second  function "driver->scd_open"  that's allowed to  assume that  the
	 *       chipset is correct, meaning it won't have to probe for the driver's existence. */
	bzero(&result->ss_cs.sc_modeops, sizeof(result->ss_cs.sc_modeops));
	if (!(*driver->scd_probe)(&result->ss_cs)) {
		LOGERR("Failed to init chipset %q\n", csname);
		goto err_svga_vdlck_libsvgadrv_r;
	}

	/* Allocate buffer for video mode. */
	mode = (struct svga_modeinfo *)malloca(result->ss_cs.sc_ops.sco_modeinfosize);
	if unlikely(!mode) {
		LOGERR("Failed to allocate mode buffer\n");
		goto err_svga_vdlck_libsvgadrv_r_cs;
	}

	if (hint) {
		/* Find video mode that matches "hint" the closest. */
find_with_hint:
		LOGERR("TODO: Mode hint\n");
		goto err_svga_vdlck_libsvgadrv_r_cs;
	} else {
		/* Find video mode that is currently active. */
		struct svga_csmode csmode;
		bzero(&csmode, sizeof(csmode));
		csmode.svcm_buf   = mode;
		csmode.svcm_bufsz = result->ss_cs.sc_ops.sco_modeinfosize;
		if unlikely(ioctl(vdlck.of_hint, SVGA_IOC_GETCSMODE, &csmode)) {
			LOGERR("Failed to determine chipset mode\n");
			goto err_svga_vdlck_libsvgadrv_r_cs_mode;
		}
		if unlikely(csmode.svcm_bufsz != result->ss_cs.sc_ops.sco_modeinfosize) {
			LOGERR("chipset %q: kernel mode size %#" PRIxSIZ " differs from expected size %#" PRIxSIZ "\n",
			       csname, csmode.svcm_bufsz, result->ss_cs.sc_ops.sco_modeinfosize);
			goto err_svga_vdlck_libsvgadrv_r_cs_mode;
		}

		/* Deal with special case: video is in text-mode */
		if (mode->smi_flags & SVGA_MODEINFO_F_TXT) {
			_default_hint.sbh_resx = mode->smi_resx * 9;
			_default_hint.sbh_resy = mode->smi_resy * 16;
			_default_hint.sbh_bpp  = 8;
			hint = &_default_hint;
			goto find_with_hint;
		}

		/* Initialize CS mode operators as per the currently set mode. */
		(*result->ss_cs.sc_ops.sco_curmode)(&result->ss_cs, mode);
	}

	if (mode->smi_flags & SVGA_MODEINFO_F_PLANAR) {
		/* TODO: Support for "SVGA_MODEINFO_F_PLANAR" */
	}

	/* Convert the SVGA video mode into libvideo codec specs. */
	svga_modeinfo_to_codec_specs(mode, &codec_specs);

	/* Build a codec from the newly constructed specs. */
	result->vb_format.vf_codec = video_codec_fromspecs(&codec_specs, &result->ss_codec_handle);
	if (!result->vb_format.vf_codec) {
		LOGERR("No codec for SVGA video mode\n");
		errno = ENODEV;
		goto err_svga_vdlck_libsvgadrv_r_cs_mode;
	}

	/* If necessary, construct a palette controller for the codec, and populate
	 * it with whatever is currently configured  by the chipset. In theory,  we
	 * could also just come up with a  new palette here, but again: use  what's
	 * already there, so another program can pre-configure it for us. */
	result->vb_format.vf_pal = NULL;
	if (result->vb_format.vf_codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_PAL) {
		shift_t cbits = result->vb_format.vf_codec->vc_specs.vcs_cbits;
		result->vb_format.vf_pal = svga_palette_new(&result->ss_cs, cbits);
		if unlikely(!result->vb_format.vf_pal) {
			LOGERR("Failed to allocate palette controller: %m\n");
			goto err_svga_vdlck_libsvgadrv_r_cs_mode_codec;
		}
	}

	/* Load physical memory mapping functions. */
	result->ss_libphys = dlopen(LIBPHYS_LIBRARY_NAME, RTLD_LOCAL);
	if unlikely(!result->ss_libphys) {
		LOGERR("dlerror: %s\n", dlerror());
		goto err_svga_vdlck_libsvgadrv_r_cs_mode_codec_pal;
	}
	*(void **)&result->ss_libphys_map = dlsym(result->ss_libphys, "mmapphys");
	if unlikely(!result->ss_libphys_map) {
		LOGERR("dlerror: %s\n", dlerror());
		goto err_svga_vdlck_libsvgadrv_r_cs_mode_codec_pal_libphys;
	}
	*(void **)&result->ss_libphys_unmap = dlsym(result->ss_libphys, "munmapphys");
	if unlikely(!result->ss_libphys_unmap) {
		LOGERR("dlerror: %s\n", dlerror());
		goto err_svga_vdlck_libsvgadrv_r_cs_mode_codec_pal_libphys;
	}

	/* If the video mode doesn't provide a custom frame
	 * buffer address, use the default VGA LFB address. */
	if (!(mode->smi_flags & SVGA_MODEINFO_F_LFB))
		mode->smi_lfb = (physaddr_t)0xA0000;

	/* Map screen memory into a physical buffer. */
	result->vb_stride = mode->smi_scanline;
	result->vb_total  = mode->smi_scanline * mode->smi_resy;
	result->vb_data   = (byte_t *)(*result->ss_libphys_map)(mode->smi_lfb, result->vb_total);
	if unlikely((void *)result->vb_data == MAP_FAILED) {
		LOGERR("Failed to map LFB: %m\n");
		goto err_svga_vdlck_libsvgadrv_r_cs_mode_codec_pal_libphys;
	}

	/* Fill in remaining fields of "result" */
	result->vb_refcnt     = 1;
	result->vb_ops        = &result->ss_ops.sbo_video;
	result->vb_size_x     = mode->smi_resx;
	result->vb_size_y     = mode->smi_resy;
	result->ss_vdlck      = vdlck.of_hint;
	result->ss_libsvgadrv = libsvgadrv;
	result->ss_drv        = driver;

	/* TODO: Need custom lock function here that prevents use of HW-accelerated
	 *       render functions, as well as calls "sco_hw_async_waitfor" on lock. */
	result->ss_ops.sbo_video.vi_rlock       = &rambuffer_lock;
	result->ss_ops.sbo_video.vi_wlock       = &rambuffer_lock;
	result->ss_ops.sbo_video.vi_unlock      = &rambuffer_unlock;
	result->ss_ops.sbo_video.vi_getgfx      = &rambuffer_getgfx;
	result->ss_ops.sbo_video.vi_gfx_noblend = &rambuffer_noblend;
	result->ss_ops.sbo_video.vi_destroy     = &svga_screen_destroy;
	shared_lock_init(&result->ss_cslock);

	/* Define the updaterects operators if needed by the chipset */
	if (result->ss_cs.sc_modeops.sco_updaterect) { /* FIXME: "sc_modeops" is only supposed to be valid after a mode was set! */
		result->ss_ops.sbo_updaterect  = &svga_screen_updaterect_cs;
		result->ss_ops.sbo_updaterects = &svga_screen_updaterects_cs;
	} else {
		result->ss_ops.sbo_updaterect  = &svga_screen_updaterect_noop;
		result->ss_ops.sbo_updaterects = &svga_screen_updaterects_noop;
	}

	/* Free our temporary mode buffer. */
	freea(mode);

	/* Close our handle to the SVGA base driver */
	(void)close(svga);

	/* And we're done! */
	return result;
/*err_svga_vdlck_libsvgadrv_r_cs_mode_codec_pal_libphys_data:
	(*result->ss_libphys_unmap)(result->vb_data, result->vb_total);*/
err_svga_vdlck_libsvgadrv_r_cs_mode_codec_pal_libphys:
	(void)dlclose(result->ss_libphys);
err_svga_vdlck_libsvgadrv_r_cs_mode_codec_pal:
	if (result->vb_format.vf_pal)
		video_palette_decref(result->vb_format.vf_pal);
err_svga_vdlck_libsvgadrv_r_cs_mode_codec:
	video_codec_handle_decref(result->ss_codec_handle);
err_svga_vdlck_libsvgadrv_r_cs_mode:
	freea(mode);
err_svga_vdlck_libsvgadrv_r_cs:
	(*result->ss_cs.sc_ops.sco_fini)(&result->ss_cs);
err_svga_vdlck_libsvgadrv_r:
	free(result);
err_svga_vdlck_libsvgadrv:
	(void)dlclose(libsvgadrv);
err_svga_vdlck:
	(void)close(vdlck.of_hint);
err_svga:
	(void)close(svga);
err:
	return NULL;
}


/* Creates+returns  a video buffer for the entire  screen (or return NULL and set
 * errno  on error). Note that screen buffer access requires `CAP_SYS_RAWIO', and
 * only  a single screen buffer can ever exist system-wide. If an attempt is made
 * to create a second screen buffer, this function will block until the first one
 * is destroyed, or the processing owning it exits.
 *
 * @param: hint: Hint regarding the intended video resolution (or "NULL" to  just
 *               use the same video mode as had already been set by whatever came
 *               before us). */
INTERN WUNUSED REF struct screen_buffer *CC
libvideo_screen_buffer_create(struct screen_buffer_hint *hint) {
	/* XXX: Support for other video drivers would go here... */
	return (REF struct screen_buffer *)svga_newscreen(hint);
}

DEFINE_PUBLIC_ALIAS(screen_buffer_create, libvideo_screen_buffer_create);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_SCREEN_C */
