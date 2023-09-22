/* HASH CRC-32:0xff8e7a54 */
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
#ifndef __local__execute_onexit_table_defined
#define __local__execute_onexit_table_defined
#include <__crt.h>
#include <bits/crt/dos/corecrt_startup.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__initialize_onexit_table_defined
#define __local___localdep__initialize_onexit_table_defined
#ifdef __CRT_HAVE__initialize_onexit_table
__COMPILER_CREDIRECT(__LIBC,,int,__NOTHROW_NCX,__LIBDCALL,__localdep__initialize_onexit_table,(struct _onexit_table_t *__self),_initialize_onexit_table,(__self))
#else /* __CRT_HAVE__initialize_onexit_table */
__NAMESPACE_LOCAL_END
#include <libc/local/corecrt_startup/_initialize_onexit_table.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__initialize_onexit_table __LIBC_LOCAL_NAME(_initialize_onexit_table)
#endif /* !__CRT_HAVE__initialize_onexit_table */
#endif /* !__local___localdep__initialize_onexit_table_defined */
#ifndef __local___localdep__initterm_e_defined
#define __local___localdep__initterm_e_defined
#ifdef __CRT_HAVE__initterm_e
__COMPILER_CREDIRECT(__LIBC,,int,__NOTHROW_NCX,__LIBDCALL,__localdep__initterm_e,(_onexit_t *__start, _onexit_t *__end),_initterm_e,(__start,__end))
#else /* __CRT_HAVE__initterm_e */
__NAMESPACE_LOCAL_END
#include <libc/local/corecrt_startup/_initterm_e.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__initterm_e __LIBC_LOCAL_NAME(_initterm_e)
#endif /* !__CRT_HAVE__initterm_e */
#endif /* !__local___localdep__initterm_e_defined */
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
__LOCAL_LIBC(_execute_onexit_table) int
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_execute_onexit_table))(struct _onexit_table_t *__self) {
	int __result;
	_onexit_t *__first = (_onexit_t *)__self->_first;
	_onexit_t *__last  = (_onexit_t *)__self->_last;
	(void)(__NAMESPACE_LOCAL_SYM __localdep__initialize_onexit_table)(__self);
	__result = (__NAMESPACE_LOCAL_SYM __localdep__initterm_e)(__first, __last);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__first);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__execute_onexit_table_defined
#define __local___localdep__execute_onexit_table_defined
#define __localdep__execute_onexit_table __LIBC_LOCAL_NAME(_execute_onexit_table)
#endif /* !__local___localdep__execute_onexit_table_defined */
#endif /* !__local__execute_onexit_table_defined */
