/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
gcc_opt.removeif(x -> x.startswith("-O"));
gcc_opt.append("-O3"); // Force _all_ optimizations because stuff in here is performance-critical
]]]*/
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
#ifndef GUARD_LIBVIDEO_GFX_IO_PNG_LODEPNG_C_INL
#define GUARD_LIBVIDEO_GFX_IO_PNG_LODEPNG_C_INL 1
#define LIBVIDEO_GFX_EXPOSE_INTERNALS
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/align.h>
#include <hybrid/minmax.h>

#include <kos/types.h>

#include <errno.h>
#include <malloc.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <libvideo/gfx/buffer.h>
/**/

#include "../io-utils.h"
#include "../ram-buffer.h"

/**/

/* Configure lodepng */
//#define LODEPNG_NO_COMPILE_ZLIB
#define LODEPNG_NO_COMPILE_DISK
#define LODEPNG_NO_COMPILE_ANCILLARY_CHUNKS
#define LODEPNG_NO_COMPILE_ERROR_TEXT
#define LODEPNG_NO_COMPILE_CPP

/* Pull in lodepng */
__pragma_GCC_diagnostic_push
__pragma_GCC_diagnostic_ignored(Wsuggest_attribute_const)
__pragma_GCC_diagnostic_ignored(Wsuggest_attribute_pure)
__pragma_GCC_diagnostic_ignored(Wstringop_overflow)
#pragma GCC visibility push(hidden) /* Don't export any of this stuff... */
#include "lodepng/lodepng.h"
#include "lodepng/lodepng.c"
#include <kos/anno.h>
#include <libvideo/codec/codecs.h>
#include <libvideo/codec/palette.h>
#include <libvideo/gfx/blend.h>
#include <libvideo/gfx/gfx.h>
#pragma GCC visibility pop
__pragma_GCC_diagnostic_pop

DECL_BEGIN

PRIVATE void CC
png_release_mem_free(void *cookie, void *mem) {
	(void)cookie;
	free(mem);
}

PRIVATE ATTR_CONST unsigned int CC
get_lodepng_stride(unsigned int w,
                   LodePNGColorType colortype,
                   unsigned int bitdepth) {
	unsigned int stride;
	switch (colortype) {
	case LCT_GREY:
	case LCT_PALETTE:
		switch (bitdepth) {
		case 1: stride = CEILDIV(w, 8); break;
		case 2: stride = CEILDIV(w, 4); break;
		case 4: stride = CEILDIV(w, 2); break;
		case 8: stride = w; break;
		default: __builtin_unreachable();
		}
		break;
	case LCT_GREY_ALPHA:
		stride = w * 2;
		break;
	case LCT_RGB:
		stride = w * 3;
		break;
	case LCT_RGBA:
		stride = w * 4;
		break;
	default: __builtin_unreachable();
	}
	return stride;
}


