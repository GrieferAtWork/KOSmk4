/* HASH CRC-32:0xf27315cd */
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
#ifndef __local__mbslwr_l_defined
#define __local__mbslwr_l_defined
#include <__crt.h>
#if defined(__CRT_HAVE__ismbblead_l) && defined(__CRT_HAVE__mbctolower_l)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__ismbblead_l_defined
#define __local___localdep__ismbblead_l_defined
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep__ismbblead_l,(unsigned int __ch, __locale_t __locale),_ismbblead_l,(__ch,__locale))
#endif /* !__local___localdep__ismbblead_l_defined */
#ifndef __local___localdep__mbctolower_l_defined
#define __local___localdep__mbctolower_l_defined
__CREDIRECT(__ATTR_WUNUSED,unsigned int,__NOTHROW_NCX,__localdep__mbctolower_l,(unsigned int __ch, __locale_t __locale),_mbctolower_l,(__ch,__locale))
#endif /* !__local___localdep__mbctolower_l_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_mbslwr_l) __ATTR_RETNONNULL __ATTR_NONNULL((1)) unsigned char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbslwr_l))(unsigned char *__buf, __locale_t __locale) {
	unsigned char *__iter = __buf;
	for (;;) {
		__UINT16_TYPE__ __ch = *__iter;
		if (!__ch)
			break;
		if ((__NAMESPACE_LOCAL_SYM __localdep__ismbblead_l)(__ch, __locale)) {
			if __unlikely(!__iter[1])
				goto __do_1byte_lower;
			__ch      = (__ch << 8) | __iter[1];
			__ch      = (__NAMESPACE_LOCAL_SYM __localdep__mbctolower_l)(__ch, __locale);
			__iter[0] = (unsigned char)((__ch & 0xff00) >> 8);
			__iter[1] = (unsigned char)(__ch & 0xff);
			__iter += 2;
		} else {
__do_1byte_lower:
			__ch      = (__NAMESPACE_LOCAL_SYM __localdep__mbctolower_l)(__ch, __locale);
			__iter[0] = (unsigned char)(__ch & 0xff);
			++__iter;
		}
	}
	return __buf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mbslwr_l_defined
#define __local___localdep__mbslwr_l_defined
#define __localdep__mbslwr_l __LIBC_LOCAL_NAME(_mbslwr_l)
#endif /* !__local___localdep__mbslwr_l_defined */
#else /* __CRT_HAVE__ismbblead_l && __CRT_HAVE__mbctolower_l */
#undef __local__mbslwr_l_defined
#endif /* !__CRT_HAVE__ismbblead_l || !__CRT_HAVE__mbctolower_l */
#endif /* !__local__mbslwr_l_defined */
