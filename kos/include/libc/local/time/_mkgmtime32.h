/* HASH CRC-32:0x32a06808 */
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
#ifndef __local__mkgmtime32_defined
#define __local__mkgmtime32_defined
#include <__crt.h>
#include <bits/types.h>
#include <features.h>
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__mkgmtime64_defined
#define __local___localdep__mkgmtime64_defined
#if defined(__CRT_HAVE__mkgmtime32) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,__localdep__mkgmtime64,(struct __NAMESPACE_STD_SYM tm __KOS_FIXED_CONST *__tp),_mkgmtime32,(__tp))
#elif defined(__CRT_HAVE__mkgmtime64)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,__localdep__mkgmtime64,(struct __NAMESPACE_STD_SYM tm __KOS_FIXED_CONST *__tp),_mkgmtime64,(__tp))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/time/_mkgmtime64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__mkgmtime64 __LIBC_LOCAL_NAME(_mkgmtime64)
#endif /* !... */
#endif /* !__local___localdep__mkgmtime64_defined */
__LOCAL_LIBC(_mkgmtime32) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __time32_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mkgmtime32))(struct __NAMESPACE_STD_SYM tm __KOS_FIXED_CONST *__tp) {

	return (__time32_t)(__NAMESPACE_LOCAL_SYM __localdep__mkgmtime64)(__tp);










}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mkgmtime32_defined
#define __local___localdep__mkgmtime32_defined
#define __localdep__mkgmtime32 __LIBC_LOCAL_NAME(_mkgmtime32)
#endif /* !__local___localdep__mkgmtime32_defined */
#endif /* !__local__mkgmtime32_defined */
