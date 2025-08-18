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
#ifndef GUARD_LIBVIDEO_GFX_SERIAL_C
#define GUARD_LIBVIDEO_GFX_SERIAL_C 1
#define _KOS_SOURCE 1
#define __VIDEO_BUFFER_const
#define __VIDEO_CODEC_const

#include "api.h"
/**/

#include <libvideo/gfx/api.h>

#ifdef CONFIG_LIBVIDEO_HAVE_SERIALIZATION
#include <hybrid/compiler.h>

#include <hybrid/byteswap.h>
#include <hybrid/unaligned.h>

#include <kos/anno.h>
#include <kos/types.h>
#include <sys/mman.h>
#include <sys/types.h>

#include <atomic.h>
#include <errno.h>
#include <malloc.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <libvideo/color.h>
#include <libvideo/crect.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/buffer/ramfdbuffer.h>
#include <libvideo/gfx/codec/codec.h>
#include <libvideo/gfx/codec/palette.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/gfx/serial.h>
#include <libvideo/gfx/serial/packet.h>
#include <libvideo/rect.h>
#include <libvideo/types.h>

#include "buffer.h"
#include "buffer/empty.h"
#include "buffer/region.h"
#include "codec/codec-specs.h"
#include "codec/codec.h"
#include "codec/converter.h"
#include "ramfddomain.h"
#include "serial.h"

DECL_BEGIN

#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
#define lpixel_t video_pixel64_t
#else /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */
#define lpixel_t video_pixel_t
#endif /* !CONFIG_LIBVIDEO_HAVE_PIXEL64 */

#ifndef VIDEO_CODEC_SETPIXEL3_CC
#define VIDEO_CODEC_SETPIXEL3_CC /* nothing */
#endif /* !VIDEO_CODEC_SETPIXEL3_CC */



/************************************************************************/
/* NET BUFFER                                                           */
/************************************************************************/
struct net_buffer: video_buffer {
	struct video_deserializer_io *nb_io;        /* [1..1][const][owned] I/O controller. */
	video_serial_token_t          nb_nexttoken; /* [lock(ATOMIC)] Next I/O token (never "VIDEO_SERIAL_TOKEN_OOB") */
};

#define video_buffer_asnet(self) ((struct net_buffer *)(self))

PRIVATE NONNULL((1)) void FCC
net_buffer_destroy(struct video_buffer *__restrict self) {
	struct net_buffer *me = video_buffer_asnet(self);
	video_deserializer_io_destroy(me->nb_io);
	__video_buffer_fini_common(me);
	free(me);
}


PRIVATE WUNUSED NONNULL((1)) video_serial_token_t FCC
net_buffer_alloctoken(struct net_buffer *__restrict self) {
	video_serial_token_t result;
	do {
		result = atomic_fetchinc(&self->nb_nexttoken);
	} while unlikely(result < VIDEO_SERIAL_TOKEN_MIN ||
	                 result > VIDEO_SERIAL_TOKEN_MAX);
	return result;
}

PRIVATE WUNUSED NONNULL((1)) video_pixel_t FCC
net_buffer_remote_color2pixel(struct net_buffer *__restrict self, video_color_t color) {
	struct netbuf_cmd_color2pixel cmd;
	struct netbuf_resp_color2pixel resp;
	video_serial_token_t token = net_buffer_alloctoken(self);
	ssize_t resp_size;
	cmd.nbp_cmd = NETBUF_CMD_COLOR2PIXEL;
	UNALIGNED_SET32(&cmd.nbc2p_color.nbc_color, color);
	if unlikely(video_deserializer_io_writepacket(self->nb_io, &cmd, sizeof(cmd), token))
		goto err;
	resp_size = video_deserializer_io_readpacket(self->nb_io, &resp, sizeof(resp), NULL, token);
	if unlikely(resp_size < (ssize_t)sizeof(resp))
		goto err;
	return UNALIGNED_GETLE32(&resp.nbrc2p_pixel);
err:
	return 0;
}

