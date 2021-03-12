/* HASH CRC-32:0x510082c6 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_strroff_defined
#define __local_strroff_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: strrchrnul from string */
#ifndef __local___localdep_strrchrnul_defined
#define __local___localdep_strrchrnul_defined 1
#ifdef __CRT_HAVE_strrchrnul
/* Same as `strrchr', but return `str - 1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strrchrnul,(char const *__restrict __haystack, int __needle),strrchrnul,(__haystack,__needle))
#else /* __CRT_HAVE_strrchrnul */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strrchrnul.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `strrchr', but return `str - 1', rather than `NULL' if `needle' wasn't found. */
#define __localdep_strrchrnul __LIBC_LOCAL_NAME(strrchrnul)
#endif /* !__CRT_HAVE_strrchrnul */
#endif /* !__local___localdep_strrchrnul_defined */
/* Same as `strrchrnul', but return the offset from `str', rather than the actual address */
__LOCAL_LIBC(strroff) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strroff))(char const *__restrict __haystack, int __needle) {
	return (__SIZE_TYPE__)(__localdep_strrchrnul(__haystack, __needle) - __haystack);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strroff_defined
#define __local___localdep_strroff_defined 1
#define __localdep_strroff __LIBC_LOCAL_NAME(strroff)
#endif /* !__local___localdep_strroff_defined */
#endif /* !__local_strroff_defined */
