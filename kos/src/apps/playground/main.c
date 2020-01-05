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
#ifndef GUARD_APPS_PLAYGROUND_MAIN_C
#define GUARD_APPS_PLAYGROUND_MAIN_C 1
#define _ALL_SOURCE 1

/* This program isn't actually meant to do anything. It is however meant to be used
 * for quickly testing out new features, or checking the behavior of system functions
 * within a live environment. */

#include <hybrid/compiler.h>

#include <asm/cpu-flags.h>
#include <asm/intrin-fpu.h>
#include <asm/intrin.h>
#include <kos/debugtrap.h>
#include <kos/except.h>
#include <kos/kernel/types.h>
#include <kos/syscalls.h>
#include <kos/ksysctl.h>
#include <kos/types.h>
#include <kos/ukern.h>
#include <kos/unistd.h>
#include <sys/io.h>
#include <sys/mmio.h>
#include <sys/stat.h>
#include <sys/syscall-proto.h>
#include <sys/syscall.h>
#include <sys/wait.h>

#include <assert.h>
#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <format-printer.h>
#include <malloc.h>
#include <pty.h>
#include <sched.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <termios.h>
#include <unistd.h>

DECL_BEGIN

/* TODO: read() should return -EWOULDBLOCK when called with IO_NONBLOCK, and
 *       no data was available. Currently, the KOS kernel returns `0' for this
 *       case, which would be indicative of EOF. - There has to be a difference
 *       between these two (the biggest culprit here are ringbuffer-based objects) */

/* TODO: Add support for `pthread_num_processors_np()' */
/* TODO: Add support for `int ungetchar(int ch)' (same as `ungetc(ch, stdin)') */

/* TODO: `__CORRECT_ISO_CPP_MATH_H_PROTO' interferes with libstdc++'s autoconf detection... */
/* TODO: libstdc++ doesn't detect `HAVE_ISWBLANK' properly */
/* TODO: libstdc++ doesn't detect `HAVE_LINK' properly */
/* TODO: libstdc++ doesn't detect `HAVE_LINUX_FUTEX' properly */
/* TODO: libstdc++ doesn't detect `HAVE_POLL' properly */
/* TODO: libstdc++ doesn't detect `HAVE_READLINK' properly */
/* TODO: libstdc++ doesn't detect `HAVE_SETENV' properly */
/* TODO: libstdc++ doesn't detect `HAVE_STDALIGN_H' properly */
/* TODO: libstdc++ doesn't detect `HAVE_STDBOOL_H' properly */
/* TODO: libstdc++ doesn't detect `HAVE_STRERROR_L' properly */
/* TODO: libstdc++ doesn't detect `HAVE_STRUCT_DIRENT_D_TYPE' properly */
/* TODO: libstdc++ doesn't detect `HAVE_STRXFRM_L' properly */
/* TODO: libstdc++ doesn't detect `HAVE_SYMLINK' properly */
/* TODO: libstdc++ doesn't detect `HAVE_SYS_RESOURCE_H' properly */
/* TODO: libstdc++ doesn't detect `HAVE_S_IFREG' properly */
/* TODO: libstdc++ doesn't detect `HAVE_TRUNCATE' properly */
/* TODO: libstdc++ doesn't detect `HAVE_VFWSCANF' properly */
/* TODO: libstdc++ doesn't detect `HAVE_VSWSCANF' properly */
/* TODO: libstdc++ doesn't detect `HAVE_VWSCANF' properly */
/* TODO: libstdc++ doesn't detect `HAVE_WCSTOF' properly */
/* TODO: libstdc++ doesn't detect `HAVE__WFOPEN' properly */
/* TODO: libstdc++ doesn't detect `USE_FCHMOD' properly */
/* TODO: libstdc++ doesn't detect `USE_FCHMODAT' properly */
/* TODO: libstdc++ doesn't detect `USE_LFS' properly */
/* TODO: libstdc++ doesn't detect `USE_LSTAT' properly */
/* TODO: libstdc++ doesn't detect `USE_NANOSLEEP' properly */
/* TODO: libstdc++ doesn't detect `USE_REALPATH' properly */
/* TODO: libstdc++ doesn't detect `USE_SCHED_YIELD' properly */
/* TODO: libstdc++ doesn't detect `USE_ST_MTIM' properly */
/* TODO: libstdc++ doesn't detect `USE_UTIME' properly */
/* TODO: libstdc++ doesn't detect `USE_UTIMENSAT' properly */
/* TODO: libstdc++ doesn't detect `machine/endian.h' */
/* TODO: Add support for `HAVE___CXA_THREAD_ATEXIT' */
/* TODO: Add system header <sys/machine.h> */
/* TODO: Add system header <sys/sdt.h> */
/* TODO: Add system header <fenv.h> */
/* TODO: Add system header <fp.h> */
/* TODO: Add system header <libintl.h> */
/* TODO: Add system header <nan.h> */
/* TODO: Add system header <ftw.h> */



