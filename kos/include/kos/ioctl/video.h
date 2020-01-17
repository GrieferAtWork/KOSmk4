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
#ifndef _KOS_IOCTL_VIDEO_H
#define _KOS_IOCTL_VIDEO_H 1

/* KOS-specific video-device system interface. */

#include <__stdinc.h>
#include <asm/ioctl.h>
#include <bits/types.h>

__DECL_BEGIN

#define VD_FORMAT_FLAG_NORMAL 0x0000 /* Normal flags */

#define VIDEOIO_LISTFORMAT _IOR_KOS('V', 0x00, struct vd_lsfmt_struct) /* Enumerate available video formats. */
#define VIDEOIO_GETFORMAT  _IOR_KOS('V', 0x01, struct vd_format) /* Get the current video format. */
#define VIDEOIO_SETFORMAT  _IOW_KOS('V', 0x01, struct vd_format) /* Set the current video format. */
#define VIDEOIO_GETPAL     _IOR_KOS('V', 0x02, struct vd_pal_struct) /* Get the current color palette. */
#define VIDEOIO_SETPAL     _IOW_KOS('V', 0x02, struct vd_pal_struct) /* Set the current color palette. */


#ifdef __CC__
typedef __uint32_t vd_color_t; /* General-purpose color (RGBA in big-endian) */
typedef __uint32_t vd_pixel_t; /* Codec-specific pixel value. */
typedef __uint16_t vd_codec_t; /* Video codec ID (one of `VIDEO_CODEC_*' from `<libvideo/codec/codecs.h>'). */

struct vd_palette {
	vd_color_t vdp_pal[256]; /* [VIDEO_CODEC_PALSIZ(*)] Palette colors. */
};

struct vd_format {
	vd_codec_t vdf_codec;  /* Video display codec (One of `VIDEO_CODEC_*'). (When `VIDEO_CODEC_NONE', this is a TTY format) */
	__uint16_t vdf_flags;  /* Video format flags (Set of `VD_FORMAT_FLAG_*') */
	__uint32_t vdf_resx;   /* Screen resolution in X (or TTY cell count in X) */
	__uint32_t vdf_resy;   /* Screen resolution in Y (or TTY cell count in Y) */
	__uint32_t vdf_scan;   /* Scanline size (in bytes) */
	__uint32_t vdf_dpix;   /* Dots (pixels) per inch in X (or 0 if unknown) (or TTY cell pixel-size in X) */
	__uint32_t vdf_dpiy;   /* Dots (pixels) per inch in Y (or 0 if unknown) (or TTY cell pixel-size in Y) */
};

struct vd_lsfmt_struct {
	__uint32_t        lsf_offset; /* [IN]  Number of leading formats to skip */
	__uint32_t        lsf_limit;  /* [IN]  Max number of formats to return.
	                               * [OUT] Actual number of formats returned (if == IN(lsf_limit), then there may be more) */
	struct vd_format *lsf_buf;    /* [1..lsf_limit] User-supplied buffer for video formats. */
};

struct vd_pal_struct {
	vd_codec_t         vp_codec;  /* The current codec */
	__uint16_t       __vp_pad[3]; /* ... */
	struct vd_palette *vp_pal;    /* [0..1] User-buffer for the palette to apply/fill
	                               * NOTE: When `NULL' during set, reset to use the default palette. */
};

#endif /* __CC__ */

__DECL_END

#endif /* !_KOS_IOCTL_VIDEO_H */
