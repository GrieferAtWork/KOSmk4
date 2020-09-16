/* HASH CRC-32:0xe8fac589 */
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
#ifndef __local_error_register_state_defined
#define __local_error_register_state_defined 1
#include <__crt.h>
#include <kos/bits/fastexcept.h>
#ifdef __arch_error_register_state
#include <kos/bits/except.h>
#ifndef __ERROR_REGISTER_STATE_TYPE
#include <bits/mcontext.h>
#define __ERROR_REGISTER_STATE_TYPE   struct mcontext
#define __SIZEOF_ERROR_REGISTER_STATE __SIZEOF_MCONTEXT
#endif /* !__ERROR_REGISTER_STATE_TYPE */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(error_register_state) __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED __ERROR_REGISTER_STATE_TYPE *
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(error_register_state))(void) {
	return __arch_error_register_state();
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_error_register_state_defined
#define __local___localdep_error_register_state_defined 1
#define __localdep_error_register_state __LIBC_LOCAL_NAME(error_register_state)
#endif /* !__local___localdep_error_register_state_defined */
#else /* __arch_error_register_state */
#undef __local_error_register_state_defined
#endif /* !__arch_error_register_state */
#endif /* !__local_error_register_state_defined */
