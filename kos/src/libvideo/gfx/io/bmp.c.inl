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
#ifndef GUARD_LIBVIDEO_GFX_IO_BMP_C_INL
#define GUARD_LIBVIDEO_GFX_IO_BMP_C_INL 1
#define LIBVIDEO_GFX_EXPOSE_INTERNALS
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/align.h>
#include <hybrid/bit.h>
#include <hybrid/byteorder.h>
#include <hybrid/byteswap.h>
#include <hybrid/overflow.h>
#include <hybrid/unaligned.h>
#include <hybrid/wordbits.h>

#include <kos/anno.h>
#include <kos/types.h>
#include <nt/types.h>
#include <nt/wingdi.h>
#include <sys/mman.h>
#include <sys/param.h>
#include <sys/syslog.h>

#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <malloc.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <libvideo/codec/codecs.h>
#include <libvideo/codec/palette.h>
#include <libvideo/codec/pixel.h>
#include <libvideo/codec/types.h>
#include <libvideo/gfx/buffer.h>
/**/

#include "../io-utils.h"
#include "../buffer.h"
#include "../ram-buffer.h"

#ifndef BITSOF
#define BITSOF(x) (sizeof(x) * NBBY)
#endif /* !BITSOF */

DECL_BEGIN

/* BMP load/save based on:
 * - https://en.wikipedia.org/wiki/BMP_file_format
 */

struct bmpbuffer: video_rambuffer {
	REF struct video_codec_handle *bb_codec_handle; /* [1..1][const] Video codec handle */
};
struct bmpbuffer_with_mapfile: bmpbuffer {
	struct mapfile bbwm_map; /* [const] Mapfile that owns the pixel buffer */
};

PRIVATE NONNULL((1)) void FCC
bmpbuffer_destroy(struct video_buffer *__restrict self) {
	struct bmpbuffer *me = (struct bmpbuffer *)self;
	if (me->vb_format.vf_pal)
		video_palette_decref(me->vb_format.vf_pal);
	video_codec_handle_decref(me->bb_codec_handle);
	free(me->rb_data);
	free(me);
}

PRIVATE NONNULL((1)) void FCC
bmpbuffer_with_mapfile_destroy(struct video_buffer *__restrict self) {
	struct bmpbuffer_with_mapfile *me = (struct bmpbuffer_with_mapfile *)self;
	if (me->vb_format.vf_pal)
		video_palette_decref(me->vb_format.vf_pal);
	video_codec_handle_decref(me->bb_codec_handle);
	unmapfile(&me->bbwm_map);
	free(me);
}

