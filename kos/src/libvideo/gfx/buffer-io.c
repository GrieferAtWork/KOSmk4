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
#ifndef GUARD_LIBVIDEO_GFX_BUFFER_IO_C
#define GUARD_LIBVIDEO_GFX_BUFFER_IO_C 1
#define LIBVIDEO_GFX_EXPOSE_INTERNALS
#define _KOS_SOURCE 1

#include "api.h"

#include <hybrid/compiler.h>

#include <hybrid/align.h>
#include <hybrid/minmax.h>

#include <kos/types.h>
#include <sys/mman.h>
#include <sys/syslog.h>

#include <assert.h>
#include <dlfcn.h>
#include <errno.h>
#include <malloc.h>
#include <pthread.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <libiberty.h>
#include <libvideo/gfx/buffer.h>
/**/

#include "buffer-io.h"
#include "ram-buffer.h"

/**/

/* Configure lodepng */
//#define LODEPNG_NO_COMPILE_ZLIB /* TODO: Load libzlib and use *it* to off-load compression out-of our lib */
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
#pragma GCC visibility pop
__pragma_GCC_diagnostic_pop

DECL_BEGIN

PRIVATE void CC
release_mem_free(void *cookie, void *mem) {
	(void)cookie;
	free(mem);
}


/* Returned by `libvideo_buffer_open_*' when the blob doesn't match the specified format. */
#define VIDEO_BUFFER_WRONG_FMT ((REF struct video_buffer *)-1)

/************************************************************************/
/* PNG                                                                  */
/************************************************************************/

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


PRIVATE ATTR_NOINLINE WUNUSED REF struct video_buffer *CC
libvideo_buffer_open_png(void const *blob, size_t blob_size) {
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
		case 1: codec_name = VIDEO_CODEC_GRAY2_LSB; break;
		case 2: codec_name = VIDEO_CODEC_GRAY4_LSB; break;
		case 4: codec_name = VIDEO_CODEC_GRAY16_LSB; break;
		default:
			state.info_png.color.bitdepth = 8;
			ATTR_FALLTHROUGH
		case 8:
			codec_name = VIDEO_CODEC_GRAY256;
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
	                                &release_mem_free, NULL);
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
libvideo_buffer_convert_to_rgb(struct video_buffer *__restrict self) {
	REF struct video_buffer *rgb_buffer;
	bool has_alpha = self->vb_format.vf_codec->vc_specs.vcs_amask != 0;
	struct video_codec const *codec;
	codec = video_codec_lookup(has_alpha ? VIDEO_CODEC_RGBA8888
	                                     : VIDEO_CODEC_RGB888);
	if unlikely(!codec) {
		errno = ENOTSUP;
		return NULL;
	}
	rgb_buffer = libvideo_rambuffer_create(self->vb_size_x,
	                                       self->vb_size_y,
	                                       codec, NULL);
	if likely(rgb_buffer) {
		/* Do a blit of "self" into "rgb_buffer" */
		struct video_gfx dst_gfx;
		struct video_gfx src_gfx;
		struct video_blit blit;
		video_buffer_getgfx(rgb_buffer, &dst_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_FNORMAL, 0);
		video_buffer_getgfx(self, &src_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_FNORMAL, 0);
		video_gfx_blitfrom(&dst_gfx, &src_gfx, &blit);
		video_blit_blit(&blit, 0, 0, 0, 0, self->vb_size_x, self->vb_size_y);
	}
	return rgb_buffer;
}

PRIVATE ATTR_NOINLINE WUNUSED NONNULL((1, 2)) int CC
libvideo_buffer_save_png(struct video_buffer *__restrict self,
                         FILE *stream, char const *options);

PRIVATE WUNUSED NONNULL((1, 2)) int CC
libvideo_buffer_convert_and_save_png(struct video_buffer *__restrict self,
                                     FILE *stream, char const *options) {
	int result;
	REF struct video_buffer *rgb_buffer;
	rgb_buffer = libvideo_buffer_convert_to_rgb(self);
	if unlikely(!rgb_buffer)
		return -1;
	result = libvideo_buffer_save_png(rgb_buffer, stream, options);
	video_buffer_decref(rgb_buffer);
	return result;
}

