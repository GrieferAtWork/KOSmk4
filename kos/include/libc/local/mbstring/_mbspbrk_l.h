/* HASH CRC-32:0x1275a2ea */
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
#ifndef __local__mbspbrk_l_defined
#define __local__mbspbrk_l_defined
#include <__crt.h>
#ifdef __CRT_HAVE__ismbblead_l
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__ismbblead_l_defined
#define __local___localdep__ismbblead_l_defined
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep__ismbblead_l,(unsigned int __ch, __locale_t __locale),_ismbblead_l,(__ch,__locale))
#endif /* !__local___localdep__ismbblead_l_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_mbspbrk_l) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) unsigned char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbspbrk_l))(unsigned char const *__haystack, unsigned char const *__accept, __locale_t __locale) {
	__UINT16_TYPE__ __haych, __ch;
	for (;;) {
		unsigned char const *__temp;
		unsigned char const *__ned_iter;
		__temp  = __haystack;
		__haych = *__haystack++;
		if ((__NAMESPACE_LOCAL_SYM __localdep__ismbblead_l)(__haych, __locale))
			__haych = *__haystack ? (__haych << 8) | *__haystack++ : 0;
		if (__haych == 0)
			break;
		for (__ned_iter = __accept;;) {
			__ch = *__ned_iter++;
			if ((__NAMESPACE_LOCAL_SYM __localdep__ismbblead_l)(__ch, __locale))
				__ch = *__ned_iter ? (__ch << 8) | *__ned_iter++ : 0;
			if (__ch == 0)
				break;
			if (__haych == __ch)
				return (unsigned char *)__temp;
		}
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mbspbrk_l_defined
#define __local___localdep__mbspbrk_l_defined
#define __localdep__mbspbrk_l __LIBC_LOCAL_NAME(_mbspbrk_l)
#endif /* !__local___localdep__mbspbrk_l_defined */
#else /* __CRT_HAVE__ismbblead_l */
#undef __local__mbspbrk_l_defined
#endif /* !__CRT_HAVE__ismbblead_l */
#endif /* !__local__mbspbrk_l_defined */
