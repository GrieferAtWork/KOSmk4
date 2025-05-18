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
#define _KOS_SOURCE 1

#include "api.h"

#include <hybrid/compiler.h>

#include <hybrid/align.h>
#include <hybrid/minmax.h>

#include <kos/types.h>
#include <sys/mman.h>

#include <errno.h>
#include <malloc.h>
#include <stdbool.h>
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
		(*rgb_buffer->vb_ops->vi_getgfx)(rgb_buffer, &dst_gfx, GFX_BLENDINFO_OVERRIDE, VIDEO_GFX_FNORMAL, 0, NULL);
		(*self->vb_ops->vi_getgfx)(self, &src_gfx, GFX_BLENDINFO_OVERRIDE, VIDEO_GFX_FNORMAL, 0, NULL);
		(*dst_gfx.vx_ops->fxo_blit)(&dst_gfx, 0, 0, &src_gfx, 0, 0, self->vb_size_x, self->vb_size_y);
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

	result = (*self->vb_ops->vi_lock)(self, &lock);
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

PRIVATE ATTR_NOINLINE WUNUSED REF struct video_buffer *CC
libvideo_buffer_open_jpg(void const *blob, size_t blob_size) {
	/* TODO */
	(void)blob;
	(void)blob_size;
	return VIDEO_BUFFER_WRONG_FMT;
}

PRIVATE ATTR_NOINLINE WUNUSED NONNULL((1, 2)) int CC
libvideo_buffer_save_jpg(struct video_buffer *__restrict self,
                         FILE *stream, char const *options) {
	(void)self;
	(void)stream;
	(void)options;
	errno = ENOSYS; /* TODO */
	return -1;
}



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
INTERN WUNUSED NONNULL((1, 2)) int CC
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
