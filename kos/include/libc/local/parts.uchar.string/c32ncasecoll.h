/* HASH CRC-32:0x128385e */
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
#ifndef __local_c32ncasecoll_defined
#define __local_c32ncasecoll_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c32ncasecmp_defined
#define __local___localdep_c32ncasecmp_defined
#if defined(__CRT_HAVE_wcsncasecmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c32ncasecmp,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsncasecmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c32ncasecmp,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c32ncasecmp,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_KOS$_wcsnicmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c32ncasecmp,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsncasecmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32ncasecmp __NAMESPACE_LOCAL_TYPEHAX(int(__LIBKCALL*)(__CHAR32_TYPE__ const *,__CHAR32_TYPE__ const *,__SIZE_TYPE__),int(__LIBKCALL&)(__CHAR32_TYPE__ const *,__CHAR32_TYPE__ const *,__SIZE_TYPE__),wcsncasecmp)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c32ncasecmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32ncasecmp __LIBC_LOCAL_NAME(c32ncasecmp)
#endif /* !... */
#endif /* !__local___localdep_c32ncasecmp_defined */
__LOCAL_LIBC(c32ncasecoll) __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32ncasecoll))(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen) {
	/* XXX: Implement properly? */
	return (__NAMESPACE_LOCAL_SYM __localdep_c32ncasecmp)(__s1, __s2, __maxlen);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32ncasecoll_defined
#define __local___localdep_c32ncasecoll_defined
#define __localdep_c32ncasecoll __LIBC_LOCAL_NAME(c32ncasecoll)
#endif /* !__local___localdep_c32ncasecoll_defined */
#endif /* !__local_c32ncasecoll_defined */
