/* HASH CRC-32:0x9d7fdd88 */
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
#ifndef GUARD_LIBC_USER_PROCESS_H
#define GUARD_LIBC_USER_PROCESS_H 1

#include "../api.h"
#include "../auto/process.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <process.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF uintptr_t NOTHROW_NCX(LIBCCALL libc__beginthread)(void (LIBDCALL *entry)(void *arg), u32 stacksz, void *arg);
INTDEF uintptr_t NOTHROW_NCX(LIBCCALL libc__beginthreadex)(void *sec, u32 stacksz, __dos_beginthreadex_entry_t entry, void *arg, u32 flags, u32 *threadaddr);
INTDEF void NOTHROW_NCX(LIBCCALL libc__endthreadex)(u32 exitcode);
INTDEF void (LIBCCALL libc__cexit)(void) THROWS(...);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libc__register_thread_local_exe_atexit_callback)(_tls_callback_type callback);
INTDEF ATTR_ACCESS_RO_OPT(1) intptr_t (LIBDCALL libd__loaddll)(char __KOS_FIXED_CONST *file) THROWS(...);
INTDEF ATTR_ACCESS_RO_OPT(1) intptr_t (LIBCCALL libc__loaddll)(char __KOS_FIXED_CONST *file) THROWS(...);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_PROCESS_H */
