/* HASH CRC-32:0xf45113bc */
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
#ifndef __local_globfree_defined
#define __local_globfree_defined 1
#include <__crt.h>
struct __glob_struct;
__NAMESPACE_LOCAL_BEGIN
/* Dependency: globfree32 from glob */
#if !defined(__local___localdep_globfree32_defined) && defined(__CRT_HAVE_globfree)
#define __local___localdep_globfree32_defined 1
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_globfree32,(void *__pglob),globfree,(__pglob))
#endif /* !__local___localdep_globfree32_defined && __CRT_HAVE_globfree */
/* Dependency: globfree64 from glob */
#ifndef __local___localdep_globfree64_defined
#define __local___localdep_globfree64_defined 1
#ifdef __CRT_HAVE_globfree64
__NAMESPACE_LOCAL_END
struct __glob64_struct;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__localdep_globfree64,(struct __glob64_struct *__pglob),globfree64,(__pglob))
#else /* __CRT_HAVE_globfree64 */
__NAMESPACE_LOCAL_END
#include <libc/local/glob/globfree64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_globfree64 __LIBC_LOCAL_NAME(globfree64)
#endif /* !__CRT_HAVE_globfree64 */
#endif /* !__local___localdep_globfree64_defined */
__LOCAL_LIBC(globfree) __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(globfree))(struct __glob_struct *__pglob) {
#ifdef __CRT_HAVE_globfree
	__localdep_globfree32(__pglob);
#else /* __CRT_HAVE_globfree */
	__localdep_globfree64((struct __glob64_struct *)__pglob);



#endif /* !__CRT_HAVE_globfree */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_globfree_defined
#define __local___localdep_globfree_defined 1
#define __localdep_globfree __LIBC_LOCAL_NAME(globfree)
#endif /* !__local___localdep_globfree_defined */
#endif /* !__local_globfree_defined */
