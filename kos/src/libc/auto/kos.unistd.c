/* HASH CRC-32:0x756b8d17 */
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
#ifndef GUARD_LIBC_AUTO_KOS_UNISTD_C
#define GUARD_LIBC_AUTO_KOS_UNISTD_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/kos.unistd.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <parts/redirect-exec.h>
/* >> execl(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
INTERN ATTR_SECTION(".text.crt.except.fs.exec.exec") ATTR_NORETURN ATTR_SENTINEL ATTR_IN(1) ATTR_IN_OPT(2) void
(VLIBCCALL libc_Execl)(char const *__restrict path,
                       char const *args,
                       ...) THROWS(...) {
	__REDIRECT_XEXECL(char, libc_Execv, path, args)
}
#include <parts/redirect-exec.h>
/* >> execle(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
INTERN ATTR_SECTION(".text.crt.except.fs.exec.exec") ATTR_NORETURN ATTR_IN(1) ATTR_IN_OPT(2) ATTR_SENTINEL_O(1) void
(VLIBCCALL libc_Execle)(char const *__restrict path,
                        char const *args,
                        ...) THROWS(...) {
	__REDIRECT_XEXECLE(char, libc_Execve, path, args)
}
#include <parts/redirect-exec.h>
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
INTERN ATTR_SECTION(".text.crt.except.fs.exec.exec") ATTR_NORETURN ATTR_SENTINEL ATTR_IN(1) ATTR_IN_OPT(2) void
(VLIBCCALL libc_Execpl)(char const *__restrict file,
                        char const *args,
                        ...) THROWS(...) {
	__REDIRECT_XEXECL(char, libc_Execvp, file, args)
}
#include <parts/redirect-exec.h>
/* >> execle(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
INTERN ATTR_SECTION(".text.crt.except.fs.exec.exec") ATTR_NORETURN ATTR_IN(1) ATTR_IN_OPT(2) ATTR_SENTINEL_O(1) void
(VLIBCCALL libc_Execlpe)(char const *__restrict file,
                         char const *args,
                         ...) THROWS(...) {
	__REDIRECT_XEXECLE(char, libc_Execvpe, file, args)
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(Execl, libc_Execl);
DEFINE_PUBLIC_ALIAS(Execle, libc_Execle);
DEFINE_PUBLIC_ALIAS(Execpl, libc_Execpl);
DEFINE_PUBLIC_ALIAS(Execlpe, libc_Execlpe);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_KOS_UNISTD_C */
