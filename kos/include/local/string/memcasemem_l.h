/* HASH CRC-32:0xb9be3bd6 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_memcasemem_l_defined
#define __local_memcasemem_l_defined 1
/* Dependency: "memcasecmp_l" from "string" */
#ifndef ____localdep_memcasecmp_l_defined
#define ____localdep_memcasecmp_l_defined 1
#if defined(__CRT_HAVE_memcasecmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcasecmp_l,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes, __locale_t __locale),memcasecmp_l,(__s1,__s2,__n_bytes,__locale))
#elif defined(__CRT_HAVE__memicmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcasecmp_l,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes, __locale_t __locale),_memicmp_l,(__s1,__s2,__n_bytes,__locale))
#else /* LIBC: memcasecmp_l */
#include <local/string/memcasecmp_l.h>
#define __localdep_memcasecmp_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasecmp_l))
#endif /* memcasecmp_l... */
#endif /* !____localdep_memcasecmp_l_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(memcasemem_l) __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memcasemem_l))(void const *__haystack,
                                                          __SIZE_TYPE__ __haystacklen,
                                                          void const *__needle,
                                                          __SIZE_TYPE__ __needlelen,
                                                          __locale_t __locale) {
#line 2366 "kos/src/libc/magic/string.c"
	__BYTE_TYPE__ *__iter = (__BYTE_TYPE__ *)__haystack;
	while (__haystacklen >= __needlelen) {
		if (__localdep_memcasecmp_l(__iter, __needle, __needlelen, __locale) == 0)
			return (void *)__iter;
		++__iter;
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_memcasemem_l_defined */