/************************************************************************/
int main_rawterm(int argc, char *argv[], char *envp[]) {
	struct termios oios, nios;
	char buf[8];
	(void)argc, (void)argv, (void)envp;
	tcgetattr(STDIN_FILENO, &oios);
	nios = oios;
	cfmakeraw(&nios);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &nios);
	printf("type 'q' to exit\n");
	for (;;) {
		ssize_t i, buflen;
		buflen = read(STDIN_FILENO, buf, sizeof(buf));
		if (buflen <= 0)
			break;
		if (buflen == 1 && buf[0] == 'q')
			break;
		for (i = 0; i < buflen; ++i) {
			printf("%s%.2x", i ? " " : "",
			       (unsigned int)(u8)buf[i]);
		}
		for (; i < (ssize_t)sizeof(buf); ++i) {
			printf("   ");
		}
		for (i = 0; i < buflen; ++i) {
			char c = buf[i];
			if (!isprint(c))
				c = '.';
			printf("%c", c);
		}
		printf("\n");
	}
	tcsetattr(STDIN_FILENO, TCSADRAIN, &oios);
	return 0;
}
/************************************************************************/





/************************************************************************/
int main_color(int argc, char *argv[], char *envp[]) {
	/* Foreground codes */
	unsigned int f, b;
	static unsigned int const f_codes[] = {
		30, 31, 32, 33, 34, 35, 36, 37,
		90, 91, 92, 93, 94, 95, 96, 97
	};
	/* Background codes */
	static unsigned int const b_codes[] = {
		40, 41, 42, 43, 44, 45, 46, 47,
		100, 101, 102, 103, 104, 105, 106, 107
	};
	(void)argc, (void)argv, (void)envp;
#define SESC "\033" /* \e */
	printf(SESC "[m");
	printf("\\e[f;bm:\n"
	       "b f");
	for (f = 0; f < COMPILER_LENOF(f_codes); ++f) {
		printf("%I32c%2u",
		       f == 0 ? 0x2551 : 0x2502,
		       f_codes[f]);
	}
	printf("\n"
	       "%I32c%I32c%I32c",
	       0x2550, 0x2550, 0x2550);
	for (f = 0; f < COMPILER_LENOF(f_codes); ++f) {
		printf("%I32c%I32c%I32c",
		       f == 0 ? 0x256c : 0x256a,
		       0x2550, 0x2550);
	}
	for (b = 0; b < COMPILER_LENOF(b_codes); ++b) {
		printf("\n%3u", b_codes[b]);
		for (f = 0; f < COMPILER_LENOF(f_codes); ++f) {
			printf("%I32c",
			       f == 0 ? 0x2551 : 0x2502);
			printf(SESC "[%u;%um%I32c%I32c" SESC "[m",
			       b_codes[b], f_codes[f],
			       0x25c4, 0x25ba);
		}
	}
	printf("\n");
	return 0;
}
/************************************************************************/





/************************************************************************/
int main_fpu(int argc, char *argv[], char *envp[]) {
	(void)argc, (void)argv, (void)envp;
	printf("mxcsr=%#.8I32x\n", __stmxcsr());
	printf("fcw=%#.4I16x\n", __fnstcw());
	printf("fsw=%#.4I16x\n", __fnstsw());
	__fldcw(FCW_IM | FCW_DM | FCW_ZM | FCW_OM | FCW_UM | FCW_PM |
	        FCW_PC_EXTEND | FCW_RC_NEAREST);
	printf("mxcsr=%#.8I32x\n", __stmxcsr());
	printf("fcw=%#.4I16x\n", __fnstcw());
	printf("fsw=%#.4I16x\n", __fnstsw());
	__fldcw(FCW_PC_EXTEND | FCW_RC_NEAREST);
	printf("mxcsr=%#.8I32x\n", __stmxcsr());
	printf("fcw=%#.4I16x\n", __fnstcw());
	printf("fsw=%#.4I16x\n", __fnstsw());
	return 0;
}
/************************************************************************/





/************************************************************************/
int main_fork(int argc, char *argv[], char *envp[]) {
	(void)argc, (void)argv, (void)envp;
	for (;;) {
		if (fork() == 0) {
			printf("child: %u\n", getpid());
			_Exit(0);
		}
		/*sched_yield();*/
	}
	return 0;
}
/************************************************************************/





/************************************************************************/
int main_environ(int argc, char *argv[], char *envp[]) {
	(void)argc, (void)argv, (void)envp;
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
int main_prognam(int argc, char *argv[], char *envp[]) {
	(void)argc, (void)argv, (void)envp;
	printf("program_invocation_name       = %q\n", program_invocation_name);
	printf("program_invocation_short_name = %q\n", program_invocation_short_name);
	return 0;
}
/************************************************************************/





/************************************************************************/
int main_logtime(int argc, char *argv[], char *envp[]) {
	(void)argc, (void)argv, (void)envp;
	for (;;)
		syslog(LOG_DEBUG, "Entry!\n");
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
	(void)argc, (void)argv, (void)envp;
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
	 * allow me to immediately go to the associated source location.
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
	{ "prognam", &main_prognam },
	{ "rawterm", &main_rawterm },
	{ "color", &main_color },
	{ "fpu", &main_fpu },
	{ "fork", &main_fork },
	{ "logtime", &main_logtime },
	{ NULL, NULL },
};


int main(int argc, char *argv[], char *envp[]) {
	unsigned int i;
	if (argc < 2) {
		fprintf(stderr, "Usage: %s NAME [ARGS...]\n", argv[0]);
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
