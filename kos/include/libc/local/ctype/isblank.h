/* HASH CRC-32:0x19abc946 */
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
#ifndef __local_isblank_defined
#define __local_isblank_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: __ctype_b_loc from ctype */
#if !defined(__local___localdep___ctype_b_loc_defined) && defined(__CRT_HAVE___ctype_b_loc)
#define __local___localdep___ctype_b_loc_defined 1
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__UINT16_TYPE__ const **,__NOTHROW,__localdep___ctype_b_loc,(void),__ctype_b_loc,())
#endif /* !__local___localdep___ctype_b_loc_defined && __CRT_HAVE___ctype_b_loc */
/* Dependency: __locale_ctype_ptr from ctype */
#if !defined(__local___localdep___locale_ctype_ptr_defined) && defined(__CRT_HAVE___locale_ctype_ptr)
#define __local___localdep___locale_ctype_ptr_defined 1
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,__localdep___locale_ctype_ptr,(void),__locale_ctype_ptr,())
#endif /* !__local___localdep___locale_ctype_ptr_defined && __CRT_HAVE___locale_ctype_ptr */
__LOCAL_LIBC(isblank) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(isblank))(int __ch) {



#if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)
#include <hybrid/byteorder.h>
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return (*__localdep___ctype_b_loc())[__ch] & (1 << 8);
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	return (*__localdep___ctype_b_loc())[__ch] & (1 << 0);
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#elif defined(__CRT_HAVE___locale_ctype_ptr) && defined(__CRT_CYG)
	return ((__localdep___locale_ctype_ptr() + 1)[__ch & 0xff] & 0200) != 0 || __ch == '\t';
#else /* ... */
	return (__UINT8_TYPE__)__ch == 0x09 || (__UINT8_TYPE__)__ch == 0x20;
#endif /* !... */

}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_isblank_defined
#define __local___localdep_isblank_defined 1
#define __localdep_isblank __LIBC_LOCAL_NAME(isblank)
#endif /* !__local___localdep_isblank_defined */
#endif /* !__local_isblank_defined */
