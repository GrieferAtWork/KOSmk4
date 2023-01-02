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
#ifndef GUARD_APPS_INSMOD_RMMOD_C
#define GUARD_APPS_INSMOD_RMMOD_C 1
#define _KOS_SOURCE 1

#include <hybrid/compiler.h>

#include <kos/ksysctl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DECL_BEGIN

int main(int argc, char *argv[]) {
	unsigned int flags = KSYSCTL_DRIVER_DELMOD_FNORMAL;
	if (argc) {
		--argc;
		++argv;
	}
	while (argc) {
		char *arg = *argv;
		if (*arg != '-')
			break;
		--argc;
		++argv;
		++arg;
		if (strcmp(arg, "-") == 0) {
			/* Support for `--' to break the commandline */
			break;
		} else if (strcmp(arg, "nd") == 0 || strcmp(arg, "-no-depend") == 0) {
			flags |= KSYSCTL_DRIVER_DELMOD_FNODEPEND;
		} else if (strcmp(arg, "f") == 0 || strcmp(arg, "-force") == 0) {
			flags |= KSYSCTL_DRIVER_DELMOD_FFORCE;
		} else if (strcmp(arg, "a") == 0 || strcmp(arg, "-async") == 0) {
			flags |= KSYSCTL_DRIVER_DELMOD_FNONBLOCK;
		} else {
			goto usage;
		}
	}
	if (!argc)
		goto usage;
	do {
		/* TODO: Temporarily  re-direct  syslog()  for  this  process  to stdout
		 *       (or capture  all  syslog()  messages written  by  this  process
		 *       after this call to `KSysctlDelmod()', and then print everything
		 *       to stdout) */
		KSysctlDelmod(*argv++, flags);
	} while (--argc);
	return EXIT_SUCCESS;
usage:
	fprintf(stderr,
	        "Usage: rmmod [FLAGS...] NAME\n"
	        "    -nd --no-depend   Don't unload dependent drivers\n"
	        "    -f  --force       Force unload\n"
	        "    -a  --async       Don't wait for completion\n");
	return EXIT_FAILURE;
}


DECL_END

#endif /* !GUARD_APPS_INSMOD_RMMOD_C */