PRIVATE WUNUSED NONNULL((1)) video_color_t FCC
net_buffer_remote_pixel2color(struct net_buffer *__restrict self, video_pixel_t pixel) {
	struct netbuf_cmd_pixel2color cmd;
	struct netbuf_resp_pixel2color resp;
	video_serial_token_t token = net_buffer_alloctoken(self);
	ssize_t resp_size;
	cmd.nbp_cmd = NETBUF_CMD_PIXEL2COLOR;
	UNALIGNED_SETLE32(&cmd.nbp2c_pixel, pixel);
	if unlikely(video_deserializer_io_writepacket(self->nb_io, &cmd, sizeof(cmd), token))
		goto err;
	resp_size = video_deserializer_io_readpacket(self->nb_io, &resp, sizeof(resp), NULL, token);
	if unlikely(resp_size < (ssize_t)sizeof(resp))
		goto err;
	return UNALIGNED_GET32(&resp.nbrp2c_color.nbc_color);
err:
	return 0;
}

#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
PRIVATE WUNUSED NONNULL((1)) video_pixel64_t FCC
net_buffer_remote_color2pixel64(struct net_buffer *__restrict self, video_color64_t color) {
	struct netbuf_cmd_color2pixel64 cmd;
	struct netbuf_resp_color2pixel64 resp;
	video_serial_token_t token = net_buffer_alloctoken(self);
	ssize_t resp_size;
	cmd.nbp_cmd = NETBUF_CMD_COLOR2PIXEL64;
	UNALIGNED_SETLE16(&cmd.nbc2p_color.nbc_channels.nbc_r, VIDEO_COLOR64_GET_RED(color));
	UNALIGNED_SETLE16(&cmd.nbc2p_color.nbc_channels.nbc_g, VIDEO_COLOR64_GET_GREEN(color));
	UNALIGNED_SETLE16(&cmd.nbc2p_color.nbc_channels.nbc_b, VIDEO_COLOR64_GET_BLUE(color));
	UNALIGNED_SETLE16(&cmd.nbc2p_color.nbc_channels.nbc_a, VIDEO_COLOR64_GET_ALPHA(color));
	if unlikely(video_deserializer_io_writepacket(self->nb_io, &cmd, sizeof(cmd), token))
		goto err;
	resp_size = video_deserializer_io_readpacket(self->nb_io, &resp, sizeof(resp), NULL, token);
	if unlikely(resp_size < (ssize_t)sizeof(resp))
		goto err;
	return UNALIGNED_GETLE64(&resp.nbrc2p_pixel);
err:
	return 0;
}

PRIVATE WUNUSED NONNULL((1)) video_color64_t FCC
net_buffer_remote_pixel2color64(struct net_buffer *__restrict self, video_pixel64_t pixel) {
	struct netbuf_cmd_pixel2color64 cmd;
	struct netbuf_resp_pixel2color64 resp;
	video_serial_token_t token = net_buffer_alloctoken(self);
	ssize_t resp_size;
	cmd.nbp_cmd = NETBUF_CMD_PIXEL2COLOR64;
	UNALIGNED_SETLE64(&cmd.nbp2c_pixel, pixel);
	if unlikely(video_deserializer_io_writepacket(self->nb_io, &cmd, sizeof(cmd), token))
		goto err;
	resp_size = video_deserializer_io_readpacket(self->nb_io, &resp, sizeof(resp), NULL, token);
	if unlikely(resp_size < (ssize_t)sizeof(resp))
		goto err;
	return VIDEO_COLOR64_RGBA(UNALIGNED_GETLE16(&resp.nbrp2c_color.nbc_channels.nbc_r),
	                          UNALIGNED_GETLE16(&resp.nbrp2c_color.nbc_channels.nbc_g),
	                          UNALIGNED_GETLE16(&resp.nbrp2c_color.nbc_channels.nbc_b),
	                          UNALIGNED_GETLE16(&resp.nbrp2c_color.nbc_channels.nbc_a));
err:
	return 0;
}
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */

