/* HASH CRC-32:0xb4388c70 */
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
#ifndef __local_wscanf_defined
#define __local_wscanf_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_vwscanf) || (defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS))
#include <kos/anno.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: vwscanf from wchar */
#ifndef __local___localdep_vwscanf_defined
#define __local___localdep_vwscanf_defined 1
#ifdef __CRT_HAVE_vwscanf
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vwscanf,(__WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args),vwscanf,(__format,__args))
#elif defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS)
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/vwscanf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vwscanf __LIBC_LOCAL_NAME(vwscanf)
#else /* ... */
#undef __local___localdep_vwscanf_defined
#endif /* !... */
#endif /* !__local___localdep_vwscanf_defined */
__LOCAL_LIBC(wscanf) __ATTR_LIBC_WSCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T
(__VLIBCCALL __LIBC_LOCAL_NAME(wscanf))(__WCHAR_TYPE__ const *__restrict __format, ...) __THROWS(...) {
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep_vwscanf(__format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wscanf_defined
#define __local___localdep_wscanf_defined 1
#define __localdep_wscanf __LIBC_LOCAL_NAME(wscanf)
#endif /* !__local___localdep_wscanf_defined */
#else /* __CRT_HAVE_vwscanf || (__CRT_HAVE_vfwscanf && !__NO_STDSTREAMS) */
#undef __local_wscanf_defined
#endif /* !__CRT_HAVE_vwscanf && (!__CRT_HAVE_vfwscanf || __NO_STDSTREAMS) */
#endif /* !__local_wscanf_defined */
