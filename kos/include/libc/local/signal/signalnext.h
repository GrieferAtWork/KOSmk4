/* HASH CRC-32:0xd9ed26fe */
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
#ifndef __local_signalnext_defined
#define __local_signalnext_defined 1
#include <__crt.h>
#include <asm/os/signal.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(signalnext) __ATTR_CONST __ATTR_WUNUSED __signo_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(signalnext))(__signo_t __signo) {
	if (__signo >= (__NSIG - 1))
		return 0;
	return __signo + 1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_signalnext_defined
#define __local___localdep_signalnext_defined 1
#define __localdep_signalnext __LIBC_LOCAL_NAME(signalnext)
#endif /* !__local___localdep_signalnext_defined */
#endif /* !__local_signalnext_defined */
