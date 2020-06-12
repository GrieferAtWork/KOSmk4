/* HASH CRC-32:0xd3f9ff24 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_PROCESS_C
#define GUARD_LIBC_AUTO_PROCESS_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/process.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.sched.thread") void
NOTHROW_NCX(LIBCCALL libc__endthread)(void) {
	_endthreadex(0);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.process") void
(LIBCCALL libc__c_exit)(void) THROWS(...) {
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") ATTR_SENTINEL NONNULL((2)) pid_t
NOTHROW_RPC(VLIBCCALL libc_spawnl)(int mode,
                                   char const *__restrict path,
                                   char const *args,
                                   ...) {
	__REDIRECT_SPAWNL(char, spawnv, mode, path, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") ATTR_SENTINEL NONNULL((2)) pid_t
NOTHROW_RPC(VLIBCCALL libc_spawnlp)(int mode,
                                    char const *__restrict file,
                                    char const *args,
                                    ...) {
	__REDIRECT_SPAWNL(char, spawnvp, mode, file, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") ATTR_SENTINEL_O(1) NONNULL((2)) pid_t
NOTHROW_RPC(VLIBCCALL libc_spawnle)(int mode,
                                    char const *__restrict path,
                                    char const *args,
                                    ...) {
	__REDIRECT_SPAWNLE(char, spawnve, mode, path, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") ATTR_SENTINEL_O(1) NONNULL((2)) pid_t
NOTHROW_RPC(VLIBCCALL libc_spawnlpe)(int mode,
                                     char const *__restrict file,
                                     char const *args,
                                     ...) {
	__REDIRECT_SPAWNLE(char, spawnvpe, mode, file, args)
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_endthread, libc__endthread);
DEFINE_PUBLIC_ALIAS(_c_exit, libc__c_exit);
DEFINE_PUBLIC_ALIAS(_spawnl, libc_spawnl);
DEFINE_PUBLIC_ALIAS(spawnl, libc_spawnl);
DEFINE_PUBLIC_ALIAS(_spawnlp, libc_spawnlp);
DEFINE_PUBLIC_ALIAS(spawnlp, libc_spawnlp);
DEFINE_PUBLIC_ALIAS(_spawnle, libc_spawnle);
DEFINE_PUBLIC_ALIAS(spawnle, libc_spawnle);
DEFINE_PUBLIC_ALIAS(_spawnlpe, libc_spawnlpe);
DEFINE_PUBLIC_ALIAS(spawnlpe, libc_spawnlpe);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_PROCESS_C */
