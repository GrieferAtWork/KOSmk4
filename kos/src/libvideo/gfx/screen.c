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
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

#include <libphys/phys.h>
#include <libsvgadrv/chipset.h>
#include <libvideo/codec/codecs.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>

#include "ram-buffer.h"

DECL_BEGIN

struct svga_screen_buffer: video_rambuffer {
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

PRIVATE WUNUSED NONNULL((1, 2)) bool CC
svga_get_format(struct svga_modeinfo const *__restrict mode,
                struct video_format *__restrict result) {
	video_codec_t codec;
	syslog(LOG_DEBUG,
	       "Video mode:\n"
	       "mode->smi_flags          = %#x\n"
	       "mode->smi_bits_per_pixel = %u\n"
	       "mode->smi_colorbits      = %u\n"
	       "mode->smi_rshift         = %u\n"
	       "mode->smi_rbits          = %u\n"
	       "mode->smi_gshift         = %u\n"
	       "mode->smi_gbits          = %u\n"
	       "mode->smi_bshift         = %u\n"
	       "mode->smi_bbits          = %u\n"
	       "",
	       (unsigned int)mode->smi_flags,
	       (unsigned int)mode->smi_bits_per_pixel,
	       (unsigned int)mode->smi_colorbits,
	       (unsigned int)mode->smi_rshift,
	       (unsigned int)mode->smi_rbits,
	       (unsigned int)mode->smi_gshift,
	       (unsigned int)mode->smi_gbits,
	       (unsigned int)mode->smi_bshift,
	       (unsigned int)mode->smi_bbits);
	if (mode->smi_flags & SVGA_MODEINFO_F_PLANAR)
		goto nope; /* TODO: Linear frame buffer emulation */
	if (!(mode->smi_flags & SVGA_MODEINFO_F_LFB))
		goto nope;
	if (mode->smi_flags & SVGA_MODEINFO_F_PAL)
		goto nope; /* TODO: palette support */
	result->vf_pal = NULL;

	codec = VIDEO_CODEC_NONE;
	if (mode->smi_flags & SVGA_MODEINFO_F_BW) {
		switch (mode->smi_colorbits) {
		case 1: codec = VIDEO_CODEC_GRAY2_LSB; break;
		case 2: codec = VIDEO_CODEC_GRAY4_LSB; break;
		case 4: codec = VIDEO_CODEC_GRAY16_LSB; break;
		case 8: codec = VIDEO_CODEC_GRAY256; break;
		default: goto nope;
		}
	} else {
		switch (mode->smi_bits_per_pixel) {

		case 32:
			if (mode->smi_rbits == 8 && mode->smi_gbits == 8 && mode->smi_bbits == 8) {
				if (mode->smi_rshift == 24 && mode->smi_gshift == 16 && mode->smi_bshift == 8) {
					codec = VIDEO_CODEC_RGBX8888;
				} else if (mode->smi_rshift == 16 && mode->smi_gshift == 8 && mode->smi_bshift == 0) {
					codec = VIDEO_CODEC_XRGB8888;
				} else if (mode->smi_bshift == 16 && mode->smi_gshift == 8 && mode->smi_rshift == 0) {
					codec = VIDEO_CODEC_XBGR8888;
				} else if (mode->smi_bshift == 24 && mode->smi_gshift == 16 && mode->smi_rshift == 8) {
					codec = VIDEO_CODEC_BGRX8888;
				}
			}
			break;

		case 24:
			if (mode->smi_rbits == 8 && mode->smi_gbits == 8 && mode->smi_bbits == 8) {
				if (mode->smi_rshift == 16 && mode->smi_gshift == 8 && mode->smi_bshift == 0) {
					codec = VIDEO_CODEC_RGB888;
				} else if (mode->smi_bshift == 16 && mode->smi_gshift == 8 && mode->smi_rshift == 0) {
					codec = VIDEO_CODEC_BGR888;
				}
			}
			break;

		case 16:
			if (mode->smi_rbits == 4 && mode->smi_gbits == 4 && mode->smi_bbits == 4) {
				if (mode->smi_rshift == 12 && mode->smi_gshift == 8 && mode->smi_bshift == 4) {
					codec = VIDEO_CODEC_RGBX4444;
				} else if (mode->smi_rshift == 8 && mode->smi_gshift == 4 && mode->smi_bshift == 0) {
					codec = VIDEO_CODEC_XRGB4444;
				} else if (mode->smi_bshift == 8 && mode->smi_gshift == 4 && mode->smi_rshift == 0) {
					codec = VIDEO_CODEC_XBGR4444;
				} else if (mode->smi_bshift == 12 && mode->smi_gshift == 8 && mode->smi_rshift == 4) {
					codec = VIDEO_CODEC_BGRX4444;
				}
			} else if (mode->smi_rbits == 5 && mode->smi_gbits == 6 && mode->smi_bbits == 5) {
				if (mode->smi_rshift == 11 && mode->smi_gshift == 5 && mode->smi_bshift == 0) {
					codec = VIDEO_CODEC_RGB565;
				} else if (mode->smi_bshift == 11 && mode->smi_gshift == 5 && mode->smi_rshift == 0) {
					codec = VIDEO_CODEC_BGR565;
				}
			} else if (mode->smi_rbits == 5 && mode->smi_gbits == 5 && mode->smi_bbits == 5) {
				if (mode->smi_rshift == 11 && mode->smi_gshift == 6 && mode->smi_bshift == 1) {
					codec = VIDEO_CODEC_RGBX5551;
				} else if (mode->smi_rshift == 10 && mode->smi_gshift == 5 && mode->smi_bshift == 0) {
					codec = VIDEO_CODEC_XRGB1555;
				} else if (mode->smi_bshift == 10 && mode->smi_gshift == 5 && mode->smi_rshift == 0) {
					codec = VIDEO_CODEC_XBGR1555;
				} else if (mode->smi_bshift == 11 && mode->smi_gshift == 6 && mode->smi_rshift == 1) {
					codec = VIDEO_CODEC_BGRX5551;
				}
			}
			break;

		default: break;
		}
	}

