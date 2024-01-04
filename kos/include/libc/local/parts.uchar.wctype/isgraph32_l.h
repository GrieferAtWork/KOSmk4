/* HASH CRC-32:0xeee669c3 */
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
#ifndef __local_isgraph32_l_defined
#define __local_isgraph32_l_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_isgraph32_defined
#define __local___localdep_isgraph32_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_iswgraph) && defined(__CRT_HAVE_iswgraph) && __SIZEOF_WCHAR_T__ == 4
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBKCALL,__localdep_isgraph32,(__WINT32_TYPE__ __wc),iswgraph,{ return __crt_iswgraph(__wc); })
#elif defined(__crt_iswgraph) && __SIZEOF_WCHAR_T__ == 4
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL __localdep_isgraph32)(__WINT32_TYPE__ __wc) { return __crt_iswgraph(__wc); }
#elif __has_builtin(__builtin_iswgraph) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswgraph) && __SIZEOF_WCHAR_T__ == 4
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBKCALL,__localdep_isgraph32,(__WINT32_TYPE__ __wc),iswgraph,{ return __builtin_iswgraph(__wc); })
#elif defined(__CRT_HAVE_iswgraph) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isgraph32,(__WINT32_TYPE__ __wc),iswgraph,(__wc))
#elif defined(__CRT_HAVE_KOS$iswgraph)
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isgraph32,(__WINT32_TYPE__ __wc),iswgraph,(__wc))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wctype/iswgraph.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isgraph32 __NAMESPACE_LOCAL_TYPEHAX(int(__LIBKCALL*)(__WINT32_TYPE__),int(__LIBKCALL&)(__WINT32_TYPE__),iswgraph)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.wctype/isgraph32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isgraph32 __LIBC_LOCAL_NAME(isgraph32)
#endif /* !... */
#endif /* !__local___localdep_isgraph32_defined */
__LOCAL_LIBC(isgraph32_l) __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(isgraph32_l))(__WINT32_TYPE__ __ch, __locale_t __locale) {
	__COMPILER_IMPURE();
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep_isgraph32)(__ch);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_isgraph32_l_defined
#define __local___localdep_isgraph32_l_defined
#define __localdep_isgraph32_l __LIBC_LOCAL_NAME(isgraph32_l)
#endif /* !__local___localdep_isgraph32_l_defined */
#endif /* !__local_isgraph32_l_defined */
