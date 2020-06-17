/* HASH CRC-32:0x9f38db05 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_PROCESS_C
#define GUARD_LIBC_AUTO_DOSABI_PROCESS_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/process.h"

DECL_BEGIN

INTERN ATTR_SECTION(".text.crt.dos.sched.thread") uintptr_t
NOTHROW_NCX(LIBDCALL libd__beginthread)(__dos_beginthread_entry_t entry,
                                        u32 stacksz,
                                        void *arg) {
	return libc__beginthread(entry, stacksz, arg);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.thread") uintptr_t
NOTHROW_NCX(LIBDCALL libd__beginthreadex)(void *sec,
                                          u32 stacksz,
                                          __dos_beginthreadex_entry_t entry,
                                          void *arg,
                                          u32 flags,
                                          u32 *threadaddr) {
	return libc__beginthreadex(sec, stacksz, entry, arg, flags, threadaddr);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.thread") void
NOTHROW_NCX(LIBDCALL libd__endthreadex)(u32 exitcode) {
	libc__endthreadex(exitcode);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.dlfcn") intptr_t
(LIBDCALL libd__loaddll)(char __KOS_FIXED_CONST *file) THROWS(...) {
	return libc__loaddll(file);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.dlfcn") int
(LIBDCALL libd__unloaddll)(intptr_t hnd) THROWS(...) {
	return libc__unloaddll(hnd);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.dlfcn") __procfun
(LIBDCALL libd__getdllprocaddr)(intptr_t hnd,
                                char __KOS_FIXED_CONST *symname,
                                intptr_t ord) THROWS(...) {
	return libc__getdllprocaddr(hnd, symname, ord);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.spawn") pid_t
NOTHROW_RPC(LIBDCALL libd_cwait)(int *tstat,
                                 pid_t pid,
                                 int action) {
	return libc_cwait(tstat, pid, action);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.spawn") NONNULL((2, 3)) pid_t
NOTHROW_RPC(LIBDCALL libd_spawnv)(int mode,
                                  char const *__restrict path,
                                  __TARGV) {
	return libc_spawnv(mode, path, ___argv);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.spawn") NONNULL((2, 3)) pid_t
NOTHROW_RPC(LIBDCALL libd_spawnvp)(int mode,
                                   char const *__restrict file,
                                   __TARGV) {
	return libc_spawnvp(mode, file, ___argv);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.spawn") NONNULL((2, 3, 4)) pid_t
NOTHROW_RPC(LIBDCALL libd_spawnve)(int mode,
                                   char const *__restrict path,
                                   __TARGV,
                                   __TENVP) {
	return libc_spawnve(mode, path, ___argv, ___envp);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.spawn") NONNULL((2, 3, 4)) pid_t
NOTHROW_RPC(LIBDCALL libd_spawnvpe)(int mode,
                                    char const *__restrict file,
                                    __TARGV,
                                    __TENVP) {
	return libc_spawnvpe(mode, file, ___argv, ___envp);
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.spawn") ATTR_SENTINEL NONNULL((2)) pid_t
NOTHROW_RPC(VLIBDCALL libd_spawnl)(int mode,
                                   char const *__restrict path,
                                   char const *args,
                                   ...) {
	__REDIRECT_SPAWNL(char, libc_spawnv, mode, path, args)
}
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.spawn") ATTR_SENTINEL NONNULL((2)) pid_t
NOTHROW_RPC(VLIBDCALL libd_spawnlp)(int mode,
                                    char const *__restrict file,
                                    char const *args,
                                    ...) {
	__REDIRECT_SPAWNL(char, libc_spawnvp, mode, file, args)
}
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.spawn") ATTR_SENTINEL_O(1) NONNULL((2)) pid_t
NOTHROW_RPC(VLIBDCALL libd_spawnle)(int mode,
                                    char const *__restrict path,
                                    char const *args,
                                    ...) {
	__REDIRECT_SPAWNLE(char, libc_spawnve, mode, path, args)
}
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.spawn") ATTR_SENTINEL_O(1) NONNULL((2)) pid_t
NOTHROW_RPC(VLIBDCALL libd_spawnlpe)(int mode,
                                     char const *__restrict file,
                                     char const *args,
                                     ...) {
	__REDIRECT_SPAWNLE(char, libc_spawnvpe, mode, file, args)
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$_beginthread, libd__beginthread);
DEFINE_PUBLIC_ALIAS(DOS$_beginthreadex, libd__beginthreadex);
DEFINE_PUBLIC_ALIAS(DOS$_endthreadex, libd__endthreadex);
DEFINE_PUBLIC_ALIAS(DOS$_loaddll, libd__loaddll);
DEFINE_PUBLIC_ALIAS(DOS$_unloaddll, libd__unloaddll);
DEFINE_PUBLIC_ALIAS(DOS$_getdllprocaddr, libd__getdllprocaddr);
DEFINE_PUBLIC_ALIAS(DOS$_cwait, libd_cwait);
DEFINE_PUBLIC_ALIAS(DOS$cwait, libd_cwait);
DEFINE_PUBLIC_ALIAS(DOS$_spawnv, libd_spawnv);
DEFINE_PUBLIC_ALIAS(DOS$spawnv, libd_spawnv);
DEFINE_PUBLIC_ALIAS(DOS$_spawnvp, libd_spawnvp);
DEFINE_PUBLIC_ALIAS(DOS$spawnvp, libd_spawnvp);
DEFINE_PUBLIC_ALIAS(DOS$_spawnve, libd_spawnve);
DEFINE_PUBLIC_ALIAS(DOS$spawnve, libd_spawnve);
DEFINE_PUBLIC_ALIAS(DOS$_spawnvpe, libd_spawnvpe);
DEFINE_PUBLIC_ALIAS(DOS$spawnvpe, libd_spawnvpe);
DEFINE_PUBLIC_ALIAS(DOS$_spawnl, libd_spawnl);
DEFINE_PUBLIC_ALIAS(DOS$spawnl, libd_spawnl);
DEFINE_PUBLIC_ALIAS(DOS$_spawnlp, libd_spawnlp);
DEFINE_PUBLIC_ALIAS(DOS$spawnlp, libd_spawnlp);
DEFINE_PUBLIC_ALIAS(DOS$_spawnle, libd_spawnle);
DEFINE_PUBLIC_ALIAS(DOS$spawnle, libd_spawnle);
DEFINE_PUBLIC_ALIAS(DOS$_spawnlpe, libd_spawnlpe);
DEFINE_PUBLIC_ALIAS(DOS$spawnlpe, libd_spawnlpe);

#endif /* !GUARD_LIBC_AUTO_DOSABI_PROCESS_C */
