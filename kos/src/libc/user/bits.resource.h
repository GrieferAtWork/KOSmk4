/* HASH 0x6c49d363 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_BITS_RESOURCE_H
#define GUARD_LIBC_USER_BITS_RESOURCE_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <bits/resource.h>

DECL_BEGIN

INTDEF int NOTHROW_NCX(LIBCCALL libc_prlimit)(pid_t pid, __rlimit_resource_t resource, struct rlimit const *new_limit, struct rlimit *old_limit);
INTDEF int NOTHROW_NCX(LIBCCALL libc_prlimit64)(pid_t pid, __rlimit_resource_t resource, struct rlimit64 const *new_limit, struct rlimit64 *old_limit);

DECL_END

#endif /* !GUARD_LIBC_USER_BITS_RESOURCE_H */
