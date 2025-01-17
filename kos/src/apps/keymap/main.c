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
#ifndef GUARD_APPS_KEYMAP_MAIN_C
#define GUARD_APPS_KEYMAP_MAIN_C 1
#define LIBKEYMAP_WANT_PROTOTYPES

#include <hybrid/compiler.h>

#include <kos/ioctl/kbd.h>
#include <kos/types.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <libkeymap/keymap.h>

DECL_BEGIN

int main(int argc, char *argv[]) {
	int opt, keymap_fd;
	int kbdev = -1;
	struct stat st;
	struct keymap keymap;
	void *keymap_mapping;
	struct kbd_keymap io;
	ssize_t codesize;
	char *map_filename;

	while ((opt = getopt(argc, argv, "d:")) != -1) {
		switch (opt) {

		case 'd':
			if (kbdev >= 0)
				close(kbdev);
			kbdev = open(optarg, O_RDWR); /* NOLINT */
			if (kbdev < 0) {
				fprintf(stderr, "%s: Failed to open device %s: %m\n",
				        argv[0], optarg);
				exit(EXIT_FAILURE);
			}
			break;

		default: /* '?' */
			fprintf(stderr, "Usage: %s [-d device] keymap\n",
			        argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	if (kbdev < 0) {
		/* TODO: if (isatty(STDIN_FILENO)) open_keyboard_of(STDIN_FILENO) */
		kbdev = open("/dev/ps2kbd1", O_RDONLY); /* NOLINT */
		if (kbdev < 0)
			kbdev = open("/dev/ps2kbd2", O_RDONLY); /* NOLINT */
		if (kbdev < 0) {
			fprintf(stderr, "%s: Failed to find keyboard device\n",
			        argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	map_filename = argv[optind];
	keymap_fd = open(map_filename, O_RDONLY); /* NOLINT */
	if (keymap_fd < 0) {
		fprintf(stderr, "%s: Failed to open keymap file %s: %m\n",
		        argv[0], map_filename);
		exit(EXIT_FAILURE);
	}
	if (fstat(keymap_fd, &st) < 0) {
		fprintf(stderr, "%s: Failed to stat keymap file %s: %m\n",
		        argv[0], map_filename);
		exit(EXIT_FAILURE);
	}
	keymap_mapping = mmap(NULL,
	                      st.st_size,
	                      PROT_READ,
	                      MAP_PRIVATE | MAP_FILE,
	                      keymap_fd,
	                      0);
	if (keymap_mapping == MAP_FAILED) {
		fprintf(stderr, "%s: Failed to read keymap file %s: %m\n",
		        argv[0], map_filename);
		exit(EXIT_FAILURE);
	}
	if (!keymap_openblob(&keymap, keymap_mapping, st.st_size)) {
		fprintf(stderr, "%s: Not a keymap file: %s\n",
		        argv[0], map_filename);
		exit(EXIT_FAILURE);
	}
	io.km_defenc = keymap.km_defencoding;
	codesize     = keymap_codesize(keymap.km_ext, &io.km_defenc, io.km_defenc);
	if (codesize < 0) {
		fprintf(stderr, "%s: Corrupted keymap file: %s\n",
		        argv[0], map_filename);
		exit(EXIT_FAILURE);
	}
	io.km_maptext = (byte_t *)keymap.km_ext;
	io.km_mapsize = (size_t)codesize;
	io.km_defenc  = keymap.km_defencoding;
	if (ioctl(kbdev, KBD_IOC_SETKEYMAP, &io) < 0) {
		fprintf(stderr, "%s: Failed to set keymap file %s: %m\n",
		        argv[0], map_filename);
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}

DECL_END

#endif /* !GUARD_APPS_KEYMAP_MAIN_C */
