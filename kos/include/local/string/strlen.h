/* HASH CRC-32:0x9d55642c */
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
#ifndef __local_strlen_defined
#define __local_strlen_defined 1
#include <__crt.h>
/* Dependency: "strend" from "string" */
#ifndef ____localdep_strend_defined
#define ____localdep_strend_defined 1
#ifdef __CRT_HAVE_strend
/* Same as `STR + strlen(STR)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strend,(char const *__restrict __string),strend,(__string))
#else /* LIBC: strend */
#include <local/string/strend.h>
/* Same as `STR + strlen(STR)' */
#define __localdep_strend (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strend))
#endif /* strend... */
#endif /* !____localdep_strend_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__LOCAL_LIBC(strlen) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strlen))(char const *__restrict __string) {
#line 256 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)(__localdep_strend(__string) - __string);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_strlen_defined */
