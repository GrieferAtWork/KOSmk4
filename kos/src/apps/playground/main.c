/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_APPS_PLAYGROUND_MAIN_C
#define GUARD_APPS_PLAYGROUND_MAIN_C 1
#define _EVERY_SOURCE 1
#define _NO_THREADING 1 /* ... so it's used at least once */

/* This  program isn't actually meant to do anything.  It is however meant to be used
 * for quickly testing out new features, or checking the behavior of system functions
 * within a live environment. */

#include <hybrid/compiler.h>

#include <arpa/inet.h>
#include <asm/cpu-flags.h>
#include <asm/intrin-fpu.h>
#include <asm/intrin.h>
#include <kos/debugtrap.h>
#include <kos/dosfs.h>
#include <kos/except.h>
#include <kos/fcntl.h>
#include <kos/kernel/types.h>
#include <kos/ksysctl.h>
#include <kos/malloc.h>
#include <kos/rtm.h>
#include <kos/syscalls.h>
#include <kos/types.h>
#include <kos/ukern.h>
#include <kos/unistd.h>
#include <linux/if_ether.h>
#include <linux/msdos_fs.h>
#include <netinet/if_ether.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <sys/auxv.h>
#include <sys/io.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/mmio.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/syscall-proto.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/un.h>
#include <sys/wait.h>

#include <assert.h>
#include <ctype.h>
#include <dlfcn.h>
#include <err.h>
#include <errno.h>
#include <format-printer.h>
#include <intrin.h>
#include <inttypes.h>
#include <malloc.h>
#include <math.h>
#include <pthread.h>
#include <pty.h>
#include <sched.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <termios.h>
#include <ttyent.h>
#include <unistd.h>

#include <libansitty/ctl.h>
#include <libdebuginfo/repr.h>
#include <libvio/vio.h>

DECL_BEGIN

/************************************************************************/
int main_rawterm(int argc, char *argv[], char *envp[]) {
#define PRINTSTR(s) write(STDOUT_FILENO, s, sizeof(s) - sizeof(char))
	struct termios oios, nios;
	char buf[8];
	bool appkeypad = false;
	bool appcursor = false;
	(void)argc, (void)argv, (void)envp;
	tcgetattr(STDIN_FILENO, &oios);
	nios = oios;
	cfmakeraw(&nios);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &nios);
	setvbuf(stdout, NULL, _IOFBF, 0); /* Fully buffered */
	printf("type 'q' to exit\n"
	       "type 'a' to toggle Application-keypad mode\n"
	       "type 'c' to toggle Application-cursor mode\n");
	for (;;) {
		ssize_t i, buflen;
		struct winsize ws;
		ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
		printf(AC_HIDECURSOR
		       AC_SAVECURSOR
		       AC_DECAWM_OFF
		       AC_CUP("%u", "%u")
		       AC_COLOR(ANSITTY_CL_LIGHT_GRAY,
		                ANSITTY_CL_DARK_GRAY)
		       "k:%s%c" AC_FG_LIGHT_GRAY ","
		       "c:%s%c"
		       AC_DEFATTR
		       AC_DECAWM_ON
		       AC_LOADCURSOR
		       AC_SHOWCURSOR,
		       ws.ws_row,
		       ws.ws_col - 6,
		       appkeypad ? AC_FG_GREEN : "",
		       appkeypad ? 'y' : 'n',
		       appcursor ? AC_FG_GREEN : "",
		       appcursor ? 'y' : 'n');
		fflush(stdout);
		buflen = read(STDIN_FILENO, buf, sizeof(buf));
		if (buflen <= 0)
			break;
		if (buflen == 1) {
			if (buf[0] == 'q')
				break;
			if (buf[0] == 'a') {
				appkeypad = !appkeypad;
				printf("%s", appkeypad ? AC_DECNKM_ON : AC_DECNKM_OFF);
				continue;
			} else if (buf[0] == 'c') {
				appcursor = !appcursor;
				printf("%s", appcursor ? AC_DECCKM_ON : AC_DECCKM_OFF);
				continue;
			}
		}
		for (i = 0; i < buflen; ++i) {
			printf("%s%.2x", i ? " " : "",
			       (unsigned int)(u8)buf[i]);
		}
		for (; i < (ssize_t)sizeof(buf); ++i)
			printf("   ");
		for (i = 0; i < buflen; ++i) {
			char c = buf[i];
			if (!isprint(c))
				c = '.';
			putchar(c);
		}
		printf(AC_EL("") "\n");
	}
	if (appkeypad)
		PRINTSTR(AC_DECNKM_OFF);
	if (appcursor)
		PRINTSTR(AC_DECCKM_OFF);
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
	for (f = 0; f < lengthof(f_codes); ++f) {
		printf("%" PRIc32 "%2u",
		       f == 0 ? 0x2551 : 0x2502,
		       f_codes[f]);
	}
	printf("\n"
	       "%" PRIc32 "%" PRIc32 "%" PRIc32,
	       0x2550, 0x2550, 0x2550);
	for (f = 0; f < lengthof(f_codes); ++f) {
		printf("%" PRIc32 "%" PRIc32 "%" PRIc32,
		       f == 0 ? 0x256c : 0x256a,
		       0x2550, 0x2550);
	}
	for (b = 0; b < lengthof(b_codes); ++b) {
		printf("\n%3u", b_codes[b]);
		for (f = 0; f < lengthof(f_codes); ++f) {
			printf("%" PRIc32 "",
			       f == 0 ? 0x2551 : 0x2502);
			printf(SESC "[%u;%um%" PRIc32 "%" PRIc32 SESC "[m",
			       b_codes[b], f_codes[f],
			       0x25c4, 0x25ba);
		}
	}
	printf("\n");
	return 0;
}
/************************************************************************/





