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
#ifndef GUARD_APPS_GFX_MAIN_C
#define GUARD_APPS_GFX_MAIN_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1
#define LIBVIDEO_GFX_WANT_PROTOTYPES

#include <hybrid/compiler.h>

#include <kos/refptr.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <kos/kernel/printk.h>

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <format-printer.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <unicode.h>
#include <unistd.h>

#include <libvideo/codec/pixel.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/font.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/gfx/screen.h>

DECL_BEGIN

PRIVATE void enable_rawtty_mode(void) {
	pid_t cpid;
	struct termios tios;
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
		tcsetattr(STDIN_FILENO, TCSADRAIN, &tios); /* Restore tty mode */
		exit(WEXITSTATUS(status));
	}
	/* Setup raw TTY mode. */
	cfmakeraw(&tios);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &tios);
}


int main(int argc, char *argv[]) {
	bool is_blocking = false;
	REF struct screen_buffer *screen;
	REF struct video_font *font;
	struct video_fontprinter_data fontprinter_data;
	struct video_gfx gfx;
	(void)argc;
	(void)argv;
	srand(time(NULL));

	enable_rawtty_mode();

	/* Load the video-mode font. */
	font = video_font_lookup(VIDEO_FONT_FIXEDWIDTH);
	if (!font)
		err(EXIT_FAILURE, "Failed to load VIDEO_FONT_FIXEDWIDTH");

	/* Bind the screen buffer. */
	screen = screen_buffer_create(NULL);
	if (!screen)
		err(EXIT_FAILURE, "Failed to load screen buffer");
	screen->getgfx(gfx,
	               GFX_BLENDMODE_ALPHA,
	               VIDEO_GFX_FLINEARBLIT |
	               VIDEO_GFX_FRDXWRAP |
	               VIDEO_GFX_FRDYWRAP |
	               VIDEO_GFX_FWRXWRAP |
	               VIDEO_GFX_FWRYWRAP);

	fontprinter_data.vfp_height  = 16;
	fontprinter_data.vfp_font    = font;
	fontprinter_data.vfp_lnstart = 0;
	fontprinter_data.vfp_color   = VIDEO_COLOR_BLACK;
	mbstate_init(&fontprinter_data.vfp_u8word);

	int render_mode = 0;
again_font:

	struct video_gfx fontgfx;
	fontgfx = gfx;
	if (render_mode == 0) {
		/* Upper half + lower half */
		fontgfx.clip(0, 0, VIDEO_DIM_MAX, VIDEO_DIM_MAX);
		fontprinter_data.vfp_cury = 0;
	} else if (render_mode == 1) {
		/* lower half only (plus additional lines) */
		fontgfx.clip(0,
		             fontprinter_data.vfp_height / 2,
		             VIDEO_DIM_MAX,
		             VIDEO_DIM_MAX);
		fontprinter_data.vfp_cury = -(video_offset_t)(fontprinter_data.vfp_height / 2);
	} else {
		/* upper half only */
		fontgfx.clip(0, 0, VIDEO_DIM_MAX, fontprinter_data.vfp_height / 2);
		fontprinter_data.vfp_cury = 0;
	}
	fontprinter_data.vfp_gfx   = &fontgfx;
	fontprinter_data.vfp_lnend = video_gfx_getclipw(&fontgfx);
	fontprinter_data.vfp_curx  = 0;

	printk(KERN_DEBUG "GFX: BEGIN RENDER\n");
	gfx.fill(VIDEO_COLOR_WHITE);
	printk(KERN_DEBUG "GFX: AFTER FILL\n");
	format_printf(&video_fontprinter,
	              &fontprinter_data,
//	              "Hello World!\n"
//	              "ℋℌℍℎℏ\n"
//	              "⌚⌛\n"
	              "─━│┃┄┅┆┇┈┉┊┋┌┍┎┏\n"
	              "┐┑┒┓└┕┖┗┘┙┚┛├┝┞┟\n"
	              "┠┡┢┣┤┥┦┧┨┩┪┫┬┭┮┯\n"
	              "┰┱┲┳┴┵┶┷┸┹┺┻┼┽┾┿\n"
	              "╀╁╂╃╄╅╆╇╈╉╊╋╌╍╎╏\n"
	              "═║╒╓╔╕╖╗╘╙╚╛╜╝╞╟\n"
	              "╠╡╢╣╤╥╦╧╨╩╪╫╬╭╮╯\n"
	              "╰╱╲╳╴╵╶╷╸╹╺╻╼╽╾╿\n"

	              "▀▁▂▃▄▅▆▇█▉▊▋▌▍▎▏\n"
	              "▐░▒▓▔▕▖▗▘▙▚▛▜▝▞▟\n");
	printk(KERN_DEBUG "GFX: DONE RENDER\n");

	for (;;) {
		char buf[1];
		screen->updaterect();
		if (read(STDIN_FILENO, buf, 1) < 1)
			break;
		if (buf[0] == '+') {
			++fontprinter_data.vfp_height;
		} else if (buf[0] == '-') {
			--fontprinter_data.vfp_height;
		} else if (buf[0] == 'm') {
			render_mode = (render_mode + 1) % 3;
		} else if (buf[0] == 's') {
			screen->getgfx(gfx, gfx.vx_blend,
			               gfx.vx_flags ^ VIDEO_GFX_FLINEARBLIT);
		} else if (buf[0] == 'd') {
			screen->getgfx(gfx, gfx.vx_blend,
			               gfx.vx_flags ^ (VIDEO_GFX_FRDXWRAP |
			                               VIDEO_GFX_FRDYWRAP |
			                               VIDEO_GFX_FWRXWRAP |
			                               VIDEO_GFX_FWRYWRAP));
		} else if (buf[0] == 'p') {
			video_buffer_save(screen, "/var/screen.png", NULL);
		} else if (buf[0] == 'q') {
			break;
		}
		goto again_font;
	}

	fcntl(STDIN_FILENO, F_SETFL,
	      fcntl(STDIN_FILENO, F_GETFL) |
	      O_NONBLOCK);

	gfx.clip(-16,
	         -16,
	         VIDEO_DIM_MAX,
	         VIDEO_DIM_MAX);

	for (;;) {
		unsigned int action;
		ssize_t error;
		char buf[1];
		video_color_t color;
		screen->updaterect();
		error = read(STDIN_FILENO, buf, 1);
		if (error == 1) {
			switch (buf[0]) {

			case 'q':
				exit(0);

			case 'c':
				gfx.fill(VIDEO_COLOR_WHITE);
				continue;

			case 'v':
				gfx.fill(VIDEO_COLOR_BLACK);
				continue;

			case 'w': {
				int mode;
				mode = fcntl(STDIN_FILENO, F_GETFL);
				mode ^= O_NONBLOCK;
				fcntl(STDIN_FILENO, F_SETFL, mode);
				is_blocking = (mode & O_NONBLOCK) == 0;
			}	break;

			case 's':
				goto random_step;

			case 'd':
				screen->getgfx(gfx, gfx.vx_blend,
				               gfx.vx_flags ^ (VIDEO_GFX_FRDXWRAP |
				                               VIDEO_GFX_FRDYWRAP |
				                               VIDEO_GFX_FWRXWRAP |
				                               VIDEO_GFX_FWRYWRAP));
				break;

			case '0' ... '9':
				action = buf[0] - '0';
				goto step;

			case 'p':
				video_buffer_save(screen, "/var/screen.jpg", NULL);
				video_buffer_save(screen, "/var/screen.png", NULL);
				video_buffer_save(screen, "/var/screen.bmp", NULL);
				break;

			default: break;
			}
		}
		if (is_blocking)
			continue;
random_step:
		action = rand() % 8;
step:
		color = VIDEO_COLOR_RGBA(rand() % 256,
		                         rand() % 256,
		                         rand() % 256,
		                         rand() % 256);
		switch (action) {

		case 0: {
			gfx.rect((rand() % screen->vb_xdim) - 16,
			         (rand() % screen->vb_ydim) - 16,
			         rand() % screen->vb_xdim,
			         rand() % screen->vb_ydim,
			         color);
		}	break;

		case 1: {
			gfx.fill((rand() % screen->vb_xdim) - 16,
			         (rand() % screen->vb_ydim) - 16,
			         rand() % screen->vb_xdim,
			         rand() % screen->vb_ydim,
			         color);
		}	break;

		case 2: {
			gfx.stretch((rand() % screen->vb_xdim) - 16,
			            (rand() % screen->vb_ydim) - 16,
			            rand() % screen->vb_xdim,
			            rand() % screen->vb_ydim,
			            gfx,
			            (rand() % screen->vb_xdim) - 16,
			            (rand() % screen->vb_ydim) - 16,
			            rand() % screen->vb_xdim,
			            rand() % screen->vb_ydim);
		}	break;

		case 3: {
			struct video_gfx blurgfx;
			video_offset_t x = (rand() % screen->vb_xdim) - 16;
			video_offset_t y = (rand() % screen->vb_ydim) - 16;
			video_coord_t size_x = rand() % screen->vb_xdim;
			video_coord_t size_y = rand() % screen->vb_ydim;
			screen->getgfx(blurgfx,
			               gfx.vx_blend,
			               gfx.vx_flags | VIDEO_GFX_FBLUR,
			               gfx.vx_colorkey);
			blurgfx.clip(video_gfx_getclipx(&gfx),
			             video_gfx_getclipy(&gfx),
			             video_gfx_getclipw(&gfx),
			             video_gfx_getcliph(&gfx));
			gfx.blit((video_offset_t)x - gfx.vx_hdr.vxh_cxoff,
			         (video_offset_t)y - gfx.vx_hdr.vxh_cyoff,
			         blurgfx,
			         (video_offset_t)x - gfx.vx_hdr.vxh_cxoff,
			         (video_offset_t)y - gfx.vx_hdr.vxh_cyoff,
			         size_x,
			         size_y);
			gfx.rect((video_offset_t)x - gfx.vx_hdr.vxh_cxoff,
			         (video_offset_t)y - gfx.vx_hdr.vxh_cyoff,
			         size_x,
			         size_y,
			         VIDEO_COLOR_BLACK);
		}	break;

		case 4: {
			video_offset_t x = (rand() % screen->vb_xdim) - 16;
			video_offset_t y = (rand() % screen->vb_ydim) - 16;
			video_coord_t size_x = rand() % screen->vb_xdim;
			video_coord_t size_y = rand() % screen->vb_ydim;
			video_color_t colors[2][2];
			colors[0][0] = VIDEO_COLOR_RGBA(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
			colors[0][1] = VIDEO_COLOR_RGBA(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
			colors[1][0] = VIDEO_COLOR_RGBA(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
			colors[1][1] = VIDEO_COLOR_RGBA(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
			gfx.gradient(x, y, size_x, size_y, colors);
		}	break;

		case 5: {
			video_offset_t x = (rand() % screen->vb_xdim) - 16;
			video_offset_t y = (rand() % screen->vb_ydim) - 16;
			video_coord_t size_x = rand() % screen->vb_xdim;
			video_coord_t size_y = rand() % screen->vb_ydim;
			video_color_t locolor = VIDEO_COLOR_RGBA(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
			video_color_t hicolor = VIDEO_COLOR_RGBA(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
			gfx.hgradient(x, y, size_x, size_y, locolor, hicolor);
		}	break;

		case 6: {
			video_offset_t x = (rand() % screen->vb_xdim) - 16;
			video_offset_t y = (rand() % screen->vb_ydim) - 16;
			video_coord_t size_x = rand() % screen->vb_xdim;
			video_coord_t size_y = rand() % screen->vb_ydim;
			video_color_t locolor = VIDEO_COLOR_RGBA(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
			video_color_t hicolor = VIDEO_COLOR_RGBA(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
			gfx.vgradient(x, y, size_x, size_y, locolor, hicolor);
		}	break;

		default:
			gfx.line(rand() % screen->vb_xdim,
			         rand() % screen->vb_ydim,
			         rand() % screen->vb_xdim,
			         rand() % screen->vb_ydim,
			         color);
			break;
		}
	}
	return 0;
}

DECL_END

#endif /* !GUARD_APPS_GFX_MAIN_C */
