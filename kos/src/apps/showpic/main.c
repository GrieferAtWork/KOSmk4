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
#ifndef GUARD_APPS_SHOWPIC_MAIN_C
#define GUARD_APPS_SHOWPIC_MAIN_C 1
#define LIBVIDEO_CODEC_WANT_PROTOTYPES
#define LIBVIDEO_GFX_WANT_PROTOTYPES
#define LIBVIDEO_COMPOSITOR_WANT_PROTOTYPES
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#define _TIME_T_BITS 64

#include <hybrid/compiler.h>

#include <hybrid/align.h>

#include <kos/anno.h>
#include <sys/time.h>

#include <err.h>
#include <format-printer.h>
#include <malloca.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <time.h>
#include <timeval-utils.h>
#include <uchar.h>
#include <unistd.h>

#include <libvideo/codec/codecs.h>
#include <libvideo/codec/palette.h>
#include <libvideo/color.h>
#include <libvideo/compositor/compositor.h>
#include <libvideo/gfx/anim.h>
#include <libvideo/gfx/blend.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/font.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/gfx/screen.h>
#include <libvideo/types.h>

DECL_BEGIN

static struct video_crect const CRECT_FULL = VIDEO_CRECT_INIT_FULL;
static struct video_rect const RECT_FULL = VIDEO_RECT_INIT_FULL;

static void
do_dump_buffer_specs(struct video_buffer *buf,
                     struct video_fontprinter_data *io) {
	struct video_codec const *codec;
	struct video_palette const *palette;
#define gfx_printf(...) format_printf(&video_fontprinter, io, __VA_ARGS__)
	gfx_printf("res:   %ux%u\n", (unsigned int)buf->vb_xdim, (unsigned int)buf->vb_ydim);
	codec = buf->vb_format.vf_codec;
	gfx_printf("codec: %#x [%ubpp,%c%c%c]\n",
	           (unsigned int)codec->vc_codec,
	           (unsigned int)codec->vc_specs.vcs_bpp,
	           (codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_PAL) ? 'P' : '-',
	           (codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_LUM) ? 'G' : '-',
	           (codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_LSB) ? 'L' : '-');
	if (!(codec->vc_specs.vcs_flags & (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_LUM))) {
		gfx_printf("rmask: %#.8I32x\n", (uint32_t)codec->vc_specs.vcs_rmask);
		gfx_printf("gmask: %#.8I32x\n", (uint32_t)codec->vc_specs.vcs_gmask);
		gfx_printf("bmask: %#.8I32x\n", (uint32_t)codec->vc_specs.vcs_bmask);
		if (codec->vc_specs.vcs_amask)
			gfx_printf("amask: %#.8I32x\n", (uint32_t)codec->vc_specs.vcs_amask);
	}
	palette = buf->vb_format.vf_pal;
	if (palette) {
		unsigned int cells_padding     = 2;
		unsigned int cell_w            = 8;
		unsigned int cell_h            = 8;
		unsigned int cells_per_row_max = ((io->vfp_lnend - io->vfp_curx) - (cells_padding * 2)) / cell_w;
		unsigned int cells_per_row     = cells_per_row_max > 32 ? 32 : cells_per_row_max;
		unsigned int rows              = CEILDIV(palette->vp_cnt, cells_per_row);
		unsigned int rows_width        = (cells_per_row * cell_w);
		unsigned int rows_height       = (rows * cell_h);
		unsigned int pal_x, pal_y;
		gfx_printf("Palette (%u):\n", palette->vp_cnt);
		io->vfp_cury += 2;
		video_gfx_rect(io->vfp_gfx, io->vfp_curx, io->vfp_cury,
		               rows_width + cells_padding * 2,
		               rows_height + cells_padding * 2,
		               io->vfp_bg_fg_colors[1]);
		io->vfp_cury += cells_padding;
		for (pal_y = 0; pal_y < rows; ++pal_y) {
			for (pal_x = 0; pal_x < cells_per_row; ++pal_x) {
				video_color_t color;
				video_pixel_t index = pal_x + (pal_y * cells_per_row);
				if (index >= palette->vp_cnt)
					break;
				color = palette->vp_pal[index];
				video_gfx_fill(io->vfp_gfx,
				               io->vfp_curx + cells_padding + (pal_x * cell_w),
				               io->vfp_cury + (pal_y * cell_h),
				               cell_w, cell_h, color);
			}
		}
		io->vfp_cury += rows_height;
		io->vfp_cury += cells_padding;
	}
#undef gfx_printf
}

