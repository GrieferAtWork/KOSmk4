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
%(c_prefix){
/* (#) Portability: DragonFly BSD (/include/readpassphrase.h) */
/* (#) Portability: FreeBSD       (/include/readpassphrase.h) */
/* (#) Portability: OpenBSD       (/include/readpassphrase.h) */
/* (#) Portability: libbsd        (/include/bsd/readpassphrase.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.bsd")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <asm/crt/readpassphrase.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%{


/* Flags for use with `readpassphrase(3)::flags' */
#if !defined(RPP_ECHO_OFF) && defined(__RPP_ECHO_OFF)
#define RPP_ECHO_OFF    __RPP_ECHO_OFF    /* Disable echo. */
#endif /* !RPP_ECHO_OFF && __RPP_ECHO_OFF */
#if !defined(RPP_ECHO_ON) && defined(__RPP_ECHO_ON)
#define RPP_ECHO_ON     __RPP_ECHO_ON     /* Don't disable echo (but leave it on). */
#endif /* !RPP_ECHO_ON && __RPP_ECHO_ON */
#if !defined(RPP_REQUIRE_TTY) && defined(__RPP_REQUIRE_TTY)
#define RPP_REQUIRE_TTY __RPP_REQUIRE_TTY /* Error out if `!isatty()' */
#endif /* !RPP_REQUIRE_TTY && __RPP_REQUIRE_TTY */
#if !defined(RPP_FORCELOWER) && defined(__RPP_FORCELOWER)
#define RPP_FORCELOWER  __RPP_FORCELOWER  /* Force all input to be lower-case. */
#endif /* !RPP_FORCELOWER && __RPP_FORCELOWER */
#if !defined(RPP_FORCEUPPER) && defined(__RPP_FORCEUPPER)
#define RPP_FORCEUPPER  __RPP_FORCEUPPER  /* Force all input to be upper-case. */
#endif /* !RPP_FORCEUPPER && __RPP_FORCEUPPER */
#if !defined(RPP_SEVENBIT) && defined(__RPP_SEVENBIT)
#define RPP_SEVENBIT    __RPP_SEVENBIT    /* Mask input with `0x7f' */
#endif /* !RPP_SEVENBIT && __RPP_SEVENBIT */
#if !defined(RPP_STDIN) && defined(__RPP_STDIN)
#define RPP_STDIN       __RPP_STDIN       /* Use `STDIN_FILENO' as input and `STDERR_FILENO' as output, rather than `/dev/tty' */
#endif /* !RPP_STDIN && __RPP_STDIN */


#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

}

