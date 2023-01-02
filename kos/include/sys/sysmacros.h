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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/sysmacros.h) */
/* (#) Portability: DJGPP         (/include/sys/sysmacros.h) */
/* (#) Portability: GNU C Library (/misc/sys/sysmacros.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/sysmacros.h) */
/* (#) Portability: diet libc     (/include/sys/sysmacros.h) */
/* (#) Portability: libc4/5       (/include/sys/sysmacros.h) */
/* (#) Portability: mintlib       (/include/sys/sysmacros.h) */
/* (#) Portability: musl libc     (/include/sys/sysmacros.h) */
/* (#) Portability: uClibc        (/include/sys/sysmacros.h) */
#ifndef _SYS_SYSMACROS_H
#define _SYS_SYSMACROS_H 1

#include <sys/mkdev.h>

#ifdef major
#define gnu_dev_major(dev) major(dev)
#endif /* major */
#ifdef minor
#define gnu_dev_minor(dev) minor(dev)
#endif /* minor */
#ifdef makedev
#define gnu_dev_makedev(major, minor) makedev(major, minor)
#endif /* makedev */

#endif /* !_SYS_SYSMACROS_H */
