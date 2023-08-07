/* HASH CRC-32:0xafb5b37e */
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
#ifndef GUARD_LIBC_AUTO_ERRNO_H
#define GUARD_LIBC_AUTO_ERRNO_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <errno.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> __p_program_invocation_short_name(3)
 * Alias for `strchr(argv[0], '/') ? strchr(argv[0], '/') + 1 : argv[0]', as passed to main() */
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char **NOTHROW(LIBCCALL libc___p_program_invocation_short_name)(void);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_ERRNO_H */
