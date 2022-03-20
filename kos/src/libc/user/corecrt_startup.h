/* HASH CRC-32:0x270ecf0a */
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
#ifndef GUARD_LIBC_USER_CORECRT_STARTUP_H
#define GUARD_LIBC_USER_CORECRT_STARTUP_H 1

#include "../api.h"
#include "../auto/corecrt_startup.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <corecrt_startup.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBDCALL libc__seh_filter_dll)(__ULONG32_TYPE__ xno, struct _EXCEPTION_POINTERS *infp_ptrs);
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBDCALL libc__seh_filter_exe)(__ULONG32_TYPE__ xno, struct _EXCEPTION_POINTERS *infp_ptrs);
INTDEF void NOTHROW_NCX(LIBDCALL libc__set_app_type)(_crt_app_type type);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd___setusermatherr)(int (__LIBDCALL *fptr)(struct _exception *));
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc___setusermatherr)(int (__LIBCCALL *fptr)(struct _exception *));
INTDEF char **NOTHROW_NCX(LIBDCALL libc___p__acmdln)(void);
INTDEF __WCHAR16_TYPE__ **NOTHROW_NCX(LIBDCALL libc___p__wcmdln)(void);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_CORECRT_STARTUP_H */
