/* HASH CRC-32:0x9478b987 */
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
#ifndef __local__putenv_s_defined
#if defined(__CRT_HAVE_setenv)
#define __local__putenv_s_defined 1
#include <parts/errno.h>
/* Dependency: "setenv" from "stdlib" */
#ifndef ____localdep_setenv_defined
#define ____localdep_setenv_defined 1
#if defined(__CRT_HAVE_setenv)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_setenv,(char const *__varname, char const *__val, int __replace),setenv,(__varname,__val,__replace))
#elif defined(__CRT_HAVE__putenv_s)
#include <local/stdlib/setenv.h>
#define __localdep_setenv (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setenv))
#else /* CUSTOM: setenv */
#undef ____localdep_setenv_defined
#endif /* setenv... */
#endif /* !____localdep_setenv_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_putenv_s) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_putenv_s))(char const *__varname,
                                                       char const *__val) {
#line 2588 "kos/src/libc/magic/stdlib.c"
	return __localdep_setenv(__varname, __val, 1) ? __libc_geterrno_or(__EINVAL) : 0;
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_setenv) */
#endif /* !__local__putenv_s_defined */
