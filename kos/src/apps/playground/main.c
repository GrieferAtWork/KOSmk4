/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_APPS_PLAYGROUND_MAIN_C
#define GUARD_APPS_PLAYGROUND_MAIN_C 1
#define _EVERY_SOURCE 1

/* This  program isn't actually meant to do anything.  It is however meant to be used
 * for quickly testing out new features, or checking the behavior of system functions
 * within a live environment. */

#include <hybrid/compiler.h>

#include <arpa/inet.h>
#include <asm/cpu-flags.h>
#include <asm/intrin-fpu.h>
#include <asm/intrin.h>
#include <kos/debugtrap.h>
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
#include <unistd.h>

#include <libansitty/ctl.h>
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
	for (f = 0; f < COMPILER_LENOF(f_codes); ++f) {
		printf("%" PRIc32 "%2u",
		       f == 0 ? 0x2551 : 0x2502,
		       f_codes[f]);
	}
	printf("\n"
	       "%" PRIc32 "%" PRIc32 "%" PRIc32,
	       0x2550, 0x2550, 0x2550);
	for (f = 0; f < COMPILER_LENOF(f_codes); ++f) {
		printf("%" PRIc32 "%" PRIc32 "%" PRIc32,
		       f == 0 ? 0x256c : 0x256a,
		       0x2550, 0x2550);
	}
	for (b = 0; b < COMPILER_LENOF(b_codes); ++b) {
		printf("\n%3u", b_codes[b]);
		for (f = 0; f < COMPILER_LENOF(f_codes); ++f) {
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
	unsigned int depth = 0;
	unsigned int max_depth = 1;
	bool in_child = false;
	bool did_trigger = false;
	pid_t mygroup = getpgid(0);
	static char const lockfile[] = "/tmp/.fork-lock";
	(void)argc, (void)argv, (void)envp;
	if (argc >= 2)
		max_depth = (unsigned int)atoi(argv[1]);
	unlink(lockfile);
	for (;;) {
		pid_t cpid;
		if (depth == max_depth && !did_trigger) {
			fd_t lock;
			/* Kill the entire process group  which should contain about a  gazillion
			 * threads at this point, but use a lock-file to only send a signal once.
			 *
			 * This wouldn't actually  be necessary,  but we  want to  ensure that  a
			 * single signal is enough to reach everyone, even if some of our sibling
			 * threads are currently in the process of being created. */
			lock = open(lockfile, O_WRONLY | O_CREAT | O_EXCL, 0644);
			if (lock >= 0) {
				kill(-mygroup, SIGKILL);
#ifdef __breakpoint
				__breakpoint();
#endif /* __breakpoint */
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
			while (*buf && isspace(strend(buf)[-1]))
				strend(buf)[-1] = '\0';
			printf(AC_CUP("", "") "%s" AC_EL(""), buf);
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
		while (*buf && isspace(strend(buf)[-1]))
			strend(buf)[-1] = '\0';
		printf(AC_CUP("", "") "%s  [usec:%.6u]" AC_EL(""),
		       buf, (unsigned int)now.tv_usec);
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
	printf("stdout   @ %p\n", &stdout);
	printf("my_state @ %p\n", &my_static);
	printf("printf   @ %p\n", (void *)&printf);
	printf("printf   @ %p (dlsym)\n", dlsym(RTLD_DEFAULT, "printf"));
	printf("vprintf  @ %p (dlsym)\n", dlsym(RTLD_DEFAULT, "vprintf"));
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
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
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

PRIVATE struct vio_operators const myvio_ops = {
	/* .vo_read = */ VIO_CALLBACK_INIT_READ(NULL, NULL, &myvio_readl, NULL),
};

int main_vio(int argc, char *argv[], char *envp[]) {
	void *libvio;
	PVIO_CREATE vio_create;
	PVIO_DESTROY vio_destroy;
	fd_t uviofd;
	u32 volatile *baseaddr;
	(void)argc, (void)argv, (void)envp;

	libvio = dlopen(LIBVIO_LIBRARY_NAME, RTLD_LOCAL);
	if (!libvio)
		err(1, "dlopen failed: %s", dlerror());
	*(void **)&vio_create = dlsym(libvio, "vio_create");
	if (!vio_create)
		err(1, "dlsym failed: %s", dlerror());
	*(void **)&vio_destroy = dlsym(libvio, "vio_destroy");
	if (!vio_destroy)
		err(1, "dlsym failed: %s", dlerror());
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
	printf("Start reading from: %p\n", baseaddr);
	viovalue = 42;
	printf("read: %I32u\n", baseaddr[0]); /* 42 */
	printf("read: %I32u\n", baseaddr[1]); /* 43 */
	printf("read: %I32u\n", baseaddr[4]); /* 44 */
	printf("read: %I32u\n", baseaddr[3]); /* 45 */
	printf("read: %I32u\n", baseaddr[2]); /* 46 */
	viovalue = 7;
	printf("read: %I32u\n", baseaddr[19]); /* 7 */
	printf("read: %I32u\n", baseaddr[8]);  /* 8 */
	printf("read: %I32u\n", baseaddr[0]);  /* 9 */

	munmap((void *)baseaddr, 0x1000);
	vio_destroy(uviofd);
	dlclose(libvio);
	return 0;
}
/************************************************************************/



/************************************************************************/
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
	{ "fpu", &main_fpu },
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
	{ "rtm", &main_rtm },
	{ "fault", &main_fault },
	{ "leak", &main_leak },
	{ "vfork", &main_vfork },
	{ "sigbounce", &main_sigbounce },
	{ "bigfile", &main_bigfile },
	{ "pass", &main_pass },
	{ "assert", &main_assert },
	{ "cc", &main_cc },
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
		fprintf(stderr, "Usage: %s NAME [ARGS...]\n", argv[0]);
		fprintf(stderr, "Possible values for NAME:\n");
		for (i = 0; defs[i].n; ++i)
			fprintf(stderr, "\t%s\n", defs[i].n);
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
