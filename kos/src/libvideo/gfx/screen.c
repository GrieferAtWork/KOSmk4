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
#define _KOS_SOURCE 1

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <kos/io.h>
#include <kos/ioctl/svga.h>
#include <kos/types.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/perm.h>
#include <sys/syslog.h>

#include <assert.h>
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
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
#include <libvideo/gfx/buffer.h>
/**/

#include "ram-buffer.h"
#include "screen.h"

DECL_BEGIN

struct svga_screen_buffer: video_rambuffer {
	REF struct video_codec_handle    *ssb_codec_handle;  /* [1..1][const] Custom codec keep-alive handle */
	fd_t                              ssb_vdlck;         /* [const] Video lock file */
	void                             *ssb_libphys;       /* [1..1][const] Handle for libphys */
	PMMAPPHYS                         ssb_libphys_map;   /* [1..1][const] Helper to map physical memory */
	PMUNMAPPHYS                       ssb_libphys_unmap; /* [1..1][const] Helper to unmap physical memory */
	void                             *ssb_libsvgadrv;    /* [1..1][const] Handle for libsvgadrv */
	struct svga_chipset_driver const *ssb_drv;           /* [1..1][const] SVGA driver */
	struct svga_chipset               ssb_cs;            /* [1..1][const] SVGA chipset */
};

PRIVATE struct video_buffer_ops svga_screen_ops = {};

PRIVATE NONNULL((1)) void CC
svga_screen_destroy(struct video_buffer *__restrict self) {
	struct svga_screen_buffer *me = (struct svga_screen_buffer *)self;
	assert(me->vb_ops == &svga_screen_ops);
	/* Finalize */
	(*me->ssb_cs.sc_ops.sco_fini)(&me->ssb_cs);
	(*me->ssb_libphys_unmap)(me->vb_data, me->vb_total);
	(void)dlclose(me->ssb_libsvgadrv);
	(void)dlclose(me->ssb_libphys);
	(void)close(me->ssb_vdlck);
	if (me->vb_format.vf_pal)
		video_palette_decref(me->vb_format.vf_pal);
	video_codec_handle_decref(me->ssb_codec_handle);
	(void)free(me);
}

