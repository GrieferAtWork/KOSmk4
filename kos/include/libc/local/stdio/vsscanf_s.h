/* HASH CRC-32:0xd456b1e9 */
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
#ifndef __local_vsscanf_s_defined
#define __local_vsscanf_s_defined
#include <__crt.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__vsscanf_s_l_defined
#define __local___localdep__vsscanf_s_l_defined
#ifdef __CRT_HAVE__vsscanf_s_l
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __ATTR_LIBC_SCANF(2, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep__vsscanf_s_l,(char const *__buf, char const *__format, __locale_t __locale, __builtin_va_list __args),_vsscanf_s_l,(__buf,__format,__locale,__args))
#else /* __CRT_HAVE__vsscanf_s_l */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/_vsscanf_s_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__vsscanf_s_l __LIBC_LOCAL_NAME(_vsscanf_s_l)
#endif /* !__CRT_HAVE__vsscanf_s_l */
#endif /* !__local___localdep__vsscanf_s_l_defined */
__LOCAL_LIBC(vsscanf_s) __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __ATTR_LIBC_SCANF(2, 0) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(vsscanf_s))(char const *__buf, char const *__format, __builtin_va_list __args) {
	return (__NAMESPACE_LOCAL_SYM __localdep__vsscanf_s_l)(__buf, __format, __NULLPTR, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vsscanf_s_defined
#define __local___localdep_vsscanf_s_defined
#define __localdep_vsscanf_s __LIBC_LOCAL_NAME(vsscanf_s)
#endif /* !__local___localdep_vsscanf_s_defined */
#endif /* !__local_vsscanf_s_defined */
