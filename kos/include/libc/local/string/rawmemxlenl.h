/* HASH CRC-32:0xcdbf10f1 */
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
#ifndef __local_rawmemxlenl_defined
#define __local_rawmemxlenl_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_rawmemxchrl_defined
#define __local___localdep_rawmemxchrl_defined
#ifdef __CRT_HAVE_rawmemxchrl
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_rawmemxchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle),rawmemxchrl,(__haystack,__needle))
#else /* __CRT_HAVE_rawmemxchrl */
__NAMESPACE_LOCAL_END
#include <libc/local/string/rawmemxchrl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_rawmemxchrl __LIBC_LOCAL_NAME(rawmemxchrl)
#endif /* !__CRT_HAVE_rawmemxchrl */
#endif /* !__local___localdep_rawmemxchrl_defined */
__LOCAL_LIBC(rawmemxlenl) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(rawmemxlenl))(void const *__restrict __haystack, __UINT32_TYPE__ __needle) {
	return (__SIZE_TYPE__)((__NAMESPACE_LOCAL_SYM __localdep_rawmemxchrl)(__haystack, __needle) - (__UINT32_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_rawmemxlenl_defined
#define __local___localdep_rawmemxlenl_defined
#define __localdep_rawmemxlenl __LIBC_LOCAL_NAME(rawmemxlenl)
#endif /* !__local___localdep_rawmemxlenl_defined */
#endif /* !__local_rawmemxlenl_defined */
