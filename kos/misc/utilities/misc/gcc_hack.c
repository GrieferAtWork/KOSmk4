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
#ifndef GUARD_GCC_HACK_C
#define GUARD_GCC_HACK_C 1
#define _POSIX_SOURCE 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include <stdio.h>  /* printf() */
#include <stdlib.h> /* EXIT_FAILURE */
#include <string.h> /* memmove */
#include <unistd.h> /* execv(), isatty() */

#ifndef __USE_KOS
#define memmovedown memmove
#endif /* !__USE_KOS */

#ifndef SLAVE
#define SLAVE "/bin/gcc"
#endif /* !SLAVE */

#ifndef KOS_ROOT
#define KOS_ROOT "/opt/kos/"
#endif /* !KOS_ROOT */

#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif /* !EXIT_FAILURE */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static char const KOS_ROOT_[] = KOS_ROOT;
#undef KOS_ROOT
#define KOS_ROOT KOS_ROOT_

#define CSTRLEN(x) ((sizeof(x) / sizeof(*(x))) - 1)

/* Verify that `filename' is non-absolute, or points into the KOS root.
 * If  it  doesn't,  return non-zero  and  print a  warning  to stdout.
 * Otherwise, return `0'
 * @param: op0: First part of the associated operand.
 * @param: op1: Second part of the associated operand. */
static int
validate_sysroot_argument(char const *filename,
                          char const *op0,
                          char const *op1,
                          char const *argv0) {
	size_t filename_len;
	char const *format;
	if (filename[0] != '/')
		return 0; /* Not an absolute path! */
	filename_len = strlen(filename);
	if (filename_len >= CSTRLEN(KOS_ROOT) &&
	    memcmp(filename, KOS_ROOT, CSTRLEN(KOS_ROOT) * sizeof(char)) == 0)
		return 0; /* Points into the KOS root. */
	if (filename_len == CSTRLEN(KOS_ROOT) - 1 &&
	    memcmp(filename, KOS_ROOT, (CSTRLEN(KOS_ROOT) - 1) * sizeof(char)) == 0)
		return 0; /* Special case: Allow the KOS root itself w/o a trailing '/' */
	format = "%s: warning: filename `%s' (`%s%s') outside of KOS root\n";
	if (isatty(STDOUT_FILENO)) {
		format = "%s: "
		         "\033[96m" /* AC_FG(ANSITTY_CL_AQUA) */
//		         "\033[91m" /* AC_FG(ANSITTY_CL_RED) */
		         "warning"
		         "\033[39m" /* AC_FGDEF */
		         ": "
		         "\033[97m" /* AC_FG(ANSITTY_CL_WHITE) */
		         "Ignoring path `%s' (`%s%s') outside of KOS root"
		         "\033[39m" /* AC_FGDEF */
		         "\n";
	}
	if (!op0)
		op0 = "";
	if (!op1)
		op1 = "";
	{
		char const *appname = argv0;
		char const *iter = argv0;
		for (; *iter; ++iter) {
			if (*iter == '/')
				appname = iter + 1;
		}
		/* NOTE: Write to stdout because writing to stderr may be interpreted
		 *       the same as a non-zero exit  code by some utilities, and  we
		 *       really  want this  kind of issue  to fly under  the radar of
		 *       tools! */
		printf(format, appname, filename, op0, op1);
	}
	return -1;
}

int main(int argc, char *argv[]) {
	unsigned int i = 1;
again:
	for (; i < argc; ++i) {
		char *arg = argv[i];
		if (arg[0] != '-')
			continue;
		if (arg[1] == 'I' || arg[1] == 'L') {
			size_t operand_len;
			char *operand = arg + 2;
			char *op1 = NULL;
			unsigned int num_args = 1;
			if (!*operand) {
				num_args = 2;
				operand  = op1 = argv[i + 1];
				if (!operand)
					continue;
			}
			if (validate_sysroot_argument(operand, arg, op1, argv[0]) == 0)
				continue;
			/* Delete affected argument(s). */
			argc -= num_args;
			memmovedown(&argv[i], &argv[i + num_args],
			            (argc - i) * sizeof(char *));
			argv[argc] = NULL;
			goto again;
		}
	}
	execv(argv[0] = SLAVE, argv);
	return EXIT_FAILURE;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !GUARD_GCC_HACK_C */
