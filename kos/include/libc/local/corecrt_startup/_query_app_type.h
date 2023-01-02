/* HASH CRC-32:0xb03f2cbf */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__query_app_type_defined
#define __local__query_app_type_defined
#include <__crt.h>
#include <bits/crt/dos/corecrt_startup.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_query_app_type) __ATTR_CONST __ATTR_WUNUSED enum _crt_app_type
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_query_app_type))(void) {
	return (enum _crt_app_type)1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__query_app_type_defined
#define __local___localdep__query_app_type_defined
#define __localdep__query_app_type __LIBC_LOCAL_NAME(_query_app_type)
#endif /* !__local___localdep__query_app_type_defined */
#endif /* !__local__query_app_type_defined */
