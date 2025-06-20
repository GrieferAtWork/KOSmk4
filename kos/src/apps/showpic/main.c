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
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#define _TIME_T_BITS 64

#include <hybrid/compiler.h>

#include <hybrid/align.h>

#include <kos/kernel/printk.h>
#include <sys/time.h>

#include <err.h>
#include <format-printer.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <timeval-utils.h>
#include <uchar.h>
#include <unistd.h>

#include <libvideo/codec/codecs.h>
#include <libvideo/codec/palette.h>
#include <libvideo/codec/pixel.h>
#include <libvideo/gfx/anim.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/font.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/gfx/screen.h>

DECL_BEGIN

static struct video_buffer_rect const WHOLE_SCREEN = {
	.vbr_startx = 0,
	.vbr_starty = 0,
	.vbr_sizex  = VIDEO_DIM_MAX,
	.vbr_sizey  = VIDEO_DIM_MAX,
};

static void
do_dump_buffer_specs(struct video_buffer *buf,
                     struct video_fontprinter_data *io) {
	struct video_codec const *codec;
	struct video_palette const *palette;
#define gfx_printf(...) format_printf(&video_fontprinter, io, __VA_ARGS__)
	gfx_printf("res:   %ux%u\n", (unsigned int)buf->vb_size_x, (unsigned int)buf->vb_size_y);
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
		               io->vfp_color);
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
	               io->vfp_color);
	io->vfp_cury += padding;
}

static ATTR_UNUSED REF struct video_buffer *
palettize(struct video_buffer *self, video_pixel_t num_colors, unsigned int method) {
	struct video_gfx gfx;
	struct video_gfx result_gfx;
	REF struct video_palette *pal;
	REF struct video_buffer *result;
	struct video_codec const *result_codec;
	video_codec_t result_codec_id;

	/* Create palette with the requested # of colors */
	pal = video_palette_create(num_colors);
	if unlikely(!pal)
		goto err;

	/* Acquire GFX context for source video buffer */
	video_buffer_getgfx(self, &gfx,
	                    GFX_BLENDMODE_OVERRIDE,
	                    VIDEO_GFX_FNORMAL, 0);

	/* Palettize source video buffer and store results in "pal" */
	if unlikely(video_gfx_palettize(&gfx, num_colors, pal->vp_pal, method))
		goto err_pal;
	pal = video_palette_optimize(pal);

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
	result_codec = video_codec_lookup(result_codec_id);
	if unlikely(!result_codec)
		goto err_pal;

	/* Allocate result buffer */
	result = video_buffer_create(VIDEO_BUFFER_AUTO,
	                             video_gfx_getclipw(&gfx),
	                             video_gfx_getcliph(&gfx),
	                             result_codec, pal);
	if unlikely(!result)
		goto err_pal;
	video_palette_decref(pal);

	/* Blit source GFX context onto result video_buffer. */
	video_buffer_getgfx(result, &result_gfx,
	                    GFX_BLENDMODE_OVERRIDE,
	                    VIDEO_GFX_FNORMAL, 0);
	video_gfx_blit(&result_gfx, 0, 0, &gfx, 0, 0,
	               video_gfx_getclipw(&gfx),
	               video_gfx_getcliph(&gfx));
	return result;
/*
err_pal_r:
	video_buffer_decref(result);*/
err_pal:
	video_palette_decref(pal);
err:
	return NULL;
}


