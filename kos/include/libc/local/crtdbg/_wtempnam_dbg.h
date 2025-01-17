/* HASH CRC-32:0x2c21b453 */
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
#ifndef __local__wtempnam_dbg_defined
#define __local__wtempnam_dbg_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_wtempnam_dbg) __ATTR_WUNUSED __WCHAR16_TYPE__ *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_wtempnam_dbg))(__WCHAR16_TYPE__ const *__dir_name, __WCHAR16_TYPE__ const *__file_prefix, int __block_type, char const *__filename, int __line) {
	(void)__block_type;
	(void)__filename;
	(void)__line;
	(void)__dir_name;
	(void)__file_prefix;
	/* TODO: c16tempnam() */
	__COMPILER_IMPURE();
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__wtempnam_dbg_defined
#define __local___localdep__wtempnam_dbg_defined
#define __localdep__wtempnam_dbg __LIBC_LOCAL_NAME(_wtempnam_dbg)
#endif /* !__local___localdep__wtempnam_dbg_defined */
#endif /* !__local__wtempnam_dbg_defined */
