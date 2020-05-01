/* HASH CRC-32:0x71796b4e */
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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_setitimer64_defined
#ifdef __CRT_HAVE_setitimer
#define __local_setitimer64_defined 1
#include <__crt.h>
/* Dependency: "setitimer32" from "sys.time" */
#ifndef ____localdep_setitimer32_defined
#define ____localdep_setitimer32_defined 1
#ifdef __CRT_HAVE_setitimer
/* Set the timer WHICH to *NEWVAL. If OLDVAL is not NULL, set *OLDVAL to the old value of timer WHICH.
 * Returns 0 on success, -1 on errors */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_setitimer32,(__itimer_which_t __which, struct __itimerval32 const *__restrict __newval, struct __itimerval32 *__restrict __oldval),setitimer,(__which,__newval,__oldval))
#else /* LIBC: setitimer */
#undef ____localdep_setitimer32_defined
#endif /* setitimer32... */
#endif /* !____localdep_setitimer32_defined */

__NAMESPACE_LOCAL_BEGIN
/* Set the timer WHICH to *NEWVAL. If OLDVAL is not NULL, set *OLDVAL to the old value of timer WHICH.
 * Returns 0 on success, -1 on errors */
__LOCAL_LIBC(setitimer64) __ATTR_NONNULL((2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(setitimer64))(__itimer_which_t __which,
                                                         struct itimerval64 const *__newval,
                                                         struct itimerval64 *__oldval) {
#line 462 "kos/src/libc/magic/sys.time.c"
	int __result;
	struct __itimerval32 __new32, __old32;
	__new32.it_interval.tv_sec  = (__time32_t)__newval->it_interval.tv_sec;
	__new32.it_interval.tv_usec = __newval->it_interval.tv_usec;
	__new32.it_value.tv_sec     = (__time32_t)__newval->it_value.tv_sec;
	__new32.it_value.tv_usec    = __newval->it_value.tv_usec;
	__result = __localdep_setitimer32(__which, &__new32, __oldval ? &__old32 : __NULLPTR);
	if (__likely(!__result) && __oldval) {
		__oldval->it_interval.tv_sec  = (__time64_t)__old32.it_interval.tv_sec;
		__oldval->it_interval.tv_usec = __old32.it_interval.tv_usec;
		__oldval->it_value.tv_sec     = (__time64_t)__old32.it_value.tv_sec;
		__oldval->it_value.tv_usec    = __old32.it_value.tv_usec;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_setitimer */
#endif /* !__local_setitimer64_defined */