static void
dump_buffer_specs(struct video_buffer *buf,
                  struct video_fontprinter_data *io) {
	unsigned int padding = 2;
	video_offset_t start_x, start_y;
	io->vfp_cury += padding;
	io->vfp_lnstart += padding;
	io->vfp_lnend -= padding;
	start_x = io->vfp_curx;
	start_y = io->vfp_cury;
	io->vfp_curx += padding;
	io->vfp_cury += padding;
	do_dump_buffer_specs(buf, io);
	io->vfp_curx -= padding;
	io->vfp_cury += padding;
	io->vfp_lnstart -= padding;
	io->vfp_lnend += padding;
	video_gfx_rect(io->vfp_gfx, start_x, start_y,
	               io->vfp_lnend - io->vfp_lnstart,
	               io->vfp_cury - start_y,
	               io->vfp_bg_fg_colors[1]);
	io->vfp_cury += padding;
}

static ATTR_UNUSED REF struct video_buffer *
palettize(struct video_buffer *self, video_pixel_t num_colors, unsigned int method) {
	struct video_gfx gfx;
	struct video_gfx result_gfx;
	REF struct video_buffer *result;
	struct video_format result_format;
	video_codec_t result_codec_id;

	/* Create palette with the requested # of colors */
	result_format.vf_pal = video_palette_create(num_colors);
	if unlikely(!result_format.vf_pal)
		goto err;

	/* Acquire GFX context for source video buffer */
	video_buffer_getgfx(self, &gfx,
	                    GFX_BLENDMODE_OVERRIDE,
	                    VIDEO_GFX_F_NORMAL, 0);

	/* Palettize source video buffer and store results in "pal" */
	if unlikely(video_gfx_palettize(&gfx, num_colors, result_format.vf_pal->vp_pal, method))
		goto err_pal;
	result_format.vf_pal = video_palette_optimize(result_format.vf_pal);

	/* Figure out appropriate codec for result buffer */
	if (num_colors <= 2) {
		result_codec_id = VIDEO_CODEC_P1_MSB;
	} else if (num_colors <= 4) {
		result_codec_id = VIDEO_CODEC_P2_MSB;
	} else if (num_colors <= 16) {
		result_codec_id = VIDEO_CODEC_P4_MSB;
	} else {
		result_codec_id = VIDEO_CODEC_P8;
	}
	result_format.vf_codec = video_codec_lookup(result_codec_id);
	if unlikely(!result_format.vf_codec)
		goto err_pal;

	/* Allocate result buffer */
	result = video_domain_newbuffer(self->vb_domain,
	                                video_gfx_getclipw(&gfx),
	                                video_gfx_getcliph(&gfx),
	                                &result_format,
	                                VIDEO_DOMAIN_NEWBUFFER_F_NORMAL);
	video_palette_decref(result_format.vf_pal);
	if unlikely(!result)
		goto err;

	/* Blit source GFX context onto result video_buffer. */
	video_buffer_getgfx(result, &result_gfx,
	                    GFX_BLENDMODE_OVERRIDE,
	                    VIDEO_GFX_F_NORMAL, 0);
	video_gfx_bitblit(&result_gfx, 0, 0, &gfx, 0, 0,
	                  video_gfx_getclipw(&gfx),
	                  video_gfx_getcliph(&gfx));
	return result;
/*
err_pal_r:
	video_buffer_decref(result);*/
err_pal:
	video_palette_decref(result_format.vf_pal);
err:
	return NULL;
}


