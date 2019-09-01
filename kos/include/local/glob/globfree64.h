/* HASH 0x15250c50 */
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
#ifndef __local_globfree64_defined
#define __local_globfree64_defined 1
struct __glob64_struct;
/* Dependency: "globfree32" from "glob" */
#ifndef ____localdep_globfree32_defined
#define ____localdep_globfree32_defined 1
#if defined(__CRT_HAVE_globfree)
/* Free storage allocated in PGLOB by a previous `glob' call */
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_globfree32,(void *__pglob),globfree,(__pglob))
#else /* LIBC: globfree */
#undef ____localdep_globfree32_defined
#endif /* globfree32... */
#endif /* !____localdep_globfree32_defined */

__NAMESPACE_LOCAL_BEGIN
/* Free storage allocated in PGLOB by a previous `glob' call */
__LOCAL_LIBC(globfree64) __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(globfree64))(struct __glob64_struct *__pglob) {
#line 215 "kos/src/libc/magic/glob.c"
#if defined(__CRT_HAVE_globfree)
	__localdep_globfree32(__pglob);
#else
	(void)__pglob;
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !__local_globfree64_defined */
