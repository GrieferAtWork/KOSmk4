/* HASH CRC-32:0xaa17e97f */
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
#ifndef __local_signalname_defined
#define __local_signalname_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: strsignal_s from string */
#ifndef __local___localdep_strsignal_s_defined
#define __local___localdep_strsignal_s_defined 1
#ifdef __CRT_HAVE_strsignal_s
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,__localdep_strsignal_s,(__signo_t __signum),strsignal_s,(__signum))
#else /* __CRT_HAVE_strsignal_s */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strsignal_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strsignal_s __LIBC_LOCAL_NAME(strsignal_s)
#endif /* !__CRT_HAVE_strsignal_s */
#endif /* !__local___localdep_strsignal_s_defined */
/* >> signalname(3)
 * Same as `strsignal_s(3)', but don't include the leading
 * `SIG*' prefix normally prepended before the signal name. */
__LOCAL_LIBC(signalname) __ATTR_CONST __ATTR_WUNUSED char const *
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(signalname))(__signo_t __signum) {
	char const *__result;
	__result = __localdep_strsignal_s(__signum);
	if (__result) {
		if (__result[0] == 'S' &&
		    __result[1] == 'I' &&
		    __result[2] == 'G')
			__result += 3;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_signalname_defined
#define __local___localdep_signalname_defined 1
#define __localdep_signalname __LIBC_LOCAL_NAME(signalname)
#endif /* !__local___localdep_signalname_defined */
#endif /* !__local_signalname_defined */
