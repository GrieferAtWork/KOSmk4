/* HASH CRC-32:0xa4bde00 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_setsigmaskfullptr_defined
#define __local_setsigmaskfullptr_defined
#include <__crt.h>
#ifdef __CRT_HAVE_setsigmaskptr
#include <bits/os/sigset.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_setsigmaskptr_defined
#define __local___localdep_setsigmaskptr_defined
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),struct __sigset_struct *,__NOTHROW_NCX,__localdep_setsigmaskptr,(struct __sigset_struct *__sigmaskptr),setsigmaskptr,(__sigmaskptr))
#endif /* !__local___localdep_setsigmaskptr_defined */
__LOCAL_LIBC(setsigmaskfullptr) __ATTR_RETNONNULL struct __sigset_struct *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(setsigmaskfullptr))(void) {
	static struct __sigset_struct const __ss_full = __SIGSET_INIT((__ULONGPTR_TYPE__)-1);
	return (__NAMESPACE_LOCAL_SYM __localdep_setsigmaskptr)((struct __sigset_struct *)&__ss_full);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_setsigmaskfullptr_defined
#define __local___localdep_setsigmaskfullptr_defined
#define __localdep_setsigmaskfullptr __LIBC_LOCAL_NAME(setsigmaskfullptr)
#endif /* !__local___localdep_setsigmaskfullptr_defined */
#else /* __CRT_HAVE_setsigmaskptr */
#undef __local_setsigmaskfullptr_defined
#endif /* !__CRT_HAVE_setsigmaskptr */
#endif /* !__local_setsigmaskfullptr_defined */
