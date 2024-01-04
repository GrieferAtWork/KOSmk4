/* HASH CRC-32:0x3b1b5a80 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_sl_find_defined
#define __local_sl_find_defined
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
#ifndef ___stringlist_defined
#define ___stringlist_defined
typedef struct _stringlist {
	char   **sl_str;
	__SIZE_TYPE__   sl_max;
	__SIZE_TYPE__   sl_cur;
} StringList;
#endif /* !___stringlist_defined */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strcmp_defined
#define __local___localdep_strcmp_defined
#if __has_builtin(__builtin_strcmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,{ return __builtin_strcmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,(__s1,__s2))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strcmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strcmp __LIBC_LOCAL_NAME(strcmp)
#endif /* !... */
#endif /* !__local___localdep_strcmp_defined */
__LOCAL_LIBC(sl_find) __ATTR_PURE __ATTR_IN(1) __ATTR_IN(2) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sl_find))(struct _stringlist __KOS_FIXED_CONST *__sl, char const *__name) {
	__SIZE_TYPE__ __i, __count = __sl->sl_cur;
	for (__i = 0; __i < __count; ++__i) {
		char *__s = __sl->sl_str[__i];
		if ((__NAMESPACE_LOCAL_SYM __localdep_strcmp)(__s, __name) == 0)
			return __s;
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sl_find_defined
#define __local___localdep_sl_find_defined
#define __localdep_sl_find __LIBC_LOCAL_NAME(sl_find)
#endif /* !__local___localdep_sl_find_defined */
#endif /* !__local_sl_find_defined */
