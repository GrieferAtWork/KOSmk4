/* HASH CRC-32:0xd8057b38 */
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
#ifndef __local_toupper_defined
#define __local_toupper_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep___ctype_toupper_loc_defined) && defined(__CRT_HAVE___ctype_toupper_loc)
#define __local___localdep___ctype_toupper_loc_defined 1
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__INT32_TYPE__ const **,__NOTHROW,__localdep___ctype_toupper_loc,(void),__ctype_toupper_loc,())
#endif /* !__local___localdep___ctype_toupper_loc_defined && __CRT_HAVE___ctype_toupper_loc */
#ifndef __local___localdep_islower_defined
#define __local___localdep_islower_defined 1
#if __has_builtin(__builtin_islower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_islower)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_islower,(int __ch),islower,{ return __builtin_islower(__ch); })
#elif defined(__CRT_HAVE_islower)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_islower,(int __ch),islower,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/islower.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_islower __LIBC_LOCAL_NAME(islower)
#endif /* !... */
#endif /* !__local___localdep_islower_defined */
__LOCAL_LIBC(toupper) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(toupper))(int __ch) {



#if defined(__CRT_HAVE___ctype_toupper_loc) && defined(__CRT_CYG)
	return __ch >= -128 && __ch < 256 ? (*__localdep___ctype_toupper_loc())[__ch] : __ch;
#else /* __CRT_HAVE___ctype_toupper_loc && __CRT_CYG */
	return __localdep_islower(__ch) ? ((__UINT8_TYPE__)__ch-0x20) : __ch;
#endif /* !__CRT_HAVE___ctype_toupper_loc || !__CRT_CYG */

}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_toupper_defined
#define __local___localdep_toupper_defined 1
#define __localdep_toupper __LIBC_LOCAL_NAME(toupper)
#endif /* !__local___localdep_toupper_defined */
#endif /* !__local_toupper_defined */
