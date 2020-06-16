/* HASH CRC-32:0x7124bc77 */
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
#ifndef __local_setenv_defined
#define __local_setenv_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_getenv) && defined(__CRT_HAVE__putenv_s)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: dos_putenv_s from stdlib */
#ifndef __local___localdep_dos_putenv_s_defined
#define __local___localdep_dos_putenv_s_defined 1
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_dos_putenv_s,(char const *__varname, char const *__val),_putenv_s,(__varname,__val))
#endif /* !__local___localdep_dos_putenv_s_defined */
/* Dependency: getenv from stdlib */
#ifndef __local___localdep_getenv_defined
#define __local___localdep_getenv_defined 1
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_getenv,(char const *__varname),getenv,(__varname))
#endif /* !__local___localdep_getenv_defined */
__LOCAL_LIBC(setenv) __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(setenv))(char const *__varname, char const *__val, int __replace) {
	if (!__replace && __localdep_getenv(__varname))
		return 0;
	return __localdep_dos_putenv_s(__varname, __val);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_setenv_defined
#define __local___localdep_setenv_defined 1
#define __localdep_setenv __LIBC_LOCAL_NAME(setenv)
#endif /* !__local___localdep_setenv_defined */
#else /* __CRT_HAVE_getenv && __CRT_HAVE__putenv_s */
#undef __local_setenv_defined
#endif /* !__CRT_HAVE_getenv || !__CRT_HAVE__putenv_s */
#endif /* !__local_setenv_defined */
