/* HASH CRC-32:0x96267db5 */
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
#ifndef __local__wasctime_defined
#define __local__wasctime_defined
#include <__crt.h>
#include <bits/types.h>
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__wasctime_s_defined
#define __local___localdep__wasctime_s_defined
#ifdef __CRT_HAVE__wasctime_s
__CREDIRECT(__ATTR_IN(3) __ATTR_OUTS(1, 2),__errno_t,__NOTHROW_NCX,__localdep__wasctime_s,(__WCHAR_TYPE__ *__buf, __SIZE_TYPE__ __buflen, struct __NAMESPACE_STD_SYM tm const *__tp),_wasctime_s,(__buf,__buflen,__tp))
#else /* __CRT_HAVE__wasctime_s */
__NAMESPACE_LOCAL_END
#include <libc/local/corecrt_wtime/_wasctime_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__wasctime_s __LIBC_LOCAL_NAME(_wasctime_s)
#endif /* !__CRT_HAVE__wasctime_s */
#endif /* !__local___localdep__wasctime_s_defined */
__LOCAL_LIBC(_wasctime) __ATTR_WUNUSED __ATTR_IN(1) __WCHAR_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_wasctime))(struct __NAMESPACE_STD_SYM tm const *__tp) {
	static __WCHAR_TYPE__ __wasctime_retbuf[26] = { 0 };
	return (__NAMESPACE_LOCAL_SYM __localdep__wasctime_s)(__wasctime_retbuf, 26, __tp) ? __NULLPTR : __wasctime_retbuf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__wasctime_defined
#define __local___localdep__wasctime_defined
#define __localdep__wasctime __LIBC_LOCAL_NAME(_wasctime)
#endif /* !__local___localdep__wasctime_defined */
#endif /* !__local__wasctime_defined */