#undef bmpbuffer_ops
#undef bmpbuffer_with_mapfile_ops
PRIVATE struct video_buffer_ops bmpbuffer_ops = {};
PRIVATE struct video_buffer_ops bmpbuffer_with_mapfile_ops = {};
PRIVATE ATTR_RETNONNULL WUNUSED struct video_buffer_ops *CC _bmpbuffer_ops(void) {
	if unlikely(!bmpbuffer_ops.vi_destroy) {
		bmpbuffer_ops.vi_rlock      = &rambuffer_rlock;
		bmpbuffer_ops.vi_wlock      = &rambuffer_wlock;
		bmpbuffer_ops.vi_unlock     = &rambuffer_unlock;
		bmpbuffer_ops.vi_initgfx    = &rambuffer_initgfx;
		bmpbuffer_ops.vi_updategfx  = &rambuffer_updategfx;
		bmpbuffer_ops.vi_noblendgfx = &rambuffer_noblend;
		COMPILER_WRITE_BARRIER();
		bmpbuffer_ops.vi_destroy = &bmpbuffer_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &bmpbuffer_ops;
}
PRIVATE ATTR_RETNONNULL WUNUSED struct video_buffer_ops *CC _bmpbuffer_with_mapfile_ops(void) {
	if unlikely(!bmpbuffer_with_mapfile_ops.vi_destroy) {
		bmpbuffer_with_mapfile_ops.vi_rlock      = &rambuffer_rlock;
		bmpbuffer_with_mapfile_ops.vi_wlock      = &rambuffer_wlock;
		bmpbuffer_with_mapfile_ops.vi_unlock     = &rambuffer_unlock;
		bmpbuffer_with_mapfile_ops.vi_initgfx    = &rambuffer_initgfx;
		bmpbuffer_with_mapfile_ops.vi_updategfx  = &rambuffer_updategfx;
		bmpbuffer_with_mapfile_ops.vi_noblendgfx = &rambuffer_noblend;
		COMPILER_WRITE_BARRIER();
		bmpbuffer_with_mapfile_ops.vi_destroy = &bmpbuffer_with_mapfile_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &bmpbuffer_with_mapfile_ops;
}
#define bmpbuffer_ops              (*_bmpbuffer_ops())
#define bmpbuffer_with_mapfile_ops (*_bmpbuffer_with_mapfile_ops())

PRIVATE NONNULL((1, 4, 5)) void CC
rle_decode(byte_t *dst, video_dim_t dst_scan, video_dim_t dst_resy,
           byte_t const *src, byte_t const *src_end, bool is_rle4) {
	/* "1 << shift_pixels_per_byte" == # of pixels per byte in "dst" */
	shift_t shift_pixels_per_byte = is_rle4 ? 1 : 0;
#define ceil_pixels_per_byte shift_pixels_per_byte
	byte_t *dst_row_end = dst + dst_resy * dst_scan;
	byte_t *dst_row_start = dst_row_end -  dst_scan;
	byte_t *dst_row_iter = dst_row_start;
#define OUTBYTE(v) (dst_row_iter < dst_row_end ? (void)(*(dst_row_iter)++ = (v)) : (void)0)
	while (src < src_end) {
		byte_t count = *src++;
		if (count) {
			byte_t pixel;
			if unlikely(src >= src_end)
				goto done;
			pixel = *src++;
			/*count += ceil_pixels_per_byte;*/
			count >>= shift_pixels_per_byte;
			do {
				OUTBYTE(pixel);
			} while (--count);
		} else {
			/* 0-length is a command escape */
			byte_t cmd;
			if unlikely(src >= src_end)
				goto done;
			cmd = *src++;
			switch (cmd) {
			case 0:
				/* Move to next scanline */
				dst_row_end -= dst_scan;
				dst_row_start -= dst_scan;
				dst_row_iter = dst_row_start;
				if (dst_row_end <= dst)
					return;
				break;
			case 1:
				/* Done! */
done:
				bzero(dst_row_iter, (size_t)(dst_row_end - dst_row_iter));
				bzero(dst, (size_t)(dst_row_start - dst));
				return;
			case 2: {
				/* Delta */
				uintptr_t row_delta;
				if unlikely(src >= src_end)
					goto done;
				cmd = *src++;
				/*cmd += ceil_pixels_per_byte;*/
				cmd >>= shift_pixels_per_byte;
				if (cmd > (size_t)(dst_row_end - dst_row_iter))
					cmd = (size_t)(dst_row_end - dst_row_iter);
				bzero(dst_row_iter, cmd);
				if unlikely(src >= src_end)
					goto done;
				cmd = *src++;
				/*cmd += ceil_pixels_per_byte;*/
				cmd >>= shift_pixels_per_byte;
				if (cmd) {
					bzero(dst_row_iter, (size_t)(dst_row_end - dst_row_iter));
					row_delta = cmd * dst_scan;
					if (row_delta > (uintptr_t)dst_row_start ||
						(dst_row_start - row_delta) < dst)
						goto done;
					dst_row_end -= row_delta;
					bzero(dst_row_end, (size_t)(dst_row_start - dst_row_end));
					dst_row_start -= row_delta;
					dst_row_iter = dst_row_start;
				}
			}	break;

			default: {
				/*cmd += ceil_pixels_per_byte;*/
				bool padafter;
				cmd >>= shift_pixels_per_byte;
				padafter = (cmd & 1);
				do {
					byte_t pixel;
					if unlikely(src >= src_end)
						goto done;
					pixel = *src++;
					OUTBYTE(pixel);
				} while (--cmd);
				if (padafter) {
					if unlikely(src >= src_end)
						goto done;
					++src;
				}
			}	break;

			}
		}
	}
#undef OUTBYTE
#undef ceil_pixels_per_byte
}

PRIVATE void CC
swap_rows(byte_t *a, byte_t *b,
          size_t scanline) {
	do {
		byte_t temp = *a;
		*a++ = *b;
		*b++ = temp;
	} while (--scanline);
}

PRIVATE void CC
vflip_scanlines(byte_t *data,
                size_t scanline,
                size_t size_y) {
	while (size_y >= 2) {
		byte_t *row1 = data;
		byte_t *row2 = data + (size_y - 1) * scanline;
		swap_rows(row1, row2, scanline);
		data += scanline;
		size_y -= 2;
	}
}


PRIVATE NONNULL((1)) void CC
fix_missing_alpha_channel(struct bmpbuffer *__restrict self) {
	struct pixel {
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
	};
	video_coord_t y;
	assert(self->vb_format.vf_codec->vc_codec == VIDEO_CODEC_RGBA8888);
	assert(self->vb_format.vf_pal == NULL);
	for (y = 0; y < self->vb_size_y; ++y) {
		struct pixel *iter, *end;
		iter = (struct pixel *)(self->rb_data + y * self->rb_stride);
		end  = iter + self->vb_size_x;
		do {
			if (iter->a != 0)
				return; /* Got actual alpha values! */
		} while (++iter < end);
	}

	/* No alpha values -> use RGBX8888 instead */
	self->vb_format.vf_codec = video_codec_lookup(VIDEO_CODEC_RGBX8888);
	assert(self->vb_format.vf_codec);
}


struct bmp_masks {
	video_pixel_t bm_r;
	video_pixel_t bm_g;
	video_pixel_t bm_b;
	video_pixel_t bm_a;
};

PRIVATE ATTR_CONST WUNUSED struct bmp_masks const *CC
default_bmp_masks(WORD biBitCount) {
	switch (biBitCount) {
	case 15:
	case 16: {
		static struct bmp_masks const b16 = {
			/* VIDEO_CODEC_XBGR1555 */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
			.bm_r = UINT16_C(0x001f),
			.bm_g = UINT16_C(0x03e0),
			.bm_b = UINT16_C(0x7c00),
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
			.bm_r = UINT16_C(0x7c00),
			.bm_g = UINT16_C(0x03e0),
			.bm_b = UINT16_C(0x001f),
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
			.bm_a = UINT32_C(0),
		};
		return &b16;
	}	break;

	case 24: {
		static struct bmp_masks const b24 = {
			/* VIDEO_CODEC_BGR888 */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
			.bm_r = UINT32_C(0x000000ff),
			.bm_g = UINT32_C(0x0000ff00),
			.bm_b = UINT32_C(0x00ff0000),
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
			.bm_r = UINT32_C(0x00ff0000),
			.bm_g = UINT32_C(0x0000ff00),
			.bm_b = UINT32_C(0x000000ff),
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
			.bm_a = UINT32_C(0),
		};
		return &b24;
	}	break;

	case 32: {
		static struct bmp_masks const b32 = {
			/* VIDEO_CODEC_BGRA8888 */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
			.bm_r = UINT32_C(0x0000ff00),
			.bm_g = UINT32_C(0x00ff0000),
			.bm_b = UINT32_C(0xff000000),
			.bm_a = UINT32_C(0x000000ff),
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
			.bm_r = UINT32_C(0x00ff0000),
			.bm_g = UINT32_C(0x0000ff00),
			.bm_b = UINT32_C(0x000000ff),
			.bm_a = UINT32_C(0xff000000),
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
		};
		return &b32;
	}	break;

	default: break;
	}
	return NULL;
}

/* BMP
 * @param: p_mapfile: When  non-NULL, the function is allowed to assume
 *                    that the given blob is owned by this mapfile, and
 *                    is also allowed to steal that mapping by doing  a
 *                    bzero on `*p_mapfile' */
INTERN ATTR_NOINLINE WUNUSED REF struct video_buffer *CC
libvideo_buffer_open_bmp(void const *blob, size_t blob_size,
                         struct mapfile *p_mapfile) {
#if 1
#define Egoto(label)                                                         \
	do {                                                                     \
		syslog(LOG_DEBUG, "[libvideo-gfx][bmp] Load error: %d\n", __LINE__); \
		goto label;                                                          \
	}	__WHILE0
#else
#define Egoto(label) goto label
#endif

#define ADDRAFTER(p) ((byte_t const *)(&(p) + 1))
	byte_t const *blobEOF = (byte_t const *)blob + blob_size;
	byte_t const *reader;
	REF struct bmpbuffer *result;
	REF struct video_palette *result_pal;
	REF struct video_codec_handle *result_codec_handle;
	struct video_codec const *result_codec;
	struct bm_hdr {
		BITMAPFILEHEADER bmFile;
		union {
			BITMAPINFOHEADER bmInfo;
			BITMAPCOREHEADER bmCore;
		};
	};
	struct bm_hdr const *hdr = (struct bm_hdr const *)blob;
	byte_t *bPixelData;
	DWORD dwPixelScanline;
	size_t szPixelDataSize;
	size_t szPixelDataSizeGot;

	bool out_vflipped = true;
	bool out_hasalpha_if_nonzero = false;
	struct video_codec_specs out_specs;

	/* Important stuff from `BITMAPINFOHEADER' */
	DWORD biSize;
	DWORD biCompression;
	LONG biWidth;
	LONG biHeight;
	DWORD biClrUsed;
	WORD biBitCount;

	video_pixel_t rmask = 0;
	video_pixel_t gmask = 0;
	video_pixel_t bmask = 0;
	video_pixel_t amask = 0;

	/* Load base BMP header */
	if (blob_size < sizeof(BITMAPFILEHEADER))
		Egoto(badfmt);
	if (UNALIGNED_GETLE16(&hdr->bmFile.bfType) != ENCODE_INT16('B', 'M'))
		Egoto(badfmt);

	/* Load BMP info header */
	if (ADDRAFTER(hdr->bmInfo.biSize) >= blobEOF)
		Egoto(badfmt);
	if (OVERFLOW_UADD((uintptr_t)hdr,
	                  UNALIGNED_GETLE32(&hdr->bmFile.bfOffBits),
	                  (uintptr_t *)&bPixelData))
		Egoto(badfmt);
	if (bPixelData >= blobEOF)
		Egoto(badfmt);
	biSize = UNALIGNED_GETLE32(&hdr->bmInfo.biSize);
	if (OVERFLOW_UADD((uintptr_t)&hdr->bmInfo, biSize, (uintptr_t *)&reader))
		Egoto(badfmt);
	if (reader >= blobEOF)
		Egoto(badfmt);
	if (biSize == 12) {
		biCompression = BI_RGB;
		biWidth       = UNALIGNED_GETLE16(&hdr->bmCore.bcWidth);
		biHeight      = UNALIGNED_GETLE16(&hdr->bmCore.bcHeight);
		biClrUsed     = 0;
		biBitCount    = UNALIGNED_GETLE16(&hdr->bmCore.bcBitCount);
	} else if (biSize >= 40) {
		biWidth       = UNALIGNED_GETLE32(&hdr->bmInfo.biWidth);
		biHeight      = UNALIGNED_GETLE32(&hdr->bmInfo.biHeight);
		biBitCount    = UNALIGNED_GETLE16(&hdr->bmInfo.biBitCount);
		biCompression = UNALIGNED_GETLE32(&hdr->bmInfo.biCompression);
		biClrUsed     = UNALIGNED_GETLE32(&hdr->bmInfo.biClrUsed);
		if (biSize == 64) /* 64 is an incompatible OS/2 2.x extension */
			Egoto(badfmt);
	} else {
		Egoto(badfmt);
	}

	/* Auto-enable palette-mode for BPP <= 8 */
	if ((biClrUsed == 0 && biBitCount <= 8) ||
	    (biClrUsed > (DWORD)1 << biBitCount))
		biClrUsed = (DWORD)1 << biBitCount;

	/* Validate image width/height */
	if (biWidth <= 0)
		Egoto(badfmt);
	if (biHeight < 0) {
		out_vflipped = false;
		biHeight = -biHeight;
	} else if (biHeight == 0) {
		Egoto(badfmt);
	}

	/* Set default bitmasks */
	switch (biCompression) {

	case BI_RGB: {
		struct bmp_masks const *default_masks;
		biCompression = BI_BITFIELDS;
		if (biClrUsed)
			break; /* Palette-mode */
		default_masks = default_bmp_masks(biBitCount);
		if unlikely(!default_masks)
			Egoto(badfmt);
		rmask = default_masks->bm_r;
		gmask = default_masks->bm_g;
		bmask = default_masks->bm_b;
		amask = default_masks->bm_a;
		out_hasalpha_if_nonzero = biBitCount >= 32;
	}	break;

	case BI_BITFIELDS:
		if (reader + 12 >= blobEOF)
			Egoto(badfmt);
		if (biSize < 52)
			Egoto(badfmt);
		rmask = UNALIGNED_GETLE32(reader);
		reader += 4;
		gmask = UNALIGNED_GETLE32(reader);
		reader += 4;
		bmask = UNALIGNED_GETLE32(reader);
		reader += 4;
		if (biSize >= 56) {
			if (reader + 4 >= blobEOF)
				Egoto(badfmt);
			amask = UNALIGNED_GETLE32(reader);
			reader += 4;
		}
		break;

	case BI_RLE4:
		if (biBitCount != 4)
			Egoto(badfmt);
		break;

	case BI_RLE8:
		if (biBitCount != 8)
			Egoto(badfmt);
		break;

	default:
		Egoto(badfmt);
	}

	/* Calculate (and verify) scanline */
	if (OVERFLOW_UMUL(biWidth, CEILDIV(biBitCount, NBBY), &dwPixelScanline))
		Egoto(badfmt);
	/* From Wikipedia: """The size of each row is rounded up to a multiple of 4 bytes""" */
	dwPixelScanline = CEIL_ALIGN(dwPixelScanline, 4);
	if (OVERFLOW_UMUL(dwPixelScanline, (ULONG)biHeight, &szPixelDataSize))
		Egoto(badfmt);
	szPixelDataSizeGot = szPixelDataSize;
	if (biCompression == BI_BITFIELDS) {
		byte_t *bPixelDataEnd; /* No compression used: assert that pixel data is in-bounds of blob */
		if (OVERFLOW_UADD((uintptr_t)bPixelData, szPixelDataSize, (uintptr_t *)&bPixelDataEnd))
			Egoto(badfmt);
		if (bPixelDataEnd > blobEOF)
			szPixelDataSizeGot = (size_t)(blobEOF - bPixelData);
	}

	/* Build output buffer codec specs. */
	if (biClrUsed) {
		/* Palette-driven format */
		if (biBitCount > 255)
			Egoto(badfmt);
		out_specs.vcs_flags = VIDEO_CODEC_FLAG_PAL;
		out_specs.vcs_rmask = ((DWORD)1 << biBitCount) - 1;
		out_specs.vcs_gmask = out_specs.vcs_rmask;
		out_specs.vcs_bmask = out_specs.vcs_rmask;

		result_pal = video_palette_create(biClrUsed);
		if unlikely(!result_pal)
			goto err;

		/* Read palette */
		if (biSize == 12) {
			size_t i;
			byte_t const *pal_end = reader + (result_pal->vp_cnt * 3);
			if unlikely(pal_end >= blobEOF)
				Egoto(badfmt_pal);
			for (i = 0; i < result_pal->vp_cnt; ++i) {
				uint8_t b = *reader++;
				uint8_t g = *reader++;
				uint8_t r = *reader++;
				result_pal->vp_pal[i] = VIDEO_COLOR_RGB(r, g, b);
			}
		} else {
			size_t i;
			byte_t const *pal_end = reader + (result_pal->vp_cnt * 4);
			if unlikely(pal_end >= blobEOF)
				Egoto(badfmt_pal);
			for (i = 0; i < result_pal->vp_cnt; ++i) {
				uint8_t b = *reader++;
				uint8_t g = *reader++;
				uint8_t r = *reader++;
				++reader; /* 4th element should be ignored */
				result_pal->vp_pal[i] = VIDEO_COLOR_RGB(r, g, b);
			}
		}
		result_pal = video_palette_optimize(result_pal);
	} else {
		/* Color-mask-driven format */
		out_specs.vcs_flags = VIDEO_CODEC_FLAG_NORMAL;
		out_specs.vcs_rmask = rmask;
		out_specs.vcs_gmask = gmask;
		out_specs.vcs_bmask = bmask;
		result_pal = NULL;
	}
	out_specs.vcs_bpp   = biBitCount;
	out_specs.vcs_amask = amask;

	/* Lookup codec */
	result_codec = video_codec_fromspecs(&out_specs, &result_codec_handle);
	if unlikely(!result_codec)
		goto err_pal;

	/* Check for special case: try to inherit BMP file and use as-is as video buffer. */
	if (p_mapfile && biCompression == BI_BITFIELDS && szPixelDataSize == szPixelDataSizeGot) {
		REF struct bmpbuffer_with_mapfile *resultwm;
		resultwm = (REF struct bmpbuffer_with_mapfile *)malloc(sizeof(struct bmpbuffer_with_mapfile));
		if unlikely(!resultwm)
			goto err_pal_codec_handle;
		memcpy(&resultwm->bbwm_map, p_mapfile, sizeof(resultwm->bbwm_map));
		resultwm->vb_ops             = &bmpbuffer_with_mapfile_ops;
		resultwm->vb_format.vf_codec = result_codec;
		resultwm->vb_format.vf_pal   = result_pal;
		resultwm->vb_size_x          = (size_t)(ULONG)biWidth;
		resultwm->vb_size_y          = (size_t)(ULONG)biHeight;
		resultwm->rb_data            = bPixelData;
		resultwm->rb_total           = szPixelDataSize;
		resultwm->rb_stride          = dwPixelScanline;
		resultwm->bb_codec_handle    = result_codec_handle;
		if (out_vflipped)
			vflip_scanlines(bPixelData, dwPixelScanline, (size_t)(ULONG)biHeight);
		bzero(p_mapfile, sizeof(*p_mapfile));
		if (out_hasalpha_if_nonzero)
			fix_missing_alpha_channel(resultwm);
		return resultwm;
	}

	/* Must allocate a dedicated image buffer */
	result = (REF struct bmpbuffer *)malloc(sizeof(struct bmpbuffer));
	if unlikely(!result)
		goto err_pal_codec_handle;
	result->vb_ops             = &bmpbuffer_ops;
	result->vb_format.vf_codec = result_codec;
	result->vb_format.vf_pal   = result_pal;
	result->vb_size_x          = (size_t)(ULONG)biWidth;
	result->vb_size_y          = (size_t)(ULONG)biHeight;
	result->rb_total           = szPixelDataSize;
	result->rb_stride          = dwPixelScanline;
	result->bb_codec_handle    = result_codec_handle;
	result->rb_data = (byte_t *)malloc(szPixelDataSize);
	if unlikely(!result->rb_data)
		goto err_pal_codec_handle_r;

	/* Time to read pixel data, based on used compression method */
	switch (biCompression) {
	case BI_BITFIELDS:
		/* In this case, pixel data bounds were already asserted */
		memcpy(result->rb_data, bPixelData, szPixelDataSizeGot);
		assert(szPixelDataSize >= szPixelDataSizeGot);
		if (szPixelDataSize > szPixelDataSizeGot) {
			byte_t *iter = result->rb_data + szPixelDataSizeGot;
			bzero(iter, szPixelDataSize - szPixelDataSizeGot);
		}
		break;

	case BI_RLE4:
	case BI_RLE8:
		rle_decode(result->rb_data, dwPixelScanline, result->vb_size_y,
		           bPixelData, blobEOF, biCompression == BI_RLE4);
		break;

	default:
		__builtin_unreachable();
	}

	if (out_vflipped) {
		vflip_scanlines(result->rb_data,
		                result->rb_stride,
		                result->vb_size_y);
	}
	if (out_hasalpha_if_nonzero)
		fix_missing_alpha_channel(result);
	return result;
/*
badfmt_pal_codec_handle_r:
	free(result);
badfmt_pal_codec_handle:
	video_codec_handle_decref(result_codec_handle);*/
badfmt_pal:
	if (result_pal)
		video_palette_decref(result_pal);
badfmt:
	return VIDEO_BUFFER_WRONG_FMT;
err_pal_codec_handle_r:
	free(result);
err_pal_codec_handle:
	video_codec_handle_decref(result_codec_handle);
err_pal:
	if (result_pal)
		video_palette_decref(result_pal);
err:
	return NULL;
#undef ADDRAFTER
}


INTERN ATTR_NOINLINE WUNUSED NONNULL((1, 2)) int CC
libvideo_buffer_save_bmp(struct video_buffer *__restrict self,
                         FILE *stream, char const *options) {
	struct ATTR_PACKED bmp_pal_color {
		uint8_t r, g, b, zero;
	};
	struct ATTR_PACKED bm_hdr {
		BITMAPFILEHEADER bmFile;
		BITMAPINFOHEADER bmInfo;
		union {
			uint32_t bmColorMasks[4];
			struct bmp_pal_color bmPalette[256];
		};
	} hdr;
	struct video_lock vid_lock;
	struct video_codec const *codec = self->vb_format.vf_codec;
	struct video_palette const *pal = self->vb_format.vf_pal;
	DWORD dwPixelScanline = CEILDIV(self->vb_size_x * codec->vc_specs.vcs_bpp, NBBY);

	/* From Wikipedia: """The size of each row is rounded up to a multiple of 4 bytes""" */
	dwPixelScanline = CEIL_ALIGN(dwPixelScanline, 4);


	/* Check for codec types that cannot be written as-it into a BMP file */
	if ((codec->vc_specs.vcs_flags & (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_LUM))
	    ? (codec->vc_specs.vcs_bpp > 8 || codec->vc_specs.vcs_amask || (pal && pal->vp_cnt > 255))
	    : (codec->vc_specs.vcs_bpp <= 8)) {
		/* Codecs with BPP <= 8 **MUST** use a palette (or the emulated grayscale palette).
		 * If that isn't the case  for "self", then we must  convert to a different  codec. */
		int result;
		REF struct video_buffer *converted_buffer;
		video_codec_t preferred_codec_id;
		struct video_codec const *preferred_codec;
		if (codec->vc_specs.vcs_amask) {
			if (pal || (codec->vc_specs.vcs_flags & (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_LUM))) {
				preferred_codec_id = VIDEO_CODEC_BGRA8888;
			} else {
				unsigned int n_alpha = POPCOUNT(codec->vc_specs.vcs_amask);
				if (n_alpha == 1) {
					preferred_codec_id = VIDEO_CODEC_BGRA5551;
				} else if (n_alpha <= 4) {
					preferred_codec_id = VIDEO_CODEC_BGRA4444;
				} else {
					preferred_codec_id = VIDEO_CODEC_BGRA8888;
				}
			}
		} else if (pal || (codec->vc_specs.vcs_flags & (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_LUM))) {
			preferred_codec_id = VIDEO_CODEC_BGR888;
		} else if (codec->vc_specs.vcs_bpp <= 16) {
			preferred_codec_id = VIDEO_CODEC_BGR565;
		} else if (codec->vc_specs.vcs_bpp <= 24) {
			preferred_codec_id = VIDEO_CODEC_BGR888;
		} else {
			preferred_codec_id = VIDEO_CODEC_BGRA8888;
		}
		preferred_codec = video_codec_lookup(preferred_codec_id);
		if unlikely(!preferred_codec) {
			errno = EINVAL;
			return -1;
		}
		assert(preferred_codec->vc_specs.vcs_bpp > 8);
		converted_buffer = libvideo_buffer_convert(self, preferred_codec,
		                                           NULL, VIDEO_BUFFER_RAM);
		if unlikely(!converted_buffer)
			return -1;
		result = libvideo_buffer_save_bmp(converted_buffer, stream, options);
		video_buffer_decref(converted_buffer);
		return result;
	}

	bzero(&hdr, sizeof(hdr));
	hdr.bmFile.bfType      = ENCODE_INT16('B', 'M');
	hdr.bmFile.bfSize      = sizeof(hdr.bmFile);
	hdr.bmInfo.biWidth     = self->vb_size_x;
	hdr.bmInfo.biHeight    = -(LONG)self->vb_size_y;
	hdr.bmInfo.biPlanes    = 1;
	hdr.bmInfo.biBitCount  = codec->vc_specs.vcs_bpp;
	hdr.bmInfo.biSizeImage = dwPixelScanline * self->vb_size_y;
	hdr.bmColorMasks[0]    = codec->vc_specs.vcs_rmask;
	hdr.bmColorMasks[1]    = codec->vc_specs.vcs_gmask;
	hdr.bmColorMasks[2]    = codec->vc_specs.vcs_bmask;
	hdr.bmColorMasks[3]    = codec->vc_specs.vcs_amask;

	if (pal) {
		/* Got a palette: must use "BI_RGB" and encode it */
		size_t i;
		hdr.bmInfo.biCompression = BI_RGB;
		hdr.bmInfo.biClrUsed     = pal->vp_cnt;
		hdr.bmInfo.biSize        = sizeof(hdr.bmInfo);
		hdr.bmFile.bfOffBits = offsetof(struct bm_hdr, bmPalette) +
		                       (pal->vp_cnt * sizeof(struct bmp_pal_color));
		for (i = 0; i < pal->vp_cnt; ++i) {
			video_color_t col = pal->vp_pal[i];
			hdr.bmPalette[i].r = VIDEO_COLOR_GET_RED(col);
			hdr.bmPalette[i].g = VIDEO_COLOR_GET_GREEN(col);
			hdr.bmPalette[i].b = VIDEO_COLOR_GET_BLUE(col);
		}
	} else if (hdr.bmColorMasks[3]) {
		/* Got an alpha-channel: **MUST** use bitfield encoding */
		hdr.bmInfo.biCompression = BI_BITFIELDS;
		hdr.bmInfo.biSize        = sizeof(hdr.bmInfo) + sizeof(hdr.bmColorMasks);
		hdr.bmFile.bfOffBits     = offsetafter(struct bm_hdr, bmColorMasks);
	} else {
		struct bmp_masks const *dmasks;
		dmasks = default_bmp_masks(hdr.bmInfo.biBitCount);
		hdr.bmInfo.biCompression = BI_RGB;
		if (dmasks != NULL &&
		    dmasks->bm_r == hdr.bmColorMasks[0] &&
		    dmasks->bm_g == hdr.bmColorMasks[1] &&
		    dmasks->bm_b == hdr.bmColorMasks[2]) {
			/* Can use default color masks */
			hdr.bmInfo.biSize    = sizeof(hdr.bmInfo);
			hdr.bmFile.bfOffBits = offsetafter(struct bm_hdr, bmInfo);
		} else {
			/* Need to use custom color masks */
			hdr.bmInfo.biSize    = sizeof(hdr.bmInfo) + 12;
			hdr.bmFile.bfOffBits = offsetafter(struct bm_hdr, bmColorMasks[2]);
		}
	}

	/* Acquire lock to video memory of "self" */
	if unlikely(video_buffer_rlock(self, &vid_lock))
		goto err;

	/* Write file header and color masks/palette */
	if (fwrite(&hdr, 1, hdr.bmFile.bfOffBits, stream) != hdr.bmFile.bfOffBits)
		goto err_unlock;

	/* Write pixel data */
	if likely(vid_lock.vl_stride == dwPixelScanline) {
		/* Can write data without any need for padding or-the-like */
		size_t n_bytes = vid_lock.vl_stride * self->vb_size_y;
		if (fwrite(vid_lock.vl_data, 1, n_bytes, stream) != n_bytes)
			goto err_unlock;
	} else if (vid_lock.vl_stride > dwPixelScanline) {
		video_coord_t y;
		for (y = 0; y < self->vb_size_y; ++y) {
			byte_t const *src = vid_lock.vl_data + y * vid_lock.vl_stride;
			if (fwrite(src, 1, dwPixelScanline, stream) != dwPixelScanline)
				goto err_unlock;
		}
	} else {
		size_t n_skip = dwPixelScanline - vid_lock.vl_stride;
		video_coord_t y;
		for (y = 0; y < self->vb_size_y; ++y) {
			byte_t const *src = vid_lock.vl_data + y * vid_lock.vl_stride;
			if (fwrite(src, 1, dwPixelScanline, stream) != dwPixelScanline)
				goto err_unlock;
			if (fseek(stream, n_skip, SEEK_CUR))
				goto err_unlock;
		}
		/* Force the last byte to be allocated within the stream */
		if (fseek(stream, -1, SEEK_CUR))
			goto err_unlock;
		if (fputc(0, stream))
			goto err_unlock;
	}

	video_buffer_unlock(self, &vid_lock);
	return 0;
err_unlock:
	video_buffer_unlock(self, &vid_lock);
err:
	return -1;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_IO_BMP_C_INL */
