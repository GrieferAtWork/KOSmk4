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
#ifndef GUARD_LIBVIDEO_GFX_IO_PNG_C_INL
#define GUARD_LIBVIDEO_GFX_IO_PNG_C_INL 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/typecore.h>

#include <kos/anno.h>
#include <kos/types.h>
#include <sys/syslog.h>

#include <dlfcn.h>
#include <errno.h>
#include <pthread.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libvideo/color.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/codec/codec.h>
#include <libvideo/gfx/codec/palette.h>

#include "../codec/codec.h"
#include "../codec/palette.h"
#include "../io-utils.h"
#include "../ramdomain.h"

DECL_BEGIN

#ifndef LIBPNGCAPI
#define LIBPNGCAPI
#endif /* !LIBPNGCAPI */
#ifndef LIBPNGCBAPI
#define LIBPNGCBAPI LIBPNGCAPI
#endif /* !LIBPNGCBAPI */
#ifndef LIBPNGAPI
#define LIBPNGAPI LIBPNGCAPI
#endif
#define LIBPNG_CALLBACK(type, name, args) type(LIBPNGCBAPI name) args

#ifndef LIBPNG_LIBPNG_VER_STRING
#define LIBPNG_LIBPNG_VER_STRING "1.6.49"
#endif /* !LIBPNG_LIBPNG_VER_STRING */

#define LIBPNG_INFO_tRNS 0x0010U

#define LIBPNG_COLOR_MASK_PALETTE    1
#define LIBPNG_COLOR_MASK_COLOR      2
#define LIBPNG_COLOR_MASK_ALPHA      4
#define LIBPNG_COLOR_TYPE_GRAY       0
#define LIBPNG_COLOR_TYPE_PALETTE    (LIBPNG_COLOR_MASK_COLOR | LIBPNG_COLOR_MASK_PALETTE)
#define LIBPNG_COLOR_TYPE_RGB        (LIBPNG_COLOR_MASK_COLOR)
#define LIBPNG_COLOR_TYPE_RGB_ALPHA  (LIBPNG_COLOR_MASK_COLOR | LIBPNG_COLOR_MASK_ALPHA)
#define LIBPNG_COLOR_TYPE_GRAY_ALPHA (LIBPNG_COLOR_MASK_ALPHA)
#define LIBPNG_COLOR_TYPE_RGBA       LIBPNG_COLOR_TYPE_RGB_ALPHA
#define LIBPNG_COLOR_TYPE_GA         LIBPNG_COLOR_TYPE_GRAY_ALPHA


typedef __UINT32_TYPE__ libpng_uint_32;
typedef struct libpng_struct_def libpng_struct;
typedef libpng_struct const *libpng_const_structp;
typedef libpng_struct *libpng_structp;
typedef libpng_struct **libpng_structpp;
typedef char const *libpng_const_charp;
typedef libpng_struct *__restrict libpng_structrp;
typedef libpng_struct const *__restrict libpng_const_structrp;
typedef void (LIBPNGCBAPI *libpng_error_ptr)(libpng_structp, libpng_const_charp);
typedef void *libpng_voidp;
typedef struct libpng_info_def libpng_info;
typedef libpng_info *libpng_infop;
typedef libpng_info const *libpng_const_infop;
typedef libpng_info **libpng_infopp;
typedef libpng_info *__restrict libpng_inforp;
typedef libpng_info const *__restrict libpng_const_inforp;
typedef void (LIBPNGCAPI *libpng_longjmp_ptr)(jmp_buf, int);
typedef byte_t libpng_byte;
typedef libpng_byte *libpng_bytep;
typedef LIBPNG_CALLBACK(void, *libpng_rw_ptr, (libpng_structp, libpng_bytep, size_t));

typedef struct libpng_color_struct {
	libpng_byte red;
	libpng_byte green;
	libpng_byte blue;
} libpng_color;
typedef libpng_color *libpng_colorp;
typedef libpng_color const *libpng_const_colorp;
typedef libpng_color **libpng_colorpp;