PRIVATE ATTR_NOINLINE WUNUSED NONNULL((1, 2)) int CC
libvideo_buffer_save_png(struct video_buffer *__restrict self,
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
	case VIDEO_CODEC_GRAY2_LSB:
		colortype = LCT_GREY;
		bitdepth  = 1;
		break;
	case VIDEO_CODEC_GRAY4_LSB:
		colortype = LCT_GREY;
		bitdepth  = 2;
		break;
	case VIDEO_CODEC_GRAY16_LSB:
		colortype = LCT_GREY;
		bitdepth  = 4;
		break;
	case VIDEO_CODEC_GRAY256:
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
		return libvideo_buffer_convert_and_save_png(self, stream, options);
	}

	result = (*self->vb_ops->vi_rlock)(self, &lock);
	if unlikely(result)
		return result;
	lodepng_stride = get_lodepng_stride(self->vb_size_x,
	                                    colortype, bitdepth);
	if likely(lodepng_stride == lock.vl_stride) {
		error = my_lodepng_encode_memory(&out, &out_size,
		                                 (unsigned char const *)lock.vl_data,
		                                 self->vb_size_x, self->vb_size_y,
		                                 colortype, bitdepth, options);
	} else {
		byte_t *fixed_stride;
		fixed_stride = video_lock_convert_stride(&lock,
		                                         lodepng_stride,
		                                         self->vb_size_y);
		if unlikely(!fixed_stride) {
			error = 83; /* OOM */
		} else {
			error = my_lodepng_encode_memory(&out, &out_size,
			                                 (unsigned char const *)fixed_stride,
			                                 self->vb_size_x, self->vb_size_y,
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

/************************************************************************/
/* JPG                                                                  */
/************************************************************************/

typedef unsigned int JPEGLIB_JDIMENSION;
typedef int JPEGLIB_J_COLOR_SPACE;
typedef byte_t JPEGLIB_JSAMPLE;
typedef JPEGLIB_JSAMPLE *JPEGLIB_JSAMPROW;
typedef JPEGLIB_JSAMPROW *JPEGLIB_JSAMPARRAY;
typedef int JPEGLIB_boolean;

#define JPEGLIB_JPEG_LIB_VERSION 90
#ifdef __x86_64__
#define JPEGLIB_JCS_GRAYSCALE                                      1
#define JPEGLIB_JCS_RGB                                            2
#define JPEGLIB_SIZEOF_jpeg_error_mgr                              168
#define JPEGLIB_OFFSETOF_jpeg_error_mgr__error_exit                0
#define JPEGLIB_OFFSETOF_jpeg_common_struct__err                   0
#define JPEGLIB_SIZEOF_jpeg_compress_struct                        584
#define JPEGLIB_ALIGNOF_jpeg_compress_struct                       8
#define JPEGLIB_OFFSETOF_jpeg_compress_struct__image_width         48
#define JPEGLIB_OFFSETOF_jpeg_compress_struct__image_height        52
#define JPEGLIB_OFFSETOF_jpeg_compress_struct__input_components    56
#define JPEGLIB_OFFSETOF_jpeg_compress_struct__in_color_space      60
#define JPEGLIB_OFFSETOF_jpeg_compress_struct__next_scanline       344
#define JPEGLIB_SIZEOF_jpeg_decompress_struct                      664
#define JPEGLIB_ALIGNOF_jpeg_decompress_struct                     8
#define JPEGLIB_OFFSETOF_jpeg_decompress_struct__out_color_space   64
#define JPEGLIB_OFFSETOF_jpeg_decompress_struct__output_width      136
#define JPEGLIB_OFFSETOF_jpeg_decompress_struct__output_height     140
#define JPEGLIB_OFFSETOF_jpeg_decompress_struct__output_scanline   168
#define JPEGLIB_OFFSETOF_jpeg_decompress_struct__output_components 148
#elif defined(__i386__)
#define JPEGLIB_JCS_GRAYSCALE                                      1
#define JPEGLIB_JCS_RGB                                            2
#define JPEGLIB_SIZEOF_jpeg_error_mgr                              132
#define JPEGLIB_OFFSETOF_jpeg_error_mgr__error_exit                0
#define JPEGLIB_OFFSETOF_jpeg_common_struct__err                   0
#define JPEGLIB_SIZEOF_jpeg_compress_struct                        432
#define JPEGLIB_ALIGNOF_jpeg_compress_struct                       4
#define JPEGLIB_OFFSETOF_jpeg_compress_struct__image_width         28
#define JPEGLIB_OFFSETOF_jpeg_compress_struct__image_height        32
#define JPEGLIB_OFFSETOF_jpeg_compress_struct__input_components    36
#define JPEGLIB_OFFSETOF_jpeg_compress_struct__in_color_space      40
#define JPEGLIB_OFFSETOF_jpeg_compress_struct__next_scanline       260
#define JPEGLIB_SIZEOF_jpeg_decompress_struct                      488
#define JPEGLIB_ALIGNOF_jpeg_decompress_struct                     4
#define JPEGLIB_OFFSETOF_jpeg_decompress_struct__out_color_space   44
#define JPEGLIB_OFFSETOF_jpeg_decompress_struct__output_width      112
#define JPEGLIB_OFFSETOF_jpeg_decompress_struct__output_height     116
#define JPEGLIB_OFFSETOF_jpeg_decompress_struct__output_scanline   140
#define JPEGLIB_OFFSETOF_jpeg_decompress_struct__output_components 124
#else /* ... */
#define NEED_dump_jpeglib_config
#warning "Unknown jpeglib config for this arch; please generate (s.a. `dump_jpeglib_config()')"
#if __has_include(<jpeglib.h>)
DECL_END
#include <jpeglib.h>
DECL_BEGIN
#define JPEGLIB_JCS_GRAYSCALE                                      JCS_GRAYSCALE
#define JPEGLIB_JCS_RGB                                            JCS_RGB
#define JPEGLIB_SIZEOF_jpeg_error_mgr                              sizeof(struct jpeg_error_mgr)
#define JPEGLIB_OFFSETOF_jpeg_error_mgr__error_exit                0
#define JPEGLIB_OFFSETOF_jpeg_common_struct__err                   0
#define JPEGLIB_SIZEOF_jpeg_compress_struct                        sizeof(struct jpeg_compress_struct)
#define JPEGLIB_ALIGNOF_jpeg_compress_struct                       alignof(struct jpeg_compress_struct)
#define JPEGLIB_OFFSETOF_jpeg_compress_struct__image_width         offsetof(struct jpeg_compress_struct, image_width)
#define JPEGLIB_OFFSETOF_jpeg_compress_struct__image_height        offsetof(struct jpeg_compress_struct, image_height)
#define JPEGLIB_OFFSETOF_jpeg_compress_struct__input_components    offsetof(struct jpeg_compress_struct, input_components)
#define JPEGLIB_OFFSETOF_jpeg_compress_struct__in_color_space      offsetof(struct jpeg_compress_struct, in_color_space)
#define JPEGLIB_OFFSETOF_jpeg_compress_struct__next_scanline       offsetof(struct jpeg_compress_struct, next_scanline)
#define JPEGLIB_SIZEOF_jpeg_decompress_struct                      sizeof(struct jpeg_decompress_struct)
#define JPEGLIB_ALIGNOF_jpeg_decompress_struct                     alignof(struct jpeg_decompress_struct)
#define JPEGLIB_OFFSETOF_jpeg_decompress_struct__out_color_space   offsetof(struct jpeg_decompress_struct, out_color_space)
#define JPEGLIB_OFFSETOF_jpeg_decompress_struct__output_width      offsetof(struct jpeg_decompress_struct, output_width)
#define JPEGLIB_OFFSETOF_jpeg_decompress_struct__output_height     offsetof(struct jpeg_decompress_struct, output_height)
#define JPEGLIB_OFFSETOF_jpeg_decompress_struct__output_scanline   offsetof(struct jpeg_decompress_struct, output_scanline)
#define JPEGLIB_OFFSETOF_jpeg_decompress_struct__output_components offsetof(struct jpeg_decompress_struct, output_components)
#endif /* __has_include(<jpeglib.h>) */
#endif /* !... */

#if __has_include(<jpeglib.h>) && (defined(NEED_dump_jpeglib_config) || 0)
DECL_END
#include <jpeglib.h>
DECL_BEGIN

#define HAVE_dump_jpeglib_config
PRIVATE void dump_jpeglib_config(void) {
#define DUMP(s, v) syslog(LOG_DEBUG, "#define %s %Iu\n", s, (size_t)(v))
	DUMP("JPEGLIB_JCS_GRAYSCALE                                     ", JCS_GRAYSCALE);
	DUMP("JPEGLIB_JCS_RGB                                           ", JCS_RGB);
	DUMP("JPEGLIB_SIZEOF_jpeg_error_mgr                             ", sizeof(struct jpeg_error_mgr));
	DUMP("JPEGLIB_OFFSETOF_jpeg_error_mgr__error_exit               ", offsetof(struct jpeg_error_mgr, error_exit));
	DUMP("JPEGLIB_OFFSETOF_jpeg_common_struct__err                  ", offsetof(struct jpeg_common_struct, err));
	DUMP("JPEGLIB_SIZEOF_jpeg_compress_struct                       ", sizeof(struct jpeg_compress_struct));
	DUMP("JPEGLIB_ALIGNOF_jpeg_compress_struct                      ", alignof(struct jpeg_compress_struct));
	DUMP("JPEGLIB_OFFSETOF_jpeg_compress_struct__image_width        ", offsetof(struct jpeg_compress_struct, image_width));
	DUMP("JPEGLIB_OFFSETOF_jpeg_compress_struct__image_height       ", offsetof(struct jpeg_compress_struct, image_height));
	DUMP("JPEGLIB_OFFSETOF_jpeg_compress_struct__input_components   ", offsetof(struct jpeg_compress_struct, input_components));
	DUMP("JPEGLIB_OFFSETOF_jpeg_compress_struct__in_color_space     ", offsetof(struct jpeg_compress_struct, in_color_space));
	DUMP("JPEGLIB_OFFSETOF_jpeg_compress_struct__next_scanline      ", offsetof(struct jpeg_compress_struct, next_scanline));
	DUMP("JPEGLIB_SIZEOF_jpeg_decompress_struct                     ", sizeof(struct jpeg_decompress_struct));
	DUMP("JPEGLIB_ALIGNOF_jpeg_decompress_struct                    ", alignof(struct jpeg_decompress_struct));
	DUMP("JPEGLIB_OFFSETOF_jpeg_decompress_struct__out_color_space  ", offsetof(struct jpeg_decompress_struct, out_color_space));
	DUMP("JPEGLIB_OFFSETOF_jpeg_decompress_struct__output_width     ", offsetof(struct jpeg_decompress_struct, output_width));
	DUMP("JPEGLIB_OFFSETOF_jpeg_decompress_struct__output_height    ", offsetof(struct jpeg_decompress_struct, output_height));
	DUMP("JPEGLIB_OFFSETOF_jpeg_decompress_struct__output_scanline  ", offsetof(struct jpeg_decompress_struct, output_scanline));
	DUMP("JPEGLIB_OFFSETOF_jpeg_decompress_struct__output_components", offsetof(struct jpeg_decompress_struct, output_components));
#undef DUMP
}
#endif /* ... */

#ifndef JPEGLIB_JCS_RGB /* Dummy values... */
#define JPEGLIB_JCS_GRAYSCALE                                      42
#define JPEGLIB_JCS_RGB                                            42
#define JPEGLIB_SIZEOF_jpeg_error_mgr                              42
#define JPEGLIB_OFFSETOF_jpeg_error_mgr__error_exit                42
#define JPEGLIB_OFFSETOF_jpeg_common_struct__err                   42
#define JPEGLIB_SIZEOF_jpeg_compress_struct                        42
#define JPEGLIB_ALIGNOF_jpeg_compress_struct                       42
#define JPEGLIB_OFFSETOF_jpeg_compress_struct__image_width         42
#define JPEGLIB_OFFSETOF_jpeg_compress_struct__image_height        42
#define JPEGLIB_OFFSETOF_jpeg_compress_struct__input_components    42
#define JPEGLIB_OFFSETOF_jpeg_compress_struct__in_color_space      42
#define JPEGLIB_OFFSETOF_jpeg_compress_struct__next_scanline       42
#define JPEGLIB_SIZEOF_jpeg_decompress_struct                      42
#define JPEGLIB_ALIGNOF_jpeg_decompress_struct                     42
#define JPEGLIB_OFFSETOF_jpeg_decompress_struct__out_color_space   42
#define JPEGLIB_OFFSETOF_jpeg_decompress_struct__output_width      42
#define JPEGLIB_OFFSETOF_jpeg_decompress_struct__output_height     42
#define JPEGLIB_OFFSETOF_jpeg_decompress_struct__output_scanline   42
#define JPEGLIB_OFFSETOF_jpeg_decompress_struct__output_components 42
#endif /* !JPEGLIB_JCS_RGB */



struct minimal_jpeg_common_struct;
struct minimal_jpeg_error_mgr {
#if JPEGLIB_OFFSETOF_jpeg_error_mgr__error_exit > 0
	byte_t _pad1[JPEGLIB_OFFSETOF_jpeg_error_mgr__error_exit];
#endif /* JPEGLIB_OFFSETOF_jpeg_error_mgr__error_exit > 0 */
	void (*error_exit)(struct minimal_jpeg_common_struct *cinfo);
	byte_t _pad2[JPEGLIB_SIZEOF_jpeg_error_mgr -
	             (JPEGLIB_OFFSETOF_jpeg_error_mgr__error_exit +
	              __SIZEOF_POINTER__)];
};



struct minimal_jpeg_common_struct {
#if JPEGLIB_OFFSETOF_jpeg_common_struct__err > 0
	byte_t _pad1[JPEGLIB_OFFSETOF_jpeg_common_struct__err];
#endif /* JPEGLIB_OFFSETOF_jpeg_common_struct__err > 0 */
	struct minimal_jpeg_error_mgr *err;
};



struct ATTR_ALIGNED(JPEGLIB_ALIGNOF_jpeg_compress_struct) minimal_jpeg_compress_struct {
#if JPEGLIB_OFFSETOF_jpeg_common_struct__err > 0
	byte_t _pad1[JPEGLIB_OFFSETOF_jpeg_common_struct__err];
#endif /* JPEGLIB_OFFSETOF_jpeg_common_struct__err > 0 */
	struct minimal_jpeg_error_mgr *err;
	byte_t _pad2[JPEGLIB_SIZEOF_jpeg_compress_struct -
	             (JPEGLIB_OFFSETOF_jpeg_common_struct__err +
	              __SIZEOF_POINTER__)];
};

#define minimal_jpeg_compress_struct__set_image_width(self, v) \
	(void)(*(JPEGLIB_JDIMENSION *)((byte_t *)(self) + JPEGLIB_OFFSETOF_jpeg_compress_struct__image_width) = (v))
#define minimal_jpeg_compress_struct__set_image_height(self, v) \
	(void)(*(JPEGLIB_JDIMENSION *)((byte_t *)(self) + JPEGLIB_OFFSETOF_jpeg_compress_struct__image_height) = (v))
#define minimal_jpeg_compress_struct__get_image_height(self) \
	(*(JPEGLIB_JDIMENSION const *)((byte_t const *)(self) + JPEGLIB_OFFSETOF_jpeg_compress_struct__image_height))
#define minimal_jpeg_compress_struct__set_input_components(self, v) \
	(void)(*(int *)((byte_t *)(self) + JPEGLIB_OFFSETOF_jpeg_compress_struct__input_components) = (v))
#define minimal_jpeg_compress_struct__set_in_color_space(self, v) \
	(void)(*(JPEGLIB_J_COLOR_SPACE *)((byte_t *)(self) + JPEGLIB_OFFSETOF_jpeg_compress_struct__in_color_space) = (v))
#define minimal_jpeg_compress_struct__get_next_scanline(self) \
	(*(JPEGLIB_JDIMENSION const *)((byte_t const *)(self) + JPEGLIB_OFFSETOF_jpeg_compress_struct__next_scanline))



struct ATTR_ALIGNED(JPEGLIB_ALIGNOF_jpeg_decompress_struct) minimal_jpeg_decompress_struct {
#if JPEGLIB_OFFSETOF_jpeg_common_struct__err > 0
	byte_t _pad1[JPEGLIB_OFFSETOF_jpeg_common_struct__err];
#endif /* JPEGLIB_OFFSETOF_jpeg_common_struct__err > 0 */
	struct minimal_jpeg_error_mgr *err;
	byte_t _pad2[JPEGLIB_SIZEOF_jpeg_decompress_struct -
	             (JPEGLIB_OFFSETOF_jpeg_common_struct__err +
	              __SIZEOF_POINTER__)];
};

#define minimal_jpeg_decompress_struct__get_output_width(self) \
	(*(JPEGLIB_JDIMENSION const *)((byte_t const *)(self) + JPEGLIB_OFFSETOF_jpeg_decompress_struct__output_width))
#define minimal_jpeg_decompress_struct__get_output_height(self) \
	(*(JPEGLIB_JDIMENSION const *)((byte_t const *)(self) + JPEGLIB_OFFSETOF_jpeg_decompress_struct__output_height))
#define minimal_jpeg_decompress_struct__get_output_scanline(self) \
	(*(JPEGLIB_JDIMENSION const *)((byte_t const *)(self) + JPEGLIB_OFFSETOF_jpeg_decompress_struct__output_scanline))
#define minimal_jpeg_decompress_struct__get_output_components(self) \
	(*(int const *)((byte_t const *)(self) + JPEGLIB_OFFSETOF_jpeg_decompress_struct__output_components))
#define minimal_jpeg_decompress_struct__set_out_color_space(self, v) \
	(void)(*(JPEGLIB_J_COLOR_SPACE *)((byte_t *)(self) + JPEGLIB_OFFSETOF_jpeg_decompress_struct__output_components) = (v))


#define DEFINEJPEGLIB_API(Treturn, name, params) \
	typedef Treturn(*P##name) params;             \
	PRIVATE P##name pdyn_##name = NULL
/* Common */
DEFINEJPEGLIB_API(struct minimal_jpeg_error_mgr *, jpeg_std_error, (struct minimal_jpeg_error_mgr *err));
/* Decompress */
DEFINEJPEGLIB_API(void, jpeg_CreateDecompress, (struct minimal_jpeg_decompress_struct *cinfo, int version, size_t structsize));
DEFINEJPEGLIB_API(void, jpeg_mem_src, (struct minimal_jpeg_decompress_struct *cinfo, byte_t const *inbuffer, size_t insize));
DEFINEJPEGLIB_API(int, jpeg_read_header, (struct minimal_jpeg_decompress_struct *cinfo, JPEGLIB_boolean require_image));
DEFINEJPEGLIB_API(JPEGLIB_boolean, jpeg_start_decompress, (struct minimal_jpeg_decompress_struct *cinfo));
DEFINEJPEGLIB_API(JPEGLIB_JDIMENSION, jpeg_read_scanlines, (struct minimal_jpeg_decompress_struct *cinfo, JPEGLIB_JSAMPARRAY scanlines, JPEGLIB_JDIMENSION max_lines));
DEFINEJPEGLIB_API(JPEGLIB_boolean, jpeg_finish_decompress, (struct minimal_jpeg_decompress_struct *cinfo));
DEFINEJPEGLIB_API(void, jpeg_destroy_decompress, (struct minimal_jpeg_decompress_struct *cinfo));
/* Compress */
DEFINEJPEGLIB_API(void, jpeg_CreateCompress, (struct minimal_jpeg_compress_struct *cinfo, int version, size_t structsize));
DEFINEJPEGLIB_API(void, jpeg_stdio_dest, (struct minimal_jpeg_compress_struct *cinfo, FILE *outfile));
DEFINEJPEGLIB_API(void, jpeg_set_defaults, (struct minimal_jpeg_compress_struct *cinfo));
DEFINEJPEGLIB_API(void, jpeg_set_quality, (struct minimal_jpeg_compress_struct *cinfo, int quality, JPEGLIB_boolean force_baseline));
DEFINEJPEGLIB_API(void, jpeg_start_compress, (struct minimal_jpeg_compress_struct *cinfo, JPEGLIB_boolean write_all_tables));
DEFINEJPEGLIB_API(JPEGLIB_JDIMENSION, jpeg_write_scanlines, (struct minimal_jpeg_compress_struct *cinfo, JPEGLIB_JSAMPARRAY scanlines, JPEGLIB_JDIMENSION num_lines));
DEFINEJPEGLIB_API(void, jpeg_finish_compress, (struct minimal_jpeg_compress_struct *cinfo));
DEFINEJPEGLIB_API(void, jpeg_destroy_compress, (struct minimal_jpeg_compress_struct *cinfo));
#undef DEFINEJPEGLIB_API


PRIVATE void *CC dlsym2(void *handle, char const *name1, char const *name2) {
	void *result = dlsym(handle, name1);
	if (result == NULL)
		result = dlsym(handle, name2);
	return result;
}

PRIVATE void __LIBCCALL jpeglib_loadapi_impl(void) {
	void *jpeglib_so;
#ifdef HAVE_dump_jpeglib_config
	dump_jpeglib_config();
#endif /* HAVE_dump_jpeglib_config */
	jpeglib_so = dlopen("libjpeg.so.9", RTLD_LOCAL);
	if unlikely(!jpeglib_so)
		return;
#define LOADSYM2(name1, name2)                                                  \
	if ((*(void **)&pdyn_##name1 = dlsym2(jpeglib_so, #name1, #name2)) == NULL) \
		goto fail
	LOADSYM2(jpeg_CreateDecompress, jCreaDecompress);
	LOADSYM2(jpeg_mem_src, jMemSrc);
	LOADSYM2(jpeg_read_header, jReadHeader);
	LOADSYM2(jpeg_start_decompress, jStrtDecompress);
	LOADSYM2(jpeg_read_scanlines, jReadScanlines);
	LOADSYM2(jpeg_finish_decompress, jFinDecompress);
	LOADSYM2(jpeg_destroy_decompress, jDestDecompress);

	LOADSYM2(jpeg_CreateCompress, jCreaCompress);
	LOADSYM2(jpeg_stdio_dest, jStdDest);
	LOADSYM2(jpeg_set_defaults, jSetDefaults);
	LOADSYM2(jpeg_set_quality, jSetQuality);
	LOADSYM2(jpeg_start_compress, jStrtCompress);
	LOADSYM2(jpeg_write_scanlines, jWrtScanlines);
	LOADSYM2(jpeg_finish_compress, jFinCompress);
	LOADSYM2(jpeg_destroy_compress, jDestCompress);

	COMPILER_BARRIER();
	LOADSYM2(jpeg_std_error, jStdError);
#undef LOADSYM
	return;
fail:
	syslog(LOG_WARN, "[libvideo-gfx][jpeglib] Failed to load API: %s\n", dlerror());
	dlclose(jpeglib_so);
	pdyn_jpeg_std_error = NULL;
}

PRIVATE pthread_once_t jpeglib_loadapi_done = PTHREAD_ONCE_INIT;
PRIVATE bool CC jpeglib_loadapi(void) {
	pthread_once(&jpeglib_loadapi_done,
	             &jpeglib_loadapi_impl);
	return pdyn_jpeg_std_error != NULL;
}


struct used_jpeg_error_mgr {
	jmp_buf                       ejem_jmp;
	struct minimal_jpeg_error_mgr ejem_mgr;
};

PRIVATE ATTR_NORETURN void
libvideo_jpeg_error_handling(struct minimal_jpeg_common_struct *cinfo) {
	struct used_jpeg_error_mgr *used_mgr;
	used_mgr = container_of(cinfo->err, struct used_jpeg_error_mgr, ejem_mgr);
	longjmp(used_mgr->ejem_jmp, 1);
}

PRIVATE ATTR_NOINLINE WUNUSED REF struct video_buffer *CC
libvideo_buffer_open_jpg(void const *blob, size_t blob_size) {
	video_codec_t result_codec_id;
	struct video_codec const *result_codec;
	REF struct video_buffer *result;
	struct video_lock vid_lock;
	size_t result_size_x, result_size_y;
	struct minimal_jpeg_decompress_struct decomp;
	struct used_jpeg_error_mgr err;
	if (!jpeglib_loadapi())
		return VIDEO_BUFFER_WRONG_FMT;

	/* Setup jpeglib error handler */
	result = NULL;
	vid_lock.vl_data = NULL;
	decomp.err = (*pdyn_jpeg_std_error)(&err.ejem_mgr);
	err.ejem_mgr.error_exit = &libvideo_jpeg_error_handling;
	if (setjmp(err.ejem_jmp) != 0) {
#if 1
		syslog(LOG_WARN, "[libvideo-gfx][jpeglib] Load error: %$[hex]\n",
		       sizeof(err.ejem_mgr), &err.ejem_mgr);
#endif
err_wrong_fmt:
		(void)(*pdyn_jpeg_destroy_decompress)(&decomp);
		if (vid_lock.vl_data)
			video_buffer_unlock(result, &vid_lock);
		if (result)
			video_buffer_decref(result);
		return VIDEO_BUFFER_WRONG_FMT;
	}

	/* Initialize decompresser and start processing data */
	(void)(*pdyn_jpeg_CreateDecompress)(&decomp, JPEGLIB_JPEG_LIB_VERSION,
	                                    JPEGLIB_SIZEOF_jpeg_decompress_struct);
	(void)(*pdyn_jpeg_mem_src)(&decomp, (byte_t const *)blob, blob_size);
	(void)(*pdyn_jpeg_read_header)(&decomp, 1);
	minimal_jpeg_decompress_struct__set_out_color_space(&decomp, JPEGLIB_JCS_RGB);
	(void)(*pdyn_jpeg_start_decompress)(&decomp);

	/* Extra image size */
	result_size_x = minimal_jpeg_decompress_struct__get_output_width(&decomp);
	result_size_y = minimal_jpeg_decompress_struct__get_output_height(&decomp);
	switch (minimal_jpeg_decompress_struct__get_output_components(&decomp)) {
	case 2: result_codec_id = VIDEO_CODEC_RGB565; break; /* ??? */
	case 3: result_codec_id = VIDEO_CODEC_RGB888; break;
	case 4: result_codec_id = VIDEO_CODEC_RGBX8888; break; /* ??? */
	default: goto err_wrong_fmt;
	}
	result_codec = video_codec_lookup(result_codec_id);
	if unlikely(!result_codec)
		goto err_wrong_fmt;

	/* Allocate video buffer */
	result = libvideo_buffer_create(VIDEO_BUFFER_RAM,
	                                result_size_x, result_size_y,
	                                result_codec, NULL);
	if unlikely(!result)
		goto err_errno;
	if unlikely(video_buffer_wlock(result, &vid_lock) != 0)
		goto err_errno_r;
	__builtin_assume(result_size_x == result->vb_size_x);
	__builtin_assume(result_size_y == result->vb_size_y);

	/* Read scanlines... */
	for (;;) {
		JPEGLIB_JSAMPROW scanline;
		JPEGLIB_JSAMPARRAY scanlines;
		JPEGLIB_JDIMENSION scanline_y;
		scanline_y = minimal_jpeg_decompress_struct__get_output_scanline(&decomp);
		if (scanline_y >= result_size_y)
			break;
		scanline = vid_lock.vl_data + scanline_y * vid_lock.vl_stride;
		scanlines = &scanline;
		(void)(*pdyn_jpeg_read_scanlines)(&decomp, scanlines, 1);
	}

	/* Cleanup... */
	(void)(*pdyn_jpeg_finish_decompress)(&decomp);
	(void)(*pdyn_jpeg_destroy_decompress)(&decomp);

	/* Release video lock and return buffer */
	video_buffer_unlock(result, &vid_lock);
	return result;
err_errno_r:
	video_buffer_decref(result);
	{
		int saved_errno;
err_errno:
		saved_errno = errno;
		(void)(*pdyn_jpeg_destroy_decompress)(&decomp);
		errno = saved_errno;
	}
	return NULL;
}

PRIVATE ATTR_NOINLINE WUNUSED NONNULL((1, 2)) int CC
libvideo_buffer_save_jpg(struct video_buffer *__restrict self,
                         FILE *stream, char const *options) {
	video_codec_t in_codec_id;
	struct minimal_jpeg_compress_struct comp;
	struct used_jpeg_error_mgr err;
	struct video_lock vid_lock;
	JPEGLIB_J_COLOR_SPACE comp_in_color_space;
	int comp_input_components;
	if (!jpeglib_loadapi()) {
		errno = ENOSYS;
		return -1;
	}

	in_codec_id = self->vb_format.vf_codec->vc_codec;
	switch (in_codec_id) {

	case VIDEO_CODEC_GRAY256:
		comp_in_color_space   = JPEGLIB_JCS_GRAYSCALE;
		comp_input_components = 1;
		break;

	case VIDEO_CODEC_RGB888:
		comp_in_color_space   = JPEGLIB_JCS_RGB;
		comp_input_components = 3;
		break;

	default: {
		/* Fallback: convert to most appropriate fallback codec, and then save it as a buffer */
		int result;
		struct video_codec const *in_codec;
		struct video_buffer *conv_buffer;
		in_codec_id = (self->vb_format.vf_codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_GRAY)
		           ? VIDEO_CODEC_GRAY256
		           : VIDEO_CODEC_RGB888;
		in_codec = video_codec_lookup(in_codec_id);
		if unlikely(!in_codec) {
			errno = EINVAL;
			return -1;
		}
		conv_buffer = libvideo_buffer_convert(self, in_codec, NULL, VIDEO_BUFFER_RAM);
		if unlikely(!conv_buffer)
			return -1;
		result = libvideo_buffer_save_jpg(conv_buffer, stream, options);
		video_buffer_decref(conv_buffer);
		return result;
	}	break;

	}

	/* Setup jpeglib error handler */
	vid_lock.vl_data = NULL;
	comp.err = (*pdyn_jpeg_std_error)(&err.ejem_mgr);
	err.ejem_mgr.error_exit = &libvideo_jpeg_error_handling;
	if (setjmp(err.ejem_jmp) != 0) {
#if 1
		syslog(LOG_WARN, "[libvideo-gfx][jpeglib] Save error: %$[hex]\n",
		       sizeof(err.ejem_mgr), &err.ejem_mgr);
#endif
		(void)(*pdyn_jpeg_destroy_compress)(&comp);
		if (vid_lock.vl_data)
			video_buffer_unlock(self, &vid_lock);
		errno = EIO; /* ??? */
		return -1;
	}

	/* Initialize compressor and start processing data */
	(void)(*pdyn_jpeg_CreateCompress)(&comp, JPEGLIB_JPEG_LIB_VERSION,
	                                  JPEGLIB_SIZEOF_jpeg_compress_struct);
	(void)(*pdyn_jpeg_stdio_dest)(&comp, stream);
	minimal_jpeg_compress_struct__set_image_width(&comp, self->vb_size_x);
	minimal_jpeg_compress_struct__set_image_height(&comp, self->vb_size_y);
	minimal_jpeg_compress_struct__set_input_components(&comp, comp_input_components);
	minimal_jpeg_compress_struct__set_in_color_space(&comp, comp_in_color_space);
	(void)(*pdyn_jpeg_set_defaults)(&comp);

	/* "quality" is a parameter between 0 (terrible) and 100 (very good)
	 * TODO: Read this parameter from "options" */
	(void)(*pdyn_jpeg_set_quality)(&comp, 50, 1 /* limit to baseline-JPEG values */);

	/* Start compression */
	(void)(*pdyn_jpeg_start_compress)(&comp, 1);

	/* Acquire a lock to video memory */
	if unlikely(video_buffer_rlock(self, &vid_lock) != 0)
		goto err_errno;

	for (;;) {
		JPEGLIB_JSAMPROW scanline;
		JPEGLIB_JSAMPARRAY scanlines;
		JPEGLIB_JDIMENSION want_y;
		want_y = minimal_jpeg_compress_struct__get_next_scanline(&comp);
		if (want_y >= minimal_jpeg_compress_struct__get_image_height(&comp))
			break;
		scanline = vid_lock.vl_data + want_y * vid_lock.vl_stride;
		scanlines = &scanline;
		(void)(*pdyn_jpeg_write_scanlines)(&comp, scanlines, 1);
	}

	/* Cleanup... */
	(void)(*pdyn_jpeg_finish_compress)(&comp);
	(void)(*pdyn_jpeg_destroy_compress)(&comp);

	/* Release video lock and indicate success */
	video_buffer_unlock(self, &vid_lock);
	return 0;
	{
		int saved_errno;
err_errno:
		saved_errno = errno;
		(void)(*pdyn_jpeg_destroy_compress)(&comp);
		errno = saved_errno;
	}
	return -1;
}

/* If the header is installed, verify that our size constants are correct */
#if !defined(HAVE_dump_jpeglib_config) && __has_include(<jpeglib.h>)
DECL_END
#include <jpeglib.h>
DECL_BEGIN

static_assert((int)JCS_GRAYSCALE == JPEGLIB_JCS_GRAYSCALE);
static_assert((int)JCS_RGB == JPEGLIB_JCS_RGB);
static_assert(JPEG_LIB_VERSION == JPEGLIB_JPEG_LIB_VERSION);
static_assert(sizeof(struct jpeg_error_mgr) <= JPEGLIB_SIZEOF_jpeg_error_mgr);
static_assert(offsetof(struct jpeg_error_mgr, error_exit) == JPEGLIB_OFFSETOF_jpeg_error_mgr__error_exit);
static_assert(sizeof(struct jpeg_compress_struct) == JPEGLIB_SIZEOF_jpeg_compress_struct);
static_assert(alignof(struct jpeg_compress_struct) <= JPEGLIB_ALIGNOF_jpeg_compress_struct);
static_assert(offsetof(struct jpeg_compress_struct, image_width) == JPEGLIB_OFFSETOF_jpeg_compress_struct__image_width);
static_assert(offsetof(struct jpeg_compress_struct, image_height) == JPEGLIB_OFFSETOF_jpeg_compress_struct__image_height);
static_assert(offsetof(struct jpeg_compress_struct, input_components) == JPEGLIB_OFFSETOF_jpeg_compress_struct__input_components);
static_assert(offsetof(struct jpeg_compress_struct, in_color_space) == JPEGLIB_OFFSETOF_jpeg_compress_struct__in_color_space);
static_assert(offsetof(struct jpeg_compress_struct, next_scanline) == JPEGLIB_OFFSETOF_jpeg_compress_struct__next_scanline);
static_assert(offsetof(struct jpeg_compress_struct, err) == JPEGLIB_OFFSETOF_jpeg_common_struct__err);
static_assert(sizeof(struct jpeg_decompress_struct) == JPEGLIB_SIZEOF_jpeg_decompress_struct);
static_assert(alignof(struct jpeg_decompress_struct) <= JPEGLIB_ALIGNOF_jpeg_decompress_struct);
static_assert(offsetof(struct jpeg_decompress_struct, err) == JPEGLIB_OFFSETOF_jpeg_common_struct__err);
static_assert(offsetof(struct jpeg_decompress_struct, out_color_space) == JPEGLIB_OFFSETOF_jpeg_decompress_struct__out_color_space);
static_assert(offsetof(struct jpeg_decompress_struct, output_width) == JPEGLIB_OFFSETOF_jpeg_decompress_struct__output_width);
static_assert(offsetof(struct jpeg_decompress_struct, output_height) == JPEGLIB_OFFSETOF_jpeg_decompress_struct__output_height);
static_assert(offsetof(struct jpeg_decompress_struct, output_scanline) == JPEGLIB_OFFSETOF_jpeg_decompress_struct__output_scanline);
static_assert(offsetof(struct jpeg_decompress_struct, output_components) == JPEGLIB_OFFSETOF_jpeg_decompress_struct__output_components);
#endif /* !HAVE_dump_jpeglib_config && __has_include(<jpeglib.h>) */







/************************************************************************/
/* BMP                                                                  */
/************************************************************************/

PRIVATE ATTR_NOINLINE WUNUSED REF struct video_buffer *CC
libvideo_buffer_open_bmp(void const *blob, size_t blob_size) {
	/* TODO */
	(void)blob;
	(void)blob_size;
	return VIDEO_BUFFER_WRONG_FMT;
}

PRIVATE ATTR_NOINLINE WUNUSED NONNULL((1, 2)) int CC
libvideo_buffer_save_bmp(struct video_buffer *__restrict self,
                         FILE *stream, char const *options) {
	(void)self;
	(void)stream;
	(void)options;
	errno = ENOSYS; /* TODO */
	return -1;
}


/************************************************************************/
/* COMMON                                                               */
/************************************************************************/

enum fmt {
	FMT_BAD,
#define FMT_FIRST FMT_PNG
	FMT_PNG,
	FMT_JPG,
	FMT_BMP,
#define FMT_LAST FMT_BMP
};

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) enum fmt CC
detect_format(char const *name) {
	if (strcasecmp(name, "png") == 0)
		return FMT_PNG;
	if (strcasecmp(name, "jpg") == 0 ||
	    strcasecmp(name, "jpeg") == 0)
		return FMT_JPG;
	if (strcasecmp(name, "bmp") == 0)
		return FMT_BMP;
	return FMT_BAD;
}

PRIVATE ATTR_NOINLINE WUNUSED REF struct video_buffer *CC
libvideo_buffer_open_fmt(void const *blob, size_t blob_size, enum fmt fmt) {
	switch (fmt) {
	case FMT_BAD:
		break;
	case FMT_PNG:
		return libvideo_buffer_open_png(blob, blob_size);
	case FMT_JPG:
		return libvideo_buffer_open_jpg(blob, blob_size);
	case FMT_BMP:
		return libvideo_buffer_open_bmp(blob, blob_size);
	default: __builtin_unreachable();
	}
	errno = ENOTSUP;
	return NULL;
}

PRIVATE ATTR_NOINLINE WUNUSED NONNULL((1, 2)) int CC
libvideo_buffer_save_fmt(struct video_buffer *__restrict self,
                         FILE *stream, char const *options,
                         enum fmt fmt) {
	switch (fmt) {
	case FMT_BAD:
		break;
	case FMT_PNG:
		return libvideo_buffer_save_png(self, stream, options);
	case FMT_JPG:
		return libvideo_buffer_save_jpg(self, stream, options);
	case FMT_BMP:
		return libvideo_buffer_save_bmp(self, stream, options);
	default: __builtin_unreachable();
	}
	errno = ENOTSUP;
	return -1;
}



PRIVATE ATTR_NOINLINE WUNUSED REF struct video_buffer *CC
libvideo_buffer_open_impl(void const *blob, size_t blob_size,
                          char const *format_hint) {
	REF struct video_buffer *result;
	enum fmt used_format, hinted_format = FMT_BAD;
	if (format_hint != NULL) {
		hinted_format = detect_format(format_hint);
		if (hinted_format != FMT_BAD) {
			result = libvideo_buffer_open_fmt(blob, blob_size, hinted_format);
			if (result != VIDEO_BUFFER_WRONG_FMT)
				return result;
		}
	}
	for (used_format = FMT_FIRST;
	     (unsigned int)used_format <= (unsigned int)FMT_LAST;
	     used_format = (enum fmt)((unsigned int)used_format + 1)) {
		result = libvideo_buffer_open_fmt(blob, blob_size, used_format);
		if (result != VIDEO_BUFFER_WRONG_FMT)
			return result;
	}
	/* Unsupported file format, or not an image file */
	errno = ENOTSUP;
	return NULL;
}

PRIVATE ATTR_NOINLINE WUNUSED NONNULL((1, 2, 3)) int CC
libvideo_buffer_save_impl(struct video_buffer *__restrict self,
                          char const *format,
                          FILE *stream, char const *options) {
	enum fmt used_format = detect_format(format);
	return libvideo_buffer_save_fmt(self, stream, options, used_format);
}



/* Various functions  for opening  a file/stream/blob  as an  image  file.
 * The actual file format is  auto-detected, and supported formats  depend
 * on installed 3rd party libraries. By default, BMP and PNG is supported. */
DEFINE_PUBLIC_ALIAS(video_buffer_mopen, libvideo_buffer_mopen);
INTERN WUNUSED REF struct video_buffer *CC
libvideo_buffer_mopen(void const *blob, size_t blob_size) {
	return libvideo_buffer_open_impl(blob, blob_size, NULL);
}

DEFINE_PUBLIC_ALIAS(video_buffer_fopen, libvideo_buffer_fopen);
INTERN WUNUSED REF struct video_buffer *CC
libvideo_buffer_fopen(FILE *__restrict fp) {
	/* TODO: Allow use of `FILE' with mapfile */
	(void)fp;
	errno = ENOSYS;
	return NULL;
}

DEFINE_PUBLIC_ALIAS(video_buffer_fdopen, libvideo_buffer_fdopen);
INTERN WUNUSED REF struct video_buffer *CC
libvideo_buffer_fdopen(fd_t fd) {
	struct mapfile mf;
	REF struct video_buffer *result;
	if (fmapfile(&mf, fd, 0, 0,
	             (size_t)-1, 0, 0))
		return NULL;
	result = libvideo_buffer_open_impl(mf.mf_addr, mf.mf_size, NULL);
	(void)unmapfile(&mf);
	return result;
}

DEFINE_PUBLIC_ALIAS(video_buffer_open, libvideo_buffer_open);
INTERN WUNUSED REF struct video_buffer *CC
libvideo_buffer_open(char const *filename) {
	struct mapfile mf;
	char const *format_hint;
	REF struct video_buffer *result;
	if (mapfile(&mf, filename, 0, 0,
	            (size_t)-1, 0, 0))
		return NULL;
	format_hint = strrchr(filename, '.');
	if (format_hint)
		++format_hint;
	result = libvideo_buffer_open_impl(mf.mf_addr, mf.mf_size, format_hint);
	(void)unmapfile(&mf);
	return result;
}



/* Do the inverse of `video_buffer_*open' and save the contents of a video buffer
 * into  a file/memory/stream. The same set of  file formats is supported as also
 * supported by `video_buffer_*open', and the intended file format is  determined
 * by the given `format' argument, which should be the case-insensitive extension
 * (without a leading ".") of the format (e.g. "png" for PNG files).
 * @param: self:     The video buffer to save to a file.
 * @param: format:   The format to use for the output file written.
 * @param: fp/fd:    Output file descriptor / stdio-stream
 * @param: filename: Output filename ("format" is detected from file extension)
 * @param: options:  ","-separated string of format-specific encoding  options.
 *                   Available options are not explicitly document here, so you
 *                   need  to look at  the source to see  what's there. You may
 *                   simply pass `NULL' to use defaults for everything.
 * @return: 0 : Success
 * @return: -1: [errno=ENOTSUP] Unsupported `format'
 * @return: -1: [errno=ENOTSUP] Unsupported parameter in `options'
 * @return: -1: Error (s.a. `errno') */
DEFINE_PUBLIC_ALIAS(video_buffer_fsave, libvideo_buffer_fsave);
INTERN WUNUSED NONNULL((1, 2)) int CC
libvideo_buffer_fsave(struct video_buffer *self, char const *format,
                      FILE *__restrict fp, char const *options) {
	return libvideo_buffer_save_impl(self, format, fp, options);
}

DEFINE_PUBLIC_ALIAS(video_buffer_fdsave, libvideo_buffer_fdsave);
INTERN WUNUSED NONNULL((1, 2)) int CC
libvideo_buffer_fdsave(struct video_buffer *self, char const *format,
                       fd_t fd, char const *options) {
	int result;
	FILE *stream = fdopen(fd, "wb");
	if unlikely(!stream)
		return -1;
	unlock_stream(stream);
	result = libvideo_buffer_save_impl(self, format, stream, options);
	(void)frelease(stream);
	(void)fclose(stream);
	return result;
}

DEFINE_PUBLIC_ALIAS(video_buffer_save, libvideo_buffer_save);
INTERN /*WUNUSED*/ NONNULL((1, 2)) int CC
libvideo_buffer_save(struct video_buffer *self,
                     char const *filename,
                     char const *options) {
	int result;
	char const *format;
	FILE *stream;
	format = strrchr(filename, '.');
	if unlikely(!format) {
		errno = EINVAL; /* Missing file extension */
		return -1;
	}
	++format;
	stream = fopen(filename, "wb");
	if unlikely(!stream)
		return -1;
	unlock_stream(stream);
	result = libvideo_buffer_save_impl(self, format, stream, options);
	(void)fclose(stream);
	if (result != 0) /* Delete broken file on error. */
		(void)unlink(filename);
	return result;
}



DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_IO_C */
