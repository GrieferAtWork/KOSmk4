/* HASH CRC-32:0xc6cb538d */
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
#ifndef __local_getdtablesize_defined
#define __local_getdtablesize_defined
#include <__crt.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(getdtablesize) __ATTR_CONST __ATTR_WUNUSED __STDC_INT_AS_SIZE_T
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(getdtablesize))(void) {
#ifdef __KOS__
	return 0x7fffffff; /* INT_MAX */
#elif defined(__linux__) || defined(__linux) || defined(linux)
	return 0x10000;    /* UINT16_MAX + 1 */
#else /* ... */
	return 256;        /* UINT8_MAX + 1 */
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getdtablesize_defined
#define __local___localdep_getdtablesize_defined
#define __localdep_getdtablesize __LIBC_LOCAL_NAME(getdtablesize)
#endif /* !__local___localdep_getdtablesize_defined */
#endif /* !__local_getdtablesize_defined */
