/* HASH CRC-32:0xedd3fa73 */
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
#ifndef GUARD_LIBC_AUTO_READPASSPHRASE_C
#define GUARD_LIBC_AUTO_READPASSPHRASE_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "readpassphrase.h"
#include "../user/ctype.h"
#include "../user/fcntl.h"
#include "../user/signal.h"
#include "../user/string.h"
#include "termios.h"
#include "../user/unistd.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <bits/types.h>
#include <asm/os/stdio.h>
#include <asm/os/oflags.h>
#include <libc/errno.h>
#include <paths.h>
#include <asm/crt/readpassphrase.h>
#include <asm/os/termios.h>
#include <bits/os/termios.h>
#include <asm/os/signal.h>
#include <bits/os/sigaction.h>
#ifndef __LOCAL_READPASSPHRASE_HELPERS_DEFINED
__NAMESPACE_LOCAL_BEGIN
#define __LOCAL_READPASSPHRASE_HELPERS_DEFINED
#if defined(__CRT_HAVE_sigaction) || defined(__CRT_HAVE___sigaction)
static signo_t const rpp_signals[] = {
#ifdef __SIGTTOU
	__SIGTTOU, /* This one _must_ be first! */
#endif /* __SIGTTOU */
#ifdef __SIGALRM
	__SIGALRM,
#endif /* __SIGALRM */
#ifdef __SIGHUP
	__SIGHUP,
#endif /* __SIGHUP */
#ifdef __SIGINT
	__SIGINT,
#endif /* __SIGINT */
#ifdef __SIGPIPE
	__SIGPIPE,
#endif /* __SIGPIPE */
#ifdef __SIGQUIT
	__SIGQUIT,
#endif /* __SIGQUIT */
#ifdef __SIGTERM
	__SIGTERM,
#endif /* __SIGTERM */
#ifdef __SIGTSTP
	__SIGTSTP,
#endif /* __SIGTSTP */
#ifdef __SIGTTIN
	__SIGTTIN,
#endif /* __SIGTTIN */
};
static __SIG_ATOMIC_TYPE__ volatile rpp_arrived[__COMPILER_LENOF(rpp_signals)];
static void __LIBCCALL rpp_handler(int signo) {
	unsigned int i;
	for (i = 0;; ++i) {
		if (rpp_signals[i] == signo) {
			rpp_arrived[i] = 1;
			break;
		}
	}
}
#endif /* __CRT_HAVE_sigaction || __CRT_HAVE___sigaction */
__NAMESPACE_LOCAL_END
#endif /* !__LOCAL_READPASSPHRASE_HELPERS_DEFINED */
/* >> readpassphrase(3)
 * @param: flags: Set of `RPP_*' (from `<readpassphrase.h>')
 * @return: buf:  Success
 * @return: NULL: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.bsd") NONNULL((2)) char *
NOTHROW_NCX(LIBCCALL libc_readpassphrase)(char const *prompt,
                                          char *buf,
                                          size_t bufsize,
                                          __STDC_INT_AS_UINT_T flags) {
#if defined(__CRT_HAVE_sigaction) || defined(__CRT_HAVE___sigaction)
	bool must_restart;
#endif /* __CRT_HAVE_sigaction || __CRT_HAVE___sigaction */
	fd_t infd, outfd;
#if (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl))
	struct termios old_ios, new_ios;
#endif /* (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) */
#if defined(__CRT_HAVE_sigaction) || defined(__CRT_HAVE___sigaction)
	struct sigaction old_sact[__COMPILER_LENOF(__NAMESPACE_LOCAL_SYM rpp_signals)];
#endif /* __CRT_HAVE_sigaction || __CRT_HAVE___sigaction */

	/* Validate input arguments. */
	if unlikely(buf == NULL || bufsize < sizeof(char)) {
#ifdef EINVAL
		(void)__libc_seterrno(EINVAL);
#else /* EINVAL */
		(void)__libc_seterrno(1);
#endif /* !EINVAL */
		goto err;
	}

again:
#if defined(__CRT_HAVE_sigaction) || defined(__CRT_HAVE___sigaction)
	must_restart = false;
