/* HASH CRC-32:0x259010f6 */
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
#ifndef __local_mmap_defined
#if defined(__CRT_HAVE_mmap) || defined(__CRT_HAVE_mmap64)
#define __local_mmap_defined 1
/* Dependency: "mmap64" from "sys.mman" */
#ifndef ____localdep_mmap64_defined
#define ____localdep_mmap64_defined 1
#ifdef __CRT_HAVE_mmap64
/* @param prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE' */
__CREDIRECT(__ATTR_WUNUSED,void *,__NOTHROW_NCX,__localdep_mmap64,(void *__addr, __SIZE_TYPE__ __len, int __prot, int __flags, __fd_t __fd, __off64_t __offset),mmap64,(__addr,__len,__prot,__flags,__fd,__offset))
#elif defined(__CRT_HAVE_mmap) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* @param prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE' */
__CREDIRECT(__ATTR_WUNUSED,void *,__NOTHROW_NCX,__localdep_mmap64,(void *__addr, __SIZE_TYPE__ __len, int __prot, int __flags, __fd_t __fd, __off64_t __offset),mmap,(__addr,__len,__prot,__flags,__fd,__offset))
#elif defined(__CRT_HAVE_mmap)
#include <local/sys.mman/mmap64.h>
/* @param prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE' */
#define __localdep_mmap64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mmap64))
#else /* CUSTOM: mmap64 */
#undef ____localdep_mmap64_defined
#endif /* mmap64... */
#endif /* !____localdep_mmap64_defined */

/* Dependency: "mmap32" from "sys.mman" */
#ifndef ____localdep_mmap32_defined
#define ____localdep_mmap32_defined 1
#ifdef __CRT_HAVE_mmap
/* @param prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE' */
__CREDIRECT(,void *,__NOTHROW_NCX,__localdep_mmap32,(void *__addr, __SIZE_TYPE__ __len, int __prot, int __flags, __fd_t __fd, __off32_t __offset),mmap,(__addr,__len,__prot,__flags,__fd,__offset))
#else /* LIBC: mmap */
#undef ____localdep_mmap32_defined
#endif /* mmap32... */
#endif /* !____localdep_mmap32_defined */

__NAMESPACE_LOCAL_BEGIN
/* @param prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE' */
__LOCAL_LIBC(mmap) __ATTR_WUNUSED void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mmap))(void *__addr,
                                                  __SIZE_TYPE__ __len,
                                                  int __prot,
                                                  int __flags,
                                                  __fd_t __fd,
                                                  __FS_TYPE(off) __offset) {
#line 295 "kos/src/libc/magic/sys.mman.c"
#ifdef __CRT_HAVE_mmap64
	return __localdep_mmap64(__addr, __len, __prot, __flags, __fd, (__off32_t)__offset);
#else /* __CRT_HAVE_mmap64 */
	return __localdep_mmap32(__addr, __len, __prot, __flags, __fd, (__off32_t)__offset);
#endif /* !__CRT_HAVE_mmap64 */
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_mmap || __CRT_HAVE_mmap64 */
#endif /* !__local_mmap_defined */
