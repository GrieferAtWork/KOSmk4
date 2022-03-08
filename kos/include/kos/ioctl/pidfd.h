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
#ifndef _KOS_IOCTL_PIDFD_H
#define _KOS_IOCTL_PIDFD_H 1

/* KOS-specific ioctls for `HANDLE_TYPE_PIDFD' (aka `pidfd_open(2)')
 * HINT: These commands can also be invoked on `open("/proc/[pid]")'! */

#include <__stdinc.h>

#include <asm/ioctl.h>
#include <bits/types.h>

#include "_openfd.h"

/* These ioctl codes can be used to augment pidfd functionality. */
#define PIDFD_IOC_GETTID     _IOR_KOS('p', 0x00, __pid_t)       /* gettid()  -- Get thread ID */
#define PIDFD_IOC_GETPID     _IOR_KOS('p', 0x01, __pid_t)       /* getpid()  -- Get process ID */
#define PIDFD_IOC_GETPPID    _IOR_KOS('p', 0x02, __pid_t)       /* getppid() -- Get parent process ID */
#define PIDFD_IOC_GETPGID    _IOR_KOS('p', 0x03, __pid_t)       /* getpgid() -- Get process group ID */
#define PIDFD_IOC_GETSID     _IOR_KOS('p', 0x04, __pid_t)       /* getsid()  -- Get session ID */
/*      PIDFD_IOC_            _IO_KOS('p', 0x05, ...)            * ... */
/*      PIDFD_IOC_            _IO_KOS('p', 0x06, ...)            * ... */
/*      PIDFD_IOC_            _IO_KOS('p', 0x07, ...)            * ... */
/*      PIDFD_IOC_            _IO_KOS('p', 0x08, ...)            * ... */
#define PIDFD_IOC_OPENPID    _IOR_KOS('p', 0x09, struct openfd) /* pidfd_open(getpid()) */
#define PIDFD_IOC_OPENPPID   _IOR_KOS('p', 0x0a, struct openfd) /* pidfd_open(getppid()) */
/*      PIDFD_IOC_            _IO_KOS('p', 0x0b, ...)            * ... */
/*      PIDFD_IOC_            _IO_KOS('p', 0x0c, ...)            * ... */
/*      PIDFD_IOC_            _IO_KOS('p', 0x0d, ...)            * ... */
/*      PIDFD_IOC_            _IO_KOS('p', 0x0e, ...)            * ... */
/*      PIDFD_IOC_            _IO_KOS('p', 0x0f, ...)            * ... */
#define PIDFD_IOC_EXITCODE   _IOR_KOS('p', 0x10, union wait)    /* Throws `E_ILLEGAL_OPERATION_CONTEXT_TASK_NOT_EXITED' when still running. */

#endif /* !_KOS_IOCTL_PIDFD_H */