#endif /* __CRT_HAVE_sigaction || __CRT_HAVE___sigaction */
	infd  = __STDIN_FILENO;
	outfd = __STDIN_FILENO;

	/* Open the relevant output stream. */
	if (!(flags & __RPP_STDIN)) {
#if defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
#ifdef _PATH_TTY
#ifdef __O_RDWR
		infd = libc_open(_PATH_TTY, __O_RDWR);
#else /* __O_RDWR */
		infd = libc_open(_PATH_TTY, 0);
#endif /* !__O_RDWR */
#else /* _PATH_TTY */
#ifdef __O_RDWR
		infd = libc_open("/dev/tty", __O_RDWR);
#else /* __O_RDWR */
		infd = libc_open("/dev/tty", 0);
#endif /* !__O_RDWR */
#endif /* !_PATH_TTY */
		if unlikely(infd == -1) {
#ifdef ENOTTY
			if (flags & __RPP_REQUIRE_TTY)
				(void)__libc_seterrno(ENOTTY);
#endif /* ENOTTY */
			goto err;
		}
		outfd = infd;
#else /* __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) */
#if defined(ENOTTY) && defined(ENOENT)
		(void)__libc_seterrno(flags & __RPP_REQUIRE_TTY ? ENOTTY : ENOENT);
#elif defined(ENOENT)
		(void)__libc_seterrno(ENOENT);
#else /* ... */
		(void)__libc_seterrno(1);
#endif /* !... */
		goto err;
#endif /* !__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat)) */
	}

	/* Update terminal IOS mode to our liking. */
#if (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl))
	if (libc_tcgetattr(infd, &old_ios) != 0) {
		if (flags & RPP_REQUIRE_TTY) {
#ifdef ENOTTY
			(void)__libc_seterrno(ENOTTY);
#endif /* ENOTTY */
			goto err_infd;
#define __PRIVATE_WANT_err_infd
		}
		libc_memcpy(&new_ios, &old_ios, sizeof(struct termios));
		if (!(flags & __RPP_ECHO_ON)) {
#if defined(__ECHO) && defined(__ECHONL)
			new_ios.c_lflag &= ~(__ECHO | __ECHONL);
#elif defined(__ECHO)
			new_ios.c_lflag &= ~(__ECHO);
#elif defined(__ECHONL)
			new_ios.c_lflag &= ~(__ECHONL);
#endif /* ... */
		}
#ifdef __VSTATUS
		if (term.c_cc[__VSTATUS] != __VDISABLE)
			term.c_cc[__VSTATUS] = __VDISABLE;
#endif /* __VSTATUS */
		if (libc_memcmp(&old_ios, &new_ios, sizeof(struct termios)) != 0) {
#if defined(__TCSAFLUSH) && defined(__TCSASOFT)
			if (libc_tcsetattr(infd, __TCSAFLUSH | __TCSASOFT, &new_ios) != 0)
				goto err_infd;
#elif defined(__TCSAFLUSH)
			if (libc_tcsetattr(infd, __TCSAFLUSH, &new_ios) != 0)
				goto err_infd;
#else /* ... */
			if (libc_tcsetattr(infd, 0, &new_ios) != 0)
				goto err_infd;
#endif /* !... */
#define __PRIVATE_WANT_err_infd
		}
	} else {
		libc_bzero(&old_ios, sizeof(struct termios));
		libc_bzero(&new_ios, sizeof(struct termios));
#ifdef __ECHO
		old_ios.c_lflag = __ECHO;
		new_ios.c_lflag = __ECHO;
#endif /* __ECHO */
	}
#endif /* (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) */

	/* Switch out signal handlers
	 * WARNING: The fact that we need to  do this has the (unintended)  side-effect
	 *          that this function as a whole is not thread-safe. Note however that
	 *          within the original  source material, this  function also  modifies
	 *          the process's signal handlers, meaning that the original  reference
	 *          for this function also isn't thread-safe! */
