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
#ifndef GUARD_LIBVIDEO_GFX_IO_JPG_C_INL
#define GUARD_LIBVIDEO_GFX_IO_JPG_C_INL 1
#define LIBVIDEO_GFX_EXPOSE_INTERNALS
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <kos/types.h>
#include <sys/syslog.h>

#include <assert.h>
#include <dlfcn.h>
#include <errno.h>
#include <pthread.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include <libvideo/codec/codecs.h>
#include <libvideo/gfx/buffer.h>
/**/

#include "../buffer.h"
#include "../io-utils.h"

/**/

DECL_BEGIN

#undef UINT8
#undef UINT8
#undef UINT16
#undef INT16
#undef INT32
#undef noreturn_t
#undef boolean
#define UINT8      _JPEGLIB_UINT8
#define UINT8      _JPEGLIB_UINT8
#define UINT16     _JPEGLIB_UINT16
#define INT16      _JPEGLIB_INT16
#define INT32      _JPEGLIB_INT32
#define noreturn_t _JPEGLIB_noreturn_t
#define boolean    _JPEGLIB_boolean


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
#include <kos/anno.h>
#include <libvideo/codec/codecs.h>
#include "../buffer.h"
#include <bits/crt/mapfile.h>
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


#define DEFINE_JPEGLIB_API(Treturn, name, params) \
	typedef Treturn(*P##name) params;             \
	PRIVATE P##name pdyn_##name = NULL
/* Common */
DEFINE_JPEGLIB_API(struct minimal_jpeg_error_mgr *, jpeg_std_error, (struct minimal_jpeg_error_mgr *err));
/* Decompress */
DEFINE_JPEGLIB_API(void, jpeg_CreateDecompress, (struct minimal_jpeg_decompress_struct *cinfo, int version, size_t structsize));
DEFINE_JPEGLIB_API(void, jpeg_mem_src, (struct minimal_jpeg_decompress_struct *cinfo, byte_t const *inbuffer, size_t insize));
DEFINE_JPEGLIB_API(int, jpeg_read_header, (struct minimal_jpeg_decompress_struct *cinfo, JPEGLIB_boolean require_image));
DEFINE_JPEGLIB_API(JPEGLIB_boolean, jpeg_start_decompress, (struct minimal_jpeg_decompress_struct *cinfo));
DEFINE_JPEGLIB_API(JPEGLIB_JDIMENSION, jpeg_read_scanlines, (struct minimal_jpeg_decompress_struct *cinfo, JPEGLIB_JSAMPARRAY scanlines, JPEGLIB_JDIMENSION max_lines));
DEFINE_JPEGLIB_API(JPEGLIB_boolean, jpeg_finish_decompress, (struct minimal_jpeg_decompress_struct *cinfo));
DEFINE_JPEGLIB_API(void, jpeg_destroy_decompress, (struct minimal_jpeg_decompress_struct *cinfo));
/* Compress */
DEFINE_JPEGLIB_API(void, jpeg_CreateCompress, (struct minimal_jpeg_compress_struct *cinfo, int version, size_t structsize));
DEFINE_JPEGLIB_API(void, jpeg_stdio_dest, (struct minimal_jpeg_compress_struct *cinfo, FILE *outfile));
DEFINE_JPEGLIB_API(void, jpeg_set_defaults, (struct minimal_jpeg_compress_struct *cinfo));
DEFINE_JPEGLIB_API(void, jpeg_set_quality, (struct minimal_jpeg_compress_struct *cinfo, int quality, JPEGLIB_boolean force_baseline));
DEFINE_JPEGLIB_API(void, jpeg_start_compress, (struct minimal_jpeg_compress_struct *cinfo, JPEGLIB_boolean write_all_tables));
DEFINE_JPEGLIB_API(JPEGLIB_JDIMENSION, jpeg_write_scanlines, (struct minimal_jpeg_compress_struct *cinfo, JPEGLIB_JSAMPARRAY scanlines, JPEGLIB_JDIMENSION num_lines));
DEFINE_JPEGLIB_API(void, jpeg_finish_compress, (struct minimal_jpeg_compress_struct *cinfo));
DEFINE_JPEGLIB_API(void, jpeg_destroy_compress, (struct minimal_jpeg_compress_struct *cinfo));
#undef DEFINE_JPEGLIB_API


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
#undef LOADSYM2
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

INTERN ATTR_NOINLINE WUNUSED REF struct video_buffer *CC
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
	__builtin_assume(result_size_x == result->vb_xdim);
	__builtin_assume(result_size_y == result->vb_ydim);

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

INTERN ATTR_NOINLINE WUNUSED NONNULL((1, 2)) int CC
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

	case VIDEO_CODEC_L8:
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
		in_codec_id = (self->vb_format.vf_codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_LUM)
		           ? VIDEO_CODEC_L8
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
	minimal_jpeg_compress_struct__set_image_width(&comp, self->vb_xdim);
	minimal_jpeg_compress_struct__set_image_height(&comp, self->vb_ydim);
	minimal_jpeg_compress_struct__set_input_components(&comp, comp_input_components);
	minimal_jpeg_compress_struct__set_in_color_space(&comp, comp_in_color_space);
	(void)(*pdyn_jpeg_set_defaults)(&comp);

	/* "quality" is a parameter between 0 (terrible) and 100 (very good) */
	{
		int qual = (int)libvideo_io_getoptl(options, "quality", 50);
		if (qual < 0)
			qual = 0;
		if (qual > 100)
			qual = 100;
		(void)(*pdyn_jpeg_set_quality)(&comp, qual, 1 /* limit to baseline-JPEG values */);
	}

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

#undef UINT8
#undef UINT8
#undef UINT16
#undef INT16
#undef INT32
#undef noreturn_t
#undef boolean

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_IO_JPG_C_INL */