	/* TODO: Support for custom codecs (that are then able to work with any arbitrary pixel format) */
	result->vf_codec = video_codec_lookup(codec);
	if unlikely(!result->vf_codec)
		goto nope;
	return true;
nope:
	return false;
}

PRIVATE WUNUSED REF struct svga_screen_buffer *CC
svga_newscreen(void) {
	fd_t svga;
	void *libsvgadrv;
	PSVGA_CHIPSET_GETDRIVERS svga_chipset_getdrivers;
	struct openfd vdlck;
	struct svga_modeinfo mode;
	struct video_format format;
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
	if (!svga_get_format(&mode, &format)) {
		LOGERR("No codec for SVGA video mode\n");
		errno = ENODEV;
		goto err_svga_vdlck;
	}

	/* Figure out which chipset we're using. */
	if (ioctl(vdlck.of_hint, SVGA_IOC_GETCSNAME, csname) < 0) {
		LOGERR("SVGA_IOC_GETCSNAME failed: %m\n");
		goto err_svga_vdlck_format;
	}

	/* Make sure we ring#3 have I/O permissions */
	if (iopl(3)) {
		LOGERR("iopl failed: %m\n");
		goto err_svga_vdlck_format;
	}

	/* Load "libsvgadrv" */
	libsvgadrv = dlopen(LIBSVGADRV_LIBRARY_NAME, RTLD_LOCAL);
	if unlikely(!libsvgadrv) {
		LOGERR("dlerror: %s\n", dlerror());
		goto err_svga_vdlck_format;
	}
	*(void **)&svga_chipset_getdrivers = dlsym(libsvgadrv, "svga_chipset_getdrivers");
	if unlikely(!svga_chipset_getdrivers) {
		LOGERR("dlerror: %s\n", dlerror());
		goto err_svga_vdlck_format_libsvgadrv;
	}

	/* Find the relevant chipset driver. */
	driver = (*svga_chipset_getdrivers)();
	if unlikely(!driver) {
		syslog(LOG_ERR, "[libvideo] No drivers available\n");
		goto err_svga_vdlck_format_libsvgadrv;
	}
	while (strcmp(driver->scd_name, csname) != 0) {
		if unlikely(!driver->scd_probe) {
			syslog(LOG_ERR, "[libvideo] No driver to active chipset %q\n", csname);
			errno = ENODEV; /*  */
			goto err_svga_vdlck_format_libsvgadrv;
		}
		++driver;
	}

	/* Allocate the screen control structure */
	{
		size_t bufsz = offsetof(struct svga_screen_buffer, ssb_cs) +
		               driver->scd_cssize;
		result = (REF struct svga_screen_buffer *)malloc(bufsz);
		if unlikely(!result)
			goto err_svga_vdlck_format_libsvgadrv;
	}

	/* Initialize the chipset for user-space. */
	/* TODO: Add a second  function "driver->scd_open"  that's allowed to  assume that  the
	 *       chipset is correct, meaning it won't have to probe for the driver's existance. */
	if (!(*driver->scd_probe)(&result->ssb_cs)) {
		syslog(LOG_ERR, "[libvideo] Failed to init chipset %q\n", csname);
		goto err_svga_vdlck_format_libsvgadrv_r;
	}

	/* Load phyiscal memory mapping functions. */
	result->ssb_libphys = dlopen(LIBPHYS_LIBRARY_NAME, RTLD_LOCAL);
	if unlikely(!result->ssb_libphys) {
		LOGERR("dlerror: %s\n", dlerror());
		goto err_svga_vdlck_format_libsvgadrv_r_cs;
	}
	*(void **)&result->ssb_libphys_map = dlsym(result->ssb_libphys, "mmapphys");
	if unlikely(!result->ssb_libphys_map) {
		LOGERR("dlerror: %s\n", dlerror());
		goto err_svga_vdlck_format_libsvgadrv_r_cs_libphys;
	}
	*(void **)&result->ssb_libphys_unmap = dlsym(result->ssb_libphys, "munmapphys");
	if unlikely(!result->ssb_libphys_unmap) {
		LOGERR("dlerror: %s\n", dlerror());
		goto err_svga_vdlck_format_libsvgadrv_r_cs_libphys;
	}

	/* Map screen memory into a physical buffer. */
	result->vb_stride = mode.smi_scanline;
	result->vb_total  = mode.smi_scanline * mode.smi_resy;
	result->vb_data   = (byte_t *)(*result->ssb_libphys_map)(mode.smi_lfb, result->vb_total);
	if unlikely((void *)result->vb_data == MAP_FAILED) {
		LOGERR("Failed to map LFB: %m\n");
		goto err_svga_vdlck_format_libsvgadrv_r_cs_libphys;
	}

	/* Fill in remaining fields of "result" */
	result->vb_refcnt          = 1;
	result->vb_ops             = get_svga_screen_ops();
	result->vb_format.vf_codec = format.vf_codec;
	result->vb_format.vf_pal   = format.vf_pal;
	result->vb_size_x          = mode.smi_resx;
	result->vb_size_y          = mode.smi_resy;
	result->ssb_vdlck          = vdlck.of_hint;
	result->ssb_libsvgadrv     = libsvgadrv;
	result->ssb_drv            = driver;

	/* Close our handle to the SVGA base driver */
	(void)close(svga);

	/* And we're done! */
	return result;
/*err_svga_vdlck_format_libsvgadrv_r_cs_libphys_data:
	(*result->ssb_libphys_unmap)(result->vb_data, result->vb_total);*/
err_svga_vdlck_format_libsvgadrv_r_cs_libphys:
	(void)dlclose(result->ssb_libphys);
err_svga_vdlck_format_libsvgadrv_r_cs:
	(*result->ssb_cs.sc_ops.sco_fini)(&result->ssb_cs);
err_svga_vdlck_format_libsvgadrv_r:
	free(result);
err_svga_vdlck_format_libsvgadrv:
	(void)dlclose(libsvgadrv);
err_svga_vdlck_format:
	if (format.vf_pal)
		video_palette_decref(format.vf_pal);
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
#if 1
	return svga_newscreen();
#else
	fd_t driver;
	struct video_rambuffer *result;
	struct vd_format format;
	result = screen_buffer; /* TODO: This needs a lock! */
	if likely(result) {
		incref(result);
		return result;
	}
	driver = libvideo_driver();
	if unlikely(driver < 0)
		goto err;
	if (ioctl(driver, VIDEOIO_GETFORMAT, &format) < 0)
		goto err;

	/* Allocate the video buffer. */
	result = (struct video_rambuffer *)malloc(sizeof(struct video_rambuffer));
	if unlikely(!result)
		goto err;
	result->vb_format.vf_pal = NULL;

	/* Lookup the video format described by the codec. */
	result->vb_format.vf_codec = video_codec_lookup(format.vdf_codec);
	if unlikely(!result->vb_format.vf_codec) {
		errno = ENOTSUP;
		goto err_r;
	}

	/* Construct a palette (if necessary) */
	if (VIDEO_CODEC_HASPAL(format.vdf_codec)) {
		struct video_palette *pal;
		struct vd_pal_struct getpal;
		size_t count = VIDEO_CODEC_PALSIZ(format.vdf_codec);
		pal = (struct video_palette *)malloc(offsetof(struct video_palette, vp_pal.vdp_pal) +
		                                     (count * sizeof(vd_color_t)));
		if unlikely(!pal)
			goto err_r;
		result->vb_format.vf_pal = pal;
		pal->vp_destroy = &screen_pal_destroy;
		pal->vp_refcnt  = 1;
		pal->vp_cache   = NULL;
		pal->vp_cnt = count;
		/* Load the current palette. */
		getpal.vp_codec = format.vdf_codec;
		getpal.vp_pal   = &pal->vp_pal;
		if (ioctl(driver, VIDEOIO_GETPAL, &getpal) < 0)
			goto err;
	}
	result->vb_stride = format.vdf_scan;
	result->vb_refcnt = 1;
	result->vb_ops    = rambuffer_getops_munmap();
	result->vb_size_x = format.vdf_resx;
	result->vb_size_y = format.vdf_resy;
	result->vb_total  = format.vdf_scan * format.vdf_resy;
	result->vb_data = (byte_t *)mmap(NULL, result->vb_total,
	                                 PROT_READ | PROT_WRITE,
	                                 MAP_PRIVATE | MAP_FILE,
	                                 driver, 0);
	if (result->vb_data == (byte_t *)MAP_FAILED)
		goto err_r;
	if (!atomic_cmpxch(&screen_buffer, NULL, result)) { /* TODO: This needs a lock! */
		(*result->vb_ops->vi_destroy)(result);
		result = screen_buffer;
	}
	incref(result);
	return result;
err_r:
	free(result->vb_format.vf_pal);
	free(result);
err:
	return NULL;
#endif
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_SCREEN_C */
