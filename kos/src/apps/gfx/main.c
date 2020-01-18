/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_APPS_GFX_MAIN_C
#define GUARD_APPS_GFX_MAIN_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1
#define LIBVIDEO_GFX_WANT_PROTOTYPES 1

#include <hybrid/compiler.h>

#include <kos/ioctl/video.h>
#include <kos/refptr.h>
#include <kos/types.h>
#include <linux/kd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/wait.h>

#include <format-printer.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/font.h>
#include <libvideo/gfx/gfx.h>

DECL_BEGIN

PRIVATE void enable_graphics_mode(void) {
	fd_t driver;
	pid_t cpid;
	struct termios tios;
	driver = video_driver();
	if (driver < 0)
		err(EXIT_FAILURE, "Failed to open driver driver");
	cpid = fork();
	if (cpid < 0)
		err(EXIT_FAILURE, "fork() failed");
	tcgetattr(STDIN_FILENO, &tios);
	if (cpid != 0) {
		/* Parent process...
		 * -> Wait for the child to exit (likely to the user pressing CTRL+C) */
		int status;
		while (waitpid(cpid, &status, 0) == -1 && errno == EINTR)
			;
		tcsetpgrp(STDIN_FILENO, 0);
		ioctl(STDOUT_FILENO, KDSETMODE, KD_TEXT); /* Restore text mode */
		tcsetattr(STDIN_FILENO, TCSADRAIN, &tios); /* Restore tty mode */
		exit(WEXITSTATUS(status));
	}
	/* Become our own process group. */
	setpgrp();
	/* Make ourself the foreground process (so we'll receive CTRL+C). */
	tcsetpgrp(STDIN_FILENO, 0);
	/* Setup raw TTY mode. */
	cfmakeraw(&tios);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &tios);
	/* Actually do the switch to graphics mode.
	 * NOTE: The proper way of doing this would be to use `VIDEOIO_SETFORMAT',
	 *       however then we'd have to decide on which graphics mode to use
	 *       ourself, rather than simply letting the kernel decide on one. */
	if (ioctl(driver, KDSETMODE, KD_GRAPHICS) < 0)
		err(EXIT_FAILURE, "ioctl(KDSETMODE, KD_GRAPHICS) failed");
}

int main(int argc, char *argv[]) {
	bool is_blocking = false;
	kos::refptr<struct video_buffer> screen;
	kos::refptr<struct video_font> font;
	struct video_fontprinter_data fontprinter_data;
	struct video_gfx gfx;
	(void)argc;
	(void)argv;
	srand(time(NULL));

	/* Load the video-mode font. */
	font = kos::inherit(video_font_lookup(VIDEO_FONT_FIXEDWIDTH));
	if (!font)
		err(EXIT_FAILURE, "Failed to load VIDEO_FONT_FIXEDWIDTH");

	/* Enable graphics mode. */
	enable_graphics_mode();

	/* Bind the screen buffer. */
	screen = kos::inherit(video_buffer_screen());
	screen->gfx(gfx,
	            GFX_BLENDINFO_ALPHA,
	            VIDEO_GFX_FLINEARBLIT,
	            0,
	            NULL);

	fontprinter_data.vfp_height  = 20;
	fontprinter_data.vfp_font    = font;
	fontprinter_data.vfp_gfx     = &gfx;
	fontprinter_data.vfp_lnstart = 0;
	fontprinter_data.vfp_lnend   = gfx.vx_size_x;
	fontprinter_data.vfp_color   = VIDEO_COLOR_BLACK;
	fontprinter_data.vfp_u8word  = 0;

again_font:
	gfx.fill(0, 0,
	         screen->vb_size_x,
	         screen->vb_size_y,
	         VIDEO_COLOR_WHITE);
	fontprinter_data.vfp_curx = 0;
	fontprinter_data.vfp_cury = 0;
	format_printf(&video_fontprinter,
	              &fontprinter_data,
	              "Hello World!\n"
	              "Second line");

	for (;;) {
		char buf[1];
		if (read(STDIN_FILENO, buf, 1) < 1)
			break;
		if (buf[0] == '+') {
			++fontprinter_data.vfp_height;
		} else if (buf[0] == '-') {
			--fontprinter_data.vfp_height;
		} else if (buf[0] == 's') {
			screen->gfx(gfx,
			            GFX_BLENDINFO_ALPHA,
			            gfx.vx_flags ^ VIDEO_GFX_FLINEARBLIT,
			            0,
			            NULL);
		} else if (buf[0] == 'q') {
			break;
		}
		goto again_font;
	}

	fcntl(STDIN_FILENO, F_SETFL,
	      fcntl(STDIN_FILENO, F_GETFL) |
	      O_NONBLOCK);

	for (;;) {
		ssize_t error;
		char buf[1];
		video_color_t color;
		error = read(STDIN_FILENO, buf, 1);
		if (error == 1) {
			switch (buf[0]) {

			case 'q':
				exit(0);

			case 'c':
				gfx.fill(0, 0,
				         screen->vb_size_x,
				         screen->vb_size_y,
				         VIDEO_COLOR_WHITE);
				continue;

			case 'v':
				gfx.fill(0, 0,
				         screen->vb_size_x,
				         screen->vb_size_y,
				         VIDEO_COLOR_BLACK);
				continue;

			case 'w': {
				int mode;
				mode = fcntl(STDIN_FILENO, F_GETFL);
				mode ^= O_NONBLOCK;
				fcntl(STDIN_FILENO, F_SETFL, mode);
				is_blocking = (mode & O_NONBLOCK) == 0;
			}	break;

			case 's':
				goto step;

			default: break;
			}
		}
		if (is_blocking)
			continue;
step:
		color = VIDEO_COLOR_RGBA(rand() % 256,
		                         rand() % 256,
		                         rand() % 256,
		                         rand() % 256);
		switch (rand() % 4) {

		case 0:
			gfx.rect(rand() % screen->vb_size_x,
			         rand() % screen->vb_size_y,
			         rand() % screen->vb_size_x,
			         rand() % screen->vb_size_y,
			         color);
			break;

		case 1:
			gfx.fill(rand() % screen->vb_size_x,
			         rand() % screen->vb_size_y,
			         rand() % screen->vb_size_x,
			         rand() % screen->vb_size_y,
			         color);
			break;

		case 2:
			gfx.stretch(rand() % screen->vb_size_x,
			            rand() % screen->vb_size_y,
			            rand() % screen->vb_size_x,
			            rand() % screen->vb_size_y,
			            gfx,
			            rand() % screen->vb_size_x,
			            rand() % screen->vb_size_y,
			            rand() % screen->vb_size_x,
			            rand() % screen->vb_size_y);
			break;

		default:
			gfx.line(rand() % screen->vb_size_x,
			         rand() % screen->vb_size_y,
			         rand() % screen->vb_size_x,
			         rand() % screen->vb_size_y,
			         color);
			break;
		}
	}
	return 0;
}

DECL_END

#endif /* !GUARD_APPS_GFX_MAIN_C */
