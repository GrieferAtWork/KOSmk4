/* HASH CRC-32:0x18a11a66 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_FTW_H
#define GUARD_LIBC_AUTO_FTW_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <ftw.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> ftw(3), ftw64(3) */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBDCALL libd_ftw)(char const *dir, __ftw_func_t func, __STDC_INT_AS_UINT_T nopenfd);
/* >> ftw(3), ftw64(3) */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBDCALL libd_ftw64)(char const *dir, __ftw64_func_t func, __STDC_INT_AS_UINT_T nopenfd);
/* >> nftw(3), nftw64(3)
 * @Param: flags: Set of `FTW_PHYS | FTW_MOUNT | FTW_CHDIR | FTW_DEPTH | FTW_ACTIONRETVAL' */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBDCALL libd_nftw)(char const *dir, __nftw_func_t func, __STDC_INT_AS_UINT_T descriptors, __STDC_INT_AS_UINT_T flags);
/* >> nftw(3), nftw64(3)
 * @Param: flags: Set of `FTW_PHYS | FTW_MOUNT | FTW_CHDIR | FTW_DEPTH | FTW_ACTIONRETVAL' */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBDCALL libd_nftw64)(char const *dir, __nftw64_func_t func, __STDC_INT_AS_UINT_T descriptors, __STDC_INT_AS_UINT_T flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_FTW_H */
