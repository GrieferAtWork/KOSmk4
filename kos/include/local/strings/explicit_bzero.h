/* HASH CRC-32:0x9dde99f5 */
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
#ifndef __local_explicit_bzero_defined
#define __local_explicit_bzero_defined 1
#include <__crt.h>
/* Dependency: "bzero" from "strings" */
#ifndef ____localdep_bzero_defined
#define ____localdep_bzero_defined 1
#if __has_builtin(__builtin_bzero) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_bzero)
__CEIREDIRECT(__ATTR_NONNULL((1)),void,__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),bzero,{ return __builtin_bzero(__dst, __num_bytes); })
#elif defined(__CRT_HAVE_bzero)
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE___bzero)
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),__bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE_explicit_bzero)
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),explicit_bzero,(__dst,__num_bytes))
#else /* LIBC: bzero */
#include <local/strings/bzero.h>
#define __localdep_bzero (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzero))
#endif /* bzero... */
#endif /* !____localdep_bzero_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `bzero(buf, len)', however compilers will not optimize away
 * uses of this function when they (think) that clearing the memory
 * wouldn't have any visible side-effects (though those side-effects
 * may be a security-concious application trying to wipe sensitive data) */
__LOCAL_LIBC(explicit_bzero) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(explicit_bzero))(void *__buf,
                                                            __SIZE_TYPE__ __len) {
#line 104 "kos/src/libc/magic/strings.c"
	void *volatile __vbuf = __buf;
	__localdep_bzero(__buf, __len);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_explicit_bzero_defined */