/************************************************************************/
#if defined(__i386__) || defined(__x86_64__)
#define HAVE_MAIN_FPU
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
#endif /* __i386__ || __x86_64__ */
/************************************************************************/





/************************************************************************/
int main_fork(int argc, char *argv[], char *envp[]) {
	unsigned int depth = 0;
	unsigned int max_depth = 1;
	bool in_child = false;
	pid_t mygroup = getpgid(0);
	static char const lockfile[] = "/tmp/.fork-lock";
	(void)argc, (void)argv, (void)envp;
	if (argc >= 2)
		max_depth = (unsigned int)atoi(argv[1]);
	unlink(lockfile);
	for (;;) {
		pid_t cpid;
		if (depth == max_depth) {
			fd_t lock;
			/* Kill the entire process group  which should contain about a  gazillion
			 * threads at this point, but use a lock-file to only send a signal once.
			 *
			 * This wouldn't actually  be necessary,  but we  want to  ensure that  a
			 * single signal is enough to reach everyone, even if some of our sibling
			 * threads are currently in the process of being created. */
			lock = open(lockfile, O_WRONLY | O_CREAT | O_EXCL, 0644); /* NOLINT */
			if (lock >= 0) {
				kill(-mygroup, SIGKILL);
#ifdef __debugbreak
				__debugbreak();
#endif /* __debugbreak */
				abort();
			}
		}
		cpid = fork();
		if (cpid == 0) {
			if (!in_child)
				++depth;
			in_child = true;
			continue;
		}
		{
			char buf[64];
			size_t len;
			len = sprintf(buf, "spawned: %d\n", cpid);
			write(STDOUT_FILENO, buf, len);
		}
		if (in_child) {
			in_child = false;
			++depth;
			continue;
		}
	}
	return 0;
}
/************************************************************************/





/************************************************************************/
int main_forkbomb(int argc, char *argv[], char *envp[]) {
	(void)argc, (void)argv, (void)envp;
	/* Just your traditional fork-bomb
	 * Use CTRL+C to kill all of the created processes at once.
	 *
	 * And with the KOS kernel now implementing a CFS-based  scheduler,
	 * it should be fairly unlikely for the system to become completely
	 * unresponsive during. */
	for (;;) {
		pid_t cpid;
		cpid = fork();
		(void)cpid; /* Prevent compiler warnings. */
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
			printf("envp[%" PRIuSIZ "]: %q\n", i, envp[i]);
	}
	return 0;
}
/************************************************************************/





/************************************************************************/
int main_args(int argc, char *argv[], char *envp[]) {
	int i;
	(void)argv, (void)envp;
	printf("argc = %d\n", argc);
	for (i = 0; i < argc; ++i)
		printf("argv[%d] = %q\n", i, argv[i]);
	return 0;
}
/************************************************************************/





/************************************************************************/
int main_prognam(int argc, char *argv[], char *envp[]) {
	(void)argc, (void)argv, (void)envp;
	printf("program_invocation_name       = %q\n", program_invocation_name);
	printf("program_invocation_short_name = %q\n", program_invocation_short_name);
	printf("dlmodulename(dlopen(NULL, 0)) = %q\n", dlmodulename(dlopen(NULL, 0)));
	printf("getauxval(AT_EXECFN)          = %q\n", (char *)getauxval(AT_EXECFN));
	return 0;
}
/************************************************************************/





/************************************************************************/
int main_logtime(int argc, char *argv[], char *envp[]) {
	(void)argc, (void)argv, (void)envp;
	struct timeval prev = { 0, 0 };
	for (;;) {
		struct timeval next;
		gettimeofday(&next, NULL);
		if (next.tv_sec != prev.tv_sec) {
			char buf[26];
			ctime_r(&next.tv_sec, buf);
			printf(AC_CUP("", "") "%s" AC_EL(""), strrstrip(buf));
			fflush(stdout);
		}
		if (next >= prev) {
			prev = next;
			/*sleep(1);*/
			continue;
		}
		{
			char buf_prev[26], buf_next[26];
			syslog(LOG_ERR,
			       "ERROR:\n"
			       "\tprev: {%" PRId64 ", %" PRIuPTR "} (%q)\n"
			       "\tnext: {%" PRId64 ", %" PRIuPTR "} (%q)\n",
			       (s64)prev.tv_sec, (uintptr_t)prev.tv_usec, ctime_r(&prev.tv_sec, buf_prev),
			       (s64)next.tv_sec, (uintptr_t)next.tv_usec, ctime_r(&next.tv_sec, buf_next));
		}
		prev = next;
		getchar();
	}
	return 0;
}
/************************************************************************/




/************************************************************************/
int main_sleep(int argc, char *argv[], char *envp[]) {
	(void)argc, (void)argv, (void)envp;
	for (;;) {
		char buf[26];
		struct timeval now;
		struct timespec delay;
		gettimeofday(&now, NULL);
		ctime_r(&now.tv_sec, buf);
		printf(AC_CUP("", "") "%s  [usec:%.6u]" AC_EL(""),
		       strrstrip(buf), (unsigned int)now.tv_usec);
		fflush(stdout);
		delay.tv_sec  = 0;
		delay.tv_nsec = 0;
		delay.add_microseconds(1000000 - now.tv_usec);
		nanosleep(&delay, NULL);
	}
	return 0;
}
/************************************************************************/




