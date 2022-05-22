/* HASH CRC-32:0x8270b629 */
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
#ifndef __local_mbstoc32s_defined
#define __local_mbstoc32s_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mbsrtoc32_defined
#define __local___localdep_mbsrtoc32_defined
#if defined(__CRT_HAVE_mbsrtowcs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <bits/crt/mbstate.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_RW(2) __ATTR_ACCESS_RW_OPT(4) __ATTR_ACCESS_WR_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbsrtoc32,(__CHAR32_TYPE__ *__restrict __dst, char const **__restrict __psrc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs),mbsrtowcs,(__dst,__psrc,__dstlen,__mbs))
#elif defined(__CRT_HAVE_KOS$mbsrtowcs)
__NAMESPACE_LOCAL_END
#include <bits/crt/mbstate.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_ACCESS_RW(2) __ATTR_ACCESS_RW_OPT(4) __ATTR_ACCESS_WR_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbsrtoc32,(__CHAR32_TYPE__ *__restrict __dst, char const **__restrict __psrc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs),mbsrtowcs,(__dst,__psrc,__dstlen,__mbs))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/mbsrtowcs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mbsrtoc32 __NAMESPACE_LOCAL_TYPEHAX(__SIZE_TYPE__(__LIBKCALL*)(__CHAR32_TYPE__ *__restrict,char const **__restrict,__SIZE_TYPE__,struct __mbstate *),__SIZE_TYPE__(__LIBKCALL&)(__CHAR32_TYPE__ *__restrict,char const **__restrict,__SIZE_TYPE__,struct __mbstate *),mbsrtowcs)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.wchar/mbsrtoc32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mbsrtoc32 __LIBC_LOCAL_NAME(mbsrtoc32)
#endif /* !... */
#endif /* !__local___localdep_mbsrtoc32_defined */
__LOCAL_LIBC(mbstoc32s) __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WRS(1, 3) __SIZE_TYPE__
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(mbstoc32s))(__CHAR32_TYPE__ *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __dstlen) {
	return (__NAMESPACE_LOCAL_SYM __localdep_mbsrtoc32)(__dst, (char const **)&__src, __dstlen, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mbstoc32s_defined
#define __local___localdep_mbstoc32s_defined
#define __localdep_mbstoc32s __LIBC_LOCAL_NAME(mbstoc32s)
#endif /* !__local___localdep_mbstoc32s_defined */
#endif /* !__local_mbstoc32s_defined */
