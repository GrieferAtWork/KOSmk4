/* HASH CRC-32:0x6aa880a8 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef __local_glob64_defined
#define __local_glob64_defined 1
struct __glob64_struct;
/* Dependency: "glob32" from "glob" */
#ifndef ____localdep_glob32_defined
#define ____localdep_glob32_defined 1
#ifdef __CRT_HAVE_glob
/* Do glob searching for PATTERN, placing results in PGLOB.
 * The bits defined above may be set in FLAGS.
 * If a directory cannot be opened or read and ERRFUNC is not nil,
 * it is called with the pathname that caused the error, and the
 * `errno' value from the failing call; if it returns non-zero
 * `glob' returns GLOB_ABEND; if it returns zero, the error is ignored.
 * If memory cannot be allocated for PGLOB, GLOB_NOSPACE is returned.
 * Otherwise, `glob' returns zero */
__CREDIRECT(__ATTR_NONNULL((1, 4)),int,__NOTHROW_NCX,__localdep_glob32,(char const *__restrict __pattern, int __flags, __glob_errfunc_t __errfunc, void *__restrict __pglob),glob,(__pattern,__flags,__errfunc,__pglob))
#else /* LIBC: glob */
#undef ____localdep_glob32_defined
#endif /* glob32... */
#endif /* !____localdep_glob32_defined */

__NAMESPACE_LOCAL_BEGIN
/* Do glob searching for PATTERN, placing results in PGLOB.
 * The bits defined above may be set in FLAGS.
 * If a directory cannot be opened or read and ERRFUNC is not nil,
 * it is called with the pathname that caused the error, and the
 * `errno' value from the failing call; if it returns non-zero
 * `glob' returns GLOB_ABEND; if it returns zero, the error is ignored.
 * If memory cannot be allocated for PGLOB, GLOB_NOSPACE is returned.
 * Otherwise, `glob' returns zero */
__LOCAL_LIBC(glob64) __ATTR_NONNULL((1, 4)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(glob64))(const char *__restrict __pattern,
                                                    int __flags,
                                                    __glob_errfunc_t __errfunc,
                                                    struct __glob64_struct *__restrict __pglob) {
#line 212 "kos/src/libc/magic/glob.c"
#if defined(__CRT_HAVE_glob)
	return __localdep_glob32(__pattern, __flags, __errfunc, __pglob);
#else
	(void)__pattern;
	(void)__flags;
	(void)__errfunc;
	(void)__pglob;
	__COMPILER_IMPURE();
	return GLOB_NOSYS;
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !__local_glob64_defined */
