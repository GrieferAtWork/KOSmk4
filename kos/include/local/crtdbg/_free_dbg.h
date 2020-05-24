/* HASH CRC-32:0x2fd92057 */
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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__free_dbg_defined
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
#define __local__free_dbg_defined 1
#include <__crt.h>
/* Dependency: "free" */
#ifndef ____localdep_free_defined
#define ____localdep_free_defined 1
#ifdef __std___localdep_free_defined
__NAMESPACE_STD_USING(__localdep_free)
#elif __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ return __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#else /* LIBC: free */
#undef ____localdep_free_defined
#endif /* free... */
#endif /* !____localdep_free_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_free_dbg) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_free_dbg))(void *__ptr,
                                                       int __block_type) {
#line 336 "kos/src/libc/magic/crtdbg.c"
	(void)__block_type;
	__localdep_free(__ptr);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree */
#endif /* !__local__free_dbg_defined */
