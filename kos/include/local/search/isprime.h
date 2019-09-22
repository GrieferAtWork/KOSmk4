/* HASH CRC-32:0xffb7b4ff */
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
#ifndef __local_isprime_defined
#define __local_isprime_defined 1
/* Dependency: "div" from "stdlib" */
#ifndef ____localdep_div_defined
#define ____localdep_div_defined 1
#if defined(__CRT_HAVE_div)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,div_t,__NOTHROW_NCX,__localdep_div,(int __numer, int __denom),div,(__numer,__denom))
#elif defined(__CRT_HAVE_ldiv) && (__SIZEOF_INT__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,div_t,__NOTHROW_NCX,__localdep_div,(int __numer, int __denom),ldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_lldiv) && (__SIZEOF_INT__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,div_t,__NOTHROW_NCX,__localdep_div,(int __numer, int __denom),lldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_imaxdiv) && (__SIZEOF_INT__ == __SIZEOF_INTMAX_T__)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,div_t,__NOTHROW_NCX,__localdep_div,(int __numer, int __denom),imaxdiv,(__numer,__denom))
#else /* LIBC: div */
#include <local/stdlib/div.h>
#define __localdep_div (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(div))
#endif /* div... */
#endif /* !____localdep_div_defined */

__NAMESPACE_LOCAL_BEGIN
/* For the used double hash method the table size has to be a prime. To
 * correct the user given table size we need a prime test.  This trivial
 * algorithm is adequate because
 * a)  the code is (most probably) called a few times per program run and
 * b)  the number is small because the table must fit in the core */
__LOCAL_LIBC(isprime) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(isprime))(unsigned int __number) {
#line 255 "kos/src/libc/magic/search.c"
	/* no even number will be passed */
	for (unsigned int __localdep_div = 3; __localdep_div <= __number / __localdep_div; __localdep_div += 2)
		if (__number % __localdep_div == 0)
			return 0;
	return 1;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_isprime_defined */
