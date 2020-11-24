/* HASH CRC-32:0x6978581 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_utimes64_defined
#define __local_utimes64_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_utimes
#include <bits/os/timeval.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: utimes32 from sys.time */
#ifndef __local___localdep_utimes32_defined
#define __local___localdep_utimes32_defined 1
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_utimes32,(char const *__file, struct __timeval32 const __tvp[2]),utimes,(__file,__tvp))
#endif /* !__local___localdep_utimes32_defined */
__LOCAL_LIBC(utimes64) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(utimes64))(char const *__file, struct __timeval64 const __tvp[2]) {
	struct __timeval32 __tv32[2];
	if (!__tvp)
		return __localdep_utimes32(__file, __NULLPTR);
	__tv32[0].tv_sec  = (__time32_t)__tvp[0].tv_sec;
	__tv32[0].tv_usec = __tvp[0].tv_usec;
	__tv32[1].tv_sec  = (__time32_t)__tvp[1].tv_sec;
	__tv32[1].tv_usec = __tvp[1].tv_usec;
	return __localdep_utimes32(__file, __tv32);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_utimes64_defined
#define __local___localdep_utimes64_defined 1
#define __localdep_utimes64 __LIBC_LOCAL_NAME(utimes64)
#endif /* !__local___localdep_utimes64_defined */
#else /* __CRT_HAVE_utimes */
#undef __local_utimes64_defined
#endif /* !__CRT_HAVE_utimes */
#endif /* !__local_utimes64_defined */
