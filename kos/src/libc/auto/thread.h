/* HASH CRC-32:0x2bcc14dc */
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
#ifndef GUARD_LIBC_AUTO_THREAD_H
#define GUARD_LIBC_AUTO_THREAD_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <thread.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_ACCESS_WR(6) NONNULL((3)) errno_t NOTHROW_NCX(LIBDCALL libd_thr_create)(void *stack_base, size_t stack_size, void *(LIBDCALL *start_routine)(void *arg), void *arg, long flags, thread_t *newthread);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_ACCESS_WR(6) NONNULL((3)) errno_t NOTHROW_NCX(LIBCCALL libc_thr_create)(void *stack_base, size_t stack_size, void *(LIBCCALL *start_routine)(void *arg), void *arg, long flags, thread_t *newthread);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_ACCESS_WR(2) ATTR_ACCESS_WR_OPT(3) errno_t NOTHROW_RPC(LIBDCALL libd_thr_join)(thread_t thr, thread_t *p_departed, void **thread_return);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_ACCESS_WR(2) ATTR_ACCESS_WR_OPT(3) errno_t NOTHROW_RPC(LIBCCALL libc_thr_join)(thread_t thr, thread_t *p_departed, void **thread_return);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_thr_setprio)(thread_t thr, int priority);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_thr_setprio)(thread_t thr, int priority);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBDCALL libd_thr_getprio)(thread_t thr, int *p_priority);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBCCALL libc_thr_getprio)(thread_t thr, int *p_priority);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_ACCESS_WR(2) errno_t NOTHROW_NCX(LIBDCALL libd_thr_getspecific)(thread_key_t key, void **p_val);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_ACCESS_WR(2) errno_t NOTHROW_NCX(LIBCCALL libc_thr_getspecific)(thread_key_t key, void **p_val);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> thr_stksegment(3)
 * Wrapper for `pthread_stackseg_np(pthread_self(), sinfo)' */
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_thr_stksegment)(stack_t *sinfo);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> thr_stksegment(3)
 * Wrapper for `pthread_stackseg_np(pthread_self(), sinfo)' */
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_thr_stksegment)(stack_t *sinfo);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_THREAD_H */
