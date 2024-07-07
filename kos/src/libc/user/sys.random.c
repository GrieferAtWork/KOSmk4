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
#ifndef GUARD_LIBC_USER_SYS_RANDOM_C
#define GUARD_LIBC_USER_SYS_RANDOM_C 1

#include "../api.h"
/**/

#include <errno.h>
#include <fcntl.h>
#include <syscall.h>
#include <unistd.h>

#include "../libc/syscalls.h"
#include "sys.random.h"

DECL_BEGIN

/*[[[head:libc_getrandom,hash:CRC-32=0x4f30f1a5]]]*/
/* >> getrandom(2)
 * Ask the kernel for up to `num_bytes' bytes of random
 * data,   which  should  then  be  written  to  `buf'.
 * @param: flags: Set of `GRND_NONBLOCK | GRND_RANDOM'
 * @return: * :   The actual number of returned random bytes.
 *                If `GRND_NONBLOCK' was passed, or if the calling thread
 *                was  interrupted,  this  may be  less  than `num_bytes'
 * @return: -1:   Error (s.a. `errno')  Note that in  the event of  the
 *                calling thread being interrupted, `EINTR' is only set
 *                if no  random data  had already  been retrieved  from
 *                the kernel's random data sink. */
INTERN ATTR_SECTION(".text.crt.system.random") WUNUSED ATTR_OUTS(1, 2) ssize_t
NOTHROW_NCX(LIBCCALL libc_getrandom)(void *buf,
                                     size_t num_bytes,
                                     unsigned int flags)
/*[[[body:libc_getrandom]]]*/
{
#ifdef SYS_getrandom
	ssize_t result;
	result = sys_getrandom(buf, num_bytes, (syscall_ulong_t)flags);
	return libc_seterrno_syserr(result);
#else /* SYS_getrandom */
	ssize_t result;
	fd_t fd;
	PRIVATE ATTR_SECTION(".rodata.crt.system.random") char const str_dev_random[] = "/dev/random";
	PRIVATE ATTR_SECTION(".rodata.crt.system.random") char const str_dev_urandom[] = "/dev/urandom";
	if ((flags & ~(GRND_NONBLOCK | GRND_RANDOM)) != 0) {
		libc_seterrno(EINVAL);
		goto err;
	}
	fd = open((flags & GRND_RANDOM) ? str_dev_random
	                                : str_dev_urandom,
	          (flags & GRND_NONBLOCK) ? (O_RDONLY | O_NONBLOCK)
	                                  : (O_RDONLY));
	if unlikely(fd < 0)
		goto err;
	result = read(fd, buf, num_bytes);
	sys_close(fd);
	return result;
err:
	return -1;
#endif /* !SYS_getrandom */
}
/*[[[end:libc_getrandom]]]*/

/*[[[head:libc_getentropy,hash:CRC-32=0xd40c5c35]]]*/
/* >> getentropy(3)
 * Similar   to   `getrandom(buf, num_bytes, GRND_RANDOM)',  however
 * the  case  where  the  calling  thread  is  interrupted,  causing
 * less  than `num_bytes' of  data to be read  is handled by reading
 * more  random  data  until  all  of  `num_bytes'  have  been read.
 * Note that  portable applications  should  be aware  that  certain
 * implementations of this function disallow calls where `num_bytes'
 * is larger than `256'
 * Also note that any error other than `EFAULT'
 * and `ENOSYS'  may be  translated into  `EIO'
 * @return:  0: Success
 * @return: -1: Error (see `errno') */
INTERN ATTR_SECTION(".text.crt.system.random") WUNUSED ATTR_OUTS(1, 2) int
NOTHROW_NCX(LIBCCALL libc_getentropy)(void *buf,
                                      size_t num_bytes)
/*[[[body:libc_getentropy]]]*/
/*AUTO*/{
	size_t result = 0;
	ssize_t temp;
	while (result < num_bytes) {
		temp = getrandom((byte_t *)buf + result,
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
/*[[[end:libc_getentropy]]]*/





/*[[[start:exports,hash:CRC-32=0xe8837891]]]*/
DEFINE_PUBLIC_ALIAS_P(getrandom,libc_getrandom,WUNUSED ATTR_OUTS(1, 2),ssize_t,NOTHROW_NCX,LIBCCALL,(void *buf, size_t num_bytes, unsigned int flags),(buf,num_bytes,flags));
DEFINE_PUBLIC_ALIAS_P(getentropy,libc_getentropy,WUNUSED ATTR_OUTS(1, 2),int,NOTHROW_NCX,LIBCCALL,(void *buf, size_t num_bytes),(buf,num_bytes));
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_RANDOM_C */
