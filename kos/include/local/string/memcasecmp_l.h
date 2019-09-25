/* HASH CRC-32:0x21305d01 */
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
#ifndef __local_memcasecmp_l_defined
#define __local_memcasecmp_l_defined 1
/* Dependency: "memcasecmp" from "string" */
#ifndef ____localdep_memcasecmp_defined
#define ____localdep_memcasecmp_defined 1
#if defined(__CRT_HAVE_memcasecmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcasecmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_memicmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memicmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE__memicmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),_memicmp,(__s1,__s2,__n_bytes))
#else /* LIBC: memcasecmp */
#include <local/string/memcasecmp.h>
#define __localdep_memcasecmp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasecmp))
#endif /* memcasecmp... */
#endif /* !____localdep_memcasecmp_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(memcasecmp_l) __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memcasecmp_l))(void const *__s1,
                                                          void const *__s2,
                                                          __SIZE_TYPE__ __n_bytes,
                                                          __locale_t __locale) {
#line 2387 "kos/src/libc/magic/string.c"
	(void)__locale;
	return __localdep_memcasecmp(__s1, __s2, __n_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_memcasecmp_l_defined */
