/* HASH CRC-32:0x6945aed0 */
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
#ifndef __local_envz_entry_defined
#define __local_envz_entry_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: memcmp from string */
#ifndef __local___localdep_memcmp_defined
#define __local___localdep_memcmp_defined 1
#ifdef __CRT_HAVE_memcmp
/* >> memcmp(3)
 * Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_bcmp)
/* >> memcmp(3)
 * Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),bcmp,(__s1,__s2,__n_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcmp.h>
__NAMESPACE_LOCAL_BEGIN
/* >> memcmp(3)
 * Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
#define __localdep_memcmp __LIBC_LOCAL_NAME(memcmp)
#endif /* !... */
#endif /* !__local___localdep_memcmp_defined */
/* Dependency: strend from string */
#ifndef __local___localdep_strend_defined
#define __local___localdep_strend_defined 1
#ifdef __CRT_HAVE_strend
/* Same as `STR + strlen(STR)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strend,(char const *__restrict __string),strend,(__string))
#else /* __CRT_HAVE_strend */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strend.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `STR + strlen(STR)' */
#define __localdep_strend __LIBC_LOCAL_NAME(strend)
#endif /* !__CRT_HAVE_strend */
#endif /* !__local___localdep_strend_defined */
/* Dependency: stroff from string */
#ifndef __local___localdep_stroff_defined
#define __local___localdep_stroff_defined 1
#ifdef __CRT_HAVE_stroff
/* Same as `strchrnul', but return the offset from `STR', rather than the actual address */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_stroff,(char const *__restrict __haystack, int __needle),stroff,(__haystack,__needle))
#else /* __CRT_HAVE_stroff */
__NAMESPACE_LOCAL_END
#include <libc/local/string/stroff.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `strchrnul', but return the offset from `STR', rather than the actual address */
#define __localdep_stroff __LIBC_LOCAL_NAME(stroff)
#endif /* !__CRT_HAVE_stroff */
#endif /* !__local___localdep_stroff_defined */
/* Find and return the entry for `name' in `envz', or `NULL' if not found.
 * If `name' contains a `=' character, only characters leading up to this
 * position are actually compared! */
__LOCAL_LIBC(envz_entry) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((3)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(envz_entry))(char const *__restrict __envz, __SIZE_TYPE__ __envz_len, char const *__restrict __name) {
	__SIZE_TYPE__ __namelen;
	char *__envz_end = (char *)(__envz + __envz_len);
	__namelen = __localdep_stroff(__name, '=');
	while (__envz < __envz_end) {
		if (__localdep_memcmp(__envz, __name, __namelen) == 0 &&
		    (__envz[__namelen] == '\0' || __envz[__namelen] == '='))
			return (char *)__envz; /* Found it! */
		__envz = __localdep_strend(__envz) + 1;
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_envz_entry_defined
#define __local___localdep_envz_entry_defined 1
#define __localdep_envz_entry __LIBC_LOCAL_NAME(envz_entry)
#endif /* !__local___localdep_envz_entry_defined */
#endif /* !__local_envz_entry_defined */
