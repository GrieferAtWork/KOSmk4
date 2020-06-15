/* HASH CRC-32:0x9f6ee319 */
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
#ifndef __local__sscanf_s_l_defined
#define __local__sscanf_s_l_defined 1
#include <__crt.h>
#include <features.h>
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: _vsscanf_s_l from stdio */
#ifndef __local___localdep__vsscanf_s_l_defined
#define __local___localdep__vsscanf_s_l_defined 1
#ifdef __CRT_HAVE__vsscanf_l
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 4) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep__vsscanf_s_l,(char const *__restrict __input, char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),_vsscanf_l,(__input,__format,__locale,__args))
#elif defined(__CRT_HAVE__vsscanf_s_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 4) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep__vsscanf_s_l,(char const *__restrict __input, char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),_vsscanf_s_l,(__input,__format,__locale,__args))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/stdio/_vsscanf_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__vsscanf_s_l __LIBC_LOCAL_NAME(_vsscanf_l)
#endif /* !... */
#endif /* !__local___localdep__vsscanf_s_l_defined */
__LOCAL_LIBC(_sscanf_s_l) __ATTR_LIBC_SCANF(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(__VLIBCCALL __LIBC_LOCAL_NAME(_sscanf_s_l))(char const *__restrict __input, char const *__restrict __format, __locale_t __locale, ...) __THROWS(...) {
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __locale);
	__result = __localdep__vsscanf_s_l(__input, __format, __locale, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__sscanf_s_l_defined
#define __local___localdep__sscanf_s_l_defined 1
#define __localdep__sscanf_s_l __LIBC_LOCAL_NAME(_sscanf_s_l)
#endif /* !__local___localdep__sscanf_s_l_defined */
#endif /* !__local__sscanf_s_l_defined */
