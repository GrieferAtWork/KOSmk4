/* HASH CRC-32:0xbb5eea48 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__vwscanf_l_defined
#if (defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS)) || defined(__CRT_HAVE_vwscanf)
#define __local__vwscanf_l_defined 1
#include <kos/anno.h>
/* Dependency: "vwscanf" from "wchar" */
#ifndef ____localdep_vwscanf_defined
#define ____localdep_vwscanf_defined 1
#ifdef __std___localdep_vwscanf_defined
__NAMESPACE_STD_USING(__localdep_vwscanf)
#elif defined(__CRT_HAVE_vwscanf)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_LIBC_WSCANF(1, 0),__STDC_INT_AS_SIZE_T,,__localdep_vwscanf,(__WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args),vwscanf,(__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS)
#include <local/wchar/vwscanf.h>
#define __localdep_vwscanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwscanf))
#else /* CUSTOM: vwscanf */
#undef ____localdep_vwscanf_defined
#endif /* vwscanf... */
#endif /* !____localdep_vwscanf_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_vwscanf_l) __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T
(__LIBCCALL __LIBC_LOCAL_NAME(_vwscanf_l))(__WCHAR_TYPE__ const *__format,
                                           __locale_t __locale,
                                           __builtin_va_list __args) __THROWS(...) {
#line 2153 "kos/src/libc/magic/wchar.c"
	(void)__locale;
	return __localdep_vwscanf(__format, __args);
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS)) || defined(__CRT_HAVE_vwscanf) */
#endif /* !__local__vwscanf_l_defined */
