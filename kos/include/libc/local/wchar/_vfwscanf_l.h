/* HASH CRC-32:0x3d1952bb */
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
#ifndef __local__vfwscanf_l_defined
#define __local__vfwscanf_l_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_vfwscanf
#include <features.h>
#include <hybrid/typecore.h>
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_vfwscanf_defined
#define __local___localdep_vfwscanf_defined 1
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vfwscanf,(__FILE *__restrict __stream, __WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args),vfwscanf,(__stream,__format,__args))
#endif /* !__local___localdep_vfwscanf_defined */
__LOCAL_LIBC(_vfwscanf_l) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(__LIBCCALL __LIBC_LOCAL_NAME(_vfwscanf_l))(__FILE *__stream, __WCHAR_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args) __THROWS(...) {
	(void)__locale;
	return __localdep_vfwscanf(__stream, __format, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__vfwscanf_l_defined
#define __local___localdep__vfwscanf_l_defined 1
#define __localdep__vfwscanf_l __LIBC_LOCAL_NAME(_vfwscanf_l)
#endif /* !__local___localdep__vfwscanf_l_defined */
#else /* __CRT_HAVE_vfwscanf */
#undef __local__vfwscanf_l_defined
#endif /* !__CRT_HAVE_vfwscanf */
#endif /* !__local__vfwscanf_l_defined */
