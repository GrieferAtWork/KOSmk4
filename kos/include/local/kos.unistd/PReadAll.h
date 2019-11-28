/* HASH CRC-32:0xe5d4d412 */
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
#ifndef __local_PReadAll_defined
#if defined(__CRT_HAVE_PReadAll) || defined(__CRT_HAVE_PRead) || defined(__CRT_HAVE_PRead64) || defined(__CRT_HAVE_PReadAll64) || (defined(__CRT_HAVE_preadall) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
#define __local_PReadAll_defined 1
#include <kos/anno.h>
#include <parts/errno.h>
/* Dependency: "PReadAll32" from "kos.unistd" */
#ifndef ____localdep_PReadAll32_defined
#define ____localdep_PReadAll32_defined 1
#ifdef __CRT_HAVE_PReadAll
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,,__localdep_PReadAll32,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __pos32_t __offset),PReadAll,(__fd,__buf,__bufsize,__offset)) __THROWS(...)
#else /* LIBC: PReadAll */
#undef ____localdep_PReadAll32_defined
#endif /* PReadAll32... */
#endif /* !____localdep_PReadAll32_defined */

/* Dependency: "PReadAll64" from "kos.unistd" */
#ifndef ____localdep_PReadAll64_defined
#define ____localdep_PReadAll64_defined 1
#ifdef __CRT_HAVE_PReadAll64
/* >> preadall64(3)
 * Same as `readall(3)', but using `pread64(2)' instead of `read()' */
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,,__localdep_PReadAll64,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __pos64_t __offset),PReadAll64,(__fd,__buf,__bufsize,__offset)) __THROWS(...)
#elif defined(__CRT_HAVE_preadall) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> preadall64(3)
 * Same as `readall(3)', but using `pread64(2)' instead of `read()' */
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,,__localdep_PReadAll64,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __pos64_t __offset),preadall,(__fd,__buf,__bufsize,__offset)) __THROWS(...)
#elif defined(__CRT_HAVE_PRead) || defined(__CRT_HAVE_PRead64)
#include <local/kos.unistd/PReadAll64.h>
/* >> preadall64(3)
 * Same as `readall(3)', but using `pread64(2)' instead of `read()' */
#define __localdep_PReadAll64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(PReadAll64))
#else /* CUSTOM: PReadAll64 */
#undef ____localdep_PReadAll64_defined
#endif /* PReadAll64... */
#endif /* !____localdep_PReadAll64_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> preadall(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
__LOCAL_LIBC(PReadAll) __ATTR_NONNULL((2)) __SIZE_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(PReadAll))(__fd_t __fd,
                                         void *__buf,
                                         __SIZE_TYPE__ __bufsize,
                                         __FS_TYPE(pos) __offset) __THROWS(...) {
#line 339 "kos/src/libc/magic/kos.unistd.c"
#ifdef __CRT_HAVE_PReadAll
	return __localdep_PReadAll32(__fd, __buf, __bufsize, (__pos32_t)__offset);
#else /* __CRT_HAVE_PReadAll */
	return __localdep_PReadAll64(__fd, __buf, __bufsize, (__pos64_t)__offset);
#endif /* !__CRT_HAVE_PReadAll */
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_PReadAll || __CRT_HAVE_PRead || __CRT_HAVE_PRead64 || __CRT_HAVE_PReadAll64 || (__CRT_HAVE_preadall && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) */
#endif /* !__local_PReadAll_defined */
