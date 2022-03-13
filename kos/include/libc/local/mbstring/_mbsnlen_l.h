/* HASH CRC-32:0xf806f2c9 */
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
#ifndef __local__mbsnlen_l_defined
#define __local__mbsnlen_l_defined
#include <__crt.h>
#ifdef __CRT_HAVE__ismbblead_l
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__ismbblead_l_defined
#define __local___localdep__ismbblead_l_defined
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep__ismbblead_l,(unsigned int __ch, __locale_t __locale),_ismbblead_l,(__ch,__locale))
#endif /* !__local___localdep__ismbblead_l_defined */
__LOCAL_LIBC(_mbsnlen_l) __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbsnlen_l))(unsigned char const *__str, __SIZE_TYPE__ __max_bytes, __locale_t __locale) {
	__SIZE_TYPE__ __result;
	for (__result = 0; __max_bytes; ++__result) {
		__UINT16_TYPE__ __ch = *__str++;
		--__max_bytes;
		if ((__NAMESPACE_LOCAL_SYM __localdep__ismbblead_l)(__ch, __locale)) {
			if (!__max_bytes)
				break;
			__ch = *__str ? (__ch << 8) | *__str++ : 0;
			--__max_bytes;
		}
		if (__ch == 0)
			break;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mbsnlen_l_defined
#define __local___localdep__mbsnlen_l_defined
#define __localdep__mbsnlen_l __LIBC_LOCAL_NAME(_mbsnlen_l)
#endif /* !__local___localdep__mbsnlen_l_defined */
#else /* __CRT_HAVE__ismbblead_l */
#undef __local__mbsnlen_l_defined
#endif /* !__CRT_HAVE__ismbblead_l */
#endif /* !__local__mbsnlen_l_defined */
