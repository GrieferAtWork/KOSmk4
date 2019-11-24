/* HASH CRC-32:0xe3706d97 */
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
#ifndef __local__wcsupr_s_defined
#define __local__wcsupr_s_defined 1
/* Dependency: "wcsnlen" from "wchar" */
#ifndef ____localdep_wcsnlen_defined
#define ____localdep_wcsnlen_defined 1
#ifdef __CRT_HAVE_wcsnlen
/* Same as `wcslen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcsnlen,(__WCHAR_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#else /* LIBC: wcsnlen */
#include <local/wchar/wcsnlen.h>
/* Same as `wcslen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __localdep_wcsnlen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlen))
#endif /* wcsnlen... */
#endif /* !____localdep_wcsnlen_defined */

/* Dependency: "towupper" from "wctype" */
#ifndef ____localdep_towupper_defined
#define ____localdep_towupper_defined 1
#if __has_builtin(__builtin_towupper) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_towupper)
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __WINT_TYPE__ __NOTHROW(__LIBCCALL __localdep_towupper)(__WINT_TYPE__ __wc) { return __builtin_towupper(__wc); }
#elif defined(__CRT_HAVE_towupper)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW,__localdep_towupper,(__WINT_TYPE__ __wc),towupper,(__wc))
#else /* LIBC: towupper */
#include <local/wctype/towupper.h>
#define __localdep_towupper (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towupper))
#endif /* towupper... */
#endif /* !____localdep_towupper_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_wcsupr_s) __ATTR_LEAF __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_wcsupr_s))(__WCHAR_TYPE__ *__buf,
                                                       __SIZE_TYPE__ __buflen) {
#line 5047 "kos/src/libc/magic/string.c"
	__WCHAR_TYPE__ *__iter, __ch;
	if (__buf == __NULLPTR)
		return __EINVAL;
	if (__localdep_wcsnlen(__buf, __buflen) >= __buflen)
		return __EINVAL;
	for (__iter = __buf; (__ch = *__iter) != '\0'; ++__iter)
		*__iter = (__WCHAR_TYPE__)__localdep_towupper(__ch);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__local__wcsupr_s_defined */