/************************************************************************/
static int my_static = 0;
int main_dl(int argc, char *argv[], char *envp[]) {
	(void)argc, (void)argv, (void)envp;
	printf("stdout    @ %p\n", &stdout);
	printf("my_static @ %p\n", &my_static);
	printf("printf    @ %p\n", (void *)&printf);
	printf("printf    @ %p (dlsym)\n", dlsym(RTLD_DEFAULT, "printf"));
	printf("vprintf   @ %p (dlsym)\n", dlsym(RTLD_DEFAULT, "vprintf"));
	return 0;
}
/************************************************************************/




/************************************************************************/
int main_ustring(int argc, char *argv[], char *envp[]) {
	(void)argc, (void)argv, (void)envp;
	{
		char const *s8 = "8-bit string";
		char16_t const *s16 = u"16-bit string";
		char32_t const *s32 = U"32-bit string";
		wchar_t const *sw = L"wide-character string";
		printf("%s    (%q)\n", s8, s8);
		printf("%I8s  (%I8q)\n", s8, s8);
		printf("%I16s (%I16q)\n", s16, s16);
		printf("%I32s (%I32q)\n", s32, s32);
		printf("%ls   (%lq)\n", sw, sw);
	}
	return 0;
}
/************************************************************************/




/************************************************************************/
int main_float(int argc, char *argv[], char *envp[]) {
	(void)argc, (void)argv, (void)envp;
	printf("1/1 = %f\n", 1.0 / 1.0);
	printf("1/2 = %f\n", 1.0 / 2.0);
	printf("1/3 = %f\n", 1.0 / 3.0);
	printf("1/4 = %f\n", 1.0 / 4.0);
	return 0;
}
/************************************************************************/




/************************************************************************/
int main_sock(int argc, char *argv[], char *envp[]) {
	fd_t sock;
	struct sockaddr_in in;
	char payload[] = "Wazzzzaaaaaap!\n";
	char response[64];
	ssize_t resplen;
	(void)argc, (void)argv, (void)envp;
	ksysctl_insmod("ne2k", NULL);
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); /* NOLINT */
	if (sock < 0)
		err(EXIT_FAILURE, "socket() failed");
	in.sin_family      = AF_INET;
	in.sin_addr.s_addr = inet_addr("10.0.2.2");
	in.sin_port        = htons(8080);
	if (connect(sock, (struct sockaddr *)&in, sizeof(in)))
		err(EXIT_FAILURE, "connect() failed");
	if (send(sock, payload, sizeof(payload), 0) < 0)
		err(EXIT_FAILURE, "send() failed");
	resplen = recv(sock, response, sizeof(response), 0);
	if (resplen < 0)
		err(EXIT_FAILURE, "recv() failed");
	printf("Response: %$q\n", (size_t)resplen, response);
	close(sock);
	return 0;
}
/************************************************************************/




#if defined(__i386__) || defined(__x86_64__)
#define HAVE_MAIN_SYSENTER 1
/************************************************************************/
int main_sysenter(int argc, char *argv[], char *envp[]) {
	(void)argc, (void)argv, (void)envp;
	__asm__(".byte 0x0f, 0x34\n");
	return 0;
}
/************************************************************************/
#endif /* __i386__ || __x86_64__ */





#if defined(__i386__) || defined(__x86_64__)
#define HAVE_MAIN_SGBASE 1
/************************************************************************/
int main_sgbase(int argc, char *argv[], char *envp[]) {
	(void)argc, (void)argv, (void)envp;
	printf("%%fs.base = %p\n", __rdfsbase());
	printf("%%gs.base = %p\n", __rdgsbase());
	return 0;
}
/************************************************************************/
#endif /* __i386__ || __x86_64__ */





#if defined(__i386__) || defined(__x86_64__)
#define HAVE_MAIN_INT3 1
/************************************************************************/
int main_int3(int argc, char *argv[], char *envp[]) {
	(void)argc, (void)argv, (void)envp;
	__asm__ __volatile__("int3");
	return 0;
}
/************************************************************************/
#endif /* __i386__ || __x86_64__ */





/************************************************************************/
PRIVATE ssize_t FORMATPRINTER_CC
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
	/* XXX: While this ~does~ work to do  exactly what it's supposed to  do,
	 *      Visual Studio's MIEngine doesn't seem to understand the protocol
	 *      that  GDB  uses  to  transmit  generic,  human-readable  strings
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
	 *               Those    actually   appear   as-is   in   the   console.
	 *      However: When running GDB normally from a console, the text is displayed
	 *               properly:
	 *       >>   a = Value
	 *       >>    for a
	 *       >>   b = Value for b
	 *       >>   c = fdadsfasdn
	 *       >>   d = This is c
	 * So the problem with this is actually Visual Studio...
	 * This sucks! You want to know why I added support for message debug traps?
	 * I added it so that I could output text to the Visual studio output window
	 * without that annoying `cmd: ' prefix caused  by the fact that all  output
	 * currently  is piped through  magic (which is started  by `cmd', hence the
	 * prefix), and is considered as a side channel by visual studio, and  there
	 * doesn't  seem  to be  a  way to  prevent  the `cmd: '  prefix  for those.
	 * Now  why do I care? Well: Because of that prefix, it is impossible for me
	 * to output file paths in  such a way that  they become clickable so-as  to
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



/************************************************************************/
PRIVATE void *main_yield_thread(void *UNUSED(arg)) {
	for (;;)
		pthread_yield();
}

