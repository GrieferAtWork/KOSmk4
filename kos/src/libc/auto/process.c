/* HASH CRC-32:0xc74376f */
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
	libc__endthreadex(0);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.process") void
(LIBCCALL libc__c_exit)(void) THROWS(...) {
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.spawn") ATTR_SENTINEL NONNULL((2)) pid_t
NOTHROW_RPC(VLIBDCALL libd_spawnl)(int mode,
                                   char const *__restrict path,
                                   char const *args,
                                   ...) {
	__REDIRECT_SPAWNL(char, libc_spawnv, mode, path, args)
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") ATTR_SENTINEL NONNULL((2)) pid_t
NOTHROW_RPC(VLIBCCALL libc_spawnl)(int mode,
                                   char const *__restrict path,
                                   char const *args,
                                   ...) {
	__REDIRECT_SPAWNL(char, libc_spawnv, mode, path, args)
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.spawn") ATTR_SENTINEL NONNULL((2)) pid_t
NOTHROW_RPC(VLIBDCALL libd_spawnlp)(int mode,
                                    char const *__restrict file,
                                    char const *args,
                                    ...) {
	__REDIRECT_SPAWNL(char, libc_spawnvp, mode, file, args)
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") ATTR_SENTINEL NONNULL((2)) pid_t
NOTHROW_RPC(VLIBCCALL libc_spawnlp)(int mode,
                                    char const *__restrict file,
                                    char const *args,
                                    ...) {
	__REDIRECT_SPAWNL(char, libc_spawnvp, mode, file, args)
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.spawn") ATTR_SENTINEL_O(1) NONNULL((2)) pid_t
NOTHROW_RPC(VLIBDCALL libd_spawnle)(int mode,
                                    char const *__restrict path,
                                    char const *args,
                                    ...) {
	__REDIRECT_SPAWNLE(char, libc_spawnve, mode, path, args)
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") ATTR_SENTINEL_O(1) NONNULL((2)) pid_t
NOTHROW_RPC(VLIBCCALL libc_spawnle)(int mode,
                                    char const *__restrict path,
                                    char const *args,
                                    ...) {
	__REDIRECT_SPAWNLE(char, libc_spawnve, mode, path, args)
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.spawn") ATTR_SENTINEL_O(1) NONNULL((2)) pid_t
NOTHROW_RPC(VLIBDCALL libd_spawnlpe)(int mode,
                                     char const *__restrict file,
                                     char const *args,
                                     ...) {
	__REDIRECT_SPAWNLE(char, libc_spawnvpe, mode, file, args)
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") ATTR_SENTINEL_O(1) NONNULL((2)) pid_t
NOTHROW_RPC(VLIBCCALL libc_spawnlpe)(int mode,
                                     char const *__restrict file,
                                     char const *args,
                                     ...) {
	__REDIRECT_SPAWNLE(char, libc_spawnvpe, mode, file, args)
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_endthread, libc__endthread);
DEFINE_PUBLIC_ALIAS(_c_exit, libc__c_exit);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_spawnl, libd_spawnl);
DEFINE_PUBLIC_ALIAS(DOS$spawnl, libd_spawnl);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_spawnl, libc_spawnl);
DEFINE_PUBLIC_ALIAS(spawnl, libc_spawnl);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_spawnlp, libd_spawnlp);
DEFINE_PUBLIC_ALIAS(DOS$spawnlp, libd_spawnlp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_spawnlp, libc_spawnlp);
DEFINE_PUBLIC_ALIAS(spawnlp, libc_spawnlp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_spawnle, libd_spawnle);
DEFINE_PUBLIC_ALIAS(DOS$spawnle, libd_spawnle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_spawnle, libc_spawnle);
DEFINE_PUBLIC_ALIAS(spawnle, libc_spawnle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_spawnlpe, libd_spawnlpe);
DEFINE_PUBLIC_ALIAS(DOS$spawnlpe, libd_spawnlpe);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_spawnlpe, libc_spawnlpe);
DEFINE_PUBLIC_ALIAS(spawnlpe, libc_spawnlpe);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_PROCESS_C */
