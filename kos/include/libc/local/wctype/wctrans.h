/* HASH CRC-32:0xda5dfe52 */
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
#ifndef __local_wctrans_defined
#define __local_wctrans_defined
#include <__crt.h>
#ifdef __CRT_KOS
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strcmp_defined
#define __local___localdep_strcmp_defined
#if __has_builtin(__builtin_strcmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,{ return __builtin_strcmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,(__s1,__s2))
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
__LOCAL_LIBC(wctrans) __ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __wctrans_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wctrans))(char const *__prop) {
	struct wctrans_entry {
		char     __we_name[8]; /* Name (including the leading "to") */
		__UINT16_TYPE__ __we_offset;  /* Offset to `int32_t' field in `struct __unitraits' */
	};
	static struct wctrans_entry const __entries[] = {
		{ "tolower", __builtin_offsetof(struct __unitraits, __ut_lower) },
		{ "toupper", __builtin_offsetof(struct __unitraits, __ut_upper) },
		{ "totitle", __builtin_offsetof(struct __unitraits, __ut_title) }, /* Kos extension! */
	};
	unsigned int __i;
	for (__i = 0; __i < __COMPILER_LENOF(__entries); ++__i) {
		if ((__NAMESPACE_LOCAL_SYM __localdep_strcmp)(__prop, __entries[__i].__we_name) == 0)
			return (__wctrans_t)(__UINTPTR_TYPE__)__entries[__i].__we_offset;
	}
	return (__wctrans_t)0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wctrans_defined
#define __local___localdep_wctrans_defined
#define __localdep_wctrans __LIBC_LOCAL_NAME(wctrans)
#endif /* !__local___localdep_wctrans_defined */
#else /* __CRT_KOS */
#undef __local_wctrans_defined
#endif /* !__CRT_KOS */
#endif /* !__local_wctrans_defined */
