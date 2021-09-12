/* HASH CRC-32:0x636932cf */
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
#ifndef __local_c32tomb_defined
#define __local_c32tomb_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_uchar_c32rtomb_defined
#define __local___localdep_uchar_c32rtomb_defined 1
#if defined(__CRT_HAVE_wcrtomb) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <bits/crt/mbstate.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_uchar_c32rtomb,(char *__restrict __str, __CHAR32_TYPE__ __wc, struct __mbstate *__mbs),wcrtomb,(__str,__wc,__mbs))
#elif defined(__CRT_HAVE_KOS$wcrtomb)
__NAMESPACE_LOCAL_END
#include <bits/crt/mbstate.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_uchar_c32rtomb,(char *__restrict __str, __CHAR32_TYPE__ __wc, struct __mbstate *__mbs),wcrtomb,(__str,__wc,__mbs))
#elif defined(__CRT_HAVE_c32rtomb) && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <bits/crt/mbstate.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_uchar_c32rtomb,(char *__restrict __str, __CHAR32_TYPE__ __wc, struct __mbstate *__mbs),c32rtomb,(__str,__wc,__mbs))
#elif defined(__CRT_HAVE_KOS$c32rtomb)
__NAMESPACE_LOCAL_END
#include <bits/crt/mbstate.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_uchar_c32rtomb,(char *__restrict __str, __CHAR32_TYPE__ __wc, struct __mbstate *__mbs),c32rtomb,(__str,__wc,__mbs))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcrtomb.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_uchar_c32rtomb __NAMESPACE_LOCAL_TYPEHAX(__SIZE_TYPE__(__LIBKCALL*)(char *__restrict,__CHAR32_TYPE__,struct __mbstate *),__SIZE_TYPE__(__LIBKCALL&)(char *__restrict,__CHAR32_TYPE__,struct __mbstate *),wcrtomb)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/uchar_c32rtomb.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_uchar_c32rtomb __LIBC_LOCAL_NAME(uchar_c32rtomb)
#endif /* !... */
#endif /* !__local___localdep_uchar_c32rtomb_defined */
__LOCAL_LIBC(c32tomb) int
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32tomb))(char *__str, __CHAR32_TYPE__ __wc) {
	return __NAMESPACE_LOCAL_SYM __localdep_uchar_c32rtomb(__str, __wc, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32tomb_defined
#define __local___localdep_c32tomb_defined 1
#define __localdep_c32tomb __LIBC_LOCAL_NAME(c32tomb)
#endif /* !__local___localdep_c32tomb_defined */
#endif /* !__local_c32tomb_defined */
