/* HASH CRC-32:0x15aadc89 */
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
#ifndef __local_pthread_getspecific_defined
#define __local_pthread_getspecific_defined
#include <__crt.h>
#ifdef __CRT_HAVE_pthread_getspecificptr_np
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_pthread_getspecificptr_np_defined
#define __local___localdep_pthread_getspecificptr_np_defined
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,void **,__NOTHROW_NCX,__localdep_pthread_getspecificptr_np,(__pthread_key_t __key),pthread_getspecificptr_np,(__key))
#endif /* !__local___localdep_pthread_getspecificptr_np_defined */
__LOCAL_LIBC(pthread_getspecific) __ATTR_WUNUSED void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(pthread_getspecific))(__pthread_key_t __key) {
	void **__slot = (__NAMESPACE_LOCAL_SYM __localdep_pthread_getspecificptr_np)(__key);
	return __likely(__slot) ? *__slot : __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pthread_getspecific_defined
#define __local___localdep_pthread_getspecific_defined
#define __localdep_pthread_getspecific __LIBC_LOCAL_NAME(pthread_getspecific)
#endif /* !__local___localdep_pthread_getspecific_defined */
#else /* __CRT_HAVE_pthread_getspecificptr_np */
#undef __local_pthread_getspecific_defined
#endif /* !__CRT_HAVE_pthread_getspecificptr_np */
#endif /* !__local_pthread_getspecific_defined */
