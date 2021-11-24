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
#ifndef _KOS_IOCTL_TASK_H
#define _KOS_IOCTL_TASK_H 1

/* KOS-specific ioctls for `HANDLE_TYPE_TASK' (aka `pidfd_open(2)')
 * HINT: These commands can also be invoked on `open("/proc/[pid]")'! */

#include <__stdinc.h>

#include <asm/ioctl.h>
#include <bits/types.h>

#include "_openfd.h"

/* These ioctl codes can be used to augment pidfd functionality. */
#define TASK_IOC_GETTID     _IOR_KOS('p', 0x00, __pid_t)       /* gettid()  -- Get thread ID */
#define TASK_IOC_GETPID     _IOR_KOS('p', 0x01, __pid_t)       /* getpid()  -- Get process ID */
#define TASK_IOC_GETPPID    _IOR_KOS('p', 0x02, __pid_t)       /* getppid() -- Get parent process ID */
#define TASK_IOC_GETPGID    _IOR_KOS('p', 0x03, __pid_t)       /* getpgid() -- Get process group ID */
#define TASK_IOC_GETSID     _IOR_KOS('p', 0x04, __pid_t)       /* getsid()  -- Get session ID */
/*      TASK_IOC_            _IO_KOS('p', 0x05, ...)            * ... */
/*      TASK_IOC_            _IO_KOS('p', 0x06, ...)            * ... */
/*      TASK_IOC_            _IO_KOS('p', 0x07, ...)            * ... */
/*      TASK_IOC_            _IO_KOS('p', 0x08, ...)            * ... */
#define TASK_IOC_OPENPID    _IOR_KOS('p', 0x09, struct openfd) /* pidfd_open(getpid()) */
#define TASK_IOC_OPENPPID   _IOR_KOS('p', 0x0a, struct openfd) /* pidfd_open(getppid()) */
#define TASK_IOC_OPENPGID   _IOR_KOS('p', 0x0b, struct openfd) /* pidfd_open(getpgid()) */
#define TASK_IOC_OPENSID    _IOR_KOS('p', 0x0c, struct openfd) /* pidfd_open(getsid()) */
/*      TASK_IOC_            _IO_KOS('p', 0x0d, ...)            * ... */
/*      TASK_IOC_            _IO_KOS('p', 0x0e, ...)            * ... */
/*      TASK_IOC_            _IO_KOS('p', 0x0f, ...)            * ... */

#endif /* !_KOS_IOCTL_TASK_H */
