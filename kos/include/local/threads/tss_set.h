/* HASH CRC-32:0xf368b54 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef __local_tss_set_defined
#if defined(__CRT_HAVE_pthread_setspecific)
#define __local_tss_set_defined 1
#include <bits/threads.h>

#include <bits/pthreadtypes.h>
/* Dependency: "pthread_setspecific" */
#ifndef ____localdep_pthread_setspecific_defined
#define ____localdep_pthread_setspecific_defined 1
#if defined(__CRT_HAVE_pthread_setspecific)
/* Store POINTER in the thread-specific data slot identified by KEY */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_pthread_setspecific,(__pthread_key_t __key, void const *__pointer),pthread_setspecific,(__key,__pointer))
#else /* LIBC: pthread_setspecific */
#undef ____localdep_pthread_setspecific_defined
#endif /* pthread_setspecific... */
#endif /* !____localdep_pthread_setspecific_defined */

__NAMESPACE_LOCAL_BEGIN
/* Sets the value of the thread-specific storage
 * identified by TSS_ID for the current thread to VAL
 * s.a. `pthread_setspecific()' */
__LOCAL_LIBC(tss_set) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(tss_set))(__tss_t __tss_id,
                                                     void *__val) {
#line 500 "kos/src/libc/magic/threads.c"
	int __error;
	__error = __localdep_pthread_setspecific((__pthread_key_t)__tss_id, __val);
	if __likely(!__error)
		return 0; /* thrd_success */
	return 2; /* thrd_error */
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_pthread_setspecific) */
#endif /* !__local_tss_set_defined */
