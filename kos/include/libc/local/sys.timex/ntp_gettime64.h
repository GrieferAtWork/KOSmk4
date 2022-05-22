/* HASH CRC-32:0x811df0 */
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
#ifndef __local_ntp_gettime64_defined
#define __local_ntp_gettime64_defined
#include <__crt.h>
#ifdef __CRT_HAVE_ntp_gettimex
#include <bits/crt/ntptimeval.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_ntp_gettime32_defined
#define __local___localdep_ntp_gettime32_defined
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,__localdep_ntp_gettime32,(struct __ntptimeval32 *__restrict __ntv),ntp_gettimex,(__ntv))
#endif /* !__local___localdep_ntp_gettime32_defined */
__LOCAL_LIBC(ntp_gettime64) __ATTR_OUT(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ntp_gettime64))(struct __ntptimeval64 *__restrict __ntv) {
	struct __ntptimeval32 __ntv32;
	int __result = (__NAMESPACE_LOCAL_SYM __localdep_ntp_gettime32)(&__ntv32);
	if __likely(__result == 0) {
		__ntv->time.tv_sec       = (__time64_t)__ntv32.time.tv_sec;
		__ntv->time.tv_usec      = __ntv32.time.tv_usec;
		__ntv->maxerror          = __ntv32.maxerror;
		__ntv->esterror          = __ntv32.esterror;
		__ntv->tai               = __ntv32.tai;
		__ntv->__glibc_reserved1 = __ntv32.__glibc_reserved1;
		__ntv->__glibc_reserved2 = __ntv32.__glibc_reserved2;
		__ntv->__glibc_reserved3 = __ntv32.__glibc_reserved3;
		__ntv->__glibc_reserved4 = __ntv32.__glibc_reserved4;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ntp_gettime64_defined
#define __local___localdep_ntp_gettime64_defined
#define __localdep_ntp_gettime64 __LIBC_LOCAL_NAME(ntp_gettime64)
#endif /* !__local___localdep_ntp_gettime64_defined */
#else /* __CRT_HAVE_ntp_gettimex */
#undef __local_ntp_gettime64_defined
#endif /* !__CRT_HAVE_ntp_gettimex */
#endif /* !__local_ntp_gettime64_defined */
