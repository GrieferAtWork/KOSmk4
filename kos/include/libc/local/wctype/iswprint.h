/* HASH CRC-32:0xbc7c3827 */
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
#ifndef __local_iswprint_defined
#define __local_iswprint_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_isprint_defined
#define __local___localdep_isprint_defined 1
#if __has_builtin(__builtin_isprint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isprint)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isprint,(int __ch),isprint,{ return __builtin_isprint(__ch); })
#elif defined(__CRT_HAVE_isprint)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isprint,(int __ch),isprint,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/isprint.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isprint __LIBC_LOCAL_NAME(isprint)
#endif /* !... */
#endif /* !__local___localdep_isprint_defined */
__LOCAL_LIBC(iswprint) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(iswprint))(__WINT_TYPE__ __wc) {
	return __localdep_isprint((int)__wc);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_iswprint_defined
#define __local___localdep_iswprint_defined 1
#define __localdep_iswprint __LIBC_LOCAL_NAME(iswprint)
#endif /* !__local___localdep_iswprint_defined */
#endif /* !__local_iswprint_defined */
