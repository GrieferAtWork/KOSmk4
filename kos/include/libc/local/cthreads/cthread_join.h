/* HASH CRC-32:0xa292766 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_cthread_join_defined
#define __local_cthread_join_defined
#include <__crt.h>
#ifdef __CRT_HAVE_pthread_getresult_np
struct cthread;
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_pthread_getresult_np_defined
#define __local___localdep_pthread_getresult_np_defined
__NAMESPACE_LOCAL_END
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(2),__errno_t,__NOTHROW_RPC,__localdep_pthread_getresult_np,(__pthread_t __self, void **__thread_return),pthread_getresult_np,(__self,__thread_return))
#endif /* !__local___localdep_pthread_getresult_np_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(cthread_join) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(cthread_join))(struct cthread * __self) {
	void *__result;
	(__NAMESPACE_LOCAL_SYM __localdep_pthread_getresult_np)((__pthread_t)__self, &__result);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_cthread_join_defined
#define __local___localdep_cthread_join_defined
#define __localdep_cthread_join __LIBC_LOCAL_NAME(cthread_join)
#endif /* !__local___localdep_cthread_join_defined */
#else /* __CRT_HAVE_pthread_getresult_np */
#undef __local_cthread_join_defined
#endif /* !__CRT_HAVE_pthread_getresult_np */
#endif /* !__local_cthread_join_defined */