int main_yield(int argc, char *argv[], char *envp[]) {
	pthread_t pt;
	(void)argc, (void)argv, (void)envp;
	pthread_create(&pt, NULL, &main_yield_thread, NULL);
	pthread_create(&pt, NULL, &main_yield_thread, NULL);
	pthread_create(&pt, NULL, &main_yield_thread, NULL);
	for (;;)
		pthread_yield();
	return 0;
}
/************************************************************************/



/************************************************************************/
static u32 volatile viovalue = 0;
PRIVATE NONNULL((1)) u32 LIBVIO_CC
myvio_readl(struct vioargs *__restrict args, vio_addr_t addr) {
	/* This function is called synchronously every time our VIO region is read from! */
	printf("VIO:readl(%p)\n", vioargs_faultaddr(args, addr));
	return viovalue++;
}

PRIVATE struct vio_ops const myvio_ops = {
	/* .vo_read = */ VIO_CALLBACK_INIT_READ(NULL, NULL, &myvio_readl, NULL),
};

int main_vio(int argc, char *argv[], char *envp[]) {
	void *libvio;
	PVIO_CREATE vio_create;
	PVIO_DESTROY vio_destroy;
	fd_t uviofd;
	u32 volatile *baseaddr;
	(void)argc, (void)argv, (void)envp;

	/* Load VIO library */
	libvio = dlopen(LIBVIO_LIBRARY_NAME, RTLD_LOCAL);
	if (!libvio)
		err(1, "dlopen failed: %s", dlerror());
	*(void **)&vio_create = dlsym(libvio, "vio_create");
	if (!vio_create)
		err(1, "dlsym failed: %s", dlerror());
	*(void **)&vio_destroy = dlsym(libvio, "vio_destroy");
	if (!vio_destroy)
		err(1, "dlsym failed: %s", dlerror());

	/* Create VIO mapping */
	uviofd = vio_create(&myvio_ops, NULL, 0x1000, O_CLOEXEC | O_CLOFORK);
	if (uviofd < 0)
		err(1, "vio_create failed");
	printf("uviofd = %d\n", uviofd);
	baseaddr = (u32 volatile *)mmap(NULL, 0x1000,
	                                PROT_READ | PROT_WRITE,
	                                MAP_FILE | MAP_SHARED,
	                                uviofd, 0);
	if ((void *)baseaddr == MAP_FAILED)
		err(1, "mmap failed");

	/* Access VIO memory */
	printf("Start reading from: %p\n", baseaddr);
	viovalue = 42;
	printf("read: %" PRIu32 "\n", baseaddr[0]); /* 42 */
	printf("read: %" PRIu32 "\n", baseaddr[1]); /* 43 */
	printf("read: %" PRIu32 "\n", baseaddr[4]); /* 44 */
	printf("read: %" PRIu32 "\n", baseaddr[3]); /* 45 */
	printf("read: %" PRIu32 "\n", baseaddr[2]); /* 46 */
	viovalue = 7;
	printf("read: %" PRIu32 "\n", baseaddr[19]); /* 7 */
	printf("read: %" PRIu32 "\n", baseaddr[8]);  /* 8 */
	printf("read: %" PRIu32 "\n", baseaddr[0]);  /* 9 */

	/* Cleanup... */
	munmap((void *)baseaddr, 0x1000);
	vio_destroy(uviofd);
	dlclose(libvio);
	return 0;
}
/************************************************************************/



/************************************************************************/
#ifdef RTM_STARTED
#define HAVE_MAIN_RTM
int main_rtm(int argc, char *argv[], char *envp[]) {
	static volatile int a, b, c;
	rtm_status_t status;
	(void)argc, (void)argv, (void)envp;
	a = 10;
	b = 20;
	c = 30;
	status = rtm_begin();
	if (status == RTM_STARTED) {
		if (a < b)
			c = b;
		b = a * c;
		a = b - c;
		rtm_end();
		printf("RTM success\n");
		printf("\ta = %d\n", a); /* 180 */
		printf("\tb = %d\n", b); /* 200 */
		printf("\tc = %d\n", c); /* 20  */
	} else {
		printf("RTM status: %#" PRIxN(__SIZEOF_RTM_STATUS_T__) "\n", status);
		printf("\ta = %d\n", a); /* 10 */
		printf("\tb = %d\n", b); /* 20 */
		printf("\tc = %d\n", c); /* 30 */
	}
	return 0;
}
#endif /* RTM_STARTED */
/************************************************************************/



/************************************************************************/
int main_fault(int argc, char *argv[], char *envp[]) {
	(void)argc, (void)argv, (void)envp;
	/* Just a simple program that will cause a SIGSEGV */
	*(int volatile *)0x123 = 321;
	return 0;
}
/************************************************************************/



/************************************************************************/
int main_leak(int argc, char *argv[], char *envp[]) {
	(void)argc, (void)argv, (void)envp;
	/* Just check for leaks in kernel-space. */
	size_t count;
	count = KSysctl(KSYSCTL_SYSTEM_MEMORY_DUMP_LEAKS);
	assertf(count == 0, "Leaks: %" PRIuSIZ, count);
	KSysctl(KSYSCTL_SYSTEM_MEMORY_VALIDATE_PADDING);
	return 0;
}
/************************************************************************/



