/* HASH CRC-32:0x1adaadc */
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
#ifndef __local_freezero_defined
#define __local_freezero_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: explicit_bzero from strings */
#ifndef __local___localdep_explicit_bzero_defined
#define __local___localdep_explicit_bzero_defined 1
#ifdef __CRT_HAVE_bzero
/* Same as `bzero(buf, num_bytes)', however compilers will not optimize
 * away uses of this function when they (think) that clearing the memory
 * wouldn't have any visible side-effects (though those side-effects
 * may be a security-concious application trying to wipe sensitive data) */
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_explicit_bzero,(void *__buf, __SIZE_TYPE__ __num_bytes),bzero,(__buf,__num_bytes))
#elif defined(__CRT_HAVE_explicit_bzero)
/* Same as `bzero(buf, num_bytes)', however compilers will not optimize
 * away uses of this function when they (think) that clearing the memory
 * wouldn't have any visible side-effects (though those side-effects
 * may be a security-concious application trying to wipe sensitive data) */
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_explicit_bzero,(void *__buf, __SIZE_TYPE__ __num_bytes),explicit_bzero,(__buf,__num_bytes))
#elif defined(__CRT_HAVE___bzero)
/* Same as `bzero(buf, num_bytes)', however compilers will not optimize
 * away uses of this function when they (think) that clearing the memory
 * wouldn't have any visible side-effects (though those side-effects
 * may be a security-concious application trying to wipe sensitive data) */
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_explicit_bzero,(void *__buf, __SIZE_TYPE__ __num_bytes),__bzero,(__buf,__num_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/strings/explicit_bzero.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `bzero(buf, num_bytes)', however compilers will not optimize
 * away uses of this function when they (think) that clearing the memory
 * wouldn't have any visible side-effects (though those side-effects
 * may be a security-concious application trying to wipe sensitive data) */
#define __localdep_explicit_bzero __LIBC_LOCAL_NAME(explicit_bzero)
#endif /* !... */
#endif /* !__local___localdep_explicit_bzero_defined */
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
/* Same as `free(mallptr)', but also ensure that the memory region
 * described by `mallptr...+=num_bytes' is explicitly freed to zero, or
 * immediately returned to the OS, rather than being left in cache
 * while still containing its previous contents. */
__LOCAL_LIBC(freezero) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(freezero))(void *__mallptr, __SIZE_TYPE__ __num_bytes) {
	if __likely(__mallptr) {
		__localdep_explicit_bzero(__mallptr, __num_bytes);
		__localdep_free(__mallptr);
	}
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_freezero_defined
#define __local___localdep_freezero_defined 1
#define __localdep_freezero __LIBC_LOCAL_NAME(freezero)
#endif /* !__local___localdep_freezero_defined */
#else /* __CRT_HAVE_free || __CRT_HAVE_cfree */
#undef __local_freezero_defined
#endif /* !__CRT_HAVE_free && !__CRT_HAVE_cfree */
#endif /* !__local_freezero_defined */