PRIVATE ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
net_buffer_initgfx(struct video_gfx *__restrict self) {
	(void)self;
	/* TODO */
	abort();
}

PRIVATE ATTR_RETNONNULL ATTR_INOUT_T(1) struct video_gfx *FCC
net_buffer_updategfx(struct video_gfx *__restrict self, unsigned int what) {
	(void)self;
	(void)what;
	/* TODO */
	abort();
}

PRIVATE WUNUSED ATTR_IN(1) ATTR_IN(2) REF struct video_buffer *FCC
net_buffer_subregion(struct video_surface const *__restrict self,
                     struct video_crect const *__restrict phys_rect) {
	(void)self;
	(void)phys_rect;
	/* TODO */
	abort();
}


PRIVATE struct video_buffer_ops net_buffer_ops = {};
PRIVATE ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _net_buffer_ops(void) {
	if (!net_buffer_ops.vi_destroy) {
		net_buffer_ops.vi_initgfx      = &net_buffer_initgfx;
		net_buffer_ops.vi_updategfx    = &net_buffer_updategfx;
		net_buffer_ops.vi_rlock        = &libvideo_buffer_notsup__rlock;
		net_buffer_ops.vi_wlock        = &libvideo_buffer_notsup__wlock;
		net_buffer_ops.vi_unlock       = &libvideo_buffer_noop__unlock;
		net_buffer_ops.vi_rlockregion  = &libvideo_buffer_notsup__rlockregion;
		net_buffer_ops.vi_wlockregion  = &libvideo_buffer_notsup__wlockregion;
		net_buffer_ops.vi_unlockregion = &libvideo_buffer_noop__unlockregion;
		net_buffer_ops.vi_subregion    = &net_buffer_subregion;
		net_buffer_ops.vi_revoke       = &libvideo_buffer_noop__revoke;
		COMPILER_WRITE_BARRIER();
		net_buffer_ops.vi_destroy = &net_buffer_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &net_buffer_ops;
}






/************************************************************************/
/* NET CODEC                                                            */
/************************************************************************/
struct net_codec: video_codec {
	struct video_deserializer_io *nc_io;  /* [1..1][const][== nc_buf->nb_io] I/O controller. */
	struct net_buffer            *nc_buf; /* [1..1][const] Buffer that uses this codec. */
};

#define video_codec_asnet(self) ((struct net_codec *)(self))

PRIVATE NONNULL((1)) void FCC
net_codec_destroy(struct video_codec *__restrict self) {
	struct net_codec *me = (struct net_codec *)self;
	free(me);
}

PRIVATE ATTR_OUT(3) void
NOTHROW(FCC net_codec_rambuffer_requirements)(video_dim_t size_x, video_dim_t size_y,
                                              struct video_rambuffer_requirements *__restrict result) {
	(void)size_x;
	(void)size_y;
	result->vbs_stride  = 1;
	result->vbs_bufsize = 1;
}

PRIVATE WUNUSED ATTR_INOUT(1) size_t
NOTHROW(FCC net_codec_coord2bytes)(video_coord_t *__restrict p_coord) {
	(void)p_coord;
	COMPILER_IMPURE();
	return 0;
}

PRIVATE WUNUSED NONNULL((1)) video_color_t FCC
net_codec_pixel2color(struct video_surface const *__restrict self, video_pixel_t pixel) {
	struct net_buffer *me = video_buffer_asnet(video_surface_getbuffer(self));
	struct net_codec const *codec = video_codec_asnet(video_buffer_getcodec(me));
	if unlikely(codec->nc_buf != me)
		return 0;
	return net_buffer_remote_pixel2color(me, pixel);
}

PRIVATE WUNUSED NONNULL((1)) video_pixel_t FCC
net_codec_color2pixel(struct video_surface const *__restrict self, video_color_t color) {
	struct net_buffer *me = video_buffer_asnet(video_surface_getbuffer(self));
	struct net_codec const *codec = video_codec_asnet(video_buffer_getcodec(me));
	if unlikely(codec->nc_buf != me)
		return 0;
	return net_buffer_remote_color2pixel(me, color);
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC
net_codec_getpixel(byte_t const *__restrict line, video_coord_t x) {
	(void)line;
	(void)x;
	COMPILER_IMPURE();
	return 0;
}

PRIVATE NONNULL((1)) void FCC
net_codec_setpixel(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) {
	(void)line;
	(void)x;
	(void)pixel;
	COMPILER_IMPURE();
}

#ifdef CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3
PRIVATE NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC
net_codec_setpixel3(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) {
	(void)line;
	(void)x;
	(void)pixel;
	COMPILER_IMPURE();
}
#endif /* CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3 */

PRIVATE NONNULL((1)) void FCC
net_codec_linefill(byte_t *__restrict line, video_coord_t x,
                   video_pixel_t pixel, video_dim_t num_pixels) {
	(void)line;
	(void)x;
	(void)pixel;
	(void)num_pixels;
	COMPILER_IMPURE();
}

PRIVATE NONNULL((1)) void FCC
net_codec_vertfill(byte_t *__restrict line, video_coord_t x, size_t stride,
                   video_pixel_t pixel, video_dim_t num_pixels) {
	(void)line;
	(void)x;
	(void)stride;
	(void)pixel;
	(void)num_pixels;
	COMPILER_IMPURE();
}

PRIVATE NONNULL((1)) void FCC
net_codec_rectfill(byte_t *__restrict line, video_coord_t x, size_t stride,
                   video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y) {
	(void)line;
	(void)x;
	(void)stride;
	(void)pixel;
	(void)size_x;
	(void)size_y;
	COMPILER_IMPURE();
}

PRIVATE NONNULL((1, 4)) void FCC
net_codec_rectcopy(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride,
                   byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride,
                   video_dim_t size_x, video_dim_t size_y) {
	(void)dst_line;
	(void)dst_x;
	(void)dst_stride;
	(void)src_line;
	(void)src_x;
	(void)src_stride;
	(void)size_x;
	(void)size_y;
	COMPILER_IMPURE();
}

PRIVATE NONNULL((1, 3)) void FCC
net_codec_rectmove(byte_t *dst_line, video_coord_t dst_x,
                   byte_t const *src_line, video_coord_t src_x,
                   size_t stride, video_dim_t size_x, video_dim_t size_y) {
	(void)dst_line;
	(void)dst_x;
	(void)src_line;
	(void)src_x;
	(void)stride;
	(void)size_x;
	(void)size_y;
	COMPILER_IMPURE();
}

PRIVATE NONNULL((1, 3)) void FCC
net_codec_linecopy(byte_t *__restrict dst_line, video_coord_t dst_x,
                   byte_t const *__restrict src_line, video_coord_t src_x,
                   video_dim_t size_x) {
	(void)dst_line;
	(void)dst_x;
	(void)src_line;
	(void)src_x;
	(void)size_x;
	COMPILER_IMPURE();
}

#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
PRIVATE WUNUSED NONNULL((1)) video_color64_t FCC
net_codec_pixel2color64(struct video_surface const *__restrict self, video_pixel64_t pixel) {
	struct net_buffer *me = video_buffer_asnet(video_surface_getbuffer(self));
	struct net_codec const *codec = video_codec_asnet(video_buffer_getcodec(me));
	if unlikely(codec->nc_buf != me)
		return 0;
	return net_buffer_remote_pixel2color64(me, pixel);
}

PRIVATE WUNUSED NONNULL((1)) video_pixel64_t FCC
net_codec_color2pixel64(struct video_surface const *__restrict self, video_color64_t color) {
	struct net_buffer *me = video_buffer_asnet(video_surface_getbuffer(self));
	struct net_codec const *codec = video_codec_asnet(video_buffer_getcodec(me));
	if unlikely(codec->nc_buf != me)
		return 0;
	return net_buffer_remote_color2pixel64(me, color);
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel64_t FCC
net_codec_getpixel64(byte_t const *__restrict line, video_coord_t x) {
	(void)line;
	(void)x;
	COMPILER_IMPURE();
	return 0;
}

PRIVATE NONNULL((1)) void FCC
net_codec_setpixel64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel) {
	(void)line;
	(void)x;
	(void)pixel;
	COMPILER_IMPURE();
}

PRIVATE NONNULL((1)) void FCC
net_codec_linefill64(byte_t *__restrict line, video_coord_t x,
                     video_pixel64_t pixel, video_dim_t num_pixels) {
	(void)line;
	(void)x;
	(void)pixel;
	(void)num_pixels;
	COMPILER_IMPURE();
}

PRIVATE NONNULL((1)) void FCC
net_codec_vertfill64(byte_t *__restrict line, video_coord_t x, size_t stride,
                     video_pixel64_t pixel, video_dim_t num_pixels) {
	(void)line;
	(void)x;
	(void)stride;
	(void)pixel;
	(void)num_pixels;
	COMPILER_IMPURE();
}

PRIVATE NONNULL((1)) void FCC
net_codec_rectfill64(byte_t *__restrict line, video_coord_t x, size_t stride,
                     video_pixel64_t pixel, video_dim_t size_x, video_dim_t size_y) {
	(void)line;
	(void)x;
	(void)stride;
	(void)pixel;
	(void)size_x;
	(void)size_y;
	COMPILER_IMPURE();
}
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */




/* General-purpose video deserializer. */
INTERN WUNUSED NONNULL((1, 2)) REF struct video_buffer *CC
libvideo_generic_deserialize(struct video_domain const *__restrict domain,
                             /*inherit(on_success)*/ struct video_deserializer_io *__restrict io,
                             video_serial_proto_t proto) {
	struct netbuf_fdinfo fdinfo;
	REF struct video_buffer *result;
	REF struct video_codec *codec;
	REF struct video_palette *palette;
	struct netbuf_cmd cmd;
	video_codec_t codec_id;
	video_gfx_flag_t result_flags;
	ssize_t fdinfo_size;
	fd_t buffer_fd;
	video_dim_t result_xdim;
	video_dim_t result_ydim;

	/* Verify that we understand the "proto" argument. */
	if (proto != VIDEO_SERIAL_PROTO_MEMFD &&
	    proto != VIDEO_SERIAL_PROTO_PACKET) {
		errno = EPROTONOSUPPORT;
		goto err;
	}

	/* Try to query buffer info */
	cmd.nbp_cmd = NETBUF_CMD_GETINFO;
	if unlikely(video_deserializer_io_writepacket(io, &cmd, sizeof(cmd), 0))
		goto err;
	buffer_fd = -1;
	fdinfo_size = video_deserializer_io_readpacket(io, &fdinfo, sizeof(fdinfo),
	                                               (proto == VIDEO_SERIAL_PROTO_PACKET)
	                                               ? NULL
	                                               : &buffer_fd,
	                                               0);
	if unlikely(fdinfo_size < 0)
		goto err;
	if unlikely((size_t)fdinfo_size < sizeof(struct netbuf_info)) {
		errno = EPROTONOSUPPORT; /* Unsupported protocol */
		goto err_buffer_fd;
	}
	codec_id = UNALIGNED_GETLE16(&fdinfo.nbfi_info.nbi_codec);
	codec = libvideo_codec_lookup(codec_id);
	if (codec) {
		video_codec_incref(codec);
	} else {
		/* Lookup codec by specs. */
		struct netbuf_codec netspecs;
		ssize_t netspecs_size;
		cmd.nbp_cmd = NETBUF_CMD_GETCODEC;
		if unlikely(video_deserializer_io_writepacket(io, &cmd, sizeof(cmd), 1))
			goto err_buffer_fd;
		netspecs_size = video_deserializer_io_readpacket(io, &netspecs, sizeof(netspecs),
		                                                 NULL, 1);
		if unlikely(netspecs_size < 0)
			goto err_buffer_fd;
		if unlikely(netspecs_size >= (ssize_t)sizeof(netspecs)) {
			struct video_codec_specs specs;
			specs.vcs_flags = netspecs.nbc_flags;
			specs.vcs_bpp   = netspecs.nbc_bpp;
			specs.vcs_rmask = (lpixel_t)UNALIGNED_GETLE64(&netspecs.nbc_rmask);
			specs.vcs_gmask = (lpixel_t)UNALIGNED_GETLE64(&netspecs.nbc_gmask);
			specs.vcs_bmask = (lpixel_t)UNALIGNED_GETLE64(&netspecs.nbc_bmask);
			specs.vcs_amask = (lpixel_t)UNALIGNED_GETLE64(&netspecs.nbc_amask);
			codec = libvideo_codec_fromspecs(&specs);
			if unlikely(!codec && errno != EINVAL)
				goto err_buffer_fd;
		}
		if (!codec) {
			/* Create custom codec that does net I/O to convert pixel<=>color.
			 *
			 * Since we can't use a memory mapped buffer at all in  this
			 * case, close the associated file descriptor if we got one. */
			REF struct net_codec *nc;
			if unlikely(buffer_fd >= 0) {
				(void)close(buffer_fd);
				buffer_fd = -1;
			}
			nc = (REF struct net_codec *)malloc(sizeof(struct net_codec));
			if unlikely(!nc)
				goto err;
			nc->vc_refcnt = 1;
			nc->vc_destroy = &net_codec_destroy;
			nc->vc_codec   = VIDEO_CODEC_USER;
			bzero(&nc->vc_specs, sizeof(nc->vc_specs));
			nc->vc_specs.vcs_flags = VIDEO_CODEC_FLAG_SPECIAL;
			nc->vc_align = 1;
			nc->vc_nalgn = nc;
			nc->vc_rambuffer_requirements = &net_codec_rambuffer_requirements;
			nc->vc_coord2bytes = &net_codec_coord2bytes;
			nc->vc_pixel2color = &net_codec_pixel2color;
			nc->vc_color2pixel = &net_codec_color2pixel;
			nc->vc_initconverter = &initconv_from_rgba;
			nc->vc_getpixel = &net_codec_getpixel;
#undef vc_setpixel
			nc->vc_setpixel = &net_codec_setpixel;
#ifdef CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3
#ifndef VIDEO_CODEC_HAVE__VC_SETPIXEL3_DUMMY
			nc->_vc_setpixel3 = &net_codec_setpixel3;
#endif /* !VIDEO_CODEC_HAVE__VC_SETPIXEL3_DUMMY */
#endif /* CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3 */
			nc->vc_linefill = &net_codec_linefill;
			nc->vc_vertfill = &net_codec_vertfill;
			nc->vc_rectfill = &net_codec_rectfill;
			nc->vc_rectcopy = &net_codec_rectcopy;
			nc->vc_rectmove = &net_codec_rectmove;
			nc->vc_linecopy = &net_codec_linecopy;
#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
			nc->vc_pixel2color64 = &net_codec_pixel2color64;
			nc->vc_color2pixel64 = &net_codec_color2pixel64;
			nc->vc_getpixel64 = &net_codec_getpixel64;
			nc->vc_setpixel64 = &net_codec_setpixel64;
			nc->vc_linefill64 = &net_codec_linefill64;
			nc->vc_vertfill64 = &net_codec_vertfill64;
			nc->vc_rectfill64 = &net_codec_rectfill64;
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */
			nc->nc_io = io;
			codec = nc;
		}
	}

	/* Load palette if used by the codec. */
	palette = NULL;
	if (codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_PAL) {
		ssize_t palette_size;
		video_pixel_t palsz = video_codec_getpalcolors(codec);
		palette = video_domain_newpalette(domain, palsz);
		if unlikely(!palette)
			goto err_buffer_fd_codec;
		cmd.nbp_cmd = NETBUF_CMD_GETPAL;
		if unlikely(video_deserializer_io_writepacket(io, &cmd, sizeof(cmd), 2))
			goto err_buffer_fd_codec_palette;
		palette_size = video_deserializer_io_readpacket(io, video_palette_getcolors(palette),
		                                                palsz * sizeof(video_color_t),
		                                                NULL, 2);
		if unlikely(palette_size < 0)
			goto err_buffer_fd_codec_palette;
		palette_size /= sizeof(video_color_t);
		bzero(video_palette_getcolors(palette) + palette_size,
		      palsz - palette_size, sizeof(video_color_t));
		palette = video_palette_optimize(palette);
	}

	result_flags = UNALIGNED_GETLE32(&fdinfo.nbfi_info.nbi_flags);
	result_flags &= ~VIDEO_GFX_F_PALOBJ;
#ifdef CONFIG_LIBVIDEO_HAVE_RLE
	result_flags &= ~VIDEO_GFX_F_RLE;
#endif /* CONFIG_LIBVIDEO_HAVE_RLE */
	if (palette)
		result_flags |= VIDEO_GFX_F_PALOBJ;
	result_xdim = UNALIGNED_GETLE32(&fdinfo.nbfi_info.nbi_xdim);
	result_ydim = UNALIGNED_GETLE32(&fdinfo.nbfi_info.nbi_ydim);

	/* Check for special case: completely empty buffer */
	if unlikely(!result_xdim || !result_ydim) {
		/* TODO */
	}

	/* Check for special case: empty buffer with non-zero dimensions */
	if ((size_t)fdinfo_size >= sizeof(struct netbuf_fdinfo) &&
	    UNALIGNED_GETLE32(&fdinfo.nbfi_total) == 0) {
		/* TODO */
	}

	/* Check for simple case: got a file descriptor that can be used to mmap the buffer */
	if ((size_t)fdinfo_size >= sizeof(struct netbuf_fdinfo) && buffer_fd >= 0) {
		REF struct video_ramfdbuffer *ramfd;
		ramfd = (REF struct video_ramfdbuffer *)malloc(sizeof(struct video_ramfdbuffer));
		if unlikely(!ramfd)
			goto err_buffer_fd_codec_palette;
		result = ramfd;
		ramfd->rfdb_total = UNALIGNED_GETLE32(&fdinfo.nbfi_total);
		ramfd->rfdb_fd    = buffer_fd;
		ramfd->rb_data = (byte_t *)mmap(NULL, ramfd->rfdb_total, PROT_READ | PROT_WRITE,
		                                MAP_SHARED | MAP_FILE, buffer_fd,
		                                UNALIGNED_GETLE32(&fdinfo.nbfi_bxoff));
		if unlikely(ramfd->rb_data == (byte_t *)MAP_FAILED)
			goto err_buffer_fd_codec_palette_result;
		ramfd->rb_stride = UNALIGNED_GETLE32(&fdinfo.nbfi_stride);
		ramfd->vb_surf.vs_pal = palette; /* Inherit reference */
		ramfd->vb_surf.vs_buffer = ramfd;
		ramfd->vb_surf.vs_flags = result_flags;
		ramfd->vb_surf.vs_colorkey = UNALIGNED_GETLE32(&fdinfo.nbfi_info.nbi_ckey);
		ramfd->vb_codec = codec; /* Inherit reference */
		__video_buffer_init_ops(ramfd, _ramfdbuffer_ops());
		__video_buffer_init_domain(ramfd, domain);
		__video_buffer_init_dim(ramfd,
		                        UNALIGNED_GETLE32(&fdinfo.nbfi_xdim),
		                        UNALIGNED_GETLE32(&fdinfo.nbfi_ydim));
		ramfd->vb_refcnt = 1;
		if (fdinfo.nbfi_hwops) {
			/* XXX: Custom operator table to still use NET I/O for certain GFX ops */
		}

		/* Check if the server wants us to apply a sub-byte pixel offset. */
		if (fdinfo.nbfi_bxrem) {
			REF struct video_ramfdbuffer_subregion_rem *sr;
			uint32_t bxrem = UNALIGNED_GETLE32(&fdinfo.nbfi_bxrem);
			sr = (REF struct video_ramfdbuffer_subregion_rem *)malloc(sizeof(struct video_ramfdbuffer_subregion_rem));
			if unlikely(!sr)
				goto err_r;
			sr->vb_surf.vs_pal = video_buffer_getpalette(result);
			sr->vb_surf.vs_buffer = sr;
			sr->vb_surf.vs_flags = video_buffer_getflags(result);
			sr->vb_surf.vs_colorkey = video_buffer_getcolorkey(result);
			sr->vb_codec = video_buffer_getcodec(result);
			__video_buffer_init_ops(sr, _ramfdbuffer_subregion_rem_ops());
			__video_buffer_init_domain(sr, domain);
			__video_buffer_init_dim(sr, video_buffer_getxdim(result) - bxrem,
			                        video_buffer_getydim(result));
			__video_buffer_init_common(sr);
			sr->rfdbsr_base = ramfd; /* Inherit reference */
			sr->rfdbsr_bxrem = bxrem;
			result = sr;
		}

		/* Check if we need to apply a super-region wrapper around the buffer.
		 * This needs to happen when  the effective pixel area extends  beyond
		 * the physically accessible pixel area. */
		if (fdinfo.nbfi_cxoff || fdinfo.nbfi_cyoff ||
		    video_buffer_getxdim(result) != result_xdim ||
		    video_buffer_getydim(result) != result_ydim) {
			struct video_rect rect;
			REF struct video_buffer *region;
			rect.vr_xmin = (int32_t)UNALIGNED_GETLE32(&fdinfo.nbfi_cxoff);
			rect.vr_ymin = (int32_t)UNALIGNED_GETLE32(&fdinfo.nbfi_cyoff);
			rect.vr_xdim = result_xdim;
			rect.vr_ydim = result_ydim;
			region = _libvideo_surface_region_distinct(video_buffer_assurface(result), &rect);
			if unlikely(!region)
				goto err_r;
			video_buffer_decref(result);
			result = region;
		}

		/* Close the NET connection since the buffer isn't going to use it. */
		video_deserializer_io_destroy(io);
		return result;
	}

	/* Must create a NET-only video buffer client.
	 * iow: one that uses "io" to serialize GFX commands. */
	{
		REF struct net_buffer *nb;
		nb = (REF struct net_buffer *)malloc(sizeof(struct net_buffer));
		if unlikely(!nb)
			goto err_buffer_fd_codec_palette;
		if (codec->vc_destroy == &net_codec_destroy)
			video_codec_asnet(codec)->nc_buf = nb;
		nb->vb_surf.vs_pal = palette; /* Inherit reference */
		nb->vb_surf.vs_buffer = nb;
		nb->vb_surf.vs_flags = result_flags;
		nb->vb_surf.vs_colorkey = UNALIGNED_GETLE32(&fdinfo.nbfi_info.nbi_ckey);
		nb->vb_codec = codec; /* Inherit reference */
		__video_buffer_init_ops(nb, _net_buffer_ops());
		__video_buffer_init_domain(nb, domain);
		__video_buffer_init_dim(nb, result_xdim, result_ydim);
		nb->vb_refcnt = 1;
		nb->nb_io = io; /* Inherit */
		nb->nb_nexttoken = 3;
		result = nb;
	}
	/* If we somehow got a file descriptor, close it since it's not being used. */
	if unlikely(buffer_fd >= 0)
		(void)close(buffer_fd);
	return result;
err_buffer_fd_codec_palette_result:
	free(result);
err_buffer_fd_codec_palette:
	if (palette)
		video_palette_decref(palette);
err_buffer_fd_codec:
	video_codec_decref(codec);
err_buffer_fd:
	if (buffer_fd >= 0)
		(void)close(buffer_fd);
err:
	return NULL;
err_r:
	result->vb_refcnt = 0;
	video_buffer_destroy(result);
	goto err;
}

DECL_END
#endif /* CONFIG_LIBVIDEO_HAVE_SERIALIZATION */

#endif /* !GUARD_LIBVIDEO_GFX_SERIAL_C */
