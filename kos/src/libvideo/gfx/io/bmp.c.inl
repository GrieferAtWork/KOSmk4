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
#define __VIDEO_BUFFER_const /*nothing */
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

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

#include <libvideo/color.h>
#include <libvideo/gfx/api.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/codec/codec.h>
#include <libvideo/gfx/codec/palette.h>
#include <libvideo/types.h>

#include "../buffer.h"
#include "../buffer/lockable.h"
#include "../codec/codec-specs.h"
#include "../codec/codec.h"
#include "../codec/palette.h"
#include "../gfx-utils.h"
#include "../io-utils.h"
#include "../ramdomain.h"

#ifndef BITSOF
#define BITSOF(x) (sizeof(x) * NBBY)
#endif /* !BITSOF */

DECL_BEGIN

/* BMP load/save based on:
 * - https://en.wikipedia.org/wiki/BMP_file_format
 */

PRIVATE void LIBVIDEO_GFX_CC
unmap_mapfile_release_mem(void *cookie, void *UNUSED(mem)) {
	struct mapfile *mf = (struct mapfile *)cookie;
	(void)unmapfile(mf);
	free(mf);
}

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
fix_missing_alpha_channel(struct video_buffer *__restrict self) {
	struct pixel {
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
	};
	video_coord_t y;
	struct video_rambuffer_base *me = (struct video_rambuffer_base *)self;
	assert(me->vb_domain == &libvideo_ramdomain);
	assert(me->vb_ops == &rambuffer_ops ||
	       me->vb_ops == &rambuffer_formem_ops);
	assert(me->vb_codec->vc_codec == VIDEO_CODEC_RGBA8888);
	assert(me->vb_surf.vs_pal == NULL);
	for (y = 0; y < me->vb_ydim; ++y) {
		struct pixel *iter, *end;
		iter = (struct pixel *)(me->rb_data + y * me->rb_stride);
		end  = iter + me->vb_xdim;
		do {
			if (iter->a != 0)
				return; /* Got actual alpha values! */
		} while (++iter < end);
	}

	/* No alpha values -> use RGBX8888 instead.
	 * Because we're a ram-buffer, we can simply change the codec like this! */
	me->vb_codec = libvideo_codec_lookup(VIDEO_CODEC_RGBX8888);
	assertf(me->vb_codec, "Built-in codec should have been recognized");
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
INTERN ATTR_NOINLINE WUNUSED NONNULL((1)) REF struct video_buffer *CC
libvideo_buffer_open_bmp(struct video_domain const *__restrict domain_hint,
                         void const *blob, size_t blob_size,
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
	REF struct video_buffer *result;
	struct video_lock result_lock;
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
	struct video_buffer_format format;

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

		format.vbf_pal = libvideo_palette_create(biClrUsed);
		if unlikely(!format.vbf_pal)
			goto err;

		/* Read palette */
		if (biSize == 12) {
			size_t i;
			byte_t const *pal_end = reader + (format.vbf_pal->vp_cnt * 3);
			if unlikely(pal_end >= blobEOF)
				Egoto(badfmt_pal);
			for (i = 0; i < format.vbf_pal->vp_cnt; ++i) {
				uint8_t b = *reader++;
				uint8_t g = *reader++;
				uint8_t r = *reader++;
				format.vbf_pal->vp_pal[i] = VIDEO_COLOR_RGB(r, g, b);
			}
		} else {
			size_t i;
			byte_t const *pal_end = reader + (format.vbf_pal->vp_cnt * 4);
			if unlikely(pal_end >= blobEOF)
				Egoto(badfmt_pal);
			for (i = 0; i < format.vbf_pal->vp_cnt; ++i) {
				uint8_t b = *reader++;
				uint8_t g = *reader++;
				uint8_t r = *reader++;
				++reader; /* 4th element should be ignored */
				format.vbf_pal->vp_pal[i] = VIDEO_COLOR_RGB(r, g, b);
			}
		}
		format.vbf_pal = libvideo_palette_optimize(format.vbf_pal);
	} else {
		/* Color-mask-driven format */
		out_specs.vcs_flags = VIDEO_CODEC_FLAG_NORMAL;
		out_specs.vcs_rmask = rmask;
		out_specs.vcs_gmask = gmask;
		out_specs.vcs_bmask = bmask;
		format.vbf_pal = NULL;
	}
	out_specs.vcs_bpp   = biBitCount;
	out_specs.vcs_amask = amask;

	/* Lookup codec */
	format.vbf_codec = libvideo_codec_fromspecs(&out_specs);
	if unlikely(!format.vbf_codec)
		goto err_pal;
	format.vbf_flags = VIDEO_GFX_F_NORMAL;

	/* Check for special case: try to inherit BMP file and use as-is as video buffer. */
	if (p_mapfile && biCompression == BI_BITFIELDS &&
	    szPixelDataSize == szPixelDataSizeGot && domain_hint == &libvideo_ramdomain) {
		void *mapfile_cookie;
		REF struct video_buffer *result;
		if (out_vflipped)
			vflip_scanlines(bPixelData, dwPixelScanline, (size_t)(ULONG)biHeight);
		mapfile_cookie = malloc(sizeof(struct mapfile));
		if unlikely(!mapfile_cookie)
			goto err_pal_codec;
		mapfile_cookie = memcpy(mapfile_cookie, p_mapfile, sizeof(*p_mapfile));
		result = _video_domain_formem(out_hasalpha_if_nonzero ? _libvideo_ramdomain() : domain_hint,
		                              &format, (size_t)(ULONG)biWidth, (size_t)(ULONG)biHeight,
		                              bPixelData, dwPixelScanline,
		                              &unmap_mapfile_release_mem, mapfile_cookie,
		                              VIDEO_DOMAIN_FORMEM_F_NORMAL);
		if unlikely(!result) {
			free(mapfile_cookie);
			goto err_pal_codec;
		}
		if (format.vbf_pal)
			video_palette_decref(format.vbf_pal);
		video_codec_decref(format.vbf_codec);
		bzero(p_mapfile, sizeof(*p_mapfile)); /* Stolen by `mapfile_cookie' */
		if (out_hasalpha_if_nonzero)
			fix_missing_alpha_channel(result);
		return result;
	}

	/* Create result buffer */
	result = video_domain_newbuffer(out_hasalpha_if_nonzero ? _libvideo_ramdomain() : domain_hint, &format,
	                                (size_t)(ULONG)biWidth, (size_t)(ULONG)biHeight,
	                                VIDEO_DOMAIN_NEWBUFFER_F_NORMAL);
	if unlikely(!result)
		goto err_pal_codec;
	if (format.vbf_pal)
		video_palette_decref(format.vbf_pal);
	video_codec_decref(format.vbf_codec);
	if unlikely(video_buffer_wlock(result, &result_lock))
		goto err_r;

	/* Time to read pixel data, based on used compression method */
	switch (biCompression) {
	case BI_BITFIELDS: {
		/* In this case, pixel data bounds were already asserted */
		byte_t *dst = result_lock.vl_data;
		if likely(result_lock.vl_stride == dwPixelScanline) {
			dst = (byte_t *)mempcpy(dst, bPixelData, szPixelDataSizeGot);
		} else {
			video_dim_t iter_y = result->vb_ydim;
			if (result_lock.vl_stride > dwPixelScanline) {
				byte_t const *src = bPixelData;
				size_t missing    = result_lock.vl_stride - dwPixelScanline;
				do {
					memcpy(dst, src, dwPixelScanline);
					bzero(dst + dwPixelScanline, dwPixelScanline, missing);
					dst += result_lock.vl_stride;
					src += dwPixelScanline;
				} while (--iter_y);
			} else {
				byte_t const *src = bPixelData;
				do {
					dst = (byte_t *)mempcpy(dst, src, result_lock.vl_stride);
					src += szPixelDataSizeGot;
				} while (--iter_y);
			}
		}
		assert(szPixelDataSize >= szPixelDataSizeGot);
		if (szPixelDataSize > szPixelDataSizeGot)
			bzero(dst, szPixelDataSize - szPixelDataSizeGot);
	}	break;

	case BI_RLE4:
	case BI_RLE8:
		rle_decode(result_lock.vl_data, result_lock.vl_stride, result->vb_ydim,
		           bPixelData, blobEOF, biCompression == BI_RLE4);
		break;

	default:
		__builtin_unreachable();
	}

	if (out_vflipped) {
		vflip_scanlines(result_lock.vl_data,
		                result_lock.vl_stride,
		                result->vb_ydim);
	}
	video_buffer_unlock(result, &result_lock);
	if (out_hasalpha_if_nonzero)
		fix_missing_alpha_channel(result);
	return result;
badfmt_pal:
	if (format.vbf_pal)
		video_palette_decref(format.vbf_pal);
badfmt:
	return VIDEO_BUFFER_WRONG_FMT;
err_r:
	video_buffer_decref(result);
	goto err;
err_pal_codec:
	video_codec_decref(format.vbf_codec);
err_pal:
	if (format.vbf_pal)
		video_palette_decref(format.vbf_pal);
err:
	return NULL;
#undef ADDRAFTER
}


