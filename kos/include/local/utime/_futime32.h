/* HASH CRC-32:0x4931306b */
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
#ifndef __local__futime32_defined
#if (defined(__CRT_HAVE__futime64) || defined(__CRT_HAVE_futime64))
#define __local__futime32_defined 1
/* Dependency: "crt_futime64" from "utime" */
#ifndef ____localdep_crt_futime64_defined
#define ____localdep_crt_futime64_defined 1
#if defined(__CRT_HAVE_futime64)
__CREDIRECT(,int,__NOTHROW_RPC,__localdep_crt_futime64,(__fd_t __fd, struct __utimbuf64 const *__file_times),futime64,(__fd,__file_times))
#elif defined(__CRT_HAVE__futime64)
__CREDIRECT(,int,__NOTHROW_RPC,__localdep_crt_futime64,(__fd_t __fd, struct __utimbuf64 const *__file_times),_futime64,(__fd,__file_times))
#else /* LIBC: futime64 */
#undef ____localdep_crt_futime64_defined
#endif /* crt_futime64... */
#endif /* !____localdep_crt_futime64_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_futime32) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(_futime32))(__fd_t __fd,
                                                       struct __utimbuf32 __KOS_FIXED_CONST *__file_times) {
#line 226 "kos/src/libc/magic/utime.c"
	struct __utimbuf64 __buf64;
	if (!__file_times)
		return __localdep_crt_futime64(__fd,__NULLPTR);
	__buf64.__actime  = (__time64_t)__file_times->__actime;
	__buf64.__modtime = (__time64_t)__file_times->__modtime;
	return __localdep_crt_futime64(__fd,&__buf64);
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE__futime64) || defined(__CRT_HAVE_futime64)) */
#endif /* !__local__futime32_defined */
