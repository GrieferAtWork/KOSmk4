/* HASH CRC-32:0x7774fe0 */
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
#ifndef __local_setenv_defined
#ifdef __CRT_HAVE__putenv_s
#define __local_setenv_defined 1
/* Dependency: "getenv" */
#ifndef ____localdep_getenv_defined
#define ____localdep_getenv_defined 1
#ifdef __CRT_HAVE_getenv
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_getenv,(char const *__varname),getenv,(__varname))
#else /* LIBC: getenv */
#undef ____localdep_getenv_defined
#endif /* getenv... */
#endif /* !____localdep_getenv_defined */

/* Dependency: "dos_putenv_s" from "stdlib" */
#ifndef ____localdep_dos_putenv_s_defined
#define ____localdep_dos_putenv_s_defined 1
#ifdef __CRT_HAVE__putenv_s
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_dos_putenv_s,(char const *__varname, char const *__val),_putenv_s,(__varname,__val))
#else /* LIBC: _putenv_s */
#undef ____localdep_dos_putenv_s_defined
#endif /* dos_putenv_s... */
#endif /* !____localdep_dos_putenv_s_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(setenv) __ATTR_NONNULL((2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(setenv))(char const *__varname,
                                                    char const *__val,
                                                    int __replace) {
#line 1353 "kos/src/libc/magic/stdlib.c"
	if (!__replace && __localdep_getenv(__varname))
		return 0;
	return __localdep_dos_putenv_s(__varname, __val);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE__putenv_s) */
#endif /* !__local_setenv_defined */
