/* HASH CRC-32:0xbfe1ce16 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__aligned_free_dbg_defined
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE__aligned_free)
#define __local__aligned_free_dbg_defined 1
/* Dependency: "_aligned_free" from "stdlib" */
#ifndef ____localdep__aligned_free_defined
#define ____localdep__aligned_free_defined 1
#ifdef __CRT_HAVE__aligned_free
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep__aligned_free,(void *__mptr),_aligned_free,(__mptr))
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
#include <local/stdlib/_aligned_free.h>
#define __localdep__aligned_free (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_free))
#else /* CUSTOM: _aligned_free */
#undef ____localdep__aligned_free_defined
#endif /* _aligned_free... */
#endif /* !____localdep__aligned_free_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_aligned_free_dbg) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_aligned_free_dbg))(void *__ptr) {
#line 406 "kos/src/libc/magic/crtdbg.c"
	__localdep__aligned_free(__ptr);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE__aligned_free */
#endif /* !__local__aligned_free_dbg_defined */
