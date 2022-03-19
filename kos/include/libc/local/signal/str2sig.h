/* HASH CRC-32:0xc9a278c9 */
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
#ifndef __local_str2sig_defined
#define __local_str2sig_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_islower_defined
#define __local___localdep_islower_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_islower) && defined(__CRT_HAVE_islower)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_islower,(int __ch),islower,{ return __crt_islower(__ch); })
#elif defined(__crt_islower)
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_islower)(int __ch) { return __crt_islower(__ch); }
#elif __has_builtin(__builtin_islower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_islower)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_islower,(int __ch),islower,{ return __builtin_islower(__ch); })
#elif defined(__CRT_HAVE_islower)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_islower,(int __ch),islower,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/islower.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_islower __LIBC_LOCAL_NAME(islower)
#endif /* !... */
#endif /* !__local___localdep_islower_defined */
#ifndef __local___localdep_signalnumber_defined
#define __local___localdep_signalnumber_defined
#ifdef __CRT_HAVE_signalnumber
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__signo_t,__NOTHROW_NCX,__localdep_signalnumber,(const char *__name),signalnumber,(__name))
#else /* __CRT_HAVE_signalnumber */
__NAMESPACE_LOCAL_END
#include <libc/local/signal/signalnumber.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_signalnumber __LIBC_LOCAL_NAME(signalnumber)
#endif /* !__CRT_HAVE_signalnumber */
#endif /* !__local___localdep_signalnumber_defined */
__LOCAL_LIBC(str2sig) __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(str2sig))(const char *__name, __signo_t *__p_signo) {
	__signo_t __result;
	__SIZE_TYPE__ __i;
	if (__name[0] == 'S' && __name[1] == 'I' && __name[2] == 'G')
		return -1;
	for (__i = 0; __name[__i]; ++__i) {
		if ((__NAMESPACE_LOCAL_SYM __localdep_islower)(__name[__i]))
			return -1;
	}
	__result = (__NAMESPACE_LOCAL_SYM __localdep_signalnumber)(__name);
	if (__result != 0) {
		*__p_signo = __result;
		return 0;
	}
	return -1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_str2sig_defined
#define __local___localdep_str2sig_defined
#define __localdep_str2sig __LIBC_LOCAL_NAME(str2sig)
#endif /* !__local___localdep_str2sig_defined */
#endif /* !__local_str2sig_defined */
