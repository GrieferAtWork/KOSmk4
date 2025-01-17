/* HASH CRC-32:0x31b06a15 */
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
#ifndef GUARD_LIBC_AUTO_SYS_SELECT_C
#define GUARD_LIBC_AUTO_SYS_SELECT_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/sys.select.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <asm/os/fd_set.h>
#include <bits/os/fd_set.h>
#include <hybrid/__assert.h>
INTERN ATTR_SECTION(".text.crt.io.poll") ATTR_CONST WUNUSED longptr_t
NOTHROW(LIBCCALL libc___fdelt_chk)(longptr_t fd) {
	__hybrid_assertf(fd >= 0 && fd < __FD_SETSIZE,
	                 "fd %ld cannot be used with `fd_set'",
	                 (long int)fd);
	return fd / __NFDBITS;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(__fdelt_warn,libc___fdelt_chk,ATTR_CONST WUNUSED,longptr_t,NOTHROW,LIBCCALL,(longptr_t fd),(fd));
DEFINE_PUBLIC_ALIAS_P(__fdelt_chk,libc___fdelt_chk,ATTR_CONST WUNUSED,longptr_t,NOTHROW,LIBCCALL,(longptr_t fd),(fd));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_SYS_SELECT_C */
