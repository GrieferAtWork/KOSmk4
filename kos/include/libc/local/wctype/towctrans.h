/* HASH CRC-32:0xc6b88f4e */
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
#ifndef __local_towctrans_defined
#define __local_towctrans_defined
#include <__crt.h>
#if defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor)
#include <hybrid/typecore.h>
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep___unicode_descriptor_defined
#define __local___localdep___unicode_descriptor_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/unicode.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_RETNONNULL,struct __unitraits const *,__NOTHROW,__localdep___unicode_descriptor,(__CHAR32_TYPE__ __ch),__unicode_descriptor,(__ch))
#endif /* !__local___localdep___unicode_descriptor_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/unicode.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(towctrans) __ATTR_CONST __ATTR_WUNUSED __WINT_TYPE__
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(towctrans))(__WINT_TYPE__ __wc, __wctrans_t __desc) {
	struct __unitraits const *__traits = (__NAMESPACE_LOCAL_SYM __localdep___unicode_descriptor)(__wc);
	return __wc + *((__INT32_TYPE__ const *)__traits + (__UINTPTR_TYPE__)__desc);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_towctrans_defined
#define __local___localdep_towctrans_defined
#define __localdep_towctrans __LIBC_LOCAL_NAME(towctrans)
#endif /* !__local___localdep_towctrans_defined */
#else /* __CRT_KOS && __CRT_HAVE___unicode_descriptor */
#undef __local_towctrans_defined
#endif /* !__CRT_KOS || !__CRT_HAVE___unicode_descriptor */
#endif /* !__local_towctrans_defined */
