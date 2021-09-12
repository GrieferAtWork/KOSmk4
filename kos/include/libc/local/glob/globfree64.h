/* HASH CRC-32:0x5afb5234 */
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
#ifndef __local_globfree64_defined
#define __local_globfree64_defined 1
#include <__crt.h>
struct __glob64_struct;
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_globfree32_defined) && defined(__CRT_HAVE_globfree)
#define __local___localdep_globfree32_defined 1
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_globfree32,(void *__pglob),globfree,(__pglob))
#endif /* !__local___localdep_globfree32_defined && __CRT_HAVE_globfree */
__LOCAL_LIBC(globfree64) __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(globfree64))(struct __glob64_struct *__pglob) {
#ifdef __CRT_HAVE_globfree
	__NAMESPACE_LOCAL_SYM __localdep_globfree32(__pglob);
#else /* __CRT_HAVE_globfree */
	__COMPILER_IMPURE();
	(void)__pglob;
#endif /* !__CRT_HAVE_globfree */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_globfree64_defined
#define __local___localdep_globfree64_defined 1
#define __localdep_globfree64 __LIBC_LOCAL_NAME(globfree64)
#endif /* !__local___localdep_globfree64_defined */
#endif /* !__local_globfree64_defined */
