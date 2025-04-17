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
/*!replace_with_include <bits/os/ifconf.h>*/
#ifndef _BITS_OS_KOS_IFCONF_H
#define _BITS_OS_KOS_IFCONF_H 1

#include <__stdinc.h>
#include <features.h>

#ifdef __CC__
__DECL_BEGIN

#undef ifc_buf
#undef ifc_req
struct ifconf {
	__STDC_INT_AS_SIZE_T ifc_len; /* ??? */
#ifdef __COMPILER_HAVE_TRANSPARENT_UNION
	union {
		char         *ifc_buf; /* Buffer address */
		struct ifreq *ifc_req; /* Buffer address */
#ifndef __USE_KOS_PURE
		union {
			char         *ifcu_buf; /* Buffer address */
			struct ifreq *ifcu_req; /* Buffer address */
		} ifc_ifcu;
#endif /* !__USE_KOS_PURE */
	};
#else /* __COMPILER_HAVE_TRANSPARENT_UNION */
	union {
		char         *ifcu_buf; /* Buffer address */
		struct ifreq *ifcu_req; /* Buffer address */
	} ifc_ifcu;
#define ifc_buf ifc_ifcu.ifcu_buf /* Buffer address */
#define ifc_req ifc_ifcu.ifcu_req /* Buffer address */
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_KOS_IFCONF_H */
