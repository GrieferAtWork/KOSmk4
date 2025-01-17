/* HASH CRC-32:0x69c765b9 */
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
#ifndef __local_thr_join_defined
#define __local_thr_join_defined
#include <__crt.h>
#ifdef __CRT_HAVE_pthread_join
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_pthread_join_defined
#define __local___localdep_pthread_join_defined
__CREDIRECT(__ATTR_OUT_OPT(2),__errno_t,__NOTHROW_RPC,__localdep_pthread_join,(__pthread_t __self, void **__thread_return),pthread_join,(__self,__thread_return))
#endif /* !__local___localdep_pthread_join_defined */
__LOCAL_LIBC(thr_join) __ATTR_OUT(2) __ATTR_OUT_OPT(3) __errno_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(thr_join))(__pthread_t __thr, __pthread_t *__p_departed, void **__thread_return) {
	__errno_t __result;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_pthread_join)(__thr, __thread_return);
	if (__result == 0)
		*__p_departed = __thr;
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_thr_join_defined
#define __local___localdep_thr_join_defined
#define __localdep_thr_join __LIBC_LOCAL_NAME(thr_join)
#endif /* !__local___localdep_thr_join_defined */
#else /* __CRT_HAVE_pthread_join */
#undef __local_thr_join_defined
#endif /* !__CRT_HAVE_pthread_join */
#endif /* !__local_thr_join_defined */
