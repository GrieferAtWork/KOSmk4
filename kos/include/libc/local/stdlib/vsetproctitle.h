/* HASH CRC-32:0x4cec6df1 */
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
#ifndef __local_vsetproctitle_defined
#define __local_vsetproctitle_defined
#include <__crt.h>
#include <linux/prctl.h>
#if ((defined(__CRT_HAVE_prctl) && defined(PR_SET_NAME)) || ((defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current) || defined(__CRT_HAVE_thr_self)) && (defined(__CRT_HAVE_pthread_setname_np) || defined(__CRT_HAVE_pthread_set_name_np)))) && (defined(__TASK_COMM_LEN) || defined(__CRT_HAVE_vstrdupf) || defined(__CRT_HAVE_vasprintf) || ((defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free))))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#elif defined(__CRT_HAVE___libc_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),__libc_free,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
#if !defined(__local___localdep_prctl_defined) && defined(__CRT_HAVE_prctl)
#define __local___localdep_prctl_defined
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(,int,__NOTHROW_NCX,__localdep_prctl,(__STDC_INT_AS_UINT_T __command),prctl,(__command),__command,4,(__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t))
#endif /* !__local___localdep_prctl_defined && __CRT_HAVE_prctl */
#ifndef __local___localdep_pthread_self_defined
#define __local___localdep_pthread_self_defined
#ifdef __CRT_HAVE_pthread_self
__NAMESPACE_LOCAL_END
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pthread_t,__NOTHROW,__localdep_pthread_self,(void),pthread_self,())
#elif defined(__CRT_HAVE_thrd_current)
__NAMESPACE_LOCAL_END
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pthread_t,__NOTHROW,__localdep_pthread_self,(void),thrd_current,())
#elif defined(__CRT_HAVE_thr_self)
__NAMESPACE_LOCAL_END
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pthread_t,__NOTHROW,__localdep_pthread_self,(void),thr_self,())
#else /* ... */
#undef __local___localdep_pthread_self_defined
#endif /* !... */
#endif /* !__local___localdep_pthread_self_defined */
#ifndef __local___localdep_pthread_setname_np_defined
#define __local___localdep_pthread_setname_np_defined
#ifdef __CRT_HAVE_pthread_setname_np
__NAMESPACE_LOCAL_END
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_RO(2),__errno_t,__NOTHROW_NCX,__localdep_pthread_setname_np,(__pthread_t __target_thread, const char *__name),pthread_setname_np,(__target_thread,__name))
#elif defined(__CRT_HAVE_pthread_set_name_np)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_RO(2),__errno_t,__NOTHROW_NCX,__localdep_pthread_setname_np,(__pthread_t __target_thread, const char *__name),pthread_set_name_np,(__target_thread,__name))
#else /* ... */
#undef __local___localdep_pthread_setname_np_defined
#endif /* !... */
#endif /* !__local___localdep_pthread_setname_np_defined */
#ifndef __local___localdep_vsnprintf_defined
#define __local___localdep_vsnprintf_defined
#if __has_builtin(__builtin_vsnprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vsnprintf)
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_WRS(1, 2) __ATTR_LIBC_PRINTF(3, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vsnprintf,(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, __builtin_va_list __args),vsnprintf,{ return __builtin_vsnprintf(__buf, __buflen, __format, __args); })
#elif defined(__CRT_HAVE_vsnprintf)
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_WRS(1, 2) __ATTR_LIBC_PRINTF(3, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vsnprintf,(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, __builtin_va_list __args),vsnprintf,(__buf,__buflen,__format,__args))
#elif defined(__CRT_HAVE___vsnprintf)
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_WRS(1, 2) __ATTR_LIBC_PRINTF(3, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vsnprintf,(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, __builtin_va_list __args),__vsnprintf,(__buf,__buflen,__format,__args))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/vsnprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vsnprintf __LIBC_LOCAL_NAME(vsnprintf)
#endif /* !... */
#endif /* !__local___localdep_vsnprintf_defined */
#ifndef __local___localdep_vstrdupf_defined
#define __local___localdep_vstrdupf_defined
#ifdef __CRT_HAVE_vstrdupf
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_LIBC_PRINTF(1, 0),char *,__NOTHROW_NCX,__localdep_vstrdupf,(char const *__restrict __format, __builtin_va_list __args),vstrdupf,(__format,__args))
#elif defined(__CRT_HAVE_vasprintf) || ((defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)))
__NAMESPACE_LOCAL_END
#include <libc/local/string/vstrdupf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vstrdupf __LIBC_LOCAL_NAME(vstrdupf)
#else /* ... */
#undef __local___localdep_vstrdupf_defined
#endif /* !... */
#endif /* !__local___localdep_vstrdupf_defined */
__LOCAL_LIBC(vsetproctitle) __ATTR_ACCESS_RO(1) __ATTR_LIBC_PRINTF(1, 0) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(vsetproctitle))(char const *__format, __builtin_va_list __args) {
	/* Load+fill a buffer for the fully qualified program name. */
#ifdef __TASK_COMM_LEN
	char __namebuf[__TASK_COMM_LEN];
	(__NAMESPACE_LOCAL_SYM __localdep_vsnprintf)(__namebuf, __TASK_COMM_LEN - 1, __format, __args);
	__namebuf[__TASK_COMM_LEN - 1] = '\0';
#else /* __TASK_COMM_LEN */
	char *__namebuf = (__NAMESPACE_LOCAL_SYM __localdep_vstrdupf)(__format, __args);
	if __unlikely(!__namebuf)
		return;
#endif /* !__TASK_COMM_LEN */

	/* Tell the kernel about our new program name. */
#if defined(__CRT_HAVE_prctl) && defined(PR_SET_NAME)
	(__NAMESPACE_LOCAL_SYM __localdep_prctl)(PR_SET_NAME, __namebuf);
#else /* __CRT_HAVE_prctl && PR_SET_NAME */
	(__NAMESPACE_LOCAL_SYM __localdep_pthread_setname_np)((__NAMESPACE_LOCAL_SYM __localdep_pthread_self)(), __namebuf);
#endif /* !__CRT_HAVE_prctl || !PR_SET_NAME */

	/* Free the name buffer if it was allocated dynamically. */
#if !defined(__TASK_COMM_LEN) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free))
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__namebuf);
#endif /* !__TASK_COMM_LEN && (__CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vsetproctitle_defined
#define __local___localdep_vsetproctitle_defined
#define __localdep_vsetproctitle __LIBC_LOCAL_NAME(vsetproctitle)
#endif /* !__local___localdep_vsetproctitle_defined */
#else /* ((__CRT_HAVE_prctl && PR_SET_NAME) || ((__CRT_HAVE_pthread_self || __CRT_HAVE_thrd_current || __CRT_HAVE_thr_self) && (__CRT_HAVE_pthread_setname_np || __CRT_HAVE_pthread_set_name_np))) && (__TASK_COMM_LEN || __CRT_HAVE_vstrdupf || __CRT_HAVE_vasprintf || ((__CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free))) */
#undef __local_vsetproctitle_defined
#endif /* ((!__CRT_HAVE_prctl || !PR_SET_NAME) && ((!__CRT_HAVE_pthread_self && !__CRT_HAVE_thrd_current && !__CRT_HAVE_thr_self) || (!__CRT_HAVE_pthread_setname_np && !__CRT_HAVE_pthread_set_name_np))) || (!__TASK_COMM_LEN && !__CRT_HAVE_vstrdupf && !__CRT_HAVE_vasprintf && ((!__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_free && !__CRT_HAVE_cfree && !__CRT_HAVE___libc_free))) */
#endif /* !__local_vsetproctitle_defined */
