/* HASH CRC-32:0xbbf8c536 */
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
#ifndef __local_mbsrtoc16_defined
#define __local_mbsrtoc16_defined
#include <__crt.h>
#include <bits/crt/mbstate.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mbsnrtoc16_defined
#define __local___localdep_mbsnrtoc16_defined
#if defined(__CRT_HAVE_mbsnrtowcs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT(2) __ATTR_INOUT_OPT(5) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbsnrtoc16,(__CHAR16_TYPE__ *__restrict __dst, char const **__restrict __psrc, __SIZE_TYPE__ __nmc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs),mbsnrtowcs,(__dst,__psrc,__nmc,__dstlen,__mbs))
#elif defined(__CRT_HAVE_DOS$mbsnrtowcs)
__CREDIRECT_DOS(__ATTR_INOUT(2) __ATTR_INOUT_OPT(5) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbsnrtoc16,(__CHAR16_TYPE__ *__restrict __dst, char const **__restrict __psrc, __SIZE_TYPE__ __nmc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs),mbsnrtowcs,(__dst,__psrc,__nmc,__dstlen,__mbs))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/mbsnrtowcs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mbsnrtoc16 __NAMESPACE_LOCAL_TYPEHAX(__SIZE_TYPE__(__LIBDCALL*)(__CHAR16_TYPE__ *__restrict,char const **__restrict,__SIZE_TYPE__,__SIZE_TYPE__,struct __mbstate *),__SIZE_TYPE__(__LIBDCALL&)(__CHAR16_TYPE__ *__restrict,char const **__restrict,__SIZE_TYPE__,__SIZE_TYPE__,struct __mbstate *),mbsnrtowcs)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.wchar/mbsnrtoc16.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mbsnrtoc16 __LIBC_LOCAL_NAME(mbsnrtoc16)
#endif /* !... */
#endif /* !__local___localdep_mbsnrtoc16_defined */
__LOCAL_LIBC(mbsrtoc16) __ATTR_INOUT(2) __ATTR_INOUT_OPT(4) __ATTR_OUT_OPT(1) __SIZE_TYPE__
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(mbsrtoc16))(__CHAR16_TYPE__ *__restrict __dst, char const **__restrict __psrc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs) {
	return (__NAMESPACE_LOCAL_SYM __localdep_mbsnrtoc16)(__dst, __psrc, (__SIZE_TYPE__)-1, __dstlen, __mbs);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mbsrtoc16_defined
#define __local___localdep_mbsrtoc16_defined
#define __localdep_mbsrtoc16 __LIBC_LOCAL_NAME(mbsrtoc16)
#endif /* !__local___localdep_mbsrtoc16_defined */
#endif /* !__local_mbsrtoc16_defined */
