/* HASH CRC-32:0x411697fb */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_wmemcasecmp_l_defined
#define __local_wmemcasecmp_l_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_wmemcasecmp_defined
#define __local___localdep_wmemcasecmp_defined
#ifdef __CRT_HAVE_wmemcasecmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wmemcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars),wmemcasecmp,(__s1,__s2,__num_chars))
#else /* __CRT_HAVE_wmemcasecmp */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wmemcasecmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wmemcasecmp __LIBC_LOCAL_NAME(wmemcasecmp)
#endif /* !__CRT_HAVE_wmemcasecmp */
#endif /* !__local___localdep_wmemcasecmp_defined */
__LOCAL_LIBC(wmemcasecmp_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wmemcasecmp_l))(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars, __locale_t __locale) {
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep_wmemcasecmp)(__s1, __s2, __num_chars);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wmemcasecmp_l_defined
#define __local___localdep_wmemcasecmp_l_defined
#define __localdep_wmemcasecmp_l __LIBC_LOCAL_NAME(wmemcasecmp_l)
#endif /* !__local___localdep_wmemcasecmp_l_defined */
#endif /* !__local_wmemcasecmp_l_defined */
