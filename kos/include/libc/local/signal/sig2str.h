/* HASH CRC-32:0x775698d0 */
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
#ifndef __local_sig2str_defined
#define __local_sig2str_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_sigabbrev_np_defined
#define __local___localdep_sigabbrev_np_defined
#ifdef __CRT_HAVE_sigabbrev_np
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,__localdep_sigabbrev_np,(__signo_t __signum),sigabbrev_np,(__signum))
#elif defined(__CRT_HAVE_signalname)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,__localdep_sigabbrev_np,(__signo_t __signum),signalname,(__signum))
#elif defined(__CRT_HAVE_strsigno)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,__localdep_sigabbrev_np,(__signo_t __signum),strsigno,(__signum))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/sigabbrev_np.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sigabbrev_np __LIBC_LOCAL_NAME(sigabbrev_np)
#endif /* !... */
#endif /* !__local___localdep_sigabbrev_np_defined */
#ifndef __local___localdep_sprintf_defined
#define __local___localdep_sprintf_defined
#if __has_builtin(__builtin_sprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sprintf) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_sprintf,(char *__restrict __buf, char const *__restrict __format, ...),sprintf,{ return __builtin_sprintf(__buf, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_sprintf)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_sprintf)(char *__restrict __buf, char const *__restrict __format, ...) __CASMNAME("sprintf");
#elif defined(__CRT_HAVE__IO_sprintf)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_sprintf)(char *__restrict __buf, char const *__restrict __format, ...) __CASMNAME("_IO_sprintf");
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/sprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sprintf __LIBC_LOCAL_NAME(sprintf)
#endif /* !... */
#endif /* !__local___localdep_sprintf_defined */
#ifndef __local___localdep_strcpy_defined
#define __local___localdep_strcpy_defined
#if __has_builtin(__builtin_strcpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcpy)
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__localdep_strcpy,(char *__restrict __dst, char const *__restrict __src),strcpy,{ return __builtin_strcpy(__dst, __src); })
#elif defined(__CRT_HAVE_strcpy)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__localdep_strcpy,(char *__restrict __dst, char const *__restrict __src),strcpy,(__dst,__src))
#elif defined(__CRT_HAVE__mbscpy)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__localdep_strcpy,(char *__restrict __dst, char const *__restrict __src),_mbscpy,(__dst,__src))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strcpy __LIBC_LOCAL_NAME(strcpy)
#endif /* !... */
#endif /* !__local___localdep_strcpy_defined */
__NAMESPACE_LOCAL_END
#include <asm/os/signal.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(sig2str) __ATTR_NONNULL((2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sig2str))(__signo_t __signo, char __buf[32]) {
	char const *__name = (__NAMESPACE_LOCAL_SYM __localdep_sigabbrev_np)(__signo);
	if (__name) {
		/* Predefined name. */
		(__NAMESPACE_LOCAL_SYM __localdep_strcpy)(__buf, __name);
		return 0;
	}
#if defined(__SIGRTMIN) && defined(__SIGRTMAX)
	if (__signo >= __SIGRTMIN && __signo <= __SIGRTMAX) {
		/* Realtime . */
		(__NAMESPACE_LOCAL_SYM __localdep_sprintf)(__buf, "RTMIN+%u", (unsigned int)(__signo - __SIGRTMIN));
		return 0;
	}
#endif /* __SIGRTMIN && __SIGRTMAX */
	return -1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sig2str_defined
#define __local___localdep_sig2str_defined
#define __localdep_sig2str __LIBC_LOCAL_NAME(sig2str)
#endif /* !__local___localdep_sig2str_defined */
#endif /* !__local_sig2str_defined */
