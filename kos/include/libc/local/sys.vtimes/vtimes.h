/* HASH CRC-32:0x2e7d4eb8 */
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
#ifndef __local_vtimes_defined
#define __local_vtimes_defined
#include <__crt.h>
#include <asm/os/resource.h>
#include <features.h>
#include <bits/types.h>
#if defined(__RUSAGE_SELF) && defined(__RUSAGE_CHILDREN) && ((defined(__CRT_HAVE_getrusage) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE___getrusage) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE___libc_getrusage) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE_getrusage64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE___getrusage64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)))
#include <bits/crt/vtimes.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getrusage_defined
#define __local___localdep_getrusage_defined
#if defined(__CRT_HAVE_getrusage) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__NAMESPACE_LOCAL_END
#include <bits/os/rusage.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_getrusage,(int __who, struct rusage *__usage),getrusage,(__who,__usage))
#elif defined(__CRT_HAVE___getrusage) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__NAMESPACE_LOCAL_END
#include <bits/os/rusage.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_getrusage,(int __who, struct rusage *__usage),__getrusage,(__who,__usage))
#elif defined(__CRT_HAVE___libc_getrusage) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__NAMESPACE_LOCAL_END
#include <bits/os/rusage.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_getrusage,(int __who, struct rusage *__usage),__libc_getrusage,(__who,__usage))
#elif defined(__CRT_HAVE_getrusage64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__NAMESPACE_LOCAL_END
#include <bits/os/rusage.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_getrusage,(int __who, struct rusage *__usage),getrusage64,(__who,__usage))
#elif defined(__CRT_HAVE___getrusage64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__NAMESPACE_LOCAL_END
#include <bits/os/rusage.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_getrusage,(int __who, struct rusage *__usage),__getrusage64,(__who,__usage))
#else /* ... */
#undef __local___localdep_getrusage_defined
#endif /* !... */
#endif /* !__local___localdep_getrusage_defined */
__NAMESPACE_LOCAL_END
#include <bits/os/rusage.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vtimes) __ATTR_OUT_OPT(1) __ATTR_OUT_OPT(2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(vtimes))(struct vtimes *__current, struct vtimes *__child) {
	int __result = 0;
	unsigned int __i;
	for (__i = 0; __i < 2; ++__i) {
		struct rusage __ru;
		struct vtimes *__slot = __i ? __child : __current;
		if (!__slot)
			continue;
		__result = (__NAMESPACE_LOCAL_SYM __localdep_getrusage)((int)(__i ? __RUSAGE_CHILDREN : __RUSAGE_SELF), &__ru);
		if __unlikely(__result != 0)
			break;
		__slot->vm_utime = ((__ru.ru_utime.tv_sec * __VTIMES_UNITS_PER_SECOND) +
		                    ((__ru.ru_utime.tv_usec * __VTIMES_UNITS_PER_SECOND) / 1000000));
		__slot->vm_stime = ((__ru.ru_stime.tv_sec * __VTIMES_UNITS_PER_SECOND) +
		                    ((__ru.ru_stime.tv_usec * __VTIMES_UNITS_PER_SECOND) / 1000000));
		__slot->vm_idsrss = __ru.ru_idrss + __ru.ru_isrss;
		__slot->vm_majflt = __ru.ru_majflt;
		__slot->vm_minflt = __ru.ru_minflt;
		__slot->vm_nswap  = __ru.ru_nswap;
		__slot->vm_inblk  = __ru.ru_inblock;
		__slot->vm_oublk  = __ru.ru_oublock;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vtimes_defined
#define __local___localdep_vtimes_defined
#define __localdep_vtimes __LIBC_LOCAL_NAME(vtimes)
#endif /* !__local___localdep_vtimes_defined */
#else /* __RUSAGE_SELF && __RUSAGE_CHILDREN && ((__CRT_HAVE_getrusage && (!__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (__CRT_HAVE___getrusage && (!__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (__CRT_HAVE___libc_getrusage && (!__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (__CRT_HAVE_getrusage64 && (__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (__CRT_HAVE___getrusage64 && (__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__))) */
#undef __local_vtimes_defined
#endif /* !__RUSAGE_SELF || !__RUSAGE_CHILDREN || ((!__CRT_HAVE_getrusage || (__USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__)) && (!__CRT_HAVE___getrusage || (__USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__)) && (!__CRT_HAVE___libc_getrusage || (__USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__)) && (!__CRT_HAVE_getrusage64 || (!__USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__)) && (!__CRT_HAVE___getrusage64 || (!__USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__))) */
#endif /* !__local_vtimes_defined */
