/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: DragonFly BSD (/sys/sys/ioccom.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/ioccom.h) */
/* (#) Portability: FreeBSD       (/sys/sys/ioccom.h) */
/* (#) Portability: NetBSD        (/sys/sys/ioccom.h) */
/* (#) Portability: OpenBSD       (/sys/sys/ioccom.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/ioccom.h) */
#ifndef _SYS_IOCCOM_H
#define _SYS_IOCCOM_H 1

#include <__stdinc.h>

#include <asm/ioctl.h>

#define IOCPARM_MASK        _IOC_SIZEMASK
#define IOCPARM_LEN         _IOC_SIZE
#define IOCBASECMD(x)       ((x) & ~(_IOC_SIZEMASK << _IOC_SIZESHIFT))
#define IOCGROUP            _IOC_TYPE
#define IOCPARM_MAX         _IOC_SIZEMASK
#define IOC_VOID            0
#define IOC_DIRMASK         _IOC_DIRMASK
#define IOC_IN              _IOC_IN
#define IOC_OUT             _IOC_OUT
#define IOC_INOUT           _IOC_INOUT
#define _IORN(type, nr, N)  _IOC(_IOC_READ, type, nr, N)
#define _IOWN(type, nr, N)  _IOC(_IOC_WRITE, type, nr, N)
#define _IOWRN(type, nr, N) _IOC(_IOC_READ | _IOC_WRITE, type, nr, N)

#endif /* !_SYS_IOCCOM_H */
