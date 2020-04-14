/* HASH CRC-32:0x4077baae */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_strrev_defined
#define __local_strrev_defined 1
/* Dependency: "memrev" from "string" */
#ifndef ____localdep_memrev_defined
#define ____localdep_memrev_defined 1
#ifdef __CRT_HAVE_memrev
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memrev,(void *__restrict __base, __SIZE_TYPE__ __n_bytes),memrev,(__base,__n_bytes))
#else /* LIBC: memrev */
#include <local/string/memrev.h>
#define __localdep_memrev (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrev))
#endif /* memrev... */
#endif /* !____localdep_memrev_defined */

/* Dependency: "strlen" from "string" */
#ifndef ____localdep_strlen_defined
#define ____localdep_strlen_defined 1
#ifdef __CRT_HAVE_strlen
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __string),strlen,(__string))
#else /* LIBC: strlen */
#include <local/string/strlen.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_strlen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlen))
#endif /* strlen... */
#endif /* !____localdep_strlen_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strrev) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strrev))(char *__restrict __str) {
#line 4906 "kos/src/libc/magic/string.c"
	return (char *)__localdep_memrev(__str, __localdep_strlen(__str));
}
__NAMESPACE_LOCAL_END
#endif /* !__local_strrev_defined */
