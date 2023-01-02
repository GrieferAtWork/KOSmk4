/* HASH CRC-32:0x4930f75f */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_strupr_l_defined
#define __local_strupr_l_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_toupper_l_defined
#define __local___localdep_toupper_l_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_toupper_l) && defined(__CRT_HAVE_toupper_l)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_toupper_l,(int __ch, __locale_t __locale),toupper_l,{ return __crt_toupper_l(__ch, __locale); })
#elif defined(__crt_toupper_l) && defined(__CRT_HAVE__toupper_l)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_toupper_l,(int __ch, __locale_t __locale),_toupper_l,{ return __crt_toupper_l(__ch, __locale); })
#elif defined(__crt_toupper_l) && defined(__CRT_HAVE___toupper_l)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_toupper_l,(int __ch, __locale_t __locale),__toupper_l,{ return __crt_toupper_l(__ch, __locale); })
#elif defined(__crt_toupper_l)
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL __localdep_toupper_l)(int __ch, __locale_t __locale) { return __crt_toupper_l(__ch, __locale); }
#elif defined(__CRT_HAVE_toupper_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_toupper_l,(int __ch, __locale_t __locale),toupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE__toupper_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_toupper_l,(int __ch, __locale_t __locale),_toupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE___toupper_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_toupper_l,(int __ch, __locale_t __locale),__toupper_l,(__ch,__locale))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/toupper_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_toupper_l __LIBC_LOCAL_NAME(toupper_l)
#endif /* !... */
#endif /* !__local___localdep_toupper_l_defined */
__LOCAL_LIBC(strupr_l) __ATTR_LEAF __ATTR_INOUT(1) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strupr_l))(char *__restrict __str, __locale_t __locale) {
	char *__iter, __ch;
	for (__iter = __str; (__ch = *__iter) != '\0'; ++__iter)
		*__iter = (char)(__NAMESPACE_LOCAL_SYM __localdep_toupper_l)((unsigned char)__ch, __locale);
	return __str;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strupr_l_defined
#define __local___localdep_strupr_l_defined
#define __localdep_strupr_l __LIBC_LOCAL_NAME(strupr_l)
#endif /* !__local___localdep_strupr_l_defined */
#endif /* !__local_strupr_l_defined */
