/* HASH CRC-32:0x4c3e4890 */
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
#ifndef __local__umask_s_defined
#define __local__umask_s_defined
#include <__crt.h>
#if defined(__CRT_HAVE_umask) || defined(__CRT_HAVE__umask) || defined(__CRT_HAVE___umask) || defined(__CRT_HAVE___libc_umask)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_umask_defined
#define __local___localdep_umask_defined
#ifdef __CRT_HAVE_umask
__CREDIRECT(,__mode_t,__NOTHROW_NCX,__localdep_umask,(__mode_t __mode),umask,(__mode))
#elif defined(__CRT_HAVE__umask)
__CREDIRECT(,__mode_t,__NOTHROW_NCX,__localdep_umask,(__mode_t __mode),_umask,(__mode))
#elif defined(__CRT_HAVE___umask)
__CREDIRECT(,__mode_t,__NOTHROW_NCX,__localdep_umask,(__mode_t __mode),__umask,(__mode))
#elif defined(__CRT_HAVE___libc_umask)
__CREDIRECT(,__mode_t,__NOTHROW_NCX,__localdep_umask,(__mode_t __mode),__libc_umask,(__mode))
#else /* ... */
#undef __local___localdep_umask_defined
#endif /* !... */
#endif /* !__local___localdep_umask_defined */
__LOCAL_LIBC(_umask_s) __ATTR_NONNULL((2)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_umask_s))(__mode_t __nmode, __mode_t *__omode) {
	*__omode = (__NAMESPACE_LOCAL_SYM __localdep_umask)(__nmode);
	return __EOK;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__umask_s_defined
#define __local___localdep__umask_s_defined
#define __localdep__umask_s __LIBC_LOCAL_NAME(_umask_s)
#endif /* !__local___localdep__umask_s_defined */
#else /* __CRT_HAVE_umask || __CRT_HAVE__umask || __CRT_HAVE___umask || __CRT_HAVE___libc_umask */
#undef __local__umask_s_defined
#endif /* !__CRT_HAVE_umask && !__CRT_HAVE__umask && !__CRT_HAVE___umask && !__CRT_HAVE___libc_umask */
#endif /* !__local__umask_s_defined */
