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
#ifndef GUARD_APPS_PLAYGROUND_MAIN_C
#define GUARD_APPS_PLAYGROUND_MAIN_C 1
#define _ALL_SOURCE 1

/* This program isn't actually meant to do anything. It is however meant to be used
 * for quickly testing out new features, or checking the behavior of system functions
 * within a live environment. */

#include <hybrid/compiler.h>

#include <kos/debugtrap.h>
#include <kos/kernel/types.h>
#include <kos/syscalls.h>
#include <kos/sysctl.h>
#include <kos/types.h>

#include <format-printer.h>
#include <ctype.h>
#include <assert.h>
#include <malloc.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

DECL_BEGIN

/************************************************************************/
int main_environ(int argc, char *argv[], char *envp[]) {
	printf("$PATH: %q\n", getenv("PATH"));
	printf("envp: %p\n", envp);
	if (envp) {
		size_t i;
		for (i = 0; envp[i]; ++i)
			printf("envp[%Iu]: %q\n", i, envp[i]);
	}
	return 0;
}
/************************************************************************/





/************************************************************************/
int main_ctype(int argc, char *argv[], char *envp[]) {
	assert(isalpha('s'));
	return 0;
}
/************************************************************************/





/************************************************************************/
PRIVATE ssize_t __LIBCCALL
debug_printer(void *UNUSED(arg), char const *message, size_t len) {
	struct debugtrap_reason r;
	r.dtr_signo  = (uint32_t)len;
	r.dtr_strarg = message;
	r.dtr_reason = DEBUGTRAP_REASON_MESSAGE;
	if (sys_debugtrap(NULL, &r) < 0)
		r.dtr_signo = 0;
	return (ssize_t)r.dtr_signo;
}

int main_dprint(int argc, char *argv[], char *envp[]) {
	/* XXX: While this ~does~ work to do exactly what it's supposed to do,
	 *      Visual Studio's MIEngine doesn't seem to understand the protocol
	 *      that GDB uses to transmit generic, human-readable strings
	 *      As such, this produces the following output:
	 *          @"a = "
	 *          @"Value\n"
	 *          @" for a"
	 *          @"\n"
	 *          @"b = "
	 *          @"Value for b"
	 *          @"\n"
	 *          @"c = "
	 *          @"fdadsfasdn"
	 *          @"\n"
	 *          @"d = "
	 *          @"This is c"
	 *          @"\n"
	 *      And no:  The \n-s in there I did _NOT_ just escape for the visual
	 *               Those actually appear as-is in the console.
	 *      However: When running GDB normally from a console, the text is displayed
	 *               properly:
	 *          a = Value
	 *           for a
	 *          b = Value for b
	 *          c = fdadsfasdn
	 *          d = This is c
	 * So the problem with this is actually Visual Studio...
	 * This sucks! You want to know why I added support for message debug traps?
	 * I added it so that I could output text to the Visual studio output window
	 * without that annoying `cmd: ' prefix caused by the fact that all output
	 * currently is piped through magic (which is started by `cmd', hence the
	 * prefix), and is considered as a side channel by visual studio, and there
	 * doesn't seem to be a way to prevent the `cmd: ' prefix for those.
	 * Now why do I care? Well: Because of that prefix, it is impossible for me
	 * to output file paths in such a way that they become clickable so-as to
	 * allow be to immediately go to the associated source location.
	 */
	format_printf(&debug_printer, NULL,
	              "a = %s\n"
	              "b = %s\n"
	              "c = %s\n"
	              "d = %s\n",
	              "Value\n for a",
	              "Value for b",
	              "fdadsfasdn",
	              "This is c");
	return 0;
}
/************************************************************************/



typedef int (*FUN)(int argc, char *argv[], char *envp[]);
typedef struct {
	char const *n;
	FUN         f;
} DEF;
PRIVATE DEF defs[] = {
	{ "environ", &main_environ },
	{ "dprint", &main_dprint },
	{ "ctype", &main_ctype },
	{ NULL, NULL },
};


int main(int argc, char *argv[], char *envp[]) {
	unsigned int i;
	if (argc < 2) {
		fprintf(stderr, "Usage: %s NAME OPTIONS\n", argv[0]);
		fprintf(stderr, "Possible values for NAME:\n");
		for (i = 0; defs[i].n; ++i)
			fprintf(stderr, "\t%s\n", defs[i].n);
		return 1;
	}
	for (i = 0; defs[i].n; ++i) {
		if (strcmp(defs[i].n, argv[1]) == 0)
			return (*defs[i].f)(argc - 1, argv + 1, envp);
	}
	fprintf(stderr, "Unknown name %q\n", argv[1]);
	return 1;
}


DECL_END

#endif /* !GUARD_APPS_PLAYGROUND_MAIN_C */
