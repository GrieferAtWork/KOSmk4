/* HASH CRC-32:0xe7318dd0 */
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
#ifndef GUARD_LIBC_AUTO_SYS_MKDEV_H
#define GUARD_LIBC_AUTO_SYS_MKDEV_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/mkdev.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED dev_t NOTHROW(LIBDCALL libd_makedev)(major_t maj, minor_t min);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED dev_t NOTHROW(LIBCCALL libc_makedev)(major_t maj, minor_t min);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED major_t NOTHROW(LIBDCALL libd_major)(dev_t dev);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED major_t NOTHROW(LIBCCALL libc_major)(dev_t dev);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED minor_t NOTHROW(LIBDCALL libd_minor)(dev_t dev);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED minor_t NOTHROW(LIBCCALL libc_minor)(dev_t dev);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED dev_t NOTHROW(LIBDCALL libd___makedev)(int version, major_t maj, minor_t min);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED dev_t NOTHROW(LIBCCALL libc___makedev)(int version, major_t maj, minor_t min);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED major_t NOTHROW(LIBDCALL libd___major)(int version, dev_t dev);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED major_t NOTHROW(LIBCCALL libc___major)(int version, dev_t dev);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED minor_t NOTHROW(LIBDCALL libd___minor)(int version, dev_t dev);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED minor_t NOTHROW(LIBCCALL libc___minor)(int version, dev_t dev);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SYS_MKDEV_H */
