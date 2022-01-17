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
#ifndef GUARD_LIBKERNEL32_K32_C
#define GUARD_LIBKERNEL32_K32_C 1

#include "api.h"
/**/

#include <kos/types.h>
#include <errno.h>

#include "k32.h"

DECL_BEGIN

/* Special functions exported by `libc.so' */
__LIBC NOBLOCK ATTR_PURE /*nt*/ errno_t NOTHROW(LIBDCALL __get_nterrno)(void);
__LIBC NOBLOCK syscall_slong_t NOTHROW(LIBDCALL __set_nterrno)(/*nt*/ errno_t value);

DEFINE_PUBLIC_ALIAS(GetLastError, libk32_GetLastError);
INTERN DWORD CC libk32_GetLastError(void) {
	return __get_nterrno();
}

DEFINE_PUBLIC_ALIAS(SetLastError, libk32_SetLastError);
INTERN void CC libk32_SetLastError(DWORD dwErrCode) {
	__set_nterrno((errno_t)dwErrCode);
}


DECL_END

#endif /* !GUARD_LIBKERNEL32_K32_C */
