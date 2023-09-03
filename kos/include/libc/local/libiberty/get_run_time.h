/* HASH CRC-32:0xefa18653 */
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
#ifndef __local_get_run_time_defined
#define __local_get_run_time_defined
#include <__crt.h>
#include <asm/os/resource.h>
#include <asm/crt/confname.h>
#include <asm/os/clock.h>
#include <bits/crt/vtimes.h>
#include <bits/types.h>
#include <features.h>
#if (defined(__RUSAGE_SELF) && ((defined(__CRT_HAVE_getrusage) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || (defined(__CRT_HAVE___getrusage) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || (defined(__CRT_HAVE___libc_getrusage) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || defined(__CRT_HAVE_getrusage64) || defined(__CRT_HAVE___getrusage64))) || (defined(_SC_CLK_TCK) && (defined(__CRT_HAVE_sysconf) || defined(__CRT_HAVE___sysconf)) && (defined(__CRT_HAVE_times) || defined(__CRT_HAVE___times) || defined(__CRT_HAVE___libc_times))) || (defined(__VTIMES_UNITS_PER_SECOND) && (defined(__CRT_HAVE_vtimes) || (defined(__RUSAGE_SELF) && defined(__RUSAGE_CHILDREN) && ((defined(__CRT_HAVE_getrusage) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE___getrusage) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE___libc_getrusage) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE_getrusage64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE___getrusage64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)))))) || (defined(__CLOCKS_PER_SEC) && (defined(__CRT_HAVE_clock) || (defined(__CLOCK_PROCESS_CPUTIME_ID) && (defined(__CRT_HAVE_clock_gettime64) || defined(__CRT_HAVE___clock_gettime64) || defined(__CRT_HAVE_clock_gettime) || defined(__CRT_HAVE___clock_gettime))) || defined(__CRT_HAVE_times) || defined(__CRT_HAVE___times) || defined(__CRT_HAVE___libc_times)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_clock_defined
#define __local___localdep_clock_defined
#ifdef __CRT_HAVE_clock
__CREDIRECT(__ATTR_WUNUSED,__clock_t,__NOTHROW_NCX,__localdep_clock,(void),clock,())
#elif (defined(__CLOCK_PROCESS_CPUTIME_ID) && (defined(__CRT_HAVE_clock_gettime64) || defined(__CRT_HAVE___clock_gettime64) || defined(__CRT_HAVE_clock_gettime) || defined(__CRT_HAVE___clock_gettime))) || defined(__CRT_HAVE_times) || defined(__CRT_HAVE___times) || defined(__CRT_HAVE___libc_times)
__NAMESPACE_LOCAL_END
#include <libc/local/time/clock.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_clock __LIBC_LOCAL_NAME(clock)
#else /* ... */
#undef __local___localdep_clock_defined
#endif /* !... */
#endif /* !__local___localdep_clock_defined */
#ifndef __local___localdep_getrusage64_defined
#define __local___localdep_getrusage64_defined
#if defined(__CRT_HAVE_getrusage) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__NAMESPACE_LOCAL_END
#include <bits/os/rusage.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_getrusage64,(int __who, struct __rusage64 *__usage),getrusage,(__who,__usage))
#elif defined(__CRT_HAVE___getrusage) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__NAMESPACE_LOCAL_END
#include <bits/os/rusage.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_getrusage64,(int __who, struct __rusage64 *__usage),__getrusage,(__who,__usage))
#elif defined(__CRT_HAVE___libc_getrusage) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__NAMESPACE_LOCAL_END
#include <bits/os/rusage.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_getrusage64,(int __who, struct __rusage64 *__usage),__libc_getrusage,(__who,__usage))
#elif defined(__CRT_HAVE_getrusage64)
__NAMESPACE_LOCAL_END
#include <bits/os/rusage.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_getrusage64,(int __who, struct __rusage64 *__usage),getrusage64,(__who,__usage))
#elif defined(__CRT_HAVE___getrusage64)
__NAMESPACE_LOCAL_END
#include <bits/os/rusage.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_getrusage64,(int __who, struct __rusage64 *__usage),__getrusage64,(__who,__usage))
#else /* ... */
#undef __local___localdep_getrusage64_defined
#endif /* !... */
#endif /* !__local___localdep_getrusage64_defined */
#ifndef __local___localdep_sysconf_defined
#define __local___localdep_sysconf_defined
#ifdef __CRT_HAVE_sysconf
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED,__LONGPTR_TYPE__,__NOTHROW_RPC,__localdep_sysconf,(__STDC_INT_AS_UINT_T __name),sysconf,(__name))
#elif defined(__CRT_HAVE___sysconf)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED,__LONGPTR_TYPE__,__NOTHROW_RPC,__localdep_sysconf,(__STDC_INT_AS_UINT_T __name),__sysconf,(__name))
#else /* ... */
#undef __local___localdep_sysconf_defined
#endif /* !... */
#endif /* !__local___localdep_sysconf_defined */
#ifndef __local___localdep_times_defined
#define __local___localdep_times_defined
#ifdef __CRT_HAVE_times
__NAMESPACE_LOCAL_END
#include <bits/os/tms.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(1),__clock_t,__NOTHROW_NCX,__localdep_times,(struct tms *__buffer),times,(__buffer))
#elif defined(__CRT_HAVE___times)
__NAMESPACE_LOCAL_END
#include <bits/os/tms.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(1),__clock_t,__NOTHROW_NCX,__localdep_times,(struct tms *__buffer),__times,(__buffer))
#elif defined(__CRT_HAVE___libc_times)
__NAMESPACE_LOCAL_END
#include <bits/os/tms.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(1),__clock_t,__NOTHROW_NCX,__localdep_times,(struct tms *__buffer),__libc_times,(__buffer))
#else /* ... */
#undef __local___localdep_times_defined
#endif /* !... */
#endif /* !__local___localdep_times_defined */
#ifndef __local___localdep_vtimes_defined
#define __local___localdep_vtimes_defined
#ifdef __CRT_HAVE_vtimes
__CREDIRECT(__ATTR_OUT_OPT(1) __ATTR_OUT_OPT(2),int,__NOTHROW_NCX,__localdep_vtimes,(struct vtimes *__current, struct vtimes *__child),vtimes,(__current,__child))
#elif defined(__RUSAGE_SELF) && defined(__RUSAGE_CHILDREN) && ((defined(__CRT_HAVE_getrusage) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE___getrusage) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE___libc_getrusage) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE_getrusage64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE___getrusage64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)))
__NAMESPACE_LOCAL_END
#include <libc/local/sys.vtimes/vtimes.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vtimes __LIBC_LOCAL_NAME(vtimes)
#else /* ... */
#undef __local___localdep_vtimes_defined
#endif /* !... */
#endif /* !__local___localdep_vtimes_defined */
__NAMESPACE_LOCAL_END
#include <bits/os/rusage.h>
#include <bits/os/tms.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(get_run_time) __ATTR_WUNUSED long
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(get_run_time))(void) {
	__UINT64_TYPE__ __result;
#if defined(__RUSAGE_SELF) && ((defined(__CRT_HAVE_getrusage) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || (defined(__CRT_HAVE___getrusage) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || (defined(__CRT_HAVE___libc_getrusage) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || defined(__CRT_HAVE_getrusage64) || defined(__CRT_HAVE___getrusage64))
	struct __rusage64 __ru;
	(__NAMESPACE_LOCAL_SYM __localdep_getrusage64)(__RUSAGE_SELF, &__ru);
	__result  = ((__UINT64_TYPE__)__ru.ru_utime.tv_sec * 1000000) + __ru.ru_utime.tv_usec;
	__result += ((__UINT64_TYPE__)__ru.ru_stime.tv_sec * 1000000) + __ru.ru_stime.tv_usec;
#elif defined(__times)
	struct tms __ts;
	(__NAMESPACE_LOCAL_SYM __localdep_times)(&__ts);
	__result = __ts.tms_utime + __ts.tms_stime;
	__result *= 1000000;
	__result /= (__NAMESPACE_LOCAL_SYM __localdep_sysconf)(_SC_CLK_TCK);
#elif defined(__VTIMES_UNITS_PER_SECOND) && (defined(__CRT_HAVE_vtimes) || (defined(__RUSAGE_SELF) && defined(__RUSAGE_CHILDREN) && ((defined(__CRT_HAVE_getrusage) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE___getrusage) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE___libc_getrusage) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE_getrusage64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE___getrusage64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)))))
	struct (__NAMESPACE_LOCAL_SYM __localdep_vtimes) __vt;
	(__NAMESPACE_LOCAL_SYM __localdep_vtimes)(&__vt, __NULLPTR);
	__result = __vt->vm_utime + __vt->vm_stime;
	__result *= 1000000;
	__result /= __VTIMES_UNITS_PER_SECOND;
#else /* ... */
	__result = (__NAMESPACE_LOCAL_SYM __localdep_clock)();
	__result *= 1000000;
	__result /= __CLOCKS_PER_SEC;
#endif /* !... */
	return (long)__result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_get_run_time_defined
#define __local___localdep_get_run_time_defined
#define __localdep_get_run_time __LIBC_LOCAL_NAME(get_run_time)
#endif /* !__local___localdep_get_run_time_defined */
#else /* (__RUSAGE_SELF && ((__CRT_HAVE_getrusage && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || (__CRT_HAVE___getrusage && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || (__CRT_HAVE___libc_getrusage && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || __CRT_HAVE_getrusage64 || __CRT_HAVE___getrusage64)) || (_SC_CLK_TCK && (__CRT_HAVE_sysconf || __CRT_HAVE___sysconf) && (__CRT_HAVE_times || __CRT_HAVE___times || __CRT_HAVE___libc_times)) || (__VTIMES_UNITS_PER_SECOND && (__CRT_HAVE_vtimes || (__RUSAGE_SELF && __RUSAGE_CHILDREN && ((__CRT_HAVE_getrusage && (!__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (__CRT_HAVE___getrusage && (!__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (__CRT_HAVE___libc_getrusage && (!__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (__CRT_HAVE_getrusage64 && (__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (__CRT_HAVE___getrusage64 && (__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)))))) || (__CLOCKS_PER_SEC && (__CRT_HAVE_clock || (__CLOCK_PROCESS_CPUTIME_ID && (__CRT_HAVE_clock_gettime64 || __CRT_HAVE___clock_gettime64 || __CRT_HAVE_clock_gettime || __CRT_HAVE___clock_gettime)) || __CRT_HAVE_times || __CRT_HAVE___times || __CRT_HAVE___libc_times)) */
#undef __local_get_run_time_defined
#endif /* (!__RUSAGE_SELF || ((!__CRT_HAVE_getrusage || __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__) && (!__CRT_HAVE___getrusage || __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__) && (!__CRT_HAVE___libc_getrusage || __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__) && !__CRT_HAVE_getrusage64 && !__CRT_HAVE___getrusage64)) && (!_SC_CLK_TCK || (!__CRT_HAVE_sysconf && !__CRT_HAVE___sysconf) || (!__CRT_HAVE_times && !__CRT_HAVE___times && !__CRT_HAVE___libc_times)) && (!__VTIMES_UNITS_PER_SECOND || (!__CRT_HAVE_vtimes && (!__RUSAGE_SELF || !__RUSAGE_CHILDREN || ((!__CRT_HAVE_getrusage || (__USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__)) && (!__CRT_HAVE___getrusage || (__USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__)) && (!__CRT_HAVE___libc_getrusage || (__USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__)) && (!__CRT_HAVE_getrusage64 || (!__USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__)) && (!__CRT_HAVE___getrusage64 || (!__USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__)))))) && (!__CLOCKS_PER_SEC || (!__CRT_HAVE_clock && (!__CLOCK_PROCESS_CPUTIME_ID || (!__CRT_HAVE_clock_gettime64 && !__CRT_HAVE___clock_gettime64 && !__CRT_HAVE_clock_gettime && !__CRT_HAVE___clock_gettime)) && !__CRT_HAVE_times && !__CRT_HAVE___times && !__CRT_HAVE___libc_times)) */
#endif /* !__local_get_run_time_defined */
