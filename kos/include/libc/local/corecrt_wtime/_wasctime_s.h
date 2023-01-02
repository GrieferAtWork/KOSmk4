/* HASH CRC-32:0xe55282fa */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__wasctime_s_defined
#define __local__wasctime_s_defined
#include <__crt.h>
#include <bits/types.h>
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_asctime_r_defined
#define __local___localdep_asctime_r_defined
#ifdef __CRT_HAVE_asctime_r
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),char *,__NOTHROW_NCX,__localdep_asctime_r,(struct __NAMESPACE_STD_SYM tm const *__restrict __tp, char __buf[26]),asctime_r,(__tp,__buf))
#else /* __CRT_HAVE_asctime_r */
__NAMESPACE_LOCAL_END
#include <libc/local/time/asctime_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_asctime_r __LIBC_LOCAL_NAME(asctime_r)
#endif /* !__CRT_HAVE_asctime_r */
#endif /* !__local___localdep_asctime_r_defined */
__LOCAL_LIBC(_wasctime_s) __ATTR_IN(3) __ATTR_OUTS(1, 2) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_wasctime_s))(__WCHAR_TYPE__ *__buf, __SIZE_TYPE__ __buflen, struct __NAMESPACE_STD_SYM tm const *__tp) {
	char __abuf[26], *__ptr;
	unsigned int __i;
	if __unlikely(__buflen < 26)
		return __ERANGE;
	/* asctime --> ASCiiTIME --> No unicode here --> directly  copy
	 * This is also why its  kind of <redacted for profanity>  that
	 * a function like `_wasctime_s()' even exists, but whatever... */
	__ptr = (__NAMESPACE_LOCAL_SYM __localdep_asctime_r)(__tp, __abuf);
	for (__i = 0; __i < 26; ++__i)
		__buf[__i] = (__WCHAR_TYPE__)__ptr[__i];
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__wasctime_s_defined
#define __local___localdep__wasctime_s_defined
#define __localdep__wasctime_s __LIBC_LOCAL_NAME(_wasctime_s)
#endif /* !__local___localdep__wasctime_s_defined */
#endif /* !__local__wasctime_s_defined */
