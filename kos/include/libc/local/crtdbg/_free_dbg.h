/* HASH CRC-32:0x8ced6f17 */
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
#ifndef __local__free_dbg_defined
#define __local__free_dbg_defined
#include <__crt.h>
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
__LOCAL_LIBC(_free_dbg) void
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_free_dbg))(void *__ptr, int __block_type) {
	(void)__block_type;
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__ptr);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__free_dbg_defined
#define __local___localdep__free_dbg_defined
#define __localdep__free_dbg __LIBC_LOCAL_NAME(_free_dbg)
#endif /* !__local___localdep__free_dbg_defined */
#else /* __CRT_HAVE_free || __CRT_HAVE_cfree */
#undef __local__free_dbg_defined
#endif /* !__CRT_HAVE_free && !__CRT_HAVE_cfree */
#endif /* !__local__free_dbg_defined */
