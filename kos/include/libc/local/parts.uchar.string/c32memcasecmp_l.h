/* HASH CRC-32:0x67e30d3 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c32memcasecmp_l_defined
#define __local_c32memcasecmp_l_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c32memcasecmp_defined
#define __local___localdep_c32memcasecmp_defined
#if defined(__CRT_HAVE_wmemcasecmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c32memcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars),wmemcasecmp,(__s1,__s2,__num_chars))
#elif defined(__CRT_HAVE_KOS$wmemcasecmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c32memcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars),wmemcasecmp,(__s1,__s2,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wmemcasecmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32memcasecmp __NAMESPACE_LOCAL_TYPEHAX(int(__LIBKCALL*)(void const *,void const *,__SIZE_TYPE__),int(__LIBKCALL&)(void const *,void const *,__SIZE_TYPE__),wmemcasecmp)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c32memcasecmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32memcasecmp __LIBC_LOCAL_NAME(c32memcasecmp)
#endif /* !... */
#endif /* !__local___localdep_c32memcasecmp_defined */
__LOCAL_LIBC(c32memcasecmp_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32memcasecmp_l))(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars, __locale_t __locale) {
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep_c32memcasecmp)(__s1, __s2, __num_chars);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32memcasecmp_l_defined
#define __local___localdep_c32memcasecmp_l_defined
#define __localdep_c32memcasecmp_l __LIBC_LOCAL_NAME(c32memcasecmp_l)
#endif /* !__local___localdep_c32memcasecmp_l_defined */
#endif /* !__local_c32memcasecmp_l_defined */