static void
do_showpic(struct screen_buffer *screen,
           struct video_buffer *image,
           struct video_font *font,
           char const *filename,
           struct video_anim_frameinfo *frameinfo) {
	struct video_gfx screen_gfx;
	struct video_gfx image_gfx;
	size_t blit_w, blit_h;
	size_t blit_x, blit_y;
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
	video_buffer_getgfx(screen_buffer_asvideo(screen), &screen_gfx,
	                    GFX_BLENDMODE_OVERRIDE,
	                    VIDEO_GFX_FLINEARBLIT, 0);
	video_buffer_getgfx(image, &image_gfx,
	                    GFX_BLENDMODE_OVERRIDE,
	                    VIDEO_GFX_FNORMAL/* |
	                    VIDEO_GFX_FRDXWRAP |
	                    VIDEO_GFX_FRDYWRAP*/,
	                    0);

	/* Calculate where the image should be displayed */
	blit_w = video_gfx_getclipw(&image_gfx);
	blit_h = video_gfx_getcliph(&image_gfx);
	if (blit_w > video_gfx_getclipw(&screen_gfx)) {
		size_t new_blit_w, new_blit_h;
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
		size_t new_blit_w, new_blit_h;
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
	printk(KERN_DEBUG "SHOWPIC: BEGIN\n");
#if 1
	video_gfx_stretch(&screen_gfx, blit_x, blit_y, blit_w, blit_h,
	                  &image_gfx, 0, 0,
	                  video_gfx_getclipw(&image_gfx),
	                  video_gfx_getcliph(&image_gfx));
#else
	if (0) { /* Change to "1" to test the tiling engine of the non-stretching blit impl */
		struct video_gfx sized_gfx;
		struct video_buffer *sized_buffer;
#if 0 /* Using this method, pixel conversion only happens once */
		struct video_buffer *format_buf = screen_buffer_asvideo(screen);
#else
		struct video_buffer *format_buf = image;
#endif
		sized_buffer = video_buffer_create(VIDEO_BUFFER_AUTO,
		                                   blit_w / 3,
		                                   blit_h / 3,
		                                   format_buf->vb_format.vf_codec,
		                                   format_buf->vb_format.vf_pal);
		video_buffer_getgfx(sized_buffer, &sized_gfx, image_gfx.vx_blend,
		                    image_gfx.vx_flags, image_gfx.vx_colorkey);
		video_gfx_stretch(&sized_gfx, 0, 0, sized_gfx.vx_hdr.vxh_cxsiz, sized_gfx.vx_hdr.vxh_cysiz,
		                  &image_gfx, 0, 0, image_gfx.vx_hdr.vxh_cxsiz, image_gfx.vx_hdr.vxh_cysiz);
		video_gfx_blit(&screen_gfx, blit_x, blit_y, &sized_gfx,
		               sized_gfx.vx_hdr.vxh_cxsiz / 2, sized_gfx.vx_hdr.vxh_cysiz / 2,
		               blit_w, blit_h);
		video_buffer_decref(sized_buffer);
	} else {
		video_gfx_stretch(&screen_gfx, blit_x, blit_y, blit_w, blit_h,
		                  &image_gfx,
		                  video_gfx_getclipw(&image_gfx) / 2,
		                  video_gfx_getcliph(&image_gfx) / 2,
		                  video_gfx_getclipw(&image_gfx) * 3,
		                  video_gfx_getcliph(&image_gfx) * 3);
	}
#endif
	printk(KERN_DEBUG "SHOWPIC: END\n");

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
		fd.vfp_color = VIDEO_COLOR_WHITE;
		mbstate_init(&fd.vfp_u8word);
#define gfx_printf(...) format_printf(&video_fontprinter, &fd, __VA_ARGS__)
		gfx_printf("Color test: ");
		fd.vfp_color = VIDEO_COLOR_RGB(0xff, 0, 0);
		gfx_printf("R");
		fd.vfp_color = VIDEO_COLOR_RGB(0, 0xff, 0);
		gfx_printf("G");
		fd.vfp_color = VIDEO_COLOR_RGB(0, 0, 0xff);
		gfx_printf("B");
		fd.vfp_color = VIDEO_COLOR_WHITE;
		gfx_printf("\n");

		gfx_printf("%s#%u\n", filename, (unsigned int)frameinfo->vafi_frameid);
		dump_buffer_specs(image, &fd);

		gfx_printf("Screen:\n");
		dump_buffer_specs(screen_buffer_asvideo(screen), &fd);
#undef gfx_printf
	}

	screen_buffer_updaterect(screen, &WHOLE_SCREEN);
}