INTERN ATTR_NOINLINE WUNUSED NONNULL((1, 2)) int CC
libvideo_surface_save_bmp(struct video_surface const *__restrict self,
                          FILE *stream, char const *options) {
	struct ATTR_PACKED bmp_pal_color {
		uint8_t b;
		uint8_t g;
		uint8_t r;
		uint8_t zero;
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
	struct video_buffer *buffer = video_surface_getbuffer(self);
	struct video_codec const *codec = video_buffer_getcodec(buffer);
	struct video_palette const *pal = video_surface_getpalette(self);
	DWORD dwPixelScanline;

	/* Check for codec types that cannot be written as-it into a BMP file */
	if ((codec->vc_specs.vcs_flags & (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_LUM))
	    ? (codec->vc_specs.vcs_bpp > 8 || codec->vc_specs.vcs_amask || (pal && pal->vp_cnt > 256))
	    : (codec->vc_specs.vcs_bpp <= 8)) {
		/* Codecs with BPP <= 8 **MUST** use a palette (or the emulated grayscale palette).
		 * If that isn't the case  for "self", then we must  convert to a different  codec. */
		int result;
		REF struct video_buffer *converted_buffer;
		video_codec_t preferred_codec_id;
		struct video_buffer_format preferred_format;
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
		preferred_format.vbf_flags = video_surface_getflags(self) & VIDEO_GFX_F_YMIRROR;
		preferred_format.vbf_codec = libvideo_codec_lookup(preferred_codec_id);
		assertf(preferred_format.vbf_codec, "Built-in codec should have been recognized");
		assert(preferred_format.vbf_codec->vc_specs.vcs_bpp > 8);
		converted_buffer = libvideo_surface_convert(self, _libvideo_ramdomain(), &preferred_format);
		if unlikely(!converted_buffer)
			return -1;
		result = libvideo_surface_save_bmp(video_buffer_assurface(converted_buffer), stream, options);
		video_buffer_decref(converted_buffer);
		return result;
	} else if (video_surface_getflags(self) & (VIDEO_GFX_F_XYSWAP | VIDEO_GFX_F_XMIRROR)) {
		/* Can't represent these flags natively (only "VIDEO_GFX_F_YMIRROR" can be encoded into a BMP) */
		int result;
		REF struct video_buffer *converted_buffer;
		struct video_buffer_format preferred_format;
		preferred_format.vbf_flags = video_surface_getflags(self) & VIDEO_GFX_F_YMIRROR;
		preferred_format.vbf_codec = video_surface_getcodec(self);
		converted_buffer = libvideo_surface_convert(self, _libvideo_ramdomain(), &preferred_format);
		if unlikely(!converted_buffer)
			return -1;
		result = libvideo_surface_save_bmp(video_buffer_assurface(converted_buffer), stream, options);
		video_buffer_decref(converted_buffer);
		return result;
	}

	/* From Wikipedia: """The size of each row is rounded up to a multiple of 4 bytes""" */
	dwPixelScanline = CEILDIV(video_buffer_getxdim(buffer) * codec->vc_specs.vcs_bpp, NBBY);
	dwPixelScanline = CEIL_ALIGN(dwPixelScanline, 4);

	bzero(&hdr, sizeof(hdr));
	hdr.bmFile.bfType   = ENCODE_INT16('B', 'M');
	hdr.bmFile.bfSize   = sizeof(hdr.bmFile);
	hdr.bmInfo.biWidth  = video_buffer_getxdim(buffer);
	hdr.bmInfo.biHeight = -(LONG)video_buffer_getydim(buffer);
	if (video_surface_getflags(self) & VIDEO_GFX_F_YMIRROR)
		hdr.bmInfo.biHeight = -hdr.bmInfo.biHeight;
	hdr.bmInfo.biPlanes    = 1;
	hdr.bmInfo.biBitCount  = codec->vc_specs.vcs_bpp;
	hdr.bmInfo.biSizeImage = dwPixelScanline * video_buffer_getydim(buffer);
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

	/* Acquire lock to video memory of "buffer" */
	if unlikely(video_buffer_rlock(buffer, &vid_lock)) {
		if (errno != ENOMEM) {
			/* Try with a force-lockable buffer */
			int result;
			struct lockable_buffer_base lockable;
			self   = lockable_buffer_initbase(&lockable, self);
			result = libvideo_surface_save_bmp(self, stream, options);
			lockable_buffer_finibase(&lockable);
			return result;
		}
		goto err;
	}

	/* Write file header and color masks/palette */
	if (!fwrite(&hdr, hdr.bmFile.bfOffBits, 1, stream))
		goto err_unlock;

	/* Write pixel data */
	if likely(vid_lock.vl_stride == dwPixelScanline) {
		/* Can write data without any need for padding or-the-like */
		size_t n_bytes = vid_lock.vl_stride * video_buffer_getydim(buffer);
		if (!fwrite(vid_lock.vl_data, n_bytes, 1, stream))
			goto err_unlock;
	} else if (vid_lock.vl_stride > dwPixelScanline) {
		video_coord_t y;
		for (y = 0; y < video_buffer_getydim(buffer); ++y) {
			byte_t const *src = vid_lock.vl_data + y * vid_lock.vl_stride;
			if (!fwrite(src, dwPixelScanline, 1, stream))
				goto err_unlock;
		}
	} else {
		size_t n_skip = dwPixelScanline - vid_lock.vl_stride;
		video_coord_t y;
		for (y = 0; y < video_buffer_getydim(buffer); ++y) {
			byte_t const *src = vid_lock.vl_data + y * vid_lock.vl_stride;
			if (!fwrite(src, dwPixelScanline, 1, stream))
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

	video_buffer_unlock(buffer, &vid_lock);
	return 0;
err_unlock:
	video_buffer_unlock(buffer, &vid_lock);
err:
	return -1;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_IO_BMP_C_INL */
