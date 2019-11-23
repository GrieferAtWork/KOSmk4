/* HASH CRC-32:0x36930f84 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_random_defined
#define __local_random_defined 1
/* Dependency: "rand" from "stdlib" */
#ifndef ____localdep_rand_defined
#define ____localdep_rand_defined 1
#ifdef __CRT_HAVE_rand
__CREDIRECT(,int,__NOTHROW,__localdep_rand,(void),rand,())
#elif defined(__CRT_HAVE_random) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
__CREDIRECT(,int,__NOTHROW,__localdep_rand,(void),random,())
#else /* LIBC: rand */
#include <local/stdlib/rand.h>
#define __localdep_rand (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rand))
#endif /* rand... */
#endif /* !____localdep_rand_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(random) long
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(random))(void) {
#line 1383 "kos/src/libc/magic/stdlib.c"
	return (long)__localdep_rand();
}
__NAMESPACE_LOCAL_END
#endif /* !__local_random_defined */
