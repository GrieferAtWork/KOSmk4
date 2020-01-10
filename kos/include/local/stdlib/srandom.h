/* HASH CRC-32:0x34651dc1 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_srandom_defined
#define __local_srandom_defined 1
/* Dependency: "srand" from "stdlib" */
#ifndef ____localdep_srand_defined
#define ____localdep_srand_defined 1
#ifdef __CRT_HAVE_srand
__CREDIRECT_VOID(,__NOTHROW,__localdep_srand,(long __seed),srand,(__seed))
#elif defined(__CRT_HAVE_srandom) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
__CREDIRECT_VOID(,__NOTHROW,__localdep_srand,(long __seed),srandom,(__seed))
#else /* LIBC: srand */
#include <local/stdlib/srand.h>
#define __localdep_srand (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(srand))
#endif /* srand... */
#endif /* !____localdep_srand_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(srandom) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(srandom))(unsigned int __seed) {
#line 1427 "kos/src/libc/magic/stdlib.c"
	__localdep_srand((long)__seed);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_srandom_defined */
