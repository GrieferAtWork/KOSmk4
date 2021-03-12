/* HASH CRC-32:0xa51ad4d2 */
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
#ifndef __local_tdestroy_defined
#define __local_tdestroy_defined 1
#include <__crt.h>
#ifndef ____free_fn_t_defined
#define ____free_fn_t_defined 1
typedef void (__LIBKCALL *__free_fn_t)(void *__nodep);
#endif /* !____free_fn_t_defined */
__NAMESPACE_LOCAL_BEGIN
/* Dependency: free from stdlib */
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined 1
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ return __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
/* >> tdestroy(3)
 * Destroy the whole tree, call `freefct' for each node or leaf */
__LOCAL_LIBC(tdestroy) __ATTR_NONNULL((2)) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(tdestroy))(void *__root, __free_fn_t __freefct) {
__again:
	if (__root) {
		void *__l, *__r;
		__l = ((void **)__root)[1];
		__r = ((void **)__root)[2];
		(*__freefct)(((void **)__root)[0]);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
		__localdep_free(__root);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree */
		if (__l) {
			if (__r)
				__LIBC_LOCAL_NAME(tdestroy)(__r, __freefct);
			__root = __l;
			goto __again;
		}
		if (__r) {
			__root = __r;
			goto __again;
		}
	}
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_tdestroy_defined
#define __local___localdep_tdestroy_defined 1
#define __localdep_tdestroy __LIBC_LOCAL_NAME(tdestroy)
#endif /* !__local___localdep_tdestroy_defined */
#endif /* !__local_tdestroy_defined */
