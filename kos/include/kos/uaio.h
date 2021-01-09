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
#ifndef _KOS_UAIO_H
#define _KOS_UAIO_H 1

#include <__stdinc.h>
#include <features.h>

#include <bits/os/timespec.h>
#include <bits/types.h>
#include <kos/anno.h>
#include <kos/asm/uaio.h>
#include <kos/bits/uaio.h>
#include <kos/hop/uaio.h>
#include <kos/ksysctl.h>

__DECL_BEGIN

#ifdef __CC__

/* Create a new UAIO controller file descriptor.
 * WARNING: The resulting UAIO object is bound to the calling process's VM!
 *          You can share the UAIO object between processes, just like any
 *          other UAIO object, however attempting to use `UAio_Start()' in
 *          a process other than the one that originally created the UAIO
 *          controller will cause `UAio_Start()' to return by throwing an
 *          `E_ILLEGAL_OPERATION' exception.
 * @param: uaio_flags: Set of `UAIO_CREATE_*'
 * @throws: E_BADALLOC: [...] */
#ifdef __ksysctl_defined
__LOCAL __ATTR_WUNUSED __fd_t
__NOTHROW_NCX(__LIBCCALL uaio_create)(__syscall_ulong_t __uaio_flags) {
	return ksysctl(KSYSCTL_UAIO_CREATE, __uaio_flags);
}
#endif /* __ksysctl_defined */
#ifdef __KSysctl_defined
__LOCAL __ATTR_WUNUSED __fd_t __LIBCCALL
UAio_Create(__syscall_ulong_t __uaio_flags) {
	return KSysctl(KSYSCTL_UAIO_CREATE, __uaio_flags);
}
#endif /* __KSysctl_defined */

/* Start a UAIO command chain.
 * NOTE: You are allowed to start (enqueue) additional UAIO operation before `self'
 *       has finished. However the order in which newly added operation are executed
 *       in relation to pre-existing operations is undefined.
 *       Additionally, the kernel is allowed to implement this case by modifying the
 *       `ua_next' pointers of the given `ops'
 * NOTE: You can wait for the UAIO object to finish all of the given UAIO operations
 *       by polling it for `POLLIN', or by using `do read(self, &c, 1); while (c != 0);'
 *       Note that `read()' will always return 1 byte of data that is a 0-byte if UAIO
 *       has been completed, and `1' if UAIO is currently in progress. The later will
 *       only ever be returned when the `IO_NONBLOCK' flag is set for `self'. If that
 *       flag is not set, then `read()' will block until all operations have completed.
 * @throws: E_BADALLOC:          [...]
 * @throws: E_INVALID_HANDLE:    [...]
 * @throws: E_ILLEGAL_OPERATION: The given UAIO object is bound to a different process's VM.
 *                               Or in other words: You're not the one that created this UAIO
 *                               object. You're only allowed to poll() and read() in order to
 *                               wait for the UAIO object to complete. */
#ifdef __hop_defined
__LOCAL __ATTR_NONNULL((2)) int
__NOTHROW_NCX(__LIBCCALL uaio_start)(__fd_t __self, struct uaio *__restrict __ops) {
	return hop(__self, HOP_UAIO_START, __ops);
}
#endif /* __hop_defined */
#ifdef __Hop_defined
__LOCAL __ATTR_NONNULL((2)) void __LIBCCALL
UAio_Start(__fd_t __self, struct uaio *__restrict __ops) {
	Hop(__self, HOP_UAIO_START, __ops);
}
#endif /* __Hop_defined */

/* Cancel all pending UAIO operations that haven't been completed, yet.
 * NOTE: 
 * @throws: E_INVALID_HANDLE: [...] */
#ifdef __hop_defined
__LOCAL int __NOTHROW_NCX(__LIBCCALL uaio_cancel)(__fd_t __self) {
	return hop(__self, HOP_UAIO_CANCEL);
}
#endif /* __hop_defined */
#ifdef __Hop_defined
__LOCAL __ATTR_NONNULL((2)) void __LIBCCALL
UAio_Cancel(__fd_t __self, struct uaio *__restrict __ops) {
	Hop(__self, HOP_UAIO_CANCEL);
}
#endif /* __Hop_defined */

#endif /* __CC__ */

__DECL_END

#endif /* !_KOS_UAIO_H */
