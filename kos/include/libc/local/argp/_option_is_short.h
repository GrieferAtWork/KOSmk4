/* HASH CRC-32:0xef7f1fd2 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__option_is_short_defined
#define __local__option_is_short_defined
#include <__crt.h>
#include <bits/crt/argp.h>
#ifdef __OPTION_DOC
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_isprint_defined
#define __local___localdep_isprint_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_isprint) && defined(__CRT_HAVE_isprint)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isprint,(int __ch),isprint,{ return __crt_isprint(__ch); })
#elif defined(__crt_isprint)
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_isprint)(int __ch) { return __crt_isprint(__ch); }
#elif __has_builtin(__builtin_isprint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isprint)
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
__LOCAL_LIBC(_option_is_short) __ATTR_IN(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_option_is_short))(struct argp_option const *__opt) {
	int __opt_key;
	if (__opt->flags & __OPTION_DOC)
		return 0;
	__opt_key = __opt->key;
	return __opt_key > 0 && __opt_key <= 0xff && (__NAMESPACE_LOCAL_SYM __localdep_isprint)(__opt_key);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__option_is_short_defined
#define __local___localdep__option_is_short_defined
#define __localdep__option_is_short __LIBC_LOCAL_NAME(_option_is_short)
#endif /* !__local___localdep__option_is_short_defined */
#else /* __OPTION_DOC */
#undef __local__option_is_short_defined
#endif /* !__OPTION_DOC */
#endif /* !__local__option_is_short_defined */