/************************************************************************/
int main_vfork(int argc, char *argv[], char *envp[]) {
	int status;
	pid_t pid;
	errno_t errno_after_vfork;
	(void)argc, (void)argv, (void)envp;
	errno = 0;
	pid = vfork();
	if (pid == 0) {
		dprintf(STDOUT_FILENO, "Child process: %u\n", getpid());
		errno = 1234;
		execl("/bin/busybox", "sh", "-c", "echo Child says: hello!", (char *)0);
		_exit(77);
	}
	errno_after_vfork = errno;
	if (pid < 0)
		err(1, "vfork() failed");
	dprintf(STDOUT_FILENO, "Parent process:    %u\n", getpid());
	dprintf(STDOUT_FILENO, "Child is:          %u\n", pid);
	dprintf(STDOUT_FILENO, "errno_after_vfork: %d\n", errno_after_vfork); /* 1234 */

	/* Wait for the child to exit */
	while (waitpid(pid, &status, 0) < 0) {
		if (errno == EINTR)
			continue;
		err(1, "waitpid() failed");
	}
	dprintf(STDOUT_FILENO, "Child exited with: %d\n", status);
	return 0;
}
/************************************************************************/



/************************************************************************/
PRIVATE sigset_t const full_sigset = SIGSET_INIT_FULL;
PRIVATE void *sigbounce_threadmain(void *) {
	/* Block _all_ signals.
	 * This function's implementation will also ensure
	 * that  we're  using the  userprocmask mechanism. */
	setsigmaskptr((sigset_t *)&full_sigset);
	for (;;) {
		printf("sigbounce_threadmain(): %d\n", gettid());
		pause();
	}
	return NULL;
}

int main_sigbounce(int argc, char *argv[], char *envp[]) {
	pthread_t pt;
	(void)argc, (void)argv, (void)envp;

	/* Block _all_ signals.
	 * This function's implementation will also ensure
	 * that  we're  using the  userprocmask mechanism. */
	setsigmaskptr((sigset_t *)&full_sigset);

	/* Create an additional thread, thus bumping our process's total
	 * thread count up to 2, which is needed to get the two  threads
	 * the signal used to end up bouncing between. */
	pthread_create(&pt, NULL, &sigbounce_threadmain, NULL);

	/* A test program  to test the  corner-case detailed in  `sigmask_ismasked_in()'
	 * To trigger the corner-case, press CTRL+C after running `playground sigbounce'
	 *
	 * At  that point, the kernel will send a signal to our process, which used
	 * to keep on bouncing between thread. This was not intended, and has since
	 * been fixed!
	 *
	 * This test program was written to consistently trigger the problem and
	 * test that it no longer happens! */
	while (getchar() != '\n')
		;
	return 0;
}
/************************************************************************/



/************************************************************************/
int main_bigfile(int argc, char *argv[], char *envp[]) {
	fd_t fd;
	byte_t *data;
	size_t i, len;
	(void)argc, (void)argv, (void)envp;

	len  = 4096;
	data = (byte_t *)Malloc(len);
	for (i = 0; i < len; ++i)
		data[i] = (byte_t)(i & 0xff);
	fd = Open("/var/bigfile.dat", O_CREAT | O_RDWR | O_TRUNC, 0644);
	Write(fd, data, len);
	fsync(fd);
	close(fd);
	free(data);
	return 0;
}
/************************************************************************/



/************************************************************************/
int main_pass(int argc, char *argv[], char *envp[]) {
	char *user, *pass;
	(void)argc, (void)argv, (void)envp;
	printf("===FAKE LOGIN===\n");
	user = getpassfd("user: ", NULL, 0, NULL,
	                 GETPASS_NEED_TTY | GETPASS_FAIL_EOF |
	                 GETPASS_ECHO | GETPASS_ECHO_NL,
	                 0);
	if (!user)
		err(1, "getpassfd() failed");
	pass = getpassfd("pass: ", NULL, 0, NULL,
	                 GETPASS_NEED_TTY | GETPASS_FAIL_EOF |
	                 GETPASS_ECHO_STAR | GETPASS_ECHO_NL,
	                 0);
	if (!pass)
		err(1, "getpassfd() failed");
	printf("you entered: %q, %q\n", user, pass);
	free(user);
	free(pass);
	return 0;
}
/************************************************************************/



/************************************************************************/
int main_assert(int argc, char *argv[], char *envp[]) {
	volatile int x;
	(void)argc, (void)argv, (void)envp;
	/* Demo for what happens when a user-space assert fails. */
	x = 42;
	assert(x == 0);
	return 0;
}
/************************************************************************/



/************************************************************************/
int main_cc(int argc, char *argv[], char *envp[]) {
	(void)argc, (void)argv, (void)envp;
	/* Clear system caches. */
	KSysctl(KSYSCTL_SYSTEM_CLEARCACHES);
	return 0;
}
/************************************************************************/



/************************************************************************/
int main_fg(int argc, char *argv[], char *envp[]) {
	(void)argc, (void)argv, (void)envp;
	printf("Before fork: %d\n", getpid());
	printf("	tcgetpgrp(0) = %d\n", tcgetpgrp(0));
	pid_t cpid = fork();
	if (cpid == 0) {
		printf("In child #1: %d (getpgid(0) = %d, tcgetpgrp(0) = %d)\n",
			getpid(), getpgid(0), tcgetpgrp(0));
		setpgid(0, getpid());
		printf("In child #2: %d (getpgid(0) = %d, tcgetpgrp(0) = %d)\n",
			getpid(), getpgid(0), tcgetpgrp(0));
		_Exit(1);
	}
	printf("In parent: %d (cpid: %d, tcgetpgrp(0) = %d)\n",
		getpid(), cpid, tcgetpgrp(0));
	int st;
	while (waitpid(cpid, &st, 0) != cpid)
		;
	printf("Child exited: %#x (tcgetpgrp(0) = %d)\n",
		st, tcgetpgrp(0));
	return 0;
}
/************************************************************************/



