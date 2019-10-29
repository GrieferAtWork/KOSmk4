/* HASH CRC-32:0xd819eeec */
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
#ifndef __local_islower_defined
#define __local_islower_defined 1
/* Dependency: "__ctype_b_loc" from "ctype" */
#ifndef ____localdep___ctype_b_loc_defined
#define ____localdep___ctype_b_loc_defined 1
#if defined(__CRT_HAVE___ctype_b_loc)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__UINT16_TYPE__ const **,__NOTHROW,__localdep___ctype_b_loc,(void),__ctype_b_loc,())
#else /* LIBC: __ctype_b_loc */
#undef ____localdep___ctype_b_loc_defined
#endif /* __ctype_b_loc... */
#endif /* !____localdep___ctype_b_loc_defined */

/* Dependency: "__locale_ctype_ptr" from "ctype" */
#ifndef ____localdep___locale_ctype_ptr_defined
#define ____localdep___locale_ctype_ptr_defined 1
#if defined(__CRT_HAVE___locale_ctype_ptr)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,__localdep___locale_ctype_ptr,(void),__locale_ctype_ptr,())
#else /* LIBC: __locale_ctype_ptr */
#undef ____localdep___locale_ctype_ptr_defined
#endif /* __locale_ctype_ptr... */
#endif /* !____localdep___locale_ctype_ptr_defined */

/* Dependency: "_isctype" from "ctype" */
#ifndef ____localdep__isctype_defined
#define ____localdep__isctype_defined 1
#if defined(__CRT_HAVE__isctype)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep__isctype,(int __ch, int __mask),_isctype,(__ch,__mask))
#else /* LIBC: _isctype */
#undef ____localdep__isctype_defined
#endif /* _isctype... */
#endif /* !____localdep__isctype_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(islower) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(islower))(int __ch) {
#line 128 "kos/src/libc/magic/ctype.c"
#if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)
#include <__hybrid/__byteorder.__h>
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return (*__localdep___ctype_b_loc())[__ch] & (1 << 1);
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	return (*__localdep___ctype_b_loc())[__ch] & (1 << 9);
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#elif defined(__CRT_HAVE___locale_ctype_ptr) && defined(__CRT_CYG)
	return ((__localdep___locale_ctype_ptr() + 1)[__ch & 0xff] & 3) == 2;
#elif defined(__CRT_HAVE__isctype) && defined(__CRT_DOS)
	return __localdep__isctype(__ch, 0x0002);
#else
	return (__UINT8_TYPE__)__ch >= 0x61 && (__UINT8_TYPE__)__ch <= 0x7a;
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !__local_islower_defined */