static void
do_showpic(struct video_buffer *screen,
           struct video_buffer *image,
           struct video_font *font,
           char const *filename,
           struct video_anim_frame *frameinfo) {
	struct video_gfx screen_gfx;
	struct video_gfx image_gfx;
	video_dim_t blit_w, blit_h;
	video_coord_t blit_x, blit_y;
#if 0
	/* Palettize "image" */
	if (!(image->vb_format.vf_codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_PAL)) {
		struct video_buffer *new_image;
		new_image = palettize(image, 128, VIDEO_GFX_PALETTIZE_METHOD_HISTOGRAM);
//		new_image = palettize(image, 32, VIDEO_GFX_PALETTIZE_METHOD_MEDIAN_CUT);
		if likely(new_image) {
			do_showpic(new_image);
			video_buffer_decref(new_image);
			return;
		}
	}
#endif

	/* Load GFX contexts for the image and the screen */
	video_buffer_getgfx(screen, &screen_gfx,
	                    GFX_BLENDMODE_ALPHA,
	                    VIDEO_GFX_F_NORMAL, 0);
	video_buffer_getgfx(image, &image_gfx,
	                    GFX_BLENDMODE_OVERRIDE,
	                    VIDEO_GFX_F_NEAREST /*VIDEO_GFX_F_LINEAR*/, 0);

	/*video_gfx_clip(&image_gfx, 200, 200,
	               video_gfx_getclipw(&image_gfx) / 2,
	               video_gfx_getcliph(&image_gfx) / 2);*/
	/*video_gfx_clip(&screen_gfx, 20, 20,
	               video_gfx_getclipw(&screen_gfx) - 40,
	               video_gfx_getcliph(&screen_gfx) - 40);
	video_gfx_clip(&screen_gfx, -20, -20,
	               video_gfx_getclipw(&screen_gfx) + 40,
	               video_gfx_getcliph(&screen_gfx) + 40);*/
//	video_gfx_hmirror(&screen_gfx);
//	video_gfx_vmirror(&screen_gfx);
//	video_gfx_lrot90(&screen_gfx);
//	video_gfx_lrot90(&image_gfx);
//	video_gfx_rrot90(&image_gfx);

	/* Calculate where the image should be displayed */
	blit_w = video_gfx_getclipw(&image_gfx);
	blit_h = video_gfx_getcliph(&image_gfx);
	if (blit_w > video_gfx_getclipw(&screen_gfx)) {
		video_dim_t new_blit_w, new_blit_h;
		/* >> new_blit_w / new_blit_h = blit_w / blit_h;
		 * >> new_blit_w = (blit_w / blit_h) * new_blit_h;
		 * >> new_blit_w / (blit_w / blit_h) = new_blit_h;
		 * >> new_blit_h = new_blit_w / (blit_w / blit_h);
		 * >> new_blit_h = (new_blit_w * blit_h) / blit_w; */
		new_blit_w = video_gfx_getclipw(&screen_gfx);
		new_blit_h = ((uint64_t)new_blit_w * blit_h) / blit_w;
		blit_w = new_blit_w;
		blit_h = new_blit_h;
	}

	if (blit_h > video_gfx_getcliph(&screen_gfx)) {
		video_dim_t new_blit_w, new_blit_h;
		/* >> new_blit_w / new_blit_h = blit_w / blit_h;
		 * >> new_blit_w = (blit_w / blit_h) * new_blit_h;
		 * >> new_blit_w = (blit_w * new_blit_h) / blit_h; */
		new_blit_h = video_gfx_getcliph(&screen_gfx);
		new_blit_w = ((uint64_t)blit_w * new_blit_h) / blit_h;
		blit_w = new_blit_w;
		blit_h = new_blit_h;
	}

	blit_x = (video_gfx_getclipw(&screen_gfx) - blit_w) / 2;
	blit_y = (video_gfx_getcliph(&screen_gfx) - blit_h) / 2;

#if 0
	blit_w = video_gfx_getclipw(&screen_gfx);
	blit_h = video_gfx_getcliph(&screen_gfx);
	blit_x = 0;
	blit_y = 0;
#endif

	/* Display the image */
#if 1
	video_gfx_stretch(&screen_gfx, blit_x, blit_y, blit_w, blit_h,
	                  &image_gfx, 0, 0,
	                  video_gfx_getclipw(&image_gfx),
	                  video_gfx_getcliph(&image_gfx));
#elif 0
	{
		static REF struct video_buffer *mask_buffer = NULL;
		if (!mask_buffer) {
			mask_buffer = video_buffer_create(VIDEO_BUFFER_AUTO, 64, 64,
			                                  video_codec_lookup(VIDEO_CODEC_A1_MSB),
			                                  NULL);
			if (mask_buffer) {
				struct video_gfx mask_gfx;
				video_buffer_getgfx(mask_buffer, &mask_gfx,
				                    GFX_BLENDMODE_OVERRIDE,
				                    VIDEO_GFX_F_XWRAP | VIDEO_GFX_F_YWRAP, 0);
				video_gfx_fill(&mask_gfx, 0, 0, 64 - 1, 64 - 1, VIDEO_COLOR_RGBA(0, 0, 0, 0xff));
				for (unsigned int i = 0; i < (32 / 4); ++i) {
					unsigned int x = i * 4;
					unsigned int y = i * 4;
					unsigned int w = 64 - (x * 2);
					unsigned int h = 64 - (y * 2);
					x += ((i & 1) >> 0) << 1;
					y += ((i & 2) >> 1) << 1;
					video_gfx_rect(&mask_gfx, x, y, w, h, VIDEO_COLOR_RGBA(0, 0, 0, 0));
				}
				video_gfx_setblend(&mask_gfx, GFX_BLENDMODE_ALPHAMASK);
			}
		}
		if (mask_buffer) {
			struct video_gfx mask_gfx;
			video_buffer_getgfx(mask_buffer, &mask_gfx,
			                    GFX_BLENDMODE_ALPHAMASK,
			                    VIDEO_GFX_F_XWRAP | VIDEO_GFX_F_YWRAP, 0);
			/*video_gfx_stretch3(&screen_gfx, blit_x, blit_y,
			                   &mask_gfx, 32, 32,
			                   blit_w, blit_h,
			                   &image_gfx, 0, 0,
			                   video_gfx_getclipw(&image_gfx),
			                   video_gfx_getcliph(&image_gfx));*/
			video_gfx_bitblit3(&screen_gfx, blit_x, blit_y,
			                   &mask_gfx, 29, 29,
			                   &image_gfx, 0, 0,
			                   video_gfx_getclipw(&image_gfx),
			                   video_gfx_getcliph(&image_gfx));
		}
	}
#elif 0
	{
		struct video_gfx flipgfx = image_gfx;
//		video_gfx_lrot90(&flipgfx);
		static int offset = 0;
		video_gfx_setblend(&flipgfx, GFX_BLENDMODE_ALPHA_OVERRIDE(200));
		video_gfx_enableflags(&flipgfx, VIDEO_GFX_F_XWRAP | VIDEO_GFX_F_YWRAP);
		video_gfx_stretch3(&screen_gfx, blit_x, blit_y,
		                   &flipgfx,
		                   (video_gfx_getcliph(&image_gfx) * 2) + offset,
		                   video_gfx_getclipw(&image_gfx) * 2,
		                   blit_w, blit_h,
		                   &image_gfx, 0, 0,
		                   video_gfx_getclipw(&image_gfx),
		                   video_gfx_getcliph(&image_gfx));
		offset += 3;
//		syslog(LOG_DEBUG, "offset = %d\n", offset);
	}
#elif 0
	{
		int offset = 10;
		gfx_blendmode_t omode = video_gfx_getblend(&screen_gfx);
		/* Draw only red */
		video_gfx_setblend(&screen_gfx, GFX_BLENDMODE_EX(
		                                /*RGB=*/SRC_ALPHA_MUL_CONSTANT_COLOR, ADD, ONE_MINUS_SRC_ALPHA_MUL_CONSTANT_COLOR,
		                                /*A  =*/ONE, ADD, ONE_MINUS_SRC_ALPHA_MUL_CONSTANT_ALPHA,
		                                0xff, 0, 0, 0xff));
		video_gfx_stretch(&screen_gfx, blit_x, blit_y, blit_w, blit_h,
		                  &image_gfx, 0, 0,
		                  video_gfx_getclipw(&image_gfx),
		                  video_gfx_getcliph(&image_gfx));
		/* Alpha-blend on-top: green */
		video_gfx_setblend(&screen_gfx, GFX_BLENDMODE_EX(
		                                /*RGB=*/SRC_ALPHA_MUL_CONSTANT_COLOR, ADD, ONE_MINUS_SRC_ALPHA_MUL_CONSTANT_COLOR,
		                                /*A  =*/ONE, ADD, ONE_MINUS_SRC_ALPHA_MUL_CONSTANT_ALPHA,
		                                0, 0xff, 0, 0xff));
		video_gfx_stretch(&screen_gfx, blit_x + offset, blit_y + offset, blit_w, blit_h,
		                  &image_gfx, 0, 0,
		                  video_gfx_getclipw(&image_gfx),
		                  video_gfx_getcliph(&image_gfx));
		/* Alpha-blend on-top: blue */
		video_gfx_setblend(&screen_gfx, GFX_BLENDMODE_EX(
		                                /*RGB=*/SRC_ALPHA_MUL_CONSTANT_COLOR, ADD, ONE_MINUS_SRC_ALPHA_MUL_CONSTANT_COLOR,
		                                /*A  =*/ONE, ADD, ONE_MINUS_SRC_ALPHA_MUL_CONSTANT_ALPHA,
		                                0, 0, 0xff, 0xff));
		video_gfx_stretch(&screen_gfx, blit_x + 2 * offset, blit_y + 2 * offset, blit_w, blit_h,
		                  &image_gfx, 0, 0,
		                  video_gfx_getclipw(&image_gfx),
		                  video_gfx_getcliph(&image_gfx));
		video_gfx_setblend(&screen_gfx, omode);
	}
#elif 0
	video_gfx_stretch(&screen_gfx, blit_x, blit_y, blit_w, blit_h,
	                  &image_gfx, 0, 0,
	                  video_gfx_getclipw(&image_gfx),
	                  video_gfx_getcliph(&image_gfx));

	/* With MIN, this is like that pencil-sketching filter from VLC :D
	 * With MAX, it looks like a  blur that also brightens the  image. */
	int delta = 2;
	for (int x = -delta; x <= delta; ++x)
	for (int y = -delta; y <= delta; ++y)
	{
		gfx_blendmode_t omode = video_gfx_getblend(&screen_gfx);
		video_gfx_setblend(&screen_gfx, GFX_BLENDMODE_EX(
		                                /*RGB=*/ONE, MAX, ONE,
		                                /*A  =*/ONE, ADD, ONE_MINUS_SRC_ALPHA_MUL_CONSTANT_ALPHA,
		                                0xff, 0, 0, 0xff));
//		video_gfx_hmirror(&image_gfx);
		video_gfx_stretch(&screen_gfx, blit_x + x, blit_y + y, blit_w, blit_h,
		                  &image_gfx, 0, 0,
		                  video_gfx_getclipw(&image_gfx),
		                  video_gfx_getcliph(&image_gfx));
//		video_gfx_hmirror(&image_gfx);
		video_gfx_setblend(&screen_gfx, omode);
	}
#elif 0
	video_gfx_bitblit(&screen_gfx, blit_x, blit_y,
	                  &image_gfx, 0, 0,
	                  blit_w, blit_h);
#else
	/* Enable read-tiling in X and Y for the image */
	video_gfx_setflags(&image_gfx,
	                   video_gfx_getflags(&image_gfx) |
	                   VIDEO_GFX_F_XWRAP | VIDEO_GFX_F_YWRAP);

	unsigned int tiles_x = 3;
	unsigned int tiles_y = 3;
	static video_offset_t dst_offset = 0;


	if (0) { /* Change to "1" to test the tiling engine of the non-stretching blit impl */
		struct video_gfx sized_gfx;
		struct video_buffer *sized_buffer;
#if 0 /* Using this method, pixel conversion only happens once */
		struct video_buffer *format_buf = screen_buffer_asvideo(screen);
#else
		struct video_buffer *format_buf = image;
#endif
		sized_buffer = video_buffer_create(VIDEO_BUFFER_AUTO,
		                                   blit_w / tiles_x,
		                                   blit_h / tiles_y,
		                                   format_buf->vb_format.vf_codec,
		                                   format_buf->vb_format.vf_pal);
		video_buffer_getgfx(sized_buffer, &sized_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_stretch(&sized_gfx, 0, 0, video_gfx_getclipw(&sized_gfx), video_gfx_getcliph(&sized_gfx),
		                  &image_gfx, 0, 0, video_gfx_getclipw(&image_gfx), video_gfx_getcliph(&image_gfx));
		video_buffer_getgfx(sized_buffer, &sized_gfx,
		                    video_gfx_getblend(&image_gfx),
		                    video_gfx_getflags(&image_gfx),
		                    video_gfx_getcolorkey(&image_gfx));
		video_gfx_bitblit(&screen_gfx, blit_x, blit_y, &sized_gfx,
		                  dst_offset + (video_gfx_getclipw(&sized_gfx) / 2),
		                  dst_offset + (video_gfx_getcliph(&sized_gfx) / 2),
		                  blit_w, blit_h);
		video_buffer_decref(sized_buffer);
	} else {
		video_gfx_stretch(&screen_gfx, blit_x, blit_y, blit_w, blit_h,
		                  &image_gfx,
		                  (video_gfx_getclipw(&image_gfx) / 2) + dst_offset * tiles_x,
		                  (video_gfx_getcliph(&image_gfx) / 2) + dst_offset * tiles_y,
		                  video_gfx_getclipw(&image_gfx) * tiles_x,
		                  video_gfx_getcliph(&image_gfx) * tiles_y);
	}

#if 0
	for (unsigned int tile_y = 0; tile_y < tiles_y + 1; ++tile_y) {
		for (unsigned int tile_x = 0; tile_x < tiles_x + 1; ++tile_x) {
			video_dim_t r_w = blit_w / tiles_x;
			video_dim_t r_h = blit_h / tiles_y;
			video_offset_t r_x = blit_x + (tile_x - 2) * r_w;
			video_offset_t r_y = blit_y + (tile_y - 2) * r_h;
			r_x += (((video_gfx_getclipw(&image_gfx) / 2) + dst_offset * tiles_x) * blit_w) / video_gfx_getclipw(&image_gfx);
			r_y += (((video_gfx_getcliph(&image_gfx) / 2) + dst_offset * tiles_y) * blit_h) / video_gfx_getcliph(&image_gfx);
			video_gfx_rect(&screen_gfx, r_x, r_y, r_w, r_h, VIDEO_COLOR_WHITE);
		}
	}
	video_gfx_rect(&screen_gfx, blit_x, blit_y, blit_w, blit_h, VIDEO_COLOR_AQUA);
#endif

	dst_offset += 3;
#endif

	if (font) {
		struct video_fontprinter_data fd;
		fd.vfp_font    = font;
		fd.vfp_gfx     = &screen_gfx;
		fd.vfp_height  = 16;
		fd.vfp_curx    = 0;
		fd.vfp_cury    = 0;
		fd.vfp_lnstart = 0;
		fd.vfp_lnend   = video_gfx_getclipw(&screen_gfx) / 5;
		if (fd.vfp_lnend < 150)
			fd.vfp_lnend = 150;
		fd.vfp_bg_fg_colors[0] = VIDEO_COLOR_BLACK;
		fd.vfp_bg_fg_colors[1] = VIDEO_COLOR_WHITE;

		mbstate_init(&fd.vfp_u8word);
#define gfx_printf(...) format_printf(&video_fontprinter, &fd, __VA_ARGS__)
		gfx_printf("Color test: ");
		fd.vfp_bg_fg_colors[1] = VIDEO_COLOR_RGB(0xff, 0, 0);
		gfx_printf("R");
		fd.vfp_bg_fg_colors[1] = VIDEO_COLOR_RGB(0, 0xff, 0);
		gfx_printf("G");
		fd.vfp_bg_fg_colors[1] = VIDEO_COLOR_RGB(0, 0, 0xff);
		gfx_printf("B");
		fd.vfp_bg_fg_colors[1] = VIDEO_COLOR_WHITE;
		gfx_printf("\n");

		gfx_printf("%s#%u\n", filename, (unsigned int)frameinfo->vaf_frameid);
		dump_buffer_specs(image, &fd);

		gfx_printf("Screen:\n");
		dump_buffer_specs(screen, &fd);
#undef gfx_printf
	}

#if 0
	static bool firsttime = true;
	if (firsttime) {
		firsttime = false;
		/* Create screenshots in a couple of file formats. */
		video_gfx_save(&screen_gfx, "/var/showpic.png", NULL);
//		video_gfx_save(&screen_gfx, "/var/showpic.jpg", NULL);
//		video_gfx_save(&screen_gfx, "/var/showpic.bmp", NULL);
		sync();
	}
#endif
}


int main(int argc, char *argv[]) {
	REF struct video_font *font;
	REF struct screen_buffer *screen;
	REF struct video_display *display = NULL;
	REF struct video_buffer *bscreen;
	REF struct video_anim *anim;
	struct video_anim_frame *frame;
	struct timeval frame_start, frame_end;

	if (argc != 2) {
		printf("Update: showpic FILE\n");
		return 1;
	}

	/* Load default system font */
	font = video_font_lookup(VIDEO_FONT_DEFAULT);

	/* Bind the screen buffer. */
	screen = screen_buffer_create(NULL);
	if (!screen)
		err(EXIT_FAILURE, "Failed to load screen buffer");

#if 0
	{
		struct video_rect rect;
		rect.vr_xmin = 100;
		rect.vr_ymin = 100;
		rect.vr_xdim = screen_buffer_asvideo(screen)->vb_xdim - 200;
		rect.vr_ydim = screen_buffer_asvideo(screen)->vb_ydim - 200;
		bscreen = video_buffer_region(screen_buffer_asvideo(screen), &rect, 0);
		if (!bscreen)
			err(EXIT_FAILURE, "Failed to load screen buffer");
//		video_buffer_revoke(bscreen);
	}
#else
	bscreen = screen_buffer_asvideo(screen);
#endif

#if 1
	{
		struct video_window_position position;
		REF struct video_display *temp_display;
		REF struct video_buffer *buffer;
		REF struct video_compositor *compositor;
		REF struct video_window *window1;
		REF struct video_window *window2;
		/* TODO: This is the wrong way around -- "screen_buffer" shouldn't exist, and
		 *       should actually be  "video_monitor", which extends  "video_display". */
		temp_display = video_display_forbuffer(bscreen);
		if unlikely(!temp_display)
			err(EXIT_FAILURE, "Failed to wrap screen in display");
		compositor = video_compositor_create(temp_display, VIDEO_COMPOSITOR_FEAT_ALL, VIDEO_COLOR_AQUA);
		if unlikely(!compositor)
			err(EXIT_FAILURE, "Failed to allocate compositor");

		position.vwp_over = VIDEO_WINDOW_MOVE_OVER__FOREGROUND;
		position.vwp_attr.vwa_flags = VIDEO_WINDOW_F_PASSTHRU;
		position.vwp_attr.vwa_rect.vr_xmin = 80;
		position.vwp_attr.vwa_rect.vr_ymin = 80;
		position.vwp_attr.vwa_rect.vr_xdim = bscreen->vb_xdim - 160;
		position.vwp_attr.vwa_rect.vr_ydim = bscreen->vb_ydim - 160;
		window1 = video_compositor_newwindow(compositor, &position, NULL);
		if unlikely(!window1)
			err(EXIT_FAILURE, "Failed to allocate window1");

		/* Create a second (small) window to interact with the first (big) one */
		position.vwp_over = VIDEO_WINDOW_MOVE_OVER__FOREGROUND;
		position.vwp_attr.vwa_flags = VIDEO_WINDOW_F_PASSTHRU | VIDEO_WINDOW_F_ALPHA;
		position.vwp_attr.vwa_rect.vr_xmin = 10;
		position.vwp_attr.vwa_rect.vr_ymin = 10;
		position.vwp_attr.vwa_rect.vr_xdim = 200;
		position.vwp_attr.vwa_rect.vr_ydim = 200;
		window2 = video_compositor_newwindow(compositor, &position, NULL);
		if unlikely(!window2)
			err(EXIT_FAILURE, "Failed to allocate window2");

		/* Render some stuff to the second window */
		buffer = video_window_getbuffer(window2);
		if unlikely(!buffer)
			err(EXIT_FAILURE, "Failed to get screen from window2");
		{
			struct video_gfx window2_gfx;
			video_color_t colors[2][2];
			video_buffer_getgfx(buffer, &window2_gfx,
			                    GFX_BLENDMODE_OVERRIDE,
			                    VIDEO_GFX_F_NORMAL, 0);
			colors[0][0] = VIDEO_COLOR_RGBA(0xff, 0, 0, 0xff);
			colors[0][1] = VIDEO_COLOR_RGBA(0, 0xff, 0, 0xff);
			colors[1][0] = VIDEO_COLOR_RGBA(0, 0, 0xff, 0xff);
			colors[1][1] = VIDEO_COLOR_RGBA(0xff, 0xff, 0xff, 0);
			video_gfx_gradient(&window2_gfx, 0, 0,
			                   video_gfx_getclipw(&window2_gfx),
			                   video_gfx_getcliph(&window2_gfx),
			                   colors);
			video_window_updaterect(window2, &RECT_FULL);
		}

		/* Use the first window as output for the main program below... */
		display = video_window_asdisplay(window1);
		bscreen = video_window_getbuffer(window1);
		if unlikely(!bscreen)
			err(EXIT_FAILURE, "Failed to get screen from window1");
	}
#endif

	/* Load the named file as a video buffer. */
	anim = video_anim_open(bscreen->vb_domain, argv[1]);
	if unlikely(!anim)
		err(EXIT_FAILURE, "Failed to open image");

	/* GIF render times (for some random animation I'm using for testing):
	 * - no caching:         ~91% spent sleeping  (=> x10 pixel output possible)
	 * - src format caching: ~95% spent sleeping  (=> x20 pixel output possible)
	 * - dst format caching: ~97% spent sleeping  (=> x30 pixel output possible) */
#if 0
	anim = video_anim_cached(anim, NULL);
#elif 1
	anim = video_anim_cached(anim, &bscreen->vb_format);
#endif
	if unlikely(!anim)
		err(EXIT_FAILURE, "Failed to cache animation");
	frame = (struct video_anim_frame *)malloca(video_anim_sizeof_frame(anim));
	if unlikely(!frame)
		err(EXIT_FAILURE, "Failed to allocate animation frame reader");

	/* Load first frame of a potentially animated image */
	if unlikely(video_anim_firstframe(anim, frame))
		err(EXIT_FAILURE, "Failed to load frame");

	/* Clear screen */
	{
		struct video_gfx screen_gfx;
		video_buffer_getgfx(bscreen, &screen_gfx,
		                    GFX_BLENDMODE_OVERRIDE,
		                    VIDEO_GFX_F_NORMAL, 0);
		video_gfx_fillall(&screen_gfx, VIDEO_COLOR_BLACK);
	}

	/* Render loop */
	gettimeofday(&frame_start, NULL);
	for (;;) {
		struct timeval tv_delay, tv_spent, tv_showfor;
		struct timespec ts_delay;

		/* Render frame */
		do_showpic(bscreen, frame->vaf_frame, font, argv[1], frame);
		if (display) {
			syslog(LOG_DEBUG, "BEGIN: video_display_updaterect()\n");
			video_display_updaterect(display, &RECT_FULL);
			syslog(LOG_DEBUG, "END: video_display_updaterect()\n");
		}
		screen_buffer_updaterect(screen, &CRECT_FULL);

		/* Load next frame as part of render delay */
		tv_showfor = frame->vaf_showfor;
		if (video_anim_nextframe(anim, frame)) {
			/* NOTE: Technically would need to decref the "frame" passed
			 *       as parameter, but we  don't care about leaks  since
			 *       everything gets cleaned up when we exit anyways. */
			err(EXIT_FAILURE, "Failed to load frame at %u",
			    (unsigned int)frame->vaf_frameid);
		}

		/* Wait until the next frame should be rendered */
#if 0
		(void)frame_start;
		(void)frame_end;
		(void)tv_showfor;
		(void)tv_spent;
		(void)tv_delay;
		(void)ts_delay;
		getchar();
#else
		gettimeofday(&frame_end, NULL);
		timeval_sub(&tv_spent, &frame_end, &frame_start);
		timeval_sub(&tv_delay, &tv_showfor, &tv_spent);
		timeval_add(&frame_end, &frame_end, &tv_delay);
		TIMEVAL_TO_TIMESPEC(&tv_delay, &ts_delay);
		frame_start = frame_end;
		if (ts_delay.tv_sec >= 0)
			nanosleep(&ts_delay, NULL);
#endif
	}

#if 0 /* Not necessary; we're about to exit, so this happens automatically */
	video_buffer_decref(bscreen);
	video_buffer_decref(image);
	if (font)
		video_font_decref(font);
#endif
	return 0;
}

DECL_END

#endif /* !GUARD_APPS_SHOWPIC_MAIN_C */
