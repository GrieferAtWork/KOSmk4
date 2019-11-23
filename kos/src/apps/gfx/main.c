/* Copyright (c) 2019 Griefer@Work                                            *
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

#include <hybrid/compiler.h>

#include <linux/kd.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include <termios.h>

DECL_BEGIN

int main(int argc, char *argv[]) {
	struct termios oios, nios;
	pid_t cpid;
	int status;
	(void)argc;
	(void)argv;

	srand(time(NULL));
	tcgetattr(STDOUT_FILENO, &oios);
	nios = oios;
	cfmakeraw(&nios);
	tcsetattr(STDOUT_FILENO, TCSADRAIN, &nios); /* Enable raw terminal mode */
	ioctl(STDOUT_FILENO, KDSETMODE, KD_GRAPHICS); /* Enable VGA graphics mode */

	/* Have the main loop run in a separate process, so that
	 * in the case of a crash, we're still able to restore
	 * display settings to terminal to the commandline. */
	cpid = fork();
	if (cpid == 0) {
		void *blob;
		size_t blob_size = 320 * 200 * 1;
		char buf[1];
		ssize_t len;
		blob = mmap(NULL,
		            blob_size,
		            PROT_READ | PROT_WRITE, MAP_SHARED,
		            STDOUT_FILENO,
		            0);
		while ((len = read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
			uint8_t color;
			if (buf[0] == 'q')
				break;
			color = rand() & 0xff;
			memset(blob, color, blob_size);
		}
		return EXIT_SUCCESS;
	}

	waitpid(cpid, &status, 0);
	ioctl(STDOUT_FILENO, KDSETMODE, KD_TEXT); /* Enable text mode */
	tcsetattr(STDOUT_FILENO, TCSADRAIN, &oios); /* Restore old terminal mode */
	return WEXITSTATUS(status);
}

DECL_END

#endif /* !GUARD_APPS_GFX_MAIN_C */
