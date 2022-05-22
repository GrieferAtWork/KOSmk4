/* HASH CRC-32:0xe5497a02 */
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
#ifndef __local_nss_checkfieldlist_defined
#define __local_nss_checkfieldlist_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strpbrk_defined
#define __local___localdep_strpbrk_defined
#if __has_builtin(__builtin_strpbrk) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strpbrk)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),char *,__NOTHROW_NCX,__localdep_strpbrk,(char const *__haystack, char const *__accept),strpbrk,{ return __builtin_strpbrk(__haystack, __accept); })
#elif defined(__CRT_HAVE_strpbrk)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),char *,__NOTHROW_NCX,__localdep_strpbrk,(char const *__haystack, char const *__accept),strpbrk,(__haystack,__accept))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strpbrk.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strpbrk __LIBC_LOCAL_NAME(strpbrk)
#endif /* !... */
#endif /* !__local___localdep_strpbrk_defined */
__LOCAL_LIBC(nss_checkfieldlist) __ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __BOOL
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(nss_checkfieldlist))(char *const *__list) {
	if (!__list)
		return 1;
	for (; *__list; ++__list) {
		char const *__item = *__list;
		if ((__NAMESPACE_LOCAL_SYM __localdep_strpbrk)(__item, ":,\n"))
			return 0;
	}
	return 1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_nss_checkfieldlist_defined
#define __local___localdep_nss_checkfieldlist_defined
#define __localdep_nss_checkfieldlist __LIBC_LOCAL_NAME(nss_checkfieldlist)
#endif /* !__local___localdep_nss_checkfieldlist_defined */
#endif /* !__local_nss_checkfieldlist_defined */