int main(int argc, char *argv[]) {
	bool firsttime = true;
	REF struct video_font *font;
	REF struct screen_buffer *screen;
	REF struct video_buffer *frame;
	REF struct video_anim *anim;
	struct video_anim_frameinfo frame_info;
	struct video_anim_frameinfo frame_nextinfo;
	struct timeval frame_start, frame_end;

	if (argc != 2) {
		printf("Update: showpic FILE\n");
		return 1;
	}

	/* Load default system font */
	font = video_font_lookup(VIDEO_FONT_DEFAULT);
	if unlikely(!font)
		err(EXIT_FAILURE, "Failed to load default font");

	/* Load the named file as a video buffer. */
	anim = video_anim_open(argv[1]);
	if unlikely(!anim)
		err(EXIT_FAILURE, "Failed to open image");

	/* Load first frame of a potentially animated image */
	frame = video_anim_firstframe(anim, &frame_info);
	if unlikely(!frame)
		err(EXIT_FAILURE, "Failed to load frame");

	/* Bind the screen buffer. */
	screen = screen_buffer_create(NULL);
	if (!screen)
		err(EXIT_FAILURE, "Failed to load screen buffer");

	/* Clear screen */
	{
		struct video_gfx screen_gfx;
		video_buffer_getgfx(screen_buffer_asvideo(screen), &screen_gfx,
		                    GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_FNORMAL, 0);
		video_gfx_fillall(&screen_gfx, VIDEO_COLOR_BLACK);
	}

	/* Render loop */
	gettimeofday(&frame_start, NULL);
	for (;;) {
		struct timeval tv_delay, tv_spent;
		struct timespec ts_delay;

		/* Render frame */
		do_showpic(screen, frame, font, argv[1], &frame_info);
		if (firsttime) {
			firsttime = false;
			/* Create screenshots in a couple of file formats. */
			/*video_buffer_save(screen_buffer_asvideo(screen), "/var/showpic.png", NULL);
			video_buffer_save(screen_buffer_asvideo(screen), "/var/showpic.jpg", NULL);
			video_buffer_save(screen_buffer_asvideo(screen), "/var/showpic.bmp", NULL);
			sync();
			getchar();*/
		}

		/* Load next frame as part of render delay */
		frame_nextinfo = frame_info;
		frame = video_anim_nextframe(anim, frame, &frame_nextinfo);
		if (!frame) {
			/* NOTE: Technically would need to decref the "frame" passed
			 *       as parameter, but we  don't care about leaks  since
			 *       everything gets cleaned up when we exit anyways. */
			err(EXIT_FAILURE, "Failed to load frame after %u",
			    (unsigned int)frame_info.vafi_frameid);
		}

		/* Wait until the next frame should be rendered */
#if 0
		getchar();
#else
		gettimeofday(&frame_end, NULL);
		timeval_sub(&tv_spent, &frame_end, &frame_start);
		timeval_sub(&tv_delay, &frame_info.vafi_showfor, &tv_spent);
		timeval_add(&frame_end, &frame_end, &tv_delay);
		TIMEVAL_TO_TIMESPEC(&tv_delay, &ts_delay);
		frame_start = frame_end;
		frame_info  = frame_nextinfo;
		if (ts_delay.tv_sec >= 0)
			nanosleep(&ts_delay, NULL);
#endif
	}

#if 0 /* Not necessary; we're about to exit, so this happens automatically */
	video_buffer_decref(screen_buffer_asvideo(screen));
	video_buffer_decref(image);
	video_font_decref(font);
#endif
	return 0;
}

DECL_END

#endif /* !GUARD_APPS_SHOWPIC_MAIN_C */
