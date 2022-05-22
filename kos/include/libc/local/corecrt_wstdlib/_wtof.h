/* HASH CRC-32:0x57db95c5 */
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
#ifndef __local__wtof_defined
#define __local__wtof_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_wcstod_defined
#define __local___localdep_wcstod_defined
#ifdef __CRT_HAVE_wcstod
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),double,__NOTHROW_NCX,__localdep_wcstod,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr),wcstod,(__nptr,__endptr))
#else /* __CRT_HAVE_wcstod */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcstod.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcstod __LIBC_LOCAL_NAME(wcstod)
#endif /* !__CRT_HAVE_wcstod */
#endif /* !__local___localdep_wcstod_defined */
__LOCAL_LIBC(_wtof) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) double
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_wtof))(__WCHAR_TYPE__ const *__nptr) {
	return (__NAMESPACE_LOCAL_SYM __localdep_wcstod)(__nptr, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__wtof_defined
#define __local___localdep__wtof_defined
#define __localdep__wtof __LIBC_LOCAL_NAME(_wtof)
#endif /* !__local___localdep__wtof_defined */
#endif /* !__local__wtof_defined */