#if defined(__CRT_HAVE_sigaction) || defined(__CRT_HAVE___sigaction)
	{
		unsigned int i;
		struct sigaction newact;
		libc_bzero((void *)__NAMESPACE_LOCAL_SYM rpp_arrived, sizeof(__NAMESPACE_LOCAL_SYM rpp_arrived));
		libc_bzero(&newact, sizeof(newact));
		newact.sa_handler = &__NAMESPACE_LOCAL_SYM rpp_handler;
		for (i = 0; i < __COMPILER_LENOF(__NAMESPACE_LOCAL_SYM rpp_signals); ++i) {
			if unlikely(libc_sigaction(__NAMESPACE_LOCAL_SYM rpp_signals[i], &newact, &old_sact[i]) != 0) {
				while (i) {
					--i;
					(void)libc_sigaction(__NAMESPACE_LOCAL_SYM rpp_signals[i], &newact, &old_sact[i]);
				}
				goto err_infd_oldios;
#define __PRIVATE_WANT_err_infd_oldios
			}
		}
	}
#endif /* __CRT_HAVE_sigaction || __CRT_HAVE___sigaction */


	/* Write the given `prompt' (if given and possible to write) */
	(void)prompt;
#if defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)
	/* XXX: I don't really understand why the prompt is only printed
	 *      when using /dev/tty as output,  but that's how BSD  does
	 *      this, too... */
	if (prompt && *prompt && !(flags & __RPP_STDIN)) {
		if (libc_write(outfd, prompt, libc_strlen(prompt)) == -1)
			goto err_infd_oldsact_oldios;
	}
#endif /* __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write */

	/* Read the actual password from input. */
	{
		unsigned char *dst, *bufend;
		dst    = (unsigned char *)buf;
		bufend = (unsigned char *)buf + (bufsize / sizeof(char)) - 1;
		for (;;) {
			unsigned char ch;
			ssize_t error;
			error = libc_read(infd, &ch, sizeof(char));
			if (error < 1) {
				if (error >= 0)
					break;
				goto err_infd_oldsact_oldios;
			}
			if (ch == '\r' || ch == '\n')
				break; /* End-of-line... */
			if (dst < bufend) {
				/* Append character. */
				if (flags & __RPP_SEVENBIT)
					ch &= 0x7f;
				if (flags & __RPP_FORCELOWER)
					ch = (unsigned char)libc_tolower((char)ch);
				if (flags & __RPP_FORCEUPPER)
					ch = (unsigned char)libc_toupper((char)ch);
				*dst++ = ch;
			}
		}
		*dst = '\0'; /* Force NUL-termination. */
	}

	/* Write a trailing \n-character if echo was disabled. */
#if defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)
#if (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl))
	if (!(new_ios.c_lflag & __ECHO))
#else /* (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) */
	if (!(flags & __RPP_ECHO_ON))
#endif /* (!__CRT_HAVE_tcgetattr && !__CRT_HAVE___tcgetattr && ((!__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl) || !__TCGETA)) || (!__CRT_HAVE_tcsetattr && !__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl) */
	{
		if (libc_write(outfd, "\n", 1) == -1)
			goto err_infd_oldsact_oldios;
	}
#endif /* __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write */


	/* Restore terminal IOS configuration */
done_infd_oldsact_oldios:
#if (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl))
	if (libc_memcmp(&old_ios, &new_ios, sizeof(struct termios)) != 0) {
#if defined(__TCSAFLUSH) && defined(__TCSASOFT)
		(void)libc_tcsetattr(infd, __TCSAFLUSH | __TCSASOFT, &old_ios);
#elif defined(__TCSAFLUSH)
		(void)libc_tcsetattr(infd, __TCSAFLUSH, &old_ios);
#else /* ... */
		(void)libc_tcsetattr(infd, 0, &old_ios);
#endif /* !... */
	}
#endif /* (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) */

	/* Restore signal handlers. */
#if defined(__CRT_HAVE_sigaction) || defined(__CRT_HAVE___sigaction)
	{
		unsigned int i;
		for (i = 0; i < __COMPILER_LENOF(__NAMESPACE_LOCAL_SYM rpp_signals); ++i)
			(void)libc_sigaction(__NAMESPACE_LOCAL_SYM rpp_signals[i], &old_sact[i], NULL);
	}
