/* HASH CRC-32:0x63b01414 */
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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/random.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/random.h) */
/* (#) Portability: FreeBSD       (/sys/sys/random.h) */
/* (#) Portability: GNU C Library (/stdlib/sys/random.h) */
/* (#) Portability: NetBSD        (/sys/sys/random.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/random.h) */
/* (#) Portability: diet libc     (/include/sys/random.h) */
/* (#) Portability: musl libc     (/include/sys/random.h) */
#ifndef _SYS_RANDOM_H
#define _SYS_RANDOM_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/os/random.h>
#include <bits/types.h>
#ifdef __USE_GLIBC_BLOAT
#include <sys/types.h>
#endif /* __USE_GLIBC_BLOAT */


/* Flags accepted by `getrandom(2)' */
#ifdef __GRND_NONBLOCK
#define GRND_NONBLOCK __GRND_NONBLOCK /* Don't block if no random data is available (right now) */
#endif /* __GRND_NONBLOCK */
#ifdef __GRND_RANDOM
#define GRND_RANDOM __GRND_RANDOM /* Use /dev/random, rather than /dev/urandom */
#endif /* __GRND_RANDOM */


#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef __ssize_t_defined
#define __ssize_t_defined
typedef __SSIZE_TYPE__ ssize_t;
#endif /* !__ssize_t_defined */

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
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_OUTS(1, 2),ssize_t,__NOTHROW_NCX,getrandom,(void *__buf, size_t __num_bytes, unsigned int __flags),(__buf,__num_bytes,__flags))
#ifndef __getentropy_defined
#define __getentropy_defined
#ifdef __CRT_HAVE_getentropy
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
__CDECLARE(__ATTR_WUNUSED __ATTR_OUTS(1, 2),int,__NOTHROW_NCX,getentropy,(void *__buf, size_t __num_bytes),(__buf,__num_bytes))
#elif defined(__GRND_RANDOM) && defined(__CRT_HAVE_getrandom)
#include <libc/local/sys.random/getentropy.h>
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
__NAMESPACE_LOCAL_USING_OR_IMPL(getentropy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUTS(1, 2) int __NOTHROW_NCX(__LIBCCALL getentropy)(void *__buf, size_t __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getentropy))(__buf, __num_bytes); })
#else /* ... */
#undef __getentropy_defined
#endif /* !... */
#endif /* !__getentropy_defined */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_RANDOM_H */
