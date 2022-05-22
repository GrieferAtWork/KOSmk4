/* HASH CRC-32:0xd736cef5 */
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
#ifndef __local_GetCurrentDirName_defined
#define __local_GetCurrentDirName_defined
#include <__crt.h>
#ifdef __CRT_HAVE_GetCwd
#include <kos/anno.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_GetCwd_defined
#define __local___localdep_GetCwd_defined
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUTS(1, 2),char *,__THROWING,__localdep_GetCwd,(char *__buf, __SIZE_TYPE__ __bufsize),GetCwd,(__buf,__bufsize))
#endif /* !__local___localdep_GetCwd_defined */
__LOCAL_LIBC(GetCurrentDirName) __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED char *
(__LIBCCALL __LIBC_LOCAL_NAME(GetCurrentDirName))(void) __THROWS(...) {
	return (__NAMESPACE_LOCAL_SYM __localdep_GetCwd)(__NULLPTR, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_GetCurrentDirName_defined
#define __local___localdep_GetCurrentDirName_defined
#define __localdep_GetCurrentDirName __LIBC_LOCAL_NAME(GetCurrentDirName)
#endif /* !__local___localdep_GetCurrentDirName_defined */
#else /* __CRT_HAVE_GetCwd */
#undef __local_GetCurrentDirName_defined
#endif /* !__CRT_HAVE_GetCwd */
#endif /* !__local_GetCurrentDirName_defined */
