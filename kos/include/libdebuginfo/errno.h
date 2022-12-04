/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBDEBUGINFO_ERRNO_H
#define _LIBDEBUGINFO_ERRNO_H 1

#include "api.h"

/* Debug info error codes. */
#define DEBUG_INFO_ERROR_SUCCESS 0 /* Function completed successfully. */
#define DEBUG_INFO_ERROR_NOFRAME 1 /* No debug information associated with the given location. */
#define DEBUG_INFO_ERROR_CORRUPT 2 /* Debug information has been corrupted. */

#ifdef __CC__
__DECL_BEGIN

/* Debug info error code (one of `DEBUG_INFO_ERROR_*') */
typedef unsigned int debuginfo_errno_t;

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBDEBUGINFO_ERRNO_H */