/************************************************************************/
int main_fatls(int argc, char *argv[], char *envp[]) {
	static char *default_args[] = { (char *)"." };
	(void)envp;
	--argc;
	++argv;
	if (!argc) {
		argv = default_args;
		argc = 1;
	}
	for (; argc; --argc, ++argv) {
		fd_t dirfd = open(*argv, O_DIRECTORY | O_RDONLY); /* NOLINT */
		if (dirfd < 0)
			err(1, "fatls: failed to open %q", *argv);
		printf("%s:\n", *argv);
		for (;;) {
			struct __fat_dirent ent[2];
			int status = ioctl(dirfd, VFAT_IOCTL_READDIR_BOTH, &ent[0]);
			if (status == 0)
				break;
			if (status == -1) {
				err(1, "fatls: ioctl failed");
				break;
			}
			printf("%-12s %-50s %#lx %lu\n",
			       ent[0].d_name,
			       ent[1].d_name,
			       ent[1].d_ino,
			       ent[1].d_off);
		}
		close(dirfd);
	}
	return 0;
}
/************************************************************************/



/************************************************************************/
int main_charmap(int argc, char *argv[], char *envp[]) {
	char const *cpvga[] = { /* s.a. /src/libvgastate/vgastate.c */
		"\uFFFD\u263A\u263B\u2665\u2666\u2663\u2660\u2022\u25D8\u25CB\u25D9\u2642\u2640\u266A\u266B\u263C",
		"\u25BA\u25C4\u2195\u203C\u00B6\u00A7\u25AC\u21A8\u2191\u2193\u2192\u2190\u221F\u2194\u25B2\u25BC",
		"\u0020\u0021\u0022\u0023\u0024\u0025\u0026\u0027\u0028\u0029\u002A\u002B\u002C\u002D\u002E\u002F",
		"\u0030\u0031\u0032\u0033\u0034\u0035\u0036\u0037\u0038\u0039\u003A\u003B\u003C\u003D\u003E\u003F",
		"\u0040\u0041\u0042\u0043\u0044\u0045\u0046\u0047\u0048\u0049\u004A\u004B\u004C\u004D\u004E\u004F",
		"\u0050\u0051\u0052\u0053\u0054\u0055\u0056\u0057\u0058\u0059\u005A\u005B\u005C\u005D\u005E\u005F",
		"\u0060\u0061\u0062\u0063\u0064\u0065\u0066\u0067\u0068\u0069\u006A\u006B\u006C\u006D\u006E\u006F",
		"\u0070\u0071\u0072\u0073\u0074\u0075\u0076\u0077\u0078\u0079\u007A\u007B\u007C\u007D\u007E\u2302",
		"\u00C7\u00FC\u00E9\u00E2\u00E4\u00E0\u00E5\u00E7\u00EA\u00EB\u00E8\u00EF\u00EE\u00EC\u00C4\u00C5",
		"\u00C9\u00E6\u00C6\u00F4\u00F6\u00F2\u00FB\u00F9\u00FF\u00D6\u00DC\u00A2\u00A3\u00A5\u20A7\u0192",
		"\u00E1\u00ED\u00F3\u00FA\u00F1\u00D1\u00AA\u00BA\u00BF\u2310\u00AC\u00BD\u00BC\u00A1\u00AB\u00BB",
		"\u2591\u2592\u2593\u2502\u2524\u2561\u2562\u2556\u2555\u2563\u2551\u2557\u255D\u255C\u255B\u2510",
		"\u2514\u2534\u252C\u251C\u2500\u253C\u255E\u255F\u255A\u2554\u2569\u2566\u2560\u2550\u256C\u2567",
		"\u2568\u2564\u2565\u2559\u2558\u2552\u2553\u256B\u256A\u2518\u250C\u2588\u2584\u258C\u2590\u2580",
		"\u03B1\u00DF\u2596\u2597\u2598\u2599\u259A\u259B\u259C\u259D\u259E\u259F\u221E\u03C6\u03B5\u2229",
		"\u2261\u00B1\u2265\u2264\u2320\u2321\u00F7\u2248\u00B0\u2219\u00B7\u221A\u207F\u00B2\u25A0\uE888",
	};
	unsigned int i;
	(void)argc, (void)argv, (void)envp;
	for (i = 0; i < 16; ++i) {
		printf(AC_COLOR(ANSITTY_CL_WHITE, ANSITTY_CL_BLACK) "%s    "
		       AC_COLOR(ANSITTY_CL_BLACK, ANSITTY_CL_WHITE) "%s"
		       AC_DEFCOLOR "\n",
		       cpvga[i], cpvga[i]);
	}
	return 0;
}
/************************************************************************/



