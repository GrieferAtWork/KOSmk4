/* HASH CRC-32:0x19666579 */
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
#ifndef __local_getentropy_defined
#define __local_getentropy_defined
#include <__crt.h>
#include <asm/os/random.h>
#if defined(__GRND_RANDOM) && defined(__CRT_HAVE_getrandom)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getrandom_defined
#define __local___localdep_getrandom_defined
__CREDIRECT(__ATTR_WUNUSED __ATTR_OUTS(1, 2),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_getrandom,(void *__buf, __SIZE_TYPE__ __num_bytes, unsigned int __flags),getrandom,(__buf,__num_bytes,__flags))
#endif /* !__local___localdep_getrandom_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(getentropy) __ATTR_WUNUSED __ATTR_OUTS(1, 2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(getentropy))(void *__buf, __SIZE_TYPE__ __num_bytes) {
	__SIZE_TYPE__ __result = 0;
	__SSIZE_TYPE__ __temp;
	while (__result < __num_bytes) {
		__temp = (__NAMESPACE_LOCAL_SYM __localdep_getrandom)((__BYTE_TYPE__ *)__buf + __result,
		                 __num_bytes - __result,
		                 __GRND_RANDOM);
		if (__temp < 0) {
#if defined(__libc_geterrno) && defined(__EINTR)
			if (__libc_geterrno() == __EINTR)
				continue;
#endif /* __libc_geterrno && __EINTR */
			goto __err;
		}
		__result += (__SIZE_TYPE__)__temp;
	}
	return 0;
__err:
	return -1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getentropy_defined
#define __local___localdep_getentropy_defined
#define __localdep_getentropy __LIBC_LOCAL_NAME(getentropy)
#endif /* !__local___localdep_getentropy_defined */
#else /* __GRND_RANDOM && __CRT_HAVE_getrandom */
#undef __local_getentropy_defined
#endif /* !__GRND_RANDOM || !__CRT_HAVE_getrandom */
#endif /* !__local_getentropy_defined */
