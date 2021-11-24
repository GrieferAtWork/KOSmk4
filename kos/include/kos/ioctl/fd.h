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
#ifndef _KOS_IOCTL_FD_H
#define _KOS_IOCTL_FD_H 1

/* ioctl control code that operate at the handle-level.
 * -> These can be used on _ALL_ file descriptors, without exception! */

#include <__stdinc.h>

#include <asm/ioctl.h>
#include <asm/os/block.h>
#include <asm/os/tty.h>

/* NOTE: By default, trying to  invoke an ioctl with  type='T'
 *       that isn't supported has ioctl(2) return with ENOTTY! */
#define FD_IOC_NCLEX  __FIONCLEX /* Clear O_CLOEXEC / IO_CLOEXEC */
#define FD_IOC_CLEX   __FIOCLEX  /* Set O_CLOEXEC / IO_CLOEXEC */
#define FD_IOC_ASYNC  __FIOASYNC /* [int *arg] Set (*arg != 0) or clear (*arg == 0) O_ASYNC / IO_ASYNC */
#define FD_IOC_NBIO   __FIONBIO  /* [int *arg] Set (*arg != 0) or clear (*arg == 0) O_NONBLOCK / IO_NONBLOCK */
#define FD_IOC_QSIZE  __FIOQSIZE /* [loff_t *arg] Return object data-size (not supported by all types of objects) */
#define FD_IOC_GETBSZ __FIGETBSZ /* [int *arg] Return `struct stat::st_blksize' */

/*  */



#endif /* !_KOS_IOCTL_FD_H */
