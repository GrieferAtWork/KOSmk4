/* HASH CRC-32:0x9de14397 */
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
#ifndef __local_symlinkat_defined
#define __local_symlinkat_defined
#include <__crt.h>
#ifdef __CRT_HAVE_fsymlinkat
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fsymlinkat_defined
#define __local___localdep_fsymlinkat_defined
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(3),int,__NOTHROW_RPC,__localdep_fsymlinkat,(char const *__link_text, __fd_t __tofd, char const *__target_path, __atflag_t __flags),fsymlinkat,(__link_text,__tofd,__target_path,__flags))
#endif /* !__local___localdep_fsymlinkat_defined */
__LOCAL_LIBC(symlinkat) __ATTR_IN(1) __ATTR_IN(3) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(symlinkat))(char const *__link_text, __fd_t __tofd, char const *__target_path) {
	return (__NAMESPACE_LOCAL_SYM __localdep_fsymlinkat)(__link_text, __tofd, __target_path, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_symlinkat_defined
#define __local___localdep_symlinkat_defined
#define __localdep_symlinkat __LIBC_LOCAL_NAME(symlinkat)
#endif /* !__local___localdep_symlinkat_defined */
#else /* __CRT_HAVE_fsymlinkat */
#undef __local_symlinkat_defined
#endif /* !__CRT_HAVE_fsymlinkat */
#endif /* !__local_symlinkat_defined */
