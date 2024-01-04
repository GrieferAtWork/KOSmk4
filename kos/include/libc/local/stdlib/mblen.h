/* HASH CRC-32:0x8400dbfa */
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
#ifndef __local_mblen_defined
#define __local_mblen_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mbrlen_defined
#define __local___localdep_mbrlen_defined
#ifdef __CRT_HAVE_mbrlen
__NAMESPACE_LOCAL_END
#include <bits/crt/mbstate.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT_OPT(3) __ATTR_IN_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbrlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),mbrlen,(__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE___mbrlen)
__NAMESPACE_LOCAL_END
#include <bits/crt/mbstate.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT_OPT(3) __ATTR_IN_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbrlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),__mbrlen,(__str,__maxlen,__mbs))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/mbrlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mbrlen __LIBC_LOCAL_NAME(mbrlen)
#endif /* !... */
#endif /* !__local___localdep_mbrlen_defined */
__LOCAL_LIBC(mblen) __ATTR_IN_OPT(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mblen))(char const *__str, __SIZE_TYPE__ __maxlen) {
	return (__NAMESPACE_LOCAL_SYM __localdep_mbrlen)(__str, __maxlen, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mblen_defined
#define __local___localdep_mblen_defined
#define __localdep_mblen __LIBC_LOCAL_NAME(mblen)
#endif /* !__local___localdep_mblen_defined */
#endif /* !__local_mblen_defined */
