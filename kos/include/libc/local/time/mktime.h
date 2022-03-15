/* HASH CRC-32:0x2d26c966 */
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
#ifndef __local_mktime_defined
#define __local_mktime_defined
#include <__crt.h>
#include <features.h>
#include <bits/types.h>
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mktime64_defined
#define __local___localdep_mktime64_defined
#if defined(__CRT_HAVE_mktime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,__localdep_mktime64,(struct __NAMESPACE_STD_SYM tm *__tp),mktime,(__tp))
#elif defined(__CRT_HAVE_mktime64)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,__localdep_mktime64,(struct __NAMESPACE_STD_SYM tm *__tp),mktime64,(__tp))
#elif defined(__CRT_HAVE__mktime64)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,__localdep_mktime64,(struct __NAMESPACE_STD_SYM tm *__tp),_mktime64,(__tp))
#elif defined(__CRT_HAVE_timelocal64)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,__localdep_mktime64,(struct __NAMESPACE_STD_SYM tm *__tp),timelocal64,(__tp))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/time/mktime64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mktime64 __LIBC_LOCAL_NAME(mktime64)
#endif /* !... */
#endif /* !__local___localdep_mktime64_defined */
__NAMESPACE_LOCAL_END
#ifndef __yearstodays
#define __yearstodays(__n_years) (((146097 * (__n_years)) / 400) /*-1*/) /* rounding error? */
#endif /* !__yearstodays */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(mktime) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __TM_TYPE(time)
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mktime))(struct __NAMESPACE_STD_SYM tm *__tp) {

	return (__TM_TYPE(time))(__NAMESPACE_LOCAL_SYM __localdep_mktime64)(__tp);












}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mktime_defined
#define __local___localdep_mktime_defined
#define __localdep_mktime __LIBC_LOCAL_NAME(mktime)
#endif /* !__local___localdep_mktime_defined */
#endif /* !__local_mktime_defined */
