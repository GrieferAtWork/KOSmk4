/* HASH CRC-32:0xf337ec90 */
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
#ifndef __local__mbsncmp_l_defined
#define __local__mbsncmp_l_defined
#include <__crt.h>
#ifdef __CRT_HAVE__ismbblead_l
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__ismbblead_l_defined
#define __local___localdep__ismbblead_l_defined
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep__ismbblead_l,(unsigned int __ch, __locale_t __locale),_ismbblead_l,(__ch,__locale))
#endif /* !__local___localdep__ismbblead_l_defined */
__LOCAL_LIBC(_mbsncmp_l) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbsncmp_l))(unsigned char const *__lhs, unsigned char const *__rhs, __SIZE_TYPE__ __max_chars, __locale_t __locale) {
	for (; __max_chars; --__max_chars) {
		__UINT16_TYPE__ __lc = 0, __rc = 0;
		__lc = *__lhs++;
		if ((__NAMESPACE_LOCAL_SYM __localdep__ismbblead_l)(__lc, __locale))
			__lc = *__lhs ? (__lc << 8) | *__lhs++ : 0;
		__rc = *__rhs++;
		if ((__NAMESPACE_LOCAL_SYM __localdep__ismbblead_l)(__rc, __locale))
			__rc = *__rhs ? (__rc << 8) | *__rhs++ : 0;
		if (__lc != __rc)
			return (int)__lc - (int)__rc;
		if (__lc == 0)
			break;
	}
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mbsncmp_l_defined
#define __local___localdep__mbsncmp_l_defined
#define __localdep__mbsncmp_l __LIBC_LOCAL_NAME(_mbsncmp_l)
#endif /* !__local___localdep__mbsncmp_l_defined */
#else /* __CRT_HAVE__ismbblead_l */
#undef __local__mbsncmp_l_defined
#endif /* !__CRT_HAVE__ismbblead_l */
#endif /* !__local__mbsncmp_l_defined */
