/* HASH CRC-32:0xc313e52e */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_getpwd_defined
#define __local_getpwd_defined
#include <__crt.h>
#if defined(__CRT_HAVE_get_current_dir_name) || defined(__CRT_HAVE_getcwd) || defined(__CRT_HAVE__getcwd)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_get_current_dir_name_defined
#define __local___localdep_get_current_dir_name_defined
#ifdef __CRT_HAVE_get_current_dir_name
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_RPC,__localdep_get_current_dir_name,(void),get_current_dir_name,())
#elif defined(__CRT_HAVE_getcwd) || defined(__CRT_HAVE__getcwd)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/get_current_dir_name.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_get_current_dir_name __LIBC_LOCAL_NAME(get_current_dir_name)
#else /* ... */
#undef __local___localdep_get_current_dir_name_defined
#endif /* !... */
#endif /* !__local___localdep_get_current_dir_name_defined */
__LOCAL_LIBC(getpwd) __ATTR_WUNUSED char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(getpwd))(void) {
	static char *__result = __NULLPTR;
	if (__result == __NULLPTR)
		__result = (__NAMESPACE_LOCAL_SYM __localdep_get_current_dir_name)();
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getpwd_defined
#define __local___localdep_getpwd_defined
#define __localdep_getpwd __LIBC_LOCAL_NAME(getpwd)
#endif /* !__local___localdep_getpwd_defined */
#else /* __CRT_HAVE_get_current_dir_name || __CRT_HAVE_getcwd || __CRT_HAVE__getcwd */
#undef __local_getpwd_defined
#endif /* !__CRT_HAVE_get_current_dir_name && !__CRT_HAVE_getcwd && !__CRT_HAVE__getcwd */
#endif /* !__local_getpwd_defined */
