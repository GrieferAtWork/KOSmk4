/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/*!replace_with_include <bits/os/cmsghdr.h>*/
#ifndef _I386_KOS_BITS_OS_KOS_CMSGHDR64_H
#define _I386_KOS_BITS_OS_KOS_CMSGHDR64_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <bits/types.h>

__DECL_BEGIN

#ifdef __x86_64__
#define __OFFSET_CMSGHDR_LEN   __OFFSET_CMSGHDRX64_LEN
#define __OFFSET_CMSGHDR_LEVEL __OFFSET_CMSGHDRX64_LEVEL
#define __OFFSET_CMSGHDR_TYPE  __OFFSET_CMSGHDRX64_TYPE
#define __OFFSET_CMSGHDR_DATA  __OFFSET_CMSGHDRX64_DATA
#define __ALIGNOF_CMSGHDR      __ALIGNOF_CMSGHDRX64
#define __cmsghdrx64           cmsghdr
#endif /* __x86_64__ */

#define __OFFSET_CMSGHDRX64_LEN   0
#define __OFFSET_CMSGHDRX64_LEVEL 8
#define __OFFSET_CMSGHDRX64_TYPE  12
#define __OFFSET_CMSGHDRX64_DATA  16
#define __ALIGNOF_CMSGHDRX64      8
#ifdef __CC__

#ifdef __USE_KOS_KERNEL
#define cmsghdrx64 __cmsghdrx64
#endif /* __USE_KOS_KERNEL */

/* Structure used for storage of ancillary data object information. */
struct __ATTR_ALIGNED(8) __cmsghdrx64 /*[NAME(cmsghdrx64)][PREFIX(cmsg_)]*/ {
	__UINT64_TYPE__  cmsg_len;     /* Length of data in cmsg_data plus length of cmsghdr structure. */
	__INT32_TYPE__   cmsg_level;   /* Originating protocol. (One of `SOL_*'; (always `SOL_SOCKET'?)) */
	__INT32_TYPE__   cmsg_type;    /* Protocol specific type (One of `SCM_*'). */
#ifdef __USE_KOS
	__COMPILER_FLEXIBLE_ARRAY(__BYTE_TYPE__, cmsg_data); /* Ancillary data. */
#else /* __USE_KOS */
	__COMPILER_FLEXIBLE_ARRAY(__BYTE_TYPE__, __cmsg_data); /* Ancillary data. */
#endif /* !__USE_KOS */
};

#endif /* __CC__ */

__DECL_END

#endif /* !_I386_KOS_BITS_OS_KOS_CMSGHDR64_H */
