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

#include <libvideo/color.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/font.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/gfx/screen.h>
#include <libvideo/gfx/surface.h>

DECL_BEGIN

#if 1
#define rand_color() \
	VIDEO_COLOR_RGBA(rand() % 256, rand() % 256, rand() % 256, rand() % 256)
#else
#define rand_color() \
	VIDEO_COLOR_RGB(rand() % 256, rand() % 256, rand() % 256)
#endif

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

	/* Bind the screen buffer. */
	screen = screen_buffer_create(NULL);
	if (!screen)
		err(EXIT_FAILURE, "Failed to load screen buffer");
	video_buffer_getgfx(screen, &gfx, GFX_BLENDMODE_ALPHA);

	/* Load the video-mode font. */
	font = video_font_lookup(video_gfx_getdomain(&gfx),
	                         VIDEO_FONT_FIXEDWIDTH);
	if (!font)
		err(EXIT_FAILURE, "Failed to load VIDEO_FONT_FIXEDWIDTH");

	fontprinter_data.vfp_height          = 16;
	fontprinter_data.vfp_font            = font;
	fontprinter_data.vfp_lnstart         = 0;
//	fontprinter_data.vfp_bg_fg_colors[0] = VIDEO_COLOR_BLACK & ~VIDEO_COLOR_ALPHA_MASK;
	fontprinter_data.vfp_bg_fg_colors[0] = VIDEO_COLOR_WHITE;
	fontprinter_data.vfp_bg_fg_colors[1] = VIDEO_COLOR_BLACK;
	mbstate_init(&fontprinter_data.vfp_u8word);

	gfx.fill(fontprinter_data.vfp_bg_fg_colors[0]);
	int render_mode = 0;
