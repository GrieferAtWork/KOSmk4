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
#ifndef _BITS_OS_KOS_FILE_HANDLE_H
#define _BITS_OS_KOS_FILE_HANDLE_H 1

#include <__stdinc.h>

#include <bits/types.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("handle_bytes")
#pragma push_macro("handle_type")
#pragma push_macro("f_handle")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef handle_bytes
#undef handle_type
#undef f_handle
struct file_handle {
	unsigned int                             handle_bytes; /* Handle bytes ??? */
	int                                      handle_type;  /* Handle type ??? */
	__COMPILER_FLEXIBLE_ARRAY(unsigned char, f_handle);    /* File identifier (max is `MAX_HANDLE_SZ'). */
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("f_handle")
#pragma pop_macro("handle_type")
#pragma pop_macro("handle_bytes")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_KOS_FILE_HANDLE_H */
