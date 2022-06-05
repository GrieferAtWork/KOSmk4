/* HASH CRC-32:0xe86a07f2 */
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
#include "string.h"
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
INTERN ATTR_SECTION(".text.crt.bsd") ATTR_IN_OPT(1) ATTR_OUTS(2, 3) char *
NOTHROW_NCX(LIBCCALL libc_readpassphrase)(char const *prompt,
                                          char *buf,
                                          size_t bufsize,
                                          __STDC_INT_AS_UINT_T flags) {

	bool must_restart;

	fd_t infd, outfd;

	struct termios old_ios, new_ios;


	struct sigaction old_sact[__COMPILER_LENOF(__NAMESPACE_LOCAL_SYM rpp_signals)];


	/* Validate input arguments. */
	if unlikely(buf == NULL || bufsize < sizeof(char)) {

		(void)libc_seterrno(EINVAL);



		goto err;
	}


again:
	must_restart = false;

	infd  = __STDIN_FILENO;
	outfd = __STDIN_FILENO;

	/* Open the relevant output stream. */
	if (!(flags & __RPP_STDIN)) {

#ifdef _PATH_TTY

		infd = libc_open(_PATH_TTY, O_RDWR | __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK);



#else /* _PATH_TTY */

		infd = libc_open("/dev/tty", O_RDWR | __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK);



#endif /* !_PATH_TTY */
		if unlikely(infd == -1) {

			if (flags & __RPP_REQUIRE_TTY)
				(void)libc_seterrno(ENOTTY);

			goto err;
		}
		outfd = infd;










	}

	/* Update terminal IOS mode to our liking. */

	if (libc_tcgetattr(infd, &old_ios) != 0) {
		if (flags & RPP_REQUIRE_TTY) {

			(void)libc_seterrno(ENOTTY);

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
#ifdef __TCSASOFT
			if (libc_tcsetattr(infd, __TCSAFLUSH | __TCSASOFT, &new_ios) != 0)
				goto err_infd;
#else /* __TCSASOFT */
			if (libc_tcsetattr(infd, __TCSAFLUSH, &new_ios) != 0)
				goto err_infd;



#endif /* !__TCSASOFT */
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


	/* Switch out signal handlers
	 * WARNING: The fact that we need to  do this has the (unintended)  side-effect
	 *          that this function as a whole is not thread-safe. Note however that
	 *          within the original  source material, this  function also  modifies
	 *          the process's signal handlers, meaning that the original  reference
	 *          for this function also isn't thread-safe! */

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



	/* Write the given `prompt' (if given and possible to write) */
	(void)prompt;

	/* XXX: I don't really understand why the prompt is only printed
	 *      when using /dev/tty as output,  but that's how BSD  does
	 *      this, too... */
	if (prompt && *prompt && !(flags & __RPP_STDIN)) {
		if (libc_write(outfd, prompt, libc_strlen(prompt)) == -1)
			goto err_infd_oldsact_oldios;
	}


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


	if (!(new_ios.c_lflag & __ECHO))



	{
		if (libc_write(outfd, "\n", 1) == -1)
			goto err_infd_oldsact_oldios;
	}



	/* Restore terminal IOS configuration */
done_infd_oldsact_oldios:

	if (libc_memcmp(&old_ios, &new_ios, sizeof(struct termios)) != 0) {
#ifdef __TCSASOFT
		(void)libc_tcsetattr(infd, __TCSAFLUSH | __TCSASOFT, &old_ios);
#else /* __TCSASOFT */
		(void)libc_tcsetattr(infd, __TCSAFLUSH, &old_ios);


#endif /* !__TCSASOFT */
	}


	/* Restore signal handlers. */

	{
		unsigned int i;
		for (i = 0; i < __COMPILER_LENOF(__NAMESPACE_LOCAL_SYM rpp_signals); ++i)
			(void)libc_sigaction(__NAMESPACE_LOCAL_SYM rpp_signals[i], &old_sact[i], NULL);
	}


	/* Close the input file handle if we've manually opened `/dev/tty' above. */
#ifdef __PRIVATE_WANT_err_infd
done_infd:
#endif /* __PRIVATE_WANT_err_infd */

	if (infd != __STDIN_FILENO)
		libc_close(infd);


	/* Re-throw signals that arrived in the mean time. */

	{
		unsigned int i;
		for (i = 0; i < __COMPILER_LENOF(__NAMESPACE_LOCAL_SYM rpp_signals); ++i) {
			if (!__NAMESPACE_LOCAL_SYM rpp_arrived[i])
				continue;

			libc_kill(libc_getpid(), __NAMESPACE_LOCAL_SYM rpp_signals[i]);




			/* Handle signals for which we must start over when they're received. */

			if (0

			    || __NAMESPACE_LOCAL_SYM rpp_signals[i] == __SIGTSTP


			    || __NAMESPACE_LOCAL_SYM rpp_signals[i] == __SIGTTIN


			    || __NAMESPACE_LOCAL_SYM rpp_signals[i] == __SIGTTOU

			    )
				must_restart = true;


		}
	}


	/* Check if we have to start over (due to having received certain signals) */

	if (must_restart && buf != NULL)
		goto again;


	/* Done! */
	return buf;

err_infd_oldsact_oldios:
	buf = NULL;
	goto done_infd_oldsact_oldios;

#ifdef __PRIVATE_WANT_err_infd_oldios
#undef __PRIVATE_WANT_err_infd_oldios
err_infd_oldios:
	/* Restore terminal IOS configuration */

	if (libc_memcmp(&old_ios, &new_ios, sizeof(struct termios)) != 0) {
#ifdef __TCSASOFT
		(void)libc_tcsetattr(infd, __TCSAFLUSH | __TCSASOFT, &old_ios);
#else /* __TCSASOFT */
		(void)libc_tcsetattr(infd, __TCSAFLUSH, &old_ios);


#endif /* !__TCSASOFT */
	}

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