/************************************************************************/
int main_dumpdebug(int argc, char *argv[], char *envp[]) {
	void *libdebuginfo;
	void *dlmod;
	PDEBUG_REPR_DUMP debug_repr_dump;
	(void)envp;
	if (argc != 2) {
		/* FIXME: Compiler error because of ambiguity as a result of
		 * >> namespace std { }
		 * >> using namespace std;
		 * >> __CEIDECLARE_GCCNCX(__ATTR_NORETURN,void,__THROWING,exit,(int __status),{ __builtin_exit(__status); })
		 * >> namespace std {
		 * >> __NAMESPACE_GLB_USING_OR_IMPL(exit, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NORETURN void (__LIBCCALL exit)(int __status) __THROWS(...) { (:: exit)(__status); })
		 * >> }
		 *
		 * Because of the `using namespace std;', there are now 2 symbols `exit' within
		 * the  global namespace. *sigh* (all of this  just because of GCC's debug info
		 * bloat; s.a. https://gcc.gnu.org/bugzilla/show_bug.cgi?id=96417) */
		/*exit(1);*/
		return 1;
	}
	libdebuginfo = dlopen(LIBDEBUGINFO_LIBRARY_NAME, RTLD_LOCAL);
	assertf(libdebuginfo, "%s", dlerror());
	*(void **)&debug_repr_dump = dlsym(libdebuginfo, "debug_repr_dump");

	dlmod = dlgetmodule(argv[1]);
	if (!dlmod)
		dlmod = dlopen(argv[1], RTLD_LOCAL);
	if (!dlmod) {
		fprintf(stderr, "dumpdebug: dlopen(%q): %s\n", argv[1], dlerror());
		return 1;
	}
	{
		size_t debug_info_size, debug_abbrev_size, debug_str_size, debug_line_str_size, debug_loclists_size;
		byte_t const *debug_info_data, *debug_abbrev_data, *debug_str_data, *debug_line_str_data, *debug_loclists_data;
		debug_info_data     = (byte_t const *)dlinflatesection(dllocksection(dlmod, ".debug_info"), &debug_info_size);
		debug_abbrev_data   = (byte_t const *)dlinflatesection(dllocksection(dlmod, ".debug_abbrev"), &debug_abbrev_size);
		debug_str_data      = (byte_t const *)dlinflatesection(dllocksection(dlmod, ".debug_str"), &debug_str_size);
		debug_line_str_data = (byte_t const *)dlinflatesection(dllocksection(dlmod, ".debug_line_str"), &debug_line_str_size);
		debug_loclists_data = (byte_t const *)dlinflatesection(dllocksection(dlmod, ".debug_loclists"), &debug_loclists_size);
		debug_repr_dump(&file_printer, stdout,
		                debug_info_data, debug_info_data + debug_info_size,
		                debug_abbrev_data, debug_abbrev_data + debug_abbrev_size,
		                debug_loclists_data, debug_loclists_data + debug_loclists_size, NULL, NULL,
		                debug_str_data, debug_str_data + debug_str_size,
		                debug_line_str_data, debug_line_str_data + debug_str_size);
	}
	return 0;
}
/************************************************************************/



/************************************************************************/
int main_leakmon(int argc, char *argv[], char *envp[]) {
	size_t loop;
	static char const reset[] = AC_ED("") AC_CUP0;
	char **volatile used_argv = argv; /* Prevents warnings about "returns_twice" and vfork()... */
	write(STDOUT_FILENO, reset, sizeof(reset) - sizeof(char));
	(void)argc;
	++used_argv;

	for (loop = 0;; ++loop) {
		int status;
		pid_t cpid;
		/*KSysctl(KSYSCTL_SYSTEM_CLEARCACHES);*/
		KSysctl(KSYSCTL_SYSTEM_MEMORY_DUMP_LEAKS);
		dprintf(STDOUT_FILENO, AC_ED("") AC_CUP0 "loop: %" PRIuSIZ "\n", loop);
		cpid = vfork();
		if (cpid == 0) {
			execvpe(used_argv[0], used_argv, envp);
			_Exit(127);
		}
		if (cpid < 0)
			err(1, "vfork");
		for (;;) {
			pid_t error = waitpid(cpid, &status, 0);
			if (error == cpid)
				break;
			if (error >= 0)
				continue;
			if (errno != EINTR)
				err(1, "waitpid");
		}
		if (!WIFEXITED(status))
			return 1;
		if (WEXITSTATUS(status) != 0)
			return WEXITSTATUS(status);
	}
	return 0;
}
/************************************************************************/



/************************************************************************/
int main_dosenv(int argc, char *argv[], char *envp[]) {
	int (__LIBDCALL *dos_setenv)(char const *varname, char const *val, int replace);
	char ***p_dos_environ, **dos_environ;
	(void)argc, (void)argv, (void)envp;

	/* Enable dosfs emulation. - Otherwise, libc won't
	 * convert  environ  paths  to/from  DOS   format.
	 *
	 * Note that in PE binaries, dosfs emulation will
	 * be turned on by default! */
	dosfs_setenabled(DOSFS_ENABLED);

	if ((*(void **)&p_dos_environ = dlsym(RTLD_DEFAULT, "DOS$_environ")) == NULL ||
	    (*(void **)&dos_setenv = dlsym(RTLD_DEFAULT, "DOS$setenv")) == NULL)
		err(1, "dlerror: %s", dlerror());
	if ((dos_environ = *p_dos_environ) != NULL) {
		size_t i;
		for (i = 0; environ[i] || dos_environ[i]; ++i)
			printf("%s\t%s\n", environ[i], dos_environ[i]);
	}
	if ((*dos_setenv)("PATH", "C:\\Windows\\system32;C:\\Window;C:\\Program Files\\bin", 1))
		err(1, "DOS$setenv");
	if ((dos_environ = *p_dos_environ) != NULL) {
		size_t i;
		for (i = 0; environ[i] || dos_environ[i]; ++i)
			printf("%s\t%s\n", environ[i], dos_environ[i]);
	}
	return 0;
}
/************************************************************************/



