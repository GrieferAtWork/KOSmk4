/* HASH CRC-32:0x289806fd */
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
#ifndef __local_gai_suspend64_defined
#define __local_gai_suspend64_defined
#include <__crt.h>
#ifdef __CRT_HAVE_gai_suspend
#include <bits/crt/gaicb.h>
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_gai_suspend32_defined
#define __local___localdep_gai_suspend32_defined
__CREDIRECT(,int,__NOTHROW_RPC,__localdep_gai_suspend32,(struct gaicb const *const __list[], int __ent, struct __timespec32 const *__timeout),gai_suspend,(__list,__ent,__timeout))
#endif /* !__local___localdep_gai_suspend32_defined */
__LOCAL_LIBC(gai_suspend64) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(gai_suspend64))(struct gaicb const *const __list[], int __ent, struct __timespec64 const *__timeout) {
	struct __timespec32 __tmo32;
	if (!__timeout)
		return (__NAMESPACE_LOCAL_SYM __localdep_gai_suspend32)(__list, __ent, __NULLPTR);
	__tmo32.tv_sec  = (__time32_t)__timeout->tv_sec;
	__tmo32.tv_nsec = __timeout->tv_nsec;
	return (__NAMESPACE_LOCAL_SYM __localdep_gai_suspend32)(__list, __ent, &__tmo32);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_gai_suspend64_defined
#define __local___localdep_gai_suspend64_defined
#define __localdep_gai_suspend64 __LIBC_LOCAL_NAME(gai_suspend64)
#endif /* !__local___localdep_gai_suspend64_defined */
#else /* __CRT_HAVE_gai_suspend */
#undef __local_gai_suspend64_defined
#endif /* !__CRT_HAVE_gai_suspend */
#endif /* !__local_gai_suspend64_defined */
