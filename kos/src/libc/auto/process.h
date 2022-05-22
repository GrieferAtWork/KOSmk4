/* HASH CRC-32:0xc20cfdd */
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
#ifndef GUARD_LIBC_AUTO_PROCESS_H
#define GUARD_LIBC_AUTO_PROCESS_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <process.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF uintptr_t NOTHROW_NCX(LIBDCALL libd__beginthread)(void (LIBDCALL *entry)(void *arg), u32 stacksz, void *arg);
INTDEF uintptr_t NOTHROW_NCX(LIBDCALL libd__beginthreadex)(void *sec, u32 stacksz, __dos_beginthreadex_entry_t entry, void *arg, u32 flags, u32 *threadaddr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF void NOTHROW_NCX(LIBCCALL libc__endthread)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF void NOTHROW_NCX(LIBDCALL libd__endthreadex)(u32 exitcode);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF void (LIBCCALL libc__c_exit)(void) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF int (LIBDCALL libd__unloaddll)(intptr_t hnd) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF int (LIBCCALL libc__unloaddll)(intptr_t hnd) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_ACCESS_RO_OPT(2) __procfun (LIBDCALL libd__getdllprocaddr)(intptr_t hnd, char __KOS_FIXED_CONST *symname, intptr_t ord) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_ACCESS_RO_OPT(2) __procfun (LIBCCALL libc__getdllprocaddr)(intptr_t hnd, char __KOS_FIXED_CONST *symname, intptr_t ord) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> cwait(3)
 * DOS name for `waitpid(2)', except that `action' is ignored. Use
 * this function together with the `spawn(3)' family of functions.
 * @return: pid: Child process exited.
 * @return: -1:  Error (s.a. `errno') */
INTDEF ATTR_ACCESS_WR_OPT(1) pid_t NOTHROW_RPC(LIBDCALL libd_cwait)(int *tstat, pid_t pid, __STDC_INT_AS_UINT_T action);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> cwait(3)
 * DOS name for `waitpid(2)', except that `action' is ignored. Use
 * this function together with the `spawn(3)' family of functions.
 * @return: pid: Child process exited.
 * @return: -1:  Error (s.a. `errno') */
INTDEF ATTR_ACCESS_WR_OPT(1) pid_t NOTHROW_RPC(LIBCCALL libc_cwait)(int *tstat, pid_t pid, __STDC_INT_AS_UINT_T action);
INTDEF ATTR_ACCESS_RO(2) ATTR_ACCESS_RO(3) pid_t NOTHROW_RPC(LIBDCALL libd_spawnv)(__STDC_INT_AS_UINT_T mode, char const *__restrict path, __TARGV);
INTDEF ATTR_ACCESS_RO(2) ATTR_ACCESS_RO(3) pid_t NOTHROW_RPC(LIBCCALL libc_spawnv)(__STDC_INT_AS_UINT_T mode, char const *__restrict path, __TARGV);
INTDEF ATTR_ACCESS_RO(2) ATTR_ACCESS_RO(3) pid_t NOTHROW_RPC(LIBDCALL libd_spawnvp)(__STDC_INT_AS_UINT_T mode, char const *__restrict file, __TARGV);
INTDEF ATTR_ACCESS_RO(2) ATTR_ACCESS_RO(3) pid_t NOTHROW_RPC(LIBCCALL libc_spawnvp)(__STDC_INT_AS_UINT_T mode, char const *__restrict file, __TARGV);
INTDEF ATTR_ACCESS_RO(2) ATTR_ACCESS_RO(3) ATTR_ACCESS_RO(4) pid_t NOTHROW_RPC(LIBDCALL libd_spawnve)(__STDC_INT_AS_UINT_T mode, char const *__restrict path, __TARGV, __TENVP);
INTDEF ATTR_ACCESS_RO(2) ATTR_ACCESS_RO(3) ATTR_ACCESS_RO(4) pid_t NOTHROW_RPC(LIBCCALL libc_spawnve)(__STDC_INT_AS_UINT_T mode, char const *__restrict path, __TARGV, __TENVP);
INTDEF ATTR_ACCESS_RO(2) ATTR_ACCESS_RO(3) ATTR_ACCESS_RO(4) pid_t NOTHROW_RPC(LIBDCALL libd_spawnvpe)(__STDC_INT_AS_UINT_T mode, char const *__restrict file, __TARGV, __TENVP);
INTDEF ATTR_ACCESS_RO(2) ATTR_ACCESS_RO(3) ATTR_ACCESS_RO(4) pid_t NOTHROW_RPC(LIBCCALL libc_spawnvpe)(__STDC_INT_AS_UINT_T mode, char const *__restrict file, __TARGV, __TENVP);
INTDEF ATTR_SENTINEL ATTR_ACCESS_RO(2) ATTR_ACCESS_RO_OPT(3) pid_t NOTHROW_RPC(VLIBDCALL libd_spawnl)(__STDC_INT_AS_UINT_T mode, char const *__restrict path, char const *args, ...);
INTDEF ATTR_SENTINEL ATTR_ACCESS_RO(2) ATTR_ACCESS_RO_OPT(3) pid_t NOTHROW_RPC(VLIBCCALL libc_spawnl)(__STDC_INT_AS_UINT_T mode, char const *__restrict path, char const *args, ...);
INTDEF ATTR_SENTINEL ATTR_ACCESS_RO(2) ATTR_ACCESS_RO_OPT(3) pid_t NOTHROW_RPC(VLIBDCALL libd_spawnlp)(__STDC_INT_AS_UINT_T mode, char const *__restrict file, char const *args, ...);
INTDEF ATTR_SENTINEL ATTR_ACCESS_RO(2) ATTR_ACCESS_RO_OPT(3) pid_t NOTHROW_RPC(VLIBCCALL libc_spawnlp)(__STDC_INT_AS_UINT_T mode, char const *__restrict file, char const *args, ...);
INTDEF ATTR_ACCESS_RO(2) ATTR_ACCESS_RO_OPT(3) ATTR_SENTINEL_O(1) pid_t NOTHROW_RPC(VLIBDCALL libd_spawnle)(__STDC_INT_AS_UINT_T mode, char const *__restrict path, char const *args, ...);
INTDEF ATTR_ACCESS_RO(2) ATTR_ACCESS_RO_OPT(3) ATTR_SENTINEL_O(1) pid_t NOTHROW_RPC(VLIBCCALL libc_spawnle)(__STDC_INT_AS_UINT_T mode, char const *__restrict path, char const *args, ...);
INTDEF ATTR_ACCESS_RO(2) ATTR_ACCESS_RO_OPT(3) ATTR_SENTINEL_O(1) pid_t NOTHROW_RPC(VLIBDCALL libd_spawnlpe)(__STDC_INT_AS_UINT_T mode, char const *__restrict file, char const *args, ...);
INTDEF ATTR_ACCESS_RO(2) ATTR_ACCESS_RO_OPT(3) ATTR_SENTINEL_O(1) pid_t NOTHROW_RPC(VLIBCCALL libc_spawnlpe)(__STDC_INT_AS_UINT_T mode, char const *__restrict file, char const *args, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_ACCESS_RO(3) ATTR_ACCESS_RO(4) pid_t NOTHROW_RPC(LIBDCALL libd_fspawnve)(__STDC_INT_AS_UINT_T mode, fd_t execfd, __TARGV, __TENVP);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_ACCESS_RO(3) ATTR_ACCESS_RO(4) pid_t NOTHROW_RPC(LIBCCALL libc_fspawnve)(__STDC_INT_AS_UINT_T mode, fd_t execfd, __TARGV, __TENVP);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_PROCESS_H */
