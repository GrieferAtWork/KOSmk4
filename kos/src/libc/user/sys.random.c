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
#ifndef GUARD_LIBC_USER_SYS_RANDOM_C
#define GUARD_LIBC_USER_SYS_RANDOM_C 1

#include "../api.h"
#include "sys.random.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:getrandom,hash:CRC-32=0x8b2e1e8c]]]*/
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
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.system.random.getrandom") ssize_t
NOTHROW_NCX(LIBCCALL libc_getrandom)(void *buf,
                                     size_t num_bytes,
                                     unsigned int flags)
/*[[[body:getrandom]]]*/
{
	(void)buf;
	(void)num_bytes;
	(void)flags;
	CRT_UNIMPLEMENTED("getrandom"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getrandom]]]*/

/*[[[head:getentropy,hash:CRC-32=0x1ff663ce]]]*/
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
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.system.random.getentropy") int
NOTHROW_NCX(LIBCCALL libc_getentropy)(void *buf,
                                      size_t num_bytes)
/*[[[body:getentropy]]]*/
/*AUTO*/{
	size_t result = 0;
	ssize_t temp;
	while (result < num_bytes) {
		temp = libc_getrandom((byte_t *)buf + result,
		                 num_bytes - result,
		                 GRND_RANDOM);
		if (temp < 0) {
#if defined(__libc_geterrno) && defined(EINTR)
			if (__libc_geterrno() == EINTR)
				continue;
#endif /* __libc_geterrno && EINTR */
			goto err;
		}
		result += (size_t)temp;
	}
	return 0;
err:
	return -1;
}
/*[[[end:getentropy]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x52a90821]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(getrandom, libc_getrandom);
DEFINE_PUBLIC_WEAK_ALIAS(getentropy, libc_getentropy);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_RANDOM_C */
