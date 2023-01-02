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
#ifndef _ASM_OS_KOS_FILE_IOCTLS_H
#define _ASM_OS_KOS_FILE_IOCTLS_H 1

#include <__stdinc.h>

#include <asm/ioctl.h>

#ifndef __linux__

/* Arguments for `_FIODIRECTIO' from <sys/filio.h> */
#define __DIRECTIO_OFF  0 /* Disable optional direct I/O (clear O_DIRECT and IO_OPTDIRECT) */
#define __DIRECTIO_ON   1 /* Enable optional direct I/O  (set O_DIRECT and IO_OPTDIRECT) */
#define __DIRECTIO_MAND 2 /* Enable mandatory direct I/O (only set O_DIRECT; KOS-specific) */

/* Enable/disable optional direct I/O (s.a. `IO_OPTDIRECT')
 * NOTE: On KOS, this ioctl also exists as `FD_IOC_DIRECTIO' */
#define __FIODIRECTIO _IO_KOS('f', 0x4c)
#endif /* !__linux__ */

#endif /* !_ASM_OS_KOS_FILE_IOCTLS_H */
