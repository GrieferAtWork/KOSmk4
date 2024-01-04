/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (#) Portability: DragonFly BSD (/include/ttyent.h) */
/* (#) Portability: FreeBSD       (/include/ttyent.h) */
/* (#) Portability: GNU C Library (/misc/ttyent.h) */
/* (#) Portability: GNU Hurd      (/usr/include/ttyent.h) */
/* (#) Portability: NetBSD        (/include/ttyent.h) */
/* (#) Portability: OpenBSD       (/include/ttyent.h) */
/* (#) Portability: OpenSolaris   (/usr/src/lib/libbc/inc/include/ttyent.h) */
/* (#) Portability: libc6         (/include/ttyent.h) */
/* (#) Portability: uClibc        (/include/ttyent.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.database.tty")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <asm/crt/ttyent.h>
)]%[insert:prefix(
#include <bits/crt/db/ttyent.h>
)]%{

#define _PATH_TTYS   "/etc/ttys"
#define _TTYS_OFF    "off"
#define _TTYS_ON     "on"
#define _TTYS_SECURE "secure"
#define _TTYS_WINDOW "window"

#ifdef __TTY_ON
#define TTY_ON __TTY_ON /* enable logins (start ty_getty program) */
#endif /* __TTY_ON */
#ifdef __TTY_SECURE
#define TTY_SECURE __TTY_SECURE /* allow uid of 0 to login */
#endif /* __TTY_SECURE */

#ifdef __CC__
__SYSDECL_BEGIN

}

@@>> getttyent(3)
[[cp_kos, decl_include("<bits/crt/db/ttyent.h>")]]
struct ttyent *getttyent();

@@>> getttynam(3)
[[cp_kos, decl_include("<bits/crt/db/ttyent.h>")]]
[[requires_function(setttyent, getttyent)]]
[[impl_include("<bits/crt/db/ttyent.h>")]]
struct ttyent *getttynam([[in]] char const *tty) {
	struct ttyent *result;
	if (!setttyent())
		return NULL;
	while ((result = getttyent()) != NULL) {
		if (strcmp(result->@ty_name@, tty) == 0)
			break;
	}
	return result;
}

@@>> setttyent(3)
@@@return: 1 : Success
@@@return: 0 : Error
[[cp_kos]]
int setttyent();

@@>> endttyent(3)
@@@return: 1 : Success
@@@return: 0 : Error
int endttyent();

%{

__SYSDECL_END
#endif /* __CC__ */

}
