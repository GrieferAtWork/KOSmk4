/* HASH CRC-32:0x93f771f5 */
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
#ifndef __local_feholdexcept_defined
#define __local_feholdexcept_defined 1
#include <__crt.h>
#include <bits/fenv-inline.h>
__NAMESPACE_LOCAL_BEGIN
/* Save the current environment in the object pointed to by ENVP, clear
 * exception flags and install a non-stop mode (if available) for all exceptions */
__LOCAL_LIBC(feholdexcept) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(feholdexcept))(fenv_t *___envp) {
#line 167 "kos/src/libc/magic/fenv.c"
	__inline_feholdexcept(___envp);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_feholdexcept_defined */
