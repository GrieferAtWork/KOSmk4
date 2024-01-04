/* HASH CRC-32:0x8066f4a1 */
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
#ifndef __local_OpenAt64_defined
#define __local_OpenAt64_defined
#include <__crt.h>
#ifdef __CRT_HAVE_OpenAt
#include <kos/anno.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_OpenAt32_defined
#define __local___localdep_OpenAt32_defined
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(2),__fd_t,__THROWING(...),__localdep_OpenAt32,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),OpenAt,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#endif /* !__local___localdep_OpenAt32_defined */
__NAMESPACE_LOCAL_END
#include <asm/os/oflags.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(OpenAt64) __ATTR_WUNUSED __ATTR_IN(2) __fd_t
(__VLIBCCALL __LIBC_LOCAL_NAME(OpenAt64))(__fd_t __dirfd, char const *__filename, __oflag_t __oflags, ...) __THROWS(...) {
	__fd_t __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __oflags);
#ifdef __O_LARGEFILE
	__result = (__NAMESPACE_LOCAL_SYM __localdep_OpenAt32)(__dirfd, __filename, __oflags | __O_LARGEFILE, __builtin_va_arg(__args, __mode_t));
#else /* __O_LARGEFILE */
	__result = (__NAMESPACE_LOCAL_SYM __localdep_OpenAt32)(__dirfd, __filename, __oflags, __builtin_va_arg(__args, __mode_t));
#endif /* !__O_LARGEFILE */
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_OpenAt64_defined
#define __local___localdep_OpenAt64_defined
#define __localdep_OpenAt64 __LIBC_LOCAL_NAME(OpenAt64)
#endif /* !__local___localdep_OpenAt64_defined */
#else /* __CRT_HAVE_OpenAt */
#undef __local_OpenAt64_defined
#endif /* !__CRT_HAVE_OpenAt */
#endif /* !__local_OpenAt64_defined */
