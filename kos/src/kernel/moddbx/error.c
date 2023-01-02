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
#ifndef GUARD_MODDBX_INCLUDE_ERROR_C
#define GUARD_MODDBX_INCLUDE_ERROR_C 1
#define _KOS_SOURCE 1

/* DeBug eXtensions. */

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER

#include "include/error.h"

#include <stddef.h>
#include <string.h>

DECL_BEGIN

PRIVATE char const error_messages[] =
"Success\0"
"Out of memory\0"
"Syntax error\0"
"Divide by zero\0"
"No such object\0"
"Read-only\0"
"Internal error\0"
"Segmentation fault\0"
"Operation interrupted\0"
"Cannot take address of object\0"
;


/* Returns  the  message associated  with a  given `error'
 * The message is simply the text from the comments above. */
PUBLIC ATTR_CONST WUNUSED char const *
NOTHROW(FCALL dbx_strerror)(dbx_errno_t error) {
	char const *result = NULL;
	if (error <= 0) {
		error = -error;
		result = error_messages;
		while (error) {
			if (!*result) {
				result = NULL;
				break;
			}
			result = strend(result) + 1;
			--error;
		}
	}
	return result;
}


DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_MODDBX_INCLUDE_ERROR_C */
