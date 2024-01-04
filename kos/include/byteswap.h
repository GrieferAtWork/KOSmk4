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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/byteswap.h) */
/* (#) Portability: DragonFly BSD (/include/byteswap.h) */
/* (#) Portability: GNU C Library (/string/byteswap.h) */
/* (#) Portability: GNU Hurd      (/usr/include/byteswap.h) */
/* (#) Portability: diet libc     (/include/byteswap.h) */
/* (#) Portability: libc6         (/include/byteswap.h) */
/* (#) Portability: mintlib       (/include/byteswap.h) */
/* (#) Portability: musl libc     (/include/byteswap.h) */
/* (#) Portability: uClibc        (/include/byteswap.h) */
#ifndef _BYTESWAP_H
#define _BYTESWAP_H 1

#include <features.h>

#include <hybrid/__byteswap.h>

#define bswap_16(x) __hybrid_bswap16(x)
#define bswap_32(x) __hybrid_bswap32(x)
#define bswap_64(x) __hybrid_bswap64(x)

/* Define  escaped  byteorder macros  since  some programs
 * wrongly  think that <byteswap.h>  is supposed to define
 * these (*cough* libpciaccess *cough*), when in actuality
 * it's <endian.h> that's defining them...
 *
 * On true Glibc, many headers implicitly include <endian.h>,
 * and thus implicitly define these macros as well (fun  fact
 * though: not actually <byteswap.h>),  but since I  suspect
 * that more programs might make this mistake, do them all a
 * favor and define them here (at least as long as we're not
 * in one of the pure-header modes) */
#if !defined(__USE_ISOC_PURE) && !defined(__USE_KOS_PURE)
#include <hybrid/byteorder.h>
#ifndef __ORDER_LITTLE_ENDIAN__
#define __ORDER_LITTLE_ENDIAN__ 1234
#endif /* !__ORDER_LITTLE_ENDIAN__ */
#ifndef __ORDER_BIG_ENDIAN__
#define __ORDER_BIG_ENDIAN__ 4321
#endif /* !__ORDER_BIG_ENDIAN__ */
#ifndef __ORDER_PDP_ENDIAN__
#define __ORDER_PDP_ENDIAN__ 3412
#endif /* !__ORDER_PDP_ENDIAN__ */
#ifndef __LITTLE_ENDIAN
#define __LITTLE_ENDIAN __ORDER_LITTLE_ENDIAN__
#define __BIG_ENDIAN    __ORDER_BIG_ENDIAN__
#define __PDP_ENDIAN    __ORDER_PDP_ENDIAN__
#endif /* !__LITTLE_ENDIAN */
#ifndef __BYTE_ORDER
#define __BYTE_ORDER __BYTE_ORDER__
#endif /* !__BYTE_ORDER */
#endif /* !__USE_ISOC_PURE && !__USE_KOS_PURE */

#endif /* !_BYTESWAP_H */