again_font:

	struct video_gfx fontgfx;
	fontgfx = gfx;
	if (render_mode == 0) {
		/* Upper half + lower half */
		fontgfx.clip(0, 0, video_gfx_getxdim(&gfx), video_gfx_getydim(&gfx));
		fontprinter_data.vfp_cury = 0;
	} else if (render_mode == 1) {
		/* lower half only (plus additional lines) */
		fontgfx.clip(0,
		             fontprinter_data.vfp_height / 2,
		             video_gfx_getxdim(&gfx),
		             video_gfx_getydim(&gfx) - (fontprinter_data.vfp_height / 2));
		fontprinter_data.vfp_cury = -(video_offset_t)(fontprinter_data.vfp_height / 2);
	} else {
		/* upper half only */
		fontgfx.clip(0, 0,
		             video_gfx_getxdim(&gfx),
		             fontprinter_data.vfp_height / 2);
		fontprinter_data.vfp_cury = 0;
	}
	fontprinter_data.vfp_gfx   = &fontgfx;
	fontprinter_data.vfp_lnend = video_gfx_getxdim(&fontgfx);
	fontprinter_data.vfp_curx  = 0;

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
	/* Clear screen beyond text area */
	fontgfx.fill(fontprinter_data.vfp_curx, fontprinter_data.vfp_cury,
	             video_gfx_getxdim(&fontgfx) - fontprinter_data.vfp_curx,
	             video_gfx_getydim(&fontgfx) - fontprinter_data.vfp_cury,
	             fontprinter_data.vfp_bg_fg_colors[0]);

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
			video_gfx_toggleflags(&gfx, VIDEO_GFX_F_LINEAR);
		} else if (buf[0] == 'd') {
			video_gfx_toggleflags(&gfx, VIDEO_GFX_F_XWRAP | VIDEO_GFX_F_YWRAP);
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
	         video_gfx_getxdim(&gfx) + 32,
	         video_gfx_getydim(&gfx) + 32);

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

			case 'h': {
				video_dim_t i;
				video_color_t color = rand_color();
				/* TODO: The quadrants of the image this produces aren't all identical
				 *       (something must be wrong somewhere in the line drawing  also) */
				for (i = 0; i < video_gfx_getxdim(&gfx); ++i)
					gfx.line(i, 0, (video_gfx_getxdim(&gfx) - 1) - i, video_gfx_getydim(&gfx) - 1, color);
				for (i = 0; i < video_gfx_getydim(&gfx); ++i)
					gfx.line(0, i, video_gfx_getxdim(&gfx) - 1, (video_gfx_getydim(&gfx) - 1) - i, color);
			}	continue;

			case 'j': {
				video_dim_t i;
				video_offset_t x1 = rand() % video_gfx_getxdim(&gfx);
				video_offset_t y1 = rand() % video_gfx_getydim(&gfx);
				video_color_t color = rand_color();
				for (i = 0; i < 100; ++i) {
					video_dim_t xm = (x1 <= 0 ? 0 : x1) ?: 1;
					video_dim_t xp = (video_dim_t)(x1 >= (video_offset_t)video_gfx_getxdim(&gfx) ? 0 : (video_offset_t)video_gfx_getxdim(&gfx) - x1) ?: 1;
					video_dim_t ym = (y1 <= 0 ? 0 : y1) ?: 1;
					video_dim_t yp = (video_dim_t)(y1 >= (video_offset_t)video_gfx_getydim(&gfx) ? 0 : (video_offset_t)video_gfx_getydim(&gfx) - y1) ?: 1;
					int xsign = (rand() % (video_gfx_getxdim(&gfx))) < xm ? -1 : 1;
					int ysign = (rand() % (video_gfx_getydim(&gfx))) < ym ? -1 : 1;
					video_offset_t x2 = x1 + (xsign * (rand() % (xsign < 0 ? xm : xp)));
					video_offset_t y2 = y1 + (ysign * (rand() % (ysign < 0 ? ym : yp)));
					gfx.line(x1, y1, x2, y2, color);
					x1 = x2;
					y1 = y2;
				}
			}	continue;

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
				video_gfx_toggleflags(&gfx, VIDEO_GFX_F_XWRAP | VIDEO_GFX_F_YWRAP);
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
		color = rand_color();
		switch (action) {

		case 0: {
			gfx.rect((rand() % video_gfx_getxdim(&gfx)) - 16,
			         (rand() % video_gfx_getydim(&gfx)) - 16,
			         rand() % video_gfx_getxdim(&gfx),
			         rand() % video_gfx_getydim(&gfx),
			         color);
		}	break;

		case 1: {
			gfx.fill((rand() % video_gfx_getxdim(&gfx)) - 16,
			         (rand() % video_gfx_getydim(&gfx)) - 16,
			         rand() % video_gfx_getxdim(&gfx),
			         rand() % video_gfx_getydim(&gfx),
			         color);
		}	break;

		case 2: {
			gfx.stretch((rand() % video_gfx_getxdim(&gfx)) - 16,
			            (rand() % video_gfx_getydim(&gfx)) - 16,
			            rand() % video_gfx_getxdim(&gfx),
			            rand() % video_gfx_getydim(&gfx),
			            gfx,
			            (rand() % video_gfx_getxdim(&gfx)) - 16,
			            (rand() % video_gfx_getydim(&gfx)) - 16,
			            rand() % video_gfx_getxdim(&gfx),
			            rand() % video_gfx_getydim(&gfx));
		}	break;

		case 3: {
			video_offset_t x = (rand() % video_gfx_getxdim(&gfx)) - 16;
			video_offset_t y = (rand() % video_gfx_getydim(&gfx)) - 16;
			video_coord_t size_x = rand() % video_gfx_getxdim(&gfx);
			video_coord_t size_y = rand() % video_gfx_getydim(&gfx);
			video_color_t colors[2][2];
			colors[0][0] = rand_color();
			colors[0][1] = rand_color();
			colors[1][0] = rand_color();
			colors[1][1] = rand_color();
			gfx.gradient(x, y, size_x, size_y, colors);
		}	break;

		case 4: {
			video_offset_t x = (rand() % video_gfx_getxdim(&gfx)) - 16;
			video_offset_t y = (rand() % video_gfx_getydim(&gfx)) - 16;
			video_coord_t size_x = rand() % video_gfx_getxdim(&gfx);
			video_coord_t size_y = rand() % video_gfx_getydim(&gfx);
			video_color_t locolor = rand_color();
			video_color_t hicolor = rand_color();
			gfx.hgradient(x, y, size_x, size_y, locolor, hicolor);
		}	break;

		case 5: {
			video_offset_t x = (rand() % video_gfx_getxdim(&gfx)) - 16;
			video_offset_t y = (rand() % video_gfx_getydim(&gfx)) - 16;
			video_coord_t size_x = rand() % video_gfx_getxdim(&gfx);
			video_coord_t size_y = rand() % video_gfx_getydim(&gfx);
			video_color_t locolor = rand_color();
			video_color_t hicolor = rand_color();
			gfx.vgradient(x, y, size_x, size_y, locolor, hicolor);
		}	break;

		default:
			gfx.line(rand() % video_gfx_getxdim(&gfx),
			         rand() % video_gfx_getydim(&gfx),
			         rand() % video_gfx_getxdim(&gfx),
			         rand() % video_gfx_getydim(&gfx),
			         color);
			break;
		}
	}
	return 0;
}

DECL_END

#endif /* !GUARD_APPS_GFX_MAIN_C */
