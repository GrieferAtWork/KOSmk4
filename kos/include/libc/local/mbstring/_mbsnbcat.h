/* HASH CRC-32:0x652daa80 */
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
#ifndef __local__mbsnbcat_defined
#define __local__mbsnbcat_defined
#include <__crt.h>
#if defined(__CRT_HAVE__mbsnbcat_l) || defined(__CRT_HAVE__ismbblead_l)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__mbsnbcat_l_defined
#define __local___localdep__mbsnbcat_l_defined
#ifdef __CRT_HAVE__mbsnbcat_l
__CREDIRECT(__ATTR_NONNULL((1, 2)),unsigned char *,__NOTHROW_NCX,__localdep__mbsnbcat_l,(unsigned char *__buf, unsigned char const *__src, __SIZE_TYPE__ __max_bytes, __locale_t __locale),_mbsnbcat_l,(__buf,__src,__max_bytes,__locale))
#elif defined(__CRT_HAVE__ismbblead_l)
__NAMESPACE_LOCAL_END
#include <libc/local/mbstring/_mbsnbcat_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__mbsnbcat_l __LIBC_LOCAL_NAME(_mbsnbcat_l)
#else /* ... */
#undef __local___localdep__mbsnbcat_l_defined
#endif /* !... */
#endif /* !__local___localdep__mbsnbcat_l_defined */
__LOCAL_LIBC(_mbsnbcat) __ATTR_NONNULL((1, 2)) unsigned char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbsnbcat))(unsigned char *__buf, unsigned char const *__src, __SIZE_TYPE__ __max_bytes) {
	return (__NAMESPACE_LOCAL_SYM __localdep__mbsnbcat_l)(__buf, __src, __max_bytes, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mbsnbcat_defined
#define __local___localdep__mbsnbcat_defined
#define __localdep__mbsnbcat __LIBC_LOCAL_NAME(_mbsnbcat)
#endif /* !__local___localdep__mbsnbcat_defined */
#else /* __CRT_HAVE__mbsnbcat_l || __CRT_HAVE__ismbblead_l */
#undef __local__mbsnbcat_defined
#endif /* !__CRT_HAVE__mbsnbcat_l && !__CRT_HAVE__ismbblead_l */
#endif /* !__local__mbsnbcat_defined */
