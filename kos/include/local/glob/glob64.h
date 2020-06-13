/* HASH CRC-32:0xaacf463f */
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
#ifndef __local_glob64_defined
#define __local_glob64_defined 1
#include <__crt.h>
#ifndef ____glob_errfunc_t_defined
#define ____glob_errfunc_t_defined 1
typedef int (__LIBCCALL *__glob_errfunc_t)(char const *__path, int __flags);
#endif /* !____glob_errfunc_t_defined */
struct __glob64_struct;
__NAMESPACE_LOCAL_BEGIN
/* Dependency: glob32 from glob */
#if !defined(__local___localdep_glob32_defined) && defined(__CRT_HAVE_glob)
#define __local___localdep_glob32_defined 1
/* Do glob searching for PATTERN, placing results in PGLOB.
 * The bits defined above may be set in FLAGS.
 * If a directory cannot be opened or read and ERRFUNC is not nil,
 * it is called with the pathname that caused the error, and the
 * `errno' value from the failing call; if it returns non-zero
 * `glob' returns GLOB_ABEND; if it returns zero, the error is ignored.
 * If memory cannot be allocated for PGLOB, GLOB_NOSPACE is returned.
 * Otherwise, `glob' returns zero */
__CREDIRECT(__ATTR_NONNULL((1, 4)),int,__NOTHROW_NCX,__localdep_glob32,(char const *__restrict __pattern, int __flags, __glob_errfunc_t __errfunc, void *__restrict __pglob),glob,(__pattern,__flags,__errfunc,__pglob))
#endif /* !__local___localdep_glob32_defined && __CRT_HAVE_glob */
/* Do glob searching for PATTERN, placing results in PGLOB.
 * The bits defined above may be set in FLAGS.
 * If a directory cannot be opened or read and ERRFUNC is not nil,
 * it is called with the pathname that caused the error, and the
 * `errno' value from the failing call; if it returns non-zero
 * `glob' returns GLOB_ABEND; if it returns zero, the error is ignored.
 * If memory cannot be allocated for PGLOB, GLOB_NOSPACE is returned.
 * Otherwise, `glob' returns zero */
__LOCAL_LIBC(glob64) __ATTR_NONNULL((1, 4)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(glob64))(const char *__restrict __pattern, int __flags, __glob_errfunc_t __errfunc, struct __glob64_struct *__restrict __pglob) {
#ifdef __CRT_HAVE_glob
	return __localdep_glob32(__pattern, __flags, __errfunc, __pglob);
#else /* __CRT_HAVE_glob */
	(void)__pattern;
	(void)__flags;
	(void)__errfunc;
	(void)__pglob;
	__COMPILER_IMPURE();
	return GLOB_NOSYS;
#endif /* !__CRT_HAVE_glob */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_glob64_defined
#define __local___localdep_glob64_defined 1
#define __localdep_glob64 __LIBC_LOCAL_NAME(glob64)
#endif /* !__local___localdep_glob64_defined */
#endif /* !__local_glob64_defined */
