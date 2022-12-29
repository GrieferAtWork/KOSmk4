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
/* (>) Standard: POSIX.2 (Issue 4, IEEE Std 1003.2-1992) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/utmpx.h) */
/* (#) Portability: DragonFly BSD (/include/utmpx.h) */
/* (#) Portability: FreeBSD       (/include/utmpx.h) */
/* (#) Portability: GNU C Library (/sysdeps/[...]/utmpx.h) */
/* (#) Portability: GNU Hurd      (/usr/include/utmpx.h) */
/* (#) Portability: NetBSD        (/include/utmpx.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/utmpx.h) */
/* (#) Portability: diet libc     (/include/utmpx.h) */
/* (#) Portability: libc6         (/include/utmpx.h) */
/* (#) Portability: musl libc     (/include/utmpx.h) */
/* (#) Portability: uClibc        (/include/utmpx.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.database.utmpx")]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <bits/crt/db/utmpx.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#include <sys/time.h>


#ifdef __USE_GNU
/* Compatibility names for the strings of the canonical file names.  */
#if !defined(UTMPX_FILE) && defined(_PATH_UTMPX)
#define UTMPX_FILE     _PATH_UTMPX
#endif /* !UTMPX_FILE && _PATH_UTMPX */
#if !defined(UTMPX_FILENAME) && defined(_PATH_UTMPX)
#define UTMPX_FILENAME _PATH_UTMPX
#endif /* !UTMPX_FILENAME && _PATH_UTMPX */
#if !defined(WTMPX_FILE) && defined(_PATH_WTMPX)
#define WTMPX_FILE     _PATH_WTMPX
#endif /* !WTMPX_FILE && _PATH_WTMPX */
#if !defined(WTMPX_FILENAME) && defined(_PATH_WTMPX)
#define WTMPX_FILENAME _PATH_WTMPX
#endif /* !WTMPX_FILENAME && _PATH_WTMPX */
#endif /* __USE_GNU */

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __USE_GNU
struct utmp;
#endif /* __USE_GNU */

#ifndef __pid_t_defined
#define __pid_t_defined
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */

}

@@>> setutxent(3)
[[cp]]
void setutxent();

@@>> endutxent(3)
[[cp_nokos]]
void endutxent();

@@>> getutxent(3)
[[cp, decl_include("<bits/crt/db/utmpx.h>")]]
struct utmpx *getutxent();

@@>> getutxid(3)
[[cp, decl_include("<bits/crt/db/utmpx.h>")]]
struct utmpx *getutxid(struct utmpx const *id);

@@>> getutxline(3)
[[cp, decl_include("<bits/crt/db/utmpx.h>")]]
struct utmpx *getutxline(struct utmpx const *line);

@@>> pututxline(3)
[[cp, decl_include("<bits/crt/db/utmpx.h>")]]
struct utmpx *pututxline(struct utmpx const *utmpx);

%
%#ifdef __USE_GNU
@@>> utmpxname(3)
[[cp]]
int utmpxname(char const *file);

@@>> updwtmpx(3)
[[cp, decl_include("<bits/crt/db/utmpx.h>")]]
void updwtmpx(char const *wtmpx_file, struct utmpx const *utmpx);

@@>> getutmp(3)
[[cp, decl_include("<bits/crt/db/utmpx.h>", "<bits/crt/db/utmp.h>")]]
void getutmp(struct utmpx const *utmpx, struct utmp *utmp);

@@>> getutmpx(3)
[[cp, decl_include("<bits/crt/db/utmpx.h>")]]
void getutmpx(struct utmp const *utmp, struct utmpx *utmpx);
%#endif /* __USE_GNU */


%{

__SYSDECL_END
#endif /* __CC__ */


}
