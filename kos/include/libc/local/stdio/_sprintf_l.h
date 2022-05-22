/* HASH CRC-32:0x5badc8f7 */
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
#ifndef __local__sprintf_l_defined
#define __local__sprintf_l_defined
#include <__crt.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__vsprintf_l_defined
#define __local___localdep__vsprintf_l_defined
#ifdef __CRT_HAVE__vsprintf_l
__CREDIRECT(__ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1) __ATTR_LIBC_PRINTF(2, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep__vsprintf_l,(char *__buf, char const *__format, __locale_t __locale, __builtin_va_list __args),_vsprintf_l,(__buf,__format,__locale,__args))
#else /* __CRT_HAVE__vsprintf_l */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/_vsprintf_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__vsprintf_l __LIBC_LOCAL_NAME(_vsprintf_l)
#endif /* !__CRT_HAVE__vsprintf_l */
#endif /* !__local___localdep__vsprintf_l_defined */
__LOCAL_LIBC(_sprintf_l) __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1) __ATTR_LIBC_PRINTF(2, 4) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__VLIBCCALL __LIBC_LOCAL_NAME(_sprintf_l))(char *__buf, char const *__format, __locale_t __locale, ...) {
	__STDC_INT_AS_SSIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __locale);
	__result = (__NAMESPACE_LOCAL_SYM __localdep__vsprintf_l)(__buf, __format, __locale, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__sprintf_l_defined
#define __local___localdep__sprintf_l_defined
#define __localdep__sprintf_l __LIBC_LOCAL_NAME(_sprintf_l)
#endif /* !__local___localdep__sprintf_l_defined */
#endif /* !__local__sprintf_l_defined */
