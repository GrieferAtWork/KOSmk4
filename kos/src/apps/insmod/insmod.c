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
#ifndef GUARD_APPS_INSMOD_INSMOD_C
#define GUARD_APPS_INSMOD_INSMOD_C 1
#define _KOS_SOURCE 1

#include <hybrid/compiler.h>

#include <kos/ksysctl.h>
#include <kos/malloc.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DECL_BEGIN

PRIVATE char *GetDriverLibraryPath(void) {
	size_t buflen = 256;
	size_t new_buflen;
	char *buf;
	buf = (char *)Malloc(buflen);
again_getpath:
	new_buflen = KSysctlGetDriverLibraryPath(buf, buflen);
	if (new_buflen > buflen) {
		buf    = (char *)Realloc(buf, new_buflen);
		buflen = new_buflen;
		goto again_getpath;
	} else if (new_buflen < buflen) {
		char *newbuf;
		newbuf = (char *)realloc(buf, new_buflen);
		if likely(newbuf)
			buf = newbuf;
	}
	return buf;
}


int main(int argc, char *argv[]) {
	char *name, *cmdline;
	if (argc < 2 || argc > 3) {
print_usage:
		fprintf(stderr, "Usage: %s NAME [CMDLINE]\n"
		                "       %s -p [LIBRARY_PATH]\n",
		        argv[0], argv[0]);
		return EXIT_FAILURE;
	}
	name = argv[1];
	if (name[0] == '-') {
		if (strcmp(name, "-p") == 0) {
			if (argc >= 3) {
				/* Set library path */
				KSysctlSetDriverLibraryPath(argv[2]);
			} else {
				/* Print library path. */
				char *path = GetDriverLibraryPath();
				printf("%s\n", path);
				free(path);
			}
			return EXIT_SUCCESS;
		}
		goto print_usage;
	}
	cmdline = NULL;
	if (argc >= 3)
		cmdline = argv[2];
	/* TODO: Temporarily  re-direct  syslog()  for  this  process  to stdout
	 *       (or capture  all  syslog()  messages written  by  this  process
	 *       after this call to `KSysctlInsmod()', and then print everything
	 *       to stdout) */
	KSysctlInsmod(name, cmdline);
	return EXIT_SUCCESS;
}


DECL_END

#endif /* !GUARD_APPS_INSMOD_INSMOD_C */
