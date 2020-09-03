/* HASH CRC-32:0x1992114c */
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
#ifndef __local__iswcsymf_l_defined
#define __local__iswcsymf_l_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: iswalpha_l from wctype */
#ifndef __local___localdep_iswalpha_l_defined
#define __local___localdep_iswalpha_l_defined 1
#ifdef __CRT_HAVE_iswalpha_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_iswalpha_l,(__WINT_TYPE__ __wc, __locale_t __locale),iswalpha_l,(__wc,__locale))
#elif defined(__CRT_HAVE__iswalpha_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_iswalpha_l,(__WINT_TYPE__ __wc, __locale_t __locale),_iswalpha_l,(__wc,__locale))
#elif defined(__CRT_HAVE___iswalpha_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_iswalpha_l,(__WINT_TYPE__ __wc, __locale_t __locale),__iswalpha_l,(__wc,__locale))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/wctype/iswalpha_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_iswalpha_l __LIBC_LOCAL_NAME(iswalpha_l)
#endif /* !... */
#endif /* !__local___localdep_iswalpha_l_defined */
__LOCAL_LIBC(_iswcsymf_l) __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_iswcsymf_l))(__WINT_TYPE__ __wc, __locale_t __locale) {
	return __localdep_iswalpha_l(__wc, __locale) || __wc == '_' || __wc == '$';
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__iswcsymf_l_defined
#define __local___localdep__iswcsymf_l_defined 1
#define __localdep__iswcsymf_l __LIBC_LOCAL_NAME(_iswcsymf_l)
#endif /* !__local___localdep__iswcsymf_l_defined */
#endif /* !__local__iswcsymf_l_defined */
