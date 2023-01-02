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
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/netinet/if_fddi.h) */
/* (#) Portability: libc6         (/include/netinet/if_fddi.h) */
/* (#) Portability: uClibc        (/include/netinet/if_fddi.h) */
#ifndef _NETINET_IF_FDDI_H
#define _NETINET_IF_FDDI_H 1

#include <__stdinc.h>
#include <features.h>

#include <linux/if_fddi.h>

#if defined(__USE_MISC) && defined(__CC__) && !defined(__USE_KOS_PURE)
#include <bits/types.h>
#endif /* __USE_MISC && __CC__ && !__USE_KOS_PURE */

#ifdef __USE_GLIBC_BLOAT
#include <sys/types.h>
#endif /* __USE_GLIBC_BLOAT */

/* Copyright (C) 1997-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

__SYSDECL_BEGIN

#ifdef __USE_MISC
#ifdef __CC__
#ifndef __USE_KOS_PURE /* Use `struct fddihdr' instead */
struct fddi_header {
	__uint8_t fddi_fc;                 /* Frame Control (FC) value. */
	__uint8_t fddi_dhost[FDDI_K_ALEN]; /* Destination address. */
	__uint8_t fddi_shost[FDDI_K_ALEN]; /* Source address. */
};
#endif /* !__USE_KOS_PURE */
#endif /* __CC__ */
#endif /* __USE_MISC */

__SYSDECL_END

#endif /* _NETINET_IF_FDDI_H */