#define DEFINE_LIBPNG_API(Treturn, name, params) \
	typedef Treturn(LIBPNGAPI *P##name) params;            \
	PRIVATE P##name pdyn_##name = NULL
/* "libpng_image"  doesn't offer access  to the *true* bitdepth  of the image. As
 * such, don't use the "simplified" API, and instead use "png_create_read_struct" */
DEFINE_LIBPNG_API(libpng_structp, png_create_read_struct, (libpng_const_charp user_png_ver, libpng_voidp error_ptr, libpng_error_ptr error_fn, libpng_error_ptr warn_fn));
DEFINE_LIBPNG_API(libpng_infop, png_create_info_struct, (libpng_const_structrp png_ptr));
DEFINE_LIBPNG_API(void, png_destroy_read_struct, (libpng_structpp png_ptr_ptr, libpng_infopp info_ptr_ptr, libpng_infopp end_info_ptr_ptr));
DEFINE_LIBPNG_API(jmp_buf *, png_set_longjmp_fn, (libpng_structrp png_ptr, libpng_longjmp_ptr longjmp_fn, size_t jmp_buf_size));
DEFINE_LIBPNG_API(void, png_set_read_fn, (libpng_structrp png_ptr, libpng_voidp io_ptr, libpng_rw_ptr read_data_fn));
DEFINE_LIBPNG_API(libpng_voidp, png_get_io_ptr, (libpng_const_structrp png_ptr));
DEFINE_LIBPNG_API(ATTR_NORETURN_T void, png_error, (libpng_const_structrp png_ptr, libpng_const_charp error_message));
DEFINE_LIBPNG_API(void, png_read_info, (libpng_structrp png_ptr, libpng_inforp info_ptr));
DEFINE_LIBPNG_API(libpng_uint_32, png_get_IHDR, (libpng_const_structrp png_ptr, libpng_const_inforp info_ptr, libpng_uint_32 *width, libpng_uint_32 *height, int *bit_depth, int *color_type, int *interlace_method, int *compression_method, int *filter_method));
DEFINE_LIBPNG_API(void, png_set_scale_16, (libpng_structrp png_ptr));
DEFINE_LIBPNG_API(void, png_set_packing, (libpng_structrp png_ptr));
DEFINE_LIBPNG_API(libpng_uint_32, png_get_valid, (libpng_const_structrp png_ptr, libpng_const_inforp info_ptr, libpng_uint_32 flag));
DEFINE_LIBPNG_API(void, png_set_tRNS_to_alpha, (libpng_structrp png_ptr));
DEFINE_LIBPNG_API(void, png_set_palette_to_rgb, (libpng_structrp png_ptr));
DEFINE_LIBPNG_API(void, png_set_gray_to_rgb, (libpng_structrp png_ptr));
DEFINE_LIBPNG_API(size_t, png_get_rowbytes, (libpng_const_structrp png_ptr, libpng_const_inforp info_ptr));
DEFINE_LIBPNG_API(libpng_uint_32, png_get_PLTE, (libpng_const_structrp png_ptr, libpng_inforp info_ptr, libpng_colorp *palette, int *num_palette));
//DEFINE_LIBPNG_API(void, png_read_end, (libpng_structrp png_ptr, libpng_inforp info_ptr));
DEFINE_LIBPNG_API(int, png_set_interlace_handling, (libpng_structrp png_ptr));
DEFINE_LIBPNG_API(void, png_read_row, (libpng_structrp png_ptr, libpng_bytep row, libpng_bytep display_row));
#undef DEFINE_LIBPNG_API

PRIVATE void __LIBCCALL libpng_loadapi_impl(void) {
	void *libpng_so = dlopen("libpng16.so.16", RTLD_LOCAL);
	if unlikely(!libpng_so)
		return;
#define LOADSYM(name)                                               \
	if ((*(void **)&pdyn_##name = dlsym(libpng_so, #name)) == NULL) \
		goto fail
#define LOADSYM2(name, name2)                                         \
	if ((*(void **)&pdyn_##name = dlsym(libpng_so, #name)) == NULL && \
	    (*(void **)&pdyn_##name = dlsym(libpng_so, #name2)) == NULL)  \
		goto fail
	LOADSYM(png_create_info_struct);
	LOADSYM(png_destroy_read_struct);
	LOADSYM(png_set_longjmp_fn);
	LOADSYM(png_set_read_fn);
	LOADSYM(png_get_io_ptr);
	LOADSYM(png_error);
	LOADSYM(png_read_info);
	LOADSYM(png_get_IHDR);
	LOADSYM2(png_set_scale_16, png_set_strip_16);
	LOADSYM(png_set_packing);
	LOADSYM(png_get_valid);
	LOADSYM(png_set_tRNS_to_alpha);
	LOADSYM(png_set_palette_to_rgb);
	LOADSYM(png_set_gray_to_rgb);
	LOADSYM(png_get_rowbytes);
	LOADSYM(png_get_PLTE);
//	LOADSYM(png_read_end);
	LOADSYM(png_set_interlace_handling);
	LOADSYM(png_read_row);
	COMPILER_WRITE_BARRIER();
	LOADSYM(png_create_read_struct);
#undef LOADSYM
#undef LOADSYM2
	return;
fail:
	syslog(LOG_WARN, "[libvideo-gfx][libpng] Failed to load API: %s\n", dlerror());
	dlclose(libpng_so);
	pdyn_png_create_read_struct = NULL;
}

PRIVATE pthread_once_t libpng_loadapi_done = PTHREAD_ONCE_INIT;
PRIVATE bool CC libpng_loadapi(void) {
	pthread_once(&libpng_loadapi_done,
	             &libpng_loadapi_impl);
	return pdyn_png_create_read_struct != NULL;
}

struct libpng_mem_reader_data {
	byte_t const *mrd_ptr; /* Pointer to remaining data */
	size_t        mrd_rem; /* # of remaining bytes */
};

PRIVATE void LIBPNGCBAPI
libpng_mem_reader_cb(libpng_structp png_ptr, libpng_bytep p, size_t n) {
	struct libpng_mem_reader_data *data;
	data = (struct libpng_mem_reader_data *)(*pdyn_png_get_io_ptr)(png_ptr);
	if (n > data->mrd_rem) {
		(*pdyn_png_error)(png_ptr, "read beyond end of data");
		abort();
	}
	memcpy(p, data->mrd_ptr, n);
	data->mrd_ptr += n;
	data->mrd_rem -= n;
}


INTERN WUNUSED NONNULL((1)) REF struct video_buffer *CC
libvideo_buffer_open_png(struct video_domain const *__restrict domain_hint,
                         void const *blob, size_t blob_size) {
	libpng_structp png_ptr;
	libpng_infop info_ptr;
	struct libpng_mem_reader_data rdat;
	libpng_uint_32 width, height;
	int bit_depth, color_type;
	video_codec_t result_codec_id;

	/* Shared with setjmp() target */
	struct video_buffer_format result_format;
	REF struct video_buffer *result;
	struct video_lock result_lock;
	byte_t *temp_line;

	if (!libpng_loadapi())
		return libvideo_buffer_open_lodepng(domain_hint, blob, blob_size);
	png_ptr = (*pdyn_png_create_read_struct)(LIBPNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if unlikely(!png_ptr)
		goto err_nomem;
	info_ptr = (*pdyn_png_create_info_struct)(png_ptr);
	if unlikely(!info_ptr)
		goto err_nomem_png_ptr;
	result                = NULL;
	result_format.vbf_pal = NULL;
	result_lock.vl_data   = NULL;
	temp_line             = NULL;
	if (setjmp(*(*pdyn_png_set_longjmp_fn)(png_ptr, &longjmp, sizeof(jmp_buf)))) {
		if (temp_line)
			free(temp_line);
		if (result_lock.vl_data)
			video_buffer_unlock(result, &result_lock);
		if (result)
			video_buffer_decref(result);
		if (result_format.vbf_pal)
			video_palette_decref(result_format.vbf_pal);
		(*pdyn_png_destroy_read_struct)(&png_ptr, &info_ptr, NULL);
		return VIDEO_BUFFER_WRONG_FMT;
	}

	/* Setup I/O */
	rdat.mrd_ptr = (byte_t const *)blob;
	rdat.mrd_rem = blob_size;
	(*pdyn_png_set_read_fn)(png_ptr, &rdat, &libpng_mem_reader_cb);

	/* Reader header */
	(*pdyn_png_read_info)(png_ptr, info_ptr);

	/* Reader image info */
	(*pdyn_png_get_IHDR)(png_ptr, info_ptr,
	                     &width, &height, &bit_depth,
	                     &color_type, NULL, NULL, NULL);

	/* Configure image transformation */
	if (bit_depth > 8) {
		(*pdyn_png_set_scale_16)(png_ptr); /* Scale down to at most 8-bit-per-channel */
		bit_depth = 8;
	}

	/* If a stand-alone alpha channel is present, include it in the result */
	if ((*pdyn_png_get_valid)(png_ptr, info_ptr, LIBPNG_INFO_tRNS) != 0) {
		(*pdyn_png_set_tRNS_to_alpha)(png_ptr);
		color_type |= LIBPNG_COLOR_MASK_ALPHA;
	}

	if (color_type & LIBPNG_COLOR_MASK_PALETTE) {
		libpng_colorp png_palette;
		int png_num_palette;
		unsigned int pal_i;

		/* Palette-driven */
		/*png_set_packswap(png_ptr);*/ /* If we called this, below would become *_LSB */
		if (color_type & LIBPNG_COLOR_MASK_ALPHA) {
			switch (bit_depth) {
			case 1: result_codec_id = VIDEO_CODEC_PA11_MSB; break;
			case 2: result_codec_id = VIDEO_CODEC_PA22_MSB; break;
			case 4: result_codec_id = VIDEO_CODEC_PA44; break;
			default: (*pdyn_png_set_packing)(png_ptr); ATTR_FALLTHROUGH
			case 8: result_codec_id = VIDEO_CODEC_PA88; break;
			}
		} else {
			switch (bit_depth) {
			case 1: result_codec_id = VIDEO_CODEC_P1_MSB; break;
			case 2: result_codec_id = VIDEO_CODEC_P2_MSB; break;
			case 4: result_codec_id = VIDEO_CODEC_P4_MSB; break;
			default: (*pdyn_png_set_packing)(png_ptr); ATTR_FALLTHROUGH
			case 8: result_codec_id = VIDEO_CODEC_P8; break;
			}
		}

		/* Read palette colors */
		if ((*pdyn_png_get_PLTE)(png_ptr, info_ptr, &png_palette, &png_num_palette) == 0) {
			(*pdyn_png_set_palette_to_rgb)(png_ptr);
			goto do_rgb_format;
		}

		/* Construct palette */
		result_format.vbf_pal = libvideo_palette_create((unsigned int)png_num_palette);
		if unlikely(!result_format.vbf_pal)
			goto err_png_ptr_info_ptr;
		for (pal_i = 0; pal_i < (unsigned int)png_num_palette; ++pal_i) {
			video_color_t color = VIDEO_COLOR_RGB(png_palette[pal_i].red,
			                                      png_palette[pal_i].green,
			                                      png_palette[pal_i].blue);
			result_format.vbf_pal->vp_pal[pal_i] = color;
		}
		result_format.vbf_pal = libvideo_palette_optimize(result_format.vbf_pal);
	} else if (!(color_type & LIBPNG_COLOR_MASK_COLOR)) {
		/* Grayscale (aka. luminance) */
		/*png_set_packswap(png_ptr);*/ /* If we called this, below would become *_LSB */
		if (color_type & LIBPNG_COLOR_MASK_ALPHA) {
			switch (bit_depth) {
			case 1: result_codec_id = VIDEO_CODEC_LA11_MSB; break;
			case 2: result_codec_id = VIDEO_CODEC_LA22_MSB; break;
			case 4: result_codec_id = VIDEO_CODEC_LA44; break;
			default: (*pdyn_png_set_packing)(png_ptr); ATTR_FALLTHROUGH
			case 8: result_codec_id = VIDEO_CODEC_LA88; break;
			}
		} else {
			switch (bit_depth) {
			case 1: result_codec_id = VIDEO_CODEC_L1_MSB; break;
			case 2: result_codec_id = VIDEO_CODEC_L2_MSB; break;
			case 4: result_codec_id = VIDEO_CODEC_L4_MSB; break;
			default: (*pdyn_png_set_packing)(png_ptr); ATTR_FALLTHROUGH
			case 8: result_codec_id = VIDEO_CODEC_L8; break;
			}
		}
	} else {
do_rgb_format:
		switch (bit_depth) {
		case 4:
			if (color_type & LIBPNG_COLOR_MASK_ALPHA) {
				result_codec_id = VIDEO_CODEC_RGBA4444;
				break;
			}
			ATTR_FALLTHROUGH
		default:
			(*pdyn_png_set_packing)(png_ptr);
			ATTR_FALLTHROUGH
		case 8:
			if (color_type & LIBPNG_COLOR_MASK_ALPHA) {
				result_codec_id = VIDEO_CODEC_RGBA8888;
			} else {
				result_codec_id = VIDEO_CODEC_RGB888;
			}
			break;
		}
	}

	/* Lookup needed codec. */
	result_format.vbf_codec = libvideo_codec_lookup(result_codec_id);
	assertf(result_format.vbf_codec, "Built-in codec should have been recognized");

	/* Allocate result video buffer. */
	result_format.vbf_flags = VIDEO_GFX_F_NORMAL;
	result = video_domain_newbuffer(domain_hint, &result_format,
	                                width, height, VIDEO_DOMAIN_NEWBUFFER_F_NORMAL);
	if unlikely(!result) {
		if (errno != ENOTSUP && domain_hint != &libvideo_ramdomain)
			goto err_png_ptr_info_ptr_pal;
		result = video_domain_newbuffer(_libvideo_ramdomain(), &result_format,
		                                width, height, VIDEO_DOMAIN_NEWBUFFER_F_NORMAL);
		if unlikely(!result)
			goto err_png_ptr_info_ptr_pal;
	}
	if unlikely(video_buffer_wlock(result, &result_lock))
		goto err_png_ptr_info_ptr_pal_r;

	/* Read image data from PNG file */
	{
		/* Don't go below whatever scanline requirements libpng has */
		size_t libpng_scanline = (*pdyn_png_get_rowbytes)(png_ptr, info_ptr);
		int passes = (*pdyn_png_set_interlace_handling)(png_ptr);
		if likely(result_lock.vl_stride >= libpng_scanline) {
			int pass;
			for (pass = 0; pass < passes; ++pass) {
				byte_t *dst = result_lock.vl_data;
				libpng_uint_32 y;
				for (y = 0; y < height; ++y) {
					(*pdyn_png_read_row)(png_ptr, dst, NULL);
					dst += result_lock.vl_stride;
				}
			}
		} else {
			int pass;
			temp_line = (byte_t *)malloc(libpng_scanline);
			if unlikely(!temp_line)
				goto err_png_ptr_info_ptr_pal_r_lock;
			for (pass = 0; pass < passes; ++pass) {
				byte_t *dst = result_lock.vl_data;
				libpng_uint_32 y;
				for (y = 0; y < height; ++y) {
					(*pdyn_png_read_row)(png_ptr, temp_line, NULL);
					dst = (byte_t *)mempcpy(dst, temp_line, result_lock.vl_stride);
				}
			}
			free(temp_line);
		}
	}
	video_buffer_unlock(result, &result_lock);
	result_lock.vl_data = NULL;
	COMPILER_WRITE_BARRIER();

	/* Cleanup... */
//	(*pdyn_png_read_end)(png_ptr, info_ptr);
	(*pdyn_png_destroy_read_struct)(&png_ptr, &info_ptr, NULL);

	if (result_format.vbf_pal)
		video_palette_decref(result_format.vbf_pal);
	return result;
/*
err_png_ptr_info_ptr_pal_r_lock_temp_line:
	free(temp_line);*/
err_png_ptr_info_ptr_pal_r_lock:
	if (result_lock.vl_data)
		video_buffer_unlock(result, &result_lock);
err_png_ptr_info_ptr_pal_r:
	video_buffer_decref(result);
err_png_ptr_info_ptr_pal:
	if (result_format.vbf_pal)
		video_palette_decref(result_format.vbf_pal);
err_png_ptr_info_ptr:
	(*pdyn_png_destroy_read_struct)(&png_ptr, &info_ptr, NULL);
	return NULL;
err_png_ptr:
	(*pdyn_png_destroy_read_struct)(&png_ptr, NULL, NULL);
err:
	return NULL;
err_nomem_png_ptr:
	errno = ENOMEM;
	goto err_png_ptr;
err_nomem:
	errno = ENOMEM;
	goto err;
}

INTERN WUNUSED NONNULL((1, 2)) int CC
libvideo_surface_save_png(struct video_surface const *__restrict self,
                          FILE *stream, char const *options) {
	if (libpng_loadapi()) {
		/* TODO: Use libpng */
	}
	return libvideo_surface_save_lodepng(self, stream, options);
}




/* Assert that bindings above match those from the relevant 3rd party header. */
#if __has_include(<libpng/png.h>)
DECL_END
#include <libpng/png.h>
DECL_BEGIN

/* TODO */
#endif /* __has_include(<libpng/png.h>) */

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_IO_PNG_C_INL */
