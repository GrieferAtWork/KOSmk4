/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_APPS_VCONF_MAIN_C
#define GUARD_APPS_VCONF_MAIN_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#define _BSD_SOURCE 1

#include <hybrid/compiler.h>

#include <hybrid/typecore.h>

#include <kos/ioctl/svga.h>
#include <kos/types.h>
#include <sys/ioctl.h>

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <libansitty/ctl.h>

#define CC /* nothing */

DECL_BEGIN

PRIVATE void CC usage(void) {
	PRIVATE char const message[] =
	"Usage: vconf info\n"
	"       vconf mode [id]\n";
	write(STDOUT_FILENO, message, sizeof(message) - sizeof(char));
}

PRIVATE NONNULL((3)) void CC
printmode(size_t id, size_t maxidlen,
          struct svga_modeinfo const *__restrict mode,
          bool highlight) {
	printf(highlight ? (AC_WHITE("%?" PRIuSIZ) ": " AC_WHITE("%" PRIu32) "x" AC_WHITE("%" PRIu32) "x" AC_WHITE("%" PRIu8))
	                 : ("%?" PRIuSIZ ": " "%" PRIu32 "x" "%" PRIu32 "x" "%" PRIu8),
	       maxidlen, id,
	       mode->smi_resx,
	       mode->smi_resy,
	       mode->smi_colorbits);
	if (mode->smi_flags & SVGA_MODEINFO_F_TXT)
		printf(highlight ? " [" AC_WHITE("text") "]" : " [text]");
	if (mode->smi_flags & SVGA_MODEINFO_F_PLANAR)
		printf(highlight ? " [" AC_WHITE("planar") "]" : " [planar]");
}

int main(int argc, char *argv[]) {
	bool otty = fisatty(stdout);
	char const *command;
	fd_t svga;
	struct svga_lsmodes lsm;
	struct svga_modeinfo curmode;
	size_t curmodeid;
	bool has_curmode;
	if likely(argc) {
		--argc;
		++argv;
	}
	if unlikely(!argc) {
		usage();
		return 0;
	}
	command = *argv++;
	--argc;

	svga = open("/dev/svga", O_RDONLY); /* NOLINT */
	if (svga < 0)
		err(1, "Failed to open '/dev/svga'");

	/* List all supported modes. */
	bzero(&lsm, sizeof(lsm));
	if (ioctl(svga, SVGA_IOC_LSMODES, &lsm) < 0)
		err(1, "ioctl(SVGA_IOC_LSMODES)");
	lsm.svl_buf = (struct svga_modeinfo *)malloc(lsm.svl_count, sizeof(struct svga_modeinfo));
	if (!lsm.svl_buf)
		err(1, "malloc(%" PRIuSIZ ", %" PRIuSIZ ")", lsm.svl_count, sizeof(struct svga_modeinfo));
	if (ioctl(svga, SVGA_IOC_LSMODES, &lsm) < 0)
		err(1, "ioctl(SVGA_IOC_LSMODES)");
	has_curmode = ioctl(svga, SVGA_IOC_GETMODE, &curmode) >= 0;
	curmodeid   = lsm.svl_count;
	if (has_curmode) {
		for (curmodeid = 0; curmodeid < lsm.svl_count; ++curmodeid) {
			if (bcmp(&lsm.svl_buf[curmodeid], &curmode, sizeof(struct svga_modeinfo)) == 0)
				break;
		}
	}
	if (strcmp(command, "info") == 0) {
		char *iter;
		size_t i, longestnamelen;
		struct svga_strings strings;
		char csname[SVGA_CSNAMELEN];
		struct winsize ws;
		if (ioctl(svga, SVGA_IOC_GETCSNAME, csname) < 0)
			err(1, "ioctl(SVGA_IOC_GETCSNAME)");
		bzero(&strings, sizeof(strings));
		strings.svs_count = (uint64_t)-1;
		if (ioctl(svga, SVGA_IOC_CSSTRINGS, &strings) < 0)
			err(1, "ioctl(SVGA_IOC_CSSTRINGS)");
		strings.svs_buf = (char *)malloc(strings.svs_bufsz);
		if (!strings.svs_buf)
			err(1, "malloc(%" PRIuSIZ ")", strings.svs_bufsz);
		if (ioctl(svga, SVGA_IOC_CSSTRINGS, &strings) < 0)
			err(1, "ioctl(SVGA_IOC_CSSTRINGS)");
		longestnamelen = 0;
		for (i = 0, iter = strings.svs_buf; i < strings.svs_count; ++i) {
			size_t namelen = strlen(iter);
			if (longestnamelen < namelen)
				longestnamelen = namelen;
			iter += namelen + 1;     /* Skip name */
			iter = strend(iter) + 1; /* Skip value */
		}
		if (ioctl(svga, TIOCGWINSZ, &ws) >= 0) {
			printf(otty ? "ttydim:  " AC_WHITE("%u") "x"
			                          AC_WHITE("%u") " ("
			                          AC_WHITE("%u") "x"
			                          AC_WHITE("%u") ")\n"
			            : "ttydim:  %ux%u (%ux%u)\n",
			       ws.ws_col, ws.ws_row,
			       ws.ws_xpixel / ws.ws_col,
			       ws.ws_ypixel / ws.ws_row);
		}
		if (has_curmode) {
			printf("mode:    ");
			printmode(curmodeid, 0, &curmode, otty);
			putchar('\n');
		}
		printf(otty ? "chipset: " AC_WHITE("%s") "\n"
		            : "chipset: %s\n",
		       csname);
		for (i = 0, iter = strings.svs_buf; i < strings.svs_count; ++i) {
			char const *name, *value;
			name  = iter;
			iter  = strend(iter) + 1;
			value = iter;
			iter  = strend(iter) + 1;
			printf(otty ? "\t%-?s : '" AC_WHITE("%#q") "'\n"
			            : "\t%-?s : '%#q'\n",
			       longestnamelen, name, value);
		}
	} else if (strcmp(command, "mode") == 0) {
		if (argc == 0) {
			size_t i, maxidlen;
			maxidlen = snprintf(NULL, 0, "%" PRIuSIZ, lsm.svl_count - 1);
			/* List available video modes */
			for (i = 0; i < lsm.svl_count; ++i) {
				printf("[%s] ",
				       i == curmodeid
				       ? (otty ? AC_GREEN("X") : "X")
				       : " ");
				printmode(i, maxidlen, &lsm.svl_buf[i],
				          otty && i == curmodeid);
				putchar('\n');
			}
		} else if (argc == 1) {
			/* Set video mode */
			errno_t error;
			char const *modename = argv[0];
			uint32_t id;
			id = strtou32_r(modename, NULL, 0, &error);
			if (error != 0)
				errc(1, error, "strtou32_r(%q)", modename);
			if (id >= lsm.svl_count)
				errc(1, ERANGE, "Invalid mode id %" PRIu32, id);
			if (ioctl(svga, SVGA_IOC_SETMODE, &lsm.svl_buf[id]) < 0)
				err(1, "ioctl(SVGA_IOC_SETMODE)");
		} else {
			goto bad_usage;
		}
	} else {
		goto bad_usage;
	}
	return 0;
bad_usage:
	usage();
	return 1;
}


DECL_END

#endif /* !GUARD_APPS_VCONF_MAIN_C */
