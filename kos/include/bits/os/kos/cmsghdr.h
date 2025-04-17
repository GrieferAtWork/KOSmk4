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
#ifndef _BITS_OS_KOS_CMSGHDR_H
#define _BITS_OS_KOS_CMSGHDR_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

__DECL_BEGIN

#define __OFFSET_CMSGHDR_LEN   0
#define __OFFSET_CMSGHDR_LEVEL __SIZEOF_SIZE_T__
#define __OFFSET_CMSGHDR_TYPE  (__SIZEOF_SIZE_T__ + 4)
#define __OFFSET_CMSGHDR_DATA  (__SIZEOF_SIZE_T__ + 8)
#define __ALIGNOF_CMSGHDR      __SIZEOF_SIZE_T__
#ifdef __CC__

/* Structure used for storage of ancillary data object information. */
struct cmsghdr /*[PREFIX(cmsg_)]*/ {
#if __SIZEOF_SOCKLEN_T__ == __SIZEOF_SIZE_T__
	__socklen_t      cmsg_len;     /* Length of data in cmsg_data plus length of cmsghdr structure. */
#else /* __SIZEOF_SOCKLEN_T__ == __SIZEOF_SIZE_T__ */
	__size_t         cmsg_len;     /* Length of data in cmsg_data plus length of cmsghdr structure.
	                                * !! The type should be socklen_t but the definition
	                                *    of   the  kernel  is  incompatible  with  this. */
#endif /* __SIZEOF_SOCKLEN_T__ != __SIZEOF_SIZE_T__ */
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

#endif /* !_BITS_OS_KOS_CMSGHDR_H */
