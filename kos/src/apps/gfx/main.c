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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
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
#include <kos/types.h>
#include <linux/kd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/wait.h>

#include <dlfcn.h>
#include <err.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include <libvideo/gfx/buffer.h>

DECL_BEGIN

PRIVATE void enable_graphics_mode(void) {
	fd_t driver;
	struct vd_format format;
	driver = video_driver();
	if (driver < 0)
		err(EXIT_FAILURE, "Failed to open driver driver");
	if (ioctl(driver, VIDEOIO_GETFORMAT, &format) < 0)
		err(EXIT_FAILURE, "ioctl(VIDEOIO_GETFORMAT) failed");
	if (format.vdf_codec == VIDEO_CODEC_NONE) {
		pid_t cpid;
		/* Video driver is still in TTY-mode
		 * -> Switch to video mode */
		if (ioctl(driver, KDSETMODE, KD_GRAPHICS) < 0)
			err(EXIT_FAILURE, "ioctl(KDSETMODE, KD_GRAPHICS) failed");
		cpid = fork();
		if (cpid < 0)
			err(EXIT_FAILURE, "fork() failed");
		if (cpid != 0) {
			/* Parent process... */
			int status;
			waitpid(cpid, &status, 0);
			ioctl(STDOUT_FILENO, KDSETMODE, KD_TEXT); /* Restore text mode */
			exit(WEXITSTATUS(status));
		}
	}
}

int main(int argc, char *argv[]) {
	/*REF*/ struct video_buffer *screen;
	struct video_buffer_gfx gfx;
	(void)argc;
	(void)argv;
	srand(time(NULL));

	/* Enable graphics mode. */
	enable_graphics_mode();

	/* Bind the screen buffer. */
	screen = video_buffer_screen();
	screen->gfx(gfx);

	gfx.fill(0, 0,
	         screen->vb_size_x,
	         screen->vb_size_y,
	         VIDEO_COLOR_WHITE);
	for (;;) {
		gfx.line(rand() % screen->vb_size_x,
		         rand() % screen->vb_size_y,
		         rand() % screen->vb_size_x,
		         rand() % screen->vb_size_y,
		         VIDEO_COLOR_RGBA(rand() % 256,
		                          rand() % 256,
		                          rand() % 256,
		                          rand() % 256));
	}

	return 0;
}

DECL_END

#endif /* !GUARD_APPS_GFX_MAIN_C */