PRIVATE ATTR_RETNONNULL WUNUSED
struct video_buffer_ops *CC get_svga_screen_ops(void) {
	if (!svga_screen_ops.vi_destroy) {
		/* TODO: Need custom lock function here that prevents use of HW-accelerated
		 *       render functions, as well as calls "sco_hw_async_waitfor" on lock. */
		svga_screen_ops.vi_lock    = &rambuffer_lock;
		svga_screen_ops.vi_unlock  = &rambuffer_unlock;
		svga_screen_ops.vi_getgfx  = &rambuffer_getgfx;
		svga_screen_ops.vi_clipgfx = &rambuffer_clipgfx;
		COMPILER_WRITE_BARRIER();
		svga_screen_ops.vi_destroy = &svga_screen_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &svga_screen_ops;
}


#define LOGERR(format, ...) \
	syslog(LOG_ERR, "[libvideo][screen:%d] " format, __LINE__, ##__VA_ARGS__)

PRIVATE WUNUSED NONNULL((2)) int CC
svga_find_first_gfx_mode(fd_t fd, struct svga_modeinfo *__restrict mode) {
	/* TODO */
	LOGERR("Not implemented: svga_find_first_gfx_mode()\n");
	(void)fd;
	(void)mode;
	return -1;
}

PRIVATE NONNULL((1)) void
NOTHROW(LIBVIDEO_CODEC_CC svga_palette_destroy)(struct video_palette *__restrict self) {
	free(self->vp_cache);
	free(self);
}

PRIVATE WUNUSED REF struct video_palette *CC
svga_palette_new(fd_t vdlck, shift_t colorbits) {
	size_t i, palsize;
	struct video_palette *result;
	struct svga_palette_color *colors;
	struct svga_palette buf;
	palsize = (size_t)1 << colorbits;
	colors  = (struct svga_palette_color *)malloca(palsize, sizeof(struct svga_palette_color));
	if unlikely(!colors) {
		LOGERR("Failed to allocate palette color buffer: %m\n");
		goto err;
	}
	buf.svp_base = 0;
	buf.svp_size = palsize;
	buf.svp_pal  = colors;
	if (ioctl(vdlck, SVGA_IOC_GETPAL_RGBX, &buf) < 0) {
		LOGERR("Failed to query palette: %m\n");
		freea(colors);
		goto err;
	}

	result = (REF struct video_palette *)malloc(offsetof(struct video_palette, vp_pal) +
	                                            (buf.svp_size * sizeof(video_color_t)));
	if unlikely(!result) {
		LOGERR("Failed to allocate palette controller: %m\n");
		freea(colors);
		goto err;
	}
	result->vp_destroy = &svga_palette_destroy;
	result->vp_refcnt  = 1;
	result->vp_cache   = NULL;
	result->vp_cnt     = buf.svp_size;
	for (i = 0; i < result->vp_cnt; ++i) {
		struct svga_palette_color color = colors[i];
		video_color_t vcolor = VIDEO_COLOR_RGB(color.spc_r, color.spc_g, color.spc_b);
		result->vp_pal[i] = vcolor;
	}
	for (; i < palsize; ++i)
		result->vp_pal[i] = 0; /* Unused colors? */
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
		result->vcs_cbits = self->smi_colorbits;
		result->vcs_rmask = ((uint32_t)1 << result->vcs_cbits) - 1;
		result->vcs_gmask = result->vcs_rmask;
		result->vcs_bmask = result->vcs_rmask;
	} else {
		result->vcs_rmask = (((uint32_t)1 << self->smi_rbits) - 1) << self->smi_rshift;
		result->vcs_gmask = (((uint32_t)1 << self->smi_gbits) - 1) << self->smi_gshift;
		result->vcs_bmask = (((uint32_t)1 << self->smi_bbits) - 1) << self->smi_bshift;
	}
	result->vcs_amask = 0;
}

PRIVATE WUNUSED REF struct svga_screen_buffer *CC
svga_newscreen(void) {
	fd_t svga;
	void *libsvgadrv;
	PSVGA_CHIPSET_GETDRIVERS svga_chipset_getdrivers;
	struct openfd vdlck;
	struct svga_modeinfo mode;
	struct video_format format;
	REF struct video_codec_handle *codec_handle;
	struct video_codec_specs codec_specs;
	REF struct svga_screen_buffer *result;
	struct svga_chipset_driver const *driver;
	char csname[SVGA_CSNAMELEN];
	svga = open("/dev/svga", O_RDWR | O_CLOEXEC);
	if unlikely(svga < 0) {
		LOGERR("Failed to open svga driver: %m\n");
		goto err;
	}

	/* Acquire a video lock */
	bzero(&vdlck, sizeof(vdlck));
	vdlck.of_flags = IO_CLOEXEC;
	if (ioctl(svga, SVGA_IOC_MAKELCK, &vdlck) < 0) {
		LOGERR("SVGA_IOC_MAKELCK failed: %m\n");
		goto err_svga;
	}

	/* Lookup current video mode. */
	if (ioctl(vdlck.of_hint, SVGA_IOC_GETMODE, &mode) < 0) {
		LOGERR("SVGA_IOC_GETMODE failed: %m\n");
		goto err_svga_vdlck;
	}

	/* If we're in text-mode, switch to graphics mode. */
	if (mode.smi_flags & SVGA_MODEINFO_F_TXT) {
		if (svga_find_first_gfx_mode(vdlck.of_hint, &mode) != 0) {
			LOGERR("Failed to find any viable GFX mode\n");
			errno = ENODEV; /* Chipset doesn't support any kind of GFX */
			goto err_svga_vdlck;
		}
		if (ioctl(vdlck.of_hint, SVGA_IOC_SETMODE, &mode) < 0) {
			LOGERR("SVGA_IOC_SETMODE failed: %m\n");
			goto err_svga_vdlck;
		}
	}

	/* Load codec to-be used for video mode. */
	svga_modeinfo_to_codec_specs(&mode, &codec_specs);
	format.vf_codec = video_codec_fromspecs(&codec_specs, &codec_handle);
	if (!format.vf_codec) {
		LOGERR("No codec for SVGA video mode\n");
		errno = ENODEV;
		goto err_svga_vdlck;
	}
	format.vf_pal = NULL;
	if (format.vf_codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_PAL) {
		format.vf_pal = svga_palette_new(vdlck.of_hint, format.vf_codec->vc_specs.vcs_cbits);
		if unlikely(!format.vf_pal) {
			LOGERR("Failed to allocate palette controller: %m\n");
			goto err_svga_vdlck_codec;
		}
	}

	/* Figure out which chipset we're using. */
	if (ioctl(vdlck.of_hint, SVGA_IOC_GETCSNAME, csname) < 0) {
		LOGERR("SVGA_IOC_GETCSNAME failed: %m\n");
		goto err_svga_vdlck_codec_format;
	}

	/* Make sure we ring#3 have I/O permissions */
	if (iopl(3)) {
		LOGERR("iopl failed: %m\n");
		goto err_svga_vdlck_codec_format;
	}

	/* Load "libsvgadrv" */
	libsvgadrv = dlopen(LIBSVGADRV_LIBRARY_NAME, RTLD_LOCAL);
	if unlikely(!libsvgadrv) {
		LOGERR("dlerror: %s\n", dlerror());
		goto err_svga_vdlck_codec_format;
	}
	*(void **)&svga_chipset_getdrivers = dlsym(libsvgadrv, "svga_chipset_getdrivers");
	if unlikely(!svga_chipset_getdrivers) {
		LOGERR("dlerror: %s\n", dlerror());
		goto err_svga_vdlck_codec_format_libsvgadrv;
	}

	/* Find the relevant chipset driver. */
	driver = (*svga_chipset_getdrivers)();
	if unlikely(!driver) {
		syslog(LOG_ERR, "[libvideo] No drivers available\n");
		goto err_svga_vdlck_codec_format_libsvgadrv;
	}
	while (strcmp(driver->scd_name, csname) != 0) {
		if unlikely(!driver->scd_probe) {
			syslog(LOG_ERR, "[libvideo] No driver to active chipset %q\n", csname);
			errno = ENODEV; /*  */
			goto err_svga_vdlck_codec_format_libsvgadrv;
		}
		++driver;
	}

	/* Allocate the screen control structure */
	{
		size_t bufsz = offsetof(struct svga_screen_buffer, ssb_cs) +
		               driver->scd_cssize;
		result = (REF struct svga_screen_buffer *)malloc(bufsz);
		if unlikely(!result)
			goto err_svga_vdlck_codec_format_libsvgadrv;
	}

	/* Initialize the chipset for user-space. */
	/* TODO: Add a second  function "driver->scd_open"  that's allowed to  assume that  the
	 *       chipset is correct, meaning it won't have to probe for the driver's existance. */
	if (!(*driver->scd_probe)(&result->ssb_cs)) {
		syslog(LOG_ERR, "[libvideo] Failed to init chipset %q\n", csname);
		goto err_svga_vdlck_codec_format_libsvgadrv_r;
	}

	/* Load phyiscal memory mapping functions. */
	result->ssb_libphys = dlopen(LIBPHYS_LIBRARY_NAME, RTLD_LOCAL);
	if unlikely(!result->ssb_libphys) {
		LOGERR("dlerror: %s\n", dlerror());
		goto err_svga_vdlck_codec_format_libsvgadrv_r_cs;
	}
	*(void **)&result->ssb_libphys_map = dlsym(result->ssb_libphys, "mmapphys");
	if unlikely(!result->ssb_libphys_map) {
		LOGERR("dlerror: %s\n", dlerror());
		goto err_svga_vdlck_codec_format_libsvgadrv_r_cs_libphys;
	}
	*(void **)&result->ssb_libphys_unmap = dlsym(result->ssb_libphys, "munmapphys");
	if unlikely(!result->ssb_libphys_unmap) {
		LOGERR("dlerror: %s\n", dlerror());
		goto err_svga_vdlck_codec_format_libsvgadrv_r_cs_libphys;
	}

	/* Map screen memory into a physical buffer. */
	result->vb_stride = mode.smi_scanline;
	result->vb_total  = mode.smi_scanline * mode.smi_resy;
	result->vb_data   = (byte_t *)(*result->ssb_libphys_map)(mode.smi_lfb, result->vb_total);
	if unlikely((void *)result->vb_data == MAP_FAILED) {
		LOGERR("Failed to map LFB: %m\n");
		goto err_svga_vdlck_codec_format_libsvgadrv_r_cs_libphys;
	}

	/* Fill in remaining fields of "result" */
	result->vb_refcnt          = 1;
	result->vb_ops             = get_svga_screen_ops();
	result->vb_format.vf_codec = format.vf_codec;
	result->vb_format.vf_pal   = format.vf_pal;
	result->vb_size_x          = mode.smi_resx;
	result->vb_size_y          = mode.smi_resy;
	result->ssb_codec_handle   = codec_handle;
	result->ssb_vdlck          = vdlck.of_hint;
	result->ssb_libsvgadrv     = libsvgadrv;
	result->ssb_drv            = driver;

	/* Close our handle to the SVGA base driver */
	(void)close(svga);

	/* And we're done! */
	return result;
/*err_svga_vdlck_codec_format_libsvgadrv_r_cs_libphys_data:
	(*result->ssb_libphys_unmap)(result->vb_data, result->vb_total);*/
err_svga_vdlck_codec_format_libsvgadrv_r_cs_libphys:
	(void)dlclose(result->ssb_libphys);
err_svga_vdlck_codec_format_libsvgadrv_r_cs:
	(*result->ssb_cs.sc_ops.sco_fini)(&result->ssb_cs);
err_svga_vdlck_codec_format_libsvgadrv_r:
	free(result);
err_svga_vdlck_codec_format_libsvgadrv:
	(void)dlclose(libsvgadrv);
err_svga_vdlck_codec_format:
	if (format.vf_pal)
		video_palette_decref(format.vf_pal);
err_svga_vdlck_codec:
	video_codec_handle_decref(codec_handle);
err_svga_vdlck:
	(void)close(vdlck.of_hint);
err_svga:
	(void)close(svga);
err:
	return NULL;
}


/* Creates+returns a video buffer for the entire screen (or return NULL and set
 * errno  on error). Note that screen buffer access is only granted to ROOT and
 * the window server */
DEFINE_PUBLIC_ALIAS(video_buffer_screen, libvideo_buffer_screen);
INTERN WUNUSED REF struct video_buffer *CC
libvideo_buffer_screen(void) {
	/* XXX: Support for other video drivers would go here... */
	return svga_newscreen();
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_SCREEN_C */
