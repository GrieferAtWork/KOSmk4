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
#define LIBVIDEO_GFX_WANT_PROTOTYPES

#include <hybrid/compiler.h>

#include <hybrid/minmax.h>

#include <err.h>
#include <stddef.h>
#include <sys/syslog.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <libvideo/codec/pixel.h>
#include <libvideo/codec/codecs.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/font.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/gfx/screen.h>

DECL_BEGIN

static struct video_buffer_rect const WHOLE_SCREEN = {
	.vbr_startx = 0,
	.vbr_starty = 0,
	.vbr_sizex  = SIZE_MAX,
	.vbr_sizey  = SIZE_MAX,
};

int main(int argc, char *argv[]) {
	REF struct screen_buffer *screen;
	REF struct video_buffer *image;
	struct video_gfx screen_gfx;
	struct video_gfx image_gfx;
	size_t blit_w, blit_h;
	size_t blit_x, blit_y;

	if (argc != 2) {
		printf("Update: showpic FILE\n");
		return 1;
	}

	/* Load the named file as a video buffer. */
	image = video_buffer_open(argv[1]);
	if unlikely(!image)
		err(EXIT_FAILURE, "Failed to open image");

	/* Bind the screen buffer. */
	screen = screen_buffer_create();
	if (!screen)
		err(EXIT_FAILURE, "Failed to load screen buffer");

#if 1 /* For debugging the same-format blit-scretch function */
	image = video_buffer_convert(image,
	                             ((REF struct video_buffer *)screen)->vb_format.vf_codec,
	                             ((REF struct video_buffer *)screen)->vb_format.vf_pal,
	                             VIDEO_BUFFER_AUTO);
#endif

	/* Load GFX contexts for the image and the screen */
	video_buffer_getgfx((struct video_buffer *)screen, &screen_gfx,
	                    GFX_BLENDINFO_OVERRIDE,
	                    VIDEO_GFX_FNEARESTBLIT, 0);
	video_buffer_getgfx(image, &image_gfx,
	                    GFX_BLENDINFO_OVERRIDE,
	                    VIDEO_GFX_FNORMAL, 0);

	/* Calculate where the image should be displayed */
	blit_w = video_gfx_sizex(&image_gfx);
	blit_h = video_gfx_sizey(&image_gfx);
	if (blit_w > video_gfx_sizex(&screen_gfx)) {
		size_t new_blit_w, new_blit_h;
		/* >> new_blit_w / new_blit_h = blit_w / blit_h;
		 * >> new_blit_w = (blit_w / blit_h) * new_blit_h;
		 * >> new_blit_w / (blit_w / blit_h) = new_blit_h;
		 * >> new_blit_h = new_blit_w / (blit_w / blit_h);
		 * >> new_blit_h = (new_blit_w * blit_h) / blit_w; */
		new_blit_w = video_gfx_sizex(&screen_gfx);
		new_blit_h = ((uint64_t)new_blit_w * blit_h) / blit_w;
		blit_w = new_blit_w;
		blit_h = new_blit_h;
	}

	if (blit_h > video_gfx_sizey(&screen_gfx)) {
		size_t new_blit_w, new_blit_h;
		/* >> new_blit_w / new_blit_h = blit_w / blit_h;
		 * >> new_blit_w = (blit_w / blit_h) * new_blit_h;
		 * >> new_blit_w = (blit_w * new_blit_h) / blit_h; */
		new_blit_h = video_gfx_sizey(&screen_gfx);
		new_blit_w = ((uint64_t)blit_w * new_blit_h) / blit_h;
		blit_w = new_blit_w;
		blit_h = new_blit_h;
	}

	blit_x = (video_gfx_sizex(&screen_gfx) - blit_w) / 2;
	blit_y = (video_gfx_sizey(&screen_gfx) - blit_h) / 2;

	/* Display the image */
	video_gfx_fillall(&screen_gfx, VIDEO_COLOR_BLACK);
	video_gfx_stretch(&screen_gfx, blit_x, blit_y, blit_w, blit_h,
	                  &image_gfx, 0, 0, VIDEO_DIM_MAX, VIDEO_DIM_MAX);
	screen_buffer_updaterect(screen, &WHOLE_SCREEN);

	/* Wait for user input */
	getchar();

#if 0 /* Not necessary; we're about to exit, so this happens automatically */
	video_buffer_decref(image);
	video_buffer_decref((struct video_buffer *)screen);
#endif
	return 0;
}

DECL_END

#endif /* !GUARD_APPS_SHOWPIC_MAIN_C */