@@>> readpassphrase(3)
@@@param: flags: Set of `RPP_*' (from `<readpassphrase.h>')
@@@return: buf:  Success
@@@return: NULL: Error (s.a. `errno')
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[requires_include("<asm/os/stdio.h>")]]
[[requires(defined(__STDIN_FILENO) && $has_function(read))]]
[[impl_include("<bits/types.h>", "<asm/os/stdio.h>", "<asm/os/oflags.h>")]]
[[impl_include("<libc/errno.h>", "<paths.h>", "<asm/crt/readpassphrase.h>")]]
[[impl_include("<asm/os/termios.h>", "<bits/os/termios.h>")]]
[[impl_include("<asm/os/signal.h>", "<bits/os/sigaction.h>")]]
[[impl_prefix(
@@pp_ifndef __LOCAL_READPASSPHRASE_HELPERS_DEFINED@@
@@push_namespace(local)@@
#define __LOCAL_READPASSPHRASE_HELPERS_DEFINED
@@pp_if $has_function(sigaction)@@
static signo_t const rpp_signals[] = {
@@pp_ifdef __SIGTTOU@@
	__SIGTTOU, /* This one _must_ be first! */
@@pp_endif@@
@@pp_ifdef __SIGALRM@@
	__SIGALRM,
@@pp_endif@@
@@pp_ifdef __SIGHUP@@
	__SIGHUP,
@@pp_endif@@
@@pp_ifdef __SIGINT@@
	__SIGINT,
@@pp_endif@@
@@pp_ifdef __SIGPIPE@@
	__SIGPIPE,
@@pp_endif@@
@@pp_ifdef __SIGQUIT@@
	__SIGQUIT,
@@pp_endif@@
@@pp_ifdef __SIGTERM@@
	__SIGTERM,
@@pp_endif@@
@@pp_ifdef __SIGTSTP@@
	__SIGTSTP,
@@pp_endif@@
@@pp_ifdef __SIGTTIN@@
	__SIGTTIN,
@@pp_endif@@
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
@@pp_endif@@
@@pop_namespace@@
@@pp_endif@@
)]]
char *readpassphrase([[in_opt]] char const *prompt,
                     [[out(? <= bufsize)]] char *buf, $size_t bufsize,
                     __STDC_INT_AS_UINT_T flags) {
@@pp_if $has_function(sigaction)@@
	bool must_restart;
@@pp_endif@@
	fd_t infd, outfd;
@@pp_if $has_function(tcgetattr) && $has_function(tcsetattr)@@
	struct termios old_ios, new_ios;
@@pp_endif@@
@@pp_if $has_function(sigaction)@@
	struct @sigaction@ old_sact[__COMPILER_LENOF(__NAMESPACE_LOCAL_SYM rpp_signals)];
@@pp_endif@@

	/* Validate input arguments. */
	if unlikely(buf == NULL || bufsize < sizeof(char)) {
@@pp_ifdef EINVAL@@
		(void)libc_seterrno(EINVAL);
@@pp_else@@
		(void)libc_seterrno(1);
@@pp_endif@@
		goto err;
	}

@@pp_if $has_function(sigaction)@@
again:
	must_restart = false;
@@pp_endif@@
	infd  = __STDIN_FILENO;
	outfd = __STDIN_FILENO;

	/* Open the relevant output stream. */
	if (!(flags & __RPP_STDIN)) {
@@pp_if $has_function(open)@@
@@pp_ifdef _PATH_TTY@@
@@pp_ifdef O_RDWR@@
		infd = open(_PATH_TTY, O_RDWR | __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK);
@@pp_else@@
		infd = open(_PATH_TTY, __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK);
@@pp_endif@@
@@pp_else@@
@@pp_ifdef O_RDWR@@
		infd = open("/dev/tty", O_RDWR | __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK);
@@pp_else@@
		infd = open("/dev/tty", __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK);
@@pp_endif@@
@@pp_endif@@
		if unlikely(infd == -1) {
@@pp_ifdef ENOTTY@@
			if (flags & __RPP_REQUIRE_TTY)
				(void)libc_seterrno(ENOTTY);
@@pp_endif@@
			goto err;
		}
		outfd = infd;
@@pp_else@@
@@pp_if defined(ENOTTY) && defined(ENOENT)@@
		(void)libc_seterrno(flags & __RPP_REQUIRE_TTY ? ENOTTY : ENOENT);
@@pp_elif defined(ENOENT)@@
		(void)libc_seterrno(ENOENT);
@@pp_else@@
		(void)libc_seterrno(1);
@@pp_endif@@
		goto err;
@@pp_endif@@
	}

	/* Update terminal IOS mode to our liking. */
@@pp_if $has_function(tcgetattr) && $has_function(tcsetattr)@@
	if (tcgetattr(infd, &old_ios) != 0) {
		if (flags & RPP_REQUIRE_TTY) {
@@pp_ifdef ENOTTY@@
			(void)libc_seterrno(ENOTTY);
@@pp_endif@@
			goto err_infd;
#define __PRIVATE_WANT_err_infd
		}
		memcpy(&new_ios, &old_ios, sizeof(struct termios));
		if (!(flags & __RPP_ECHO_ON)) {
@@pp_if defined(__ECHO) && defined(__ECHONL)@@
			new_ios.@c_lflag@ &= ~(__ECHO | __ECHONL);
@@pp_elif defined(__ECHO)@@
			new_ios.@c_lflag@ &= ~(__ECHO);
@@pp_elif defined(__ECHONL)@@
			new_ios.@c_lflag@ &= ~(__ECHONL);
@@pp_endif@@
		}
@@pp_ifdef __VSTATUS@@
		if (term.c_cc[__VSTATUS] != __VDISABLE)
			term.c_cc[__VSTATUS] = __VDISABLE;
@@pp_endif@@
		if (bcmp(&old_ios, &new_ios, sizeof(struct termios)) != 0) {
@@pp_if defined(__TCSAFLUSH) && defined(__TCSASOFT)@@
			if (tcsetattr(infd, __TCSAFLUSH | __TCSASOFT, &new_ios) != 0)
				goto err_infd;
@@pp_elif defined(__TCSAFLUSH)@@
			if (tcsetattr(infd, __TCSAFLUSH, &new_ios) != 0)
				goto err_infd;
@@pp_else@@
			if (tcsetattr(infd, 0, &new_ios) != 0)
				goto err_infd;
@@pp_endif@@
#define __PRIVATE_WANT_err_infd
		}
	} else {
		bzero(&old_ios, sizeof(struct termios));
		bzero(&new_ios, sizeof(struct termios));
@@pp_ifdef __ECHO@@
		old_ios.@c_lflag@ = __ECHO;
		new_ios.@c_lflag@ = __ECHO;
@@pp_endif@@
	}
@@pp_endif@@

	/* Switch out signal handlers
	 * WARNING: The fact that we need to  do this has the (unintended)  side-effect
	 *          that this function as a whole is not thread-safe. Note however that
	 *          within the original  source material, this  function also  modifies
	 *          the process's signal handlers, meaning that the original  reference
	 *          for this function also isn't thread-safe! */
@@pp_if $has_function(sigaction)@@
	{
		unsigned int i;
		struct @sigaction@ newact;
		bzero((void *)__NAMESPACE_LOCAL_SYM rpp_arrived, sizeof(__NAMESPACE_LOCAL_SYM rpp_arrived));
		bzero(&newact, sizeof(newact));
		newact.@sa_handler@ = &__NAMESPACE_LOCAL_SYM rpp_handler;
		for (i = 0; i < __COMPILER_LENOF(__NAMESPACE_LOCAL_SYM rpp_signals); ++i) {
			if unlikely(sigaction(__NAMESPACE_LOCAL_SYM rpp_signals[i], &newact, &old_sact[i]) != 0) {
				while (i) {
					--i;
					(void)sigaction(__NAMESPACE_LOCAL_SYM rpp_signals[i], &newact, &old_sact[i]);
				}
				goto err_infd_oldios;
#define __PRIVATE_WANT_err_infd_oldios
			}
		}
	}
@@pp_endif@@


	/* Write the given `prompt' (if given and possible to write) */
	(void)prompt;
@@pp_if $has_function(write)@@
	/* XXX: I don't really understand why the prompt is only printed
	 *      when using /dev/tty as output,  but that's how BSD  does
	 *      this, too... */
	if (prompt && *prompt && !(flags & __RPP_STDIN)) {
		if (write(outfd, prompt, strlen(prompt)) == -1)
			goto err_infd_oldsact_oldios;
	}
@@pp_endif@@

	/* Read the actual password from input. */
	{
		unsigned char *dst, *bufend;
		dst    = (unsigned char *)buf;
		bufend = (unsigned char *)buf + (bufsize / sizeof(char)) - 1;
		for (;;) {
			unsigned char ch;
			ssize_t error;
			error = read(infd, &ch, sizeof(char));
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
					ch = (unsigned char)tolower((char)ch);
				if (flags & __RPP_FORCEUPPER)
					ch = (unsigned char)toupper((char)ch);
				*dst++ = ch;
			}
		}
		*dst = '\0'; /* Force NUL-termination. */
	}

	/* Write a trailing \n-character if echo was disabled. */
