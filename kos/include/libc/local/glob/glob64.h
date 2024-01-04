/* HASH CRC-32:0x743dca17 */
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
#ifndef __local_glob64_defined
#define __local_glob64_defined
#include <__crt.h>
#include <features.h>
#include <bits/crt/glob.h>
#include <asm/crt/glob.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(glob64) __ATTR_IN(1) __ATTR_OUT(4) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(glob64))(const char *__restrict __pattern, __STDC_INT_AS_UINT_T __flags, int (__LIBKCALL *__errfunc)(char const *__path, int __flags), struct __glob64_struct *__restrict __pglob) {
	(void)__pattern;
	(void)__flags;
	(void)__errfunc;
	(void)__pglob;
	__COMPILER_IMPURE();
	return __GLOB_NOSYS;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_glob64_defined
#define __local___localdep_glob64_defined
#define __localdep_glob64 __LIBC_LOCAL_NAME(glob64)
#endif /* !__local___localdep_glob64_defined */
#endif /* !__local_glob64_defined */
