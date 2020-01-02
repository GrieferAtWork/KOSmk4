/* HASH CRC-32:0xcf96a22f */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_mtx_init_defined
#ifdef __CRT_HAVE_pthread_mutex_init
#define __local_mtx_init_defined 1
#include <bits/threads.h>

#include <bits/pthreadvalues.h>

#include <bits/pthreadtypes.h>
/* Dependency: "pthread_mutex_init" */
#ifndef ____localdep_pthread_mutex_init_defined
#define ____localdep_pthread_mutex_init_defined 1
#ifdef __CRT_HAVE_pthread_mutex_init
/* Initialize a mutex */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_pthread_mutex_init,(__pthread_mutex_t *__mutex, __pthread_mutexattr_t const *__mutexattr),pthread_mutex_init,(__mutex,__mutexattr))
#else /* LIBC: pthread_mutex_init */
#undef ____localdep_pthread_mutex_init_defined
#endif /* pthread_mutex_init... */
#endif /* !____localdep_pthread_mutex_init_defined */

/* Dependency: "pthread_mutexattr_init" */
#ifndef ____localdep_pthread_mutexattr_init_defined
#define ____localdep_pthread_mutexattr_init_defined 1
#ifdef __CRT_HAVE_pthread_mutexattr_init
/* Initialize mutex attribute object ATTR with default attributes (kind is PTHREAD_MUTEX_TIMED_NP) */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_pthread_mutexattr_init,(__pthread_mutexattr_t *__attr),pthread_mutexattr_init,(__attr))
#else /* LIBC: pthread_mutexattr_init */
#undef ____localdep_pthread_mutexattr_init_defined
#endif /* pthread_mutexattr_init... */
#endif /* !____localdep_pthread_mutexattr_init_defined */

/* Dependency: "pthread_mutexattr_settype" */
#ifndef ____localdep_pthread_mutexattr_settype_defined
#define ____localdep_pthread_mutexattr_settype_defined 1
#ifdef __CRT_HAVE_pthread_mutexattr_settype
/* Set the mutex kind attribute in *ATTR to KIND (either PTHREAD_MUTEX_NORMAL,
 * PTHREAD_MUTEX_RECURSIVE, PTHREAD_MUTEX_ERRORCHECK, or PTHREAD_MUTEX_DEFAULT) */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_pthread_mutexattr_settype,(__pthread_mutexattr_t *__attr, int __kind),pthread_mutexattr_settype,(__attr,__kind))
#else /* LIBC: pthread_mutexattr_settype */
#undef ____localdep_pthread_mutexattr_settype_defined
#endif /* pthread_mutexattr_settype... */
#endif /* !____localdep_pthread_mutexattr_settype_defined */

/* Dependency: "pthread_mutexattr_destroy" */
#ifndef ____localdep_pthread_mutexattr_destroy_defined
#define ____localdep_pthread_mutexattr_destroy_defined 1
#ifdef __CRT_HAVE_pthread_mutexattr_destroy
/* Destroy mutex attribute object ATTR */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_pthread_mutexattr_destroy,(__pthread_mutexattr_t *__attr),pthread_mutexattr_destroy,(__attr))
#else /* LIBC: pthread_mutexattr_destroy */
#undef ____localdep_pthread_mutexattr_destroy_defined
#endif /* pthread_mutexattr_destroy... */
#endif /* !____localdep_pthread_mutexattr_destroy_defined */

__NAMESPACE_LOCAL_BEGIN
/* Creates a new mutex object with type TYPE.
 * If successful the new object is pointed by MUTEX
 * s.a. `pthread_mutex_init()' */
__LOCAL_LIBC(mtx_init) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mtx_init))(__mtx_t *__restrict __mutex,
                                                      int __type) {
#line 250 "kos/src/libc/magic/threads.c"
	int __error;
	if (__type == 0 /*mtx_plain*/) {
		__error = __localdep_pthread_mutex_init((__pthread_mutex_t *)__mutex, __NULLPTR);
	} else {
		__pthread_mutexattr_t __attr;
		__error = __localdep_pthread_mutexattr_init(&__attr);
		if (__error == 0) {
			__error = __localdep_pthread_mutexattr_settype(&__attr,
			                                  (__type & 1) ? __PTHREAD_MUTEX_RECURSIVE
			                                             : __PTHREAD_MUTEX_TIMED);
			if (__error == 0)
				__error = __localdep_pthread_mutex_init((__pthread_mutex_t *)__mutex, &__attr);
			__localdep_pthread_mutexattr_destroy(&__attr);
		}
	}
	if __likely(!__error)
		return 0; /* thrd_success */
	return 2; /* thrd_error */
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_pthread_mutex_init */
#endif /* !__local_mtx_init_defined */
