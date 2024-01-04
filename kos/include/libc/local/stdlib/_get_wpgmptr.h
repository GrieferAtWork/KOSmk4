/* HASH CRC-32:0xcdada509 */
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
#ifndef __local__get_wpgmptr_defined
#define __local__get_wpgmptr_defined
#include <__crt.h>
#ifdef __CRT_HAVE___p__wpgmptr
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep___p__wpgmptr_defined
#define __local___localdep___p__wpgmptr_defined
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__WCHAR_TYPE__ **,__NOTHROW,__localdep___p__wpgmptr,(void),__p__wpgmptr,())
#endif /* !__local___localdep___p__wpgmptr_defined */
__LOCAL_LIBC(_get_wpgmptr) __ATTR_OUT(1) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_get_wpgmptr))(__WCHAR_TYPE__ **__pvalue) {
	*__pvalue = *(__NAMESPACE_LOCAL_SYM __localdep___p__wpgmptr)();
	return __EOK;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__get_wpgmptr_defined
#define __local___localdep__get_wpgmptr_defined
#define __localdep__get_wpgmptr __LIBC_LOCAL_NAME(_get_wpgmptr)
#endif /* !__local___localdep__get_wpgmptr_defined */
#else /* __CRT_HAVE___p__wpgmptr */
#undef __local__get_wpgmptr_defined
#endif /* !__CRT_HAVE___p__wpgmptr */
#endif /* !__local__get_wpgmptr_defined */
