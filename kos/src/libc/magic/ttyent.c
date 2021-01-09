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
%(c_prefix){
/* (#) Portability: FreeBSD       (/include/ttyent.h) */
/* (#) Portability: GNU C Library (/misc/ttyent.h) */
/* (#) Portability: NetBSD        (/include/ttyent.h) */
/* (#) Portability: uClibc        (/include/ttyent.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.database.utmpx")]

%{
#include <features.h>
#include <asm/crt/ttyent.h>
#include <bits/crt/db/ttyent.h>

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

__SYSDECL_BEGIN

#ifdef __CC__

}

[[cp_kos, decl_include("<bits/crt/db/ttyent.h>")]]
struct ttyent *getttyent();

[[cp_kos, decl_include("<bits/crt/db/ttyent.h>")]]
struct ttyent *getttynam([[nonnull]] char const *tty);

[[cp_kos]]
int setttyent();

int endttyent();


%{
#endif /* __CC__ */

__SYSDECL_END

}