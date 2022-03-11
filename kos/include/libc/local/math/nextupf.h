/* HASH CRC-32:0x46532b6e */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_nextupf_defined
#define __local_nextupf_defined
#include <__crt.h>
#ifdef __CRT_HAVE_nextup
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_nextup_defined
#define __local___localdep_nextup_defined
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW_NCX,__localdep_nextup,(double __x),nextup,(__x))
#endif /* !__local___localdep_nextup_defined */
__LOCAL_LIBC(nextupf) __ATTR_WUNUSED float
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(nextupf))(float __x) {
	return (float)(__NAMESPACE_LOCAL_SYM __localdep_nextup)((double)__x);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_nextupf_defined
#define __local___localdep_nextupf_defined
#define __localdep_nextupf __LIBC_LOCAL_NAME(nextupf)
#endif /* !__local___localdep_nextupf_defined */
#else /* __CRT_HAVE_nextup */
#undef __local_nextupf_defined
#endif /* !__CRT_HAVE_nextup */
#endif /* !__local_nextupf_defined */
