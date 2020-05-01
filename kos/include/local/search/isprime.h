/* HASH CRC-32:0x8e7e3fb1 */
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
#ifndef __local_isprime_defined
#define __local_isprime_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* For the used double hash method the table size has to be a prime. To
 * correct the user given table size we need a prime test.  This trivial
 * algorithm is adequate because
 * a)  the code is (most probably) called a few times per program run and
 * b)  the number is small because the table must fit in the core */
__LOCAL_LIBC(isprime) __ATTR_CONST int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(isprime))(unsigned int __number) {
#line 256 "kos/src/libc/magic/search.c"
	/* no even number will be passed */
	for (unsigned int __div = 3; __div <= __number / __div; __div += 2) {
		if (__number % __div == 0)
			return 0;
	}
	return 1;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_isprime_defined */