@@pp_if $has_function(write)@@
@@pp_if $has_function(tcgetattr) && $has_function(tcsetattr)@@
	if (!(new_ios.@c_lflag@ & __ECHO))
@@pp_else@@
	if (!(flags & __RPP_ECHO_ON))
@@pp_endif@@
	{
		if (write(outfd, "\n", 1) == -1)
			goto err_infd_oldsact_oldios;
	}
@@pp_endif@@


	/* Restore terminal IOS configuration */
done_infd_oldsact_oldios:
@@pp_if $has_function(tcgetattr) && $has_function(tcsetattr)@@
	if (bcmp(&old_ios, &new_ios, sizeof(struct termios)) != 0) {
@@pp_if defined(__TCSAFLUSH) && defined(__TCSASOFT)@@
		(void)tcsetattr(infd, __TCSAFLUSH | __TCSASOFT, &old_ios);
@@pp_elif defined(__TCSAFLUSH)@@
		(void)tcsetattr(infd, __TCSAFLUSH, &old_ios);
@@pp_else@@
		(void)tcsetattr(infd, 0, &old_ios);
@@pp_endif@@
	}
@@pp_endif@@

	/* Restore signal handlers. */
@@pp_if $has_function(sigaction)@@
	{
		unsigned int i;
		for (i = 0; i < __COMPILER_LENOF(__NAMESPACE_LOCAL_SYM rpp_signals); ++i)
			(void)sigaction(__NAMESPACE_LOCAL_SYM rpp_signals[i], &old_sact[i], NULL);
	}
