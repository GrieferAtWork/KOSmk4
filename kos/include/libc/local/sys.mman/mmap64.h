/* HASH CRC-32:0x1b435349 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_mmap64_defined
#define __local_mmap64_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_mmap
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: mmap32 from sys.mman */
#ifndef __local___localdep_mmap32_defined
#define __local___localdep_mmap32_defined 1
/* @param prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_LOOSE | PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS | MAP_FIXED | MAP_GROWSDOWN | MAP_LOCKED|
 *               MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE | MAP_STACK | MAP_SYNC |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE' */
__CREDIRECT(,void *,__NOTHROW_NCX,__localdep_mmap32,(void *__addr, __SIZE_TYPE__ __len, __STDC_INT_AS_UINT_T __prot, __STDC_INT_AS_UINT_T __flags, __fd_t __fd, __off32_t __offset),mmap,(__addr,__len,__prot,__flags,__fd,__offset))
#endif /* !__local___localdep_mmap32_defined */
/* @param prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_LOOSE | PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS | MAP_FIXED | MAP_GROWSDOWN | MAP_LOCKED|
 *               MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE | MAP_STACK | MAP_SYNC |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE' */
__LOCAL_LIBC(mmap64) __ATTR_WUNUSED void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mmap64))(void *__addr, __SIZE_TYPE__ __len, __STDC_INT_AS_UINT_T __prot, __STDC_INT_AS_UINT_T __flags, __fd_t __fd, __off64_t __offset) {
	return __localdep_mmap32(__addr, __len, __prot, __flags, __fd, (__off32_t)__offset);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mmap64_defined
#define __local___localdep_mmap64_defined 1
#define __localdep_mmap64 __LIBC_LOCAL_NAME(mmap64)
#endif /* !__local___localdep_mmap64_defined */
#else /* __CRT_HAVE_mmap */
#undef __local_mmap64_defined
#endif /* !__CRT_HAVE_mmap */
#endif /* !__local_mmap64_defined */
