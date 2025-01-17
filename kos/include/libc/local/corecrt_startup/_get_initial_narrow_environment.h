/* HASH CRC-32:0x4aab7b44 */
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
#ifndef __local__get_initial_narrow_environment_defined
#define __local__get_initial_narrow_environment_defined
#include <__crt.h>
#ifdef __CRT_HAVE___p___initenv
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep___p___initenv_defined
#define __local___localdep___p___initenv_defined
__CREDIRECT(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,char ***,__NOTHROW,__localdep___p___initenv,(void),__p___initenv,())
#endif /* !__local___localdep___p___initenv_defined */
__LOCAL_LIBC(_get_initial_narrow_environment) __ATTR_PURE __ATTR_WUNUSED char **
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_get_initial_narrow_environment))(void) {
	return *(__NAMESPACE_LOCAL_SYM __localdep___p___initenv)();
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__get_initial_narrow_environment_defined
#define __local___localdep__get_initial_narrow_environment_defined
#define __localdep__get_initial_narrow_environment __LIBC_LOCAL_NAME(_get_initial_narrow_environment)
#endif /* !__local___localdep__get_initial_narrow_environment_defined */
#else /* __CRT_HAVE___p___initenv */
#undef __local__get_initial_narrow_environment_defined
#endif /* !__CRT_HAVE___p___initenv */
#endif /* !__local__get_initial_narrow_environment_defined */
