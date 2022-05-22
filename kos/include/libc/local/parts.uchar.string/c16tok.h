/* HASH CRC-32:0x466bdcbd */
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
#ifndef __local_c16tok_defined
#define __local_c16tok_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c16cspn_defined
#define __local___localdep_c16cspn_defined
#if defined(__CRT_HAVE_wcscspn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16cspn,(__CHAR16_TYPE__ const *__haystack, __CHAR16_TYPE__ const *__reject),wcscspn,(__haystack,__reject))
#elif defined(__CRT_HAVE_DOS$wcscspn)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16cspn,(__CHAR16_TYPE__ const *__haystack, __CHAR16_TYPE__ const *__reject),wcscspn,(__haystack,__reject))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcscspn.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16cspn __NAMESPACE_LOCAL_TYPEHAX(__SIZE_TYPE__(__LIBDCALL*)(__CHAR16_TYPE__ const *,__CHAR16_TYPE__ const *),__SIZE_TYPE__(__LIBDCALL&)(__CHAR16_TYPE__ const *,__CHAR16_TYPE__ const *),wcscspn)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c16cspn.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16cspn __LIBC_LOCAL_NAME(c16cspn)
#endif /* !... */
#endif /* !__local___localdep_c16cspn_defined */
#ifndef __local___localdep_c16spn_defined
#define __local___localdep_c16spn_defined
#if defined(__CRT_HAVE_wcsspn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16spn,(__CHAR16_TYPE__ const *__haystack, __CHAR16_TYPE__ const *__accept),wcsspn,(__haystack,__accept))
#elif defined(__CRT_HAVE_DOS$wcsspn)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16spn,(__CHAR16_TYPE__ const *__haystack, __CHAR16_TYPE__ const *__accept),wcsspn,(__haystack,__accept))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsspn.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16spn __NAMESPACE_LOCAL_TYPEHAX(__SIZE_TYPE__(__LIBDCALL*)(__CHAR16_TYPE__ const *,__CHAR16_TYPE__ const *),__SIZE_TYPE__(__LIBDCALL&)(__CHAR16_TYPE__ const *,__CHAR16_TYPE__ const *),wcsspn)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c16spn.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16spn __LIBC_LOCAL_NAME(c16spn)
#endif /* !... */
#endif /* !__local___localdep_c16spn_defined */
__LOCAL_LIBC(c16tok) __ATTR_ACCESS_RO(2) __ATTR_ACCESS_RW(3) __ATTR_ACCESS_RW_OPT(1) __CHAR16_TYPE__ *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16tok))(__CHAR16_TYPE__ *__str, __CHAR16_TYPE__ const *__restrict __delim, __CHAR16_TYPE__ **__restrict __save_ptr) {
	__CHAR16_TYPE__ *__end;
	if (!__str)
		__str = *__save_ptr;
	if (!*__str) {
		*__save_ptr = __str;
		return __NULLPTR;
	}
	__str += (__NAMESPACE_LOCAL_SYM __localdep_c16spn)(__str, __delim);
	if (!*__str) {
		*__save_ptr = __str;
		return __NULLPTR;
	}
	__end = __str + (__NAMESPACE_LOCAL_SYM __localdep_c16cspn)(__str, __delim);
	if (!*__end) {
		*__save_ptr = __end;
		return __str;
	}
	*__end = '\0';
	*__save_ptr = __end + 1;
	return __str;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16tok_defined
#define __local___localdep_c16tok_defined
#define __localdep_c16tok __LIBC_LOCAL_NAME(c16tok)
#endif /* !__local___localdep_c16tok_defined */
#endif /* !__local_c16tok_defined */
