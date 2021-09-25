/* HASH CRC-32:0x41e1303e */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_getprogname_defined
#define __local_getprogname_defined 1
#include <__crt.h>
#include <libc/template/program_invocation_name.h>
#ifdef __LOCAL_program_invocation_short_name
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(getprogname) __ATTR_CONST __ATTR_WUNUSED char const *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(getprogname))(void) {
	return __LOCAL_program_invocation_short_name;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getprogname_defined
#define __local___localdep_getprogname_defined 1
#define __localdep_getprogname __LIBC_LOCAL_NAME(getprogname)
#endif /* !__local___localdep_getprogname_defined */
#else /* __LOCAL_program_invocation_short_name */
#undef __local_getprogname_defined
#endif /* !__LOCAL_program_invocation_short_name */
#endif /* !__local_getprogname_defined */
