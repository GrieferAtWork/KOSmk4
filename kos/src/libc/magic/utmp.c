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
%(c_prefix){
/* (#) Portability: Cygwin        (/newlib/libc/include/utmp.h) */
/* (#) Portability: GNU C Library (/login/utmp.h) */
/* (#) Portability: NetBSD        (/include/utmp.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/utmp.h) */
/* (#) Portability: OpenBSD       (/include/utmp.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/utmp.h) */
/* (#) Portability: diet libc     (/include/utmp.h) */
/* (#) Portability: libc4/5       (/include/utmp.h) */
/* (#) Portability: libc6         (/include/utmp.h) */
/* (#) Portability: musl libc     (/include/utmp.h) */
/* (#) Portability: uClibc        (/include/utmp.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.database.utmp")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/crt/db/utmp.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#include <paths.h>

#ifdef __USE_GLIBC
#include <sys/time.h>
#include <sys/types.h>
#endif /* __USE_GLIBC */

/* Compatibility names for the strings of the canonical file names. */
#define UTMP_FILE     _PATH_UTMP
#define UTMP_FILENAME _PATH_UTMP
#define WTMP_FILE     _PATH_WTMP
#define WTMP_FILENAME _PATH_WTMP

#ifdef __CC__
__SYSDECL_BEGIN

}


@@>> login_tty(3)
@@Set the given `fd' as the controlling terminal, stdin,
@@stdout,   and  stderr.  Afterwards,  `fd'  is  closed.
@@@return: 0 : Success
@@@return: * : Error
[[guard, cp_kos, section(".text.crt{|.dos}.io.tty")]]
[[impl_include("<asm/os/tty.h>")]]
[[impl_include("<asm/os/stdio.h>")]]
[[requires_include("<asm/os/tty.h>")]]
[[requires(defined(@__TIOCSCTTY@) && $has_function(ioctl) &&
           $has_function(setsid) && $has_function(dup2) &&
           $has_function(close))]]
int login_tty($fd_t fd) {
	if unlikely(setsid() < 0)
		goto err;
	if unlikely(ioctl(fd, @__TIOCSCTTY@, 1) < 0)
		goto err;
@@pp_if STDIN_FILENO <= 2 && STDOUT_FILENO <= 2 && STDERR_FILENO <= 2@@
	{
		fd_t i;
		for (i = 0; i <= 2; ++i) {
			if likely(fd != i) {
				if unlikely(dup2(fd, i))
					goto err;
			}
		}
	}
	if likely(fd >= 3)
		close(fd);
@@pp_else@@
	if (likely(fd != STDIN_FILENO) && unlikely(dup2(fd, STDIN_FILENO)))
		goto err;
	if (likely(fd != STDOUT_FILENO) && unlikely(dup2(fd, STDOUT_FILENO)))
		goto err;
	if (likely(fd != STDERR_FILENO) && unlikely(dup2(fd, STDERR_FILENO)))
		goto err;
	if likely(fd != STDIN_FILENO && fd != STDOUT_FILENO && fd != STDERR_FILENO)
		close(fd);
@@pp_endif@@
	return 0;
err:
	return -1;
}


@@>> login(3)
[[guard, cp_kos, decl_include("<bits/crt/db/utmp.h>")]]
void login([[nonnull]] struct utmp const *entry);

@@>> logout(3)
[[guard, cp_kos]]
int logout([[nonnull]] char const *ut_line);

@@>> logwtmp(3)
[[guard, cp_kos]]
void logwtmp([[nonnull]] char const *ut_line,
             [[nonnull]] char const *ut_name,
             [[nonnull]] char const *ut_host);

@@>> updwtmp(3)
[[cp_kos, decl_include("<bits/crt/db/utmp.h>")]]
void updwtmp([[nonnull]] char const *wtmp_file,
             [[nonnull]] struct utmp const *utmp);

@@>> utmpname(3)
[[cp_kos]]
int utmpname([[nonnull]] char const *file);

@@>> getutent(3), getutent_r(3)
[[cp_kos, decl_include("<bits/crt/db/utmp.h>")]]
struct utmp *getutent();

@@>> setutent(3)
[[cp_kos]]
void setutent();

@@>> endutent(3)
void endutent();

@@>> getutid(3), getutid_r(3)
[[cp_kos, decl_include("<bits/crt/db/utmp.h>")]]
struct utmp *getutid([[nonnull]] struct utmp const *id);

@@>> getutline(3), getutline_r(3)
[[cp_kos, decl_include("<bits/crt/db/utmp.h>")]]
struct utmp *getutline([[nonnull]] struct utmp const *line);

@@>> pututline(3)
[[cp_kos, decl_include("<bits/crt/db/utmp.h>")]]
struct utmp *pututline([[nonnull]] struct utmp const *utmp_ptr);

%
%#ifdef __USE_MISC
[[cp_kos, doc_alias("getutent"), decl_include("<bits/crt/db/utmp.h>")]]
int getutent_r([[nonnull]] struct utmp *buffer,
               [[nonnull]] struct utmp **result);

[[cp_kos, doc_alias("getutid"), decl_include("<bits/crt/db/utmp.h>")]]
int getutid_r([[nonnull]] struct utmp const *id,
              [[nonnull]] struct utmp *buffer,
              [[nonnull]] struct utmp **result);

[[cp_kos, doc_alias("getutline"), decl_include("<bits/crt/db/utmp.h>")]]
int getutline_r([[nonnull]] struct utmp const *line,
                [[nonnull]] struct utmp *buffer,
                [[nonnull]] struct utmp **result);
%#endif /* __USE_MISC */


%{

__SYSDECL_END
#endif /* __CC__ */

}
