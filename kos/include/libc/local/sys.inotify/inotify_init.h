/* HASH CRC-32:0x533fbdbd */
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
#ifndef __local_inotify_init_defined
#define __local_inotify_init_defined
#include <__crt.h>
#ifdef __CRT_HAVE_inotify_init1
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_inotify_init1_defined
#define __local___localdep_inotify_init1_defined
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,__fd_t,__NOTHROW_NCX,__localdep_inotify_init1,(__STDC_INT_AS_UINT_T __flags),inotify_init1,(__flags))
#endif /* !__local___localdep_inotify_init1_defined */
__LOCAL_LIBC(inotify_init) __fd_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(inotify_init))(void) {
	return (__NAMESPACE_LOCAL_SYM __localdep_inotify_init1)(0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_inotify_init_defined
#define __local___localdep_inotify_init_defined
#define __localdep_inotify_init __LIBC_LOCAL_NAME(inotify_init)
#endif /* !__local___localdep_inotify_init_defined */
#else /* __CRT_HAVE_inotify_init1 */
#undef __local_inotify_init_defined
#endif /* !__CRT_HAVE_inotify_init1 */
#endif /* !__local_inotify_init_defined */
