/* HASH CRC-32:0xc7f4331b */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_iswgraph_defined
#define __local_iswgraph_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_isgraph_defined
#define __local___localdep_isgraph_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_isgraph) && defined(__CRT_HAVE_isgraph)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isgraph,(int __ch),isgraph,{ return __crt_isgraph(__ch); })
#elif defined(__crt_isgraph)
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_isgraph)(int __ch) { return __crt_isgraph(__ch); }
#elif __has_builtin(__builtin_isgraph) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isgraph)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isgraph,(int __ch),isgraph,{ return __builtin_isgraph(__ch); })
#elif defined(__CRT_HAVE_isgraph)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isgraph,(int __ch),isgraph,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/isgraph.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isgraph __LIBC_LOCAL_NAME(isgraph)
#endif /* !... */
#endif /* !__local___localdep_isgraph_defined */
#ifndef __local___localdep_wctob_defined
#define __local___localdep_wctob_defined
#ifdef __CRT_HAVE_wctob
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_wctob,(__WINT_TYPE__ __ch),wctob,(__ch))
#else /* __CRT_HAVE_wctob */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wctob.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wctob __LIBC_LOCAL_NAME(wctob)
#endif /* !__CRT_HAVE_wctob */
#endif /* !__local___localdep_wctob_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(iswgraph) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(iswgraph))(__WINT_TYPE__ __wc) {
#ifdef __crt_iswgraph
	return __crt_iswgraph(__wc);
#else /* __crt_iswgraph */
	return (__NAMESPACE_LOCAL_SYM __localdep_isgraph)((__NAMESPACE_LOCAL_SYM __localdep_wctob)(__wc));
#endif /* !__crt_iswgraph */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_iswgraph_defined
#define __local___localdep_iswgraph_defined
#define __localdep_iswgraph __LIBC_LOCAL_NAME(iswgraph)
#endif /* !__local___localdep_iswgraph_defined */
#endif /* !__local_iswgraph_defined */
