/* HASH CRC-32:0x7ce140df */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_strnroff_defined
#define __local_strnroff_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strnrchrnul_defined
#define __local___localdep_strnrchrnul_defined
#ifdef __CRT_HAVE_strnrchrnul
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ACCESS_ROS(1, 3) __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strnrchrnul,(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen),strnrchrnul,(__haystack,__needle,__maxlen))
#else /* __CRT_HAVE_strnrchrnul */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strnrchrnul.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strnrchrnul __LIBC_LOCAL_NAME(strnrchrnul)
#endif /* !__CRT_HAVE_strnrchrnul */
#endif /* !__local___localdep_strnrchrnul_defined */
__LOCAL_LIBC(strnroff) __ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_ROS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strnroff))(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen) {
	return (__SIZE_TYPE__)((__NAMESPACE_LOCAL_SYM __localdep_strnrchrnul)(__haystack, __needle, __maxlen) - __haystack);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strnroff_defined
#define __local___localdep_strnroff_defined
#define __localdep_strnroff __LIBC_LOCAL_NAME(strnroff)
#endif /* !__local___localdep_strnroff_defined */
#endif /* !__local_strnroff_defined */
