/* HASH CRC-32:0xe94a75e4 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_setproctitle_defined
#define __local_setproctitle_defined
#include <__crt.h>
#include <linux/prctl.h>
#if ((defined(__CRT_HAVE_prctl) && defined(PR_SET_NAME)) || ((defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current) || defined(__CRT_HAVE_thr_self) || defined(__CRT_HAVE_cthread_self)) && (defined(__CRT_HAVE_pthread_setname_np) || defined(__CRT_HAVE_pthread_set_name_np) || defined(__CRT_HAVE_cthread_set_name)))) && (defined(__TASK_COMM_LEN) || defined(__CRT_HAVE_vstrdupf) || defined(__CRT_HAVE_vasprintf) || ((defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free))))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_vsetproctitle_defined
#define __local___localdep_vsetproctitle_defined
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/vsetproctitle.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vsetproctitle __LIBC_LOCAL_NAME(vsetproctitle)
#endif /* !__local___localdep_vsetproctitle_defined */
__LOCAL_LIBC(setproctitle) __ATTR_IN(1) __ATTR_LIBC_PRINTF(1, 2) void
__NOTHROW_NCX(__VLIBCCALL __LIBC_LOCAL_NAME(setproctitle))(char const *__format, ...) {
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	(__NAMESPACE_LOCAL_SYM __localdep_vsetproctitle)(__format, __args);
	__builtin_va_end(__args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_setproctitle_defined
#define __local___localdep_setproctitle_defined
#define __localdep_setproctitle __LIBC_LOCAL_NAME(setproctitle)
#endif /* !__local___localdep_setproctitle_defined */
#else /* ((__CRT_HAVE_prctl && PR_SET_NAME) || ((__CRT_HAVE_pthread_self || __CRT_HAVE_thrd_current || __CRT_HAVE_thr_self || __CRT_HAVE_cthread_self) && (__CRT_HAVE_pthread_setname_np || __CRT_HAVE_pthread_set_name_np || __CRT_HAVE_cthread_set_name))) && (__TASK_COMM_LEN || __CRT_HAVE_vstrdupf || __CRT_HAVE_vasprintf || ((__CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free))) */
#undef __local_setproctitle_defined
#endif /* ((!__CRT_HAVE_prctl || !PR_SET_NAME) && ((!__CRT_HAVE_pthread_self && !__CRT_HAVE_thrd_current && !__CRT_HAVE_thr_self && !__CRT_HAVE_cthread_self) || (!__CRT_HAVE_pthread_setname_np && !__CRT_HAVE_pthread_set_name_np && !__CRT_HAVE_cthread_set_name))) || (!__TASK_COMM_LEN && !__CRT_HAVE_vstrdupf && !__CRT_HAVE_vasprintf && ((!__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_free && !__CRT_HAVE_cfree && !__CRT_HAVE___libc_free))) */
#endif /* !__local_setproctitle_defined */
