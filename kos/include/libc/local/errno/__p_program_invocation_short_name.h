/* HASH CRC-32:0x792fe98e */
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
#ifndef __local___p_program_invocation_short_name_defined
#define __local___p_program_invocation_short_name_defined
#include <__crt.h>
#include <libc/template/program_invocation_name.h>
#ifdef __LOCAL_program_invocation_short_name_p
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__p_program_invocation_short_name) __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED char **
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(__p_program_invocation_short_name))(void) {
	return &__LOCAL_program_invocation_short_name_p;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___p_program_invocation_short_name_defined
#define __local___localdep___p_program_invocation_short_name_defined
#define __localdep___p_program_invocation_short_name __LIBC_LOCAL_NAME(__p_program_invocation_short_name)
#endif /* !__local___localdep___p_program_invocation_short_name_defined */
#else /* __LOCAL_program_invocation_short_name_p */
#undef __local___p_program_invocation_short_name_defined
#endif /* !__LOCAL_program_invocation_short_name_p */
#endif /* !__local___p_program_invocation_short_name_defined */
