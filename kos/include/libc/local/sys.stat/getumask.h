/* HASH CRC-32:0xe070e526 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_getumask_defined
#define __local_getumask_defined
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
__LOCAL_LIBC(getumask) __mode_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(getumask))(void) {
	__mode_t __result;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_umask)(0);
	(__NAMESPACE_LOCAL_SYM __localdep_umask)(__result);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getumask_defined
#define __local___localdep_getumask_defined
#define __localdep_getumask __LIBC_LOCAL_NAME(getumask)
#endif /* !__local___localdep_getumask_defined */
#else /* __CRT_HAVE_umask || __CRT_HAVE__umask || __CRT_HAVE___umask || __CRT_HAVE___libc_umask */
#undef __local_getumask_defined
#endif /* !__CRT_HAVE_umask && !__CRT_HAVE__umask && !__CRT_HAVE___umask && !__CRT_HAVE___libc_umask */
#endif /* !__local_getumask_defined */
