/* HASH CRC-32:0xadde16cb */
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
#ifndef __local_mbsrtoc32_defined
#define __local_mbsrtoc32_defined
#include <__crt.h>
#include <bits/crt/mbstate.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mbsnrtoc32_defined
#define __local___localdep_mbsnrtoc32_defined
#if defined(__CRT_HAVE_mbsnrtowcs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_INOUT(2) __ATTR_INOUT_OPT(5) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbsnrtoc32,(__CHAR32_TYPE__ *__restrict __dst, char const **__restrict __psrc, __SIZE_TYPE__ __nmc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs),mbsnrtowcs,(__dst,__psrc,__nmc,__dstlen,__mbs))
#elif defined(__CRT_HAVE_KOS$mbsnrtowcs)
__CREDIRECT_KOS(__ATTR_INOUT(2) __ATTR_INOUT_OPT(5) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbsnrtoc32,(__CHAR32_TYPE__ *__restrict __dst, char const **__restrict __psrc, __SIZE_TYPE__ __nmc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs),mbsnrtowcs,(__dst,__psrc,__nmc,__dstlen,__mbs))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/mbsnrtowcs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mbsnrtoc32 __NAMESPACE_LOCAL_TYPEHAX(__SIZE_TYPE__(__LIBKCALL*)(__CHAR32_TYPE__ *__restrict,char const **__restrict,__SIZE_TYPE__,__SIZE_TYPE__,struct __mbstate *),__SIZE_TYPE__(__LIBKCALL&)(__CHAR32_TYPE__ *__restrict,char const **__restrict,__SIZE_TYPE__,__SIZE_TYPE__,struct __mbstate *),mbsnrtowcs)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.wchar/mbsnrtoc32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mbsnrtoc32 __LIBC_LOCAL_NAME(mbsnrtoc32)
#endif /* !... */
#endif /* !__local___localdep_mbsnrtoc32_defined */
__LOCAL_LIBC(mbsrtoc32) __ATTR_INOUT(2) __ATTR_INOUT_OPT(4) __ATTR_OUT_OPT(1) __SIZE_TYPE__
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(mbsrtoc32))(__CHAR32_TYPE__ *__restrict __dst, char const **__restrict __psrc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs) {
	return (__NAMESPACE_LOCAL_SYM __localdep_mbsnrtoc32)(__dst, __psrc, (__SIZE_TYPE__)-1, __dstlen, __mbs);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mbsrtoc32_defined
#define __local___localdep_mbsrtoc32_defined
#define __localdep_mbsrtoc32 __LIBC_LOCAL_NAME(mbsrtoc32)
#endif /* !__local___localdep_mbsrtoc32_defined */
#endif /* !__local_mbsrtoc32_defined */
