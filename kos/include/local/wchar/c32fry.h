/* HASH CRC-32:0x3002f580 */
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
#ifndef __local_c32fry_defined
#define __local_c32fry_defined 1
/* Dependency: "wcslen" from "wchar" */
#ifndef ____localdep_c32len_defined
#define ____localdep_c32len_defined 1
#if defined(__CRT_HAVE_wcslen) && (__SIZEOF_WCHAR_T__ == 4)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32len,(__CHAR32_TYPE__ const *__restrict __string),wcslen,(__string))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcslen.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_c32len(string) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslen))((__WCHAR_TYPE__ const *)(string))
#else /* LIBC: c32len */
#include <local/wchar/c32len.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_c32len (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32len))
#endif /* c32len... */
#endif /* !____localdep_c32len_defined */

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
__LOCAL_LIBC(c32fry) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c32fry))(__CHAR32_TYPE__ *__restrict __string) {
#line 780 "kos/src/libc/magic/string.c"
	__SIZE_TYPE__ __i, __count = __localdep_c32len(__string);
	for (__i = 0; __i < __count; ++__i) {
		__CHAR32_TYPE__ __temp;
		__SIZE_TYPE__ __j = __localdep_rand();
		__j = __i + (__j % (__count - __i));
		/* Swap these 2 characters. */
		__temp = __string[__i];
		__string[__i] = __string[__j];
		__string[__j] = __temp;
	}
	return __string;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c32fry_defined */
