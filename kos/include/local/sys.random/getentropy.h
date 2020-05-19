/* HASH CRC-32:0xa6750b29 */
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
#ifndef __local_getentropy_defined
#include <asm/random.h>
#if defined(__GRND_RANDOM) && defined(__CRT_HAVE_getrandom)
#define __local_getentropy_defined 1
#include <__crt.h>
#include <parts/errno.h>
/* Dependency: "getrandom" */
#ifndef ____localdep_getrandom_defined
#define ____localdep_getrandom_defined 1
#ifdef __CRT_HAVE_getrandom
/* Ask the kernel for up to `NUM_BYTES' bytes of random data, which
 * should then be written to `BUFFER'.
 * @param: FLAGS: Set of `GRND_NONBLOCK | GRND_RANDOM'
 * @return: * :   The actual number of returned random bytes.
 *                If `GRND_NONBLOCK' was passed, or if the calling thread
 *                was interrupted, this may be less than `NUM_BYTES'
 * @return: -1:   Error (s.a. `errno') Note that in the event of the
 *                calling thread being interrupted, EINTR is only set
 *                if no random data had already been retrieved from
 *                the kernel's random data sink. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_getrandom,(void *__buf, __SIZE_TYPE__ __num_bytes, unsigned int __flags),getrandom,(__buf,__num_bytes,__flags))
#else /* LIBC: getrandom */
#undef ____localdep_getrandom_defined
#endif /* getrandom... */
#endif /* !____localdep_getrandom_defined */

__NAMESPACE_LOCAL_BEGIN
/* Similar to `getrandom(BUF, NUM_BYTES, GRND_RANDOM)', however
 * the case where the calling thread is interrupted, causing an
 * less than `NUM_BYTES' of data to be read is handled by reading
 * more random data until all of `NUM_BYTES' have been read.
 * Note that portable applications should be aware that certain
 * implementations of this function disallow calls where `NUM_BYTES'
 * is larger than `256'
 * Also note that any other than `EFAULT' and `ENOSYS' are translated into `EIO'
 * @return:  0: Success
 * @return: -1: Error (see `errno') */
__LOCAL_LIBC(getentropy) __ATTR_WUNUSED __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(getentropy))(void *__buf,
                                                        __SIZE_TYPE__ __num_bytes) {
#line 86 "kos/src/libc/magic/sys.random.c"
	__SIZE_TYPE__ __result = 0;
	__SSIZE_TYPE__ __temp;
	while (__result < __num_bytes) {
		__temp = __localdep_getrandom((__BYTE_TYPE__ *)__buf + __result,
		                 __num_bytes - __result,
		                 __GRND_RANDOM);
		if (__temp < 0) {
#if defined(__libc_geterrno) && defined(__EINTR)
			if (__libc_geterrno() == __EINTR)
				continue;
#endif /* __libc_geterrno && EINTR */
			goto __err;
		}
		__result += (__SIZE_TYPE__)__temp;
	}
	return 0;
__err:
	return -1;
}
__NAMESPACE_LOCAL_END
#endif /* __GRND_RANDOM && __CRT_HAVE_getrandom */
#endif /* !__local_getentropy_defined */
