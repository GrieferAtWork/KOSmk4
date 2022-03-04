/* HASH CRC-32:0x227ddb17 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_wctype_defined
#define __local_wctype_defined
#include <__crt.h>
#if defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor)
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strcmp_defined
#define __local___localdep_strcmp_defined
#if __has_builtin(__builtin_strcmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,{ return __builtin_strcmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,(__s1,__s2))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strcmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strcmp __LIBC_LOCAL_NAME(strcmp)
#endif /* !... */
#endif /* !__local___localdep_strcmp_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/unicode.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wctype) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __wctype_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wctype))(char const *__prop) {
	struct wctype_entry {
		char     __we_name[8]; /* Name (with leading "is" stripped) */
		__UINT16_TYPE__ __we_flags;   /* Flags that must be set. */
	};
	static struct wctype_entry const __entries[] = {
		{ "cntrl",   __UNICODE_ISCNTRL },
		{ "space",   __UNICODE_ISSPACE },
		{ "lower",   __UNICODE_ISLOWER },
		{ "upper",   __UNICODE_ISUPPER },
		{ "alpha",   __UNICODE_ISALPHA },
		{ "digit",   __UNICODE_ISDIGIT },
		{ "xdigit",  __UNICODE_ISXDIGIT },
		{ "alnum",   __UNICODE_ISALNUM },
		{ "punct",   __UNICODE_ISPUNCT },
		{ "graph",   __UNICODE_ISGRAPH },
		{ "print",   __UNICODE_ISPRINT },
		{ "blank",   __UNICODE_ISBLANK },
		/* All of the following are KOS extensions! */
		{ "tab",     __UNICODE_ISTAB },
		{ "white",   __UNICODE_ISWHITE },
		{ "empty",   __UNICODE_ISEMPTY },
		{ "lf",      __UNICODE_ISLF },
		{ "hex",     __UNICODE_ISHEX },
		{ "title",   __UNICODE_ISTITLE },
		{ "numeric", __UNICODE_ISNUMERIC },
		{ "symstrt", __UNICODE_ISSYMSTRT },
		{ "symcont", __UNICODE_ISSYMCONT },
	};
	unsigned int __i;
	for (__i = 0; __i < __COMPILER_LENOF(__entries); ++__i) {
		if ((__NAMESPACE_LOCAL_SYM __localdep_strcmp)(__prop, __entries[__i].__we_name) == 0)
			return __entries[__i].__we_flags;
	}
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wctype_defined
#define __local___localdep_wctype_defined
#define __localdep_wctype __LIBC_LOCAL_NAME(wctype)
#endif /* !__local___localdep_wctype_defined */
#else /* __CRT_KOS && __CRT_HAVE___unicode_descriptor */
#undef __local_wctype_defined
#endif /* !__CRT_KOS || !__CRT_HAVE___unicode_descriptor */
#endif /* !__local_wctype_defined */