/************************************************************************/
int main_stackend(int argc, char *argv[], char *envp[]) {
	void **p_stackend;
	(void)argc, (void)argv, (void)envp;
	p_stackend = (void **)dlsym(RTLD_DEFAULT, "__libc_stack_end");
	if (!p_stackend)
		err(1, "dlsym failed: %s", dlerror());
	printf(" __libc_stack_end = %p\n", p_stackend);
	printf("*__libc_stack_end = %p\n", *p_stackend);
	assert(*p_stackend != NULL);
	return 0;
}
/************************************************************************/



/************************************************************************/
int main_ttys(int argc, char *argv[], char *envp[]) {
	struct ttyent *ent;
	(void)argc, (void)argv, (void)envp;
	if (!setttyent())
		err(1, "setttyent() failed");
	while ((ent = getttyent()) != NULL) {
		printf("getttyent: { ty_name:%q, ty_getty:%q, ty_type:%q, ty_status:%#x, "
		                    "ty_window: %q, ty_comment: %q, ty_group: %q}\n",
		       ent->ty_name, ent->ty_getty, ent->ty_type,
		       ent->ty_status, ent->ty_window, ent->ty_comment,
		       ent->ty_group);
	}
	endttyent();
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
	{ "args", &main_args },
	{ "dprint", &main_dprint },
	{ "prognam", &main_prognam },
	{ "rawterm", &main_rawterm },
	{ "color", &main_color },
#ifdef HAVE_MAIN_FPU
	{ "fpu", &main_fpu },
#endif /* HAVE_MAIN_FPU */
	{ "fork", &main_fork },
	{ "forkbomb", &main_forkbomb },
	{ "logtime", &main_logtime },
	{ "sleep", &main_sleep },
	{ "dl", &main_dl },
	{ "ustring", &main_ustring },
	{ "float", &main_float },
	{ "sock", &main_sock },
#ifdef HAVE_MAIN_SYSENTER
	{ "sysenter", &main_sysenter },
#endif /* HAVE_MAIN_SYSENTER */
#ifdef HAVE_MAIN_SGBASE
	{ "sgbase", &main_sgbase },
#endif /* HAVE_MAIN_SGBASE */
#ifdef HAVE_MAIN_INT3
	{ "int3", &main_int3 },
#endif /* HAVE_MAIN_INT3 */
	{ "yield", &main_yield },
	{ "vio", &main_vio },
#ifdef HAVE_MAIN_RTM
	{ "rtm", &main_rtm },
#endif /* HAVE_MAIN_RTM */
	{ "fault", &main_fault },
	{ "leak", &main_leak },
	{ "vfork", &main_vfork },
	{ "sigbounce", &main_sigbounce },
	{ "bigfile", &main_bigfile },
	{ "pass", &main_pass },
	{ "assert", &main_assert },
	{ "cc", &main_cc },
	{ "charmap", &main_charmap },
	{ "dumpdebug", &main_dumpdebug },
	{ "fg", &main_fg },
	{ "fatls", &main_fatls },
	{ "leakmon", &main_leakmon },
	{ "dosenv", &main_dosenv },
	{ "stackend", &main_stackend },
	{ "ttys", &main_ttys },
	/* TODO: On x86_64, add a playground that:
	 *   - mmap(0x00007ffffffff000, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_ANON|MAP_FIXED);
	 *   - WRITE(0x00007ffffffffffe, [0x0f, 0x05]); // syscall
	 *   - jmp 0x00007ffffffffffe
	 * By doing this, the syscall will return to a non-canonical address,
	 * which is something  that normally  will cause sysret  to #GP  with
	 * user-space  registers  (this  is a  known  bug in  all  x86 cpus).
	 * KOS (should) prevent this  by the `testb  $(0), 0(%rcx)' that  can
	 * be  found  in `/kos/src/kernel/core/arch/i386/syscall/sysret64.S',
	 * however that  check hasn't  been tested  thus far,  and it  really
	 * should get tested!
	 *
	 * Additionally, add another playground that doing the same, just not
	 * at that particular address, such  that the syscall return  address
	 * isn't mapped into memory, but would still be canonical. Then check
	 * if the kernel handles this case correctly as well (single-step the
	 * in-kernel sysret wrapper for this)
	 */
	{ NULL, NULL }
};


int main(int argc, char *argv[], char *envp[]) {
	unsigned int i;
	if (argc < 2) {
		fprintf(stdout, "Usage: %s NAME [ARGS...]\n", argv[0]);
		fprintf(stdout, "Possible values for NAME:\n");
		for (i = 0; defs[i].n; ++i)
			fprintf(stdout, "\t%s\n", defs[i].n);
		return 1;
	}
	for (i = 0; defs[i].n; ++i) {
		if (strcmp(defs[i].n, argv[1]) == 0) {
			/* The `args' program is special, in that we mustn't
			 * strip  the initial `playground' argument from it. */
			if (strcmp(defs[i].n, "args") != 0) {
				--argc;
				++argv;
			}
			return (*defs[i].f)(argc, argv, envp);
		}
	}
	fprintf(stderr, "Unknown name %q\n", argv[1]);
	return 1;
}


DECL_END

#endif /* !GUARD_APPS_PLAYGROUND_MAIN_C */
