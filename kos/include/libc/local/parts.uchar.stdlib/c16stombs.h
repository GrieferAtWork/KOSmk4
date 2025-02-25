/* HASH CRC-32:0x34d7f680 */
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
#ifndef __local_c16stombs_defined
#define __local_c16stombs_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c16rtombs_defined
#define __local___localdep_c16rtombs_defined
#if defined(__CRT_HAVE_wcsrtombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__NAMESPACE_LOCAL_END
#include <bits/crt/mbstate.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(2) __ATTR_INOUT_OPT(4) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16rtombs,(char *__dst, __CHAR16_TYPE__ const **__restrict __psrc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs),wcsrtombs,(__dst,__psrc,__dstlen,__mbs))
#elif defined(__CRT_HAVE_DOS$wcsrtombs)
__NAMESPACE_LOCAL_END
#include <bits/crt/mbstate.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_DOS(__ATTR_INOUT(2) __ATTR_INOUT_OPT(4) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16rtombs,(char *__dst, __CHAR16_TYPE__ const **__restrict __psrc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs),wcsrtombs,(__dst,__psrc,__dstlen,__mbs))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsrtombs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16rtombs __NAMESPACE_LOCAL_TYPEHAX(__SIZE_TYPE__(__LIBDCALL*)(char *,__CHAR16_TYPE__ const **__restrict,__SIZE_TYPE__,struct __mbstate *),__SIZE_TYPE__(__LIBDCALL&)(char *,__CHAR16_TYPE__ const **__restrict,__SIZE_TYPE__,struct __mbstate *),wcsrtombs)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.wchar/c16rtombs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16rtombs __LIBC_LOCAL_NAME(c16rtombs)
#endif /* !... */
#endif /* !__local___localdep_c16rtombs_defined */
__LOCAL_LIBC(c16stombs) __ATTR_IN(2) __ATTR_OUTS(1, 3) __SIZE_TYPE__
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16stombs))(char *__restrict __dst, __CHAR16_TYPE__ const *__restrict __src, __SIZE_TYPE__ __dstlen) {
	return (__NAMESPACE_LOCAL_SYM __localdep_c16rtombs)(__dst, (__CHAR16_TYPE__ const **)&__src, __dstlen, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16stombs_defined
#define __local___localdep_c16stombs_defined
#define __localdep_c16stombs __LIBC_LOCAL_NAME(c16stombs)
#endif /* !__local___localdep_c16stombs_defined */
#endif /* !__local_c16stombs_defined */
