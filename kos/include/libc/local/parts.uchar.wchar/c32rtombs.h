/* HASH CRC-32:0x2940bde1 */
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
#ifndef __local_c32rtombs_defined
#define __local_c32rtombs_defined
#include <__crt.h>
#include <bits/crt/mbstate.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c32nrtombs_defined
#define __local___localdep_c32nrtombs_defined
#if defined(__CRT_HAVE_wcsnrtombs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32nrtombs,(char *__dst, __CHAR32_TYPE__ const **__restrict __psrc, __SIZE_TYPE__ __nwc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs),wcsnrtombs,(__dst,__psrc,__nwc,__dstlen,__mbs))
#elif defined(__CRT_HAVE_KOS$wcsnrtombs)
__CREDIRECT_KOS(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32nrtombs,(char *__dst, __CHAR32_TYPE__ const **__restrict __psrc, __SIZE_TYPE__ __nwc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs),wcsnrtombs,(__dst,__psrc,__nwc,__dstlen,__mbs))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsnrtombs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32nrtombs __NAMESPACE_LOCAL_TYPEHAX(__SIZE_TYPE__(__LIBKCALL*)(char *,__CHAR32_TYPE__ const **__restrict,__SIZE_TYPE__,__SIZE_TYPE__,struct __mbstate *),__SIZE_TYPE__(__LIBKCALL&)(char *,__CHAR32_TYPE__ const **__restrict,__SIZE_TYPE__,__SIZE_TYPE__,struct __mbstate *),wcsnrtombs)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.wchar/c32nrtombs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32nrtombs __LIBC_LOCAL_NAME(c32nrtombs)
#endif /* !... */
#endif /* !__local___localdep_c32nrtombs_defined */
__LOCAL_LIBC(c32rtombs) __ATTR_NONNULL((1, 2)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32rtombs))(char *__dst, __CHAR32_TYPE__ const **__restrict __psrc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs) {
	return (__NAMESPACE_LOCAL_SYM __localdep_c32nrtombs)(__dst, __psrc, (__SIZE_TYPE__)-1, __dstlen, __mbs);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32rtombs_defined
#define __local___localdep_c32rtombs_defined
#define __localdep_c32rtombs __LIBC_LOCAL_NAME(c32rtombs)
#endif /* !__local___localdep_c32rtombs_defined */
#endif /* !__local_c32rtombs_defined */