@@pp_endif@@

	/* Close the input file handle if we've manually opened `/dev/tty' above. */
#ifdef __PRIVATE_WANT_err_infd
done_infd:
#endif /* __PRIVATE_WANT_err_infd */
@@pp_if $has_function(close)@@
	if (infd != __STDIN_FILENO)
		close(infd);
@@pp_endif@@

	/* Re-throw signals that arrived in the mean time. */
@@pp_if $has_function(sigaction)@@
	{
		unsigned int i;
		for (i = 0; i < __COMPILER_LENOF(__NAMESPACE_LOCAL_SYM rpp_signals); ++i) {
			if (!__NAMESPACE_LOCAL_SYM rpp_arrived[i])
				continue;
@@pp_if $has_function(kill) && $has_function(getpid)@@
			kill(getpid(), __NAMESPACE_LOCAL_SYM rpp_signals[i]);
@@pp_elif $has_function(raise)@@
			raise(__NAMESPACE_LOCAL_SYM rpp_signals[i]);
@@pp_endif@@

			/* Handle signals for which we must start over when they're received. */
@@pp_if defined(__SIGTSTP) || defined(__SIGTTIN) || defined(__SIGTTOU)@@
			if (0
@@pp_ifdef __SIGTSTP@@
			    || __NAMESPACE_LOCAL_SYM rpp_signals[i] == __SIGTSTP
@@pp_endif@@
@@pp_ifdef __SIGTTIN@@
			    || __NAMESPACE_LOCAL_SYM rpp_signals[i] == __SIGTTIN
@@pp_endif@@
@@pp_ifdef __SIGTTOU@@
			    || __NAMESPACE_LOCAL_SYM rpp_signals[i] == __SIGTTOU
@@pp_endif@@
			    )
				must_restart = true;
@@pp_endif@@

		}
	}
@@pp_endif@@

	/* Check if we have to start over (due to having received certain signals) */
@@pp_if $has_function(sigaction)@@
	if (must_restart && buf != NULL)
		goto again;
@@pp_endif@@

	/* Done! */
	return buf;

err_infd_oldsact_oldios:
	buf = NULL;
	goto done_infd_oldsact_oldios;

#ifdef __PRIVATE_WANT_err_infd_oldios
#undef __PRIVATE_WANT_err_infd_oldios
err_infd_oldios:
	/* Restore terminal IOS configuration */
@@pp_if $has_function(tcgetattr) && $has_function(tcsetattr)@@
	if (bcmp(&old_ios, &new_ios, sizeof(struct termios)) != 0) {
@@pp_if defined(__TCSAFLUSH) && defined(__TCSASOFT)@@
		(void)tcsetattr(infd, __TCSAFLUSH | __TCSASOFT, &old_ios);
@@pp_elif defined(__TCSAFLUSH)@@
		(void)tcsetattr(infd, __TCSAFLUSH, &old_ios);
@@pp_else@@
		(void)tcsetattr(infd, 0, &old_ios);
@@pp_endif@@
	}
@@pp_endif@@
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



%{

__SYSDECL_END
#endif /* __CC__ */

}