#endif /* __CRT_HAVE_sigaction || __CRT_HAVE___sigaction */

	/* Close the input file handle if we've manually opened `/dev/tty' above. */
#ifdef __PRIVATE_WANT_err_infd
done_infd:
#endif /* __PRIVATE_WANT_err_infd */
#if defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)
	if (infd != __STDIN_FILENO)
		libc_close(infd);
#endif /* __CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close */

	/* Re-throw signals that arrived in the mean time. */
#if defined(__CRT_HAVE_sigaction) || defined(__CRT_HAVE___sigaction)
	{
		unsigned int i;
		for (i = 0; i < __COMPILER_LENOF(__NAMESPACE_LOCAL_SYM rpp_signals); ++i) {
			if (!__NAMESPACE_LOCAL_SYM rpp_arrived[i])
				continue;
#if (defined(__CRT_HAVE_kill) || defined(__CRT_HAVE___kill) || defined(__CRT_HAVE___libc_kill)) && (defined(__CRT_HAVE_getpid) || defined(__CRT_HAVE__getpid) || defined(__CRT_HAVE___getpid) || defined(__CRT_HAVE___libc_getpid))
			libc_kill(libc_getpid(), __NAMESPACE_LOCAL_SYM rpp_signals[i]);
#elif defined(__CRT_HAVE_raise) || (defined(__CRT_HAVE_pthread_kill) && (defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current)))
			libc_raise(__NAMESPACE_LOCAL_SYM rpp_signals[i]);
#endif /* ... */

			/* Handle signals for which we must start over when they're received. */
#if defined(__SIGTSTP) || defined(__SIGTTIN) || defined(__SIGTTOU)
			if (0
#ifdef __SIGTSTP
			    || __NAMESPACE_LOCAL_SYM rpp_signals[i] == __SIGTSTP
#endif /* __SIGTSTP */
#ifdef __SIGTTIN
			    || __NAMESPACE_LOCAL_SYM rpp_signals[i] == __SIGTTIN
#endif /* __SIGTTIN */
#ifdef __SIGTTOU
			    || __NAMESPACE_LOCAL_SYM rpp_signals[i] == __SIGTTOU
#endif /* __SIGTTOU */
			    )
				must_restart = true;
#endif /* __SIGTSTP || __SIGTTIN || __SIGTTOU */

		}
	}
#endif /* __CRT_HAVE_sigaction || __CRT_HAVE___sigaction */

	/* Check if we have to start over (due to having received certain signals) */
#if defined(__CRT_HAVE_sigaction) || defined(__CRT_HAVE___sigaction)
	if (must_restart && buf != NULL)
		goto again;
#endif /* __CRT_HAVE_sigaction || __CRT_HAVE___sigaction */

	/* Done! */
	return buf;

err_infd_oldsact_oldios:
	buf = NULL;
	goto done_infd_oldsact_oldios;

#ifdef __PRIVATE_WANT_err_infd_oldios
#undef __PRIVATE_WANT_err_infd_oldios
err_infd_oldios:
	/* Restore terminal IOS configuration */
#if (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl))
	if (libc_memcmp(&old_ios, &new_ios, sizeof(struct termios)) != 0) {
#if defined(__TCSAFLUSH) && defined(__TCSASOFT)
		(void)libc_tcsetattr(infd, __TCSAFLUSH | __TCSASOFT, &old_ios);
#elif defined(__TCSAFLUSH)
		(void)libc_tcsetattr(infd, __TCSAFLUSH, &old_ios);
#else /* ... */
		(void)libc_tcsetattr(infd, 0, &old_ios);
#endif /* !... */
	}
#endif /* (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) */
	buf = NULL;
	goto done_infd;
#endif /* __PRIVATE_WANT_err_infd_oldios */

#ifdef __PRIVATE_WANT_err_infd
#undef __PRIVATE_WANT_err_infd
err_infd:
	buf = NULL;
	goto done_infd;
#endif /* __PRIVATE_WANT_err_infd */

err:
	return NULL;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(readpassphrase, libc_readpassphrase);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_READPASSPHRASE_C */
