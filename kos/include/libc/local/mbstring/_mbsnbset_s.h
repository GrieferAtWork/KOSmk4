/* HASH CRC-32:0xe28273e4 */
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
#ifndef __local__mbsnbset_s_defined
#define __local__mbsnbset_s_defined
#include <__crt.h>
#if defined(__CRT_HAVE__mbsnbset_s_l) || defined(__CRT_HAVE__mbsnbset_l) || defined(__CRT_HAVE__ismbblead_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <hybrid/typecore.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__mbsnbset_s_l_defined
#define __local___localdep__mbsnbset_s_l_defined
#ifdef __CRT_HAVE__mbsnbset_s_l
__CREDIRECT(__ATTR_INOUTS(1, 2),__errno_t,__NOTHROW_NCX,__localdep__mbsnbset_s_l,(unsigned char *__buf, __SIZE_TYPE__ __true_bufsize, unsigned int __ch, __SIZE_TYPE__ __max_bytes, __locale_t __locale),_mbsnbset_s_l,(__buf,__true_bufsize,__ch,__max_bytes,__locale))
#elif defined(__CRT_HAVE__mbsnbset_l) || defined(__CRT_HAVE__ismbblead_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
__NAMESPACE_LOCAL_END
#include <libc/local/mbstring/_mbsnbset_s_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__mbsnbset_s_l __LIBC_LOCAL_NAME(_mbsnbset_s_l)
#else /* ... */
#undef __local___localdep__mbsnbset_s_l_defined
#endif /* !... */
#endif /* !__local___localdep__mbsnbset_s_l_defined */
__LOCAL_LIBC(_mbsnbset_s) __ATTR_INOUTS(1, 4) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbsnbset_s))(unsigned char *__buf, __SIZE_TYPE__ __true_bufsize, unsigned int __ch, __SIZE_TYPE__ __max_bytes) {
	return (__NAMESPACE_LOCAL_SYM __localdep__mbsnbset_s_l)(__buf, __true_bufsize, __ch, __max_bytes, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mbsnbset_s_defined
#define __local___localdep__mbsnbset_s_defined
#define __localdep__mbsnbset_s __LIBC_LOCAL_NAME(_mbsnbset_s)
#endif /* !__local___localdep__mbsnbset_s_defined */
#else /* __CRT_HAVE__mbsnbset_s_l || __CRT_HAVE__mbsnbset_l || __CRT_HAVE__ismbblead_l || __CRT_HAVE__mbctype || __CRT_HAVE___p__mbctype */
#undef __local__mbsnbset_s_defined
#endif /* !__CRT_HAVE__mbsnbset_s_l && !__CRT_HAVE__mbsnbset_l && !__CRT_HAVE__ismbblead_l && !__CRT_HAVE__mbctype && !__CRT_HAVE___p__mbctype */
#endif /* !__local__mbsnbset_s_defined */
