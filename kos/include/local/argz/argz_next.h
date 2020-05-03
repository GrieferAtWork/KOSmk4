/* HASH CRC-32:0x8a1639d6 */
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
#ifndef __local_argz_next_defined
#define __local_argz_next_defined 1
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
/* Returns the next entry in ARGZ & ARGZ_LEN after ENTRY, or NULL if there
 * are no more. If entry is NULL, then the first entry is returned. This
 * behavior allows two convenient iteration styles:
 * >> char *entry = NULL;
 * >> while ((entry = argz_next(argz, argz_len, entry)) != NULL)
 * >>     ...;
 * or
 * >> char *entry;
 * >> for (entry = NULL; entry; entry = argz_next(argz, argz_len, entry))
 * >>     ...; */
__LOCAL_LIBC(argz_next) __ATTR_PURE __ATTR_WUNUSED char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(argz_next))(char const *__restrict __argz,
                                                       __SIZE_TYPE__ __argz_len,
                                                       char const *__restrict __entry) {
#line 553 "kos/src/libc/magic/argz.c"
	char const *__argz_end;
	if (!__entry)
		return __argz_len ? (char *)__argz : __NULLPTR;
	__argz_end = __argz + __argz_len;
	if (__entry < __argz_end)
		__entry = __localdep_strend(__entry) + 1;
	if (__entry >= __argz_end)
		return __NULLPTR;
	return (char *)__entry;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_argz_next_defined */
