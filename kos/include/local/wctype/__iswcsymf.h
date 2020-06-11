/* HASH CRC-32:0x4442bee3 */
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
#ifndef __local___iswcsymf_defined
#define __local___iswcsymf_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: iswalpha from wctype */
#ifndef __local___localdep_iswalpha_defined
#define __local___localdep_iswalpha_defined 1
#if __has_builtin(__builtin_iswalpha) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswalpha)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_iswalpha,(__WINT_TYPE__ __wc),iswalpha,{ return __builtin_iswalpha(__wc); })
#elif defined(__CRT_HAVE_iswalpha)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_iswalpha,(__WINT_TYPE__ __wc),iswalpha,(__wc))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/wctype/iswalpha.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_iswalpha __LIBC_LOCAL_NAME(iswalpha)
#endif /* !... */
#endif /* !__local___localdep_iswalpha_defined */
__LOCAL_LIBC(__iswcsymf) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__iswcsymf))(__WINT_TYPE__ __wc) {
	return __localdep_iswalpha(__wc) || __wc == '_' || __wc == '$';
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___iswcsymf_defined
#define __local___localdep___iswcsymf_defined 1
#define __localdep___iswcsymf __LIBC_LOCAL_NAME(__iswcsymf)
#endif /* !__local___localdep___iswcsymf_defined */
#endif /* !__local___iswcsymf_defined */
