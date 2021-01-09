/* HASH CRC-32:0x354ae9a9 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_random_defined
#define __local_random_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: rand from stdlib */
#ifndef __local___localdep_rand_defined
#define __local___localdep_rand_defined 1
#ifdef __CRT_HAVE_rand
__CREDIRECT(,int,__NOTHROW,__localdep_rand,(void),rand,())
#elif defined(__CRT_HAVE_random) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(,int,__NOTHROW,__localdep_rand,(void),random,())
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/rand.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_rand __LIBC_LOCAL_NAME(rand)
#endif /* !... */
#endif /* !__local___localdep_rand_defined */
__LOCAL_LIBC(random) long
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(random))(void) {
	return (long)__localdep_rand();
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_random_defined
#define __local___localdep_random_defined 1
#define __localdep_random __LIBC_LOCAL_NAME(random)
#endif /* !__local___localdep_random_defined */
#endif /* !__local_random_defined */