INTERN ATTR_NOINLINE WUNUSED REF struct video_buffer *CC
libvideo_buffer_open_lodepng(void const *blob, size_t blob_size) {
	LodePNGState state;
	unsigned int w, h, error, stride;
	unsigned char *out;
	REF struct video_buffer *result;
	struct video_codec const *codec;
	video_codec_t codec_name;
	struct video_palette *palette;
	bzero(&state, sizeof(state));
	error = lodepng_inspect(&w, &h, &state, (unsigned char const *)blob, blob_size);
	if (error != 0)
		goto handle_error;

	/* Determine preferred code based on the PNG's native format.
	 * If the caller wants to use a custom codec, they'll need to
	 * blit the PNG buffer into another buffer of their choosing. */
	palette = NULL;
	switch (state.info_png.color.colortype) {
	case LCT_GREY:
		switch (state.info_png.color.bitdepth) {
		case 1: codec_name = VIDEO_CODEC_L1_LSB; break;
		case 2: codec_name = VIDEO_CODEC_L2_LSB; break;
		case 4: codec_name = VIDEO_CODEC_L4_LSB; break;
		default:
			state.info_png.color.bitdepth = 8;
			ATTR_FALLTHROUGH
		case 8:
			codec_name = VIDEO_CODEC_L8;
			break;
		}
		break;
	case LCT_RGB:
		codec_name = VIDEO_CODEC_RGB888;
		state.info_png.color.bitdepth = 8;
		break;
	/* TODO: LCT_PALETTE */
	default:
		state.info_png.color.colortype = LCT_RGBA;
		state.info_png.color.bitdepth  = 8;
		codec_name = VIDEO_CODEC_RGBA8888;
		break;
	}
	codec = video_codec_lookup(codec_name);
	if unlikely(!codec)
		goto err;
	error = lodepng_decode_memory(&out, &w, &h, (unsigned char const *)blob,
	                              blob_size, state.info_png.color.colortype,
	                              state.info_png.color.bitdepth);
	if (error != 0)
		goto handle_error;
	stride = get_lodepng_stride(w, state.info_png.color.colortype,
	                            state.info_png.color.bitdepth);
	result = libvideo_buffer_formem(out, w, h, stride, codec, palette,
	                                &png_release_mem_free, NULL);
	if unlikely(!result)
		free(out);
	return result;
handle_error:
	switch (error) {
	case 27: /* File too small */
	case 28: /* Wrong header (not a PNG file) */
	case 94: /* Wrong header size */
	case 29: /* Wrong first chunk type */
		return VIDEO_BUFFER_WRONG_FMT;
	case 83: /* OOM */
		errno = ENOMEM;
		return NULL;
	default: break;
	}
err:
	errno = EINVAL; /* Malformed PNG file. */
	return NULL;
}

PRIVATE unsigned
my_lodepng_encode_memory(unsigned char **out, size_t *outsize, unsigned char const *image,
                         unsigned w, unsigned h, LodePNGColorType colortype, unsigned bitdepth,
                         char const *options) {
	(void)options; /* TODO (stuff like additional meta-data to embed) */
	return lodepng_encode_memory(out, outsize, image, w, h, colortype, bitdepth);
}

PRIVATE WUNUSED NONNULL((1)) byte_t *CC
video_lock_convert_stride(struct video_lock *__restrict self,
                          size_t new_stride, unsigned int h) {
	byte_t *result = (byte_t *)malloc(new_stride, h);
	if likely(result) {
		unsigned int y;
		byte_t const *src = self->vl_data;
		byte_t *dst = result;
		size_t common = MIN(new_stride, self->vl_stride);
		for (y = 0; y < h; ++y, src += self->vl_stride, dst += new_stride)
			memcpy(dst, src, common);
	}
	return result;
}

