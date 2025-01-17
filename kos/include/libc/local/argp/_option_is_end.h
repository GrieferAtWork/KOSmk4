/* HASH CRC-32:0x3e4fe397 */
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
#ifndef __local__option_is_end_defined
#define __local__option_is_end_defined
#include <__crt.h>
#include <bits/crt/argp.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_option_is_end) __ATTR_IN(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_option_is_end))(struct argp_option const *__opt) {
	return !__opt->name && !__opt->key && !__opt->doc && !__opt->group;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__option_is_end_defined
#define __local___localdep__option_is_end_defined
#define __localdep__option_is_end __LIBC_LOCAL_NAME(_option_is_end)
#endif /* !__local___localdep__option_is_end_defined */
#endif /* !__local__option_is_end_defined */
