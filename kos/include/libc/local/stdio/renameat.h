/* HASH CRC-32:0x331e853f */
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
#ifndef __local_renameat_defined
#define __local_renameat_defined
#include <__crt.h>
#ifdef __CRT_HAVE_renameat2
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_renameat2_defined
#define __local___localdep_renameat2_defined
__CREDIRECT(__ATTR_IN(2) __ATTR_IN(4),int,__NOTHROW_RPC,__localdep_renameat2,(__fd_t __oldfd, char const *__oldname, __fd_t __newfd, char const *__newname_or_path, __atflag_t __flags),renameat2,(__oldfd,__oldname,__newfd,__newname_or_path,__flags))
#endif /* !__local___localdep_renameat2_defined */
__LOCAL_LIBC(renameat) __ATTR_IN(2) __ATTR_IN(4) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(renameat))(__fd_t __oldfd, char const *__oldname, __fd_t __newfd, char const *__newname_or_path) {
	return (__NAMESPACE_LOCAL_SYM __localdep_renameat2)(__oldfd, __oldname, __newfd, __newname_or_path, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_renameat_defined
#define __local___localdep_renameat_defined
#define __localdep_renameat __LIBC_LOCAL_NAME(renameat)
#endif /* !__local___localdep_renameat_defined */
#else /* __CRT_HAVE_renameat2 */
#undef __local_renameat_defined
#endif /* !__CRT_HAVE_renameat2 */
#endif /* !__local_renameat_defined */
