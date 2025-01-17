/* HASH CRC-32:0x1b0ad5c4 */
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
#ifndef __local_rand_s_defined
#define __local_rand_s_defined
#include <__crt.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_rand_defined
#define __local___localdep_rand_defined
#ifdef __CRT_HAVE_rand
__CREDIRECT(,int,__NOTHROW,__localdep_rand,(void),rand,())
#else /* __CRT_HAVE_rand */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_random) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(,int,__NOTHROW,__localdep_rand,(void),random,())
#else /* __CRT_HAVE_random && __SIZEOF_INT__ == __SIZEOF_LONG__ */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/rand.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_rand __LIBC_LOCAL_NAME(rand)
#endif /* !__CRT_HAVE_random || __SIZEOF_INT__ != __SIZEOF_LONG__ */
#endif /* !__CRT_HAVE_rand */
#endif /* !__local___localdep_rand_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(rand_s) __ATTR_OUT(1) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(rand_s))(unsigned int *__restrict __randval) {
	if (!__randval) {
#ifdef __EINVAL
		return __EINVAL;
#else /* __EINVAL */
		return 1;
#endif /* !__EINVAL */
	}
	*__randval = (__NAMESPACE_LOCAL_SYM __localdep_rand)();
	return __EOK;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_rand_s_defined
#define __local___localdep_rand_s_defined
#define __localdep_rand_s __LIBC_LOCAL_NAME(rand_s)
#endif /* !__local___localdep_rand_s_defined */
#endif /* !__local_rand_s_defined */