/* Convert "self" into a RGB/RGBA buffer. */
PRIVATE ATTR_NOINLINE WUNUSED NONNULL((1)) REF struct video_buffer *CC
libvideo_buffer_convert_to_lodepng_rgb(struct video_buffer *__restrict self) {
	REF struct video_buffer *rgb_buffer;
	bool has_alpha = self->vb_format.vf_codec->vc_specs.vcs_amask != 0;
	struct video_codec const *codec;
	codec = video_codec_lookup(has_alpha ? VIDEO_CODEC_RGBA8888
	                                     : VIDEO_CODEC_RGB888);
	if unlikely(!codec) {
		errno = ENOTSUP;
		return NULL;
	}
	rgb_buffer = libvideo_rambuffer_create(self->vb_xdim,
	                                       self->vb_ydim,
	                                       codec, NULL);
	if likely(rgb_buffer) {
		/* Do a blit of "self" into "rgb_buffer" */
		struct video_gfx dst_gfx;
		struct video_gfx src_gfx;
		video_buffer_getgfx(rgb_buffer, &dst_gfx,
		                    GFX_BLENDMODE_OVERRIDE,
		                    VIDEO_GFX_F_NORMAL, 0);
		video_buffer_getgfx(self, &src_gfx,
		                    GFX_BLENDMODE_OVERRIDE,
		                    VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit(&dst_gfx, 0, 0,
		                  &src_gfx, 0, 0,
		                  self->vb_xdim, self->vb_ydim);
	}
	return rgb_buffer;
}

PRIVATE WUNUSED NONNULL((1, 2)) int CC
libvideo_buffer_convert_and_save_lodepng(struct video_buffer *__restrict self,
                                     FILE *stream, char const *options) {
	int result;
	REF struct video_buffer *rgb_buffer;
	rgb_buffer = libvideo_buffer_convert_to_lodepng_rgb(self);
	if unlikely(!rgb_buffer)
		return -1;
	result = libvideo_buffer_save_lodepng(rgb_buffer, stream, options);
	video_buffer_decref(rgb_buffer);
	return result;
}

INTERN ATTR_NOINLINE WUNUSED NONNULL((1, 2)) int CC
libvideo_buffer_save_lodepng(struct video_buffer *__restrict self,
                             FILE *stream, char const *options) {
	int result;
	LodePNGColorType colortype;
	unsigned int bitdepth;
	unsigned int error;
	unsigned int lodepng_stride;
	unsigned char *out;
	size_t out_size;
	struct video_lock lock;
	switch (self->vb_format.vf_codec->vc_codec) {
	case VIDEO_CODEC_L1_LSB:
		colortype = LCT_GREY;
		bitdepth  = 1;
		break;
	case VIDEO_CODEC_L2_LSB:
		colortype = LCT_GREY;
		bitdepth  = 2;
		break;
	case VIDEO_CODEC_L4_LSB:
		colortype = LCT_GREY;
		bitdepth  = 4;
		break;
	case VIDEO_CODEC_L8:
		colortype = LCT_GREY;
		bitdepth  = 8;
		break;
	case VIDEO_CODEC_RGBA8888:
		colortype = LCT_RGBA;
		bitdepth  = 8;
		break;
	case VIDEO_CODEC_RGB888:
		colortype = LCT_RGB;
		bitdepth  = 8;
		break;

	default:
		/* Convert "self" into a supported codec */
		return libvideo_buffer_convert_and_save_lodepng(self, stream, options);
	}

	result = (*self->vb_ops->vi_rlock)(self, &lock);
	if unlikely(result)
		return result;
	lodepng_stride = get_lodepng_stride(self->vb_xdim,
	                                    colortype, bitdepth);
	if likely(lodepng_stride == lock.vl_stride) {
		error = my_lodepng_encode_memory(&out, &out_size,
		                                 (unsigned char const *)lock.vl_data,
		                                 self->vb_xdim, self->vb_ydim,
		                                 colortype, bitdepth, options);
	} else {
		byte_t *fixed_stride;
		fixed_stride = video_lock_convert_stride(&lock,
		                                         lodepng_stride,
		                                         self->vb_ydim);
		if unlikely(!fixed_stride) {
			error = 83; /* OOM */
		} else {
			error = my_lodepng_encode_memory(&out, &out_size,
			                                 (unsigned char const *)fixed_stride,
			                                 self->vb_xdim, self->vb_ydim,
			                                 colortype, bitdepth, options);
			free(fixed_stride);
		}
	}
	(*self->vb_ops->vi_unlock)(self, &lock);
	switch (error) {
	case 0:
		result = 0;
		break;
	case 83: /* OOM */
		errno  = ENOMEM;
		result = -1;
		break;
	default:
		errno  = EINVAL; /* Something was invalid... */
		result = -1;
		break;
	}

	/* On success, write lodepng's buffer to the output stream. */
	if likely(result == 0) {
		int old_errno = errno;
		errno = 0;
		if (fwrite(out, 1, out_size, stream) != out_size) {
			if (errno == 0)
				errno = ENOSPC;
			result = -1;
		} else {
			errno = old_errno;
		}
		free(out);
	}
	return result;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_IO_PNG_LODEPNG_C_INL */
