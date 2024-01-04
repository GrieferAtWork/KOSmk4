/* HASH CRC-32:0x9819bf64 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_ERRNO_C
#define GUARD_LIBC_AUTO_ERRNO_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/errno.h"

DECL_BEGIN

#include "../libc/globals.h"
#ifndef __KERNEL__
/* >> __p_program_invocation_short_name(3)
 * Alias for `strchr(argv[0], '/') ? strchr(argv[0], '/') + 1 : argv[0]', as passed to main() */
INTERN ATTR_SECTION(".text.crt.errno.utility") ATTR_CONST ATTR_RETNONNULL WUNUSED char **
NOTHROW(LIBCCALL libc___p_program_invocation_short_name)(void) {
	return &__LOCAL_program_invocation_short_name_p;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__p_program_invocation_short_name, libc___p_program_invocation_short_name);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_ERRNO_C */
