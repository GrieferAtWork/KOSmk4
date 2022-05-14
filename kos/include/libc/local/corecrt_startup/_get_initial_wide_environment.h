/* HASH CRC-32:0xaa68a09a */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__get_initial_wide_environment_defined
#define __local__get_initial_wide_environment_defined
#include <__crt.h>
#if (defined(__CRT_HAVE___p___winitenv) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$__p___winitenv)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep___p___c16initenv_defined
#define __local___localdep___p___c16initenv_defined
#if defined(__CRT_HAVE___p___winitenv) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__CHAR16_TYPE__ ***,__NOTHROW_NCX,__localdep___p___c16initenv,(void),__p___winitenv,())
#elif defined(__CRT_HAVE_DOS$__p___winitenv)
__CREDIRECT_DOS(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__CHAR16_TYPE__ ***,__NOTHROW_NCX,__localdep___p___c16initenv,(void),__p___winitenv,())
#else /* ... */
#undef __local___localdep___p___c16initenv_defined
#endif /* !... */
#endif /* !__local___localdep___p___c16initenv_defined */
__LOCAL_LIBC(_get_initial_wide_environment) __ATTR_PURE __ATTR_WUNUSED __WCHAR16_TYPE__ **
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_get_initial_wide_environment))(void) {
	return (__WCHAR16_TYPE__ **)*(__NAMESPACE_LOCAL_SYM __localdep___p___c16initenv)();
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__get_initial_wide_environment_defined
#define __local___localdep__get_initial_wide_environment_defined
#define __localdep__get_initial_wide_environment __LIBC_LOCAL_NAME(_get_initial_wide_environment)
#endif /* !__local___localdep__get_initial_wide_environment_defined */
#else /* (__CRT_HAVE___p___winitenv && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$__p___winitenv */
#undef __local__get_initial_wide_environment_defined
#endif /* (!__CRT_HAVE___p___winitenv || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$__p___winitenv */
#endif /* !__local__get_initial_wide_environment_defined */
