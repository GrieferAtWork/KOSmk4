/* HASH CRC-32:0x70b6b5ca */
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
#ifndef __local_isblank_l_defined
#define __local_isblank_l_defined 1
/* Dependency: "__locale_ctype_ptr_l" from "ctype" */
#ifndef ____localdep___locale_ctype_ptr_l_defined
#define ____localdep___locale_ctype_ptr_l_defined 1
#if defined(__CRT_HAVE___locale_ctype_ptr_l)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW_NCX,__localdep___locale_ctype_ptr_l,(__locale_t __locale),__locale_ctype_ptr_l,(__locale))
#else /* LIBC: __locale_ctype_ptr_l */
#undef ____localdep___locale_ctype_ptr_l_defined
#endif /* __locale_ctype_ptr_l... */
#endif /* !____localdep___locale_ctype_ptr_l_defined */

/* Dependency: "isblank" from "ctype" */
#ifndef ____localdep_isblank_defined
#define ____localdep_isblank_defined 1
#if __has_builtin(__builtin_isblank) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isblank)
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_isblank)(int __ch) { return __builtin_isblank(__ch); }
#elif defined(__CRT_HAVE_isblank)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isblank,(int __ch),isblank,(__ch))
#else /* LIBC: isblank */
#include <local/ctype/isblank.h>
#define __localdep_isblank (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isblank))
#endif /* isblank... */
#endif /* !____localdep_isblank_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(isblank_l) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(isblank_l))(int __ch,
                                                       __locale_t __locale) {
#line 586 "kos/src/libc/magic/ctype.c"
#if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)
#include <__hybrid/__byteorder.__h>
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return __locale->__ctype_b[__ch] & (1 << 8);
#else
	return __locale->__ctype_b[__ch] & (1 << 0);
#endif
#elif defined(__CRT_HAVE___locale_ctype_ptr_l) && defined(__CRT_CYG)
	return ((__localdep___locale_ctype_ptr_l(__locale) + 1)[__ch & 0xff] & 0200) != 0 || __ch == '\t';
#else
	(void)__locale;
	return __localdep_isblank(__ch);
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !__local_isblank_l_defined */
